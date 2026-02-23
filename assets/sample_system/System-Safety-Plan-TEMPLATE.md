# System Safety Plan

**DOCUMENT TYPE**: System-Level Input Document  
**EN 50128 REFERENCE**: Section 7.2.2 (Input to Software Requirements Specification)  
**STANDARD**: EN 50126-2:2017, EN 50129:2018

<!--
TEMPLATE USAGE INSTRUCTIONS:

This is a REFERENCE EXAMPLE document, not a generic template with placeholders.

The content below is a REAL, COMPLETE System Safety Plan for the Train Door Control System.
It demonstrates proper EN 50126/50129 compliant safety planning structure, including:
- Safety management organization (roles, responsibilities, independence)
- Safety lifecycle activities mapped to V-Model phases
- Hazard management process with real FMEA/FTA examples
- V&V strategy with SIL 3-specific requirements
- Independent Safety Assessment (ISA) plan
- Safety case development approach

TO USE THIS TEMPLATE FOR YOUR PROJECT:

1. COPY this file and rename it (e.g., System-Safety-Plan.md)
2. REPLACE metadata fields with YOUR project information:
   - Document IDs: DOC-SYS-SAFE-PLAN-YYYY-NNN → DOC-SYS-SAFE-PLAN-2026-001
   - Dates: YYYY-MM-DD → 2026-03-15
   - Names: [Name] → Jane Smith
   - Organizations: [Railway Authority] → UK Rail Safety Authority
   - Configuration IDs: CI-SYS-SAFE-PLAN-NNN → CI-SYS-SAFE-PLAN-001
3. ADAPT the concrete Train Door Control System content to YOUR system:
   - Keep the section structure and safety planning approach
   - Replace Train Door Control specifics with YOUR system details
   - Maintain the same level of rigor and detail
   - Follow the same EN 50126/50129 compliance patterns

This approach gives you a working example to learn from and adapt, rather than
forcing you to fill in generic placeholders without context.

Key sections to customize:
- Section 1: Your system description, SIL level, safety standards
- Section 2: Your safety organization (names, roles)
- Section 3-8: Your lifecycle activities, schedule, ISA plan
- Section 12: Your operational safety procedures
- Section 15: Your safety assumptions and dependencies
-->

---

## DOCUMENT CONTROL

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SYS-SAFE-PLAN-YYYY-NNN |
| **Version** | 1.0 |
| **Date** | YYYY-MM-DD |
| **Project** | Train Door Control System (train_door_control2) |
| **System SIL Level** | SIL 3 |
| **Author** | Safety Management Team |
| **Status** | Approved - Active Safety Plan |

---

## VERSION HISTORY

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | [Safety Manager Name] | Initial safety plan draft | - |
| 0.5 | YYYY-MM-DD | [Safety Manager Name] | Review updates, added assessment plan | [Technical Lead Name] |
| 1.0 | YYYY-MM-DD | [Safety Manager Name] | Approved baseline | [Safety Authority], [Project Manager Name] |

---

## APPROVALS

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Safety Manager** | [Name] | [Signed] | YYYY-MM-DD |
| **Independent Safety Assessor** | [Name] ([Assessment Body]) | [Signed] | YYYY-MM-DD |
| **System Engineer** | [Name] | [Signed] | YYYY-MM-DD |
| **Project Manager** | [Name] | [Signed] | YYYY-MM-DD |
| **Railway Safety Authority** | [Railway Authority] | [Signed] | YYYY-MM-DD |

---

## 1. INTRODUCTION

### 1.1 Purpose

This System Safety Plan defines the safety management strategy, activities, organization, and processes for the **Train Door Control System** development, verification, validation, and operation. It establishes the framework for achieving and demonstrating SIL 3 safety integrity per EN 50129.

This plan covers:
- Safety management organization and responsibilities
- Safety lifecycle activities per EN 50126-2
- Hazard management process
- Safety requirements management
- Safety verification and validation
- Independent safety assessment
- Safety case development

### 1.2 Scope

This Safety Plan applies to all safety-related activities for the Train Door Control System, including:
- System safety activities (hazard analysis, safety requirements, safety case)
- Hardware safety activities (hardware safety design, verification)
- Software safety activities (per EN 50128 - detailed in Software Quality Assurance Plan)
- Safety assessment and certification

**Project Lifecycle Coverage**: All phases from concept through operation and maintenance

### 1.3 Safety Standards and Regulations

This project SHALL comply with the following safety standards:

| Standard | Title | Application |
|----------|-------|-------------|
| **EN 50126-1:2017** | RAMS - Part 1: Generic RAMS process | Overall RAMS framework |
| **EN 50126-2:2017** | RAMS - Part 2: Systems approach to safety | Safety process and risk assessment |
| **EN 50129:2018** | Safety related electronic systems for signalling | System safety integrity (SIL 3) |
| **EN 50128:2011** | Software for railway control and protection systems | Software safety (SIL 3) |
| **EN 14752:2015** | Railway applications - Bodyside entrance systems | Door safety requirements |

**Regulatory Requirements**:
- UK Railway Safety Authority approval required
- Compliance with Railway Safety Directive 2004/49/EC (as applicable)

### 1.4 System SIL Classification

**Target SIL Level**: **SIL 3**

**Safety Functions at SIL 3**:
- SF-001: Door Opening Interlock (prevent opening when train moving)
- SF-002: Door Locking Function (maintain locks when moving)
- SF-004: Emergency Release (mechanical fail-safe)
- SF-006: Door Closed Verification (confirm doors closed before train movement)
- SF-007: Fault Detection and Safe State

See **System Safety Requirements Specification (DOC-SYS-SAFE-YYYY-NNN)** for complete safety requirements.

---

## 2. SAFETY MANAGEMENT ORGANIZATION

### 2.1 Safety Organization Structure

