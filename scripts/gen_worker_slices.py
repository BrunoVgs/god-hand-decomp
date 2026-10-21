#!/usr/bin/env python3
"""Split the remaining decomp queue into 8 address-balanced worker slices.

Excludes:
  - the six halt-report integrate targets (even if not yet linked)
  - everything already referenced from a *_nm.c / NON_MATCHING TU
  - everything mentioned in progress/permuter_queue.md
  - everything already carved with a tu (matched)

Writes progress/worker_slices/worker-1.json … worker-8.json.
"""
from __future__ import annotations

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "progress" / "worker_slices"
N_WORKERS = 8

EXCLUDE_NAMES = {
    "func_00144B50",
    "func_002E8318",
    "func_001ED3C0",
    "func_0037FC28",
    "func_00313030",
    "func_001B5430",
}


def nm_names() -> set[str]:
    names: set[str] = set()
    for p in (ROOT / "src").rglob("*"):
        if p.suffix not in {".c", ".cc", ".cpp"}:
            continue
        text = p.read_text(errors="ignore")
        if "NON_MATCHING" not in text and not p.name.endswith("_nm.c"):
            continue
        names |= set(re.findall(r'section\("\.text\.([^"]+)"\)', text))
        names |= set(re.findall(r"INCLUDE_ASM\([^,]+,\s*(\w+)\)", text))
    return names


def permuter_names() -> set[str]:
    q = ROOT / "progress" / "permuter_queue.md"
    if not q.is_file():
        return set()
    return set(re.findall(r"`([A-Za-z_][A-Za-z0-9_]*)`", q.read_text()))


def carved_names() -> set[str]:
    cfg = json.loads((ROOT / "compile_config.json").read_text())
    return {
        e["name"]
        for e in cfg.get("carved_funcs") or []
        if isinstance(e, dict) and e.get("name") and e.get("tu")
    }


def main() -> int:
    q = json.loads((ROOT / "progress" / "decomp_queue.json").read_text())
    skip = EXCLUDE_NAMES | nm_names() | permuter_names() | carved_names()
    items = []
    for it in q["queue"]:
        name = it["name"]
        if name in skip:
            continue
        addr = int(str(it.get("address") or it.get("vaddr") or "0"), 16)
        size = int(it.get("size") or 0)
        if size <= 0:
            continue
        items.append(
            {
                "name": name,
                "address": f"0x{addr:08X}",
                "size": size,
                "compiler": it.get("compiler") or "sn-2.95.3-136",
                "unit": it.get("unit"),
                "tier": it.get("tier"),
                "priority": it.get("priority"),
            }
        )
    # Address order, then greedy bin-pack by bytes into 8 slices
    items.sort(key=lambda x: int(x["address"], 16))
    slices: list[list[dict]] = [[] for _ in range(N_WORKERS)]
    bytes_per: list[int] = [0] * N_WORKERS
    # Split address space into 8 contiguous ranges with balanced bytes
    total = sum(i["size"] for i in items)
    target = total / N_WORKERS if N_WORKERS else 1
    # Contiguous by address: walk and cut when cumulative exceeds targets
    cuts = []
    acc = 0
    next_cut = target
    for i, it in enumerate(items):
        acc += it["size"]
        if len(cuts) < N_WORKERS - 1 and acc >= next_cut:
            cuts.append(i + 1)
            next_cut += target
    bounds = [0] + cuts + [len(items)]
    OUT.mkdir(parents=True, exist_ok=True)
    for w in range(N_WORKERS):
        lo, hi = bounds[w], bounds[w + 1]
        chunk = items[lo:hi]
        # Within slice: smallest first (worker instruction)
        chunk_sorted = sorted(chunk, key=lambda x: (x["size"], int(x["address"], 16)))
        payload = {
            "worker": w + 1,
            "address_range": {
                "start": chunk[0]["address"] if chunk else None,
                "end": chunk[-1]["address"] if chunk else None,
            },
            "function_count": len(chunk_sorted),
            "total_bytes": sum(x["size"] for x in chunk_sorted),
            "functions": chunk_sorted,
        }
        path = OUT / f"worker-{w + 1}.json"
        path.write_text(json.dumps(payload, indent=2) + "\n")
        print(
            f"worker-{w + 1}: {payload['function_count']} funcs, "
            f"{payload['total_bytes']} B, "
            f"{payload['address_range']['start']}..{payload['address_range']['end']}"
        )
    print(f"eligible {len(items)} / queue {len(q['queue'])}; skipped {len(skip)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
