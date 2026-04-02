# VAL 2nd-Check Review Record — Phase 2 (Requirements)

**Project**: TDC (Train Door Control System)  
**SIL Level**: SIL 3  
**Phase**: Phase 2 — Requirements Specification  
**Review Date**: 2026-04-02  
**Reviewer**: Software Validator (VAL)  
**Status**: 2nd-Check Review (Independent Validation Perspective)

---

## 1. PURPOSE

This document records the **VAL 2nd-Check Review** of Phase 2 deliverables per EN 50128:2011 Annex C Table C.1. VAL performs the 2nd-Check (Column 4) after VER's 1st-check (Item 8) has been completed and approved by VMGR.

**Authority**: VAL is independent from REQ, TST, and PM per EN 50128 §5.1.2.10(f) for SIL 3. VAL reports to VMGR (not PM).

**Scope**: Validation feasibility assessment — VAL evaluates whether the Phase 2 deliverables provide a sound basis for Phase 7 system-level validation.

---

## 2. DELIVERABLES REVIEWED

| Item # | Document ID | Title | Version | VER 1st-Check Status |
|--------|------------|-------|---------|---------------------|
| 6 | DOC-SRS-2026-001 | Software Requirements Specification | 0.1 DRAFT | COMPLETE (Item 8 approved by VMGR) |
| 7 | DOC-OTSTSPEC-2026-001 | Overall Software Test Specification | 0.1 DRAFT | COMPLETE (Item 8 approved by VMGR) |

---

## 3. VALIDATION FEASIBILITY ASSESSMENT — SOFTWARE REQUIREMENTS SPECIFICATION (Item 6)

### 3.1 Overall Assessment

The SRS defines **81 requirements** organized into 7 categories:
- 18 Functional Requirements (REQ-FUN-001 to REQ-FUN-018)
- 10 Performance Requirements (REQ-PERF-001 to REQ-PERF-010)
- 13 Interface Requirements (REQ-INT-001 to REQ-INT-013)
- 21 Safety Requirements (REQ-SAFE-001 to REQ-SAFE-021)
- 4 Reliability Requirements (REQ-REL-001 to REQ-REL-004)
- 8 Operational Requirements (REQ-OPR-001 to REQ-OPR-008)
- 3 Security Requirements (REQ-SEC-001 to REQ-SEC-003)

**Validation Perspective**: The SRS provides a **comprehensive and validatable** set of requirements suitable for Phase 7 system-level validation.

### 3.2 Testability and Acceptance Criteria

**Finding**: Each requirement includes quantified acceptance criteria with measurable pass/fail thresholds.

**Examples of Strong Validation Criteria**:
- REQ-FUN-001: "All 5 precondition combinations tested; no door opens when train speed > 5 km/h; command-to-motor-start latency <= 200 ms"
- REQ-PERF-003: "Measured time from obstacle sensor rising edge to motor reversal PWM command <= 150 ms on target hardware"
- REQ-SAFE-001: "No door open command processed when speed > 5 km/h; inhibit active on stale/missing speed; both channels independently verify; verified by fault injection"

**VAL Assessment**: All 81 requirements are **testable** in Phase 7 with quantifiable outcomes. No subjective acceptance criteria identified.

### 3.3 Safety Requirements Validation Feasibility (SIL 3)

**21 Safety Requirements** (REQ-SAFE-001 to REQ-SAFE-021) support 7 safety functions (SF-001 to SF-007) from the System Safety Requirements Specification.

**VAL Assessment**:
- All safety requirements include **2oo2 verification mechanisms** (dual-channel, dual-sensor)
- **Fail-safe defaults** are clearly specified (e.g., inhibit door opening if speed data absent)
- **Fault injection test requirements** are explicit in acceptance criteria
- **Timing constraints** are measurable (e.g., 100 ms for safe state entry, 150 ms for obstacle reversal)
- **Cross-channel comparison** requirements are validatable (REQ-SAFE-010)

**Observation**: REQ-SAFE-014 (Diagnostic Coverage >= 99%) states "Verified by analysis" but does not specify acceptance test requirements. This is acceptable — DC calculation is a VER/SAF analysis activity, not a VAL system test activity. VAL will verify the DC report exists and is approved in Phase 7.

### 3.4 Performance Requirements Validation Feasibility

**10 Performance Requirements** (REQ-PERF-001 to REQ-PERF-010) define critical timing, resource, and WCET constraints.

**VAL Assessment**:
- All timing requirements include **measurable thresholds** (e.g., WCET <= 16 ms, speed interlock response <= 100 ms)
- **Test method is specified** (e.g., "Performance Test (hardware timer instrumentation)")
- **Tolerance margins** are defined where appropriate (e.g., ± 100 ms for timeouts)
- Resource requirements (RAM <= 800 KB, Flash <= 1600 KB) are verifiable by static analysis and linker map inspection

