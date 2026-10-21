"""Unit tests for scripts/report_categories.py (per-function category scoring).

Offline. A synthetic report covers the split of a mixed unit; the committed
report.json is checked for being current, for counting every library function,
and for top-level categories that add up to the headline.
"""
from __future__ import annotations

import copy
import importlib.util
import json
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parent.parent


@pytest.fixture(scope="module")
def rc():
    sys.path.insert(0, str(ROOT / "scripts"))
    spec = importlib.util.spec_from_file_location(
        "report_categories", ROOT / "scripts" / "report_categories.py"
    )
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def _report():
    return {
        "categories": [{"id": i, "name": i, "measures": {}}
                       for i in ("engine", "engine.casino", "cri-middleware")],
        "units": [
            {"name": "src/cod/casino/a", "measures": {"total_units": 1},
             "metadata": {"progress_categories": ["engine", "engine.casino"], "complete": True},
             "functions": [
                 {"name": "func_00100000", "size": "40", "fuzzy_match_percent": 100.0},
                 {"name": "ADXT_Stop", "size": "24", "fuzzy_match_percent": 100.0},
             ]},
            {"name": "asm/cod/000000.part1", "measures": {"total_units": 1},
             "metadata": {"progress_categories": ["engine"]},
             "functions": [{"name": "func_00100100", "size": "16"}]},
            {"name": "asm/data/x", "measures": {"total_data": "8", "total_units": 1},
             "metadata": {"progress_categories": ["engine"]}},
        ],
    }


def test_mixed_unit_splits_by_function(rc):
    rep = _report()
    found = rc.rescore(rep, {0x00200000: "cri-middleware"}, {"ADXT_Stop": 0x00200000})
    assert found == 1
    cats = {c["id"]: c["measures"] for c in rep["categories"]}
    assert cats["cri-middleware"]["total_code"] == "24"
    assert cats["cri-middleware"]["matched_functions"] == 1
    assert cats["cri-middleware"]["complete_code"] == "24"
    assert cats["engine"]["total_code"] == "56"
    assert cats["engine"]["matched_code"] == "40"
    assert cats["engine"]["total_data"] == "8"
    assert cats["engine.casino"]["total_code"] == "40"
    assert rep["units"][0]["metadata"]["progress_categories"] == [
        "engine", "engine.casino", "cri-middleware"]
    assert rep["units"][2]["metadata"]["progress_categories"] == ["engine"]
    again = copy.deepcopy(rep)
    rc.rescore(again, {0x00200000: "cri-middleware"}, {"ADXT_Stop": 0x00200000})
    assert again == rep


def test_committed_report_is_current(rc):
    assert rc.main(["--check"]) == 0


def test_committed_report_counts_every_library_function(rc):
    rep = json.loads(rc.REPORT.read_text())
    library = json.loads(rc.CATEGORIES.read_text())["categories"]
    cats = {c["id"]: c["measures"] for c in rep["categories"]}
    for cid, addrs in library.items():
        assert cats[cid]["total_functions"] == len(addrs), cid
    top = [c["measures"] for c in rep["categories"] if "." not in c["id"]]
    for k in ("total_code", "matched_code", "total_functions", "matched_functions"):
        assert sum(int(m.get(k, 0)) for m in top) == int(rep["measures"][k]), k
