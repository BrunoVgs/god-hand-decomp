#!/usr/bin/env bash
# permuter_daemon.sh — keep two permuters running at -j 3 from the queue.
#
# - Resumes from saved bests in progress/permuter/<func>/
# - Rotates a run after 15 minutes with no score improvement
# - On score 0: drop progress/inbox/permuter/<func>/ for integrate_inbox.py
#
# Usage: nohup bash scripts/permuter_daemon.sh >> build/permuter_daemon.log 2>&1 &
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"
mkdir -p build progress/inbox/permuter progress/permuter
PIDFILE="$ROOT/build/permuter_daemon.pid"
echo $$ >"$PIDFILE"
STALE_SECS="${PERMUTER_STALE_SECS:-900}"  # 15 minutes
JOBS="${PERMUTER_JOBS:-3}"
SLOTS=2

log() { echo "[$(date -u +%Y-%m-%dT%H:%M:%SZ)] $*"; }

# Parse queue markdown for function names marked queued / parked / active
queue_names() {
    python3 - <<'PY'
import re
from pathlib import Path
text = Path("progress/permuter_queue.md").read_text(errors="ignore")
names = []
for line in text.splitlines():
    if "|" not in line or "`" not in line:
        continue
    low = line.lower()
    if "promoted" in low or "done" in low:
        continue
    m = re.search(r"`([A-Za-z_][A-Za-z0-9_]*)`", line)
    if not m:
        continue
    name = m.group(1)
    # Prefer lines that look like table rows with status
    if "queued" in low or "parked" in low or "active" in low or "stopped" in low or "near" in low:
        names.append(name)
    elif name.startswith("func_") or name[0].isupper():
        names.append(name)
# unique preserve order
seen=set(); out=[]
for n in names:
    if n in seen: continue
    seen.add(n); out.append(n)
print("\n".join(out))
PY
}

best_score() {
    local name="$1" dir="$ROOT/progress/permuter/$name" best=999999999
    [[ -d "$dir" ]] || { echo ""; return; }
    if [[ -f "$dir/best_score.txt" ]]; then
        cat "$dir/best_score.txt"
        return
    fi
    local s
    for s in "$dir"/output/output-*/score.txt "$dir"/output-*/score.txt; do
        [[ -f "$s" ]] || continue
        local sc
        sc=$(cat "$s" 2>/dev/null || true)
        [[ "$sc" =~ ^[0-9]+$ ]] || continue
        if (( sc < best )); then best=$sc; fi
    done
    if (( best < 999999999 )); then echo "$best"; else echo ""; fi
}

case_ready() {
    local name="$1" dir="$ROOT/progress/permuter/$name"
    [[ -f "$dir/base.c" && -f "$dir/compile.sh" && -f "$dir/target.s" ]]
}

# Track running jobs: name|pid|last_best|last_improve_epoch
declare -a RUN_NAME RUN_PID RUN_BEST RUN_IMPROVE

slot_count() { echo "${#RUN_NAME[@]}"; }

reap() {
    local i new_names=() new_pids=() new_bests=() new_imps=()
    for i in "${!RUN_NAME[@]}"; do
        local name="${RUN_NAME[$i]}" pid="${RUN_PID[$i]}"
        if kill -0 "$pid" 2>/dev/null; then
            # update best from live scratch if present
            local sc
            sc=$(best_score "$name")
            local prev="${RUN_BEST[$i]}"
            if [[ -n "$sc" && ( -z "$prev" || "$sc" -lt "$prev" ) ]]; then
                RUN_BEST[$i]="$sc"
                RUN_IMPROVE[$i]=$(date +%s)
                echo "$sc" >"progress/permuter/$name/best_score.txt"
                log "$name improved to $sc"
                if [[ "$sc" == "0" ]]; then
                    log "$name HIT ZERO — inbox drop"
                    deliver_zero "$name"
                    kill "$pid" 2>/dev/null || true
                    wait "$pid" 2>/dev/null || true
                    continue
                fi
            else
                local now age
                now=$(date +%s)
                age=$(( now - ${RUN_IMPROVE[$i]} ))
                if (( age >= STALE_SECS )); then
                    log "$name stale ${age}s — rotate"
                    kill "$pid" 2>/dev/null || true
                    wait "$pid" 2>/dev/null || true
                    # preserve outputs
                    docker exec "${GODHAND_NIX_CONTAINER:-godhand-nix}" bash -lc \
                        "src=/tmp/godhand-permuter/$name; dst=/src/progress/permuter/$name/output; mkdir -p \$dst; [[ -d \$src ]] && cp -a \$src/. \$dst/ || true" \
                        2>/dev/null || true
                    continue
                fi
            fi
            new_names+=("$name"); new_pids+=("$pid")
            new_bests+=("${RUN_BEST[$i]}"); new_imps+=("${RUN_IMPROVE[$i]}")
        else
            log "$name pid $pid exited"
            # check zero on exit
            local sc
            sc=$(best_score "$name")
            if [[ "$sc" == "0" ]]; then
                deliver_zero "$name"
            fi
        fi
    done
    RUN_NAME=("${new_names[@]+"${new_names[@]}"}")
    RUN_PID=("${new_pids[@]+"${new_pids[@]}"}")
    RUN_BEST=("${new_bests[@]+"${new_bests[@]}"}")
    RUN_IMPROVE=("${new_imps[@]+"${new_imps[@]}"}")
}

