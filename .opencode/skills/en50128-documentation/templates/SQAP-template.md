# Software Quality Assurance Plan (SQAP) - Template

**Document Type:** Software Quality Assurance Plan  
**Template Version:** 1.0  
**Last Updated:** 2026-02-18  
**Compliance:** EN 50128:2011 Section 6.5, Table A.9  

---

## Instructions for Use

1. **Copy this template** to your project directory (e.g., `docs/plans/SQAP.md`)
2. **Fill in the standard header** using values from `DOCUMENT-HEADER-TEMPLATE.md`
3. **Replace all [placeholders]** with project-specific information
4. **Delete instruction sections** (like this one) before finalizing
5. **Follow SIL-specific requirements** noted in each section

---

# Software Quality Assurance Plan

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SQAP-[YYYY]-[NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, or 4] |
| **Author** | [QA Manager Name, QA Manager] |
| **Reviewer** | [Name, Role] |
| **Approver** | [Project Manager Name, Project Manager] |
| **Status** | [Draft \| Review \| Approved \| Baseline] |

---

## Document Control

| Version | Date | Author | Changes | Approval Status |
|---------|------|--------|---------|-----------------|
| 0.1 | [YYYY-MM-DD] | [Author Name] | Initial draft | Draft |

---

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (QA Manager)** | [Name] | | [YYYY-MM-DD] |
| **Reviewer** | [Name] | | [YYYY-MM-DD] |
| **Safety Manager** | [Name] | | [YYYY-MM-DD] |
| **Project Manager** | [Name] | | [YYYY-MM-DD] |

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

[Define the purpose of this SQAP. Example:]

This Software Quality Assurance Plan (SQAP) establishes the quality assurance processes, procedures, and activities for the [Project Name] to ensure compliance with EN 50128:2011 requirements for SIL [X] railway software development. This plan defines QA responsibilities, standards, review processes, and quality metrics necessary to deliver safe and reliable railway control software.

### 1.2 Scope

**Software Component:** [Component Name]  
**SIL Level:** [0, 1, 2, 3, or 4]  
**Development Phases:** [e.g., Requirements through Validation]  
**Programming Language:** C (MISRA C:2012 compliant for SIL 2+)  
**Target Platform:** [Hardware platform description]  

**QA Coverage:**
- Requirements quality assurance
- Design quality assurance
- Implementation quality assurance (code reviews, static analysis)
- Testing quality assurance
- Documentation quality assurance
- Process compliance audits

### 1.3 Applicable Standards

- EN 50128:2011 Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems
- EN 50126-1:2017 Railway Applications - RAMS (Part 1)
- EN 50126-2:2017 Railway Applications - RAMS (Part 2)
- MISRA C:2012 Guidelines for the use of the C language in critical systems (MANDATORY for SIL 2+)
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

---

## 2. Quality Objectives

### 2.1 Overall Quality Goals

**For SIL [X], the quality objectives are:**

1. **Correctness:** All software requirements implemented correctly with 100% traceability
2. **Reliability:** Software operates without failure under specified conditions
3. **Safety:** All safety requirements met with appropriate SIL level
4. **Maintainability:** Code is readable, modular, and well-documented
5. **Compliance:** Full compliance with EN 50128:2011 and MISRA C:2012

### 2.2 SIL-Specific Quality Objectives

**SIL [X] Requirements:**
- Code review coverage: [100% for all SIL levels]
- Static analysis: [Recommended for SIL 0-1, Highly Recommended for SIL 2, MANDATORY for SIL 3-4]
- MISRA C:2012 compliance: [MANDATORY for SIL 2+]
- Cyclomatic complexity: [≤20 for SIL 0-1, ≤15 for SIL 2, ≤10 for SIL 3-4]
- Test coverage: [See Section 11.3]

### 2.3 Quality Metrics Targets

[See Section 11 for detailed metrics]

---

## 3. Quality Organization

### 3.1 QA Team Structure

**QA Manager:** [Name]
- Overall quality oversight
- Audit approval
- Quality gate authorization
- Non-conformance escalation
- Reports to: [Safety Authority / Senior Management]

