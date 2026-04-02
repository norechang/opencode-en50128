# System Requirements Specification

**DOCUMENT TYPE**: System-Level Input Document  
**EN 50128 REFERENCE**: Section 7.2.2 (Input to Software Requirements Specification)  
**STANDARD**: EN 50126-1:2017 (Section 5), EN 50126-2:2017 (Section 5), IEC 62278

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SYS-REQ-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **System SIL Level** | SIL 3 |
| **Author** | System Engineering Team |
| **Status** | Approved - Baseline for Software Development |

---

## VERSION HISTORY

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-03-15 | System Engineer | Initial draft | - |
| 0.5 | 2026-03-22 | System Engineer | Review updates | Technical Lead |
| 1.0 | 2026-04-02 | System Engineer | Approved baseline | Project Manager, Safety Authority |

---

## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **System Engineer** | [PENDING] | [PENDING] | [PENDING] |
| **Safety Manager** | [PENDING] | [PENDING] | [PENDING] |
| **Technical Lead** | [PENDING] | [PENDING] | [PENDING] |
| **Project Manager** | [PENDING] | [PENDING] | [PENDING] |
| **Customer Representative** | [PENDING] | [PENDING] | [PENDING] |

---

## 1. INTRODUCTION

### 1.1 Purpose

This System Requirements Specification (SysRS) defines the complete set of system-level requirements for the **Train Door Control System (TDC)** for passenger railway vehicles. It establishes the baseline requirements that will be allocated to hardware, software, and operational procedures.

This document serves as the **primary input** to:
- Software Requirements Specification (EN 50128 Section 7.2)
- Hardware Requirements Specification
- System Safety Requirements Specification
- System Architecture Description

**EN 50126-1:2017 Reference**: Section 5 specifies the RAMS lifecycle and requirement specification process for railway systems.

### 1.2 Scope

**System**: Train Door Control System (TDCS) for passenger railway vehicles

**System Boundary**: 
- Door Control Unit (DCU) — central processing module
- Door Drive Units (DDU) per door leaf — electromechanical actuators with position sensors
- Obstacle detection sensors (infrared, 2 per door opening)
- Door open/close command inputs from Train Control and Management System (TCMS)
- Speed interlock input from TCMS (train speed signal)
- Door status outputs to TCMS (door locked, door open, door fault)
- Local door open buttons (platform side and cab side)
- Emergency door release mechanism (passive, manual)

**Operational Environment**:
- Electric multiple units (EMU), metro, suburban rail
- Operating temperature: -25°C to +55°C (operational), -40°C to +70°C (storage)
- Humidity: 5% to 95% (non-condensing)
- Voltage: 24V DC nominal (18V - 32V range)
- Train speed range: 0–200 km/h (system active only at ≤ 5 km/h for door operations)
- EMC environment: EN 50121-3-2 (Rolling stock)
- Vibration: EN 61373 Category 1 Class B

### 1.3 System Context

The Train Door Control System is a safety-critical subsystem of the overall train control and protection system. It interfaces with:

- **Train Control Management System (TCMS)**: Operational commands, status reporting
- **Speed Monitoring System**: Train speed for door interlocks
- **Driver Control Panel**: Manual door control, status displays
- **Passenger Emergency Interfaces**: Emergency door release handles
- **Door Hardware**: Motors, locks, position sensors, obstacle sensors
- **Platform Screen Doors (PSD)**: Door open/close commands (where fitted)
- **Vehicle diagnostic system**: Fault logs via TCMS

**EN 50126-2:2017 Reference**: Section 5 defines the systems approach to safety and hazard analysis methodology.

### 1.4 System SIL Classification

**System SIL Level**: **SIL 3** (Safety Integrity Level 3)

**Rationale** (per EN 50126-2 hazard analysis):

