# Software Configuration Management Plan (SCMP)

**DOCUMENT TYPE**: Software Configuration Management Plan  
**EN 50128 DELIVERABLE**: Annex C Item 3  
**STANDARD REFERENCE**: EN 50128:2011 Section 6.6, Table A.9  
**PROJECT**: TDC (Train Door Control System)  
**SIL LEVEL**: 3

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SCMP-2026-001 |
| **Version** | 1.0 |
| **Date** | 2026-04-02 |
| **Project** | TDC (Train Door Control System) |
| **SIL Level** | SIL 3 |
| **Author** | Configuration Manager (CM) |
| **Status** | DRAFT — Awaiting VER 1st Check |

---

## VERSION HISTORY

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | 2026-04-02 | CM | Initial SCMP draft for SIL 3 | - |
| 1.0 | 2026-04-02 | CM | Baseline version for Phase 1 | [Pending VER] |

---

## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author (CM)** | [CM Name] | [PENDING] | [PENDING] |
| **Reviewer (QUA)** | [QUA Name] | [PENDING] | [PENDING] |
| **Approver (PM)** | [PM Name] | [PENDING] | [PENDING] |

**Note**: Per EN 50128:2011 Annex C Table C.1, the SCMP (item 3) is written by CM, 1st-checked by VER, 2nd-checked by VAL, and approved by PM. The Approvals table above records Track A sign-off (Author → QUA template check → PM approval). VER 1st check, VAL 2nd check, and VMGR technical review occur in the deliverable review chain per `DELIVERABLES.md` but do not appear as Approvals table signatories.

---

## 1. INTRODUCTION

### 1.1 Purpose

This Software Configuration Management Plan (SCMP) establishes the configuration management processes, procedures, and responsibilities for the Train Door Control System (TDC) software development at Safety Integrity Level 3 (SIL 3). This plan ensures that all software configuration items (CIs) are identified, controlled, tracked, and audited throughout the software lifecycle in accordance with EN 50128:2011 Section 6.6.

**Normative Basis**: EN 50128:2011 §6.6.4.1 mandates that a Software Configuration Management Plan shall be established and maintained. Table A.9 Technique 5 (Software Configuration Management) is MANDATORY at ALL SIL levels (SIL 0–4).

This SCMP governs all configuration management activities from Phase 1 (Planning) through Phase 10 (Maintenance) and ensures compliance with:
- EN 50128:2011 Railway Software Standard (SIL 3)
- EN 50126-1:2017 RAMS Part 1 (Generic RAMS process)
- EN 50126-2:2017 RAMS Part 2 (Systems approach to safety)
- ISO 9001:2015 Quality management systems

### 1.2 Scope

This SCMP applies to all software artifacts under configuration control for the TDC Software at SIL 3. The plan covers:

1. **Configuration Identification** — Document and code naming conventions, baseline definitions
2. **Configuration Control** — Change control process, CCB composition, nine aspects per §6.6.4.1
3. **Configuration Status Accounting** — Configuration status reporting, traceability management (MANDATORY SIL 3)
4. **Configuration Audits** — Baseline verification, CM presence checks, VER functional completeness
5. **Version Control Strategy** — Git repository structure, branch strategy, tagging conventions
6. **Baseline Management** — Eight baselines across phases 1–9, creation procedure per gate
7. **Traceability Management** — T1–T15 traceability rules, workspace.py trace command usage
8. **Build and Release Management** — Build automation, release package content, reproducibility
9. **Evidence Management** — Canonical evidence paths for VER, TST, SAF artifacts per phase

**Out of Scope**: System-level configuration management (covered by System Configuration Management Plan); hardware configuration management.

### 1.3 SIL Classification

**Target SIL Level**: SIL 3

**EN 50128 Table A.9 Configuration Management Obligations**:

| # | Technique | SIL 3 Obligation | TDC Implementation |
|---|-----------|------------------|-------------------|
| **T5** | Software Configuration Management | **M** (MANDATORY) | This SCMP; Git VCS; CM canonical path authority |
| **T6** | Traceability | **M** (MANDATORY) | T1–T15 traceability checked by VER; workspace.py trace; RTM |
| **T8** | Data Recording and Analysis | **M** (MANDATORY) | Configuration status reports; CR metrics; baseline manifests |

**SIL 3 Implications**:
- **Enhanced Traceability**: All T1–T15 traceability links MANDATORY; checked by VER every phase; audited by QUA
- **Independent V&V**: VER (MANDATORY independent from DES/IMP) performs functional completeness checks at each baseline
- **CCB Composition for Safety-Critical CRs**: PM (Chair) + CM (Secretary) + QUA + VER (SIL 3 requirement for safety-critical changes)
- **Audit Trail**: All configuration changes require Software Change Record per §6.6.4.1; audit trail maintained throughout lifecycle
- **Baseline Reproducibility**: §9.1.4.3 requires reproducibility throughout operational lifetime; enforced via Git tags + CM manifest

### 1.4 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **CI** | Configuration Item — Any software artifact under configuration management per §6.6 |
| **Baseline** | Approved version of CIs that can only be changed through formal change control (CCB approval) |
| **CCB** | Change Control Board — Authority for approving changes to baselines; PM chairs, CM is secretary |
| **CR** | Change Request — Formal request to modify a baselined CI per §6.6.4.1 |
| **SCM** | Software Configuration Management — Process per EN 50128:2011 §6.6 |
| **VCS** | Version Control System (Git) — Repository for all CIs under CM control |
| **Canonical Path** | The single authoritative file system path for a deliverable or evidence artifact, resolved by CM query-location capability |
| **T1–T15** | Traceability rules from System Req → Code → Test, defined in `TRACEABILITY.md` |
| **workspace.py** | Lifecycle coordination tool; CM uses `trace` command for traceability verification |
| **Manifest** | Baseline manifest (manifest.yaml) — CM-produced record of all CIs in a baseline per §9.1.4.2 |

### 1.5 References

| Reference | Document | Location |
|-----------|----------|----------|
| **[EN50128]** | EN 50128:2011 Railway Software Standard | `std/EN50128-2011.md` |
| **[EN50126-1]** | EN 50126-1:2017 RAMS Part 1 | `std/EN 50126-1-2017.md` |
| **[EN50126-2]** | EN 50126-2:2017 RAMS Part 2 | `std/EN 50126-2-2017.md` |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 | `docs/phase-1-planning/Software-Quality-Assurance-Plan.md` |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 | `docs/phase-1-planning/Software-Verification-Plan.md` (to be created) |
| **[SVaP]** | Software Validation Plan, DOC-SVaP-2026-001 | `docs/phase-1-planning/Software-Validation-Plan.md` (to be created) |
| **[LIFECYCLE]** | LIFECYCLE.md — EN 50128 V-Model lifecycle | `/home/norechang/test/opencode-en50128/LIFECYCLE.md` |
| **[TRACEABILITY]** | TRACEABILITY.md — T1–T15 traceability rules | `/home/norechang/test/opencode-en50128/TRACEABILITY.md` |
| **[BASELINE_MGMT]** | Baseline Management — Diagrams 1–2 | `/home/norechang/test/opencode-en50128/tasks/BASELINE_MANAGEMENT.md` |
| **[DELIVERABLES]** | DELIVERABLES.md — Annex C Table C.1 | `/home/norechang/test/opencode-en50128/DELIVERABLES.md` |
| **[WORKFLOW]** | WORKFLOW.md — Agent interaction, CCB flow | `/home/norechang/test/opencode-en50128/WORKFLOW.md` |

### 1.6 Overview

This SCMP is organized as follows:
- **Section 2**: Configuration Management Organization — CM role, CCB composition, independence requirements
- **Section 3**: Configuration Identification — Document registry, evidence paths, version numbering, Git branch strategy
- **Section 4**: Configuration Control — Nine aspects per §6.6.4.1, CCB process, change request lifecycle
- **Section 5**: Configuration Status Accounting — Status reports, traceability management, data recording
- **Section 6**: Configuration Audits — CM presence checks, VER functional completeness, baseline verification
- **Section 7**: Baseline Management — Eight baselines (Gates 1–9), creation procedure, manifest format
- **Section 8**: Version Control Strategy — Git repository structure, branch protection, tagging conventions
- **Section 9**: Build and Release Management — Build automation, release package content, reproducibility evidence
- **Section 10**: Tools and Infrastructure — Git, workspace.py, tool qualification (SIL 3 requirement)
- **Section 11**: Training and Competence — CM training requirements
- **Section 12**: Compliance Matrix — EN 50128 §6.6 compliance evidence

---

## 2. CONFIGURATION MANAGEMENT ORGANIZATION

### 2.1 Configuration Manager (CM) — Sole Location Authority

**Role**: Configuration Manager (CM)

**Responsibilities** (per EN 50128:2011 §6.6 and Annex B Table B.10):
1. **Sole location authority** — Define and maintain the canonical document registry (`document-registry.yaml`). All agents MUST call CM `query-location` before writing any deliverable or evidence artifact.
2. **Maintain SCMP** — This document; reviewed quarterly (SIL 3 requirement).
3. **Establish and maintain version control repository** — Git repository; access control; backup procedures.
4. **Manage configuration baselines** — Create eight baselines at Gates 1–9; tag VCS; archive manifest.
5. **Administer Change Control Board (CCB)** — Schedule CCB meetings; prepare CR documentation; record CCB decisions (CM is CCB Secretary).
6. **Perform CM presence checks at baseline** — Verify required signed documents and evidence artifacts are present, correctly versioned, and stored at canonical paths (see Section 2.3 for role boundary).
7. **Generate configuration status reports** — Bi-weekly for SIL 3 (§6.6.3 output documents).
8. **Maintain Requirements Traceability Matrix (RTM)** — MANDATORY SIL 3; tool: workspace.py trace command.
9. **Evidence storage initialization** — Create canonical evidence directories before VER/TST/SAF activities.
10. **Violation alarm protocol** — Raise CRITICAL violation and invoke PM immediately if: document written to unregistered path, baseline created without COD authorization, CI changed without approved CR, VCS tag deleted/force-pushed without CCB approval.

**Independence**: No independence requirement per EN 50128 Annex B Table B.10 (all SIL levels). However, CM SHALL NOT report to development team (DES, IMP, TST). CM reports to PM.

**Authority Structure**:
- CM is the **sole authority** for document locations and baseline control.
- CM does NOT approve or reject change requests — CCB (PM chair) has that authority.
- CM does NOT perform functional completeness verification — VER has that responsibility (§6.2.4.7).
- CM records and archives; VER and VAL judge technical correctness.

### 2.2 Change Control Board (CCB)

**Composition** (SIL 3 — safety-critical CRs):

| Role | Responsibility |
|------|----------------|
| **Project Manager (PM)** | Chair — Final decision authority on CR approval/rejection |
| **Configuration Manager (CM)** | Secretary — Prepare CR documentation, record CCB decisions, update configuration status |
| **Quality Assurance Engineer (QUA)** | Process compliance review — Assess CR impact on QA process, traceability audit requirements |
| **Verifier (VER)** | Technical verification — Assess impact on verification evidence, re-verification scope (MANDATORY for safety-critical CRs at SIL 3) |
| **Safety Engineer (SAF)** | Safety impact analysis — Assess impact on Hazard Log, safety requirements, FMEA/FTA (if CR affects safety-critical requirements) |
| **Software Manager / DES** | Technical feasibility — Assess design impact, effort estimate |

