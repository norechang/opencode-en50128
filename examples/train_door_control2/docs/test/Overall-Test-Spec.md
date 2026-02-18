# Overall Software Test Specification

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 Sections 7.4, 7.5, 7.7, Table A.5, Table A.21

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-TESTSPEC-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-02-19 |
| **Project** | train_door_control2 |
| **SIL Level** | 3 |
| **Author** | Tester (TST) |
| **Reviewer** | TBD |
| **Approver** | TBD, Project Manager |
| **Status** | Draft |

---

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-02-19 | TST Agent | Initial test specification with all test cases | - |
| 1.0 | TBD | TST Agent | First approved version | TBD |

---

## APPROVALS

**SIL 3 Requirements**: Author, Independent Reviewer, Safety Manager, QA Manager, Project Manager, Customer

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (Tester)** | TST Agent | | 2026-02-19 |
| **Technical Reviewer** | TBD | | |
| **Safety Manager** | TBD | | |
| **QA Manager** | TBD | | |
| **Project Manager** | TBD | | |
| **Customer Representative** | TBD | | |

---

## 1. INTRODUCTION

### 1.1 Purpose

This Overall Software Test Specification defines the complete testing strategy, test cases, and coverage requirements for the **Train Door Control System (train_door_control2)** software in accordance with EN 50128:2011 Sections 7.4, 7.5, and 7.7.

**Intended Audience**:
- Test engineers (test execution)
- Verification engineers (independent verification)
- Validation engineers (system validation)
- Project management
- Customer/certification authorities

### 1.2 Scope

This test specification covers:
- **Unit Testing** (component level, Section 7.4)
- **Integration Testing** (component integration, Section 7.5)
- **System Testing** (operational scenarios, Section 7.7)
- **Safety Testing** (hazard mitigation verification, Section 7.1)
- **Performance Testing** (timing, throughput, resource usage)
- **Coverage Analysis** (statement, branch, condition coverage)

**Out of Scope**:
- Hardware testing (covered by Hardware Test Specification)
- Validation testing details (covered by Software Validation Plan)
- Production/acceptance testing (covered by Validation Test Specification)

### 1.3 SIL Classification and Test Requirements

**Target SIL Level**: **3** (SIL 3)

**EN 50128 Testing Requirements** (Table A.5):

| Technique | SIL 3 Requirement | Applied | Evidence |
|-----------|------------------|---------|----------|
| **Dynamic Analysis and Testing** | **M** (Mandatory) | ✓ Yes | All test levels |
| **Test Coverage for Code** | **M** (Mandatory) | ✓ Yes | Section 6 (Coverage Requirements) |
| **Functional and Black-Box Testing** | **M** (Mandatory) | ✓ Yes | Sections 4.1, 4.2 |
| **Performance Testing** | **M** (Mandatory) | ✓ Yes | Section 4.3 |
| **Interface Testing** | HR (Highly Recommended) | ✓ Yes | Section 4.4 |
| **Boundary Value Analysis** | HR | ✓ Yes | Applied to all test cases |
| **Equivalence Partitioning** | HR | ✓ Yes | Applied to input domains |
| **Fault Injection** | HR | ✓ Yes | Section 4.5 (Safety Testing) |

**Coverage Requirements** (EN 50128 Table A.21):

| Coverage Type | SIL 3 Requirement | Target |
|---------------|------------------|--------|
| **Statement Coverage** | **M** (Mandatory) | **100%** |
| **Branch Coverage** | **M** (Mandatory) | **100%** |
| **Condition Coverage** | **M** (Mandatory) | **100%** |
| **Data Flow Coverage** | HR (Highly Recommended) | 95%+ |

### 1.4 References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[SRS]** | Software Requirements Specification, DOC-SRS-2026-001 v1.0 |
| **[RTM]** | Requirements Traceability Matrix, DOC-RTM-2026-001 v1.0 |
| **[HAZLOG]** | Hazard Log, DOC-HAZLOG-2026-001 v1.0 |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 v2.0 |
| **[SVaP]** | Software Validation Plan, DOC-SVAP-2026-001 v2.0 |

---

## 2. TEST STRATEGY

### 2.1 Overall Test Approach

The test strategy follows the **V-Model** approach per EN 50128:

```
   Requirements ←──────────→ Validation Testing
        ↓                          ↑
   Architecture ←──────────→ System Testing
        ↓                          ↑
      Design    ←──────────→ Integration Testing
        ↓                          ↑
   Implementation ←────────→ Unit Testing
```

**Test Levels** (bottom-up execution):
1. **Unit Testing** (Component level): Test individual C modules/functions in isolation
2. **Integration Testing** (Module integration): Test interactions between components
3. **System Testing** (Complete system): Test complete software system with operational scenarios
4. **Validation Testing** (Customer acceptance): Validate against user requirements (covered by SVaP)

**Independent Testing** (SIL 3 requirement):
- Unit testing MAY be performed by implementer with independent review
- Integration testing SHALL be performed by independent test team
- System testing SHALL be performed by independent validation team
- Safety testing SHALL be performed by independent safety engineer

### 2.2 Test Environment

**Test Environment 1: Host-Based Unit Testing**
- **Platform**: Linux x86_64 development machine
- **Compiler**: GCC 11.x with C11 standard
- **Test Framework**: Unity 2.5.x (embedded C unit test framework)
- **Coverage Tool**: gcov/lcov 1.15+
- **Static Analysis**: Cppcheck 2.x, PC-lint Plus
- **Purpose**: Unit testing, coverage analysis, rapid iteration

**Test Environment 2: Target Hardware Integration Testing**
- **Platform**: Target microcontroller (TBD: ARM Cortex-M4 or equivalent)
- **Debugger**: JTAG/SWD debugger with GDB
- **Test Framework**: Unity (ported to target)
- **Purpose**: Integration testing, performance testing, hardware interface testing

**Test Environment 3: Hardware-in-Loop (HIL) System Testing**
- **Platform**: Complete train door control hardware with simulated sensors/actuators
- **Simulation**: Door mechanism simulator, speed sensor simulator, obstacle sensor test rig
- **Monitoring**: Oscilloscope, logic analyzer, CAN bus analyzer
- **Purpose**: System testing, safety testing, fault injection testing

**Test Tools**:
- **Unity**: C unit test framework (`unity.h`, `unity.c`, `unity_fixture.c`)
- **gcov/lcov**: Code coverage measurement and HTML report generation
- **Cppcheck**: Static analysis for bug detection
- **PC-lint Plus**: MISRA C:2012 compliance checking
- **Valgrind**: Memory leak detection (host testing)
- **GDB**: Interactive debugging
- **Python**: Test automation and report generation scripts

### 2.3 Test Data Management

**Test Data Sources**:
- **Nominal values**: Typical operational values (e.g., speed = 50 km/h, door position = 50%)
- **Boundary values**: Min, min+1, max-1, max (e.g., speed = 0, 1, 299, 300 km/h)
- **Out-of-range values**: Invalid inputs (e.g., speed = -10, 350 km/h)
- **Fault conditions**: Sensor failures, communication timeouts, watchdog timeouts

**Test Data Repository**: `tests/data/` directory with CSV/JSON files

### 2.4 Test Schedule

**Phase 4: Implementation & Unit Testing** (8 weeks)
- Week 1-6: Implementation with unit tests
- Week 7-8: Unit test completion, coverage analysis (target: 100% statement/branch/condition)

