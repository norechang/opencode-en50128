# System Requirements Specification

**DOCUMENT TYPE**: System-Level Input Document  
**EN 50128 REFERENCE**: Section 7.2.2 (Input to Software Requirements Specification)  
**STANDARD**: EN 50126:2017, IEC 62278

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SYS-REQ-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-02-21 |
| **Project** | Train Door Control System (train_door_control2) |
| **System SIL Level** | SIL 3 |
| **Author** | System Engineering Team |
| **Status** | Approved - Baseline for Software Development |

---

## VERSION HISTORY

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-01-15 | System Engineer | Initial draft | - |
| 0.5 | 2026-01-28 | System Engineer | Review updates | Technical Lead |
| 1.0 | 2026-02-10 | System Engineer | Approved baseline | Project Manager, Safety Authority |

---

## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **System Engineer** | Dr. Sarah Chen | [Signed] | 2026-02-10 |
| **Safety Manager** | Michael Torres | [Signed] | 2026-02-10 |
| **Technical Lead** | Robert Kim | [Signed] | 2026-02-10 |
| **Project Manager** | Lisa Anderson | [Signed] | 2026-02-10 |
| **Customer Representative** | Railway Authority UK | [Signed] | 2026-02-10 |

---

## 1. INTRODUCTION

### 1.1 Purpose

This System Requirements Specification (SysRS) defines the complete set of system-level requirements for the **Train Door Control System** for passenger railway vehicles. It establishes the baseline requirements that will be allocated to hardware, software, and operational procedures.

This document serves as the **primary input** to:
- Software Requirements Specification (EN 50128 Section 7.2)
- Hardware Requirements Specification
- System Safety Requirements Specification
- System Architecture Description

### 1.2 Scope

**System**: Train Door Control System for passenger railway vehicles

**System Boundary**: 
- Passenger door assemblies (left and right sides)
- Door control electronics and actuators
- Sensors (position, obstacle, speed)
- Driver control interface
- Central train control interface
- Emergency release mechanisms
- Status indication systems

**Operational Environment**:
- Passenger railway vehicles (metro, commuter, regional trains)
- Operating temperature: -40°C to +70°C
- Voltage: 24V DC nominal (18V - 36V range)
- EMC environment: Railway EN 50121
- Vibration: EN 61373 Category 1 Class B

### 1.3 System Context

The Train Door Control System is a safety-critical subsystem of the overall train control and protection system. It interfaces with:

- **Train Control Management System (TCMS)**: Operational commands, status reporting
- **Speed Monitoring System**: Train speed for door interlocks
- **Platform Detection System**: Platform side detection
- **Driver Control Panel**: Manual door control, status displays
- **Passenger Emergency Interfaces**: Emergency door release handles
- **Door Hardware**: Motors, locks, position sensors, obstacle sensors

### 1.4 System SIL Classification

**System SIL Level**: **SIL 3** (Safety Integrity Level 3)

**Rationale** (per EN 50126 hazard analysis):

| Hazard ID | Hazard Description | Consequence | Frequency | SIL |
|-----------|-------------------|-------------|-----------|-----|
| SYS-HAZ-001 | Doors open while train moving (>5 km/h) | Passenger fall from train → Fatality | Catastrophic | **SIL 3** |
| SYS-HAZ-002 | Doors close on passenger causing injury | Passenger trapped/crushed → Serious injury | Critical | **SIL 2** |
| SYS-HAZ-003 | Doors fail to open in emergency | Passenger entrapment → Serious injury/fatality | Critical | **SIL 3** |
| SYS-HAZ-004 | Door unlocks while train moving | Passenger could open door → Fatality | Catastrophic | **SIL 3** |

**Highest SIL**: SIL 3 (driven by HAZ-001, HAZ-003, HAZ-004)

---

## 2. SYSTEM REQUIREMENTS

### 2.1 Functional Requirements

#### 2.1.1 Door Opening Control

**SYS-REQ-001**: The system SHALL control passenger door opening on the left and right sides independently.  
**SIL**: 3  
**Rationale**: Basic operational function

**SYS-REQ-002**: The system SHALL only permit door opening when ALL of the following conditions are met:  
- Train speed ≤ 5 km/h
- Platform side correctly identified (left/right)
- Driver door enable command received OR emergency evacuation mode active
- No door fault conditions present

**SIL**: 3  
**Rationale**: Safety interlock to prevent HAZ-001 (doors opening while moving)

**SYS-REQ-003**: The system SHALL complete door opening within 3.0 seconds from door enable command.  
**SIL**: 1  
**Rationale**: Operational performance requirement

