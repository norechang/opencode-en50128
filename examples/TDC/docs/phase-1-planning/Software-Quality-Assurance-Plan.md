# Software Quality Assurance Plan (SQAP)

**DOCUMENT TYPE**: Software Quality Assurance Plan  
**EN 50128 DELIVERABLE**: Annex C Item 1  
**STANDARD REFERENCE**: EN 50128:2011 Section 6.5  
**PROJECT**: TDC (Train Door Control System)  
**SIL LEVEL**: 3

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SQAP-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Quality Assurance Engineer (QUA) |
| **Status** | DRAFT — Awaiting VER 1st Check |

---

## VERSION HISTORY

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-04-02 | QUA | Initial SQAP draft for SIL 3 | - |
| 1.0 | 2026-04-02 | QUA | Baseline version for Phase 1 | [Pending VER] |

---

## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (QUA)** | [QUA Name] | [PENDING] | [PENDING] |
| **1st Check (VER)** | [VER Name] | [PENDING] | [PENDING] |
| **2nd Check (VAL)** | [VAL Name] | [PENDING] | [PENDING] |
| **Approver (PM)** | [PM Name] | [PENDING] | [PENDING] |

**Note**: Per deviation D8 (DELIVERABLES.md), QUA authors the SQAP under VER direction and responsibility (§6.5.4.3). QUA cannot perform the 2nd check on its own document due to self-certification conflict. VER performs 1st check; VAL performs 2nd check.

---

## INTRODUCTION

### Purpose

This Software Quality Assurance Plan (SQAP) defines the quality management strategy, organization, processes, techniques, and measures for the Train Door Control System (TDC) software development lifecycle. This plan establishes the framework for achieving and demonstrating software quality compliance with EN 50128:2011 at Safety Integrity Level 3 (SIL 3).

**Normative Basis**: EN 50128:2011 §6.5.4.3 mandates: "A Software Quality Assurance Plan shall be written, under the responsibility of the Verifier."

This SQAP governs all software quality activities from Phase 1 (Planning) through Phase 10 (Maintenance) and ensures compliance with:
- EN 50128:2011 Railway Software Standard (SIL 3)
- EN 50126-1:2017 RAMS Part 1 (Generic RAMS process)
- EN 50126-2:2017 RAMS Part 2 (Systems approach to safety)
- EN 50129:2018 Safety-related electronic systems for signalling
- ISO 9001:2015 Quality management systems

### Scope

This SQAP applies to all software development, verification, validation, integration, deployment, and maintenance activities for the TDC Software at SIL 3. The plan covers:

1. **Software Quality Organization** — roles, responsibilities, independence requirements
2. **Lifecycle Model** — V-Model phases, activities, entry/exit criteria, inputs/outputs
3. **Documentation Structure** — document hierarchy, templates, control procedures
4. **Quality Activities by Phase** — specific QA tasks for each lifecycle phase
5. **Reviews and Audits** — review types, schedules, criteria, checklists
6. **Methods, Measures and Tools** — QA techniques per EN 50128 Table A.9, SIL 3
7. **Traceability Management** — traceability approach, tools, verification (MANDATORY SIL 3)
8. **Non-Conformance Management** — NCR tracking, deviation management, corrective action
9. **Quality Metrics** — metrics collection, analysis, reporting (MANDATORY SIL 3)
10. **Training** — QA training requirements for SIL 3

**Out of Scope**: Hardware quality assurance (covered by System Quality Plan); system-level RAMS activities (covered by System Safety Plan DOC-SYS-PLAN-2026-001).

### Applicable Standards

This SQAP is compliant with:

| Standard | Title | Application |
|----------|-------|-------------|
| **EN 50128:2011** | Railway Software Standard | Software quality requirements (SIL 3) |
| **EN 50126-1:2017** | RAMS - Part 1 | Overall RAMS framework |
| **EN 50126-2:2017** | RAMS - Part 2 | Safety process and risk assessment |
| **ISO 9001:2015** | Quality Management Systems | Quality system compliance (MANDATORY SIL 3) |
| **ISO/IEC 90003:2014** | Software engineering guidelines for ISO 9001 | Software-specific quality guidance |
| **MISRA C:2012** | C Coding Standard | Mandatory coding standard for SIL 3 |

### References

This SQAP references the following project documents:

| Document ID | Document Name | Annex C Item |
|-------------|---------------|--------------|
| DOC-SCMP-2026-001 | Software Configuration Management Plan | 3 |
| DOC-SVP-2026-001 | Software Verification Plan | 4 |
| DOC-SVaP-2026-001 | Software Validation Plan | 5 |
| DOC-SYS-PLAN-2026-001 | System Safety Plan | N/A (System-level) |
| DOC-SYS-SAF-2026-001 | System Safety Requirements Specification | N/A (System-level) |

### Platform Deviations

This project adopts the following platform deviations from EN 50128:2011 Annex C Table C.1. All deviations are documented in `DELIVERABLES.md` and subject to Safety Authority review:

| Deviation ID | Description | Justification | Impact |
|--------------|-------------|---------------|--------|
| **D1** | SVaP (item 5) placed in Phase 1 (Planning), not Phase 2 (Requirements) per Annex C | §6.3.4.3 requires SVaP on the basis of input documents; §5.3.2.4 requires validation planning before relevant lifecycle phase | Early validation criteria establishment |
| **D2** | Software Component Test Report (item 20) placed in Phase 5 (Implementation & Testing), not Integration per Annex C | §7.5.4.5 normative output; integration testing requires prior unit test completion | Logical phase dependency |
| **D3** | Deployment Verification Report (item 40) placed in Phase 9 (Deployment), not Maintenance per Annex C | §9.1 normative deployment clause; deployment must be verified before maintenance begins | Logical phase dependency |
| **D4** | Maintenance Verification Report (item 44) placed in Phase 10 (Maintenance), not Assessment per Annex C | §9.2 normative maintenance clause; maintenance activities generate the verification report | Logical phase dependency |
| **D5** | Planning documents (items 1–5) MANDATORY at all SIL | Normative override: §5.3.2.4, §6.2.4.2, §6.3.4.2, §6.5.4.3, §6.6.4.1 impose "shall" obligations | Annex C "HR" overridden by normative clauses |
| **D6** | Software Source Code Verification Report (item 19) has VAL 2nd check (blank in Annex C) | Platform addition for SIL 3 enhanced rigor | Additional independent review |
| **D7** | Software Validation Verification Report (Phase 7, no Annex C item number) | Normatively required by §6.3.4.12–14; Annex C does not assign item number | Explicit platform tracking as item † |
| **D8** | SQAP authored by QUA under VER direction; QUA cannot 2nd-check own plan | §6.5.4.3 assigns responsibility to VER; self-certification conflict | VER 1st-checks; VAL 2nd-checks; deviation documented in SQAP Section 2.1 |

**Safety Authority Approval**: All deviations D1–D8 are subject to Safety Authority review and approval per project Safety Plan.

---

## 1. QUALITY ORGANIZATION

### 1.1 Quality Assurance Function

**Role**: Quality Assurance Engineer (QUA)