```
┌────────────────────────────────────────────────────────────────┐
│               RAILWAY SAFETY AUTHORITY                         │
│               ([Railway Authority])                            │
└────────────────────┬───────────────────────────────────────────┘
                     │ Approval & Oversight
                     │
┌────────────────────▼───────────────────────────────────────────┐
│            INDEPENDENT SAFETY ASSESSOR (ISA)                   │
│            [Name] ([Assessment Body])                          │
│            - Independent from project organization             │
│            - Reports directly to Safety Authority              │
└────────────────────────────────────────────────────────────────┘
                     
┌────────────────────────────────────────────────────────────────┐
│                   PROJECT ORGANIZATION                         │
├────────────────────────────────────────────────────────────────┤
│                                                                │
│  ┌──────────────────────────────────────────────────────┐     │
│  │         PROJECT MANAGER ([Name])                     │     │
│  │         - Overall project responsibility             │     │
│  └───────────────────┬──────────────────────────────────┘     │
│                      │                                         │
│      ┌───────────────┼───────────────┐                         │
│      │               │               │                         │
│  ┌───▼─────────┐ ┌───▼────────┐ ┌───▼─────────────┐           │
│  │  SAFETY     │ │  TECHNICAL │ │  QUALITY        │           │
│  │  MANAGER    │ │  LEAD      │ │  ASSURANCE      │           │
│  │  ([Name])   │ │  ([Name])  │ │  MANAGER        │           │
│  │             │ │            │ │  ([Name])       │           │
│  └──────┬──────┘ └──────┬─────┘ └─────────────────┘           │
│         │               │                                      │
│  ┌──────▼──────────┐    │                                      │
│  │  Safety         │    ├─────────────┬─────────────┐          │
│  │  Engineers      │    │             │             │          │
│  │  - System       │  ┌─▼───────┐ ┌───▼──────┐ ┌───▼──────┐   │
│  │    Safety       │  │ Hardware│ │ Software │ │ Test     │   │
│  │  - Software     │  │ Team    │ │ Team     │ │ Team     │   │
│  │    Safety       │  └─────────┘ └──────────┘ └──────────┘   │
│  └─────────────────┘                                           │
└────────────────────────────────────────────────────────────────┘
```

### 2.2 Safety Roles and Responsibilities

#### 2.2.1 Safety Manager ([Name])

**Responsibilities**:
- Overall responsibility for safety activities and safety plan execution
- Hazard management (maintain Hazard Log)
- Safety requirements management and traceability
- Safety case development and maintenance
- Interface with Independent Safety Assessor
- Safety training coordination
- Safety review and approval of deliverables
- Safety reporting to Project Manager and Safety Authority

**Authority**:
- Approve/reject work products with safety implications
- Mandate additional safety activities if needed
- Escalate safety concerns to Project Manager or Safety Authority

**Independence**: Reports to Project Manager but has authority to escalate safety issues directly to Safety Authority

#### 2.2.2 System Safety Engineer ([Name])

**Responsibilities**:
- System hazard analysis (FMEA, FTA)
- System safety requirements derivation
- System safety case development
- Safety architecture review
- Interface with hardware and software safety engineers
- Safety verification planning (system level)
- Residual risk assessment

**Deliverables**:
- System Safety Requirements Specification (DOC-SYS-SAFE-YYYY-NNN)
- Hazard Log (docs/Hazard-Log.md)
- FMEA and FTA reports
- System Safety Case

#### 2.2.3 Software Safety Engineer (Part of Software Team)

**Responsibilities**:
- Software safety requirements specification (per EN 50128 Section 7.2)
- Software safety architecture review
- Software hazard analysis (Software FMEA)
- Software safety verification planning
- Software safety case contribution
- EN 50128 SIL 3 compliance verification

**Deliverables**:
- Software safety requirements (in Software Requirements Specification)
- Software safety analysis reports
- Software safety verification evidence

**Independence**: For SIL 3, software verification SHALL be independent from software design and implementation

#### 2.2.4 Independent Safety Assessor (ISA) - [Name] ([Assessment Body])

**Responsibilities** (per EN 50129 Section 6):
- Independent assessment of safety case
- Review of hazard analysis and safety requirements
- Assessment of safety integrity (SIL 3 achievement)
- Review of verification and validation evidence
- Assessment report for Safety Authority
- Witness key safety tests

**Independence Requirements**:
- Organizationally and financially independent from project team
- No involvement in design, development, or testing
- Reports directly to Railway Safety Authority
- Veto authority on safety acceptance

**Deliverables**:
- Independent Safety Assessment Plan
- Safety Assessment Reports (interim and final)
- Safety Assessment Opinion for Safety Authority

#### 2.2.5 Project Manager ([Name])

**Responsibilities**:
- Allocate resources for safety activities
- Ensure safety plan execution
- Safety milestone approval
- Resolve resource conflicts impacting safety
- Safety reporting to senior management and customer

**Note**: Project Manager does NOT have authority to override Safety Manager or ISA safety decisions

### 2.3 Safety Independence Requirements

Per EN 50129 and EN 50128, the following independence requirements apply for SIL 3:

| Activity | Independence Requirement | Implementation |
|----------|--------------------------|----------------|
| **Software Verification** | Independent from software design and coding | Separate verification team, reports to QA Manager |
| **Software Validation** | Independent from software development | Separate validation team |
| **Safety Assessment** | Independent from project organization | External ISA ([Assessment Body]), reports to Safety Authority |
| **Hazard Analysis** | Independent review required | Peer review by external safety expert |

---

## 3. SAFETY LIFECYCLE

### 3.1 Safety Lifecycle Model

The project follows the **EN 50126 V-Model Safety Lifecycle**:

```
LEFT SIDE (SPECIFICATION)              RIGHT SIDE (VERIFICATION/VALIDATION)

┌─────────────────────────┐
│ 1. Concept              │
│    - Initial hazards    │
└────────┬────────────────┘
         │
         ▼
┌─────────────────────────┐            ┌─────────────────────────┐
│ 2. System Definition    │            │ 9. System Acceptance    │
│    - Hazard analysis    │◀───────────│    - Safety validation  │
│    - Safety reqts       │            │    - ISA approval       │
└────────┬────────────────┘            └─────────────────────────┘
         │                                         ▲
         ▼                                         │
┌─────────────────────────┐            ┌──────────┴──────────────┐
│ 3. Risk Analysis        │            │ 8. System Integration   │
│    - FMEA, FTA          │◀───────────│    - Integration test   │
│    - SIL determination  │            │    - Safety validation  │
└────────┬────────────────┘            └─────────────────────────┘
         │                                         ▲
         ▼                                         │
┌─────────────────────────┐            ┌──────────┴──────────────┐
│ 4. System Requirements  │            │ 7. Subsystem Validation │
│    - System safety reqs │◀───────────│    - HW validation      │
│    - Allocation to      │            │    - SW validation      │
│      HW/SW              │            └─────────────────────────┘
└────────┬────────────────┘                        ▲
         │                                         │
         ├──────────────┬──────────────┐           │
         ▼              ▼              ▼           │
┌────────────┐  ┌────────────┐  ┌────────────┐    │
│ 5. HW      │  │ 5. SW      │  │ 5. Ops     │    │
│ Design     │  │ Design     │  │ Procedures │    │
└──────┬─────┘  └──────┬─────┘  └──────┬─────┘    │
       │               │               │          │
       ▼               ▼               ▼          │
┌────────────┐  ┌────────────┐  ┌────────────┐    │
│ 6. HW      │  │ 6. SW      │  │ 6. Ops     │    │
│ Implement  │  │ Implement  │  │ Training   │    │
└──────┬─────┘  └──────┬─────┘  └──────┬─────┘    │
       │               │               │          │
       └───────────────┴───────────────┴──────────┘
```