**SYS-REQ-004**: The system SHALL detect door fully open position using redundant position sensors (2oo2).  
**SIL**: 3  
**Rationale**: Confirmation of safe state

#### 2.1.2 Door Closing Control

**SYS-REQ-005**: The system SHALL control passenger door closing on commanded side(s).  
**SIL**: 3  
**Rationale**: Basic operational function

**SYS-REQ-006**: The system SHALL detect obstacles during door closing operation using obstacle detection sensors.  
**SIL**: 3  
**Rationale**: Safety function to prevent HAZ-002 (doors closing on passengers)

**SYS-REQ-007**: The system SHALL automatically re-open doors if obstacle is detected during closing.  
**SIL**: 3  
**Rationale**: Safety response to HAZ-002

**SYS-REQ-008**: The system SHALL limit door closing force to maximum 150 N.  
**SIL**: 3  
**Rationale**: Safety limit per EN 14752 (Railway applications - bodyside entrance systems)

**SYS-REQ-009**: The system SHALL retry door closing operation maximum 3 times if obstacle prevents closure.  
**SIL**: 2  
**Rationale**: Operational requirement with safety implications

**SYS-REQ-010**: The system SHALL alert the driver if doors fail to close after 3 attempts.  
**SIL**: 2  
**Rationale**: Operational alert for manual intervention

**SYS-REQ-011**: The system SHALL complete door closing within 5.0 seconds from door close command (no obstacles).  
**SIL**: 1  
**Rationale**: Operational performance

#### 2.1.3 Door Locking Control

**SYS-REQ-012**: The system SHALL engage door locks when ALL of the following conditions are met:  
- Doors are fully closed (confirmed by position sensors)
- Door close command completed successfully

**SIL**: 3  
**Rationale**: Prerequisite for safe train movement

**SYS-REQ-013**: The system SHALL maintain door locks engaged when train speed > 5 km/h.  
**SIL**: 3  
**Rationale**: Critical safety function to prevent HAZ-001 and HAZ-004

**SYS-REQ-014**: The system SHALL use redundant locking mechanisms (2oo2) for door lock verification.  
**SIL**: 3  
**Rationale**: High integrity locking verification

**SYS-REQ-015**: The system SHALL only permit door unlocking when train speed ≤ 5 km/h.  
**SIL**: 3  
**Rationale**: Safety interlock to prevent HAZ-004

**SYS-REQ-016**: The system SHALL prevent train movement if any door is not properly locked (except emergency/degraded modes).  
**SIL**: 3  
**Rationale**: System-level safety interlock (interface to traction control)

#### 2.1.4 Emergency Door Release

**SYS-REQ-017**: The system SHALL provide manual emergency door release capability at each door.  
**SIL**: 3  
**Rationale**: Critical safety function for emergency evacuation (HAZ-003)

**SYS-REQ-018**: Emergency door release SHALL be operable by passengers without tools or special knowledge.  
**SIL**: 3  
**Rationale**: Usability requirement for emergency evacuation

**SYS-REQ-019**: Emergency door release SHALL mechanically override electronic door locks.  
**SIL**: 3  
**Rationale**: Independence from electronic system failures

**SYS-REQ-020**: The system SHALL detect emergency door release activation and alert the driver.  
**SIL**: 2  
**Rationale**: Operational alert for driver awareness

**SYS-REQ-021**: Emergency door release SHALL be functional in all system failure modes (including power loss).  
**SIL**: 3  
**Rationale**: Ultimate safety function must be fail-safe

#### 2.1.5 Operational Modes

**SYS-REQ-022**: The system SHALL support the following operational modes:
- **Normal Mode**: Automatic door control with full safety interlocks
- **Manual/Maintenance Mode**: Manual door operation for testing (safety interlocks active)
- **Emergency Evacuation Mode**: Rapid door opening override (speed interlock bypassed, requires authorization)
- **Diagnostic Mode**: System diagnostics and sensor testing
- **Degraded/Fail-Safe Mode**: Limited operation after detected fault

**SIL**: 3 (mode management), 1-3 (mode-specific functions)  
**Rationale**: Comprehensive operational coverage

**SYS-REQ-023**: Mode transitions SHALL require explicit authorization from driver or maintenance personnel.  
**SIL**: 3  
**Rationale**: Prevent unauthorized safety interlock bypass

**SYS-REQ-024**: Emergency Evacuation Mode SHALL only be activated when train is stationary OR speed < 5 km/h AND explicit emergency authorization given.  
**SIL**: 3  
**Rationale**: Controlled override of safety interlocks

#### 2.1.6 Position Monitoring

