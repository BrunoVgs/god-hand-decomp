#!/usr/bin/env python3
"""fam_sig.py FN...: compact signature of damage-take setup functions (constants, stack store order, tail)."""
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "scripts"))
import sa_precheck  # noqa: E402

funcs = sa_precheck.load_funcs()


def sig(name):
    ins = funcs[name]
    regs = {}
    consts = []
    stack = []
    tail = []
    calls = []
    scale = None
    pending_hi = {}
    for _, op, a in ins:
        if op == "lui" and a[0] == "$at":
            m = re.match(r"\(0x([0-9A-F]+) >> 16\)", a[1])
            if m:
                pending_hi["at"] = int(m.group(1), 16)
        if op == "mtc1" and a[0] == "$at" and "at" in pending_hi:
            v = struct.unpack("<f", struct.pack("<I", pending_hi["at"]))[0]
            regs[a[1]] = round(v, 4)
            consts.append(round(v, 4))
        if op == "mtc1" and a[0] == "$zero":
            regs[a[1]] = 0.0
        if op in ("swc1", "sw") and a[1].endswith("($sp)"):
            off = int(a[1].split("(")[0], 16)
            if off < 0x40:
                stack.append(f"{off // 4}={regs.get(a[0], a[0])}")
        if op == "mul.s":
            scale = a
        if op in ("sw", "sh", "sb") and a[1].endswith("($s0)"):
            tail.append(f"{op}{a[1].split('(')[0]}={a[0]}")
        if op == "jal":
            calls.append(a[0])
    return consts, stack, scale, tail, calls


if __name__ == "__main__":
  for n in sys.argv[1:]:
      c, s, sc, t, calls = sig(n)
      print(n, len(funcs[n]) * 4)
      print("   consts", c)
      print("   stack ", " ".join(s))
      print("   scale ", sc)
      print("   tail  ", " ".join(t))
      print("   calls ", " ".join(calls))
