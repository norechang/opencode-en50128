# Overall Software Test Specification (OSTS)

**TEMPLATE VERSION**: 2.0
**REFERENCE**: EN 50128:2011 Sections 7.7, 6.1.4.4, Table A.5, Table A.7, Table A.21

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-OTSTSPEC-2026-001 |
| **Version** | 0.1 DRAFT |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Software Tester (TST) |
| **Status** | Draft |

### Revision History

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-04-02 | Software Tester (TST) | Initial draft — Phase 2 OSTS from SRS DOC-SRS-2026-001 | — |

## APPROVALS

**EN 50128 Annex C Table C.1 Signature Chain — Item 7 (Overall Software Test Specification)**

| Column | Role | Name | Signature | Date |
|--------|------|------|-----------|------|
| Written By | Software Tester (TST) | [Name] | _____________ | 2026-04-02 |
| 1st Check | Software Verifier (VER) | [Name] | _____________ | __________ |
| 2nd Check | Software Validator (VAL) | [Name] | _____________ | __________ |

**Notes:**
- **Written By**: TST — Author responsible for document content (EN 50128 Annex C Table C.1 Column 2, Item 7)
- **1st Check**: VER — First independent reviewer (EN 50128 Annex C Table C.1 Column 3)
- **2nd Check**: VAL — Second independent reviewer (EN 50128 Annex C Table C.1 Column 4)
- Roles per `activities/deliverables.yaml` item 7: `written_by: tst`, `first_check: ver`, `second_check: val`
- SIL 3: Independence requirements apply per EN 50128 §6.2 (Verification) and §6.3 (Validation)
- TST is independent from IMP (highly recommended for SIL 3 per ORGANIZATION.md)
- Signature authority per project SQAP (DOC-SQAP-2026-001) and DELIVERABLES.md

---

## 1. Introduction

### 1.1 Purpose

This document is the **Overall Software Test Specification (OSTS)** for the **Train Door Control System (TDC)** software. It is Annex C Item 7 in the EN 50128:2011 deliverable catalogue and is authored by the Software Tester (TST) in Phase 2 of the V-Model lifecycle.

**Objectives**:
- Define the system-level test strategy for validating the complete TDC software against all 81 requirements in the Software Requirements Specification (DOC-SRS-2026-001)
- Specify test cases for functional validation, performance verification, safety-critical paths, and operational scenarios
- Establish acceptance criteria for software release at Phase 7 (Overall Software Testing / Validation)
- Ensure bidirectional traceability between all software requirements and test cases
- Apply all mandatory Table A.5 and Table A.7 techniques for SIL 3

**Relationship to lifecycle**: This OSTS is the V-Model left-side counterpart to the Overall Software Test Report (Annex C Item 24), which is produced in Phase 7. The test cases specified here SHALL be executed during Phase 7 overall software testing.

### 1.2 Scope

**In Scope**:
- System-level functional testing (black-box) of all 81 SRS requirements
- Performance testing (timing, resource, WCET)
- Safety-critical path testing for all 7 safety functions (SF-001 to SF-007)
- Boundary value analysis for all safety-critical numeric parameters (M SIL 3–4)
- Fault injection testing for all safe-state trigger conditions
- Operational scenario testing (Normal, Selective Disable, Diagnostic, Safe State modes)
- Regression testing (mandatory SIL 3)
- Acceptance testing with VAL participation

**Out of Scope**:
- Software component (unit) testing — covered by Component Test Specification (Annex C Item 16)
- Software integration testing — covered by Software Integration Test Specification (Annex C Item 12)
- Hardware design testing — hardware design is out of scope per SRS Section 1.2

### 1.3 SIL Classification

**Target SIL Level**: SIL 3

The TDC software is classified SIL 3 per the System Safety Requirements Specification (DOC-SYS-SAF-2026-001). All test cases for SIL 3 requirements SHALL apply the mandatory techniques of EN 50128 Table A.5 and Table A.7.

### 1.4 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **OSTS** | Overall Software Test Specification (this document; EN 50128 Annex C Item 7) |
| **OSTR** | Overall Software Test Report (EN 50128 Annex C Item 24) |
| **SRS** | Software Requirements Specification (DOC-SRS-2026-001) |
| **SUT** | System Under Test (TDC software on DCU hardware) |
| **TC** | Test Case |
| **SVP/SQAP** | Software Verification Plan (DOC-SVP-2026-001) / Software Quality Assurance Plan (DOC-SQAP-2026-001) — define project coverage targets |
| **WCET** | Worst-Case Execution Time |
| **BVA** | Boundary Value Analysis (EN 50128 Table A.5 item 13, M at SIL 3) |
| **2oo2** | Two-out-of-two voting |
| **DCU** | Door Control Unit |
| **DDU** | Door Drive Unit |
| **TCMS** | Train Control Management System |
| **CCC** | Compound Condition Coverage (EN 50128 Table A.21 item 3 — HR at SIL 3) |
| **FI** | Fault Injection |
| **HAL** | Hardware Abstraction Layer |

### 1.5 References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications — Software for railway control and protection systems |
| **[EN50129]** | EN 50129:2018 Railway applications — Safety related electronic systems for signalling |
| **[SRS]** | Software Requirements Specification, DOC-SRS-2026-001 |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-2026-001 |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 |
| **[SVaP]** | Software Validation Plan, DOC-SVaP-2026-001 |
| **[SSRS]** | System Safety Requirements Specification, DOC-SYS-SAF-2026-001 |

---

## 2. Test Strategy

### 2.1 Test Approach

**Test Level**: System-level overall software testing (EN 50128 §7.7)

**Test Philosophy**:
- Black-box testing based on SRS requirements (EN 50128 Table A.7 Functional and Black-Box Testing — M at SIL 3)
- All 81 requirements shall have at least one corresponding test case
- Safety-critical paths (SIL 3 safety functions SF-001–SF-007) shall be tested with fault injection
- Boundary value analysis applied to all safety-critical numeric parameters (M at SIL 3 per Table A.5 item 13)
- All test results shall be produced in machine-readable format (XML or JSON) per EN 50128 §7.6.4.5b
- TST is independent from IMP as required for SIL 3 (HR per ORGANIZATION.md)

### 2.2 EN 50128 Techniques Applied

**Table A.5 Techniques (Verification and Testing) — SIL 3 obligations**:

| # | Technique | SIL 3 | Applied | Evidence Section |
|---|-----------|-------|---------|-----------------|
| 4 | Dynamic Analysis and Testing (A.13) | **M** | Yes | All test cases in Section 3 |
| 5 | Test Coverage for Code (A.21) | **M** | Yes | Section 2.4 |
| 7 | Traceability (D.58) | **M** | Yes | Section 4 (RTM) |
| 9 | Functional/Black-Box Testing (A.14) | **M** | Yes | Sections 3.2, 3.4, 3.7 |
| 10 | Performance Testing (A.18) | **M** | Yes | Section 3.3 |
| 12 | Regression Testing (D.46) | **M** | Yes | Section 3.6 |
| 13 | Boundary Value Analysis (D.7) | **M** | Yes | Section 3.5 |
| 14 | Equivalence Classes (D.20) | HR | Yes | Sections 3.2, 3.5 |
| 3 | Static Analysis (A.19) | **M** | By VER | VER owns Static Analysis Report (Item 19) |

**Table A.7 Techniques (Overall Software Testing) — SIL 3 obligations**:

| Technique | SIL 3 | Applied |
|-----------|-------|---------|
| Functional and Black-Box Testing | **M** | Yes — all functional test cases |
| Performance Testing | **M** | Yes — Section 3.3 |

### 2.3 Test Environment

**Target Hardware**:
- Platform: STM32H743 (ARM Cortex-M7, 400 MHz), dual-channel DCU
- Channel A (MCU-A) and Channel B (MCU-B) operating in 2oo2 configuration
- SPI cross-channel link (10 Mbps) between MCU-A and MCU-B
- 1 MB SRAM, 2 MB Flash per MCU; 16 MB SPI Flash (event log)

**Hardware Test Equipment**:
- CAN bus analyser (e.g., PEAK PCAN-USB Pro) for TCMS interface testing
- RS-485 bus analyser for DDU interface testing
- Oscilloscope (>=100 MHz) for PWM (20 kHz), GPIO timing, and ISR latency measurement
- Hardware fault injection harness for deliberate sensor/bus fault insertion
- Power supply with controlled power interruption capability

**Software Tools**:
- Compiler: ARM GCC 12.x (arm-none-eabi-gcc), same as production build
- Debugger: J-Link / OpenOCD
- Test harness: Unity test framework (component level); system-level test scripts (Python)
- Coverage: gcov + lcov (statement, branch); gcovr (JSON export)
- CAN injection: custom Python script via PCAN driver
- Static analysis: PC-lint Plus (VER-owned), Cppcheck, Lizard (cyclomatic complexity)
- Result format: XML (JUnit-compatible) and JSON per §7.6.4.5b

**Environmental Conditions**:
- Temperature: Operating range as per DCU hardware specification
- Power supply: 24 VDC nominal, tested at ±10% tolerance
- EMI: Per EN 50121 railway EMC requirements

### 2.4 Coverage Requirements

**Coverage Targets — EN 50128 Table A.21 (SIL 3)**:

| Coverage Type | Table A.21 | SIL 3 Obligation | Project Target |
|---------------|-----------|-----------------|----------------|
| Statement Coverage | Item 1 | **M** (Mandatory) | As defined in SVP/SQAP (DOC-SVP-2026-001) |
| Branch Coverage | Item 2 | **M** (Mandatory) | As defined in SVP/SQAP (DOC-SVP-2026-001) |
| Compound Condition Coverage | Item 3 | HR (Highly Recommended) | As defined in SVP/SQAP (DOC-SVP-2026-001) |
| Data Flow Coverage | Item 4 | HR (Highly Recommended) | As defined in SVP/SQAP (DOC-SVP-2026-001) |

> **NORMATIVE NOTE**: EN 50128:2011 Table A.21 Requirement 1 requires a quantified coverage measure to be defined per project in the SVP/SQAP. No percentage threshold is mandated by the standard itself. The project-defined targets are authoritative. "Compound Condition Coverage" is the correct EN 50128 term (Table A.21 item 3). Statement and Branch coverage are **Mandatory** at SIL 3. Compound Condition Coverage is **Highly Recommended** (not Mandatory) at SIL 3.

**Coverage Measurement**:
- Tool: gcov (instrumented build) + lcov (HTML report) + gcovr (JSON export)
- Report format: HTML coverage report + JSON summary (machine-readable per §7.6.4.5b)
- Exclusions: Boot-time startup code (CRT0) and hardware-specific HAL stubs shall be listed with justification in the OSTR