**SYS-REQ-025**: The system SHALL continuously monitor door position states: Fully Open, Intermediate, Fully Closed, Unknown.  
**SIL**: 3  
**Rationale**: State awareness for safety decisions

**SYS-REQ-026**: The system SHALL use redundant position sensors (minimum 2oo2) for Fully Closed determination.  
**SIL**: 3  
**Rationale**: High integrity position verification

**SYS-REQ-027**: The system SHALL report door position status to the driver control panel and TCMS.  
**SIL**: 2  
**Rationale**: Operational awareness

#### 2.1.7 Fault Detection and Management

**SYS-REQ-028**: The system SHALL continuously monitor for the following fault conditions:
- Position sensor failures
- Obstacle sensor failures
- Motor/actuator failures
- Lock mechanism failures
- Control electronics failures
- Communication failures
- Speed sensor failures

**SIL**: 3  
**Rationale**: Fault detection for safety integrity

**SYS-REQ-029**: The system SHALL detect sensor faults within 100 ms.  
**SIL**: 3  
**Rationale**: Timely fault detection

**SYS-REQ-030**: The system SHALL transition to a safe state upon detection of critical faults:
- Doors locked closed if train moving
- Doors prevented from opening if speed interlock compromised
- Emergency release remains functional

**SIL**: 3  
**Rationale**: Fail-safe behavior per EN 50129

**SYS-REQ-031**: The system SHALL log all fault events with timestamp for maintenance analysis.  
**SIL**: 1  
**Rationale**: Maintainability

### 2.2 Performance Requirements

**SYS-REQ-032**: Door opening time: ≤ 3.0 seconds (from enable command to fully open)  
**SIL**: 1

**SYS-REQ-033**: Door closing time: ≤ 5.0 seconds (from close command to locked, no obstacles)  
**SIL**: 1

**SYS-REQ-034**: Obstacle detection response time: ≤ 200 ms (from obstacle detected to door re-opening)  
**SIL**: 3

**SYS-REQ-035**: System response time for speed interlock: ≤ 50 ms (from speed > 5 km/h to door lock confirmation)  
**SIL**: 3

**SYS-REQ-036**: Control cycle time: ≤ 20 ms (periodic control loop execution)  
**SIL**: 3

**SYS-REQ-037**: Mean Time Between Failures (MTBF): ≥ 50,000 hours  
**SIL**: N/A (Reliability requirement)

**SYS-REQ-038**: Mean Time To Repair (MTTR): ≤ 30 minutes (module replacement)  
**SIL**: N/A (Maintainability requirement)

### 2.3 Interface Requirements

#### 2.3.1 Hardware Interfaces

**SYS-REQ-039**: The system SHALL interface with door motor actuators (24V DC, PWM control, 0-100% duty cycle).  
**SIL**: 3

**SYS-REQ-040**: The system SHALL interface with redundant door position sensors (2x inductive proximity sensors per door).  
**SIL**: 3

**SYS-REQ-041**: The system SHALL interface with obstacle detection sensors (infrared beam, 2x sensors per door).  
**SIL**: 3

**SYS-REQ-042**: The system SHALL interface with door lock actuators (solenoid locks, 24V DC).  
**SIL**: 3

**SYS-REQ-043**: The system SHALL interface with lock position sensors (2x magnetic reed switches per lock).  
**SIL**: 3

**SYS-REQ-044**: The system SHALL interface with emergency release sensors (1x switch per door).  
**SIL**: 2

#### 2.3.2 System Interfaces

**SYS-REQ-045**: The system SHALL interface with Speed Monitoring System via CAN bus (ISO 11898, 250 kbps).  
**SIL**: 3  
**Rationale**: Critical speed data for door interlocks

**SYS-REQ-046**: The system SHALL interface with Train Control Management System (TCMS) via MVB (Multifunction Vehicle Bus, IEC 61375-1).  
**SIL**: 2  
**Rationale**: Operational commands and status

**SYS-REQ-047**: The system SHALL interface with Driver Control Panel via discrete I/O and CAN bus.  
**SIL**: 2  
**Rationale**: Driver commands and status displays

**SYS-REQ-048**: The system SHALL interface with Platform Detection System via discrete inputs.  
**SIL**: 2  
**Rationale**: Platform side identification

#### 2.3.3 User Interfaces

**SYS-REQ-049**: The system SHALL provide visual door status indication on driver control panel (per-door status: open, closed, locked, fault).  
**SIL**: 2

**SYS-REQ-050**: The system SHALL provide audible alerts for fault conditions.  
**SIL**: 1