**Meeting Frequency**: Weekly (SIL 3 requirement for active development phases); bi-weekly during maintenance.

**Quorum**: Minimum 4 members (PM, CM, QUA, VER) for SIL 3 safety-critical CR decisions.

**Decision Authority**: PM has final approval authority; CM records decision in CCB minutes and Software Change Record per §6.6.4.1.

**CCB Responsibilities**:
1. Review and approve/reject change requests per §6.6.4.1
2. Assess change impact on SIL, safety, traceability, schedule, cost
3. Authorize baseline modifications
4. Determine re-entry phase per §6.6.4.2 (COD authorizes re-entry; CCB identifies scope)
5. Resolve configuration conflicts

### 2.3 CM Role Boundary — What CM Does and Does NOT Do

**CM's Role at a Baseline Event** (see `tasks/BASELINE_MANAGEMENT.md` Terminology note):

| CM DOES | CM DOES NOT DO |
|---------|----------------|
| Verify required signed documents are present at canonical paths | Judge functional completeness — VER's responsibility per §6.2.4.7 |
| Verify documents are correctly versioned per SCMP naming conventions | Assess technical correctness of requirements, design, or code — VER's responsibility |
| Verify evidence artifacts exist in canonical evidence directories | Re-execute verification checks — VER produces evidence; CM checks presence |
| Create baseline manifest (manifest.yaml) listing all CIs | Decide if verification is complete — VAL's responsibility per §6.3.4.9 |
| Tag VCS with baseline version per Section 7 | State the baseline validated — VAL's responsibility per §6.3.4.10 |
| Archive baseline to `baselines/<baseline-name>/` directory | Override VMGR's V&V decision (SIL 3) — VMGR has final authority |
| Record baseline under configuration control per §9.1.4.2 | Create or modify deliverable content — that is the authoring agent's responsibility |

**EN 50128 Terminology Clarification**:

EN 50128:2011 does **not** define "FCA" (Functional Configuration Audit) or "PCA" (Physical Configuration Audit). Those terms come from MIL-STD-973 / IEEE 828. The EN 50128 equivalent activities are:

| MIL-STD-973 Term | EN 50128 Owner | EN 50128 Clause |
|------------------|----------------|-----------------|
| "Physical" check — CI matches VCS and build artifacts | CM | §6.6, D.48 |
| Functional completeness — requirements satisfied per phase | VER | §6.2.4.7 |
| VER report documents identity/configuration of items verified | VER | §6.2.4.13(a) |
| VER evidence retained in format defined/referenced in SVP | CM (presence check) | §6.2.4.8 |
| Verification process complete | VAL | §6.3.4.9 |
| Baseline stated in Validation Report | VAL | §6.3.4.10 |
| CM records baseline under configuration control | CM | §9.1.4.2 |

**CM MUST NOT** use the terms FCA or PCA in any deliverable or report. Use EN 50128 terminology: "CM presence check" and "VER functional completeness check."

### 2.4 Roles and Responsibilities — Development Team

#### 2.4.1 All Development Agents (REQ, DES, IMP, INT, TST, SAF)

**Responsibilities**:
- **NEVER** write a document or evidence artifact without first calling CM `query-location` or `evidence-path` to obtain canonical path.
- Follow Git version control procedures per Section 8.
- Submit change requests for baseline modifications per Section 4.
- Update traceability information per `TRACEABILITY.md` when modifying requirements, design, code, or tests.
- Participate in CM presence checks at baseline (provide evidence artifacts).
- Maintain Git branch hygiene per Section 8.3.

#### 2.4.2 Verifier (VER)

**CM-Specific Responsibilities**:
- Perform functional completeness checks per §6.2.4.7 at each phase.
- Produce Verification Reports (Annex C items 2, 8, 14, 17, 19, 23, 40, 44) stating identity/configuration of items verified per §6.2.4.13(a).
- Check traceability T1–T15 technical completeness per §6.5.4.14–17; record findings in Verification Reports.
- Store verification evidence at CM canonical evidence paths (CM provides path via `evidence-path` capability).

**Independence**: MANDATORY independent from DES and IMP at SIL 3 per §5.1.2.10e.

#### 2.4.3 Validator (VAL)

**CM-Specific Responsibilities**:
- Check that verification process is complete per §6.3.4.9 before final validation.
- State the software baseline validated in Validation Report per §6.3.4.10 (Phase 7 only).
- Perform 2nd check on deliverables per `DELIVERABLES.md` Annex C Table C.1.

**Independence**: MANDATORY independent from all development roles at SIL 3 per §5.1.2.10f.

### 2.5 Independence Requirements (SIL 3)

Per EN 50128:2011 §5.1.2.10 and SQAP Section 1.5:

| Role | Independence Required | Reports To |
|------|----------------------|------------|
| **CM** | No (Annex B Table B.10) | PM |
| **VER** | **YES** (§5.1.2.10e — MANDATORY SIL 3) | VMGR |
| **VAL** | **YES** (§5.1.2.10f — MANDATORY SIL 3) | VMGR |
| **VMGR** | **YES** (independent from COD and PM — MANDATORY SIL 3) | Safety Authority |
| **QUA** | Yes (platform policy — not a normative EN 50128 requirement) | COD/PM |

**Organizational Evidence**: Organization chart demonstrating independence of VER, VAL, VMGR from development team shall be maintained in `docs/organization/org-chart.pdf` and reviewed quarterly.

---

## 3. CONFIGURATION IDENTIFICATION

### 3.1 Document-to-Phase Registry — CM Canonical Path Authority

CM maintains the **sole authoritative registry** of all deliverables and their canonical file system paths in `document-registry.yaml`. This registry is the runtime implementation of `DELIVERABLES.md` Annex C Table C.1.

**CM Capabilities**:
1. **query-location** — Given a document key (e.g., `SQAP`, `SRS`, `COMPTESTRPT`), return the canonical absolute path for that document.
2. **evidence-path** — Given an evidence type (e.g., `static-analysis`, `coverage`, `test-log`), return the canonical evidence storage path for the current phase.

**Mandatory Rule for All Agents**: Before writing ANY file, the agent MUST invoke CM via the task tool:
```
Task(subagent_type="cm", prompt="query-location --doc 'Software Requirements Specification'")
```
CM returns the canonical path. If an agent writes to a non-canonical path, CM raises a CRITICAL violation and invokes PM immediately.

### 3.2 Canonical Directory Layout

All TDC Software artifacts are stored under `examples/TDC/` with the following structure:

```
examples/TDC/
├── LIFECYCLE_STATE.md                     # COD-owned; CM tracks
├── changes/
│   └── CR-<YYYYMMDD>-<NNN>.md             # One file per change request
├── baselines/
│   └── <baseline-name>/
│       └── manifest.yaml                  # CI manifest per §9.1.4.2
│
├── docs/
│   ├── phase-1-planning/
│   │   ├── Software-Quality-Assurance-Plan.md
│   │   ├── Software-Configuration-Management-Plan.md        # This document
│   │   ├── Software-Verification-Plan.md
│   │   ├── Software-Validation-Plan.md
│   │   ├── reports/
│   │   │   └── Software-Quality-Assurance-Verification-Report.md
│   │   └── evidence/                      # No evidence in Phase 1
│   │
│   ├── phase-2-requirements/
│   │   ├── Software-Requirements-Specification.md
│   │   ├── Overall-Software-Test-Specification.md
│   │   ├── reports/
│   │   │   └── Software-Requirements-Verification-Report.md
│   │   └── evidence/                      # No evidence in Phase 2
│   │
│   ├── phase-3-architecture-design/
│   │   ├── Software-Architecture-Specification.md
│   │   ├── Software-Design-Specification.md
│   │   ├── Software-Interface-Specifications.md
│   │   ├── Software-Integration-Test-Specification.md
│   │   ├── Software-Hardware-Integration-Test-Specification.md
│   │   ├── reports/
│   │   │   └── Software-Architecture-and-Design-Verification-Report.md
│   │   └── evidence/
│   │       └── design-analysis/           # FMEA/FTA raw outputs (SAF-produced)
│   │
│   ├── phase-4-component-design/
│   │   ├── Software-Component-Design-Specification.md
│   │   ├── Software-Component-Test-Specification.md
│   │   ├── reports/
│   │   │   └── Software-Component-Design-Verification-Report.md
│   │   └── evidence/
│   │       └── design-review/             # Design inspection records (VER/DES-produced)
│   │
│   ├── phase-5-implementation-testing/
│   │   ├── src/                           # Source code tree (IMP-owned)
│   │   ├── Software-Source-Code-Verification-Report.md
│   │   ├── Software-Component-Test-Report.md
│   │   └── evidence/
│   │       ├── static-analysis/           # MISRA checker raw output (VER/IMP-produced)
│   │       ├── coverage/                  # gcov/lcov data files (TST/VER-produced)
│   │       ├── test-logs/                 # Unit test execution logs (TST-produced)
│   │       └── tool-qualification/        # Tool qualification evidence (VAL-produced)
│   │
│   ├── phase-6-integration/
│   │   ├── Software-Integration-Test-Report.md
│   │   ├── Software-Hardware-Integration-Test-Report.md
│   │   └── evidence/
│   │       ├── integration-test-logs/     # Integration test logs (INT/TST-produced)
│   │       └── hw-integration-logs/       # HW integration evidence (INT-produced)
│   │
│   ├── phase-7-validation/
│   │   ├── Software-Integration-Verification-Report.md
│   │   ├── Overall-Software-Test-Report.md
│   │   ├── Software-Validation-Report.md
│   │   ├── Tools-Validation-Report.md
│   │   ├── Release-Note.md
│   │   └── evidence/
│   │       ├── system-test-logs/          # System test logs (VAL/TST-produced)
│   │       └── validation-records/        # VAL evidence per §6.3.4
│   │
│   ├── phase-8-assessment/
│   │   ├── Software-Assessment-Plan.md
│   │   ├── Software-Assessment-Report.md
│   │   └── evidence/
│   │       └── assessor-records/          # ASR review notes (ASR-produced, CM stores)
│   │
│   ├── phase-9-deployment/
│   │   ├── Software-Release-and-Deployment-Plan.md
│   │   ├── Software-Deployment-Manual.md
│   │   ├── Release-Notes.md
│   │   ├── Deployment-Records.md
│   │   ├── Deployment-Verification-Report.md
│   │   └── evidence/
│   │       └── deployment-records/        # §9.1.4.13 deployment evidence (PM/VER-produced)
│   │
│   └── phase-10-maintenance/
│       ├── Software-Maintenance-Plan.md
│       ├── Software-Change-Records.md
│       ├── Software-Maintenance-Records.md
│       ├── Software-Maintenance-Verification-Report.md
│       └── evidence/
│           └── maintenance-logs/          # Change execution records (IMP/TST/VER-produced)
```

### 3.3 Configuration Items (CIs)

All software artifacts SHALL be identified as Configuration Items and placed under version control.

#### 3.3.1 Document CIs (46 Annex C Items)