**Responsibility**: QUA is the **FORMAT gate-keeper** in the EN 50128 V-Model lifecycle. QUA sits between deliverable production and PM→COD handoff on every phase (Track A). QUA also checks VER and VAL report FORMAT before VMGR reviews technical content (Track B).

**QUA Authority** (SIL 3):
- QUA has final authority to ACCEPT or REJECT deliverables for format compliance
- QUA decisions CANNOT be overridden by development team (DES, IMP, TST) or Software Manager
- QUA reports to COD/PM directly — NOT to DES, IMP, TST, or Software Manager
- QUA raises Non-Conformance Reports (NCRs) against format/process defects
- QUA conducts process audits monthly (MANDATORY SIL 3)

**Independence**: QUA SHALL NOT report to DES, IMP, TST, or Software Manager. QUA reports to COD/PM. At SIL 3, QUA is a documented independent function (platform governance policy; EN 50128:2011 does not define a normative QUA independence requirement — see ORGANIZATION.md Independence Reference Matrix).

**Deviation D8 — SQAP Self-Certification Conflict**:
- QUA authors the SQAP (item 1) under VER direction and responsibility per §6.5.4.3
- QUA CANNOT perform the 2nd check on its own plan (self-certification conflict)
- VER performs 1st check; VAL performs 2nd check
- This deviation is documented here per §6.5.4.5(d) requirement

### 1.2 Software Quality Assurance Plan Ownership

**Written By**: QUA (under VER direction, deviation D8)  
**1st Check**: VER (independent verification)  
**2nd Check**: VAL (independent validation)  
**Approver**: PM  
**VMGR Review**: VMGR reviews VER's 1st Check report (SQAVR, item 2) before final approval

### 1.3 QUA Capabilities

QUA provides five capabilities across the lifecycle:

| Capability | Description | SIL 3 Obligation | Output |
|------------|-------------|------------------|--------|
| **1. Format-Gate Deliverable** | Check Document ID, Document Control, Approvals, Required Sections | MANDATORY (all deliverables except items 45–46) | QUA Review Report |
| **2. Author SQAP** | Draft Software Quality Assurance Plan under VER direction | MANDATORY (§6.5.4.3) | This document (item 1) |
| **3. Process Audit** | Verify EN 50128 lifecycle process adherence; audit evidence existence | MANDATORY monthly (SIL 3) | Process Audit Report |
| **4. Log Non-Conformance** | Raise NCR against deliverable or process finding; track to closure | MANDATORY (SIL 3) | Non-Conformance Report |
| **5. Metrics Report** | Collect and report QA process data per SQAP | MANDATORY per phase (SIL 3) | Quality Metrics Report |

### 1.4 QUA Checks — Four Things Only

QUA checks FORMAT on every deliverable — nothing else:

| Check | What QUA Covers | What QUA Does NOT Cover |
|-------|-----------------|------------------------|
| **Document ID format** | `DOC-[ABBREV]-[YYYY]-[NNN]` regex match | Technical correctness of requirements, design, or code |
| **Document Control table** | Version, Date, Author, Status fields present | MISRA C compliance, cyclomatic complexity, static analysis results |
| **Approvals table** | Correct roles for SIL level present and signed | Traceability link completeness (VER checks T1–T15) |
| **Required sections** | Document-type-specific mandatory section headings present | Test adequacy or coverage figures |

Technical content review is VER's responsibility (1st Check column, DELIVERABLES.md). QUA audits that VER evidence *exists* (process audit capability) — QUA does not independently re-execute VER checks.

### 1.5 Role Assignments

| Role | Agent | Independence Required (SIL 3) | Reports To | Authority |
|------|-------|------------------------------|-----------|-----------|
| **QUA** | Quality Assurance Engineer | Yes (platform policy) | COD/PM | Format gate; NCR; process audit |
| **VER** | Verifier | MANDATORY (§5.1.2.10e) | VMGR | 1st Check; technical verification |
| **VAL** | Validator | MANDATORY (§5.1.2.10f) | VMGR | 2nd Check; technical validation |
| **VMGR** | V&V Manager | MANDATORY (independent from COD/PM) | Safety Authority | Final V&V decision (cannot be overridden) |
| **PM** | Project Manager | No | COD | Team coordination; resource mgmt |
| **CM** | Configuration Manager | No | PM | Version control; baselines; change control |
| **COD** | Lifecycle Coordinator | No | Safety Authority / Customer | Phase gates; lifecycle state; compliance |
| **DES** | Designer | No | PM | Architecture and design |
| **IMP** | Implementer | No | PM | Code implementation |
| **TST** | Tester | Highly Recommended (SIL 3) | PM | Software testing |
| **INT** | Integrator | No | PM | Software integration |
| **SAF** | Safety Engineer | No | PM | Hazard analysis; safety case |
| **REQ** | Requirements Engineer | No | PM | Requirements specification |
| **ASR** | Assessor | MANDATORY (§6.4.1.1 SIL 1–4) | Safety Authority (external) | Independent safety assessment |

**Role Combination Rules** (SIL 3):
- **Prohibited**: Designer/Implementer + Verifier; any development role + Validator; any role + Assessor; Implementer + Tester (own code)
- **Allowed**: Software Manager + Designer; Designer + Implementer; Integrator + Tester

**Independence Evidence**: Organization chart demonstrating independence of VER, VAL, VMGR, and QUA from development team shall be maintained in `docs/organization/org-chart.pdf` and reviewed quarterly.

### 1.6 QUA Touchpoints on Annex C Deliverables

QUA has a touchpoint on **37 of 46 Annex C deliverables** (all except items 45–46 ASR documents and Section 8 generic platform items 28–35).

**QUA Check Types**:
- `[QUA]` — Standard template compliance check (max 3 iterations before PM escalation)
- `[QUA-VER]` — QUA checks VER report (**1-Pass Rule**: 1 resubmission; 2nd rejection = process failure)
- `[QUA-VAL]` — QUA checks VAL report (**1-Pass Rule**: Phase 7 only)
- `[—]` — No QUA check (items 45–46: ASR documents fully independent)

**Summary** (from `tasks/QUALITY_PROCESS.md` Diagram 2):
- Items with standard QUA check: 23
- Items with 1-Pass Rule (VER/VAL reports): 14
- Items with no QUA check (ASR): 2
- **Total in scope**: 37 items

**Phase 8 Rule**: QUA has ZERO activity in Phase 8 (Assessment). QUA MUST NOT review, check, or comment on items 45 (Software Assessment Plan) or 46 (Software Assessment Report). The ASR (Assessor) is fully independent from the project AND supplier (§5.1.2.5–5.1.2.7).

---

## 2. LIFECYCLE MODEL

### 2.1 V-Model Overview

The TDC Software follows the EN 50128:2011 V-Model lifecycle with 10 phases:

