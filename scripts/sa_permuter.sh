#!/usr/bin/env bash
# One decomp-permuter run at a time, lowest CPU priority, -j 8.
#   scripts/sa_permuter.sh start NAME [MINUTES]   (case must exist: permuter_case.py)
#   scripts/sa_permuter.sh status
#   scripts/sa_permuter.sh stop                   (kills every permuter in godhand-nix)
set -uo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PIDF="$ROOT/build/sa_permuter.pid"
NAMEF="$ROOT/build/sa_permuter.name"
# The container has no pgrep/pkill; scan /proc instead.
perm_pids() {
    docker exec godhand-nix bash -c 'for p in /proc/[0-9]*; do [ "${p#/proc/}" = "$$" ] && continue; c=$(tr "\0" " " < "$p/cmdline" 2>/dev/null) || continue; case "$c" in *permuter.py*|*godhand-permuter*) echo "${p#/proc/}";; esac; done' 2>/dev/null
}
running() { [[ -n "$(perm_pids)" ]]; }
case "${1:-}" in
start)
    name="${2:?name}"; mins="${3:-30}"
    if running; then echo "sa_permuter: already running ($(cat "$NAMEF" 2>/dev/null))"; exit 1; fi
    [[ -f "$ROOT/progress/permuter/$name/base.c" ]] || { echo "no case for $name"; exit 2; }
    echo "$name" > "$NAMEF"
    python3 - "$ROOT" "$name" "$mins" "$PIDF" <<'PY'
import subprocess, sys
root, name, mins, pidf = sys.argv[1:5]
inner = f'''set -e
src=/src/progress/permuter/{name}; scratch=/tmp/godhand-permuter/{name}
rm -rf "$scratch"; mkdir -p "$scratch"; cp -a "$src/." "$scratch/"
qemu-i386 /src/compiler/linux/ee/gcc/bin/ee-as -EL -mips3 -mcpu=5900 -mabi=eabi -G0 \
  -I/src/include -I/src/build/asm "$scratch/target.s" -o "$scratch/target.o"
cd "$scratch"
timeout {int(mins)*60} nice -n 19 /src/.venv/bin/python /src/tools/decomp-permuter/permuter.py . -j 8 --stop-on-zero || true
mkdir -p "$src/output"; cp -a "$scratch/." "$src/output/"
'''
log = open(f"{root}/build/sa_permuter.log", "w")
p = subprocess.Popen([f"{root}/scripts/container_run.sh", "bash", "-lc", inner],
                     cwd=root, stdout=log, stderr=subprocess.STDOUT, start_new_session=True)
open(pidf, "w").write(f"{p.pid}\n")
print(f"sa_permuter: started {name} pid {p.pid} ({mins} min cap)")
PY
    ;;
status)
    if running; then echo "running: $(cat "$NAMEF" 2>/dev/null)"; else echo "idle (last: $(cat "$NAMEF" 2>/dev/null))"; fi
    grep -aoE "(base score|New best|score) [^\r]*" "$ROOT/build/sa_permuter.log" 2>/dev/null | tail -2
    ;;
stop)
    pids="$(perm_pids | tr '\n' ' ')"
    [[ -n "$pids" ]] && docker exec godhand-nix kill $pids 2>/dev/null
    [[ -f "$PIDF" ]] && kill "$(cat "$PIDF")" 2>/dev/null
    sleep 1
    if running; then echo "sa_permuter: still running!"; exit 1; fi
    echo "sa_permuter: no permuter processes in godhand-nix"
    ;;
*) sed -n 2,6p "$0"; exit 2 ;;
esac
