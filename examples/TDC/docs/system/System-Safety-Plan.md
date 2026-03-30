# System Safety Plan

## Document Control

| Property | Value |
|----------|-------|
| **Document ID** | DOC-TDC-SSP-SYS-001 |
| **Project** | TDC — Train Door Control |
| **System** | Train Door Control System (TDCS) |
| **Version** | 1.0 |
| **Status** | APPROVED — System Input |
| **Date** | 2026-03-27 |
| **Prepared by** | COD (generate-system) |
| **Standard** | EN 50126:2017, EN 50128:2011, EN 50129:2018 |
| **SIL Level** | SIL 3 |

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Safety Manager | TBD | ___________ | 2026-03-27 |
| Project Manager | TBD | ___________ | — |
| Safety Authority | TBD | ___________ | — |

---

## 1. Introduction

### 1.1 Purpose

This System Safety Plan (SSP) defines the safety management activities, safety analysis methods, and safety evidence requirements for the Train Door Control System (TDCS). It establishes the framework for achieving and demonstrating SIL 3 safety integrity for the software component in accordance with EN 50128:2011 and EN 50126:2017.

### 1.2 Scope

This SSP covers:
- Safety organisation and responsibilities
- Safety lifecycle activities
- Hazard management process
- Safety analysis techniques (FMEA, FTA)
- Safety verification and validation requirements
- Independent Safety Assessment requirements
- Safety evidence requirements for the EN 50129 Safety Case

### 1.3 Relationship to Software Safety

The software component of the TDCS is subject to:
- **EN 50128:2011** at **SIL 3** for all safety-critical software modules (DSM, SPM, OBD, TCI, FMG, HAL)
- **EN 50128:2011** at **SIL 1–2** for non-safety-critical software modules (DGN)
- All SIL 3 mandatory techniques per EN 50128 Annex A (Tables A.2–A.21)

---

## 2. Safety Organisation

### 2.1 Safety Roles and Responsibilities

| Role | Responsibility | Independence Required |
|------|---------------|----------------------|
| Safety Manager | Overall safety management; maintains Safety Case; approves safety deliverables | No |
| System Safety Engineer (SAF) | Hazard analysis (FMEA, FTA); safety requirements; hazard log maintenance | No |
| Software Safety Engineer | Implements safety requirements in software design; reviews safety constraints | No |
| Independent Safety Assessor (ISA) | Independent review of all safety evidence; provides assessment report | **YES — Mandatory SIL 3 (§6.4.1.1)** |
| Software Verifier (VER) | Independent software verification; static analysis; coverage verification | **YES — Mandatory SIL 3** |
| Software Validator (VAL) | Independent software validation; system-level acceptance testing | **YES — Mandatory SIL 3** |

### 2.2 Independence Requirements

Per EN 50128:2011 §5.1.2.4–§5.1.2.7 and §6.4.1.1:
- The **ISA** SHALL be independent of the development organisation and SHALL NOT report to the Project Manager
- The **VER** SHALL be independent from the Designer and Implementer (mandatory SIL 3)
- The **VAL** SHALL NOT report to the Project Manager (mandatory SIL 3)
- The **VMGR** (V&V Manager) SHALL be independent of COD and PM

---

## 3. Safety Lifecycle Activities

### 3.1 Lifecycle Phase Mapping

| Phase | Safety Activity | Deliverable |
|-------|----------------|------------|
| Phase 0 — Initialization | Establish safety context; define SIL | This SSP |
| Phase 1 — Planning | Create Software Quality Assurance Plan (SQAP) with safety criteria | SQAP |
| Phase 2 — Requirements | Software hazard analysis; derive SW safety requirements from SYS hazards | SRS + Hazard Log |
| Phase 3 — Design | FMEA at software component level; safety architecture review | SAS + FMEA-Worksheet |
| Phase 4 — Component Design | Safety review of component design; verify safety constraints | Component Design Spec |
| Phase 5 — Implementation | MISRA C:2012 compliance; static analysis; 100% coverage | Verification Report |
| Phase 6 — Integration | Integration-level fault injection; safety function testing | Integration Test Report |
| Phase 7 — Validation | System-level safety function validation; performance testing | Validation Report |
| Phase 8 — Assessment | ISA reviews all safety evidence; issues Assessment Report | Assessment Report |
| Phase 9 — Deployment | Safety release approval; deployment records | Release Package |