| CI Type | Document Key | Naming Convention | Phase | Baseline Trigger |
|---------|--------------|-------------------|-------|------------------|
| Planning documents | SQAP, SCMP, SVP, SVaP | `DOC-{KEY}-2026-NNN` | 1 | Gate 1 (planning-baseline) |
| Requirements | SRS, OTSTSPEC | `DOC-{KEY}-2026-NNN` | 2 | Gate 2 (requirements-baseline) |
| Architecture & Design | SAS, SDS, INTERFACES | `DOC-{KEY}-2026-NNN` | 3 | Gate 3 (design-baseline) |
| Component Design | COMPDESIGN, COMPTESTSPEC | `DOC-{KEY}-2026-NNN` | 4 | Gate 4 (component-design-baseline) |
| Source Code | SOURCECODE | `src/module_name.{c,h}` | 5 | Gate 5 (implementation-baseline) |
| Integration | INTTESTRPT, HWINTTESTRPT | `DOC-{KEY}-2026-NNN` | 6 | Gate 6 (integration-baseline) |
| Validation | VALRPT, OVERALLTESTRPT | `DOC-{KEY}-2026-NNN` | 7 | Gate 7 (release-baseline) ★ |
| Assessment | ASSESSPLAN, ASSESSRPT | `DOC-{KEY}-2026-NNN` | 8 | No new baseline (ASR reviews release-baseline) |
| Deployment | DEPLOYPLAN, DEPLOYREC | `DOC-{KEY}-2026-NNN` | 9 | Gate 9 (deployment-baseline) |
| Maintenance | MAINTPLAN, CHANGEREC | `DOC-{KEY}-2026-NNN` | 10 | Per-CR baseline (per-cr-baseline) |

★ **release-baseline** (Gate 7) is the most critical baseline per §9.1.4.2–3. VALRPT SHALL state the baseline validated per §6.3.4.10. This baseline MUST be reproducible throughout the operational lifetime.

#### 3.3.2 Source Code CIs

| CI Type | Naming Convention | Location | Baseline Trigger |
|---------|-------------------|----------|------------------|
| C Header Files | `module_name.h` | `docs/phase-5-implementation-testing/src/` | Gate 5 |
| C Source Files | `module_name.c` | `docs/phase-5-implementation-testing/src/` | Gate 5 |
| Unit Test Files | `test_module_name.c` | `docs/phase-5-implementation-testing/src/tests/unit/` | Gate 5 |
| Integration Test Files | `test_integration_*.c` | `docs/phase-6-integration/tests/integration/` | Gate 6 |
| System Test Files | `test_system_*.c` | `docs/phase-7-validation/tests/system/` | Gate 7 |

#### 3.3.3 Evidence CIs (Mandatory SIL 3 per §6.2.4.8)

| Evidence Type | CM Evidence Path | Phase | Produced By |
|---------------|-----------------|-------|-------------|
| static-analysis | `phase-5-implementation-testing/evidence/static-analysis/` | 5 | VER, IMP |
| coverage | `phase-5-implementation-testing/evidence/coverage/` | 5 | TST, VER |
| unit-test-log | `phase-5-implementation-testing/evidence/test-logs/` | 5 | TST |
| tool-qualification | `phase-5-implementation-testing/evidence/tool-qualification/` | 5 | VAL |
| design-analysis | `phase-3-architecture-design/evidence/design-analysis/` | 3 | SAF |
| design-review | `phase-4-component-design/evidence/design-review/` | 4 | VER, DES |
| integration-test-log | `phase-6-integration/evidence/integration-test-logs/` | 6 | INT, TST |
| hw-integration-log | `phase-6-integration/evidence/hw-integration-logs/` | 6 | INT |
| system-test-log | `phase-7-validation/evidence/system-test-logs/` | 7 | VAL, TST |
| validation-record | `phase-7-validation/evidence/validation-records/` | 7 | VAL |
| assessor-record | `phase-8-assessment/evidence/assessor-records/` | 8 | ASR (CM stores) |
| deployment-record | `phase-9-deployment/evidence/deployment-records/` | 9 | PM, VER |
| maintenance-log | `phase-10-maintenance/evidence/maintenance-logs/` | 10 | IMP, TST, VER |

**CM Responsibility**: Initialize evidence directories before phase start using `evidence-init` capability. VER, TST, SAF MUST call CM `evidence-path` before storing any evidence artifact.

#### 3.3.4 Traceability CIs (Mandatory SIL 3)

| CI Type | Naming Convention | Location | Update Trigger |
|---------|-------------------|----------|----------------|
| Traceability Reports | `T{N}-{from}-to-{to}.md` | `docs/traceability/` | Every phase gate |
| Hazard Log | `Hazard-Log.md` | `docs/safety/` | Continuous (SAF updates) |

**Tool**: workspace.py trace command. VER checks T1–T15 technical completeness; CM maintains traceability reports under version control.

### 3.4 Version Numbering Scheme

**Format**: `MAJOR.MINOR.PATCH` (Semantic Versioning)

- **MAJOR**: Incremented for baseline releases (e.g., 1.0, 2.0) — triggered by COD gate-check PASS
- **MINOR**: Incremented for approved changes within baseline (e.g., 1.1, 1.2) — triggered by CCB-approved CR
- **PATCH**: Incremented for minor corrections (e.g., 1.0.1, 1.0.2) — editorial fixes, no technical content change

**Special Versions**:
- `0.x`: Draft versions (not yet approved; under QUA review)
- `1.0`: First approved baseline (Gate N passed; COD authorized)
- `2.0+`: Major baseline revisions (triggered by CCB-approved CR requiring re-entry to prior phase per §6.6.4.2)

**Examples**:
- `SRS-0.1` — Initial draft (REQ-authored, not yet QUA-passed)
- `SRS-0.5` — Draft under VER 1st check
- `SRS-1.0` — First approved baseline (Gate 2 passed, COD authorized)
- `SRS-1.1` — Approved change to baseline (CR-2026-042 implemented, CCB approved)
- `SRS-2.0` — Major baseline revision (CR-2026-089 required re-entry to Phase 2 per §6.6.4.2)

### 3.5 Document ID Convention

All documents use the format: `DOC-<ABBREV>-<YYYY>-<NNN>`

**Format Rules**:
- `<ABBREV>`: Document key from `document-registry.yaml` (e.g., SQAP, SRS, COMPTESTRPT)
- `<YYYY>`: Year (2026)
- `<NNN>`: Sequential number within year (001, 002, ...)

**Examples**:
- `DOC-SQAP-2026-001` — Software Quality Assurance Plan
- `DOC-SRS-2026-001` — Software Requirements Specification
- `DOC-COMPTESTRPT-2026-001` — Software Component Test Report

**QUA Check**: QUA verifies Document ID format compliance using regex: `DOC-[A-Z]+-\d{4}-\d{3}`.

---

## 4. CONFIGURATION CONTROL

### 4.1 Change Control Process — EN 50128 §6.6.4.1 Nine Required Aspects

**All changes to baselined Configuration Items SHALL follow this process and address all nine aspects (a–i) per EN 50128:2011 §6.6.4.1:**

```
Step 1: Change Request Submission
  │  (§6.6.4.1(a) — Unique identification)
  ▼
Step 2: CM Logs CR → Assign CR ID
  │  (§6.6.4.1(a) — Unique identification)
  ▼
Step 3: CM Impact Analysis
  │  (§6.6.4.1(c) — Analysis of consequences)
  │  (§6.6.4.1(f) — Recording of affected software items)
  ▼
Step 4: CCB Review and Decision
  │  (§6.6.4.1(b) — Recording of reasons)
  │  (§6.6.4.1(d) — Approval by authorized personnel)
  ▼
Step 5: Implementation (if approved)
  │  (§6.6.4.1(e) — Updating of all affected documents)
  │  (§6.6.4.1(g) — Implementation, verification, test)
  ▼
Step 6: Verification of Change
  │  (§6.6.4.1(g) — Verification and test of the change)
  ▼
Step 7: Update Baseline and Traceability
  │  (§6.6.4.1(i) — Maintaining traceability throughout lifecycle)
  ▼
Step 8: Configuration Status Accounting
  │  (§6.6.4.1(h) — Reporting to all relevant parties)
  ▼
Step 9: Re-entry to Lifecycle Phase (if required per §6.6.4.2)
```

**§6.6.4.2 Mandatory Re-entry**: ALL changes SHALL initiate a return to an appropriate lifecycle phase. CM identifies the re-entry scope; COD authorizes re-entry. See `WORKFLOW.md` Diagram 4 for CCB re-entry flow.

#### 4.1.1 Change Request Submission

**Who**: Any project member, customer, or stakeholder.

**Process**:
1. Create Change Request (CR) document using template (Appendix A).
2. CM assigns unique CR ID: `CR-<YYYYMMDD>-<NNN>` (§6.6.4.1(a)).
3. Submit to Configuration Manager via Git issue or `changes/` directory.
4. CM logs CR in Change Request Register (CSV or Markdown table).

**Required Information** (§6.6.4.1 compliance):
- **CR ID** (aspect a — unique identification)
- **Submitter name and date**
- **Affected CIs (by Document ID or file path)** (aspect f — affected software items)
- **Reason for change** (aspect b — recording of reasons)
- **Proposed solution (if known)**
- **Priority** (Critical / High / Medium / Low)
- **SIL impact assessment** (preliminary)

#### 4.1.2 CM Impact Analysis

**Who**: Configuration Manager (with input from technical leads: DES, VER, SAF).

**Process**:
1. Identify all affected CIs: requirements, design, code, tests, documentation (§6.6.4.1(f)).
2. Assess impact on (§6.6.4.1(c) — analysis of consequences):
   - **SIL level** — Does the change affect safety-critical requirements? Hazard Log update required?
   - **Requirements traceability** — Which traceability links (T1–T15) are affected?
   - **Verification and validation** — What re-verification is required? Coverage impact?
   - **Schedule and cost** — Effort estimate, critical path impact.
   - **Existing baselines** — Which baseline(s) must be modified?
   - **Re-entry phase** — Per §6.6.4.2, which phase must be re-entered? (CM identifies; COD authorizes)
3. Document analysis in CR (aspect c complete).
4. Schedule CCB review.

**Mandatory for SIL 3**: Impact on safety requirements (SAF consults), Hazard Log, traceability matrix (VER consults), FMEA/FTA if design change.

#### 4.1.3 CCB Review and Decision

**When**: Regular CCB meetings (weekly during active development for SIL 3); emergency session for critical safety-related changes.

**Process**:
1. CM presents CR and impact analysis (CM is CCB Secretary).
2. CCB discusses technical, safety, schedule implications.
3. VER assesses verification impact (MANDATORY for safety-critical CRs at SIL 3).
4. SAF assesses safety impact if CR affects safety-critical requirements.
5. CCB votes: **Approve** / **Reject** / **Defer** (pending more information).
6. CM records decision in CCB minutes and CR document (§6.6.4.1(d) — approval by authorized personnel).
7. CM notifies submitter and affected parties (§6.6.4.1(h) — reporting to all relevant parties).

**Approval Criteria**:
- Technical feasibility confirmed (DES/IMP assessment)
- No adverse safety impact (or justified with Safety Authority approval)
- Traceability maintained (VER confirms re-verification plan)
- Verification plan updated (VER confirms scope)
- Resources available (PM confirms)
- Re-entry phase identified per §6.6.4.2 (CM identifies; COD will authorize)

