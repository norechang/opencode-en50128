# Software Integration Test Specification

**REFERENCE**: EN 50128:2011 Section 7.6, Table A.6, Annex C Item 12

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SITSPEC-2026-001 |
| **CI ID** | CI-SITSPEC-TDC-001 |
| **Version** | 0.1 DRAFT |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Software Integrator (INT) |
| **Reviewer** | Software Verifier (VER) |
| **Approver** | Project Manager (PM) |
| **Status** | Draft — submitted to QUA for review |

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-04-02 | INT | Initial draft — Phase 3 SW Integration Test Specification from DOC-SAS-2026-001 v0.2, DOC-SDS-2026-001 v0.1, DOC-SIS-2026-001 v0.1. Covers all 20 internal interfaces (IF-001–IF-020). | — |

## APPROVALS

**EN 50128 Annex C Table C.1 Signature Chain — Item 12 (SW Integration Test Specification)**

| Written By | 1st Check | 2nd Check | Date |
|------------|-----------|-----------|------|
| Software Integrator<br>Name: [INT]<br>Signature: _____________ | Software Verifier<br>Name: [VER]<br>Signature: _____________ | Quality Assurance Engineer<br>Name: [QUA]<br>Signature: _____________ | 2026-04-02 |

**Notes:**
- **Written By**: INT is the owner of Annex C Item 12 (EN 50128 §5.3.6, Table B.6).
- **1st Check**: VER independently reviews per §6.2. Mandatory independence at SIL 3.
- **2nd Check**: QUA verifies process compliance per §6.5.
- INT MUST NOT contact QUA or VER directly — all submissions route through PM.
- Test EXECUTION (Phase 6) and REPORTS (items 21/22) are separate deliverables.

---

## 1. INTRODUCTION

### 1.1 Purpose

This document constitutes the **Software Integration Test Specification** for the TDC
(Train Door Control System) in accordance with EN 50128:2011 Section 7.6 and Annex C
Item 12.

This specification defines:
- Integration strategy for 8 TDC software components
- Test cases for all 20 internal interfaces (IF-001 through IF-020) as defined in
  DOC-SIS-2026-001 v0.1
- Safety-critical integration scenarios including 2oo2 cross-channel comparison
- Entry/exit criteria for each integration phase
- Traceability from every test case to SAS architecture and SIS interface specifications

**Phase Note**: This specification is produced in **Phase 3** (Architecture & Design).
Test EXECUTION and the SW Integration Test Report (Item 21) are Phase 6 activities.

### 1.2 Scope

**In Scope**:
- Software-to-software component integration (8 components, 20 internal interfaces)
- Interface testing for all IF-001–IF-020 as specified in DOC-SIS-2026-001
- Cross-channel 2oo2 integration (Channel A ↔ Channel B SPI, IF-017)
- Safety gate integration (safe state, speed interlock)
- Performance and timing verification at integration boundaries
- Error propagation and fault detection integration testing

**Out of Scope**:
- Unit (component-level) tests — see Component Test Specification (Annex C Item 17)
- Hardware/Software integration — see Item 13 (HW/SW Integration Test Specification)
- System-level validation — see Overall Software Test Specification (Annex C Item 16)
- Test EXECUTION and results — see SW Integration Test Report (Annex C Item 21)

### 1.3 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **2oo2** | Two-out-of-two voting — both channels/sensors must agree |
| **CRC-16-CCITT** | Cyclic Redundancy Check, polynomial 0x1021, init 0xFFFF, no final XOR |
| **DCU** | Door Control Unit — dual-channel (2oo2) embedded processing module |
| **DSM** | Door State Machine component (COMP-004) |
| **DGN** | Diagnostics component (COMP-007) |
| **FMG** | Fault Manager component (COMP-005) |
| **HAL** | Hardware Abstraction Layer component (COMP-008) |
| **IF-NNN** | Internal interface identifier from DOC-SIS-2026-001 |
| **OBD** | Obstacle Detector component (COMP-003) |
| **SKN** | Safety Kernel component (COMP-001) |
| **SPM** | Speed Monitor component (COMP-002) |
| **TCI** | TCMS Interface component (COMP-006) |
| **WCET** | Worst-Case Execution Time |

### 1.4 Input Documents

| Document ID | Title | Version | Role |
|-------------|-------|---------|------|
| DOC-SAS-2026-001 | Software Architecture Specification | 0.2 DRAFT | Architecture, component inventory, interface summary |
| DOC-SDS-2026-001 | Software Design Specification | 0.1 DRAFT | Module design, data types, algorithms |
| DOC-SIS-2026-001 | Software Interface Specifications | 0.1 DRAFT | Authoritative interface definitions IF-001–IF-020 |
| DOC-SRS-2026-001 | Software Requirements Specification | 0.1 DRAFT | Requirements traceability source |

### 1.5 Output Documents

| Document ID | Title | Owner | Phase |
|-------------|-------|-------|-------|
| DOC-SITSPEC-2026-001 | Software Integration Test Specification (this document) | INT | 3 |
| DOC-SITREP-2026-001 | Software Integration Test Report (Item 21) | INT | 6 — after TST execution |

---

## 2. INTEGRATION STRATEGY

### 2.1 Integration Approach

**Integration Strategy**: **Bottom-Up with Safety-First Prioritisation**

**Rationale**: The TDC software architecture has a clear dependency hierarchy with HAL
at the base and SKN at the apex of safety decision-making. Bottom-up integration:
1. Eliminates the need for stubs of lower-level components — HAL, the most hardware-
   dependent component, is integrated first against the HW/SW integration testing
   environment (Item 13), then available for all SW integration phases.
2. Starts with well-bounded, low-risk components (HAL, DGN) before tackling safety-
   critical components (SKN, FMG, DSM).
3. Matches the cyclic executive execution order (HAL provides data before consumers read).
4. Minimises stub complexity — only TCI requires a minimal CAN-bus stub in early phases.

**Safety-First Variation**: While strictly bottom-up, the safety-critical integration
path (SKN ↔ all) is prioritised within each phase. Safety gate signals
(`safe_state_active`, `speed_interlock_active`) are verified at each integration step
before proceeding.

### 2.2 Integration Phases Overview

The integration is structured into 5 progressive phases. Each phase must be completed and
its exit criteria satisfied before the next phase begins (EN 50128 §7.6.4.1).

| Phase | Scope | Key Interfaces Tested | Safety Priority |
|-------|-------|-----------------------|----------------|
| **Phase 1** | HAL + DGN integration | IF-020 (DGN↔SPI Flash) | Low (SIL 1 path) |
| **Phase 2** | TCI + SPM integration | IF-001 (TCI→SPM), IF-002 (SPM→SKN) | HIGH (speed interlock chain) |
| **Phase 3** | OBD + DSM integration | IF-004–IF-006 (sensor chain), IF-010, IF-011 (HAL actuators) | CRITICAL (obstacle detection) |
| **Phase 4** | FMG + SKN integration | IF-012 (FMG→SKN), IF-015 (SKN broadcast), IF-016 (SKN→TCI) | CRITICAL (safe state) |
| **Phase 5** | Full system + cross-channel | IF-017 (SPI 2oo2), complete 20-interface regression | CRITICAL (2oo2 architecture) |

**Integration Order Diagram**:
```
Phase 1: HAL ──IF-020──► DGN
              (verified by HW/SW integration, Item 13)

Phase 2: HAL ──IF-001──► TCI ──IF-001──► SPM ──IF-002──► [SKN stub]
                                          SPM ──IF-003──► [DSM stub]

Phase 3: HAL ──IF-004──► DSM ──IF-006◄── OBD ◄──IF-005── HAL
         DSM ──IF-009──► TCI (status reporting)
         DSM ──IF-010──► HAL (lock actuator)
         DSM ──IF-011──► HAL (motor PWM)

Phase 4: [Phase 2+3 integration]
         FMG ──IF-012──► SKN ──IF-015──► ALL (safe state broadcast)
         SKN ──IF-016──► TCI ──IF-013◄── FMG ──IF-014──► DGN
         TCI ──IF-018──► DSM (commands)

Phase 5: SKN(ChA) ──IF-017──► SKN(ChB)  [2oo2 cross-channel]
         Complete IF-001..IF-020 regression
         Performance tests (HR SIL 3)
```

### 2.3 Integration Techniques (EN 50128 Table A.6)

The following EN 50128 Table A.6 techniques are applied at SIL 3:

| # | Technique | SIL 3 Obligation | Applied | Section |
|---|-----------|-----------------|---------|---------|
| 1 | Functional and Black-Box Testing | HR | **Yes** | §4.2 (functional test cases per phase) |
| 3 | Interface Testing | **M** | **Yes** | §4.3 (ALL 20 interfaces have ≥1 test case) |
| 4 | Performance Testing | HR | **Yes** | §4.7 (timing tests: WCET, interlock latency) |
| 6 | Structural Coverage (Branch) | **M** | Yes (measured by TST in Phase 6) | §7 (coverage target) |
| 7 | Error Guessing | R | Yes | §4.5 (error condition tests) |
| 8 | Cause Consequence Diagrams | HR | Yes | SAS §7.1 (safety function allocation) |

