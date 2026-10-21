#!/usr/bin/env python3
"""Print cleaned listings: lst.py FN [FN...] (scratch helper)."""
import re
import sys

lines = open("asm/cod/000000.s").read().split("\n")
idx = {}
for i, l in enumerate(lines):
    m = re.match(r"glabel (\w+)$", l)
    if m:
        idx[m.group(1)] = i
for fn in sys.argv[1:]:
    i = idx.get(fn)
    if i is None:
        print("?? %s" % fn)
        continue
    while True:
        l = re.sub(r"^\s*/\* [0-9A-F]+ [0-9A-F]+ [0-9A-F]+ \*/\s*", "", lines[i])
        if l.strip():
            print(l)
        if lines[i].startswith("endlabel %s" % fn):
            break
        i += 1
