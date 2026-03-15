# Code Review Workflow

**Skill**: en50128-implementation  
**Role**: Quality Assurance (QUA), Verifier (VER), Implementer (IMP)  
**Phase**: Implementation & Testing (Phase 4)  
**EN 50128 Reference**: Section 6.5 (Software Quality Assurance), Table A.9

---

## Purpose

This workflow guides the code review process for C implementations in EN 50128 railway safety software. Code review is **Mandatory** for all SIL levels and is a key quality assurance technique per EN 50128 Section 6.5.

**Key Objectives**:
- Verify code correctness and completeness
- Ensure MISRA C:2012 compliance (SIL 3-4)
- Validate defensive programming implementation
- Check complexity within limits
- Verify traceability to design
- Identify defects before integration

**Review Requirements by SIL**:
- **SIL 0-2**: Peer review + QUA review (2 reviewers minimum)
- **SIL 3-4**: Peer review + QUA review + VER review (3 reviewers minimum, independent VER)

---

## Prerequisites

### Required Inputs
- [ ] Source code implementation (.c and .h files) - COMPLETE
- [ ] Unit test code and results - ALL TESTS PASSING
- [ ] Software Design Specification (DOC-10) - APPROVED
- [ ] Static analysis results (Cppcheck, PC-lint)
- [ ] Complexity analysis results (Lizard)
- [ ] Coverage reports (100% for SIL 3-4)

### Required Tools
```bash
# Verify analysis tools
which cppcheck && cppcheck --version
which lizard && lizard --version
which lcov && lcov --version

# Check review documentation
ls docs/reviews/
ls .opencode/skills/en50128-quality/templates/Code-Review-Checklist-template.md
```

---

## Review Roles and Responsibilities

### 1. Author (IMP - Implementer)
**Responsibilities**:
- Prepare code for review
- Run static analysis and fix violations
- Verify unit tests pass with 100% coverage
- Create self-review checklist
- Address review comments

**Cannot**:
- Approve own code
- Skip review process

### 2. Peer Reviewer (IMP - Another Implementer)
**Responsibilities**:
- Review code logic and correctness
- Check design implementation
- Verify coding standards followed
- Test code locally
- Provide constructive feedback

**Independence**: Should NOT be the author

### 3. QA Reviewer (QUA - Quality Assurance)
**Responsibilities**:
- Verify MISRA C compliance
- Check complexity within limits
- Validate defensive programming
- Review test coverage
- Enforce quality gates
- Final approval for SIL 0-2

**Independence**: Independent from development team

### 4. Verifier (VER - SIL 3-4 Only)
**Responsibilities**:
- Independent verification
- Traceability verification
- Safety-critical code analysis
- Final technical approval for SIL 3-4

**Independence**: **MANDATORY** - Cannot be Author, Peer, or report to same manager

---

## Step 1: Author Self-Review

### 1.1 Pre-Review Checklist

**Author MUST complete before submitting for review**:

```markdown
# Self-Review Checklist - brake_controller.c

## Author: [Name]
## Date: 2026-03-13
## Module: brake_controller
## SIL Level: 3

### Compilation
- [x] Code compiles without errors
- [x] Code compiles without warnings (-Wall -Wextra -Werror)
- [x] No compiler optimization warnings

### Static Analysis
- [x] Cppcheck: 0 errors, 0 warnings
- [x] MISRA C violations: 0 mandatory, 0 required, 0 advisory
- [x] Complexity: All functions ≤ 10 CCN (SIL 3)

### Testing
- [x] All unit tests pass (10/10)
- [x] Statement coverage: 100%
- [x] Branch coverage: 100%
- [x] Condition coverage: 100%

### Code Quality
- [x] All functions have Doxygen comments
- [x] All parameters documented
- [x] All return values documented
- [x] No dead code
- [x] No commented-out code
- [x] Consistent formatting

### MISRA C (SIL 3-4)
- [x] No dynamic memory allocation
- [x] Fixed-width types used (uint8_t, uint16_t, etc.)
- [x] All pointers checked for NULL
- [x] All return values checked
- [x] Explicit type casts
- [x] No recursion

### Defensive Programming
- [x] Input validation at module boundaries
- [x] Range checks on all inputs
- [x] Error handling comprehensive
- [x] Safe arithmetic (overflow checks)
- [x] Bounded loops (no infinite loops)

### Traceability
- [x] Design items implemented
- [x] Traceability comments in code
- [x] Requirements traced to functions

### Ready for Review: YES
```

