# Software Validation Plan (SVaP)

**DOCUMENT TYPE**: Software Validation Plan  
**EN 50128 DELIVERABLE**: Annex C Item 5  
**STANDARD REFERENCE**: EN 50128:2011 Section 6.3.4.2, Section 7.7, Table A.7  
**PROJECT**: TDC (Train Door Control System)  
**SIL LEVEL**: 3

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SVaP-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Validator (VAL) |
| **Status** | DRAFT — Awaiting VER 1st Check |

---

## VERSION HISTORY

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-04-02 | VAL | Initial SVaP draft for SIL 3 TDC project | - |
| 1.0 | 2026-04-02 | VAL | Baseline version for Phase 1 gate | [Pending VER] |

---

## APPROVALS

### Track A Approvals (Development Workflow)

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (VAL)** | [VAL Name] | [PENDING] | [PENDING] |
| **Reviewer (QUA)** | [QUA Name] | [PENDING] | [PENDING] |
| **Approver (PM)** | [PM Name] | [PENDING] | [PENDING] |

**Track A**: Development deliverable → QUA format-gate → PM approval → COD gate-check

### Track B Approvals (EN 50128 Annex C Table C.1 Signature Chain)

| Written By | 1st Check | 2nd Check | Date |
|------------|-----------|-----------|------|
| Software Validator<br>Name: [VAL Name]<br>Signature: _____________ | Software Verifier<br>Name: [VER Name]<br>Signature: _____________ | — | [YYYY-MM-DD] |

**Track B**: VER 1st-check (technical review) → VMGR review (SIL 3) → Final V&V decision

**Notes:**
- **Track A** documents QUA format-gate approval and PM approval before COD gate-check (WORKFLOW.md)
- **Track B** documents EN 50128 Annex C technical review chain (Written By / 1st Check / 2nd Check)
- **Written By**: Validator responsible for document content per EN 50128 §6.3.4.3
- **1st Check**: Verifier independent review per Annex C Table C.1 Column 3
- **2nd Check**: None per Annex C Table C.1 (item 5 has blank 2nd check column)
- For SIL 3: Independence requirements apply per EN 50128 §5.1.2.10f (VAL independent from development and reports to Safety Authority, not PM)
- Signature authority per project SQAP and DELIVERABLES.md

---

## INTRODUCTION

### 1.1 Purpose

This Software Validation Plan (SVaP) defines the validation strategy, activities, acceptance criteria, and organizational structure for the Train Door Control System (TDC) software. Validation confirms that the software fulfills its intended use in its intended operational environment in accordance with EN 50128:2011 Section 7.7.

**Validation Definition** (EN 50128): Confirmation by examination and provision of objective evidence that the particular requirements for a specific intended use are fulfilled.

**Key Distinction**:
- **Verification**: "Are we building the product right?" (compliance with specifications) — covered by Software Verification Plan (DOC-SVP-2026-001)
- **Validation**: "Are we building the right product?" (fitness for intended use in operational environment) — covered by this plan

**Normative Basis**: EN 50128:2011 §6.3.4.2 mandates: "Validation shall be documented with a Software Validation Plan and a Software Validation Report." This SVaP fulfills the planning requirement and will guide the Software Validation Report (item 25) production in Phase 7.

### 1.2 Scope

This SVaP applies to system-level validation of the TDC software in its operational railway environment. The plan covers:

1. **System-Level Validation Testing** — End-to-end operational scenarios in target environment (Phase 7)
2. **Acceptance Testing** — Customer-witnessed testing and formal acceptance (Phase 7)
3. **Operational Environment Testing** — Target hardware, realistic railway conditions (Phase 7)
4. **Performance Validation** — Timing, throughput, resource usage (MANDATORY SIL 3)
5. **Safety Scenario Validation** — All safety-critical scenarios from Hazard Log (MANDATORY SIL 3)
6. **Validation Reporting** — Software Validation Report (item 25), Tools Validation Report (item 26 if needed), Release Note (item 27)
7. **Release Decision** — AGREE/DISAGREE authority per §5.1.2.8 (FINAL decision, cannot be overridden)

**Target SIL Level**: SIL 3

**Out of Scope**:
- Unit testing and integration testing (covered by Software Verification Plan DOC-SVP-2026-001)
- Requirements verification (covered by SVP)
- Design verification (covered by SVP)
- Code verification (covered by SVP)
- Hardware validation (covered by Hardware Validation Plan)
- System integration beyond software scope (covered by System Validation Plan)

**Platform Deviation D1**: This SVaP is placed in Phase 1 (Planning) rather than Phase 2 (Requirements) as suggested by Annex C Table C.1 "requirements" phase assignment. This deviation is justified by:
- **§6.3.4.3**: SVaP shall be written "on the basis of the input documents" — planning documents (SQAP, SCMP, SVP) are sufficient input
- **§5.3.2.4**: "Plans for each lifecycle phase shall be approved and documented at an earlier phase than that to which they relate" — validation plan must be baselined BEFORE Phase 7 (Validation)

This deviation ensures early establishment of validation acceptance criteria and customer agreement on validation approach before development begins. Documented per SQAP requirement.

### 1.3 SIL 3 Classification and Requirements

**Target SIL Level**: SIL 3 (Safety Integrity Level 3)

**EN 50128 Validation Requirements** (Table A.7):

| SIL Level | Mandatory Techniques | Key Requirements |
|-----------|---------------------|------------------|
| **SIL 3** | Functional/Black-Box Testing (**M**), Performance Testing (**M**) | Independent validation (**M**), Operational scenarios (**M**), Target environment testing (**M**), Customer acceptance (**M**) |

**SIL 3 Independence Requirements** (§5.1.2.10f):
- **MANDATORY**: Validator SHALL be independent from Designer, Implementer, Tester, Verifier, and Integrator
- **MANDATORY**: Validator SHALL NOT report to Project Manager (reports to Safety Authority or Customer directly)
- **MANDATORY**: Organizational separation from development team
- **MANDATORY**: Personnel independence (different individuals)
- **MANDATORY**: Final release decision authority (AGREE/DISAGREE per §5.1.2.8) — cannot be overridden by PM, COD, or VMGR

### 1.4 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **Validation** | Confirmation that software fulfills its intended use in operational environment |
| **Acceptance Testing** | Validation testing with customer/user involvement and formal acceptance |
| **Operational Scenario** | Realistic use case representing actual railway operations (normal, degraded, emergency, recovery) |
| **Black-Box Testing** | Testing without knowledge of internal implementation (based on external behavior) |
| **Performance Testing** | Testing of timing, throughput, resource usage, real-time constraints (MANDATORY SIL 3) |
| **Target Environment** | Actual railway hardware/software platform where TDC software will operate |
| **Release Decision** | VAL final AGREE/DISAGREE decision for software release per §5.1.2.8 |
| **TDC** | Train Door Control System — software controlling train door open/close operations |
| **WCET** | Worst-Case Execution Time — maximum time for time-critical functions |

### 1.5 References

| Reference | Document | Location |
|-----------|----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems | `std/EN50128-2011.md` |
| **[EN50126-1]** | EN 50126-1:2017 Railway applications - RAMS Part 1 | `std/EN 50126-1-2017.md` |
| **[EN50126-2]** | EN 50126-2:2017 Railway applications - RAMS Part 2 | `std/EN 50126-2-2017.md` |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 | `docs/phase-1-planning/Software-Quality-Assurance-Plan.md` |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-2026-001 | `docs/phase-1-planning/Software-Configuration-Management-Plan.md` |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 | `docs/phase-1-planning/Software-Verification-Plan.md` |
| **[SRS]** | Software Requirements Specification (to be created in Phase 2) | `docs/phase-2-requirements/Software-Requirements-Specification.md` |
| **[HAZLOG]** | Hazard Log (system-level, created by SAF) | `docs/system/Hazard-Log.md` |
| **[SYSREQ]** | System Requirements Specification, DOC-SYS-REQ-2026-001 | `docs/system/System-Requirements-Specification.md` |
| **[SYSSAF]** | System Safety Requirements Specification, DOC-SYS-SAF-2026-001 | `docs/system/System-Safety-Requirements-Specification.md` |

