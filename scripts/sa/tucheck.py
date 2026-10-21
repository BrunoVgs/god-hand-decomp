"""tucheck.py TU...: match_check every carved function of each registered TU with its configured compiler."""
import json
import subprocess
import sys

cfg = json.load(open("compile_config.json"))
units = {u.get("path"): u for u in cfg["compile_units"] if "path" in u}
bad = 0
for tu in sys.argv[1:]:
    u = units.get(tu)
    fns = [f["name"] for f in cfg["carved_funcs"] if f.get("tu") == tu]
    if not u or not fns:
        print(f"{tu}: not registered")
        bad += 1
        continue
    cmd = ["python3", "scripts/match_check.py", tu, *fns, "--compiler", u.get("compiler", "ee-2.9-991111")]
    if u.get("c_flags_drop"):
        cmd.append("--drop-reorder")
    out = subprocess.run(cmd, capture_output=True, text=True).stdout + ""
    res = [l for l in out.splitlines() if l.startswith(("MATCH", "FAIL", "ERROR")) or "rror" in l]
    ok = sum(l.startswith("MATCH") for l in res)
    status = "OK" if ok == len(fns) else "BAD"
    bad += status == "BAD"
    print(f"{status} {tu}: {ok}/{len(fns)}")
    if status == "BAD":
        print(out[-3000:])
sys.exit(1 if bad else 0)
