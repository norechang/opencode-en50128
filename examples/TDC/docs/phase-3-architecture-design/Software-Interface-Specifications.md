# Software Interface Specifications (SIS)

**REFERENCE**: EN 50128:2011 Section 7.3.3, Table A.3, Annex C Item 11

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SIS-2026-001 |
| **CI ID** | CI-INTERFACES-TDC-001 |
| **Version** | 0.1 DRAFT |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Software Designer (DES) |
| **Status** | Draft |

### Revision History

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-04-02 | DES | Initial draft — Phase 3 SIS derived from DOC-SAS-2026-001 v0.2 and DOC-SDS-2026-001 v0.1. Covers all 20 internal interfaces (IF-001–IF-020) and 13 external interfaces (REQ-INT-001–REQ-INT-013). | — |

---

## APPROVALS

**EN 50128 Annex C Table C.1 Signature Chain — Item 11 (SIS) — Track A (Development)**

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Author (DES) | Software Designer | _____________ | 2026-04-02 |
| Reviewer (QUA) | Quality Assurance | _____________ | __________ |
| Approver (PM) | Project Manager | _____________ | __________ |

**Notes:**
- Track A sign-off only. VER and VAL are Track B independent reviewers; their sign-off
  is recorded in their own reports (item 14: Architecture and Design Verification Report,
  item 25: Software Validation Report) — NOT in this document's Approvals table.
- DES has no authorship role in items 12, 13, 14 (owned by INT or VER).
- All submissions route through PM — DES does not contact QUA or VER directly.

---

## 1. INTRODUCTION

### 1.1 Purpose

This Software Interface Specifications (SIS) document defines all software interfaces for
the TDC (Train Door Control System) at SIL 3, in compliance with EN 50128:2011 §7.3.3
and Annex C Item 11.

This document specifies:
- All **internal module-to-module interfaces** (IF-001 through IF-020 from SAS §5.1)
- All **external hardware/software interfaces** (REQ-INT-001 through REQ-INT-013)
- **Data type definitions** referenced across all interfaces
- **Interface safety constraints** including fail-safe defaults, error detection, and
  timeout behaviour
- **Traceability** from interfaces to SRS requirements

### 1.2 Scope

This SIS covers all interfaces between software modules executing on Channel A and
Channel B of the TDC Door Control Unit (DCU), and all external interfaces to:
- Train Control and Management System (TCMS) via CAN bus
- Door Display Unit (DDU) via RS-485
- Door hardware sensors and actuators via GPIO and ADC
- Cross-channel redundancy link via SPI
- Watchdog hardware
- Diagnostics port

**Out of Scope**: Hardware design, bootloader interfaces, maintenance tooling internals.

### 1.3 SIL Classification

**Target SIL Level**: SIL 3 (all safety-critical interfaces). DGN diagnostics port is
classified SIL 1 per DOC-SAS-2026-001 §4.1.

### 1.4 Interface Design Constraints (Mandatory SIL 3)

The following constraints govern all interfaces in this document:

| Constraint | Rule | Reference |
|-----------|------|-----------|
| No dynamic memory allocation | MISRA C:2012 Rule 21.3; mandatory SIL 2+ | REQ-SAFE-017 |
| Fixed-width integer types only | MISRA C:2012 | All interfaces |
| CRC-16-CCITT polynomial **0x1021**, initial value 0xFFFF, no final XOR | Unified CRC policy — OI-FTA-003 | SAS §5.3 v0.2 |
| All HAL functions return `error_t`; callers must check | Architecture rule | SDS §2.2 |
| `safe_state_active` writable only by SKN module | Architecture rule | SAS §5.2 |
| Static data structures only — no `malloc`/`calloc` | Architecture rule | SDS §1.4 |
| Little-endian byte order for all multi-byte fields | Platform constraint | All serial/CAN interfaces |

### 1.5 Input Documents

| Document ID | Title | Version | Role |
|-------------|-------|---------|------|
| DOC-SRS-2026-001 | Software Requirements Specification | 0.1 | Requirements source |
| DOC-SAS-2026-001 | Software Architecture Specification | 0.2 | Architecture source — IF-001–IF-020 |
| DOC-SDS-2026-001 | Software Design Specification | 0.1 | Module design and data types source |

---

## 2. INTERFACE OVERVIEW

### 2.1 Interface Categories

| Category | Count | IDs | Description |
|----------|-------|-----|-------------|
| Internal module interfaces | 20 | IF-001–IF-020 | Intra-software data flows between architectural components |
| External hardware interfaces | 13 | EXT-001–EXT-013 | Interfaces to hardware, external systems, and the environment |

### 2.2 Architectural Component Summary

The following components exchange data via the interfaces specified in this document:

| Component ID | Name | Abbreviation | SIL |
|---|---|---|---|
| COMP-001 | Safety Kernel | SKN | SIL 3 |
| COMP-002 | Speed Interlock Monitor | SPM | SIL 3 |
| COMP-003 | Door State Machine | DSM | SIL 3 |
| COMP-004 | Obstacle Detection | OBD | SIL 3 |
| COMP-005 | Train Communication Interface | TCI | SIL 3 |
| COMP-006 | Fault Manager | FMG | SIL 3 |
| COMP-007 | Diagnostics Logger | DGN | SIL 1 |
| COMP-008 | Hardware Abstraction Layer | HAL | SIL 3 (platform) |

### 2.3 Interface Topology Diagram

```
                    ┌──────────────────────────────────────────────┐
                    │             TDC Software Architecture         │
                    │                                              │
  CAN Bus ─────────►│ TCI ──IF-001──► SPM ──IF-002──► SKN         │
  (TCMS)           │      ──IF-018──► DSM ──IF-008──► SKN         │
                    │      ◄─IF-016──  SKN ──IF-015──► ALL        │
  RS-485 ──────────►│ TCI ◄─IF-009── DSM                          │
  (DDU)            │                                              │
                    │       OBD ──IF-006──► DSM                    │
  GPIO/ADC ────────►│ HAL ──IF-004──► DSM    ──IF-007──► SKN       │
  (Sensors)        │      ──IF-005──► OBD                          │
                    │      ──IF-019──► SKN                         │
                    │                                              │
  SPI ─────────────►│ SKN ──IF-017──► SKN(Ch B)                   │
  (Cross-channel)  │                                              │
                    │       FMG ──IF-012──► SKN                    │
                    │           ──IF-013──► TCI                    │
                    │           ──IF-014──► DGN                    │
                    │                                              │
  Diag Port ───────►│ DGN ──IF-020──► SPI Flash                   │
                    └──────────────────────────────────────────────┘
```

---

## 3. INTERNAL SOFTWARE INTERFACES

### 3.1 Interface Conventions

All internal interfaces share the following conventions:

- **Cycle period**: 20 ms (50 Hz) unless otherwise specified
- **Data direction**: Written by exactly one component; read by one or more
- **Memory**: All shared data in statically allocated global structures
- **Write ownership**: Only the designated writer may modify a shared datum
- **Error propagation**: Functions returning `error_t` — callers MUST check return value
- **Safe defaults**: All shared data initialised to fail-safe values at startup

### 3.2 IF-001 — TCI → SPM: TCMS Speed Message

| Field | Value |
|-------|-------|
| **Interface ID** | IF-001 |
| **Direction** | TCI writes → SPM reads |
| **Data Structure** | `tcms_speed_msg_t` |
| **Period** | 100 ms (CAN message 0x100) |
| **Traceability** | REQ-INT-007, SAS §5.1 IF-001 |

**Data Structure** (`tdc_types.h`):

```c
typedef struct {
    uint16_t speed_kmh_x10;   /* Speed in 0.1 km/h units; range [0, 5000]; 0xFFFF = invalid */
    uint8_t  seq_counter;     /* Sequence counter [0–255], monotonically incrementing       */
    uint16_t crc16;           /* CRC-16-CCITT (0x1021) over bytes 0–2                       */
} tcms_speed_msg_t;
```

**Pre-conditions**:
- TCI has successfully received and validated CAN frame (CRC and sequence check passed)
- `tcms_speed_msg_t` instance is in statically allocated TCI buffer

**Post-conditions**:
- SPM reads `speed_kmh_x10` within one scheduler cycle after TCI writes
- If CRC fails: TCI leaves previous valid value; increments `can_crc_error_count`

**Fail-safe Default**: `speed_kmh_x10 = 0xFFFF` (invalid sentinel) — treated by SPM as
"speed unknown → interlock active".

**Timing Constraint**: SPM must read within 100 ms of TCI write (one CAN period).
Missed update (> 200 ms = `CAN_TIMEOUT_MS`) triggers `ERR_COMM_TIMEOUT` in FMG.

---

### 3.3 IF-002 — SPM → SKN: Speed Interlock Gate (Cycle)

| Field | Value |
|-------|-------|
| **Interface ID** | IF-002 |
| **Direction** | SPM writes → SKN reads |
| **Data** | `speed_interlock_active` (`uint8_t`), `current_speed_kmh_x10` (`uint16_t`) |
| **Period** | Every 20 ms scheduler cycle |
| **Traceability** | REQ-SAFE-001, REQ-INT-007, SAS §5.1 IF-002 |

**Signal Definitions**:

| Signal | Type | Range | Fail-safe Value | Meaning |
|--------|------|-------|-----------------|---------|
| `speed_interlock_active` | `uint8_t` | 0 = clear, 1 = active | 1 (interlock active) | Inhibits door open commands when speed ≥ 5 km/h |
| `current_speed_kmh_x10` | `uint16_t` | [0, 5000] or 0xFFFF | 0xFFFF | Current vehicle speed for logging |

**Pre-conditions**: SPM has processed the latest `tcms_speed_msg_t` from IF-001.

**Post-conditions**: SKN applies `speed_interlock_active` in the same cycle; does not
propagate a door open command while `speed_interlock_active == 1`.

**Fail-safe Default**: `speed_interlock_active = 1` at cold start until first valid
TCMS speed message received.

---

### 3.4 IF-003 — SPM → DSM: Speed Gate (Cycle)

| Field | Value |
|-------|-------|
| **Interface ID** | IF-003 |
| **Direction** | SPM writes → DSM reads |
| **Data** | `speed_interlock_active` (`uint8_t`) — same variable as IF-002 |
| **Period** | Every 20 ms scheduler cycle |
| **Traceability** | REQ-SAFE-001, SAS §5.1 IF-003 |

DSM reads `speed_interlock_active` each cycle. If `speed_interlock_active == 1`, DSM
refuses to transition any door FSM to `FSM_OPENING` or `FSM_CLOSING`.

**Fail-safe Default**: Same as IF-002 — `speed_interlock_active = 1` at startup.

---

### 3.5 IF-004 — HAL GPIO → DSM: Position and Lock Sensor Inputs

| Field | Value |
|-------|-------|
| **Interface ID** | IF-004 |
| **Direction** | HAL writes → DSM reads |
| **Data** | Per-door sensor arrays (see below) |
| **Period** | Every 20 ms scheduler cycle |
| **Traceability** | REQ-INT-002, REQ-INT-005, SAS §5.1 IF-004 |

**Data Structures** (statically allocated arrays, index = door number [0–3]):

```c
/* Position sensors — 2 per door (2oo2 voting by DSM) */
uint8_t hal_pos_sensor_a[MAX_DOORS];  /* 1 = activated, 0 = not activated */
uint8_t hal_pos_sensor_b[MAX_DOORS];  /* 1 = activated, 0 = not activated */

/* Lock sensors — 2 per door (2oo2 voting by DSM) */
uint8_t hal_lock_sensor_a[MAX_DOORS]; /* 1 = locked, 0 = unlocked */
uint8_t hal_lock_sensor_b[MAX_DOORS]; /* 1 = locked, 0 = unlocked */
```

**2oo2 Voting Rule**: DSM interprets a door as in the indicated state only if BOTH
sensors agree. Disagreement → `ERR_SENSOR_DISAGREE` → FMG fault log → safe state.

**Fail-safe Defaults**:
- `hal_pos_sensor_a/b = 0` (not activated — door assumed not at end position)
- `hal_lock_sensor_a/b = 1` (locked — conservative default)

**Error Handling**: GPIO read failure (`error_t != SUCCESS`) → HAL sets sensor value to
fail-safe default and reports to FMG.

---

### 3.6 IF-005 — HAL GPIO → OBD: Obstacle Sensor Inputs

| Field | Value |
|-------|-------|
| **Interface ID** | IF-005 |
| **Direction** | HAL writes → OBD reads |
| **Data** | Per-door obstacle sensor arrays + ISR trigger flag |
| **Period** | ISR (immediate) + 20 ms polled confirmation |
| **Traceability** | REQ-INT-003, SAS §5.1 IF-005 |

**Data Structures**:

```c
/* Obstacle sensors — 2 per door (1oo2 logic for detection by OBD) */
uint8_t hal_obs_sensor_a[MAX_DOORS];   /* 1 = obstacle detected, 0 = clear */
uint8_t hal_obs_sensor_b[MAX_DOORS];   /* 1 = obstacle detected, 0 = clear */
uint8_t hal_obs_isr_flag[MAX_DOORS];   /* Set by ISR OBD_ObstacleISR; cleared by OBD */
```

**1oo2 Detection Logic**: OBD considers an obstacle present if EITHER sensor indicates
detection (`hal_obs_sensor_a[d] == 1 || hal_obs_sensor_b[d] == 1`). This is the
safety-conservative (1oo2) voting for detection; 2oo2 would miss single sensor
activations.

**ISR Interface** (`OBD_ObstacleISR`):
- Triggered on rising edge of obstacle sensor GPIO line
- ISR sets `hal_obs_isr_flag[door]` and records timestamp (ms tick)
- ISR latency ≤ 1 ms (REQ-INT-003)
- ISR MUST be minimal — no blocking calls, no HAL function calls with side-effects

**Fail-safe Default**: `hal_obs_sensor_a/b = 0` (clear); `hal_obs_isr_flag = 0`.

---

### 3.7 IF-006 — OBD → DSM: Obstacle Flags (Cycle)

| Field | Value |
|-------|-------|
| **Interface ID** | IF-006 |
| **Direction** | OBD writes → DSM reads |
| **Data** | `obstacle_flags[MAX_DOORS]` (`uint8_t`) |
| **Period** | Every 20 ms scheduler cycle |
| **Traceability** | REQ-SAFE-004, REQ-INT-003, SAS §5.1 IF-006 |

```c
uint8_t obstacle_flags[MAX_DOORS]; /* 1 = obstacle present on door d, 0 = clear */
```

**Semantics**: OBD sets `obstacle_flags[d] = 1` if either obstacle sensor for door `d`
indicates detection, OR if `hal_obs_isr_flag[d]` was set since last cycle. Cleared only
when both sensors read 0 for 3 consecutive cycles (debounce).

**DSM Response**: Upon reading `obstacle_flags[d] == 1` while door `d` is in
`FSM_CLOSING` or `FSM_OPENING`: transition to `FSM_OBSTACLE_HALT` immediately, cut motor
PWM, assert lock actuator to locked state.

**Fail-safe Default**: `obstacle_flags[d] = 0` (clear). OBD sets to 1 on any detection;
fail-safe is achieved by DSM's conservative response to obstacle.

---

### 3.8 IF-007 — OBD → SKN: Obstacle Flags for Safety Arbitration

| Field | Value |
|-------|-------|
| **Interface ID** | IF-007 |
| **Direction** | OBD writes → SKN reads |
| **Data** | `obstacle_flags[MAX_DOORS]` (`uint8_t`) — same array as IF-006 |
| **Period** | Every 20 ms scheduler cycle |
| **Traceability** | REQ-SAFE-004, SAS §5.1 IF-007 |

SKN reads `obstacle_flags` each cycle for independent safety arbitration. If any flag is
set and SKN has issued a door open/close command, SKN independently triggers a safe state
command to DSM via IF-015.

---

### 3.9 IF-008 — DSM → SKN: Door and Lock States (Cycle)

| Field | Value |
|-------|-------|
| **Interface ID** | IF-008 |
| **Direction** | DSM writes → SKN reads |
| **Data** | `door_states[MAX_DOORS]`, `lock_states[MAX_DOORS]` |
| **Period** | Every 20 ms scheduler cycle |
| **Traceability** | REQ-SAFE-001, REQ-SAFE-003, SAS §5.1 IF-008 |

**Data Structures**:

```c
door_state_t door_states[MAX_DOORS]; /* Per-door physical state (enum) */
uint8_t      lock_states[MAX_DOORS]; /* 1 = locked, 0 = unlocked         */
```

**`door_state_t` Enum**:

| Value | Symbol | Meaning |
|-------|--------|---------|
| 0 | `DOOR_UNKNOWN` | State indeterminate (startup or sensor fault) |
| 1 | `DOOR_FULLY_OPEN` | Both position sensors agree: open limit reached |
| 2 | `DOOR_INTERMEDIATE` | Door in motion or partially open |
| 3 | `DOOR_FULLY_CLOSED` | Both position sensors agree: closed limit reached |
| 4 | `DOOR_CLOSED_AND_LOCKED` | Closed + both lock sensors agree: locked |
| 5 | `DOOR_FAULT` | Sensor disagreement or mechanical fault detected |

**Fail-safe Default**: `door_states[d] = DOOR_UNKNOWN`, `lock_states[d] = 1` (locked).

**SKN Departure Interlock**: SKN will assert `departure_interlock_ok = 0` (interlock NOT
clear) unless ALL doors report `DOOR_CLOSED_AND_LOCKED`.

---

### 3.10 IF-009 — DSM → TCI: Per-Door Status for DDU/TCMS (100 ms)

| Field | Value |
|-------|-------|
| **Interface ID** | IF-009 |
| **Direction** | DSM writes → TCI reads |
| **Data** | `door_status_msg_t` (one per door) |
| **Period** | 100 ms |
| **Traceability** | REQ-INT-008, REQ-INT-009, SAS §5.1 IF-009 |

**Data Structure**:

```c
typedef struct {
    uint8_t       door_id;           /* Door number [0–3]                              */
    door_state_t  door_state;        /* Physical state (enum)                          */
    uint8_t       lock_state;        /* 1 = locked, 0 = unlocked                       */
    door_fsm_state_t fsm_state;      /* FSM state for diagnostics                      */
    uint8_t       fault_flags;       /* Bitmask: bit0=sensor_disagree, bit1=timeout    */
    uint8_t       seq_counter;       /* Sequence counter [0–255]                       */
    uint16_t      crc16;             /* CRC-16-CCITT (0x1021) over bytes 0–6           */
} door_status_msg_t;
```