**Platform References**:
- `DELIVERABLES.md` — Annex C Table C.1 deliverable registry, deviation D1
- `WORKFLOW.md` — Authority structure, Phase 7 Track B flow, VAL independence
- `tasks/VnV-PROCESS.md` — V&V process reference (ISA PASS)
- `TRACEABILITY.md` — T1–T15 traceability rules
- `LIFECYCLE.md` — EN 50128 V-Model lifecycle phases

### 1.6 Overview

This SVaP is structured as follows:

- **Section 2**: Validation Organization — VAL role, responsibilities, independence requirements (SIL 3)
- **Section 3**: Validation Strategy — Multi-level validation approach, Table A.7 techniques
- **Section 4**: Validation Activities — Phase-by-phase validation activities (requirements validation, test planning, test execution, performance validation, acceptance testing)
- **Section 5**: Traceability to Requirements — Requirements → validation tests (100% coverage)
- **Section 6**: Validation Evidence Management — Evidence collection, review, archival
- **Section 7**: Validation Acceptance Criteria — Overall acceptance criteria for release decision
- **Section 8**: Validation Schedule — Milestones, effort estimates
- **Section 9**: Risk Management — Validation risks and mitigation
- **Section 10**: Validation Tools and Resources — Test tools, personnel, hardware, facilities
- **Section 11**: Compliance Matrix — EN 50128 §7.7 and Table A.7 compliance
- **Section 12**: References — Normative and project references
- **Appendices**: Validation test case template, validation report template, customer acceptance certificate

---

## 2. VALIDATION ORGANIZATION

### 2.1 Validator (VAL) Role and Responsibilities

**Role**: Validator (VAL)

**EN 50128 Reference**: Section 5.3.7, Annex B Table B.7

**Primary Responsibilities**:
1. **Author this SVaP** (item 5) per §6.3.4.3 — defines validation strategy for Phase 7
2. **Define validation test scenarios** — operational scenarios representing actual railway use
3. **Coordinate acceptance testing with customer** — customer witnesses critical tests
4. **Execute validation testing in target environment** — TDC software on target railway hardware
5. **Analyze validation test results** — pass/fail per acceptance criteria
6. **Produce Software Validation Report** (item 25) per §7.7.4.6–7.7.4.11 (Phase 7)
7. **Produce Tools Validation Report** (item 26) if tool qualification required (Phase 7)
8. **Produce Release Note** (item 27) per §7.7.4.12 (Phase 7)
9. **Issue release decision** — AGREE or DISAGREE for software release per §5.1.2.8 (FINAL decision)
10. **Perform 2nd-check reviews** — on deliverables in Phases 1–6, 9–10 per VnV-PROCESS.md

**Qualifications** (Table B.7):
- Knowledge of EN 50128 validation requirements (§7.7, Table A.7)
- Understanding of intended operational use (railway train door systems)
- Experience with system-level testing in operational environments
- Familiarity with railway safety requirements (EN 50126, EN 50129)
- Understanding of customer acceptance processes

**Independence Requirements** (§5.1.2.10f — MANDATORY SIL 3):
- **MANDATORY**: Validator SHALL NOT be the Designer, Implementer, Tester, Verifier, or Integrator
- **MANDATORY**: Validator SHALL NOT report to Project Manager (reports to Safety Authority or Customer directly)
- **MANDATORY**: Organizational independence — separate reporting line from development team
- **MANDATORY**: Personnel independence — different individuals from design/implementation/verification
- **MANDATORY**: Final release decision authority — AGREE/DISAGREE decision CANNOT be overridden by PM, COD, or VMGR

### 2.2 Validation Support Roles

| Role | Responsibilities | Independence | Reporting |
|------|------------------|--------------|-----------|
| **Customer Representative** | Define acceptance criteria, witness tests, approve results | Yes (external) | Customer organization |
| **Safety Manager (SAF)** | Review safety scenarios, approve safety-critical tests, maintain Hazard Log | No | PM/COD |
| **Lifecycle Coordinator (COD)** | Authorize Phase 7 execution, coordinate VAL tasking (via VMGR at SIL 3) | No | Safety Authority |
| **V&V Manager (VMGR)** | Coordinate VAL tasking (SIL 3), review VAL reports, issue FINAL V&V decision | Yes (SIL 3) | Safety Authority |
| **QA Manager (QUA)** | Format-gate VAL reports, approve validation evidence | No | PM/COD |
| **Configuration Manager (CM)** | Baseline validation artifacts, control validation evidence | No | PM |
| **Test Support Engineer** | Execute validation tests (under VAL direction), collect test data | No | VAL |

### 2.3 Independence Management (SIL 3)

**EN 50128 Requirement**: Validator SHALL be independent of development, verification, and project management (§5.1.2.10f).

**Independence Measures for TDC Project**:
1. **Organizational Separation**: VAL reports to Safety Authority (or Customer), NOT to Project Manager
2. **Personnel Separation**: VAL is a different individual from DES, IMP, TST, VER, INT
3. **Authority Separation**: VAL has final release decision authority; PM cannot override VAL DISAGREE decision
4. **Work Product Separation**: VAL does NOT participate in requirements, design, implementation, integration, or verification activities
5. **Reporting Structure**: VAL → VMGR → Safety Authority (SIL 3 hierarchy per WORKFLOW.md Diagram 1)

**Independence Verification**:
- Organization chart documents separate reporting line for VAL
- Training records confirm VAL qualification per Table B.7
- Project plan confirms VAL not assigned design/implementation/verification tasks
- SQAP Section 1 documents independence requirements
- VMGR reviews independence compliance monthly

**Validation Authority**: Validator has final authority to AGREE or DISAGREE with software release per §5.1.2.8. This decision is FINAL and cannot be overridden by PM, COD, or VMGR.

### 2.4 Reporting Structure (SIL 3)

```
Safety Authority / Customer
        ↓
   VMGR (Independent V&V Authority)
        ↓
   VAL (Validator)
        ↓
   Test Support Engineer (if needed)
```

**Key Rules**:
- VAL reports to VMGR (SIL 3) or COD (SIL 0-2) — NEVER to PM at SIL 3
- VAL receives tasking from VMGR (SIL 3) or COD (SIL 0-2) — NEVER from PM at SIL 3
- VAL's AGREE/DISAGREE release decision is FINAL per §5.1.2.8
- VMGR reviews VAL reports but cannot override VAL's release decision
- VMGR issues FINAL V&V DECISION to COD after reviewing VER + VAL reports together

---

## 3. VALIDATION STRATEGY

### 3.1 Validation Approach

**Multi-Level Validation for TDC**:

1. **Requirements Validation** (Phase 2): Confirm SRS requirements match customer needs and intended use
   - Customer walkthrough of SRS
   - Scenario mapping (customer use cases → SRS requirements)
   - Safety requirements review (Hazard Log → SRS safety requirements)

2. **Scenario-Based Validation** (Phase 7): Test realistic operational scenarios in target railway environment
   - Normal operation (doors open/close at station stops)
   - Degraded operation (sensor failures, actuator faults)
   - Emergency scenarios (emergency brake, obstacle detection, emergency release)
   - Recovery scenarios (fault recovery, safe state entry)
   - Environmental stress (temperature, vibration, EMI)

3. **Performance Validation** (Phase 7 — MANDATORY SIL 3): Confirm timing, throughput, resource usage
   - Response time ≤ 50ms for safety-critical functions (per SRS performance requirements)
   - CPU usage ≤ 70% under worst-case load
   - Memory usage ≤ 85% of available RAM
   - WCET analysis for time-critical functions
   - Long-duration reliability testing (72 hours continuous operation)

