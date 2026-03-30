# System-Level Input Documents

This directory contains the **4 system-level input documents** required by EN 50128:2011 Section 7.2.2 for software development initialization. These documents are produced by the **System Engineering** phase and serve as inputs to the **Software Engineering** phase.

---

## EN 50128 Section 7.2.2 Requirements

Per EN 50128:2011 Section 7.2.2, the following inputs SHALL be available before software requirements specification begins:

> "The inputs to this phase are:
> 1. **System Requirements Specification** (including description of overall functions and architecture)
> 2. **System Safety Requirements Specification** (including identified safety functions and their SIL assignment)
> 3. **System Architecture Description** (including definition of hardware and software functions)
> 4. **System Safety Plan** (including safety management and assessment approach)"

---

## Document Overview

### 1. System Requirements Specification
**File**: `System-Requirements-Specification.md`  
**Document ID**: DOC-SYS-REQ-2026-001  
**Status**: Approved Baseline (v1.0, 2026-02-10)

**Purpose**: Defines complete system-level requirements for the Train Door Control System, including functional, performance, interface, environmental, and safety requirements.

**Key Contents**:
- 70+ system requirements (SYS-REQ-001 to SYS-REQ-071)
- Requirements allocation to hardware, software, and operational procedures
- System context and interfaces
- SIL 3 classification and rationale
- Requirements traceability to hazards

**Usage**: Source for deriving software requirements (SW-REQ-xxx in Software Requirements Specification)

---

### 2. System Safety Requirements Specification
**File**: `System-Safety-Requirements-Specification.md`  
**Document ID**: DOC-SYS-SAFE-2026-001  
**Status**: Approved Baseline (v1.0, 2026-02-10)

**Purpose**: Defines safety requirements, hazards, risk analysis, and safety integrity requirements for the Train Door Control System at SIL 3.

**Key Contents**:
- 9 identified hazards (SYS-HAZ-001 to SYS-HAZ-009) with risk assessment
- 7 safety functions (SF-001 to SF-007) with SIL assignments
- Hardware safety integrity requirements (SAFE-HW-xxx)
- Software safety integrity requirements (SAFE-SW-xxx)
- FMEA and FTA analysis
- Safety function allocation to hardware and software

**Usage**: Source for deriving software safety requirements (SW-SAFE-xxx in Software Requirements Specification Section 3)

---

### 3. System Architecture Description
**File**: `System-Architecture-Description.md`  
**Document ID**: DOC-SYS-ARCH-2026-001  
**Status**: Approved Baseline (v1.0, 2026-02-10)

**Purpose**: Defines overall system architecture, including hardware/software decomposition, interfaces, safety architecture, and deployment.

**Key Contents**:
- System decomposition (Door Control Electronics, Door Actuator Units, interfaces)
- Hardware architecture (dual-channel processing, sensors, actuators)
- Software architecture overview (allocation to hardware)
- Safety architecture (2oo2 redundancy, fail-safe mechanisms)
- Communication architecture (CAN, MVB, discrete I/O)
- Physical architecture and deployment

**Usage**: Source for defining software architecture (Software Architecture Specification) and hardware/software interfaces

---

### 4. System Safety Plan
**File**: `System-Safety-Plan.md`  
**Document ID**: DOC-SYS-SAFE-PLAN-2026-001  
**Status**: Approved Baseline (v1.0, 2026-02-10)

**Purpose**: Defines safety management strategy, activities, organization, and processes for achieving and demonstrating SIL 3 safety integrity.

**Key Contents**:
- Safety management organization and roles (Safety Manager, Independent Safety Assessor)
- Safety lifecycle activities per EN 50126-2
- Hazard management process
- Safety verification and validation strategy
- Independent safety assessment plan
- Safety case structure

**Usage**: Defines safety management framework for software development (referenced in Software Quality Assurance Plan)

---

## Document Relationships

