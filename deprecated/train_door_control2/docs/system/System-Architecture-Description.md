# System Architecture Description

**DOCUMENT TYPE**: System-Level Input Document  
**EN 50128 REFERENCE**: Section 7.2.2 (Input to Software Requirements Specification)  
**STANDARD**: EN 50129:2018, IEC 62278

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SYS-ARCH-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-02-21 |
| **Project** | Train Door Control System (train_door_control2) |
| **System SIL Level** | SIL 3 |
| **Author** | System Architecture Team |
| **Status** | Approved - Baseline for Software Architecture |

---

## VERSION HISTORY

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-01-22 | System Architect | Initial architecture draft | - |
| 0.5 | 2026-02-03 | System Architect | Review updates, safety architecture | Technical Lead, Safety Manager |
| 1.0 | 2026-02-10 | System Architect | Approved baseline | Project Manager, Chief Engineer |

---

## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **System Architect** | Dr. Robert Kim | [Signed] | 2026-02-10 |
| **Safety Manager** | Michael Torres | [Signed] | 2026-02-10 |
| **Hardware Lead** | Jessica Liu | [Signed] | 2026-02-10 |
| **Software Lead** | Thomas Anderson | [Signed] | 2026-02-10 |
| **Project Manager** | Lisa Anderson | [Signed] | 2026-02-10 |

---

## 1. INTRODUCTION

### 1.1 Purpose

This System Architecture Description (SAD) defines the overall architecture of the **Train Door Control System**, including:
- System decomposition into hardware and software subsystems
- Component interfaces and interactions
- Hardware/software allocation
- Safety architecture and redundancy strategy
- Physical and logical architecture views

This document serves as the **primary architectural input** to:
- Software Architecture Specification (EN 50128 Section 7.3)
- Hardware Design Specification
- Interface Control Documents (ICDs)

### 1.2 Scope

This SAD describes the complete system architecture for the Train Door Control System, covering:
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
   - Redundancy for critical functions (2oo2 sensors, redundant processing)
   - Fail-safe behavior (doors locked on fault, mechanical emergency release)
   - Fault detection and diagnostics (DC ≥ 99%)

2. **Performance Requirements**:
   - Real-time control (20 ms cycle, 50 ms response time for speed interlock)
   - Door operation timing (open ≤ 3s, close ≤ 5s)

3. **Reliability Requirements**:
   - MTBF ≥ 50,000 hours
   - Modular design for easy maintenance (MTTR ≤ 30 min)

4. **Environmental Requirements**:
   - Temperature: -40°C to +70°C
   - Vibration: EN 61373 Category 1 Class B
   - EMC: EN 50121-3-2

5. **Operational Requirements**:
   - Multi-door control (left/right sides, multiple doors per side)
   - Multiple operational modes (Normal, Maintenance, Emergency, Diagnostic, Degraded)
   - Integration with train control system (TCMS)

---

## 2. SYSTEM ARCHITECTURE OVERVIEW

### 2.1 System Context Diagram

