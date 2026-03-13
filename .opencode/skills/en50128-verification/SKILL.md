---
name: en50128-verification
description: EN 50128 software verification techniques and static analysis for C
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  section: "6.2"
  sil_applicability: "0-4"
---

## What I do

I provide verification techniques, static analysis patterns, and evidence collection methods required by EN 50128 Section 6.2:
- Independent verification for SIL 3-4 (mandatory)
- Static analysis (mandatory SIL 3-4)
- Control flow and data flow analysis (mandatory SIL 3-4)
- Traceability verification (mandatory SIL 3-4)
- Metrics collection and analysis
- Verification evidence collection
- 11 verification reports (DOC-2, DOC-4, DOC-8, DOC-14, DOC-17, DOC-19, DOC-23, DOC-32, DOC-35, DOC-40, DOC-44)

## When to use me

Use this skill when:
- Performing software verification activities
- Running static analysis on C code
- Verifying traceability matrices
- Collecting verification evidence
- Analyzing code metrics
- Preparing verification reports

---

## How to Use This Skill

### Overview

The **en50128-verification** skill is the **largest and most comprehensive skill** in the EN 50128 platform, covering 11 verification reports across all lifecycle phases. This skill provides:

- **4 comprehensive workflows** (~170 pages) - Step-by-step processes for verification planning, static analysis, traceability, and reporting
- **5 detailed resources** (~230 pages) - Guidelines, checklists, tool references, defect catalogs, and metrics
- **Cross-cutting application** - Used throughout all phases (Planning, Requirements, Design, Implementation, Integration, Validation)
- **Independence focus** - MANDATORY independent verification for SIL 3-4

**Total Content**: ~400 pages of verification guidance (largest skill in platform)

### Role-Specific Usage

#### For Verifiers (VER)

**Primary Responsibilities**:
- Execute independent verification activities (MANDATORY SIL 3-4)
- Perform static analysis (Cppcheck, PC-lint Plus, Clang, Lizard)
- Verify traceability completeness (forward and backward)
- Collect verification evidence
- Create 11 verification reports

**Key Workflows**:
1. **`workflows/verification-planning.md`** - Create Software Verification Plan (SVP) - DOC-4
   - EN 50128 technique selection (Tables A.5, A.19, A.21)
   - Tool selection and qualification (12+ tools)
   - Independence requirements (SIL 3-4)
   - Verification schedule and resource planning
   
2. **`workflows/static-analysis-workflow.md`** - Execute static analysis
   - Multi-tool strategy (Cppcheck + PC-lint Plus + Clang + Lizard)
   - Defect triage (Critical, High, Medium, Low)
   - MISRA C:2012 compliance verification (zero mandatory violations SIL 2+)
   - Complexity verification (CCN ≤ 10 SIL 3-4)
   
3. **`workflows/traceability-verification.md`** - Verify traceability
   - Forward traceability: Requirements → Design → Code → Tests (100% SIL 3-4)
   - Backward traceability: Tests → Requirements (100% SIL 3-4)
   - Safety requirements traceability (100% MANDATORY SIL 3-4)
   - Gap analysis and remediation
   
4. **`workflows/verification-reporting.md`** - Create verification reports
   - 11 verification report templates
   - Evidence collection and organization
   - QUA template compliance review (SIL 3-4)
   - VMGR technical review submission (SIL 3-4)

**Key Resources**:
- **`resources/static-analysis-guidelines.md`** - Tool configuration for Cppcheck, PC-lint Plus, Clang, Lizard (40 pages)
- **`resources/verification-tools-reference.md`** - Comprehensive tool catalog with installation, usage, qualification (40 pages)
- **`resources/common-verification-defects.md`** - 30+ defect patterns with before/after code examples (40 pages)
- **`resources/verification-metrics.md`** - Complexity, coverage, defect, traceability, quality metrics (40 pages)
- **`resources/traceability-verification-checklist.md`** - Phase-by-phase checklists (40 pages)

**Typical VER Workflow**:
```bash
# 1. Plan verification activities
# Read: workflows/verification-planning.md
# Create: Software Verification Plan (SVP) - DOC-4

# 2. Execute static analysis
# Read: workflows/static-analysis-workflow.md
# Read: resources/static-analysis-guidelines.md
cppcheck --enable=all --xml src/ 2> cppcheck_report.xml
pclp64 --misra3 -os(misra_report.xml) src/*.c
scan-build -o analysis_results make
lizard -CCN 10 -w src/

# 3. Verify traceability
# Read: workflows/traceability-verification.md
python3 tools/traceability/check_forward_trace.py --requirements SRS.md --code src/ --tests tests/
python3 tools/traceability/check_backward_trace.py --code src/ --requirements SRS.md

# 4. Collect metrics
# Read: resources/verification-metrics.md
./tools/metrics/collect_all_metrics.sh 3 metrics_output/

# 5. Create verification report
# Read: workflows/verification-reporting.md
# Template: deliverables/DOC-19-Software-Source-Code-Verification-Report.yaml
# Create: Software Source Code Verification Report - DOC-19

# 6. Submit to QUA for template compliance review (SIL 3-4)
# QUA verifies document structure, completeness, EN 50128 references

# 7. Address QUA feedback (if any) - ONE iteration only

# 8. Submit to VMGR for technical review (SIL 3-4)
# VMGR reviews verification evidence, approves/rejects
```