**Validation Feasibility**: All performance requirements are **validatable** in Phase 7 using target hardware instrumentation.

### 3.5 Interface Requirements Validation Feasibility

**13 Interface Requirements** (REQ-INT-001 to REQ-INT-013) define hardware, software, and user interfaces.

**VAL Assessment**:
- Hardware interface requirements (PWM, GPIO, CAN, RS-485, SPI) specify **observable signals** (e.g., PWM frequency 20 kHz confirmed by oscilloscope)
- **Error handling** is specified for all critical interfaces (e.g., HAL_PWM error -> SAFE_STATE)
- CAN message requirements include **timing, CRC, and sequence counter** validation criteria
- **Diagnostic port security** (REQ-INT-013) is testable via access control test

**Validation Feasibility**: All interface requirements are **validatable** using standard test equipment (CAN analyser, oscilloscope, RS-485 analyser).

### 3.6 Traceability and Coverage

**Backward Traceability**: All 81 requirements trace to system-level requirements (SYS-REQ-*) and/or hazards (HAZ-*). This provides a **complete hazard-to-requirement-to-validation chain** for Phase 7.

**Forward Traceability**: The SRS references the Overall Software Test Specification (Item 7) as the V-Model counterpart for Phase 7 validation. This bidirectional traceability supports **end-to-end validation**.

**VAL Assessment**: Traceability structure is **adequate** for Phase 7 validation reporting (Item 25).

---

## 4. VALIDATION FEASIBILITY ASSESSMENT — OVERALL SOFTWARE TEST SPECIFICATION (Item 7)

### 4.1 Overall Assessment

The OSTS defines **267 test cases** organized into 11 categories:
- 62 Functional test cases
- 12 Performance test cases
- 63 Safety-critical path test cases
- 31 Interface test cases
- 28 Boundary value analysis test cases
- 15 Fault injection test cases
- 14 Operational scenario test cases
- 16 Reliability/Operational test cases
- 6 Security test cases
- 10 Regression test cases
- 10 Acceptance test cases

**Validation Perspective**: The OSTS provides a **comprehensive and executable** test plan for Phase 7 validation.

### 4.2 Test Strategy and Techniques (SIL 3 Compliance)

**EN 50128 Table A.7 Mandatory Techniques (SIL 3)**:
- Functional and Black-Box Testing (M) — **Applied** (Sections 3.2, 3.4, 3.7)
- Performance Testing (M) — **Applied** (Section 3.3)

**EN 50128 Table A.5 Mandatory Techniques (SIL 3)**:
- Boundary Value Analysis (M) — **Applied** (Section 3.6, 28 test cases)
- Regression Testing (M) — **Applied** (Section 3.11, 10 regression suites)
- Traceability (M) — **Applied** (Section 4, forward/backward RTM)

**VAL Assessment**: All mandatory SIL 3 validation techniques are **correctly applied** in the OSTS.

### 4.3 Test Coverage Adequacy

**Requirements Coverage**:
- OSTS states "Every SRS requirement SHALL have at least one test case (81/81 — 100%)"
- Section 4.1 (Traceability Matrix) confirms **bidirectional traceability** between requirements and test cases

**Code Coverage**:
- OSTS correctly references **project-defined targets** in SVP/SQAP per EN 50128 Table A.21 (no percentage threshold mandated by standard)
- Statement Coverage: M at SIL 3 — measured via gcov
- Branch Coverage: M at SIL 3 — measured via gcov
- Compound Condition Coverage: HR at SIL 3 — measured and reported

**VAL Assessment**: Coverage approach is **compliant** with EN 50128 §7.7 and Table A.21. VAL will verify actual coverage results in Phase 7 against SVP/SQAP targets.

### 4.4 Safety-Critical Test Cases (SIL 3)

**63 Safety Test Cases** (TC-OSTS-SAFE-001 to TC-OSTS-SAFE-063) provide **comprehensive coverage** of all 21 safety requirements.

**VAL Assessment**:
- **2oo2 voting validation**: TC-OSTS-SAFE-016, 017 test all sensor combinations with conservative outcome verification
- **Speed interlock validation**: TC-OSTS-SAFE-001 to 005 test both channels independently, fail-safe defaults, and stale data handling
- **Obstacle detection validation**: TC-OSTS-SAFE-012 to 015 test both sensors, timing (<=150 ms), and ISR latency (<=1 ms)
- **Safe state transition validation**: TC-OSTS-SAFE-019 to 025 test all 6 critical fault triggers with timing verification (<=100 ms)
- **Fail-safe mechanism validation**: TC-OSTS-SAFE-026, 027 test fail-closed locks and watchdog recovery

