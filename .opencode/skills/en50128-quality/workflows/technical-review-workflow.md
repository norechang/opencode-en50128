# Technical Review Workflow

**EN 50128 Reference**: Section 6.5.4.5(e) (Methods, measures and tools for QA), Table A.5 (Verification)  
**Phase**: All phases (cross-cutting activity)  
**Role**: Quality Assurance (QUA), with subject matter experts  
**SIL Level**: All (0-4)

---

## Purpose

This workflow defines the technical review process for EN 50128 railway software development. Technical reviews are **content-focused** reviews performed AFTER document template compliance is verified by QA. They include design reviews, code reviews, and test reviews.

**Key Objectives**:
- Verify technical correctness of requirements, designs, code, and tests
- Identify defects early in lifecycle (shift-left quality)
- Ensure EN 50128 technical standards compliance (MISRA C, complexity, defensive programming)
- Multi-reviewer process with subject matter experts (SMEs)
- Defect tracking and resolution workflow
- Review report generation for audit trail

**Technical Review vs. Document Review**:
- **Document Review** (QUA only): Template compliance, format, structure (FIRST)
- **Technical Review** (QUA + SMEs): Content correctness, technical quality (AFTER document review approval)

**Inputs**:
- Deliverable approved by QA for template compliance
- EN 50128 technical standards (MISRA C, complexity limits, defensive programming)
- Review checklist (design, code, or test specific)
- SIL level for project

**Outputs**:
- Technical Review Report (approved/rejected)
- Defect list with severity (Critical, Major, Minor)
- Corrective action items
- Approval for next phase OR rework required

---

## Table of Contents

