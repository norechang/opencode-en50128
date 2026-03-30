# Train Door Control System - Documentation Overview

This document provides a complete overview of all project documentation, showing the relationship between system-level and software-level documents per EN 50128:2011.

---

## EN 50128 V-Model Documentation Flow

```
┌─────────────────────────────────────────────────────────────────────┐
│                    SYSTEM ENGINEERING PHASE                         │
│                    (External to Software Team)                      │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  INPUT DOCUMENTS (Per EN 50128 Section 7.2.2)                      │
│  Location: docs/system/                                            │
│                                                                     │
│  1. System Requirements Specification             569 lines        │
│     - 71 system requirements (SYS-REQ-xxx)                          │
│     - SIL 3 classification                                          │
│     - HW/SW allocation                                              │
│                                                                     │
│  2. System Safety Requirements Specification      508 lines        │
│     - 9 hazards (SYS-HAZ-xxx)                                       │
│     - 7 safety functions (SF-xxx)                                   │
│     - FMEA and FTA analysis                                         │
│     - Safety integrity requirements (SAFE-xxx)                      │
│                                                                     │
│  3. System Architecture Description               769 lines        │
│     - HW architecture (dual-channel, sensors)                       │
│     - SW architecture overview                                      │
│     - Safety architecture (2oo2, fail-safe)                         │
│     - Interfaces (CAN, MVB, I/O)                                    │
│                                                                     │
│  4. System Safety Plan                           1189 lines        │
│     - Safety organization and roles                                 │
│     - Safety lifecycle activities                                   │
│     - Verification and validation strategy                          │
│     - Independent safety assessment plan                            │
│                                                                     │
└──────────────────────────┬──────────────────────────────────────────┘
                           │
                           │ Inputs to Software Development
                           │
                           ▼
┌─────────────────────────────────────────────────────────────────────┐
│                   SOFTWARE ENGINEERING PHASE                        │
│                   (EN 50128 Lifecycle)                              │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  PHASE 1: PLANNING (EN 50128 Section 6)                            │
│  Location: docs/plans/                                             │
│                                                                     │
│  - Software Quality Assurance Plan (SQAP)                           │
│  - Software Configuration Management Plan (SCMP)                    │
│  - Software Verification Plan (SVP)                                 │
│  - Software Validation Plan (SVaP)                                  │
│                                                                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  PHASE 2: REQUIREMENTS (EN 50128 Section 7.2)                      │
│  Location: docs/                                                   │
│                                                                     │
│  - Software Requirements Specification           1880 lines ✅      │
│    - Functional requirements (SW-REQ-xxx)                           │
│    - Safety requirements (SW-SAFE-xxx)                              │
│    - Interface requirements                                         │
│    - Derived from 4 system input documents                          │
│                                                                     │
│  - Requirements Traceability Matrix               16201 bytes ✅    │
│    - Hazards → System Reqs → Software Reqs → Tests                  │
│                                                                     │
│  - Hazard Log                                    54566 bytes ✅    │
│    - 9 hazards with risk assessment                                 │
│    - Mitigation measures                                            │
│                                                                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  PHASE 3: ARCHITECTURE & DESIGN (EN 50128 Section 7.3)             │
│  Location: docs/                                                   │
│                                                                     │
│  - Software Architecture Specification           64987 bytes ✅    │
│    - Module decomposition                                           │
│    - Safety architecture                                            │
│    - Interfaces                                                     │
│    - Implements allocation from System Arch Description             │
│                                                                     │
│  - Software Design Specification                 (Planned)         │
│  - Software Interface Specifications             (Planned)         │
│                                                                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  PHASE 4: COMPONENT DESIGN (EN 50128 Section 7.4)                  │
│  - Software Component Design Specification        (Planned)        │
│  - Software Component Test Specification          (Planned)        │
│                                                                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  PHASE 5: IMPLEMENTATION & TESTING (EN 50128 Section 7.5)          │
│  Location: src/                                                    │
│                                                                     │
│  - Software Source Code                           (In Progress)    │
│  - Software Component Test Report                 (Planned)        │
│  - Software Source Code Verification Report       (Planned)        │
│                                                                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  PHASE 6: INTEGRATION (EN 50128 Section 7.6)                       │
│  - Software Integration Test Report               (Planned)        │
│  - Software/Hardware Integration Test Report      (Planned)        │
│  - Software Integration Verification Report       (Planned)        │
│                                                                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  PHASE 7: VALIDATION (EN 50128 Section 7.7)                        │
│  - Overall Software Test Report                   (Planned)        │
│  - Software Validation Report                     (Planned)        │
│  - Release Note                                   (Planned)        │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## Document Statistics

### System-Level Documents (4 documents, 3,294 lines)

| Document | Lines | Size | Status | Date |
|----------|-------|------|--------|------|
| System Requirements Specification | 569 | 22 KB | ✅ Approved Baseline v1.0 | 2026-02-10 |
| System Safety Requirements Specification | 508 | 25 KB | ✅ Approved Baseline v1.0 | 2026-02-10 |
| System Architecture Description | 769 | 42 KB | ✅ Approved Baseline v1.0 | 2026-02-10 |
| System Safety Plan | 1,189 | 55 KB | ✅ Approved Baseline v1.0 | 2026-02-10 |
| **System README** | 259 | 13 KB | ✅ Created | 2026-02-21 |
| **Total** | **3,294** | **157 KB** | | |

### Software-Level Documents (3 documents complete, multiple planned)

| Document | Lines/Size | Status | Date |
|----------|------------|--------|------|
| Software Requirements Specification | 1,880 lines / 75 KB | ✅ Complete | 2026-02-19 |
| Software Architecture Specification | 64,987 bytes / 65 KB | ✅ Complete | 2026-02-20 |
| Requirements Traceability Matrix | 16,201 bytes / 16 KB | ✅ Complete | 2026-02-19 |
| Hazard Log | 54,566 bytes / 55 KB | ✅ Complete | 2026-02-19 |
| Software Design Specification | - | ⏳ Planned | Phase 3 |
| Software Interface Specifications | - | ⏳ Planned | Phase 3 |
| Software Component Test Specification | - | ⏳ Planned | Phase 4 |
| Software Source Code | - | 🔄 In Progress | Phase 5 |

### Planning Documents (4 documents, all complete)

| Document | Status | Location |
|----------|--------|----------|
| Software Quality Assurance Plan (SQAP) | ✅ Complete | docs/plans/ |
| Software Configuration Management Plan (SCMP) | ✅ Complete | docs/plans/ |
| Software Verification Plan (SVP) | ✅ Complete | docs/plans/ |
| Software Validation Plan (SVaP) | ✅ Complete | docs/plans/ |

---

## Key Traceability Chains

### Hazard → System Requirement → Software Requirement

```
HAZ-001: Doors open while moving
    │
    ├─→ SYS-REQ-002: Door opening interlock (speed ≤ 5 km/h)
    │       │
    │       └─→ SW-REQ-010: Speed interlock logic
    │           SW-SAFE-001: Speed check before door enable
    │           SW-SAFE-002: 2oo2 speed sensor voting
    │
    ├─→ SYS-REQ-013: Maintain door locks when speed > 5 km/h
    │       │
    │       └─→ SW-REQ-015: Door lock control logic
    │           SW-SAFE-006: Lock verification
    │
    └─→ SAFE-SW-001: Software SIL 3 development
            │
            └─→ SQAP, SCMP, SVP, SVaP (planning documents)
                100% MC/DC coverage (testing)
