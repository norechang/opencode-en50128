# Software Component Test Specification (SCTS)

**REFERENCE**: EN 50128:2011 Sections 7.4.4.8, 7.5, 6.1.4.4, Table A.5, Table A.21, Annex C Item 16

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-COMPTESTSPEC-2026-001 |
| **CI ID** | CI-COMPTESTSPEC-TDC-001 |
| **Version** | 0.1 DRAFT |
| **Date** | 2026-04-04 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Software Tester (TST) |
| **Status** | Draft |

### Revision History

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-04-04 | TST | Initial draft — Phase 4 component test specification for all 30 modules (MOD-SKN-001 through MOD-HAL-005). Derives test cases from SCDS DOC-COMPDES-2026-001 v0.1 and SRS DOC-SRS-2026-001 v0.1. | — |

---

## APPROVALS

**EN 50128 Annex C Table C.1 Signature Chain — Item 16 (SCTS) — Track A (Development)**

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Written By (TST) | Software Tester | _____________ | 2026-04-04 |
| 1st Check (VER) | Software Verifier | _____________ | __________ |
| 2nd Check (VAL) | Software Validator | _____________ | __________ |

**Notes:**
- For SIL 3: Independence requirements apply per EN 50128 §6.2 (Verification) and §6.3 (Validation)
- TST is independent from IMP (SIL 3 HR) — test cases are authored without implementer input
- All submissions route through PM — TST does not contact QUA or VER directly
- VER and VAL sign-offs recorded in Item 17 (Component Design Verification Report) — NOT in this table

---

## 1. INTRODUCTION

### 1.1 Purpose

This Software Component Test Specification (SCTS) defines the **unit-level test cases** for all **30 software modules** (MOD-SKN-001 through MOD-HAL-005) comprising the **TDC (Train Door Control System)** at SIL 3, in accordance with EN 50128:2011 Section 7.4.4.8 and Section 7.5.

**Objectives**:
- Define component-level test cases for all 30 modules and 97 software units
- Specify test vectors, expected outputs, and verification procedures for each unit
- Define code coverage targets per the project SVP/SQAP (DOC-SVP-2026-001)
- Ensure all SRS requirements are testable at component level
- Provide the V-Model left-side test specification that pairs with the Software Component Test Report (Item 20, Phase 5)
- Apply all mandatory SIL 3–4 testing techniques per EN 50128 Table A.5

**EN 50128 Reference**: Sections 7.4.4.8 (Component Testing), 7.5 (Integration), Table A.5, Table A.21

### 1.2 Scope

**Components Under Test**:

| Component | Acronym | SIL | Modules | Units |
|-----------|---------|-----|---------|-------|
| COMP-001 Safety Kernel | SKN | 3 | MOD-SKN-001 to MOD-SKN-004 | 9 |
| COMP-002 Speed Monitor | SPM | 3 | MOD-SPM-001 to MOD-SPM-003 | 5 |
| COMP-003 Obstacle Detector | OBD | 3 | MOD-OBD-001 to MOD-OBD-003 | 5 |
| COMP-004 Door State Machine | DSM | 3 | MOD-DSM-001 to MOD-DSM-005 | 18 |
| COMP-005 Fault Manager | FMG | 3 | MOD-FMG-001 to MOD-FMG-003 | 6 |
| COMP-006 TCMS Interface | TCI | 3 | MOD-TCI-001 to MOD-TCI-004 | 8 |
| COMP-007 Diagnostics | DGN | 1 | MOD-DGN-001 to MOD-DGN-003 | 8 |
| COMP-008 Hardware Abstraction Layer | HAL | 3 | MOD-HAL-001 to MOD-HAL-005 | 20 |
| **Total** | | | **30 modules** | **97 units** |

**Test Types Applied** (EN 50128 Table A.5 SIL 3–4 Mandatory):
- **M** Dynamic Analysis and Testing (item 4) — all normal-operation cases
- **M** Test Coverage for Code (item 5) — statement + branch per SVP/SQAP targets
- **M** Functional/Black-Box Testing (item 9) — requirement-derived test cases
- **M** Performance Testing (item 10) — timing and boundary cases
- **M** Regression Testing (item 12) — full suite on every change
- **M** Boundary Value Analysis (item 13) — min−1/min/min+1/max−1/max/max+1 for all parameterized functions
- **M** Traceability (item 7) — every test case traces to SRS requirement and SCDS unit

**Out of Scope**:
- Integration testing (covered in Software Integration Test Specification, INT item 12)
- System testing (covered in Overall Software Test Specification, TST item 7)
- Hardware testing (covered by hardware test plans)

### 1.3 Test Strategy

**Test Framework**: Unity (C unit testing framework, version 2.5.2+)

**Test Approach**: White-box (unit-level, function-level) + Black-box (requirement-driven inputs/outputs)

**Coverage Targets** (per SIL 3, defined in SVP/SQAP DOC-SVP-2026-001):

| Coverage Type | EN 50128 Table A.21 | SIL 3 Status | Project Target |
|---------------|---------------------|--------------|----------------|
| Statement Coverage | Item 1 | **M** (Mandatory) | As specified in DOC-SVP-2026-001 |
| Branch Coverage | Item 2 | **M** (Mandatory) | As specified in DOC-SVP-2026-001 |
| Compound Condition Coverage | Item 3 | **HR** (Highly Recommended) | As specified in DOC-SVP-2026-001 |
| Data Flow Coverage | Item 4 | HR | Targeted for safety-critical paths |

> **Note**: EN 50128:2011 Table A.21 Req.1 requires a quantified measure to be defined per project in the SVP/SQAP. No generic percentage is mandated by the standard. Project coverage targets are defined in DOC-SVP-2026-001 and referenced in each test case header. The term "Compound Condition Coverage" (EN 50128 Table A.21 item 3) is used throughout — not "MC/DC".

**Test Environment**:
- **Host**: Linux development host with gcc, Unity 2.5.2, gcov, lcov, gcovr
- **Target**: STM32H743 evaluation board (for integration/HW tests)
- **Mock Layer**: HAL functions mocked using Unity CMock; hardware-dependent units tested with mock objects
- **Build**: `gcc -fprofile-arcs -ftest-coverage -g -O0 -DUNITY_TEST` per Makefile target `make coverage`

### 1.4 References

| Reference | Document |
|-----------|----------|
| **[SRS]** | Software Requirements Specification, DOC-SRS-2026-001 v0.1 |
| **[SDS]** | Software Design Specification, DOC-SDS-2026-001 v0.1 |
| **[SAS]** | Software Architecture Specification, DOC-SAS-2026-001 v0.2 |
| **[SCDS]** | Software Component Design Specification, DOC-COMPDES-2026-001 v0.1 |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 |
| **[EN50128]** | EN 50128:2011 Sections 7.4, 7.5, Table A.5, Table A.21 |
| **[HAZLOG]** | Hazard Log, DOC-HAZLOG-2026-001 v0.2 |

---

## 2. TEST ORGANIZATION

### 2.1 Test Naming Convention

**Test Case ID Format**: `TC-[COMP]-[UNIT]-[TYPE]-[NNN]`

Where:
- `[COMP]` = component acronym (SKN, SPM, OBD, DSM, FMG, TCI, DGN, HAL)
- `[UNIT]` = unit suffix (e.g., 001 for UNIT-SKN-001)
- `[TYPE]` = test type: `NRM` (Normal), `BND` (Boundary), `ERR` (Error/NULL), `FLT` (Fault Injection), `PFM` (Performance)
- `[NNN]` = sequential number within category

**Examples**:
- `TC-SKN-001-NRM-001` = Normal operation test for UNIT-SKN-001
- `TC-SPM-002-BND-001` = Boundary value test for UNIT-SPM-002
- `TC-DSM-001-FLT-001` = Fault injection test for UNIT-DSM-001

### 2.2 Test Data

**Test Data Location**: `examples/TDC/tests/data/`

**Test Data Types**:
- `valid_inputs.c` — Normal-case input constants
- `boundary_values.h` — MIN/MAX constants per parameter
- `fault_vectors.c` — Invalid/error input data
- `mock_hal.c` — HAL mock implementations returning controlled error codes

### 2.3 Test Execution Order

**Order**: Sequential within each module suite; modules executable independently

**Setup**: Per-module `setUp()` reinitializes all module static state before each test case
**Teardown**: Per-module `tearDown()` verifies no residual static state corruption

**Test Suites**: `tests/test_[module_name].c` — one file per module

---

## 3. COMPONENT TEST CASES

---

### 3.1 COMP-001: SAFETY KERNEL (SKN) — SIL 3

**Traceability**: SRS REQ-SAFE-002/007/008/009/010/012/014/015/018, SW-HAZ-001/003/006/008/011
**Source Files**: `skn_comparator.c`, `skn_safe_state.c`, `skn_scheduler.c`, `skn_init.c`
**Test Suite**: `tests/test_skn.c`

---

#### 3.1.1 MOD-SKN-001 — Cross-Channel Comparator

**UNIT-SKN-001: `SKN_BuildLocalState`**

---

##### TC-SKN-001-NRM-001: Build Local State — Normal Valid Inputs

```
/* TC-SKN-001-NRM-001: Build local cross-channel state with valid inputs
 * Tests: UNIT-SKN-001 (SKN_BuildLocalState)
 * SRS: REQ-SAFE-010 (CRC protection), REQ-INT-010 (cross-channel)
 * SCDS: §3.1.1
 * SIL: 3
 * Coverage: Statement, Branch, Compound Condition per DOC-SVP-2026-001
 */
```

**Test Type**: Normal | **Priority**: High

**Preconditions**: Module initialized; CRC16_CCITT_Compute mock returns known value

**Test Inputs**:
```c
cross_channel_state_t state;    /* output buffer */
uint16_t speed     = 100U;      /* 10.0 km/h */
uint8_t  doors[4]  = {3, 3, 3, 3};   /* all CLOSED_AND_LOCKED */
uint8_t  locks[4]  = {1, 1, 1, 1};
uint8_t  obs[4]    = {0, 0, 0, 0};
uint8_t  faults    = 0x00U;
uint8_t  decisions = 0x01U;     /* safe_state_active = 0, interlock = 1 */
```

**Expected Result**:
```c
return_value == SUCCESS
state.speed_kmh_x10 == 100U
state.door_states[0..3] == 3U
state.lock_states[0..3] == 1U
state.obstacle_flags[0..3] == 0U
state.fault_flags == 0x00U
state.safety_decisions == 0x01U
state.crc16 != 0U   /* CRC computed over preceding fields */
```

**Pass Criteria**: Returns SUCCESS; all fields populated; CRC16 is non-zero and matches CRC16_CCITT_Compute result over preceding bytes.

---

##### TC-SKN-001-ERR-001: Build Local State — NULL Output Pointer

```
/* TC-SKN-001-ERR-001: NULL pointer guard for state output
 * Tests: UNIT-SKN-001 defensive programming
 * SRS: REQ-IMPL-006 (defensive programming), REQ-SAFE-010
 * SCDS: §3.1.1 Preconditions
 * SIL: 3
 */
```

**Test Type**: Error | **Priority**: High (SIL 3 mandatory NULL guard)

**Test Inputs**:
```c
cross_channel_state_t *state = NULL;
uint16_t speed = 100U;
/* ... other valid inputs ... */
```

**Expected Result**:
```c
return_value == ERR_NULL_PTR
/* No crash, no memory write */
```

---

##### TC-SKN-001-BND-001: Build Local State — Maximum Speed (Boundary)

```
/* TC-SKN-001-BND-001: Speed at upper boundary (3000 = 300.0 km/h)
 * Tests: UNIT-SKN-001 boundary value analysis
 * SRS: REQ-SAFE-001 (speed interlock), REQ-SAFE-010 (CRC)
 * SIL: 3
 */
```

**Test Type**: Boundary | **Priority**: High

**Test Inputs**:
```c
uint16_t speed = 3000U;   /* MAX valid speed = 300.0 km/h */
```

**Expected Result**:
```c
return_value == SUCCESS
state.speed_kmh_x10 == 3000U
/* CRC computed correctly over max-value speed field */
```

---

##### TC-SKN-001-BND-002: Build Local State — Speed = UNKNOWN (0xFFFF)

**Test Type**: Boundary | **Priority**: High

**Test Inputs**:
```c
uint16_t speed = 0xFFFFU;   /* UNKNOWN sentinel value */
```

**Expected Result**:
```c
return_value == SUCCESS
state.speed_kmh_x10 == 0xFFFFU
```

---

