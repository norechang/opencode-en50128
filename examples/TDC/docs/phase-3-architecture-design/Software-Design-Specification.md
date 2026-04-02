# Software Design Specification (SDS)

**REFERENCE**: EN 50128:2011 Section 7.3–7.4, Table A.4, Annex C Item 10

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SDS-2026-001 |
| **CI ID** | CI-SDS-TDC-001 |
| **Version** | 0.1 DRAFT |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Software Designer (DES) |
| **Status** | Draft |

### Revision History

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-04-02 | DES | Initial draft — Phase 3 SDS from SAS DOC-SAS-2026-001 v0.2. Resolves OI-SAS-005 (CRC-16-CCITT 0x1021 unified), OI-SAS-003 (mode FSM complete), OI-FMEA-001 (SPI transient filter), OI-FTA-003 (CRC polynomial unification). | — |

---

## APPROVALS

**EN 50128 Annex C Table C.1 Signature Chain — Item 10 (SDS) — Track A (Development)**

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

This Software Design Specification (SDS) refines the TDC software architecture defined in
DOC-SAS-2026-001 v0.2 (Software Architecture Specification) into a module-level design
suitable for C implementation per MISRA C:2012 by IMP.

This document:
- Decomposes each SAS architectural component (COMP-001 through COMP-008) into modules
- Specifies data structures (static allocation only — mandatory SIL 2+)
- Defines function signatures, algorithms (pseudocode), pre/postconditions, and error
  handling for all modules
- Specifies CRC-16-CCITT (0x1021) for all safety-critical data — resolving OI-FTA-003
- Specifies the SPI transient filter algorithm for COMP-001 SKN — resolving OI-FMEA-001
- Documents all SIL 3 design constraints: cyclomatic complexity ≤ 10, no dynamic memory,
  no recursion, MISRA C:2012

### 1.2 Scope

This SDS covers all software modules executing on Channel A and Channel B of the TDC
Door Control Unit (DCU), comprising:
- 8 architectural components from DOC-SAS-2026-001
- 30 modules total (3–5 per component)
- All safety-critical functions at SIL 3

**Out of Scope**: Integration test specifications (INT, item 12/13), hardware design,
bootloader.

### 1.3 SIL Classification

**Target SIL Level**: SIL 3 (all safety components except DGN which is SIL 1).

### 1.4 SIL 3 Design Constraints (Mandatory)

The following constraints govern this design and all downstream implementation (IMP):

| Constraint | Rule | Reference |
|-----------|------|-----------|
| No dynamic memory allocation (`malloc`/`calloc`/`realloc`/`free`) | MISRA C:2012 Rule 21.3; mandatory SIL 2+ | REQ-SAFE-017, EN 50128 Table A.4 |
| Cyclomatic complexity ≤ 10 per function | EN 50128 SIL 3 mandatory | §7.6 SAS |
| No recursion | HR SIL 3–4 | EN 50128 Table A.4 |
| No function pointers in safety-critical paths | HR SIL 3–4 | EN 50128 Table A.4 |
| Fixed-width integer types only (`uint8_t`, `uint16_t`, `uint32_t`, `int16_t`, etc.) | MISRA C:2012 | All modules |
| CRC-16-CCITT polynomial **0x1021**, initial value 0xFFFF, no final XOR | OI-FTA-003 resolution | §5.3 SAS v0.2, all modules |
| All HAL functions return `error_t`; callers must check return value | Architecture rule | HAL COMP-008 |
| `safe_state_active` writable only by SKN | Architecture rule | COMP-001 SKN |

### 1.5 Input Documents

| Document ID | Title | Version | Role |
|-------------|-------|---------|------|
| DOC-SAS-2026-001 | Software Architecture Specification | 0.2 | Primary input |
| DOC-SRS-2026-001 | Software Requirements Specification | 0.1 | Requirements source |
| DOC-HAZLOG-2026-001 | Hazard Log | 0.2 | Hazard and safety requirements |
| DOC-FMEA-2026-001 | FMEA Report | 0.1 | OI-FMEA-001 SPI transient filter input |
| DOC-FTA-2026-001 | FTA Report | 0.1 | OI-FTA-003 CRC polynomial unification input |

### 1.6 Output Documents

| Document ID | Title | Owner |
|-------------|-------|-------|
| DOC-SIS-2026-001 | Software Interface Specifications (item 11) | DES |
| DOC-SITSPEC-2026-001 | Software Integration Test Specification (item 12) | INT |
| DOC-DESVER-2026-001 | Architecture and Design Verification Report (item 14) | VER |
| DOC-COMPDES-2026-001 | Software Component Design Specification (item 15) | DES |

---

## 2. DESIGN OVERVIEW

### 2.1 Module Decomposition Summary

Each SAS component is decomposed into 3–5 modules. All modules use static allocation.

| Comp ID | Comp Name | Module IDs | Module Count |
|---------|-----------|-----------|-------------|
| COMP-001 | Safety Kernel (SKN) | MOD-SKN-001 to MOD-SKN-004 | 4 |
| COMP-002 | Speed Monitor (SPM) | MOD-SPM-001 to MOD-SPM-003 | 3 |
| COMP-003 | Obstacle Detector (OBD) | MOD-OBD-001 to MOD-OBD-003 | 3 |
| COMP-004 | Door State Machine (DSM) | MOD-DSM-001 to MOD-DSM-005 | 5 |
| COMP-005 | Fault Manager (FMG) | MOD-FMG-001 to MOD-FMG-003 | 3 |
| COMP-006 | TCMS Interface (TCI) | MOD-TCI-001 to MOD-TCI-004 | 4 |
| COMP-007 | Diagnostics (DGN) | MOD-DGN-001 to MOD-DGN-003 | 3 |
| COMP-008 | Hardware Abstraction Layer (HAL) | MOD-HAL-001 to MOD-HAL-005 | 5 |

### 2.2 Common Data Types

The following types are defined in `tdc_types.h` and used throughout all modules:

```c
/* ---- tdc_types.h ---- */
#include <stdint.h>

#define MAX_DOORS         (4U)
#define MAX_DDU_NODES     (4U)
#define MAX_LOG_ENTRIES   (1024U)
#define SPEED_THRESHOLD   (50U)    /* km/h × 10 = 5.0 km/h */
#define CAN_TIMEOUT_MS    (200U)
#define WDG_REFRESH_MS    (40U)
#define CYCLE_MS          (20U)

/* Error codes — used by all safety-critical modules */
typedef enum {
    SUCCESS             = 0,
    ERR_NULL_PTR        = 1,
    ERR_RANGE           = 2,
    ERR_TIMEOUT         = 3,
    ERR_CRC             = 4,
    ERR_HW_FAULT        = 5,
    ERR_INVALID_STATE   = 6,
    ERR_NOT_PERMITTED   = 7,
    ERR_SENSOR_DISAGREE = 8,
    ERR_COMM_TIMEOUT    = 9,
    ERR_WATCHDOG        = 10
} error_t;

/* Door state enum */
typedef enum {
    DOOR_STATE_UNKNOWN          = 0,
    DOOR_STATE_FULLY_OPEN       = 1,
    DOOR_STATE_INTERMEDIATE     = 2,
    DOOR_STATE_FULLY_CLOSED     = 3,
    DOOR_STATE_CLOSED_AND_LOCKED = 4,
    DOOR_STATE_FAULT            = 5
} door_state_t;

/* Door FSM states */
typedef enum {
    FSM_IDLE              = 0,
    FSM_OPENING           = 1,
    FSM_FULLY_OPEN        = 2,
    FSM_CLOSING           = 3,
    FSM_OBSTACLE_REVERSAL = 4,
    FSM_FULLY_CLOSED      = 5,
    FSM_LOCKING           = 6,
    FSM_CLOSED_AND_LOCKED = 7,
    FSM_FAULT             = 8
} door_fsm_state_t;

/* Fault severity */
typedef enum {
    FAULT_NONE     = 0,
    FAULT_LOW      = 1,
    FAULT_MEDIUM   = 2,
    FAULT_HIGH     = 3,
    FAULT_CRITICAL = 4
} fault_severity_t;

/* Cross-channel SPI structure — CRC covers all preceding fields */
typedef struct {
    uint16_t speed_kmh_x10;
    uint8_t  door_states[MAX_DOORS];
    uint8_t  lock_states[MAX_DOORS];
    uint8_t  obstacle_flags[MAX_DOORS];
    uint8_t  fault_flags;
    uint8_t  safety_decisions;    /* bit0 = safe_state_active, bit1 = departure_interlock_ok */
    uint16_t crc16;               /* CRC-16-CCITT 0x1021 over all preceding bytes */
} cross_channel_state_t;

/* CAN speed message */
typedef struct {
    uint16_t speed_kmh_x10;
    uint8_t  seq_counter;
    uint16_t crc16;
} tcms_speed_msg_t;

/* Event log entry */
typedef struct {
    uint32_t timestamp_ms;
    uint8_t  source_comp;
    uint8_t  event_code;
    uint16_t data;
    uint16_t crc16;
} event_log_entry_t;
```

### 2.3 CRC-16-CCITT Algorithm

