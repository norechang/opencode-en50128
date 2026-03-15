# Phase 3: Tool Implementation and Testing

**Status**: In Progress  
**Start Date**: 2026-03-15  
**Duration**: 2-3 weeks (estimated)  
**Prerequisites**: ✅ Phase 2 Complete (all 13 skills enhanced)

---

## ⚠️ SCOPE CHANGE (2026-03-15)

**Decision**: Train Door Control sample project **DEPRECATED** and moved to **Phase 4 (Future Work)**

**Rationale**: Focus Phase 3 on core tool implementation and skill workflow testing WITHOUT large sample project. Sample projects will be created AFTER transformation is complete.

**New Phase 3 Scope**:
1. ✅ Implement 10 missing tools (~1,550 lines)
2. ✅ Test all 13 skill workflows end-to-end (using opencode_session_debugger if needed)
3. ❌ ~~Create Train Door Control sample project~~ → **MOVED TO PHASE 4**

---

## Executive Summary

**Phase 3 Goal**: Implement missing tools and test all skill workflows end-to-end to verify tool integration points work correctly.

**Phase 2 Achievements**:
- ✅ 13 of 13 skills complete (100%)
- ✅ 3,611 pages of comprehensive workflows (~144,285 lines)
- ✅ 2 working tools integrated (traceability_manager.py, workflow_manager.py via workspace.py)
- ✅ 30+ Python automation scripts documented
- ✅ Complete EN 50128 coverage (all sections, tables, lifecycle phases)
- ✅ Zero placeholder tools in workflows - all tool references are working implementations

**Phase 3 Challenges**:
- 10 documented tools are NOT YET IMPLEMENTED (e.g., validate_test_doc_template.py)
- Workflows have not been tested end-to-end
- Tool integration points need verification
- Skill invocation evidence tracking may require opencode_session_debugger (OPENCODE_DEBUG_ENABLED=true)

---

## Phase 3 Objectives

### 1. Tool Implementation (Priority: HIGH)

Implement all missing tools documented in Phase 2 workflows:

| Tool | Purpose | Skill | Lines (est.) | Priority | Status |
|------|---------|-------|--------------|----------|--------|
| `tools/scripts/validate_test_doc_template.py` | Test doc template validation | Documentation | ~200 | **CRITICAL** | ⏳ TODO |
| `tools/tool-validation/run-all-validations.sh` | Automated T2 tool validation | Tools | ~150 | **HIGH** | ⏳ TODO |
| `tools/tool-validation/check-tool-versions.sh` | Tool version checker | Tools | ~100 | **MEDIUM** | ⏳ TODO |
| `tools/scripts/validate_srs_template.py` | SRS template validation | Documentation | ~200 | **MEDIUM** | ⏳ TODO |
| `tools/scripts/validate_sas_sds_template.py` | SAS/SDS template validation | Documentation | ~250 | **MEDIUM** | ⏳ TODO |
| `tools/scripts/generate_test_report.py` | Automated test report generation | Documentation | ~200 | **MEDIUM** | ⏳ TODO |
| `tools/scripts/parse_coverage_report.py` | Coverage report parsing | Documentation | ~150 | **MEDIUM** | ⏳ TODO |
| `.github/workflows/tool-validation.yml` | CI/CD tool validation | Tools | ~50 | **LOW** | ⏳ TODO |
| `.github/workflows/tool-version-check.yml` | CI/CD tool version check | Tools | ~50 | **LOW** | ⏳ TODO |

**Total Estimated Effort**: ~1,550 lines of Python/Bash code

**NOTE**: `tools/mcdc/mcdc_analyzer.py` **ALREADY EXISTS** (11K lines) - removed from implementation list

**Tool Implementation Strategy**:
1. **Week 1**: Implement CRITICAL and HIGH priority tools (validate_test_doc_template.py, run-all-validations.sh, check-tool-versions.sh)
2. **Week 2**: Implement MEDIUM priority tools (template validation scripts, test report generation)
3. **Week 3**: Implement LOW priority tools (CI/CD workflows)

### 2. Skill Workflow Testing (Priority: CRITICAL)

Test all 13 skill workflows end-to-end to verify tool integration:

**Testing Strategy**:
- Load each skill using `skill` tool
- Execute primary workflows documented in skill
- Verify all tool invocations work correctly
- Use `opencode_session_debugger` if needed (set OPENCODE_DEBUG_ENABLED=true)
- Document any issues or missing integrations

