#!/usr/bin/env bash
# score_nm.sh — measured NON_MATCHING decompiled % (never touches matching build/).
#
# 1) gen us-nm config
# 2) seed build-nm from matching build via hardlinks (fast) + LCF rewrite
# 3) delete .o for every TU containing NON_MATCHING
# 4) compile.py --no-link with -DNON_MATCHING
# 5) fill gaps from build/; objdiff → progress/report.nm.json + score_nm_summary.json
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

echo "[1/6] generate config/us-nm/"
python3 scripts/gen_nm_config.py

echo "[2/6] seed build-nm/ .o hardlinks from build/ + LCF"
python3 - <<'PY'
import os
import shutil
from pathlib import Path

src, dst = Path("build"), Path("build-nm")
n = 0
for p in src.rglob("*.o"):
    out = dst / p.relative_to(src)
    out.parent.mkdir(parents=True, exist_ok=True)
    if out.exists():
        continue
    try:
        os.link(p, out)
    except OSError:
        shutil.copy2(p, out)
    n += 1
print(f"  linked/copied {n} new .o files")
lcf = Path("build/SLUS_215.03.lcf")
if lcf.is_file():
    Path("build-nm/SLUS_215.03.lcf").write_text(
        lcf.read_text().replace("build/", "build-nm/")
    )
stamp = Path("build/carve.stamp.json")
if stamp.is_file():
    shutil.copy2(stamp, Path("build-nm/carve.stamp.json"))
rel = Path("build/rel")
if rel.is_dir():
    for p in rel.rglob("*"):
        if not p.is_file():
            continue
        out = Path("build-nm/rel") / p.relative_to(rel)
        out.parent.mkdir(parents=True, exist_ok=True)
        if out.exists():
            continue
        try:
            os.link(p, out)
        except OSError:
            shutil.copy2(p, out)
PY

echo "[3/6] delete NON_MATCHING TU objects for measured rebuild"
python3 - <<'PY'
from pathlib import Path
n = 0
for src in Path("src").rglob("*"):
    if src.suffix not in {".c", ".cc", ".cpp"}:
        continue
    if "NON_MATCHING" not in src.read_text(errors="ignore"):
        continue
    obj = Path("build-nm") / src.with_suffix(".o")
    if obj.is_file():
        obj.unlink()
        n += 1
print(f"  deleted {n} objects")
PY

echo "[4/6] compile build-nm with -DNON_MATCHING (--no-link)"
python3 compile.py --config config/us-nm/compile_config.json --no-link

echo "[5/6] fill missing bases from matching build/"
python3 - <<'PY'
import json, shutil
from pathlib import Path
root = Path(".")
objdiff = json.loads((root / "config/us-nm/objdiff.json").read_text())
copied = missing = 0
for unit in objdiff.get("units", []):
    base = unit.get("base_path")
    if not base:
        continue
    base_rel = base.replace("../../", "", 1)
    base_path = root / base_rel
    if base_path.is_file():
        continue
    match_path = root / base_rel.replace("build-nm/", "build/", 1)
    if match_path.is_file():
        base_path.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(match_path, base_path)
        copied += 1
    else:
        missing += 1
print(f"  copied {copied}; missing {missing}")
if missing:
    raise SystemExit(f"score_nm: {missing} bases still missing")
PY

echo "[6/6] objdiff report.nm.json"
tools/objdiff-cli report generate -p config/us-nm -o progress/report.nm.json -f json-pretty

python3 - <<'PY'
import json
from pathlib import Path
a = json.load(open("progress/report.json"))["measures"]
b = json.load(open("progress/report.nm.json"))["measures"]
total = int(a["total_code"])
matched = int(a["matched_code"])
nm_fuzzy = float(b["fuzzy_match_percent"])
decomp_bytes = int(round(total * nm_fuzzy / 100.0))
nm_only = max(0, decomp_bytes - matched)
print(f"  matching  fuzzy={a['fuzzy_match_percent']:.6f}% matched_code={matched}")
print(f"  NON_MATCH fuzzy={nm_fuzzy:.6f}%")
print(f"  decompiled (measured): {nm_fuzzy:.4f}% ({decomp_bytes}/{total}); +{nm_only} B NM")
Path("progress/score_nm_summary.json").write_text(
    json.dumps(
        {
            "matched_code": matched,
            "total_code": total,
            "matched_code_percent": float(a["matched_code_percent"]),
            "data_percent": float(a["matched_data_percent"]),
            "nm_fuzzy_match_percent": nm_fuzzy,
            "decompiled_bytes": decomp_bytes,
            "non_matching_bytes": nm_only,
        },
        indent=2,
    )
    + "\n"
)
PY
echo "done."