**Requirement Traceability Coverage**:
- Every SRS requirement SHALL have at least one test case (81/81 — 100%)
- Every test case SHALL trace to at least one SRS requirement
- Traceability matrix SHALL be 100% complete (see Section 4)

### 2.5 Test Entry and Exit Criteria

**Entry Criteria (before OSTS execution in Phase 7)**:
- [ ] Software integration testing (Phase 6) completed and Integration Test Report (Item 21) approved
- [ ] All critical and high-priority defects from integration testing resolved
- [ ] Software integrated on DCU target hardware
- [ ] Test environment (hardware, tools, harness) configured and validated
- [ ] This OSTS reviewed and approved by VER and VAL
- [ ] Test data and test vectors prepared and version-controlled
- [ ] Traceability matrix complete (Section 4 of this document)
- [ ] VAL acceptance criteria confirmed (VAL participates in defining acceptance test criteria)

**Exit Criteria (before Phase 7 gate approval)**:
- [ ] All 255 test cases executed (see Section 3 summary)
- [ ] All critical and high-priority test cases passed
- [ ] All critical and high defects resolved (or risk-accepted per CCB with documented justification)
- [ ] Statement and Branch coverage targets (from SVP/SQAP) met; Compound Condition Coverage measured and reported
- [ ] All SIL 3 safety function tests passed (SF-001 to SF-007)
- [ ] All performance requirements verified (WCET ≤ 16 ms, response times per SRS)
- [ ] Overall Software Test Report (Item 24) completed and submitted to PM
- [ ] VAL approval obtained (independent validator, mandatory SIL 3)

### 2.6 Test Data Management

**Test Data Sources**:
- Requirements-derived test vectors (from SRS Section 3 acceptance criteria)
- Boundary value datasets (min−1, min, min+1, max−1, max, max+1 per BVA)
- Fault injection datasets (sensor faults, CAN timeouts, CRC corruptions, power interruptions)
- Operational scenario scripts (Python / CAN injection scripts)
- Regression test baseline data (versioned with CM per SCMP DOC-SCMP-2026-001)

**Test Data Storage**:
- Location: `examples/TDC/tests/system/data/`
- Version control: Git (per SCMP DOC-SCMP-2026-001)
- Data validation: CRC-32 checksums on all test data files; validated before each test run
- Machine-readable results: XML (JUnit) + JSON stored in `examples/TDC/tests/system/results/`

---

## 3. Test Cases

### 3.1 Test Case Conventions

Each test case uses the following header format:

```
Test Case ID:   TC-OSTS-[CAT]-[NNN]
Requirement(s): [REQ-ID, ...]
SIL:            [level]
Coverage target: [Statement | Branch | Compound Condition] per SVP/SQAP (DOC-SVP-2026-001)
```

**Category codes**:
- `FUNC` — Functional test cases (Sections 3.2)
- `PERF` — Performance test cases (Section 3.3)
- `SAFE` — Safety-critical path test cases (Section 3.4)
- `BOUND` — Boundary value analysis test cases (Section 3.5)
- `FAULT` — Fault injection / robustness test cases (Section 3.6)
- `OPS` — Operational scenario test cases (Section 3.7)
- `REG` — Regression test cases (Section 3.8)
- `ACC` — Acceptance test cases (Section 3.9)

**Priority**: Critical / High / Medium / Low (matching SRS priority)

**Pass/Fail criteria**: All test cases require quantified, measurable pass/fail criteria. Subjective criteria are not acceptable at SIL 3.

---

### 3.2 Functional Test Cases

**Objective**: Validate all 18 functional requirements (REQ-FUN-001 to REQ-FUN-018) through black-box system tests.

| TC ID | Requirement(s) | Description | Priority | SIL |
|-------|---------------|-------------|----------|-----|
| TC-OSTS-FUNC-001 | REQ-FUN-001 | Door open command accepted — all 5 preconditions satisfied | Critical | 3 |
| TC-OSTS-FUNC-002 | REQ-FUN-001 | Door open command rejected — train speed > 5 km/h | Critical | 3 |
| TC-OSTS-FUNC-003 | REQ-FUN-001 | Door open command rejected — active door fault present | High | 3 |
| TC-OSTS-FUNC-004 | REQ-FUN-001 | Door open command rejected — active emergency stop flag | High | 3 |
| TC-OSTS-FUNC-005 | REQ-FUN-001 | Door open command rejected — wrong operational mode | High | 3 |
| TC-OSTS-FUNC-006 | REQ-FUN-001 | Command-to-motor-start latency ≤ 200 ms | Critical | 3 |
| TC-OSTS-FUNC-007 | REQ-FUN-002 | Door declared FULLY_OPEN — both sensors agree | High | 3 |
| TC-OSTS-FUNC-008 | REQ-FUN-002 | Door NOT declared FULLY_OPEN — single sensor only | High | 3 |
| TC-OSTS-FUNC-009 | REQ-FUN-002 | Sensor disagreement logged — FULLY_OPEN not declared | High | 3 |
| TC-OSTS-FUNC-010 | REQ-FUN-003 | Opening timeout fault raised at 4.0 s ± 100 ms | High | 2 |
| TC-OSTS-FUNC-011 | REQ-FUN-003 | Motor de-energized on opening timeout; fault logged to TCMS | High | 2 |
| TC-OSTS-FUNC-012 | REQ-FUN-004 | Door close command accepted — no obstacle, no fault | Critical | 3 |
| TC-OSTS-FUNC-013 | REQ-FUN-004 | Door close command rejected — obstacle present at command time | Critical | 3 |
| TC-OSTS-FUNC-014 | REQ-FUN-004 | Door close retry after obstacle cleared and command re-issued | High | 3 |
| TC-OSTS-FUNC-015 | REQ-FUN-005 | Door declared CLOSED_AND_LOCKED — all 4 sensors agree (2oo2) | Critical | 3 |
| TC-OSTS-FUNC-016 | REQ-FUN-005 | Fault on partial lock sensor agreement (NOT_LOCKED) | Critical | 3 |
| TC-OSTS-FUNC-017 | REQ-FUN-005 | Fault on partial position sensor agreement (NOT_CLOSED) | Critical | 3 |
| TC-OSTS-FUNC-018 | REQ-FUN-005 | Departure interlock NOT released on sensor fault | Critical | 3 |
| TC-OSTS-FUNC-019 | REQ-FUN-006 | Closing timeout fault at 10.0 s ± 100 ms (no obstacle scenario) | High | 2 |
| TC-OSTS-FUNC-020 | REQ-FUN-006 | Fault logged; TCMS alert on closing timeout | High | 2 |
| TC-OSTS-FUNC-021 | REQ-FUN-007 | Exactly 3 obstacle-induced retries permitted | Medium | 2 |
| TC-OSTS-FUNC-022 | REQ-FUN-007 | Fault raised after 3rd obstacle event; door remains open | Medium | 2 |
| TC-OSTS-FUNC-023 | REQ-FUN-008 | Lock command issued only when both position sensors report closed | Critical | 3 |
| TC-OSTS-FUNC-024 | REQ-FUN-008 | No lock command on position sensor disagreement; fault raised | Critical | 3 |
| TC-OSTS-FUNC-025 | REQ-FUN-009 | MSG_DOOR_LOCKED_ALL transmitted within 100 ms of all-doors-locked | Critical | 3 |
| TC-OSTS-FUNC-026 | REQ-FUN-009 | MSG_DOOR_LOCKED_ALL withheld when any door not CLOSED_AND_LOCKED | Critical | 3 |
| TC-OSTS-FUNC-027 | REQ-FUN-009 | MSG_DOOR_NOT_READY transmitted every 100 ms when doors not ready | High | 3 |
| TC-OSTS-FUNC-028 | REQ-FUN-010 | Lock re-commanded within one 20 ms cycle on lock-lost-while-moving | Critical | 3 |
| TC-OSTS-FUNC-029 | REQ-FUN-010 | FAULT_LOCK_LOST_WHILE_MOVING raised; TCMS alerted | Critical | 3 |
| TC-OSTS-FUNC-030 | REQ-FUN-011 | All 4 operational modes (NORMAL, SELECTIVE_DISABLE, DIAGNOSTIC, SAFE_STATE) reachable | High | 3 |
| TC-OSTS-FUNC-031 | REQ-FUN-011 | Illegal mode transitions rejected | High | 3 |
| TC-OSTS-FUNC-032 | REQ-FUN-011 | Unknown mode code treated as SAFE_STATE | High | 3 |
| TC-OSTS-FUNC-033 | REQ-FUN-011 | Mode change logged with timestamp | High | 3 |
| TC-OSTS-FUNC-034 | REQ-FUN-012 | Mode transition accepted with valid driver key authorization | High | 3 |
| TC-OSTS-FUNC-035 | REQ-FUN-012 | Mode transition accepted with valid TCMS digital command | High | 3 |
| TC-OSTS-FUNC-036 | REQ-FUN-012 | Unauthorized mode transition rejected; rejection logged | High | 3 |
| TC-OSTS-FUNC-037 | REQ-FUN-013 | Disabled door isolated; remaining doors operational in SELECTIVE_DISABLE | Medium | 2 |
| TC-OSTS-FUNC-038 | REQ-FUN-013 | Departure inhibited for platform-side disabled door | Medium | 2 |
| TC-OSTS-FUNC-039 | REQ-FUN-013 | Disablement event logged with timestamp and authorization source | Medium | 2 |
| TC-OSTS-FUNC-040 | REQ-FUN-014 | DIAGNOSTIC mode entered when speed = 0 AND authorization present | Medium | 2 |
| TC-OSTS-FUNC-041 | REQ-FUN-014 | DIAGNOSTIC mode rejected when speed > 0 km/h | Medium | 2 |
| TC-OSTS-FUNC-042 | REQ-FUN-014 | Safety interlocks verified active in DIAGNOSTIC mode | Medium | 2 |
| TC-OSTS-FUNC-043 | REQ-FUN-015 | FULLY_OPEN state declared when both open-end-stop sensors active | High | 3 |
| TC-OSTS-FUNC-044 | REQ-FUN-015 | FULLY_CLOSED state declared when both closed-end-stop sensors active | High | 3 |
| TC-OSTS-FUNC-045 | REQ-FUN-015 | INTERMEDIATE state declared when neither end-stop met | High | 3 |
| TC-OSTS-FUNC-046 | REQ-FUN-015 | UNKNOWN state declared on sensor A/B disagreement | High | 3 |
| TC-OSTS-FUNC-047 | REQ-FUN-015 | Door not commanded in UNKNOWN state; fault raised | High | 3 |
| TC-OSTS-FUNC-048 | REQ-FUN-015 | State updated every 20 ms cycle (timing verified) | High | 3 |
| TC-OSTS-FUNC-049 | REQ-FUN-016 | Door status CAN message (0x201) transmitted every 100 ms ± 10 ms | High | 2 |
| TC-OSTS-FUNC-050 | REQ-FUN-016 | CAN message content: correct position state, lock state, fault code | High | 2 |
| TC-OSTS-FUNC-051 | REQ-FUN-016 | CRC-16 valid on transmitted door_status_msg_t | High | 2 |
| TC-OSTS-FUNC-052 | REQ-FUN-017 | Position sensor fault detected within 100 ms | Critical | 3 |
| TC-OSTS-FUNC-053 | REQ-FUN-017 | Obstacle sensor fault detected within 100 ms | Critical | 3 |
| TC-OSTS-FUNC-054 | REQ-FUN-017 | Lock mechanism fault detected within 100 ms | Critical | 3 |
| TC-OSTS-FUNC-055 | REQ-FUN-017 | CAN communication fault detected within 200 ms | Critical | 3 |
| TC-OSTS-FUNC-056 | REQ-FUN-017 | Speed sensor timeout fault detected within 200 ms | Critical | 3 |
| TC-OSTS-FUNC-057 | REQ-FUN-017 | Cross-channel disagreement fault detected within 20 ms | Critical | 3 |
| TC-OSTS-FUNC-058 | REQ-FUN-017 | Watchdog failure fault detected within 50 ms | Critical | 3 |
| TC-OSTS-FUNC-059 | REQ-FUN-018 | Event log stores >= 1000 events in circular buffer | High | 1 |
| TC-OSTS-FUNC-060 | REQ-FUN-018 | CRC-16 verified on event log entry retrieval | High | 1 |
| TC-OSTS-FUNC-061 | REQ-FUN-018 | Circular buffer wraps correctly; oldest entries overwritten | High | 1 |
| TC-OSTS-FUNC-062 | REQ-FUN-018 | Event log readable via diagnostics port | Medium | 1 |

