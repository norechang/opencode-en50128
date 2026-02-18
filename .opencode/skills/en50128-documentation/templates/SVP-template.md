# Software Verification Plan (SVP)

**TEMPLATE VERSION**: 1.0  
**REFERENCE**: EN 50128:2011 Section 6.2, Table A.5

---

## STANDARD HEADER

| Field | Value |
|-------|-------|
| **Document ID** | DOC-SVP-YYYY-NNN |
| **Version** | 0.1 (Draft) → 1.0 (Approved) |
| **Date** | YYYY-MM-DD |
| **Project** | [Project Name] |
| **SIL Level** | [0, 1, 2, 3, 4] |
| **Author** | [Name], Verifier |
| **Reviewer** | [Name], [Role] |
| **Approver** | [Name], Project Manager |
| **Status** | [Draft \| Review \| Approved \| Baseline] |

---

## DOCUMENT CONTROL

| Version | Date | Author | Changes | Approved By |
|---------|------|--------|---------|-------------|
| 0.1 | YYYY-MM-DD | [Name] | Initial draft | - |
| 1.0 | YYYY-MM-DD | [Name] | First approved version | [PM Name] |

---

## APPROVALS

**SIL 0-2 Requirements**: Author, QA Manager, Project Manager  
**SIL 3-4 Requirements**: Author, Independent Verifier, QA Manager, Project Manager

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Author** | [Verifier Name] | | |
| **Independent Verifier** (SIL 3-4) | [Verifier Name] | | |
| **QA Manager** | [QA Name] | | |
| **Project Manager** | [PM Name] | | |

---

## 1. INTRODUCTION

### 1.1 Purpose

[State the purpose of this Software Verification Plan. Example:]

This Software Verification Plan (SVP) defines the verification strategy, activities, techniques, and acceptance criteria for the [Project Name] software development. Verification ensures that software outputs of each lifecycle phase correctly implement the specifications and requirements in accordance with EN 50128:2011 Section 6.2.

**Verification Definition** (EN 50128): Confirmation by examination and provision of objective evidence that specified requirements have been fulfilled.

### 1.2 Scope

[Define the scope of verification activities. Example:]

This SVP applies to:
- All software lifecycle phases (requirements through validation)
- All software configuration items (documents, code, tests)
- All verification techniques per EN 50128 Table A.5
- Target SIL level: [0, 1, 2, 3, 4]

**Out of Scope**:
- System validation (covered by Software Validation Plan)
- Hardware verification (covered by Hardware Verification Plan)

### 1.3 SIL Classification

**Target SIL Level**: [0, 1, 2, 3, 4]

**EN 50128 Verification Requirements** (Table A.5):

| SIL Level | Mandatory Techniques | Key Requirements |
|-----------|---------------------|------------------|
| **SIL 0** | None | Basic verification recommended |
| **SIL 1-2** | Dynamic Analysis and Testing (HR) | Static analysis (HR), Traceability (HR) |
| **SIL 3-4** | Dynamic Analysis (**M**), Test Coverage (**M**), Traceability (**M**), Functional Testing (**M**) | Static analysis (**M**), Independent verification (**M**) |

**Independence Requirements**:
- **SIL 0-2**: Independence recommended but not mandatory
- **SIL 3-4**: **Independent Verifier MANDATORY** (different person/team from developers)

### 1.4 Definitions and Acronyms

| Term | Definition |
|------|------------|
| **Verification** | Confirmation that software outputs correctly implement specifications |
| **Validation** | Confirmation that software fulfills its intended use |
| **Static Analysis** | Analysis of software without execution (code review, data/control flow analysis) |
| **Dynamic Analysis** | Analysis of software during execution (testing, profiling) |
| **Traceability** | Ability to trace requirements through design, code, and tests |
| **Coverage** | Measure of test completeness (statement, branch, condition, MC/DC) |
| **MISRA C** | Motor Industry Software Reliability Association C coding standard |

### 1.5 References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-YYYY-NNN |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-YYYY-NNN |
| **[SRS]** | Software Requirements Specification, DOC-SRS-YYYY-NNN |
| **[SAS]** | Software Architecture Specification, DOC-SAS-YYYY-NNN |
| **[SDS]** | Software Design Specification, DOC-SDS-YYYY-NNN |

