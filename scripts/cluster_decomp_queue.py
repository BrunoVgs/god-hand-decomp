#!/usr/bin/env python3
"""Group the remaining decomp queue by exact instruction bodies and by shape.

Reads progress/decomp_queue.json and asm/cod/000000.s. Writes
progress/clusters.json. Does not compile.
"""
from __future__ import annotations

import json
import re
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
QUEUE = ROOT / "progress" / "decomp_queue.json"
ASM = ROOT / "asm" / "cod" / "000000.s"
OUT = ROOT / "progress" / "clusters.json"

GLABEL = re.compile(r"^glabel\s+(\S+)")
ENDLABEL = re.compile(r"^endlabel\s+(\S+)")
INSN = re.compile(r"^\s*/\*.*\*/\s*([A-Za-z0-9_.]+)\b")
BRANCH = {
    "beq", "bne", "bnel", "beql", "bgez", "bgezl", "bgtz", "bgtzl",
    "blez", "blezl", "bltz", "bltzl", "b", "bnez", "bnezl", "beqz", "beqzl",
    "bc1f", "bc1fl", "bc1t", "bc1tl",
}


def load_bodies(wanted: set[str]) -> dict[str, tuple[str, ...]]:
    bodies: dict[str, tuple[str, ...]] = {}
    current: str | None = None
    ops: list[str] = []
    with ASM.open() as handle:
        for line in handle:
            label = GLABEL.match(line)
            if label:
                current = label.group(1)
                ops = []
                continue
            end = ENDLABEL.match(line)
            if end and current == end.group(1):
                if current in wanted:
                    bodies[current] = tuple(ops)
                current = None
                ops = []
                continue
            if current is None:
                continue
            insn = INSN.match(line)
            if insn:
                ops.append(insn.group(1))
    return bodies


def main() -> None:
    queue = json.loads(QUEUE.read_text())["queue"]
    by_name = {item["name"]: item for item in queue}
    bodies = load_bodies(set(by_name))
    exact: dict[tuple, list[str]] = defaultdict(list)
    shape: dict[tuple, list[str]] = defaultdict(list)
    missing = sorted(set(by_name) - set(bodies))
    for name, ops in bodies.items():
        meta = by_name[name]
        branches = tuple(op for op in ops if op in BRANCH or op.startswith("b"))
        likely = any(op.endswith("l") and op[:-1] in BRANCH for op in ops)
        vu = any(op.startswith("v") or op in {"lqc2", "sqc2", "cfc2", "ctc2"} for op in ops)
        exact[(meta["compiler"], meta["size"], ops)].append(name)
        shape[(meta["compiler"], meta["size"], branches, likely, vu)].append(name)

    def rows(groups: dict[tuple, list[str]], kind: str) -> list[dict]:
        out = []
        for key, names in groups.items():
            if len(names) < 2:
                continue
            compiler, size = key[0], key[1]
            names = sorted(names)
            out.append({
                "kind": kind,
                "compiler": compiler,
                "size": size,
                "count": len(names),
                "bytes": len(names) * size,
                "functions": names,
            })
        out.sort(key=lambda row: (-row["bytes"], -row["count"], row["size"], row["functions"][0]))
        for index, row in enumerate(out, start=1):
            row["rank"] = index
        return out

    exact_rows = rows(exact, "exact")
    shape_rows = rows(shape, "shape")
    payload = {
        "source_queue": "progress/decomp_queue.json",
        "functions": len(by_name),
        "bodies_found": len(bodies),
        "missing_from_asm": missing,
        "exact_clusters": exact_rows,
        "shape_clusters": shape_rows,
        "exact_functions": sum(row["count"] for row in exact_rows),
        "exact_bytes": sum(row["bytes"] for row in exact_rows),
    }
    OUT.write_text(json.dumps(payload, indent=2) + "\n")
    print(
        f"{OUT.relative_to(ROOT)}: {len(exact_rows)} exact clusters, "
        f"{payload['exact_functions']} functions, {payload['exact_bytes']} bytes"
    )


if __name__ == "__main__":
    main()
