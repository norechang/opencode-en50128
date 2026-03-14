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
# Unified workspace CLI with traceability manager
workspace.py trace --help
workspace.py trace extract --help
workspace.py trace validate --help
workspace.py trace create --help
workspace.py trace check-gaps --help
workspace.py trace query --help
workspace.py trace report --help

# Ensure workspace.py is in PATH or use full path: tools/workspace.py
```

---

## Step 1: Verify Requirements-to-Design Traceability

### 1.1 Extract Requirement IDs from SRS

```bash
# Extract all requirement traceability links from SRS
workspace.py trace extract \
    --document DOC-SRS-*.md \
    --type requirements_to_design \
    --merge

# Or extract to specific matrix file
workspace.py trace extract \
    --document DOC-SRS-*.md \
    --type requirements_to_design \
    --output evidence/traceability/requirements_to_design.csv

# Result: Traceability links stored in CSV format
# Can query with: workspace.py trace query --matrix requirements_to_design
```

### 1.2 Extract Design Traces from SAS/SDS

```bash
# Extract design-to-architecture traceability from architecture documents
workspace.py trace extract \
    --document DOC-SAS-*.md \
    --type architecture_to_design \
    --merge

# Extract design-to-implementation traceability from design documents
workspace.py trace extract \
    --document DOC-SDS-*.md \
    --type design_to_implementation \
    --merge

# Query design traces
workspace.py trace query \
    --source ARCH-COMP-003 \
    --direction forward \
    --matrix architecture_to_design
```

### 1.3 Check Requirements Coverage

```bash
# Validate requirements-to-design traceability completeness
workspace.py trace validate \
    --phase design \
    --sil 3

# Check specific matrix for gaps
workspace.py trace check-gaps \
    --phase design \
    --sil 3

# Generate detailed validation report
workspace.py trace report \
    --from requirements \
    --to design \
    --format markdown \
    --output reports/traceability/req-to-design-report.md

