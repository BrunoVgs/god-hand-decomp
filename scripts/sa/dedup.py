"""dedup.py FILE HEADER [--before MARKER]: remove from FILE's prelude every line that also appears in HEADER
(exact stripped match of extern/typedef-struct blocks), then insert #include "HEADER" at the first removed spot."""
import re, sys
f, hdr = sys.argv[1], sys.argv[2]
s = open(f).read()
h = open("include/" + hdr).read()
cut = s.index("__attribute__((section")
pre, body = s[:cut], s[cut:]
# whole typedef blocks whose name is defined in header
names = set(re.findall(r"\}\s*(\w+)\s*;", h)) | set(re.findall(r"^struct (\w+) \{", h, re.M))
out_pre = pre
first = None
for m in list(re.finditer(r"(?ms)^(typedef struct[^{;]*\{.*?^\}\s*(\w+)\s*;\n|^struct (\w+) \{.*?^\};\n|^typedef struct (\w+) \w+;\n)", pre)):
    nm = m.group(2) or m.group(3) or m.group(4)
    if nm in names:
        pos = out_pre.find(m.group(1))
        first = pos if first is None else min(first, pos)
        out_pre = out_pre.replace(m.group(1), "\x00", 1)
hdecl = {re.sub(r"\s+", " ", re.sub(r"/\*.*?\*/", "", l)).strip() for l in h.splitlines() if l.startswith("extern")}
# also split multi-decls in header like "extern volatile long A, B;"
syms = {}
for l in h.splitlines():
    if l.startswith("extern"):
        for nm in re.findall(r"(\w+)\s*(?:\[\]|\()", l) + re.findall(r"(\w+)\s*[,;]", l):
            syms[nm] = l
lines = out_pre.split("\n")
res = []
for i, l in enumerate(lines):
    norm = re.sub(r"\s+", " ", re.sub(r"/\*.*?\*/", "", l)).strip()
    if l.startswith("extern") and norm in hdecl:
        res.append("\x00")
        continue
    res.append(l)
out_pre = "\n".join(res)
idx = out_pre.find("\x00")
if idx < 0:
    sys.exit(f"{f}: nothing removed")
out_pre = out_pre[:idx] + f'#include "{hdr}"\n' + out_pre[idx:]
out_pre = re.sub(r"\x00\n?", "", out_pre)
out_pre = re.sub(r"\n{3,}", "\n\n", out_pre)
open(f, "w").write(out_pre + body)
print("ok", f)
