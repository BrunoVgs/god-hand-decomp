#!/usr/bin/env python3
"""Take NM-closer handoffs from progress/nm_solved/ into the matching build.

    python3 scripts/sa/nm_handoff.py            # verify only, print verdicts
    python3 scripts/sa/nm_handoff.py --apply    # also splice, register, file folders

Folder format: see progress/nm_solved/README.md.

The NON_MATCHING source holding the function is found by its INCLUDE_ASM line.
- Standalone NM file (not a compile unit, only this function): the solved C,
  with the .text.<fn> section attribute, becomes src/cod/<addr>.c and the NM
  file is removed. Compiler and per-file settings come from meta.json, else the NM
  header. Per-file flags must be in compile.py's per-file vocabulary, and the
  compiler must already be used by some registered unit.
- Function inside a registered TU: its `#ifdef NON_MATCHING ... #endif` block is
  replaced by the solved C (include line dropped). The unit's own compiler and
  flags are used; meta.json may not change them.

header_changes.md: each old declaration must occur exactly once in its header.
Every other registered unit that sees the header and names a declared
identifier is rebuilt (container `compile.py --single-file`) before and after
the change, and its object must stay equivalent (scripts/sa/objcmp.py: alloc
section bytes plus relocations by symbol). Any break, or a failed solved-function
check, restores the headers and objects and rejects the handoff.

The final spliced text is what gets verified (match_check: instruction words
and relocation targets). Real C only. Results append to
progress/nm_solved/handoff_log.tsv (date, fn, verdict, reason) for checkpoints.
"""
from __future__ import annotations

import argparse
import datetime
import json
import re
import shutil
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from objcmp import diff as obj_diff  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
INBOX = ROOT / "progress" / "nm_solved"
LOG = INBOX / "handoff_log.tsv"
CFG = ROOT / "compile_config.json"
WORK = ROOT / "build" / "sa" / "handoff"

ASM_RE = re.compile(r"__asm__|\basm\s*(volatile\s*)?\(|\.word\b")
ALLOWED_ASM_RE = re.compile(r'__asm__\s*(__volatile__|volatile)?\s*\(\s*"(nop)?"\s*(:::\s*"memory"\s*)?\)\s*;')
GUARD_RE = r"#ifdef NON_MATCHING\n.*?#else\n[^#]*?INCLUDE_ASM\(\"[^\"]+\",\s*{fn}\);\n#endif\n?"
UNIT_KEYS_MODELED = {"path", "compiler", "c_flags_drop", "c_flags_add", "as", "fp_hazard_rules", "call_loop_pad"}
C_WORDS = set("""auto break case char const continue default do double else enum extern float for goto if
inline int long register restrict return short signed sizeof static struct switch typedef union unsigned
void volatile while u8 u16 u32 u64 s8 s16 s32 s64 f32 f64 __attribute__ section aligned packed""".split())


def asm_problem(text: str) -> str | None:
    code = re.sub(r"/\*.*?\*/|//[^\n]*", "", text, flags=re.S)
    allowed = ALLOWED_ASM_RE.findall(code)
    rest = ALLOWED_ASM_RE.sub("", code)
    if ASM_RE.search(rest):
        return "contains inline asm or .word"
    if len(allowed) > 1:
        return "more than one inline nop/barrier"
    return None


def extra_definitions(text: str, fn: str) -> list[str]:
    code = re.sub(r"/\*.*?\*/|//[^\n]*", "", text, flags=re.S)
    code = re.sub(r"__attribute__\s*\(\(.*?\)\)", "", code, flags=re.S)
    out = []
    for m in re.finditer(r"^([A-Za-z_][^;{}()]*?)\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{", code, re.M):
        if m.group(2) != fn and not re.search(r"\bstatic\b", m.group(1)):
            out.append(m.group(2))
    return out


def supported_flag_sets() -> tuple[set[str], set[str]]:
    text = (ROOT / "compile.py").read_text()
    out = []
    for name in ("SUPPORTED_C_FLAG_ADDS", "SUPPORTED_C_FLAG_DROPS"):
        m = re.search(rf"^{name} = frozenset\(\{{(.*?)\}}\)", text, re.M | re.S)
        out.append(set(re.findall(r'"([^"]+)"', m.group(1))) if m else set())
    return out[0], out[1]


