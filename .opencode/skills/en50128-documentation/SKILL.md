---
name: en50128-documentation
description: EN 50128 compliant documentation templates for all mandatory deliverables including SRS, SAS, SDS, and test plans
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  document-types: SRS, SAS, SDS, SQAP, SCMP
---

## What I do

I provide templates and guidelines for all mandatory EN 50128 documentation per Section 5:
- Software Requirements Specification (SRS)
- Software Architecture Specification (SAS)
- Software Design Specification (SDS)
- Software Quality Assurance Plan (SQAP)
- Software Configuration Management Plan (SCMP)
- Test plans and reports
- Verification and validation documentation

## When to use me

Use this skill when:
- Creating any EN 50128 mandatory document
- Reviewing document completeness
- Ensuring document consistency
- Preparing deliverable packages
- Supporting certification activities

## EN 50128 Documentation Requirements

**All documentation requirements are based on:**
- **EN 50128:2011 Annex C** - Document requirements table
- **Table A.2** - Requirements specification techniques
- **Table A.3** - Architecture and design techniques
- **Table A.4** - Implementation techniques
- **Table A.5** - Verification and testing techniques
- **Table A.6** - Integration techniques
- **Table A.7** - Validation techniques
- **Table A.8** - Software analysis techniques
- **Table A.9** - Quality assurance techniques (3 MANDATORY for ALL SILs)
- **Table A.21** - Test coverage requirements

**Standard Reference:** `std/EN50128-2011.md` Annex C, all technique tables

## Mandatory Documentation by Phase

### Phase 1: Planning
- [ ] Software Quality Assurance Plan (SQAP)
- [ ] Software Configuration Management Plan (SCMP)
- [ ] Software Verification Plan (SVP)
- [ ] Software Validation Plan (SVaP)

### Phase 2: Requirements
- [ ] Software Requirements Specification (SRS)
- [ ] Requirements Traceability Matrix
- [ ] Requirements Verification Report

### Phase 3: Design
- [ ] Software Architecture Specification (SAS)
- [ ] Software Design Specification (SDS)
- [ ] Interface Specifications
- [ ] Design Verification Report

### Phase 4: Implementation
- [ ] Source Code
- [ ] Unit Test Specifications
- [ ] Unit Test Reports
- [ ] Code Review Records

### Phase 5: Testing
- [ ] Integration Test Specification
- [ ] Integration Test Report
- [ ] System Test Specification
- [ ] System Test Report
- [ ] Coverage Reports

### Phase 6: Validation
- [ ] Validation Test Specification
- [ ] Validation Test Report
- [ ] Software Assessment Report

## Document Template Structure

### Standard Header

```markdown
# [Document Title]

| Field | Value |
|-------|-------|
| Document ID | [DOC-XXX-YYY] |
| Version | [X.Y] |
| Date | [YYYY-MM-DD] |
| Author | [Name, Role] |
| Reviewer | [Name, Role] |
| Approver | [Name, Role] |
| SIL Level | [0-4] |
| Status | [Draft|Review|Approved|Baseline] |

## Document Control

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft |
| 1.0 | YYYY-MM-DD | [Name] | First approved version |

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Author | | | |
| Reviewer | | | |
| QA Manager | | | |
| Safety Manager | | | |
```

## Software Requirements Specification (SRS) Template

```markdown
# Software Requirements Specification

## 1. Introduction
### 1.1 Purpose
### 1.2 Scope
### 1.3 Definitions and Acronyms
### 1.4 References
### 1.5 Overview

## 2. General Description
### 2.1 System Context
### 2.2 System Functions
### 2.3 User Characteristics
### 2.4 Constraints
### 2.5 Assumptions and Dependencies

## 3. System Requirements

### 3.1 Functional Requirements
#### 3.1.1 [Function Group]
- REQ-FUNC-001: [Requirement]

### 3.2 Performance Requirements
- REQ-PERF-001: [Timing requirement]

### 3.3 Interface Requirements
#### 3.3.1 Hardware Interfaces
- REQ-IF-HW-001: [Requirement]

#### 3.3.2 Software Interfaces
- REQ-IF-SW-001: [Requirement]

### 3.4 Safety Requirements
- REQ-SAFE-001: [Safety requirement with SIL]

### 3.5 C Language Constraints
- Data types: Fixed-width types (uint8_t, etc.)
- Memory: Static allocation (SIL 2+)
- Error handling: Explicit return codes

## 4. Verification
### 4.1 Verification Methods
### 4.2 Requirements Traceability Matrix

## 5. Appendices
```

## Software Architecture Specification (SAS) Template

