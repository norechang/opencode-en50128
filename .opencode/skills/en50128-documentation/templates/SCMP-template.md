# Software Configuration Management Plan (SCMP)

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 Section 6.6, Table A.9

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SCMP-YYYY-NNN |
| **Version** | 0.1 (Draft) → 1.0 (Approved) |
| **Date** | YYYY-MM-DD |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, 4] |
| **Author** | [Name], Configuration Manager |
| **Reviewer** | [Name], [Role] |
| **Approver** | [Name], Project Manager |
| **Status** | [Draft \| Review \| Approved \| Baseline] |

---

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | - |
| 1.0 | YYYY-MM-DD | [Name] | First approved version | [PM Name] |

---

## APPROVALS

**SIL 0-2 Requirements**: Author, Configuration Manager, Project Manager  
**SIL 3-4 Requirements**: Author, Configuration Manager, QA Manager, Project Manager, Independent Assessor

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | [CM Name] | | |
| **Configuration Manager** | [CM Name] | | |
| **QA Manager** | [QA Name] | | |
| **Project Manager** | [PM Name] | | |
| **Independent Assessor** (SIL 3-4) | [Assessor Name] | | |

---

## 1. INTRODUCTION

### 1.1 Purpose

[State the purpose of this Software Configuration Management Plan. Example:]

This Software Configuration Management Plan (SCMP) establishes the configuration management processes, procedures, and responsibilities for the [Project Name] software development. It ensures that all software configuration items are identified, controlled, tracked, and audited throughout the software lifecycle in accordance with EN 50128:2011 Section 6.6.

### 1.2 Scope

[Define the scope of configuration management. Example:]

This SCMP applies to:
- All software configuration items (source code, documentation, tools, test artifacts)
- All phases of the software lifecycle (requirements through deployment)
- All project personnel involved in creating, modifying, or using software artifacts
- All SIL levels [specify: 0, 1, 2, 3, 4]

### 1.3 SIL Classification

**Target SIL Level**: [0, 1, 2, 3, 4]

**EN 50128 Requirement**: Configuration Management is **MANDATORY for ALL SIL levels** (Table A.9, Technique 1)

**Implications**:
- **SIL 0-4**: Version control, change control, configuration identification, configuration audits REQUIRED
- **SIL 3-4**: Enhanced traceability (**MANDATORY** per Table A.9), formal change control board, independent audits
- **SIL 3-4**: Data recording and analysis **MANDATORY** (Table A.9, Technique 7)

### 1.4 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **CI** | Configuration Item - Any software artifact under configuration management |
| **Baseline** | Approved version of a configuration item that can only be changed through formal change control |
| **CCB** | Change Control Board - Authority for approving changes to baselines |
| **SCM** | Software Configuration Management |
| **RTM** | Requirements Traceability Matrix |
| **VCS** | Version Control System (e.g., Git) |

### 1.5 References

| Reference | Document |
|-----------|----------|
| [EN50128] | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| [SQAP] | Software Quality Assurance Plan, DOC-SQAP-YYYY-NNN |
| [SVP] | Software Verification Plan, DOC-SVP-YYYY-NNN |
| [LIFECYCLE] | LIFECYCLE.md - EN 50128 V-Model lifecycle definition |

### 1.6 Overview

[Provide a brief overview of the document structure.]

---

## 2. CONFIGURATION MANAGEMENT ORGANIZATION

### 2.1 Roles and Responsibilities

#### 2.1.1 Configuration Manager (CM)

**Responsibilities**:
- Maintain Software Configuration Management Plan (this document)
- Establish and maintain version control repository
- Manage configuration baselines
- Administer Change Control Board (CCB) meetings
- Perform configuration audits (PCA, FCA)
- Generate configuration status reports
- Maintain Requirements Traceability Matrix (mandatory SIL 3-4)

**Independence**: No independence requirement (all SIL levels)