### 1.2 Generate Analysis Reports

```bash
# Create review package directory
mkdir -p docs/reviews/brake_controller_rev1

# Static analysis
cppcheck --enable=all --xml --xml-version=2 \
    src/brake_controller.c \
    2> docs/reviews/brake_controller_rev1/cppcheck.xml

# Complexity analysis
lizard src/brake_controller.c \
    -o docs/reviews/brake_controller_rev1/complexity.html

# Coverage report
cp -r coverage/html docs/reviews/brake_controller_rev1/coverage

# MISRA C report (if PC-lint available)
pclp64 std.lnt src/brake_controller.c \
    > docs/reviews/brake_controller_rev1/misra.txt
```

### 1.3 Submit for Review

```bash
# Create review request
python3 tools/workspace.py workflow submit \
    --document src/brake_controller.c \
    --for-review \
    --reviewers PEER,QUA,VER \
    --sil 3 \
    --notes "Ready for code review - all self-checks passed"

# Output:
# Review request created: REV-BRAKE-001
# Status: Pending Peer Review
# Assigned to: john.doe@example.com (PEER)
```

---

## Step 2: Peer Review

### 2.1 Review Focus Areas

**Peer reviewer checks**:
1. **Logic Correctness**: Does the code implement the design correctly?
2. **Algorithm Efficiency**: Are algorithms appropriate?
3. **Edge Cases**: Are boundary conditions handled?
4. **Error Handling**: Are all errors caught and handled?
5. **Readability**: Is code clear and maintainable?

### 2.2 Peer Review Checklist

```markdown
# Peer Review - brake_controller.c

## Reviewer: John Doe (PEER)
## Date: 2026-03-13
## Review ID: REV-BRAKE-001

### 1. Design Implementation
- [x] Code matches design specification (DOC-10 MOD-001)
- [x] All required functions implemented
- [x] Function signatures match design
- [x] Interfaces correctly implemented

**Comments**: All design elements correctly implemented.

### 2. Logic and Correctness
- [x] Algorithms implemented correctly
- [x] Calculations verified
- [x] State machine logic correct (if applicable)
- [x] Boolean logic correct

**Comments**: Brake level calculation verified manually.

### 3. Error Handling
- [x] All error conditions identified
- [x] All error paths tested
- [x] Error codes appropriate
- [x] Error logging comprehensive

**Comments**: Comprehensive error handling observed.

### 4. Input Validation
- [x] NULL pointer checks present
- [x] Range validation present
- [x] Plausibility checks present
- [x] Array bounds checked

**Comments**: All inputs validated at module boundary.

### 5. Code Clarity
- [x] Variable names meaningful
- [x] Function names descriptive
- [x] Comments helpful (not redundant)
- [x] Code structure logical

**Comments**: Code is clear and well-structured.

### 6. Potential Issues
- [ ] Issue 1: Line 145 - Consider adding assertion for internal consistency
- [ ] Issue 2: None

### 7. Suggestions
- Suggestion 1: Consider extracting magic number 2 into named constant BRAKE_COEFFICIENT

### Overall Assessment: APPROVE with minor suggestions

**Signature**: John Doe, 2026-03-13
```

### 2.3 Peer Review Workflow

```bash
# Peer reviewer: Approve with comments
python3 tools/workspace.py workflow review \
    --review-id REV-BRAKE-001 \
    --reviewer PEER \
    --decision approve \
    --comments-file peer_review_comments.md

# Status updated: Pending QA Review
```

---

## Step 3: QA Review

### 3.1 QA Review Focus

**QA reviewer checks**:
1. **MISRA C Compliance**: Zero mandatory violations (SIL 3-4)
2. **Complexity**: Within limits (CCN ≤ 10 for SIL 3-4)
3. **Coverage**: 100% statement, branch, condition (SIL 3-4)
4. **Defensive Programming**: All patterns implemented
5. **Documentation**: Complete and accurate
6. **Process Compliance**: All steps followed

### 3.2 QA Review Checklist

**Use comprehensive checklist** from `../resources/code-review-checklist.md`.