**Skills to Test** (13 total):
1. en50128-requirements - Requirements elicitation, SIL assignment, traceability
2. en50128-design - Architecture design, defensive programming
3. en50128-implementation - C coding, MISRA C compliance
4. en50128-verification - Static analysis, verification reports
5. en50128-testing - Unit/integration testing, coverage
6. en50128-integration - Progressive integration, HW/SW integration
7. en50128-validation - System validation, acceptance testing
8. en50128-quality - SQAP, code reviews, quality gates
9. en50128-safety - Hazard analysis, FMEA, FTA
10. en50128-lifecycle-coordination - V-Model orchestration, phase gates
11. en50128-configuration - Version control, change control
12. en50128-documentation - Document workflows, automation
13. en50128-tools - Tool qualification, validation

### 3. ~~Sample Project Creation~~ (DEPRECATED - MOVED TO PHASE 4)

**⚠️ STATUS**: This objective has been **DEPRECATED** and moved to **Phase 4 (Future Work)**.

**Rationale**: Focus Phase 3 on core tool implementation and skill workflow testing. Sample projects will be created AFTER architecture transformation is complete to avoid premature scope expansion.

**Original Plan** (for reference):

~~**Project**: **Train Door Control System (SIL 3)**~~

~~**Scope**:
- Safety-critical software for railway train door control
- SIL 3 (per EN 50128, EN 50126)
- C programming language (MISRA C:2012 compliant)
- ~2,000 lines of production code
- ~3,000 lines of test code
- Complete V-Model lifecycle documentation~~

~~**System Requirements** (10-15 requirements):
1. System shall open doors only when train is stopped (hazard: door opens while moving)
2. System shall close doors before train departure (hazard: train moves with doors open)
3. System shall detect obstacles in door path (hazard: door closes on passenger)
4. System shall provide emergency door release (safety requirement)
5. System shall monitor door sensors for faults (safety requirement)
6. System shall enter safe state on critical failure (safety requirement)
7. System shall respond to door open command within 500ms (performance)
8. System shall respond to door close command within 500ms (performance)
9. System shall log all door events for audit (traceability)
10. System shall support manual override (operational)~~

~~**Architecture** (5-7 modules):
1. `door_controller.c` - Main door control state machine
2. `sensor_interface.c` - Door sensor reading and fault detection
3. `motor_control.c` - Door motor control with position feedback
4. `safety_monitor.c` - Safety checks and fault handling
5. `event_logger.c` - Event logging for audit trail
6. `system_config.c` - Configuration and initialization
7. `diagnostics.c` - Self-test and diagnostics~~

~~**Lifecycle Phases to Test**:
- **Phase 0**: Initialization (COD plan)
- **Phase 1**: Planning (SQAP, SCMP, SVP, SVaP)
- **Phase 2**: Requirements (SRS, Hazard Log, Traceability)
- **Phase 3**: Design (SAS, SDS)
- **Phase 4**: Implementation (Source code, Unit tests)
- **Phase 5**: Integration (Integration tests)
- **Phase 6**: Validation (System tests, Validation Report)
- **Phase 7**: Assessment (Assessment Report - simulated)
- **Phase 8**: Deployment (Release Package)~~

~~**Deliverables** (per EN 50128 Annex C):
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
- Tool Validation Reports (Cppcheck, Clang, gcov, lcov, Lizard)~~

~~**Quality Metrics** (SIL 3 targets):
- Statement Coverage: 100% (MANDATORY)
- Branch Coverage: 100% (MANDATORY)
- Condition Coverage: 100% (MANDATORY)
- MC/DC Coverage: 100% (Highly Recommended)
- Cyclomatic Complexity: ≤10 per function (MANDATORY)
- MISRA C Compliance: Zero mandatory violations (MANDATORY)
- Traceability: 100% coverage (MANDATORY)~~

**(Full project details preserved for Phase 4 reference - see original phase3-plan.md in git history)**

---

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
| ~~**Sample Project Documentation**~~ | ~~Complete Train Door Control System docs~~ | ~~200~~ | **DEPRECATED** |
| **Tool Implementation Reports** | Documentation for each implemented tool | ~50 | ⏳ TODO |
| **Tool Integration Test Report** | Results of tool integration verification | ~30 | ⏳ TODO |
| **Skill Workflow Test Report** | Results of end-to-end skill testing | ~50 | ⏳ TODO |
| **Phase 3 Completion Report** | Summary of Phase 3 achievements | ~30 | ⏳ TODO |
| **Phase 3 Lessons Learned** | Issues discovered and resolved | ~20 | ⏳ TODO |