---

### 3.3 Performance Test Cases

**Objective**: Verify all 10 performance requirements (REQ-PERF-001 to REQ-PERF-010). Performance testing is **Mandatory** at SIL 3 (Table A.5 item 10, Table A.7).

| TC ID | Requirement(s) | Description | Target | Priority | SIL |
|-------|---------------|-------------|--------|----------|-----|
| TC-OSTS-PERF-001 | REQ-PERF-001 | WCET of complete control cycle on target hardware | ≤ 16 ms | Critical | 3 |
| TC-OSTS-PERF-002 | REQ-PERF-001 | Control cycle period on target hardware under worst-case load | 20 ms ± 1 ms | Critical | 3 |
| TC-OSTS-PERF-003 | REQ-PERF-002 | Speed interlock response: speed >5 km/h → lock command | ≤ 100 ms | Critical | 3 |
| TC-OSTS-PERF-004 | REQ-PERF-003 | Obstacle detection → motor reversal command | ≤ 150 ms | Critical | 3 |
| TC-OSTS-PERF-005 | REQ-PERF-004 | Door command received → first motor movement command | ≤ 200 ms | High | 3 |
| TC-OSTS-PERF-006 | REQ-PERF-005 | All-doors-locked state confirmed → CAN locked-all transmission | ≤ 100 ms | High | 3 |
| TC-OSTS-PERF-007 | REQ-PERF-006 | Sensor fault (stuck/out-of-range/2oo2 disagree) → fault flag | ≤ 100 ms | High | 3 |
| TC-OSTS-PERF-008 | REQ-PERF-007 | TCMS CAN speed signal loss → fault flag | ≤ 200 ms ± 20 ms | High | 3 |
| TC-OSTS-PERF-009 | REQ-PERF-008 | CPU utilization under worst-case operational load | ≤ 80% | Medium | 2 |
| TC-OSTS-PERF-010 | REQ-PERF-009 | SRAM usage (stack + globals + BSS) per MCU | ≤ 800 KB | High | 3 |
| TC-OSTS-PERF-011 | REQ-PERF-010 | Flash usage (code + rodata) per MCU | ≤ 1600 KB | High | 2 |
| TC-OSTS-PERF-012 | REQ-PERF-001 | WCET of each individual task (Safety Kernel, SPM, OBD, DSM, FMG) | Per task budget | High | 3 |

**Detailed test method for timing tests (TC-OSTS-PERF-001 through TC-OSTS-PERF-008)**:
- Timing measured using hardware timer instrumentation (GPIO toggle at task entry/exit) observed on oscilloscope
- Worst-case scenario: all doors in CLOSING state, obstacle on one door, CAN messages at maximum rate, cross-channel active
- Minimum 100 consecutive measurement samples; worst-case sample reported in OSTR

---

### 3.4 Safety-Critical Path Test Cases

**Objective**: Validate all safety requirements (REQ-SAFE-001 to REQ-SAFE-021), covering safety functions SF-001 to SF-007. Fault injection is required for all SIL 3 safety requirements.

| TC ID | Requirement(s) | Description | Priority | SIL |
|-------|---------------|-------------|----------|-----|
| TC-OSTS-SAFE-001 | REQ-SAFE-001 | Speed interlock: all door open commands inhibited when speed > 5 km/h (Channel A) | Critical | 3 |
| TC-OSTS-SAFE-002 | REQ-SAFE-001 | Speed interlock: all door open commands inhibited when speed > 5 km/h (Channel B) | Critical | 3 |
| TC-OSTS-SAFE-003 | REQ-SAFE-001 | Speed interlock: inhibit active when speed data absent (stale > 200 ms) | Critical | 3 |
| TC-OSTS-SAFE-004 | REQ-SAFE-001 | Speed interlock: inhibit active when speed data CRC error | Critical | 3 |
| TC-OSTS-SAFE-005 | REQ-SAFE-001 | Speed interlock: both channels evaluate independently (2oo2 cross-check) | Critical | 3 |
| TC-OSTS-SAFE-006 | REQ-SAFE-002 | Doors commanded locked within one 20 ms cycle when speed > 5 km/h | Critical | 3 |
| TC-OSTS-SAFE-007 | REQ-SAFE-002 | Doors maintained locked while speed > 5 km/h | Critical | 3 |
| TC-OSTS-SAFE-008 | REQ-SAFE-002 | Fail-safe: doors commanded locked on missing/stale speed signal | Critical | 3 |
| TC-OSTS-SAFE-009 | REQ-SAFE-003 | Departure signal withheld when any door not CLOSED_AND_LOCKED | Critical | 3 |
| TC-OSTS-SAFE-010 | REQ-SAFE-003 | Departure signal withheld with N-1 doors locked (one door open) | Critical | 3 |
| TC-OSTS-SAFE-011 | REQ-SAFE-003 | Departure signal asserted ONLY when all doors confirmed locked | Critical | 3 |
| TC-OSTS-SAFE-012 | REQ-SAFE-004 | Obstacle detection → motor stop and reversal within 150 ms (obstacle sensor A) | Critical | 3 |
| TC-OSTS-SAFE-013 | REQ-SAFE-004 | Obstacle detection → motor stop and reversal within 150 ms (obstacle sensor B) | Critical | 3 |
| TC-OSTS-SAFE-014 | REQ-SAFE-004 | Door reversal continues until FULLY_OPEN position reached | Critical | 3 |
| TC-OSTS-SAFE-015 | REQ-SAFE-004 | ISR latency ≤ 1 ms from obstacle GPIO rising edge to interrupt handler | Critical | 3 |
| TC-OSTS-SAFE-016 | REQ-SAFE-005 | 2oo2 position: CLOSED only when both sensors agree | Critical | 3 |
| TC-OSTS-SAFE-017 | REQ-SAFE-005 | All 4 sensor combinations produce correct conservative outcome | Critical | 3 |
| TC-OSTS-SAFE-018 | REQ-SAFE-005 | Sensor disagreement logged; fault raised on disagreement | Critical | 3 |
| TC-OSTS-SAFE-019 | REQ-SAFE-006 | Safe state triggered within 100 ms on speed sensor failure | Critical | 3 |
| TC-OSTS-SAFE-020 | REQ-SAFE-006 | Safe state triggered within 100 ms on position sensor failure | Critical | 3 |
| TC-OSTS-SAFE-021 | REQ-SAFE-006 | Safe state triggered within 100 ms on lock sensor failure | Critical | 3 |
| TC-OSTS-SAFE-022 | REQ-SAFE-006 | Safe state triggered within 100 ms on cross-channel disagreement | Critical | 3 |
| TC-OSTS-SAFE-023 | REQ-SAFE-006 | Safe state triggered within 100 ms on CAN speed timeout > 200 ms | Critical | 3 |
| TC-OSTS-SAFE-024 | REQ-SAFE-006 | Safe state triggered within 100 ms on MCU failure (cross-channel detected) | Critical | 3 |
| TC-OSTS-SAFE-025 | REQ-SAFE-006 | TCMS alerted within 100 ms of safe state entry | Critical | 3 |
| TC-OSTS-SAFE-026 | REQ-SAFE-007 | Lock sensors report locked after controlled power removal | Critical | 3 |
| TC-OSTS-SAFE-027 | REQ-SAFE-007 | No software logic defaults locks open (HAL active-low verified) | Critical | 3 |
| TC-OSTS-SAFE-028 | REQ-SAFE-008 | Watchdog refreshed every 40 ms ± 5 ms during normal operation | Critical | 3 |
| TC-OSTS-SAFE-029 | REQ-SAFE-008 | Deliberate watchdog starvation (loop hang) → hardware reset within 55 ms | Critical | 3 |
| TC-OSTS-SAFE-030 | REQ-SAFE-008 | Watchdog refresh not callable before safety logic completion | Critical | 3 |
| TC-OSTS-SAFE-031 | REQ-SAFE-009 | CRC-16 verified on CAN speed message (receive) — valid CRC passes | Critical | 3 |
| TC-OSTS-SAFE-032 | REQ-SAFE-009 | CRC-16 error on CAN speed message → message discarded, fault logged | Critical | 3 |
| TC-OSTS-SAFE-033 | REQ-SAFE-009 | CRC-16 verified on cross-channel SPI frame | Critical | 3 |
| TC-OSTS-SAFE-034 | REQ-SAFE-009 | CRC-16 verified on boot-time flash integrity (valid CRC → boot proceeds) | Critical | 3 |
| TC-OSTS-SAFE-035 | REQ-SAFE-009 | CRC-16 corruption on event log entry → fault detected | Critical | 3 |
| TC-OSTS-SAFE-036 | REQ-SAFE-010 | Channel A and Channel B independently compute same speed interlock decision | Critical | 3 |
| TC-OSTS-SAFE-037 | REQ-SAFE-010 | Deliberate disagreement injection → safe state within 20 ms | Critical | 3 |
| TC-OSTS-SAFE-038 | REQ-SAFE-010 | All listed safety decisions compared every 20 ms cycle | Critical | 3 |
| TC-OSTS-SAFE-039 | REQ-SAFE-011 | Out-of-range speed input rejected and logged | Critical | 3 |
| TC-OSTS-SAFE-040 | REQ-SAFE-011 | Speed delta > 50 km/h per 100 ms triggers plausibility violation | Critical | 3 |
| TC-OSTS-SAFE-041 | REQ-SAFE-011 | Out-of-range sensor input rejected and logged | Critical | 3 |
| TC-OSTS-SAFE-042 | REQ-SAFE-012 | Emergency release detected within 20 ms | High | 2 |
| TC-OSTS-SAFE-043 | REQ-SAFE-012 | TCMS alert within 200 ms of emergency release detection | High | 2 |
| TC-OSTS-SAFE-044 | REQ-SAFE-012 | FAULT_EMERG_RELEASE_WHILE_MOVING raised when speed > 5 km/h | High | 2 |
| TC-OSTS-SAFE-045 | REQ-SAFE-013 | System refuses Normal mode entry on self-test failure | High | 3 |
| TC-OSTS-SAFE-046 | REQ-SAFE-013 | All sensor types exercised in startup self-test | High | 3 |
| TC-OSTS-SAFE-047 | REQ-SAFE-013 | Specific fault code reported per failed sensor on self-test | High | 3 |
| TC-OSTS-SAFE-048 | REQ-SAFE-014 | DC >= 99% calculation verified by analysis (FMEA-based) | High | 3 |
| TC-OSTS-SAFE-049 | REQ-SAFE-015 | Doors remain locked when CAN disconnected (speed assumed) | Critical | 3 |
| TC-OSTS-SAFE-050 | REQ-SAFE-015 | Doors locked within 200 ms of CAN speed signal loss | Critical | 3 |
| TC-OSTS-SAFE-051 | REQ-SAFE-015 | No door opening when speed data invalid (CRC error) | Critical | 3 |
| TC-OSTS-SAFE-052 | REQ-SAFE-016 | Position sensor fault → door assumed not closed → departure withheld | Critical | 3 |
| TC-OSTS-SAFE-053 | REQ-SAFE-016 | Stuck sensor fault → door assumed not closed | Critical | 3 |
| TC-OSTS-SAFE-054 | REQ-SAFE-017 | All safety variables initialized to fail-safe defaults at system startup | Critical | 3 |
| TC-OSTS-SAFE-055 | REQ-SAFE-017 | speed_interlock_active = 1 at init; door_lock_command = 1 at init | Critical | 3 |
| TC-OSTS-SAFE-056 | REQ-SAFE-018 | Speed interlock active for all doors (including disabled) in SELECTIVE_DISABLE | High | 2 |
| TC-OSTS-SAFE-057 | REQ-SAFE-018 | Departure inhibited if disabled door on platform side and not confirmed locked | High | 2 |
| TC-OSTS-SAFE-058 | REQ-SAFE-019 | RAM CRC corruption detected within 100 ms; safe state triggered | High | 3 |
| TC-OSTS-SAFE-059 | REQ-SAFE-019 | FAULT_RAM_CRC_FAIL raised and logged on corruption | High | 3 |
| TC-OSTS-SAFE-060 | REQ-SAFE-020 | Flash CRC fail at boot → Normal mode NOT entered; boot fault code output | High | 3 |
| TC-OSTS-SAFE-061 | REQ-SAFE-020 | Flash CRC pass at boot → Normal mode entered normally | High | 3 |
| TC-OSTS-SAFE-062 | REQ-SAFE-021 | Zero `goto` occurrences in SIL 3 safety functions (static analysis) | High | 3 |
| TC-OSTS-SAFE-063 | REQ-SAFE-021 | MISRA C Rule 15.1 compliance verified | High | 3 |