4. **Safety Validation** (Phase 7 — MANDATORY SIL 3): Validate safety requirements and hazard mitigation
   - All Hazard Log hazards validated (SIL 3 mitigation measures effective)
   - Safety state transitions validated (fail-safe behavior)
   - Fault detection and recovery validated
   - Safety integrity validated (no systematic failures)

5. **Acceptance Testing** (Phase 7): Customer-witnessed testing and formal acceptance
   - Customer witnesses critical validation tests
   - Customer reviews all test results and defects
   - Customer approves validation evidence
   - Customer signs acceptance certificate

### 3.2 Validation Techniques (EN 50128 Table A.7)

The following validation techniques SHALL be applied for SIL 3:

| # | Technique | SIL 3 | Implementation | Reference | Justification |
|---|-----------|-------|----------------|-----------|---------------|
| **1** | Functional and Black-Box Testing | **M** | System test suite with operational scenarios (normal, degraded, emergency, recovery) | Table A.14 | MANDATORY SIL 3 — confirms software behavior matches intended use without knowledge of internal implementation |
| **2** | Performance Testing | **M** | Timing analysis (WCET), load testing, resource usage profiling, long-duration reliability testing | Table A.18 | MANDATORY SIL 3 — confirms real-time constraints met, resources within limits |
| **3** | Boundary Value Analysis | **M** | Test input boundaries (min, max, just-below, just-above) for all safety-critical inputs | Table A.7 #6 | MANDATORY SIL 3 — high-risk area for defects |
| **4** | Equivalence Classes | HR | Partition input space into equivalence classes, test representative values | Table A.7 #7 | HR SIL 3 — reduces test count while maintaining coverage |
| **5** | Regression Testing | **M** | Re-execute all validation tests after defect fixes or changes | Table A.7 #4 | MANDATORY SIL 3 — ensures fixes don't introduce new defects |

**Approved Combination for SIL 3**: 1 + 2 + 3 + 4 + 5 (all MANDATORY or HR techniques)

**Rationale**: 
- Techniques 1 and 2 are MANDATORY for SIL 3 per Table A.7
- Technique 3 (Boundary Value Analysis) is MANDATORY for SIL 3 per Table A.7 #6
- Technique 4 (Equivalence Classes) is HR for SIL 3 per Table A.7 #7
- Technique 5 (Regression Testing) is MANDATORY for SIL 3 per Table A.7 #4
- These techniques provide comprehensive validation of fitness for use in railway operational environment
- Black-box approach ensures validation independent of implementation details

### 3.3 Validation Environment

**Target Environment**: Railway train door control system hardware platform

**Environment Requirements**:
- **Hardware**: Railway-grade embedded control unit (production hardware, not development board)
- **Operating System**: Bare-metal or railway-qualified RTOS (per system requirements)
- **Interfaces**: Actual door sensors (position, obstruction), door actuators (motor controllers), emergency controls, brake system interface, HMI interface
- **Environmental Conditions**: Railway operational environment (temperature -40°C to +70°C, vibration per EN 50155, EMI per EN 50121)
- **Power Supply**: Railway power supply (per system requirements)

**Difference from Development/Verification Environment**:
- Validation SHALL be performed on **target hardware** (not development PC or simulator)
- Validation SHALL use **production build configuration** (not debug builds)
- Validation SHALL include **realistic environmental conditions** (temperature, vibration, EMI)
- Validation SHALL use **actual sensors and actuators** (not stubs or mocks)

**Test Environment Setup**:
1. Railway test facility with door hardware installed on test rig
2. Target control unit mounted per production specifications
3. All sensors and actuators connected and calibrated
4. Power supply connected per railway specifications
5. Environmental chamber for temperature/EMI testing (if needed)
6. Test instrumentation (oscilloscope, logic analyzer, RTOS profiler) for performance measurements

### 3.4 Pre-existing Software

**Applicability**: Not applicable — the TDC project develops all software from scratch.

**Justification**: Per EN 50128 §6.3.4.5, the Software Validation Plan shall identify "steps to demonstrate adequacy of any pre-existing software." The TDC project does NOT use any pre-existing software components, libraries, or COTS (Commercial Off-The-Shelf) software as part of the safety-critical software. All TDC software is developed from scratch according to this project's requirements, design, and implementation processes.

**Validation Steps**: No validation steps are required for pre-existing software, as none is used in the TDC project.

**Note**: If future phases introduce pre-existing software components (e.g., reuse of qualified libraries, COTS integration), this section SHALL be updated per SCMP change control procedures, and appropriate validation steps SHALL be defined per §6.3.4.5 requirements (e.g., component validation testing, interface validation, qualification evidence review).

---

## 4. VALIDATION ACTIVITIES

### 4.1 Phase 2: Requirements Validation

**Objective**: Confirm that SRS software requirements correctly capture customer needs and intended use.

#### 4.1.1 Validation Inputs
- System Requirements Specification (DOC-SYS-REQ-2026-001)
- Software Requirements Specification (SRS) — to be created in Phase 2
- System Safety Requirements Specification (DOC-SYS-SAF-2026-001)
- Customer use cases (from customer interviews)
- Hazard Log (DOC-HAZLOG-2026-001)

#### 4.1.2 Validation Activities

| Activity | Method | Acceptance Criteria | Responsible |
|----------|--------|---------------------|-------------|
| **Requirements review** | Customer walkthrough of SRS | Customer confirms requirements match operational needs | VAL, Customer |
| **Use case validation** | Scenario mapping (use cases → SRS requirements) | All customer use cases covered by SRS requirements (100%) | VAL |
| **Safety requirements review** | Hazard analysis review (Hazard Log → SRS safety requirements) | All identified hazards addressed by SRS safety requirements | VAL, SAF |
| **Operational scenario identification** | Customer interviews, operational documentation review | Comprehensive list of validation scenarios (normal, degraded, emergency, recovery) | VAL, Customer |

#### 4.1.3 Validation Deliverables
- Requirements Validation Report (preliminary) — documenting customer sign-off
- Customer sign-off on SRS requirements
- Updated SRS (if corrections needed based on customer feedback)
- Preliminary validation scenario list (input to Validation Test Specification in Phase 7)

### 4.2 Phase 7: Validation Test Planning

**Objective**: Define validation test scenarios, test cases, and acceptance criteria.

#### 4.2.1 Validation Test Strategy

**Operational Scenarios for TDC**: Define realistic operational scenarios representing actual railway train door operations.

**TDC Validation Scenarios** (minimum 10 for SIL 3):

1. **Normal Operation Scenarios**:
   - **SCEN-VAL-001**: Normal door opening at station stop (train stationary, doors unlocked, open button pressed)
   - **SCEN-VAL-002**: Normal door closing after passenger boarding (close button pressed, no obstruction)
   - **SCEN-VAL-003**: Multiple door open/close cycles (10 cycles, all doors synchronized)

2. **Degraded Operation Scenarios**:
   - **SCEN-VAL-004**: Door position sensor failure (one sensor fails, system uses redundant sensor)
   - **SCEN-VAL-005**: Door actuator partial failure (reduced motor power, slower operation)
   - **SCEN-VAL-006**: Communication fault with brake system (safe state: doors remain closed)

3. **Emergency Scenarios**:
   - **SCEN-VAL-007**: Emergency brake activation during door operation (doors immediately close or remain closed)
   - **SCEN-VAL-008**: Obstacle detection during door closing (doors reopen, alarm activated)
   - **SCEN-VAL-009**: Emergency door release (passenger activates emergency release, door opens, alarm activated)
   - **SCEN-VAL-010**: Train motion detection during door operation (doors immediately close if train moving)

