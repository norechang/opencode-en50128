# EN 50128 V-Model: Complete Phase-to-Document Mapping

**Standard**: EN 50128:2011 Railway Software  
**Date**: 2026-02-21  
**Purpose**: Complete reference of all lifecycle phases and their deliverable documents

---

## Quick Reference Table

| Phase | EN 50128 Section | Documents | Phase Definition File |
|-------|-----------------|-----------|----------------------|
| Phase 0: Initialization | Platform Extension | 1 document | N/A (COD internal) |
| Phase 1: Planning | 5, 6.5, 6.6 | 4 documents | N/A (manual setup) |
| Phase 2: Requirements | 7.2 | 3 documents | `phase-2-requirements.yaml` |
| Phase 3: Architecture & Design | 7.3 | 6 documents | `phase-3-architecture-design.yaml` |
| Phase 4: Component Design | 7.4 | 3 documents | `phase-4-component-design.yaml` |
| Phase 5: Implementation & Testing | 7.5 | 3 documents | `phase-5-implementation-testing.yaml` |
| Phase 6: Integration | 7.6 | 3 documents | `phase-6-integration.yaml` |
| Phase 7: Validation | 7.7 | 3 documents | `phase-7-validation.yaml` |
| Phase 8: Assessment | 6.4 | 1 document | Not yet created (SIL 3-4 only) |
| Phase 9: Deployment | 9.1 | Variable | Not yet created |

**Total Documents**: 27 mandatory documents (3 in Phase 1, 24 in Phases 2-7)

---

## Phase 0: Initialization (Platform Extension)

**Purpose**: Initialize lifecycle tracking and project structure  
**Owner**: Lifecycle Coordinator (COD)  
**Command**: `/cod plan --sil [0-4] --project [name]`

### Deliverables (1)

| # | Document Name | File Path | Owner | Notes |
|---|---------------|-----------|-------|-------|
| 1 | **LIFECYCLE_STATE.md** | `LIFECYCLE_STATE.md` | COD | Tracks project state, phase progress, deliverables |

**Key Points**:
- COD-managed file (DO NOT edit manually)
- Contains project info, phase history, deliverable status, approvals
- Updated automatically by COD during lifecycle operations

---

## Phase 1: Planning (EN 50128 Sections 5, 6.5, 6.6)

**Purpose**: Establish project organization, quality assurance, and configuration management  
**Primary Agents**: `/pm`, `/cm`, `/qua`  
**EN 50128 Reference**: Section 5.3.2.5 - "All activities during a phase SHALL be defined and planned"

### Deliverables (4 Mandatory)

| # | Document Name | File Path | Owner | EN 50128 Ref |
|---|---------------|-----------|-------|--------------|
| 1 | **Software Quality Assurance Plan (SQAP)** | `docs/plans/SQAP.md` | QUA | 6.5.4.2 |
| 2 | **Software Configuration Management Plan (SCMP)** | `docs/plans/SCMP.md` | CM | 6.6.4.1 |
| 3 | **Software Verification Plan (SVP)** | `docs/plans/SVP.md` | VER | 6.2.4.2 |
| 4 | **Software Validation Plan (SVaP)** | `docs/plans/SVaP.md` | VAL | 6.3.4.2 |

**Optional/Supporting**:
- Project Organization Chart
- Project Standards Document
- Tool Qualification Plan (if tools used)

**Phase Gate**: `/cod gate-check planning` (MANDATORY all SIL levels)

---

## Phase 2: Requirements (EN 50128 Section 7.2)

**Purpose**: Define complete, unambiguous software requirements  
**Primary Agent**: `/req` (Requirements Engineer)  
**Supporting Agents**: `/saf` (Safety), `/qua` (QA), `/ver` (Verifier)  
**Phase Definition**: `phase-2-requirements.yaml`

### Deliverables (3 Mandatory per EN 50128 Section 7.2.3)

