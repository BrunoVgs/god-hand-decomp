#!/usr/bin/env python3
"""Process progress/inbox/{worker-*,permuter}/ mechanically.

Throughput design:
  1. File NON_MATCHING / near-miss drops immediately (no scratch, no reseed).
  2. Scratch-compile + verify all claimed matches in parallel (no build lock).
  3. Register every scratch-pass, then ONE --reseed-expected for the whole set.
  4. Bisect only if that reseed fails. No score_nm / PROGRESS here.

Usage:
  python3 scripts/integrate_inbox.py
  python3 scripts/integrate_inbox.py --dry-run
  INTEGRATE_JOBS=8 python3 scripts/integrate_inbox.py
"""
from __future__ import annotations

import argparse
import fcntl
import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
import sys
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
INBOX = ROOT / "progress" / "inbox"
DONE = INBOX / "done"
RETAIL_ELF = "1742f95bef65bdb2aa57b7a77df4ac7619a092e9646e1ea325bc32ec8a64f3cd"
RETAIL_OV = "ea59932301345e48add7a3eff029b7d0d0138fff1abc67569467880678c653c1"
OBJDUMP = "mipsel-linux-gnu-objdump"
MONOLITH = ROOT / "asm" / "cod" / "000000.s"

sys.path.insert(0, str(ROOT))


def utc() -> str:
    return datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    h.update(path.read_bytes())
    return h.hexdigest()


def container(*args: str) -> subprocess.CompletedProcess:
    return subprocess.run(
        [str(ROOT / "scripts" / "container_run.sh"), *args],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )


def load_cfg() -> dict:
    return json.loads((ROOT / "compile_config.json").read_text())


def save_cfg(cfg: dict) -> None:
    (ROOT / "compile_config.json").write_text(json.dumps(cfg, indent=2) + "\n")


def inbox_folders() -> list[Path]:
    folders: list[Path] = []
    if not INBOX.is_dir():
        return folders
    for child in sorted(INBOX.iterdir()):
        if not child.is_dir() or child.name == "done":
            continue
        if child.name.startswith("worker-") or child.name == "permuter":
            for fn in sorted(child.iterdir()):
                if fn.is_dir() and not fn.name.startswith("."):
                    folders.append(fn)
    return folders


def read_meta(folder: Path) -> dict:
    meta_path = folder / "meta.json"
    if meta_path.is_file():
        meta = json.loads(meta_path.read_text())
    else:
        c_files = list(folder.glob("*.c"))
        if not c_files:
            raise FileNotFoundError(f"no .c in {folder}")
        meta = {
            "name": folder.name,
            "source": c_files[0].name,
            "compiler": "sn-2.95.3-136",
            "flags": ["-O2", "-G0", "-f=-freorder-blocks"],
            "size": None,
            "vaddr": None,
            "kind": "match",
        }
    if (folder / "fuzzy_score.txt").is_file() or (folder / "NON_MATCHING").is_file():
        meta["kind"] = "near_miss"
        try:
            meta["fuzzy_score"] = (folder / "fuzzy_score.txt").read_text().strip()
        except OSError:
            pass
    if folder.name.startswith("func_") and not meta.get("vaddr"):
        hexpart = folder.name.split("_", 1)[1]
        try:
            meta["vaddr"] = f"0x{int(hexpart, 16):08X}"
        except ValueError:
            pass
    return meta


_MONOLITH_TEXT: str | None = None


def monolith_text() -> str:
    global _MONOLITH_TEXT
    if _MONOLITH_TEXT is None:
        _MONOLITH_TEXT = MONOLITH.read_text()
    return _MONOLITH_TEXT


def extract_asm(name: str) -> Path:
    out_dir = ROOT / "build" / "inbox_verify_asm"
    out_dir.mkdir(parents=True, exist_ok=True)
    out = out_dir / f"{name}.s"
    if out.is_file():
        return out
    text = monolith_text()
    m = re.search(rf"^glabel {re.escape(name)}\n", text, re.M)
    if not m:
        raise FileNotFoundError(f"no glabel {name}")
    m2 = re.search(rf"^endlabel {re.escape(name)}\n", text[m.end() :], re.M)
    if not m2:
        raise FileNotFoundError(f"no endlabel {name}")
    out.write_text(text[m.start() : m.end() + m2.end()])
    return out