**Mandatory SIL 3 compliance note**: Table A.6 Item 3 (Interface Testing) is Mandatory
at SIL 3–4. Every interface in IF-001 through IF-020 SHALL have at least one test case
in this specification. See §5.1 for the complete traceability matrix.

### 2.4 Stubs and Drivers

**Stubs Required** (minimal — bottom-up strategy minimises stub need):

| Stub | Simulates | Used In Phase | Functionality |
|------|-----------|--------------|---------------|
| `stub_skn.c` | COMP-001 SKN | Phase 2 | Accept speed interlock flag; provide safe_state_active = 0 |
| `stub_dsm.c` | COMP-004 DSM | Phase 2 | Accept speed gate; provide door_states = DOOR_UNKNOWN |
| `stub_skn_full.c` | COMP-001 SKN | Phase 3 | Accept door states; evaluate departure interlock logic |
| `stub_can_bus.c` | CAN hardware | Phase 2–4 | Inject CAN frames with configurable CRC and seq counter |

**Drivers Required**:

| Driver | Simulates | Used In Phase | Functionality |
|--------|-----------|--------------|---------------|
| `driver_scheduler.c` | Static cyclic executive | All | Drives 20 ms cycle; calls components in execution order |
| `driver_sensor_inject.c` | HAL sensor inputs | Phase 3 | Injects position/lock/obstacle sensor values |

**Stub/Driver Requirements**:
- All stubs SHALL be placed under CM control in `tests/integration/stubs/`
- Stubs SHALL simulate all error conditions (ERR_NULL_PTR, ERR_HW_FAULT, etc.)
- Stubs SHALL record call counts and last arguments for test verification
- Stubs SHALL be reviewed by VER before use in integration testing

---

## 3. INTEGRATION TEST ENVIRONMENT

### 3.1 Test Environment Configuration

**Software Environment** (SW-only integration, prior to target hardware):

| Parameter | Value |
|-----------|-------|
| Host platform | Linux x86_64 (cross-compilation for SW unit tests; native for integration harness) |
| Target MCU | STM32H743 (ARM Cortex-M7, 400 MHz) — used from Phase 5 onward |
| Compiler | arm-none-eabi-gcc 12.x with `-O0 -g` for coverage; `-O2` for performance tests |
| Build system | CMake + Make |
| Test framework | Unity (C unit test framework) for integration test harness |
| Coverage tool | gcov/lcov (host) + Segger SystemView (target) |
| Version control | Git |

**Phase 5 Cross-Channel Configuration**:
- Two physical STM32H743 boards (DCU-A and DCU-B)
- SPI cross-link cable between boards
- Logic analyser on SPI bus for frame capture
- Shared GND reference

### 3.2 Test Data Sources

- Interface specification test vectors: DOC-SIS-2026-001 §3–§4 boundary values
- Boundary value test data: speed 0–5000 (km/h×10), door_id [0–3], duty [0–100]
- Error condition test data: NULL pointers, out-of-range values, CRC-corrupted frames
- CRC-16-CCITT test vectors: standard polynomial 0x1021 reference vectors
- Performance test data: worst-case execution scenarios (all 4 doors active)

### 3.3 Integration Build Process

**Build Steps**:
1. Compile individual components (one `.c` → `.o` per module)
2. Compile appropriate stubs/drivers for the current integration phase
3. Link phase-specific test executable
4. Run test executable and capture results to XML (Unity output format)
5. Analyse coverage with lcov; verify branch coverage ≥ target (see §7.2)

**Configuration Baseline**: All components under test SHALL be at a known baseline
recorded in `SCMP` (DOC-SCMP-2026-001) before integration testing begins.

---

## 4. INTEGRATION TEST CASES

### 4.1 Test Case Convention

Each test case header uses the following format:

```
TC-INT-NNN: <test name>
Interface(s): IF-NNN [, IF-NNN ...]
SAS reference: COMP-NNN §<section>
SIS reference: DOC-SIS-2026-001 §<section>
SIL: 3
Type: Interface (M) | Functional (HR) | Performance (HR) | Error (R)
Integration Phase: <1–5>
Priority: Critical | High | Medium
```

### 4.2 Phase 1 — HAL + DGN Integration

**Objective**: Verify COMP-008 (HAL) provides correct GPIO, CAN, SPI, and timer
initialisation, and that COMP-007 (DGN) correctly writes to and reads from the SPI Flash
circular buffer via IF-020. This phase validates the non-safety diagnostic path.

---

**TC-INT-001: DGN event log write and read (IF-020)**
```
Interface(s): IF-020
SAS reference: COMP-007 (DGN) §4.8, COMP-008 (HAL) §4.9
SIS reference: DOC-SIS-2026-001 §3.21
SIL: SIL 1 (DGN path)
Type: Interface (M), Functional (HR)
Integration Phase: 1
Priority: High
```
**Objective**: Verify DGN correctly writes `event_log_entry_t` to the circular buffer in
SPI Flash via HAL SPI driver, and reads them back with CRC-16-CCITT integrity.

**Preconditions**:
- HAL SPI peripheral initialised (from HW/SW integration, Item 13)
- SPI Flash chip powered and accessible
- `event_log_entry_t` with valid CRC pre-populated

**Test Steps**:
1. Call `DGN_WriteLogEntry(&entry)` with a valid `event_log_entry_t` (timestamp=1000, source=1, event=5, data=0xABCD, correct CRC-16-CCITT)
2. Call `DGN_ReadLogEntry(0, &read_entry)`
3. Compare all fields of `entry` vs `read_entry`
4. Call `DGN_WriteLogEntry` 1024 times (fill circular buffer)
5. Write one more entry (entry 1025)
6. Read entry at index 0 — verify it is entry 1025 (wrap-around)

**Expected Results**:
- Steps 1–3: `read_entry` matches `entry` in all fields; CRC passes
- Steps 4–6: Circular buffer wraps; oldest entry overwritten; no memory overrun

**Pass/Fail Criteria**:
- PASS: All field comparisons succeed; CRC validation passes; circular wrap verified
- FAIL: Any field mismatch, CRC failure, or buffer overrun detected

**Postconditions**: Event log contains 1024 entries; buffer state is known

---

**TC-INT-002: DGN non-interference with safety state (IF-020, IF-015)**
```
Interface(s): IF-020, IF-015
SAS reference: COMP-007 §4.8, COMP-001 §4.2
SIS reference: DOC-SIS-2026-001 §3.21, §3.16
SIL: SIL 3 (safety gate verification)
Type: Interface (M), Functional (HR)
Integration Phase: 1
Priority: Critical
```
**Objective**: Verify DGN cannot modify `safe_state_active` or any SKN-owned safety variable.

**Preconditions**: DGN and SKN stub both initialised; `safe_state_active = 0`

**Test Steps**:
1. Set `safe_state_active = 0` via SKN stub
2. Execute DGN cycle including a `DGN_WriteLogEntry` call with `source_comp = 1` (SKN)
3. Read `safe_state_active`
4. Attempt to write `safe_state_active` directly from DGN code path (should be prevented by compile-time `const` or write-ownership rule)
5. Execute 100 DGN cycles; check `safe_state_active` after each

**Expected Results**:
- `safe_state_active` remains 0 throughout all DGN cycles
- No direct write to `safe_state_active` is possible from DGN module

**Pass/Fail Criteria**:
- PASS: `safe_state_active` unchanged after all DGN operations
- FAIL: `safe_state_active` changed by DGN

---

### 4.3 Phase 2 — TCI + SPM Integration (Speed Interlock Chain)

**Objective**: Verify the speed interlock chain: TCI receives CAN speed frames (IF-001),
SPM validates and derives the interlock flag (IF-002, IF-003). This tests the primary
SF-001 (Speed Interlock) data flow.

---

**TC-INT-003: Normal speed message delivery (IF-001)**
```
Interface(s): IF-001
SAS reference: COMP-006 (TCI) §4.7, COMP-002 (SPM) §4.3
SIS reference: DOC-SIS-2026-001 §3.2
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 2
Priority: Critical
```
**Objective**: Verify TCI correctly transfers a valid `tcms_speed_msg_t` to the shared
buffer readable by SPM.

**Preconditions**:
- CAN bus stub (`stub_can_bus.c`) initialised
- TCI module initialised with CAN RX filter for ID 0x100
- SPM module initialised with pointer to TCI speed buffer

**Test Steps**:
1. Inject CAN frame: ID=0x100, speed=500 (50.0 km/h×10), seq=1, CRC-16-CCITT computed correctly
2. Execute one TCI cycle (CAN RX processing)
3. Read `tcms_speed_msg_t` from shared buffer via SPM interface
4. Verify `speed_kmh_x10 = 500`, `seq_counter = 1`, CRC field correct
5. Inject next frame: seq=2, speed=0; verify seq increments and speed updates

**Expected Results**:
- Buffer contains exactly the injected values
- No CRC error reported; `can_crc_error_count` remains 0

**Pass/Fail Criteria**:
- PASS: All field values match injected frame; no CRC error
- FAIL: Mismatch or spurious CRC error

---

