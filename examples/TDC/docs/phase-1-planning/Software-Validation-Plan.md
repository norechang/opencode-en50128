# Software Validation Plan (SVaP)

## Document Control

| Field | Value |
|-------|-------|
| **Document ID** | DOC-TDC-SVaP-001 |
| **Version** | 1.0 |
| **Date** | 2026-03-30 |
| **Status** | DRAFT |
| **Author** | Software Validator (VAL) |
| **Project** | TDC (Train Door Control) |
| **SIL Level** | SIL 3 |
| **Standard** | EN 50128:2011 Section 7.7 — Software Validation |

---

## Approvals

**EN 50128 Annex C Table C.1 Signature Chain (Item 5)**

| Written By | 1st Check | 2nd Check | Date |
|------------|-----------|-----------|------|
| Software Validator<br>Name: TBD — assigned at project kick-off<br>Signature: _____________ | Software Verifier<br>Name: TBD — assigned at project kick-off<br>Signature: _____________ | — | 2026-03-30 |

**Notes:**
- **Written By**: VAL authors the Software Validation Plan (EN 50128 Annex C Table C.1, Item 5)
- **1st Check**: VER performs 1st-check (mandatory per deliverables.yaml)
- **2nd Check**: None required (SVaP has no 2nd-check per Annex C Table C.1)
- For SIL 3: VAL independence from development/verification is **MANDATORY** (EN 50128 §5.1.2.10f)

---