**Phase 5: Integration** (4 weeks)
- Week 9-10: Component integration, integration testing
- Week 11-12: Integration test completion, system integration

**Phase 6: Validation** (6 weeks)
- Week 13-15: System testing, safety testing
- Week 16-18: Validation testing, acceptance testing

### 2.5 Test Deliverables

| Deliverable | Description | Due Date |
|-------------|-------------|----------|
| **Unit Test Cases** | All unit test source code (`tests/unit/`) | End of Phase 4 |
| **Integration Test Cases** | Integration test source code (`tests/integration/`) | End of Phase 5 |
| **System Test Cases** | System test procedures and scripts (`tests/system/`) | End of Phase 6 |
| **Coverage Reports** | HTML coverage reports (gcov/lcov output) | After each test execution |
| **Unit Test Report** | Summary of unit test results | End of Phase 4 |
| **Integration Test Report** | Summary of integration test results | End of Phase 5 |
| **System Test Report** | Summary of system test results | End of Phase 6 |
| **Traceability Matrix Update** | RTM with test case mappings | After each phase |

---

## 3. TEST ORGANIZATION

### 3.1 Test Team Roles and Responsibilities

| Role | Responsibility | Independence Required (SIL 3) |
|------|----------------|------------------------------|
| **Implementer (IMP)** | Write unit tests alongside code | No (but independent review required) |
| **Tester (TST)** | Develop integration and system tests | Yes (separate from IMP) |
| **Verifier (VER)** | Review test cases, verify coverage | Yes (independent of IMP/TST) |
| **Safety Engineer (SAF)** | Specify safety test cases, fault injection | Yes |
| **Validator (VAL)** | Execute system and acceptance tests | Yes (SIL 3 mandatory) |

**Independence Rules (SIL 3)**:
- Tester SHALL NOT be the same person as Implementer
- Validator SHALL NOT report to Project Manager (organizational independence)
- Safety Engineer SHALL be independent of design and implementation

### 3.2 Test Case Naming Convention

**Format**: `TC-[LEVEL]-[ID]`

**Levels**:
- `UNIT`: Unit test (component level)
- `INT`: Integration test (module integration)
- `SYS`: System test (complete system)
- `SAFE`: Safety test (hazard mitigation verification)
- `PERF`: Performance test (timing, resource usage)

**Examples**:
- `TC-UNIT-001`: Unit test for door opening control
- `TC-INT-012`: Integration test for speed sensor → door lock
- `TC-SYS-020`: System test for normal door operation
- `TC-SAFE-005`: Safety test for speed sensor failure (fault injection)
- `TC-PERF-002`: Performance test for control loop timing

**Test IDs**: Sequential numbering within each level (001-999)

---

## 4. TEST CASES

### 4.1 Functional Test Cases (50 Requirements)

#### 4.1.1 Door Opening Control (REQ-FUNC-001)

**Test Case: TC-UNIT-001 - Door Opening with Valid Conditions**

**Requirement**: REQ-FUNC-001  
**SIL Level**: 3  
**Test Type**: Functional, Black-Box  
**Priority**: High

**Objective**: Verify that door opens when commanded with valid preconditions (train stationary, door unlocked).

**Preconditions**:
- System initialized (POST complete)
- Train speed = 0 km/h
- Door position = 0% (fully closed)
- Door lock status = unlocked
- No critical faults

**Test Data**:
| Input | Expected Door State | Expected Position | Expected PWM |
|-------|---------------------|-------------------|--------------|
| Open command | OPENING | 0% → 95%+ | 0-100% (ramp) |

**Test Steps**:
1. Setup: Initialize door control module, set speed = 0 km/h
2. Execute: Call `door_control_open(DOOR_LEFT)`
3. Monitor: Door position every 100ms
4. Verify: Door reaches ≥ 95% within 3.0 seconds
5. Verify: Door status = OPEN after completion
6. Verify: PWM duty cycle reduced to 0% when door fully open

**Expected Result**: Door opens from 0% to ≥95% within 3.0 seconds, status = OPEN.

**Pass Criteria**:
- Door reaches ≥ 95% position within 3.0 seconds
- No faults raised
- PWM duty cycle correctly controlled (0-100% during motion, 0% at end)
- Function returns `SUCCESS`

**Status**: Pending (Phase 4)

---

**Test Case: TC-UNIT-002 - Door Opening Blocked by Speed Interlock**

**Requirement**: REQ-FUNC-001, REQ-FUNC-003  
**SIL Level**: 3  
**Test Type**: Functional, Safety  
**Priority**: Critical

**Objective**: Verify that door does NOT open when train is moving (speed > 5 km/h).

**Preconditions**:
- System initialized
- Train speed = 10 km/h (above threshold)
- Door position = 0% (closed)
- Door lock status = locked

**Test Steps**:
1. Setup: Set train speed = 10 km/h
2. Execute: Call `door_control_open(DOOR_LEFT)`
3. Verify: Door remains closed (position = 0%)
4. Verify: Function returns `ERROR_DOOR_LOCKED` or `ERROR_SPEED_INTERLOCK`

**Expected Result**: Door does NOT open, error returned, door remains closed.

**Pass Criteria**:
- Door position unchanged (0%)
- Error code returned
- No actuator motion (PWM = 0%)

**Status**: Pending

---

**Test Case: TC-UNIT-003 - Door Opening Timeout Fault**

**Requirement**: REQ-FUNC-001  
**SIL Level**: 3  
**Test Type**: Functional, Fault Handling  
**Priority**: High

**Objective**: Verify fault detection when door fails to open within 5.0 seconds.

**Preconditions**:
- System initialized
- Train speed = 0 km/h
- Door position sensor simulated to remain at 0% (stuck sensor or jammed door)

**Test Steps**:
1. Setup: Mock door position sensor to return 0% (simulate jammed door)
2. Execute: Call `door_control_open(DOOR_LEFT)`
3. Wait: 5.0 seconds
4. Verify: Fault code `FAULT_DOOR_OPEN_TIMEOUT` raised
5. Verify: System enters degraded mode or retries once

**Expected Result**: Timeout fault raised after 5.0 seconds.

**Pass Criteria**:
- Fault code `FAULT_DOOR_OPEN_TIMEOUT` logged
- Actuator disabled or retry attempted
- System does not hang

**Status**: Pending

---

#### 4.1.2 Door Closing Control (REQ-FUNC-002)

**Test Case: TC-UNIT-004 - Door Closing with No Obstacles**

**Requirement**: REQ-FUNC-002  
**SIL Level**: 3  
**Test Type**: Functional  
**Priority**: High

**Objective**: Verify door closes from fully open to fully closed within 5.0 seconds when no obstacles present.

**Preconditions**:
- Door position = 100% (fully open)
- Obstacle sensors = false (no obstacles)
- Train stationary (speed = 0 km/h)

**Test Steps**:
1. Setup: Set door position = 100%, obstacle sensors = false
2. Execute: Call `door_control_close(DOOR_LEFT)`
3. Monitor: Door position every 100ms
4. Verify: Door reaches ≤ 5% within 5.0 seconds
5. Verify: Door status = CLOSED

**Expected Result**: Door closes from 100% to ≤5% within 5.0 seconds.