**TC-INT-004: CRC error on CAN speed frame — fail-safe behaviour (IF-001)**
```
Interface(s): IF-001
SAS reference: COMP-006 §4.7, COMP-002 §4.3
SIS reference: DOC-SIS-2026-001 §3.2 (Post-conditions, Fail-safe Default)
SIL: 3
Type: Interface (M), Error
Integration Phase: 2
Priority: Critical
```
**Objective**: Verify TCI does NOT update SPM buffer on CRC failure; previous valid
value is retained; error counter increments.

**Test Steps**:
1. Inject valid frame (speed=100, seq=1, correct CRC)
2. Execute TCI cycle; verify buffer = {100, 1, correct_CRC}
3. Inject frame with corrupted CRC (flip one bit)
4. Execute TCI cycle
5. Read SPM buffer; verify `speed_kmh_x10` still = 100 (unchanged)
6. Verify `can_crc_error_count` = 1

**Expected Results**:
- Step 5: Previous valid value retained (fail-safe behaviour per SIS §3.2)
- Step 6: Error counter = 1

**Pass/Fail Criteria**:
- PASS: Buffer unchanged after CRC failure; error counter incremented
- FAIL: Buffer updated with corrupted data or error counter not incremented

---

**TC-INT-005: CAN timeout — speed interlock activation (IF-001, IF-002)**
```
Interface(s): IF-001, IF-002
SAS reference: COMP-002 §4.3, COMP-006 §4.7
SIS reference: DOC-SIS-2026-001 §3.2, §3.3
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 2
Priority: Critical
```
**Objective**: Verify SPM activates `speed_interlock_active = 1` when CAN messages
are not received within 200 ms (CAN_TIMEOUT_MS).

**Test Steps**:
1. Inject valid speed frame (speed=0, train stopped); verify `speed_interlock_active = 0`
2. Advance system tick by 201 ms without injecting new CAN frames
3. Execute SPM cycle
4. Read `speed_interlock_active`
5. Inject new valid frame (speed=0); advance tick by 1 ms; execute SPM cycle
6. Read `speed_interlock_active`

**Expected Results**:
- Step 4: `speed_interlock_active = 1` (timeout expired → assume moving)
- Step 6: `speed_interlock_active` remains 1 until valid low-speed confirmed per SPM policy

**Pass/Fail Criteria**:
- PASS: Interlock activates at exactly 200 ms timeout; confirmed by SPM logic
- FAIL: Interlock not activated, or activated early (<200 ms)

---

**TC-INT-006: Speed interlock gate propagation to SKN (IF-002)**
```
Interface(s): IF-002
SAS reference: COMP-002 §4.3, COMP-001 §4.2
SIS reference: DOC-SIS-2026-001 §3.3
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 2
Priority: Critical
```
**Objective**: Verify SPM correctly writes `speed_interlock_active` to the shared
variable readable by SKN stub.

**Test Steps**:
1. Inject speed=600 (60.0 km/h×10); execute SPM; verify `speed_interlock_active = 1`
2. Read `speed_interlock_active` via SKN stub interface
3. Inject speed=30 (3.0 km/h×10); execute SPM; verify `speed_interlock_active = 0`
4. Read via SKN stub; verify = 0
5. Inject speed=0xFFFF (invalid sentinel); verify interlock = 1

**Pass/Fail Criteria**:
- PASS: SKN stub observes correct interlock state for all speed values
- FAIL: Mismatch between SPM output and SKN-visible variable

---

**TC-INT-007: Speed gate propagation to DSM (IF-003)**
```
Interface(s): IF-003
SAS reference: COMP-002 §4.3, COMP-004 §4.5
SIS reference: DOC-SIS-2026-001 §3.4
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 2
Priority: Critical
```
**Objective**: Verify DSM stub receives `speed_interlock_active` from SPM and refuses
door open transitions when interlock is active.

**Test Steps**:
1. Set `speed_interlock_active = 1` via SPM; attempt door OPEN command on DSM stub
2. Verify DSM stub rejects OPEN command (returns ERR_INVALID_STATE or equivalent)
3. Set `speed_interlock_active = 0` via SPM; attempt OPEN command
4. Verify DSM stub accepts OPEN command

**Pass/Fail Criteria**:
- PASS: OPEN rejected when interlock=1; accepted when interlock=0
- FAIL: OPEN accepted with interlock=1 (safety violation)

---

**TC-INT-008: Sequence counter validation on CAN RX (IF-001)**
```
Interface(s): IF-001
SAS reference: COMP-006 §4.7
SIS reference: DOC-SIS-2026-001 §4.7 (Reception Rules item 2)
SIL: 3
Type: Interface (M), Error
Integration Phase: 2
Priority: High
```
**Objective**: Verify TCI detects sequence counter discontinuities (jump > 1) and logs
`FAULT_SEQ_COUNTER_JUMP`.

**Test Steps**:
1. Inject frame seq=5; execute TCI; verify accepted
2. Inject frame seq=7 (skip 6); execute TCI
3. Verify FMG stub receives `FAULT_SEQ_COUNTER_JUMP` log entry
4. Inject frame seq=8 (resume normal); verify accepted without fault

**Pass/Fail Criteria**:
- PASS: Jump detected; fault logged; normal sequence accepted
- FAIL: Jump not detected or false positive on normal sequence

---

### 4.4 Phase 3 — OBD + DSM Integration (Obstacle Detection + Door FSM)

**Objective**: Verify obstacle detection (OBD) correctly integrates with DSM door state
machine, HAL sensor inputs (IF-004, IF-005), lock and motor actuators (IF-010, IF-011).
Critical for SF-003 (Obstacle Detection and Reversal) and SF-005 (Door Position).

---

**TC-INT-009: HAL position sensor read → DSM state transition (IF-004)**
```
Interface(s): IF-004
SAS reference: COMP-008 (HAL) §4.9, COMP-004 (DSM) §4.5
SIS reference: DOC-SIS-2026-001 §3.5
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 3
Priority: Critical
```
**Objective**: Verify DSM correctly reads HAL position sensor arrays (2oo2 voting) and
transitions door FSM states accordingly.

**Test Steps**:
1. Set `hal_pos_sensor_a[0]=0, hal_pos_sensor_b[0]=0` (door not at limit); execute DSM
2. Verify door 0 state = DOOR_INTERMEDIATE (or DOOR_UNKNOWN if never moved)
3. Set both sensors = 1 (both at open limit); execute DSM
4. Verify door 0 state = DOOR_FULLY_OPEN
5. Set sensors to disagree (A=1, B=0); execute 3 DSM cycles
6. Verify door state → DOOR_FAULT; FMG receives `ERR_SENSOR_DISAGREE`

**Pass/Fail Criteria**:
- PASS: FSM transitions match 2oo2 voting rules; sensor disagreement → DOOR_FAULT
- FAIL: FSM transitions without 2oo2 agreement, or disagreement not detected

---

**TC-INT-010: HAL obstacle sensor ISR → OBD → DSM reversal (IF-005, IF-006)**
```
Interface(s): IF-005, IF-006
SAS reference: COMP-003 (OBD) §4.4, COMP-004 (DSM) §4.5
SIS reference: DOC-SIS-2026-001 §3.6, §3.7
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 3
Priority: Critical
```
**Objective**: Verify obstacle ISR sets `hal_obs_isr_flag`, OBD propagates
`obstacle_flags`, DSM enters FSM_OBSTACLE_HALT and commands motor stop.

**Test Steps**:
1. Place DSM door 0 in FSM_CLOSING state
2. Simulate ISR trigger: call `OBD_ObstacleISR(0)` directly; verify `hal_obs_isr_flag[0] = 1`
3. Execute OBD cycle; verify `obstacle_flags[0] = 1`
4. Execute DSM cycle; verify door 0 transitions to FSM_OBSTACLE_HALT
5. Verify `motor_duty[0] = 0` (motor stop) and lock actuator commanded locked
6. Clear sensor (set sensors 0 for 3 cycles); verify OBD clears `obstacle_flags[0] = 0`

**Expected Results**: Reversal latency (ISR→motor stop) < 1 ms for ISR path; < 20 ms for polled path

**Pass/Fail Criteria**:
- PASS: obstacle_flags set within one cycle; DSM halts motor; obstacle clears after 3 clear readings
- FAIL: Motor not stopped on obstacle; flag not cleared after 3 clear cycles

---

**TC-INT-011: OBD → SKN obstacle propagation for safety arbitration (IF-007)**
```
Interface(s): IF-007
SAS reference: COMP-003 §4.4, COMP-001 §4.2
SIS reference: DOC-SIS-2026-001 §3.8
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 3
Priority: Critical
```
**Objective**: Verify SKN stub independently reads `obstacle_flags` from OBD and can
trigger safe state independently of DSM response.

**Test Steps**:
1. Set `obstacle_flags[1] = 1` (door 1) via OBD module
2. Execute SKN stub cycle; verify `safe_state_active = 1` triggered by obstacle
3. Verify all DSM door FSMs respond to `safe_state_active = 1`
4. Clear `obstacle_flags`; verify SKN does not auto-clear safe state (irreversible within cycle)

**Pass/Fail Criteria**:
- PASS: SKN triggers safe state from obstacle flag independently of DSM
- FAIL: SKN does not observe obstacle_flags, or safe state not triggered

---

