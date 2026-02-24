"""
coverage_tracker.py - Map test execution results to MC/DC coverage.

Consumes:
  - MC-DC-Vectors.json   (output of 'analyze' mode)
  - test-results.json    (test execution results)

Produces:
  - Per-expression MC/DC coverage percentage
  - Per-condition independence pair coverage status
  - Overall project MC/DC coverage

test-results.json format (expected):
{
  "project": "train_door_control2",
  "timestamp": "2026-02-24T00:00:00Z",
  "sil_level": 3,
  "test_cases": [
    {
      "id": "TC-CBE-SM-001-01",
      "expression_id": "CBE-SM-001",
      "condition_values": {"0": true, "1": false},
      "outcome": false,
      "status": "PASS",
      "test_function": "test_sm_speed_check_primary_fail"
    },
    ...
  ]
}

If test-results.json uses a different schema (e.g. plain Unity-style output),
the tracker also accepts a simplified format:
{
  "test_cases": [
    {"id": "test_name", "status": "PASS"}
  ]
}
In that case, coverage is computed from vector labels that appear in test IDs.
"""

from __future__ import annotations

import json
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, List, Optional, Set, Tuple


# ---------------------------------------------------------------------------
# Data structures
# ---------------------------------------------------------------------------

@dataclass
class VectorCoverage:
    """Coverage status for a single MC/DC test vector."""
    vector_label: str           # e.g. "TC-CBE-SM-001-01"
    expression_id: str
    row_id: int
    covered: bool               # True if executed by at least one test
    test_ids: List[str]         # which test functions covered it


@dataclass
class ExpressionCoverage:
    """MC/DC coverage for one expression."""
    expression_id: str
    file: str
    line: int
    function: str
    text: str
    operator: str
    num_conditions: int
    total_vectors: int          # |minimal_vectors|
    covered_vectors: int
    conditions_covered: int     # conditions with independence pair covered
    conditions_total: int
    coverage_pct: float         # covered_vectors / total_vectors * 100
    condition_coverage_pct: float
    independence_pairs_covered: List[dict]
    independence_pairs_missing: List[dict]
    is_fully_covered: bool


@dataclass
class CoverageReport:
    """Overall MC/DC coverage report."""
    project: str
    sil_level: int
    timestamp: str
    expressions: List[ExpressionCoverage]
    total_expressions: int
    fully_covered_expressions: int
    overall_coverage_pct: float     # fully_covered / total
    overall_vector_coverage_pct: float  # vectors covered / total vectors
    meets_sil3_requirement: bool    # True if 100% condition coverage
    gap_summary: List[str]          # human-readable gaps


# ---------------------------------------------------------------------------
# Loader
# ---------------------------------------------------------------------------

def load_vectors_json(vectors_path: str) -> dict:
    """Load the MC-DC-Vectors.json produced by the 'analyze' mode."""
    with open(vectors_path, 'r', encoding='utf-8') as f:
        return json.load(f)


def load_test_results(results_path: str) -> dict:
    """Load test-results.json."""
    with open(results_path, 'r', encoding='utf-8') as f:
        return json.load(f)


# ---------------------------------------------------------------------------
# Coverage computation
# ---------------------------------------------------------------------------

def _extract_covered_vector_labels(test_results: dict) -> Set[str]:
    """
    Extract the set of vector labels (TC-CBE-xxx-NN) that appear in passing
    test results.

    Handles two schemas:
      1. Structured: test_cases[].id is exactly a vector label
      2. Simple:     match vector labels appearing anywhere in test IDs
    """
    covered: Set[str] = set()
    test_cases = test_results.get('test_cases', [])

    for tc in test_cases:
        status = tc.get('status', 'FAIL').upper()
        if status not in ('PASS', 'PASSED', 'OK'):
            continue
        tc_id = tc.get('id', '')
        # Direct match: TC-CBE-XX-NNN-NN
        if tc_id.startswith('TC-CBE-'):
            covered.add(tc_id)
            continue
        # Fuzzy: look for TC-CBE pattern inside test function name or description
        import re
        matches = re.findall(r'TC-CBE-[A-Z]+-\d{3}-\d+', tc_id)
        for m in matches:
            covered.add(m)

    return covered


def _match_test_cases_to_vectors(
    test_results: dict,
    expression_id: str,
    vector_labels: List[str],
) -> Dict[str, List[str]]:
    """
    For each vector label, find which test cases (by test function) executed it.

    Returns: {vector_label: [test_function_id, ...]}
    """
    mapping: Dict[str, List[str]] = {v: [] for v in vector_labels}
    test_cases = test_results.get('test_cases', [])

    for tc in test_cases:
        status = tc.get('status', 'FAIL').upper()
        if status not in ('PASS', 'PASSED', 'OK'):
            continue
        tc_id = tc.get('id', '')
        expr_id = tc.get('expression_id', '')
        func = tc.get('test_function', tc_id)

        # Direct association by expression_id field
        if expr_id == expression_id:
            # Map by condition_values if available
            cond_vals = tc.get('condition_values', {})
            row_id = tc.get('row_id')
            if row_id is not None:
                label = f"TC-{expression_id}-{int(row_id)+1:02d}"
                if label in mapping:
                    mapping[label].append(func)
            # Also try by tc_id directly
            if tc_id in mapping:
                mapping[tc_id].append(func)
            continue

        # Fuzzy: match vector labels in tc_id
        import re
        for vlabel in vector_labels:
            if vlabel in tc_id or vlabel in func:
                mapping[vlabel].append(func)

    return mapping


