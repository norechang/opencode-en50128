# EN 50128 Software Development Lifecycle

This document defines the complete software development lifecycle for EN 50128:2011 compliant railway safety software development. All projects in this workspace SHALL follow this lifecycle.

## Document Information

| Property | Value |
|----------|-------|
| **Standard** | EN 50128:2011 Railway Software Standard |
| **Section** | Section 6: Software Lifecycle Issues |
| **Lifecycle Model** | V-Model (Mandatory for SIL 2-4) |
| **Language** | C (MISRA C:2012 for SIL 2+) |
| **Version** | 1.0 |

---

## 1. Lifecycle Overview

### 1.1 EN 50128 V-Model

The V-Model is MANDATORY for SIL 2-4 and shows the relationship between development phases (left side) and verification/validation phases (right side).

```
┌─────────────────────────────────────────────────────────────────┐
│                    EN 50128 V-Model Lifecycle                   │
└─────────────────────────────────────────────────────────────────┘

    System Requirements ────────────────────► System Validation
           │                                        ▲
           │                                        │
           ▼                                        │
    Software Requirements ──────────────► Software Validation
    (SRS - Section 7.2)                    (Section 7.6)
           │                                        ▲
           │                                        │
           ▼                                        │
    Software Architecture ──────────────► Integration Testing
    (SAS - Section 7.3)                    (Section 7.5)
           │                                        ▲
           │                                        │
           ▼                                        │
    Software Design ────────────────────► Module Testing
    (SDS - Section 7.3)                    (Section 7.4)
           │                                        ▲
           │                                        │
           ▼                                        │
    Implementation ─────────────────────► Unit Testing
    (Code - Section 7.4)                   (Section 7.4)
           │                                        │
           └────────────────────────────────────────┘

    ◄────────── Verification (Section 6.4) Throughout ──────────►
    ◄────────── Quality Assurance (Section 6.3) Throughout ──────►
    ◄────────── Safety Management Throughout ────────────────────►
```

### 1.2 Lifecycle Phases

The EN 50128 lifecycle consists of the following phases:

1. **Software Planning** (Section 6.2)
2. **Software Requirements** (Section 7.2)
3. **Software Architecture & Design** (Section 7.3)
4. **Software Implementation & Testing** (Section 7.4)
5. **Software Integration** (Section 7.5)
6. **Software Validation** (Section 7.6)
7. **Software Assessment** (Section 6.5)
8. **Software Deployment & Maintenance** (Section 7.7, 7.8)

---

## 2. Phase 1: Software Planning (Section 6.2)

### 2.1 Objectives
- Define project organization and responsibilities
- Establish quality assurance plan
- Define verification and validation strategies
- Establish configuration management
- Determine SIL levels

### 2.2 Key Activities
1. Establish Software Quality Assurance Plan (SQAP)
2. Establish Software Configuration Management Plan (SCMP)
3. Establish Software Verification Plan (SVP)
4. Establish Software Validation Plan (SVaP)
5. Define project standards and guidelines

### 2.3 Agents Involved
- Project Manager (overall project responsibility per EN 50128 Section 5, Table B.9)
- Software Manager (software development responsibility per EN 50128 Section 5.3.1)
- Configuration Manager (CM per EN 50128 Section 5, Table B.10)
- Quality Assurance (`/qua`)
- Safety Engineer (`/saf`)

**Note**: EN 50128 defines both "Project Manager" (Table B.9) and "Software Manager" (Section 5.3.1). Project Manager has overall project responsibility, while Software Manager focuses on software development activities.

### 2.4 Deliverables
- [ ] Software Quality Assurance Plan (SQAP)
- [ ] Software Configuration Management Plan (SCMP)
- [ ] Software Verification Plan (SVP)
- [ ] Software Validation Plan (SVaP)
- [ ] Project Standards Document
- [ ] Tool Qualification Plan (if applicable)

### 2.5 EN 50128 References
- Section 6.2: Software quality assurance
- Section 6.3: Software configuration and change management
- Table A.1: Software lifecycle phases and related documents

### 2.6 Entry Criteria
- System requirements available
- SIL level determined
- Project authorization obtained