| Hazard ID | Hazard Description | Consequence | Severity | Frequency | Risk Level | SIL |
|-----------|-------------------|-------------|----------|-----------|------------|-----|
| HAZ-001 | Train departs with door open or not fully locked | Passenger fall from train → Fatalities | Catastrophic | Occasional | Intolerable | **SIL 3** |
| HAZ-002 | Door closes on passenger causing entrapment injury | Passenger trapped/crushed → Serious injury | Critical | Frequent | Intolerable | **SIL 3** |
| HAZ-003 | Door opens while train is moving above 5 km/h | Passenger fall from train → Fatality | Catastrophic | Remote | Intolerable | **SIL 3** |
| HAZ-004 | Obstacle detected but door continues to close | Passenger crushed → Serious injury | Critical | Occasional | Intolerable | **SIL 3** |
| HAZ-005 | False door-locked signal allows train departure with door ajar | Passenger fall → Fatality | Catastrophic | Occasional | Intolerable | **SIL 3** |
| HAZ-006 | Door fails to open at station (passenger trapped) | Passenger trapped → Minor injury/disruption | Marginal | Frequent | Tolerable (ALARP) | **SIL 2** |
| HAZ-007 | Door fails to close at end of dwell time (service disruption) | Service delay | Marginal | Occasional | Tolerable (ALARP) | **SIL 1** |
| HAZ-008 | Emergency door release triggers during normal operation | Spurious door opening → Injury | Critical | Remote | Tolerable (ALARP) | **SIL 2** |
| HAZ-009 | DCU software fault leads to loss of all door control | Loss of door control → Injury | Critical | Remote | Tolerable (ALARP) | **SIL 2** |

**Highest SIL**: SIL 3 (driven by HAZ-001, HAZ-002, HAZ-003, HAZ-004, HAZ-005)

---

## 2. SYSTEM REQUIREMENTS

### 2.1 Functional Requirements

#### 2.1.1 Door Opening Control

**SYS-REQ-001**: The system SHALL open all doors on the commanded side when commanded by TCMS and train speed ≤ 5 km/h.  
**SIL**: 3  
**Rationale**: Basic operational function with safety interlock

**SYS-REQ-002**: The system SHALL only permit door opening when ALL of the following conditions are met:  
- Train speed ≤ 5 km/h
- Door open command received from TCMS OR local door open button pressed
- No door fault conditions present  
**SIL**: 3  
**Rationale**: Safety interlock to prevent HAZ-003 (doors opening while moving)

**SYS-REQ-003**: The system SHALL complete door opening within 3.0 seconds from door enable command (door command to first motor movement ≤ 200 ms).  
**SIL**: 1  
**Rationale**: Operational performance requirement

**SYS-REQ-004**: The system SHALL detect door fully open position using redundant position sensors (2oo2).  
**SIL**: 3  
**Rationale**: Confirmation of safe state

#### 2.1.2 Door Closing Control

**SYS-REQ-005**: The system SHALL close and lock all doors when commanded by TCMS.  
**SIL**: 3  
**Rationale**: Basic operational function

**SYS-REQ-006**: The system SHALL detect obstacles during door closing operation using obstacle detection sensors (2 per door opening).  
**SIL**: 3  
**Rationale**: Safety function to prevent HAZ-002, HAZ-004 (doors closing on passengers)

**SYS-REQ-007**: The system SHALL automatically reverse door motion if obstacle is detected during closing (obstacle detected → motor reversal within 150 ms).  
**SIL**: 3  
**Rationale**: Safety response to HAZ-002, HAZ-004

**SYS-REQ-008**: The system SHALL limit door closing force to maximum 150 N (per EN 14752).  
**SIL**: 3  
**Rationale**: Safety limit per EN 14752 (Railway applications - bodyside entrance systems)

**SYS-REQ-009**: The system SHALL retry door closing operation maximum 3 times if obstacle prevents closure.  
**SIL**: 2  
**Rationale**: Operational requirement with safety implications

**SYS-REQ-010**: The system SHALL alert the driver if doors fail to close after 3 attempts.  
**SIL**: 2  
**Rationale**: Operational alert for manual intervention

**SYS-REQ-011**: The system SHALL complete door close-and-lock sequence within 8 seconds under nominal conditions (no obstacles).  
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
**Rationale**: Critical safety function to prevent HAZ-001, HAZ-003