```
┌─────────────────────────────────────────────────────────────────────────┐
│                         EXTERNAL SYSTEMS                                │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌──────────────┐    ┌─────────────────┐    ┌──────────────────┐      │
│  │   Driver     │    │  Train Control  │    │  Speed Monitor   │      │
│  │   Control    │    │  Management     │    │  System (SMS)    │      │
│  │   Panel      │───▶│  System (TCMS)  │    │                  │      │
│  └──────────────┘    └─────────────────┘    └──────────────────┘      │
│         │                     │                       │                │
│         │ Discrete I/O        │ MVB                   │ CAN            │
│         │ + CAN               │ (IEC 61375-1)         │ (ISO 11898)    │
│         ▼                     ▼                       ▼                │
│  ┌─────────────────────────────────────────────────────────────┐      │
│  │                                                               │      │
│  │           TRAIN DOOR CONTROL SYSTEM (Target System)          │      │
│  │                                                               │      │
│  │  ┌────────────────────────────────────────────────────┐     │      │
│  │  │  Door Control Electronics (DCE) - SIL 3            │     │      │
│  │  │  - Dual-channel processing (2oo2 for safety)      │     │      │
│  │  │  - Safety logic + Application logic                │     │      │
│  │  │  - Fault detection and diagnostics                 │     │      │
│  │  └────────────────────────────────────────────────────┘     │      │
│  │                           │                                  │      │
│  │                           │ Discrete I/O, PWM                │      │
│  │                           ▼                                  │      │
│  │  ┌────────────────────────────────────────────────────┐     │      │
│  │  │  Door Actuator Units (per door)                    │     │      │
│  │  │  - Motor drivers                                    │     │      │
│  │  │  - Lock actuators                                   │     │      │
│  │  │  - Position sensors (2x per door)                   │     │      │
│  │  │  - Obstacle sensors (2x IR per door)                │     │      │
│  │  │  - Lock sensors (2x per lock)                       │     │      │
│  │  │  - Emergency release (mechanical)                   │     │      │
│  │  └────────────────────────────────────────────────────┘     │      │
│  └───────────────────────────────────────────────────────────────┘      │
│                                                                         │
│  ┌──────────────┐    ┌─────────────────┐                               │
│  │  Platform    │    │  Passenger      │                               │
│  │  Detection   │    │  Emergency      │                               │
│  │  System      │    │  Interfaces     │                               │
│  └──────────────┘    └─────────────────┘                               │
│         │                     │                                        │
│         │ Discrete I/O        │ Discrete I/O                           │
│         └─────────────────────┘                                        │
└─────────────────────────────────────────────────────────────────────────┘
```

### 2.2 System Decomposition

The Train Door Control System is decomposed into the following major subsystems:

| Subsystem | Description | SIL | Implementation |
|-----------|-------------|-----|----------------|
| **Door Control Electronics (DCE)** | Central processing unit with dual-channel safety logic | SIL 3 | Hardware + Software |
| **Door Actuator Units (DAU)** | Motors, locks, sensors per door | SIL 3 | Hardware |
| **Communication Interfaces** | CAN, MVB, discrete I/O interfaces | SIL 2-3 | Hardware + Software |
| **Power Supply Unit (PSU)** | 24V DC power distribution with monitoring | SIL 2 | Hardware |
| **Emergency Release Mechanisms** | Mechanical door release per door | SIL 3 | Hardware (mechanical) |

---

## 3. HARDWARE ARCHITECTURE

### 3.1 Hardware Block Diagram

