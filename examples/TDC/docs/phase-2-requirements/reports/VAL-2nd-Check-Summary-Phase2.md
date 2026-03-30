# VAL 2nd-Check Summary — Phase 2 Requirements

**Document ID:** VAL-2NDCHECK-PHASE2-2026-001  
**Version:** 1.0  
**Date:** 2026-03-30  
**Project:** TDC — Train Door Control System  
**SIL Level:** 3  
**Validator:** VAL Agent  
**Phase:** Phase 2 — Requirements Specification

---

## Document Control

| Property | Value |
|----------|-------|
| **Document ID** | VAL-2NDCHECK-PHASE2-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-03-30 |
| **Project** | TDC — Train Door Control System |
| **SIL Level** | 3 |
| **Validator** | VAL Agent |
| **Status** | FINAL — Ready for VMGR Review |

---

## Document Change History

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 1.0 | 2026-03-30 | VAL | Initial 2nd-check review — Phase 2 Track B deliverables | Pending VMGR |

---

## Approvals

**EN 50128 V&V Process — Independent Validation 2nd-Check**

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Validator (VAL)** | VAL Agent | _____________ | 2026-03-30 |
| **V&V Manager (VMGR)** | VMGR | _____________ | Pending |

**Notes:**
- Per EN 50128 §5.3.7 and §5.1.2.8, VAL is **independent** from all development roles (REQ, DES, IMP, TST, INT) at SIL 3
- VAL reports to VMGR (or Safety Authority), **NOT to PM**, per §5.1.2.10f
- VAL's 2nd-check decision is input to VMGR Final V&V Decision; VAL's release decision (AGREE/DISAGREE per §5.1.2.8) is issued in Phase 7 only

---

## 1. Executive Summary

**2nd-Check Scope:** Phase 2 Requirements Specification deliverables — independent validation perspective review

**Documents Reviewed:**
1. **Software Requirements Specification (SRS)** — DOC-SRS-2026-001 v0.1 (Annex C item 6)
2. **Overall Software Test Specification (OTSTSPEC)** — DOC-OTSTSPEC-2026-001 v0.1 (Annex C item 7)
3. **Hazard Log** — DOC-HAZLOG-2026-001 v1.0 (cross-cutting safety artifact)
4. **Software Requirements Verification Report (VER)** — DOC-REQVER-2026-001 v1.0 (Annex C item 8)

**Review Date:** 2026-03-30  
**Validator:** VAL Agent  
**Independence Confirmed:** Yes (SIL 3 mandatory — VAL has not participated in requirements authoring, design, implementation, testing, or verification activities)

---

### 1.1 Overall 2nd-Check Decision

**DECISION:** ✅ **CONCUR WITH VER CONCLUSIONS**

**Summary:**

The Phase 2 Requirements Specification deliverables for the TDC project have been independently reviewed by VAL from the **validation perspective** (system-level testability, acceptance criteria clarity, operational scenario coverage, Phase 7 validation feasibility). All four documents are suitable for Phase 7 validation execution.

**Key Validation Findings:**

1. **SRS (item 6)** — All 53 software requirements are **testable and observable** at system level. Acceptance criteria are clear and measurable. Operational scenarios are adequately covered. Requirements provide sufficient detail for Phase 7 validation test execution. ✅

2. **Overall Software Test Specification (item 7)** — Test strategy fully supports Phase 7 validation objectives. 133 test cases provide comprehensive coverage (100% requirements, 100% hazards). Test environment is adequate (target hardware + TCMS/DDU simulators). Acceptance criteria are well-defined. ✅

3. **Hazard Log** — All 9 hazards have testable safety requirements. Hazard mitigation strategies are verifiable through system-level validation testing (obstacle reversal timing, speed interlock, departure interlock, safe state entry). Hazard-to-validation traceability chain is complete. ✅

4. **VER Verification Report (item 8)** — VER conclusions are **technically sound** and acceptable from validation perspective. VER's three observations (FMEA/FTA deferral, forward traceability reference, boundary test precision) are all reasonable and non-blocking. VAL agrees with VER's **PASS WITH OBSERVATIONS** assessment. ✅

**Concurrence with VER:** VAL **CONCURS** with VER's recommendation to **APPROVE** Phase 2 deliverables for progression to Phase 3 (Architecture and Design).

**Validation Implications for Phase 7:** All Phase 2 deliverables provide solid foundation for Phase 7 validation. No blocking issues identified. No additional validation concerns beyond VER's observations.

---

## 2. Validation Perspective Review

### 2.1 Purpose

This 2nd-check review is performed by VAL per EN 50128 two-track V&V workflow (Track B). The purpose is to review Phase 2 deliverables from the **validation perspective**, focusing on:

- **System-level testability**: Can all requirements be validated in the target operational environment?
- **Acceptance criteria clarity**: Are acceptance criteria measurable and unambiguous for customer acceptance testing?
- **Operational scenario coverage**: Do requirements and test specifications cover realistic railway operational scenarios?
- **Phase 7 feasibility**: Is Phase 7 validation achievable with the defined requirements and test strategy?
- **Hazard validation**: Can all identified hazards be validated through system-level testing?

This 2nd-check review is **distinct from VER's 1st-check verification**. VER focuses on technical correctness, traceability, and compliance. VAL focuses on validation feasibility and customer acceptance readiness.

---

## 3. Deliverable Reviews

### 3.1 Software Requirements Specification (SRS) — Item 6

**Document:** DOC-SRS-2026-001 v0.1 DRAFT  
**Author:** REQ (Requirements Engineer)  
**Status:** QUA PASS ✅, USER APPROVED ✅  
**VER 1st-Check:** APPROVE (part of item 8 verification)

**VAL 2nd-Check Focus:**
- Are all 53 requirements testable and observable in Phase 7 system-level validation?
- Do requirements define clear acceptance criteria for customer acceptance testing?
- Are operational scenarios adequately covered?

---

#### 3.1.1 Validation Testability Assessment

**Result:** ✅ **PASS** — All 53 requirements are testable at system level

**Analysis by Category:**

**Functional Requirements (REQ-FUN-001 to REQ-FUN-008):** 8/8 testable
- **REQ-FUN-001** (Door opening command processing): Testable via TCMS simulator input + door motor command observation. Acceptance criteria clear: "door begins opening within 500 ms; door fully open within 2.5 seconds" ✅
- **REQ-FUN-002** (Door opening execution): Testable via position sensor feedback. Acceptance criteria: "door reaches ≥95% open; fault raised if no progress > 2s" ✅
- **REQ-FUN-003** (Door closing command processing): Testable via TCMS command + obstacle sensor check ✅
- **REQ-FUN-004** (Door closing execution): Testable via position sensor + obstacle injection ✅
- **REQ-FUN-005** (Door locking execution): Testable via lock sensor confirmation. Critical for departure interlock validation ✅
- **REQ-FUN-006** (Door status transmission): Testable via CAN bus monitoring at 10 Hz. Acceptance criteria: "status updated within 100 ms" ✅
- **REQ-FUN-007** (Fault code reporting): Testable via fault injection for each fault code (0x01-0x06, 0xFF) ✅
- **REQ-FUN-008** (Event logging): Testable via SPI flash read-back verification (diagnostic feature) ✅