**Observation**: TC-OSTS-SAFE-048 (DC >= 99% verification) references "analysis" as verification method. VAL confirms this is appropriate — DC is a calculated metric, not a direct system test. VAL will verify the DC report (from VER/SAF) is present and approved in Phase 7.

### 4.5 Fault Injection Test Cases

**15 Fault Injection Test Cases** (TC-OSTS-FAULT-001 to TC-OSTS-FAULT-015) provide **realistic hazard scenario testing**.

**Examples**:
- TC-OSTS-FAULT-001: CAN bus physically disconnected → verify fail-safe response
- TC-OSTS-FAULT-006: Deliberate watchdog starvation → verify hardware reset within 55 ms
- TC-OSTS-FAULT-007: SPI cross-channel disagreement → verify safe state within 20 ms
- TC-OSTS-FAULT-011: RAM corruption → verify CRC detection and safe state within 100 ms

**VAL Assessment**: Fault injection test cases are **executable** and provide **high-confidence validation** of safety mechanisms under failure conditions.

### 4.6 Boundary Value Analysis (BVA)

**28 BVA Test Cases** (TC-OSTS-BOUND-001 to TC-OSTS-BOUND-028) apply **systematic BVA** to all safety-critical numeric parameters.

**Examples**:
- Speed threshold (5 km/h): min-1 (4.9), min (5.0), min+1 (5.1)
- Watchdog timeout (50 ms): starvation test at 50 ms -> reset within 55 ms
- Speed staleness (200 ms): 180 ms (valid), 200 ms (at threshold), 220 ms (stale)

**VAL Assessment**: BVA is **correctly applied** per EN 50128 Table A.5 item 13 (M at SIL 3). All critical thresholds are covered.

### 4.7 Acceptance Test Cases (VAL Participation)

**10 Acceptance Test Cases** (TC-OSTS-ACC-001 to TC-OSTS-ACC-010) define **customer/validator acceptance criteria** with VAL witness participation.

**Key Acceptance Tests**:
- TC-OSTS-ACC-001: All 7 safety functions (SF-001 to SF-007) demonstrated end-to-end
- TC-OSTS-ACC-002: 1000-cycle soak test with zero door opening at speed > 5 km/h
- TC-OSTS-ACC-004: Safe state entry within 100 ms for all 6 critical fault triggers (witnessed)
- TC-OSTS-ACC-006: Coverage targets met (per SVP/SQAP) — report presented to VAL
- TC-OSTS-ACC-008: All 81 requirements have at least one passed test case — RTM review with VAL

**VAL Assessment**: Acceptance test cases are **well-defined** and align with VAL's Phase 7 validation objectives. VAL confirms these acceptance criteria are appropriate and measurable.

### 4.8 Test Environment and Tooling

**Target Hardware**: STM32H743 dual-channel DCU (2oo2 configuration)

**Test Equipment**:
- CAN bus analyser (PEAK PCAN-USB Pro)
- RS-485 bus analyser
- Oscilloscope (>=100 MHz) for PWM and timing measurement
- Hardware fault injection harness

**Coverage Tools**: gcov + lcov (HTML) + gcovr (JSON)

**VAL Assessment**: Test environment specification is **adequate** for SIL 3 system-level validation. All required test equipment is industry-standard and suitable for target hardware.

### 4.9 Test Entry and Exit Criteria

**Entry Criteria** (Section 2.5):
- Integration testing (Phase 6) completed and approved
- Test environment validated
- **OSTS reviewed and approved by VER and VAL** ← VAL confirms this 2nd-check satisfies this criterion
- Traceability matrix complete

**Exit Criteria** (Section 2.5):
- All 267 test cases executed
- Statement and Branch coverage targets met; Compound Condition Coverage measured
- All SIL 3 safety function tests passed
- **VAL approval obtained** ← VAL will provide final approval in Phase 7 after test execution

**VAL Assessment**: Entry and exit criteria are **appropriate** for SIL 3 validation. VAL notes that VAL's Phase 7 approval authority is correctly identified in exit criteria.

---

## 5. VALIDATION CONCERNS AND OBSERVATIONS

### 5.1 Concerns

**None identified**. No blocking concerns for Phase 3 authorization.

### 5.2 Observations (Non-Blocking)

1. **Observation 1 — Diagnostic Coverage (REQ-SAFE-014 and TC-OSTS-SAFE-048)**:
   - REQ-SAFE-014 states DC >= 99% "Verified by analysis"
   - TC-OSTS-SAFE-048 references "FMEA-based" DC calculation
   - **VAL Comment**: This is acceptable — DC is a VER/SAF calculated metric, not a direct VAL system test. VAL will verify the DC report exists and is approved by VMGR in Phase 7 Track B.

