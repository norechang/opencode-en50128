# System Architecture Description

## Document Control

| Property | Value |
|----------|-------|
| **Document ID** | DOC-TDC-SAD-SYS-001 |
| **Project** | TDC — Train Door Control |
| **System** | Train Door Control System (TDCS) |
| **Version** | 1.0 |
| **Status** | APPROVED — System Input |
| **Date** | 2026-03-27 |
| **Prepared by** | COD (generate-system) |
| **Standard** | EN 50128:2011, EN 50129:2018 |
| **SIL Level** | SIL 3 |

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| System Engineer | TBD | ___________ | 2026-03-27 |
| Safety Authority | TBD | ___________ | — |

---

## 1. Introduction

### 1.1 Purpose

This System Architecture Description (SAD) defines the overall architecture of the Train Door Control System (TDCS). It provides the architectural context and constraints that SHALL be respected by the software architecture developed in EN 50128 Phase 3.

### 1.2 Scope

The SAD covers the hardware architecture, software partitioning, inter-component interfaces, and safety architecture of the TDCS at the system level. It is an input to the Software Architecture Specification (SAS).

---

## 2. Architectural Overview

### 2.1 Architecture Pattern

The TDCS employs a **dual-channel (2oo2) safety architecture** to achieve SIL 3:

```
┌─────────────────────────────────────────────────────────────────┐
│                    Train Door Control System                     │
│                        (TDCS — SIL 3)                           │
└──────────────────────────┬──────────────────────────────────────┘
                           │
          ┌────────────────┴────────────────┐
          │                                 │
┌─────────▼─────────┐             ┌─────────▼─────────┐
│   DCU Channel A   │◄───SPI──────►   DCU Channel B   │
│  (STM32H743 CPU)  │  Cross-link  │  (STM32H743 CPU)  │
│                   │             │                   │
│  ┌─────────────┐  │             │  ┌─────────────┐  │
│  │ SW: DSM     │  │             │  │ SW: DSM     │  │
│  │ SW: SPM     │  │             │  │ SW: SPM     │  │
│  │ SW: OBD     │  │             │  │ SW: OBD     │  │
│  │ SW: TCI     │  │             │  │ SW: TCI     │  │
│  │ SW: FMG     │  │             │  │ SW: FMG     │  │
│  │ SW: DGN     │  │             │  │ SW: DGN     │  │
│  │ SW: HAL     │  │             │  │ SW: HAL     │  │
│  └─────────────┘  │             │  └─────────────┘  │
└─────────┬─────────┘             └─────────┬─────────┘
          │                                 │
          └─────────────┬───────────────────┘
                        │ (AND-gate: both channels agree)
              ┌─────────▼─────────┐
              │  Output Comparator │
              │   & Actuator I/F   │
              └─────────┬─────────┘
                        │
         ┌──────────────┼──────────────┐
         │              │              │
    ┌────▼────┐   ┌──────▼──────┐  ┌──▼──────────┐
    │  DDU(s) │   │  TCMS (CAN) │  │  Diag. Port │
    │per door │   │  Interface  │  │  (USB/RS232)│
    └─────────┘   └─────────────┘  └─────────────┘
```

### 2.2 Safety Architecture Principle

- Both channels independently compute all outputs
- **Agreement required** before any actuator command is issued
- **Disagreement** triggers immediate transition to safe state (doors locked, drives de-energised)
- Watchdog timer (50 ms) on each channel — expiry triggers safe state without software intervention

---

## 3. Hardware Architecture

### 3.1 Door Control Unit (DCU)

| Parameter | Value |
|-----------|-------|
| Architecture | Dual-channel 2oo2 |
| Processor (per channel) | STM32H743 (or equivalent), ARM Cortex-M7, 400 MHz |
| RAM (per channel) | 1 MB SRAM (static allocation only) |
| Flash (per channel) | 2 MB internal flash (program code) |
| Non-volatile storage | SPI flash 16 MB (event log, shared) |
| Watchdog | Hardware watchdog per channel, 50 ms timeout |
| Power supply | 24 VDC input; isolated 5 V/3.3 V DC-DC per channel |
| Environmental | EN 50155 qualified, -25°C to +55°C operational |
| EMC | EN 50121-3-2 emissions and immunity |