**TC-INT-012: DSM → HAL lock actuator command (IF-010)**
```
Interface(s): IF-010
SAS reference: COMP-004 §4.5, COMP-008 §4.9
SIS reference: DOC-SIS-2026-001 §3.11
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 3
Priority: Critical
```
**Objective**: Verify DSM correctly calls `HAL_GPIO_SetLockActuator` with correct
parameters when transitioning to LOCKING state; verify fail-safe encoding.

**Test Steps**:
1. Place door 0 in FSM_LOCKING state; execute DSM cycle
2. Verify `HAL_GPIO_SetLockActuator(0, 0)` called (lock = 0 = locked)
3. Inject `safe_state_active = 1`; execute DSM cycle
4. Verify HAL lock command = 0 (locked) for all doors
5. Attempt unlock command when `speed_interlock_active = 1`
6. Verify DSM rejects unlock (ERR_NOT_PERMITTED or no HAL call)

**Pass/Fail Criteria**:
- PASS: Lock command sent with correct door_id and lock value; safe state → all locked
- FAIL: Wrong door_id, wrong lock value, or unlock permitted under interlock

---

**TC-INT-013: DSM → HAL motor PWM command (IF-011)**
```
Interface(s): IF-011
SAS reference: COMP-004 §4.5, COMP-008 §4.9
SIS reference: DOC-SIS-2026-001 §3.12
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 3
Priority: Critical
```
**Objective**: Verify DSM correctly calls HAL PWM and direction functions when
transitioning between door FSM states; verify fail-safe (duty=0) on safe state.

**Test Steps**:
1. Transition door 0 from FSM_IDLE to FSM_OPENING; verify `HAL_PWM_SetDutyCycle(0, X)` where X>0 and `HAL_GPIO_SetMotorDirection(0, 0)` (open direction)
2. Transition door 0 to FSM_CLOSING; verify direction=1 (close)
3. Inject `safe_state_active = 1`; execute DSM cycle
4. Verify `HAL_PWM_SetDutyCycle(door, 0)` called for ALL 4 doors
5. Inject `HAL_PWM_SetDutyCycle` returning `ERR_HW_FAULT`
6. Verify DSM logs fault to FMG and enters FSM_FAULT

**Pass/Fail Criteria**:
- PASS: Direction encoding correct; duty=0 on safe state for all doors; HW fault escalated to FMG
- FAIL: Wrong direction, duty not cleared on safe state, or HW fault silently ignored

---

**TC-INT-014: DSM → TCI per-door status reporting (IF-009)**
```
Interface(s): IF-009
SAS reference: COMP-004 §4.5, COMP-006 §4.7
SIS reference: DOC-SIS-2026-001 §3.10
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 3
Priority: High
```
**Objective**: Verify DSM writes `door_status_msg_t` to shared buffer; TCI reads and
includes in CAN 0x201 transmission; CRC-16-CCITT correct.

**Test Steps**:
1. Set door 0 to DOOR_CLOSED_AND_LOCKED via DSM; execute DSM cycle
2. Read `door_status_msg_t[0]` from shared buffer
3. Verify `door_state = DOOR_CLOSED_AND_LOCKED`, `lock_state = 1`
4. Verify CRC-16-CCITT is correct over bytes 0–6
5. Execute TCI cycle; verify CAN 0x201 frame contains door state = CLOSED_AND_LOCKED

**Pass/Fail Criteria**:
- PASS: door_status_msg_t fields correct; CRC valid; CAN frame contains correct state
- FAIL: Wrong state, CRC error, or CAN frame mismatch

---

### 4.5 Phase 4 — FMG + SKN Full Integration (Safe State Logic)

**Objective**: Verify FMG aggregates fault flags from all components (IF-012) and SKN
responds with safe state broadcast (IF-015); departure interlock logic (IF-016); TCI
fault reporting (IF-013); DGN fault log (IF-014). Tests SF-004 (Safe State on Fault)
end-to-end.

---

**TC-INT-015: FMG fault aggregation → SKN safe state (IF-012, IF-015)**
```
Interface(s): IF-012, IF-015
SAS reference: COMP-005 (FMG) §4.6, COMP-001 (SKN) §4.2
SIS reference: DOC-SIS-2026-001 §3.13, §3.16
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 4
Priority: Critical
```
**Objective**: Verify FMG sets critical fault bits in `fault_state_bitmask` and SKN
immediately asserts `safe_state_active = 1` in the same cycle.

**Test Steps**:
1. Set `fault_state_bitmask = 0x00000000` (no faults); execute FMG + SKN cycle
2. Verify `safe_state_active = 0`
3. Set bit 0 (`FAULT_SENSOR_DISAGREE` = CRITICAL); execute FMG cycle
4. Execute SKN cycle immediately after; verify `safe_state_active = 1` within same 20 ms cycle
5. Clear bit 0; set bit 1 (`FAULT_CAN_TIMEOUT`); verify safe state triggers
6. Set bit 3 (`FAULT_WATCHDOG_NEAR_EXPIRY` = WARNING only); verify safe state NOT triggered

**Pass/Fail Criteria**:
- PASS: Critical bits → safe state same cycle; WARNING bits → no safe state
- FAIL: Critical fault without safe state, or WARNING incorrectly triggers safe state

---

**TC-INT-016: SKN safe state broadcast to all components (IF-015)**
```
Interface(s): IF-015
SAS reference: COMP-001 §4.2
SIS reference: DOC-SIS-2026-001 §3.16
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 4
Priority: Critical
```
**Objective**: Verify `safe_state_active = 1` broadcast is received and acted upon by
ALL components in the correct cycle.

**Test Steps**:
1. Assert `safe_state_active = 1` via SKN; execute one full scheduler cycle
2. Verify DSM: all door FSMs in FSM_SAFE_STATE; motor duty = 0; all locks = locked
3. Verify TCI: CAN 0x200 departure_interlock_ok = 0 transmitted
4. Verify SPM: continues monitoring (does not enter safe state itself)
5. Verify OBD: continues monitoring (does not enter safe state itself)
6. Verify FMG: logs safe state activation event via DGN

**Pass/Fail Criteria**:
- PASS: All components respond correctly; no component blocks or delays safe state response
- FAIL: Any component does not respond to safe_state_active or blocks cycle

---

**TC-INT-017: Departure interlock — all doors CLOSED_AND_LOCKED (IF-016, IF-008)**
```
Interface(s): IF-016, IF-008
SAS reference: COMP-001 §4.2, COMP-004 §4.5
SIS reference: DOC-SIS-2026-001 §3.17, §3.9
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 4
Priority: Critical
```
**Objective**: Verify SKN asserts `departure_interlock_ok = 1` only when ALL 4 doors
report DOOR_CLOSED_AND_LOCKED; verify TCI transmits on CAN 0x200.

**Test Steps**:
1. Set all 4 `door_states[d] = DOOR_CLOSED_AND_LOCKED` via DSM; `fault_state_bitmask = 0`; `speed_interlock_active = 0`
2. Execute SKN cycle; verify `departure_interlock_ok = 1`
3. Execute TCI cycle; verify CAN 0x200 frame byte0=1 with correct CRC
4. Set `door_states[2] = DOOR_INTERMEDIATE` (one door not locked)
5. Execute SKN cycle; verify `departure_interlock_ok = 0`
6. Set `fault_state_bitmask = 0x01` (any critical fault)
7. Execute SKN cycle; verify `departure_interlock_ok = 0`

**Pass/Fail Criteria**:
- PASS: Interlock only asserted when ALL conditions met; ANY deviation → interlock held
- FAIL: Interlock asserted with a door not in CLOSED_AND_LOCKED state

---

**TC-INT-018: FMG → TCI fault report (IF-013)**
```
Interface(s): IF-013
SAS reference: COMP-005 §4.6, COMP-006 §4.7
SIS reference: DOC-SIS-2026-001 §3.14
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 4
Priority: High
```
**Objective**: Verify FMG writes `fault_report_msg_t` to shared buffer; TCI reads and
transmits on CAN 0x202 with correct CRC; repeated transmission at 500 ms.

**Test Steps**:
1. Inject critical fault code 0x01 from FMG; execute FMG cycle
2. Read `fault_report_msg_t` from buffer; verify fault_code=1, CRC-16-CCITT correct
3. Execute TCI cycle; verify CAN 0x202 transmitted
4. Advance tick by 501 ms; execute TCI cycle; verify CAN 0x202 retransmitted
5. Clear fault (FMG); verify TCI stops retransmitting

**Pass/Fail Criteria**:
- PASS: Fault reported to CAN within one cycle; retransmitted at 500 ms; stops on clear
- FAIL: Fault not transmitted, no retransmission, or transmission after fault cleared

---

**TC-INT-019: FMG → DGN fault log entry (IF-014)**
```
Interface(s): IF-014
SAS reference: COMP-005 §4.6, COMP-007 §4.8
SIS reference: DOC-SIS-2026-001 §3.15
SIL: 3 (FMG side) / SIL 1 (DGN side)
Type: Interface (M), Functional (HR)
Integration Phase: 4
Priority: High
```
**Objective**: Verify FMG correctly writes `event_log_entry_t` to DGN interface on
fault detection; CRC-16-CCITT correct.

