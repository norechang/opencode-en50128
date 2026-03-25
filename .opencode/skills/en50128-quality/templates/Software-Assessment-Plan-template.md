# Software Assessment Plan

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 §6.4.4.4-6.4.4.7  
**ANNEX C ITEM**: #45  
**NOTE**: Assessment is MANDATORY for SIL 1-4 (§6.4.1.1). SIL 0 exempt (§6.4.1.2) for ISO 9001-certified organisations.

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SAP-[YYYY]-[NNN] |
| **Version** | [X.Y] |
| **Date** | [YYYY-MM-DD] |
| **Project** | [Project Name] |
| **SIL Level** | [1 \| 2 \| 3 \| 4] |
| **Author** | [Name], Assessor (ASR) |
| **Reviewer** | [Name], VER |
| **Status** | [Draft \| Approved] |

## DOCUMENT CONTROL

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft |

---

## 1. Introduction

### 1.1 Purpose

This Software Assessment Plan (SAP) defines the approach, scope, and schedule for independent software assessment of [Project Name] in accordance with EN 50128:2011 Section 6.4.

### 1.2 Scope

This assessment covers software at SIL [X] level. The assessor is independent of all design and verification activities per §6.4.1.1.

### 1.3 Assessment Independence Declaration

Assessor [Name] declares independence from:
- Software development team (Designer, Implementer, Tester, Integrator)
- Software verification team (Verifier)
- Project management

### 1.4 Reference Documents

| Document ID | Title | Version |
|-------------|-------|---------|
| DOC-SQAP-YYYY-NNN | Software Quality Assurance Plan | X.Y |
| DOC-SVP-YYYY-NNN | Software Verification Plan | X.Y |
| DOC-SVaP-YYYY-NNN | Software Validation Plan | X.Y |
| STD-EN50128 | EN 50128:2011 Railway Applications | - |

---

## 2. Assessment Objectives

Per §6.4.4.5, the assessment shall:

| Objective | Reference | Status |
|-----------|-----------|--------|
| Assess suitability of lifecycle processes | §6.4.4.5(a) | [Planned] |
| Assess suitability of techniques and measures | §6.4.4.5(b) | [Planned] |
| Assess whether SIL requirements are met | §6.4.4.5(c) | [Planned] |
| Assess independence requirements are satisfied | §6.4.4.5(d) | [Planned] |
| Assess suitability of development documentation | §6.4.4.5(e) | [Planned] |

---

## 3. Assessment Scope and Deliverables Under Assessment

### 3.1 Documents Under Assessment

| Deliverable ID | Document | Phase | Assessment Activity |
|---------------|----------|-------|-------------------|
| DOC-001-SQAP | Software Quality Assurance Plan | Planning | Document review |
| DOC-002-QA-VER | QA Verification Report | Planning | Document review |
| DOC-003-SCMP | Software Configuration Management Plan | Planning | Document review |
| DOC-004-SVP | Software Verification Plan | Planning | Document review |
| DOC-005-SVaP | Software Validation Plan | Planning | Document review |
| DOC-006-SRS | Software Requirements Specification | Requirements | Document review |
| DOC-009-SAS | Software Architecture Specification | Architecture | Document review |
| DOC-018-SOURCE-CODE | Software Source Code | Implementation | Code sampling |
| DOC-025-VALIDATION-REPORT | Software Validation Report | Validation | Document review |
| [All other Annex C deliverables] | [Name] | [Phase] | Document review |

### 3.2 Processes Under Assessment

| Process | Reference | Assessment Method |
|---------|-----------|-------------------|
| Requirements process | §7.2 | Process audit |
| Design process | §7.3 | Process audit |
| Implementation process | §7.4-7.5 | Process audit + code sampling |
| Testing process | §7.4-7.7 | Process audit |
| Verification process | §6.2 | Independence check + report review |
| Validation process | §6.3 | Independence check + report review |
| Configuration management | §6.6 | Process audit |
| Quality assurance | §6.5 | Process audit |

---

## 4. Assessment Method

### 4.1 Document Reviews

Each mandatory deliverable will be reviewed for:
- Completeness against EN 50128 requirements
- Correctness and internal consistency
- Traceability (where required by SIL level)
- Independence compliance (where required)

### 4.2 Process Audits

Planned interviews and process observations:
- Requirements capture process (REQ team)
- Design review process (DES team)
- Code review process (IMP/VER teams)
- Testing process (TST team)
- V&V process (VER/VAL/VMGR)

### 4.3 Sampling

Code review: [X]% sample of all source files at SIL [X] level.

---

## 5. Assessment Schedule

| Milestone | Date | Activity |
|-----------|------|----------|
| Phase 1-2 review | [Date] | Planning and requirements deliverables |
| Phase 3-4 review | [Date] | Design deliverables |
| Phase 5-6 review | [Date] | Implementation, testing, integration deliverables |
| Phase 7 review | [Date] | Validation deliverables |
| Final assessment | [Date] | Conclude and issue Software Assessment Report |

---

## 6. Assessment Team

| Role | Name | Organization | Qualification |
|------|------|--------------|---------------|
| Lead Assessor | [Name] | [Organization] | [Qualification/Certification] |
| Deputy Assessor | [Name] | [Organization] | [Qualification/Certification] |

---

## 7. Assessment Outputs

This plan will result in:
- Software Assessment Report (DOC-SAR-YYYY-NNN) per §6.4.4.16-19
- Issue log (findings during assessment)
- Corrective action requests (where deficiencies found)

---

## 8. Escalation and Dispute Resolution

[Define process if project team disputes assessment findings]

---

**End of Software Assessment Plan**