**Total Estimated Documentation**: ~200 pages (reduced from ~400 due to sample project removal)

---

## Phase 3 Schedule (UPDATED 2026-03-15)

### Week 1: Critical and High Priority Tool Implementation (40 hours)

**Days 1-2 (16 hours)**: Tool Implementation - CRITICAL/HIGH
- Implement `tools/scripts/validate_test_doc_template.py` (~200 lines)
- Implement `tools/tool-validation/run-all-validations.sh` (~150 lines)
- Test both tools with sample data
- Document usage in tool README

**Days 3-4 (16 hours)**: Tool Implementation - MEDIUM Priority (Part 1)
- Implement `tools/tool-validation/check-tool-versions.sh` (~100 lines)
- Implement `tools/scripts/validate_srs_template.py` (~200 lines)
- Test automation scripts
- Document in TOOLS.md

**Day 5 (8 hours)**: Tool Implementation - MEDIUM Priority (Part 2)
- Implement `tools/scripts/validate_sas_sds_template.py` (~250 lines)
- Test template validation tools
- Document usage patterns

**Deliverables**: 5 tools implemented (~900 lines)

### Week 2: Remaining Tools + Skill Workflow Testing (Part 1) (40 hours)

**Days 1-2 (16 hours)**: Tool Implementation - MEDIUM Priority (Part 3)
- Implement `tools/scripts/generate_test_report.py` (~200 lines)
- Implement `tools/scripts/parse_coverage_report.py` (~150 lines)
- Test report generation tools

**Days 3-4 (16 hours)**: Skill Workflow Testing - Core Development
- Test en50128-requirements skill workflow
- Test en50128-design skill workflow
- Test en50128-implementation skill workflow
- Test en50128-verification skill workflow
- Document any issues found

**Day 5 (8 hours)**: Skill Workflow Testing - Testing & Integration
- Test en50128-testing skill workflow
- Test en50128-integration skill workflow
- Test en50128-validation skill workflow
- Document issues and tool integration points

**Deliverables**: 2 tools implemented (~350 lines), 7 skills tested

### Week 3: Skill Workflow Testing (Part 2) + Documentation (40 hours)

**Days 1-2 (16 hours)**: Skill Workflow Testing - Management & Support
- Test en50128-quality skill workflow
- Test en50128-safety skill workflow
- Test en50128-lifecycle-coordination skill workflow
- Test en50128-configuration skill workflow
- Document issues and integration points

**Days 3-4 (16 hours)**: Skill Workflow Testing - Documentation & Tools
- Test en50128-documentation skill workflow
- Test en50128-tools skill workflow
- Fix any critical issues found
- Verify all tool integrations work

**Day 5 (8 hours)**: LOW Priority Tools (Optional)
- Implement `.github/workflows/tool-validation.yml` (~50 lines)
- Implement `.github/workflows/tool-version-check.yml` (~50 lines)
- Test CI/CD workflows

**Deliverables**: All 13 skills tested, 2 CI/CD workflows implemented (optional), test reports created

### Week 4 (Optional): Issue Resolution and Finalization (20 hours)

**Days 1-2 (16 hours)**: Bug Fixes and Enhancements
- Fix any issues discovered during skill testing
- Enhance tool integration based on findings
- Update documentation

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

## Success Criteria (UPDATED 2026-03-15)

Phase 3 will be considered successful if:

### 1. Tool Implementation (MANDATORY)
- ✅ All 9 documented tools implemented and tested
- ✅ validate_test_doc_template.py validates all test document templates
- ✅ Tool automation scripts work correctly (run-all-validations.sh, check-tool-versions.sh)
- ✅ Template validation tools (SRS, SAS/SDS) work correctly
- ✅ Report generation tools work correctly

### 2. ~~Sample Project~~ (DEPRECATED - MOVED TO PHASE 4)
- ~~✅ Train Door Control System SIL 3 project complete~~
- ~~✅ All EN 50128 Annex C deliverables created~~
- **STATUS**: Removed from Phase 3 scope

### 3. Skill Workflow Testing (MANDATORY)
- ✅ All 13 skill workflows tested end-to-end
- ✅ All tool integration points verified (workspace.py, traceability_manager.py, workflow_manager.py)
- ✅ Document any issues or missing integrations
- ✅ Verify skill loading and workflow execution

### 4. Documentation (MANDATORY)
- ✅ Phase 3 Completion Report created
- ✅ Tool Implementation Reports created
- ✅ Skill Workflow Test Report created
- ✅ SUMMARY.md updated with Phase 3 status

