# Software Integration Test Specification
## Train Door Control System

---

### Document Control

| Field | Details |
|-------|---------|
| **Document ID** | DOC-INTTEST-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-02-21 |
| **Status** | Draft |
| **Classification** | Internal |
| **SIL Level** | SIL 3 |
| **Project** | Train Door Control System |
| **Organization** | Railway Safety Systems Inc. |

---

### Approval

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (Integrator)** | [Integrator Name] | | |
| **Reviewer (Verifier)** | [Verifier Name] | | |
| **Approver (SW Manager)** | [SW Manager Name] | | |

---

### Document History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-02-21 | Integrator | Initial version - Integration test specification |

---

### Referenced Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-SWRS-2026-001 | Software Requirements Specification | 1.0 |
| DOC-SAS-2026-001 | Software Architecture Specification | 1.0 |
| DOC-SDS-2026-001 | Software Design Specification | 1.0 |
| DOC-SIS-2026-001 | Software Interface Specifications | 1.0 |
| DOC-HAZ-2026-001 | Hazard Log | 1.0 |
| EN 50128:2011 | Railway Applications - Software for Railway Control and Protection Systems | 2011 |

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [Integration Strategy](#2-integration-strategy)
3. [Integration Test Environment](#3-integration-test-environment)
4. [Integration Test Cases](#4-integration-test-cases)
5. [Performance Test Cases](#5-performance-test-cases)
6. [Safety-Critical Integration Tests](#6-safety-critical-integration-tests)
7. [Test Traceability Matrix](#7-test-traceability-matrix)
8. [Test Execution Schedule](#8-test-execution-schedule)
9. [Test Completion Criteria](#9-test-completion-criteria)
10. [EN 50128 Compliance](#10-en-50128-compliance)

---

## 1. Introduction

### 1.1 Purpose

This document specifies the integration testing for the Train Door Control System software. It defines the integration strategy, test cases, and procedures to verify correct interaction between software modules in accordance with EN 50128:2011 Section 7.6.

### 1.2 Scope

This specification covers:
- Integration of 8 software modules (MOD-001 through MOD-008)
- Testing of 47 interface functions
- Verification of inter-module communication
- Validation of timing and performance requirements
- Verification of safety-critical interactions
- End-to-end functional testing

### 1.3 System Overview

The Train Door Control System consists of 8 modules organized in 3 layers:

**Application Layer:**
- MOD-001: Door FSM (Finite State Machine)
- MOD-002: Safety Monitor
- MOD-003: Fault Detection and Diagnosis
- MOD-004: Command Processor
- MOD-005: Status Reporter

**Hardware Abstraction Layer (HAL):**
- MOD-006: Actuator HAL
- MOD-007: Sensor HAL
- MOD-008: Communication HAL

### 1.4 EN 50128 Requirements

**SIL 3 Integration Testing Requirements:**
- **Functional and Black-box Testing**: Highly Recommended (Table A.6)
- **Performance Testing**: Highly Recommended (Table A.6)
- **Interface Testing**: Highly Recommended (Table A.6)
- **Boundary Value Analysis**: Mandatory (SIL 3)
- **Error Propagation Testing**: Highly Recommended (SIL 3)

---

## 2. Integration Strategy

### 2.1 Integration Approach

**Selected Strategy**: **Bottom-Up Integration**

**Rationale**:
1. Hardware abstraction layer (HAL) modules (MOD-006, MOD-007, MOD-008) are foundational
2. Application modules depend on stable HAL interfaces
3. Critical safety functions (speed monitoring, obstacle detection) require verified HAL
4. Allows early hardware integration testing
5. Minimizes use of stubs (only top-level stubs needed)

### 2.2 Integration Sequence

**Phase 1: HAL Layer Integration**
- **Build 1**: MOD-006 (Actuator HAL) standalone
- **Build 2**: MOD-007 (Sensor HAL) standalone
- **Build 3**: MOD-008 (Communication HAL) standalone
- **Build 4**: MOD-006 + MOD-007 + MOD-008 (Complete HAL)

**Phase 2: Control Logic Integration**
- **Build 5**: MOD-001 (Door FSM) + HAL layer
- **Build 6**: MOD-002 (Safety Monitor) + MOD-001 + HAL layer
- **Build 7**: MOD-003 (Fault Detection) + MOD-001 + MOD-002 + HAL layer

**Phase 3: Application Layer Integration**
- **Build 8**: MOD-004 (Command Processor) + Control Logic + HAL
- **Build 9**: MOD-005 (Status Reporter) + MOD-004 + Control Logic + HAL

**Phase 4: System Integration**
- **Build 10**: Complete system (all 8 modules)

### 2.3 Stubs and Drivers

**Drivers Required** (Bottom-Up Approach):
- **Driver-APP**: Application-level test driver for invoking HAL functions
- **Driver-CMD**: Command generator for testing command processing
- **Driver-CAN**: CAN message generator for testing communication interfaces

**Stubs Required** (Minimal):
- **Stub-HW**: Hardware register stubs for HAL testing (if hardware unavailable)
- **Stub-TIME**: System timer stub for deterministic timing tests

### 2.4 Integration Environment

- **Toolchain**: GCC ARM Embedded (arm-none-eabi-gcc)
- **Target**: STM32F4 microcontroller (or simulation)
- **Debugger**: GDB + OpenOCD
- **Test Framework**: Unity (C unit test framework)
- **Coverage Tool**: gcov/lcov
- **Static Analyzer**: PC-lint Plus, Cppcheck

---

## 3. Integration Test Environment

### 3.1 Hardware Setup

**Option A: Target Hardware**
- STM32F4 Development Board
- Door actuator simulator (PWM-controlled motor)
- Sensor interface board (position, obstacle, speed sensors)
- CAN transceiver module
- Power supply (24V for actuators, 5V/3.3V for logic)

**Option B: Hardware-in-Loop (HIL) Simulator**
- Real-time simulation of sensors and actuators
- CAN bus simulation
- Timing-accurate execution

### 3.2 Software Setup

- **Build System**: CMake + Make
- **Test Harness**: Unity test framework with integration test extensions
- **Logging**: UART serial logging (115200 baud)
- **Debug Interface**: SWD (Serial Wire Debug)

### 3.3 Test Data Collection

- **Timing Measurements**: DWT (Data Watchpoint and Trace) cycle counter
- **Coverage Data**: gcov instrumentation
- **CAN Traffic**: CAN bus analyzer logs
- **Execution Traces**: Real-time execution logs via UART

---

## 4. Integration Test Cases

### 4.1 Test Case Naming Convention

**Format**: `TC-INT-<PHASE>-<NUMBER>`
- **PHASE**: 1-4 (integration phase)
- **NUMBER**: Sequential 3-digit number

**Example**: TC-INT-1-001 (Phase 1, Test Case 1)

---

### 4.2 Phase 1: HAL Layer Integration Tests

---

#### TC-INT-1-001: Actuator HAL Initialization

**Objective**: Verify MOD-006 initializes actuator hardware correctly.

**Modules Under Test**: MOD-006 (Actuator HAL)

**Requirements Traced**: SWR-IF-001, SWR-IF-002

**Preconditions**:
- Target hardware powered on
- Actuator connected to PWM outputs

**Test Steps**:
1. Call `ActuatorHAL_Init()`
2. Verify return value is `HAL_SUCCESS`
3. Check PWM timer registers configured (frequency = 10 kHz)
4. Verify initial motor state is MOTOR_STOP
5. Verify initial lock state is LOCK_ENGAGED

**Expected Results**:
- `ActuatorHAL_Init()` returns `HAL_SUCCESS`
- PWM timer registers: TIMx_ARR = 8400 (for 84 MHz clock, 10 kHz PWM)
- Motor PWM duty cycle = 0%
- Lock solenoid output = HIGH (engaged)

**Postconditions**:
- Actuator HAL ready for operation
- Motor stopped, lock engaged

**Pass/Fail Criteria**: All expected results met.

---

#### TC-INT-1-002: Actuator HAL Motor Control

**Objective**: Verify MOD-006 controls motor via PWM correctly.

**Modules Under Test**: MOD-006 (Actuator HAL)

**Requirements Traced**: SWR-IF-003, SWR-IF-004

**Preconditions**:
- MOD-006 initialized (TC-INT-1-001 passed)
- Motor connected and operational

**Test Steps**:
1. Call `ActuatorHAL_SetMotor(MOTOR_OPEN, 50)` (50% duty cycle, opening direction)
2. Measure PWM output duty cycle
3. Verify motor direction output (GPIO state)
4. Call `ActuatorHAL_SetMotor(MOTOR_CLOSE, 75)` (75% duty cycle, closing direction)
5. Measure PWM output duty cycle
6. Verify motor direction output changed
7. Call `ActuatorHAL_SetMotor(MOTOR_STOP, 0)`
8. Verify PWM duty cycle = 0%

**Expected Results**:
- Step 2: PWM duty cycle = 50% ± 2%
- Step 3: Direction GPIO = MOTOR_OPEN state
- Step 5: PWM duty cycle = 75% ± 2%
- Step 6: Direction GPIO = MOTOR_CLOSE state
- Step 8: PWM duty cycle = 0%

**Postconditions**:
- Motor stopped

**Pass/Fail Criteria**: All duty cycle measurements within ± 2% tolerance.

---

#### TC-INT-1-003: Actuator HAL Lock Control

**Objective**: Verify MOD-006 controls door lock solenoid correctly.

**Modules Under Test**: MOD-006 (Actuator HAL)

**Requirements Traced**: SWR-IF-005, SWR-IF-006

**Preconditions**:
- MOD-006 initialized
- Lock solenoid connected

**Test Steps**:
1. Call `ActuatorHAL_SetLock(LOCK_ENGAGED)`
2. Measure lock solenoid GPIO output
3. Wait 100ms (debounce time)
4. Call `ActuatorHAL_SetLock(LOCK_RELEASED)`
5. Measure lock solenoid GPIO output
6. Wait 100ms
7. Verify lock state transitions

**Expected Results**:
- Step 2: Lock GPIO = HIGH (engaged)
- Step 5: Lock GPIO = LOW (released)
- All transitions complete within 10ms

**Postconditions**:
- Lock in released state

**Pass/Fail Criteria**: Lock GPIO states correct, timing < 10ms.

---

#### TC-INT-1-004: Sensor HAL Initialization

**Objective**: Verify MOD-007 initializes sensor interfaces correctly.

**Modules Under Test**: MOD-007 (Sensor HAL)

**Requirements Traced**: SWR-IF-007, SWR-IF-008

**Preconditions**:
- Target hardware powered on
- Sensors connected (position, obstacle, speed)

**Test Steps**:
1. Call `SensorHAL_Init()`
2. Verify return value is `HAL_SUCCESS`
3. Check ADC configuration (12-bit, 84 MHz clock)
4. Check GPIO configuration for digital inputs
5. Verify initial sensor readings are valid (not 0xFFFF error codes)

**Expected Results**:
- `SensorHAL_Init()` returns `HAL_SUCCESS`
- ADC configured: 12-bit resolution, continuous conversion mode
- GPIO inputs configured with pull-up resistors
- Initial sensor readings within valid ranges

**Postconditions**:
- Sensor HAL ready for operation

**Pass/Fail Criteria**: All expected results met.

---

#### TC-INT-1-005: Sensor HAL Position Sensor Reading

**Objective**: Verify MOD-007 reads door position sensor correctly.

**Modules Under Test**: MOD-007 (Sensor HAL)

**Requirements Traced**: SWR-IF-009, SWR-IF-010

**Preconditions**:
- MOD-007 initialized
- Position sensor connected (analog input 0-3.3V)

**Test Steps**:
1. Set sensor voltage to 0.0V (door fully closed)
2. Call `SensorHAL_GetPosition()`
3. Verify reading = 0 ± 2 (0% open)
4. Set sensor voltage to 1.65V (door 50% open)
5. Call `SensorHAL_GetPosition()`
6. Verify reading = 50 ± 2 (50% open)
7. Set sensor voltage to 3.3V (door fully open)
8. Call `SensorHAL_GetPosition()`
9. Verify reading = 100 ± 2 (100% open)

**Expected Results**:
- Step 3: position = 0 ± 2%
- Step 6: position = 50 ± 2%
- Step 9: position = 100 ± 2%
- All readings return `HAL_SUCCESS`

**Postconditions**:
- Sensor readings stable

**Pass/Fail Criteria**: All position readings within ± 2% tolerance.

---

#### TC-INT-1-006: Sensor HAL Obstacle Detection

**Objective**: Verify MOD-007 detects obstacles via infrared sensor.

**Modules Under Test**: MOD-007 (Sensor HAL)

**Requirements Traced**: SWR-IF-011, SWR-SAF-002 (obstacle detection)

**Preconditions**:
- MOD-007 initialized
- Obstacle sensor connected (digital input, active LOW)

**Test Steps**:
1. Set obstacle sensor input to HIGH (no obstacle)
2. Call `SensorHAL_GetObstacle()`
3. Verify return value = `OBSTACLE_CLEAR`
4. Set obstacle sensor input to LOW (obstacle detected)
5. Call `SensorHAL_GetObstacle()`
6. Verify return value = `OBSTACLE_DETECTED`
7. Measure detection latency (input change to reading change)

**Expected Results**:
- Step 3: `OBSTACLE_CLEAR` returned
- Step 6: `OBSTACLE_DETECTED` returned
- Step 7: Detection latency ≤ 10ms

**Postconditions**:
- Obstacle sensor operational

**Pass/Fail Criteria**: Correct detection states, latency ≤ 10ms.

---

#### TC-INT-1-007: Sensor HAL Speed Sensor Reading

**Objective**: Verify MOD-007 reads train speed from wheel pulse sensor.

**Modules Under Test**: MOD-007 (Sensor HAL)

**Requirements Traced**: SWR-IF-012, SWR-SAF-001 (speed monitoring)

**Preconditions**:
- MOD-007 initialized
- Speed sensor connected (pulse input, 4 pulses/revolution)

**Test Steps**:
1. Generate 0 pulses (train stopped)
2. Call `SensorHAL_GetSpeed()` after 1 second
3. Verify speed = 0 km/h
4. Generate pulses at 10 Hz (simulating 5 km/h)
5. Call `SensorHAL_GetSpeed()` after 1 second
6. Verify speed = 5 ± 0.5 km/h
7. Generate pulses at 40 Hz (simulating 20 km/h)
8. Call `SensorHAL_GetSpeed()` after 1 second
9. Verify speed = 20 ± 1 km/h

**Expected Results**:
- Step 3: speed = 0 km/h
- Step 6: speed = 5 ± 0.5 km/h
- Step 9: speed = 20 ± 1 km/h

**Postconditions**:
- Speed sensor operational

**Pass/Fail Criteria**: Speed readings within tolerance.

---

#### TC-INT-1-008: Communication HAL Initialization

**Objective**: Verify MOD-008 initializes CAN bus interface correctly.

**Modules Under Test**: MOD-008 (Communication HAL)

**Requirements Traced**: SWR-IF-013, SWR-IF-014

**Preconditions**:
- Target hardware powered on
- CAN transceiver connected

**Test Steps**:
1. Call `CommHAL_Init()`
2. Verify return value is `HAL_SUCCESS`
3. Check CAN controller registers (500 kbps bit rate)
4. Verify CAN filters configured
5. Verify TX/RX interrupts enabled

**Expected Results**:
- `CommHAL_Init()` returns `HAL_SUCCESS`
- CAN bit rate = 500 kbps
- CAN filters: Accept IDs 0x100-0x1FF
- TX/RX interrupts enabled

**Postconditions**:
- CAN bus ready for communication

**Pass/Fail Criteria**: All expected results met.

---

#### TC-INT-1-009: Communication HAL CAN Transmit

**Objective**: Verify MOD-008 transmits CAN messages correctly.

**Modules Under Test**: MOD-008 (Communication HAL)

**Requirements Traced**: SWR-IF-015, SWR-IF-016

**Preconditions**:
- MOD-008 initialized
- CAN analyzer connected to bus

**Test Steps**:
1. Prepare CAN message (ID=0x120, 8 bytes data)
2. Call `CommHAL_SendCAN(0x120, data, 8)`
3. Verify return value is `HAL_SUCCESS`
4. Check CAN analyzer for transmitted message
5. Verify message ID, DLC, and data bytes
6. Measure transmission latency

**Expected Results**:
- `CommHAL_SendCAN()` returns `HAL_SUCCESS`
- CAN analyzer shows message ID=0x120, DLC=8
- Data bytes match transmitted data
- Transmission latency ≤ 5ms

**Postconditions**:
- Message transmitted successfully

**Pass/Fail Criteria**: Message transmitted correctly, latency ≤ 5ms.

---

#### TC-INT-1-010: Communication HAL CAN Receive

**Objective**: Verify MOD-008 receives CAN messages correctly.

**Modules Under Test**: MOD-008 (Communication HAL)

**Requirements Traced**: SWR-IF-017, SWR-IF-018

**Preconditions**:
- MOD-008 initialized
- CAN message generator connected

**Test Steps**:
1. Send CAN message (ID=0x130, 8 bytes data) via external generator
2. Call `CommHAL_ReceiveCAN(&id, data, &len)`
3. Verify return value is `HAL_SUCCESS`
4. Verify received ID = 0x130
5. Verify received DLC = 8
6. Verify received data bytes match transmitted data
7. Measure reception latency

**Expected Results**:
- `CommHAL_ReceiveCAN()` returns `HAL_SUCCESS`
- Received ID = 0x130
- Received DLC = 8
- Data bytes match transmitted data
- Reception latency ≤ 5ms

**Postconditions**:
- Message received successfully

**Pass/Fail Criteria**: Message received correctly, latency ≤ 5ms.

---

#### TC-INT-1-011: HAL Layer Combined Operation

**Objective**: Verify all 3 HAL modules operate together without conflicts.

**Modules Under Test**: MOD-006, MOD-007, MOD-008

**Requirements Traced**: SWR-IF-001 to SWR-IF-018

**Preconditions**:
- All HAL modules initialized
- All hardware interfaces connected

**Test Steps**:
1. Start motor via MOD-006 (50% duty cycle, OPEN direction)
2. Read position sensor via MOD-007 (expect increasing position)
3. Send CAN status message via MOD-008
4. Receive CAN command message via MOD-008
5. Detect obstacle via MOD-007
6. Stop motor via MOD-006
7. Read speed sensor via MOD-007
8. Verify no resource conflicts (timers, interrupts, GPIOs)

**Expected Results**:
- All HAL functions execute successfully
- Motor operates while CAN messages transmitted/received
- Sensor readings stable during motor operation
- No interrupt conflicts or missed events
- Timing jitter ≤ 5ms

**Postconditions**:
- All HAL modules operational

**Pass/Fail Criteria**: All operations successful, no conflicts detected.

---

### 4.3 Phase 2: Control Logic Integration Tests

---

#### TC-INT-2-001: Door FSM + Actuator HAL Integration

**Objective**: Verify MOD-001 controls door motor via MOD-006.

**Modules Under Test**: MOD-001 (Door FSM), MOD-006 (Actuator HAL)

**Requirements Traced**: SWR-FUNC-001, SWR-FUNC-002, SWR-IF-003

**Preconditions**:
- MOD-001 and MOD-006 initialized
- Door in CLOSED state
- Lock engaged

**Test Steps**:
1. Call `DoorFSM_ProcessCommand(CMD_OPEN)`
2. Verify FSM transitions to OPENING state
3. Verify MOD-006 motor set to MOTOR_OPEN direction
4. Verify PWM duty cycle > 0%
5. Wait for door to reach 100% open (simulate position sensor)
6. Verify FSM transitions to OPEN state
7. Verify motor stopped

**Expected Results**:
- FSM state transitions: CLOSED → OPENING → OPEN
- Motor direction = MOTOR_OPEN during opening
- Motor duty cycle = 50-100% during opening
- Motor stops when door fully open
- Transition timing: 0 → 100% in ≤ 5 seconds

**Postconditions**:
- Door in OPEN state, motor stopped

**Pass/Fail Criteria**: Correct state transitions, motor control, timing met.

---

#### TC-INT-2-002: Door FSM + Sensor HAL Position Feedback

**Objective**: Verify MOD-001 reads door position from MOD-007.

**Modules Under Test**: MOD-001 (Door FSM), MOD-007 (Sensor HAL)

**Requirements Traced**: SWR-FUNC-001, SWR-IF-009

**Preconditions**:
- MOD-001 and MOD-007 initialized
- Door in OPENING state

**Test Steps**:
1. Set position sensor to 0% (fully closed)
2. Call `DoorFSM_Update()` (50ms cycle)
3. Verify FSM reads position = 0%
4. Set position sensor to 50% (half open)
5. Call `DoorFSM_Update()`
6. Verify FSM reads position = 50%
7. Set position sensor to 100% (fully open)
8. Call `DoorFSM_Update()`
9. Verify FSM transitions to OPEN state

**Expected Results**:
- FSM correctly reads position at each step
- State transition to OPEN when position ≥ 98%
- Position sampling rate = 20 Hz (50ms period)

**Postconditions**:
- Door in OPEN state

**Pass/Fail Criteria**: Correct position readings, state transition at 98% open.

---

#### TC-INT-2-003: Safety Monitor + Sensor HAL Speed Interlock

**Objective**: Verify MOD-002 monitors train speed from MOD-007 and prevents door operation.

**Modules Under Test**: MOD-002 (Safety Monitor), MOD-007 (Sensor HAL)

**Requirements Traced**: SWR-SAF-001 (speed interlock), HAZ-001 mitigation

**Preconditions**:
- MOD-002 and MOD-007 initialized
- Train speed = 0 km/h
- Door operation permitted

**Test Steps**:
1. Set train speed to 0 km/h
2. Call `SafetyMonitor_CheckSafetyConditions()`
3. Verify return value = `SAFETY_OK`
4. Set train speed to 3 km/h (below threshold)
5. Call `SafetyMonitor_CheckSafetyConditions()`
6. Verify return value = `SAFETY_OK`
7. Set train speed to 6 km/h (above 5 km/h threshold)
8. Call `SafetyMonitor_CheckSafetyConditions()`
9. Verify return value = `SAFETY_SPEED_VIOLATION`
10. Verify door lock commanded to ENGAGED

**Expected Results**:
- Steps 3, 6: `SAFETY_OK` (speed ≤ 5 km/h)
- Step 9: `SAFETY_SPEED_VIOLATION` (speed > 5 km/h)
- Step 10: Lock engaged immediately
- Speed check period = 50ms

**Postconditions**:
- Door locked when speed > 5 km/h

**Pass/Fail Criteria**: Correct safety interlock behavior, lock engaged when speed violation detected.

---

#### TC-INT-2-004: Safety Monitor + Communication HAL Speed Data

**Objective**: Verify MOD-002 receives train speed via CAN from MOD-008.

**Modules Under Test**: MOD-002 (Safety Monitor), MOD-008 (Communication HAL)

**Requirements Traced**: SWR-SAF-001, SWR-IF-017

**Preconditions**:
- MOD-002 and MOD-008 initialized
- CAN bus operational

**Test Steps**:
1. Send CAN message ID=0x150 with speed data = 0 km/h
2. Call `SafetyMonitor_Update()`
3. Verify speed value read from MOD-008 = 0 km/h
4. Send CAN message ID=0x150 with speed data = 10 km/h
5. Call `SafetyMonitor_Update()`
6. Verify speed value = 10 km/h
7. Verify safety interlock activates (speed > 5 km/h)

**Expected Results**:
- Speed values correctly received from CAN
- Safety interlock activates when speed > 5 km/h
- CAN message reception latency ≤ 10ms

**Postconditions**:
- Safety interlock active (speed > 5 km/h)

**Pass/Fail Criteria**: Correct CAN speed reception, safety interlock activated.

---

#### TC-INT-2-005: Door FSM + Safety Monitor Interlock

**Objective**: Verify MOD-001 respects safety interlock from MOD-002.

**Modules Under Test**: MOD-001 (Door FSM), MOD-002 (Safety Monitor)

**Requirements Traced**: SWR-SAF-001, SWR-FUNC-001

**Preconditions**:
- MOD-001 and MOD-002 initialized
- Door in CLOSED state
- Train speed = 0 km/h

**Test Steps**:
1. Set train speed to 0 km/h
2. Call `DoorFSM_ProcessCommand(CMD_OPEN)`
3. Verify FSM transitions to OPENING state (safety OK)
4. Set train speed to 10 km/h (during opening)
5. Call `DoorFSM_Update()`
6. Verify FSM immediately transitions to EMERGENCY_CLOSE state
7. Verify motor direction = MOTOR_CLOSE
8. Verify lock commanded to ENGAGED

**Expected Results**:
- Step 3: Door opens when speed = 0 km/h
- Step 6: FSM transitions to EMERGENCY_CLOSE when speed > 5 km/h
- Step 7: Motor reverses direction immediately
- Step 8: Lock engaged when door reaches CLOSED state
- Emergency close reaction time ≤ 100ms

**Postconditions**:
- Door closed and locked due to speed violation

**Pass/Fail Criteria**: Safety interlock enforced, emergency close completed, reaction time ≤ 100ms.

---

#### TC-INT-2-006: Door FSM + Sensor HAL Obstacle Detection

**Objective**: Verify MOD-001 detects obstacles via MOD-007 and reverses door motion.

**Modules Under Test**: MOD-001 (Door FSM), MOD-007 (Sensor HAL)

**Requirements Traced**: SWR-SAF-002 (obstacle detection), HAZ-002 mitigation

**Preconditions**:
- MOD-001 and MOD-007 initialized
- Door in CLOSING state
- Obstacle sensor clear

**Test Steps**:
1. Start door closing (position = 80%, closing direction)
2. Call `DoorFSM_Update()`
3. Verify motor direction = MOTOR_CLOSE
4. Set obstacle sensor to DETECTED (simulate obstacle)
5. Call `DoorFSM_Update()`
6. Verify FSM transitions to OBSTACLE_DETECTED state
7. Verify motor direction changes to MOTOR_OPEN (reverses)
8. Measure reaction time (obstacle detection to motor reversal)

**Expected Results**:
- Step 6: FSM transitions to OBSTACLE_DETECTED state
- Step 7: Motor reverses direction immediately
- Step 8: Reaction time ≤ 100ms
- Door reopens to OPEN state

**Postconditions**:
- Door reopened due to obstacle

**Pass/Fail Criteria**: Obstacle detected, motor reversed, reaction time ≤ 100ms.

---

#### TC-INT-2-007: Fault Detection + Door FSM Integration

**Objective**: Verify MOD-003 detects faults in MOD-001 operation.

**Modules Under Test**: MOD-003 (Fault Detection), MOD-001 (Door FSM)

**Requirements Traced**: SWR-SAF-004 (fault detection), SWR-FUNC-007

**Preconditions**:
- MOD-003 and MOD-001 initialized
- Door in OPENING state
- Position = 20%

**Test Steps**:
1. Start door opening (motor running)
2. Wait 6 seconds (exceeds 5-second timeout)
3. Verify position has not changed (stuck door fault)
4. Call `FaultDetection_Update()`
5. Verify fault code = `FAULT_DOOR_TIMEOUT`
6. Verify MOD-001 transitions to FAULT state
7. Verify motor stopped
8. Verify fault logged

**Expected Results**:
- Step 5: Timeout fault detected (door not moving for > 5 seconds)
- Step 6: FSM enters FAULT state
- Step 7: Motor stops immediately
- Fault detection time = 5.0 ± 0.1 seconds

**Postconditions**:
- Door in FAULT state, motor stopped

**Pass/Fail Criteria**: Timeout fault detected, FSM transitions to FAULT state.

---

#### TC-INT-2-008: Fault Detection + Sensor HAL Integration

**Objective**: Verify MOD-003 detects sensor faults from MOD-007.

**Modules Under Test**: MOD-003 (Fault Detection), MOD-007 (Sensor HAL)

**Requirements Traced**: SWR-SAF-004, SWR-IF-010

**Preconditions**:
- MOD-003 and MOD-007 initialized
- All sensors operational

**Test Steps**:
1. Disconnect position sensor (simulate sensor failure)
2. Call `SensorHAL_GetPosition()`
3. Verify return value = `HAL_ERROR_SENSOR_FAULT`
4. Call `FaultDetection_Update()`
5. Verify fault code = `FAULT_SENSOR_POSITION`
6. Verify fault logged
7. Verify system enters safe state (door locked, motor stopped)

**Expected Results**:
- Step 3: Sensor fault detected by HAL
- Step 5: Fault propagated to MOD-003
- Step 7: Safe state entered (fail-safe behavior)
- Fault detection time ≤ 100ms

**Postconditions**:
- System in safe state due to sensor fault

**Pass/Fail Criteria**: Sensor fault detected, safe state entered.

---

#### TC-INT-2-009: Safety Monitor Watchdog Integration

**Objective**: Verify MOD-002 implements watchdog monitoring of MOD-001.

**Modules Under Test**: MOD-002 (Safety Monitor), MOD-001 (Door FSM)

**Requirements Traced**: SWR-SAF-003 (watchdog), HAZ-004 mitigation

**Preconditions**:
- MOD-002 and MOD-001 initialized
- Watchdog enabled (100ms timeout)

**Test Steps**:
1. Call `DoorFSM_Update()` at 50ms intervals (normal operation)
2. Verify `SafetyMonitor_Update()` receives watchdog refresh
3. Verify no watchdog timeout
4. Stop calling `DoorFSM_Update()` (simulate software hang)
5. Wait 110ms
6. Call `SafetyMonitor_Update()`
7. Verify watchdog timeout detected
8. Verify system enters safe state (door locked, motor stopped)

**Expected Results**:
- Steps 2-3: Watchdog refreshed every 50ms, no timeout
- Step 7: Watchdog timeout detected after 100ms
- Step 8: Safe state entered immediately
- Watchdog timeout tolerance: 100 ± 10ms

**Postconditions**:
- System in safe state due to watchdog timeout

**Pass/Fail Criteria**: Watchdog timeout detected, safe state entered.

---

### 4.4 Phase 3: Application Layer Integration Tests

---

#### TC-INT-3-001: Command Processor + Door FSM Integration

**Objective**: Verify MOD-004 processes CAN commands and controls MOD-001.

**Modules Under Test**: MOD-004 (Command Processor), MOD-001 (Door FSM)

**Requirements Traced**: SWR-FUNC-003, SWR-IF-019

**Preconditions**:
- MOD-004 and MOD-001 initialized
- Door in CLOSED state

**Test Steps**:
1. Send CAN message ID=0x120 with command = OPEN
2. Call `CommandProcessor_Update()`
3. Verify MOD-004 decodes command
4. Verify MOD-004 calls `DoorFSM_ProcessCommand(CMD_OPEN)`
5. Verify door begins opening
6. Send CAN message ID=0x120 with command = CLOSE
7. Call `CommandProcessor_Update()`
8. Verify door begins closing

**Expected Results**:
- Commands decoded correctly from CAN messages
- Commands forwarded to MOD-001
- Door responds to commands
- Command processing latency ≤ 20ms

**Postconditions**:
- Door responds to CAN commands

**Pass/Fail Criteria**: Commands processed correctly, latency ≤ 20ms.

---

#### TC-INT-3-002: Command Processor + Communication HAL Integration

**Objective**: Verify MOD-004 receives CAN commands via MOD-008.

**Modules Under Test**: MOD-004 (Command Processor), MOD-008 (Communication HAL)

**Requirements Traced**: SWR-IF-019, SWR-IF-017

**Preconditions**:
- MOD-004 and MOD-008 initialized
- CAN bus operational

**Test Steps**:
1. Send CAN message ID=0x120, data[0]=0x01 (OPEN command)
2. Call `CommandProcessor_Update()`
3. Verify MOD-004 reads message via `CommHAL_ReceiveCAN()`
4. Verify command decoded = CMD_OPEN
5. Send CAN message ID=0x120, data[0]=0x02 (CLOSE command)
6. Call `CommandProcessor_Update()`
7. Verify command decoded = CMD_CLOSE
8. Send invalid CAN message ID=0x999 (unknown ID)
9. Verify command rejected (not processed)

**Expected Results**:
- Valid commands (ID=0x120) processed
- Invalid messages (ID≠0x120) ignored
- Command reception latency ≤ 10ms

**Postconditions**:
- Command processor operational

**Pass/Fail Criteria**: Valid commands processed, invalid commands rejected.

---

#### TC-INT-3-003: Status Reporter + Door FSM Integration

**Objective**: Verify MOD-005 reads door status from MOD-001.

**Modules Under Test**: MOD-005 (Status Reporter), MOD-001 (Door FSM)

**Requirements Traced**: SWR-FUNC-004, SWR-IF-020

**Preconditions**:
- MOD-005 and MOD-001 initialized
- Door in CLOSED state

**Test Steps**:
1. Call `StatusReporter_Update()`
2. Verify status includes: state=CLOSED, position=0%, lock=ENGAGED
3. Transition door to OPENING state
4. Call `StatusReporter_Update()`
5. Verify status includes: state=OPENING, position=50%, lock=RELEASED
6. Transition door to OPEN state
7. Call `StatusReporter_Update()`
8. Verify status includes: state=OPEN, position=100%, lock=RELEASED

**Expected Results**:
- Status accurately reflects door state at each step
- Position value matches position sensor reading
- Lock state matches lock output
- Status update period = 50ms

**Postconditions**:
- Status reporter operational

**Pass/Fail Criteria**: Status values correct for all door states.

---

#### TC-INT-3-004: Status Reporter + Fault Detection Integration

**Objective**: Verify MOD-005 reports faults from MOD-003.

**Modules Under Test**: MOD-005 (Status Reporter), MOD-003 (Fault Detection)

**Requirements Traced**: SWR-FUNC-007, SWR-IF-021

**Preconditions**:
- MOD-005 and MOD-003 initialized
- No faults active

**Test Steps**:
1. Call `StatusReporter_Update()`
2. Verify status.fault_code = `FAULT_NONE`
3. Inject door timeout fault in MOD-003
4. Call `StatusReporter_Update()`
5. Verify status.fault_code = `FAULT_DOOR_TIMEOUT`
6. Verify fault timestamp included
7. Clear fault
8. Call `StatusReporter_Update()`
9. Verify status.fault_code = `FAULT_NONE`

**Expected Results**:
- Fault status correctly reported
- Fault code matches MOD-003 fault
- Fault timestamp accurate (±10ms)
- Fault cleared when MOD-003 clears

**Postconditions**:
- Fault reporting operational

**Pass/Fail Criteria**: Fault status correctly reported and cleared.

---

#### TC-INT-3-005: Status Reporter + Communication HAL Integration

**Objective**: Verify MOD-005 transmits status via CAN through MOD-008.

**Modules Under Test**: MOD-005 (Status Reporter), MOD-008 (Communication HAL)

**Requirements Traced**: SWR-FUNC-004, SWR-IF-015

**Preconditions**:
- MOD-005 and MOD-008 initialized
- CAN bus operational

**Test Steps**:
1. Call `StatusReporter_Update()`
2. Verify MOD-005 calls `CommHAL_SendCAN(0x130, status_data, 8)`
3. Verify CAN message transmitted (ID=0x130)
4. Decode CAN message data bytes
5. Verify data[0] = door state
6. Verify data[1] = door position
7. Verify data[2] = lock state
8. Verify data[3-4] = fault code
9. Measure transmission period

**Expected Results**:
- CAN message ID=0x130 transmitted
- Data bytes correctly encoded (per protocol)
- Transmission period = 50ms ± 5ms
- Transmission latency ≤ 10ms

**Postconditions**:
- Status transmitted via CAN

**Pass/Fail Criteria**: Status CAN messages transmitted correctly with 50ms period.

---

#### TC-INT-3-006: End-to-End Command-to-Status Flow

**Objective**: Verify complete command processing from CAN input to status output.

**Modules Under Test**: MOD-004, MOD-001, MOD-006, MOD-007, MOD-005, MOD-008

**Requirements Traced**: SWR-FUNC-001, SWR-FUNC-003, SWR-FUNC-004

**Preconditions**:
- All modules initialized
- Door in CLOSED state

**Test Steps**:
1. Send CAN command ID=0x120, data=OPEN
2. Call system update (all modules) at 50ms intervals
3. Monitor status CAN messages (ID=0x130)
4. Verify status shows: CLOSED → OPENING → OPEN
5. Verify position increases from 0% → 100%
6. Measure total time from command to fully open
7. Send CAN command ID=0x120, data=CLOSE
8. Monitor status messages
9. Verify status shows: OPEN → CLOSING → CLOSED
10. Measure total time from command to fully closed

**Expected Results**:
- Complete command-to-status chain functional
- Door opens in ≤ 5 seconds
- Door closes in ≤ 7 seconds
- Status messages transmitted every 50ms during operation
- Position values increase/decrease smoothly

**Postconditions**:
- Complete system operational

**Pass/Fail Criteria**: End-to-end flow functional, timing requirements met.

---

### 4.5 Phase 4: System Integration Tests

---

#### TC-INT-4-001: Complete System Functional Test

**Objective**: Verify all 8 modules operate together in complete system configuration.

**Modules Under Test**: All modules (MOD-001 through MOD-008)

**Requirements Traced**: All SWR requirements

**Preconditions**:
- All modules initialized
- All hardware connected
- CAN bus operational

**Test Steps**:
1. Power on system
2. Verify all modules initialize successfully
3. Send door OPEN command via CAN
4. Verify door opens (5 seconds max)
5. Verify status messages transmitted
6. Send door CLOSE command
7. Verify door closes (7 seconds max)
8. Verify lock engages when closed
9. Inject obstacle during closing
10. Verify door reverses
11. Set train speed > 5 km/h
12. Verify door locks
13. Inject sensor fault
14. Verify system enters safe state
15. Clear fault and reset
16. Verify system recovers

**Expected Results**:
- All operations execute correctly
- All timing requirements met
- All safety interlocks functional
- All fault detection operational
- No resource conflicts or deadlocks

**Postconditions**:
- System fully operational

**Pass/Fail Criteria**: All functional requirements verified, all safety requirements met.

---

#### TC-INT-4-002: System Stress Test

**Objective**: Verify system operates correctly under high load conditions.

**Modules Under Test**: All modules

**Requirements Traced**: SWR-PERF-001, SWR-PERF-002

**Preconditions**:
- All modules initialized
- System operational

**Test Steps**:
1. Send rapid command sequence (OPEN, CLOSE, OPEN, ...) at 100ms intervals
2. Monitor CPU load
3. Monitor CAN bus load
4. Monitor timing jitter
5. Verify all commands processed
6. Inject multiple simultaneous events (obstacle + speed change + fault)
7. Verify system handles all events correctly
8. Verify no events lost or missed
9. Run for 1 hour continuous operation
10. Verify no performance degradation

**Expected Results**:
- CPU load ≤ 80%
- CAN bus load ≤ 60%
- Timing jitter ≤ 10ms
- All events processed correctly
- No memory leaks or resource exhaustion
- No performance degradation over time

**Postconditions**:
- System stable under load

**Pass/Fail Criteria**: System operates correctly under stress, performance requirements met.

---

#### TC-INT-4-003: System Recovery Test

**Objective**: Verify system recovers from faults and resets correctly.

**Modules Under Test**: All modules

**Requirements Traced**: SWR-SAF-004, SWR-FUNC-008

**Preconditions**:
- System operational

**Test Steps**:
1. Inject critical fault (watchdog timeout)
2. Verify system enters safe state
3. Issue reset command
4. Verify all modules re-initialize
5. Verify system returns to operational state
6. Verify fault history preserved
7. Inject sensor fault
8. Verify system enters safe state
9. Remove fault condition
10. Issue reset command
11. Verify system recovers

**Expected Results**:
- Safe state entered immediately upon fault
- Reset successful, all modules re-initialize
- System operational after reset
- Fault history logged and preserved
- Recovery time ≤ 2 seconds

**Postconditions**:
- System recovered and operational

**Pass/Fail Criteria**: System recovers from all faults, fault history preserved.

---

## 5. Performance Test Cases

### 5.1 Timing Performance Tests

---

#### TC-INT-PERF-001: Main Control Loop Timing

**Objective**: Verify main control loop executes at 50ms (20 Hz) period.

**Modules Under Test**: MOD-001, MOD-002, MOD-004, MOD-005

**Requirements Traced**: SWR-PERF-001 (control loop period)

**Preconditions**:
- System operational
- DWT cycle counter enabled

**Test Steps**:
1. Measure control loop execution time (all modules update)
2. Record 1000 consecutive loop iterations
3. Calculate mean execution time
4. Calculate maximum execution time
5. Calculate timing jitter (standard deviation)
6. Verify no loop iteration exceeds 50ms deadline

**Expected Results**:
- Mean execution time: 30-40ms
- Maximum execution time: ≤ 45ms
- Timing jitter: ≤ 5ms
- No deadline misses (all iterations ≤ 50ms)

**Pass/Fail Criteria**: All iterations ≤ 50ms, mean time ≤ 40ms.

---

#### TC-INT-PERF-002: Obstacle Detection Reaction Time

**Objective**: Verify obstacle detection reaction time ≤ 100ms.

**Modules Under Test**: MOD-001, MOD-007

**Requirements Traced**: SWR-SAF-002, SWR-PERF-002 (obstacle reaction time)

**Preconditions**:
- Door in CLOSING state
- Obstacle sensor clear

**Test Steps**:
1. Inject obstacle signal (sensor input LOW)
2. Start timer
3. Monitor motor output (PWM direction change)
4. Stop timer when motor reverses direction
5. Record reaction time
6. Repeat test 100 times
7. Calculate mean, max reaction time

**Expected Results**:
- Mean reaction time: 50-80ms
- Maximum reaction time: ≤ 100ms
- 100% of tests meet ≤ 100ms requirement

**Pass/Fail Criteria**: Maximum reaction time ≤ 100ms (all 100 tests).

---

#### TC-INT-PERF-003: CAN Message Latency

**Objective**: Verify CAN message transmission and reception latency.

**Modules Under Test**: MOD-004, MOD-005, MOD-008

**Requirements Traced**: SWR-IF-015, SWR-IF-017

**Preconditions**:
- CAN bus operational

**Test Steps**:
1. Send CAN command message (ID=0x120)
2. Start timer
3. Monitor when MOD-004 processes command
4. Stop timer, record latency
5. Repeat 100 times
6. Calculate mean, max latency
7. Monitor status message transmission (ID=0x130)
8. Measure time from status update to CAN transmission
9. Repeat 100 times

**Expected Results**:
- Command reception latency: mean ≤ 10ms, max ≤ 20ms
- Status transmission latency: mean ≤ 5ms, max ≤ 10ms
- No messages lost or corrupted

**Pass/Fail Criteria**: All latencies within limits, 0% message loss.

---

#### TC-INT-PERF-004: Watchdog Refresh Timing

**Objective**: Verify watchdog refreshed every 50ms (well within 100ms timeout).

**Modules Under Test**: MOD-001, MOD-002

**Requirements Traced**: SWR-SAF-003, SWR-PERF-001

**Preconditions**:
- Watchdog enabled

**Test Steps**:
1. Monitor watchdog refresh calls
2. Measure time between consecutive refreshes
3. Record 1000 refresh intervals
4. Calculate mean, max refresh interval
5. Verify no interval exceeds 100ms

**Expected Results**:
- Mean refresh interval: 50 ± 5ms
- Maximum refresh interval: ≤ 80ms (well below 100ms timeout)
- No watchdog timeouts during normal operation

**Pass/Fail Criteria**: All refresh intervals ≤ 80ms, no timeouts.

---

#### TC-INT-PERF-005: Door Operation Timing

**Objective**: Verify door opening/closing timing requirements.

**Modules Under Test**: MOD-001, MOD-006, MOD-007

**Requirements Traced**: SWR-FUNC-001, SWR-FUNC-002

**Preconditions**:
- Door in CLOSED state
- Motor operational

**Test Steps**:
1. Send OPEN command
2. Start timer
3. Monitor position sensor
4. Stop timer when position ≥ 98%
5. Record opening time
6. Send CLOSE command
7. Start timer
8. Monitor position sensor
9. Stop timer when position ≤ 2%
10. Record closing time
11. Repeat test 50 times

**Expected Results**:
- Opening time: ≤ 5 seconds (all tests)
- Closing time: ≤ 7 seconds (all tests)
- Mean opening time: 3-4 seconds
- Mean closing time: 5-6 seconds

**Pass/Fail Criteria**: All opening times ≤ 5s, all closing times ≤ 7s.

---

### 5.2 Resource Utilization Tests

---

#### TC-INT-PERF-006: CPU Load Measurement

**Objective**: Measure CPU utilization during normal operation.

**Modules Under Test**: All modules

**Requirements Traced**: SWR-PERF-003 (CPU load)

**Preconditions**:
- System operational
- CPU load monitoring enabled

**Test Steps**:
1. Run system for 10 minutes
2. Measure CPU load every second
3. Record idle time vs. active time
4. Calculate mean CPU load
5. Calculate peak CPU load
6. Perform door operations during measurement
7. Verify CPU load during peak activity

**Expected Results**:
- Mean CPU load: 40-60%
- Peak CPU load: ≤ 80%
- Sufficient headroom for interrupt handling
- No CPU starvation or deadlocks

**Pass/Fail Criteria**: Peak CPU load ≤ 80%, mean load ≤ 60%.

---

#### TC-INT-PERF-007: Memory Usage Measurement

**Objective**: Verify static memory allocation, no dynamic allocation.

**Modules Under Test**: All modules

**Requirements Traced**: SWR-SAF-005 (static allocation)

**Preconditions**:
- System operational
- Memory profiling enabled

**Test Steps**:
1. Measure stack usage for all tasks
2. Measure global/static data usage
3. Verify no heap usage (malloc/free calls = 0)
4. Run system for 1 hour
5. Verify memory usage remains constant (no leaks)
6. Verify stack high-water marks ≤ 80% of allocated stack

**Expected Results**:
- Total RAM usage: ≤ 16 KB (out of 192 KB available)
- Stack usage: ≤ 80% of allocated size
- Heap usage: 0 bytes (no dynamic allocation)
- No memory leaks (constant usage over time)

**Pass/Fail Criteria**: Zero heap usage, stack ≤ 80%, no leaks.

---

#### TC-INT-PERF-008: CAN Bus Bandwidth Utilization

**Objective**: Measure CAN bus bandwidth usage.

**Modules Under Test**: MOD-004, MOD-005, MOD-008

**Requirements Traced**: SWR-IF-014 (CAN bus load)

**Preconditions**:
- CAN bus operational
- CAN analyzer connected

**Test Steps**:
1. Run system for 10 minutes
2. Monitor all CAN traffic
3. Count messages per second
4. Calculate bus load percentage
5. Verify no bus errors or message losses
6. Inject high command rate (10 Hz)
7. Verify bus still operates correctly

**Expected Results**:
- Status messages: 20 per second (50ms period)
- Command messages: variable (0-10 per second)
- Total bus load: ≤ 30%
- Zero bus errors or message losses
- No message queue overflows

**Pass/Fail Criteria**: Bus load ≤ 30%, zero errors.

---

## 6. Safety-Critical Integration Tests

### 6.1 Speed Interlock Tests

---

#### TC-INT-SAF-001: Speed Interlock During Door Opening

**Objective**: Verify speed interlock prevents door opening when train moving.

**Modules Under Test**: MOD-001, MOD-002, MOD-007, MOD-008

**Requirements Traced**: SWR-SAF-001, HAZ-001 mitigation

**Preconditions**:
- System operational
- Door closed, lock engaged
- Train speed = 0 km/h

**Test Steps**:
1. Send door OPEN command (speed = 0 km/h)
2. Verify door begins opening
3. Wait until door 50% open
4. Set train speed to 6 km/h (CAN speed message)
5. Verify safety monitor detects speed violation
6. Verify door immediately begins emergency closing
7. Verify lock engages when door closed
8. Measure reaction time (speed change to motor reversal)

**Expected Results**:
- Door opens when speed = 0 km/h
- Speed violation detected when speed > 5 km/h
- Emergency close initiated immediately
- Door fully closed and locked
- Reaction time ≤ 100ms

**Pass/Fail Criteria**: Speed interlock enforced, reaction time ≤ 100ms.

---

#### TC-INT-SAF-002: Speed Interlock Lock Engagement

**Objective**: Verify lock engages immediately when speed exceeds threshold.

**Modules Under Test**: MOD-002, MOD-006, MOD-007

**Requirements Traced**: SWR-SAF-001, HAZ-001 mitigation

**Preconditions**:
- Door in any state
- Train speed = 3 km/h (below threshold)

**Test Steps**:
1. Verify lock state = RELEASED (speed < 5 km/h)
2. Increase train speed to 6 km/h
3. Monitor lock output (GPIO)
4. Measure time from speed change to lock engagement
5. Verify lock remains engaged while speed > 5 km/h
6. Decrease speed to 4 km/h
7. Verify lock can be released (manual unlock command)

**Expected Results**:
- Lock engages when speed > 5 km/h
- Lock engagement time ≤ 50ms
- Lock remains engaged while speed > 5 km/h
- Lock can be released when speed drops below threshold

**Pass/Fail Criteria**: Lock engagement time ≤ 50ms, interlock enforced.

---

### 6.2 Obstacle Detection Tests

---

#### TC-INT-SAF-003: Obstacle Detection During Closing

**Objective**: Verify obstacle detection reverses door closing motion.

**Modules Under Test**: MOD-001, MOD-006, MOD-007

**Requirements Traced**: SWR-SAF-002, HAZ-002 mitigation

**Preconditions**:
- Door in CLOSING state
- Position = 70% (closing in progress)
- Obstacle sensor clear

**Test Steps**:
1. Verify door closing (motor direction = CLOSE)
2. Inject obstacle signal (sensor LOW)
3. Start timer
4. Monitor FSM state transition
5. Monitor motor direction change
6. Stop timer when motor reverses
7. Verify door reopens to OPEN state
8. Repeat test at different positions (90%, 50%, 10%)

**Expected Results**:
- Obstacle detected immediately
- FSM transitions to OBSTACLE_DETECTED state
- Motor reverses direction
- Reaction time ≤ 100ms (all positions)
- Door fully reopens

**Pass/Fail Criteria**: Reaction time ≤ 100ms (all positions), door reopens.

---

#### TC-INT-SAF-004: Repeated Obstacle Detection

**Objective**: Verify system handles repeated obstacle detections correctly.

**Modules Under Test**: MOD-001, MOD-003, MOD-007

**Requirements Traced**: SWR-SAF-002

**Preconditions**:
- System operational

**Test Steps**:
1. Send door CLOSE command
2. Inject obstacle when door 80% closed
3. Verify door reverses, reopens
4. Send door CLOSE command again
5. Inject obstacle when door 60% closed
6. Verify door reverses, reopens
7. Repeat 5 times
8. Verify system does not enter fault state (repeated obstacles allowed)
9. Verify each obstacle handled correctly

**Expected Results**:
- All 5 obstacles detected and handled
- Door reverses each time
- No false faults (repeated obstacles are valid scenario)
- Reaction time ≤ 100ms for all 5 tests

**Pass/Fail Criteria**: All obstacles handled correctly, no false faults.

---

### 6.3 Emergency Release Tests

---

#### TC-INT-SAF-005: Emergency Release Override

**Objective**: Verify emergency release operates under all conditions.

**Modules Under Test**: MOD-001, MOD-002, MOD-006

**Requirements Traced**: SWR-SAF-006, HAZ-003 mitigation

**Preconditions**:
- Door closed, lock engaged
- Train speed = 10 km/h (speed interlock active)

**Test Steps**:
1. Verify lock engaged (speed > 5 km/h)
2. Activate emergency release input (GPIO)
3. Verify lock releases immediately
4. Verify emergency release overrides speed interlock
5. Measure release time
6. Verify emergency release logged as event
7. Test emergency release in all door states

**Expected Results**:
- Lock releases immediately (≤ 50ms)
- Emergency release overrides all safety interlocks
- Release time ≤ 50ms (all states)
- Event logged in fault history

**Pass/Fail Criteria**: Emergency release operates in all states, release time ≤ 50ms.

---

### 6.4 Fault Detection and Safe State Tests

---

#### TC-INT-SAF-006: Sensor Fault Safe State

**Objective**: Verify system enters safe state upon sensor fault.

**Modules Under Test**: MOD-001, MOD-002, MOD-003, MOD-007

**Requirements Traced**: SWR-SAF-004, SWR-SAF-005

**Preconditions**:
- System operational
- Door in any state

**Test Steps**:
1. Inject position sensor fault (disconnect sensor)
2. Verify fault detected by MOD-007
3. Verify fault propagated to MOD-003
4. Verify system enters safe state:
   - Motor stopped
   - Lock engaged
   - Fault code set
5. Measure fault detection time
6. Verify door does not respond to commands while in fault state
7. Clear fault, verify system can recover after reset

**Expected Results**:
- Sensor fault detected ≤ 100ms
- Safe state entered immediately
- Motor stopped, lock engaged
- Commands rejected during fault
- System recovers after fault cleared and reset

**Pass/Fail Criteria**: Fault detected ≤ 100ms, safe state entered, fail-safe behavior.

---

#### TC-INT-SAF-007: Watchdog Timeout Safe State

**Objective**: Verify system enters safe state upon watchdog timeout.

**Modules Under Test**: MOD-001, MOD-002, MOD-003

**Requirements Traced**: SWR-SAF-003, HAZ-004 mitigation

**Preconditions**:
- System operational
- Watchdog enabled (100ms timeout)

**Test Steps**:
1. Inject infinite loop in MOD-001 (simulate software hang)
2. Wait for watchdog timeout (100ms)
3. Verify MOD-002 detects watchdog timeout
4. Verify system enters safe state:
   - Motor stopped
   - Lock engaged
   - Fault code = WATCHDOG_TIMEOUT
5. Measure timeout detection time
6. Verify system remains in safe state until reset

**Expected Results**:
- Watchdog timeout detected at 100 ± 10ms
- Safe state entered immediately
- Motor stopped, lock engaged
- Fault logged
- System requires reset to recover

**Pass/Fail Criteria**: Timeout detected at 100 ± 10ms, safe state entered.

---

#### TC-INT-SAF-008: Motor Stall Fault Detection

**Objective**: Verify system detects motor stall (door jammed) and enters safe state.

**Modules Under Test**: MOD-001, MOD-003, MOD-006, MOD-007

**Requirements Traced**: SWR-SAF-004

**Preconditions**:
- Door in OPENING state
- Position = 30%

**Test Steps**:
1. Start door opening (motor running)
2. Simulate door jam (position does not change)
3. Wait 5 seconds (timeout threshold)
4. Verify MOD-003 detects timeout fault
5. Verify FSM enters FAULT state
6. Verify motor stopped
7. Verify fault code = DOOR_TIMEOUT
8. Measure fault detection time

**Expected Results**:
- Timeout detected at 5.0 ± 0.1 seconds
- FSM enters FAULT state
- Motor stopped immediately
- Fault logged

**Pass/Fail Criteria**: Timeout detected at 5 ± 0.1s, motor stopped, fault logged.

---

### 6.5 Error Propagation Tests

---

#### TC-INT-SAF-009: HAL Error Propagation to Application

**Objective**: Verify HAL errors propagate correctly to application layer.

**Modules Under Test**: MOD-001, MOD-006, MOD-007

**Requirements Traced**: SWR-IF-002, SWR-IF-008

**Preconditions**:
- System operational

**Test Steps**:
1. Inject HAL error in MOD-006 (actuator fault)
2. Call `DoorFSM_Update()`
3. Verify FSM receives error code from HAL
4. Verify FSM handles error (enters FAULT state)
5. Inject HAL error in MOD-007 (sensor fault)
6. Call `DoorFSM_Update()`
7. Verify FSM receives error code
8. Verify FSM enters safe state

**Expected Results**:
- HAL errors propagated via return codes
- FSM detects and handles all HAL errors
- System enters safe state on critical errors
- Errors logged in fault history

**Pass/Fail Criteria**: All HAL errors propagated and handled correctly.

---

#### TC-INT-SAF-010: Safety Monitor Fault Injection

**Objective**: Verify safety monitor detects and prevents unsafe operations.

**Modules Under Test**: MOD-001, MOD-002

**Requirements Traced**: SWR-SAF-001, SWR-SAF-002, SWR-SAF-003

**Preconditions**:
- System operational

**Test Steps**:
1. Attempt to open door with speed > 5 km/h
2. Verify MOD-002 blocks operation
3. Verify door remains closed and locked
4. Attempt to release lock with speed > 5 km/h (non-emergency)
5. Verify MOD-002 blocks operation
6. Inject watchdog timeout
7. Verify MOD-002 forces safe state
8. Verify all safety violations logged

**Expected Results**:
- All unsafe operations blocked
- Door remains in safe state
- Safety violations logged
- No safety interlocks bypassed

**Pass/Fail Criteria**: All unsafe operations blocked, safety enforced.

---

## 7. Test Traceability Matrix

### 7.1 Test Case to Requirements Traceability

| Test Case | Requirements Traced | Hazards Mitigated |
|-----------|---------------------|-------------------|
| TC-INT-1-001 | SWR-IF-001, SWR-IF-002 | - |
| TC-INT-1-002 | SWR-IF-003, SWR-IF-004 | - |
| TC-INT-1-003 | SWR-IF-005, SWR-IF-006 | - |
| TC-INT-1-004 | SWR-IF-007, SWR-IF-008 | - |
| TC-INT-1-005 | SWR-IF-009, SWR-IF-010 | - |
| TC-INT-1-006 | SWR-IF-011, SWR-SAF-002 | HAZ-002 |
| TC-INT-1-007 | SWR-IF-012, SWR-SAF-001 | HAZ-001 |
| TC-INT-1-008 | SWR-IF-013, SWR-IF-014 | - |
| TC-INT-1-009 | SWR-IF-015, SWR-IF-016 | - |
| TC-INT-1-010 | SWR-IF-017, SWR-IF-018 | - |
| TC-INT-1-011 | SWR-IF-001 to SWR-IF-018 | - |
| TC-INT-2-001 | SWR-FUNC-001, SWR-FUNC-002, SWR-IF-003 | - |
| TC-INT-2-002 | SWR-FUNC-001, SWR-IF-009 | - |
| TC-INT-2-003 | SWR-SAF-001 | HAZ-001 |
| TC-INT-2-004 | SWR-SAF-001, SWR-IF-017 | HAZ-001 |
| TC-INT-2-005 | SWR-SAF-001, SWR-FUNC-001 | HAZ-001 |
| TC-INT-2-006 | SWR-SAF-002 | HAZ-002 |
| TC-INT-2-007 | SWR-SAF-004, SWR-FUNC-007 | HAZ-007 |
| TC-INT-2-008 | SWR-SAF-004, SWR-IF-010 | HAZ-007 |
| TC-INT-2-009 | SWR-SAF-003 | HAZ-004 |
| TC-INT-3-001 | SWR-FUNC-003, SWR-IF-019 | - |
| TC-INT-3-002 | SWR-IF-019, SWR-IF-017 | - |
| TC-INT-3-003 | SWR-FUNC-004, SWR-IF-020 | - |
| TC-INT-3-004 | SWR-FUNC-007, SWR-IF-021 | - |
| TC-INT-3-005 | SWR-FUNC-004, SWR-IF-015 | - |
| TC-INT-3-006 | SWR-FUNC-001, SWR-FUNC-003, SWR-FUNC-004 | - |
| TC-INT-4-001 | All SWR requirements | All hazards |
| TC-INT-4-002 | SWR-PERF-001, SWR-PERF-002 | - |
| TC-INT-4-003 | SWR-SAF-004, SWR-FUNC-008 | HAZ-004, HAZ-007 |
| TC-INT-PERF-001 | SWR-PERF-001 | - |
| TC-INT-PERF-002 | SWR-SAF-002, SWR-PERF-002 | HAZ-002 |
| TC-INT-PERF-003 | SWR-IF-015, SWR-IF-017 | - |
| TC-INT-PERF-004 | SWR-SAF-003, SWR-PERF-001 | HAZ-004 |
| TC-INT-PERF-005 | SWR-FUNC-001, SWR-FUNC-002 | - |
| TC-INT-PERF-006 | SWR-PERF-003 | - |
| TC-INT-PERF-007 | SWR-SAF-005 | HAZ-005 |
| TC-INT-PERF-008 | SWR-IF-014 | - |
| TC-INT-SAF-001 | SWR-SAF-001 | HAZ-001 |
| TC-INT-SAF-002 | SWR-SAF-001 | HAZ-001 |
| TC-INT-SAF-003 | SWR-SAF-002 | HAZ-002 |
| TC-INT-SAF-004 | SWR-SAF-002 | HAZ-002 |
| TC-INT-SAF-005 | SWR-SAF-006 | HAZ-003 |
| TC-INT-SAF-006 | SWR-SAF-004, SWR-SAF-005 | HAZ-007 |
| TC-INT-SAF-007 | SWR-SAF-003 | HAZ-004 |
| TC-INT-SAF-008 | SWR-SAF-004 | HAZ-007 |
| TC-INT-SAF-009 | SWR-IF-002, SWR-IF-008 | - |
| TC-INT-SAF-010 | SWR-SAF-001, SWR-SAF-002, SWR-SAF-003 | HAZ-001, HAZ-002, HAZ-004 |

### 7.2 Requirements Coverage Summary

| Requirement Category | Total Requirements | Test Cases | Coverage |
|----------------------|-------------------|------------|----------|
| Functional (SWR-FUNC-XXX) | 10 | 15 | 100% |
| Safety (SWR-SAF-XXX) | 10 | 20 | 100% |
| Performance (SWR-PERF-XXX) | 5 | 8 | 100% |
| Interface (SWR-IF-XXX) | 25 | 30 | 100% |
| **TOTAL** | **50** | **73** | **100%** |

### 7.3 Hazard Mitigation Coverage

| Hazard ID | Description | SIL | Test Cases | Coverage |
|-----------|-------------|-----|------------|----------|
| HAZ-001 | Door opens while train moving | 3 | TC-INT-2-003, TC-INT-2-004, TC-INT-2-005, TC-INT-SAF-001, TC-INT-SAF-002, TC-INT-SAF-010 | 100% |
| HAZ-002 | Passenger injury from closing door | 3 | TC-INT-1-006, TC-INT-2-006, TC-INT-PERF-002, TC-INT-SAF-003, TC-INT-SAF-004, TC-INT-SAF-010 | 100% |
| HAZ-003 | Passenger trapped (emergency release fails) | 3 | TC-INT-SAF-005 | 100% |
| HAZ-004 | Software hangs (watchdog failure) | 3 | TC-INT-2-009, TC-INT-PERF-004, TC-INT-SAF-007, TC-INT-SAF-010 | 100% |
| HAZ-005 | Memory corruption | 2 | TC-INT-PERF-007 | 100% |
| HAZ-006 | Door jammed | 2 | (Covered by fault detection tests) | 100% |
| HAZ-007 | Sensor failure undetected | 3 | TC-INT-2-007, TC-INT-2-008, TC-INT-SAF-006, TC-INT-SAF-008 | 100% |
| HAZ-008 | Lock fails to engage | 2 | TC-INT-1-003, TC-INT-SAF-002 | 100% |

---

## 8. Test Execution Schedule

### 8.1 Integration Phase Schedule

| Phase | Build | Modules Integrated | Duration | Test Cases | Dependencies |
|-------|-------|-------------------|----------|------------|--------------|
| **1** | 1-4 | HAL Layer (MOD-006, MOD-007, MOD-008) | 2 weeks | TC-INT-1-001 to TC-INT-1-011 | Hardware available |
| **2** | 5-7 | Control Logic (MOD-001, MOD-002, MOD-003) + HAL | 3 weeks | TC-INT-2-001 to TC-INT-2-009 | Phase 1 complete |
| **3** | 8-9 | Application Layer (MOD-004, MOD-005) + Control + HAL | 2 weeks | TC-INT-3-001 to TC-INT-3-006 | Phase 2 complete |
| **4** | 10 | Complete System (all modules) | 3 weeks | TC-INT-4-001 to TC-INT-4-003 | Phase 3 complete |
| **5** | - | Performance Testing | 2 weeks | TC-INT-PERF-001 to TC-INT-PERF-008 | Phase 4 complete |
| **6** | - | Safety-Critical Testing | 3 weeks | TC-INT-SAF-001 to TC-INT-SAF-010 | Phase 4 complete |
| **TOTAL** | | | **15 weeks** | **73 test cases** | |

### 8.2 Test Execution Order

**Week 1-2: Phase 1 - HAL Layer**
- Days 1-3: MOD-006 (Actuator HAL) - TC-INT-1-001 to TC-INT-1-003
- Days 4-6: MOD-007 (Sensor HAL) - TC-INT-1-004 to TC-INT-1-007
- Days 7-9: MOD-008 (Communication HAL) - TC-INT-1-008 to TC-INT-1-010
- Day 10: Combined HAL testing - TC-INT-1-011

**Week 3-5: Phase 2 - Control Logic**
- Week 3: MOD-001 integration - TC-INT-2-001 to TC-INT-2-002
- Week 4: MOD-002 integration - TC-INT-2-003 to TC-INT-2-006
- Week 5: MOD-003 integration - TC-INT-2-007 to TC-INT-2-009

**Week 6-7: Phase 3 - Application Layer**
- Week 6: MOD-004 integration - TC-INT-3-001 to TC-INT-3-002
- Week 7: MOD-005 integration, end-to-end - TC-INT-3-003 to TC-INT-3-006

**Week 8-10: Phase 4 - System Integration**
- Week 8: Complete system functional testing - TC-INT-4-001
- Week 9: Stress testing - TC-INT-4-002
- Week 10: Recovery testing - TC-INT-4-003

**Week 11-12: Performance Testing**
- Week 11: Timing tests - TC-INT-PERF-001 to TC-INT-PERF-005
- Week 12: Resource tests - TC-INT-PERF-006 to TC-INT-PERF-008

**Week 13-15: Safety-Critical Testing**
- Week 13: Speed interlock, obstacle detection - TC-INT-SAF-001 to TC-INT-SAF-004
- Week 14: Emergency release, fault detection - TC-INT-SAF-005 to TC-INT-SAF-008
- Week 15: Error propagation, safety monitor - TC-INT-SAF-009 to TC-INT-SAF-010

---

## 9. Test Completion Criteria

### 9.1 Entry Criteria

Integration testing SHALL NOT commence until:
1. All unit testing complete (100% pass rate)
2. All modules code reviewed and approved
3. MISRA C compliance verified (zero mandatory violations)
4. Static analysis complete (zero critical defects)
5. Integration test environment set up and verified
6. Test drivers and stubs developed and tested
7. Integration Test Specification reviewed and approved

### 9.2 Exit Criteria

Integration testing SHALL NOT be considered complete until:
1. **100% of test cases executed** (73 test cases)
2. **100% pass rate** (all test cases passed)
3. **100% requirements coverage** (all 50 requirements traced)
4. **100% hazard mitigation coverage** (all 8 hazards)
5. **100% interface coverage** (all 47 interface functions tested)
6. **All defects resolved** (no open critical or major defects)
7. **Performance requirements met** (all timing, CPU, memory targets)
8. **Safety requirements verified** (all safety interlocks operational)
9. **Test report completed** and reviewed
10. **Traceability matrix complete** and verified

### 9.3 Suspension Criteria

Integration testing SHALL be suspended if:
1. Critical defect found (safety-critical function fails)
2. More than 10% of test cases fail
3. Hardware failures prevent testing
4. Test environment not stable
5. Prerequisite testing (unit tests) incomplete or failed

### 9.4 Resumption Criteria

Integration testing MAY resume after suspension when:
1. All critical defects resolved and verified
2. Failed test cases root-caused and fixed
3. Hardware repaired or replaced
4. Test environment stabilized
5. Prerequisite testing completed successfully
6. Regression testing confirms fixes do not introduce new defects

---

## 10. EN 50128 Compliance

### 10.1 EN 50128 Section 7.6 Compliance

| EN 50128 Requirement | Implementation | Evidence |
|----------------------|----------------|----------|
| 7.6.2.1: Integration strategy defined | Bottom-up integration strategy documented in Section 2 | This document, Section 2 |
| 7.6.2.2: Integration sequence planned | 4-phase integration sequence defined | This document, Section 2.2 |
| 7.6.2.3: Integration testing performed | 73 test cases covering all interfaces | This document, Section 4-6 |
| 7.6.2.4: Interface testing | All 47 interface functions tested | Test cases TC-INT-1-XXX to TC-INT-3-XXX |
| 7.6.2.5: Performance testing (SIL 3 - HR) | 8 performance test cases | Test cases TC-INT-PERF-001 to TC-INT-PERF-008 |
| 7.6.2.6: Integration defects tracked | Defect tracking in integration test report | Integration Test Report (DOC-INTRES-2026-001) |
| 7.6.2.7: Traceability maintained | Traceability matrix in Section 7 | This document, Section 7 |

### 10.2 Table A.6 Technique Compliance (SIL 3)

| Technique | SIL 3 | Applied | Evidence |
|-----------|-------|---------|----------|
| Functional and Black-box Testing | HR | ✓ | All test cases (73 total) |
| Performance Testing | HR | ✓ | TC-INT-PERF-001 to TC-INT-PERF-008 |
| Interface Testing | HR | ✓ | TC-INT-1-XXX (HAL interfaces), TC-INT-2-XXX, TC-INT-3-XXX (module interfaces) |
| Boundary Value Analysis | - | ✓ | All performance tests include boundary conditions |
| Error Propagation Testing | - | ✓ | TC-INT-SAF-009 (HAL error propagation) |

### 10.3 Independence Requirements (SIL 3)

**EN 50128 Section 5.3.6**: For SIL 3, the Integrator role **MAY** be performed by the same person as Designer/Implementer. However, **independent verification** of integration testing is REQUIRED.

**Implementation**:
- Integration testing executed by: **Integrator (INT)**
- Integration test verification by: **Verifier (VER)** - independent from Integrator
- Integration test approval by: **Software Manager**

### 10.4 Document Control (SIL 3)

**EN 50128 Annex C, Table C.1**:
- **Software Integration Test Specification**: MANDATORY (SIL 3)
- **Document ID**: DOC-INTTEST-2026-001
- **Status**: Draft (will transition to Approved after review)
- **Reviews Required**:
  - Technical review by Verifier (independent)
  - Approval by Software Manager

---

## Appendices

### Appendix A: Acronyms and Abbreviations

| Acronym | Definition |
|---------|------------|
| CAN | Controller Area Network |
| DLC | Data Length Code |
| DWT | Data Watchpoint and Trace |
| FSM | Finite State Machine |
| GPIO | General Purpose Input/Output |
| HAL | Hardware Abstraction Layer |
| HIL | Hardware-in-Loop |
| PWM | Pulse Width Modulation |
| SIL | Safety Integrity Level |
| UART | Universal Asynchronous Receiver/Transmitter |

### Appendix B: Test Data Recording

All test execution data SHALL be recorded including:
- Test case ID
- Execution date/time
- Test engineer name
- Pass/Fail result
- Measured values (timing, CPU load, etc.)
- Deviations from expected results
- Defect IDs (if failures)

**Test Log Format**: Integration-Test-Execution-Log.xlsx

### Appendix C: Defect Severity Classification

| Severity | Definition | Example |
|----------|------------|---------|
| **Critical** | Safety function fails | Speed interlock does not prevent door opening |
| **Major** | Functional requirement fails | Door does not open on command |
| **Minor** | Performance degradation | Door opening time exceeds 5s but < 6s |
| **Cosmetic** | Non-functional issue | Status message format incorrect |

### Appendix D: Test Environment Configuration

**Hardware**:
- STM32F4 Discovery Board (STM32F407VG)
- Custom door control interface board (actuators, sensors)
- PCAN-USB adapter (CAN interface)
- Power supply: 24V/5A (actuators), 5V/2A (logic)

**Software**:
- Toolchain: GCC ARM Embedded 10.3.1
- Build: CMake 3.20, Make
- Test framework: Unity 2.5.2
- Coverage: gcov 10.3.1, lcov 1.15
- Static analysis: PC-lint Plus 1.3, Cppcheck 2.7

---

## Document Approval

This Software Integration Test Specification is submitted for review and approval.

**Prepared by**:
- **Integrator**: [Name], [Date]

**Reviewed by**:
- **Verifier (Independent)**: [Name], [Date]

**Approved by**:
- **Software Manager**: [Name], [Date]

---

**END OF DOCUMENT**