```

### System Safety Function → Software Module

```
SF-001: Door Opening Interlock (SIL 3)
    │
    ├─→ System Architecture: Allocated to Software (Safety Kernel)
    │
    └─→ Software Architecture: Speed Interlock Module
            │
            ├─→ speed_interlock.c (implementation)
            ├─→ test_speed_interlock.c (unit tests)
            └─→ Coverage: 100% MC/DC (required for SIL 3)
```

---

## Document Directory Structure

```
train_door_control2/
├── docs/
│   ├── system/                                    # System-level inputs
│   │   ├── README.md                              # This overview
│   │   ├── System-Requirements-Specification.md
│   │   ├── System-Safety-Requirements-Specification.md
│   │   ├── System-Architecture-Description.md
│   │   └── System-Safety-Plan.md
│   │
│   ├── plans/                                     # Phase 1: Planning
│   │   ├── Software-Quality-Assurance-Plan.md
│   │   ├── Software-Configuration-Management-Plan.md
│   │   ├── Software-Verification-Plan.md
│   │   └── Software-Validation-Plan.md
│   │
│   ├── Software-Requirements-Specification.md     # Phase 2: Requirements
│   ├── Requirements-Traceability-Matrix.md
│   ├── Hazard-Log.md
│   │
│   ├── Software-Architecture-Specification.md     # Phase 3: Architecture
│   │
│   ├── config/                                    # Configuration
│   │   └── ...
│   │
│   ├── reports/                                   # Verification reports
│   │   └── ...
│   │
│   └── test/                                      # Test specifications
│       └── ...
│
├── src/                                           # Phase 5: Implementation
│   ├── main.c
│   ├── speed_interlock.c
│   ├── door_control.c
│   └── ...
│
├── LIFECYCLE_STATE.md                             # Project tracking
├── INTEGRATION_TEST_LOG.md
└── Makefile
```

---

## EN 50128 Compliance Summary

### Phase 1: Planning ✅ COMPLETE
- Software Quality Assurance Plan ✅
- Software Configuration Management Plan ✅
- Software Verification Plan ✅
- Software Validation Plan ✅

### Phase 2: Requirements ✅ COMPLETE
- **System Inputs** (4 documents) ✅ NEW
  - System Requirements Specification ✅
  - System Safety Requirements Specification ✅
  - System Architecture Description ✅
  - System Safety Plan ✅
- Software Requirements Specification ✅
- Requirements Traceability Matrix ✅
- Hazard Log ✅

### Phase 3: Architecture & Design 🔄 IN PROGRESS
- Software Architecture Specification ✅
- Software Design Specification ⏳
- Software Interface Specifications ⏳

### Phase 4-7: Implementation through Validation ⏳ PLANNED
- Implementation, Integration, Validation phases planned

---

## How to Use This Documentation

### For System Engineers
1. **Maintain system documents** in `docs/system/`
2. **Baseline system documents** before software development starts
3. **Process changes** through Change Control Board (CCB)
4. **Review software requirements** to ensure correct derivation from system requirements

### For Software Engineers
1. **Start here**: Read all 4 system input documents (docs/system/)
2. **Derive software requirements** from system requirements
3. **Maintain traceability**: Every SW-REQ-xxx → SYS-REQ-xxx
4. **Implement safety requirements**: Pay special attention to SW-SAFE-xxx (SIL 3)
5. **Follow plans**: SQAP, SCMP, SVP, SVaP define processes

### For Safety Engineers
1. **Hazard Log**: Maintain throughout project (docs/Hazard-Log.md)
2. **Safety requirements traceability**: Hazard → System → Software
3. **Safety verification**: Review static analysis, code reviews, test coverage
4. **Safety case**: Collect evidence from all phases

### For Verifiers/Validators
1. **Verification Plan**: docs/plans/Software-Verification-Plan.md
2. **Validation Plan**: docs/plans/Software-Validation-Plan.md
3. **Test traceability**: Requirement → Test case → Test result
4. **Coverage**: 100% MC/DC for SIL 3 safety functions

### For Project Managers
1. **LIFECYCLE_STATE.md**: Current project status
2. **Phase gates**: Use COD agent (/cod gate-check <phase>)
3. **Traceability**: Requirements Traceability Matrix
4. **Change control**: CCB for all baseline changes

---

## Key Contacts

| Role | Name | Responsibility |
|------|------|---------------|
| **System Engineer** | Dr. Sarah Chen | System requirements, architecture |
| **Safety Manager** | Michael Torres | Safety requirements, hazard log, safety case |
| **Software Lead** | Thomas Anderson | Software development |
| **Project Manager** | Lisa Anderson | Overall coordination |
| **Independent Safety Assessor** | James Wilson (TÜV SÜD) | Independent safety assessment |

---

## References

### EN 50128:2011
- **Section 7.2.2**: Inputs to Software Requirements Specification
- **Section 7.3**: Software Architecture and Design
- **Section 7.4**: Software Component Design
- **Section 7.5**: Software Component Implementation and Testing
- **Section 7.6**: Software Integration
- **Section 7.7**: Software Validation

### Project Documents
- **LIFECYCLE.md** (platform): Complete EN 50128 V-Model lifecycle
- **AGENTS.md** (platform): Agent roles and responsibilities
- **LIFECYCLE_STATE.md** (project): Current project status

---

**Last Updated**: 2026-02-21  
**Project**: train_door_control2  
**SIL Level**: SIL 3  
**Status**: Phase 2 Complete, Phase 3 In Progress