### 1.6 Overview

[Provide a brief overview of the document structure.]

---

## 2. VERIFICATION ORGANIZATION

### 2.1 Verification Team

#### 2.1.1 Verifier Role

**Responsibilities**:
- Develop and maintain Software Verification Plan (this document)
- Perform verification activities per Table A.5
- Execute static analysis (control flow, data flow, MISRA C)
- Verify test coverage per Table A.21
- Verify traceability (requirements → design → code → tests)
- Collect and manage verification evidence
- Generate Verification Reports for each phase
- Ensure EN 50128 compliance

**Qualifications**:
- Knowledge of EN 50128 verification requirements
- Experience with static analysis tools (PC-lint, Cppcheck)
- Understanding of C programming and MISRA C:2012
- Familiarity with test coverage tools (gcov/lcov)

**Independence Requirements**:
- **SIL 0-2**: No independence requirement (can be same person as developer)
- **SIL 3-4**: **MANDATORY independence** - Verifier SHALL NOT be involved in design/implementation

#### 2.1.2 Verification Support Roles

| Role | Responsibilities | Independence |
|------|------------------|--------------|
| **QA Manager** | Oversee verification process, approve verification reports | No |
| **Configuration Manager** | Maintain traceability matrix, baseline verification evidence | No |
| **Tester** | Execute tests, collect coverage data, provide test evidence | No |
| **Designer/Implementer** | Provide verification evidence, respond to verification findings | N/A |

### 2.2 Independence Management (SIL 3-4)

**EN 50128 Requirement**: Verifier SHALL be independent of design and implementation teams.

**Independence Measures**:
- Verifier reports to QA Manager (not Project Manager or development lead)
- Verifier has no design or coding responsibilities
- Verifier has authority to reject incomplete/incorrect verification evidence
- Verification findings cannot be overruled by development team

**Verification Authority**: Verifier has final authority to approve/reject phase completion based on verification evidence.

---

## 3. VERIFICATION STRATEGY

### 3.1 Verification Approach

**Multi-Level Verification**: Verification is performed at multiple levels:

1. **Document Verification**: Review and approve all lifecycle documents (SRS, SAS, SDS, plans)
2. **Design Verification**: Verify architecture and design correctness, traceability, completeness
3. **Code Verification**: Static analysis, code review, MISRA C compliance, complexity analysis
4. **Test Verification**: Verify test completeness, coverage, traceability, test results
5. **Traceability Verification**: End-to-end traceability from requirements to tests (mandatory SIL 3-4)

### 3.2 Verification Techniques (EN 50128 Table A.5)

The following verification techniques SHALL be applied per SIL level:

| # | Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Implementation | Reference |
|---|-----------|-------|---------|---------|----------------|-----------|
| **1** | Formal Proof | - | R | HR | Not planned for [Project] | D.29 |
| **2** | Probabilistic Testing | - | R | HR | Not planned | D.41 |
| **3** | Static Analysis | - | HR | **M** | PC-lint, Cppcheck, manual code review | Table A.19 |
| **4** | Dynamic Analysis and Testing | - | HR | **M** | Unity unit tests, integration tests | Table A.13 |
| **5** | Metrics | - | R | HR | Complexity, coverage, defect metrics | D.37 |
| **6** | Simulation | R | R | R | Not planned | D.47 |
| **7** | Traceability | R | HR | **M** | Requirements Traceability Matrix (RTM) | D.58 |
| **8** | Software Error Effect Analysis | - | R | HR | FMEA on critical modules | D.25 |
| **9** | Test Coverage for Code | R | HR | **M** | Statement, branch, condition coverage | Table A.21 |

**Approved Combination for SIL 3-4**: 3, 5, 7, 8 + one from {1, 2, 6} (we choose 3, 4, 5, 7, 9)

**Rationale**: 
- Techniques 3, 4, 7, 9 are MANDATORY for SIL 3-4
- Technique 5 (metrics) is HIGHLY RECOMMENDED and supports evidence collection
- This combination provides comprehensive verification coverage

### 3.3 Verification Tools

