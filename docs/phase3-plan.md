# Phase 3: Tool Implementation and Testing

**Status**: Planning  
**Start Date**: 2026-03-14 (estimated)  
**Duration**: 2-3 weeks (estimated)  
**Prerequisites**: ✅ Phase 2 Complete (all 13 skills enhanced)

---

## Executive Summary

**Phase 3 Goal**: Implement missing tools, test all workflows with a real EN 50128 SIL 3 project, verify all tool integration points work correctly, and create a comprehensive sample project demonstrating the complete V-Model lifecycle.

**Phase 2 Achievements**:
- ✅ 13 of 13 skills complete (100%)
- ✅ 3,611 pages of comprehensive workflows (~144,285 lines)
- ✅ 2 working tools integrated (traceability_manager.py, workflow_manager.py via workspace.py)
- ✅ 30+ Python automation scripts documented
- ✅ Complete EN 50128 coverage (all sections, tables, lifecycle phases)
- ✅ Zero placeholder tools in workflows - all tool references are working implementations

**Phase 3 Challenges**:
- Some documented tools are NOT YET IMPLEMENTED (e.g., mcdc_analyzer.py, validate_test_doc_template.py)
- Workflows have not been tested end-to-end with real EN 50128 project
- Tool integration points need verification
- Sample project needed to demonstrate complete lifecycle

---

## Phase 3 Objectives

### 1. Tool Implementation (Priority: HIGH)

Implement all missing tools documented in Phase 2 workflows:

| Tool | Purpose | Skill | Lines (est.) | Priority | Status |
|------|---------|-------|--------------|----------|--------|
| `tools/mcdc/mcdc_analyzer.py` | MC/DC coverage analysis (SIL 3-4) | Testing | ~200 | **CRITICAL** | ⏳ TODO |
| `tools/scripts/validate_test_doc_template.py` | Test doc template validation | Documentation | ~200 | **HIGH** | ⏳ TODO |
| `tools/tool-validation/run-all-validations.sh` | Automated T2 tool validation | Tools | ~150 | **HIGH** | ⏳ TODO |
| `tools/tool-validation/check-tool-versions.sh` | Tool version checker | Tools | ~100 | **MEDIUM** | ⏳ TODO |
| `tools/scripts/validate_srs_template.py` | SRS template validation | Documentation | ~200 | **MEDIUM** | ⏳ TODO |
| `tools/scripts/validate_sas_sds_template.py` | SAS/SDS template validation | Documentation | ~250 | **MEDIUM** | ⏳ TODO |
| `tools/scripts/generate_test_report.py` | Automated test report generation | Documentation | ~200 | **MEDIUM** | ⏳ TODO |
| `tools/scripts/parse_coverage_report.py` | Coverage report parsing | Documentation | ~150 | **MEDIUM** | ⏳ TODO |
| `.github/workflows/tool-validation.yml` | CI/CD tool validation | Tools | ~50 | **LOW** | ⏳ TODO |
| `.github/workflows/tool-version-check.yml` | CI/CD tool version check | Tools | ~50 | **LOW** | ⏳ TODO |

**Total Estimated Effort**: ~1,550 lines of Python/Bash code

**Tool Implementation Strategy**:
1. **Week 1**: Implement CRITICAL and HIGH priority tools (mcdc_analyzer.py, validate_test_doc_template.py, run-all-validations.sh, check-tool-versions.sh)
2. **Week 2**: Implement MEDIUM priority tools (template validation scripts, test report generation)
3. **Week 3**: Implement LOW priority tools (CI/CD workflows)

### 2. Sample Project Creation (Priority: CRITICAL)

Create a complete EN 50128 SIL 3 sample project to test all workflows:

**Project**: **Train Door Control System (SIL 3)**

**Scope**:
- Safety-critical software for railway train door control
- SIL 3 (per EN 50128, EN 50126)
- C programming language (MISRA C:2012 compliant)
- ~2,000 lines of production code
- ~3,000 lines of test code
- Complete V-Model lifecycle documentation

**System Requirements** (10-15 requirements):
1. System shall open doors only when train is stopped (hazard: door opens while moving)
2. System shall close doors before train departure (hazard: train moves with doors open)
3. System shall detect obstacles in door path (hazard: door closes on passenger)
4. System shall provide emergency door release (safety requirement)
5. System shall monitor door sensors for faults (safety requirement)
6. System shall enter safe state on critical failure (safety requirement)
7. System shall respond to door open command within 500ms (performance)
8. System shall respond to door close command within 500ms (performance)
9. System shall log all door events for audit (traceability)
10. System shall support manual override (operational)