# Expected output:
# Requirements traced to design: 48/50 (96%)
# Missing traces:
#   - REQ-FUNC-042: Data logging (no design element)
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
# Extract traceability links from source code @trace tags
workspace.py trace extract \
    --document src/*.c \
    --type implementation_to_tests \
    --merge

# Extract from header files
workspace.py trace extract \
    --document include/*.h \
    --type implementation_to_tests \
    --merge

# Query code traces
workspace.py trace query \
    --source calculate_speed \
    --matrix implementation_to_tests
```

### 2.2 Check Design Coverage in Code

```bash
# Validate design-to-implementation traceability
workspace.py trace validate \
    --phase implementation \
    --sil 3

# Check for gaps in design-to-implementation
workspace.py trace check-gaps \
    --phase implementation \
    --sil 3

# Generate report
workspace.py trace report \
    --from design \
    --to implementation \
    --format markdown \
    --output reports/traceability/design-to-code-report.md

# Expected output:
# Design elements implemented: 45/45 (100%) ✓
# Orphan design elements: 0
```

**SIL 3-4 Requirement**: 100% coverage

---

## Step 3: Verify Code-to-Test Traceability

### 3.1 Extract Test Traces

```bash
# Extract traceability links from test code @trace tags
workspace.py trace extract \
    --document tests/*.c \
    --type tests_to_requirements \
    --merge

# Query test traces
workspace.py trace query \
    --source test_calculate_speed_valid \
    --matrix tests_to_requirements \
    --direction backward
```

### 3.2 Check Code Coverage by Tests

```bash
# Validate implementation-to-tests traceability
workspace.py trace validate \
    --phase tests \
    --sil 3

# Check for untested code
workspace.py trace check-gaps \
    --phase tests \
    --sil 3

# Generate coverage report
workspace.py trace report \
    --from implementation \
    --to tests \
    --format markdown \
    --output reports/traceability/code-to-test-report.md

# Expected output:
# Code functions tested: 120/120 (100%) ✓
# Untested functions: 0
```

**SIL 3-4 Requirement**: 100% coverage (all functions tested)

---

## Step 4: Verify Backward Traceability

### 4.1 Check Backward Traceability from Tests

```bash
# Verify all tests trace back to requirements (backward direction)
workspace.py trace query \
    --matrix tests_to_requirements \
    --direction backward

# Validate backward traceability completeness
workspace.py trace validate \
    --phase tests \
    --direction backward \
    --sil 3

# Generate backward traceability report
workspace.py trace report \
    --from tests \
    --to requirements \
    --format markdown \
    --output reports/traceability/test-to-req-report.md

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
workspace.py trace create \
    --from requirements \
    --to design,implementation,tests

# Generate HTML report for visualization
workspace.py trace report \
    --from requirements \
    --to design,implementation,tests \
    --format html \
    --output reports/traceability/traceability-matrix.html

# Generate CSV for analysis
workspace.py trace report \
    --from requirements \
    --to design,implementation,tests \
    --format csv \
    --output reports/traceability/traceability-matrix.csv

# Generate Markdown report
workspace.py trace report \
    --from requirements \
    --to design,implementation,tests \
    --format markdown \
    --output reports/traceability/traceability-matrix.md
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
workspace.py trace check-gaps \
    --phase design \
    --sil 3

workspace.py trace check-gaps \
    --phase implementation \
    --sil 3

workspace.py trace check-gaps \
    --phase tests \
    --sil 3

# Generate comprehensive gap report
workspace.py trace report \
    --from requirements \
    --to design,implementation,tests \
    --format markdown \
    --output reports/traceability/orphan-requirements.md

# Expected: 0 orphan requirements for SIL 3-4
```

### 6.2 Find Orphan Code

```bash
# Find code with no requirement trace (gold plating)
workspace.py trace query \
    --matrix implementation_to_tests \
    --direction backward

# Check for untraced implementation
workspace.py trace check-gaps \
    --phase implementation \
    --direction backward \
    --sil 3

# Generate orphan code report
workspace.py trace report \
    --from implementation \
    --to requirements \
    --format markdown \
    --output reports/traceability/orphan-code.md

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
# Check that ALL safety requirements (REQ-SAF-*) are fully traced
# Query safety requirements specifically
workspace.py trace query \
    --source "REQ-SAF-*" \
    --direction forward \
    --matrix requirements_to_design

# Validate safety traceability
workspace.py trace validate \
    --phase design,implementation,tests \
    --sil 3 \
    --safety-only

# Generate safety traceability report
workspace.py trace report \
    --from requirements \
    --to design,implementation,tests \
    --format markdown \
    --filter "REQ-SAF-*" \
    --output reports/traceability/safety-traceability-report.md

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
# Generate comprehensive safety test traceability report
workspace.py trace report \
    --from requirements \
    --to tests \
    --format markdown \
    --filter "REQ-SAF-*" \
    --output reports/traceability/safety-test-coverage.md

# Cross-reference with code coverage data (if available)
# Note: For detailed coverage metrics (statement/branch/condition),
# use gcov/lcov tools in conjunction with traceability data
# Example: lcov --capture --directory . --output-file coverage.info
#          lcov --extract coverage.info '*/safety/*' --output-file safety_coverage.info

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

- **Traceability Manager** (`workspace.py trace`) - Extraction, validation, gap analysis, reporting
  - Commands: extract, validate, create, check-gaps, query, report, visualize
  - Storage: CSV (evidence/traceability/*.csv), JSON, Markdown
  - Version: 1.0.0 (see tools/README_TRACEABILITY.md)
- Manual review for complex traces and safety-critical validations

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
workspace.py trace extract --document DOC-SRS-*.md --type requirements_to_design --merge
workspace.py trace extract --document DOC-SAS-*.md --type architecture_to_design --merge
workspace.py trace extract --document DOC-SDS-*.md --type design_to_implementation --merge
workspace.py trace extract --document src/*.c include/*.h --type implementation_to_tests --merge
workspace.py trace extract --document tests/*.c --type tests_to_requirements --merge
echo "✓ Extraction complete"
echo ""

# 2. Validate traceability for each phase
echo "2. Validating traceability..."
workspace.py trace validate --phase design --sil 3
workspace.py trace validate --phase implementation --sil 3
workspace.py trace validate --phase tests --sil 3
echo "✓ Validation complete"
echo ""

# 3. Check for gaps
echo "3. Checking for traceability gaps..."
workspace.py trace check-gaps --phase design --sil 3
workspace.py trace check-gaps --phase implementation --sil 3
workspace.py trace check-gaps --phase tests --sil 3
echo "✓ Gap analysis complete"
echo ""

# 4. Generate comprehensive traceability matrix
echo "4. Generating traceability matrix..."
workspace.py trace report \
    --from requirements \
    --to design,implementation,tests \
    --format html \
    --output reports/traceability/traceability-matrix.html
workspace.py trace report \
    --from requirements \
    --to design,implementation,tests \
    --format markdown \
    --output reports/traceability/traceability-matrix.md
echo "✓ Matrix generated: reports/traceability/traceability-matrix.html"
echo ""

# 5. Generate safety-specific report
echo "5. Verifying safety requirements traceability..."
workspace.py trace report \
    --from requirements \
    --to design,implementation,tests \
    --format markdown \
    --filter "REQ-SAF-*" \
    --output reports/traceability/safety-traceability.md
echo "✓ Safety traceability verified"
echo ""

# 6. Visualize traceability
echo "6. Generating traceability visualization..."
workspace.py trace visualize \
    --from requirements \
    --to verification \
    --format mermaid \
    --output reports/traceability/traceability-graph.mmd
echo "✓ Visualization complete"
echo ""

echo "===== Traceability Verification COMPLETE ====="
echo "Overall Status: PASS (verify all reports for detailed status)"
echo ""
echo "Generated reports:"
echo "  - reports/traceability/traceability-matrix.html"
echo "  - reports/traceability/traceability-matrix.md"
echo "  - reports/traceability/safety-traceability.md"
echo "  - reports/traceability/traceability-graph.mmd"
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
