#!/usr/bin/env python3
"""Generate a deterministic priority queue for the remaining code matches."""

from __future__ import annotations

import json
import re
from pathlib import Path

from compiler_for_function import lookup_compiler

ROOT = Path(__file__).resolve().parent.parent
REPORT = ROOT / "progress" / "report.json"
CONFIG = ROOT / "compile_config.json"
SYMBOLS = ROOT / "config" / "symbol_addrs.txt"
OUTPUT = ROOT / "progress" / "decomp_queue.json"

SYMBOL_RE = re.compile(
    r"^\s*([A-Za-z_.$][\w.$]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;",
)
FUNC_ADDR_RE = re.compile(r"^func_([0-9A-Fa-f]{6,8})$")


def load_symbol_addresses() -> dict[str, int]:
    addresses: dict[str, int] = {}
    for line in SYMBOLS.read_text().splitlines():
        match = SYMBOL_RE.match(line)
        if match:
            addresses[match.group(1)] = int(match.group(2), 16)
    return addresses


def function_address(name: str, addresses: dict[str, int]) -> int | None:
    match = FUNC_ADDR_RE.match(name)
    if match:
        return int(match.group(1), 16)
    return addresses.get(name)


def priority(size: int, is_named: bool) -> tuple[int, str]:
    if size <= 64:
        return 1, "tiny"
    if size <= 256:
        return 2, "small"
    if is_named and size <= 1024:
        return 3, "named-medium"
    if size <= 1024:
        return 4, "medium"
    return 5, "large"


def main() -> int:
    report = json.loads(REPORT.read_text())
    config = json.loads(CONFIG.read_text())
    carved = {
        entry["name"]
        for entry in config.get("carved_funcs", [])
        if isinstance(entry, dict) and "name" in entry
    }
    addresses = load_symbol_addresses()
    remaining: list[dict[str, object]] = []

    for unit in report.get("units", []):
        unit_name = unit.get("name", "")
        if not unit_name.startswith("asm/cod/000000.part"):
            continue
        for function in unit.get("functions", []) or []:
            name = function["name"]
            if name in carved or name.startswith(("D_", ".L")):
                continue
            size = int(function.get("size", 0))
            address = function_address(name, addresses)
            is_named = FUNC_ADDR_RE.match(name) is None
            rank, tier = priority(size, is_named)
            remaining.append(
                {
                    "name": name,
                    "address": None if address is None else f"0x{address:08X}",
                    "size": size,
                    "instructions": size // 4,
                    "unit": unit_name,
                    "compiler": None if address is None else lookup_compiler(address),
                    "named": is_named,
                    "tier": tier,
                    "priority": rank,
                }
            )

    remaining.sort(
        key=lambda item: (
            item["priority"],
            item["size"],
            item["address"] or "",
            item["name"],
        )
    )
    payload = {
        "source_report": str(REPORT.relative_to(ROOT)),
        "remaining_functions": len(remaining),
        "remaining_code_bytes": sum(int(item["size"]) for item in remaining),
        "queue": remaining,
    }
    OUTPUT.write_text(json.dumps(payload, indent=2) + "\n")
    print(
        f"{OUTPUT.relative_to(ROOT)}: {payload['remaining_functions']} functions, "
        f"{payload['remaining_code_bytes']} bytes"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
