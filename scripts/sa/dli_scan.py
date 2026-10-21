"""dli_scan.py: count functions whose retail listing has a ps2eeas-only dli chain (ori rX,$zero,imm ; dsll[32] rX,rX,n)."""
import json, re, sys
from pathlib import Path
asm = Path("asm/cod/000000.s").read_text().splitlines()
cfg = json.load(open("compile_config.json"))
carved = {e["name"] for e in cfg["carved_funcs"] if "name" in e}
units = {u.get("path"): u for u in cfg["compile_units"] if "path" in u}
tu_of = {e["name"]: e.get("tu") for e in cfg["carved_funcs"] if "name" in e}
log = Path("progress/batch_log.md").read_text()
ins_re = re.compile(r"/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/\s+(\w+)\s+(.*)")
funcs = []; cur = None
for line in asm:
    if line.startswith("glabel "):
        cur = {"name": line.split()[1], "ins": []}; funcs.append(cur); continue
    if line.startswith("endlabel"): cur = None; continue
    if cur is not None:
        m = ins_re.search(line)
        if m: cur["ins"].append((m[1], [a.strip() for a in m[2].split(",")]))
def odd_shift(op, amt):
    v = int(amt, 0)
    return (op == "dsll" and v != 16) or (op == "dsll32" and v != 0)


def chains(ins):
    n = 0
    for i, (op, a) in enumerate(ins):
        if op == "ori" and len(a) == 3 and a[1] == "$zero":
            r = a[0]
            j, odd, steps, tail = i + 1, False, 0, False
            while j < len(ins) and j < i + 12:
                op2, b = ins[j]
                if op2 in ("dsll", "dsll32") and b[:2] == [r, r]:
                    odd |= odd_shift(op2, b[2]); steps += 1
                elif op2 == "ori" and b[:2] == [r, r]:
                    tail |= odd
                elif r in b:
                    break
                j += 1
            if steps and odd and tail:
                n += 1
    return n
hit = [(f["name"], chains(f["ins"]), len(f["ins"])*4) for f in funcs]
hit = [h for h in hit if h[1]]
print("functions with ps2eeas-only chains:", len(hit), "sites:", sum(h[1] for h in hit))
un = [h for h in hit if h[0] not in carved]
print("  unmatched (queue):", len(un), "bytes:", sum(h[2] for h in un))
tried = [h for h in un if re.search(rf"\| {re.escape(h[0])} \|", log)]
print("  of which already tried today:", len(tried), [h[0] for h in tried])
m = [h for h in hit if h[0] in carved]
print("  matched:", len(m), " in TUs with as=sn:", sum(units.get(tu_of[h[0]], {}).get("as") == "sn" for h in m))
other = [h for h in m if units.get(tu_of[h[0]], {}).get("as") != "sn"]
print("  matched without as=sn (should be 0 or asm-included):", len(other), [ (h[0], tu_of[h[0]]) for h in other][:10])
