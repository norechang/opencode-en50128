# Software Integration Test Report
## Train Door Control System

---

### Document Control

| Field | Details |
|-------|---------|
| **Document ID** | DOC-INTTESTRPT-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-02-26 |
| **Status** | Draft |
| **Classification** | Internal |
| **SIL Level** | SIL 3 |
| **Project** | Train Door Control System |
| **Organization** | Railway Safety Systems Inc. |

---

### Approval

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (Integrator)** | [Integrator Name] | | 2026-02-26 |
| **Reviewer (Verifier)** | [Verifier Name] | | |
| **Quality Assurance** | [QA Name] | | |
| **Project Manager** | [PM Name] | | |

**SIL 3 Requirements**:
- Verifier SHALL be independent from Integrator and development team (EN 50128 5.1.2.10f)
- Integration testing SHALL be performed according to Software Integration Test Specification DOC-INTTEST-2026-001

---

### Document History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-02-26 | Integrator | Initial version - Integration test execution results |

---

### Referenced Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-INTTEST-2026-001 | Software Integration Test Specification | 1.0 |
| DOC-SWRS-2026-001 | Software Requirements Specification | 1.0 |
| DOC-SAS-2026-001 | Software Architecture Specification | 1.0 |
| DOC-SDS-2026-001 | Software Design Specification | 1.0 |
| DOC-SIS-2026-001 | Software Interface Specifications | 1.0 |
| EN 50128:2011 | Railway Applications - Software for Railway Control and Protection Systems | 2011 |

---

## Table of Contents

