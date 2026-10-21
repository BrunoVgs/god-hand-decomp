#!/usr/bin/env python3
"""Find the already-matched function whose instruction pattern is closest to a target. Not part of the build.

    python3 scripts/near_clone.py FN [--top N] [--no-compile] [--min RATIO]

Compares mnemonic/operand-shape sequences (registers, immediates and symbols
ignored) against every carved function that has C in its TU. For the best
candidate it copies that TU to build/sa/clone_FN.c with the candidate renamed
to FN and runs match_check with the TU's compiler, so the printed score is the
number of differing instructions that C gives against FN's retail code. The
candidate's C is printed as a starting point when its ratio reaches --min
(default 0.85); below that the m2c draft is usually the better start.
"""
from __future__ import annotations

import difflib
import json
import re
import subprocess
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import sa_precheck  # noqa: E402

INDEX = ROOT / "build" / "sa" / "clone_index.json"


def shape(op: str, args: list[str]) -> str:
    kinds = []
    for a in args:
        if a.startswith("$f"):
            kinds.append("f")
        elif a.startswith("$"):
            kinds.append("r")
        elif "(" in a:
            kinds.append("m")
        else:
            kinds.append("i")
    return op + ":" + "".join(kinds)


def build_index(cfg: dict, funcs: dict) -> dict:
    src_cfg = ROOT / "compile_config.json"
    if INDEX.exists() and INDEX.stat().st_mtime >= src_cfg.stat().st_mtime:
        return json.loads(INDEX.read_text())
    units = {u["path"]: u for u in cfg["compile_units"] if "path" in u}
    idx = {}
    for e in cfg["carved_funcs"]:
        name, tu = e.get("name"), e.get("tu")
        if not name or not tu or name not in funcs or not tu.endswith((".c", ".cc", ".cpp")):
            continue
        p = ROOT / tu
        if not p.exists() or f'".text.{name}"' not in p.read_text(errors="replace"):
            continue
        u = units.get(tu, {})
        idx[name] = {
            "tu": tu,
            "compiler": u.get("compiler", "ee-2.9-991111"),
            "drop": bool(u.get("c_flags_drop")),
            "seq": [shape(op, a) for _, op, a in funcs[name]],
        }
    INDEX.parent.mkdir(parents=True, exist_ok=True)
    INDEX.write_text(json.dumps(idx))
    return idx


def c_body(tu: Path, name: str) -> str | None:
    text = tu.read_text(errors="replace")
    start = text.find(f'__attribute__((section(".text.{name}")))')
    if start < 0:
        return None
    brace = text.find("{", text.find(name, start + 30))
    depth = 0
    for i in range(brace, len(text)):
        depth += {"{": 1, "}": -1}.get(text[i], 0)
        if depth == 0:
            return text[start:i + 1]
    return None


def compile_score(cand: str, info: dict, target: str) -> str:
    src = ROOT / info["tu"]
    text = src.read_text(errors="replace")
    body = c_body(src, cand)
    if body is None:
        return "?"
    renamed = body.replace(f".text.{cand}", f".text.{target}")
    renamed = re.sub(rf"\b{re.escape(cand)}\s*\(", f"{target}(", renamed, count=1)
    existing = c_body(src, target)
    if existing:
        text = text.replace(existing, "")
    out = ROOT / "build" / "sa" / f"clone_{target}{src.suffix}"
    out.write_text(text.replace(body, renamed))
    cmd = [sys.executable, str(ROOT / "scripts" / "match_check.py"), str(out), target, "--compiler", info["compiler"]]
    if info["drop"]:
        cmd.append("--drop-reorder")
    if src.suffix != ".c":
        cmd += ["--lang", "c++"]
    r = subprocess.run(cmd, capture_output=True, text=True)
    res = r.stdout + r.stderr
    if re.search(rf"^MATCH {re.escape(target)}\b", res, re.M):
        return "MATCH (instructions and relocations)"
    d = re.search(r"(\d+) differing insns", res)
    w = re.search(r"(\d+) words vs retail (\d+)", res)
    if d or w:
        return " / ".join(x for x in [w and f"{w.group(1)} words vs {w.group(2)}", d and f"{d.group(1)} insns differ"] if x)
    return "compile failed"


def main() -> int:
    args = sys.argv[1:]
    if not args or args[0].startswith("-"):
        print(__doc__)
        return 2
    target = args[0]
    top = int(args[args.index("--top") + 1]) if "--top" in args else 3
    min_ratio = float(args[args.index("--min") + 1]) if "--min" in args else 0.85
    cfg = json.loads((ROOT / "compile_config.json").read_text())
    funcs = sa_precheck.load_funcs()
    if target not in funcs:
        sys.exit(f"near_clone: {target} not in listing")
    idx = build_index(cfg, funcs)
    seq = [shape(op, a) for _, op, a in funcs[target]]
    n = len(seq)
    cnt = Counter(seq)
    scored = []
    for name, info in idx.items():
        if name == target:
            continue
        s = info["seq"]
        if not (0.8 * n <= len(s) <= 1.25 * n):
            continue
        overlap = sum((cnt & Counter(s)).values()) * 2 / (n + len(s))
        if overlap < min(0.6, min_ratio - 0.15):
            continue
        sm = difflib.SequenceMatcher(None, seq, s, autojunk=False)
        if sm.quick_ratio() < min_ratio - 0.15:
            continue
        scored.append((sm.ratio(), name, info))
    scored.sort(key=lambda x: -x[0])
    if not scored:
        print(f"near_clone: no matched function within reach of {target} ({n} insns); use the m2c draft")
        return 1
    for ratio, name, info in scored[:top]:
        print(f"{ratio:.3f}  {name:40s} {len(info['seq']):4d} insns  {info['compiler']}{' dr' if info['drop'] else ''}  {info['tu']}")
    ratio, name, info = scored[0]
    if ratio < min_ratio:
        print(f"near_clone: best ratio {ratio:.3f} < {min_ratio}; use the m2c draft")
        return 1
    if "--no-compile" not in args:
        print(f"near_clone: {name} C compiled as {target}: {compile_score(name, info, target)}")
    print(f"/* near_clone: from {name} in {info['tu']} (ratio {ratio:.3f}) */")
    print(c_body(ROOT / info["tu"], name))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