---

### 3.5 Interface Test Cases

**Objective**: Validate all 13 interface requirements (REQ-INT-001 to REQ-INT-013).

| TC ID | Requirement(s) | Description | Priority | SIL |
|-------|---------------|-------------|----------|-----|
| TC-OSTS-INT-001 | REQ-INT-001 | PWM output at 20 kHz confirmed by oscilloscope | High | 3 |
| TC-OSTS-INT-002 | REQ-INT-001 | Duty cycle accuracy ± 2% (0%, 50%, 100% test points) | High | 3 |
| TC-OSTS-INT-003 | REQ-INT-001 | Direction GPIO correct for OPEN, CLOSE, STOP commands | High | 3 |
| TC-OSTS-INT-004 | REQ-INT-001 | HAL_PWM error → duty set to 0 → FAULT_MOTOR_CTRL_FAIL → SAFE_STATE | Critical | 3 |
| TC-OSTS-INT-005 | REQ-INT-002 | Both position sensors read independently per 20 ms cycle | High | 3 |
| TC-OSTS-INT-006 | REQ-INT-002 | Interrupt latency ≤ 5 ms for position sensor interrupt | High | 3 |
| TC-OSTS-INT-007 | REQ-INT-003 | Single obstacle sensor (A) trigger → reversal initiated | Critical | 3 |
| TC-OSTS-INT-008 | REQ-INT-003 | Single obstacle sensor (B) trigger → reversal initiated | Critical | 3 |
| TC-OSTS-INT-009 | REQ-INT-003 | ISR latency ≤ 1 ms from obstacle GPIO rising edge | Critical | 3 |
| TC-OSTS-INT-010 | REQ-INT-003 | Both obstacle sensors tested at startup; fault if both read 0 | High | 3 |
| TC-OSTS-INT-011 | REQ-INT-004 | Lock command/release verified by lock sensors | Critical | 3 |
| TC-OSTS-INT-012 | REQ-INT-004 | Fail-closed: lock springs lock door on solenoid power-off | Critical | 3 |
| TC-OSTS-INT-013 | REQ-INT-005 | Lock sensor disagreement treated conservatively (not-locked) | Critical | 3 |
| TC-OSTS-INT-014 | REQ-INT-005 | Lock sensor fault detected and logged | Critical | 3 |
| TC-OSTS-INT-015 | REQ-INT-006 | Watchdog refreshed every 40 ms ± 5 ms via HAL | Critical | 3 |
| TC-OSTS-INT-016 | REQ-INT-006 | Deliberate missed watchdog refresh → hardware reset within 55 ms | Critical | 3 |
| TC-OSTS-INT-017 | REQ-INT-007 | Speed CAN message (0x100) parsed correctly with valid CRC | Critical | 3 |
| TC-OSTS-INT-018 | REQ-INT-007 | CRC mismatch on 0x100 → message discarded, CRC error logged | Critical | 3 |
| TC-OSTS-INT-019 | REQ-INT-007 | Sequence counter discontinuity on 0x100 detected and logged | High | 3 |
| TC-OSTS-INT-020 | REQ-INT-007 | CAN timeout (> 200 ms no message) → speed fault raised | Critical | 3 |
| TC-OSTS-INT-021 | REQ-INT-008 | CAN 0x200 (door-locked-all) transmitted at 100 ms rate; CRC-16 valid | High | 3 |
| TC-OSTS-INT-022 | REQ-INT-008 | CAN 0x201 (per-door status) transmitted at 100 ms rate; content correct | High | 2 |
| TC-OSTS-INT-023 | REQ-INT-009 | DDU messages exchanged every 20 ms; CRC validated | High | 3 |
| TC-OSTS-INT-024 | REQ-INT-009 | DDU timeout (> 40 ms no response) → DDU communication fault | High | 3 |
| TC-OSTS-INT-025 | REQ-INT-010 | Cross-channel SPI state exchange every 20 ms cycle | Critical | 3 |
| TC-OSTS-INT-026 | REQ-INT-010 | SPI CRC mismatch → safe state triggered | Critical | 3 |
| TC-OSTS-INT-027 | REQ-INT-010 | Deliberate speed disagreement between channels → safe state within 20 ms | Critical | 3 |
| TC-OSTS-INT-028 | REQ-INT-011 | Emergency release detected within 20 ms; TCMS alert within 200 ms | High | 2 |
| TC-OSTS-INT-029 | REQ-INT-012 | Status indicators match door state within one 20 ms cycle | Medium | 2 |
| TC-OSTS-INT-030 | REQ-INT-013 | Event log downloadable via diagnostics port in Normal mode | Low | 1 |
| TC-OSTS-INT-031 | REQ-INT-013 | No safety parameter modification possible via diagnostics port in Normal mode | Medium | 1 |

---

### 3.6 Boundary Value Analysis Test Cases

**Objective**: Apply BVA to all safety-critical numeric parameters. Boundary Value Analysis is **Mandatory** at SIL 3 (Table A.5 item 13). For each parameter: test min−1 (invalid), min, min+1, max−1, max, max+1 (invalid).