def find_nm_source(fn: str) -> Path | None:
    pat = re.compile(rf"INCLUDE_ASM\(\"[^\"]+\",\s*{fn}\);")
    for p in sorted((ROOT / "src").rglob("*.c")):
        t = p.read_text(errors="ignore")
        if ("NON_MATCHING" in t or re.search(r"_nm(_\w+)?\.c$", p.name)) and pat.search(t):
            return p
    return None


def already_matched_in(fn: str, nm_rel: str, cfg: dict) -> str | None:
    """The registered owner TU, if it is not the NM source and defines fn in C (not via INCLUDE_ASM)."""
    owner = next((c.get("tu") for c in cfg.get("carved_funcs", []) if c.get("name") == fn), None)
    if not owner or owner == nm_rel or not (ROOT / owner).is_file():
        return None
    t = (ROOT / owner).read_text(errors="ignore")
    if re.search(rf"INCLUDE_ASM\(\"[^\"]+\",\s*{re.escape(fn)}\);", t):
        return None
    return owner if re.search(rf"\b{re.escape(fn)}\s*\([^;{{]*\)\s*\{{", t) else None


def handoff_addr(src: Path, fn: str, cfg: dict) -> str | None:
    """Lower-case 8-digit address for the new <addr>.c, never derived from a symbol's name text."""
    if (m := re.fullmatch(r"\w+_([0-9A-Fa-f]{8})", fn)):
        return m.group(1).lower()
    for c in cfg.get("carved_funcs", []):
        if c.get("name") == fn and c.get("vaddr"):
            return f"{int(c['vaddr'], 16):08x}"
    syms = ROOT / "config" / "symbol_addrs.txt"
    if syms.is_file():
        m = re.search(rf"^{re.escape(fn)}\s*=\s*0x([0-9A-Fa-f]+);", syms.read_text(errors="ignore"), re.M)
        if m:
            return f"{int(m.group(1), 16):08x}"
    return None


def header_opts(text: str) -> dict:
    head = text.split("\n", 1)[0]
    m = re.search(r"\((sn-[\w.\-]+|ee-[\w.\-]+|cygnus[\w.\-]*|gcc[\w.\-]*)", head)
    return {"compiler": m.group(1) if m else None,
            "c_flags_drop": ["-f=-freorder-blocks"] if "drop-reorder" in head else [],
            "c_flags_add": ["-O0"] if re.search(r"[\s,(]-O0\b", head) else [],
            "as": "sn" if "as=sn" in head else None,
            "fp_hazard_rules": (m.group(1) if (m := re.search(r"fp_hazard_rules[ =]([\w,]+)", head)) else None),
            "call_loop_pad": "call_loop_pad" in head}


def check(path: Path, fn: str, o: dict) -> tuple[bool, str]:
    cmd = ["python3", "scripts/match_check.py", str(path), fn, "--compiler", o["compiler"]]
    if "-f=-freorder-blocks" in o.get("c_flags_drop", []):
        cmd.append("--drop-reorder")
    cmd += [f"--wrap-arg={f}" for f in o.get("c_flags_add", [])]
    if o.get("as") == "sn":
        cmd += ["--as", "sn"]
    if o.get("fp_hazard_rules"):
        cmd += ["--fp-hazard-rules", o["fp_hazard_rules"]]
    if o.get("call_loop_pad"):
        cmd.append("--wrap-arg=--call-loop-pad")
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    out = r.stdout + r.stderr
    m = re.search(rf"^MATCH {fn} .*$", out, re.M)
    if m:
        return True, m.group(0)
    fails = [l for l in out.splitlines() if l.startswith(("FAIL", "COMPILE-FAIL"))]
    return False, "; ".join(fails) or (out.strip().splitlines() or ["no output"])[-1]


def remove_function(text: str, fn: str) -> str | None:
    """Drop fn's definition (with its section attribute) and INCLUDE_ASM line from a multi-function NM file."""
    inc = re.compile(rf"^INCLUDE_ASM\(\"[^\"]+\",\s*{fn}\);\n", re.M)
    m = re.search(rf"^(__attribute__\(\(section\(\"\.text\.{fn}\"\)\)\)\n)?[A-Za-z_][^\n;{{}}]*\b{fn}\s*\([^;{{]*\)\s*\{{", text, re.M)
    if not inc.search(text):
        return None
    if not m:
        # Older batch NM files list bare INCLUDE_ASM lines with no C attempt beside them.
        return inc.sub("", text, count=1)
    depth, k = 0, m.end() - 1
    while k < len(text):
        depth += {"{": 1, "}": -1}.get(text[k], 0)
        k += 1
        if depth == 0:
            break
    if depth:
        return None
    end = k + (1 if text[k:k + 1] == "\n" else 0)
    end += 1 if text[end:end + 1] == "\n" else 0
    return inc.sub("", text[:m.start()] + text[end:], count=1)