**Architecture** (5-7 modules):
1. `door_controller.c` - Main door control state machine
2. `sensor_interface.c` - Door sensor reading and fault detection
3. `motor_control.c` - Door motor control with position feedback
4. `safety_monitor.c` - Safety checks and fault handling
5. `event_logger.c` - Event logging for audit trail
6. `system_config.c` - Configuration and initialization
7. `diagnostics.c` - Self-test and diagnostics

**Lifecycle Phases to Test**:
- **Phase 0**: Initialization (COD plan)
- **Phase 1**: Planning (SQAP, SCMP, SVP, SVaP)
- **Phase 2**: Requirements (SRS, Hazard Log, Traceability)
- **Phase 3**: Design (SAS, SDS)
- **Phase 4**: Implementation (Source code, Unit tests)
- **Phase 5**: Integration (Integration tests)
- **Phase 6**: Validation (System tests, Validation Report)
- **Phase 7**: Assessment (Assessment Report - simulated)
- **Phase 8**: Deployment (Release Package)

**Deliverables** (per EN 50128 Annex C):
- Software Requirements Specification (SRS)
- Software Architecture Specification (SAS)
- Software Design Specification (SDS)
- Source Code (~2,000 lines C, MISRA C compliant)
- Unit Test Code (~1,500 lines)
- Integration Test Code (~1,000 lines)
- System Test Code (~500 lines)
- Component Test Specification/Report
- Integration Test Specification/Report
- Overall Test Specification/Report
- Verification Report (11 reports per verification skill)
- Validation Report
- Software Quality Assurance Plan (SQAP)
- Software Configuration Management Plan (SCMP)
- Software Verification Plan (SVP)
- Software Validation Plan (SVaP)
- Hazard Log
- Traceability Matrix (System Req → SW Req → Arch → Design → Code → Tests → Validation)
- Tool Qualification Reports (GCC, Unity)
- Tool Validation Reports (Cppcheck, Clang, gcov, lcov, Lizard)

**Quality Metrics** (SIL 3 targets):
- Statement Coverage: 100% (MANDATORY)
- Branch Coverage: 100% (MANDATORY)
- Condition Coverage: 100% (MANDATORY)
- MC/DC Coverage: 100% (Highly Recommended)
- Cyclomatic Complexity: ≤10 per function (MANDATORY)
- MISRA C Compliance: Zero mandatory violations (MANDATORY)
- Traceability: 100% coverage (MANDATORY)

### 3. End-to-End Testing (Priority: CRITICAL)

Test each workflow with the sample project:

| Skill | Workflows to Test | Test Scenarios | Expected Outcomes |
|-------|-------------------|----------------|-------------------|
| **Requirements** | Requirements Elicitation, SIL Assignment, Traceability | Create SRS with 15 SW requirements, assign SIL 3, link to 10 system requirements | SRS complete, traceability 100%, workspace.py trace validates |
| **Design** | Architecture Design, Detailed Design | Create SAS with 7 modules, SDS with detailed design, link to SRS | SAS/SDS complete, complexity ≤10, traceability updated |
| **Implementation** | C Coding, Unit Testing, MISRA C | Implement 7 modules (~2,000 lines), write unit tests (~1,500 lines), check MISRA C | Code compiles, unit tests pass, zero MISRA mandatory violations |
| **Testing** | Unit Testing, Integration Testing, Coverage | Execute all tests, measure coverage (statement/branch/condition/MC/DC) | All tests pass, 100% coverage achieved |
| **Verification** | Static Analysis, Complexity, Coverage | Run Cppcheck, Clang, Lizard, gcov/lcov, generate Verification Report | All checks pass, Verification Report complete |
| **Integration** | Component Integration, HW/SW Integration | Integrate 7 modules, test interfaces, test with HIL (simulated) | Integration successful, interface tests pass |
| **Validation** | System Validation, Acceptance | Execute system tests, operational scenarios, acceptance criteria | All system tests pass, customer acceptance (simulated) |
| **Safety** | Hazard Analysis, FMEA, FTA | Create Hazard Log (5 hazards), FMEA (6 failure modes), FTA (2 fault trees) | Safety analysis complete, all hazards mitigated |
| **Quality** | Document Review, Code Review, Audits | Review all documents (template compliance), code review, pre-release audit | All reviews pass, zero NCRs remaining |
| **Lifecycle** | Phase Gates, V-Model, Traceability, Iteration | Execute all 8 phase gates, maintain traceability, test one iteration | All gates pass, traceability 100%, iteration successful |
| **Configuration** | Version Control, Change Control, Baselines | Git workflow, 1 Change Request, baseline at Gate 4 | All CIs under CM, CR processed, baseline established |
| **Documentation** | SRS, SAS/SDS, Test/Verification Docs | Create all mandatory documents per Annex C | All documents complete, template compliant |
| **Tools** | Tool Qualification, Tool Validation | Qualify GCC (T3), validate Cppcheck/Clang/gcov (T2) | All tools qualified/validated, reports complete |