### 2.7 Exit Criteria
- All planning documents approved
- Quality gates defined
- Verification/validation strategies established
- Configuration management in place

---

## 3. Phase 2: Software Requirements (Section 7.2)

### 3.1 Objectives
- Define complete, unambiguous software requirements
- Establish requirements traceability
- Assign SIL levels to requirements
- Identify safety requirements

### 3.2 Key Activities
1. Elicit requirements from stakeholders and system specification
2. Write Software Requirements Specification (SRS)
3. Establish requirements traceability matrix
4. Perform hazard analysis
5. Define safety requirements
6. Review and approve requirements

### 3.3 Agents Involved
- Requirements Engineer (`/req`) - PRIMARY
- Safety Engineer (`/saf`)
- Quality Assurance (`/qua`)

### 3.4 Skills Required
- `en50128-requirements` - Requirements engineering patterns
- `en50128-safety` - Hazard analysis and safety requirements
- `en50128-documentation` - SRS templates

### 3.5 Deliverables
- [ ] Software Requirements Specification (SRS)
- [ ] Requirements Traceability Matrix (RTM)
- [ ] Hazard Log
- [ ] Safety Requirements Specification
- [ ] Requirements Review Report

### 3.6 Requirements Quality Checklist
- [ ] All requirements unambiguous
- [ ] All requirements testable
- [ ] All requirements traceable
- [ ] SHALL/SHOULD/MAY keywords used correctly
- [ ] SIL levels assigned
- [ ] C language constraints considered
- [ ] Safety requirements identified

### 3.7 EN 50128 References
- Section 7.2: Software requirements
- Table A.3: Software requirements specification techniques
- Table A.16: Defensive programming

### 3.8 Entry Criteria
- System requirements available
- SQAP approved
- Verification plan approved

### 3.9 Exit Criteria
- SRS complete and approved
- All requirements traceable to system requirements
- Requirements review passed
- Hazard analysis complete

---

## 4. Phase 3: Software Architecture & Design (Section 7.3)

### 4.1 Objectives
- Define software architecture
- Design software modules and interfaces
- Ensure design meets requirements
- Apply defensive programming principles

### 4.2 Key Activities
1. Create Software Architecture Specification (SAS)
2. Create Software Design Specification (SDS)
3. Define module interfaces
4. Design data structures (static allocation for SIL 2+)
5. Define error handling strategy
6. Perform design reviews
7. Establish complexity limits

### 4.3 Agents Involved
- Designer (`/des`) - PRIMARY
- Safety Engineer (`/saf`)
- Quality Assurance (`/qua`)
- Requirements Engineer (`/req`) - for traceability

### 4.4 Skills Required
- `en50128-design` - Architecture and design patterns
- `en50128-safety` - Safety analysis (FMEA/FTA)
- `en50128-implementation` - MISRA C design patterns

### 4.5 Deliverables
- [ ] Software Architecture Specification (SAS)
- [ ] Software Design Specification (SDS)
- [ ] Interface Control Document (ICD)
- [ ] Design Traceability Matrix
- [ ] Design Review Report
- [ ] FMEA/FTA Results (SIL 3-4)

### 4.6 Design Constraints by SIL

#### SIL 2+ Mandatory Constraints
- Static memory allocation ONLY (no malloc/free)
- Fixed-width integer types (uint8_t, uint16_t, uint32_t)
- Defensive programming mandatory
- Error handling for all functions
- Modular design

#### SIL 3-4 Additional Constraints
- Cyclomatic complexity ≤ 10 per function
- No recursion (highly recommended)
- Redundant safety mechanisms
- Independent verification required

### 4.7 Design Review Checklist
- [ ] Architecture traceable to requirements
- [ ] Module interfaces clearly defined
- [ ] Static allocation used (SIL 2+)
- [ ] Complexity limits defined
- [ ] Error handling comprehensive
- [ ] MISRA C compliance considered
- [ ] Safety mechanisms designed

