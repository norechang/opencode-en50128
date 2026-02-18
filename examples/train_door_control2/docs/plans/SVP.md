# Software Verification Plan

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SVP-2026-001 |
| **Version** | 2.0 |
| **Date** | 2026-02-18 |
| **Project** | train_door_control2 |
| **SIL Level** | 3 |
| **Author** | Independent Verifier |
| **Reviewer** | QA Manager |
| **Approver** | Project Manager |
| **Status** | Draft |

---

## Document Control

| Version | Date | Author | Changes | Approval Status |
|---------|------|--------|---------|-----------------|
| 0.1 | 2026-02-18 | Independent Verifier | Initial draft | Draft |
| 1.0 | 2026-02-18 | Independent Verifier | First approved version | Approved |
| 2.0 | 2026-02-18 | Independent Verifier | Major revision: Added standard header, Document Control table, Approvals table, and enhanced template compliance per EN 50128 Section 6.2 | Draft |

---

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | Independent Verifier | | 2026-02-18 |
| **Independent Verifier** (SIL 3) | Independent Verifier | | |
| **QA Manager** | QA Manager | | |
| **Project Manager** | Project Manager | | |

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [Verification Objectives](#2-verification-objectives)
3. [Verification Techniques](#3-verification-techniques)
4. [Verification Activities](#4-verification-activities)
5. [Tools and Environment](#5-tools-and-environment)
6. [Independence Requirements](#6-independence-requirements)
7. [Verification Criteria](#7-verification-criteria)
8. [Verification Schedule](#8-verification-schedule)
9. [Deliverables](#9-deliverables)
10. [Roles and Responsibilities](#10-roles-and-responsibilities)
11. [Risk Management](#11-risk-management)
12. [Configuration Management](#12-configuration-management)
13. [References](#13-references)

---

## 1. Introduction

### 1.1 Purpose

This Software Verification Plan (SVP) defines the verification strategy, activities, techniques, and acceptance criteria for the train_door_control2 software development. Verification ensures that software outputs of each lifecycle phase correctly implement the specifications and requirements in accordance with EN 50128:2011 Section 6.2.

**Verification Definition** (EN 50128): Confirmation by examination and provision of objective evidence that specified requirements have been fulfilled.

### 1.2 Scope

This SVP applies to:
- All software lifecycle phases (requirements through validation)
- All software configuration items (documents, code, tests)
- All verification techniques per EN 50128 Table A.5
- Target SIL level: 3

**Verification Coverage:**
- All software requirements (SRS)
- Software architecture (SAS)
- Software design (SDS)
- Source code implementation (C language)
- Unit and integration tests
- Traceability verification

**Out of Scope**:
- System validation (covered by Software Validation Plan - DOC-SVAP-2026-001)
- Hardware verification (covered by Hardware Verification Plan)

### 1.3 SIL Classification

**Target SIL Level**: 3

**EN 50128 Verification Requirements** (Table A.5):

**SIL 3 Mandatory Techniques**:
- Dynamic Analysis and Testing (**M**)
- Test Coverage for Code (**M**)
- Traceability (**M**)
- Functional and Black-box Testing (**M**)
- Static Analysis (**M**)

**Independence Requirements**:
- **SIL 3**: **Independent Verifier MANDATORY** (different person/team from developers)

### 1.4 Project Information

- **Project Name**: Train Door Control System (Version 2)
- **Software Component**: Door Control Module
- **SIL Level**: 3
- **Programming Language**: C (MISRA C:2012 compliant)
- **Target Platform**: Embedded railway controller

### 1.5 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **Verification** | Confirmation that software outputs correctly implement specifications |
| **Validation** | Confirmation that software fulfills its intended use |
| **Static Analysis** | Analysis of software without execution (code review, data/control flow analysis) |
| **Dynamic Analysis** | Analysis of software during execution (testing, profiling) |
| **Traceability** | Ability to trace requirements through design, code, and tests |
| **Coverage** | Measure of test completeness (statement, branch, condition, MC/DC) |
| **MISRA C** | Motor Industry Software Reliability Association C coding standard |
| **CCN** | Cyclomatic Complexity Number |
| **RTM** | Requirements Traceability Matrix |

### 1.6 References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[EN50126]** | EN 50126-1:2017 Railway Applications - RAMS |
| **[MISRA]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-2026-001 |
| **[SVaP]** | Software Validation Plan, DOC-SVAP-2026-001 |
| **[LIFECYCLE]** | LIFECYCLE.md - EN 50128 V-Model lifecycle definition |

---

## 2. Verification Objectives

The verification objectives for SIL 3 train_door_control2 are:

1. **Correctness**: Ensure software meets all functional and safety requirements
2. **Compliance**: Verify compliance with EN 50128:2011 SIL 3 requirements
3. **Traceability**: Confirm complete bidirectional traceability from requirements to code and tests
4. **Quality**: Validate static analysis, complexity (CCN ≤10), and coverage metrics (100% statement/branch/condition)
5. **Independence**: Provide evidence for independent verification (MANDATORY for SIL 3)
6. **Safety**: Verify all safety requirements are correctly implemented

---

## 3. Verification Techniques

### 3.1 EN 50128 Table A.5 Techniques

**Mandatory Techniques for SIL 3:**

| # | Technique | SIL 3 | Reference | Implementation |
|---|-----------|-------|-----------|----------------|
| **3** | Static Analysis | **M** | Table A.19 | PC-lint Plus, Cppcheck, Clang |
| **7** | Traceability | **M** | D.58 | Requirements Traceability Matrix |
| **8** | Dynamic Analysis and Testing | **M** | Table A.13 | Unit, Integration, System tests |
| - | Test Coverage for Code | **M** | Table A.21 | gcov/lcov (100% stmt/branch/cond) |
| - | Functional and Black-box Testing | **M** | Table A.14 | System test cases |
| - | Performance Testing | **M** | Table A.18 | Timing analysis |

**Highly Recommended Techniques for SIL 3:**
- **Formal Proof** (Technique 1) - Highly Recommended
- **Metrics** (Technique 5) - Highly Recommended (complexity, MISRA compliance)
- **Software Error Effect Analysis** (Technique 9) - Highly Recommended
- **Software Fault Tree Analysis** (Technique 10) - Highly Recommended

**Approved Combination** (Table A.5):
- Static Analysis (3), Metrics (5), Traceability (7), Testing (8) + Formal Proof (1)

### 3.2 Static Analysis Techniques (Table A.19)

**Mandatory for SIL 3:**
- **Control Flow Analysis** (Technique 2) - **MANDATORY**
- **Data Flow Analysis** (Technique 3) - **MANDATORY**
- **Compiler Warnings** (Technique 4) - **MANDATORY**

**Implementation:**
- PC-lint Plus: Control flow, data flow, MISRA C compliance
- Cppcheck: General static analysis with MISRA addon
- Clang Static Analyzer: Deep semantic analysis
- GCC with `-Wall -Wextra -Werror`

### 3.3 Test Coverage for Code (Table A.21)

**Mandatory for SIL 3:**
- **Statement Coverage**: 100% (MANDATORY)
- **Branch Coverage**: 100% (MANDATORY)
- **Condition Coverage** (MC/DC): 100% (MANDATORY)

**Tools:**
- gcov/lcov: Statement, branch, and condition coverage
- Custom Python scripts for threshold verification

---

## 4. Verification Activities

### 4.1 Requirements Verification

**Activities:**
- Review SRS for completeness and unambiguity
- Verify SIL assignment justification
- Check traceability to higher-level requirements
- Verify requirements are testable
- Check for conflicting or ambiguous requirements

**Deliverable:** Requirements Verification Report

**Pass Criteria:**
- All requirements clear and unambiguous
- All requirements testable
- SIL levels justified
- Traceability complete

### 4.2 Design Verification

**Activities:**
- Review SAS and SDS for modular design (MANDATORY for SIL 3)
- Verify interface definitions (fully defined)
- Check defensive programming patterns
- Validate complexity limits (CCN ≤ 10 for SIL 3)
- Verify static memory allocation strategy (no malloc/free for SIL 3)
- Check for recursion (none for SIL 3)

**Deliverable:** Design Verification Report

**Pass Criteria:**
- Modular design with clear interfaces
- Complexity estimates ≤10 per function
- Defensive programming patterns present
- Static allocation only
- Traceability to requirements complete

### 4.3 Code Verification

**Activities:**
- Static analysis with qualified tools
- MISRA C:2012 compliance verification (100% mandatory and required rules)
- Complexity analysis (CCN ≤ 10 for all functions)
- Manual code review/walkthrough
- Control flow analysis
- Data flow analysis

**Deliverable:** Code Verification Reports (per module)

**Pass Criteria:**
- Zero MISRA C mandatory rule violations
- Zero MISRA C required rule violations (or justified deviations)
- All functions CCN ≤ 10
- Zero critical static analysis issues
- All warnings reviewed and justified

### 4.4 Testing Verification

**Activities:**
- Unit test verification (test completeness, correctness)
- Integration test verification
- Coverage analysis verification (100% statement/branch/condition)
- Fault injection testing
- Boundary value analysis
- Performance testing (timing constraints)

**Deliverable:** Test Verification Report

**Pass Criteria:**
- 100% statement coverage
- 100% branch coverage
- 100% condition coverage (MC/DC)
- All tests passed
- Performance requirements met

### 4.5 Traceability Verification

**Activities:**
- Bidirectional traceability matrix validation
- Requirements-to-design traceability
- Design-to-code traceability
- Code-to-test traceability
- Identify orphan requirements or untested code

**Deliverable:** Traceability Verification Report

**Pass Criteria:**
- 100% bidirectional traceability
- No orphan requirements
- No untested code
- RTM complete and up-to-date

---

## 5. Tools and Environment

### 5.1 Static Analysis Tools

| Tool | Version | Purpose | TCL | Qualification Status |
|------|---------|---------|-----|---------------------|
| **PC-lint Plus** | 2.0 | MISRA C compliance, control/data flow analysis | TCL 2 | Required |
| **Cppcheck** | 2.10 | General static analysis with MISRA addon | TCL 2 | Required |
| **Clang Static Analyzer** | Latest | Deep semantic analysis | TCL 2 | Required |

### 5.2 Complexity Analysis Tools

| Tool | Version | Purpose | TCL | Qualification Status |
|------|---------|---------|-----|---------------------|
| **Lizard** | 1.17 | Cyclomatic complexity measurement | TCL 1 | Low risk |

### 5.3 Coverage Analysis Tools

| Tool | Version | Purpose | TCL | Qualification Status |
|------|---------|---------|-----|---------------------|
| **gcov/lcov** | Latest | Statement, branch, and condition coverage | TCL 2 | Required |

### 5.4 Other Tools

| Tool | Version | Purpose |
|------|---------|---------|
| **Unity Test Framework** | Latest | Unit testing |
| **Python 3.x** | 3.8+ | Automation scripts, threshold verification |
| **Git** | Latest | Configuration management |

### 5.5 Tool Qualification (SIL 3)

**EN 50128 Requirement**: Tools used for automated verification SHALL be qualified (Section 6.7)

**Tool Classification:**
- **TCL 1** (Low confidence): Errors unlikely to go undetected (e.g., Lizard)
- **TCL 2** (Medium confidence): Errors may go undetected, tool output verified (e.g., PC-lint, gcov)
- **TCL 3** (High confidence): Errors likely undetected, generates safety code (e.g., compiler)

**Qualification Evidence**: Stored in `docs/tool-qualification/`

---

## 6. Independence Requirements

### 6.1 EN 50128 Requirements

Per EN 50128 Section 5.3.5 and Table A.5:

**SIL 3 (MANDATORY):**
- **Independent Verification MANDATORY**
- Verifier SHALL NOT be the same person as designer or implementer
- Verifier SHALL be organizationally independent from development team
- Verifier SHALL have authority to reject software that does not meet verification criteria
- Verifier SHALL report directly to Safety Authority (NOT Project Manager)

### 6.2 Implementation

**Verification Team:**
- Independent Verifier (Lead)
- Verification Engineers

**Independence Verification:**
- [x] Verifier organizationally separate from development
- [x] Verifier reports to Safety Authority
- [x] Verifier has authority to reject non-compliant software

**Evidence Collection:**
- Verification activities performed by dedicated verification team
- Evidence collection and reporting independent of development team
- All verification reports signed by Independent Verifier

---

## 7. Verification Criteria

### 7.1 Pass/Fail Criteria

**Static Analysis:**
- Zero critical issues
- All warnings reviewed and justified
- Zero MISRA C mandatory rule violations
- Zero MISRA C required rule violations (or documented/approved deviations)

**Complexity:**
- CCN ≤ 10 for all functions (MANDATORY for SIL 3)
- Average CCN ≤ 5

**Coverage:**
- 100% statement coverage (MANDATORY for SIL 3)
- 100% branch coverage (MANDATORY for SIL 3)
- 100% condition coverage / MC/DC (MANDATORY for SIL 3)

**Traceability:**
- Complete bidirectional traceability (100%)
- Requirements → Design → Code → Tests
- No orphan requirements
- No untested code

**MISRA C:**
- Compliance with MISRA C:2012
- All mandatory rules: 100% compliance
- All required rules: 100% compliance (deviations documented and approved)

### 7.2 Quality Gates

**Requirements Verification Gate:**
- Before design phase
- All requirements verified
- SIL levels justified

**Design Verification Gate:**
- Before implementation phase
- Design compliant with requirements
- Complexity budgets met
- Interfaces fully defined

**Code Verification Gate:**
- Continuous during implementation (weekly checks)
- MISRA C compliance verified
- Static analysis passed
- Complexity within limits

**Testing Verification Gate:**
- Before integration phase
- All tests passed
- Coverage requirements met

**Final Verification Gate:**
- Before validation phase
- All verification activities complete
- All evidence collected
- Traceability verified
- Final Verification Report approved

---

## 8. Verification Schedule

### Phase 1: Planning (Current)
- **Timeline**: Current phase
- **Activities**: SVP development and approval
- **Deliverable**: This document (SVP)

### Phase 2: Requirements Verification
- **Timeline**: 2 weeks after SRS approval
- **Activities**: Requirements review, traceability check
- **Deliverable**: Requirements Verification Report

### Phase 3: Design Verification
- **Timeline**: 3 weeks after SDS approval
- **Activities**: Design review, complexity analysis, interface verification
- **Deliverable**: Design Verification Report

### Phase 4: Implementation Verification
- **Timeline**: Continuous during implementation (weekly checks)
- **Activities**: Static analysis, MISRA C compliance, code reviews
- **Deliverable**: Code Verification Reports (per module)

### Phase 5: Testing Verification
- **Timeline**: 2 weeks after test completion
- **Activities**: Coverage analysis, test verification
- **Deliverable**: Test Verification Report

### Phase 6: Final Verification
- **Timeline**: 1 week before validation
- **Activities**: Final checks, evidence review, traceability verification
- **Deliverable**: Final Verification Report

---

## 9. Deliverables

### 9.1 Verification Reports

**Required Reports:**
- Requirements Verification Report (Phase 2)
- Design Verification Report (Phase 3)
- Code Verification Reports (Phase 4, per module)
- Test Verification Report (Phase 5)
- Final Verification Report (Phase 6)

**Report Contents:**
- Verification activities performed
- Pass/fail criteria
- Results and findings
- Non-conformances identified
- Evidence references
- Independent Verifier signature

### 9.2 Evidence Collection

**Verification Evidence:**
- Static analysis reports (PC-lint, Cppcheck, Clang)
- Complexity analysis results (Lizard)
- Coverage reports (gcov/lcov)
- Traceability matrices (RTM)
- MISRA C compliance reports
- Deviation records (justified deviations)
- Review records (code review checklists)

**Evidence Storage:** `docs/verification/evidence/`

**Evidence Retention:** Project lifecycle + 10 years

---

## 10. Roles and Responsibilities

### 10.1 Independent Verifier

**Responsibilities:**
- Execute all verification activities
- Collect and document evidence
- Report findings to Project Manager and Safety Authority
- Approve verification completion
- Sign all verification reports
- Maintain independence from development team

**Authority:**
- Reject software that does not meet verification criteria
- Halt releases if verification incomplete
- Escalate issues directly to Safety Authority

### 10.2 Development Team

**Responsibilities:**
- Provide access to code, tests, and documentation
- Address verification findings
- Implement corrective actions
- Participate in reviews (as reviewees)
- Maintain traceability information

### 10.3 Project Manager

**Responsibilities:**
- Ensure verification independence
- Review verification reports
- Approve verification milestones
- Allocate resources for verification activities
- Support verifier authority

**Constraints:**
- SHALL NOT influence verifier's decisions (SIL 3 independence requirement)

### 10.4 Safety Authority

**Responsibilities:**
- Oversee independent verification
- Review verification reports
- Approve safety-critical verification decisions

---

## 11. Risk Management

### 11.1 Verification Risks

| Risk | Impact | Likelihood | Mitigation |
|------|--------|------------|------------|
| Tool qualification delays | High | Medium | Early tool setup and qualification |
| Incomplete traceability | High | Medium | Continuous traceability maintenance |
| Complexity violations | Medium | Medium | Automated complexity checks in CI/CD |
| Coverage gaps | High | Low | Coverage targets in test planning |
| Independence compromised | Critical | Low | Organizational separation, reporting to Safety Authority |

### 11.2 Mitigation Strategies

**Tool Qualification:**
- Early tool setup and qualification (Phase 1)
- Supplier evidence collection
- Validation testing

**Traceability:**
- Continuous traceability maintenance
- RTM updated with every change
- Automated traceability checks

**Complexity:**
- Automated complexity checks in CI/CD
- Complexity budgets in design phase
- Refactoring before implementation

**Coverage:**
- Coverage targets in test planning (100% for SIL 3)
- Coverage measurement during testing
- Gap analysis and additional tests

**Independence:**
- Organizational separation enforced
- Reporting structure to Safety Authority
- Authority documented and communicated

---

## 12. Configuration Management

### 12.1 Verification Artifacts Under CM

All verification artifacts shall be under configuration management per SCMP:
- Version control in Git
- Baselines at phase gates
- Change control for SVP modifications
- Traceability to verification evidence

**CM Responsibilities:**
- Configuration Manager maintains verification artifact baselines
- All verification reports versioned
- Evidence archived with baselines

**SVP Change Control:**
- All changes to this SVP require CCB approval
- Major revisions increment version number
- Changes logged in Document Control table

---

## 13. References

### 13.1 Normative References

1. EN 50128:2011 Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems
2. EN 50126-1:2017 Railway Applications - The Specification and Demonstration of Reliability, Availability, Maintainability and Safety (RAMS)
3. MISRA C:2012 Guidelines for the use of the C language in critical systems
4. ISO/IEC 9899:2018 Programming languages - C
5. IEC 61508:2010 Functional safety of electrical/electronic/programmable electronic safety-related systems

### 13.2 Project References

| Reference | Document ID |
|-----------|-------------|
| **Software Quality Assurance Plan** | DOC-SQAP-2026-001 |
| **Software Configuration Management Plan** | DOC-SCMP-2026-001 |
| **Software Validation Plan** | DOC-SVAP-2026-001 |
| **Lifecycle Definition** | LIFECYCLE.md |

---

**END OF DOCUMENT**