### 3.2 Safety Activities by Lifecycle Phase

#### Phase 1: Concept (Complete)

**Safety Activities**:
- Initial hazard identification
- Preliminary risk assessment
- SIL determination

**Deliverables**:
- Preliminary Hazard List
- Initial risk assessment

**Status**: ✅ Complete (YYYY-MM-DD)

#### Phase 2: System Definition (Complete)

**Safety Activities**:
- Detailed hazard analysis (FMEA, FTA)
- System safety requirements specification
- Safety architecture definition
- This System Safety Plan

**Deliverables**:
- System Safety Requirements Specification (DOC-SYS-SAFE-YYYY-NNN) ✅
- Hazard Log (docs/Hazard-Log.md) ✅
- FMEA Report ✅
- FTA Report ✅
- System Safety Plan (this document) ✅

**Status**: ✅ Complete (YYYY-MM-DD)

#### Phase 3: Risk Analysis (Complete)

**Safety Activities**:
- Quantitative risk assessment
- SIL validation (confirm SIL 3 appropriate)
- Residual risk assessment

**Deliverables**:
- Quantitative Risk Assessment Report ✅

**Status**: ✅ Complete (YYYY-MM-DD)

#### Phase 4: System Requirements (In Progress)

**Safety Activities**:
- Allocate safety requirements to hardware and software
- Define safety-related interfaces
- Traceability matrix (hazards → safety requirements → subsystem requirements)

**Deliverables**:
- System Requirements Specification (DOC-SYS-REQ-YYYY-NNN) ✅
- Software Requirements Specification with safety requirements (DOC-SRS-YYYY-NNN) ✅
- Hardware Requirements Specification (in progress)
- Requirements Traceability Matrix (docs/Requirements-Traceability-Matrix.md) ✅

**Status**: 🔄 In Progress (Expected: YYYY-MM-DD)

#### Phase 5: Design (Hardware and Software)

**Safety Activities**:
- Hardware safety design review
- Software safety architecture review (per EN 50128 Section 7.3)
- Software safety design review (per EN 50128 Section 7.4)
- Safety-critical component identification
- Defensive programming review

**Deliverables**:
- Hardware Design Specification with safety analysis
- Software Architecture Specification (DOC-SAS-YYYY-NNN)
- Software Design Specification (DOC-SDS-YYYY-NNN)
- Design safety review reports

**Status**: ⏳ Planned (Start: YYYY-MM-DD)

#### Phase 6: Implementation (Hardware and Software)

**Safety Activities**:
- Hardware safety verification (component qualification)
- Software safety implementation review (per EN 50128 Section 7.5)
- MISRA C compliance verification (mandatory SIL 2+)
- Unit testing with safety coverage analysis
- Static analysis (PC-lint, Cppcheck)

**Deliverables**:
- Hardware qualification reports
- Software source code with safety annotations
- MISRA C compliance report (zero mandatory violations)
- Unit test reports with coverage (target 100% MC/DC for safety functions)
- Static analysis reports

**Status**: ⏳ Planned (Start: YYYY-MM-DD)

#### Phase 7: Subsystem Validation (Hardware and Software)

**Safety Activities**:
- Hardware safety testing (environmental, EMC, fault injection)
- Software validation testing (per EN 50128 Section 7.7)
- Safety function validation (test cases derived from safety requirements)
- Fault injection testing (verify safe states)
- Independent validation (SIL 3 requirement)

**Deliverables**:
- Hardware test reports (environmental, EMC)
- Software Validation Report
- Safety function test reports
- Fault injection test reports

**Status**: ⏳ Planned (Start: YYYY-MM-DD)

#### Phase 8: System Integration

**Safety Activities**:
- Hardware-software integration testing
- System-level safety testing (hazard scenario testing)
- Interface testing (safety-critical interfaces)
- Performance testing under safety constraints
- Integration fault injection

**Deliverables**:
- Integration test reports
- Hazard scenario test reports
- Safety performance verification reports

**Status**: ⏳ Planned (Start: YYYY-MM-DD)

#### Phase 9: System Acceptance

**Safety Activities**:
- Independent safety assessment (ISA review)
- Safety case finalization
- Factory Acceptance Test (FAT) with safety scenarios
- Site Acceptance Test (SAT)
- Railway Safety Authority approval

**Deliverables**:
- Independent Safety Assessment Report (ISA)
- Safety Case (complete)
- FAT/SAT reports with safety evidence
- Safety Authority approval certificate

**Status**: ⏳ Planned (Start: YYYY-MM-DD, Approval Target: YYYY-MM-DD)

---

## 4. HAZARD MANAGEMENT

### 4.1 Hazard Identification Process

**Methods**:
- Preliminary Hazard Analysis (PHA) - concept phase
- Failure Mode and Effects Analysis (FMEA) - detailed design
- Fault Tree Analysis (FTA) - top-down risk analysis
- Operational hazard analysis - operational scenarios
- Change impact analysis - for design changes

**Triggers for Hazard Analysis**:
- Initial system definition
- Design changes
- Requirements changes
- Failure events during testing or operation
- Regulatory changes

### 4.2 Hazard Log

**Hazard Log Location**: `docs/Hazard-Log.md`

**Hazard Log Contents** (per EN 50126-2):
- Hazard ID and description
- Potential causes
- Consequences and severity
- Frequency estimation
- Risk classification
- SIL assignment
- Derived safety requirements
- Mitigation measures (design, procedures, training)
- Verification evidence
- Residual risk assessment
- Status (open, mitigated, closed)