```markdown
# QA Review - brake_controller.c

## Reviewer: Jane Smith (QUA)
## Date: 2026-03-14
## Review ID: REV-BRAKE-001
## SIL Level: 3

### A. MISRA C:2012 Compliance (MANDATORY SIL 3-4)

#### A.1 Mandatory Rules
- [x] Rule 1.3: No undefined behavior
- [x] Rule 2.1: No unreachable code
- [x] Rule 2.2: No dead code
- [x] Rule 8.1: Types explicitly declared
- [x] Rule 9.1: All variables initialized
- [x] Rule 21.3: No malloc/free (MANDATORY SIL 2+)

**Cppcheck Results**: 0 mandatory violations ✅

#### A.2 Required Rules
- [x] All required rules complied or deviated with justification

**Deviations**: None

#### A.3 Advisory Rules
- [x] Advisory rules followed where practical

**Advisory Violations**: 0

### B. Complexity Analysis (MANDATORY SIL 3-4)

| Function | CCN | Limit (SIL 3) | Status |
|----------|-----|---------------|--------|
| brake_init | 3 | ≤ 10 | ✅ PASS |
| brake_apply | 4 | ≤ 10 | ✅ PASS |
| brake_emergency | 3 | ≤ 10 | ✅ PASS |
| validate_speed | 2 | ≤ 10 | ✅ PASS |
| calculate_brake_level | 4 | ≤ 10 | ✅ PASS |
| transition_mode | 6 | ≤ 10 | ✅ PASS |

**Max CCN**: 6 (PASS - within limit of 10) ✅

### C. Test Coverage (MANDATORY SIL 3-4)

| Metric | Target | Actual | Status |
|--------|--------|--------|--------|
| Statement Coverage | 100% | 100% (50/50) | ✅ PASS |
| Branch Coverage | 100% | 100% (20/20) | ✅ PASS |
| Condition Coverage | 100% | 100% | ✅ PASS |
| Function Coverage | 100% | 100% (6/6) | ✅ PASS |

**Unit Tests**: 10/10 passed ✅

### D. Defensive Programming (HR SIL 3-4)

- [x] All pointer parameters checked for NULL
- [x] All numeric inputs range-validated
- [x] All return values checked by callers
- [x] Integer overflow detection implemented
- [x] Division by zero protection implemented
- [x] Bounded loops (no infinite loops)
- [x] Safe state entry on critical errors

**Assessment**: Comprehensive defensive programming ✅

### E. Code Quality

#### E.1 Documentation
- [x] All functions have Doxygen comments
- [x] All parameters documented with @param
- [x] All return values documented with @return
- [x] Preconditions documented with @pre
- [x] Postconditions documented with @post
- [x] Complexity documented with @note

#### E.2 Naming Conventions
- [x] Functions: lower_case with module prefix
- [x] Variables: lower_case
- [x] Constants: UPPER_CASE
- [x] Types: lower_case_t suffix

#### E.3 Code Structure
- [x] Header guards present
- [x] Include order correct
- [x] Static functions used appropriately
- [x] No global variables (or justified)

### F. Traceability

- [x] Design items traced (DOC-10 MOD-001)
- [x] Requirements traced (DOC-6 REQ-FUNC-012)
- [x] Test cases traced (DOC-16 TEST-BRAKE-001)
- [x] Traceability comments in code

**Traceability**: Complete ✅

### G. Issues Found

**Critical Issues**: 0
**Major Issues**: 0
**Minor Issues**: 1

#### Minor Issue 1: Magic Number
- **Location**: Line 145
- **Description**: Magic number '2' used for BRAKE_COEFF
- **Recommendation**: Extract to named constant
- **Severity**: Minor
- **Required Action**: Optional improvement

### H. Overall Assessment

**Decision**: ✅ **APPROVE with minor suggestion**

**Rationale**:
- Zero MISRA C mandatory violations
- All complexity within limits (max 6, limit 10)
- 100% test coverage achieved
- Comprehensive defensive programming
- Complete traceability
- One minor suggestion (non-blocking)

**Recommendation**: Proceed to VER review (SIL 3)

**Signature**: Jane Smith (QUA), 2026-03-14
```

### 3.3 QA Review Workflow

```bash
# QA reviewer: Approve with minor comments
python3 tools/workspace.py workflow review \
    --review-id REV-BRAKE-001 \
    --reviewer QUA \
    --decision approve \
    --comments-file qa_review_report.md

# Status updated: Pending VER Review (SIL 3-4 only)
```

---

## Step 4: Verifier Review (SIL 3-4 Only)

### 4.1 VER Review Focus