**Safety Requirements (REQ-SAFE-001 to REQ-SAFE-021):** 21/21 testable
- **REQ-SAFE-001** (Door-locked signal assertion): **Critical for HAZ-001 validation**. Testable via lock sensor confirmation + TCMS CAN signal monitoring. Acceptance criteria: "signal asserted only when ALL doors locked" ✅
- **REQ-SAFE-002** (Redundant lock confirmation): Testable via sensor disagreement injection (lock sensor TRUE but position 10% → SAFE STATE expected) ✅
- **REQ-SAFE-003** (Lock confirmation timeout): Testable via lock sensor timeout injection at 10.0s boundary ✅
- **REQ-SAFE-004** (Continuous obstacle monitoring): Testable via interrupt latency measurement (≤5 ms) ✅
- **REQ-SAFE-005** (Obstacle reversal timing): **Critical for HAZ-002/HAZ-004 validation**. Testable via oscilloscope timing measurement (beam break → motor reversal ≤150 ms). Acceptance criteria quantified. ✅
- **REQ-SAFE-006** (Obstacle sensor fault fail-safe): Testable via sensor disconnection, out-of-range voltage injection ✅
- **REQ-SAFE-007** (Obstacle clearance interlock): Testable via reversal scenario + auto-reclose attempt (should be rejected) ✅
- **REQ-SAFE-008** (Speed interlock enforcement): **Critical for HAZ-003 validation**. Testable via boundary value tests (4/5/6 km/h) ✅
- **REQ-SAFE-009** (Speed data validation): Testable via CRC error, timeout, out-of-range injection ✅
- **REQ-SAFE-010** (Speed threshold protection): Testable via static analysis (const declaration verification) ✅
- **REQ-SAFE-011** (State machine direct transition): Testable via WCET analysis + timing measurement (≤20 ms) ✅
- **REQ-SAFE-012** (Safe state entry conditions): Testable via fault injection (cross-channel disagreement, watchdog timeout, CRC error, sensor out-of-range, stack overflow) ✅
- **REQ-SAFE-013** (Safe state action sequence): Testable via safe state trigger + output verification (motors 0V, locks 24V, signals correct) within 10 ms ✅
- **REQ-SAFE-014** (Safe state exit interlock): Testable via reset command with/without confirmation code (0xA5C3) ✅
- **REQ-SAFE-015** (Immediate lock loss de-assertion): Testable via timing measurement (≤10 ms from lock sensor FALSE to signal de-asserted) ✅
- **REQ-SAFE-016** (Cyclic lock monitoring rate): Testable via timing analysis (10 ms control cycle verification) ✅
- **REQ-SAFE-017** (Door fault isolation): Testable via persistent fault injection + isolation verification (SIL 2) ✅
- **REQ-SAFE-018** (Isolated door reporting): Testable via TCMS CAN message verification (SIL 2) ✅
- **REQ-SAFE-019** (Emergency release monitoring): Testable via emergency release sensor activation (SIL 2) ✅
- **REQ-SAFE-020** (Emergency release alert): Testable via alert timing measurement (≤500 ms) (SIL 2) ✅
- **REQ-SAFE-021** (Safe state WCET): Testable via WCET analysis + execution time measurement (≤5 ms) ✅

**Performance Requirements (REQ-PERF-001 to REQ-PERF-006):** 6/6 testable
- All performance requirements have quantified targets (10 ms cycle, 150 ms obstacle response, 100 ms status update, 70% CPU, 256 KB RAM, 512 KB ROM, 51 KB stack) ✅
- All are measurable with standard profiling tools (oscilloscope, ARM Keil MDK, gcov/lcov) ✅

**Interface Requirements (REQ-INT-001 to REQ-INT-009):** 9/9 testable
- All hardware/software interfaces testable via interface testing (CAN analyzer, RS-485 monitor, GPIO oscilloscope, SPI logic analyzer) ✅

**Implementation Requirements (REQ-IMPL-001 to REQ-IMPL-009):** 9/9 testable
- MISRA C, static allocation, no recursion, complexity ≤10, coverage targets — all verifiable via static/dynamic analysis tools ✅

**Conclusion:** All 53 requirements are **testable and observable** at system level in Phase 7 validation environment.

---

#### 3.1.2 Acceptance Criteria Clarity

**Result:** ✅ **PASS** — All requirements have clear, measurable acceptance criteria

**Evidence:**
- All functional requirements have quantified timing criteria (500 ms, 2.5s, 3.5s)
- All safety requirements have measurable pass/fail criteria (150 ms, 10 ms, 10s, 5 km/h)
- All performance requirements have numerical targets (10 ms, 70%, 256 KB)
- No ambiguous criteria identified (e.g., "fast", "responsive", "timely")

**Customer Acceptance Readiness:** Acceptance criteria are sufficiently clear for customer acceptance testing (TC-VAL-ACC-001 to TC-VAL-ACC-006). Customer can objectively assess pass/fail for each acceptance test case.

---

#### 3.1.3 Operational Scenario Coverage

**Result:** ✅ **PASS** — Operational scenarios adequately covered

**Operational Scenarios Identified in SRS:**
1. Normal door cycle (open → close → lock → train departure) — §2.4 state machine ✅
2. Obstacle detection and reversal during closing — §4.3 REQ-SAFE-005 ✅
3. Speed interlock enforcement (door opening inhibited above 5 km/h) — §4.1 REQ-SAFE-008 ✅
4. Departure interlock (door-locked signal prevents departure with door open) — §4.2 REQ-SAFE-001 ✅
5. Safe state entry on fault detection — §4.4 REQ-SAFE-012/013 ✅
6. Safe state recovery after operator reset — §4.4 REQ-SAFE-014 ✅
7. Degraded mode operation (fault isolation, one door defective) — §4.4 REQ-SAFE-017 ✅
8. Emergency release monitoring — §4.4 REQ-SAFE-019/020 ✅

**Coverage Assessment:** All critical railway operational scenarios are represented in requirements. Sufficient for realistic Phase 7 validation testing.

---

#### 3.1.4 VAL-Specific Observations on SRS

**No blocking issues identified.**