**Hazard Log Management**:
- Maintained by Safety Manager
- Updated throughout project lifecycle
- Reviewed at each lifecycle phase gate
- Version controlled (same as safety documents)
- Reviewed by Independent Safety Assessor

**Hazard Closure Criteria**:
- All derived safety requirements implemented and verified
- Residual risk demonstrated ALARP (As Low As Reasonably Practicable)
- Safety Manager approval
- ISA review and concurrence

### 4.3 Risk Assessment Methodology

**Risk Matrix** (per EN 50126-2):

| Severity ↓ / Frequency → | Frequent | Probable | Occasional | Remote | Improbable | Incredible |
|---------------------------|----------|----------|------------|--------|------------|------------|
| **Catastrophic** | Intolerable | Unacceptable | Unacceptable | Undesirable | Tolerable | Acceptable |
| **Critical** | Unacceptable | Undesirable | Undesirable | Tolerable | Acceptable | Acceptable |
| **Marginal** | Undesirable | Tolerable | Tolerable | Acceptable | Acceptable | Acceptable |
| **Negligible** | Tolerable | Acceptable | Acceptable | Acceptable | Acceptable | Acceptable |

**SIL Assignment**:
- **Intolerable**: SIL 4 (must be eliminated or reduced)
- **Unacceptable**: SIL 3-4 (requires risk reduction)
- **Undesirable**: SIL 2-3 (requires justification if not reduced)
- **Tolerable**: SIL 1-2 (acceptable with review)
- **Acceptable**: SIL 0-1 (no additional safety requirements)

### 4.4 Residual Risk Management

After all mitigation measures implemented, residual risk SHALL be:
- Assessed quantitatively (dangerous failure rates)
- Documented in Hazard Log
- Demonstrated ALARP (As Low As Reasonably Practicable)
- Accepted by Safety Authority

**ALARP Demonstration**:
- Further risk reduction impractical (cost grossly disproportionate to benefit)
- Industry best practices applied
- Comparison with similar systems
- Independent expert review

---

## 5. SAFETY REQUIREMENTS MANAGEMENT

### 5.1 Safety Requirements Hierarchy

```
┌────────────────────────────────────────────────────────────┐
│                      HAZARDS                               │
│         (Hazard Log: SYS-HAZ-001 to SYS-HAZ-009)           │
└────────────────────┬───────────────────────────────────────┘
                     │ Derive safety requirements
                     ▼
┌────────────────────────────────────────────────────────────┐
│               SYSTEM SAFETY REQUIREMENTS                   │
│         (System Safety Requirements Specification)         │
│         - Safety Functions (SF-001 to SF-007)              │
│         - Safety Integrity Requirements (SAFE-xxx)         │
└────────────────────┬───────────────────────────────────────┘
                     │ Allocate to subsystems
                     │
         ┌───────────┴───────────┐
         ▼                       ▼
┌─────────────────────┐  ┌───────────────────────┐
│  HARDWARE SAFETY    │  │  SOFTWARE SAFETY      │
│  REQUIREMENTS       │  │  REQUIREMENTS         │
│  (HW Spec)          │  │  (SW Requirements     │
│                     │  │   Specification       │
│                     │  │   Section 3)          │
└─────────────────────┘  └───────────────────────┘
```

### 5.2 Safety Requirements Attributes

All safety requirements SHALL have the following attributes:

| Attribute | Description | Mandatory |
|-----------|-------------|-----------|
| **Requirement ID** | Unique identifier (e.g., SAFE-SW-001) | Yes |
| **Description** | Clear, unambiguous statement (SHALL/SHALL NOT) | Yes |
| **SIL Level** | SIL 0, 1, 2, 3, or 4 | Yes |
| **Rationale** | Justification, link to hazard | Yes |
| **Allocation** | Hardware, Software, or Procedural | Yes |
| **Verification Method** | Test, Analysis, Inspection, Demonstration | Yes |
| **Traceability** | Parent (hazard) and children (design requirements) | Yes |
| **Status** | Draft, Approved, Implemented, Verified | Yes |

### 5.3 Safety Requirements Traceability

**Traceability Matrix** maintained in:
- Requirements Traceability Matrix (docs/Requirements-Traceability-Matrix.md)
- Traceability sections in safety documents

**Traceability Links**:
- **Backward**: Safety requirement → Hazard (source)
- **Forward**: Safety requirement → Design requirement → Implementation → Test case → Test result

**Traceability Reviews**:
- Requirements phase: Hazard → Safety requirements
- Design phase: Safety requirements → Design requirements
- Implementation phase: Design requirements → Code
- Test phase: Requirements → Test cases → Test results

**Tool Support**: Traceability managed in markdown tables (suitable for version control)

---

## 6. SAFETY VERIFICATION AND VALIDATION

### 6.1 V&V Strategy

**Verification** (Are we building the product right?):
- Requirements verification (completeness, consistency, correctness)
- Design verification (architecture review, design review)
- Code verification (static analysis, code review, unit testing)
- Integration verification (integration testing)

**Validation** (Are we building the right product?):
- System validation testing (against system requirements)
- Safety validation testing (against safety requirements and hazard scenarios)
- Operational scenario validation
- Acceptance testing (FAT, SAT)

### 6.2 Safety Verification Activities

#### Hardware Safety Verification

| Activity | Method | SIL 3 Requirement | Responsibility |
|----------|--------|-------------------|----------------|
| **Hardware design review** | Inspection | Mandatory | Safety Manager + Hardware Lead |
| **FMEA** | Analysis | Highly Recommended | System Safety Engineer |
| **Component qualification** | Test | Mandatory | Hardware Test Team |
| **Environmental testing** | Test | Mandatory (EN 50155, EN 61373) | Hardware Test Team |
| **EMC testing** | Test | Mandatory (EN 50121-3-2) | External test lab |
| **Fault injection** | Test | Highly Recommended | Hardware Test Team |

#### Software Safety Verification (per EN 50128)

