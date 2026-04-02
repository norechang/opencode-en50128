# System Architecture Description

**DOCUMENT TYPE**: System-Level Input Document  
**EN 50128 REFERENCE**: Section 7.2.2 (Input to Software Requirements Specification)  
**STANDARD**: EN 50126-1:2017 (Section 6), EN 50126-2:2017 (Section 6.4), EN 50129:2018, IEC 62278

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SYS-ARCH-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **System SIL Level** | SIL 3 |
| **Author** | System Architecture Team |
| **Status** | Approved - Baseline for Software Architecture |

---

## VERSION HISTORY

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-03-15 | System Architect | Initial architecture draft | - |
| 0.5 | 2026-03-22 | System Architect | Review updates, safety architecture | Technical Lead, Safety Manager |
| 1.0 | 2026-04-02 | System Architect | Approved baseline | Project Manager, Chief Engineer |

---

## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **System Architect** | [PENDING] | [PENDING] | [PENDING] |
| **Safety Manager** | [PENDING] | [PENDING] | [PENDING] |
| **Hardware Lead** | [PENDING] | [PENDING] | [PENDING] |
| **Software Lead** | [PENDING] | [PENDING] | [PENDING] |
| **Project Manager** | [PENDING] | [PENDING] | [PENDING] |

---

## 1. INTRODUCTION

### 1.1 Purpose

This System Architecture Description (SAD) defines the overall architecture of the **Train Door Control System (TDC)**, including:
- System decomposition into hardware and software subsystems
- Component interfaces and interactions
- Hardware/software allocation
- Safety architecture and redundancy strategy
- Physical and logical architecture views

This document serves as the **primary architectural input** to:
- Software Architecture Specification (EN 50128 Section 7.3)
- Hardware Design Specification
- Interface Control Documents (ICDs)

**EN 50126-1:2017 Reference**: Section 6 specifies the system design and architecture requirements for RAMS.

**EN 50126-2:2017 Reference**: Section 6.4 defines the safety architecture design principles.

### 1.2 Scope

This SAD describes the complete system architecture for the Train Door Control System (TDC), covering:
- High-level system decomposition
- Hardware architecture (processing units, sensors, actuators, interfaces)
- Software architecture overview (detailed in Software Architecture Specification)
- Safety architecture (redundancy, fault tolerance, fail-safe mechanisms)
- Communication architecture
- Physical deployment

**Architectural Constraints**:
- SIL 3 safety integrity requirements per EN 50129
- Railway environmental requirements (EN 50155, EN 61373)
- Real-time control requirements (20 ms cycle time)
- Distributed system architecture (multiple door control units per train)

### 1.3 Architectural Drivers

The system architecture is driven by:

1. **Safety Requirements** (SIL 3):
   - Redundancy for critical functions (2oo2 sensors, dual-channel processing)
   - Fail-safe behavior (doors locked on fault, mechanical emergency release)
   - Fault detection and diagnostics (DC ≥ 99%)

2. **Performance Requirements**:
   - Real-time control (20 ms cycle, 100 ms response time for speed interlock)
   - Door operation timing (open ≤ 3s, close ≤ 8s)

3. **Reliability Requirements**:
   - MTBF ≥ 200,000 hours
   - Modular design for easy maintenance (MTTR ≤ 4 hours)

4. **Environmental Requirements**:
   - Temperature: -25°C to +55°C (operational), -40°C to +70°C (storage)
   - Vibration: EN 61373 Category 1 Class B
   - EMC: EN 50121-3-2

5. **Operational Requirements**:
   - Multi-door control (left/right sides, multiple doors per side)
   - Multiple operational modes (Normal, Selective Disablement, Diagnostic, Safe State)
   - Integration with Train Control and Management System (TCMS)

---

## 2. SYSTEM ARCHITECTURE OVERVIEW

### 2.1 System Context Diagram

