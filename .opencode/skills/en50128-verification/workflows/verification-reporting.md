# Verification Reporting Workflow for EN 50128

**Purpose**: Step-by-step workflow for creating verification reports compliant with EN 50128 Section 6.2.4.13.

**Scope**: All lifecycle phases - documents verification activities, results, defects, and conclusions for each phase.

**Audience**: Verifiers (VER), V&V Managers (VMGR), Quality Assurance (QUA)

**EN 50128 Reference**: 
- Section 6.2.4.13 "Software Verification Report"
- Section 6.2.4.14 "Contents of Verification Report"
- Table A.5 "Verification and Testing techniques"
- Annex C "Document control summary"

**Related Documents**:
- `workflows/verification-planning.md` - Verification strategy and techniques
- `workflows/static-analysis-workflow.md` - Static analysis execution
- `workflows/traceability-verification.md` - Traceability verification
- `resources/verification-metrics.md` - Metrics calculation and reporting
- `report-templates/` - Verification report templates

---

## Table of Contents

1. [Verification Reporting Overview](#1-verification-reporting-overview)
2. [The 11 Verification Reports](#2-the-11-verification-reports)
3. [Standard Report Structure](#3-standard-report-structure)
4. [Step 1: Select Report Template](#step-1-select-report-template)
5. [Step 2: Initialize Report Document](#step-2-initialize-report-document)
6. [Step 3: Execute Verification Activities](#step-3-execute-verification-activities)
7. [Step 4: Document Verification Results](#step-4-document-verification-results)
8. [Step 5: Record Defects and Issues](#step-5-record-defects-and-issues)
9. [Step 6: Analyze Traceability](#step-6-analyze-traceability)
10. [Step 7: Calculate Metrics](#step-7-calculate-metrics)
11. [Step 8: Write Recommendations and Conclusion](#step-8-write-recommendations-and-conclusion)
12. [Step 9: QUA Template Compliance Review](#step-9-qua-template-compliance-review)
13. [Step 10: VMGR Technical Review](#step-10-vmgr-technical-review)
14. [Step 11: Finalize and Archive Report](#step-11-finalize-and-archive-report)
15. [Phase-Specific Verification Requirements](#phase-specific-verification-requirements)
16. [Evidence Collection Guidelines](#evidence-collection-guidelines)
17. [Common Reporting Issues](#common-reporting-issues)

---

## 1. Verification Reporting Overview

### Purpose of Verification Reports

Verification reports provide:
- **Evidence of verification activities** performed per SVP
- **Results of verification** against defined criteria
- **Defects discovered** and remediation status
- **Traceability analysis** (MANDATORY SIL 3-4)
- **Metrics** demonstrating quality
- **Independent assessment** (MANDATORY SIL 3-4)
- **Approval/rejection decision** for phase completion

### EN 50128 Requirements

**Section 6.2.4.13**: "The results of the verification activities shall be reported in accordance with the SVP"

**Section 6.2.4.14** requires verification reports to include:
- Verification activities performed
- Verification results (pass/fail per criterion)
- Defects and anomalies
- Traceability analysis
- Metrics
- Verifier statement and approval

### Verification Report Types by Lifecycle Phase

| Phase | Report Document ID | EN 50128 Ref | Primary Verification Focus |
|-------|-------------------|--------------|---------------------------|
| **Phase 1: Planning** | DOC-2 SQAP Verification Report | Annex C #2 | SQAP completeness, plan adequacy |
| **Phase 1: Planning** | DOC-4 Software Verification Plan | Annex C #4 | SVP itself (meta-verification) |
| **Phase 2: Requirements** | DOC-8 SW Requirements Verification Report | Annex C #8 | SRS completeness, traceability, testability |
| **Phase 3: Architecture** | DOC-14 SW Architecture and Design Verification Report | Annex C #14 | SAS/SDS design quality, modularity, interfaces |
| **Phase 4: Component Design** | DOC-17 SW Component Design Verification Report | Annex C #17 | Component design completeness, complexity |
| **Phase 5: Implementation** | DOC-19 SW Source Code Verification Report | Annex C #20 | MISRA C, static analysis, complexity, coverage |
| **Phase 6: Integration** | DOC-23 SW Integration Verification Report | Annex C #23 | Integration test results, interface verification |
| **Phase 6: Integration** | DOC-32 SW/HW Integration Verification Report | Annex C #32 | Hardware integration test results |
| **Phase 6: Validation** | DOC-35 Overall SW Test Verification Report | Annex C #35 | System test results, validation coverage |
| **Phase 7: Validation** | DOC-40 SW Validation Verification Report | Annex C #40 | Validation results, acceptance criteria |
| **Phase 8: Maintenance** | DOC-44 SW Maintenance Verification Report | Annex C #44 | Maintenance process verification |

### Report Review Flow (SIL 3-4)

```
┌──────────────────────────────────────────────────────────────┐
│ STEP 1: VER Creates Verification Report                      │
│ - Execute verification activities per SVP                    │
│ - Document results with evidence                             │
│ - Calculate metrics                                           │
│ - Write verifier statement                                   │
└──────────────────────────────────────────────────────────────┘
                          ↓
┌──────────────────────────────────────────────────────────────┐
│ STEP 2: QUA Template Compliance Review (1 pass)              │
│ - Check document structure (12 sections + 4 appendices)      │
│ - Verify Document Control table                              │
│ - Verify Approvals table                                     │
│ - Check section completeness                                 │
│ DECISION: Approve OR Reject (VER fixes, resubmits ONCE)      │
└──────────────────────────────────────────────────────────────┘
                          ↓
┌──────────────────────────────────────────────────────────────┐
│ STEP 3: VMGR Technical Review (SIL 3-4)                      │
│ - Verify verification methods adequate                       │
│ - Review evidence quality and completeness                   │
│ - Assess defect severity and resolution                      │
│ - Verify traceability (100% MANDATORY SIL 3-4)               │
│ - Check metrics meet SIL requirements                        │
│ DECISION: Approve OR Reject (with mandatory actions)         │
└──────────────────────────────────────────────────────────────┘
                          ↓
┌──────────────────────────────────────────────────────────────┐
│ STEP 4: COD Gate Check                                       │
│ - COD enforces gate based on VMGR approval                   │
│ - If VMGR approved: Gate PASS → proceed to next phase        │
│ - If VMGR rejected: Gate BLOCKED → PM coordinates fixes      │
└──────────────────────────────────────────────────────────────┘
```

**Key Point**: VMGR approval CANNOT be overridden by PM or COD. VMGR has independent V&V authority.

---

## 2. The 11 Verification Reports

### Report 1: DOC-2 SQAP Verification Report

**Phase**: Phase 1 (Planning)  
**Verifies**: Software Quality Assurance Plan (SQAP)  
**EN 50128 Reference**: Annex C #2, Section 6.5  
**Template**: `report-templates/SQAP-Verification-Report.md`

**Key Verification Activities**:
- SQAP addresses all EN 50128 Section 6.5 requirements
- Quality activities defined for each lifecycle phase
- Review and audit schedule defined
- Metrics and criteria defined
- QUA independence established (SIL 3-4)
- Configuration management integrated

**Critical Criteria**:
- All Table A.9 techniques addressed (Configuration Management MANDATORY all SILs)
- Code review process defined (MANDATORY all SILs)
- Quality gates defined per phase
- Tool qualification approach defined
- Traceability approach defined (MANDATORY SIL 3-4)

**Metrics**:
- SQAP completeness: 100% of EN 50128 Section 6.5 requirements addressed
- Review coverage: All lifecycle phases have defined QA activities

### Report 2: DOC-4 Software Verification Plan

**Phase**: Phase 1 (Planning)  
**Verifies**: Software Verification Plan (SVP) itself  
**EN 50128 Reference**: Annex C #4, Section 6.2.4  
**Template**: `report-templates/Software-Verification-Plan-Verification-Report.md`

**Key Verification Activities**:
- SVP addresses all EN 50128 Section 6.2.4.1-6.2.4.9 requirements
- Verification techniques selected from Tables A.5, A.19, A.21
- Static analysis strategy defined (MANDATORY SIL 3-4)
- Coverage requirements defined per SIL
- Tool qualification plan complete
- Verifier independence established (MANDATORY SIL 3-4)

**Critical Criteria**:
- Table A.5 techniques: Static Analysis (MANDATORY SIL 3-4), Traceability (MANDATORY SIL 3-4)
- Table A.19: Control Flow (M), Data Flow (M) for SIL 3-4
- Table A.21: Statement (M), Branch (M), Condition (M) for SIL 3-4
- Tool list complete with qualification status
- Verification activities defined for all 8 lifecycle phases

**Metrics**:
- SVP completeness: 100% of EN 50128 Section 6.2.4 requirements addressed
- Technique coverage: All MANDATORY techniques for target SIL included

### Report 3: DOC-8 Software Requirements Verification Report

**Phase**: Phase 2 (Requirements)  
**Verifies**: Software Requirements Specification (SRS), Hazard Log, Overall SW Test Specification  
**EN 50128 Reference**: Annex C #8, Section 7.2  
**Template**: `report-templates/Software-Requirements-Verification-Report.md`

**Key Verification Activities**:
- Requirements completeness (all system requirements allocated)
- Requirements quality (unambiguous, testable, traceable, consistent)
- Traceability: System Requirements → Software Requirements (100% SIL 3-4)
- SIL assignment correct per EN 50128 Table A.1
- Safety requirements identified and traced to Hazard Log
- Test specification covers all requirements
- Requirements review checklist

**Critical Criteria**:
- All requirements use SHALL/SHOULD/MAY keywords correctly
- All requirements have unique IDs (REQ-XXX-NNN format)
- All requirements have @trace tags
- All requirements have assigned SIL level
- All safety requirements traced to hazards
- Zero ambiguous requirements
- Zero untestable requirements

**Metrics**:
- Requirements completeness: 100% system requirements covered
- Requirements quality: 100% pass quality criteria
- Traceability: 100% forward (Sys→SW), 100% backward (SW→Sys)
- Safety traceability: 100% safety requirements → hazards
- Test coverage: 100% requirements have test cases

### Report 4: DOC-14 Software Architecture and Design Verification Report

**Phase**: Phase 3 (Architecture and Design)  
**Verifies**: Software Architecture Specification (SAS), Software Design Specification (SDS), SW Interface Specifications, Integration Test Specifications  
**EN 50128 Reference**: Annex C #14, Section 7.3  
**Template**: `report-templates/Software-Architecture-Design-Verification-Report.md`

**Key Verification Activities**:
- Architecture completeness (all requirements allocated to components)
- Modular approach verified (MANDATORY SIL 2+)
- Interface specifications complete and consistent
- Defensive programming patterns present (HR SIL 3-4)
- Traceability: Requirements → Architecture → Design (100% SIL 3-4)
- Integration test specifications complete
- Design complexity analysis (estimated CCN)
- Static allocation design (no malloc/free for SIL 2+)
- Design review checklist

**Critical Criteria**:
- All requirements traced to architecture components
- All components have defined interfaces
- All modules use static allocation (SIL 2+)
- No recursion in design (HR SIL 3-4)
- Defensive programming patterns documented
- Complexity targets set (≤10 for SIL 3-4)
- Safety functions identified and isolated

**Metrics**:
- Architecture completeness: 100% requirements → components
- Interface completeness: 100% interfaces specified
- Traceability: 100% Requirements → Architecture → Design
- Estimated complexity: % functions with CCN ≤ target
- Module count, interface count, layer depth

### Report 5: DOC-17 Software Component Design Verification Report

**Phase**: Phase 4 (Component Design)  
**Verifies**: Software Component Design Specification, SW Component Test Specification  
**EN 50128 Reference**: Annex C #17, Section 7.4  
**Template**: `report-templates/Software-Component-Design-Verification-Report.md`

**Key Verification Activities**:
- Component design completeness (all functions specified)
- Detailed design quality (pseudo-code, data structures, algorithms)
- Traceability: Architecture → Component Design (100% SIL 3-4)
- Unit test specifications complete for all functions
- Complexity analysis of design (pseudo-code CCN estimation)
- Data structure safety (static arrays, bounds checking)
- Error handling design complete

**Critical Criteria**:
- All architectural components have detailed designs
- All functions have specifications (inputs, outputs, behavior, error handling)
- All functions have unit test specifications
- Traceability complete to architecture
- Estimated complexity within limits
- Error handling specified for all failure modes

**Metrics**:
- Design completeness: 100% components → functions
- Test specification coverage: 100% functions have unit test specs
- Traceability: 100% Architecture → Component Design
- Estimated complexity: % functions with estimated CCN ≤ target

### Report 6: DOC-19 Software Source Code Verification Report

**Phase**: Phase 5 (Implementation and Testing)  
**Verifies**: Software Source Code, SW Component Test Report  
**EN 50128 Reference**: Annex C #20, Section 7.5  
**Template**: `report-templates/Software-Source-Code-Verification-Report.md`

**This is the MOST CRITICAL verification report** with extensive static analysis, MISRA C compliance, complexity, and coverage verification.

**Key Verification Activities**:
1. **Static Analysis** (MANDATORY SIL 3-4):
   - Cppcheck: General static analysis, control/data flow
   - PC-lint Plus: MISRA C:2012 all 178 rules + 16 directives
   - Clang Static Analyzer: Deep semantic analysis
2. **Complexity Analysis**:
   - Lizard: Cyclomatic Complexity (CCN ≤ 10 SIL 3-4, ≤ 15 SIL 2)
3. **Coverage Analysis**:
   - gcov/lcov: Statement (100% SIL 2+), Branch (100% SIL 2+), Condition (100% SIL 3-4)
   - MC/DC: Highly Recommended SIL 3-4
4. **Code Review**:
   - Manual review by independent verifier (MANDATORY SIL 3-4)
   - Defensive programming checklist
   - MISRA C compliance review
5. **Traceability**:
   - Design → Code → Tests (100% SIL 3-4)

**Critical Criteria**:
- **MISRA C Mandatory Rules**: Zero violations (SIL 2+)
- **MISRA C Required Rules**: Zero violations OR justified deviations (SIL 2+)
- **Static Analysis Critical Issues**: Zero unresolved critical issues
- **Complexity**: 100% functions CCN ≤ target (10 for SIL 3-4)
- **Statement Coverage**: 100% (MANDATORY SIL 2+)
- **Branch Coverage**: 100% (MANDATORY SIL 2+)
- **Condition Coverage**: 100% (MANDATORY SIL 3-4)
- **Traceability**: 100% bidirectional (Design ↔ Code ↔ Tests)

**Metrics**:
- MISRA C compliance rate: (rules passed / total rules) × 100%
- Static analysis defect density: defects per KLOC
- Cyclomatic complexity: average, max, % within target
- Statement coverage: % (target 100% SIL 2+)
- Branch coverage: % (target 100% SIL 2+)
- Condition coverage: % (target 100% SIL 3-4)
- MC/DC coverage: % (target 100% SIL 3-4 if used)
- Traceability: % forward, % backward

**Tool Commands**:
```bash
# Static analysis
cppcheck --enable=all --xml --xml-version=2 src/ 2> cppcheck_report.xml
pclp64 --template=misra src/*.c > pclint_report.txt
scan-build -o analysis_results make

# Complexity
lizard src/ -l c --CCN 10 --xml > lizard_report.xml

# Coverage
gcov -b -c src/*.c
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html

# MC/DC (if used)
python3 tools/mcdc/mcdc_analyzer.py --source src/ --gcov coverage.info --output mcdc_report.json
```

### Report 7: DOC-23 Software Integration Verification Report

**Phase**: Phase 6 (Integration)  
**Verifies**: Software Integration Test Report  
**EN 50128 Reference**: Annex C #23, Section 7.6  
**Template**: `report-templates/Software-Integration-Verification-Report.md`

**Key Verification Activities**:
- Integration test execution results verification
- Interface testing completeness (all interfaces tested)
- Performance testing results (HR SIL 3-4)
- Integration defects analysis
- Integration traceability verification
- Multi-module interaction verification

**Critical Criteria**:
- All integration test cases executed
- All interface specifications tested
- All integration test cases passed
- Performance requirements met (if applicable)
- Integration traceability complete

**Metrics**:
- Integration test pass rate: % passed / total
- Interface coverage: % interfaces tested
- Defect density: defects per module pair

### Report 8: DOC-32 Software/Hardware Integration Verification Report

**Phase**: Phase 6 (Integration)  
**Verifies**: Software/Hardware Integration Test Report  
**EN 50128 Reference**: Annex C #32, Section 7.6  
**Template**: `report-templates/Software-Hardware-Integration-Verification-Report.md`

**Key Verification Activities**:
- SW/HW integration test execution results verification
- Hardware interface testing (all HW interfaces tested)
- Timing and performance verification on target hardware
- Resource usage verification (memory, CPU, stack)
- Interrupt handling verification
- Hardware fault injection testing

**Critical Criteria**:
- All SW/HW integration test cases executed on target hardware
- All hardware interfaces tested
- All timing requirements met on target
- Memory usage within bounds
- Stack usage within bounds (no stack overflow)
- Interrupt latency within requirements

**Metrics**:
- SW/HW test pass rate: % passed / total
- HW interface coverage: % HW interfaces tested
- Timing margin: % of worst-case deadline
- Memory usage: % of available RAM/ROM
- Stack usage: maximum observed, % of allocated

### Report 9: DOC-35 Overall Software Test Verification Report

**Phase**: Phase 6 (Validation)  
**Verifies**: Overall Software Test Report (system testing)  
**EN 50128 Reference**: Annex C #35, Section 7.7  
**Template**: `report-templates/Overall-Software-Test-Verification-Report.md`

**Key Verification Activities**:
- System test execution results verification
- System requirements coverage (all system requirements tested)
- End-to-end scenario testing
- Safety scenario testing
- Performance testing (MANDATORY SIL 3-4)
- Stress testing and boundary testing

**Critical Criteria**:
- All system test cases executed
- All system requirements covered by tests
- All system test cases passed
- All safety scenarios tested and passed
- Performance requirements met
- System-level traceability complete (Requirements → Tests)

**Metrics**:
- System test pass rate: % passed / total
- System requirements coverage: % requirements tested
- Safety scenario coverage: 100% (MANDATORY SIL 3-4)
- Performance test results vs. requirements

### Report 10: DOC-40 Software Validation Verification Report

**Phase**: Phase 7 (Validation)  
**Verifies**: Software Validation Report  
**EN 50128 Reference**: Annex C #40, Section 7.7  
**Template**: `report-templates/Software-Validation-Verification-Report.md`

**Key Verification Activities**:
- Validation report completeness
- Validation test results verification
- Customer acceptance criteria verification
- Operational scenario validation
- Safety validation (all safety requirements validated)
- Validation in target environment

**Critical Criteria**:
- All validation criteria met
- All customer acceptance criteria met
- All operational scenarios validated
- All safety requirements validated
- Validation performed by independent validator (MANDATORY SIL 3-4)

**Metrics**:
- Validation criteria met: % / total
- Customer acceptance: pass/fail
- Safety validation: 100% safety requirements validated

### Report 11: DOC-44 Software Maintenance Verification Report

**Phase**: Phase 8 (Maintenance)  
**Verifies**: Software Maintenance Records, Software Maintenance Plan  
**EN 50128 Reference**: Annex C #44, Section 8  
**Template**: `report-templates/Software-Maintenance-Verification-Report.md`

**Key Verification Activities**:
- Maintenance process verification (change control, impact analysis)
- Maintenance records completeness
- Regression testing after changes
- Configuration management during maintenance
- Traceability maintenance

**Critical Criteria**:
- All changes have approved change requests
- Impact analysis performed for all changes
- Regression testing performed after all changes
- Configuration management maintained
- Traceability updated after changes

**Metrics**:
- Changes with approved CRs: 100%
- Changes with impact analysis: 100%
- Changes with regression tests: 100%

---

## 3. Standard Report Structure

All verification reports follow this 12-section + 4-appendix structure:

### Main Sections (12 sections)

1. **Header**
   - Document ID: `DOC-[TYPE]VER-YYYY-NNN` (e.g., `DOC-IMPVER-2026-001`)
   - Document Type: `[Phase] Verification Report`
   - Phase: `Phase N: [Phase Name]`
   - EN 50128 Reference: `Annex C #NN, Section X.Y`
   - Project Name, SIL Level, Date, Version

2. **Document Control**
   - Version history table (version, date, author, reviewer, approver, changes)
   - Configuration item ID
   - Baseline reference

3. **Approvals**
   - Prepared by: VER (Verifier name, date, signature)
   - Reviewed by: QUA (Quality Assurance name, date, signature)
   - Approved by: VMGR (V&V Manager name, date, signature) for SIL 3-4
   - Independence Declaration: "The undersigned verifier declares independence from the software development team per EN 50128 Section 5.1.2.10" (SIL 3-4)

4. **Executive Summary**
   - Project name and SIL level
   - Verification scope (documents/artifacts verified)
   - Overall verification result: PASS / PASS WITH CONDITIONS / FAIL
   - Critical findings summary
   - Recommendation for phase gate

5. **Introduction**
   - Purpose of verification report
   - Scope of verification
   - References (SVP, SRS, SAS, SDS, source code, test reports, EN 50128)
   - Verification team (VER, VMGR, independence status)
   - Glossary and abbreviations

6. **Verification Methodology**
   - Verification techniques applied (from EN 50128 Tables A.5, A.19, A.21)
   - Verification activities performed
   - Tools used (with versions and qualification status)
   - Verification schedule and effort

7. **Verification Criteria**
   - Phase-specific criteria from `verification-criteria/[phase]-verification-criteria.yaml`
   - Pass/fail criteria for each criterion
   - SIL-specific requirements

8. **Verification Results**
   - Detailed results for each criterion
   - Pass/fail status per criterion
   - Evidence references (tool reports, checklists, reviews)
   - Observations and notes

9. **Defects and Issues**
   - Defect summary table (Critical, Major, Minor counts)
   - Critical defects (detailed description, impact, status, resolution)
   - Major defects (detailed description, impact, status, resolution)
   - Minor defects and observations
   - Defect metrics (defect density, defect distribution)

10. **Traceability Analysis**
    - Forward traceability results (% complete)
    - Backward traceability results (% complete)
    - Traceability gaps identified
    - Safety requirements traceability (100% MANDATORY SIL 3-4)

11. **EN 50128 Compliance**
    - Table A.5 techniques applied (Static Analysis, Traceability, etc.)
    - Table A.19 techniques applied (Control Flow, Data Flow - for code verification)
    - Table A.21 coverage achieved (Statement, Branch, Condition - for code verification)
    - Independence requirements met (SIL 3-4)

12. **Metrics**
    - Phase-specific quality metrics
    - Comparison with targets
    - Trend analysis (if multiple reports)

13. **Recommendations**
    - Mandatory actions (must be resolved before phase gate)
    - Suggested improvements (should be considered)
    - Areas of concern (observations for future phases)

14. **Conclusion**
    - Overall assessment of verification results
    - Conditions for approval (if any)
    - Verifier statement: "Based on the verification activities performed, I [approve/conditionally approve/reject] the [artifact] for progression to [next phase]."
    - Verifier signature and date

### Appendices (4 appendices)

**Appendix A: Verification Checklist**
- Phase-specific verification checklist
- Each item marked: Pass / Fail / N/A
- Notes for each item

**Appendix B: Traceability Matrix**
- Complete traceability matrix for phase
- Format: Source ID | Target ID(s) | Status | Notes
- Example: `REQ-FUNC-001 | DES-ARCH-003, CODE-calculate_speed, TEST-UT-001 | Complete | -`

**Appendix C: Defect Details**
- Detailed defect reports
- Each defect: ID, Severity, Description, Location, Impact, Status, Resolution, Verifier Comments

**Appendix D: Tool Output Summaries**
- Static analysis tool reports (Cppcheck, PC-lint, Clang)
- Coverage reports (lcov summary)
- Complexity reports (Lizard)
- Test execution reports
- Key excerpts or references to full reports

---

## Step 1: Select Report Template

### Identify Phase and Report Type

**Activity**: Determine which verification report to create based on current lifecycle phase.

**Inputs**:
- Current lifecycle phase (from COD or PM)
- Phase deliverables (from phase definition)
- LIFECYCLE_STATE.md (project status)

**Decision Tree**:
```
Current Phase?
├─ Phase 1 (Planning)
│  ├─ Verifying SQAP? → Use SQAP-Verification-Report.md
│  └─ Verifying SVP? → Use Software-Verification-Plan-Verification-Report.md
├─ Phase 2 (Requirements)
│  └─ Use Software-Requirements-Verification-Report.md
├─ Phase 3 (Architecture & Design)
│  └─ Use Software-Architecture-Design-Verification-Report.md
├─ Phase 4 (Component Design)
│  └─ Use Software-Component-Design-Verification-Report.md
├─ Phase 5 (Implementation)
│  └─ Use Software-Source-Code-Verification-Report.md
├─ Phase 6 (Integration)
│  ├─ SW Integration? → Use Software-Integration-Verification-Report.md
│  └─ SW/HW Integration? → Use Software-Hardware-Integration-Verification-Report.md
├─ Phase 7 (Validation)
│  ├─ System Testing? → Use Overall-Software-Test-Verification-Report.md
│  └─ Validation? → Use Software-Validation-Verification-Report.md
└─ Phase 8 (Maintenance)
   └─ Use Software-Maintenance-Verification-Report.md
```

**Command**:
```bash
# Copy template to project docs/reports/ directory
cp .opencode/skills/en50128-verification/report-templates/[Template-Name].md \
   docs/reports/DOC-[TYPE]VER-$(date +%Y)-001.md
```

**Example**:
```bash
# For Phase 5 (Implementation) verification
cp .opencode/skills/en50128-verification/report-templates/Software-Source-Code-Verification-Report.md \
   docs/reports/DOC-IMPVER-2026-001.md
```

---

## Step 2: Initialize Report Document

### Update Header and Metadata

**Activity**: Fill in document header, document control, and approvals sections.

**Header Fields**:
```markdown
# Software [Phase] Verification Report

**Document ID**: DOC-[TYPE]VER-YYYY-NNN  
**Document Type**: [Phase] Verification Report  
**Phase**: Phase N: [Phase Name]  
**EN 50128 Reference**: Annex C #NN, Section X.Y  
**Project Name**: [Your Project Name]  
**SIL Level**: SIL [0/1/2/3/4]  
**Date**: YYYY-MM-DD  
**Version**: 1.0  
```

**Document Control Table**:
```markdown
| Version | Date | Author | Reviewer | Approver | Changes |
|---------|------|--------|----------|----------|---------|
| 0.1 | 2026-03-13 | J. Smith (VER) | - | - | Initial draft |
| 0.2 | 2026-03-14 | J. Smith (VER) | M. Johnson (QUA) | - | QUA review incorporated |
| 1.0 | 2026-03-15 | J. Smith (VER) | M. Johnson (QUA) | A. Brown (VMGR) | Final approval |

**Configuration Item ID**: CI-DOC-IMPVER-2026-001  
**Baseline**: BASELINE-PHASE5-001  
```

**Approvals Table** (SIL 3-4):
```markdown
| Role | Name | Date | Signature | Independence |
|------|------|------|-----------|--------------|
| **Prepared by (VER)** | Jane Smith | 2026-03-15 | _J. Smith_ | Independent from development team |
| **Reviewed by (QUA)** | Mark Johnson | 2026-03-15 | _M. Johnson_ | Independent QA function |
| **Approved by (VMGR)** | Alice Brown | 2026-03-15 | _A. Brown_ | Independent V&V Manager |

**Independence Declaration** (SIL 3-4): "The undersigned verifier (Jane Smith) declares independence from the software development team per EN 50128 Section 5.1.2.10. The verifier has had no involvement in requirements, design, or implementation activities for this software."
```

**For SIL 0-2**: Replace VMGR with PM in approvals table.

---

## Step 3: Execute Verification Activities

### Perform Verification per SVP and Phase Criteria

**Activity**: Execute all verification activities defined in the Software Verification Plan (SVP) for this phase.

**Verification Activity Categories**:

1. **Document Review**
   - Check document completeness (all required sections present)
   - Check document quality (clarity, consistency, correctness)
   - Use phase-specific checklists (see Appendix A templates)

2. **Static Analysis** (for code verification)
   - Run Cppcheck, PC-lint Plus, Clang Static Analyzer
   - Run Lizard for complexity analysis
   - See `workflows/static-analysis-workflow.md` for detailed steps

3. **Traceability Verification**
   - Verify forward traceability (Requirements → Design → Code → Tests)
   - Verify backward traceability (Tests → Requirements)
   - See `workflows/traceability-verification.md` for detailed steps

4. **Coverage Analysis** (for code/test verification)
   - Measure statement, branch, condition coverage with gcov/lcov
   - Calculate MC/DC coverage if required (SIL 3-4)
   - Verify coverage meets SIL requirements (100% for SIL 2+ statement/branch)

5. **Metrics Calculation**
   - Calculate phase-specific metrics (complexity, coverage, defect density)
   - See `resources/verification-metrics.md` for metric definitions

6. **Manual Review**
   - Independent verifier reviews artifacts
   - Apply phase-specific criteria from `verification-criteria/[phase]-verification-criteria.yaml`
   - Use checklists for consistency

**Evidence Collection**:
- Save all tool output (XML, JSON, HTML reports)
- Document manual review findings
- Take screenshots of key results
- Reference evidence in verification results section

**Example Commands** (for code verification):
```bash
# Create verification evidence directory
mkdir -p docs/reports/evidence/DOC-IMPVER-2026-001

# Static analysis
cppcheck --enable=all --xml --xml-version=2 src/ 2> docs/reports/evidence/DOC-IMPVER-2026-001/cppcheck_report.xml
pclp64 --template=misra src/*.c > docs/reports/evidence/DOC-IMPVER-2026-001/pclint_report.txt
scan-build -o docs/reports/evidence/DOC-IMPVER-2026-001/clang_analysis make

# Complexity
lizard src/ -l c --CCN 10 --xml > docs/reports/evidence/DOC-IMPVER-2026-001/lizard_report.xml

# Coverage
gcov -b -c src/*.c
lcov --capture --directory . --output-file docs/reports/evidence/DOC-IMPVER-2026-001/coverage.info
genhtml docs/reports/evidence/DOC-IMPVER-2026-001/coverage.info \
        --output-directory docs/reports/evidence/DOC-IMPVER-2026-001/coverage_html

# Traceability
python3 tools/traceability/trace_checker.py --source src/ --requirements docs/SRS.md \
        --output docs/reports/evidence/DOC-IMPVER-2026-001/traceability_matrix.csv
```

---

## Step 4: Document Verification Results

### Record Results for Each Verification Criterion

**Activity**: For each verification criterion, document the result with evidence references.

**Verification Results Format**:
```markdown
#### Criterion [ID]: [Criterion Title]

**Description**: [Criterion description from verification-criteria YAML]

**Pass/Fail Criteria**: [Specific measurable criteria]

**Verification Method**: [Static Analysis / Manual Review / Tool Check / Traceability Check]

**Result**: **PASS** / **FAIL** / **PASS WITH CONDITIONS**

**Evidence**:
- Tool Report: `docs/reports/evidence/DOC-IMPVER-2026-001/[tool]_report.[xml|txt|html]`
- Manual Review Checklist: See Appendix A, items [X-Y]
- [Additional evidence references]

**Findings**:
- [List specific findings, issues, or observations]
- [Reference defects if issues found]

**Verifier Notes**:
- [Additional context, explanations, or observations]
```

**Example** (Code Verification - MISRA C Compliance):
```markdown
#### Criterion IMP-VER-003: MISRA C:2012 Compliance

**Description**: Source code shall comply with MISRA C:2012 coding standard. Zero mandatory rule violations for SIL 2+. Zero required rule violations OR documented deviations for SIL 2+.

**Pass/Fail Criteria**:
- SIL 3-4: Zero mandatory violations, zero required violations (or justified deviations)
- SIL 2: Zero mandatory violations, all required violations justified
- Mandatory rules: 143 rules
- Required rules: 35 rules

**Verification Method**: Static Analysis - PC-lint Plus with MISRA C:2012 configuration

**Result**: **PASS WITH CONDITIONS**

**Evidence**:
- PC-lint Report: `docs/reports/evidence/DOC-IMPVER-2026-001/pclint_report.txt`
- MISRA C Compliance Summary: `docs/reports/evidence/DOC-IMPVER-2026-001/misra_summary.txt`
- Deviation Requests: `docs/deviations/MISRA-DEV-001.md`, `docs/deviations/MISRA-DEV-002.md`

**Findings**:
- **Mandatory Rules**: 0 violations (143/143 rules passed) ✅
- **Required Rules**: 2 violations (33/35 rules passed)
  - Rule 2.2 violation in `sensor.c:145` - Dead code after return (Defect DEF-IMP-001)
  - Rule 8.13 violation in `uart.c:67` - Pointer parameter not declared const (Defect DEF-IMP-002)
- **Advisory Rules**: 12 violations (acceptable for SIL 3)

**Verifier Notes**:
- PASS WITH CONDITIONS: Mandatory rule compliance achieved (zero violations).
- Required rule violations must be resolved OR justified deviations submitted.
- DEF-IMP-001: Dead code removal recommended (fix trivial).
- DEF-IMP-002: Const qualifier addition recommended (fix trivial).
- Recommendation: Fix both violations before final approval. If not fixed, submit deviation requests per MISRA C:2012 Appendix B.
```

**Repeat for all criteria** from `verification-criteria/[phase]-verification-criteria.yaml`.

---

## Step 5: Record Defects and Issues

### Document All Defects Found During Verification

**Activity**: Create detailed defect records for all issues found.

**Defect Summary Table**:
```markdown
## 9. Defects and Issues

### Defect Summary

| Severity | Count | Resolved | Open |
|----------|-------|----------|------|
| **Critical** | 0 | 0 | 0 |
| **Major** | 3 | 1 | 2 |
| **Minor** | 8 | 5 | 3 |
| **Observation** | 12 | - | - |
| **TOTAL** | 23 | 6 | 5 |
```

**Defect Severity Definitions**:
- **Critical**: Prevents progression to next phase, violates MANDATORY EN 50128 requirement, safety hazard
- **Major**: Significant quality issue, violates Highly Recommended EN 50128 requirement, impacts functionality
- **Minor**: Quality issue, violates Recommended EN 50128 requirement, cosmetic issue
- **Observation**: Not a defect, but noted for improvement or future consideration

**Defect Detail Format**:
```markdown
### Critical Defects

#### Defect DEF-[PHASE]-[NNN]: [Short Title]

**Severity**: Critical  
**Status**: Open / Resolved / Deferred  
**Found by**: [Verifier Name]  
**Date Found**: YYYY-MM-DD  
**Location**: [File:Line or Document Section]  

**Description**:
[Detailed description of the defect]

**Impact**:
[Description of impact on safety, functionality, or quality]

**EN 50128 Violation**:
[Which EN 50128 requirement is violated, if any]

**Recommendation**:
[Specific action to resolve the defect]

**Resolution** (if resolved):
[Description of how defect was resolved, date, person responsible]

**Verifier Assessment**:
[Verifier's assessment of resolution adequacy]
```

**Example Critical Defect**:
```markdown
#### Defect DEF-IMP-005: Uninitialized Variable Used in Safety-Critical Function

**Severity**: Critical  
**Status**: Open  
**Found by**: Jane Smith (VER)  
**Date Found**: 2026-03-13  
**Location**: `src/braking.c:234`  

**Description**:
Variable `braking_force` is used without initialization in function `calculate_braking_force()`. The variable is declared on line 230 but used in calculation on line 234 without being assigned a value. This is a SIL 4 safety-critical function.

**Impact**:
- **Safety Impact**: Uninitialized variable in braking calculation could lead to undefined braking force, potentially causing train to fail to stop (Hazard HAZ-001: "Inadequate braking").
- **EN 50128 Impact**: Violates defensive programming requirement (Table A.3 Technique 2, Highly Recommended SIL 3-4).
- **MISRA C Impact**: Violates MISRA C:2012 Rule 9.1 (Mandatory) - "The value of an object with automatic storage duration shall not be read before it has been set".

**EN 50128 Violation**:
- Table A.3, Technique 2 "Defensive Programming" (Highly Recommended SIL 3-4)
- MISRA C:2012 Rule 9.1 (Mandatory)

**Recommendation**:
**MANDATORY ACTION**: Initialize `braking_force` to safe default value (e.g., maximum braking) on line 230:
```c
// BEFORE (DEFECT):
uint32_t braking_force;
// ... (no assignment)
total_force = braking_force * wheel_count; // Line 234 - USES UNINITIALIZED VALUE

// AFTER (FIX):
uint32_t braking_force = MAX_BRAKING_FORCE; // Safe default
if (sensor_valid) {
    braking_force = calculate_from_sensor();
}
total_force = braking_force * wheel_count; // Line 234 - NOW SAFE
```

**Resolution**: 
[To be filled by Implementer]

**Verifier Assessment**:
CRITICAL defect blocks phase gate approval. Must be resolved before final verification approval.
```

**Defect Tracking**:
- All defects recorded in Appendix C
- Critical defects MUST be resolved before phase gate (SIL 3-4)
- Major defects SHOULD be resolved or deferred with justification
- Minor defects may be deferred to future phases

---

## Step 6: Analyze Traceability

### Verify Bidirectional Traceability

**Activity**: Analyze traceability completeness and document results.

**Traceability Analysis Format**:
```markdown
## 10. Traceability Analysis

### Forward Traceability

| Source | Target | Total Items | Traced Items | % Complete | Status |
|--------|--------|-------------|--------------|------------|--------|
| System Requirements | Software Requirements | 45 | 45 | 100% | ✅ PASS |
| Software Requirements | Architecture Components | 78 | 78 | 100% | ✅ PASS |
| Architecture Components | Design Functions | 156 | 156 | 100% | ✅ PASS |
| Design Functions | Source Code | 156 | 153 | 98% | ⚠️ INCOMPLETE |
| Source Code | Unit Tests | 153 | 153 | 100% | ✅ PASS |

### Backward Traceability

| Target | Source | Total Items | Traced Items | % Complete | Status |
|--------|--------|-------------|--------------|------------|--------|
| Software Requirements | System Requirements | 78 | 78 | 100% | ✅ PASS |
| Architecture Components | Software Requirements | 156 | 156 | 100% | ✅ PASS |
| Design Functions | Architecture Components | 156 | 156 | 100% | ✅ PASS |
| Source Code | Design Functions | 153 | 150 | 98% | ⚠️ INCOMPLETE |
| Unit Tests | Source Code | 153 | 153 | 100% | ✅ PASS |

### Traceability Gaps

#### Gap 1: Missing Code for 3 Design Functions
- Design functions without implementation:
  - `DES-FUNC-045`: `validate_sensor_cross_check()` - Not found in source code
  - `DES-FUNC-089`: `log_diagnostic_event()` - Not found in source code
  - `DES-FUNC-112`: `calculate_backup_speed()` - Not found in source code
- **Impact**: Design-to-Code traceability incomplete (98%)
- **Recommendation**: Implement missing functions OR remove from design if not needed

#### Gap 2: Orphan Code (3 functions not traced to design)
- Source code functions without design traceability:
  - `src/util.c:145`: `helper_function_a()` - No @trace tag to design
  - `src/util.c:189`: `helper_function_b()` - No @trace tag to design
  - `src/debug.c:67`: `print_debug_info()` - No @trace tag to design
- **Impact**: Code-to-Design backward traceability incomplete (98%)
- **Recommendation**: Add @trace tags to design OR remove functions if unused

### Safety Requirements Traceability (SIL 3-4 MANDATORY)

| Safety Requirement ID | Traced to Design | Traced to Code | Traced to Test | Status |
|-----------------------|------------------|----------------|----------------|--------|
| SREQ-SAFE-001 | ✅ DES-ARCH-005 | ✅ brake.c:234 | ✅ TEST-IT-012 | ✅ Complete |
| SREQ-SAFE-002 | ✅ DES-ARCH-009 | ✅ sensor.c:145 | ✅ TEST-IT-015 | ✅ Complete |
| SREQ-SAFE-003 | ✅ DES-ARCH-012 | ✅ safety.c:89 | ✅ TEST-UT-045, TEST-IT-018 | ✅ Complete |
| ... | ... | ... | ... | ... |

**Safety Traceability**: 15/15 safety requirements (100%) fully traced ✅ PASS

### Traceability Matrix

See **Appendix B** for complete traceability matrix.

### Overall Traceability Assessment

- **Forward Traceability**: 98% (Target: 100% for SIL 3-4)
- **Backward Traceability**: 98% (Target: 100% for SIL 3-4)
- **Safety Traceability**: 100% ✅ (MANDATORY SIL 3-4)
- **Status**: ⚠️ INCOMPLETE - 6 gaps identified (3 missing code, 3 orphan code)
- **Recommendation**: Resolve all gaps to achieve 100% traceability before phase gate
```

**Tool Commands**:
```bash
# Generate traceability matrix
python3 tools/traceability/trace_checker.py \
    --source src/ \
    --requirements docs/SRS.md \
    --design docs/SAS.md docs/SDS.md \
    --tests tests/ \
    --output docs/reports/evidence/DOC-IMPVER-2026-001/traceability_matrix.csv

# Check for gaps
python3 tools/traceability/trace_checker.py \
    --source src/ \
    --requirements docs/SRS.md \
    --design docs/SAS.md docs/SDS.md \
    --tests tests/ \
    --check-gaps \
    --output docs/reports/evidence/DOC-IMPVER-2026-001/traceability_gaps.txt
```

---

## Step 7: Calculate Metrics

### Compute Phase-Specific Quality Metrics

**Activity**: Calculate and document all phase-specific quality metrics.

**Metrics Section Format**:
```markdown
## 12. Metrics

### Code Quality Metrics (for code verification)

| Metric | Value | Target | Status |
|--------|-------|--------|--------|
| **Lines of Code (LOC)** | 15,234 | - | - |
| **Source Files** | 45 | - | - |
| **Functions** | 156 | - | - |
| **Average Function Length** | 98 LOC | ≤150 LOC | ✅ PASS |
| **Maximum Function Length** | 245 LOC | ≤300 LOC | ✅ PASS |

### Complexity Metrics (SIL 3-4)

| Metric | Value | Target (SIL 4) | Status |
|--------|-------|----------------|--------|
| **Average Cyclomatic Complexity (CCN)** | 6.2 | ≤10 | ✅ PASS |
| **Maximum Cyclomatic Complexity (CCN)** | 12 | ≤10 | ❌ FAIL |
| **Functions with CCN ≤ 10** | 153/156 (98%) | 100% | ❌ FAIL |
| **Functions with CCN > 10** | 3 | 0 | ❌ FAIL |

**Functions Exceeding Complexity Limit**:
- `src/protocol.c:parse_message()` - CCN = 12 (Defect DEF-IMP-015)
- `src/state_machine.c:process_state()` - CCN = 11 (Defect DEF-IMP-016)
- `src/config.c:validate_config()` - CCN = 11 (Defect DEF-IMP-017)

### MISRA C Compliance Metrics

| Rule Category | Rules | Passed | Failed | Compliance Rate |
|---------------|-------|--------|--------|-----------------|
| **Mandatory Rules** | 143 | 143 | 0 | 100% ✅ |
| **Required Rules** | 35 | 33 | 2 | 94% ⚠️ |
| **Advisory Rules** | 109 | 97 | 12 | 89% ✅ |
| **TOTAL** | 287 | 273 | 14 | 95% |

**SIL 3 Target**: Mandatory 100%, Required 100% (or deviations)  
**Status**: ⚠️ PASS WITH CONDITIONS (2 required rule violations, see Defects section)

### Static Analysis Metrics

| Tool | Total Issues | Critical | High | Medium | Low | Info |
|------|--------------|----------|------|--------|-----|------|
| **Cppcheck** | 23 | 0 | 3 | 8 | 12 | - |
| **PC-lint Plus** | 14 | 0 | 2 | 5 | 7 | - |
| **Clang Analyzer** | 8 | 1 | 2 | 3 | 2 | - |
| **TOTAL** | 45 | 1 | 7 | 16 | 21 | - |

**Critical Issues**: 1 (must be resolved before phase gate)  
**High Issues**: 7 (should be resolved or justified)

### Code Coverage Metrics (SIL 3-4 MANDATORY)

| Coverage Type | Achieved | Target (SIL 4) | Status |
|---------------|----------|----------------|--------|
| **Statement Coverage** | 98.7% | 100% | ⚠️ INCOMPLETE |
| **Branch Coverage** | 96.5% | 100% | ⚠️ INCOMPLETE |
| **Condition Coverage** | 94.2% | 100% | ⚠️ INCOMPLETE |
| **MC/DC Coverage** | 92.8% | 100% (HR) | ⚠️ INCOMPLETE |

**Uncovered Code**:
- Statement: 198/15,234 lines not executed (1.3%)
- Branch: 27/789 branches not taken (3.5%)
- Condition: 45/778 conditions not evaluated (5.8%)

**Recommendation**: Add test cases to achieve 100% coverage (MANDATORY SIL 3-4)

### Defect Metrics

| Metric | Value |
|--------|-------|
| **Total Defects Found** | 23 |
| **Critical Defects** | 0 |
| **Major Defects** | 3 |
| **Minor Defects** | 8 |
| **Observations** | 12 |
| **Defect Density** | 1.51 defects/KLOC |
| **Critical Defect Density** | 0.0 critical/KLOC |

**Industry Benchmark** (safety-critical software): <2 defects/KLOC  
**Status**: ✅ PASS (1.51 defects/KLOC is within acceptable range)

### Traceability Metrics

| Metric | Value | Target | Status |
|--------|-------|--------|--------|
| **Forward Traceability** | 98% | 100% | ⚠️ INCOMPLETE |
| **Backward Traceability** | 98% | 100% | ⚠️ INCOMPLETE |
| **Safety Requirements Traceability** | 100% | 100% | ✅ PASS |
| **Orphan Requirements** | 0 | 0 | ✅ PASS |
| **Orphan Design Items** | 3 | 0 | ❌ FAIL |
| **Orphan Code** | 3 | 0 | ❌ FAIL |

### Overall Metrics Assessment

**Strengths**:
- MISRA C Mandatory rules: 100% compliance ✅
- Defect density: Within industry benchmark ✅
- Average complexity: Well below target ✅
- Safety requirements traceability: 100% ✅

**Weaknesses**:
- Code coverage: Below 100% target (98.7% statement, 96.5% branch)
- Complexity: 3 functions exceed CCN target
- Traceability: 6 gaps (3 missing code, 3 orphan code)
- MISRA C Required rules: 2 violations

**Overall Assessment**: ⚠️ GOOD QUALITY with improvements needed before final approval
```

**Tool Commands**:
```bash
# Complexity metrics
lizard src/ -l c --CCN 10 --xml > lizard_report.xml
python3 tools/metrics/complexity_summary.py lizard_report.xml

# MISRA C compliance
python3 tools/metrics/misra_compliance.py pclint_report.txt

# Coverage metrics
python3 tools/metrics/coverage_summary.py coverage.info

# Defect metrics
python3 tools/metrics/defect_density.py docs/reports/DOC-IMPVER-2026-001.md

# Traceability metrics
python3 tools/traceability/trace_metrics.py traceability_matrix.csv
```

---

## Step 8: Write Recommendations and Conclusion

### Provide Actionable Recommendations and Overall Assessment

**Activity**: Based on verification results, provide recommendations and overall conclusion.

**Recommendations Section Format**:
```markdown
## 13. Recommendations

### Mandatory Actions (Must be resolved before phase gate)

1. **Resolve Critical Static Analysis Issue**
   - **Issue**: Uninitialized variable in `src/braking.c:234` (Defect DEF-IMP-005)
   - **Impact**: Safety hazard - undefined braking force
   - **Action**: Initialize variable to safe default value
   - **Responsible**: Implementer (IMP)
   - **Deadline**: Before phase gate review

2. **Achieve 100% Code Coverage**
   - **Issue**: Statement coverage 98.7%, Branch coverage 96.5%, Condition coverage 94.2% (Target: 100% for SIL 3-4)
   - **Impact**: Not compliant with EN 50128 Table A.21 (MANDATORY SIL 3-4)
   - **Action**: Add test cases to cover all uncovered code paths
   - **Responsible**: Tester (TST), Implementer (IMP)
   - **Deadline**: Before phase gate review

3. **Reduce Complexity of 3 Functions**
   - **Issue**: 3 functions exceed CCN ≤ 10 target (SIL 4)
   - **Functions**: `parse_message()` (CCN=12), `process_state()` (CCN=11), `validate_config()` (CCN=11)
   - **Impact**: Not compliant with EN 50128 Table A.19 complexity target
   - **Action**: Refactor functions to reduce complexity (extract sub-functions, simplify logic)
   - **Responsible**: Implementer (IMP), Designer (DES)
   - **Deadline**: Before phase gate review

4. **Resolve Traceability Gaps**
   - **Issue**: 6 traceability gaps (3 missing code, 3 orphan code) - 98% traceability (Target: 100% for SIL 3-4)
   - **Impact**: Not compliant with EN 50128 Table A.5 Technique 7 (MANDATORY SIL 3-4)
   - **Action**: Implement missing functions OR remove from design; Add @trace tags to orphan code OR remove unused code
   - **Responsible**: Implementer (IMP), Designer (DES)
   - **Deadline**: Before phase gate review

### Highly Recommended Actions (Should be resolved or justified)

1. **Resolve MISRA C Required Rule Violations**
   - **Issue**: 2 Required rule violations (Rule 2.2, Rule 8.13)
   - **Action**: Fix violations OR submit formal deviation requests per MISRA C:2012 Appendix B
   - **Responsible**: Implementer (IMP), Quality Assurance (QUA)

2. **Resolve High-Severity Static Analysis Issues**
   - **Issue**: 7 high-severity issues from Cppcheck, PC-lint, Clang
   - **Action**: Fix issues OR provide justification for false positives
   - **Responsible**: Implementer (IMP), Verifier (VER)

### Suggested Improvements (Consider for future phases)

1. **Improve MC/DC Coverage**
   - Current: 92.8%, Target: 100% (Highly Recommended SIL 3-4)
   - Consider using tools/mcdc/mcdc_analyzer.py for precise MC/DC measurement

2. **Reduce Average Function Length**
   - Current average: 98 LOC (acceptable)
   - Consider refactoring functions >150 LOC for better maintainability

3. **Document Complex Algorithms**
   - Functions with high complexity (even if within limits) should have detailed comments explaining logic

### Areas of Concern for Future Phases

1. **Integration Testing Preparation**
   - Ensure all module interfaces are well-documented for Phase 6 integration testing
   - Consider creating interface test specifications now to identify gaps early

2. **Target Hardware Performance**
   - Some functions approach complexity limits; monitor performance on target hardware in Phase 6

3. **Maintenance Considerations**
   - Document rationale for complex logic to aid future maintenance (Phase 8)
```

**Conclusion Section Format**:
```markdown
## 14. Conclusion

### Overall Assessment

Based on the comprehensive verification activities performed per the Software Verification Plan (SVP), the Software Source Code for the [Project Name] project (SIL 4) demonstrates **GOOD OVERALL QUALITY** but requires **MANDATORY IMPROVEMENTS** before progression to Phase 6 (Integration).

### Verification Summary

**Strengths**:
- ✅ MISRA C Mandatory Rules: 100% compliance (zero violations)
- ✅ Static Analysis: Zero critical issues from Cppcheck, PC-lint Plus (1 critical from Clang to be resolved)
- ✅ Defect Density: 1.51 defects/KLOC (within industry benchmark <2 defects/KLOC)
- ✅ Average Complexity: 6.2 CCN (well below SIL 4 target of ≤10)
- ✅ Safety Requirements Traceability: 100% (MANDATORY SIL 3-4)
- ✅ Defensive Programming: Comprehensive defensive patterns observed

**Weaknesses Requiring Resolution**:
- ⚠️ Code Coverage: 98.7% statement, 96.5% branch, 94.2% condition (Target: 100% MANDATORY SIL 3-4)
- ⚠️ Complexity: 3 functions exceed CCN ≤ 10 target (2% of functions)
- ⚠️ Traceability: 98% forward/backward (Target: 100% MANDATORY SIL 3-4)
- ⚠️ Static Analysis Critical Issue: 1 critical issue from Clang (uninitialized variable in safety function)

### Conditions for Approval

**The Software Source Code is CONDITIONALLY APPROVED for progression to Phase 6 (Integration), subject to the following MANDATORY conditions**:

1. ✅ **Critical Static Analysis Issue Resolved** (Defect DEF-IMP-005: Uninitialized variable in braking.c)
2. ✅ **100% Code Coverage Achieved** (Statement, Branch, Condition per EN 50128 Table A.21)
3. ✅ **Complexity Reduced** (3 functions refactored to CCN ≤ 10 per EN 50128 Table A.19)
4. ✅ **Traceability Gaps Resolved** (100% forward and backward traceability per EN 50128 Table A.5)
5. ✅ **Re-verification Performed** (VER re-executes verification activities and confirms all conditions met)

**All conditions must be met before COD authorizes phase gate transition.**

### Verifier Statement

Based on the verification activities performed, including:
- Static analysis (Cppcheck, PC-lint Plus, Clang Static Analyzer)
- Complexity analysis (Lizard)
- Coverage analysis (gcov/lcov)
- MISRA C:2012 compliance verification
- Traceability verification
- Manual code review

I, **Jane Smith (Verifier)**, **CONDITIONALLY APPROVE** the Software Source Code for the [Project Name] project, subject to resolution of the 4 mandatory conditions listed above.

**Independence Declaration**: I declare that I have been independent from the software development team throughout the verification process, per EN 50128 Section 5.1.2.10. I have had no involvement in requirements, design, or implementation activities for this software.

**Signature**: _Jane Smith_  
**Date**: 2026-03-15  
**Role**: Verifier (VER)

---

**Reviewed by**: _Mark Johnson_ (QUA) - 2026-03-15  
**Approved by**: _Alice Brown_ (VMGR) - 2026-03-15 (subject to conditions met)

---

**END OF REPORT**
```

---

## Step 9: QUA Template Compliance Review

### Submit Report to Quality Assurance for Template Review

**Activity**: QUA reviews verification report for template compliance (MANDATORY SIL 3-4, 1 pass only).

**QUA Review Process**:

1. **Receive Report** from VER
2. **Check Template Compliance**:
   - Document ID format: `DOC-[TYPE]VER-YYYY-NNN` ✅
   - Document Control table: Complete with version history ✅
   - Approvals table: All roles present (VER, QUA, VMGR for SIL 3-4) ✅
   - Independence Declaration: Present for SIL 3-4 ✅
   - All 12 main sections present ✅
   - All 4 appendices present ✅
   - Traceability section complete ✅
   - EN 50128 compliance section complete ✅
   - Metrics section complete ✅
3. **Decision**: Approve OR Reject with specific issues
4. **ONE PASS ONLY**: If rejected, VER fixes issues and resubmits ONCE. Second rejection escalates to VMGR.

**QUA Review Checklist**:
```markdown
# QA Template Compliance Review Checklist - Verification Report

**Report ID**: DOC-IMPVER-2026-001  
**Reviewer**: Mark Johnson (QUA)  
**Review Date**: 2026-03-14  
**Review Result**: APPROVE / REJECT

## Section 1: Document Header
- [ ] Document ID format correct: `DOC-[TYPE]VER-YYYY-NNN`
- [ ] Document Type specified
- [ ] Phase specified
- [ ] EN 50128 Reference provided
- [ ] Project Name, SIL, Date, Version filled

## Section 2: Document Control
- [ ] Version history table complete
- [ ] Configuration Item ID provided
- [ ] Baseline reference provided
- [ ] At least 3 versions (draft, review, final)

## Section 3: Approvals
- [ ] Prepared by (VER) - name, date, signature
- [ ] Reviewed by (QUA) - name, date, signature
- [ ] Approved by (VMGR for SIL 3-4, PM for SIL 0-2) - name, date, signature
- [ ] Independence Declaration present (SIL 3-4 MANDATORY)

## Section 4-14: Main Sections
- [ ] Executive Summary complete with overall result
- [ ] Introduction complete with purpose, scope, references
- [ ] Verification Methodology complete with techniques and tools
- [ ] Verification Criteria complete with pass/fail criteria
- [ ] Verification Results complete with evidence references
- [ ] Defects and Issues complete with severity and status
- [ ] Traceability Analysis complete with metrics
- [ ] EN 50128 Compliance complete with Table references
- [ ] Metrics complete with targets and actuals
- [ ] Recommendations complete with mandatory actions
- [ ] Conclusion complete with verifier statement

## Appendices
- [ ] Appendix A: Verification Checklist present
- [ ] Appendix B: Traceability Matrix present
- [ ] Appendix C: Defect Details present
- [ ] Appendix D: Tool Output Summaries present

## SIL-Specific Requirements (SIL 3-4)
- [ ] Independence Declaration present and signed
- [ ] VMGR approval signature present
- [ ] Traceability Analysis shows 100% target (or gaps documented)
- [ ] EN 50128 MANDATORY techniques documented (Static Analysis, Traceability)
- [ ] Coverage metrics show 100% target (or gaps documented)

## Overall Assessment
- [ ] No sections missing
- [ ] No required fields blank
- [ ] No obvious errors or inconsistencies
- [ ] Professional formatting and presentation

**QUA Decision**: APPROVE / REJECT

**Comments**:
[QUA comments on template compliance]

**Signature**: _Mark Johnson_ (QUA)  
**Date**: 2026-03-14
```

**QUA Approval**:
- If **APPROVED**: VER proceeds to Step 10 (VMGR Technical Review)
- If **REJECTED**: VER fixes issues and resubmits ONCE

---

## Step 10: VMGR Technical Review

### Submit Report to V&V Manager for Technical Review (SIL 3-4)

**Activity**: VMGR reviews verification report for technical adequacy (MANDATORY SIL 3-4).

**VMGR Review Process**:

1. **Receive Report** from VER (after QUA approval)
2. **Verify QUA Approval** present
3. **Technical Review**:
   - Verification methods adequate for phase and SIL?
   - Evidence quality and completeness sufficient?
   - Defects appropriately classified and addressed?
   - Traceability 100% or gaps justified?
   - Metrics meet SIL requirements or gaps documented?
   - Verifier independence confirmed?
4. **Decision**: Approve / Conditionally Approve / Reject
5. **Authority**: VMGR decision CANNOT be overridden by PM or COD

**VMGR Technical Review Checklist**:
```markdown
# V&V Manager Technical Review Checklist - Verification Report

**Report ID**: DOC-IMPVER-2026-001  
**Reviewer**: Alice Brown (VMGR)  
**Review Date**: 2026-03-15  
**Review Result**: APPROVE / CONDITIONALLY APPROVE / REJECT

## Verification Methodology Assessment
- [ ] Verification techniques appropriate for phase (Table A.5)
- [ ] Static analysis adequate (Table A.19 - Control/Data Flow for SIL 3-4)
- [ ] Coverage requirements defined (Table A.21 - 100% for SIL 3-4)
- [ ] Tools used are qualified or qualification status documented
- [ ] Tool versions documented

## Evidence Quality Assessment
- [ ] All verification results supported by evidence
- [ ] Tool output references provided
- [ ] Manual review checklists completed
- [ ] Evidence traceable to specific verification criteria
- [ ] Evidence adequate to support conclusions

## Defects and Issues Assessment
- [ ] Defect severity classification appropriate
- [ ] Critical defects correctly identified
- [ ] Critical defects resolution status clear
- [ ] Major defects adequately addressed or justified
- [ ] Defect metrics calculated correctly

## Traceability Assessment (MANDATORY SIL 3-4)
- [ ] Forward traceability verified (Requirements → Design → Code → Tests)
- [ ] Backward traceability verified (Tests → Requirements)
- [ ] Traceability metrics documented
- [ ] Target: 100% for SIL 3-4 (or gaps documented with resolution plan)
- [ ] Safety requirements traceability: 100% MANDATORY SIL 3-4

## Metrics Assessment
- [ ] Phase-specific metrics calculated
- [ ] Metrics compared to targets
- [ ] MISRA C compliance: Mandatory 100%, Required 100% (or deviations) for SIL 2+
- [ ] Complexity: Average and max within targets for SIL level
- [ ] Coverage: 100% statement/branch (SIL 2+), 100% condition (SIL 3-4)
- [ ] Metrics support overall assessment

## Independence Assessment (MANDATORY SIL 3-4)
- [ ] Independence Declaration signed by verifier
- [ ] Verifier is independent from development team (not REQ/DES/IMP/INT/TST)
- [ ] No conflicts of interest identified
- [ ] VER reports to VMGR (not PM)

## Overall Technical Assessment
- [ ] Verification activities adequate and complete
- [ ] Verification results support conclusions
- [ ] Defects appropriately identified and classified
- [ ] Recommendations are actionable and necessary
- [ ] Conclusion reflects verification results accurately
- [ ] Report demonstrates professional engineering judgment

**VMGR Decision**: APPROVE / CONDITIONALLY APPROVE / REJECT

**Conditions** (if Conditionally Approved):
1. [List mandatory conditions that must be met]

**Technical Comments**:
[VMGR technical assessment comments]

**VMGR Statement**:
Based on my technical review as V&V Manager, I [APPROVE / CONDITIONALLY APPROVE / REJECT] this verification report. [If conditional: The following conditions must be met before phase gate transition: ...]

**Signature**: _Alice Brown_ (VMGR)  
**Date**: 2026-03-15  
**Authority**: Independent V&V Manager (EN 50128 Section 5.1.2.10)
```

**VMGR Decisions**:
- **APPROVE**: Phase gate can proceed (COD enforces based on VMGR approval)
- **CONDITIONALLY APPROVE**: Phase gate blocked until conditions met, then VER re-verifies
- **REJECT**: Significant issues, development team must fix and VER must create new report

**For SIL 0-2**: Replace VMGR with PM for approval.

---

## Step 11: Finalize and Archive Report

### Complete Report and Add to Configuration Management

**Activity**: Finalize report, obtain all signatures, and archive in configuration management.

**Finalization Steps**:

1. **Update Version to 1.0** (final)
2. **Obtain All Signatures**:
   - VER signature (Prepared by)
   - QUA signature (Reviewed by)
   - VMGR signature (Approved by) for SIL 3-4
3. **Update Document Control Table** with final version entry
4. **Archive Report**:
   ```bash
   # Add to configuration management
   cp docs/reports/DOC-IMPVER-2026-001.md docs/reports/archive/
   
   # Add to git
   git add docs/reports/DOC-IMPVER-2026-001.md
   git add docs/reports/evidence/DOC-IMPVER-2026-001/
   git commit -m "Add Phase 5 Software Source Code Verification Report (APPROVED)"
   
   # Tag baseline
   git tag -a BASELINE-PHASE5-VER-001 -m "Phase 5 Verification Report Approved"
   ```
4. **Notify COD** that verification report approved (for gate check)
5. **Update LIFECYCLE_STATE.md**:
   ```yaml
   phase5:
     verification_report:
       status: approved
       document_id: DOC-IMPVER-2026-001
       approved_by: Alice Brown (VMGR)
       approved_date: 2026-03-15
   ```

**Archival Requirements (EN 50128 Section 6.6)**:
- Verification report archived with version control
- All evidence archived (tool reports, checklists, reviews)
- Report traceable to configuration baseline
- Report retrievable for audits and assessments

**EN 50128 Reference**: Section 6.6 "Software Configuration Management" - All verification reports are configuration items.

---

## 15. Phase-Specific Verification Requirements

### Requirements Verification (Phase 2)

**Key Activities**:
- Requirements completeness review (all system requirements allocated)
- Requirements quality review (unambiguous, testable, traceable)
- SIL assignment review
- Traceability verification (System Requirements → Software Requirements)
- Test specification review (all requirements have test cases)

**Critical Criteria**:
- All requirements use SHALL/SHOULD/MAY keywords
- All requirements have unique IDs
- All requirements have @trace tags to system requirements
- All safety requirements identified and traced to hazards
- Zero ambiguous or untestable requirements

**Tools**: Manual review, requirements traceability scripts

### Architecture and Design Verification (Phase 3)

**Key Activities**:
- Architecture completeness review (all requirements allocated to components)
- Design quality review (modularity, interfaces, defensive programming)
- Traceability verification (Requirements → Architecture → Design)
- Complexity estimation (design pseudo-code)
- Integration test specification review

**Critical Criteria**:
- Modular approach (MANDATORY SIL 2+)
- All components have defined interfaces
- Static allocation design (no malloc/free for SIL 2+)
- Defensive programming patterns present (HR SIL 3-4)
- Estimated complexity within limits

**Tools**: Manual review, design traceability scripts, pseudo-code complexity estimators

### Component Design Verification (Phase 4)

**Key Activities**:
- Component design completeness review (all functions specified)
- Detailed design quality review (pseudo-code, data structures, algorithms)
- Traceability verification (Architecture → Component Design)
- Unit test specification review
- Complexity estimation (function-level)

**Critical Criteria**:
- All functions have specifications (inputs, outputs, behavior, error handling)
- All functions have unit test specifications
- Estimated complexity within limits
- Error handling specified for all failure modes

**Tools**: Manual review, design traceability scripts

### Source Code Verification (Phase 5) - MOST CRITICAL

**Key Activities**:
- Static analysis (Cppcheck, PC-lint Plus, Clang)
- MISRA C:2012 compliance verification
- Complexity analysis (Lizard)
- Coverage analysis (gcov/lcov)
- Manual code review
- Traceability verification (Design → Code → Tests)

**Critical Criteria**:
- MISRA C Mandatory rules: Zero violations (SIL 2+)
- Static analysis critical issues: Zero unresolved
- Complexity: 100% functions CCN ≤ target
- Coverage: 100% statement/branch (SIL 2+), 100% condition (SIL 3-4)
- Traceability: 100% bidirectional

**Tools**: Cppcheck, PC-lint Plus, Clang Static Analyzer, Lizard, gcov/lcov, traceability scripts

### Integration Verification (Phase 6)

**Key Activities**:
- Integration test results verification
- Interface testing completeness review
- Performance testing results review (HR SIL 3-4)
- Integration defects analysis
- SW/HW integration results verification (on target hardware)

**Critical Criteria**:
- All integration test cases executed
- All interfaces tested
- Performance requirements met (if applicable)
- Timing requirements met on target hardware
- Memory and stack usage within bounds

**Tools**: Manual review, test result parsers, profiling tools

### Validation Verification (Phase 7)

**Key Activities**:
- System test results verification
- System requirements coverage review
- Safety scenario testing review
- Customer acceptance criteria verification
- Validation in target environment

**Critical Criteria**:
- All system test cases executed
- All system requirements covered
- All safety scenarios tested (100% SIL 3-4)
- Customer acceptance criteria met
- Independent validation performed (SIL 3-4)

**Tools**: Manual review, test result parsers, requirements traceability scripts

---

## 16. Evidence Collection Guidelines

### Evidence Types

**Tool Output Evidence**:
- XML reports: Cppcheck, Lizard
- Text reports: PC-lint Plus
- HTML reports: lcov coverage, Clang Static Analyzer
- JSON reports: Custom analysis scripts

**Manual Review Evidence**:
- Completed checklists (PDF or Markdown)
- Review meeting minutes
- Review comments and resolutions

**Traceability Evidence**:
- Traceability matrices (CSV, Excel, Markdown tables)
- Gap analysis reports

**Test Evidence** (for test-related verification):
- Test execution logs
- Test result summaries
- Test coverage reports

### Evidence Organization

```
docs/reports/evidence/DOC-[TYPE]VER-YYYY-NNN/
├── static-analysis/
│   ├── cppcheck_report.xml
│   ├── pclint_report.txt
│   ├── clang_analysis/
│   │   ├── index.html
│   │   └── [scan results]
│   └── summary.txt
├── complexity/
│   ├── lizard_report.xml
│   ├── lizard_report.html
│   └── complexity_summary.txt
├── coverage/
│   ├── coverage.info
│   ├── coverage_html/
│   │   ├── index.html
│   │   └── [coverage HTML]
│   └── coverage_summary.txt
├── traceability/
│   ├── traceability_matrix.csv
│   ├── traceability_gaps.txt
│   └── trace_metrics.json
├── checklists/
│   ├── requirements_review_checklist.pdf
│   ├── code_review_checklist.pdf
│   └── design_review_checklist.pdf
└── test-results/
    ├── unit_test_results.xml
    ├── integration_test_results.xml
    └── test_summary.txt
```

### Evidence Referencing in Report

**Good Example**:
```markdown
**Evidence**:
- Static Analysis Report: `docs/reports/evidence/DOC-IMPVER-2026-001/static-analysis/cppcheck_report.xml`
- MISRA C Compliance: `docs/reports/evidence/DOC-IMPVER-2026-001/static-analysis/pclint_report.txt`, lines 1-50 (summary)
- Coverage Report: `docs/reports/evidence/DOC-IMPVER-2026-001/coverage/coverage_html/index.html` (100% statement coverage achieved)
- Code Review Checklist: `docs/reports/evidence/DOC-IMPVER-2026-001/checklists/code_review_checklist.pdf`, page 3, item 15 (PASS)
```

**Bad Example**:
```markdown
**Evidence**:
- Static analysis was performed
- Coverage was measured
- Code was reviewed
```
(No specific references, not auditable)

### Evidence Retention (EN 50128)

**Retention Period**: For the lifecycle of the software system + regulatory period (typically 10-30 years for railway systems)

**Storage**: Configuration-managed repository with backup and retrieval procedures

---

## 17. Common Reporting Issues

### Issue 1: Insufficient Evidence

**Problem**: Verification results stated without evidence references.

**Example (Bad)**:
```markdown
**Result**: PASS
**Evidence**: Code review was performed.
```

**Solution (Good)**:
```markdown
**Result**: PASS
**Evidence**:
- Code Review Checklist: `docs/reports/evidence/DOC-IMPVER-2026-001/checklists/code_review_checklist.pdf`
- Review performed by: Jane Smith (VER), independent verifier
- Review date: 2026-03-13
- Review findings: 0 critical, 2 major, 5 minor issues (see Defects section)
```

### Issue 2: Vague Defect Descriptions

**Problem**: Defects described without specific location or impact.

**Example (Bad)**:
```markdown
**Defect**: Code has some issues.
**Impact**: Quality might be affected.
```

**Solution (Good)**:
```markdown
**Defect DEF-IMP-003**: Uninitialized variable `brake_pressure` in `braking.c:234`
**Impact**: Safety hazard - variable used in braking force calculation without initialization, could lead to undefined braking behavior (Hazard HAZ-001). Violates MISRA C:2012 Rule 9.1 (Mandatory).
**Recommendation**: Initialize to safe default (MAX_BRAKING_PRESSURE) on line 230.
```

### Issue 3: Missing Traceability Matrix

**Problem**: Traceability analysis discussed but matrix not provided in Appendix B.

**Solution**: Always include complete traceability matrix in Appendix B, even if large. Use CSV export from traceability tool.

### Issue 4: Metrics Without Targets

**Problem**: Metrics reported without comparison to targets.

**Example (Bad)**:
```markdown
**Cyclomatic Complexity**: Average 6.2, Max 12
```

**Solution (Good)**:
```markdown
**Cyclomatic Complexity**:
- Average: 6.2 (Target: ≤10 for SIL 4) ✅ PASS
- Maximum: 12 (Target: ≤10 for SIL 4) ❌ FAIL
- Functions exceeding target: 3/156 (2%)
```

### Issue 5: Unclear Conclusion

**Problem**: Conclusion does not provide clear approve/reject decision.

**Example (Bad)**:
```markdown
The code is generally good with some issues that should be addressed.
```

**Solution (Good)**:
```markdown
Based on the verification activities performed, I **CONDITIONALLY APPROVE** the Software Source Code, subject to resolution of the following MANDATORY conditions:
1. Critical defect DEF-IMP-005 resolved
2. 100% code coverage achieved
3. 3 functions refactored to CCN ≤ 10
4. Traceability gaps resolved (100% traceability)

All conditions must be met before phase gate transition.
```

### Issue 6: Independence Not Documented (SIL 3-4)

**Problem**: SIL 3-4 report missing Independence Declaration.

**Solution**: Always include Independence Declaration in Approvals section for SIL 3-4:
```markdown
**Independence Declaration** (SIL 3-4): "The undersigned verifier (Jane Smith) declares independence from the software development team per EN 50128 Section 5.1.2.10. The verifier has had no involvement in requirements, design, or implementation activities for this software."
```

### Issue 7: Tool Versions Not Documented

**Problem**: Tools mentioned without versions or qualification status.

**Example (Bad)**:
```markdown
Static analysis performed with Cppcheck.
```

**Solution (Good)**:
```markdown
**Static Analysis Tools**:
- Cppcheck 2.13.0 (Tool Confidence Level T1 - output inspection required)
- PC-lint Plus 2.1.0 (Tool Confidence Level T2 - qualified per Tool Qualification Report TQR-001)
- Clang Static Analyzer 18.1.0 (Tool Confidence Level T1 - output inspection required)
```

---

## Tool Integration Commands

### Full Verification Workflow (Code Verification Example)

```bash
#!/bin/bash
# verify_code.sh - Complete code verification workflow
# Usage: ./verify_code.sh <source_dir> <report_id>

SOURCE_DIR=$1
REPORT_ID=$2
EVIDENCE_DIR="docs/reports/evidence/${REPORT_ID}"

# Create evidence directory
mkdir -p ${EVIDENCE_DIR}/{static-analysis,complexity,coverage,traceability,checklists}

echo "=== Phase 1: Static Analysis ==="

# Cppcheck
echo "Running Cppcheck..."
cppcheck --enable=all --xml --xml-version=2 ${SOURCE_DIR} \
    2> ${EVIDENCE_DIR}/static-analysis/cppcheck_report.xml

# PC-lint Plus (MISRA C)
echo "Running PC-lint Plus (MISRA C:2012)..."
pclp64 --template=misra ${SOURCE_DIR}/*.c \
    > ${EVIDENCE_DIR}/static-analysis/pclint_report.txt

# Clang Static Analyzer
echo "Running Clang Static Analyzer..."
scan-build -o ${EVIDENCE_DIR}/static-analysis/clang_analysis make

echo "=== Phase 2: Complexity Analysis ==="

# Lizard
echo "Running Lizard (CCN ≤ 10 for SIL 4)..."
lizard ${SOURCE_DIR} -l c --CCN 10 --xml \
    > ${EVIDENCE_DIR}/complexity/lizard_report.xml
lizard ${SOURCE_DIR} -l c --CCN 10 --html \
    > ${EVIDENCE_DIR}/complexity/lizard_report.html

echo "=== Phase 3: Coverage Analysis ==="

# Run tests with coverage
echo "Running unit tests with coverage..."
make clean
make test COVERAGE=1

# Generate coverage reports
echo "Generating coverage reports..."
gcov -b -c ${SOURCE_DIR}/*.c
lcov --capture --directory . \
    --output-file ${EVIDENCE_DIR}/coverage/coverage.info
genhtml ${EVIDENCE_DIR}/coverage/coverage.info \
    --output-directory ${EVIDENCE_DIR}/coverage/coverage_html

# MC/DC analysis (if SIL 3-4)
echo "Running MC/DC analysis..."
python3 tools/mcdc/mcdc_analyzer.py \
    --source ${SOURCE_DIR} \
    --gcov ${EVIDENCE_DIR}/coverage/coverage.info \
    --output ${EVIDENCE_DIR}/coverage/mcdc_report.json

echo "=== Phase 4: Traceability Verification ==="

# Traceability checking
echo "Checking traceability..."
python3 tools/traceability/trace_checker.py \
    --source ${SOURCE_DIR} \
    --requirements docs/SRS.md \
    --design docs/SAS.md docs/SDS.md \
    --tests tests/ \
    --output ${EVIDENCE_DIR}/traceability/traceability_matrix.csv

# Check for gaps
python3 tools/traceability/trace_checker.py \
    --source ${SOURCE_DIR} \
    --requirements docs/SRS.md \
    --design docs/SAS.md docs/SDS.md \
    --tests tests/ \
    --check-gaps \
    --output ${EVIDENCE_DIR}/traceability/traceability_gaps.txt

echo "=== Phase 5: Generate Summaries ==="

# Generate summaries for report
python3 tools/metrics/complexity_summary.py \
    ${EVIDENCE_DIR}/complexity/lizard_report.xml \
    > ${EVIDENCE_DIR}/complexity/complexity_summary.txt

python3 tools/metrics/coverage_summary.py \
    ${EVIDENCE_DIR}/coverage/coverage.info \
    > ${EVIDENCE_DIR}/coverage/coverage_summary.txt

python3 tools/metrics/misra_compliance.py \
    ${EVIDENCE_DIR}/static-analysis/pclint_report.txt \
    > ${EVIDENCE_DIR}/static-analysis/misra_summary.txt

python3 tools/traceability/trace_metrics.py \
    ${EVIDENCE_DIR}/traceability/traceability_matrix.csv \
    > ${EVIDENCE_DIR}/traceability/trace_metrics.json

echo "=== Verification Complete ==="
echo "Evidence collected in: ${EVIDENCE_DIR}"
echo "Next step: Fill verification report with results"
```

**Usage**:
```bash
./verify_code.sh src/ DOC-IMPVER-2026-001
```

---

## Summary

This workflow covers the complete process for creating all 11 EN 50128 verification reports across the software lifecycle. Each report follows the same structure but focuses on phase-specific verification activities and criteria.

**Key Principles**:
1. **Evidence-Based**: All results supported by objective evidence (tool reports, checklists)
2. **Traceable**: All verification activities traceable to SVP and phase criteria
3. **Independent**: Independent verifier for SIL 3-4 (VER → VMGR, not PM)
4. **Auditable**: Complete evidence archive for future audits
5. **Actionable**: Clear recommendations and approval/rejection decisions

**For VER Agent**: Use this workflow to systematically create verification reports with appropriate rigor for the project SIL level.

**For VMGR Agent**: Use the review checklists to assess verification report quality and make approval decisions.

**For QUA Agent**: Use the template compliance checklist to verify report structure before VMGR review.

---

**END OF WORKFLOW**
