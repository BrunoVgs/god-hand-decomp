#!/usr/bin/env python3
"""Scan src/** for NON_MATCHING complete-C bodies and refresh the permuter queue.

    python3 scripts/queue_nm_permuter.py

Writes/updates progress/permuter_queue.md. Does not start the permuter.
"""

from __future__ import annotations

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
QUEUE = ROOT / "progress" / "permuter_queue.md"
SRC = ROOT / "src"

_BLOCK = re.compile(
    r"#ifdef\s+NON_MATCHING\b(.*?)^#else\b",
    re.S | re.M,
)
# Prefer section attribute name; it is the retail symbol.
_SECTION_FN = re.compile(
    r'__attribute__\s*\(\(section\s*\("\.text\.([^"]+)"\)\)\)\s*'
    r"[\w\s\*]+\b([A-Za-z_][\w]*)\s*\(",
)


def _sizes_from_clusters_and_config() -> dict[str, int]:
    out: dict[str, int] = {}
    cfg_path = ROOT / "compile_config.json"
    if cfg_path.is_file():
        cfg = json.loads(cfg_path.read_text())
        for e in cfg.get("carved_funcs", []):
            if isinstance(e.get("name"), str) and isinstance(e.get("size"), int):
                out[e["name"]] = e["size"]
    clusters = ROOT / "progress" / "clusters.json"
    if clusters.is_file():
        data = json.loads(clusters.read_text())
        for cl in data.get("exact_clusters") or []:
            size = cl.get("size")
            if not isinstance(size, int):
                continue
            for m in cl.get("members") or []:
                name = m.get("name") if isinstance(m, dict) else m
                if isinstance(name, str) and name not in out:
                    out[name] = size
    return out


def _carved_matched() -> set[str]:
    cfg = json.loads((ROOT / "compile_config.json").read_text())
    return {e["name"] for e in cfg.get("carved_funcs", []) if e.get("tu")}


_INCLUDE_ASM = re.compile(r'INCLUDE_ASM\("asm/nonmatching",\s*(\w+)\)')
_TEXT_SECTION = re.compile(r'\.text\.([A-Za-z_][\w]*)')


def find_nm_functions() -> list[tuple[str, Path]]:
    matched = _carved_matched()
    found: list[tuple[str, Path]] = []
    seen: set[str] = set()
    for path in sorted(SRC.rglob("*.c")):
        text = path.read_text(errors="replace")
        if "NON_MATCHING" not in text or "INCLUDE_ASM" not in text:
            continue
        names: set[str] = set()
        for block in _BLOCK.findall(text):
            for m in _SECTION_FN.finditer(block):
                names.add(m.group(1))
            names.update(_TEXT_SECTION.findall(block))
        # Macro-generated bodies may only appear as INCLUDE_ASM targets.
        names.update(_INCLUDE_ASM.findall(text))
        for name in sorted(names):
            if name in matched or name in seen:
                continue
            seen.add(name)
            found.append((name, path.relative_to(ROOT)))
    return found


def main() -> int:
    sizes = _sizes_from_clusters_and_config()
    found = find_nm_functions()

    if QUEUE.is_file():
        existing = QUEUE.read_text()
    else:
        existing = (
            "# Permuter queue\n\n"
            "Auto-maintained by `scripts/queue_nm_permuter.py`.\n"
            "One run at a time via `scripts/run_permuter.sh … -j 4`.\n"
            "Rotate after a 15-minute plateau; promote zeros in the next batch.\n\n"
            "## Queued\n\n"
            "| Function | Compiler | Size | Notes | Status |\n"
            "|---|---|---:|---|---|\n"
        )

    # Drop bogus auto-row if present
    existing = re.sub(
        r"^\| `__attribute__`.*\n", "", existing, flags=re.M
    )

    added = []
    for name, rel in sorted(found, key=lambda t: t[0]):
        if f"`{name}`" in existing:
            continue
        size = sizes.get(name)
        size_s = str(size) if size else "—"
        added.append(
            f"| `{name}` | sn-2.95.3-136 | {size_s} | "
            f"complete C in `{rel.as_posix()}` | queued |\n"
        )

    if added:
        if "## Queued" not in existing:
            existing = existing.rstrip() + "\n\n## Queued\n\n"
            existing += (
                "| Function | Compiler | Size | Notes | Status |\n"
                "|---|---|---:|---|---|\n"
            )
        existing = existing.rstrip() + "\n" + "".join(added) + "\n"
        QUEUE.write_text(existing)

    print(f"NON_MATCHING functions with complete C: {len(found)}")
    print(f"newly queued rows: {len(added)}")
    for name, rel in sorted(found):
        print(f"  {name}  ({rel.as_posix()})  size={sizes.get(name, '?')}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