```
Phase 0: Initialization (System documents generated by COD)
Phase 1: Planning (SQAP, SCMP, SVP, SVaP)
Phase 2: Requirements (SRS, Overall Test Spec) ─────────────────┐
Phase 3: Architecture & Design (SAS, SDS, Interface Specs) ──┐  │
Phase 4: Component Design (Component Design, Component Test) │  │
Phase 5: Implementation & Testing (Code, Unit Tests) ◄────┘  │  │
Phase 6: Integration (Integration Testing) ◄────────────────┘  │
Phase 7: Validation (System Testing, Acceptance Testing) ◄──────┘
Phase 8: Assessment (Independent Safety Assessment)
Phase 9: Deployment (Release and Deployment)
Phase 10: Maintenance (Ongoing — triggered by CCB Change Requests)
```

Each phase has:
- **Entry Criteria**: prerequisites from prior phases
- **Activities**: tasks performed by agents (REQ, DES, IMP, TST, INT, VER, VAL, QUA, CM, SAF)
- **Deliverables**: documents per Annex C Table C.1
- **Exit Criteria**: phase gate requirements (COD gate-check)

### 2.2 Lifecycle Phases and QUA Activities

| Phase | Name | Deliverables | QUA Activities | Gate Authority |
|-------|------|--------------|----------------|----------------|
| **0** | Initialization | System docs (4) | NONE (COD generates; QUA not yet instantiated) | N/A |
| **1** | Planning | Items 1–5 | SQAP authorship; template compliance on all 5 items | COD |
| **2** | Requirements | Items 6–8 | Template compliance; traceability audit (T1–T2, SIL 3) | COD |
| **3** | Architecture & Design | Items 9–14 | Template compliance; traceability audit (T3–T5c, SIL 3) | COD |
| **4** | Component Design | Items 15–17 | Template compliance; traceability audit (T6, T11, SIL 3) | COD |
| **5** | Implementation & Testing | Items 18–20 | Template compliance; evidence audit (MISRA, coverage); QA process data (T8, SIL 3) | COD |
| **6** | Integration | Items 21–22 | Template compliance; traceability audit (T10a, T10b, T12, SIL 3) | COD |
| **7** | Validation | Items 23–27 | Template compliance on VER/VAL reports (1-Pass Rule); Track B checks | COD |
| **8** | Assessment | Items 45–46 | **ZERO ACTIVITY** (ASR fully independent; no QUA role) | COD |
| **9** | Deployment | Items 36–40 | Template compliance; deployment records audit | COD |
| **10** | Maintenance | Items 41–44 | Template compliance; CCB change control audit; traceability impact audit (SIL 3) | COD |

### 2.3 Entry and Exit Criteria

**Phase 1 Entry Criteria**:
- Phase 0 complete (system documents generated and reviewed)
- Project initialized at SIL 3 (LIFECYCLE_STATE.md)
- COD authorizes Phase 1 start

**Phase 1 Exit Criteria** (COD gate-check requirements):
- All 5 planning documents (items 1–5) QUA-PASSED
- VER 1st-check complete on items 1, 3 (SQAP, SCMP)
- VER-authored items 2, 4 (SQAVR, SVP) QUA-PASSED
- VAL-authored item 5 (SVaP) QUA-PASSED
- VAL 2nd-check complete on items 1–5
- VMGR review complete on items 2, 4, 5 (VER/VAL reports) — SIL 3 requirement
- Zero CRITICAL NCRs open
- All items baselined under CM control (SCMP in effect)
- COD gate-check: `@cod gate-check planning`

**Subsequent Phases**: Entry/exit criteria are defined in `LIFECYCLE.md` and enforced by COD at each gate.

### 2.4 Two-Track Workflow

The TDC Software lifecycle operates on **two parallel tracks**:

**Track A — Development** (PM orchestrates):
1. PM invokes development agents (REQ, DES, IMP, INT, TST, SAF, CM)
2. Development agents produce deliverables
3. **QUA template check** (MANDATORY gate before PM→COD handoff)
4. On PASS: PM marks deliverable QUA-ACCEPTED; on FAIL: PM returns to author (max 3 iterations)
5. All phase deliverables QUA-ACCEPTED → PM reports Track A complete to COD

**Track B — Independent V&V** (COD coordinates; VMGR manages at SIL 3):
1. COD receives Track A complete from PM
2. COD → VMGR: "request verification of phase deliverables"
3. VMGR assigns VER; VER performs technical verification
4. VER produces Verification Report
5. **QUA template check on VER report** (1-Pass Rule)
6. On PASS: VMGR reviews VER report (technical content)
7. On VMGR APPROVE: proceed to validation (Phase 7 only) or report to COD
8. Phase 7: VMGR assigns VAL; VAL produces Validation Reports
9. **QUA template check on VAL reports** (1-Pass Rule)
10. VMGR reviews VAL reports → Final V&V Decision (cannot be overridden by COD or PM)

**COD Gate Check**:
- ✓ All phase deliverables QUA-passed (Track A)
- ✓ VER Verification Report QUA-passed and VMGR-approved (Track B, SIL 3)
- ✓ VAL reports QUA-passed and VMGR-approved (Phase 7 only, SIL 3)
- ✓ Traceability complete (from VER findings)
- ✓ Zero critical open defects
- **Result**: COD authorizes next phase (PASS) or COD BLOCKS (FAIL)

**QUA Position**: QUA is a gate within Track A and a gate within Track B — QUA never performs technical verification (VER's role) or technical validation (VAL's role).

---

## 3. DOCUMENTATION STRUCTURE

### 3.1 Document Hierarchy

```
System Level (EN 50126/50129)
├── System Requirements Specification (S1)
├── System Architecture Description (S2)
├── System Safety Requirements Specification (S3)
└── System Safety Plan (S4)
    │
    └──> Software Level (EN 50128) — 46 Annex C Items
         ├── Phase 1: Planning (Items 1–5)
         ├── Phase 2: Requirements (Items 6–8)
         ├── Phase 3: Architecture & Design (Items 9–14)
         ├── Phase 4: Component Design (Items 15–17)
         ├── Phase 5: Implementation & Testing (Items 18–20)
         ├── Phase 6: Integration (Items 21–22)
         ├── Phase 7: Validation (Items 23–27)
         ├── Phase 8: Assessment (Items 45–46)
         ├── Phase 9: Deployment (Items 36–40)
         └── Phase 10: Maintenance (Items 41–44)
```

**Complete deliverable matrix**: See `DELIVERABLES.md` Annex C Table C.1.

### 3.2 Document Templates

All Annex C deliverables follow standardized templates located in `deliverables/` directory. Each template defines:
- Document Control table (Document ID, Version, Date, Author, Status)
- Approvals table (Author, 1st Check, 2nd Check, Approver)
- Required sections per document type
- EN 50128 standard references

**Template Compliance**: QUA checks that every deliverable conforms to its template using `[SKILL_ROOT] review-criteria/generic-format-checker.yaml` plus document-specific sections supplement from `[SKILL_ROOT] review-criteria/sections/<doc-key>-sections.yaml`.

### 3.3 Document ID Convention

All documents use the format: `DOC-<ABBREV>-<YYYY>-<NNN>`

**Examples**:
- `DOC-SQAP-2026-001` (Software Quality Assurance Plan)
- `DOC-SRS-2026-001` (Software Requirements Specification)
- `DOC-SOURCECODE-2026-001` (Software Source Code and supporting documentation)