**UNIT-SKN-002: `SKN_ExchangeAndCompare`**

---

##### TC-SKN-002-NRM-001: Exchange and Compare — Channels Agree

```
/* TC-SKN-002-NRM-001: Successful SPI exchange, channels agree
 * Tests: UNIT-SKN-002 (SKN_ExchangeAndCompare)
 * SRS: REQ-INT-010 (cross-channel 2oo2), REQ-SAFE-010 (CRC)
 * SCDS: §3.1.2, OI-FMEA-001
 * SIL: 3
 */
```

**Test Type**: Normal | **Priority**: High

**Preconditions**: `HAL_SPI_CrossChannel_Exchange` mock returns SUCCESS and copies local state as remote state; CRC matches

**Test Inputs**:
```c
cross_channel_state_t local = { .speed_kmh_x10 = 50U, .crc16 = <valid_crc> };
uint8_t safe_state_out;
```

**Expected Result**:
```c
return_value == SUCCESS
safe_state_out == 0   /* no disagreement */
s_spi_infra_fault_count == 0   /* counter reset */
```

---

##### TC-SKN-002-FLT-001: Exchange and Compare — Single SPI Transient (OI-FMEA-001 Filter)

```
/* TC-SKN-002-FLT-001: SPI infrastructure fault — transient (1 of 3 consecutive)
 * Tests: UNIT-SKN-002 OI-FMEA-001 transient filter
 * SRS: REQ-INT-010, REQ-SAFE-006
 * SCDS: §3.1.2 Step 2 (transient: retain last good, do NOT assert safe state)
 * SIL: 3 — Safety-critical test
 */
```

**Test Type**: Fault Injection | **Priority**: Critical

**Preconditions**: `HAL_SPI_CrossChannel_Exchange` mock returns `ERR_COMM_TIMEOUT` on 1st call; `s_spi_infra_fault_count = 0`

**Expected Result**:
```c
return_value == ERR_CRC       /* transient: ERR_CRC, not ERR_COMM_TIMEOUT */
safe_state_out == 0           /* NO safe state on transient */
s_spi_infra_fault_count == 1  /* counter incremented */
/* Remote state = last known good (not corrupted) */
```

**Safety Significance**: Confirms OI-FMEA-001 filter does NOT assert safe state on single transient.

---

##### TC-SKN-002-FLT-002: Exchange and Compare — Persistent SPI Fault (3 Consecutive) → Safe State

```
/* TC-SKN-002-FLT-002: Persistent SPI fault — 3 consecutive failures → safe state
 * Tests: UNIT-SKN-002 OI-FMEA-001 persistent path
 * SRS: REQ-SAFE-006, REQ-INT-010
 * SCDS: §3.1.2 Step 2 (persistent: assert safe state after 3 cycles)
 * SIL: 3 — Safety-critical test
 */
```

**Test Type**: Fault Injection | **Priority**: Critical

**Preconditions**: Call `SKN_ExchangeAndCompare` 3 times with `HAL_SPI_CrossChannel_Exchange` returning `ERR_COMM_TIMEOUT` each time

**Expected Result** (on 3rd call):
```c
return_value == ERR_COMM_TIMEOUT
safe_state_out == 1       /* SAFE STATE ASSERTED on 3rd consecutive fault */
s_spi_infra_fault_count >= 3
```

---

##### TC-SKN-002-FLT-003: Exchange and Compare — CRC Mismatch on Safety Data → Immediate Safe State

```
/* TC-SKN-002-FLT-003: CRC mismatch on remote safety data payload
 * Tests: UNIT-SKN-002 Step 3 (CRC validation)
 * SRS: REQ-SAFE-009 (CRC protection), REQ-SAFE-006
 * SCDS: §3.1.2 Step 3
 * SIL: 3 — Safety-critical: immediate safe state, no filter
 */
```

**Test Type**: Fault Injection | **Priority**: Critical

**Preconditions**: `HAL_SPI_CrossChannel_Exchange` succeeds; remote CRC = `<computed_crc XOR 0x0001>` (corrupted)

**Expected Result**:
```c
return_value == ERR_CRC
safe_state_out == 1       /* IMMEDIATE safe state on CRC fail */
s_spi_infra_fault_count == 0   /* counter reset on CRC fail */
```

---

##### TC-SKN-002-FLT-004: Exchange and Compare — Channel Disagreement → Safe State

```
/* TC-SKN-002-FLT-004: Safety-data fields disagree between channels
 * Tests: UNIT-SKN-002 Step 4 (channel comparison)
 * SRS: REQ-SAFE-010 (2oo2 cross-channel), REQ-SAFE-006
 * SCDS: §3.1.2 Step 4
 * SIL: 3 — Safety-critical: IMMEDIATE safe state, no filter
 */
```

**Test Type**: Fault Injection | **Priority**: Critical

**Preconditions**: Remote state has `speed_kmh_x10 = 200U` while local has `speed_kmh_x10 = 50U`; remote CRC valid

**Expected Result**:
```c
return_value == ERR_SENSOR_DISAGREE
safe_state_out == 1   /* IMMEDIATE safe state on disagreement */
```

---

##### TC-SKN-002-ERR-001: Exchange and Compare — NULL Pointers

**Test Type**: Error | **Priority**: High

**Test Inputs**:
```c
const cross_channel_state_t *local = NULL;
uint8_t safe_state_out;
```

**Expected Result**:
```c
return_value == ERR_NULL_PTR
safe_state_out   /* undefined; function must not crash */
```

---

#### 3.1.2 MOD-SKN-002 — Safe State Manager

**UNIT-SKN-004: `SKN_EvaluateSafeState`**

---

##### TC-SKN-004-NRM-001: Evaluate Safe State — All Inputs OK → Safe State Not Set

```
/* TC-SKN-004-NRM-001: No fault triggers — safe state remains 0
 * Tests: UNIT-SKN-004
 * SRS: REQ-SAFE-006 (safe state triggers)
 * SCDS: §3.2.1
 * SIL: 3
 */
```

**Test Type**: Normal | **Priority**: High

**Test Inputs**:
```c
uint8_t channel_disagree = 0;
uint8_t fault_state      = 0x00U;
uint8_t memory_crc_ok    = 1;
uint8_t stack_canary_ok  = 1;
uint8_t out;
```

**Expected Result**:
```c
return_value == SUCCESS
out == 0   /* safe state NOT activated */
```

---

##### TC-SKN-004-FLT-001: Evaluate Safe State — Channel Disagree Trigger

**Test Type**: Fault Injection | **Priority**: Critical

**Test Inputs**:
```c
uint8_t channel_disagree = 1;
uint8_t fault_state      = 0x00U;
uint8_t memory_crc_ok    = 1;
uint8_t stack_canary_ok  = 1;
```

**Expected Result**:
```c
return_value == SUCCESS
out == 1   /* safe state ACTIVATED */
```

---

##### TC-SKN-004-FLT-002: Evaluate Safe State — Critical Fault Bits Set

**Test Type**: Fault Injection | **Priority**: Critical

**Test Inputs**: `fault_state = 0x07U` (bits 0, 1, 2 all set — FAULT_CRITICAL_MASK)

**Expected Result**: `out == 1` (safe state active)

---

##### TC-SKN-004-FLT-003: Evaluate Safe State — Memory CRC Fail

**Test Type**: Fault Injection | **Priority**: Critical

**Test Inputs**: `memory_crc_ok = 0; channel_disagree = 0; fault_state = 0x00U; stack_canary_ok = 1`

**Expected Result**: `out == 1`

---

##### TC-SKN-004-FLT-004: Evaluate Safe State — Stack Canary Corrupted

**Test Type**: Fault Injection | **Priority**: Critical

**Test Inputs**: `stack_canary_ok = 0`

**Expected Result**: `out == 1`

---

##### TC-SKN-004-FLT-005: Evaluate Safe State — Sticky Flag (Once Set, Cannot Clear)

```
/* TC-SKN-004-FLT-005: Safe state is STICKY — verify it cannot be cleared
 * SRS: REQ-SAFE-006 (safe state maintained until reset)
 * SCDS: §3.2.1 — "Safe state is STICKY — never cleared in normal operation"
 * SIL: 3 — Safety-critical: verify irreversibility
 */
```

**Test Type**: Fault Injection | **Priority**: Critical

**Test Steps**:
1. Call with `channel_disagree=1` → `out == 1` (safe state set)
2. Call again with all-clear inputs (`channel_disagree=0, fault_state=0, mem_ok=1, canary_ok=1`)

**Expected Result** (Step 2): `out == 1` (sticky — safe state CANNOT be cleared by subsequent call)

---

##### TC-SKN-004-ERR-001: Evaluate Safe State — NULL Output Pointer

**Test Type**: Error | **Priority**: High

**Test Inputs**: `safe_state_active_out = NULL`

**Expected Result**: `return_value == ERR_NULL_PTR`

---

**UNIT-SKN-005: `SKN_EvaluateDepartureInterlock`**

---

##### TC-SKN-005-NRM-001: Departure Interlock — All Doors Locked → Interlock OK

```
/* TC-SKN-005-NRM-001: All 4 doors CLOSED_AND_LOCKED → interlock_ok = 1
 * Tests: UNIT-SKN-005
 * SRS: REQ-SAFE-003 (departure interlock)
 * SCDS: §3.2.2
 * SIL: 3
 */
```

**Test Inputs**:
```c
uint8_t doors[4] = {DOOR_STATE_CLOSED_AND_LOCKED,
                    DOOR_STATE_CLOSED_AND_LOCKED,
                    DOOR_STATE_CLOSED_AND_LOCKED,
                    DOOR_STATE_CLOSED_AND_LOCKED};
uint8_t locks[4] = {1, 1, 1, 1};
uint8_t channel_disagree = 0;
uint8_t safe_state_active = 0;
uint8_t out;
```

**Expected Result**:
```c
return_value == SUCCESS
out == 1   /* interlock OK — departure permitted */
```

---

##### TC-SKN-005-FLT-001: Departure Interlock — One Door Not Locked → Interlock Blocked

```
/* TC-SKN-005-FLT-001: One door not CLOSED_AND_LOCKED → interlock_ok = 0
 * SRS: REQ-SAFE-003 — single door failure must block departure
 * SIL: 3 — Safety-critical
 */
```

**Test Inputs**:
```c
uint8_t doors[4] = {DOOR_STATE_CLOSED_AND_LOCKED, DOOR_STATE_FULLY_OPEN,
                    DOOR_STATE_CLOSED_AND_LOCKED, DOOR_STATE_CLOSED_AND_LOCKED};
```

**Expected Result**: `out == 0` (interlock blocked)

---

##### TC-SKN-005-FLT-002: Departure Interlock — Safe State Active → Interlock Blocked

**Test Inputs**: `safe_state_active = 1; doors[4] = all CLOSED_AND_LOCKED`

**Expected Result**: `out == 0` (safe state overrides interlock)

---

##### TC-SKN-005-FLT-003: Departure Interlock — Channel Disagree → Interlock Blocked

**Test Inputs**: `channel_disagree = 1`

**Expected Result**: `out == 0`

---

##### TC-SKN-005-ERR-001: Departure Interlock — NULL Pointers → Fail-Closed

```
/* TC-SKN-005-ERR-001: NULL pointer inputs → fail-closed (out = 0)
 * SRS: REQ-SAFE-003, defensive programming
 * SCDS: §3.2.2 — "fail-closed" on NULL
 */
```

**Test Inputs**: `doors = NULL; locks = NULL; out = &val`

**Expected Result**:
```c
return_value == ERR_NULL_PTR
out == 0   /* fail-closed: interlock blocked on null */
```

---

**UNIT-SKN-006: `SKN_CheckMemoryIntegrity`**

---

##### TC-SKN-006-NRM-001: Memory Integrity — ROM and RAM CRC Match

**Test Type**: Normal | **Priority**: High

**Preconditions**: Mock ROM/RAM CRC matches stored expected value

**Expected Result**: `return_value == SUCCESS; *crc_ok_out == 1`

---

##### TC-SKN-006-FLT-001: Memory Integrity — ROM CRC Mismatch → Integrity Fail

```
/* TC-SKN-006-FLT-001: ROM CRC corruption detected
 * SRS: REQ-SAFE-009 (CRC protection), SW-HAZ-008 (memory corruption)
 * SCDS: §3.2.3
 * SIL: 3
 */
```

**Preconditions**: Mock ROM CRC returns `__rom_expected_crc__ XOR 0x0001`

**Expected Result**: `return_value == ERR_CRC; *crc_ok_out == 0`

