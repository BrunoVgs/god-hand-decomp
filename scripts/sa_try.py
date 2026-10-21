#!/usr/bin/env python3
"""Track match attempts per function and say when to park. Matching aid only; not part of the build.

    python3 scripts/sa_try.py start FN                 # mark the start (before drafting)
    python3 scripts/sa_try.py run FILE FN [match_check args...]
    python3 scripts/sa_try.py time FN                  # wall-clock seconds since start, for batch_log

`run` calls scripts/match_check.py, records the differing-instruction count
(plus the word-count gap) as this attempt's score in build/sa/attempts/FN.log,
and prints the advice:

    MATCH       done
    CONTINUE    keep iterating
    PARK        attempt >= 3 and the best score is not at least 25% below attempt 1:
                save complete C as NON_MATCHING (or log hard-tail) and move on
    NEAR-MISS   parked with best score <= 5: also queue it for the permuter
    STOP        attempt 6 reached
"""
from __future__ import annotations

import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LOGDIR = ROOT / "build" / "sa" / "attempts"
PARK_AT = 3
MAX_ATTEMPTS = 6
MIN_GAIN = 0.25
NEAR_MISS = 5


def log_path(fn: str) -> Path:
    LOGDIR.mkdir(parents=True, exist_ok=True)
    return LOGDIR / f"{fn}.log"


def read(fn: str) -> tuple[float | None, list[int]]:
    p = log_path(fn)
    start, scores = None, []
    if p.exists():
        for line in p.read_text().splitlines():
            kind, ts, *rest = line.split()
            if kind == "start":
                start, scores = float(ts), []
            elif kind == "try":
                scores.append(int(rest[0]))
    return start, scores


def score(out: str, fn: str) -> int | None:
    if re.search(rf"^MATCH {re.escape(fn)}\b", out, re.M):
        return 0
    if re.search(r"COMPILE-FAIL|cc1 failed", out):
        return None
    diff = re.search(rf"^FAIL {re.escape(fn)}: (\d+) differing insns", out, re.M)
    words = re.search(rf"^FAIL {re.escape(fn)}: (\d+) words vs retail (\d+)", out, re.M)
    s = int(diff.group(1)) if diff else 0
    if words:
        s += abs(int(words.group(1)) - int(words.group(2)))
    if not diff and not words:
        reloc = re.search(rf"^FAIL {re.escape(fn)}.*", out, re.M)
        return 1 if reloc else None
    return s


def advice(scores: list[int]) -> str:
    n, best = len(scores), min(scores)
    if best == 0 and scores[-1] == 0:
        return "MATCH"
    if n >= MAX_ATTEMPTS:
        return "STOP" + (" (near-miss: queue for permuter)" if best <= NEAR_MISS else "")
    if n >= PARK_AT and best > scores[0] * (1 - MIN_GAIN):
        return "NEAR-MISS" if best <= NEAR_MISS else "PARK"
    return "CONTINUE"


def main() -> int:
    if len(sys.argv) < 3 or sys.argv[1] not in ("start", "run", "time"):
        print(__doc__)
        return 2
    cmd, fn = sys.argv[1], sys.argv[2]
    if cmd == "start":
        with log_path(fn).open("a") as f:
            f.write(f"start {time.time():.0f}\n")
        return 0
    if cmd == "time":
        start, _ = read(fn)
        print(int(time.time() - start) if start else "?")
        return 0
    src, fn = sys.argv[2], sys.argv[3]
    start, _ = read(fn)
    if start is None:
        with log_path(fn).open("a") as f:
            f.write(f"start {time.time():.0f}\n")
    r = subprocess.run([sys.executable, str(ROOT / "scripts" / "match_check.py"), src, fn, *sys.argv[4:]],
                       capture_output=True, text=True)
    out = r.stdout + r.stderr
    s = score(out, fn)
    if s is None:
        sys.stdout.write(out[-2500:])
        print(f"sa_try: {fn}: compile failed (not counted as an attempt)")
        return 1
    with log_path(fn).open("a") as f:
        f.write(f"try {time.time():.0f} {s}\n")
    start, scores = read(fn)
    if s:
        # Local (decomp-lab): the FIRST differing stretch is the one to fix, so show the head of the diff.
        lines = [l for l in out.splitlines() if l.strip()]
        text = "\n".join(lines)
        if len(text) > 2500:
            text = text[:2300] + f"\n... ({len(lines)} lines in all, fix the first stretch above first)"
        sys.stdout.write(text + "\n")
    elapsed = int(time.time() - start) if start else 0
    print(f"sa_try: {fn}: attempt {len(scores)} score {s} (best {min(scores)}, first {scores[0]}), "
          f"{elapsed}s -> {advice(scores)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