def bswap32(w: int) -> int:
    return struct.unpack("<I", struct.pack(">I", w))[0]


def parse_listing(path: Path):
    words = []
    jals = []
    for line in path.read_text().splitlines():
        if line.startswith("endlabel"):
            break
        m = re.search(
            r"/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s*\*/\s*(.*)$",
            line,
        )
        if not m:
            continue
        words.append(bswap32(int(m.group(1), 16)))
        jm = re.search(r"\bjal\s+(\w+)", m.group(2))
        if jm:
            jals.append((len(words) - 1, jm.group(1)))
    return words, jals


def is_jal(w: int) -> bool:
    return (w >> 26) == 0x03


def is_lui(w: int) -> bool:
    return (w >> 26) == 0x0F


def is_addiu(w: int) -> bool:
    return (w >> 26) == 0x09


def is_ori(w: int) -> bool:
    return (w >> 26) == 0x0D


def is_loadstore_i(w: int) -> bool:
    return (w >> 26) in (0x20, 0x21, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B)


def rt_of(w: int) -> int:
    return (w >> 16) & 0x1F


def rs_of(w: int) -> int:
    return (w >> 21) & 0x1F


def scratch_compile(folder: Path, meta: dict) -> Path:
    src = folder / meta["source"]
    out_dir = ROOT / "build" / "inbox_scratch" / meta["name"]
    out_dir.mkdir(parents=True, exist_ok=True)
    obj = out_dir / "scratch.o"
    shutil.copy2(src, out_dir / src.name)
    compiler = meta.get("compiler") or "sn-2.95.3-136"
    flags = meta.get("flags") or ["-O2", "-G0", "-f=-freorder-blocks"]
    # Quote flags safely for bash -lc
    flag_s = " ".join(flags)
    cmd = (
        f"python3 /src/scripts/ee-cc-wrap.py -c --compiler={compiler} -x c "
        f"{flag_s} -I/src/include -I/src/include/sce -I/src/build/asm "
        f"/src/build/inbox_scratch/{meta['name']}/{src.name} "
        f"-o /src/build/inbox_scratch/{meta['name']}/scratch.o"
    )
    r = container("bash", "-lc", cmd)
    if r.returncode != 0 or not obj.is_file():
        raise RuntimeError(f"compile failed: {r.stderr[-2000:]}\n{r.stdout[-1000:]}")
    return obj