4. **Recovery Scenarios**:
   - **SCEN-VAL-011**: Fault recovery after sensor failure (system recovers to normal operation after sensor replacement)
   - **SCEN-VAL-012**: Safe state entry and exit (system enters safe state on critical fault, exits after fault cleared)

5. **Environmental Stress Scenarios**:
   - **SCEN-VAL-013**: High temperature operation (+70°C ambient, doors operate normally)
   - **SCEN-VAL-014**: Low temperature operation (-40°C ambient, doors operate normally)
   - **SCEN-VAL-015**: EMI stress testing (doors operate normally under EMI per EN 50121)

**Black-Box Approach**: Tests SHALL be based on external observable behavior (door position, alarm states, HMI feedback) — NOT on internal implementation (internal variables, state machine states).

#### 4.2.2 Test Case Development

**Test Case Format** (see Appendix A for full template):
```
Test Case ID: TC-VAL-NNN
Scenario: [Scenario name]
Objective: [What is being validated - fitness for intended use]
Preconditions: [System state before test]
Test Steps: [Step-by-step procedure]
Expected Results: [Observable outcomes]
Acceptance Criteria: [Pass/fail criteria]
SIL Level: 3
Traceability: REQ-XXX (requirements traced)
```

**Coverage**: All SRS software requirements SHALL be traced to at least one validation test case (100% coverage).

#### 4.2.3 Performance Test Planning (MANDATORY SIL 3)

**Performance Tests** (EN 50128 Table A.18):

| Performance Aspect | Test Method | Acceptance Criteria | SIL 3 Requirement |
|-------------------|-------------|---------------------|-------------------|
| **Response Time** | Timing measurement (oscilloscope) | ≤ 50ms for safety-critical functions (door close on train motion detect) | **M** |
| **Throughput** | Message rate testing | ≥ 100 messages/sec on CAN bus (per system requirements) | **M** |
| **CPU Usage** | RTOS profiler | ≤ 70% CPU under worst-case load | **M** |
| **Memory Usage** | Static analysis + runtime profiler | ≤ 85% RAM usage (15% margin for safety) | **M** |
| **WCET** | Timing analysis tool | WCET ≤ allocated time budget for all time-critical functions | **M** |
| **Reliability** | Long-duration testing | MTBF ≥ 10,000 hours (per system requirements), 72 hours continuous operation without failure | **M** |

**Performance Test Cases** (minimum 12 for SIL 3):
- TC-PERF-001 to TC-PERF-006: Response time for all safety-critical functions
- TC-PERF-007 to TC-PERF-009: CPU usage under normal, high, worst-case load
- TC-PERF-010 to TC-PERF-012: Memory usage, WCET, long-duration reliability

#### 4.2.4 Deliverables
- Validation Test Specification (DOC-VAL-TEST-SPEC-2026-001) — all scenarios and test cases
- Test case register (CSV file with all TC-VAL-NNN entries)
- Performance test plan (TC-PERF-NNN entries)
- Requirements traceability matrix (SRS requirements → validation test cases)

### 4.3 Phase 7: Validation Test Execution

**Objective**: Execute validation tests in target environment and collect results.

#### 4.3.1 Test Execution Process

1. **Environment Setup**: Configure railway test facility, install target hardware, connect all sensors/actuators
2. **Pre-Test Verification**: Verify test environment ready (all interfaces connected, power supply stable, instrumentation calibrated)
3. **Test Execution**: Execute test cases per Validation Test Specification
4. **Result Recording**: Record test results (pass/fail), screenshots, oscilloscope traces, log files
5. **Defect Logging**: Log any defects found during testing (severity: Critical/Major/Minor)
6. **Re-Test**: Re-execute failed tests after developer fixes defects (regression testing)

**Customer Involvement**: Customer representatives SHALL witness critical tests (emergency scenarios SCEN-VAL-007 to SCEN-VAL-010) — MANDATORY SIL 3.

#### 4.3.2 Test Execution Checklist

- [ ] Target hardware configured correctly (production control unit, actual sensors/actuators)
- [ ] Production build installed (not debug build) — verified by CM baseline record
- [ ] All external interfaces connected (door sensors, actuators, brake interface, HMI)
- [ ] Environmental conditions match operational conditions (temperature, vibration if applicable)
- [ ] Test data prepared (input sequences, expected output data)
- [ ] Test tools calibrated (oscilloscope, logic analyzer calibrated within 12 months)
- [ ] Customer representative present for critical tests (emergency scenarios)
- [ ] Test instrumentation recording (oscilloscope traces, log files, video if needed)

#### 4.3.3 Test Result Recording

**For Each Test Case**:
- Test case ID (TC-VAL-NNN or TC-PERF-NNN)
- Execution date and time
- Tester name
- Test result (Pass / Fail / Blocked)
- Actual results (door position readings, timing measurements, oscilloscope traces, log excerpts)
- Defects found (if any) — link to defect report
- Customer witness signature (for critical acceptance tests)

**Test Result Format** (CSV file):
```
TestCaseID,ExecutionDate,Tester,Result,ActualResults,DefectsFound,CustomerWitness
TC-VAL-001,2026-06-15,John Doe,Pass,"Doors opened in 1.2s, position sensor confirmed",None,Jane Smith
TC-VAL-007,2026-06-16,John Doe,Fail,"Doors did not close within 50ms on brake activation",DEFECT-VAL-012,Jane Smith
```

#### 4.3.4 Defect Management

**Defect Severity Classification**:
- **Critical**: Prevents intended use, safety hazard (e.g., doors open while train moving)
- **Major**: Significant functional issue, workaround exists (e.g., doors slow to respond)
- **Minor**: Cosmetic or low-impact issue (e.g., HMI display formatting)

**Defect Handling** (SIL 3):
- **Critical defects**: MUST be fixed before acceptance (no exceptions)
- **Major defects**: MUST be fixed or justified with risk analysis (customer approval required)
- **Minor defects**: Can be deferred to future release (with customer approval)

**SIL 3 Acceptance Rule**: All Critical and Major defects MUST be resolved before VAL issues AGREE decision.

### 4.4 Phase 7: Performance Validation (Mandatory SIL 3)

**Objective**: Validate that TDC software meets all performance requirements in target environment.

#### 4.4.1 Timing Analysis

**Method**: Measure execution time for all time-critical functions using oscilloscope and GPIO toggle.

**Time-Critical Functions**:
- Door close on train motion detection: ≤ 50ms (safety-critical)
- Obstacle detection and door reopen: ≤ 100ms
- Emergency brake response (door close): ≤ 50ms

**Acceptance Criteria**: All timing requirements met per SRS performance requirements (no exceptions for SIL 3).

**Tools**: Oscilloscope (Tektronix MSO54 or equivalent, calibrated), logic analyzer, RTOS profiler

#### 4.4.2 Load Testing

**Method**: Test TDC system under maximum expected load (all doors operating simultaneously, all sensors active, CAN bus at maximum message rate).

**Worst-Case Scenario**: All doors opening/closing simultaneously while processing emergency brake signal and obstacle detection inputs.

**Acceptance Criteria**: System remains stable, no missed deadlines, no buffer overflows, CPU usage ≤ 70%.

#### 4.4.3 Resource Usage Analysis

**Method**: Measure CPU usage, memory usage, stack depth using RTOS profiler and static analysis tools.

**Acceptance Criteria** (SIL 3): 
- CPU usage ≤ 70% of maximum (30% margin for safety)
- Memory usage ≤ 85% of available RAM (15% margin for safety)
- Stack usage ≤ 70% of allocated per task (30% margin to prevent overflow)

**Tools**: RTOS-aware debugger, static stack analysis tool (IAR Embedded Workbench or GCC with -fstack-usage)

#### 4.4.4 Reliability Testing

