# Software Configuration Management Plan (SCMP)

## Document Control

| Field | Value |
|-------|-------|
| **Document ID** | DOC-TDC-SCMP-001 |
| **Version** | 1.0 |
| **Date** | 2026-03-30 |
| **Status** | DRAFT |
| **Author** | Configuration Manager (CM) |
| **Project** | TDC (Train Door Control) |
| **SIL Level** | SIL 3 |
| **Standard** | EN 50128:2011 Section 6.6 — Software Configuration Management |

---

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Configuration Manager (Author) | TBD — assigned at project kick-off | | |
| Project Manager | TBD — assigned at project kick-off | | |
| QA Manager (1st Check) | TBD — assigned at project kick-off | | |
| Independent Validator (2nd Check) | TBD — assigned at project kick-off | | |

**Note**: Per EN 50128:2011 Table B.10, the Configuration Manager role does not require independence from development at any SIL level. However, for SIL 3, CM must maintain separation from implementation activities to preserve baseline authority and integrity.

---

## Revision History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-03-30 | CM Team | Initial SCMP for TDC project (SIL 3) |

---

## Table of Contents

1. [Purpose and Scope](#1-purpose-and-scope)
2. [References](#2-references)
3. [Definitions and Abbreviations](#3-definitions-and-abbreviations)
4. [Configuration Management Organisation](#4-configuration-management-organisation)
5. [Configuration Item Identification](#5-configuration-item-identification)
6. [Version Control System](#6-version-control-system)
7. [Baseline Management](#7-baseline-management)
8. [Change Control Process](#8-change-control-process)
9. [Change Request Document Format](#9-change-request-document-format)
10. [Build Management](#10-build-management)
11. [Problem Reporting](#11-problem-reporting)
12. [Backup and Recovery](#12-backup-and-recovery)
13. [Configuration Audits](#13-configuration-audits)
14. [Configuration Status Accounting](#14-configuration-status-accounting)
15. [Tool Qualification](#15-tool-qualification)
16. [Appendix A: Configuration Item Registry](#appendix-a-configuration-item-registry)
17. [Appendix B: Change Request Template](#appendix-b-change-request-template)
18. [Appendix C: Baseline Manifest Template](#appendix-c-baseline-manifest-template)

---

## 1. Purpose and Scope

### 1.1 Purpose

This Software Configuration Management Plan (SCMP) defines the configuration management approach, processes, and tools for the **TDC (Train Door Control)** software development project. The plan is prepared in accordance with **EN 50128:2011 Section 6.6** and is tailored for **SIL 3** safety integrity requirements.

The SCMP establishes:
- Configuration Item (CI) identification and naming conventions
- Version control system and repository structure
- Baseline management procedures for all lifecycle phases
- Change control process and Change Control Board (CCB) operation
- Configuration status accounting and reporting mechanisms
- Backup and recovery procedures
- Configuration audit procedures

### 1.2 Scope

This SCMP covers **all lifecycle phases (Phases 1–9, plus ongoing Phase 10 maintenance)** of the TDC software development project:

| Phase | Name | Configuration Scope |
|-------|------|---------------------|
| Phase 1 | Planning | SQAP, SCMP, SVP, SVaP |
| Phase 2 | Requirements | SRS, Overall Test Spec, traceability matrices |
| Phase 3 | Architecture & Design | SAS, SDS, SIS, integration test specifications |
| Phase 4 | Component Design | Component design & test specifications |
| Phase 5 | Implementation & Testing | C source code (MISRA C:2012), unit tests, evidence |
| Phase 6 | Integration | Integration test reports, SW/HW integration evidence |
| Phase 7 | Validation | Validation report, overall test report, release note |
| Phase 8 | Assessment | Assessment plan and report (independent assessor) |
| Phase 9 | Deployment | Release package, deployment records, verification report |
| Phase 10 | Maintenance | Change records, maintenance records, verification reports |

All Configuration Items are under version control from creation through deployment and maintenance.

### 1.3 Relationship to Other Plans

This SCMP is supported by and references:
- **Software Quality Assurance Plan (SQAP)** — quality standards, document templates, review checklists
- **Software Verification Plan (SVP)** — verification activities, traceability requirements, evidence retention
- **Software Validation Plan (SVaP)** — validation strategy, acceptance criteria
- **System Safety Plan** — system-level safety requirements and hazard management

### 1.4 EN 50128 Configuration Management Requirements

Per EN 50128:2011 Section 6.6, the Configuration Manager SHALL:
1. Identify and control all configuration items throughout the lifecycle
2. Maintain version control of all software and documentation
3. Ensure traceability between requirements, design, code, and tests
4. Control changes through a formal change control process
5. Maintain baselines at defined lifecycle gates
6. Provide configuration status accounting
7. Support configuration audits (verification of baseline completeness per §6.2.4.7–8)

Per **EN 50128:2011 Table A.9 Technique #5**, Software Configuration Management is **MANDATORY** at SIL 3.

---

## 2. References

### 2.1 Normative References

| Reference | Title | Version |
|-----------|-------|---------|
| EN 50128:2011 | Railway applications — Communication, signalling and processing systems — Software for railway control and protection systems | 2011 |
| EN 50126-1:2017 | Railway applications — Specification and demonstration of RAMS — Part 1: Generic RAMS process | 2017 |
| EN 50126-2:2017 | Railway applications — RAMS — Part 2: Systems approach to safety | 2017 |
| MISRA C:2012 | Guidelines for the use of the C language in critical systems | Amendment 2 (2020) |
| ISO 9001:2015 | Quality management systems — Requirements | 2015 |

### 2.2 Project Documents

| Document ID | Title | Phase |
|-------------|-------|-------|
| DOC-TDC-SQAP-001 | Software Quality Assurance Plan | Phase 1 |
| DOC-TDC-SVP-001 | Software Verification Plan | Phase 1 |
| DOC-TDC-SVaP-001 | Software Validation Plan | Phase 1 |
| DOC-TDC-SRS-SYS-001 | System Requirements Specification | Phase 0 |
| DOC-TDC-SAD-SYS-001 | System Architecture Description | Phase 0 |
| DOC-TDC-SSP-SYS-001 | System Safety Plan | Phase 0 |
| DOC-TDC-SSRS-SYS-001 | System Safety Requirements Specification | Phase 0 |

### 2.3 EN 50128 Clauses

| Clause | Topic |
|--------|-------|
| §6.6 | Software Configuration Management |
| §6.6.3 | Configuration Management Outputs |
| §6.6.4.1 | Change Control — Nine Required Aspects (a–i) |
| §6.6.4.2 | Change Re-entry to Lifecycle Phase |
| §6.2.4.7–8 | VER functional completeness and evidence retention |
| §6.2.4.13(a) | VER report identity/configuration documentation |
| §6.3.4.9–10 | VAL verification-complete check and baseline statement |
| §9.1.4.2–3 | Baseline recording and reproducibility |
| §9.1.4.13 | Deployment Record as tracked evidence artifact |
| §9.2.4 | Maintenance-phase change assessment and Software Change Records |
| Annex D.48 | Software Configuration Management technique description |

---

## 3. Definitions and Abbreviations

### 3.1 Abbreviations

| Abbreviation | Definition |
|--------------|------------|
| ASR | Assessor (Independent Safety Assessor) |
| CCB | Change Control Board |
| CCN | Cyclomatic Complexity Number |
| CI | Configuration Item |
| CM | Configuration Manager |
| COD | Lifecycle Coordinator |
| CR | Change Request |
| DES | Designer |
| IMP | Implementer |
| INT | Integrator |
| ISA | Independent Safety Assessment |
| MISRA | Motor Industry Software Reliability Association |
| NCR | Non-Conformance Report |
| PM | Project Manager |
| PR | Problem Report |
| QUA | Quality Assurance Engineer |
| REQ | Requirements Engineer |
| RTM | Requirements Traceability Matrix |
| SAF | Safety Engineer |
| SCMP | Software Configuration Management Plan |
| SIL | Safety Integrity Level |
| SQAP | Software Quality Assurance Plan |
| SVaP | Software Validation Plan |
| SVP | Software Verification Plan |
| TDC | Train Door Control |
| TST | Tester |
| VAL | Validator |
| VCS | Version Control System |
| VER | Verifier |
| VMGR | V&V Manager |

### 3.2 Definitions

| Term | Definition |
|------|------------|
| **Baseline** | A formally approved version of a configuration item or set of configuration items, recorded and maintained throughout the lifecycle (EN 50128 §9.1.4.2). |
| **Configuration Item (CI)** | Any artifact (document, source file, test file, tool, evidence) that is formally identified, version-controlled, and subject to change control. |
| **Change Request (CR)** | A formal request to modify one or more configuration items, subject to CCB review and approval. |
| **Change Control Board (CCB)** | A group authorized to approve or reject change requests. PM chairs the CCB; COD approves lifecycle impact. |
| **Configuration Manifest** | A list of all configuration items included in a baseline, with version identifiers. |
| **Problem Report (PR)** | A record of a detected defect or non-conformance, which may trigger a Change Request. |
| **Evidence Artifact** | Raw output from verification or testing activities (e.g., MISRA reports, coverage data, test logs) retained per §6.2.4.8. |

---

## 4. Configuration Management Organisation

### 4.1 CM Role and Responsibilities

The **Configuration Manager (CM)** is responsible for:

| Responsibility | EN 50128 Clause |
|----------------|-----------------|
| Defining and maintaining the CI identification scheme | §6.6 |
| Operating the version control system (Git) | §6.6 |
| Creating and maintaining baselines at each phase gate | §9.1.4.2–3 |
| Operating the Change Control Board secretariat (PM chairs CCB) | §6.6.4.1 |
| Recording all change requests and CCB decisions | §6.6.4.1(a,d,h) |
| Ensuring all affected CIs are updated per approved CRs | §6.6.4.1(e,f) |
| Maintaining configuration status accounting records | §6.6 |
| Supporting configuration audits (presence checks per §6.2.4.8) | §6.2.4.8 |
| Managing repository backup and recovery | §6.6 |
| Validating that document and evidence paths conform to the canonical registry | §6.6, D.48 |

**Note on Terminology**: EN 50128:2011 does **not** define "FCA" (Functional Configuration Audit) or "PCA" (Physical Configuration Audit). Those terms come from MIL-STD-973 / IEEE 828. The EN 50128 equivalent activities are:
- **Functional completeness** (requirements satisfied per phase) — VER responsibility per §6.2.4.7
- **Physical presence check** (each CI matches VCS and build artifacts) — CM responsibility per §6.6, D.48
- **VER evidence retention format** — CM presence check per §6.2.4.8

CM's role at a baseline event is **record-keeping and presence-checking**: verify that the required signed documents and evidence artifacts are present, correctly versioned, and stored at canonical paths. CM does **NOT** independently judge functional completeness — that is VER's and VAL's responsibility.

### 4.2 Independence Requirements

Per EN 50128:2011 Table B.10:
- **SIL 0–4**: CM independence from development is **NOT REQUIRED**.
- **SIL 3 Best Practice**: CM SHOULD maintain separation from implementation activities (IMP role) to preserve baseline authority and avoid conflicts of interest.

For this project:
- CM SHALL NOT perform the Implementer (IMP) role
- CM MAY coordinate with all other roles (REQ, DES, TST, INT, SAF, VER, VAL, QUA, PM, COD)
- CM reports to **PM** for day-to-day operations
- CM coordinates with **COD** for phase gate baseline creation (COD authorizes gate passage; CM executes baseline procedure)

### 4.3 Change Control Board (CCB)

The CCB is responsible for reviewing and approving all change requests.

| Role | CCB Responsibility |
|------|-------------------|
| **PM** | CCB Chair — leads meetings, coordinates decision-making |
| **COD** | Approves lifecycle impact and phase re-entry (§6.6.4.2) — cannot be overridden |
| **CM** | CCB Secretary — prepares CR documentation, records decisions |
| **Technical Reviewers** | Ad-hoc members (REQ, DES, IMP, INT, SAF, VER, VAL) — provide technical impact analysis |
| **QUA** | Quality impact assessment |
| **Safety Manager** | Safety impact assessment (invokes SAF as needed) |

**Critical CCB Rules**:
1. **PM chairs**, but **COD has final authority** on lifecycle decisions
2. **VMGR is independent** — if a CR affects V&V activities, VMGR provides independent assessment but does not report to CCB
3. All CR decisions must address the **nine required aspects** per §6.6.4.1(a–i) (see Section 8)

---

## 5. Configuration Item Identification

### 5.1 CI Categories

All project artifacts fall into one of the following CI categories:

| Category | Examples | Version Control |
|----------|----------|-----------------|
| **Documents** | SQAP, SCMP, SRS, SAS, test reports | Git (Markdown) |
| **Source Code** | C modules (.c, .h), MISRA C:2012 compliant | Git |
| **Test Code** | Unit tests (Unity framework), integration tests | Git |
| **Build Artifacts** | Makefiles, build scripts, compiler configurations | Git |
| **Evidence Artifacts** | MISRA reports (.xml), coverage data (.gcda, .gcno), test logs | Git (in evidence/ directories) |
| **Tools** | Compilers, static analyzers, test frameworks, coverage tools | Version recorded; binaries NOT in Git |
| **Baselines** | Baseline manifests, tagged releases | Git tags + archived manifests |

### 5.2 Document CI Naming Convention

All project documents follow this naming scheme:

```
DOC-TDC-<TYPE>-<NNN>
```

| Field | Description | Example |
|-------|-------------|---------|
| `DOC` | Fixed prefix for documents | `DOC` |
| `TDC` | Project identifier | `TDC` |
| `<TYPE>` | Document type abbreviation (4–6 chars) | `SQAP`, `SRS`, `SAS`, `VER` |
| `<NNN>` | Three-digit sequence number | `001`, `002`, `123` |

**Examples**:
- `DOC-TDC-SQAP-001` — Software Quality Assurance Plan
- `DOC-TDC-SCMP-001` — Software Configuration Management Plan (this document)
- `DOC-TDC-SRS-001` — Software Requirements Specification
- `DOC-TDC-SAS-001` — Software Architecture Specification
- `DOC-TDC-REQVER-001` — Software Requirements Verification Report

**System-level documents** use `SYS` in the type field:
- `DOC-TDC-SRS-SYS-001` — System Requirements Specification
- `DOC-TDC-SAD-SYS-001` — System Architecture Description
- `DOC-TDC-SSP-SYS-001` — System Safety Plan
- `DOC-TDC-SSRS-SYS-001` — System Safety Requirements Specification

### 5.3 Source Code CI Naming Convention

All source code files follow this naming scheme:

```
TDC-SRC-<MODULE>-<NNN>.<ext>
```

| Field | Description | Example |
|-------|-------------|---------|
| `TDC` | Project identifier | `TDC` |
| `SRC` | Fixed source code indicator | `SRC` |
| `<MODULE>` | Module abbreviation (3–6 chars) | `DSM`, `PSM`, `COMM`, `DIAG` |
| `<NNN>` | Three-digit sequence number | `001`, `002`, `123` |
| `<ext>` | File extension | `.c` (source), `.h` (header) |

**Examples**:
- `TDC-SRC-DSM-001.c` — Door State Machine module (source)
- `TDC-SRC-DSM-001.h` — Door State Machine module (header)
- `TDC-SRC-PSM-001.c` — Platform Safety Monitor module
- `TDC-SRC-COMM-001.c` — Communication module

**Directory Structure**:
```
examples/TDC/src/
├── dsm/                    # Door State Machine
│   ├── TDC-SRC-DSM-001.c
│   └── TDC-SRC-DSM-001.h
├── psm/                    # Platform Safety Monitor
│   ├── TDC-SRC-PSM-001.c
│   └── TDC-SRC-PSM-001.h
├── comm/                   # Communication
│   ├── TDC-SRC-COMM-001.c
│   └── TDC-SRC-COMM-001.h
└── diag/                   # Diagnostics
    ├── TDC-SRC-DIAG-001.c
    └── TDC-SRC-DIAG-001.h
```

### 5.4 Test CI Naming Convention

All test files follow this naming scheme:

```
TDC-TST-<MODULE>-<NNN>.<ext>
```

| Field | Description | Example |
|-------|-------------|---------|
| `TDC` | Project identifier | `TDC` |
| `TST` | Fixed test indicator | `TST` |
| `<MODULE>` | Module under test | `DSM`, `PSM`, `COMM`, `DIAG` |
| `<NNN>` | Three-digit sequence number | `001`, `002`, `123` |
| `<ext>` | File extension | `.c` (Unity tests) |

**Examples**:
- `TDC-TST-DSM-001.c` — Unit tests for Door State Machine
- `TDC-TST-PSM-001.c` — Unit tests for Platform Safety Monitor
- `TDC-TST-INT-001.c` — Integration test for multiple modules

**Directory Structure**:
```
examples/TDC/tests/
├── unit/                   # Unit tests
│   ├── TDC-TST-DSM-001.c
│   ├── TDC-TST-PSM-001.c
│   └── TDC-TST-COMM-001.c
└── integration/            # Integration tests
    ├── TDC-TST-INT-001.c
    └── TDC-TST-INT-002.c
```

### 5.5 Baseline Tag Naming Convention

All baseline tags follow this naming scheme:

```
TDC-BL-<BASELINE_NAME>-v<X.Y>
```

| Field | Description | Example |
|-------|-------------|---------|
| `TDC` | Project identifier | `TDC` |
| `BL` | Fixed baseline indicator | `BL` |
| `<BASELINE_NAME>` | Baseline identifier (see Section 7.2) | `PHASE1`, `REQUIREMENTS`, `RELEASE` |
| `v<X.Y>` | Version number (major.minor) | `v1.0`, `v1.1`, `v2.0` |

**Examples**:
- `TDC-BL-PHASE1-v1.0` — Planning baseline (Phase 1 gate)
- `TDC-BL-REQUIREMENTS-v1.0` — Requirements baseline (Phase 2 gate)
- `TDC-BL-DESIGN-v1.0` — Architecture & design baseline (Phase 3 gate)
- `TDC-BL-RELEASE-v1.0` — Release baseline (Phase 7 gate) — **most critical**
- `TDC-BL-DEPLOYMENT-v1.0` — Deployment baseline (Phase 9 gate)

**Version Numbering Rules**:
- **Major version** (X) increments on baseline creation at a new phase gate
- **Minor version** (Y) increments on baseline update due to approved change request within the same phase
- Initial baseline at each gate: `v1.0`
- CR-triggered re-baseline: `v1.1`, `v1.2`, etc.

### 5.6 Change Request Naming Convention

All change requests follow this naming scheme:

```
CR-TDC-<YYYYMMDD>-<NNN>
```

| Field | Description | Example |
|-------|-------------|---------|
| `CR` | Fixed change request prefix | `CR` |
| `TDC` | Project identifier | `TDC` |
| `<YYYYMMDD>` | Date submitted | `20260330` |
| `<NNN>` | Three-digit sequence number (per day) | `001`, `002`, `123` |

**Examples**:
- `CR-TDC-20260330-001` — First CR submitted on 2026-03-30
- `CR-TDC-20260330-002` — Second CR submitted on 2026-03-30
- `CR-TDC-20260415-001` — First CR submitted on 2026-04-15

### 5.7 Problem Report Naming Convention

All problem reports follow this naming scheme:

```
PR-TDC-<YYYYMMDD>-<NNN>
```

**Examples**:
- `PR-TDC-20260330-001` — First PR logged on 2026-03-30
- `PR-TDC-20260330-002` — Second PR logged on 2026-03-30

**Relationship to CRs**: A Problem Report (PR) records a detected defect. If the defect requires a code or document change, a Change Request (CR) is created. The CR references the originating PR.

---

## 6. Version Control System

### 6.1 VCS Selection

The TDC project uses **Git** as the version control system.

| Tool | Purpose | Version | Classification |
|------|---------|---------|----------------|
| Git | Version control, branching, tagging, history | ≥ 2.30 | T1 (no qualification required) |
| GitHub / GitLab | Remote repository hosting (optional) | Latest | T1 (no qualification required) |

**Rationale**: Git is a widely-used, industry-standard version control system. Per EN 50128:2011 §7.4.4.14 and Table A.20, Git is classified as a **T1 tool** (generates no output that becomes part of the safety software). **No tool qualification is required.**

### 6.2 Repository Structure

The Git repository follows this canonical structure:

```
examples/TDC/
├── .git/                           # Git metadata (not a CI)
├── LIFECYCLE_STATE.md              # COD lifecycle tracking
├── README.md                       # Project overview
├── changes/                        # Change requests
│   ├── CR-TDC-20260330-001.md
│   └── ...
├── baselines/                      # Baseline manifests
│   ├── planning-baseline/
│   │   └── manifest.yaml
│   ├── requirements-baseline/
│   │   └── manifest.yaml
│   └── ...
├── docs/                           # Documents (Phase 1–9)
│   ├── Software-Quality-Assurance-Plan.md
│   ├── Software-Configuration-Management-Plan.md
│   ├── Software-Verification-Plan.md
│   ├── Software-Validation-Plan.md
│   ├── Software-Requirements-Specification.md
│   ├── Software-Architecture-Specification.md
│   └── ...
│   └── system/                     # System-level documents (Phase 0)
│       ├── System-Requirements-Specification.md
│       ├── System-Architecture-Description.md
│       ├── System-Safety-Plan.md
│       └── System-Safety-Requirements-Specification.md
├── src/                            # Source code (Phase 5)
│   ├── dsm/
│   ├── psm/
│   ├── comm/
│   └── diag/
├── tests/                          # Test code (Phase 5–7)
│   ├── unit/
│   └── integration/
├── evidence/                       # Evidence artifacts (Phase 5–9)
│   ├── static-analysis/
│   ├── coverage/
│   ├── test-logs/
│   └── ...
├── build/                          # Build outputs (NOT version-controlled)
└── release/                        # Release packages (Phase 9)
```

**Version Control Rules**:
1. **All source files** (.c, .h) are version-controlled
2. **All document files** (.md) are version-controlled
3. **All test files** (.c) are version-controlled
4. **All evidence artifacts** (MISRA reports, coverage data, test logs) are version-controlled
5. **Build outputs** (object files, executables) are **NOT** version-controlled (added to `.gitignore`)
6. **Baseline manifests** are version-controlled in `baselines/` directory

### 6.3 Branching Strategy

The TDC project follows a **feature branch workflow** with phase-based integration:

```
main (protected)
├── develop (integration branch)
│   ├── feature/phase-1-planning
│   ├── feature/phase-2-requirements
│   ├── feature/phase-3-design
│   ├── feature/phase-4-component-design
│   ├── feature/phase-5-implementation
│   ├── feature/phase-6-integration
│   └── feature/phase-7-validation
└── hotfix/CR-TDC-YYYYMMDD-NNN (for urgent production fixes)
```

| Branch | Purpose | Lifetime | Merge Rules |
|--------|---------|----------|-------------|
| `main` | Production-ready releases | Permanent | Only from `develop` after Phase 7 gate |
| `develop` | Integration branch for all phase work | Permanent | Feature branches merge here |
| `feature/<phase-name>` | Phase-specific development | Until phase gate passes | Merge to `develop` after COD gate approval |
| `hotfix/CR-TDC-*` | Urgent fixes to production (Phase 10) | Until CR approved and deployed | Merge to `main` and `develop` |

**Branch Protection Rules**:
- `main` branch is **protected** — no direct commits
- All merges to `main` require:
  - COD gate approval
  - VER report signed
  - VAL report signed (Phase 7 only)
  - VMGR approval (SIL 3 mandatory)
  - PM approval

### 6.4 Commit Message Convention

All Git commit messages SHALL follow this format:

```
<type>(<scope>): <subject>

<body>

Refs: <issue-or-CR-id>
```

| Field | Description | Example |
|-------|-------------|---------|
| `<type>` | Commit type (see below) | `feat`, `fix`, `docs`, `test` |
| `<scope>` | Module or document affected | `DSM`, `SQAP`, `unit-tests` |
| `<subject>` | Short description (≤ 50 chars) | `Add door open command handler` |
| `<body>` | Detailed description (optional) | Explain why, not what |
| `Refs:` | Reference to CR, PR, or issue | `Refs: CR-TDC-20260330-001` |

**Commit Types**:
- `feat` — New feature or functionality
- `fix` — Bug fix
- `docs` — Documentation update
- `test` — Test code addition or modification
- `refactor` — Code refactoring (no functional change)
- `style` — Code style or formatting change
- `build` — Build system or configuration change
- `ci` — Continuous integration configuration
- `chore` — Maintenance task (e.g., updating .gitignore)

**Examples**:
```
feat(DSM): Add door state machine transition logic

Implement state transitions for CLOSED → OPENING → OPEN
per SRS requirement REQ-TDC-DSM-005.

Refs: DOC-TDC-SRS-001
```

```
fix(PSM): Correct platform detection timeout

Previous timeout was 100ms (too short). Updated to 500ms
per safety analysis FMEA-TDC-003.

Refs: CR-TDC-20260330-001
```

```
docs(SQAP): Update review checklist for Phase 5

Added MISRA C:2012 Rule 21.3 to checklist per VER feedback.

Refs: DOC-TDC-SQAP-001
```

### 6.5 Tagging Convention

Git tags are used to mark baselines. See Section 5.5 for tag naming convention.

**Tag Creation Process**:
1. CM receives COD gate approval notification
2. CM verifies all required CIs are present and signed
3. CM creates baseline manifest (see Appendix C)
4. CM creates annotated Git tag:
   ```bash
   git tag -a TDC-BL-PHASE1-v1.0 -m "Planning baseline (Phase 1 gate)"
   git push origin TDC-BL-PHASE1-v1.0
   ```
5. CM archives baseline manifest to `baselines/<baseline-name>/manifest.yaml`
6. CM updates configuration status accounting

**Tag Protection**:
- Baseline tags are **immutable** — once created, they SHALL NOT be deleted or modified
- If a tag must be corrected, create a new minor version (e.g., `v1.1`)
- **Violation Protocol**: Deletion or force-push of a baseline tag without CCB approval + Software Change Record is a **CRITICAL violation** — CM SHALL immediately invoke PM

---

## 7. Baseline Management

### 7.1 Baseline Definition

Per EN 50128:2011 §9.1.4.2:

> "The configuration management system shall record the baseline configuration which consists of all items which are necessary to reproduce the released software, including the compiler and its version."

A **baseline** is:
- A formally approved version of a set of configuration items
- Created at each COD phase gate
- Immutably recorded via Git tag + manifest file
- Includes all documents, source code, tests, evidence, and tool versions
- Ensures reproducibility throughout the operational lifetime (§9.1.4.3)

### 7.2 Baseline Types

One baseline is created at each phase gate. The following table maps phases to baseline names:

| Gate | Phase | Baseline Name | VER Report Required | VAL Role |
|------|-------|---------------|---------------------|----------|
| 1 | Planning | `planning-baseline` | SQAVR (Software Quality Assurance Verification Report) | 2nd check (items 1, 3, 4 only)† |
| 2 | Requirements | `requirements-baseline` | REQVER (Software Requirements Verification Report) | 2nd check |
| 3 | Architecture & Design | `design-baseline` | ARCHDESIGNVER (Software Architecture and Design Verification Report) | 2nd check |
| 4 | Component Design | `component-design-baseline` | COMPDESIGNVER (Software Component Design Verification Report) | 2nd check |
| 5 | Implementation & Testing | `implementation-baseline` | SOURCECODEVER (Software Source Code Verification Report) | 2nd check |
| 6 | Integration | `integration-baseline` | VER review (INTVER produced in Phase 7) | 2nd check |
| 7 | Validation | `release-baseline` ★ | INTVER (Software Integration Verification Report) | Formal VALRPT (§6.3.4.10) |
| 9 | Deployment | `deployment-baseline` | DEPLOYVER (Deployment Verification Report) | 2nd check (items 36–39 only) |
| Per-CR | Maintenance (Phase 10) | `maintenance-baseline-<CR-ID>` | MAINTVER (Software Maintenance Verification Report) | 2nd check |

† Gate 1 VAL 2nd check applies to items 1 (SQAP), 3 (SCMP), and 4 (SVP) only. Item 5 (SVaP) has no VAL 2nd check per DELIVERABLES.md.

★ **Release baseline** (Phase 7) is the most critical. Per §6.3.4.10, the Software Validation Report MUST explicitly state this baseline. Per §9.1.4.3, reproducibility is required throughout the operational lifetime.

### 7.3 Baseline Creation Procedure

The following 7-step procedure is executed at each phase gate:

**Pre-conditions**:
1. All phase deliverables are complete and signed
2. VER report is signed and approved by VMGR (SIL 3 mandatory)
3. VAL 2nd check is complete (or formal VAL report signed for Phase 7)
4. QUA review is complete
5. COD gate-check has passed

**Procedure**:

| Step | Actor | Action | EN 50128 Clause |
|------|-------|--------|-----------------|
| 1 | COD | Notify CM that gate has passed | — |
| 2 | CM | Verify all required documents are signed and present at canonical paths | §6.6, D.48 |
| 3 | CM | Verify all evidence artifacts are present per VER report | §6.2.4.8 |
| 4 | CM | Create baseline manifest (see Appendix C) listing all CIs with versions | §9.1.4.2 |
| 5 | CM | Record tool versions (compiler, static analyzer, test framework) | §9.1.4.2 |
| 6 | CM | Create Git tag per Section 6.5 | §9.1.4.2 |
| 7 | CM | Archive manifest to `baselines/<baseline-name>/manifest.yaml` | §9.1.4.2 |

**Post-conditions**:
- Baseline is immutably recorded
- All CIs are under configuration control
- Configuration status accounting is updated
- Baseline is reproducible (§9.1.4.3)

**Responsible, Accountable, Consulted, Informed (RACI)**:

| Actor | Responsibility |
|-------|----------------|
| COD | **Accountable** — authorizes baseline creation (gate approval) |
| CM | **Responsible** — executes baseline procedure (steps 2–7) |
| VER | **Consulted** — provides evidence list, confirms completeness |
| VAL | **Consulted** — confirms verification process complete (§6.3.4.9) |
| PM | **Informed** — receives baseline completion notification |
| QUA | **Informed** — receives baseline completion notification |

### 7.4 Baseline Content

Each baseline includes:

| CI Category | Examples | Verification |
|-------------|----------|--------------|
| **Documents** | All deliverables for the phase (e.g., SQAP, SRS, SAS) | Signed, dated, at canonical path |
| **Source Code** | All .c and .h files in `src/` (Phases 5+) | Git commit SHA recorded |
| **Test Code** | All .c files in `tests/` (Phases 5+) | Git commit SHA recorded |
| **Build Configuration** | Makefiles, compiler flags | Git commit SHA recorded |
| **Evidence Artifacts** | MISRA reports, coverage data, test logs | Present in `evidence/` per VER report |
| **VER Report** | Phase-specific Verification Report | Signed, approved by VMGR |
| **VAL Report** | Software Validation Report (Phase 7 only) | Signed, approved by VMGR |
| **Tool Versions** | Compiler, static analyzer, test framework, coverage tools | Recorded in manifest |
| **Baseline Manifest** | YAML file listing all CIs and versions | Stored in `baselines/<baseline-name>/` |

### 7.5 Baseline Reproducibility

Per EN 50128:2011 §9.1.4.3:

> "It shall be possible, throughout the operational lifetime of the software, to reproduce the software and any of its components from the baselined information."

CM ensures reproducibility by:
1. Recording exact tool versions (compiler, linker, libraries)
2. Recording all build flags and configuration options
3. Recording all source file Git commit SHAs
4. Recording all external dependencies (e.g., third-party libraries — if any)
5. Storing baseline manifest in version control
6. Maintaining backup copies of the Git repository (see Section 12)

**Reproducibility Test**: CM SHALL periodically verify that the software can be rebuilt from a baseline by:
1. Checking out the baseline Git tag
2. Installing the exact tool versions per manifest
3. Running the build process
4. Comparing binary checksums (SHA-256) with the original baseline

---

## 8. Change Control Process

### 8.1 Change Control Overview

Per EN 50128:2011 §6.6.4.1, every change to a configuration item under baseline control MUST be processed through the formal change control procedure.

**Change Control Flow**:

```
1. Change Identified
   ├─► Problem Report (PR-TDC-*)      [Defect detected]
   └─► Change Request (CR-TDC-*)      [Enhancement or requirement change]

2. CR Submitted
   ├─► Initiator fills CR template (see Appendix B)
   ├─► CM assigns CR-ID
   └─► CM logs CR in tracking system

3. Impact Analysis
   ├─► Technical Reviewers assess affected CIs
   ├─► SAF assesses safety impact
   ├─► QUA assesses quality impact
   ├─► VER assesses verification impact
   └─► CM estimates re-entry phase per §6.6.4.2

4. CCB Review
   ├─► PM chairs meeting
   ├─► COD assesses lifecycle impact
   ├─► CCB votes: APPROVE / REJECT / DEFER
   └─► CM records decision

5. CR Approved
   ├─► COD authorizes phase re-entry (§6.6.4.2)
   ├─► PM assigns work to technical team
   └─► CM updates affected CI status

6. Change Implementation
   ├─► Assigned agents (REQ, DES, IMP, etc.) implement change
   ├─► All affected CIs are updated (§6.6.4.1(e,f))
   └─► Traceability maintained (§6.6.4.1(i))

7. Verification & Testing
   ├─► VER verifies change implementation
   ├─► TST executes regression tests
   └─► VER produces verification report

8. CCB Closure Review
   ├─► VER report reviewed
   ├─► All nine aspects (a–i) confirmed complete
   └─► CCB approves CR closure

9. Baseline Update
   ├─► CM creates new minor baseline version (e.g., v1.1)
   ├─► CM updates configuration status accounting
   └─► CM notifies all relevant parties (§6.6.4.1(h))
```

### 8.2 Nine Required Aspects (§6.6.4.1)

Per EN 50128:2011 §6.6.4.1, every Software Change Record SHALL address all nine aspects:

| Aspect | Requirement | CR Template Section |
|--------|-------------|---------------------|
| **(a)** | Unique identification of the change | CR ID (e.g., CR-TDC-20260330-001) |
| **(b)** | Recording of the reasons for the change | Description, Rationale |
| **(c)** | Analysis of the consequences of the change | Impact Analysis (technical, safety, quality, verification) |
| **(d)** | Approval of the change by authorised personnel | CCB Decision (PM, COD, Safety Manager signatures) |
| **(e)** | Updating of all affected documents | Affected CIs list → Document updates recorded |
| **(f)** | Recording of all affected software items (CIs) | Affected CIs list (documents, source files, tests) |
| **(g)** | Implementation, verification and test of the change | Implementation section + VER report reference |
| **(h)** | Reporting to all relevant parties | Notification list → CM sends closure notice |
| **(i)** | Maintaining traceability of the change throughout the lifecycle | Traceability Impact section + RTM updates |

**Violation Protocol**: If a CR is submitted or approved without addressing all nine aspects, CM SHALL return it to the originator as a **MAJOR violation**.

### 8.3 Phase Re-entry (§6.6.4.2)

Per EN 50128:2011 §6.6.4.2:

> "All changes, including software fault correction, shall initiate a return to an appropriate stage of the software lifecycle."

CM, in consultation with COD, determines the **re-entry phase** based on the change impact:

| Change Type | Re-entry Phase | Rationale |
|-------------|----------------|-----------|
| Documentation typo (no technical impact) | Same phase | Minimal impact; no downstream effects |
| SRS requirement change | Phase 2 (Requirements) | Must re-verify SRS, update RTM, re-verify downstream |
| Design change (algorithm modification) | Phase 3 (Design) | Must re-verify design, update code, re-test |
| Code bug fix (no design impact) | Phase 5 (Implementation) | Must re-verify code, re-run unit tests, regression tests |
| Integration issue | Phase 6 (Integration) | Must re-run integration tests |
| Validation failure | Phase 7 (Validation) | Must re-run validation tests |
| Production defect | Phase 10 (Maintenance) | Follow maintenance CR procedure |

**COD Authority**: COD has final authority on phase re-entry. If COD determines that a CR requires re-entry to an earlier phase than proposed by the technical team, **COD's decision cannot be overridden**.

### 8.4 Change Control Board (CCB) Operation

**CCB Meeting Frequency**:
- **Ad-hoc** — scheduled within 5 working days of CR submission
- **Regular** — bi-weekly during active development phases

**CCB Meeting Procedure**:
1. CM distributes CR package (CR document + impact analysis) 2 days before meeting
2. PM chairs meeting
3. Technical reviewers present impact analysis
4. SAF presents safety impact assessment
5. QUA presents quality impact assessment
6. VER presents verification impact assessment
7. COD presents lifecycle impact assessment
8. CCB votes: APPROVE / REJECT / DEFER
9. CM records decision and action items
10. CM distributes meeting minutes within 1 working day

**Decision Criteria**:
- **APPROVE** — if all impacts are acceptable and resources are available
- **REJECT** — if safety impact is unacceptable, or cost/schedule impact is prohibitive
- **DEFER** — if more information is needed, or resources are not currently available

**Voting Rules**:
- **PM** has one vote (chair)
- **COD** has veto power on lifecycle impact
- **Safety Manager** has veto power on safety impact
- **VMGR** is consulted (not a voting member) if CR affects V&V activities
- Simple majority required for APPROVE

---

## 9. Change Request Document Format

All Change Requests SHALL follow the template in Appendix B. The following sections are MANDATORY:

### 9.1 CR Header

| Field | Description | Example |
|-------|-------------|---------|
| CR ID | Unique identifier per Section 5.6 | CR-TDC-20260330-001 |
| Submitted By | Initiator name and role | John Doe (TST) |
| Date Submitted | Date CR created | 2026-03-30 |
| Related PR | Problem Report ID (if applicable) | PR-TDC-20260330-001 |
| Type | Change type (see below) | Defect, Enhancement, Requirement Change |
| Priority | Priority level (see below) | Critical, High, Medium, Low |
| Status | Current status (see below) | Submitted, Under Review, Approved, Implemented, Closed |

**Change Types**:
- **Defect** — Bug fix or non-conformance correction
- **Enhancement** — New feature or improvement
- **Requirement Change** — Modification to SRS or system requirements
- **Process Change** — Modification to SQAP, SCMP, SVP, SVaP

**Priority Levels**:
- **Critical** — Safety-critical defect; blocks gate passage; must be fixed immediately
- **High** — Non-safety defect; significant impact on functionality or schedule
- **Medium** — Moderate impact; can be deferred to next phase
- **Low** — Minor issue; cosmetic or documentation-only

**Status Values**:
- **Submitted** — CR created, awaiting impact analysis
- **Under Review** — Impact analysis in progress
- **Approved** — CCB approved; awaiting implementation
- **Rejected** — CCB rejected
- **Deferred** — CCB deferred decision
- **Implemented** — Change implemented; awaiting verification
- **Closed** — Verification complete; baseline updated

### 9.2 CR Body Sections

| Section | Requirement | Aspect (§6.6.4.1) |
|---------|-------------|-------------------|
| **Description** | Detailed description of the change | (b) |
| **Rationale** | Why the change is needed | (b) |
| **Affected CIs** | List all documents, source files, tests affected | (f) |
| **Impact Analysis** | Technical, safety, quality, verification, schedule impacts | (c) |
| **Traceability Impact** | How RTM and other traceability matrices are affected | (i) |
| **Phase Re-entry** | Which phase must be re-entered per §6.6.4.2 | (c) |
| **CCB Decision** | Approve/Reject/Defer + signatures | (d) |
| **Implementation Plan** | Who, what, when | (g) |
| **Verification Plan** | How the change will be verified | (g) |
| **Test Plan** | Regression tests required | (g) |
| **Notification List** | Who must be informed of CR closure | (h) |
| **Document Updates** | Which documents must be updated | (e) |

See Appendix B for the complete CR template.

---

## 10. Build Management

### 10.1 Build System

The TDC project uses **GNU Make** as the build system.

| Tool | Purpose | Version | Classification |
|------|---------|---------|----------------|
| GNU Make | Build automation | ≥ 4.0 | T1 (no qualification required) |
| GCC | C compiler | ≥ 9.0 | T2 (reduced verification on output) |
| GNU ld | Linker | ≥ 2.30 | T2 (reduced verification on output) |

**Rationale**: GNU Make is a widely-used, industry-standard build automation tool. Per EN 50128:2011 §7.4.4.14 and Table A.20, GNU Make is classified as a **T1 tool** (generates no output that becomes part of the safety software). **No tool qualification is required.**

GCC (compiler) and GNU ld (linker) are classified as **T2 tools** (output requires reduced verification). The VER agent performs static analysis on the source code (MISRA C:2012) and verifies that the compiler output matches expected behavior through unit and integration testing.

### 10.2 Build Configuration

All build configurations are version-controlled in the `Makefile` and `.build/` directory.

**Compiler Flags** (SIL 3 mandatory):
```makefile
CFLAGS = -std=c11 \
         -Wall -Wextra -Werror \
         -pedantic \
         -O2 \
         -g \
         -fno-builtin \
         -fno-common \
         -fstack-protector-strong \
         -D_FORTIFY_SOURCE=2
```

**Prohibited Features** (MISRA C:2012 + SIL 3):
- No dynamic memory allocation (`-fno-builtin` disables malloc/free)
- No recursion (enforced by static analysis)
- No function pointers (except where explicitly justified and documented)
- No `goto` statements (except forward-only goto for error handling)

### 10.3 Reproducible Builds

Per EN 50128:2011 §9.1.4.2–3, builds must be reproducible.

**Reproducibility Measures**:
1. **Exact tool versions** recorded in baseline manifest
2. **Deterministic compilation** — compiler flags ensure consistent output
3. **Build date/time removed** — no `__DATE__` or `__TIME__` macros used
4. **Build environment documented** — OS version, library versions recorded
5. **Binary checksums** — SHA-256 checksums recorded for all executables

**Build Verification**:
1. CM checks out baseline tag
2. CM sets up build environment per manifest
3. CM runs `make clean && make`
4. CM compares SHA-256 checksum of resulting binary with baseline
5. If checksums match → build is reproducible ✅
6. If checksums differ → investigate and document discrepancy ⚠️

### 10.4 Build Artifacts

| Artifact | Generated By | Version Controlled? | Stored Where |
|----------|-------------|---------------------|--------------|
| Object files (.o) | GCC | ❌ No (build-time only) | `build/` (ignored by Git) |
| Executables | GNU ld | ❌ No (build-time only) | `build/` (ignored by Git) |
| Libraries (.a) | ar | ❌ No (build-time only) | `build/` (ignored by Git) |
| Dependency files (.d) | GCC | ❌ No (build-time only) | `build/` (ignored by Git) |
| Coverage data (.gcda, .gcno) | gcov | ✅ Yes (evidence) | `evidence/coverage/` |
| MISRA reports (.xml) | MISRA checker | ✅ Yes (evidence) | `evidence/static-analysis/` |
| Test logs (.log) | Unity | ✅ Yes (evidence) | `evidence/test-logs/` |
| Release binary (final) | GNU ld | ✅ Yes (Phase 9) | `release/` |

**Build Outputs NOT Version-Controlled**:
- All files in `build/` directory are added to `.gitignore`
- Intermediate build artifacts are regenerated on each build
- Only final release binary (Phase 9) is version-controlled

---

## 11. Problem Reporting

### 11.1 Problem Report (PR) Process

A **Problem Report (PR)** records a detected defect, non-conformance, or issue.

**PR Sources**:
- **VER** — MISRA violations, static analysis findings, traceability gaps
- **TST** — Unit test failures, integration test failures
- **QUA** — Document review findings, audit findings
- **VAL** — Validation test failures, acceptance criteria not met
- **ASR** — Independent assessment findings
- **Customer** — User-reported issues (post-deployment)

**PR Workflow**:
```
1. Defect Detected
   └─► Detector logs PR-TDC-YYYYMMDD-NNN

2. PR Triage (PM + Technical Lead)
   ├─► Severity: Critical / High / Medium / Low
   ├─► Classify: Defect / Documentation / Process
   └─► Assign to: Responsible agent (IMP, DES, REQ, etc.)

3. Investigation
   ├─► Root cause analysis
   └─► Determine if CR is needed

4. Resolution
   ├─► If CR needed → Submit CR-TDC-YYYYMMDD-NNN
   ├─► If no CR needed → Fix directly (minor documentation typo)
   └─► Update PR status

5. Verification
   ├─► VER verifies fix
   └─► TST runs regression tests

6. Closure
   ├─► PM approves closure
   └─► CM updates PR status to CLOSED
```

### 11.2 PR Template

All PRs SHALL include:

| Field | Description |
|-------|-------------|
| **PR ID** | Unique identifier (PR-TDC-YYYYMMDD-NNN) |
| **Reported By** | Name and role |
| **Date Reported** | Date PR created |
| **Severity** | Critical / High / Medium / Low |
| **Phase Detected** | Which phase the defect was found |
| **Description** | Detailed description of the defect |
| **Steps to Reproduce** | How to trigger the defect (if applicable) |
| **Expected Behavior** | What should happen |
| **Actual Behavior** | What actually happened |
| **Affected CIs** | Which documents, source files, or tests are affected |
| **Root Cause** | Determined during investigation |
| **Resolution** | How the defect was fixed |
| **Related CR** | CR-TDC-YYYYMMDD-NNN (if applicable) |
| **Status** | Open / Under Investigation / Resolved / Closed |

### 11.3 Relationship to NCR Process

The **Non-Conformance Report (NCR)** process is defined in the SQAP (DOC-TDC-SQAP-001).

**Distinction**:
- **PR** — Technical defect (code bug, test failure, traceability gap)
- **NCR** — Process non-conformance (missed review, unsigned document, incorrect template)

**Integration**:
- If a PR reveals a process non-conformance, QUA opens an NCR
- If an NCR identifies a technical defect, the originator opens a PR
- Both PR and NCR may trigger a Change Request (CR)

---

## 12. Backup and Recovery

### 12.1 Repository Backup

CM is responsible for ensuring the Git repository is backed up regularly.

**Backup Schedule**:
- **Daily** — Automated backup to on-site backup server
- **Weekly** — Automated backup to off-site backup location
- **After each baseline** — Manual backup to offline storage (USB drive or external hard drive)

**Backup Procedure**:
1. Create Git bundle:
   ```bash
   git bundle create TDC-backup-YYYYMMDD.bundle --all
   ```
2. Verify bundle integrity:
   ```bash
   git bundle verify TDC-backup-YYYYMMDD.bundle
   ```
3. Copy bundle to backup location
4. Record backup in CM backup log

**Backup Verification**:
- CM SHALL periodically verify that backups can be restored
- Test restoration procedure at least once per phase

### 12.2 Recovery Procedure

In the event of repository corruption or loss:

1. **Identify Loss**
   - CM detects repository corruption or data loss
   - CM notifies PM and COD immediately

2. **Assess Impact**
   - Determine which commits are lost
   - Identify last known good baseline

3. **Restore from Backup**
   - Retrieve most recent backup bundle
   - Clone repository from bundle:
     ```bash
     git clone TDC-backup-YYYYMMDD.bundle TDC-restored
     ```
   - Verify all baselines and tags are present

4. **Verify Restoration**
   - CM verifies all baseline tags are present
   - CM compares restored files with baseline manifests
   - VER performs spot checks on critical files

5. **Resume Operations**
   - CM notifies all team members
   - CM updates configuration status accounting
   - PM assesses schedule impact

**Recovery Time Objective (RTO)**: 4 hours (maximum time to restore repository from backup)

**Recovery Point Objective (RPO)**: 1 day (maximum acceptable data loss — daily backups)

### 12.3 Off-site Storage

CM maintains off-site backups at a secure location separate from the primary development site.

**Off-site Backup Schedule**:
- **Weekly** — Automated sync to cloud storage (encrypted)
- **After each baseline** — Physical backup media (USB drive) stored at off-site location

**Security**:
- All off-site backups are encrypted using AES-256
- Encryption keys are stored in secure key management system
- Physical backup media are stored in locked, access-controlled facility

---

## 13. Configuration Audits

### 13.1 Audit Overview

Per EN 50128:2011 §6.6, CM supports configuration audits to verify baseline completeness and integrity.

**Audit Types**:
1. **Baseline Presence Check** (CM responsibility) — verify all required CIs are present and correctly versioned
2. **Functional Completeness Check** (VER responsibility per §6.2.4.7) — verify requirements are satisfied
3. **Evidence Retention Check** (CM presence check per §6.2.4.8) — verify all VER evidence artifacts are stored at canonical paths

**Terminology Note**: EN 50128:2011 does **NOT** define "FCA" (Functional Configuration Audit) or "PCA" (Physical Configuration Audit). Those terms come from MIL-STD-973 / IEEE 828. See Section 4.1 for the EN 50128 mapping.

### 13.2 Baseline Presence Check (CM)

CM performs this check at each baseline creation (Section 7.3, Steps 2–3):

**Checklist**:
- ✅ All required documents are present per DELIVERABLES.md
- ✅ All documents are signed and dated
- ✅ All documents are stored at canonical paths per document registry
- ✅ All source code files are committed to Git
- ✅ All test code files are committed to Git
- ✅ All evidence artifacts are present per VER report
- ✅ All evidence artifacts are stored at canonical evidence paths
- ✅ Baseline manifest is complete and accurate
- ✅ Git tag is created and pushed to remote
- ✅ Tool versions are recorded in manifest

**Output**: CM produces a **Baseline Presence Check Report** documenting the results.

### 13.3 Functional Completeness Check (VER)

VER performs this check per §6.2.4.7:

> "The Verifier shall check the functional completeness of the software items against the specification(s) at each lifecycle stage."

**Checklist** (examples):
- ✅ All SRS requirements are allocated to design elements (Phase 3)
- ✅ All design elements are implemented in source code (Phase 5)
- ✅ All source code units have corresponding unit tests (Phase 5)
- ✅ All unit tests have passed (Phase 5)
- ✅ All MISRA violations are resolved or justified (Phase 5)
- ✅ Traceability matrices are complete and accurate (all phases)

**Output**: VER produces a **phase-specific Verification Report** (e.g., REQVER, SOURCECODEVER).

### 13.4 Evidence Retention Check (CM)

Per §6.2.4.8:

> "Results of each verification activity shall be retained in a format which is defined or referenced in the Software Verification Plan."

CM verifies that all evidence artifacts listed in the VER report are present at canonical paths.

**Checklist**:
- ✅ MISRA reports present in `evidence/static-analysis/`
- ✅ Coverage data present in `evidence/coverage/`
- ✅ Unit test logs present in `evidence/test-logs/`
- ✅ Design review checklists present in `evidence/design-review/`
- ✅ Integration test logs present in `evidence/integration-test-logs/`
- ✅ System test logs present in `evidence/system-test-logs/`
- ✅ All evidence files are version-controlled

**Output**: CM includes evidence retention status in the **Baseline Presence Check Report**.

### 13.5 Audit Schedule

| Audit Type | Frequency | Conducted By | Output |
|------------|-----------|--------------|--------|
| Baseline Presence Check | At each phase gate (8 times) | CM | Baseline Presence Check Report |
| Functional Completeness Check | At each phase gate (8 times) | VER | Phase-specific Verification Report |
| Evidence Retention Check | At each phase gate (8 times) | CM | Section in Baseline Presence Check Report |
| QUA Process Audit | Once per phase | QUA | QUA Audit Report (per SQAP) |
| Independent Assessment | Phase 8 (once) | ASR | Software Assessment Report |

### 13.6 Audit Non-Conformances

If an audit identifies a non-conformance:

1. **CM logs NCR** (Non-Conformance Report per SQAP)
2. **PM assigns corrective action** to responsible agent
3. **Agent implements correction**
4. **VER verifies correction**
5. **CM updates configuration status accounting**
6. **QUA approves NCR closure**

**Gate Impact**: If a non-conformance is detected during a Baseline Presence Check, the phase gate CANNOT be passed until the non-conformance is resolved.

---

## 14. Configuration Status Accounting

### 14.1 Overview

CM maintains **configuration status accounting** to track the state of all configuration items throughout the lifecycle.

Per EN 50128:2011 §6.6:

> "Configuration status accounting shall provide information on the status of configuration items throughout the lifecycle."

### 14.2 Status Tracking

CM tracks the following status information for each CI:

| Attribute | Description | Example |
|-----------|-------------|---------|
| **CI ID** | Unique identifier | DOC-TDC-SRS-001, TDC-SRC-DSM-001.c |
| **Version** | Current version number | 1.0, 1.1, 2.0 |
| **Git Commit SHA** | Git commit hash | `a1b2c3d4e5f6...` |
| **Status** | Current status (see below) | Draft, Under Review, Approved, Baselined |
| **Baseline** | Which baseline includes this CI | TDC-BL-REQUIREMENTS-v1.0 |
| **Last Modified** | Date of last change | 2026-03-30 |
| **Modified By** | Agent or person who last modified | REQ, DES, IMP |
| **Related CRs** | Change requests affecting this CI | CR-TDC-20260330-001 |
| **Related PRs** | Problem reports affecting this CI | PR-TDC-20260330-001 |

**CI Status Values**:
- **Draft** — CI created, not yet reviewed
- **Under Review** — QUA or VER review in progress
- **Approved** — Review complete, approved
- **Baselined** — Included in a baseline
- **Obsolete** — Superseded by a newer version

### 14.3 Configuration Status Report

CM produces a **Configuration Status Report** at the following milestones:
- End of each phase (before gate check)
- After each baseline creation
- After each CCB meeting (if CRs are approved)
- On request from PM, COD, or VMGR

**Report Contents**:

| Section | Content |
|---------|---------|
| **1. Project Overview** | Project name, SIL level, current phase, completion % |
| **2. Baseline Status** | List of all baselines created, with dates and Git tags |
| **3. CI Summary** | Total number of CIs by category (documents, source files, tests) |
| **4. CI Version Status** | Table of all CIs with current version, status, baseline |
| **5. Open CRs** | List of all open Change Requests with status |
| **6. Open PRs** | List of all open Problem Reports with status |
| **7. Traceability Status** | Summary of RTM coverage (SYS-REQ → SW-REQ → Code → Test) |
| **8. Evidence Completeness** | Summary of evidence artifacts per phase |
| **9. Audit Findings** | Open non-conformances from audits |
| **10. Metrics** | CM metrics (see Section 14.4) |

### 14.4 CM Metrics

CM tracks the following metrics:

| Metric | Purpose | Target |
|--------|---------|--------|
| **Total CRs Submitted** | Trend analysis | — |
| **CRs Approved** | CCB approval rate | ≥ 70% |
| **CRs Rejected** | CCB rejection rate | ≤ 30% |
| **CRs Deferred** | CCB deferral rate | ≤ 10% |
| **Average CR Processing Time** | Efficiency | ≤ 10 working days |
| **CRs per Phase** | Change impact by phase | — |
| **Open PRs** | Current defect backlog | 0 at each gate |
| **Baseline Tags Created** | Progress tracking | 8 (Phases 1–9) |
| **Configuration Audit Findings** | Baseline quality | 0 non-conformances at each gate |

---

## 15. Tool Qualification

### 15.1 Tool Classification

Per EN 50128:2011 §7.4.4.14 and Table A.20, all tools are classified as T1, T2, or T3:

| Class | Description | Qualification Required? |
|-------|-------------|-------------------------|
| **T1** | Generates no output forming part of the safety software; errors cannot introduce errors into the safety software | ❌ No qualification required |
| **T2** | Supports the development of safety software; output requires reduced verification effort | ⚠️ Reduced verification on output |
| **T3** | Generates output that directly forms part of the safety software | ✅ Full tool qualification required |

### 15.2 TDC Project Tools

The following tools are used in the TDC project:

| Tool | Purpose | Version | Class | Qualification |
|------|---------|---------|-------|---------------|
| **Git** | Version control | ≥ 2.30 | T1 | None |
| **GNU Make** | Build automation | ≥ 4.0 | T1 | None |
| **GCC** | C compiler | ≥ 9.0 | T2 | Reduced verification (static analysis + testing) |
| **GNU ld** | Linker | ≥ 2.30 | T2 | Reduced verification (static analysis + testing) |
| **Cppcheck** | MISRA C:2012 checker | ≥ 2.0 | T1 | None (VER verifies output manually) |
| **gcov/lcov** | Code coverage | ≥ 9.0 | T1 | None (VER verifies coverage manually) |
| **Unity** | Unit test framework | ≥ 2.5 | T1 | None (TST verifies test results manually) |
| **Lizard** | Cyclomatic complexity | ≥ 1.17 | T1 | None (VER verifies CCN manually) |

**Rationale**:
- **Git, GNU Make, Cppcheck, gcov/lcov, Unity, Lizard** — T1 tools generate reports or metrics that are manually reviewed by VER. Errors in these tools cannot introduce errors into the safety software. **No qualification required.**
- **GCC, GNU ld** — T2 tools generate executable code. However, the TDC project uses **reduced verification** (MISRA C:2012 static analysis + 100% statement/branch/condition coverage + integration testing) to ensure the output is correct. **No full tool qualification required.**

### 15.3 Tool Version Control

CM records exact tool versions in each baseline manifest (see Appendix C).

**Version Recording Procedure**:
1. CM runs version query commands:
   ```bash
   git --version
   gcc --version
   ld --version
   cppcheck --version
   lcov --version
   lizard --version
   ```
2. CM records output in baseline manifest `tools:` section
3. CM commits manifest to `baselines/<baseline-name>/manifest.yaml`

**Tool Change Control**:
- If a tool version is upgraded, CM SHALL:
  1. Open a CR (e.g., CR-TDC-20260415-001: Upgrade GCC from 9.0 to 10.0)
  2. CCB reviews impact
  3. VER verifies that tool upgrade does not affect output (regression tests)
  4. CM updates baseline manifest with new tool version

---

## Appendix A: Configuration Item Registry

This appendix lists all Configuration Items for the TDC project, organized by lifecycle phase.

### Phase 0 — System-Level Documents

| CI ID | Document Name | Filename | Path |
|-------|---------------|----------|------|
| DOC-TDC-SRS-SYS-001 | System Requirements Specification | System-Requirements-Specification.md | `docs/system/` |
| DOC-TDC-SAD-SYS-001 | System Architecture Description | System-Architecture-Description.md | `docs/system/` |
| DOC-TDC-SSP-SYS-001 | System Safety Plan | System-Safety-Plan.md | `docs/system/` |
| DOC-TDC-SSRS-SYS-001 | System Safety Requirements Specification | System-Safety-Requirements-Specification.md | `docs/system/` |

### Phase 1 — Planning

| CI ID | Document Name | Filename | Path |
|-------|---------------|----------|------|
| DOC-TDC-SQAP-001 | Software Quality Assurance Plan | Software-Quality-Assurance-Plan.md | `docs/` |
| DOC-TDC-SCMP-001 | Software Configuration Management Plan | Software-Configuration-Management-Plan.md | `docs/` |
| DOC-TDC-SVP-001 | Software Verification Plan | Software-Verification-Plan.md | `docs/` |
| DOC-TDC-SVaP-001 | Software Validation Plan | Software-Validation-Plan.md | `docs/` |
| DOC-TDC-SQAVR-001 | Software Quality Assurance Verification Report | Software-Quality-Assurance-Verification-Report.md | `docs/reports/` |

### Phase 2 — Requirements

| CI ID | Document Name | Filename | Path |
|-------|---------------|----------|------|
| DOC-TDC-SRS-001 | Software Requirements Specification | Software-Requirements-Specification.md | `docs/` |
| DOC-TDC-OTSTSPEC-001 | Overall Software Test Specification | Overall-Software-Test-Specification.md | `docs/` |
| DOC-TDC-REQVER-001 | Software Requirements Verification Report | Software-Requirements-Verification-Report.md | `docs/reports/` |

### Phase 3 — Architecture & Design

| CI ID | Document Name | Filename | Path |
|-------|---------------|----------|------|
| DOC-TDC-SAS-001 | Software Architecture Specification | Software-Architecture-Specification.md | `docs/` |
| DOC-TDC-SDS-001 | Software Design Specification | Software-Design-Specification.md | `docs/` |
| DOC-TDC-SIS-001 | Software Interface Specifications | Software-Interface-Specifications.md | `docs/` |
| DOC-TDC-INTTESTSPEC-001 | Software Integration Test Specification | Software-Integration-Test-Specification.md | `docs/` |
| DOC-TDC-HWINTTESTSPEC-001 | Software/Hardware Integration Test Specification | Software-Hardware-Integration-Test-Specification.md | `docs/` |
| DOC-TDC-ARCHDESIGNVER-001 | Software Architecture and Design Verification Report | Software-Architecture-and-Design-Verification-Report.md | `docs/reports/` |

### Phase 4 — Component Design

| CI ID | Document Name | Filename | Path |
|-------|---------------|----------|------|
| DOC-TDC-COMPDESIGN-001 | Software Component Design Specification | Software-Component-Design-Specification.md | `docs/` |
| DOC-TDC-COMPTESTSPEC-001 | Software Component Test Specification | Software-Component-Test-Specification.md | `docs/` |
| DOC-TDC-COMPDESIGNVER-001 | Software Component Design Verification Report | Software-Component-Design-Verification-Report.md | `docs/reports/` |

### Phase 5 — Implementation & Testing

| CI ID | Document Name | Filename | Path |
|-------|---------------|----------|------|
| TDC-SRC-* | Source code files (C, MISRA C:2012) | *.c, *.h | `src/` |
| TDC-TST-* | Unit test files (Unity framework) | *.c | `tests/unit/` |
| DOC-TDC-SOURCECODEVER-001 | Software Source Code Verification Report | Software-Source-Code-Verification-Report.md | `docs/` |
| DOC-TDC-COMPTESTRPT-001 | Software Component Test Report | Software-Component-Test-Report.md | `docs/` |

### Phase 6 — Integration

| CI ID | Document Name | Filename | Path |
|-------|---------------|----------|------|
| TDC-TST-INT-* | Integration test files | *.c | `tests/integration/` |
| DOC-TDC-INTTESTRPT-001 | Software Integration Test Report | Software-Integration-Test-Report.md | `docs/` |
| DOC-TDC-HWINTTESTRPT-001 | Software/Hardware Integration Test Report | Software-Hardware-Integration-Test-Report.md | `docs/` |

### Phase 7 — Validation

| CI ID | Document Name | Filename | Path |
|-------|---------------|----------|------|
| DOC-TDC-INTVER-001 | Software Integration Verification Report | Software-Integration-Verification-Report.md | `docs/` |
| DOC-TDC-OVERALLTESTRPT-001 | Overall Software Test Report | Overall-Software-Test-Report.md | `docs/` |
| DOC-TDC-VALRPT-001 | Software Validation Report | Software-Validation-Report.md | `docs/` |
| DOC-TDC-TOOLSVALRPT-001 | Tools Validation Report | Tools-Validation-Report.md | `docs/` |
| DOC-TDC-RELEASENOTE-001 | Release Note | Release-Note.md | `docs/` |

### Phase 8 — Assessment

| CI ID | Document Name | Filename | Path |
|-------|---------------|----------|------|
| DOC-TDC-ASSESSPLAN-001 | Software Assessment Plan | Software-Assessment-Plan.md | `docs/` |
| DOC-TDC-ASSESSRPT-001 | Software Assessment Report | Software-Assessment-Report.md | `docs/` |

### Phase 9 — Deployment

| CI ID | Document Name | Filename | Path |
|-------|---------------|----------|------|
| DOC-TDC-DEPLOYPLAN-001 | Software Release and Deployment Plan | Software-Release-and-Deployment-Plan.md | `docs/` |
| DOC-TDC-DEPLOYMAN-001 | Software Deployment Manual | Software-Deployment-Manual.md | `docs/` |
| DOC-TDC-RELEASENOTES-001 | Release Notes | Release-Notes.md | `docs/` |
| DOC-TDC-DEPLOYREC-001 | Deployment Records | Deployment-Records.md | `docs/` |
| DOC-TDC-DEPLOYVER-001 | Deployment Verification Report | Deployment-Verification-Report.md | `docs/` |

### Phase 10 — Maintenance

| CI ID | Document Name | Filename | Path |
|-------|---------------|----------|------|
| DOC-TDC-MAINTPLAN-001 | Software Maintenance Plan | Software-Maintenance-Plan.md | `docs/` |
| DOC-TDC-CHANGEREC-* | Software Change Records | Software-Change-Records.md | `docs/` |
| DOC-TDC-MAINTREC-* | Software Maintenance Records | Software-Maintenance-Records.md | `docs/` |
| DOC-TDC-MAINTVER-* | Software Maintenance Verification Report | Software-Maintenance-Verification-Report.md | `docs/` |

---

## Appendix B: Change Request Template

```markdown
# Change Request

## CR Header

| Field | Value |
|-------|-------|
| **CR ID** | CR-TDC-YYYYMMDD-NNN |
| **Submitted By** | [Name] ([Role]) |
| **Date Submitted** | YYYY-MM-DD |
| **Related PR** | PR-TDC-YYYYMMDD-NNN (if applicable) |
| **Type** | Defect / Enhancement / Requirement Change / Process Change |
| **Priority** | Critical / High / Medium / Low |
| **Status** | Submitted / Under Review / Approved / Rejected / Deferred / Implemented / Closed |

---

## 1. Description (§6.6.4.1(b))

[Detailed description of the proposed change]

---

## 2. Rationale (§6.6.4.1(b))

[Explain why this change is needed — what problem does it solve?]

---

## 3. Affected Configuration Items (§6.6.4.1(f))

List all documents, source files, test files, and other CIs affected by this change:

| CI ID | CI Name | Type | Current Version | Change Type |
|-------|---------|------|-----------------|-------------|
| | | | | Add / Modify / Delete |
| | | | | Add / Modify / Delete |

---

## 4. Impact Analysis (§6.6.4.1(c))

### 4.1 Technical Impact

[Describe the technical impact — what code, design, or requirements will change?]

### 4.2 Safety Impact

[SAF assessment — does this change affect safety functions or safety requirements?]

### 4.3 Quality Impact

[QUA assessment — does this change affect quality standards or processes?]

### 4.4 Verification Impact

[VER assessment — what verification activities must be repeated?]

### 4.5 Schedule Impact

[PM assessment — how does this affect the project schedule?]

### 4.6 Resource Impact

[PM assessment — what resources (people, tools, budget) are needed?]

---

## 5. Traceability Impact (§6.6.4.1(i))

[How does this change affect traceability matrices (RTM, etc.)?]

---

## 6. Phase Re-entry (§6.6.4.2)

| Re-entry Phase | Rationale |
|----------------|-----------|
| Phase X — [Phase Name] | [Explain why this phase must be re-entered] |

**COD Decision**: [COD confirms or overrides re-entry phase]

---

## 7. CCB Decision (§6.6.4.1(d))

| Decision | Date | Notes |
|----------|------|-------|
| ☐ APPROVE ☐ REJECT ☐ DEFER | YYYY-MM-DD | |

**Signatures**:

| Role | Name | Signature | Date |
|------|------|-----------|------|
| PM (CCB Chair) | | | |
| COD (Lifecycle Authority) | | | |
| Safety Manager | | | |

---

## 8. Implementation Plan (§6.6.4.1(g))

| Task | Assigned To | Estimated Effort | Target Date |
|------|-------------|------------------|-------------|
| | | | |
| | | | |

---

## 9. Verification Plan (§6.6.4.1(g))

[Describe how the change will be verified — what VER activities are required?]

---

## 10. Test Plan (§6.6.4.1(g))

[Describe what tests must be run — unit tests, integration tests, regression tests?]

---

## 11. Document Updates (§6.6.4.1(e))

List all documents that must be updated:

| Document ID | Document Name | Section to Update |
|-------------|---------------|-------------------|
| | | |

---

## 12. Notification List (§6.6.4.1(h))

List all parties who must be informed of CR closure:

| Name | Role | Notification Method |
|------|------|---------------------|
| | | Email / Meeting / Report |

---

## 13. Implementation Status

| Date | Milestone | Status |
|------|-----------|--------|
| | Change implemented | |
| | Verification complete | |
| | Tests passed | |
| | Documents updated | |
| | Baseline updated | |
| | Notifications sent | |
| | CR closed | |

---

**CM Notes**:
[CM records any additional notes, issues, or lessons learned]
```

---

## Appendix C: Baseline Manifest Template

Each baseline SHALL include a YAML manifest file stored in `baselines/<baseline-name>/manifest.yaml`.

```yaml
# Baseline Manifest
# EN 50128:2011 §9.1.4.2–3 — Configuration Management

baseline:
  id: TDC-BL-PHASE1-v1.0
  name: "Planning Baseline"
  phase: 1
  phase_name: "Planning"
  date_created: 2026-03-30
  created_by: CM Team
  authorized_by: COD
  git_tag: TDC-BL-PHASE1-v1.0
  git_commit_sha: a1b2c3d4e5f6a1b2c3d4e5f6a1b2c3d4e5f6a1b2

project:
  name: TDC (Train Door Control)
  sil_level: 3
  standard: EN 50128:2011

tools:
  - name: Git
    version: 2.30.0
    purpose: Version control
  - name: GNU Make
    version: 4.0
    purpose: Build automation
  - name: GCC
    version: 9.0
    purpose: C compiler
  - name: GNU ld
    version: 2.30
    purpose: Linker
  - name: Cppcheck
    version: 2.0
    purpose: MISRA C:2012 checker
  - name: gcov
    version: 9.0
    purpose: Code coverage
  - name: lcov
    version: 1.14
    purpose: Coverage report generator
  - name: Unity
    version: 2.5.0
    purpose: Unit test framework
  - name: Lizard
    version: 1.17.0
    purpose: Cyclomatic complexity analyzer

documents:
  - ci_id: DOC-TDC-SQAP-001
    name: Software Quality Assurance Plan
    version: 1.0
    git_commit_sha: a1b2c3d4e5f6a1b2c3d4e5f6a1b2c3d4e5f6a1b2
    path: docs/Software-Quality-Assurance-Plan.md
    signed_by: QUA Team
    signed_date: 2026-03-30
    
  - ci_id: DOC-TDC-SCMP-001
    name: Software Configuration Management Plan
    version: 1.0
    git_commit_sha: a1b2c3d4e5f6a1b2c3d4e5f6a1b2c3d4e5f6a1b2
    path: docs/Software-Configuration-Management-Plan.md
    signed_by: CM Team
    signed_date: 2026-03-30
    
  - ci_id: DOC-TDC-SVP-001
    name: Software Verification Plan
    version: 1.0
    git_commit_sha: a1b2c3d4e5f6a1b2c3d4e5f6a1b2c3d4e5f6a1b2
    path: docs/Software-Verification-Plan.md
    signed_by: VER Team
    signed_date: 2026-03-30
    
  - ci_id: DOC-TDC-SVaP-001
    name: Software Validation Plan
    version: 1.0
    git_commit_sha: a1b2c3d4e5f6a1b2c3d4e5f6a1b2c3d4e5f6a1b2
    path: docs/Software-Validation-Plan.md
    signed_by: VAL Team
    signed_date: 2026-03-30

verification_reports:
  - ci_id: DOC-TDC-SQAVR-001
    name: Software Quality Assurance Verification Report
    version: 1.0
    git_commit_sha: a1b2c3d4e5f6a1b2c3d4e5f6a1b2c3d4e5f6a1b2
    path: docs/reports/Software-Quality-Assurance-Verification-Report.md
    signed_by: VER Team
    signed_date: 2026-03-30
    vmgr_approved_by: VMGR Team
    vmgr_approved_date: 2026-03-30

evidence_artifacts:
  # No evidence artifacts in Phase 1

source_code:
  # No source code in Phase 1

test_code:
  # No test code in Phase 1

build_configuration:
  # No build configuration in Phase 1

gate_approval:
  cod_approval: true
  cod_approved_by: COD Team
  cod_approved_date: 2026-03-30
  gate_check_result: PASS

notes: |
  Planning baseline includes all four planning documents (SQAP, SCMP, SVP, SVaP)
  and the SQAVR verification report. No source code or evidence artifacts
  are present at this phase.
```

---

**END OF DOCUMENT**
