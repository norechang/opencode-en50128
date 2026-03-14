# Safety Case Development Workflow

## Document Control

**Workflow**: Safety Case Development for EN 50128 Railway Software  
**Skill**: en50128-safety  
**Version**: 2.0  
**Date**: 2026-03-14  
**Status**: Phase 2 Enhanced

## Table of Contents

1. [Purpose and Scope](#1-purpose-and-scope)
2. [EN 50128 and EN 50126 Applicability](#2-en-50128-and-en-50126-applicability)
3. [Safety Case Structure](#3-safety-case-structure)
4. [Goal Structuring Notation (GSN)](#4-goal-structuring-notation-gsn)
5. [Top-Level Safety Argument](#5-top-level-safety-argument)
6. [Evidence Collection](#6-evidence-collection)
7. [Assurance Argument](#7-assurance-argument)
8. [Safety Case Review and Approval](#8-safety-case-review-and-approval)
9. [Safety Case Example](#9-safety-case-example)
10. [Tool Integration](#10-tool-integration)
11. [Example Scenario: Train Control Safety Case](#11-example-scenario-train-control-safety-case)

---

## 1. Purpose and Scope

### 1.1 Safety Case Definition

A **Safety Case** is a structured argument, supported by evidence, that demonstrates a system is acceptably safe for a given application in a given environment.

**Key Components**:
1. **Claims**: Statements about system safety (e.g., "System is acceptably safe")
2. **Arguments**: Logical reasoning linking claims to evidence
3. **Evidence**: Objective data supporting claims (test results, analysis, reviews)

### 1.2 Safety Case Objectives

For EN 50128 compliant railway software:

1. **Demonstrate Compliance**: Show EN 50128/EN 50126 requirements met
2. **Support Certification**: Provide evidence for independent assessment (SIL 3-4)
3. **Risk Communication**: Communicate residual risks to stakeholders
4. **Lifecycle Documentation**: Document safety rationale throughout V-Model
5. **Regulatory Approval**: Obtain authorization from railway safety authority

### 1.3 Safety Case Audience

**Primary Audiences**:
- **Independent Assessor** (MANDATORY SIL 3-4) - Reviews and approves safety case
- **Railway Safety Authority** - Grants operational authorization
- **Operator/Customer** - Accepts system for deployment

**Secondary Audiences**:
- **Maintenance Engineers** - Understand safety constraints
- **Incident Investigators** - Reference during accident investigation
- **Future Developers** - Understand safety rationale for modifications

### 1.4 When to Develop Safety Case

**Progressive Development** (aligned with V-Model phases):

| Phase | Safety Case Activity | Deliverable |
|-------|---------------------|-------------|
| **Phase 1: Planning** | Define safety case structure, top-level claims | Safety Case Plan |
| **Phase 2: Requirements** | Develop safety requirements argument | Preliminary Safety Case |
| **Phase 3-4: Design/Implementation** | Add design and implementation evidence | Interim Safety Case |
| **Phase 5-6: Integration/Validation** | Add test evidence, complete argument | Final Safety Case (Draft) |
| **Phase 7: Assessment** | Independent review, address findings | Final Safety Case (Approved) |
| **Phase 8: Deployment** | Operational evidence, residual risk statement | Safety Case (Operational) |

**Safety Case is ITERATIVE**: Updated as evidence becomes available throughout lifecycle.

---

## 2. EN 50128 and EN 50126 Applicability

### 2.1 EN 50128 Requirements

**Section 5.1.2.8: Validator**
- "The Validator shall give agreement/disagreement for the software release"
- Validation Report is key evidence in safety case

**Section 6.2: Verification**
- Verification evidence (static analysis, reviews, tests) supports safety case

**Section 7.7: Overall Software Testing and Validation**
- System test results provide evidence of correct operation

**Table A.7: Overall Software Testing/Validation Techniques**

| Technique | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | Reference |
|-----------|-------|-------|-------|-------|-------|-----------|
| Safety Case | - | R | **HR** | **HR** | **M** | - |

**Interpretation**:
- **SIL 4**: **MANDATORY** - Safety case required for certification
- **SIL 3**: **Highly Recommended** - Rationale required if not produced
- **SIL 2**: Recommended - Often required by railway operators
- **SIL 0-1**: Optional

### 2.2 EN 50126 Requirements

**EN 50126-1:2017 Section 8**: System Acceptance
- Safety case supports system acceptance decision
- Demonstrates RAMS requirements achieved

**EN 50126-2:2017 Section 10.5**: Safety Validation
- Validation provides evidence for safety case
- Safety case demonstrates THR (Tolerable Hazard Rate) achieved

### 2.3 Independent Assessment Requirement

**EN 50128 Section 5.1.2.9: Assessor**
- **SIL 3-4**: Independent safety assessment MANDATORY
- Assessor reviews safety case and provides Assessment Report
- Assessor SHALL NOT be part of development or V&V teams

**Assessment Report** (separate from Safety Case):
- Independent review of safety case completeness
- Verification of evidence validity
- Identification of gaps or weaknesses
- Approval recommendation (with conditions)

---

## 3. Safety Case Structure

### 3.1 Standard Safety Case Outline

```
1. EXECUTIVE SUMMARY
   - System overview
   - Safety claim summary
   - Assessment status

2. SYSTEM DESCRIPTION
   - System scope and boundaries
   - Operational environment
   - Safety-related functions

3. SAFETY REQUIREMENTS
   - SIL allocation
   - Safety requirements specification
   - Traceability to hazards

4. SAFETY ARGUMENT
   - Top-level safety claim
   - Argument decomposition (GSN diagram)
   - Sub-claims and strategies

5. EVIDENCE
   - Hazard analysis (PHA, FMEA, FTA)
   - Verification evidence (static analysis, reviews)
   - Validation evidence (system tests, operational scenarios)
   - Process evidence (EN 50128 compliance)

6. ASSURANCE ARGUMENT
   - Independence evidence
   - Competence evidence
   - Process compliance evidence

7. ASSUMPTIONS AND LIMITATIONS
   - Operational assumptions
   - Environmental constraints
   - Residual risks

8. CONCLUSIONS
   - Safety claim justified
   - Residual risk acceptable
   - Recommendations for operation

APPENDICES
   - Traceability matrices
   - Test reports
   - Verification reports
   - Tool qualification evidence
```

### 3.2 Safety Case Hierarchy

```
                    ┌─────────────────────────┐
                    │  TOP-LEVEL CLAIM        │
                    │ "System is acceptably   │
                    │  safe"                  │
                    └───────────┬─────────────┘
                                │
                    ┌───────────▼─────────────┐
                    │  ARGUMENT STRATEGY      │
                    │ "Decompose by lifecycle │
                    │  phase evidence"        │
                    └───────────┬─────────────┘
                                │
                ┌───────────────┼───────────────┐
                │               │               │
        ┌───────▼──────┐ ┌──────▼─────┐ ┌──────▼─────┐
        │ SUB-CLAIM 1  │ │ SUB-CLAIM 2│ │ SUB-CLAIM 3│
        │ (Requirements)│ │ (Design)   │ │ (Tests)    │
        └───────┬──────┘ └──────┬─────┘ └──────┬─────┘
                │               │               │
        ┌───────▼──────┐ ┌──────▼─────┐ ┌──────▼─────┐
        │  EVIDENCE 1  │ │ EVIDENCE 2 │ │ EVIDENCE 3 │
        │ (Hazard Log) │ │ (SAS, SDS) │ │ (Test Rpts)│
        └──────────────┘ └────────────┘ └────────────┘
```

### 3.3 Claims, Arguments, Evidence (CAE) Structure

**Claim**: A statement to be justified
- Example: "All identified hazards have been mitigated to acceptable levels"

**Argument**: Logical reasoning supporting the claim
- Example: "Decompose by hazard, show each hazard mitigated per Hazard Log"

**Evidence**: Objective data proving the claim
- Example: "Hazard Log shows all hazards with Residual Risk ≤ MEDIUM"

**CAE Example**:
```
CLAIM: Speed monitoring system is safe (SIL 3)

ARGUMENT: Decompose into sub-claims:
  1. All hazards identified (PHA, FMEA, FTA)
  2. All hazards mitigated (design measures, safety requirements)
  3. All mitigations verified (verification reports)
  4. All mitigations validated (system tests)

EVIDENCE:
  - Hazard Log (DOC-SAF-HAZLOG-001): 12 hazards identified, all mitigated
  - FMEA Report (DOC-SAF-FMEA-SPD-001): Failure modes analyzed, RPN < 100
  - FTA Report (DOC-SAF-FTA-SPD-001): No SPOFs, THR < 10^-7 per hour
  - Verification Report (DOC-VER-001): Static analysis zero critical defects
  - Validation Report (DOC-VAL-001): System tests passed, 100% coverage
```

---

## 4. Goal Structuring Notation (GSN)

### 4.1 GSN Overview

**Goal Structuring Notation (GSN)** is a graphical notation for representing safety arguments.

**Benefits**:
- **Visual**: Easier to understand than text-only argument
- **Structured**: Clear relationships between claims, arguments, evidence
- **Traceable**: Explicit links to evidence documents
- **Reviewable**: Independent assessor can follow argument flow

### 4.2 GSN Symbols

**Primary Symbols**:

| Symbol | Name | Description | Example |
|--------|------|-------------|---------|
| Rectangle (Goal) | Goal | Claim to be supported | G1: System is safe |
| Parallelogram (Strategy) | Strategy | Argument approach | S1: Argument by hazard analysis |
| Circle (Solution) | Solution | Evidence | Sn1: Hazard Log |
| Rounded Rectangle (Context) | Context | Scope, assumptions | C1: SIL 3 system |
| Ellipse (Justification) | Justification | Rationale for strategy | J1: Per EN 50128 Table A.8 |

**Relationships**:
- **SupportedBy**: Goal supported by sub-goals or evidence (solid arrow →)
- **InContextOf**: Goal applies within context (hollow arrow ⇢)

### 4.3 GSN Example

```
┌─────────────────────────────────────┐
│ G1: System is acceptably safe       │
│     for operation                   │
└──────────────┬──────────────────────┘
               │ SupportedBy
    ┌──────────▼──────────┐
    │ S1: Argument by     │
    │     hazard analysis │
    └──────────┬──────────┘
               │ SupportedBy
    ┌──────────┼──────────┐
    │          │          │
┌───▼───┐  ┌───▼───┐  ┌───▼───┐
│G2: All│  │G3: All│  │G4: All│
│hazards│  │hazards│  │miti-  │
│identi-│  │miti-  │  │gations│
│fied   │  │gated  │  │valid  │
└───┬───┘  └───┬───┘  └───┬───┘
    │          │          │ SupportedBy
 ┌──▼──┐    ┌──▼──┐    ┌──▼──┐
 │Sn1: │    │Sn2: │    │Sn3: │
 │Hazard│   │FMEA │    │Val  │
 │Log  │    │FTA  │    │Rpt  │
 └─────┘    └─────┘    └─────┘
```

### 4.4 GSN Patterns for Railway Software

**Pattern 1: Argument by Lifecycle Phase**
```
G1: Software is safe
  S1: Argument by V-Model phase
    G2: Requirements are safe (Phase 2)
    G3: Design is safe (Phase 3-4)
    G4: Implementation is safe (Phase 4)
    G5: System tests pass (Phase 6)
```

**Pattern 2: Argument by Hazard**
```
G1: All hazards mitigated
  S1: Argument over all hazards in Hazard Log
    G2: Hazard HAZ-SPD-001 mitigated
    G3: Hazard HAZ-BRK-001 mitigated
    G4: Hazard HAZ-DOOR-001 mitigated
    ...
```

**Pattern 3: Argument by EN 50128 Compliance**
```
G1: Software complies with EN 50128 SIL 3
  S1: Argument by EN 50128 lifecycle phases
    G2: SQAP followed (Section 6.5)
    G3: SCMP followed (Section 6.6)
    G4: Verification performed (Section 6.2)
    G5: Validation performed (Section 7.7)
```

---

## 5. Top-Level Safety Argument

### 5.1 Top-Level Safety Claim

**Generic Form**:
```
G1: System X is acceptably safe for application Y in environment Z
```

**Example (Train Control System)**:
```
G1: The Train Control System is acceptably safe for passenger train operations
    on the Metro North line at SIL 3
```

**Claim Characteristics**:
- **Specific**: Names the system, application, environment
- **Measurable**: "Acceptably safe" defined by SIL 3 THR (10^-7 per hour)
- **Scoped**: Metro North line (specific railway)
- **Qualified**: SIL 3 (safety integrity level)

### 5.2 Top-Level Argument Strategy

**Strategy Options**:

**Option 1: Argument by Hazard Analysis** (Recommended for safety-critical systems)
```
S1: Argument that all identified hazards have been mitigated to acceptable levels
    - Sub-goal for each hazard in Hazard Log
    - Evidence: Hazard analysis (PHA, FMEA, FTA)
```

**Option 2: Argument by Lifecycle Phase** (Recommended for EN 50128 compliance)
```
S1: Argument that all EN 50128 lifecycle phases completed successfully
    - Sub-goal for each phase (requirements, design, implementation, tests)
    - Evidence: Phase deliverables and reviews
```

**Option 3: Argument by Safety Requirement** (Alternative)
```
S1: Argument that all safety requirements have been satisfied
    - Sub-goal for each safety requirement
    - Evidence: Traceability from requirement → test
```

**Recommended**: **Combine Options 1 and 2** for comprehensive coverage.

### 5.3 Top-Level GSN Diagram

```
┌──────────────────────────────────────────────────────────────┐
│ G1: Train Control System is acceptably safe for passenger    │
│     train operations on Metro North line (SIL 3)             │
└────────────────────────────┬─────────────────────────────────┘
                             │ InContextOf
                  ┌──────────▼──────────┐
                  │ C1: SIL 3 system    │
                  │     per EN 50128    │
                  └─────────────────────┘
                             │ SupportedBy
                  ┌──────────▼──────────┐
                  │ S1: Argument by     │
                  │     hazard analysis │
                  │     and lifecycle   │
                  └──────────┬──────────┘
                             │ SupportedBy
                ┌────────────┼────────────┐
                │            │            │
        ┌───────▼─────┐  ┌───▼────┐  ┌───▼────┐
        │ G2: All     │  │ G3: EN │  │ G4: All│
        │ identified  │  │ 50128  │  │ safety │
        │ hazards     │  │ process│  │ reqmts │
        │ mitigated   │  │ followed│ │ met    │
        └─────────────┘  └────────┘  └────────┘
```

### 5.4 Context and Assumptions

**Context Elements** (define scope):
- **C1: SIL Level**: SIL 3 per EN 50128
- **C2: Application**: Passenger train operations
- **C3: Environment**: Metro North line (urban, max speed 120 km/h)
- **C4: Standards**: EN 50128:2011, EN 50126:2017, MISRA C:2012

**Assumptions** (must be validated):
- **A1**: Train operators follow operational procedures
- **A2**: Maintenance performed per schedule
- **A3**: Environmental conditions within design limits (-40°C to +70°C)
- **A4**: Hardware failure rates per manufacturer data sheets

**Document Assumptions**:
```markdown
## Assumptions

### A1: Train Operators Follow Procedures
- **Description**: Operators trained and follow operational procedures
- **Validation**: Training records, operational audits
- **Impact if Invalid**: Increased risk of human error (operator bypass)

### A2: Maintenance Performed Per Schedule
- **Description**: Preventive maintenance every 6 months
- **Validation**: Maintenance logs, system health monitoring
- **Impact if Invalid**: Hardware failure rates may exceed design assumptions
```

---

## 6. Evidence Collection

### 6.1 Evidence Types

**Three Categories of Evidence**:

1. **Hazard Analysis Evidence**: Shows hazards identified and mitigated
2. **Verification Evidence**: Shows software correctly implements requirements
3. **Validation Evidence**: Shows software operates correctly in target environment
4. **Process Evidence**: Shows EN 50128 processes followed

### 6.2 Hazard Analysis Evidence

**Required Documents**:

| Document | Description | EN 50128 Reference | SIL Requirement |
|----------|-------------|-------------------|-----------------|
| Hazard Log | All hazards, mitigations, status | Section 7.1 | ALL SILs |
| FMEA Report | Failure modes, RPN, mitigations | Table A.8 | HR (SIL 2+) |
| FTA Report | Fault trees, cut sets, probabilities | Table A.8 | HR (SIL 2+) |
| CCF Analysis | Common cause failures | Table A.8 | M (SIL 4), HR (SIL 3) |

**Evidence Cross-Reference**:
```markdown
### Evidence: Hazard Analysis

- **Hazard Log** (DOC-SAF-HAZLOG-001, v1.5, 2026-03-01)
  - 15 hazards identified (12 software-related, 3 hardware-related)
  - All hazards mitigated to MEDIUM or LOW residual risk
  - Traceability: Hazard → Safety Requirement → Design → Test

- **FMEA Report** (DOC-SAF-FMEA-SPD-001, v1.2, 2026-02-15)
  - Speed monitoring module: 6 failure modes analyzed
  - Average RPN: 158 → 82 (after mitigations)
  - All critical failure modes (S ≥ 8) mitigated

- **FTA Report** (DOC-SAF-FTA-SPD-001, v1.1, 2026-02-20)
  - Top event: Train exceeds speed limit
  - Probability: 2.8×10^-3 → 1×10^-7 per hour (after mitigations)
  - No single points of failure (SPOFs) in final design
  - CCF analysis: β = 0.05 (diverse sensors)
```

### 6.3 Verification Evidence

**Required Documents**:

| Document | Description | EN 50128 Reference | SIL Requirement |
|----------|-------------|-------------------|-----------------|
| Verification Report | Summary of all verification activities | Section 6.2 | ALL SILs |
| Static Analysis Report | Cppcheck, PC-lint results | Table A.19 | M (SIL 3-4) |
| Code Review Report | Manual code review findings | Table A.9 | M (ALL SILs) |
| Complexity Report | Cyclomatic complexity metrics | Table A.19 | HR (SIL 2+) |
| Unit Test Report | Unit test results, coverage | Table A.21 | M (SIL 3-4) |

**Evidence Cross-Reference**:
```markdown
### Evidence: Verification

- **Verification Report** (DOC-VER-001, v2.0, 2026-03-10)
  - Static analysis: Zero critical defects (Cppcheck, PC-lint)
  - Code review: 100% of code reviewed by independent verifier
  - Complexity: Max CCN = 8 (target ≤ 10 for SIL 3) ✓
  - MISRA C:2012: Zero mandatory violations, 3 advisory deviations (justified)

- **Unit Test Report** (DOC-TST-UNIT-001, v1.8, 2026-03-05)
  - Test coverage: 100% statement, 100% branch, 98% MC/DC
  - Tests passed: 487/487 (100%)
  - Fault injection: 25 fault cases, all detected
```

### 6.4 Validation Evidence

**Required Documents**:

| Document | Description | EN 50128 Reference | SIL Requirement |
|----------|-------------|-------------------|-----------------|
| Validation Report | Summary of validation activities | Section 7.7 | ALL SILs |
| System Test Report | System-level test results | Table A.7 | M (SIL 3-4) |
| Integration Test Report | Integration test results | Section 7.6 | ALL SILs |
| Performance Test Report | Timing, load testing | Table A.18 | M (SIL 3-4) |

**Evidence Cross-Reference**:
```markdown
### Evidence: Validation

- **Validation Report** (DOC-VAL-001, v1.5, 2026-03-12)
  - System tests: 124/124 passed (100%)
  - Operational scenarios: 15 scenarios tested, all passed
  - Performance: All timing constraints met (worst-case < 50ms, target < 100ms)
  - Target environment: Tested on actual hardware in lab environment

- **System Test Report** (DOC-TST-SYS-001, v1.3, 2026-03-10)
  - Functional tests: 98 test cases, 100% passed
  - Safety tests: 26 test cases (overspeed, door interlock, emergency brake), 100% passed
  - Boundary tests: 45 test cases (min/max speed, temperature, voltage), 100% passed
```

### 6.5 Process Evidence

**Required Documents**:

| Document | Description | EN 50128 Reference | SIL Requirement |
|----------|-------------|-------------------|-----------------|
| SQAP | Software Quality Assurance Plan | Section 6.5 | M (ALL SILs) |
| SCMP | Software Configuration Management Plan | Section 6.6 | M (ALL SILs) |
| SVP | Software Verification Plan | Section 6.2 | M (SIL 2+) |
| SVaP | Software Validation Plan | Section 7.7 | M (SIL 2+) |
| Tool Qualification | Qualification of software tools | Section 6.7 | M (T2/T3 tools) |

**Evidence Cross-Reference**:
```markdown
### Evidence: EN 50128 Process Compliance

- **SQAP** (DOC-QUA-SQAP-001, v1.0, 2025-10-01)
  - Defines quality assurance activities per EN 50128 Section 6.5
  - Code review: 100% coverage by independent reviewer (SIL 3 requirement)
  - Quality gates: All gates passed (requirements, design, implementation, validation)

- **SCMP** (DOC-CM-SCMP-001, v1.0, 2025-10-01)
  - Version control: Git with branch protection
  - Change control: Change Control Board (CCB) approval for all baseline changes
  - Traceability: Complete traceability matrix maintained (requirements → test)

- **Independence Evidence** (SIL 3 requirement):
  - Verifier: John Smith (independent from development team)
  - Validator: Jane Doe (independent from development and verification)
  - Assessor: SafetyCert Ltd (independent from development organization)
```

### 6.6 Evidence Traceability Matrix

**Cross-Reference Evidence to Claims**:

| Claim | Evidence Documents | Traceability Link |
|-------|-------------------|-------------------|
| G2: All hazards identified | Hazard Log, FMEA, FTA | workspace.py trace report |
| G3: All hazards mitigated | Hazard Log (residual risk), Safety Requirements | HAZ-XXX → REQ-SAFE-YYY |
| G4: Design is safe | SAS, SDS, Design Review Report | REQ → DES traceability |
| G5: Implementation correct | Source Code, Unit Tests, Code Review | DES → CODE → TEST traceability |
| G6: System operates safely | System Test Report, Validation Report | REQ → TST traceability |
| G7: EN 50128 process followed | SQAP, SCMP, SVP, SVaP, Audit Reports | Process compliance matrix |

**Generate Traceability Report**:
```bash
# Complete traceability from hazard to validation
workspace.py trace report \
    --from hazard \
    --to validation \
    --format markdown \
    --output evidence/safety-case/traceability-matrix.md
```

---

## 7. Assurance Argument

### 7.1 Assurance Argument Purpose

**Assurance Argument**: Demonstrates that the safety case itself is trustworthy.

**Three Pillars of Assurance**:
1. **Independence**: Key roles (Verifier, Validator, Assessor) are independent
2. **Competence**: Personnel have appropriate qualifications and experience
3. **Process**: EN 50128 processes followed correctly

### 7.2 Independence Assurance

**EN 50128 Independence Requirements (SIL 3-4)**:

| Role | Independence Requirement | Evidence |
|------|--------------------------|----------|
| **Verifier** | Independent from Designer, Implementer, Tester | Organization chart, role assignments |
| **Validator** | Independent from all development roles, does not report to PM | Organization chart, reporting structure |
| **Assessor** | Independent from development organization | Contract with external assessor |

**Independence Evidence**:
```markdown
### Independence Assurance (SIL 3)

**Verifier**:
- Name: John Smith, Safety Verifier
- Organization: Quality Assurance Department (separate from Engineering)
- Reports to: QA Manager (not Project Manager)
- Verification: Organization chart (Appendix A1)

**Validator**:
- Name: Jane Doe, Senior Validator
- Organization: Independent V&V Contractor (V&V Solutions Ltd)
- Reports to: Customer Safety Authority (not development organization)
- Verification: Contract (Appendix A2), Statement of Independence (Appendix A3)

**Assessor**:
- Name: Dr. Robert Brown, Lead Assessor
- Organization: SafetyCert Ltd (independent assessment body)
- Accreditation: National Railway Safety Authority accreditation #12345
- Verification: Assessment contract (Appendix A4), Accreditation certificate (Appendix A5)
```

### 7.3 Competence Assurance

**Competence Evidence**:

| Role | Required Competence | Evidence |
|------|---------------------|----------|
| **Software Manager** | Railway software experience, EN 50128 training | CV, certificates |
| **Designer** | Safety-critical design, MISRA C, formal methods | CV, certificates, publications |
| **Implementer** | C programming, MISRA C, embedded systems | CV, code samples, peer reviews |
| **Verifier** | Static analysis, EN 50128 verification techniques | CV, tool certifications |
| **Validator** | System testing, operational scenarios | CV, previous projects |
| **Assessor** | EN 50128/50126 expertise, assessment methodology | CV, accreditation, training records |

**Competence Summary**:
```markdown
### Competence Assurance

**Software Manager** (Alice Johnson):
- Experience: 15 years railway software, 8 SIL 3-4 projects
- Training: EN 50128:2011 (2 days, 2024), Functional Safety (IEC 61508, 3 days, 2023)
- Certifications: Certified Functional Safety Engineer (TÜV Rheinland)

**Implementer** (Bob Williams):
- Experience: 10 years embedded C, 5 years railway software
- Training: MISRA C:2012 (1 day, 2024), Defensive Programming (2 days, 2023)
- Code Quality: Zero critical defects in code reviews (last 3 projects)

**Assessor** (Dr. Robert Brown):
- Experience: 20 years safety assessment, 50+ EN 50128 assessments
- Training: EN 50128:2011 (5 days, 2020), EN 50126:2017 (3 days, 2020)
- Certifications: Accredited Assessor (National Railway Safety Authority)
- Publications: 10 papers on railway software safety
```

### 7.4 Process Assurance

**Process Compliance Evidence**:

| EN 50128 Requirement | Evidence | Compliance Status |
|---------------------|----------|-------------------|
| SQAP developed and followed | SQAP document, QA audit reports | ✓ Compliant |
| SCMP developed and followed | SCMP document, CM audit reports, Git history | ✓ Compliant |
| SVP developed and followed | SVP document, Verification Report | ✓ Compliant |
| SVaP developed and followed | SVaP document, Validation Report | ✓ Compliant |
| Code review (100% for SIL 3) | Code review reports, review meeting minutes | ✓ Compliant (100% coverage) |
| Static analysis (M for SIL 3) | Static analysis reports (Cppcheck, PC-lint) | ✓ Compliant (zero critical defects) |
| Independent verification | Verifier independence evidence, Verification Report | ✓ Compliant |
| Independent validation | Validator independence evidence, Validation Report | ✓ Compliant |

**Process Audit Results**:
```markdown
### Process Assurance

**Quality Audits Performed**:
- **Audit 1** (Requirements Phase, 2025-12-01): SQAP compliance verified, zero findings
- **Audit 2** (Design Phase, 2026-01-15): Design review process verified, 2 minor findings (closed)
- **Audit 3** (Implementation Phase, 2026-02-20): Code review process verified, 1 minor finding (closed)
- **Audit 4** (Validation Phase, 2026-03-10): Test process verified, zero findings

**Configuration Management Audits**:
- **CM Audit 1** (2026-01-10): Baseline management verified, zero findings
- **CM Audit 2** (2026-03-05): Change control process verified, zero findings

**Audit Conclusion**: All EN 50128 processes followed correctly, all findings closed.
```

---

## 8. Safety Case Review and Approval

### 8.1 Safety Case Review Process

**Review Steps**:

```
STEP 1: Safety Case Submitted (by Developer/Validator)
↓
STEP 2: Completeness Check (by Assessor)
- All required sections present
- All evidence documents referenced
- Traceability complete
↓
STEP 3: Technical Review (by Assessor)
- Argument logic sound
- Evidence valid and sufficient
- Claims justified
↓
STEP 4: Findings Report (by Assessor)
- Identify gaps, weaknesses, inconsistencies
- Categorize findings (critical, major, minor)
↓
STEP 5: Developer Response
- Address all findings
- Provide additional evidence if needed
- Update safety case
↓
STEP 6: Re-review (by Assessor)
- Verify findings addressed
↓
STEP 7: Assessment Report (by Assessor)
- Recommendation: Approve / Approve with Conditions / Reject
↓
STEP 8: Safety Authority Approval
- Review Assessment Report
- Grant operational authorization
```

### 8.2 Assessment Findings

**Finding Categories**:

**Critical Finding**: Prevents safety case approval
- Example: "No evidence provided for Claim G4 (design is safe)"
- Action Required: Provide missing evidence, update argument

**Major Finding**: Weakens safety case, must be addressed
- Example: "FTA analysis incomplete - CCF not analyzed"
- Action Required: Complete CCF analysis, update FTA report

**Minor Finding**: Does not prevent approval, should be addressed
- Example: "Traceability matrix formatting inconsistent"
- Action Required: Correct formatting (or accept as-is with rationale)

**Observation**: Noted for information, no action required
- Example: "Consider adding more boundary value tests in future versions"

### 8.3 Assessment Report Structure

```markdown
# Independent Safety Assessment Report

## Executive Summary
- System: Train Control System v1.0
- SIL Level: 3
- Assessment Date: 2026-03-14
- Assessor: Dr. Robert Brown, SafetyCert Ltd
- Recommendation: **APPROVE WITH CONDITIONS**

## Scope of Assessment
- Safety Case document review (DOC-SAF-SC-001, v2.0)
- Evidence document review (27 documents)
- Traceability verification
- EN 50128 process compliance

## Assessment Findings

### Critical Findings: 0

### Major Findings: 2
1. **Finding M1**: FTA-SPD-001 does not include CCF analysis for dual sensors
   - **Evidence**: FTA report section 8 missing
   - **Impact**: Cannot verify beta-factor assumption
   - **Resolution**: Developer provided CCF analysis (v1.1), verified by assessor. **CLOSED**

2. **Finding M2**: Unit test coverage for alarm module only 98% MC/DC (target 100%)
   - **Evidence**: Unit test report shows 2 uncovered conditions
   - **Impact**: Minor gap in verification evidence
   - **Resolution**: Developer added tests, achieved 100% coverage. **CLOSED**

### Minor Findings: 3
[Details omitted for brevity]

## Compliance Assessment
- EN 50128:2011 compliance: ✓ All requirements met
- Independence requirements (SIL 3): ✓ Verified
- Competence requirements: ✓ Verified
- Process requirements: ✓ All processes followed

## Safety Case Adequacy
- Argument structure: ✓ Sound and complete
- Evidence quality: ✓ Sufficient and valid
- Traceability: ✓ Complete from hazard to validation
- Assurance: ✓ Independence, competence, process verified

## Recommendation
**APPROVE WITH CONDITIONS**

**Conditions**:
1. Operational assumption A2 (maintenance every 6 months) must be enforced
2. Residual risk R3 (operator bypass) must be monitored operationally
3. Safety case shall be updated after 12 months of operation with operational data

## Assessor Signature
Dr. Robert Brown, Lead Assessor
SafetyCert Ltd
Date: 2026-03-14
```

### 8.4 Safety Authority Approval

**After Assessment**:
- Safety Authority reviews Assessment Report
- May request additional information or clarifications
- Issues **Authorization for Operation** (if approved)

**Authorization Document**:
```markdown
# Authorization for Operation

**System**: Train Control System v1.0
**Operator**: Metro North Railway
**Line**: Metro North Line (urban)
**SIL Level**: 3

**Authorization**: The Train Control System v1.0 is hereby authorized for passenger
train operations on the Metro North Line, subject to the following conditions:

**Conditions**:
1. Preventive maintenance SHALL be performed every 6 months
2. Operator bypass events SHALL be logged and reviewed monthly
3. Safety case SHALL be updated after 12 months with operational experience
4. Any software changes SHALL require re-assessment before deployment

**Validity**: 3 years from date of issue (renewable)
**Issue Date**: 2026-03-20
**Expiry Date**: 2029-03-20

**Issued by**: National Railway Safety Authority
**Signature**: [Authority Signature]
```

---

## 9. Safety Case Example

### 9.1 Example: Train Control System Safety Case (Excerpt)

```markdown
# Safety Case: Train Control System v1.0

## 1. Executive Summary

### System Overview
The Train Control System (TCS) v1.0 is a microprocessor-based system that monitors
train speed, controls door interlocks, and manages emergency braking for passenger
trains on the Metro North Line.

### Safety Claim
The TCS v1.0 is acceptably safe for passenger train operations on the Metro North
Line at SIL 3, with residual risks reduced to As Low As Reasonably Practicable (ALARP).

### Assessment Status
- **Independent Assessment**: Complete (SafetyCert Ltd, 2026-03-14)
- **Recommendation**: Approve with Conditions
- **Authorization**: Granted by National Railway Safety Authority (2026-03-20)

## 2. System Description

### Scope
- Speed monitoring (0-150 km/h, resolution 1 km/h)
- Overspeed protection (automatic braking if speed > limit)
- Door interlock (doors locked when speed > 5 km/h)
- Emergency brake interface (initiate emergency brake on command)

### Safety-Related Functions (SIL 3)
1. **F1**: Speed Monitoring - Continuously monitor train speed, detect overspeed
2. **F2**: Automatic Train Protection (ATP) - Apply brakes if overspeed detected
3. **F3**: Door Interlock - Prevent door opening when train moving
4. **F4**: Emergency Brake - Activate emergency brake on command

## 3. Safety Requirements

### SIL Allocation
- System SIL: **3**
- All safety-related functions: **SIL 3**
- Tolerable Hazard Rate (THR): **10^-7 failures per hour**

### Safety Requirements Summary
- Total Safety Requirements: 42
- Speed monitoring: 12 requirements
- Door interlock: 8 requirements
- Emergency brake: 6 requirements
- Diagnostics/monitoring: 16 requirements

## 4. Safety Argument (GSN)

### Top-Level Argument

[See GSN diagram in Appendix B]

**G1: Train Control System is acceptably safe for passenger operations (SIL 3)**
  ← C1: SIL 3 system per EN 50128:2011
  ← C2: Metro North Line operations (max speed 120 km/h)
  
  → S1: Argument by hazard analysis and lifecycle evidence
  
  → G2: All identified hazards have been mitigated to acceptable levels
     → S2: Argument over all hazards in Hazard Log
     → G2.1: HAZ-SPD-001 (Train overspeed) mitigated
        → Sn1: FTA-SPD-001 (probability 1×10^-7 per hour, meets THR)
        → Sn2: Verification Report (static analysis, zero defects)
        → Sn3: System Test Report (overspeed scenarios, 100% passed)
     → G2.2: HAZ-DOOR-001 (Door opens while moving) mitigated
        → Sn4: FTA-DOOR-001 (probability 1×10^-7 per hour, meets THR)
        → Sn5: System Test Report (door interlock scenarios, 100% passed)
     ... [Additional hazards G2.3-G2.15]
  
  → G3: EN 50128 lifecycle process followed correctly
     → S3: Argument by lifecycle phase
     → G3.1: Software Quality Assurance Plan (SQAP) followed
        → Sn10: SQAP document, QA audit reports (zero findings)
     → G3.2: Software Configuration Management Plan (SCMP) followed
        → Sn11: SCMP document, CM audit reports (zero findings)
     → G3.3: Independent verification performed (SIL 3 requirement)
        → Sn12: Verifier independence evidence, Verification Report
     → G3.4: Independent validation performed (SIL 3 requirement)
        → Sn13: Validator independence evidence, Validation Report
  
  → G4: All safety requirements satisfied
     → S4: Argument by traceability
     → Sn14: Traceability matrix (Hazard → Requirement → Design → Test)
     → Sn15: System Test Report (100% safety requirements tested, passed)

## 5. Evidence

[See Section 6 for detailed evidence cross-reference]

### Hazard Analysis
- Hazard Log (DOC-SAF-HAZLOG-001): 15 hazards, all mitigated to MEDIUM or LOW
- FMEA Reports: 4 modules analyzed (SPD, DOOR, BRK, COMM)
- FTA Reports: 3 critical hazards analyzed (SPD, DOOR, BRK)

### Verification
- Static Analysis: Zero critical defects (Cppcheck, PC-lint)
- Code Review: 100% coverage by independent verifier
- Unit Tests: 100% statement, branch, MC/DC coverage
- Complexity: Max CCN = 8 (target ≤ 10)

### Validation
- System Tests: 124 test cases, 100% passed
- Operational Scenarios: 15 scenarios, 100% passed
- Performance: All timing constraints met

## 6. Assurance Argument

### Independence (SIL 3)
- Verifier: John Smith (QA Department, independent from Engineering)
- Validator: Jane Doe (V&V Solutions Ltd, external contractor)
- Assessor: Dr. Robert Brown (SafetyCert Ltd, accredited)

### Competence
- All personnel have appropriate qualifications and experience
- Training records and certificates provided (Appendix C)

### Process Compliance
- All EN 50128 processes followed and audited
- Zero critical or major audit findings

## 7. Assumptions and Limitations

### Operational Assumptions
- **A1**: Train operators follow operational procedures (training required)
- **A2**: Maintenance performed every 6 months (tracked by maintenance logs)
- **A3**: Environmental conditions within design limits (-40°C to +70°C)

### Residual Risks
- **R1**: Operator bypass of door interlock (procedural control, two-person authorization)
- **R2**: Common cause failure of dual sensors (β=0.05, within acceptable limits)
- **R3**: Hardware failures beyond design assumptions (monitored via diagnostics)

## 8. Conclusions

### Safety Claim Justified
The evidence presented demonstrates that the Train Control System v1.0 is acceptably
safe for passenger train operations on the Metro North Line at SIL 3. All identified
hazards have been mitigated to acceptable levels, and residual risks are ALARP.

### Residual Risk Acceptable
Residual risks are within acceptable limits for SIL 3 operations and are monitored
through operational procedures and system diagnostics.

### Recommendations
1. Enforce maintenance schedule (every 6 months) per assumption A2
2. Monitor operator bypass events monthly per residual risk R1
3. Update safety case after 12 months of operation with operational data

## Appendices
- Appendix A: Organization Charts and Role Assignments
- Appendix B: GSN Diagram (full)
- Appendix C: Competence Evidence (CVs, certificates)
- Appendix D: Traceability Matrix (complete)
- Appendix E: Evidence Document List (27 documents)
```

---

## 10. Tool Integration

### 10.1 GSN Diagram Generator

**Script**: `tools/safety-case/gsn_generator.py`

```python
#!/usr/bin/env python3
"""
GSN Diagram Generator for Safety Cases

Generates ASCII-art GSN diagrams from structured input.
Supports Goals, Strategies, Solutions, Context, Justifications.
"""

from typing import List, Dict
from dataclasses import dataclass

@dataclass
class GSNNode:
    """GSN Node"""
    id: str
    type: str  # 'goal', 'strategy', 'solution', 'context', 'justification'
    text: str
    supported_by: List[str]
    in_context_of: List[str]

class GSNDiagram:
    """GSN Diagram Generator"""
    
    def __init__(self):
        self.nodes: Dict[str, GSNNode] = {}
    
    def add_node(self, node: GSNNode):
        """Add node to diagram"""
        self.nodes[node.id] = node
    
    def generate_ascii(self, root_id: str, indent: int = 0) -> str:
        """Generate ASCII art diagram (recursive)"""
        if root_id not in self.nodes:
            return ""
        
        node = self.nodes[root_id]
        prefix = "  " * indent
        
        # Node representation
        if node.type == 'goal':
            output = f"{prefix}┌─ {node.id}: {node.text}\n"
        elif node.type == 'strategy':
            output = f"{prefix}├─ {node.id}: {node.text}\n"
        elif node.type == 'solution':
            output = f"{prefix}└─ {node.id}: {node.text}\n"
        else:
            output = f"{prefix}   {node.id}: {node.text}\n"
        
        # Context
        for ctx_id in node.in_context_of:
            output += f"{prefix}   ← Context: {ctx_id}\n"
        
        # Supported by (recursive)
        for child_id in node.supported_by:
            output += self.generate_ascii(child_id, indent + 1)
        
        return output
    
    def generate_markdown(self, filename: str, root_id: str):
        """Generate Markdown safety case with embedded GSN"""
        with open(filename, 'w') as f:
            f.write("# Safety Case: GSN Argument\n\n")
            f.write("```\n")
            f.write(self.generate_ascii(root_id))
            f.write("```\n")
        print(f"✓ GSN diagram exported to {filename}")

def main():
    """Example usage"""
    gsn = GSNDiagram()
    
    # Top-level goal
    gsn.add_node(GSNNode(
        id="G1",
        type="goal",
        text="System is acceptably safe",
        supported_by=["S1"],
        in_context_of=["C1"]
    ))
    
    # Context
    gsn.add_node(GSNNode(
        id="C1",
        type="context",
        text="SIL 3 system per EN 50128",
        supported_by=[],
        in_context_of=[]
    ))
    
    # Strategy
    gsn.add_node(GSNNode(
        id="S1",
        type="strategy",
        text="Argument by hazard analysis",
        supported_by=["G2", "G3"],
        in_context_of=[]
    ))
    
    # Sub-goals
    gsn.add_node(GSNNode(
        id="G2",
        type="goal",
        text="All hazards identified",
        supported_by=["Sn1"],
        in_context_of=[]
    ))
    
    gsn.add_node(GSNNode(
        id="G3",
        type="goal",
        text="All hazards mitigated",
        supported_by=["Sn2"],
        in_context_of=[]
    ))
    
    # Solutions (evidence)
    gsn.add_node(GSNNode(
        id="Sn1",
        type="solution",
        text="Hazard Log (DOC-SAF-HAZLOG-001)",
        supported_by=[],
        in_context_of=[]
    ))
    
    gsn.add_node(GSNNode(
        id="Sn2",
        type="solution",
        text="FMEA/FTA Reports",
        supported_by=[],
        in_context_of=[]
    ))
    
    # Generate diagram
    gsn.generate_markdown("safety-case-gsn.md", "G1")

if __name__ == "__main__":
    main()
```

**Usage**:
```bash
python3 tools/safety-case/gsn_generator.py
# Output: safety-case-gsn.md created
```

### 10.2 Evidence Cross-Reference Checker

**Script**: `tools/safety-case/evidence_checker.py`

```python
#!/usr/bin/env python3
"""
Evidence Cross-Reference Checker for Safety Cases

Verifies that all claims in safety case are supported by evidence.
Checks for missing evidence, broken references.
"""

import re
from typing import List, Dict, Set

def extract_claims(safety_case_file: str) -> List[str]:
    """Extract all claims (Gx: ...) from safety case"""
    claims = []
    with open(safety_case_file, 'r') as f:
        for line in f:
            match = re.search(r'(G\d+):', line)
            if match:
                claims.append(match.group(1))
    return claims

def extract_evidence_refs(safety_case_file: str) -> Dict[str, List[str]]:
    """Extract evidence references (Snx: ...) for each claim"""
    evidence_map = {}
    current_claim = None
    
    with open(safety_case_file, 'r') as f:
        for line in f:
            # Check for claim
            claim_match = re.search(r'(G\d+):', line)
            if claim_match:
                current_claim = claim_match.group(1)
                evidence_map[current_claim] = []
            
            # Check for evidence reference
            if current_claim:
                evidence_match = re.search(r'(Sn\d+):', line)
                if evidence_match:
                    evidence_map[current_claim].append(evidence_match.group(1))
    
    return evidence_map

def check_evidence_completeness(claims: List[str], evidence_map: Dict[str, List[str]]) -> List[str]:
    """Check if all claims have evidence"""
    issues = []
    
    for claim in claims:
        if claim not in evidence_map or len(evidence_map[claim]) == 0:
            issues.append(f"⚠ Claim {claim} has no supporting evidence")
    
    return issues

def main():
    """Check evidence completeness"""
    import sys
    
    if len(sys.argv) < 2:
        print("Usage: evidence_checker.py <safety-case-file.md>")
        sys.exit(1)
    
    safety_case_file = sys.argv[1]
    
    claims = extract_claims(safety_case_file)
    evidence_map = extract_evidence_refs(safety_case_file)
    issues = check_evidence_completeness(claims, evidence_map)
    
    print(f"Safety Case Evidence Check")
    print(f"=" * 60)
    print(f"Claims found: {len(claims)}")
    print(f"Claims with evidence: {len([c for c in claims if c in evidence_map and len(evidence_map[c]) > 0])}")
    print()
    
    if issues:
        print("Issues Found:")
        for issue in issues:
            print(f"  {issue}")
    else:
        print("✓ All claims have supporting evidence")

if __name__ == "__main__":
    main()
```

**Usage**:
```bash
python3 tools/safety-case/evidence_checker.py docs/safety-case/DOC-SAF-SC-001.md
# Output:
# Safety Case Evidence Check
# ============================================================
# Claims found: 15
# Claims with evidence: 15
# ✓ All claims have supporting evidence
```

### 10.3 Traceability Management

```bash
# Generate complete traceability matrix for safety case
workspace.py trace report \
    --from hazard \
    --to validation \
    --format markdown \
    --output evidence/safety-case/traceability-complete.md

# Validate traceability completeness
workspace.py trace validate \
    --phase all \
    --sil 3 \
    --check-completeness \
    --output evidence/safety-case/traceability-validation.md
```

### 10.4 Workflow Management

```bash
# Submit safety case for assessment
workspace.py wf submit \
    --deliverable DOC-SAF-SC-001 \
    --phase assessment \
    --author "Validator (VAL)" \
    --sil 3

# Assessor review
workspace.py wf review \
    --deliverable DOC-SAF-SC-001 \
    --reviewer "Assessor (SafetyCert Ltd)" \
    --status "approved-with-conditions" \
    --comments "Approve with 3 conditions per Assessment Report"

# Check status
workspace.py wf status --deliverable DOC-SAF-SC-001
```

---

## 11. Example Scenario: Train Control Safety Case

[Content from Section 9.1 applies - complete train control system safety case example]

---

## Summary

This Safety Case Development workflow provides:

1. **Structured Argument**: Claims, Arguments, Evidence (CAE) structure
2. **Graphical Representation**: Goal Structuring Notation (GSN)
3. **Evidence Collection**: Hazard analysis, verification, validation, process evidence
4. **Assurance**: Independence, competence, process compliance
5. **Review Process**: Independent assessment, findings resolution, approval
6. **Traceability**: Complete traceability from hazard to evidence
7. **EN 50128 Compliance**: Highly Recommended SIL 2-3, MANDATORY SIL 4

**Key Takeaways**:
- Safety case demonstrates system is "acceptably safe"
- GSN provides visual, traceable argument structure
- Evidence must be objective, valid, and sufficient
- Assurance (independence, competence, process) is critical
- Independent assessment is MANDATORY for SIL 3-4
- Safety case is iterative - updated throughout lifecycle

**Lifecycle Integration**:
- Safety case planning in Phase 1 (Planning)
- Progressive development through Phases 2-6
- Independent assessment in Phase 7
- Operational updates in Phase 8

---

**End of Safety Case Development Workflow**