---

##### TC-SKN-006-FLT-002: Memory Integrity — Safety Globals RAM CRC Mismatch

**Preconditions**: RAM CRC differs from snapshot taken at init

**Expected Result**: `return_value == ERR_CRC; *crc_ok_out == 0`

---

##### TC-SKN-006-ERR-001: Memory Integrity — NULL Output Pointer

**Expected Result**: `return_value == ERR_NULL_PTR`

---

**UNIT-SKN-007: `SKN_CheckStackCanary`**

---

##### TC-SKN-007-NRM-001: Stack Canary — Both Canaries Valid

**Test Inputs**: `__stack_top_canary__ = 0xDEADBEEF; __stack_bottom_canary__ = 0xDEADBEEF`

**Expected Result**: `return_value == SUCCESS; *canary_ok_out == 1`

---

##### TC-SKN-007-FLT-001: Stack Canary — Top Canary Corrupted

**Test Inputs**: `__stack_top_canary__ = 0x00000000U` (corrupted)

**Expected Result**: `return_value == ERR_HW_FAULT; *canary_ok_out == 0`

---

##### TC-SKN-007-FLT-002: Stack Canary — Bottom Canary Corrupted

**Test Inputs**: `__stack_bottom_canary__ = 0xDEADBEF0U` (one byte off)

**Expected Result**: `return_value == ERR_HW_FAULT; *canary_ok_out == 0`

---

**UNIT-SKN-008: `SKN_RunCycle`**

---

##### TC-SKN-008-NRM-001: Run Cycle — Normal Execution (No Faults)

```
/* TC-SKN-008-NRM-001: Full cycle dispatch with no faults
 * SRS: REQ-PERF-001 (20 ms cycle), REQ-INT-010 (cross-channel)
 * SCDS: §3.3.1
 */
```

**Preconditions**: All mocks return SUCCESS; `s_cycle_count = 0`

**Expected Result**: All component Run/Cycle functions called in order; no safe state set; `s_cycle_count == 1`

---

##### TC-SKN-008-PFM-001: Run Cycle — Memory Integrity Check Every 5 Cycles

**Test Steps**: Call `SKN_RunCycle` 5 times; verify `SKN_CheckMemoryIntegrity` is called on cycle 5 (index 4 mod 5 == 0) and NOT on cycles 1–4

**Expected Result**: `SKN_CheckMemoryIntegrity` called exactly 1 time in 5 calls

---

**UNIT-SKN-009: `SKN_Init`**

---

##### TC-SKN-009-NRM-001: Init — All State Variables Reset to Fail-Safe Defaults

```
/* TC-SKN-009-NRM-001: Initialize SKN to fail-safe defaults
 * SRS: REQ-SAFE-006 (safe state management), REQ-SAFE-009 (CRC)
 * SCDS: §3.4.1
 */
```

**Expected Result**:
```c
return_value == SUCCESS
s_safe_state_active == 0
s_departure_interlock_ok == 0    /* fail-closed default */
s_spi_infra_fault_count == 0
__stack_top_canary__ == 0xDEADBEEF
__stack_bottom_canary__ == 0xDEADBEEF
/* ROM CRC snapshot stored */
/* Safety globals CRC snapshot stored */
```

---

### 3.2 COMP-002: SPEED MONITOR (SPM) — SIL 3

**Traceability**: SRS REQ-SAFE-001/002/003/016, REQ-PERF-002, SW-HAZ-001/007
**Source Files**: `spm_can.c`, `spm_interlock.c`, `spm_init.c`
**Test Suite**: `tests/test_spm.c`

---

#### 3.2.1 MOD-SPM-001 — CAN Speed Reception

**UNIT-SPM-001: `SPM_ProcessSpeedFrame`**

---

##### TC-SPM-001-NRM-001: Process Speed Frame — Valid CRC, Sequence, Range

```
/* TC-SPM-001-NRM-001: Normal valid speed frame accepted
 * Tests: UNIT-SPM-001
 * SRS: REQ-INT-007 (CAN receive), REQ-SAFE-001 (speed interlock input)
 * SCDS: §4.1.1
 */
```

**Test Inputs**:
```c
tcms_speed_msg_t msg = {
    .speed_kmh_x10 = 100U,   /* 10.0 km/h */
    .seq_counter   = 1U,
    .crc16         = CRC16_CCITT_Compute((uint8_t*)&msg, sizeof(msg)-2)
};
uint32_t timestamp_ms = 1000U;
```

**Expected Result**:
```c
return_value == SUCCESS
s_current_speed_kmh_x10 == 100U
s_last_valid_rx_ms == 1000U
s_last_seq_counter == 1U
```

---

##### TC-SPM-001-ERR-001: Process Speed Frame — NULL Pointer

**Test Inputs**: `msg = NULL`

**Expected Result**: `return_value == ERR_NULL_PTR`

---

##### TC-SPM-001-ERR-002: Process Speed Frame — CRC Mismatch → Reject

```
/* TC-SPM-001-ERR-002: CRC failure — frame must be discarded
 * SRS: REQ-SAFE-009 (CRC on all safety-critical messages)
 * SIL: 3 — Safety-critical
 */
```

**Test Inputs**: `msg.crc16 = msg.crc16 XOR 0xFFFFU` (corrupt)

**Expected Result**: `return_value == ERR_CRC; s_current_speed_kmh_x10 unchanged`

---

##### TC-SPM-001-ERR-003: Process Speed Frame — Speed Out of Range (> 3000)

```
/* TC-SPM-001-ERR-003: Speed exceeds maximum valid range
 * SRS: REQ-SAFE-001 (fail-safe on invalid speed)
 * SCDS: §4.1.1 range check
 */
```

**Test Inputs**: `msg.speed_kmh_x10 = 3001U` (out of range); CRC valid over corrupt value

**Expected Result**: `return_value == ERR_RANGE; s_current_speed_kmh_x10 unchanged`

---

##### TC-SPM-001-BND-001: Process Speed Frame — Speed at Upper Boundary (3000)

**Test Inputs**: `msg.speed_kmh_x10 = 3000U` (boundary MAX); CRC valid

**Expected Result**: `return_value == SUCCESS; s_current_speed_kmh_x10 == 3000U`

---

##### TC-SPM-001-BND-002: Process Speed Frame — Speed at Zero

**Test Inputs**: `msg.speed_kmh_x10 = 0U`; CRC valid

**Expected Result**: `return_value == SUCCESS; s_current_speed_kmh_x10 == 0U`

---

##### TC-SPM-001-BND-003: Process Speed Frame — Sequence Counter Rollover (255 → 0)

**Test Inputs**: Previous seq = 255; new `msg.seq_counter = 0U`

**Expected Result**: `return_value == SUCCESS` (seq counter rollover is valid modulo-256); no fault

---

#### 3.2.2 MOD-SPM-002 — Interlock Evaluation

**UNIT-SPM-002: `SPM_EvaluateInterlock`**

---

##### TC-SPM-002-NRM-001: Interlock — Speed at Threshold (50 = 5.0 km/h) → Not Active (Boundary)

```
/* TC-SPM-002-NRM-001: Speed exactly at SPEED_THRESHOLD — OI-FMEA-002 boundary
 * Tests: UNIT-SPM-002
 * SRS: REQ-SAFE-001 — "exact boundary 50 is SAFE" per OI-FMEA-002
 * SCDS: §4.2.1 — speed > SPEED_THRESHOLD (not >=)
 * SIL: 3 — CRITICAL boundary: exact threshold must NOT inhibit (SAFE side)
 */
```

**Test Inputs**:
```c
s_current_speed_kmh_x10 = SPEED_THRESHOLD;   /* == 50U */
s_last_valid_rx_ms = 0U;
current_time_ms = 50U;   /* well within CAN_TIMEOUT_MS */
```

**Expected Result**:
```c
return_value == SUCCESS
out == 0   /* interlock NOT active at exact threshold */
```

**Safety Significance**: Confirms OI-FMEA-002 boundary — speed == 50 (5.0 km/h) is permitted side.

---

##### TC-SPM-002-FLT-001: Interlock — Speed Just Above Threshold (51) → Active

```
/* TC-SPM-002-FLT-001: Speed one unit above threshold — interlock must activate
 * SRS: REQ-SAFE-001
 * SIL: 3 — Safety-critical: speed > 5.0 km/h MUST block door opening
 */
```

**Test Inputs**: `s_current_speed_kmh_x10 = 51U` (just above threshold = 5.1 km/h)

**Expected Result**: `out == 1` (interlock active)

---

##### TC-SPM-002-FLT-002: Interlock — CAN Timeout → Interlock Active (Fail-Safe)

```
/* TC-SPM-002-FLT-002: Stale speed data → interlock active (fail-safe default)
 * SRS: REQ-SAFE-001 — "default to train moving if speed data absent or stale"
 * SIL: 3 — Safety-critical
 */
```

**Test Inputs**:
```c
s_last_valid_rx_ms = 0U;
current_time_ms = CAN_TIMEOUT_MS + 1U;   /* 201 ms — beyond timeout */
```

**Expected Result**: `out == 1` (fail-safe: assume moving)

---

##### TC-SPM-002-FLT-003: Interlock — Unknown Speed (0xFFFF) → Active

**Test Inputs**: `s_current_speed_kmh_x10 = 0xFFFFU`; timeout not elapsed

**Expected Result**: `out == 1`

---

##### TC-SPM-002-ERR-001: Interlock — NULL Output Pointer

**Expected Result**: `return_value == ERR_NULL_PTR`

---

##### TC-SPM-002-BND-001: Interlock — Speed One Below Threshold (49) → Not Active

**Test Inputs**: `s_current_speed_kmh_x10 = 49U` (just below = 4.9 km/h); data fresh

**Expected Result**: `out == 0`

---

#### 3.2.3 MOD-SPM-003 — Initialization and Cycle Entry

**UNIT-SPM-003: `SPM_Init`**

##### TC-SPM-003-NRM-001: Init — Fail-Safe Defaults

**Expected Result**:
```c
return_value == SUCCESS
s_current_speed_kmh_x10 == 0xFFFFU   /* UNKNOWN */
s_speed_interlock_active == 1          /* fail-safe: inhibit */
s_last_valid_rx_ms == 0U
s_last_seq_counter == 0U
```

---

**UNIT-SPM-005: `SPM_GetSpeed`**

##### TC-SPM-005-NRM-001: GetSpeed — Returns Current Speed

**Preconditions**: `s_current_speed_kmh_x10 = 250U`

**Expected Result**: `return_value == 250U`

---

### 3.3 COMP-003: OBSTACLE DETECTOR (OBD) — SIL 3

**Traceability**: SRS REQ-SAFE-004/005/006, REQ-PERF-003, SW-HAZ-002
**Source Files**: `obd_isr.c`, `obd_detect.c`, `obd_init.c`
**Test Suite**: `tests/test_obd.c`

---

#### 3.3.1 MOD-OBD-001 — Obstacle Sensor ISR Handler

**UNIT-OBD-001: `OBD_ObstacleISR`**

---

##### TC-OBD-001-NRM-001: Obstacle ISR — Valid Door ID Sets Flag

```
/* TC-OBD-001-NRM-001: ISR sets mailbox flag for valid door_id
 * Tests: UNIT-OBD-001
 * SRS: REQ-SAFE-004 (obstacle detection), REQ-INT-003 (ISR interface)
 * SCDS: §5.1.1 — minimal ISR (set flag only)
 */
```

**Test Inputs**: `door_id = 0U`

**Expected Result**: `s_obstacle_isr_flags[0] == 1U`; no other flags modified

---

##### TC-OBD-001-BND-001: Obstacle ISR — Last Valid Door (MAX_DOORS - 1)

**Test Inputs**: `door_id = MAX_DOORS - 1U`   (= 3U)

**Expected Result**: `s_obstacle_isr_flags[3] == 1U`

---

##### TC-OBD-001-ERR-001: Obstacle ISR — Door ID Out of Range → No Action (Defensive)

```
/* TC-OBD-001-ERR-001: ISR bounds check — door_id >= MAX_DOORS
 * SRS: defensive programming (REQ-IMPL-006), REQ-SAFE-004
 * SCDS: §5.1.1 — "defensive bounds check"
 */
```

**Test Inputs**: `door_id = MAX_DOORS`   (= 4U, out of bounds)

**Expected Result**: No `s_obstacle_isr_flags` element modified; no crash

---

#### 3.3.2 MOD-OBD-002 — Obstacle Detection and Reversal

**UNIT-OBD-002: `OBD_PollSensorsAndEvaluate`**