### 5. Quality (MANDATORY)
- ✅ All tool tests pass
- ✅ All tools properly documented with usage examples
- ✅ All skill workflows execute without errors
- ✅ Tool integration verified

### 6. Optional Enhancements (NICE TO HAVE)
- ⏳ CI/CD workflows created and tested
- ⏳ Branch merged to main
- ⏳ Git tag v2.0.0-phase3-complete created

---

## Risk Management (UPDATED 2026-03-15)

### Identified Risks

| Risk | Probability | Impact | Mitigation |
|------|-------------|--------|------------|
| **Tool integration issues** | MEDIUM | HIGH | Test each tool individually before integration, create test harnesses, use opencode_session_debugger |
| **Skill workflow testing time-consuming** | HIGH | MEDIUM | Prioritize critical workflows (requirements, design, implementation, verification), defer less critical |
| **Skills don't auto-load or execute properly** | MEDIUM | HIGH | Use opencode_session_debugger (OPENCODE_DEBUG_ENABLED=true) to trace skill invocation |
| **Documentation takes longer than expected** | MEDIUM | LOW | Use templates extensively, focus on completeness over polish |
| **Phase 3 schedule too aggressive** | MEDIUM | MEDIUM | Extend to 4 weeks if needed, prioritize MANDATORY success criteria |
| **Missing tool functionality discovered** | MEDIUM | MEDIUM | Document gaps, implement in Phase 4 if non-critical |

### Risk Response Plan

**If tool integration fails**:
1. Debug each tool individually
2. Use verbose logging for troubleshooting
3. Use opencode_session_debugger to trace execution
4. Document workarounds in Phase 3 report

**If skill testing time-consuming**:
1. Prioritize 7 critical skills: Requirements, Design, Implementation, Verification, Testing, Lifecycle, Quality
2. Defer less critical skills to Phase 4
3. Document limitations in Phase 3 report

**If skills don't load properly**:
1. Enable OPENCODE_DEBUG_ENABLED=true
2. Use opencode_session_debugger to trace skill invocation
3. Verify skill SKILL.md syntax
4. Check for skill loading errors in debug output

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

## Deliverables Summary (UPDATED 2026-03-15)

### Code
- 9 Python tools/scripts: ~1,550 lines
- 2 CI/CD workflows (optional): ~100 lines
- ~~Sample project code~~: ~~3,500 lines~~ **DEPRECATED**
- **Total**: ~1,650 lines of code

### Documentation
- ~~Sample project documentation~~: ~~200 pages~~ **DEPRECATED**
- Phase 3 reports: ~200 pages (test plan, tool reports, skill test report, completion report, lessons learned)
- **Total**: ~200 pages of documentation

### Artifacts
- ~~Complete Train Door Control System SIL 3 project~~ **DEPRECATED**
- 9 working tools with documentation and test harnesses
- Skill workflow test reports (13 skills tested)
- Tool integration verification reports
- Phase 3 completion report with lessons learned

---

## Post-Phase 3 Actions (UPDATED 2026-03-15)

### Immediate Actions (After Phase 3 Completion)
1. Review Phase 3 Completion Report
2. Identify any gaps or issues discovered during skill testing
3. Prioritize fixes or enhancements for Phase 4
4. Update project roadmap based on lessons learned
5. **Decision point**: Merge to main or continue with Phase 4 work on branch

### Phase 4 Planning (Future)
**Phase 4 Goals** (tentative):
- **Create sample projects** (Train Door Control System SIL 3, Simple Calculator SIL 0, Signal Controller SIL 4)
- Implement any remaining tools or enhancements
- Create user documentation and tutorials
- Conduct user acceptance testing
- Prepare for production release

### Long-Term Actions
1. Merge `architecture-transforming` to `main`
2. Create Git tag `v2.0.0-transformation-complete`
3. Publish Phase 3 Completion Report
4. Update project documentation
5. Consider conference paper on EN 50128 skill-based automation

---

## Appendix A: Tool Implementation Details (UPDATED 2026-03-15)

**NOTE**: `tools/mcdc/mcdc_analyzer.py` **ALREADY EXISTS** (331 lines, implemented 2024-02-24). This appendix now focuses on the 9 tools to be implemented.

### A.1: validate_test_doc_template.py

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
- ~~Test with Train Door Control System test documents~~ **Use synthetic test documents**

### A.2: run-all-validations.sh

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