#### 2.1.2 Change Control Board (CCB)

**Members**:
- Project Manager (Chair)
- Configuration Manager (Secretary)
- Software Manager
- QA Manager (SIL 2+)
- Safety Manager (if safety-critical)
- Customer Representative (optional)

**Responsibilities**:
- Review and approve/reject change requests
- Assess change impact on SIL, safety, schedule, cost
- Authorize baseline modifications
- Resolve configuration conflicts

**Meeting Frequency**: [Weekly / Bi-weekly / As needed]

#### 2.1.3 Developers (All Roles)

**Responsibilities**:
- Follow version control procedures
- Submit change requests for baseline modifications
- Update traceability information
- Participate in configuration audits
- Maintain branch hygiene

### 2.2 Independence Requirements

**SIL 0-2**: No independence requirements for CM function

**SIL 3-4**: 
- Configuration Manager SHALL be independent of development team
- CCB SHALL include independent QA representation
- Configuration audits SHOULD be performed by independent auditor

---

## 3. CONFIGURATION IDENTIFICATION

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
| Test Harness Scripts | `run_tests.py` | `tests/` | Phase 4 |

#### 3.1.4 Traceability CIs (Mandatory SIL 3-4)

| CI Type | Naming Convention | Location | Baseline Trigger |
|---------|-------------------|----------|------------------|
| Requirements Traceability Matrix | `RTM.md` | `docs/traceability/` | Every phase gate |
| Hazard Log | `HAZARD_LOG.md` | `docs/safety/` | Continuous |

### 3.2 Version Numbering Scheme

**Format**: `MAJOR.MINOR.PATCH` (Semantic Versioning)

- **MAJOR**: Incremented for baseline releases (e.g., 1.0, 2.0)
- **MINOR**: Incremented for approved changes within baseline (e.g., 1.1, 1.2)
- **PATCH**: Incremented for minor corrections (e.g., 1.0.1, 1.0.2)

**Special Versions**:
- `0.x`: Draft versions (not yet approved)
- `1.0`: First approved baseline
- `2.0+`: Major baseline revisions

**Examples**:
- `SRS-0.1` - Initial draft
- `SRS-0.5` - Draft under review
- `SRS-1.0` - First approved baseline
- `SRS-1.1` - Approved change to baseline
- `SRS-2.0` - Major baseline revision

### 3.3 Branch Strategy

**Repository**: Git

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
- **`main`**: Production-ready code, tagged baselines only
- **`develop`**: Integration branch for ongoing development
- **`feature/*`**: New feature development (from `develop`)
- **`bugfix/*`**: Non-critical bug fixes (from `develop`)
- **`hotfix/*`**: Critical fixes for production (from `main`)
- **`release/*`**: Baseline preparation and maintenance (from `develop`)

**Branch Protection**:
- **`main`**: Require pull request reviews (≥2 reviewers SIL 3-4, ≥1 reviewer SIL 0-2)
- **`main`**: Require status checks to pass (build, tests, MISRA C)
- **`main`**: Require CCB approval for merges (all SIL levels)
- **`release/*`**: Require pull request reviews, CCB approval

### 3.4 Tagging Strategy

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

---

## 4. CONFIGURATION CONTROL

### 4.1 Change Control Process

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

**Who**: Any project member, customer, or stakeholder

**Process**:
1. Create Change Request (CR) document using template
2. Assign unique CR ID: `CR-YYYY-NNN`
3. Submit to Configuration Manager
4. CM logs CR in Change Request Register

**Required Information**:
- CR ID
- Submitter name and date
- Affected CIs (by ID)
- Reason for change
- Proposed solution (if known)
- Priority (Critical / High / Medium / Low)
- SIL impact assessment

#### 4.1.2 Change Impact Analysis

**Who**: Configuration Manager (with input from technical leads)