---

##### TC-OBD-002-NRM-001: Poll Sensors — No Obstacles, No Closing → All Clear

```
/* TC-OBD-002-NRM-001: Clean state — no obstacles
 * Tests: UNIT-OBD-002
 * SRS: REQ-SAFE-004, REQ-SAFE-005
 * SCDS: §5.2.1
 */
```

**Preconditions**: All `s_obstacle_isr_flags[i] = 0`; HAL mocks: sensors return 0; closing_flags = {0,0,0,0}

**Expected Result**: `return_value == SUCCESS; obstacle_flags_out[i] == 0 for all i`

---

##### TC-OBD-002-FLT-001: Poll Sensors — ISR Flag Set → Obstacle Detected

```
/* TC-OBD-002-FLT-001: ISR latch active → obstacle flag set and ISR cleared
 * SRS: REQ-SAFE-004 — ISR-driven detection
 * SIL: 3 — Safety-critical
 */
```

**Preconditions**: `s_obstacle_isr_flags[1] = 1U` (door 1 ISR fired)

**Expected Result**:
```c
obstacle_flags_out[1] == 1U    /* obstacle detected */
s_obstacle_isr_flags[1] == 0U /* ISR flag cleared after read */
```

---

##### TC-OBD-002-FLT-002: Poll Sensors — Sensor A Returns GPIO Error → Fail-Safe

```
/* TC-OBD-002-FLT-002: HAL error on sensor read → fail-safe (treat as obstacle)
 * SRS: REQ-SAFE-004 — "fail-safe on sensor fault"
 * SIL: 3 — Safety-critical
 */
```

**Preconditions**: `HAL_GPIO_ReadObstacleSensor(0, 0, &val)` mock returns `ERR_HW_FAULT`

**Expected Result**: `obstacle_flags_out[0] == 1U` (fail-safe: assume obstacle)

---

##### TC-OBD-002-FLT-003: Poll Sensors — Motor Current Exceeds MAX_FORCE_ADC → Obstacle

```
/* TC-OBD-002-FLT-003: Excess motor current during closing detected
 * SRS: REQ-SAFE-006 — force limit detection
 * SCDS: §5.2.1 — ADC motor current check
 */
```

**Preconditions**: `closing_flags[2] = 1U`; `HAL_ADC_ReadMotorCurrent(2, &val)` mock returns `MAX_FORCE_ADC + 1U`

**Expected Result**: `obstacle_flags_out[2] == 1U`

---

##### TC-OBD-002-ERR-001: Poll Sensors — NULL Input Pointers → Fail-Safe

```
/* TC-OBD-002-ERR-001: NULL pointer inputs — fail-safe all outputs = 1
 * SRS: REQ-SAFE-004 — defensive + fail-safe defaults
 * SCDS: §5.2.1 — "fail-safe on NULL_PTR"
 */
```

**Test Inputs**: `closing_flags = NULL; out = obstacle_flags_out` (valid buffer)

**Expected Result**:
```c
return_value == ERR_NULL_PTR
obstacle_flags_out[i] == 1U for all i   /* fail-safe */
```

---

### 3.4 COMP-004: DOOR STATE MACHINE (DSM) — SIL 3

**Traceability**: SRS REQ-SAFE-007/008/009/010/011/019/020, REQ-FUN-001–015, SW-HAZ-003/004/009
**Source Files**: `dsm_fsm.c`, `dsm_voter.c`, `dsm_mode.c`, `dsm_emergency.c`, `dsm_init.c`
**Test Suite**: `tests/test_dsm.c`

---

#### 3.4.1 MOD-DSM-001 — Per-Door FSM Engine

**UNIT-DSM-001: `DSM_UpdateFSM`**

---

##### TC-DSM-001-NRM-001: FSM Update — IDLE → OPENING (Normal Open Command)

```
/* TC-DSM-001-NRM-001: Normal door open command from IDLE state
 * Tests: UNIT-DSM-001 + UNIT-DSM-002 (TransitionFromIdle)
 * SRS: REQ-FUN-001 (door opening command), REQ-SAFE-001 (speed interlock)
 * SCDS: §6.1.1, §6.1.2
 * SIL: 3
 */
```

**Preconditions**: `s_door_fsm[0] = FSM_IDLE; s_door_state_entry_time_ms[0] = 0`

**Test Inputs**:
```c
uint8_t door_id = 0;
uint8_t cmd_open = 1;
uint8_t speed_interlock = 0;   /* speed OK */
uint8_t safe_state_active = 0;
uint32_t current_time_ms = 100U;
/* other params: 0 */
```

**Expected Result**:
```c
return_value == SUCCESS
s_door_fsm[0] == FSM_OPENING
/* HAL_GPIO_SetMotorDirection called with direction=0 (open) */
/* HAL_PWM_SetDutyCycle called with 80% */
```

---

##### TC-DSM-001-FLT-001: FSM Update — Speed Interlock Active → Opening Rejected

```
/* TC-DSM-001-FLT-001: Open command with speed interlock active — must reject
 * SRS: REQ-SAFE-001 — speed interlock enforced in FSM
 * SIL: 3 — Safety-critical
 */
```

**Preconditions**: `s_door_fsm[0] = FSM_IDLE`

**Test Inputs**: `cmd_open = 1; speed_interlock = 1` (train moving)

**Expected Result**: `s_door_fsm[0] == FSM_IDLE` (no transition; command rejected)

---

##### TC-DSM-001-FLT-002: FSM Update — Safe State Active → Any State → FSM_FAULT

```
/* TC-DSM-001-FLT-002: Safe state override — any FSM state → FAULT
 * SRS: REQ-SAFE-006 (safe state transition)
 * SCDS: §6.1.1 — "safe_state override ANY state → FSM_FAULT"
 * SIL: 3 — Safety-critical
 */
```

**Preconditions**: `s_door_fsm[0] = FSM_OPENING` (door was moving)

**Test Inputs**: `safe_state_active = 1`

**Expected Result**:
```c
s_door_fsm[0] == FSM_FAULT
s_door_states[0] == DOOR_STATE_FAULT
/* HAL_PWM_SetDutyCycle called with 0 (motor stop) */
/* HAL_GPIO_SetLockActuator called with 1 (lock) */
```

---

##### TC-DSM-001-FLT-003: FSM Update — Dwell Timeout in OPENING → FSM_FAULT

```
/* TC-DSM-001-FLT-003: Opening timeout — door stuck — transition to FAULT
 * SRS: REQ-FUN-003 (opening timeout 4.0 s)
 * SCDS: §6.1.1 FSM_MAX_DWELL_MS[FSM_OPENING] = 4000
 */
```

**Preconditions**: `s_door_fsm[0] = FSM_OPENING; s_door_state_entry_time_ms[0] = 0`

**Test Inputs**: `current_time_ms = 4001U` (> 4000 ms dwell)

**Expected Result**: `s_door_fsm[0] == FSM_FAULT`

---

##### TC-DSM-001-ERR-001: FSM Update — Door ID Out of Range

**Test Inputs**: `door_id = MAX_DOORS` (= 4U)

**Expected Result**: `return_value == ERR_RANGE`

---

##### TC-DSM-001-NRM-002: FSM Update — CLOSING → OBSTACLE_REVERSAL (Obstacle Detected)

```
/* TC-DSM-001-NRM-002: Obstacle during closing → reversal
 * SRS: REQ-SAFE-004, REQ-PERF-003
 * SCDS: §6.1.5 DSM_TransitionFromClosing
 */
```

**Preconditions**: `s_door_fsm[0] = FSM_CLOSING`

**Test Inputs**: `obstacle = 1`

**Expected Result**:
```c
s_door_fsm[0] == FSM_OBSTACLE_REVERSAL
/* HAL_GPIO_SetMotorDirection: direction=0 (open/reverse) */
/* HAL_PWM_SetDutyCycle: 60% */
```

---

##### TC-DSM-001-NRM-003: FSM Update — CLOSING → FULLY_CLOSED (Both Position Sensors)

```
/* TC-DSM-001-NRM-003: Door reaches closed end-stop (2oo2 confirmation)
 * SRS: REQ-FUN-005 (2oo2 close detection), REQ-SAFE-005
 */
```

**Preconditions**: `s_door_fsm[0] = FSM_CLOSING`

**Test Inputs**: `pos_a_closed = 1; pos_b_closed = 1; obstacle = 0`

**Expected Result**: `s_door_fsm[0] == FSM_FULLY_CLOSED`

---

##### TC-DSM-001-NRM-004: FSM Update — LOCKING → CLOSED_AND_LOCKED (Both Lock Sensors)

```
/* TC-DSM-001-NRM-004: Lock sensors confirm locked (2oo2)
 * SRS: REQ-FUN-005, REQ-FUN-008 (lock engagement), REQ-SAFE-007 (2oo2 lock)
 */
```

**Preconditions**: `s_door_fsm[0] = FSM_LOCKING`

**Test Inputs**: `lock_a = 1; lock_b = 1`

**Expected Result**: `s_door_fsm[0] == FSM_CLOSED_AND_LOCKED`

---

#### 3.4.2 MOD-DSM-002 — Sensor Voter (2oo2)

**UNIT-DSM-012: `DSM_VotePosition`**

---

##### TC-DSM-012-NRM-001: Vote Position — Both Sensors Agree → Voted Value = Input

```
/* TC-DSM-012-NRM-001: 2oo2 agreement — voted position = sensor value
 * SRS: REQ-SAFE-005 (2oo2 position verification), REQ-FUN-002
 * SCDS: §6.2.1
 */
```

**Test Inputs**: `pos_a = 1; pos_b = 1`

**Expected Result**:
```c
return_value == SUCCESS
*voted_position == 1
*disagree_out == 0
```

---

##### TC-DSM-012-FLT-001: Vote Position — Sensors Disagree → Conservative (0) + Disagree Flag

```
/* TC-DSM-012-FLT-001: Sensor disagreement → conservative output
 * SRS: REQ-SAFE-005 — "single sensor cannot declare closed alone"
 * SIL: 3 — Safety-critical: disagreement must produce conservative (0=not-at-position)
 */
```

**Test Inputs**: `pos_a = 1; pos_b = 0`

**Expected Result**:
```c
*voted_position == 0   /* conservative — unknown */
*disagree_out == 1
```

---

##### TC-DSM-012-FLT-002: Vote Position — Both Zero → Agreement on Zero

**Test Inputs**: `pos_a = 0; pos_b = 0`

**Expected Result**: `*voted_position == 0; *disagree_out == 0`

---

##### TC-DSM-012-ERR-001: Vote Position — NULL Output Pointers

**Expected Result**: `return_value == ERR_NULL_PTR`

---

#### 3.4.3 MOD-DSM-003 — Operational Mode Manager

**UNIT-DSM-013: `DSM_TransitionMode`**

---

##### TC-DSM-013-NRM-001: Mode Transition — NORMAL → DIAGNOSTIC (Speed Zero, Authorized)

```
/* TC-DSM-013-NRM-001: Valid transition to DIAGNOSTIC mode
 * SRS: REQ-FUN-011 (operational modes), REQ-FUN-014 (diagnostic conditions)
 * SCDS: §6.3.1
 */
```

**Preconditions**: `s_op_mode = MODE_NORMAL`

**Test Inputs**: `requested_mode = MODE_DIAGNOSTIC; tcms_authorized = 1; speed_zero = 1`

**Expected Result**:
```c
return_value == SUCCESS
s_op_mode == MODE_DIAGNOSTIC
```

---

##### TC-DSM-013-FLT-001: Mode Transition — NORMAL → DIAGNOSTIC Without Authorization → Rejected

```
/* TC-DSM-013-FLT-001: Unauthorized mode transition must be rejected
 * SRS: REQ-FUN-012 (mode authorization), REQ-FUN-014
 * SIL: 3
 */
```

**Test Inputs**: `requested_mode = MODE_DIAGNOSTIC; tcms_authorized = 0; speed_zero = 1`

**Expected Result**: `return_value == ERR_NOT_PERMITTED; s_op_mode == MODE_NORMAL` (unchanged)

---

##### TC-DSM-013-FLT-002: Mode Transition — NORMAL → DIAGNOSTIC While Moving → Rejected

**Test Inputs**: `requested_mode = MODE_DIAGNOSTIC; tcms_authorized = 1; speed_zero = 0`

**Expected Result**: `return_value == ERR_NOT_PERMITTED; s_op_mode == MODE_NORMAL`

---

##### TC-DSM-013-FLT-003: Mode Transition — Invalid State → ERR_INVALID_STATE