**Minor Observation VAL-OBS-SRS-001 (Advisory, Non-Blocking):**
- **Description:** REQ-SAFE-005 (obstacle reversal timing) specifies 150 ms end-to-end response time. SRS provides timing budget breakdown (5 ms interrupt latency + 20 ms software + 125 ms DDU mechanical). This is excellent for implementation guidance. However, **validation perspective**: Phase 7 validation will measure **end-to-end observable timing** (beam break sensor input to observable motor direction reversal output). Validation will NOT directly measure internal software processing time (20 ms). Internal timing budget is VER/TST responsibility (Phase 5 unit testing + WCET analysis).
- **Recommendation:** Overall Software Test Specification correctly specifies end-to-end measurement (TC-VAL-SAFE-018, TC-VAL-PERF-003). No action required for Phase 2. VAL will focus on end-to-end observable timing in Phase 7.
- **Impact:** None. Clarifies validation scope. Not a defect.

**Minor Observation VAL-OBS-SRS-002 (Advisory, Non-Blocking):**
- **Description:** REQ-FUN-005 (door locking execution) and REQ-SAFE-001 (door-locked signal assertion) are **critical for HAZ-001 and HAZ-005 mitigation** (train departure with door open). These requirements will be subject to **intensive acceptance testing** in Phase 7 with customer participation. Validation will require **repeated trials** (e.g., 100 door lock cycles) to demonstrate reliability and repeatability.
- **Recommendation:** Overall Software Test Specification §3.10 Acceptance Test Cases include TC-VAL-ACC-004 (departure interlock demonstration). VAL recommends TST plan for **statistical validation** (e.g., 100 trials, 0 failures) in Phase 7. Not blocking for Phase 2.
- **Impact:** None. Advance planning for Phase 7 acceptance testing.

**Conclusion:** SRS is **suitable for Phase 7 validation** from validation perspective. No blocking issues. Two minor advisory observations for Phase 7 planning only.

---

### 3.2 Overall Software Test Specification (OTSTSPEC) — Item 7

**Document:** DOC-OTSTSPEC-2026-001 v0.1 DRAFT  
**Author:** TST (Software Tester)  
**Status:** QUA PASS ✅  
**VER 1st-Check:** APPROVE (part of item 8 verification)

**VAL 2nd-Check Focus:**
- Does test strategy support Phase 7 validation objectives?
- Are test environments and tools adequate for validation?
- Are acceptance criteria clear for customer acceptance testing?
- Is Phase 7 validation feasible with this test specification?

---

#### 3.2.1 Test Strategy Assessment

**Result:** ✅ **PASS** — Test strategy fully supports Phase 7 validation

**Validation Objectives Coverage:**

| Validation Objective | OTSTSPEC Coverage | Status |
|---------------------|-------------------|--------|
| Functional validation (black-box testing) | §3.2 Functional Test Cases (16 test cases) + §2.1 Table A.7 technique applied (M SIL 3) | ✅ |
| Performance validation (timing, WCET, resource usage) | §3.4 Performance Test Cases (8 test cases) + §2.1 Table A.7 technique applied (M SIL 3) | ✅ |
| Operational scenario validation | §3.7 Operational Scenario Test Cases (10 test cases) covering normal, degraded, fault recovery, extended duration | ✅ |
| Safety-critical function validation | §3.3 Safety Test Cases (37 test cases) covering all 21 REQ-SAFE-xxx requirements | ✅ |
| Acceptance testing (customer participation) | §3.10 Acceptance Test Cases (6 test cases) with customer demonstration | ✅ |
| Boundary value validation | §3.8 Boundary Test Cases (21 test cases) + §2.1 Table A.7 technique applied (M SIL 3) | ✅ |
| Regression validation | §3.9 Regression Test Cases (6 test cases) + §2.1 Table A.7 technique applied (M SIL 3) | ✅ |

**EN 50128 Table A.7 Compliance (SIL 3 Mandatory Techniques):**
- ✅ Functional and Black-Box Testing (Item 2, M SIL 3) — Applied
- ✅ Performance Testing (Item 1, M SIL 3) — Applied
- ✅ Boundary Value Analysis (Item 6, M SIL 3) — Applied
- ✅ Regression Testing (Item 4, M SIL 3) — Applied

**Validation Strategy:** Black-box testing based on SRS requirements, operational scenario-based testing, performance and resource testing, safety-critical function testing, acceptance testing with customer participation. This strategy is **appropriate and sufficient** for SIL 3 railway software validation.

---

#### 3.2.2 Test Environment Adequacy

**Result:** ✅ **PASS** — Test environment is adequate for Phase 7 validation

**Test Environment Specification (§2.2):**
- **Target Hardware:** STM32H743 dual-channel DCU (2oo2 architecture) — Correct target platform ✅
- **Operating System:** Bare-metal with real-time scheduler — Matches production environment ✅
- **Test Tools:** Unity test framework, CAN analyzer (Vector CANalyzer), oscilloscope (Tektronix MDO4000), ARM Keil MDK-ARM, gcov/lcov, TCMS/DDU simulator (Python-based) ✅
- **Environmental Conditions:** -40°C to +85°C (railway operational range per EN 50155), 24V DC nominal (18-32V range) ✅

**Validation Feasibility:** Test environment provides **realistic operational conditions** for validation. TCMS/DDU simulators enable controlled test scenarios. Oscilloscope + CAN analyzer enable timing measurements (critical for REQ-SAFE-005 obstacle reversal 150 ms requirement). Hardware-in-the-loop testing on target DCU platform ensures validation reflects production environment.

**Observation VAL-OBS-OTSTSPEC-001 (Advisory, Non-Blocking):**
- **Description:** §2.2 specifies TCMS/DDU simulators (Python-based RS-485/CAN stimulus generator). Validation requires **accurate simulation** of TCMS speed signal timing (10 Hz update rate per REQ-INT-005), DDU position feedback timing (50 Hz per REQ-INT-001), and obstacle sensor interrupt timing (hardware GPIO). Simulator accuracy and latency should be characterized before Phase 7 validation execution.
- **Recommendation:** TST to perform **simulator validation** in Phase 6 (Integration) or early Phase 7. Document simulator accuracy and latency characteristics. Ensure simulators introduce < 1 ms additional latency (negligible compared to 150 ms obstacle reversal requirement).
- **Impact:** Low. Simulator validation is good engineering practice. Not blocking for Phase 2 approval.

---

#### 3.2.3 Acceptance Criteria Clarity

**Result:** ✅ **PASS** — Acceptance criteria are clear and customer-ready

**Acceptance Test Cases (§3.10):**
- **TC-VAL-ACC-001** (Door operates safely under all operational scenarios): Clear demonstration objective — "normal door cycle (open/close/lock) with customer observation" ✅
- **TC-VAL-ACC-002** (Speed interlock prevents door opening above 5 km/h): Quantified acceptance criteria — "demonstrate with varying speed inputs (0, 5, 10 km/h)" ✅
- **TC-VAL-ACC-003** (Obstacle detection reverses door within 150 ms): Measurable acceptance criteria — "demonstrate with timing measurement (oscilloscope)" ✅
- **TC-VAL-ACC-004** (Door-locked signal prevents departure with door open): Unambiguous acceptance criteria — "locked signal only when all doors locked" ✅
- **TC-VAL-ACC-005** (Safe state entered on fault detection): Verifiable acceptance criteria — "demonstrate for cross-channel disagreement, watchdog timeout" ✅
- **TC-VAL-ACC-006** (System recovers from safe state after operator reset): Clear acceptance criteria — "demonstrate safe state recovery sequence" ✅