**Canonical Path Resolution**: Before writing any QUA Review Report, QUA invokes CM `query-location` via the `task` tool to obtain the canonical path. Never hard-code file paths.

---

## 4. DOCUMENTATION CONTROL

### 4.1 Roles for Write/Check/Approval

Per EN 50128 Annex C Table C.1 and DELIVERABLES.md:

| Deliverable Type | Written By | 1st Check | 2nd Check | Approver |
|------------------|------------|-----------|-----------|----------|
| Development deliverables (items 6, 9–13, 15–16, 18, 20–22, 24, 27, 36–39, 41–43) | REQ/DES/IMP/INT/TST/PM/CM | VER | VAL | PM |
| VER reports (items 2, 4, 8, 14, 17, 19, 23, 40, 44) | VER | — | VAL (or —) | VMGR (SIL 3) |
| VAL reports (items 5, 25, 26) | VAL | VER | — | VMGR (SIL 3) |
| QUA-authored (item 1 only) | QUA | VER | VAL | PM |
| CM-authored (items 3, 39) | CM | VER | VAL | PM |
| ASR-authored (items 45–46) | ASR | VER | — | Safety Authority (external) |

**QUA Template Check**: QUA checks FORMAT before 1st Check (Track A) or before VMGR review (Track B for VER/VAL reports).

**Track A Flow**: Author → QUA template check → (if PASS) → VER 1st check → VAL 2nd check → PM approval → COD gate  
**Track B Flow (VER/VAL reports)**: VER/VAL → QUA template check (1-Pass Rule) → (if PASS) → VMGR technical review → COD gate

### 4.2 Document Distribution and Archiving

**Distribution**:
- All deliverables are stored in project Git repository under `examples/TDC/docs/`
- CM maintains controlled access per SCMP (item 3, DOC-SCMP-2026-001)
- External stakeholders (Safety Authority, Customer) receive controlled copies via PM

**Archiving**:
- All baselined documents archived under CM control
- Baseline created at phase gate (COD approval)
- Change control required for all post-baseline modifications (CCB approval per SCMP)

### 4.3 Document Update Procedure

**Frequency**: SQAP reviewed and updated:
- Quarterly (SIL 3 requirement)
- At phase transitions
- On SIL level change, organization change, tool change, audit finding, significant defect pattern

**Responsibility**: QUA authors updates; VER 1st-checks; VAL 2nd-checks; PM approves; COD notified

**Method**: Version-controlled updates via Git; CCB approval for baseline changes; LIFECYCLE_STATE.md updated with change log entry

---

## 5. QUALITY ACTIVITIES BY PHASE

### Phase 1: Planning

**QUA Activities**:
- [A] **SQAP authorship** — QUA writes this SQAP (item 1) under VER direction (§6.5.4.3, deviation D8)
- [B] **Template compliance check** on all Phase 1 deliverables (items 1–5):
  - Item 1: SQAP (exception: QUA authors; VER 1st-checks)
  - Item 2: SQAVR (produced by VER; QUA checks VER report)
  - Item 3: SCMP (produced by CM)
  - Item 4: SVP (produced by VER; QUA checks VER document)
  - Item 5: SVaP (produced by VAL; QUA checks VAL document)

**QUA Output**: QUA Review Reports for items 1–5

**Gate Input to COD**: All items QUA-PASS before PM reports Track A complete

### Phase 2: Requirements

**QUA Activities**:
- [A] Template compliance: Item 6 (SRS)
- [B] Template compliance: Item 7 (Overall Software Test Specification)
- [C] Template compliance: Item 8 (Software Requirements Verification Report) — 1-Pass Rule
- [D] **Traceability audit** (MANDATORY SIL 3): VER checks T1–T2 (System Req → SW Req → Overall Test Spec); QUA audits traceability completeness evidence per Table A.9 T6

**QUA Output**: QUA Review Reports for items 6–8; Traceability Audit Report (SIL 3)

### Phase 3: Architecture & Design

**QUA Activities**:
- [A] Template compliance: Item 9 (SAS)
- [B] Template compliance: Item 10 (SDS)
- [C] Template compliance: Item 11 (Software Interface Specifications)
- [D] Template compliance: Item 12 (Software Integration Test Specification)
- [E] Template compliance: Item 13 (Software/Hardware Integration Test Specification)
- [F] Template compliance: Item 14 (Software Architecture and Design Verification Report) — 1-Pass Rule
- [G] **Traceability audit** (MANDATORY SIL 3): VER checks T3–T5c (SRS → SAS → SDS → Interfaces → Integration Test Specs); QUA audits evidence

**QUA Output**: QUA Review Reports for items 9–14; Traceability Audit Report (SIL 3)

### Phase 4: Component Design

**QUA Activities**:
- [A] Template compliance: Item 15 (Software Component Design Specification)
- [B] Template compliance: Item 16 (Software Component Test Specification)
- [C] Template compliance: Item 17 (Software Component Design Verification Report) — 1-Pass Rule
- [D] **Traceability audit** (MANDATORY SIL 3): VER checks T6, T11 (SDS → Component Design → Component Test Spec); QUA audits evidence

**QUA Output**: QUA Review Reports for items 15–17; Traceability Audit Report (SIL 3)

### Phase 5: Implementation & Testing

**QUA Activities**:
- [A] Template compliance: Item 18 (Software Source Code and Supporting Documentation) — QUA checks FORMAT only; VER performs code review (§7.5.4.10)
- [B] Template compliance + 1-Pass Rule: Item 19 (Software Source Code Verification Report) — VER performs MISRA C, static analysis, complexity checks; QUA checks VER report FORMAT
- [C] Template compliance: Item 20 (Software Component Test Report)
- [D] **Traceability audit** (MANDATORY SIL 3): VER checks T7, T12 (Component Design → Code → Unit Tests); QUA audits evidence
- [E] **QA process data recording** (MANDATORY SIL 3, Table A.9 T8): QUA records NCR counts, gate pass/fail rates, process audit findings; QUA verifies measurement data (coverage, defects, complexity) produced by IMP/TST/VER and CM-controlled

**QUA Output**: QUA Review Reports for items 18–20; QA Process Data Record (SIL 3); Traceability Audit Report (SIL 3)

**Critical Note**: QUA does NOT run measurement tools (cppcheck, gcov, lizard) — those are IMP/TST/VER responsibilities. QUA audits that evidence exists.

### Phase 6: Integration

**QUA Activities**:
- [A] Template compliance: Item 21 (Software Integration Test Report)
- [B] Template compliance: Item 22 (Software/Hardware Integration Test Report)
- [C] **Traceability audit** (MANDATORY SIL 3): VER checks T10a, T10b, T12 (Integration Test Specs → Integration Tests → Results); QUA audits evidence

**QUA Output**: QUA Review Reports for items 21–22; Traceability Audit Report (SIL 3)

**Note**: Item 23 (Software Integration Verification Report) is produced in Phase 7 per Annex C, not Phase 6.

### Phase 7: Validation

**QUA Activities — Track A**:
- [A] Template compliance: Item 24 (Overall Software Test Report) — TST-produced