| # | Document Name | File Path | Owner | EN 50128 Clause |
|---|---------------|-----------|-------|-----------------|
| 1 | **Software Requirements Specification** | `docs/Software-Requirements-Specification.md` | REQ | 7.2.4.1 |
| 2 | **Overall Software Test Specification** | `docs/test/Overall-Software-Test-Specification.md` | TST | 7.2.4.16 |
| 3 | **Software Requirements Verification Report** | `docs/reports/Software-Requirements-Verification-Report.md` | VER | 7.2.4.27 |

**Best Practice (Recommended)**:
- **Hazard Log** - `docs/Hazard-Log.md` - SAF (EN 50126 / EN 50129)

**Key Points**:
- Requirements Traceability Matrix (RTM) is **implicit** in Software Requirements Specification (not a separate document per EN 50128)
- Overall Software Test Specification created in Phase 2, **executed** in Phase 7 (V-Model)
- User approval REQUIRED for requirement establishment (via `/cod approve-requirement`)

**Phase Gate**: `/cod gate-check requirements` (MANDATORY all SIL levels)

---

## Phase 3: Architecture & Design (EN 50128 Section 7.3)

**Purpose**: Define software architecture, design, and interfaces  
**Primary Agent**: `/des` (Designer)  
**Supporting Agents**: `/saf` (Safety), `/qua` (QA), `/int` (Integrator), `/ver` (Verifier)  
**Phase Definition**: `phase-3-architecture-design.yaml`

### Deliverables (6 Mandatory per EN 50128 Section 7.3.3)

| # | Document Name | File Path | Owner | EN 50128 Clause |
|---|---------------|-----------|-------|-----------------|
| 1 | **Software Architecture Specification** | `docs/Software-Architecture-Specification.md` | DES | 7.3.4.1 |
| 2 | **Software Design Specification** | `docs/Software-Design-Specification.md` | DES | 7.3.4.20 |
| 3 | **Software Interface Specifications** | `docs/Software-Interface-Specifications.md` | DES | 7.3.4.18 |
| 4 | **Software Integration Test Specification** | `docs/test/Software-Integration-Test-Specification.md` | INT | 7.3.4.25 |
| 5 | **Software/Hardware Integration Test Specification** | `docs/test/Software-Hardware-Integration-Test-Specification.md` | INT | 7.3.4.33 |
| 6 | **Software Architecture and Design Verification Report** | `docs/reports/Software-Architecture-and-Design-Verification-Report.md` | VER | 7.3.4.40 |

**Important Naming Notes**:
- #3: **PLURAL** - "Software Interface Specification**s**" (per EN 50128 7.3.3 item 3)
- #5: Use forward slash **"/"** not hyphen - "Software/Hardware" (per EN 50128 7.3.3 item 5)
- #4 and #5: Test **Specifications** created in Phase 3, Test **Reports** created in Phase 6 (V-Model)

**Phase Gate**: `/cod gate-check architecture-design` (MANDATORY all SIL levels)

---

## Phase 4: Component Design (EN 50128 Section 7.4)

**Purpose**: Decompose design into components with detailed specifications  
**Primary Agents**: `/des` (Designer), `/tst` (Tester)  
**Supporting Agents**: `/qua` (QA), `/ver` (Verifier)  
**Phase Definition**: `phase-4-component-design.yaml`

### Deliverables (3 Mandatory per EN 50128 Section 7.4.3)

| # | Document Name | File Path | Owner | EN 50128 Clause |
|---|---------------|-----------|-------|-----------------|
| 1 | **Software Component Design Specification** | `docs/Software-Component-Design-Specification.md` | DES | 7.4.4.1 |
| 2 | **Software Component Test Specification** | `docs/test/Software-Component-Test-Specification.md` | TST | 7.4.4.7 |
| 3 | **Software Component Design Verification Report** | `docs/reports/Software-Component-Design-Verification-Report.md` | VER | 7.4.4.11 |