TCI transmits `door_status_msg_t` as:
- CAN message 0x201 (door status, 100 ms periodic) — fields from all 4 doors
- RS-485 DDU frame (on-change + 100 ms periodic)

---

### 3.11 IF-010 — DSM → HAL: Lock Actuator Command

| Field | Value |
|-------|-------|
| **Interface ID** | IF-010 |
| **Direction** | DSM writes → HAL executes |
| **Data** | `lock_cmd[MAX_DOORS]` (`uint8_t`) |
| **Period** | On state transition only |
| **Traceability** | REQ-INT-004, SAS §5.1 IF-010 |

```c
uint8_t lock_cmd[MAX_DOORS]; /* 0 = lock (fail-safe), 1 = unlock */
```

**Fail-safe Encoding**: GPIO output is **active-LOW** — driving pin LOW energises
actuator to unlock; releasing pin (HIGH or de-energised) allows spring return to locked
state. `lock_cmd = 0` → `HAL_GPIO_SetLockActuator(door, 0)` → GPIO HIGH → spring locked.

**Function Signature**:
```c
error_t HAL_GPIO_SetLockActuator(uint8_t door_id, uint8_t unlock);
```
- `door_id`: [0–3]
- `unlock`: 0 = locked (default/safe), 1 = unlocked
- Returns: `ERROR_SUCCESS` or `ERR_HW_FAULT`

**Pre-condition**: DSM checks `speed_interlock_active == 0` and
`safe_state_active == 0` before calling unlock. Lock (0) may be commanded at any time.

---

### 3.12 IF-011 — DSM → HAL: Motor PWM and Direction Command

| Field | Value |
|-------|-------|
| **Interface ID** | IF-011 |
| **Direction** | DSM writes → HAL executes |
| **Data** | `motor_duty[MAX_DOORS]`, `motor_dir[MAX_DOORS]` |
| **Period** | On command (FSM transition) |
| **Traceability** | REQ-INT-001, SAS §5.1 IF-011 |

```c
uint8_t motor_duty[MAX_DOORS]; /* PWM duty cycle [0–100] in percent; 0 = motor stopped */
uint8_t motor_dir[MAX_DOORS];  /* 0 = open direction, 1 = close direction               */
```

**Function Signatures**:
```c
error_t HAL_PWM_SetDutyCycle(uint8_t door_id, uint8_t duty_pct);
error_t HAL_GPIO_SetMotorDirection(uint8_t door_id, uint8_t direction);
```
- `duty_pct`: [0–100]; 0 stops motor
- `direction`: 0 = opening, 1 = closing
- Returns: `ERROR_SUCCESS`, `ERR_RANGE`, or `ERR_HW_FAULT`

**Fail-safe**: On safe state activation, DSM commands `motor_duty = 0` (all doors) and
`lock_cmd = 0` (all doors locked) before any other action.

**PWM Frequency**: 20 kHz (hardware-configured, not controllable via software).

---

### 3.13 IF-012 — FMG → SKN: Fault State Bitmask (Cycle)

| Field | Value |
|-------|-------|
| **Interface ID** | IF-012 |
| **Direction** | FMG writes → SKN reads |
| **Data** | `fault_state_bitmask` (`uint32_t`) |
| **Period** | Every 20 ms scheduler cycle |
| **Traceability** | REQ-SAFE-006, SAS §5.1 IF-012 |

```c
uint32_t fault_state_bitmask; /* Bitmask of active fault codes (see FMG fault catalogue) */
```

**Bitmask Allocation**:

| Bit | Fault Code | Severity | Safe State Trigger |
|-----|-----------|----------|--------------------|
| 0 | `FAULT_SENSOR_DISAGREE` | CRITICAL | Yes |
| 1 | `FAULT_CAN_TIMEOUT` | CRITICAL | Yes |
| 2 | `FAULT_SPI_DISAGREE` | CRITICAL | Yes |
| 3 | `FAULT_WATCHDOG_NEAR_EXPIRY` | WARNING | No |
| 4 | `FAULT_OBSTACLE` | CRITICAL | Yes |
| 5 | `FAULT_LOCK_FAILED` | CRITICAL | Yes |
| 6 | `FAULT_CRC_ERROR` | WARNING | No |
| 7 | `FAULT_SEQ_COUNTER_JUMP` | WARNING | No |
| 8–31 | Reserved | — | — |

**SKN Policy**: Any bit flagged as "Safe State Trigger = Yes" causes SKN to set
`safe_state_active = 1` in the same cycle.

**Fail-safe Default**: `fault_state_bitmask = 0x00000001` (sensor_disagree set) at cold
start until FMG completes its own BIT (Built-In Test).

---

### 3.14 IF-013 — FMG → TCI: Fault Report to TCMS (CAN 0x202)

| Field | Value |
|-------|-------|
| **Interface ID** | IF-013 |
| **Direction** | FMG writes → TCI reads → CAN TX |
| **Data** | `fault_report_msg_t` |
| **Period** | On-event + repeated at 500 ms while fault active |
| **Traceability** | REQ-INT-008, SAS §5.1 IF-013 |

**Data Structure**:

```c
typedef struct {
    uint8_t  fault_code;     /* Primary fault code [0–255]                              */
    uint8_t  fault_severity; /* fault_severity_t enum value [0–4]                      */
    uint16_t fault_data;     /* Supplementary data (context-specific)                  */
    uint8_t  seq_counter;    /* Sequence counter [0–255]                               */
    uint16_t crc16;          /* CRC-16-CCITT (0x1021) over bytes 0–4                   */
} fault_report_msg_t;
```

Transmitted as CAN message 0x202. If fault persists: TCI retransmits at 500 ms intervals
until FMG clears the fault or system resets.

---

### 3.15 IF-014 — FMG → DGN: Event Log Entry

| Field | Value |
|-------|-------|
| **Interface ID** | IF-014 |
| **Direction** | FMG writes → DGN reads |
| **Data** | `event_log_entry_t` |
| **Period** | On-fault (asynchronous) |
| **Traceability** | REQ-SAFE-006, SAS §5.1 IF-014 |

**Data Structure** (`tdc_types.h`):

```c
typedef struct {
    uint32_t timestamp_ms;   /* System tick in milliseconds since startup               */
    uint8_t  source_comp;    /* Component ID (COMP-001=1, COMP-002=2, … COMP-008=8)    */
    uint8_t  event_code;     /* Event/fault code                                        */
    uint16_t data;           /* Supplementary context data                              */
    uint16_t crc16;          /* CRC-16-CCITT (0x1021) over bytes 0–7                   */
} event_log_entry_t;
```

DGN stores in circular buffer of 1,024 entries (IF-020). On buffer full: oldest entry
overwritten (ring buffer policy). SIL 1 — non-safety-critical path.

---

### 3.16 IF-015 — SKN → All: Safe State Broadcast (Cycle)

| Field | Value |
|-------|-------|
| **Interface ID** | IF-015 |
| **Direction** | SKN writes → All components read |
| **Data** | `safe_state_active` (`uint8_t`) |
| **Period** | Every 20 ms scheduler cycle |
| **Traceability** | REQ-SAFE-001, REQ-SAFE-003, SAS §5.1 IF-015 |

```c
uint8_t safe_state_active; /* 0 = normal operation, 1 = safe state commanded */
```

**Write Ownership**: `safe_state_active` is writable by **SKN ONLY**. No other component
may write this variable. All other components read it each cycle.

**Safe State Response by Component**:

| Component | Response to `safe_state_active == 1` |
|-----------|--------------------------------------|
| DSM | Halt all door FSMs; command motor stop; command lock; stay in current FSM state |
| TCI | Cease CAN door-open TX; transmit departure-interlock = 0 on 0x200 |
| SPM | Continue monitoring; log activation |
| OBD | Continue monitoring |
| FMG | Continue logging; flag safe state activation as event |
| DGN | Continue logging |

**Fail-safe Default**: `safe_state_active = 1` at cold start. Cleared by SKN BIT
completion only.

---

### 3.17 IF-016 — SKN → TCI: Departure Interlock Status (CAN 0x200, 100 ms)

| Field | Value |
|-------|-------|
| **Interface ID** | IF-016 |
| **Direction** | SKN writes → TCI reads → CAN TX |
| **Data** | `departure_interlock_ok` (`uint8_t`) |
| **Period** | 100 ms |
| **Traceability** | REQ-SAFE-001, REQ-INT-008, SAS §5.1 IF-016 |

```c
uint8_t departure_interlock_ok; /* 0 = interlock NOT cleared (unsafe), 1 = cleared (safe) */
```

**Write Ownership**: `departure_interlock_ok` writable by **SKN ONLY**.

**Conditions for `departure_interlock_ok = 1`**:
- All 4 doors: `door_states[d] == DOOR_CLOSED_AND_LOCKED`
- `safe_state_active == 0`
- `speed_interlock_active == 0`
- `fault_state_bitmask == 0` (no active safety faults)

TCI packages this as CAN message 0x200 (departure interlock, 100 ms periodic).

**CAN Frame 0x200 Format**:

| Byte | Field | Type | Value |
|------|-------|------|-------|
| 0 | `departure_interlock_ok` | `uint8_t` | 0/1 |
| 1 | `seq_counter` | `uint8_t` | [0–255] |
| 2–3 | `crc16` | `uint16_t` | CRC-16-CCITT |
| 4–7 | Padding | `uint8_t[4]` | 0x00 |