```
┌─────────────────────────────────────────────────────────────────────────┐
│                         EXTERNAL SYSTEMS                                │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌──────────────┐    ┌─────────────────┐    ┌──────────────────┐      │
│  │   Driver     │    │  Train Control  │    │  Platform Screen │      │
│  │   Control    │    │  and Management │    │  Doors (PSD)     │      │
│  │   Panel      │───▶│  System (TCMS)  │    │  (where fitted)  │      │
│  └──────────────┘    └─────────────────┘    └──────────────────┘      │
│         │                     │                       │                │
│         │ Discrete I/O        │ CAN 2.0B              │ Discrete I/O   │
│         │ + CAN               │ 250 kbit/s            │                │
│         ▼                     ▼                       ▼                │
│  ┌─────────────────────────────────────────────────────────────┐      │
│  │                                                               │      │
│  │           TRAIN DOOR CONTROL SYSTEM (Target System)          │      │
│  │                        TDC / TDCS                            │      │
│  │                                                               │      │
│  │  ┌────────────────────────────────────────────────────┐     │      │
│  │  │  Door Control Unit (DCU) - SIL 3                   │     │      │
│  │  │  - Dual-channel processing (2oo2 for safety)      │     │      │
│  │  │  - Safety logic + Application logic                │     │      │
│  │  │  - Fault detection and diagnostics                 │     │      │
│  │  │  - STM32H743 dual microcontroller (400 MHz)       │     │      │
│  │  └────────────────────────────────────────────────────┘     │      │
│  │                           │                                  │      │
│  │                           │ RS-485 + Discrete I/O, PWM       │      │
│  │                           ▼                                  │      │
│  │  ┌────────────────────────────────────────────────────┐     │      │
│  │  │  Door Drive Units (DDU) - per door                 │     │      │
│  │  │  - DC motor drivers                                │     │      │
│  │  │  - Lock actuators                                  │     │      │
│  │  │  - Position sensors (2x per door - 2oo2)           │     │      │
│  │  │  - Obstacle sensors (2x IR per door)               │     │      │
│  │  │  - Lock sensors (2x per lock - 2oo2)               │     │      │
│  │  │  - Emergency release (mechanical)                  │     │      │
│  │  └────────────────────────────────────────────────────┘     │      │
│  └───────────────────────────────────────────────────────────────┘      │
│                                                                         │
│  ┌──────────────┐    ┌─────────────────┐                               │
│  │  Vehicle     │    │  Passenger      │                               │
│  │  Diagnostic  │    │  Emergency      │                               │
│  │  System      │    │  Interfaces     │                               │
│  └──────────────┘    └─────────────────┘                               │
│         │                     │                                        │
│         │ USB/RS-232          │ Discrete I/O                           │
│         └─────────────────────┘                                        │
└─────────────────────────────────────────────────────────────────────────┘
```

### 2.2 System Decomposition

The Train Door Control System is decomposed into the following major subsystems:

| Subsystem | Description | SIL | Implementation |
|-----------|-------------|-----|----------------|
| **Door Control Unit (DCU)** | Central dual-channel processing unit with safety logic | SIL 3 | Hardware + Software |
| **Door Drive Units (DDU)** | Electromechanical actuators, motors, locks, sensors per door | SIL 3 | Hardware |
| **Communication Interfaces** | CAN, RS-485, discrete I/O interfaces | SIL 2-3 | Hardware + Software |
| **Power Supply Unit (PSU)** | 24V DC power distribution with monitoring | SIL 2 | Hardware |
| **Emergency Release Mechanisms** | Mechanical passive door release per door | SIL 3 | Hardware (mechanical) |

---

## 3. HARDWARE ARCHITECTURE

### 3.1 Hardware Block Diagram