**QUA Activities — Track B**:
- [B] Template compliance: Item 23 (Software Integration Verification Report) — VER-produced; 1-Pass Rule
- [C] Template compliance: Item 25 (Software Validation Report) — VAL-produced; 1-Pass Rule
- [D] Template compliance: Item 26 (Tools Validation Report) — VAL-produced; 1-Pass Rule; if applicable
- [E] Template compliance: Item 27 (Release Note)

**QUA Output**: QUA Review Reports for items 23–27; QA Template Compliance Reports (for VER/VAL reports, 1-Pass Rule)

**Note**: This is the only phase where QUA template-checks VAL-authored formal Validation Reports. QUA checks FORMAT only; VMGR reviews technical content (SIL 3).

### Phase 8: Assessment

**QUA Activity**: **NONE**

**Rationale**: ASR (Assessor) is fully independent from the project AND supplier (§5.1.2.5–5.1.2.7). ASR is not directed by COD, PM, or QUA. Items 45–46 are ASR-authored; VER performs 1st check only; no VAL 2nd check and no QUA template compliance step.

**Mandatory**: SIL 1–4 per §6.4.1.1; SIL 0 exempt §6.4.1.2

### Phase 9: Deployment

**QUA Activities**:
- [A] Template compliance: Item 36 (Software Release and Deployment Plan)
- [B] Template compliance: Item 37 (Software Deployment Manual)
- [C] Template compliance: Item 38 (Release Notes)
- [D] Template compliance: Item 39 (Deployment Records)
- [E] Template compliance: Item 40 (Deployment Verification Report) — VER-authored; 1-Pass Rule

**QUA Output**: QUA Review Reports for items 36–40

### Phase 10: Maintenance

**QUA Activities** (recurring per CCB-approved Change Request):
- [A] Template compliance: Item 41 (Software Maintenance Plan)
- [B] Template compliance: Item 42 (Software Change Records)
- [C] Template compliance: Item 43 (Software Maintenance Records)
- [D] Template compliance: Item 44 (Software Maintenance Verification Report) — VER-authored; 1-Pass Rule
- [E] **Process audit** (MANDATORY SIL 3): Verify CCB change control procedures followed
- [F] **Traceability impact audit** (MANDATORY SIL 3): Verify all downstream traceability links re-checked for each CR scope

**QUA Output**: QUA Review Reports for items 41–44; Process Audit Report (SIL 3)

### Cross-Cutting Activities (Active Throughout All Phases)

**[P] Process Audits** (MANDATORY monthly, SIL 3):
- Output: Process Audit Reports

**[M] Quality Metrics Collection and Trend Analysis** (MANDATORY per phase, SIL 3):
- Output: Quality Metrics Reports

**[T] Traceability Audits** (MANDATORY, SIL 3):
- VER checks technical completeness of traceability (§6.5.4.14–17)
- QUA audits the evidence that VER traceability checking was performed, recorded, and baselined under CM control (§6.5.4.15)
- Output: Traceability Audit Reports

**[N] Non-Conformance Management** (MANDATORY SIL 3):
- QUA logs and tracks NCRs; escalates to PM/COD if unresolved
- Output: Non-Conformance Reports (NCRs)

---

## 6. REVIEWS AND AUDITS

### 6.1 Review Types

| Review Type | Participants | Frequency | Criteria | Output |
|-------------|--------------|-----------|----------|--------|
| **QUA Template Check** | QUA (sole reviewer) | Per deliverable submission | Document ID format; Document Control; Approvals; Required Sections | QUA Review Report (PASS/FAIL) |
| **VER 1st Check** | VER (independent) | Per deliverable (Track A) | Technical correctness; traceability; compliance with standards | Verification Report (Annex C items 2, 8, 14, 17, 19, 23, 40, 44) |
| **VAL 2nd Check** | VAL (independent) | Per deliverable (Track A) | Validation against system requirements; fitness for purpose | Validation annotations in VAL reports |
| **VMGR Technical Review** | VMGR (independent) | Per VER/VAL report (Track B, SIL 3) | Technical content of VER/VAL findings; V&V completeness | VMGR approval or rejection |
| **Process Audit** | QUA + CM + PM | Monthly (SIL 3) | EN 50128 process adherence; evidence existence; CM control | Process Audit Report |
| **CCB Review** | PM (chair) + CM + SAF + VER + VAL + affected agents | Per Change Request | Impact analysis; traceability impact; safety impact; regression risk | CCB Decision Record |

### 6.2 Audit Schedule (SIL 3)

| Audit Type | Frequency | Scope | Led By | Output |
|------------|-----------|-------|--------|--------|
| **Process Audit** | Monthly | EN 50128 lifecycle compliance; evidence existence; CM baselines | QUA | Process Audit Report |
| **Traceability Audit** | Per phase gate | VER traceability checks T1–T15 performed and recorded | QUA | Traceability Audit Report |
| **QA Metrics Review** | Per phase gate | NCR trends; gate pass/fail rates; first-submission PASS rate | QUA | Quality Metrics Report |
| **SQAP Compliance Audit** | Quarterly | Adherence to this SQAP; update triggers; deviation tracking | QUA + VER | SQAP Compliance Audit Report |

### 6.3 Audit Criteria

**Process Audit Criteria** (from `tasks/QUALITY_PROCESS.md` Diagram 1):

| Phase | Audit Criteria |
|-------|----------------|
| 1 | SQAP issued; SCMP issued; SVP produced by VER; SVaP produced by VAL |
| 2 | Hazard log initiated; SIL assignments recorded; traceability audit (VER performed T1–T2) |
| 3 | FMEA/FTA evidence exists (SAF); architecture meets SIL constraints (VER evidence) |
| 4 | Component test specs exist; component design reviewed |
| 5 | Static analysis report exists; MISRA evidence record exists; coverage record exists |
| 6 | Integration test results recorded; SW/HW integration test results recorded |
| 7 | Validation report exists; Overall Software Test Report exists |
| 8 | **No QUA activity** |
| 9 | Release package complete; deployment records present |
| 10 | Maintenance records; change records per §9.2.4 |

### 6.4 Audit Output

**Audit Finding Record**: If conformance found, no action. If non-conformance found:
- QUA raises NCR (see Section 9)
- NCR assigned to owner (agent/role responsible for fix)
- NCR tracked to closure
- NCR must be resolved before phase gate (CRITICAL NCRs block gate; PM can waive MINOR/MAJOR with COD approval)

---

## 7. METHODS, MEASURES AND TOOLS

### 7.1 EN 50128 Table A.9 Techniques for SIL 3

This section documents the selection and justification of Quality Assurance techniques per EN 50128:2011 Table A.9 for SIL 3. Justification follows §4.7–4.9 requirements.

