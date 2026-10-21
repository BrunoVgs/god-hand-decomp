"""List TUs that include a header and also declare one of the given symbols locally.

usage: python3 scripts/sa/hdr_conflicts.py godhand/X.h SYM [SYM...]
Also follows headers that include X.h one level up.
"""
import pathlib
import re
import sys

hdr = sys.argv[1]
syms = sys.argv[2:]
root = pathlib.Path(".")
inc_re = re.compile(r'#include\s+"([^"]+)"')

includers = {hdr}
for h in pathlib.Path("include").rglob("*.h"):
    rel = str(h.relative_to("include"))
    if hdr in inc_re.findall(h.read_text(errors="replace")):
        includers.add(rel)

for src in sorted(list(root.glob("src/**/*.c")) + list(root.glob("src/**/*.cc"))):
    text = src.read_text(errors="replace")
    incs = set(inc_re.findall(text))
    if not incs & includers:
        continue
    for sym in syms:
        for line in text.splitlines():
            if re.search(r"\b%s\b" % re.escape(sym), line) and (
                line.lstrip().startswith(("extern", "typedef", "struct")) or re.match(r"^\w[\w\s\*]*\b%s\s*\(" % re.escape(sym), line)
            ):
                print(f"{src}: {sym}: {line.strip()}")
