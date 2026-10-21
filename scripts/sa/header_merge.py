#!/usr/bin/env python3
"""Checkpoint header merge: move locally declared types into include/ and prove nothing moved.

    python3 scripts/sa/header_merge.py SPEC.json

SPEC.json:
    {"create": {"include/godhand/x.h": "...text..."},
     "changes": [{"header": "include/godhand/y.h" or "src/cod/z.c", "old": "...", "new": "..."}]}

New headers are written first, then every change is applied through nm_handoff.HeaderTxn:
registered units that see a changed header and name one of its identifiers, plus every
registered .c file edited directly, are rebuilt before and after; their objects must be
identical (objcmp: alloc section bytes and relocations). Any difference or build failure
restores every file and object and exits 1.
"""
from __future__ import annotations

import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from nm_handoff import CFG, ROOT, HeaderTxn  # noqa: E402


def main() -> int:
    spec = json.loads(Path(sys.argv[1]).read_text())
    created = []
    clash = [rel for rel in spec.get("create", {}) if (ROOT / rel).exists()]
    if clash:
        print(f"header_merge: {', '.join(clash)} already exist; extend them with a change instead")
        return 1
    for rel, text in spec.get("create", {}).items():
        p = ROOT / rel
        p.write_text(text)
        created.append(p)
    txn = HeaderTxn(spec["changes"], json.loads(CFG.read_text()), set())
    err = txn.apply()
    if err:
        txn.undo()
        for p in created:
            p.unlink()
        print(f"header_merge: FAILED, restored: {err}")
        return 1
    print(f"header_merge: OK, {len(txn.units)} units rebuilt with identical objects")
    for u in txn.units:
        print(f"  {u}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