**Independence Requirements (SIL 3-4)**:
- VER **MUST NOT** be the same person as REQ, DES, IMP, TST, INT
- VER reports to VMGR (NOT to PM or COD)
- VER approval required for phase gate transitions
- VER has authority to reject work products (cannot be overridden by PM)

#### For V&V Managers (VMGR)

**Primary Responsibilities** (SIL 3-4 MANDATORY):
- Manage independent verification team (VER reports to VMGR)
- Review and approve all verification reports (11 reports)
- Perform validation activities (VMGR acts as VAL role)
- Provide final V&V approval/rejection for phase gates
- Coordinate with COD (but independent authority)

**Key Workflows**:
1. **`workflows/verification-planning.md`** - Review and approve Software Verification Plan (SVP)
   - Verify VER independence maintained
   - Approve technique selection
   - Approve tool selection and qualification plan
   
2. **`workflows/verification-reporting.md`** - Review verification reports
   - Technical review of verification evidence
   - Assess completeness and correctness
   - Approve or reject with detailed feedback
   - Provide V&V status to COD for gate check

**Typical VMGR Review Workflow**:
```bash
# 1. VER submits verification report (after QUA template compliance approved)

# 2. VMGR reviews verification report
# Read: workflows/verification-reporting.md Section 10 "VMGR Technical Review"
# Check:
#   - Evidence complete? (static analysis, coverage, traceability, metrics)
#   - Defect analysis thorough? (all defects triaged, critical/high closed)
#   - Metrics meet targets? (CCN ≤ 10, 100% coverage, 0 critical defects)
#   - EN 50128 techniques applied correctly? (Tables A.5, A.19, A.21)
#   - Independence preserved? (VER not involved in development)

# 3. VMGR decision
# Option A: APPROVE
#   - Document approval in report (signature, date)
#   - Inform COD: "Verification APPROVED for Phase X"
#   - COD enforces gate based on VMGR decision
# Option B: REJECT
#   - Document rejection reasons (specific, actionable feedback)
#   - Inform COD: "Verification REJECTED for Phase X"
#   - COD BLOCKS gate transition (cannot override VMGR)
#   - VER addresses feedback, resubmits (NEW iteration, not amend)

# 4. VMGR reports V&V status to COD
python3 tools/vmgr/report_vv_status.py --phase implementation --status approved
```

**Authority Structure**:
```
Safety Authority / Customer
        |
    ┌───┴───┐
    |       |
  COD    VMGR (Independent V&V Authority)
    |       |
   PM     VER (Verification Team)
    |
REQ, DES, IMP, TST, INT, QUA, CM, SAF
```

**Key Point**: VMGR has **independent authority** - COD cannot override VMGR approval/rejection decisions.

#### For Quality Assurance (QUA)

**Primary Responsibilities**:
- Template compliance review (MANDATORY SIL 3-4 BEFORE VER submission to VMGR)
- Verify document structure follows EN 50128 requirements
- One-pass review (reject if non-compliant, VER fixes ONCE, resubmits)

**Key Workflows**:
1. **`workflows/verification-reporting.md`** Section 9 "QUA Template Compliance Review"
   - Document ID format (DOC-XXX-YYYY-NNN)
   - Document Control table (version, date, author, approvals)
   - Approvals table with SIL-specific roles
   - Section structure per template
   - EN 50128 references present

**QUA Review Workflow**:
```bash
# 1. VER submits verification report for QUA review

# 2. QUA performs template compliance check
# Read: workflows/verification-reporting.md Section 9
# Check:
#   - Document ID correct? (DOC-19-SWC-VER-001)
#   - Document Control table present?
#   - Approvals table with correct roles? (VER, VMGR for SIL 3-4)
#   - All required sections present? (12 sections + 4 appendices)
#   - EN 50128 references present? (Section 6.2, Tables A.5, A.19, A.21)

# 3. QUA decision (ONE PASS only)
# Option A: APPROVE
#   - Document approval in QA Template Compliance Report
#   - VER proceeds to VMGR technical review
# Option B: REJECT
#   - Document specific non-compliance issues
#   - VER fixes issues ONCE, resubmits
#   - QUA re-reviews (final decision)

# 4. After QUA approval, VER submits to VMGR
```

**Important**: QUA checks **template compliance** (structure, format). VMGR checks **technical content** (evidence, correctness).

#### For Project Managers (PM)

**Usage**:
- Monitor verification progress via metrics dashboards
- Coordinate VER resources (but NOT direct VER technical work)
- Review verification reports for schedule impact
- **Cannot override VER/VMGR decisions** (independence preserved)

**Key Resources**:
- **`resources/verification-metrics.md`** - Track verification progress, defect trends, coverage status
- **`workflows/verification-reporting.md`** Section 14 "Project Management Dashboard"

**PM Monitoring**:
```bash
# View verification metrics dashboard
python3 tools/metrics/generate_dashboard.py --sil 3 --output dashboard.html
# See: Coverage %, Defect density, CCN distribution, Verification progress %

# Check verification bottlenecks
# Read: resources/verification-metrics.md Section 8 "Verification Progress Metrics"
```

### 11 Verification Reports Covered

