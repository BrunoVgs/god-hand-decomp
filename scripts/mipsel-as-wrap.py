#!/usr/bin/env python3
"""mipsel-as-wrap.py — assembler shim for modern GNU binutils (>= ~2.43).

Why this exists
---------------
The monolithic/​carved ``.s`` for this project use the **O32 symbolic register
names** ($t0-$t7 == $8-$15) that the EE disassembly emits.  Historically the
build assembled them with ``mipsel-linux-gnu-as -mabi=eabi``, and binutils
through 2.42 mapped EABI register names the O32 way, so $t0-$t7 resolved to
$8-$15 and the eabi64 ELF flag (0x4000) matched retail / the ee-as C objects.

Binutils changed EABI to use the **N32/N64 register-name table** (where
$t0-$t3 == $12-$15 and $t4-$t7 do not exist).  Under that table the EE asm
either mis-encodes (e.g. $t0 -> $12 instead of $8) or fails outright on
$t4-$t7 ("invalid operands").

The fix that reproduces the old bytes exactly:
  * assemble with ``-mabi=o64`` instead of ``-mabi=eabi`` — o64 keeps the O32
    register-name table *and* allows the 64-bit / MMI ops the EE needs, so the
    ``.text`` is byte-identical to the 2.42 ``-mabi=eabi`` output (verified
    across all 3655 monolithic fragments);
  * then rewrite the object's EF_MIPS_ABI field from o64 (0x2000) to eabi64
    (0x4000) so ld merges it with the eabi64 C objects and the linked image
    keeps matching retail.

This shim is a no-op on toolchains where ``-mabi=eabi`` already produces the
right bytes (the e_flags rewrite is idempotent: eabi64 -> eabi64).
"""
from __future__ import annotations

import os
import struct
import subprocess
import sys

REAL_AS = os.environ.get("MIPSEL_AS_REAL", "mipsel-linux-gnu-as")

EF_MIPS_ABI_MASK = 0x0000F000
EF_MIPS_ABI_O64 = 0x00002000
EF_MIPS_ABI_EABI64 = 0x00004000


def _patch_eabi64(obj_path: str) -> None:
    """Rewrite EF_MIPS_ABI in a 32-bit ELF e_flags field to eabi64."""
    with open(obj_path, "r+b") as f:
        ident = f.read(16)
        if ident[:4] != b"\x7fELF" or ident[4] != 1:  # ELFCLASS32 only
            return
        little = ident[5] == 1
        end = "<" if little else ">"
        # e_flags is at offset 0x24 in the 32-bit ELF header.
        f.seek(0x24)
        (flags,) = struct.unpack(end + "I", f.read(4))
        new = (flags & ~EF_MIPS_ABI_MASK) | EF_MIPS_ABI_EABI64
        if new != flags:
            f.seek(0x24)
            f.write(struct.pack(end + "I", new))


def _output_path(args: list[str]) -> str | None:
    for i, arg in enumerate(args):
        if arg == "-o" and i + 1 < len(args):
            return args[i + 1]
        if arg.startswith("-o") and len(arg) > 2:
            return arg[2:]
    return None


def _abi(path: str) -> int | None:
    try:
        with open(path, "rb") as fh:
            ident = fh.read(16)
            if len(ident) < 16 or ident[:4] != b"\x7fELF" or ident[4] != 1:
                return None
            endian = "<" if ident[5] == 1 else ">"
            fh.seek(0x24)
            raw = fh.read(4)
            if len(raw) != 4:
                return None
            flags = struct.unpack(endian + "I", raw)[0]
    except OSError:
        return None
    return flags & EF_MIPS_ABI_MASK


def _assemble_and_patch(args: list[str], out: str | None) -> int:
    rc = subprocess.run([REAL_AS, *args]).returncode
    if rc != 0:
        return rc
    if out and os.path.exists(out):
        _patch_eabi64(out)
    return 0


def main(argv: list[str]) -> int:
    # GNU as is invoked as o64 so the O32 register names ($t0-$t7) survive.
    # That writes EF_MIPS_ABI 0x2000 (e_flags 0x20922001). The poke below
    # rewrites it to eabi64. A short read of the just-written object used to
    # skip the poke and leave the O64 flag for the linker.
    args = ["-mabi=o64" if a == "-mabi=eabi" else a for a in argv]
    out = _output_path(args)
    rc = _assemble_and_patch(args, out)
    if rc != 0:
        return rc
    if out is None or _abi(out) == EF_MIPS_ABI_EABI64:
        return 0
    rc = _assemble_and_patch(args, out)
    if rc != 0:
        return rc
    if _abi(out) != EF_MIPS_ABI_EABI64:
        sys.stderr.write(
            f"mipsel-as-wrap: {out} is not eabi64 after retry\n"
        )
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