| TC ID | Requirement(s) | Parameter | Boundary | Test Value | Expected Outcome | Priority | SIL |
|-------|---------------|-----------|----------|------------|-----------------|----------|-----|
| TC-OSTS-BOUND-001 | REQ-SAFE-001, REQ-FUN-001 | Train speed threshold | min−1 | 49 (4.9 km/h) | Door open PERMITTED | Critical | 3 |
| TC-OSTS-BOUND-002 | REQ-SAFE-001, REQ-FUN-001 | Train speed threshold | min (at threshold) | 50 (5.0 km/h) | Door open INHIBITED | Critical | 3 |
| TC-OSTS-BOUND-003 | REQ-SAFE-001, REQ-FUN-001 | Train speed threshold | min+1 | 51 (5.1 km/h) | Door open INHIBITED | Critical | 3 |
| TC-OSTS-BOUND-004 | REQ-INT-007 | Speed range (CAN) | max valid | 2000 (200.0 km/h) | Accepted | High | 3 |
| TC-OSTS-BOUND-005 | REQ-INT-007 | Speed range (CAN) | max+1 (invalid) | 2001 | Rejected; fault logged | High | 3 |
| TC-OSTS-BOUND-006 | REQ-INT-007 | Speed delta plausibility | max valid delta | 500 (50.0 km/h / 100 ms) | Accepted | High | 3 |
| TC-OSTS-BOUND-007 | REQ-INT-007 | Speed delta plausibility | max+1 (invalid) | 501 | Plausibility violation triggered | High | 3 |
| TC-OSTS-BOUND-008 | REQ-FUN-003 | Opening timeout | min−1 | 3900 ms | No timeout fault | High | 2 |
| TC-OSTS-BOUND-009 | REQ-FUN-003 | Opening timeout | nominal | 4000 ms | Timeout fault raised | High | 2 |
| TC-OSTS-BOUND-010 | REQ-FUN-003 | Opening timeout | max tolerance | 4100 ms (4.0 s + 100 ms) | Timeout fault must be raised by now | High | 2 |
| TC-OSTS-BOUND-011 | REQ-FUN-006 | Closing timeout | min−1 | 9900 ms | No timeout fault | High | 2 |
| TC-OSTS-BOUND-012 | REQ-FUN-006 | Closing timeout | nominal | 10000 ms | Timeout fault raised | High | 2 |
| TC-OSTS-BOUND-013 | REQ-FUN-006 | Closing timeout | max tolerance | 10100 ms | Timeout fault must be raised by now | High | 2 |
| TC-OSTS-BOUND-014 | REQ-SAFE-008, REQ-INT-006 | Watchdog refresh period | min−1 | 34 ms | Acceptable (not starved) | Critical | 3 |
| TC-OSTS-BOUND-015 | REQ-SAFE-008, REQ-INT-006 | Watchdog refresh period | max valid | 45 ms (40 ms + 5 ms margin) | Acceptable | Critical | 3 |
| TC-OSTS-BOUND-016 | REQ-SAFE-008, REQ-INT-006 | Watchdog timeout | timeout value | 50 ms starve | Hardware reset within 55 ms | Critical | 3 |
| TC-OSTS-BOUND-017 | REQ-PERF-007, REQ-SAFE-015 | Speed signal staleness | min−1 | 180 ms (valid) | Speed data accepted | Critical | 3 |
| TC-OSTS-BOUND-018 | REQ-PERF-007, REQ-SAFE-015 | Speed signal staleness | at threshold | 200 ms | Fault flag must be set | Critical | 3 |
| TC-OSTS-BOUND-019 | REQ-PERF-007, REQ-SAFE-015 | Speed signal staleness | max+1 | 220 ms | Fault flag confirmed active | Critical | 3 |
| TC-OSTS-BOUND-020 | REQ-PERF-001 | WCET control cycle | max limit | 16 ms | Pass (WCET ≤ 16 ms) | Critical | 3 |
| TC-OSTS-BOUND-021 | REQ-PERF-002, REQ-SAFE-001 | Speed interlock response | max limit | 100 ms | Lock command within 100 ms | Critical | 3 |
| TC-OSTS-BOUND-022 | REQ-PERF-003, REQ-SAFE-004 | Obstacle reversal | max limit | 150 ms | Reversal command within 150 ms | Critical | 3 |
| TC-OSTS-BOUND-023 | REQ-FUN-007 | Retry counter | max valid | 3 | Retry; no fault on 3rd | Medium | 2 |
| TC-OSTS-BOUND-024 | REQ-FUN-007 | Retry counter | max+1 (invalid) | 4th obstacle | Fault raised; retry rejected | Medium | 2 |
| TC-OSTS-BOUND-025 | REQ-FUN-009, REQ-PERF-005 | All-locked → CAN tx | max latency | 100 ms | CAN msg transmitted within 100 ms | High | 3 |
| TC-OSTS-BOUND-026 | REQ-SAFE-019 | RAM CRC check period | max | 100 ms | CRC checked within 100 ms | High | 3 |
| TC-OSTS-BOUND-027 | REQ-FUN-016 | CAN status period | min | 90 ms | Message must have arrived | High | 2 |
| TC-OSTS-BOUND-028 | REQ-FUN-016 | CAN status period | max | 110 ms | Message must have arrived | High | 2 |

---

### 3.7 Fault Injection Test Cases

**Objective**: Verify correct behaviour under injected fault conditions. Fault injection is required for all SIL 3 safety requirements (EN 50128 §7.4, hazard scenario testing).

| TC ID | Requirement(s) | Injected Fault | Expected Safe Response | Priority | SIL |
|-------|---------------|---------------|----------------------|----------|-----|
| TC-OSTS-FAULT-001 | REQ-SAFE-006, REQ-SAFE-015 | CAN bus physically disconnected | Doors remain locked; speed assumed; TCMS alerted | Critical | 3 |
| TC-OSTS-FAULT-002 | REQ-SAFE-009, REQ-INT-007 | CRC byte corrupted in CAN speed frame | Message discarded; CRC error logged; last valid speed retained | Critical | 3 |
| TC-OSTS-FAULT-003 | REQ-SAFE-006, REQ-FUN-017 | Position sensor A stuck-at-1 (always closed) | Sensor fault raised; UNKNOWN state; no departure signal | Critical | 3 |
| TC-OSTS-FAULT-004 | REQ-SAFE-016 | Position sensors A and B disagree (A=closed, B=open) | Door assumed not closed; departure withheld; fault logged | Critical | 3 |
| TC-OSTS-FAULT-005 | REQ-SAFE-006 | Lock sensor fault: commanded locked but sensor reads unlocked | FAULT_LOCK_LOST_WHILE_MOVING; TCMS alerted; lock re-commanded | Critical | 3 |
| TC-OSTS-FAULT-006 | REQ-SAFE-008 | Deliberate infinite loop in safety task (watchdog starvation) | Hardware reset within 55 ms; doors spring-locked | Critical | 3 |
| TC-OSTS-FAULT-007 | REQ-SAFE-010 | Deliberate disagreement injected into SPI cross-channel frame | Safe state triggered within 20 ms; all doors locked | Critical | 3 |
| TC-OSTS-FAULT-008 | REQ-SAFE-010 | SPI CRC mismatch injected | Safe state triggered; fault logged | Critical | 3 |
| TC-OSTS-FAULT-009 | REQ-SAFE-004 | Obstacle sensor IR beam physically interrupted during closing | Motor reversal within 150 ms; door returns to FULLY_OPEN | Critical | 3 |
| TC-OSTS-FAULT-010 | REQ-SAFE-007, REQ-INT-004 | Controlled power removal during normal operation | Lock sensors report locked after power-off | Critical | 3 |
| TC-OSTS-FAULT-011 | REQ-SAFE-019 | Single byte of safety RAM corrupted via debug probe | FAULT_RAM_CRC_FAIL within 100 ms; safe state; logged | High | 3 |
| TC-OSTS-FAULT-012 | REQ-SAFE-020 | Single byte of application Flash corrupted via debug probe | Boot fault code output; Normal mode NOT entered | High | 3 |
| TC-OSTS-FAULT-013 | REQ-INT-001 | HAL_PWM_SetDutyCycle returns ERR_HW_FAULT | Duty = 0; FAULT_MOTOR_CTRL_FAIL; SAFE_STATE entry | Critical | 3 |
| TC-OSTS-FAULT-014 | REQ-INT-007 | Sequence counter discontinuity in CAN speed message | Counter error logged; speed treated as stale after 200 ms | High | 3 |
| TC-OSTS-FAULT-015 | REQ-INT-009 | DDU RS-485 bus silence > 40 ms (DDU not responding) | DDU communication fault raised; logged | High | 3 |

---

### 3.8 Operational Scenario Test Cases

**Objective**: Validate complete end-to-end operational scenarios representative of real-world TDC usage.

| TC ID | Scenario | Description | Priority | SIL |
|-------|----------|-------------|----------|-----|
| TC-OSTS-OPS-001 | Normal station stop — door open/close cycle | Train stops; speed ≤ 5 km/h; TCMS commands open; doors open; doors close; doors locked; departure signal sent | Critical | 3 |
| TC-OSTS-OPS-002 | Speed interlock during opening attempt | Train moving at 10 km/h; operator attempts door open; all opening commands rejected; doors remain locked throughout | Critical | 3 |
| TC-OSTS-OPS-003 | Obstacle during closing | Door closing; passenger arm in doorway; obstacle detected; door reverses to fully open; retry 3 times; fault raised; driver alerted | Critical | 3 |
| TC-OSTS-OPS-004 | System startup and self-test (all pass) | Power on; self-test runs; all sensors pass; CRC valid; Normal mode entered; departure signal withheld (doors not yet closed) | High | 3 |
| TC-OSTS-OPS-005 | System startup — self-test fail (sensor fault) | Power on; self-test runs; one position sensor fails beam test; specific fault code output; Normal mode NOT entered | High | 3 |
| TC-OSTS-OPS-006 | Selective door disablement mode | One door disabled; remaining doors operate normally; platform-side disabled door blocks departure; disablement logged | Medium | 2 |
| TC-OSTS-OPS-007 | Diagnostic mode entry and exit | Train stationary; maintenance authorization present; DIAGNOSTIC mode entered; sensor readings available via diag port; safety interlocks verified active; DIAGNOSTIC mode exited | Medium | 2 |
| TC-OSTS-OPS-008 | CAN bus failure during operation | Train in revenue service; CAN bus fails; speed assumed > 5 km/h (fail-safe); doors locked; driver alerted; safe state maintained | Critical | 3 |
| TC-OSTS-OPS-009 | Channel B failure — cross-channel disagreement | Channel B MCU hangs; Channel A detects disagreement via SPI; safe state triggered within 20 ms; all doors locked; TCMS alerted | Critical | 3 |
| TC-OSTS-OPS-010 | Multiple-door deployment (N doors, all close correctly) | All N doors commanded closed; each door individually reaches CLOSED_AND_LOCKED; departure signal asserted only when last door locked | Critical | 3 |
| TC-OSTS-OPS-011 | Mode transition — Normal to Safe State | Critical fault detected during Normal mode; safe state entered within 100 ms; all doors locked; TCMS alerted; no mode change without valid recovery | Critical | 3 |
| TC-OSTS-OPS-012 | Emergency release detection while moving | Train moving at 30 km/h; emergency release activated on door 2; detection within 20 ms; FAULT_EMERG_RELEASE_WHILE_MOVING raised; TCMS alerted within 200 ms | High | 2 |
| TC-OSTS-OPS-013 | Watchdog-triggered recovery | Safety task execution hangs (simulated via debug); watchdog fires in 55 ms; MCU resets; system restarts; startup self-test runs; Normal mode re-entered if all pass | Critical | 3 |
| TC-OSTS-OPS-014 | Reliability — 30-day continuous operational availability | Simulated 30-day operational cycle; system availability >= 99.9%; no critical faults; event log functional | High | 3 |

---

### 3.9 Reliability and Operational Requirement Test Cases

**Objective**: Validate all reliability requirements (REQ-REL-001 to REQ-REL-004) and operational requirements (REQ-OPR-001 to REQ-OPR-008).