### 4.8 EN 50128 References
- Section 7.3: Software architecture and design
- Table A.4: Software design and implementation methods
- Table A.16: Defensive programming
- Table A.17: Failure assertion programming
- Table A.18: Modular approach

### 4.9 Entry Criteria
- SRS approved
- Design standards defined
- FMEA/FTA planned (SIL 3-4)

### 4.10 Exit Criteria
- SAS and SDS complete and approved
- Design traceable to requirements
- Design review passed
- Complexity limits established

---

## 5. Phase 4: Software Implementation & Testing (Section 7.4)

### 5.1 Objectives
- Implement software modules in C
- Ensure MISRA C:2012 compliance
- Develop unit tests
- Achieve required coverage

### 5.2 Key Activities
1. Implement C code following MISRA C:2012
2. Write unit tests (Unity framework)
3. Execute unit tests
4. Measure code coverage
5. Perform static analysis
6. Conduct code reviews
7. Document code

### 5.3 Agents Involved
- Implementer (`/imp`) - PRIMARY
- Tester (`/tst`)
- Verifier (`/ver`)
- Quality Assurance (`/qua`)

### 5.4 Skills Required
- `en50128-implementation` - MISRA C coding patterns
- `en50128-testing` - Unit testing with Unity
- `en50128-verification` - Static analysis
- `en50128-design` - Design patterns reference

### 5.5 Deliverables
- [ ] Source Code (*.c, *.h)
- [ ] Unit Test Code
- [ ] Unit Test Results
- [ ] Code Coverage Report (100% for SIL 3-4)
- [ ] Static Analysis Report (PC-lint/Cppcheck)
- [ ] Complexity Analysis Report (Lizard)
- [ ] Code Review Report
- [ ] Implementation Traceability Matrix

### 5.6 MISRA C:2012 Compliance

#### Mandatory for SIL 2+
- All mandatory rules: ZERO violations
- Required rules: Violations must be justified
- Advisory rules: Recommended

#### Key MISRA Rules
- **Rule 21.3**: No dynamic memory allocation
- **Rule 17.7**: Check all function return values
- **Rule 4.6**: Use fixed-width types
- **Rule 14.4**: Boolean conditions explicit
- **Rule 8.7**: Internal linkage when possible

### 5.7 Coverage Requirements by SIL

| SIL Level | Statement | Branch | MC/DC | Notes |
|-----------|-----------|--------|-------|-------|
| SIL 0-1 | 80% | 70% | - | Recommended |
| SIL 2 | 100% | 100% | - | Mandatory |
| SIL 3-4 | 100% | 100% | 100% | Mandatory |

### 5.8 Implementation Checklist
- [ ] MISRA C:2012 compliant (zero mandatory violations)
- [ ] Static allocation only (SIL 2+)
- [ ] No recursion
- [ ] All pointers validated
- [ ] All return values checked
- [ ] Cyclomatic complexity ≤ limit
- [ ] Unit tests written
- [ ] Coverage requirements met
- [ ] Static analysis clean
- [ ] Code reviewed and approved

### 5.9 EN 50128 References
- Section 7.4: Software component design and implementation
- Table A.4: Design and implementation methods
- Table A.5: Verification methods
- Table A.16: Defensive programming
- MISRA C:2012 Guidelines

### 5.10 Entry Criteria
- SDS approved
- Coding standards defined
- Unit test framework ready
- Static analysis tools configured

### 5.11 Exit Criteria
- All code implemented and reviewed
- Unit tests pass
- Coverage requirements met
- Static analysis clean
- Code traceable to design

---

## 6. Phase 5: Software Integration (Section 7.5)

### 6.1 Objectives
- Integrate software modules
- Perform integration testing
- Verify interfaces
- Validate overall functionality

### 6.2 Key Activities
1. Integrate modules incrementally
2. Execute integration tests
3. Test module interfaces
4. Verify system behavior
5. Resolve integration issues

### 6.3 Agents Involved
- Tester (`/tst`) - PRIMARY
- Implementer (`/imp`)
- Designer (`/des`)
- Verifier (`/ver`)

### 6.4 Skills Required
- `en50128-testing` - Integration testing strategies
- `en50128-verification` - Integration verification