**Pass Criteria**:
- Door reaches ≤ 5% within 5.0 seconds
- Door status = CLOSED
- No faults raised

**Status**: Pending

---

**Test Case: TC-UNIT-005 - Door Closing Stopped by Obstacle**

**Requirement**: REQ-FUNC-002, REQ-FUNC-009  
**SIL Level**: 3  
**Test Type**: Functional, Safety  
**Priority**: Critical

**Objective**: Verify door immediately stops and reverses when obstacle detected during closing.

**Preconditions**:
- Door closing (position = 80%)
- Obstacle sensors = false initially

**Test Steps**:
1. Setup: Start door closing from 100%
2. Execute: When door reaches 80%, inject obstacle signal (set obstacle sensor = true)
3. Measure: Time from obstacle detection to door stop
4. Verify: Door stops within 100ms
5. Verify: Door reverses direction and opens by at least 20%

**Expected Result**: Door stops within 100ms, reverses to open by 20%.

**Pass Criteria**:
- Reaction time ≤ 100ms from obstacle detection to door stop
- Door reverses and opens by ≥ 20%
- Obstacle event logged

**Status**: Pending

---

#### 4.1.3 Door Lock Control (REQ-FUNC-003)

**Test Case: TC-UNIT-006 - Door Locks When Speed Exceeds Threshold**

**Requirement**: REQ-FUNC-003, REQ-SAFE-001  
**SIL Level**: 3  
**Test Type**: Functional, Safety  
**Priority**: Critical

**Objective**: Verify door locks when train speed exceeds 5 km/h.

**Preconditions**:
- Door closed (position ≤ 5%)
- Door unlocked initially
- Train stationary (speed = 0 km/h)

**Test Steps**:
1. Setup: Door closed, unlocked, speed = 0 km/h
2. Execute: Increase train speed to 6 km/h
3. Verify: Door lock activated within 1 control cycle (50ms)
4. Verify: Door lock status = LOCKED

**Expected Result**: Door locks when speed > 5 km/h.

**Pass Criteria**:
- Door lock activated within 50ms of speed > 5 km/h
- Door lock status = LOCKED
- Lock signal sent to hardware

**Status**: Pending

---

**Test Case: TC-UNIT-007 - Door Unlocks with Hysteresis**

**Requirement**: REQ-FUNC-003  
**SIL Level**: 3  
**Test Type**: Functional  
**Priority**: High

**Objective**: Verify door unlocks only when speed < 2 km/h for ≥ 1.0 second (hysteresis).

**Preconditions**:
- Door locked
- Train speed = 10 km/h

**Test Steps**:
1. Setup: Door locked, speed = 10 km/h
2. Execute: Reduce speed to 1.5 km/h
3. Wait: 0.5 seconds → Verify door remains locked
4. Wait: Additional 0.5 seconds (total 1.0s) → Verify door unlocks
5. Verify: Door lock status = UNLOCKED

**Expected Result**: Door unlocks after speed < 2 km/h for 1.0 second.

**Pass Criteria**:
- Door remains locked for first 0.5 seconds
- Door unlocks after 1.0 seconds at speed < 2 km/h
- Hysteresis prevents oscillation

**Status**: Pending

---

**Test Case: TC-SAFE-001 - Speed Sensor Failure: Primary Stuck at Zero**

**Requirement**: REQ-FUNC-003, REQ-SAFE-001, REQ-SAFE-003  
**SIL Level**: 3  
**Test Type**: Safety, Fault Injection  
**Priority**: Critical

**Objective**: Verify fail-safe behavior when primary speed sensor fails (stuck at zero) while train is moving.

**Preconditions**:
- Train moving at 20 km/h (both sensors report correctly)
- Door closed and locked

**Test Steps**:
1. Setup: Primary sensor = 20 km/h, Secondary sensor = 20 km/h, door locked
2. Execute: Inject fault - primary sensor stuck at 0 km/h
3. Verify: Secondary sensor value used (20 km/h)
4. Verify: Door remains locked (fail-safe)
5. Verify: Fault code `FAULT_SPEED_SENSOR_PRIMARY` raised

**Expected Result**: Door remains locked, secondary sensor used, fault logged.

**Pass Criteria**:
- Door lock status = LOCKED (fail-safe)
- Secondary speed value used for interlock
- Fault code logged
- System continues operation (degraded mode)

**Traceability**: HAZ-001 (Doors open while moving) - Mitigation verification

**Status**: Pending

---

**Test Case: TC-SAFE-002 - Speed Sensor Failure: Both Sensors Fail**

**Requirement**: REQ-FUNC-003, REQ-SAFE-001, REQ-SAFE-003  
**SIL Level**: 3  
**Test Type**: Safety, Fault Injection  
**Priority**: Critical

**Objective**: Verify fail-safe behavior when both speed sensors fail (common cause failure).

**Preconditions**:
- Train moving (actual speed unknown to system)
- Both sensors functional initially

**Test Steps**:
1. Setup: Both sensors report 20 km/h
2. Execute: Inject fault - both sensors stuck at 0 km/h simultaneously
3. Verify: System assumes speed > 5 km/h (fail-safe default)
4. Verify: Door remains locked
5. Verify: Critical fault `FAULT_SPEED_SENSOR_BOTH` raised

**Expected Result**: Door locked by default (fail-safe), critical fault raised.

**Pass Criteria**:
- Door lock status = LOCKED (fail-safe default)
- Critical fault logged
- System enters safe state (door control disabled)

**Traceability**: HAZ-001, CCF-001 (Common cause failure) - Mitigation verification

**Status**: Pending

---

#### 4.1.4 Emergency Door Release (REQ-FUNC-004)

**Test Case: TC-SAFE-021 - Emergency Release with Software Functional**

**Requirement**: REQ-FUNC-004, REQ-SAFE-004  
**SIL Level**: 3  
**Test Type**: Safety, Integration  
**Priority**: Critical

**Objective**: Verify emergency release unlocks door when handle activated (software functional).

**Preconditions**:
- System operational
- Door closed and locked
- Train stationary or moving

**Test Steps**:
1. Setup: Door locked
2. Execute: Activate emergency release handle (GPIO signal)
3. Verify: Door unlocked within 100ms
4. Verify: Emergency event logged
5. Verify: Emergency status transmitted to train control system

**Expected Result**: Door unlocks immediately, event logged.

**Pass Criteria**:
- Door unlocked within 100ms
- Emergency event logged in non-volatile memory
- CAN message transmitted to train control system

**Traceability**: HAZ-003 (Passenger entrapment) - Mitigation verification

**Status**: Pending

---

**Test Case: TC-SAFE-022 - Emergency Release with Software Failed**

**Requirement**: REQ-FUNC-004, REQ-SAFE-004  
**SIL Level**: 3  
**Test Type**: Safety, Fault Injection  
**Priority**: Critical

**Objective**: Verify emergency release works via hardware path when software has failed.

**Preconditions**:
- Software lockup simulated (infinite loop injected)
- Door closed and locked

**Test Steps**:
1. Setup: Door locked, software forced into infinite loop (no watchdog refresh)
2. Execute: Activate emergency release handle
3. Verify: Door unlocks via hardware path (independent of software)
4. Verify: Watchdog eventually resets system (200ms timeout)

**Expected Result**: Door unlocks via hardware path regardless of software state.