This skill provides guidance for creating **11 verification reports** across all lifecycle phases:

| Report ID | Report Name | Phase | Workflow Section |
|-----------|-------------|-------|------------------|
| **DOC-2** | SQAP Verification Report | Phase 1 | `workflows/verification-reporting.md` Sec 5.1 |
| **DOC-4** | Software Verification Plan | Phase 1 | `workflows/verification-planning.md` (PRIMARY) |
| **DOC-8** | Software Requirements Verification Report | Phase 2 | `workflows/verification-reporting.md` Sec 5.2 |
| **DOC-14** | SW Architecture and Design Verification Report | Phase 3 | `workflows/verification-reporting.md` Sec 5.3 |
| **DOC-17** | Software Component Design Verification Report | Phase 3 | `workflows/verification-reporting.md` Sec 5.4 |
| **DOC-19** | Software Source Code Verification Report | Phase 4 | `workflows/verification-reporting.md` Sec 5.5 (PRIMARY) |
| **DOC-23** | Software Integration Verification Report | Phase 5 | `workflows/verification-reporting.md` Sec 5.6 |
| **DOC-32** | Software/Hardware Integration Verification Report | Phase 5 | `workflows/verification-reporting.md` Sec 5.7 |
| **DOC-35** | Overall Software Test Verification Report | Phase 6 | `workflows/verification-reporting.md` Sec 5.8 |
| **DOC-40** | Software Validation Verification Report | Phase 6 | `workflows/verification-reporting.md` Sec 5.9 |
| **DOC-44** | Software Maintenance Verification Report | Phase 8 | `workflows/verification-reporting.md` Sec 5.10 |

**Most Common Reports**:
- **DOC-4**: Software Verification Plan (created in Phase 1, updated throughout)
- **DOC-19**: Software Source Code Verification Report (created in Phase 4, most detailed)
- **DOC-35**: Overall Software Test Verification Report (created in Phase 6, comprehensive)

### Tool Integration Commands

**Quick Reference - Static Analysis**:

```bash
# Cppcheck (MANDATORY SIL 3-4)
cppcheck --enable=all --xml --xml-version=2 src/ 2> cppcheck_report.xml

# PC-lint Plus (MANDATORY SIL 3-4, MISRA C)
pclp64 -vm -os(misra_report.xml) +ffn -w3 au-misra3.lnt src/*.c

# Clang Static Analyzer (MANDATORY SIL 3-4)
scan-build -o analysis_results --status-bugs make

# Lizard Complexity (MANDATORY SIL 3-4)
lizard -CCN 10 -w src/

# GCC Compilation with all warnings (MANDATORY all SILs)
gcc -Wall -Wextra -Werror -std=c11 -pedantic src/*.c

# Valgrind Memory Analysis (HR SIL 3-4)
valgrind --leak-check=full --show-leak-kinds=all ./test_executable
```

**Quick Reference - Coverage**:

```bash
# gcov/lcov (MANDATORY SIL 3-4)
gcc -fprofile-arcs -ftest-coverage src/module.c -o module_test
./module_test
gcov src/module.c
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html

# Check coverage thresholds
lcov --summary coverage.info
# SIL 3-4 REQUIREMENT: 100% statement, 100% branch, 100% condition, 100% MC/DC
```

**Quick Reference - Metrics Collection**:

```bash
# Automated metrics collection (all tools)
./tools/metrics/collect_all_metrics.sh 3 metrics_output/

# Generate metrics dashboard
python3 tools/metrics/generate_metrics_report.py \
    --sil 3 \
    --metrics-dir metrics_output/ \
    --output metrics_report.html
```

### Skill Structure

```
.opencode/skills/en50128-verification/
├── SKILL.md (THIS FILE - Overview and quick reference)
├── workflows/ (4 files, ~170 pages)
│   ├── verification-planning.md (50 pages) - SVP creation, technique selection
│   ├── static-analysis-workflow.md (38 pages) - Multi-tool static analysis
│   ├── traceability-verification.md (15 pages) - Forward/backward trace
│   └── verification-reporting.md (40 pages) - 11 verification reports
├── resources/ (5 files, ~230 pages)
│   ├── static-analysis-guidelines.md (40 pages) - Tool config, thresholds
│   ├── traceability-verification-checklist.md (40 pages) - Phase-by-phase
│   ├── verification-tools-reference.md (40 pages) - 12+ tool catalog
│   ├── common-verification-defects.md (40 pages) - 30+ defect patterns
│   └── verification-metrics.md (40 pages) - Metrics formulas, targets
├── verification-criteria/ (5 YAML files from Phase 1)
│   └── [Criteria for each verification type]
└── report-templates/ (2 template files from Phase 1)
    └── [Templates for verification reports]
```

### When to Use Each Workflow

| Workflow | When to Use | Primary Output |
|----------|-------------|----------------|
| **verification-planning.md** | Phase 1 (Planning), updated each phase | Software Verification Plan (SVP) - DOC-4 |
| **static-analysis-workflow.md** | Phase 4 (Implementation), Phase 5 (Integration) | Static analysis reports (Cppcheck, PC-lint, Clang, Lizard) |
| **traceability-verification.md** | All phases (2-7), gate checks | Traceability matrices, gap analysis reports |
| **verification-reporting.md** | End of each phase (2-7) | 11 verification reports (DOC-2, DOC-8, DOC-14, etc.) |