**Process**:
1. Identify all affected CIs (requirements, design, code, tests)
2. Assess impact on:
   - SIL level (does it increase safety risk?)
   - Requirements traceability
   - Verification and validation
   - Schedule and cost
   - Existing baselines
3. Document analysis in CR
4. Schedule CCB review

**Mandatory for SIL 3-4**: Impact on safety requirements, hazard log, traceability matrix

#### 4.1.3 CCB Review and Decision

**When**: Regular CCB meetings (or emergency session for critical changes)

**Process**:
1. CM presents change request and impact analysis
2. CCB discusses technical, safety, schedule implications
3. CCB votes: **Approve** / **Reject** / **Defer** (pending more info)
4. CM records decision in CCB minutes
5. CM notifies submitter and affected parties

**Approval Criteria**:
- Technical feasibility
- No adverse safety impact (or justified)
- Traceability maintained
- Verification plan updated
- Resources available

#### 4.1.4 Implementation

**Who**: Assigned developer(s)

**Process**:
1. Create feature/bugfix branch from `develop`
2. Implement changes following coding standards (MISRA C:2012)
3. Update affected CIs (code, docs, tests, traceability)
4. Commit with reference to CR ID in commit message
5. Create pull request for review

**Commit Message Format**:
```
[CR-YYYY-NNN] Brief description of change

- Detailed explanation
- Affected modules: module_name.c, module_name.h
- Traceability: REQ-FUNC-001 → MOD-001 → test_module.c
- SIL impact: None / Minor / Requires re-verification
```

#### 4.1.5 Verification of Change

**Who**: Verifier (independent for SIL 3-4), QA Manager

**Process**:
1. Review pull request for code quality, MISRA C compliance
2. Run static analysis (PC-lint, Cppcheck)
3. Execute affected tests (unit, integration, system)
4. Verify coverage requirements met (per SIL level)
5. Update verification evidence
6. Approve pull request if all checks pass

**Mandatory Checks**:
- MISRA C compliance (SIL 2+)
- Complexity within limits (SIL-specific)
- Traceability updated (RTM, hazard log)
- Test coverage maintained (per Table A.21)

#### 4.1.6 Update Baseline and Traceability

**Who**: Configuration Manager

**Process**:
1. Merge approved pull request to `develop`
2. Update Configuration Status Accounting log
3. Update Requirements Traceability Matrix (SIL 3-4 mandatory)
4. Tag baseline if change triggers new release
5. Archive old baseline version

#### 4.1.7 Configuration Status Accounting

**Who**: Configuration Manager

**Process**:
1. Record change in Configuration Status Report
2. Update CI status in version control
3. Notify stakeholders of baseline change
4. Update project documentation index

### 4.2 Baseline Management

**Baseline Definition**: An approved version of a configuration item that can only be changed through formal change control.

#### 4.2.1 Baseline Types

| Baseline Type | Trigger | CIs Included | CCB Approval Required |
|---------------|---------|--------------|----------------------|
| **Planning Baseline** | Phase 1 gate approval | SQAP, SCMP, SVP, SVaP | Yes |
| **Requirements Baseline** | Phase 2 gate approval | SRS, RTM, Hazard Log | Yes |
| **Design Baseline** | Phase 3 gate approval | SAS, SDS, Interface Specs | Yes |
| **Implementation Baseline** | Phase 4 gate approval | Source code, Unit tests | Yes |
| **Integration Baseline** | Phase 5 gate approval | Integration tests, reports | Yes |
| **Validation Baseline** | Phase 6 gate approval | System tests, validation report | Yes |
| **Release Baseline** | Deployment approval | All CIs (complete software package) | Yes |

#### 4.2.2 Baseline Creation Process

1. **Trigger**: Phase gate approval by Lifecycle Coordinator (`/cod gate-check <phase>`)
2. **CM Action**: 
   - Freeze CIs (no further changes without CR)
   - Create baseline branch (e.g., `release/v1.0`)
   - Tag baseline with version number
   - Archive baseline in secure location
   - Update Configuration Status Accounting