```
┌─────────────────────────────────────────────────────────────────────────┐
│                     DOOR CONTROL UNIT (DCU)                             │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌──────────────────────────────────────────────────────────────┐      │
│  │              DUAL-CHANNEL PROCESSING (2oo2)                  │      │
│  │              STM32H743 dual microcontroller                  │      │
│  │                                                               │      │
│  │  ┌────────────────────┐         ┌────────────────────┐       │      │
│  │  │  Processing        │         │  Processing        │       │      │
│  │  │  Channel A         │◀───────▶│  Channel B         │       │      │
│  │  │                    │  Cross-  │                    │       │      │
│  │  │  - MCU-A           │  Check   │  - MCU-B           │       │      │
│  │  │  - 400 MHz         │  SPI     │  - 400 MHz         │       │      │
│  │  │  - 1 MB SRAM       │  10 Mbit │  - 1 MB SRAM       │       │      │
│  │  │  - Safety Logic    │          │  - Safety Logic    │       │      │
│  │  │  - Watchdog 50 ms  │          │  - Watchdog 50 ms  │       │      │
│  │  └────────────────────┘         └────────────────────┘       │      │
│  │           │                              │                    │      │
│  └───────────┼──────────────────────────────┼────────────────────┘      │
│              │                              │                           │
│  ┌───────────┴──────────────────────────────┴───────────────────┐      │
│  │                   I/O INTERFACE MODULE                        │      │
│  │  - Digital Inputs (sensors, switches - 24V logic)            │      │
│  │  - Digital Outputs (lock actuators - 24V)                    │      │
│  │  - PWM Outputs (motor control - 20 kHz)                      │      │
│  │  - Analog Inputs (current monitoring, 0-10V)                 │      │
│  └────────────────────────────────────────────────────────────────┘      │
│              │                                                          │
│  ┌───────────┴──────────────────────────────────────────────────┐      │
│  │               COMMUNICATION INTERFACE MODULE                  │      │
│  │  - CAN Controller x2 (redundant - 250 kbit/s)                │      │
│  │  - RS-485 Transceiver (115.2 kbit/s to DDU)                  │      │
│  │  - USB/RS-232 (diagnostics - 115.2 kbit/s)                   │      │
│  │  - Discrete I/O for driver panel                              │      │
│  └────────────────────────────────────────────────────────────────┘      │
│              │                                                          │
│  ┌───────────┴──────────────────────────────────────────────────┐      │
│  │                   POWER SUPPLY MODULE                         │      │
│  │  - 24V DC input (18-32V range)                                │      │
│  │  - Isolated 5V/3.3V for MCUs                                  │      │
│  │  - Voltage monitoring                                         │      │
│  │  - Over-current protection                                    │      │
│  └────────────────────────────────────────────────────────────────┘      │
│              │                                                          │
│  ┌───────────┴──────────────────────────────────────────────────┐      │
│  │             NON-VOLATILE STORAGE                              │      │
│  │  - SPI Flash 16 MB (event log, configuration)                 │      │
│  │  - CRC protection for stored data                             │      │
│  └────────────────────────────────────────────────────────────────┘      │
└─────────────────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌─────────────────────────────────────────────────────────────────────────┐
│              DOOR DRIVE UNIT (DDU) - per door (4-8 typical)             │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌────────────────────┐   ┌────────────────────┐                       │
│  │  Door Motor        │   │  Door Lock         │                       │
│  │  - 24V DC motor    │   │  - Solenoid lock   │                       │
│  │  - PWM control     │   │  - Fail-closed     │                       │
│  │  - Encoder         │   │  - Spring-loaded   │                       │
│  │  - Current monitor │   │  - 24V actuation   │                       │
│  └────────────────────┘   └────────────────────┘                       │
│                                                                         │
│  ┌───────────────────────────────────────────────────────────┐         │
│  │  Position Sensors (2x per door - 2oo2)                    │         │
│  │  - Sensor A: Inductive proximity (fully open/closed)      │         │
│  │  - Sensor B: Inductive proximity (fully open/closed)      │         │
│  │  - End-stop switches                                       │         │
│  └───────────────────────────────────────────────────────────┘         │
│                                                                         │
│  ┌───────────────────────────────────────────────────────────┐         │
│  │  Obstacle Sensors (2x per door - redundant)               │         │
│  │  - Sensor A: Infrared beam transmitter/receiver           │         │
│  │  - Sensor B: Infrared beam transmitter/receiver           │         │
│  │  - 24V GPIO interrupt-driven                               │         │
│  └───────────────────────────────────────────────────────────┘         │
│                                                                         │
│  ┌───────────────────────────────────────────────────────────┐         │
│  │  Lock Position Sensors (2x per lock - 2oo2)               │         │
│  │  - Sensor A: Magnetic reed switch (locked/unlocked)       │         │
│  │  - Sensor B: Magnetic reed switch (locked/unlocked)       │         │
│  └───────────────────────────────────────────────────────────┘         │
│                                                                         │
│  ┌───────────────────────────────────────────────────────────┐         │
│  │  Emergency Release Mechanism (mechanical - passive)        │         │
│  │  - Manual pull handle (passenger-operable)                 │         │
│  │  - Mechanical lock override (independent of electronics)   │         │
│  │  - Release detection switch                                │         │
│  └───────────────────────────────────────────────────────────┘         │
└─────────────────────────────────────────────────────────────────────────┘
```

### 3.2 Hardware Components

#### 3.2.1 Door Control Unit (DCU)

**Component**: Door Control Unit (DCU)  
**Description**: Central dual-channel processing unit with SIL 3 safety integrity

**Specifications**:
- **Processing**: Dual STM32H743 microcontrollers (or equivalent)
  - Channel A: Primary safety logic + application logic
  - Channel B: Redundant safety logic + cross-check
  - Cross-channel communication via SPI (10 Mbps)
- **Clock**: 400 MHz ARM Cortex-M7
- **Memory**:
  - SRAM: 1 MB per MCU (all static allocation, no heap)
  - Flash: 2 MB per MCU (code + configuration)
  - External SPI Flash: 16 MB (event log, configuration backup with CRC)
- **Watchdog**: Independent hardware watchdog per MCU (50 ms timeout)
- **Power**: 24V DC input (18-32V range), isolated 5V/3.3V internal supplies
- **Operating Temperature**: -25°C to +55°C (operational), -40°C to +70°C (storage)
- **Enclosure**: IP65-rated aluminum housing
- **Dimensions**: 250mm x 200mm x 100mm (rack-mountable under-floor)
- **Weight**: ~2.0 kg

**Safety Features**:
- 2oo2 processing for safety-critical functions
- Memory protection (MPU) for code/data separation
- CRC on flash memory (boot-time verification)
- Voltage and temperature monitoring
- Fail-safe power-down sequence