## Revision History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-03-30 | VAL Team | Initial SVaP for TDC project (SIL 3) |

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [References](#2-references)
3. [Definitions and Abbreviations](#3-definitions-and-abbreviations)
4. [Validation Organization](#4-validation-organization)
5. [Validation Strategy](#5-validation-strategy)
6. [Validation Techniques (EN 50128 Table A.7)](#6-validation-techniques-en-50128-table-a7)
7. [Validation Environment](#7-validation-environment)
8. [Validation Activities by Phase](#8-validation-activities-by-phase)
9. [System Testing vs Acceptance Testing](#9-system-testing-vs-acceptance-testing)
10. [Performance Validation (SIL 3 Mandatory)](#10-performance-validation-sil-3-mandatory)
11. [Safety Requirements Validation](#11-safety-requirements-validation)
12. [Software/Hardware Integration Validation](#12-softwarehardware-integration-validation)
13. [Traceability Requirements](#13-traceability-requirements)
14. [Validation Tools and Test Automation](#14-validation-tools-and-test-automation)
15. [Validation Deliverables](#15-validation-deliverables)
16. [Roles and Responsibilities](#16-roles-and-responsibilities)
17. [Review and Approval Process](#17-review-and-approval-process)
18. [Validation Schedule](#18-validation-schedule)
19. [Risk Management](#19-risk-management)
20. [EN 50128 Compliance Matrix](#20-en-50128-compliance-matrix)

---

## 1. Introduction

### 1.1 Purpose

This Software Validation Plan (SVaP) defines the validation strategy, activities, and acceptance criteria for the **TDC (Train Door Control)** software development project. Validation confirms that the software fulfills its intended use in its intended operational environment in accordance with **EN 50128:2011 Section 7.7**.

**Validation Definition** (EN 50128:2011 §3.1.60): Confirmation by examination and provision of objective evidence that the particular requirements for a specific intended use are fulfilled.

**Critical Distinction — Verification vs Validation**:

| Aspect | Verification (SVP) | Validation (SVaP) |
|--------|-------------------|-------------------|
| **Question** | "Are we building the product right?" | "Are we building the right product?" |
| **Focus** | Compliance with specifications | Fitness for intended use |
| **Method** | Static analysis, code review, traceability | Operational scenario testing, acceptance testing |
| **Environment** | Development/test environment acceptable | **Target hardware/environment MANDATORY** |
| **Evidence** | Verification reports per phase | Validation report, customer acceptance certificate |
| **Authority** | VER confirms correctness | **VAL gives release agreement/disagreement** (§5.1.2.8) |

The SVaP establishes:
- Validation organization structure and independence requirements (SIL 3 mandatory)
- Validation techniques per EN 50128 Table A.7 (mandatory for SIL 3)
- System-level validation activities in target environment
- Performance validation requirements (mandatory SIL 3)
- Safety requirements validation and traceability to hazards
- Software/hardware integration validation approach
- Acceptance testing criteria with customer involvement
- Validation tools and qualification status
- Validation deliverables per lifecycle phase
- 1-Pass Rule: VAL reports accepted if no Major/Critical findings

### 1.2 Scope

This SVaP applies to **all software validation activities in Phase 7 (Validation)** of the TDC software development project, with preliminary validation activities in Phase 2 (requirements validation).

| Phase | Validation Activities | VAL Deliverables |
|-------|----------------------|------------------|
| Phase 1 | SVaP authoring | This document (DOC-TDC-SVaP-001) |
| Phase 2 | 2nd-check: SRS, OTSS, REQVER | None (2nd-check only) |
| Phase 3 | 2nd-check: SAS, SDS, SIS, integration test specs, ARCHDESIGNVER | None (2nd-check only) |
| Phase 4 | 2nd-check: Component design & test specs | None (2nd-check only) |
| Phase 5 | 2nd-check: Source code, unit test report | None (2nd-check only) |
| Phase 6 | 2nd-check: Integration test spec & report | None (2nd-check only) |
| **Phase 7** | **System validation, acceptance testing** | **Software Validation Report (item 25), Tools Validation Report (item 26 if applicable), Release Note (item 27)** |
| Phase 8 | No VAL touchpoint (ISA-driven) | None |
| Phase 9 | 2nd-check: Deployment plan, manual, release notes, records | None (2nd-check only) |
| Phase 10 | 2nd-check: Maintenance records, change records, maintenance plan | None (2nd-check only) |

**In Scope**:
- System-level validation testing in target environment (Phase 7)
- Operational scenario validation (normal, degraded, emergency, recovery)
- Performance testing (timing, throughput, resource usage — mandatory SIL 3)
- Acceptance testing with customer involvement
- Software/hardware integration validation
- Safety requirements validation (SSRS traceability)
- Release decision authority (AGREE/DISAGREE per §5.1.2.8)

**Out of Scope**:
- Unit testing and integration testing (covered by Software Verification Plan and TST)
- Verification activities (static analysis, code review — covered by SVP and VER)
- Hardware validation (covered by System Safety Plan)
- Phase 8 Assessment (ISA-driven; VAL has no touchpoint)
- Phase 10 Maintenance (covered by Software Maintenance Plan)

### 1.3 SIL Classification

**Target SIL Level**: **SIL 3** (Strict gate enforcement, independent VAL mandatory)

**EN 50128 Validation Requirements** (Table A.7):

| Technique | SIL 0 | SIL 1-2 | **SIL 3-4** | TDC Implementation |
|-----------|-------|---------|-------------|-------------------|
| Functional and Black-Box Testing | HR | HR | **M** | System test suite (operational scenarios) |
| Performance Testing | - | HR | **M** | Timing analysis, load testing, WCET analysis |
| Modelling | - | R | R | Not used (risk-based decision) |
| Regression Testing | HR | HR | **M** | Automated regression suite |
| User Interface Testing | HR | HR | HR | TCMS interface testing |
| Boundary Value Analysis | R | HR | **M** | Speed interlock, door timing boundaries |
| Equivalence Classes | R | HR | HR | Door state equivalence classes |

**SIL 3 Mandatory Techniques Applied**:
- Functional and Black-Box Testing (**M**)
- Performance Testing (**M**)
- Regression Testing (**M**)
- Boundary Value Analysis (**M**)

**Independence Requirements**:
- **SIL 3**: **Independent Validator MANDATORY** (EN 50128 §5.1.2.10f)
- VAL SHALL NOT report to Project Manager
- VAL SHALL NOT have been involved in requirements, design, implementation, integration, or verification
- VAL reports to Safety Authority or Customer (or VMGR for SIL 3-4 coordination)
- VAL's release decision cannot be overridden by PM, COD, or VMGR

### 1.4 Definitions and Abbreviations

| Term | Definition |
|------|------------|
| **Validation** | Confirmation by examination and provision of objective evidence that the particular requirements for a specific intended use are fulfilled (EN 50128 §3.1.60) |
| **Verification** | Confirmation by examination and provision of objective evidence that specified requirements have been fulfilled (EN 50128 §3.1.59) |
| **Acceptance Testing** | Validation testing with customer/user involvement and formal acceptance |
| **Operational Scenario** | Realistic use case in target operational environment (normal, degraded, emergency, recovery) |
| **Black-Box Testing** | Testing based on external behavior without knowledge of internal implementation |
| **Performance Testing** | Testing of timing, throughput, resource usage, WCET |
| **Target Environment** | Actual hardware/software platform where software will operate (DCU hardware, 24 VDC power, -25°C to +55°C) |
| **System Testing** | End-to-end testing of complete system (software + hardware) in target environment |
| **Release Decision** | VAL's final authority to AGREE or DISAGREE for software release (§5.1.2.8) |
| **1-Pass Rule** | QUA format-gate accepts VAL reports if no Major/Critical findings |

| Abbreviation | Meaning |
|--------------|---------|
| **SVaP** | Software Validation Plan (this document) |
| **SVP** | Software Verification Plan |
| **SRS** | Software Requirements Specification |
| **SSRS** | System Safety Requirements Specification |
| **OTSS** | Overall Test Specification (item 7) |
| **DCU** | Door Control Unit — central processing module |
| **DDU** | Door Drive Unit — per-door electromechanical actuator |
| **TCMS** | Train Control and Management System |
| **VAL** | Software Validator (role per EN 50128 §5.3.7) |
| **VER** | Software Verifier (role per EN 50128 §5.3.5) |
| **VMGR** | V&V Manager (independent V&V authority for SIL 3-4) |
| **COD** | Lifecycle Coordinator |
| **ISA** | Independent Safety Assessor (Phase 8) |
| **WCET** | Worst-Case Execution Time |
| **EMI** | Electromagnetic Interference |
| **MTBF** | Mean Time Between Failures |

### 1.5 References

#### 1.5.1 Normative References

| Reference | Document | Version |
|-----------|----------|---------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems | 2011 |
| **[EN50126]** | EN 50126:2017 Railway applications - RAMS (Part 1 & 2) | 2017 |
| **[EN50129]** | EN 50129:2018 Railway applications - Safety-related electronic systems for signalling | 2018 |
| **[EN13272]** | EN 13272 Railway applications — Doors for passenger rolling stock | Current |
| **[IEC61508]** | IEC 61508 Functional Safety | 2010 |

#### 1.5.2 Project References

| Reference | Document | Location |
|-----------|----------|----------|
| **[SQAP]** | Software Quality Assurance Plan | DOC-TDC-SQAP-001 v1.0 DRAFT |
| **[SVP]** | Software Verification Plan | DOC-TDC-SVP-001 v1.0 DRAFT |
| **[SCMP]** | Software Configuration Management Plan | DOC-TDC-SCMP-001 v1.0 DRAFT |
| **[SYS-SRS]** | System Requirements Specification | DOC-TDC-SRS-SYS-001 v1.0 APPROVED |
| **[SYS-SSRS]** | System Safety Requirements Specification | DOC-TDC-SSRS-SYS-001 v1.0 APPROVED |
| **[SYS-SAD]** | System Architecture Description | DOC-TDC-SAD-SYS-001 v1.0 APPROVED |
| **[SYS-SSP]** | System Safety Plan | DOC-TDC-SSP-SYS-001 v1.0 APPROVED |

---

## 2. References

See Section 1.5 above.

---

## 3. Definitions and Abbreviations

See Section 1.4 above.

---

## 4. Validation Organization

### 4.1 Validation Team Structure

#### 4.1.1 Software Validator (VAL)

**Primary Responsibility**: Independent validation authority for TDC software; holds release decision authority per EN 50128 §5.1.2.8.

**Responsibilities**:
- Author and maintain Software Validation Plan (this document)
- Define operational validation scenarios (normal, degraded, emergency, recovery)
- Coordinate acceptance testing with customer representative
- Execute validation testing in target environment (DCU hardware)
- Perform 2nd-check on deliverables in Phases 1–6, 9–10 (no VAL report produced)
- Analyze validation test results and generate Validation Report (item 25)
- Generate Tools Validation Report (item 26) if tool qualification required
- Author Release Note (item 27) per §7.7.4.12
- **Issue release decision: AGREE or DISAGREE** (§5.1.2.8) — this decision is FINAL
- Report to Safety Authority or VMGR (SIL 3), NOT to Project Manager

**Qualifications** (EN 50128 Table B.7):
- Knowledge of EN 50128 validation requirements (Section 7.7, Table A.7)
- Understanding of train door control systems and railway operational environment
- Experience with system-level testing in embedded safety-critical systems
- Familiarity with railway safety requirements (EN 50126, EN 50129)
- Knowledge of performance testing and timing analysis for real-time systems
- Experience with hardware/software integration testing

**Independence Requirements (SIL 3 Mandatory)**:
- VAL SHALL NOT report to Project Manager (§5.1.2.10f)
- VAL SHALL NOT have been involved in requirements, design, implementation, integration, or verification of TDC software
- VAL is organizationally separate from development team
- VAL has independent reporting line to Safety Authority or VMGR
- VAL's release decision cannot be overridden by PM, COD, or VMGR

**Assigned Personnel**: TBD — assigned at project kick-off

#### 4.1.2 Validation Support Roles

| Role | Responsibilities | Independence Required | Assigned |
|------|------------------|-----------------------|----------|
| **Customer Representative** | Define acceptance criteria, witness acceptance tests, sign acceptance certificate | Yes (external) | TBD |
| **Safety Manager (SAF)** | Review safety validation scenarios, approve safety-critical test results, confirm hazard coverage | No | TBD |
| **VMGR (V&V Manager)** | Coordinate VER and VAL activities, review VAL reports, issue FINAL V&V decision to COD | Yes (SIL 3 mandatory) | TBD |
| **QUA (Quality Assurance)** | Perform format-gate on VAL deliverables (1-Pass Rule), oversee validation process | No | TBD |
| **TST (Tester)** | Execute validation tests under VAL direction, collect test data, prepare test logs | No | TBD |
| **VER (Verifier)** | Perform 1st-check on SVaP, author item † (Validation Verification Report) in Phase 7 Track B Step B2 | Yes (SIL 3 mandatory) | TBD |

### 4.2 Independence Management (SIL 3 Mandatory)

**EN 50128 Requirement**: Validator SHALL be independent of development, verification, and project management (§5.1.2.10f).

**Independence Measures Implemented**:

1. **Organizational Independence**:
   - VAL reports to Safety Authority or VMGR (not PM)
   - VAL is not part of development organization
   - VAL has no design, coding, integration, or verification responsibilities

2. **Personnel Independence**:
   - VAL personnel SHALL NOT have participated in TDC requirements, design, implementation, integration, or verification
   - VAL personnel assigned from independent V&V team or external organization
   - VAL personnel have no performance objectives tied to development schedule

3. **Authority Independence**:
   - VAL has authority to reject software for release (DISAGREE decision per §5.1.2.8)
   - VAL findings cannot be overruled by PM, COD, or development team
   - VAL reports defects directly to VMGR and Safety Authority

4. **Process Independence**:
   - VAL receives tasking from VMGR (SIL 3), NOT from PM
   - VAL uses independent validation test specifications (not development test plans)
   - VAL maintains independent validation evidence (separate from verification evidence)

**Verification of Independence**: VMGR verifies VAL independence before Phase 7 validation activities commence.

---

## 5. Validation Strategy

### 5.1 Validation Approach

**Multi-Level Validation Strategy for SIL 3**:

1. **Requirements Validation** (Phase 2):
   - Confirm SRS requirements match customer needs and intended use
   - Validate operational scenarios against System SRS
   - Ensure safety requirements (SSRS) are correctly decomposed into SRS

2. **Scenario-Based Validation** (Phase 7):
   - Test realistic operational scenarios in target environment (DCU hardware)
   - Normal operation: door open/close sequences at station stops
   - Degraded operation: single-sensor failures, communication delays
   - Emergency operation: emergency door release, safe state entry
   - Recovery operation: system restart after fault, fault diagnostics

3. **Performance Validation** (Phase 7 — Mandatory SIL 3):
   - Confirm timing requirements met (obstacle response ≤ 150 ms)
   - Measure WCET for safety-critical functions
   - Validate resource usage (CPU ≤ 80%, memory ≤ 90%, stack ≤ 70%)
   - Long-duration reliability testing (72 hours continuous operation)

4. **Safety Validation** (Phase 7):
   - Validate all safety requirements (SSR-001 to SSR-028) with evidence
   - Confirm hazard mitigation (HAZ-001 to HAZ-009)
   - Test safe state entry and recovery (fault injection)
   - Validate dual-channel operation (2oo2 architecture)

5. **Acceptance Testing** (Phase 7):
   - Customer-witnessed testing of critical scenarios
   - Formal acceptance certificate signed by customer representative
   - Final release decision (AGREE/DISAGREE) by VAL

### 5.2 Validation Philosophy

**"Are We Building the Right Product?"**

Validation focuses on **fitness for intended use**, NOT just compliance with specifications (that's verification's job).

**Key Principles**:
- **Target environment testing**: ALL validation performed on DCU target hardware, not development PC
- **Black-box approach**: Tests based on external behavior, not internal implementation
- **Operational realism**: Scenarios reflect actual railway operations (station stops, emergency situations, environmental conditions)
- **Customer involvement**: Customer representative witnesses acceptance tests and signs acceptance certificate
- **Independence**: VAL is independent from development and has final release authority

**Validation vs Verification Boundary**:

| Activity | Verification (VER) | Validation (VAL) |
|----------|-------------------|------------------|
| Requirements correctness | Yes (traceability to System SRS) | Yes (customer confirms intended use) |
| Code correctness | Yes (MISRA C, static analysis) | No (not VAL's concern) |
| Test coverage | Yes (100% branch + MC/DC) | No (coverage already verified by VER) |
| Functional testing | Yes (unit + integration tests) | Yes (system-level operational scenarios) |
| Performance testing | Yes (timing bounds checked) | **Yes (WCET measured in target environment)** |
| Acceptance testing | No (VER not customer-facing) | **Yes (VAL coordinates with customer)** |
| Release decision | No (VER confirms correctness) | **Yes (VAL gives AGREE/DISAGREE)** |

---

## 6. Validation Techniques (EN 50128 Table A.7)

### 6.1 SIL 3 Mandatory Techniques

The following validation techniques SHALL be applied per EN 50128 Table A.7 for SIL 3:

| # | Technique | SIL 3 | TDC Implementation | EN 50128 Reference |
|---|-----------|-------|-------------------|-------------------|
| **1** | Functional and Black-Box Testing | **M** | System test suite (operational scenarios) | Table A.7 #2, Table A.14 |
| **2** | Performance Testing | **M** | Timing analysis, load testing, WCET | Table A.7 #1, Table A.18 |
| **4** | Regression Testing | **M** | Automated regression suite | Table A.7 #4 |
| **6** | Boundary Value Analysis | **M** | Speed interlock (5 km/h), door timing (8 s, 10 s) | Table A.7 #6 |

### 6.2 SIL 3 Highly Recommended Techniques

| # | Technique | SIL 3 | TDC Implementation | EN 50128 Reference |
|---|-----------|-------|-------------------|-------------------|
| **5** | User Interface Testing | HR | TCMS interface testing (door commands, status signals) | Table A.7 #5 |
| **7** | Equivalence Classes | HR | Door states (open, closed, locked, unlocked, fault) | Table A.7 #7 |

### 6.3 SIL 3 Recommended Techniques

| # | Technique | SIL 3 | TDC Decision | Rationale |
|---|-----------|-------|--------------|-----------|
| **3** | Modelling | R | NOT USED | Risk-based decision: operational scenarios and hardware testing provide sufficient validation evidence without modelling overhead |

### 6.4 Technique Details

#### 6.4.1 Functional and Black-Box Testing (Mandatory SIL 3)

**Method**: Test TDC software based on external behavior (inputs/outputs) without knowledge of internal code structure.

**Implementation**:
- Define operational scenarios (see Section 8.3)
- Execute scenarios on target DCU hardware
- Observe external outputs (door motion, TCMS signals, fault indicators)
- Compare actual behavior to expected behavior (per SRS)

**Coverage**: All SRS functional requirements traced to at least one validation test case.

**EN 50128 Table A.14 Sub-Techniques Applied**:
- Input domain testing (all input combinations)
- Output domain testing (all output states)
- State transition testing (door state machine)
- Syntax testing (TCMS protocol)
- Fault injection (sensor failures, communication faults)

#### 6.4.2 Performance Testing (Mandatory SIL 3)

**Method**: Measure timing, throughput, resource usage in target environment.

**Implementation** (see Section 10):
- **Timing analysis**: Measure obstacle response time (≤ 150 ms), control cycle time (10 ms), door-locked signal response (≤ 10 ms)
- **WCET analysis**: Measure worst-case execution time for safety-critical functions
- **Load testing**: Maximum simultaneous events (all doors closing, all obstacles detected)
- **Resource usage**: CPU load (≤ 80%), memory usage (≤ 90%), stack depth (≤ 70%)
- **Reliability testing**: 72 hours continuous operation

**Tools**: Oscilloscope, logic analyzer, RTOS profiler (if applicable), WCET analysis tool

**EN 50128 Table A.18 Sub-Techniques Applied**:
- Timing analysis (response time, cycle time)
- Load testing (maximum throughput)
- Resource usage analysis (CPU, memory, stack)
- Reliability testing (long-duration)

#### 6.4.3 Regression Testing (Mandatory SIL 3)

**Method**: Re-execute validation tests after any code change to confirm no regression.

**Implementation**:
- Maintain automated regression test suite
- Execute regression suite after every CM baseline change
- Compare current results to previous baseline results
- Block release if any regression detected

**Trigger Events**:
- Code change (any SCMP-controlled file)
- Configuration change (compiler flags, linker script)
- Defect fix
- Requirement change (CCB-approved)

#### 6.4.4 Boundary Value Analysis (Mandatory SIL 3)

**Method**: Test at boundaries of input/output domains where defects are most likely.

**Implementation**:

| Requirement | Boundary Values Tested | Expected Behavior |
|-------------|------------------------|-------------------|
| Speed interlock ≤ 5 km/h (SSR-001) | 0 km/h, 4 km/h, 5 km/h, 6 km/h, 200 km/h | Doors open at ≤ 5 km/h, inhibited at > 5 km/h |
| Door close timeout 10 s (SSR-008) | 0 s, 9.9 s, 10.0 s, 10.1 s | Fault asserted after 10 s |
| Obstacle response ≤ 150 ms (SSR-011) | 0 ms, 149 ms, 150 ms, 151 ms | Door reversal within 150 ms |
| Door open/close cycle 8 s (SYS-FR-012) | 7.9 s, 8.0 s, 8.1 s | Cycle completes within 8 s |

#### 6.4.5 Equivalence Classes (Highly Recommended SIL 3)

**Method**: Partition input/output domains into equivalence classes; test one representative from each class.

**Implementation**:

| Variable | Equivalence Classes | Representative Test Values |
|----------|---------------------|---------------------------|
| Train speed | {0–5 km/h}, {6–200 km/h}, {> 200 km/h}, {invalid} | 2 km/h, 50 km/h, 250 km/h, -10 km/h |
| Door position | {fully open}, {partially open}, {fully closed}, {locked}, {unlocked}, {fault} | 100%, 50%, 0%, locked sensor active, locked sensor inactive, sensor timeout |
| Obstacle sensor | {clear}, {beam broken}, {sensor fault}, {both beams broken} | No break, single break, sensor timeout, dual break |

---

## 7. Validation Environment

### 7.1 Target Environment Description

**Hardware Platform**: Door Control Unit (DCU) — production hardware

| Parameter | Specification | Validation Requirement |
|-----------|---------------|------------------------|
| Processor | TBD (e.g., ARM Cortex-M4, 168 MHz) | Use production DCU hardware |
| Memory | TBD (e.g., 256 KB RAM, 1 MB Flash) | Load production firmware image |
| Power supply | 24 VDC nominal (18–32 VDC range) | Test at 18 VDC, 24 VDC, 32 VDC |
| Ambient temperature | -25°C to +55°C (operational) | Test at -25°C, 0°C, +25°C, +55°C |
| Humidity | 5% to 95% (non-condensing) | Test at 10%, 50%, 90% |
| Vibration | EN 61373 Category 1 Class B | Test with vibration table (optional) |
| EMI/EMC | EN 50121-3-2 | Test in EMI chamber (optional) |

**Software Platform**:
- RTOS or bare-metal (TBD in SRS)
- Production build configuration (optimization enabled, debug disabled)
- Checksums and CRC verified

**Interfaces**:
- TCMS interface (door commands, speed signal, status outputs) — hardware or simulator
- DDU interface (door actuator commands, position sensors) — hardware or HIL simulator
- Obstacle detection sensors (infrared) — hardware or sensor simulator
- Lock sensors — hardware or simulator
- Diagnostic interface (fault logs, debug access) — UART or CAN

### 7.2 Validation Environment vs Development Environment

**Key Differences**:

| Aspect | Development Environment | Validation Environment |
|--------|------------------------|------------------------|
| Hardware | Development PC or evaluation board | **Production DCU hardware** |
| Build | Debug build (symbols, no optimization) | **Production build (optimized, no debug symbols)** |
| Testing | Unit tests, integration tests (white-box) | **System tests (black-box)** |
| Interfaces | Mocked or stubbed | **Real hardware or high-fidelity HIL simulator** |
| Environmental conditions | Room temperature, lab bench | **-25°C to +55°C, vibration, EMI (as feasible)** |
| Test executor | Developer (VER/TST) | **Independent Validator (VAL)** |

**Rationale**: Validation MUST be performed in target environment to confirm fitness for actual operational use (EN 50128 §7.7.4.3).

### 7.3 Test Environment Setup

**Minimum Configuration**:
1. Production DCU hardware (2 units minimum for dual-channel testing)
2. 24 VDC power supply (programmable for voltage variation testing)
3. TCMS interface (hardware or HIL simulator)
4. DDU interface (hardware or HIL simulator) — minimum 2 doors (left + right)
5. Obstacle detection sensors (hardware or simulator)
6. Lock sensors (hardware or simulator)
7. Oscilloscope or logic analyzer (timing measurements)
8. Test control PC (test automation, data logging)

**Optional Configuration**:
- Full door assembly (8 doors per vehicle) for integration testing
- Environmental chamber (-25°C to +55°C)
- Vibration table (EN 61373 testing)
- EMI test chamber (EN 50121-3-2 testing)

**Hardware-in-the-Loop (HIL) Simulator**: If full hardware not available, high-fidelity HIL simulator acceptable for functional validation; performance validation MUST use real hardware.

---

## 8. Validation Activities by Phase

### 8.1 Phase 1 — Planning (Current Phase)

**VAL Activities**:
- Author Software Validation Plan (this document)
- Submit SVaP to VER for 1st-check
- After VER 1st-check PASS: submit to VMGR for acceptance

**VAL Deliverables**:
- Software Validation Plan (DOC-TDC-SVaP-001) — this document

**2nd-Check Activities**:
- 2nd-check SQAP (DOC-TDC-SQAP-001)
- 2nd-check SCMP (DOC-TDC-SCMP-001)
- 2nd-check SVP (DOC-TDC-SVP-001)
- 2nd-check SVaP (N/A — VAL authored it)

### 8.2 Phase 2 — Requirements Specification

**VAL Activities** (2nd-Check Only):
- Review SRS (item 6) for customer needs alignment and operational scenario coverage
- Review Overall Test Specification (item 7) for validation test coverage
- Review Requirements Verification Report (item 8) — VER 1st-check
- Confirm all system safety requirements (SSRS) correctly decomposed into SRS

**VAL Deliverables**: None (2nd-check only; no VAL report produced)

**Acceptance Criteria for VAL 2nd-Check**:
- SRS requirements match System SRS intended use
- All safety requirements (SSRS) traced to SRS
- Operational scenarios identified (normal, degraded, emergency, recovery)
- OTSS includes acceptance test placeholder

### 8.3 Phase 3 — Architecture & Design

**VAL Activities** (2nd-Check Only):
- Review SAS (item 9) for architecture fitness (dual-channel, safe state, fault detection)
- Review SDS (item 10) for design fitness (door state machine, interlock logic)
- Review Software Interface Specifications (item 11) for TCMS/DDU interface correctness
- Review Integration Test Specifications (items 12–13) for hardware integration coverage
- Review Architecture & Design Verification Report (item 14) — VER 1st-check

**VAL Deliverables**: None (2nd-check only)

**Acceptance Criteria for VAL 2nd-Check**:
- Architecture supports operational scenarios (dual-channel, safe state)
- Design supports validation testing (testability, observability)
- Interfaces match System SRS (TCMS commands, door sensors)

### 8.4 Phase 4 — Component Design

**VAL Activities** (2nd-Check Only):
- Review Software Component Design Specification (item 15)
- Review Software Component Test Specification (item 16)
- Confirm component design supports validation scenarios

**VAL Deliverables**: None (2nd-check only)

### 8.5 Phase 5 — Implementation & Testing

**VAL Activities** (2nd-Check Only):
- Review source code (item 18) for readability and maintainability (customer perspective)
- Review Unit Test Report (item 20)
- Confirm code supports validation testing (no unnecessary complexity)

**VAL Deliverables**: None (2nd-check only)

### 8.6 Phase 6 — Integration

**VAL Activities** (2nd-Check Only):
- Review Integration Test Specification (item 21)
- Review Integration Test Report (item 22)
- Confirm integration testing prepares for system validation

**VAL Deliverables**: None (2nd-check only)

### 8.7 Phase 7 — Validation (PRIMARY VAL PHASE)

**VAL Activities** (Author Mode):

#### Phase 7 Track A (TST produces item 24)
- TST authors Overall Software Test Report (item 24)
- QUA performs format-gate on item 24

#### Phase 7 Track B Step B1 (VER reviews item 24)
- VER reviews item 24
- VER authors Software Integration Verification Report (item 23)
- QUA performs format-gate on item 23
- VMGR reviews item 23

#### Phase 7 Track B Step B2 (VAL EXECUTION)

**Trigger**: VMGR assigns VAL after VER item 23 approved

**Activities**:
1. **Functional Validation**:
   - Execute operational scenario tests (normal, degraded, emergency, recovery)
   - Functional/black-box testing (all SRS requirements)
   - Boundary value testing (speed interlock, door timing)
   - Equivalence class testing (door states, sensor states)

2. **Performance Validation** (Mandatory SIL 3):
   - Timing analysis (obstacle response ≤ 150 ms, control cycle = 10 ms)
   - WCET analysis (safety-critical functions)
   - Load testing (maximum simultaneous events)
   - Resource usage (CPU ≤ 80%, memory ≤ 90%, stack ≤ 70%)
   - Reliability testing (72 hours continuous operation)

3. **Safety Validation**:
   - Validate all safety requirements (SSR-001 to SSR-028)
   - Fault injection (sensor failures, communication faults, cross-channel disagreement)
   - Safe state entry and recovery
   - Dual-channel operation (2oo2 architecture)

4. **Software/Hardware Integration Validation**:
   - TCMS interface validation (commands, speed signal, status outputs)
   - DDU interface validation (door actuator commands, position sensors)
   - Obstacle detection validation (infrared sensors)
   - Lock sensor validation

5. **Acceptance Testing**:
   - Customer-witnessed testing of critical scenarios
   - Customer acceptance certificate signed

6. **Validation Reporting**:
   - Author Software Validation Report (item 25)
   - Author Tools Validation Report (item 26) if tool qualification required
   - Author Release Note (item 27) per §7.7.4.12

7. **QUA Format-Gate** (1-Pass Rule):
   - Submit items 25, 26, 27 to QUA
   - QUA performs format-gate (accepts if no Major/Critical findings)

8. **VER Review**:
   - VER authors Software Validation Verification Report (item †)
   - QUA performs format-gate on item †

9. **VMGR Review**:
   - VMGR reviews items 23 + 25(+26) + † together
   - VMGR issues FINAL V&V DECISION to COD

10. **VAL Release Decision**:
    - **VAL issues release decision: AGREE or DISAGREE** (§5.1.2.8)
    - This decision is FINAL and cannot be overridden

**VAL Deliverables**:
- Software Validation Report (item 25) — DOC-TDC-VALRPT-001
- Tools Validation Report (item 26) — DOC-TDC-TOOLSVALRPT-001 (if applicable)
- Release Note (item 27) — DOC-TDC-RELEASENOTE-001

**Validation Test Coverage**:
- All SRS functional requirements traced to at least one validation test case
- All safety requirements (SSR-001 to SSR-028) validated with evidence
- All operational scenarios executed (normal, degraded, emergency, recovery)
- All performance requirements met (timing, throughput, resource usage)

### 8.8 Phase 8 — Assessment

**VAL Activities**: NONE — Phase 8 is ISA-driven; VAL has no touchpoint

**Rationale**: Phase 8 Assessment is performed by Independent Safety Assessor (ISA) who reviews all artifacts including VAL's Validation Report. VAL MUST NOT review or comment on Phase 8 documents to maintain ISA independence.

### 8.9 Phase 9 — Deployment

**VAL Activities** (2nd-Check Only):
- Review Release and Deployment Plan (item 36)
- Review Software User Manual (item 37)
- Review Release Notes (item 38) — distinct from item 27
- Review Deployment Records (item 39)

**VAL Deliverables**: None (2nd-check only)

### 8.10 Phase 10 — Maintenance

**VAL Activities** (2nd-Check Only):
- Review Maintenance Records (item 41)
- Review Change Records (item 42)
- Review Software Maintenance Plan (item 43)

**VAL Deliverables**: None (2nd-check only)

**Re-Validation**: If maintenance change triggers CCB re-entry to Phase 7, VAL SHALL re-execute validation per SVaP Section 8.7.

---

## 9. System Testing vs Acceptance Testing

### 9.1 System Testing

**Objective**: Confirm software functions correctly in target environment (operational scenarios).

**Executor**: VAL team with TST support

**Environment**: Target DCU hardware, TCMS/DDU interfaces, production build

**Method**:
- Black-box testing (external behavior)
- Operational scenarios (normal, degraded, emergency, recovery)
- Performance testing (timing, resource usage)
- Fault injection (sensor failures, communication faults)

**Evidence**: Test execution logs, screenshots, timing measurements, fault logs

**Acceptance Criteria**:
- All test cases executed
- All test cases passed (or failures justified)
- All SRS requirements traced to test cases
- All performance requirements met

### 9.2 Acceptance Testing

**Objective**: Customer confirms software meets intended use and accepts for deployment.

**Executor**: VAL team with **customer representative** witness

**Environment**: Same as system testing (target DCU hardware)

**Method**:
- Customer reviews SRS and confirms requirements match needs
- Customer selects critical scenarios for witnessed testing
- Customer witnesses test execution
- Customer reviews validation test results and open defects
- Customer signs acceptance certificate

**Evidence**:
- Customer acceptance certificate (signed)
- Witnessed test execution logs
- Customer sign-off on SRS
- Customer acceptance of open defects (if any)

**Acceptance Criteria**:
- Customer confirms SRS matches intended use
- Customer witnesses critical tests and confirms pass
- Customer reviews all defects and accepts risk (or requests fixes)
- Customer signs acceptance certificate
- VAL issues release decision (AGREE/DISAGREE)

### 9.3 Customer Involvement

**Customer Representative**: TBD — assigned at project kick-off

**Customer Activities**:
1. **Phase 2**: Review SRS, confirm requirements match intended use, sign off on SRS
2. **Phase 7**: Define acceptance criteria, select critical scenarios for witnessed testing
3. **Phase 7**: Witness execution of critical test cases
4. **Phase 7**: Review validation test results and open defects
5. **Phase 7**: Sign acceptance certificate (or reject if not acceptable)

**Customer Acceptance Criteria**: See Section 9.2 above.

**Customer Sign-Off Required**: Before VAL issues release decision (AGREE).

---

## 10. Performance Validation (SIL 3 Mandatory)

### 10.1 Performance Requirements from System SSRS

| ID | Performance Requirement | Target | Verification Method |
|----|------------------------|--------|---------------------|
| SSR-011 | Obstacle response time | ≤ 150 ms | Timing measurement (oscilloscope) |
| SSR-014 | Obstacle response budget allocation | ≤ 5 ms interrupt + ≤ 20 ms SW + ≤ 125 ms DDU | WCET analysis + timing measurement |
| SSR-009 | Door-locked signal response | ≤ 10 ms | Timing measurement |
| SSR-018 | Safe state entry time | ≤ 10 ms | Timing measurement |
| SSR-021 | Lock sensor polling period | ≤ 50 ms | Code review + timing measurement |
| SYS-FR-012 | Door open/close cycle time | ≤ 8 s | Timing measurement |

### 10.2 Timing Analysis

**Method**: Measure execution time for all time-critical functions using oscilloscope or logic analyzer.

**Test Cases**:

| Test Case | Function | Expected Time | Acceptance Criteria |
|-----------|----------|---------------|---------------------|
| TC-VAL-PERF-001 | Obstacle detection to door reversal | ≤ 150 ms | Measured time ≤ 150 ms |
| TC-VAL-PERF-002 | Control cycle time | 10 ms ± 1 ms | Measured time within tolerance |
| TC-VAL-PERF-003 | Door-locked signal response | ≤ 10 ms | Measured time ≤ 10 ms |
| TC-VAL-PERF-004 | Safe state entry time | ≤ 10 ms | Measured time ≤ 10 ms |
| TC-VAL-PERF-005 | Lock sensor polling period | ≤ 50 ms | Measured period ≤ 50 ms |
| TC-VAL-PERF-006 | Door open/close cycle | ≤ 8 s | Measured time ≤ 8 s |

**Tools**: Oscilloscope, logic analyzer, GPIO toggle markers for timing measurement

**Evidence**: Oscilloscope screenshots, CSV timing data, statistical analysis (min, max, mean, stddev)

### 10.3 WCET Analysis

**Method**: Measure worst-case execution time for safety-critical functions.

**Functions Analyzed**:
- Obstacle detection interrupt handler
- Speed interlock check
- Door-locked signal calculation
- Safe state entry logic
- Cross-channel comparison

**Method**:
- Execute function under maximum load (worst-case input data)
- Measure execution time using RTOS profiler or GPIO toggle
- Repeat 1000 times, record maximum
- Confirm maximum ≤ timing budget

**Acceptance Criteria**: WCET ≤ timing budget with 20% margin

### 10.4 Load Testing

**Method**: Test system under maximum expected load (worst-case scenarios).

**Test Scenarios**:

| Scenario | Load Description | Acceptance Criteria |
|----------|------------------|---------------------|
| All doors closing simultaneously | 8 doors closing, 16 obstacle sensors monitored | No missed deadlines, all doors respond within 8 s |
| All obstacles detected simultaneously | 16 obstacle sensors triggered simultaneously | All doors reverse within 150 ms |
| Maximum TCMS message rate | TCMS sends commands at maximum rate (TBD Hz) | All commands processed, no buffer overflow |
| Simultaneous faults | Multiple sensor failures + cross-channel disagreement | Safe state entered within 10 ms |

**Evidence**: Test execution logs, timing measurements, CPU usage profiling

### 10.5 Resource Usage Analysis

**Method**: Measure CPU usage, memory usage, stack depth under normal and maximum load.

**Resource Limits**:

| Resource | Limit | Acceptance Criteria |
|----------|-------|---------------------|
| CPU usage | ≤ 80% of maximum | Measured usage ≤ 80% under maximum load |
| RAM usage | ≤ 90% of available | Measured usage ≤ 90% under maximum load |
| Stack usage | ≤ 70% of allocated | Measured max stack depth ≤ 70% of stack size |

**Tools**: RTOS profiler (if applicable), memory dump analysis, stack watermarking

**Evidence**: CPU usage graphs, memory usage reports, stack depth analysis

### 10.6 Reliability Testing

**Method**: Long-duration continuous operation testing.

**Test Configuration**:
- Duration: **72 hours minimum** (SIL 3 recommendation)
- Scenario: Cyclic door open/close operations (station stop simulation every 2 minutes)
- Monitoring: CPU usage, memory usage, fault counts, diagnostic logs

**Acceptance Criteria**:
- No crashes or hangs over 72 hours
- No memory leaks (memory usage stable)
- No performance degradation (timing remains within limits)
- No unexpected faults or safe state entries

**Evidence**: 72-hour test log, CPU/memory usage graphs, fault log analysis

---

## 11. Safety Requirements Validation

### 11.1 Safety Requirements Traceability

**Objective**: Validate all safety requirements (SSRS) with evidence.

**Method**: Trace each safety requirement (SSR-001 to SSR-028) to validation test case(s).

**Traceability Matrix** (excerpt):

| SSRS ID | Safety Requirement | Validation Test Case(s) | Test Result |
|---------|-------------------|------------------------|-------------|
| SSR-001 | Inhibit door open when speed > 5 km/h | TC-VAL-SAFE-001 (boundary value: 4, 5, 6 km/h) | TBD Phase 7 |
| SSR-002 | Safe default if speed signal invalid | TC-VAL-SAFE-002 (speed signal timeout) | TBD Phase 7 |
| SSR-003 | Both channels enforce speed interlock | TC-VAL-SAFE-003 (single-channel fault) | TBD Phase 7 |
| SSR-005 | Door-locked signal requires ALL doors locked | TC-VAL-SAFE-005 (one door unlocked) | TBD Phase 7 |
| SSR-011 | Obstacle response ≤ 150 ms | TC-VAL-PERF-001 + TC-VAL-SAFE-011 | TBD Phase 7 |
| SSR-015 | Safe state entry on fault detection | TC-VAL-SAFE-015 (fault injection: cross-channel disagreement, watchdog, CRC, sensor range, stack overflow) | TBD Phase 7 |
| SSR-016 | Safe state action | TC-VAL-SAFE-016 (verify motors de-energized, locks energized, signals de-asserted, fault log written) | TBD Phase 7 |

**Coverage**: 100% of SSRS safety requirements (SSR-001 to SSR-028) traced to validation test cases.

**Evidence**: Traceability matrix (SSRS → validation tests) with test results.

### 11.2 Hazard Validation

**Objective**: Confirm all identified hazards (HAZ-001 to HAZ-009) are mitigated by TDC software.

**Method**: Trace each hazard to safety requirements (SSRS) to validation test cases.

**Hazard-to-Validation Traceability** (excerpt):

| Hazard ID | Hazard Description | SSRS | Validation Test Case(s) |
|-----------|-------------------|------|------------------------|
| HAZ-001 | Train departs with door open or not fully locked | SSR-005, SSR-006, SSR-007, SSR-008, SSR-009 | TC-VAL-SAFE-005 to TC-VAL-SAFE-009 |
| HAZ-002 | Door closes on passenger causing entrapment injury | SSR-010, SSR-011, SSR-012, SSR-013, SSR-014 | TC-VAL-SAFE-010 to TC-VAL-SAFE-014 |
| HAZ-003 | Door opens while train is moving above 5 km/h | SSR-001, SSR-002, SSR-003, SSR-004 | TC-VAL-SAFE-001 to TC-VAL-SAFE-004 |
| HAZ-005 | False door-locked signal allows departure with door ajar | SSR-005, SSR-006, SSR-007, SSR-009, SSR-019, SSR-020 | TC-VAL-SAFE-005 to TC-VAL-SAFE-009, TC-VAL-SAFE-019 to TC-VAL-SAFE-020 |
| HAZ-009 | DCU software fault — loss of all door control | SSR-015, SSR-016, SSR-017, SSR-018 | TC-VAL-SAFE-015 to TC-VAL-SAFE-018 |

**Coverage**: All SIL 3 hazards (HAZ-001 to HAZ-005) validated with evidence.

**Evidence**: Hazard Log with validation test results cross-referenced.

### 11.3 Fault Injection Testing

**Objective**: Validate safe state entry and fault detection mechanisms.

**Method**: Inject faults and confirm system enters safe state correctly.

**Fault Injection Test Cases**:

| Test Case | Fault Injected | Expected Behavior | Validation Criteria |
|-----------|---------------|-------------------|---------------------|
| TC-VAL-SAFE-015a | Cross-channel disagreement (> 2 cycles) | Safe state entry within 10 ms | Safe state entered, fault logged |
| TC-VAL-SAFE-015b | Watchdog timeout | Safe state entry within 10 ms | Safe state entered, fault logged |
| TC-VAL-SAFE-015c | CRC error in safety-critical data | Safe state entry within 10 ms | Safe state entered, fault logged |
| TC-VAL-SAFE-015d | Sensor input out of valid range | Safe state entry within 10 ms | Safe state entered, fault logged |
| TC-VAL-SAFE-015e | Stack overflow detection | Safe state entry within 10 ms | Safe state entered, fault logged |
| TC-VAL-SAFE-002 | Speed signal timeout (> 200 ms) | Treat speed as > 5 km/h (safe default) | Doors inhibited, no fault |
| TC-VAL-SAFE-012 | Obstacle sensor fault | Treat as obstacle present (fail-safe) | Door reversal within 150 ms |

**Tools**: Fault injection harness (hardware or software), logic analyzer for timing measurement

**Evidence**: Fault injection test logs, timing measurements, fault log analysis

---

## 12. Software/Hardware Integration Validation

### 12.1 TCMS Interface Validation

**Objective**: Validate TDC software correctly interfaces with TCMS.

**Interfaces Validated**:

| Interface | Direction | Validation Method |
|-----------|-----------|-------------------|
| Door open command (left/right) | TCMS → DCU | Functional test: door opens when commanded |
| Door close command (left/right) | TCMS → DCU | Functional test: door closes when commanded |
| Train speed signal | TCMS → DCU | Boundary value test: 0, 4, 5, 6, 200 km/h |
| Door-locked signal | DCU → TCMS | Functional test: signal asserted only when all doors locked |
| Door fault signal | DCU → TCMS | Fault injection test: signal asserted on fault |
| Door status (open/closed) | DCU → TCMS | Functional test: status reflects actual door position |

**Test Cases**: TC-VAL-INT-TCMS-001 to TC-VAL-INT-TCMS-010

**Evidence**: Interface test logs, oscilloscope screenshots (signal timing and levels)

### 12.2 DDU Interface Validation

**Objective**: Validate TDC software correctly controls Door Drive Units (DDU).

**Interfaces Validated**:

| Interface | Direction | Validation Method |
|-----------|-----------|-------------------|
| Door motor command (open/close/stop) | DCU → DDU | Functional test: door moves as commanded |
| Door position feedback | DDU → DCU | Functional test: position feedback matches actual door position |
| Lock solenoid command (lock/unlock) | DCU → DDU | Functional test: lock engages/disengages as commanded |
| Lock sensor feedback | DDU → DCU | Functional test: lock sensor reflects actual lock position |

**Test Cases**: TC-VAL-INT-DDU-001 to TC-VAL-INT-DDU-010

**Evidence**: Interface test logs, door motion video, lock position verification

### 12.3 Obstacle Detection Sensor Validation

**Objective**: Validate TDC software correctly processes obstacle detection sensors.

**Sensors Validated**:
- Infrared beam sensors (2 per door opening)
- Sensor fault detection (no signal, out-of-range, both beams broken)

**Test Cases**:

| Test Case | Scenario | Expected Behavior |
|-----------|----------|-------------------|
| TC-VAL-INT-OBS-001 | Obstacle breaks beam during closing | Door reverses within 150 ms |
| TC-VAL-INT-OBS-002 | Obstacle clears after reversal | Door remains open until re-close command |
| TC-VAL-INT-OBS-003 | Sensor fault (no signal) | Treated as obstacle present (fail-safe) |
| TC-VAL-INT-OBS-004 | Both beams broken simultaneously | Treated as sensor fault (fail-safe) |

**Evidence**: Timing measurements (obstacle response time), sensor state logs

### 12.4 Dual-Channel (2oo2) Architecture Validation

**Objective**: Validate dual-channel architecture operates correctly (both channels agree, faults detected).

**Test Cases**:

| Test Case | Scenario | Expected Behavior |
|-----------|----------|-------------------|
| TC-VAL-INT-DUAL-001 | Normal operation (both channels agree) | System operates normally |
| TC-VAL-INT-DUAL-002 | Single-channel fault (cross-channel disagreement) | Safe state entered within 10 ms (2 cycles) |
| TC-VAL-INT-DUAL-003 | Both channels detect same fault | Safe state entered within 10 ms |
| TC-VAL-INT-DUAL-004 | One channel receives valid speed, other invalid | Speed interlock enforced (SSR-003) |

**Evidence**: Dual-channel test logs, cross-channel comparison logs, timing measurements

---

## 13. Traceability Requirements

### 13.1 Requirements-to-Validation Traceability

**Objective**: Confirm all requirements are validated (no orphaned requirements).

**Method**: Maintain traceability matrix from System SRS → Software SRS → Validation Test Cases.

**Traceability Levels**:

1. **System SRS → Software SRS**: Traced in SRS (Phase 2)
2. **Software SRS → Validation Test Cases**: Traced in Validation Test Specification (Phase 7)

**Coverage Target**: 100% of SRS requirements traced to at least one validation test case.

**Traceability Matrix Format**:

| SRS ID | SRS Requirement | Validation Test Case(s) | Test Result | Status |
|--------|----------------|------------------------|-------------|--------|
| SW-REQ-001 | Open door when commanded and speed ≤ 5 km/h | TC-VAL-FUNC-001 | TBD Phase 7 | Pending |
| SW-REQ-002 | Close door when commanded | TC-VAL-FUNC-002 | TBD Phase 7 | Pending |
| ... | ... | ... | ... | ... |

**Traceability Verification**: VAL SHALL verify 100% traceability completeness before issuing release decision.

**Tool Support**: Use `python3 tools/workspace.py trace validate --phase validation --sil 3` to verify traceability completeness.

### 13.2 Hazard-to-Validation Traceability

**Objective**: Confirm all hazards are mitigated and validated.

**Method**: Trace System Hazards → SSRS → SRS → Validation Test Cases.

**Traceability Chain**:

```
System Hazard (HAZ-001)
  ↓ mitigated by
System Safety Requirement (SSRS: SSR-005 to SSR-009)
  ↓ decomposed into
Software Requirement (SRS: SW-REQ-010 to SW-REQ-015)
  ↓ validated by
Validation Test Case (TC-VAL-SAFE-005 to TC-VAL-SAFE-009)
```

**Coverage Target**: 100% of SIL 3 hazards (HAZ-001 to HAZ-005) traced to validation test cases.

**Evidence**: Hazard Log with validation test results cross-referenced.

### 13.3 Validation Test Coverage Analysis

**Objective**: Confirm validation test suite provides adequate coverage of requirements and hazards.

**Coverage Metrics**:

| Metric | Target | Verification Method |
|--------|--------|---------------------|
| SRS requirements coverage | 100% | Traceability matrix (SRS → test cases) |
| SSRS safety requirements coverage | 100% | Traceability matrix (SSRS → test cases) |
| Hazard coverage | 100% (SIL 3 hazards) | Traceability matrix (Hazards → test cases) |
| Operational scenario coverage | 100% (normal, degraded, emergency, recovery) | Scenario matrix |

**Gap Analysis**: If any requirement has zero validation test cases, VAL SHALL create test cases to close the gap.

---

## 14. Validation Tools and Test Automation

### 14.1 Validation Tools

| Tool | Purpose | Qualification Required | Status |
|------|---------|------------------------|--------|
| **Unity** | Unit/integration test framework (background) | No (not used for validation evidence) | Available |
| **Oscilloscope** | Timing measurements (obstacle response, cycle time) | No (Class T1 per SVP) | TBD — acquire |
| **Logic Analyzer** | Signal analysis (TCMS/DDU interface timing) | No (Class T1 per SVP) | TBD — acquire |
| **RTOS Profiler** | CPU/memory usage measurement | No (Class T1 per SVP) | TBD — if RTOS used |
| **Environmental Chamber** | Temperature testing (-25°C to +55°C) | No (Class T1 per SVP) | TBD — optional |
| **HIL Simulator** | Hardware-in-the-loop simulation (TCMS/DDU) | **Yes (Class T2 if used for validation evidence)** | TBD — if used |
| **Test Automation Framework** | Automated test execution and logging | No (Class T1 per SVP) | TBD — develop |

**Tool Qualification**:
- **Class T1**: No qualification required (offline tools, measurement tools)
- **Class T2**: Qualification required if tool output used as validation evidence
- **Class T3**: Full qualification required (not applicable for validation tools)

**Tools Validation Report (item 26)**: Required if any Class T2 or T3 tools used for validation evidence.

### 14.2 Test Automation

**Objective**: Automate validation test execution and result logging to improve repeatability and reduce manual effort.

**Automation Framework**:
- Test control PC (Python or C++)
- TCMS/DDU interface control (send commands, read status)
- Automated result logging (CSV, JSON)
- Automated pass/fail criteria evaluation

**Automated Test Cases**:
- Functional tests (door open/close sequences)
- Boundary value tests (speed interlock)
- Regression tests (re-execute after code changes)

**Manual Test Cases** (cannot be automated):
- Customer acceptance tests (require customer witness)
- Environmental tests (temperature, vibration — require manual setup)
- Visual inspection (door motion, lock engagement)

**Automation Coverage Target**: ≥ 70% of validation test cases automated (to enable efficient regression testing).

### 14.3 Test Data Management

**Test Data Location**: `examples/TDC/validation/test-data/`

**Test Data Types**:
- Input data (TCMS commands, speed signals, sensor states)
- Expected output data (door status, TCMS status signals, fault logs)
- Actual output data (test execution results)
- Timing data (oscilloscope CSV exports)

**Test Data Version Control**: All test data under CM control (SCMP Section 4.2).

---

## 15. Validation Deliverables

### 15.1 Phase 1 Deliverables

| Item | Deliverable | Annex C Item | Author | 1st Check | 2nd Check | Status |
|------|------------|--------------|--------|-----------|-----------|--------|
| 1 | Software Validation Plan (SVaP) | 5 | VAL | VER | — | This document (DRAFT) |

### 15.2 Phase 7 Deliverables

| Item | Deliverable | Annex C Item | Author | 1st Check | 2nd Check | Status |
|------|------------|--------------|--------|-----------|-----------|--------|
| 1 | Software Validation Report | 25 | VAL | — | QUA (format-gate) | TBD Phase 7 |
| 2 | Tools Validation Report | 26 | VAL | — | QUA (format-gate) | TBD Phase 7 (if applicable) |
| 3 | Release Note | 27 | VAL | — | QUA (format-gate) | TBD Phase 7 |

**Note**: After QUA format-gate, VER authors Software Validation Verification Report (item †), then VMGR reviews items 23 + 25(+26) + † together and issues FINAL V&V DECISION to COD.

### 15.3 Validation Evidence

| Evidence Type | Location | CM Control |
|--------------|----------|------------|
| Validation Test Specification | `examples/TDC/validation/test-spec/` | Baseline (SCMP) |
| Validation Test Results | `examples/TDC/validation/test-results/` | Baseline (SCMP) |
| Timing Measurements | `examples/TDC/validation/timing/` | Baseline (SCMP) |
| Performance Data | `examples/TDC/validation/performance/` | Baseline (SCMP) |
| Fault Injection Logs | `examples/TDC/validation/fault-injection/` | Baseline (SCMP) |
| Customer Acceptance Certificate | `examples/TDC/validation/acceptance/` | Baseline (SCMP) |
| Traceability Matrix (SRS → tests) | `examples/TDC/validation/traceability/` | Baseline (SCMP) |

**Evidence Retention**: All validation evidence SHALL be retained per project records retention policy (minimum 10 years for SIL 3).

---

## 16. Roles and Responsibilities

### 16.1 Software Validator (VAL)

**Responsibilities**:
- Author and maintain Software Validation Plan (this document)
- Define operational validation scenarios (normal, degraded, emergency, recovery)
- Coordinate acceptance testing with customer representative
- Execute validation testing in target environment (DCU hardware)
- Perform 2nd-check on deliverables in Phases 1–6, 9–10
- Analyze validation test results and generate Validation Report (item 25)
- Generate Tools Validation Report (item 26) if tool qualification required
- Author Release Note (item 27)
- **Issue release decision: AGREE or DISAGREE** (§5.1.2.8)
- Report to Safety Authority or VMGR (SIL 3), NOT to Project Manager

**Authority**:
- Final release decision authority (AGREE/DISAGREE per §5.1.2.8)
- Cannot be overridden by PM, COD, or VMGR

**Independence** (SIL 3 Mandatory):
- SHALL NOT report to Project Manager (§5.1.2.10f)
- SHALL NOT have been involved in requirements, design, implementation, integration, or verification

### 16.2 Customer Representative

**Responsibilities**:
- Define acceptance criteria
- Review SRS and confirm requirements match intended use
- Select critical scenarios for witnessed testing
- Witness execution of critical test cases
- Review validation test results and open defects
- Sign acceptance certificate (or reject if not acceptable)

**Authority**: Final customer acceptance decision

### 16.3 VMGR (V&V Manager)

**Responsibilities**:
- Coordinate VER and VAL activities in Phase 7
- Review VAL reports (items 25, 26, 27)
- Issue FINAL V&V DECISION to COD after reviewing items 23 + 25(+26) + †

**Authority**: FINAL V&V DECISION (coordinates VAL's release decision with VER's verification results)

**Independence** (SIL 3 Mandatory): VMGR is independent from PM and development team

### 16.4 Safety Manager (SAF)

**Responsibilities**:
- Review safety validation scenarios
- Approve safety-critical test results
- Confirm hazard coverage (Hazard Log)
- Review VAL reports for safety adequacy

### 16.5 Quality Assurance (QUA)

**Responsibilities**:
- Perform format-gate on VAL deliverables (1-Pass Rule)
- Oversee validation process compliance with SVaP
- Audit validation evidence completeness

### 16.6 Software Verifier (VER)

**Responsibilities**:
- Perform 1st-check on SVaP (item 5) in Phase 1
- Author Software Validation Verification Report (item †) in Phase 7 Track B Step B2
- Coordinate with VAL to clarify verification vs validation boundary

**Independence** (SIL 3 Mandatory): VER is independent from development team

---

## 17. Review and Approval Process

### 17.1 SVaP Review and Approval (Phase 1)

**Review Chain** (EN 50128 Annex C Table C.1, Item 5):

```
1. VAL authors SVaP (this document)
   ↓
2. VER performs 1st-check (mandatory per deliverables.yaml)
   - Check: Validation strategy appropriate for SIL 3
   - Check: Validation techniques per Table A.7 applied
   - Check: Independence requirements addressed
   - Check: Validation vs verification boundary clear
   ↓
3. No 2nd-check (SVaP has no 2nd-check per Annex C Table C.1)
   ↓
4. VMGR approval (SIL 3)
   - Approve or request revisions
   ↓
5. SVaP baselined by CM
```

**Acceptance Criteria for VER 1st-Check**:
- Validation strategy appropriate for SIL 3 (Table A.7 mandatory techniques applied)
- Independence requirements addressed (VAL does not report to PM)
- Validation vs verification boundary clear
- Operational scenarios defined (normal, degraded, emergency, recovery)
- Performance testing plan defined (mandatory SIL 3)
- Traceability requirements defined
- Acceptance testing approach defined

### 17.2 Phase 7 VAL Deliverables Review and Approval

**Review Chain** (items 25, 26, 27):

```
1. VAL authors items 25, 26 (if applicable), 27
   ↓
2. QUA performs format-gate (1-Pass Rule)
   - Accept if no Major/Critical findings
   - Reject if Major/Critical findings present
   ↓
3. VER authors Software Validation Verification Report (item †)
   - 1st-check on validation evidence
   ↓
4. QUA performs format-gate on item †
   ↓
5. VMGR reviews items 23 + 25(+26) + † together
   - Issue FINAL V&V DECISION to COD
   ↓
6. VAL issues release decision: AGREE or DISAGREE (§5.1.2.8)
   - This decision is FINAL and cannot be overridden
```

**1-Pass Rule**: QUA format-gate accepts VAL reports if no Major/Critical findings. Minor findings can be addressed after acceptance.

**Release Decision Criteria** (see Section 18.2):
- All validation test cases passed
- All performance requirements met
- All safety requirements validated
- Zero unresolved critical/high-severity defects
- Customer acceptance certificate signed
- VMGR FINAL V&V DECISION issued

---

## 18. Validation Schedule

### 18.1 Validation Milestones

| Milestone | Phase | Planned Date | Validation Activities | Deliverable |
|-----------|-------|--------------|------------------------|-------------|
| **SVaP Authoring** | 1 | 2026-03-30 | VAL authors SVaP | This document |
| **SVaP 1st-Check** | 1 | TBD | VER performs 1st-check on SVaP | VER sign-off |
| **SVaP Approval** | 1 | TBD | VMGR approves SVaP | VMGR sign-off |
| **Requirements Validation** | 2 | TBD | VAL 2nd-check on SRS, OTSS | 2nd-check sign-off |
| **Validation Test Planning** | 7 | TBD | Define validation test scenarios, develop test spec | Validation Test Specification |
| **Validation Environment Setup** | 7 | TBD | Configure target DCU hardware, interfaces | Test readiness report |
| **Functional Validation** | 7 | TBD | Execute operational scenario tests | Test execution logs |
| **Performance Validation** | 7 | TBD | Execute performance tests (timing, resource usage, 72h) | Performance test results |
| **Safety Validation** | 7 | TBD | Fault injection, safe state testing | Safety test results |
| **Acceptance Testing** | 7 | TBD | Customer-witnessed testing | Customer acceptance certificate |
| **Validation Report** | 7 | TBD | VAL authors items 25, 26, 27 | DOC-TDC-VALRPT-001, etc. |
| **Release Decision** | 7 | TBD | VAL issues AGREE/DISAGREE decision | Release decision memo |

### 18.2 Validation Effort Estimate

| Activity | Effort (person-hours) | Notes |
|----------|-----------------------|-------|
| SVaP authoring | 24 hours | This document |
| Requirements validation (Phase 2) | 16 hours | SRS 2nd-check |
| Validation test planning | 40 hours | Test specification development |
| Validation environment setup | 40 hours | DCU hardware, TCMS/DDU interfaces, HIL setup |
| Functional validation | 80 hours | Operational scenarios, black-box testing |
| Performance validation | 80 hours | Timing, WCET, load, resource, 72-hour reliability |
| Safety validation | 40 hours | Fault injection, safe state, dual-channel |
| SW/HW integration validation | 40 hours | TCMS/DDU interfaces, sensors |
| Acceptance testing | 24 hours | Customer-witnessed tests |
| Validation reporting | 40 hours | Items 25, 26, 27 |
| 2nd-check activities (Phases 1–6, 9–10) | 80 hours | 2nd-check on all deliverables |
| **Total** | **504 hours** | ~63 person-days (~3 person-months) |

**SIL 3 Factor**: Includes 30% additional effort for independence activities, VMGR coordination, and additional safety/performance testing.

---

## 19. Risk Management

### 19.1 Validation Risks

| Risk | Probability | Impact | Mitigation |
|------|-------------|--------|------------|
| **Target hardware (DCU) unavailable** | Medium | High | Order DCU hardware early (Phase 2), use HIL simulator as backup (with limitations) |
| **Customer representative unavailable for acceptance testing** | Medium | High | Schedule acceptance tests early (Phase 6), confirm customer availability, escalate to Safety Authority if needed |
| **Performance requirements not met** | Medium | Critical | Monitor performance early (Phase 4 architectural analysis), allocate time for optimization in Phase 5, involve DES/IMP in performance tuning |
| **VAL independence compromised** (SIL 3) | Low | Critical | Enforce organizational independence, separate reporting to VMGR (not PM), VMGR verifies independence before Phase 7 |
| **Environmental test chamber unavailable** | Medium | Medium | Partner with external test lab, prioritize room-temperature testing, defer extreme temperature testing if necessary (with risk acceptance) |
| **Obstacle response timing not met** (≤ 150 ms) | Low | Critical | Early timing analysis in Phase 4 (design review), optimize interrupt latency and DDU response, validate with oscilloscope in Phase 7 |
| **Dual-channel disagreement not detected** | Low | Critical | Independent VER review of dual-channel logic (Phase 5), fault injection testing in Phase 7 |
| **Traceability gaps** (orphaned requirements) | Low | High | Use `workspace.py trace validate` tool in Phase 7, VAL reviews traceability before issuing release decision |

### 19.2 Risk Monitoring

**Risk Review Frequency**: Monthly project meetings (or per validation milestone)

**Risk Owner**: Software Validator (VAL)

**Escalation**: Critical risks escalated to VMGR and Safety Authority

**Risk Log**: Maintained in project risk register (SQAP Section 14)

---

## 20. EN 50128 Compliance Matrix

### 20.1 EN 50128 Section 7.7 Compliance

| Requirement | EN 50128 Section | SVaP Section | Evidence | Status |
|-------------|------------------|--------------|----------|--------|
| **Validation plan established** | §7.7.2 | This document (all sections) | This SVaP | ✓ |
| **Validation independence (SIL 3-4)** | §7.7.3, §5.1.2.10f | Section 4.2, 16.1 | VAL reports to VMGR, not PM | ✓ |
| **Validation in target environment** | §7.7.4.3 | Section 7, 8.7 | DCU hardware, production build | ✓ |
| **Operational scenarios** | §7.7.4.5 | Section 8.3, 8.7 | Normal, degraded, emergency, recovery | ✓ |
| **Performance testing (SIL 3-4)** | Table A.7 #1 | Section 10 | Timing, WCET, load, resource, 72h | ✓ |
| **Functional/black-box testing (SIL 3-4)** | Table A.7 #2 | Section 6.4.1, 8.7 | System test suite | ✓ |
| **Acceptance testing** | §7.7.4.6 | Section 9.2, 8.7 | Customer-witnessed tests, acceptance certificate | ✓ |
| **Validation report** | §7.7.4.6–7.7.4.11 | Section 15.2 | Item 25 (Software Validation Report) | TBD Phase 7 |
| **Release note** | §7.7.4.12 | Section 15.2 | Item 27 (Release Note) | TBD Phase 7 |
| **VAL release decision authority** | §5.1.2.8 | Section 1.1, 8.7, 16.1 | AGREE/DISAGREE decision | TBD Phase 7 |

### 20.2 EN 50128 Table A.7 Compliance (Validation Techniques)

| # | Technique | SIL 0 | SIL 1-2 | **SIL 3-4** | TDC SIL 3 | SVaP Section |
|---|-----------|-------|---------|-------------|-----------|--------------|
| **1** | Performance Testing | - | HR | **M** | **Applied** | Section 10 |
| **2** | Functional and Black-Box Testing | HR | HR | **M** | **Applied** | Section 6.4.1, 8.7 |
| **3** | Modelling | - | R | R | NOT USED (risk-based decision) | Section 6.3 |
| **4** | Regression Testing | HR | HR | **M** | **Applied** | Section 6.4.3 |
| **5** | User Interface Testing | HR | HR | HR | **Applied** | Section 6.4.5 |
| **6** | Boundary Value Analysis | R | HR | **M** | **Applied** | Section 6.4.4 |
| **7** | Equivalence Classes | R | HR | HR | **Applied** | Section 6.4.5 |

**SIL 3 Mandatory Techniques (M)**: All applied ✓  
**SIL 3 Highly Recommended Techniques (HR)**: All applied ✓  
**SIL 3 Recommended Techniques (R)**: Modelling NOT USED (risk-based decision documented in Section 6.3)

---

## APPENDICES

### Appendix A: Validation Test Case Template

See `deliverables/validation/Software-Validation-Report-template.md` Appendix A.

### Appendix B: Validation Report Template

See `deliverables/validation/Software-Validation-Report-template.md`.

### Appendix C: Customer Acceptance Certificate Template

See `deliverables/validation/Software-Validation-Report-template.md` Appendix C.

### Appendix D: Operational Scenarios (TDC-Specific)

**Scenario 1: Normal Operation — Station Stop**

**Description**: Train arrives at station, doors open, passengers board/alight, doors close and lock, train departs.

**Preconditions**:
- Train speed ≤ 5 km/h
- TCMS sends door open command (left side)

**Test Steps**:
1. TCMS sends door open command (left side)
2. DCU opens all left-side doors
3. Passengers board (simulated: wait 30 seconds)
4. TCMS sends door close command (left side)
5. DCU closes all left-side doors
6. DCU asserts door-locked signal to TCMS
7. TCMS sends traction enable (train departs)

**Expected Results**:
- All left-side doors open within 2 seconds
- Doors remain open until close command
- All left-side doors close and lock within 8 seconds
- Door-locked signal asserted to TCMS after all doors locked
- Train can depart (door-locked signal present)

**Validation Criteria**:
- All timing requirements met (open ≤ 2 s, close ≤ 8 s)
- Door-locked signal asserted correctly
- Zero faults logged

---

**Scenario 2: Degraded Operation — Obstacle Detection**

**Description**: Passenger obstructs door during closing, door reverses, passenger clears, door closes successfully.

**Preconditions**:
- Train at station, doors closing
- Obstacle sensor infrared beam available

**Test Steps**:
1. Doors begin closing
2. Simulate obstacle by breaking infrared beam (at 50% closed position)
3. Observe door reversal
4. Clear obstacle (restore infrared beam)
5. TCMS sends re-close command
6. Doors resume closing

**Expected Results**:
- Door reverses within 150 ms of beam break
- Door remains open after reversal (does not auto-close)
- Door closes successfully after re-close command
- No fault logged (normal obstacle detection)

**Validation Criteria**:
- Obstacle response time ≤ 150 ms (measured with oscilloscope)
- Door does not continue closing after obstacle detected
- Door closes successfully after obstacle cleared and re-close commanded

---

**Scenario 3: Emergency Operation — Safe State Entry**

**Description**: Cross-channel disagreement detected, system enters safe state.

**Preconditions**:
- Dual-channel DCU operational
- Fault injection capability available

**Test Steps**:
1. System operating normally
2. Inject cross-channel disagreement (e.g., one channel reads door locked, other reads unlocked)
3. Maintain disagreement for > 2 consecutive control cycles (> 20 ms)
4. Observe safe state entry

**Expected Results**:
- Safe state entered within 10 ms (1 control cycle) after disagreement detected for > 2 cycles
- All door motors de-energized
- All lock solenoids energized (locked position)
- Door-locked signal de-asserted to TCMS
- Door fault signal asserted to TCMS
- Fault code written to non-volatile log

**Validation Criteria**:
- Safe state entry time ≤ 10 ms (measured with oscilloscope)
- All safe state actions executed correctly
- Fault logged correctly (cross-channel disagreement)
- System does not exit safe state autonomously (requires operator reset)

---

**Scenario 4: Recovery Operation — System Restart After Fault**

**Description**: After safe state entry, operator resets system, system resumes normal operation.

**Preconditions**:
- System in safe state (after fault injection)
- TCMS connected

**Test Steps**:
1. System in safe state
2. TCMS sends reset command (with confirmation sequence)
3. Observe system restart
4. TCMS sends door open command
5. Observe door operation

**Expected Results**:
- System accepts reset command
- System exits safe state
- Doors respond to open command correctly
- Fault log retained (not cleared by reset)

**Validation Criteria**:
- Reset sequence requires confirmation (not accidental reset)
- System resumes normal operation after reset
- Previous fault logged and retrievable

---

### Appendix E: Acronyms and Abbreviations

See Section 1.4.

---

## DOCUMENT HISTORY

This document is maintained under configuration control per SCMP. All changes SHALL be approved by the Change Control Board (CCB).

**Current Version**: 1.0 DRAFT  
**Last Updated**: 2026-03-30  
**Next Review**: After Phase 7 validation activities (or per CCB change request)

---

**END OF DOCUMENT**