**QA Engineers:** [Names]
- Code reviews
- Design reviews
- Process audits
- Metrics collection
- Testing oversight

### 3.2 Independence Requirements

**SIL 0-2:**
- QA function recommended to be independent from development
- QA Manager reports to Project Manager

**SIL 3-4 (MANDATORY):**
- QA function MUST be independent from development team
- QA Manager reports directly to Safety Authority (NOT Project Manager)
- QA has authority to halt releases if quality criteria not met
- Independent verification and validation required

**Independence Verification:**
- [ ] QA team organizationally separate from development
- [ ] QA reports to [Safety Authority/Management] independent of PM
- [ ] QA authority documented in [Project Charter/Org Chart]

### 3.3 Roles and Responsibilities

**QA Manager:**
- Develop and maintain SQAP
- Conduct quality audits (PCA, FCA)
- Approve NCRs and CARs
- Authorize phase gate transitions
- Report quality metrics to management

**QA Engineers:**
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

**MISRA C:2012 (MANDATORY for SIL 2+):**
- All mandatory rules: 100% compliance
- All required rules: 100% compliance (deviations require justification)
- Advisory rules: Compliance recommended

**Project-Specific C Coding Guidelines:**
- Fixed-width integer types (uint8_t, uint16_t, uint32_t, etc.)
- Static allocation only (SIL 2+: NO malloc/calloc/realloc/free)
- No recursion (Highly Recommended for SIL 3-4)
- No function pointers (Highly Recommended for SIL 3-4)
- Explicit error handling (all return values checked)
- Defensive programming (all inputs validated)
- Consistent naming conventions: [Define conventions]

**Cyclomatic Complexity Limits:**
- SIL 0-1: CCN ≤ 20
- SIL 2: CCN ≤ 15
- SIL 3-4: CCN ≤ 10 (MANDATORY)

### 4.2 Documentation Standards

**EN 50128 Document Requirements (Annex C Table C.1):**
- All mandatory documents per SIL level
- Standard document header (see DOCUMENT-HEADER-TEMPLATE.md)
- Version control for all documents
- Traceability to requirements (MANDATORY for SIL 3-4)
- Review and approval signatures

**Document Templates:**
- Follow templates in `.opencode/skills/en50128-documentation/templates/`
- Template compliance verified by QA before approval

### 4.3 Process Standards

**EN 50128 V-Model Lifecycle:**
- Requirements → Design → Implementation → Testing → Validation
- Phase gates with quality criteria
- Independent verification and validation (SIL 3-4)

**Configuration Management:**
- MANDATORY for all SIL levels (EN 50128 Section 6.6)
- Version control (Git)
- Change control via CCB
- Baseline management

---

## 5. Quality Activities by Lifecycle Phase

### 5.1 Phase 1: Planning
- [ ] SQAP review and approval
- [ ] SCMP review and approval
- [ ] SVP review and approval
- [ ] SVaP review and approval
- [ ] Tool qualification plan review
- [ ] Quality standards defined

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
- [ ] Performance testing review (SIL 3-4)

### 5.6 Phase 6: Validation
- [ ] System test review
- [ ] Validation test review
- [ ] Coverage analysis review
- [ ] Traceability end-to-end verification

---

## 6. Reviews and Audits

### 6.1 Code Reviews

**Scope:** 100% of source code (MANDATORY for all SIL levels)

**Process:**
1. Developer submits code for review
2. QA Engineer performs review using checklist
3. Findings documented in review record
4. Developer addresses findings
5. QA Engineer verifies resolution

**Review Checklist:**
- [ ] MISRA C:2012 compliance
- [ ] Cyclomatic complexity within limits
- [ ] Defensive programming patterns
- [ ] Error handling complete
- [ ] Comments adequate
- [ ] Traceability to design

**Review Records:** Stored in `docs/reviews/code-reviews/`

### 6.2 Design Reviews

**Scope:** All design documents (SAS, SDS)

**Review Checklist:**
- [ ] Modular design (MANDATORY SIL 2+)
- [ ] Static allocation (SIL 2+)
- [ ] Interfaces fully defined
- [ ] Complexity budgets met
- [ ] Traceability to requirements