```
┌─────────────────────────────────────────────────────────────────────────┐
│                     DOOR CONTROL ELECTRONICS (DCE)                      │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌──────────────────────────────────────────────────────────────┐      │
│  │              DUAL-CHANNEL PROCESSING (2oo2)                  │      │
│  │                                                               │      │
│  │  ┌────────────────────┐         ┌────────────────────┐       │      │
│  │  │  Processing        │         │  Processing        │       │      │
│  │  │  Channel A         │◀───────▶│  Channel B         │       │      │
│  │  │                    │  Cross-  │                    │       │      │
│  │  │  - MCU-A (32-bit)  │  Check   │  - MCU-B (32-bit)  │       │      │
│  │  │  - Safety Logic    │         │  - Safety Logic    │       │      │
│  │  │  - Watchdog        │         │  - Watchdog        │       │      │
│  │  └────────────────────┘         └────────────────────┘       │      │
│  │           │                              │                    │      │
│  └───────────┼──────────────────────────────┼────────────────────┘      │
│              │                              │                           │
│  ┌───────────┴──────────────────────────────┴───────────────────┐      │
│  │                   I/O INTERFACE MODULE                        │      │
│  │  - Digital Inputs (sensors, switches)                         │      │
│  │  - Digital Outputs (lock actuators)                           │      │
│  │  - PWM Outputs (motor control)                                │      │
│  │  - Analog Inputs (current monitoring)                         │      │
│  └────────────────────────────────────────────────────────────────┘      │
│              │                                                          │
│  ┌───────────┴──────────────────────────────────────────────────┐      │
│  │               COMMUNICATION INTERFACE MODULE                  │      │
│  │  - CAN Controller x2 (redundant)                              │      │
│  │  - MVB Interface (IEC 61375-1)                                │      │
│  │  - Discrete I/O for driver panel                              │      │
│  └────────────────────────────────────────────────────────────────┘      │
│              │                                                          │
│  ┌───────────┴──────────────────────────────────────────────────┐      │
│  │                   POWER SUPPLY MODULE                         │      │
│  │  - 24V DC input (18-36V range)                                │      │
│  │  - Isolated 5V/3.3V for MCUs                                  │      │
│  │  - Voltage monitoring                                         │      │
│  │  - Over-current protection                                    │      │
│  └────────────────────────────────────────────────────────────────┘      │
└─────────────────────────────────────────────────────────────────────────┘
                               │
                               ▼
┌─────────────────────────────────────────────────────────────────────────┐
│              DOOR ACTUATOR UNIT (per door - 4 doors typical)            │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌────────────────────┐   ┌────────────────────┐                       │
│  │  Door Motor        │   │  Door Lock         │                       │
│  │  - 24V DC motor    │   │  - Solenoid lock   │                       │
│  │  - PWM control     │   │  - Fail-closed     │                       │
│  │  - Current monitor │   │  - Spring-loaded   │                       │
│  └────────────────────┘   └────────────────────┘                       │
│                                                                         │
│  ┌───────────────────────────────────────────────────────────┐         │
│  │  Position Sensors (2x per door - 2oo2)                    │         │
│  │  - Sensor A: Inductive proximity (fully open/closed)      │         │
│  │  - Sensor B: Inductive proximity (fully open/closed)      │         │
│  └───────────────────────────────────────────────────────────┘         │
│                                                                         │
│  ┌───────────────────────────────────────────────────────────┐         │
│  │  Obstacle Sensors (2x per door - redundant)               │         │
│  │  - Sensor A: Infrared beam transmitter/receiver           │         │
│  │  - Sensor B: Infrared beam transmitter/receiver           │         │
│  └───────────────────────────────────────────────────────────┘         │
│                                                                         │
│  ┌───────────────────────────────────────────────────────────┐         │
│  │  Lock Position Sensors (2x per lock - 2oo2)               │         │
│  │  - Sensor A: Magnetic reed switch (locked/unlocked)       │         │
│  │  - Sensor B: Magnetic reed switch (locked/unlocked)       │         │
│  └───────────────────────────────────────────────────────────┘         │
│                                                                         │
│  ┌───────────────────────────────────────────────────────────┐         │
│  │  Emergency Release Mechanism (mechanical)                  │         │
│  │  - Manual pull handle (passenger-operable)                 │         │
│  │  - Mechanical lock override (independent of electronics)   │         │
│  │  - Release detection switch                                │         │
│  └───────────────────────────────────────────────────────────┘         │
└─────────────────────────────────────────────────────────────────────────┘
```

### 3.2 Hardware Components

#### 3.2.1 Door Control Electronics (DCE)

**Component**: Door Control Unit (DCU)  
**Description**: Central processing unit with dual-channel architecture for SIL 3 safety integrity

**Specifications**:
- **Processing**: Dual 32-bit microcontrollers (STM32F4 or equivalent)
  - Channel A: Primary safety logic + application logic
  - Channel B: Redundant safety logic + cross-check
  - Cross-channel communication via SPI (2 Mbps)
- **Memory**:
  - Flash: 512 KB per MCU (code + configuration)
  - RAM: 128 KB per MCU (all static allocation, no heap)
  - EEPROM: 16 KB (configuration data with CRC)