#### 3.2.2 Door Drive Units (DDU)

**Component**: Door Motor Assembly  
**Type**: 24V DC brushless motor with gearbox and encoder  
**Specifications**:
- Torque: 10 Nm nominal, 15 Nm peak
- Speed: Variable 0-100% via PWM (20 kHz)
- Current: 5A nominal, 8A peak
- Position feedback: Integrated encoder + end-stop switches
- Mechanical force limit: 150 N (per EN 14752)

**Component**: Door Lock Actuator  
**Type**: 24V DC solenoid lock (fail-closed)  
**Specifications**:
- Locking force: 500 N holding force
- Actuation time: < 100 ms
- Fail-safe: Spring-loaded (locked without power)
- Lock verification: 2x magnetic reed switches (2oo2)

**Component**: Position Sensors (2x per door)  
**Type**: Inductive proximity sensors + end-stop switches  
**Specifications**:
- Detection range: 5 mm
- Output: 24V logic (interrupt-driven)
- Response time: < 5 ms
- Mounting: One at fully-open position, one at fully-closed position

**Component**: Obstacle Detection Sensors (2x per door)  
**Type**: Infrared beam transmitter/receiver pairs  
**Specifications**:
- Detection range: Up to 1.5 m (door width)
- Response time: < 50 ms
- Output: 24V GPIO (interrupt-driven)
- Alignment: Horizontal beam across door opening at 0.3m and 1.0m heights

**Component**: Emergency Release Mechanism  
**Type**: Mechanical pull handle with lock override (passive)  
**Specifications**:
- Actuation force: 50-100 N (operable by passengers)
- Mechanical advantage: Direct mechanical link to lock mechanism
- Independence: No electrical or electronic components in release path
- Detection: Microswitch for release event logging

### 3.3 Hardware Interface Specifications

#### 3.3.1 External Communication Interfaces

**CAN Bus Interface** (TCMS):
- **Protocol**: CAN 2.0B (ISO 11898)
- **Bit Rate**: 250 kbit/s
- **Termination**: 120Ω at each end
- **Messages**:
  - RX: Speed data (100 ms period / 10 Hz, CRC-16), door commands
  - TX: Door status, door-locked signal (100 ms after lock), fault codes
- **Connector**: 9-pin D-sub or M12 circular
- **SIL Level**: SIL 3 (speed data critical for door interlocks)

**RS-485 Interface** (DDU):
- **Protocol**: Proprietary RS-485 multi-drop
- **Bit Rate**: 115.2 kbit/s
- **Purpose**: Drive commands, position feedback per door
- **Connector**: Screw terminals or M12 circular
- **SIL Level**: SIL 3 (door position critical)

**Discrete I/O** (Driver Control Panel):
- **Inputs**: 8x digital inputs (24V logic, opto-isolated)
  - Door open button (left/right)
  - Door close button (left/right)
  - Mode selection switches
- **Outputs**: 16x digital outputs (24V, 500 mA per channel)
  - Door status indicators (per door)
  - Fault indicators
  - Audible alarms

**USB/RS-232** (Diagnostics):
- **Bit Rate**: 115.2 kbit/s
- **Purpose**: Maintenance laptop access, event log download
- **Connector**: USB Type-B or 9-pin D-sub
- **SIL Level**: SIL 1 (diagnostics only)

#### 3.3.2 Internal Interfaces (DCU to DDU)

**Door Motor Control**:
- **Signal**: PWM output (20 kHz, 0-100% duty cycle)
- **Voltage**: 24V DC
- **Current Monitoring**: Analog input 0-10V (proportional to motor current)
- **Wiring**: Shielded twisted pair, max length 15m

**Lock Actuator Control**:
- **Signal**: Digital output (24V, 1A)
- **Feedback**: 2x digital inputs (lock position sensors A and B - 2oo2)
- **Wiring**: Shielded cable, max length 15m

**Position Sensors**:
- **Signal**: Digital inputs (24V logic, interrupt-driven)
- **Channels**: 2x inputs per door (fully open, fully closed)
- **Wiring**: Shielded twisted pair per sensor

**Obstacle Sensors**:
- **Signal**: Digital inputs (24V GPIO, interrupt-driven)
- **Channels**: 2x inputs per door (obstacle A, obstacle B)
- **Wiring**: Shielded twisted pair per sensor

---

## 4. SOFTWARE ARCHITECTURE OVERVIEW

**Note**: Detailed software architecture is specified in **Software Architecture Specification (DOC-SAS-2026-001)**. This section provides system-level context for software allocation.

### 4.1 Software Decomposition

The software is structured into the following major components:

