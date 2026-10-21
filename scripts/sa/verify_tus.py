"""Run match_check on every carved function of the given TUs with the TU's settings.

usage: python3 scripts/sa/verify_tus.py src/cod/a.c [src/cod/b.c ...]
Prints one line per TU: OK n/n, or the failing function lines.
"""
import json
import subprocess
import sys

cfg = json.load(open("compile_config.json"))
units = {u["path"]: u for u in cfg["compile_units"] if "path" in u}
funcs = {}
for f in cfg["carved_funcs"]:
    if "tu" in f:
        funcs.setdefault(f["tu"], []).append(f["name"])

rc = 0
for tu in sys.argv[1:]:
    u = units.get(tu)
    names = funcs.get(tu, [])
    if u is None or not names:
        print(f"{tu}: not registered / no carved functions")
        continue
    cmd = ["python3", "scripts/match_check.py", tu, *names, "--compiler", u["compiler"]]
    if u.get("fp_hazard_rules"):
        cmd.append(f"--fp-hazard-rules={u['fp_hazard_rules']}")
    if "-f=-freorder-blocks" in u.get("c_flags_drop", []):
        cmd.append("--drop-reorder")
    for flag in u.get("c_flags_add", []):
        cmd.append(f"--wrap-arg={flag}")
    if u.get("call_loop_pad"):
        cmd.append("--wrap-arg=--call-loop-pad")
    if tu.endswith((".cc", ".cpp")):
        cmd += ["--lang", "c++"]
    out = subprocess.run(cmd, capture_output=True, text=True).stdout
    lines = [l for l in out.splitlines() if l.startswith(("MATCH", "FAIL", "COMPILE-FAIL"))]
    ok = sum(l.startswith("MATCH") for l in lines)
    if ok == len(names):
        print(f"{tu}: OK {ok}/{len(names)}")
    else:
        rc = 1
        print(f"{tu}: {ok}/{len(names)}")
        for l in lines:
            if not l.startswith("MATCH"):
                print("   ", l)
        if not lines:
            print("   ", out[-400:])
sys.exit(rc)
