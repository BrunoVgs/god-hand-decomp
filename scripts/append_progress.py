#!/usr/bin/env python3
"""Append a timestamped progress entry to progress/PROGRESS.md.

    python3 scripts/append_progress.py --batch N \\
        --matched-bytes-delta B --matched-fns-delta F \\
        --hours H --permuter-queued Q --permuter-promoted P \\
        [--nm-bytes B]

Reads progress/report.json for linked % and data %.
If --nm-bytes omitted, leaves NON_MATCHING bytes as \"(run score_nm.sh)\".
"""

from __future__ import annotations

import argparse
import json
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REPORT = ROOT / "progress" / "report.json"
OUT = ROOT / "progress" / "PROGRESS.md"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--batch", type=int, required=True)
    ap.add_argument("--matched-bytes-delta", type=int, required=True)
    ap.add_argument("--matched-fns-delta", type=int, required=True)
    ap.add_argument("--hours", type=float, required=True)
    ap.add_argument("--permuter-queued", type=int, required=True)
    ap.add_argument("--permuter-promoted", type=int, required=True)
    ap.add_argument("--nm-bytes", type=int, default=None,
                    help="Override; default reads progress/score_nm_summary.json")
    args = ap.parse_args()

    m = json.loads(REPORT.read_text())["measures"]
    matched = int(m["matched_code"])
    total = int(m["total_code"])
    linked_pct = 100.0 * matched / total if total else 0.0
    data_pct = float(m["matched_data_percent"])
    nm = args.nm_bytes
    summary_path = ROOT / "progress" / "score_nm_summary.json"
    if nm is None and summary_path.is_file():
        s = json.loads(summary_path.read_text())
        nm = int(s.get("non_matching_bytes", 0))
        decomp = int(s.get("decompiled_bytes", matched + nm))
        decomp_pct = float(s.get("nm_fuzzy_match_percent", 100.0 * decomp / total))
        decomp_s = f"{nm} B NON_MATCHING (measured via score_nm.sh)"
        decomp_pct_s = f"{decomp_pct:.4f}% ({decomp} / {total})"
    elif nm is None:
        decomp_s = "(run score_nm.sh for measured NON_MATCHING bytes)"
        decomp_pct_s = "n/a"
    else:
        decomp = matched + nm
        decomp_pct = 100.0 * decomp / total if total else 0.0
        decomp_s = f"{nm} B NON_MATCHING"
        decomp_pct_s = f"{decomp_pct:.4f}% ({decomp} / {total})"
    bph = args.matched_bytes_delta / args.hours if args.hours > 0 else 0.0
    utc = datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")
    entry = (
        f"\n## Batch {args.batch} — {utc}\n\n"
        f"- **% fully linked:** {linked_pct:.4f}% "
        f"({matched} / {total} code bytes)\n"
        f"- **% decompiled:** {decomp_pct_s}; {decomp_s}\n"
        f"- **Data %:** {data_pct:.4f}%\n"
        f"- **Since last entry:** +{args.matched_bytes_delta} B, "
        f"+{args.matched_fns_delta} functions; "
        f"{bph:.0f} B/h over {args.hours:.2f} h\n"
        f"- **Permuter:** {args.permuter_queued} queued; "
        f"{args.permuter_promoted} promoted since last entry\n"
    )
    prev = OUT.read_text() if OUT.is_file() else "# Matching progress\n"
    if not prev.endswith("\n"):
        prev += "\n"
    OUT.write_text(prev + entry)
    print(entry)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