### 3.2 Safety Analysis Methods

| Method | Phase | Standard Reference | Required for SIL 3? |
|--------|-------|------------------|---------------------|
| FMEA (Failure Mode and Effects Analysis) | 2, 3 | EN 50128 Table A.8 | HR (Highly Recommended) |
| FTA (Fault Tree Analysis) | 2, 3 | EN 50128 Table A.8 | HR |
| Hazard and Operability Study (HAZOP) | 2 | EN 50128 Table A.8 | R |
| Cause-Consequence Analysis | 3 | EN 50128 Table A.8 | R |

---

## 4. Hazard Management Process

### 4.1 Hazard Log

A Hazard Log SHALL be maintained throughout the lifecycle (Phase 2 onwards). It shall contain:
- Hazard ID, description, severity, frequency, risk level
- SIL allocation per hazard
- Mitigating safety function (SF reference)
- Software safety requirements derived from hazard
- Verification evidence (test case IDs confirming mitigation)
- Status (Open / Mitigated / Closed)

### 4.2 Hazard-to-Requirement Traceability

Each identified system hazard (HAZ-001 to HAZ-009) SHALL have:
1. A corresponding **system safety function** (SF-001 to SF-007)
2. One or more **software safety requirements** in the SRS (Phase 2)
3. **Verification evidence** (test results) in the Validation Report (Phase 7)
4. Formal closure sign-off by Safety Manager before Phase 8

### 4.3 Hazard Status at Project Initialization

| Hazard ID | Status | SIL | Mitigating SF | SW Req Status |
|-----------|--------|-----|--------------|---------------|
| HAZ-001 | Open | SIL 3 | SF-002, SF-005 | Pending Phase 2 |
| HAZ-002 | Open | SIL 3 | SF-003 | Pending Phase 2 |
| HAZ-003 | Open | SIL 3 | SF-001 | Pending Phase 2 |
| HAZ-004 | Open | SIL 3 | SF-003 | Pending Phase 2 |
| HAZ-005 | Open | SIL 3 | SF-002, SF-004 | Pending Phase 2 |
| HAZ-006 | Open | SIL 2 | SF-007 | Pending Phase 2 |
| HAZ-007 | Open | SIL 1 | — | Pending Phase 2 |
| HAZ-008 | Open | SIL 2 | SF-006 | Pending Phase 2 |
| HAZ-009 | Open | SIL 2 | SF-004, SF-007 | Pending Phase 2 |

---

## 5. Safety Requirements

### 5.1 Software Safety Integrity Requirements

The software of the TDCS SHALL comply with EN 50128:2011 at the following SIL levels:

| Module | SIL | Rationale |
|--------|-----|-----------|
| DSM (Door State Machine) | SIL 3 | Implements SF-001, SF-002 — direct departure interlock |
| SPM (Speed Monitor) | SIL 3 | Implements SF-001 — speed interlock |
| OBD (Obstacle Detector) | SIL 3 | Implements SF-003 — obstacle detection and reversal |
| TCI (TCMS Interface) | SIL 3 | Safety-critical command/status channel |
| FMG (Fault Manager) | SIL 3 | Implements SF-004 — safe state management |
| HAL | SIL 3 | Direct hardware control; safety function execution |
| DGN (Diagnostics) | SIL 1 | Non-safety; logging only |

### 5.2 Mandatory Safety Techniques (EN 50128 Annex A — SIL 3)

The following techniques are **mandatory** for all SIL 3 software components:

| Technique | Table Reference | Application |
|-----------|----------------|-------------|
| Structured programming | A.4 | All modules |
| MISRA C:2012 | A.4 | All safety-critical modules |
| No dynamic memory allocation | A.4 | All modules |
| No recursion | A.4 | All safety-critical modules |
| Static analysis (Cppcheck, Clang) | A.19 | All modules |
| Cyclomatic complexity ≤ 10 | A.4 | All functions |
| 100% statement coverage | A.21 | All test suites |
| 100% branch coverage | A.21 | All test suites |
| 100% condition coverage (MC/DC) | A.21 | All test suites |
| Defensive programming | A.4 | All modules |
| Boundary value analysis | A.5 | All test specifications |
| Equivalence partitioning | A.5 | All test specifications |

---

## 6. Safety Verification and Validation Requirements

### 6.1 Verification Requirements (per phase)

| Phase | Verification Activity | Evidence Required |
|-------|--------------------|-------------------|
| Phase 2 | Review SRS against system hazards | QUA review report; VER checklist |
| Phase 3 | Review SAS/SDS against safety architecture constraints | QUA review report; FMEA worksheet |
| Phase 5 | Static analysis; MISRA compliance; coverage measurement | Verification Report Phase 5 |
| Phase 6 | Integration-level safety function testing | Verification Report Phase 6 |

### 6.2 Validation Requirements

| Activity | Requirement | Phase |
|---------|------------|-------|
| System-level safety function testing | All SF-001 to SF-007 tested with boundary conditions | Phase 7 |
| Performance testing | All timing requirements (Section 7.1 of SRS) validated under load | Phase 7 |
| Fault injection testing | Representative faults injected; safe state verified | Phase 7 |
| Acceptance testing | All SYS-FR-001 to SYS-FR-012 exercised | Phase 7 |

---

## 7. Independent Safety Assessment

### 7.1 ISA Requirement

Per EN 50128:2011 §6.4.1.1, an **Independent Safety Assessment is MANDATORY** for SIL 3.

The ISA SHALL:
- Be independent from the development organisation
- Have appropriate competence in railway safety software at SIL 3
- Review all safety-relevant deliverables
- Issue a formal Assessment Report stating assessment conclusion (Pass/Pass with conditions/Reject)

### 7.2 ISA Scope

The ISA SHALL review as a minimum:
1. This System Safety Plan
2. System Safety Requirements Specification (SSRS)
3. Software Requirements Specification (SRS — Phase 2)
4. Software Architecture Specification (SAS — Phase 3)
5. Source code (sample or complete)
6. Unit test reports and coverage data (Phase 5)
7. Integration test report (Phase 6)
8. Validation report (Phase 7)
9. SQAP and SCMP compliance evidence
10. Hazard log (all hazards closed)

### 7.3 ISA Deliverable

The ISA shall produce a **Software Assessment Report** (Phase 8) containing:
- Scope and basis of assessment
- Summary of evidence reviewed
- Findings, observations, and conditions
- Assessment conclusion
- ISA signature and independence declaration

---

## 8. Safety Case Structure

The EN 50129 Safety Case for the TDCS shall be structured as follows:

```
Safety Case (EN 50129)
├── System Definition (this SSP + SRS)
├── Hazard Analysis (Hazard Log + FMEA/FTA)
├── Safety Requirements (SSRS + SW SRS)
├── Safety Implementation Evidence
│   ├── Software (EN 50128 SIL 3 compliance evidence)
│   │   ├── Phase 1–5 deliverables
│   │   ├── Verification Reports (all phases)
│   │   └── Coverage and static analysis reports
│   └── Hardware (EN 50155 qualification certificates)
├── Validation Evidence
│   └── Validation Report (Phase 7)
├── Assessment Report (Phase 8)
└── Safety Declaration
```

---

*End of Document — DOC-TDC-SSP-SYS-001 v1.0*