**Key Points**:
- All names **singular** (one specification covers all components)
- #2: Test **Specification** created in Phase 4, Test **Report** created in Phase 5 (V-Model)
- Defines unit-level designs, algorithms, data structures

**Phase Gate**: `/cod gate-check component-design` (MANDATORY all SIL levels)

---

## Phase 5: Implementation & Testing (EN 50128 Section 7.5)

**Purpose**: Implement source code and execute unit tests  
**Primary Agents**: `/imp` (Implementer), `/tst` (Tester)  
**Supporting Agents**: `/qua` (QA), `/ver` (Verifier)  
**Phase Definition**: `phase-5-implementation-testing.yaml`

### Deliverables (3 Mandatory per EN 50128 Section 7.5.3)

| # | Document Name | File Path | Owner | EN 50128 Clause |
|---|---------------|-----------|-------|-----------------|
| 1 | **Software Source Code and supporting documentation** | `src/` + docs | IMP | 7.5.4.1 |
| 2 | **Software Component Test Report** | `docs/reports/Software-Component-Test-Report.md` | TST | 7.5.4.5 |
| 3 | **Software Source Code Verification Report** | `docs/reports/Software-Source-Code-Verification-Report.md` | VER | 7.5.4.8 |

**Important Naming Notes**:
- #1: "Software Source Code" (not just "Source Code")
- #1: Lowercase **"and"** - "and supporting documentation" (per EN 50128 7.5.3 item 1)
- #2: Test **Report** (execution results), not "Specification"

**Key Requirements**:
- MISRA C:2012 compliance (ZERO mandatory violations for SIL 2+)
- Static allocation only (no `malloc`/`free` for SIL 2+)
- Cyclomatic complexity ≤10 (SIL 3-4), ≤15 (SIL 2)
- Coverage: 100% statement/branch/MC/DC (SIL 3-4)

**Phase Gate**: `/cod gate-check implementation-testing` (MANDATORY all SIL levels)

---

## Phase 6: Integration (EN 50128 Section 7.6)

**Purpose**: Integrate components and test software-hardware integration  
**Primary Agent**: `/int` (Integrator)  
**Supporting Agents**: `/tst` (Tester), `/qua` (QA), `/ver` (Verifier)  
**Phase Definition**: `phase-6-integration.yaml`

### Deliverables (3 Mandatory per EN 50128 Section 7.6.3)

| # | Document Name | File Path | Owner | EN 50128 Clause |
|---|---------------|-----------|-------|-----------------|
| 1 | **Software Integration Test Report** | `docs/reports/Software-Integration-Test-Report.md` | INT | 7.6.4.3 |
| 2 | **Software/Hardware Integration Test Report** | `docs/reports/Software-Hardware-Integration-Test-Report.md` | INT | 7.6.4.7 |
| 3 | **Software Integration Verification Report** | `docs/reports/Software-Integration-Verification-Report.md` | VER | 7.6.4.11 |

**Important Naming Notes**:
- #2: Use forward slash **"/"** not hyphen - "Software/Hardware"
- #1 and #2: Test **Reports** (execution of specs created in Phase 3)

**V-Model Correspondence**:
- Software Integration Test Specification (Phase 3) → Software Integration Test Report (Phase 6)
- Software/Hardware Integration Test Specification (Phase 3) → Software/Hardware Integration Test Report (Phase 6)

**Phase Gate**: `/cod gate-check integration` (MANDATORY all SIL levels)

---

## Phase 7: Validation (EN 50128 Section 7.7)

**Purpose**: Overall software testing and validation for fitness of use  
**Primary Agents**: `/tst` (Tester), `/val` (Validator)  
**Supporting Agents**: `/qua` (QA), `/ver` (Verifier)  
**Phase Definition**: `phase-7-validation.yaml`

### Deliverables (3 Mandatory per EN 50128 Section 7.7.3)