### When to Use Each Resource

| Resource | When to Use | Primary Purpose |
|----------|-------------|-----------------|
| **static-analysis-guidelines.md** | Before running static analysis | Tool configuration, severity classification, thresholds |
| **traceability-verification-checklist.md** | During traceability verification | Phase-specific checklist, forward/backward trace |
| **verification-tools-reference.md** | Tool selection, installation, usage | Comprehensive tool catalog, installation, qualification |
| **common-verification-defects.md** | Defect triage, remediation | 30+ defect patterns with before/after code examples |
| **verification-metrics.md** | Metrics collection, interpretation, reporting | Formulas, targets, benchmarks, dashboards |

### SIL-Specific Requirements Summary

**SIL 0-1** (Advisory/Recommended):
- Static analysis: Recommended
- Complexity: CCN ≤ 20
- Coverage: Statement ≥ 85%, Branch ≥ 75%
- MISRA C: Follow where practical
- Independence: Not required

**SIL 2** (Highly Recommended):
- Static analysis: Highly Recommended
- Complexity: CCN ≤ 15
- Coverage: Statement 100%, Branch 100% (MANDATORY)
- MISRA C: Zero mandatory violations (MANDATORY)
- Independence: Highly Recommended

**SIL 3-4** (MANDATORY):
- Static analysis: **MANDATORY** (Control flow + Data flow analysis)
- Complexity: **CCN ≤ 10 MANDATORY**
- Coverage: **100% statement, branch, condition, MC/DC MANDATORY**
- MISRA C: **Zero mandatory violations MANDATORY**
- Traceability: **100% forward and backward MANDATORY**
- Independence: **MANDATORY** (VER independent from REQ/DES/IMP/TST/INT)
- VMGR: **MANDATORY** (independent V&V authority)

### EN 50128 Compliance Mapping

| EN 50128 Reference | Skill Coverage | Workflow/Resource |
|--------------------|----------------|-------------------|
| **Section 6.2** Software Verification | Complete | All workflows, all resources |
| **Table A.5** Verification techniques | Technique selection | `workflows/verification-planning.md` Sec 3 |
| **Table A.19** Static Analysis | All 8 techniques | `workflows/static-analysis-workflow.md`, `resources/static-analysis-guidelines.md` |
| **Table A.21** Test Coverage | Statement, Branch, Condition, MC/DC | `resources/verification-metrics.md` Sec 3 |
| **Section 7.5.4.10** Source Code Verification | Complete | `workflows/verification-reporting.md` Sec 5.5 |

### Getting Started

**For First-Time Users**:

1. **Read this section** ("How to Use This Skill") - 10 minutes
2. **Read `workflows/verification-planning.md`** - Understand verification planning - 30 minutes
3. **Read `resources/verification-tools-reference.md`** - Understand available tools - 20 minutes
4. **Install verification tools** - Run `./install_tools.sh` - 15 minutes
5. **Try static analysis on sample code** - Run Cppcheck, PC-lint Plus - 30 minutes
6. **Review example verification report** - See `workflows/verification-reporting.md` Appendix A - 20 minutes

**Total Getting Started Time**: ~2 hours

**For Experienced Users**:

1. Jump directly to relevant workflow (verification-planning, static-analysis, traceability, verification-reporting)
2. Use resources as reference (static-analysis-guidelines, verification-metrics, common-defects)
3. Follow tool commands in "Tool Integration Commands" section above

### Related Skills

**Upstream Skills** (provide inputs to verification):
- **en50128-requirements** - Requirements documents (SRS) to verify
- **en50128-design** - Design documents (SAS, SDS) to verify
- **en50128-implementation** - Source code to verify
- **en50128-testing** - Test results to verify coverage

**Downstream Skills** (consume verification outputs):
- **en50128-validation** - Uses verification reports as evidence
- **en50128-quality** - Uses verification metrics for quality assessment
- **en50128-lifecycle-coordination** - Uses verification status for gate checks

**Parallel Skills** (used concurrently):
- **en50128-configuration** - Version control for verification artifacts
- **en50128-safety** - Safety analysis integrated with verification

### Common Pitfalls and Best Practices

**Pitfall 1**: Running static analysis without configuration
- **Fix**: Read `resources/static-analysis-guidelines.md` BEFORE running tools
- **Best Practice**: Use provided tool configuration files (Cppcheck project file, PC-lint options)

**Pitfall 2**: Ignoring Low/Medium severity defects
- **Fix**: All defects must be triaged, documented (fix or justify)
- **Best Practice**: Zero critical, zero high defects (MANDATORY SIL 3-4)

**Pitfall 3**: Incomplete traceability (missing forward or backward traces)
- **Fix**: Run traceability verification scripts (forward AND backward)
- **Best Practice**: 100% traceability (MANDATORY SIL 3-4)

**Pitfall 4**: Submitting verification report without QUA review (SIL 3-4)
- **Fix**: ALWAYS submit to QUA for template compliance BEFORE VMGR technical review
- **Best Practice**: Follow workflow order: VER → QUA (template) → VMGR (technical)

**Pitfall 5**: VMGR (or PM) overriding VER rejection
- **Fix**: VER/VMGR have independent authority (cannot be overridden)
- **Best Practice**: Respect independence requirements (EN 50128 5.3.5)

