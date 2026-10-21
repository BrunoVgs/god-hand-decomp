#!/usr/bin/env bash
# Reseed after registering a batch, then check both retail hashes.
# Usage: scripts/sa_reseed.sh ANCHOR_FUNCTION   (exit 0 only if both hashes match)
set -uo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"
ELF_SHA=1742f95bef65bdb2aa57b7a77df4ac7619a092e9646e1ea325bc32ec8a64f3cd
OV_SHA=ea59932301345e48add7a3eff029b7d0d0138fff1abc67569467880678c653c1
t0=$(date +%s)
./scripts/container_run.sh python3 compile.py --reseed-expected "$1" > build/sa_reseed.log 2>&1
rc=$?
dt=$(( $(date +%s) - t0 ))
elf=$(shasum -a 256 build/SLUS_215.03.elf 2>/dev/null | cut -d' ' -f1)
ov=$(shasum -a 256 build/rel/r207.rel 2>/dev/null | cut -d' ' -f1)
e=BAD; o=BAD
[[ "$elf" == "$ELF_SHA" ]] && e=OK
[[ "$ov" == "$OV_SHA" ]] && o=OK
echo "reseed rc=$rc ${dt}s elf=$e overlay=$o"
[[ $rc == 0 && $e == OK && $o == OK ]]