**Fail-safe Default**: `departure_interlock_ok = 0` (not cleared) at cold start.

---

### 3.18 IF-017 — SKN Ch A ↔ SKN Ch B: Cross-Channel State Synchronisation (SPI)

| Field | Value |
|-------|-------|
| **Interface ID** | IF-017 |
| **Direction** | Bidirectional (Ch A writes, Ch B writes; both read each other) |
| **Data** | `cross_channel_state_t` |
| **Period** | Every 20 ms scheduler cycle (step 6 of 8) |
| **Traceability** | REQ-INT-010, SAS §5.1 IF-017, OI-FMEA-001 |

**Data Structure** (`tdc_types.h`):

```c
typedef struct {
    uint16_t speed_kmh_x10;                   /* Speed from local TCMS CAN input          */
    door_state_t  door_states[MAX_DOORS];     /* Local door states                        */
    uint8_t       lock_states[MAX_DOORS];     /* Local lock states                        */
    uint8_t       obstacle_flags[MAX_DOORS];  /* Local obstacle detection                 */
    uint32_t      fault_flags;                /* Local fault bitmask                      */
    uint8_t       safety_decisions;           /* Bitmask: bit0=safe_state, bit1=interlock_ok */
    uint16_t      crc16;                      /* CRC-16-CCITT (0x1021) over all prior fields */
} cross_channel_state_t;
```

**SPI Protocol**:
- Speed: 10 Mbit/s
- Frame format: `cross_channel_state_t` as byte array, MSB first within each field
- CRC computed over all bytes preceding `crc16` field
- Timeout: 5 ms (`SPI_TIMEOUT_MS = 5`)

**Disagreement Handling (OI-FMEA-001 — SPI Transient Filter)**:

```
For each cycle at step 6:
  1. Transmit local cross_channel_state_t to peer channel
  2. Receive peer cross_channel_state_t
  3. Validate peer CRC-16-CCITT — if fail: increment spi_crc_fail_count[channel]
  4. Compare safety-critical fields:
     a. safe_state decisions (bit0 of safety_decisions)
     b. speed_interlock_active (derived from speed_kmh_x10)
     c. door_states[4], lock_states[4], obstacle_flags[4]
  5. If safety-data disagreement detected (step 4):
     → Set safe_state_active = 1 IMMEDIATELY (no filter)
  6. If SPI infrastructure fault (step 3 CRC fail):
     → Increment transient_fault_count
     → If transient_fault_count >= 3 consecutive cycles: Set safe_state_active = 1
     → If transient_fault_count resets to 0: Clear fault (3-cycle recovery)
```

**Rationale for Dual Policy**: Safety-data disagreements (step 5) indicate a real
system-state conflict that demands immediate response. SPI infrastructure faults (step 6)
may be transient electromagnetic interference; 3-cycle filter avoids nuisance trips while
bounding fault response to 60 ms (3 × 20 ms). This implements OI-FMEA-001.

---

### 3.19 IF-018 — TCI → DSM: Door Commands from TCMS (On-Event)

| Field | Value |
|-------|-------|
| **Interface ID** | IF-018 |
| **Direction** | TCI writes → DSM reads |
| **Data** | `door_command_t` |
| **Period** | On-event (CAN RX) |
| **Traceability** | REQ-INT-007, REQ-INT-008, SAS §5.1 IF-018 |

**Data Structure**:

```c
typedef struct {
    uint8_t  command_type;   /* 0=OPEN, 1=CLOSE, 2=MODE_CHANGE, 3=EMERGENCY_STOP     */
    uint8_t  door_mask;      /* Bitmask: bit[d]=1 means command applies to door d      */
    uint8_t  mode;           /* New mode if command_type==2 (op_mode_t value)         */
    uint8_t  seq_counter;    /* Sequence counter [0–255]                               */
    uint16_t crc16;          /* CRC-16-CCITT (0x1021) over bytes 0–3                  */
} door_command_t;
```

**CAN Mapping**:

| CAN ID | Command Type | Description |
|--------|-------------|-------------|
| 0x101 | OPEN (0) | Door open command (selective by door_mask) |
| 0x102 | CLOSE (1) | Door close command |
| 0x103 | MODE_CHANGE (2) | Operational mode change (`op_mode_t`) |
| 0x104 | EMERGENCY_STOP (3) | Emergency stop — all doors halt immediately |

**Gate**: DSM checks `speed_interlock_active` and `safe_state_active` before executing
OPEN or CLOSE commands. EMERGENCY_STOP is executed unconditionally.

---

### 3.20 IF-019 — HAL → SKN: Watchdog Status (Cycle)

| Field | Value |
|-------|-------|
| **Interface ID** | IF-019 |
| **Direction** | HAL writes → SKN reads |
| **Data** | `watchdog_status` (`uint8_t`) |
| **Period** | Every 20 ms scheduler cycle |
| **Traceability** | REQ-INT-006, SAS §5.1 IF-019 |

```c
uint8_t watchdog_status; /* 0 = OK, 1 = near-expiry warning (> 40 ms since last refresh) */
```

HAL calls `HAL_Watchdog_Refresh()` each cycle (step 1). If the call fails or the
hardware counter exceeds 40 ms without refresh, HAL sets `watchdog_status = 1`.

SKN reads `watchdog_status` each cycle. If `watchdog_status == 1`, SKN logs
`FAULT_WATCHDOG_NEAR_EXPIRY` (bit 3 of fault bitmask) — non-safe-state-triggering.
Actual watchdog expiry (> 50 ms) causes hardware reset — no software intervention.

**Watchdog Timing**:

| Parameter | Value | Source |
|-----------|-------|--------|
| HW timeout | 50 ms | REQ-INT-006 |
| SW refresh interval | 40 ms (`WDG_REFRESH_MS`) | REQ-INT-006, SDS §1.4 |
| Warning threshold | 40 ms | This document |
| Scheduler cycle | 20 ms | CYCLE_MS |

---

### 3.21 IF-020 — DGN → SPI Flash: Event Log Circular Buffer

| Field | Value |
|-------|-------|
| **Interface ID** | IF-020 |
| **Direction** | DGN writes → SPI Flash storage |
| **Data** | `event_log_entry_t[1024]` circular buffer |
| **Period** | Deferred (not time-critical) |
| **Traceability** | REQ-SAFE-006, SAS §5.1 IF-020 |

**Buffer Configuration**:

```c
#define EVENT_LOG_SIZE   1024U
event_log_entry_t event_log[EVENT_LOG_SIZE]; /* Statically allocated circular buffer */
uint16_t          event_log_head;            /* Write index [0–1023]                 */
uint16_t          event_log_count;           /* Number of entries written (max 1024) */
```

**Write Policy**: DGN writes to SPI Flash asynchronously (deferred write-back). In-memory
buffer is always up-to-date; Flash write may lag by ≤ 5 cycles (100 ms). SIL 1 path —
Flash write errors are logged but do not trigger safe state.

**SPI Flash Interface**:
```c
error_t DGN_WriteLogEntry(const event_log_entry_t *entry);
error_t DGN_ReadLogEntry(uint16_t index, event_log_entry_t *entry);
error_t DGN_FlushLog(void);
```

---

## 4. EXTERNAL INTERFACES

### 4.1 EXT-001 / REQ-INT-001 — PWM Motor Actuator

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-001 |
| **SRS Reference** | REQ-INT-001 |
| **Direction** | Software → Hardware |
| **Hardware** | Motor PWM + direction GPIO per door |
| **HAL Functions** | `HAL_PWM_SetDutyCycle`, `HAL_GPIO_SetMotorDirection` |

**Interface Specification**:

| Parameter | Value | Notes |
|-----------|-------|-------|
| PWM frequency | 20 kHz | Fixed; hardware-configured |
| Duty cycle range | 0–100% (`uint8_t`) | 0 = motor stopped |
| Direction encoding | 0 = open, 1 = close | GPIO level |
| Number of channels | 4 (one per door) | |
| Fail-safe state | duty = 0, direction = close (1) | Motor stopped, spring-locked |

**Error Handling**: `HAL_PWM_SetDutyCycle` returns `ERR_HW_FAULT` on timer peripheral
failure. Caller (DSM) must: stop motor (`duty = 0`), log fault to FMG, trigger safe state.

---

### 4.2 EXT-002 / REQ-INT-002 — Door Position Sensors (GPIO)

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-002 |
| **SRS Reference** | REQ-INT-002 |
| **Direction** | Hardware → Software |
| **Hardware** | 2 sensors × 4 doors = 8 GPIO inputs |
| **HAL Function** | `HAL_GPIO_ReadPositionSensor` |
| **Polling Period** | 20 ms |

**Interface Specification**:

| Parameter | Value |
|-----------|-------|
| Sensor type | Reed switch / proximity, 24 V logic |
| Logic level | 1 = sensor activated (door at limit), 0 = not activated |
| Voting logic | 2oo2 (both must agree) — implemented in DSM |
| Input impedance | 10 kΩ pull-down |
| Debounce | 2 consecutive same readings (40 ms) |
| Fail-safe | Both sensors disagree → `DOOR_FAULT`, ERR_SENSOR_DISAGREE |

