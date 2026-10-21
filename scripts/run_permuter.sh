#!/usr/bin/env bash
# Run decomp-permuter for one prepared case inside container /tmp.
# Does not call compile.py and does not take the build lock.
#
#   ./scripts/run_permuter.sh func_001746B0
#   ./scripts/run_permuter.sh func_001746B0 --stop-on-zero --best-only
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
name="${1:?function name}"
shift
case_dir="$ROOT/progress/permuter/$name"
if [[ ! -f "$case_dir/compile.sh" || ! -f "$case_dir/base.c" || ! -f "$case_dir/target.s" ]]; then
    echo "run_permuter: missing case files in progress/permuter/$name" >&2
    echo "create them with: python3 scripts/permuter_case.py $name --compiler COMPILER" >&2
    exit 2
fi

# Default 3 cores; run at most two permuters (2×3) so compile.py still has headroom.
# Override with PERMUTER_JOBS or a trailing -j N (argparse last-wins).
cores="${PERMUTER_JOBS:-3}"
# Drop a leading -j N from "$@" so callers can pass --stop-on-zero -j 3 cleanly;
# we always inject -j "$cores" first then append the rest (last -j wins if present).
exec "$ROOT/scripts/container_run.sh" bash -lc '
    set -euo pipefail
    name="$1"
    cores="$2"
    shift 2
    src="/src/progress/permuter/$name"
    scratch="/tmp/godhand-permuter/$name"
    rm -rf "$scratch"
    mkdir -p "$scratch"
    cp -a "$src/." "$scratch/"
    $( [ "$(uname -m)" = x86_64 ] || echo qemu-i386 ) /src/compiler/linux/ee/gcc/bin/ee-as \
        -EL -mips3 -mcpu=5900 -mabi=eabi -G0 \
        -I/src/include -I/src/build/asm \
        "$scratch/target.s" -o "$scratch/target.o"
    cd "$scratch"
    /src/.venv/bin/python /src/tools/decomp-permuter/permuter.py . -j "$cores" "$@"
    mkdir -p "$src/output"
    cp -a "$scratch/." "$src/output/"
' bash "$name" "$cores" "$@"