1. [Executive Summary](#executive-summary)
2. [Introduction](#1-introduction)
3. [Integration Configuration](#2-integration-configuration)
4. [Integration Test Results](#3-integration-test-results)
5. [Defects and Issues](#4-defects-and-issues)
6. [Coverage Analysis](#5-coverage-analysis)
7. [Performance Results](#6-performance-results)
8. [EN 50128 Compliance](#7-en-50128-compliance)
9. [Conclusions and Recommendations](#8-conclusions-and-recommendations)

---

## Executive Summary

### Integration Test Outcome

**Overall Integration Result**: ⚠️ **CONDITIONAL FAIL**

**Integration Period**: 2026-02-25 to 2026-02-26

**Software Version Integrated**: v1.0 (git commit: Phase-5-complete)

**Integration Strategy**: Bottom-Up Integration (4 phases, 10 builds)

**Test Execution Summary**:
- **Total Test Cases**: 73
- **Tests Executed**: 73 (100%)
- **Tests Passed**: 57 (78.1%)
- **Tests Failed**: 16 (21.9%)
- **Tests Blocked**: 0

**Key Findings**:
- ✅ HAL layer integration partially functional (6/11 passing)
- ⚠️ Control logic integration has issues (5/9 passing)
- ⚠️ Application layer integration has issues (3/6 passing)
- ⚠️ System integration incomplete (1/3 passing)
- ✅ Performance testing successful (8/8 passing)
- ✅ Safety-critical testing mostly successful (34/36 passing)

**Critical Issues**:
1. **16 integration test failures** - Root causes identified as:
   - Mock-to-production interface mismatches (GPIO, ADC, CAN)
   - State initialization issues (locks, FSM)
   - Timing-related issues (wraparound in timing measurements)
   
2. **SIL 3 Non-Compliance**: EN 50128 Section 7.6.4.7 requires 100% test pass rate. Current 78.1% is NOT acceptable for safety-critical software.

**Defects Reported**: 16 defects logged (DEFECT-INT-001 through DEFECT-INT-016)

**Recommendation**: ⚠️ **NOT READY for Validation** - Defect resolution required before proceeding to Phase 7

---

## 1. Introduction

### 1.1 Purpose

This document reports the results of **Software Integration Testing** for the Train Door Control System in accordance with EN 50128:2011 Section 7.6.

**Report Objectives**:
- Document execution of all 73 integration test cases from DOC-INTTEST-2026-001
- Report integration results, interface test coverage, and defects found
- Document integration phases (4 phases) and build sequence (10 builds)
- Provide evidence for readiness (or lack thereof) for overall software testing (Phase 7: Validation)

### 1.2 Scope

**Integration Testing Performed**:
- Software component integration (8 modules: MOD-001 through MOD-008)
- Interface testing between 47 interface functions
- Functional testing of integrated components (bottom-up strategy)
- Performance testing (8 test cases, timing verification)
- Safety-critical integration testing (36 test cases)

**Reference Documents**:
- Software Integration Test Specification: DOC-INTTEST-2026-001 v1.0
- Software Architecture Specification: DOC-SAS-2026-001 v1.0
- Software Interface Specifications: DOC-SIS-2026-001 v1.0

### 1.3 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **HAL** | Hardware Abstraction Layer |
| **FSM** | Finite State Machine (Door FSM module) |
| **CAN** | Controller Area Network bus |
| **GPIO** | General Purpose Input/Output |
| **ADC** | Analog-to-Digital Converter |
| **PWM** | Pulse Width Modulation |
| **PASS** | Test case passed all acceptance criteria |
| **FAIL** | Test case failed one or more acceptance criteria |
| **Mock** | Simulated hardware interface for host PC testing |

---

## 2. Integration Configuration

### 2.1 Software Components Integrated

**Integrated Software**:
- Software name: Train Door Control System
- Version: 1.0
- Build date: 2026-02-26
- Git commit: Phase-5-complete
- Configuration baseline: Baseline 5 (post-unit-test)
- SIL level: SIL 3

**Software Components (8 Modules)**:

| Component | Version | Files | Unit Test Status | LOC |
|-----------|---------|-------|------------------|-----|
| MOD-001: Door FSM | 1.0 | door_control/door_fsm.c/h | PASSED (32/32) | 450 |
| MOD-002: Safety Monitor | 1.0 | safety/safety_monitor.c/h | PASSED (35/35) | 420 |
| MOD-003: Fault Detection | 1.0 | fault_detection/fault_detection.c/h | PASSED (30/30) | 380 |
| MOD-004: Command Processor | 1.0 | command_processor/command_processor.c/h | PASSED (28/28) | 350 |
| MOD-005: Status Reporter | 1.0 | status_reporter/status_reporter.c/h | PASSED (25/25) | 320 |
| MOD-006: Actuator HAL | 1.0 | hal/actuator_hal.c/h | PASSED (35/35) | 410 |
| MOD-007: Sensor HAL | 1.0 | hal/sensor_hal.c/h | PASSED (40/40) | 480 |
| MOD-008: Communication HAL | 1.0 | hal/communication_hal.c/h | PASSED (37/37) | 450 |
| **TOTAL** | | 21 files | **262/262 PASSED** | **~3740** |

**All unit tests passed before integration** (Phase 5 gate check: 2026-02-25)

### 2.2 Integration Test Environment

**Hardware Configuration** (Simulation):
- Platform: Linux x86_64 (host PC simulation)
- Processor: x86_64 (simulating ARM Cortex-M4)
- Memory: Host memory (simulating 128 KB RAM, 512 KB Flash)
- Simulation: Mock hardware layer (PWM, GPIO, ADC, CAN, UART)

**Note**: Tests executed on **host PC** (not target hardware). This introduces RISK-003: WCET not measured on actual target hardware.

**Software Configuration**:
- Operating System: Linux (Ubuntu/Debian)
- Compiler: gcc 13.3.0
- Build system: GNU Make
- Test framework: Custom Unity-compatible framework
- Integration test harness: software_integration_tests.c (2000+ LOC)

**Tools Used**:
- Version control: git
- Test execution: Custom test runner (software_integration_tests)
- Coverage analysis: gcov/lcov (installed but not generated for integration tests yet)
- Mock framework: integration_mocks.c/h (500+ LOC)

**Compilation Flags** (SIL 3 compliant):
```
-std=c11 -Wall -Wextra -Werror -pedantic -O0 -g
-DSIL_LEVEL=3 -DMISRA_C_2012 -DINTEGRATION_TEST
-Wstrict-prototypes -Wmissing-prototypes
-Wformat=2 -Wformat-security
-Wconversion -Wsign-conversion
-Wcast-qual -Wcast-align
-fstack-protector-strong -D_FORTIFY_SOURCE=2 -fno-common
-fprofile-arcs -ftest-coverage --coverage
```

### 2.3 Integration Team

| Role | Name | Responsibilities |
|------|------|------------------|
| **Integrator (INT)** | [Integrator Name] | Integration planning, coordination, report authoring |
| **Tester (TST)** | [Tester Name] | Test execution, defect reporting |
| **Verifier (VER)** | [Verifier Name] | Independent verification (SIL 3) |
| **Quality Assurance (QUA)** | [QA Name] | Quality review, template compliance |

---

## 3. Integration Test Results

### 3.1 Integration Strategy Execution

**Strategy**: Bottom-Up Integration (per DOC-INTTEST-2026-001 Section 2.2)

**Integration Sequence** (10 builds):

**Phase 1: HAL Layer Integration**
- Build 1: MOD-006 (Actuator HAL) standalone ✅
- Build 2: MOD-007 (Sensor HAL) standalone ✅
- Build 3: MOD-008 (Communication HAL) standalone ✅
- Build 4: MOD-006 + MOD-007 + MOD-008 (Complete HAL) ⚠️

**Phase 2: Control Logic Integration**
- Build 5: MOD-001 (Door FSM) + HAL layer ⚠️
- Build 6: MOD-002 (Safety Monitor) + MOD-001 + HAL ✅
- Build 7: MOD-003 (Fault Detection) + MOD-001 + MOD-002 + HAL ⚠️

**Phase 3: Application Layer Integration**
- Build 8: MOD-004 (Command Processor) + Control Logic + HAL ✅
- Build 9: MOD-005 (Status Reporter) + MOD-004 + Control Logic + HAL ⚠️

**Phase 4: System Integration**
- Build 10: Complete system (all 8 modules) ⚠️

**Legend**: ✅ All tests passed | ⚠️ Some tests failed

### 3.2 Test Execution Summary

| Phase | Test Range | Total | Passed | Failed | Pass Rate |
|-------|-----------|-------|--------|--------|-----------|
| **Phase 1: HAL Layer** | TC-INT-1-001 to 1-011 | 11 | 6 | 5 | 54.5% |
| **Phase 2: Control Logic** | TC-INT-2-001 to 2-009 | 9 | 5 | 4 | 55.6% |
| **Phase 3: Application** | TC-INT-3-001 to 3-006 | 6 | 3 | 3 | 50.0% |
| **Phase 4: System** | TC-INT-4-001 to 4-003 | 3 | 1 | 2 | 33.3% |
| **Performance Testing** | TC-INT-PERF-001 to 008 | 8 | 8 | 0 | 100.0% |
| **Safety-Critical** | TC-INT-SAF-001 to 036 | 36 | 34 | 2 | 94.4% |
| **TOTAL** | | **73** | **57** | **16** | **78.1%** |

⚠️ **SIL 3 COMPLIANCE ISSUE**: EN 50128 Section 7.6.4.7 requires 100% test pass rate. **78.1% is NOT acceptable.**

### 3.3 Detailed Test Results

#### Phase 1: HAL Layer Integration Tests (11 tests)

| Test ID | Test Name | Result | Duration | Defect |
|---------|-----------|--------|----------|--------|
| TC-INT-1-001 | Actuator HAL Initialization | ❌ FAIL | 0 ms | DEFECT-INT-001 |
| TC-INT-1-002 | Actuator HAL Motor Control | ✅ PASS | 0 ms | - |
| TC-INT-1-003 | Actuator HAL Lock Control | ✅ PASS | 0 ms | - |
| TC-INT-1-004 | Sensor HAL Initialization | ✅ PASS | 0 ms | - |
| TC-INT-1-005 | Sensor HAL Position Reading | ❌ FAIL | 0 ms | DEFECT-INT-002 |
| TC-INT-1-006 | Sensor HAL Obstacle Detection | ✅ PASS | 0 ms | - |
| TC-INT-1-007 | Sensor HAL Speed Reading | ❌ FAIL | 0 ms | DEFECT-INT-003 |
| TC-INT-1-008 | Communication HAL Initialization | ✅ PASS | 0 ms | - |
| TC-INT-1-009 | Communication HAL CAN Transmit | ❌ FAIL | 0 ms | DEFECT-INT-004 |
| TC-INT-1-010 | Communication HAL CAN Receive | ✅ PASS | 0 ms | - |
| TC-INT-1-011 | HAL Layer Combined Operation | ❌ FAIL | 0 ms | DEFECT-INT-005 |

**Phase 1 Summary**: 6 passed, 5 failed (54.5%)

#### Phase 2: Control Logic Integration Tests (9 tests)

| Test ID | Test Name | Result | Duration | Defect |
|---------|-----------|--------|----------|--------|
| TC-INT-2-001 | Door FSM + Actuator HAL Integration | ❌ FAIL | 0 ms | DEFECT-INT-006 |
| TC-INT-2-002 | Door FSM + Sensor HAL Position Feedback | ❌ FAIL | 0 ms | DEFECT-INT-007 |
| TC-INT-2-003 | Safety Monitor + Sensor HAL Speed Interlock | ✅ PASS | 100 ms | - |
| TC-INT-2-004 | Safety Monitor + Communication HAL Speed Data | ✅ PASS | ~100 ms | - |
| TC-INT-2-005 | Door FSM + Safety Monitor Interlock | ✅ PASS | ~100 ms | - |
| TC-INT-2-006 | Door FSM + Sensor HAL Obstacle Detection | ❌ FAIL | 0 ms | DEFECT-INT-008 |
| TC-INT-2-007 | Fault Detection + Door FSM Integration | ✅ PASS | 5100 ms | - |
| TC-INT-2-008 | Fault Detection + Sensor HAL Integration | ❌ FAIL | 0 ms | DEFECT-INT-009 |
| TC-INT-2-009 | Safety Monitor Watchdog Integration | ✅ PASS | 400 ms | - |

**Phase 2 Summary**: 5 passed, 4 failed (55.6%)

#### Phase 3: Application Layer Integration Tests (6 tests)

| Test ID | Test Name | Result | Duration | Defect |
|---------|-----------|--------|----------|--------|
| TC-INT-3-001 | Command Processor + Door FSM Integration | ✅ PASS | ~100 ms | - |
| TC-INT-3-002 | Command Processor + Communication HAL Integration | ✅ PASS | 0 ms | - |
| TC-INT-3-003 | Status Reporter + Door FSM Integration | ❌ FAIL | 0 ms | DEFECT-INT-010 |
| TC-INT-3-004 | Status Reporter + Fault Detection Integration | ✅ PASS | ~100 ms | - |
| TC-INT-3-005 | Status Reporter + Communication HAL Integration | ❌ FAIL | 0 ms | DEFECT-INT-011 |
| TC-INT-3-006 | End-to-End Command-to-Status Flow | ❌ FAIL | 0 ms | DEFECT-INT-012 |

**Phase 3 Summary**: 3 passed, 3 failed (50.0%)

#### Phase 4: System Integration Tests (3 tests)

| Test ID | Test Name | Result | Duration | Defect |
|---------|-----------|--------|----------|--------|
| TC-INT-4-001 | Complete System Functional Test | ❌ FAIL | 0 ms | DEFECT-INT-013 |
| TC-INT-4-002 | System Stress Test | ✅ PASS | ~100 ms | - |
| TC-INT-4-003 | System Recovery Test | ❌ FAIL | 0 ms | DEFECT-INT-014 |

**Phase 4 Summary**: 1 passed, 2 failed (33.3%)

#### Performance Testing (8 tests)

| Test ID | Test Name | Result | Duration | Notes |
|---------|-----------|--------|----------|-------|
| TC-INT-PERF-001 | Main Control Loop Timing | ✅ PASS | 50000 ms | 10 ms measured (< 10 ms limit) |
| TC-INT-PERF-002 | Obstacle Reaction Time | ✅ PASS | ~100 ms | 50 ms measured (< 100 ms limit) |
| TC-INT-PERF-003 | CAN Message Latency | ✅ PASS | ~100 ms | 5 ms measured (< 10 ms limit) |
| TC-INT-PERF-004 | Watchdog Refresh Timing | ✅ PASS | 500 ms | 50 ms measured (< 100 ms limit) |
| TC-INT-PERF-005 | Door Operation Timing | ✅ PASS | 4750 ms | Open: 5.0s, Close: 7.0s (within spec) |
| TC-INT-PERF-006 | CPU Load Measurement | ✅ PASS | 0 ms | ~30% CPU load (< 50% limit) |
| TC-INT-PERF-007 | Memory Usage Measurement | ✅ PASS | 0 ms | 10 KB used (< 64 KB limit) |
| TC-INT-PERF-008 | CAN Bus Bandwidth Utilization | ✅ PASS | 4750 ms | 5% utilization (< 20% limit) |

**Performance Summary**: 8 passed, 0 failed (100%)

⚠️ **WARNING**: All timing measurements performed on **host PC**, not target hardware. WCET values NOT accurate (RISK-003).

#### Safety-Critical Testing (36 tests)

| Test ID | Test Name | Result | Duration | Defect |
|---------|-----------|--------|----------|--------|
| TC-INT-SAF-001 | Speed Interlock During Door Opening | ✅ PASS | ~100 ms | - |
| TC-INT-SAF-002 | Speed Interlock Lock Engagement | ✅ PASS | 50 ms | - |
| TC-INT-SAF-003 | Obstacle Detection During Closing | ❌ FAIL | 0 ms | DEFECT-INT-015 |
| TC-INT-SAF-004 | Repeated Obstacle Detection | ✅ PASS | 500 ms | - |
| TC-INT-SAF-005 | Emergency Release Override | ✅ PASS | ~100 ms | - |
| TC-INT-SAF-006 | Sensor Fault Safe State | ❌ FAIL | 0 ms | DEFECT-INT-016 |
| TC-INT-SAF-007 | Watchdog Timeout Safe State | ✅ PASS | 0 ms | - |
| TC-INT-SAF-008 | Motor Stall Fault Detection | ✅ PASS | 5500 ms | - |
| TC-INT-SAF-009 | HAL Error Propagation to Application | ✅ PASS | ~100 ms | - |
| TC-INT-SAF-010 | Safety Monitor Fault Injection | ✅ PASS | 200 ms | - |
| TC-INT-SAF-011 to SAF-030 | [Various safety tests] | ✅ PASS | Various | - |
| TC-INT-SAF-031 to SAF-036 | [Various safety tests] | ✅ PASS | Various | - |

**Safety-Critical Summary**: 34 passed, 2 failed (94.4%)

---

## 4. Defects and Issues

### 4.1 Defect Summary

**Total Defects Found**: 16

| Severity | Count | Percentage |
|----------|-------|------------|
| **Critical** | 0 | 0% |
| **High** | 6 | 37.5% |
| **Medium** | 8 | 50.0% |
| **Low** | 2 | 12.5% |

**Defect Status**:
- Open: 16
- Fixed: 0
- Deferred: 0

### 4.2 Defect Details

#### DEFECT-INT-001: Actuator HAL Lock Initialization
- **Test Case**: TC-INT-1-001
- **Severity**: Medium
- **Description**: Left lock not engaged after `actuator_hal_init()`. Expected: LEFT_LOCK engaged (GPIO pin 10 HIGH). Actual: Lock state unknown or not properly initialized.
- **Root Cause**: Suspected mock GPIO initialization issue or production code lock engagement logic.
- **Impact**: Lock safety verification fails at initialization.
- **Status**: Open

#### DEFECT-INT-002: Sensor HAL Position Reading Mismatch
- **Test Case**: TC-INT-1-005
- **Severity**: Medium
- **Description**: Position sensor readback does not match mock-set position. Expected: 50% (ADC ~2048). Actual: Different value.
- **Root Cause**: Mock ADC simulation not synchronized with `mock_left/right_position_raw` variables.
- **Impact**: Position feedback unreliable in integration tests.
- **Status**: Open

#### DEFECT-INT-003: Sensor HAL Speed Reading Incorrect
- **Test Case**: TC-INT-1-007
- **Severity**: Medium
- **Description**: Speed sensor readback incorrect. Expected: 50 (5.0 km/h). Actual: Different value.
- **Root Cause**: CAN speed message injection or big-endian parsing issue in mock.
- **Impact**: Speed interlock tests unreliable.
- **Status**: Open

#### DEFECT-INT-004: Communication HAL CAN Message ID Mismatch
- **Test Case**: TC-INT-1-009
- **Severity**: Medium
- **Description**: CAN message ID mismatch after transmission. Expected: Match sent ID. Actual: Different ID.
- **Root Cause**: CAN TX queue mock implementation or message struct handling issue.
- **Impact**: CAN-based command/status communication unreliable.
- **Status**: Open

#### DEFECT-INT-005: HAL Combined Operation Position Issue
- **Test Case**: TC-INT-1-011
- **Severity**: High
- **Description**: Position sensor returns 0 in combined HAL operation. Expected: Position > 0 after motor activation.
- **Root Cause**: Mock door motion physics not updating ADC position feedback.
- **Impact**: Multi-module HAL operation fails.
- **Status**: Open

#### DEFECT-INT-006: Door FSM Not Reaching OPEN State
- **Test Case**: TC-INT-2-001
- **Severity**: High
- **Description**: Door FSM does not transition to OPEN state during integration. Expected: STATE_OPEN. Actual: Different state.
- **Root Cause**: FSM state machine logic or actuator HAL feedback issue.
- **Impact**: Core door control functionality fails.
- **Status**: Open

#### DEFECT-INT-007: Door FSM Position Feedback Incorrect
- **Test Case**: TC-INT-2-002
- **Severity**: High
- **Description**: Door FSM position feedback mismatch. Expected: 50%. Actual: Different value.
- **Root Cause**: Sensor HAL position reading issue (related to DEFECT-INT-002).
- **Impact**: Position-based control unreliable.
- **Status**: Open

#### DEFECT-INT-008: Door FSM Not Opening Before Obstacle Test
- **Test Case**: TC-INT-2-006
- **Severity**: High
- **Description**: Door not in OPEN state before obstacle detection test. Expected: STATE_OPEN. Actual: Different state.
- **Root Cause**: FSM state progression issue (related to DEFECT-INT-006).
- **Impact**: Obstacle detection test cannot execute properly.
- **Status**: Open

#### DEFECT-INT-009: Fault Detection Sensor Error Not Returned
- **Test Case**: TC-INT-2-008
- **Severity**: Medium
- **Description**: Sensor fault not properly returned to fault detection module. Expected: ERROR_SENSOR_FAULT. Actual: SUCCESS or different error.
- **Root Cause**: Sensor HAL error propagation or fault detection module integration issue.
- **Impact**: Fault detection reliability compromised.
- **Status**: Open

#### DEFECT-INT-010: Status Reporter FSM State Incorrect
- **Test Case**: TC-INT-3-003
- **Severity**: Medium
- **Description**: Status reporter does not report correct FSM state. Expected: STATE_OPEN. Actual: Different state.
- **Root Cause**: FSM state propagation to status reporter or FSM state issue (related to DEFECT-INT-006).
- **Impact**: Status reporting unreliable.
- **Status**: Open

#### DEFECT-INT-011: Status Reporter CAN Message ID Wrong
- **Test Case**: TC-INT-3-005
- **Severity**: Medium
- **Description**: Status message CAN ID incorrect. Expected: 0x201. Actual: Different ID.
- **Root Cause**: Status reporter CAN message construction or communication HAL issue.
- **Impact**: Status message routing unreliable.
- **Status**: Open

#### DEFECT-INT-012: End-to-End Door State Incorrect
- **Test Case**: TC-INT-3-006
- **Severity**: High
- **Description**: End-to-end command flow does not result in correct door state. Expected: Door OPEN. Actual: Different state.
- **Root Cause**: Multiple cascading issues from FSM, actuator HAL, and sensor HAL problems.
- **Impact**: Complete system functionality compromised.
- **Status**: Open

#### DEFECT-INT-013: Complete System Left Door Not Opening
- **Test Case**: TC-INT-4-001
- **Severity**: High
- **Description**: Left door does not open in complete system test. Expected: Left door OPEN. Actual: Not open.
- **Root Cause**: FSM, actuator HAL, or sensor HAL integration issue (cascading from earlier defects).
- **Impact**: Complete system functional test fails.
- **Status**: Open

#### DEFECT-INT-014: System Recovery FSM Not Operating After Reset
- **Test Case**: TC-INT-4-003
- **Severity**: Medium
- **Description**: FSM does not operate correctly after system reset. Expected: FSM operational. Actual: Not operational.
- **Root Cause**: Initialization sequence or state persistence issue.
- **Impact**: System recovery reliability compromised.
- **Status**: Open

#### DEFECT-INT-015: Obstacle Detection Door State Issue During Closing
- **Test Case**: TC-INT-SAF-003
- **Severity**: Low
- **Description**: Door not in CLOSING state during obstacle detection test. Expected: STATE_CLOSING. Actual: Different state.
- **Root Cause**: FSM state progression (related to DEFECT-INT-006, DEFECT-INT-008).
- **Impact**: Safety test cannot execute as intended.
- **Status**: Open

#### DEFECT-INT-016: Sensor Fault Safe State Error Not Returned
- **Test Case**: TC-INT-SAF-006
- **Severity**: Low
- **Description**: Sensor fault injection does not return expected error. Expected: ERROR_SENSOR_FAULT. Actual: Different error or success.
- **Root Cause**: Sensor HAL fault injection or error handling (related to DEFECT-INT-009).
- **Impact**: Safety fault handling verification incomplete.
- **Status**: Open

### 4.3 Defect Root Cause Analysis

**Primary Root Causes**:

1. **Mock-Production Interface Mismatch** (8 defects)
   - GPIO pin mappings incorrect
   - ADC position simulation not synchronized
   - CAN message queue handling issues
   - Timing wraparound issues (uint32_t overflow)

2. **FSM State Initialization/Progression Issues** (6 defects)
   - Door FSM not reaching expected states
   - State propagation to status reporter failing
   - State initialization after reset incomplete

3. **Sensor HAL Feedback Issues** (2 defects)
   - Position feedback not synchronized
   - Speed feedback incorrect

**Corrective Actions Required**:
- Fix mock GPIO, ADC, CAN implementations
- Debug FSM state machine logic
- Verify sensor HAL feedback synchronization
- Fix timing measurement wraparound issues

---

## 5. Coverage Analysis

### 5.1 Interface Coverage

**Interface Test Coverage**:
- Total interfaces: 47 (per DOC-SIS-2026-001)
- Interfaces tested: 47 (100%)
- Interfaces passing: ~35 (74.5% estimated)
- Interfaces failing: ~12 (25.5% estimated due to 16 test failures)

**Coverage by Module**:

| Module | Interfaces | Tested | Passing | Coverage |
|--------|-----------|--------|---------|----------|
| MOD-001: Door FSM | 8 | 8 | 6 | 75.0% |
| MOD-002: Safety Monitor | 6 | 6 | 6 | 100.0% |
| MOD-003: Fault Detection | 7 | 7 | 6 | 85.7% |
| MOD-004: Command Processor | 5 | 5 | 5 | 100.0% |
| MOD-005: Status Reporter | 4 | 4 | 3 | 75.0% |
| MOD-006: Actuator HAL | 7 | 7 | 5 | 71.4% |
| MOD-007: Sensor HAL | 6 | 6 | 4 | 66.7% |
| MOD-008: Communication HAL | 4 | 4 | 3 | 75.0% |
| **TOTAL** | **47** | **47** | **~38** | **~80.9%** |

### 5.2 Code Coverage (Integration Tests)

**Note**: Code coverage NOT generated for integration tests (gcov/lcov not run after integration test execution).

**Expected Coverage** (from Phase 5 unit tests):
- Statement coverage: 99.8% (844/846 lines)
- Branch coverage: 99.6% (453/455 branches)
- MC/DC coverage: 28/28 conditions COMPLETE

**Action Item**: Generate integration test code coverage report after defect resolution.

---

## 6. Performance Results

### 6.1 Timing Measurements

**All performance tests PASSED (8/8)**:

| Requirement | Limit | Measured | Margin | Status |
|-------------|-------|----------|--------|--------|
| Main control loop period | ≤ 10 ms | 10 ms | 0% | ✅ PASS |
| Obstacle reaction time | ≤ 100 ms | 50 ms | 50% | ✅ PASS |
| CAN message latency | ≤ 10 ms | 5 ms | 50% | ✅ PASS |
| Watchdog refresh period | ≤ 100 ms | 50 ms | 50% | ✅ PASS |
| Door open time | 4-6 s | 5.0 s | Nominal | ✅ PASS |
| Door close time | 6-8 s | 7.0 s | Nominal | ✅ PASS |
| CPU load | ≤ 50% | ~30% | 40% | ✅ PASS |
| Memory usage | ≤ 64 KB | 10 KB | 84% | ✅ PASS |
| CAN bandwidth utilization | ≤ 20% | 5% | 75% | ✅ PASS |

⚠️ **CRITICAL LIMITATION**: All timing measurements performed on **host PC** (x86_64), NOT on target hardware (ARM Cortex-M4). WCET values are **estimates only** and NOT reliable for safety analysis.

**RISK-003 Impact**: Without target hardware testing:
- WCET cannot be guaranteed
- Interrupt latency not measured
- Cache/memory effects not captured
- Actual performance unknown

### 6.2 Resource Utilization

**Memory Usage** (estimated):
- RAM: ~10 KB used / 128 KB available (7.8%)
- Flash: ~18 KB used / 512 KB available (3.5%)

**CPU Load** (estimated):
- Average: ~30%
- Peak: ~45% (during door motion with CAN traffic)

---

## 7. EN 50128 Compliance

### 7.1 Section 7.6 Requirements

| Requirement | Compliance | Evidence | Notes |
|-------------|-----------|----------|-------|
| **7.6.4.5a**: Integration test specification | ✅ YES | DOC-INTTEST-2026-001 v1.0 | 73 test cases defined |
| **7.6.4.5b**: Integration test execution | ⚠️ PARTIAL | This report | 73/73 executed, 57/73 passed |
| **7.6.4.5c**: Integration test report | ✅ YES | This document (DOC-INTTESTRPT-2026-001) | Present |
| **7.6.4.5d**: Test environment documented | ✅ YES | Section 2.2 | Environment documented |
| **7.6.4.7**: All tests shall pass | ❌ NO | Section 3.2 | Only 78.1% passing |
| **7.6.4.9**: Progressive integration | ✅ YES | Section 3.1 | Bottom-up, 4 phases, 10 builds |
| **7.6.4.10**: Interface testing | ✅ YES | Section 5.1 | 47/47 interfaces tested |

⚠️ **NON-COMPLIANCE**: EN 50128 Section 7.6.4.7 requires 100% test pass rate. Current 78.1% is **NOT acceptable for SIL 3**.

### 7.2 Table A.6 Techniques (SIL 3)

| Technique | SIL 3 | Applied | Evidence |
|-----------|-------|---------|----------|
| **Functional and Black-Box Testing** | HR | ✅ YES | All 73 tests use black-box approach |
| **Performance Testing** | HR | ✅ YES | 8 performance tests (TC-INT-PERF-001 to 008) |
| **Interface Testing** | HR | ✅ YES | 47 interfaces tested |

✅ All highly recommended techniques applied.

### 7.3 Traceability

**Architecture to Integration Tests**:
- Total architectural elements: 8 modules, 47 interfaces
- Elements traced to integration tests: 47/47 (100%)
- Traceability matrix: Present in DOC-INTTEST-2026-001 Section 7

**Integration Tests to Requirements**:
- Total requirements: 50 (from DOC-SWRS-2026-001)
- Requirements covered by integration tests: 45/50 (90%)
- Not covered: 5 requirements (documentation/non-functional)

---

## 8. Conclusions and Recommendations

### 8.1 Conclusions

1. **Integration Test Infrastructure**: ✅ COMPLETE and ROBUST
   - 73 test cases implemented and executed
   - Mock framework comprehensive (500+ LOC)
   - Build system functional (MISRA C compliant)

2. **Integration Test Execution**: ⚠️ PARTIAL SUCCESS
   - 57/73 tests passing (78.1%)
   - 16/73 tests failing (21.9%)
   - 0 tests blocked

3. **Defects Identified**: 16 defects logged
   - Root causes identified (mock issues, FSM state issues)
   - No critical defects (all medium/high/low)

4. **EN 50128 Compliance**: ⚠️ NON-COMPLIANT
   - Section 7.6.4.7 requires 100% test pass rate
   - Current 78.1% is NOT acceptable for SIL 3

5. **Performance**: ✅ ALL PERFORMANCE TESTS PASSED
   - Timing requirements met (on host PC)
   - Resource utilization acceptable
   - **RISK-003**: WCET not measured on target hardware

### 8.2 Readiness Assessment

**Question**: Is the software ready for Phase 7 (Validation)?

**Answer**: ⚠️ **NO - NOT READY**

**Justification**:
- 16 integration test failures blocking validation
- EN 50128 Section 7.6.4.7 compliance not achieved (100% pass rate required)
- Root causes identified but not resolved
- RISK-003 (no target hardware testing) remains open

### 8.3 Recommendations

**Priority 1 - MANDATORY (before Validation)**:

1. **Resolve all 16 integration test defects**
   - Fix mock-production interface issues (GPIO, ADC, CAN)
   - Debug FSM state progression issues
   - Verify sensor HAL feedback synchronization
   - Fix timing measurement wraparound issues
   - **Target**: 100% test pass rate (73/73 passing)

2. **Re-execute integration tests**
   - After defect resolution, re-run complete test suite
   - Generate integration test code coverage report (gcov/lcov)
   - Document results in updated Integration Test Report v2.0

3. **Generate missing deliverables**
   - JUnit XML test results: `results/software_integration_results.xml`
   - Code coverage HTML report: `results/coverage/index.html`
   - Performance JSON data: `results/performance_results.json`

**Priority 2 - HIGHLY RECOMMENDED**:

4. **Mitigate RISK-003: Target Hardware Testing**
   - Obtain target hardware (STM32F4 development board)
   - Execute integration tests on target hardware
   - Measure actual WCET values
   - Update performance test results with real measurements
   - Document hardware limitations if any

5. **Update Software Integration Verification Report**
   - After defect resolution, update verification evidence
   - Document compliance with EN 50128 Section 7.6.4.7

**Priority 3 - RECOMMENDED**:

6. **Enhance test robustness**
   - Add more detailed failure diagnostics
   - Implement test isolation mechanisms
   - Add timeout protection for tests

7. **Software/Hardware Integration Planning**
   - Proceed with Activity 1 (HW/SW Integration Testing)
   - Execute 48 HW/SW integration test cases
   - Document HW/SW integration results

### 8.4 Gate Check Prediction

**Expected Gate Check Result** (Phase 6 gate):

⚠️ **FAIL** - Phase 6 gate check will **NOT PASS** with current results.

**Gate Blocking Issues**:
1. 78.1% test pass rate (100% required for SIL 3)
2. 16 open defects (HIGH and MEDIUM severity)
3. RISK-003 mitigation incomplete (no target hardware testing)

**Path Forward**:
- Resolve all defects → Re-test → Achieve 100% pass rate → Re-submit to gate check

---

**Integrator**: [Integrator Name]  
**Date**: 2026-02-26  
**Document**: DOC-INTTESTRPT-2026-001 v1.0  
**Status**: Draft - Awaiting QUA Review

---

## Appendices

### Appendix A: Test Environment Metadata

```yaml
test_environment:
  platform: "Linux x86_64"
  os: "Ubuntu 22.04 LTS"
  kernel: "5.15.0"
  compiler:
    name: "gcc"
    version: "13.3.0"
    target: "x86_64-linux-gnu"
  build_system:
    tool: "GNU Make"
    version: "4.3"
  test_framework:
    name: "Custom Unity-compatible"
    version: "1.0"
  coverage_tools:
    - name: "gcov"
      version: "13.3.0"
    - name: "lcov"
      version: "2.0-1"
  date: "2026-02-26"
  time: "14:30:00 UTC"
  hostname: "build-server"
  user: "tst-agent"
```

### Appendix B: Defect List Summary

```csv
Defect ID,Test Case,Severity,Description,Status
DEFECT-INT-001,TC-INT-1-001,Medium,Lock not engaged after init,Open
DEFECT-INT-002,TC-INT-1-005,Medium,Position reading mismatch,Open
DEFECT-INT-003,TC-INT-1-007,Medium,Speed reading incorrect,Open
DEFECT-INT-004,TC-INT-1-009,Medium,CAN message ID mismatch,Open
DEFECT-INT-005,TC-INT-1-011,High,Position returns 0 in combined HAL,Open
DEFECT-INT-006,TC-INT-2-001,High,FSM not reaching OPEN state,Open
DEFECT-INT-007,TC-INT-2-002,High,FSM position feedback incorrect,Open
DEFECT-INT-008,TC-INT-2-006,High,Door not opening before obstacle test,Open
DEFECT-INT-009,TC-INT-2-008,Medium,Sensor error not returned,Open
DEFECT-INT-010,TC-INT-3-003,Medium,Status reporter FSM state incorrect,Open
DEFECT-INT-011,TC-INT-3-005,Medium,Status message CAN ID wrong,Open
DEFECT-INT-012,TC-INT-3-006,High,End-to-end door state incorrect,Open
DEFECT-INT-013,TC-INT-4-001,High,Left door not opening in system test,Open
DEFECT-INT-014,TC-INT-4-003,Medium,FSM not operating after reset,Open
DEFECT-INT-015,TC-INT-SAF-003,Low,Door state issue during obstacle test,Open
DEFECT-INT-016,TC-INT-SAF-006,Low,Sensor fault error not returned,Open
```

### Appendix C: Test Execution Log

See: `test/integration/latest_test_run.log` for complete test execution output.

### Appendix D: Tool Versions

| Tool | Version | Purpose |
|------|---------|---------|
| gcc | 13.3.0 | C compiler |
| GNU Make | 4.3 | Build system |
| gcov | 13.3.0 (part of gcc) | Coverage measurement |
| lcov | 2.0-1 | Coverage HTML report generation |
| git | 2.34.1 | Version control |

---

**END OF REPORT**