def verify(name: str, obj: Path) -> tuple[bool, str]:
    asm = extract_asm(name)
    retail, jals = parse_listing(asm)
    rel = obj.relative_to(ROOT)
    # One container round-trip for both objdumps.
    script = (
        f"{OBJDUMP} -s -j .text.{name} /src/{rel}; echo __RELOCS__; "
        f"{OBJDUMP} -r /src/{rel}"
    )
    out = container("bash", "-lc", script)
    if out.returncode != 0:
        return False, f"objdump failed: {out.stderr[-500:]}"
    dump_s, _, dump_r = out.stdout.partition("__RELOCS__")
    raw = b""
    for line in dump_s.splitlines():
        m = re.match(r"\s*[0-9a-f]+\s+((?:[0-9a-f]{8}\s*)+)", line)
        if m:
            for w in m.group(1).split():
                raw += bytes.fromhex(w)
    ours = [struct.unpack_from("<I", raw, i)[0] for i in range(0, len(raw), 4)]
    if len(ours) != len(retail):
        return False, f"len {len(ours)}!={len(retail)}"
    real = 0
    last_lui_rt = None
    gap = 99
    for i, (rw, ow) in enumerate(zip(retail, ours)):
        gap += 1
        ign = is_jal(rw) or is_jal(ow)
        if not ign and (rw & 0xFFFF0000) == (ow & 0xFFFF0000):
            if is_lui(rw) or is_addiu(rw) or is_ori(rw) or is_loadstore_i(rw):
                if is_lui(rw) or (rw & 0xFFFF) == 0 or (ow & 0xFFFF) == 0:
                    ign = True
        if is_lui(rw) or is_lui(ow):
            ign = True
            last_lui_rt = rt_of(rw if is_lui(rw) else ow)
            gap = 0
        elif (
            last_lui_rt is not None
            and gap <= 6
            and (
                (is_addiu(rw) and is_addiu(ow))
                or (is_ori(rw) and is_ori(ow))
                or (is_loadstore_i(rw) and is_loadstore_i(ow))
            )
            and (rt_of(rw) == last_lui_rt or rs_of(rw) == last_lui_rt)
        ):
            ign = True
        if not ign and is_addiu(rw) and is_addiu(ow) and (ow & 0xFFFF) == 0:
            ign = True
        if not ign and is_ori(rw) and is_ori(ow) and (ow & 0xFFFF) == 0:
            ign = True
        if rw != ow and not ign:
            real += 1
    relocs = {}
    in_sec = False
    for line in dump_r.splitlines():
        if line.startswith(f"RELOCATION RECORDS FOR [.text.{name}]"):
            in_sec = True
            continue
        if in_sec:
            if line.startswith("RELOCATION RECORDS FOR"):
                break
            parts = line.split()
            if len(parts) >= 3 and parts[0] != "OFFSET":
                relocs[int(parts[0], 16)] = (parts[1], parts[2])
    for idx, sym in jals:
        off = idx * 4
        r = relocs.get(off)
        if r is None or r[0] != "R_MIPS_26" or r[1].split("+")[0] != sym:
            return False, f"jal reloc @{off:x} want {sym} got {r}"
    if real:
        return False, f"{real} word diffs"
    return True, f"match {len(retail)} words + {len(jals)} jals"


def pick_tu(name: str, meta: dict) -> str:
    if meta.get("tu"):
        return meta["tu"]
    return f"src/cod/inbox_{name}.c"


def resolve_vaddr(name: str, meta: dict) -> str:
    v = meta.get("vaddr")
    if isinstance(v, str) and v.startswith("0x"):
        return v
    if isinstance(v, int):
        return f"0x{v:08X}"
    if name.startswith("func_"):
        hexpart = name.split("_", 1)[1]
        try:
            return f"0x{int(hexpart, 16):08X}"
        except ValueError:
            pass
    m = re.search(
        rf"^glabel {re.escape(name)}\n\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+",
        monolith_text(),
        re.M,
    )
    if m:
        return f"0x{int(m.group(1), 16):08X}"
    raise ValueError(f"cannot resolve vaddr for {name}")


def resolve_src(folder: Path, meta: dict) -> Path:
    src = folder / meta.get("source", "")
    if src.is_file() and src.stat().st_size > 0:
        return src
    cands = [
        p
        for p in list(folder.glob("*.c")) + list(folder.rglob("*.c"))
        if p.is_file() and p.stat().st_size > 0
    ]
    if not cands:
        raise FileNotFoundError(f"no .c in {folder}")
    src = min(cands, key=lambda p: (0 if p.parent == folder else 1, len(str(p))))
    meta["source"] = str(src.relative_to(folder))
    return src


def register_near_miss(name: str, folder: Path, meta: dict, src: Path) -> str:
    """Write NON_MATCHING-guarded TU + permuter queue. Does not touch retail build."""
    tu = f"src/cod/inbox_nm_{name}.c"
    body = src.read_text()
    text = (
        f"/* inbox near-miss {name} */\n"
        f"#ifdef NON_MATCHING\n{body}\n"
        f"#else\nINCLUDE_ASM(\"nonmatching\", {name});\n#endif\n"
    )
    (ROOT / tu).write_text(text)
    q = ROOT / "progress" / "permuter_queue.md"
    line = (
        f"| `{name}` | {meta.get('compiler', 'sn')} | {meta.get('size', '—')} | "
        f"inbox near-miss fuzzy={meta.get('fuzzy_score', '?')} | queued |\n"
    )
    if q.is_file():
        qt = q.read_text()
        if name not in qt:
            q.write_text(qt.rstrip() + "\n" + line)
    else:
        q.write_text(
            "# Permuter queue\n\n| function | compiler | size | note | status |\n"
            "| --- | --- | --- | --- | --- |\n" + line
        )
    return tu


