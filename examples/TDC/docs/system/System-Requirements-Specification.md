# System Requirements Specification

## Document Control

| Property | Value |
|----------|-------|
| **Document ID** | DOC-TDC-SRS-SYS-001 |
| **Project** | TDC — Train Door Control |
| **System** | Train Door Control System (TDCS) |
| **Version** | 1.0 |
| **Status** | APPROVED — System Input |
| **Date** | 2026-03-27 |
| **Prepared by** | COD (generate-system) |
| **Standard** | EN 50128:2011, EN 50126:2017, EN 50129:2018 |
| **SIL Level** | SIL 3 |

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| System Engineer | TBD | ___________ | 2026-03-27 |
| Safety Authority | TBD | ___________ | — |

---

## 1. Introduction

### 1.1 Purpose

This System Requirements Specification (SRS) defines the system-level functional and non-functional requirements for the Train Door Control System (TDCS) as deployed on electric multiple unit (EMU), metro, and suburban rail vehicles. It serves as the primary input for the Software Requirements Specification (SRS) produced in EN 50128 Phase 2.

### 1.2 Scope

The TDCS is a safety-critical electronic system responsible for controlling and monitoring the passenger door system of a railway vehicle. The system is classified at **SIL 3** in accordance with EN 50126:2017 risk analysis. The software component shall comply with **EN 50128:2011** at SIL 3.

### 1.3 Applicable Documents

| Reference | Document | Version |
|-----------|----------|---------|
| [1] | EN 50128:2011 — Railway Software Standard | 2011 |
| [2] | EN 50129:2018 — Safety-Related Electronic Systems for Signalling | 2018 |
| [3] | EN 50126:2017 — RAMS (Part 1 & 2) | 2017 |
| [4] | EN 13272 — Railway applications — Doors for passenger rolling stock | Current |
| [5] | IEC 61508 — Functional Safety | 2010 |
| [6] | EN 61373 — Railway applications — Shock and vibration | Current |
| [7] | EN 50121-3-2 — EMC — Railway applications — Rolling stock | Current |

### 1.4 Definitions and Abbreviations

| Term | Definition |
|------|-----------|
| DCU | Door Control Unit — central processing module |
| DDU | Door Drive Unit — per-door electromechanical actuator |
| TCMS | Train Control and Management System |
| 2oo2 | Two-out-of-two voting |
| PFH | Probability of Failure per Hour |
| HAZ | Hazard |
| SF | Safety Function |
| MTBF | Mean Time Between Failures |
| MTTR | Mean Time To Repair |
| SIL | Safety Integrity Level |
| TDCS | Train Door Control System |

---

## 2. System Overview

### 2.1 System Description

The Train Door Control System (TDCS) controls the opening, closing, locking, and monitoring of all passenger doors on a railway vehicle. It receives commands from the Train Control and Management System (TCMS) and enforces safety interlocks to prevent unsafe door operations.

The system operates as a **dual-channel (2oo2)** architecture to achieve the required SIL 3 safety integrity level.

### 2.2 Operational Environment

| Parameter | Value |
|-----------|-------|
| Ambient temperature (operational) | -25°C to +55°C |
| Ambient temperature (storage) | -40°C to +70°C |
| Humidity | 5% to 95% (non-condensing) |
| Vibration | EN 61373 Category 1 Class B |
| EMC | EN 50121-3-2 |
| Power supply | 24 VDC nominal (18–32 VDC range) from train battery |
| Train speed range | 0–200 km/h (door operations permitted only at ≤ 5 km/h) |
| Deployment | EMU, metro, suburban rail |

### 2.3 System Boundary

**Inside the system boundary:**
- Door Control Unit (DCU) — central processing module
- Door Drive Units (DDU) per door leaf — electromechanical actuators with position sensors
- Obstacle detection sensors (infrared, 2 per door opening)
- Door open/close command inputs from TCMS
- Speed interlock input from TCMS (train speed signal)
- Door status outputs to TCMS (door locked, door open, door fault)
- Local door open buttons (platform side and cab side)
- Emergency door release mechanism (passive, manual)

**Outside the system boundary (interfaces only):**
- TCMS — provides speed, commands, receives status
- Driver Desk Display Unit — receives door status summary
- Platform Screen Doors (PSD) — receives door open/close commands (where fitted)
- Vehicle diagnostic system — receives fault logs via TCMS
- Wayside ATP — no direct interface; speed interlock sourced from TCMS

---

## 3. Hazard Analysis

### 3.1 Identified Hazards