| Software Component | Description | SIL | Execution |
|-------------------|-------------|-----|-----------|
| **Safety Kernel** | Safety-critical control logic (speed interlock, lock control, safe state) | SIL 3 | Both channels (2oo2) |
| **Door State Machine (DSM)** | Main control logic, state-based door sequencing | SIL 3 | Both channels |
| **Speed Monitor (SPM)** | Reads speed from TCMS, enforces interlock | SIL 3 | Both channels |
| **Obstacle Detector (OBD)** | Processes obstacle sensor inputs, triggers reversal within 150 ms | SIL 3 | Both channels |
| **TCMS Interface (TCI)** | CAN bus driver, message encoding/decoding | SIL 3 | Both channels |
| **Fault Manager (FMG)** | Fault detection, safe state management, fault log | SIL 3 | Both channels |
| **Diagnostics (DGN)** | Event logging, diagnostic data reporting | SIL 1 | Channel A (primary) |
| **Hardware Abstraction Layer (HAL)** | GPIO, ADC, CAN, SPI, RS-485 drivers | SIL 3 | Both channels |

### 4.2 Software Deployment

Software is deployed on dual-channel processing:

```
┌─────────────────────────────────────────────────────────────────┐
│                       SOFTWARE DEPLOYMENT                       │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  ┌──────────────────────┐         ┌──────────────────────┐     │
│  │   Channel A (MCU-A)  │         │   Channel B (MCU-B)  │     │
│  ├──────────────────────┤         ├──────────────────────┤     │
│  │ Safety Kernel        │◀───────▶│ Safety Kernel        │     │
│  │ Door State Machine   │  Cross  │ (Safety only)        │     │
│  │ Speed Monitor        │  Check  │ Speed Monitor        │     │
│  │ Obstacle Detector    │  SPI    │ Obstacle Detector    │     │
│  │ TCMS Interface       │  10Mbit │ TCMS Interface       │     │
│  │ Fault Manager        │         │ Fault Manager        │     │
│  │ Diagnostics          │         │ (minimal)            │     │
│  │ HAL                  │         │ HAL                  │     │
│  └──────────────────────┘         └──────────────────────┘     │
│           │                                │                    │
│           └────────────┬───────────────────┘                    │
│                        ▼                                        │
│              Hardware I/O (sensors/actuators)                   │
└─────────────────────────────────────────────────────────────────┘
```

**Software Voting**: 2oo2 voting for safety-critical outputs (door lock commands, door open inhibit)

### 4.3 Software Execution Model

- **Control Cycle**: 20 ms periodic execution (50 Hz)
- **Scheduler**: Static cyclic executive (time-triggered, no RTOS overhead)
- **Safety Cycle**: Safety logic executed every cycle with cross-channel comparison
- **Timing Budget**:
  - Safety logic: 5 ms max
  - Door state machine: 6 ms max
  - Communication (CAN, RS-485): 3 ms max
  - Diagnostics: 2 ms max
  - Margin: 4 ms

**Key Timing Requirements**:
- Speed signal update rate from TCMS: 100 ms period (10 Hz)
- Door command → first motor movement: ≤ 200 ms
- Obstacle detected → motor reversal: ≤ 150 ms
- Door position confirmed → TCMS status update: ≤ 100 ms
- Watchdog timeout (no software heartbeat): 50 ms → safe state

---

## 5. SAFETY ARCHITECTURE

### 5.1 Safety Principles

The system safety architecture implements the following principles per EN 50126-2:

1. **Redundancy**: 2oo2 voting for critical sensors and dual-channel processing
2. **Diversity**: Diverse sensor types where feasible (inductive + magnetic)
3. **Fail-Safe**: Default to safe state (doors locked) on fault detection
4. **Independence**: Mechanical emergency release independent of electronics
5. **Fault Detection**: Comprehensive diagnostics (DC ≥ 99%)

### 5.2 Redundancy Architecture

**Processing Redundancy** (2oo2):
- Dual STM32H743 microcontrollers (Channel A and Channel B)
- Both channels execute safety logic independently
- Cross-channel communication via SPI for comparison (every 20 ms cycle)
- Disagreement → Safe state (doors locked, open inhibited)

**Sensor Redundancy** (2oo2):
- Door position sensors: 2x per door (both must agree for "fully closed")
- Lock position sensors: 2x per lock (both must agree for "locked")
- Obstacle sensors: 2x per door (either sensor triggers re-opening)
- Speed sensors: Redundant CAN sources from TCMS

**Actuator Independence**:
- Door locks: Fail-closed (spring-loaded, default locked without power)
- Emergency release: Mechanical override (independent path)

### 5.3 Fault Detection Coverage

Target diagnostic coverage: **DC ≥ 99%** (per EN 50129 for SIL 3)