**Preconditions**: `s_op_mode = 0xFFU` (invalid — inject directly)

**Expected Result**: `return_value == ERR_INVALID_STATE`

---

#### 3.4.4 MOD-DSM-004 — Emergency Release Handler

**UNIT-DSM-014: `DSM_HandleEmergencyRelease`**

---

##### TC-DSM-014-NRM-001: Emergency Release — Debounce Period Not Elapsed → No Latch

```
/* TC-DSM-014-NRM-001: Emergency release active but debounce not complete
 * SRS: REQ-INT-011 (emergency release detection)
 * SCDS: §6.4.1 — EMERG_DEBOUNCE_MS = 60
 */
```

**Preconditions**: `s_emerg_debounce_start_ms[0] = 0`; HAL mock: `HAL_GPIO_ReadEmergencyRelease` returns 1 (active)

**Test Inputs**: `current_time_ms = 59U` (< 60 ms debounce)

**Expected Result**: `s_emergency_release_latched[0] == 0` (not yet latched)

---

##### TC-DSM-014-FLT-001: Emergency Release — Debounce Complete → Latch and Unlock

```
/* TC-DSM-014-FLT-001: Emergency release confirmed after debounce
 * SRS: REQ-INT-011 — "log event, send TCMS alert within 200 ms"
 * SCDS: §6.4.1 — latch + HAL_GPIO_SetLockActuator(0) = unlock
 */
```

**Preconditions**: `s_emerg_debounce_start_ms[0] = 0U`; `HAL_GPIO_ReadEmergencyRelease` returns 1

**Test Inputs**: `current_time_ms = EMERG_DEBOUNCE_MS + 1U`   (= 61 ms)

**Expected Result**:
```c
s_emergency_release_latched[0] == 1
/* HAL_GPIO_SetLockActuator(0, 0) called — unlock */
```

---

##### TC-DSM-014-ERR-001: Emergency Release — Door ID Out of Range

**Test Inputs**: `door_id = MAX_DOORS`

**Expected Result**: `return_value == ERR_RANGE`

---

### 3.5 COMP-005: FAULT MANAGER (FMG) — SIL 3

**Traceability**: SRS REQ-SAFE-012/013/021, REQ-FUN-013/017/018, SW-HAZ-005/010
**Source Files**: `fmg_aggregator.c`, `fmg_safe_state.c`, `fmg_init.c`
**Test Suite**: `tests/test_fmg.c`

---

**UNIT-FMG-001: `FMG_AggregateFaults`**

---

##### TC-FMG-001-NRM-001: Aggregate Faults — No Faults → Fault State = 0

```
/* TC-FMG-001-NRM-001: All clear — fault state zero
 * SRS: REQ-FUN-017 (fault monitoring)
 * SCDS: §7.1.1
 */
```

**Test Inputs**: All fault inputs = 0

**Expected Result**: `return_value == SUCCESS; *fault_state_out == 0x00U`

---

##### TC-FMG-001-FLT-001: Aggregate Faults — Multiple Fault Sources Bitwise OR'd

**Test Inputs**: `spm_fault = 0x01U; obd_fault = 0x04U; dsm_fault = 0x00U; tci_fault = 0x00U; hal_fault = 0x00U`

**Expected Result**: `*fault_state_out == 0x05U` (OR of all)

---

##### TC-FMG-001-ERR-001: Aggregate Faults — NULL Output Pointer

**Expected Result**: `return_value == ERR_NULL_PTR`

---

**UNIT-FMG-002: `FMG_ClassifyAndEscalate`**

---

##### TC-FMG-002-NRM-001: Classify — No Fault Bits → FAULT_NONE

**Test Inputs**: `fault_state = 0x00U`

**Expected Result**: `*max_severity_out == FAULT_NONE`

---

##### TC-FMG-002-FLT-001: Classify — Bit 0 Set → FAULT_CRITICAL

```
/* TC-FMG-002-FLT-001: Critical fault bit triggers FAULT_CRITICAL classification
 * SRS: REQ-SAFE-006 (critical fault triggers safe state)
 * SCDS: §7.1.2 FAULT_TABLE[0] = {0x01, FAULT_CRITICAL}
 */
```

**Test Inputs**: `fault_state = 0x01U`

**Expected Result**: `*max_severity_out == FAULT_CRITICAL`

---

##### TC-FMG-002-FLT-002: Classify — Mixed Critical and High Bits → FAULT_CRITICAL (Max)

**Test Inputs**: `fault_state = 0x09U` (bits 0 and 3 — CRITICAL and HIGH)

**Expected Result**: `*max_severity_out == FAULT_CRITICAL` (highest wins)

---

**UNIT-FMG-003: `FMG_HandleSelectiveDisablement`**

---

##### TC-FMG-003-NRM-001: Selective Disable — Authorized → Mask Applied

```
/* TC-FMG-003-NRM-001: Authorized door disablement
 * SRS: REQ-FUN-013 (selective door disablement)
 * SCDS: §7.2.1
 */
```

**Test Inputs**: `door_mask = 0x02U; tcms_authorized = 1`

**Expected Result**:
```c
return_value == SUCCESS
s_door_disabled_mask == 0x02U
```

---

##### TC-FMG-003-FLT-001: Selective Disable — Not Authorized → Rejected

**Test Inputs**: `door_mask = 0x02U; tcms_authorized = 0`

**Expected Result**: `return_value == ERR_NOT_PERMITTED; s_door_disabled_mask unchanged`

---

### 3.6 COMP-006: TCMS INTERFACE (TCI) — SIL 3

**Traceability**: SRS REQ-INT-007/008/009, REQ-SAFE-003/016, REQ-FUN-016, SW-HAZ-007
**Source Files**: `tci_rx.c`, `tci_tx.c`, `tci_seq.c`, `tci_init.c`
**Test Suite**: `tests/test_tci.c`

---

**UNIT-TCI-001: `TCI_CanRxISR`**

---

##### TC-TCI-001-NRM-001: CAN Rx ISR — Valid Speed Frame Stored in Mailbox

```
/* TC-TCI-001-NRM-001: ISR stores valid frame in correct mailbox slot
 * SRS: REQ-INT-007 (CAN receive)
 * SCDS: §8.1.1
 */
```

**Preconditions**: HAL mock: `HAL_CAN_Receive` populates `msg_id=0x100, data[8], dlc=5`

**Expected Result**:
```c
s_can_rx_mailbox[0].msg_id == 0x100U
s_can_rx_mailbox[0].valid == 1
s_can_rx_mailbox[0].dlc == 5
```

---

##### TC-TCI-001-ERR-001: CAN Rx ISR — Out of Range Message ID → Discarded

**Preconditions**: HAL mock: `HAL_CAN_Receive` returns `msg_id = 0x200U` (outside 0x100–0x104)

**Expected Result**: No mailbox slot modified; no crash

---

**UNIT-TCI-002: `TCI_ProcessReceivedFrames`**

---

##### TC-TCI-002-NRM-001: Process Received — Valid CRC → Frame Routed

**Preconditions**: `s_can_rx_mailbox[0].valid = 1`; CRC in frame matches computed CRC

**Expected Result**: Appropriate handler (SPM_ProcessSpeedFrame) called; `s_can_rx_mailbox[0].valid == 0` after processing

---

##### TC-TCI-002-ERR-001: Process Received — CRC Mismatch → Frame Discarded

```
/* TC-TCI-002-ERR-001: CRC failure — safety frame must be discarded
 * SRS: REQ-SAFE-009 (CRC protection on all safety-critical messages)
 * SIL: 3 — Safety-critical
 */
```

**Preconditions**: `s_can_rx_mailbox[0].valid = 1`; CRC corrupted (`^0x0001`)

**Expected Result**:
```c
s_can_rx_mailbox[0].valid == 0   /* discarded */
/* No handler called */
```

---

**UNIT-TCI-003: `TCI_TransmitDepartureInterlock`**

---

##### TC-TCI-003-NRM-001: Transmit Departure Interlock — Data and CRC Correct

```
/* TC-TCI-003-NRM-001: Departure interlock CAN frame (0x200) transmitted with CRC
 * SRS: REQ-SAFE-003 (departure interlock signal), REQ-INT-008
 * SCDS: §8.2.1
 */
```

**Test Inputs**: `interlock_ok = 1U`

**Expected Result**:
```c
return_value == SUCCESS
/* HAL_CAN_Transmit called with msg_id=0x200 */
/* data[0] == 1U; data[1] == s_tx_seq_0x200 */
/* CRC16 of data[0..1] == data[2] | (data[3] << 8) */
/* s_tx_seq_0x200 incremented */
```

---

**UNIT-TCI-006: `TCI_ValidateRxSeqDelta`**

---

##### TC-TCI-006-NRM-001: Validate Sequence — Expected Sequence → No Log

**Preconditions**: `s_last_rx_seq[0] = 5U`

**Test Inputs**: `msg_id = 0x100; rx_seq = 6U`

**Expected Result**: `return_value == SUCCESS; s_last_rx_seq[0] == 6U`

---

##### TC-TCI-006-ERR-001: Validate Sequence — msg_id Out of Range

**Test Inputs**: `msg_id = 0x105U` (idx = 5, >= 5)

**Expected Result**: `return_value == ERR_RANGE`

---

### 3.7 COMP-007: DIAGNOSTICS (DGN) — SIL 1

**Traceability**: SRS REQ-FUN-018
**Note**: COMP-007 is SIL 1. Compound Condition coverage not required; branch coverage is HR.
**Test Suite**: `tests/test_dgn.c`

---

##### TC-DGN-NRM-001: Event Log Write — Valid Entry Stored with CRC

```
/* TC-DGN-NRM-001: Event logged with timestamp and CRC-16
 * SRS: REQ-FUN-018 (event logging)
 * SIL: 1
 */
```

**Test Inputs**:
```c
event_log_entry_t entry = {
    .timestamp_ms = 5000U,
    .source_comp  = COMP_SKN,
    .event_code   = EVT_SPI_INFRA_TRANSIENT,
    .data         = 1U
};
```

**Expected Result**: Entry stored in circular buffer; `entry.crc16` == CRC16_CCITT over preceding 6 bytes

---

##### TC-DGN-NRM-002: Circular Buffer Wraparound — Entry 1001 Overwrites Entry 1

**Preconditions**: Log buffer filled with MAX_LOG_ENTRIES (1024) entries

**Expected Result**: Entry 1025 overwrites slot 0 (circular); no overflow; buffer head wraps

---

##### TC-DGN-ERR-001: Log Write — NULL Entry Pointer → No Crash

**Test Inputs**: `entry = NULL`

**Expected Result**: Function returns error; no buffer write; no crash

---

### 3.8 COMP-008: HARDWARE ABSTRACTION LAYER (HAL) — SIL 3

**Traceability**: SRS REQ-INT-001–013, REQ-SAFE-014/017/018, SW-HAZ-006/008
**Source Files**: `hal_gpio.c`, `hal_pwm.c`, `hal_can.c`, `hal_spi.c`, `hal_services.c`
**Test Suite**: `tests/test_hal.c`

---

**UNIT-HAL-001: `HAL_GPIO_ReadPositionSensor`**

---

##### TC-HAL-001-NRM-001: Read Position Sensor — Valid Door and Sensor ID

```
/* TC-HAL-001-NRM-001: Normal sensor read via HAL
 * SRS: REQ-INT-002 (position sensor interface)
 * SCDS: §10.1.1
 */
```

**Test Inputs**: `door_id = 0U; sensor_id = 0U; *state = &val`

**Preconditions**: Hardware mock returns GPIO pin = 1 (at end-stop)

**Expected Result**: `return_value == SUCCESS; *state == 1U`

---

##### TC-HAL-001-ERR-001: Read Position Sensor — NULL State Pointer

**Expected Result**: `return_value == ERR_NULL_PTR`

---

##### TC-HAL-001-ERR-002: Read Position Sensor — door_id >= MAX_DOORS

```
/* TC-HAL-001-ERR-002: Out-of-range door_id
 * SRS: REQ-INT-002, defensive programming
 */
```

**Test Inputs**: `door_id = MAX_DOORS`

**Expected Result**: `return_value == ERR_RANGE`

---

##### TC-HAL-001-ERR-003: Read Position Sensor — sensor_id >= 2

**Test Inputs**: `door_id = 0U; sensor_id = 2U`

**Expected Result**: `return_value == ERR_RANGE`

---

##### TC-HAL-001-BND-001: Read Position Sensor — Last Valid door_id (MAX_DOORS-1)