**Function Signature**:
```c
error_t HAL_GPIO_ReadPositionSensor(uint8_t door_id, uint8_t sensor_idx,
                                     uint8_t *value);
```
- `sensor_idx`: 0 = sensor A, 1 = sensor B
- `*value`: 1 = activated, 0 = not activated
- Returns: `ERROR_SUCCESS` or `ERR_HW_FAULT`

---

### 4.3 EXT-003 / REQ-INT-003 — Obstacle Sensors (GPIO + ISR)

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-003 |
| **SRS Reference** | REQ-INT-003 |
| **Direction** | Hardware → Software |
| **Hardware** | 2 sensors × 4 doors = 8 GPIO inputs (interrupt-capable) |
| **HAL Function** | `HAL_GPIO_ReadObstacleSensor` + ISR `OBD_ObstacleISR` |
| **Interrupt Latency** | ≤ 1 ms (REQ-INT-003) |

**Interface Specification**:

| Parameter | Value |
|-----------|-------|
| Sensor type | Optical / IR / pressure, active-high |
| Trigger mode | Rising-edge interrupt + polled confirmation |
| Voting logic | 1oo2 (either sensor triggers detection) |
| ISR behaviour | Set `hal_obs_isr_flag[door]`; do NOT call HAL functions |
| Debounce / clear | 3 consecutive clear readings (60 ms) to clear obstacle flag |
| Fail-safe | Any detection → immediate stop and lock within 1 ms (ISR) |

**ISR Signature** (registered at HAL initialisation):
```c
void OBD_ObstacleISR(uint8_t door_id); /* Called from GPIO IRQ handler */
```

**Polled Function**:
```c
error_t HAL_GPIO_ReadObstacleSensor(uint8_t door_id, uint8_t sensor_idx,
                                     uint8_t *value);
```

---

### 4.4 EXT-004 / REQ-INT-004 — Lock Actuators (GPIO)

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-004 |
| **SRS Reference** | REQ-INT-004 |
| **Direction** | Software → Hardware |
| **Hardware** | 1 lock actuator × 4 doors = 4 GPIO outputs |
| **HAL Function** | `HAL_GPIO_SetLockActuator` |

**Interface Specification**:

| Parameter | Value |
|-----------|-------|
| Voltage level | 24 V DC |
| Active-LOW encoding | GPIO LOW = unlock signal; GPIO HIGH (or Hi-Z) = locked (spring return) |
| Fail-safe | De-energised = spring-locked; no power required to maintain lock |
| Response time | ≤ 100 ms mechanical engagement |

**Function Signature**:
```c
error_t HAL_GPIO_SetLockActuator(uint8_t door_id, uint8_t unlock);
```
- `unlock`: 0 = lock (safe), 1 = unlock
- Returns: `ERROR_SUCCESS` or `ERR_HW_FAULT`

---

### 4.5 EXT-005 / REQ-INT-005 — Lock Position Sensors (GPIO)

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-005 |
| **SRS Reference** | REQ-INT-005 |
| **Direction** | Hardware → Software |
| **Hardware** | 2 sensors × 4 doors = 8 GPIO inputs |
| **HAL Function** | `HAL_GPIO_ReadLockSensor` |
| **Polling Period** | 20 ms |

**Interface Specification**:

| Parameter | Value |
|-----------|-------|
| Logic level | 1 = locked, 0 = unlocked |
| Voting logic | 2oo2 (both must agree to confirm locked state) |
| Fail-safe | Sensors disagree → `lock_states[d] = 0` (unlocked) → departure interlock held |

**Function Signature**:
```c
error_t HAL_GPIO_ReadLockSensor(uint8_t door_id, uint8_t sensor_idx,
                                 uint8_t *value);
```

---

### 4.6 EXT-006 / REQ-INT-006 — Independent Watchdog (IWDG)

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-006 |
| **SRS Reference** | REQ-INT-006 |
| **Direction** | Software → Hardware (refresh); Hardware → System (reset on expiry) |
| **Hardware** | STM32 IWDG (Independent Watchdog) |
| **HAL Function** | `HAL_Watchdog_Refresh` |

**Interface Specification**:

| Parameter | Value |
|-----------|-------|
| Watchdog type | Independent (not halted by debug) |
| Timeout | 50 ms |
| Refresh interval | 40 ms (`WDG_REFRESH_MS`) |
| Refresh location | Scheduler cycle start (step 1 of 8) |
| On expiry | Hardware reset — no software recovery path |
| Fail-safe | Expiry causes reset; safe state enforced on restart via cold-start defaults |

**Function Signature**:
```c
error_t HAL_Watchdog_Refresh(void);
```
Returns: `ERROR_SUCCESS` or `ERR_WATCHDOG` (peripheral fault).

---

### 4.7 EXT-007 / REQ-INT-007 — CAN Bus RX from TCMS

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-007 |
| **SRS Reference** | REQ-INT-007 |
| **Direction** | TCMS → TDC software (via CAN controller) |
| **Physical Layer** | CAN 2.0B, bit rate TBD (typically 250 kbit/s or 500 kbit/s) |
| **HAL Module** | MOD-HAL-003 (CAN controller) |

**CAN RX Message Catalogue**:

| CAN ID | Name | Period | DLC | Contents |
|--------|------|--------|-----|---------|
| 0x100 | TCMS Speed | 100 ms | 5 | `speed_kmh_x10` (2B) + `seq_counter` (1B) + `crc16` (2B) |
| 0x101 | Door Open Cmd | On-event | 5 | `door_mask` (1B) + `seq_counter` (1B) + `crc16` (2B) + pad |
| 0x102 | Door Close Cmd | On-event | 5 | `door_mask` (1B) + `seq_counter` (1B) + `crc16` (2B) + pad |
| 0x103 | Mode Change | On-event | 5 | `mode` (1B) + `seq_counter` (1B) + `crc16` (2B) + pad |
| 0x104 | Emergency Stop | On-event | 3 | `seq_counter` (1B) + `crc16` (2B) |

**Reception Rules**:
1. CRC-16-CCITT (0x1021) must pass — frame discarded on CRC failure
2. Sequence counter must increment by 1 — jump > 1 logs `FAULT_SEQ_COUNTER_JUMP`
3. Speed message timeout: if no 0x100 within `CAN_TIMEOUT_MS = 200 ms` → `ERR_COMM_TIMEOUT`
   → SPM treats speed as unknown → interlock active
4. Emergency stop (0x104): no sequence check; processed immediately

**Error Accumulation**: After 3 consecutive CRC failures on same ID → `FAULT_CAN_TIMEOUT`
logged and interlock activated.

---

### 4.8 EXT-008 / REQ-INT-008 — CAN Bus TX to TCMS

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-008 |
| **SRS Reference** | REQ-INT-008 |
| **Direction** | TDC software → TCMS (via CAN controller) |

**CAN TX Message Catalogue**:

| CAN ID | Name | Period | DLC | Contents |
|--------|------|--------|-----|---------|
| 0x200 | Departure Interlock | 100 ms | 4 | `departure_interlock_ok` (1B) + `seq_counter` (1B) + `crc16` (2B) |
| 0x201 | Door Status | 100 ms | 8 | `door_state_summary` (1B) + `lock_state_summary` (1B) + `fault_flags` (2B) + `seq_counter` (1B) + `crc16` (2B) + pad |
| 0x202 | Fault Report | On-event + 500 ms | 7 | `fault_code` (1B) + `fault_severity` (1B) + `fault_data` (2B) + `seq_counter` (1B) + `crc16` (2B) |
| 0x203 | Mode Status | On-change + 1 s | 4 | `current_mode` (1B) + `seq_counter` (1B) + `crc16` (2B) + pad |

**Transmission Rules**:
1. Sequence counter incremented for each transmission per message ID
2. CRC-16-CCITT (0x1021) appended to all messages
3. Departure interlock (0x200): transmitted at 100 ms even if `departure_interlock_ok`
   does not change — TCMS must receive confirmation within its supervision window
4. Fault report (0x202): first transmission on fault detection, then repeated every 500 ms
   while fault is active

---

### 4.9 EXT-009 / REQ-INT-009 — RS-485 DDU Interface

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-009 |
| **SRS Reference** | REQ-INT-009 |
| **Direction** | Bidirectional (TDC ↔ DDU) |
| **Physical Layer** | RS-485 multi-drop, 115.2 kbit/s, 8N1 |
| **HAL Module** | MOD-HAL-004 |
| **Timeout** | 40 ms |

**Frame Format**:

| Byte | Field | Value / Description |
|------|-------|---------------------|
| 0 | SOF | 0xAA (Start of Frame) |
| 1 | Address | DDU address [0x01–0x0F]; 0x00 = broadcast |
| 2 | Length | Payload length [1–16] |
| 3–N | Payload | Command or status data |
| N+1 | Seq | Sequence counter [0–255] |
| N+2–N+3 | CRC16 | CRC-16-CCITT (0x1021) over bytes 0 through N+1 |
| N+4 | EOF | 0x55 (End of Frame) |

**TDC → DDU Commands**:

| Command Code | Description | Payload |
|---|---|---|
| 0x01 | Door status update | `door_states[4]` + `lock_states[4]` |
| 0x02 | Mode update | `current_mode` (1B) |
| 0x03 | Fault indication | `fault_code` (1B) + `fault_severity` (1B) |

**DDU → TDC Commands** (informational only — not safety-critical):