def register_matches_batch(
    items: list[tuple[str, Path, dict, Path]],
) -> list[str]:
    """Register many matches with a single compile_config write."""
    if not items:
        return []
    cfg = load_cfg()
    carved = {
        e["name"]
        for e in cfg.get("carved_funcs") or []
        if isinstance(e, dict) and e.get("name")
    }
    paths = {u.get("path") for u in cfg.get("compile_units") or [] if isinstance(u, dict)}
    added: list[str] = []
    for name, folder, meta, src in items:
        tu = pick_tu(name, meta)
        tu_path = ROOT / tu
        body = src.read_text()
        if not tu_path.exists():
            tu_path.write_text(f"/* inbox integrate {name} */\n{body}\n")
        elif f".text.{name}" not in tu_path.read_text():
            tu_path.write_text(tu_path.read_text().rstrip() + "\n\n" + body + "\n")
        size = meta.get("size")
        if not size:
            asm = extract_asm(name)
            size = len(parse_listing(asm)[0]) * 4
        vaddr = resolve_vaddr(name, meta)
        if name not in carved:
            cfg["carved_funcs"].append(
                {
                    "name": name,
                    "unit": "asm/cod/000000",
                    "vaddr": vaddr,
                    "size": int(size),
                    "tu": tu,
                }
            )
            carved.add(name)
        if tu not in paths:
            cfg["compile_units"].append(
                {
                    "path": tu,
                    "compiler": meta.get("compiler") or "sn-2.95.3-136",
                }
            )
            paths.add(tu)
        added.append(name)
    save_cfg(cfg)
    return added


def unregister(name: str) -> None:
    cfg = load_cfg()
    tus = {
        e.get("tu")
        for e in cfg["carved_funcs"]
        if isinstance(e, dict) and e.get("name") == name
    }
    cfg["carved_funcs"] = [
        e
        for e in cfg["carved_funcs"]
        if not (isinstance(e, dict) and e.get("name") == name)
    ]
    still = {
        e.get("tu")
        for e in cfg["carved_funcs"]
        if isinstance(e, dict) and e.get("tu")
    }
    drop = {
        t for t in tus if t and t not in still and str(t).startswith("src/cod/inbox_")
    }
    cfg["compile_units"] = [
        u
        for u in cfg["compile_units"]
        if not (isinstance(u, dict) and u.get("path") in drop)
    ]
    save_cfg(cfg)
    for t in drop:
        p = ROOT / t
        if p.is_file():
            p.unlink()


def move_done(folder: Path, status: str, note: str) -> None:
    DONE.mkdir(parents=True, exist_ok=True)
    dest = DONE / folder.name
    if dest.exists():
        shutil.rmtree(dest)
    if folder.exists():
        shutil.move(str(folder), str(dest))
    else:
        dest.mkdir(parents=True, exist_ok=True)
    (dest / "RESULT.txt").write_text(f"{status}\n{utc()}\n{note}\n")


def reseed(name: str) -> tuple[bool, bool, str]:
    stamp = ROOT / "build" / "carve.stamp.json"
    if stamp.exists():
        stamp.unlink()
    t0 = time.time()
    r = container("python3", "compile.py", "--reseed-expected", name)
    (ROOT / "build" / "integrate_inbox_reseed.log").write_text(
        r.stdout + "\n" + r.stderr
    )
    elf = ROOT / "build" / "SLUS_215.03.elf"
    ov = ROOT / "build" / "rel" / "r207.rel"
    dt = time.time() - t0
    if not elf.is_file():
        return False, False, f"missing elf ({dt:.1f}s)"
    return (
        sha256(elf) == RETAIL_ELF,
        sha256(ov) == RETAIL_OV,
        f"rc={r.returncode} {dt:.1f}s",
    )


