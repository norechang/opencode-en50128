# Quality Audit Workflow

**EN 50128 Reference**: Section 6.5.1.2 (Provide evidence that activities have been carried out), Section 6.5.4.5  
**Phase**: All phases (periodic activity)  
**Role**: Quality Assurance (QUA), with Independent Assessor (SIL 3-4)  
**SIL Level**: All (0-4)

---

## Purpose

This workflow defines the quality audit process for EN 50128 railway software development. Quality audits provide **independent verification** that the software development process is being followed and that deliverables meet EN 50128 requirements.

**Key Objectives**:
- Verify EN 50128 lifecycle process compliance (V-Model adherence)
- Verify artifact completeness and quality (deliverable audits)
- Verify tool qualification status (T1, T2, T3 tools per Annex B)
- Identify non-conformances and drive corrective actions
- Provide audit trail for certification and assessment
- Support continuous process improvement

**Audit Types**:
1. **Process Compliance Audits**: Verify V-Model lifecycle adherence
2. **Artifact Audits**: Verify deliverable completeness per EN 50128 Annex C
3. **Tool Qualification Audits**: Verify T2/T3 tools qualified per Annex B
4. **Pre-Release Audit**: Final audit before deployment (MANDATORY SIL 3-4)

**Inputs**:
- Software Quality Assurance Plan (SQAP)
- Software Configuration Management Plan (SCMP)
- All lifecycle deliverables
- EN 50128:2011 requirements
- Tool qualification reports (T2/T3 tools)

**Outputs**:
- Audit Plan
- Audit Checklist
- Audit Report (findings, non-conformances, corrective actions)
- Corrective Action Tracking
- Audit closure report

---

## Table of Contents

