# Traceability Verification Workflow for EN 50128

**Purpose**: Step-by-step workflow for verifying bidirectional traceability from requirements through design, code, and tests.

**Scope**: All lifecycle phases - ensures complete traceability per EN 50128 Table A.5 Technique 7 (MANDATORY SIL 3-4).

**Audience**: Verifiers (VER), Requirements Engineers (REQ), Designers (DES), Implementers (IMP)

**EN 50128 Reference**: 
- Table A.5, Technique 7 "Traceability" (**MANDATORY** SIL 3-4)
- Section 6.2.4.9(h) "Structure and content of each verification step"
- Annex D.58 "Traceability"

**Related Documents**:
- `workflows/verification-planning.md` - Traceability strategy
- `resources/traceability-verification-checklist.md` - Completeness checklist
- `resources/verification-tools-reference.md` - Traceability tools

---

## Table of Contents

1. [Traceability Overview](#1-traceability-overview)
2. [Prerequisites](#2-prerequisites)
3. [Step 1: Verify Requirements-to-Design Traceability](#step-1-verify-requirements-to-design-traceability)
4. [Step 2: Verify Design-to-Code Traceability](#step-2-verify-design-to-code-traceability)
5. [Step 3: Verify Code-to-Test Traceability](#step-3-verify-code-to-test-traceability)
6. [Step 4: Verify Backward Traceability](#step-4-verify-backward-traceability)
7. [Step 5: Generate Traceability Matrix](#step-5-generate-traceability-matrix)
8. [Step 6: Identify Traceability Gaps](#step-6-identify-traceability-gaps)
9. [Step 7: Verify Safety Requirements Traceability](#step-7-verify-safety-requirements-traceability)
10. [Step 8: Generate Traceability Report](#step-8-generate-traceability-report)

---

## 1. Traceability Overview

### EN 50128 Traceability Requirements

**Table A.5, Technique 7**: Traceability (**MANDATORY** SIL 3-4, Highly Recommended SIL 2)

**Purpose**: Demonstrate that:
- All requirements are implemented in design
- All design elements are implemented in code
- All code is verified by tests
- Nothing is implemented without a requirement (no "gold plating")

### Traceability Chain

```
System Requirements
        ↓ (forward)
Software Requirements (SRS)
        ↓ (forward)
Software Architecture (SAS)
        ↓ (forward)
Software Design (SDS)
        ↓ (forward)
Source Code
        ↓ (forward)
Unit Tests / Integration Tests
        ↓ (forward)
Validation Tests
        
        ↑ (backward)
[All levels traced back to requirements]
```

### Traceability Tag Format

**Standard format** used throughout project:

```c
/**
 * @brief Calculate train speed from wheel sensor pulses
 * @trace REQ-FUNC-001 Train speed calculation algorithm
 * @trace DES-ARCH-003 Speed calculation module
 * @trace DES-COMP-015 calculate_speed() function design
 * @sil 4
 */
uint32_t calculate_speed(sensor_t* sensor, uint32_t time_ms) {
    // Implementation
}
```

**Test traceability**:

```c
/**
 * @test Test calculate_speed() with valid inputs
 * @trace REQ-FUNC-001 Train speed calculation
 * @trace CODE-FUNC-calculate_speed
 */
void test_calculate_speed_valid(void) {
    // Test implementation
}
```

---

## 2. Prerequisites

### Required Documents

- Software Requirements Specification (DOC-SRS-YYYY-NNN)
- Software Architecture Specification (DOC-SAS-YYYY-NNN)
- Software Design Specification (DOC-SDS-YYYY-NNN)
- Source code with @trace tags
- Unit test code with @trace tags

### Required Tools

```bash
# Python traceability tools
python3 tools/traceability/extract_traces.py --help
python3 tools/traceability/check_traceability.py --help
python3 tools/traceability/generate_matrix.py --help

# Install dependencies
pip3 install pyyaml jinja2 graphviz
```

---

## Step 1: Verify Requirements-to-Design Traceability

### 1.1 Extract Requirement IDs from SRS

```bash
# Extract all requirement IDs from SRS
python3 tools/traceability/extract_traces.py \
    --input DOC-SRS-*.md \
    --type requirements \
    --output traces/requirements.yaml

# Expected format:
# - REQ-FUNC-001: Train speed calculation algorithm
# - REQ-FUNC-002: Emergency brake activation
# - REQ-SAF-001: Safe state entry within 100ms
# - ...
```

### 1.2 Extract Design Traces from SAS/SDS

```bash
# Extract design elements with requirement traces
python3 tools/traceability/extract_traces.py \
    --input DOC-SAS-*.md DOC-SDS-*.md \
    --type design \
    --output traces/design.yaml

# Expected format:
# - DES-ARCH-003:
#     description: Speed calculation module
#     traces: [REQ-FUNC-001]
# - DES-COMP-015:
#     description: calculate_speed() function
#     traces: [REQ-FUNC-001, DES-ARCH-003]
```

### 1.3 Check Requirements Coverage

```bash
# Check that all requirements are traced to design
python3 tools/traceability/check_traceability.py \
    --source traces/requirements.yaml \
    --target traces/design.yaml \
    --direction forward \
    --output reports/traceability/req-to-design.txt

# Expected output:
# Requirements traced to design: 48/50 (96%)
# Orphan requirements (no design):
#   - REQ-FUNC-042: Data logging (not yet designed)
#   - REQ-PERF-003: Response time < 10ms (missing trace in design)
```

**SIL 3-4 Requirement**: 100% coverage (all requirements traced)

**Action**: For any orphan requirements:
1. Add missing design elements, OR
2. Document rationale if requirement deferred

---

## Step 2: Verify Design-to-Code Traceability

### 2.1 Extract Code Traces

```bash
# Extract @trace tags from source code
python3 tools/traceability/extract_traces.py \
    --input src/*.c include/*.h \
    --type code \
    --output traces/code.yaml

# Expected format:
# - CODE-FUNC-calculate_speed:
#     file: src/speed_calc.c
#     line: 120
#     traces: [REQ-FUNC-001, DES-ARCH-003, DES-COMP-015]
```

### 2.2 Check Design Coverage in Code

```bash
# Check that all design elements are implemented
python3 tools/traceability/check_traceability.py \
    --source traces/design.yaml \
    --target traces/code.yaml \
    --direction forward \
    --output reports/traceability/design-to-code.txt

# Expected output:
# Design elements implemented: 45/45 (100%) ✓
# Orphan design elements: 0
```

**SIL 3-4 Requirement**: 100% coverage

---

## Step 3: Verify Code-to-Test Traceability

### 3.1 Extract Test Traces

```bash
# Extract @trace tags from test code
python3 tools/traceability/extract_traces.py \
    --input tests/*.c \
    --type tests \
    --output traces/tests.yaml

# Expected format:
# - TEST-test_calculate_speed_valid:
#     file: tests/test_speed_calc.c
#     line: 45
#     traces: [REQ-FUNC-001, CODE-FUNC-calculate_speed]
```

### 3.2 Check Code Coverage by Tests

```bash
# Check that all code is tested
python3 tools/traceability/check_traceability.py \
    --source traces/code.yaml \
    --target traces/tests.yaml \
    --direction forward \
    --output reports/traceability/code-to-test.txt

# Expected output:
# Code functions tested: 120/120 (100%) ✓
# Untested functions: 0
```

**SIL 3-4 Requirement**: 100% coverage (all functions tested)

---

## Step 4: Verify Backward Traceability

### 4.1 Check Backward Traceability from Tests

```bash
# Verify all tests trace back to requirements
python3 tools/traceability/check_traceability.py \
    --source traces/tests.yaml \
    --target traces/requirements.yaml \
    --direction backward \
    --output reports/traceability/test-to-req.txt

# Expected output:
# Tests traced to requirements: 250/250 (100%) ✓
# Orphan tests (no requirement): 0
```

**Purpose**: Ensure no unnecessary tests (gold plating)

---

## Step 5: Generate Traceability Matrix

### 5.1 Generate Complete Traceability Matrix

```bash
# Generate full traceability matrix (Requirements → Design → Code → Tests)
python3 tools/traceability/generate_matrix.py \
    --requirements traces/requirements.yaml \
    --design traces/design.yaml \
    --code traces/code.yaml \
    --tests traces/tests.yaml \
    --output reports/traceability/traceability-matrix.html \
    --format html

# Generate CSV for analysis
python3 tools/traceability/generate_matrix.py \
    --requirements traces/requirements.yaml \
    --design traces/design.yaml \
    --code traces/code.yaml \
    --tests traces/tests.yaml \
    --output reports/traceability/traceability-matrix.csv \
    --format csv
```

### 5.2 Review Traceability Matrix

**Open HTML report**:

```bash
xdg-open reports/traceability/traceability-matrix.html
```

**Example matrix format**:

| Requirement ID | Description | Design Elements | Code Functions | Tests | Coverage |
|----------------|-------------|-----------------|----------------|-------|----------|
| REQ-FUNC-001 | Speed calculation | DES-ARCH-003, DES-COMP-015 | calculate_speed() | test_calculate_speed_valid, test_calculate_speed_zero, test_calculate_speed_overflow | ✓ 100% |
| REQ-FUNC-002 | Emergency brake | DES-ARCH-005, DES-COMP-020 | activate_brake() | test_activate_brake_normal, test_activate_brake_fault | ✓ 100% |
| REQ-SAF-001 | Safe state entry | DES-ARCH-010, DES-COMP-025 | enter_safe_state() | test_safe_state_entry, test_safe_state_timing | ✓ 100% |

---

## Step 6: Identify Traceability Gaps

### 6.1 Find Orphan Requirements

```bash
# Find requirements with no design/code/tests
python3 tools/traceability/find_gaps.py \
    --requirements traces/requirements.yaml \
    --design traces/design.yaml \
    --code traces/code.yaml \
    --tests traces/tests.yaml \
    --gap-type orphan-requirements \
    --output reports/traceability/orphan-requirements.txt

# Expected: 0 orphan requirements for SIL 3-4
```

### 6.2 Find Orphan Code

```bash
# Find code with no requirement trace (gold plating)
python3 tools/traceability/find_gaps.py \
    --requirements traces/requirements.yaml \
    --code traces/code.yaml \
    --gap-type orphan-code \
    --output reports/traceability/orphan-code.txt

# Expected: 0 orphan code (except utilities with justification)
```

### 6.3 Create Gap Resolution Plan

**For each gap**:

```yaml
# Traceability Gap: REQ-FUNC-042 (Data logging)
gap_id: GAP-001
requirement: REQ-FUNC-042
description: Data logging requirement has no design element
severity: High
impact: Requirement not implemented
resolution_plan: |
  1. Add design element DES-COMP-050 for data logging module
  2. Implement log_data() function
  3. Add unit tests
  4. Update traceability matrix
assigned_to: Designer Name
due_date: 2026-03-20
status: Open
```

---

## Step 7: Verify Safety Requirements Traceability

### 7.1 Extract Safety Requirements

```bash
# Extract all safety requirements (REQ-SAF-*)
grep -h "^### REQ-SAF-" DOC-SRS-*.md | \
    sed 's/### //' | \
    sort > reports/traceability/safety-requirements.txt

# Count
wc -l reports/traceability/safety-requirements.txt
```

### 7.2 Verify Safety Traceability Completeness

```bash
# Check that ALL safety requirements are fully traced
python3 tools/traceability/check_safety_traceability.py \
    --requirements traces/requirements.yaml \
    --design traces/design.yaml \
    --code traces/code.yaml \
    --tests traces/tests.yaml \
    --safety-only \
    --output reports/traceability/safety-traceability-report.txt

# Expected output:
# Safety Requirements: 12
# Fully traced (Req → Design → Code → Tests): 12/12 (100%) ✓
# Partially traced: 0
# Not traced: 0
```

**SIL 3-4 Requirement**: 100% safety requirement traceability (MANDATORY)

### 7.3 Verify Safety Test Coverage

```bash
# Verify safety requirements have adequate test coverage
python3 tools/traceability/check_safety_test_coverage.py \
    --requirements traces/requirements.yaml \
    --tests traces/tests.yaml \
    --coverage reports/coverage/coverage_filtered.info \
    --output reports/traceability/safety-test-coverage.txt

# Expected: 100% statement, branch, condition coverage for safety functions
```

---

## Step 8: Generate Traceability Report

### 8.1 Create Traceability Verification Report

**Template**: `reports/traceability/Traceability-Verification-Report.md`

```markdown
# Traceability Verification Report

**Document ID**: DOC-TRACE-VER-2026-001
**Project**: Train Control System (TCS)
**SIL Level**: 4
**Verification Date**: 2026-03-14
**Verifier**: Bob Jones (VER-1)

## 1. Summary

| Traceability Check | Coverage | Status |
|-------------------|----------|--------|
| Requirements → Design | 50/50 (100%) | ✓ PASS |
| Design → Code | 45/45 (100%) | ✓ PASS |
| Code → Tests | 120/120 (100%) | ✓ PASS |
| Tests → Requirements (backward) | 250/250 (100%) | ✓ PASS |
| **Overall** | **100%** | **✓ PASS** |

## 2. Safety Requirements Traceability

| Check | Coverage | Status |
|-------|----------|--------|
| Safety Requirements Fully Traced | 12/12 (100%) | ✓ PASS |
| Safety Test Coverage | 100% stmt/branch/cond | ✓ PASS |

## 3. Traceability Gaps

**Orphan Requirements**: 0
**Orphan Design Elements**: 0
**Orphan Code**: 0 (excluding justified utilities)
**Orphan Tests**: 0

## 4. Traceability Matrix

See Appendix A: Full Traceability Matrix (HTML/CSV)

## 5. Tools Used

- Python traceability scripts (tools/traceability/)
- Manual review for complex traces

## 6. Overall Assessment

**Traceability Verification Status**: ✓ PASS

**Conclusion**: All requirements are fully traced through design, code, and tests. Bidirectional traceability complete. Meets EN 50128 Table A.5 Technique 7 requirements for SIL 4.

## 7. Approvals

- **Verified by**: Bob Jones (VER-1), 2026-03-14
- **Approved by**: John Doe (VMGR), 2026-03-14
```

---

## Automation Scripts

### Complete Traceability Check Script

```bash
#!/bin/bash
# scripts/check_traceability.sh

set -e

echo "===== EN 50128 Traceability Verification ====="
echo ""

# 1. Extract all traces
echo "1. Extracting traceability information..."
python3 tools/traceability/extract_traces.py --input DOC-SRS-*.md --type requirements --output traces/requirements.yaml
python3 tools/traceability/extract_traces.py --input DOC-SAS-*.md DOC-SDS-*.md --type design --output traces/design.yaml
python3 tools/traceability/extract_traces.py --input src/*.c include/*.h --type code --output traces/code.yaml
python3 tools/traceability/extract_traces.py --input tests/*.c --type tests --output traces/tests.yaml
echo "✓ Extraction complete"
echo ""

# 2. Check forward traceability
echo "2. Checking forward traceability..."
python3 tools/traceability/check_traceability.py --source traces/requirements.yaml --target traces/design.yaml --direction forward
python3 tools/traceability/check_traceability.py --source traces/design.yaml --target traces/code.yaml --direction forward
python3 tools/traceability/check_traceability.py --source traces/code.yaml --target traces/tests.yaml --direction forward
echo "✓ Forward traceability complete"
echo ""

# 3. Check backward traceability
echo "3. Checking backward traceability..."
python3 tools/traceability/check_traceability.py --source traces/tests.yaml --target traces/requirements.yaml --direction backward
echo "✓ Backward traceability complete"
echo ""

# 4. Generate traceability matrix
echo "4. Generating traceability matrix..."
python3 tools/traceability/generate_matrix.py \
    --requirements traces/requirements.yaml \
    --design traces/design.yaml \
    --code traces/code.yaml \
    --tests traces/tests.yaml \
    --output reports/traceability/traceability-matrix.html \
    --format html
echo "✓ Matrix generated: reports/traceability/traceability-matrix.html"
echo ""

# 5. Check for gaps
echo "5. Checking for traceability gaps..."
python3 tools/traceability/find_gaps.py \
    --requirements traces/requirements.yaml \
    --design traces/design.yaml \
    --code traces/code.yaml \
    --tests traces/tests.yaml \
    --output reports/traceability/gaps-report.txt

if [ -s reports/traceability/gaps-report.txt ]; then
    echo "✗ Traceability gaps found (see gaps-report.txt)"
    exit 1
else
    echo "✓ No traceability gaps"
fi
echo ""

# 6. Safety requirements check
echo "6. Verifying safety requirements traceability..."
python3 tools/traceability/check_safety_traceability.py \
    --requirements traces/requirements.yaml \
    --design traces/design.yaml \
    --code traces/code.yaml \
    --tests traces/tests.yaml \
    --safety-only \
    --output reports/traceability/safety-traceability.txt
echo "✓ Safety traceability verified"
echo ""

echo "===== Traceability Verification COMPLETE ====="
echo "Overall Status: PASS"
```

---

## Summary

This traceability verification workflow ensures:

1. **Forward traceability**: Requirements → Design → Code → Tests
2. **Backward traceability**: Tests → Requirements
3. **Completeness**: No orphan requirements, design, code, or tests
4. **Safety traceability**: All safety requirements fully traced
5. **Automation**: Python scripts for efficient verification
6. **Reporting**: Comprehensive traceability matrix and reports

**EN 50128 Compliance**: Table A.5 Technique 7 "Traceability" (**MANDATORY** SIL 3-4)
