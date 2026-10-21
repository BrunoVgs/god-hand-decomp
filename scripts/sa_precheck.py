#!/usr/bin/env python3
"""Classify functions by known listing patterns before spending attempts on them. Not part of the build.

    python3 scripts/sa_precheck.py FN [FN...]
    python3 scripts/sa_precheck.py --queue          # summary over every uncarved function

Verdicts:
    ASSN dli      ps2eeas-only `dli` chain (ori $zero / odd dsll / ori). Write it in a new
                  per-function file; check with match_check.py --as sn and register with
                  sa_register.py --as sn.
    SKIP epilogue symbol starts with the previous function's epilogue.
    SKIP cvtws    retail cvt.w.s; every compiler emits trunc.w.s for (int) casts.
    HAND          VU0 or MMI instructions: m2c cannot draft them, write from the listing.
    M2C           m2c_draft.py should give a usable draft (notes list what the wrapper fixes up).
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ASM = ROOT / "asm" / "cod" / "000000.s"
INS_RE = re.compile(r"/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+(\w+)\s*(.*)")
CVTWS_RE = re.compile(r"/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+\.word\s+\S+\s+# cvt\.w\.s\s+(.*?) #")
VU0_RE = re.compile(r"^(lqc2|sqc2|qmfc2|qmtc2|cfc2|ctc2|vcallms\w*|v[a-z0-9]+\.\w+|vnop|vwaitq)$")
MMI_RE = re.compile(
    r"^(p(add|sub|ext|cpy|and|or|xor|nor|mf|mt|sll|srl|sra|ceq|cgt|min|max|abs|lzc|mult|madd|div"
    r"|interh|rot|exe|pac|hadd|hmadd)\w*|mfhi1|mflo1|mthi1|mtlo1|mult1|multu1|div1|divu1|madd1|maddu1|qfsrv)$")


def load_funcs() -> dict[str, list[tuple[int, str, list[str]]]]:
    funcs: dict[str, list[tuple[int, str, list[str]]]] = {}
    cur = None
    for line in ASM.read_text().splitlines():
        if line.startswith("glabel "):
            cur = funcs.setdefault(line.split()[1], [])
            continue
        if line.startswith("endlabel"):
            cur = None
            continue
        if cur is not None:
            m = INS_RE.search(line)
            if m:
                cur.append((int(m[1], 16), m[2], [a.strip() for a in m[3].split(",")] if m[3] else []))
            elif m := CVTWS_RE.search(line):
                cur.append((int(m[1], 16), "cvt.w.s", [a.strip() for a in m[2].split(",")]))
    return funcs


def dli_chains(ins) -> int:
    n = 0
    for i, (_, op, a) in enumerate(ins):
        if op != "ori" or len(a) != 3 or a[1] != "$zero":
            continue
        r, odd, steps, tail = a[0], False, 0, False
        for _, op2, b in ins[i + 1:i + 12]:
            if op2 in ("dsll", "dsll32") and b[:2] == [r, r]:
                v = int(b[2], 0)
                odd |= (op2 == "dsll" and v != 16) or (op2 == "dsll32" and v != 0)
                steps += 1
            elif op2 == "ori" and b[:2] == [r, r]:
                tail |= odd
            elif r in b:
                break
        if steps and odd and tail:
            n += 1
    return n


def classify(ins) -> tuple[str, list[str]]:
    notes = []
    if not ins:
        return "SKIP noasm", notes
    ops = [op for _, op, _ in ins]
    first = ins[0]
    if first[1] in ("addiu", "daddiu") and first[2][:2] == ["$sp", "$sp"] and not first[2][2].startswith("-"):
        return "SKIP epilogue", notes
    if "cvt.w.s" in ops:
        return "SKIP cvtws", ["cvt.w.s: every compiler emits trunc.w.s for (int) casts"]
    hand = []
    if any(VU0_RE.match(o) for o in ops):
        hand.append("VU0")
    if any(MMI_RE.match(o) for o in ops):
        hand.append("MMI")
    o0 = any(op == "daddu" and a[:3] == ["$fp", "$sp", "$zero"] for _, op, a in ins) \
        and not any(op == "subu" and a and a[0] == "$sp" for _, op, a in ins)
    o0_note = ("-O0 object: new file, --c-flags-add=-O0 (+ --as sn); int params, register self; "
               "one extra return per surplus `b` to the epilogue (classFADE.c)")
    if dli_chains(ins):
        note = f"{dli_chains(ins)} ps2eeas dli chain(s): new file, --as sn"
        if hand:
            return "HAND " + "/".join(hand), [note]
        return ("O0" if o0 else "ASSN dli"), ([o0_note] if o0 else []) + [note]
    if o0 and not hand:
        return "O0", [o0_note]
    jt = sum(1 for _, op, a in ins if op == "jr" and a and a[0] != "$ra")
    if jt:
        notes.append(f"{jt} jump table(s): m2c_draft.py adds jtbl_ data")
    if any(o in ("ldl", "ldr", "sdl", "sdr") for o in ops):
        notes.append("ldl/sdl pairs: m2c_draft.py folds them to ld/sd")
    if any(re.search(r"\$t[0-3]\b", r) for _, _, a in ins for r in a):
        notes.append("args 5-8: m2c_draft.py renames $t0-$t3 to $a4-$a7")
    if any(ins[i][1] == "mtc1" and ins[i + 1][1] == "nop" for i in range(len(ins) - 1)):
        notes.append("mtc1+nop hazard pairs: try --as sn (ps2eeas keeps them; ee-as drops them)")
    lw_regs = {a[0] for _, op, a in ins if op == "lw" and a}
    if any(op == "dsrl" and a and a[1] in lw_regs for _, op, a in ins):
        notes.append("lw+dsrl bit test: long t = word; if ((((unsigned long)t >> N) & 1UL) == 1UL)")
    if hand:
        return "HAND " + "/".join(hand), notes
    return "M2C", notes


def main() -> int:
    args = sys.argv[1:]
    if not args:
        print(__doc__)
        return 2
    funcs = load_funcs()
    if args == ["--queue"]:
        cfg = json.loads((ROOT / "compile_config.json").read_text())
        carved = {e["name"] for e in cfg["carved_funcs"] if "name" in e}
        tally: dict[str, list[int]] = {}
        for name, ins in funcs.items():
            if name in carved:
                continue
            v = classify(ins)[0]
            t = tally.setdefault(v, [0, 0])
            t[0] += 1
            t[1] += len(ins) * 4
        for v, (n, b) in sorted(tally.items(), key=lambda x: -x[1][0]):
            print(f"{v:16s} {n:5d} functions {b:8d} bytes")
        return 0
    for name in args:
        ins = funcs.get(name)
        v, notes = classify(ins or [])
        print(f"{name} {len(ins or []) * 4:5d}B  {v:14s} {'; '.join(notes)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
