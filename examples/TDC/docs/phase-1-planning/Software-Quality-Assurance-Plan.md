# Software Quality Assurance Plan (SQAP)

## Document Control

| Field | Value |
|-------|-------|
| **Document ID** | DOC-TDC-SQAP-001 |
| **Version** | 1.0 |
| **Date** | 2026-03-30 |
| **Status** | DRAFT |
| **Author** | QUA Team |
| **Project** | TDC (Train Door Control) |
| **SIL Level** | SIL 3 |
| **Standard** | EN 50128:2011 Railway Software Standard |

---

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| QA Manager (Author) | TBD — assigned at project kick-off | | |
| Independent Verifier (1st Check) | TBD — assigned at project kick-off | | |
| Independent Validator (2nd Check) | TBD — assigned at project kick-off | | |
| Project Manager | TBD — assigned at project kick-off | | |
| Safety Manager | TBD — assigned at project kick-off | | |

---

## Revision History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-03-30 | QUA Team | Initial SQAP for TDC project (SIL 3) |

---

## Table of Contents

1. [Purpose and Scope](#1-purpose-and-scope)
2. [References](#2-references)
3. [Definitions and Abbreviations](#3-definitions-and-abbreviations)
4. [Quality Organisation](#4-quality-organisation)
5. [Lifecycle Model and Quality Activities](#5-lifecycle-model-and-quality-activities)
6. [Document Quality Standards](#6-document-quality-standards)
7. [Code Quality Standards](#7-code-quality-standards)
8. [QUA Review Process](#8-qua-review-process)
9. [Coverage and Testing Requirements](#9-coverage-and-testing-requirements)
10. [Static Analysis Requirements](#10-static-analysis-requirements)
11. [Document Review Checklists](#11-document-review-checklists)
12. [Code Review Checklists](#12-code-review-checklists)
13. [Audit Schedule](#13-audit-schedule)
14. [Non-Conformance Management](#14-non-conformance-management)
15. [Metrics and Data Recording](#15-metrics-and-data-recording)
16. [SIL 3 Mandatory Techniques (EN 50128 Table A.9)](#16-sil-3-mandatory-techniques-en-50128-table-a9)
17. [Traceability](#17-traceability)
18. [Configuration Management](#18-configuration-management)
19. [Tools Qualification](#19-tools-qualification)
20. [Platform Deviations](#20-platform-deviations)
21. [SQAP Update Procedure](#21-sqap-update-procedure)

---

## 1. Purpose and Scope

### 1.1 Purpose

This Software Quality Assurance Plan (SQAP) defines the quality assurance approach, standards, processes, and activities for the **TDC (Train Door Control)** software development project. The plan is prepared in accordance with EN 50128:2011 Section 6.5 and is tailored for **SIL 3** safety integrity requirements.

The SQAP establishes:
- Quality organisation structure and independence requirements
- Quality standards for documentation and source code
- Review, verification, and validation processes
- Metrics collection and non-conformance management
- Compliance demonstration with EN 50128 Table A.9 mandatory techniques

### 1.2 Scope

This SQAP covers **all lifecycle phases (Phases 1–9)** of the TDC software development project:

| Phase | Name | Scope |
|-------|------|-------|
| Phase 1 | Planning | SQAP, SCMP, SVP, SVaP |
| Phase 2 | Requirements | SRS, Overall Test Spec, Hazard Log |
| Phase 3 | Architecture & Design | SAS, SDS, SIS, Integration Test Specs |
| Phase 4 | Component Design | Component Design & Test Specs |
| Phase 5 | Implementation & Testing | C source code (MISRA C:2012), unit tests |
| Phase 6 | Integration | SW integration, SW/HW integration testing |
| Phase 7 | Validation | System testing, validation, acceptance |
| Phase 8 | Assessment | Independent Safety Assessment (ISA) |
| Phase 9 | Deployment | Release package, deployment records |

**Note**: Phase 10 (Maintenance) is governed by a separate Software Maintenance Plan (item 41) and follows the change control procedures defined in the Software Configuration Management Plan (SCMP).

### 1.3 Relationship to Other Plans

This SQAP is supported by and references:
- **Software Configuration Management Plan (SCMP)** — configuration control, baselines, change management
- **Software Verification Plan (SVP)** — verification activities, static analysis, traceability
- **Software Validation Plan (SVaP)** — validation strategy, system testing, acceptance criteria
- **System Safety Plan** — system-level safety requirements and hazard management
- **System Safety Requirements Specification** — allocated safety requirements

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
| DOC-TDC-SCMP-001 | Software Configuration Management Plan | Phase 1 |
| DOC-TDC-SVP-001 | Software Verification Plan | Phase 1 |
| DOC-TDC-SVaP-001 | Software Validation Plan | Phase 1 |

---

## 3. Definitions and Abbreviations

### 3.1 Abbreviations

| Abbreviation | Definition |
|--------------|------------|
| ASR | Assessor (Independent Safety Assessor) |
| CCB | Change Control Board |
| CM | Configuration Manager |
| COD | Lifecycle Coordinator |
| DES | Designer |
| FMEA | Failure Modes and Effects Analysis |
| FTA | Fault Tree Analysis |
| HR | Highly Recommended (EN 50128 technique classification) |
| IMP | Implementer |
| INT | Integrator |
| ISA | Independent Safety Assessment |
| M | Mandatory (EN 50128 technique classification) |
| MC/DC | Modified Condition/Decision Coverage |
| MISRA | Motor Industry Software Reliability Association |
| NCR | Non-Conformance Report |
| PM | Project Manager |
| QUA | Quality Assurance Engineer |
| R | Recommended (EN 50128 technique classification) |
| REQ | Requirements Engineer |
| RTM | Requirements Traceability Matrix |
| SAF | Safety Engineer |
| SAS | Software Architecture Specification |
| SCMP | Software Configuration Management Plan |
| SDS | Software Design Specification |
| SIL | Safety Integrity Level |
| SIS | Software Interface Specifications |
| SQAP | Software Quality Assurance Plan (this document) |
| SRS | Software Requirements Specification |
| SVaP | Software Validation Plan |
| SVP | Software Verification Plan |
| TDC | Train Door Control (project name) |
| TST | Tester |
| VAL | Validator |
| VER | Verifier |
| VMGR | V&V Manager (Independent V&V Authority) |

### 3.2 Key Definitions

**Quality Assurance (QA)**: Systematic activities ensuring that software development processes comply with EN 50128 requirements and project standards.

**Format-Gate Check**: QUA review of deliverable structure and format compliance (Document ID, Document Control table, Approvals table, required sections) — **not technical content**.

**1-Pass Rule**: QUA template compliance policy for VER/VAL reports. If QUA rejects a report, the author may resubmit **once**. A second rejection constitutes a process failure requiring PM escalation.

**Template Compliance**: Document adherence to platform document structure standards, including mandatory sections, SIL allocation, and approval requirements.

**Technical Review**: Content correctness review performed by VER (1st Check) and VAL (2nd Check) — distinct from QUA format-gate check.

**Independence (SIL 3)**: Organizational separation requirement — VER, VAL, and VMGR SHALL NOT report to development roles or PM. They report to COD/Safety Authority.

---

## 4. Quality Organisation

### 4.1 Organisational Structure (SIL 3)

Per EN 50128:2011 §5.1.2.10, the TDC project operates under a **Strict Independence Organisation** with mandatory separation between development and V&V streams:

```
SAFETY AUTHORITY / CUSTOMER
        │
        ├─────────────────────────────────────┐
        │                                     │
        ▼                                     ▼
   COD (Lifecycle                    VMGR (Independent V&V Authority)
    Coordinator)                      ★ MANDATORY INDEPENDENT
        │                                     │
        │ authorizes phases                   │ coordinates V&V
        ▼                                     │
   PM (Project Manager)                       │
        │                                     │
        │ orchestrates                        │ manages
        ▼                                     ▼
┌──────────────────────┐            ┌─────────────────────┐
│  DEVELOPMENT TEAM    │            │    V&V TEAM         │
│  REQ, DES, IMP       │            │    VER, VAL         │
│  INT, TST, SAF       │            │    (Independent)    │
│  QUA, CM             │            │                     │
└──────────────────────┘            └─────────────────────┘
                                             │
                                             ▼
                                    ASR (Independent Safety
                                         Assessor)
```

### 4.2 Role Responsibilities

#### 4.2.1 Quality Assurance Engineer (QUA)

**Primary Responsibility**: Format-gate keeper for all deliverables; ensures template compliance before VER/VAL technical review.

**Key Activities**:
- Author the SQAP (this document) under VER direction (§6.5.4.3)
- Perform template compliance checks on all Annex C deliverables (items 1–44, excluding Phase 8 ASR documents)
- Apply 1-Pass Rule to VER/VAL reports
- Conduct process audits (monthly at SIL 3)
- Log and track Non-Conformance Reports (NCRs)
- Collect and report quality metrics
- Audit traceability evidence (verify VER checks were performed and recorded)

**QUA checks FORMAT only** — QUA does **NOT**:
- Review technical correctness of requirements, design, or code
- Check MISRA C compliance or cyclomatic complexity (VER duty)
- Verify traceability link completeness (VER duty)
- Assess test adequacy or coverage values (TST/VER duty)

**Reporting**: QUA reports to COD/PM. QUA is independent from DES, IMP, TST, and Software Manager.

**Independence Requirement**: Not normatively required by EN 50128 at any SIL (see §6.5, ORGANIZATION.md Independence Matrix). However, QUA SHALL NOT report to development roles to maintain process objectivity.

#### 4.2.2 Verifier (VER)

**Independence**: **MANDATORY at SIL 3** (§5.1.2.10(e–j), Table A.5 Technique T1).

**Responsibilities**:
- 1st Check of all development deliverables (technical content review)
- Static analysis (MISRA C, Cppcheck, Clang scan-build)
- Traceability verification (RTM completeness checks)
- Code review for defensive programming and SIL constraints
- Author SVP, Verification Reports per phase
- Report to VMGR (not PM)

#### 4.2.3 Validator (VAL)

**Independence**: **MANDATORY at SIL 3** (§5.1.2.10(f), Table A.7 Technique T1).

**Responsibilities**:
- 2nd Check of development deliverables
- System testing and acceptance testing
- Validation against System Requirements
- Author SVaP, Validation Report (Phase 7)
- Report to VMGR (not PM)

#### 4.2.4 V&V Manager (VMGR)

**Platform Role Notice**: VMGR is a platform-defined extension implementing EN 50128 §5.1.2.10(e–f). The VMGR construct assigns an independent Validator to coordinate Verifiers, implementing the "Verifier reports to Validator" option of §5.1.2.10(e).

**Independence**: **MANDATORY at SIL 3**. VMGR is organizationally independent from PM and the development team.

**Responsibilities**:
- Coordinate VER team activities
- Review all VER and VAL reports
- Provide final V&V decision (cannot be overridden by PM or COD)
- Coordinate with COD on lifecycle gate progression
- Escalate V&V blocking issues to Safety Authority

**Authority**: VMGR decisions on V&V adequacy are final and binding at SIL 3.

#### 4.2.5 Independent Safety Assessor (ASR)

**Independence**: **MANDATORY at SIL 3** (§6.4.1.1, §5.1.2.4–5.1.2.7).

**Responsibilities**:
- Independent assessment of all Phase 1–7 deliverables
- Author Software Assessment Plan and Software Assessment Report (Phase 8)
- Verify EN 50128 compliance across all phases
- Report directly to Safety Authority (not COD, PM, or VMGR)

**Phase 8 QUA Rule**: QUA has **NO** activity in Phase 8. ASR documents (items 45–46) are not subject to QUA template compliance checks.

---

## 5. Lifecycle Model and Quality Activities

### 5.1 V-Model Lifecycle

The TDC project follows the EN 50128:2011 V-Model lifecycle with 10 phases:

```
  [Phase 1] ──► [Phase 2] ──► [Phase 3] ──► [Phase 4] ──► [Phase 5]
   Planning    Requirements  Architecture  Component   Implementation
                                & Design     Design      & Testing
      │             │             │            │             │
      └─────────────┴─────────────┴────────────┴─────────────┘
                                  │
                                  ▼
                            [Phase 6]
                           Integration
                                  │
      ┌─────────────┬─────────────┴────────────┬─────────────┐
      │             │             │             │             │
      ▼             ▼             ▼             ▼             ▼
  [Phase 7]     [Phase 8]     [Phase 9]   [Phase 10]
  Validation   Assessment    Deployment  Maintenance
```

**Gate Authority**: COD enforces phase gate progression. No phase may begin without COD gate-check approval of the prior phase.

**Strict Gatekeeper Mode**: At SIL 3, COD operates in Strict Gatekeeper mode — **no override permitted**. All gate criteria must be satisfied.

### 5.2 QUA Activities Per Phase

#### Phase 1: Planning
- **QUA Authors SQAP** under VER direction (§6.5.4.3, deviation D8)
- Template compliance: Items 1–5 (SQAP, SQAVR, SCMP, SVP, SVaP)
- 1-Pass Rule applies to items 2, 4, 5 (VER/VAL-authored plans)

#### Phase 2: Requirements
- Template compliance: Items 6–8 (SRS, Overall Test Spec, Requirements VER Report)
- Traceability audit: Verify VER performed T1–T2 checks (SYS-REQ → SW-REQ)
- 1-Pass Rule applies to item 8 (Requirements VER Report)

#### Phase 3: Architecture & Design
- Template compliance: Items 9–14 (SAS, SDS, SIS, Integration Test Specs, Architecture VER Report)
- Traceability audit: Verify VER performed T3–T5c checks (SW-REQ → Architecture → Components)
- Process audit: FMEA/FTA evidence exists (SAF responsibility)
- 1-Pass Rule applies to item 14 (Architecture VER Report)

#### Phase 4: Component Design
- Template compliance: Items 15–17 (Component Design Spec, Component Test Spec, Component Design VER Report)
- Traceability audit: Verify VER performed T6, T11 checks
- 1-Pass Rule applies to item 17 (Component Design VER Report)

#### Phase 5: Implementation & Testing
- Template compliance: Items 18–20 (Source Code package, Source Code VER Report, Component Test Report)
- **Critical**: QUA checks source code package FORMAT only (Document ID, Document Control, package structure). VER performs actual code review (MISRA C, static analysis, cyclomatic complexity).
- Traceability audit: Verify VER performed T7, T12 checks (Components → Code → Unit Tests)
- QA process data recording (Table A.9 T8): Verify coverage reports, defect counts, complexity distributions exist and are under CM control
- 1-Pass Rule applies to item 19 (Source Code VER Report)

#### Phase 6: Integration
- Template compliance: Items 21–22 (Integration Test Reports)
- Traceability audit: Verify VER performed T10a, T10b, T12 checks

#### Phase 7: Validation
- Template compliance — Track A: Item 24 (Overall Test Report)
- Template compliance — Track B: Items 23, 25, 26, 27 (Integration VER Report, Validation Report, Tools Validation Report, Release Note)
- 1-Pass Rule applies to items 23, 25, 26 (VER/VAL reports)
- **Note**: This is the only phase where QUA checks VAL-authored formal Validation Reports

#### Phase 8: Assessment
- **QUA activity: NONE**
- ASR operates independently; items 45–46 are not subject to QUA checks

#### Phase 9: Deployment
- Template compliance: Items 36–40 (Release & Deployment Plan, Deployment Manual, Release Notes, Deployment Records, Deployment VER Report)
- 1-Pass Rule applies to item 40 (Deployment VER Report)

#### Phase 10: Maintenance (ongoing)
- Template compliance: Items 41–44 (Maintenance Plan, Change Records, Maintenance Records, Maintenance VER Report)
- Process audit: Verify CCB change control procedures followed
- Traceability impact audit: Verify downstream RTM links re-checked for each Change Request
- 1-Pass Rule applies to item 44 (Maintenance VER Report)

### 5.3 Cross-Cutting QUA Activities

**Process Audits**: Monthly at SIL 3 (MANDATORY per Table A.9 T8)

**Quality Metrics Collection**: Per phase at SIL 3 (MANDATORY per Table A.9 T8)

**Traceability Audits**: After each VER traceability check (SIL 3 MANDATORY per Table A.9 T6)

**Non-Conformance Management**: Continuous — NCRs logged and tracked to closure

---

## 6. Document Quality Standards

### 6.1 Document ID Format

**Mandatory Format**: `DOC-<PROJECT>-<TYPE>-<NNN>`

**Examples**:
- `DOC-TDC-SQAP-001` (this document)
- `DOC-TDC-SRS-001` (Software Requirements Specification)
- `DOC-TDC-SAS-001` (Software Architecture Specification)

**QUA Check Rule GF-001**: Every deliverable SHALL have a Document ID field in the Document Control table matching the regex:  
`DOC-[A-Z]+-[A-Z]+-[0-9]{3}`

Severity: **ERROR** — QUA SHALL reject deliverable if Document ID is missing or malformed.

### 6.2 Document Control Table

**Mandatory Fields**:
- Document ID
- Version
- Date (YYYY-MM-DD format)
- Author
- Status (DRAFT | IN REVIEW | APPROVED | BASELINE)

**QUA Check Rule GF-002**: All five fields SHALL be present and non-empty.

Severity: **ERROR** — QUA SHALL reject deliverable if any field is missing or empty.

### 6.3 Approvals Table

**Mandatory Columns**:
- Role
- Name
- Signature
- Date

**Required Roles (SIL 3)**:
- Author (document producer)
- Reviewer (QUA for Track A deliverables)
- Approver (PM for development deliverables)

**Additional Roles (context-dependent)**:
- Safety Manager (for safety-critical documents: SRS, SAS, SDS, Hazard Log, FMEA)
- VER (1st Check — listed after QUA review complete)
- VAL (2nd Check — listed after VER review complete, where applicable)

**QUA Check Rule GF-003**: Approvals table SHALL contain all required roles for the SIL level.

**Note on VER/VAL Sign-off**: VER and VAL are Track B roles. They review deliverables **after** QUA accepts them. The Approvals table lists Track A sign-off only (Author, Reviewer=QUA, Approver=PM). VER/VAL sign-off is recorded in their respective Verification/Validation Reports, not in the development deliverable's Approvals table.

Severity: **ERROR** — QUA SHALL reject deliverable if required roles are missing.

### 6.4 Required Sections Check

Every document type has a mandatory section structure defined in:
- `review-criteria/sections/<doc-key>-sections.yaml`

**QUA Check Rule GF-004**: All mandatory section headings SHALL be present in the document (case-insensitive match).

**Common Mandatory Sections** (all deliverables):
1. Document Control
2. Approvals
3. Revision History
4. Table of Contents
5. Purpose and Scope
6. References

**Document-Specific Sections**: Defined per Annex C item type (see Section 11 checklists).

Severity: **ERROR** — QUA SHALL list all missing sections in the QUA Review Report.

### 6.5 SIL Allocation Requirement

**SIL 3 Mandatory Rule**: All requirements, design elements, and test cases SHALL be assigned a SIL level.

**QUA Check**: QUA audits that a SIL allocation table or column exists in:
- SRS (software requirements)
- SAS/SDS (architecture/design elements)
- Test Specifications (test cases)

Severity: **WARNING** — QUA SHALL flag missing SIL allocation for PM review.

### 6.6 Normative Language Keywords

Documents SHALL use RFC 2119 keywords consistently:
- **SHALL** / **SHALL NOT** — mandatory requirement
- **SHOULD** / **SHOULD NOT** — recommendation (justification required if not followed)
- **MAY** — optional, permissive

**QUA Check**: QUA SHALL verify that normative requirements use "SHALL", not informal language like "must", "will", or "need to".

Severity: **WARNING** — QUA SHALL flag inconsistent keyword usage.

---

## 7. Code Quality Standards

### 7.1 Programming Language

**Language**: C (ISO/IEC 9899:2011, C11 standard)

**Coding Standard**: **MISRA C:2012** (including Amendment 2, 2020) — **MANDATORY at SIL 3** per EN 50128 Table A.4 Technique T2a.

### 7.2 MISRA C:2012 Compliance

**Mandatory Rule Compliance**: **ZERO violations of MISRA C:2012 mandatory rules** permitted.

**Advisory Rule Compliance**: Advisory rule deviations SHALL be documented with:
- Rule ID (e.g., Rule 2.3)
- Location (file, function, line number)
- Justification (technical reason for deviation)
- VER approval signature

**Required Rules Compliance**: Required rule deviations SHALL be treated as mandatory rules for SIL 3 — deviations require Safety Authority approval.

**Tool Support**:
- **Cppcheck** with MISRA C:2012 addon — primary checker
- **Clang Static Analyzer** (scan-build) — supplementary analysis

**Deviation Procedure**:
1. IMP documents deviation in source code (inline comment with deviation permit number)
2. Deviation recorded in MISRA Deviation Log (maintained by CM)
3. VER reviews and approves/rejects deviation
4. Safety Authority approves any Required rule deviations

### 7.3 Cyclomatic Complexity

**Maximum CCN (Cyclomatic Complexity Number)**: **≤ 10 per function** at SIL 3 (EN 50128 Table A.4 Technique T8).

**Tool**: Lizard (Python-based complexity analyzer)

**Measurement**: McCabe cyclomatic complexity (v(G) = edges - nodes + 2)

**Enforcement**: VER SHALL reject any function with CCN > 10. No deviations permitted at SIL 3.

**Refactoring Required**: Functions exceeding CCN 10 SHALL be refactored into smaller functions.

### 7.4 Defensive Programming (SIL 3 Mandatory)

Per EN 50128 Table A.4 Technique T13 (MANDATORY at SIL 3):

**Required Practices**:
1. **Input Validation**: All external inputs (sensors, communication) SHALL be validated before use
2. **Range Checks**: All arithmetic operations SHALL include overflow/underflow checks
3. **Pointer Validation**: All pointers SHALL be checked for NULL before dereferencing
4. **Array Bounds Checking**: All array accesses SHALL verify index within bounds
5. **Error Handling**: All function return values SHALL be checked; no silent failures
6. **Assertions**: Runtime assertions SHALL be used for invariant checking (enabled in debug builds)
7. **Fail-Safe Defaults**: Error conditions SHALL default to safe state (e.g., door locked, emergency stop)

**VER Review**: VER SHALL verify defensive programming practices in code review (item 19, Phase 5).

### 7.5 Prohibited Constructs (SIL 3)

The following constructs are **PROHIBITED** at SIL 3:

| Construct | Rationale | EN 50128 Reference |
|-----------|-----------|-------------------|
| Dynamic memory allocation (`malloc`, `calloc`, `realloc`, `free`) | Memory exhaustion risk; non-deterministic behavior | Table A.4 T2b (M) |
| Recursion | Stack overflow risk; unbounded execution time | Table A.4 T9 (HR → M for TDC) |
| Function pointers (except for state machines with static tables) | Control flow obfuscation; validation complexity | Table A.4 T10 (HR → M for TDC) |
| `goto` statements (except for single-exit error cleanup) | Unstructured control flow | Table A.4 T1 (M) |
| Variable-length arrays (VLAs) | Stack overflow risk | MISRA C:2012 Rule 18.8 |
| `setjmp` / `longjmp` | Non-local control flow | MISRA C:2012 Rule 21.4 |

**Tool Detection**: VER SHALL use Cppcheck and Clang scan-build to detect prohibited constructs.

### 7.6 Memory Safety

**Static Allocation Only**: All memory SHALL be allocated at compile time (global or stack).

**Stack Depth Analysis**: Maximum stack depth SHALL be analyzed and documented (tool: GCC `-fstack-usage`).

**Initialized Variables**: All variables SHALL be initialized at declaration (MISRA C Rule 9.1).

**No Dangling Pointers**: VER SHALL verify no pointers to stack variables escape function scope.

---

## 8. QUA Review Process

### 8.1 Review Workflow

```
   PM submits deliverable
          │
          ▼
   CM assigns Document ID, baseline
          │
          ▼
   QUA performs Format-Gate Check
   • Document ID format (GF-001)
   • Document Control table (GF-002)
   • Approvals table (GF-003)
   • Required sections (GF-004)
   • SIL allocation present
          │
          ├─────► PASS ──────► QUA writes QUA Review Report (PASS)
          │                    │
          │                    ▼
          │              PM routes to VER (Track A) or VMGR (Track B)
          │
          └─────► FAIL ──────► QUA writes QUA Review Report (FAIL + defect list)
                               │
                               ▼
                         PM returns to author for fix
                               │
                               ▼
                         [Iteration tracking]
                               │
                               ├─────► Iteration 1, 2 → resubmit to QUA
                               │
                               └─────► Iteration 3 → NCR raised, PM escalates
```

### 8.2 Iteration Limits

#### 8.2.1 Development Deliverables (Standard Iteration Limit)

**Applicable to**: Items 1, 3, 6–17, 18, 20–22, 24, 27, 36–39, 41–43

**Limit**: **3 iterations** (initial submission + 2 resubmissions)

**On 3rd Failure**:
1. QUA raises NCR against author (Severity: MAJOR)
2. QUA escalates to PM
3. PM assigns mandatory training intervention
4. Author must complete training before resubmission
5. NCR tracked to closure

**Rationale**: Repeated template failures indicate author training gap, not isolated error.

#### 8.2.2 VER/VAL Reports (1-Pass Rule)

**Applicable to**: Items 2, 4, 5, 8, 14, 17, 19, 23, 25, 26, 40, 44 (all VER/VAL-authored reports)

**Limit**: **1 resubmission** (initial submission + 1 resubmission)

**On 2nd Failure**:
1. QUA raises NCR (Severity: MAJOR)
2. QUA flags as **process failure** to PM and VMGR
3. PM escalates to VMGR (SIL 3) or Safety Manager (SIL 1–2)
4. Root cause analysis required
5. Training intervention mandatory
6. VMGR reviews corrective action before accepting next submission

**Rationale**: VER/VAL reports are produced by trained, independent personnel. Repeated template failures indicate process breakdown, not training gap.

### 8.3 QUA Review Report

**Document ID Format**: `QUA-REVIEW-TDC-YYYY-NNN`

**Mandatory Content**:
1. Document reviewed (Document ID, version, date)
2. Annex C item number
3. `qua_check_type`: `template_compliance` or `template_compliance_one_pass`
4. Iteration number (1, 2, or 3)
5. Check results:
   - GF-001 (Document ID format): PASS | FAIL
   - GF-002 (Document Control table): PASS | FAIL
   - GF-003 (Approvals table): PASS | FAIL
   - GF-004 (Required sections): PASS | FAIL + list of missing sections
6. Overall result: **PASS** | **FAIL**
7. Defect list (if FAIL): defect ID, rule, location, suggested fix
8. Disposition:
   - **PASS**: Approved for VER/VAL review; proceed to Track A or Track B
   - **FAIL**: Returned to author; iteration count incremented

**Archive**: All QUA Review Reports are baselined under CM control.

### 8.4 QUA Decision Authority

**QUA rejection is binding**: PM and development team CANNOT override QUA template compliance rejection.

**Escalation Path** (if dispute):
1. PM may escalate to COD
2. COD reviews QUA checklist application
3. If QUA correctly applied SQAP rules → rejection stands
4. If QUA misapplied rules → COD directs QUA to re-review with correct interpretation

**VMGR Authority**: VMGR reviews VER/VAL reports for technical content **after** QUA accepts format. VMGR cannot override QUA format rejection, but VMGR's technical content decision is final and binding.

---

## 9. Coverage and Testing Requirements

### 9.1 Coverage Metrics (SIL 3 Mandatory)

Per EN 50128 Table A.21 Requirement 2 (SIL 3: HR branch coverage + compound condition coverage **or** data flow coverage):

**Mandatory Targets**:

| Metric | Target | Rationale | Tool |
|--------|--------|-----------|------|
| Statement Coverage | **100%** | EN 50128 Table A.21 Req. 1 (M at all SILs) | gcov/lcov |
| Branch Coverage | **100%** | EN 50128 Table A.21 Req. 2 (HR at SIL 3) | gcov/lcov |
| Modified Condition/Decision Coverage (MC/DC) | **100%** | EN 50128 Table A.21 Req. 2 (HR at SIL 3) — TDC selects MC/DC over data flow | Custom analyzer (mcdc_analyzer.py) |

**Interpretation of Table A.21 "HR" for TDC**:
- EN 50128 Table A.21 Requirement 2 lists branch + compound condition coverage as "HR" (Highly Recommended), not "M" (Mandatory) at SIL 3.
- However, the TDC project adopts **100% MC/DC as project policy** to demonstrate stringent quality control.
- This exceeds the normative minimum and is documented as a **project-specific enhancement**.
- Justification: Train door control is a safety-critical function (failure modes include passenger injury). 100% coverage provides maximum confidence in test completeness.

**EN 50128 Threshold Note**:
- Table A.21 does **not** specify a numeric percentage threshold (e.g., "100%") for any coverage metric.
- The standard uses symbolic notations (M, HR, R) without quantitative targets.
- The 100% target is a **platform/project policy**, not an EN 50128 normative requirement.
- Rationale for 100% target: Safety-critical SIL 3 software demands maximum test rigor. Industry best practice for railway safety software.

### 9.2 Coverage Measurement Process

**Responsibility**: TST executes tests; VER verifies coverage; QUA audits evidence.

**Workflow**:
1. **TST** writes unit tests (Unity framework) targeting 100% coverage
2. **TST** executes tests with gcov instrumentation: `gcc -fprofile-arcs -ftest-coverage`
3. **TST** generates coverage report: `gcov *.gcda && lcov --capture --directory . --output-file coverage.info`
4. **TST** runs MC/DC analyzer: `python3 mcdc_analyzer.py --gcda-dir . --report mcdc_report.html`
5. **TST** produces Component Test Report (item 20) with coverage summary
6. **VER** reviews coverage reports, verifies 100% target met
7. **VER** records verification in Source Code Verification Report (item 19)
8. **QUA** audits that coverage reports exist, are under CM control, and VER verified them (QUA does NOT independently re-verify coverage values)

**Coverage Deficiency Handling**:
- Any function/branch/condition with <100% coverage SHALL be justified in Component Test Report
- Justification categories: defensive code (unreachable), hardware-dependent (simulated), exception handling (fault injection required)
- VER SHALL review and approve all coverage justifications
- Uncovered code with no valid justification → VER rejects item 19 → PM returns to TST/IMP for additional tests

### 9.3 Test Framework

**Unit Testing**: Unity test framework (C-based, lightweight, suitable for embedded)

**Integration Testing**: System-level test harness (TBD per Integration Plan, item 36)

**Test Automation**: All tests SHALL be automated and repeatable via CI pipeline

**Test Data Management**: Test input data and expected results SHALL be version-controlled alongside test code

---

## 10. Static Analysis Requirements

### 10.1 Mandatory Static Analysis Tools (SIL 3)

Per EN 50128 Table A.5 Technique T16 (M at SIL 3):

| Tool | Purpose | Frequency | Responsible |
|------|---------|-----------|-------------|
| **Cppcheck** (with MISRA addon) | MISRA C:2012 compliance, coding standards | Every code commit | IMP (pre-commit), VER (gate check) |
| **Clang Static Analyzer** (scan-build) | Memory safety, undefined behavior, null dereference | Every code commit | IMP (pre-commit), VER (gate check) |
| **Lizard** | Cyclomatic complexity (CCN ≤ 10) | Every code commit | IMP (pre-commit), VER (gate check) |
| **GCC/Clang warnings** | Compiler diagnostics (`-Wall -Wextra -Werror`) | Every build | IMP (continuous) |

**Tool Qualification**: Tools used for compliance demonstration (Cppcheck MISRA addon) SHALL be qualified per EN 50128 Section 6.7. See Tools Validation Report (item 26).

### 10.2 Cppcheck Configuration (MISRA C:2012)

**Command**:
```bash
cppcheck --addon=misra \
  --suppressions-list=misra_suppressions.txt \
  --enable=all --inconclusive \
  --error-exitcode=1 \
  --template='{file}:{line}: {severity} ({id}): {message}' \
  src/
```

**Mandatory Rules**: Zero violations permitted. Build SHALL fail on any mandatory rule violation.

**Required/Advisory Rules**: Deviations tracked in `misra_suppressions.txt` with justifications.

**Inline Suppressions**: Permitted only with deviation permit number:
```c
// Deviation Permit: DP-TDC-2026-042 (Rule 11.3 — cast required for hardware register access)
uint32_t* door_status_reg = (uint32_t*)0x40001000; // cppcheck-suppress misra-c2012-11.3
```

### 10.3 Clang Static Analyzer Configuration

**Command**:
```bash
scan-build -o static-analysis-reports \
  --status-bugs \
  -enable-checker nullability.NullableDereferenced \
  -enable-checker security.insecureAPI \
  make clean all
```

**Zero Defects Policy**: scan-build SHALL exit with code 0 (no bugs found). Any defect blocks VER approval.

**Report Archive**: HTML reports stored in `static-analysis-reports/` under CM control.

### 10.4 Lizard Complexity Check

**Command**:
```bash
lizard -l c -C 10 -w src/ > complexity_report.txt
```

**CCN Threshold**: 10 (SIL 3 mandatory)

**Gate Block**: Any function with CCN > 10 blocks VER approval of item 19 (Source Code VER Report).

**Refactoring Required**: Functions SHALL be decomposed until CCN ≤ 10.

### 10.5 QUA Role in Static Analysis

**QUA audits evidence, does NOT run tools**:
- QUA verifies static analysis reports exist in CM baseline
- QUA verifies VER reviewed and signed off on static analysis results
- QUA verifies zero MISRA mandatory violations documented in VER report
- QUA verifies CCN ≤ 10 documented in VER report

**QUA does NOT**:
- Run Cppcheck, Clang, or Lizard independently
- Interpret static analysis findings
- Approve/reject code based on static analysis results (VER responsibility)

---

## 11. Document Review Checklists

### 11.1 Generic Format Checklist (All Deliverables)

**QUA SHALL verify** (Rules GF-001 to GF-004):

- [ ] **GF-001**: Document ID present and matches format `DOC-TDC-<TYPE>-<NNN>`
- [ ] **GF-002**: Document Control table present with all fields (Document ID, Version, Date, Author, Status)
- [ ] **GF-003**: Approvals table present with required roles (Author, Reviewer, Approver)
- [ ] **GF-004**: All mandatory sections present (see document-specific checklist)
- [ ] **GF-005**: Revision History table present
- [ ] **GF-006**: Table of Contents present (for documents >5 pages)
- [ ] **GF-007**: References section lists all cited documents with Document IDs
- [ ] **GF-008**: Normative keywords (SHALL, SHOULD, MAY) used consistently

### 11.2 Software Requirements Specification (SRS, Item 6)

**Additional Sections Required**:
- [ ] System Context and Boundaries
- [ ] Functional Requirements (with SIL allocation)
- [ ] Safety Requirements (with SIL allocation)
- [ ] Performance Requirements
- [ ] Interface Requirements
- [ ] Traceability to System Requirements (forward traceability matrix)
- [ ] Requirements Verification Criteria

**SIL 3 Specific**:
- [ ] Every requirement tagged with SIL level (0, 1, 2, or 3)
- [ ] Safety requirements explicitly identified and justified

**QUA Notes**:
- QUA checks section presence and SIL allocation table existence
- VER checks requirement technical correctness and traceability link completeness (T1–T2)

### 11.3 Software Architecture Specification (SAS, Item 9)

**Additional Sections Required**:
- [ ] Architectural Design Principles
- [ ] System Decomposition (components, modules)
- [ ] Interface Definitions
- [ ] Concurrency Model (if applicable)
- [ ] Safety Architecture (fail-safe mechanisms, redundancy)
- [ ] Traceability to SRS (T3 — Requirements → Architecture)

**SIL 3 Specific**:
- [ ] Every component tagged with allocated SIL level
- [ ] Freedom from interference analysis (if mixed-SIL components)

### 11.4 Source Code Package (Item 18)

**QUA checks FORMAT only** (not code content):

- [ ] Package manifest / index section present
- [ ] File listing with Document IDs assigned
- [ ] Directory structure documented
- [ ] Build instructions provided
- [ ] Compiler version and flags documented

**QUA does NOT check** (VER responsibility):
- MISRA C compliance
- Cyclomatic complexity
- Coding style
- Logic correctness

### 11.5 Verification Reports (Items 2, 8, 14, 17, 19, 23, 40, 44)

**1-Pass Rule applies**

**Additional Sections Required**:
- [ ] Verification Scope (deliverables reviewed)
- [ ] Verification Activities Performed (per SVP)
- [ ] Findings and Observations (defects, non-conformances)
- [ ] Traceability Verification Results (T1–T15 as applicable)
- [ ] Static Analysis Results (Phase 5 — item 19 only)
- [ ] Overall Verification Verdict (PASS | CONDITIONAL PASS | FAIL)

**SIL 3 Specific**:
- [ ] VER signatory independent from development team (organizational independence verified)

### 11.6 Validation Reports (Items 25, 26)

**1-Pass Rule applies**

**Additional Sections Required**:
- [ ] Validation Scope (system-level requirements validated)
- [ ] Test Execution Summary (test cases executed, pass/fail counts)
- [ ] Test Coverage Analysis (T14 — SW-REQ → Test Cases)
- [ ] Acceptance Criteria Verification
- [ ] Overall Validation Verdict (PASS | CONDITIONAL PASS | FAIL)

**SIL 3 Specific**:
- [ ] VAL signatory independent from development team (organizational independence verified)

---

## 12. Code Review Checklists

**Responsible Role**: VER (not QUA)

QUA provides this checklist to VER as reference. VER records code review findings in Source Code Verification Report (item 19). QUA verifies VER performed the review and documented results.

### 12.1 MISRA C:2012 Key Rules (VER Checklist)

**Mandatory Rules (Zero Violations)**:
- [ ] **Rule 1.3**: No undefined behavior
- [ ] **Rule 2.1**: No unreachable code
- [ ] **Rule 8.4**: Identifiers with external linkage declared in header
- [ ] **Rule 9.1**: Variables initialized before use
- [ ] **Rule 14.3**: No invariant Boolean conditions (e.g., `if (true)`)
- [ ] **Rule 21.3**: No use of `malloc`, `calloc`, `realloc`, `free`
- [ ] **Rule 21.4**: No use of `setjmp`, `longjmp`
- [ ] **Rule 21.6**: No use of standard I/O (`printf`, `scanf`) in production code

**Required Rules (Deviations require justification)**:
- [ ] **Rule 8.2**: Function prototypes with named parameters
- [ ] **Rule 8.13**: Pointer parameters that do not modify data declared `const`
- [ ] **Rule 10.1**: Operands of bitwise operators are unsigned
- [ ] **Rule 11.3**: Cast between pointer and integer only for hardware addresses
- [ ] **Rule 17.7**: Return value of non-void function checked

### 12.2 Defensive Programming Checklist (VER)

**Input Validation**:
- [ ] All sensor inputs range-checked before use
- [ ] All communication inputs validated (CRC, sequence number)
- [ ] All function parameters validated (NULL check, range check)

**Pointer Safety**:
- [ ] All pointers checked for NULL before dereference
- [ ] No pointer arithmetic on NULL pointers
- [ ] Array bounds checked before indexing

**Arithmetic Safety**:
- [ ] Integer overflow/underflow checked (especially in safety-critical calculations)
- [ ] Division by zero prevented
- [ ] Type promotions reviewed for unintended sign extension

**Error Handling**:
- [ ] All function return codes checked
- [ ] Error conditions propagated to caller or logged
- [ ] No silent failures

**Fail-Safe Defaults**:
- [ ] Error conditions default to safe state (door locked, movement inhibited)
- [ ] Watchdog timer configured and serviced
- [ ] Timeout handling for all blocking operations

### 12.3 Prohibited Constructs Checklist (VER)

- [ ] No `malloc`, `calloc`, `realloc`, `free` (dynamic memory allocation)
- [ ] No recursion (direct or indirect)
- [ ] No function pointers (except static state machine tables approved by Safety Manager)
- [ ] No `goto` (except single-exit error cleanup approved by VER)
- [ ] No variable-length arrays (VLAs)
- [ ] No `setjmp` / `longjmp`

### 12.4 Complexity Checklist (VER)

- [ ] All functions have CCN ≤ 10 (verified by Lizard)
- [ ] Functions >50 lines refactored into smaller units (guideline, not hard rule)
- [ ] Deeply nested code (>4 levels) refactored for readability

---

## 13. Audit Schedule

### 13.1 Process Audits (SIL 3 Mandatory)

**Frequency**: **Monthly** (EN 50128 Table A.9 T8 — Data Recording and Analysis, M at SIL 3)

**Scope**:
- Verify EN 50128 lifecycle process compliance
- Audit that evidence exists for all mandatory activities (FMEA, FTA, traceability, static analysis, coverage)
- Review NCR trends and corrective actions
- Verify CM baseline integrity
- Check that VER independence is maintained

**Output**: Process Audit Report (tracked by QUA, reviewed by PM and VMGR)

**Responsible**: QUA

**QUA Audit Checklist**:
- [ ] SQAP, SCMP, SVP, SVaP issued and under CM control
- [ ] All deliverables baselined per SCMP
- [ ] VER independence maintained (no reporting to development roles)
- [ ] VAL independence maintained (no reporting to PM)
- [ ] Traceability evidence exists for completed phases (RTM baselined, VER reviewed)
- [ ] Static analysis reports exist and show zero MISRA mandatory violations
- [ ] Coverage reports exist and show 100% targets met (or justified deviations)
- [ ] FMEA/FTA evidence exists (SAF-produced, VER-reviewed)
- [ ] NCRs tracked and closed within phase gate
- [ ] Tools qualified per EN 50128 Section 6.7 (if used for compliance demonstration)

### 13.2 Traceability Audits (SIL 3 Mandatory)

**Frequency**: **After each VER traceability check** (Phases 2, 3, 4, 5, 6, 7)

**Scope**:
- Verify VER performed traceability checks per SVP (T1–T15)
- Verify traceability evidence is recorded in RTM and baselined
- Verify no orphaned requirements (upstream link missing)
- Verify no orphaned design/code (downstream link missing)

**Output**: Traceability Audit Report

**Responsible**: QUA (audits evidence); VER (performs traceability checks)

**QUA does NOT**:
- Re-check traceability links independently (VER responsibility)
- Verify technical correctness of links (VER responsibility)

**QUA DOES**:
- Verify RTM exists and is baselined
- Verify VER signed off on RTM completeness
- Verify T1–T15 evidence recorded per phase

### 13.3 Quality Metrics Review (SIL 3 Mandatory)

**Frequency**: **Per phase gate** (EN 50128 Table A.9 T7 — Metrics, R at SIL 3; T8 — Data Recording, M at SIL 3)

**Scope**:
- NCR count by phase, severity, type
- Gate pass/fail rates by phase
- QUA review iterations (1st submission PASS rate)
- Open NCR age distribution
- Coverage trend (statement, branch, MC/DC) across modules
- MISRA deviation count and trend
- Complexity distribution (CCN histogram)

**Output**: Quality Metrics Report

**Responsible**: QUA

**Metrics Thresholds** (guideline — not hard gate criteria):
- 1st submission PASS rate >80% (indicates good process maturity)
- Open NCRs <5 at any time (indicates prompt resolution)
- MISRA mandatory violations = 0 (hard gate criterion)
- CCN ≤ 10 for all functions (hard gate criterion)
- Coverage = 100% statement, branch, MC/DC (hard gate criterion)

---

## 14. Non-Conformance Management

### 14.1 NCR Process

**Definition**: A Non-Conformance Report (NCR) is a formal record of a deviation from EN 50128 requirements, project standards, or process compliance.

**Authority**: QUA raises NCRs; PM assigns resolution owner; COD reviews closure.

**NCR Workflow**:
1. **Detection**: QUA identifies non-conformance during review, audit, or metrics analysis
2. **Logging**: QUA creates NCR with unique ID `NCR-TDC-YYYY-NNN`
3. **Severity Assignment**: QUA assigns severity (MINOR | MAJOR | CRITICAL)
4. **Owner Assignment**: PM assigns resolution owner (typically document author or process owner)
5. **Resolution**: Owner proposes corrective action
6. **Review**: QUA reviews corrective action
7. **Closure**: QUA closes NCR after verification; PM approves
8. **Gate Check**: COD verifies all CRITICAL NCRs closed before phase gate

### 14.2 NCR Severity Levels

| Severity | Definition | Examples | Gate Impact |
|----------|------------|----------|-------------|
| **CRITICAL** | Violates EN 50128 mandatory requirement; blocks safety case | MISRA mandatory violation; missing traceability link; VER not independent | **HARD BLOCK** — COD SHALL NOT pass gate with open CRITICAL NCR |
| **MAJOR** | Violates project standard; significant rework required | Missing required section; 3rd QUA review failure; CCN > 10 in function | Waiver requires PM approval; COD may escalate |
| **MINOR** | Formatting issue; editorial error; low-impact deviation | Typo in document; missing date in Approvals table; inconsistent keyword usage | PM may waive; closure at next convenient milestone |

### 14.3 NCR Fields

**NCR ID**: `NCR-TDC-YYYY-NNN` (sequential numbering)

**Mandatory Fields**:
- **Phase**: Phase number where NCR raised
- **Annex C Item** (if deliverable-related): Item number (1–46)
- **Type**: `format_defect` | `process_defect` | `evidence_missing` | `standards_violation` | `traceability_gap`
- **Severity**: `MINOR` | `MAJOR` | `CRITICAL`
- **Description**: Clear statement of the non-conformance
- **Detection Method**: How NCR was found (QUA review, process audit, traceability audit, metrics analysis)
- **Owner**: Role/agent responsible for resolution
- **Due Date**: Target closure (typically next phase gate)
- **Status**: `OPEN` | `IN PROGRESS` | `RESOLVED` | `VERIFIED` | `CLOSED` | `WAIVED`
- **Corrective Action**: Proposed fix
- **Waiver Authority**: PM (MINOR/MAJOR) | COD (CRITICAL) | Safety Authority (SIL constraints)

### 14.4 NCR Tracking

**NCR Register**: Maintained by QUA in `NCR-Register-TDC.md` under CM control.

**NCR Review Cadence**:
- **Daily**: QUA monitors CRITICAL NCRs
- **Weekly**: PM reviews MAJOR NCRs with owners
- **Monthly**: QUA reports NCR trends in Quality Metrics Report
- **Per Phase Gate**: COD reviews NCR register; blocks gate if CRITICAL NCRs open

**Escalation Path**:
- CRITICAL NCR open >7 days → QUA escalates to PM
- CRITICAL NCR open >14 days → PM escalates to COD
- CRITICAL NCR open >30 days → COD escalates to Safety Authority

---

## 15. Metrics and Data Recording

### 15.1 Mandatory Metrics (SIL 3)

Per EN 50128 Table A.9 T8 (Data Recording and Analysis — **MANDATORY** at SIL 3):

**Collected Metrics**:

| Metric | Frequency | Source | Responsible |
|--------|-----------|--------|-------------|
| NCR count by severity | Per phase | NCR Register | QUA |
| NCR closure time (days) | Per phase | NCR Register | QUA |
| QUA review iterations | Per deliverable | QUA Review Reports | QUA |
| 1st submission PASS rate | Per phase | QUA Review Reports | QUA |
| Gate pass/fail by phase | Per gate | COD gate-check logs | COD |
| MISRA violation count (by rule) | Per commit | Cppcheck reports | VER |
| MISRA deviation count | Per phase | MISRA Deviation Log | VER |
| Cyclomatic complexity distribution | Per module | Lizard reports | VER |
| Statement coverage | Per module | gcov/lcov reports | TST |
| Branch coverage | Per module | gcov/lcov reports | TST |
| MC/DC coverage | Per module | mcdc_analyzer.py reports | TST |
| Defect density (defects per KLOC) | Per phase | VER defect logs | VER |
| Requirements volatility (% changed) | Per phase | RTM change logs | REQ |
| Test execution pass rate | Per test cycle | Test reports | TST |

### 15.2 Metrics Reporting

**Quality Metrics Report** produced by QUA at each phase gate:

**Report ID**: `DOC-TDC-METRICSR-<PHASE>-001`

**Contents**:
1. NCR summary (count by severity, age distribution)
2. QUA review iteration summary (1st pass rate trend)
3. Gate pass/fail history
4. MISRA compliance summary (deviation count, violation trend)
5. Complexity summary (CCN distribution, outliers)
6. Coverage summary (statement, branch, MC/DC by module)
7. Defect density trend (by phase)
8. Requirements stability (change rate by phase)
9. Trend analysis and recommendations

**Audience**: PM (immediate action), VMGR (V&V oversight), COD (gate decision support), Safety Authority (audit trail)

### 15.3 Data Recording Infrastructure

**Storage**: All metrics data stored in `metrics/` directory under CM control.

**Format**: CSV and JSON for machine processing; HTML for human review.

**Retention**: All metrics data retained for project lifetime + 10 years per EN 50128 Section 9.3.

**Tool Support**:
- `workspace.py wf metrics` — query metrics database
- `workspace.py wf report` — generate Quality Metrics Report
- `workspace.py wf ncr` — manage NCR register

---

## 16. SIL 3 Mandatory Techniques (EN 50128 Table A.9)

This section maps EN 50128 Table A.9 QA techniques to TDC project implementation.

| # | Technique | SIL 3 | TDC Implementation |
|---|-----------|-------|--------------------|
| **T1** | EN ISO 9001 accreditation | HR | Organization accreditation status: [TBD per Safety Authority requirement] |
| **T2** | EN ISO 9001 compliance | **M** | This SQAP and SCMP establish ISO 9001-compliant quality management system |
| **T3** | EN ISO 9001 certification | HR | Organization certification status: [TBD per Safety Authority requirement] |
| **T4** | Company Quality System | **M** | This SQAP + SCMP + SVP + SVaP constitute the Company Quality System for TDC project |
| **T5** | Software Configuration Management | **M** | Implemented per SCMP (item 3); CM role assigned; baseline management enforced |
| **T6** | Traceability | **M** | RTM maintained; VER checks T1–T15; QUA audits traceability evidence (Section 17) |
| **T7** | Metrics | R | Quality Metrics Report per phase gate (Section 15); exceeds normative minimum |
| **T8** | Data Recording and Analysis | **M** | Metrics collected per Section 15.1; monthly process audits per Section 13.1 |

**Justifications** (per §4.7):
- **T1/T3 (ISO 9001 accreditation/certification)**: HR at SIL 3. Status: [TBD]. If organization lacks certification, justification: This SQAP, SCMP, SVP, SVaP provide equivalent documented quality management system per EN 50128 requirements. Independent Assessment (Phase 8) verifies adequacy.
- **T7 (Metrics)**: R (Recommended) at SIL 3, but T8 (Data Recording) is M (Mandatory). TDC implements T7 fully (Quality Metrics Report per phase) to support T8 obligation. Industry best practice for SIL 3 projects.

**Table A.9 Deviation Notes**: None. All M and HR techniques implemented. R techniques implemented as best practice.

---

## 17. Traceability

### 17.1 Traceability Strategy

**Objective**: Demonstrate 100% bidirectional traceability from System Requirements through Validation (T1–T15 per `TRACEABILITY.md`).

**Traceability Chain**:
```
System Requirements (SYS-REQ)
    ↕ T1, T2
Software Requirements (SW-REQ)
    ↕ T3, T4a, T4b
Architecture (Components)
    ↕ T5a, T5b, T5c
Design (Modules, Functions)
    ↕ T6, T7
Source Code (Functions, Units)
    ↕ T12
Unit Tests (Test Cases)
    ↕ T10a, T10b
Integration Tests
    ↕ T13
Validation Tests
    ↕ T14, T15
```

**Responsibility**:
- **REQ**: Establish T1, T2 (SYS-REQ → SW-REQ) in SRS
- **DES**: Establish T3–T5 (SW-REQ → Architecture → Components) in SAS/SDS
- **IMP**: Establish T6, T7 (Components → Code) in source code comments
- **TST**: Establish T12 (Code → Unit Tests), T10 (Components → Integration Tests), T14 (SW-REQ → Validation Tests) in test specifications
- **VER**: Verify traceability completeness; check T1–T15; record in Verification Reports
- **QUA**: Audit that VER performed traceability checks and evidence is baselined

### 17.2 Traceability Tool

**Tool**: Requirements Traceability Matrix (RTM) — `Requirements-Traceability-Matrix.md`

**Format**: Markdown table with columns:
- SYS-REQ-ID
- SW-REQ-ID (T1 forward)
- Component-ID (T3 forward)
- Function-ID (T6 forward)
- Test-Case-ID (T12, T14 forward)
- Verification Status (VER sign-off)

**Example**:
```markdown
| SYS-REQ-ID | SW-REQ-ID | Component-ID | Function-ID | Test-Case-ID | VER Status |
|------------|-----------|--------------|-------------|--------------|------------|
| SYS-REQ-005 | SW-REQ-042 | COMP-DOOR-CTRL | door_lock() | UT-DOOR-042 | ✓ VER PASS |
```

**Automation Support**: `workspace.py trace` commands (per `en50128-lifecycle-tool-integration` skill).

### 17.3 Traceability Verification (VER)

**VER Checks** (per phase):
- **Phase 2**: T1, T2 (100% SYS-REQ covered by SW-REQ; 100% SW-REQ trace to SYS-REQ)
- **Phase 3**: T3, T4a, T4b, T5a, T5b, T5c (100% SW-REQ covered by architecture; 100% architecture trace to SW-REQ)
- **Phase 4**: T6 (100% components covered by design)
- **Phase 5**: T7, T12 (100% design implemented in code; 100% code covered by unit tests)
- **Phase 6**: T10a, T10b (100% components covered by integration tests)
- **Phase 7**: T13, T14, T15 (100% SW-REQ covered by validation tests; 100% system tested)

**Output**: VER records traceability check results in Verification Reports (items 8, 14, 17, 19, 23).

### 17.4 Traceability Audit (QUA)

**QUA Audit** (per phase, after VER check):
- [ ] RTM exists and is baselined under CM control
- [ ] VER signed off on RTM completeness (Verification Report item)
- [ ] T1–T15 evidence recorded (as applicable to phase)
- [ ] No orphaned requirements flagged (upstream link missing)
- [ ] No orphaned code flagged (downstream link missing)

**QUA does NOT**:
- Re-check traceability links independently
- Verify link technical correctness
- Approve/reject RTM content (VER responsibility)

**Output**: Traceability Audit Report (per phase gate).

---

## 18. Configuration Management

### 18.1 CM Authority

**Configuration Management** is governed by the **Software Configuration Management Plan (SCMP)**, item 3.

**Responsible Role**: CM (Configuration Manager)

**QUA Interface with CM**:
- QUA verifies all deliverables are baselined per SCMP before gate check
- QUA verifies all QUA Review Reports are archived under CM control
- QUA audits CM baseline integrity in monthly process audits

### 18.2 Baseline Definition

**Baselines** (per SCMP):
- **Planning Baseline** (Phase 1 gate): Items 1–5 (SQAP, SCMP, SVP, SVaP, SQAVR)
- **Requirements Baseline** (Phase 2 gate): Items 6–8 (SRS, Overall Test Spec, Requirements VER Report)
- **Design Baseline** (Phase 3 gate): Items 9–14 (SAS, SDS, SIS, Integration Test Specs, Architecture VER Report)
- **Code Baseline** (Phase 5 gate): Items 18–20 (Source Code, Source Code VER Report, Component Test Report)
- **Integration Baseline** (Phase 6 gate): Items 21–23 (Integration Test Reports, Integration VER Report)
- **Validation Baseline** (Phase 7 gate): Items 24–27 (Validation Reports, Release Note)
- **Release Baseline** (Phase 9 gate): Items 36–40 (Deployment package, Deployment VER Report)

**Baseline Freeze**: After COD gate-check PASS, the baseline is frozen. All subsequent changes require CCB approval (Change Request process per SCMP).

### 18.3 Change Control

**Change Control Board (CCB)**: Chaired by PM; members: REQ, DES, SAF, VER, CM, QUA.

**Change Request (CR) Process**:
1. CR submitted to CCB (any role may submit)
2. CCB evaluates impact (scope, schedule, safety, traceability)
3. CCB approves/rejects CR
4. If approved: CM updates baseline; PM re-executes affected phases; VER re-verifies traceability
5. QUA audits CR process compliance in monthly process audit

**QUA Role in Change Control**:
- QUA is a CCB member (advisory, not decision-making)
- QUA audits that CCB minutes are documented and baselined
- QUA tracks CR-related NCRs (e.g., traceability not updated after CR)

### 18.4 Document Versioning

**Versioning Scheme**: `<MAJOR>.<MINOR>` (e.g., 1.0, 1.1, 2.0)

**Major Version Increment**: Baseline change (post-gate approval)

**Minor Version Increment**: Editorial correction, clarification (no technical change)

**Revision History**: Every document SHALL include Revision History table listing:
- Version
- Date
- Author
- Changes summary

---

## 19. Tools Qualification

### 19.1 Tool Classification (EN 50128 Section 6.7)

**Tool Classes**:
- **T1**: Generates outputs that are part of the safety software (e.g., compiler, linker)
- **T2**: Verifies outputs that are part of the safety software (e.g., static analyzers used for compliance demonstration)
- **T3**: Supports development but does not generate or verify safety software (e.g., editors, IDEs)

**Qualification Requirement** (§6.7.4.3):
- **T1 tools**: Full qualification required (validation against known-good test cases)
- **T2 tools**: Qualification required if used for compliance demonstration (e.g., Cppcheck MISRA addon for SIL 3 compliance)
- **T3 tools**: No qualification required

### 19.2 TDC Project Tool List

| Tool | Version | Purpose | Class | Qualification Required | Status |
|------|---------|---------|-------|------------------------|--------|
| GCC | 11.3.0 | C compiler | T1 | Yes | TBD per SVP |
| GNU Linker (ld) | 2.38 | Linker | T1 | Yes | TBD per SVP |
| gcov/lcov | 11.3.0 / 1.16 | Coverage measurement | T2 | Yes (compliance demo) | TBD per SVP |
| Cppcheck | 2.10 (MISRA addon) | MISRA C checker | T2 | Yes (compliance demo) | TBD per SVP |
| Clang Static Analyzer | 15.0.0 | Static analysis | T2 | Yes (compliance demo) | TBD per SVP |
| Lizard | 1.17.10 | Complexity analyzer | T2 | Yes (compliance demo) | TBD per SVP |
| Unity | 2.5.2 | Unit test framework | T3 | No | N/A |
| Make | 4.3 | Build automation | T3 | No | N/A |
| Git | 2.39.2 | Version control | T3 | No | N/A |

**Tool Qualification Plan**: Defined in SVP (item 4). VER responsible for tool qualification activities.

**Tool Validation Report**: Item 26, Phase 7. VAL verifies tool qualification evidence.

### 19.3 Tool Qualification Evidence

**For T1/T2 tools**, VER SHALL produce:
- Tool version and configuration documentation
- Known-good test suite execution results
- Comparison with reference tool (if available)
- Failure mode analysis (what happens if tool produces incorrect output?)
- Mitigation (e.g., cross-check with alternative tool, manual review sample)

**QUA Role**: QUA audits that tool qualification evidence exists and is baselined (item 26). QUA does NOT perform tool qualification.

---

## 20. Platform Deviations

This section documents platform deviations from EN 50128:2011 Annex C informative guidance, per SQAP obligation to track deviations (§6.5.4.5 item 4).

### 20.1 Deviation Summary

| Deviation ID | Annex C Item | Description | Justification | Impact | Safety Authority Approval |
|--------------|--------------|-------------|---------------|--------|---------------------------|
| **D1** | Item 5 (SVaP) | Platform places SVaP in Phase 1 (Planning); Annex C Table C.1 places it in Phase 2 (Requirements) | §6.3.4.3 requires SVaP early; validation criteria must be established before requirements elaboration | Earlier validation planning; no safety impact | TBD at project kick-off |
| **D8** | Item 1 (SQAP) | QUA authors SQAP under VER direction (§6.5.4.3); QUA cannot 2nd-check its own document | Self-certification conflict; VER performs 1st check; deviation documented in this SQAP | VER 1st-check replaces QUA self-review; VAL 2nd-check retained; no safety impact | TBD at project kick-off |

**Additional Deviations** (tracked in SCMP and SVP):
- **D2, D3, D4, D5, D6, D7**: See SCMP item 3 for CM-related deviations
- **Item 20 phase assignment**: See DELIVERABLES.md Note 5 (platform assigns item 20 to Phase 5; Annex C assigns to Integration phase)

**Safety Authority Review**: All deviations documented in this SQAP SHALL be reviewed and approved by the Safety Authority before Phase 1 gate.

---

## 21. SQAP Update Procedure

### 21.1 Update Trigger

This SQAP SHALL be updated when:
- Safety Authority directs a change
- COD approves a lifecycle process change
- CCB approves a Change Request affecting QA process
- Non-conformance trend analysis indicates process improvement opportunity
- Phase 8 ISA Assessment recommends SQAP update

### 21.2 Update Responsibility

**Owner**: QUA (under VER direction per §6.5.4.3)

**Approval**: VER (1st Check), VAL (2nd Check), PM (management approval), Safety Authority (final approval for SIL 3)

### 21.3 Update Frequency

**Minimum**: Once per major phase transition (if process changes required)

**Best Practice**: Review SQAP at each phase gate; update if needed

**Reactive**: Within 14 days of Change Request approval affecting QA process

### 21.4 Update Process

1. QUA drafts SQAP update (revision number incremented)
2. QUA documents changes in Revision History table
3. QUA submits to VER for 1st Check
4. VER reviews technical correctness (Verification Report produced)
5. VAL performs 2nd Check (if applicable per DELIVERABLES.md)
6. PM approves for project use
7. CM baselines updated SQAP
8. Safety Authority reviews and approves (SIL 3 requirement)
9. QUA notifies all agents of SQAP update

### 21.5 Version Control

**Current Version**: 1.0 (2026-03-30)

**Next Planned Update**: Phase 2 gate (after Requirements phase; assess if SRS experience reveals process gaps)

**Superseded Versions**: Archived under CM control; retained for audit trail

---

## 22. SQAP Compliance Verification

### 22.1 SQAP Self-Assessment

**Frequency**: Per phase gate

**Responsible**: QUA

**Method**: QUA SHALL verify that all SQAP-defined activities were performed in the completed phase:
- [ ] All deliverables subjected to QUA format-gate check
- [ ] All QUA Review Reports archived under CM control
- [ ] All NCRs logged and tracked
- [ ] Process audit conducted (if scheduled)
- [ ] Traceability audit conducted (if applicable)
- [ ] Quality Metrics Report produced (per phase)

**Output**: SQAP Compliance Checklist (included in Quality Metrics Report)

### 22.2 VER Review of SQAP Compliance

**Responsibility**: VER (independent review)

**Method**: VER SHALL verify QUA compliance with this SQAP in each Verification Report:
- [ ] QUA performed all format-gate checks per Section 8
- [ ] QUA applied correct iteration limits (3 for dev deliverables; 1-Pass Rule for VER/VAL reports)
- [ ] QUA raised NCRs for non-conformances
- [ ] QUA produced required audit reports and metrics reports

**Output**: VER documents SQAP compliance findings in Verification Reports (items 8, 14, 17, 19, 23)

### 22.3 VMGR Review of SQAP Effectiveness

**Responsibility**: VMGR (independent V&V authority)

**Method**: VMGR SHALL assess SQAP effectiveness at Phase 7 gate:
- Quality Metrics trends (NCR rate, 1st-pass rate, defect density)
- Process audit findings and corrective actions
- Comparison with industry benchmarks (if available)
- Recommendation for SQAP improvements

**Output**: VMGR includes SQAP effectiveness assessment in final V&V approval to COD

---

## 23. Glossary

(See Section 3 for Definitions and Abbreviations)

---

## 24. Appendices

### Appendix A: QUA Review Report Template

**Document ID**: `QUA-REVIEW-TDC-YYYY-NNN`

**Template Structure**:
```markdown
# QUA Review Report

## Document Control
- QUA Review ID: QUA-REVIEW-TDC-YYYY-NNN
- Date: YYYY-MM-DD
- Reviewer: [QUA name]
- Deliverable Reviewed: [Document ID, version]
- Annex C Item: [item number]
- qua_check_type: [template_compliance | template_compliance_one_pass]
- Iteration: [1 | 2 | 3]

## Review Results
- GF-001 (Document ID format): [PASS | FAIL]
- GF-002 (Document Control table): [PASS | FAIL]
- GF-003 (Approvals table): [PASS | FAIL]
- GF-004 (Required sections): [PASS | FAIL]
  - Missing sections: [list if FAIL]

## Overall Result
[PASS | FAIL]

## Defect List
[If FAIL, list all defects with ID, rule, location, suggested fix]

## Disposition
[Approved for VER/VAL review | Returned to author for correction]

## QUA Signature
[Name, date]
```

### Appendix B: NCR Template

**NCR ID**: `NCR-TDC-YYYY-NNN`

**Template Structure**:
```markdown
# Non-Conformance Report

## NCR Control
- NCR ID: NCR-TDC-YYYY-NNN
- Date Raised: YYYY-MM-DD
- Raised By: QUA

## Classification
- Phase: [phase number]
- Annex C Item: [item number, if applicable]
- Type: [format_defect | process_defect | evidence_missing | standards_violation | traceability_gap]
- Severity: [MINOR | MAJOR | CRITICAL]

## Description
[Clear statement of the non-conformance]

## Detection Method
[QUA review | Process audit | Traceability audit | Metrics analysis]

## Owner
[Role/agent responsible for resolution]

## Due Date
[Target closure date]

## Status
[OPEN | IN PROGRESS | RESOLVED | VERIFIED | CLOSED | WAIVED]

## Corrective Action
[Proposed fix]

## Waiver Authority
[PM | COD | Safety Authority]

## Closure Verification
[QUA signature, date]
```

### Appendix C: Quality Metrics Report Template

**Document ID**: `DOC-TDC-METRICSR-<PHASE>-001`

**Template Structure**:
```markdown
# Quality Metrics Report — Phase [N]

## Document Control
[Standard Document Control table]

## Summary
- Phase: [phase number]
- Reporting Period: [start date] to [end date]
- Deliverables Reviewed: [count]
- NCRs Raised: [count]

## NCR Summary
[Table: NCR count by severity, age distribution]

## QUA Review Summary
[Table: Iteration count, 1st-pass rate]

## Gate History
[Table: Phase, gate result, date]

## MISRA Compliance
[Table: Deviation count, violation trend]

## Complexity Summary
[Table: CCN distribution, outliers]

## Coverage Summary
[Table: Statement, branch, MC/DC by module]

## Defect Density
[Table: Defects per KLOC by phase]

## Trend Analysis
[Narrative: trends, recommendations]

## QUA Signature
[Name, date]
```

---

## End of Document

**Document ID**: DOC-TDC-SQAP-001  
**Version**: 1.0  
**Date**: 2026-03-30  
**Status**: DRAFT  

**Approval Pending**: VER 1st Check, VAL 2nd Check, PM Approval, Safety Authority Approval

---

**QUA Note to PM**: This SQAP is now ready for VER 1st Check (item 2, Software Quality Assurance Verification Report). Per deviation D8, QUA cannot 2nd-check its own plan. VER will perform 1st check; VAL will perform 2nd check.
