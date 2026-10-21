#!/usr/bin/env python3
"""Register / unregister single-agent matches in compile_config.json.

    python3 scripts/sa_register.py add TU NAME [NAME ...] --compiler C
        [--fp-hazard-rules R] [--drop-reorder] [--as sn]
        [--c-flags-add F ...] [--c-flags-drop F ...]
    python3 scripts/sa_register.py remove NAME [NAME ...]

`add` writes a carved_funcs entry (vaddr/size from asm/cod/000000.s) for each
uncarved NAME pointing at TU, retargets an existing INCLUDE_ASM carve to TU,
and adds TU to compile_units if missing. `--as sn` (ps2eeas, for `dli` chains)
and the per-file `--c-flags-add` / `--c-flags-drop` (checked against
compile.py's SUPPORTED_C_FLAG_ADDS / SUPPORTED_C_FLAG_DROPS) are only accepted
when TU is new to compile_units; an existing unit's settings are never changed.
`remove` drops the carve entries
this tool added (TU still on disk) and the compile_units entry once no carve
points at it.
"""
from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CFG = ROOT / "compile_config.json"
MONOLITH = ROOT / "asm" / "cod" / "000000.s"
LEDGER = ROOT / "progress" / "sa_registered.json"


def listing_info(name: str, text: str) -> tuple[str, int]:
    m = re.search(rf"^nonmatching {re.escape(name)}, 0x([0-9A-Fa-f]+)\n\s*\n?glabel {re.escape(name)}\n\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)", text, re.M)
    if not m:
        raise SystemExit(f"sa_register: cannot find {name} in listing")
    return f"0x{int(m.group(2), 16):08X}", int(m.group(1), 16)


def supported_flag_sets() -> tuple[set[str], set[str]]:
    text = (ROOT / "compile.py").read_text()
    sets = []
    for name in ("SUPPORTED_C_FLAG_ADDS", "SUPPORTED_C_FLAG_DROPS"):
        m = re.search(rf"^{name} = frozenset\(\{{(.*?)\}}\)", text, re.M | re.S)
        sets.append(set(re.findall(r'"([^"]+)"', m.group(1))) if m else set())
    return sets[0], sets[1]


def main() -> int:
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    a = sub.add_parser("add")
    a.add_argument("tu")
    a.add_argument("names", nargs="+")
    a.add_argument("--compiler", required=True)
    a.add_argument("--fp-hazard-rules")
    a.add_argument("--drop-reorder", action="store_true")
    a.add_argument("--as", dest="assembler", choices=("sn",))
    a.add_argument("--c-flags-add", action="append", default=[])
    a.add_argument("--c-flags-drop", action="append", default=[])
    a.add_argument("--call-loop-pad", action="store_true")
    r = sub.add_parser("remove")
    r.add_argument("names", nargs="+")
    args = ap.parse_args()
    cfg = json.loads(CFG.read_text())
    ledger = json.loads(LEDGER.read_text()) if LEDGER.is_file() else {}
    if args.cmd == "add":
        per_file = args.assembler or args.c_flags_add or args.c_flags_drop or args.call_loop_pad
        existing = next((u for u in cfg["compile_units"] if u.get("path") == args.tu), None)
        if per_file and existing is not None:
            raise SystemExit(f"sa_register: {args.tu} is already a compile unit; "
                             "--as / --c-flags-* / --call-loop-pad are only for new per-function files")
        if existing is not None and existing.get("compiler") != args.compiler:
            raise SystemExit(f"sa_register: {args.tu} is compiled with {existing.get('compiler')}; "
                             "the compiler of an existing unit is never changed")
        if existing is None and args.compiler not in {u.get("compiler") for u in cfg["compile_units"]}:
            raise SystemExit(f"sa_register: compiler {args.compiler!r} is not used by any existing unit")
        adds, drops = supported_flag_sets()
        bad = [f for f in args.c_flags_add if f not in adds] + [f for f in args.c_flags_drop if f not in drops]
        if bad:
            raise SystemExit(f"sa_register: not in compile.py's per-file vocabulary: {bad}")
        if args.drop_reorder and "-f=-freorder-blocks" not in args.c_flags_drop:
            args.c_flags_drop.append("-f=-freorder-blocks")
        text = MONOLITH.read_text()
        by_name = {e["name"]: e for e in cfg["carved_funcs"] if "name" in e}
        for n in args.names:
            if n in by_name:
                ledger[n] = {"prev_tu": by_name[n].get("tu")}
                by_name[n]["tu"] = args.tu
            else:
                vaddr, size = listing_info(n, text)
                cfg["carved_funcs"].append({"name": n, "unit": "asm/cod/000000",
                                            "vaddr": vaddr, "size": size,
                                            "tu": args.tu})
                ledger[n] = {"prev_tu": None}
        if not any(u.get("path") == args.tu for u in cfg["compile_units"]):
            u = {"path": args.tu, "compiler": args.compiler}
            if args.fp_hazard_rules:
                u["fp_hazard_rules"] = args.fp_hazard_rules
            if args.c_flags_drop:
                u["c_flags_drop"] = list(dict.fromkeys(args.c_flags_drop))
            if args.c_flags_add:
                u["c_flags_add"] = list(dict.fromkeys(args.c_flags_add))
            if args.assembler:
                u["as"] = args.assembler
            if args.call_loop_pad:
                u["call_loop_pad"] = True
            cfg["compile_units"].append(u)
    else:
        names = {n for n in args.names if n in ledger}
        tus = {e.get("tu") for e in cfg["carved_funcs"] if e.get("name") in names}
        kept = []
        for e in cfg["carved_funcs"]:
            if e.get("name") in names:
                prev = ledger.pop(e["name"])["prev_tu"]
                if prev is None:
                    continue
                e["tu"] = prev
            kept.append(e)
        cfg["carved_funcs"] = kept
        still = {e.get("tu") for e in cfg["carved_funcs"]}
        cfg["compile_units"] = [u for u in cfg["compile_units"]
                                if not (u.get("path") in tus and u.get("path") not in still)]
    CFG.write_text(json.dumps(cfg, indent=2) + "\n")
    LEDGER.write_text(json.dumps(ledger, indent=1) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