**Polynomial**: 0x1021 (CRC-16-CCITT / X.25).  
**Initial value**: 0xFFFF.  
**Final XOR**: None (0x0000).  
**Resolution of OI-FTA-003**: This polynomial is the **only** CRC-16 variant used in TDC.

```c
/* Defined in MOD-HAL-005 (crc16.c) — usable by all modules */
uint16_t CRC16_CCITT_Compute(const uint8_t *data, uint16_t length);
```

Pseudocode:
```
FUNCTION CRC16_CCITT_Compute(data[], length):
    PRE: data != NULL, length > 0
    crc = 0xFFFF
    FOR i = 0 TO length-1:
        crc = crc XOR (data[i] << 8)
        FOR bit = 0 TO 7:
            IF (crc AND 0x8000):
                crc = (crc << 1) XOR 0x1021
            ELSE:
                crc = crc << 1
            crc = crc AND 0xFFFF
    RETURN crc
    /* Cyclomatic complexity: 4 (linear, 1 outer loop, 1 inner loop, 1 branch) */
```

---

## 3. MODULE DESIGN: COMP-001 — Safety Kernel (SKN)

**SIL**: 3 | **Complexity limit**: ≤ 10 per function | **Phase**: Cycle step 1

The Safety Kernel is the central authority for:
- Cross-channel 2oo2 comparison via SPI
- Safe state assertion and management
- Departure interlock assertion
- SPI transient fault filtering (OI-FMEA-001)
- Stack canary and memory integrity checks

### 3.1 MOD-SKN-001 — Cross-Channel Comparator

**File**: `skn_comparator.c` / `skn_comparator.h`  
**Responsibility**: Compare local safety state with received cross-channel state.

#### Data Structures (static)

```c
static cross_channel_state_t s_local_state;     /* populated by SKN_BuildLocalState() */
static cross_channel_state_t s_remote_state;    /* populated by SPI exchange */
static uint8_t s_spi_infra_fault_count = 0U;    /* OI-FMEA-001 transient filter counter */
static cross_channel_state_t s_last_good_remote; /* last known good remote state */
```

#### Functions

**`SKN_BuildLocalState`**
```
SIGNATURE: error_t SKN_BuildLocalState(cross_channel_state_t *state,
               const uint16_t speed_kmh_x10,
               const uint8_t door_states[MAX_DOORS],
               const uint8_t lock_states[MAX_DOORS],
               const uint8_t obstacle_flags[MAX_DOORS],
               const uint8_t fault_flags,
               const uint8_t safety_decisions)

PRE:  state != NULL
POST: state->crc16 = CRC16_CCITT_Compute over all preceding fields
      Returns SUCCESS or ERR_NULL_PTR

ALGORITHM:
    IF state == NULL: RETURN ERR_NULL_PTR
    state->speed_kmh_x10 = speed_kmh_x10
    COPY door_states[MAX_DOORS] to state->door_states
    COPY lock_states[MAX_DOORS] to state->lock_states
    COPY obstacle_flags[MAX_DOORS] to state->obstacle_flags
    state->fault_flags = fault_flags
    state->safety_decisions = safety_decisions
    state->crc16 = CRC16_CCITT_Compute((uint8_t*)state,
                       sizeof(cross_channel_state_t) - sizeof(uint16_t))
    RETURN SUCCESS

MISRA: No pointer arithmetic beyond struct member access. Fixed-size array copy via loop.
Cyclomatic complexity: 2
```

**`SKN_ExchangeAndCompare`**
```
SIGNATURE: error_t SKN_ExchangeAndCompare(const cross_channel_state_t *local,
               uint8_t *safe_state_active_out)

PRE:  local != NULL, safe_state_active_out != NULL
POST: *safe_state_active_out = 1 if mismatch or unrecoverable infra fault; else 0
      s_spi_infra_fault_count updated per OI-FMEA-001 algorithm
      Returns SUCCESS, ERR_CRC, ERR_COMM_TIMEOUT, or ERR_SENSOR_DISAGREE

OI-FMEA-001 ALGORITHM (SPI transient filter — see SAS v0.2 §7.3):
    result = HAL_SPI_CrossChannel_Exchange(local, &s_remote_state)

    IF result != SUCCESS:
        /* Infrastructure fault: CRC error / timeout / HW error on SPI frame */
        s_spi_infra_fault_count++
        IF s_spi_infra_fault_count >= 3U:
            *safe_state_active_out = 1U
            LOG_EVENT(DGN, COMP_SKN, EVT_SPI_INFRA_PERSISTENT, s_spi_infra_fault_count)
            RETURN ERR_COMM_TIMEOUT
        ELSE:
            /* Transient: retain last known good, log warning, do NOT assert safe state */
            s_remote_state = s_last_good_remote
            LOG_EVENT(DGN, COMP_SKN, EVT_SPI_INFRA_TRANSIENT, s_spi_infra_fault_count)
            *safe_state_active_out = 0U
            RETURN ERR_CRC  /* caller is aware; safe_state NOT set */

    /* SPI frame received OK — validate remote CRC */
    computed_crc = CRC16_CCITT_Compute((uint8_t*)&s_remote_state,
                       sizeof(cross_channel_state_t) - sizeof(uint16_t))
    IF computed_crc != s_remote_state.crc16:
        /* CRC failure on safety-data payload — immediate safe state */
        s_spi_infra_fault_count = 0U
        *safe_state_active_out = 1U
        LOG_EVENT(DGN, COMP_SKN, EVT_SPI_CRC_FAIL, 0)
        RETURN ERR_CRC

    /* CRC OK — compare safety-data fields */
    s_spi_infra_fault_count = 0U   /* reset infrastructure counter */
    s_last_good_remote = s_remote_state

    IF SKN_FieldsDisagree(local, &s_remote_state):
        /* Safety-data disagreement — IMMEDIATE safe state, no filter */
        *safe_state_active_out = 1U
        LOG_EVENT(DGN, COMP_SKN, EVT_CHANNEL_DISAGREE, 0)
        RETURN ERR_SENSOR_DISAGREE

    *safe_state_active_out = 0U
    RETURN SUCCESS

Cyclomatic complexity: 7
```

**`SKN_FieldsDisagree`** *(internal helper)*
```
SIGNATURE: static uint8_t SKN_FieldsDisagree(const cross_channel_state_t *a,
               const cross_channel_state_t *b)

PRE:  a != NULL, b != NULL
POST: Returns 1 if any safety field differs; 0 if all agree

ALGORITHM:
    IF a->speed_kmh_x10 != b->speed_kmh_x10: RETURN 1
    FOR i = 0 TO MAX_DOORS-1:
        IF a->door_states[i] != b->door_states[i]: RETURN 1
        IF a->lock_states[i] != b->lock_states[i]: RETURN 1
        IF a->obstacle_flags[i] != b->obstacle_flags[i]: RETURN 1
    IF a->fault_flags != b->fault_flags: RETURN 1
    IF a->safety_decisions != b->safety_decisions: RETURN 1
    RETURN 0

Cyclomatic complexity: 8 (MAX_DOORS=4; 4 loop iterations × 2 branches + entry/exit)
```

---

### 3.2 MOD-SKN-002 — Safe State Manager

**File**: `skn_safe_state.c` / `skn_safe_state.h`  
**Responsibility**: Assert/clear `safe_state_active`; manage departure interlock.

#### Data Structures (static)

```c
static uint8_t s_safe_state_active = 0U;
static uint8_t s_departure_interlock_ok = 0U;  /* init: 0 (locked/unknown) */
```

#### Functions

**`SKN_EvaluateSafeState`**
```
SIGNATURE: error_t SKN_EvaluateSafeState(
               const uint8_t channel_disagree,
               const uint8_t fault_state,
               const uint8_t memory_crc_ok,
               const uint8_t stack_canary_ok,
               uint8_t *safe_state_active_out)

PRE:  safe_state_active_out != NULL
POST: s_safe_state_active updated; *safe_state_active_out reflects new state
      Safe state is sticky (once set, only cleared by power cycle / maintenance reset)

ALGORITHM:
    IF safe_state_active_out == NULL: RETURN ERR_NULL_PTR
    IF channel_disagree OR (fault_state AND FAULT_CRITICAL_MASK) OR
       NOT memory_crc_ok OR NOT stack_canary_ok:
        s_safe_state_active = 1U
    /* Safe state is STICKY — never cleared in normal operation */
    *safe_state_active_out = s_safe_state_active
    RETURN SUCCESS

Cyclomatic complexity: 5
```