3. **CCB Action**: Formal baseline approval meeting
4. **CM Action**: Publish baseline notification to stakeholders

#### 4.2.3 Baseline Modification

**Process**: All baseline modifications SHALL go through Change Control (Section 4.1)

**SIL 3-4 Additional Requirements**:
- Independent impact analysis required
- Safety assessment for safety-critical CIs
- Re-verification evidence required
- Traceability matrix update mandatory

### 4.3 Build and Release Management

#### 4.3.1 Build Process

**Continuous Integration**:
- Automated builds triggered on every commit to `develop`
- Build artifacts: executable, library, documentation
- Build logs archived

**Build Verification**:
- All unit tests pass
- MISRA C compliance check (SIL 2+)
- Static analysis clean (no critical/high issues)
- Complexity analysis within limits

**Tools**:
- Make / CMake
- GCC / Clang with MISRA C flags
- PC-lint Plus (MISRA C checker)
- Cppcheck (static analyzer)

#### 4.3.2 Release Process

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

---

## 5. CONFIGURATION STATUS ACCOUNTING

### 5.1 Configuration Status Reports

**Frequency**: 
- **SIL 0-2**: Monthly
- **SIL 3-4**: Bi-weekly (mandatory per Table A.9, Technique 7 - Data Recording and Analysis)

**Report Contents**:
- List of all CIs with current version
- Baseline status (established, modified, released)
- Pending change requests
- Recently approved changes
- Build status
- Defect summary
- Traceability status (SIL 3-4)

**Distribution**: Project Manager, QA Manager, Lifecycle Coordinator, CCB members

### 5.2 Traceability Management (Mandatory SIL 3-4)

**Requirements Traceability Matrix (RTM)**:

**Format**: `docs/traceability/RTM.md`

**Traceability Links** (mandatory):
```
System Requirement → Software Requirement → Architecture → Design → Code → Test Case → Test Result
```

**Update Trigger**: Every CI modification

**Verification**: Independent verification required (SIL 3-4)

**Example RTM Entry**:
| System Req | SW Req | Architecture | Design | Code | Unit Test | Integration Test | Validation Test | Status |
|------------|--------|--------------|--------|------|-----------|------------------|-----------------|--------|
| SYS-001 | REQ-FUNC-001 | SAS-MOD-001 | SDS-MOD-001 | brake.c:45 | TC-UNIT-001 | TC-INT-001 | TC-VAL-001 | Verified |

### 5.3 Data Recording and Analysis (Mandatory SIL 3-4)

**EN 50128 Requirement**: Table A.9, Technique 7 - **MANDATORY for SIL 3-4**

**Recorded Data**:
- Change request metrics (count, type, priority, resolution time)
- Defect metrics (count, severity, phase detected, root cause)
- Build metrics (build success rate, build time)
- Test metrics (pass rate, coverage, defect density)
- Review metrics (review findings, review effort)

**Analysis Frequency**: Monthly (minimum)

**Reports To**: Project Manager, QA Manager, Lifecycle Coordinator

**Tool**: [Specify defect tracking tool, e.g., Jira, Bugzilla, CSV-based]

---

## 6. CONFIGURATION AUDITS

### 6.1 Audit Types

#### 6.1.1 Physical Configuration Audit (PCA)

**Purpose**: Verify that physical software artifacts match the documented configuration.

**When**: Before each baseline release

**Scope**:
- Source code files present and match version control
- Documentation versions match CI register
- Build artifacts reproducible from source
- Test artifacts complete

**Auditor**: Configuration Manager (SIL 0-2) or Independent Auditor (SIL 3-4)

**Deliverable**: PCA Report

#### 6.1.2 Functional Configuration Audit (FCA)

**Purpose**: Verify that software functionality matches requirements and design specifications.

**When**: After validation testing, before release