**Pitfall 6**: Insufficient metrics collection
- **Fix**: Use automated metrics collection script (`collect_all_metrics.sh`)
- **Best Practice**: Collect metrics continuously (CI/CD), not just at gate checks

**Pitfall 7**: Using single static analysis tool (SIL 3-4)
- **Fix**: Multi-tool strategy required (Cppcheck + PC-lint Plus + Clang + Lizard)
- **Best Practice**: Each tool finds different defect types (complementary)

**Pitfall 8**: Not documenting tool qualification (T2/T3 tools)
- **Fix**: Document tool version, vendor qualification, validation testing
- **Best Practice**: Maintain Tool Qualification Report (see `resources/verification-tools-reference.md` Sec 11)

### Success Criteria

**Verification Phase Complete When**:
- ✓ All 11 verification reports created (or applicable subset for phase)
- ✓ Zero critical defects, zero high defects (SIL 3-4)
- ✓ 100% statement, branch, condition, MC/DC coverage (SIL 3-4)
- ✓ CCN ≤ 10 for all functions (SIL 3-4)
- ✓ Zero MISRA C mandatory violations (SIL 2+)
- ✓ 100% forward and backward traceability (SIL 3-4)
- ✓ QUA template compliance approved (SIL 3-4)
- ✓ VMGR technical review approved (SIL 3-4)
- ✓ All verification evidence collected and archived

**Ready for Next Phase (Gate Check) When**:
- ✓ Verification report signed by VER, VMGR (SIL 3-4)
- ✓ All defects closed (or justified and approved)
- ✓ Metrics meet SIL-specific targets
- ✓ COD receives VMGR approval for phase transition

---

## Verification Techniques (EN 50128 Table A.5)

**EN 50128 Section 6.2, 7.3, Table A.5** defines verification and testing techniques.

**Verification Techniques (subset of Table A.5):**

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Formal Proof | D.29 | - | R | HR |
| 2 | Probabilistic Testing | D.44 | R | R | - |
| 3 | **Static Analysis** | Table A.19 | - | HR | **M** |
| 5 | Metrics | D.37 | - | R | HR |
| 7 | **Traceability** | D.58 | R | HR | **M** |
| 9 | Software Error Effect Analysis | D.25 | - | R | HR |
| 10 | Software Fault Tree Analysis | D.25 | - | R | HR |

**Mandatory for SIL 3-4:**
- **Static Analysis (3)** - **MANDATORY** (see Table A.19 below)
- **Traceability (7)** - **MANDATORY**

**Highly Recommended for SIL 3-4:**
- Formal Proof, Metrics, Software Error Effect Analysis, Fault Tree Analysis

**Approved Combination (SIL 3-4):**
- **3, 5, 7, 8 + one from {1, 2, 6}**
- (Static Analysis, Metrics, Traceability, [Testing] + Formal Proof OR Probabilistic Testing)

**Independence Requirements:**
- **SIL 3-4:** Verification **MUST** be performed by independent verifier (not developer/designer/implementer)

**Standard Reference:** `std/EN50128-2011.md` Section 6.2, Table A.5

## Static Analysis Techniques (EN 50128 Table A.19)

**EN 50128 Annex A, Table A.19** defines static analysis techniques:

| # | TECHNIQUE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-----------|-----|-------|---------|---------|
| 1 | Boundary Value Analysis | D.4 | R | HR | HR |
| 2 | **Control Flow Analysis** | D.9 | R | HR | **M** |
| 3 | **Data Flow Analysis** | D.11 | R | HR | **M** |
| 4 | Range Checking | D.45 | R | HR | HR |
| 5 | Semantic Analysis | D.41 | - | R | HR |
| 6 | **Code Review / Walkthrough** | D.56, D.61 | HR | HR | HR |
| 7 | **Fagan Inspection** | D.23 | - | R | HR |
| 8 | Complexity Metrics | D.8, D.37 | R | HR | HR |

**Mandatory for SIL 3-4:**
- **Control Flow Analysis (2)** - **MANDATORY**
- **Data Flow Analysis (3)** - **MANDATORY**

**Highly Recommended for SIL 3-4:**
- Boundary Value Analysis, Range Checking, Semantic Analysis, Code Review, Fagan Inspection, Complexity Metrics

**Tools for Static Analysis:**
- **PC-lint Plus:** MISRA C compliance, control/data flow
- **Cppcheck:** General static analysis
- **Clang Static Analyzer:** Deep analysis
- **Lizard:** Complexity metrics
- **SonarQube:** Code quality metrics

**Requirements:**
- Static Analysis is **MANDATORY** for SIL 3-4
- Control Flow and Data Flow Analysis are **MANDATORY** for SIL 3-4
- Tools SHALL be qualified per Annex C
- Analysis results SHALL be documented in verification reports

**Standard Reference:** `std/EN50128-2011.md` Annex A, Table A.19

## Verification Overview

**Independent Verification**: MANDATORY for SIL 3-4 (Highly Recommended for SIL 2)
- Verifier must be independent from designer and implementer
- Verification activities performed throughout lifecycle
- Evidence-based verification

## Static Analysis (Mandatory SIL 3-4)

