#!/usr/bin/env python3
"""Draft C for one function with m2c. Drafting aid only; not part of the build.

    python3 scripts/m2c_draft.py NAME [--no-context] [--no-src-context] [--raw] [-- extra m2c args]

Cuts NAME out of asm/cod/000000.s, adds glabel/endlabel macro definitions,
and runs tools/m2c/m2c.py -t mipsee-gcc-c on it with a --context header
built from include/ (preprocessed by the Cygnus cpp0 with -DM2CTX, cached in
build/m2c/ until a header changes), plus a second context with the types,
externs and matched-function prototypes found in registered src/ C TUs that
include/ does not already declare (validated with m2c's own C parser, cached
in build/m2c/ctx_src.i until a TU or compile_config.json changes).

Unless --raw is given, the cut listing is adapted to what m2c understands:
jump tables get jtbl_ names plus their case labels and table data (read from
the retail ELF), ldl/ldr and sdl/sdr pairs become ld/sd, and $t0-$t3 are
renamed $a4-$a7 so m2c sees arguments 5-8.

Run from the host: it re-executes itself inside the godhand-nix container,
where .venv lives.
"""
from __future__ import annotations

import json
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MONOLITH = ROOT / "asm" / "cod" / "000000.s"
OUT = ROOT / "build" / "m2c"
CPP0 = ROOT / "compiler/linux/ee/gcc/lib/gcc-lib/ee/2.96-ee-001003-1/cpp0"
VENV_PY = ROOT / ".venv" / "bin" / "python"
RETAIL_ELF = ROOT / "disc_extract" / "SLUS_215.03"
INS_ADDR = re.compile(r"/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/")

ASM_PRELUDE = (
    ".set noat\n.set noreorder\n"
    ".macro glabel label\n.global \\label\n\\label:\n.endm\n"
    ".macro endlabel label\n.endm\n"
    ".macro nonmatching label, size=1\n.endm\n"
)

# Headers m2c's C parser cannot digest (inline asm bodies, intrinsics).
CONTEXT_SKIP = {"mmi.h", "vu0.h", "sync.h", "eesyscall.h", "mul64.h", "gp.h"}


def in_container() -> bool:
    return str(ROOT) == "/src"


def src_items(text: str) -> tuple[list[tuple[str, str]], list[tuple[str, str]]]:
    """Top-level type blocks and declarations of one TU, as (name, text) pairs."""
    types, decls = [], []
    for m in re.finditer(r"(?ms)^(typedef\s+(?:struct|union|enum)\b[^;{]*\{.*?^\}\s*(\w+)\s*;)", text):
        types.append((m.group(2), m.group(1)))
    for m in re.finditer(r"(?ms)^(struct\s+(\w+)\s*\{.*?^\};)", text):
        types.append(("struct " + m.group(2), m.group(1)))
    for m in re.finditer(r"(?m)^(typedef\s+(?:struct|union)\s+(\w+)\s+(\w+)\s*;)", text):
        types.append((m.group(3), m.group(1)))
    for m in re.finditer(r"(?m)^(extern\s+[^;{}()]*?\b(\w+)\s*(?:\[[^\]]*\])?\s*;)", text):
        decls.append((m.group(2), m.group(1)))
    for m in re.finditer(r"(?m)^(extern\s+[^;{}]*?\b(\w+)\s*\([^;{}]*\)\s*;)", text):
        decls.append((m.group(2), m.group(1)))
    for m in re.finditer(r'(?ms)^__attribute__\(\(section\("\.text\.(\w+)"\)\)\)\s*\n([^;{}#]*?)\{', text):
        head = " ".join(m.group(2).split())
        if re.search(rf"\b{re.escape(m.group(1))}\s*\(", head) and not head.startswith(("static", "inline")):
            decls.append((m.group(1), "def:" + head + ";"))
    bad = re.compile(r"__attribute__|__asm__|\basm\b|__inline|#")
    return [t for t in types if not bad.search(t[1])], [d for d in decls if not bad.search(d[1])]