| Command Code | Description |
|---|---|
| 0x81 | DDU status alive |
| 0x82 | DDU display acknowledgement |

**Error Handling**: Response timeout > 40 ms → retry once; second timeout → log
`ERR_COMM_TIMEOUT` to FMG (non-safe-state-triggering for DDU).

---

### 4.10 EXT-010 / REQ-INT-010 — Cross-Channel SPI Interface

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-010 |
| **SRS Reference** | REQ-INT-010 |
| **Direction** | Bidirectional (Ch A ↔ Ch B) |
| **Physical Layer** | SPI, 10 Mbit/s, full-duplex |
| **HAL Module** | MOD-HAL-004 (SPI side) |
| **Timeout** | 5 ms |

Cross-channel SPI carries `cross_channel_state_t` — see IF-017 (§3.18) for full protocol
specification including the OI-FMEA-001 transient filter algorithm.

**SPI Electrical Interface**:

| Signal | Description |
|--------|-------------|
| MOSI (Ch A) | Master output from Channel A → Channel B |
| MISO (Ch A) | Master input = Channel B output |
| SCK | 10 MHz SPI clock (Channel A is master) |
| CS | Active-LOW chip select |

**Frame Size**: `sizeof(cross_channel_state_t)` bytes. Actual size must be computed at
compile time and is bounded by static struct — no dynamic sizing.

---

### 4.11 EXT-011 / REQ-INT-011 — Emergency Release (GPIO)

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-011 |
| **SRS Reference** | REQ-INT-011 |
| **Direction** | Hardware → Software |
| **Hardware** | 1 GPIO per door = 4 inputs |
| **Polling Period** | 20 ms |

**Interface Specification**:

| Parameter | Value |
|-----------|-------|
| Trigger | Active-LOW mechanical switch (emergency release lever) |
| Response action | Unlock door regardless of operational mode |
| TCMS notification | CAN message 0x202 fault code `EMERGENCY_RELEASE_ACTIVATED` within 200 ms |
| Safety guard | If `current_speed_kmh_x10 > 50` (5 km/h): block release + log `ERR_NOT_PERMITTED` |
| Logging | Every activation logged via FMG → DGN (IF-014) |

**Function Signature**:
```c
error_t HAL_GPIO_ReadEmergencyRelease(uint8_t door_id, uint8_t *activated);
```

---

### 4.12 EXT-012 / REQ-INT-012 — Driver Control Panel (GPIO)

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-012 |
| **SRS Reference** | REQ-INT-012 |
| **Direction** | Bidirectional (discrete I/O) |
| **Hardware** | 24 V discrete I/O, read every 20 ms |
| **HAL Module** | MOD-HAL-001 (GPIO) |

**Inputs (Panel → TDC)**:

| Signal | Description | Logic |
|--------|-------------|-------|
| DCP_DOOR_OPEN | Driver open command | Active-HIGH |
| DCP_DOOR_CLOSE | Driver close command | Active-HIGH |
| DCP_MODE_SEL | Mode selection switch | Multi-position encoder |
| DCP_EMRG_STOP | Emergency stop button | Active-LOW, latched |

**Outputs (TDC → Panel)**:

| Signal | Description | Logic |
|--------|-------------|-------|
| DCP_LED_CLOSED | Door closed indicator | Active-HIGH LED |
| DCP_LED_LOCKED | Door locked indicator | Active-HIGH LED |
| DCP_LED_FAULT | Fault indicator | Active-HIGH LED, blinking on fault |
| DCP_LED_SAFE | Safe state indicator | Active-HIGH LED |

**Function Signatures**:
```c
error_t HAL_GPIO_ReadDCP(uint8_t signal_id, uint8_t *value);
error_t HAL_GPIO_WriteDCP(uint8_t signal_id, uint8_t value);
```

---

### 4.13 EXT-013 / REQ-INT-013 — Diagnostics Port (USB/RS-232)

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-013 |
| **SRS Reference** | REQ-INT-013 |
| **Direction** | Bidirectional (read commands from tool; send log data) |
| **Physical Layer** | USB CDC or RS-232, 115.2 kbit/s, 8N1 |
| **SIL Level** | SIL 1 (diagnostics only — not safety-critical) |
| **HAL Module** | MOD-HAL-004 |

**Operating Mode Restrictions**:

| Mode | Read Access | Write Access | Notes |
|------|-------------|--------------|-------|
| `MODE_NORMAL` | Yes (log read) | **No** | Software interlocked — write commands rejected |
| `MODE_DIAGNOSTIC` | Yes | Yes | Full access; requires physical key switch |
| `MODE_MAINTENANCE` | Yes | Yes | Maintenance commands only |
| `MODE_DOOR_DISABLED` | Yes | No | Read-only |

**Protocol**: Simple ASCII or binary command/response. Not safety-critical — no CRC
requirement (recommended for robustness). Frame format: `[CMD_ID][LEN][DATA][LF]`.

**Fail-safe**: Diagnostics port access must not affect `safe_state_active`,
`departure_interlock_ok`, or any safety-critical shared datum. DGN MUST NOT modify
any variable owned by SKN, SPM, DSM, or OBD.

---

### 4.14 ADC Interface — Motor Current Sensing

| Field | Value |
|-------|-------|
| **Interface ID** | EXT-ADC |
| **SRS Reference** | REQ-SAFE-009 (obstacle-by-force / OBD) |
| **Direction** | Hardware → Software |
| **Hardware** | ADC channel per motor |
| **HAL Function** | `HAL_ADC_ReadMotorCurrent` |
| **Sampling Period** | Every 20 ms scheduler cycle |

**Interface Specification**:

| Parameter | Value |
|-----------|-------|
| ADC resolution | 12-bit (0–4095 = 0–full scale) |
| Current range | 0–20 A (linear mapping: `current_A = (adc_value * 20U) / 4095U`) |
| Overcurrent threshold | Configurable; default 15 A |
| Use in OBD | Force-based obstacle detection (REQ-SAFE-009) |
| Fail-safe | ADC fault → assume overcurrent (15 A) → obstacle flag set |

**Function Signature**:
```c
error_t HAL_ADC_ReadMotorCurrent(uint8_t door_id, uint16_t *adc_raw);
```

---

## 5. DATA TYPE DEFINITIONS

All types defined in `tdc_types.h`. This section provides the authoritative
interface-level specification of each type.

### 5.1 `error_t` — Error Return Code

```c
typedef enum {
    ERROR_SUCCESS        = 0,  /* Operation successful                                */
    ERR_NULL_PTR         = 1,  /* NULL pointer passed to function                     */
    ERR_RANGE            = 2,  /* Parameter out of valid range                        */
    ERR_TIMEOUT          = 3,  /* Operation timed out                                 */
    ERR_CRC              = 4,  /* CRC validation failed                               */
    ERR_HW_FAULT         = 5,  /* Hardware peripheral fault                           */
    ERR_INVALID_STATE    = 6,  /* FSM / system state does not permit operation        */
    ERR_NOT_PERMITTED    = 7,  /* Operation not permitted (e.g., speed guard)         */
    ERR_SENSOR_DISAGREE  = 8,  /* Redundant sensor values disagree (2oo2 violation)  */
    ERR_COMM_TIMEOUT     = 9,  /* Communication link timeout                          */
    ERR_WATCHDOG         = 10  /* Watchdog peripheral fault                           */
} error_t;
```

**Usage Rule**: All HAL functions and safety-critical module functions MUST return
`error_t`. Callers MUST check the return value — discarding is a MISRA C:2012 violation.

---

### 5.2 `door_state_t` — Physical Door State

```c
typedef enum {
    DOOR_UNKNOWN          = 0, /* State indeterminate (startup / sensor fault)        */
    DOOR_FULLY_OPEN       = 1, /* Both position sensors: open limit activated         */
    DOOR_INTERMEDIATE     = 2, /* Door in motion or between limits                   */
    DOOR_FULLY_CLOSED     = 3, /* Both position sensors: closed limit activated       */
    DOOR_CLOSED_AND_LOCKED= 4, /* Fully closed + both lock sensors: locked            */
    DOOR_FAULT            = 5  /* Sensor disagreement or mechanical fault             */
} door_state_t;
```

**Departure Interlock Rule**: `departure_interlock_ok = 1` requires ALL doors to be in
state `DOOR_CLOSED_AND_LOCKED` (value 4). Any other state → interlock held.

---

### 5.3 `door_fsm_state_t` — Door FSM Internal State

```c
typedef enum {
    FSM_IDLE             = 0,  /* No active command; door at rest                    */
    FSM_OPENING          = 1,  /* Door moving toward open limit                      */
    FSM_OPEN_LIMIT       = 2,  /* Door reached open limit; motor stopped             */
    FSM_CLOSING          = 3,  /* Door moving toward closed limit                    */
    FSM_LOCKING          = 4,  /* Door reached closed limit; lock actuator engaging  */
    FSM_LOCKED           = 5,  /* Door confirmed closed and locked                   */
    FSM_OBSTACLE_HALT    = 6,  /* Obstacle detected; motor stopped; awaiting command */
    FSM_FAULT            = 7,  /* Unrecoverable fault; awaiting reset                */
    FSM_SAFE_STATE       = 8   /* Safe state commanded by SKN                        */
} door_fsm_state_t;
```

---

### 5.4 `fault_severity_t` — Fault Severity Level