- **Clock**: 168 MHz system clock with PLL
- **Watchdog**: Independent hardware watchdog per MCU (100 ms timeout)
- **Power**: 24V DC input, isolated 5V/3.3V internal supplies
- **Operating Temperature**: -40°C to +85°C (internal electronics)
- **Enclosure**: IP65-rated aluminum housing
- **Dimensions**: 200mm x 150mm x 80mm (rack-mountable)
- **Weight**: ~1.5 kg

**Safety Features**:
- 2oo2 processing for safety-critical functions
- Diverse MCU sources (if feasible)
- Memory protection (MPU) for code/data separation
- CRC on flash memory (boot-time verification)
- Voltage and temperature monitoring

#### 3.2.2 Door Actuator Units

**Component**: Door Motor Assembly  
**Type**: 24V DC brushless motor with gearbox  
**Specifications**:
- Torque: 10 Nm nominal, 15 Nm peak
- Speed: Variable 0-100% via PWM (20 kHz)
- Current: 5A nominal, 8A peak
- Position feedback: Integrated encoder (optional)
- Mechanical force limit: 150 N (per EN 14752)

**Component**: Door Lock Actuator  
**Type**: 24V DC solenoid lock (fail-closed)  
**Specifications**:
- Locking force: 500 N holding force
- Actuation time: < 100 ms
- Fail-safe: Spring-loaded (locked without power)
- Lock verification: 2x magnetic reed switches (2oo2)

**Component**: Position Sensors (2x per door)  
**Type**: Inductive proximity sensors  
**Specifications**:
- Detection range: 5 mm
- Output: PNP normally open, 24V logic
- Response time: < 5 ms
- Mounting: One at fully-open position, one at fully-closed position

**Component**: Obstacle Detection Sensors (2x per door)  
**Type**: Infrared beam transmitter/receiver pairs  
**Specifications**:
- Detection range: Up to 1.5 m (door width)
- Response time: < 50 ms
- Output: Relay contact (N.C. when beam intact)
- Alignment: Horizontal beam across door opening at 0.3m and 1.0m heights

**Component**: Emergency Release Mechanism  
**Type**: Mechanical pull handle with lock override  
**Specifications**:
- Actuation force: 50-100 N (operable by passengers)
- Mechanical advantage: Direct mechanical link to lock mechanism
- Independence: No electrical or electronic components in release path
- Detection: Microswitch for release event logging

### 3.3 Hardware Interface Specifications

#### 3.3.1 External Communication Interfaces

**CAN Bus Interface** (Speed Monitoring System):
- **Protocol**: ISO 11898 (CAN 2.0B)
- **Bit Rate**: 250 kbps
- **Termination**: 120Ω at each end
- **Messages**:
  - RX: Speed data (100 ms cycle, CRC-16)
  - TX: Door status (200 ms cycle)
- **Connector**: 9-pin D-sub male
- **SIL Level**: SIL 3 (speed data critical for door interlocks)

**MVB Interface** (Train Control Management System):
- **Protocol**: IEC 61375-1 (Multifunction Vehicle Bus)
- **Bit Rate**: 1.5 Mbps
- **Messages**:
  - RX: Operational commands (door open/close enable)
  - TX: Door status, fault codes
- **Connector**: Proprietary MVB connector
- **SIL Level**: SIL 2 (operational commands)

**Discrete I/O** (Driver Control Panel):
- **Inputs**: 8x digital inputs (24V logic, opto-isolated)
  - Door open button (left/right)
  - Door close button (left/right)
  - Emergency evacuation enable
  - Mode selection switches
- **Outputs**: 16x digital outputs (24V, 500 mA per channel)
  - Door status indicators (per door)
  - Fault indicators
  - Audible alarms