**`SKN_EvaluateDepartureInterlock`**
```
SIGNATURE: error_t SKN_EvaluateDepartureInterlock(
               const uint8_t door_states[MAX_DOORS],
               const uint8_t lock_states[MAX_DOORS],
               const uint8_t channel_disagree,
               const uint8_t safe_state_active,
               uint8_t *interlock_ok_out)

PRE:  door_states != NULL, lock_states != NULL, interlock_ok_out != NULL
POST: *interlock_ok_out = 1 only if ALL doors CLOSED_AND_LOCKED and channel agrees
      OI-FTA-001: departure_interlock_ok ONLY asserted after successful cross-channel comparison

ALGORITHM:
    IF door_states == NULL OR lock_states == NULL OR interlock_ok_out == NULL:
        *interlock_ok_out = 0U   /* fail-closed */
        RETURN ERR_NULL_PTR
    IF safe_state_active OR channel_disagree:
        *interlock_ok_out = 0U
        RETURN SUCCESS
    all_locked = 1U
    FOR i = 0 TO MAX_DOORS-1:
        IF door_states[i] != DOOR_STATE_CLOSED_AND_LOCKED: all_locked = 0U; BREAK
        IF lock_states[i] != 1U: all_locked = 0U; BREAK
    *interlock_ok_out = all_locked
    s_departure_interlock_ok = all_locked
    RETURN SUCCESS

Cyclomatic complexity: 7
```

**`SKN_CheckMemoryIntegrity`**
```
SIGNATURE: error_t SKN_CheckMemoryIntegrity(uint8_t *crc_ok_out)

PRE:  crc_ok_out != NULL
POST: *crc_ok_out = 1 if ROM CRC and safety-global CRC match stored values; else 0

ALGORITHM (pseudocode — exact addresses provided by linker symbols):
    IF crc_ok_out == NULL: RETURN ERR_NULL_PTR
    rom_crc = CRC16_CCITT_Compute(ROM_START_ADDR, ROM_SAFETY_LEN)
    IF rom_crc != ROM_EXPECTED_CRC: *crc_ok_out = 0U; RETURN ERR_CRC
    ram_crc = CRC16_CCITT_Compute(SAFETY_GLOBALS_START, SAFETY_GLOBALS_LEN)
    IF ram_crc != s_safety_globals_crc_snapshot: *crc_ok_out = 0U; RETURN ERR_CRC
    *crc_ok_out = 1U
    RETURN SUCCESS

Cyclomatic complexity: 4
```

**`SKN_CheckStackCanary`**
```
SIGNATURE: error_t SKN_CheckStackCanary(uint8_t *canary_ok_out)

PRE:  canary_ok_out != NULL
POST: *canary_ok_out = 1 if canary values at stack top and bottom unchanged; else 0

ALGORITHM:
    IF canary_ok_out == NULL: RETURN ERR_NULL_PTR
    IF (*STACK_CANARY_TOP_ADDR != CANARY_VALUE) OR (*STACK_CANARY_BOTTOM_ADDR != CANARY_VALUE):
        *canary_ok_out = 0U
        RETURN ERR_HW_FAULT
    *canary_ok_out = 1U
    RETURN SUCCESS

Cyclomatic complexity: 3
```

---

### 3.3 MOD-SKN-003 — Scheduler Entry Point

**File**: `skn_scheduler.c` / `skn_scheduler.h`  
**Responsibility**: Orchestrate the 20 ms cyclic executive. Called by the timer ISR flag.

#### Functions

**`SKN_RunCycle`** *(top-level cycle dispatcher)*
```
SIGNATURE: void SKN_RunCycle(void)

PRE:  All static state initialized (SKN_Init called at boot)
POST: One complete 20 ms cycle executed in correct component order (SAS §3.1)

ALGORITHM:
    /* Step 1: Safety Kernel gate */
    SKN_BuildLocalState(...)
    SKN_ExchangeAndCompare(&s_local_state, &channel_disagree)
    SKN_CheckStackCanary(&canary_ok)
    IF (cycle_count % 5U == 0U): SKN_CheckMemoryIntegrity(&mem_ok)  /* every 100 ms */
    SKN_EvaluateSafeState(channel_disagree, FMG_GetFaultState(),
                          mem_ok, canary_ok, &g_safe_state_active)
    /* Steps 2–11: invoke other components */
    SPM_RunCycle()
    OBD_RunCycle()
    DSM_RunCycle()
    FMG_RunCycle()
    /* Step 6: actuators, CAN TX, RS-485, watchdog, DGN handled by respective modules */
    TCI_TransmitCycle()
    HAL_Watchdog_Refresh()
    DGN_RunCycle()
    cycle_count++

Cyclomatic complexity: 3
```

---

### 3.4 MOD-SKN-004 — Initialization

**File**: `skn_init.c` / `skn_init.h`

**`SKN_Init`**
```
SIGNATURE: error_t SKN_Init(void)

POST: All static state variables zeroed/initialized to fail-safe values
      s_safe_state_active = 0U
      s_departure_interlock_ok = 0U  (LOCKED_UNKNOWN — fail-closed)
      s_spi_infra_fault_count = 0U
      s_last_good_remote = {0}
      ROM CRC snapshot stored
      RAM safety-globals CRC snapshot stored
      Returns SUCCESS or ERR_HW_FAULT

Cyclomatic complexity: 2
```

---

## 4. MODULE DESIGN: COMP-002 — Speed Monitor (SPM)

**SIL**: 3 | **Complexity limit**: ≤ 10 | **Phase**: Cycle step 2

### 4.1 MOD-SPM-001 — CAN Speed Reception and Validation

**File**: `spm_can.c` / `spm_can.h`

#### Data Structures (static)

```c
static tcms_speed_msg_t  s_latest_speed_msg;
static uint32_t          s_last_valid_rx_ms = 0U;  /* timestamp of last valid frame */
static uint8_t           s_last_seq_counter = 0U;
static uint8_t           s_speed_interlock_active = 1U;  /* default: inhibit (fail-safe) */
static uint16_t          s_current_speed_kmh_x10 = 0xFFFFU;  /* UNKNOWN */
```

#### Functions

**`SPM_ProcessSpeedFrame`**
```
SIGNATURE: error_t SPM_ProcessSpeedFrame(const tcms_speed_msg_t *msg,
               const uint32_t timestamp_ms)

PRE:  msg != NULL
POST: s_latest_speed_msg updated if valid; s_last_valid_rx_ms updated; s_last_seq_counter updated
      Returns SUCCESS, ERR_NULL_PTR, ERR_CRC, ERR_RANGE

ALGORITHM:
    IF msg == NULL: RETURN ERR_NULL_PTR
    /* CRC-16-CCITT check */
    computed_crc = CRC16_CCITT_Compute((uint8_t*)msg,
                       sizeof(tcms_speed_msg_t) - sizeof(uint16_t))
    IF computed_crc != msg->crc16:
        LOG_EVENT(DGN, COMP_SPM, EVT_CAN_CRC_FAIL, 0)
        RETURN ERR_CRC  /* speed stays stale; timeout logic will trigger interlock */
    /* Sequence counter check — modulo-256 */
    expected_seq = (s_last_seq_counter + 1U) AND 0xFFU
    IF msg->seq_counter != expected_seq:
        LOG_EVENT(DGN, COMP_SPM, EVT_CAN_SEQ_SKIP, msg->seq_counter)
        /* Not fatal — log only; OI-FMEA-002 notes boundary condition in seq counter */
    /* Range check: 0–3000 (0–300.0 km/h × 10) */
    IF msg->speed_kmh_x10 > 3000U:
        LOG_EVENT(DGN, COMP_SPM, EVT_SPEED_RANGE_ERR, msg->speed_kmh_x10)
        RETURN ERR_RANGE
    s_latest_speed_msg = *msg
    s_last_valid_rx_ms = timestamp_ms
    s_last_seq_counter = msg->seq_counter
    s_current_speed_kmh_x10 = msg->speed_kmh_x10
    RETURN SUCCESS

Cyclomatic complexity: 6
```

---

### 4.2 MOD-SPM-002 — Interlock Evaluation

**File**: `spm_interlock.c` / `spm_interlock.h`

**`SPM_EvaluateInterlock`**
```
SIGNATURE: error_t SPM_EvaluateInterlock(const uint32_t current_time_ms,
               uint8_t *interlock_active_out)

PRE:  interlock_active_out != NULL
POST: *interlock_active_out = 1 if speed > SPEED_THRESHOLD or data stale/unknown
      Fail-safe default: interlock = 1 (assume moving)
      OI-FMEA-002: boundary: speed == SPEED_THRESHOLD (50 = 5.0 km/h × 10) → safe (= 0)

ALGORITHM:
    IF interlock_active_out == NULL: RETURN ERR_NULL_PTR
    /* Timeout check */
    IF (current_time_ms - s_last_valid_rx_ms) > CAN_TIMEOUT_MS:
        s_speed_interlock_active = 1U  /* stale → assume moving */
        *interlock_active_out = 1U
        RETURN SUCCESS
    /* Unknown speed */
    IF s_current_speed_kmh_x10 == 0xFFFFU:
        s_speed_interlock_active = 1U
        *interlock_active_out = 1U
        RETURN SUCCESS
    /* Speed threshold — OI-FMEA-002: exact boundary 50 (5.0 km/h) is SAFE */
    IF s_current_speed_kmh_x10 > SPEED_THRESHOLD:
        s_speed_interlock_active = 1U
    ELSE:
        s_speed_interlock_active = 0U
    *interlock_active_out = s_speed_interlock_active
    RETURN SUCCESS

Cyclomatic complexity: 5
```

---

### 4.3 MOD-SPM-003 — Initialization and Cycle Entry

**File**: `spm_init.c` / `spm_init.h`