| Fault Class | Detection Method | Detection Time | Coverage |
|-------------|------------------|----------------|----------|
| **MCU failure** | Watchdog timeout (50 ms), cross-channel comparison | ≤ 50 ms | 99% |
| **Sensor failure** | Sensor plausibility checks, 2oo2 disagreement | ≤ 100 ms | 98% |
| **Actuator failure** | Feedback monitoring (lock sensors, motor current) | ≤ 200 ms | 95% |
| **Communication failure** | CRC errors, timeout detection (200 ms) | ≤ 200 ms | 99% |
| **Memory corruption** | CRC checks (flash, RAM), MPU violations | ≤ 1 cycle (20 ms) | 99% |
| **Power supply fault** | Voltage monitoring (under/over voltage) | ≤ 50 ms | 100% |

**Overall Diagnostic Coverage**: ~98-99% (meets SIL 3 requirement)

### 5.4 Safe States

| Fault Condition | Safe State Response | Rationale |
|----------------|---------------------|-----------|
| **Speed sensor failure** | Assume "train moving", lock doors, inhibit opening | Conservative assumption |
| **Position sensor failure** | Assume "door not closed", inhibit train movement | Prevent movement with unverified door state |
| **Lock sensor failure** | Assume "not locked", inhibit train movement | Conservative assumption |
| **MCU failure (either channel)** | Lock doors (via hardware fail-safe), inhibit opening | Electronics failure → mechanical safety |
| **Communication loss (TCMS)** | Assume "train moving", lock doors | Loss of critical interlock data |
| **Power loss** | Locks fail-closed (spring-loaded), emergency release remains functional | Mechanical fail-safe |
| **Watchdog timeout** | Trigger safe state within 50 ms | Software hang detection |

### 5.5 Safety-Critical Functions Allocation

| Safety Function | Hardware | Software | Fail-Safe Mechanism |
|----------------|----------|----------|---------------------|
| **Door opening interlock** (SF-001) | Redundant speed sensors (TCMS), dual processing | Safety Kernel (2oo2) | Default deny door opening |
| **Departure interlock** (SF-002) | Spring-loaded locks, 2oo2 lock sensors | Safety Kernel (2oo2) | Fail-closed locks |
| **Obstacle detection and reversal** (SF-003) | 2x IR sensors, force limiter | Obstacle Detector (SIL 3) | Hardware force limit 150N |
| **Safe state on fault** (SF-004) | Watchdog, power monitor | Fault Manager (2oo2) | Locks fail-closed |
| **Door position verification** (SF-005) | 2x inductive sensors per door | Safety Kernel (2oo2) | Conservative assumption on fault |
| **Emergency release** | Mechanical override (passive) | None (mechanical) | Direct mechanical link |

---

## 6. COMMUNICATION ARCHITECTURE

### 6.1 External Communication Network

```
                   ┌───────────────────────────────┐
                   │  Train Control Management     │
                   │  System (TCMS)                │
                   └───────────┬───────────────────┘
                               │ CAN 2.0B (ISO 11898)
                               │ 250 kbit/s
                   ┌───────────▼───────────────────┐
                   │  Door Control Unit (DCU)      │
                   │  Dual-channel processing      │
                   └───────┬───────────┬───────────┘
                           │           │
        RS-485 115.2 kbit  │           │ Discrete I/O
        (DDU control)      │           │ + CAN
                           │           │
     ┌─────────────────────▼─┐    ┌───▼─────────────────┐
     │  Door Drive Units     │    │  Driver Control     │
     │  (DDU) x 4-8          │    │  Panel              │
     └───────────────────────┘    └─────────────────────┘
```

### 6.2 Internal Communication

**Cross-Channel Communication** (Channel A ↔ Channel B):
- **Protocol**: SPI (Serial Peripheral Interface)
- **Speed**: 10 Mbps
- **Data**: Safety-critical variables (speed, door state, lock state, fault flags)
- **CRC**: CRC-16 on all messages
- **Cycle**: Every 20 ms (synchronized with control cycle)

### 6.3 Communication Safety Measures

- **CRC Protection**: CRC-16 on all safety-critical messages (TCMS, cross-channel)
- **Timeout Detection**: Missing messages detected within 2x cycle time (200 ms)
- **Sequence Counters**: Detect lost or duplicated messages
- **Fail-Safe Default**: On communication loss, assume worst-case (train moving, doors not closed)

---

## 7. PHYSICAL ARCHITECTURE

### 7.1 Physical Deployment

**Typical Train Configuration**:
- 4-8 doors per side (left and right) = 8-16 doors total per car
- 1x Door Control Unit (DCU) per car (centralized, under-floor)
- 8-16x Door Drive Units (DDU) - one per door
- Cable harness from DCU to each door (max 15m)

**Installation Locations**:
- **DCU**: Under-floor equipment bay (protected environment, IP65)
- **Door Drive Units**: Integrated into door frame
- **Emergency Release**: Interior passenger area (clearly marked, accessible)

