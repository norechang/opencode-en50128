# Tool Validation Suite — SRS Template Validator (validate_srs_template.py)

**Status**: TO BE PROVIDED — required before ISA evaluation

**Tool**: `tools/scripts/validate_srs_template.py`
**Origin**: Platform-developed
**TCL**: T2
**EN 50128 Reference**: Section 7.2, Table A.2, Section 6.7, Section 6.7.4.3
**Catalog Entry**: `tools/catalog/validate-srs.yaml`

---

## Purpose

This directory contains the validation test suite for the platform-developed
SRS Template Validator (`validate_srs_template.py`). This tool checks SRS documents
against EN 50128 Section 7.2 template requirements and produces a PASS/FAIL verdict
that gates QUA acceptance of the SRS deliverable.

Because this is a **platform-developed T2 tool**, no supplier qualification evidence
exists. The project must produce all validation evidence independently.

See `VALIDATION-PLAN.md` in this directory for the detailed validation plan.

---

## When This Must Be Complete

This validation suite must be completed and formally reviewed before:
1. Any SIL 2+ project submits to ISA evaluation
2. The tool's PASS/FAIL verdicts are used in QUA gate acceptance records

---

## See Also

- `VALIDATION-PLAN.md` — detailed test plan
- `deliverables/tools/Tool-Validation-Report-template.md` — report template
- `tools/catalog/validate-srs.yaml` — tool catalog entry