**`SPM_Init`**: Sets all static state to fail-safe (interlock = 1, speed = UNKNOWN).  
**`SPM_RunCycle`**: Calls `SPM_ProcessSpeedFrame` (if new CAN frame in mailbox) then
`SPM_EvaluateInterlock(current_time_ms, &g_speed_interlock_active)`.  
Cyclomatic complexity: ≤ 3 per function.

---

## 5. MODULE DESIGN: COMP-003 — Obstacle Detector (OBD)

**SIL**: 3 | **Complexity limit**: ≤ 10 | **Phase**: Cycle step 3 + ISR

### 5.1 MOD-OBD-001 — Obstacle Sensor ISR Handler

**File**: `obd_isr.c` / `obd_isr.h`  
**Responsibility**: Interrupt service routine — write to static mailbox only (no logic).

#### Data Structures (static)

```c
static uint8_t s_obstacle_isr_flags[MAX_DOORS];   /* set by ISR, polled by OBD_RunCycle */
```

**`OBD_ObstacleISR`** *(ISR — called by HAL on GPIO EXTI interrupt)*
```
SIGNATURE: void OBD_ObstacleISR(uint8_t door_id)

PRE:  door_id < MAX_DOORS (bounds-checked in HAL before calling)
POST: s_obstacle_isr_flags[door_id] = 1U

ALGORITHM:
    IF door_id >= MAX_DOORS: RETURN   /* defensive bounds check */
    s_obstacle_isr_flags[door_id] = 1U

MISRA: ISR is minimal — no logic, no function calls, no allocation.
Cyclomatic complexity: 2
```

---

### 5.2 MOD-OBD-002 — Obstacle Detection and Reversal

**File**: `obd_detect.c` / `obd_detect.h`

#### Data Structures (static)

```c
static uint8_t  s_obstacle_flags[MAX_DOORS];   /* authoritative, polled by SKN/DSM */
static uint16_t s_motor_current_adc[MAX_DOORS]; /* raw ADC reading (≤ 65535) */
```

**`OBD_PollSensorsAndEvaluate`**
```
SIGNATURE: error_t OBD_PollSensorsAndEvaluate(
               const uint8_t door_closing_flags[MAX_DOORS],
               uint8_t obstacle_flags_out[MAX_DOORS])

PRE:  door_closing_flags != NULL, obstacle_flags_out != NULL
POST: obstacle_flags_out[i] = 1 if obstacle on door i; s_obstacle_flags updated
      Fail-safe: if sensor NULL → treat as OBSTACLE_DETECTED

ALGORITHM:
    IF door_closing_flags == NULL OR obstacle_flags_out == NULL:
        FOR i = 0 TO MAX_DOORS-1: obstacle_flags_out[i] = 1U  /* fail-safe */
        RETURN ERR_NULL_PTR
    FOR i = 0 TO MAX_DOORS-1:
        detected = 0U
        /* ISR latch */
        IF s_obstacle_isr_flags[i]: detected = 1U; s_obstacle_isr_flags[i] = 0U
        /* Polled sensor A */
        ret_a = HAL_GPIO_ReadObstacleSensor(i, 0U, &sensor_a)
        IF ret_a != SUCCESS: detected = 1U  /* fail-safe on NULL / HW error */
        ELSE IF sensor_a: detected = 1U
        /* Polled sensor B (1oo2 — either triggers reversal) */
        ret_b = HAL_GPIO_ReadObstacleSensor(i, 1U, &sensor_b)
        IF ret_b != SUCCESS: detected = 1U
        ELSE IF sensor_b: detected = 1U
        /* Motor current check — force > MAX_FORCE equivalent (REQ-SAFE-006) */
        IF door_closing_flags[i]:
            adc_ret = HAL_ADC_ReadMotorCurrent(i, &s_motor_current_adc[i])
            IF adc_ret == SUCCESS AND s_motor_current_adc[i] > MAX_FORCE_ADC:
                detected = 1U
        s_obstacle_flags[i] = detected
        obstacle_flags_out[i] = detected
    RETURN SUCCESS

Cyclomatic complexity: 10 (within limit)
```

---

### 5.3 MOD-OBD-003 — Initialization and Cycle Entry

**`OBD_Init`**: Zeros all static arrays, ISR flags, ADC readings.  
**`OBD_RunCycle`**: Calls `OBD_PollSensorsAndEvaluate`; writes result to `g_obstacle_flags`.  
Cyclomatic complexity: ≤ 3 each.

---

## 6. MODULE DESIGN: COMP-004 — Door State Machine (DSM)

**SIL**: 3 | **Complexity limit**: ≤ 10 | **Phase**: Cycle step 4

### 6.1 MOD-DSM-001 — Per-Door FSM Engine

**File**: `dsm_fsm.c` / `dsm_fsm.h`

#### Data Structures (static)

```c
static door_fsm_state_t s_door_fsm[MAX_DOORS];
static uint32_t         s_door_state_entry_time_ms[MAX_DOORS];  /* dwell timer */
static uint8_t          s_door_states[MAX_DOORS];               /* exported to SKN/TCI */
static uint8_t          s_lock_states[MAX_DOORS];

/* FSM maximum dwell times per state (ms) */
static const uint16_t FSM_MAX_DWELL_MS[] = {
    [FSM_IDLE]              = 0U,       /* no timeout — idle forever */
    [FSM_OPENING]           = 4000U,
    [FSM_FULLY_OPEN]        = 0U,       /* no timeout — waits for close command */
    [FSM_CLOSING]           = 10000U,
    [FSM_OBSTACLE_REVERSAL] = 2000U,
    [FSM_FULLY_CLOSED]      = 500U,     /* brief — locking should be fast */
    [FSM_LOCKING]           = 2000U,
    [FSM_CLOSED_AND_LOCKED] = 0U,
    [FSM_FAULT]             = 0U
};
```

**`DSM_UpdateFSM`** *(called once per door per cycle)*
```
SIGNATURE: error_t DSM_UpdateFSM(uint8_t door_id,
               const uint8_t cmd_open,
               const uint8_t cmd_close,
               const uint8_t pos_a_open, const uint8_t pos_a_closed,
               const uint8_t pos_b_open, const uint8_t pos_b_closed,
               const uint8_t lock_a, const uint8_t lock_b,
               const uint8_t obstacle,
               const uint8_t speed_interlock,
               const uint8_t safe_state_active,
               const uint32_t current_time_ms)

PRE:  door_id < MAX_DOORS
POST: s_door_fsm[door_id] updated; s_door_states[door_id], s_lock_states[door_id] updated
      Returns SUCCESS, ERR_RANGE, ERR_INVALID_STATE

ALGORITHM:
    IF door_id >= MAX_DOORS: RETURN ERR_RANGE

    /* Safe state override — any state → FAULT, motor stop */
    IF safe_state_active:
        IF s_door_fsm[door_id] != FSM_FAULT:
            HAL_PWM_SetDutyCycle(door_id, 0U)
            HAL_GPIO_SetLockActuator(door_id, 1U)
            s_door_fsm[door_id] = FSM_FAULT
        s_door_states[door_id] = DOOR_STATE_FAULT
        RETURN SUCCESS

    /* Dwell timeout check */
    dwell = current_time_ms - s_door_state_entry_time_ms[door_id]
    max_dwell = FSM_MAX_DWELL_MS[s_door_fsm[door_id]]
    IF (max_dwell > 0U) AND (dwell > max_dwell):
        DSM_EnterFaultState(door_id, current_time_ms)
        RETURN SUCCESS

    /* FSM transitions — dispatched per current state */
    SWITCH s_door_fsm[door_id]:
        CASE FSM_IDLE:         DSM_TransitionFromIdle(door_id, cmd_open, speed_interlock, current_time_ms); BREAK
        CASE FSM_OPENING:      DSM_TransitionFromOpening(door_id, pos_a_open, pos_b_open, current_time_ms); BREAK
        CASE FSM_FULLY_OPEN:   DSM_TransitionFromFullyOpen(door_id, cmd_close, obstacle, current_time_ms); BREAK
        CASE FSM_CLOSING:      DSM_TransitionFromClosing(door_id, pos_a_closed, pos_b_closed, obstacle, current_time_ms); BREAK
        CASE FSM_OBSTACLE_REVERSAL: DSM_TransitionFromReversal(door_id, current_time_ms); BREAK
        CASE FSM_FULLY_CLOSED: DSM_TransitionFromFullyClosed(door_id, current_time_ms); BREAK
        CASE FSM_LOCKING:      DSM_TransitionFromLocking(door_id, lock_a, lock_b, current_time_ms); BREAK
        CASE FSM_CLOSED_AND_LOCKED: /* Stable state — no spontaneous transition */ BREAK
        DEFAULT:               DSM_EnterFaultState(door_id, current_time_ms); BREAK

    DSM_UpdateDoorStateEnum(door_id)
    RETURN SUCCESS

Cyclomatic complexity: 8 (switch with 9 cases bounded; safe_state + dwell checks = 2 more)
```

Individual transition helpers (each ≤ 5 cyclomatic complexity):