### 7.2 Wiring Architecture

```
                      ┌─────────────────────┐
                      │  DCU (Under-floor)  │
                      └──┬──┬──┬──┬──┬──┬───┘
                         │  │  │  │  │  │
          ┌──────────────┘  │  │  │  │  └────────────┐
          │     ┌───────────┘  │  │  └─────────┐     │
          │     │     ┌────────┘  └────────┐   │     │
          │     │     │     ┌──────────┐   │   │     │
          ▼     ▼     ▼     ▼          ▼   ▼   ▼     ▼
        Door  Door  Door  Door       Door Door Door Door
        L1    L2    L3    L4         R1   R2   R3   R4
       (Left Side)                  (Right Side)
```

**Cable Specifications**:
- Shielded twisted pair (STP) for all signal cables
- 24V DC power distribution (separate power cables)
- Connectors: M12 circular connectors (IP67 rated) or equivalent
- Maximum cable length: 15m (DCU to furthest door)

---

## 8. HARDWARE/SOFTWARE INTERFACE

### 8.1 Hardware Abstraction Layer (HAL)

The software interfaces with hardware through a Hardware Abstraction Layer (HAL) that provides:
- **GPIO**: Digital input/output for sensors, actuators (24V logic)
- **PWM**: Motor speed control (20 kHz)
- **ADC**: Analog-to-digital conversion for current monitoring
- **CAN**: CAN bus driver (transmit/receive, 250 kbit/s)
- **RS-485**: RS-485 interface driver (115.2 kbit/s)
- **SPI**: Cross-channel communication (10 Mbps)
- **Timers**: Periodic interrupt for 20ms control cycle
- **Watchdog**: Hardware watchdog refresh (50 ms timeout)

**HAL API** (example):
```c
// Digital I/O
uint8_t HAL_GPIO_ReadPin(GPIO_Port port, uint8_t pin);
void HAL_GPIO_WritePin(GPIO_Port port, uint8_t pin, uint8_t value);

// PWM
void HAL_PWM_SetDutyCycle(PWM_Channel channel, uint8_t duty_percent);

// CAN
error_t HAL_CAN_Transmit(CAN_Message* msg);
error_t HAL_CAN_Receive(CAN_Message* msg);

// Watchdog
void HAL_Watchdog_Refresh(void);
```

### 8.2 Memory Map

**MCU Flash Memory** (2 MB per STM32H743):
- 0x08000000 - 0x0801FFFF: Bootloader (128 KB)
- 0x08020000 - 0x081FFFFF: Application code (1920 KB)

**MCU SRAM** (1 MB per STM32H743):
- 0x20000000 - 0x2007FFFF: Stack (512 KB)
- 0x20080000 - 0x200FFFFF: Global variables (512 KB)
- No heap allocation (malloc/free forbidden per MISRA C:2012 and SIL 3 requirements)

**External SPI Flash** (16 MB):
- Event log (circular buffer, 1000+ events)
- Configuration data (door parameters, calibration)
- CRC-16 protection for all stored data

---

## 9. OPERATIONAL MODES

The system supports the following operational modes (managed by software):

| Mode | Description | Speed Interlock | Use Case |
|------|-------------|-----------------|----------|
| **Normal** | Automatic door control with full interlocks | Active | Revenue service |
| **Selective Door Disablement** | Isolate one defective door, maintain operation of others | Active | Service with partial door fault |
| **Diagnostic** | System diagnostics and sensor testing | Active | Maintenance testing |
| **Safe State** | Command all doors to locked state on system fault | Active | Fault response |

**Mode Transitions**: Controlled by software, require authorization (driver key or TCMS command)

---

## 10. INTERFACE CONTROL DOCUMENTS (ICDs)

The following Interface Control Documents define detailed interface specifications:

| ICD | Description | Status |
|-----|-------------|--------|
| **ICD-001** | DCU to TCMS (CAN interface, speed signal, commands, status) | Approved |
| **ICD-002** | DCU to Door Drive Units (RS-485 interface) | Approved |
| **ICD-003** | DCU to Driver Control Panel (Discrete I/O + CAN) | Approved |
| **ICD-004** | DCU Internal (Cross-channel SPI communication) | Approved |
| **ICD-005** | DCU to Diagnostics Port (USB/RS-232) | Approved |

**ICD Location**: `docs/interfaces/`

---

## 11. DESIGN RATIONALE

### 11.1 Architectural Decisions

