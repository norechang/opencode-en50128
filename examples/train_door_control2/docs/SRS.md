# Software Requirements Specification (SRS)

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 Section 7.2, Table A.2

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SRS-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-02-19 |
| **Project** | train_door_control2 |
| **SIL Level** | 3 |
| **Author** | Requirements Engineer (REQ) |
| **Reviewer** | TBD |
| **Approver** | TBD, Project Manager |
| **Status** | Draft |

---

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-02-19 | REQ Engineer | Initial draft based on user requirements elicitation | - |
| 1.0 | TBD | REQ Engineer | First approved version | TBD |

---

## APPROVALS

**SIL 3 Requirements**: Author, Independent Reviewer, Safety Manager, Project Manager, Customer

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | Requirements Engineer | | 2026-02-19 |
| **Technical Reviewer** | TBD | | |
| **Safety Manager** | TBD | | |
| **QA Manager** | TBD | | |
| **Project Manager** | TBD | | |
| **Customer Representative** | TBD | | |

---

## 1. INTRODUCTION

### 1.1 Purpose

This Software Requirements Specification (SRS) defines the complete set of software requirements for the **Train Door Control System (train_door_control2)** for passenger railway vehicles. It provides a detailed description of functional requirements, performance requirements, interface requirements, and safety requirements in accordance with EN 50128:2011 Section 7.2.

**Intended Audience**:
- Software designers and implementers
- Verification and validation teams
- Safety engineers
- Project management
- Customer/certification authorities

### 1.2 Scope

This SRS applies to the **Train Door Control System** software, which controls passenger door opening, closing, locking, emergency release, and obstacle detection on railway vehicles operating at **SIL 3** (Safety Integrity Level 3).

**System Context**: The door control software is embedded within the train control and protection system. It interfaces with door actuators, position sensors, obstacle sensors, speed sensors, driver control panels, and the central train control system.

**In Scope**:
- Passenger door control for both left and right sides of the vehicle
- Door opening control with safety interlocks (train stationary, platform detection)
- Door closing control with obstacle detection and prevention
- Door locking when train is in motion (speed > 5 km/h)
- Emergency door release mechanism (manual override)
- Position monitoring and status reporting
- Fault detection and safe state management
- Multiple operational modes: Normal, Manual/Maintenance, Emergency Evacuation, Diagnostic, Degraded/Fail-Safe
- Hardware interfaces: door motors, position sensors, obstacle sensors, speed sensors, control panels, status indicators, emergency release handles

**Out of Scope**:
- Hardware design and specifications (covered by Hardware Specification)
- System-level requirements (derived in this document as typical requirements)
- Mechanical door mechanisms and actuators
- Multi-vehicle door coordination (future extension)

### 1.3 SIL Classification

**Target SIL Level**: **3** (SIL 3)

**Rationale**: Train door control is classified as SIL 3 based on hazard analysis per EN 50126/50129. The following hazards have been identified:
- **HAZ-001**: Doors opening while train is moving → Risk of passenger falling from train (catastrophic)
- **HAZ-002**: Doors closing on passengers → Risk of injury (critical)
- **HAZ-003**: Doors failing to open during emergency → Risk of passenger entrapment (critical)

EN 50128:2011 requires SIL 3 for functions where failure could result in serious injury or loss of life.

**EN 50128 Requirements Specification Techniques** (Table A.2):

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Applied |
|-----------|-------|---------|---------|---------|
| Formal Methods | - | R | HR | No (not required for this project scope) |
| Modelling | R | R | HR | **Yes** (state machines for door control modes) |
| Structured Methodology | R | R | HR | **Yes** (hierarchical decomposition, traceability) |
| Decision Tables | R | R | HR | **Yes** (door open/close logic with safety interlocks) |

### 1.4 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **SHALL** | Mandatory requirement (must be implemented) |
| **SHOULD** | Recommended requirement (highly desirable) |
| **MAY** | Optional requirement (nice to have) |
| **SIL** | Safety Integrity Level (0-4 per EN 50128) |
| **MISRA C** | Motor Industry Software Reliability Association C coding standard |
| **RTM** | Requirements Traceability Matrix |
| **WCET** | Worst-Case Execution Time |
| **HAZ** | Hazard identifier from Hazard Log |
| **ADC** | Analog-to-Digital Converter |
| **PWM** | Pulse-Width Modulation |
| **CAN** | Controller Area Network (communication bus) |
| **HMI** | Human-Machine Interface |
| **CCB** | Change Control Board |

### 1.5 References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[EN50126-1]** | EN 50126-1:2017 Railway applications - RAMS - Part 1: Generic RAMS process |
| **[EN50126-2]** | EN 50126-2:2017 Railway applications - RAMS - Part 2: Systems approach to safety |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 v2.0 |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-2026-001 v2.0 |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 v2.0 |
| **[SVaP]** | Software Validation Plan, DOC-SVAP-2026-001 v2.0 |
| **[MISRAC]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |
| **[HAZLOG]** | Hazard Log, TBD (to be created by Safety Engineer) |

### 1.6 Overview

This document is organized as follows:
- **Section 1**: Introduction, purpose, scope, SIL classification
- **Section 2**: General system description, context, constraints
- **Section 3**: Detailed software requirements (functional, performance, interface, safety, implementation)
- **Section 4**: Verification methods and traceability approach
- **Section 5**: Requirements summary and statistics
- **Section 6**: EN 50128 compliance matrix
- **Section 7**: References
- **Appendices**: Requirements template, glossary

---

## 2. GENERAL DESCRIPTION

### 2.1 System Context

```
┌──────────────────────────────────────────────────────────────┐
│              Train Control & Protection System               │
│                                                              │
│  ┌──────────────────────────────────────────────────────┐  │
│  │    Train Door Control Software (SIL 3)               │  │
│  │                                                      │  │
│  │  ┌──────────────┐  ┌──────────────┐  ┌───────────┐ │  │
│  │  │ Door Control │  │  Safety      │  │ Diagnostic│ │  │
│  │  │   Module     │  │  Monitor     │  │  Module   │ │  │
│  │  └──────────────┘  └──────────────┘  └───────────┘ │  │
│  │         │                 │                  │      │  │
│  └─────────┼─────────────────┼──────────────────┼──────┘  │
│            │                 │                  │         │
└────────────┼─────────────────┼──────────────────┼─────────┘
             ▼                 ▼                  ▼
    ┌────────────────┐  ┌─────────────┐  ┌──────────────┐
    │ Door Actuators │  │Speed Sensors│  │ Control Panel│
    │  (L/R sides)   │  │(Primary/Sec)│  │  & Display   │
    └────────────────┘  └─────────────┘  └──────────────┘
             ▲                 ▲                  ▲
    ┌────────────────┐  ┌─────────────┐  ┌──────────────┐
    │Position Sensors│  │  Obstacle   │  │  Emergency   │
    │ (Limit Switch) │  │   Sensors   │  │Release Handle│
    └────────────────┘  └─────────────┘  └──────────────┘
```

**System Interfaces**:
- **Hardware interfaces**: 
  - Door motors/actuators (left and right sides)
  - Position sensors (limit switches, 0-5V analog)
  - Obstacle sensors (infrared/pressure, digital/analog)
  - Speed sensors (primary and secondary for redundancy)
  - Driver control panel buttons (open/close commands)
  - Status indicator LEDs/display
  - Emergency release handles (mechanical/electrical)
  - External watchdog timer (hardware fail-safe)

- **Software interfaces**: 
  - Train control system (CAN bus, 500 kbps)
  - Diagnostic/maintenance system (UART serial console)

- **Communication interfaces**: 
  - CAN 2.0B bus (primary communication with train control)
  - UART serial (diagnostic port, non-safety-critical)

- **User interfaces**: 
  - Driver control panel (buttons for open/close commands)
  - Status display (door position, lock status, fault indicators)
  - Maintenance diagnostic console (text-based)

### 2.2 System Functions (High-Level)

The **Train Door Control Software** provides the following major functions:

1. **Door Movement Control**: Control opening and closing of passenger doors on left and right sides of the vehicle with precise position control and timing.

2. **Safety Interlock Management**: Enforce safety interlocks to prevent door opening when train is moving (speed > 5 km/h) and ensure doors are locked during motion.

3. **Obstacle Detection and Prevention**: Detect obstacles during door closing and immediately stop/reverse door movement to prevent passenger injury.

4. **Emergency Override**: Provide manual emergency door release capability that is always available regardless of system state.

5. **Position Monitoring and Status Reporting**: Continuously monitor door position (open/closed/intermediate) and report status to train control system and driver display.

6. **Fault Detection and Diagnosis**: Detect hardware faults (sensor failures, actuator failures, communication failures) and enter safe state with fault reporting.

7. **Multi-Mode Operation**: Support normal operation, manual/maintenance mode, emergency evacuation mode, diagnostic mode, and degraded/fail-safe mode.

### 2.3 User Characteristics

**Primary Users**: 
- Train drivers/operators (door open/close commands during normal operation)
- Maintenance technicians (diagnostic access, manual door operation)
- Passengers (emergency release only)

