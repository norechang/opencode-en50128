# Tool Validation Suite — SAS/SDS Template Validator (validate_sas_sds_template.py)

**Status**: TO BE PROVIDED — required before ISA evaluation

**Tool**: `tools/scripts/validate_sas_sds_template.py`
**Origin**: Platform-developed
**TCL**: T2
**EN 50128 Reference**: Section 7.3, Section 7.4, Tables A.3/A.4, Section 6.7, Section 6.7.4.3
**Catalog Entry**: `tools/catalog/validate-sas-sds.yaml`

---

## Purpose

This directory contains the validation test suite for the platform-developed
SAS/SDS Template Validator (`validate_sas_sds_template.py`). This tool checks
Software Architecture Specification (SAS) and Software Design Specification (SDS)
documents against EN 50128 Section 7.3/7.4 template requirements, producing a
PASS/FAIL verdict that gates QUA acceptance of these deliverables.

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
- `tools/catalog/validate-sas-sds.yaml` — tool catalog entry