**Decision Record**: CCB minutes stored in `changes/CCB-Minutes-<YYYYMMDD>.md` under CM control.

#### 4.1.4 Implementation

**Who**: Assigned developer(s) — DES, IMP, INT, TST depending on affected CIs.

**Process**:
1. Create feature/bugfix branch from `develop` per Section 8.3.
2. Implement changes following coding standards (MISRA C:2012 for SIL 3).
3. Update affected CIs: code, documentation, tests, traceability (§6.6.4.1(e) — updating of all affected documents).
4. Commit with reference to CR ID in commit message (§6.6.4.1(a) — traceability of change).
5. Create pull request for VER review.

**Commit Message Format**:
```
[CR-YYYYMMDD-NNN] Brief description of change

- Detailed explanation
- Affected modules: module_name.c, module_name.h
- Traceability: REQ-FUNC-001 → MOD-001 → test_module.c (T7, T12 updated)
- SIL impact: None / Minor / Requires re-verification
- Verification evidence: [link to VER evidence]
```

#### 4.1.5 Verification of Change

**Who**: Verifier (VER) — independent for SIL 3 per §5.1.2.10e.

**Process** (§6.6.4.1(g) — verification and test of the change):
1. Review pull request for code quality, MISRA C compliance (SIL 3 MANDATORY).
2. Run static analysis (cppcheck, PC-lint) — check for new violations.
3. Execute affected tests (unit, integration, system as appropriate).
4. Verify coverage requirements met per Table A.21 (SIL 3: branch + compound condition or data flow).
5. Update verification evidence; store at CM canonical evidence path.
6. Update traceability matrix (T1–T15 as affected).
7. Approve pull request if all checks pass; otherwise reject with findings.

**Mandatory Checks (SIL 3)**:
- MISRA C:2012 compliance — 100% (deviations justified per MISRA deviation procedure)
- Cyclomatic complexity ≤ 10 per function (SIL 3 limit)
- Traceability updated (T1–T15 checked; RTM reflects changes per §6.6.4.1(i))
- Test coverage maintained (per Table A.21 — branch + MC/DC for safety-critical modules)

**VER Output**: Verification evidence stored at canonical path; pull request approval recorded in Git.

#### 4.1.6 Update Baseline and Traceability

**Who**: Configuration Manager (after VER approval and CCB confirmation).

**Process**:
1. Merge approved pull request to `develop` (or directly to `main` for hotfix).
2. Update Configuration Status Accounting log (§6.6.4.1(h) — reporting).
3. Update Requirements Traceability Matrix (SIL 3 MANDATORY per §6.6.4.1(i) — maintaining traceability).
4. Tag new baseline version if change triggers new release per Section 7.
5. Archive old baseline version in `baselines/<old-baseline-name>/`.
6. Create new baseline manifest (manifest.yaml) listing all CIs with updated versions per §9.1.4.2.

#### 4.1.7 Configuration Status Accounting

**Who**: Configuration Manager.

**Process**:
1. Record change in Configuration Status Report (Section 5.1).
2. Update CI status in version control (Git tag, branch merge).
3. Notify stakeholders of baseline change per §6.6.4.1(h) (PM, COD, VMGR, Safety Authority if safety-critical).
4. Update project documentation index.
5. Close CR in Change Request Register.

**Output**: Software Change Record per §9.2.4 (stored in `changes/CR-<YYYYMMDD>-<NNN>.md`).

#### 4.1.8 Re-entry to Lifecycle Phase (§6.6.4.2)

**Normative Requirement**: EN 50128:2011 §6.6.4.2 states: "ALL changes, whether corrective, perfective, or adaptive, shall initiate a return to an appropriate phase of the software development lifecycle."

**Process**:
1. CM identifies re-entry phase based on affected CIs:
   - **Requirements change** → Re-enter Phase 2 (Requirements)
   - **Design change** → Re-enter Phase 3 (Architecture) or Phase 4 (Component Design)
   - **Code change** → Re-enter Phase 5 (Implementation)
   - **Test change** → Re-enter relevant test phase (5, 6, or 7)
2. CM documents re-entry scope in Software Change Record.
3. CM requests COD authorization for re-entry (COD has lifecycle authority).
4. COD invokes PM to execute re-entry phase per `WORKFLOW.md` Diagram 4.
5. Re-entry phase follows normal phase execution: deliverable update → QUA check → VER 1st check → VAL 2nd check → VMGR review (if SIL 3) → COD gate-check.
6. Upon COD gate-check PASS, CM creates per-CR baseline or updates existing baseline.

**See Also**: `WORKFLOW.md` Diagram 4 (CCB change request re-entry flow); `activities/baseline-management.yaml` `change_request_baseline_path` for machine-readable CR re-entry steps.

---

## 5. CONFIGURATION STATUS ACCOUNTING

### 5.1 Configuration Status Reports

**Frequency**:
- **SIL 3**: Bi-weekly (MANDATORY per Table A.9 Technique 8 — Data Recording and Analysis)

**Report Contents** (per §6.6.3):
1. List of all CIs with current version and baseline status.
2. Baseline status: established, modified, released.
3. Pending change requests (open CRs with status).
4. Recently approved changes (closed CRs this period).
5. Build status (latest build number, result, test pass rate).
6. Defect summary (open defects by severity).
7. Traceability status (SIL 3 MANDATORY) — T1–T15 coverage percentage.

**Distribution**: Project Manager, QA Manager (QUA), Lifecycle Coordinator (COD), VMGR, CCB members.

**Format**: Markdown report stored in `docs/configuration/Configuration-Status-Report-<YYYYMMDD>.md` under CM control.

**Template**: See Appendix B.

### 5.2 Traceability Management (Mandatory SIL 3)

**EN 50128 Requirement**: Table A.9 Technique 6 (Traceability) is **MANDATORY** for SIL 3.

**Traceability Chain** (per `TRACEABILITY.md`):

```
System Requirements (S1, S4)
  ↓ T1
Software Requirements (SRS)
  ↓ T2                        ↓ T3
Overall Test Spec (OTSTSPEC)  Software Architecture (SAS)
                              ↓ T4
                              Software Design (SDS)
                              ↓ T5a, T5b, T5c
                              Integration Test Specs + Interface Specs
                              ↓ T6
                              Software Component Design
                              ↓ T7              ↓ T8
                              Source Code       Component Test Spec
                              ↓ T12             ↓ T11
                              Component Test Report
                              ↓ T10a, T10b      ↓ T14
                              Integration Test Report
                              ↓ T15
                              Overall Test Report
                              ↓ T13
                              Validation Report
```

**VER Responsibility**: Check technical completeness of T1–T15 per §6.5.4.14–17; record findings in Verification Reports.

**CM Responsibility**: Maintain traceability reports under version control; update traceability at every CR closure per §6.6.4.1(i).

**Tool**: workspace.py trace command.

**Usage Examples**:
```bash
# Check T1 traceability (System Req → SW Req)
python3 tools/workspace.py trace T1 --from SYS-REQ-001 --to REQ-FUNC-001

# Check T7 traceability (Component Design → Code)
python3 tools/workspace.py trace T7 --from COMP-001 --to src/door_control.c

# Generate traceability coverage report (all T1–T15)
python3 tools/workspace.py trace --coverage
```

**Output**: Traceability reports stored in `docs/traceability/` under CM control; included in baseline manifest at each gate.

### 5.3 Data Recording and Analysis (Mandatory SIL 3)

**EN 50128 Requirement**: Table A.9 Technique 8 (Data Recording and Analysis) is **MANDATORY** for SIL 3.

**Recorded Data**:

| Metric | Description | Frequency | Reported To |
|--------|-------------|-----------|-------------|
| **Change request metrics** | CR count, type (corrective/perfective/adaptive), priority, resolution time | Per CR closure | PM, QUA, COD |
| **Defect metrics** | Defect count, severity, phase detected, root cause, closure time | Per defect closure | PM, QUA, VER |
| **Build metrics** | Build success rate, build time, build failures by cause | Per build | CM, PM |
| **Test metrics** | Test pass rate, coverage (statement/branch/MC/DC), defect density | Per test execution | TST, VER |
| **Review metrics** | Review findings count, review effort (hours), review coverage | Per review | VER, QUA |
| **Traceability metrics** | T1–T15 coverage percentage, orphaned requirements/tests count | Per phase gate | VER, CM |

**Analysis Frequency**: Monthly (minimum for SIL 3).

**Analysis Output**: Configuration Status Report includes trend analysis; escalate to PM if metrics exceed thresholds.

**Tool**: CSV-based tracking in `docs/configuration/Metrics-<YYYYMM>.csv`; CM generates summary reports.

---

## 6. CONFIGURATION AUDITS

### 6.1 CM Presence Checks at Baseline (EN 50128 Terminology)

**Purpose**: Verify that required signed documents and evidence artifacts are present at canonical paths, correctly versioned, and stored per SCMP.

**When**: Before each baseline creation (Gates 1–9).

**Scope** (CM checks presence only — not technical correctness):
1. All required deliverables for this phase present at canonical paths per `document-registry.yaml`.
2. Document IDs match naming convention per Section 3.5.
3. Version numbers match Section 3.4 scheme.
4. Approvals table complete with required signatures (Author, 1st Check, 2nd Check, Approver).
5. Evidence artifacts exist in canonical evidence directories per Section 3.3.3.
6. VER Verification Report present and states identity/configuration of items verified per §6.2.4.13(a).
7. VAL 2nd check complete per `DELIVERABLES.md` Annex C Table C.1.
8. Git repository tag matches baseline version per Section 7.

**Auditor**: Configuration Manager (all SIL levels).

**Deliverable**: CM Presence Check Report (stored in `baselines/<baseline-name>/CM-Presence-Check-Report.md`).

**CM Does NOT Check**:
- Technical correctness of requirements, design, or code (VER responsibility per §6.2.4.7).
- Functional completeness — requirements satisfied per phase (VER responsibility per §6.2.4.7).
- Test adequacy or coverage figures (VER responsibility; CM only checks evidence exists).

### 6.2 VER Functional Completeness Check (EN 50128 §6.2.4.7)

**Purpose**: Verify that software functionality matches requirements and design specifications per §6.2.4.7.

**When**: During each phase; findings recorded in Verification Report at phase completion.

**Scope** (VER responsibility):
1. Requirements traceability complete (T1–T15 technical completeness per §6.5.4.14–17).
2. All tests passed (test evidence reviewed).
3. Verification evidence complete (static analysis, coverage, complexity reports meet SIL 3 criteria).
4. Safety requirements verified (if applicable — SAF consults).
5. MISRA C compliance verified (SIL 3 MANDATORY).
6. Identity/configuration of items verified stated in VER Verification Report per §6.2.4.13(a).

**Auditor**: Verifier (VER) — independent from DES and IMP at SIL 3 per §5.1.2.10e.

**Deliverable**: VER Verification Report (Annex C items 2, 8, 14, 17, 19, 23, 40, 44).

### 6.3 VAL Verification-Complete Check (EN 50128 §6.3.4.9–10)