**User Expertise**: 
- Train drivers: Trained railway operators with domain-specific knowledge
- Maintenance technicians: Technical staff with electronics/software troubleshooting skills
- Passengers: No technical knowledge required for emergency release

**User Environment**: 
- Train driver cab (control panel, status display)
- Train interior (emergency release handles)
- Maintenance workshop (diagnostic console access)

### 2.4 Constraints

**Programming Language**: C (MISRA C:2012 compliant, mandatory for SIL 3)

**Platform Constraints**:
- Target processor: TBD (e.g., ARM Cortex-M4 or equivalent 32-bit microcontroller)
- Memory: TBD (typical range 64-256 KB RAM, 256-512 KB Flash ROM)
- Operating system: Bare-metal (no RTOS) OR safety-certified RTOS (if applicable)
- Execution time: 50ms main control loop (20 Hz)

**Regulatory Constraints**:
- EN 50128:2011 compliance **mandatory**
- EN 50126/50129 RAMS requirements **mandatory**
- MISRA C:2012 compliance **mandatory**
- National railway safety regulations (country-specific)

**Development Constraints**:
- **Static memory allocation only** (SIL 2+) - No `malloc/free` allowed
- **No recursion** (highly recommended SIL 3-4)
- **Cyclomatic complexity ≤ 10** (SIL 3-4)
- **Fixed-width integer types** (`uint8_t`, `uint16_t`, `uint32_t`, etc.)
- **Defensive programming mandatory** (pointer validation, range checks, return value checks)
- **Independent verification required** (SIL 3)
- **Independent validation required** (SIL 3)

**Environmental Constraints**:
- Operating temperature: 0°C to +40°C (indoor/sheltered environment)
- Humidity: 10% to 90% non-condensing
- Vibration: Per EN 61373 (railway vehicle vibration)
- Electromagnetic interference: Per EN 50121 (railway EMC)

### 2.5 Assumptions and Dependencies

**Assumptions**:
- Hardware will be available and tested by Phase 4 (Implementation)
- External train control system interface is stable and documented
- Speed sensor signals are reliable and meet accuracy requirements
- Power supply is stable (12V or 24V DC with appropriate regulation)

**Dependencies**:
- Depends on train control system for speed information and door commands
- Requires hardware watchdog timer for fail-safe operation
- Requires position sensors with ≥ 12-bit resolution for accurate door position
- Requires obstacle sensors with ≤ 100ms detection latency

---

## 3. SOFTWARE REQUIREMENTS

### 3.1 Functional Requirements

#### 3.1.1 Door Opening Control

**REQ-FUNC-001**: Door Opening Control  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-REQ-001 (typical system requirement)

**Description**: The software SHALL open the door when commanded by the driver control panel OR train control system AND the train is stationary (speed < 1 km/h) AND the door is not locked.

**Inputs**: 
- Door open command (boolean, from driver panel or CAN bus)
- Train speed (km/h, from speed sensor via CAN bus)
- Door lock status (boolean, internal state)
- Door position (0-100%, from position sensor ADC)

**Outputs**:
- Door actuator control signal (PWM, 0-100% duty cycle)
- Door status (opening/open) to train control system and display

**Preconditions**:
- System initialized and operational
- No critical faults present
- Door currently closed or partially closed
- Speed < 1 km/h for at least 500ms (debounce)

**Postconditions**:
- Door fully open (position ≥ 95%) within 3.0 seconds
- Door open status reported to train control system
- Actuator PWM reduced to 0% (no holding force required)

**Error Handling**:
- IF door fails to open within 5.0 seconds, THEN raise fault code FAULT_DOOR_OPEN_TIMEOUT and retry once
- IF obstacle detected during opening, THEN stop door immediately and raise fault code FAULT_OBSTACLE_OPENING
- IF position sensor failure detected, THEN enter degraded mode and use timeout-based open control

**Verification Method**: Test (unit test, integration test, system test), Inspection (design review)

---

**REQ-FUNC-002**: Door Closing Control  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-REQ-002

**Description**: The software SHALL close the door when commanded by the driver control panel OR train control system AND no obstacle is detected AND the door is currently open or partially open.

**Inputs**:
- Door close command (boolean, from driver panel or CAN bus)
- Obstacle detection sensor(s) (boolean array, digital inputs)
- Door position (0-100%, from position sensor ADC)

**Outputs**:
- Door actuator control signal (PWM, 0-100% duty cycle, reverse direction)
- Door status (closing/closed) to train control system and display

**Preconditions**:
- System initialized and operational
- No critical faults present
- Door currently open or partially open (position > 5%)
- Obstacle detection sensors operational

**Postconditions**:
- Door fully closed (position ≤ 5%) within 5.0 seconds
- Door closed status reported to train control system
- Actuator PWM reduced to 0% (mechanical latch holds door)

**Error Handling**:
- IF obstacle detected during closing, THEN immediately stop door (≤ 100ms reaction time), reverse direction to open door by 20%, and raise fault code FAULT_OBSTACLE_DETECTED
- IF door fails to close within 7.0 seconds, THEN raise fault code FAULT_DOOR_CLOSE_TIMEOUT and retry once
- IF position sensor failure detected, THEN enter degraded mode and use timeout-based close control with reduced speed

**Verification Method**: Test (unit test, integration test, system test, safety test with fault injection), Inspection

---

**REQ-FUNC-003**: Door Lock Control  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-REQ-003, HAZ-001

**Description**: The software SHALL lock the door whenever train speed exceeds 5 km/h. The software SHALL NOT unlock the door until train speed is below 2 km/h for at least 1.0 second (hysteresis to prevent oscillation).

**Inputs**:
- Train speed (km/h, from primary speed sensor)
- Train speed (km/h, from secondary speed sensor, for redundancy)
- Door position (0-100%, from position sensor)

**Outputs**:
- Door lock actuator signal (boolean, energize lock solenoid)
- Door lock status to train control system and display

**Preconditions**:
- System initialized
- Door is closed (position ≤ 5%)

**Postconditions**:
- Door locked when speed > 5 km/h
- Door unlocked when speed < 2 km/h for ≥ 1.0 second

**Safety Mechanism**: 
- Redundant speed monitoring (primary and secondary sensors)
- IF sensors disagree by > 10%, THEN use most restrictive value (lock door)
- IF any sensor fails, THEN lock door (fail-safe)

**Error Handling**:
- IF speed sensor failure detected, THEN lock door by default (fail-safe) and raise fault code FAULT_SPEED_SENSOR
- IF door not fully closed when speed > 5 km/h, THEN raise critical fault FAULT_DOOR_NOT_CLOSED_MOVING and trigger emergency brake request

**Verification Method**: Test (unit test, integration test, safety test), FMEA, Fault Injection

**Hazard Mitigation**: Mitigates HAZ-001 (doors opening while train moving)

---

**REQ-FUNC-004**: Emergency Door Release  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-REQ-004, HAZ-003

**Description**: The software SHALL provide manual emergency door release capability that unlocks and opens the door when the emergency release handle is activated, REGARDLESS of system state, train speed, or faults. This function SHALL be implemented with hardware-level fail-safe mechanism (direct electrical path from handle to lock release).

**Inputs**:
- Emergency release handle activation (boolean, hardware interrupt)

**Outputs**:
- Emergency release signal to door lock actuator (hardware-level direct path)
- Emergency event logged in fault log
- Emergency status reported to train control system

**Preconditions**: NONE (SHALL work in any system state, including power loss)

**Postconditions**:
- Door unlocked immediately (≤ 100ms)
- Door can be manually pushed open by passenger
- Emergency event recorded in non-volatile memory

**Safety Mechanism**: 
- Hardware-level direct electrical path from handle to lock release solenoid
- Software monitors emergency handle state and logs events but does NOT control emergency release function
- Emergency release overrides all software locks and interlocks

**Error Handling**:
- Emergency release is fail-safe and SHALL work even if software has failed

**Verification Method**: Test (integration test, safety test), Inspection, Demonstration

**Hazard Mitigation**: Mitigates HAZ-003 (passenger entrapment during emergency)

---

#### 3.1.2 Position Monitoring and Status Reporting

**REQ-FUNC-005**: Door Position Monitoring  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-REQ-005

**Description**: The software SHALL continuously monitor door position using analog position sensors and classify door state as CLOSED (≤ 5%), OPEN (≥ 95%), or INTERMEDIATE (> 5% and < 95%).

**Inputs**:
- Door position sensor (analog voltage 0-5V, via 12-bit ADC)
- Position sensor left side
- Position sensor right side

**Outputs**:
- Door state (CLOSED / OPEN / INTERMEDIATE) for each side
- Door position percentage (0-100%) for each side

**Sampling Rate**: 100 Hz minimum (10ms sampling period)

**Position Conversion**: 
```
Position (%) = (ADC_value / 4095) * 100
where ADC_value is 12-bit (0-4095)
```

**Preconditions**: ADC initialized and operational

**Postconditions**: Door position updated every 10ms maximum