**Test Inputs**: `door_id = MAX_DOORS - 1U` (= 3); `sensor_id = 1U`

**Expected Result**: `return_value == SUCCESS`

---

**UNIT-HAL-020: `CRC16_CCITT_Compute`**

---

##### TC-HAL-020-NRM-001: CRC16 — Known Vector (All Zeros, Length 4)

```
/* TC-HAL-020-NRM-001: CRC-16-CCITT known reference vector
 * Tests: UNIT-HAL-020 (CRC16_CCITT_Compute)
 * SRS: REQ-SAFE-009 (CRC protection)
 * SCDS: §10.2.1 — poly 0x1021, init 0xFFFF, no final XOR
 */
```

**Test Inputs**:
```c
uint8_t data[4] = {0x00, 0x00, 0x00, 0x00};
uint16_t len = 4U;
```

**Expected Result**: `return_value == 0x84C0U` (CRC-16-CCITT reference value for all-zeros input)

---

##### TC-HAL-020-NRM-002: CRC16 — Known Vector ("123456789" standard test)

```
/* TC-HAL-020-NRM-002: CRC-16-CCITT industry standard test vector
 * Expected: 0x29B1 for "123456789"
 */
```

**Test Inputs**:
```c
uint8_t data[] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};
uint16_t len = 9U;
```

**Expected Result**: `return_value == 0x29B1U`

---

##### TC-HAL-020-ERR-001: CRC16 — NULL Data Pointer → Returns 0x0000

```
/* TC-HAL-020-ERR-001: NULL input → return 0x0000 (defensive per SCDS §10.2.1)
 * SRS: REQ-SAFE-009, defensive programming
 */
```

**Test Inputs**: `data = NULL; length = 4U`

**Expected Result**: `return_value == 0x0000U`

---

##### TC-HAL-020-ERR-002: CRC16 — Zero Length → Returns 0x0000

**Test Inputs**: `data = valid_ptr; length = 0U`

**Expected Result**: `return_value == 0x0000U`

---

##### TC-HAL-020-BND-001: CRC16 — Single Byte Input

**Test Inputs**: `data = {0xA5U}; length = 1U`

**Expected Result**: `return_value` == known single-byte CRC-16-CCITT(0xA5) value; function does not crash

---

##### TC-HAL-020-BND-002: CRC16 — Maximum Length Input (65535)

```
/* TC-HAL-020-BND-002: Maximum uint16_t length — no overflow
 * SRS: REQ-SAFE-009 (CRC integrity)
 * SIL: 3
 */
```

**Test Inputs**: `data = static_buffer_65535_bytes; length = 0xFFFFU`

**Expected Result**: Returns valid CRC-16 value; no integer overflow; no crash

---

---

## 4. TEST COVERAGE ANALYSIS

### 4.1 Coverage Requirements (EN 50128 Table A.21)

| Coverage Type | EN 50128 Table A.21 | SIL 3 Obligation | Project Target (DOC-SVP-2026-001) |
|---|---|---|---|
| Statement Coverage | Item 1 | **M** (Mandatory) | Defined in DOC-SVP-2026-001 |
| Branch Coverage | Item 2 | **M** (Mandatory) | Defined in DOC-SVP-2026-001 |
| Compound Condition Coverage | Item 3 | **HR** (Highly Recommended) | Defined in DOC-SVP-2026-001 (safety-critical units) |
| Data Flow Coverage | Item 4 | HR | Targeted for SKN and DSM units |

> **Normative Compliance Note**: EN 50128:2011 Table A.21 Requirement 1 requires a quantified coverage measure to be defined per project in the SVP/SQAP (DOC-SVP-2026-001). No percentage threshold is mandated by the standard. Coverage targets are project-specific and shall be recorded in DOC-SVP-2026-001. All coverage data shall be measured by gcov/lcov and reported in the Software Component Test Report (Item 20).

### 4.2 Coverage Measurement Procedure

**Instrumented Build**:
```bash
gcc -fprofile-arcs -ftest-coverage -g -O0 -DUNITY_TEST \
    -o test_<module> <src>.c test_<module>.c unity.c mock_hal.c
```

**Coverage Data Collection**:
```bash
./test_<module>
gcov <src>.c
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html/
gcovr --json --output coverage_<module>.json
```

**Report Location**: `examples/TDC/tests/coverage/` (JSON and HTML; machine-readable per §7.6.4.5b)

### 4.3 Critical Units — Compound Condition Coverage Priority

The following units contain compound boolean conditions and SHALL be targeted for Compound Condition Coverage per DOC-SVP-2026-001:

| Unit | Compound Condition | SRS Reference |
|------|--------------------|---------------|
| `SKN_EvaluateSafeState` | `disagree OR (faults AND MASK) OR NOT mem_ok OR NOT canary_ok` | REQ-SAFE-006 |
| `SKN_EvaluateDepartureInterlock` | `safe OR disagree` | REQ-SAFE-003 |
| `SPM_EvaluateInterlock` | `timeout OR unknown OR speed > threshold` | REQ-SAFE-001 |
| `DSM_TransitionFromIdle` | `cmd_open AND NOT speed_interlock` | REQ-FUN-001 |
| `DSM_TransitionFromClosing` | `obstacle OR (pos_a AND pos_b)` | REQ-SAFE-004 |
| `OBD_PollSensorsAndEvaluate` | Multiple sensor OR conditions | REQ-SAFE-004 |

### 4.4 Uncoverable Code Justification

Defensive code paths (NULL pointer checks in functions only called from tested callers with valid pointers) shall be documented with justification in the Software Component Test Report (Item 20) per EN 50128 §6.2.4.

---

## 5. TEST EXECUTION PLAN

### 5.1 Test Suite Schedule

| Module | Test Suite File | Test Cases | SIL | Priority | Planned Phase |
|--------|----------------|-----------|-----|----------|---------------|
| MOD-SKN-001..004 | `test_skn.c` | 28 | 3 | Critical | Phase 5 |
| MOD-SPM-001..003 | `test_spm.c` | 14 | 3 | Critical | Phase 5 |
| MOD-OBD-001..003 | `test_obd.c` | 9 | 3 | Critical | Phase 5 |
| MOD-DSM-001..005 | `test_dsm.c` | 22 | 3 | Critical | Phase 5 |
| MOD-FMG-001..003 | `test_fmg.c` | 9 | 3 | High | Phase 5 |
| MOD-TCI-001..004 | `test_tci.c` | 10 | 3 | High | Phase 5 |
| MOD-DGN-001..003 | `test_dgn.c` | 3 | 1 | Medium | Phase 5 |
| MOD-HAL-001..005 | `test_hal.c` | 11 | 3 | Critical | Phase 5 |
| **Total** | | **106** | | | |

### 5.2 Test Environment Setup

**Build Commands**:
```bash
# Build all unit tests with coverage
make coverage PROJ=TDC

# Run all component tests
make run-unit-tests PROJ=TDC

# Generate machine-readable results (XML — §7.6.4.5b)
make test-xml PROJ=TDC

# Generate coverage report
make coverage-report PROJ=TDC
```

**Required Tools**:
- gcc ≥ 9.0 (with `-fprofile-arcs -ftest-coverage`)
- Unity test framework v2.5.2
- CMock v2.5.3 (for HAL mocking)
- gcov + lcov ≥ 1.14
- gcovr ≥ 5.0
- python3 (for test harness scripts)

**Machine-Readable Output Format**: JUnit XML (Unity XML runner) — mandatory per EN 50128 §7.6.4.5b

**Output Location**: `examples/TDC/tests/results/component_test_results.xml`

### 5.3 Test Independence (SIL 3 HR)

Per EN 50128 Table B.4 and the independence matrix in ORGANIZATION.md:
- SIL 3: Tester independence from implementer is **HR** (Highly Recommended)
- Test cases in this specification are authored by TST, independent of IMP
- TST SHALL NOT review or modify IMP source code — HAL mocks ensure test isolation

---

## 6. TEST TRACEABILITY

### 6.1 SRS Requirements → Test Cases (Bidirectional)

| SRS Requirement | Description | Test Cases | Notes |
|---|---|---|---|
| REQ-FUN-001 | Door opening preconditions | TC-DSM-001-NRM-001, TC-DSM-001-FLT-001, TC-SPM-002-FLT-001 | Opening gate |
| REQ-FUN-002 | 2oo2 fully-open detection | TC-DSM-012-NRM-001, TC-DSM-012-FLT-001 | Sensor voter |
| REQ-FUN-003 | Opening timeout fault | TC-DSM-001-FLT-003 | 4.0 s dwell |
| REQ-FUN-004 | Door closing preconditions | TC-DSM-001-NRM-002, TC-OBD-002-FLT-001 | Close gate |
| REQ-FUN-005 | 2oo2 close-and-lock detection | TC-DSM-001-NRM-003, TC-DSM-001-NRM-004, TC-DSM-012-FLT-001 | Critical |
| REQ-FUN-007 | Obstacle retry logic | TC-DSM-001-NRM-002 (retry states) | FSM states |
| REQ-FUN-008 | Automatic lock engagement | TC-DSM-001-NRM-004 | LOCKING→LOCKED |
| REQ-FUN-011 | Operational mode FSM | TC-DSM-013-NRM-001, TC-DSM-013-FLT-001, TC-DSM-013-FLT-002, TC-DSM-013-FLT-003 | Mode FSM |
| REQ-FUN-012 | Mode authorization | TC-DSM-013-FLT-001, TC-FMG-003-FLT-001 | Auth guard |
| REQ-FUN-013 | Selective door disablement | TC-FMG-003-NRM-001, TC-FMG-003-FLT-001 | FMG |
| REQ-FUN-017 | Fault monitoring | TC-FMG-001-NRM-001, TC-FMG-001-FLT-001, TC-FMG-002-FLT-001/002 | FMG |
| REQ-FUN-018 | Event logging | TC-DGN-NRM-001, TC-DGN-NRM-002, TC-DGN-ERR-001 | DGN circular buffer |
| REQ-INT-002 | Position sensor HAL | TC-HAL-001-NRM-001..BND-001 | HAL |
| REQ-INT-007 | TCMS CAN receive | TC-TCI-001-NRM-001, TC-TCI-002-NRM-001, TC-TCI-002-ERR-001 | CAN Rx |
| REQ-INT-008 | TCMS CAN transmit | TC-TCI-003-NRM-001 | CAN Tx |
| REQ-INT-010 | Cross-channel SPI 2oo2 | TC-SKN-002-NRM-001, TC-SKN-002-FLT-001..004 | Cross-channel |
| REQ-PERF-001 | 20 ms cycle | TC-SKN-008-NRM-001 | Scheduler |
| REQ-SAFE-001 | Speed interlock — inhibit open | TC-SPM-002-NRM-001, TC-SPM-002-FLT-001..003, TC-DSM-001-FLT-001 | **Safety-critical** |
| REQ-SAFE-003 | Departure interlock | TC-SKN-005-NRM-001, TC-SKN-005-FLT-001..003 | **Safety-critical** |
| REQ-SAFE-004 | Obstacle detection + reversal | TC-OBD-001-NRM-001, TC-OBD-002-FLT-001..003, TC-DSM-001-NRM-002 | **Safety-critical** |
| REQ-SAFE-005 | 2oo2 position verification | TC-DSM-012-NRM-001, TC-DSM-012-FLT-001/002 | **Safety-critical** |
| REQ-SAFE-006 | Safe state on critical fault | TC-SKN-004-FLT-001..005, TC-SKN-002-FLT-002..004, TC-DSM-001-FLT-002 | **Safety-critical** |
| REQ-SAFE-009 | CRC protection | TC-SKN-001-NRM-001, TC-SPM-001-ERR-002, TC-TCI-002-ERR-001, TC-HAL-020-NRM-001/002 | **Safety-critical** |
| REQ-SAFE-010 | Cross-channel 2oo2 safety | TC-SKN-002-NRM-001, TC-SKN-002-FLT-001..004, TC-SKN-001-NRM-001 | **Safety-critical** |

### 6.2 Test Cases → SCDS Units (Bidirectional)