| # | Technique | Table A.9 Ref | SIL 3 Obligation | TDC Selection | Justification |
|---|-----------|---------------|------------------|---------------|---------------|
| **T1** | Accredited to EN ISO 9001 | D.59 | HR | ADOPTED | Organisation holds EN ISO 9001:2015 accreditation; certificate on file; scope covers railway software development |
| **T2** | Compliant with EN ISO 9001 | D.59 | **M** | **ADOPTED** | Quality management system compliant with ISO 9001:2015; SQAP documents compliance per §6.5.4.5 |
| **T3** | Compliant with ISO/IEC 90003 | D.59 | R | ADOPTED | ISO/IEC 90003:2014 software engineering guidelines applied; noted in SQAP Section 1.3 |
| **T4** | Company Quality System | D.59 | **M** | **ADOPTED** | Company QMS documented; project practices consistent with company QMS; referenced in SQAP Section 1.3 |
| **T5** | Software Configuration Management | D.48 | **M** | **ADOPTED** | SCM processes per §6.6; SCMP (item 3, DOC-SCMP-2026-001); Git version control; baselines at phase gates |
| **T6** | Traceability | D.58 | **M** | **ADOPTED** | Traceability T1–T15 checked by VER; audited by QUA; mandatory SIL 3 per Table A.9; `TRACEABILITY.md` defines chain |
| **T7** | Metrics | D.38 | R | ADOPTED | Quality metrics collected per phase (NCR counts, gate rates, defect trends); reported in QUA Metrics Reports |
| **T8** | Data Recording and Analysis | D.12 | **M** | **ADOPTED** | QA process data recorded per SQAP; coverage reports, defect counts, complexity distributions produced by IMP/TST/VER; QUA audits existence and CM control; mandatory SIL 3 |

**Key**: **M** = Mandatory; **HR** = Highly Recommended; **R** = Recommended

**Techniques NOT ADOPTED**: None — all Table A.9 techniques adopted for SIL 3.

**Justification Summary**:
- All MANDATORY (M) techniques adopted without deviation
- All HIGHLY RECOMMENDED (HR) techniques adopted (T1 accreditation)
- All RECOMMENDED (R) techniques adopted (T3, T7) for enhanced rigor at SIL 3

### 7.2 QA Tools

| Tool | Purpose | Qualification Status | Used By | Output |
|------|---------|---------------------|---------|--------|
| **Git** | Version control, CM baselines | T1 (platform tools per §6.7.4.4.2) | CM | Version-controlled repository |
| **workspace.py** | Lifecycle state tracking, traceability checking | T1 (platform tools per §6.7.4.4.2) | COD, CM, QUA | LIFECYCLE_STATE.md, traceability reports |
| **generic-format-checker.yaml** | QUA template compliance checking | T1 (QA tool per SQAP) | QUA | QUA Review Reports |
| **cppcheck** | Static analysis (MISRA C) | T2 (requires qualification per §6.7) | VER | Static analysis reports |
| **gcov** | Code coverage measurement | T2 (requires qualification per §6.7) | TST, VER | Coverage reports |
| **lizard** | Cyclomatic complexity measurement | T2 (requires qualification per §6.7) | VER | Complexity reports |
| **Unity** | Unit test framework | T2 (requires qualification per §6.7) | TST | Unit test results |

**Tool Qualification**: Tools classified T2 (development tools per §6.7.4.4.3) require qualification per item 26 (Tools Validation Report, Phase 7). VAL produces item 26; VER 1st-checks; VMGR reviews (SIL 3).

**Platform Tools** (T1): Git and workspace.py are platform-provided; treated as T1 per §6.7.4.4.2 (no separate qualification required beyond platform validation).

### 7.3 QA Methods

| Method | Description | Applied In | Frequency |
|--------|-------------|------------|-----------|
| **Template Compliance Check** | 4-point check (Document ID, Document Control, Approvals, Sections) using generic-format-checker.yaml | All phases (deliverable submission) | Per deliverable |
| **1-Pass Rule** | VER/VAL reports: 1 resubmission allowed; 2nd rejection = process failure | Phases 1–7, 9–10 (VER/VAL reports) | Per VER/VAL report |
| **Process Audit** | Verify EN 50128 process adherence; evidence existence; CM control | All phases | Monthly (SIL 3) |
| **Traceability Audit** | Audit that VER performed T1–T15 and recorded evidence under CM control | Phases 2–6, 10 | Per phase gate |
| **QA Metrics Collection** | Collect NCR counts, gate rates, first-submission PASS rate | All phases | Per phase gate |
| **NCR Management** | Log, track, escalate non-conformances | All phases | Per finding |

---

## 8. TRACEABILITY MANAGEMENT

### 8.1 Traceability Approach

**Obligation**: Traceability is **MANDATORY** for SIL 3 per EN 50128:2011 Table A.9 Technique T6.

**Scope**: The TDC Software maintains bidirectional traceability across all lifecycle phases per `TRACEABILITY.md`:

```
T1:  System Requirements → Software Requirements
T2:  Software Requirements → Overall Software Test Specification
T3:  Software Requirements → Software Architecture
T4:  Software Architecture → Software Design
T5a: Software Design → Integration Test Specification
T5b: Software Architecture → Software/Hardware Integration Test Specification
T5c: Software Architecture → Software Interface Specifications
T6:  Software Design → Software Component Design
T7:  Software Component Design → Source Code
T8:  Software Component Design → Software Component Test Specification (forward only)
T9:  (reserved — not used in EN 50128:2011)
T10a: Integration Test Specification → Integration Test Report
T10b: Software/Hardware Integration Test Specification → Software/Hardware Integration Test Report
T11: Software Component Test Specification → Software Component Test Report
T12: Source Code → Software Component Test Report
T13: Software Requirements → Software Validation Report (via Overall Test Spec)
T14: Software Component Test Reports → Overall Software Test Report
T15: Integration Test Reports → Overall Software Test Report
```

**VER Responsibility**: VER checks technical completeness of all traceability links T1–T15 per §6.5.4.14–17 and records findings in Verification Reports (items 8, 14, 17, 19, 23, 40, 44).

