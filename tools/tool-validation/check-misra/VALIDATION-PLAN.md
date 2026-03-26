# Validation Plan — MISRA C Checker Wrapper (check_misra.py)

**Document Status**: TO BE PROVIDED
**Tool**: `tools/static-analysis/check_misra.py`
**TCL**: T2
**Origin**: Platform-developed
**EN 50128 Reference**: Table A.19, Section 6.7.4.3
**Required For**: SIL 1-4 (mandatory formal report: SIL 3-4)
**Planned Report**: `deliverables/tools/MisraChecker-Tool-Validation-Report.md`

---

## 1. Validation Objective

Demonstrate that `check_misra.py` correctly wraps Cppcheck with the MISRA C:2012
addon, correctly generates a compliance report, and produces the correct pass/fail
verdict for all tested scenarios.

Note: this validation covers the **wrapper layer only**. Cppcheck itself requires
separate validation (see `tools/tool-validation/cppcheck/`).

---

## 2. Test Environment

| Item | Requirement |
|------|-------------|
| Python version | 3.10+ |
| Cppcheck version | 2.13.0 (baselined, validated separately) |
| MISRA addon | misra.py (bundled with Cppcheck) |
| OS | Linux (Ubuntu 22.04 LTS) |
| Test runner | bash or pytest |

---

## 3. Required Test Cases

### 3.1 Positive Cases (tool must PASS)

| Test ID | Input | Expected Output |
|---------|-------|-----------------|
| MCW-POS-001 | Clean C file with no MISRA violations | Exit 0, report shows PASS, zero violations |
| MCW-POS-002 | Multiple clean C files in a directory | Exit 0, all files analysed, zero violations |

### 3.2 Negative Cases (tool must FAIL and report correctly)

| Test ID | Input | Expected Output |
|---------|-------|-----------------|
| MCW-NEG-001 | C file with MISRA Rule 15.5 violation (multiple return statements) | Exit non-zero, report shows FAIL, violation listed |
| MCW-NEG-002 | C file with MISRA Rule 8.7 violation (non-local linkage) | Exit non-zero, violation listed with rule number |
| MCW-NEG-003 | C file with MISRA Rule 10.1 violation (inappropriate essential type) | Exit non-zero, violation listed |
| MCW-NEG-004 | C file with MISRA Rule 17.7 violation (return value ignored) | Exit non-zero, violation listed |
| MCW-NEG-005 | C file with multiple simultaneous violations | Exit non-zero, all violations listed |

### 3.3 Boundary / Error Cases

| Test ID | Input | Expected Output |
|---------|-------|-----------------|
| MCW-BND-001 | Non-existent source directory | Exit non-zero, error message, no crash |
| MCW-BND-002 | Empty source directory | Exit 0, report shows "no files analysed" or equivalent |
| MCW-BND-003 | Cppcheck not installed | Graceful failure with clear error message |

### 3.4 Report Format Cases

| Test ID | Verification | Expected Output |
|---------|-------------|-----------------|
| MCW-FMT-001 | Report output format | Report is valid Markdown, includes tool version, date, PASS/FAIL verdict |
| MCW-FMT-002 | Violation detail format | Each violation includes: file, line number, rule number, description |

---

## 4. Acceptance Criteria

- All positive cases: tool returns exit code 0 and PASS verdict
- All negative cases: tool returns non-zero exit code and correct FAIL verdict
- All boundary cases: no crashes; graceful error handling
- All format cases: report conforms to required structure
- **Minimum 80% of specified tests must pass** for SIL 1-2
- **100% of specified tests must pass** for SIL 3-4

---

## 5. Regression Requirements

After any change to `check_misra.py`, the full validation suite must be re-run
and pass before the updated tool version can be used in project work.

---

## 6. Sign-off Requirements

| Role | Action |
|------|--------|
| QUA | Review and approve validation test suite and results |
| VER | Independent review of validation results |
| PM  | Accept completed validation report into SCMP baseline |

---

## 7. Status

**Current Status**: PLANNED — test cases defined, implementation pending.

To implement this plan:
1. Create test C files for each test case in this directory
2. Create a `run-validation.sh` script that executes all tests and reports results
3. Execute the suite and capture results
4. Complete `deliverables/tools/MisraChecker-Tool-Validation-Report.md`
5. Obtain QUA, VER, and PM sign-off