```markdown
# Software Architecture Specification

## 1. Introduction
### 1.1 Purpose
### 1.2 Scope
### 1.3 SIL Classification

## 2. Architecture Overview
### 2.1 System Context Diagram
### 2.2 Architecture Goals
### 2.3 Architecture Patterns

## 3. Architecture Description
### 3.1 Logical Architecture
- Component diagram
- Module descriptions (C modules)
- Interface specifications

### 3.2 Process Architecture
- Task allocation
- Inter-process communication

### 3.3 Data Architecture
- Data model
- Data structures (C structs)
- Static data allocation

## 4. Safety Architecture
### 4.1 Safety Functions
### 4.2 Redundancy and Diversity
### 4.3 Fault Detection
### 4.4 Safe States

## 5. C Implementation Constraints
- Static memory allocation only (SIL 2+)
- No recursion (highly recommended SIL 3-4)
- MISRA C:2012 compliance
- Cyclomatic complexity limits

## 6. Verification
### 6.1 Traceability to Requirements
```

## Software Design Specification (SDS) Template

```markdown
# Software Design Specification

## 1. Introduction
### 1.1 Purpose
### 1.2 SIL Level

## 2. Module Designs

### 2.1 Module: [Name]

**Identifier**: MOD-[ID]
**SIL Level**: [0-4]
**Implements**: REQ-[IDs]
**C Files**: [module.h, module.c]

#### Purpose
[Module responsibility]

#### Interfaces
**Input**: [Parameters]
**Output**: [Return values]
**Dependencies**: [Other modules]

#### Data Structures
```c
typedef struct {
    uint32_t field1;
    bool field2;
} module_state_t;
```

#### Functions
```c
error_t module_init(module_state_t* state);
error_t module_process(module_state_t* state, input_t* input);
```

#### Error Handling
- [Error detection mechanisms]
- [Error recovery strategies]

#### Complexity
- Cyclomatic complexity: [Value] (limit: [10/15/20])

## 3. Traceability
| Design Element | Requirements | Code Location |
|----------------|--------------|---------------|
| MOD-001 | REQ-FUNC-001 | brake.c |
```

## Software Test Plan Template

```markdown
# Software Test Plan

## 1. Introduction
### 1.1 Purpose
### 1.2 Scope
### 1.3 SIL Level
### 1.4 Test Framework: Unity (C)

## 2. Test Items
### 2.1 Software Under Test
### 2.2 Features to be Tested

## 3. Test Approach
### 3.1 Test Levels
- Component testing (Unity framework)
- Integration testing
- System testing

### 3.2 Coverage Criteria
- SIL 2: Statement 100%, Branch 100%
- SIL 3-4: Statement 100%, Branch 100%, Condition 100%

### 3.3 Tools
- Unity test framework
- gcov/lcov for coverage

## 4. Test Environment
### 4.1 Hardware Requirements
### 4.2 Software Requirements
### 4.3 Test Tools

## 5. Test Deliverables
- Test specifications
- Test reports
- Coverage reports

## 6. Traceability
| Requirement | Test Cases |
|-------------|------------|
| REQ-FUNC-001 | TC-UNIT-001, TC-UNIT-002 |
```

## Software Quality Assurance Plan (SQAP) Template

```markdown
# Software Quality Assurance Plan

## 1. Introduction
### 1.1 Purpose
### 1.2 SIL Classification

## 2. Quality Objectives
### 2.1 Quality Goals
### 2.2 Quality Metrics

## 3. Organization
### 3.1 QA Organization
### 3.2 Roles and Responsibilities
### 3.3 Independence Requirements (SIL 3-4)

## 4. Quality Activities
### 4.1 Reviews and Audits
- Document reviews
- Code reviews (mandatory for all code)
- Design reviews

### 4.2 Verification Activities
- Static analysis (PC-lint, Cppcheck)
- Dynamic testing
- MISRA C compliance checking

## 5. Quality Standards
### 5.1 Coding Standards
- MISRA C:2012 (mandatory SIL 2+)
- Fixed-width types
- No dynamic memory (SIL 2+)

### 5.2 Documentation Standards
- EN 50128 templates

## 6. Problem Reporting
### 6.1 Defect Tracking
### 6.2 Corrective Actions
```

## Document Review Checklist

### General Quality
- [ ] Follows standard template
- [ ] All sections complete
- [ ] Version control maintained
- [ ] Approvals present
- [ ] References correct
- [ ] Acronyms defined

### Technical Content
- [ ] Accurate and complete
- [ ] SIL level stated
- [ ] Requirements traceable
- [ ] Consistent with related docs
- [ ] EN 50128 compliance demonstrated

### Safety Critical (SIL 3-4)
- [ ] Independent review performed
- [ ] Safety analysis included
- [ ] Hazards addressed
- [ ] Verification evidence provided

## References
- EN 50128:2011 Section 5 (Documentation)
- EN 50128:2011 Annex B (Document Guidelines)
- ISO/IEC 15289 (Documentation Management)