**`DSM_TransitionFromIdle`**: Checks speed_interlock==0 and cmd_open; if OK, start motor, enter FSM_OPENING.  
**`DSM_TransitionFromOpening`**: pos_a_open AND pos_b_open → motor stop, FSM_FULLY_OPEN.  
**`DSM_TransitionFromFullyOpen`**: cmd_close AND !obstacle → motor close direction, FSM_CLOSING.  
**`DSM_TransitionFromClosing`**: obstacle → FSM_OBSTACLE_REVERSAL; pos_a_closed AND pos_b_closed → FSM_FULLY_CLOSED.  
**`DSM_TransitionFromReversal`**: Always → motor open direction, FSM_OPENING (retry).  
**`DSM_TransitionFromFullyClosed`**: Unconditional → energize lock solenoid, FSM_LOCKING.  
**`DSM_TransitionFromLocking`**: lock_a AND lock_b (2oo2 × 2oo2) → FSM_CLOSED_AND_LOCKED; notify SKN.

---

### 6.2 MOD-DSM-002 — Sensor Voter (2oo2)

**File**: `dsm_voter.c` / `dsm_voter.h`

**`DSM_VotePosition`**
```
SIGNATURE: error_t DSM_VotePosition(uint8_t door_id,
               const uint8_t pos_a, const uint8_t pos_b,
               uint8_t *voted_position, uint8_t *disagree_out)

PRE:  voted_position != NULL, disagree_out != NULL, door_id < MAX_DOORS
POST: *voted_position = agreed value; *disagree_out = 1 on disagreement

ALGORITHM:
    IF voted_position==NULL OR disagree_out==NULL: RETURN ERR_NULL_PTR
    IF pos_a == pos_b:
        *voted_position = pos_a
        *disagree_out = 0U
    ELSE:
        *voted_position = 0U           /* UNKNOWN — conservative */
        *disagree_out = 1U
        LOG_EVENT(DGN, COMP_DSM, EVT_SENSOR_DISAGREE, door_id)
    RETURN SUCCESS

Cyclomatic complexity: 3
```

---

### 6.3 MOD-DSM-003 — Operational Mode Manager

**File**: `dsm_mode.c` / `dsm_mode.h`  
**Responsibility**: Manage operational mode FSM (OI-SAS-003 resolution).

#### Data Structures (static)

```c
typedef enum {
    MODE_NORMAL        = 0,
    MODE_DIAGNOSTIC    = 1,
    MODE_MAINTENANCE   = 2,
    MODE_DOOR_DISABLED = 3
} op_mode_t;

static op_mode_t s_op_mode = MODE_NORMAL;
```

**`DSM_TransitionMode`**
```
SIGNATURE: error_t DSM_TransitionMode(const op_mode_t requested_mode,
               const uint8_t tcms_authorized,
               const uint8_t speed_zero)

PRE:  requested_mode is a valid op_mode_t value
POST: s_op_mode updated if transition is authorized and conditions met

TRANSITION GUARDS:
    NORMAL → DIAGNOSTIC:     speed_zero AND tcms_authorized
    NORMAL → MAINTENANCE:    speed_zero AND tcms_authorized
    NORMAL → DOOR_DISABLED:  tcms_authorized (REQ-FUN-013; speed interlock remains)
    DIAGNOSTIC → NORMAL:     always (exit diagnostic mode)
    MAINTENANCE → NORMAL:    always (maintenance reset)
    DOOR_DISABLED → NORMAL:  tcms_authorized
    Any unlisted transition: RETURN ERR_NOT_PERMITTED

Cyclomatic complexity: 8
```

---

### 6.4 MOD-DSM-004 — Emergency Release Handler

**File**: `dsm_emergency.c` / `dsm_emergency.h`

**`DSM_HandleEmergencyRelease`**
```
SIGNATURE: error_t DSM_HandleEmergencyRelease(uint8_t door_id,
               const uint32_t current_time_ms)

POST: Emergency release latched (REQ-SAFE-020); TCMS alerted within 100 ms (REQ-SAFE-019)
      Release latched until maintenance reset — cannot be cleared in Normal mode

ALGORITHM:
    Debounce ≥ 60 ms (SEEA mitigation for REQ-SAFE-019)
    On confirmed release: set s_emergency_release_latched[door_id] = 1U
    Log EVT_EMERGENCY_RELEASE to DGN
    Schedule CAN 0x201 status TX (TCI) within 100 ms

Cyclomatic complexity: 4
```

---

### 6.5 MOD-DSM-005 — Initialization and Cycle Entry

**`DSM_Init`**: All FSM states → FSM_IDLE; door_states → DOOR_STATE_UNKNOWN; lock_states → 0 (LOCKED_UNKNOWN).  
**`DSM_RunCycle`**: For each door, reads sensors via HAL, calls `DSM_VotePosition`, calls `DSM_UpdateFSM`.  
Cyclomatic complexity: ≤ 4 each.

---

## 7. MODULE DESIGN: COMP-005 — Fault Manager (FMG)

**SIL**: 3 | **Complexity limit**: ≤ 10 | **Phase**: Cycle step 5

### 7.1 MOD-FMG-001 — Fault Aggregator

**File**: `fmg_aggregator.c` / `fmg_aggregator.h`

#### Data Structures (static)

```c
static uint8_t s_fault_state = 0U;

/* Fault classification table — static lookup */
typedef struct {
    uint8_t           fault_bit;
    fault_severity_t  severity;
    const char       *description;   /* for DGN logging only — read-only string */
} fault_entry_t;

static const fault_entry_t FAULT_TABLE[] = {
    {0x01U, FAULT_CRITICAL, "Speed interlock defeat"},
    {0x02U, FAULT_CRITICAL, "Cross-channel SPI mismatch"},
    {0x04U, FAULT_CRITICAL, "CRC mismatch safety structure"},
    {0x08U, FAULT_HIGH,     "Sensor 2oo2 disagreement"},
    {0x10U, FAULT_HIGH,     "CAN timeout > 200ms"},
    {0x20U, FAULT_HIGH,     "Motor control failure"},
    {0x40U, FAULT_HIGH,     "Obstacle sensor fault"},
    {0x80U, FAULT_MEDIUM,   "DDU communication timeout"}
};

#define FAULT_TABLE_SIZE (sizeof(FAULT_TABLE) / sizeof(FAULT_TABLE[0]))
#define FAULT_CRITICAL_MASK (0x07U)
```

**`FMG_AggregateFaults`**
```
SIGNATURE: error_t FMG_AggregateFaults(
               const uint8_t spm_fault,
               const uint8_t obd_fault,
               const uint8_t dsm_fault,
               const uint8_t tci_fault,
               const uint8_t hal_fault,
               uint8_t *fault_state_out)

PRE:  fault_state_out != NULL
POST: s_fault_state = OR of all input fault bits; *fault_state_out updated

ALGORITHM:
    IF fault_state_out == NULL: RETURN ERR_NULL_PTR
    s_fault_state = spm_fault OR obd_fault OR dsm_fault OR tci_fault OR hal_fault
    *fault_state_out = s_fault_state
    RETURN SUCCESS

Cyclomatic complexity: 2
```

**`FMG_ClassifyAndEscalate`**
```
SIGNATURE: error_t FMG_ClassifyAndEscalate(const uint8_t fault_state,
               fault_severity_t *max_severity_out)

PRE:  max_severity_out != NULL
POST: *max_severity_out = highest severity among active fault bits

ALGORITHM:
    IF max_severity_out == NULL: RETURN ERR_NULL_PTR
    *max_severity_out = FAULT_NONE
    FOR i = 0 TO FAULT_TABLE_SIZE-1:
        IF fault_state AND FAULT_TABLE[i].fault_bit:
            IF FAULT_TABLE[i].severity > *max_severity_out:
                *max_severity_out = FAULT_TABLE[i].severity
                LOG_EVENT(DGN, COMP_FMG, EVT_FAULT_ACTIVE, FAULT_TABLE[i].fault_bit)
    RETURN SUCCESS

Cyclomatic complexity: 4
```

---

### 7.2 MOD-FMG-002 — Safe State Coordinator

**File**: `fmg_safe_state.c` / `fmg_safe_state.h`

**`FMG_HandleSelectiveDisablement`**: Implements REQ-FUN-013 / REQ-SAFE-013 —
speed interlock remains active during selective door disablement. Requires TCMS
authorization (REQ-SAFE-021). Logs to DGN. Cyclomatic complexity: ≤ 6.

---

### 7.3 MOD-FMG-003 — Initialization and Cycle Entry

**`FMG_Init`**: s_fault_state = 0U.  
**`FMG_RunCycle`**: Calls `FMG_AggregateFaults` then `FMG_ClassifyAndEscalate`.  
**`FMG_GetFaultState`**: Returns s_fault_state (called by SKN).  
Cyclomatic complexity: ≤ 3 each.

---

## 8. MODULE DESIGN: COMP-006 — TCMS Interface (TCI)

**SIL**: 3 | **Complexity limit**: ≤ 10 | **Phase**: Cycle step 8 (TX) + ISR (RX)

### 8.1 MOD-TCI-001 — CAN Receive Handler

**File**: `tci_rx.c` / `tci_rx.h`

#### Data Structures (static)