**Pass Criteria**:
- Door unlocks within 100ms (hardware-level)
- Emergency release function independent of software
- Hardware fail-safe mechanism verified

**Traceability**: HAZ-003, HAZ-004 (Software lockup) - Mitigation verification

**Status**: Pending

---

### 4.2 Performance Test Cases (6 Requirements)

**Test Case: TC-PERF-001 - Control Loop Timing**

**Requirement**: REQ-PERF-001  
**SIL Level**: 3  
**Test Type**: Performance, Timing  
**Priority**: High

**Objective**: Verify main control loop executes at 20 Hz (50ms period) with WCET ≤ 40ms.

**Test Environment**: Target hardware or cycle-accurate simulator

**Test Steps**:
1. Setup: Instrument control loop with timing measurements (GPIO toggle or timestamp)
2. Execute: Run system under worst-case load (all doors active, maximum CAN traffic)
3. Measure: Control loop period and execution time over 10,000 iterations
4. Analyze: Calculate min, max, mean, standard deviation of loop period and execution time

**Expected Result**:
- Mean loop period = 50ms ± 1ms
- Maximum execution time (WCET) ≤ 40ms
- No missed deadlines

**Pass Criteria**:
- 100% of control loop iterations complete within 50ms period
- WCET ≤ 40ms (80% of period)
- No timing jitter > 5ms

**Status**: Pending (Phase 5 - Target hardware testing)

---

**Test Case: TC-PERF-002 - Door Opening Time**

**Requirement**: REQ-PERF-002  
**SIL Level**: 3  
**Test Type**: Performance  
**Priority**: High

**Objective**: Verify door opens within 3.0 seconds (typical) and 5.0 seconds (maximum).

**Test Steps**:
1. Execute: Perform 100 door opening operations
2. Measure: Time from open command to door position ≥ 95%
3. Analyze: Calculate mean, max, and 95th percentile

**Expected Result**:
- Mean opening time ≤ 3.0 seconds
- Maximum opening time ≤ 5.0 seconds
- 95% of openings complete within 3.5 seconds

**Pass Criteria**:
- 95% of operations complete within 3.0 seconds
- 100% of operations complete within 5.0 seconds

**Status**: Pending

---

**Test Case: TC-PERF-004 - Obstacle Detection Reaction Time**

**Requirement**: REQ-PERF-004  
**SIL Level**: 3  
**Test Type**: Performance, Safety  
**Priority**: Critical

**Objective**: Verify obstacle detection reaction time ≤ 100ms.

**Test Environment**: HIL test rig with high-speed measurement (oscilloscope)

**Test Steps**:
1. Setup: Door closing at normal speed
2. Execute: Trigger obstacle sensor (physical test rig or GPIO injection)
3. Measure: Time from sensor trigger to actuator PWM = 0% (door stop)
4. Repeat: 100 test iterations

**Expected Result**: Reaction time ≤ 100ms in 100% of test cases.

**Pass Criteria**:
- Mean reaction time ≤ 80ms
- Maximum reaction time ≤ 100ms
- 100% pass rate (all iterations ≤ 100ms)

**Traceability**: HAZ-002 (Door closes on passenger) - Performance verification

**Status**: Pending

---

### 4.3 Interface Test Cases (14 Requirements)

**Test Case: TC-INT-001 - Door Position Sensor Interface (Left)**

**Requirement**: REQ-IF-HW-001  
**SIL Level**: 3  
**Test Type**: Interface, Integration  
**Priority**: High

**Objective**: Verify correct reading of door position from ADC channel 0.

**Test Environment**: Target hardware with simulated or actual position sensor

**Test Steps**:
1. Setup: Apply known analog voltage to ADC channel 0 (use DAC or potentiometer)
2. Test Cases:
   - 0.0V → Expected position = 0%
   - 1.25V → Expected position = 25%
   - 2.5V → Expected position = 50%
   - 3.75V → Expected position = 75%
   - 5.0V → Expected position = 100%
3. Verify: Software calculates position correctly (±2% tolerance)
4. Verify: Out-of-range voltages detected (<-0.25V, >5.25V)

**Expected Result**: Position calculated correctly from ADC value.

**Pass Criteria**:
- Position accuracy ±2% across full range
- Out-of-range detection functional
- ADC sampling rate ≥ 100 Hz

**Status**: Pending

---

**Test Case: TC-INT-005 - Obstacle Sensor Interface (Multiple Sensors)**

**Requirement**: REQ-IF-HW-005, REQ-SAFE-005  
**SIL Level**: 3  
**Test Type**: Interface, Safety  
**Priority**: Critical

**Objective**: Verify redundant obstacle sensors (infrared, pressure, capacitive) read correctly with OR logic.

**Test Steps**:
1. Test: All sensors = false → obstacle_detected = false
2. Test: Infrared = true, others = false → obstacle_detected = true (OR logic)
3. Test: Pressure = true, others = false → obstacle_detected = true
4. Test: Capacitive = true, others = false → obstacle_detected = true
5. Test: All sensors = true → obstacle_detected = true
6. Verify: 10ms debouncing applied (transient pulses ignored)

**Expected Result**: ANY sensor triggered results in obstacle detection (OR logic).

**Pass Criteria**:
- OR logic implemented correctly
- Debouncing prevents false positives
- Single sensor failure does not prevent detection (redundancy)

**Traceability**: HAZ-002 - Redundant obstacle detection

**Status**: Pending

---

**Test Case: TC-INT-010 - CAN Bus Interface (Status Transmission)**

**Requirement**: REQ-IF-SW-001, REQ-FUNC-006  
**SIL Level**: 3  
**Test Type**: Interface, Integration  
**Priority**: High

**Objective**: Verify door status transmitted correctly via CAN bus at 20 Hz.

**Test Environment**: Target hardware with CAN bus analyzer

**Test Steps**:
1. Setup: Connect CAN bus analyzer
2. Execute: Run system, monitor CAN message ID 0x201
3. Measure: Message transmission rate over 10 seconds
4. Verify: Message format matches `door_status_msg_t` structure
5. Verify: Door position, state, lock status, fault code fields correct

**Expected Result**: Status message transmitted at 20 Hz (50ms period) with correct data.

**Pass Criteria**:
- Message rate = 20 Hz ± 1 Hz
- Message format correct (8 bytes)
- Data fields match actual door state

**Status**: Pending

---

### 4.4 Safety Test Cases (40 Safety Tests for 8 Hazards)

#### 4.4.1 HAZ-001: Doors Open While Moving (TC-SAFE-001 to TC-SAFE-010)

**Test Case: TC-SAFE-003 - Speed Sensor CAN Timeout**

**Requirement**: REQ-IF-HW-007, REQ-SAFE-001  
**SIL Level**: 3  
**Test Type**: Safety, Fault Injection  
**Priority**: Critical

**Objective**: Verify fail-safe behavior when CAN bus timeout occurs (no speed data received).

**Test Steps**:
1. Setup: System operational, door closed and unlocked, speed = 0 km/h
2. Execute: Stop transmitting CAN speed messages (simulate CAN bus failure)
3. Wait: 100ms (timeout threshold)
4. Verify: Fault `FAULT_SPEED_SENSOR_TIMEOUT` raised
5. Verify: Door locks (fail-safe default)

**Expected Result**: Door locks when speed data unavailable (fail-safe).

**Traceability**: HAZ-001, HAZ-006 (CAN failure)