**Verifier checks** (independent verification):
1. **Requirements Compliance**: Code satisfies requirements
2. **Safety-Critical Analysis**: Focus on safety-critical functions
3. **Traceability**: Complete bidirectional traceability
4. **Independent Testing**: May perform additional tests
5. **Final Technical Approval**: Authority to approve/reject

### 4.2 VER Review Checklist

```markdown
# Verification Review - brake_controller.c

## Reviewer: Dr. Robert Johnson (VER)
## Date: 2026-03-15
## Review ID: REV-BRAKE-001
## SIL Level: 3

### 1. Requirements Verification

| Requirement | Implementation | Status |
|-------------|----------------|--------|
| REQ-FUNC-012.1 (Init) | brake_init() | ✅ Verified |
| REQ-FUNC-012.2 (Apply) | brake_apply() | ✅ Verified |
| REQ-FUNC-012.3 (Emergency) | brake_emergency() | ✅ Verified |

**Traceability**: Complete (REQ → Design → Code → Test) ✅

### 2. Safety-Critical Analysis

**Safety-Critical Functions**:
- `brake_emergency()` - SIL 3 function

**Safety Analysis**:
- [x] Emergency brake activates unconditionally
- [x] Cannot be cancelled (sticky safe state)
- [x] Maximum brake level applied immediately
- [x] Error handling comprehensive
- [x] No failure modes identified

**Safety Assessment**: PASS ✅

### 3. EN 50128 Compliance

#### Table A.4 Techniques (MANDATORY SIL 3-4)
- [x] Technique 4: Modular Approach (MANDATORY) - Verified
- [x] Technique 6: Design and Coding Standards (MANDATORY) - MISRA C compliant
- [x] Technique 8: Strongly Typed Language (HR) - Fixed-width types used

**Approved Combination**: 4, 5, 6, 8 ✅

#### Table A.5 Verification Techniques
- [x] Dynamic Analysis and Testing (MANDATORY) - 100% coverage
- [x] Traceability (MANDATORY) - Complete

### 4. Independent Verification Activities

#### 4.1 Static Analysis (Re-run)
```bash
cppcheck --enable=all --addon=misra src/brake_controller.c
Result: 0 errors, 0 warnings ✅
```

#### 4.2 Complexity Analysis (Re-run)
```bash
lizard src/brake_controller.c --CCN 10 --warnings_only
Result: No functions exceed CCN 10 ✅
```

#### 4.3 Independent Test Execution
```bash
make -f Makefile.test test
Result: 10/10 tests passed ✅
```

#### 4.4 Coverage Verification
```bash
make -f Makefile.test coverage
Result: 100% statement, branch, condition ✅
```

### 5. Traceability Verification

```bash
workspace.py trace validate \
    --phase implementation \
    --sil 3

Result: 100% coverage, 0 gaps, 0 orphans ✅
```

### 6. Issues Found

**Critical**: 0
**Major**: 0
**Minor**: 0

**Note**: QUA identified minor suggestion (magic number) - Acceptable, non-blocking.

### 7. Verification Decision

**Decision**: ✅ **APPROVE**

**Rationale**:
- All requirements verified as implemented
- Safety-critical functions verified
- EN 50128 mandatory techniques applied
- Independent verification activities passed
- Traceability complete
- No blocking issues

**Recommendation**: **APPROVED for integration**

**Signature**: Dr. Robert Johnson (VER), 2026-03-15
```

### 4.3 VER Review Workflow

```bash
# Verifier: Approve (final approval for SIL 3-4)
python3 tools/workspace.py workflow review \
    --review-id REV-BRAKE-001 \
    --reviewer VER \
    --decision approve \
    --comments-file ver_review_report.md

# Status updated: APPROVED (ready for integration)
```

---

## Step 5: Address Review Comments

### 5.1 Review Comment Types

**Critical**: MUST fix before approval
**Major**: Should fix before approval
**Minor**: Suggestion for improvement (optional)
**Question**: Clarification needed

### 5.2 Addressing Comments

**If comments require changes**:

1. **Create rework branch**:
```bash
git checkout -b review-rework-brake-controller
```

2. **Fix issues**:
```c
// Before (from review comment)
uint16_t temp = speed / 2U;  /* Magic number */

// After (addressing comment)
#define BRAKE_COEFFICIENT  (2U)  /* Brake level divider */
uint16_t temp = speed / BRAKE_COEFFICIENT;
```

3. **Re-run verification**:
```bash
# Recompile
make clean all

# Re-run tests
make -f Makefile.test test

# Re-run static analysis
cppcheck --enable=all src/brake_controller.c
```