def build_src_context(base: Path) -> Path:
    """Declarations from registered C TUs in src/ that include/ does not already provide."""
    out = OUT / "ctx_src.i"
    cfg_path = ROOT / "compile_config.json"
    cfg = json.loads(cfg_path.read_text())
    tus = [ROOT / u["path"] for u in cfg["compile_units"]
           if u.get("path", "").endswith(".c") and (ROOT / u["path"]).is_file()]
    newest = max([cfg_path.stat().st_mtime, base.stat().st_mtime] + [p.stat().st_mtime for p in tus])
    if out.is_file() and out.stat().st_mtime >= newest:
        return out
    base_text = base.read_text()
    known = set(re.findall(r"\}\s*(\w+)\s*;", base_text)) | set(re.findall(r"typedef[^;{]*?\b(\w+)\s*;", base_text))
    known |= {"struct " + t for t in re.findall(r"struct\s+(\w+)\s*\{", base_text)}
    known_sym = set(re.findall(r"\b(\w+)\s*\(", base_text)) | set(re.findall(r"\b(\w+)\s*(?:\[[^\]]*\])?\s*;", base_text))
    seen_t: dict[str, str | None] = {}
    order_t: list[str] = []
    seen_d: dict[str, str | None] = {}
    norm = lambda s: re.sub(r"/\*.*?\*/|\s+", " ", s, flags=re.S).strip()  # noqa: E731
    for tu in tus:
        types, decls = src_items(tu.read_text(errors="replace"))
        for name, body in types:
            if name in known:
                continue
            if name not in seen_t:
                seen_t[name] = body
                order_t.append(name)
            elif seen_t[name] is not None and norm(seen_t[name]) != norm(body):
                seen_t[name] = None
        for name, body in decls:
            if name in known_sym:
                continue
            is_def = body.startswith("def:")
            body = body[4:] if is_def else body
            if not is_def and re.search(r"\(\s*(void)?\s*\)\s*;$", body):
                continue
            body = body if body.startswith("extern") else "extern " + body
            prev = seen_d.get(name, "")
            if is_def:
                seen_d[name] = "!" + body
            elif prev == "":
                seen_d[name] = body
            elif prev is not None and not prev.startswith("!") and norm(prev) != norm(body):
                seen_d[name] = None
    items = [seen_t[n] for n in order_t if seen_t[n]] + [d.lstrip("!") for d in seen_d.values() if d]
    symbolic_dim = re.compile(r"\[[^\]]*[A-Za-z_][^\]]*\]")
    items = [it for it in items if not symbolic_dim.search(re.sub(r"\b0x[0-9A-Fa-f]+|sizeof\s*\(\w+\)", "0", it))]
    kept = validate_items(base_text, items)
    kept = validate_typemap(base, kept, out)
    return out


def validate_typemap(base: Path, items: list[str], out: Path) -> list[str]:
    """Drop items until m2c's full type-map build (sizes, layouts) accepts base + items."""
    from m2c.arch_mips import MipseeArch  # noqa: E402
    from m2c.c_types import build_typemap  # noqa: E402
    from m2c.error import DecompFailure  # noqa: E402

    for _ in range(200):
        out.write_text("\n".join(items) + "\n")
        try:
            build_typemap([base, out], MipseeArch(), use_cache=False)
            return items
        except DecompFailure as e:
            names = set(re.findall(r"\b[A-Za-z_]\w{2,}\b", str(e))) - {"Failed", "evaluate", "expression",
                                                                    "compile", "time", "only", "simple",
                                                                    "arithmetic", "supported", "for", "now"}
            hit = [i for i, it in enumerate(items) if any(re.search(rf"\b{re.escape(n)}\b", it) for n in names)]
            if not hit:
                out.write_text("")
                return []
            for i in reversed(hit):
                items.pop(i)
    return items


def validate_items(base_text: str, items: list[str]) -> list[str]:
    """Keep the items m2c's C parser accepts after the include/ context, in chunks."""
    sys.path.insert(0, str(ROOT / "tools" / "m2c"))
    from m2c.c_types import parse_c  # noqa: E402  (only importable inside the container)
    from m2c.error import DecompFailure  # noqa: E402

    _, scope = parse_c(base_text, None)
    kept: list[str] = []
    i, chunk = 0, 150
    while i < len(items):
        part = items[i:i + chunk]
        while part:
            src = "\n".join(part) + "\n"
            try:
                _, new_scope = parse_c(src, scope)
            except DecompFailure as e:
                m = re.search(r"at line (\d+)", str(e))
                line = int(m.group(1)) + 1 if m else src.count("\n")
                pos, drop = 0, len(part) - 1
                for k, it in enumerate(part):
                    pos += it.count("\n") + 1
                    if pos >= line:
                        drop = k
                        break
                part.pop(drop)
                continue
            scope = new_scope
            kept += part
            break
        i += chunk
    return kept


