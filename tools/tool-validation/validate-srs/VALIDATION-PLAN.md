# Validation Plan — SRS Template Validator (validate_srs_template.py)

**Document Status**: TO BE PROVIDED
**Tool**: `tools/scripts/validate_srs_template.py`
**TCL**: T2
**Origin**: Platform-developed
**EN 50128 Reference**: Section 7.2, Table A.2, Section 6.7.4.3
**Required For**: SIL 2-4 (mandatory formal report: SIL 3-4)
**Planned Report**: `deliverables/tools/ValidateSRS-Tool-Validation-Report.md`

---

## 1. Validation Objective

Demonstrate that `validate_srs_template.py` correctly validates Software Requirements
Specification documents against EN 50128 Section 7.2 template requirements, produces
accurate PASS/FAIL verdicts, correctly enforces SIL-specific approval requirements,
and provides meaningful diagnostic output for detected issues.

---

## 2. Test Environment

| Item | Requirement |
|------|-------------|
| Python version | 3.10+ |
| Test runner | bash or pytest |
| Reference documents | Pre-authored SRS Markdown files (compliant and non-compliant, see §3) |

---

## 3. Required Test Cases

### 3.1 Positive Cases (tool must PASS)

| Test ID | Input | Expected Output |
|---------|-------|-----------------|
| SRS-POS-001 | Fully compliant SRS, SIL 3 (all 8 approvers) | Exit 0, PASS verdict |
| SRS-POS-002 | Fully compliant SRS, SIL 1 (4 approvers) | Exit 0, PASS verdict |
| SRS-POS-003 | Fully compliant SRS, SIL 0 (4 approvers) | Exit 0, PASS verdict |

### 3.2 Document ID Validation

| Test ID | Defect | Expected Output |
|---------|--------|-----------------|
| SRS-ID-001 | Missing document ID entirely | FAIL, error identifies missing ID |
| SRS-ID-002 | Wrong ID format (e.g. DOC-DES-2026-001 instead of DOC-REQ) | FAIL, error identifies format issue |
| SRS-ID-003 | Correct format DOC-REQ-2026-001 | PASS for this check |

### 3.3 Approver Enforcement by SIL

| Test ID | SIL | Approvers in doc | Expected |
|---------|-----|------------------|----------|
| SRS-APR-001 | 3 | 8 approvers (all required) | PASS |
| SRS-APR-002 | 3 | 4 approvers (missing Independent Verifier, Validator, Assessor, Safety Mgr) | FAIL |
| SRS-APR-003 | 1 | 4 approvers (correct for SIL 1) | PASS |
| SRS-APR-004 | 1 | 3 approvers | FAIL |
| SRS-APR-005 | 2 | 5 approvers (includes Safety Manager) | PASS |

### 3.4 Required Sections

| Test ID | Defect | Expected Output |
|---------|--------|-----------------|
| SRS-SEC-001 | Missing "Functional Requirements" section | FAIL, section identified |
| SRS-SEC-002 | Missing "Introduction" section | FAIL, section identified |
| SRS-SEC-003 | Missing traceability section | FAIL or WARNING |
| SRS-SEC-004 | All required sections present | PASS for this check |

### 3.5 Requirements Format Validation

| Test ID | Defect | Expected Output |
|---------|--------|-----------------|
| SRS-FMT-001 | Requirement without SHALL/SHOULD/MAY keyword | WARNING or FAIL |
| SRS-FMT-002 | Requirement ID wrong format (e.g. R-001 instead of REQ-XXX-001) | WARNING or FAIL |
| SRS-FMT-003 | Correctly formatted requirements | PASS for this check |

### 3.6 Error Handling

| Test ID | Input | Expected Output |
|---------|-------|-----------------|
| SRS-ERR-001 | Non-existent file path | Exit non-zero, clear error, no crash |
| SRS-ERR-002 | Invalid SIL level (--sil 5) | Exit non-zero, clear error |
| SRS-ERR-003 | Non-Markdown file (binary) | Graceful failure |

---

## 4. Reference Test Documents

Pre-authored Markdown SRS test files stored in this directory:

```
tools/tool-validation/validate-srs/
  test-data/
    srs-compliant-sil3.md        # Fully compliant SRS for SIL 3
    srs-compliant-sil1.md        # Fully compliant SRS for SIL 1
    srs-missing-id.md            # Missing document ID
    srs-wrong-id-format.md       # Wrong ID prefix
    srs-missing-section.md       # Missing required section
    srs-wrong-approvers-sil3.md  # Only 4 approvers for SIL 3
    srs-bad-req-format.md        # Requirements without SHALL/SHOULD/MAY
```

---

## 5. Acceptance Criteria

- All positive cases: tool returns exit 0 and PASS verdict
- All negative cases: tool returns correct FAIL verdict with issue identified
- All error cases: graceful failure with no crashes
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
1. Author reference Markdown SRS test files for each test case
2. Create `run-validation.sh` to execute all tests and check verdicts
3. Execute suite, capture results
4. Complete `deliverables/tools/ValidateSRS-Tool-Validation-Report.md`
5. Obtain QUA, VER, and PM sign-off