**Error Handling**:
- IF ADC read fails, THEN use last valid value and raise warning WARN_ADC_READ_FAIL
- IF sensor value out of range (< -5% or > 105%), THEN raise fault FAULT_POSITION_SENSOR and enter degraded mode
- IF sensor noise detected (position change > 20% in single sample), THEN apply median filter

**Verification Method**: Test (unit test, integration test), Analysis (timing analysis)

---

**REQ-FUNC-006**: Status Reporting to Train Control System  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-REQ-006

**Description**: The software SHALL report door status to the train control system via CAN bus at 20 Hz (50ms update rate).

**Inputs**:
- Door position (from REQ-FUNC-005)
- Door lock status (from REQ-FUNC-003)
- Fault status (from fault detection module)

**Outputs** (CAN message):
```c
typedef struct {
    uint8_t door_left_position;     // 0-100 (%)
    uint8_t door_right_position;    // 0-100 (%)
    uint8_t door_left_state;        // 0=CLOSED, 1=OPEN, 2=INTERMEDIATE, 3=FAULT
    uint8_t door_right_state;       // 0=CLOSED, 1=OPEN, 2=INTERMEDIATE, 3=FAULT
    uint8_t door_left_locked;       // 0=unlocked, 1=locked
    uint8_t door_right_locked;      // 0=unlocked, 1=locked
    uint16_t fault_code;            // 0=no fault, 1-65535=fault codes
} door_status_msg_t;
```

**CAN Parameters**:
- Message ID: 0x201 (example)
- Update rate: 20 Hz (50ms)
- Baud rate: 500 kbps

**Preconditions**: CAN bus initialized

**Postconditions**: Status message transmitted every 50ms

**Error Handling**:
- IF CAN transmit fails, THEN retry up to 3 times and raise warning WARN_CAN_TX_FAIL

**Verification Method**: Test (integration test, interface test)

---

#### 3.1.3 Fault Detection and Safe State

**REQ-FUNC-007**: Fault Detection  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-REQ-007, HAZ-002

**Description**: The software SHALL continuously monitor for hardware and software faults and enter a safe state when critical faults are detected.

**Monitored Faults**:
1. Position sensor failure (out of range, stuck value, excessive noise)
2. Obstacle sensor failure (stuck high/low, inconsistent readings)
3. Speed sensor failure (timeout, out of range, primary/secondary disagreement)
4. CAN bus communication timeout (no message received for > 100ms)
5. Actuator feedback failure (door not moving when commanded)
6. Watchdog timeout (software lockup)
7. Internal consistency check failures (corrupted data structures)

**Safe State Definition**:
- All door actuators disabled (0% PWM)
- Doors locked (if closed) or held in current position (if open)
- Fault code reported to train control system and driver display
- Non-volatile fault log updated
- System awaits manual reset or automatic recovery (if fault clears)

**Fault Classification**:
- **Critical faults**: Immediate safe state entry (e.g., speed sensor failure, watchdog timeout)
- **Non-critical faults**: Warning logged, degraded mode operation continues (e.g., single obstacle sensor failure with redundancy available)

**Preconditions**: Fault detection module initialized

**Postconditions**: Safe state entered within 100ms of critical fault detection

**Error Handling**: Safe state is the error handling mechanism

**Verification Method**: Test (fault injection, safety test), FMEA, Analysis

**Hazard Mitigation**: Mitigates HAZ-002 (uncontrolled door movement due to system failure)

---

**REQ-FUNC-008**: Watchdog Monitoring  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-REQ-008, HAZ-002

**Description**: The software SHALL refresh an external hardware watchdog timer every 100ms. The watchdog timeout SHALL be 200ms (2x refresh period for margin). IF the software fails to refresh the watchdog, the external hardware SHALL reset the system into a safe state.

**Watchdog Refresh**:
- Refresh signal: GPIO toggle or watchdog peripheral kick
- Refresh rate: Every 100ms (±10ms tolerance)
- Timeout: 200ms

**Safe State (Hardware-Triggered)**:
- Watchdog hardware disables all actuators
- Watchdog hardware locks doors (if closed)
- System undergoes hardware reset
- After reset, software enters diagnostic mode and checks for watchdog reset flag

**Safety Mechanism**: External hardware watchdog (independent of software)

**Preconditions**: Watchdog timer initialized at startup

**Postconditions**: Watchdog refreshed every 100ms during normal operation

**Error Handling**: Watchdog timeout triggers hardware-level safe state and system reset

**Verification Method**: Test (fault injection - deliberate watchdog timeout), Inspection

**Hazard Mitigation**: Mitigates HAZ-002 (software lockup or infinite loop)

---

#### 3.1.4 Obstacle Detection

**REQ-FUNC-009**: Obstacle Detection During Door Closing  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-REQ-009, HAZ-002 (door closing on passenger)

**Description**: The software SHALL continuously monitor obstacle detection sensors during door closing operation. IF an obstacle is detected, the software SHALL immediately stop door movement (≤ 100ms reaction time) AND reverse door direction to open by at least 20% of full travel.

**Inputs**:
- Obstacle sensors (array of digital/analog sensors: infrared, pressure, capacitive)
- Door position (from position sensor)
- Door state (from state machine)

**Outputs**:
- Door actuator control (immediate stop, then reverse)
- Obstacle event logged
- Obstacle warning to driver display

**Obstacle Detection Logic**:
- IF ANY obstacle sensor is triggered during closing, THEN obstacle detected
- Use voting logic if multiple redundant sensors (2-out-of-3 voting)
- Apply sensor debouncing (10ms minimum trigger duration to avoid false positives)

**Timing Requirements**:
- Sensor sampling rate: 100 Hz (10ms period)
- Reaction time: ≤ 100ms from obstacle detection to door stop
- Reverse door by 20% to ensure obstacle is clear

**Preconditions**: 
- Door in CLOSING state
- Obstacle sensors operational

**Postconditions**: 
- Door stopped within 100ms
- Door reversed to open by 20% within 1.0 second
- Obstacle event logged in fault log

**Error Handling**:
- IF obstacle sensor failure detected (stuck or inconsistent), THEN enter degraded mode with reduced door closing speed
- IF obstacle persists for > 3 consecutive close attempts, THEN disable automatic closing and require manual intervention

**Verification Method**: Test (unit test, integration test, safety test with physical obstacle), Fault Injection

**Hazard Mitigation**: Mitigates HAZ-002 (door closing on passenger causing injury)

---

#### 3.1.5 Operational Modes

**REQ-FUNC-010**: Normal Operation Mode  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-REQ-010

**Description**: In Normal Operation Mode, the software SHALL accept door open/close commands from the train control system and driver control panel, enforce all safety interlocks (speed, obstacle detection), and report status normally.

**Mode Entry**: Automatic at system startup after successful power-on self-test (POST)

**Mode Behavior**:
- Accept door open/close commands (REQ-FUNC-001, REQ-FUNC-002)
- Enforce door locking based on speed (REQ-FUNC-003)
- Monitor obstacles (REQ-FUNC-009)
- Report status (REQ-FUNC-006)
- Detect faults (REQ-FUNC-007)

**Mode Exit**: Transition to Diagnostic Mode, Manual Mode, Emergency Mode, or Degraded Mode based on user command or fault detection

**Verification Method**: Test (system test, operational scenarios)

---

**REQ-FUNC-011**: Manual/Maintenance Mode  
**Priority**: Medium  
**SIL Level**: 0 (Non-safety-critical)  
**Traceability**: SYS-REQ-011

**Description**: In Manual/Maintenance Mode, the software SHALL allow direct door control by maintenance personnel with reduced safety interlocks (for testing and maintenance purposes). This mode SHALL be password-protected and SHALL require physical maintenance switch activation.

**Mode Entry**: 
- Maintenance switch activated (hardware key switch)
- Maintenance password entered via diagnostic console
- Train stationary (speed = 0 km/h)

**Mode Behavior**:
- Allow direct door open/close commands from diagnostic console
- Disable speed interlock (allow door operation while stationary only)
- Obstacle detection REMAINS ACTIVE (cannot be disabled)
- Display "MAINTENANCE MODE" warning on driver display
- Log all manual commands to diagnostic log

**Mode Exit**: 
- Maintenance switch deactivated
- Manual exit command from diagnostic console
- System reset

**Safety Constraints**: 
- Maintenance mode SHALL NOT allow door operation while train is moving
- Obstacle detection SHALL NOT be disabled in any mode

**Verification Method**: Test (manual test, inspection)

---

**REQ-FUNC-012**: Emergency Evacuation Mode  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-REQ-012

**Description**: In Emergency Evacuation Mode, the software SHALL immediately open all doors on both sides of the vehicle and disable automatic door closing. This mode is activated by the train driver during emergency situations requiring rapid passenger evacuation.

**Mode Entry**: 
- Emergency evacuation button pressed (driver control panel)
- Emergency evacuation command received via CAN bus

