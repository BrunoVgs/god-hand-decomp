#!/usr/bin/env python3
"""Split a scratch file into a matched TU and an NM file.

    split_nm.py SCRATCH MATCHED_OUT NM_OUT "NM comment" FN [FN...]

FNs listed go to NM_OUT under #ifdef NON_MATCHING with INCLUDE_ASM fallbacks;
everything else stays in MATCHED_OUT. The shared head (types, externs) is
copied into both.
"""
import re
import sys

src, matched_out, nm_out, comment = sys.argv[1:5]
nm_fns = sys.argv[5:]
s = open(src).read()
parts = re.split(r'(?=__attribute__\(\(section\("\.text\.)', s)
head, fns = parts[0], parts[1:]
by_name = {re.search(r'\.text\.(\w+)', p).group(1): p for p in fns}
missing = [f for f in nm_fns if f not in by_name]
if missing:
    sys.exit("not in scratch: %s" % " ".join(missing))

keep = [p for p in fns if re.search(r'\.text\.(\w+)', p).group(1) not in nm_fns]
open(matched_out, "w").write(head + "".join(keep).rstrip() + "\n")

head_body = head.split("\n", 1)[1] if head.startswith("/*") else head
nm = "/* NM, not registered. %s */\n#include \"include_asm.h\"\n\n#ifdef NON_MATCHING\n" % comment
nm += head_body + "".join(by_name[f] for f in nm_fns).rstrip() + "\n\n#else\n\n"
nm += "".join('INCLUDE_ASM("asm/nonmatching", %s);\n' % f for f in nm_fns)
nm += "\n#endif\n"
open(nm_out, "w").write(nm)