def with_section(text: str, fn: str) -> str:
    if f'section(".text.{fn}")' in text:
        return text
    m = re.search(rf"^[A-Za-z_][^\n;{{}}]*\b{fn}\s*\([^;{{]*\)\s*\{{", text, re.M)
    if not m:
        raise ValueError("cannot find function definition")
    return text[:m.start()] + f'__attribute__((section(".text.{fn}")))\n' + text[m.start():]


# ---------------------------------------------------------------- header changes

def parse_header_changes(path: Path) -> list[dict]:
    """`## <header path>`, then an old and a new label (`### old`, `Old:`, `**Old**`), each followed by one fenced block."""
    text = path.read_text()
    changes = []
    label = r"^[ \t]*(?:#+[ \t]*)?\**{w}\**:?\**[ \t]*\n\s*```[a-z]*\n(.*?)\n```"
    for sec in re.split(r"^## ", text, flags=re.M)[1:]:
        hdr = sec.split("\n", 1)[0].strip().strip("`")
        old = re.search(label.format(w="old"), sec, re.M | re.S | re.I)
        new = re.search(label.format(w="new"), sec, re.M | re.S | re.I)
        if not (old and new):
            raise ValueError(f"header_changes.md: section {hdr!r} needs an old and a new code block")
        changes.append({"header": hdr, "old": old.group(1), "new": new.group(1)})
    if not changes:
        raise ValueError("header_changes.md has no '## <header>' sections")
    return changes


def declared_names(decl: str) -> set[str]:
    code = re.sub(r"/\*.*?\*/|//[^\n]*", "", decl, flags=re.S)
    names = set(re.findall(r"\b(?:struct|union|enum)\s+([A-Za-z_]\w*)", code))
    names |= set(re.findall(r"([A-Za-z_]\w*)\s*\(", code))
    names |= set(re.findall(r"#define\s+([A-Za-z_]\w*)", code))
    for stmt in re.findall(r"[^;{}]*;", re.sub(r"\{[^{}]*\}", " ", code)):
        ids = re.findall(r"[A-Za-z_]\w*", re.sub(r"\[[^\]]*\]|\([^()]*\)", " ", stmt))
        if ids:
            names.add(ids[-1])
    return {n for n in names if n not in C_WORDS}


def enclosing_names(header_text: str, snippet: str) -> set[str]:
    """Struct/union/enum names around `snippet` when it sits inside a braced body."""
    i = header_text.find(snippet)
    if i < 0:
        return set()
    depth, j = 0, i - 1
    while j >= 0:
        c = header_text[j]
        if c == "}":
            depth += 1
        elif c == "{":
            if depth == 0:
                break
            depth -= 1
        j -= 1
    if j < 0:
        return set()
    names = set(re.findall(r"\b(?:struct|union|enum)\s+([A-Za-z_]\w*)\s*$", header_text[max(0, j - 200):j]))
    depth, k = 1, j + 1
    while k < len(header_text) and depth:
        depth += {"{": 1, "}": -1}.get(header_text[k], 0)
        k += 1
    m = re.match(r"\s*([A-Za-z_]\w*)\s*;", header_text[k:])
    if m:
        names.add(m.group(1))
    return names


def includes_of(path: Path) -> list[str]:
    return re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]', path.read_text(errors="ignore"), re.M)