### 6.5 Deliverables
- [ ] Integration Test Specification
- [ ] Integration Test Results
- [ ] Integration Coverage Report
- [ ] Issue Resolution Log
- [ ] Integrated Software Baseline

### 6.6 Integration Testing Checklist
- [ ] All modules integrated
- [ ] Interface tests executed
- [ ] Data flow verified
- [ ] Error handling tested
- [ ] Performance requirements met
- [ ] Integration issues resolved

### 6.7 EN 50128 References
- Section 7.5: Software integration
- Table A.5: Verification and testing methods

### 6.8 Entry Criteria
- All modules unit tested
- Integration test plan approved
- Integration environment ready

### 6.9 Exit Criteria
- All integration tests pass
- Interfaces verified
- Software baseline established
- Ready for validation

---

## 7. Phase 6: Software Validation (Section 7.6)

### 7.1 Objectives
- Validate software meets requirements
- Validate in operational environment
- Obtain customer acceptance
- Demonstrate safety requirements

### 7.2 Key Activities
1. Execute validation test suite
2. Perform operational scenario testing
3. Conduct user acceptance testing
4. Validate safety requirements
5. Perform performance testing

### 7.3 Agents Involved
- Validator (`/val`) - PRIMARY (must be independent for SIL 3-4)
- Tester (`/tst`)
- Safety Engineer (`/saf`)
- Customer/End User

### 7.4 Skills Required
- `en50128-validation` - System testing and UAT
- `en50128-safety` - Safety validation
- `en50128-testing` - Test execution

### 7.5 Deliverables
- [ ] Software Validation Report
- [ ] Validation Test Results
- [ ] User Acceptance Test Results
- [ ] Safety Validation Report
- [ ] Performance Test Results
- [ ] Acceptance Certificate

### 7.6 Validation Testing Checklist
- [ ] All requirements validated
- [ ] Operational scenarios tested
- [ ] Safety requirements validated
- [ ] Performance requirements met
- [ ] User acceptance obtained
- [ ] Validation independent (SIL 3-4)

### 7.7 EN 50128 References
- Section 7.6: Software validation
- Table A.5: Validation methods

### 7.8 Entry Criteria
- Integration complete
- Validation plan approved
- Target environment available
- Independent validator assigned (SIL 3-4)

### 7.9 Exit Criteria
- All validation tests pass
- Customer acceptance obtained
- Safety requirements validated
- Validation report approved

---

## 8. Phase 7: Software Verification (Continuous)

### 8.1 Objectives
- Verify correctness throughout lifecycle
- Ensure compliance with standards
- Collect objective evidence
- Maintain quality

### 8.2 Key Activities (Throughout Lifecycle)
1. Perform static analysis
2. Conduct design reviews
3. Conduct code reviews
4. Verify traceability
5. Check complexity
6. Verify coverage
7. Collect evidence

### 8.3 Agents Involved
- Verifier (`/ver`) - PRIMARY (must be independent for SIL 3-4)
- Quality Assurance (`/qua`)
- All other agents (peer verification)

### 8.4 Skills Required
- `en50128-verification` - Static analysis, verification methods
- `en50128-quality` - QA processes

### 8.5 Deliverables
- [ ] Software Verification Report
- [ ] Static Analysis Reports
- [ ] Review Records
- [ ] Traceability Verification
- [ ] Complexity Analysis
- [ ] Coverage Reports
- [ ] Verification Evidence Package

### 8.6 Verification Checklist
- [ ] Requirements verification complete
- [ ] Design verification complete
- [ ] Code verification complete
- [ ] Test verification complete
- [ ] Traceability verified
- [ ] MISRA C compliance verified
- [ ] Coverage verified
- [ ] Independent verification (SIL 3-4)

### 8.7 EN 50128 References
- Section 6.4: Software verification
- Table A.5: Verification and testing methods

### 8.8 Independence Requirements

| SIL Level | Verification Independence |
|-----------|---------------------------|
| SIL 0-1 | Not required |
| SIL 2 | Highly recommended |
| SIL 3-4 | Mandatory |

---