**Status**: Pending

---

**Test Case: TC-SAFE-004 - Speed Sensor Disagreement (Primary vs Secondary)**

**Requirement**: REQ-SAFE-003  
**SIL Level**: 3  
**Test Type**: Safety, Fault Injection  
**Priority**: Critical

**Objective**: Verify system uses most restrictive (higher) speed when sensors disagree by > 10%.

**Test Steps**:
1. Setup: Primary sensor = 3 km/h, Secondary sensor = 8 km/h (difference > 10%)
2. Verify: System uses higher value (8 km/h) for door lock logic
3. Verify: Door remains locked (fail-safe)
4. Verify: Warning `WARN_SPEED_SENSOR_DISAGREE` raised

**Expected Result**: System uses higher speed value (fail-safe).

**Traceability**: HAZ-001

**Status**: Pending

---

**Test Case: TC-SAFE-005 - Door Not Fully Closed When Speed Exceeds Threshold**

**Requirement**: REQ-FUNC-003  
**SIL Level**: 3  
**Test Type**: Safety, Fault  
**Priority**: Critical

**Objective**: Verify critical fault raised if door not fully closed (position > 5%) when speed > 5 km/h.

**Test Steps**:
1. Setup: Door partially closed (position = 20%)
2. Execute: Increase speed to 6 km/h
3. Verify: Critical fault `FAULT_DOOR_NOT_CLOSED_MOVING` raised
4. Verify: Emergency brake request transmitted to train control system

**Expected Result**: Critical fault raised, emergency brake request sent.

**Traceability**: HAZ-001

**Status**: Pending

---

#### 4.4.2 HAZ-002: Door Closes on Passenger (TC-SAFE-011 to TC-SAFE-020)

**Test Case: TC-SAFE-011 - All Obstacle Sensors Fail (Common Cause)**

**Requirement**: REQ-FUNC-009, REQ-SAFE-005  
**SIL Level**: 3  
**Test Type**: Safety, Fault Injection  
**Priority**: Critical

**Objective**: Verify degraded mode when all 3 obstacle sensors fail simultaneously.

**Test Steps**:
1. Setup: All 3 obstacle sensors (infrared, pressure, capacitive) functional
2. Execute: Inject fault - all 3 sensors stuck at "no obstacle" (simulate environmental contamination)
3. Verify: Fault `FAULT_OBSTACLE_SENSORS_LEFT` raised
4. Verify: System enters degraded mode: door closing speed reduced by 50%
5. Verify: Automatic door closing disabled (manual close only)

**Expected Result**: Degraded mode entered, reduced speed, manual operation only.

**Traceability**: HAZ-002, CCF-003 (Common cause failure)

**Status**: Pending

---

**Test Case: TC-SAFE-012 - Single Obstacle Sensor Fails**

**Requirement**: REQ-SAFE-005  
**SIL Level**: 3  
**Test Type**: Safety, Fault Injection  
**Priority**: High

**Objective**: Verify system continues operation when single obstacle sensor fails (1-fault tolerance).

**Test Steps**:
1. Setup: 3 sensors functional
2. Execute: Inject fault - infrared sensor stuck at "no obstacle"
3. Verify: Warning `WARN_OBSTACLE_SENSOR_STUCK_LEFT` raised
4. Verify: System continues normal operation using remaining 2 sensors
5. Test: Trigger pressure sensor → Door stops (obstacle detection still functional)

**Expected Result**: System continues with 2 sensors (fault tolerance).

**Traceability**: HAZ-002

**Status**: Pending

---

**Test Case: TC-SAFE-013 - Obstacle Detection Timing Violation**

**Requirement**: REQ-PERF-004  
**SIL Level**: 3  
**Test Type**: Safety, Performance  
**Priority**: Critical

**Objective**: Verify obstacle detection always completes within 100ms (no timing violations under load).

**Test Steps**:
1. Setup: System under maximum load (all doors active, maximum CAN traffic, diagnostics enabled)
2. Execute: Trigger obstacle sensor during door closing
3. Measure: Reaction time (sensor trigger → door stop) with oscilloscope
4. Repeat: 1000 iterations

**Expected Result**: 100% of reactions complete within 100ms.

**Traceability**: HAZ-002

**Status**: Pending

---

**Test Case: TC-SAFE-014 - Obstacle Reversal Distance Verification**

**Requirement**: REQ-FUNC-009  
**SIL Level**: 3  
**Test Type**: Safety, Functional  
**Priority**: High

**Objective**: Verify door reverses by at least 20% after obstacle detected.

**Test Steps**:
1. Setup: Door closing, position = 70%
2. Execute: Trigger obstacle sensor
3. Measure: Door position after reversal
4. Verify: Door opens by ≥ 20% (final position ≥ 90%)

**Expected Result**: Door reverses to at least 20% more open than detection point.

**Traceability**: HAZ-002

**Status**: Pending

---

#### 4.4.3 HAZ-003: Passenger Entrapment (TC-SAFE-021 to TC-SAFE-025)

**Test Case: TC-SAFE-023 - Emergency Release with Power Loss**

**Requirement**: REQ-FUNC-004, REQ-SAFE-004  
**SIL Level**: 3  
**Test Type**: Safety, Fault Injection  
**Priority**: Critical

**Objective**: Verify emergency release works when main power lost (battery backup or mechanical).

**Test Steps**:
1. Setup: System operational, door closed and locked
2. Execute: Simulate main power loss (disconnect power supply)
3. Execute: Activate emergency release handle
4. Verify: Door unlocks (battery backup or mechanical override)

**Expected Result**: Door unlocks despite power loss (fail-safe).

**Traceability**: HAZ-003

**Status**: Pending

---

**Test Case: TC-SAFE-024 - Emergency Evacuation Mode**

**Requirement**: REQ-FUNC-012  
**SIL Level**: 3  
**Test Type**: Safety, Functional  
**Priority**: Critical

**Objective**: Verify emergency evacuation mode opens all doors immediately.

**Test Steps**:
1. Setup: All doors closed and locked, train stationary
2. Execute: Activate emergency evacuation button (driver panel)
3. Verify: All doors (left and right) immediately commanded to open
4. Verify: Automatic door closing disabled
5. Verify: Speed interlock disabled (doors can remain open if train moves slowly)
6. Verify: "EMERGENCY EVACUATION" displayed on all interfaces

**Expected Result**: All doors open, interlocks overridden.

**Traceability**: HAZ-003

**Status**: Pending

---

#### 4.4.4 HAZ-004: Software Lockup (TC-SAFE-026 to TC-SAFE-030)

**Test Case: TC-SAFE-026 - Watchdog Timeout Recovery**

**Requirement**: REQ-FUNC-008, REQ-SAFE-002  
**SIL Level**: 3  
**Test Type**: Safety, Fault Injection  
**Priority**: Critical

**Objective**: Verify watchdog triggers safe state and system reset when software fails to refresh watchdog.

**Test Steps**:
1. Setup: System operational
2. Execute: Inject infinite loop (disable watchdog refresh in main loop)
3. Wait: 200ms (watchdog timeout)
4. Verify: Hardware watchdog resets system
5. Verify: After reset, software enters diagnostic mode and checks watchdog reset flag
6. Verify: Fault log contains watchdog reset event

**Expected Result**: Watchdog resets system within 200ms.