```c
typedef enum {
    FAULT_NONE     = 0,  /* No fault                                                  */
    FAULT_INFO     = 1,  /* Informational — no action required                        */
    FAULT_WARNING  = 2,  /* Warning — log and monitor; no safe state                  */
    FAULT_ERROR    = 3,  /* Error — degraded operation; may trigger safe state        */
    FAULT_CRITICAL = 4   /* Critical — immediate safe state required                  */
} fault_severity_t;
```

---

### 5.5 `op_mode_t` — Operational Mode

```c
typedef enum {
    MODE_NORMAL       = 0, /* Normal revenue service                                  */
    MODE_DIAGNOSTIC   = 1, /* Diagnostic mode — full data access                     */
    MODE_MAINTENANCE  = 2, /* Maintenance mode — controlled manual override           */
    MODE_DOOR_DISABLED= 3  /* Door disabled — all door operations inhibited           */
} op_mode_t;
```

**Mode Transition Authority**: Mode changes may only be commanded by TCMS (CAN 0x103)
or Driver Control Panel (DCP_MODE_SEL). SKN validates mode change requests against
current safety state before permitting transition.

---

### 5.6 `cross_channel_state_t` — SPI Cross-Channel Frame

See IF-017 (§3.18) for full structure definition and usage.

**Size Note**: Must be a fixed-size structure (no variable-length fields, no padding
gaps that could change between compilers). A `static_assert` on `sizeof(cross_channel_state_t)`
shall be present in the implementation.

---

### 5.7 `tcms_speed_msg_t` — TCMS Speed CAN Message

See IF-001 (§3.2) for full structure definition and usage.

---

### 5.8 `event_log_entry_t` — Diagnostics Event Log Entry

See IF-014 (§3.15) and IF-020 (§3.21) for full structure definition and usage.

---

### 5.9 Constants

| Constant | Type | Value | Description |
|----------|------|-------|-------------|
| `MAX_DOORS` | `uint8_t` | 4 | Maximum number of door units |
| `SPEED_THRESHOLD` | `uint16_t` | 50 | Speed limit for door operation (0.1 km/h units = 5 km/h) |
| `CAN_TIMEOUT_MS` | `uint16_t` | 200 | CAN supervision timeout (ms) |
| `WDG_REFRESH_MS` | `uint16_t` | 40 | Watchdog refresh interval (ms) |
| `CYCLE_MS` | `uint8_t` | 20 | Scheduler cycle period (ms) |
| `SPI_TIMEOUT_MS` | `uint8_t` | 5 | Cross-channel SPI timeout (ms) |
| `RS485_TIMEOUT_MS` | `uint8_t` | 40 | DDU RS-485 response timeout (ms) |
| `EVENT_LOG_SIZE` | `uint16_t` | 1024 | Event log circular buffer depth |
| `CRC16_POLY` | `uint16_t` | 0x1021 | CRC-16-CCITT polynomial |
| `CRC16_INIT` | `uint16_t` | 0xFFFF | CRC-16-CCITT initial value |

---

## 6. ERROR HANDLING

### 6.1 Error Handling Policy

All error handling in the TDC follows these rules, consistent with SDS §1.4:

1. **Return code check mandatory**: Every function returning `error_t` MUST have its
   return value checked by the caller. Implicit discards are prohibited (MISRA C).
2. **No error hiding**: Errors must be propagated upward or explicitly handled — no
   silent discard.
3. **Fault logging**: All errors at severity WARNING or above MUST be logged via FMG
   (IF-014) within one scheduler cycle.
4. **Safe state escalation**: Errors with `fault_severity == FAULT_CRITICAL` MUST cause
   `safe_state_active = 1` via SKN within one scheduler cycle (20 ms).
5. **No recovery from hardware reset**: Watchdog expiry causes hardware reset. Post-reset
   boot must return to safe defaults (cold-start initialisation).

### 6.2 Per-Interface Error Summary

| Interface | Error Condition | Error Code | Severity | Safe State? |
|-----------|----------------|------------|----------|-------------|
| IF-001 (CAN RX speed) | CRC failure | `ERR_CRC` | WARNING | No |
| IF-001 (CAN RX speed) | Timeout > 200 ms | `ERR_COMM_TIMEOUT` | CRITICAL | Yes |
| IF-004 (GPIO sensors) | Read failure | `ERR_HW_FAULT` | CRITICAL | Yes |
| IF-004 (GPIO sensors) | Sensor disagree | `ERR_SENSOR_DISAGREE` | CRITICAL | Yes |
| IF-005 (obstacle) | Read failure | `ERR_HW_FAULT` | CRITICAL | Yes |
| IF-010 (lock actuator) | Actuator fault | `ERR_HW_FAULT` | CRITICAL | Yes |
| IF-011 (motor PWM) | PWM fault | `ERR_HW_FAULT` | CRITICAL | Yes |
| IF-017 (SPI) | CRC failure (< 3 cycles) | `ERR_CRC` | WARNING | No (filter) |
| IF-017 (SPI) | CRC failure (≥ 3 cycles) | `ERR_CRC` | CRITICAL | Yes |
| IF-017 (SPI) | Safety data disagree | `ERR_SENSOR_DISAGREE` | CRITICAL | Yes (immediate) |
| IF-019 (watchdog) | Near-expiry | `ERR_WATCHDOG` | WARNING | No |
| EXT-007 (CAN RX) | Seq counter jump | — | WARNING | No |
| EXT-009 (RS-485) | Response timeout | `ERR_COMM_TIMEOUT` | WARNING | No |

---

## 7. INTERFACE CONSTRAINTS AND TIMING

### 7.1 Scheduler Execution Order

All software executes in a deterministic fixed-period scheduler (20 ms cycle). The
scheduler step order determines data freshness across interfaces:

| Step | Component | Action |
|------|-----------|--------|
| 1 | HAL | Watchdog refresh (`HAL_Watchdog_Refresh`) → IF-019 |
| 2 | HAL | Read all GPIO sensors → IF-004, IF-005 |
| 3 | HAL | Read ADC motor current → EXT-ADC |
| 4 | TCI | Process CAN RX queue → IF-001, IF-018 |
| 5 | SPM | Compute speed interlock → IF-002, IF-003 |
| 6 | SKN | Cross-channel SPI exchange → IF-017 |
| 7 | OBD | Evaluate obstacle flags → IF-006, IF-007 |
| 8 | DSM | Run door FSMs → IF-008, IF-010, IF-011 |
| 9 | FMG | Aggregate faults → IF-012, IF-013, IF-014 |
| 10 | SKN | Final safety arbitration → IF-015, IF-016 |
| 11 | TCI | CAN TX and RS-485 TX → EXT-008, EXT-009 |
| 12 | DGN | Deferred log flush → IF-020 |

**Data Latency**: Maximum latency from sensor input to motor command = one full scheduler
cycle = 20 ms. Maximum latency from sensor input to TCMS notification = one cycle + CAN
TX = 20 ms + propagation.

### 7.2 Timing Constraints Summary

| Interface | Timing Constraint | Reference |
|-----------|------------------|-----------|
| IF-001 CAN speed | 100 ms period; 200 ms timeout | REQ-INT-007 |
| IF-003 speed interlock | ≤ 20 ms to apply after TCMS update | Architecture rule |
| IF-005 obstacle ISR | ≤ 1 ms ISR latency | REQ-INT-003 |
| IF-006 obstacle to motor stop | ≤ 20 ms (one cycle) | REQ-SAFE-004 |
| IF-015 safe state broadcast | ≤ 20 ms (same cycle) | REQ-SAFE-001 |
| IF-016 departure interlock TX | 100 ms periodic | REQ-INT-008 |
| IF-017 cross-channel SPI | ≤ 5 ms per transaction | REQ-INT-010 |
| EXT-006 watchdog refresh | Every 40 ms; timeout at 50 ms | REQ-INT-006 |
| EXT-007 CAN speed timeout | 200 ms | REQ-INT-007 |
| EXT-009 RS-485 response | 40 ms | REQ-INT-009 |
| EXT-011 emergency release notification | ≤ 200 ms to TCMS | REQ-INT-011 |

### 7.3 Shared Resource Access Rules

| Shared Resource | Exclusive Writer | Readers |
|----------------|-----------------|---------|
| `safe_state_active` | SKN only | All components |
| `departure_interlock_ok` | SKN only | TCI |
| `door_states[]`, `lock_states[]` | DSM only | SKN, TCI |
| `speed_interlock_active` | SPM only | SKN, DSM |
| `obstacle_flags[]` | OBD only | DSM, SKN |
| `fault_state_bitmask` | FMG only | SKN |
| CAN bus | TCI exclusive (TX) | HAL (RX interrupt) |
| Cross-channel SPI | SKN exclusive (one per cycle) | — |
| SPI Flash | DGN exclusive (write) | DGN (read) |

**Write Ownership Rule**: Multiple writers to the same datum are prohibited. Any
violation of write ownership constitutes a design defect (architectural integrity rule).

---

## 8. INTERFACE TRACEABILITY

### 8.1 SRS Requirements → Interfaces