**Mode Behavior**:
- Immediately command all doors to open (left and right sides)
- Disable automatic door closing (manual close only, requires confirmation)
- Unlock all doors
- Disable speed interlock (allow doors to remain open even if train moves slowly)
- Display "EMERGENCY EVACUATION" on all displays
- Sound audible alarm (if available)
- Log emergency evacuation event with timestamp

**Mode Exit**: 
- Manual reset by driver after evacuation complete
- System reset

**Safety Considerations**: 
- Emergency evacuation overrides normal safety interlocks
- Obstacle detection REMAINS ACTIVE during emergency opening
- Emergency evacuation event is non-volatile and requires explicit reset

**Verification Method**: Test (system test, demonstration), Inspection

---

**REQ-FUNC-013**: Diagnostic/Test Mode  
**Priority**: Low  
**SIL Level**: 0 (Non-safety-critical)  
**Traceability**: SYS-REQ-013

**Description**: In Diagnostic/Test Mode, the software SHALL disable door control and execute system diagnostics including sensor tests, actuator tests, communication tests, and memory tests.

**Mode Entry**: 
- Diagnostic command from maintenance console
- Train stationary and doors closed
- No passengers on board (manual confirmation required)

**Mode Behavior**:
- Disable all door control functions
- Execute diagnostic test suite:
  1. Position sensor test (read sensors, check range)
  2. Obstacle sensor test (trigger sensors, check response)
  3. Actuator test (apply low-power PWM, check feedback)
  4. Communication test (CAN bus loopback, UART echo)
  5. Memory test (RAM/ROM integrity check)
  6. Watchdog test (verify watchdog triggering, not recommended for field use)
- Report diagnostic results to console
- Log diagnostic results to non-volatile memory

**Mode Exit**: 
- Diagnostic tests complete
- Manual exit command
- System reset

**Verification Method**: Test (unit test for each diagnostic), Manual Test

---

**REQ-FUNC-014**: Degraded/Fail-Safe Mode  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-REQ-014

**Description**: In Degraded/Fail-Safe Mode, the software SHALL continue to provide basic door control functionality with reduced performance when non-critical faults are detected. Critical faults SHALL result in complete safe state shutdown.

**Mode Entry**: Automatic upon detection of non-critical fault (e.g., single sensor failure with redundancy available)

**Mode Behavior** (Degraded Operation):
- Continue door control with reduced speed (50% of normal)
- Use redundant sensors if primary sensor fails
- Use timeout-based position control if position sensor fails
- Increase obstacle detection sensitivity (more conservative)
- Display "DEGRADED MODE" warning on driver display
- Log all degraded mode operations

**Mode Exit**: 
- Fault cleared (sensor recovery)
- Manual reset after maintenance
- Transition to full safe state if degradation worsens

**Safe State Conditions** (Complete Shutdown):
- Critical fault detected (e.g., all speed sensors failed, actuator failure, watchdog timeout)
- All actuators disabled
- Doors locked (if closed) or held (if open)
- System awaits manual reset

**Verification Method**: Test (fault injection, degraded operation test), FMEA

---

### 3.2 Performance Requirements

**REQ-PERF-001**: Control Loop Timing  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-PERF-001

**Description**: The software SHALL execute the main control loop at 20 Hz (50ms period). Worst-case execution time (WCET) for one control loop iteration SHALL NOT exceed 40ms (80% of period, leaving 20% margin).

**Control Loop Tasks**:
1. Read all sensors (position, obstacle, speed)
2. Process state machine logic
3. Update actuator outputs (PWM)
4. Transmit CAN status message
5. Refresh watchdog timer
6. Process diagnostic messages

**Timing Budget** (example allocation):
- Sensor reading: 10ms
- State machine logic: 15ms
- Actuator updates: 5ms
- CAN transmission: 5ms
- Watchdog/diagnostics: 5ms
- **Total WCET**: ≤ 40ms (with 10ms margin)

**Acceptance Criteria**: Measured WCET ≤ 40ms under worst-case load conditions (all doors moving, all sensors active, maximum CAN traffic)

**Verification Method**: Performance Testing (oscilloscope, profiler, timing analysis), Static Analysis (WCET tools)

---

**REQ-PERF-002**: Door Opening Time  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-PERF-002

**Description**: The software SHALL command the door to open from fully closed (0%) to fully open (≥ 95%) within 3.0 seconds under normal conditions (no obstacles, normal temperature, normal voltage).

**Target Time**: 3.0 seconds (typical)  
**Maximum Time**: 5.0 seconds (with fault raised if exceeded)

**Acceptance Criteria**: 95% of door opening operations complete within 3.0 seconds during acceptance testing

**Verification Method**: Performance Testing (measure door open time with position sensor and stopwatch/timer)

---

**REQ-PERF-003**: Door Closing Time  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-PERF-003

**Description**: The software SHALL command the door to close from fully open (100%) to fully closed (≤ 5%) within 5.0 seconds under normal conditions (no obstacles).

**Target Time**: 5.0 seconds (typical)  
**Maximum Time**: 7.0 seconds (with fault raised if exceeded)

**Note**: Closing time is longer than opening time for safety (slower speed reduces impact force if obstacle detection fails)

**Acceptance Criteria**: 95% of door closing operations complete within 5.0 seconds during acceptance testing

**Verification Method**: Performance Testing

---

**REQ-PERF-004**: Obstacle Detection Reaction Time  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-PERF-004, HAZ-002

**Description**: The software SHALL react to obstacle detection by stopping door movement within 100ms from the time the obstacle sensor is triggered.

**Timing Breakdown**:
- Sensor sampling: ≤ 10ms (100 Hz sampling)
- Signal processing and decision: ≤ 40ms
- Actuator command update: ≤ 10ms
- Actuator physical response: ≤ 40ms (depends on hardware)
- **Total reaction time**: ≤ 100ms

**Acceptance Criteria**: Measured reaction time ≤ 100ms in 100% of test cases during safety testing

**Verification Method**: Safety Testing (high-speed measurement with oscilloscope, physical obstacle test rig)

---

**REQ-PERF-005**: CPU Utilization  
**Priority**: Medium  
**SIL Level**: 3  
**Traceability**: SYS-PERF-005

**Description**: The software SHALL consume no more than 70% of available CPU cycles under worst-case load conditions.

**Measurement**: CPU idle time ≥ 30% during stress testing (all doors active, maximum CAN traffic, all diagnostics enabled)

**Acceptance Criteria**: Measured CPU utilization ≤ 70% during stress testing

**Verification Method**: Performance Testing (CPU profiler, idle task measurement)

---

**REQ-PERF-006**: Memory Footprint  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-PERF-006

**Description**: The software SHALL meet the following memory constraints:
- **RAM usage**: ≤ 32 KB (data + stack)
- **ROM usage**: ≤ 128 KB (code + constants)

**Note**: Actual memory limits depend on target hardware (TBD)

**Acceptance Criteria**: 
- Measured RAM usage ≤ 32 KB with 10% margin (≤ 28.8 KB typical)
- Measured ROM usage ≤ 128 KB

**Verification Method**: Static Analysis (linker map file analysis), Performance Testing (runtime memory profiler)

---

### 3.3 Interface Requirements

#### 3.3.1 Hardware Interfaces

**REQ-IF-HW-001**: Door Position Sensor Interface (Left Side)  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-IF-001

**Description**: The software SHALL read the left door position from an analog position sensor via ADC channel 0.

**Interface Specification**:
- **Signal Type**: Analog voltage, 0-5V
- **Encoding**: 0V = fully closed (0%), 5V = fully open (100%)
- **Sampling Rate**: 100 Hz (10ms period)
- **Resolution**: 12-bit ADC (0-4095 counts)
- **Conversion Formula**: `Position (%) = (ADC_value / 4095.0) * 100.0`
- **Valid Range**: -5% to 105% (allows for sensor tolerance)

**C Data Type**:
```c
typedef struct {
    uint16_t adc_raw;        // Raw ADC value (0-4095)
    float position_percent;  // Calculated position (0.0-100.0)
    bool valid;              // Sensor reading valid flag
} position_sensor_t;
```

**Error Handling**:
- IF ADC read fails, THEN set `valid = false`, use last valid value, raise warning WARN_ADC_FAIL_LEFT
- IF `position_percent < -5.0` OR `position_percent > 105.0`, THEN raise fault FAULT_POSITION_SENSOR_LEFT

**Verification Method**: Integration Test, Interface Test

---

**REQ-IF-HW-002**: Door Position Sensor Interface (Right Side)  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-IF-002

**Description**: The software SHALL read the right door position from an analog position sensor via ADC channel 1.

**Interface Specification**: (Same as REQ-IF-HW-001, but ADC channel 1)

**Verification Method**: Integration Test, Interface Test

---

**REQ-IF-HW-003**: Door Actuator Control Interface (Left Side)  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-IF-003

**Description**: The software SHALL control the left door actuator motor via PWM signal on GPIO pin TBD (e.g., Timer 1 Channel 1).

