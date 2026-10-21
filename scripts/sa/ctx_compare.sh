#!/bin/bash
# inside container: compare drafts with and without src context
cd /src
for fn in "$@"; do
  for mode in "--no-src-context" ""; do
    out=$(/src/.venv/bin/python scripts/m2c_draft.py $fn $mode 2>&1)
    q=$(printf '%s\n' "$out" | grep -c '?')
    ext=$(printf '%s\n' "$out" | grep -E '/\* extern \*/|^extern ' | grep -c '?')
    err=$(printf '%s\n' "$out" | grep -c 'M2C_ERROR')
    fail=$(printf '%s\n' "$out" | grep -c 'Decompilation failure')
    printf '%s\t%s\t%s\t%s\t%s\t%s\n' "$fn" "${mode:-src}" "$q" "$ext" "$err" "$fail"
  done
done