| Tool | Purpose | SIL Requirement | Qualification Status |
|------|---------|-----------------|---------------------|
| **PC-lint Plus** | MISRA C:2012 compliance checking | SIL 2+ (HR SIL 3-4) | [Qualified / Not qualified] |
| **Cppcheck** | Static analysis (control flow, data flow) | SIL 2+ (HR SIL 3-4) | [Qualified / Not qualified] |
| **Clang Static Analyzer** | Additional static analysis | Optional | [Qualified / Not qualified] |
| **gcov / lcov** | Test coverage measurement | SIL 2+ | [Qualified / Not qualified] |
| **Bullseye** | Advanced coverage (MC/DC for SIL 4) | SIL 4 | [Qualified / Not qualified] |
| **Lizard** | Cyclomatic complexity analysis | All SILs | Not safety-critical |
| **Git** | Version control, traceability | All SILs | Not safety-critical |

**Tool Qualification** (EN 50128 Section 6.7):
- **T1 Tools** (generate no output used in executable): No qualification required (Lizard)
- **T2 Tools** (support test/verification): Validation of tool required (PC-lint, Cppcheck, gcov)
- **T3 Tools** (generate executable code): Full qualification required (Compiler - not in this list)

**Tool Validation Evidence**: [Specify location of tool validation reports]

---

## 4. VERIFICATION ACTIVITIES BY PHASE

### 4.1 Phase 1: Planning Phase Verification

**Objective**: Verify that planning documents (SQAP, SCMP, SVP, SVaP) are complete, consistent, and EN 50128 compliant.

#### 4.1.1 Verification Inputs
- Software Quality Assurance Plan (SQAP)
- Software Configuration Management Plan (SCMP)
- Software Verification Plan (this document)
- Software Validation Plan (SVaP)

#### 4.1.2 Verification Activities

| Activity | Method | Acceptance Criteria | Responsible |
|----------|--------|---------------------|-------------|
| **Document review** | Checklist-based review | All sections complete, EN 50128 compliant | Verifier |
| **Consistency check** | Cross-reference verification | Plans consistent with each other | Verifier |
| **SIL verification** | Review SIL-specific requirements | SIL level stated, appropriate techniques planned | Verifier |
| **Tool verification** | Tool list review | Tools appropriate for SIL level, qualification plan present | Verifier |
| **Traceability check** | Review traceability approach | Traceability strategy defined (mandatory SIL 3-4) | Verifier |

#### 4.1.3 Verification Deliverables
- Planning Phase Verification Report (DOC-VER-PLAN-YYYY-NNN)
- Verification findings and corrective actions
- Approval recommendation to Project Manager

### 4.2 Phase 2: Requirements Phase Verification

**Objective**: Verify that Software Requirements Specification (SRS) is complete, unambiguous, testable, and traceable.

#### 4.2.1 Verification Inputs
- Software Requirements Specification (SRS)
- Requirements Traceability Matrix (RTM)
- Hazard Log (if safety-critical)

#### 4.2.2 Verification Activities

| Activity | Method | Acceptance Criteria | Responsible |
|----------|--------|---------------------|-------------|
| **Requirements review** | Checklist-based review | All requirements unambiguous, testable, traceable | Verifier |
| **SIL assignment** | Review SIL per requirement | SIL level assigned per Table 4 (EN 50128) | Verifier, Safety Engineer |
| **Traceability check** | RTM completeness | All requirements traced to system requirements | Verifier |
| **Consistency check** | Cross-reference verification | No conflicting requirements | Verifier |
| **Completeness check** | Structured walkthrough | All system requirements addressed | Verifier |
| **C constraints check** | Review data types, memory | C-specific constraints defined (fixed-width types, static allocation) | Verifier |

**Requirements Quality Checklist**:
- [ ] All requirements have unique IDs (REQ-FUNC-NNN, REQ-PERF-NNN, REQ-SAFE-NNN)
- [ ] All requirements use SHALL (mandatory) or SHOULD (recommended) language
- [ ] All requirements are unambiguous (single interpretation)
- [ ] All requirements are testable (verification method identified)
- [ ] All safety requirements have SIL level assigned
- [ ] All requirements traced to system requirements (RTM complete)
- [ ] All C language constraints specified (data types, memory allocation, error handling)