**Interface Specification**:
- **Signal Type**: PWM, 0-100% duty cycle
- **Frequency**: 10 kHz (to reduce motor noise)
- **Direction Control**: Separate GPIO pin (HIGH = open, LOW = close)
- **Range**: 0% = no motion, 100% = maximum speed
- **Update Rate**: 20 Hz (50ms, synchronized with control loop)

**C Data Type**:
```c
typedef struct {
    uint8_t pwm_duty_cycle;  // 0-100 (%)
    bool direction_open;     // true = open, false = close
    bool enable;             // true = actuator enabled
} actuator_control_t;
```

**Error Handling**:
- IF PWM output fails (timer malfunction), THEN disable actuator (`enable = false`) and raise critical fault FAULT_PWM_LEFT

**Verification Method**: Integration Test, Interface Test (oscilloscope measurement)

---

**REQ-IF-HW-004**: Door Actuator Control Interface (Right Side)  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-IF-004

**Description**: The software SHALL control the right door actuator motor via PWM signal on GPIO pin TBD (e.g., Timer 1 Channel 2).

**Interface Specification**: (Same as REQ-IF-HW-003, but different GPIO pins)

**Verification Method**: Integration Test, Interface Test

---

**REQ-IF-HW-005**: Obstacle Sensor Interface (Left Side)  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-IF-005, HAZ-002

**Description**: The software SHALL read obstacle detection sensors for the left door. Multiple sensors (infrared, pressure, capacitive) SHALL be read to provide redundancy.

**Interface Specification**:
- **Number of Sensors**: 3 (infrared beam, pressure strip, capacitive proximity)
- **Signal Type**: Digital (GPIO inputs, active low)
- **Sampling Rate**: 100 Hz (10ms period)
- **Debounce Time**: 10ms (obstacle must persist for 10ms to be valid)
- **Detection Logic**: OR logic (ANY sensor triggered = obstacle detected)

**C Data Type**:
```c
typedef struct {
    bool infrared_triggered;
    bool pressure_triggered;
    bool capacitive_triggered;
    bool obstacle_detected;  // Logical OR of above
    uint32_t last_trigger_time_ms;
} obstacle_sensors_t;
```

**Error Handling**:
- IF sensor stuck high (always triggered), THEN raise warning WARN_OBSTACLE_SENSOR_STUCK_LEFT
- IF all sensors stuck low (never triggered), THEN raise fault FAULT_OBSTACLE_SENSORS_LEFT

**Verification Method**: Integration Test, Safety Test (physical obstacle test)

---

**REQ-IF-HW-006**: Obstacle Sensor Interface (Right Side)  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-IF-006, HAZ-002

**Description**: The software SHALL read obstacle detection sensors for the right door (same specification as REQ-IF-HW-005).

**Verification Method**: Integration Test, Safety Test

---

**REQ-IF-HW-007**: Speed Sensor Interface (Primary)  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-IF-007, HAZ-001

**Description**: The software SHALL read the primary train speed sensor via CAN bus message from the train control system.

**Interface Specification**:
- **Protocol**: CAN 2.0B
- **Message ID**: 0x100 (example)
- **Data Format**: 2 bytes, unsigned integer, units: 0.1 km/h (resolution 0.1 km/h)
- **Range**: 0-300 km/h (0-3000 in raw value)
- **Update Rate**: 20 Hz (50ms)
- **Timeout**: 100ms (if no message received, assume communication fault)

**C Data Type**:
```c
typedef struct {
    uint16_t speed_raw;         // Raw CAN data (units: 0.1 km/h)
    float speed_kmh;            // Calculated speed (km/h)
    bool valid;                 // Data valid (received within timeout)
    uint32_t last_update_ms;    // Timestamp of last message
} speed_sensor_t;
```

**Error Handling**:
- IF no CAN message received within 100ms, THEN set `valid = false` and raise fault FAULT_SPEED_SENSOR_PRIMARY
- IF speed value out of range (> 300 km/h), THEN raise fault FAULT_SPEED_INVALID

**Verification Method**: Integration Test, Interface Test

---

**REQ-IF-HW-008**: Speed Sensor Interface (Secondary)  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-IF-008, HAZ-001

**Description**: The software SHALL read the secondary train speed sensor (diverse technology, e.g., wheel encoder) via CAN bus for redundancy.

**Interface Specification**: (Similar to REQ-IF-HW-007, but different CAN message ID and potentially different resolution)

**Redundancy Logic**:
- IF primary and secondary sensors agree within 10%, THEN use primary value
- IF sensors disagree by > 10%, THEN use MAXIMUM value (most restrictive, fail-safe)
- IF both sensors fail, THEN assume speed > 5 km/h (lock doors, fail-safe)

**Verification Method**: Integration Test, Safety Test (sensor disagreement test)

---

**REQ-IF-HW-009**: Driver Control Panel Interface  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-IF-009

**Description**: The software SHALL read door open/close commands from the driver control panel via digital GPIO inputs.

**Interface Specification**:
- **Open Button**: GPIO input, active low (pulled high, pressed = low)
- **Close Button**: GPIO input, active low
- **Emergency Evacuation Button**: GPIO input, active low (safety-critical)
- **Debounce Time**: 50ms (button must be pressed for ≥ 50ms to register)

**C Data Type**:
```c
typedef struct {
    bool open_button_pressed;
    bool close_button_pressed;
    bool emergency_button_pressed;
} driver_panel_t;
```

**Verification Method**: Integration Test, Interface Test

---

**REQ-IF-HW-010**: Status Indicator LEDs Interface  
**Priority**: Low  
**SIL Level**: 0 (Non-safety-critical)  
**Traceability**: SYS-IF-010

**Description**: The software SHALL control status indicator LEDs on the driver control panel to show door state and faults.

**Interface Specification**:
- **Door Open LED (Green)**: GPIO output, HIGH = on
- **Door Closed LED (Green)**: GPIO output, HIGH = on
- **Fault LED (Red)**: GPIO output, HIGH = on
- **Update Rate**: 20 Hz (synchronized with control loop)

**Verification Method**: Manual Test, Inspection

---

**REQ-IF-HW-011**: Watchdog Timer Interface  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-IF-011, HAZ-002

**Description**: The software SHALL refresh an external hardware watchdog timer via GPIO toggle or watchdog peripheral every 100ms.

**Interface Specification**:
- **Watchdog Trigger**: GPIO toggle OR watchdog peripheral kick instruction
- **Refresh Rate**: 100ms (±10ms tolerance)
- **Timeout**: 200ms (hardware-configured)
- **Reset Action**: Hardware-triggered system reset and safe state entry

**Verification Method**: Integration Test, Safety Test (watchdog timeout test)

---

**REQ-IF-HW-012**: Emergency Release Handle Interface  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: SYS-IF-012, HAZ-003

**Description**: The software SHALL monitor the emergency release handle activation signal via hardware interrupt (GPIO input).

**Interface Specification**:
- **Signal Type**: Digital GPIO input with hardware interrupt (rising edge)
- **Active Level**: Active high (handle pulled = HIGH)
- **Hardware Fail-Safe**: Emergency handle ALSO has direct electrical path to door lock release (hardware-level, independent of software)
- **Software Function**: Log emergency event, report to train control system

**Note**: Emergency release is primarily a hardware function. Software monitors for logging and reporting only.

**Verification Method**: Integration Test, Safety Test, Inspection

---

#### 3.3.2 Software Interfaces

**REQ-IF-SW-001**: Train Control System CAN Bus Interface  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: SYS-IF-020

**Description**: The software SHALL communicate with the train control system via CAN 2.0B bus at 500 kbps.

**CAN Parameters**:
- **Protocol**: CAN 2.0B (29-bit extended ID)
- **Baud Rate**: 500 kbps
- **Bus Termination**: 120Ω (hardware)
- **Update Rate**: 20 Hz (50ms cycle)

**Received Messages** (from train control system):
1. **Door Command Message** (ID: 0x180):
   ```c
   typedef struct {
       uint8_t door_left_open_cmd;   // 0=no command, 1=open
       uint8_t door_left_close_cmd;  // 0=no command, 1=close
       uint8_t door_right_open_cmd;
       uint8_t door_right_close_cmd;
       uint8_t emergency_stop;       // 0=normal, 1=emergency stop
       uint8_t emergency_evac;       // 0=normal, 1=emergency evacuation
   } door_command_msg_t;
   ```

2. **Speed Sensor Message** (ID: 0x100): See REQ-IF-HW-007

**Transmitted Messages** (to train control system):
1. **Door Status Message** (ID: 0x201): See REQ-FUNC-006

**Timeout Handling**:
- IF no command message received for > 200ms, THEN enter safe state (doors hold current position)
- IF no speed message received for > 100ms, THEN raise fault FAULT_SPEED_SENSOR_TIMEOUT

**Verification Method**: Integration Test, Interface Test (CAN bus analyzer)

---

#### 3.3.3 User Interfaces

**REQ-IF-UI-001**: Diagnostic Serial Console Interface  
**Priority**: Low  
**SIL Level**: 0 (Non-safety-critical)  
**Traceability**: SYS-IF-030

**Description**: The software MAY provide diagnostic information via UART serial console for maintenance and debugging purposes.