### 3.2 Door Drive Units (DDU)

| Parameter | Value |
|-----------|-------|
| Per-door quantity | 1 DDU per door leaf |
| Actuator type | DC motor with encoder and mechanical end-stops |
| Position sensing | Dual-channel (open/locked) end-stop switches |
| Interface to DCU | Proprietary RS-485, 115.2 kbit/s |
| Safety feature | Motor power removed on loss of RS-485 comms (fail-safe) |

### 3.3 Obstacle Detection Sensors

| Parameter | Value |
|-----------|-------|
| Type | Infrared beam pairs |
| Quantity | 2 per door opening (redundant) |
| Interface | Digital GPIO (24 V logic), interrupt-driven |
| Response time | Interrupt latency ≤ 5 ms |
| Fail-safe | Beam break treated as obstacle present (fail-safe default) |

### 3.4 External Interfaces

| Interface | Connected To | Protocol | Purpose |
|-----------|-------------|----------|---------|
| CAN 2.0B | TCMS | ISO 11898, 250 kbit/s | Speed signal, door commands, door status |
| RS-485 | DDUs (all doors) | Proprietary, 115.2 kbit/s | Drive commands, position feedback |
| GPIO (24 V) | Obstacle sensors | Interrupt-driven | Obstacle detect/clear |
| SPI cross-link | Channel A ↔ Channel B | 10 Mbit/s | Cross-channel comparison |
| USB/RS-232 | Maintenance laptop | 115.2 kbit/s | Diagnostics and maintenance access |
| 24 VDC | Train battery | N/A | Primary power supply |

---

## 4. Software Architecture Overview

### 4.1 Software Partitioning

Each DCU channel runs **identical software** on independent hardware. The software is structured in layers:

```
┌──────────────────────────────────────────────────────────────────┐
│                    Application Layer                              │
│  ┌──────────┐ ┌──────────┐ ┌──────────┐ ┌──────────────────────┐│
│  │   DSM    │ │   SPM    │ │   OBD    │ │        FMG           ││
│  │ (Door SM)│ │(Speed Mon)│ │(Obstacle)│ │  (Fault Manager)    ││
│  └──────────┘ └──────────┘ └──────────┘ └──────────────────────┘│
│  ┌──────────┐ ┌──────────────────────────────────────────────────┐│
│  │   DGN    │ │              TCI (TCMS Interface)                ││
│  │(Diagnostics│ └──────────────────────────────────────────────────┘│
│  └──────────┘                                                     │
└──────────────────────────────────────────────────────────────────┘
┌──────────────────────────────────────────────────────────────────┐
│                  Hardware Abstraction Layer (HAL)                 │
│         GPIO │ ADC │ CAN │ SPI │ RS-485 │ Watchdog │ Flash       │
└──────────────────────────────────────────────────────────────────┘
┌──────────────────────────────────────────────────────────────────┐
│                       Hardware (STM32H743)                        │
└──────────────────────────────────────────────────────────────────┘
```

### 4.2 Software Components

| Component | ID | SIL | Safety-Critical | Description |
|-----------|-----|-----|----------------|-------------|
| Door State Machine | DSM | SIL 3 | YES | Main door control logic; state-based sequencing |
| Speed Monitor | SPM | SIL 3 | YES | Reads TCMS speed; enforces speed interlock (SF-001) |
| Obstacle Detector | OBD | SIL 3 | YES | Processes obstacle inputs; triggers reversal (SF-003) |
| TCMS Interface | TCI | SIL 3 | YES | CAN bus driver; command/status encoding-decoding |
| Fault Manager | FMG | SIL 3 | YES | Detects faults; manages safe state (SF-004) |
| Diagnostics | DGN | SIL 1 | NO | Event logging; non-safety diagnostic reporting |
| Hardware Abstraction Layer | HAL | SIL 3 | YES | All hardware I/O drivers |