**Purpose**: 
- §6.3.4.9: Check that verification process is complete before final validation.
- §6.3.4.10: State the software baseline validated in Validation Report (Phase 7 only).

**When**: Phase 7 (Validation); also VAL performs 2nd check on deliverables per `DELIVERABLES.md` in other phases.

**Scope** (VAL responsibility):
1. VER Verification Report complete and VMGR-approved (SIL 3).
2. All verification evidence present (CM confirms presence; VAL confirms VER completeness per §6.3.4.9).
3. Software baseline identified — VAL states baseline in Validation Report per §6.3.4.10.
4. System requirements validated (traceability T13: SRS → Validation Report).
5. Acceptance criteria met.

**Auditor**: Validator (VAL) — independent from all development roles at SIL 3 per §5.1.2.10f.

**Deliverable**: VAL Validation Report (Annex C item 25 — Phase 7 only). In other phases, VAL performs 2nd check and annotates deliverables per `DELIVERABLES.md`.

### 6.4 Baseline Verification Process

**Seven-Step Procedure** (per `tasks/BASELINE_MANAGEMENT.md` Diagram 2):

```
Step 1: COD Gate-Check PASS
  │  Trigger: All phase deliverables QUA-passed; VER report VMGR-approved (SIL 3)
  ▼
Step 2: CM Presence Check
  │  CM verifies: documents present at canonical paths; evidence artifacts exist; approvals complete
  ▼
Step 3: CM Creates Baseline Manifest
  │  manifest.yaml lists all CIs with version, path, SHA-256 hash per §9.1.4.2
  ▼
Step 4: CM Tags VCS
  │  Git annotated tag: v<MAJOR>.<MINOR>.<PATCH> with baseline metadata
  ▼
Step 5: CM Archives Baseline
  │  Copy manifest + all CIs to baselines/<baseline-name>/
  ▼
Step 6: CM Notifies Stakeholders
  │  Notification to PM, COD, VMGR, Safety Authority (if applicable)
  ▼
Step 7: CCB Formal Baseline Approval
  │  CCB reviews CM Presence Check Report; approves baseline; CM records in CCB minutes
```

**Preconditions** (CM checks before Step 2):
- COD gate-check status = PASS (read from LIFECYCLE_STATE.md).
- VER Verification Report present and VMGR-approved (SIL 3).
- VAL 2nd check complete per `DELIVERABLES.md` (if applicable).
- Zero CRITICAL NCRs open (QUA confirms).

**Postconditions**:
- Baseline manifest archived in `baselines/<baseline-name>/manifest.yaml`.
- Git tag created and pushed to remote.
- Configuration Status Report updated.
- LIFECYCLE_STATE.md updated with baseline record.

---

## 7. BASELINE MANAGEMENT

### 7.1 Eight Baselines Across Phases 1–9

Per `tasks/BASELINE_MANAGEMENT.md` Diagram 1, one baseline is created at each COD phase gate:

| Gate | Phase | Baseline Name | Content Scope | VER Report | VAL Role |
|------|-------|---------------|---------------|------------|----------|
| **Gate 1** | Planning | `planning-baseline` | SQAP, SCMP, SVP, SVaP (items 1–5) | SQAVR (item 2) | 2nd check (items 1, 3, 4 only; item 5 exempt) |
| **Gate 2** | Requirements | `requirements-baseline` | SRS, OTSTSPEC, REQVER (items 6–8) | REQVER (item 8) | 2nd check (items 6–7) |
| **Gate 3** | Architecture & Design | `design-baseline` | SAS, SDS, INTERFACES, INTTESTSPEC, HWINTTESTSPEC, ARCHDESIGNVER (items 9–14) | ARCHDESIGNVER (item 14) | 2nd check (items 9–13) |
| **Gate 4** | Component Design | `component-design-baseline` | COMPDESIGN, COMPTESTSPEC, COMPDESIGNVER (items 15–17) | COMPDESIGNVER (item 17) | 2nd check (items 15–16) |
| **Gate 5** | Implementation & Testing | `implementation-baseline` | Source code, SOURCECODEVER, COMPTESTRPT, evidence (items 18–20) | SOURCECODEVER (item 19) | 2nd check (item 18, 20) |
| **Gate 6** | Integration | `integration-baseline` | INTTESTRPT, HWINTTESTRPT, evidence (items 21–22) | VER review (item 23 produced in Phase 7) | 2nd check (items 21–22) |
| **Gate 7** | Validation | `release-baseline` ★ | INTVER, OVERALLTESTRPT, VALRPT, TOOLSVALRPT, RELEASENOTE, evidence (items 23–27) | INTVER (item 23) | Formal VALRPT (item 25) per §6.3.4.10 |
| **Gate 9** | Deployment | `deployment-baseline` | DEPLOYPLAN, DEPLOYMAN, RELEASENOTES, DEPLOYREC, DEPLOYVER, evidence (items 36–40) | DEPLOYVER (item 40) | 2nd check (items 36–39 only; item 40 exempt) |

**★ release-baseline (Gate 7)** is the most critical:
- §6.3.4.10: VALRPT SHALL state the software baseline validated.
- §9.1.4.2: Baseline SHALL be recorded under CM control before delivery.
- §9.1.4.3: Release SHALL be reproducible throughout the operational lifetime.

**Phase 8 (Assessment)**: No new baseline. ASR reviews `release-baseline` artifacts; CM provides read-only access.

**Phase 10 (Maintenance)**: Per-CR baseline created for each CCB-approved change request per §6.6.4.2 re-entry.

### 7.2 Baseline Creation Procedure

**Trigger**: COD gate-check PASS (COD command: `@cod gate-check <phase>` returns status PASS).

**Procedure** (Seven Steps — see Section 6.4 for detailed flow):

1. **COD Gate-Check PASS** — Preconditions verified by COD.
2. **CM Presence Check** — CM verifies documents and evidence present at canonical paths.
3. **CM Creates Baseline Manifest** — manifest.yaml per Section 7.3.
4. **CM Tags VCS** — Git annotated tag per Section 8.4.
5. **CM Archives Baseline** — Copy to `baselines/<baseline-name>/`.
6. **CM Notifies Stakeholders** — Email to PM, COD, VMGR, Safety Authority (if safety-critical).
7. **CCB Formal Approval** — CCB reviews CM Presence Check Report; PM (CCB Chair) approves baseline.

**RACI** (per `activities/baseline-management.yaml`):
- **Responsible**: CM (executes Steps 2–6)
- **Accountable**: PM (CCB Chair approves Step 7)
- **Consulted**: VER (functional completeness per §6.2.4.7), VAL (verification-complete check per §6.3.4.9)
- **Informed**: COD, VMGR, Safety Authority

### 7.3 Baseline Manifest Format

**File**: `baselines/<baseline-name>/manifest.yaml`

**Purpose**: Record all CIs in the baseline per §9.1.4.2; enable reproducibility per §9.1.4.3.

**Format**:
```yaml
baseline:
  name: planning-baseline
  gate: 1
  phase: Planning
  date: 2026-04-02
  sil: 3
  cod_authorization: PASS
  ccb_approval_date: 2026-04-02
  ccb_approval_reference: CCB-Minutes-20260402

configuration_items:
  - document_key: SQAP
    document_id: DOC-SQAP-2026-001
    version: 1.0
    path: docs/phase-1-planning/Software-Quality-Assurance-Plan.md
    sha256: <hash>
    author: QUA
    first_check: VER
    second_check: VAL
    approver: PM
    
  - document_key: SCMP
    document_id: DOC-SCMP-2026-001
    version: 1.0
    path: docs/phase-1-planning/Software-Configuration-Management-Plan.md
    sha256: <hash>
    author: CM
    first_check: VER
    second_check: VAL
    approver: PM

  # ... (all CIs in this baseline)

git_tag: v1.0.0
git_commit_sha: <commit-hash>

verification_evidence:
  - ver_report: DOC-SQAVR-2026-001
    path: docs/phase-1-planning/reports/Software-Quality-Assurance-Verification-Report.md
    vmgr_approved: true
    vmgr_approval_date: 2026-04-02

traceability_status:
  - T1: not applicable (no system-to-SW traceability in Phase 1)
  - T2: not applicable (no SRS in Phase 1)
  # ... (T1–T15 status per phase)

cm_presence_check:
  status: PASS
  report: baselines/planning-baseline/CM-Presence-Check-Report.md
  date: 2026-04-02
  auditor: CM
```

**Reproducibility Evidence** (§9.1.4.3):
- Git tag and commit SHA enable exact source checkout.
- SHA-256 hashes of all CIs enable integrity verification.
- Manifest stored in baselines/ directory under CM control; archived off-site.

### 7.4 Baseline Modification

**Process**: All baseline modifications SHALL go through Change Control per Section 4.

**§6.6.4.2 Re-entry**: CM identifies re-entry phase; COD authorizes re-entry; PM executes phase per `WORKFLOW.md` Diagram 4.

**SIL 3 Additional Requirements**:
- Independent impact analysis required (VER performs).
- Safety assessment for safety-critical CIs (SAF performs).
- Re-verification evidence required (VER produces; CM archives at canonical evidence path).
- Traceability matrix update mandatory (VER checks T1–T15; CM updates RTM per §6.6.4.1(i)).

**Output**: New baseline or updated baseline manifest with incremented version number (MAJOR or MINOR per Section 3.4).

---

## 8. VERSION CONTROL STRATEGY

### 8.1 Version Control System

**Tool**: Git

**Repository Location**: [To be specified: GitHub Enterprise, GitLab self-hosted, or local Git server]

**Access Control**:
- **Read access**: All project members
- **Write access**: Developers (REQ, DES, IMP, INT, TST, SAF) via pull request workflow only
- **Admin access**: Configuration Manager (CM), Project Manager (PM)
- **Protected branches**: `main`, `release/*` (require CCB approval for merges)

**Backup**: Daily automated backup to off-site location; CM verifies backup integrity weekly.

**Repository Structure**:
```
tdc-software/  (Git repository root)
├── .git/
├── docs/
│   ├── phase-1-planning/
│   ├── phase-2-requirements/
│   └── ... (all phase directories)
├── baselines/
├── changes/
├── LIFECYCLE_STATE.md
└── README.md
```

### 8.2 Git Configuration

**Commit Signing**: MANDATORY for SIL 3 — all commits SHALL be GPG-signed.

**Commit Message Format**: See Section 4.1.4.

**Pre-commit Hooks** (SIL 3 enforced via Git hooks):
1. Check commit message format (CR ID reference required for baselined branches).
2. Run MISRA C checker (cppcheck) on modified .c/.h files.
3. Block commit if MISRA violations detected (unless deviation recorded).
4. Check Document ID format if modifying .md files in docs/.

### 8.3 Branch Strategy

**Branch Structure**:
```
main (protected — production-ready code, tagged baselines only)
  ├── develop (integration branch for ongoing development)
  │   ├── feature/REQ-001-door-control-logic
  │   ├── feature/REQ-002-emergency-stop
  │   ├── bugfix/BUG-042-sensor-timeout
  │   └── hotfix/CRIT-089-safety-fault
  ├── release/v1.0 (baseline branch — Gate 7 preparation)
  └── release/v2.0 (baseline branch — future major release)
```