**SYS-REQ-014**: The system SHALL confirm door lock status via independent sensor channel (2oo2 voting).  
**SIL**: 3  
**Rationale**: High integrity locking verification per HAZ-001, HAZ-005

**SYS-REQ-015**: The system SHALL only permit door unlocking when train speed ≤ 5 km/h.  
**SIL**: 3  
**Rationale**: Safety interlock to prevent HAZ-003

**SYS-REQ-016**: The system SHALL withhold door-locked signal to TCMS until all doors confirmed locked (prevent train departure if any door is not fully locked).  
**SIL**: 3  
**Rationale**: System-level safety interlock (interface to traction control) per HAZ-001, HAZ-005

**SYS-REQ-017**: The system SHALL transmit door-locked status to TCMS within 100 ms of lock confirmation.  
**SIL**: 3  
**Rationale**: Timely departure interlock signal

#### 2.1.4 Emergency Door Release

**SYS-REQ-018**: The system SHALL provide manual emergency door release capability at each door (allow manual emergency door release from inside the saloon).  
**SIL**: 3  
**Rationale**: Critical safety function for emergency evacuation

**SYS-REQ-019**: Emergency door release SHALL be operable by passengers without tools or special knowledge.  
**SIL**: 3  
**Rationale**: Usability requirement for emergency evacuation

**SYS-REQ-020**: Emergency door release SHALL mechanically override electronic door locks.  
**SIL**: 3  
**Rationale**: Independence from electronic system failures

**SYS-REQ-021**: The system SHALL detect emergency door release activation and alert the driver.  
**SIL**: 2  
**Rationale**: Operational alert for driver awareness per HAZ-008

**SYS-REQ-022**: Emergency door release SHALL be functional in all system failure modes (including power loss).  
**SIL**: 3  
**Rationale**: Ultimate safety function must be fail-safe

#### 2.1.5 Operational Modes

**SYS-REQ-023**: The system SHALL support the following operational modes:
- **Normal Mode**: Automatic door control with full safety interlocks
- **Selective Door Disablement Mode**: Isolate one defective door and maintain operation of remaining doors
- **Diagnostic Mode**: System diagnostics and sensor testing
- **Safe State Mode**: Command all doors to locked state on system fault  
**SIL**: 3 (mode management), 1-3 (mode-specific functions)  
**Rationale**: Comprehensive operational coverage per HAZ-009

**SYS-REQ-024**: Mode transitions SHALL require explicit authorization from driver or maintenance personnel.  
**SIL**: 3  
**Rationale**: Prevent unauthorized safety interlock bypass

#### 2.1.6 Position Monitoring

**SYS-REQ-025**: The system SHALL continuously monitor door position states: Fully Open, Intermediate, Fully Closed, Unknown.  
**SIL**: 3  
**Rationale**: State awareness for safety decisions

**SYS-REQ-026**: The system SHALL use redundant position sensors (minimum 2oo2) for Fully Closed determination.  
**SIL**: 3  
**Rationale**: High integrity position verification per HAZ-001, HAZ-005

**SYS-REQ-027**: The system SHALL transmit individual door fault status to TCMS for each defective door.  
**SIL**: 2  
**Rationale**: Operational awareness

#### 2.1.7 Fault Detection and Management

**SYS-REQ-028**: The system SHALL continuously monitor for the following fault conditions:
- Position sensor failures
- Obstacle sensor failures
- Motor/actuator failures
- Lock mechanism failures
- Control electronics failures
- Communication failures (TCMS interface)
- Speed sensor failures (from TCMS)  
**SIL**: 3  
**Rationale**: Fault detection for safety integrity per HAZ-005, HAZ-009

**SYS-REQ-029**: The system SHALL detect sensor faults within 100 ms.  
**SIL**: 3  
**Rationale**: Timely fault detection

**SYS-REQ-030**: The system SHALL transition to a safe state upon detection of critical faults:
- Doors locked closed if train moving
- Doors prevented from opening if speed interlock compromised
- Emergency release remains functional  
**SIL**: 3  
**Rationale**: Fail-safe behavior per EN 50129 (HAZ-009)