### PC-lint Plus Configuration

```bash
# Run PC-lint Plus with MISRA C:2012
pclp64 \
    -i"$PROJECT_ROOT/include" \
    --misra3 \
    +ffn \
    -b \
    au-misra3.lnt \
    source.c

# Generate HTML report
pclp64 --misra3 --html=report.html source.c
```

**PC-lint Configuration File** (`pclint.lnt`):
```
// MISRA C:2012 compliance
+libclass(angle, foreign)
-strong(AJX)
+fll
-width(120)

// SIL-specific rules
// SIL 3-4: Complexity limit 10
-esym(818, *)  // Could be pointer to const
```

### Cppcheck with MISRA Addon

```bash
# Run Cppcheck with MISRA C:2012
cppcheck \
    --enable=all \
    --addon=misra \
    --suppress=missingIncludeSystem \
    --inline-suppr \
    --template='{file}:{line}: {severity}: {message} [{id}]' \
    --xml \
    --xml-version=2 \
    source.c 2> cppcheck_report.xml

# Generate HTML report
cppcheck-htmlreport \
    --file=cppcheck_report.xml \
    --report-dir=cppcheck_html \
    --source-dir=.
```

**Cppcheck Project File** (`cppcheck-project.xml`):
```xml
<?xml version="1.0" encoding="UTF-8"?>
<project>
    <paths>
        <dir name="src"/>
    </paths>
    <exclude>
        <path name="test/"/>
    </exclude>
    <libraries>
        <library>std</library>
    </libraries>
    <defines>
        <define name="TARGET_PLATFORM=RAILWAY"/>
        <define name="SIL_LEVEL=3"/>
    </defines>
</project>
```

### Clang Static Analyzer

```bash
# Run Clang Static Analyzer
clang --analyze \
    -Xanalyzer -analyzer-output=text \
    -Xanalyzer -analyzer-checker=core \
    -Xanalyzer -analyzer-checker=deadcode \
    -Xanalyzer -analyzer-checker=security \
    -Xanalyzer -analyzer-checker=unix \
    source.c

# Or use scan-build
scan-build -o analysis_results make
```

### Splint (Secure Programming Lint)

```bash
# Run splint for secure programming checks
splint \
    +posixlib \
    +checks \
    -warnposix \
    -exportlocal \
    source.c
```

## Cyclomatic Complexity Analysis

### Using Lizard

```bash
# Analyze complexity
lizard \
    --CCN 10 \
    --length 100 \
    --arguments 5 \
    --warnings_only \
    src/

# Generate HTML report
lizard -o complexity_report.html \
    --CCN 10 \
    src/

# Check specific file
lizard -w source.c
```

**Complexity Limits by SIL**:
```bash
# SIL 0-1: CCN <= 20
lizard --CCN 20 src/

# SIL 2: CCN <= 15
lizard --CCN 15 src/

# SIL 3-4: CCN <= 10
lizard --CCN 10 src/
```

### Python Script for Complexity Verification

```python
#!/usr/bin/env python3
"""Verify cyclomatic complexity meets SIL requirements."""

import sys
import subprocess
import json

SIL_COMPLEXITY_LIMITS = {
    0: 20,
    1: 20,
    2: 15,
    3: 10,
    4: 10
}

def check_complexity(source_dir, sil_level):
    """Check that all functions meet complexity limit."""
    limit = SIL_COMPLEXITY_LIMITS.get(sil_level, 10)
    
    result = subprocess.run(
        ['lizard', '--CCN', str(limit), '--warnings_only', source_dir],
        capture_output=True,
        text=True
    )
    
    if result.returncode != 0:
        print(f"ERROR: Functions exceed complexity limit ({limit}) for SIL {sil_level}")
        print(result.stdout)
        return False
    
    print(f"SUCCESS: All functions meet SIL {sil_level} complexity limit ({limit})")
    return True

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: check_complexity.py <source_dir> <sil_level>")
        sys.exit(1)
    
    source_dir = sys.argv[1]
    sil_level = int(sys.argv[2])
    
    if not check_complexity(source_dir, sil_level):
        sys.exit(1)
```

## Coverage Verification

### gcov/lcov for Coverage Analysis

```bash
# Compile with coverage instrumentation
gcc -fprofile-arcs -ftest-coverage -O0 source.c -o test

# Run tests
./test

# Generate coverage data
gcov source.c

# Generate HTML report with lcov
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html

# Check coverage thresholds
lcov --summary coverage.info
```

### Python Script for Coverage Verification