1. [Technical Review Overview](#technical-review-overview)
2. [Review Types](#review-types)
3. [Design Review Process](#design-review-process)
4. [Code Review Process](#code-review-process)
5. [Test Review Process](#test-review-process)
6. [Review Meeting Management](#review-meeting-management)
7. [Defect Management](#defect-management)
8. [Review Checklists](#review-checklists)
9. [Automated Technical Checks](#automated-technical-checks)
10. [Tool Integration](#tool-integration)
11. [SIL-Specific Requirements](#sil-specific-requirements)
12. [Example Technical Review Scenarios](#example-technical-review-scenarios)

---

## Technical Review Overview

### Purpose of Technical Reviews

**EN 50128 Section 6.5.4.5(e)**: "Methods, measures and tools for quality assurance shall include: reviews, audits, inspections, walkthroughs"

Technical reviews verify:
1. **Technical Correctness**: Does the artifact correctly implement requirements?
2. **EN 50128 Compliance**: Does the artifact meet EN 50128 technical standards?
3. **Quality**: Is the artifact maintainable, testable, and safe?
4. **Traceability**: Are all upstream requirements addressed?

**Technical Reviews are MANDATORY for**:
- SIL 3-4: All deliverables (requirements, design, code, tests)
- SIL 2: Highly recommended for all deliverables
- SIL 0-1: Recommended for critical deliverables

---

### Technical Review Workflow Overview

```
QA approves document for template compliance (document review PASS)
          ↓
Technical review preparation (assign reviewers, schedule meeting)
          ↓
Pre-review (reviewers read artifact, identify issues)
          ↓
Review meeting (present artifact, discuss issues, log defects)
          ↓
Review report generation (defect list, severity, corrective actions)
          ↓
    [NO DEFECTS] → Approve, proceed to next phase
          ↓
    [DEFECTS FOUND] → Rework required
          ↓
Developer fixes defects
          ↓
Re-review (verify fixes)
    ├─→ [ALL FIXED] → Approve, proceed
    └─→ [NOT FIXED] → Escalate to PM + QA Manager
```

---

### Review Team Composition

| Review Type | Participants | Roles |
|------------|-------------|-------|
| **Requirements Review** | REQ (author), SAF, DES, QUA | REQ presents, SAF checks safety requirements, DES checks implementability, QUA checks process |
| **Design Review (Architecture)** | DES (author), REQ, SAF, IMP, QUA | DES presents, REQ checks traceability, SAF checks safety design, IMP checks implementability, QUA checks process |
| **Design Review (Detailed)** | DES (author), IMP, TST, QUA | DES presents, IMP checks implementability, TST checks testability, QUA checks process |
| **Code Review** | IMP (author), Peer Developer, QUA | IMP presents, Peer reviews code, QUA checks MISRA C/complexity |
| **Test Review** | TST (author), REQ, VER, QUA | TST presents, REQ checks coverage, VER checks evidence, QUA checks process |

**Independence Note (SIL 3-4)**:
- For SIL 3-4, at least one reviewer MUST be independent of development team
- QUA always independent
- VER independent for verification activities
- VAL independent for validation activities

---

## Review Types

### 1. Requirements Review

**Purpose**: Verify Software Requirements Specification (SRS) correctness and completeness

**Review Focus**:
- Are requirements unambiguous, testable, verifiable?
- Are requirements traceable to system requirements?
- Are SIL levels assigned correctly?
- Are safety requirements identified?
- Are SHALL/SHOULD/MAY keywords used correctly?

**Reviewers**: REQ (author), SAF, DES, QUA

**Checklist**: See [Requirements Review Checklist](#requirements-review-checklist)

---

### 2. Design Review (Architecture)

**Purpose**: Verify Software Architecture Specification (SAS) correctness and quality

**Review Focus**:
- Is architecture modular and maintainable?
- Are interfaces well-defined (fully defined interface)?
- Is complexity within limits (CCN ≤ 10 for SIL 3-4)?
- Is traceability to SRS complete?
- Are defensive programming patterns used?
- Are safety mechanisms designed (redundancy, voting, watchdog)?

**Reviewers**: DES (author), REQ, SAF, IMP, QUA

**Checklist**: See [Design Review Checklist](#design-review-checklist)

---

### 3. Design Review (Detailed)

**Purpose**: Verify Software Design Specification (SDS) correctness and implementability

**Review Focus**:
- Are algorithms correct and efficient?
- Are data structures appropriate?
- Is traceability to SAS/SRS complete?
- Is design implementable in C with static allocation?
- Is design testable (unit tests can be written)?

**Reviewers**: DES (author), IMP, TST, QUA

**Checklist**: See [Design Review Checklist](#design-review-checklist)

---

### 4. Code Review

**Purpose**: Verify C source code correctness, MISRA C compliance, and quality

**Review Focus**:
- MISRA C:2012 compliance (MANDATORY SIL 2+, zero mandatory violations)
- Cyclomatic complexity within limits (≤10 for SIL 3-4, ≤15 for SIL 2)
- Defensive programming (input validation, error handling, assertions)
- Traceability to design
- No dynamic memory allocation (SIL 2+)
- No recursion (highly recommended SIL 3-4)

**Reviewers**: IMP (author), Peer Developer, QUA

**Checklist**: See [Code Review Checklist](#code-review-checklist)

---

### 5. Test Review

**Purpose**: Verify test plans, test specifications, and test reports for completeness and quality

**Review Focus**:
- Are all requirements covered by tests (traceability)?
- Is coverage adequate (SIL-specific: statement, branch, condition)?
- Are test cases well-designed (boundary values, equivalence classes)?
- Are test results documented and evidence provided?
- Are defects tracked and resolved?

**Reviewers**: TST (author), REQ, VER, QUA

**Checklist**: See [Test Review Checklist](#test-review-checklist)

---

## Design Review Process

### Step 1: Design Review Preparation

**Trigger**: Software Architecture Specification (SAS) or Software Design Specification (SDS) approved by QA for template compliance

**Actions**:
1. **Schedule review meeting** (2-4 hours depending on SIL level)
2. **Assign reviewers**:
   - Architecture: DES (author), REQ, SAF, IMP, QUA
   - Detailed Design: DES (author), IMP, TST, QUA
3. **Distribute materials** (at least 3 days before meeting):
   - SAS or SDS document
   - SRS document (for traceability check)
   - Design review checklist
4. **Reviewers prepare** (pre-review):
   - Read design document
   - Check against checklist
   - Identify potential issues
   - Prepare questions

**Pre-Review Checklist Distribution**:
```bash
# Send review invitation
echo "Design Review Scheduled:
Date: 2026-03-20 10:00-12:00
Location: Conference Room A
Materials: docs/DOC-DES-SAS-001.md (v1.0)
Checklist: .opencode/skills/en50128-quality/templates/Design-Review-Checklist.md

Please review materials and prepare comments before meeting." \
| mail -s "Design Review: DOC-DES-SAS-001" reviewers@project.com
```

---

### Step 2: Design Review Meeting

**Duration**: 2-4 hours (depending on design complexity and SIL level)

**Agenda**:
1. **Introduction** (5 min):
   - Review purpose and scope
   - Review checklist overview
   - Defect logging process

2. **Design Presentation** (30-60 min):
   - Designer presents architecture or detailed design
   - Module structure and responsibilities
   - Interface specifications
   - Design decisions and rationale
   - Traceability to requirements

3. **Walkthrough** (60-120 min):
   - Reviewer 1 (REQ): Check requirements traceability
   - Reviewer 2 (SAF): Check safety design patterns
   - Reviewer 3 (IMP): Check implementability
   - Reviewer 4 (QUA): Check EN 50128 compliance (modularity, complexity, defensive programming)

4. **Defect Discussion** (30-60 min):
   - Log defects with severity (Critical, Major, Minor)
   - Assign corrective actions
   - Estimate rework effort

5. **Wrap-up** (10 min):
   - Summarize defects
   - Determine review outcome (Approved / Minor Rework / Major Rework / Rejected)
   - Schedule re-review if needed

---

### Step 3: Design Review Report Generation

**QA Action**: Generate Design Review Report within 2 business days

**Report Contents**:
- Review summary (date, participants, artifact reviewed)
- Review outcome (Approved / Minor Rework / Major Rework / Rejected)
- Defect list with severity and corrective actions
- Traceability check results
- Complexity analysis results
- EN 50128 compliance assessment

**Example Report**:
```markdown
# Design Review Report: DOC-DES-SAS-001

## Review Summary

| Field | Value |
|-------|-------|
| **Artifact Reviewed** | DOC-DES-SAS-001 (Software Architecture Specification v1.0) |
| **Review Date** | 2026-03-20 |
| **Review Type** | Architecture Design Review |
| **SIL Level** | 3 |
| **Participants** | Alice (DES - author), Bob (REQ), Carol (SAF), Dave (IMP), Eve (QUA) |
| **Duration** | 3 hours |

## Review Outcome

**Outcome**: MINOR REWORK REQUIRED

**Rationale**: Design is generally sound with good modularity and traceability. However, 3 defects identified requiring minor fixes before approval.

## Defects Found

### Defect 1: Missing Safety Interlock in Emergency Stop Module
- **Severity**: CRITICAL
- **Found By**: Carol (SAF)
- **Location**: Section 4.3 (Emergency Stop Module)
- **Issue**: Emergency stop module does not include redundancy for safety-critical function (SIL 3 requirement)
- **Impact**: Safety requirement REQ-SAFETY-005 not fully addressed
- **Corrective Action**: Add redundant emergency stop channels with voting logic
- **Assigned To**: Alice (DES)
- **Due Date**: 2026-03-25

### Defect 2: DoorController Complexity May Exceed Limit
- **Severity**: MAJOR
- **Found By**: Dave (IMP)
- **Location**: Section 4.2 (DoorController Module)
- **Issue**: DoorController module has 15 responsibilities, likely to exceed CCN ≤ 10 limit when implemented
- **Impact**: Will fail complexity check during code review
- **Corrective Action**: Split DoorController into DoorControl (open/close) and DoorMonitor (sensor monitoring)
- **Assigned To**: Alice (DES)
- **Due Date**: 2026-03-25

### Defect 3: Interface Specification Incomplete for SensorInterface
- **Severity**: MINOR
- **Found By**: Bob (REQ)
- **Location**: Section 5.3 (SensorInterface ICD)
- **Issue**: Missing error code definitions for sensor failures
- **Impact**: Implementer will need to define error codes, may be inconsistent
- **Corrective Action**: Add error code enumeration (SENSOR_OK, SENSOR_FAULT, SENSOR_TIMEOUT)
- **Assigned To**: Alice (DES)
- **Due Date**: 2026-03-22

## Checklist Results

| Check | Status | Notes |
|-------|--------|-------|
| Requirements Traceability | PASS | 40/40 requirements traced (100%) |
| Modularity | PASS | 8 modules with clear responsibilities |
| Interface Specification | MINOR ISSUE | Missing error codes (Defect 3) |
| Complexity Estimation | MAJOR ISSUE | DoorController may exceed limit (Defect 2) |
| Defensive Programming | PASS | Input validation and error handling designed |
| Safety Design | CRITICAL ISSUE | Missing redundancy (Defect 1) |
| Static Allocation Design | PASS | All data structures static |
| No Recursion | PASS | No recursive calls in design |

## Next Steps

1. Designer (Alice) fixes defects 1, 2, 3 by 2026-03-25
2. Designer updates SAS document to v1.1
3. Designer submits for re-review via `workspace.py wf submit`
4. QA performs document review (template compliance)
5. Technical re-review (desk check by SAF, IMP, QUA - no full meeting)
6. If approved, proceed to detailed design phase

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **QA Manager (Review Lead)** | Eve Green | | 2026-03-21 |
| **Safety Manager** | Carol White | | 2026-03-21 |
```

---

### Step 4: Design Rework and Re-Review

**Designer Action**:
1. Fix all defects identified in review report
2. Update design document (version 1.0 → 1.1)
3. Update Version History table with changes
4. Update traceability if requirements affected
5. Submit for re-review

**Re-Review Process**:
- **Minor Rework** (< 3 defects, no Critical): Desk check by QA and key reviewers (no full meeting)
- **Major Rework** (≥ 3 defects or ≥ 1 Critical): Full review meeting repeated

**Re-Review Approval**:
```bash
# Designer submits reworked design
workspace.py wf submit \
    --deliverable DOC-DES-SAS-001 \
    --phase design \
    --author "Alice Designer" \
    --version 1.1 \
    --comments "Fixed defects from design review: added safety redundancy, split DoorController module, added error codes"

# QA document review (template compliance)
python3 tools/document_checker.py \
    --document docs/DOC-DES-SAS-001.md \
    --sil 3 \
    --output evidence/qa/doc_review_DOC-DES-SAS-001_v1.1.json

# QA approves template compliance
workspace.py wf review \
    --deliverable DOC-DES-SAS-001 \
    --reviewer QUA \
    --status approved \
    --comments "Template compliance verified (v1.1)"

# Technical re-review (desk check)
# SAF checks safety redundancy fix → Approved
# IMP checks module split → Approved
# QUA checks overall compliance → Approved

# QA approves technical review
workspace.py wf review \
    --deliverable DOC-DES-SAS-001 \
    --reviewer QUA \
    --status approved \
    --comments "All design review defects fixed. Design approved for implementation. Proceed to detailed design and implementation phases."
```

---

## Code Review Process

### Step 1: Code Review Preparation

**Trigger**: Code implementation complete, unit tests passing, developer ready for review

**Pre-Review Automated Checks** (Developer runs BEFORE submitting):
```bash
# 1. MISRA C compliance check (MANDATORY SIL 2+)
cppcheck --enable=all --addon=misra.json \
    --suppress=missingIncludeSystem \
    --xml --xml-version=2 \
    src/*.c 2> evidence/static_analysis/cppcheck_report.xml

# Check for mandatory violations (MUST be 0 for SIL 2+)
python3 tools/check_misra.py \
    --report evidence/static_analysis/cppcheck_report.xml \
    --sil 3 \
    --mandatory-only

# 2. Complexity check
lizard src/*.c -o evidence/complexity/lizard_report.txt

# Check for functions exceeding limit (CCN ≤ 10 for SIL 3-4)
python3 tools/check_complexity.py \
    --report evidence/complexity/lizard_report.txt \
    --sil 3 \
    --max-ccn 10

# 3. Unit test coverage
make test
gcov src/*.c
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_report

# Check coverage (100% required for SIL 3+)
python3 tools/check_coverage.py \
    --coverage coverage.info \
    --sil 3 \
    --statement 100 \
    --branch 100 \
    --condition 100
```

**If Any Pre-Review Check Fails**: Developer MUST fix issues before submitting for code review. Do NOT submit code that fails MISRA C mandatory, complexity, or coverage checks.

---

### Step 2: Code Review Submission

**Developer Action**:
```bash
# Submit code for review (after all automated checks PASS)
workspace.py wf submit \
    --deliverable src/door_controller.c \
    --phase implementation \
    --author "Dave Developer" \
    --version 1.0 \
    --comments "Door controller implementation complete. MISRA C compliant, CCN=8, coverage 100%"
```

**QA Action**:
1. Assign code reviewers (Peer Developer + QA)
2. Distribute code review checklist
3. Schedule code review meeting (or async review for small changes)

---

### Step 3: Code Review Execution

**Review Method**:
- **Formal Inspection** (SIL 3-4): In-person meeting, line-by-line review
- **Walkthrough** (SIL 2): Presentation by developer, reviewers ask questions
- **Desk Check** (SIL 0-1): Reviewers read code individually, provide comments

**Review Focus** (see [Code Review Checklist](#code-review-checklist)):
1. **MISRA C Compliance** (SIL 2+)
   - Zero mandatory violations (verify with Cppcheck report)
   - Required/advisory violations documented with rationale
   
2. **Complexity** (SIL-dependent)
   - SIL 3-4: CCN ≤ 10 (verify with Lizard report)
   - SIL 2: CCN ≤ 15
   - SIL 0-1: CCN ≤ 20
   
3. **Defensive Programming** (Highly Recommended SIL 2+, Mandatory SIL 3-4)
   - All pointers validated before use
   - All return values checked
   - Input parameters validated
   - Assertions for preconditions/postconditions
   - Error handling for all failure modes
   
4. **Static Allocation** (Mandatory SIL 2+)
   - No `malloc`, `calloc`, `realloc`, `free`
   - All arrays fixed-size
   
5. **No Recursion** (Highly Recommended SIL 3-4)
   
6. **Traceability** (Mandatory SIL 3-4)
   - Comments link code to design elements
   - All design elements implemented

**Code Review Meeting** (Formal Inspection - SIL 3-4):
```
1. Introduction (5 min)
   - Review purpose and scope
   - Checklist overview

2. Code Presentation (15 min)
   - Developer presents code structure
   - Key algorithms and design decisions
   - Traceability to design

3. Line-by-Line Review (60-90 min)
   - Reviewer 1 (Peer): Check correctness, edge cases, maintainability
   - Reviewer 2 (QUA): Check MISRA C, complexity, defensive programming
   - Log defects with line numbers and severity

4. Wrap-up (10 min)
   - Summarize defects
   - Determine outcome (Approved / Rework Required / Rejected)
```

---

### Step 4: Code Review Report Generation

**QA Action**: Generate Code Review Report

**Example Report**:
```markdown
# Code Review Report: door_controller.c

## Review Summary

| Field | Value |
|-------|-------|
| **Code Reviewed** | src/door_controller.c (v1.0, 450 LOC) |
| **Review Date** | 2026-03-25 |
| **Review Type** | Formal Inspection |
| **SIL Level** | 3 |
| **Reviewers** | Frank (Peer), Eve (QUA) |
| **Author** | Dave (IMP) |

## Review Outcome

**Outcome**: REWORK REQUIRED

**Rationale**: Code is generally well-structured and MISRA C compliant. However, 2 defects found related to defensive programming (NULL pointer check missing).

## Automated Check Results

| Check | Result | Details |
|-------|--------|---------|
| MISRA C Mandatory | PASS ✓ | 0 mandatory violations |
| MISRA C Required | PASS ✓ | 3 required violations, all documented with deviations |
| Cyclomatic Complexity | PASS ✓ | Max CCN = 8 (limit: 10) |
| Unit Test Coverage | PASS ✓ | Statement 100%, Branch 100%, Condition 100% |
| Static Allocation | PASS ✓ | No dynamic memory allocation |
| No Recursion | PASS ✓ | No recursive calls |

## Manual Review Results

### Defect 1: Missing NULL Pointer Check in door_set_state()
- **Severity**: CRITICAL
- **Found By**: Frank (Peer)
- **Location**: Line 125, door_controller.c
- **Issue**: Function `door_set_state()` does not check if `door` pointer is NULL before dereferencing
- **Code**:
  ```c
  void door_set_state(door_t* door, door_state_t state) {
      door->state = state;  // DEFECT: No NULL check
  }
  ```
- **Expected** (Defensive Programming):
  ```c
  void door_set_state(door_t* door, door_state_t state) {
      if (door == NULL) {
          handle_error(ERR_NULL_POINTER);
          return;
      }
      door->state = state;
  }
  ```
- **EN 50128 Reference**: Table A.3 Technique 8 (Defensive Programming) - MANDATORY SIL 3-4
- **Corrective Action**: Add NULL pointer check with error handling
- **Assigned To**: Dave (IMP)
- **Due Date**: 2026-03-26

### Defect 2: Unchecked Return Value from sensor_read()
- **Severity**: MAJOR
- **Found By**: Eve (QUA)
- **Location**: Line 178, door_controller.c
- **Issue**: Return value from `sensor_read()` not checked (may return error)
- **Code**:
  ```c
  sensor_value = sensor_read(DOOR_SENSOR_ID);  // DEFECT: Return not checked
  if (sensor_value > THRESHOLD) { ... }
  ```
- **Expected**:
  ```c
  error_t err = sensor_read(DOOR_SENSOR_ID, &sensor_value);
  if (err != SUCCESS) {
      handle_error(err);
      return;
  }
  if (sensor_value > THRESHOLD) { ... }
  ```
- **EN 50128 Reference**: Table A.3 Technique 8 (Defensive Programming)
- **Corrective Action**: Check return value and handle error
- **Assigned To**: Dave (IMP)
- **Due Date**: 2026-03-26

## Next Steps

1. Developer (Dave) fixes defects 1 and 2 by 2026-03-26
2. Developer updates code to v1.1
3. Developer re-runs automated checks (MISRA C, complexity, coverage)
4. Developer submits for re-review
5. QA performs desk check (no full meeting for 2 defects)
6. If approved, proceed to integration testing

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Code Reviewer (Peer)** | Frank Peer | | 2026-03-25 |
| **QA Manager** | Eve Green | | 2026-03-25 |
```

---

### Step 5: Code Rework and Re-Review

**Developer Action**:
1. Fix all defects
2. Re-run automated checks (MISRA C, complexity, coverage)
3. Update code version
4. Submit for re-review

**Re-Review** (Desk Check for ≤ 3 defects):
```bash
# Developer submits reworked code
workspace.py wf submit \
    --deliverable src/door_controller.c \
    --phase implementation \
    --author "Dave Developer" \
    --version 1.1 \
    --comments "Fixed code review defects: added NULL checks, checked sensor_read() return"

# QA desk check
# - Review changes (git diff v1.0 v1.1)
# - Verify defects fixed
# - Re-run automated checks

# QA approves
workspace.py wf review \
    --deliverable src/door_controller.c \
    --reviewer QUA \
    --status approved \
    --comments "All code review defects fixed. Code approved for integration. Proceed to integration testing."
```

---

## Test Review Process

### Step 1: Test Review Preparation

**Trigger**: Test plan/specification complete, or test execution complete

**Review Types**:
1. **Test Plan Review**: Review test strategy, test cases, coverage plan (BEFORE testing)
2. **Test Specification Review**: Review test case design, expected results (BEFORE testing)
3. **Test Report Review**: Review test results, coverage achieved, defects found (AFTER testing)

**Test Plan Review Focus**:
- Are all requirements covered by test cases (traceability)?
- Is coverage adequate for SIL level (statement, branch, condition)?
- Are test methods appropriate (black-box, white-box, boundary value)?
- Are test resources identified (test harness, test environment)?

---

### Step 2: Test Plan Review Meeting

**Participants**: TST (author), REQ, VER, QUA

**Agenda**:
1. **Test Strategy Presentation** (15 min):
   - Test levels (unit, integration, system)
   - Test methods (functional, performance, stress)
   - Coverage requirements (SIL-specific)

2. **Test Case Review** (60 min):
   - Traceability matrix (test cases → requirements)
   - Test case design (inputs, expected outputs, pass/fail criteria)
   - Boundary value analysis, equivalence classes

3. **Coverage Review** (30 min):
   - Statement coverage plan (100% for SIL 3+)
   - Branch coverage plan (100% for SIL 3+)
   - Condition coverage plan (100% for SIL 3+, MANDATORY)
   - MC/DC coverage plan (if applicable)

4. **Test Environment Review** (15 min):
   - Test harness (Unity, CUnit)
   - Target environment (on-target vs. simulation)
   - Test data and test fixtures

5. **Defect Discussion and Approval**

---

### Step 3: Test Report Review

**Trigger**: Test execution complete, test report generated

**Review Focus**:
- Are all test cases executed?
- Are test results documented with evidence (logs, screenshots)?
- Is coverage achieved (statement, branch, condition)?
- Are defects logged and tracked?
- Are failed tests explained and retested?

**Test Report Review Process**:
```bash
# Tester submits test report
workspace.py wf submit \
    --deliverable DOC-TST-REP-001 \
    --phase testing \
    --author "Tom Tester" \
    --version 1.0

# QA document review (template compliance)
python3 tools/document_checker.py \
    --document docs/DOC-TST-REP-001.md \
    --sil 3 \
    --output evidence/qa/doc_review_DOC-TST-REP-001.json

# QA technical review (coverage, traceability)
# Check coverage results
python3 tools/check_coverage.py \
    --coverage coverage.info \
    --sil 3 \
    --statement 100 \
    --branch 100 \
    --condition 100

# Validate traceability (tests → requirements)
workspace.py trace validate --phase testing --sil 3

# If PASS:
workspace.py wf review \
    --deliverable DOC-TST-REP-001 \
    --reviewer QUA \
    --status approved \
    --comments "Test report approved. Coverage 100% (statement, branch, condition). Traceability 100%. All tests passed. Proceed to integration."
```

---

## Review Meeting Management

### Review Meeting Roles

| Role | Responsibilities |
|------|-----------------|
| **Moderator (QA)** | Facilitate meeting, keep on schedule, ensure all checklist items covered |
| **Author (DEV)** | Present artifact, explain design decisions, answer questions |
| **Reviewers (SMEs)** | Identify defects, ask questions, provide expertise |
| **Scribe (QA)** | Log defects, action items, decisions |

---

### Review Meeting Best Practices

**Before Meeting**:
- ✓ Distribute materials at least 3 days in advance
- ✓ Provide checklist to reviewers
- ✓ Ensure reviewers have time to prepare (pre-review)
- ✓ Set clear objectives and scope

**During Meeting**:
- ✓ Stay focused on artifact (not solutions)
- ✓ Log defects, don't fix in meeting (fixing is author's responsibility)
- ✓ Use severity classification (Critical, Major, Minor)
- ✓ Keep to time limit (2-4 hours max, schedule additional meeting if needed)
- ✓ Ensure all reviewers participate

**After Meeting**:
- ✓ Generate review report within 2 business days
- ✓ Assign corrective actions with due dates
- ✓ Track defect resolution
- ✓ Schedule re-review if needed

---

### Review Meeting Automation

**Meeting Management Script**: `tools/review_meeting.py`

**Usage**:
```bash
# Create review meeting
python3 tools/review_meeting.py create \
    --meeting-id RVW-2026-025 \
    --type design \
    --artifact DOC-DES-SAS-001 \
    --date 2026-03-20 \
    --participants "Alice(DES),Bob(REQ),Carol(SAF),Dave(IMP),Eve(QUA)" \
    --output evidence/reviews/meeting_RVW-2026-025.json

# Log defect during meeting
python3 tools/review_meeting.py log-defect \
    --meeting-id RVW-2026-025 \
    --severity CRITICAL \
    --found-by Carol \
    --location "Section 4.3" \
    --issue "Missing safety interlock" \
    --action "Add redundant channels with voting"

# Generate meeting report
python3 tools/review_meeting.py report \
    --meeting-id RVW-2026-025 \
    --output docs/DOC-QUA-REVIEW-025.md
```

---

## Defect Management

### Defect Severity Classification

| Severity | Definition | Examples | Resolution Priority |
|----------|-----------|----------|-------------------|
| **CRITICAL** | Safety impact, functional failure, EN 50128 mandatory violation | - Missing safety interlock<br>- MISRA C mandatory violation<br>- NULL pointer not checked | **MUST FIX** before approval |
| **MAJOR** | Quality issue, may cause failure, EN 50128 highly recommended violation | - Complexity exceeds limit<br>- Traceability gap<br>- Missing error handling | **SHOULD FIX** before approval (may defer with justification) |
| **MINOR** | Improvement, maintainability, EN 50128 recommended violation | - Missing comments<br>- Inconsistent naming<br>- Incomplete documentation | **MAY DEFER** to backlog |

---

### Defect Resolution Workflow

```
Defect logged during review
          ↓
Defect assigned to developer with due date
          ↓
Developer fixes defect
          ↓
Developer updates artifact version
          ↓
Developer submits for re-review
          ↓
QA/Reviewer verifies fix
    ├─→ [FIXED] → Close defect, mark as resolved
    └─→ [NOT FIXED] → Re-assign to developer, escalate if repeated
          ↓
All defects resolved → Approve artifact
```

**Defect Tracking**:
```bash
# Log defect
workspace.py wf log-defect \
    --deliverable DOC-DES-SAS-001 \
    --defect-id DEF-2026-125 \
    --severity CRITICAL \
    --description "Missing safety interlock in emergency stop module" \
    --assigned-to "Alice Designer" \
    --due-date 2026-03-25

# Update defect status
workspace.py wf update-defect \
    --defect-id DEF-2026-125 \
    --status resolved \
    --resolution "Added redundant emergency stop channels with 2oo3 voting logic"

# List open defects for deliverable
workspace.py wf list-defects \
    --deliverable DOC-DES-SAS-001 \
    --status open
```

---

## Review Checklists

### Requirements Review Checklist

**EN 50128 Reference**: Section 7.2 (Software Requirements Specification), Table A.2

**Checklist Items**:

#### 1. Requirements Quality
- [ ] Are all requirements unambiguous (no "etc.", "and/or", "TBD")?
- [ ] Are all requirements testable (can be verified)?
- [ ] Are all requirements atomic (one requirement per ID)?
- [ ] Are all requirements necessary (no gold-plating)?
- [ ] Are SHALL/SHOULD/MAY keywords used correctly (RFC 2119)?

#### 2. Requirements Completeness
- [ ] Are all system requirements addressed?
- [ ] Are safety requirements identified and marked?
- [ ] Are interface requirements specified?
- [ ] Are performance requirements specified?
- [ ] Are error handling requirements specified?

#### 3. Requirements Traceability
- [ ] Is each requirement traceable to system requirement (backward)?
- [ ] Does each system requirement have at least one software requirement (forward)?
- [ ] Are requirement IDs unique (REQ-XXX-NNN format)?

#### 4. SIL Level Assignment
- [ ] Is SIL level assigned to each requirement?
- [ ] Are safety-critical requirements marked as SIL 3 or SIL 4?
- [ ] Are non-safety requirements appropriately classified (SIL 0-2)?

#### 5. Requirements Consistency
- [ ] Are requirements consistent (no conflicts)?
- [ ] Are requirements feasible (can be implemented in C with static allocation)?
- [ ] Are requirements verifiable (test method identified)?

---

### Design Review Checklist

**EN 50128 Reference**: Section 7.3 (Software Architecture and Design), Table A.3

**Checklist Items**:

#### 1. Modularity (MANDATORY SIL 2+)
- [ ] Is design modular with clear module responsibilities?
- [ ] Are module interfaces well-defined (inputs, outputs, errors)?
- [ ] Is information encapsulation used (data hiding)?
- [ ] Are module dependencies minimized (low coupling)?
- [ ] Are modules cohesive (high cohesion)?

#### 2. Complexity (SIL-dependent)
- [ ] Is cyclomatic complexity estimated for each module?
- [ ] SIL 3-4: Is CCN ≤ 10 for all modules?
- [ ] SIL 2: Is CCN ≤ 15 for all modules?
- [ ] SIL 0-1: Is CCN ≤ 20 for all modules?
- [ ] Are overly complex modules split into simpler modules?

#### 3. Defensive Programming (HR for SIL 2+, M for SIL 3-4)
- [ ] Are input validation mechanisms designed (range checks, NULL checks)?
- [ ] Are error handling mechanisms designed (return codes, error states)?
- [ ] Are assertions planned for preconditions/postconditions?
- [ ] Are fault detection mechanisms designed (watchdog, voting)?

#### 4. Static Allocation (MANDATORY SIL 2+)
- [ ] Are all data structures statically allocated (no dynamic memory)?
- [ ] Are all array sizes fixed and known at compile time?
- [ ] Are buffer sizes adequate for worst-case scenarios?

#### 5. No Recursion (HR for SIL 3-4)
- [ ] Is recursion avoided in all modules?
- [ ] If recursion used (exception), is rationale documented and recursion depth bounded?

#### 6. Traceability (MANDATORY SIL 3-4)
- [ ] Is each design element traceable to at least one requirement?
- [ ] Are all requirements addressed by at least one design element?
- [ ] Is traceability matrix complete (100% coverage)?

#### 7. Safety Design Patterns (SIL 2+)
- [ ] Are safety mechanisms designed (redundancy, voting, watchdog)?
- [ ] Are fail-safe states defined?
- [ ] Are common cause failures addressed?

---

### Code Review Checklist

**EN 50128 Reference**: Section 7.4 (Software Implementation), Table A.4

**Checklist Items**:

#### 1. MISRA C Compliance (MANDATORY SIL 2+)
- [ ] Static analysis performed (Cppcheck, PC-lint, Clang)?
- [ ] MISRA C mandatory violations = 0 (MANDATORY SIL 2+)?
- [ ] MISRA C required violations documented with deviations?
- [ ] MISRA C advisory violations reviewed and justified?

**Critical MISRA C Rules** (MANDATORY SIL 2+):
- **Rule 1.3**: No undefined behavior
- **Rule 2.1**: No unreachable code
- **Rule 9.1**: All variables initialized before use
- **Rule 14.1**: No unreachable code
- **Rule 17.7**: Return value of non-void function must be used
- **Rule 21.3**: No dynamic memory allocation (malloc, calloc, realloc, free)

#### 2. Cyclomatic Complexity (SIL-dependent)
- [ ] Complexity analysis performed (Lizard, McCabe)?
- [ ] SIL 3-4: All functions CCN ≤ 10?
- [ ] SIL 2: All functions CCN ≤ 15?
- [ ] SIL 0-1: All functions CCN ≤ 20?

#### 3. Defensive Programming (HR for SIL 2+, M for SIL 3-4)
- [ ] All pointers checked for NULL before dereferencing?
- [ ] All return values checked (error codes)?
- [ ] All input parameters validated (range, NULL, bounds)?
- [ ] All array accesses bounds-checked?
- [ ] Assertions used for preconditions/postconditions?
- [ ] Error handling for all failure modes?

**Example (Correct Defensive Programming)**:
```c
error_t door_set_state(door_t* door, door_state_t state) {
    // 1. Check pointer parameter
    if (door == NULL) {
        return ERR_NULL_POINTER;
    }
    
    // 2. Validate enum parameter
    if (state != DOOR_OPEN && state != DOOR_CLOSED && state != DOOR_MOVING) {
        return ERR_INVALID_STATE;
    }
    
    // 3. Precondition assertion
    assert(door->magic == DOOR_MAGIC);
    
    // 4. Perform operation
    door->state = state;
    
    // 5. Postcondition check
    if (door->state != state) {
        return ERR_STATE_MISMATCH;
    }
    
    return SUCCESS;
}
```

#### 4. Static Allocation (MANDATORY SIL 2+)
- [ ] No dynamic memory allocation (malloc, calloc, realloc, free)?
- [ ] All arrays fixed-size and statically allocated?
- [ ] All data structures declared static or global (no VLAs)?

#### 5. No Recursion (HR for SIL 3-4)
- [ ] No recursive function calls?
- [ ] If recursion used (exception), is depth bounded and justified?

#### 6. Traceability (MANDATORY SIL 3-4)
- [ ] Are functions/modules linked to design elements (comments)?
- [ ] Are all design elements implemented?
- [ ] Are all requirements addressed (via design → code traceability)?

#### 7. Code Quality
- [ ] Are variable names meaningful (not single letters)?
- [ ] Are magic numbers avoided (use constants or enums)?
- [ ] Are comments adequate (explain WHY, not WHAT)?
- [ ] Is code formatted consistently (indentation, braces)?

---

### Test Review Checklist

**EN 50128 Reference**: Sections 7.4, 7.5, 7.7 (Testing), Table A.5, Table A.21

**Checklist Items**:

#### 1. Test Coverage (SIL-dependent)
- [ ] SIL 3-4: Statement coverage = 100% (MANDATORY)?
- [ ] SIL 3-4: Branch coverage = 100% (MANDATORY)?
- [ ] SIL 3-4: Condition coverage = 100% (MANDATORY)?
- [ ] SIL 2: Branch coverage ≥ 95% (MANDATORY)?
- [ ] SIL 0-1: Statement coverage ≥ 80% (recommended)?

#### 2. Traceability (MANDATORY SIL 3-4)
- [ ] Is each requirement covered by at least one test case?
- [ ] Is traceability matrix complete (tests → requirements)?
- [ ] Are all test cases linked to requirements?

#### 3. Test Case Design
- [ ] Are boundary values tested (min, max, min-1, max+1)?
- [ ] Are equivalence classes identified and tested?
- [ ] Are error conditions tested (invalid inputs, failure modes)?
- [ ] Are pass/fail criteria clearly defined?

#### 4. Test Results
- [ ] Are all test cases executed?
- [ ] Are test results documented (pass/fail, actual vs. expected)?
- [ ] Are test logs and evidence provided?
- [ ] Are failed tests explained and retested?

#### 5. Test Environment
- [ ] Is test environment documented (tools, version, configuration)?
- [ ] Is test reproducible (test data and fixtures documented)?
- [ ] Is test performed on target hardware (or justified simulation)?

---

## Automated Technical Checks

### MISRA C Compliance Check

**Tool**: Cppcheck with MISRA addon

**Usage**:
```bash
# Run Cppcheck with MISRA C:2012 addon
cppcheck --enable=all \
    --addon=/usr/share/cppcheck/addons/misra.py \
    --suppress=missingIncludeSystem \
    --xml --xml-version=2 \
    src/*.c 2> evidence/static_analysis/cppcheck_report.xml

# Check for mandatory violations (MUST be 0 for SIL 2+)
python3 tools/check_misra.py \
    --report evidence/static_analysis/cppcheck_report.xml \
    --sil 3 \
    --mandatory-only

# Output:
# MISRA C Compliance Check: PASS
# Mandatory violations: 0
# Required violations: 3 (deviations documented)
# Advisory violations: 12 (reviewed)
```

---

### Complexity Analysis

**Tool**: Lizard

**Usage**:
```bash
# Run Lizard complexity analysis
lizard src/*.c -o evidence/complexity/lizard_report.txt

# Check for functions exceeding limit
python3 tools/check_complexity.py \
    --report evidence/complexity/lizard_report.txt \
    --sil 3 \
    --max-ccn 10

# Output:
# Complexity Check: PASS
# Functions analyzed: 25
# Functions within limit (CCN ≤ 10): 25
# Functions exceeding limit: 0
# Max complexity: 8 (door_emergency_stop)
```

---

### Coverage Analysis

**Tool**: gcov, lcov

**Usage**:
```bash
# Run unit tests with coverage
make test

# Generate coverage report
gcov src/*.c
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_report

# Check coverage (SIL 3 requires 100%)
python3 tools/check_coverage.py \
    --coverage coverage.info \
    --sil 3 \
    --statement 100 \
    --branch 100 \
    --condition 100

# Output:
# Coverage Check: PASS
# Statement coverage: 100.0% (450/450 lines)
# Branch coverage: 100.0% (120/120 branches)
# Condition coverage: 100.0% (80/80 conditions)
```

---

## Tool Integration

### Workflow Integration

**Submit for Technical Review**:
```bash
# After QA document review approval
workspace.py wf submit \
    --deliverable DOC-DES-SAS-001 \
    --phase design \
    --author "Alice Designer" \
    --version 1.0 \
    --comments "Software Architecture Specification complete. Ready for technical review."
```

**Technical Review Approval**:
```bash
workspace.py wf review \
    --deliverable DOC-DES-SAS-001 \
    --reviewer QUA \
    --status approved \
    --comments "Technical review complete. Design approved with minor revisions (see review report DOC-QUA-REVIEW-025). Proceed to detailed design."
```

**Technical Review Rejection**:
```bash
workspace.py wf review \
    --deliverable DOC-DES-SAS-001 \
    --reviewer QUA \
    --status rejected \
    --comments "Technical review failed. 3 defects found (1 Critical, 2 Major). Fix and resubmit. See review report DOC-QUA-REVIEW-025."
```

---

### Traceability Validation During Review

**Validate Traceability**:
```bash
# Check design → requirements traceability
workspace.py trace validate \
    --phase design \
    --sil 3

# Output:
# Traceability Validation: PASS
# Coverage: 100% (40/40 requirements traced)
# Orphan requirements: 0
# Orphan design elements: 0
```

**Generate Traceability Report for Review**:
```bash
workspace.py trace report \
    --from design --to requirements \
    --format markdown \
    --output evidence/traceability/design-to-requirements.md
```

---

## SIL-Specific Requirements

### Technical Review Requirements by SIL

| Requirement | SIL 0-1 | SIL 2 | SIL 3-4 |
|------------|---------|-------|---------|
| **Technical Review** | Recommended | Highly Recommended | **MANDATORY** |
| **Independent Reviewers** | Optional | Recommended | **MANDATORY** |
| **MISRA C Compliance Check** | Optional | **MANDATORY** | **MANDATORY** |
| **Complexity Check** | Recommended | **MANDATORY** | **MANDATORY** |
| **Coverage Check** | Recommended | Highly Recommended | **MANDATORY** |
| **Defensive Programming Check** | Recommended | Highly Recommended | **MANDATORY** |
| **Review Report Generation** | Recommended | Highly Recommended | **MANDATORY** |
| **Defect Tracking** | Recommended | Highly Recommended | **MANDATORY** |

---

### SIL 3-4 Specific Requirements

**Independence** (EN 50128 Section 5.1.2.10):
- At least one reviewer MUST be independent of development team
- QUA always independent (reports to QA Manager, not PM)
- VER independent for verification reviews
- VAL independent for validation reviews

**MISRA C Compliance** (MANDATORY SIL 2+):
- Zero mandatory violations (MANDATORY)
- Required violations documented with deviations
- Advisory violations reviewed

**Complexity Limits** (MANDATORY SIL 3-4):
- CCN ≤ 10 for all functions (MANDATORY)
- No exceptions without documented rationale and approval

**Defensive Programming** (MANDATORY SIL 3-4):
- All pointers checked before use
- All return values checked
- All inputs validated
- Assertions for preconditions/postconditions

**Coverage** (MANDATORY SIL 3-4):
- Statement coverage = 100%
- Branch coverage = 100%
- Condition coverage = 100% (MC/DC for safety-critical)

---

## Example Technical Review Scenarios

### Scenario 1: Design Review - Missing Safety Redundancy (REJECT)

**Context**: SIL 3 railway door controller, architecture review

**Review Meeting**: 2026-03-20

**Participants**: Alice (DES - author), Bob (REQ), Carol (SAF), Dave (IMP), Eve (QUA)

**Issue Found**: Emergency stop module does not include redundancy (2oo3 voting)

**Defect**:
- **Severity**: CRITICAL
- **Found By**: Carol (SAF)
- **Location**: Section 4.3 (Emergency Stop Module)
- **Issue**: EN 50128 SIL 3 requires redundancy for safety-critical functions. Emergency stop module has single channel (no redundancy).
- **EN 50128 Reference**: Table A.3 Technique 11 (Fault Detection & Diagnosis) - Highly Recommended SIL 3
- **Corrective Action**: Add redundant emergency stop channels with 2oo3 voting logic

**Review Outcome**: REWORK REQUIRED (1 Critical defect)

**Designer Action**:
1. Redesign emergency stop module with 3 channels and voting logic
2. Update SAS document (Section 4.3)
3. Update traceability (link to safety requirement REQ-SAFETY-005)
4. Submit for re-review

**Re-Review**: Desk check by SAF and QUA → APPROVED

---

### Scenario 2: Code Review - MISRA C Mandatory Violation (REJECT)

**Context**: SIL 3 speed controller, code review for `speed_limiter.c`

**Review**: Formal inspection, 2026-03-28

**Automated Check Result**: MISRA C mandatory violation found

**Issue**:
- **Rule 21.3**: Dynamic memory allocation used (malloc in speed_limiter.c line 85)
- **Severity**: CRITICAL (MANDATORY violation for SIL 3)
- **Code**:
  ```c
  speed_data_t* data = malloc(sizeof(speed_data_t));  // VIOLATION
  ```
- **Expected** (Static Allocation):
  ```c
  static speed_data_t data;  // Static allocation (SIL 2+)
  ```

**Review Outcome**: REJECTED (MANDATORY MISRA C violation)

**Developer Action**:
1. Replace `malloc` with static allocation
2. Re-run Cppcheck → 0 mandatory violations
3. Submit for re-review

**Re-Review**: Desk check by QUA → APPROVED

---

### Scenario 3: Code Review - Defensive Programming Issue (REWORK)

**Context**: SIL 3 brake controller, code review for `brake_controller.c`

**Review**: Formal inspection, 2026-04-02

**Issue Found**: Missing NULL pointer check

**Defect**:
- **Severity**: CRITICAL
- **Found By**: Frank (Peer)
- **Location**: Line 125, brake_controller.c
- **Code**:
  ```c
  void brake_apply(brake_t* brake, uint8_t force) {
      brake->applied_force = force;  // DEFECT: No NULL check
  }
  ```
- **Expected**:
  ```c
  void brake_apply(brake_t* brake, uint8_t force) {
      if (brake == NULL) {
          handle_error(ERR_NULL_POINTER);
          return;
      }
      if (force > MAX_BRAKE_FORCE) {
          handle_error(ERR_INVALID_FORCE);
          return;
      }
      brake->applied_force = force;
  }
  ```

**Review Outcome**: REWORK REQUIRED (1 Critical defect)

**Developer Action**: Add NULL check and input validation → Re-review → APPROVED

---

### Scenario 4: Test Review - Coverage Incomplete (REJECT)

**Context**: SIL 3 door controller, test report review

**Review**: 2026-04-10

**Issue Found**: Branch coverage 95% (100% required for SIL 3)

**Coverage Check**:
```bash
python3 tools/check_coverage.py \
    --coverage coverage.info \
    --sil 3 \
    --statement 100 \
    --branch 100 \
    --condition 100

# Output:
# Coverage Check: FAIL
# Statement coverage: 100.0% ✓
# Branch coverage: 95.0% ✗ (required: 100%)
# Condition coverage: 100.0% ✓
# Uncovered branches: 6 in door_error_handler()
```

**Review Outcome**: REJECTED (Coverage requirement not met)

**Tester Action**:
1. Add tests for uncovered branches in `door_error_handler()`
2. Re-run tests, achieve 100% branch coverage
3. Submit for re-review

**Re-Review**: Coverage check → 100% → APPROVED

---

## 13. References

- EN 50128:2011 Section 6.5 (Software Quality Assurance)
- EN 50128:2011 Table A.3 (Software Architecture and Design Techniques)
- EN 50128:2011 Table A.4 (Software Design and Implementation Techniques)
- EN 50128:2011 Table A.5 (Verification and Testing Techniques)
- EN 50128:2011 Table A.19 (Static Analysis Techniques)
- EN 50128:2011 Table A.21 (Test Coverage for Code)
- MISRA C:2012 (Guidelines for the Use of C in Critical Systems)
- IEEE 1028-2008 (Standard for Software Reviews and Audits)