**SYS-REQ-031**: The system SHALL log all door events with timestamps for diagnostic purposes (minimum 1000 events in non-volatile storage).  
**SIL**: 1  
**Rationale**: Maintainability

### 2.2 Performance Requirements

**SYS-REQ-032**: Door opening time: ≤ 3.0 seconds (from enable command to fully open)  
**SIL**: 1

**SYS-REQ-033**: Door closing time: ≤ 8.0 seconds (from close command to locked, no obstacles)  
**SIL**: 1

**SYS-REQ-034**: Obstacle detection response time: ≤ 150 ms (from obstacle detected to door reversal)  
**SIL**: 3

**SYS-REQ-035**: System response time for speed interlock: ≤ 100 ms (from speed > 5 km/h to door lock confirmation)  
**SIL**: 3

**SYS-REQ-036**: Control cycle time: ≤ 20 ms (periodic control loop execution)  
**SIL**: 3

**SYS-REQ-037**: Mean Time Between Failures (MTBF): ≥ 200,000 hours for the DCU  
**SIL**: N/A (Reliability requirement)

**SYS-REQ-038**: Mean Time To Repair (MTTR): ≤ 4 hours (module replacement with standard railway maintenance tools)  
**SIL**: N/A (Maintainability requirement)

**SYS-REQ-039**: System availability: ≥ 99.9% per 24-hour period  
**SIL**: N/A (Availability requirement)

### 2.3 Interface Requirements

#### 2.3.1 Hardware Interfaces

**SYS-REQ-040**: The system SHALL interface with door motor actuators (24V DC, PWM control).  
**SIL**: 3

**SYS-REQ-041**: The system SHALL interface with redundant door position sensors (2x inductive proximity sensors or equivalent per door).  
**SIL**: 3

**SYS-REQ-042**: The system SHALL interface with obstacle detection sensors (infrared beam, 2x sensors per door opening).  
**SIL**: 3

**SYS-REQ-043**: The system SHALL interface with door lock actuators (solenoid locks or equivalent, 24V DC).  
**SIL**: 3

**SYS-REQ-044**: The system SHALL interface with lock position sensors (2x sensors per lock - 2oo2).  
**SIL**: 3

**SYS-REQ-045**: The system SHALL interface with emergency release sensors (1x switch per door).  
**SIL**: 2

#### 2.3.2 System Interfaces

**SYS-REQ-046**: The system SHALL interface with Train Control Management System (TCMS) via CAN bus (CAN 2.0B, ISO 11898, 250 kbit/s).  
**SIL**: 3  
**Rationale**: Critical speed data and command interface

**SYS-REQ-047**: The system SHALL receive speed signal from TCMS with update rate 100 ms period (10 Hz).  
**SIL**: 3  
**Rationale**: Timely speed data for door interlocks

**SYS-REQ-048**: The system SHALL interface with Driver Control Panel via discrete I/O or CAN bus.  
**SIL**: 2  
**Rationale**: Driver commands and status displays

**SYS-REQ-049**: The system SHALL interface with Door Drive Units (DDU) via proprietary RS-485 at 115.2 kbit/s.  
**SIL**: 3  
**Rationale**: Drive commands, position feedback per door

**SYS-REQ-050**: The system SHALL support diagnostics port via USB/RS-232 at 115.2 kbit/s.  
**SIL**: 1  
**Rationale**: Maintenance laptop access

#### 2.3.3 User Interfaces

**SYS-REQ-051**: The system SHALL provide visual door status indication on driver control panel (per-door status: open, closed, locked, fault).  
**SIL**: 2

**SYS-REQ-052**: The system SHALL provide audible alerts for fault conditions.  
**SIL**: 1

**SYS-REQ-053**: The system SHALL provide passenger-visible door status indicators (green=open permitted, red=closed/locked).  
**SIL**: 1

### 2.4 Environmental Requirements

**SYS-REQ-054**: The system SHALL operate in temperature range: -25°C to +55°C (operational), -40°C to +70°C (storage).  
**SIL**: 3

**SYS-REQ-055**: The system SHALL withstand vibration per EN 61373 Category 1 Class B.  
**SIL**: 3

