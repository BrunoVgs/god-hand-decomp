#!/usr/bin/env python3
"""clone_scan.py [MIN]: best near-clone ratio for every unmatched M2C-class function.

Writes build/sa/clone_queue.txt (size, name, ratio, clone, compiler, TU, verdict), sorted by size,
for ratios >= MIN (default 0.85). Functions that already have an NM file under src/ are marked NM.
"""
import difflib
import json
import re
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
(ROOT / "build" / "sa").mkdir(parents=True, exist_ok=True)
sys.path.insert(0, str(ROOT / "scripts"))
import near_clone  # noqa: E402
import sa_precheck  # noqa: E402

min_ratio = float(sys.argv[1]) if len(sys.argv) > 1 else 0.85
cfg = json.loads((ROOT / "compile_config.json").read_text())
funcs = sa_precheck.load_funcs()
idx = near_clone.build_index(cfg, funcs)
carved = {e["name"] for e in cfg["carved_funcs"] if "name" in e}
nm_src = set()
for p in (ROOT / "src").rglob("*.c"):
    t = p.read_text(errors="replace")
    if "NON_MATCHING" in t:
        nm_src.update(re.findall(r'INCLUDE_ASM\(\s*"[^"]+"\s*,\s*(\w+)\s*\)', t))

by_len = {}
for name, info in idx.items():
    by_len.setdefault(len(info["seq"]), []).append((name, info, Counter(info["seq"])))

rows = []
for name, ins in funcs.items():
    if name in carved:
        continue
    verdict = sa_precheck.classify(ins)[0]
    if verdict != "M2C":
        continue
    seq = [near_clone.shape(op, a) for _, op, a in ins]
    n = len(seq)
    cnt = Counter(seq)
    best = (0.0, None, None)
    for ln in range(int(0.8 * n), int(1.25 * n) + 1):
        for cname, info, ccnt in by_len.get(ln, ()):
            overlap = sum((cnt & ccnt).values()) * 2 / (n + ln)
            if overlap < max(min_ratio, best[0]):
                continue
            sm = difflib.SequenceMatcher(None, seq, info["seq"], autojunk=False)
            if sm.quick_ratio() < max(min_ratio, best[0]):
                continue
            r = sm.ratio()
            if r > best[0]:
                best = (r, cname, info)
    if best[1] and best[0] >= min_ratio:
        info = best[2]
        rows.append((n * 4, name, best[0], best[1], info["compiler"], info["tu"], "NM" if name in nm_src else "M2C"))

rows.sort()
with open(ROOT / "build" / "sa" / "clone_queue.txt", "w") as f:
    for sz, name, r, c, comp, tu, v in rows:
        f.write(f"{sz:5d} {name:36s} {r:.3f} {c:34s} {comp:14s} {tu} {v}\n")
print(f"{len(rows)} candidates >= {min_ratio}; {sum(1 for r in rows if r[6] == 'NM')} already have NM C")