| # | Document Name | File Path | Owner | EN 50128 Clause |
|---|---------------|-----------|-------|-----------------|
| 1 | **Overall Software Test Report** | `docs/reports/Overall-Software-Test-Report.md` | TST | 7.7.4.1 |
| 2 | **Software Validation Report** | `docs/reports/Software-Validation-Report.md` | VAL | 7.7.4.6 |
| 3 | **Release Note** | `docs/Release-Note.md` | PM/VAL | 7.7.4.12 |

**Important Naming Notes**:
- #3: "Release Note" (SINGULAR per EN 50128 7.7.3 item 3), not "Release Notes"

**V-Model Correspondence**:
- Overall Software Test Specification (Phase 2) → Overall Software Test Report (Phase 7)

**Critical Requirements (SIL 3-4)**:
- Independent validator MANDATORY (does NOT report to Project Manager)
- Performance Testing MANDATORY (Table A.7)
- Functional/Black-box Testing MANDATORY (Table A.7)
- Customer acceptance REQUIRED

**Phase Gate**: `/cod gate-check validation` (MANDATORY all SIL levels)

---

## Phase 8: Assessment (EN 50128 Section 6.4)

**Purpose**: Independent safety assessment (SIL 3-4 ONLY)  
**Primary Agent**: Assessor (independent)  
**Phase Definition**: Not yet created

### Deliverables (1 Mandatory per EN 50128 Section 6.4.4)

| # | Document Name | File Path | Owner | EN 50128 Clause |
|---|---------------|-----------|-------|-----------------|
| 1 | **Software Assessment Report** | `docs/reports/Software-Assessment-Report.md` | Assessor | 6.4.4.3 |

**Key Points**:
- **MANDATORY for SIL 3-4 ONLY**
- Assessor MUST be independent (separate organization recommended)
- Assessor has NO organizational relationship with PM or development team
- Assessment covers all lifecycle phases and deliverables

**Phase Gate**: `/cod gate-check assessment` (MANDATORY SIL 3-4 only)

---

## Phase 9: Deployment (EN 50128 Section 9.1)

**Purpose**: Deploy software to operational environment  
**Primary Agents**: `/pm` (Project Manager), `/cm` (Configuration Manager)  
**Phase Definition**: Not yet created

### Deliverables (Variable)

| # | Document Name | File Path | Owner | Notes |
|---|---------------|-----------|-------|-------|
| 1 | **Deployment Plan** | `docs/Deployment-Plan.md` | PM | Installation procedures |
| 2 | **Installation Report** | `docs/reports/Installation-Report.md` | PM | Deployment verification |
| 3 | **Software Baseline** | Configuration items | CM | Final release baseline |

**Key Points**:
- Deployment procedures per EN 50128 Section 9.1
- Installation verification and acceptance
- Handover to operations and maintenance

---

## Summary Statistics

### Documents by Phase

| Phase | Mandatory Documents | Optional/Supporting | Total |
|-------|---------------------|---------------------|-------|
| Phase 0: Initialization | 1 | 0 | 1 |
| Phase 1: Planning | 4 | 3+ | 7+ |
| Phase 2: Requirements | 3 | 1 | 4 |
| Phase 3: Architecture & Design | 6 | 0 | 6 |
| Phase 4: Component Design | 3 | 0 | 3 |
| Phase 5: Implementation & Testing | 3 | 0 | 3 |
| Phase 6: Integration | 3 | 0 | 3 |
| Phase 7: Validation | 3 | 0 | 3 |
| Phase 8: Assessment (SIL 3-4) | 1 | 0 | 1 |
| Phase 9: Deployment | 3 | Variable | 3+ |
| **TOTAL** | **30** | **4+** | **34+** |

### Documents by Type

| Type | Count | Phases |
|------|-------|--------|
| Specifications | 10 | 2, 3, 4 |
| Test Specifications | 4 | 2, 3, 4 |
| Test Reports | 5 | 5, 6, 7 |
| Verification Reports | 7 | 2, 3, 4, 5, 6 |
| Validation Reports | 1 | 7 |
| Assessment Reports | 1 | 8 |
| Plans | 4 | 1 |
| Other (Release Note, etc.) | 4 | 0, 7, 9 |

