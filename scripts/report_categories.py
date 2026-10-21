#!/usr/bin/env python3
"""report_categories.py — score the progress categories per function.

objdiff-cli adds each unit's measures, whole, to every category in the unit's
``metadata.progress_categories``. A library function (one listed in
``progress/function_categories.json``) gets its own category only while it is
a standalone ``asm/nonmatching/<func>`` unit. Once it matches, it moves into an
engine-tagged ``src/cod`` TU, often next to game functions, so the library
categories lost every matched function.

This rescores the categories in ``progress/report.json`` from its per-function
rows. A library function counts under its library category. Every other
function counts under its unit's engine tags (``engine``, ``engine.<subsys>``).
Each unit's tags become the categories of the functions it holds, and its
unit-level measures (data, unit counts) follow those tags.

Idempotent. Pure Python, no toolchain. scripts/progress.sh runs it after
mark_complete.py.

    python3 scripts/report_categories.py          # rewrite report.json
    python3 scripts/report_categories.py --check  # exit 1 if it is stale
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gen_unit_names import load_symbol_addrs  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
REPORT = ROOT / "progress" / "report.json"
CATEGORIES = ROOT / "progress" / "function_categories.json"
SYMBOLS = ROOT / "config" / "symbol_addrs.txt"

_AUTO_FUNC_RE = re.compile(r"func_([0-9A-Fa-f]{8})")

# objdiff's Measures fields in proto order; u64 fields serialise as strings.
_U64 = ("total_code", "matched_code", "total_data", "matched_data",
        "complete_code", "complete_data")
_ORDER = (
    "fuzzy_match_percent", "total_code", "matched_code", "matched_code_percent",
    "total_data", "matched_data", "matched_data_percent", "total_functions",
    "matched_functions", "matched_functions_percent", "complete_code",
    "complete_code_percent", "complete_data", "complete_data_percent",
    "total_units", "complete_units",
)


def _num(value) -> float:
    try:
        return float(value)
    except (TypeError, ValueError):
        return 0.0


def _r32(x: float) -> float:
    return struct.unpack("f", struct.pack("f", x))[0]


def _f32(x: float) -> float:
    """Round to f32 and keep the shortest decimal that round-trips (objdiff's style)."""
    v = _r32(x)
    for p in range(1, 10):
        s = float(f"{v:.{p}g}")
        if _r32(s) == v:
            return s
    return v


def load_library_map(categories_path: Path = CATEGORIES) -> dict[int, str]:
    data = json.loads(categories_path.read_text())
    return {int(a, 16): cat for cat, addrs in data["categories"].items() for a in addrs}


def function_vaddr(name: str, vaddr_by_func: dict[str, int]):
    if name in vaddr_by_func:
        return vaddr_by_func[name]
    m = _AUTO_FUNC_RE.fullmatch(name)
    return int(m.group(1), 16) if m else None


def _finish(acc: dict) -> dict:
    """objdiff's calc_fuzzy_match_percent + calc_matched_percent, zero fields omitted."""
    def pct(n, d):  # f32 steps, as objdiff: n as f32 / d as f32 * 100.0
        return 100.0 if d == 0 else _f32(_r32(_r32(n) / _r32(d)) * 100.0)

    m = dict(acc)
    m["fuzzy_match_percent"] = pct(acc["fuzzy"], 100.0 * acc["total_code"])
    m["matched_code_percent"] = pct(acc["matched_code"], acc["total_code"])
    m["matched_data_percent"] = pct(acc["matched_data"], acc["total_data"])
    m["matched_functions_percent"] = pct(acc["matched_functions"], acc["total_functions"])
    m["complete_code_percent"] = pct(acc["complete_code"], acc["total_code"])
    m["complete_data_percent"] = pct(acc["complete_data"], acc["total_data"])
    out = {}
    for k in _ORDER:
        v = m.get(k, 0)
        if v:
            out[k] = str(int(v)) if k in _U64 else (v if "percent" in k else int(v))
    return out


def rescore(report: dict, library: dict[int, str], vaddr_by_func: dict[str, int]) -> int:
    """Retag units and rewrite ``report["categories"]`` measures in place.
    Returns how many library functions were found in the report."""
    lib_ids = set(library.values())
    order = {c["id"]: i for i, c in enumerate(report.get("categories", []))}
    acc: dict[str, dict] = defaultdict(lambda: defaultdict(float))
    found = 0
    for unit in report.get("units", []):
        md = unit.setdefault("metadata", {})
        engine_tags = [c for c in md.get("progress_categories", []) if c not in lib_ids] or ["engine"]
        complete = bool(md.get("complete"))
        tags: list[str] = []
        for f in unit.get("functions", []):
            lib = library.get(function_vaddr(f["name"], vaddr_by_func))
            found += lib is not None
            cats = [lib] if lib else engine_tags
            size = int(_num(f.get("size")))
            pct = _num(f.get("fuzzy_match_percent"))
            for cid in cats:
                a = acc[cid]
                a["total_code"] += size
                a["total_functions"] += 1
                a["fuzzy"] += pct * size
                if pct == 100.0:
                    a["matched_code"] += size
                    a["matched_functions"] += 1
                if complete:
                    a["complete_code"] += size
                if cid not in tags:
                    tags.append(cid)
        if not tags:  # a data-only unit keeps its tags
            tags = md.get("progress_categories", []) or engine_tags
        md["progress_categories"] = sorted(tags, key=lambda c: order.get(c, len(order)))
        m = unit.get("measures", {})
        for cid in md["progress_categories"]:
            a = acc[cid]
            for k in ("total_data", "matched_data", "complete_data", "total_units", "complete_units"):
                a[k] += _num(m.get(k))
    for cat in report.get("categories", []):
        cat["measures"] = _finish(acc[cat["id"]])
    return found


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description="Score progress categories per function.")
    ap.add_argument("--check", action="store_true",
                    help="exit 1 if report.json categories are out of date (no write).")
    args = ap.parse_args(argv)

    if not REPORT.is_file():
        print("report_categories: progress/report.json missing — nothing to do.")
        return 0
    before = REPORT.read_text()
    report = json.loads(before)
    library = load_library_map()
    _, vaddr_by_func = load_symbol_addrs(SYMBOLS)
    found = rescore(report, library, vaddr_by_func)
    after = json.dumps(report, indent=2) + "\n"
    stale = after != before
    summary = ", ".join(
        f"{c['id']} {c['measures'].get('total_functions', 0)} fns"
        for c in report["categories"] if "." not in c["id"]
    )
    print(f"report_categories: {found}/{len(library)} library functions scored; {summary}"
          f"  [{'STALE' if stale and args.check else 'updated' if stale else 'ok'}]")
    if args.check:
        return 1 if stale else 0
    if stale:
        REPORT.write_text(after)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