**Branch Types**:
- **`main`**: Production-ready code; only accepts merges from `release/*` or `hotfix/*`; every merge = baseline; tagged with version per Section 8.4.
- **`develop`**: Integration branch for ongoing development; merges from `feature/*` and `bugfix/*`; tested before merging to `release/*`.
- **`feature/*`**: New feature development (from `develop`); naming: `feature/<REQ-ID>-<short-description>`.
- **`bugfix/*`**: Non-critical bug fixes (from `develop`); naming: `bugfix/<BUG-ID>-<short-description>`.
- **`hotfix/*`**: Critical fixes for production (from `main`); naming: `hotfix/<CRIT-ID>-<short-description>`; merged back to both `main` and `develop`.
- **`release/*`**: Baseline preparation and maintenance (from `develop`); naming: `release/v<MAJOR>.<MINOR>`; no new features after branch creation; only bugfixes allowed.

**Branch Protection Rules** (SIL 3 enforced via Git server):

| Branch | Rule |
|--------|------|
| `main` | Require pull request reviews (≥2 reviewers: VER + VAL for SIL 3) |
| `main` | Require status checks to pass (build, unit tests, MISRA C, coverage threshold) |
| `main` | Require CCB approval for merges (PM or CM approval required) |
| `main` | Restrict force push (CRITICAL violation if attempted — CM invokes PM immediately) |
| `main` | Restrict tag deletion (CRITICAL violation if attempted — requires CCB approval + Change Record per §6.6.4.1) |
| `release/*` | Require pull request reviews (≥1 reviewer: VER for SIL 3) |
| `release/*` | Require CCB approval for merges |
| `develop` | Require pull request reviews (≥1 reviewer) |
| `feature/*`, `bugfix/*` | No protection (developers may commit directly; PR required to merge to `develop`) |

### 8.4 Tagging Strategy

**Format**: `v<MAJOR>.<MINOR>.<PATCH>[-<METADATA>]`

**Tag Types**:

| Tag Type | Example | Branch | When | Annotated? |
|----------|---------|--------|------|-----------|
| **Baseline tags** | `v1.0.0` | `main` | COD gate-check PASS; baseline approved | Yes (required) |
| **Release candidate tags** | `v1.0.0-rc1` | `release/*` | Baseline preparation; pre-validation | Yes |
| **Phase gate tags** | `phase2-gate` | `main` | Each gate pass (in addition to version tag) | Yes |

**Required Metadata for Baseline Tags** (Git annotated tag message):
```
Baseline: planning-baseline
SIL: 3
Phase: 1 (Planning)
Date: 2026-04-02
COD Authorization: PASS (gate-check planning)
CCB Approval: CCB-Minutes-20260402
Author: Configuration Manager (CM)
VER Report: DOC-SQAVR-2026-001 (VMGR-approved)
VAL 2nd Check: Complete (items 1, 3, 4)
Manifest: baselines/planning-baseline/manifest.yaml
```

**Tagging Command Example**:
```bash
git tag -a v1.0.0 -m "Baseline: planning-baseline\nSIL: 3\nPhase: 1\nDate: 2026-04-02\nCOD Authorization: PASS\nCCB Approval: CCB-Minutes-20260402"
git push origin v1.0.0
```

**Tag Protection**: Tags on `main` CANNOT be deleted or modified without CCB approval + Software Change Record per §6.6.4.1.

---

## 9. BUILD AND RELEASE MANAGEMENT

### 9.1 Build Process

**Build Automation**: Continuous Integration (CI) pipeline triggered on every commit to `develop`, `release/*`, and `main`.

**Build Steps**:
1. Checkout code from Git.
2. Compile source code with GCC (with MISRA C flags for SIL 3).
3. Run static analysis (cppcheck, PC-lint Plus — see Section 10.2).
4. Run unit tests (Unity framework).
5. Generate coverage report (gcov/lcov — SIL 3 target: ≥95% statement, ≥90% branch).
6. Check cyclomatic complexity (lizard — SIL 3 limit: ≤10 per function).
7. Archive build artifacts (executable, libraries, coverage report, static analysis report).

**Build Verification Criteria** (SIL 3 — all must pass before merge to `main`):
- ✓ All unit tests pass (100% pass rate).
- ✓ MISRA C compliance clean (zero violations; deviations justified per MISRA deviation procedure).
- ✓ Static analysis clean (no critical/high issues).
- ✓ Coverage thresholds met (≥95% statement, ≥90% branch; MC/DC for safety-critical modules).
- ✓ Complexity within limits (cyclomatic complexity ≤10 per function).

**Build Logs**: Archived in `docs/phase-5-implementation-testing/evidence/build-logs/` under CM control.

**Tools**:
- Make / CMake (build automation)
- GCC with `-std=c11 -Wall -Wextra -pedantic -Werror` flags
- PC-lint Plus (MISRA C checker — T2 tool, requires qualification per §6.7)
- cppcheck (static analyzer — T2 tool, requires qualification per §6.7)

### 9.2 Release Process

**Three-Phase Release** (per `release-baseline` at Gate 7):

#### Phase 1: Release Candidate Creation
1. Branch from `develop` to `release/v<MAJOR>.<MINOR>`.
2. Tag release candidate: `v<MAJOR>.<MINOR>.0-rc1`.
3. Perform integration testing (Phase 6).
4. Perform system/acceptance testing (Phase 7 — VAL executes).
5. Fix critical issues only; no new features after RC creation.
6. Tag subsequent RCs if needed: `v<MAJOR>.<MINOR>.0-rc2`, etc.

#### Phase 2: Release Approval
1. Complete verification (VER produces INTVER — item 23).
2. Complete validation (VAL produces VALRPT — item 25, stating baseline per §6.3.4.10).
3. Complete tool validation if applicable (VAL produces TOOLSVALRPT — item 26).
4. QUA checks format of VER/VAL reports (1-Pass Rule).
5. VMGR reviews VER and VAL reports (SIL 3 MANDATORY).
6. VMGR approves (final V&V decision — cannot be overridden by COD or PM).
7. COD gate-check: `@cod gate-check validation`.
8. CCB approves release (PM chairs; CM records decision).

#### Phase 3: Release Baseline Creation
1. Merge `release/v<MAJOR>.<MINOR>` to `main`.
2. CM tags final release: `v<MAJOR>.<MINOR>.0` with baseline metadata.
3. CM creates release-baseline manifest per Section 7.3.
4. CM archives release package per Section 9.3.
5. CM creates Release Notes (item 27).
6. CM notifies stakeholders (PM, COD, VMGR, Safety Authority, Customer).

### 9.3 Release Package Contents

**Release Package**: Comprehensive archive enabling reproducibility per §9.1.4.3.

**Contents**:

| Category | Items | Location in Package |
|----------|-------|-------------------|
| **Source Code** | All .c/.h files with supporting documentation | `src/` |
| **Compiled Binaries** | Executable, libraries | `bin/` |
| **Documentation** | All 27 Phase 1–7 deliverables (items 1–27) | `docs/` |
| **Verification Evidence** | VER reports (items 2, 8, 14, 17, 19, 23); static analysis reports; coverage reports | `evidence/verification/` |
| **Validation Evidence** | VAL report (item 25); Tools VAL report (item 26); system test logs | `evidence/validation/` |
| **Traceability Matrix** | T1–T15 traceability reports; RTM | `docs/traceability/` |
| **Test Evidence** | Test specifications, test reports, test logs | `evidence/testing/` |
| **Configuration Data** | Baseline manifest; Configuration Status Report | `configuration/` |
| **Build Instructions** | Makefile, build scripts, build README | `build/` |
| **Deployment Instructions** | Deployment Manual (item 37 — created in Phase 9) | `deployment/` |
| **Safety Evidence** | Hazard Log, FMEA/FTA reports, Safety Case | `safety/` |
| **Git Metadata** | Git tag, commit SHA, branch history | `git-metadata.txt` |

**Archive Format**: Compressed tarball (`.tar.gz`) or ZIP with SHA-256 hash for integrity verification.

**Archive Location**: `baselines/release-baseline/release-package-v<MAJOR>.<MINOR>.0.tar.gz`

**Backup**: Off-site backup maintained for entire operational lifetime per §9.1.4.3.

---

## 10. TOOLS AND INFRASTRUCTURE

### 10.1 Configuration Management Tools

| Tool | Purpose | Classification | Qualification Required? | Used By |
|------|---------|---------------|------------------------|---------|
| **Git** | Version control | T1 (platform tool) | No (§6.7.4.4.2) | CM, all agents |
| **workspace.py** | Lifecycle state tracking, traceability checking | T1 (platform tool) | No (§6.7.4.4.2) | COD, CM, QUA, VER |
| **Make / CMake** | Build automation | T1 (build tool) | No | CM, IMP |
| **Markdown editors** | Document authoring | T1 (editor) | No | All agents |

**Platform Tools** (T1 per §6.7.4.4.2): Git and workspace.py are platform-provided; treated as T1 (no separate qualification required beyond platform validation).

### 10.2 Development and Verification Tools (SIL 3 — Qualification Required)

| Tool | Purpose | Classification | Qualification Required? | Qualification Evidence |
|------|---------|---------------|------------------------|----------------------|
| **GCC** | C compiler | T3 (code-generating tool) | **YES** (§6.7.4.4.4) | Compiler validation report; comparison with reference compiler |
| **PC-lint Plus** | MISRA C checker | T2 (verification tool) | **YES** (§6.7.4.4.3) | Tool validation report (item 26 — Phase 7) |
| **cppcheck** | Static analyzer | T2 (verification tool) | **YES** (§6.7.4.4.3) | Tool validation report (item 26 — Phase 7) |
| **gcov / lcov** | Coverage analysis | T2 (verification tool) | **YES** (§6.7.4.4.3) | Tool validation report (item 26 — Phase 7) |
| **lizard** | Complexity analysis | T2 (verification tool) | **YES** (§6.7.4.4.3) | Tool validation report (item 26 — Phase 7) |
| **Unity** | Unit test framework | T2 (verification tool) | **YES** (§6.7.4.4.3) | Tool validation report (item 26 — Phase 7) |

**Tool Qualification Evidence**: VAL produces Tools Validation Report (item 26) in Phase 7; VER performs 1st check; VMGR reviews (SIL 3). Qualification evidence stored at `docs/phase-7-validation/Tools-Validation-Report.md` and `docs/phase-5-implementation-testing/evidence/tool-qualification/`.

**Reference**: See `TOOLS.md` for complete tool catalog and Agent Tool Usage Protocol.

### 10.3 Traceability Tool — workspace.py

**Tool**: `workspace.py` (Python script in `tools/` directory)

**Capabilities** (relevant to CM):
- **trace**: Check traceability links T1–T15; generate coverage reports.
- **wf**: Workflow status queries (used by COD; CM reads LIFECYCLE_STATE.md).
- **cm**: CM capabilities (query-location, evidence-path, baseline, change-request, status-accounting).

**Usage Examples for CM**:
```bash
# Query canonical path for a document
python3 tools/workspace.py cm query-location --doc "Software Requirements Specification"

# Query canonical evidence path
python3 tools/workspace.py cm evidence-path --type "static-analysis"

# Create baseline
python3 tools/workspace.py cm baseline --name "planning-baseline" --gate 1

# Generate configuration status report
python3 tools/workspace.py cm status-accounting --period "2026-04-01:2026-04-15"
```