**Test Steps**:
1. Inject fault from SPM (CAN timeout); execute FMG cycle
2. Verify DGN receives `event_log_entry_t` with `source_comp = FMG_ID`, `event_code = FAULT_CAN_TIMEOUT`
3. Verify CRC-16-CCITT over bytes 0–7 is correct
4. Read back entry from DGN circular buffer; verify integrity

**Pass/Fail Criteria**:
- PASS: Entry written with correct fields and valid CRC; readable from DGN buffer
- FAIL: Wrong fields, CRC error, or entry not written

---

**TC-INT-020: TCI → DSM door command delivery (IF-018)**
```
Interface(s): IF-018
SAS reference: COMP-006 §4.7, COMP-004 §4.5
SIS reference: DOC-SIS-2026-001 §3.19
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 4
Priority: Critical
```
**Objective**: Verify TCI correctly places door commands from TCMS CAN into the shared
`door_command_t` buffer; DSM processes commands subject to speed and safe state gates.

**Test Steps**:
1. Inject CAN 0x101 (door open, door_mask=0x01, seq=1, correct CRC); execute TCI ISR
2. Verify `door_command_t` buffer: command_type=OPEN, door_mask=0x01
3. Execute DSM cycle with `speed_interlock_active = 0`; verify door 0 transitions to FSM_OPENING
4. Inject CAN 0x104 (emergency stop, seq=2, correct CRC); execute TCI ISR
5. Execute DSM cycle; verify ALL doors enter FSM_SAFE_STATE immediately (no speed/safe gate check for E-STOP)
6. Inject CAN 0x101 with corrupted CRC; verify TCI discards frame

**Pass/Fail Criteria**:
- PASS: Commands delivered correctly; gates applied for OPEN/CLOSE; E-STOP unconditional; CRC failure discards frame
- FAIL: E-STOP gated, OPEN accepted under interlock, or corrupted frame processed

---

### 4.6 Phase 5 — Cross-Channel 2oo2 Integration (Safety-Critical)

**Objective**: Verify the 2oo2 cross-channel comparison via SPI (IF-017). This is the
most safety-critical integration test: it exercises SF-004 and SF-005, and validates
the OI-FMEA-001 SPI transient filter algorithm.

---

**TC-INT-021: Normal cross-channel SPI exchange — data agreement (IF-017)**
```
Interface(s): IF-017
SAS reference: COMP-001 §4.2, §6.2 (Dual-channel architecture)
SIS reference: DOC-SIS-2026-001 §3.18
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 5
Priority: Critical
```
**Objective**: Verify both channels exchange `cross_channel_state_t` via SPI every
20 ms; CRC-16-CCITT (0x1021) validated; data agreement → no safe state trigger.

**Preconditions**: Two physical STM32H743 boards (Ch A master, Ch B slave) with SPI
cross-link; identical software binary; `cross_channel_state_t` pre-populated with
matching data on both channels.

**Test Steps**:
1. Execute 10 full 20 ms cycles with identical `cross_channel_state_t` on both channels
2. Verify CRC-16-CCITT (0x1021, init=0xFFFF) passes on both sides each cycle
3. Verify `safe_state_active = 0` on both channels throughout

**Pass/Fail Criteria**:
- PASS: CRC valid; data agrees; safe state not triggered over 10 cycles
- FAIL: Spurious safe state on agreeing data (false positive)

---

**TC-INT-022: Cross-channel safety-data disagreement → immediate safe state (IF-017)**
```
Interface(s): IF-017
SAS reference: COMP-001 §4.2, §6.3 (Safe state entry, OI-FMEA-001)
SIS reference: DOC-SIS-2026-001 §3.18
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 5
Priority: Critical
```
**Objective**: Verify that ANY safety-data field disagreement (speed, door state, lock
state, obstacle, safety_decisions) triggers IMMEDIATE safe state on both channels
within the same 20 ms cycle — no filter.

**Test Steps**:
1. Start with both channels in agreement; `safe_state_active = 0`
2. Corrupt `speed_kmh_x10` on Channel B by +100 (disagreement on speed field)
3. Execute one SPI exchange cycle
4. Verify `safe_state_active = 1` on BOTH channels within the same cycle (≤ 20 ms)
5. Reset; repeat with `door_states[0]` disagreement → same result
6. Reset; repeat with `safety_decisions` bit disagreement → same result

**Pass/Fail Criteria**:
- PASS: Safe state asserted on BOTH channels within same cycle for any safety-data disagreement
- FAIL: Safe state not triggered, triggered only on one channel, or delayed beyond 20 ms

---

**TC-INT-023: SPI infrastructure fault — transient filter (3-cycle confirmation) (IF-017)**
```
Interface(s): IF-017
SAS reference: COMP-001 §4.2 (OI-FMEA-001 resolution)
SIS reference: DOC-SIS-2026-001 §3.18 (Disagreement Handling)
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 5
Priority: Critical
```
**Objective**: Verify that SPI infrastructure faults (CRC of the SPI frame, bus timeout,
HW error) do NOT trigger immediate safe state; safe state only after 3 consecutive
infrastructure fault cycles (OI-FMEA-001 SPI transient filter).

**Test Steps**:
1. Inject SPI frame CRC error on Channel A (bit-flip in received CRC field)
2. Execute cycle 1: verify `spi_infra_fault_count = 1`; `safe_state_active = 0`
3. Inject SPI CRC error cycle 2: verify `spi_infra_fault_count = 2`; `safe_state_active = 0`
4. Inject SPI CRC error cycle 3: verify `spi_infra_fault_count = 3`; `safe_state_active = 1`
5. Reset; inject 2 consecutive SPI errors then one successful exchange
6. Verify `spi_infra_fault_count` resets to 0 on successful exchange; safe state NOT triggered

**Pass/Fail Criteria**:
- PASS: Safe state only after 3 consecutive infrastructure faults; resets on success
- FAIL: Safe state on first/second infrastructure fault (too sensitive), or never (filter broken)

---

**TC-INT-024: SPI timeout → safe state via 3-cycle filter (IF-017)**
```
Interface(s): IF-017, IF-019 (watchdog status)
SAS reference: COMP-001 §4.2, §6.3
SIS reference: DOC-SIS-2026-001 §3.18, §3.20
SIL: 3
Type: Interface (M), Error
Integration Phase: 5
Priority: Critical
```
**Objective**: Verify SPI bus timeout (>5 ms) is treated as infrastructure fault and
subject to 3-cycle filter per OI-FMEA-001.

**Test Steps**:
1. Simulate SPI timeout by not responding on Channel B for 3 consecutive cycles (>5 ms each)
2. Verify `spi_infra_fault_count` increments each cycle
3. After 3rd timeout: verify `safe_state_active = 1` on Channel A
4. Restore SPI communication; verify system requires maintenance reset to clear safe state

**Pass/Fail Criteria**:
- PASS: 3 consecutive SPI timeouts → safe state; single timeout → no safe state
- FAIL: Single timeout triggers safe state, or 3 consecutive timeouts do not

---

**TC-INT-025: HAL watchdog status → SKN warning (IF-019)**
```
Interface(s): IF-019
SAS reference: COMP-008 §4.9, COMP-001 §4.2
SIS reference: DOC-SIS-2026-001 §3.20
SIL: 3
Type: Interface (M), Functional (HR)
Integration Phase: 5
Priority: High
```
**Objective**: Verify HAL sets `watchdog_status = 1` when watchdog refresh exceeds
40 ms; SKN reads and logs `FAULT_WATCHDOG_NEAR_EXPIRY` (WARNING, not critical).

**Test Steps**:
1. Normal operation: watchdog refreshed every 20 ms; verify `watchdog_status = 0`
2. Simulate delay: hold refresh for 41 ms; HAL sets `watchdog_status = 1`
3. Execute SKN cycle; verify `FAULT_WATCHDOG_NEAR_EXPIRY` bit 3 set in fault bitmask
4. Verify `safe_state_active` NOT triggered by watchdog WARNING alone
5. Simulate actual watchdog expiry (> 50 ms no refresh): hardware reset — verify system
   restarts with `safe_state_active = 1` (cold-start default)

**Pass/Fail Criteria**:
- PASS: Warning logged at 41 ms; no safe state from WARNING; hardware reset at 50 ms+
- FAIL: Safe state triggered by WARNING, or WARNING not detected

---

### 4.7 Performance Integration Tests (HR SIL 3)

**EN 50128 Table A.6 Item 4: Performance Testing — Highly Recommended at SIL 3**

---

**TC-INT-PERF-001: Full scheduler cycle WCET (20 ms budget)**
```
Interface(s): IF-001..IF-020 (all)
SAS reference: SAS §3.1 (execution model), §9.3 REQ-PERF-001
SIS reference: DOC-SIS-2026-001 all
SIL: 3
Type: Performance (HR)
Integration Phase: 5
Priority: Critical
```
**Objective**: Verify the complete 20 ms scheduler cycle WCET ≤ 16 ms with all
8 components executing in order (SAS §3.1 execution steps 1–11).

**Test Steps**:
1. Configure all 4 doors in FSM_CLOSING state (worst-case scenario)
2. Inject active obstacle, active CAN messages, and SPI exchange
3. Execute one full cycle; measure wall-clock execution time via DWT cycle counter
4. Repeat 1000 cycles; record maximum observed time
5. Compute WCET; verify ≤ 16 ms (REQ-PERF-001)