**SYS-REQ-056**: The system SHALL meet EMC requirements per EN 50121-3-2 (Rolling stock emissions and immunity).  
**SIL**: 3

**SYS-REQ-057**: The system SHALL operate with power supply: 24V DC nominal (18V - 32V range).  
**SIL**: 3

**SYS-REQ-058**: The system SHALL operate in humidity: 5% to 95% (non-condensing).  
**SIL**: 2

### 2.5 Safety Requirements

**SYS-REQ-059**: The system SHALL achieve SIL 3 per EN 50129 for door interlock functions (door lock when moving, door open prevention when moving).  
**SIL**: 3

**SYS-REQ-060**: The system SHALL implement diverse redundancy for critical safety functions (2oo2 sensors, dual-channel processing where applicable).  
**SIL**: 3

**SYS-REQ-061**: The system SHALL implement fail-safe behavior: default to doors locked if any critical fault detected.  
**SIL**: 3

**SYS-REQ-062**: The system SHALL have Probability of Failure per Hour (PFH) ≤ 10^-7 per hour (SIL 3 per IEC 61508 Table 2).  
**SIL**: 3

**SYS-REQ-063**: The system SHALL implement cyclic redundancy checks (CRC) for all safety-critical data communication.  
**SIL**: 3

**SYS-REQ-064**: The system SHALL implement watchdog timers for processor monitoring (watchdog timeout ≤ 50 ms → safe state).  
**SIL**: 3

### 2.6 Reliability and Availability Requirements

**SYS-REQ-065**: The system SHALL have a target failure rate: PFH ≤ 10^-7 per hour (dangerous failures) for SIL 3 functions.  
**SIL**: 3

**SYS-REQ-066**: The system SHALL have diagnostic coverage ≥ 99% for SIL 3 functions.  
**SIL**: 3

**SYS-REQ-067**: The system SHALL have availability ≥ 99.9% (operational availability per 24-hour period).  
**Rationale**: Operational requirement for passenger service

**SYS-REQ-068**: The system SHALL support online diagnostics without interrupting normal operation.  
**SIL**: 2

### 2.7 Maintainability Requirements

**SYS-REQ-069**: The system SHALL support modular replacement of control electronics (MTTR ≤ 4 hours with standard railway maintenance tools).  
**Rationale**: Maintainability

**SYS-REQ-070**: The system SHALL log diagnostic data for fault analysis (minimum 1000 events in non-volatile storage).  
**SIL**: 1

**SYS-REQ-071**: The system SHALL provide self-test capability for all sensors and actuators in Diagnostic Mode.  
**SIL**: 2

**SYS-REQ-072**: The system SHALL have service life ≥ 30 years with scheduled maintenance.  
**Rationale**: Railway equipment lifecycle requirement

### 2.8 Security Requirements

**SYS-REQ-073**: The system SHALL prevent unauthorized mode changes (require physical key or authorized digital command).  
**SIL**: 2  
**Rationale**: Security against tampering

**SYS-REQ-074**: The system SHALL log all mode change events with timestamp and authorization source.  
**SIL**: 2

---

## 3. REQUIREMENTS ALLOCATION

### 3.1 Hardware Allocation

The following requirements are allocated to hardware design:
- SYS-REQ-008 (door closing force limit) - mechanical design
- SYS-REQ-018, 020, 022 (emergency release mechanism) - mechanical design
- SYS-REQ-054 to 058 (environmental requirements) - hardware electronics
- Motor drivers, sensor interfaces, power supply
- DCU hardware: STM32H743 (or equivalent) dual microcontroller module

### 3.2 Software Allocation

The following requirements are allocated to software:
- **All control logic** (SYS-REQ-001, 002, 005, 006, 007, 009, 012, 013, 015)
- **Safety interlocks** (SYS-REQ-002, 013, 015, 016)
- **Fault detection** (SYS-REQ-028, 029, 030)
- **Operational modes** (SYS-REQ-023, 024)
- **Position monitoring** (SYS-REQ-025, 027)
- **Communication protocols** (SYS-REQ-046, 047, 048, 049)
- **Diagnostics** (SYS-REQ-071)