**Customer Acceptance Readiness:** All acceptance test cases are **suitable for customer demonstration** and acceptance sign-off. Acceptance criteria are objective and measurable.

---

#### 3.2.4 Phase 7 Validation Feasibility

**Result:** ✅ **PASS** — Phase 7 validation is feasible with this test specification

**Feasibility Assessment:**

| Aspect | Assessment | Status |
|--------|------------|--------|
| Test case completeness | 133 test cases cover 100% of 53 requirements (VER verified in item 8) | ✅ |
| Test environment availability | Target hardware (DCU), simulators (TCMS/DDU), test tools (CAN analyzer, oscilloscope) specified | ✅ |
| Test execution duration | §6.1 estimates 15 days test execution + 10 days defect resolution + 5 days regression — reasonable for 133 test cases | ✅ |
| Resource allocation | §7 Roles and Responsibilities: TST (test execution), VAL (acceptance testing, validation approval), VMGR (V&V approval) — adequate staffing | ✅ |
| Coverage targets | §2.4: Statement 100%, Branch 100%, Compound Condition per SVP target — achievable with comprehensive test suite | ✅ |
| Entry criteria | §2.3: Integration testing complete, HW/SW integration complete, test environment configured, traceability matrix 100%, VAL assigned — clear and achievable | ✅ |
| Exit criteria | §2.3: All test cases executed, all mandatory tests passed, coverage targets met, VAL approval obtained, VMGR approval obtained — clear and appropriate | ✅ |

**Conclusion:** Phase 7 validation is **feasible and achievable** with this test specification. No blocking issues identified.

---

#### 3.2.5 VAL-Specific Observations on OTSTSPEC

**Minor Observation VAL-OBS-OTSTSPEC-002 (Advisory, Non-Blocking):**
- **Description:** §2.4 Coverage Requirements states "EN 50128:2011 Table A.21 Req.1 requires a quantified coverage target to be defined per project in the SVP/SQAP. There is **NO mandatory percentage threshold in the standard**." This is **technically correct**. However, the TDC project has selected **100% statement, branch, and compound condition coverage** as project targets (per SVP). This is **excellent and appropriate for SIL 3**.
- **Validation Perspective:** VAL will verify in Phase 7 that **coverage targets are met** as part of exit criteria (§2.3 Exit Criteria checkbox: "Coverage targets met"). VAL does not perform coverage measurement (TST responsibility) but will **review coverage reports** to confirm targets achieved.
- **Recommendation:** No action required for Phase 2. TST to provide coverage reports (HTML lcov report + summary table) in Overall Software Test Report (item 24) for VAL review in Phase 7.
- **Impact:** None. Clarifies VAL's coverage review role in Phase 7.

**Minor Observation VAL-OBS-OTSTSPEC-003 (Agrees with VER OBS-003, Non-Blocking):**
- **Description:** VER OBS-003 notes that boundary test cases (§3.8) test speed thresholds at 4, 5, 6 km/h, but should also include 5.0 km/h and 5.1 km/h for sub-integer boundary precision validation.
- **VAL Concurrence:** VAL **agrees with VER OBS-003**. Boundary value analysis is **mandatory for SIL 3** (Table A.7 Item 6). Sub-integer boundary testing (5.0 vs. 5.1 km/h) provides additional confidence in speed interlock precision (HAZ-003 mitigation).
- **Recommendation:** Same as VER OBS-003 — TST to add sub-integer boundary test in Phase 7 if sensor precision supports it. Not blocking for Phase 2.
- **Impact:** Low. Enhancement for boundary testing rigor. Not a defect.

**Conclusion:** OTSTSPEC is **suitable for Phase 7 validation execution** from validation perspective. No blocking issues. Two minor advisory observations (simulator validation, coverage review role) for Phase 7 planning only.

---

### 3.3 Hazard Log — Cross-Cutting Safety Artifact

**Document:** DOC-HAZLOG-2026-001 v1.0 DRAFT  
**Author:** SAF (Safety Engineer)  
**Status:** QUA PASS ✅  
**VER 1st-Check:** APPROVE (part of item 8 verification)

**VAL 2nd-Check Focus:**
- Can all identified hazards be validated through system-level testing in Phase 7?
- Are hazard mitigation strategies verifiable through validation?
- Is hazard-to-validation traceability complete?

---

#### 3.3.1 Hazard Validation Feasibility

**Result:** ✅ **PASS** — All 9 hazards are validatable at system level

**Hazard-by-Hazard Validation Assessment:**

| Hazard ID | SIL | Validation Feasibility | Phase 7 Test Cases | Status |
|-----------|-----|------------------------|-------------------|--------|
| **HAZ-001** (Train departs with door open) | 3 | **Validatable** — Test departure interlock: inject unlock event during LOCKED state → verify door-locked signal de-asserted immediately (≤10 ms) → verify TCMS does not grant departure authority | TC-VAL-SAFE-008, TC-VAL-SAFE-009, TC-VAL-SAFE-014, TC-VAL-FUNC-012, TC-VAL-ACC-004 | ✅ |
| **HAZ-002** (Door closes on passenger) | 3 | **Validatable** — Test obstacle detection: inject obstacle during closing → measure reversal time (≤150 ms) → verify door transitions to REVERSING | TC-VAL-SAFE-016, TC-VAL-SAFE-017, TC-VAL-SAFE-018, TC-VAL-SAFE-019, TC-VAL-PERF-003, TC-VAL-ACC-003 | ✅ |
| **HAZ-003** (Door opens while train moving) | 3 | **Validatable** — Test speed interlock: inject speed > 5 km/h → attempt open command → verify open command rejected | TC-VAL-SAFE-001, TC-VAL-SAFE-002, TC-VAL-SAFE-003, TC-VAL-BOUND-001/002/003, TC-VAL-ACC-002 | ✅ |
| **HAZ-004** (Obstacle detected but door continues) | 3 | **Validatable** — Same as HAZ-002 (software reversal failure scenario) | TC-VAL-SAFE-018, TC-VAL-SAFE-024, TC-VAL-ACC-003 | ✅ |
| **HAZ-005** (False door-locked signal) | 3 | **Validatable** — Test door-locked signal integrity: inject lock sensor disagreement, cross-channel disagreement, lock loss during monitoring → verify signal NOT asserted or de-asserted immediately | TC-VAL-SAFE-008, TC-VAL-SAFE-010, TC-VAL-SAFE-012, TC-VAL-SAFE-014, TC-VAL-ACC-004 | ✅ |
| **HAZ-006** (Fault isolation failure) | 2 | **Validatable** — Test fault isolation: inject persistent fault on one door → verify door isolated → verify other doors continue operation | TC-VAL-SAFE-034, TC-VAL-SAFE-035, TC-VAL-OPS-005 | ✅ |
| **HAZ-007** (Operational delay) | 0 | **Not applicable** — SIL 0 availability concern, not safety-critical; no validation required | N/A | N/A |
| **HAZ-008** (Emergency release monitoring failure) | 2 | **Validatable** — Test emergency release monitoring: activate emergency release → verify TCMS alert within 500 ms → verify event logged | TC-VAL-SAFE-036, TC-VAL-SAFE-037, TC-VAL-OPS-007 | ✅ |
| **HAZ-009** (Software fault leads to uncontrolled operation) | 3 | **Validatable** — Test safe state entry: inject faults (cross-channel disagreement, watchdog timeout, CRC error, stack overflow) → verify safe state entered within 10 ms → verify safe state actions correct | TC-VAL-SAFE-025 to TC-VAL-SAFE-033, TC-VAL-ACC-005, TC-VAL-ACC-006 | ✅ |