**Pass/Fail Criteria**:
- PASS: WCET ≤ 16 ms over 1000 cycles
- FAIL: Any cycle exceeds 16 ms

---

**TC-INT-PERF-002: Speed interlock response latency ≤ 100 ms (IF-001, IF-002, IF-003)**
```
Interface(s): IF-001, IF-002, IF-003
SAS reference: §9.3 REQ-PERF-002
SIS reference: DOC-SIS-2026-001 §3.2, §3.3
SIL: 3
Type: Performance (HR)
Integration Phase: 5
Priority: Critical
```
**Objective**: Verify speed interlock activation (CAN frame injection → DSM gate applied)
occurs within ≤ 100 ms (5 × 20 ms cycles).

**Test Steps**:
1. Train stopped (speed=0); verify `speed_interlock_active = 0`
2. Inject CAN 0x100 with speed=600 (60 km/h); timestamp T0
3. Execute scheduler cycles until `speed_interlock_active = 1` observed at DSM
4. Record T1 (cycle when interlock observed at DSM gate)
5. Compute T1 - T0; verify ≤ 100 ms

**Pass/Fail Criteria**:
- PASS: Speed interlock propagates to DSM gate within 100 ms
- FAIL: Propagation > 100 ms

---

**TC-INT-PERF-003: Obstacle reversal latency ≤ 150 ms (IF-005, IF-006, IF-011)**
```
Interface(s): IF-005, IF-006, IF-011
SAS reference: §9.3 REQ-PERF-003
SIS reference: DOC-SIS-2026-001 §3.6, §3.7, §3.12
SIL: 3
Type: Performance (HR)
Integration Phase: 5
Priority: Critical
```
**Objective**: Verify obstacle detection to motor stop (reversal) latency ≤ 150 ms.

**Test Steps**:
1. Place door 0 in FSM_CLOSING state
2. Simulate obstacle ISR at T0 (call `OBD_ObstacleISR(0)`)
3. Execute scheduler cycle
4. Measure T1 = time when `motor_duty[0] = 0` confirmed at HAL
5. T1 - T0 ≤ 150 ms (SAS §4.4 specifies ≤ 100 ms SW + 50 ms HW margin)

**Pass/Fail Criteria**:
- PASS: motor_duty[0]=0 within 150 ms of ISR trigger
- FAIL: Motor not stopped within 150 ms

---

**TC-INT-PERF-004: TCMS departure interlock reporting ≤ 100 ms (IF-016)**
```
Interface(s): IF-016, IF-008
SAS reference: §9.3 REQ-PERF-005
SIS reference: DOC-SIS-2026-001 §3.17
SIL: 3
Type: Performance (HR)
Integration Phase: 5
Priority: High
```
**Objective**: Verify that after all 4 doors reach CLOSED_AND_LOCKED state, the
departure_interlock_ok = 1 is transmitted on CAN 0x200 within ≤ 100 ms.

**Test Steps**:
1. Set all doors to DOOR_CLOSED_AND_LOCKED; timestamp T0
2. Execute scheduler cycles; monitor CAN 0x200 for departure_interlock_ok = 1
3. Record T1 when CAN 0x200 with departure_interlock_ok=1 transmitted
4. Verify T1 - T0 ≤ 100 ms

**Pass/Fail Criteria**:
- PASS: Departure interlock transmitted within 100 ms
- FAIL: Latency > 100 ms

---

### 4.8 Error Propagation and Fault Integration Tests

---

**TC-INT-ERR-001: NULL pointer from HAL to DSM (IF-004)**
```
Interface(s): IF-004
SAS reference: COMP-004 §4.5 (Key constraints: DSM/array-oob)
SIS reference: DOC-SIS-2026-001 §3.5
SIL: 3
Type: Error
Integration Phase: 3
Priority: High
```
**Objective**: Verify DSM handles `HAL_GPIO_ReadPositionSensor` returning ERR_NULL_PTR
by substituting fail-safe sensor value (0 = not activated).

**Test Steps**:
1. Configure HAL stub to return ERR_NULL_PTR for door 0 position sensor A
2. Execute DSM cycle
3. Verify DSM uses fail-safe value (0) for sensor A
4. Verify FMG receives error notification
5. Verify DSM does not access null pointer; no crash

**Pass/Fail Criteria**:
- PASS: Fail-safe substitution applied; FMG notified; no crash
- FAIL: Null dereference, crash, or error silently ignored

---

**TC-INT-ERR-002: CRC-16 computation consistency across all safety structures**
```
Interface(s): IF-001, IF-009, IF-013, IF-016, IF-017
SAS reference: §5.3 (CRC-16 Protection Scope — OI-FTA-003)
SIS reference: DOC-SIS-2026-001 §1.4 (CRC-16-CCITT 0x1021)
SIL: 3
Type: Error, Functional (HR)
Integration Phase: 5
Priority: Critical
```
**Objective**: Verify ALL safety-critical data structures use CRC-16-CCITT polynomial
0x1021 (initial value 0xFFFF, no final XOR) — OI-FTA-003 compliance check.

**Test Steps**:
1. Compute reference CRC-16-CCITT (0x1021) for known test vector `[0x01, 0x02, 0x03]` = 0x6131
2. Call CRC computation for `tcms_speed_msg_t` — verify uses 0x1021
3. Call CRC computation for `cross_channel_state_t` — verify uses 0x1021
4. Call CRC computation for `door_status_msg_t` — verify uses 0x1021
5. Call CRC computation for `fault_report_msg_t` — verify uses 0x1021
6. Call CRC computation for `event_log_entry_t` — verify uses 0x1021
7. Attempt to use polynomial 0x8005 — verify it is either absent or returns error

**Pass/Fail Criteria**:
- PASS: All structures use 0x1021 exclusively; reference vector matches; 0x8005 absent
- FAIL: Any structure uses 0x8005 or any other polynomial

---

**TC-INT-ERR-003: Door index bounds check across all components**
```
Interface(s): IF-004, IF-005, IF-006, IF-010, IF-011
SAS reference: COMP-004 §4.5 (SEEA: DSM/array-oob)
SIS reference: DOC-SIS-2026-001 §3.5, §3.6, §3.11
SIL: 3
Type: Error
Integration Phase: 3
Priority: High
```
**Objective**: Verify all components performing `door_id`-indexed array access validate
`0 ≤ door_id < MAX_DOORS` before access.

**Test Steps**:
1. Call `HAL_GPIO_SetLockActuator(255, 1)` (invalid door_id = 255)
2. Verify return = ERR_RANGE; no array out-of-bounds access
3. Call `HAL_PWM_SetDutyCycle(4, 50)` (door_id = 4 = MAX_DOORS)
4. Verify return = ERR_RANGE
5. Verify DSM, OBD, and FMG each perform same bound check before any array index

**Pass/Fail Criteria**:
- PASS: ERR_RANGE returned for all out-of-bounds door_id values; no buffer overrun
- FAIL: Out-of-bounds access proceeds, or no bounds checking present

---

**TC-INT-ERR-004: FMG initialization — fault counter at startup**
```
Interface(s): IF-012, IF-015
SAS reference: COMP-005 §4.6 (SEEA: FMG/uninitialized-counter)
SIS reference: DOC-SIS-2026-001 §3.13
SIL: 3
Type: Error
Integration Phase: 4
Priority: High
```
**Objective**: Verify FMG fault counter initialised to 0 at startup; `safe_state_active`
initialised to 1 (fail-safe cold start); cleared only after successful BIT.

**Test Steps**:
1. Cold start: verify `fault_state_bitmask = 0x00000001` (FAULT_SENSOR_DISAGREE set — cold start default)
2. Verify `safe_state_active = 1` at cold start (fail-safe default)
3. Complete FMG BIT; verify `fault_state_bitmask` cleared to 0x00000000
4. Verify `safe_state_active` cleared only after full BIT pass
5. Simulate power cycle; repeat steps 1–4

**Pass/Fail Criteria**:
- PASS: Cold start in safe state; BIT clears faults; normal operation starts after BIT
- FAIL: Cold start with `safe_state_active = 0` (unsafe initialization)

---

## 5. TRACEABILITY MATRIX

### 5.1 Interface Coverage (Mandatory SIL 3 — Table A.6 Item 3)

Every internal interface IF-001 through IF-020 SHALL be covered by at least one test case.
SIL 3 requires 100% interface coverage (Mandatory).