**Testing Approach**:
1. **Sequential Phase Execution**: Execute phases 0-8 in order, enforcing phase gates
2. **Tool Integration Verification**: Verify workspace.py trace and workspace.py wf work correctly at each phase
3. **Traceability Validation**: Verify end-to-end traceability at each phase (System Req → Validation Results)
4. **Quality Gate Enforcement**: Verify QUA reviews and approvals work correctly
5. **Iteration Testing**: Introduce one requirements defect in Phase 6, test iteration workflow (return to Phase 2, update SRS, re-verify, re-validate)
6. **Automation Verification**: Verify all Python automation scripts work correctly
7. **Deliverable Completeness**: Verify all EN 50128 Annex C deliverables are created and complete

### 4. Tool Integration Verification (Priority: HIGH)

Verify all tool integration points work correctly:

| Integration Point | Description | Test Method | Status |
|-------------------|-------------|-------------|--------|
| **workspace.py trace** | Traceability management | Create 100+ traceability links, validate, generate reports | ⏳ TODO |
| **workspace.py wf** | Document workflow | Submit 20+ documents, approve/reject, check status | ⏳ TODO |
| **GCC compilation** | C compilation with SIL 3 flags | Compile all 7 modules, check warnings, check errors | ⏳ TODO |
| **Cppcheck** | Static analysis | Run Cppcheck on all code, verify XML output, check issues | ⏳ TODO |
| **Clang** | Static analysis | Run Clang scan-build, verify HTML output, check issues | ⏳ TODO |
| **Lizard** | Complexity analysis | Run Lizard on all code, verify CCN ≤10, generate report | ⏳ TODO |
| **gcov/lcov** | Coverage measurement | Execute all tests, measure coverage, verify 100% achieved | ⏳ TODO |
| **mcdc_analyzer.py** | MC/DC analysis | Analyze conditions, calculate MC/DC coverage, verify 100% | ⏳ TODO |
| **Valgrind** | Memory checking | Run integration tests under Valgrind, verify no leaks | ⏳ TODO |
| **Unity** | Unit testing | Execute all unit tests, verify test results, generate report | ⏳ TODO |
| **Git** | Version control | Commit all changes, tag baselines, verify audit trail | ⏳ TODO |
| **Template validators** | Document compliance | Validate all documents against templates, verify compliance | ⏳ TODO |

### 5. Documentation and Reporting (Priority: MEDIUM)

Create comprehensive Phase 3 documentation:

| Document | Purpose | Pages (est.) | Status |
|----------|---------|--------------|--------|
| **Phase 3 Test Plan** | Overall testing strategy and approach | ~20 | ⏳ TODO |
| **Sample Project Documentation** | Complete Train Door Control System docs | ~200 | ⏳ TODO |
| **Tool Implementation Reports** | Documentation for each implemented tool | ~50 | ⏳ TODO |
| **Integration Test Report** | Results of tool integration verification | ~30 | ⏳ TODO |
| **End-to-End Test Report** | Results of workflow testing | ~50 | ⏳ TODO |
| **Phase 3 Completion Report** | Summary of Phase 3 achievements | ~30 | ⏳ TODO |
| **Phase 3 Lessons Learned** | Issues discovered and resolved | ~20 | ⏳ TODO |

**Total Estimated Documentation**: ~400 pages

---

## Phase 3 Schedule

### Week 1: Critical Tool Implementation + Project Setup (40 hours)

**Days 1-2 (16 hours)**: Tool Implementation - CRITICAL
- Implement `tools/mcdc/mcdc_analyzer.py` (~200 lines)
- Implement `tools/scripts/validate_test_doc_template.py` (~200 lines)
- Test both tools with sample data
- Document usage in tool README

**Days 3-4 (16 hours)**: Tool Implementation - HIGH
- Implement `tools/tool-validation/run-all-validations.sh` (~150 lines)
- Implement `tools/tool-validation/check-tool-versions.sh` (~100 lines)
- Test automation scripts
- Document in TOOLS.md

**Day 5 (8 hours)**: Sample Project Setup
- Create project structure (`sample-projects/train-door-control-sil3/`)
- Initialize Git repository
- Create initial LIFECYCLE_STATE.md
- Execute Phase 0 (COD plan)

**Deliverables**: 4 tools implemented (~650 lines), sample project structure created

### Week 2: Sample Project Development + Testing (40 hours)