**Interface Specification**:
- **Protocol**: UART
- **Baud Rate**: 115200 baud, 8 data bits, no parity, 1 stop bit (8N1)
- **Format**: ASCII text, newline-terminated (`\r\n`)
- **Content**: 
  - System status (door position, state, faults)
  - Fault codes and descriptions
  - Diagnostic counters (door open/close cycles, fault counts)
  - Manual commands (enter maintenance mode, run diagnostics)

**Example Output**:
```
TRAIN DOOR CONTROL v1.0 - DIAGNOSTIC CONSOLE
> status
Door Left: CLOSED (0%), Locked
Door Right: CLOSED (0%), Locked
Speed: 0.0 km/h
Mode: NORMAL
Faults: NONE
> 
```

**Note**: This interface is for maintenance only and is NOT safety-critical.

**Verification Method**: Manual Test

---

### 3.4 Safety Requirements

**REQ-SAFE-001**: Fail-Safe Door Locking  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: HAZ-001 (doors open while train moving causing passenger fall)

**Description**: The software SHALL ensure that doors remain locked whenever train speed exceeds 5 km/h. This is a safety-critical requirement to prevent passenger injury. IF speed sensor fails, doors SHALL be locked by default (fail-safe).

**Safety Mechanism**: 
- Redundant speed monitoring (primary and secondary sensors)
- IF sensors disagree by > 10%, use most restrictive value (higher speed → lock doors)
- IF any sensor fails, lock doors by default

**Failure Mode Coverage**:
- Speed sensor failure → Lock doors (fail-safe)
- Speed sensor stuck at zero → Secondary sensor overrides (IF secondary shows speed > 5 km/h, lock doors)
- Both sensors fail → Lock doors (fail-safe)
- CAN bus communication failure → Lock doors (fail-safe)

**Verification Method**: Safety Test, FMEA, Fault Injection (sensor failure simulation)

**Hazard Mitigation**: Mitigates HAZ-001 (doors opening during train motion)

---

**REQ-SAFE-002**: Watchdog Monitoring and Safe State  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: HAZ-002 (software lockup causing unsafe door operation)

**Description**: The software SHALL refresh an external hardware watchdog timer every 100ms. IF the software fails to refresh the watchdog (due to lockup, infinite loop, or crash), the hardware SHALL reset the system into a safe state within 200ms.

**Safe State Definition**:
- All door actuators disabled (0% PWM)
- Doors locked IF closed
- Doors held in current position IF open or intermediate
- System undergoes hardware reset
- After reset, software checks watchdog reset flag and logs watchdog event

**Verification Method**: Safety Test, Fault Injection (deliberate watchdog timeout by disabling refresh)

**Hazard Mitigation**: Mitigates HAZ-002 (software lockup or failure)

---

**REQ-SAFE-003**: Redundant Speed Sensor Monitoring  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: HAZ-001

**Description**: The software SHALL monitor train speed using TWO independent speed sensors (primary and secondary with diverse technology). IF sensors disagree by more than 10%, the software SHALL use the HIGHER speed value (most restrictive, fail-safe).

**Sensor Comparison Logic**:
```c
if (abs(primary_speed - secondary_speed) > 0.1 * max(primary_speed, secondary_speed)) {
    // Sensors disagree by > 10%
    actual_speed = max(primary_speed, secondary_speed);  // Use higher (fail-safe)
    raise_warning(WARN_SPEED_SENSOR_DISAGREEMENT);
}
```

**Verification Method**: Safety Test, Fault Injection (sensor disagreement simulation)

---

**REQ-SAFE-004**: Emergency Release Hardware Independence  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: HAZ-003 (passenger entrapment)

**Description**: The emergency door release function SHALL be implemented with a hardware-level fail-safe mechanism that operates INDEPENDENTLY of software. The emergency release handle SHALL have a direct electrical path to the door lock release solenoid that functions even if software has failed or power is lost.

**Hardware Mechanism**:
- Emergency handle activation provides direct electrical connection to lock release solenoid
- No software intervention required for emergency release
- Software monitors handle state for logging and reporting only

**Verification Method**: Inspection (hardware design review), Safety Test (emergency release with software disabled), Demonstration

**Hazard Mitigation**: Mitigates HAZ-003 (passenger entrapment during emergency)

---

**REQ-SAFE-005**: Obstacle Detection Redundancy  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: HAZ-002 (door closing on passenger)

**Description**: The software SHALL use multiple redundant obstacle detection sensors (infrared, pressure, capacitive) with OR logic. An obstacle is detected IF ANY sensor is triggered. IF one sensor fails (stuck or inconsistent), the system SHALL continue operation using remaining sensors and raise a warning.

**Redundancy Logic**:
- 3 sensors per door: infrared beam, pressure strip, capacitive proximity
- Obstacle detected = infrared OR pressure OR capacitive
- IF one sensor stuck high (always triggered), ignore that sensor and use remaining sensors
- IF all sensors fail, enter degraded mode (slower door speed, manual close only)

**Verification Method**: Safety Test, Fault Injection (individual sensor failures)

**Hazard Mitigation**: Mitigates HAZ-002 (door closing on passenger)

---

**REQ-SAFE-006**: Safe State on Critical Fault  
**Priority**: Critical  
**SIL Level**: 3  
**Traceability**: HAZ-002, HAZ-001

**Description**: Upon detection of a critical fault (actuator failure, both speed sensors failed, watchdog timeout), the software SHALL immediately enter a safe state within 100ms.

**Safe State Actions**:
1. Disable all door actuators (0% PWM)
2. Lock doors IF closed (position ≤ 5%)
3. Hold doors in current position IF open or intermediate
4. Report critical fault to train control system
5. Log fault event to non-volatile memory
6. Display fault on driver panel (red LED, fault code)
7. Await manual reset or automatic recovery (if fault clears)

**Critical Faults** (trigger immediate safe state):
- FAULT_SPEED_SENSOR_BOTH_FAILED
- FAULT_ACTUATOR_LEFT_FAILED
- FAULT_ACTUATOR_RIGHT_FAILED
- FAULT_WATCHDOG_TIMEOUT
- FAULT_POSITION_SENSOR_BOTH_FAILED
- FAULT_MEMORY_CORRUPTION

**Verification Method**: Safety Test, Fault Injection, FMEA

---

### 3.5 C Language Implementation Constraints

**REQ-IMPL-001**: MISRA C:2012 Compliance  
**Priority**: High  
**SIL Level**: 3 (Mandatory)  
**Traceability**: EN 50128 Section 7.4, Table A.4

**Description**: All source code SHALL comply with MISRA C:2012 guidelines. Deviations SHALL be documented in a deviation log with technical justification and approved by QA Manager.

**Compliance Target**: 100% compliance OR ≤ 5% documented deviations

**Verification Tools**: PC-lint Plus, Cppcheck, Clang Static Analyzer

**Verification Method**: Static Analysis (PC-lint Plus reports), Code Review

---

**REQ-IMPL-002**: Fixed-Width Integer Types  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: MISRA C Rule 4.6, EN 50128 best practice

**Description**: The software SHALL use fixed-width integer types from `<stdint.h>` (`uint8_t`, `uint16_t`, `uint32_t`, `int8_t`, etc.) instead of platform-dependent types (`int`, `long`, `unsigned`).

**Rationale**: Ensures portability and predictable behavior across platforms (32-bit vs 64-bit, different compilers)

**Example**:
```c
// CORRECT:
uint32_t counter;
int16_t temperature;

// FORBIDDEN:
unsigned long counter;   // Platform-dependent size
int temperature;         // Platform-dependent size
```

**Verification Method**: Static Analysis (grep for forbidden types), Code Review

---

**REQ-IMPL-003**: Static Memory Allocation  
**Priority**: Critical  
**SIL Level**: 3 (Mandatory)  
**Traceability**: EN 50128 Section 7.4, Table A.4

**Description**: The software SHALL use ONLY static memory allocation. Dynamic memory allocation functions (`malloc`, `calloc`, `realloc`, `free`) SHALL NOT be used.

**Rationale**: Eliminates memory leaks, heap fragmentation, non-deterministic execution time

**Example**:
```c
// CORRECT:
static uint8_t buffer[256];
static sensor_data_t sensor_data;

// FORBIDDEN:
uint8_t* buffer = malloc(256);  // Dynamic allocation not allowed
```

**Verification Method**: Static Analysis (grep for `malloc|calloc|realloc|free`), Code Review, Linker Configuration (disable heap)

---

**REQ-IMPL-004**: No Recursion  
**Priority**: High  
**SIL Level**: 3 (Highly Recommended)  
**Traceability**: EN 50128 Section 7.4, Table A.4

**Description**: The software SHALL NOT use recursive function calls (direct or indirect recursion).

**Rationale**: Eliminates stack overflow risk, ensures bounded execution time and stack usage

**Verification Method**: Static Analysis (call graph analysis with PC-lint or dedicated tool), Code Review

---