| Interface ID | Description | Test Case(s) | Coverage |
|---|---|---|---|
| IF-001 | TCI → SPM: TCMS speed message | TC-INT-003, TC-INT-004, TC-INT-005, TC-INT-008 | ✓ |
| IF-002 | SPM → SKN: speed interlock gate | TC-INT-005, TC-INT-006, TC-INT-PERF-002 | ✓ |
| IF-003 | SPM → DSM: speed gate | TC-INT-007, TC-INT-020 | ✓ |
| IF-004 | HAL GPIO → DSM: position/lock sensors | TC-INT-009, TC-INT-ERR-001, TC-INT-ERR-003 | ✓ |
| IF-005 | HAL GPIO → OBD: obstacle sensors | TC-INT-010, TC-INT-PERF-003, TC-INT-ERR-003 | ✓ |
| IF-006 | OBD → DSM: obstacle flags | TC-INT-010, TC-INT-PERF-003 | ✓ |
| IF-007 | OBD → SKN: obstacle for safety arbitration | TC-INT-011 | ✓ |
| IF-008 | DSM → SKN: door/lock states | TC-INT-017, TC-INT-PERF-004 | ✓ |
| IF-009 | DSM → TCI: per-door status | TC-INT-014 | ✓ |
| IF-010 | DSM → HAL: lock actuator | TC-INT-012, TC-INT-ERR-003 | ✓ |
| IF-011 | DSM → HAL: motor PWM | TC-INT-013, TC-INT-PERF-003, TC-INT-ERR-003 | ✓ |
| IF-012 | FMG → SKN: fault state bitmask | TC-INT-015, TC-INT-ERR-004 | ✓ |
| IF-013 | FMG → TCI: fault report | TC-INT-018 | ✓ |
| IF-014 | FMG → DGN: event log entry | TC-INT-019 | ✓ |
| IF-015 | SKN → all: safe state broadcast | TC-INT-016, TC-INT-015 | ✓ |
| IF-016 | SKN → TCI: departure interlock | TC-INT-017, TC-INT-PERF-004 | ✓ |
| IF-017 | SKN Ch A ↔ Ch B: SPI cross-channel | TC-INT-021, TC-INT-022, TC-INT-023, TC-INT-024 | ✓ |
| IF-018 | TCI → DSM: door commands | TC-INT-020 | ✓ |
| IF-019 | HAL → SKN: watchdog status | TC-INT-025 | ✓ |
| IF-020 | DGN → SPI Flash: event log buffer | TC-INT-001, TC-INT-002 | ✓ |

**Coverage Statistics**:
- Total interfaces: 20 (IF-001 through IF-020)
- Interfaces with test cases: **20 / 20**
- Coverage: **100%** ✓ (Mandatory SIL 3 requirement met)

### 5.2 Safety Function → Test Case Traceability

| Safety Function | SF-ID | Primary Test Cases |
|---|---|---|
| Speed Interlock (inhibit open when moving) | SF-001 | TC-INT-005, TC-INT-006, TC-INT-007, TC-INT-PERF-002 |
| Departure Interlock (all doors locked) | SF-002 | TC-INT-017, TC-INT-PERF-004 |
| Obstacle Detection and Reversal | SF-003 | TC-INT-010, TC-INT-011, TC-INT-PERF-003 |
| Safe State on Critical Fault | SF-004 | TC-INT-015, TC-INT-016, TC-INT-022 |
| Door Position Verification (2oo2) | SF-005 | TC-INT-009, TC-INT-021, TC-INT-022 |

### 5.3 SRS Requirements → Test Case Traceability

| Requirement | Description | Test Case(s) |
|---|---|---|
| REQ-SAFE-001 | Speed interlock inhibit | TC-INT-005, TC-INT-006, TC-INT-007 |
| REQ-SAFE-002 | 2oo2 cross-channel speed | TC-INT-021, TC-INT-022 |
| REQ-SAFE-003 | CAN timeout → assume moving | TC-INT-005 |
| REQ-SAFE-004 | Obstacle detection ≤ 20 ms | TC-INT-010, TC-INT-PERF-003 |
| REQ-SAFE-006 | Motor current → reversal | TC-INT-010 |
| REQ-SAFE-007 | 2oo2 sensor for lock | TC-INT-009 |
| REQ-SAFE-008 | All-doors-locked for interlock | TC-INT-017 |
| REQ-SAFE-009 | Cross-channel lock verification | TC-INT-021, TC-INT-022 |
| REQ-SAFE-010 | CRC-16 on all safety data | TC-INT-ERR-002 |
| REQ-SAFE-012 | Safe state trigger | TC-INT-015, TC-INT-016 |
| REQ-SAFE-014 | Hardware watchdog | TC-INT-025 |
| REQ-SAFE-015 | Cross-channel SW watchdog | TC-INT-024 |
| REQ-SAFE-016 | CRC-16 on CAN; reject on fail | TC-INT-004, TC-INT-008 |
| REQ-SAFE-018 | Memory integrity check | TC-INT-ERR-004 |
| REQ-PERF-001 | WCET ≤ 16 ms | TC-INT-PERF-001 |
| REQ-PERF-002 | Speed interlock ≤ 100 ms | TC-INT-PERF-002 |
| REQ-PERF-003 | Obstacle reversal ≤ 150 ms | TC-INT-PERF-003 |
| REQ-PERF-005 | TCMS locked status ≤ 100 ms | TC-INT-PERF-004 |

---

## 6. INTEGRATION TEST PROCEDURES

### 6.1 Phase 1: HAL + DGN Integration

**Entry Criteria**:
- [ ] HAL component unit tested and passed (Component Test Report approved)
- [ ] DGN component unit tested and passed
- [ ] HW/SW integration Phase 1 (HAL ↔ hardware) complete — Item 13 Phase 1
- [ ] Integration build successful (no compile or link errors)
- [ ] SPI Flash hardware available and functional

**Test Cases**: TC-INT-001, TC-INT-002

**Exit Criteria**:
- [ ] TC-INT-001 PASSED: DGN write/read circular buffer verified
- [ ] TC-INT-002 PASSED: DGN non-interference with safety state verified
- [ ] No critical or high-severity defects open

### 6.2 Phase 2: TCI + SPM Integration (Speed Interlock Chain)

**Entry Criteria**:
- [ ] Phase 1 exit criteria met
- [ ] TCI and SPM components unit tested and passed
- [ ] CAN bus stub (`stub_can_bus.c`) reviewed and available
- [ ] SKN stub (`stub_skn.c`) reviewed and available
- [ ] DSM stub (`stub_dsm.c`) reviewed and available

**Test Cases**: TC-INT-003, TC-INT-004, TC-INT-005, TC-INT-006, TC-INT-007, TC-INT-008

**Exit Criteria**:
- [ ] TC-INT-003 PASSED: Normal speed delivery verified
- [ ] TC-INT-004 PASSED: CRC fail → fail-safe retention verified
- [ ] TC-INT-005 PASSED: CAN timeout → interlock activation verified
- [ ] TC-INT-006 PASSED: Speed gate propagation to SKN verified
- [ ] TC-INT-007 PASSED: Speed gate to DSM verified
- [ ] TC-INT-008 PASSED: Sequence counter validation verified
- [ ] No critical defects open

### 6.3 Phase 3: OBD + DSM Integration

**Entry Criteria**:
- [ ] Phase 2 exit criteria met
- [ ] OBD and DSM components unit tested and passed
- [ ] Sensor injection driver (`driver_sensor_inject.c`) reviewed and available
- [ ] HW/SW Phase 2 (HAL ↔ GPIO sensors) complete

**Test Cases**: TC-INT-009, TC-INT-010, TC-INT-011, TC-INT-012, TC-INT-013, TC-INT-014, TC-INT-ERR-001, TC-INT-ERR-003

**Exit Criteria**:
- [ ] TC-INT-009 through TC-INT-014 PASSED
- [ ] TC-INT-ERR-001, TC-INT-ERR-003 PASSED
- [ ] No critical defects open

### 6.4 Phase 4: FMG + SKN Full Integration

**Entry Criteria**:
- [ ] Phase 3 exit criteria met
- [ ] FMG and SKN components unit tested and passed
- [ ] All stubs from Phase 2–3 replaced with real components (no stubs for FMG, SKN)

**Test Cases**: TC-INT-015, TC-INT-016, TC-INT-017, TC-INT-018, TC-INT-019, TC-INT-020, TC-INT-ERR-002, TC-INT-ERR-004

**Exit Criteria**:
- [ ] TC-INT-015 through TC-INT-020 PASSED
- [ ] TC-INT-ERR-002, TC-INT-ERR-004 PASSED
- [ ] No critical defects open

### 6.5 Phase 5: Cross-Channel 2oo2 + Complete Integration

**Entry Criteria**:
- [ ] Phase 4 exit criteria met
- [ ] Two physical DCU boards available (Ch A and Ch B)
- [ ] SPI cross-link wired and verified functional
- [ ] Logic analyser ready on SPI bus

**Test Cases**: TC-INT-021, TC-INT-022, TC-INT-023, TC-INT-024, TC-INT-025, TC-INT-PERF-001 through TC-INT-PERF-004

**Regression Test Suites**: Execute ALL Phase 1–4 test cases as regression

**Exit Criteria**:
- [ ] TC-INT-021 through TC-INT-025 PASSED (cross-channel 2oo2)
- [ ] TC-INT-PERF-001 through TC-INT-PERF-004 PASSED (performance)
- [ ] All Phase 1–4 regression tests PASSED
- [ ] 100% interface coverage verified (§5.1)
- [ ] Branch coverage ≥ target (see §7.2)
- [ ] No critical or high-severity defects open

---

## 7. TEST ENTRY AND EXIT CRITERIA (OVERALL)

### 7.1 Overall Entry Criteria