| TC ID | Requirement(s) | Description | Priority | SIL |
|-------|---------------|-------------|----------|-----|
| TC-OSTS-REL-001 | REQ-REL-001 | System availability >= 99.9% over simulated 30-day period | High | 3 |
| TC-OSTS-REL-002 | REQ-REL-001 | Diagnostic operations do not interrupt normal door control cycle | High | 3 |
| TC-OSTS-REL-003 | REQ-REL-002 | EN 50128 SIL 3 lifecycle compliance demonstrated (safety case) | Critical | 3 |
| TC-OSTS-REL-004 | REQ-REL-003 | DC >= 99% calculation documented and reviewed by VER/SAF | High | 3 |
| TC-OSTS-REL-005 | REQ-REL-004 | Diagnostics task time budget ≤ 2 ms per 20 ms cycle (no overrun) | Medium | 2 |
| TC-OSTS-OPR-001 | REQ-OPR-001 | Static analysis: zero mandatory MISRA C:2012 violations | High | 3 |
| TC-OSTS-OPR-002 | REQ-OPR-001 | All required MISRA rule violations documented; deviation log reviewed by QUA | High | 3 |
| TC-OSTS-OPR-003 | REQ-OPR-002 | Static analysis: zero use of `int`/`unsigned`/`long` in safety modules | High | 3 |
| TC-OSTS-OPR-004 | REQ-OPR-003 | Static analysis: zero calls to `malloc`/`calloc`/`realloc`/`free`/`alloca` | Critical | 3 |
| TC-OSTS-OPR-005 | REQ-OPR-003 | Linker map confirms zero heap usage | Critical | 3 |
| TC-OSTS-OPR-006 | REQ-OPR-004 | Static call graph: zero recursive paths in SIL 3 modules | High | 3 |
| TC-OSTS-OPR-007 | REQ-OPR-005 | Static analysis: zero functions exceeding cyclomatic complexity limit (≤10 for SIL 3) | High | 3 |
| TC-OSTS-OPR-008 | REQ-OPR-006 | Code review: NULL checks, range checks, return value checks in all SIL 3 functions | High | 3 |
| TC-OSTS-OPR-009 | REQ-OPR-007 | Static analysis: all non-void SIL 3 functions return `error_t` | High | 3 |
| TC-OSTS-OPR-010 | REQ-OPR-008 | Scheduler task execution order documented and verified by performance test | High | 3 |
| TC-OSTS-OPR-011 | REQ-OPR-008 | WCET of each task measured; total cycle ≤ 16 ms verified | Critical | 3 |

---

### 3.10 Security Test Cases

**Objective**: Validate all security requirements (REQ-SEC-001 to REQ-SEC-003).

| TC ID | Requirement(s) | Description | Priority | SIL |
|-------|---------------|-------------|----------|-----|
| TC-OSTS-SEC-001 | REQ-SEC-001 | Unauthorized mode change (no auth token) → rejected; attempt logged | High | 2 |
| TC-OSTS-SEC-002 | REQ-SEC-001 | Authorized mode change (valid driver key) → accepted; logged | High | 2 |
| TC-OSTS-SEC-003 | REQ-SEC-002 | All mode change events logged with required fields (timestamp, mode, source, result) | Medium | 2 |
| TC-OSTS-SEC-004 | REQ-SEC-003 | Write command on diagnostics port in Normal mode → `CMD_NOT_PERMITTED` | Medium | 2 |
| TC-OSTS-SEC-005 | REQ-SEC-003 | Read command on diagnostics port in Normal mode → succeeds | Medium | 2 |
| TC-OSTS-SEC-006 | REQ-SEC-003 | Configuration write in Diagnostic mode with maintenance auth → permitted | Medium | 2 |

---

### 3.11 Regression Test Cases

**Objective**: Provide a stable regression test suite for re-execution after any software change. Regression testing is **Mandatory** at SIL 3 (Table A.5 item 12).

**Regression Test Scope**: All critical and high-priority test cases from Sections 3.2–3.10. Selected test cases are identified for the core regression suite below.

| TC ID | Description | Basis Test Case(s) | Priority |
|-------|-------------|-------------------|----------|
| TC-OSTS-REG-001 | Speed interlock regression (core safety) | TC-OSTS-SAFE-001, 002, 003, 006, 007 | Critical |
| TC-OSTS-REG-002 | Obstacle detection regression | TC-OSTS-SAFE-012, 013, TC-OSTS-PERF-004 | Critical |
| TC-OSTS-REG-003 | Safe state transition regression (all triggers) | TC-OSTS-SAFE-019 to 025 | Critical |
| TC-OSTS-REG-004 | 2oo2 sensor voting regression | TC-OSTS-SAFE-016, 017, TC-OSTS-FUNC-015 | Critical |
| TC-OSTS-REG-005 | Departure interlock regression | TC-OSTS-SAFE-009, 010, 011, TC-OSTS-FUNC-025, 026 | Critical |
| TC-OSTS-REG-006 | CRC protection regression | TC-OSTS-SAFE-031, 032, 033, 034, 035 | Critical |
| TC-OSTS-REG-007 | Watchdog regression | TC-OSTS-SAFE-028, 029, TC-OSTS-FAULT-006 | Critical |
| TC-OSTS-REG-008 | WCET regression (performance) | TC-OSTS-PERF-001, 002 | Critical |
| TC-OSTS-REG-009 | Full Normal station stop scenario | TC-OSTS-OPS-001 | Critical |
| TC-OSTS-REG-010 | Cross-channel 2oo2 regression | TC-OSTS-SAFE-036, 037, TC-OSTS-FAULT-007, 008 | Critical |

**Regression Trigger**: Any software change (defect fix, enhancement, configuration change) SHALL trigger execution of the full regression suite before re-release. Regression results SHALL be included in the OSTR (Item 24).

---

### 3.12 Acceptance Test Cases

**Objective**: Customer/validator acceptance testing executed with VAL participation. Acceptance criteria are confirmed with VAL prior to Phase 7 test execution.

| TC ID | Acceptance Criterion | Description | Priority | SIL |
|-------|---------------------|-------------|----------|-----|
| TC-OSTS-ACC-001 | All 7 safety functions (SF-001–SF-007) verified operational | Safety function end-to-end demonstration with VAL witness | Critical | 3 |
| TC-OSTS-ACC-002 | Speed interlock: zero door opening events at speed > 5 km/h in 1000-cycle soak test | Soak test: 1000 open/close cycles with speed variations | Critical | 3 |
| TC-OSTS-ACC-003 | Obstacle reversal latency ≤ 150 ms in 100 consecutive trials | Statistical obstacle response test (100 trials, report worst-case) | Critical | 3 |
| TC-OSTS-ACC-004 | Safe state entry within 100 ms for all 6 critical fault triggers | Witnessed fault injection demonstration | Critical | 3 |
| TC-OSTS-ACC-005 | WCET ≤ 16 ms verified on target hardware | WCET measurement demonstrated to VAL | Critical | 3 |
| TC-OSTS-ACC-006 | Statement and Branch coverage targets met (per SVP/SQAP) | Coverage report presented to VAL | Critical | 3 |
| TC-OSTS-ACC-007 | Zero safety-critical MISRA C violations | Static analysis report presented to VAL | High | 3 |
| TC-OSTS-ACC-008 | All 81 requirements have at least one passed test case | Traceability matrix review with VAL | Critical | 3 |
| TC-OSTS-ACC-009 | System availability ≥ 99.9% over 30-day operational soak test | Operational availability demonstration | High | 3 |
| TC-OSTS-ACC-010 | All machine-readable test results available (XML/JSON) | Test results package reviewed by VAL | High | 3 |

---

## 3.13 Test Case Summary

| Category | Section | TC Count | Critical | High | Medium | Low |
|----------|---------|----------|----------|------|--------|-----|
| Functional | 3.2 | 62 | 20 | 32 | 10 | 0 |
| Performance | 3.3 | 12 | 5 | 6 | 1 | 0 |
| Safety-Critical Path | 3.4 | 63 | 43 | 20 | 0 | 0 |
| Interface | 3.5 | 31 | 16 | 14 | 1 | 1 |
| Boundary Value Analysis | 3.6 | 28 | 16 | 12 | 0 | 0 |
| Fault Injection | 3.7 | 15 | 12 | 3 | 0 | 0 |
| Operational Scenarios | 3.8 | 14 | 9 | 5 | 0 | 0 |
| Reliability/Operational | 3.9 | 16 | 5 | 10 | 1 | 0 |
| Security | 3.10 | 6 | 0 | 3 | 3 | 0 |
| Regression | 3.11 | 10 | 10 | 0 | 0 | 0 |
| Acceptance | 3.12 | 10 | 7 | 3 | 0 | 0 |
| **TOTAL** | | **267** | **143** | **108** | **16** | **1** |

---

## 4. Traceability Matrix

### 4.1 Requirements to Test Cases (Forward Traceability)

All 81 SRS requirements are traced below. Every SRS requirement has at least one test case — 100% coverage.