| Activity | Method | SIL 3 Requirement | Responsibility |
|----------|--------|-------------------|----------------|
| **Requirements review** | Inspection | Mandatory | Safety Engineer (independent) |
| **Architecture review** | Inspection | Mandatory | Safety Engineer (independent) |
| **Design review** | Inspection | Mandatory | Safety Engineer (independent) |
| **Code review** | Inspection | Mandatory | QA Team (independent) |
| **Static analysis** | Analysis | Mandatory | Verification Team |
| **MISRA C compliance** | Analysis | Mandatory | Verification Team |
| **Complexity analysis** | Analysis | Highly Recommended | Verification Team |
| **Unit testing** | Test | Mandatory | Verification Team (independent) |
| **Integration testing** | Test | Mandatory | Verification Team |
| **Coverage analysis** | Analysis | Mandatory (100% MC/DC) | Verification Team |

**Independence**: Software verification SHALL be performed by team independent from software design and coding (SIL 3 requirement)

### 6.3 Safety Validation Activities

| Activity | Description | Responsibility | Schedule |
|----------|-------------|----------------|----------|
| **Hazard scenario testing** | Test cases derived from each hazard in Hazard Log | Validation Team | Phase 8 (Integration) |
| **Fault injection testing** | Inject faults to verify safe state transitions | Validation Team | Phase 7-8 |
| **Performance testing** | Verify timing constraints for safety functions (e.g., 50ms speed interlock response) | Validation Team | Phase 7-8 |
| **Operational scenario testing** | Test realistic operational scenarios (normal, degraded, emergency) | Validation Team | Phase 8 |
| **FAT (Factory Acceptance Test)** | Customer acceptance testing with safety scenarios | Validation Team + Customer | Phase 9 |
| **SAT (Site Acceptance Test)** | On-site testing in operational environment | Validation Team + Customer | Phase 9 |

**Independence**: Validation team SHALL be independent from development team (SIL 3 requirement)

### 6.4 Safety Test Coverage Requirements

Per EN 50128 Table A.21 (Test Coverage for Code):

| Coverage Type | SIL 0 | SIL 1-2 | SIL 3-4 | Train Door Control (SIL 3) |
|---------------|-------|---------|---------|---------------------------|
| **Entry Point** | R | HR | M | **100%** (Mandatory) |
| **Statement** | HR | HR | **M** | **100%** (Mandatory) |
| **Branch** | HR | **M** | **M** | **100%** (Mandatory) |
| **Condition** | R | R | **M** | **100%** (Mandatory) |
| **MC/DC** | - | R | **M** | **100%** (Mandatory for safety functions) |

**Target**: 100% MC/DC (Modified Condition/Decision Coverage) for all software implementing SIL 3 safety functions

**Coverage Tools**: gcov/lcov (open-source), Bullseye or VectorCAST (commercial, for MC/DC)

---

## 7. INDEPENDENT SAFETY ASSESSMENT

### 7.1 ISA Role and Responsibilities

**Independent Safety Assessor**: [Name] ([Assessment Body])

**Responsibilities** (per EN 50129 Section 6):
1. Assess safety management process compliance
2. Review hazard analysis (FMEA, FTA) for completeness and correctness
3. Assess safety requirements completeness and traceability
4. Review safety architecture and design
5. Assess verification and validation evidence
6. Review safety case
7. Witness key safety tests
8. Provide independent safety assessment report
9. Recommend approval or rejection to Safety Authority

**Independence**:
- Organizationally independent ([Assessment Body], not project organization)
- Financially independent (separate contract)
- No involvement in design, development, or testing
- Reports directly to Railway Safety Authority

### 7.2 ISA Assessment Plan

| Assessment Activity | Lifecycle Phase | Deliverable Reviewed | Schedule |
|---------------------|-----------------|----------------------|----------|
| **Assessment Plan Review** | Phase 2 | System Safety Plan | YYYY-MM-DD ✅ |
| **Hazard Analysis Review** | Phase 2-3 | System Safety Requirements Specification, FMEA, FTA | YYYY-MM-DD ✅ |
| **Requirements Assessment** | Phase 4 | Software Requirements Specification, traceability | YYYY-MM-DD (planned) |
| **Design Assessment** | Phase 5 | Software Architecture Specification, Software Design Specification | YYYY-MM-DD (planned) |
| **Code and Test Assessment** | Phase 6 | Source code, static analysis reports, unit test reports | YYYY-MM-DD (planned) |
| **Integration Assessment** | Phase 8 | Integration test reports, hazard scenario test results | YYYY-MM-DD (planned) |
| **Validation Assessment** | Phase 8-9 | Validation reports, FAT/SAT results | YYYY-MM-DD (planned) |
| **Final Safety Case Assessment** | Phase 9 | Complete safety case | YYYY-MM-DD (planned) |
| **Safety Assessment Report** | Phase 9 | Final report to Safety Authority | YYYY-MM-DD (planned) |

### 7.3 ISA Review Criteria

The ISA SHALL assess:
- **Compliance** with EN 50126, EN 50129, EN 50128 standards
- **Completeness** of hazard analysis and safety requirements
- **Traceability** from hazards through requirements, design, implementation, to verification
- **Adequacy** of verification and validation evidence
- **SIL Achievement**: Demonstration that SIL 3 integrity is achieved
- **Residual Risk**: Residual risk is ALARP and acceptable
- **Competence**: Personnel competence and training records

### 7.4 ISA Reporting

**Interim Reports**: After each major phase (Requirements, Design, Implementation, Integration, Validation)

**Final Assessment Report**: Before Safety Authority approval

**Report Contents**:
- Executive summary with recommendation (approve/reject)
- Assessment scope and methodology
- Findings (observations, non-conformances, recommendations)
- Evidence reviewed
- Conclusion on safety integrity achievement (SIL 3)
- Residual issues and risks

**Distribution**: Railway Safety Authority (primary), Project Manager, Safety Manager

---

## 8. SAFETY CASE

### 8.1 Safety Case Structure

The Safety Case follows EN 50129 structure:

