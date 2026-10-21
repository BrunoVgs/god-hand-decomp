#!/bin/zsh
# nc.sh FN [compiler-args...]: start sa_try timer, show best near-clone C, its diff vs FN, and FN's listing.
cd "$(dirname $0)/../.."
fn=$1; shift
python3 scripts/sa_try.py start $fn >/dev/null
python3 scripts/near_clone.py $fn --top 1 | head -2
f=build/sa/clone_$fn.c
awk '/near_clone: from/,0' $f
python3 scripts/match_check.py $f $fn "$@" 2>&1 | grep -cE "^!!" | sed 's/^/diff lines: /'
python3 scripts/sa/lst.py $fn