def affected_units(header: Path, names: set[str], cfg: dict, skip: set[str]) -> list[str]:
    """Registered C units that transitively include `header` and name one of `names`."""
    roots = [ROOT / d for d in cfg.get("include_dirs", [])] + [ROOT / "build" / "asm"]

    def resolve(inc: str, frm: Path) -> Path | None:
        for base in [frm.parent] + roots:
            p = (base / inc).resolve()
            if p.is_file():
                return p
        return None

    memo: dict[Path, set[Path]] = {}

    def closure(p: Path) -> set[Path]:
        if p in memo:
            return memo[p]
        memo[p] = set()
        seen = set()
        for inc in includes_of(p):
            q = resolve(inc, p)
            if q and q not in seen:
                seen.add(q)
                seen |= closure(q)
        memo[p] = seen
        return seen

    target = header.resolve()
    alt = "|".join(map(re.escape, sorted(names)))
    word = re.compile(rf"\b({alt})\b") if names else None
    proto = re.compile(rf"^\s*(extern\s+)?[\w\s\*]+\b({alt})\s*\([^;{{]*\)\s*;\s*$") if names else None

    def header_uses(t: str) -> bool:
        return any(word.search(l) and not proto.match(l) for l in t.splitlines())

    out = []
    for u in cfg["compile_units"]:
        rel = u.get("path")
        if not rel or rel in skip or not rel.endswith((".c", ".cc", ".cpp")):
            continue
        src = ROOT / rel
        if not src.is_file():
            continue
        inc = closure(src.resolve())
        if target not in inc:
            continue
        if word is None or word.search(src.read_text(errors="ignore")) \
                or any(header_uses(h.read_text(errors="ignore")) for h in inc if h != target):
            out.append(rel)
    return out


def obj_path(rel: str) -> Path:
    return ROOT / "build" / Path(rel).with_suffix(".o")


def build_many(rels: list[str]) -> list[str]:
    """Rebuild each unit's object in one container session; return the units that failed."""
    if not rels:
        return []
    loop = ("for f in " + " ".join(rels) + "; do "
            "out=$(python3 compile.py --single-file \"$f\" 2>&1); rc=$?; "
            "if [ $rc -ne 0 ] || printf '%s' \"$out\" | grep -q 'failed (exit'; then echo \"BUILD-FAIL $f\"; fi; done")
    r = subprocess.run(["./scripts/container_run.sh", "bash", "-c", loop], cwd=ROOT, capture_output=True, text=True)
    failed = re.findall(r"^BUILD-FAIL (\S+)$", r.stdout, re.M)
    return failed if r.returncode == 0 else (failed or list(rels))


class HeaderTxn:
    """Apply header changes; prove every other affected unit's object is unchanged; undo on demand."""

    def __init__(self, changes: list[dict], cfg: dict, skip: set[str]):
        self.changes, self.cfg, self.skip = changes, cfg, skip
        self.saved_headers: dict[Path, str] = {}
        self.saved_objs: dict[str, Path] = {}
        self.units: list[str] = []

    def apply(self) -> str | None:
        units: set[str] = set()
        for c in self.changes:
            h = ROOT / c["header"]
            if not h.is_file() or not h.resolve().is_relative_to(ROOT) or not c["header"].startswith(("include/", "src/")):
                return f"header {c['header']} not found under include/ or src/"
            t = h.read_text()
            if t.count(c["old"]) != 1:
                return f"old declaration occurs {t.count(c['old'])}x in {c['header']} (need exactly 1)"
            names = enclosing_names(t, c["old"]) or (declared_names(c["old"]) | declared_names(c["new"]))
            c["names"] = sorted(names)
            units |= set(affected_units(h, names, self.cfg, self.skip))
            if c["header"] not in self.skip and any(u.get("path") == c["header"] for u in self.cfg["compile_units"]):
                units.add(c["header"])
        self.units = sorted(units)
        bak = WORK / "objs"
        shutil.rmtree(bak, ignore_errors=True)
        bak.mkdir(parents=True)
        if (bad := build_many(self.units)):
            return f"baseline build failed for {bad[0]}"
        for rel in self.units:
            dst = bak / rel.replace("/", "__")
            shutil.copy2(obj_path(rel), dst)
            self.saved_objs[rel] = dst
        for c in self.changes:
            h = ROOT / c["header"]
            self.saved_headers.setdefault(h, h.read_text())
            h.write_text(h.read_text().replace(c["old"], c["new"], 1))
        if (bad := build_many(self.units)):
            return f"header change breaks the build of {bad[0]}"
        for rel in self.units:
            d = obj_diff(self.saved_objs[rel], obj_path(rel))
            if d:
                return f"header change alters {rel}: {d}"
        return None

    def undo(self) -> None:
        for h, t in self.saved_headers.items():
            h.write_text(t)
        for rel, saved in self.saved_objs.items():
            shutil.copy2(saved, obj_path(rel))

    def summary(self) -> str:
        hs = sorted({f"{c['header']} ({'/'.join(c.get('names', []))})" for c in self.changes})
        return f"header change {', '.join(hs)}; {len(self.units)} other units rebuilt and unchanged"