| SRS Requirement | Interface(s) | Component(s) |
|----------------|-------------|-------------|
| REQ-INT-001 (PWM motor) | IF-011, EXT-001 | DSM, HAL |
| REQ-INT-002 (position sensors) | IF-004, EXT-002 | HAL, DSM |
| REQ-INT-003 (obstacle sensors) | IF-005, IF-006, IF-007, EXT-003 | HAL, OBD, DSM, SKN |
| REQ-INT-004 (lock actuators) | IF-010, EXT-004 | DSM, HAL |
| REQ-INT-005 (lock sensors) | IF-004, EXT-005 | HAL, DSM |
| REQ-INT-006 (watchdog) | IF-019, EXT-006 | HAL, SKN |
| REQ-INT-007 (CAN RX TCMS) | IF-001, IF-018, EXT-007 | TCI, SPM, DSM |
| REQ-INT-008 (CAN TX TCMS) | IF-009, IF-013, IF-016, EXT-008 | DSM, FMG, SKN, TCI |
| REQ-INT-009 (RS-485 DDU) | IF-009, EXT-009 | TCI |
| REQ-INT-010 (cross-channel SPI) | IF-017, EXT-010 | SKN |
| REQ-INT-011 (emergency release) | EXT-011 | HAL, DSM, TCI |
| REQ-INT-012 (driver control panel) | EXT-012 | HAL, TCI, DSM |
| REQ-INT-013 (diagnostics port) | IF-020, EXT-013 | DGN |

### 8.2 SAS Internal Interfaces → SIS Sections

| SAS Interface ID | SIS Section | Description |
|-----------------|-------------|-------------|
| IF-001 | §3.2 | TCI → SPM: TCMS speed message |
| IF-002 | §3.3 | SPM → SKN: speed interlock gate |
| IF-003 | §3.4 | SPM → DSM: speed gate |
| IF-004 | §3.5 | HAL GPIO → DSM: position + lock sensors |
| IF-005 | §3.6 | HAL GPIO → OBD: obstacle sensors |
| IF-006 | §3.7 | OBD → DSM: obstacle flags |
| IF-007 | §3.8 | OBD → SKN: obstacle flags for safety arbitration |
| IF-008 | §3.9 | DSM → SKN: door and lock states |
| IF-009 | §3.10 | DSM → TCI: per-door status |
| IF-010 | §3.11 | DSM → HAL: lock actuator command |
| IF-011 | §3.12 | DSM → HAL: motor PWM and direction |
| IF-012 | §3.13 | FMG → SKN: fault state bitmask |
| IF-013 | §3.14 | FMG → TCI: fault report to TCMS |
| IF-014 | §3.15 | FMG → DGN: event log entry |
| IF-015 | §3.16 | SKN → All: safe state broadcast |
| IF-016 | §3.17 | SKN → TCI: departure interlock status |
| IF-017 | §3.18 | SKN Ch A ↔ Ch B: cross-channel SPI |
| IF-018 | §3.19 | TCI → DSM: door commands from TCMS |
| IF-019 | §3.20 | HAL → SKN: watchdog status |
| IF-020 | §3.21 | DGN → SPI Flash: event log circular buffer |

### 8.3 SAS Components → Interfaces Owned / Used

| Component | Interfaces Written | Interfaces Read |
|-----------|-------------------|----------------|
| SKN (COMP-001) | IF-015, IF-016, IF-017 (own side) | IF-002, IF-007, IF-008, IF-012, IF-017 (peer), IF-019 |
| SPM (COMP-002) | IF-002, IF-003 | IF-001 |
| DSM (COMP-003) | IF-008, IF-009, IF-010, IF-011 | IF-003, IF-004, IF-006, IF-015, IF-018 |
| OBD (COMP-004) | IF-006, IF-007 | IF-005 |
| TCI (COMP-005) | IF-001, IF-018, EXT-008, EXT-009 | IF-009, IF-013, IF-016 |
| FMG (COMP-006) | IF-012, IF-013, IF-014 | — (aggregates from all) |
| DGN (COMP-007) | IF-020 | IF-014 |
| HAL (COMP-008) | IF-004, IF-005, IF-019, EXT-ADC | IF-010, IF-011 |

---

## 9. REFERENCES

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-SRS-2026-001 | Software Requirements Specification | 0.1 |
| DOC-SAS-2026-001 | Software Architecture Specification | 0.2 |
| DOC-SDS-2026-001 | Software Design Specification | 0.1 |
| EN 50128:2011 | Railway Applications — Software for Railway Control and Protection Systems | 2011 |
| MISRA C:2012 | Guidelines for the Use of the C Language in Critical Systems | 2012 |

---

## APPENDIX A — INTERFACE QUICK-REFERENCE TABLE

| ID | Name | Direction | Period | Data Type | Safety-Critical | SRS Ref |
|----|------|-----------|--------|-----------|-----------------|---------|
| IF-001 | TCI → SPM speed | TCI→SPM | 100 ms | `tcms_speed_msg_t` | Yes | REQ-INT-007 |
| IF-002 | Speed interlock to SKN | SPM→SKN | 20 ms | `uint8_t`, `uint16_t` | Yes | REQ-SAFE-001 |
| IF-003 | Speed gate to DSM | SPM→DSM | 20 ms | `uint8_t` | Yes | REQ-SAFE-001 |
| IF-004 | GPIO sensors to DSM | HAL→DSM | 20 ms | `uint8_t[4]` arrays | Yes | REQ-INT-002,005 |
| IF-005 | Obstacle sensors to OBD | HAL→OBD | ISR+20 ms | `uint8_t[4]` arrays | Yes | REQ-INT-003 |
| IF-006 | Obstacle flags to DSM | OBD→DSM | 20 ms | `uint8_t[4]` | Yes | REQ-SAFE-004 |
| IF-007 | Obstacle flags to SKN | OBD→SKN | 20 ms | `uint8_t[4]` | Yes | REQ-SAFE-004 |
| IF-008 | Door/lock states to SKN | DSM→SKN | 20 ms | `door_state_t[4]`, `uint8_t[4]` | Yes | REQ-SAFE-001 |
| IF-009 | Door status to TCI | DSM→TCI | 100 ms | `door_status_msg_t` | Yes | REQ-INT-008 |
| IF-010 | Lock actuator cmd | DSM→HAL | On-event | `uint8_t[4]` | Yes | REQ-INT-004 |
| IF-011 | Motor PWM cmd | DSM→HAL | On-event | `uint8_t[4]` × 2 | Yes | REQ-INT-001 |
| IF-012 | Fault bitmask to SKN | FMG→SKN | 20 ms | `uint32_t` | Yes | REQ-SAFE-006 |
| IF-013 | Fault report to TCI | FMG→TCI | On-event+500ms | `fault_report_msg_t` | Yes | REQ-INT-008 |
| IF-014 | Event log entry | FMG→DGN | On-fault | `event_log_entry_t` | No (SIL 1) | REQ-SAFE-006 |
| IF-015 | Safe state broadcast | SKN→All | 20 ms | `uint8_t` | Yes | REQ-SAFE-001 |
| IF-016 | Departure interlock | SKN→TCI | 100 ms | `uint8_t` | Yes | REQ-INT-008 |
| IF-017 | Cross-channel SPI | SKN↔SKN | 20 ms | `cross_channel_state_t` | Yes | REQ-INT-010 |
| IF-018 | Door commands | TCI→DSM | On-event | `door_command_t` | Yes | REQ-INT-007 |
| IF-019 | Watchdog status | HAL→SKN | 20 ms | `uint8_t` | Yes | REQ-INT-006 |
| IF-020 | Event log to flash | DGN→Flash | Deferred | `event_log_entry_t[1024]` | No (SIL 1) | REQ-SAFE-006 |
| EXT-001 | Motor PWM actuator | SW→HW | On-event | `uint8_t` duty + dir | Yes | REQ-INT-001 |
| EXT-002 | Position sensors | HW→SW | 20 ms | `uint8_t` (2oo2) | Yes | REQ-INT-002 |
| EXT-003 | Obstacle sensors | HW→SW | ISR+20ms | `uint8_t` (1oo2) | Yes | REQ-INT-003 |
| EXT-004 | Lock actuators | SW→HW | On-event | `uint8_t` (active-LOW) | Yes | REQ-INT-004 |
| EXT-005 | Lock sensors | HW→SW | 20 ms | `uint8_t` (2oo2) | Yes | REQ-INT-005 |
| EXT-006 | IWDG watchdog | SW→HW | 40 ms | — | Yes | REQ-INT-006 |
| EXT-007 | CAN RX TCMS | TCMS→SW | Mixed | CAN frames | Yes | REQ-INT-007 |
| EXT-008 | CAN TX TCMS | SW→TCMS | Mixed | CAN frames | Yes | REQ-INT-008 |
| EXT-009 | RS-485 DDU | SW↔DDU | 40ms/on-event | DDU frames | No | REQ-INT-009 |
| EXT-010 | Cross-channel SPI | SW↔SW | 20 ms | `cross_channel_state_t` | Yes | REQ-INT-010 |
| EXT-011 | Emergency release | HW→SW | 20 ms | `uint8_t` (4 doors) | Yes | REQ-INT-011 |
| EXT-012 | Driver control panel | SW↔HW | 20 ms | Discrete I/O | No | REQ-INT-012 |
| EXT-013 | Diagnostics port | SW↔Tool | On-demand | ASCII/binary cmds | No (SIL 1) | REQ-INT-013 |
| EXT-ADC | Motor current ADC | HW→SW | 20 ms | `uint16_t` (12-bit) | Yes | REQ-SAFE-009 |

---

*End of Document — DOC-SIS-2026-001 v0.1 DRAFT*