4. **Document changes**:
```markdown
# Review Comment Resolution

## Comment 1 (Minor): Magic number
- **From**: Jane Smith (QUA)
- **Issue**: Magic number '2' on line 145
- **Resolution**: Extracted to named constant BRAKE_COEFFICIENT
- **Files Changed**: src/brake_controller.c
- **Verification**: Code recompiled, tests re-run (all pass)
```

5. **Resubmit for review**:
```bash
# Update review with resolution
python3 tools/workspace.py workflow update \
    --review-id REV-BRAKE-001 \
    --status rework-complete \
    --notes "Addressed QUA comment: magic number extracted to constant"

# Reviewers re-approve changes
```

### 5.3 Approval Criteria

**Code can be approved when**:
- All **Critical** issues resolved
- All **Major** issues resolved
- **Minor** issues addressed or justified as not blocking
- All reviewers have approved
- All quality gates passed

---

## Step 6: Final Approval and Baseline

### 6.1 Workflow Completion

```bash
# Mark review as complete
python3 tools/workspace.py workflow approve \
    --review-id REV-BRAKE-001 \
    --approver PM

# Create baseline
python3 tools/workspace.py workflow baseline \
    --document src/brake_controller.c \
    --version 1.0.0 \
    --tag BASELINE-BRAKE-CTRL-V1.0.0

# Output:
# Review REV-BRAKE-001: APPROVED
# Baseline created: BASELINE-BRAKE-CTRL-V1.0.0
# Git tag: brake_controller_v1.0.0
```

### 6.2 Update Traceability

```bash
# Generate traceability report
workspace.py trace report \
    --from requirements \
    --to implementation \
    --format markdown \
    --output docs/traceability/requirements_to_code_report.md
```

### 6.3 Archive Review Artifacts

```bash
# Archive all review documents
mkdir -p docs/reviews/archive/brake_controller_v1.0.0
mv docs/reviews/brake_controller_rev1/* \
   docs/reviews/archive/brake_controller_v1.0.0/

# Create review summary
cat > docs/reviews/archive/brake_controller_v1.0.0/REVIEW_SUMMARY.md <<EOF
# Code Review Summary - brake_controller v1.0.0

## Review Details
- Review ID: REV-BRAKE-001
- Module: brake_controller
- Version: 1.0.0
- SIL Level: 3
- Review Date: 2026-03-13 to 2026-03-15

## Reviewers
1. John Doe (PEER) - Approved 2026-03-13
2. Jane Smith (QUA) - Approved 2026-03-14
3. Dr. Robert Johnson (VER) - Approved 2026-03-15

## Review Results
- Critical Issues: 0
- Major Issues: 0
- Minor Issues: 1 (addressed)
- Questions: 0

## Metrics
- MISRA C Violations: 0 (mandatory), 0 (required), 0 (advisory)
- Complexity: Max CCN 6 (limit 10 for SIL 3)
- Coverage: 100% statement, 100% branch, 100% condition
- Unit Tests: 10/10 passed

## Approval Decision: APPROVED
- Baseline: BASELINE-BRAKE-CTRL-V1.0.0
- Ready for Integration: YES
EOF
```

---

## Step 7: Document Review Process

### 7.1 Code Review Report

**Create formal review report** (DOC-19 format):