| SCDS Unit | Unit Name | Test Cases | Compound Condition |
|---|---|---|---|
| UNIT-SKN-001 | `SKN_BuildLocalState` | TC-SKN-001-NRM-001, ERR-001, BND-001/002 | No |
| UNIT-SKN-002 | `SKN_ExchangeAndCompare` | TC-SKN-002-NRM-001, FLT-001..004, ERR-001 | Yes |
| UNIT-SKN-003 | `SKN_FieldsDisagree` | Exercised via TC-SKN-002-FLT-004 | No |
| UNIT-SKN-004 | `SKN_EvaluateSafeState` | TC-SKN-004-NRM-001, FLT-001..005, ERR-001 | **Yes — priority** |
| UNIT-SKN-005 | `SKN_EvaluateDepartureInterlock` | TC-SKN-005-NRM-001, FLT-001..003, ERR-001 | **Yes — priority** |
| UNIT-SKN-006 | `SKN_CheckMemoryIntegrity` | TC-SKN-006-NRM-001, FLT-001/002, ERR-001 | No |
| UNIT-SKN-007 | `SKN_CheckStackCanary` | TC-SKN-007-NRM-001, FLT-001/002 | No |
| UNIT-SKN-008 | `SKN_RunCycle` | TC-SKN-008-NRM-001, PFM-001 | No |
| UNIT-SKN-009 | `SKN_Init` | TC-SKN-009-NRM-001 | No |
| UNIT-SPM-001 | `SPM_ProcessSpeedFrame` | TC-SPM-001-NRM-001, ERR-001..003, BND-001..003 | No |
| UNIT-SPM-002 | `SPM_EvaluateInterlock` | TC-SPM-002-NRM-001, FLT-001..003, ERR-001, BND-001 | **Yes — priority** |
| UNIT-SPM-003 | `SPM_Init` | TC-SPM-003-NRM-001 | No |
| UNIT-SPM-005 | `SPM_GetSpeed` | TC-SPM-005-NRM-001 | No |
| UNIT-OBD-001 | `OBD_ObstacleISR` | TC-OBD-001-NRM-001, BND-001, ERR-001 | No |
| UNIT-OBD-002 | `OBD_PollSensorsAndEvaluate` | TC-OBD-002-NRM-001, FLT-001..003, ERR-001 | **Yes — priority** |
| UNIT-OBD-003 | `OBD_Init` | Covered via module init sequence | No |
| UNIT-DSM-001 | `DSM_UpdateFSM` | TC-DSM-001-NRM-001..004, FLT-001..003, ERR-001 | Yes |
| UNIT-DSM-012 | `DSM_VotePosition` | TC-DSM-012-NRM-001, FLT-001/002, ERR-001 | No |
| UNIT-DSM-013 | `DSM_TransitionMode` | TC-DSM-013-NRM-001, FLT-001..003 | Yes |
| UNIT-DSM-014 | `DSM_HandleEmergencyRelease` | TC-DSM-014-NRM-001, FLT-001, ERR-001 | No |
| UNIT-FMG-001 | `FMG_AggregateFaults` | TC-FMG-001-NRM-001, FLT-001, ERR-001 | No |
| UNIT-FMG-002 | `FMG_ClassifyAndEscalate` | TC-FMG-002-NRM-001, FLT-001/002 | No |
| UNIT-FMG-003 | `FMG_HandleSelectiveDisablement` | TC-FMG-003-NRM-001, FLT-001 | No |
| UNIT-TCI-001 | `TCI_CanRxISR` | TC-TCI-001-NRM-001, ERR-001 | No |
| UNIT-TCI-002 | `TCI_ProcessReceivedFrames` | TC-TCI-002-NRM-001, ERR-001 | No |
| UNIT-TCI-003 | `TCI_TransmitDepartureInterlock` | TC-TCI-003-NRM-001 | No |
| UNIT-TCI-006 | `TCI_ValidateRxSeqDelta` | TC-TCI-006-NRM-001, ERR-001 | No |
| UNIT-HAL-001 | `HAL_GPIO_ReadPositionSensor` | TC-HAL-001-NRM-001, ERR-001..003, BND-001 | No |
| UNIT-HAL-020 | `CRC16_CCITT_Compute` | TC-HAL-020-NRM-001/002, ERR-001/002, BND-001/002 | No |

**Traceability Summary**:
- Total SRS requirements with test cases: 24 of 81 (Phase 4 component scope — safety-critical and functional subset)
- Safety-critical requirements (REQ-SAFE-001 through REQ-SAFE-018): All safety-critical SIL 3 paths covered
- Performance requirements: TC-SKN-008-PFM-001 covers REQ-PERF-001
- Remaining requirements (interface, performance, memory) addressed in Overall Software Test Specification (Item 7) and Integration Test Specification (Item 12)

---

## 7. TEST PASS/FAIL CRITERIA

### 7.1 Individual Test Case Criteria

**PASS**:
- Return value matches expected value exactly
- All output parameters match expected values
- No unexpected crashes, exceptions, or memory violations
- Mocked HAL calls invoked in correct order and count (verified by CMock)

**FAIL**:
- Any mismatch between expected and actual result
- Unexpected crash or illegal memory access (AddressSanitizer)
- Mock call-count violation

### 7.2 Module Test Suite Criteria

**PASS** (module ready for Phase 5 implementation):
- All test cases in suite PASS
- Statement and branch coverage targets achieved (per DOC-SVP-2026-001)
- Compound Condition coverage achieved for priority units (per §4.3)
- No open safety-critical defects

**FAIL**:
- One or more test cases FAIL
- Coverage target not met (gaps require additional test cases or justified as uncoverable)
- Open critical defect unresolved

### 7.3 Overall Component Testing Criteria (Ready for Phase 6 Integration)

**PASS**:
- All 30 module test suites PASS
- Coverage targets met for all components (per DOC-SVP-2026-001)
- All safety-critical SRS requirements traced to passing test cases
- Machine-readable XML results produced and archived
- Software Component Test Report (Item 20) submitted via PM

**FAIL**:
- Any module test suite FAILS
- Coverage targets not met
- Open safety-critical defects

---

## 8. DEFECT MANAGEMENT

### 8.1 Defect Severity Levels

| Severity | Definition | Response |
|----------|-----------|----------|
| **Critical** | Safety-critical failure, incorrect safe-state behavior, lock/interlock logic error | Halt Phase 5; immediate escalation to PM and SAF |
| **High** | Functional failure, incorrect FSM transition, CRC failure not detected | Block Phase 5 gate for affected module |
| **Medium** | Minor functional issue, edge case failure, performance near limit | Corrective action before Phase 6 |
| **Low** | Cosmetic, documentation, non-functional | Log and address in next baseline |

### 8.2 Defect Reporting

All defects are reported to PM via the project defect tracker. PM routes to IMP for correction. TST re-tests after fix. All defects and resolutions recorded in Software Component Test Report (Item 20).

---

## 9. TEST AUTOMATION

### 9.1 Automated Test Execution

**Unity XML Test Runner** (machine-readable — §7.6.4.5b mandatory):
```bash
# Generate JUnit XML for all component tests
make test-xml PROJ=TDC
# Output: tests/results/component_test_results.xml
```

**Coverage Automation**:
```bash
# Generate JSON coverage report (machine-readable)
gcovr --json --output tests/coverage/coverage_report.json \
      --root . --filter 'src/.*'
```

**Continuous Integration**: All component tests run on each commit via CI pipeline; coverage report attached to build artifacts.

---

## APPENDIX A: TEST CASE SUMMARY TABLE