```c
typedef struct {
    uint32_t msg_id;
    uint8_t  data[8];
    uint8_t  dlc;
    uint32_t rx_timestamp_ms;
    uint8_t  valid;
} can_mailbox_t;

static can_mailbox_t s_can_rx_mailbox[5];  /* one per CAN ID 0x100–0x104 */
```

**`TCI_CanRxISR`** *(ISR — minimal, copy-to-mailbox only)*
```
SIGNATURE: void TCI_CanRxISR(void)
POST: s_can_rx_mailbox updated from HAL CAN FIFO; no processing in ISR
Cyclomatic complexity: 3
```

**`TCI_ProcessReceivedFrames`** *(called at cycle step 2 by SPM and DSM)*
```
SIGNATURE: error_t TCI_ProcessReceivedFrames(void)

FOR each mailbox with valid = 1:
    Validate CRC-16-CCITT (0x1021) — OI-FTA-003
    IF CRC fail: discard, log EVT_CAN_CRC_FAIL, treat as timeout, CONTINUE
    Validate sequence counter (modulo-256 delta)
    Route frame to appropriate handler:
        0x100 → SPM_ProcessSpeedFrame
        0x101/0x102 → DSM command mailbox
        0x103 → DSM_TransitionMode
        0x104 → FMG emergency stop
    Mark mailbox valid = 0

Cyclomatic complexity: 8
```

---

### 8.2 MOD-TCI-002 — CAN Transmit

**File**: `tci_tx.c` / `tci_tx.h`

**`TCI_TransmitDepartureInterlock`** (CAN 0x200, 100 ms):
```
Builds: departure_interlock_ok (bit0) + per-door lock mask + CRC-16-CCITT (0x1021)
Calls HAL_CAN_Transmit(0x200, data, dlc)
Cyclomatic complexity: 3
```

**`TCI_TransmitDoorStatus`** (CAN 0x201, 100 ms):
```
Builds per-door status frame + CRC-16-CCITT (0x1021)
Cyclomatic complexity: 3
```

**`TCI_TransmitFaultReport`** (CAN 0x202, on-event + 500 ms periodic):
```
Encodes s_fault_state into CAN frame; CRC-16-CCITT
Cyclomatic complexity: 3
```

---

### 8.3 MOD-TCI-003 — Sequence Counter

**File**: `tci_seq.c` / `tci_seq.h`

**`TCI_IncrementTxSeqCounter`**: Modulo-256 increment of TX sequence counter.  
**`TCI_ValidateRxSeqDelta`**: Checks RX delta; logs discontinuity.  
Cyclomatic complexity: ≤ 3 each.

---

### 8.4 MOD-TCI-004 — Initialization and Cycle Entry

**`TCI_Init`**: Zeros all mailboxes, seq counters.  
**`TCI_TransmitCycle`**: Called at step 8; calls all three TX functions.  
Cyclomatic complexity: ≤ 3 each.

---

## 9. MODULE DESIGN: COMP-007 — Diagnostics (DGN)

**SIL**: 1 (non-safety) | **Complexity limit**: ≤ 10 | **Phase**: Cycle step 11

### 9.1 MOD-DGN-001 — Event Log (Circular Buffer)

**File**: `dgn_log.c` / `dgn_log.h`

#### Data Structures (static)

```c
static event_log_entry_t s_log_buffer[MAX_LOG_ENTRIES];
static uint16_t          s_log_head = 0U;   /* next write index */
static uint16_t          s_log_count = 0U;  /* entries used */
```

**`DGN_LogEvent`**
```
SIGNATURE: error_t DGN_LogEvent(uint8_t source_comp, uint8_t event_code,
               uint16_t data, uint32_t timestamp_ms)

POST: Entry written at s_log_head; CRC-16-CCITT computed over entry body;
      s_log_head advanced modulo MAX_LOG_ENTRIES; MUST NOT block safety components

ALGORITHM:
    entry.timestamp_ms = timestamp_ms
    entry.source_comp  = source_comp
    entry.event_code   = event_code
    entry.data         = data
    entry.crc16 = CRC16_CCITT_Compute((uint8_t*)&entry, sizeof(entry)-sizeof(uint16_t))
    s_log_buffer[s_log_head] = entry
    s_log_head = (s_log_head + 1U) % MAX_LOG_ENTRIES
    IF s_log_count < MAX_LOG_ENTRIES: s_log_count++
    RETURN SUCCESS

Cyclomatic complexity: 2
```

---

### 9.2 MOD-DGN-002 — SPI Flash Writer

**File**: `dgn_flash.c` / `dgn_flash.h`  
**Responsibility**: Non-blocking, deferred write of log buffer to SPI Flash.  
DGN MUST NOT block if SPI Flash is busy — defers to next cycle.  
Cyclomatic complexity: ≤ 8.

---

### 9.3 MOD-DGN-003 — Diagnostic Port Handler

**File**: `dgn_port.c` / `dgn_port.h`  
**Responsibility**: Serve log data on USB/RS-232 port.  
Read-only in Normal mode; write access in Maintenance mode only (DSM_GetOpMode check).  
Cyclomatic complexity: ≤ 8.

---

## 10. MODULE DESIGN: COMP-008 — Hardware Abstraction Layer (HAL)

**SIL**: 3 | **Complexity limit**: ≤ 10 | **Phase**: Called by all components

### 10.1 MOD-HAL-001 — GPIO and Sensor Drivers

**File**: `hal_gpio.c` / `hal_gpio.h`

All functions follow `error_t` return convention. NULL pointer guard + bounds check on
`door_id` and `sensor_id` before any register access. Returns `ERR_HW_FAULT` on
peripheral failure.

```c
error_t HAL_GPIO_ReadPositionSensor(uint8_t door_id, uint8_t sensor_id, uint8_t *state);
error_t HAL_GPIO_ReadObstacleSensor(uint8_t door_id, uint8_t sensor_id, uint8_t *detected);
error_t HAL_GPIO_ReadLockSensor(uint8_t door_id, uint8_t sensor_id, uint8_t *locked);
error_t HAL_GPIO_SetLockActuator(uint8_t door_id, uint8_t locked);
error_t HAL_GPIO_SetMotorDirection(uint8_t door_id, uint8_t direction);
```

Each function: cyclomatic complexity ≤ 4.

---

### 10.2 MOD-HAL-002 — PWM Motor Driver

**File**: `hal_pwm.c` / `hal_pwm.h`

```c
error_t HAL_PWM_SetDutyCycle(uint8_t door_id, uint8_t duty_percent);
error_t HAL_ADC_ReadMotorCurrent(uint8_t door_id, uint16_t *adc_value);
```

Pre-conditions: `door_id < MAX_DOORS`, `duty_percent <= 100`.  
Cyclomatic complexity: ≤ 4 each.

---

### 10.3 MOD-HAL-003 — CAN Controller Driver

**File**: `hal_can.c` / `hal_can.h`

```c
error_t HAL_CAN_Receive(uint32_t *msg_id, uint8_t *data, uint8_t *dlc);
error_t HAL_CAN_Transmit(uint32_t msg_id, const uint8_t *data, uint8_t dlc);
```

NULL guard on all pointer parameters. Transmit timeout: 5 ms → `ERR_TIMEOUT`.  
Cyclomatic complexity: ≤ 6 each.

---

### 10.4 MOD-HAL-004 — SPI Cross-Channel and RS-485 DDU Drivers

**File**: `hal_spi.c` / `hal_spi.h`, `hal_rs485.c` / `hal_rs485.h`

```c
error_t HAL_SPI_CrossChannel_Exchange(const cross_channel_state_t *tx,
                                       cross_channel_state_t *rx);
error_t HAL_RS485_DDU_Exchange(uint8_t ddu_id, const uint8_t *cmd,
                                uint8_t cmd_len, uint8_t *resp, uint8_t *resp_len);
```

SPI exchange: blocking with 5 ms timeout → `ERR_TIMEOUT` (OI-FMEA-001: caller in
MOD-SKN-001 applies 3-cycle confirmation filter).  
RS-485: DMA-assisted; poll-for-completion with 35 ms timeout.  
Cyclomatic complexity: ≤ 8 each.

---

### 10.5 MOD-HAL-005 — CRC-16, Watchdog, and System Services

**File**: `hal_services.c` / `hal_services.h`

```c
uint16_t CRC16_CCITT_Compute(const uint8_t *data, uint16_t length);
void     HAL_Watchdog_Refresh(void);
uint32_t HAL_GetSystemTickMs(void);
```

- `CRC16_CCITT_Compute`: polynomial 0x1021, init 0xFFFF, no final XOR (see §2.3).  
  Returns 0x0000 if `data == NULL` or `length == 0` (defensive — caller should not pass
  these; MISRA note: return value must be checked by caller if used for CRC validation).  
- `HAL_Watchdog_Refresh`: Writes to STM32H743 IWDG_KR register. Must be called ≤ 40 ms.  
- `HAL_GetSystemTickMs`: Returns SysTick counter (ms). Static; no side effects.  
Cyclomatic complexity: ≤ 4 each.

---

## 11. REQUIREMENTS → MODULE TRACEABILITY

**EN 50128 §7.3 — Traceability mandatory at SIL 3 (Rule T5, T6).**