**Discrete I/O** (Platform Detection):
- **Inputs**: 2x digital inputs (24V logic)
  - Platform left side
  - Platform right side

#### 3.3.2 Internal Interfaces (DCE to Door Actuator Units)

**Door Motor Control**:
- **Signal**: PWM output (20 kHz, 0-100% duty cycle)
- **Voltage**: 24V DC
- **Current Monitoring**: Analog input 0-10V (proportional to motor current)
- **Wiring**: Shielded twisted pair, max length 10m

**Lock Actuator Control**:
- **Signal**: Digital output (24V, 1A)
- **Feedback**: 2x digital inputs (lock position sensors A and B)
- **Wiring**: Shielded cable, max length 10m

**Position Sensors**:
- **Signal**: Digital inputs (24V PNP)
- **Channels**: 2x inputs per door (fully open, fully closed)
- **Wiring**: Shielded twisted pair per sensor

**Obstacle Sensors**:
- **Signal**: Digital inputs (relay contact N.C.)
- **Channels**: 2x inputs per door (obstacle A, obstacle B)
- **Wiring**: Shielded twisted pair per sensor

---

## 4. SOFTWARE ARCHITECTURE OVERVIEW

**Note**: Detailed software architecture is specified in **Software Architecture Specification (DOC-SAS-2026-001)**. This section provides system-level context for software allocation.

### 4.1 Software Decomposition

The software is structured into the following major components:

| Software Component | Description | SIL | Execution |
|-------------------|-------------|-----|-----------|
| **Safety Kernel** | Safety-critical control logic (speed interlock, lock control) | SIL 3 | Both channels (2oo2) |
| **Application Logic** | Non-safety operational logic (mode management, UI) | SIL 1 | Channel A (primary) |
| **Communication Drivers** | CAN, MVB protocol stacks | SIL 2-3 | Both channels |
| **Diagnostics Module** | Fault detection, logging | SIL 3 | Both channels |
| **Hardware Abstraction Layer (HAL)** | Low-level hardware drivers | SIL 3 | Both channels |

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
│  │ Application Logic    │  Cross  │ (Safety only)        │     │
│  │ Communication        │  Check  │ Communication        │     │
│  │ Diagnostics          │         │ Diagnostics          │     │
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
  - Application logic: 8 ms max
  - Communication: 3 ms max
  - Diagnostics: 2 ms max
  - Margin: 2 ms

---

## 5. SAFETY ARCHITECTURE

### 5.1 Safety Principles

The system safety architecture implements the following principles:

1. **Redundancy**: 2oo2 voting for critical sensors and processing
2. **Diversity**: Diverse sensor types where feasible (inductive + magnetic)
3. **Fail-Safe**: Default to safe state (doors locked) on fault detection
4. **Independence**: Mechanical emergency release independent of electronics
5. **Fault Detection**: Comprehensive diagnostics (DC ≥ 99%)

### 5.2 Redundancy Architecture

**Processing Redundancy** (2oo2):
- Dual microcontrollers (Channel A and Channel B)
- Both channels execute safety logic independently
- Cross-channel communication for comparison (every cycle)
- Disagreement → Safe state (doors locked, open inhibited)

**Sensor Redundancy** (2oo2):
- Door position sensors: 2x per door (both must agree for "fully closed")
- Lock position sensors: 2x per lock (both must agree for "locked")
- Obstacle sensors: 2x per door (either sensor triggers re-opening)
- Speed sensors: Redundant CAN sources or diverse speed measurement

**Actuator Independence**:
- Door locks: Fail-closed (spring-loaded, default locked without power)
- Emergency release: Mechanical override (independent path)

### 5.3 Fault Detection Coverage

Target diagnostic coverage: **DC ≥ 99%** (per EN 50129 for SIL 3)