**Scope**:
- Requirements traceability complete
- All tests passed
- Verification evidence complete
- Validation evidence complete
- Safety requirements verified (if applicable)

**Auditor**: QA Manager (SIL 0-2) or Independent Auditor (SIL 3-4)

**Deliverable**: FCA Report

### 6.2 Audit Process

1. **Schedule Audit**: CM schedules audit with 2-week notice
2. **Prepare Audit Checklist**: CM prepares checklist based on audit scope
3. **Conduct Audit**: Auditor reviews CIs, documentation, evidence
4. **Record Findings**: Auditor documents conformances and non-conformances
5. **Corrective Actions**: Project team addresses non-conformances
6. **Close Audit**: Auditor verifies corrective actions, issues audit report
7. **CCB Review**: CCB reviews audit report, approves baseline if clean

### 6.3 Audit Checklists

#### PCA Checklist
- [ ] All source code files under version control
- [ ] Version numbers match CI register
- [ ] Build reproducible from tagged source
- [ ] Documentation complete and versioned
- [ ] Test artifacts archived
- [ ] Traceability matrix up-to-date (SIL 3-4)

#### FCA Checklist
- [ ] All requirements traced to tests
- [ ] All tests passed (evidence provided)
- [ ] Coverage requirements met (per Table A.21)
- [ ] MISRA C compliance verified (SIL 2+)
- [ ] Complexity within limits
- [ ] Verification report complete
- [ ] Validation report complete
- [ ] Safety requirements verified (if applicable)

---

## 7. TOOLS AND INFRASTRUCTURE

### 7.1 Version Control System

**Tool**: Git

**Repository Location**: [Specify: local server, GitHub, GitLab, etc.]

**Access Control**:
- Read access: All project members
- Write access: Developers (with pull request workflow)
- Admin access: Configuration Manager, Project Manager

**Backup**: Daily automated backup to [specify location]

### 7.2 Configuration Management Tools

| Tool | Purpose | SIL Requirement |
|------|---------|-----------------|
| **Git** | Version control | All SILs |
| **Make / CMake** | Build automation | All SILs |
| **PC-lint Plus** | MISRA C checking | SIL 2+ |
| **Cppcheck** | Static analysis | SIL 2+ (HR SIL 3-4) |
| **gcov / lcov** | Coverage analysis | SIL 2+ |
| **Doxygen** | Code documentation | Recommended |
| **Markdown** | Document authoring | All SILs |

### 7.3 Tool Qualification (SIL 3-4)

**EN 50128 Requirement**: Tools used for automated verification SHALL be qualified (Section 6.7)

**Tools Requiring Qualification**:
- Compiler (GCC/Clang) - T3 tool (requires qualification)
- Static analyzers (PC-lint, Cppcheck) - T2 tool (validation required)
- Test harness (Unity) - T1 tool (low risk)

**Qualification Evidence**: [Specify location of tool qualification reports]

---

## 8. TRAINING AND COMPETENCE

### 8.1 Required Training

All project personnel SHALL receive training on:
- Version control procedures (Git workflow)
- Branch strategy and pull request process
- Change control process
- MISRA C coding standards (developers)
- Configuration audit procedures (auditors)

**Training Records**: Maintained by Configuration Manager

### 8.2 Competence Requirements

**Configuration Manager**:
- Experience with version control systems
- Knowledge of EN 50128 configuration management requirements
- Understanding of software development lifecycle

**CCB Members**:
- Understanding of change impact analysis
- Knowledge of project constraints (safety, schedule, cost)
- Authority to make change decisions

---

## 9. COMPLIANCE MATRIX

### 9.1 EN 50128 Section 6.6 Compliance

