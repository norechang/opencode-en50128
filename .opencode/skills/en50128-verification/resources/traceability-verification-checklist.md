# Traceability Verification Checklist for EN 50128

**Purpose**: Phase-by-phase checklist for verifying bidirectional traceability completeness per EN 50128 Table A.5 Technique 7 (MANDATORY SIL 3-4).

**Scope**: Complete traceability verification from System Requirements through Validation Tests.

**Audience**: Verifiers (VER), Requirements Engineers (REQ), Designers (DES), Implementers (IMP)

**EN 50128 Reference**:
- Table A.5, Technique 7 "Traceability" (**MANDATORY** SIL 3-4, Highly Recommended SIL 2)
- Annex D.58 "Traceability"
- Section 6.2.4.9(h) "Structure and content of each verification step"

**Related Documents**:
- `workflows/traceability-verification.md` - Traceability workflow
- `workflows/verification-reporting.md` - Report traceability results

---

## Table of Contents

1. [Traceability Overview](#1-traceability-overview)
2. [Phase 2: Requirements Traceability Checklist](#2-phase-2-requirements-traceability-checklist)
3. [Phase 3: Architecture and Design Traceability Checklist](#3-phase-3-architecture-and-design-traceability-checklist)
4. [Phase 4: Component Design Traceability Checklist](#4-phase-4-component-design-traceability-checklist)
5. [Phase 5: Implementation Traceability Checklist](#5-phase-5-implementation-traceability-checklist)
6. [Phase 6: Integration Traceability Checklist](#6-phase-6-integration-traceability-checklist)
7. [Phase 7: Validation Traceability Checklist](#7-phase-7-validation-traceability-checklist)
8. [Safety Requirements Traceability Checklist](#8-safety-requirements-traceability-checklist)
9. [Traceability Matrix Templates](#9-traceability-matrix-templates)
10. [Automated Traceability Checking](#10-automated-traceability-checking)

---

## 1. Traceability Overview

### EN 50128 Traceability Requirements

**Table A.5, Technique 7 "Traceability"**:
- SIL 0: Recommended (R)
- SIL 1-2: Highly Recommended (HR)
- SIL 3-4: **MANDATORY (M)**

**Definition** (Annex D.58): "The degree to which a relationship can be established between two or more products of the development process, especially products having a predecessor-successor or master-subordinate relationship to one another."

### Traceability Chain

```
System Requirements (from system spec)
    ↓ (forward trace)
Software Requirements (SRS)
    ↓ (forward trace)
Software Architecture (SAS)
    ↓ (forward trace)
Software Design (SDS)
    ↓ (forward trace)
Source Code
    ↓ (forward trace)
Unit Tests
    ↓ (forward trace)
Integration Tests
    ↓ (forward trace)
System Tests
    ↓ (forward trace)
Validation Tests

    ↑ (backward trace - all levels back to requirements)
```

### Traceability Completeness Targets

| SIL Level | Forward Trace Target | Backward Trace Target | Safety Requirements Trace |
|-----------|----------------------|-----------------------|---------------------------|
| **SIL 0** | Best effort | Best effort | Best effort |
| **SIL 1-2** | 95%+ | 95%+ | 100% |
| **SIL 3-4** | **100%** | **100%** | **100%** |

### Traceability Tag Format

**Standard format** used throughout project:

```c
/**
 * @brief Function description
 * @trace REQ-XXX-NNN Requirement description
 * @trace DES-XXX-NNN Design description
 * @sil N
 */
```

**Example**:

```c
/**
 * @brief Calculate train speed from wheel sensor
 * @trace REQ-FUNC-001 Train speed calculation algorithm
 * @trace DES-ARCH-003 Speed calculation module
 * @trace DES-COMP-015 calculate_speed() function design
 * @sil 4
 */
uint32_t calculate_speed(sensor_t* sensor, uint32_t time_ms);
```

---

## 2. Phase 2: Requirements Traceability Checklist

### Forward Trace: System Requirements → Software Requirements

**Objective**: Verify all system requirements are allocated to software requirements.

**Checklist**:

- [ ] **TRACE-REQ-F001**: All system requirements documented in System Requirements Specification
- [ ] **TRACE-REQ-F002**: Each system requirement has unique ID (SYS-XXX-NNN format)
- [ ] **TRACE-REQ-F003**: Software Requirements Specification (SRS) contains all allocated software requirements
- [ ] **TRACE-REQ-F004**: Each software requirement has unique ID (REQ-XXX-NNN format)
- [ ] **TRACE-REQ-F005**: Each software requirement has @trace tag to parent system requirement(s)
- [ ] **TRACE-REQ-F006**: All system requirements allocated to software have at least one software requirement
- [ ] **TRACE-REQ-F007**: Traceability matrix generated: System Req → Software Req
- [ ] **TRACE-REQ-F008**: Forward traceability completeness: ____ % (Target: 100% SIL 3-4)
- [ ] **TRACE-REQ-F009**: No orphan software requirements (all have parent system requirement)

**Evidence**:
- System Requirements Specification: `docs/System_Requirements.md`
- Software Requirements Specification: `docs/SRS.md`
- Traceability Matrix: `docs/traceability/system_to_software_requirements.csv`

### Backward Trace: Software Requirements → System Requirements

**Objective**: Verify all software requirements trace back to system requirements (no "gold plating").

**Checklist**:

- [ ] **TRACE-REQ-B001**: Each software requirement has @trace tag to at least one system requirement
- [ ] **TRACE-REQ-B002**: All @trace tags reference valid system requirement IDs (no broken links)
- [ ] **TRACE-REQ-B003**: No orphan software requirements (requirements without system parent)
- [ ] **TRACE-REQ-B004**: Backward traceability completeness: ____ % (Target: 100% SIL 3-4)
- [ ] **TRACE-REQ-B005**: Traceability matrix generated: Software Req → System Req
- [ ] **TRACE-REQ-B006**: All orphan software requirements justified (e.g., derived requirements documented)

**Evidence**:
- Software Requirements Specification with @trace tags: `docs/SRS.md`
- Backward Traceability Matrix: `docs/traceability/software_to_system_requirements.csv`

### Requirements Phase Traceability Summary

| Metric | Value | Target (SIL 3-4) | Status |
|--------|-------|------------------|--------|
| Total System Requirements | ____ | - | - |
| Total Software Requirements | ____ | - | - |
| Forward Trace Completeness | ____% | 100% | ☐ PASS / ☐ FAIL |
| Backward Trace Completeness | ____% | 100% | ☐ PASS / ☐ FAIL |
| Orphan System Requirements | ____ | 0 | ☐ PASS / ☐ FAIL |
| Orphan Software Requirements | ____ | 0 | ☐ PASS / ☐ FAIL |

**Overall Phase 2 Traceability Status**: ☐ PASS / ☐ FAIL

---

## 3. Phase 3: Architecture and Design Traceability Checklist

### Forward Trace: Software Requirements → Architecture Components

**Objective**: Verify all software requirements are allocated to architecture components.

**Checklist**:

- [ ] **TRACE-ARCH-F001**: Software Architecture Specification (SAS) contains all architecture components
- [ ] **TRACE-ARCH-F002**: Each architecture component has unique ID (DES-ARCH-NNN format)
- [ ] **TRACE-ARCH-F003**: Each architecture component has @trace tag to parent software requirement(s)
- [ ] **TRACE-ARCH-F004**: All software requirements allocated to at least one architecture component
- [ ] **TRACE-ARCH-F005**: Traceability matrix generated: Software Req → Architecture Component
- [ ] **TRACE-ARCH-F006**: Forward traceability completeness: ____ % (Target: 100% SIL 3-4)
- [ ] **TRACE-ARCH-F007**: No orphan architecture components (all have parent requirements)

**Evidence**:
- Software Architecture Specification: `docs/SAS.md`
- Traceability Matrix: `docs/traceability/requirements_to_architecture.csv`

### Forward Trace: Architecture Components → Design Functions

**Objective**: Verify all architecture components are refined into detailed design functions.

**Checklist**:

- [ ] **TRACE-DES-F001**: Software Design Specification (SDS) contains all design functions
- [ ] **TRACE-DES-F002**: Each design function has unique ID (DES-FUNC-NNN format)
- [ ] **TRACE-DES-F003**: Each design function has @trace tag to parent architecture component(s)
- [ ] **TRACE-DES-F004**: All architecture components refined to at least one design function
- [ ] **TRACE-DES-F005**: Traceability matrix generated: Architecture Component → Design Function
- [ ] **TRACE-DES-F006**: Forward traceability completeness: ____ % (Target: 100% SIL 3-4)
- [ ] **TRACE-DES-F007**: No orphan design functions (all have parent architecture component)

**Evidence**:
- Software Design Specification: `docs/SDS.md`
- Traceability Matrix: `docs/traceability/architecture_to_design.csv`

### Backward Trace: Architecture/Design → Software Requirements

**Checklist**:

- [ ] **TRACE-ARCH-B001**: Each architecture component has @trace tag to at least one software requirement
- [ ] **TRACE-ARCH-B002**: Each design function traces back to architecture component (via @trace)
- [ ] **TRACE-ARCH-B003**: Each design function traces back to software requirement (transitively)
- [ ] **TRACE-ARCH-B004**: Backward traceability completeness: ____ % (Target: 100% SIL 3-4)
- [ ] **TRACE-ARCH-B005**: No orphan architecture components or design functions

**Evidence**:
- Backward Traceability Matrix: `docs/traceability/design_to_requirements.csv`

### Phase 3 Traceability Summary

| Metric | Value | Target (SIL 3-4) | Status |
|--------|-------|------------------|--------|
| Total Architecture Components | ____ | - | - |
| Total Design Functions | ____ | - | - |
| Req → Arch Completeness | ____% | 100% | ☐ PASS / ☐ FAIL |
| Arch → Design Completeness | ____% | 100% | ☐ PASS / ☐ FAIL |
| Backward Trace Completeness | ____% | 100% | ☐ PASS / ☐ FAIL |
| Orphan Architecture Components | ____ | 0 | ☐ PASS / ☐ FAIL |
| Orphan Design Functions | ____ | 0 | ☐ PASS / ☐ FAIL |

**Overall Phase 3 Traceability Status**: ☐ PASS / ☐ FAIL

---

## 4. Phase 4: Component Design Traceability Checklist

### Forward Trace: Design Functions → Component Design

**Objective**: Verify all design functions have detailed component design specifications.

**Checklist**:

- [ ] **TRACE-COMP-F001**: Software Component Design Specification contains all component designs
- [ ] **TRACE-COMP-F002**: Each component design has unique ID (DES-COMP-NNN format)
- [ ] **TRACE-COMP-F003**: Each component design has @trace tag to parent design function(s)
- [ ] **TRACE-COMP-F004**: All design functions refined to component design
- [ ] **TRACE-COMP-F005**: Traceability matrix generated: Design Function → Component Design
- [ ] **TRACE-COMP-F006**: Forward traceability completeness: ____ % (Target: 100% SIL 3-4)

### Forward Trace: Component Design → Unit Test Specifications

**Objective**: Verify all component designs have unit test specifications.

**Checklist**:

- [ ] **TRACE-COMP-T001**: Software Component Test Specification contains all unit test specs
- [ ] **TRACE-COMP-T002**: Each unit test spec has unique ID (TEST-UT-NNN format)
- [ ] **TRACE-COMP-T003**: Each unit test spec has @trace tag to component design(s)
- [ ] **TRACE-COMP-T004**: All component designs have at least one unit test specification
- [ ] **TRACE-COMP-T005**: Traceability matrix generated: Component Design → Unit Test Spec
- [ ] **TRACE-COMP-T006**: Forward traceability completeness: ____ % (Target: 100% SIL 3-4)

### Phase 4 Traceability Summary

| Metric | Value | Target (SIL 3-4) | Status |
|--------|-------|------------------|--------|
| Total Component Designs | ____ | - | - |
| Total Unit Test Specs | ____ | - | - |
| Design → Component Completeness | ____% | 100% | ☐ PASS / ☐ FAIL |
| Component → Unit Test Completeness | ____% | 100% | ☐ PASS / ☐ FAIL |

**Overall Phase 4 Traceability Status**: ☐ PASS / ☐ FAIL

---

## 5. Phase 5: Implementation Traceability Checklist

### Forward Trace: Component Design → Source Code

**Objective**: Verify all component designs are implemented in source code.

**Checklist**:

- [ ] **TRACE-CODE-F001**: All source code files documented in Software Source Code listing
- [ ] **TRACE-CODE-F002**: Each source function has @trace tag in Doxygen comment
- [ ] **TRACE-CODE-F003**: Each source function traces to at least one component design (DES-COMP-NNN)
- [ ] **TRACE-CODE-F004**: All component designs implemented (at least one source function per design)
- [ ] **TRACE-CODE-F005**: Traceability matrix generated: Component Design → Source Code
- [ ] **TRACE-CODE-F006**: Forward traceability completeness: ____ % (Target: 100% SIL 3-4)
- [ ] **TRACE-CODE-F007**: No missing implementations (design functions without code)

**Evidence**:
- Source Code: `src/`
- Traceability Matrix: `docs/traceability/design_to_code.csv`

### Forward Trace: Source Code → Unit Tests

**Objective**: Verify all source functions are tested by unit tests.

**Checklist**:

- [ ] **TRACE-TEST-F001**: All unit test files documented in Software Component Test Report
- [ ] **TRACE-TEST-F002**: Each unit test function has @test tag in comment
- [ ] **TRACE-TEST-F003**: Each unit test has @trace tag to source code function(s)
- [ ] **TRACE-TEST-F004**: All source functions have at least one unit test (or justification for untestable code)
- [ ] **TRACE-TEST-F005**: Traceability matrix generated: Source Code → Unit Tests
- [ ] **TRACE-TEST-F006**: Forward traceability completeness: ____ % (Target: 100% SIL 3-4)
- [ ] **TRACE-TEST-F007**: No untested code (except justified exceptions like hardware init)

**Evidence**:
- Unit Tests: `tests/unit/`
- Traceability Matrix: `docs/traceability/code_to_unit_tests.csv`

### Backward Trace: Source Code → Component Design

**Objective**: Verify all source code traces back to design (no unauthorized implementation).

**Checklist**:

- [ ] **TRACE-CODE-B001**: Each source function has @trace tag to at least one component design
- [ ] **TRACE-CODE-B002**: All @trace tags reference valid component design IDs (no broken links)
- [ ] **TRACE-CODE-B003**: No orphan source code (code without design traceability)
- [ ] **TRACE-CODE-B004**: Backward traceability completeness: ____ % (Target: 100% SIL 3-4)
- [ ] **TRACE-CODE-B005**: Orphan code justified (e.g., utility functions documented as such)

**Evidence**:
- Backward Traceability Matrix: `docs/traceability/code_to_design.csv`

### Backward Trace: Unit Tests → Source Code

**Checklist**:

- [ ] **TRACE-TEST-B001**: Each unit test has @trace tag to at least one source function
- [ ] **TRACE-TEST-B002**: No orphan unit tests (tests without code traceability)
- [ ] **TRACE-TEST-B003**: Backward traceability completeness: ____ % (Target: 100% SIL 3-4)

### Phase 5 Traceability Summary

| Metric | Value | Target (SIL 3-4) | Status |
|--------|-------|------------------|--------|
| Total Source Functions | ____ | - | - |
| Total Unit Tests | ____ | - | - |
| Design → Code Completeness | ____% | 100% | ☐ PASS / ☐ FAIL |
| Code → Unit Test Completeness | ____% | 100% | ☐ PASS / ☐ FAIL |
| Code → Design Backward | ____% | 100% | ☐ PASS / ☐ FAIL |
| Unit Test → Code Backward | ____% | 100% | ☐ PASS / ☐ FAIL |
| Orphan Source Functions | ____ | 0 | ☐ PASS / ☐ FAIL |
| Orphan Unit Tests | ____ | 0 | ☐ PASS / ☐ FAIL |
| Untested Source Functions | ____ | 0 | ☐ PASS / ☐ FAIL |

**Overall Phase 5 Traceability Status**: ☐ PASS / ☐ FAIL

---

## 6. Phase 6: Integration Traceability Checklist

### Forward Trace: Architecture → Integration Tests

**Objective**: Verify all architecture interfaces are tested by integration tests.

**Checklist**:

- [ ] **TRACE-INT-F001**: Software Integration Test Specification contains all integration test specs
- [ ] **TRACE-INT-F002**: Each integration test has unique ID (TEST-IT-NNN format)
- [ ] **TRACE-INT-F003**: Each integration test has @trace tag to architecture component(s)
- [ ] **TRACE-INT-F004**: All architecture interfaces have at least one integration test
- [ ] **TRACE-INT-F005**: Traceability matrix generated: Architecture → Integration Tests
- [ ] **TRACE-INT-F006**: Forward traceability completeness: ____ % (Target: 100% SIL 3-4)

### Backward Trace: Integration Tests → Architecture

**Checklist**:

- [ ] **TRACE-INT-B001**: Each integration test traces back to architecture component(s)
- [ ] **TRACE-INT-B002**: No orphan integration tests
- [ ] **TRACE-INT-B003**: Backward traceability completeness: ____ % (Target: 100% SIL 3-4)

### Phase 6 Traceability Summary

| Metric | Value | Target (SIL 3-4) | Status |
|--------|-------|------------------|--------|
| Total Architecture Interfaces | ____ | - | - |
| Total Integration Tests | ____ | - | - |
| Arch → Integration Test Completeness | ____% | 100% | ☐ PASS / ☐ FAIL |
| Integration Test → Arch Backward | ____% | 100% | ☐ PASS / ☐ FAIL |
| Untested Interfaces | ____ | 0 | ☐ PASS / ☐ FAIL |

**Overall Phase 6 Traceability Status**: ☐ PASS / ☐ FAIL

---

## 7. Phase 7: Validation Traceability Checklist

### Forward Trace: Software Requirements → System Tests

**Objective**: Verify all software requirements are validated by system tests.

**Checklist**:

- [ ] **TRACE-VAL-F001**: Overall Software Test Specification contains all system test specs
- [ ] **TRACE-VAL-F002**: Each system test has unique ID (TEST-ST-NNN format)
- [ ] **TRACE-VAL-F003**: Each system test has @trace tag to software requirement(s)
- [ ] **TRACE-VAL-F004**: All software requirements have at least one system test
- [ ] **TRACE-VAL-F005**: Traceability matrix generated: Software Requirements → System Tests
- [ ] **TRACE-VAL-F006**: Forward traceability completeness: ____ % (Target: 100% SIL 3-4)

### Backward Trace: System Tests → Software Requirements

**Checklist**:

- [ ] **TRACE-VAL-B001**: Each system test traces back to at least one software requirement
- [ ] **TRACE-VAL-B002**: No orphan system tests
- [ ] **TRACE-VAL-B003**: Backward traceability completeness: ____ % (Target: 100% SIL 3-4)

### End-to-End Traceability Verification

**Checklist**:

- [ ] **TRACE-E2E-001**: Select sample requirement and trace through all phases:
  - System Requirement → Software Requirement → Architecture → Design → Code → Unit Test → Integration Test → System Test
- [ ] **TRACE-E2E-002**: All traceability links valid (no broken links)
- [ ] **TRACE-E2E-003**: Traceability documented in Validation Verification Report

### Phase 7 Traceability Summary

| Metric | Value | Target (SIL 3-4) | Status |
|--------|-------|------------------|--------|
| Total Software Requirements | ____ | - | - |
| Total System Tests | ____ | - | - |
| Req → System Test Completeness | ____% | 100% | ☐ PASS / ☐ FAIL |
| System Test → Req Backward | ____% | 100% | ☐ PASS / ☐ FAIL |
| Unvalidated Requirements | ____ | 0 | ☐ PASS / ☐ FAIL |

**Overall Phase 7 Traceability Status**: ☐ PASS / ☐ FAIL

---

## 8. Safety Requirements Traceability Checklist

### Safety Requirements Identification

**Objective**: Ensure all safety requirements are identified and traced end-to-end (100% MANDATORY for SIL 3-4).

**Checklist**:

- [ ] **TRACE-SAFE-001**: All safety requirements identified in Hazard Log
- [ ] **TRACE-SAFE-002**: Each safety requirement has unique ID (SREQ-SAFE-NNN format)
- [ ] **TRACE-SAFE-003**: Each safety requirement has assigned SIL level (SIL 0-4)
- [ ] **TRACE-SAFE-004**: Each safety requirement traced to hazard(s) in Hazard Log

### Safety Requirements Forward Trace

**Checklist**:

- [ ] **TRACE-SAFE-F001**: All safety requirements allocated to software requirements (SRS)
- [ ] **TRACE-SAFE-F002**: All safety software requirements allocated to architecture (SAS)
- [ ] **TRACE-SAFE-F003**: All safety architecture components allocated to design (SDS)
- [ ] **TRACE-SAFE-F004**: All safety design functions implemented in code
- [ ] **TRACE-SAFE-F005**: All safety code tested by unit tests
- [ ] **TRACE-SAFE-F006**: All safety code tested by integration tests
- [ ] **TRACE-SAFE-F007**: All safety requirements validated by system tests
- [ ] **TRACE-SAFE-F008**: Safety traceability matrix generated: SREQ → SW Req → Arch → Design → Code → Tests
- [ ] **TRACE-SAFE-F009**: Safety forward traceability completeness: ____ % (Target: **100%** SIL 3-4)

### Safety Requirements Backward Trace

**Checklist**:

- [ ] **TRACE-SAFE-B001**: All safety code traces back to safety requirements
- [ ] **TRACE-SAFE-B002**: All safety tests trace back to safety requirements
- [ ] **TRACE-SAFE-B003**: Safety backward traceability completeness: ____ % (Target: **100%** SIL 3-4)

### Safety Traceability Summary

| Metric | Value | Target (SIL 3-4) | Status |
|--------|-------|------------------|--------|
| Total Safety Requirements | ____ | - | - |
| Safety Req → SW Req | ____% | **100%** | ☐ PASS / ☐ FAIL |
| Safety Req → Architecture | ____% | **100%** | ☐ PASS / ☐ FAIL |
| Safety Req → Design | ____% | **100%** | ☐ PASS / ☐ FAIL |
| Safety Req → Code | ____% | **100%** | ☐ PASS / ☐ FAIL |
| Safety Req → Unit Tests | ____% | **100%** | ☐ PASS / ☐ FAIL |
| Safety Req → Integration Tests | ____% | **100%** | ☐ PASS / ☐ FAIL |
| Safety Req → System Tests | ____% | **100%** | ☐ PASS / ☐ FAIL |
| Safety Backward Traceability | ____% | **100%** | ☐ PASS / ☐ FAIL |

**Overall Safety Traceability Status**: ☐ PASS / ☐ FAIL

**CRITICAL**: Safety traceability MUST be 100% for SIL 3-4. Any gap blocks phase gate.

---

## 9. Traceability Matrix Templates

### System Req → Software Req Matrix

| System Req ID | System Req Description | Software Req ID(s) | Software Req Description | Status | Notes |
|---------------|------------------------|-------------------|-------------------------|--------|-------|
| SYS-FUNC-001 | Train speed calculation | REQ-FUNC-001, REQ-FUNC-002 | Speed calculation algorithm, Speed sensor interface | Complete | - |
| SYS-SAFE-001 | Emergency braking | REQ-SAFE-001 | Emergency brake activation | Complete | Safety-critical |
| ... | ... | ... | ... | ... | ... |

### Software Req → Architecture Matrix

| Software Req ID | Req Description | Architecture Component ID(s) | Component Description | Status | Notes |
|-----------------|-----------------|----------------------------|----------------------|--------|-------|
| REQ-FUNC-001 | Speed calculation | DES-ARCH-003 | Speed Calculation Module | Complete | - |
| REQ-SAFE-001 | Emergency brake | DES-ARCH-005 | Brake Control Module | Complete | Safety-critical |
| ... | ... | ... | ... | ... | ... |

### Design → Code Matrix

| Design Function ID | Function Description | Source File | Source Function | Status | Notes |
|--------------------|---------------------|-------------|-----------------|--------|-------|
| DES-FUNC-015 | calculate_speed() | src/speed.c:120 | `uint32_t calculate_speed(sensor_t*, uint32_t)` | Complete | - |
| DES-FUNC-023 | activate_emergency_brake() | src/brake.c:234 | `void activate_emergency_brake(void)` | Complete | Safety-critical |
| ... | ... | ... | ... | ... | ... |

### Code → Unit Test Matrix

| Source Function | File:Line | Unit Test Function | Test File | Status | Coverage |
|-----------------|-----------|-------------------|-----------|--------|----------|
| `calculate_speed()` | src/speed.c:120 | `test_calculate_speed_valid()`, `test_calculate_speed_invalid()` | tests/unit/test_speed.c | Complete | 100% |
| `activate_emergency_brake()` | src/brake.c:234 | `test_emergency_brake_activation()` | tests/unit/test_brake.c | Complete | 100% |
| ... | ... | ... | ... | ... | ... |

### Safety Requirements End-to-End Matrix

| Safety Req ID | Hazard | SW Req | Architecture | Design | Code | Unit Test | Integration Test | System Test | Status |
|---------------|--------|--------|--------------|--------|------|-----------|------------------|-------------|--------|
| SREQ-SAFE-001 | HAZ-001 | REQ-SAFE-001 | DES-ARCH-005 | DES-FUNC-023 | brake.c:234 | TEST-UT-023 | TEST-IT-015 | TEST-ST-005 | Complete |
| ... | ... | ... | ... | ... | ... | ... | ... | ... | ... |

---

## 10. Automated Traceability Checking

### Traceability Extraction Tool

**Script**: `tools/traceability/trace_checker.py`

**Usage**:

```bash
# Extract all @trace tags from source code, requirements, design docs
python3 tools/traceability/trace_checker.py \
    --source src/ \
    --requirements docs/SRS.md \
    --design docs/SAS.md docs/SDS.md \
    --tests tests/ \
    --output docs/traceability/traceability_matrix.csv

# Check for gaps (missing traces)
python3 tools/traceability/trace_checker.py \
    --source src/ \
    --requirements docs/SRS.md \
    --design docs/SAS.md docs/SDS.md \
    --tests tests/ \
    --check-gaps \
    --output docs/traceability/traceability_gaps.txt

# Generate HTML report
python3 tools/traceability/trace_checker.py \
    --source src/ \
    --requirements docs/SRS.md \
    --design docs/SAS.md docs/SDS.md \
    --tests tests/ \
    --html docs/traceability/traceability_report.html
```

### Traceability Gap Report Format

```
Traceability Gap Report
=======================

MISSING CODE IMPLEMENTATIONS (Design → Code):
- DES-FUNC-045: validate_sensor_cross_check() - No implementation found
- DES-FUNC-089: log_diagnostic_event() - No implementation found

ORPHAN CODE (Code → Design):
- src/util.c:145: helper_function_a() - No @trace tag to design
- src/util.c:189: helper_function_b() - No @trace tag to design

UNTESTED CODE (Code → Unit Test):
- src/sensor.c:234: read_sensor_raw() - No unit test found

ORPHAN UNIT TESTS (Unit Test → Code):
- tests/unit/test_util.c:67: test_obsolete_function() - Traces to non-existent function

SUMMARY:
- Total Gaps: 6
- Forward Trace Completeness: 98% (Target: 100%)
- Backward Trace Completeness: 98% (Target: 100%)
- Status: INCOMPLETE
```

### CI/CD Integration

Add to `.gitlab-ci.yml`:

```yaml
traceability-check:
  stage: verification
  script:
    - python3 tools/traceability/trace_checker.py \
        --source src/ \
        --requirements docs/SRS.md \
        --design docs/SAS.md docs/SDS.md \
        --tests tests/ \
        --check-gaps \
        --output traceability_gaps.txt
    - python3 tools/ci/fail_if_gaps.py traceability_gaps.txt
  artifacts:
    paths:
      - traceability_gaps.txt
    expire_in: 1 month
  allow_failure: false  # MUST pass for SIL 3-4
```

---

## Summary

Traceability verification is **MANDATORY for SIL 3-4** (EN 50128 Table A.5) and requires:

1. **100% Forward Traceability**: System Req → SW Req → Arch → Design → Code → Unit Test → Integration Test → System Test
2. **100% Backward Traceability**: Tests → Requirements (no orphan code or tests)
3. **100% Safety Traceability**: All safety requirements traced end-to-end (CRITICAL)
4. **Automated Checking**: Use traceability tools to extract @trace tags and check completeness
5. **Phase-by-Phase Verification**: Verify traceability at each lifecycle phase
6. **Traceability Matrix**: Document all traceability relationships in matrices

**For VER Agent**: Use these checklists to systematically verify traceability completeness at each phase.

**For REQ/DES/IMP Agents**: Use @trace tags consistently to enable automated traceability checking.

**For COD Agent**: Enforce 100% traceability as gate check criterion for SIL 3-4 projects.

---

**END OF CHECKLIST**
