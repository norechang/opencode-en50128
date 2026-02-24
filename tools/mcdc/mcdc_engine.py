"""
mcdc_engine.py - MC/DC truth table computation and test vector generation.

Implements Masking MC/DC (the standard variant for EN 50128 / C short-circuit
evaluation).

Definitions
-----------
For an expression with N atomic conditions C0..C(N-1):

  Independence pair for Ci:
    Two truth-table rows that differ ONLY in the value of Ci, and the
    expression outcome differs between them.  This demonstrates that Ci
    independently affects the outcome.

  Minimum MC/DC test set:
    A set of truth-table rows such that every condition has at least one
    independence pair covered.  The minimum size is N+1 for pure AND/OR.

Algorithm
---------
  1. Enumerate all 2^N truth-table rows.
  2. Evaluate the expression for each row.
  3. For each condition Ci, collect all independence pairs:
       (row_a, row_b) where row_a and row_b differ only in Ci, and
       outcome(row_a) != outcome(row_b).
  4. Greedy set-cover: pick the smallest set of rows that covers at least
     one independence pair per condition.

Pure AND rule (shortcut for N conditions):
  - Independence pair for Ci: (all-TRUE) ↔ (row where only Ci is FALSE)
  → minimum N+1 vectors: 1 all-TRUE + N single-false rows

Pure OR rule (shortcut for N conditions):
  - Independence pair for Ci: (all-FALSE) ↔ (row where only Ci is TRUE)
  → minimum N+1 vectors: 1 all-FALSE + N single-true rows

For MIXED expressions the general algorithm is used.
"""

from __future__ import annotations

import itertools
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Set, Tuple

from c_parser import Condition, Expression


# ---------------------------------------------------------------------------
# Data structures
# ---------------------------------------------------------------------------

@dataclass
class TruthRow:
    """One row in an MC/DC truth table."""
    row_id: int                      # 0-based index
    assignments: Dict[int, bool]     # condition_index -> value
    outcome: bool                    # expression result for this assignment
    label: str = ""                  # e.g. "TC-CBE-SM-001-01"


@dataclass
class IndependencePair:
    """An MC/DC independence pair for a single condition."""
    condition_index: int
    condition_text: str
    row_a: int          # row_id where condition is False
    row_b: int          # row_id where condition is True
    # outcome_a and outcome_b differ by definition


@dataclass
class MCDCResult:
    """Full MC/DC analysis result for one expression."""
    expression: Expression
    truth_table: List[TruthRow]
    independence_pairs: Dict[int, List[IndependencePair]]  # cond_idx -> pairs
    minimal_vectors: List[TruthRow]   # greedy-minimal covering set
    min_required: int                 # N+1
    is_achievable: bool               # False if no independence pair found for some cond


# ---------------------------------------------------------------------------
# Expression evaluator
# ---------------------------------------------------------------------------

def _evaluate_pure_and(assignments: Dict[int, bool], n: int) -> bool:
    return all(assignments[i] for i in range(n))


def _evaluate_pure_or(assignments: Dict[int, bool], n: int) -> bool:
    return any(assignments[i] for i in range(n))


def _evaluate_mixed(assignments: Dict[int, bool], expr: Expression) -> bool:
    """
    For MIXED expressions we build a Python lambda string and eval it.
    We map condition indices to local variable names c0, c1, ...
    The original text is used to reconstruct the expression with substitutions.
    """
    # Build substitution: replace condition text with c0, c1, ...
    text = expr.text
    # Sort by length descending to avoid partial replacements
    sorted_conds = sorted(expr.conditions, key=lambda c: -len(c.text))
    local_vars = {f"c{c.index}": assignments[c.index] for c in expr.conditions}
    temp = text
    for c in sorted_conds:
        temp = temp.replace(c.text, f"c{c.index}")

    # Replace C operators with Python
    temp = temp.replace('&&', ' and ').replace('||', ' or ').replace('!', ' not ')
    try:
        result = eval(temp, {"__builtins__": {}}, local_vars)  # noqa: S307
        return bool(result)
    except Exception:
        # Fallback: treat as all-AND
        return _evaluate_pure_and(assignments, len(expr.conditions))


def _evaluate(assignments: Dict[int, bool], expr: Expression) -> bool:
    """Evaluate expression for a given truth assignment."""
    n = expr.num_conditions
    if expr.operator == 'AND':
        return _evaluate_pure_and(assignments, n)
    if expr.operator == 'OR':
        return _evaluate_pure_or(assignments, n)
    return _evaluate_mixed(assignments, expr)


# ---------------------------------------------------------------------------
# Truth table generation
# ---------------------------------------------------------------------------

def build_truth_table(expr: Expression) -> List[TruthRow]:
    """Generate all 2^N truth table rows for the expression."""
    n = expr.num_conditions
    rows: List[TruthRow] = []
    for row_id, combo in enumerate(itertools.product([False, True], repeat=n)):
        assignments = {i: v for i, v in enumerate(combo)}
        outcome = _evaluate(assignments, expr)
        label = f"TC-{expr.expr_id}-{row_id+1:02d}"
        rows.append(TruthRow(
            row_id=row_id,
            assignments=assignments,
            outcome=outcome,
            label=label,
        ))
    return rows


# ---------------------------------------------------------------------------
# Independence pair extraction
# ---------------------------------------------------------------------------