**Method**: Long-duration testing (continuous operation for 72 hours minimum).

**Test Procedure**: Run TDC system continuously for 72 hours with cyclic door operations (open/close every 5 minutes simulating station stops).

**Acceptance Criteria**: No crashes, memory leaks, or performance degradation over 72 hours.

**Monitoring**: CPU usage, memory usage, response time logged every 10 minutes; automated test script checks for anomalies.

**SIL 3**: Minimum 72 hours continuous operation without failure (recommended for SIL 3 railway systems).

### 4.5 Phase 7: Acceptance Testing

**Objective**: Customer-witnessed testing and formal acceptance.

#### 4.5.1 Acceptance Test Process

1. **Customer Review**: Customer reviews Validation Test Specification and approves test plan
2. **Witness Testing**: Customer witnesses execution of critical test cases (all emergency scenarios SCEN-VAL-007 to SCEN-VAL-010)
3. **Results Review**: Customer reviews all validation test results (functional and performance)
4. **Defect Review**: Customer reviews all open defects and accepts risk (or requests additional fixes)
5. **Acceptance Decision**: Customer provides formal acceptance or rejection
6. **Acceptance Certificate**: Customer signs Customer Acceptance Certificate (see Appendix C)

#### 4.5.2 Acceptance Criteria (Summary for SIL 3)

Software SHALL be accepted for railway operational use ONLY if all of the following criteria are met:

- [ ] All validation test cases executed (100%)
- [ ] All validation test cases passed (or failures justified with risk analysis and customer approval)
- [ ] All Critical defects resolved (0 open Critical defects)
- [ ] All Major defects resolved or accepted by customer (with risk justification)
- [ ] All performance requirements met per SRS (response time, CPU, memory, reliability)
- [ ] All safety requirements validated (all Hazard Log hazards mitigated)
- [ ] Traceability complete (SRS requirements → validation tests, 100% coverage)
- [ ] Validation Report complete and approved (item 25)
- [ ] Customer Acceptance Certificate signed
- [ ] Independent validation performed (VAL independent from DES, IMP, TST, VER)

---

## 5. TRACEABILITY TO REQUIREMENTS

### 5.1 Validation Traceability Matrix

**Format**: All SRS requirements SHALL be traced to validation test cases (100% coverage for SIL 3).

**Traceability Matrix** (example):

| Requirement ID | Requirement Description | Validation Test Case(s) | Test Result | Status |
|----------------|------------------------|-------------------------|-------------|--------|
| REQ-FUNC-001 | Door shall open within 2 seconds of open button press | TC-VAL-001, TC-VAL-015 | Pass | Validated |
| REQ-FUNC-002 | Door shall close within 3 seconds of close button press | TC-VAL-002 | Pass | Validated |
| REQ-SAFE-001 | Door shall close within 50ms of train motion detection | TC-VAL-010, TC-PERF-001 | Pass | Validated |
| REQ-SAFE-002 | Door shall reopen within 100ms of obstacle detection | TC-VAL-008, TC-PERF-002 | Pass | Validated |
| REQ-PERF-001 | CPU usage shall not exceed 70% under worst-case load | TC-PERF-007, TC-PERF-008 | Pass | Validated |
| REQ-PERF-002 | Memory usage shall not exceed 85% of available RAM | TC-PERF-010 | Pass | Validated |

**Coverage Verification**: Validator SHALL verify 100% traceability completeness before issuing final Validation Report.

**Traceability Tool**: `workspace.py trace` commands (see Section 10.1).

**Matrix Location**: `evidence/traceability/doc25_to_doc6.csv` (Validation Report → SRS requirements)

### 5.2 Traceability Verification

**Verification Method**:
1. VAL reviews SRS (item 6) and lists all requirements
2. VAL reviews Validation Test Specification and lists all test cases
3. VAL creates traceability matrix (SRS requirements → validation test cases)
4. VAL verifies 100% coverage (every SRS requirement has ≥1 validation test case)
5. VAL verifies backward traceability (every validation test case traces to ≥1 SRS requirement)
6. VAL uses `workspace.py trace gate-check --phase validation --sil 3` to verify T-rule compliance

**Acceptance Criteria**: 100% forward and backward traceability (SIL 3 mandatory).

---

## 6. VALIDATION EVIDENCE MANAGEMENT

### 6.1 Evidence Collection

**Evidence Types**:
- Validation Test Specification (DOC-VAL-TEST-SPEC-2026-001)
- Validation Test Results (CSV files, log files, oscilloscope traces, video recordings)
- Performance test results (timing data, profiling reports, long-duration test logs)
- Defect reports and resolutions (defect tracking system exports)
- Traceability matrix (SRS requirements → validation tests, CSV file)
- Customer Acceptance Certificate (signed by customer representative)
- Software Validation Report (item 25, DOC-VALRPT-2026-001)
- Tools Validation Report (item 26, if tool qualification required)
- Release Note (item 27)

**Evidence Location**: `evidence/validation/` (under Git version control per SCMP)

**Evidence Storage Structure**:
```
evidence/
  validation/
    test-specifications/
      Validation-Test-Specification-v1.0.md
    test-results/
      TC-VAL-001-results.csv
      TC-VAL-001-oscilloscope-trace.png
      TC-VAL-007-video.mp4
      ...
    performance-results/
      TC-PERF-001-timing-data.csv
      TC-PERF-007-cpu-usage-profile.csv
      long-duration-test-log.txt
    defects/
      DEFECT-VAL-001-report.md
      DEFECT-VAL-012-resolution.md
    traceability/
      doc25_to_doc6.csv  (Validation Report → SRS)
    acceptance/
      Customer-Acceptance-Certificate-signed.pdf
    reports/
      Software-Validation-Report-v1.0.md  (item 25)
      Tools-Validation-Report-v1.0.md     (item 26, if needed)
      Release-Note-v1.0.md                (item 27)
```

### 6.2 Evidence Review

**Review Process** (SIL 3):
1. **Independent Validator reviews all evidence** (VAL reviews test results, defect resolutions, traceability)
2. **QA Manager reviews validation report** (QUA format-gate on items 25, 26, 27)
3. **Customer reviews test results and defects** (customer approval before acceptance)
4. **VMGR reviews validation evidence** (VMGR reviews item 25 for FINAL V&V decision)

**Review Criteria**:
- Evidence is complete (all test cases executed, all results recorded)
- Evidence is objective (customer-witnessed, tool-generated measurements, not subjective assessment)
- Evidence demonstrates fitness for intended use in railway operational environment
- Evidence is traceable to SRS requirements (100% coverage)
- Evidence is under configuration control (baseline recorded in SCMP)

### 6.3 Evidence Archival

**Archival Process**:
- All validation evidence SHALL be baselined per SCMP Section 4.2
- Evidence SHALL be included in release package (baseline archive)
- Evidence SHALL be retained per project records retention policy (minimum 10 years for railway safety-critical software)

**SIL 3**: Evidence SHALL be independently reviewed and approved by VMGR before customer acceptance.

**Baseline Tag**: `baseline-validation-v1.0` (Git tag per SCMP)

---

## 7. VALIDATION ACCEPTANCE CRITERIA

### 7.1 Overall Acceptance Criteria (SIL 3)

TDC software SHALL be accepted for railway operational use ONLY if all of the following criteria are met:

| Criterion | Description | Evidence Required | SIL 3 Requirement |
|-----------|-------------|-------------------|-------------------|
| **Test Execution** | All validation test cases executed (100%) | Validation Test Results CSV | **M** |
| **Test Pass Rate** | 100% pass rate (or failures justified with risk analysis and customer approval) | Test results summary, risk justification for any failures | **M** |
| **Requirements Coverage** | 100% SRS requirements traced to validation tests | Traceability matrix (doc25_to_doc6.csv) | **M** |
| **Performance** | All performance requirements met (timing, CPU, memory, reliability) | Performance test results (TC-PERF-NNN) | **M** |
| **Defects** | All Critical defects resolved, all Major defects resolved or customer-approved | Defect report (0 open Critical, 0 open Major or risk-justified) | **M** |
| **Customer Acceptance** | Customer provides signed Acceptance Certificate | Customer Acceptance Certificate (Appendix C) | **M** |
| **Independence** | Independent validation performed (VAL independent from DES, IMP, TST, VER) | Organization chart, independence verification | **M** |
| **Safety Validation** | All Hazard Log hazards mitigated and validated | Safety validation results (all hazards addressed) | **M** |
| **Traceability** | End-to-end traceability complete (System Requirements → SRS → Validation Tests) | T-rule gate-check PASS (workspace.py trace gate-check) | **M** |
| **Configuration Control** | All validation artifacts baselined | CM baseline record (baseline-validation-v1.0) | **M** |

### 7.2 Conditional Acceptance

**SIL 3 Rule**: Conditional acceptance is NOT allowed for SIL 3 railway software. All acceptance criteria MUST be met (no exceptions).

**Rationale**: SIL 3 is a safety-critical level requiring the highest confidence in software fitness for operational use. Conditional acceptance with open defects is not acceptable.

**Minor Defects**: Minor defects (cosmetic, low-impact) MAY be deferred to future release with customer approval, but do NOT constitute a "conditional acceptance" — software is either ACCEPTED (all criteria met) or REJECTED (criteria not met).

### 7.3 Release Decision Authority

**Per EN 50128 §5.1.2.8**: Validator has final authority to AGREE or DISAGREE with software release for operational use.

**AGREE Decision**: VAL issues AGREE if all acceptance criteria met → software may proceed to deployment (Phase 9)

**DISAGREE Decision**: VAL issues DISAGREE if any acceptance criterion not met → software BLOCKED from deployment; defects must be fixed and validation re-executed

**FINAL Decision**: VAL's AGREE/DISAGREE decision is FINAL and cannot be overridden by PM, COD, or VMGR.

---

## 8. VALIDATION SCHEDULE

### 8.1 Validation Milestones

| Milestone | Planned Phase | Planned Date | Validation Activities | Deliverable |
|-----------|---------------|--------------|------------------------|-------------|
| **SVaP Baseline** | Phase 1 (Planning) | 2026-04-02 | SVaP approved and baselined | This document (DOC-SVaP-2026-001) |
| **Requirements Validation** | Phase 2 (Requirements) | 2026-05-15 | Customer review of SRS, scenario identification | Requirements validation sign-off |
| **Test Planning** | Phase 7 (Validation) | 2026-08-01 | Develop Validation Test Specification | DOC-VAL-TEST-SPEC-2026-001 |
| **Test Environment Setup** | Phase 7 (Validation) | 2026-08-15 | Configure railway test facility, target hardware | Test readiness report |
| **Functional Test Execution** | Phase 7 (Validation) | 2026-09-01 | Execute all TC-VAL-NNN test cases | Validation test results (functional) |
| **Performance Testing** | Phase 7 (Validation) | 2026-09-15 | Execute all TC-PERF-NNN test cases | Performance test results |
| **Acceptance Testing** | Phase 7 (Validation) | 2026-09-30 | Customer-witnessed critical tests | Customer Acceptance Certificate |
| **Validation Report** | Phase 7 (Validation) | 2026-10-15 | Final validation report | DOC-VALRPT-2026-001 (item 25) |
| **Release Decision** | Phase 7 (Validation) | 2026-10-20 | VAL issues AGREE/DISAGREE | Release Note (item 27) |

### 8.2 Validation Effort Estimate

| Activity | Effort (person-hours) | Notes |
|----------|-----------------------|-------|
| **SVaP authoring** (Phase 1) | 24 hours | This document |
| **Requirements validation** (Phase 2) | 16 hours | Customer meetings, scenario identification |
| **Test planning** (Phase 7) | 80 hours | Validation Test Specification development (15 scenarios, 50+ test cases) |
| **Test environment setup** (Phase 7) | 40 hours | Railway test facility configuration, target hardware installation |
| **Functional test execution** (Phase 7) | 120 hours | All TC-VAL-NNN test cases (15 scenarios, 50+ test cases) |
| **Performance testing** (Phase 7) | 80 hours | Timing analysis, load testing, WCET, long-duration testing (72 hours continuous + analysis) |
| **Acceptance testing** (Phase 7) | 32 hours | Customer-witnessed tests (4 days × 8 hours) |
| **Defect investigation and re-testing** (Phase 7) | 40 hours | Analyze defects, coordinate with developers, re-execute failed tests |
| **Validation report** (Phase 7) | 32 hours | Software Validation Report (item 25), Tools Validation Report (item 26), Release Note (item 27) |
| **Evidence review and archival** (Phase 7) | 16 hours | Evidence collection, review, baseline |
| **Total** | **480 hours** | ~60 person-days (3 months with 1 FTE VAL + 0.5 FTE test support) |

**SIL 3 Note**: Effort includes 30% overhead for independent validation activities, additional performance testing, and customer coordination compared to SIL 0-2.

---

## 9. RISK MANAGEMENT

### 9.1 Validation Risks

| Risk ID | Risk | Probability | Impact | Mitigation |
|---------|------|-------------|--------|------------|
| **RISK-VAL-001** | Target hardware unavailable for validation testing | Medium | High | Order target hardware early (Phase 3), procure backup unit, use high-fidelity simulator as fallback |
| **RISK-VAL-002** | Customer unavailable for acceptance testing (schedule conflict) | Medium | High | Schedule acceptance tests 2 months in advance, confirm customer availability in writing, identify backup customer representative |
| **RISK-VAL-003** | Performance requirements not met (timing violations, resource overruns) | Medium | Critical | Monitor performance early (Phase 4 Component Design, Phase 5 Implementation), allocate time for optimization in schedule, involve performance expert if needed |
| **RISK-VAL-004** | Validator independence compromise (organizational pressure, resource conflicts) | Low | Critical | Enforce organizational independence per §5.1.2.10f, VAL reports to Safety Authority not PM, document independence in SQAP, VMGR monitors independence monthly |
| **RISK-VAL-005** | Railway test facility not available (facility scheduling conflict) | Low | High | Reserve test facility early (6 months in advance), identify backup facility, consider mobile test rig |
| **RISK-VAL-006** | Environmental conditions not achievable (temperature chamber, EMI chamber unavailable) | Low | Medium | Partner with accredited test lab (e.g., railway testing institute), schedule environmental testing early, consider on-site environmental testing if feasible |
| **RISK-VAL-007** | Critical defects found late in Phase 7 (schedule delay) | Medium | High | Perform early validation activities in Phase 2 (requirements validation), coordinate with VER to catch defects early in verification, allocate buffer time in schedule |
| **RISK-VAL-008** | Test instrumentation failure (oscilloscope, logic analyzer malfunction) | Low | Medium | Maintain calibrated backup instrumentation, have service contract with test equipment vendor, verify equipment calibration before test execution |

### 9.2 Risk Monitoring

**Risk Review Frequency**: Monthly during Phases 1–6; weekly during Phase 7 (Validation execution)

**Risk Owner**: Validator (VAL)

**Escalation**: Critical risks (RISK-VAL-003, RISK-VAL-004) escalated immediately to VMGR and COD

**Risk Register**: Maintained in `docs/risk/Validation-Risk-Register.csv` (updated at each review)

---

## 10. VALIDATION TOOLS AND RESOURCES

### 10.1 Test Tools

