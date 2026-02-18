# Software Configuration Management Plan

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SCMP-2026-001 |
| **Version** | 2.0 |
| **Date** | 2026-02-18 |
| **Project** | train_door_control2 |
| **SIL Level** | 3 |
| **Author** | Configuration Manager |
| **Reviewer** | QA Manager |
| **Approver** | Project Manager |
| **Status** | Draft |

---

## Document Control

| Version | Date | Author | Changes | Approval Status |
|---------|------|--------|---------|-----------------|
| 0.1 | 2026-02-18 | Configuration Manager | Initial draft | Draft |
| 1.0 | 2026-02-18 | Configuration Manager | First approved version | Approved |
| 2.0 | 2026-02-18 | Configuration Manager | Major revision: Added standard header, Document Control table, Approvals table, and enhanced template compliance per EN 50128 Section 6.6 | Draft |

---

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | Configuration Manager | | 2026-02-18 |
| **Configuration Manager** | Configuration Manager | | |
| **QA Manager** | QA Manager | | |
| **Project Manager** | Project Manager | | |
| **Independent Assessor** (SIL 3) | | | |

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [Configuration Management Organization](#2-configuration-management-organization)
3. [Configuration Identification](#3-configuration-identification)
4. [Configuration Control](#4-configuration-control)
5. [Configuration Status Accounting](#5-configuration-status-accounting)
6. [Configuration Audits and Reviews](#6-configuration-audits-and-reviews)
7. [Tools and Infrastructure](#7-tools-and-infrastructure)
8. [Interface Control and Third-Party Management](#8-interface-control-and-third-party-management)
9. [Build and Release Management](#9-build-and-release-management)
10. [Traceability Management](#10-traceability-management)
11. [Data Recording and Analysis](#11-data-recording-and-analysis)
12. [Training Requirements](#12-training-requirements)
13. [Compliance Matrix](#13-compliance-matrix)
14. [References](#14-references)

---

## 1. Introduction

### 1.1 Purpose

This Software Configuration Management Plan (SCMP) establishes the configuration management processes, procedures, and responsibilities for the train_door_control2 software development. It ensures that all software configuration items are identified, controlled, tracked, and audited throughout the software lifecycle in accordance with EN 50128:2011 Section 6.6.

### 1.2 Scope

This SCMP applies to:
- All software configuration items (source code, documentation, tools, test artifacts)
- All phases of the software lifecycle (requirements through deployment)
- All project personnel involved in creating, modifying, or using software artifacts
- SIL 3 safety integrity level

**Configuration Management Coverage:**
- Source code files (`.c`, `.h`)
- Build scripts (`Makefile`, build scripts)
- Documentation (SRS, SAS, SDS, test plans, reports)
- Test artifacts (test cases, test data, test results)
- Tools and compilers (with version numbers)
- Libraries and dependencies

### 1.3 SIL Classification

**Target SIL Level**: 3

**EN 50128 Requirement**: Configuration Management is **MANDATORY for ALL SIL levels** (Table A.9, Technique 1)

**SIL 3 Implications**:
- Version control, change control, configuration identification, configuration audits REQUIRED
- Enhanced traceability (**MANDATORY** per Table A.9)
- Formal Change Control Board
- Independent audits
- Data recording and analysis **MANDATORY** (Table A.9, Technique 7)

### 1.4 Definitions and Abbreviations

| Term | Definition |
|------|------------|
| **CI** | Configuration Item - Any software artifact under configuration management |
| **Baseline** | Approved version of a configuration item that can only be changed through formal change control |
| **CCB** | Change Control Board - Authority for approving changes to baselines |
| **SCM** | Software Configuration Management |
| **SCMP** | Software Configuration Management Plan |
| **PCA** | Physical Configuration Audit |
| **FCA** | Functional Configuration Audit |
| **CR** | Change Request |
| **SIL** | Safety Integrity Level (0-4) |
| **RTM** | Requirements Traceability Matrix |
| **VCS** | Version Control System (Git) |

### 1.5 Applicable Standards

- EN 50128:2011 Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems (Section 6.6)
- EN 50126-1:2017 Railway Applications - The Specification and Demonstration of Reliability, Availability, Maintainability and Safety (RAMS)
- MISRA C:2012 Guidelines for the use of the C language in critical systems
- IEC 61508:2010 Functional safety of electrical/electronic/programmable electronic safety-related systems

### 1.6 References

| Reference | Document |
|-----------|----------|
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 |
| **[SVaP]** | Software Validation Plan, DOC-SVAP-2026-001 |
| **[LIFECYCLE]** | LIFECYCLE.md - EN 50128 V-Model lifecycle definition |

---

## 2. Configuration Management Organization

### 2.1 Roles and Responsibilities

#### 2.1.1 Configuration Manager (CM)

**Responsibilities**:
- Develop and maintain the SCMP (this document)
- Establish and maintain version control repository
- Identify and track all configuration items
- Manage configuration baselines
- Administer Change Control Board (CCB) meetings
- Perform configuration audits (PCA, FCA)
- Generate configuration status reports
- Maintain Requirements Traceability Matrix (MANDATORY for SIL 3)
- Coordinate change control processes
- Maintain configuration status accounting

**Independence**: Configuration Manager SHALL be independent of development team (SIL 3 requirement)

#### 2.1.2 Change Control Board (CCB)

**Members**:
- Project Manager (Chair)
- Configuration Manager (Secretary)
- Safety Engineer
- Technical Lead
- QA Manager (SIL 3 requirement)

**Responsibilities**:
- Review and approve/reject change requests
- Assess change impact on SIL, safety, schedule, cost
- Evaluate change requests for safety impact, technical feasibility, and schedule impact
- Authorize baseline modifications
- Resolve configuration conflicts
- Meet weekly or as needed for urgent changes

**Meeting Frequency**: Weekly (or as needed for urgent changes)

**Approval Authority**: All changes require CCB approval for SIL 3

#### 2.1.3 Project Manager

**Responsibilities**:
- Approve baseline releases
- Allocate resources for CM activities
- Review configuration status reports

#### 2.1.4 Development Team

**Responsibilities**:
- Follow version control procedures
- Submit change requests through the CM process
- Implement approved changes
- Provide information for impact analysis
- Update traceability information
- Participate in configuration audits
- Maintain branch hygiene

### 2.2 Independence Requirements

**SIL 3 (MANDATORY)**:
- Configuration Manager SHALL be independent of development team
- CCB SHALL include independent QA representation
- Configuration audits SHOULD be performed by independent auditor

### 2.3 CM Tools and Environment

| Tool | Purpose | SIL Requirement |
|------|---------|-----------------|
| **Git** | Version control with GitHub | All SILs |
| **Make** | Build automation | All SILs |
| **Jenkins CI/CD** | Continuous integration | Recommended |
| **Excel/CSV** | CM database for CI tracking and RTM | All SILs |
| **GitHub Issues** | Issue tracking | All SILs |
| **Markdown** | Documentation | All SILs |

---

## 3. Configuration Identification

### 3.1 Configuration Items (CIs)

All software artifacts SHALL be identified as Configuration Items and placed under version control.

#### 3.1.1 Document CIs

| CI Type | Naming Convention | Location | Baseline Trigger |
|---------|-------------------|----------|------------------|
| Requirements (SRS) | `DOC-SRS-YYYY-NNN.md` | `docs/requirements/` | Phase 2 gate approval |
| Architecture (SAS) | `DOC-SAS-YYYY-NNN.md` | `docs/design/` | Phase 3 gate approval |
| Design (SDS) | `DOC-SDS-YYYY-NNN.md` | `docs/design/` | Phase 3 gate approval |
| Plans (SQAP, SCMP, SVP, SVaP) | `DOC-{TYPE}-YYYY-NNN.md` | `docs/plans/` | Phase 1 gate approval |
| Test Specifications | `DOC-TST-{LEVEL}-YYYY-NNN.md` | `docs/tests/` | Before test execution |
| Test Reports | `RPT-TST-{LEVEL}-YYYY-NNN.md` | `docs/reports/` | After test execution |
| Verification Reports | `RPT-VER-{TYPE}-YYYY-NNN.md` | `docs/reports/` | Phase completion |
| Validation Reports | `RPT-VAL-YYYY-NNN.md` | `docs/reports/` | Phase 6 completion |

#### 3.1.2 Source Code CIs

| CI Type | Naming Convention | Location | Baseline Trigger |
|---------|-------------------|----------|------------------|
| C Header Files | `module_name.h` | `src/` | Phase 4 gate approval |
| C Source Files | `module_name.c` | `src/` | Phase 4 gate approval |
| Unit Test Files | `test_module_name.c` | `tests/unit/` | Phase 4 gate approval |
| Integration Test Files | `test_integration_*.c` | `tests/integration/` | Phase 5 gate approval |
| System Test Files | `test_system_*.c` | `tests/system/` | Phase 6 gate approval |

#### 3.1.3 Build and Tool CIs

| CI Type | Naming Convention | Location | Baseline Trigger |
|---------|-------------------|----------|------------------|
| Makefiles | `Makefile` | `build/` | Phase 4 |
| Build Scripts | `build_*.sh` | `scripts/` | Phase 4 |
| Static Analysis Configs | `*.cfg`, `*.ini` | `tools/config/` | Phase 1 |

#### 3.1.4 Traceability CIs (Mandatory SIL 3)

| CI Type | Naming Convention | Location | Baseline Trigger |
|---------|-------------------|----------|------------------|
| Requirements Traceability Matrix | `RTM.md` | `docs/traceability/` | Every phase gate |
| Hazard Log | `HAZARD_LOG.md` | `docs/safety/` | Continuous |

### 3.2 Naming Conventions

All CIs follow the format: `CI-<TYPE>-<YEAR>-<SEQ>`
- **TYPE:** SRC (source), DOC (document), TEST (test), BUILD (build script)
- **YEAR:** Current year (e.g., 2026)
- **SEQ:** Sequential number (001, 002, etc.)

**Examples:**
- CI-SRC-2026-001: main.c
- CI-DOC-2026-001: SRS.md
- CI-TEST-2026-001: test_main.c

### 3.3 Version Numbering Scheme

**Format**: `MAJOR.MINOR.PATCH` (Semantic Versioning)

- **MAJOR**: Incremented for baseline releases (e.g., 1.0, 2.0) - Incompatible changes
- **MINOR**: Incremented for approved changes within baseline (e.g., 1.1, 1.2) - Backward-compatible new features
- **PATCH**: Incremented for minor corrections (e.g., 1.0.1, 1.0.2) - Backward-compatible bug fixes

**Special Versions**:
- `0.x`: Draft versions (not yet approved)
- `1.0`: First approved baseline
- `2.0+`: Major baseline revisions

**Examples**:
- `SRS-0.1` - Initial draft
- `SRS-1.0` - First approved baseline
- `SRS-1.1` - Approved change to baseline
- `SRS-2.0` - Major baseline revision

### 3.4 Baseline Identification

Baselines follow: `baseline_SIL3_vX.Y.Z`
- Released on: 2026-02-18
- Next planned: baseline_SIL3_v1.1.0 (2026-04-01)

**Baseline Types:**

| Baseline Type | Trigger | CIs Included | CCB Approval Required |
|---------------|---------|--------------|----------------------|
| **Planning Baseline** | Phase 1 gate approval | SQAP, SCMP, SVP, SVaP | Yes |
| **Requirements Baseline** | Phase 2 gate approval | SRS, RTM, Hazard Log | Yes |
| **Design Baseline** | Phase 3 gate approval | SAS, SDS, Interface Specs | Yes |
| **Implementation Baseline** | Phase 4 gate approval | Source code, Unit tests | Yes |
| **Integration Baseline** | Phase 5 gate approval | Integration tests, reports | Yes |
| **Validation Baseline** | Phase 6 gate approval | System tests, validation report | Yes |
| **Release Baseline** | Deployment approval | All CIs (complete software package) | Yes |

### 3.5 Branch Strategy

**Repository**: Git with GitHub

**Branch Structure**:
```
main (protected)
  ├── develop (integration branch)
  │   ├── feature/REQ-001-door-control
  │   ├── feature/REQ-002-emergency-stop
  │   ├── bugfix/BUG-123-sensor-timeout
  │   └── hotfix/CRIT-456-safety-fault
  ├── release/v1.0 (baseline branch)
  └── release/v2.0 (baseline branch)
```

**Branch Types**:
- **`main`**: Production releases only - Production-ready code, tagged baselines only
- **`develop`**: Integration branch for ongoing development
- **`feature/*`**: Feature development - New feature development (from `develop`)
- **`release/*`**: Release preparation - Baseline preparation and maintenance (from `develop`)
- **`hotfix/*`**: Emergency fixes for production (from `main`)

**Branch Protection**:
- **`main`**: Require pull request reviews (≥2 reviewers for SIL 3)
- **`main`**: Require status checks to pass (build, tests, MISRA C)
- **`main`**: Require CCB approval for merges
- **`release/*`**: Require pull request reviews, CCB approval

### 3.6 Tagging Strategy

**Format**: `v<MAJOR>.<MINOR>.<PATCH>[-<METADATA>]`

**Tag Types**:
- **Baseline tags**: `v1.0.0`, `v2.0.0` (on `main` branch)
- **Release candidate tags**: `v1.0.0-rc1`, `v1.0.0-rc2` (on `release/*` branches)
- **Phase gate tags**: `phase2-gate`, `phase3-gate`, etc.

**Required Tags** (all baselines):
- Git annotated tag with message
- Tag message SHALL include: date, author, CCB approval reference, SIL level, phase

**Example**:
```bash
git tag -a v1.0.0 -m "Baseline v1.0.0 - SIL 3 - Phase 4 Gate - CCB-2026-02-18"
```

### 3.7 Document Control Procedures

All documents are stored in the repository under `docs/` with version control. Changes require CR approval and update the document header with version and date.

---

## 4. Configuration Control

### 4.1 Change Request Process

**All changes to baselined Configuration Items SHALL follow this process:**

```
1. Change Request Submission
   ↓
2. Change Impact Analysis (CM performs)
   ↓
3. CCB Review and Decision
   ↓
4. Implementation (if approved)
   ↓
5. Verification of Change
   ↓
6. Update Baseline and Traceability
   ↓
7. Configuration Status Accounting
```

#### 4.1.1 Change Request Submission

**Who**: Any project member, Developer, customer, or stakeholder

**Process**:
1. Developer submits CR with description, impact analysis, and affected CIs
2. Create Change Request (CR) document using template (Appendix A)
3. Assign unique CR ID: `CR-YYYY-NNN`
4. Submit to Configuration Manager
5. CM logs CR in Change Request Register

**Required Information**:
- CR ID
- Submitter name and date
- Affected CIs (by ID)
- Reason for change
- Proposed solution (if known)
- Priority (Critical / High / Medium / Low)
- SIL impact assessment

#### 4.1.2 Change Impact Analysis

**Who**: Configuration Manager (with input from technical leads) performs initial review

**Process**:
1. Configuration Manager performs initial review
2. Designer and Safety Engineer assess technical and safety impact
3. Identify all affected CIs (requirements, design, code, tests)
4. Assess impact on:
   - SIL level (does it increase safety risk?)
   - Requirements traceability
   - Verification and validation
   - Schedule and cost
   - Existing baselines
5. Document analysis in CR
6. Schedule CCB review

**Mandatory for SIL 3**: Impact on safety requirements, hazard log, traceability matrix

#### 4.1.3 CCB Review and Decision

**When**: Regular CCB meetings (Weekly meetings, or emergency session for critical changes)

**Process**:
1. CM presents change request and impact analysis
2. CCB evaluates and approves/rejects
3. CCB discusses technical, safety, schedule implications
4. CCB votes: **Approve** / **Reject** / **Defer** (pending more info)
5. CM records decision in CCB minutes
6. CM notifies submitter and affected parties

**Approval Criteria**:
- Technical feasibility
- No adverse safety impact (or justified)
- Traceability maintained
- Verification plan updated
- Resources available

#### 4.1.4 Implementation

**Who**: Developer, Assigned developer(s)

**Process**:
1. Developer implements change
2. Create feature/bugfix branch from `develop`
3. Implement changes following coding standards (MISRA C:2012)
4. Update affected CIs (code, docs, tests, traceability)
5. Commit with reference to CR ID in commit message
6. Create pull request for review

**Commit Message Format**:
```
[CR-YYYY-NNN] Brief description of change

- Detailed explanation
- Affected modules: module_name.c, module_name.h
- Traceability: REQ-FUNC-001 → MOD-001 → test_module.c
- SIL impact: None / Minor / Requires re-verification
```

#### 4.1.5 Verification of Change

**Who**: Tester and Verifier (independent for SIL 3), QA Manager

**Process**:
1. Verifier confirms requirements met
2. Review pull request for code quality, MISRA C compliance
3. Run static analysis (PC-lint, Cppcheck)
4. Execute affected tests (unit, integration, system)
5. Verify coverage requirements met (per SIL level)
6. Update verification evidence
7. Approve pull request if all checks pass

**Mandatory Checks**:
- MISRA C compliance (SIL 3)
- Complexity within limits (≤10 for SIL 3)
- Traceability updated (RTM, hazard log)
- Test coverage maintained (100% statement/branch/condition for SIL 3)

#### 4.1.6 Update Baseline and Traceability

**Who**: Configuration Manager

**Process**:
1. Merge approved pull request to `develop`
2. Configuration Manager updates baseline and closes CR
3. Update Configuration Status Accounting log
4. Update Requirements Traceability Matrix (MANDATORY for SIL 3)
5. Tag baseline if change triggers new release
6. Archive old baseline version

#### 4.1.7 Configuration Status Accounting

**Who**: Configuration Manager

**Process**:
1. Record change in Configuration Status Report
2. Update CI status in version control
3. Notify stakeholders of baseline change
4. Update project documentation index

### 4.2 Change Control Board (CCB)

**Membership**: Project Manager (Chair), Configuration Manager, Safety Engineer, Technical Lead, QA Manager

**Frequency**: Weekly meetings, emergency meetings as needed

**Approval Authority**: All changes require CCB approval for SIL 3

### 4.3 Baseline Management

**Baseline Definition**: An approved version of a configuration item that can only be changed through formal change control.

#### 4.3.1 Baseline Creation Process

1. **Trigger**: Phase gate approval by Lifecycle Coordinator (`/cod gate-check <phase>`)
2. **CM Action**: 
   - Freeze CIs (no further changes without CR)
   - Create baseline branch (e.g., `release/v1.0`)
   - Tag baseline with version number
   - Archive baseline in secure location
   - Update Configuration Status Accounting
3. **CCB Action**: Formal baseline approval meeting
4. **CM Action**: Publish baseline notification to stakeholders

#### 4.3.2 Baseline Modification

**Process**: All baseline modifications SHALL go through Change Control (Section 4.1)

**SIL 3 Additional Requirements**:
- Independent impact analysis required
- Safety assessment for safety-critical CIs
- Re-verification evidence required
- Traceability matrix update mandatory

---

## 5. Configuration Status Accounting

### 5.1 CI Status Tracking

CI status states: Draft, Review, Approved, Released, Obsolete

**Tool**: Excel/CSV files in `docs/cm/`

**Retention**: Project lifecycle + 10 years

### 5.2 Status Reporting

**Frequency**: 
- **SIL 3**: Bi-weekly (mandatory per Table A.9, Technique 7 - Data Recording and Analysis)

**Report Contents**:
- List of all CIs with current version
- Baseline status (established, modified, released)
- Pending change requests
- Recently approved changes
- Build status
- Defect summary
- Traceability status (SIL 3 - MANDATORY)

**Distribution**: Project Manager, QA Manager, Lifecycle Coordinator, CCB members

**Reporting Schedule**:
- **Monthly**: Configuration status report
- **Quarterly**: Metrics report (mandatory SIL 3)

### 5.3 Configuration Database

**Tool**: Excel/CSV files in `docs/cm/`

**Retention**: Project lifecycle + 10 years

### 5.4 Change History Tracking

All changes recorded in Git commit history and CR database.

---

## 6. Configuration Audits and Reviews

### 6.1 Physical Configuration Audit (PCA)

**Purpose**: Verify that physical software artifacts match the documented configuration.

**Frequency**: Before each baseline release

**Scope**:
- Source code files present and match version control
- Documentation versions match CI register
- Build artifacts reproducible from source
- Test artifacts complete

**Auditor**: Configuration Manager or Independent Auditor (SIL 3)

**Deliverable**: PCA Report

**Checklist**: See Appendix B

### 6.2 Functional Configuration Audit (FCA)

**Purpose**: Verify that software functionality matches requirements and design specifications.

**When**: After validation testing, before each baseline release

**Scope**:
- Requirements traceability complete
- All tests passed
- Verification evidence complete
- Validation evidence complete
- Safety requirements verified (if applicable)

**Auditor**: QA Manager or Independent Auditor (SIL 3)

**Deliverable**: FCA Report

**Checklist**: See Appendix C

### 6.3 Periodic Reviews

- CM process review: Quarterly
- Tool audits: Annually

### 6.4 Audit Process

1. **Schedule Audit**: CM schedules audit with 2-week notice
2. **Prepare Audit Checklist**: CM prepares checklist based on audit scope
3. **Conduct Audit**: Auditor reviews CIs, documentation, evidence
4. **Record Findings**: Auditor documents conformances and non-conformances
5. **Corrective Actions**: Project team addresses non-conformances
6. **Close Audit**: Auditor verifies corrective actions, issues audit report
7. **CCB Review**: CCB reviews audit report, approves baseline if clean

### 6.5 Audit Reporting

Reports to Project Manager and Quality Assurance.

---

## 7. Tools and Infrastructure

### 7.1 Version Control System

**Tool**: Git

**Repository Location**: GitHub

**Access Control**:
- Read access: All project members
- Write access: Developers (with pull request workflow)
- Admin access: Configuration Manager, Project Manager

**Backup**: Daily automated backup

### 7.2 Configuration Management Tools

| Tool | Purpose | SIL Requirement |
|------|---------|-----------------|
| **Git** | Version control | All SILs |
| **Make** | Build automation | All SILs |
| **PC-lint Plus** | MISRA C checking | SIL 2+ (MANDATORY SIL 3) |
| **Cppcheck** | Static analysis | SIL 2+ (HR SIL 3) |
| **gcov / lcov** | Coverage analysis | SIL 2+ (MANDATORY SIL 3) |
| **Markdown** | Document authoring | All SILs |

### 7.3 Tool Qualification (SIL 3)

**EN 50128 Requirement**: Tools used for automated verification SHALL be qualified (Section 6.7)

**Tools Requiring Qualification**:
- Compiler (GCC) - T3 tool (requires qualification)
- Static analyzers (PC-lint, Cppcheck) - T2 tool (validation required)
- Test harness (Unity) - T1 tool (low risk)

**Qualification Evidence**: To be stored in `docs/tool-qualification/`

---

## 8. Interface Control and Third-Party Management

### 8.1 Interface Identification

**Software interfaces**:
- Door control API

**Hardware interfaces**:
- Sensor inputs
- Actuator outputs

**External systems**:
- Train control system

### 8.2 Interface Change Control

All interface changes require CCB approval and impact analysis.

### 8.3 Third-Party Component Management

**Vendor**: None (all custom development for SIL 3)

**Licenses**: MIT for any open-source components (if used)

---

## 9. Build and Release Management

### 9.1 Build Procedures

**Continuous Integration**:
- Automated build using Make
- Build artifacts: executable, library, documentation
- Build logs archived

**Build Verification**: 
- Unit tests pass
- No compilation errors
- All unit tests pass
- MISRA C compliance check (SIL 3)
- Static analysis clean (no critical/high issues)
- Complexity analysis within limits

**Tools**:
- Make / CMake
- GCC with MISRA C flags
- PC-lint Plus (MISRA C checker)
- Cppcheck (static analyzer)

### 9.2 Release Criteria

- All tests passed (100% statement/branch/condition coverage for SIL 3)
- PCA and FCA passed
- Documentation approved
- Traceability verified (100% for SIL 3)

### 9.3 Release Process

1. **Release Candidate Creation**:
   - Branch from `develop` to `release/vX.Y`
   - Tag release candidate: `vX.Y.0-rc1`
   - Perform integration testing
   - Fix critical issues only

2. **Release Approval**:
   - Complete verification (VER)
   - Complete validation (VAL)
   - CCB approval
   - Lifecycle Coordinator gate check pass

3. **Release Baseline**:
   - Merge `release/vX.Y` to `main`
   - Tag final release: `vX.Y.0`
   - Create release notes
   - Archive release package

**Release Package Contents**:
- Source code (all CIs)
- Compiled binaries
- All documentation (plans, specs, reports)
- Traceability matrix
- Test evidence (reports, coverage)
- Verification and validation reports
- Configuration status report
- Build instructions
- Deployment instructions

### 9.4 Deployment Configuration

**Target**: Embedded railway controller

**Installation**: Via secure update mechanism

### 9.5 Rollback Procedures

Rollback to previous baseline within 30 minutes.

---

## 10. Traceability Management (MANDATORY SIL 3)

### 10.1 Traceability Requirements

**SIL 3**: Traceability MANDATORY (100% bidirectional)

**Traceability Links** (mandatory):
```
System Requirement → Software Requirement → Architecture → Design → Code → Test Case → Test Result
```

**Requirements to**:
- Requirements to design: 100%
- Design to code: 100%
- Code to tests: 100%
- Bi-directional verified

### 10.2 Traceability Matrix Maintenance

**Format**: `docs/traceability/RTM.md`

**Tool**: CSV file `docs/traceability/rtm.csv`

**Update Trigger**: Each CR closure, Every CI modification

**Verification**: Before baseline release, Independent verification required (SIL 3)

**Example RTM Entry**:
| System Req | SW Req | Architecture | Design | Code | Unit Test | Integration Test | Validation Test | Status |
|------------|--------|--------------|--------|------|-----------|------------------|-----------------|--------|
| SYS-001 | REQ-FUNC-001 | SAS-MOD-001 | SDS-MOD-001 | brake.c:45 | TC-UNIT-001 | TC-INT-001 | TC-VAL-001 | Verified |

---

## 11. Data Recording and Analysis (MANDATORY SIL 3)

### 11.1 EN 50128 Requirement

**EN 50128 Requirement**: Table A.9, Technique 7 - **MANDATORY for SIL 3**

### 11.2 Metrics Collection

**Recorded Data**:
- Change request metrics (count, type, priority, resolution time)
- Defect metrics (count, severity, phase detected, root cause)
- Build metrics (build success rate, build time)
- Audit metrics
- Baseline metrics
- Test metrics (pass rate, coverage, defect density)
- Review metrics (review findings, review effort)

### 11.3 Analysis and Reporting

**Analysis Frequency**: Monthly (minimum), Quarterly trend analysis

**Reports To**: Project Manager, QA Manager, Lifecycle Coordinator

**Tool**: GitHub Issues for defect tracking, Excel/CSV for metrics

---

## 12. Training Requirements

### 12.1 CM Tool Training

All project personnel SHALL receive training on:
- Git version control
- Build automation
- Issue tracking
- Branch strategy and pull request process
- Change control process
- MISRA C coding standards (developers)
- Configuration audit procedures (auditors)

### 12.2 Process Training

- Change request process
- Audit procedures
- Baseline management

### 12.3 Role-Specific Training

**Configuration Manager**:
- EN 50128 CM requirements
- Experience with version control systems
- Knowledge of EN 50128 configuration management requirements
- Understanding of software development lifecycle

**CCB Members**:
- Change evaluation
- Understanding of change impact analysis
- Knowledge of project constraints (safety, schedule, cost)
- Authority to make change decisions

**Training Records**: Maintained by Configuration Manager

---

## 13. Compliance Matrix

### 13.1 EN 50128 Section 6.6 Compliance

| Requirement | Section | Evidence | Status |
|-------------|---------|----------|--------|
| **CM Plan established** | 6.6.2 | This document (SCMP) | ✓ |
| **Configuration identification** | 6.6.2.2 | Section 3 | ✓ |
| **Configuration control** | 6.6.2.3 | Section 4 | ✓ |
| **Configuration status accounting** | 6.6.2.4 | Section 5 | ✓ |
| **Configuration audits** | 6.6.2.5 | Section 6 | ✓ |
| **Version control** | 6.6.2.2 | Git repository | ✓ |
| **Change control** | 6.6.2.3 | CCB process (Section 4.1) | ✓ |
| **Traceability (SIL 3)** | Table A.9 | RTM (Section 10) | ✓ |
| **Data recording (SIL 3)** | Table A.9 | Metrics (Section 11) | ✓ |

### 13.2 EN 50128 Table A.9 Compliance (QA Techniques)

| # | Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Implementation |
|---|-----------|-------|---------|---------|----------------|
| **1** | Software Configuration Management | **M** | **M** | **M** | This document (SCMP) |
| **2** | Traceability | R | HR | **M** | Section 10 (RTM) |
| **7** | Data Recording and Analysis | HR | HR | **M** | Section 11 |

**M** = Mandatory, **HR** = Highly Recommended, **R** = Recommended

---

## 14. References

### 14.1 Normative References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[EN50126]** | EN 50126:2017 Railway applications - The specification and demonstration of Reliability, Availability, Maintainability and Safety (RAMS) |

### 14.2 Project References

| Reference | Document |
|-----------|----------|
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-2026-001 |
| **[SVP]** | Software Verification Plan, DOC-SVP-2026-001 |
| **[SVaP]** | Software Validation Plan, DOC-SVAP-2026-001 |
| **[LIFECYCLE]** | LIFECYCLE.md - EN 50128 V-Model lifecycle definition |

---

## Appendices

### Appendix A: Change Request Template

```markdown
# Change Request

**CR ID**: CR-YYYY-NNN  
**Date**: YYYY-MM-DD  
**Submitter**: [Name]  
**Priority**: [Critical / High / Medium / Low]

## 1. Affected CIs
- [List all affected configuration items]

## 2. Reason for Change
[Describe why this change is needed]

## 3. Proposed Solution
[Describe the proposed solution, if known]

## 4. Impact Assessment (CM to complete)
- **Requirements**: [Affected requirements]
- **Design**: [Affected design elements]
- **Code**: [Affected modules]
- **Tests**: [Affected tests]
- **SIL Impact**: [None / Minor / Major]
- **Traceability Impact**: [RTM updates required]
- **Effort Estimate**: [Hours/days]

## 5. CCB Decision
- **Date**: YYYY-MM-DD
- **Decision**: [Approved / Rejected / Deferred]
- **Rationale**: [CCB reasoning]
- **Assigned To**: [Developer name]

## 6. Implementation
- **Branch**: [feature/CR-YYYY-NNN]
- **Commits**: [List commit SHAs]
- **Pull Request**: [PR link]
- **Verification**: [Verification evidence]

## 7. Closure
- **Date**: YYYY-MM-DD
- **Closed By**: [CM name]
- **Baseline Updated**: [Yes / No]
```

### Appendix B: Physical Configuration Audit (PCA) Checklist

- [ ] All CIs listed in baseline manifest present
- [ ] CI version numbers match manifest
- [ ] File checksums match recorded values
- [ ] Build reproducible from baseline
- [ ] Source files have correct version headers
- [ ] Tool versions recorded
- [ ] No unauthorized files in baseline
- [ ] Archive and retrieval procedures tested
- [ ] All source code files under version control
- [ ] Version numbers match CI register
- [ ] Build reproducible from tagged source
- [ ] Documentation complete and versioned
- [ ] Test artifacts archived
- [ ] Traceability matrix up-to-date (SIL 3 - MANDATORY)

### Appendix C: Functional Configuration Audit (FCA) Checklist

- [ ] All requirements traced to design (100%)
- [ ] All design elements traced to code (100%)
- [ ] All code traced to tests (100%)
- [ ] All tests passed
- [ ] Coverage requirements met (Statement 100%, Branch 100%, Condition 100% for SIL 3)
- [ ] All defects resolved
- [ ] All documents approved
- [ ] MISRA C compliance verified (100% for SIL 3)
- [ ] Static analysis passed
- [ ] All requirements traced to tests
- [ ] All tests passed (evidence provided)
- [ ] Coverage requirements met (per Table A.21)
- [ ] MISRA C compliance verified (SIL 3)
- [ ] Complexity within limits (≤10 for SIL 3)
- [ ] Verification report complete
- [ ] Validation report complete
- [ ] Safety requirements verified (if applicable)

### Appendix D: Configuration Status Report Template

```markdown
# Configuration Status Report

**Report Period**: [Start Date] to [End Date]  
**Report Date**: YYYY-MM-DD  
**Prepared By**: Configuration Manager

## 1. Baseline Status
| Baseline | Version | Date Established | Status |
|----------|---------|------------------|--------|
| Planning | 1.0 | YYYY-MM-DD | Established |
| Requirements | 1.0 | YYYY-MM-DD | Modified (CR-2026-001) |

## 2. Change Requests
| CR ID | Submitter | Priority | Status | CCB Decision Date |
|-------|-----------|----------|--------|-------------------|
| CR-2026-001 | [Name] | High | Approved | YYYY-MM-DD |

## 3. Build Status
- **Latest Build**: #123
- **Build Date**: YYYY-MM-DD
- **Build Result**: Success / Failure
- **Test Results**: 156/156 passed

## 4. Metrics (SIL 3)
- **Open CRs**: 3
- **Closed CRs (this period)**: 7
- **Defects Found**: 12
- **Defects Fixed**: 10
- **Test Coverage**: 98% statement, 95% branch

## 5. Traceability Status (SIL 3)
- **Requirements traced**: 100% (45/45)
- **Design elements traced**: 100% (23/23)
- **Code traced**: 100% (15 modules)
- **Tests traced**: 98% (155/158)

## 6. Issues and Risks
[List any configuration management issues or risks]
```

### Appendix E: Baseline Manifest Template

```markdown
# Baseline Manifest

**Baseline**: baseline_SIL3_vX.Y.Z  
**Created**: [Date]  
**Baseline Status**: RELEASED  
**SIL Level**: 3  
**Configuration Manager**: [Name]

## Source Files
CI-SRC-2026-XXX [Name] [Version] [SHA256] [Status]

## Documentation
CI-DOC-2026-XXX [Name] [Version] [SHA256] [Status]

## Test Artifacts
CI-TEST-2026-XXX [Name] [Version] [SHA256] [Status]

## Traceability Status
Requirements to Design: 100% traced  
Design to Code: 100% traced  
Code to Tests: 100% traced

## Audits
PCA: PASSED [Date]  
FCA: PASSED [Date]
```

---

**END OF DOCUMENT**