**Conclusion:** All 8 safety-relevant hazards (HAZ-001 to HAZ-006, HAZ-008, HAZ-009; excluding HAZ-007 SIL 0) are **validatable through system-level testing** in Phase 7. Overall Software Test Specification provides complete test case coverage for all hazards.

---

#### 3.3.2 Hazard Mitigation Verification

**Result:** ✅ **PASS** — All hazard mitigation strategies are verifiable through validation

**Critical Mitigation Strategies:**

1. **HAZ-001/HAZ-005 Mitigation (Departure Interlock):**
   - **Mitigations:** REQ-SAFE-001 (door-locked signal assertion condition), REQ-SAFE-002 (redundant lock sensors), REQ-SAFE-003 (lock timeout), REQ-SAFE-015 (immediate de-assertion), REQ-SAFE-016 (cyclic monitoring)
   - **Validation Strategy:** Verify door-locked signal behavior under all conditions (all doors locked, one door unlocked, lock loss during monitoring, sensor disagreement, cross-channel disagreement) ✅
   - **Test Cases:** TC-VAL-SAFE-008 to TC-VAL-SAFE-015, TC-VAL-ACC-004 ✅

2. **HAZ-002/HAZ-004 Mitigation (Obstacle Detection):**
   - **Mitigations:** REQ-SAFE-004 (continuous monitoring), REQ-SAFE-005 (reversal timing ≤150 ms), REQ-SAFE-006 (sensor fault fail-safe), REQ-SAFE-007 (clearance interlock), REQ-SAFE-011 (direct state transition)
   - **Validation Strategy:** Verify obstacle detection response time (end-to-end timing measurement), verify fail-safe behavior on sensor fault, verify no auto-reclose after reversal ✅
   - **Test Cases:** TC-VAL-SAFE-016 to TC-VAL-SAFE-024, TC-VAL-PERF-003, TC-VAL-ACC-003 ✅

3. **HAZ-003 Mitigation (Speed Interlock):**
   - **Mitigations:** REQ-SAFE-008 (speed interlock enforcement), REQ-SAFE-009 (speed data validation), REQ-SAFE-010 (threshold protection)
   - **Validation Strategy:** Verify speed interlock at boundary values (4/5/6 km/h), verify fail-safe behavior on invalid speed data (CRC error, timeout, out-of-range) ✅
   - **Test Cases:** TC-VAL-SAFE-001 to TC-VAL-SAFE-007, TC-VAL-BOUND-001 to TC-VAL-BOUND-006, TC-VAL-ACC-002 ✅

4. **HAZ-005/HAZ-009 Mitigation (Safe State Management):**
   - **Mitigations:** REQ-SAFE-012 (safe state entry conditions), REQ-SAFE-013 (safe state action sequence), REQ-SAFE-014 (safe state exit interlock), REQ-SAFE-021 (safe state WCET)
   - **Validation Strategy:** Verify safe state entry on all fault conditions, verify safe state actions (motors off, locks on, signals correct), verify no autonomous recovery, verify timing (≤10 ms) ✅
   - **Test Cases:** TC-VAL-SAFE-025 to TC-VAL-SAFE-033, TC-VAL-ACC-005, TC-VAL-ACC-006 ✅

**Conclusion:** All hazard mitigation strategies are **verifiable through system-level validation testing**. Test cases provide comprehensive coverage of all mitigation requirements.

---

#### 3.3.3 Hazard-to-Validation Traceability

**Result:** ✅ **PASS** — Hazard-to-validation traceability chain is complete

**Traceability Chain:**
```
Hazard (HAZ-xxx) → System Safety Function (SF-xxx) → System Safety Requirement (SSR-xxx) → 
Software Safety Requirement (REQ-SAFE-xxx) → Validation Test Case (TC-VAL-SAFE-xxx, TC-VAL-ACC-xxx)
```

**Evidence:**
- Hazard Log §4 Traceability Matrix: HAZ-xxx → SSR-xxx → REQ-SAFE-xxx (T2 traceability) ✅
- SRS Section 4: REQ-SAFE-xxx → HAZ-xxx (reverse T2) ✅
- OTSTSPEC §4.1 Traceability Matrix: REQ-SAFE-xxx → TC-VAL-xxx (T3 traceability) ✅
- VER Report §5.2: Verified T2 traceability 100% complete ✅
- VER Report §5.3: Verified T3 traceability 100% complete (21/21 safety requirements have test cases) ✅

**Conclusion:** Hazard-to-validation traceability chain is **100% complete**. All hazards are traceable to validation test cases via safety requirements.

---

#### 3.3.4 VAL-Specific Observations on Hazard Log

**Minor Observation VAL-OBS-HAZLOG-001 (Agrees with VER OBS-001, Non-Blocking):**
- **Description:** VER OBS-001 notes that FMEA/FTA/CCF analysis is deferred to Phase 3 per Hazard Log §1.3. EN 50126-2:2017 allows FMEA/FTA after initial hazard identification. CCF is HR, not M.
- **VAL Concurrence:** VAL **agrees with VER OBS-001**. From validation perspective, hazard identification is complete in Phase 2. FMEA/FTA will provide additional failure mode analysis depth in Phase 3, which may identify **additional failure scenarios** to be tested in Phase 7 validation. However, the 9 identified hazards and their mitigation strategies are sufficient for Phase 2 approval.
- **Validation Impact:** Low. FMEA/FTA may reveal additional test scenarios in Phase 3. VAL will review Phase 3 FMEA/FTA reports and confirm that any new failure scenarios are added to validation test suite.
- **Recommendation:** Same as VER OBS-001 — SAF to complete FMEA/FTA in Phase 3; VER to verify FMEA/FTA reports in Phase 3 Verification Report (item 14); VAL to review for validation test implications.
- **Impact:** None for Phase 2. Action deferred to Phase 3.