```
┌─────────────────────────────────────────────────────────────┐
│                     SAFETY CASE                             │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. DEFINITION OF SYSTEM                                    │
│     - System description and boundaries                     │
│     - Operational context                                   │
│     - Reference documents                                   │
│                                                             │
│  2. QUALITY MANAGEMENT REPORT                               │
│     - Quality management system                             │
│     - Process compliance evidence                           │
│                                                             │
│  3. SAFETY MANAGEMENT REPORT                                │
│     - This System Safety Plan                               │
│     - Hazard Log                                            │
│     - Safety requirements traceability                      │
│                                                             │
│  4. TECHNICAL SAFETY REPORT                                 │
│     - Hazard analysis (FMEA, FTA)                           │
│     - Safety requirements specification                     │
│     - Safety architecture and design                        │
│     - Safety verification evidence                          │
│     - Safety validation evidence                            │
│     - Quantitative safety analysis (failure rates, SIL)     │
│                                                             │
│  5. RELATED SAFETY CASES                                    │
│     - Hardware safety case                                  │
│     - Software safety case (per EN 50128)                   │
│     - Interface safety cases (TCMS, speed sensors, etc.)    │
│                                                             │
│  6. CONCLUSION                                              │
│     - Safety claim: "The Train Door Control System is      │
│       acceptably safe for operation at SIL 3"               │
│     - Supporting evidence summary                           │
│     - Residual risk statement                               │
│     - ALARP justification                                   │
└─────────────────────────────────────────────────────────────┘
```

### 8.2 Safety Case Development

**Responsibility**: Safety Manager (with input from System Safety Engineer, Software Safety Engineer, ISA)

**Development Timeline**:
- **Draft Safety Case**: Phase 7 (after subsystem validation) - YYYY-MM-DD
- **Complete Safety Case**: Phase 9 (before FAT) - YYYY-MM-DD
- **Final Safety Case**: Phase 9 (after ISA review) - YYYY-MM-DD

**Review and Approval**:
1. Internal review (Safety Manager, Technical Lead, Project Manager)
2. Independent Safety Assessor review
3. Revision based on ISA feedback
4. Submission to Railway Safety Authority
5. Safety Authority approval

### 8.3 Safety Case Evidence

Key evidence to be included in Safety Case:

| Evidence Type | Documents/Reports |
|---------------|-------------------|
| **Hazard Analysis** | FMEA Report, FTA Report, Hazard Log |
| **Safety Requirements** | System Safety Requirements Specification, Software Requirements Specification |
| **Safety Design** | System Architecture Description, Software Architecture Specification, Software Design Specification |
| **Verification** | Static analysis reports, unit test reports, integration test reports, coverage reports |
| **Validation** | Hazard scenario test reports, fault injection reports, FAT/SAT reports |
| **Quantitative Analysis** | Failure rate calculations, SIL achievement demonstration |
| **Process Compliance** | Process audit reports, tool qualification reports |
| **Competence** | Training records, personnel qualifications |
| **ISA Assessment** | Independent Safety Assessment Report |

---

## 9. SAFETY TRAINING AND COMPETENCE

### 9.1 Competence Requirements

All personnel involved in safety-related activities SHALL have:
- **Education**: Relevant degree (engineering, computer science) or equivalent experience
- **Training**: EN 50126/50129/50128 standards training
- **Experience**: Previous safety-critical system experience (or mentorship)

**Specific Competencies**:

| Role | Required Competencies |
|------|----------------------|
| **Safety Manager** | EN 50126/50129 expert, railway safety experience, risk assessment |
| **System Safety Engineer** | Hazard analysis (FMEA, FTA), EN 50129, safety architecture |
| **Software Safety Engineer** | EN 50128 SIL 3 lifecycle, software safety analysis, MISRA C |
| **Independent Safety Assessor** | EN 50129 assessment, railway safety certification, independence |

### 9.2 Safety Training Plan

| Training | Target Audience | Provider | Schedule |
|----------|----------------|----------|----------|
| **EN 50128 SIL 3 Software Development** | Software Team | [Training Provider] | YYYY-MM-DD (complete) ✅ |
| **EN 50129 Safety Case Development** | Safety Manager, System Safety Engineer | [Training Provider] | YYYY-MM-DD (complete) ✅ |
| **MISRA C:2012 Guidelines** | Software Developers | Internal | YYYY-MM-DD (complete) ✅ |
| **Hazard Analysis (FMEA/FTA)** | Safety Engineers, Hardware/Software Leads | External consultant | YYYY-MM-DD (complete) ✅ |
| **Railway Safety Standards Overview** | All team members | Internal | YYYY-MM-DD (planned) |
| **Static Analysis Tools (PC-lint)** | Verification Team | Tool vendor | YYYY-MM-DD (planned) |

**Training Records**: Maintained by Project Manager, reviewed by Safety Manager and ISA

---

## 10. SAFETY DOCUMENTATION

### 10.1 Safety Documents Hierarchy

```
┌─────────────────────────────────────────────────────────────┐
│                  SYSTEM LEVEL (Complete)                    │
├─────────────────────────────────────────────────────────────┤
│  - System Requirements Specification                        │
│  - System Safety Requirements Specification                 │
│  - System Architecture Description                          │
│  - System Safety Plan (this document)                       │
│  - Hazard Log                                               │
└────────────────────┬────────────────────────────────────────┘
                     │
         ┌───────────┴───────────┐
         ▼                       ▼
┌──────────────────────┐  ┌────────────────────────────────┐
│  HARDWARE SAFETY     │  │  SOFTWARE SAFETY (EN 50128)    │
│  (In Progress)       │  │  (In Progress)                 │
├──────────────────────┤  ├────────────────────────────────┤
│ - HW Requirements    │  │ - Software Requirements        │
│   Specification      │  │   Specification ✅              │
│ - HW Design Spec     │  │ - Software Quality Assurance   │
│ - HW Test Reports    │  │   Plan (SQAP)                  │
│ - HW Safety Case     │  │ - Software Configuration       │
│                      │  │   Management Plan (SCMP)       │
│                      │  │ - Software Verification Plan   │
│                      │  │ - Software Validation Plan     │
│                      │  │ - Software Architecture        │
│                      │  │   Specification                │
│                      │  │ - Software Design              │
│                      │  │   Specification                │
│                      │  │ - Software Source Code         │
│                      │  │ - Test Specifications/Reports  │
│                      │  │ - Software Safety Case         │
└──────────────────────┘  └────────────────────────────────┘
                                      │
                                      ▼
                          ┌────────────────────────┐
                          │  VERIFICATION &        │
                          │  VALIDATION EVIDENCE   │
                          ├────────────────────────┤
                          │ - Test reports         │
                          │ - Coverage reports     │
                          │ - Static analysis      │
                          │ - Review records       │
                          └────────────────────────┘
```

### 10.2 Safety Document Control

