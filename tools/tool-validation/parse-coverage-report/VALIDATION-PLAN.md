# Validation Plan — Coverage Report Parser (parse_coverage_report.py)

**Document Status**: TO BE PROVIDED
**Tool**: `tools/scripts/parse_coverage_report.py`
**TCL**: T2
**Origin**: Platform-developed
**EN 50128 Reference**: Table A.21, Section 6.7.4.3
**Required For**: SIL 2-4 (mandatory formal report: SIL 3-4)
**Planned Report**: `deliverables/tools/ParseCoverageReport-Tool-Validation-Report.md`

---

## 1. Validation Objective

Demonstrate that `parse_coverage_report.py` correctly parses lcov `coverage.info`
files, correctly computes statement, branch, and function coverage percentages, and
correctly enforces EN 50128 Table A.21 thresholds by SIL level, returning correct
PASS/FAIL verdicts and exit codes.

---

## 2. Test Environment

| Item | Requirement |
|------|-------------|
| Python version | 3.10+ |
| lcov version | 1.16 (to generate reference coverage.info files) |
| Test runner | bash or pytest |
| Reference files | Pre-computed coverage.info files with known percentages (see §3) |

---

## 3. Required Test Cases

### 3.1 Coverage Calculation Accuracy

| Test ID | Input | Known Ground Truth | Expected Output |
|---------|-------|--------------------|-----------------|
| PCP-CALC-001 | coverage.info: 100/100 lines instrumented, 100 executed | 100% statement | Parser reports 100.0% |
| PCP-CALC-002 | coverage.info: 100/100 lines, 80 executed | 80% statement | Parser reports 80.0% |
| PCP-CALC-003 | coverage.info: 50 branches total, 45 taken | 90% branch | Parser reports 90.0% ±0.1% |
| PCP-CALC-004 | coverage.info: multiple source files | Aggregate % | Correct aggregate, correct per-file breakdown |
| PCP-CALC-005 | coverage.info: functions tracked (FN/FNDA) | Function coverage % | Correct function coverage |

### 3.2 SIL Threshold Enforcement

| Test ID | SIL | Coverage | Threshold | Expected Verdict |
|---------|-----|----------|-----------|-----------------|
| PCP-SIL-001 | 2 | Branch: 100% | Branch mandatory | PASS (exit 0) |
| PCP-SIL-002 | 2 | Branch: 95% | Branch mandatory | FAIL (exit 1) |
| PCP-SIL-003 | 3 | Statement: 100%, Branch: 100% | Both mandatory | PASS (exit 0) |
| PCP-SIL-004 | 3 | Statement: 100%, Branch: 95% | Both mandatory | FAIL (exit 1) |
| PCP-SIL-005 | 1 | Statement: 70%, Branch: 60% | Both HR (not mandatory) | PASS with warnings (exit 0) |
| PCP-SIL-006 | 0 | Statement: 50% | Recommended only | PASS (exit 0) |

### 3.3 Uncovered Code Reporting

| Test ID | Input | Expected Output |
|---------|-------|-----------------|
| PCP-RPT-001 | coverage.info with known uncovered lines | Report lists uncovered lines with file:line |
| PCP-RPT-002 | coverage.info: full coverage | Report states "No uncovered code" or zero uncovered locations |

### 3.4 Error Handling

| Test ID | Input | Expected Output |
|---------|-------|-----------------|
| PCP-ERR-001 | Non-existent coverage.info path | Exit non-zero, clear error message, no crash |
| PCP-ERR-002 | Malformed/corrupt coverage.info | Graceful failure with parse error message |
| PCP-ERR-003 | Empty coverage.info | Graceful handling, report 0% or error |
| PCP-ERR-004 | Invalid SIL level (e.g. --sil 5) | Exit non-zero, clear error message |

---

## 4. Reference Coverage.info Files

Pre-computed `coverage.info` files must be created for each test case and stored
in this directory. These files represent known states:

```
tools/tool-validation/parse-coverage-report/
  test-data/
    full-coverage.info          # 100% statement, 100% branch
    partial-statement.info      # 80% statement, 100% branch
    partial-branch.info         # 100% statement, 90% branch
    multi-file.info             # Multiple source files with known aggregate %
    uncovered-lines.info        # Known set of uncovered lines
    empty.info                  # Empty file
    malformed.info              # Deliberately corrupt
```

---

## 5. Acceptance Criteria

- All calculation tests: computed percentages within ±0.1% of ground truth
- All SIL threshold tests: correct PASS/FAIL verdict and exit code
- All error handling tests: graceful failure, no unhandled exceptions
- **100% of specified tests must pass** for SIL 3-4 use

---

## 6. Regression Requirements

After any change to `parse_coverage_report.py`, the full validation suite must
be re-run before the updated version can be used in project work.

---

## 7. Sign-off Requirements

| Role | Action |
|------|--------|
| QUA | Review and approve validation test suite and results |
| VER | Independent review of validation results |
| PM  | Accept completed validation report into SCMP baseline |

---

## 8. Status

**Current Status**: PLANNED — test cases defined, reference data and implementation pending.

To implement this plan:
1. Generate reference `coverage.info` files using a known test program + lcov
2. Create `run-validation.sh` script that executes all tests and checks verdicts
3. Execute the suite and capture results
4. Complete `deliverables/tools/ParseCoverageReport-Tool-Validation-Report.md`
5. Obtain QUA, VER, and PM sign-off