**SYS-REQ-051**: The system SHALL provide passenger-visible door status indicators (green=open permitted, red=closed/locked).  
**SIL**: 1

### 2.4 Environmental Requirements

**SYS-REQ-052**: The system SHALL operate in temperature range: -40°C to +70°C (EN 50155 Class T1).  
**SIL**: 3

**SYS-REQ-053**: The system SHALL withstand vibration per EN 61373 Category 1 Class B.  
**SIL**: 3

**SYS-REQ-054**: The system SHALL meet EMC requirements per EN 50121-3-2 (Rolling stock).  
**SIL**: 3

**SYS-REQ-055**: The system SHALL operate with power supply: 24V DC nominal (18V - 36V range).  
**SIL**: 3

**SYS-REQ-056**: The system SHALL have IP65 ingress protection rating (EN 60529).  
**SIL**: 2

### 2.5 Safety Requirements

**SYS-REQ-057**: The system SHALL achieve SIL 3 per EN 50129 for door interlock functions (door lock when moving, door open prevention when moving).  
**SIL**: 3

**SYS-REQ-058**: The system SHALL implement diverse redundancy for critical safety functions (2oo2 sensors, diverse processing).  
**SIL**: 3

**SYS-REQ-059**: The system SHALL implement fail-safe behavior: default to doors locked if any critical fault detected.  
**SIL**: 3

**SYS-REQ-060**: The system SHALL have maximum Systematic Capability Level: SC 2 (per EN 50129 Table A.3 for SIL 3).  
**SIL**: 3

**SYS-REQ-061**: The system SHALL implement cyclic redundancy checks (CRC) for all safety-critical data communication.  
**SIL**: 3

**SYS-REQ-062**: The system SHALL implement watchdog timers for processor monitoring (≤ 100 ms timeout).  
**SIL**: 3

### 2.6 Reliability and Availability Requirements

**SYS-REQ-063**: The system SHALL have a target failure rate: λ ≤ 10^-8 per hour (dangerous failures) for SIL 3 functions.  
**SIL**: 3

**SYS-REQ-064**: The system SHALL have diagnostic coverage ≥ 99% for SIL 3 functions.  
**SIL**: 3

**SYS-REQ-065**: The system SHALL have availability ≥ 99.5% (operational availability).  
**Rationale**: Operational requirement for passenger service

**SYS-REQ-066**: The system SHALL support online diagnostics without interrupting normal operation.  
**SIL**: 2

### 2.7 Maintainability Requirements

**SYS-REQ-067**: The system SHALL support modular replacement of control electronics (MTTR ≤ 30 minutes).  
**Rationale**: Maintainability

**SYS-REQ-068**: The system SHALL log diagnostic data for fault analysis (minimum 1000 events).  
**SIL**: 1

**SYS-REQ-069**: The system SHALL provide self-test capability for all sensors and actuators in Diagnostic Mode.  
**SIL**: 2

### 2.8 Security Requirements

**SYS-REQ-070**: The system SHALL prevent unauthorized mode changes (require physical key or authorized digital command).  
**SIL**: 2  
**Rationale**: Security against tampering

**SYS-REQ-071**: The system SHALL log all mode change events with timestamp and authorization source.  
**SIL**: 2

---

## 3. REQUIREMENTS ALLOCATION

### 3.1 Hardware Allocation

The following requirements are allocated to hardware design:
- SYS-REQ-008 (door closing force limit) - mechanical design
- SYS-REQ-017, 019, 021 (emergency release mechanism) - mechanical design
- SYS-REQ-052 to 056 (environmental requirements) - hardware electronics
- Motor drivers, sensor interfaces, power supply

### 3.2 Software Allocation

The following requirements are allocated to software:
- **All control logic** (SYS-REQ-001, 002, 005, 006, 007, 009, 012, 013, 015)
- **Safety interlocks** (SYS-REQ-002, 013, 015, 016)
- **Fault detection** (SYS-REQ-028, 029, 030)
- **Operational modes** (SYS-REQ-022, 023, 024)
- **Position monitoring** (SYS-REQ-025, 027)
- **Communication protocols** (SYS-REQ-045, 046, 047, 048)
- **Diagnostics** (SYS-REQ-069)

See **Software Requirements Specification (DOC-SRS-2026-001)** for detailed software requirements.

### 3.3 Operational Procedures Allocation

The following requirements are allocated to operational procedures:
- Driver training for emergency evacuation mode
- Maintenance procedures for diagnostic mode
- Fault response procedures (SYS-REQ-010)

---

## 4. SYSTEM ARCHITECTURE OVERVIEW