| Fault Class | Detection Method | Detection Time | Coverage |
|-------------|------------------|----------------|----------|
| **MCU failure** | Watchdog timeout, cross-channel comparison | ≤ 100 ms | 99% |
| **Sensor failure** | Sensor plausibility checks, 2oo2 disagreement | ≤ 100 ms | 98% |
| **Actuator failure** | Feedback monitoring (lock sensors, motor current) | ≤ 200 ms | 95% |
| **Communication failure** | CRC errors, timeout detection | ≤ 200 ms | 99% |
| **Memory corruption** | CRC checks (flash, RAM), MPU violations | ≤ 1 cycle | 99% |
| **Power supply fault** | Voltage monitoring (under/over voltage) | ≤ 50 ms | 100% |

**Overall Diagnostic Coverage**: ~98% (exceeds SIL 3 requirement)

### 5.4 Safe States

| Fault Condition | Safe State Response | Rationale |
|----------------|---------------------|-----------|
| **Speed sensor failure** | Assume "train moving", lock doors, inhibit opening | Conservative assumption |
| **Position sensor failure** | Assume "door not closed", inhibit train movement | Prevent movement with unverified door state |
| **Lock sensor failure** | Assume "not locked", inhibit train movement | Conservative assumption |
| **MCU failure (either channel)** | Lock doors (via hardware fail-safe), inhibit opening | Electronics failure → mechanical safety |
| **Communication loss (speed data)** | Assume "train moving", lock doors | Loss of critical interlock data |
| **Power loss** | Locks fail-closed (spring-loaded), emergency release remains functional | Mechanical fail-safe |

### 5.5 Safety-Critical Functions Allocation

| Safety Function | Hardware | Software | Fail-Safe Mechanism |
|----------------|----------|----------|---------------------|
| **Door opening interlock** | Redundant speed sensors, processing | Safety Kernel (2oo2) | Default deny door opening |
| **Door locking** | Spring-loaded locks, 2oo2 sensors | Safety Kernel (2oo2) | Fail-closed locks |
| **Emergency release** | Mechanical override | None (mechanical) | Direct mechanical link |
| **Obstacle detection** | 2x IR sensors, force limiter | Application Logic (SIL 2) | Hardware force limit 150N |
| **Position verification** | 2x inductive sensors per door | Safety Kernel (2oo2) | Conservative assumption on fault |

---

## 6. COMMUNICATION ARCHITECTURE

### 6.1 External Communication Network

```
                  ┌───────────────────────────────┐
                  │  Train Control Management     │
                  │  System (TCMS)                │
                  └───────────┬───────────────────┘
                              │ MVB (IEC 61375-1)
                              │ 1.5 Mbps
                  ┌───────────▼───────────────────┐
                  │  Door Control Electronics     │
                  │  (DCE)                        │
                  └───────┬───────────┬───────────┘
                          │           │
       CAN 250 kbps       │           │ Discrete I/O
       (Speed data)       │           │ + CAN
                          │           │
    ┌─────────────────────▼─┐    ┌───▼─────────────────┐
    │  Speed Monitoring     │    │  Driver Control     │
    │  System               │    │  Panel              │
    └───────────────────────┘    └─────────────────────┘
```

### 6.2 Internal Communication

**Cross-Channel Communication** (Channel A ↔ Channel B):
- **Protocol**: SPI (Serial Peripheral Interface)
- **Speed**: 2 Mbps
- **Data**: Safety-critical variables (speed, door state, lock state)
- **CRC**: CRC-16 on all messages
- **Cycle**: Every 20 ms (synchronized with control cycle)

### 6.3 Communication Safety Measures

- **CRC Protection**: CRC-16 on all safety-critical messages
- **Timeout Detection**: Missing messages detected within 2x cycle time
- **Sequence Counters**: Detect lost or duplicated messages
- **Fail-Safe Default**: On communication loss, assume worst-case (train moving, doors not closed)

---

## 7. PHYSICAL ARCHITECTURE

### 7.1 Physical Deployment

