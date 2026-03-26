# Tool Validation Suite — MISRA C Checker Wrapper (check_misra.py)

**Status**: TO BE PROVIDED — required before ISA evaluation

**Tool**: `tools/static-analysis/check_misra.py`
**Origin**: Platform-developed
**TCL**: T2
**EN 50128 Reference**: Table A.19, Section 6.7, Section 6.7.4.3
**Catalog Entry**: `tools/catalog/misra-checker.yaml`

---

## Purpose

This directory contains the validation test suite for the platform-developed
MISRA C Checker Wrapper (`check_misra.py`). This tool wraps Cppcheck with the
MISRA C:2012 addon and produces a compliance report used in SIL gate decisions.

Because this is a **platform-developed T2 tool**, no supplier qualification evidence
exists. The project must produce all validation evidence independently.

See `VALIDATION-PLAN.md` in this directory for the detailed validation plan.

---

## Relationship to Cppcheck Validation

`check_misra.py` wraps Cppcheck. Both tools require independent validation:

- **Cppcheck** (third-party T2): see `tools/tool-validation/cppcheck/`
- **check_misra.py** (platform-developed T2): this directory

The wrapper validation focuses on the **wrapper layer** — correct invocation of
Cppcheck, correct report generation, and correct pass/fail verdict — not on the
underlying Cppcheck detection capabilities.

---

## When This Must Be Complete

This validation suite must be completed and formally reviewed before:
1. Any SIL 2+ project submits to ISA evaluation
2. The tool's output is used as evidence in a Verification Report

---

## See Also

- `VALIDATION-PLAN.md` — detailed test plan
- `deliverables/tools/Tool-Validation-Report-template.md` — report template
- `tools/catalog/misra-checker.yaml` — tool catalog entry