deliver_zero() {
    local name="$1"
    local src="$ROOT/progress/permuter/$name"
    local dest="$ROOT/progress/inbox/permuter/$name"
    mkdir -p "$dest"
    # Prefer best_source.c, else base.c
    if [[ -f "$src/best_source.c" ]]; then
        cp -a "$src/best_source.c" "$dest/${name}.c"
    elif [[ -f "$src/output/best_source.c" ]]; then
        cp -a "$src/output/best_source.c" "$dest/${name}.c"
    else
        # find a zero-score source
        local z
        z=$(find "$src" -path '*/output-0-*/source.c' 2>/dev/null | head -1 || true)
        if [[ -n "$z" ]]; then cp -a "$z" "$dest/${name}.c"
        else cp -a "$src/base.c" "$dest/${name}.c"
        fi
    fi
    python3 - <<PY
import json
from pathlib import Path
name="$name"
dest=Path("progress/inbox/permuter")/name
meta={
  "name": name,
  "source": f"{name}.c",
  "compiler": "sn-2.95.3-136",
  "flags": ["-O2","-G0","-f=-freorder-blocks"],
  "kind": "match",
  "from": "permuter_daemon",
}
# try size from decomp queue
try:
    q=json.loads(Path("progress/decomp_queue.json").read_text())
    for it in q.get("queue",[]):
        if it.get("name")==name:
            meta["size"]=it.get("size")
            meta["vaddr"]=it.get("address")
            meta["compiler"]=it.get("compiler") or meta["compiler"]
            break
except Exception:
    pass
(dest/"meta.json").write_text(json.dumps(meta, indent=2)+"\n")
(dest/"proof.txt").write_text("permuter score 0\n")
print("inbox", dest)
PY
    # mark promoted in queue
    python3 - <<PY
from pathlib import Path
import re
q=Path("progress/permuter_queue.md")
t=q.read_text()
t=re.sub(rf"(\| `{name}` \|[^|]*)\|[^|]*\|", rf"\1| **promoted→inbox** |", t, count=1)
q.write_text(t)
PY
}

start_one() {
    local name="$1"
    if ! case_ready "$name"; then
        log "skip $name — case not ready"
        return 1
    fi
    # already running?
    local n
    for n in "${RUN_NAME[@]+"${RUN_NAME[@]}"}"; do
        [[ "$n" == "$name" ]] && return 1
    done
    log "start $name -j $JOBS"
    PERMUTER_JOBS="$JOBS" nohup ./scripts/run_permuter.sh "$name" --stop-on-zero --best-only \
        >"build/permuter_${name}.log" 2>&1 &
    local pid=$!
    local sc
    sc=$(best_score "$name")
    RUN_NAME+=("$name")
    RUN_PID+=("$pid")
    RUN_BEST+=("${sc:-999999}")
    RUN_IMPROVE+=("$(date +%s)")
    return 0
}

pick_next() {
    local name running
    while IFS= read -r name; do
        [[ -z "$name" ]] && continue
        running=0
        for n in "${RUN_NAME[@]+"${RUN_NAME[@]}"}"; do
            [[ "$n" == "$name" ]] && running=1
        done
        (( running )) && continue
        # skip if already in inbox done/pass
        [[ -d "progress/inbox/permuter/$name" ]] && continue
        [[ -f "progress/inbox/done/$name/RESULT.txt" ]] && grep -q '^pass' "progress/inbox/done/$name/RESULT.txt" 2>/dev/null && continue
        case_ready "$name" || continue
        echo "$name"
        return 0
    done < <(queue_names)
    return 1
}

log "daemon start pid=$$ jobs=$JOBS slots=$SLOTS stale=${STALE_SECS}s"
trap 'log "daemon stop"; rm -f "$PIDFILE"; for p in "${RUN_PID[@]+"${RUN_PID[@]}"}"; do kill "$p" 2>/dev/null || true; done; exit 0' INT TERM

while true; do
    reap
    while (( $(slot_count) < SLOTS )); do
        next=$(pick_next || true)
        [[ -z "${next:-}" ]] && break
        start_one "$next" || break
    done
    sleep 30
done