## 9. Phase 8: Software Assessment (Section 6.5)

### 9.1 Objectives
- Assess overall software quality
- Verify compliance with EN 50128
- Determine readiness for deployment
- Obtain safety approval

### 9.2 Key Activities
1. Review all lifecycle artifacts
2. Assess compliance with EN 50128
3. Review verification evidence
4. Review validation results
5. Assess safety case
6. Prepare assessment report

### 9.3 Agents Involved
- **Assessor** (independent, mandatory for SIL 3-4, per EN 50128 Section 5.3.8, Table B.8)
- **Project Manager** (overall project responsibility)
- **Software Manager** (software development responsibility)
- Quality Assurance (`/qua`)

**Note**: The Assessor role is explicitly defined in EN 50128 Section 5.3.8 and MUST be completely independent for SIL 3-4.

### 9.4 Deliverables
- [ ] Software Assessment Report
- [ ] Compliance Matrix
- [ ] Safety Case
- [ ] Approval Certificate
- [ ] Deployment Authorization

### 9.5 Assessment Checklist
- [ ] All lifecycle phases complete
- [ ] All deliverables produced
- [ ] Traceability complete
- [ ] Verification complete
- [ ] Validation complete
- [ ] MISRA C compliance verified
- [ ] Coverage requirements met
- [ ] Safety requirements satisfied
- [ ] EN 50128 compliance demonstrated

### 9.6 EN 50128 References
- Section 6.5: Software assessment
- Table A.1: Lifecycle requirements

---

## 10. Lifecycle Workflow Examples

### 10.1 Example: Complete SIL 3 Project Workflow

```bash
# Phase 1: Planning
# (Establish SQAP, SCMP, plans)

# Phase 2: Requirements
/req
# Create SRS, requirements.md
# Establish traceability
# Perform hazard analysis

# Phase 3: Design
/des
# Create SAS/SDS
# Design architecture and modules
# Define interfaces

# Phase 4: Implementation & Unit Testing
/imp
# Implement C code (MISRA C compliant)
# Write unit tests

/tst
# Execute unit tests
# Measure coverage (100% for SIL 3)

/ver
# Run static analysis
# Verify complexity
# Code review

# Phase 5: Integration
/tst
# Integration testing
# Interface verification

# Phase 6: Validation
/val
# System testing
# UAT
# Safety validation

# Phase 7: Verification (continuous)
/ver
# Collect evidence
# Verify traceability
# Generate verification report

# Phase 8: Assessment
/qua
# Software assessment
# Compliance verification
# Deployment approval
```

### 10.2 Example: Quick Prototyping (SIL 0-1)

```bash
# Simplified workflow for lower SIL levels
/req  # Define basic requirements
/des  # Basic design
/imp  # Implement and test
/tst  # Test with 80% coverage
```

---

## 11. Traceability Requirements

### 11.1 Mandatory Traceability Links

```
System Requirements
        ↓
Software Requirements (SRS)
        ↓
Software Architecture (SAS)
        ↓
Software Design (SDS)
        ↓
Source Code (*.c, *.h)
        ↓
Unit Tests
        ↓
Integration Tests
        ↓
Validation Tests
```

### 11.2 Bidirectional Traceability

All traceability MUST be bidirectional:
- Forward: Requirement → Design → Code → Test
- Backward: Test → Code → Design → Requirement

### 11.3 Traceability Matrix Example

| Requirement | Design Module | Source File | Test Case | Status |
|-------------|---------------|-------------|-----------|--------|
| REQ-FUNC-001 | door_control | door_control.c | TC-001 | ✓ |
| REQ-SAFE-001 | fail_safe | door_control.c | TC-010 | ✓ |

---

## 12. Quality Gates

### 12.1 Phase Gate Criteria

Each phase has entry and exit criteria (quality gates) that MUST be satisfied:

| Phase | Entry Gate | Exit Gate |
|-------|------------|-----------|
| Requirements | System req available | SRS approved |
| Design | SRS approved | SAS/SDS approved |
| Implementation | SDS approved | Code reviewed, tests pass |
| Integration | Unit tests pass | Integration tests pass |
| Validation | Integration complete | Customer acceptance |