| Requirement | Section | Evidence | Status |
|-------------|---------|----------|--------|
| **CM Plan established** | 6.6.2 | This document (SCMP) | ✓ |
| **Configuration identification** | 6.6.2.2 | Section 3 | ✓ |
| **Configuration control** | 6.6.2.3 | Section 4 | ✓ |
| **Configuration status accounting** | 6.6.2.4 | Section 5 | ✓ |
| **Configuration audits** | 6.6.2.5 | Section 6 | ✓ |
| **Version control** | 6.6.2.2 | Git repository | ✓ |
| **Change control** | 6.6.2.3 | CCB process (Section 4.1) | ✓ |
| **Traceability (SIL 3-4)** | Table A.9 | RTM (Section 5.2) | ✓ |
| **Data recording (SIL 3-4)** | Table A.9 | Metrics (Section 5.3) | ✓ |

### 9.2 EN 50128 Table A.9 Compliance (QA Techniques)

| # | Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Implementation |
|---|-----------|-------|---------|---------|----------------|
| **1** | Software Configuration Management | **M** | **M** | **M** | This document (SCMP) |
| **2** | Traceability | R | HR | **M** | Section 5.2 (RTM) |
| **7** | Data Recording and Analysis | HR | HR | **M** | Section 5.3 |

---

## 10. REFERENCES

### 10.1 Normative References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[EN50126]** | EN 50126:2017 Railway applications - The specification and demonstration of Reliability, Availability, Maintainability and Safety (RAMS) |

### 10.2 Project References

| Reference | Document |
|-----------|----------|
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-YYYY-NNN |
| **[SVP]** | Software Verification Plan, DOC-SVP-YYYY-NNN |
| **[SVaP]** | Software Validation Plan, DOC-SVaP-YYYY-NNN |
| **[LIFECYCLE]** | LIFECYCLE.md - EN 50128 V-Model lifecycle definition |

---

## APPENDICES

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

### Appendix B: Configuration Status Report Template

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

## 4. Metrics (SIL 3-4)
- **Open CRs**: 3
- **Closed CRs (this period)**: 7
- **Defects Found**: 12
- **Defects Fixed**: 10
- **Test Coverage**: 98% statement, 95% branch

## 5. Traceability Status (SIL 3-4)
- **Requirements traced**: 100% (45/45)
- **Design elements traced**: 100% (23/23)
- **Code traced**: 100% (15 modules)
- **Tests traced**: 98% (155/158)

## 6. Issues and Risks
[List any configuration management issues or risks]
```

### Appendix C: Audit Report Template

```markdown
# Configuration Audit Report

**Audit Type**: [Physical Configuration Audit (PCA) / Functional Configuration Audit (FCA)]  
**Audit Date**: YYYY-MM-DD  
**Auditor**: [Name], [Role]  
**Baseline**: [Baseline name and version]

## 1. Audit Scope
[Describe the scope of the audit]

## 2. Audit Checklist Results
| Item | Expected | Actual | Status | Notes |
|------|----------|--------|--------|-------|
| All source files under VC | Yes | Yes | ✓ Pass | - |
| Traceability complete | 100% | 98% | ✗ Fail | 2 tests not traced |

## 3. Conformances
[List items that passed audit]

## 4. Non-Conformances
| # | Description | Severity | Assigned To | Due Date |
|---|-------------|----------|-------------|----------|
| 1 | TC-INT-005 not traced to REQ-FUNC-012 | Medium | [Name] | YYYY-MM-DD |

## 5. Corrective Actions
[Track corrective actions for non-conformances]

## 6. Audit Conclusion
- **Overall Result**: [Pass / Fail / Pass with Conditions]
- **Baseline Approval**: [Approved / Not Approved]
- **Auditor Signature**: ___________________
- **Date**: YYYY-MM-DD
```

---

## DOCUMENT HISTORY

This document is maintained under configuration control per Section 4. All changes SHALL be approved by the Change Control Board (CCB).

**Current Version**: [Version from header]  
**Last Updated**: [Date from header]  
**Next Review**: [Date - recommended annual review]

---

**END OF DOCUMENT**
