# Software Quality Assurance Plan

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SQAP-2026-001 |
| **Version** | 2.0 |
| **Date** | 2026-02-18 |
| **Project** | train_door_control2 |
| **SIL Level** | 3 |
| **Author** | Jane Smith, QA Manager |
| **Reviewer** | Bob Johnson, QA Engineer |
| **Approver** | Project Manager |
| **Status** | Draft |

---

## Document Control

| Version | Date | Author | Changes | Approval Status |
|---------|------|--------|---------|-----------------|
| 0.1 | 2026-02-18 | Jane Smith | Initial draft | Draft |
| 1.0 | 2026-02-18 | Jane Smith | First approved version | Approved |
| 2.0 | 2026-02-18 | Jane Smith | Major revision: Added standard header, Document Control table, Approvals table, and template compliance per EN 50128 requirements | Draft |

---

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (QA Manager)** | Jane Smith | | 2026-02-18 |
| **Reviewer (QA Engineer)** | Bob Johnson | | |
| **Safety Manager** | | | |
| **Project Manager** | | | |

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [Quality Objectives](#2-quality-objectives)
3. [Quality Organization](#3-quality-organization)
4. [Quality Standards](#4-quality-standards)
5. [Quality Activities by Lifecycle Phase](#5-quality-activities-by-lifecycle-phase)
6. [Reviews and Audits](#6-reviews-and-audits)
7. [Non-Conformance Management](#7-non-conformance-management)
8. [Problem Reporting and Corrective Action](#8-problem-reporting-and-corrective-action)
9. [Traceability Management](#9-traceability-management)
10. [Tool Qualification](#10-tool-qualification)
11. [Quality Metrics](#11-quality-metrics)
12. [Training](#12-training)
13. [References](#13-references)

---

## 1. Introduction

### 1.1 Purpose

This Software Quality Assurance Plan (SQAP) establishes the quality assurance processes, procedures, and activities for the train_door_control2 project to ensure compliance with EN 50128:2011 requirements for SIL 3 railway software development. This plan defines QA responsibilities, standards, review processes, and quality metrics necessary to deliver safe and reliable railway control software.

### 1.2 Scope

**Software Component:** Train Door Control System (train_door_control2)  
**SIL Level:** 3  
**Development Phases:** Full V-Model lifecycle (Requirements through Validation)  
**Programming Language:** C (MISRA C:2012 compliant)  
**Target Platform:** Railway door control embedded system  

**QA Coverage:**
- Requirements quality assurance
- Design quality assurance
- Implementation quality assurance (code reviews, static analysis)
- Testing quality assurance
- Documentation quality assurance
- Process compliance audits

**QA Team:**
- QA Manager: Jane Smith
- QA Engineers: Bob Johnson, Alice Brown

### 1.3 Applicable Standards

- EN 50128:2011 Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems
- EN 50126-1:2017 Railway Applications - RAMS (Part 1)
- EN 50126-2:2017 Railway Applications - RAMS (Part 2)
- MISRA C:2012 Guidelines for the use of the C language in critical systems (MANDATORY for SIL 3)
- IEC 61508:2010 Functional safety of electrical/electronic/programmable electronic safety-related systems
- ISO 9001:2015 Quality management systems

### 1.4 Definitions and Abbreviations

| Term | Definition |
|------|------------|
| **QA** | Quality Assurance |
| **SIL** | Safety Integrity Level (0-4) |
| **NCR** | Non-Conformance Report |
| **CAR** | Corrective Action Request |
| **MISRA C** | Motor Industry Software Reliability Association C standard |
| **CCN** | Cyclomatic Complexity Number |
| **RTM** | Requirements Traceability Matrix |
| **CCB** | Configuration Control Board |

---

## 2. Quality Objectives

### 2.1 Overall Quality Goals

**For SIL 3, the quality objectives are:**

1. **Correctness:** All software requirements implemented correctly with 100% traceability
2. **Reliability:** Software operates without failure under specified conditions
3. **Safety:** All safety requirements met with appropriate SIL 3 level
4. **Maintainability:** Code is readable, modular, and well-documented
5. **Compliance:** Full compliance with EN 50128:2011 and MISRA C:2012

### 2.2 SIL 3 Quality Objectives

**SIL 3 Requirements:**
- Code review coverage: 100% (MANDATORY)
- Static analysis: MANDATORY
- MISRA C:2012 compliance: MANDATORY (100% mandatory and required rules)
- Cyclomatic complexity: ≤10 (MANDATORY)
- Test coverage: 100% statement, 100% branch, 100% condition (MANDATORY)
- Independent verification and validation: MANDATORY

### 2.3 Quality Metrics Targets

See Section 11 for detailed quality metrics, including:
- MISRA C compliance: 100%
- Test coverage: 100% statement/branch/condition
- Cyclomatic complexity: Maximum 10, Average ≤5
- Code review coverage: 100%
- Defect density: < 2 defects per KLOC

---

## 3. Quality Organization

### 3.1 QA Team Structure

**QA Manager:** Jane Smith
- Overall quality oversight
- Audit approval
- Quality gate authorization
- Non-conformance escalation
- Reports to: Safety Authority (independent of Project Manager per SIL 3 requirements)

**QA Engineers:** Bob Johnson, Alice Brown
- Code reviews
- Design reviews
- Process audits
- Metrics collection
- Testing oversight

### 3.2 Independence Requirements

**SIL 3 (MANDATORY):**
- QA function MUST be independent from development team
- QA Manager reports directly to Safety Authority (NOT Project Manager)
- QA has authority to halt releases if quality criteria not met
- Independent verification and validation required

**Independence Verification:**
- [x] QA team organizationally separate from development
- [x] QA reports to Safety Authority independent of PM
- [x] QA authority documented in Project Charter

### 3.3 Roles and Responsibilities

**QA Manager (Jane Smith):**
- Develop and maintain SQAP
- Conduct quality audits (PCA, FCA)
- Approve NCRs and CARs
- Authorize phase gate transitions
- Report quality metrics to management

**QA Engineers (Bob Johnson, Alice Brown):**
- Perform code reviews (100% coverage)
- Conduct design reviews
- Monitor MISRA C compliance
- Verify test coverage
- Track defects and NCRs

**Development Team:**
- Comply with quality standards
- Address review findings
- Participate in reviews
- Resolve defects in timely manner

**Project Manager:**
- Allocate resources for QA activities
- Support QA independence
- Act on QA recommendations
- Approve quality-related process changes

---

## 4. Quality Standards

### 4.1 Coding Standards

**MISRA C:2012 (MANDATORY for SIL 3):**
- All mandatory rules: 100% compliance
- All required rules: 100% compliance (deviations require justification)
- Advisory rules: Compliance recommended

**Project-Specific C Coding Guidelines:**
- Fixed-width integer types (uint8_t, uint16_t, uint32_t, etc.)
- Static allocation only (NO malloc/calloc/realloc/free)
- No recursion (Highly Recommended for SIL 3)
- Explicit error handling (all return values checked)
- Defensive programming (all inputs validated)
- Consistent naming conventions for train door control logic

**Cyclomatic Complexity Limits:**
- SIL 3: CCN ≤ 10 (MANDATORY)
- Average complexity target: ≤5

### 4.2 Documentation Standards

**EN 50128 Document Requirements (Annex C Table C.1):**
- All mandatory documents per SIL 3 level
- Standard document header (see DOCUMENT-HEADER-TEMPLATE.md)
- Version control for all documents
- Traceability to requirements (MANDATORY for SIL 3)
- Review and approval signatures

**Document Templates:**
- Follow templates in `.opencode/skills/en50128-documentation/templates/`
- Template compliance verified by QA before approval

### 4.3 Process Standards

**EN 50128 V-Model Lifecycle:**
- Requirements → Design → Implementation → Testing → Validation
- Phase gates with quality criteria
- Independent verification and validation (MANDATORY for SIL 3)

**Configuration Management:**
- MANDATORY for all SIL levels (EN 50128 Section 6.6)
- Version control (Git)
- Change control via CCB
- Baseline management

---

## 5. Quality Activities by Lifecycle Phase

### 5.1 Phase 1: Planning
- [x] SQAP review and approval
- [x] SCMP review and approval
- [x] SVP review and approval
- [x] SVaP review and approval
- [ ] Tool qualification plan review
- [x] Quality standards defined

### 5.2 Phase 2: Requirements
- [ ] Requirements document review
- [ ] Requirements traceability verification
- [ ] Requirements quality checklist completed
- [ ] SIL level assignment review
- [ ] Requirements ambiguity check

### 5.3 Phase 3: Architecture & Design
- [ ] Architecture review (modular design, interfaces)
- [ ] Design review (complexity, defensive programming)
- [ ] Design-to-requirements traceability verification
- [ ] Safety architecture review

### 5.4 Phase 4: Implementation & Testing
- [ ] Code reviews (100% coverage)
- [ ] MISRA C compliance verification
- [ ] Static analysis review
- [ ] Complexity analysis review
- [ ] Unit test review
- [ ] Code-to-design traceability verification

### 5.5 Phase 5: Integration
- [ ] Integration test review
- [ ] Interface testing review
- [ ] Performance testing review (MANDATORY for SIL 3)

### 5.6 Phase 6: Validation
- [ ] System test review
- [ ] Validation test review
- [ ] Coverage analysis review (100% statement/branch/condition)
- [ ] Traceability end-to-end verification

---

## 6. Reviews and Audits

### 6.1 Code Reviews

**Scope:** 100% of source code (MANDATORY for SIL 3)

**Frequency:** All C code reviewed before integration into main branch

**Participants:** Developer, Senior Developer (Reviewer), QA Engineer

**Process:**
1. Developer submits code for review
2. QA Engineer performs review using checklist
3. Findings documented in review record
4. Developer addresses findings
5. QA Engineer verifies resolution

**Review Checklist:**
- [ ] MISRA C:2012 compliance (100% mandatory and required rules)
- [ ] Cyclomatic complexity ≤ 10
- [ ] Defensive programming patterns (all pointers validated, all returns checked)
- [ ] Error handling complete
- [ ] Static allocation only (no malloc/free)
- [ ] Comments adequate
- [ ] Traceability to design

**Exit Criteria:** Zero critical issues, all major issues resolved, traceability verified

**Review Records:** Stored in `docs/reviews/code-reviews/`

### 6.2 Design Reviews

**Scope:** All design documents (SAS, SDS)

**Frequency:** Architecture design (SAS), detailed design (SDS), interface designs

**Participants:** Designer, Requirements Engineer, Safety Engineer, QA Engineer

**Review Checklist:**
- [ ] Modular design (MANDATORY SIL 3)
- [ ] Static allocation strategy (SIL 3)
- [ ] Interfaces fully defined
- [ ] Complexity budgets met (≤10 per function)
- [ ] Traceability to requirements
- [ ] Safety design patterns applied

**Exit Criteria:** Design approved by all participants, traceability complete, safety concerns addressed

### 6.3 Document Reviews

**Scope:** All project deliverables

**Review Checklist:**
- [ ] Template compliance (DOCUMENT-HEADER-TEMPLATE.md)
- [ ] Technical accuracy
- [ ] Completeness
- [ ] Consistency with related documents
- [ ] EN 50128 compliance

### 6.4 Process Audits

**Frequency:** Quarterly (MANDATORY for SIL 3)

**Additional Audits:**
- Phase transitions (before each phase gate)
- Major milestones (every 2 weeks minimum)

**Audit Types:**
- Physical Configuration Audit (PCA): Before each baseline
- Functional Configuration Audit (FCA): Before each baseline
- Process compliance audit: Quarterly

**Scope:** Process compliance, EN 50128 adherence, documentation completeness

**Participants:** QA team, Project Manager, Independent Assessor (SIL 3)

**Deliverable:** Audit report with findings, corrective action plans

---

## 7. Non-Conformance Management

### 7.1 Non-Conformance Reporting

**Non-Conformance Report (NCR) Process:**
1. QA identifies non-conformance during review/audit
2. NCR raised with severity (Critical/Major/Minor)
3. Assigned to responsible party
4. Root cause analysis performed
5. Corrective action implemented
6. QA verifies resolution
7. NCR closed

**NCR Tracking:** GitHub Issues with NCR- prefix (format: NCR-YYYY-NNN)

### 7.2 Severity Levels

| Severity | Definition | Example | Action Required |
|----------|------------|---------|-----------------|
| **Critical** | Safety impact or EN 50128 violation | MISRA mandatory rule violation, Complexity >10 | Immediate fix, cannot proceed |
| **Major** | Quality impact, non-compliance | MISRA required rule violation, Missing traceability | Fix before phase gate |
| **Minor** | Style/documentation issue | Advisory rule violation, Missing comment | Fix in next revision |

### 7.3 Detection

- Identified during code reviews, design reviews, audits, testing, static analysis
- Logged in non-conformance tracking system (GitHub Issues with NCR- prefix)

### 7.4 Resolution

- Root cause analysis performed for all non-conformances
- Corrective actions implemented and verified
- Preventive actions identified to avoid recurrence
- Process improvements documented and implemented

### 7.5 Tracking

- All non-conformances tracked to closure with NCR-YYYY-NNN format
- Monthly quality metrics report to management
- Escalation to CCB for critical safety-related issues

---

## 8. Problem Reporting and Corrective Action

### 8.1 Problem Reporting Process

**Defect Tracking:**
- Tool: GitHub Issues
- All defects tracked with unique ID
- Priority assigned (P1-Critical, P2-High, P3-Medium, P4-Low)
- Status tracked (Open, In Progress, Resolved, Closed, Verified)

### 8.2 Corrective Action Request (CAR)

**When CAR Required:**
- Repeated NCRs (same root cause)
- Process failure identified
- Quality metrics not met
- Audit findings requiring process change

**CAR Process:**
1. Root cause analysis
2. Corrective action plan developed
3. QA Manager approves plan
4. Action implemented
5. Effectiveness verified
6. CAR closed

---

## 9. Traceability Management

### 9.1 Traceability Requirements

**SIL 3:** Traceability MANDATORY (100% bidirectional)

**Traceability Links:**
- System Requirements → Software Requirements
- Software Requirements → Architecture
- Architecture → Design
- Design → Source Code
- Source Code → Unit Tests
- Requirements → System Tests

### 9.2 Traceability Verification

**QA Responsibilities:**
- Verify RTM completeness at each phase gate
- Identify orphan requirements
- Identify untested requirements
- Report traceability gaps

**Tools:** Requirements Traceability Matrix (RTM) in CSV format

---

## 10. Tool Qualification

### 10.1 Tool Classification (EN 50128 Section 6.7)

**TCL 1 (Low confidence):** Errors unlikely to go undetected  
**TCL 2 (Medium confidence):** Errors may go undetected, tool output verified  
**TCL 3 (High confidence):** Errors likely undetected, generates safety code

### 10.2 Tools Requiring Qualification

**For SIL 3:**

| Tool | Version | TCL | Qualification Required | Status |
|------|---------|-----|----------------------|--------|
| gcc | Latest | TCL 1 | Usage validation | Planned |
| PC-lint Plus | Latest | TCL 2 | Supplier evidence + validation | Planned |
| Cppcheck | Latest | TCL 2 | Validation | Planned |
| gcov/lcov | Latest | TCL 2 | Usage validation | Planned |
| Clang Static Analyzer | Latest | TCL 2 | Validation | Planned |
| Lizard | Latest | TCL 1 | Usage validation | Planned |
| Unity/CUnit | Latest | TCL 1 | Usage validation | Planned |

**Qualification Evidence:** To be stored in `docs/tool-qualification/`

---

## 11. Quality Metrics

### 11.1 Requirement Metrics

**Metrics Collected:**
- Total requirements count (functional, safety, performance, interface)
- Requirements volatility (changes per phase)
- Requirements ambiguity score
- Requirements testability score

**Targets:**
- Requirements volatility: < 10% after SRS approval
- Ambiguity: 0 ambiguous requirements
- Testability: 100% testable

### 11.2 Design Metrics

**Metrics Collected:**
- Number of modules
- Average cyclomatic complexity
- Maximum cyclomatic complexity
- Module coupling/cohesion

**Targets:**
- Max CCN: ≤10 for SIL 3 (MANDATORY)
- Average CCN: ≤5 for SIL 3

### 11.3 Code Metrics

**Metrics Collected:**
- Lines of Code (LOC)
- Comment ratio
- MISRA C violations (mandatory, required, advisory)
- Static analysis warnings

**Targets:**
- Comment ratio: ≥20%
- MISRA mandatory violations: 0
- MISRA required violations: 0 (deviations justified)
- Cyclomatic complexity: ≤10 (MANDATORY)

### 11.4 Test Metrics

**Coverage Targets (EN 50128 Table A.21):**

| SIL Level | Statement | Branch | MC/DC (Condition) |
|-----------|-----------|--------|-------------------|
| 3 | **M** (100%) | **M** (100%) | **M** (100%) |

**M** = Mandatory

**Additional Test Metrics:**
- Test pass rate: 100%
- Defect density: < 2 defects per KLOC

### 11.5 Defect Metrics

**Metrics Collected:**
- Open defects (by severity)
- Defect closure rate
- Defect density (defects per KLOC)
- Defect age (average days open)

**Targets:**
- Critical defects: 0 open at phase gate
- Defect density: < 2 defects per KLOC

### 11.6 Process Metrics

**Metrics Collected:**
- Schedule adherence (planned vs actual phase completion)
- Defect detection rate (defects found per review/audit)
- Review effectiveness (defects found vs total defects)
- Non-conformance closure time
- Code review coverage (100% of code reviewed)

---

## 12. Training

### 12.1 QA Training Requirements

**QA Team Training:**
- EN 50128:2011 standard
- MISRA C:2012
- Static analysis tools (PC-lint, Cppcheck)
- Code review techniques
- Audit procedures

### 12.2 Development Team Training

**All Developers:**
- MISRA C:2012 coding standard
- Defensive programming
- Unit testing with Unity framework
- Configuration management
- Train door control domain knowledge

**Training Records:** To be maintained in `docs/training/`

---

## 13. References

1. EN 50128:2011 Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems
2. EN 50126-1:2017 Railway Applications - RAMS Part 1
3. EN 50126-2:2017 Railway Applications - RAMS Part 2
4. MISRA C:2012 Guidelines for the use of the C language in critical systems
5. IEC 61508:2010 Functional safety
6. ISO 9001:2015 Quality management systems
7. Software Configuration Management Plan (SCMP) - DOC-SCMP-2026-001
8. Software Verification Plan (SVP) - DOC-SVP-2026-001
9. Software Validation Plan (SVaP) - DOC-SVAP-2026-001
10. Software Requirements Specification (SRS) for train_door_control2 (to be developed)
11. Project Quality Plan for train_door_control2 (to be developed)

---

**END OF DOCUMENT**