See **System Architecture Description (DOC-SYS-ARCH-2026-001)** for detailed architecture.

**High-Level System Components**:
1. **Door Control Electronics (DCE)** - SIL 3 processing unit
2. **Door Actuator Units** - Motors, locks, sensors per door
3. **Driver Control Interface** - Control panel, displays
4. **Communication Interfaces** - CAN, MVB, discrete I/O
5. **Emergency Release Mechanisms** - Mechanical overrides
6. **Power Supply Unit** - 24V DC distribution

**Hardware/Software Split**:
- **Hardware**: Physical safety mechanisms (locks, emergency release), sensor/actuator interfaces
- **Software**: Control algorithms, safety interlocks, fault detection, mode management

---

## 5. VERIFICATION AND VALIDATION

### 5.1 System Verification

System-level verification SHALL demonstrate compliance with all SYS-REQ-xxx requirements through:
- System design reviews
- Hardware-Software integration testing
- System qualification testing (environmental, EMC, vibration)
- Safety case review

### 5.2 System Validation

System validation SHALL be performed in operational environment:
- Factory acceptance testing (FAT)
- Site acceptance testing (SAT)
- Revenue service trials

### 5.3 Acceptance Criteria

System acceptance requires:
- 100% of SIL 3 requirements verified
- All hazard scenarios tested
- SIL 3 safety integrity demonstrated per EN 50129
- Customer approval

---

## 6. TRACEABILITY

### 6.1 Upstream Traceability

| System Requirement | Source (Hazard / Standard) |
|-------------------|---------------------------|
| SYS-REQ-002, 013, 015, 016 | SYS-HAZ-001 (doors open while moving) |
| SYS-REQ-006, 007, 008 | SYS-HAZ-002 (doors close on passenger) |
| SYS-REQ-017, 018, 019, 021 | SYS-HAZ-003 (emergency evacuation) |
| SYS-REQ-008 | EN 14752 (door force limits) |
| SYS-REQ-057 to 062 | EN 50129 (SIL 3 requirements) |

### 6.2 Downstream Traceability

All system requirements SHALL be traced to:
- **Software Requirements Specification** (DOC-SRS-2026-001)
- **Hardware Requirements Specification** (DOC-HW-REQ-2026-001)
- **System Safety Requirements Specification** (DOC-SYS-SAFE-2026-001)

See Requirements Traceability Matrix (RTM) in project documentation.

---

## 7. REFERENCES

### 7.1 Normative References

- **EN 50128:2011** - Railway applications - Communications, signalling and processing systems - Software for railway control and protection systems
- **EN 50129:2018** - Railway applications - Communication, signalling and processing systems - Safety related electronic systems for signalling
- **EN 50126-1:2017** - Railway applications - The specification and demonstration of Reliability, Availability, Maintainability and Safety (RAMS) - Part 1: Generic RAMS process
- **EN 50126-2:2017** - Railway applications - The specification and demonstration of RAMS - Part 2: Systems approach to safety
- **EN 50155:2017** - Railway applications - Electronic equipment used on rolling stock
- **EN 61373:2010** - Railway applications - Rolling stock equipment - Shock and vibration tests
- **EN 50121-3-2:2016** - Railway applications - Electromagnetic compatibility - Part 3-2: Rolling stock - Apparatus
- **EN 14752:2015** - Railway applications - Bodyside entrance systems

### 7.2 Informative References

- IEC 61508 - Functional Safety of E/E/PE Safety-related Systems
- ISO 26262 - Road vehicles - Functional safety (analogous principles)

---

## 8. GLOSSARY

| Term | Definition |
|------|------------|
| **DCE** | Door Control Electronics - Electronic control unit |
| **TCMS** | Train Control Management System |
| **SIL** | Safety Integrity Level (0-4 per EN 50129) |
| **2oo2** | 2 out of 2 voting (both sensors must agree) |
| **CAN** | Controller Area Network (ISO 11898) |
| **MVB** | Multifunction Vehicle Bus (IEC 61375-1) |
| **PWM** | Pulse Width Modulation |
| **HAZ** | Hazard identifier |
| **MTBF** | Mean Time Between Failures |
| **MTTR** | Mean Time To Repair |

---

## DOCUMENT APPROVAL

This System Requirements Specification is **APPROVED** as the baseline for software and hardware development.

**Baseline Version**: 1.0  
**Baseline Date**: 2026-02-10  
**Configuration Item ID**: CI-SYS-REQ-001  

Any changes to this document SHALL be processed through the Change Control Board (CCB) per project CM procedures.

---

**END OF DOCUMENT**