**Days 1-2 (16 hours)**: Planning and Requirements (Phases 1-2)
- Execute Phase 1: Create SQAP, SCMP, SVP, SVaP
- Execute Phase 2: Create SRS (15 requirements), Hazard Log (5 hazards), Traceability
- Verify workspace.py trace works correctly
- Pass Gate 2

**Days 3-4 (16 hours)**: Design and Implementation (Phases 3-4)
- Execute Phase 3: Create SAS (7 modules), SDS (detailed design)
- Execute Phase 4: Implement code (~2,000 lines C), unit tests (~1,500 lines)
- Verify GCC compilation, Cppcheck/Clang analysis, MISRA C compliance
- Pass Gates 3 and 4

**Day 5 (8 hours)**: Integration and Testing (Phase 5)
- Execute Phase 5: Integration tests (~1,000 lines)
- Measure coverage (gcov/lcov)
- Run mcdc_analyzer.py
- Pass Gate 5

**Deliverables**: Phases 1-5 complete, Train Door Control System code (~3,500 lines) implemented

### Week 3: Validation, Quality, and Completion (40 hours)

**Days 1-2 (16 hours)**: Validation and Verification (Phase 6)
- Execute Phase 6: System tests (~500 lines), Validation Report
- Create 11 Verification Reports
- Verify QUA document reviews work correctly
- Pass Gate 6

**Days 3 (8 hours)**: Assessment and Deployment (Phases 7-8)
- Execute Phase 7: Assessment Report (simulated independent assessment)
- Execute Phase 8: Release Package preparation
- Pass Gates 7 and 8
- Complete all EN 50128 Annex C deliverables

**Day 4 (8 hours)**: Iteration Testing
- Introduce requirements defect in Validation
- Execute iteration workflow (return to Phase 2)
- Update SRS, re-verify, re-validate
- Verify iteration workflow works correctly

**Day 5 (8 hours)**: Documentation and Reporting
- Create Phase 3 Completion Report
- Create Integration Test Report
- Create End-to-End Test Report
- Update SUMMARY.md with Phase 3 status

**Deliverables**: Complete Train Door Control System (all phases 0-8), Phase 3 reports

### Week 4 (Optional): Tool Enhancement and Merge (20 hours)

**Days 1-2 (16 hours)**: Remaining Tool Implementation
- Implement MEDIUM priority tools (template validators, test report generators)
- Implement LOW priority tools (CI/CD workflows)
- Test all tools

**Day 3 (4 hours)**: Branch Merge Preparation
- Review all changes in `architecture-transforming` branch
- Create pull request description
- Prepare merge commit message

**Days 4-5 (Optional)**: Merge and Finalization
- Merge `architecture-transforming` to `main`
- Create Git tag: `v2.0.0-phase3-complete`
- Update main branch README

**Deliverables**: All tools implemented, branch merged to main

---

## Success Criteria

Phase 3 will be considered successful if:

### 1. Tool Implementation (MANDATORY)
- ✅ All CRITICAL and HIGH priority tools implemented and tested
- ✅ mcdc_analyzer.py provides accurate MC/DC coverage (validated against manual analysis)
- ✅ validate_test_doc_template.py validates all test document templates
- ✅ Tool automation scripts work correctly (run-all-validations.sh, check-tool-versions.sh)

### 2. Sample Project (MANDATORY)
- ✅ Train Door Control System SIL 3 project complete (all 8 phases executed)
- ✅ All EN 50128 Annex C deliverables created and complete
- ✅ Code quality: 100% coverage, CCN ≤10, zero MISRA mandatory violations
- ✅ Traceability: 100% end-to-end coverage (System Req → Validation Results)
- ✅ All phase gates passed (COD gate-check successful)

### 3. Workflow Testing (MANDATORY)
- ✅ All 13 skill workflows tested end-to-end with sample project
- ✅ All tool integration points verified (workspace.py trace/wf, GCC, Cppcheck, etc.)
- ✅ Iteration workflow tested (requirements defect introduced, iteration successful)
- ✅ QUA review workflows tested (document review, code review, audits)

### 4. Documentation (MANDATORY)
- ✅ Phase 3 Completion Report created
- ✅ Sample Project Documentation complete (~200 pages)
- ✅ Integration Test Report and End-to-End Test Report created
- ✅ SUMMARY.md updated with Phase 3 status

### 5. Quality (MANDATORY)
- ✅ All tests pass (unit, integration, system)
- ✅ All static analysis checks pass (Cppcheck, Clang)
- ✅ All coverage targets met (100% statement/branch/condition, SIL 3)
- ✅ All documents template-compliant (validated by scripts)