| Req ID | Description | Test Case ID(s) | SIL | Coverage |
|--------|-------------|----------------|-----|----------|
| REQ-FUN-001 | Door Opening Command Processing | TC-OSTS-FUNC-001 to 006 | 3 | ✓ |
| REQ-FUN-002 | Door Opening Completion Detection | TC-OSTS-FUNC-007 to 009 | 3 | ✓ |
| REQ-FUN-003 | Door Opening Timeout Fault | TC-OSTS-FUNC-010, 011, TC-OSTS-BOUND-008 to 010 | 2 | ✓ |
| REQ-FUN-004 | Door Closing Command Processing | TC-OSTS-FUNC-012 to 014 | 3 | ✓ |
| REQ-FUN-005 | Door Close-and-Lock Completion | TC-OSTS-FUNC-015 to 018 | 3 | ✓ |
| REQ-FUN-006 | Door Closing Fault — Timeout | TC-OSTS-FUNC-019, 020, TC-OSTS-BOUND-011 to 013 | 2 | ✓ |
| REQ-FUN-007 | Door Obstacle Retry Logic | TC-OSTS-FUNC-021, 022, TC-OSTS-BOUND-023, 024 | 2 | ✓ |
| REQ-FUN-008 | Automatic Door Lock Engagement | TC-OSTS-FUNC-023, 024 | 3 | ✓ |
| REQ-FUN-009 | Departure Interlock Signal | TC-OSTS-FUNC-025 to 027, TC-OSTS-BOUND-025 | 3 | ✓ |
| REQ-FUN-010 | Door Lock Maintenance While Moving | TC-OSTS-FUNC-028, 029 | 3 | ✓ |
| REQ-FUN-011 | Operational Mode Support | TC-OSTS-FUNC-030 to 033 | 3 | ✓ |
| REQ-FUN-012 | Mode Transition Authorization | TC-OSTS-FUNC-034 to 036 | 3 | ✓ |
| REQ-FUN-013 | Selective Door Disablement Mode | TC-OSTS-FUNC-037 to 039, TC-OSTS-OPS-006 | 2 | ✓ |
| REQ-FUN-014 | Diagnostic Mode Conditions | TC-OSTS-FUNC-040 to 042, TC-OSTS-OPS-007 | 2 | ✓ |
| REQ-FUN-015 | Continuous Door Position Monitoring | TC-OSTS-FUNC-043 to 048 | 3 | ✓ |
| REQ-FUN-016 | Door Status Reporting to TCMS | TC-OSTS-FUNC-049 to 051, TC-OSTS-BOUND-027, 028 | 2 | ✓ |
| REQ-FUN-017 | Continuous Fault Monitoring | TC-OSTS-FUNC-052 to 058 | 3 | ✓ |
| REQ-FUN-018 | Fault Event Logging | TC-OSTS-FUNC-059 to 062 | 1 | ✓ |
| REQ-PERF-001 | Control Cycle Time (WCET ≤ 16 ms) | TC-OSTS-PERF-001, 002, 012, TC-OSTS-BOUND-020 | 3 | ✓ |
| REQ-PERF-002 | Speed Interlock Response ≤ 100 ms | TC-OSTS-PERF-003, TC-OSTS-BOUND-021 | 3 | ✓ |
| REQ-PERF-003 | Obstacle Detection Response ≤ 150 ms | TC-OSTS-PERF-004, TC-OSTS-BOUND-022 | 3 | ✓ |
| REQ-PERF-004 | Command-to-Motor-Start Latency ≤ 200 ms | TC-OSTS-PERF-005 | 3 | ✓ |
| REQ-PERF-005 | TCMS Locked Status Latency ≤ 100 ms | TC-OSTS-PERF-006, TC-OSTS-BOUND-025 | 3 | ✓ |
| REQ-PERF-006 | Sensor Fault Detection ≤ 100 ms | TC-OSTS-PERF-007 | 3 | ✓ |
| REQ-PERF-007 | Communication Fault Detection ≤ 200 ms | TC-OSTS-PERF-008, TC-OSTS-BOUND-017 to 019 | 3 | ✓ |
| REQ-PERF-008 | CPU Utilization ≤ 80% | TC-OSTS-PERF-009 | 2 | ✓ |
| REQ-PERF-009 | RAM Utilization ≤ 800 KB | TC-OSTS-PERF-010 | 3 | ✓ |
| REQ-PERF-010 | Flash Utilization ≤ 1600 KB | TC-OSTS-PERF-011 | 2 | ✓ |
| REQ-INT-001 | Door Motor Actuator Interface | TC-OSTS-INT-001 to 004 | 3 | ✓ |
| REQ-INT-002 | Door Position Sensor Interface | TC-OSTS-INT-005, 006 | 3 | ✓ |
| REQ-INT-003 | Obstacle Detection Sensor Interface | TC-OSTS-INT-007 to 010 | 3 | ✓ |
| REQ-INT-004 | Door Lock Actuator Interface | TC-OSTS-INT-011, 012 | 3 | ✓ |
| REQ-INT-005 | Lock Position Sensor Interface | TC-OSTS-INT-013, 014 | 3 | ✓ |
| REQ-INT-006 | Watchdog Hardware Interface | TC-OSTS-INT-015, 016, TC-OSTS-BOUND-014 to 016 | 3 | ✓ |
| REQ-INT-007 | TCMS CAN Interface — Receive | TC-OSTS-INT-017 to 020, TC-OSTS-BOUND-004 to 007 | 3 | ✓ |
| REQ-INT-008 | TCMS CAN Interface — Transmit | TC-OSTS-INT-021, 022 | 3 | ✓ |
| REQ-INT-009 | DDU RS-485 Interface | TC-OSTS-INT-023, 024 | 3 | ✓ |
| REQ-INT-010 | Cross-Channel SPI Communication | TC-OSTS-INT-025 to 027 | 3 | ✓ |
| REQ-INT-011 | Emergency Release Detection | TC-OSTS-INT-028, TC-OSTS-OPS-012 | 2 | ✓ |
| REQ-INT-012 | Driver Control Panel Interface | TC-OSTS-INT-029 | 2 | ✓ |
| REQ-INT-013 | Diagnostics Port Interface | TC-OSTS-INT-030, 031 | 1 | ✓ |
| REQ-SAFE-001 | Speed Interlock — Inhibit Opening | TC-OSTS-SAFE-001 to 005, TC-OSTS-BOUND-001 to 003 | 3 | ✓ |
| REQ-SAFE-002 | Speed Interlock — Maintain Locking | TC-OSTS-SAFE-006 to 008 | 3 | ✓ |
| REQ-SAFE-003 | Departure Interlock — All Locked | TC-OSTS-SAFE-009 to 011 | 3 | ✓ |
| REQ-SAFE-004 | Obstacle Detection and Reversal | TC-OSTS-SAFE-012 to 015, TC-OSTS-FAULT-009 | 3 | ✓ |
| REQ-SAFE-005 | 2oo2 Position Verification | TC-OSTS-SAFE-016 to 018 | 3 | ✓ |
| REQ-SAFE-006 | Safe State — Critical Fault | TC-OSTS-SAFE-019 to 025, TC-OSTS-FAULT-001 to 005 | 3 | ✓ |
| REQ-SAFE-007 | Safe State — Power Loss | TC-OSTS-SAFE-026, 027, TC-OSTS-FAULT-010 | 3 | ✓ |
| REQ-SAFE-008 | Watchdog Monitoring | TC-OSTS-SAFE-028 to 030, TC-OSTS-BOUND-014 to 016 | 3 | ✓ |
| REQ-SAFE-009 | CRC Protection | TC-OSTS-SAFE-031 to 035 | 3 | ✓ |
| REQ-SAFE-010 | Cross-Channel 2oo2 Safety Logic | TC-OSTS-SAFE-036 to 038, TC-OSTS-FAULT-007, 008 | 3 | ✓ |
| REQ-SAFE-011 | Input Validation — All External Inputs | TC-OSTS-SAFE-039 to 041 | 3 | ✓ |
| REQ-SAFE-012 | Emergency Release Monitoring | TC-OSTS-SAFE-042 to 044, TC-OSTS-OPS-012 | 2 | ✓ |
| REQ-SAFE-013 | Self-Test at Startup | TC-OSTS-SAFE-045 to 047, TC-OSTS-OPS-004, 005 | 3 | ✓ |
| REQ-SAFE-014 | Diagnostic Coverage >= 99% | TC-OSTS-SAFE-048, TC-OSTS-REL-004 | 3 | ✓ |
| REQ-SAFE-015 | Safe State — Speed Interlock on Comm Loss | TC-OSTS-SAFE-049 to 051, TC-OSTS-FAULT-001 | 3 | ✓ |
| REQ-SAFE-016 | Safe State — Position Sensor Fault | TC-OSTS-SAFE-052, 053 | 3 | ✓ |
| REQ-SAFE-017 | Fail-Safe Initialization Defaults | TC-OSTS-SAFE-054, 055, TC-OSTS-OPS-004 | 3 | ✓ |
| REQ-SAFE-018 | Selective Disable — Interlock Maintenance | TC-OSTS-SAFE-056, 057, TC-OSTS-OPS-006 | 2 | ✓ |
| REQ-SAFE-019 | Periodic Memory Integrity Check | TC-OSTS-SAFE-058, 059, TC-OSTS-FAULT-011, TC-OSTS-BOUND-026 | 3 | ✓ |
| REQ-SAFE-020 | Boot-Time Flash Integrity | TC-OSTS-SAFE-060, 061, TC-OSTS-FAULT-012 | 3 | ✓ |
| REQ-SAFE-021 | Structured Programming Compliance | TC-OSTS-SAFE-062, 063, TC-OSTS-OPR-001 | 3 | ✓ |
| REQ-REL-001 | System Availability >= 99.9% | TC-OSTS-REL-001, 002, TC-OSTS-OPS-014, TC-OSTS-ACC-009 | 3 | ✓ |
| REQ-REL-002 | PFH Target (SIL 3) | TC-OSTS-REL-003 | 3 | ✓ |
| REQ-REL-003 | Diagnostic Coverage Achievement | TC-OSTS-REL-004, TC-OSTS-SAFE-048 | 3 | ✓ |
| REQ-REL-004 | Online Diagnostics Non-Interruption | TC-OSTS-REL-005, TC-OSTS-PERF-012 | 2 | ✓ |
| REQ-SEC-001 | Unauthorized Mode Change Prevention | TC-OSTS-SEC-001, 002 | 2 | ✓ |
| REQ-SEC-002 | Mode Change Event Logging | TC-OSTS-SEC-003 | 2 | ✓ |
| REQ-SEC-003 | Diagnostics Port Read-Only Enforcement | TC-OSTS-SEC-004 to 006 | 2 | ✓ |
| REQ-OPR-001 | MISRA C:2012 Compliance | TC-OSTS-OPR-001, 002, TC-OSTS-ACC-007 | 3 | ✓ |
| REQ-OPR-002 | Fixed-Width Integer Types | TC-OSTS-OPR-003 | 3 | ✓ |
| REQ-OPR-003 | Static Memory Allocation Only | TC-OSTS-OPR-004, 005 | 3 | ✓ |
| REQ-OPR-004 | No Recursion | TC-OSTS-OPR-006 | 3 | ✓ |
| REQ-OPR-005 | Cyclomatic Complexity Limit | TC-OSTS-OPR-007 | 3 | ✓ |
| REQ-OPR-006 | Defensive Programming | TC-OSTS-OPR-008 | 3 | ✓ |
| REQ-OPR-007 | Error Handling — Explicit Return Codes | TC-OSTS-OPR-009 | 3 | ✓ |
| REQ-OPR-008 | Static Cyclic Executive Scheduler | TC-OSTS-OPR-010, 011 | 3 | ✓ |

### 4.2 Traceability Statistics

| Metric | Value |
|--------|-------|
| Total SRS requirements | 81 |
| Requirements with ≥ 1 test case | 81 |
| Forward traceability coverage | **100%** (81/81) |
| SIL 3 requirements covered | 58/58 — **100%** |
| SIL 2 requirements covered | 17/17 — **100%** |
| SIL 1 requirements covered | 6/6 — **100%** |
| Total test cases | 267 |
| Orphan test cases (no req) | 0 |

### 4.3 Test Cases to Requirements (Reverse Traceability)

All 267 test cases in Sections 3.2–3.12 trace to at least one SRS requirement. The mapping is given in each table's `Requirement(s)` column and the forward traceability table above. Zero orphan test cases exist (all test cases have at least one SRS requirement).

---

## 5. Defect Management

### 5.1 Defect Classification

| Severity | Definition | Action |
|----------|------------|--------|
| **Critical** | Safety impact, SIL 3 test failure, safe state not triggered, CRC not checked | Immediate fix required; block Phase 7 exit gate |
| **High** | Major function not working; test case failed; performance target missed | Fix before release |
| **Medium** | Minor function not working; workaround exists; no safety impact | Fix in next release (with CCB approval) |
| **Low** | Cosmetic issue; no functional or safety impact | Fix as time permits |