**Entry Criteria for SW Integration Testing (Phase 6)**:
- [ ] All 8 software components unit tested and Component Test Reports approved (Annex C Item 19)
- [ ] Software Architecture Specification (SAS, Item 9) approved: DOC-SAS-2026-001 v0.2+
- [ ] Software Design Specification (SDS, Item 10) approved: DOC-SDS-2026-001 v0.1+
- [ ] Software Interface Specifications (SIS, Item 11) approved: DOC-SIS-2026-001 v0.1+
- [ ] This Integration Test Specification (Item 12) reviewed by VER and QUA
- [ ] HW/SW Integration Phase 1 complete (Item 13 HAL integration passed)
- [ ] Integration test environment configured and validated
- [ ] All stubs and drivers reviewed and placed under CM control
- [ ] Traceability matrix (§5.1) verified — 20/20 interfaces covered

### 7.2 Overall Exit Criteria

**Exit Criteria for SW Integration Testing**:
- [ ] All 29 SW integration test cases executed (TC-INT-001 through TC-INT-ERR-004)
- [ ] All Phase 5 cross-channel tests passed (TC-INT-021 through TC-INT-025) — CRITICAL
- [ ] All performance tests passed (TC-INT-PERF-001 through TC-INT-PERF-004) — CRITICAL
- [ ] 100% interface coverage (20/20 interfaces): verified in §5.1
- [ ] Branch coverage ≥ 80% (as specified in SQAP DOC-SQAP-2026-001) — measured by TST
- [ ] No critical or high-severity defects open
- [ ] SW Integration Test Report (Item 21) completed by INT with TST-provided results
- [ ] VER approval of Integration Test Report (independent, SIL 3 mandatory)
- [ ] All components identified with version and git commit SHA in the test report

---

## 8. DEFECT MANAGEMENT

### 8.1 Defect Classification

| Severity | Definition | Action |
|----------|------------|--------|
| **Critical** | Safety gate failure; safe state not triggered when required; interface test fails on safety-critical data path | Immediate fix; re-test before next phase |
| **High** | Interface data incorrect; performance requirement exceeded; error not detected | Fix before next integration phase |
| **Medium** | Non-safety interface mismatch; workaround available | Fix before Phase 5 |
| **Low** | Cosmetic or diagnostic path issue | Fix before Integration Test Report |

### 8.2 Defect Escalation

All defects discovered during integration testing are reported to PM. PM routes to:
- IMP for fixes to component code
- DES for architectural issues
- QUA/VER through PM (INT does not contact directly)

---

## 9. RISKS AND MITIGATION

| Risk | Probability | Impact | Mitigation |
|------|-------------|--------|------------|
| SPI cross-channel hardware not available for Phase 5 | Medium | High | Simulate SPI via shared memory for host-based testing; validate timing on actual hardware |
| Stub behaviour diverges from real component | Medium | High | VER review of all stubs before integration; regression testing when stub replaced by real component |
| CRC-16 polynomial inconsistency (OI-FTA-003) | Low | Critical | TC-INT-ERR-002 explicitly tests all structures; mandatory pass before Phase 5 |
| Performance tests fail (WCET > 16 ms) | Low | Critical | TC-INT-PERF-001 run on actual STM32H743 target; optimisation cycle with DES/IMP if exceeded |
| SPI transient filter regression | Low | Critical | TC-INT-023 explicitly tests 3-cycle filter; OI-FMEA-001 compliance verified |

---

## 10. CONFIGURATION MANAGEMENT

**Document Version Control**:
- Document: DOC-SITSPEC-2026-001 v0.1
- Repository: git (project repository)
- Baseline: Phase 3 architecture baseline

**Software Components Under Integration** (to be verified at Phase 6):
- Components: COMP-001 through COMP-008 (versions to be recorded at Phase 6 test start)
- All git commit SHAs shall be recorded in the SW Integration Test Report (Item 21)

---

## 11. ROLES AND RESPONSIBILITIES

| Role | Responsibilities |
|------|-----------------|
| **Integrator (INT)** | Owns this specification (Item 12); authors SW Integration Test Report (Item 21) from TST results |
| **Tester (TST)** | Executes integration tests in Phase 6; returns machine-readable results (XML/JSON) to PM |
| **Verifier (VER)** | Reviews this specification; reviews Test Report; owns Item 23 (Integration Verification Report) |
| **Quality Assurance (QUA)** | Verifies process compliance and template compliance |
| **Project Manager (PM)** | Routes deliverables; INT submits all items to PM |
| **Implementer (IMP)** | Provides fixes for integration defects discovered in Phase 6 |

**SIL 3 Independence Note**: VER shall be independent from INT and the development team.

---

## 12. REFERENCES

### 12.1 Normative References

- **EN 50128:2011** — Railway applications — Software for railway control and protection systems (§5.3.6, §7.6, Table A.6)
- **EN 50126:2017** — Railway applications — RAMS
- **MISRA C:2012** — Guidelines for the use of the C language in critical systems

### 12.2 Project References

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-SAS-2026-001 | Software Architecture Specification | 0.2 DRAFT |
| DOC-SDS-2026-001 | Software Design Specification | 0.1 DRAFT |
| DOC-SIS-2026-001 | Software Interface Specifications | 0.1 DRAFT |
| DOC-SRS-2026-001 | Software Requirements Specification | 0.1 DRAFT |
| DOC-SQAP-2026-001 | Software Quality Assurance Plan | — |
| DOC-SCMP-2026-001 | Software Configuration Management Plan | — |
| DOC-SVP-2026-001 | Software Verification Plan | — |

---

## APPENDIX A: TEST CASE SUMMARY TABLE

| TC ID | Phase | Interface(s) | Type | Priority | Safety Function |
|-------|-------|-------------|------|----------|----------------|
| TC-INT-001 | 1 | IF-020 | Interface, Functional | High | — (SIL 1) |
| TC-INT-002 | 1 | IF-020, IF-015 | Interface, Functional | Critical | SF-004 |
| TC-INT-003 | 2 | IF-001 | Interface, Functional | Critical | SF-001 |
| TC-INT-004 | 2 | IF-001 | Interface, Error | Critical | SF-001 |
| TC-INT-005 | 2 | IF-001, IF-002 | Interface, Functional | Critical | SF-001 |
| TC-INT-006 | 2 | IF-002 | Interface, Functional | Critical | SF-001 |
| TC-INT-007 | 2 | IF-003 | Interface, Functional | Critical | SF-001 |
| TC-INT-008 | 2 | IF-001 | Interface, Error | High | SF-001 |
| TC-INT-009 | 3 | IF-004 | Interface, Functional | Critical | SF-005 |
| TC-INT-010 | 3 | IF-005, IF-006 | Interface, Functional | Critical | SF-003 |
| TC-INT-011 | 3 | IF-007 | Interface, Functional | Critical | SF-003 |
| TC-INT-012 | 3 | IF-010 | Interface, Functional | Critical | SF-002, SF-005 |
| TC-INT-013 | 3 | IF-011 | Interface, Functional | Critical | SF-003, SF-004 |
| TC-INT-014 | 3 | IF-009 | Interface, Functional | High | SF-002 |
| TC-INT-015 | 4 | IF-012, IF-015 | Interface, Functional | Critical | SF-004 |
| TC-INT-016 | 4 | IF-015 | Interface, Functional | Critical | SF-004 |
| TC-INT-017 | 4 | IF-016, IF-008 | Interface, Functional | Critical | SF-002 |
| TC-INT-018 | 4 | IF-013 | Interface, Functional | High | SF-004 |
| TC-INT-019 | 4 | IF-014 | Interface, Functional | High | — |
| TC-INT-020 | 4 | IF-018 | Interface, Functional | Critical | SF-001, SF-003 |
| TC-INT-021 | 5 | IF-017 | Interface, Functional | Critical | SF-004, SF-005 |
| TC-INT-022 | 5 | IF-017 | Interface, Functional | Critical | SF-004 |
| TC-INT-023 | 5 | IF-017 | Interface, Functional | Critical | SF-004 |
| TC-INT-024 | 5 | IF-017, IF-019 | Interface, Error | Critical | SF-004 |
| TC-INT-025 | 5 | IF-019 | Interface, Functional | High | SF-004 |
| TC-INT-PERF-001 | 5 | ALL | Performance | Critical | All |
| TC-INT-PERF-002 | 5 | IF-001..IF-003 | Performance | Critical | SF-001 |
| TC-INT-PERF-003 | 5 | IF-005..IF-006, IF-011 | Performance | Critical | SF-003 |
| TC-INT-PERF-004 | 5 | IF-016, IF-008 | Performance | High | SF-002 |
| TC-INT-ERR-001 | 3 | IF-004 | Error | High | SF-005 |
| TC-INT-ERR-002 | 5 | IF-001,IF-009,IF-013,IF-016,IF-017 | Error, Functional | Critical | All |
| TC-INT-ERR-003 | 3 | IF-004..IF-006,IF-010,IF-011 | Error | High | All |
| TC-INT-ERR-004 | 4 | IF-012, IF-015 | Error | High | SF-004 |

**Total test cases defined: 33**
**Total interfaces covered: 20 / 20 (100%)**
**Total traceability links: ≥ 65** (interface → test case; test case → SF; test case → REQ)

---

**END OF DOCUMENT**

*Submitted to PM for routing to QUA and VER per EN 50128 §5.3.6 and WORKFLOW.md.*