### V-Model Correspondence (Specification → Report)

| Specification (Left side) | Phase | Report (Right side) | Phase |
|---------------------------|-------|---------------------|-------|
| Overall Software Test Specification | 2 | Overall Software Test Report | 7 |
| Software Integration Test Specification | 3 | Software Integration Test Report | 6 |
| Software/Hardware Integration Test Spec | 3 | Software/Hardware Integration Test Report | 6 |
| Software Component Test Specification | 4 | Software Component Test Report | 5 |

---

## Phase Definition Files Status

| Phase | YAML File | Status | Lines | Created |
|-------|-----------|--------|-------|---------|
| Phase 0 | N/A | COD internal | - | - |
| Phase 1 | N/A | Manual setup | - | - |
| Phase 2 | `phase-2-requirements.yaml` | ✅ Complete | ~110 | 2026-02-19 |
| Phase 3 | `phase-3-architecture-design.yaml` | ✅ Complete | ~140 | 2026-02-20 |
| Phase 4 | `phase-4-component-design.yaml` | ✅ Complete | 91 | 2026-02-20 |
| Phase 5 | `phase-5-implementation-testing.yaml` | ✅ Complete | 115 | 2026-02-21 |
| Phase 6 | `phase-6-integration.yaml` | ✅ Complete | 97 | 2026-02-21 |
| Phase 7 | `phase-7-validation.yaml` | ✅ Complete | 127 | 2026-02-21 |
| Phase 8 | `phase-8-assessment.yaml` | ⏳ Pending | - | Future |
| Phase 9 | `phase-9-deployment.yaml` | ⏳ Pending | - | Future |

**Current Coverage**: 6 of 10 phases (60%) - **Phases 2-7 operational**

---

## Document Naming Conventions

### File Naming

**Format**: Use exact EN 50128 name with hyphens replacing spaces

Examples:
- ✅ `Software-Requirements-Specification.md`
- ✅ `Software-Architecture-Specification.md`
- ✅ `Software-Interface-Specifications.md` (PLURAL!)
- ✅ `Software-Hardware-Integration-Test-Report.md` (use hyphen in filename for "/")
- ❌ `SRS.md` (abbreviations NOT recommended)

### Document ID Format

**Format**: `DOC-<TYPE>-YYYY-NNN`

Examples:
- `DOC-SRS-2026-001` - Software Requirements Specification
- `DOC-SAS-2026-001` - Software Architecture Specification
- `DOC-COMPDES-2026-001` - Software Component Design Specification

---

## Quick Command Reference

### COD Lifecycle Commands

```bash
# Initialize project
/cod plan --sil 3 --project train_door_control

# Check phase gates
/cod gate-check planning
/cod gate-check requirements
/cod gate-check architecture-design
/cod gate-check component-design
/cod gate-check implementation-testing
/cod gate-check integration
/cod gate-check validation
/cod gate-check assessment  # SIL 3-4 only

# View lifecycle status
/cod status

# Approve requirement activities
/cod approve-requirement
```

### Phase Execution Commands

```bash
# Execute phases via Project Manager
/pm execute-phase requirements
/pm execute-phase architecture-design
/pm execute-phase component-design
/pm execute-phase implementation-testing
/pm execute-phase integration
/pm execute-phase validation
```

---

## References

- **EN 50128:2011**: Railway applications - Software for railway control and protection systems
- **Standard Location**: `std/EN50128-2011.md`
- **Deliverables Mapping**: `EN50128-DELIVERABLES-MAPPING.md`
- **Lifecycle Documentation**: `LIFECYCLE.md`
- **Agent Definitions**: `AGENTS.md`
- **Phase Definitions**: `.opencode/skills/en50128-project-management/phase-definitions/`

---

**Document Version**: 1.0  
**Last Updated**: 2026-02-21  
**Maintained By**: Platform Development Team