### 6. Optional Enhancements (NICE TO HAVE)
- ⏳ All MEDIUM and LOW priority tools implemented
- ⏳ CI/CD workflows created and tested
- ⏳ Branch merged to main
- ⏳ Git tag v2.0.0-phase3-complete created

---

## Risk Management

### Identified Risks

| Risk | Probability | Impact | Mitigation |
|------|-------------|--------|------------|
| **mcdc_analyzer.py implementation complex** | HIGH | HIGH | Start with simple MC/DC algorithm, validate against manual analysis, use existing gcov branch coverage data |
| **Sample project too large** | MEDIUM | MEDIUM | Reduce scope to 5 modules if needed, focus on quality over quantity |
| **Tool integration issues** | MEDIUM | HIGH | Test each tool individually before integration, create test harnesses |
| **Workflow testing time-consuming** | HIGH | MEDIUM | Prioritize critical workflows (requirements, design, implementation, verification), defer less critical |
| **Documentation takes longer than expected** | MEDIUM | LOW | Use templates extensively, automate where possible, focus on completeness over polish |
| **Phase 3 schedule too aggressive** | MEDIUM | MEDIUM | Extend to 4 weeks if needed, prioritize MANDATORY success criteria |

### Risk Response Plan

**If mcdc_analyzer.py too complex**:
1. Use simplified MC/DC algorithm (basic condition coverage + branch coverage)
2. Document limitations clearly
3. Validate with 2-3 simple test cases manually

**If sample project scope too large**:
1. Reduce to 5 modules (~1,500 lines code)
2. Simplify requirements (10 instead of 15)
3. Focus on one iteration scenario

**If tool integration fails**:
1. Debug each tool individually
2. Use verbose logging for troubleshooting
3. Document workarounds in Phase 3 report

**If testing time-consuming**:
1. Prioritize 6 critical skills: Requirements, Design, Implementation, Verification, Testing, Lifecycle
2. Defer less critical skills to Phase 4
3. Document limitations in Phase 3 report

---

## Dependencies

### External Dependencies
- ✅ GCC compiler (already installed)
- ✅ Cppcheck (already installed)
- ✅ Clang (already installed)
- ✅ gcov/lcov (already installed)
- ✅ Lizard (already installed)
- ✅ Unity test framework (already available)
- ✅ Git (already installed)
- ✅ Python 3.8+ (already installed)

### Internal Dependencies
- ✅ Phase 2 complete (all 13 skills)
- ✅ workspace.py working (traceability_manager.py, workflow_manager.py)
- ✅ TOOLS.md complete (tool catalog)
- ✅ EN 50128 standard document (std/EN50128-2011.md)

---

## Deliverables Summary

### Code
- 4 Python tools (CRITICAL/HIGH): ~650 lines
- 6 Python tools (MEDIUM): ~1,000 lines
- 2 CI/CD workflows (LOW): ~100 lines
- Sample project code: ~3,500 lines (production + tests)
- **Total**: ~5,250 lines of code

### Documentation
- Sample project documentation: ~200 pages (all EN 50128 Annex C deliverables)
- Phase 3 reports: ~130 pages (test plan, tool reports, integration report, end-to-end report, completion report, lessons learned)
- **Total**: ~330 pages of documentation

### Artifacts
- Complete Train Door Control System SIL 3 project (all phases 0-8)
- Tool Qualification Reports (2 reports: GCC, Unity)
- Tool Validation Reports (5 reports: Cppcheck, Clang, gcov, lcov, Lizard)
- Traceability Matrix (100+ links)
- Coverage Reports (statement/branch/condition/MC/DC, 100%)
- Verification Reports (11 reports per verification skill)
- Validation Report
- All EN 50128 Annex C deliverables

---

## Post-Phase 3 Actions

### Immediate Actions (Week 4)
1. Review Phase 3 Completion Report with stakeholders
2. Identify any gaps or issues discovered during testing
3. Prioritize fixes or enhancements for Phase 4
4. Update project roadmap based on lessons learned

### Phase 4 Planning (Future)
**Phase 4 Goals** (tentative):
- Implement remaining MEDIUM/LOW priority tools
- Create additional sample projects (SIL 0, SIL 2, SIL 4)
- Enhance tool automation (CI/CD integration)
- Create user documentation and tutorials
- Conduct user acceptance testing with external users
- Prepare for production release

### Long-Term Actions
1. Merge `architecture-transforming` to `main`
2. Create Git tag `v2.0.0-phase3-complete`
3. Publish Phase 3 Completion Report
4. Update project website with sample project
5. Prepare conference paper or technical report on EN 50128 automation

---

## Appendix A: Tool Implementation Details

### A.1: mcdc_analyzer.py