| Tool | Purpose | SIL 3 Requirement | Qualification Status |
|------|---------|-------------------|----------------------|
| **Unity Test Framework** | Background (unit/integration tests by TST/VER) | All SILs | T2 (VER qualified in SVP) |
| **Oscilloscope (Tektronix MSO54)** | Timing measurements, signal analysis | **M** (performance testing) | T3 (increased confidence from use) |
| **Logic Analyzer** | CAN bus analysis, multi-signal capture | HR | T3 (increased confidence from use) |
| **RTOS Profiler (IAR Embedded Workbench)** | CPU usage, memory usage, task profiling | **M** (performance testing) | T2 (tool qualification report required) |
| **Environmental Chamber** | Temperature testing (-40°C to +70°C) | HR (SIL 3 recommended) | T3 (accredited test lab equipment) |
| **EMI Test Chamber** | EMI stress testing per EN 50121 | R (if EMI requirements in SRS) | T3 (accredited test lab equipment) |
| **Video Recording Equipment** | Customer acceptance testing (witness evidence) | HR | T3 (increased confidence from use) |
| **workspace.py (traceability tool)** | Traceability verification (T-rule gate-check) | **M** (SIL 3 traceability) | T2 (platform-provided, automated verification) |

**Tool Qualification Notes**:
- T2 tools require formal qualification per §6.7.4.5 (Tool Qualification Report)
- T3 tools do NOT require formal qualification but evidence of use and increased confidence (per §6.7.4.6)
- If any T1 tool is used (affects deliverable content), Tools Validation Report (item 26) SHALL be produced

### 10.2 workspace.py Commands for Validation

```bash
# Submit SVaP to workflow after authoring (Phase 1)
python3 tools/workspace.py wf submit DOC-SVaP-2026-001 \
  --path docs/phase-1-planning/Software-Validation-Plan.md \
  --author-role VAL \
  --author-name 'Jane Validator' \
  --sil 3

# Submit Validation Report to workflow (Phase 7)
python3 tools/workspace.py wf submit DOC-VALRPT-2026-001 \
  --path evidence/validation/reports/Software-Validation-Report-v1.0.md \
  --author-role VAL \
  --author-name 'Jane Validator' \
  --sil 3

# Verify traceability completeness before release (Phase 7)
# T-rule gate check for validation phase (checks all T-rules applicable up to Phase 7)
python3 tools/workspace.py trace gate-check \
    --phase validation \
    --sil 3

# Mark a traceability link as VAL-verified in the matrix (Phase 7)
python3 tools/workspace.py trace verify-link \
    --matrix doc25_to_doc6 \
    --source VAL-TEST-001 \
    --target REQ-FUNC-001 \
    --role VAL \
    --name 'Jane Validator'

# Generate requirements coverage report (SRS → validation tests)
python3 tools/workspace.py trace report \
    --from requirements --to tests --format markdown \
    --output evidence/validation/requirements_coverage.md

# Record VAL AGREE decision for release (Phase 7)
python3 tools/workspace.py wf review DOC-VALRPT-2026-001 \
  --role VAL \
  --name 'Jane Validator' \
  --approve \
  --comment "Validation complete. All acceptance criteria met. AGREE for release."
```

### 10.3 Resource Requirements

**Personnel**:
- **Validator (primary)**: 1 FTE for 3 months (Phase 7) — SIL 3 independent validator
- **Test Support Engineer**: 0.5 FTE for 2 months (Phase 7) — execute tests under VAL direction
- **Customer Representative**: 4 days for acceptance testing (Phase 7) — witness critical tests

**Hardware**:
- **Target control unit** (production hardware): 2 units (1 primary, 1 backup)
- **Door hardware** (sensors, actuators): Railway test facility provides
- **Test equipment**: Oscilloscope (Tektronix MSO54), logic analyzer, RTOS-aware debugger
- **Environmental chamber**: Access to accredited test lab (if temperature/EMI testing required)

**Facilities**:
- **Railway test facility** with door hardware installed on test rig (reserved for 2 months)
- **Environmental test chamber** (for temperature -40°C to +70°C testing, if required)
- **EMI test chamber** (for EMI testing per EN 50121, if required)

**Estimated Cost**:
- Personnel: 3 months × 1.5 FTE = 4.5 person-months
- Hardware: €20,000 (2 target control units)
- Test facility rental: €10,000 (2 months)
- Environmental testing (test lab): €5,000 (if needed)
- **Total estimated cost**: €35,000 - €40,000

---

## 11. COMPLIANCE MATRIX

### 11.1 EN 50128 Section 7.7 Compliance

| Requirement | Section | Evidence | Status |
|-------------|---------|----------|--------|
| **Validation plan established** | 7.7.2 | This document (DOC-SVaP-2026-001) | ✓ |
| **Validation independence (SIL 3)** | 7.7.3, §5.1.2.10f | Section 2.2, Section 2.4 | ✓ |
| **Validation in target environment** | 7.7.4 | Section 3.3, Section 4.3 | ✓ |
| **Operational scenarios defined** | 7.7.5 | Section 4.2.1 (15 scenarios) | ✓ |
| **Performance testing (SIL 3 M)** | Table A.7 | Section 4.4 (6 performance tests) | ✓ |
| **Acceptance testing** | 7.7.6 | Section 4.5 | ✓ |
| **Validation report planned** | 7.7.7 | Section 6.1 (item 25 deliverable) | ✓ |
| **Release decision authority** | §5.1.2.8 | Section 2.1, Section 7.3 | ✓ |

### 11.2 EN 50128 Table A.7 Compliance (Validation Techniques)

| # | Technique | SIL 3 | Implementation | Section |
|---|-----------|-------|----------------|---------|
| **1** | Functional and Black-Box Testing | **M** | Operational scenarios (TC-VAL-001 to TC-VAL-015) | 4.2, 4.3 |
| **2** | Performance Testing | **M** | Timing, CPU, memory, WCET, reliability (TC-PERF-001 to TC-PERF-012) | 4.4 |
| **3** | Boundary Value Analysis | **M** | Safety-critical input boundaries tested | 3.2 |
| **4** | Regression Testing | **M** | Re-execute all tests after defect fixes | 4.3.1 step 6 |
| **5** | Equivalence Classes | HR | Input space partitioning | 3.2 |

**Compliance Status**: All MANDATORY techniques implemented for SIL 3 ✓

---

## 12. REFERENCES

### 12.1 Normative References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[EN50126-1]** | EN 50126-1:2017 Railway applications - RAMS Part 1 |
| **[EN50126-2]** | EN 50126-2:2017 Railway applications - RAMS Part 2 |

### 12.2 Project References

| Reference | Document | Location |
|-----------|----------|----------|
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 | `docs/phase-1-planning/Software-Quality-Assurance-Plan.md` |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-2026-001 | `docs/phase-1-planning/Software-Configuration-Management-Plan.md` |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 | `docs/phase-1-planning/Software-Verification-Plan.md` |
| **[SRS]** | Software Requirements Specification (Phase 2) | `docs/phase-2-requirements/Software-Requirements-Specification.md` |
| **[HAZLOG]** | Hazard Log | `docs/system/Hazard-Log.md` |

---

## APPENDICES

### Appendix A: Validation Test Case Template