| ID | Hazard Description | Severity | Frequency | Risk Level | SIL Allocation |
|----|-------------------|----------|-----------|------------|----------------|
| HAZ-001 | Train departs with door open or not fully locked | Catastrophic | Occasional | Intolerable | **SIL 3** |
| HAZ-002 | Door closes on passenger causing entrapment injury | Critical | Frequent | Intolerable | **SIL 3** |
| HAZ-003 | Door opens while train is moving above 5 km/h | Catastrophic | Remote | Intolerable | **SIL 3** |
| HAZ-004 | Obstacle detected but door continues to close | Critical | Occasional | Intolerable | **SIL 3** |
| HAZ-005 | False door-locked signal allows departure with door ajar | Catastrophic | Occasional | Intolerable | **SIL 3** |
| HAZ-006 | Door fails to open at station (passenger trapped) | Marginal | Frequent | Tolerable (ALARP) | SIL 2 |
| HAZ-007 | Door fails to close at end of dwell time | Marginal | Occasional | Tolerable (ALARP) | SIL 1 |
| HAZ-008 | Emergency release triggers during normal operation | Critical | Remote | Tolerable (ALARP) | SIL 2 |
| HAZ-009 | DCU software fault — loss of all door control | Critical | Remote | Tolerable (ALARP) | SIL 2 |

### 3.2 SIL Determination Basis

Severity and frequency categories are per EN 50126:2017 risk matrix:
- **Catastrophic**: Multiple fatalities possible
- **Critical**: Single fatality or serious injuries possible
- **Marginal**: Minor injuries or service disruption

HAZ-001 through HAZ-005 are the primary drivers for the **SIL 3** system classification.

---

## 4. System Functional Requirements

### 4.1 Door Operation

| ID | Requirement | Priority |
|----|-------------|----------|
| SYS-FR-001 | The system SHALL open all doors on the commanded side when commanded by TCMS and train speed ≤ 5 km/h | HIGH |
| SYS-FR-002 | The system SHALL close and lock all doors when commanded by TCMS | HIGH |
| SYS-FR-012 | The system SHALL complete door close-and-lock sequence within 8 seconds under nominal conditions | HIGH |

### 4.2 Safety Interlocks

| ID | Requirement | Priority |
|----|-------------|----------|
| SYS-FR-003 | The system SHALL prevent door opening when train speed > 5 km/h | **SAFETY-CRITICAL** |
| SYS-FR-004 | The system SHALL prevent train departure authority if any door is not fully locked | **SAFETY-CRITICAL** |

### 4.3 Obstacle Detection

| ID | Requirement | Priority |
|----|-------------|----------|
| SYS-FR-005 | The system SHALL detect obstacles in the door opening and reverse door motion within 150 ms | **SAFETY-CRITICAL** |

### 4.4 Status and Fault Reporting

| ID | Requirement | Priority |
|----|-------------|----------|
| SYS-FR-006 | The system SHALL transmit door-locked status to TCMS within 100 ms of lock confirmation | HIGH |
| SYS-FR-007 | The system SHALL transmit individual door fault status to TCMS for each defective door | HIGH |

### 4.5 Emergency and Maintenance

| ID | Requirement | Priority |
|----|-------------|----------|
| SYS-FR-008 | The system SHALL allow manual emergency door release from inside the saloon | HIGH |
| SYS-FR-009 | The system SHALL support selective door disablement (isolate one defective door) | MEDIUM |

### 4.6 Fault Handling

| ID | Requirement | Priority |
|----|-------------|----------|
| SYS-FR-011 | The system SHALL command the safe state (doors locked, no active drive) on any internal fault | **SAFETY-CRITICAL** |

### 4.7 Diagnostics

| ID | Requirement | Priority |
|----|-------------|----------|
| SYS-FR-010 | The system SHALL log all door events with timestamps for diagnostic purposes | MEDIUM |

---

## 5. System Safety Functions

| ID | Safety Function | SIL | Derived From Hazard(s) |
|----|----------------|-----|------------------------|
| SF-001 | **Speed Interlock**: Inhibit door open command when train speed > 5 km/h | SIL 3 | HAZ-003 |
| SF-002 | **Departure Interlock**: Withhold door-locked signal until all doors confirmed locked | SIL 3 | HAZ-001, HAZ-005 |
| SF-003 | **Obstacle Detection and Reversal**: Detect and respond to obstacle within 150 ms | SIL 3 | HAZ-002, HAZ-004 |
| SF-004 | **Safe State**: Command all doors to locked state on system fault | SIL 3 | HAZ-005, HAZ-009 |
| SF-005 | **Door Position Verification**: Confirm door lock status via independent sensor channel | SIL 3 | HAZ-001, HAZ-005 |
| SF-006 | **Emergency Release Monitoring**: Detect and report emergency release activation | SIL 2 | HAZ-008 |
| SF-007 | **Fault Isolation**: Isolate defective door; maintain operation of remaining doors | SIL 2 | HAZ-009 |

---

## 6. System Architecture

### 6.1 Processing Architecture

- **Dual-channel (2oo2) DCU** with independent CPUs running identical software
- Each channel independently monitors all sensor inputs and computes outputs
- Outputs compared by cross-channel monitor before actuation
- Channel disagreement triggers immediate safe state transition

### 6.2 Hardware Components