**REQ-IMPL-005**: Cyclomatic Complexity Limit  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: EN 50128 Section 7.4, Table A.4

**Description**: Every function SHALL have cyclomatic complexity ≤ 10.

**Rationale**: Lower complexity improves testability, readability, and maintainability. SIL 3 requires CC ≤ 10.

**Measurement**: Cyclomatic complexity = number of decision points + 1

**Verification Method**: Static Analysis (Lizard, PC-lint, McCabe IQ)

---

**REQ-IMPL-006**: Defensive Programming  
**Priority**: High  
**SIL Level**: 3 (Highly Recommended)  
**Traceability**: EN 50128 Section 7.3, Table A.3

**Description**: The software SHALL implement defensive programming techniques:
1. Validate all input parameters (NULL pointer checks, range checks)
2. Check all function return values
3. Use assertions for internal consistency checks
4. Handle all error conditions explicitly

**Example**:
```c
error_t process_sensor_data(const sensor_data_t* input, result_t* output) {
    // Defensive checks
    if (input == NULL) {
        return ERROR_NULL_POINTER;
    }
    if (output == NULL) {
        return ERROR_NULL_POINTER;
    }
    if (input->value > MAX_SENSOR_VALUE) {
        return ERROR_OUT_OF_RANGE;
    }
    
    // Process data...
    error_t result = calculate_position(input);
    if (result != SUCCESS) {
        return result;  // Check return value
    }
    
    return SUCCESS;
}
```

**Verification Method**: Code Review, Static Analysis (checking for unchecked return values, NULL dereferences)

---

**REQ-IMPL-007**: Error Handling Strategy  
**Priority**: High  
**SIL Level**: 3  
**Traceability**: EN 50128 design best practices

**Description**: The software SHALL use explicit error return codes (enum type `error_t`). Error handling via `errno`, `setjmp/longjmp`, or exceptions SHALL NOT be used.

**Error Type Definition**:
```c
typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER,
    ERROR_OUT_OF_RANGE,
    ERROR_TIMEOUT,
    ERROR_HARDWARE_FAULT,
    ERROR_CAN_TX_FAIL,
    ERROR_CAN_RX_TIMEOUT,
    ERROR_SENSOR_FAULT,
    ERROR_ACTUATOR_FAULT,
    // ... additional error codes
} error_t;
```

**All functions that can fail SHALL return `error_t`.**

**Verification Method**: Code Review, Static Analysis

---

**REQ-IMPL-008**: Function Parameter Limits  
**Priority**: Medium  
**SIL Level**: 3  
**Traceability**: MISRA C, coding best practices

**Description**: Functions SHALL have no more than 6 parameters. IF more data is required, use a structure.

**Rationale**: Improves readability, reduces stack usage, prevents parameter passing errors

**Example**:
```c
// CORRECT (using structure):
typedef struct {
    uint8_t door_id;
    uint8_t command;
    uint8_t speed_limit;
    bool obstacle_override;
} door_command_params_t;

error_t control_door(const door_command_params_t* params);

// AVOID (too many parameters):
error_t control_door(uint8_t door_id, uint8_t command, uint8_t speed_limit, 
                     bool obstacle_override, uint8_t retry_count, 
                     uint32_t timeout_ms, bool log_enabled);  // 7 params - too many
```

**Verification Method**: Static Analysis, Code Review

---

**REQ-IMPL-009**: No Global Variables (Minimize)  
**Priority**: Medium  
**SIL Level**: 3  
**Traceability**: EN 50128 best practices, MISRA C

**Description**: Global variables SHOULD be minimized. IF global variables are necessary (e.g., hardware register access, inter-module communication), they SHALL be:
1. Declared `static` to limit scope to compilation unit
2. Accessed via getter/setter functions (encapsulation)
3. Protected with `volatile` keyword if accessed by interrupts

**Example**:
```c
// File: door_control.c
static volatile door_state_t g_door_state_left;  // Static, volatile (ISR access)

// Getter/setter functions
door_state_t get_door_state_left(void) {
    return g_door_state_left;
}

void set_door_state_left(door_state_t state) {
    g_door_state_left = state;
}
```

**Verification Method**: Code Review, Static Analysis

---

**REQ-IMPL-010**: Const Correctness  
**Priority**: Medium  
**SIL Level**: 3  
**Traceability**: MISRA C, coding best practices

**Description**: Function parameters that are NOT modified SHALL be declared `const`. This improves code safety and compiler optimization.

**Example**:
```c
// CORRECT:
error_t calculate_speed(const sensor_data_t* input, speed_result_t* output);
                        //^^^^^ input not modified, marked const

// INCORRECT:
error_t calculate_speed(sensor_data_t* input, speed_result_t* output);
                        // input not modified, but not marked const
```

**Verification Method**: Code Review, Static Analysis (MISRA C checkers)

---

---

## 4. VERIFICATION AND TRACEABILITY

### 4.1 Verification Methods

Each requirement SHALL be verified using one or more of the following methods per EN 50128 Section 6.2:

| Method | Description | Applicable To | EN 50128 Reference |
|--------|-------------|---------------|-------------------|
| **Test** | Unit test, integration test, system test, validation test | Functional, performance, interface requirements | Table A.5, A.13 |
| **Analysis** | Static analysis, dynamic analysis, timing analysis, WCET analysis | Performance, safety, implementation requirements | Table A.5, A.19 |
| **Inspection** | Code review, design review, document review | All requirements | Table A.5 |
| **Demonstration** | Operational demonstration to customer or certification authority | High-level functional requirements, validation | Table A.7 |

**Verification Responsibilities**:
- **Unit Testing**: Implementer (IMP) and Tester (TST)
- **Integration Testing**: Integrator (INT) and Tester (TST)
- **System Testing**: Tester (TST)
- **Static Analysis**: Verifier (VER)
- **Code Review**: Quality Assurance (QUA)
- **Validation**: Validator (VAL), independent team (SIL 3)

### 4.2 Requirements Traceability Matrix (RTM)

**Location**: `docs/RTM.md` (to be created)

**Format**: Bidirectional traceability from system requirements → software requirements → design → code → tests.

**Example RTM Entry**:

| System Req | SW Req | Priority | SIL | Design | Code Module | Test Cases | Status |
|------------|--------|----------|-----|--------|-------------|------------|--------|
| SYS-001 | REQ-FUNC-001 | High | 3 | MOD-DOOR-CTRL | door_control.c:open_door() | TC-UNIT-001, TC-INT-001, TC-SYS-001 | Traced |
| SYS-001 | REQ-FUNC-003 | Critical | 3 | MOD-SAFETY | safety_monitor.c:check_speed() | TC-UNIT-010, TC-SAFETY-001 | Traced |

**RTM Completeness Requirements**:
- 100% of software requirements SHALL be traced backward to system requirements (or marked as derived)
- 100% of software requirements SHALL be traced forward to design, code, and tests
- All safety requirements (SIL 3) SHALL have complete traceability

**RTM Maintenance**: 
- RTM SHALL be updated whenever requirements, design, or tests change
- RTM SHALL be reviewed and approved at each phase gate
- Configuration Manager (CM) is responsible for RTM updates

### 4.3 Requirements Quality Checklist

All requirements in this SRS SHALL meet the following quality criteria (per EN 50128 Section 7.2):

- [x] **Unique ID**: Each requirement has a unique identifier (REQ-<CATEGORY>-NNN)
- [x] **Unambiguous**: Single interpretation (uses SHALL/SHOULD/MAY keywords consistently)
- [x] **Testable**: Verification method identified, acceptance criteria defined
- [x] **Complete**: All necessary information provided (inputs, outputs, preconditions, postconditions, error handling)
- [x] **Consistent**: No conflicts with other requirements (to be verified during design review)
- [x] **Traceable**: Linked to system requirements (SYS-REQ-NNN) or hazards (HAZ-NNN)
- [x] **SIL Assigned**: SIL level specified for all requirements
- [x] **C-Compatible**: Implementation feasible in C within constraints (static allocation, no recursion, complexity ≤ 10)
- [x] **Safety-Focused**: Safety requirements identified and linked to hazards

**Quality Verification**: This checklist SHALL be reviewed during requirements verification (by VER agent) in Phase 2.

---

## 5. REQUIREMENTS SUMMARY

### 5.1 Requirements Count by Category

| Category | Count | Critical | High | Medium | Low |
|----------|-------|----------|------|--------|-----|
| **Functional** | 14 | 4 | 8 | 2 | 0 |
| **Performance** | 6 | 1 | 4 | 1 | 0 |
| **Interface - Hardware** | 12 | 3 | 7 | 0 | 2 |
| **Interface - Software** | 1 | 0 | 1 | 0 | 0 |
| **Interface - User** | 1 | 0 | 0 | 0 | 1 |
| **Safety** | 6 | 6 | 0 | 0 | 0 |
| **Implementation** | 10 | 1 | 5 | 4 | 0 |
| **TOTAL** | **50** | **15** | **25** | **7** | **3** |

### 5.2 Requirements Count by SIL Level