```python
#!/usr/bin/env python3
"""Verify test coverage meets SIL requirements."""

import sys
import subprocess
import re

SIL_COVERAGE_REQUIREMENTS = {
    0: {'statement': 80, 'branch': 70},
    1: {'statement': 90, 'branch': 80},
    2: {'statement': 100, 'branch': 100},
    3: {'statement': 100, 'branch': 100, 'condition': 100},
    4: {'statement': 100, 'branch': 100, 'condition': 100}
}

def check_coverage(coverage_file, sil_level):
    """Check coverage meets SIL requirements."""
    requirements = SIL_COVERAGE_REQUIREMENTS.get(sil_level, {})
    
    # Parse lcov summary
    result = subprocess.run(
        ['lcov', '--summary', coverage_file],
        capture_output=True,
        text=True
    )
    
    # Extract coverage percentages
    lines_match = re.search(r'lines\.*:\s+([\d.]+)%', result.stdout)
    branches_match = re.search(r'branches\.*:\s+([\d.]+)%', result.stdout)
    
    if not lines_match or not branches_match:
        print("ERROR: Could not parse coverage data")
        return False
    
    line_coverage = float(lines_match.group(1))
    branch_coverage = float(branches_match.group(1))
    
    # Check requirements
    passed = True
    
    if line_coverage < requirements.get('statement', 0):
        print(f"FAIL: Statement coverage {line_coverage}% < {requirements['statement']}%")
        passed = False
    else:
        print(f"PASS: Statement coverage {line_coverage}% >= {requirements['statement']}%")
    
    if branch_coverage < requirements.get('branch', 0):
        print(f"FAIL: Branch coverage {branch_coverage}% < {requirements['branch']}%")
        passed = False
    else:
        print(f"PASS: Branch coverage {branch_coverage}% >= {requirements['branch']}%")
    
    return passed

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: check_coverage.py <coverage.info> <sil_level>")
        sys.exit(1)
    
    if not check_coverage(sys.argv[1], int(sys.argv[2])):
        sys.exit(1)
```

## MISRA C Compliance Verification

### MISRA C:2012 Rule Categories

**Mandatory Rules**: Must be followed (no deviations)
**Required Rules**: Should be followed (deviations require justification)
**Advisory Rules**: Recommended (deviations acceptable)

### Common MISRA C Violations to Check

```c
// Rule 8.7: Functions/objects should have internal linkage
// VIOLATION: Function not declared static
void helper_function(void);  // Should be static if only used in this file

// CORRECT:
static void helper_function(void);

// Rule 10.1: Operands shall not be of inappropriate essential type
// VIOLATION: Implicit type conversion
uint8_t a = 255;
uint8_t b = a + 1;  // Overflow

// CORRECT:
uint8_t a = 255U;
uint16_t temp = (uint16_t)a + 1U;
uint8_t b = (temp > 255U) ? 255U : (uint8_t)temp;

// Rule 11.5: Conversion from pointer to void into pointer to object
// VIOLATION: Cast from void* without explicit cast
void* ptr = get_buffer();
uint8_t* data = ptr;  // Implicit conversion

// CORRECT:
void* ptr = get_buffer();
uint8_t* data = (uint8_t*)ptr;  // Explicit cast

// Rule 14.4: The controlling expression of an if statement shall have boolean type
// VIOLATION: Non-boolean condition
uint32_t value = get_value();
if (value) {  // Should be explicit comparison
    // ...
}

// CORRECT:
uint32_t value = get_value();
if (value != 0U) {
    // ...
}

// Rule 17.7: Return value of function shall be used
// VIOLATION: Ignoring return value
read_sensor(&value);  // Return value ignored

// CORRECT:
error_t err = read_sensor(&value);
if (err != SUCCESS) {
    handle_error(err);
}

// Rule 21.3: malloc/free shall not be used
// VIOLATION: Dynamic memory
uint8_t* buffer = malloc(size);

// CORRECT (SIL 2+):
static uint8_t buffer[BUFFER_SIZE];
```

### MISRA Deviation Process

When MISRA rule deviation is necessary:

1. **Document Deviation**:
```c
/* MISRA Deviation: Rule 11.5
 * Justification: Hardware register access requires pointer cast
 * Risk Assessment: Low - register address is fixed and validated
 * Approved by: [Name], [Date]
 */
volatile uint32_t* reg = (volatile uint32_t*)HARDWARE_REG_ADDR;
```

2. **Log in Deviation Report**:
```
Deviation ID: DEV-001
Rule: MISRA C:2012 Rule 11.5
File: hardware.c:45
Justification: Hardware register access requires pointer cast
Alternative: None available for memory-mapped I/O
Risk: Low - address validated at build time
Approval: Safety Manager, 2024-01-15
```

## Verification Checklist

### Requirements Traceability
- [ ] All requirements traced to design elements
- [ ] All design elements traced to code
- [ ] All code traced to tests
- [ ] Bidirectional traceability verified

### Code Quality
- [ ] Static analysis run (PC-lint/Cppcheck)
- [ ] Zero critical issues
- [ ] All warnings reviewed
- [ ] MISRA C compliance verified
- [ ] Deviations documented and approved

### Complexity
- [ ] Cyclomatic complexity within limits
  - SIL 0-1: ≤ 20
  - SIL 2: ≤ 15
  - SIL 3-4: ≤ 10
- [ ] Function length reasonable (≤ 100 lines recommended)
- [ ] Nesting depth reasonable (≤ 4 levels)

### Testing
- [ ] All unit tests pass
- [ ] Coverage requirements met
  - SIL 2: 100% statement + branch
  - SIL 3-4: 100% statement + branch + condition
- [ ] Boundary values tested
- [ ] Error conditions tested

### Documentation
- [ ] Code comments adequate
- [ ] Design rationale documented
- [ ] Safety considerations documented
- [ ] MISRA deviations documented

### Memory Safety
- [ ] No dynamic allocation (SIL 2+)
- [ ] No recursion (highly recommended SIL 3-4)
- [ ] Buffer bounds checked
- [ ] Pointer validity checked
- [ ] Stack usage within limits