def elf_reader(path: Path):
    data = path.read_bytes()
    phoff, phentsize, phnum = struct.unpack_from("<I", data, 0x1C)[0], *struct.unpack_from("<HH", data, 0x2A)
    loads = []
    for i in range(phnum):
        p_type, p_offset, p_vaddr, _, p_filesz = struct.unpack_from("<IIIII", data, phoff + i * phentsize)
        if p_type == 1:
            loads.append((p_vaddr, p_offset, p_filesz))

    def word(vaddr: int) -> int | None:
        for base, off, size in loads:
            if base <= vaddr < base + size:
                return struct.unpack_from("<I", data, off + vaddr - base)[0]
        return None

    return word


def fix_jump_tables(lines: list[str], notes: list[str]) -> str:
    """Rename each jr's table to jtbl_ADDR, label its case targets, and return the .rodata copy."""
    addrs = [int(m.group(1), 16) if (m := INS_ADDR.search(l)) else None for l in lines]
    known = [a for a in addrs if a is not None]
    if not known:
        return ""
    lo_fn, hi_fn = min(known), max(known) + 4
    word = None
    tables: dict[str, list[int]] = {}
    for i, line in enumerate(lines):
        m = re.search(r"\*/\s+jr\s+\$(\w+)", line)
        if not m or m.group(1) == "ra":
            continue
        sym = bound = None
        for back in lines[max(0, i - 16):i][::-1]:
            if sym is None and (s := re.search(r"%lo\((D_([0-9A-F]{8}))\)", back)):
                sym = s.group(1)
            if bound is None and (b := re.search(r"\*/\s+sltiu\s+\$\w+, \$\w+, (0x[0-9A-Fa-f]+|\d+)", back)):
                bound = int(b.group(1), 0)
        if sym is None:
            notes.append(f"jr ${m.group(1)} without a %lo(D_) table read: left as is")
            continue
        word = word or elf_reader(RETAIL_ELF)
        base, entries = int(sym[2:], 16), []
        for k in range(bound if bound else 512):
            w = word(base + 4 * k)
            if w is None or not (lo_fn <= w < hi_fn):
                break
            entries.append(w)
        if entries:
            tables[sym] = entries
    if not tables:
        return ""
    have = {m.group(1) for l in lines if (m := re.match(r"\s*(\.L[0-9A-F]{8}):", l))}
    want = {f".L{t:08X}" for ents in tables.values() for t in ents} - have
    for i in range(len(lines) - 1, -1, -1):
        if addrs[i] is not None and f".L{addrs[i]:08X}" in want:
            lines.insert(i, f"  .L{addrs[i]:08X}:")
    for i, line in enumerate(lines):
        for sym in tables:
            line = line.replace(f"({sym})", f"(jtbl_{sym[2:]})")
        lines[i] = line
    data = [".section .rodata"]
    for sym, ents in tables.items():
        data.append(f"glabel jtbl_{sym[2:]}")
        data += [f".word .L{t:08X}" for t in ents]
        data.append(".word 0")
        notes.append(f"jump table jtbl_{sym[2:]}: {len(ents)} cases")
    return "\n".join(data) + "\n"


def fold_unaligned(lines: list[str], notes: list[str]) -> None:
    """ldl/ldr and sdl/sdr pairs on one register become a single ld/sd (m2c has no ldl)."""
    pair_re = re.compile(r"^(.*\*/\s+)(ldl|ldr|sdl|sdr)(\s+)(\$\w+), (-?0x[0-9A-Fa-f]+|-?\d+)\((\$\w+)\)\s*$")
    n = 0
    for i, line in enumerate(lines):
        m = pair_re.match(line)
        if not m or m.group(2) not in ("ldl", "sdl"):
            continue
        partner = {"ldl": "ldr", "sdl": "sdr"}[m.group(2)]
        hi = int(m.group(5), 0)
        for j in range(i + 1, min(i + 4, len(lines))):
            p = pair_re.match(lines[j])
            if p and p.group(2) == partner and p.group(4) == m.group(4) and p.group(6) == m.group(6) \
                    and int(p.group(5), 0) == hi - 7:
                op = "ld" if partner == "ldr" else "sd"
                lines[i] = f"{m.group(1)}{op}{m.group(3)}{m.group(4)}, {hi - 7:#x}({m.group(6)})"
                lines[j] = f"{p.group(1)}nop"
                n += 1
                break
    if n:
        notes.append(f"{n} ldl/ldr or sdl/sdr pair(s) folded to ld/sd")


