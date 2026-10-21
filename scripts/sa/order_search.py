#!/usr/bin/env python3
"""order_search.py SRC.c FUNC [match_check compiler args...] [--max N]

SRC.c holds FUNC with one or more blocks of independent statements marked
    /*ORDER*/            (own line)
    stmt;                (one statement per line)
    /*END*/
Every combination of block orderings (capped by --max, default 2000) is emitted as a copy of FUNC
named FUNC__vN in a single TU, compiled once, and compared word-for-word (after relocations)
with retail FUNC. Prints the best orderings; writes the best source to build/sa/order_best_FUNC.c.
"""
import itertools
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
(ROOT / "build" / "sa").mkdir(parents=True, exist_ok=True)
sys.path.insert(0, str(ROOT / "scripts"))
import match_check as mc  # noqa: E402

argv = sys.argv[1:]
cap = 2000
if "--max" in argv:
    i = argv.index("--max")
    cap = int(argv[i + 1])
    del argv[i:i + 2]
src, func, ccargs = Path(argv[0]), argv[1], argv[2:]
text = src.read_text()
start = text.index(f'__attribute__((section(".text.{func}")))')
brace = text.index("{", text.index(func + "(", start))
depth = 0
for end in range(brace, len(text)):
    depth += {"{": 1, "}": -1}.get(text[end], 0)
    if depth == 0:
        break
fbody = text[start:end + 1]
prefix, suffix = text[:start], text[end + 1:]

blocks = []
parts = re.split(r"^[ \t]*/\*ORDER\*/[ \t]*\n(.*?)^[ \t]*/\*END\*/[ \t]*\n", fbody, flags=re.M | re.S)
skeleton = parts[0::2]
for b in parts[1::2]:
    blocks.append([ln for ln in b.splitlines(keepends=True) if ln.strip()])
perms = [list(itertools.permutations(b)) for b in blocks]
combos = itertools.islice(itertools.product(*perms), cap)

variants = []
out = [prefix]
for n, combo in enumerate(combos):
    body = skeleton[0]
    for k, order in enumerate(combo):
        body += "".join(order) + skeleton[k + 1]
    body = body.replace(f".text.{func}", f".text.{func}__v{n}", 1)
    body = re.sub(rf"\b{re.escape(func)}\s*\(", f"{func}__v{n}(", body, count=1)
    variants.append(combo)
    out.append(body + "\n\n")
out.append(suffix)
tmp = ROOT / "build" / "sa" / f"order_tu_{func}.c"
tmp.write_text("".join(out))
print(f"order_search: {len(variants)} variants")

r = subprocess.run([sys.executable, str(ROOT / "scripts" / "match_check.py"), str(tmp), f"{func}__v0", *ccargs, "-q"],
                   capture_output=True, text=True)
obj = mc.CACHE / (tmp.stem + ".o")
dump = mc.container(f"{mc.OBJDUMP} -s /src/{obj.relative_to(ROOT)}; echo __RELOCS__; {mc.OBJDUMP} -r /src/{obj.relative_to(ROOT)}; echo __DISASM__")
sections, relocs, _ = mc.parse_objdump(dump.stdout)
if not sections:
    print(r.stdout[-3000:], r.stderr[-3000:])
    sys.exit("order_search: compile failed")
table = mc.symbol_addresses()
retail = mc.retail_listing(func)
scores = []
for n in range(len(variants)):
    sec = f".text.{func}__v{n}"
    if sec not in sections:
        continue
    words, seen, errors = mc.resolve(func, sections[sec], relocs.get(sec, []), retail[0][0], table)
    d = abs(len(words) - len(retail)) + len(errors)
    for i, (_, rw, rtext) in enumerate(retail):
        ow = words[i] if i < len(words) else None
        need = bool(mc.SYMREF.search(rtext) or mc.JREF.match(rtext))
        if ow != rw or (need and i * 4 not in seen):
            d += 1
    scores.append((d, n))
scores.sort()
for d, n in scores[:5]:
    print(f"  v{n}: {d} differing")
best = scores[0][1]
body = skeleton[0]
for k, order in enumerate(variants[best]):
    body += "".join(order) + skeleton[k + 1]
(ROOT / "build" / "sa" / f"order_best_{func}.c").write_text(prefix + body + suffix)
print(f"order_search: best v{best} ({scores[0][0]}) -> build/sa/order_best_{func}.c")