### 5.2 Defect Tracking

**Defect Tracking**: All defects tracked per SCMP (DOC-SCMP-2026-001). Defect IDs referenced in OSTR (Item 24).

**Defect Workflow**:
1. Defect detected during test execution → logged with severity, TC ID, steps to reproduce
2. TST assigns severity; routes to PM
3. PM routes to IMP (fix) or DES (design issue) or REQ (requirements ambiguity)
4. IMP fixes and unit-tests
5. TST re-executes failed TC and regression suite
6. Defect closed if verified; reopened if not resolved

**Critical Defects**: Zero outstanding critical defects is a mandatory Phase 7 exit criterion.

---

## 6. Test Schedule

### 6.1 Test Phases (Phase 7)

| Phase | Activity | Responsible |
|-------|----------|-------------|
| T-2 weeks | Test environment setup and validation | TST |
| T-1 week | Test data preparation and OSTS final review | TST, VER, VAL |
| Phase 7 start | Begin OSTS execution: functional, safety, performance, fault injection | TST |
| Phase 7 mid | Defect resolution; regression run | TST + IMP |
| Phase 7 end | Acceptance tests (with VAL); OSTR compilation | TST + VAL |
| Phase 7 gate | OSTR (Item 24) submitted to PM for routing to QUA/VER/VAL | TST → PM |

### 6.2 Test Milestones

| Milestone | Criteria |
|-----------|----------|
| OSTS approved (Phase 2 gate) | VER and VAL approve this document; COD records in LIFECYCLE_STATE.md |
| Test environment ready | All hardware, tools, test harness validated |
| Test execution complete | All 267 test cases executed; results in XML/JSON |
| All critical defects resolved | Zero outstanding critical defects |
| Coverage targets met | Statement and Branch coverage per SVP/SQAP confirmed |
| OSTR submitted | TST submits Item 24 to PM for routing |
| VAL acceptance | VAL provides acceptance sign-off (independent, mandatory SIL 3) |

---

## 7. Roles and Responsibilities

| Role | Responsibilities |
|------|-----------------|
| **Software Tester (TST)** | OSTS authorship; test case design; test execution; OSTR compilation; defect logging; regression execution |
| **Software Validator (VAL)** | OSTS 2nd check; acceptance test witness; VAL acceptance criteria input; final software release recommendation |
| **Software Verifier (VER)** | OSTS 1st check; static analysis (owns Item 19); coverage evidence review |
| **Implementer (IMP)** | Defect fixes; unit tests of fixes |
| **Quality Assurance (QUA)** | OSTS template compliance check; audit; approve OSTR |
| **Project Manager (PM)** | Task routing; schedule management; CCB leadership; deliverable submission |
| **Safety Engineer (SAF)** | SAF input on safety-critical test cases (TC-OSTS-SAFE-* scenarios); DC calculation review |

**SIL 3 Independence Requirements**:
- TST MUST NOT test code written by the same person (HR per EN 50128 §5.3.4 and ORGANIZATION.md)
- VAL SHALL be independent from TST and development team (M at SIL 3 per EN 50128 §5.3.7)
- VER SHALL be independent from DES/IMP (M at SIL 3 per EN 50128 §5.3.5)
- TST SHALL NOT also act as VER (independence boundary — separate oversight roles)
- TST SHALL NOT contact QUA, VER, or VAL directly — all submissions through PM

---

## 8. Risks and Mitigation

| Risk | Probability | Impact | Mitigation |
|------|-------------|--------|------------|
| Target hardware (DCU) unavailable for Phase 7 testing | Low | High | Secure hardware during Phase 5; confirm availability with PM |
| WCET exceeds 16 ms target | Medium | Critical | Early WCET monitoring in Phase 5; IMP to refactor if exceeded |
| Coverage targets not met for Statement/Branch | Low | Critical | Monitor coverage continuously during Phase 5 component testing |
| Fault injection harness not ready | Medium | High | Develop and validate harness in Phase 5/6 |
| Critical defects delay Phase 7 exit gate | Medium | High | Allocate buffer; daily defect triage with PM |
| Independent validator (VAL) unavailable | Low | Critical | Schedule VAL participation early; backup validator identified |
| CAN/RS-485 test equipment unavailable | Low | Medium | Confirm equipment availability during Phase 1 planning |

---

## 9. Configuration Management

**This document** is maintained under CM per SCMP (DOC-SCMP-2026-001).
- **Configuration Item ID**: CI-OSTS-001
- **Version control**: Git repository (see SCMP for repository location)
- **Baseline**: Baseline established at Phase 2 gate approval
- **Change control**: All changes to this OSTS after baselining SHALL be processed through the CCB

**Software Under Test (at time of Phase 7 execution)**:
- TDC software version: to be recorded at OSTR compile time
- Git commit SHA: to be recorded in OSTR (Item 24)
- Configuration baseline: to be recorded in OSTR per SCMP

---

## 10. References

### 10.1 Normative References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications — Software for railway control and protection systems |
| **[EN50129]** | EN 50129:2018 Railway applications — Safety related electronic systems for signalling |
| **[EN50126-2]** | EN 50126-2:2017 Railway applications — RAMS — Part 2: Systems approach to safety |
| **[EN14752]** | EN 14752:2015 Railway applications — Bodyside entrance systems |
| **[MISRAC]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |

### 10.2 Project References

| Reference | Document | Status |
|-----------|----------|--------|
| **[SRS]** | Software Requirements Specification, DOC-SRS-2026-001 | Draft (Phase 2) |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 | Approved |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-2026-001 | Approved |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 | Approved |
| **[SVaP]** | Software Validation Plan, DOC-SVaP-2026-001 | Approved |
| **[SSRS]** | System Safety Requirements Specification, DOC-SYS-SAF-2026-001 | Approved Baseline |

---

## Appendix A: Test Environment Configuration

**Hardware Configuration (DCU Test Bench)**:
- 2x STM32H743 MCUs (Channel A and Channel B) interconnected via SPI (10 Mbps)
- CAN bus (250 kbit/s): connected to PEAK PCAN-USB Pro analyser + test PC
- RS-485 bus (115.2 kbit/s): connected to DDU simulator + bus analyser
- GPIO inputs: fault injection harness (sensor simulation board)
- GPIO outputs: oscilloscope probe points (PWM output, direction, lock actuator commands)
- Power supply: bench PSU with controllable power interrupt relay

**Software Configuration**:
- Compiler: arm-none-eabi-gcc 12.x, optimization -O0 for coverage build, -O2 for WCET test
- Build system: CMake + Makefile (per SCMP)
- Test harness: Unity (component) + Python system-level scripts
- Coverage: gcov/lcov/gcovr (statement + branch)
- Result output: JUnit XML + JSON (per §7.6.4.5b requirement)

**Instrumentation Points**:
- GPIO_DBG_CYCLE_START / GPIO_DBG_CYCLE_END: cycle timing
- GPIO_DBG_SAFETY_START / GPIO_DBG_SAFETY_END: safety kernel timing
- GPIO_DBG_OBSTACLE_ISR: obstacle ISR entry (timing from obstacle GPIO rising edge)

---

## Appendix B: Safety Function Test Coverage Summary

| Safety Function | SRS Requirements | Test Cases | Type |
|----------------|-----------------|------------|------|
| SF-001: Speed Interlock | REQ-SAFE-001, 002, 015; REQ-FUN-001, 010; REQ-PERF-002 | TC-OSTS-SAFE-001 to 008; TC-OSTS-BOUND-001 to 003; TC-OSTS-FAULT-001 | Safety, BVA, FI |
| SF-002: Departure Interlock | REQ-SAFE-003; REQ-FUN-009; REQ-PERF-005 | TC-OSTS-SAFE-009 to 011; TC-OSTS-FUNC-025 to 027; TC-OSTS-BOUND-025 | Safety, Functional, BVA |
| SF-003: Obstacle Detection | REQ-SAFE-004; REQ-INT-003; REQ-PERF-003 | TC-OSTS-SAFE-012 to 015; TC-OSTS-FAULT-009; TC-OSTS-BOUND-022 | Safety, FI, BVA |
| SF-004: Safe State | REQ-SAFE-006, 007, 008; REQ-FUN-017 | TC-OSTS-SAFE-019 to 030; TC-OSTS-FAULT-001 to 013 | Safety, FI |
| SF-005: Position Verification | REQ-SAFE-005; REQ-FUN-015; REQ-FUN-005 | TC-OSTS-SAFE-016 to 018; TC-OSTS-FUNC-015 to 018 | Safety, Functional |
| SF-006: Emergency Release | REQ-SAFE-012; REQ-INT-011 | TC-OSTS-SAFE-042 to 044; TC-OSTS-OPS-012 | Safety, Scenario |
| SF-007: Fault Isolation | REQ-FUN-013; REQ-SAFE-018 | TC-OSTS-FUNC-037 to 039; TC-OSTS-SAFE-056, 057; TC-OSTS-OPS-006 | Functional, Safety |

---

## Appendix C: Coverage Analysis Plan

**Statement Coverage (Mandatory SIL 3, Table A.21 Item 1)**:
- Tool: gcov (instrumented with `-fprofile-arcs -ftest-coverage`)
- Report: lcov HTML + gcovr JSON summary
- Target: As defined in SVP/SQAP DOC-SVP-2026-001 (project-defined; not a standard-mandated percentage)
- Exclusions: To be listed in OSTR with justification (expected: CRT0 startup code, HAL hardware stubs)

**Branch Coverage (Mandatory SIL 3, Table A.21 Item 2)**:
- Tool: gcov branch coverage (`-fprofile-arcs`)
- Report: lcov HTML (branch annotation) + gcovr JSON
- Target: As defined in SVP/SQAP DOC-SVP-2026-001
- Analysis: All uncovered branches shall be explained with justification or new test case added

**Compound Condition Coverage (Highly Recommended SIL 3, Table A.21 Item 3)**:
- Tool: gcovr with condition coverage extension (where toolchain supports)
- Report: JSON summary
- Target: As defined in SVP/SQAP DOC-SVP-2026-001
- Note: Compound Condition Coverage is the EN 50128 term (Table A.21 item 3). This is HR (not M) at SIL 3.

**Coverage Gaps**: Any coverage shortfall with respect to SVP/SQAP targets shall be documented in the OSTR with one of:
  (a) additional test case added to close the gap, or
  (b) justified exclusion (dead code, unreachable defensive code) reviewed by VER

---

## Document History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | 2026-04-02 | Software Tester (TST) | Initial draft — Phase 2 OSTS for TDC SIL 3. All 81 requirements from DOC-SRS-2026-001 covered. 267 test cases specified. |

---

**Configuration Item ID**: CI-OSTS-001
**END OF DOCUMENT**