def bisect_restore(added: list[str]) -> list[str]:
    """Unregister bad names until hashes OK. Returns kept names."""
    kept: list[str] = []
    for name in added:
        unregister(name)
    ok, ov, note = reseed("func_0037B338")
    if not (ok and ov):
        raise RuntimeError(f"cannot restore retail after failed integrate: {note}")
    for name in added:
        done = DONE / name
        if not done.is_dir():
            continue
        meta = read_meta(done)
        try:
            src = resolve_src(done, meta)
            register_matches_batch([(name, done, meta, src)])
            e_ok, o_ok, n2 = reseed(name)
        except Exception as exc:  # noqa: BLE001
            unregister(name)
            (done / "RESULT.txt").write_text(f"fail\n{utc()}\nbisect error: {exc}\n")
            continue
        if e_ok and o_ok:
            kept.append(name)
            (done / "RESULT.txt").write_text(f"pass\n{utc()}\nbisect kept; {n2}\n")
        else:
            unregister(name)
            register_near_miss(name, done, {**meta, "kind": "near_miss"}, src)
            e2, o2, n3 = reseed("func_0037B338")
            (done / "RESULT.txt").write_text(
                f"fail\n{utc()}\blink mismatch; demoted NM; restore {e2}/{o2} {n3}\n"
            )
            if not (e2 and o2):
                raise RuntimeError("bisect demote broke retail")
    return kept