**Reference**: See `en50128-lifecycle-tool-integration` skill → workspace.py command reference.

---

## 11. TRAINING AND COMPETENCE

### 11.1 Required Training

All project personnel SHALL receive training on configuration management procedures:

| Role | Training Topic | Frequency | Evidence |
|------|----------------|-----------|----------|
| **CM** | EN 50128 §6.6 Configuration Management; SCMP procedures; Git advanced usage; baseline creation; CCB administration | Initial + annual refresher | Training certificate; SCMP quiz (>80%) |
| **VER** | Traceability checking (T1–T15); workspace.py trace command; functional completeness per §6.2.4.7 | Initial + annual refresher | Training certificate; traceability audit evidence |
| **All Developers** | Git workflow; branch strategy; pull request process; commit message format; SCMP Section 3–4 (CI identification, change control) | Initial (project onboarding) + refresher as needed | Training attendance record |
| **CCB Members** | Change impact analysis; §6.6.4.1 nine aspects; §6.6.4.2 re-entry procedure; CCB decision criteria | Initial + annual refresher | CCB attendance record |

### 11.2 Competence Requirements

**Configuration Manager (CM)**:
- Experience with Git version control systems (≥2 years for SIL 3 projects).
- Knowledge of EN 50128:2011 §6.6 configuration management requirements.
- Understanding of software development lifecycle (V-Model).
- Familiarity with traceability management (T1–T15 rules).
- Ability to facilitate CCB meetings and record decisions.

**CCB Members**:
- Understanding of change impact analysis (technical, safety, traceability, schedule).
- Knowledge of SIL 3 constraints (MANDATORY techniques per Table A.9).
- Authority to make change decisions within their domain (PM: final approval; VER: technical verification; SAF: safety impact).

### 11.3 Training Records

**Storage**: `docs/training/Training-Records.md` under CM control.

**CM Review**: Quarterly review of training completion; identify gaps; schedule refresher training as needed.

**Audit**: QUA audits training completion during monthly process audits (SIL 3 requirement per SQAP Section 6.2).

---

## 12. COMPLIANCE MATRIX

### 12.1 EN 50128 Section 6.6 Compliance

| Requirement | EN 50128 Clause | SCMP Section | Evidence | Status |
|-------------|----------------|--------------|----------|--------|
| **CM Plan established** | §6.6.2, §6.6.4.1 | This document (entire SCMP) | SCMP approved by PM | ✓ |
| **Configuration identification** | §6.6.2.2 | Section 3 | Document registry; evidence registry | ✓ |
| **Configuration control** | §6.6.2.3, §6.6.4.1 | Section 4 | CR process; nine aspects (a–i) | ✓ |
| **Configuration status accounting** | §6.6.2.4, §6.6.3 | Section 5 | Bi-weekly status reports (SIL 3) | ✓ |
| **Configuration audits** | §6.6.2.5 | Section 6 | CM presence checks; VER functional completeness | ✓ |
| **Version control** | §6.6.2.2, D.48 | Section 8 | Git repository; tagged baselines | ✓ |
| **Change control (nine aspects)** | §6.6.4.1(a–i) | Section 4.1 | CR template with all nine aspects | ✓ |
| **Re-entry to lifecycle phase** | §6.6.4.2 | Section 4.1.8 | CM identifies scope; COD authorizes re-entry | ✓ |
| **Baseline recording** | §9.1.4.2 | Section 7 | Baseline manifest (manifest.yaml) | ✓ |
| **Reproducibility** | §9.1.4.3 | Section 7.3, 9.3 | Git tags, SHA-256 hashes, release package | ✓ |
| **VER evidence retention** | §6.2.4.8 | Section 3.3.3 | Canonical evidence paths; CM presence check | ✓ |
| **VER reports state CI configuration** | §6.2.4.13(a) | Section 6.2 | VER Verification Reports | ✓ |
| **VAL checks verification complete** | §6.3.4.9 | Section 6.3 | VAL 2nd check; VALRPT | ✓ |
| **VAL states baseline validated** | §6.3.4.10 | Section 7.1 (Gate 7) | VALRPT item 25 — Phase 7 | ✓ |
| **Deployment Record as evidence** | §9.1.4.13 | Section 3.3.3 | Deployment evidence path | ✓ |
| **Software Change Records** | §9.2.4 | Section 4.1.7 | CR documents in changes/ | ✓ |

### 12.2 EN 50128 Table A.9 Compliance (CM-Related Techniques)

| # | Technique | SIL 0 | SIL 1–2 | SIL 3–4 | TDC (SIL 3) Implementation | SCMP Section |
|---|-----------|-------|---------|---------|---------------------------|--------------|
| **5** | Software Configuration Management | **M** | **M** | **M** | This SCMP; Git VCS; CM canonical path authority | Entire document |
| **6** | Traceability | R | HR | **M** | T1–T15 checked by VER; workspace.py trace; RTM | Section 5.2 |
| **8** | Data Recording and Analysis | HR | HR | **M** | Configuration status reports; CR metrics; baseline manifests | Section 5.3 |

**Key**: **M** = Mandatory; **HR** = Highly Recommended; **R** = Recommended

**Compliance Status**: All MANDATORY (M) techniques implemented for SIL 3.

---

## 13. REFERENCES

### 13.1 Normative References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications — Communication, signalling and processing systems — Software for railway control and protection systems |
| **[EN50126-1]** | EN 50126-1:2017 Railway applications — The specification and demonstration of Reliability, Availability, Maintainability and Safety (RAMS) — Part 1: Generic RAMS process |
| **[EN50126-2]** | EN 50126-2:2017 Railway applications — RAMS — Part 2: Systems approach to safety |
| **[ISO9001]** | ISO 9001:2015 Quality management systems — Requirements |

### 13.2 Project References

| Reference | Document | Location |
|-----------|----------|----------|
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 | `docs/phase-1-planning/Software-Quality-Assurance-Plan.md` |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 | `docs/phase-1-planning/Software-Verification-Plan.md` (to be created) |
| **[SVaP]** | Software Validation Plan, DOC-SVaP-2026-001 | `docs/phase-1-planning/Software-Validation-Plan.md` (to be created) |
| **[LIFECYCLE]** | LIFECYCLE.md — EN 50128 V-Model lifecycle | `/home/norechang/test/opencode-en50128/LIFECYCLE.md` |
| **[TRACEABILITY]** | TRACEABILITY.md — T1–T15 traceability rules | `/home/norechang/test/opencode-en50128/TRACEABILITY.md` |
| **[BASELINE_MGMT]** | Baseline Management — Diagrams 1–2 | `/home/norechang/test/opencode-en50128/tasks/BASELINE_MANAGEMENT.md` |
| **[DELIVERABLES]** | DELIVERABLES.md — Annex C Table C.1 | `/home/norechang/test/opencode-en50128/DELIVERABLES.md` |
| **[WORKFLOW]** | WORKFLOW.md — Agent interaction, CCB flow | `/home/norechang/test/opencode-en50128/WORKFLOW.md` |

---

## APPENDIX A: CHANGE REQUEST TEMPLATE

```markdown
# Change Request

**CR ID**: CR-<YYYYMMDD>-<NNN>  
**Date**: YYYY-MM-DD  
**Submitter**: [Name], [Role]  
**Priority**: [Critical / High / Medium / Low]  
**Status**: [Open / Under Review / Approved / Rejected / Implemented / Closed]

---

## 1. AFFECTED CONFIGURATION ITEMS (§6.6.4.1(f))

- [List all affected CIs with Document ID or file path]
- Example: `DOC-SRS-2026-001` (Software Requirements Specification)
- Example: `src/door_control.c` (source code module)
- Example: `docs/phase-2-requirements/Software-Requirements-Specification.md`

---

## 2. REASON FOR CHANGE (§6.6.4.1(b))

[Describe why this change is needed. Categories: Corrective (bug fix) / Perfective (enhancement) / Adaptive (environment change)]

**Change Category**: [Corrective / Perfective / Adaptive]

---

## 3. PROPOSED SOLUTION

[Describe the proposed solution, if known. Include technical approach, affected modules, estimated effort.]

---

## 4. CM IMPACT ANALYSIS (§6.6.4.1(c))

**Performed By**: Configuration Manager  
**Date**: YYYY-MM-DD

### 4.1 Affected Requirements
- [List requirements IDs affected, e.g., REQ-FUNC-001]

### 4.2 Affected Design Elements
- [List design components affected, e.g., SAS-MOD-001, SDS-MOD-001]

### 4.3 Affected Code Modules
- [List source files affected, e.g., door_control.c, sensor_interface.h]

### 4.4 Affected Tests
- [List test cases affected, e.g., TC-UNIT-001, TC-INT-005]

### 4.5 SIL Impact
- **Safety Impact**: [None / Minor / Major — affects safety-critical requirements]
- **Hazard Log Update Required**: [Yes / No]
- **FMEA/FTA Update Required**: [Yes / No]

### 4.6 Traceability Impact (§6.6.4.1(i))
- **Affected Traceability Links**: [List T1–T15 links affected, e.g., T7 (Component Design → Code), T12 (Code → Test)]
- **RTM Update Required**: [Yes / No]

### 4.7 Re-entry Phase (§6.6.4.2)
- **Re-entry Phase**: [Phase 2 / Phase 3 / Phase 4 / Phase 5 / Phase 6 / Phase 7]
- **Re-entry Scope**: [Describe which activities must be repeated]
- **COD Authorization Required**: Yes (CM identifies; COD authorizes)

### 4.8 Effort Estimate
- **Effort**: [Hours / Days]
- **Schedule Impact**: [None / Minor / Major]

---

## 5. CCB DECISION (§6.6.4.1(d))

**CCB Meeting Date**: YYYY-MM-DD  
**CCB Members Present**: [PM (Chair), CM (Secretary), QUA, VER, SAF, DES]

**Decision**: [Approved / Rejected / Deferred]

**Rationale**: [CCB reasoning for decision]

**Assigned To**: [Developer name / team]

**Target Completion Date**: YYYY-MM-DD

**CCB Minutes Reference**: `changes/CCB-Minutes-<YYYYMMDD>.md`

---

## 6. IMPLEMENTATION (§6.6.4.1(e,g))

**Implementer**: [Name], [Role]  
**Implementation Date**: YYYY-MM-DD

### 6.1 Branch
- **Branch Name**: `feature/CR-<YYYYMMDD>-<NNN>` or `bugfix/CR-<YYYYMMDD>-<NNN>`

### 6.2 Commits
- [List commit SHAs]
- Example: `a1b2c3d` — [CR-<YYYYMMDD>-<NNN>] Implement door control timeout logic

### 6.3 Pull Request
- **PR Link**: [GitHub/GitLab PR URL]
- **PR Status**: [Open / Merged]

### 6.4 Updated Documents (§6.6.4.1(e))
- [List all documents updated with new version numbers]

### 6.5 Verification Evidence (§6.6.4.1(g))
- **VER Review Date**: YYYY-MM-DD
- **VER Reviewer**: [Name]
- **MISRA C Check**: [Pass / Fail — deviations justified]
- **Static Analysis**: [Pass / Fail]
- **Coverage**: [Statement: X%, Branch: Y%, MC/DC: Z% if applicable]
- **Tests Executed**: [List test IDs]
- **Tests Passed**: [Count / Total]
- **Verification Evidence Path**: [CM canonical evidence path]

---

## 7. TRACEABILITY UPDATE (§6.6.4.1(i))

**Updated By**: [VER Name]  
**Date**: YYYY-MM-DD

**Traceability Links Updated**:
- [List T1–T15 links updated, e.g., T7: COMP-001 → src/door_control.c (line 45)]

**RTM Updated**: [Yes — version X.Y]

---

## 8. CONFIGURATION STATUS ACCOUNTING (§6.6.4.1(h))

**CM Status Update Date**: YYYY-MM-DD

**Baseline Updated**: [Yes / No]  
**New Baseline Version**: [e.g., 1.1 or 2.0]  
**Baseline Name**: [e.g., requirements-baseline-v1.1]

**Stakeholders Notified**: [PM, COD, VMGR, Safety Authority (if safety-critical)]

**Configuration Status Report Updated**: `docs/configuration/Configuration-Status-Report-<YYYYMMDD>.md`

---

## 9. CLOSURE

**Closure Date**: YYYY-MM-DD  
**Closed By**: Configuration Manager  
**Final Status**: [Implemented / Rejected / Deferred]

**Lessons Learned**: [Optional — any process improvements identified]
```