**QUA Responsibility**: QUA audits the **evidence** that VER performed traceability checking, that traceability data is recorded, and that it is baselined under CM control per §6.5.4.15. QUA does NOT independently re-check traceability links (that is VER's duty).

### 8.2 Traceability Tools

**Tool**: `workspace.py trace` command

**Usage**:
```bash
# Check T1 traceability (System Req → SW Req)
python3 tools/workspace.py trace T1 --from <System-Req-ID> --to <SW-Req-ID>

# Generate traceability coverage report
python3 tools/workspace.py trace --coverage
```

**Output**: Traceability reports stored in `docs/traceability/` under CM control.

**Reference**: See `en50128-lifecycle-tool-integration` skill → workspace.py trace command reference.

### 8.3 Traceability Verification

**Per Phase**:
- **Phase 2**: VER checks T1, T2 → QUA audits evidence → Traceability Audit Report
- **Phase 3**: VER checks T3, T4, T5a, T5b, T5c → QUA audits evidence → Traceability Audit Report
- **Phase 4**: VER checks T6, T11 (forward only per §7.4.4.13) → QUA audits evidence → Traceability Audit Report
- **Phase 5**: VER checks T7, T12 → QUA audits evidence → Traceability Audit Report
- **Phase 6**: VER checks T10a, T10b, T12 (integration test execution) → QUA audits evidence → Traceability Audit Report
- **Phase 7**: VER checks T13, T14, T15 (validation traceability) → reported in Software Validation Verification Report (item †)
- **Phase 10**: VER checks traceability impact per Change Request scope → QUA audits re-check evidence → Traceability Audit Report

**Gate Requirement**: COD gate-check requires traceability complete (VER-verified, QUA-audited) before phase advancement.

---

## 9. NON-CONFORMANCE MANAGEMENT

### 9.1 Deviations Tracking

**Platform Deviations D1–D8**: Documented in Section 1.4 (Introduction) and tracked in `DELIVERABLES.md`. Subject to Safety Authority review.

**Project-Specific Deviations**: Any deviation from this SQAP or from EN 50128:2011 requirements must be:
1. Raised as NCR by QUA
2. Impact-assessed by VER + SAF
3. Approved by PM (MINOR/MAJOR) or COD (CRITICAL)
4. Recorded in LIFECYCLE_STATE.md change log
5. Reported to Safety Authority (CRITICAL deviations)

### 9.2 Non-Conformance Report (NCR) Structure

**NCR Fields**:
- **NCR ID**: `NCR-[YYYY]-[NNN]` (e.g., `NCR-2026-001`)
- **Phase**: Phase number where found
- **Annex C Item** (if deliverable-related): Item number
- **Type**: `format_defect` | `process_defect` | `evidence_missing` | `deviation`
- **Severity**: `MINOR` | `MAJOR` | `CRITICAL`
- **Description**: What was found
- **Owner**: Agent/role responsible for fix
- **Due**: Phase gate (must close before gate)
- **Status**: `OPEN` | `RESOLVED` | `WAIVED`
- **Waiver Authority**: PM (MINOR/MAJOR) | COD (CRITICAL)

### 9.3 NCR Severity Definitions

| Severity | Definition | Example | Waiver Authority | Gate Impact |
|----------|------------|---------|------------------|-------------|
| **CRITICAL** | Violation of MANDATORY (M) EN 50128 requirement; safety impact; SIL integrity compromise | Missing MISRA C compliance at SIL 3; traceability gap in safety-critical requirement | COD (with Safety Authority notification) | **BLOCKS GATE** (cannot proceed) |
| **MAJOR** | Violation of HIGHLY RECOMMENDED (HR) technique without justification; significant process defect | VER report fails 1-Pass Rule twice; missing coverage report | PM (with COD approval) | Requires resolution or waiver before gate |
| **MINOR** | Formatting defect; documentation gap; process improvement opportunity | Missing Document Control field; typo in Approvals table | PM | Tracked; may proceed with waiver |

### 9.4 NCR Lifecycle

```
1. QUA logs NCR (format/process defect found during template check or audit)
   ↓
2. QUA assigns to owner (agent/role responsible for fix)
   ↓
3. Owner fixes defect; resubmits deliverable or provides evidence
   ↓
4. QUA re-checks
   ├── PASS → QUA marks NCR RESOLVED
   └── FAIL → Iteration count increments
       ├── If < iteration limit → return to step 3
       └── If ≥ iteration limit → QUA escalates to PM
           ├── PM requests waiver from COD (if CRITICAL)
           ├── PM grants waiver (if MINOR/MAJOR with justification)
           └── QUA marks NCR WAIVED (recorded in LIFECYCLE_STATE.md)
   ↓
5. COD gate-check:
   ├── Zero CRITICAL NCRs OPEN → gate may proceed
   └── CRITICAL NCRs OPEN → COD BLOCKS gate
```

### 9.5 NCR Tracking and Reporting

**Tracking**: All NCRs tracked in QUA Metrics Reports per phase. NCR database maintained in `docs/quality/NCR-Log.md` under CM control.

**Reporting**:
- **Monthly** (SIL 3): QUA Metrics Report includes NCR counts by phase, severity, type, age
- **Per Phase Gate**: NCR summary in COD gate-check input
- **Quarterly**: SQAP Compliance Audit reviews NCR trends; identifies systemic issues

**Escalation**: Unresolved CRITICAL NCRs escalated to COD; COD notifies Safety Authority if safety impact.

---

## 10. QUALITY METRICS

### 10.1 Metrics Collection (MANDATORY SIL 3)

Per EN 50128:2011 Table A.9 Technique T8 (Data Recording and Analysis), QUA collects the following metrics:

| Metric ID | Metric Name | Collected By | Frequency | Source | Target (SIL 3) |
|-----------|-------------|--------------|-----------|--------|----------------|
| **M1** | NCR count by phase | QUA | Per phase gate | QUA NCR Log | < 5 MAJOR per phase; 0 CRITICAL at gate |
| **M2** | NCR count by severity | QUA | Per phase gate | QUA NCR Log | 0 CRITICAL open; < 3 MAJOR open |
| **M3** | NCR count by type | QUA | Per phase gate | QUA NCR Log | Trend analysis (reduce format_defect over time) |
| **M4** | Gate pass/fail rate | QUA | Per phase gate | LIFECYCLE_STATE.md | 100% gate PASS (after iterations) |
| **M5** | QUA review iterations per deliverable | QUA | Per deliverable | QUA Review Reports | > 80% PASS on 1st submission |
| **M6** | First-submission PASS rate | QUA | Per phase | QUA Review Reports | > 80% (quality trend indicator) |
| **M7** | Open NCR age (days since raised) | QUA | Monthly | QUA NCR Log | < 30 days average age |
| **M8** | Process audit findings | QUA | Monthly | Process Audit Reports | 0 CRITICAL findings; < 3 MAJOR findings |
| **M9** | Code coverage (statement/branch/MC/DC) | TST, VER | Phase 5 gate | gcov reports | ≥ 95% statement; ≥ 90% branch; MC/DC per safety-critical modules |
| **M10** | Cyclomatic complexity | VER | Phase 5 gate | lizard reports | ≤ 10 per function (SIL 3 limit) |
| **M11** | MISRA C compliance rate | VER | Phase 5 gate | cppcheck reports | 100% (zero violations; deviations justified per MISRA deviation procedure) |
| **M12** | Traceability coverage | VER | Per phase gate | workspace.py trace --coverage | 100% (all links T1–T15 verified) |

### 10.2 Metrics Thresholds and Reporting

**Thresholds**:
- **GREEN**: Metric within target (e.g., M5 > 80% first-submission PASS)
- **YELLOW**: Metric approaching threshold (e.g., M5 = 70–80%)
- **RED**: Metric exceeds threshold (e.g., M5 < 70%) — triggers corrective action

**Reporting Frequency**:
- **Per Phase Gate**: QUA Metrics Report submitted to COD as gate input
- **Monthly**: QUA Metrics Summary (SIL 3 requirement)
- **Quarterly**: SQAP Compliance Audit reviews metrics trends

**Corrective Action**:
- **RED metric**: QUA raises NCR; PM identifies root cause; corrective action plan developed; QUA verifies implementation
- **Trend Analysis**: QUA identifies systemic issues (e.g., repeated format defects from same author → training intervention)

### 10.3 Metrics Storage

**Location**: `docs/quality/Metrics-Reports/`

**Format**: Markdown tables per phase; CSV export for trend analysis

**CM Control**: All metrics reports baselined at phase gate; archived under CM control per SCMP

---

## 11. TRAINING

### 11.1 Training Requirements (MANDATORY SIL 3)

Per EN 50128:2011 §6.5 and Table A.9, all personnel performing quality-related activities SHALL receive training in:

| Role | Training Topic | Frequency | Evidence |
|------|----------------|-----------|----------|
| **QUA** | EN 50128:2011 §6.5 Quality Assurance; SQAP procedures; template compliance checking; NCR management | Initial + annual refresher | Training certificate; SQAP quiz (> 80%) |
| **VER** | EN 50128:2011 §6.2 Verification; MISRA C:2012; static analysis tools (cppcheck); traceability checking T1–T15 | Initial + annual refresher | Training certificate; tool qualification evidence |
| **VAL** | EN 50128:2011 §6.3 Validation; system testing; acceptance criteria; SVaP procedures | Initial + annual refresher | Training certificate; validation plan review |
| **All Agents** | Document templates; Approvals table requirements; EN 50128 SIL 3 obligations | Initial (project onboarding) | Training attendance record |

### 11.2 Training Records

**Storage**: `docs/training/Training-Records.md`

**CM Control**: Training records archived; reviewed quarterly by QUA

**Audit**: QUA audits training completion during monthly process audits (SIL 3)

---

## 12. REFERENCES

### 12.1 Normative References

| Reference | Title |
|-----------|-------|
| **EN 50128:2011** | Railway applications — Communication, signalling and processing systems — Software for railway control and protection systems |
| **EN 50126-1:2017** | Railway applications — The specification and demonstration of Reliability, Availability, Maintainability and Safety (RAMS) — Part 1: Generic RAMS process |
| **EN 50126-2:2017** | Railway applications — The specification and demonstration of Reliability, Availability, Maintainability and Safety (RAMS) — Part 2: Systems approach to safety |
| **EN 50129:2018** | Railway applications — Communication, signalling and processing systems — Safety related electronic systems for signalling |
| **ISO 9001:2015** | Quality management systems — Requirements |
| **ISO/IEC 90003:2014** | Software engineering — Guidelines for the application of ISO 9001:2015 to computer software |
| **MISRA C:2012** | Guidelines for the use of the C language in critical systems (Third Edition) |

### 12.2 Project References

| Document ID | Document Name | Location |
|-------------|---------------|----------|
| DOC-SCMP-2026-001 | Software Configuration Management Plan | `docs/phase-1-planning/Software-Configuration-Management-Plan.md` |
| DOC-SVP-2026-001 | Software Verification Plan | `docs/phase-1-planning/Software-Verification-Plan.md` |
| DOC-SVaP-2026-001 | Software Validation Plan | `docs/phase-1-planning/Software-Validation-Plan.md` |
| DOC-SYS-PLAN-2026-001 | System Safety Plan | `docs/system/System-Safety-Plan.md` |
| DOC-SYS-SAF-2026-001 | System Safety Requirements Specification | `docs/system/System-Safety-Requirements-Specification.md` |
| — | DELIVERABLES.md | `/home/norechang/test/opencode-en50128/DELIVERABLES.md` |
| — | WORKFLOW.md | `/home/norechang/test/opencode-en50128/WORKFLOW.md` |
| — | TRACEABILITY.md | `/home/norechang/test/opencode-en50128/TRACEABILITY.md` |
| — | LIFECYCLE.md | `/home/norechang/test/opencode-en50128/LIFECYCLE.md` |
| — | ORGANIZATION.md | `/home/norechang/test/opencode-en50128/ORGANIZATION.md` |
| — | tasks/QUALITY_PROCESS.md | `/home/norechang/test/opencode-en50128/tasks/QUALITY_PROCESS.md` |

---

## APPENDIX A: QUA Format-Gate Algorithm

**Full algorithm details**: See `en50128-quality` skill, Section 3 (Format-Gate Algorithm).

**Summary**:
1. Read .workspace → resolve workspace root
2. Invoke CM query-location to confirm canonical path of deliverable
3. Read deliverable at canonical path
4. Identify document type → load generic-format-checker.yaml
5. Identify sections supplement → load sections/<doc-key>-sections.yaml
6. Apply generic checks (GF-001: Document ID, GF-002: Document Control, GF-003: Approvals)
7. Apply sections check (all required sections present?)
8. Collect all failures
9. Determine qua_check_type from quality-process.yaml for this annex_c_item
10. Write QUA Review Report to canonical path (CM query-location for QUAREPORT)
11. Report PASS or FAIL to PM

**On PASS**: PM notified; deliverable proceeds to VER (Track A) or VMGR (Track B).  
**On FAIL**: Return defect list to PM; PM routes to author for fix; track iteration count.

---

## APPENDIX B: Iteration Limits

| Deliverable Type | QUA Check Type | Iteration Limit | On Exceed |
|------------------|----------------|-----------------|-----------|
| **Development deliverables** (items 6, 9–13, 15–16, 18, 20–22, 24, 27, 36–39, 41–43) | `template_compliance` | 3 iterations | QUA raises NCR; PM escalates for training intervention |
| **VER/VAL reports** (items 2, 4, 5, 8, 14, 17, 19, 23, 25, 26, 40, 44) | `template_compliance_one_pass` | 1 resubmission (2 total attempts) | QUA raises NCR severity=MAJOR; PM escalates to VMGR (SIL 3); process failure |
| **ASR documents** (items 45–46) | `none` | N/A | No QUA check |

---

## APPENDIX C: Table A.9 Complete Mapping (SIL 3)

See Section 7.1 for full Table A.9 technique selection and justification.

---

## APPENDIX D: Glossary

| Term | Definition |
|------|------------|
| **CCB** | Change Control Board — reviews and approves Change Requests per SCMP |
| **COD** | Lifecycle Coordinator — end-to-end lifecycle orchestration; phase gate enforcement |
| **Format-Gate** | QUA checkpoint verifying Document ID, Document Control, Approvals, Required Sections |
| **NCR** | Non-Conformance Report — record of quality defect or process violation |
| **1-Pass Rule** | VER/VAL reports: 1 resubmission allowed; 2nd rejection = process failure |
| **QUA** | Quality Assurance Engineer — FORMAT gate-keeper; process auditor |
| **Track A** | Development workflow (PM orchestrates; QUA gates before PM→COD handoff) |
| **Track B** | Independent V&V workflow (COD coordinates; VMGR manages VER/VAL at SIL 3) |
| **VER** | Verifier — performs technical verification; produces Verification Reports |
| **VAL** | Validator — performs technical validation; produces Validation Reports |
| **VMGR** | V&V Manager — independent V&V authority for SIL 3–4; final V&V decision |

---

**END OF DOCUMENT**

---

**SQAP Version**: 1.0  
**Date**: 2026-04-02  
**Next Review**: 2026-07-02 (Quarterly)  
**Status**: DRAFT — Awaiting VER 1st Check  
**Baseline**: To be established at Phase 1 gate