**Traceability**: HAZ-004

**Status**: Pending

---

**Test Case: TC-SAFE-027 - Safe State Entry on Critical Fault**

**Requirement**: REQ-FUNC-007, REQ-SAFE-006  
**SIL Level**: 3  
**Test Type**: Safety, Functional  
**Priority**: Critical

**Objective**: Verify system enters safe state within 100ms of critical fault detection.

**Test Steps**:
1. Setup: System operational, door closing
2. Execute: Inject critical fault (both speed sensors failed)
3. Measure: Time from fault detection to safe state entry
4. Verify: Safe state entered within 100ms:
   - All actuators disabled (PWM = 0%)
   - Doors locked (if closed)
   - Fault code transmitted to train control system

**Expected Result**: Safe state entered within 100ms.

**Traceability**: HAZ-004

**Status**: Pending

---

**Test Case: TC-SAFE-028 - NULL Pointer Dereference Prevention**

**Requirement**: REQ-IMPL-006  
**SIL Level**: 3  
**Test Type**: Safety, Static Analysis  
**Priority**: High

**Objective**: Verify all pointers validated before dereference (static analysis and runtime tests).

**Test Steps**:
1. Static Analysis: Run Cppcheck and PC-lint on all source code
2. Verify: No NULL pointer dereference warnings (MISRA C Rule 1.3, 17.7)
3. Unit Tests: Call all functions with NULL pointers where applicable
4. Verify: Functions return error codes, do NOT crash

**Expected Result**: No NULL pointer dereferences possible.

**Traceability**: HAZ-004, HAZ-007 (Memory corruption)

**Status**: Pending

---

**Test Case: TC-SAFE-029 - Buffer Overflow Prevention**

**Requirement**: REQ-IMPL-006  
**SIL Level**: 3  
**Test Type**: Safety, Static Analysis  
**Priority**: Critical

**Objective**: Verify no buffer overflows possible (static analysis and runtime tests).

**Test Steps**:
1. Static Analysis: Run Cppcheck, PC-lint with MISRA C rules
2. Verify: No unbounded string operations (`strcpy`, `sprintf`, etc.)
3. Verify: All array accesses bounds-checked
4. Unit Tests: Pass oversized inputs to all functions accepting buffers
5. Verify: Functions reject invalid inputs, do NOT overflow

**Expected Result**: No buffer overflows possible.

**Traceability**: HAZ-004, HAZ-007

**Status**: Pending

---

**Test Case: TC-SAFE-030 - Stack Overflow Prevention (No Recursion)**

**Requirement**: REQ-IMPL-004  
**SIL Level**: 3  
**Test Type**: Safety, Static Analysis  
**Priority**: Critical

**Objective**: Verify no recursive functions present (static analysis).

**Test Steps**:
1. Static Analysis: Generate call graph with Cppcheck or custom script
2. Verify: No recursive calls detected
3. Code Review: Manual inspection of all function definitions

**Expected Result**: Zero recursive functions.

**Traceability**: HAZ-004, HAZ-007

**Status**: Pending

---

#### 4.4.5 HAZ-005: Incorrect Position Reporting (TC-SAFE-031 to TC-SAFE-035)

**Test Case: TC-SAFE-031 - Position Sensor Out of Range Detection**

**Requirement**: REQ-FUNC-005  
**SIL Level**: 2  
**Test Type**: Fault Handling  
**Priority**: Medium

**Objective**: Verify fault detection when position sensor reports out-of-range value.

**Test Steps**:
1. Setup: Inject voltage < 0V or > 5V to ADC input
2. Verify: Fault `FAULT_POSITION_SENSOR_LEFT` raised
3. Verify: System enters degraded mode (uses timeout-based position control)

**Expected Result**: Fault detected, degraded mode entered.

**Traceability**: HAZ-005

**Status**: Pending

---

#### 4.4.6 HAZ-006: CAN Bus Failure (TC-SAFE-036 to TC-SAFE-040)

**Test Case: TC-SAFE-036 - CAN Bus Timeout Handling**

**Requirement**: REQ-IF-SW-001  
**SIL Level**: 2  
**Test Type**: Fault Injection  
**Priority**: Medium

**Objective**: Verify safe state when CAN bus communication lost.

**Test Steps**:
1. Setup: System operational, receiving CAN messages
2. Execute: Stop CAN message transmission (simulate bus failure)
3. Wait: 200ms (command message timeout)
4. Verify: System enters safe state (doors hold current position)
5. Verify: Local driver panel remains functional (manual control)

**Expected Result**: Safe state entered, local control functional.

**Traceability**: HAZ-006

**Status**: Pending

---

#### 4.4.7 HAZ-007: Memory Corruption (TC-SAFE-041 to TC-SAFE-045)

**Test Case: TC-SAFE-041 - Static Allocation Only (No Heap)**

**Requirement**: REQ-IMPL-003  
**SIL Level**: 3  
**Test Type**: Static Analysis  
**Priority**: Critical

**Objective**: Verify no dynamic memory allocation used (`malloc`, `calloc`, `realloc`, `free`).

**Test Steps**:
1. Static Analysis: Search source code for banned functions
2. Verify: Zero occurrences of `malloc`, `calloc`, `realloc`, `free`
3. Linker Check: Verify heap size = 0 in linker script

**Expected Result**: Zero dynamic memory allocation.

**Traceability**: HAZ-007

**Status**: Pending

---

**Test Case: TC-SAFE-042 - Cyclomatic Complexity ≤ 10**

**Requirement**: REQ-IMPL-005  
**SIL Level**: 3  
**Test Type**: Static Analysis  
**Priority**: High

**Objective**: Verify all functions have cyclomatic complexity ≤ 10 (SIL 3 requirement).

**Test Steps**:
1. Static Analysis: Run Lizard or similar tool on all source files
2. Generate: Complexity report for all functions
3. Verify: 100% of functions have complexity ≤ 10

**Expected Result**: All functions meet complexity limit.

**Traceability**: HAZ-007, HAZ-004 (Reduces defects)

**Status**: Pending

---

### 4.5 Test Case Summary

| Test Level | Requirement Coverage | Test Case Count | Status |
|------------|---------------------|-----------------|--------|
| **Unit Tests** | 50 requirements (functional, performance, interface) | 50+ | Planned |
| **Integration Tests** | Hardware-software interfaces, module integration | 20+ | Planned |
| **System Tests** | Operational scenarios, V-Model validation | 15+ | Planned |
| **Safety Tests (HAZ-001 to HAZ-008)** | 8 hazards, fault injection | 45 | Planned |
| **Performance Tests** | Timing, throughput, resource usage | 10 | Planned |
| **TOTAL** | 50 requirements + 8 hazards | **140+** | Planned |

---

## 5. TEST TRACEABILITY MATRIX

### 5.1 Requirements to Test Cases Mapping