```markdown
# Software Source Code Verification Report

**Document ID**: DOC-19-BRAKE-CTRL-001  
**Version**: 1.0.0  
**Date**: 2026-03-15  
**SIL Level**: 3

## 1. Introduction

### 1.1 Purpose
This report documents the code review verification for the brake_controller module.

### 1.2 Scope
- **Module**: brake_controller
- **Files**: src/brake_controller.c, src/brake_controller.h
- **Functions**: 6 public/private functions
- **Lines of Code**: 250

### 1.3 Review Team
| Role | Name | Independence |
|------|------|--------------|
| Author | Alice Brown | N/A |
| Peer Reviewer | John Doe | Yes |
| QA Reviewer | Jane Smith | Yes |
| Verifier | Dr. Robert Johnson | Yes (SIL 3) |

## 2. Review Process

### 2.1 Review Activities
1. Author self-review (2026-03-13)
2. Peer review (2026-03-13)
3. QA review (2026-03-14)
4. VER review (2026-03-15)

### 2.2 Review Criteria
- MISRA C:2012 compliance (MANDATORY SIL 3)
- Complexity within limits (CCN ≤ 10)
- Test coverage 100% (statement, branch, condition)
- Defensive programming implemented
- Traceability complete

## 3. Review Results

### 3.1 MISRA C Compliance
- **Mandatory Violations**: 0 ✅
- **Required Violations**: 0 ✅
- **Advisory Violations**: 0 ✅
- **Deviations**: 0

**Tool**: Cppcheck 2.13.0 with MISRA addon

### 3.2 Complexity Analysis
| Function | CCN | Status |
|----------|-----|--------|
| brake_init | 3 | PASS |
| brake_apply | 4 | PASS |
| brake_emergency | 3 | PASS |
| validate_speed | 2 | PASS |
| calculate_brake_level | 4 | PASS |
| transition_mode | 6 | PASS |

**Max CCN**: 6 (Limit: 10 for SIL 3) ✅

**Tool**: Lizard 1.17.10

### 3.3 Test Coverage
| Metric | Target | Actual | Status |
|--------|--------|--------|--------|
| Statement | 100% | 100% | ✅ PASS |
| Branch | 100% | 100% | ✅ PASS |
| Condition | 100% | 100% | ✅ PASS |
| Function | 100% | 100% | ✅ PASS |

**Unit Tests**: 10/10 passed  
**Tool**: gcov/lcov, Unity framework

### 3.4 Issues Summary
| Severity | Count | Status |
|----------|-------|--------|
| Critical | 0 | N/A |
| Major | 0 | N/A |
| Minor | 1 | Resolved |
| Questions | 0 | N/A |

**Minor Issue**: Magic number extracted to named constant (resolved).

### 3.5 Traceability Verification
- Requirements → Design: 100% ✅
- Design → Code: 100% ✅
- Code → Test: 100% ✅

**Gaps**: 0  
**Orphans**: 0

## 4. Verification Decision

**Decision**: ✅ **APPROVED**

**Rationale**:
- All EN 50128 mandatory techniques applied (Table A.4)
- Zero MISRA C mandatory violations
- 100% test coverage achieved
- Complexity within limits
- Complete traceability
- Independent verification performed (SIL 3)

**Baseline**: BASELINE-BRAKE-CTRL-V1.0.0  
**Ready for Integration**: YES

## 5. Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Author | Alice Brown | [Signed] | 2026-03-13 |
| Peer | John Doe | [Signed] | 2026-03-13 |
| QA | Jane Smith | [Signed] | 2026-03-14 |
| VER | Dr. Robert Johnson | [Signed] | 2026-03-15 |

---

**Report Status**: APPROVED  
**Prepared by**: Jane Smith (QUA)  
**Approved by**: Dr. Robert Johnson (VER)  
**Date**: 2026-03-15
```

---

## Review Decision Matrix

### Approval Criteria by SIL

**SIL 0-1**:
- Peer review: Approve
- QA review: Approve
- **Result**: APPROVED (2 approvals)

**SIL 2**:
- Peer review: Approve
- QA review: Approve
- **Result**: APPROVED (2 approvals, independent QUA)

**SIL 3-4**:
- Peer review: Approve
- QA review: Approve
- **VER review: Approve** (independent verification MANDATORY)
- **Result**: APPROVED (3 approvals, independent VER)

### Rejection Scenarios

**REJECTED if**:
- Any mandatory MISRA C violation (SIL 3-4)
- Complexity exceeds limit for SIL level
- Coverage < 100% for SIL 3-4 without justification
- Critical issues unresolved
- Traceability incomplete

**REWORK REQUIRED if**:
- Major issues found
- Required reviewer rejects
- Test failures
- Design mismatch

---

## SIL-Dependent Requirements

### SIL 0-1: Recommended
- Code review **recommended**
- Peer review sufficient
- Informal review process acceptable
- Review documentation recommended

### SIL 2: Highly Recommended
- Code review **highly recommended**
- Peer review + QA review
- Formal review process
- MISRA C compliance check
- Review documentation required

### SIL 3-4: Mandatory
- Code review **MANDATORY** (EN 50128 Section 6.5)
- Peer review + QA review + **independent VER review**
- Formal review process with documented workflow
- MISRA C compliance check **MANDATORY**
- Complexity verification **MANDATORY**
- 100% coverage verification **MANDATORY**
- Complete traceability verification **MANDATORY**
- All review artifacts retained
- Independent verification **MANDATORY**