2. **Observation 2 — Acceptance Test Criteria Alignment**:
   - Section 3.12 (Acceptance Test Cases) correctly identifies VAL participation and witness requirements
   - **VAL Comment**: VAL confirms the 10 acceptance test cases (TC-OSTS-ACC-001 to ACC-010) align with VAL's Phase 7 validation objectives. VAL will coordinate with TST during Phase 7 execution to witness these tests.

3. **Observation 3 — Coverage Targets Reference to SVP/SQAP**:
   - OSTS Section 2.4 correctly references project-defined coverage targets in SVP/SQAP per EN 50128 Table A.21 Requirement 1
   - **VAL Comment**: VAL will verify actual coverage results against the SVP/SQAP-defined targets in Phase 7. The OSTS approach is compliant with EN 50128 (no percentage threshold mandated by standard).

4. **Observation 4 — Machine-Readable Test Results**:
   - OSTS Section 2.3 specifies XML (JUnit) and JSON result formats per §7.6.4.5b
   - **VAL Comment**: This is correct and facilitates automated traceability verification in Phase 7. VAL will verify machine-readable results are produced for all 267 test cases.

5. **Observation 5 — Regression Test Scope**:
   - Section 3.11 defines 10 regression test suites covering critical safety paths
   - **VAL Comment**: Regression scope is appropriate for SIL 3. VAL recommends that any software change after Phase 7 validation triggers re-execution of the full regression suite before re-release.

---

## 6. VALIDATION FEASIBILITY CONCLUSION

### 6.1 SRS Validation Feasibility

The Software Requirements Specification (DOC-SRS-2026-001) provides a **sound basis for Phase 7 validation**:
- All 81 requirements are **testable** with quantified acceptance criteria
- Safety requirements include **measurable 2oo2 mechanisms** and **fail-safe defaults**
- Performance requirements define **observable timing and resource constraints**
- Interface requirements specify **verifiable signals and protocols**
- **Backward traceability** to system requirements and hazards is complete
- **Forward traceability** to OSTS is established

**VAL Assessment**: The SRS is **validatable** in Phase 7.

### 6.2 OSTS Adequacy for Phase 7 Validation

The Overall Software Test Specification (DOC-OTSTSPEC-2026-001) provides a **comprehensive and executable test plan**:
- **267 test cases** provide full coverage of all 81 SRS requirements
- All **mandatory SIL 3 techniques** are correctly applied (functional/black-box testing, performance testing, BVA, regression testing)
- **Safety-critical test cases** (63) include fault injection, 2oo2 validation, and timing verification
- **Acceptance test cases** (10) define clear VAL witness criteria
- **Test environment** is adequate for target hardware validation
- **Entry and exit criteria** are appropriate for SIL 3

**VAL Assessment**: The OSTS is a **sound basis for Phase 7 validation reporting** (Item 25).

---

## 7. VAL 2ND-CHECK DECISION

**Decision**: **CONCUR**

**Rationale**:
- The SRS and OSTS provide a **complete and validatable foundation** for Phase 7 system-level validation.
- All 81 requirements are testable with quantified acceptance criteria.
- All mandatory EN 50128 SIL 3 validation techniques are correctly applied.
- No blocking concerns identified.
- The 5 observations noted above are **non-blocking** and do not require Phase 2 rework.

**Outcome**: VAL approves Items 6 and 7 for Phase 3 gate authorization. VAL will execute Phase 7 validation per the OSTS and produce the Software Validation Report (Item 25) after test execution.

---

## 8. APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Software Validator (VAL)** | [Name] | _____________ | 2026-04-02 |

**Next Step**: This VAL 2nd-Check Review Record is submitted to **VMGR** for final Phase 2 Track B approval.

---

## 9. REFERENCES

| Document | ID | Version |
|----------|-----|---------|
| Software Requirements Specification | DOC-SRS-2026-001 | 0.1 DRAFT |
| Overall Software Test Specification | DOC-OTSTSPEC-2026-001 | 0.1 DRAFT |
| Software Quality Assurance Plan | DOC-SQAP-2026-001 | 0.1 DRAFT |
| Software Verification Plan | DOC-SVP-2026-001 | 0.1 DRAFT |
| Software Validation Plan | DOC-SVaP-2026-001 | 0.1 DRAFT |
| System Safety Requirements Specification | DOC-SYS-SAF-2026-001 | 0.1 DRAFT |
| EN 50128:2011 | §5.3.7, §6.3, §7.7, Table A.7, Table C.1 | — |
| VnV-PROCESS.md | VAL 2nd-check table, Phase 7 Track B flow | — |
| deliverables.yaml | Item 6, Item 7 signature chains | — |

---

**END OF VAL 2ND-CHECK REVIEW RECORD**