| Component | Description |
|-----------|-------------|
| DCU | STM32H743 (or equivalent) dual microcontroller module, 400 MHz, 1 MB SRAM |
| DDU | Per-door electromechanical drive with DC motor, encoder, end-stop switches |
| Obstacle sensors | Infrared beam pairs, 2 per door opening (redundant) |
| Power supply | 24 VDC primary; 5 V/3.3 V DC-DC converters; watchdog circuit |
| Storage | SPI flash 16 MB for event log |

### 6.3 Software Components

| Component | Abbreviation | Description |
|-----------|-------------|-------------|
| Door State Machine | DSM | Main control logic; state-based door sequencing |
| Speed Monitor | SPM | Reads speed from TCMS; enforces interlock |
| Obstacle Detector | OBD | Processes obstacle sensor inputs; triggers reversal |
| TCMS Interface | TCI | CAN bus driver; message encoding/decoding |
| Fault Manager | FMG | Fault detection; safe state management; fault log |
| Diagnostics | DGN | Event logging; diagnostic data reporting |
| Hardware Abstraction Layer | HAL | GPIO, ADC, CAN, SPI drivers |

---

## 7. Communication Interfaces

| Interface | Protocol | Data Rate | Purpose |
|-----------|----------|-----------|---------|
| TCMS ↔ DCU | CAN 2.0B (ISO 11898) | 250 kbit/s | Speed signal, door commands, door status |
| DCU ↔ DDU | Proprietary RS-485 | 115.2 kbit/s | Drive commands, position feedback per door |
| DCU ↔ Obstacle Sensors | Digital GPIO (24 V) | N/A (interrupt-driven) | Obstacle detect/clear |
| DCU Channel A ↔ Channel B | SPI cross-link | 10 Mbit/s | Cross-channel comparison data |
| DCU ↔ Diagnostics port | USB/RS-232 | 115.2 kbit/s | Maintenance laptop access |

### 7.1 Key Timing Requirements

| Parameter | Value |
|-----------|-------|
| Speed signal update rate from TCMS | 100 ms period (10 Hz) |
| Door command → first motor movement | ≤ 200 ms |
| Obstacle detected → motor reversal | ≤ 150 ms |
| Door position confirmed → TCMS status update | ≤ 100 ms |
| Watchdog timeout (no software heartbeat) | 50 ms → safe state |

---

## 8. Non-Functional Requirements

| Category | ID | Requirement |
|----------|----|-------------|
| Reliability | SYS-NFR-001 | MTBF ≥ 200,000 hours for the DCU |
| Availability | SYS-NFR-002 | System availability ≥ 99.9% per 24-hour period |
| Maintainability | SYS-NFR-003 | MTTR ≤ 4 hours with standard railway maintenance tools |
| Safety Integrity | SYS-NFR-004 | PFH ≤ 10⁻⁷ per hour (SIL 3 per IEC 61508 Table 2) |
| Response Time | SYS-NFR-005 | End-to-end command-to-locked response ≤ 8 seconds |
| Service Life | SYS-NFR-006 | ≥ 30 years with scheduled maintenance |
| Certifiability | SYS-NFR-007 | EN 50129 Safety Case required; EN 50128 SIL 3 for software |

---

## 9. Design Constraints

| ID | Constraint |
|----|-----------|
| DC-001 | Software implemented in C; MISRA C:2012 mandatory |
| DC-002 | No dynamic memory allocation (static allocation only) |
| DC-003 | Cyclomatic complexity ≤ 10 per function |
| DC-004 | 100% statement, branch, and condition (MC/DC) coverage required |
| DC-005 | Software independence: Verifier and Validator must be independent of development team |
| DC-006 | Hardware qualification: EN 50155 for railway electronic equipment |
| DC-007 | No recursion permitted in safety-critical code paths |
| DC-008 | All external inputs validated before use |

---

## 10. Traceability Summary

| System Requirement | Safety Function | SIL | Hazard(s) |
|-------------------|----------------|-----|-----------|
| SYS-FR-001, SYS-FR-002 | SF-002 (Departure Interlock) | SIL 3 | HAZ-001, HAZ-005 |
| SYS-FR-003 | SF-001 (Speed Interlock) | SIL 3 | HAZ-003 |
| SYS-FR-004 | SF-002 (Departure Interlock) | SIL 3 | HAZ-001, HAZ-005 |
| SYS-FR-005 | SF-003 (Obstacle Detection) | SIL 3 | HAZ-002, HAZ-004 |
| SYS-FR-006 | SF-005 (Position Verification) | SIL 3 | HAZ-001, HAZ-005 |
| SYS-FR-011 | SF-004 (Safe State) | SIL 3 | HAZ-005, HAZ-009 |
| SYS-FR-008 | SF-006 (Emergency Release) | SIL 2 | HAZ-008 |
| SYS-FR-009 | SF-007 (Fault Isolation) | SIL 2 | HAZ-009 |

---

*End of Document — DOC-TDC-SRS-SYS-001 v1.0*