def compute_coverage(
    vectors_data: dict,
    test_results: dict,
) -> CoverageReport:
    """
    Compute MC/DC coverage by mapping test results onto vector requirements.

    Args:
        vectors_data:   parsed MC-DC-Vectors.json
        test_results:   parsed test-results.json

    Returns:
        CoverageReport
    """
    import datetime

    project = vectors_data.get('project', 'unknown')
    sil_level = vectors_data.get('sil_level', 3)
    timestamp = datetime.datetime.utcnow().strftime('%Y-%m-%dT%H:%M:%SZ')

    covered_labels = _extract_covered_vector_labels(test_results)

    expression_coverages: List[ExpressionCoverage] = []
    total_vectors_all = 0
    covered_vectors_all = 0

    for expr_data in vectors_data.get('expressions', []):
        expr_id = expr_data['expr_id']
        minimal_vectors = expr_data.get('minimal_vectors', [])
        independence_pairs = expr_data.get('independence_pairs', {})
        num_conditions = expr_data.get('num_conditions', 0)

        vector_labels = [v['label'] for v in minimal_vectors]
        test_map = _match_test_cases_to_vectors(test_results, expr_id, vector_labels)

        total_vectors = len(minimal_vectors)
        covered_vectors = sum(1 for lbl in vector_labels
                              if lbl in covered_labels or bool(test_map.get(lbl)))

        total_vectors_all += total_vectors
        covered_vectors_all += covered_vectors

        # Check independence pairs
        pairs_covered = []
        pairs_missing = []
        conditions_covered_set: Set[int] = set()

        for cond_idx_str, pairs in independence_pairs.items():
            cond_idx = int(cond_idx_str)
            for pair in pairs:
                row_a_label = pair.get('row_a_label', '')
                row_b_label = pair.get('row_b_label', '')
                a_covered = (row_a_label in covered_labels or
                             bool(test_map.get(row_a_label)))
                b_covered = (row_b_label in covered_labels or
                             bool(test_map.get(row_b_label)))
                pair_info = {
                    'condition_index': cond_idx,
                    'condition_text': pair.get('condition_text', ''),
                    'row_a': row_a_label,
                    'row_b': row_b_label,
                    'row_a_covered': a_covered,
                    'row_b_covered': b_covered,
                    'pair_covered': a_covered and b_covered,
                }
                if a_covered and b_covered:
                    pairs_covered.append(pair_info)
                    conditions_covered_set.add(cond_idx)
                else:
                    pairs_missing.append(pair_info)

        conditions_covered = len(conditions_covered_set)
        conditions_total = num_conditions

        cov_pct = (covered_vectors / total_vectors * 100.0) if total_vectors else 0.0
        cond_cov_pct = (conditions_covered / conditions_total * 100.0) if conditions_total else 0.0
        is_fully_covered = (conditions_covered == conditions_total and
                            covered_vectors == total_vectors)

        expression_coverages.append(ExpressionCoverage(
            expression_id=expr_id,
            file=expr_data.get('file', ''),
            line=expr_data.get('line', 0),
            function=expr_data.get('function', ''),
            text=expr_data.get('text', ''),
            operator=expr_data.get('operator', ''),
            num_conditions=num_conditions,
            total_vectors=total_vectors,
            covered_vectors=covered_vectors,
            conditions_covered=conditions_covered,
            conditions_total=conditions_total,
            coverage_pct=cov_pct,
            condition_coverage_pct=cond_cov_pct,
            independence_pairs_covered=pairs_covered,
            independence_pairs_missing=pairs_missing,
            is_fully_covered=is_fully_covered,
        ))

    total_exprs = len(expression_coverages)
    fully_covered_exprs = sum(1 for e in expression_coverages if e.is_fully_covered)
    overall_cov = (fully_covered_exprs / total_exprs * 100.0) if total_exprs else 0.0
    overall_vec_cov = (covered_vectors_all / total_vectors_all * 100.0) if total_vectors_all else 0.0
    meets_sil3 = (fully_covered_exprs == total_exprs)

    # Build gap summary
    gap_summary: List[str] = []
    for ec in expression_coverages:
        if not ec.is_fully_covered:
            missing = ec.conditions_total - ec.conditions_covered
            gap_summary.append(
                f"{ec.expression_id} ({ec.function}:{ec.line}): "
                f"{ec.conditions_covered}/{ec.conditions_total} conditions covered "
                f"({missing} independence pair(s) missing)"
            )

    return CoverageReport(
        project=project,
        sil_level=sil_level,
        timestamp=timestamp,
        expressions=expression_coverages,
        total_expressions=total_exprs,
        fully_covered_expressions=fully_covered_exprs,
        overall_coverage_pct=overall_cov,
        overall_vector_coverage_pct=overall_vec_cov,
        meets_sil3_requirement=meets_sil3,
        gap_summary=gap_summary,
    )