**Purpose**: Analyze C code for Modified Condition/Decision Coverage (MC/DC) compliance per EN 50128 Table A.21 (MANDATORY SIL 3-4).

**Algorithm**:
1. Parse source code to identify decision points (if/while/for with compound conditions)
2. Identify atomic conditions within each decision (A, B, C, etc.)
3. For each atomic condition, identify test cases where:
   - Condition independently affects decision outcome
   - Other conditions remain constant
4. Calculate MC/DC coverage: (Conditions with MC/DC coverage) / (Total conditions) * 100%
5. Generate report: Uncovered conditions, required test cases

**Input**: 
- Source code files (*.c, *.h)
- gcov coverage data (*.gcov, *.gcda)
- Test case metadata (optional)

**Output**:
- MC/DC coverage report (Markdown, HTML)
- Uncovered conditions list
- Recommended test cases

**Implementation Notes**:
- Use `pycparser` for C parsing
- Use gcov branch coverage data as starting point
- Implement simplified MC/DC algorithm (may not be 100% accurate for complex conditions)
- Document limitations clearly

**Testing**:
- Validate with 3 simple test cases (2 conditions, 3 conditions, 4 conditions)
- Compare results with manual analysis
- Test with Train Door Control System code

### A.2: validate_test_doc_template.py

**Purpose**: Validate test documentation (Component/Integration/Overall Test Specifications and Reports) against EN 50128 templates.

**Validation Checks**:
1. Document ID format: `DOC-TST-[TYPE]-[NNN]`
2. Document Control table: 8 required fields
3. Approvals table: SIL-specific approvers (TST, VER for all SIL; +VAL for SIL 3-4)
4. Test case structure: ID, Requirement ID, Description, Inputs, Expected Outputs, Pass/Fail
5. Traceability section: Links to requirements, design, code
6. Coverage data: Statement/Branch/Condition coverage percentages

**Input**:
- Test document (Markdown format)
- SIL level (0-4)

**Output**:
- Validation report (PASS/FAIL)
- List of issues (missing sections, incorrect format, etc.)
- Compliance percentage

**Implementation Notes**:
- Parse Markdown with regex or Markdown parser
- Check for required sections in order
- Validate table formats (Document Control, Approvals, Test Cases)
- Generate detailed error messages for failures

**Testing**:
- Test with valid test document (should pass)
- Test with invalid documents (missing sections, wrong format, etc.)
- Test with Train Door Control System test documents

### A.3: run-all-validations.sh

**Purpose**: Automate T2 tool validation for all tools (Cppcheck, Clang, gcov, lcov, Lizard).

**Workflow**:
1. Check tool installation and versions
2. For each T2 tool:
   - Run tool validation test suite
   - Generate validation report
   - Compare results with expected output
3. Generate summary report (all tools)

**Input**:
- Tool validation test suite (test cases for each tool)
- Expected validation results

**Output**:
- Individual tool validation reports (Markdown)
- Summary validation report (all tools)

**Implementation Notes**:
- Use Bash script for orchestration
- Call individual tool validation scripts
- Generate Markdown reports
- Return exit code 0 (all pass) or 1 (any fail)

**Testing**:
- Run with all tools installed
- Run with one tool missing (should report error)
- Run with invalid tool version (should report warning)

### A.4: check-tool-versions.sh

**Purpose**: Check installed tool versions against EN 50128 requirements.

**Checks**:
1. Tool installation (which <tool>)
2. Tool version (<tool> --version)
3. Version comparison against minimum required version
4. Tool qualification status (T1/T2/T3)

**Input**:
- Tool requirements (TOOLS.md or tool_requirements.yaml)

**Output**:
- Tool version report (Markdown)
- Warnings for outdated tools
- Errors for missing tools

**Implementation Notes**:
- Parse TOOLS.md for tool requirements
- Use version comparison (compare-versions or custom)
- Generate Markdown report with status icons (✅/⚠️/❌)

**Testing**:
- Run with all tools installed (should pass)
- Run with outdated tool (should warn)
- Run with missing tool (should error)

---

## Appendix B: Sample Project Structure