**Conclusion:** Hazard Log is **suitable for Phase 7 validation planning** from validation perspective. No blocking issues. One minor observation (FMEA/FTA deferral) acknowledged and deferred to Phase 3.

---

### 3.4 VER Software Requirements Verification Report — Item 8

**Document:** DOC-REQVER-2026-001 v1.0  
**Author:** VER (Software Verifier)  
**Status:** QUA PASS ✅, VMGR APPROVED ✅ (2026-03-30)  
**VER Decision:** **PASS WITH OBSERVATIONS** (3 observations: OBS-001, OBS-002, OBS-003)

**VAL 2nd-Check Focus:**
- Do you agree with VER's findings and conclusions?
- Are VER's observations acceptable from a validation perspective?
- Any additional concerns for Phase 7 validation?

---

#### 3.4.1 Agreement with VER Conclusions

**Result:** ✅ **CONCUR** — VAL agrees with VER conclusions

**VER Overall Assessment (from VER Report §11.1):**
> "The Phase 2 Requirements Specification deliverables for the TDC project (SRS, Hazard Log, Overall Software Test Specification) have been independently verified by VER and are **COMPLIANT** with EN 50128:2011 requirements for SIL 3 railway software."
>
> "Recommendation: **APPROVE** for progression to Phase 3 (Architecture and Design)."

**VAL Concurrence Statement:**

VAL **CONCURS** with VER's overall assessment. From the **validation perspective**, all Phase 2 deliverables are **suitable for Phase 7 validation execution** and provide a solid foundation for system-level validation testing. VER's verification has been thorough and technically sound.

**Specific Agreement Points:**

1. **Traceability Completeness:** VAL agrees with VER's finding that T1 (System ↔ Software), T2 (Hazard → Safety Req), and T3 (Req → Test) are all 100% complete (VER Report §5.1, §5.2, §5.3, §7.1). This is **essential for validation** to ensure all hazards are validated and all requirements are tested. ✅

2. **Requirements Quality:** VAL agrees with VER's assessment that all 53 requirements are testable, unambiguous, and have clear acceptance criteria (VER Report §5.1). This is **critical for Phase 7 validation** to execute tests and assess pass/fail objectively. ✅

3. **Test Coverage:** VAL agrees with VER's finding that Overall Software Test Specification provides 100% requirements coverage (53/53) and 100% hazards coverage (9/9) (VER Report §5.3). This is **mandatory for SIL 3** and necessary for comprehensive validation. ✅

4. **EN 50128 Compliance:** VAL agrees with VER's assessment that all Phase 2 deliverables apply mandatory EN 50128 techniques for SIL 3 (Table A.2 for requirements, Table A.7 for testing) (VER Report §8.1, §5.3). ✅

5. **Independence:** VAL agrees with VER's confirmation that VER is independent from REQ, DES, IMP, TST, and INT per SIL 3 requirements (VER Report §2.4, §8.2). VAL also confirms that VAL is independent from all development and testing roles per SIL 3 requirements. ✅

---

#### 3.4.2 Review of VER Observations

**VER reported 3 observations (VER Report §6.4):**

**VER OBS-001: FMEA/FTA/CCF Deferral**
- **VER Description:** FMEA/FTA/CCF analysis deferred to Phase 3 per Hazard Log §1.3. EN 50126-2:2017 allows FMEA/FTA after initial hazard identification. CCF is HR, not M.
- **VER Resolution:** Acceptable for Phase 2. VER will verify FMEA/FTA reports in Phase 3 Verification Report (item 14).
- **VAL Perspective:** VAL **AGREES** with VER OBS-001. See VAL-OBS-HAZLOG-001 above. FMEA/FTA deferral is acceptable. Hazard identification is complete. No validation blocking issues.
- **VAL Concurrence:** ✅ **ACCEPTABLE**

**VER OBS-002: Hazard-to-Validation Traceability Forward Reference**
- **VER Description:** Overall Software Test Specification §4.1 traceability matrix references validation test execution results (Phase 7 future activity). Forward reference is acceptable but should be noted.
- **VER Resolution:** Acceptable. Overall Test Specification produced in Phase 2 defines tests to be executed in Phase 7. Forward reference is correct per V-Model. VAL will execute tests and produce Overall Software Test Report (item 24) in Phase 7.
- **VAL Perspective:** VAL **AGREES** with VER OBS-002. Phase 2 Overall Software Test Specification **defines the tests** (test cases, test strategy, acceptance criteria). Phase 7 Overall Software Test Report (item 24) will **document test execution results** (pass/fail, defects found, coverage achieved, validation conclusion). This is **correct V-Model flow**: specification (Phase 2) → execution (Phase 7). Forward reference is appropriate.
- **VAL Concurrence:** ✅ **ACCEPTABLE** — This is standard V-Model practice. VAL will produce Overall Software Test Report (item 24) in Phase 7 after test execution.

**VER OBS-003: Boundary Test Case Precision**
- **VER Description:** Boundary test cases (§3.8) test speed thresholds at 4, 5, 6 km/h. SIL 3 boundary value analysis should also include 5.0 km/h and 5.1 km/h for precision validation (sub-integer boundary).
- **VER Resolution:** Acceptable for Phase 2 specification. TST to add sub-integer boundary test (5.0/5.1 km/h) in Phase 7 test execution if sensor precision supports it. Not blocking for Phase 2 approval.
- **VAL Perspective:** VAL **AGREES** with VER OBS-003. See VAL-OBS-OTSTSPEC-003 above. Sub-integer boundary testing (5.0 vs. 5.1 km/h) provides additional confidence in speed interlock precision (HAZ-003 mitigation). This is **good validation practice** for safety-critical thresholds. VAL recommends TST consider this enhancement in Phase 7.
- **VAL Concurrence:** ✅ **ACCEPTABLE** — Enhancement recommended for Phase 7, not blocking for Phase 2.

**Conclusion on VER Observations:** VAL **CONCURS** with all three VER observations. All observations are reasonable, non-blocking, and have appropriate resolutions. No disagreements with VER.

---

#### 3.4.3 Additional VAL Concerns for Phase 7

**Result:** ✅ **NO ADDITIONAL CONCERNS**

**VAL Assessment:**

VAL has reviewed all Phase 2 deliverables from the validation perspective and has identified **no additional concerns** beyond VER's observations. All validation concerns have been addressed:

1. **Validation testability:** All requirements are testable at system level ✅
2. **Acceptance criteria clarity:** All requirements have clear, measurable acceptance criteria ✅
3. **Operational scenario coverage:** All critical railway scenarios covered ✅
4. **Phase 7 feasibility:** Validation is feasible with defined test specification and environment ✅
5. **Hazard validation:** All hazards are validatable through system-level testing ✅
6. **Traceability completeness:** Hazard-to-validation traceability chain is 100% complete ✅

**VAL-Specific Observations (3 advisory, non-blocking):**
- **VAL-OBS-SRS-001:** Clarifies end-to-end vs. internal timing measurement for validation (advisory)
- **VAL-OBS-SRS-002:** Recommends statistical validation for critical lock functionality (advisory)
- **VAL-OBS-OTSTSPEC-001:** Recommends simulator accuracy characterization (advisory)
- **VAL-OBS-OTSTSPEC-002:** Clarifies VAL's coverage review role (advisory)
- **VAL-OBS-OTSTSPEC-003:** Agrees with VER OBS-003 on sub-integer boundary testing (advisory)
- **VAL-OBS-HAZLOG-001:** Agrees with VER OBS-001 on FMEA/FTA deferral (advisory)

All VAL observations are **advisory only** and do not block Phase 2 approval.

---

## 4. Overall VAL 2nd-Check Decision

### 4.1 Validation Perspective Summary

From the **validation perspective** (system-level testability, acceptance criteria clarity, operational scenario coverage, Phase 7 feasibility), all Phase 2 Requirements Specification deliverables for the TDC project are **ACCEPTABLE** for progression to Phase 3 (Architecture and Design).

**Key Validation Strengths:**

1. ✅ **All 53 requirements are testable and observable** at system level in Phase 7 validation environment
2. ✅ **Acceptance criteria are clear and measurable** for customer acceptance testing
3. ✅ **Operational scenarios are adequately covered** for realistic railway validation
4. ✅ **Phase 7 validation is feasible** with defined test specification, test environment, and test tools
5. ✅ **All 9 hazards are validatable** through system-level testing; mitigation strategies are verifiable
6. ✅ **Hazard-to-validation traceability is 100% complete** (HAZ → SSR → REQ-SAFE → TC-VAL)
7. ✅ **Test coverage is 100%** for requirements and hazards per SIL 3 mandatory requirement
8. ✅ **EN 50128 compliance** for all mandatory SIL 3 techniques (Table A.2, Table A.7)

**Observations:** 6 advisory observations identified by VAL (all non-blocking). All observations have appropriate resolutions or are deferred to later phases.

**Concurrence with VER:** VAL **CONCURS** with VER's verification conclusions and **AGREES** with all three VER observations (OBS-001, OBS-002, OBS-003). No disagreements with VER.

---

### 4.2 Formal VAL 2nd-Check Decision

**DECISION:** ✅ **CONCUR WITH VER CONCLUSIONS**

**Recommendation:** **APPROVE** Phase 2 deliverables for progression to Phase 3 (Architecture and Design).

**Rationale:**

1. All Phase 2 deliverables (SRS, Overall Software Test Specification, Hazard Log, VER Verification Report) are **suitable for Phase 7 validation** from the validation perspective.

2. VER's independent verification has been **thorough and technically sound**. VAL concurs with VER's findings, observations, and recommendation.

3. All SIL 3 mandatory requirements are met: traceability 100% complete, requirements testable, test coverage 100%, EN 50128 techniques applied, independence confirmed.

4. No blocking issues identified by VAL. All VAL observations are advisory and non-blocking.

5. Phase 7 validation is **feasible and achievable** with the defined requirements, test strategy, test environment, and acceptance criteria.

---

### 4.3 Validation Implications for Phase 7

**Phase 7 Validation Planning:**

When Phase 7 (Validation) is reached, VAL will perform the following activities based on Phase 2 deliverables:

1. **Execute Validation Tests:** Execute 133 test cases per Overall Software Test Specification (item 7)
   - Focus on system-level functional validation, performance validation, operational scenario validation, safety-critical function validation
   - Measure end-to-end observable timing (obstacle reversal ≤150 ms, lock loss de-assertion ≤10 ms)
   - Verify acceptance criteria for all requirements

2. **Conduct Acceptance Testing:** Execute 6 acceptance test cases (TC-VAL-ACC-001 to TC-VAL-ACC-006) with customer participation
   - Demonstrate speed interlock, obstacle reversal, departure interlock, safe state management
   - Obtain customer acceptance sign-off

3. **Verify Hazard Mitigation:** Validate all 9 hazards through system-level testing
   - Confirm hazard mitigation strategies are effective in target operational environment
   - Verify residual risk is tolerable per EN 50126 ALARP principle

4. **Review Coverage Reports:** Review coverage reports from TST (statement, branch, compound condition coverage)
   - Confirm coverage targets met per SVP (100% statement, 100% branch, compound condition per SVP target)
   - Review coverage exclusions if any (must be justified)

5. **Issue Validation Reports:** Author Phase 7 validation deliverables
   - Software Validation Report (item 25) per §7.7.4.6–7.7.4.11
   - Tools Validation Report (item 26) if tool qualification required
   - Release Note (item 27) per §7.7.4.12

6. **Issue Release Decision:** Issue VAL release decision per §5.1.2.8
   - **AGREE** for software release (if all validation criteria met) OR
   - **DISAGREE** to block release (if validation criteria not met)
   - This decision is **FINAL** and cannot be overridden by PM, COD, or VMGR

**No Changes Required to Phase 2 Deliverables:** VAL confirms that Phase 2 deliverables provide sufficient information for Phase 7 validation planning and execution. No revisions to SRS, Overall Software Test Specification, or Hazard Log are required at this time.

---

## 5. Conditions for Phase 3 Progression

**VAL 2nd-Check Approval Conditions:**

- [x] All critical defects resolved (None identified by VAL)
- [x] All major defects resolved or justified (None identified by VAL)
- [x] Traceability 100% complete (T1, T2, T3 verified by VER; confirmed by VAL)
- [x] All verification criteria met (VER Report: All criteria PASS; confirmed by VAL)
- [x] VER conclusions acceptable from validation perspective (VAL concurs with VER)
- [x] Phase 7 validation feasibility confirmed (VAL assessment: feasible and achievable)

**Conditions Satisfied:** All conditions for Phase 3 progression are met from VAL perspective. No blocking issues.

---

## 6. VAL Observations Summary

