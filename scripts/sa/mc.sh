#!/bin/sh
# Compact match summary across compilers: mc.sh FILE FN... (scratch helper)
f=$1; shift
for c in "cygnus-2.96" "cygnus-2.96 --drop-reorder" "sn-2.95.3-136"; do
  r=$(python3 scripts/match_check.py "$f" "$@" --compiler $c 2>&1 | grep -E '^(FAIL|MATCH)' | grep -v 'words vs' | sed -E 's/ \(([0-9]+) insns.*//; s/ differing insns//; s/func_00//' | tr '\n' ' ')
  echo "== $c: $r"
done