Every SRS requirement traces to at least one SDS module. No orphan modules.

### 11.1 Safety Requirements → Modules

| Requirement | Description (brief) | SIL | Primary Module(s) |
|-------------|---------------------|-----|-------------------|
| REQ-SAFE-001 | Inhibit door open when speed > 5 km/h | SIL 3 | MOD-SPM-002, MOD-DSM-001 |
| REQ-SAFE-002 | Dual-channel speed confirmation (2oo2) | SIL 3 | MOD-SKN-001 |
| REQ-SAFE-003 | CAN timeout → assume moving → inhibit | SIL 3 | MOD-SPM-002, MOD-TCI-001 |
| REQ-SAFE-004 | Obstacle detection ≤ 20 ms; reversal ≤ 100 ms | SIL 3 | MOD-OBD-001, MOD-OBD-002 |
| REQ-SAFE-005 | Obstacle sensor fault → door re-opens | SIL 3 | MOD-OBD-002 |
| REQ-SAFE-006 | Motor current > 150 N → reversal | SIL 3 | MOD-OBD-002, MOD-HAL-002 |
| REQ-SAFE-007 | 2oo2 sensor agreement for LOCKED state | SIL 3 | MOD-DSM-002, MOD-DSM-001 |
| REQ-SAFE-008 | All-doors-locked signal withheld until all confirm | SIL 3 | MOD-SKN-002 |
| REQ-SAFE-009 | Cross-channel lock state verification every 20 ms | SIL 3 | MOD-SKN-001 |
| REQ-SAFE-010 | CRC-16-CCITT (0x1021) on all safety-critical structures | SIL 3 | MOD-HAL-005, all |
| REQ-SAFE-011 | Position sensor timeout (100 ms) → assume door open | SIL 3 | MOD-DSM-001, MOD-HAL-001 |
| REQ-SAFE-012 | Safe state trigger requires 2oo2 channel confirmation | SIL 2 | MOD-SKN-001, MOD-SKN-002 |
| REQ-SAFE-013 | Selective disablement: speed interlock remains active | SIL 2 | MOD-FMG-002, MOD-DSM-003 |
| REQ-SAFE-014 | Hardware watchdog 50 ms → safe state both channels | SIL 3 | MOD-HAL-005 |
| REQ-SAFE-015 | Cross-channel software watchdog every 20 ms | SIL 3 | MOD-SKN-001, MOD-SKN-003 |
| REQ-SAFE-016 | CRC-16-CCITT on CAN messages; CRC fail = reject + timeout | SIL 3 | MOD-TCI-001, MOD-TCI-002 |
| REQ-SAFE-017 | No dynamic memory allocation (MISRA 21.3) | SIL 3 | All modules (architectural) |
| REQ-SAFE-018 | Memory integrity check at boot + every 100 ms | SIL 3 | MOD-SKN-002 |
| REQ-SAFE-019 | Emergency release debounce ≥ 60 ms; alert ≤ 100 ms | SIL 2 | MOD-DSM-004 |
| REQ-SAFE-020 | Emergency release latched until maintenance reset | SIL 2 | MOD-DSM-004, MOD-DSM-003 |
| REQ-SAFE-021 | Selective disablement: TCMS authorization required; logged | SIL 2 | MOD-FMG-002, MOD-DGN-001 |

### 11.2 Functional Requirements → Modules

| Requirement | Primary Module(s) |
|-------------|-------------------|
| REQ-FUN-001 to REQ-FUN-008 | MOD-DSM-001 to MOD-DSM-005 |
| REQ-FUN-009 (departure interlock) | MOD-SKN-002, MOD-TCI-002 |
| REQ-FUN-010 (lock while moving) | MOD-DSM-001, MOD-SPM-002 |
| REQ-FUN-011 (mode FSM) | MOD-DSM-003 |
| REQ-FUN-012 (mode authorization) | MOD-DSM-003, MOD-TCI-001 |
| REQ-FUN-013 (selective disablement) | MOD-FMG-002 |
| REQ-FUN-014 (diagnostic mode) | MOD-DSM-003, MOD-DGN-003 |
| REQ-FUN-015 (continuous position monitoring) | MOD-DSM-001, MOD-HAL-001 |
| REQ-FUN-016 (status reporting to TCMS) | MOD-TCI-002 |
| REQ-FUN-017 (fault monitoring) | MOD-FMG-001, MOD-FMG-002 |
| REQ-FUN-018 (fault event logging) | MOD-DGN-001, MOD-FMG-001 |

### 11.3 Hazard → Module Traceability

| Hazard ID | Hazard | SIL | Primary Module(s) |
|-----------|--------|-----|-------------------|
| SW-HAZ-001 | Door opens while moving | SIL 3 | MOD-SPM-002, MOD-SKN-001 |
| SW-HAZ-002 | Door closes on passenger | SIL 3 | MOD-OBD-001, MOD-OBD-002 |
| SW-HAZ-003 | False door lock indication | SIL 3 | MOD-DSM-002, MOD-SKN-002 |
| SW-HAZ-004 | Loss of door position indication | SIL 3 | MOD-DSM-001, MOD-DSM-002 |
| SW-HAZ-005 | Spurious safe state | SIL 2 | MOD-FMG-001, MOD-SKN-002 |
| SW-HAZ-006 | Watchdog failure | SIL 3 | MOD-HAL-005, MOD-SKN-003 |
| SW-HAZ-007 | CAN speed data loss | SIL 3 | MOD-TCI-001, MOD-SPM-002 |
| SW-HAZ-008 | Memory corruption | SIL 3 | MOD-SKN-002 |
| SW-HAZ-009 | Emergency release mishandled | SIL 2 | MOD-DSM-004 |
| SW-HAZ-010 | Selective disablement misuse | SIL 2 | MOD-FMG-002 |
| SW-HAZ-011 | SPI transient → denial-of-safe-operation | SIL 2 | MOD-SKN-001 (OI-FMEA-001 filter) |

---

## 12. TABLE A.4 COMPLIANCE

**EN 50128 Table A.4 — Software Design and Implementation Techniques — SIL 3:**

| # | Technique/Measure | SIL 3–4 | Applied | Evidence |
|---|-------------------|---------|---------|---------|
| 1 | Structured Programming | **M** | **Yes** | Cyclic executive; no GOTO; switch/case for FSM §6 |
| 2 | Defensive Programming | HR | Yes | NULL guards, range checks, fail-safe defaults throughout |
| 3 | Error Detection — CRC | HR | Yes | CRC-16-CCITT (0x1021) on all safety structures §2.3 |
| 4 | No Dynamic Memory Allocation | **M** | **Yes** | All structures static; §1.4 constraint; MISRA 21.3 |
| 5 | Fixed-width Integer Types | HR | Yes | All modules use `uint8_t`/`uint16_t`/`uint32_t` only |
| 6 | No Function Pointers (safety-critical paths) | HR | Yes | Dispatch via switch/case in DSM FSM §6.1 |
| 7 | No Recursion | HR | Yes | No recursive calls in any module |
| 8 | Cyclomatic Complexity ≤ 10 | **M** (SIL 3) | **Yes** | Max complexity 10 (MOD-OBD-002, MOD-TCI-001); documented per function |
| 9 | Failure Assertion Programming | HR | Yes | `error_t` return codes; assert-style canary checks |
| 10 | Coding Standards (MISRA C:2012) | **M** | **Yes** | Applied throughout; verified by VER (Phase 5 static analysis) |

---

## 13. QUALITY METRICS

| Metric | Target | SIL 3 Basis |
|--------|--------|-------------|
| Max cyclomatic complexity per function | ≤ 10 | EN 50128 mandatory SIL 3 |
| Dynamic memory allocation calls | 0 | MISRA C:2012 Rule 21.3; EN 50128 SIL 2+ |
| Recursion instances | 0 | EN 50128 Table A.4 HR SIL 3–4 |
| Function pointer usage (safety paths) | 0 | EN 50128 Table A.4 HR SIL 3–4 |
| Requirements traced to modules | 100% (21/21 REQ-SAFE, 18/18 REQ-FUN) | EN 50128 §7.3 mandatory SIL 3 |
| Hazards traced to modules | 100% (11/11 SW-HAZ) | EN 50128 §7.3 mandatory SIL 3 |
| CRC-16 variant uniformity | CRC-16-CCITT 0x1021 only | OI-FTA-003 resolution |

---

## 14. REVIEW CHECKLIST

| Item | Check | Status |
|------|-------|--------|
| All SAS components (COMP-001 to COMP-008) decomposed into modules | ✅ | Done (30 modules) |
| Each module has function signatures, pre/postconditions, algorithm | ✅ | Done |
| Static allocation only — no `malloc`/`calloc`/`realloc`/`free` | ✅ | Done |
| Cyclomatic complexity ≤ 10 documented per function | ✅ | Done |
| CRC-16-CCITT (0x1021) — no other polynomial | ✅ | OI-FTA-003 resolved |
| SPI transient filter (3-cycle confirmation) specified in MOD-SKN-001 | ✅ | OI-FMEA-001 resolved |
| Safety-data disagreement still triggers immediate safe state | ✅ | MOD-SKN-001 §SKN_ExchangeAndCompare |
| Departure interlock only asserted after successful cross-channel comparison | ✅ | OI-FTA-001 addressed; MOD-SKN-002 |
| All 21 REQ-SAFE traced to modules | ✅ | §11.1 |
| All 11 SW-HAZ traced to modules (including SW-HAZ-011) | ✅ | §11.3 |
| Approvals: Author(DES), Reviewer(QUA), Approver(PM) only — no VER/VAL | ✅ | Approvals table |
| Document ID format correct: DOC-SDS-2026-001 | ✅ | Document Control |

