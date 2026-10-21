"""m2c_survey.py NAME...: run m2c (as scripts/m2c_draft.py does) on each function and classify the result.

Run inside the container:  scripts/container_run.sh /src/.venv/bin/python /src/scripts/sa/m2c_survey.py NAMES
Prints one TSV line per function: name, verdict, listing markers, m2c_errors, first error line.
"""
import os
import re
import subprocess
import sys

sys.path.insert(0, "/src/scripts")
import m2c_draft  # noqa: E402

VU0 = re.compile(r"\b(lqc2|sqc2|qmfc2|qmtc2|cfc2|ctc2|vcallms\w*|v(add|sub|mul|madd|msub|opm\w*|div|sqrt|rsqrt|move|mr32|itof\d*|ftoi\d*|clip|nop|waitq|abs|max|mini|iadd\w*|isub\w*|lqi|sqi)\w*\.\w+)\b")
MMI = re.compile(r"\b(p(add|sub|ext|cpy|and|or|xor|nor|mf|mt|sll|srl|sra|ceq|cgt|min|max|abs|lzc|mult|madd|div|interh|rot|exe|pac|hadd|hmadd)\w*|mfhi1|mflo1|mthi1|mtlo1|mult1|multu1|div1|divu1|madd1|maddu1|qfsrv)\b")
Q128 = re.compile(r"^\s*(?:/\*.*?\*/\s*)?(lq|sq)\s", re.M)
JR = re.compile(r"\bjr\s+\$(?!ra\b)\w+")


def classify(name):
    asm = m2c_draft.extract(name, raw=os.environ.get("M2C_RAW") == "1")
    text = asm.read_text()
    marks = []
    if JR.search(text) and re.search(r"jtbl|\.rodata|D_\w+", text):
        marks.append("jtbl")
    if VU0.search(text):
        marks.append("vu0")
    if MMI.search(text):
        marks.append("mmi")
    if Q128.search(text):
        marks.append("q128")
    cmd = [str(m2c_draft.VENV_PY), str(m2c_draft.ROOT / "tools" / "m2c" / "m2c.py"),
           "-t", "mipsee-gcc-c", "--context", str(m2c_draft.build_context()), str(asm)]
    p = subprocess.run(cmd, capture_output=True, text=True, timeout=120)
    out = p.stdout
    errs = out.count("M2C_ERROR")
    jt = "jump table" in out.lower() or "jtbl" in out
    first = ""
    for line in (p.stderr + "\n" + out).splitlines():
        if "M2C_ERROR" in line or "Error" in line or "error" in line.lower():
            first = line.strip()[:140]
            break
    if p.returncode != 0 or not out.strip():
        verdict = "crash"
    elif errs:
        verdict = "errors"
    else:
        verdict = "clean"
    unset = sorted(set(re.findall(r"Read from unset register \$(\w+)", out)))
    unk = sorted(set(re.findall(r"unknown instruction: (\w+)", out)))
    if unset:
        marks.append("unset:" + "/".join(unset))
    if unk:
        marks.append("unk:" + "/".join(unk))
    if jt and "jtbl" not in marks:
        marks.append("jtbl")
    return verdict, ",".join(marks) or "-", errs, first


for n in sys.argv[1:]:
    try:
        v, m, e, f = classify(n)
    except SystemExit as ex:
        v, m, e, f = "noasm", "-", 0, str(ex)[:140]
    except Exception as ex:  # noqa: BLE001
        v, m, e, f = "crash", "-", 0, repr(ex)[:140]
    print(f"{n}\t{v}\t{m}\t{e}\t{f}", flush=True)