---

## APPENDIX B: CONFIGURATION STATUS REPORT TEMPLATE

```markdown
# Configuration Status Report

**Report Period**: [Start Date] to [End Date]  
**Report Date**: YYYY-MM-DD  
**Prepared By**: Configuration Manager  
**SIL Level**: 3  
**Project**: TDC (Train Door Control System)

---

## 1. BASELINE STATUS

| Baseline | Version | Date Established | Status | Last Modified | Change Reference |
|----------|---------|------------------|--------|---------------|------------------|
| planning-baseline | 1.0 | 2026-04-02 | Established | — | — |
| requirements-baseline | 1.0 | 2026-04-15 | Modified | 2026-04-18 | CR-20260418-042 |
| design-baseline | 1.0 | 2026-05-01 | Established | — | — |

---

## 2. CHANGE REQUESTS

| CR ID | Submitter | Priority | Category | Status | CCB Decision Date | Closure Date |
|-------|-----------|----------|----------|--------|-------------------|--------------|
| CR-20260418-042 | DES Team | High | Perfective | Closed | 2026-04-18 | 2026-04-20 |
| CR-20260420-043 | Customer | Medium | Adaptive | Under Review | — | — |
| CR-20260421-044 | VER Team | Critical | Corrective (safety) | Open | — | — |

**Summary**:
- **Total CRs This Period**: 3
- **Open CRs**: 1 (1 Critical — safety-related)
- **Closed CRs**: 1
- **Average Resolution Time**: 2 days (for closed CRs)

---

## 3. BUILD STATUS

**Latest Build**: #0245  
**Build Date**: 2026-04-22  
**Build Result**: ✓ Success  
**Build Time**: 3 minutes 42 seconds  
**Test Results**: 158/158 passed (100%)

**Build Verification Checks**:
- ✓ MISRA C compliance: Pass (zero violations)
- ✓ Static analysis: Pass (zero critical/high issues)
- ✓ Coverage: Statement 96.2%, Branch 91.5%, MC/DC 89.3% (safety-critical modules)
- ✓ Complexity: Max 8 (within SIL 3 limit ≤10)

---

## 4. DEFECTS

| Defect ID | Severity | Phase Detected | Status | Assigned To | Target Date |
|-----------|----------|----------------|--------|-------------|-------------|
| DEF-001 | Major | Phase 5 (Unit Testing) | Open | IMP Team | 2026-04-25 |
| DEF-002 | Minor | Phase 3 (Design Review) | Closed | DES Team | 2026-04-21 |

**Summary**:
- **Total Defects This Period**: 2
- **Open Defects**: 1 (0 Critical, 1 Major, 0 Minor)
- **Closed Defects This Period**: 1

---

## 5. METRICS (SIL 3 — MANDATORY)

| Metric | Value | Target | Status |
|--------|-------|--------|--------|
| Open CRs | 1 | ≤3 | ✓ Green |
| Critical CRs Open | 1 (safety-related) | 0 | ⚠ Yellow — under review |
| Closed CRs This Period | 1 | — | — |
| Defects Found This Period | 2 | — | — |
| Defects Fixed This Period | 1 | — | — |
| Statement Coverage | 96.2% | ≥95% | ✓ Green |
| Branch Coverage | 91.5% | ≥90% | ✓ Green |
| MC/DC Coverage (safety-critical) | 89.3% | ≥90% | ⚠ Yellow — re-test planned |
| Cyclomatic Complexity (max) | 8 | ≤10 | ✓ Green |

---

## 6. TRACEABILITY STATUS (SIL 3 — MANDATORY)

| Traceability Link | Total Items | Traced Items | Coverage | Status |
|-------------------|-------------|--------------|----------|--------|
| T1: System Req → SW Req | 45 | 45 | 100% | ✓ Complete |
| T2: SW Req → Overall Test Spec | 45 | 45 | 100% | ✓ Complete |
| T3: SW Req → SW Architecture | 45 | 45 | 100% | ✓ Complete |
| T7: Component Design → Code | 23 | 23 | 100% | ✓ Complete |
| T12: Code → Component Test | 15 modules | 15 modules | 100% | ✓ Complete |

**Summary**: All T1–T15 traceability links verified by VER; coverage 100%.

---

## 7. EVIDENCE STATUS

| Evidence Type | Phase | Artifacts Count | Storage Path | CM Check |
|---------------|-------|-----------------|--------------|----------|
| Static Analysis | 5 | 15 reports | `phase-5-implementation-testing/evidence/static-analysis/` | ✓ Present |
| Coverage | 5 | 15 reports | `phase-5-implementation-testing/evidence/coverage/` | ✓ Present |
| Unit Test Logs | 5 | 15 logs | `phase-5-implementation-testing/evidence/test-logs/` | ✓ Present |

**Summary**: All evidence artifacts present at canonical paths per SCMP Section 3.3.3.

---

## 8. ISSUES AND RISKS

**Issue #1**: Critical CR-20260421-044 (safety-related) requires Safety Authority review before CCB decision. **Risk**: Potential schedule delay if safety impact assessment requires re-entry to Phase 2. **Mitigation**: SAF performing expedited Hazard Log review; CCB emergency session scheduled for 2026-04-23.

**Issue #2**: MC/DC coverage for Module 7 (emergency_stop.c) at 89.3% — below 90% target. **Risk**: Gate 5 may be delayed. **Mitigation**: TST team adding additional test cases; re-run scheduled for 2026-04-24.

---

## 9. NEXT PERIOD ACTIONS

1. Close Critical CR-20260421-044 after Safety Authority review.
2. Re-run MC/DC coverage tests for emergency_stop.c.
3. Prepare for Gate 5 (Implementation & Testing) — target date 2026-04-26.
4. Schedule CM presence check for implementation-baseline.

---

**END OF REPORT**

**Distribution**: PM, QUA, COD, VMGR, CCB Members  
**Next Report Due**: 2026-05-06 (bi-weekly for SIL 3)
```

---

## APPENDIX C: CM PRESENCE CHECK REPORT TEMPLATE

```markdown
# CM Presence Check Report

**Baseline**: <baseline-name>  
**Gate**: <N>  
**Phase**: <phase-name>  
**Date**: YYYY-MM-DD  
**Auditor**: Configuration Manager (CM)  
**SIL Level**: 3

---

## 1. PRECONDITIONS

**COD Gate-Check Status**: [PASS / FAIL]  
**COD Authorization**: [Read from LIFECYCLE_STATE.md]  
**VMGR Approval (SIL 3)**: [Yes / No — VER report reviewed and approved]  
**Critical NCRs Open**: [0 / Count]

**Precondition Check Result**: [PASS / FAIL]

---

## 2. DELIVERABLES PRESENCE CHECK

| Annex C Item | Document Key | Document ID | Version | Canonical Path | Present? | Version Correct? |
|--------------|--------------|-------------|---------|----------------|----------|------------------|
| 1 | SQAP | DOC-SQAP-2026-001 | 1.0 | `docs/phase-1-planning/Software-Quality-Assurance-Plan.md` | ✓ | ✓ |
| 3 | SCMP | DOC-SCMP-2026-001 | 1.0 | `docs/phase-1-planning/Software-Configuration-Management-Plan.md` | ✓ | ✓ |

**Result**: [All deliverables present / Missing: list]

---

## 3. APPROVALS CHECK

| Document Key | Author Signature | 1st Check (VER) | 2nd Check (VAL) | Approver (PM) | Complete? |
|--------------|------------------|-----------------|-----------------|---------------|-----------|
| SQAP | ✓ | ✓ | ✓ | ✓ | ✓ |
| SCMP | ✓ | ✓ | ✓ | ✓ | ✓ |

**Result**: [All approvals complete / Missing: list]

---

## 4. EVIDENCE ARTIFACTS PRESENCE CHECK

| Evidence Type | Canonical Path | Artifacts Count | Present? |
|---------------|---------------|-----------------|----------|
| static-analysis | `phase-5-implementation-testing/evidence/static-analysis/` | 15 | ✓ |
| coverage | `phase-5-implementation-testing/evidence/coverage/` | 15 | ✓ |

**Result**: [All evidence artifacts present / Missing: list]

---

## 5. VER VERIFICATION REPORT CHECK

**VER Report**: [Document ID]  
**VER Report Present**: [Yes / No]  
**VER Report States CI Configuration (§6.2.4.13(a))**: [Yes / No]  
**VMGR Approval (SIL 3)**: [Yes / No — date]

**Result**: [VER report complete / Issues: list]

---

## 6. VAL 2ND CHECK

**VAL 2nd Check Required**: [Yes / No — per DELIVERABLES.md]  
**VAL 2nd Check Complete**: [Yes / No]  
**VAL Check Date**: [YYYY-MM-DD]

**Result**: [VAL 2nd check complete / Issues: list]

---

## 7. GIT REPOSITORY CHECK

**Git Tag**: [v1.0.0]  
**Git Commit SHA**: [<commit-hash>]  
**Branch**: [main]  
**Tag Annotated**: [Yes / No]  
**Tag Message Includes Baseline Metadata**: [Yes / No]

**Result**: [Git tag correct / Issues: list]

---

## 8. CM PRESENCE CHECK RESULT

**Overall Result**: [PASS / FAIL]

**Issues Found**: [None / List of issues]

**Corrective Actions Required**: [None / List of actions]

**CM Recommendation**: [Approve baseline creation / Reject — corrective actions required]

---

**CM Signature**: _____________________  
**Date**: YYYY-MM-DD
```

---

## DOCUMENT HISTORY

This document is maintained under configuration control per Section 4. All changes SHALL be approved by the Change Control Board (CCB).

**Current Version**: 1.0  
**Last Updated**: 2026-04-02  
**Next Review**: 2026-07-02 (quarterly review for SIL 3)

---

**END OF DOCUMENT**
