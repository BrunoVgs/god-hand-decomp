#!/usr/bin/env python3
"""Create a decomp-permuter case for one near-miss function.

The case lives in progress/permuter/<function>/ and is copied into the
container's /tmp by scripts/run_permuter.sh. It does not call compile.py
and does not take the build lock.

Usage:
    python3 scripts/permuter_case.py func_001746B0 --compiler sn-2.95.3-136 --source candidate.c
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts.carver import _eeas_compat_registers

ASM = ROOT / "asm" / "cod" / "000000.s"
GLABEL = re.compile(r"^glabel\s+(\S+)")
ENDLABEL = re.compile(r"^endlabel\s+(\S+)")


def extract_body(name: str) -> str:
    carved = ROOT / "build" / "asm" / "nonmatching" / f"{name}.s"
    if carved.is_file():
        return carved.read_text()
    lines: list[str] = []
    capturing = False
    with ASM.open() as handle:
        for line in handle:
            label = GLABEL.match(line)
            if label and label.group(1) == name:
                capturing = True
                lines.append(line)
                continue
            if capturing:
                lines.append(line)
                if ENDLABEL.match(line) and ENDLABEL.match(line).group(1) == name:
                    break
    if not lines:
        raise SystemExit(f"permuter_case: {name} not found in {ASM}")
    wrapped = (
        '.include "labels.inc"\n\n.set noat\n.set noreorder\n\n'
        f'.section .text.{name}, "ax"\n.align 3\n'
        + _eeas_compat_registers("".join(lines))
    )
    return wrapped


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("function")
    parser.add_argument("--compiler", required=True)
    parser.add_argument("--source", type=Path, default=None,
                        help="candidate C file; copied to base.c")
    parser.add_argument("--drop-reorder", action="store_true",
                        help="drop -freorder-blocks from the compile line")
    args = parser.parse_args()
    case = ROOT / "progress" / "permuter" / args.function
    case.mkdir(parents=True, exist_ok=True)
    (case / "target.s").write_text(extract_body(args.function))
    if args.source is not None:
        (case / "base.c").write_text(args.source.read_text())
    elif not (case / "base.c").exists():
        (case / "base.c").write_text(
            f"void {args.function}(void) {{\n}}\n"
        )
    flags = ["-O2", "-G0"]
    if not args.drop_reorder:
        flags.append("-f=-freorder-blocks")
    flag_text = " ".join(flags)
    (case / "compile.sh").write_text(
        "#!/bin/bash\n"
        "set -euo pipefail\n"
        "exec /src/.venv/bin/python /src/scripts/ee-cc-wrap.py -c "
        f"--compiler={args.compiler} -x c {flag_text} "
        "-I/src/include -I/src/include/sce -I/src/build/asm "
        '"$@"\n'
    )
    (case / "compile.sh").chmod(0o755)
    (case / "settings.toml").write_text(
        'compiler = "gcc"\n'
        'objdump_command = "mipsel-linux-gnu-objdump -drz"\n'
    )
    print(case.relative_to(ROOT))


if __name__ == "__main__":
    main()
