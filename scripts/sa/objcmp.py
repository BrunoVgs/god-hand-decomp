#!/usr/bin/env python3
"""Compare the code-relevant content of two MIPS ELF32 little-endian objects.

    python3 scripts/sa/objcmp.py A.o B.o     # exit 0 if equivalent

Equivalent means: identical bytes in every SHF_ALLOC section, and identical
relocations per section as (offset, type, symbol name, addend). Symbol table
order, .comment, .mdebug, .pdr and debug sections are ignored.
"""
from __future__ import annotations

import struct
import sys
from pathlib import Path

SHF_ALLOC = 0x2
SHT_SYMTAB, SHT_RELA, SHT_REL = 2, 4, 9


def sections(data: bytes) -> list[dict]:
    shoff, = struct.unpack_from("<I", data, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", data, 0x2E)
    out = []
    for i in range(shnum):
        name, typ, flags, _addr, off, size, link, info, _al, entsize = struct.unpack_from("<10I", data, shoff + i * shentsize)
        out.append({"name_off": name, "type": typ, "flags": flags, "off": off, "size": size,
                    "link": link, "info": info, "entsize": entsize})
    strtab = out[shstrndx]
    for s in out:
        start = strtab["off"] + s["name_off"]
        s["name"] = data[start:data.index(b"\0", start)].decode()
    return out


def summary(path: Path) -> tuple[dict, dict]:
    data = path.read_bytes()
    secs = sections(data)
    alloc = {s["name"]: data[s["off"]:s["off"] + s["size"]] if s["type"] != 8 else s["size"]
             for s in secs if s["flags"] & SHF_ALLOC}
    names: list[str] = []
    sym = next((s for s in secs if s["type"] == SHT_SYMTAB), None)
    if sym:
        st = secs[sym["link"]]
        for i in range(sym["size"] // 16):
            nm, _v, _sz, info, _o, shndx = struct.unpack_from("<IIIBBH", data, sym["off"] + i * 16)
            if nm:
                start = st["off"] + nm
                names.append(data[start:data.index(b"\0", start)].decode())
            elif (info & 0xF) == 3 and shndx < len(secs):
                names.append("$sec:" + secs[shndx]["name"])
            else:
                names.append("")
    relocs = {}
    for s in secs:
        if s["type"] not in (SHT_REL, SHT_RELA):
            continue
        target = secs[s["info"]]["name"]
        ent = 12 if s["type"] == SHT_RELA else 8
        rows = []
        for i in range(s["size"] // ent):
            off, info = struct.unpack_from("<II", data, s["off"] + i * ent)
            add = struct.unpack_from("<i", data, s["off"] + i * ent + 8)[0] if ent == 12 else 0
            idx = info >> 8
            rows.append((off, info & 0xFF, names[idx] if idx < len(names) else idx, add))
        relocs[target] = rows
    return alloc, relocs


def diff(a: Path, b: Path) -> str | None:
    aa, ar = summary(a)
    ba, br = summary(b)
    if aa.keys() != ba.keys():
        return f"section sets differ: {sorted(aa.keys() ^ ba.keys())}"
    for k in aa:
        if aa[k] != ba[k]:
            return f"bytes differ in {k}"
    for k in ar.keys() | br.keys():
        if ar.get(k, []) != br.get(k, []):
            return f"relocations differ in {k}"
    return None


if __name__ == "__main__":
    d = diff(Path(sys.argv[1]), Path(sys.argv[2]))
    print(d or "equivalent")
    sys.exit(1 if d else 0)