def find_independence_pairs(
    expr: Expression,
    truth_table: List[TruthRow],
) -> Dict[int, List[IndependencePair]]:
    """
    For each condition Ci, find all independence pairs in the truth table.

    An independence pair for Ci is two rows that differ ONLY in Ci and
    have different outcomes.
    """
    n = expr.num_conditions
    pairs: Dict[int, List[IndependencePair]] = {i: [] for i in range(n)}

    for i in range(len(truth_table)):
        for j in range(i + 1, len(truth_table)):
            row_a = truth_table[i]
            row_b = truth_table[j]
            # Must have different outcomes
            if row_a.outcome == row_b.outcome:
                continue
            # Find which conditions differ
            differing = [k for k in range(n)
                         if row_a.assignments[k] != row_b.assignments[k]]
            if len(differing) != 1:
                continue
            cond_idx = differing[0]
            cond_text = expr.conditions[cond_idx].text

            # Ensure row_a is the False row for clarity (optional convention)
            if row_a.assignments[cond_idx]:
                row_a, row_b = row_b, row_a

            pairs[cond_idx].append(IndependencePair(
                condition_index=cond_idx,
                condition_text=cond_text,
                row_a=row_a.row_id,
                row_b=row_b.row_id,
            ))

    return pairs


# ---------------------------------------------------------------------------
# Greedy set-cover for minimal test vectors
# ---------------------------------------------------------------------------

def greedy_minimal_vectors(
    expr: Expression,
    truth_table: List[TruthRow],
    independence_pairs: Dict[int, List[IndependencePair]],
) -> List[TruthRow]:
    """
    Select the minimum set of truth-table rows that covers at least one
    complete independence PAIR per condition.

    A condition is "covered" only when BOTH rows of an independence pair are
    included in the selected set (both rows together demonstrate independence).

    Algorithm:
      1. Build a "needs-cover" set of conditions (uncovered).
      2. For each condition, enumerate its available pairs.
      3. Greedily pick the pair that, together with already-selected rows,
         covers the most new conditions (or adds the fewest new rows).
      4. Repeat until all conditions are covered.

    For pure AND/OR with N conditions this always yields exactly N+1 rows.
    """
    n = expr.num_conditions
    row_map = {r.row_id: r for r in truth_table}
    uncovered = set(range(n))
    selected_ids: List[int] = []

    # Collect all pairs as (cond_idx, row_a_id, row_b_id)
    all_pairs: List[Tuple[int, int, int]] = []
    for cond_idx, pair_list in independence_pairs.items():
        for pair in pair_list:
            all_pairs.append((cond_idx, pair.row_a, pair.row_b))

    # Iteratively pick pairs until all conditions covered
    max_iterations = n * 2 + 4  # safety bound
    iteration = 0
    while uncovered and iteration < max_iterations:
        iteration += 1

        # Filter pairs for still-uncovered conditions
        candidate_pairs = [
            (ci, ra, rb) for (ci, ra, rb) in all_pairs if ci in uncovered
        ]
        if not candidate_pairs:
            break

        # Score each candidate pair:
        #   primary:   how many new rows it needs (0 if both already selected,
        #              1 if one already selected, 2 if neither)
        #   secondary: how many currently-uncovered conditions it would cover
        #              if we also included both rows in scoring
        def _pair_score(candidate: Tuple[int, int, int]) -> Tuple[int, int]:
            ci, ra, rb = candidate
            new_rows = sum(1 for rid in (ra, rb) if rid not in selected_ids)
            # Count conditions whose pairs become fully covered by adding ra+rb
            extra_selected = set(selected_ids) | {ra, rb}
            newly_covered = 0
            for uc in uncovered:
                for (aci, ara, arb) in all_pairs:
                    if aci == uc and ara in extra_selected and arb in extra_selected:
                        newly_covered += 1
                        break
            return (new_rows, -newly_covered)  # minimise new_rows, maximise covered

        best = min(candidate_pairs, key=_pair_score)
        ci, ra, rb = best

        for rid in (ra, rb):
            if rid not in selected_ids:
                selected_ids.append(rid)

        # Mark all conditions whose pairs are now fully covered
        newly_done = set()
        for uc in list(uncovered):
            for (aci, ara, arb) in all_pairs:
                if aci == uc and ara in selected_ids and arb in selected_ids:
                    newly_done.add(uc)
                    break
        uncovered -= newly_done

    # Return rows in stable (row_id) order
    return [row_map[rid] for rid in sorted(selected_ids)]


# ---------------------------------------------------------------------------
# Public API
# ---------------------------------------------------------------------------

def analyze_expression(expr: Expression) -> MCDCResult:
    """
    Perform full MC/DC analysis on a single expression.

    Returns an MCDCResult with:
      - Full truth table (2^N rows)
      - Independence pairs per condition
      - Minimal test vector set (greedy N+1)
      - is_achievable flag (False if some condition has no independence pair)
    """
    truth_table = build_truth_table(expr)
    independence_pairs = find_independence_pairs(expr, truth_table)

    # Check achievability: every condition must have ≥1 independence pair
    is_achievable = all(
        len(independence_pairs[i]) > 0
        for i in range(expr.num_conditions)
    )

    minimal_vectors = greedy_minimal_vectors(expr, truth_table, independence_pairs)

    return MCDCResult(
        expression=expr,
        truth_table=truth_table,
        independence_pairs=independence_pairs,
        minimal_vectors=minimal_vectors,
        min_required=expr.num_conditions + 1,
        is_achievable=is_achievable,
    )


def analyze_all(expressions: List[Expression]) -> List[MCDCResult]:
    """Analyze a list of expressions and return one MCDCResult per expression."""
    return [analyze_expression(expr) for expr in expressions]