**Configuration Management**:
- All safety documents under version control (Git)
- Baseline versions approved by Safety Manager
- Changes processed through Change Control Board (CCB)
- Traceability of changes

**Document Review and Approval**:
- Internal review (technical lead, safety manager)
- Independent review (ISA for key documents)
- Approval sign-off (project manager, safety manager)

**Document Status**:
- Draft
- Internal Review
- ISA Review
- Approved (Baseline)

**Document Identification**:
- Unique Document ID (e.g., DOC-SYS-SAFE-PLAN-YYYY-NNN)
- Version number (major.minor)
- Date
- Configuration Item ID (for baseline versions)

---

## 11. CHANGE MANAGEMENT FOR SAFETY

### 11.1 Safety Change Control Process

**Change Control Board (CCB)**: See `docs/ccb-charter.md`

**Safety-Impacting Changes** (require Safety Manager approval):
- Changes to safety requirements
- Changes to safety-critical design
- Changes to safety-critical code
- Changes to verification or validation plans
- Changes to operational procedures affecting safety

**Safety Change Assessment**:
1. **Impact Analysis**: Does change affect safety requirements, hazards, or safety case?
2. **Hazard Analysis**: Does change introduce new hazards or alter existing hazards?
3. **Regression Analysis**: What re-verification/re-validation is required?
4. **ISA Notification**: Inform ISA of safety-impacting changes

**Change Approval**:
- Minor changes (no safety impact): Technical lead approval
- Safety-impacting changes: Safety Manager approval + CCB approval
- Major safety changes: ISA review required

### 11.2 Safety Impact Assessment Criteria

A change has **safety impact** if it:
- Modifies or adds safety requirements
- Changes software implementing SIL 3 safety functions
- Alters safety architecture or redundancy
- Affects safety-critical interfaces
- Changes operational procedures related to safety
- Impacts hazard analysis or risk assessment

**Safety Impact Levels**:
- **High**: Direct change to SIL 3 safety functions → Full re-verification + ISA review
- **Medium**: Change to SIL 2 functions or non-safety code with potential impact → Partial re-verification
- **Low**: No impact on safety functions, only operational features → Standard verification

---

## 12. OPERATIONAL SAFETY

### 12.1 Operational Safety Requirements

**Operational Procedures** shall be developed for:
- Normal operation (driver training on door control system)
- Emergency evacuation (emergency release usage)
- Maintenance procedures (diagnostic mode, sensor calibration)
- Fault response procedures (degraded mode operation)

**Safety-Critical Operational Procedures**:
1. **Emergency Evacuation Mode Activation**: Requires driver authorization, only when train stationary or speed < 5 km/h
2. **Manual Door Release**: Passenger emergency door release instructions (clearly marked)
3. **Fault Response**: Driver actions when door faults detected (alert protocols, degraded operation)

### 12.2 Maintenance Safety

**Preventive Maintenance**:
- Sensor calibration and testing (quarterly)
- Lock mechanism inspection and lubrication (monthly)
- Emergency release pull-test (monthly)
- Software configuration backup (weekly)

**Corrective Maintenance**:
- Fault diagnosis using diagnostic mode
- Module replacement (MTTR ≤ 30 min target)
- Post-maintenance testing (functional test + safety function test)

**Safety Considerations**:
- Maintenance mode does NOT bypass safety interlocks
- Test procedures include safety function verification
- Maintenance personnel training on safety system operation

### 12.3 Incident Reporting and Analysis

**Safety Incident Reporting**:
- Any safety-related failure or near-miss SHALL be reported to Safety Manager
- Incident investigation within 48 hours
- Root cause analysis for safety incidents
- Hazard Log update if new hazards identified
- Corrective action plan

**Incident Categories**:
- **Category 1 (Critical)**: Safety function failure (e.g., doors opened while moving) → Immediate investigation + ISA notification
- **Category 2 (Major)**: Degraded safety function (e.g., single sensor failure detected) → Investigation within 24 hours
- **Category 3 (Minor)**: Non-safety fault (e.g., display failure) → Standard fault handling

---

## 13. SAFETY METRICS AND REPORTING

### 13.1 Safety Performance Indicators

**Leading Indicators** (process):
- Number of safety requirements defined and approved
- Percentage of safety requirements traced to hazards
- Number of safety reviews completed on schedule
- Percentage of safety test cases executed
- Number of open safety-related NCRs (Non-Conformance Reports)

**Lagging Indicators** (product):
- Dangerous failure rate (target: λ ≤ 10^-8 per hour for SIL 3)
- Diagnostic coverage (target: DC ≥ 99% for SIL 3)
- Test coverage (target: 100% MC/DC for safety functions)
- Number of safety-related defects found in testing
- MTBF (target: ≥ 50,000 hours)

### 13.2 Safety Reporting

**Weekly Safety Status** (to Project Manager):
- Safety activities completed this week
- Safety milestones achieved
- Safety-related issues and risks
- Action items

**Monthly Safety Report** (to Project Manager, ISA):
- Safety metrics (as above)
- Hazard Log status (new hazards, closed hazards)
- Safety verification and validation progress
- Safety-related change requests
- Safety risks and mitigation actions

**Phase Gate Safety Review** (to CCB, ISA, Safety Authority):
- Safety activities completed in phase
- Safety deliverables approved
- Safety verification evidence
- Open safety issues and closure plan
- Recommendation for phase transition

**Final Safety Report** (to Safety Authority):
- Complete safety case
- Verification and validation evidence
- ISA assessment report
- Residual risk assessment
- Recommendation for operational approval

---

## 14. SAFETY ASSURANCE

### 14.1 Safety Audits

**Internal Safety Audits**:
- Quarterly audits by QA Manager
- Audit safety process compliance (this Safety Plan)
- Audit safety document quality
- Audit traceability completeness
- Audit competence and training records

**External Safety Audit**:
- Conducted by Independent Safety Assessor (ISA)
- At key lifecycle phases (Requirements, Design, Implementation, Validation)
- Audit findings tracked to closure

**Audit Reports**: Distributed to Safety Manager, Project Manager, ISA

### 14.2 Safety Reviews