| Decision | Rationale |
|----------|-----------|
| **Dual-channel processing (2oo2)** | Achieves SIL 3 hardware fault tolerance (HFT=1) per EN 50129 |
| **Centralized DCU per car** | Reduces wiring complexity, simplifies maintenance (modular replacement) |
| **Fail-closed locks** | Mechanical fail-safe ensures doors locked on power loss |
| **Mechanical emergency release** | Independence from electronics ensures reliability in all failure modes |
| **Static memory allocation** | Eliminates heap fragmentation risks, meets EN 50128 SIL 3 recommendations |
| **20 ms control cycle** | Balance between responsiveness (100 ms speed interlock) and processing margin |
| **CAN for TCMS interface** | Standard railway bus, deterministic timing, suitable for SIL 3 with CRC |
| **Redundant obstacle sensors** | Improves reliability, either sensor can trigger safety response |
| **STM32H743 (400 MHz)** | High-performance MCU suitable for real-time control with sufficient margin |

### 11.2 Trade-offs

| Trade-off | Decision | Justification |
|-----------|----------|---------------|
| **Centralized vs. Distributed DCU** | Centralized (1 DCU per car) | Simpler configuration management, easier maintenance, lower cost |
| **Single vs. Dual channel processing** | Dual channel (2oo2) | Required for SIL 3, provides fault tolerance |
| **Hardware vs. Software force limit** | Both (hardware mechanical limit + software current limit) | Defense in depth |
| **CAN vs. proprietary protocol for TCMS** | CAN | Widely supported, simpler for safety data with CRC |

---

## 12. TRACEABILITY

### 12.1 System Requirements to Architecture Allocation

| System Requirement | Architectural Component | Implementation |
|-------------------|------------------------|----------------|
| SYS-REQ-001 to SYS-REQ-017 (Door control) | DCU + DDU | Software + Hardware |
| SYS-REQ-018 to SYS-REQ-022 (Emergency release) | Emergency Release Mechanism | Hardware (mechanical) |
| SYS-REQ-023 to SYS-REQ-024 (Operational modes) | Software (Mode Management) | Software |
| SYS-REQ-025 to SYS-REQ-027 (Position monitoring) | Position Sensors + Software | Hardware + Software |
| SYS-REQ-028 to SYS-REQ-031 (Fault detection) | Fault Manager (Software) | Software |
| SYS-REQ-046 to SYS-REQ-050 (System interfaces) | Communication Interfaces | Hardware + Software |

### 12.2 Safety Requirements to Architecture Allocation

| Safety Function | Architectural Component | SIL |
|----------------|------------------------|-----|
| SF-001 (Door opening interlock) | Dual-channel processing + Speed sensors (TCMS) | SIL 3 |
| SF-002 (Departure interlock) | Fail-closed locks + 2oo2 lock sensors | SIL 3 |
| SF-003 (Obstacle detection) | Redundant IR sensors + Software | SIL 3 |
| SF-004 (Safe state) | Fault Manager + Watchdog + Locks | SIL 3 |
| SF-005 (Door closed verification) | 2oo2 position sensors + Software | SIL 3 |
| Emergency release | Mechanical release mechanism | SIL 3 |

---

## 13. REFERENCES

### 13.1 Normative References

- **EN 50129:2018** - Railway applications - Safety related electronic systems for signalling
- **EN 50128:2011** - Railway applications - Software for railway control and protection systems
- **EN 50126-1:2017** - Railway applications - The specification and demonstration of Reliability, Availability, Maintainability and Safety (RAMS) - Part 1: Generic RAMS process
- **EN 50126-2:2017** - Railway applications - The specification and demonstration of RAMS - Part 2: Systems approach to safety
- **EN 50155:2017** - Railway applications - Electronic equipment used on rolling stock
- **EN 61373:2010** - Railway applications - Rolling stock equipment - Shock and vibration tests
- **EN 50121-3-2:2016** - Railway applications - Electromagnetic compatibility - Part 3-2: Rolling stock - Apparatus
- **EN 14752:2015** - Railway applications - Bodyside entrance systems
- **ISO 11898:2003** - Controller area network (CAN)
- **IEC 61508** - Functional Safety of E/E/PE Safety-related Systems

### 13.2 Project References

- **System Requirements Specification** (DOC-SYS-REQ-2026-001)
- **System Safety Requirements Specification** (DOC-SYS-SAF-2026-001)
- **Software Architecture Specification** (DOC-SAS-2026-001) [To be developed]
- **Hardware Design Specification** (DOC-HW-DES-2026-001) [To be developed]
- **Interface Control Documents** (ICD-001 to ICD-005)

---

## DOCUMENT APPROVAL

This System Architecture Description is **APPROVED** as the architectural baseline for software and hardware design.

**Baseline Version**: 1.0  
**Baseline Date**: 2026-04-02  
**Configuration Item ID**: CI-SYS-ARCH-001  

Any changes to system architecture SHALL be processed through the Change Control Board (CCB) with architecture review.

---

**END OF DOCUMENT**