```
sample-projects/
└── train-door-control-sil3/
    ├── README.md                           # Project overview
    ├── LIFECYCLE_STATE.md                  # Current lifecycle state
    ├── docs/                               # All EN 50128 deliverables
    │   ├── planning/
    │   │   ├── DOC-PM-SQAP-001.md         # Software Quality Assurance Plan
    │   │   ├── DOC-CM-SCMP-001.md         # Software Configuration Management Plan
    │   │   ├── DOC-VER-SVP-001.md         # Software Verification Plan
    │   │   └── DOC-VAL-SVAP-001.md        # Software Validation Plan
    │   ├── requirements/
    │   │   ├── DOC-REQ-SRS-001.md         # Software Requirements Specification
    │   │   ├── DOC-SAF-HAZLOG-001.md      # Hazard Log
    │   │   └── traceability.csv            # Traceability Matrix (System → SW Req)
    │   ├── design/
    │   │   ├── DOC-DES-SAS-001.md         # Software Architecture Specification
    │   │   ├── DOC-DES-SDS-001.md         # Software Design Specification
    │   │   └── DOC-DES-SIS-001.md         # Software Interface Specifications
    │   ├── implementation/
    │   │   └── (source code and unit tests - see src/, tests/)
    │   ├── testing/
    │   │   ├── DOC-TST-CTSP-001.md        # Component Test Specification
    │   │   ├── DOC-TST-CTSR-001.md        # Component Test Report
    │   │   ├── DOC-TST-ITSP-001.md        # Integration Test Specification
    │   │   ├── DOC-TST-ITSR-001.md        # Integration Test Report
    │   │   ├── DOC-TST-OTSP-001.md        # Overall Test Specification
    │   │   └── DOC-TST-OTSR-001.md        # Overall Test Report
    │   ├── verification/
    │   │   ├── DOC-VER-SCA-001.md         # Software Configuration Audit Report
    │   │   ├── DOC-VER-SCS-001.md         # Software Code Standards Compliance Report
    │   │   ├── DOC-VER-STA-001.md         # Static Analysis Report
    │   │   ├── DOC-VER-DYN-001.md         # Dynamic Analysis Report
    │   │   ├── DOC-VER-COV-001.md         # Coverage Analysis Report
    │   │   ├── DOC-VER-COMP-001.md        # Complexity Analysis Report
    │   │   ├── DOC-VER-TRACE-001.md       # Traceability Verification Report
    │   │   ├── DOC-VER-REV-001.md         # Review Report
    │   │   ├── DOC-VER-QA-001.md          # Quality Assurance Report
    │   │   ├── DOC-VER-SAFE-001.md        # Safety Analysis Report
    │   │   ├── DOC-VER-TOOL-001.md        # Tool Qualification/Validation Report
    │   │   └── DOC-VER-SVR-001.md         # Software Verification Report (consolidated)
    │   ├── validation/
    │   │   └── DOC-VAL-SVALR-001.md       # Software Validation Report
    │   ├── safety/
    │   │   ├── DOC-SAF-FMEA-001.md        # FMEA Report
    │   │   ├── DOC-SAF-FTA-001.md         # FTA Report
    │   │   └── DOC-SAF-SC-001.md          # Safety Case
    │   ├── tools/
    │   │   ├── DOC-TOOL-TQR-GCC-001.md    # Tool Qualification Report - GCC (T3)
    │   │   ├── DOC-TOOL-TQR-UNITY-001.md  # Tool Qualification Report - Unity (T3)
    │   │   ├── DOC-TOOL-TVR-CPPCHECK-001.md # Tool Validation Report - Cppcheck (T2)
    │   │   ├── DOC-TOOL-TVR-CLANG-001.md  # Tool Validation Report - Clang (T2)
    │   │   ├── DOC-TOOL-TVR-GCOV-001.md   # Tool Validation Report - gcov (T2)
    │   │   ├── DOC-TOOL-TVR-LCOV-001.md   # Tool Validation Report - lcov (T2)
    │   │   └── DOC-TOOL-TVR-LIZARD-001.md # Tool Validation Report - Lizard (T2)
    │   └── release/
    │       ├── DOC-PM-RN-001.md           # Release Note
    │       └── DOC-PM-DP-001.md           # Deployment Package
    ├── src/                                # Source code (~2,000 lines)
    │   ├── door_controller.c               # Main door control state machine
    │   ├── door_controller.h
    │   ├── sensor_interface.c              # Sensor reading and fault detection
    │   ├── sensor_interface.h
    │   ├── motor_control.c                 # Motor control with position feedback
    │   ├── motor_control.h
    │   ├── safety_monitor.c                # Safety checks and fault handling
    │   ├── safety_monitor.h
    │   ├── event_logger.c                  # Event logging for audit
    │   ├── event_logger.h
    │   ├── system_config.c                 # Configuration and initialization
    │   ├── system_config.h
    │   ├── diagnostics.c                   # Self-test and diagnostics
    │   ├── diagnostics.h
    │   └── main.c                          # Main entry point
    ├── tests/                              # Test code (~3,000 lines)
    │   ├── unit/                           # Unit tests (~1,500 lines)
    │   │   ├── test_door_controller.c
    │   │   ├── test_sensor_interface.c
    │   │   ├── test_motor_control.c
    │   │   ├── test_safety_monitor.c
    │   │   ├── test_event_logger.c
    │   │   ├── test_system_config.c
    │   │   └── test_diagnostics.c
    │   ├── integration/                    # Integration tests (~1,000 lines)
    │   │   ├── test_door_open_sequence.c
    │   │   ├── test_door_close_sequence.c
    │   │   ├── test_obstacle_detection.c
    │   │   ├── test_emergency_release.c
    │   │   └── test_fault_handling.c
    │   └── system/                         # System tests (~500 lines)
    │       ├── test_normal_operation.c
    │       ├── test_fault_injection.c
    │       ├── test_performance.c
    │       └── test_safety_scenarios.c
    ├── coverage/                           # Coverage reports
    │   ├── index.html                      # lcov HTML report
    │   ├── coverage.xml                    # gcov XML report
    │   └── mcdc_report.md                  # MC/DC coverage report
    ├── analysis/                           # Static analysis reports
    │   ├── cppcheck_report.xml
    │   ├── clang_report.html
    │   └── lizard_report.txt
    ├── Makefile                            # Build system
    ├── .gitignore
    └── .git/                               # Git repository
```

