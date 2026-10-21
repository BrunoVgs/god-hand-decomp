#!/usr/bin/env python3
"""Scratch-compile a C file and check functions against retail. Not part of the build.

    python3 scripts/match_check.py SRC.c FUNC [FUNC ...] [--compiler C]
        [--drop-reorder] [--fp-hazard-rules R] [--wrap-arg=ARG ...] [--quiet]

A function matches only if, after applying each of our relocations against
the linker-map address of its symbol, every instruction word equals retail,
and every retail jal/j/%hi/%lo operand has a relocation at that offset.
Relocations against our own sections (.rodata, .data, static symbols) cannot
be resolved before link and count as a mismatch.

Exit 0 if every named function matches. Prints a diff of differing
instructions otherwise.
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MONOLITH = ROOT / "asm" / "cod" / "000000.s"
MAP = ROOT / "build" / "SLUS_215.03.map"
CACHE = ROOT / "build" / "mc"
OBJDUMP = "mipsel-linux-gnu-objdump"

LINE = re.compile(r"/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s*\*/\s*(.*)$")
SYMREF = re.compile(r"%(hi|lo)\(([A-Za-z_.$][\w.$]*)(?:\s*\+\s*(0x[0-9A-Fa-f]+|\d+))?\)")
JREF = re.compile(r"^(jal|j)\s+([A-Za-z_.$][\w.$]*)\s*$")


def container(script: str) -> subprocess.CompletedProcess:
    return subprocess.run(
        [str(ROOT / "scripts" / "container_run.sh"), "bash", "-lc", script],
        cwd=ROOT, capture_output=True, text=True,
    )


def symbol_addresses() -> dict[str, int]:
    out = CACHE / "symaddr.json"
    if out.is_file() and out.stat().st_mtime >= MAP.stat().st_mtime:
        return json.loads(out.read_text())
    table: dict[str, int] = {}
    pat = re.compile(r"^\s+0x([0-9a-fA-F]+)\s+([A-Za-z_.$][\w.$]*)(?:\s*=.*)?$")
    with MAP.open() as fh:
        for line in fh:
            m = pat.match(line)
            if m:
                table.setdefault(m.group(2), int(m.group(1), 16))
    CACHE.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(table))
    return table


def retail_listing(name: str) -> list[tuple[int, int, str]]:
    text = MONOLITH.read_text()
    m = re.search(rf"^glabel {re.escape(name)}\n", text, re.M)
    if not m:
        raise SystemExit(f"match_check: no glabel {name}")
    e = re.search(rf"^endlabel {re.escape(name)}\n", text[m.end():], re.M)
    rows = []
    for line in text[m.end(): m.end() + e.start()].splitlines():
        lm = LINE.search(line)
        if lm:
            word = struct.unpack("<I", bytes.fromhex(lm.group(2)))[0]
            rows.append((int(lm.group(1), 16), word, " ".join(lm.group(3).split())))
    return rows


def retail_pad_words(name: str) -> int:
    """Count of retail `nop` words between `endlabel name` and the next `.align 3`.

    ps2eeas pads each function's .text to 8 bytes; those zero words are only
    accepted when retail has the same inter-function nop pad (the carve slot
    covers it, so the linked bytes are identical)."""
    text = MONOLITH.read_text()
    m = re.search(rf"^endlabel {re.escape(name)}\n((?:[^\n]*\n)*?)\.align 3", text, re.M)
    if not m:
        return 0
    n = 0
    for line in m.group(1).splitlines():
        lm = LINE.search(line)
        if lm:
            if int(lm.group(2), 16) != 0:
                return n
            n += 1
    return n


def sym_addr(sym: str, table: dict[str, int]) -> int | None:
    if sym.startswith(".text.") and sym != ".text.":
        sym = sym[len(".text."):]
    if sym in table:
        return table[sym]
    m = re.fullmatch(r"(?:D|func|jtbl|lbl)_([0-9A-Fa-f]+)", sym)
    return int(m.group(1), 16) if m else None


def sext16(v: int) -> int:
    return v - 0x10000 if v & 0x8000 else v


def parse_objdump(dump: str):
    sections: dict[str, bytes] = {}
    relocs: dict[str, list[tuple[int, str, str]]] = {}
    disasm: dict[str, dict[int, str]] = {}
    part_s, _, rest = dump.partition("__RELOCS__")
    part_r, _, part_d = rest.partition("__DISASM__")
    cur = None
    for line in part_s.splitlines():
        m = re.match(r"Contents of section (\S+):", line)
        if m:
            cur = m.group(1)
            sections[cur] = b""
            continue
        m = re.match(r"\s*[0-9a-f]+\s+((?:[0-9a-f]{2,8}\s)+)", line + " ")
        if cur and m:
            sections[cur] += bytes.fromhex("".join(m.group(1).split()))
    cur = None
    for line in part_r.splitlines():
        m = re.match(r"RELOCATION RECORDS FOR \[(\S+)\]:", line)
        if m:
            cur = m.group(1)
            relocs[cur] = []
            continue
        parts = line.split()
        if cur and len(parts) >= 3 and re.fullmatch(r"[0-9a-f]+", parts[0]):
            relocs[cur].append((int(parts[0], 16), parts[1], parts[2]))
    cur = None
    for line in part_d.splitlines():
        m = re.match(r"Disassembly of section (\S+):", line)
        if m:
            cur = m.group(1)
            disasm[cur] = {}
            continue
        m = re.match(r"\s*([0-9a-f]+):\s+[0-9a-f]{8}\s+(.*)$", line)
        if cur and m:
            disasm[cur][int(m.group(1), 16)] = " ".join(m.group(2).split())
            continue
        m = re.match(r"\s*([0-9a-f]+):\s+(R_MIPS_\w+)\s+(\S+)", line)
        if cur and m:
            off = int(m.group(1), 16)
            disasm[cur][off] = disasm[cur].get(off, "") + f"  [{m.group(2)} {m.group(3)}]"
    return sections, relocs, disasm


def resolve(name, raw, relocs, base, table):
    """Return (words after relocation, set of offsets with relocs, errors)."""
    words = [struct.unpack_from("<I", raw, i)[0] for i in range(0, len(raw), 4)]
    errors: list[str] = []
    seen: set[int] = set()
    rl = sorted(relocs)
    for i, (off, typ, target) in enumerate(rl):
        seen.add(off)
        sym, _, add = target.partition("+")
        addend_extra = int(add, 16) if add else 0
        s = sym_addr(sym, table)
        if s is None:
            errors.append(f"@{off:x} {typ} against unresolvable '{target}'")
            continue
        idx = off // 4
        w = words[idx]
        if typ == "R_MIPS_26":
            tgt = ((w & 0x03FFFFFF) << 2) + s + addend_extra
            words[idx] = (w & 0xFC000000) | ((tgt >> 2) & 0x03FFFFFF)
        elif typ == "R_MIPS_HI16":
            lo = next((r for r in rl[i + 1:] if r[1] == "R_MIPS_LO16" and r[2] == target), None)
            lo_imm = sext16(words[lo[0] // 4] & 0xFFFF) if lo else 0
            ahl = ((w & 0xFFFF) << 16) + lo_imm + addend_extra
            v = s + ahl
            words[idx] = (w & 0xFFFF0000) | (((v + 0x8000) >> 16) & 0xFFFF)
        elif typ == "R_MIPS_LO16":
            v = s + sext16(w & 0xFFFF) + addend_extra
            words[idx] = (w & 0xFFFF0000) | (v & 0xFFFF)
        elif typ == "R_MIPS_32":
            words[idx] = (w + s + addend_extra) & 0xFFFFFFFF
        else:
            errors.append(f"@{off:x} unsupported reloc {typ} {target}")
    return words, seen, errors


def check(name, sections, relocs, disasm, table, quiet) -> bool:
    sec = f".text.{name}"
    retail = retail_listing(name)
    if sec not in sections:
        print(f"FAIL {name}: no section {sec} in object")
        return False
    words, seen, errors = resolve(name, sections[sec], relocs.get(sec, []), retail[0][0], table)
    ok = not errors
    pad = retail_pad_words(name)
    if len(retail) < len(words) <= len(retail) + pad and not any(words[len(retail):]) \
            and (retail[0][0] + 4 * len(words)) % 8 == 0:
        words = words[:len(retail)]
    if len(words) != len(retail):
        print(f"FAIL {name}: {len(words)} words vs retail {len(retail)}")
        ok = False
    diffs = []
    for i, (vaddr, rw, rtext) in enumerate(retail):
        off = i * 4
        ow = words[i] if i < len(words) else None
        needs_reloc = bool(SYMREF.search(rtext) or JREF.match(rtext))
        bad = ow != rw or (needs_reloc and off not in seen)
        if bad:
            diffs.append(i)
        if bad or not quiet:
            pass
    if diffs:
        ok = False
    if ok:
        print(f"MATCH {name} ({len(retail)} insns, {len(seen)} relocs)")
        return True
    print(f"FAIL {name}: {len(diffs)} differing insns" + (f"; {'; '.join(errors)}" if errors else ""))
    if not quiet:
        dis = disasm.get(sec, {})
        n = max(len(retail), len(words))
        dset = set(diffs)
        for i in range(n):
            mark = "!!" if i in dset or i >= len(retail) or i >= len(words) else "  "
            r = retail[i][2] if i < len(retail) else ""
            o = dis.get(i * 4, "") if i < len(words) else ""
            print(f"{mark} {i*4:4x}  {r:<44.44}| {o}")
    return False


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("src", type=Path)
    ap.add_argument("funcs", nargs="+")
    ap.add_argument("--compiler")
    ap.add_argument("--drop-reorder", action="store_true")
    ap.add_argument("--quiet", "-q", action="store_true")
    ap.add_argument("--fp-hazard-rules")
    ap.add_argument("--as", dest="assembler", choices=("ee", "sn"), default="ee",
                    help="stage-3 assembler, as compile_units 'as' (sn = ps2eeas under wibo)")
    ap.add_argument("-D", dest="defines", action="append", default=[])
    ap.add_argument("--lang", default="c", choices=("c", "c++"))
    ap.add_argument("--wrap-arg", action="append", default=[],
                    help="extra ee-cc-wrap argument, e.g. --wrap-arg=--call-loop-pad")
    args = ap.parse_args()
    src = args.src.resolve()
    rel = src.relative_to(ROOT)
    compiler = args.compiler
    if not compiler:
        r = subprocess.run([sys.executable, str(ROOT / "scripts" / "compiler_for_function.py"),
                            args.funcs[0]], capture_output=True, text=True)
        compiler = r.stdout.split()[0] if r.returncode == 0 else "sn-2.95.3-136"
    cfg = json.loads((ROOT / "compile_config.json").read_text())
    flags = [f for f in cfg["c_flags"] if not (args.drop_reorder and f == "-f=-freorder-blocks")]
    extra = list(args.wrap_arg) + [f"-D{d}" for d in args.defines]
    if args.fp_hazard_rules:
        extra.append(f"--fp-hazard-rules={args.fp_hazard_rules}")
    if args.assembler != "ee":
        extra.append(f"--assembler={args.assembler}")
    CACHE.mkdir(parents=True, exist_ok=True)
    obj = CACHE / (src.stem + ".o")
    objr = obj.relative_to(ROOT)
    script = (
        f"set -e; python3 /src/scripts/ee-cc-wrap.py -c --compiler={compiler} -x {args.lang} "
        f"{' '.join(flags)} -I/src/include -I/src/include/sce -I/src/build/asm "
        f"{' '.join(extra)} /src/{rel} -o /src/{objr} 1>&2; "
        f"{OBJDUMP} -s /src/{objr}; echo __RELOCS__; {OBJDUMP} -r /src/{objr}; "
        f"echo __DISASM__; {OBJDUMP} -d -r -M no-aliases /src/{objr}"
    )
    out = container(script)
    if out.returncode != 0:
        print(out.stderr[-4000:])
        print(f"COMPILE-FAIL ({compiler})")
        return 2
    sections, relocs, disasm = parse_objdump(out.stdout)
    table = symbol_addresses()
    results = [check(f, sections, relocs, disasm, table, args.quiet) for f in args.funcs]
    return 0 if all(results) else 1


if __name__ == "__main__":
    raise SystemExit(main())