# ---------------------------------------------------------------- one handoff

def process(folder: Path, apply: bool) -> tuple[str, str]:
    fn = folder.name
    cs = sorted(folder.glob("*.c"))
    solved = folder / "solved.c" if (folder / "solved.c").is_file() else (cs[0] if len(cs) == 1 else None)
    if solved is None:
        return "rejected", "no single solved .c file in folder"
    text = solved.read_text()
    meta = json.loads((folder / "meta.json").read_text()) if (folder / "meta.json").is_file() else {}
    if (p := asm_problem(text)):
        return "rejected", p
    if (extra := extra_definitions(text, fn)):
        return "rejected", f"also defines non-static {', '.join(extra)} (duplicate symbols at link); one function per folder"
    src = find_nm_source(fn)
    if src is None:
        return "rejected", "no NON_MATCHING source with INCLUDE_ASM for it"
    rel = src.relative_to(ROOT).as_posix()
    cfg = json.loads(CFG.read_text())
    if (owner := already_matched_in(fn, rel, cfg)):
        return "rejected", f"already matched in {owner}; the NON_MATCHING block in {rel} is stale"
    unit = next((u for u in cfg["compile_units"] if u.get("path") == rel), None)
    old = src.read_text()
    WORK.mkdir(parents=True, exist_ok=True)

    rest = None
    if unit is None:
        if len(re.findall(r"INCLUDE_ASM\(", old)) != 1:
            rest = remove_function(old, fn)
            if rest is None:
                return "rejected", f"cannot cut {fn} out of multi-function {rel}; split by hand"
        o = header_opts(old)
        for k in ("compiler", "as", "c_flags_add", "c_flags_drop", "fp_hazard_rules", "call_loop_pad"):
            if k in meta:
                o[k] = meta[k]
        if not isinstance(o.get("call_loop_pad", False), bool):
            return "rejected", f"meta call_loop_pad must be true or false, got {o['call_loop_pad']!r}"
        if meta.get("drop_reorder") and "-f=-freorder-blocks" not in o["c_flags_drop"]:
            o["c_flags_drop"] = o["c_flags_drop"] + ["-f=-freorder-blocks"]
        if not o.get("compiler"):
            return "rejected", "compiler unknown (no meta.json, no NM header)"
        if o["compiler"] not in {u.get("compiler") for u in cfg["compile_units"]}:
            return "rejected", f"compiler {o['compiler']!r} is not used by any registered unit"
        adds, drops = supported_flag_sets()
        bad = [f for f in o["c_flags_add"] if f not in adds] + [f for f in o["c_flags_drop"] if f not in drops]
        if bad:
            return "rejected", f"per-file flags not in compile.py's vocabulary: {bad}"
        body = re.sub(r'^#include "include_asm.h"\n', "", text, flags=re.M)
        body = re.sub(r"^/\* NON_MATCHING[^\n]*\*/\n", "", body)
        try:
            body = with_section(body, fn)
        except ValueError as e:
            return "rejected", str(e)
        tag = ", ".join([o["compiler"]] + (["as=sn"] if o.get("as") == "sn" else [])
                        + ([f"fp_hazard_rules {o['fp_hazard_rules']}"] if o.get("fp_hazard_rules") else [])
                        + (["call_loop_pad"] if o.get("call_loop_pad") else [])
                        + [f"+{f}" for f in o["c_flags_add"]] + [f"-{f}" for f in o["c_flags_drop"]])
        new = f"/* {o['compiler']} */\n" + body.lstrip("\n")
        addr = handoff_addr(src, fn, cfg)
        if addr is None:
            return "rejected", f"cannot derive an address-based file name for {fn}"
        dest = src.parent / f"{addr}.c"
        if dest.exists() and dest != src:
            return "rejected", f"{dest.relative_to(ROOT)} already exists"
        if dest == src and rest is not None:
            return "rejected", f"{rel} holds other drafts; move them to their own <addr>.c files first"
    else:
        extra = set(unit) - UNIT_KEYS_MODELED
        if extra:
            return "rejected", f"unit {rel} has settings match_check can't model ({sorted(extra)}); process by hand"
        o = {"compiler": unit["compiler"], "c_flags_drop": unit.get("c_flags_drop", []),
             "c_flags_add": unit.get("c_flags_add", []), "as": unit.get("as"),
             "fp_hazard_rules": unit.get("fp_hazard_rules"), "call_loop_pad": unit.get("call_loop_pad", False)}
        for k in ("compiler", "as", "c_flags_add", "c_flags_drop", "call_loop_pad"):
            if k in meta and meta[k] not in (o.get(k), None, [], False):
                return "rejected", f"meta {k}={meta[k]!r} differs from registered unit {rel}; units are never changed"
        if meta.get("drop_reorder") and "-f=-freorder-blocks" not in o["c_flags_drop"]:
            return "rejected", f"meta drop_reorder=True but registered unit {rel} keeps reorder; units are never changed"
        body = re.sub(r'^#include "include_asm.h"\n', "", text, flags=re.M)
        new, n = re.subn(GUARD_RE.format(fn=re.escape(fn)), lambda _: body.strip("\n") + "\n", old, count=1, flags=re.S)
        if n != 1:
            return "rejected", f"cannot isolate the NON_MATCHING block for it in {rel}"
        dest = src

    txn = None
    hc = folder / "header_changes.md"
    if hc.is_file():
        try:
            changes = parse_header_changes(hc)
        except ValueError as e:
            return "rejected", str(e)
        txn = HeaderTxn(changes, cfg, {dest.relative_to(ROOT).as_posix()})
        if (err := txn.apply()):
            txn.undo()
            return "rejected", err

    probe = WORK / (dest.stem + ".c")
    probe.write_text(new)
    ok, why = check(probe, fn, o)
    if txn:
        why += f"; {txn.summary()}"
    if not ok:
        if txn:
            txn.undo()
        return "rejected", f"re-verify failed: {why}"
    if not apply:
        if txn:
            txn.undo()
        return "verified", f"{why} -> {dest.relative_to(ROOT)}"

    dest.write_text(new)
    if rest is not None:
        src.write_text(rest)
    elif dest != src:
        src.unlink()
    cmd = ["python3", "scripts/sa_register.py", "add", "--compiler", o["compiler"]]
    if unit is None:
        cmd += [f"--c-flags-drop={f}" for f in o["c_flags_drop"]]
        cmd += [f"--c-flags-add={f}" for f in o["c_flags_add"]]
        if o.get("as") == "sn":
            cmd += ["--as", "sn"]
        if o.get("fp_hazard_rules"):
            cmd += ["--fp-hazard-rules", o["fp_hazard_rules"]]
        if o.get("call_loop_pad"):
            cmd.append("--call-loop-pad")
    cmd += [dest.relative_to(ROOT).as_posix(), fn]
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        if dest != src:
            dest.unlink()
        src.write_text(old)
        if txn:
            txn.undo()
        return "rejected", f"register failed: {(r.stdout + r.stderr).strip()[-200:]}"
    if rest is not None:
        why += f"; cut from {rel}"
    return "registered", f"{why} -> {dest.relative_to(ROOT)}"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--apply", action="store_true")
    args = ap.parse_args()
    (INBOX / "done").mkdir(parents=True, exist_ok=True)
    (INBOX / "rejected").mkdir(parents=True, exist_ok=True)
    folders = [p for p in sorted(INBOX.iterdir()) if p.is_dir() and p.name not in ("done", "rejected")]
    if not folders:
        print("nm_handoff: nothing in progress/nm_solved/")
        return 0
    for f in folders:
        verdict, why = process(f, args.apply)
        print(f"{f.name}\t{verdict}\t{why}")
        if not args.apply:
            continue
        sub = "done" if verdict == "registered" else "rejected"
        target = INBOX / sub / f.name
        if target.exists():
            target = INBOX / sub / f"{f.name}.{datetime.datetime.now():%Y%m%d%H%M%S}"
        shutil.move(str(f), str(target))
        if sub == "rejected":
            (target / "REJECTED.txt").write_text(why + "\n")
        with LOG.open("a") as fh:
            fh.write(f"{datetime.datetime.now():%Y-%m-%d %H:%M}\t{f.name}\t{verdict}\t{why}\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