**Typical Train Configuration**:
- 4 doors per side (left and right) = 8 doors total per car
- 1x Door Control Electronics (DCE) unit per car (centralized)
- 8x Door Actuator Units (one per door)
- Cable harness from DCE to each door (max 15m)

**Installation Locations**:
- **DCE**: Under-floor equipment bay (protected environment)
- **Door Actuator Units**: Integrated into door frame
- **Emergency Release**: Interior passenger area (clearly marked)

### 7.2 Wiring Architecture

```
                     ┌─────────────────────┐
                     │  DCE (Under-floor)  │
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
- Connectors: M12 circular connectors (IP67 rated)
- Maximum cable length: 15m (DCE to furthest door)

---

## 8. HARDWARE/SOFTWARE INTERFACE

### 8.1 Hardware Abstraction Layer (HAL)

The software interfaces with hardware through a Hardware Abstraction Layer (HAL) that provides:
- **GPIO**: Digital input/output for sensors, actuators
- **PWM**: Motor speed control (20 kHz)
- **ADC**: Analog-to-digital conversion for current monitoring
- **CAN**: CAN bus driver (transmit/receive)
- **MVB**: MVB interface driver
- **Timers**: Periodic interrupt for 20ms control cycle
- **Watchdog**: Hardware watchdog refresh

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

**MCU Flash Memory** (512 KB):
- 0x08000000 - 0x08007FFF: Bootloader (32 KB)
- 0x08008000 - 0x0807FFFF: Application code (480 KB)

**MCU RAM** (128 KB):
- 0x20000000 - 0x2000FFFF: Stack (64 KB)
- 0x20010000 - 0x2001FFFF: Global variables (64 KB)
- No heap allocation (malloc/free forbidden)

**EEPROM** (16 KB):
- Configuration data (door parameters, calibration)
- CRC-16 protection for all stored data

---

## 9. OPERATIONAL MODES

The system supports the following operational modes (managed by software):

| Mode | Description | Speed Interlock | Use Case |
|------|-------------|-----------------|----------|
| **Normal** | Automatic door control with full interlocks | Active | Revenue service |
| **Manual/Maintenance** | Manual door operation for testing | Active | Maintenance testing |
| **Emergency Evacuation** | Override mode for emergency | Bypassed (with authorization) | Emergency evacuation |
| **Diagnostic** | System diagnostics and sensor testing | Active | Fault diagnosis |
| **Degraded/Fail-Safe** | Limited operation after detected fault | Active | Graceful degradation |

**Mode Transitions**: Controlled by software, require authorization (driver key, TCMS command)

---

## 10. INTERFACE CONTROL DOCUMENTS (ICDs)

The following Interface Control Documents define detailed interface specifications:

| ICD | Description | Status |
|-----|-------------|--------|
| **ICD-001** | DCE to Speed Monitoring System (CAN interface) | Approved |
| **ICD-002** | DCE to TCMS (MVB interface) | Approved |
| **ICD-003** | DCE to Driver Control Panel (Discrete I/O + CAN) | Approved |
| **ICD-004** | DCE to Door Actuator Units (Internal I/O) | Approved |
| **ICD-005** | DCE to Platform Detection System (Discrete I/O) | Approved |

**ICD Location**: `docs/interfaces/`

---

## 11. DESIGN RATIONALE

### 11.1 Architectural Decisions

| Decision | Rationale |
|----------|-----------|
| **Dual-channel processing (2oo2)** | Achieves SIL 3 hardware fault tolerance (HFT=1) per EN 50129 |
| **Centralized DCE per car** | Reduces wiring complexity, simplifies maintenance (modular replacement) |
| **Fail-closed locks** | Mechanical fail-safe ensures doors locked on power loss |
| **Mechanical emergency release** | Independence from electronics ensures reliability in all failure modes |
| **Static memory allocation** | Eliminates heap fragmentation risks, meets EN 50128 SIL 3 recommendations |
| **20 ms control cycle** | Balance between responsiveness (50 ms speed interlock) and processing margin |
| **CAN for speed data** | Standard railway bus, deterministic timing, suitable for SIL 3 with CRC |
| **Redundant obstacle sensors** | Improves reliability, either sensor can trigger safety response |

### 11.2 Trade-offs

| Trade-off | Decision | Justification |
|-----------|----------|---------------|
| **Centralized vs. Distributed DCE** | Centralized (1 DCE per car) | Simpler configuration management, easier maintenance, lower cost |
| **Single vs. Dual channel processing** | Dual channel (2oo2) | Required for SIL 3, provides fault tolerance |
| **Hardware vs. Software force limit** | Both (hardware mechanical limit + software current limit) | Defense in depth |
| **CAN vs. MVB for speed data** | CAN | More widely supported, simpler for point-to-point safety data |

---

## 12. TRACEABILITY

### 12.1 System Requirements to Architecture Allocation

| System Requirement | Architectural Component | Implementation |
|-------------------|------------------------|----------------|
| SYS-REQ-001 to SYS-REQ-016 (Door control) | DCE + Door Actuator Units | Software + Hardware |
| SYS-REQ-017 to SYS-REQ-021 (Emergency release) | Emergency Release Mechanism | Hardware (mechanical) |
| SYS-REQ-022 to SYS-REQ-024 (Operational modes) | Software (Mode Management) | Software |
| SYS-REQ-025 to SYS-REQ-027 (Position monitoring) | Position Sensors + Software | Hardware + Software |
| SYS-REQ-028 to SYS-REQ-031 (Fault detection) | Diagnostics Module (Software) | Software |
| SYS-REQ-045 to SYS-REQ-048 (System interfaces) | Communication Interfaces | Hardware + Software |

### 12.2 Safety Requirements to Architecture Allocation

| Safety Requirement | Architectural Component | SIL |
|-------------------|------------------------|-----|
| SF-001 (Door opening interlock) | Dual-channel processing + Speed sensors | SIL 3 |
| SF-002 (Door locking) | Fail-closed locks + 2oo2 lock sensors | SIL 3 |
| SF-003 (Obstacle detection) | Redundant IR sensors + Software | SIL 2 |
| SF-004 (Emergency release) | Mechanical release mechanism | SIL 3 |
| SF-006 (Door closed verification) | 2oo2 position sensors + Software | SIL 3 |
| SF-007 (Fault detection) | Diagnostics module + Cross-channel checks | SIL 3 |

---

## 13. REFERENCES

### 13.1 Normative References

- **EN 50129:2018** - Railway applications - Safety related electronic systems for signalling
- **EN 50128:2011** - Railway applications - Software for railway control and protection systems
- **EN 50155:2017** - Railway applications - Electronic equipment used on rolling stock
- **EN 61373:2010** - Railway applications - Rolling stock equipment - Shock and vibration tests
- **IEC 61375-1:2012** - Electronic railway equipment - Train communication network (TCN)
- **ISO 11898:2003** - Controller area network (CAN)

### 13.2 Project References

- **System Requirements Specification** (DOC-SYS-REQ-2026-001)
- **System Safety Requirements Specification** (DOC-SYS-SAFE-2026-001)
- **Software Architecture Specification** (DOC-SAS-2026-001) [To be developed]
- **Hardware Design Specification** (DOC-HW-DES-2026-001) [To be developed]
- **Interface Control Documents** (ICD-001 to ICD-005)

---

## DOCUMENT APPROVAL

This System Architecture Description is **APPROVED** as the architectural baseline for software and hardware design.

**Baseline Version**: 1.0  
**Baseline Date**: 2026-02-10  
**Configuration Item ID**: CI-SYS-ARCH-001  

Any changes to system architecture SHALL be processed through the Change Control Board (CCB) with architecture review.

---

**END OF DOCUMENT**