```
┌─────────────────────────────────────────────────────────────────┐
│              SYSTEM ENGINEERING OUTPUTS                         │
│              (These 4 Documents)                                │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  System Requirements            System Safety Requirements     │
│  Specification                  Specification                  │
│  (SYS-REQ-xxx)                  (HAZ-xxx, SF-xxx, SAFE-xxx)    │
│         │                                  │                   │
│         └──────────────┬───────────────────┘                   │
│                        │                                       │
│  System Architecture   │   System Safety Plan                  │
│  Description           │   (Safety Process)                    │
│  (HW/SW allocation)    │                                       │
│         │              │          │                            │
└─────────┼──────────────┼──────────┼────────────────────────────┘
          │              │          │
          ▼              ▼          ▼
┌─────────────────────────────────────────────────────────────────┐
│              SOFTWARE ENGINEERING INPUTS                        │
│              (EN 50128 Section 7.2)                             │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  Software Requirements Specification                            │
│  - Functional requirements (SW-REQ-xxx)                         │
│  - Safety requirements (SW-SAFE-xxx)                            │
│  - Derived from SYS-REQ-xxx and SAFE-SW-xxx                     │
│                                                                 │
│  Software Quality Assurance Plan (SQAP)                         │
│  - Implements safety process from System Safety Plan            │
│                                                                 │
│  Software Architecture Specification                            │
│  - Implements allocation from System Architecture Description   │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

## Traceability

### System to Software Requirements Traceability

| System Requirement | Software Requirement | Document |
|-------------------|---------------------|----------|
| SYS-REQ-001 to SYS-REQ-016 (Door control functions) | SW-REQ-001 to SW-REQ-050 | Software Requirements Specification Section 2 |
| SAFE-SW-001 to SAFE-SW-010 (Software safety integrity) | SW-SAFE-001 to SW-SAFE-020 | Software Requirements Specification Section 3 |
| SF-001, SF-002, SF-006, SF-007 (Safety functions allocated to software) | SW-SAFE-xxx (specific safety requirements) | Software Requirements Specification Section 3 |

### Hazard to Software Safety Requirements Traceability

| Hazard | System Safety Function | Software Safety Requirement |
|--------|----------------------|---------------------------|
| HAZ-001 (Doors open while moving) | SF-001 (Door opening interlock) | SW-SAFE-001 to SW-SAFE-005 (Speed interlock logic) |
| HAZ-001, HAZ-004 (Door unlock while moving) | SF-002 (Door locking function) | SW-SAFE-006 to SW-SAFE-010 (Lock control logic) |
| HAZ-002 (Doors close on passenger) | SF-003 (Obstacle detection) | SW-SAFE-011 to SW-SAFE-015 (Obstacle detection logic) |
| HAZ-006 (Door not closed before departure) | SF-006 (Door closed verification) | SW-SAFE-016 to SW-SAFE-018 (Position verification logic) |

See **Requirements Traceability Matrix** (`../Requirements-Traceability-Matrix.md`) for complete traceability.

---

## Usage in Software Development

### Phase 2: Software Requirements (EN 50128 Section 7.2)

**Input Documents** (these 4 system documents):
1. Read System Requirements Specification → Identify software-allocated requirements
2. Read System Safety Requirements Specification → Identify software safety requirements
3. Read System Architecture Description → Understand HW/SW allocation and interfaces
4. Read System Safety Plan → Understand safety process and verification requirements

**Output Document**:
- **Software Requirements Specification** (DOC-SRS-2026-001)
  - Section 2: Functional requirements (derived from SYS-REQ-xxx)
  - Section 3: Safety requirements (derived from SAFE-SW-xxx and SF-xxx)
  - Section 4: Interface requirements (derived from System Architecture Description)

### Phase 3: Software Architecture (EN 50128 Section 7.3)

**Input Documents**:
- System Architecture Description → Defines hardware platform, processing architecture, interfaces
- Software Requirements Specification → Defines software modules and structure

**Output Document**:
- **Software Architecture Specification** (DOC-SAS-2026-001)
  - Implements software allocation from System Architecture Description
  - Maps software components to hardware (dual-channel processing)
  - Defines software interfaces per System Architecture Description

---

## Document Status and Approval

All 4 system-level documents are:
- **Status**: Approved Baseline
- **Version**: 1.0
- **Baseline Date**: 2026-02-10
- **Configuration Management**: Under version control (Git), managed by Configuration Manager
- **Change Control**: Any changes require Change Control Board (CCB) approval

**Approvers**:
- System Engineer: Dr. Sarah Chen
- Safety Manager: Michael Torres
- Project Manager: Lisa Anderson
- Independent Safety Assessor: James Wilson (TÜV SÜD)
- Railway Safety Authority: UK Rail Safety Authority

---

## References

### EN 50128:2011 References

- **Section 7.2.2** - Inputs to Software Requirements Specification phase
  - "The inputs to this phase are..." (lists these 4 documents)
- **Section 5.3** - Lifecycle issues and documentation
  - Requirements for system-level inputs before software development

### EN 50126-2:2017 References

- System hazard analysis methodology
- Risk assessment and SIL determination

### EN 50129:2018 References

- Safety integrity requirements for SIL 3
- Safety case structure

---

## Notes for Software Engineers

1. **READ THESE FIRST**: Before starting Software Requirements Specification, read all 4 documents to understand:
   - What the system does (System Requirements Specification)
   - Why it's SIL 3 (System Safety Requirements Specification - hazards)
   - How it's built (System Architecture Description)
   - How safety is managed (System Safety Plan)

2. **Traceability is MANDATORY**: Every software requirement SHALL trace back to a system requirement or safety requirement

3. **Don't duplicate system requirements**: Software Requirements Specification should contain software-specific requirements, not copy system requirements verbatim

4. **Safety requirements are critical**: Pay special attention to SAFE-SW-xxx requirements (these drive EN 50128 SIL 3 compliance)

5. **Interfaces are defined**: System Architecture Description defines all hardware/software interfaces (CAN, MVB, I/O)

---

## Contact

For questions about these system-level documents:
- **System Requirements**: Dr. Sarah Chen (System Engineer)
- **Safety Requirements**: Michael Torres (Safety Manager)
- **Architecture**: Dr. Robert Kim (System Architect)
- **Safety Process**: Michael Torres (Safety Manager)

---

**Document Location**: `examples/train_door_control2/docs/system/`  
**Last Updated**: 2026-02-21
