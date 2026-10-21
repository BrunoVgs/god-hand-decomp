#!/usr/bin/env python3
"""Rank remaining areas (runs of consecutive uncarved functions) by small-leaf count.

usage: areas.py [--min ADDR] [--top N] [--show AREA_START]
"""
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "scripts"))
import sa_precheck  # noqa: E402
ASM = ROOT / "asm/cod/000000.s"
LOG = ROOT / "progress/batch_log.md"
SMALL = 256


def load_funcs():
    funcs = []
    cur = None
    addr_re = re.compile(r"/\* [0-9A-F]+ ([0-9A-F]{8}) ")
    for line in ASM.read_text().splitlines():
        if line.startswith("glabel "):
            cur = {"name": line.split()[1], "addr": None, "n": 0, "calls": set()}
            funcs.append(cur)
            continue
        if line.startswith("endlabel"):
            cur = None
            continue
        if cur is None:
            continue
        m = addr_re.search(line)
        if m:
            if cur["addr"] is None:
                cur["addr"] = int(m.group(1), 16)
            cur["n"] += 1
            j = re.search(r"\bjal\s+(\w+)", line)
            if j:
                cur["calls"].add(j.group(1))
    return [f for f in funcs if f["addr"] is not None]


def main():
    args = sys.argv[1:]
    top = 15
    show = None
    lo = 0
    if "--top" in args:
        top = int(args[args.index("--top") + 1])
    if "--show" in args:
        show = int(args[args.index("--show") + 1], 16)
    if "--min" in args:
        lo = int(args[args.index("--min") + 1], 16)
    cfg = json.loads((ROOT / "compile_config.json").read_text())
    carved = {e["name"] for e in cfg["carved_funcs"] if "name" in e}
    tried = set(re.findall(r"^\| [^|]+\| (\S+) \|", LOG.read_text(), re.M))
    for blk in ("handwritten.txt", "mmi_vu.txt"):
        hw = ROOT / "build/sa" / blk
        if hw.exists():
            tried |= set(hw.read_text().split())
    funcs = load_funcs()
    listing = sa_precheck.load_funcs()
    tried |= {n for n in listing if n not in carved and sa_precheck.classify(listing[n])[0].startswith("SKIP")}
    unmatched = {f["name"] for f in funcs if f["name"] not in carved}
    areas = []
    run = []
    for f in funcs:
        if f["name"] in carved:
            if run:
                areas.append(run)
            run = []
        else:
            run.append(f)
    if run:
        areas.append(run)
    rows = []
    for a in areas:
        if a[0]["addr"] < lo:
            continue
        todo = [f for f in a if f["name"] not in tried]
        leaves = [f for f in todo if f["n"] * 4 <= SMALL
                  and not (f["calls"] - {f["name"]}) & unmatched]
        if show is not None and a[0]["addr"] == show:
            for f in a:
                v = sa_precheck.classify(listing.get(f["name"], []))[0]
                st = v if v.startswith("SKIP") else ("tried" if f["name"] in tried else "")
                lf = "leaf" if f in leaves else ""
                callees = sorted((f["calls"] - {f["name"]}) & unmatched)
                print(f"{f['addr']:08X} {f['name']:40s} {f['n']*4:5d} {lf:4s} {st:5s} {' '.join(callees)}")
            return
        if todo:
            rows.append((len(leaves), len(todo), sum(f["n"] for f in todo) * 4, a[0]["addr"]))
    rows.sort(key=lambda r: (-r[0], r[2]))
    for r in rows[:top]:
        print(f"area {r[3]:08X}: small leaves {r[0]:3d}  todo {r[1]:4d}  bytes {r[2]}")


if __name__ == "__main__":
    main()