#### 4.2.3 Verification Deliverables
- Requirements Verification Report (DOC-VER-REQ-YYYY-NNN)
- Updated RTM (if corrections needed)
- Verification findings and corrective actions
- Approval recommendation to Project Manager

### 4.3 Phase 3: Design Phase Verification

**Objective**: Verify that Software Architecture Specification (SAS) and Software Design Specification (SDS) correctly implement requirements and are EN 50128 compliant.

#### 4.3.1 Verification Inputs
- Software Architecture Specification (SAS)
- Software Design Specification (SDS)
- Interface Specifications
- Requirements Traceability Matrix (RTM)

#### 4.3.2 Verification Activities

| Activity | Method | Acceptance Criteria | Responsible |
|----------|--------|---------------------|-------------|
| **Architecture review** | Structured walkthrough | Architecture addresses all requirements, modular design (mandatory SIL 2+) | Verifier |
| **Design review** | Checklist-based review | All modules designed, interfaces specified | Verifier |
| **Traceability check** | RTM update verification | All requirements traced to design elements | Verifier |
| **Safety review** | Hazard analysis | Safety requirements addressed in design | Verifier, Safety Engineer |
| **C design review** | MISRA C, defensive programming | Static allocation, no recursion (HR SIL 3-4), defensive programming | Verifier |
| **Complexity analysis** | Estimated complexity | Complexity within limits (10 SIL 3-4, 15 SIL 2, 20 SIL 0-1) | Verifier |

**Design Quality Checklist**:
- [ ] Modular architecture (mandatory SIL 2+)
- [ ] All modules have defined interfaces
- [ ] All requirements traced to design elements (RTM updated)
- [ ] Static memory allocation only (mandatory SIL 2+)
- [ ] No recursion planned (highly recommended SIL 3-4)
- [ ] Defensive programming patterns specified
- [ ] Error handling strategy defined
- [ ] Complexity estimated within limits

#### 4.3.3 Verification Deliverables
- Design Verification Report (DOC-VER-DES-YYYY-NNN)
- Updated RTM (requirements → design traceability)
- Verification findings and corrective actions
- Approval recommendation to Project Manager

### 4.4 Phase 4: Implementation Phase Verification

**Objective**: Verify that source code correctly implements design, complies with MISRA C:2012, and meets EN 50128 coding requirements.

#### 4.4.1 Verification Inputs
- Source code (C files: `.h`, `.c`)
- Unit test code
- Software Design Specification (SDS)
- Requirements Traceability Matrix (RTM)
- MISRA C:2012 compliance report

#### 4.4.2 Verification Activities

| Activity | Method | Tool | Acceptance Criteria | Responsible |
|----------|--------|------|---------------------|-------------|
| **Static analysis** | Automated analysis | PC-lint, Cppcheck | No critical/high issues | Verifier |
| **MISRA C compliance** | Automated checking | PC-lint Plus | 100% compliance (or deviations justified) | Verifier |
| **Code review** | Manual inspection | - | Code matches design, defensive programming used | Verifier, QA |
| **Complexity analysis** | Automated measurement | Lizard | Cyclomatic complexity ≤ 10 (SIL 3-4), ≤ 15 (SIL 2), ≤ 20 (SIL 0-1) | Verifier |
| **Data flow analysis** | Static analysis | Cppcheck | No uninitialized variables, no memory leaks | Verifier |
| **Control flow analysis** | Static analysis | Cppcheck | No unreachable code, no infinite loops | Verifier |
| **Traceability check** | RTM verification | - | All design elements traced to code, all code traced to tests | Verifier |
| **Unit test review** | Test case review | - | All functions have unit tests, boundary values tested | Verifier |

**Code Quality Checklist** (per EN 50128 Table A.4):
- [ ] MISRA C:2012 compliance (mandatory SIL 2+) - 100% or deviations justified
- [ ] Fixed-width types used (`uint8_t`, `uint32_t`, etc.)
- [ ] Static allocation only (mandatory SIL 2+) - no `malloc/free`
- [ ] No recursion (highly recommended SIL 3-4)
- [ ] All pointers validated before use (defensive programming)
- [ ] All return values checked
- [ ] Cyclomatic complexity within limits
- [ ] All functions have unit tests
- [ ] Traceability: Code → Design, Code → Tests