### 12.2 Quality Gate Reviews

All quality gates require:
- [ ] Deliverables complete
- [ ] Reviews passed
- [ ] Traceability verified
- [ ] Quality metrics met
- [ ] Approvals obtained

---

## 13. Documentation Requirements

### 13.1 Mandatory Documents by Phase

| Phase | Mandatory Documents |
|-------|---------------------|
| Planning | SQAP, SCMP, SVP, SVaP |
| Requirements | SRS, RTM, Hazard Log |
| Design | SAS, SDS, ICD |
| Implementation | Source Code, Unit Tests, Coverage Report |
| Integration | Integration Test Report |
| Validation | Validation Report, UAT Results |
| Verification | Verification Report, Evidence Package |
| Assessment | Assessment Report, Safety Case |

### 13.2 Document Templates

Templates available in:
- `docs/templates/` - Generic templates
- `.opencode/skills/en50128-documentation/` - EN 50128 specific templates

---

## 14. Tool Qualification

### 14.1 Tool Categories (EN 50128 Section 6.7)

**T1**: Tools generating code → Requires qualification
**T2**: Tools supporting testing → May require qualification
**T3**: Development tools → Typically no qualification required

### 14.2 Tools Used in This Workspace

| Tool | Category | Qualification Required | Status |
|------|----------|------------------------|--------|
| GCC | T1 | Yes (SIL 3-4) | Industry accepted |
| Unity | T2 | Recommended | Open source |
| Cppcheck | T3 | No | - |
| PC-lint Plus | T3 | No | - |
| gcov/lcov | T2 | Recommended | Industry accepted |

---

## 15. Configuration Management

### 15.1 Version Control

All artifacts SHALL be under version control:
- Source code (Git)
- Requirements (Git)
- Design documents (Git)
- Test artifacts (Git)

### 15.2 Baseline Management

Baselines SHALL be established at:
- Requirements freeze
- Design freeze
- Code freeze
- Release

### 15.3 Change Management

All changes SHALL:
1. Be documented
2. Be reviewed
3. Impact assessment performed
4. Traceability updated
5. Regression testing performed

---

## 16. SIL-Specific Requirements Summary

### 16.1 SIL 0-1 (Low Safety Integrity)

| Aspect | Requirement |
|--------|-------------|
| Lifecycle | V-Model recommended |
| Independence | Not required |
| Coverage | 80% statement, 70% branch |
| MISRA C | Recommended |
| Complexity | ≤ 20 |

### 16.2 SIL 2 (Medium Safety Integrity)

| Aspect | Requirement |
|--------|-------------|
| Lifecycle | V-Model mandatory |
| Independence | Highly recommended |
| Coverage | 100% statement, 100% branch |
| MISRA C | Mandatory |
| Complexity | ≤ 15 |
| Static Analysis | Mandatory |

### 16.3 SIL 3-4 (High Safety Integrity)

| Aspect | Requirement |
|--------|-------------|
| Lifecycle | V-Model mandatory |
| Independence | Mandatory (verification & validation) |
| Coverage | 100% statement, branch, MC/DC |
| MISRA C | Mandatory |
| Complexity | ≤ 10 |
| Static Analysis | Mandatory |
| FMEA/FTA | Mandatory |
| No Recursion | Highly recommended |
| No Dynamic Memory | Mandatory |

---

## 17. References

### 17.1 Standards
- EN 50128:2011 - Railway applications - Software for railway control and protection systems
- EN 50126:2017 - Railway applications - RAMS
- IEC 61508 - Functional safety
- MISRA C:2012 - Guidelines for the use of C

### 17.2 Related Documents
- `AGENTS.md` - Role-based agents
- `.opencode/skills/` - Domain-specific skills
- `.opencode/commands/` - Agent command definitions
- `docs/EN50128-Compliance-Guide.md` - Compliance checklist

---

## 18. Revision History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2026-02-06 | EN50128 Team | Initial lifecycle definition |

---

**Document Status**: Approved  
**Next Review**: [Date]  
**Approval**: [Signature]