def rename_arg_regs(lines: list[str], notes: list[str]) -> None:
    """The listing names registers 8-11 $t0-$t3 (o32); m2c's EE target calls them $a4-$a7."""
    n = 0
    for i, line in enumerate(lines):
        head, sep, ops = line.partition("*/")
        if not sep:
            continue
        new = re.sub(r"\$t([0-3])\b", lambda m: f"$a{int(m.group(1)) + 4}", ops)
        if new != ops:
            n += 1
            lines[i] = head + sep + new
    if n:
        notes.append(f"$t0-$t3 renamed to $a4-$a7 on {n} line(s)")


def extract(name: str, raw: bool = False) -> Path:
    text = MONOLITH.read_text()
    m = re.search(rf"^glabel {re.escape(name)}\n", text, re.M)
    if not m:
        sys.exit(f"m2c_draft: no glabel {name} in {MONOLITH.name}")
    e = re.search(rf"^endlabel {re.escape(name)}\n", text[m.end():], re.M)
    if not e:
        sys.exit(f"m2c_draft: no endlabel {name}")
    body = text[m.start(): m.end() + e.end()]
    data = ""
    notes: list[str] = []
    if not raw:
        lines = body.splitlines()
        data = fix_jump_tables(lines, notes)
        fold_unaligned(lines, notes)
        rename_arg_regs(lines, notes)
        body = "\n".join(lines) + "\n"
    for n in notes:
        print(f"/* m2c_draft: {n} */", flush=True)
    OUT.mkdir(parents=True, exist_ok=True)
    out = OUT / f"{name}.s"
    out.write_text(ASM_PRELUDE + body + data)
    return out


def headers() -> list[Path]:
    return sorted(
        p for p in (ROOT / "include" / "godhand").glob("*.h")
        if p.name not in CONTEXT_SKIP
    )


def build_context() -> Path:
    ctx = OUT / "ctx.i"
    hs = headers()
    newest = max(p.stat().st_mtime for p in hs)
    if ctx.is_file() and ctx.stat().st_mtime >= newest:
        return ctx
    OUT.mkdir(parents=True, exist_ok=True)
    src = OUT / "ctx.c"
    src.write_text("".join(f'#include "godhand/{p.name}"\n' for p in hs))
    subprocess.run(
        [str(CPP0), "-lang-c", "-P", "-DM2CTX",
         f"-I{ROOT / 'include'}", f"-I{ROOT / 'include' / 'sce'}",
         str(src), str(ctx)],
        check=True,
    )
    return ctx


def main() -> int:
    argv = sys.argv[1:]
    if not in_container():
        cmd = [str(ROOT / "scripts" / "container_run.sh"),
               "/src/.venv/bin/python", "/src/scripts/m2c_draft.py", *argv]
        return subprocess.call(cmd)
    if not argv or argv[0].startswith("-"):
        print(__doc__)
        return 2
    name, rest = argv[0], argv[1:]
    use_ctx = "--no-context" not in rest
    use_src = "--no-src-context" not in rest
    raw = "--raw" in rest
    rest = [a for a in rest if a not in ("--no-context", "--no-src-context", "--raw", "--")]
    asm = extract(name, raw)
    cmd = [str(VENV_PY), str(ROOT / "tools" / "m2c" / "m2c.py"),
           "-t", "mipsee-gcc-c"]
    if use_ctx:
        base = build_context()
        cmd += ["--context", str(base)]
        if use_src:
            cmd += ["--context", str(build_src_context(base))]
    cmd += [*rest, str(asm)]
    return subprocess.call(cmd)


if __name__ == "__main__":
    raise SystemExit(main())