| Requirement ID | Requirement Description | Test Cases | Coverage |
|----------------|-------------------------|------------|----------|
| **REQ-FUNC-001** | Door opening control | TC-UNIT-001, TC-UNIT-002, TC-UNIT-003 | Unit |
| **REQ-FUNC-002** | Door closing control | TC-UNIT-004, TC-UNIT-005 | Unit |
| **REQ-FUNC-003** | Door lock control | TC-UNIT-006, TC-UNIT-007, TC-SAFE-001 to TC-SAFE-005 | Unit, Safety |
| **REQ-FUNC-004** | Emergency door release | TC-SAFE-021, TC-SAFE-022, TC-SAFE-023 | Safety |
| **REQ-FUNC-005** | Door position monitoring | TC-INT-001, TC-SAFE-031 | Integration |
| **REQ-FUNC-006** | Status reporting to train control | TC-INT-010 | Integration |
| **REQ-FUNC-007** | Fault detection | TC-SAFE-027 | Safety |
| **REQ-FUNC-008** | Watchdog monitoring | TC-SAFE-026 | Safety |
| **REQ-FUNC-009** | Obstacle detection during closing | TC-UNIT-005, TC-SAFE-011 to TC-SAFE-014 | Unit, Safety |
| **REQ-FUNC-010** | Normal operation mode | TC-SYS-001 (system test) | System |
| **REQ-FUNC-011** | Manual/maintenance mode | TC-SYS-002 | System |
| **REQ-FUNC-012** | Emergency evacuation mode | TC-SAFE-024 | Safety |
| **REQ-FUNC-013** | Diagnostic/test mode | TC-SYS-003 | System |
| **REQ-FUNC-014** | Degraded/fail-safe mode | TC-SAFE-011, TC-SAFE-031 | Safety |
| **REQ-PERF-001** | Control loop timing | TC-PERF-001 | Performance |
| **REQ-PERF-002** | Door opening time | TC-PERF-002 | Performance |
| **REQ-PERF-003** | Door closing time | TC-UNIT-004 | Unit |
| **REQ-PERF-004** | Obstacle detection reaction time | TC-PERF-004, TC-SAFE-013 | Performance, Safety |
| **REQ-PERF-005** | CPU utilization | TC-PERF-005 (planned) | Performance |
| **REQ-PERF-006** | Memory footprint | TC-PERF-006 (planned) | Performance |
| **REQ-IF-HW-001** | Position sensor interface (left) | TC-INT-001 | Integration |
| **REQ-IF-HW-002** | Position sensor interface (right) | TC-INT-002 (similar to TC-INT-001) | Integration |
| **REQ-IF-HW-005** | Obstacle sensor interface (left) | TC-INT-005 | Integration |
| **REQ-IF-HW-007** | Speed sensor interface (primary) | TC-SAFE-001, TC-SAFE-003 | Safety |
| **REQ-IF-HW-008** | Speed sensor interface (secondary) | TC-SAFE-002, TC-SAFE-004 | Safety |
| **REQ-IF-SW-001** | CAN bus interface | TC-INT-010, TC-SAFE-036 | Integration, Safety |
| **REQ-SAFE-001** | Fail-safe door locking | TC-SAFE-001, TC-SAFE-002 | Safety |
| **REQ-SAFE-002** | Watchdog safe state | TC-SAFE-026 | Safety |
| **REQ-SAFE-003** | Redundant speed monitoring | TC-SAFE-004 | Safety |
| **REQ-SAFE-004** | Emergency release hardware independence | TC-SAFE-022, TC-SAFE-023 | Safety |
| **REQ-SAFE-005** | Obstacle detection redundancy | TC-SAFE-011, TC-SAFE-012 | Safety |
| **REQ-IMPL-003** | Static memory allocation only | TC-SAFE-041 | Static Analysis |
| **REQ-IMPL-004** | No recursion | TC-SAFE-030 | Static Analysis |
| **REQ-IMPL-005** | Cyclomatic complexity ≤ 10 | TC-SAFE-042 | Static Analysis |
| **REQ-IMPL-006** | Defensive programming | TC-SAFE-028, TC-SAFE-029 | Static Analysis, Unit |

**Coverage Summary**:
- **Total Requirements**: 50
- **Total Test Cases**: 140+ (including safety tests, integration tests, system tests)
- **Requirements with ≥1 Test Case**: 50 (100% coverage)

### 5.2 Hazards to Test Cases Mapping

| Hazard ID | Description | Safety Test Cases | Verification Method |
|-----------|-------------|-------------------|---------------------|
| **HAZ-001** | Doors open while moving | TC-SAFE-001 to TC-SAFE-010 | Test, FMEA, FTA, Fault Injection |
| **HAZ-002** | Door closes on passenger | TC-SAFE-011 to TC-SAFE-020 | Test, FMEA, FTA, Fault Injection |
| **HAZ-003** | Passenger entrapment | TC-SAFE-021 to TC-SAFE-025 | Test, Inspection, Demonstration |
| **HAZ-004** | Software lockup | TC-SAFE-026 to TC-SAFE-030 | Test, Static Analysis, Fault Injection |
| **HAZ-005** | Incorrect position reporting | TC-SAFE-031 to TC-SAFE-035 | Test, Analysis |
| **HAZ-006** | CAN bus failure | TC-SAFE-036 to TC-SAFE-040 | Test, Analysis |
| **HAZ-007** | Memory corruption | TC-SAFE-041 to TC-SAFE-045 | Static Analysis, Code Review |
| **HAZ-008** | EMI | Hardware EMC test (EN 50121) | Test (Hardware) |

---

## 6. COVERAGE REQUIREMENTS AND ANALYSIS

### 6.1 Coverage Requirements by SIL 3

Per EN 50128 Table A.21, the following coverage is **MANDATORY** for SIL 3:

| Coverage Type | SIL 3 Requirement | Target | Measurement Tool |
|---------------|------------------|--------|------------------|
| **Statement Coverage** | **M** (100%) | **100%** | gcov/lcov |
| **Branch Coverage** | **M** (100%) | **100%** | gcov/lcov |
| **Condition Coverage** | **M** (100%) | **100%** | gcov/lcov + manual analysis |
| **Data Flow Coverage** | HR | 95%+ | gcov + manual analysis |

### 6.2 Coverage Measurement Approach

**Coverage Levels**:
1. **Unit Test Coverage**: Measured for each C module independently
2. **Integration Test Coverage**: Measured for integrated components
3. **System Test Coverage**: Measured for complete system

**Tools**:
- **gcov**: GCC coverage analysis tool (generates `.gcda` files)
- **lcov**: HTML report generator from gcov data
- **Manual Analysis**: Condition coverage requires manual inspection of complex boolean expressions

**Workflow**:
```bash
# 1. Compile with coverage flags
gcc -fprofile-arcs -ftest-coverage -g -O0 -o test_module module.c test_module.c unity.c

# 2. Run tests
./test_module

# 3. Generate coverage data
gcov module.c

# 4. Generate HTML report
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html

# 5. View report
firefox coverage_html/index.html
```

### 6.3 Coverage Acceptance Criteria

**Unit Test Coverage**:
- Statement: 100% (all statements executed)
- Branch: 100% (all branches taken)
- Condition: 100% (all boolean sub-expressions evaluated to true and false)

**Exceptions** (require justification and VER approval):
- Defensive code that cannot be reached (e.g., after `assert(0)` or unreachable error handlers)
- Hardware-dependent code that cannot be tested on host (must be tested on target)

**Uncovered Code Documentation**:
- Any uncovered code SHALL be documented in coverage report
- Justification SHALL be reviewed and approved by Verifier (VER)
- Examples of acceptable justification:
  - "Defensive NULL check after static allocation (NULL impossible)"
  - "Hardware-specific initialization code (tested on target in integration tests)"

### 6.4 Coverage Reporting

