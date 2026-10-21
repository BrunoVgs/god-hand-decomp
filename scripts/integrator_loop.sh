#!/usr/bin/env bash
# Drain progress/inbox continuously while work is waiting; idle-poll for 10+.
# PROGRESS.md / score_nm only every 10 integrate passes — never per pass.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"
mkdir -p build
echo $$ > build/integrator_loop.pid
log() { echo "[$(date -u +%Y-%m-%dT%H:%M:%SZ)] $*"; }

LAST_PROGRESS_COUNT=0
[[ -f progress/integrate_count.txt ]] && LAST_PROGRESS_COUNT=$(cat progress/integrate_count.txt)

waiting_count() {
  find progress/inbox/worker-* progress/inbox/permuter -mindepth 1 -maxdepth 1 -type d 2>/dev/null | wc -l | tr -d ' '
}

ensure_daemon() {
  if [[ -f build/permuter_daemon.pid ]] && kill -0 "$(cat build/permuter_daemon.pid)" 2>/dev/null; then
    return 0
  fi
  log "permuter_daemon dead — restart"
  # detach so loop death doesn't kill daemon
  python3 - <<'PY'
import os, subprocess
from pathlib import Path
root = Path(".")
lf = open("build/permuter_daemon.log", "a")
p = subprocess.Popen(
    ["bash", "scripts/permuter_daemon.sh"],
    cwd=str(root.resolve()),
    stdin=subprocess.DEVNULL,
    stdout=lf,
    stderr=subprocess.STDOUT,
    start_new_session=True,
    close_fds=True,
)
Path("build/permuter_daemon.pid").write_text(f"{p.pid}\n")
print(p.pid)
PY
}

run_integrate() {
  if [[ -f build/integrate_inbox.pid ]] && kill -0 "$(cat build/integrate_inbox.pid)" 2>/dev/null; then
    log "integrate already running pid=$(cat build/integrate_inbox.pid)"
    return 0
  fi
  log "integrate start (waiting=$(waiting_count))"
  INTEGRATE_JOBS="${INTEGRATE_JOBS:-8}" PYTHONUNBUFFERED=1 \
    python3 scripts/integrate_inbox.py >> build/integrate_inbox_latest.log 2>&1 \
    || log "integrate_inbox FAILED"
}

maybe_progress() {
  local count
  count=$(cat progress/integrate_count.txt 2>/dev/null || echo 0)
  if (( count >= LAST_PROGRESS_COUNT + 10 )); then
    log "PROGRESS entry at integrate #$count (score_nm once here)"
    # Refresh report + optional NM score only at PROGRESS cadence
    ./scripts/container_run.sh bash -lc \
      'tools/objdiff-cli report generate -p . -o progress/report.json -f json-pretty' \
      >> build/report_refresh.log 2>&1 || true
    if [[ -x scripts/score_nm.sh ]]; then
      bash scripts/score_nm.sh >> build/score_nm.log 2>&1 || true
    fi
    python3 scripts/append_progress.py --batch "$count" \
      --matched-bytes-delta 0 --matched-fns-delta 0 --hours 0.25 \
      --permuter-queued 0 --permuter-promoted 0 || true
    LAST_PROGRESS_COUNT=$count
  fi
}

while true; do
  ensure_daemon
  waiting=$(waiting_count)
  log "inbox waiting=$waiting"

  if (( waiting >= 10 )); then
    # Drain back-to-back until empty (or only incompletes remain).
    while true; do
      waiting=$(waiting_count)
      if (( waiting == 0 )); then
        log "inbox drained"
        break
      fi
      before=$waiting
      run_integrate
      maybe_progress
      waiting=$(waiting_count)
      if (( waiting >= before )); then
        # No progress (all incomplete / lock contention) — back off
        log "no drain progress (before=$before after=$waiting); backoff 30s"
        sleep 30
        break
      fi
    done
  else
    # Idle: poll often; only integrate again once 10+ arrive
    sleep 30
  fi
done