#### 4.4.3 Static Analysis Tool Configuration

**PC-lint Plus Configuration**:
```
// Mandatory MISRA C:2012 rules (all)
+elib(*)  // Enable all library checks
-w4      // Warning level 4
au-misra3.lnt  // MISRA C:2012 configuration
```

**Cppcheck Configuration**:
```
cppcheck --enable=all --inconclusive --std=c11 --platform=unix64 src/
```

**Acceptable Deviations**:
- MISRA C deviations SHALL be documented and justified
- SIL 3-4: Maximum 5% of rules may be deviated (with justification)
- SIL 0-2: Deviations allowed with justification

#### 4.4.4 Verification Deliverables
- Implementation Verification Report (DOC-VER-IMP-YYYY-NNN)
- Static analysis reports (PC-lint, Cppcheck)
- MISRA C compliance report with deviation rationale
- Complexity analysis report
- Updated RTM (design → code → tests traceability)
- Verification findings and corrective actions
- Approval recommendation to Project Manager

### 4.5 Phase 5: Integration Phase Verification

**Objective**: Verify that integrated software components function correctly together and meet integration test requirements.

#### 4.5.1 Verification Inputs
- Integrated software build
- Integration test specifications
- Integration test results
- Interface specifications

#### 4.5.2 Verification Activities

| Activity | Method | Acceptance Criteria | Responsible |
|----------|--------|---------------------|-------------|
| **Integration test review** | Test case review | All interfaces tested, all integration scenarios covered | Verifier |
| **Test execution verification** | Test result analysis | All integration tests passed | Verifier |
| **Interface verification** | Interface testing | All interfaces function correctly | Verifier, Integrator |
| **Performance verification** | Performance testing | Performance requirements met (highly recommended SIL 3-4) | Verifier |
| **Traceability check** | RTM verification | All design elements traced to integration tests | Verifier |

#### 4.5.3 Verification Deliverables
- Integration Verification Report (DOC-VER-INT-YYYY-NNN)
- Integration test result analysis
- Updated RTM
- Verification findings and corrective actions
- Approval recommendation to Project Manager

### 4.6 Phase 6: Testing Phase Verification

**Objective**: Verify that test coverage meets EN 50128 requirements (Table A.21) and all tests have passed.

#### 4.6.1 Verification Inputs
- System test specifications
- System test results
- Coverage reports (gcov/lcov)
- Requirements Traceability Matrix (RTM)

#### 4.6.2 Verification Activities

| Activity | Method | Tool | Acceptance Criteria | Responsible |
|----------|--------|------|---------------------|-------------|
| **Coverage analysis** | Automated measurement | gcov/lcov | Per Table A.21 (see below) | Verifier |
| **Test case review** | Checklist-based review | - | All requirements traced to test cases | Verifier |
| **Test result verification** | Test report analysis | - | All tests passed, no open defects (or justified) | Verifier |
| **Traceability verification** | RTM completeness | - | End-to-end traceability complete (REQ→DES→CODE→TEST) | Verifier |
| **Regression testing** | Verify test re-execution | - | All tests re-executed after changes | Verifier |

**Coverage Requirements** (EN 50128 Table A.21):

| Coverage Type | SIL 0 | SIL 1 | SIL 2 | SIL 3-4 | Target |
|---------------|-------|-------|-------|---------|--------|
| **Entry Point** | - | - | - | - | 100% (all functions called) |
| **Statement** | HR | HR | HR | **M** | 100% (SIL 3-4), 100% (SIL 2), 100% (SIL 0-1) |
| **Branch** | HR | HR | **M** | **M** | 100% (SIL 2+), 100% (SIL 0-1) |
| **Condition** (Boolean operand) | - | R | R | **M** | 100% (SIL 3-4), recommended (SIL 0-2) |
| **MC/DC** (Modified Condition/Decision) | - | - | R | HR | Highly recommended (SIL 4), optional (SIL 3) |

**Coverage Acceptance Criteria**:
- **SIL 0-1**: Statement ≥95%, Branch ≥90%
- **SIL 2**: Statement ≥99%, Branch 100%
- **SIL 3-4**: Statement 100%, Branch 100%, Condition 100%