1. [Quality Audit Overview](#quality-audit-overview)
2. [Audit Types](#audit-types)
3. [Audit Planning](#audit-planning)
4. [Process Compliance Audit](#process-compliance-audit)
5. [Artifact Audit](#artifact-audit)
6. [Tool Qualification Audit](#tool-qualification-audit)
7. [Pre-Release Audit](#pre-release-audit)
8. [Audit Execution](#audit-execution)
9. [Finding Management](#finding-management)
10. [Corrective Action Tracking](#corrective-action-tracking)
11. [Audit Report Generation](#audit-report-generation)
12. [Tool Integration](#tool-integration)
13. [SIL-Specific Requirements](#sil-specific-requirements)
14. [Example Audit Scenarios](#example-audit-scenarios)

---

## Quality Audit Overview

### Purpose of Quality Audits

**EN 50128 Section 6.5.1.2**: "The Software Quality Assurance shall provide objective evidence that all activities, both technical and managerial, related to the software have been performed in accordance with the plans, procedures, standards and conventions"

Quality audits provide **independent verification** that:
1. **Process**: EN 50128 lifecycle is being followed
2. **Products**: Deliverables meet EN 50128 requirements
3. **People**: Roles and responsibilities are clear and followed
4. **Tools**: Tools are qualified per EN 50128 Annex B

**Quality Audits vs. Reviews**:
- **Reviews**: Focus on specific deliverable content (technical correctness)
- **Audits**: Focus on process compliance and deliverable completeness (process correctness)

---

### Audit Frequency by SIL

| SIL Level | Process Audit Frequency | Artifact Audit Frequency | Tool Audit Frequency | Pre-Release Audit |
|-----------|------------------------|-------------------------|---------------------|------------------|
| **SIL 0-1** | Optional (ad-hoc) | Optional | Optional | Optional |
| **SIL 2** | Recommended (quarterly) | Recommended (per phase) | Recommended (once) | Highly Recommended |
| **SIL 3-4** | **MANDATORY** (monthly) | **MANDATORY** (per phase) | **MANDATORY** (per tool) | **MANDATORY** |

---

### Audit Independence Requirements

| SIL Level | Auditor Independence Requirement |
|-----------|--------------------------------|
| **SIL 0-1** | Recommended (can be internal QA) |
| **SIL 2** | Highly Recommended (should be independent of project) |
| **SIL 3-4** | **MANDATORY** (Independent Assessor per EN 50128 §6.4.1.1; §5.1.2.4–§5.1.2.7) |

**SIL 3-4 Independence**:
- Auditor MUST NOT be part of development team
- Auditor MUST NOT report to Project Manager
- Auditor reports to senior management, Safety Manager, or customer
- Auditor has authority to stop release if critical non-conformances found

---

### Audit Workflow Overview

```
Audit Planning (QA Manager + Assessor)
          ↓
Audit Preparation (collect evidence, prepare checklist)
          ↓
Opening Meeting (introduce audit scope and process)
          ↓
Audit Execution (review documents, interview personnel, observe processes)
          ↓
Finding Documentation (log non-conformances, observations)
          ↓
Closing Meeting (present findings, discuss corrective actions)
          ↓
Audit Report Generation (within 5 business days)
          ↓
Corrective Action Implementation (assigned to responsible parties)
          ↓
Follow-up Audit (verify corrective actions implemented)
          ↓
Audit Closure (all corrective actions verified)
```

---

## Audit Types

### 1. Process Compliance Audit

**Purpose**: Verify EN 50128 V-Model lifecycle process is being followed

**Audit Focus**:
- Are lifecycle phases executed in correct sequence?
- Are phase gates enforced (SIL-specific criteria)?
- Are EN 50128 techniques applied per Tables A.2-A.21?
- Are roles and responsibilities clear (REQ, DES, IMP, TST, VER, VAL, etc.)?
- Is configuration management active (baselines, change control)?
- Is traceability maintained (MANDATORY SIL 3-4)?

**Frequency**:
- SIL 3-4: Monthly (MANDATORY)
- SIL 2: Quarterly (Highly Recommended)
- SIL 0-1: Optional (ad-hoc)

**Audit Checklist**: See [Process Compliance Audit Checklist](#process-compliance-audit-checklist)

---

### 2. Artifact Audit

**Purpose**: Verify deliverables meet EN 50128 Annex C requirements

**Audit Focus**:
- Are all mandatory deliverables produced (per Annex C Table C.1)?
- Do deliverables follow EN 50128 templates (Document Control, Approvals, Traceability)?
- Are deliverables reviewed and approved (per SIL-specific approvers)?
- Are deliverables under configuration management (version control, baselines)?
- Is traceability complete (requirements → design → code → tests)?

**Frequency**:
- SIL 3-4: Per phase (MANDATORY)
- SIL 2: Per phase (Highly Recommended)
- SIL 0-1: Optional

**Audit Checklist**: See [Artifact Audit Checklist](#artifact-audit-checklist)

---

### 3. Tool Qualification Audit

**Purpose**: Verify tools are qualified per EN 50128 Annex B

**Audit Focus**:
- Are all tools classified (T1, T2, T3)?
- Are T2 tools validated (increased confidence from use)?
- Are T3 tools qualified (tool qualification report per Annex B.4)?
- Are tool versions documented and controlled?
- Are tool qualification reports available for assessment?

**Frequency**:
- SIL 3-4: Per tool, once before use (MANDATORY for T2/T3)
- SIL 2: Recommended for T2/T3 tools
- SIL 0-1: Optional

**Audit Checklist**: See [Tool Qualification Audit Checklist](#tool-qualification-audit-checklist)

---

### 4. Pre-Release Audit

**Purpose**: Final verification before deployment (MANDATORY SIL 3-4)

**Audit Focus**:
- Are all lifecycle phases complete?
- Are all deliverables approved (including Verification Report, Validation Report)?
- Are all defects resolved (no open Critical or Major defects)?
- Is traceability 100% (requirements → design → code → tests)?
- Are all non-conformances closed?
- Is Safety Case complete (SIL 2+)?
- Is Assessor approval obtained (SIL 3-4)?

**Frequency**:
- SIL 3-4: Once before deployment (MANDATORY)
- SIL 2: Highly Recommended before deployment
- SIL 0-1: Optional

**Audit Checklist**: See [Pre-Release Audit Checklist](#pre-release-audit-checklist)

---

## Audit Planning

### Step 1: Define Audit Scope

**Audit Plan Contents**:
- Audit type (Process / Artifact / Tool / Pre-Release)
- Audit scope (phase, deliverables, tools)
- Audit objectives (specific questions to answer)
- Audit team (lead auditor, supporting auditors)
- Audit schedule (start date, duration, closing meeting date)
- Auditees (project team members to interview)
- Evidence required (documents, logs, tool reports)

**Example Audit Plan**:
```markdown
# Quality Audit Plan: AUD-2026-Q1-001

## Audit Information

| Field | Value |
|-------|-------|
| **Audit ID** | AUD-2026-Q1-001 |
| **Audit Type** | Process Compliance Audit |
| **Project** | Railway Door Controller |
| **SIL Level** | 3 |
| **Audit Scope** | Requirements, Design, Implementation phases |
| **Audit Period** | 2026-01-01 to 2026-03-31 (Q1 2026) |
| **Audit Date** | 2026-04-10 to 2026-04-12 (3 days) |

## Audit Team

| Role | Name | Independence Status |
|------|------|-------------------|
| **Lead Auditor** | Eve Green (QA Manager) | Independent (reports to Safety Manager) |
| **Assessor** | Frank Black | Independent (external assessor) |
| **Support Auditor** | Grace Gray (QA Engineer) | Independent |

## Audit Objectives

1. Verify EN 50128 V-Model lifecycle adherence (phases 1-4)
2. Verify phase gate criteria enforced (SIL 3 requirements)
3. Verify traceability maintained (requirements → design → code)
4. Verify configuration management active (baselines, change control)
5. Identify non-conformances and drive corrective actions

## Audit Scope

### In Scope
- Requirements phase (Phase 2): Software Requirements Specification
- Design phase (Phase 3): Software Architecture Specification, Software Design Specification
- Implementation phase (Phase 4): Source code, unit tests
- Traceability: REQ → DES → IMP
- Configuration management: Git, baselines, change control

### Out of Scope
- Testing phase (Phase 5): Will be audited in Q2 2026
- Integration phase (Phase 6): Not yet started
- Validation phase (Phase 7): Not yet started

## Audit Schedule

| Date | Time | Activity | Participants |
|------|------|----------|--------------|
| 2026-04-10 | 09:00-09:30 | Opening Meeting | All project team + audit team |
| 2026-04-10 | 09:30-12:00 | Document Review (SRS, SAS, SDS) | Audit team |
| 2026-04-10 | 13:00-15:00 | Interview REQ, DES, IMP | Audit team + REQ/DES/IMP |
| 2026-04-11 | 09:00-12:00 | Code Review (sample) | Audit team + IMP |
| 2026-04-11 | 13:00-15:00 | Traceability Check | Audit team + CM |
| 2026-04-11 | 15:00-17:00 | Configuration Management Check | Audit team + CM |
| 2026-04-12 | 09:00-12:00 | Finding Documentation | Audit team |
| 2026-04-12 | 14:00-15:00 | Closing Meeting | All project team + audit team |

## Evidence Required

- Software Requirements Specification (DOC-REQ-SRS-001)
- Software Architecture Specification (DOC-DES-SAS-001)
- Software Design Specification (DOC-DES-SDS-001)
- Source code (src/*.c)
- Traceability matrices (evidence/traceability/*.md)
- Configuration management logs (git log, baseline tags)
- Phase gate approval records (LIFECYCLE_STATE.md)
- Review reports (QA review reports, technical review reports)

## Audit Checklist

See: `.opencode/skills/en50128-quality/workflows/quality-audit-workflow.md` Section "Process Compliance Audit Checklist"
```

---

### Step 2: Notify Project Team

**Notification Email**:
```
To: Project Team (PM, REQ, DES, IMP, TST, CM, etc.)
Subject: Quality Audit Scheduled: AUD-2026-Q1-001

Dear Project Team,

A quality audit has been scheduled for the Railway Door Controller project:

Audit ID: AUD-2026-Q1-001
Audit Type: Process Compliance Audit (Q1 2026)
Audit Dates: 2026-04-10 to 2026-04-12 (3 days)
Audit Team: Eve Green (Lead Auditor), Frank Black (Assessor), Grace Gray (Support)

Audit Scope:
- Requirements, Design, Implementation phases (Q1 2026 activities)
- EN 50128 V-Model lifecycle compliance
- Traceability and configuration management

Opening Meeting: 2026-04-10 09:00-09:30 (Conference Room A)

Please prepare:
- All deliverables ready for review (SRS, SAS, SDS, source code)
- Traceability matrices up to date
- Review reports and approvals available
- Configuration management logs accessible

If you have any questions, please contact Eve Green (QA Manager).

Thank you,
Quality Assurance Team
```

---

## Process Compliance Audit

### Process Compliance Audit Checklist

**EN 50128 Reference**: Section 5 (Lifecycle), Section 6 (Software Quality Assurance)

#### 1. Lifecycle Process (V-Model)

| Check | SIL 0-1 | SIL 2 | SIL 3-4 | Evidence | Status | Notes |
|-------|---------|-------|---------|----------|--------|-------|
| Are lifecycle phases executed in correct sequence? | R | HR | **M** | LIFECYCLE_STATE.md | ☐ OK ☐ NC | |
| Are phase gates enforced (SIL-specific criteria)? | R | HR | **M** | Phase gate approval records | ☐ OK ☐ NC | |
| Is COD (Lifecycle Coordinator) managing phase transitions? | R | HR | **M** | Phase gate records | ☐ OK ☐ NC | |
| Are out-of-sequence activities prevented? | R | HR | **M** | LIFECYCLE_STATE.md | ☐ OK ☐ NC | |

**Legend**: M = Mandatory, HR = Highly Recommended, R = Recommended, NC = Non-Conformance

---

#### 2. Requirements Phase (Phase 2)

| Check | SIL 0-1 | SIL 2 | SIL 3-4 | Evidence | Status | Notes |
|-------|---------|-------|---------|----------|--------|-------|
| Is Software Requirements Specification (SRS) complete? | HR | **M** | **M** | DOC-REQ-SRS-001 | ☐ OK ☐ NC | |
| Are requirements traceable to system requirements? | R | HR | **M** | Traceability matrix | ☐ OK ☐ NC | |
| Is SIL level assigned to each requirement? | R | HR | **M** | SRS Section 2 | ☐ OK ☐ NC | |
| Are safety requirements identified? | R | HR | **M** | SRS + Hazard Log | ☐ OK ☐ NC | |
| Are requirements reviewed and approved? | R | HR | **M** | Review reports | ☐ OK ☐ NC | |
| Is requirements phase gate approved? | R | HR | **M** | LIFECYCLE_STATE.md | ☐ OK ☐ NC | |

---

#### 3. Design Phase (Phase 3)

| Check | SIL 0-1 | SIL 2 | SIL 3-4 | Evidence | Status | Notes |
|-------|---------|-------|---------|----------|--------|-------|
| Is Software Architecture Specification (SAS) complete? | HR | **M** | **M** | DOC-DES-SAS-001 | ☐ OK ☐ NC | |
| Is Software Design Specification (SDS) complete? | HR | **M** | **M** | DOC-DES-SDS-001 | ☐ OK ☐ NC | |
| Is design modular (MANDATORY SIL 2+)? | R | **M** | **M** | SAS Section 4 | ☐ OK ☐ NC | |
| Is complexity within limits (CCN ≤ 10 for SIL 3-4)? | R | HR | **M** | Complexity analysis | ☐ OK ☐ NC | |
| Is design traceable to requirements? | R | HR | **M** | Traceability matrix | ☐ OK ☐ NC | |
| Are design reviews performed? | R | HR | **M** | Design review reports | ☐ OK ☐ NC | |
| Is design phase gate approved? | R | HR | **M** | LIFECYCLE_STATE.md | ☐ OK ☐ NC | |

---

#### 4. Implementation Phase (Phase 4)

| Check | SIL 0-1 | SIL 2 | SIL 3-4 | Evidence | Status | Notes |
|-------|---------|-------|---------|----------|--------|-------|
| Is source code complete? | HR | **M** | **M** | src/*.c | ☐ OK ☐ NC | |
| Is MISRA C:2012 compliant (SIL 2+)? | R | **M** | **M** | Cppcheck reports | ☐ OK ☐ NC | |
| Zero MISRA C mandatory violations (SIL 2+)? | R | **M** | **M** | Static analysis report | ☐ OK ☐ NC | |
| Is complexity within limits? | R | HR | **M** | Lizard reports | ☐ OK ☐ NC | |
| Is static allocation only (SIL 2+)? | R | **M** | **M** | Code review report | ☐ OK ☐ NC | |
| Are unit tests complete? | R | HR | **M** | test/*.c | ☐ OK ☐ NC | |
| Is unit test coverage adequate (SIL-specific)? | R | HR | **M** | gcov/lcov reports | ☐ OK ☐ NC | |
| Are code reviews performed? | R | HR | **M** | Code review reports | ☐ OK ☐ NC | |
| Is code traceable to design? | R | HR | **M** | Code comments | ☐ OK ☐ NC | |
| Is implementation phase gate approved? | R | HR | **M** | LIFECYCLE_STATE.md | ☐ OK ☐ NC | |

---

#### 5. Configuration Management

| Check | SIL 0-1 | SIL 2 | SIL 3-4 | Evidence | Status | Notes |
|-------|---------|-------|---------|----------|--------|-------|
| Is SCMP (Software Configuration Management Plan) active? | **M** | **M** | **M** | DOC-CM-PLAN-001 | ☐ OK ☐ NC | |
| Are all artifacts under version control? | **M** | **M** | **M** | Git repository | ☐ OK ☐ NC | |
| Are baselines defined and controlled? | **M** | **M** | **M** | Git tags | ☐ OK ☐ NC | |
| Is change control active (Change Control Board)? | R | HR | **M** | Change requests | ☐ OK ☐ NC | |
| Are configuration audits performed? | R | HR | **M** | Audit reports | ☐ OK ☐ NC | |

**Note**: Configuration Management is **MANDATORY for ALL SIL levels** (0, 1, 2, 3, 4) per EN 50128 Section 6.6

---

#### 6. Traceability

| Check | SIL 0-1 | SIL 2 | SIL 3-4 | Evidence | Status | Notes |
|-------|---------|-------|---------|----------|--------|-------|
| Is forward traceability maintained (REQ → DES → CODE → TESTS)? | R | HR | **M** | Traceability matrices | ☐ OK ☐ NC | |
| Is backward traceability maintained (TESTS → CODE → DES → REQ)? | R | HR | **M** | Traceability matrices | ☐ OK ☐ NC | |
| Is traceability coverage 100% (no orphan requirements)? | R | HR | **M** | Traceability reports | ☐ OK ☐ NC | |
| Is traceability validated? | R | HR | **M** | workspace.py trace validate | ☐ OK ☐ NC | |

---

#### 7. Quality Assurance

| Check | SIL 0-1 | SIL 2 | SIL 3-4 | Evidence | Status | Notes |
|-------|---------|-------|---------|----------|--------|-------|
| Is SQAP (Software Quality Assurance Plan) active? | HR | **M** | **M** | DOC-QUA-PLAN-001 | ☐ OK ☐ NC | |
| Are document reviews performed? | R | HR | **M** | QA review reports | ☐ OK ☐ NC | |
| Are technical reviews performed? | R | HR | **M** | Technical review reports | ☐ OK ☐ NC | |
| Are quality gates enforced? | R | HR | **M** | Gate approval records | ☐ OK ☐ NC | |
| Is QA independent of development (SIL 3-4)? | R | HR | **M** | Org chart | ☐ OK ☐ NC | |

---

### Process Audit Execution

**Audit Activities**:
1. **Document Review** (2-4 hours):
   - Review SQAP, SCMP, lifecycle state
   - Check phase gate approvals
   - Verify deliverable completeness

2. **Traceability Check** (2 hours):
   ```bash
   # Validate traceability
   workspace.py trace validate --phase design --sil 3
   workspace.py trace validate --phase implementation --sil 3
   
   # Generate traceability reports
   workspace.py trace report --from requirements --to design \
       --format markdown --output audit_evidence/traceability_req_to_des.md
   workspace.py trace report --from design --to implementation \
       --format markdown --output audit_evidence/traceability_des_to_code.md
   ```

3. **Configuration Management Check** (2 hours):
   ```bash
   # Check Git repository structure
   git log --oneline --all --graph
   
   # Check baselines (tags)
   git tag -l "baseline-*"
   
   # Check change control
   git log --grep="CR-" --oneline
   ```

4. **Interviews** (3-4 hours):
   - Interview PM: Phase gate process
   - Interview REQ: Requirements process
   - Interview DES: Design process
   - Interview IMP: Implementation process
   - Interview CM: Configuration management process

5. **Observations** (1-2 hours):
   - Observe code review meeting
   - Observe phase gate meeting

---

### Process Audit Finding Examples

**Finding 1: Phase Gate Not Enforced**
- **Type**: Non-Conformance (Major)
- **Area**: Lifecycle Process
- **Observation**: Implementation phase started before design phase gate approval (LIFECYCLE_STATE.md shows design gate approved 2026-03-15, but git log shows code commits starting 2026-03-10)
- **EN 50128 Reference**: Section 5.3.2.5 "All activities during a phase SHALL be defined and planned prior to commencement"
- **Impact**: Risk of implementing unapproved design, rework if design changes
- **Corrective Action**: Stop out-of-sequence activities, enforce phase gates via COD
- **Assigned To**: PM + COD
- **Due Date**: 2026-04-20

**Finding 2: Traceability Gap**
- **Type**: Non-Conformance (Critical)
- **Area**: Traceability
- **Observation**: 3 requirements (REQ-DOOR-012, REQ-DOOR-015, REQ-DOOR-018) have no design elements (workspace.py trace validate shows 92% coverage, 100% required for SIL 3)
- **EN 50128 Reference**: Section 6.5.4.5(d) "Traceability of all items to and from requirements" (MANDATORY SIL 3-4)
- **Impact**: Requirements not implemented, validation cannot proceed
- **Corrective Action**: Add design elements for missing requirements, update traceability
- **Assigned To**: DES
- **Due Date**: 2026-04-15

---

## Artifact Audit

### Artifact Audit Checklist

**EN 50128 Reference**: Annex C (Document Control Summary - Table C.1)

#### EN 50128 Annex C.1: Mandatory Deliverables

| Deliverable | SIL 0-1 | SIL 2 | SIL 3-4 | Document ID | Status | Notes |
|------------|---------|-------|---------|-------------|--------|-------|
| **Software Quality Assurance Plan (SQAP)** | HR | **M** | **M** | DOC-QUA-PLAN-001 | ☐ OK ☐ Missing | |
| **Software Configuration Management Plan (SCMP)** | **M** | **M** | **M** | DOC-CM-PLAN-001 | ☐ OK ☐ Missing | |
| **Software Verification Plan (SVP)** | R | HR | **M** | DOC-VER-PLAN-001 | ☐ OK ☐ Missing | |
| **Software Validation Plan (SVaP)** | R | HR | **M** | DOC-VAL-PLAN-001 | ☐ OK ☐ Missing | |
| **Software Requirements Specification (SRS)** | HR | **M** | **M** | DOC-REQ-SRS-001 | ☐ OK ☐ Missing | |
| **Software Architecture Specification (SAS)** | HR | **M** | **M** | DOC-DES-SAS-001 | ☐ OK ☐ Missing | |
| **Software Design Specification (SDS)** | HR | **M** | **M** | DOC-DES-SDS-001 | ☐ OK ☐ Missing | |
| **Software Source Code** | **M** | **M** | **M** | src/*.c | ☐ OK ☐ Missing | |
| **Unit Test Specification** | R | HR | **M** | DOC-TST-UTP-001 | ☐ OK ☐ Missing | |
| **Integration Test Specification** | R | HR | **M** | DOC-INT-ITP-001 | ☐ OK ☐ Missing | |
| **Validation Test Specification** | R | HR | **M** | DOC-VAL-VTP-001 | ☐ OK ☐ Missing | |
| **Verification Report** | R | HR | **M** | DOC-VER-REP-001 | ☐ OK ☐ Missing | |
| **Validation Report** | R | HR | **M** | DOC-VAL-REP-001 | ☐ OK ☐ Missing | |
| **Assessment Report** | - | - | **M** | DOC-ASS-REP-001 | ☐ OK ☐ Missing | SIL 3-4 only |

---

#### Deliverable Template Compliance

For each deliverable, check template compliance:

| Check | Evidence | Status | Notes |
|-------|----------|--------|-------|
| Document ID format correct (DOC-[ROLE]-[TYPE]-[NNN])? | Document header | ☐ OK ☐ NC | |
| Document Control table present and complete? | Document header | ☐ OK ☐ NC | |
| Version History table present? | Document Section 2 | ☐ OK ☐ NC | |
| Approvals table present with SIL-specific approvers? | Document Section 3 | ☐ OK ☐ NC | |
| Traceability section present (SIL 3-4)? | Document Section 7+ | ☐ OK ☐ NC | |
| EN 50128:2011 reference in References section? | Document last section | ☐ OK ☐ NC | |

---

#### Deliverable Review Status

| Deliverable | QA Document Review | Technical Review | Approved By | Baseline | Status | Notes |
|------------|-------------------|-----------------|-------------|----------|--------|-------|
| DOC-REQ-SRS-001 | ☐ Pass ☐ Fail | ☐ Pass ☐ Fail | | ☐ Yes ☐ No | ☐ OK ☐ NC | |
| DOC-DES-SAS-001 | ☐ Pass ☐ Fail | ☐ Pass ☐ Fail | | ☐ Yes ☐ No | ☐ OK ☐ NC | |
| DOC-DES-SDS-001 | ☐ Pass ☐ Fail | ☐ Pass ☐ Fail | | ☐ Yes ☐ No | ☐ OK ☐ NC | |

---

### Artifact Audit Execution

**Audit Activities**:
1. **Deliverable Inventory** (1 hour):
   - List all deliverables produced
   - Check against EN 50128 Annex C Table C.1 mandatory list
   - Identify missing deliverables (non-conformance)

2. **Template Compliance Check** (2-3 hours):
   ```bash
   # Run automated document checker for each deliverable
   for doc in docs/DOC-*.md; do
       python3 tools/document_checker.py \
           --document "$doc" \
           --sil 3 \
           --output "audit_evidence/doc_check_$(basename $doc .md).json"
   done
   ```

3. **Review Status Check** (2 hours):
   - Check QA review reports for each deliverable
   - Check technical review reports for each deliverable
   - Verify approvals complete (SIL-specific approvers)

4. **Configuration Management Check** (1 hour):
   - Verify all deliverables under version control
   - Check baseline tags present
   - Verify document versions match Git tags

---

## Tool Qualification Audit

### Tool Classification per EN 50128 Annex B

| Tool Classification | Definition | Qualification Requirement |
|--------------------|------------|-------------------------|
| **T1** | Tool generates no outputs used in executable code or verification/validation | No qualification required |
| **T2** | Tool supports test or verification (output not part of executable) | Increased confidence from use (validation) |
| **T3** | Tool generates outputs that are part of executable or contribute to verification/validation | Qualification per Annex B.4 (formal qualification report) |

---

### Tool Qualification Audit Checklist

| Tool | Version | Classification | Qualification Status | Evidence | Status | Notes |
|------|---------|---------------|---------------------|----------|--------|-------|
| **gcc** | 11.4.0 | T3 (compiler) | ☐ Qualified ☐ Not Qualified | Tool Qual Report | ☐ OK ☐ NC | |
| **Cppcheck** | 2.13.0 | T2 (static analysis) | ☐ Validated ☐ Not Validated | Validation report | ☐ OK ☐ NC | |
| **gcov** | 11.4.0 | T2 (coverage) | ☐ Validated ☐ Not Validated | Validation report | ☐ OK ☐ NC | |
| **Lizard** | 1.17.10 | T2 (complexity) | ☐ Validated ☐ Not Validated | Validation report | ☐ OK ☐ NC | |
| **Git** | 2.34.1 | T1 (version control) | N/A | N/A | ☐ OK | |

---

### T2 Tool Validation Requirements

**EN 50128 Annex B.2**: "Increased confidence from use"

**Validation Evidence Required**:
1. Tool usage history (successfully used on previous projects)
2. Tool validation report (test tool with known inputs, verify outputs)
3. Tool version control (version documented, same version used throughout)

**Example T2 Validation for Cppcheck**:
```bash
# Create validation test case
cat > test_misra_validation.c <<EOF
#include <stdint.h>

// MISRA C Rule 21.3 violation (dynamic memory allocation)
void test_malloc(void) {
    uint8_t* buffer = malloc(256);  // Should be detected
}

// MISRA C Rule 17.7 violation (unused return value)
int function_with_return(void) {
    return 42;
}

void test_unused_return(void) {
    function_with_return();  // Should be detected
}
EOF

# Run Cppcheck on validation test case
cppcheck --enable=all --addon=misra.json \
    test_misra_validation.c 2> validation_result.txt

# Verify expected violations detected
if grep -q "Rule 21.3" validation_result.txt && \
   grep -q "Rule 17.7" validation_result.txt; then
    echo "Cppcheck validation: PASS"
else
    echo "Cppcheck validation: FAIL"
fi
```

---

### T3 Tool Qualification Requirements

**EN 50128 Annex B.4**: "Qualification of software tools of tool class T3"

**Tool Qualification Report Contents**:
1. **Tool Identification**: Name, version, vendor, purpose
2. **Tool Classification**: Rationale for T3 classification
3. **Tool Validation**: Test suite, expected results, actual results
4. **Tool Limitations**: Known issues, constraints, unsupported features
5. **Tool Configuration**: Compiler flags, options, settings used
6. **Tool Environment**: Operating system, dependencies, hardware
7. **Tool Qualification Conclusion**: Qualified / Not Qualified

**Example T3 Qualification for gcc**:
```markdown
# Tool Qualification Report: gcc 11.4.0

## 1. Tool Identification

| Field | Value |
|-------|-------|
| **Tool Name** | GNU Compiler Collection (gcc) |
| **Version** | 11.4.0 |
| **Vendor** | Free Software Foundation |
| **Purpose** | C compiler for ARM Cortex-M4 target |
| **Classification** | T3 (generates executable code) |

## 2. Tool Qualification Method

**Method**: Comparison with Reference Compiler (IAR EWARM 9.20)

**Approach**:
1. Compile reference test suite with gcc and IAR
2. Compare generated assembly code
3. Execute on target hardware, compare outputs
4. Verify identical behavior

## 3. Qualification Test Suite

- Test suite: EN 50128 C Compiler Validation Suite (50 test cases)
- Coverage: All C language constructs used in project (no VLAs, no dynamic memory, no recursion)
- Test execution: ARM Cortex-M4 target board

## 4. Qualification Results

| Test Case | gcc Output | IAR Output | Match | Status |
|-----------|-----------|-----------|-------|--------|
| TC-001: Integer arithmetic | 0x1234 | 0x1234 | ✓ | PASS |
| TC-002: Pointer arithmetic | 0x2000 | 0x2000 | ✓ | PASS |
| ... | ... | ... | ... | ... |
| TC-050: Interrupt handling | ISR called | ISR called | ✓ | PASS |

**Overall Result**: PASS (50/50 test cases passed)

## 5. Tool Configuration

```bash
# Compiler flags used
arm-none-eabi-gcc \
    -mcpu=cortex-m4 \
    -mthumb \
    -std=c11 \
    -O2 \
    -Wall -Wextra -Werror \
    -fno-common \
    -ffunction-sections \
    -fdata-sections
```

## 6. Tool Qualification Conclusion

**Qualified**: gcc 11.4.0 is QUALIFIED for use in SIL 3 railway door controller project.

**Valid Until**: 2027-03-31 (1 year)

**Qualification Approval**:
- Verifier: Carol White, 2026-03-15
- Assessor: Frank Black, 2026-03-16
```

---

## Pre-Release Audit

### Pre-Release Audit Checklist (SIL 3-4 MANDATORY)

**EN 50128 Reference**: Section 7.7 (Validation), Section 6.5.4.5 (QA verification)

#### 1. Lifecycle Completeness

| Check | Evidence | Status | Notes |
|-------|----------|--------|-------|
| All lifecycle phases complete (Phase 1-7)? | LIFECYCLE_STATE.md | ☐ OK ☐ NC | |
| All phase gates approved? | Phase gate records | ☐ OK ☐ NC | |
| All deliverables approved per Annex C? | Deliverable list | ☐ OK ☐ NC | |

---

#### 2. Verification Completeness (SIL 3-4 MANDATORY)

| Check | Evidence | Status | Notes |
|-------|----------|--------|-------|
| Verification Report complete and approved? | DOC-VER-REP-001 | ☐ OK ☐ NC | |
| Static analysis complete (zero mandatory violations)? | Cppcheck reports | ☐ OK ☐ NC | |
| Complexity within limits (CCN ≤ 10 for SIL 3-4)? | Lizard reports | ☐ OK ☐ NC | |
| Coverage requirements met (100% for SIL 3-4)? | gcov/lcov reports | ☐ OK ☐ NC | |
| Traceability 100% (no orphan requirements)? | Traceability reports | ☐ OK ☐ NC | |

---

#### 3. Validation Completeness (SIL 3-4 MANDATORY)

| Check | Evidence | Status | Notes |
|-------|----------|--------|-------|
| Validation Report complete and approved? | DOC-VAL-REP-001 | ☐ OK ☐ NC | |
| System tests complete and passed? | Test reports | ☐ OK ☐ NC | |
| Acceptance tests complete and passed? | Acceptance cert | ☐ OK ☐ NC | |
| Customer approval obtained? | Signed certificate | ☐ OK ☐ NC | |

---

#### 4. Defect Status

| Check | Evidence | Status | Notes |
|-------|----------|--------|-------|
| No open Critical defects? | Defect tracking system | ☐ OK ☐ NC | |
| No open Major defects? | Defect tracking system | ☐ OK ☐ NC | |
| All Minor defects documented for next release? | Defect backlog | ☐ OK ☐ NC | |

---

#### 5. Safety Case (SIL 2+ MANDATORY)

| Check | Evidence | Status | Notes |
|-------|----------|--------|-------|
| Hazard Log complete? | Hazard Log | ☐ OK ☐ NC | |
| FMEA complete? | FMEA report | ☐ OK ☐ NC | |
| FTA complete (if applicable)? | FTA report | ☐ OK ☐ NC | |
| Safety Case complete? | Safety Case | ☐ OK ☐ NC | |

---

#### 6. Assessment (SIL 3-4 MANDATORY)

| Check | Evidence | Status | Notes |
|-------|----------|--------|-------|
| Assessment Report complete? | DOC-ASS-REP-001 | ☐ OK ☐ NC | |
| Assessor approval obtained? | Signed assessment | ☐ OK ☐ NC | |
| All assessment findings addressed? | Finding closure records | ☐ OK ☐ NC | |

---

#### 7. Configuration Management

| Check | Evidence | Status | Notes |
|-------|----------|--------|-------|
| Release baseline created and tagged? | Git tag | ☐ OK ☐ NC | |
| Release notes complete? | Release notes | ☐ OK ☐ NC | |
| All artifacts in baseline? | Baseline manifest | ☐ OK ☐ NC | |

---

### Pre-Release Audit Decision

**Decision Criteria**:
- **APPROVE FOR RELEASE**: All checks OK, zero non-conformances
- **CONDITIONAL APPROVAL**: Minor non-conformances only, corrective actions planned
- **REJECT RELEASE**: Critical or Major non-conformances, must be fixed before release

**Pre-Release Audit Report**: See [Audit Report Generation](#audit-report-generation)

---

## Audit Execution

### Opening Meeting

**Purpose**: Introduce audit scope, process, and expectations

**Agenda** (30 minutes):
1. Introductions (audit team + project team)
2. Audit objectives and scope
3. Audit schedule and activities
4. Evidence required
5. Finding classification (Non-Conformance, Observation, Best Practice)
6. Closing meeting schedule
7. Q&A

---

### Audit Evidence Collection

**Document Review**:
- Read deliverables (SRS, SAS, SDS, etc.)
- Check template compliance
- Verify traceability
- Check review and approval status

**Automated Checks**:
```bash
# Run all audit checks
./tools/audit_checks.sh --sil 3 --output audit_evidence/

# Includes:
# - Document template compliance (document_checker.py)
# - Traceability validation (workspace.py trace validate)
# - MISRA C compliance (cppcheck)
# - Complexity analysis (lizard)
# - Coverage analysis (gcov/lcov)
```

**Interviews**:
- Interview project team members
- Ask open-ended questions
- Verify understanding of EN 50128 process
- Verify roles and responsibilities

**Observations**:
- Observe review meetings
- Observe phase gate meetings
- Observe configuration management process

---

### Finding Documentation

**Finding Classification**:
| Type | Definition | Action Required |
|------|-----------|-----------------|
| **Non-Conformance (Critical)** | Violation of EN 50128 MANDATORY requirement | **MUST FIX** before release |
| **Non-Conformance (Major)** | Violation of EN 50128 Highly Recommended requirement | **SHOULD FIX** before release |
| **Non-Conformance (Minor)** | Violation of EN 50128 Recommended requirement | **MAY DEFER** to next release |
| **Observation** | Potential issue, not a violation | Consider improvement |
| **Best Practice** | Exceeds EN 50128 requirements | Document for other projects |

**Finding Template**:
```markdown
## Finding: AUD-2026-Q1-001-F01

### Finding Information

| Field | Value |
|-------|-------|
| **Finding ID** | AUD-2026-Q1-001-F01 |
| **Type** | Non-Conformance (Critical) |
| **Area** | Traceability |
| **Found By** | Eve Green (Lead Auditor) |
| **Date** | 2026-04-11 |

### Observation

3 requirements (REQ-DOOR-012, REQ-DOOR-015, REQ-DOOR-018) have no design elements traced to them.

**Evidence**:
```bash
workspace.py trace validate --phase design --sil 3
# Output: Traceability coverage: 92% (37/40 requirements traced)
# Missing: REQ-DOOR-012, REQ-DOOR-015, REQ-DOOR-018
```

### EN 50128 Reference

**Section 6.5.4.5(d)**: "Traceability of all items to and from requirements" (MANDATORY SIL 3-4)

**Table A.9 Technique 7**: Traceability (MANDATORY SIL 3-4)

### Impact

- Requirements not implemented (functionality missing)
- Validation cannot proceed (no tests for missing requirements)
- Risk of customer rejection

### Corrective Action Required

1. Design team (DES): Add design elements for REQ-DOOR-012, REQ-DOOR-015, REQ-DOOR-018
2. Update Software Design Specification (SDS) with new design elements
3. Update traceability matrix (workspace.py trace create)
4. Re-validate traceability (workspace.py trace validate must show 100%)

### Assignment

- **Assigned To**: Alice Designer (DES)
- **Due Date**: 2026-04-15
- **Follow-up Audit**: 2026-04-18

### Status

☐ Open  
☐ In Progress  
☐ Resolved  
☐ Verified  
☐ Closed
```

---

### Closing Meeting

**Purpose**: Present audit findings and corrective actions

**Agenda** (60 minutes):
1. Audit summary (scope, activities performed)
2. Finding presentation (Critical → Major → Minor)
3. Corrective action discussion (assignments, due dates)
4. Follow-up audit schedule
5. Q&A
6. Audit closure criteria

**Closing Meeting Report**: Summarize findings, get project team acknowledgment

---

## Finding Management

### Finding Lifecycle

```
Finding Identified (during audit)
          ↓
Finding Documented (finding report)
          ↓
Finding Presented (closing meeting)
          ↓
Corrective Action Assigned (responsible party, due date)
          ↓
Corrective Action Implemented (by assigned party)
          ↓
Corrective Action Verified (follow-up audit)
          ↓
Finding Closed (QA approval)
```

---

### Finding Tracking

**Tool**: `workspace.py wf` (workflow management)

**Usage**:
```bash
# Log audit finding
workspace.py wf log-finding \
    --audit-id AUD-2026-Q1-001 \
    --finding-id F01 \
    --type non-conformance \
    --severity critical \
    --area traceability \
    --description "3 requirements not traced to design" \
    --assigned-to "Alice Designer" \
    --due-date 2026-04-15

# Update finding status
workspace.py wf update-finding \
    --finding-id AUD-2026-Q1-001-F01 \
    --status in-progress \
    --comments "Design elements added for REQ-DOOR-012, REQ-DOOR-015. Working on REQ-DOOR-018."

# Verify finding resolved
workspace.py wf verify-finding \
    --finding-id AUD-2026-Q1-001-F01 \
    --verified-by "Eve Green (QA)" \
    --verification-date 2026-04-18 \
    --verification-evidence "workspace.py trace validate shows 100% coverage"

# Close finding
workspace.py wf close-finding \
    --finding-id AUD-2026-Q1-001-F01 \
    --closed-by "Eve Green (QA)" \
    --closed-date 2026-04-20
```

---

## Corrective Action Tracking

### Corrective Action Plan (CAP)

**Contents**:
1. Finding ID and description
2. Root cause analysis
3. Corrective action (fix the issue)
4. Preventive action (prevent recurrence)
5. Responsible party and due date
6. Verification method

**Example CAP**:
```markdown
# Corrective Action Plan: AUD-2026-Q1-001-F01

## Finding

**Finding ID**: AUD-2026-Q1-001-F01  
**Description**: 3 requirements not traced to design

## Root Cause Analysis

**Root Cause**: Design phase started before all requirements finalized. Requirements REQ-DOOR-012, REQ-DOOR-015, REQ-DOOR-018 added during design phase but not incorporated into design.

**Contributing Factors**:
- Change control process not followed (requirements added without CR)
- Traceability not validated before implementation phase

## Corrective Action

1. Add design elements for REQ-DOOR-012, REQ-DOOR-015, REQ-DOOR-018
2. Update Software Design Specification (SDS) to v1.2
3. Update traceability matrix (workspace.py trace create)
4. Re-validate traceability (workspace.py trace validate)

**Responsible**: Alice Designer (DES)  
**Due Date**: 2026-04-15

## Preventive Action

1. Enforce change control: All requirement changes MUST go through CR process
2. Implement traceability validation as phase gate criterion (COD to enforce)
3. Train team on traceability management (workspace.py trace commands)

**Responsible**: PM + COD  
**Due Date**: 2026-04-30

## Verification Method

- Design elements added: Verify in SDS v1.2 Section 4
- Traceability updated: Run `workspace.py trace validate --phase design --sil 3` → expect 100%
- Change control enforced: Audit CR log next month

## Status

☐ Open  
☐ In Progress  
☐ Resolved  
☐ Verified  
☐ Closed
```

---

## Audit Report Generation

### Audit Report Template

**File**: `DOC-QUA-AUDIT-NNN.md`

**Contents**:
1. **Executive Summary**: Audit outcome, key findings, recommendations
2. **Audit Information**: Audit ID, type, scope, dates, team
3. **Audit Activities**: What was reviewed, who was interviewed
4. **Findings**: Non-conformances, observations, best practices
5. **Corrective Action Plan**: Assignments, due dates, verification
6. **Conclusion**: Approve / Conditional / Reject
7. **Follow-up Audit**: Date, scope

**Example Audit Report**: See quality-assurance-workflow.md for full example

---

## Tool Integration

### Workflow Integration

**Log Audit**:
```bash
# Create audit record
workspace.py wf create-audit \
    --audit-id AUD-2026-Q1-001 \
    --type process-compliance \
    --project "Railway Door Controller" \
    --sil 3 \
    --start-date 2026-04-10 \
    --end-date 2026-04-12 \
    --lead-auditor "Eve Green"
```

**Automated Audit Checks**:
```bash
# Run all audit checks in one script
./tools/run_audit_checks.sh \
    --audit-id AUD-2026-Q1-001 \
    --sil 3 \
    --output audit_evidence/

# Script includes:
# - Deliverable inventory
# - Document template compliance
# - Traceability validation
# - MISRA C compliance
# - Complexity analysis
# - Coverage analysis
# - Configuration management check
```

---

## SIL-Specific Requirements

### Quality Audit Requirements by SIL

| Requirement | SIL 0-1 | SIL 2 | SIL 3-4 |
|------------|---------|-------|---------|
| **Process Compliance Audit** | Optional | Recommended (quarterly) | **MANDATORY** (monthly) |
| **Artifact Audit** | Optional | Recommended (per phase) | **MANDATORY** (per phase) |
| **Tool Qualification Audit** | Optional | Recommended (T2/T3) | **MANDATORY** (T2/T3) |
| **Pre-Release Audit** | Optional | Highly Recommended | **MANDATORY** |
| **Independent Auditor** | Recommended | Highly Recommended | **MANDATORY** (Assessor) |
| **Audit Report** | Recommended | Highly Recommended | **MANDATORY** |
| **Corrective Action Tracking** | Recommended | Highly Recommended | **MANDATORY** |

---

## Example Audit Scenarios

### Scenario 1: Process Audit Finds Phase Gate Violation (Critical NC)

**Context**: SIL 3 railway door controller, Q1 2026 audit

**Finding**: Implementation phase started before design phase gate approval

**Evidence**: Git log shows code commits starting 2026-03-10, but LIFECYCLE_STATE.md shows design gate approved 2026-03-15

**Impact**: Risk of implementing unapproved design, potential rework

**Corrective Action**: Stop out-of-sequence activities, enforce phase gates via COD

**Result**: Process improved, COD enforces gates strictly

---

### Scenario 2: Artifact Audit Finds Missing Deliverable (Major NC)

**Context**: SIL 3 speed controller, Phase 5 audit

**Finding**: Software Verification Plan (SVP) not created (MANDATORY SIL 3-4)

**Evidence**: Deliverable DOC-VER-PLAN-001 missing, not in Git repository

**Impact**: Verification activities not planned, risk of inadequate verification

**Corrective Action**: VER creates SVP, submit for QA review

**Result**: SVP created and approved, verification planned

---

### Scenario 3: Tool Audit Finds Unqualified T3 Tool (Critical NC)

**Context**: SIL 3 brake controller, tool qualification audit

**Finding**: gcc compiler (T3 tool) not qualified

**Evidence**: No Tool Qualification Report for gcc 11.4.0

**Impact**: Compiler may generate incorrect code, safety risk

**Corrective Action**: VER creates Tool Qualification Report for gcc

**Result**: gcc qualified, Tool Qualification Report approved

---

### Scenario 4: Pre-Release Audit Approves Release (OK)

**Context**: SIL 3 door controller, pre-release audit before deployment

**Findings**: Zero non-conformances, all checklist items OK

**Evidence**:
- All deliverables complete and approved
- Traceability 100%
- Coverage 100% (statement, branch, condition)
- MISRA C compliant (zero mandatory violations)
- All defects closed
- Assessor approval obtained

**Decision**: APPROVE FOR RELEASE

**Result**: Software deployed to production

---

## 15. References

- EN 50128:2011 Section 6.5 (Software Quality Assurance)
- EN 50128:2011 §5.1.2.4–§5.1.2.7, Annex B Table B.8 (Assessor Role)
- EN 50128:2011 Annex B (Tool Classification and Qualification)
- EN 50128:2011 Annex C (Document Control Summary - Table C.1)
- EN ISO 9001:2015 Section 9.2 (Internal Audit)
- ISO/IEC 90003:2014 (Software Engineering - Guidelines for ISO 9001)
- IEEE 1028-2008 (Standard for Software Reviews and Audits)
