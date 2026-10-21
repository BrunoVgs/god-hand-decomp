#!/usr/bin/env python3
"""Report contiguous byte-difference ranges between two ELF files."""

from __future__ import annotations

import argparse
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("actual", type=Path)
    parser.add_argument("expected", type=Path)
    parser.add_argument("--text-offset", type=lambda value: int(value, 0))
    parser.add_argument("--text-address", type=lambda value: int(value, 0))
    args = parser.parse_args()

    actual = args.actual.read_bytes()
    expected = args.expected.read_bytes()
    limit = min(len(actual), len(expected))
    ranges: list[tuple[int, int]] = []
    start: int | None = None

    for offset in range(limit):
        if actual[offset] != expected[offset]:
            if start is None:
                start = offset
        elif start is not None:
            ranges.append((start, offset))
            start = None
    if start is not None:
        ranges.append((start, limit))
    if len(actual) != len(expected):
        ranges.append((limit, max(len(actual), len(expected))))

    for start, end in ranges:
        location = ""
        if (
            args.text_offset is not None
            and args.text_address is not None
            and start >= args.text_offset
        ):
            address = args.text_address + start - args.text_offset
            location = f" vaddr=0x{address:08X}"
        print(
            f"offset=0x{start:08X}..0x{end:08X} "
            f"size={end - start}{location}"
        )
    print(f"{len(ranges)} differing range(s)")
    return 1 if ranges else 0


if __name__ == "__main__":
    raise SystemExit(main())