**Software Components**:
- Door State Machine (DSM): main control logic, state-based door sequencing
- Speed Monitor (SPM): reads speed from TCMS, enforces interlock
- Obstacle Detector (OBD): processes obstacle sensor inputs, triggers reversal
- TCMS Interface (TCI): CAN bus driver, message encoding/decoding
- Fault Manager (FMG): fault detection, safe state management, fault log
- Diagnostics (DGN): event logging, diagnostic data reporting
- Hardware Abstraction Layer (HAL): GPIO, ADC, CAN, SPI drivers

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
1. **Door Control Unit (DCU)** - SIL 3 dual-channel processing module
2. **Door Drive Units (DDU)** - Motors, locks, sensors per door
3. **Driver Control Interface** - Control panel, displays
4. **Communication Interfaces** - CAN, RS-485, discrete I/O
5. **Emergency Release Mechanisms** - Mechanical overrides
6. **Power Supply Unit** - 24V DC distribution

**Processing Architecture**:
- Dual-channel (2oo2) DCU with independent CPUs running identical software
- Each channel independently monitors all sensor inputs and computes outputs
- Outputs compared by cross-channel monitor before actuation
- Disagreement between channels → safe state transition

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
- All hazard scenarios tested (HAZ-001 through HAZ-009)
- SIL 3 safety integrity demonstrated per EN 50129
- Customer approval
- EN 50129 Safety Case required; EN 50128 SIL 3 for software

---

## 6. TRACEABILITY

### 6.1 Upstream Traceability

| System Requirement | Source (Hazard / Standard) |
|-------------------|---------------------------|
| SYS-REQ-002, 013, 015, 016 | HAZ-001, HAZ-003, HAZ-005 (doors open while moving, false locked signal) |
| SYS-REQ-006, 007, 008 | HAZ-002, HAZ-004 (doors close on passenger) |
| SYS-REQ-018, 019, 020, 022 | Emergency evacuation requirements |
| SYS-REQ-008 | EN 14752 (door force limits) |
| SYS-REQ-059 to 064 | EN 50129 (SIL 3 requirements) |
| SYS-REQ-023 | HAZ-006, HAZ-009 (fault isolation) |

### 6.2 Downstream Traceability

All system requirements SHALL be traced to:
- **Software Requirements Specification** (DOC-SRS-2026-001)
- **Hardware Requirements Specification** (DOC-HW-REQ-2026-001)
- **System Safety Requirements Specification** (DOC-SYS-SAF-2026-001)

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
- **EN 13272** - Railway applications - Electrical lighting for rolling stock in public transport systems
- **IEC 61508** - Functional Safety of E/E/PE Safety-related Systems
- **ISO 11898** - Controller Area Network (CAN)

### 7.2 Informative References

- ISO 26262 - Road vehicles - Functional safety (analogous principles)

---

## 8. GLOSSARY

| Term | Definition |
|------|------------|
| **DCU** | Door Control Unit — central processing module |
| **DDU** | Door Drive Unit — per-door electromechanical actuator module |
| **TCMS** | Train Control Management System — train-level supervisory system |
| **SIL** | Safety Integrity Level (0-4 per EN 50129) |
| **2oo2** | Two-out-of-two voting — both channels/sensors must agree |
| **CAN** | Controller Area Network (ISO 11898) |
| **PWM** | Pulse Width Modulation |
| **HAZ** | Hazard identifier |
| **PFH** | Probability of Failure per Hour — SIL integrity measure |
| **MTBF** | Mean Time Between Failures |
| **MTTR** | Mean Time To Repair |
| **ALARP** | As Low As Reasonably Practicable |

---

## DOCUMENT APPROVAL

This System Requirements Specification is **APPROVED** as the baseline for software and hardware development.

**Baseline Version**: 1.0  
**Baseline Date**: 2026-04-02  
**Configuration Item ID**: CI-SYS-REQ-001  

Any changes to this document SHALL be processed through the Change Control Board (CCB) per project CM procedures.

---

**END OF DOCUMENT**