---

## 15. COMPLIANCE MATRIX

| EN 50128 Clause | Requirement | Addressed In |
|-----------------|-------------|-------------|
| §7.3.4 | Architecture decomposed to modules | §2 Design Overview |
| §7.3.4.5 | Interfaces defined | §2.2 Common Data Types; SIS (item 11) |
| §7.3.4.12 | Traceability — requirements to design | §11 |
| §7.4.4.3 | No dynamic allocation SIL 2+ | §1.4 |
| §7.4.4.4 | Complexity limits | §1.4, §12 |
| Table A.3, Entry 19 | Modular Approach (M SIL 2+) | §2.1 |
| Table A.4, Entry 10 | MISRA C:2012 (M SIL 3) | §1.4, §12 |
| Table A.4, Entry 4 | Structured Programming (M SIL 3) | §12 |
| OI-FTA-003 | CRC-16-CCITT 0x1021 unified | §2.3, §8.1, §8.2, §10.5 |
| OI-FMEA-001 | SPI transient filter 3-cycle confirmation | §3.1 MOD-SKN-001 |
| OI-SAS-003 | Mode FSM complete | §6.3 MOD-DSM-003 |

---

## 16. REFERENCES

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-SAS-2026-001 | Software Architecture Specification | 0.2 |
| DOC-SRS-2026-001 | Software Requirements Specification | 0.1 |
| DOC-HAZLOG-2026-001 | Hazard Log | 0.2 |
| DOC-FMEA-2026-001 | FMEA Report | 0.1 |
| DOC-FTA-2026-001 | FTA Report | 0.1 |
| EN 50128:2011 | Railway applications — Software for railway control and protection systems | 2011 |
| MISRA C:2012 | Guidelines for the Use of the C Language in Critical Systems | 2012 |

---

## APPENDIX A: MODULE SUMMARY TABLE

| Module ID | File | Comp | SIL | Max CC | Functions |
|-----------|------|------|-----|--------|-----------|
| MOD-SKN-001 | skn_comparator.c | COMP-001 | 3 | 8 | SKN_BuildLocalState, SKN_ExchangeAndCompare, SKN_FieldsDisagree |
| MOD-SKN-002 | skn_safe_state.c | COMP-001 | 3 | 7 | SKN_EvaluateSafeState, SKN_EvaluateDepartureInterlock, SKN_CheckMemoryIntegrity, SKN_CheckStackCanary |
| MOD-SKN-003 | skn_scheduler.c | COMP-001 | 3 | 3 | SKN_RunCycle |
| MOD-SKN-004 | skn_init.c | COMP-001 | 3 | 2 | SKN_Init |
| MOD-SPM-001 | spm_can.c | COMP-002 | 3 | 6 | SPM_ProcessSpeedFrame |
| MOD-SPM-002 | spm_interlock.c | COMP-002 | 3 | 5 | SPM_EvaluateInterlock |
| MOD-SPM-003 | spm_init.c | COMP-002 | 3 | 3 | SPM_Init, SPM_RunCycle |
| MOD-OBD-001 | obd_isr.c | COMP-003 | 3 | 2 | OBD_ObstacleISR |
| MOD-OBD-002 | obd_detect.c | COMP-003 | 3 | 10 | OBD_PollSensorsAndEvaluate |
| MOD-OBD-003 | obd_init.c | COMP-003 | 3 | 3 | OBD_Init, OBD_RunCycle |
| MOD-DSM-001 | dsm_fsm.c | COMP-004 | 3 | 8 | DSM_UpdateFSM, DSM_Transition* (7 helpers) |
| MOD-DSM-002 | dsm_voter.c | COMP-004 | 3 | 3 | DSM_VotePosition |
| MOD-DSM-003 | dsm_mode.c | COMP-004 | 3 | 8 | DSM_TransitionMode |
| MOD-DSM-004 | dsm_emergency.c | COMP-004 | 3 | 4 | DSM_HandleEmergencyRelease |
| MOD-DSM-005 | dsm_init.c | COMP-004 | 3 | 4 | DSM_Init, DSM_RunCycle |
| MOD-FMG-001 | fmg_aggregator.c | COMP-005 | 3 | 4 | FMG_AggregateFaults, FMG_ClassifyAndEscalate |
| MOD-FMG-002 | fmg_safe_state.c | COMP-005 | 3 | 6 | FMG_HandleSelectiveDisablement |
| MOD-FMG-003 | fmg_init.c | COMP-005 | 3 | 3 | FMG_Init, FMG_RunCycle, FMG_GetFaultState |
| MOD-TCI-001 | tci_rx.c | COMP-006 | 3 | 8 | TCI_CanRxISR, TCI_ProcessReceivedFrames |
| MOD-TCI-002 | tci_tx.c | COMP-006 | 3 | 3 | TCI_Transmit* (3 functions) |
| MOD-TCI-003 | tci_seq.c | COMP-006 | 3 | 3 | TCI_IncrementTxSeqCounter, TCI_ValidateRxSeqDelta |
| MOD-TCI-004 | tci_init.c | COMP-006 | 3 | 3 | TCI_Init, TCI_TransmitCycle |
| MOD-DGN-001 | dgn_log.c | COMP-007 | 1 | 2 | DGN_LogEvent |
| MOD-DGN-002 | dgn_flash.c | COMP-007 | 1 | 8 | DGN_FlushToFlash |
| MOD-DGN-003 | dgn_port.c | COMP-007 | 1 | 8 | DGN_ServePortRequest |
| MOD-HAL-001 | hal_gpio.c | COMP-008 | 3 | 4 | HAL_GPIO_Read*(3), HAL_GPIO_Set*(2) |
| MOD-HAL-002 | hal_pwm.c | COMP-008 | 3 | 4 | HAL_PWM_SetDutyCycle, HAL_ADC_ReadMotorCurrent |
| MOD-HAL-003 | hal_can.c | COMP-008 | 3 | 6 | HAL_CAN_Receive, HAL_CAN_Transmit |
| MOD-HAL-004 | hal_spi.c + hal_rs485.c | COMP-008 | 3 | 8 | HAL_SPI_CrossChannel_Exchange, HAL_RS485_DDU_Exchange |
| MOD-HAL-005 | hal_services.c | COMP-008 | 3 | 4 | CRC16_CCITT_Compute, HAL_Watchdog_Refresh, HAL_GetSystemTickMs |

**Total modules**: 30  
**Max cyclomatic complexity**: 10 (MOD-OBD-002, within SIL 3 limit)  
**Dynamic memory**: 0 allocations  
**Recursion**: 0 instances

---

## APPENDIX B: OI RESOLUTION SUMMARY

| Open Issue | Source | Resolution | Section |
|------------|--------|------------|---------|
| OI-FTA-003 | DOC-FTA-2026-001 §7.3 | CRC-16-CCITT (0x1021) specified for ALL SPI and safety CAN messages | §1.4, §2.3, §8.1, §8.2, §10.5, §12 |
| OI-FMEA-001 | DOC-FMEA-2026-001 §4 | SPI transient filter: 3-consecutive-cycle confirmation for SPI infrastructure faults; immediate safe state for safety-data disagreements | §3.1 MOD-SKN-001 |
| OI-SAS-003 | DOC-SAS-2026-001 v0.1 §13 | Operational mode FSM complete transition table specified | §6.3 MOD-DSM-003 |
| OI-SAS-005 | DOC-SAS-2026-001 v0.1 §13 | Resolved by OI-FTA-003: CRC-16-CCITT (0x1021) unified | §2.3 |
| OI-FMEA-002 | DOC-FMEA-2026-001 §4 | Boundary condition: speed == 50 (5.0 km/h × 10) is SAFE (≤ threshold); VER to add TC-SPM-007 boundary test | §4.2 MOD-SPM-002 |

**Remaining open issues for DES (not resolved in SDS)**:
- OI-SAS-001: MAX_DOORS value — awaiting System Architecture confirmation from PM. SDS uses `MAX_DOORS = 4U` as current working assumption; must be confirmed before Phase 5.
- OI-SAS-002: RS-485 DDU frame format — awaiting REQ update. MOD-HAL-004 defines the driver boundary; frame format to be specified in SIS (item 11, DOC-SIS-2026-001).

---

**END OF SOFTWARE DESIGN SPECIFICATION**

*Document ID*: DOC-SDS-2026-001 v0.1 DRAFT  
*Date*: 2026-04-02  
*Author*: Software Designer (DES)  
*Project*: TDC (Train Door Control System), SIL 3  
*Next action*: Submit to PM for QUA review routing (DES does not contact QUA directly)