**Uncovered Code**:
- Justification REQUIRED for any uncovered code (e.g., defensive code that cannot be tested)
- SIL 3-4: Maximum 1% uncovered (with strong justification)

#### 4.6.3 Verification Deliverables
- Testing Phase Verification Report (DOC-VER-TST-YYYY-NNN)
- Coverage reports with analysis
- Traceability verification report (end-to-end RTM)
- Verification findings and corrective actions
- Approval recommendation to Project Manager

---

## 5. TRACEABILITY VERIFICATION (MANDATORY SIL 3-4)

### 5.1 Traceability Strategy

**EN 50128 Requirement**: Traceability is **MANDATORY for SIL 3-4** (Table A.5, Technique 7)

**Traceability Chain**:
```
System Requirement → Software Requirement → Architecture → Design → Code → Unit Test → Integration Test → System Test → Validation Test
```

**Bidirectional Traceability**: Forward (requirements → tests) and backward (tests → requirements)

### 5.2 Requirements Traceability Matrix (RTM)

**Location**: `docs/traceability/RTM.md`

**Format**:
| System Req | SW Req | Architecture | Design | Code | Unit Test | Int Test | Sys Test | Val Test | Status |
|------------|--------|--------------|--------|------|-----------|----------|----------|----------|--------|
| SYS-001 | REQ-FUNC-001 | SAS-MOD-001 | SDS-MOD-001 | brake.c:45 | TC-UNIT-001 | TC-INT-001 | TC-SYS-001 | TC-VAL-001 | Verified |

**RTM Verification Checklist**:
- [ ] All requirements have at least one test case
- [ ] All design elements traced to requirements
- [ ] All code modules traced to design elements
- [ ] All test cases traced to requirements
- [ ] No orphaned code (code not traced to any requirement)
- [ ] No orphaned tests (tests not traced to any requirement)
- [ ] Bidirectional traceability complete (forward and backward)

### 5.3 Traceability Tools

**Tool**: Git commit messages, markdown-based RTM, grep/scripting

**Automation**: [Specify if traceability is automated or manual]

**Update Frequency**: Every phase gate, every baseline change

---

## 6. VERIFICATION EVIDENCE MANAGEMENT

### 6.1 Evidence Collection

All verification activities SHALL produce objective evidence. Evidence SHALL be collected, reviewed, and archived.

**Evidence Types**:
- Verification reports (per phase)
- Static analysis reports (PC-lint, Cppcheck)
- Coverage reports (gcov/lcov)
- Complexity reports (Lizard)
- Code review records
- Test results
- Traceability matrix (RTM)
- Tool validation reports

**Evidence Location**: `docs/reports/` (under version control)

### 6.2 Evidence Review

**Review Process**:
1. Verifier collects evidence from all verification activities
2. Verifier reviews evidence for completeness and correctness
3. Verifier identifies gaps or non-conformances
4. Verifier requests corrective actions from responsible parties
5. Verifier verifies corrective actions completed
6. Verifier approves phase completion (or rejects if evidence insufficient)

**Review Criteria**:
- Evidence is objective (tool-generated or independently reviewed)
- Evidence is complete (all verification activities performed)
- Evidence demonstrates compliance with EN 50128 requirements
- Evidence is traceable to requirements

### 6.3 Evidence Archival

**Archival Process**:
- All evidence SHALL be baselined per phase (SCMP Section 4.2)
- Evidence SHALL be stored under version control (Git)
- Evidence SHALL be included in release package
- Evidence SHALL be retained per project records retention policy

**SIL 3-4 Requirement**: Evidence SHALL be independently reviewed and approved before phase completion.

---

## 7. VERIFICATION ACCEPTANCE CRITERIA

### 7.1 Phase Completion Criteria

**Phase SHALL NOT be approved until all verification acceptance criteria are met.**

