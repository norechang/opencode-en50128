# Software Verification Plan (SVP)

## Document Control

| Field | Value |
|-------|-------|
| **Document ID** | DOC-TDC-SVP-001 |
| **Version** | 1.0 |
| **Date** | 2026-03-30 |
| **Status** | DRAFT |
| **Author** | Software Verifier (VER) |
| **Project** | TDC (Train Door Control) |
| **SIL Level** | SIL 3 |
| **Standard** | EN 50128:2011 Section 6.2 — Software Verification |

---

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Software Verifier (Author) | TBD — assigned at project kick-off | | |
| Independent Validator (2nd Check) | TBD — assigned at project kick-off | | |
| VMGR (Approval Authority) | TBD — assigned at project kick-off | | |

**Note**: Per EN 50128:2011 Annex C Table C.1, the Software Verification Plan (item 4) is **written by VER** with **no 1st check** (VER cannot self-check) and **2nd-checked by VAL**. For SIL 3, VER reports to VMGR (independent V&V authority), not PM.

---

## Revision History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-03-30 | VER Team | Initial SVP for TDC project (SIL 3) |

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [References](#2-references)
3. [Definitions and Abbreviations](#3-definitions-and-abbreviations)
4. [Verification Organization](#4-verification-organization)
5. [Verification Strategy](#5-verification-strategy)
6. [Verification Techniques (EN 50128 Table A.5)](#6-verification-techniques-en-50128-table-a5)
7. [Static Analysis Requirements (EN 50128 Table A.19)](#7-static-analysis-requirements-en-50128-table-a19)
8. [Test Coverage Requirements (EN 50128 Table A.21)](#8-test-coverage-requirements-en-50128-table-a21)
9. [MISRA C:2012 Verification](#9-misra-c2012-verification)
10. [Traceability Verification](#10-traceability-verification)
11. [Verification Activities by Phase](#11-verification-activities-by-phase)
12. [Verification Tools](#12-verification-tools)
13. [Verification Evidence Management](#13-verification-evidence-management)
14. [Verification Acceptance Criteria](#14-verification-acceptance-criteria)
15. [Verification Schedule](#15-verification-schedule)
16. [Risk Management](#16-risk-management)
17. [EN 50128 Compliance Matrix](#17-en-50128-compliance-matrix)

---

## 1. Introduction

### 1.1 Purpose

This Software Verification Plan (SVP) defines the verification strategy, activities, techniques, and acceptance criteria for the **TDC (Train Door Control)** software development project. Verification ensures that software outputs of each lifecycle phase correctly implement the specifications and requirements in accordance with **EN 50128:2011 Section 6.2**.

**Verification Definition** (EN 50128:2011 §3.1.60): Confirmation by examination and provision of objective evidence that specified requirements have been fulfilled.

The SVP establishes:
- Verification organization structure and independence requirements (SIL 3 mandatory)
- Verification techniques per EN 50128 Table A.5 (mandatory and highly recommended)
- Static analysis requirements per EN 50128 Table A.19
- Test coverage requirements per EN 50128 Table A.21
- MISRA C:2012 compliance verification approach
- Traceability verification requirements (mandatory SIL 3)
- Verification activities mapped to lifecycle phases (2-9)
- Verification evidence management and retention
- Verification tools and qualification status

### 1.2 Scope

This SVP applies to **all software lifecycle phases (Phases 2–9)** of the TDC software development project:

| Phase | Name | Verification Scope |
|-------|------|-------------------|
| Phase 1 | Planning | SVP itself (no VER report; VAL performs 2nd-check on SVP) |
| Phase 2 | Requirements | SRS, Overall Test Spec, Hazard Log, traceability |
| Phase 3 | Architecture & Design | SAS, SDS, SIS, integration test specifications |
| Phase 4 | Component Design | Component design & test specifications |
| Phase 5 | Implementation & Testing | C source code (MISRA C:2012), unit tests, coverage |
| Phase 6 | Integration | SW integration, SW/HW integration testing |
| Phase 7 | Validation | Integration evidence (Step B1), Validation evidence (Step B2) |
| Phase 8 | Assessment | 1st-check on items 45-46 only (no VER report) |
| Phase 9 | Deployment | Release package, deployment records, deployment verification |

**Out of Scope**:
- System validation (covered by Software Validation Plan)
- Hardware verification (covered by System Safety Plan)
- Phase 10 (Maintenance) verification (covered by Software Maintenance Plan)

### 1.3 SIL Classification

**Target SIL Level**: **SIL 3**

**EN 50128 Verification Requirements** (Table A.5):

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | TDC Implementation |
|-----------|-------|---------|---------|-------------------|
| Static Analysis (Table A.19) | - | HR | **M** | PC-lint Plus, Cppcheck, Clang Static Analyzer |
| Dynamic Analysis and Testing (Table A.13) | - | HR | **M** | Unity unit tests, integration tests |
| Traceability (D.58) | R | HR | **M** | Requirements Traceability Matrix (RTM) |
| Test Coverage for Code (Table A.21) | R | HR | **M** | gcov/lcov (statement, branch, condition) |
| Functional and Black-box Testing (Table A.14) | HR | HR | **M** | Unity tests, system tests |
| Metrics (D.37) | - | R | HR | Complexity (Lizard), coverage metrics, defect density |
| Software Error Effect Analysis (D.25) | - | R | HR | FMEA on safety-critical modules |

**Independence Requirements**:
- **SIL 3 (TDC)**: **Independent Verifier MANDATORY** (EN 50128 §5.1.2.10e, Table B.5)
  - VER SHALL NOT be involved in requirements, design, implementation, integration, or testing of the software being verified
  - VER reports to VMGR (independent V&V authority), NOT to PM
  - VER has authority to reject phase completion if verification criteria not met
  - VMGR approval is REQUIRED for all VER reports; VMGR decision cannot be overridden by PM or COD

### 1.4 Relationship to Other Plans

This SVP is supported by and references:
- **Software Quality Assurance Plan (SQAP)** (DOC-TDC-SQAP-001) — quality standards, document templates, review checklists
- **Software Configuration Management Plan (SCMP)** (DOC-TDC-SCMP-001) — configuration control, baselines, change management
- **Software Validation Plan (SVaP)** (DOC-TDC-SVaP-001) — validation strategy, system testing, acceptance criteria
- **System Safety Plan** (DOC-TDC-SSP-SYS-001) — system-level safety requirements and hazard management
- **System Safety Requirements Specification** (DOC-TDC-SSRS-SYS-001) — allocated safety requirements

**Verification vs Validation Boundary**:
- **Verification (VER)**: "Are we building the product right?" — Confirms outputs correctly implement specifications (requirements → design → code → tests)
- **Validation (VAL)**: "Are we building the right product?" — Confirms software fulfills its intended use in the operational environment

---

## 2. References

### 2.1 Normative References

| Reference | Title | Version |
|-----------|-------|---------|
| EN 50128:2011 | Railway applications — Communication, signalling and processing systems — Software for railway control and protection systems | 2011 |
| EN 50126-1:2017 | Railway applications — Specification and demonstration of Reliability, Availability, Maintainability and Safety (RAMS) — Part 1: Generic RAMS process | 2017 |
| EN 50126-2:2017 | Railway applications — RAMS — Part 2: Systems approach to safety | 2017 |
| MISRA C:2012 | Guidelines for the use of the C language in critical systems | Amendment 2 (2020) |
| ISO 9001:2015 | Quality management systems — Requirements | 2015 |

### 2.2 Project Documents

| Document ID | Title | Phase |
|-------------|-------|-------|
| DOC-TDC-SRS-SYS-001 | System Requirements Specification | Phase 0 |
| DOC-TDC-SAD-SYS-001 | System Architecture Description | Phase 0 |
| DOC-TDC-SSP-SYS-001 | System Safety Plan | Phase 0 |
| DOC-TDC-SSRS-SYS-001 | System Safety Requirements Specification | Phase 0 |
| DOC-TDC-SQAP-001 | Software Quality Assurance Plan | Phase 1 |
| DOC-TDC-SCMP-001 | Software Configuration Management Plan | Phase 1 |
| DOC-TDC-SVaP-001 | Software Validation Plan | Phase 1 |

### 2.3 EN 50128 Key Clauses

| Clause | Topic |
|--------|-------|
| §6.2 | Software Verification |
| §6.2.4.2 | Software Verification Plan |
| §6.2.4.13 | Verification Report Requirements |
| Table A.5 | Verification and Testing Techniques |
| Table A.19 | Static Analysis Techniques |
| Table A.21 | Test Coverage for Code |
| §5.1.2.10e | VER Independence Requirements (SIL 3-4) |
| §5.3.5 | VER Role and Responsibilities (Annex B Table B.5) |

---

## 3. Definitions and Abbreviations

### 3.1 Abbreviations

| Abbreviation | Definition |
|--------------|------------|
| CCB | Change Control Board |
| CCN | Cyclomatic Complexity Number |
| CM | Configuration Manager |
| COD | Lifecycle Coordinator |
| DES | Designer |
| FMEA | Failure Modes and Effects Analysis |
| FTA | Fault Tree Analysis |
| HR | Highly Recommended (EN 50128 technique classification) |
| IMP | Implementer |
| INT | Integrator |
| M | Mandatory (EN 50128 technique classification) |
| MC/DC | Modified Condition/Decision Coverage |
| MISRA | Motor Industry Software Reliability Association |
| PM | Project Manager |
| QUA | Quality Assurance |
| R | Recommended (EN 50128 technique classification) |
| REQ | Requirements Engineer |
| RTM | Requirements Traceability Matrix |
| SAF | Safety Engineer |
| SIL | Safety Integrity Level |
| TST | Tester |
| VAL | Validator |
| VER | Verifier |
| VMGR | V&V Manager (Independent V&V Authority for SIL 3-4) |

### 3.2 Key Definitions

| Term | Definition (EN 50128:2011) |
|------|---------------------------|
| **Verification** | Confirmation by examination and provision of objective evidence that specified requirements have been fulfilled (§3.1.60) |
| **Validation** | Confirmation by examination and provision of objective evidence that the particular requirements for a specific intended use are fulfilled (§3.1.59) |
| **Static Analysis** | Analysis of software without execution (e.g., code review, data flow analysis, control flow analysis) |
| **Dynamic Analysis** | Analysis of software during execution (e.g., testing, profiling, debugging) |
| **Traceability** | Ability to trace the relationships between requirements, design, code, and tests (D.58) |
| **Coverage** | Measure of test completeness (statement, branch, condition, MC/DC) as a percentage of code executed during testing |
| **Independence** | Separation of VER role from design and implementation teams to ensure objective verification (§5.1.2.10e) |

---

## 4. Verification Organization

### 4.1 Verification Team Structure

#### 4.1.1 Verifier (VER) Role

**Responsibilities** (EN 50128 §5.3.5, Annex B Table B.5):
- Develop and maintain Software Verification Plan (this document)
- Perform verification activities per EN 50128 Table A.5 for assigned lifecycle phases
- Execute static analysis (control flow, data flow, MISRA C) per Table A.19
- Verify test coverage per Table A.21 (statement, branch, condition — mandatory SIL 3)
- Verify traceability (requirements → design → code → tests) per Table A.9 #7 (mandatory SIL 3)
- Collect and manage verification evidence per §6.2.4.8
- Generate Verification Reports for each phase per §6.2.4.13
- Ensure EN 50128 compliance at SIL 3
- Report to VMGR (not PM) for SIL 3 projects
- Approve or reject phase completion based on verification evidence

**Qualifications**:
- Deep knowledge of EN 50128:2011 verification requirements (§6.2, Table A.5, A.19, A.21)
- Experience with static analysis tools (PC-lint Plus, Cppcheck, Clang Static Analyzer)
- Expert understanding of C programming and MISRA C:2012 (Amendment 2)
- Familiarity with test coverage tools (gcov/lcov, Bullseye)
- Railway domain knowledge (EN 50126, EN 50129)
- At least 3 years experience in software verification at SIL 2+

**Independence Requirements (SIL 3 — MANDATORY)**:
- VER SHALL NOT have been involved in requirements, design, implementation, integration, or testing of the software being verified
- VER SHALL report to VMGR (independent V&V authority), not to PM or development leads
- VER SHALL NOT be subject to performance evaluation by PM or development managers
- VER SHALL have authority to reject phase completion if verification criteria not met
- VER findings SHALL NOT be overruled by PM or COD without VMGR approval

#### 4.1.2 V&V Manager (VMGR)

**Responsibilities** (EN 50128 §5.1.2.10f, platform extension):
- Coordinate VER team activities across all lifecycle phases
- Review and approve all VER reports before phase gate approval
- Coordinate with VAL (independent validator) for Phase 7 validation activities
- Final V&V approval authority for SIL 3 projects
- Report to Safety Authority (not PM or COD)
- Ensure VER independence is maintained throughout lifecycle
- Resolve conflicts between VER and development teams

**Independence** (SIL 3 — MANDATORY):
- VMGR SHALL be organizationally independent from PM, COD, and development teams
- VMGR SHALL report directly to Safety Authority or senior management
- VMGR decisions on V&V approval CANNOT be overridden by PM or COD

#### 4.1.3 Verification Support Roles

| Role | Responsibilities | Independence Required |
|------|------------------|----------------------|
| **QUA** | Oversee verification process quality, perform 1st-check on SQAP and SCMP | No |
| **CM** | Maintain traceability matrix, baseline verification evidence, configuration audits | No |
| **TST** | Execute tests, collect coverage data, provide test evidence to VER | No (but separation from IMP recommended) |
| **SAF** | Provide safety requirements, hazard analysis, support VER in safety verification | No |

### 4.2 Independence Management (SIL 3)

**EN 50128 Requirement** (§5.1.2.10e): Verifier SHALL be independent of design and implementation teams at SIL 3.

**Independence Measures**:
1. **Organizational Separation**: VER reports to VMGR, who reports to Safety Authority (not PM or COD)
2. **Role Separation**: VER SHALL NOT perform any design, implementation, integration, or testing activities
3. **Financial Independence**: VER performance evaluation and compensation not tied to project schedule or budget
4. **Authority**: VER has final authority to approve/reject phase completion; PM cannot override VER findings without VMGR approval
5. **Physical Separation**: VER workstation separate from development team (recommended)

**Prohibited Role Combinations (SIL 3)**:
- VER + DES (Designer)
- VER + IMP (Implementer)
- VER + REQ (Requirements Engineer) — for the same software being verified
- VER + TST (Tester) — for the same software being verified
- VER + INT (Integrator)

**Allowed Role Combinations (SIL 3)**:
- VER + QUA (Quality Assurance) — if QUA does not perform development activities
- VER + CM (Configuration Manager) — if CM maintains independence from development

---

## 5. Verification Strategy

### 5.1 Verification Approach

**Multi-Level Verification**: Verification is performed at multiple levels across the V-Model lifecycle:

1. **Document Verification** (Phases 1-4): Review and approve all lifecycle documents (SQAP, SCMP, SRS, SAS, SDS, test specs)
2. **Design Verification** (Phases 3-4): Verify architecture and design correctness, traceability, completeness, modularity (mandatory SIL 2+)
3. **Code Verification** (Phase 5): Static analysis, code review, MISRA C compliance, complexity analysis, data/control flow
4. **Test Verification** (Phases 5-7): Verify test completeness, coverage per Table A.21, traceability, test results
5. **Traceability Verification** (All phases): End-to-end traceability from system requirements to validation tests (mandatory SIL 3)
6. **Integration Verification** (Phase 6-7): Verify SW integration and SW/HW integration evidence
7. **Validation Verification** (Phase 7): VER reviews VAL evidence (Step B1: SW Integration Verification Report; Step B2: SW Validation Verification Report)

### 5.2 Verification Principles

**EN 50128 Verification Principles** (§6.2):

1. **Independence**: VER is organizationally and financially independent from development (mandatory SIL 3)
2. **Objectivity**: VER uses objective evidence (tool reports, test results, traceability matrices) — not subjective judgment
3. **Completeness**: VER verifies ALL lifecycle outputs per EN 50128 Annex C Table C.1
4. **Traceability**: VER ensures bidirectional traceability from system requirements to validation tests (mandatory SIL 3)
5. **Coverage**: VER verifies test coverage meets Table A.21 requirements (statement, branch, condition — mandatory SIL 3)
6. **Repeatability**: VER activities are documented and repeatable (verification reports, evidence archives)
7. **Compliance**: VER ensures compliance with EN 50128 techniques per Table A.5, A.19, A.21

### 5.3 Verification Workflow

**Per-Phase Verification Loop**:

```
Development Team → Deliverable → QUA 1st-check → VER Independent Verification → VMGR Approval → Phase Gate
                                                         ↓
                                                  (if findings)
                                                         ↓
                                         VER Non-Conformance Report
                                                         ↓
                                      Development Team Corrective Action
                                                         ↓
                                           VER Re-Verification
                                                         ↓
                                              VMGR Approval
```

**Phase Gate Approval Authority** (SIL 3):
- **COD**: Overall lifecycle authority, enforces phase gates
- **VMGR**: V&V approval authority — COD cannot open next phase gate without VMGR approval
- **VER**: Technical verification authority — VMGR cannot approve without VER recommendation
- **PM**: Coordinates development activities but has NO authority over VER or VMGR decisions

---

## 6. Verification Techniques (EN 50128 Table A.5)

### 6.1 Table A.5 Technique Selection

**EN 50128 Table A.5** defines 10 verification and testing techniques. For SIL 3, the following are MANDATORY (M) or HIGHLY RECOMMENDED (HR):

| # | Technique | Ref | SIL 0 | SIL 1-2 | SIL 3-4 | TDC Implementation |
|---|-----------|-----|-------|---------|---------|-------------------|
| 1 | Formal Proof | D.29 | - | R | HR | NOT PLANNED (rationale: formal methods not cost-effective for TDC; covered by extensive testing + static analysis) |
| 2 | Probabilistic Testing | D.41 | - | R | HR | NOT PLANNED (rationale: deterministic testing preferred for safety-critical software) |
| 3 | **Static Analysis** | Table A.19 | - | HR | **M** | **PC-lint Plus, Cppcheck, Clang Static Analyzer** |
| 4 | **Dynamic Analysis and Testing** | Table A.13 | - | HR | **M** | **Unity unit tests, integration tests, system tests** |
| 5 | Metrics | D.37 | - | R | HR | **Complexity (Lizard), coverage metrics, defect density** |
| 6 | Simulation | D.47 | R | R | R | NOT PLANNED (rationale: hardware-in-the-loop testing not in scope) |
| 7 | **Traceability** | D.58 | R | HR | **M** | **Requirements Traceability Matrix (RTM) — bidirectional** |
| 8 | Software Error Effect Analysis | D.25 | - | R | HR | **FMEA on safety-critical modules (door lock, speed interlock, obstacle detection)** |
| 9 | **Test Coverage for Code** | Table A.21 | R | HR | **M** | **gcov/lcov (statement, branch, condition)** |
| 10 | Performance Modelling | D.38 | - | R | R | NOT PLANNED (rationale: performance verified through testing) |

**Approved Combination for SIL 3** (per EN 50128 §4.8):
- **Selected Techniques**: 3, 4, 5, 7, 8, 9
- **Rationale**: This combination covers all MANDATORY (M) techniques (3, 4, 7, 9) plus HIGHLY RECOMMENDED (HR) techniques (5, 8). Formal proof (1) and probabilistic testing (2) are not cost-effective for TDC; comprehensive static analysis + dynamic testing + traceability provide equivalent safety assurance.

### 6.2 Technique 3: Static Analysis (MANDATORY SIL 3)

**Implementation**: See Section 7 (Static Analysis Requirements)

### 6.3 Technique 4: Dynamic Analysis and Testing (MANDATORY SIL 3)

**Implementation**:
- **Unit Testing**: Unity test framework, one test file per C module
- **Integration Testing**: Module-to-module interface testing, SW/HW integration testing
- **System Testing**: End-to-end functional testing, safety scenario testing
- **Coverage Measurement**: gcov/lcov (statement, branch, condition)
- **Boundary Value Analysis**: Test all input boundaries (e.g., speed = 5 km/h threshold)
- **Fault Injection**: Test error handling paths (sensor failures, communication timeouts)

**Acceptance Criteria**:
- All unit tests pass (100% pass rate)
- All integration tests pass (100% pass rate)
- Coverage meets Table A.21 requirements (statement, branch, condition — 100% SIL 3)
- All safety-critical paths tested (speed interlock, obstacle detection, door lock verification)

### 6.4 Technique 5: Metrics (HIGHLY RECOMMENDED SIL 3)

**Metrics Collected**:

| Metric | Tool | Target (SIL 3) | Evidence Location |
|--------|------|----------------|------------------|
| Cyclomatic Complexity (CCN) | Lizard | ≤ 10 per function | `docs/reports/complexity-report.md` |
| Statement Coverage | gcov/lcov | 100% | `test-results/coverage/index.html` |
| Branch Coverage | gcov/lcov | 100% | `test-results/coverage/index.html` |
| Condition Coverage | gcov (manual analysis) | 100% | `test-results/coverage/condition-coverage.md` |
| Defect Density | Manual tracking | ≤ 0.5 defects/KLOC at release | `docs/reports/defect-log.md` |
| MISRA C Violations | PC-lint Plus | 0 mandatory violations | `docs/reports/misra-compliance-report.md` |
| Code Size | `cloc` | Tracked per module | `docs/reports/code-metrics.md` |

**Metric Review Frequency**: After each phase completion, before gate approval

### 6.5 Technique 7: Traceability (MANDATORY SIL 3)

**Implementation**: See Section 10 (Traceability Verification)

### 6.6 Technique 8: Software Error Effect Analysis (HIGHLY RECOMMENDED SIL 3)

**Implementation**:
- **FMEA** (Failure Modes and Effects Analysis) on safety-critical modules:
  - Door lock verification module
  - Speed interlock module
  - Obstacle detection module
  - Cross-channel comparison module (2oo2 architecture)
- **Analysis Scope**: Identify single-point failures, common-cause failures, undetected errors
- **Evidence**: FMEA worksheet per SAF (Safety Engineer), reviewed by VER
- **Acceptance Criteria**: All identified failure modes have mitigation (defensive code, dual-channel voting, safe state)

### 6.7 Technique 9: Test Coverage for Code (MANDATORY SIL 3)

**Implementation**: See Section 8 (Test Coverage Requirements)

---

## 7. Static Analysis Requirements (EN 50128 Table A.19)

### 7.1 Static Analysis Techniques (MANDATORY SIL 3)

**EN 50128 Table A.19** defines 12 static analysis techniques. For SIL 3-4, the following are MANDATORY (M) or HIGHLY RECOMMENDED (HR):

| # | Technique | Ref | SIL 0 | SIL 1-2 | SIL 3-4 | TDC Tool |
|---|-----------|-----|-------|---------|---------|----------|
| 1 | Boundary Value Analysis | D.4 | R | R | HR | **Manual code review + test case design** |
| 2 | Control Flow Analysis | D.8 | - | HR | **M** | **Cppcheck, Clang Static Analyzer** |
| 3 | Data Flow Analysis | D.10 | - | HR | **M** | **Cppcheck, Clang Static Analyzer** |
| 4 | Symbolic Execution | - | - | R | R | NOT PLANNED |
| 5 | Common Cause Failure Analysis | D.9 | - | R | HR | **FMEA (SAF), VER review** |
| 6 | Worst Case Execution Time Analysis | - | - | R | HR | **Timing analysis (manual), critical path measurement** |
| 7 | Stack Usage Analysis | - | - | R | HR | **Static stack analyzer, `gcc -fstack-usage`** |
| 8 | Semantic Analysis | - | R | HR | HR | **PC-lint Plus, Cppcheck** |
| 9 | Complexity Metrics | D.12 | - | R | HR | **Lizard (cyclomatic complexity)** |

**Approved Combination for SIL 3**: Techniques 1, 2, 3, 5, 6, 7, 8, 9

### 7.2 Control Flow Analysis (MANDATORY SIL 3)

**Objective**: Detect unreachable code, infinite loops, improper control structures

**Tools**:
- **Cppcheck**: `--enable=style,warning --inconclusive`
- **Clang Static Analyzer**: `scan-build -o analysis/ make`

**Acceptance Criteria**:
- No unreachable code (except defensive error-handling paths)
- No infinite loops (all loops have exit conditions)
- No knotted code (reducible control flow graphs only)
- All `switch` statements have `default` case

### 7.3 Data Flow Analysis (MANDATORY SIL 3)

**Objective**: Detect uninitialized variables, unused variables, dead stores

**Tools**:
- **Cppcheck**: `--enable=all --inconclusive`
- **Clang Static Analyzer**: `scan-build -enable-checker alpha.core.Uninitialized`

**Acceptance Criteria**:
- No uninitialized variables (all variables initialized before use)
- No unused variables (or justified as defensive programming)
- No dead stores (or justified)
- All pointer dereferences checked for NULL

### 7.4 Complexity Metrics (HIGHLY RECOMMENDED SIL 3)

**Objective**: Ensure code is maintainable and testable

**Tool**: **Lizard** (cyclomatic complexity analyzer)

**Acceptance Criteria**:
- **Cyclomatic Complexity (CCN)**: ≤ 10 per function (SIL 3)
- **Function Length**: ≤ 100 lines per function (recommended)
- **Parameter Count**: ≤ 5 parameters per function (recommended)
- **Nesting Depth**: ≤ 4 levels (recommended)

**Rationale**: EN 50128 Table A.4 #6 (Structured Programming) is MANDATORY for SIL 3-4; low complexity supports testability and maintainability.

### 7.5 Stack Usage Analysis (HIGHLY RECOMMENDED SIL 3)

**Objective**: Ensure stack does not overflow (critical for safety)

**Tool**: `gcc -fstack-usage` (generates `.su` files)

**Acceptance Criteria**:
- Maximum stack depth per task < 50% of allocated stack size
- No dynamic recursion (highly recommended SIL 3-4)
- Stack overflow detection enabled (if hardware supports)

### 7.6 Worst Case Execution Time (WCET) Analysis (HIGHLY RECOMMENDED SIL 3)

**Objective**: Ensure real-time deadlines are met (critical for obstacle detection — 150 ms budget)

**Approach**:
- **Static Analysis**: Analyze control flow, count instruction cycles
- **Measurement**: Instrument code with timing counters, measure on target hardware
- **Critical Paths**: Speed interlock (≤ 10 ms), obstacle detection (≤ 150 ms), door lock check (≤ 10 ms)

**Tool**: Manual timing analysis + hardware timers (RTOS tick counters)

**Acceptance Criteria**:
- All real-time deadlines met with 20% margin
- WCET documented per safety-critical function

---

## 8. Test Coverage Requirements (EN 50128 Table A.21)

### 8.1 Coverage Requirements by SIL

**EN 50128 Table A.21 — Test Coverage for Code**:

| Coverage Type | SIL 0 | SIL 1-2 | SIL 3-4 | TDC Target |
|---------------|-------|---------|---------|-----------|
| **Entry Point Coverage** | - | - | - | 100% (all functions called) |
| **Statement Coverage** | HR | HR | **M** | **100%** |
| **Branch Coverage** | HR | **M** | **M** | **100%** |
| **Condition Coverage** (Boolean operand) | - | R | **M** | **100%** |
| **Data Flow Coverage** | - | R | HR | NOT REQUIRED (but monitored) |
| **Path Coverage** | - | - | R | NOT REQUIRED |

**SIL 3 Mandatory Requirements**:
- **Statement Coverage**: 100% (all executable statements executed at least once)
- **Branch Coverage**: 100% (all branches taken — both true and false)
- **Condition Coverage**: 100% (all Boolean operands tested — both true and false independently)

**Note**: EN 50128 Table A.21 does NOT mandate a specific percentage threshold; it mandates that the techniques SHALL be applied. However, for SIL 3, industry best practice is 100% coverage with justified exclusions.

### 8.2 Coverage Measurement Tools

**Primary Tool**: **gcov/lcov** (GNU coverage tool)

**Configuration**:
```bash
# Compile with coverage instrumentation
gcc -fprofile-arcs -ftest-coverage -O0 -g src/*.c -o build/module.o

# Run tests
./run_tests.sh

# Generate coverage report
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory test-results/coverage/
```

**Alternative Tool (SIL 4)**: **Bullseye** (for MC/DC coverage — highly recommended SIL 4, optional SIL 3)

### 8.3 Coverage Acceptance Criteria

**SIL 3 Acceptance Criteria**:

| Coverage Type | Target | Minimum Acceptable | Uncovered Code Justification |
|---------------|--------|-------------------|----------------------------|
| Entry Point | 100% | 100% | None allowed (all functions must be tested) |
| Statement | 100% | 99% | Defensive code that cannot be triggered in normal testing |
| Branch | 100% | 100% | None allowed |
| Condition | 100% | 99% | Complex conditions where independent testing is infeasible |

**Justified Exclusions** (with VER approval):
- Defensive error-handling code that cannot be triggered without hardware fault injection
- Dead code required for future expansion (if justified and documented)
- Compiler-generated code (e.g., initialization stubs)

**Unjustified Exclusions** (CRITICAL FINDING):
- Application logic code not covered by tests
- Safety-critical paths not covered
- Boundary conditions not tested

### 8.4 Coverage Verification Process

1. **TST** executes all unit tests, integration tests, system tests with coverage instrumentation enabled
2. **TST** generates coverage reports (HTML + summary)
3. **VER** reviews coverage reports:
   - Verify statement, branch, condition coverage ≥ target
   - Identify uncovered code
   - Request justification for uncovered code from IMP
   - Approve or reject coverage evidence
4. **VER** documents coverage analysis in Verification Report
5. **VMGR** approves coverage evidence before phase gate

---

## 9. MISRA C:2012 Verification

### 9.1 MISRA C:2012 Requirements (MANDATORY SIL 2+)

**EN 50128 Table A.4 Technique #10** (MISRA C): **MANDATORY for SIL 2+**

**Standard**: MISRA C:2012 (Guidelines for the use of the C language in critical systems), Amendment 2 (2020)

**Scope**: All C source code (`.c` and `.h` files) in `src/` directory

**Compliance Target**: **100% compliance** (or justified deviations)

### 9.2 MISRA C Rule Categories

**MISRA C:2012 Rule Classification**:
- **Mandatory**: Must be complied with (no deviations)
- **Required**: Deviations require formal deviation (rare)
- **Advisory**: Deviations require justification (more common)

**SIL 3 Requirement**: Zero **Mandatory** and **Required** violations; **Advisory** violations require written justification.

### 9.3 MISRA C Verification Tools

**Primary Tool**: **PC-lint Plus** (Gimpel Software)

**Configuration**:
```
// au-misra3.lnt — MISRA C:2012 configuration
+elib(*)                  // Enable all library checks
-w4                       // Warning level 4 (all messages)
-summary()                // Summary report
+fll                      // Long long support (if used)
-e537                     // Suppress repeated includes (justified)
```

**Alternative Tools**:
- **Cppcheck** (MISRA addon): `cppcheck --addon=misra src/`
- **Clang-Tidy** (partial MISRA coverage): `clang-tidy --checks='-*,misra-*' src/*.c`

### 9.4 Deviation Process

**Permitted Deviations** (SIL 3):
- **Advisory** rules: Deviations allowed with written justification
- **Required** rules: Rare deviations allowed with formal review and approval by VER + VMGR
- **Mandatory** rules: No deviations allowed

**Deviation Documentation**:
```c
/* MISRA Deviation: Rule 11.5 (Required)
 * Justification: Cast from void* to uint8_t* required for hardware register access
 * Risk Assessment: Low — pointer alignment verified by hardware design
 * Approved By: VER, VMGR
 * Date: 2026-XX-XX
 */
uint8_t* reg = (uint8_t*)0x40000000;
```

**Deviation Register**: `docs/reports/misra-deviations.md` (maintained by CM, approved by VER)

### 9.5 MISRA C Compliance Acceptance Criteria

**SIL 3 Acceptance Criteria**:
- **Mandatory** violations: 0
- **Required** violations: 0 (or < 5 with formal deviations approved by VMGR)
- **Advisory** violations: < 10 per KLOC (with written justifications)

**Critical MISRA C Rules for TDC (examples)**:
- **Rule 1.3** (Mandatory): No undefined behavior
- **Rule 8.13** (Advisory): Pointer parameters should be `const` if not modified
- **Rule 10.1** (Required): Operands shall not be of inappropriate essential type
- **Rule 21.3** (Required): `malloc` and `free` shall not be used (CRITICAL for SIL 3)
- **Dir 4.12** (Required): Dynamic memory allocation shall not be used

---

## 10. Traceability Verification

### 10.1 Traceability Requirements (MANDATORY SIL 3)

**EN 50128 Table A.9 Technique #7** (Traceability): **MANDATORY for SIL 3-4**

**Traceability Definition** (EN 50128 D.58): Ability to trace relationships between requirements, design, code, and tests bidirectionally.

**Traceability Chain**:
```
System Requirement → Software Requirement → Architecture → Design → Code → Unit Test → Integration Test → System Test → Validation Test
                                                                                                                         ↓
                                                                                           Safety Case Evidence ← Hazard Log
```

**Bidirectional Traceability**:
- **Forward**: Requirements → Tests (coverage)
- **Backward**: Tests → Requirements (justification)

### 10.2 Requirements Traceability Matrix (RTM)

**Location**: `docs/traceability/Requirements-Traceability-Matrix.md`

**Format**:

| System Req | SW Req | SIL | Architecture | Design | Code | Unit Test | Int Test | Sys Test | Val Test | Hazard | Status |
|------------|--------|-----|--------------|--------|------|-----------|----------|----------|----------|--------|--------|
| SYS-REQ-001 | SW-REQ-FUNC-001 | 3 | SAS-MOD-001 | SDS-FUNC-001 | door_lock.c:45 | TC-UNIT-001 | TC-INT-001 | TC-SYS-001 | TC-VAL-001 | HAZ-001 | ✅ Verified |

**RTM Verification Checklist** (per phase):
- [ ] All system requirements traced to software requirements (Phase 2)
- [ ] All software requirements traced to architecture elements (Phase 3)
- [ ] All architecture elements traced to design modules (Phase 4)
- [ ] All design modules traced to source code (Phase 5)
- [ ] All source code traced to unit tests (Phase 5)
- [ ] All software requirements traced to integration tests (Phase 6)
- [ ] All software requirements traced to system tests (Phase 7)
- [ ] All safety requirements (SIL 3) traced to validation tests (Phase 7)
- [ ] No orphaned requirements (requirements without tests)
- [ ] No orphaned code (code not traced to any requirement)
- [ ] No orphaned tests (tests not traced to any requirement)

### 10.3 Traceability Tools

**Tools**:
- **Markdown-based RTM**: Maintained by CM in `docs/traceability/`
- **Git commit messages**: Traceability tags (e.g., `[SW-REQ-FUNC-001]`)
- **Python scripts**: Automated traceability checks (optional)
- **`grep` / `ripgrep`**: Search for requirement IDs in code and test files

**Update Frequency**: RTM updated at every phase gate and every baseline change

### 10.4 Traceability Verification Process

1. **CM** maintains RTM (forward and backward traceability)
2. **VER** reviews RTM at every phase gate:
   - Verify all requirements traced to tests
   - Verify all code traced to requirements
   - Verify all tests traced to requirements
   - Identify gaps (orphaned requirements, code, tests)
3. **VER** requests corrective actions for gaps
4. **VER** approves RTM completeness before phase gate
5. **VMGR** approves traceability evidence

**Acceptance Criteria** (SIL 3):
- **100% forward traceability**: All requirements → tests
- **100% backward traceability**: All tests → requirements
- **0 orphaned requirements**: All requirements have at least one test
- **0 orphaned code**: All code traced to at least one requirement (or justified as infrastructure)

---

## 11. Verification Activities by Phase

### 11.1 Phase 1: Planning Phase Verification

**Objective**: Verify that planning documents (SQAP, SCMP, SVaP) are complete, consistent, and EN 50128 compliant. Note: SVP itself (this document) is **written by VER** but **2nd-checked by VAL** (no 1st-check per Annex C Table C.1).

**VER Deliverable**: **NO Verification Report** for Phase 1 (VER authors SVP, cannot self-check)

**QUA Role**: Performs 1st-check on SQAP and SCMP per Annex C Table C.1

**VAL Role**: Performs 2nd-check on SVP per Annex C Table C.1

### 11.2 Phase 2: Requirements Phase Verification

**Objective**: Verify that Software Requirements Specification (SRS) is complete, unambiguous, testable, and traceable.

#### 11.2.1 Verification Inputs
- Software Requirements Specification (SRS) — DOC-TDC-SRS-002
- Overall Software Test Specification — DOC-TDC-OSTS-007
- Hazard Log — DOC-TDC-HAZLOG-XXX
- Requirements Traceability Matrix (RTM) — initial version

#### 11.2.2 Verification Activities

| Activity | Method | Tool | Acceptance Criteria | Responsible |
|----------|--------|------|---------------------|-------------|
| **Requirements review** | Checklist-based review | SQAP checklist | All requirements unambiguous, testable, traceable (unique IDs) | VER |
| **SIL assignment verification** | Review SIL per requirement | Manual review | SIL level assigned per EN 50128 Table 4; safety requirements = SIL 3 | VER, SAF |
| **Traceability check** | RTM completeness | RTM spreadsheet/Markdown | All SW requirements traced to system requirements (100% forward) | VER |
| **Consistency check** | Cross-reference verification | Manual review | No conflicting requirements | VER |
| **Completeness check** | Structured walkthrough | Checklist | All system requirements decomposed to SW requirements | VER |
| **C constraints verification** | Review data types, memory | Manual review | Fixed-width types specified, static allocation required, error handling defined | VER |

**Requirements Quality Checklist**:
- [ ] All requirements have unique IDs (SW-REQ-FUNC-NNN, SW-REQ-PERF-NNN, SW-REQ-SAFE-NNN)
- [ ] All requirements use SHALL (mandatory) or SHOULD (recommended) language
- [ ] All requirements are unambiguous (single interpretation possible)
- [ ] All requirements are testable (verification method identified)
- [ ] All safety requirements have SIL level = 3 assigned
- [ ] All requirements traced to system requirements (RTM 100% complete)
- [ ] All C language constraints specified (fixed-width types, static allocation, no recursion)
- [ ] Hazard Log initiated and linked to safety requirements

#### 11.2.3 Verification Deliverables
- **Software Requirements Verification Report** — DOC-TDC-SRVR-008 (Annex C item 8)
- Updated RTM (if corrections needed)
- Verification findings and corrective actions
- Recommendation to VMGR (approve/reject phase completion)

### 11.3 Phase 3: Architecture & Design Phase Verification

**Objective**: Verify that Software Architecture Specification (SAS) and Software Design Specification (SDS) correctly implement requirements and are EN 50128 compliant.

#### 11.3.1 Verification Inputs
- Software Architecture Specification (SAS) — DOC-TDC-SAS-009
- Software Design Specification (SDS) — DOC-TDC-SDS-010
- Software Interface Specifications (SIS) — DOC-TDC-SIS-011
- Software Integration Test Specification — DOC-TDC-SITS-012
- Software/Hardware Integration Test Specification — DOC-TDC-SHITS-013
- Requirements Traceability Matrix (RTM) — updated

#### 11.3.2 Verification Activities

| Activity | Method | Tool | Acceptance Criteria | Responsible |
|----------|--------|------|---------------------|-------------|
| **Architecture review** | Structured walkthrough | SQAP checklist | Modular architecture (mandatory SIL 2+), all requirements addressed | VER |
| **Design review** | Checklist-based review | SQAP checklist | All modules designed, interfaces specified, defensive programming patterns | VER |
| **Traceability check** | RTM update verification | RTM | All requirements traced to design elements (100% forward) | VER |
| **Safety review** | Hazard analysis | FMEA worksheet | Safety requirements addressed in design, fail-safe mechanisms defined | VER, SAF |
| **C design review** | MISRA C, defensive programming | Manual review | Static allocation, no recursion (HR SIL 3-4), defensive programming patterns | VER |
| **Complexity estimation** | Estimated complexity | Manual estimation | Estimated CCN ≤ 10 per function | VER |
| **Interface verification** | Interface consistency | Manual review | All interfaces documented, data types specified | VER |

**Design Quality Checklist**:
- [ ] Modular architecture (mandatory SIL 2+) — modules < 500 LOC each
- [ ] All modules have defined interfaces (SIS complete)
- [ ] All requirements traced to design elements (RTM updated — 100% forward)
- [ ] Static memory allocation only (mandatory SIL 2+) — no `malloc/free`
- [ ] No recursion planned (highly recommended SIL 3-4)
- [ ] Defensive programming patterns specified (NULL checks, range checks, safe state)
- [ ] Error handling strategy defined (safe state, error codes, logging)
- [ ] Complexity estimated within limits (CCN ≤ 10)
- [ ] Safety architecture: 2oo2 dual-channel voting, cross-channel comparison, watchdog

#### 11.3.3 Verification Deliverables
- **Software Architecture and Design Verification Report** — DOC-TDC-SADVR-014 (Annex C item 14)
- Updated RTM (requirements → design traceability)
- Verification findings and corrective actions
- Recommendation to VMGR (approve/reject phase completion)

### 11.4 Phase 4: Component Design Phase Verification

**Objective**: Verify that Software Component Design Specification and Component Test Specification are complete and traceable.

#### 11.4.1 Verification Inputs
- Software Component Design Specification — DOC-TDC-SCDS-015
- Software Component Test Specification — DOC-TDC-SCTS-016
- Requirements Traceability Matrix (RTM) — updated

#### 11.4.2 Verification Activities

| Activity | Method | Acceptance Criteria | Responsible |
|----------|--------|---------------------|-------------|
| **Component design review** | Checklist-based review | All components designed to SDS requirements | VER |
| **Test specification review** | Checklist-based review | All components have unit test specifications | VER |
| **Traceability check** | RTM verification | All design elements traced to test cases | VER |
| **Complexity estimation** | Manual estimation | Estimated CCN ≤ 10 per function | VER |

#### 11.4.3 Verification Deliverables
- **Software Component Design Verification Report** — DOC-TDC-SCDVR-017 (Annex C item 17)
- Updated RTM
- Recommendation to VMGR

### 11.5 Phase 5: Implementation & Testing Phase Verification

**Objective**: Verify that source code correctly implements design, complies with MISRA C:2012, and meets EN 50128 coding requirements.

#### 11.5.1 Verification Inputs
- Source code (C files: `.h`, `.c`) in `src/` directory
- Unit test code (Unity framework) in `tests/unit/` directory
- Software Design Specification (SDS)
- Requirements Traceability Matrix (RTM)
- Unit test results
- Coverage reports (gcov/lcov)

#### 11.5.2 Verification Activities

| Activity | Method | Tool | Acceptance Criteria | Responsible |
|----------|--------|------|---------------------|-------------|
| **Static analysis** | Automated analysis | Cppcheck, Clang Static Analyzer | No critical/high issues | VER |
| **MISRA C compliance** | Automated checking | PC-lint Plus | 100% compliance (or justified deviations) | VER |
| **Code review** | Manual inspection | SQAP checklist | Code matches design, defensive programming used | VER, QUA |
| **Complexity analysis** | Automated measurement | Lizard | CCN ≤ 10 per function (SIL 3) | VER |
| **Data flow analysis** | Static analysis | Cppcheck | No uninitialized variables, no memory leaks | VER |
| **Control flow analysis** | Static analysis | Cppcheck | No unreachable code, no infinite loops | VER |
| **Traceability check** | RTM verification | RTM, `grep` | All design elements traced to code, all code traced to tests | VER |
| **Unit test verification** | Test case review | Unity test reports | All functions have unit tests, boundary values tested, 100% pass rate | VER |
| **Coverage analysis** | Coverage measurement | gcov/lcov | Statement 100%, Branch 100%, Condition 100% (SIL 3) | VER |

**Code Quality Checklist** (per EN 50128 Table A.4):
- [ ] MISRA C:2012 compliance (mandatory SIL 2+) — 100% or justified deviations
- [ ] Fixed-width types used (`uint8_t`, `uint32_t`, etc.) from `<stdint.h>`
- [ ] Static allocation only (mandatory SIL 2+) — no `malloc/free/calloc/realloc`
- [ ] No recursion (highly recommended SIL 3-4)
- [ ] All pointers validated before use (defensive programming — NULL checks)
- [ ] All return values checked (especially from functions that can fail)
- [ ] Cyclomatic complexity within limits (CCN ≤ 10 per function)
- [ ] All functions have unit tests (100% function coverage)
- [ ] Traceability: Code → Design (comments with design IDs), Code → Tests (test case IDs)
- [ ] Error handling: Safe state on all critical errors, no silent failures

#### 11.5.3 Verification Deliverables
- **Software Source Code Verification Report** — DOC-TDC-SSCVR-019 (Annex C item 19)
- **Software Component Test Report** (reviewed by VER) — DOC-TDC-SCTR-020 (Annex C item 20)
- Static analysis reports (PC-lint, Cppcheck, Clang)
- MISRA C compliance report with deviation rationale
- Complexity analysis report
- Coverage reports (statement, branch, condition)
- Updated RTM (design → code → tests traceability)
- Verification findings and corrective actions
- Recommendation to VMGR

### 11.6 Phase 6: Integration Phase Verification

**Objective**: Verify that integrated software components function correctly together and meet integration test requirements.

#### 11.6.1 Verification Inputs
- Integrated software build
- Software Integration Test Report — DOC-TDC-SITR-021
- Software/Hardware Integration Test Report — DOC-TDC-SHITR-022
- Interface specifications

#### 11.6.2 Verification Activities

| Activity | Method | Acceptance Criteria | Responsible |
|----------|--------|---------------------|-------------|
| **Integration test review** | Test case review | All interfaces tested, all integration scenarios covered | VER |
| **Test execution verification** | Test result analysis | All integration tests passed (100% pass rate) | VER |
| **Interface verification** | Interface testing | All interfaces function correctly, no communication errors | VER, INT |
| **Performance verification** | Performance testing | Performance requirements met (HR SIL 3-4): timing deadlines, resource usage | VER |
| **Traceability check** | RTM verification | All design elements traced to integration tests | VER |

#### 11.6.3 Verification Deliverables
- **Software Integration Verification Report** — DOC-TDC-SIVR-023 (Annex C item 23)
  - **IMPORTANT**: Per EN 50128 §6.3.4.12–6.3.4.14, item 23 is produced in **Phase 7 Step B1** (not Phase 6)
  - **Phase 6 has NO VER report** per standard phase mapping
  - VER reviews integration test evidence in Phase 6 but does NOT produce a formal report until Phase 7

### 11.7 Phase 7: Validation Phase Verification (Special Two-Step Flow)

**Objective**: VER reviews validation evidence in two steps per EN 50128 §6.3.4.12–6.3.4.14.

**Phase 7 Special Flow** (per EN 50128):

#### Step B1: SW Integration Verification (§6.3.4.12)
- **VER Input**: Software Integration Test Report (item 21), SW/HW Integration Test Report (item 22)
- **VER Activity**: Review integration test evidence, verify completeness, verify traceability
- **VER Output**: **Software Integration Verification Report** (item 23, Annex C)

#### Step B2: SW Validation Verification (§6.3.4.13–6.3.4.14)
- **VER Input**: Software Validation Plan (item 5), Software Validation Report (item 25), Overall SW Test Report (item 24), Tools Validation Report (item 26), Release Note (item 27)
- **VER Activity**: Review validation evidence package, verify SVaP followed, verify all tests passed, verify traceability complete
- **VER Output**: **Software Validation Verification Report** (item †, no Annex C number per EN 50128)

**Note**: Item † (Software Validation Verification Report) is normatively required by §6.3.4.12 but not assigned an Annex C item number in the standard.

#### 11.7.1 Verification Deliverables
- **Software Integration Verification Report** (item 23) — Phase 7 Step B1
- **Software Validation Verification Report** (item †) — Phase 7 Step B2

Both reports submitted to VMGR for approval before COD Phase 7 gate.

### 11.8 Phase 8: Assessment Phase Verification

**Objective**: VER performs **1st-check only** on Assessment Plan and Report (items 45-46). VER does **NOT** review the content of the assessment (assessor independence).

**VER Role** (SIL 3):
- Perform 1st-check on Software Assessment Plan (item 45) and Software Assessment Report (item 46) per Annex C Table C.1
- Verify document format, completeness, traceability to EN 50128 requirements
- **VER SHALL NOT** comment on the content, findings, or conclusions of the assessment
- **NO VER report** is generated for Phase 8

**IMPORTANT**: The Independent Safety Assessor (ISA) is **mandatory for SIL 1-4** per §6.4.1.1. ISA is independent from all development and V&V roles. ISA reviews ALL lifecycle artifacts and issues the final Software Assessment Report.

### 11.9 Phase 9: Deployment Phase Verification

**Objective**: Verify that release package is complete, correct, and ready for deployment.

#### 11.9.1 Verification Inputs
- Software Release and Deployment Plan — DOC-TDC-SRDP-036
- Release package (binary, source, documentation)
- Deployment records

#### 11.9.2 Verification Activities

| Activity | Method | Acceptance Criteria | Responsible |
|----------|--------|---------------------|-------------|
| **Release package verification** | Checklist-based review | All artifacts present, versions correct, baselines match SCMP | VER, CM |
| **Deployment verification** | Deployment record review | Deployment followed plan, target hardware verified | VER |
| **Traceability verification** | Final RTM check | End-to-end traceability complete (100%) | VER |

#### 11.9.3 Verification Deliverables
- **Deployment Verification Report** — DOC-TDC-DVR-040 (Annex C item 40)
- Recommendation to VMGR

---

## 12. Verification Tools

### 12.1 Tool Classification (EN 50128 Section 6.7)

**EN 50128 Tool Classes**:
- **T1 Tools** (generate no output used in executable): No qualification required
- **T2 Tools** (support test/verification): Validation of tool required
- **T3 Tools** (generate executable code): Full qualification required

### 12.2 Verification Tool List

| Tool | Version | Purpose | EN 50128 Class | Qualification Status | Evidence Location |
|------|---------|---------|---------------|---------------------|------------------|
| **PC-lint Plus** | 2.1 | MISRA C:2012 compliance checking | T2 | REQUIRED | `docs/tool-validation/pclint-validation.md` |
| **Cppcheck** | 2.10 | Static analysis (control flow, data flow) | T2 | REQUIRED | `docs/tool-validation/cppcheck-validation.md` |
| **Clang Static Analyzer** | 15.0 | Additional static analysis | T2 | REQUIRED | `docs/tool-validation/clang-validation.md` |
| **gcov / lcov** | GCC 11.x | Test coverage measurement (statement, branch) | T2 | REQUIRED | `docs/tool-validation/gcov-validation.md` |
| **Lizard** | 1.17 | Cyclomatic complexity analysis | T1 | NOT REQUIRED | N/A (T1 tool) |
| **Unity** | 2.5.2 | Unit test framework | T1 | NOT REQUIRED | N/A (T1 tool) |
| **Git** | 2.39 | Version control, traceability | T1 | NOT REQUIRED | N/A (T1 tool) |
| **GCC** | 11.3 | C compiler | T3 | REQUIRED (by compiler vendor) | Vendor qualification certificate |

**Tool Qualification Requirements** (SIL 3):
- **T1 Tools**: No qualification required (output not used in safety-critical executable)
- **T2 Tools**: Tool validation REQUIRED — verify tool produces correct results via sample programs with known defects
- **T3 Tools**: Full tool qualification REQUIRED — typically provided by vendor (e.g., GCC qualification certificate)

### 12.3 Tool Validation Process (T2 Tools)

**Validation Approach**:
1. Select representative sample programs with known defects (e.g., MISRA C violations, uninitialized variables)
2. Run tool on sample programs
3. Verify tool detects all known defects (100% detection rate)
4. Document tool validation results in tool validation report
5. VER approves tool validation report
6. VMGR approves tool for use in project

**Validation Evidence**: `docs/tool-validation/` directory

**Validation Frequency**: Once per project, or when tool version changes

---

## 13. Verification Evidence Management

### 13.1 Evidence Collection

All verification activities SHALL produce objective evidence. Evidence SHALL be collected, reviewed, and archived per EN 50128 §6.2.4.8.

**Evidence Types**:

| Evidence Type | Generator | Storage Location | Retention Period |
|---------------|-----------|------------------|-----------------|
| Verification reports (per phase) | VER | `docs/reports/verification/` | Life of system + 10 years |
| Static analysis reports (PC-lint, Cppcheck, Clang) | VER | `docs/reports/static-analysis/` | Life of system + 10 years |
| Coverage reports (gcov/lcov) | TST (verified by VER) | `test-results/coverage/` | Life of system + 10 years |
| Complexity reports (Lizard) | VER | `docs/reports/complexity/` | Life of system + 10 years |
| Code review records | VER, QUA | `docs/reports/code-reviews/` | Life of system + 10 years |
| Test results (unit, integration, system) | TST (verified by VER) | `test-results/` | Life of system + 10 years |
| Traceability matrix (RTM) | CM (verified by VER) | `docs/traceability/` | Life of system + 10 years |
| Tool validation reports | VER | `docs/tool-validation/` | Life of system + 10 years |
| FMEA worksheets | SAF (verified by VER) | `docs/safety/` | Life of system + 10 years |
| MISRA C deviation register | CM (approved by VER) | `docs/reports/misra-deviations.md` | Life of system + 10 years |

**Evidence Format**: Markdown (`.md`) for reports, HTML for coverage/static analysis, PDF for formal deliverables

### 13.2 Evidence Review Process

**Review Process**:
1. **Evidence Collection**: VER collects evidence from all verification activities (tool reports, checklists, review records)
2. **Evidence Review**: VER reviews evidence for completeness, correctness, and EN 50128 compliance
3. **Gap Identification**: VER identifies gaps or non-conformances (missing evidence, failed tests, uncovered code)
4. **Corrective Action Request**: VER issues non-conformance reports to responsible parties (IMP, DES, TST)
5. **Corrective Action Verification**: VER verifies corrective actions completed (re-run tools, re-test, update documentation)
6. **Evidence Approval**: VER approves evidence package for phase
7. **VMGR Review**: VMGR reviews VER report and evidence package
8. **VMGR Approval**: VMGR approves phase completion (or requests additional evidence)

**Review Criteria**:
- Evidence is objective (tool-generated or independently reviewed)
- Evidence is complete (all verification activities performed per SVP)
- Evidence demonstrates compliance with EN 50128 requirements
- Evidence is traceable to requirements (RTM complete)
- Evidence is under configuration control (SCMP baseline)

### 13.3 Evidence Archival

**Archival Process**:
- All evidence SHALL be baselined per phase per SCMP Section 7 (Baseline Management)
- Evidence SHALL be stored under version control (Git repository)
- Evidence SHALL be included in release package (Phase 9)
- Evidence SHALL be retained per EN 50128 records retention policy (life of system + 10 years)

**SIL 3 Requirement**: Evidence SHALL be independently reviewed and approved by VMGR before phase completion.

---

## 14. Verification Acceptance Criteria

### 14.1 Phase Completion Criteria

**Phase SHALL NOT be approved until all verification acceptance criteria are met.**

| Phase | Acceptance Criteria | Evidence Required | VER Report |
|-------|---------------------|-------------------|------------|
| **Phase 1 (Planning)** | All plans complete, consistent, EN 50128 compliant | VAL 2nd-check on SVP | None (VER authors SVP) |
| **Phase 2 (Requirements)** | All requirements unambiguous, testable, traced; SIL assigned | Requirements Verification Report, RTM | Item 8 |
| **Phase 3 (Design)** | Design complete, traceable, modular (SIL 2+), complexity estimated | Design Verification Report, RTM | Item 14 |
| **Phase 4 (Component Design)** | Component design complete, test specifications complete | Component Design Verification Report, RTM | Item 17 |
| **Phase 5 (Implementation)** | MISRA C compliant (SIL 2+), CCN ≤ 10, coverage 100%, unit tests pass | Implementation Verification Report, Static analysis reports, Coverage reports, RTM | Item 19 |
| **Phase 6 (Integration)** | All integration tests passed, interfaces verified | Integration test reports (reviewed, no VER report) | None |
| **Phase 7 (Validation)** | Integration evidence reviewed (Step B1), Validation evidence reviewed (Step B2) | SW Integration Verification Report (item 23), SW Validation Verification Report (item †) | Items 23, † |
| **Phase 8 (Assessment)** | 1st-check on items 45-46 complete | VER 1st-check record | None |
| **Phase 9 (Deployment)** | Release package complete, deployment verified, traceability 100% | Deployment Verification Report | Item 40 |

### 14.2 Non-Conformance Handling

**Process**:
1. **Identification**: VER identifies non-conformance (evidence missing, criteria not met)
2. **Documentation**: VER documents non-conformance in verification report (severity, description, responsible party)
3. **Corrective Action Assignment**: VER assigns corrective action to responsible party with due date
4. **Corrective Action Implementation**: Responsible party implements corrective action (fix code, add tests, update documentation)
5. **Corrective Action Verification**: VER verifies corrective action completed (re-run tools, re-review)
6. **Status Update**: VER updates verification report status (open → closed)

**Non-Conformance Severity** (SIL 3):
- **CRITICAL**: Blocks phase approval — must be resolved before gate (e.g., missing traceability, 0% coverage on safety-critical code)
- **MAJOR**: Requires corrective action before approval (e.g., MISRA C violations, uncovered branches)
- **MINOR**: Can be deferred to next phase (e.g., documentation typos, advisory MISRA violations with justification)

**SIL 3 Hard Rule**: All CRITICAL and MAJOR non-conformances MUST be resolved before VMGR approval.

---

## 15. Verification Schedule

### 15.1 Verification Milestones

| Milestone | Phase | Planned Date | Verification Activities | Deliverable | VMGR Approval |
|-----------|-------|--------------|-------------------------|-------------|---------------|
| **Planning Gate** | Phase 1 | 2026-04-15 | VAL 2nd-check on SVP | SVP (this doc) | ✅ Required |
| **Requirements Gate** | Phase 2 | 2026-05-31 | Requirements review, traceability, SIL assignment | SW Requirements Verification Report (item 8) | ✅ Required |
| **Design Gate** | Phase 3 | 2026-07-31 | Design review, architecture review, traceability | SW Architecture and Design Verification Report (item 14) | ✅ Required |
| **Component Design Gate** | Phase 4 | 2026-08-31 | Component design review, test spec review | SW Component Design Verification Report (item 17) | ✅ Required |
| **Implementation Gate** | Phase 5 | 2026-11-30 | Static analysis, MISRA C, code review, coverage | SW Source Code Verification Report (item 19) | ✅ Required |
| **Integration Gate** | Phase 6 | 2026-12-31 | Integration test review, interface verification | Integration test reports (reviewed, no VER report) | ✅ Required |
| **Validation Gate** | Phase 7 | 2027-02-28 | Integration verification (Step B1), Validation verification (Step B2) | SW Integration Verification Report (item 23), SW Validation Verification Report (item †) | ✅ Required |
| **Assessment Gate** | Phase 8 | 2027-03-31 | 1st-check on items 45-46 | VER 1st-check record | ✅ Required |
| **Deployment Gate** | Phase 9 | 2027-04-30 | Release package verification, deployment verification | Deployment Verification Report (item 40) | ✅ Required |

**Note**: Dates are estimates and subject to project schedule updates per PM.

### 15.2 Verification Effort Estimate

**Effort Estimates** (per phase):

| Phase | Verification Effort (person-hours) | Notes |
|-------|-----------------------------------|-------|
| Phase 1 (Planning) | 8 hours | VAL 2nd-check on SVP |
| Phase 2 (Requirements) | 60 hours | Requirements review (300 estimated requirements), RTM setup |
| Phase 3 (Design) | 48 hours | Architecture review (12 modules), design review, complexity estimation |
| Phase 4 (Component Design) | 32 hours | Component design review (30 components), test spec review |
| Phase 5 (Implementation) | 120 hours | Static analysis (5000 LOC), code review, MISRA C, coverage analysis |
| Phase 6 (Integration) | 40 hours | Integration test review (50 integration tests) |
| Phase 7 (Validation) | 60 hours | Integration verification (Step B1: 20 hours), Validation verification (Step B2: 40 hours) |
| Phase 8 (Assessment) | 8 hours | 1st-check on items 45-46 |
| Phase 9 (Deployment) | 24 hours | Release package verification, deployment verification |
| **Total** | **400 hours** | ~50 person-days (~2.5 person-months) |

**SIL 3 Multiplier**: Independent verification adds ~30% effort overhead due to independence requirements (separate reviews, VMGR coordination).

---

## 16. Risk Management

### 16.1 Verification Risks

| Risk | Probability | Impact | Mitigation | Owner |
|------|-------------|--------|------------|-------|
| **Insufficient tool qualification** | Medium | High | Qualify T2 tools early (Phase 1), allocate 40 hours for tool validation | VER |
| **Incomplete traceability** | Medium | Critical | Establish RTM in Phase 2, update continuously at every phase gate, automate with scripts | VER, CM |
| **Verifier independence compromise** (SIL 3) | Low | Critical | Enforce organizational independence (VER → VMGR → Safety Authority, NOT PM), document reporting structure in SQAP | VMGR |
| **Inadequate coverage** | Medium | High | Monitor coverage continuously (weekly builds with coverage), allocate time for additional tests, prioritize safety-critical code | VER, TST |
| **MISRA C non-compliance** | Medium | High | Run PC-lint early and often (daily CI builds), provide MISRA C training for IMP, allocate time for deviation documentation | VER, IMP |
| **Late delivery of evidence** | High | Medium | Set evidence deadlines 1 week before phase gate, escalate delays to PM/COD early | VER |
| **Tool failures** | Low | Medium | Maintain backup tools (e.g., Cppcheck + Clang Static Analyzer), test tools on sample code before use | VER |

### 16.2 Risk Monitoring

**Risk Review Frequency**: Monthly (or per phase gate)

**Risk Owner**: VER (reports to VMGR)

**Escalation**: Critical risks escalated to VMGR → Safety Authority

---

## 17. EN 50128 Compliance Matrix

### 17.1 EN 50128 Section 6.2 Compliance

| Requirement | EN 50128 Clause | Evidence | Section in SVP | Status |
|-------------|----------------|----------|---------------|--------|
| **Verification plan established** | §6.2.4.2 | This document (SVP) | All | ✅ |
| **Verification independence (SIL 3-4)** | §5.1.2.10e, Table B.5 | Section 4.2 | 4.2 | ✅ |
| **Verification activities defined** | §6.2.4.3–6.2.4.11 | Section 11 | 11 | ✅ |
| **Verification techniques selected** | Table A.5 | Section 6 | 6 | ✅ |
| **Traceability (SIL 3-4)** | Table A.9 #7 | Section 10 | 10 | ✅ |
| **Test coverage (SIL 3-4)** | Table A.21 | Section 8 | 8 | ✅ |
| **Static analysis (SIL 3-4)** | Table A.19 | Section 7 | 7 | ✅ |
| **Evidence management** | §6.2.4.8 | Section 13 | 13 | ✅ |
| **Verification reports per phase** | §6.2.4.13 | Section 11 | 11 | ✅ |
| **VMGR approval (SIL 3-4)** | Platform extension | Section 4.1.2 | 4.1.2 | ✅ |

### 17.2 EN 50128 Table A.5 Compliance (Verification Techniques)

| # | Technique | SIL 0 | SIL 1-2 | SIL 3-4 | TDC Implementation | Section in SVP |
|---|-----------|-------|---------|---------|-------------------|---------------|
| **3** | Static Analysis | - | HR | **M** | PC-lint Plus, Cppcheck, Clang Static Analyzer | 7 |
| **4** | Dynamic Analysis and Testing | - | HR | **M** | Unity tests, integration tests | 6.3 |
| **5** | Metrics | - | R | HR | Complexity (Lizard), coverage, defect density | 6.4 |
| **7** | Traceability | R | HR | **M** | Requirements Traceability Matrix (RTM) | 10 |
| **8** | Software Error Effect Analysis | - | R | HR | FMEA on safety-critical modules | 6.6 |
| **9** | Test Coverage for Code | R | HR | **M** | gcov/lcov (statement, branch, condition) | 8 |

### 17.3 EN 50128 Table A.19 Compliance (Static Analysis)

| # | Technique | SIL 0 | SIL 1-2 | SIL 3-4 | TDC Tool | Section in SVP |
|---|-----------|-------|---------|---------|----------|---------------|
| **2** | Control Flow Analysis | - | HR | **M** | Cppcheck, Clang Static Analyzer | 7.2 |
| **3** | Data Flow Analysis | - | HR | **M** | Cppcheck, Clang Static Analyzer | 7.3 |
| **9** | Complexity Metrics | - | R | HR | Lizard | 7.4 |

### 17.4 EN 50128 Table A.21 Compliance (Test Coverage)

| Coverage Type | SIL 0 | SIL 1-2 | SIL 3-4 | TDC Target | Tool | Section in SVP |
|---------------|-------|---------|---------|-----------|------|---------------|
| **Statement Coverage** | HR | HR | **M** | 100% | gcov/lcov | 8.1 |
| **Branch Coverage** | HR | **M** | **M** | 100% | gcov/lcov | 8.1 |
| **Condition Coverage** | - | R | **M** | 100% | gcov (manual analysis) | 8.1 |

---

## APPENDICES

### Appendix A: Verification Checklist Templates

**Note**: Detailed verification checklists are maintained in the SQAP (DOC-TDC-SQAP-001) Section 11 (Document Review Checklists) and Section 12 (Code Review Checklists). VER SHALL use SQAP checklists for all verification activities.

### Appendix B: Verification Report Template

**Template**: See `deliverables/verification/Verification-Report-template.md`

**Required Sections** (per EN 50128 §6.2.4.13):
1. Verification Scope
2. Verification Activities Performed
3. Verification Results (per activity)
4. Non-Conformances (severity, description, assigned to, status)
5. Verification Conclusion (Pass / Fail / Pass with Conditions)
6. Verifier Signature and Date
7. VMGR Approval Signature and Date

### Appendix C: Traceability Matrix (RTM) Template

**Location**: `docs/traceability/Requirements-Traceability-Matrix.md`

**Format**: See Section 10.2

---

## DOCUMENT HISTORY

This document is maintained under configuration control per SCMP (DOC-TDC-SCMP-001). All changes SHALL be approved by the Change Control Board (CCB) and VMGR.

**Current Version**: 1.0 DRAFT  
**Last Updated**: 2026-03-30  
**Next Review**: 2026-04-15 (Phase 1 gate — VAL 2nd-check)

---

**END OF DOCUMENT**

---

**Verifier Signature**: ___________________________  
**Date**: ___________________________

**VMGR Approval (after VAL 2nd-check)**: ___________________________  
**Date**: ___________________________