| SIL Level | Count | Percentage |
|-----------|-------|------------|
| **SIL 3** | 46 | 92% |
| **SIL 0** | 4 | 8% |
| **TOTAL** | **50** | **100%** |

**Note**: 92% of requirements are safety-critical (SIL 3), reflecting the high safety integrity of this train door control system.

### 5.3 Requirements Count by Verification Method

| Verification Method | Count | Percentage |
|---------------------|-------|------------|
| **Test** (Unit/Integration/System/Safety) | 35 | 70% |
| **Static Analysis** | 10 | 20% |
| **Code Review / Inspection** | 10 | 20% |
| **FMEA / Fault Injection** | 6 | 12% |
| **Manual Test / Demonstration** | 3 | 6% |

**Note**: Many requirements require multiple verification methods (e.g., test + analysis).

---

## 6. COMPLIANCE MATRIX

### 6.1 EN 50128 Section 7.2 Compliance

| EN 50128 Requirement | Section | Evidence | Status |
|---------------------|---------|----------|--------|
| **Requirements specification established** | 7.2.2 | This document (SRS DOC-SRS-2026-001) | ✓ Complete |
| **Requirements unambiguous** | 7.2.3 | SHALL/SHOULD/MAY keywords used consistently, Section 4.3 quality checklist | ✓ Complete |
| **Requirements testable** | 7.2.4 | Verification method and acceptance criteria for each requirement, Section 4.1 | ✓ Complete |
| **Requirements traceable** | 7.2.5 | Traceability to system requirements and hazards, RTM planned (Section 4.2) | ✓ Complete |
| **SIL level assigned** | 7.2.6 | All requirements have SIL field (46 SIL 3, 4 SIL 0) | ✓ Complete |
| **Safety requirements identified** | 7.2.7 | Section 3.4 (6 safety requirements with hazard traceability) | ✓ Complete |
| **Interface requirements specified** | 7.2.8 | Section 3.3 (14 interface requirements: HW, SW, UI) | ✓ Complete |
| **C language constraints specified** | 7.2.9 | Section 3.5 (10 implementation constraints: MISRA C, static allocation, etc.) | ✓ Complete |

### 6.2 EN 50128 Table A.2 Compliance (Requirements Techniques for SIL 3)

| Technique | SIL 3 Recommendation | Applied | Evidence |
|-----------|---------------------|---------|----------|
| **Structured Methodology** | HR | ✓ Yes | Hierarchical decomposition (functional, performance, interface, safety, implementation), systematic traceability (RTM) | ✓ |
| **Modelling** | HR | ✓ Yes | State machine model for operational modes (Normal, Manual, Emergency, Diagnostic, Degraded) planned for design phase | ✓ |
| **Decision Tables** | HR | ✓ Yes | Door open/close logic with safety interlocks (speed, obstacle detection, lock status) documented as decision logic in requirements | ✓ |
| **Formal Methods** | HR | ✗ No | Not applied for this project. Rationale: Structured methodology with state machines and decision tables provide sufficient rigor for SIL 3. Formal methods add complexity without proportional benefit for this control application. | Justified |

**Compliance Status**: **COMPLIANT** (3 out of 4 highly recommended techniques applied, 1 justified as not required)

---

## 7. REFERENCES

### 7.1 Normative References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[EN50126-1]** | EN 50126-1:2017 Railway applications - RAMS - Part 1: Generic RAMS process |
| **[EN50126-2]** | EN 50126-2:2017 Railway applications - RAMS - Part 2: Systems approach to safety |
| **[MISRAC]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |
| **[EN50125]** | EN 50125 series - Environmental conditions for railway rolling stock |
| **[EN50155]** | EN 50155 - Railway applications - Electronic equipment used on rolling stock |

### 7.2 Project References

| Reference | Document |
|-----------|----------|
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 v2.0 |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-2026-001 v2.0 |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 v2.0 |
| **[SVaP]** | Software Validation Plan, DOC-SVAP-2026-001 v2.0 |
| **[HAZLOG]** | Hazard Log, TBD (to be created by Safety Engineer /saf) |
| **[RTM]** | Requirements Traceability Matrix, docs/RTM.md (to be created) |

---

## APPENDICES

### Appendix A: Requirements Template (Used in This Document)

```markdown
**REQ-[CATEGORY]-NNN**: [Requirement Title]  
**Priority**: [Critical / High / Medium / Low]  
**SIL Level**: [0, 1, 2, 3, 4]  
**Traceability**: [Parent requirement ID (SYS-REQ-NNN), hazard ID (HAZ-NNN)]

**Description**: [Detailed requirement using SHALL/SHOULD/MAY]

**Inputs**: [Required inputs with data types]  
**Outputs**: [Expected outputs with data types]  
**Preconditions**: [System state before requirement applies]  
**Postconditions**: [System state after requirement fulfilled]  

**Error Handling**: [How errors are detected and handled]

**Verification Method**: [Test / Analysis / Inspection / Demonstration]  
**Acceptance Criteria**: [Specific pass/fail criteria]
```

### Appendix B: Glossary

| Term | Definition |
|------|------------|
| **ADC** | Analog-to-Digital Converter - converts analog sensor signals (0-5V) to digital values |
| **CAN** | Controller Area Network - serial communication bus used in vehicles |
| **Cyclomatic Complexity** | Software metric measuring number of independent paths through code (decision points + 1) |
| **Fail-Safe** | System behavior that defaults to safe state upon failure |
| **FMEA** | Failure Modes and Effects Analysis - safety analysis technique |
| **PWM** | Pulse-Width Modulation - technique for controlling motor speed via duty cycle |
| **RAMS** | Reliability, Availability, Maintainability, Safety - EN 50126 framework |
| **RTM** | Requirements Traceability Matrix - document mapping requirements to design, code, tests |
| **SIL** | Safety Integrity Level (0-4) - measure of risk reduction per EN 50128 |
| **WCET** | Worst-Case Execution Time - maximum time for code execution |

### Appendix C: System Requirements (Typical - For Traceability)

The following typical system requirements are assumed for this train door control system:

| System Req ID | Description |
|--------------|-------------|
| **SYS-REQ-001** | The system shall open doors when commanded and train is stationary |
| **SYS-REQ-002** | The system shall close doors when commanded and no obstacle detected |
| **SYS-REQ-003** | The system shall lock doors when train speed > 5 km/h |
| **SYS-REQ-004** | The system shall provide emergency door release |
| **SYS-REQ-005** | The system shall monitor door position continuously |
| **SYS-REQ-006** | The system shall report door status to train control |
| **SYS-REQ-007** | The system shall detect and report faults |
| **SYS-REQ-008** | The system shall implement watchdog monitoring |
| **SYS-REQ-009** | The system shall detect obstacles during door closing |
| **SYS-REQ-010** | The system shall support normal operation mode |
| **SYS-REQ-011** | The system shall support maintenance mode |
| **SYS-REQ-012** | The system shall support emergency evacuation mode |
| **SYS-REQ-013** | The system shall support diagnostic mode |
| **SYS-REQ-014** | The system shall support degraded/fail-safe mode |
| **SYS-PERF-001** | The system shall execute control loop at 20 Hz |
| **SYS-PERF-002** | Doors shall open within 3.0 seconds |
| **SYS-PERF-003** | Doors shall close within 5.0 seconds |
| **SYS-PERF-004** | Obstacle detection reaction time ≤ 100ms |
| **SYS-PERF-005** | CPU utilization ≤ 70% |
| **SYS-PERF-006** | Memory footprint: RAM ≤ 32 KB, ROM ≤ 128 KB |
| **SYS-IF-001..012** | Hardware interfaces (sensors, actuators, control panel, etc.) |
| **SYS-IF-020** | CAN bus interface to train control system |
| **SYS-IF-030** | UART diagnostic console |

### Appendix D: Hazards (Typical - For Traceability)

The following hazards are assumed for this system (detailed hazard log to be created by Safety Engineer):

| Hazard ID | Hazard Description | Risk Level | Mitigation |
|-----------|-------------------|------------|------------|
| **HAZ-001** | Doors open while train is moving | Catastrophic | Speed interlock, redundant speed sensors, fail-safe locking (REQ-FUNC-003, REQ-SAFE-001, REQ-SAFE-003) |
| **HAZ-002** | Doors close on passenger causing injury | Critical | Obstacle detection, fast reaction time, redundant sensors (REQ-FUNC-009, REQ-SAFE-005) |
| **HAZ-003** | Passengers trapped due to door failure during emergency | Critical | Emergency release hardware independence (REQ-FUNC-004, REQ-SAFE-004) |

---

## DOCUMENT HISTORY

This document is maintained under configuration control per SCMP (DOC-SCMP-2026-001). All changes SHALL be approved by the Change Control Board (CCB).

**Current Version**: 1.0 (Draft)  
**Last Updated**: 2026-02-19  
**Next Review**: Phase 2 Requirements Verification (by VER agent)  
**Baseline**: Not yet baselined (awaiting approval chain: REQ → QUA → VER → PM → Customer)

---

**END OF DOCUMENT**