**Formal Safety Reviews**:
1. **Hazard Analysis Review** (Phase 3) - Review FMEA/FTA completeness
2. **Safety Requirements Review** (Phase 4) - Review safety requirements completeness and traceability
3. **Safety Design Review** (Phase 5) - Review safety architecture and design adequacy
4. **Safety Code Review** (Phase 6) - Review safety-critical code (MISRA C, defensive programming)
5. **Safety Test Review** (Phase 7-8) - Review safety test completeness and coverage
6. **Safety Case Review** (Phase 9) - Review complete safety case before ISA final assessment

**Review Participants**: Safety Manager, System Safety Engineer, Software Safety Engineer, Technical Lead, ISA (observer)

---

## 15. ASSUMPTIONS AND DEPENDENCIES

### 15.1 Safety Assumptions

**ASSUME-SAFE-001**: Train speed information from Speed Monitoring System is accurate and available with latency < 50 ms.  
**Verification**: Interface specification review, integration testing

**ASSUME-SAFE-002**: Platform detection system provides reliable platform side indication (SIL 2 integrity).  
**Verification**: Interface safety case review

**ASSUME-SAFE-003**: Driver is trained and follows operational procedures for emergency evacuation mode.  
**Verification**: Driver training program review, operational procedure validation

**ASSUME-SAFE-004**: Regular maintenance is performed per maintenance schedule.  
**Verification**: Maintenance procedures, audit maintenance records

**ASSUME-SAFE-005**: Mechanical door hardware (actuators, locks) meets reliability requirements.  
**Verification**: Hardware qualification testing, supplier RAMS data

### 15.2 Safety Dependencies

**DEPEND-SAFE-001**: System safety depends on accurate speed information from Train Control Management System (TCMS).  
**Mitigation**: Redundant speed sources, fail-safe default (assume moving if speed unavailable)

**DEPEND-SAFE-002**: Software safety integrity depends on EN 50128 SIL 3 development process compliance.  
**Mitigation**: Software Quality Assurance Plan, independent verification

**DEPEND-SAFE-003**: Hardware safety integrity depends on component quality and manufacturing.  
**Mitigation**: Component qualification, manufacturing quality control, acceptance testing

**DEPEND-SAFE-004**: Overall system safety depends on correct integration of hardware and software.  
**Mitigation**: Integration testing, hazard scenario testing, FAT/SAT

---

## 16. REFERENCES

### 16.1 Normative References

- **EN 50126-1:2017** - Railway applications - The specification and demonstration of RAMS - Part 1: Generic RAMS process
- **EN 50126-2:2017** - Railway applications - The specification and demonstration of RAMS - Part 2: Systems approach to safety
- **EN 50129:2018** - Railway applications - Communication, signalling and processing systems - Safety related electronic systems for signalling
- **EN 50128:2011** - Railway applications - Communications, signalling and processing systems - Software for railway control and protection systems
- **EN 14752:2015** - Railway applications - Bodyside entrance systems

### 16.2 Project References

- **System Requirements Specification** (DOC-SYS-REQ-YYYY-NNN)
- **System Safety Requirements Specification** (DOC-SYS-SAFE-YYYY-NNN)
- **System Architecture Description** (DOC-SYS-ARCH-YYYY-NNN)
- **Software Requirements Specification** (DOC-SRS-YYYY-NNN)
- **Software Quality Assurance Plan** (DOC-SQAP-YYYY-NNN)
- **Hazard Log** (docs/Hazard-Log.md)
- **Change Control Board Charter** (docs/ccb-charter.md)

---

## APPENDIX A: SAFETY ACTIVITY SCHEDULE

| Phase | Activity | Deliverable | Start Date | End Date | Status |
|-------|----------|-------------|------------|----------|--------|
| **Phase 2** | Hazard Analysis (FMEA, FTA) | System Safety Requirements Specification, FMEA/FTA Reports | YYYY-MM-DD | YYYY-MM-DD | ✅ Complete |
| **Phase 2** | System Safety Plan | System Safety Plan (this document) | YYYY-MM-DD | YYYY-MM-DD | ✅ Complete |
| **Phase 3** | Quantitative Risk Assessment | Risk Assessment Report | YYYY-MM-DD | YYYY-MM-DD | ✅ Complete |
| **Phase 4** | Safety Requirements Allocation | Software Requirements Specification (safety section) | YYYY-MM-DD | YYYY-MM-DD | 🔄 In Progress |
| **Phase 5** | Safety Design Review | Design Safety Review Report | YYYY-MM-DD | YYYY-MM-DD | ⏳ Planned |
| **Phase 6** | Safety Code Review | Code Safety Review Report | YYYY-MM-DD | YYYY-MM-DD | ⏳ Planned |
| **Phase 6** | Static Analysis | Static Analysis Reports (PC-lint, Cppcheck) | YYYY-MM-DD | YYYY-MM-DD | ⏳ Planned |
| **Phase 7** | Safety Unit Testing | Unit Test Reports (100% MC/DC) | YYYY-MM-DD | YYYY-MM-DD | ⏳ Planned |
| **Phase 8** | Hazard Scenario Testing | Hazard Scenario Test Reports | YYYY-MM-DD | YYYY-MM-DD | ⏳ Planned |
| **Phase 8** | Fault Injection Testing | Fault Injection Reports | YYYY-MM-DD | YYYY-MM-DD | ⏳ Planned |
| **Phase 9** | Draft Safety Case | Draft Safety Case Document | YYYY-MM-DD | YYYY-MM-DD | ⏳ Planned |
| **Phase 9** | FAT Safety Testing | FAT Test Reports | YYYY-MM-DD | YYYY-MM-DD | ⏳ Planned |
| **Phase 9** | Complete Safety Case | Final Safety Case Document | YYYY-MM-DD | YYYY-MM-DD | ⏳ Planned |
| **Phase 9** | ISA Final Assessment | Independent Safety Assessment Report | YYYY-MM-DD | YYYY-MM-DD | ⏳ Planned |
| **Phase 9** | Safety Authority Approval | Safety Approval Certificate | YYYY-MM-DD | YYYY-MM-DD | ⏳ Planned |

---

## DOCUMENT APPROVAL

This System Safety Plan is **APPROVED** and active for the Train Door Control System project.

**Baseline Version**: 1.0  
**Baseline Date**: YYYY-MM-DD  
**Configuration Item ID**: CI-SYS-SAFE-PLAN-NNN  

Any changes to this Safety Plan SHALL be processed through the Change Control Board (CCB) with Safety Manager approval and ISA notification.

---

**END OF DOCUMENT**