| Phase | Acceptance Criteria | Evidence Required |
|-------|---------------------|-------------------|
| **Planning** | All plans complete, consistent, EN 50128 compliant | Planning Verification Report |
| **Requirements** | All requirements unambiguous, testable, traced; SIL assigned | Requirements Verification Report, RTM |
| **Design** | Design complete, traceable, modular (SIL 2+), complexity estimated | Design Verification Report, RTM |
| **Implementation** | MISRA C compliant (SIL 2+), complexity within limits, 100% unit test coverage | Implementation Verification Report, Static analysis reports, Coverage reports, RTM |
| **Integration** | All integration tests passed, interfaces verified | Integration Verification Report |
| **Testing** | Coverage per Table A.21, all tests passed, traceability complete | Testing Verification Report, Coverage reports, RTM |

### 7.2 Non-Conformance Handling

**Process**:
1. Verifier identifies non-conformance (evidence missing, criteria not met)
2. Verifier documents non-conformance in verification report
3. Verifier assigns corrective action to responsible party
4. Responsible party implements corrective action
5. Verifier verifies corrective action completed
6. Verifier updates verification report status

**Non-Conformance Severity**:
- **Critical**: Blocks phase approval (e.g., missing traceability for SIL 3-4)
- **Major**: Requires corrective action before approval (e.g., MISRA C violations)
- **Minor**: Can be deferred to next phase (e.g., documentation typos)

**SIL 3-4**: All Critical and Major non-conformances MUST be resolved before phase approval.

---

## 8. VERIFICATION SCHEDULE

### 8.1 Verification Milestones

| Milestone | Phase | Planned Date | Verification Activities | Deliverable |
|-----------|-------|--------------|-------------------------|-------------|
| **Planning Gate** | Phase 1 | [Date] | Document review, consistency check | Planning Verification Report |
| **Requirements Gate** | Phase 2 | [Date] | Requirements review, traceability check, SIL assignment | Requirements Verification Report |
| **Design Gate** | Phase 3 | [Date] | Design review, architecture review, traceability check | Design Verification Report |
| **Implementation Gate** | Phase 4 | [Date] | Static analysis, MISRA C check, code review, complexity analysis | Implementation Verification Report |
| **Integration Gate** | Phase 5 | [Date] | Integration test review, interface verification | Integration Verification Report |
| **Testing Gate** | Phase 6 | [Date] | Coverage analysis, traceability verification, test result review | Testing Verification Report |

### 8.2 Verification Effort Estimate

[Provide effort estimates per phase, e.g.:]

| Phase | Verification Effort (person-hours) | Notes |
|-------|------------------------------------|-------|
| Planning | 16 hours | Document review |
| Requirements | 40 hours | Requirements review, RTM setup |
| Design | 32 hours | Design review, complexity estimation |
| Implementation | 80 hours | Static analysis, code review, MISRA C |
| Integration | 24 hours | Integration test review |
| Testing | 40 hours | Coverage analysis, traceability verification |
| **Total** | **232 hours** | ~29 person-days |

**SIL 3-4**: Add 30-50% effort for independent verification activities.

---

## 9. RISK MANAGEMENT

### 9.1 Verification Risks

| Risk | Probability | Impact | Mitigation |
|------|-------------|--------|------------|
| **Insufficient tool qualification** | Medium | High | Qualify tools early (Phase 1) |
| **Incomplete traceability** | Medium | High | Establish RTM in Phase 2, update continuously |
| **Verifier independence compromise** (SIL 3-4) | Low | Critical | Enforce organizational independence, separate reporting |
| **Inadequate coverage** | Medium | High | Monitor coverage continuously, allocate time for additional tests |
| **MISRA C non-compliance** | Medium | Medium | Run static analysis early and often, training for developers |

### 9.2 Risk Monitoring

**Risk Review Frequency**: Monthly (or per phase gate)

**Risk Owner**: Verifier

**Escalation**: Critical risks escalated to Project Manager and Lifecycle Coordinator

---

## 10. VERIFICATION TOOLS AND RESOURCES

### 10.1 Tool List

See Section 3.3 for detailed tool list.

### 10.2 Resource Requirements

**Personnel**:
- Verifier (primary): [X person-months]
- QA Manager (support): [X person-months]
- Configuration Manager (traceability): [X person-months]

**Hardware**:
- Development workstations with static analysis tools
- Test environment (if needed for verification)

