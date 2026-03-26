# Tool Validation Suite — Coverage Report Parser (parse_coverage_report.py)

**Status**: TO BE PROVIDED — required before ISA evaluation

**Tool**: `tools/scripts/parse_coverage_report.py`
**Origin**: Platform-developed
**TCL**: T2
**EN 50128 Reference**: Table A.21, Section 6.7, Section 6.7.4.3
**Catalog Entry**: `tools/catalog/parse-coverage-report.yaml`

---

## Purpose

This directory contains the validation test suite for the platform-developed
Coverage Report Parser (`parse_coverage_report.py`). This tool parses lcov
`coverage.info` files and produces a PASS/FAIL verdict against EN 50128 Table A.21
coverage thresholds. The verdict feeds directly into SIL phase gate decisions.

Because this is a **platform-developed T2 tool**, no supplier qualification evidence
exists. The project must produce all validation evidence independently.

See `VALIDATION-PLAN.md` in this directory for the detailed validation plan.

---

## Risk if Not Validated

If `parse_coverage_report.py` contains a calculation error, a falsely passing
coverage verdict could be accepted at a SIL gate. The ISA will require evidence
that the tool's coverage calculations are correct before accepting coverage reports
as compliance evidence.

---

## When This Must Be Complete

This validation suite must be completed and formally reviewed before:
1. Any SIL 2+ project submits to ISA evaluation
2. Coverage verdicts from this tool are cited in Verification Reports

---

## See Also

- `VALIDATION-PLAN.md` — detailed test plan
- `deliverables/tools/Tool-Validation-Report-template.md` — report template
- `tools/catalog/parse-coverage-report.yaml` — tool catalog entry