### 4.3 Cross-Channel Communication

- Each channel transmits its computed output to the other channel via SPI cross-link at every control cycle (10 ms)
- The output comparator compares both channels before enabling actuator output
- If computed outputs disagree for more than **2 consecutive cycles (20 ms)**: safe state triggered
- Cross-link failure (no data received within 15 ms): safe state triggered

### 4.4 Safe State Definition

The TDCS safe state is defined as:
- All door drives de-energised
- Door lock solenoids energised (locked closed)
- Door-locked signal NOT asserted to TCMS
- All obstacle detection monitoring active
- FMG fault code recorded to non-volatile log
- Watchdog timer restarted (system continues monitoring)

---

## 5. Timing and Performance Architecture

### 5.1 Control Cycle

| Parameter | Value |
|-----------|-------|
| Main control cycle | 10 ms |
| Cross-channel comparison period | 10 ms (every cycle) |
| Watchdog heartbeat period | ≤ 25 ms (must be within 50 ms timeout) |
| TCMS speed poll period | 100 ms (10 Hz, per SYS-FR interface) |
| Obstacle interrupt response | ≤ 5 ms (interrupt latency) |

### 5.2 Timing Budgets

| Event Chain | Budget | Allocation |
|-------------|--------|-----------|
| Obstacle detected → motor reversal | ≤ 150 ms | ISR: 5 ms; OBD processing: 10 ms; DSM state change: 10 ms; DDU command: 125 ms |
| TCMS command → door movement start | ≤ 200 ms | TCI decode: 10 ms; DSM decision: 10 ms; HAL output: 5 ms; DDU response: 175 ms |
| Door locked → TCMS status update | ≤ 100 ms | HAL read: 5 ms; DSM update: 10 ms; TCI transmit: 10 ms; CAN latency: 75 ms |
| Channel watchdog timeout → safe state | ≤ 50 ms | Hardware enforced |

---

## 6. Safety Architecture Evidence

### 6.1 Safety Integrity Achievement

| Safety Function | Architecture Measure | SIL Achieved |
|----------------|---------------------|--------------|
| SF-001 (Speed Interlock) | 2oo2 channel comparison; speed validated by both channels | SIL 3 |
| SF-002 (Departure Interlock) | Lock sensor read by both channels independently | SIL 3 |
| SF-003 (Obstacle Detection) | 2 redundant sensors per door; both channels monitor | SIL 3 |
| SF-004 (Safe State) | Watchdog + FMG on both channels; safe state = hardware default | SIL 3 |
| SF-005 (Position Verification) | Independent sensor channel per door position | SIL 3 |

### 6.2 Common-Cause Failure Mitigation

| Measure | Implementation |
|---------|---------------|
| Diverse hardware per channel | Independent power regulators; separate PCBs |
| Thermal separation | Channels physically separated in DCU enclosure |
| Software identical (2oo2) | Same binary; common-cause detected by hardware comparator |
| Independent watchdog | Separate hardware watchdog per channel |
| EMC separation | Separate EMC filtering per channel input |

---

## 7. Architectural Constraints for Software Design

The following constraints SHALL be respected in the software architecture and design phases:

| ID | Constraint | Phase |
|----|-----------|-------|
| AC-001 | No dynamic memory allocation anywhere in the software | Phase 3, 5 |
| AC-002 | No recursion in any safety-critical code path | Phase 3, 5 |
| AC-003 | All inter-module communication via defined interfaces (no global mutable state except HAL registers) | Phase 3 |
| AC-004 | All external inputs validated in HAL before passing to application layer | Phase 3, 5 |
| AC-005 | Cyclomatic complexity ≤ 10 for every function | Phase 5 |
| AC-006 | MISRA C:2012 compliance mandatory for all safety-critical modules | Phase 5 |
| AC-007 | Each software component shall have a defined single responsibility (Table 4.2) | Phase 3 |
| AC-008 | Cross-channel data exchange protocol shall be defined in SIS before implementation | Phase 3 |

---

*End of Document — DOC-TDC-SAD-SYS-001 v1.0*