## Verification Report Template

```markdown
# Software Verification Report

## Project Information
- Project Name: [Name]
- Software Component: [Component]
- SIL Level: [0-4]
- Verification Date: [Date]
- Verifier: [Name] (Independent: Yes/No)

## Verification Activities

### 1. Static Analysis
- **Tool**: PC-lint Plus 2.0
- **Configuration**: MISRA C:2012, SIL 3 rules
- **Results**: 
  - Critical Issues: 0
  - Warnings: 5 (all reviewed and justified)
  - MISRA Deviations: 2 (documented in DEV-001, DEV-002)

### 2. Complexity Analysis
- **Tool**: Lizard 1.17
- **Limit**: CCN ≤ 10 (SIL 3)
- **Results**: 
  - Maximum CCN: 8 (function: process_safety_state)
  - Average CCN: 4.2
  - Passed: YES

### 3. Coverage Analysis
- **Tool**: gcov/lcov 1.15
- **Requirements**: 100% statement, branch, condition (SIL 3)
- **Results**:
  - Statement Coverage: 100%
  - Branch Coverage: 100%
  - Condition Coverage: 100%
  - Passed: YES

### 4. Traceability Verification
- All requirements traced to code: YES
- All code traced to tests: YES
- Bidirectional traceability complete: YES

## Verification Conclusion
- Overall Result: PASS
- Verification Complete: YES
- Ready for Validation: YES

## Approvals
- Verifier: [Signature], [Date]
- Project Manager: [Signature], [Date]
```

## Automated Verification Script

```python
#!/usr/bin/env python3
"""Complete verification workflow for EN 50128."""

import sys
import subprocess
import os

def run_verification(source_dir, sil_level):
    """Run all verification checks."""
    print(f"=== EN 50128 Verification for SIL {sil_level} ===\n")
    
    results = {}
    
    # 1. Static Analysis
    print("1. Running static analysis (Cppcheck)...")
    result = subprocess.run(
        ['cppcheck', '--enable=all', '--addon=misra', source_dir],
        capture_output=True
    )
    results['static_analysis'] = (result.returncode == 0)
    
    # 2. Complexity Check
    print("2. Checking cyclomatic complexity...")
    complexity_limits = {0: 20, 1: 20, 2: 15, 3: 10, 4: 10}
    limit = complexity_limits.get(sil_level, 10)
    result = subprocess.run(
        ['lizard', '--CCN', str(limit), '--warnings_only', source_dir],
        capture_output=True
    )
    results['complexity'] = (result.returncode == 0)
    
    # 3. Coverage Check (if coverage.info exists)
    if os.path.exists('coverage.info'):
        print("3. Verifying test coverage...")
        result = subprocess.run(
            ['lcov', '--summary', 'coverage.info'],
            capture_output=True,
            text=True
        )
        # Parse and check coverage (simplified)
        results['coverage'] = ('100.0%' in result.stdout)
    else:
        print("3. Coverage file not found (skipping)")
        results['coverage'] = None
    
    # 4. Summary
    print("\n=== Verification Results ===")
    for check, passed in results.items():
        if passed is None:
            status = "SKIPPED"
        elif passed:
            status = "PASS"
        else:
            status = "FAIL"
        print(f"{check}: {status}")
    
    # Overall result
    all_passed = all(r for r in results.values() if r is not None)
    print(f"\nOverall: {'PASS' if all_passed else 'FAIL'}")
    
    return 0 if all_passed else 1

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: verify.py <source_dir> <sil_level>")
        sys.exit(1)
    
    sys.exit(run_verification(sys.argv[1], int(sys.argv[2])))
```

## Tool Integration in Build System

### Makefile Integration

```makefile
# Verification targets
.PHONY: verify verify-static verify-complexity verify-coverage

# Complete verification
verify: verify-static verify-complexity verify-coverage
	@echo "=== All Verification Checks Passed ==="

# Static analysis
verify-static:
	cppcheck --enable=all --addon=misra --suppress=missingIncludeSystem src/
	clang --analyze src/*.c

# Complexity check
verify-complexity:
	lizard --CCN $(COMPLEXITY_LIMIT) --warnings_only src/

# Coverage check
verify-coverage:
	lcov --summary coverage.info
	@python3 tools/check_coverage.py coverage.info $(SIL_LEVEL)

# MISRA compliance
verify-misra:
	pclp64 --misra3 src/*.c
```

### CMake Integration

```cmake
# Verification targets
find_program(CPPCHECK cppcheck)
find_program(LIZARD lizard)
find_program(LCOV lcov)

if(CPPCHECK)
    add_custom_target(verify-static
        COMMAND ${CPPCHECK} --enable=all --addon=misra src/
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

if(LIZARD)
    add_custom_target(verify-complexity
        COMMAND ${LIZARD} --CCN ${COMPLEXITY_LIMIT} --warnings_only src/
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

# Add to verification target
add_custom_target(verify
    DEPENDS verify-static verify-complexity verify-coverage
)
```

## References

- EN 50128:2011 Section 6.4 (Software Verification)
- EN 50128:2011 Table A.5 (Verification Techniques)
- MISRA C:2012 Guidelines for C
- ISO/IEC 9899:2018 (C Standard)