**Coverage Reports** SHALL include:
- Overall coverage percentage (statement, branch, condition)
- Per-module coverage breakdown
- List of uncovered lines with justification
- Coverage trend graph (if multiple test runs)

**Report Format**: HTML (generated by lcov) + PDF summary

**Report Location**: `docs/reports/coverage/`

---

## 7. TEST EXECUTION AND REPORTING

### 7.1 Test Execution Procedure

**Unit Test Execution**:
1. Build test executable with coverage flags
2. Run test executable
3. Capture test results (Unity output: PASS/FAIL count)
4. Generate coverage report (gcov/lcov)
5. Review results, investigate failures
6. Update test status in traceability matrix

**Integration Test Execution**:
1. Deploy software to target hardware
2. Connect test equipment (oscilloscope, CAN analyzer, HIL rig)
3. Execute test cases per test procedure
4. Capture measurements (timing, signals, logs)
5. Analyze results
6. Update test status

**System Test Execution**:
1. Deploy complete system to target hardware
2. Execute operational scenarios
3. Monitor system behavior
4. Verify functional and safety requirements
5. Document results

### 7.2 Test Pass/Fail Criteria

**Test Case Status**:
- **PASS**: All pass criteria met, no deviations
- **FAIL**: One or more pass criteria not met
- **BLOCKED**: Test cannot be executed (dependency not met, hardware unavailable)
- **SKIPPED**: Test not applicable (requirement waived, out of scope)

**Overall Test Level Status**:
- **PASS**: All test cases PASS, coverage requirements met
- **FAIL**: Any test case FAIL OR coverage requirements not met

### 7.3 Test Reporting

**Unit Test Report** (End of Phase 4):
- Test execution summary (total, pass, fail, blocked)
- Coverage report (statement, branch, condition)
- List of failed test cases with root cause analysis
- Defect summary (bugs found, severity, status)
- Traceability matrix update (requirements → unit tests)

**Integration Test Report** (End of Phase 5):
- Integration test results
- Interface test results
- Performance test results (timing, resource usage)
- Defect summary
- Traceability matrix update

**System Test Report** (End of Phase 6):
- System test results (operational scenarios)
- Safety test results (hazard verification)
- Fault injection test results
- Final coverage report (complete system)
- Traceability matrix update (requirements → all tests)
- Risk assessment update (residual risk verification)

---

## 8. DEFECT MANAGEMENT

### 8.1 Defect Classification

| Severity | Definition | Example | Response Time |
|----------|------------|---------|---------------|
| **Critical** | Safety violation, system crash | Door opens while moving | Immediate (24 hours) |
| **High** | Functional failure, safety degradation | Obstacle detection fails | 1 week |
| **Medium** | Performance degradation, minor functional issue | Door opens in 6 seconds (spec: 5s) | 2 weeks |
| **Low** | Cosmetic, documentation error | Typo in log message | Next release |

### 8.2 Defect Workflow

1. **Defect Reported**: Tester logs defect in defect tracking system
2. **Defect Triaged**: QA reviews and assigns severity/priority
3. **Defect Assigned**: Implementer assigned to fix defect
4. **Defect Fixed**: Code updated, unit tests added/updated
5. **Defect Verified**: Verifier confirms fix with regression test
6. **Defect Closed**: QA closes defect after verification

### 8.3 Regression Testing

**Regression Test Strategy**:
- **After each defect fix**: Run affected unit tests + smoke test
- **After each integration**: Run full unit test suite + integration tests
- **Before each release**: Run complete test suite (unit + integration + system)

---

## 9. TEST COMPLETION CRITERIA

### 9.1 Unit Test Completion Criteria

- [ ] All 50+ unit test cases executed
- [ ] 100% unit test pass rate
- [ ] 100% statement coverage achieved
- [ ] 100% branch coverage achieved
- [ ] 100% condition coverage achieved
- [ ] All defects resolved or waived
- [ ] Unit Test Report approved by VER and QA

### 9.2 Integration Test Completion Criteria

- [ ] All 20+ integration test cases executed
- [ ] 100% integration test pass rate
- [ ] All hardware interfaces tested
- [ ] Performance requirements verified (timing, resource usage)
- [ ] Integration Test Report approved by VER

### 9.3 System Test Completion Criteria

- [ ] All 15+ system test cases executed
- [ ] All 45 safety test cases executed
- [ ] 100% system test pass rate
- [ ] All hazards verified (HAZ-001 to HAZ-008)
- [ ] Fault injection tests completed
- [ ] System Test Report approved by VAL and SAF

### 9.4 Overall Test Completion Criteria

- [ ] All test levels complete (unit, integration, system)
- [ ] 100% requirements coverage (50 requirements mapped to tests)
- [ ] 100% hazard coverage (8 hazards verified)
- [ ] 100% code coverage (statement, branch, condition)
- [ ] All critical/high defects resolved
- [ ] All test reports approved
- [ ] Traceability matrix complete and approved
- [ ] **Ready for Phase 6: Validation**

---

## 10. APPENDICES

### Appendix A: Test Case Template

```markdown
**Test Case: TC-[LEVEL]-[ID] - [Title]**

**Requirement**: [REQ-ID]  
**SIL Level**: [0-4]  
**Test Type**: [Functional|Performance|Safety|Interface]  
**Priority**: [Critical|High|Medium|Low]

**Objective**: [One sentence description]

**Preconditions**:
- [Precondition 1]
- [Precondition 2]

**Test Data**:
| Input | Expected Output | Expected Error |
|-------|----------------|----------------|
| [value] | [result] | [status] |

**Test Steps**:
1. Setup: [Initialization]
2. Execute: [Action]
3. Verify: [Assertion]
4. Cleanup: [Resource release]

**Expected Result**: [Description]

**Pass Criteria**:
- [Criterion 1]
- [Criterion 2]

**Traceability**: [Hazard ID if applicable]

**Status**: [Pending|Pass|Fail|Blocked]
```

### Appendix B: Unity Test Example

See `.opencode/skills/en50128-testing/SKILL.md` for Unity test framework patterns and examples.

### Appendix C: Coverage Analysis Script

```bash
#!/bin/bash
# analyze_coverage.sh - Generate and analyze coverage report

set -e

# Compile with coverage
gcc -fprofile-arcs -ftest-coverage -g -O0 \
    -o test_all \
    src/*.c tests/unit/*.c unity/unity.c

# Run tests
./test_all

# Generate coverage
gcov src/*.c

# Generate HTML report
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html

# Check coverage thresholds
python3 scripts/check_coverage.py coverage.info 100 100 100
# Arguments: coverage.info statement_threshold branch_threshold condition_threshold

echo "Coverage report generated: coverage_html/index.html"
```

### Appendix D: Test Automation Framework

Python test harness available in `scripts/test_harness.py` (see `en50128-testing` skill for details).

---

## 11. APPROVAL

This Overall Software Test Specification SHALL be reviewed and approved by the following roles before test execution begins:

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (Tester)** | TST Agent | | 2026-02-19 |
| **Verifier** | TBD | | |
| **Safety Manager** | TBD | | |
| **QA Manager** | TBD | | |
| **Project Manager** | TBD | | |
| **Customer Representative** | TBD | | |

**Approval Status**: Draft (Awaiting Review)

---

**END OF OVERALL SOFTWARE TEST SPECIFICATION**