### 6.3 Document Reviews

**Scope:** All project deliverables

**Review Checklist:**
- [ ] Template compliance (DOCUMENT-HEADER-TEMPLATE.md)
- [ ] Technical accuracy
- [ ] Completeness
- [ ] Consistency with related documents
- [ ] EN 50128 compliance

### 6.4 Process Audits

**Frequency:**
- SIL 0-1: Annually
- SIL 2: Semi-annually
- SIL 3-4: Quarterly (MANDATORY)

**Audit Types:**
- Physical Configuration Audit (PCA): Before each baseline
- Functional Configuration Audit (FCA): Before each baseline
- Process compliance audit: Per schedule above

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

**NCR Template:** See `docs/quality/NCR-template.md`

### 7.2 Severity Levels

| Severity | Definition | Example | Action Required |
|----------|------------|---------|-----------------|
| **Critical** | Safety impact or EN 50128 violation | MISRA mandatory rule violation | Immediate fix, cannot proceed |
| **Major** | Quality impact, non-compliance | Complexity exceeds limit | Fix before phase gate |
| **Minor** | Style/documentation issue | Missing comment | Fix in next revision |

---

## 8. Problem Reporting and Corrective Action

### 8.1 Problem Reporting Process

**Defect Tracking:**
- Tool: [GitHub Issues / Jira / Bugzilla]
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

**SIL 0-2:** Traceability Highly Recommended
**SIL 3-4:** Traceability MANDATORY (100% bidirectional)

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

**Tools:** CSV/Excel RTM, or traceability tool

---

## 10. Tool Qualification

### 10.1 Tool Classification (EN 50128 Section 6.7)

**TCL 1 (Low confidence):** Errors unlikely to go undetected  
**TCL 2 (Medium confidence):** Errors may go undetected, tool output verified  
**TCL 3 (High confidence):** Errors likely undetected, generates safety code

### 10.2 Tools Requiring Qualification

**For SIL [X]:**

| Tool | Version | TCL | Qualification Required | Status |
|------|---------|-----|----------------------|--------|
| gcc | [Version] | TCL 1 | Usage validation | [Status] |
| PC-lint Plus | [Version] | TCL 2 | Supplier evidence + validation | [Status] |
| Cppcheck | [Version] | TCL 2 | Validation | [Status] |
| gcov | [Version] | TCL 2 | Usage validation | [Status] |

**Qualification Evidence:** Stored in `docs/tool-qualification/`

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
- Max CCN: ≤10 for SIL 3-4
- Average CCN: ≤5 for SIL 3-4

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

### 11.4 Test Metrics

**Coverage Targets (EN 50128 Table A.21):**

| SIL Level | Statement | Branch | MC/DC (Condition) |
|-----------|-----------|--------|-------------------|
| 0-1 | HR | HR | - |
| 2 | HR | **M** | - |
| 3-4 | **M** (100%) | **M** (100%) | **M** (100%) |

**M** = Mandatory, **HR** = Highly Recommended

**Additional Test Metrics:**
- Test pass rate: 100%
- Defect density: < [X] defects per KLOC

### 11.5 Defect Metrics

**Metrics Collected:**
- Open defects (by severity)
- Defect closure rate
- Defect density (defects per KLOC)
- Defect age (average days open)

**Targets:**
- Critical defects: 0 open at phase gate
- Defect density: < 2 defects per KLOC

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

**Training Records:** Maintained in `docs/training/`

---

## 13. References

1. EN 50128:2011 Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems
2. EN 50126-1:2017 Railway Applications - RAMS Part 1
3. EN 50126-2:2017 Railway Applications - RAMS Part 2
4. MISRA C:2012 Guidelines for the use of the C language in critical systems
5. IEC 61508:2010 Functional safety
6. ISO 9001:2015 Quality management systems
7. Software Configuration Management Plan (SCMP) - [Document ID]
8. Software Verification Plan (SVP) - [Document ID]
9. Software Validation Plan (SVaP) - [Document ID]

---

**END OF TEMPLATE**

**Next Steps:**
1. Fill in all [placeholders]
2. Delete instruction sections
3. Submit for review
4. Obtain required approvals