def scratch_verify_one(
    folder: Path, meta: dict, src: Path
) -> tuple[str, bool, str, Path, dict, Path]:
    """Worker: scratch compile + verify. Returns (name, ok, detail, folder, meta, src)."""
    name = folder.name
    t0 = time.time()
    try:
        src_name = src.name
        if not (folder / src_name).is_file():
            shutil.copy2(src, folder / src_name)
        meta = {**meta, "name": name, "source": src_name}
        obj = scratch_compile(folder, meta)
        ok, detail = verify(name, obj)
        detail = f"{detail} ({time.time() - t0:.1f}s)"
        return name, ok, detail, folder, meta, folder / src_name
    except Exception as exc:  # noqa: BLE001
        return name, False, f"error: {exc} ({time.time() - t0:.1f}s)", folder, meta, src


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument(
        "--jobs",
        type=int,
        default=int(os.environ.get("INTEGRATE_JOBS", "8")),
        help="parallel scratch-verify workers",
    )
    args = ap.parse_args()
    pid_path = ROOT / "build" / "integrate_inbox.pid"
    lock_path = ROOT / "build" / "integrate_inbox.lock"
    pid_path.parent.mkdir(parents=True, exist_ok=True)
    lock_fh = open(lock_path, "a+", encoding="utf-8")
    try:
        fcntl.flock(lock_fh.fileno(), fcntl.LOCK_EX | fcntl.LOCK_NB)
    except BlockingIOError:
        print("integrate_inbox: another instance holds the lock; exiting")
        return 0
    pid_path.write_text(f"{os.getpid()}\n")

    t_all = time.time()
    folders = inbox_folders()
    if not folders:
        print("integrate_inbox: nothing waiting")
        return 0
    print(
        f"integrate_inbox: {len(folders)} folder(s) @ {utc()} jobs={args.jobs}",
        flush=True,
    )

    stats = {
        "pass": 0,
        "near_miss": 0,
        "fail": 0,
        "skip_incomplete": 0,
        "skip_already": 0,
        "skip_gone": 0,
    }
    timing = {"near_miss_s": 0.0, "verify_s": 0.0, "register_s": 0.0, "reseed_s": 0.0}

    cfg0 = load_cfg()
    already = {
        e["name"]
        for e in cfg0.get("carved_funcs") or []
        if isinstance(e, dict) and e.get("name") and e.get("tu")
    }

    near_items: list[tuple[Path, dict, Path]] = []
    match_items: list[tuple[Path, dict, Path]] = []

    for folder in folders:
        name = folder.name
        if not folder.is_dir():
            stats["skip_gone"] += 1
            continue
        if name in already:
            if not args.dry_run:
                move_done(folder, "pass", "already carved; skipped")
            stats["skip_already"] += 1
            print(f"  skip-already {name}", flush=True)
            continue
        try:
            meta = read_meta(folder)
            meta["name"] = name
            src = resolve_src(folder, meta)
        except FileNotFoundError:
            print(f"  skip-incomplete {name}: no .c yet", flush=True)
            stats["skip_incomplete"] += 1
            continue
        except Exception as exc:  # noqa: BLE001
            print(f"  error {name}: {exc}", flush=True)
            if not args.dry_run:
                try:
                    move_done(folder, "fail", str(exc))
                except Exception:
                    pass
            stats["fail"] += 1
            continue
        if meta.get("kind") == "near_miss":
            near_items.append((folder, meta, src))
        else:
            match_items.append((folder, meta, src))

    # --- Phase 1: near-misses (no reseed) ---
    t0 = time.time()
    for folder, meta, src in near_items:
        name = folder.name
        if args.dry_run:
            print(f"  DRY near_miss {name}", flush=True)
        else:
            register_near_miss(name, folder, meta, src)
            move_done(folder, "near_miss", "queued for permuter; no reseed")
        stats["near_miss"] += 1
        print(f"  near_miss {name}", flush=True)
    timing["near_miss_s"] = time.time() - t0

    # --- Phase 2: parallel scratch verify ---
    t0 = time.time()
    verified_ok: list[tuple[str, Path, dict, Path, str]] = []
    if match_items:
        print(
            f"  verifying {len(match_items)} match candidate(s) with {args.jobs} jobs…",
            flush=True,
        )

        def _work(item: tuple[Path, dict, Path]):
            folder, meta, src = item
            return scratch_verify_one(folder, meta, src)

        with ThreadPoolExecutor(max_workers=max(1, args.jobs)) as ex:
            futs = [ex.submit(_work, it) for it in match_items]
            for fut in as_completed(futs):
                name, ok, detail, folder, meta, src = fut.result()
                if ok:
                    verified_ok.append((name, folder, meta, src, detail))
                    print(f"  scratch-pass {name}: {detail}", flush=True)
                else:
                    if args.dry_run:
                        print(f"  DRY fail {name}: {detail}", flush=True)
                    else:
                        try:
                            register_near_miss(
                                name, folder, {**meta, "kind": "near_miss"}, src
                            )
                            move_done(folder, "fail", detail)
                        except Exception as exc:  # noqa: BLE001
                            print(f"  error filing fail {name}: {exc}", flush=True)
                            try:
                                move_done(folder, "fail", detail)
                            except Exception:
                                pass
                    stats["fail"] += 1
                    print(f"  scratch-fail {name}: {detail}", flush=True)
    timing["verify_s"] = time.time() - t0

    if args.dry_run:
        stats["pass"] = len(verified_ok)
        print("stats", stats, "timing", timing, flush=True)
        return 0

    # --- Phase 3: register all passes, ONE reseed ---
    t0 = time.time()
    batch = [(n, f, m, s) for n, f, m, s, _ in verified_ok]
    added = register_matches_batch(batch)
    for name, folder, meta, src, detail in verified_ok:
        move_done(folder, "pass", detail)
        stats["pass"] += 1
        print(f"  pass {name}: {detail}", flush=True)
    timing["register_s"] = time.time() - t0

    reseeds = 0
    if added:
        t0 = time.time()
        anchor = added[-1]
        elf_ok, ov_ok, note = reseed(anchor)
        reseeds = 1
        timing["reseed_s"] = time.time() - t0
        print(f"reseed {anchor}: elf={elf_ok} ov={ov_ok} {note}", flush=True)
        if not (elf_ok and ov_ok):
            print("hash mismatch — bisecting", flush=True)
            kept = bisect_restore(added)
            # bisect_restore does 1 restore + N trial reseeds + demote restores
            reseeds += 1 + len(added)  # upper bound note
            print(f"bisect kept {len(kept)}/{len(added)}", flush=True)
            stats["pass"] = len(kept)
            stats["fail"] += len(added) - len(kept)

    counter = ROOT / "progress" / "integrate_count.txt"
    n = int(counter.read_text()) if counter.is_file() else 0
    counter.write_text(str(n + 1) + "\n")
    print(
        f"stats {stats} integrate#{n + 1} reseeds={reseeds} "
        f"timing={ {k: round(v, 1) for k, v in timing.items()} } "
        f"total={time.time() - t_all:.1f}s",
        flush=True,
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