**Software**:
- PC-lint Plus (MISRA C checker)
- Cppcheck (static analyzer)
- gcov/lcov (coverage tools)
- Lizard (complexity analyzer)
- Git (version control)

---

## 11. COMPLIANCE MATRIX

### 11.1 EN 50128 Section 6.2 Compliance

| Requirement | Section | Evidence | Status |
|-------------|---------|----------|--------|
| **Verification plan established** | 6.2.2 | This document (SVP) | ✓ |
| **Verification independence (SIL 3-4)** | 6.2.3 | Section 2.2 | ✓ |
| **Verification activities defined** | 6.2.4 | Section 4 | ✓ |
| **Verification techniques selected** | Table A.5 | Section 3.2 | ✓ |
| **Traceability (SIL 3-4)** | Table A.5 | Section 5 | ✓ |
| **Test coverage (SIL 3-4)** | Table A.21 | Section 4.6.2 | ✓ |
| **Static analysis (SIL 3-4)** | Table A.19 | Section 4.4 | ✓ |
| **Evidence management** | 6.2.5 | Section 6 | ✓ |

### 11.2 EN 50128 Table A.5 Compliance (Verification Techniques)

| # | Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Implementation |
|---|-----------|-------|---------|---------|----------------|
| **3** | Static Analysis | - | HR | **M** | PC-lint, Cppcheck (Section 4.4) |
| **4** | Dynamic Analysis and Testing | - | HR | **M** | Unity tests (Section 4.4) |
| **5** | Metrics | - | R | HR | Complexity, coverage (Section 4.4, 4.6) |
| **7** | Traceability | R | HR | **M** | RTM (Section 5) |
| **9** | Test Coverage for Code | R | HR | **M** | gcov/lcov (Section 4.6) |

---

## 12. REFERENCES

### 12.1 Normative References

| Reference | Document |
|-----------|----------|
| **[EN50128]** | EN 50128:2011 Railway applications - Software for railway control and protection systems |
| **[MISRAC]** | MISRA C:2012 Guidelines for the use of the C language in critical systems |

### 12.2 Project References

| Reference | Document |
|-----------|----------|
| **[SQAP]** | Software Quality Assurance Plan, DOC-SQAP-YYYY-NNN |
| **[SCMP]** | Software Configuration Management Plan, DOC-SCMP-YYYY-NNN |
| **[SRS]** | Software Requirements Specification, DOC-SRS-YYYY-NNN |
| **[SAS]** | Software Architecture Specification, DOC-SAS-YYYY-NNN |
| **[SDS]** | Software Design Specification, DOC-SDS-YYYY-NNN |

---

## APPENDICES

### Appendix A: Verification Checklist Templates

[Include verification checklists for each phase - requirements review, design review, code review, etc.]

### Appendix B: Verification Report Template

```markdown
# [Phase] Verification Report

**Document ID**: DOC-VER-[PHASE]-YYYY-NNN  
**Verification Date**: YYYY-MM-DD  
**Verifier**: [Name]

## 1. Verification Scope
[Describe what was verified]

## 2. Verification Activities Performed
[List activities from SVP Section 4]

## 3. Verification Results
| Activity | Status | Evidence | Findings |
|----------|--------|----------|----------|
| Static analysis | Pass | Static-analysis-report.pdf | 3 minor issues |

## 4. Non-Conformances
| # | Severity | Description | Assigned To | Due Date | Status |
|---|----------|-------------|-------------|----------|--------|
| 1 | Major | MISRA C Rule 10.1 violation in module.c:45 | [Developer] | [Date] | Open |

## 5. Verification Conclusion
- **Overall Result**: [Pass / Fail / Pass with Conditions]
- **Recommendation**: [Approve phase / Request corrective actions]
- **Verifier Signature**: ___________________
- **Date**: YYYY-MM-DD
```

### Appendix C: Traceability Matrix (RTM) Template

See Section 5.2 for RTM format.

---

## DOCUMENT HISTORY

This document is maintained under configuration control per SCMP. All changes SHALL be approved by the Change Control Board (CCB).

**Current Version**: [Version from header]  
**Last Updated**: [Date from header]  
**Next Review**: [Date - recommended per phase gate]

---

**END OF DOCUMENT**