---

## Checklist

### Pre-Review (Author)
- [ ] Code compiles without errors/warnings
- [ ] All unit tests pass
- [ ] Static analysis run (0 mandatory violations)
- [ ] Complexity within limits
- [ ] Coverage meets SIL requirements
- [ ] Self-review checklist complete
- [ ] Review package prepared

### Peer Review
- [ ] Design implementation verified
- [ ] Logic correctness checked
- [ ] Error handling reviewed
- [ ] Code clarity assessed
- [ ] Review comments documented
- [ ] Decision recorded (Approve/Reject/Rework)

### QA Review
- [ ] MISRA C compliance verified
- [ ] Complexity verified
- [ ] Coverage verified
- [ ] Defensive programming checked
- [ ] Documentation quality checked
- [ ] Traceability verified
- [ ] Review report created
- [ ] Decision recorded

### VER Review (SIL 3-4)
- [ ] Requirements compliance verified
- [ ] Safety-critical analysis performed
- [ ] Independent verification activities completed
- [ ] Traceability verification performed
- [ ] Final approval/rejection decision
- [ ] Verification report created

### Post-Review
- [ ] All comments addressed or justified
- [ ] Rework verified (if applicable)
- [ ] Final approval obtained
- [ ] Baseline created
- [ ] Traceability updated
- [ ] Review artifacts archived
- [ ] Code released for integration

---

## Tools and Commands

### Review Workflow
```bash
# Submit for review
python3 tools/workspace.py workflow submit \
    --document src/module.c \
    --for-review \
    --reviewers PEER,QUA,VER \
    --sil 3

# Record review decision
python3 tools/workspace.py workflow review \
    --review-id REV-XXX-001 \
    --reviewer QUA \
    --decision approve \
    --comments-file review_comments.md

# Final approval
python3 tools/workspace.py workflow approve \
    --review-id REV-XXX-001 \
    --approver VER

# Create baseline
python3 tools/workspace.py workflow baseline \
    --document src/module.c \
    --version 1.0.0
```

### Static Analysis (for review)
```bash
# MISRA C check
cppcheck --addon=misra --enable=all --xml src/module.c

# Complexity check
lizard src/module.c --CCN 10 --warnings_only

# Coverage check
make -f Makefile.test coverage
lcov --summary coverage/coverage_filtered.info
```

### Traceability Verification
```bash
# Validate traceability
workspace.py trace validate \
    --phase implementation \
    --sil 3

# Check for gaps
workspace.py trace check-gaps \
    --phase implementation \
    --sil 3
```

---

## Common Review Issues

### Issue 1: MISRA C Violations
**Problem**: Cppcheck reports mandatory violations.

**Solution**:
1. Review each violation
2. Fix code to comply
3. If fix not possible, document deviation with rationale
4. Re-run Cppcheck to verify

### Issue 2: Complexity Too High
**Problem**: Function exceeds CCN limit (10 for SIL 3-4).

**Solution**:
1. Refactor function into smaller functions
2. Extract complex conditions
3. Simplify control flow
4. Re-run Lizard to verify

### Issue 3: Coverage < 100%
**Problem**: Branch coverage 95%, missing one branch.

**Solution**:
1. Review coverage report for missing branch
2. Add test case for uncovered branch
3. Re-run tests and coverage
4. Verify 100% achieved

### Issue 4: Reviewer Rejection
**Problem**: VER rejects code due to safety concern.

**Solution**:
1. Understand rejection rationale
2. Address safety concern in design/code
3. Re-test thoroughly
4. Resubmit for VER review

---

## Related Resources

- **[Code Review Checklist](../resources/code-review-checklist.md)** - Comprehensive checklist (120+ items)
- **[MISRA C Coding Patterns](../resources/misra-c-coding-patterns.md)** - Compliant code patterns
- **[Common Pitfalls](../resources/common-pitfalls.md)** - Common review findings
- **[QA Review Report Template](../../../en50128-quality/templates/QA-Review-Report-template.md)** - Report format

---

## References

1. **EN 50128:2011** Section 6.5 (Software Quality Assurance)
2. **EN 50128:2011** Table A.9 (Software Quality Assurance Techniques)
3. **EN 50128:2011** Section 5.1.2.10 (Independent Verification - SIL 3-4)
4. **MISRA C:2012** Guidelines for code review
5. **`std/EN50128-2011.md`** - Full EN 50128 standard (project repository)