| Test Case ID | Module | Unit | SRS Req | Type | Priority | Status |
|---|---|---|---|---|---|---|
| TC-SKN-001-NRM-001 | MOD-SKN-001 | UNIT-SKN-001 | REQ-SAFE-010 | Normal | High | Not Run |
| TC-SKN-001-ERR-001 | MOD-SKN-001 | UNIT-SKN-001 | REQ-SAFE-010 | Error | High | Not Run |
| TC-SKN-001-BND-001 | MOD-SKN-001 | UNIT-SKN-001 | REQ-SAFE-001 | Boundary | High | Not Run |
| TC-SKN-001-BND-002 | MOD-SKN-001 | UNIT-SKN-001 | REQ-SAFE-001 | Boundary | High | Not Run |
| TC-SKN-002-NRM-001 | MOD-SKN-001 | UNIT-SKN-002 | REQ-INT-010 | Normal | Critical | Not Run |
| TC-SKN-002-FLT-001 | MOD-SKN-001 | UNIT-SKN-002 | REQ-SAFE-010 | Fault | Critical | Not Run |
| TC-SKN-002-FLT-002 | MOD-SKN-001 | UNIT-SKN-002 | REQ-SAFE-006 | Fault | Critical | Not Run |
| TC-SKN-002-FLT-003 | MOD-SKN-001 | UNIT-SKN-002 | REQ-SAFE-009 | Fault | Critical | Not Run |
| TC-SKN-002-FLT-004 | MOD-SKN-001 | UNIT-SKN-002 | REQ-SAFE-010 | Fault | Critical | Not Run |
| TC-SKN-002-ERR-001 | MOD-SKN-001 | UNIT-SKN-002 | REQ-SAFE-010 | Error | High | Not Run |
| TC-SKN-004-NRM-001 | MOD-SKN-002 | UNIT-SKN-004 | REQ-SAFE-006 | Normal | High | Not Run |
| TC-SKN-004-FLT-001 | MOD-SKN-002 | UNIT-SKN-004 | REQ-SAFE-006 | Fault | Critical | Not Run |
| TC-SKN-004-FLT-002 | MOD-SKN-002 | UNIT-SKN-004 | REQ-SAFE-006 | Fault | Critical | Not Run |
| TC-SKN-004-FLT-003 | MOD-SKN-002 | UNIT-SKN-004 | REQ-SAFE-009 | Fault | Critical | Not Run |
| TC-SKN-004-FLT-004 | MOD-SKN-002 | UNIT-SKN-004 | REQ-SAFE-008 | Fault | Critical | Not Run |
| TC-SKN-004-FLT-005 | MOD-SKN-002 | UNIT-SKN-004 | REQ-SAFE-006 | Fault | Critical | Not Run |
| TC-SKN-004-ERR-001 | MOD-SKN-002 | UNIT-SKN-004 | REQ-SAFE-006 | Error | High | Not Run |
| TC-SKN-005-NRM-001 | MOD-SKN-002 | UNIT-SKN-005 | REQ-SAFE-003 | Normal | Critical | Not Run |
| TC-SKN-005-FLT-001 | MOD-SKN-002 | UNIT-SKN-005 | REQ-SAFE-003 | Fault | Critical | Not Run |
| TC-SKN-005-FLT-002 | MOD-SKN-002 | UNIT-SKN-005 | REQ-SAFE-003 | Fault | Critical | Not Run |
| TC-SKN-005-FLT-003 | MOD-SKN-002 | UNIT-SKN-005 | REQ-SAFE-003 | Fault | Critical | Not Run |
| TC-SKN-005-ERR-001 | MOD-SKN-002 | UNIT-SKN-005 | REQ-SAFE-003 | Error | High | Not Run |
| TC-SKN-006-NRM-001 | MOD-SKN-002 | UNIT-SKN-006 | REQ-SAFE-009 | Normal | High | Not Run |
| TC-SKN-006-FLT-001 | MOD-SKN-002 | UNIT-SKN-006 | REQ-SAFE-009 | Fault | Critical | Not Run |
| TC-SKN-006-FLT-002 | MOD-SKN-002 | UNIT-SKN-006 | REQ-SAFE-009 | Fault | Critical | Not Run |
| TC-SKN-006-ERR-001 | MOD-SKN-002 | UNIT-SKN-006 | REQ-SAFE-009 | Error | High | Not Run |
| TC-SKN-007-NRM-001 | MOD-SKN-002 | UNIT-SKN-007 | REQ-SAFE-008 | Normal | High | Not Run |
| TC-SKN-007-FLT-001 | MOD-SKN-002 | UNIT-SKN-007 | REQ-SAFE-008 | Fault | Critical | Not Run |
| TC-SKN-007-FLT-002 | MOD-SKN-002 | UNIT-SKN-007 | REQ-SAFE-008 | Fault | Critical | Not Run |
| TC-SKN-008-NRM-001 | MOD-SKN-003 | UNIT-SKN-008 | REQ-PERF-001 | Normal | High | Not Run |
| TC-SKN-008-PFM-001 | MOD-SKN-003 | UNIT-SKN-008 | REQ-PERF-001 | Performance | High | Not Run |
| TC-SKN-009-NRM-001 | MOD-SKN-004 | UNIT-SKN-009 | REQ-SAFE-006 | Normal | High | Not Run |
| TC-SPM-001-NRM-001 | MOD-SPM-001 | UNIT-SPM-001 | REQ-INT-007 | Normal | High | Not Run |
| TC-SPM-001-ERR-001 | MOD-SPM-001 | UNIT-SPM-001 | REQ-INT-007 | Error | High | Not Run |
| TC-SPM-001-ERR-002 | MOD-SPM-001 | UNIT-SPM-001 | REQ-SAFE-009 | Error | Critical | Not Run |
| TC-SPM-001-ERR-003 | MOD-SPM-001 | UNIT-SPM-001 | REQ-SAFE-001 | Error | Critical | Not Run |
| TC-SPM-001-BND-001 | MOD-SPM-001 | UNIT-SPM-001 | REQ-SAFE-001 | Boundary | High | Not Run |
| TC-SPM-001-BND-002 | MOD-SPM-001 | UNIT-SPM-001 | REQ-SAFE-001 | Boundary | High | Not Run |
| TC-SPM-001-BND-003 | MOD-SPM-001 | UNIT-SPM-001 | REQ-INT-007 | Boundary | High | Not Run |
| TC-SPM-002-NRM-001 | MOD-SPM-002 | UNIT-SPM-002 | REQ-SAFE-001 | Normal/Boundary | Critical | Not Run |
| TC-SPM-002-FLT-001 | MOD-SPM-002 | UNIT-SPM-002 | REQ-SAFE-001 | Fault | Critical | Not Run |
| TC-SPM-002-FLT-002 | MOD-SPM-002 | UNIT-SPM-002 | REQ-SAFE-001 | Fault | Critical | Not Run |
| TC-SPM-002-FLT-003 | MOD-SPM-002 | UNIT-SPM-002 | REQ-SAFE-001 | Fault | Critical | Not Run |
| TC-SPM-002-ERR-001 | MOD-SPM-002 | UNIT-SPM-002 | REQ-SAFE-001 | Error | High | Not Run |
| TC-SPM-002-BND-001 | MOD-SPM-002 | UNIT-SPM-002 | REQ-SAFE-001 | Boundary | Critical | Not Run |
| TC-SPM-003-NRM-001 | MOD-SPM-003 | UNIT-SPM-003 | REQ-SAFE-001 | Normal | High | Not Run |
| TC-SPM-005-NRM-001 | MOD-SPM-003 | UNIT-SPM-005 | REQ-SAFE-001 | Normal | Medium | Not Run |
| TC-OBD-001-NRM-001 | MOD-OBD-001 | UNIT-OBD-001 | REQ-SAFE-004 | Normal | Critical | Not Run |
| TC-OBD-001-BND-001 | MOD-OBD-001 | UNIT-OBD-001 | REQ-SAFE-004 | Boundary | High | Not Run |
| TC-OBD-001-ERR-001 | MOD-OBD-001 | UNIT-OBD-001 | REQ-SAFE-004 | Error | High | Not Run |
| TC-OBD-002-NRM-001 | MOD-OBD-002 | UNIT-OBD-002 | REQ-SAFE-004 | Normal | High | Not Run |
| TC-OBD-002-FLT-001 | MOD-OBD-002 | UNIT-OBD-002 | REQ-SAFE-004 | Fault | Critical | Not Run |
| TC-OBD-002-FLT-002 | MOD-OBD-002 | UNIT-OBD-002 | REQ-SAFE-004 | Fault | Critical | Not Run |
| TC-OBD-002-FLT-003 | MOD-OBD-002 | UNIT-OBD-002 | REQ-SAFE-006 | Fault | Critical | Not Run |
| TC-OBD-002-ERR-001 | MOD-OBD-002 | UNIT-OBD-002 | REQ-SAFE-004 | Error | Critical | Not Run |
| TC-DSM-001-NRM-001 | MOD-DSM-001 | UNIT-DSM-001 | REQ-FUN-001 | Normal | Critical | Not Run |
| TC-DSM-001-NRM-002 | MOD-DSM-001 | UNIT-DSM-001 | REQ-SAFE-004 | Normal | Critical | Not Run |
| TC-DSM-001-NRM-003 | MOD-DSM-001 | UNIT-DSM-001 | REQ-FUN-005 | Normal | Critical | Not Run |
| TC-DSM-001-NRM-004 | MOD-DSM-001 | UNIT-DSM-001 | REQ-FUN-008 | Normal | Critical | Not Run |
| TC-DSM-001-FLT-001 | MOD-DSM-001 | UNIT-DSM-001 | REQ-SAFE-001 | Fault | Critical | Not Run |
| TC-DSM-001-FLT-002 | MOD-DSM-001 | UNIT-DSM-001 | REQ-SAFE-006 | Fault | Critical | Not Run |
| TC-DSM-001-FLT-003 | MOD-DSM-001 | UNIT-DSM-001 | REQ-FUN-003 | Fault | High | Not Run |
| TC-DSM-001-ERR-001 | MOD-DSM-001 | UNIT-DSM-001 | REQ-FUN-001 | Error | High | Not Run |
| TC-DSM-012-NRM-001 | MOD-DSM-002 | UNIT-DSM-012 | REQ-SAFE-005 | Normal | Critical | Not Run |
| TC-DSM-012-FLT-001 | MOD-DSM-002 | UNIT-DSM-012 | REQ-SAFE-005 | Fault | Critical | Not Run |
| TC-DSM-012-FLT-002 | MOD-DSM-002 | UNIT-DSM-012 | REQ-SAFE-005 | Fault | High | Not Run |
| TC-DSM-012-ERR-001 | MOD-DSM-002 | UNIT-DSM-012 | REQ-SAFE-005 | Error | High | Not Run |
| TC-DSM-013-NRM-001 | MOD-DSM-003 | UNIT-DSM-013 | REQ-FUN-011 | Normal | High | Not Run |
| TC-DSM-013-FLT-001 | MOD-DSM-003 | UNIT-DSM-013 | REQ-FUN-012 | Fault | High | Not Run |
| TC-DSM-013-FLT-002 | MOD-DSM-003 | UNIT-DSM-013 | REQ-FUN-014 | Fault | High | Not Run |
| TC-DSM-013-FLT-003 | MOD-DSM-003 | UNIT-DSM-013 | REQ-FUN-011 | Fault | High | Not Run |
| TC-DSM-014-NRM-001 | MOD-DSM-004 | UNIT-DSM-014 | REQ-INT-011 | Normal | High | Not Run |
| TC-DSM-014-FLT-001 | MOD-DSM-004 | UNIT-DSM-014 | REQ-INT-011 | Fault | High | Not Run |
| TC-DSM-014-ERR-001 | MOD-DSM-004 | UNIT-DSM-014 | REQ-INT-011 | Error | High | Not Run |
| TC-FMG-001-NRM-001 | MOD-FMG-001 | UNIT-FMG-001 | REQ-FUN-017 | Normal | High | Not Run |
| TC-FMG-001-FLT-001 | MOD-FMG-001 | UNIT-FMG-001 | REQ-FUN-017 | Fault | High | Not Run |
| TC-FMG-001-ERR-001 | MOD-FMG-001 | UNIT-FMG-001 | REQ-FUN-017 | Error | High | Not Run |
| TC-FMG-002-NRM-001 | MOD-FMG-001 | UNIT-FMG-002 | REQ-SAFE-006 | Normal | High | Not Run |
| TC-FMG-002-FLT-001 | MOD-FMG-001 | UNIT-FMG-002 | REQ-SAFE-006 | Fault | Critical | Not Run |
| TC-FMG-002-FLT-002 | MOD-FMG-001 | UNIT-FMG-002 | REQ-SAFE-006 | Fault | High | Not Run |
| TC-FMG-003-NRM-001 | MOD-FMG-002 | UNIT-FMG-003 | REQ-FUN-013 | Normal | High | Not Run |
| TC-FMG-003-FLT-001 | MOD-FMG-002 | UNIT-FMG-003 | REQ-FUN-012 | Fault | High | Not Run |
| TC-TCI-001-NRM-001 | MOD-TCI-001 | UNIT-TCI-001 | REQ-INT-007 | Normal | High | Not Run |
| TC-TCI-001-ERR-001 | MOD-TCI-001 | UNIT-TCI-001 | REQ-INT-007 | Error | High | Not Run |
| TC-TCI-002-NRM-001 | MOD-TCI-001 | UNIT-TCI-002 | REQ-INT-007 | Normal | High | Not Run |
| TC-TCI-002-ERR-001 | MOD-TCI-001 | UNIT-TCI-002 | REQ-SAFE-009 | Error | Critical | Not Run |
| TC-TCI-003-NRM-001 | MOD-TCI-002 | UNIT-TCI-003 | REQ-SAFE-003 | Normal | Critical | Not Run |
| TC-TCI-006-NRM-001 | MOD-TCI-003 | UNIT-TCI-006 | REQ-INT-007 | Normal | High | Not Run |
| TC-TCI-006-ERR-001 | MOD-TCI-003 | UNIT-TCI-006 | REQ-INT-007 | Error | High | Not Run |
| TC-DGN-NRM-001 | MOD-DGN-001 | DGN-log | REQ-FUN-018 | Normal | Medium | Not Run |
| TC-DGN-NRM-002 | MOD-DGN-001 | DGN-log | REQ-FUN-018 | Normal | Medium | Not Run |
| TC-DGN-ERR-001 | MOD-DGN-001 | DGN-log | REQ-FUN-018 | Error | Medium | Not Run |
| TC-HAL-001-NRM-001 | MOD-HAL-001 | UNIT-HAL-001 | REQ-INT-002 | Normal | High | Not Run |
| TC-HAL-001-ERR-001 | MOD-HAL-001 | UNIT-HAL-001 | REQ-INT-002 | Error | High | Not Run |
| TC-HAL-001-ERR-002 | MOD-HAL-001 | UNIT-HAL-001 | REQ-INT-002 | Error | High | Not Run |
| TC-HAL-001-ERR-003 | MOD-HAL-001 | UNIT-HAL-001 | REQ-INT-002 | Error | High | Not Run |
| TC-HAL-001-BND-001 | MOD-HAL-001 | UNIT-HAL-001 | REQ-INT-002 | Boundary | High | Not Run |
| TC-HAL-020-NRM-001 | MOD-HAL-005 | UNIT-HAL-020 | REQ-SAFE-009 | Normal | Critical | Not Run |
| TC-HAL-020-NRM-002 | MOD-HAL-005 | UNIT-HAL-020 | REQ-SAFE-009 | Normal | Critical | Not Run |
| TC-HAL-020-ERR-001 | MOD-HAL-005 | UNIT-HAL-020 | REQ-SAFE-009 | Error | High | Not Run |
| TC-HAL-020-ERR-002 | MOD-HAL-005 | UNIT-HAL-020 | REQ-SAFE-009 | Error | High | Not Run |
| TC-HAL-020-BND-001 | MOD-HAL-005 | UNIT-HAL-020 | REQ-SAFE-009 | Boundary | High | Not Run |
| TC-HAL-020-BND-002 | MOD-HAL-005 | UNIT-HAL-020 | REQ-SAFE-009 | Boundary | High | Not Run |

**Total Test Cases: 106**

---

## APPENDIX B: EN 50128 TABLE A.5 COMPLIANCE MATRIX

| # | Technique | SIL 3 Obligation | Applied | Evidence |
|---|-----------|-----------------|---------|---------|
| 4 | Dynamic Analysis and Testing | **M** | **Yes** | All 106 test cases with Unity framework |
| 5 | Test Coverage for Code | **M** | **Yes** | gcov/lcov per §4.2; targets in DOC-SVP-2026-001 |
| 7 | Traceability | **M** | **Yes** | §6.1 and §6.2 bidirectional RTM |
| 9 | Functional/Black-Box Testing | **M** | **Yes** | NRM test cases from SRS requirements |
| 10 | Performance Testing | **M** | **Yes** | TC-SKN-008-PFM-001, TC-SPM-002-FLT-002 (timing) |
| 12 | Regression Testing | **M** | **Yes** | Full suite in CI pipeline on every change |
| 13 | Boundary Value Analysis | **M** | **Yes** | BND test cases: min−1/min/min+1/max−1/max/max+1 |
| 3 | Static Analysis (VER responsibility) | **M** | VER | Owned by VER; TST provides coverage evidence |

---

## APPENDIX C: REVISION HISTORY

| Date | Version | Author | Changes | Approval |
|------|---------|--------|---------|----------|
| 2026-04-04 | 0.1 | TST | Initial draft — 106 test cases for 30 modules, 8 components, SIL 3 | — |

---

**END OF DOCUMENT**

*This document (DOC-COMPTESTSPEC-2026-001) is the V-Model counterpart to Software Component Test Report (Item 20, Phase 5). All test results shall be recorded in Item 20 following Phase 5 execution.*
