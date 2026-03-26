# Validation Plan — SAS/SDS Template Validator (validate_sas_sds_template.py)

**Document Status**: TO BE PROVIDED
**Tool**: `tools/scripts/validate_sas_sds_template.py`
**TCL**: T2
**Origin**: Platform-developed
**EN 50128 Reference**: Section 7.3, Section 7.4, Tables A.3/A.4, Section 6.7.4.3
**Required For**: SIL 2-4 (mandatory formal report: SIL 3-4)
**Planned Report**: `deliverables/tools/ValidateSASSDS-Tool-Validation-Report.md`

---

## 1. Validation Objective

Demonstrate that `validate_sas_sds_template.py` correctly validates Software
Architecture Specification (SAS) and Software Design Specification (SDS) documents
against EN 50128 Section 7.3/7.4 template requirements, produces accurate PASS/FAIL
verdicts, enforces document-type-specific requirements (SAS vs. SDS checks differ),
and correctly enforces SIL-specific requirements.

---

## 2. Test Environment

| Item | Requirement |
|------|-------------|
| Python version | 3.10+ |
| Test runner | bash or pytest |
| Reference documents | Pre-authored SAS and SDS Markdown files (see §3) |

---

## 3. Required Test Cases

### 3.1 Positive Cases

| Test ID | Input | Expected Output |
|---------|-------|-----------------|
| SAS-POS-001 | Fully compliant SAS, SIL 3 | Exit 0, PASS verdict |
| SAS-POS-002 | Fully compliant SDS, SIL 3 | Exit 0, PASS verdict |
| SAS-POS-003 | Compliant SAS, SIL 1 | Exit 0, PASS verdict |
| SAS-POS-004 | Compliant SDS, SIL 1 | Exit 0, PASS verdict |

### 3.2 Document ID Validation

| Test ID | Defect | Expected Output |
|---------|--------|-----------------|
| SAS-ID-001 | Missing document ID | FAIL, error identifies missing ID |
| SAS-ID-002 | Wrong prefix (e.g. DOC-REQ instead of DOC-DES) | FAIL |
| SAS-ID-003 | Correct DOC-DES-SAS-001 format | PASS for this check |
| SAS-ID-004 | Correct DOC-DES-SDS-001 format | PASS for this check |

### 3.3 Document-Type-Specific Checks

| Test ID | Type | Defect | Expected Output |
|---------|------|--------|-----------------|
| SAS-DTYPE-001 | SAS | Missing architecture diagrams section | FAIL (SAS-only check) |
| SAS-DTYPE-002 | SDS | Architecture diagrams section not required | No error raised for SDS |
| SAS-DTYPE-003 | SAS | Modular approach not documented (SIL 2+) | FAIL |
| SAS-DTYPE-004 | SDS | Component decomposition section present | PASS |
| SAS-DTYPE-005 | SAS | Interface specifications missing | FAIL |
| SAS-DTYPE-006 | SDS | Interface specifications missing | FAIL |

### 3.4 Traceability Checks

| Test ID | Defect | Expected Output |
|---------|--------|-----------------|
| SAS-TRC-001 | No traceability to SRS | FAIL or WARNING |
| SAS-TRC-002 | Traceability section present with SRS references | PASS for this check |

### 3.5 Design Constraints (SIL 2+)

| Test ID | Defect | Expected Output |
|---------|--------|-----------------|
| SAS-CON-001 | MISRA C compliance statement missing (SIL 3) | FAIL |
| SAS-CON-002 | Static allocation requirement missing (SIL 3) | FAIL |
| SAS-CON-003 | Complexity limits missing (SIL 3) | FAIL |
| SAS-CON-004 | All constraints documented (SIL 3) | PASS |

### 3.6 Error Handling

| Test ID | Input | Expected Output |
|---------|-------|-----------------|
| SAS-ERR-001 | Non-existent file | Exit non-zero, clear error, no crash |
| SAS-ERR-002 | Missing --type argument | Exit non-zero, usage message |
| SAS-ERR-003 | Invalid type value (--type xyz) | Exit non-zero, clear error |

---

## 4. Reference Test Documents

```
tools/tool-validation/validate-sas-sds/
  test-data/
    sas-compliant-sil3.md          # Fully compliant SAS for SIL 3
    sas-compliant-sil1.md          # Fully compliant SAS for SIL 1
    sds-compliant-sil3.md          # Fully compliant SDS for SIL 3
    sds-compliant-sil1.md          # Fully compliant SDS for SIL 1
    sas-missing-diagrams.md        # SAS without architecture diagrams
    sas-missing-constraints.md     # SAS without design constraints
    sas-missing-traceability.md    # SAS without SRS traceability
    sas-wrong-id.md                # Wrong document ID prefix
```

---

## 5. Acceptance Criteria

- All positive cases: tool returns exit 0 and PASS verdict
- All negative cases: correct FAIL verdict with specific issue identified
- Document-type-specific checks: SAS-only checks not triggered for SDS (and vice versa)
- All error cases: graceful failure, no crashes
- **100% of specified tests must pass** for SIL 3-4 use

---

## 6. Sign-off Requirements

| Role | Action |
|------|--------|
| QUA | Review and approve validation test suite and results |
| VER | Independent review of validation results |
| PM  | Accept completed validation report into SCMP baseline |

---

## 7. Status

**Current Status**: PLANNED — test cases defined, reference documents and implementation pending.

To implement:
1. Author reference Markdown SAS/SDS test files for each test case
2. Create `run-validation.sh` to execute all tests and check verdicts
3. Execute suite, capture results
4. Complete `deliverables/tools/ValidateSASSDS-Tool-Validation-Report.md`
5. Obtain QUA, VER, and PM sign-off