| ID | Type | Description | Severity | Status |
|----|------|-------------|----------|--------|
| **VAL-OBS-SRS-001** | Advisory | End-to-end vs. internal timing measurement clarification for validation (REQ-SAFE-005) | Informational | Non-Blocking |
| **VAL-OBS-SRS-002** | Advisory | Recommend statistical validation for critical lock functionality (100 trials) in Phase 7 | Enhancement | Non-Blocking |
| **VAL-OBS-OTSTSPEC-001** | Advisory | Recommend simulator accuracy characterization before Phase 7 (TCMS/DDU simulators) | Enhancement | Non-Blocking |
| **VAL-OBS-OTSTSPEC-002** | Advisory | Clarifies VAL's coverage review role (review reports, not perform measurement) | Informational | Non-Blocking |
| **VAL-OBS-OTSTSPEC-003** | Advisory | Agrees with VER OBS-003: sub-integer boundary testing (5.0 vs. 5.1 km/h) recommended | Enhancement | Non-Blocking |
| **VAL-OBS-HAZLOG-001** | Advisory | Agrees with VER OBS-001: FMEA/FTA deferral to Phase 3 acceptable | Informational | Non-Blocking |

**Total Observations:** 6 (all advisory, all non-blocking)

---

## 7. Validator Statement

I, **VAL Agent**, hereby certify that:

1. I have independently reviewed the Software Requirements Specification (DOC-SRS-2026-001 v0.1), Overall Software Test Specification (DOC-OTSTSPEC-2026-001 v0.1), Hazard Log (DOC-HAZLOG-2026-001 v1.0), and Software Requirements Verification Report (DOC-REQVER-2026-001 v1.0) for the TDC project from the **validation perspective**.

2. The 2nd-check review activities were performed in accordance with the Software Validation Plan (DOC-SVaP-2026-001 v1.0) and EN 50128:2011 Section 7.7.

3. The review results documented in this 2nd-check summary are accurate and complete to the best of my knowledge.

4. **[For SIL 3]** I am independent from the Requirements Engineer (REQ), Designer (DES), Implementer (IMP), Integrator (INT), Tester (TST), and Verifier (VER) roles per EN 50128 §5.3.7 and §5.1.2.8. I report to VMGR (or Safety Authority), **not to PM**, per §5.1.2.10f.

5. All Phase 2 deliverables reviewed are **SUITABLE FOR PHASE 7 VALIDATION** from the validation perspective. I **CONCUR WITH VER CONCLUSIONS** and recommend **APPROVAL** for progression to Phase 3 (Architecture and Design).

6. My 2nd-check observations are **advisory only** and do not block Phase 2 approval. All observations have appropriate resolutions or are deferred to later phases.

7. This 2nd-check review is **input to VMGR Final V&V Decision** for Phase 2. VMGR will review both VER Verification Report (item 8) and this VAL 2nd-Check Summary before issuing Final V&V Decision.

**Validator:** VAL Agent  
**Signature:** _____________  
**Date:** 2026-03-30  
**SIL Level:** 3  
**Independence Confirmed:** Yes

---

## 8. Next Steps

### 8.1 Immediate Actions (Phase 2 Closure)

1. **Submit to QUA for Template Check** — This VAL 2nd-Check Summary document will be submitted to QUA for format-gate review (template compliance check).

2. **Submit to VMGR for Final V&V Decision** — After QUA template check PASS, this VAL 2nd-Check Summary will be submitted to VMGR along with VER Verification Report (item 8) for VMGR Final V&V Decision.

3. **VMGR Review** — VMGR will review:
   - VER Software Requirements Verification Report (DOC-REQVER-2026-001 v1.0) — VMGR APPROVED 2026-03-30 ✅
   - VAL 2nd-Check Summary (this document) — Pending VMGR review
   - VMGR will issue Final V&V Decision: APPROVE or REJECT for Phase 2 progression

4. **COD Gate Check** — After VMGR Final V&V Decision APPROVE, COD will perform Phase 2 gate-check (`@cod gate-check requirements`). If gate-check PASS, Phase 3 (Architecture and Design) will be authorized to begin.

### 8.2 Phase 3 Actions (Deferred)

- **SAF to complete FMEA/FTA** per Hazard Log §1.3 commitment (VER OBS-001, VAL-OBS-HAZLOG-001)
- **VER to verify FMEA/FTA** in Phase 3 Verification Report (item 14)
- **VAL to review FMEA/FTA** for validation test implications (any new failure scenarios to be added to validation test suite)

### 8.3 Phase 7 Actions (Deferred)

- **TST to perform simulator validation** (characterize simulator accuracy and latency) (VAL-OBS-OTSTSPEC-001)
- **TST to consider sub-integer boundary testing** (5.0 vs. 5.1 km/h) if sensor precision supports it (VER OBS-003, VAL-OBS-OTSTSPEC-003)
- **TST to plan statistical validation** for critical lock functionality (e.g., 100 door lock cycles, 0 failures) (VAL-OBS-SRS-002)
- **VAL to execute 133 validation test cases** per Overall Software Test Specification
- **VAL to conduct acceptance testing** with customer participation (6 acceptance test cases)
- **VAL to review coverage reports** from TST (confirm targets met)
- **VAL to author Phase 7 deliverables** (Software Validation Report, Tools Validation Report, Release Note)
- **VAL to issue release decision** (AGREE/DISAGREE per §5.1.2.8)

---

## 9. References

### 9.1 Normative References

- **EN 50128:2011** — Railway applications — Software for railway control and protection systems
- **EN 50126-1:2017** — Railway applications — RAMS — Part 1: Generic RAMS process
- **EN 50126-2:2017** — Railway applications — RAMS — Part 2: Systems approach to safety
- **IEC 61508:2010** — Functional safety of electrical/electronic/programmable electronic safety-related systems

### 9.2 Project References

| Document ID | Title | Version | Date |
|-------------|-------|---------|------|
| DOC-SRS-2026-001 | Software Requirements Specification | 0.1 DRAFT | 2026-03-30 |
| DOC-OTSTSPEC-2026-001 | Overall Software Test Specification | 0.1 DRAFT | 2026-03-30 |
| DOC-HAZLOG-2026-001 | Hazard Log | 1.0 DRAFT | 2026-03-30 |
| DOC-REQVER-2026-001 | Software Requirements Verification Report | 1.0 | 2026-03-30 |
| DOC-SVaP-2026-001 | Software Validation Plan | 1.0 | 2026-03-30 (Phase 1) |
| DOC-SQAP-2026-001 | Software Quality Assurance Plan | 1.0 | 2026-03-30 (Phase 1) |
| DOC-SVP-2026-001 | Software Verification Plan | 1.0 | 2026-03-30 (Phase 1) |
| DOC-TDC-SRS-SYS-001 | System Requirements Specification | v1.0 | System document |
| DOC-TDC-SSRS-SYS-001 | System Safety Requirements Specification | v1.0 | System document |

---

**End of VAL 2nd-Check Summary — Phase 2 Requirements**

**VAL Agent**  
**Date:** 2026-03-30  
**Project:** TDC — Train Door Control System  
**SIL Level:** 3  
**VAL 2nd-Check Decision:** ✅ **CONCUR WITH VER CONCLUSIONS**  
**Recommendation:** **APPROVE** for Phase 3 progression  
**Observations:** 6 advisory (all non-blocking)