**Total Files**: ~80 files (40 documents, 20 source files, 20 test files)

---

## Appendix C: Phase 3 Metrics

### Code Metrics
| Metric | Target | Actual | Status |
|--------|--------|--------|--------|
| Production Code Lines | ~2,000 | TBD | ⏳ TODO |
| Test Code Lines | ~3,000 | TBD | ⏳ TODO |
| Tool Implementation Lines | ~1,550 | TBD | ⏳ TODO |
| Total Code Lines | ~6,550 | TBD | ⏳ TODO |

### Coverage Metrics (SIL 3)
| Metric | Target | Actual | Status |
|--------|--------|--------|--------|
| Statement Coverage | 100% | TBD | ⏳ TODO |
| Branch Coverage | 100% | TBD | ⏳ TODO |
| Condition Coverage | 100% | TBD | ⏳ TODO |
| MC/DC Coverage | 100% | TBD | ⏳ TODO |

### Complexity Metrics (SIL 3)
| Metric | Target | Actual | Status |
|--------|--------|--------|--------|
| Maximum Cyclomatic Complexity | ≤10 | TBD | ⏳ TODO |
| Average Cyclomatic Complexity | ≤5 | TBD | ⏳ TODO |
| Functions > CCN 10 | 0 | TBD | ⏳ TODO |

### MISRA C Metrics (SIL 3)
| Metric | Target | Actual | Status |
|--------|--------|--------|--------|
| Mandatory Violations | 0 | TBD | ⏳ TODO |
| Required Violations | ≤5 | TBD | ⏳ TODO |
| Advisory Violations | Acceptable | TBD | ⏳ TODO |

### Traceability Metrics (SIL 3)
| Metric | Target | Actual | Status |
|--------|--------|--------|--------|
| System Req → SW Req | 100% | TBD | ⏳ TODO |
| SW Req → Arch | 100% | TBD | ⏳ TODO |
| Arch → Design | 100% | TBD | ⏳ TODO |
| Design → Code | 100% | TBD | ⏳ TODO |
| Code → Unit Tests | 100% | TBD | ⏳ TODO |
| SW Req → System Tests | 100% | TBD | ⏳ TODO |
| System Tests → Validation | 100% | TBD | ⏳ TODO |

### Deliverable Metrics
| Metric | Target | Actual | Status |
|--------|--------|--------|--------|
| Documents Created | ~40 | TBD | ⏳ TODO |
| Document Pages | ~200 | TBD | ⏳ TODO |
| Tools Implemented | 10 | TBD | ⏳ TODO |
| Phase 3 Report Pages | ~130 | TBD | ⏳ TODO |

---

## Appendix D: References

1. **EN 50128:2011** - Railway applications - Communication, signalling and processing systems - Software for railway control and protection systems
2. **EN 50126-1:2017** - Railway applications - The specification and demonstration of Reliability, Availability, Maintainability and Safety (RAMS) - Part 1: Generic RAMS process
3. **EN 50126-2:2017** - Railway applications - The specification and demonstration of RAMS - Part 2: Systems approach to safety
4. **MISRA C:2012** - Guidelines for the use of the C language in critical systems
5. **Phase 2 Completion Reports** - All 13 skill enhancement reports (docs/phase2-*-skill-enhancement.md)
6. **TOOLS.md** - EN 50128 Tool Catalog (904 lines)
7. **LIFECYCLE.md** - EN 50128 V-Model Lifecycle
8. **AGENTS.md** - EN 50128 Role-Based Agents

---

**END OF PHASE 3 PLAN**
