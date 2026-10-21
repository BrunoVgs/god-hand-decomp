#!/usr/bin/env python3
"""Append real wall-clock rows to progress/batch_log.md.

    python3 scripts/batch_log.py start FUNCTION
    python3 scripts/batch_log.py finish FUNCTION --size 124 --status matched --attempts 2
    python3 scripts/batch_log.py batch --reseed 28.6 --score 51.2

``start`` must be called *before* the first compile attempt for that
function. ``finish`` writes elapsed seconds from that start. Back-to-back
start/finish (no real work) is rejected so the log cannot fill with 0.0s.

Start times live in build/batch_timing.json.
"""

from __future__ import annotations

import argparse
import json
import sys
import time
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LOG = ROOT / "progress" / "batch_log.md"
STATE = ROOT / "build" / "batch_timing.json"

# Reject finish that is clearly start+finish with no work in between.
# A real --single-file / scratch compile is well above this.
_MIN_SECONDS = 0.25


def _utc() -> str:
    return datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def _load() -> dict:
    if not STATE.is_file():
        return {}
    return json.loads(STATE.read_text())


def _save(state: dict) -> None:
    STATE.parent.mkdir(parents=True, exist_ok=True)
    STATE.write_text(json.dumps(state, indent=2) + "\n")


def _append(line: str) -> None:
    text = LOG.read_text() if LOG.is_file() else (
        "# Batch log\n\n"
        "| utc | function | size | status | attempts | seconds |\n"
        "| --- | --- | ---: | --- | ---: | ---: |\n"
    )
    if not text.endswith("\n"):
        text += "\n"
    LOG.write_text(text + line + "\n")


def start(function: str) -> int:
    state = _load()
    if function in state:
        print(
            f"batch_log: restarting timer for {function} "
            f"(previous start was open)",
            file=sys.stderr,
        )
    state[function] = time.time()
    _save(state)
    return 0


def finish(
    function: str,
    size: int,
    status: str,
    attempts: int,
    *,
    allow_short: bool = False,
    m2c: str | None = None,
    area: str | None = None,
) -> int:
    state = _load()
    started = state.pop(function, None)
    if started is None:
        print(
            f"batch_log: no start time for {function} — call "
            f"`batch_log.py start {function}` before the first attempt",
            file=sys.stderr,
        )
        return 2
    _save(state)
    seconds = time.time() - started
    if seconds < _MIN_SECONDS and not allow_short:
        print(
            f"batch_log: refusing finish for {function}: elapsed "
            f"{seconds:.3f}s < {_MIN_SECONDS}s. Timer must bracket real "
            f"compile work (start before attempts, finish after). "
            f"Pass --allow-short only for intentional micro-timings.",
            file=sys.stderr,
        )
        # Put the start back so a later real finish can still work.
        state = _load()
        state[function] = started
        _save(state)
        return 3
    row = f"| {_utc()} | {function} | {size} | {status} | {attempts} | {seconds:.1f} |"
    if m2c is not None:
        row += f" {m2c} | {area or '-'} |"
    _append(row)
    return 0


def batch(reseed: float, score: float, note: str | None = None) -> int:
    row = f"| {_utc()} | BATCH | - | batch | - | reseed {reseed:.1f}; score {score:.1f} |"
    if note is not None:
        row += f" - | {note} |"
    _append(row)
    return 0


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="cmd", required=True)

    p_start = sub.add_parser("start")
    p_start.add_argument("function")

    p_finish = sub.add_parser("finish")
    p_finish.add_argument("function")
    p_finish.add_argument("--size", type=int, required=True)
    p_finish.add_argument(
        "--status", required=True, choices=("matched", "non-matching", "hard-tail", "skipped")
    )
    p_finish.add_argument("--attempts", type=int, required=True)
    p_finish.add_argument(
        "--allow-short",
        action="store_true",
        help="Allow finish with elapsed < 0.25s (default: reject)",
    )

    p_finish.add_argument("--m2c", choices=("yes", "no"))
    p_finish.add_argument("--area")

    p_batch = sub.add_parser("batch")
    p_batch.add_argument("--note")
    p_batch.add_argument("--reseed", type=float, required=True)
    p_batch.add_argument("--score", type=float, required=True)

    args = parser.parse_args(argv)
    if args.cmd == "start":
        return start(args.function)
    if args.cmd == "finish":
        return finish(
            args.function,
            args.size,
            args.status,
            args.attempts,
            allow_short=args.allow_short,
            m2c=args.m2c,
            area=args.area,
        )
    if args.cmd == "batch":
        return batch(args.reseed, args.score, args.note)
    return 2


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