```markdown
# Validation Test Case

**Test Case ID**: TC-VAL-NNN  
**Scenario**: [Scenario name]  
**SIL Level**: 3

## Objective
[What is being validated - fitness for intended use in railway operational environment]

## Traceability
**Requirements**: REQ-FUNC-NNN, REQ-PERF-NNN  
**Hazards**: HAZ-NNN (if safety-critical)

## Preconditions
[System state before test, environment setup]
- Target hardware installed and configured
- Production build loaded (baseline version X.Y.Z)
- All sensors and actuators connected and calibrated
- Test environment verified ready

## Test Steps
1. [Step 1 - e.g., Press door open button]
2. [Step 2 - e.g., Observe door position sensor]
3. [Step 3 - e.g., Verify door fully open within 2 seconds]
4. [Step 4 - e.g., Press door close button]
5. [Step 5 - e.g., Verify door fully closed within 3 seconds]

## Expected Results
[Observable outcomes that demonstrate correct behavior]
- Door opens within 2 seconds ±0.1s
- Door position sensor indicates OPEN state
- HMI displays "DOOR OPEN" message
- Door closes within 3 seconds ±0.1s
- Door position sensor indicates CLOSED state
- HMI displays "DOOR CLOSED" message

## Acceptance Criteria
**Pass**: All expected results achieved, timing within tolerance  
**Fail**: Any expected result not achieved, or timing violation

## Test Data
[Input data, test fixtures]
- Open button press: digital input high for 100ms
- Close button press: digital input high for 100ms

## Test Environment
**Hardware**: TDC Target Control Unit v2.0, Door Hardware Test Rig  
**Software**: TDC Production Build baseline-tdc-v1.0.0  
**Environmental Conditions**: Ambient temperature +20°C ±2°C, no EMI stress

## Test Results
**Execution Date**: 2026-09-01  
**Tester**: [Tester Name]  
**Customer Witness**: [Customer Name] (for acceptance tests)  
**Result**: [Pass / Fail / Blocked]  
**Actual Results**: [Recorded observations, timing measurements, screenshots]
- Door opened in 1.8 seconds (oscilloscope measurement)
- Door position sensor indicated OPEN (log file excerpt)
- HMI displayed "DOOR OPEN" (screenshot attached)
- Door closed in 2.9 seconds (oscilloscope measurement)
- Door position sensor indicated CLOSED (log file excerpt)
- HMI displayed "DOOR CLOSED" (screenshot attached)

**Defects Found**: [Defect IDs if any] — None

**Comments**: Test passed all criteria. Customer witness confirmed.

**Customer Signature**: ___________________  **Date**: __________
```

### Appendix B: Software Validation Report Template (Item 25)

```markdown
# Software Validation Report

**DOCUMENT TYPE**: Software Validation Report  
**EN 50128 DELIVERABLE**: Annex C Item 25  
**STANDARD REFERENCE**: EN 50128:2011 Section 7.7.4.6–7.7.4.11  
**PROJECT**: TDC (Train Door Control System)  
**SIL LEVEL**: 3

**Document ID**: DOC-VALRPT-2026-001  
**Validation Date**: 2026-10-15  
**Validator**: [VAL Name]  
**Software Version**: baseline-tdc-v1.0.0

## 1. Validation Scope
This report documents the validation of TDC software version baseline-tdc-v1.0.0 in the target railway operational environment per Software Validation Plan DOC-SVaP-2026-001.

## 2. Validation Activities Performed
- Functional and black-box testing (15 operational scenarios, 50 test cases)
- Performance testing (timing, CPU, memory, WCET, reliability)
- Safety scenario validation (all Hazard Log hazards)
- Acceptance testing (customer-witnessed critical tests)
- Traceability verification (SRS requirements → validation tests, 100%)

## 3. Validation Results Summary
| Test Category | Total Tests | Passed | Failed | Pass Rate |
|---------------|-------------|--------|--------|-----------|
| Functional Tests (TC-VAL-NNN) | 50 | 50 | 0 | 100% |
| Performance Tests (TC-PERF-NNN) | 12 | 12 | 0 | 100% |
| **Total** | **62** | **62** | **0** | **100%** |

## 4. Requirements Traceability
- **Total SRS Requirements**: 45
- **Requirements Validated**: 45 (100%)
- **Traceability Complete**: Yes (T-rule gate-check PASS)

## 5. Defects Summary
| Severity | Found | Resolved | Open | Notes |
|----------|-------|----------|------|-------|
| Critical | 2 | 2 | 0 | All resolved before acceptance |
| Major | 5 | 5 | 0 | All resolved before acceptance |
| Minor | 3 | 1 | 2 | Deferred to v1.1 (customer approved) |

## 6. Performance Validation Results (SIL 3)
| Performance Metric | Requirement | Measured | Status |
|--------------------|-------------|----------|--------|
| Response Time (door close on motion) | ≤ 50ms | 38ms | Pass |
| CPU Usage (worst-case) | ≤ 70% | 62% | Pass |
| Memory Usage | ≤ 85% | 78% | Pass |
| WCET (safety-critical functions) | ≤ allocated budget | Within budget | Pass |
| Reliability (72-hour test) | No failures | No failures | Pass |

## 7. Safety Validation Results
- All Hazard Log hazards validated (SIL 3 mitigation measures effective)
- All safety scenarios passed (emergency brake, obstacle detection, train motion detection)
- Safety integrity verified (no systematic failures observed)

## 8. Validation Conclusion
- **Overall Result**: PASS
- **Fitness for Use**: CONFIRMED — TDC software is fit for intended use in railway operational environment
- **Recommendation**: ACCEPT for deployment in Phase 9

## 9. Release Decision (EN 50128 §5.1.2.8)
**AGREE** — Validator agrees to software release for railway operational use.

All acceptance criteria met per SVaP Section 7.1.

## 10. Acceptance Certificate
**Customer Name**: [Customer Name]  
**Customer Organization**: [Railway Operator]  
**Customer Signature**: _______________________  
**Date**: 2026-10-15

**Validator Name**: [VAL Name]  
**Validator Signature**: _______________________  
**Date**: 2026-10-15
```

### Appendix C: Customer Acceptance Certificate

```markdown
# Customer Acceptance Certificate

**Project**: TDC (Train Door Control System)  
**Software Version**: baseline-tdc-v1.0.0  
**SIL Level**: 3  
**Acceptance Date**: 2026-10-15

## Acceptance Statement

I, [Customer Name], on behalf of [Railway Operator Organization], hereby confirm that:

1. I have reviewed the Software Validation Report (DOC-VALRPT-2026-001)
2. I have witnessed critical validation test executions (emergency scenarios SCEN-VAL-007 to SCEN-VAL-010)
3. I have reviewed all open defects and accept the associated risks (2 Minor defects deferred to v1.1)
4. The TDC software meets the intended use requirements for railway train door control operations
5. The TDC software is fit for deployment in the operational railway environment

## Acceptance Decision

☑ **ACCEPTED** - Software is approved for deployment in railway operations  
☐ **CONDITIONALLY ACCEPTED** - (Not applicable for SIL 3)  
☐ **REJECTED** - (Not applicable - all criteria met)

**Conditions/Notes**: 2 Minor defects (cosmetic HMI issues) deferred to v1.1 per agreement with customer representative. These defects do not affect safety or operational fitness.

## Signatures

**Customer Representative**:  
Name: _______________________  
Title: _______________________  
Organization: [Railway Operator]  
Signature: _______________________  
Date: 2026-10-15

**Validator**:  
Name: [VAL Name]  
Role: Independent Validator (SIL 3)  
Signature: _______________________  
Date: 2026-10-15

**V&V Manager (VMGR)**:  
Name: [VMGR Name]  
Role: V&V Manager (SIL 3)  
Signature: _______________________  
Date: 2026-10-15

**Lifecycle Coordinator (COD)**:  
Name: [COD Name]  
Role: Lifecycle Coordinator  
Signature: _______________________  
Date: 2026-10-15
```

---

## DOCUMENT HISTORY

This document is maintained under configuration control per SCMP DOC-SCMP-2026-001. All changes SHALL be approved by the Change Control Board (CCB).

**Current Version**: 1.0  
**Last Updated**: 2026-04-02  
**Next Review**: Phase 7 (Validation) commencement — 2026-08-01

**Configuration Management**:
- Baseline Tag: `baseline-svap-v1.0` (to be applied after VER 1st-check PASS and COD approval)
- Location: `examples/TDC/docs/phase-1-planning/Software-Validation-Plan.md`
- Under Git control per SCMP Section 4

---

**END OF DOCUMENT**
