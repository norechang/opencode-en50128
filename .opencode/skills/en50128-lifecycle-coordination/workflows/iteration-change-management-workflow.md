# EN 50128 Iteration and Change Management Workflow

**Skill**: `en50128-lifecycle-coordination`  
**Workflow**: Iteration and Change Management  
**Role**: Lifecycle Coordinator (COD)  
**EN 50128 Reference**: Section 5.3.2.2 (Iterations), Section 6.6 (Configuration Management), Section 6.4 (Change Management)  
**Purpose**: Handle feedback loops, change control, and regression testing throughout lifecycle

---

## Table of Contents

1. [Iteration Principles](#iteration-principles)
2. [Feedback Loop Detection](#feedback-loop-detection)
3. [Change Request Process](#change-request-process)
4. [Iteration Execution](#iteration-execution)
5. [Regression Testing Requirements](#regression-testing-requirements)
6. [Traceability Updates During Iteration](#traceability-updates-during-iteration)
7. [LIFECYCLE_STATE.md Change Log](#lifecycle_statemd-change-log)
8. [Tool Integration](#tool-integration)
9. [Automation Scripts](#automation-scripts)
10. [Example Scenarios](#example-scenarios)

---

## Iteration Principles

### EN 50128 Iteration Allowance

**Section 5.3.2.2**: "The lifecycle model shall take into account the possibility of iterations in and between phases."

EN 50128 **explicitly allows** iterations with constraints:

1. **Iterations ARE allowed** between phases (feedback loops)
2. **Change control IS required** for all iterations
3. **Traceability MUST be maintained** through iterations
4. **Regression testing IS mandatory** after iterations
5. **Configuration baselines MUST be updated** after iterations

### Iteration Types

```
┌────────────────────────────────────────────────────────────┐
│ ITERATION TYPES                                            │
├────────────────────────────────────────────────────────────┤
│ 1. Requirements Feedback                                   │
│    - Design reveals requirements issues                    │
│    - Implementation identifies missing requirements        │
│    - Testing uncovers requirements ambiguities             │
│                                                            │
│ 2. Design Feedback                                         │
│    - Implementation reveals design flaws                   │
│    - Integration identifies interface issues               │
│    - Performance testing shows design inefficiencies       │
│                                                            │
│ 3. Implementation Feedback                                 │
│    - Unit testing finds code defects                       │
│    - Static analysis reveals MISRA C violations            │
│    - Code review identifies complexity issues              │
│                                                            │
│ 4. Validation Feedback                                     │
│    - System testing reveals requirements gaps              │
│    - Customer validation identifies usability issues       │
│    - Acceptance testing uncovers performance problems      │
│                                                            │
│ 5. Safety Feedback                                         │
│    - FMEA identifies new hazards                          │
│    - FTA reveals critical failure modes                    │
│    - Safety assessment requires additional mitigations     │
└────────────────────────────────────────────────────────────┘
```

### Iteration Constraints by SIL

| SIL Level | Iteration Control | Change Approval | Regression Testing | Traceability Update |
|-----------|-------------------|-----------------|---------------------|---------------------|
| **SIL 0** | Informal | Developer decision | Optional | Recommended |
| **SIL 1** | Basic tracking | Team lead approval | Affected tests | Recommended |
| **SIL 2** | Change request | CCB approval | Affected + related tests | **MANDATORY** |
| **SIL 3** | Formal CR process | CCB + safety approval | Full regression suite | **MANDATORY** |
| **SIL 4** | Formal CR process | CCB + safety + assessor approval | Full regression suite | **MANDATORY** |

### When Iterations Are Triggered

**Common Triggers**:

1. **Verification Failure** - VER rejects deliverable (BLOCK gate)
2. **Validation Failure** - VAL rejects system behavior (BLOCK gate)
3. **Quality Gate Failure** - QUA identifies violations (BLOCK gate)
4. **Safety Issue** - SAF identifies new hazard or mitigation failure
5. **Requirements Change** - Customer or stakeholder change request
6. **Design Change** - Technical improvement or correction
7. **Implementation Defect** - Bug fix required
8. **Integration Issue** - Interface mismatch or performance problem

---

## Feedback Loop Detection

### Feedback Loop Structure

```
Phase N                  Phase N+1                 Phase N+2
┌─────────┐              ┌─────────┐               ┌─────────┐
│         │──────────────>│         │───────────────>│         │
│  Phase  │              │  Phase  │               │  Phase  │
│    N    │<──────────────│   N+1   │<───────────────│   N+2   │
│         │   FEEDBACK    │         │   FEEDBACK    │         │
└─────────┘              └─────────┘               └─────────┘
     │                        │                         │
     │                        │                         │
     └────────────────────────┴─────────────────────────┘
              FEEDBACK (may skip phases)
```

### Feedback Detection Algorithm

**Inputs**:
- Current phase
- Issue type (requirements, design, implementation, testing, safety)
- Issue severity (critical, major, minor)
- SIL level

**Output**:
- Target phase for iteration (return to which phase)
- Iteration scope (which artifacts need update)
- Change control level (informal, CR, formal CR)

**Algorithm**:

```python
def detect_feedback_loop(current_phase, issue_type, severity, sil_level):
    """
    Detect which phase to return to based on issue type.
    
    EN 50128 Reference: Section 5.3.2.2 (iterations allowed)
    """
    
    # Feedback mapping: issue_type -> target_phase
    feedback_map = {
        'requirements': {
            'ambiguous_requirement': 'requirements',
            'missing_requirement': 'requirements',
            'conflicting_requirement': 'requirements',
            'untestable_requirement': 'requirements',
        },
        'design': {
            'architecture_flaw': 'design',
            'interface_mismatch': 'design',
            'complexity_violation': 'design',
            'performance_issue': 'design',
        },
        'implementation': {
            'code_defect': 'implementation',
            'misra_violation': 'implementation',
            'unit_test_failure': 'implementation',
        },
        'safety': {
            'new_hazard': 'requirements',  # Safety requirements update
            'mitigation_failure': 'design',  # Design mitigation update
            'safety_violation': 'implementation',  # Code fix
        },
        'validation': {
            'system_test_failure': 'integration',  # May need integration fix
            'acceptance_failure': 'requirements',  # Requirements gap
            'performance_failure': 'design',  # Design issue
        }
    }
    
    # Determine target phase
    if issue_type in feedback_map:
        target_phase = feedback_map[issue_type].get(severity, 'requirements')
    else:
        target_phase = 'requirements'  # Default: most upstream
    
    # Determine change control level based on SIL
    if sil_level in [0, 1]:
        change_control = 'informal'  # Team decision
    elif sil_level == 2:
        change_control = 'change_request'  # CCB approval
    else:  # SIL 3-4
        change_control = 'formal_change_request'  # CCB + safety + assessor
    
    # Determine iteration scope (which artifacts affected)
    iteration_scope = calculate_iteration_scope(target_phase, current_phase)
    
    return {
        'target_phase': target_phase,
        'change_control_level': change_control,
        'iteration_scope': iteration_scope,
        'regression_testing_required': True if sil_level >= 2 else False
    }

def calculate_iteration_scope(target_phase, current_phase):
    """
    Calculate which artifacts need update when returning to target_phase.
    """
    
    # Phase dependency chain
    phase_chain = [
        'planning',
        'requirements',
        'design',
        'component-design',
        'implementation',
        'integration',
        'validation',
        'assessment',
        'deployment'
    ]
    
    target_idx = phase_chain.index(target_phase)
    current_idx = phase_chain.index(current_phase)
    
    # All phases from target to current are in scope
    affected_phases = phase_chain[target_idx:current_idx+1]
    
    return affected_phases
```

### Feedback Detection Examples

**Example 1: Validation Failure Requires Requirements Update**

```bash
# Scenario: System testing reveals missing requirement
# Current phase: validation
# Issue: acceptance_failure (missing requirement)
# SIL: 3

feedback = detect_feedback_loop(
    current_phase='validation',
    issue_type='validation',
    severity='acceptance_failure',
    sil_level=3
)

# Result:
# {
#   'target_phase': 'requirements',
#   'change_control_level': 'formal_change_request',
#   'iteration_scope': ['requirements', 'design', 'implementation', 
#                       'integration', 'validation'],
#   'regression_testing_required': True
# }
```

**Example 2: Design Issue Found During Implementation**

```bash
# Scenario: Code reveals interface mismatch in design
# Current phase: implementation
# Issue: interface_mismatch
# SIL: 2

feedback = detect_feedback_loop(
    current_phase='implementation',
    issue_type='design',
    severity='interface_mismatch',
    sil_level=2
)

# Result:
# {
#   'target_phase': 'design',
#   'change_control_level': 'change_request',
#   'iteration_scope': ['design', 'implementation'],
#   'regression_testing_required': True
# }
```

---

## Change Request Process

### Change Control Board (CCB)

**EN 50128 Reference**: Section 6.4 (Problem Reporting and Change Control)

**CCB Composition** (SIL-dependent):

| SIL Level | CCB Members | Decision Authority | Safety Review Required |
|-----------|-------------|---------------------|------------------------|
| **SIL 0** | PM, Lead Developer | PM | No |
| **SIL 1** | PM, Lead Developer, QUA | PM | No |
| **SIL 2** | PM, Lead Developer, QUA, CM | CCB consensus | Recommended |
| **SIL 3** | PM, QUA, CM, SAF, VER | CCB consensus + SAF approval | **MANDATORY** |
| **SIL 4** | PM, QUA, CM, SAF, VER, ASR | CCB consensus + SAF + ASR approval | **MANDATORY** |

### Change Request Workflow

```
┌─────────────────────────────────────────────────────────────┐
│ CHANGE REQUEST WORKFLOW                                     │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. CR Creation                                             │
│     - Identify issue/change need                            │
│     - Create CR document (CR-<project>-<NNNN>)             │
│     - Describe current state, proposed change, rationale    │
│                                                             │
│  2. Impact Analysis                                         │
│     - Identify affected artifacts (REQ, DES, CODE, TESTS)   │
│     - Estimate effort (person-hours)                        │
│     - Identify affected requirements (traceability)         │
│     - Assess safety impact (SAF review)                     │
│     - Determine regression test scope                       │
│                                                             │
│  3. CCB Review                                              │
│     - Present CR to CCB                                     │
│     - Review impact analysis                                │
│     - Safety approval (SIL 3-4)                             │
│     - Assessor approval (SIL 4)                             │
│     - Decision: APPROVE / REJECT / DEFER                    │
│                                                             │
│  4. Implementation                                          │
│     - Return to target phase                                │
│     - Update artifacts per iteration scope                  │
│     - Maintain traceability (RTM updates)                   │
│     - Execute regression tests                              │
│                                                             │
│  5. Verification                                            │
│     - VER verifies change implemented correctly             │
│     - QUA reviews updated artifacts                         │
│     - Coverage/quality metrics re-checked                   │
│                                                             │
│  6. Closure                                                 │
│     - Update LIFECYCLE_STATE.md with iteration record       │
│     - Close CR (status: CLOSED)                             │
│     - Update baselines (CM)                                 │
└─────────────────────────────────────────────────────────────┘
```

### Change Request Document Template

**CR Document ID**: `CR-<project>-<NNNN>`

**Template**:

```markdown
# Change Request CR-<project>-<NNNN>

## 1. Change Identification

**CR ID**: CR-<project>-<NNNN>  
**Date Created**: YYYY-MM-DD  
**Originator**: [Name, Role]  
**Current Phase**: [Planning/Requirements/Design/Implementation/Integration/Validation]  
**SIL Level**: [0/1/2/3/4]  

## 2. Change Description

### 2.1 Current State

[Describe current artifact/behavior that needs change]

### 2.2 Proposed Change

[Describe proposed new artifact/behavior]

### 2.3 Rationale

[Explain why change is needed: defect, requirements gap, safety issue, etc.]

### 2.4 Category

- [ ] Requirements Change
- [ ] Design Change
- [ ] Implementation Change (Bug Fix)
- [ ] Safety Change
- [ ] Other: _______________

## 3. Impact Analysis

### 3.1 Affected Artifacts

| Artifact Type | Artifact ID | Change Scope |
|---------------|-------------|--------------|
| Requirements  | REQ-XXX-NNNN | [Modify/Add/Delete] |
| Design        | DES-XXX-NNNN | [Modify/Add/Delete] |
| Code          | `file.c:line` | [Modify/Add/Delete] |
| Tests         | TEST-XXX-NNNN | [Modify/Add/Delete] |

### 3.2 Traceability Impact

**Affected Requirements** (from RTM):
- REQ-XXX-001
- REQ-XXX-002

**Downstream Impact** (propagates to):
- DES-XXX-010
- CODE: `module.c`
- TEST-XXX-050

### 3.3 Safety Impact (SAF Review Required for SIL 2+)

**Hazard Assessment**:
- [ ] No new hazards introduced
- [ ] New hazards identified (list below)
- [ ] Existing mitigations affected

**New Hazards** (if any):
[List new hazards]

**Mitigation Updates**:
[Describe mitigation updates]

### 3.4 Effort Estimate

**Total Effort**: [XX person-hours]

| Phase | Activity | Effort (hours) |
|-------|----------|----------------|
| Requirements | Update SRS | X |
| Design | Update SAS/SDS | X |
| Implementation | Code changes | X |
| Testing | Regression tests | X |
| Verification | Re-verification | X |

### 3.5 Regression Test Scope

**Test Scope**:
- [ ] Affected tests only
- [ ] Affected + related tests
- [ ] Full regression suite (MANDATORY SIL 3-4)

**Tests to Re-Execute**:
- TEST-XXX-001
- TEST-XXX-002
- ...

## 4. CCB Review

**CCB Meeting Date**: YYYY-MM-DD  
**CCB Members Present**:
- [Name, Role]
- [Name, Role]

**CCB Decision**: [APPROVE / REJECT / DEFER]  
**Decision Date**: YYYY-MM-DD  
**Rationale**: [Explain decision]

**Safety Approval** (SIL 3-4):
- SAF Approver: [Name]
- SAF Approval Date: YYYY-MM-DD
- Safety Impact Acceptable: [YES/NO]

**Assessor Approval** (SIL 4):
- ASR Approver: [Name]
- ASR Approval Date: YYYY-MM-DD
- Safety Case Impact Acceptable: [YES/NO]

## 5. Implementation Tracking

**Target Phase Return**: [Phase name]  
**Iteration Scope**: [Phases affected]  
**Start Date**: YYYY-MM-DD  
**Completion Date**: YYYY-MM-DD  

**Implementation Status**:
- [ ] Requirements updated
- [ ] Design updated
- [ ] Code updated
- [ ] Tests updated
- [ ] RTM updated
- [ ] Regression tests passed
- [ ] Verification complete
- [ ] Baselines updated

## 6. Verification

**Verifier**: [Name]  
**Verification Date**: YYYY-MM-DD  
**Verification Result**: [PASS/FAIL]  
**Verification Notes**: [Notes]

## 7. Closure

**Closure Date**: YYYY-MM-DD  
**Closed By**: [Name, Role]  
**Final Status**: CLOSED  
**LIFECYCLE_STATE.md Updated**: [YES/NO]  
**Baseline Version**: [Version number]
```

### CR Impact Analysis Tool

**Tool**: `cr_impact_analyzer.py`

**Purpose**: Analyze CR impact on traceability and downstream artifacts

**Usage**:

```bash
# Analyze impact of changing a requirement
python3 tools/cr_impact_analyzer.py \
  --cr-id CR-PROJ-0001 \
  --affected-req REQ-PROJ-001 \
  --change-type modify \
  --rtm-file docs/traceability/requirements_traceability_matrix.md

# Output:
# CR Impact Analysis Report
# ========================
# CR ID: CR-PROJ-0001
# Affected Requirement: REQ-PROJ-001
# Change Type: modify
#
# Downstream Impact (from RTM):
# - Design: DES-PROJ-010, DES-PROJ-011
# - Code: src/door_control.c:50, src/door_control.c:75
# - Unit Tests: TEST-PROJ-050, TEST-PROJ-051
# - Integration Tests: TEST-PROJ-100
# - System Tests: TEST-PROJ-200
#
# Regression Test Scope:
# - Must re-execute: 5 tests
# - Related tests: 8 tests
# - Total regression: 13 tests
#
# Effort Estimate: 24 person-hours
# - Requirements update: 4 hours
# - Design update: 6 hours
# - Code update: 8 hours
# - Testing: 6 hours
```

---

## Iteration Execution

### Iteration Execution Steps

**Step 1: COD Authorizes Iteration**

```bash
# COD detects feedback condition
@cod authorize-iteration --phase validation \
  --target-phase requirements \
  --cr-id CR-PROJ-0001 \
  --reason "System testing revealed missing requirement REQ-PROJ-025"

# COD updates LIFECYCLE_STATE.md
# - Records iteration event
# - Sets current phase = requirements (return)
# - Links to CR-PROJ-0001
# - Marks validation as "INCOMPLETE" (pending re-validation)
```

**Step 2: Return to Target Phase**

```bash
# Return to requirements phase
# COD resets phase status to IN_PROGRESS
# Previous work preserved, but marked for update

# Example: LIFECYCLE_STATE.md update
phases:
  requirements:
    status: IN_PROGRESS  # WAS: COMPLETE
    iteration_count: 1   # Increment iteration counter
    iteration_reason: "CR-PROJ-0001: Add missing requirement"
    baseline: v1.0.0     # Previous baseline preserved
    new_baseline: v1.1.0 # New baseline after iteration
```

**Step 3: Update Artifacts in Iteration Scope**

```bash
# For iteration scope: [requirements, design, implementation, integration, validation]

# 3a. Update Requirements (Phase 2)
# REQ updates Software Requirements Specification
# - Add new requirement REQ-PROJ-025
# - Update traceability (upstream to system requirements)
# - Mark as "CHANGED" in change log

# 3b. Update Design (Phase 3)
# DES updates Software Architecture Specification / Software Design Specification
# - Add design element for REQ-PROJ-025
# - Update RTM: REQ-PROJ-025 -> DES-PROJ-030

# 3c. Update Implementation (Phase 4)
# IMP updates code
# - Implement new functionality for REQ-PROJ-025
# - Add/update unit tests
# - Update RTM: DES-PROJ-030 -> src/module.c:100 -> TEST-PROJ-080

# 3d. Update Integration (Phase 5)
# INT updates integration tests
# - Add/update integration tests for REQ-PROJ-025
# - Re-execute affected integration tests

# 3e. Re-Validate (Phase 6)
# VAL re-executes system tests
# - Re-execute affected validation tests
# - Execute new tests for REQ-PROJ-025
# - Verify all tests pass
```

**Step 4: Maintain Traceability**

```bash
# Update RTM at each phase
workspace.py trace add-requirement \
  --req-id REQ-PROJ-025 \
  --description "Door shall provide audible alert on timeout" \
  --sil 3

workspace.py trace link \
  --from REQ-PROJ-025 \
  --to DES-PROJ-030 \
  --type design

workspace.py trace link \
  --from DES-PROJ-030 \
  --to src/door_control.c:150 \
  --type implementation

workspace.py trace link \
  --from src/door_control.c:150 \
  --to TEST-PROJ-080 \
  --type unit_test

# Verify traceability complete
workspace.py trace validate --sil 3

# Output:
# ✓ All requirements traced to design
# ✓ All design traced to implementation
# ✓ All code traced to unit tests
# ✓ Forward coverage: 100%
# ✓ Backward coverage: 100%
# ✓ No gaps detected
```

**Step 5: Execute Regression Tests**

```bash
# Regression test execution (SIL 3 = full regression suite)
workspace.py wf submit-document \
  --document-id TEST-REPORT-ITER-001 \
  --title "Regression Test Report - CR-PROJ-0001" \
  --phase integration \
  --author "TST Agent" \
  --status "Submitted for Review"

# TST executes full regression suite
# - Re-run all unit tests
# - Re-run all integration tests
# - Re-run all system tests
# - Document results in TEST-REPORT-ITER-001
```

**Step 6: Re-Verify and Re-Validate**

```bash
# VER re-verifies all updated artifacts
@ver verify-iteration --cr-id CR-PROJ-0001

# VER checks:
# - Requirements traceability complete
# - Design consistency
# - Code quality (MISRA C, complexity)
# - Test coverage (still 100% for SIL 3)
# - RTM gaps (none)

# VAL re-validates system
@val validate-iteration --cr-id CR-PROJ-0001

# VAL checks:
# - All system tests pass
# - New requirement REQ-PROJ-025 validated
# - No regressions introduced
```

**Step 7: COD Completes Iteration**

```bash
# COD verifies iteration complete
@cod complete-iteration --cr-id CR-PROJ-0001

# COD checks:
# - All iteration scope phases re-completed
# - Traceability updated and validated
# - Regression tests passed
# - VER/VAL approvals obtained
# - Baselines updated

# COD updates LIFECYCLE_STATE.md
phases:
  validation:
    status: COMPLETE  # Restored after successful iteration
    iteration_completion_date: "2026-03-15"
    baseline: v1.1.0  # New baseline
```

### Iteration Completion Criteria

| SIL Level | Iteration Completion Criteria |
|-----------|-------------------------------|
| **SIL 0** | • Updated artifacts complete<br>• Basic testing passed |
| **SIL 1** | • Updated artifacts complete<br>• Affected tests passed<br>• Traceability recommended |
| **SIL 2** | • All iteration scope phases re-completed<br>• Affected + related tests passed<br>• Traceability updated (MANDATORY)<br>• QUA review complete |
| **SIL 3-4** | • All iteration scope phases re-completed<br>• **Full regression suite passed** (MANDATORY)<br>• Traceability updated and validated (MANDATORY)<br>• VER re-verification complete<br>• VAL re-validation complete<br>• Baselines updated<br>• CR closed with approvals |

---

## Regression Testing Requirements

### Regression Test Strategy

**Purpose**: Ensure changes do not introduce unintended side effects

**EN 50128 Requirement**: Implicit in Section 6.1 (testing thoroughness) and Section 5.3.2.2 (iterations)

### Regression Test Scope by SIL

| SIL Level | Regression Scope | Test Selection | Automation Required |
|-----------|------------------|----------------|---------------------|
| **SIL 0** | Optional | Developer discretion | No |
| **SIL 1** | Affected tests | Manual selection | Recommended |
| **SIL 2** | Affected + related tests | Impact-based selection | **MANDATORY** |
| **SIL 3** | **Full regression suite** | All tests | **MANDATORY** |
| **SIL 4** | **Full regression suite** | All tests | **MANDATORY** |

### Regression Test Selection Algorithm

**For SIL 2** (affected + related):

```python
def select_regression_tests_sil2(changed_artifacts, rtm):
    """
    Select regression tests for SIL 2 iteration.
    Includes affected tests + related tests (1 hop).
    
    Args:
        changed_artifacts: List of changed artifact IDs (REQ, DES, CODE)
        rtm: Requirements Traceability Matrix
        
    Returns:
        Set of test IDs to re-execute
    """
    regression_tests = set()
    
    # 1. Find directly affected tests
    for artifact in changed_artifacts:
        # Trace from artifact to tests
        tests = rtm.trace_forward(artifact, target_type='test')
        regression_tests.update(tests)
    
    # 2. Find related tests (1 hop)
    related_artifacts = set()
    for artifact in changed_artifacts:
        # Find related requirements (same module, same feature)
        related = rtm.find_related(artifact, hops=1)
        related_artifacts.update(related)
    
    for artifact in related_artifacts:
        tests = rtm.trace_forward(artifact, target_type='test')
        regression_tests.update(tests)
    
    return regression_tests
```

**For SIL 3-4** (full regression):

```python
def select_regression_tests_sil3(rtm):
    """
    Select regression tests for SIL 3-4 iteration.
    ALWAYS full regression suite.
    
    Returns:
        ALL test IDs in RTM
    """
    return rtm.get_all_tests()  # Every single test
```

### Regression Test Execution

**Test Execution Steps**:

1. **Identify regression test set** (via selection algorithm)
2. **Prepare test environment** (same environment as original tests)
3. **Execute tests** (automated test harness)
4. **Record results** (machine-readable format: XML/JSON)
5. **Compare with baseline** (detect regressions)
6. **Report results** (to TST, VER, VAL, COD)

**Regression Test Report Template**:

```markdown
# Regression Test Report - CR-<project>-<NNNN>

## 1. Test Identification

**Report ID**: TEST-REPORT-ITER-<NNNN>  
**CR ID**: CR-<project>-<NNNN>  
**Test Date**: YYYY-MM-DD  
**Tester**: [Name]  
**SIL Level**: [0/1/2/3/4]  

## 2. Test Scope

**Regression Scope**: [Affected tests / Affected + related / Full regression]  
**Total Tests**: [N tests]  
**Test Categories**:
- Unit tests: [N]
- Integration tests: [N]
- System tests: [N]

## 3. Test Results

**Summary**:
- Tests Executed: [N]
- Tests Passed: [N]
- Tests Failed: [N]
- Tests Skipped: [N]

**Pass Rate**: [XX%]

## 4. Detailed Results

| Test ID | Category | Status | Baseline Result | Regression? |
|---------|----------|--------|-----------------|-------------|
| TEST-001 | Unit | PASS | PASS | No |
| TEST-002 | Unit | PASS | PASS | No |
| TEST-050 | Integration | FAIL | PASS | **YES** |
| TEST-100 | System | PASS | PASS | No |

## 5. Regression Analysis

**Regressions Detected**: [N]

### Regression 1: TEST-050 Failure

**Test ID**: TEST-050  
**Test Name**: Door integration test  
**Expected**: Door closes within 3 seconds  
**Actual**: Door closes in 5 seconds  
**Root Cause**: New timeout logic in CR-PROJ-0001 increased delay  
**Action**: Fix timeout logic in `door_control.c:150`  

## 6. Conclusion

**Regression Testing Result**: [PASS / FAIL]  
**Regressions Resolved**: [YES / NO]  
**Ready for Gate Check**: [YES / NO]
```

### Regression Test Automation

**Tool**: `regression_test_selector.py`

**Purpose**: Automate regression test selection based on SIL level and changed artifacts

**Usage**:

```bash
# Select regression tests for SIL 2 iteration
python3 tools/regression_test_selector.py \
  --sil 2 \
  --changed-artifacts REQ-PROJ-001,DES-PROJ-010,src/door_control.c \
  --rtm-file docs/traceability/requirements_traceability_matrix.md \
  --output regression_test_list.txt

# Output: regression_test_list.txt
# TEST-PROJ-050
# TEST-PROJ-051
# TEST-PROJ-052
# TEST-PROJ-100  (related test)
# TEST-PROJ-101  (related test)

# Execute regression tests
./scripts/run_regression_tests.sh regression_test_list.txt
```

---

## Traceability Updates During Iteration

### Traceability Maintenance Rules

**MANDATORY for SIL 2+ (EN 50128 Table A.9 - Traceability MANDATORY SIL 3-4, HR SIL 2)**:

1. **RTM MUST be updated** at each phase during iteration
2. **Bidirectional links MUST be maintained** (forward + backward)
3. **Gap detection MUST be run** after each artifact update
4. **100% coverage MUST be restored** before iteration completion (SIL 3-4)

### RTM Update Workflow During Iteration

```
Iteration Start
     │
     ├─> Update Requirements
     │   └─> workspace.py trace add-requirement REQ-XXX
     │       workspace.py trace link --from SYSTEM-REQ --to REQ-XXX
     │       workspace.py trace validate (check gaps)
     │
     ├─> Update Design
     │   └─> workspace.py trace link --from REQ-XXX --to DES-XXX
     │       workspace.py trace validate (check gaps)
     │
     ├─> Update Implementation
     │   └─> workspace.py trace link --from DES-XXX --to src/file.c:line
     │       workspace.py trace link --from src/file.c:line --to TEST-XXX
     │       workspace.py trace validate (check gaps)
     │
     ├─> Update Tests
     │   └─> workspace.py trace link --from TEST-XXX --to VALIDATION-RESULT-XXX
     │       workspace.py trace validate (check gaps)
     │
     └─> Iteration Complete
         └─> workspace.py trace report --format pdf (final RTM report)
```

### RTM Gap Detection During Iteration

**Gap Types to Check**:

1. **Uncovered Requirements** - Requirements with no downstream design
2. **Orphan Design** - Design elements with no upstream requirements
3. **Untraced Code** - Code with no design link
4. **Untested Code** - Code with no unit test link
5. **Unvalidated Tests** - Tests with no validation result

**Gap Detection Tool**:

```bash
# Run gap detection after each artifact update
workspace.py trace validate --sil 3 --report gaps_iteration.txt

# Example output (gaps detected):
# RTM Validation Report (SIL 3)
# ==============================
# 
# ❌ GAPS DETECTED (ITERATION INCOMPLETE)
# 
# Uncovered Requirements:
# - REQ-PROJ-025 (NEW) -> No design link
# 
# Orphan Design:
# - (none)
# 
# Untraced Code:
# - (none)
# 
# Untested Code:
# - src/door_control.c:150 (NEW) -> No unit test link
# 
# Unvalidated Tests:
# - TEST-PROJ-080 (NEW) -> No validation result
# 
# ACTION: Continue iteration, add missing links
```

**After Gap Resolution**:

```bash
# Re-run gap detection
workspace.py trace validate --sil 3 --report gaps_iteration_final.txt

# Example output (no gaps):
# RTM Validation Report (SIL 3)
# ==============================
# 
# ✓ NO GAPS DETECTED
# 
# Forward Coverage: 100% (25/25 requirements traced)
# Backward Coverage: 100% (25/25 design elements traced)
# 
# Traceability Complete: YES
# Iteration Ready for Completion: YES
```

---

## LIFECYCLE_STATE.md Change Log

### Iteration Tracking in LIFECYCLE_STATE.md

**Purpose**: Record all iterations for audit trail and lifecycle transparency

**Location**: Root of project repository (`LIFECYCLE_STATE.md`)

### Iteration Log Structure

```yaml
# LIFECYCLE_STATE.md (excerpt)

project:
  name: "Railway Door Control System"
  sil: 3

iterations:
  - iteration_id: ITER-001
    cr_id: CR-PROJ-0001
    start_date: "2026-03-10"
    end_date: "2026-03-15"
    trigger_phase: validation
    target_phase: requirements
    iteration_scope:
      - requirements
      - design
      - implementation
      - integration
      - validation
    reason: "System testing revealed missing requirement REQ-PROJ-025"
    ccb_decision: APPROVED
    ccb_date: "2026-03-11"
    safety_approval: true
    safety_approver: "SAF Agent"
    artifacts_updated:
      - REQ-PROJ-025 (added)
      - DES-PROJ-030 (added)
      - src/door_control.c:150 (modified)
      - TEST-PROJ-080 (added)
    regression_tests_executed: 25
    regression_tests_passed: 25
    traceability_validated: true
    status: COMPLETE
    
  - iteration_id: ITER-002
    cr_id: CR-PROJ-0002
    start_date: "2026-03-20"
    end_date: "2026-03-22"
    trigger_phase: integration
    target_phase: design
    iteration_scope:
      - design
      - implementation
      - integration
    reason: "Interface mismatch detected during integration testing"
    ccb_decision: APPROVED
    ccb_date: "2026-03-20"
    safety_approval: true
    safety_approver: "SAF Agent"
    artifacts_updated:
      - DES-PROJ-015 (modified)
      - src/interface.c:80 (modified)
    regression_tests_executed: 25
    regression_tests_passed: 25
    traceability_validated: true
    status: COMPLETE
```

### COD Commands for Iteration Tracking

**1. Start Iteration**:

```bash
@cod start-iteration \
  --cr-id CR-PROJ-0001 \
  --trigger-phase validation \
  --target-phase requirements \
  --reason "System testing revealed missing requirement"

# COD updates LIFECYCLE_STATE.md:
# - Creates new iteration entry with status IN_PROGRESS
# - Records trigger phase, target phase, reason
# - Links to CR-PROJ-0001
# - Sets current phase = requirements
```

**2. Update Iteration Progress**:

```bash
@cod update-iteration \
  --iteration-id ITER-001 \
  --artifact-updated REQ-PROJ-025 \
  --action added

# COD updates LIFECYCLE_STATE.md:
# - Appends to artifacts_updated list
# - Records change type (added/modified/deleted)
```

**3. Complete Iteration**:

```bash
@cod complete-iteration \
  --iteration-id ITER-001 \
  --regression-tests-passed 25 \
  --traceability-validated true

# COD updates LIFECYCLE_STATE.md:
# - Sets iteration status = COMPLETE
# - Records end_date
# - Records regression test results
# - Restores phases to COMPLETE status
```

### Iteration Metrics

**Tracked Metrics** (per iteration):

1. **Duration** - Start date to end date (calendar days)
2. **Effort** - Total person-hours (from CR impact analysis)
3. **Artifacts Updated** - Count and list of artifacts
4. **Regression Tests** - Number executed and passed
5. **Traceability Impact** - Number of RTM links updated

**Example Iteration Metrics** (from LIFECYCLE_STATE.md):

```yaml
iteration_metrics:
  total_iterations: 2
  average_duration_days: 4.5
  total_effort_hours: 72
  total_artifacts_updated: 6
  total_regression_tests: 50  (25 per iteration x 2)
```

---

## Tool Integration

### workspace.py Integration for Iterations

**Traceability Management** (`workspace.py trace`):

```bash
# 1. Add new requirement during iteration
workspace.py trace add-requirement \
  --req-id REQ-PROJ-025 \
  --description "Door audible alert on timeout" \
  --sil 3 \
  --iteration ITER-001

# 2. Link new requirement to upstream system requirement
workspace.py trace link \
  --from SYSTEM-REQ-010 \
  --to REQ-PROJ-025 \
  --type requirements \
  --iteration ITER-001

# 3. Link new requirement to design
workspace.py trace link \
  --from REQ-PROJ-025 \
  --to DES-PROJ-030 \
  --type design \
  --iteration ITER-001

# 4. Link design to implementation
workspace.py trace link \
  --from DES-PROJ-030 \
  --to src/door_control.c:150 \
  --type implementation \
  --iteration ITER-001

# 5. Link implementation to unit test
workspace.py trace link \
  --from src/door_control.c:150 \
  --to TEST-PROJ-080 \
  --type unit_test \
  --iteration ITER-001

# 6. Validate traceability (no gaps)
workspace.py trace validate --sil 3 --iteration ITER-001

# 7. Generate iteration RTM report
workspace.py trace report \
  --format markdown \
  --output docs/traceability/rtm_iteration_001.md \
  --iteration ITER-001
```

**Workflow Management** (`workspace.py wf`):

```bash
# Submit updated documents during iteration
workspace.py wf submit-document \
  --document-id SRS-v1.1 \
  --title "Software Requirements Specification v1.1 (Iteration ITER-001)" \
  --phase requirements \
  --author "REQ Agent" \
  --iteration ITER-001

workspace.py wf submit-document \
  --document-id SAS-v1.1 \
  --title "Software Architecture Specification v1.1 (Iteration ITER-001)" \
  --phase design \
  --author "DES Agent" \
  --iteration ITER-001

# Track iteration document approval workflow
workspace.py wf list-pending --iteration ITER-001

# Output:
# Pending Documents (Iteration ITER-001):
# - SRS-v1.1 (Submitted, awaiting QUA review)
# - SAS-v1.1 (Submitted, awaiting QUA review)

# Approve iteration documents
workspace.py wf approve-document \
  --document-id SRS-v1.1 \
  --approver "QUA Agent" \
  --iteration ITER-001
```

---

## Automation Scripts

### Script 1: CR Impact Analyzer

**File**: `tools/cr_impact_analyzer.py`

```python
#!/usr/bin/env python3
"""
CR Impact Analyzer

Analyze change request impact on traceability and downstream artifacts.

Usage:
    python3 tools/cr_impact_analyzer.py \\
      --cr-id CR-PROJ-0001 \\
      --affected-req REQ-PROJ-001 \\
      --change-type modify \\
      --rtm-file docs/traceability/requirements_traceability_matrix.md
"""

import argparse
import sys
from pathlib import Path

class CRImpactAnalyzer:
    def __init__(self, rtm_file):
        self.rtm_file = Path(rtm_file)
        self.rtm = self.load_rtm()
        
    def load_rtm(self):
        """Load Requirements Traceability Matrix from markdown."""
        if not self.rtm_file.exists():
            raise FileNotFoundError(f"RTM file not found: {self.rtm_file}")
        
        # Parse RTM markdown (simplified)
        # In production, use structured format (JSON/YAML)
        rtm = {}
        with open(self.rtm_file, 'r') as f:
            content = f.read()
            # Parse traceability links from RTM
            # Format: REQ-XXX -> DES-YYY -> CODE-ZZZ -> TEST-AAA
            # (Implementation details omitted for brevity)
        return rtm
    
    def analyze_impact(self, cr_id, affected_artifact, change_type):
        """
        Analyze impact of changing an artifact.
        
        Args:
            cr_id: Change request ID
            affected_artifact: Artifact ID (e.g., REQ-PROJ-001)
            change_type: 'add', 'modify', 'delete'
            
        Returns:
            Dictionary with impact analysis results
        """
        result = {
            'cr_id': cr_id,
            'affected_artifact': affected_artifact,
            'change_type': change_type,
            'downstream_impact': [],
            'regression_tests': [],
            'effort_estimate': {}
        }
        
        # Trace forward to find downstream artifacts
        downstream = self._trace_forward(affected_artifact)
        result['downstream_impact'] = downstream
        
        # Identify regression tests
        tests = self._find_tests(affected_artifact, downstream)
        result['regression_tests'] = tests
        
        # Estimate effort
        effort = self._estimate_effort(change_type, len(downstream), len(tests))
        result['effort_estimate'] = effort
        
        return result
    
    def _trace_forward(self, artifact_id):
        """Trace forward from artifact to all downstream dependencies."""
        downstream = []
        
        # Simplified: In production, walk RTM graph
        # Example: REQ -> DES -> CODE -> TEST
        if artifact_id.startswith('REQ'):
            # Find design elements
            downstream.extend(self._find_linked_design(artifact_id))
            # Find code
            for des in downstream:
                if des['type'] == 'design':
                    downstream.extend(self._find_linked_code(des['id']))
            # Find tests
            for code in downstream:
                if code['type'] == 'code':
                    downstream.extend(self._find_linked_tests(code['id']))
        
        return downstream
    
    def _find_tests(self, artifact_id, downstream):
        """Find all tests affected by change."""
        tests = []
        
        # Direct tests
        tests.extend([d for d in downstream if d['type'] == 'test'])
        
        # Related tests (1 hop)
        for artifact in downstream:
            related = self._find_related_tests(artifact['id'])
            tests.extend(related)
        
        return tests
    
    def _estimate_effort(self, change_type, downstream_count, test_count):
        """Estimate effort in person-hours."""
        effort = {
            'requirements': 0,
            'design': 0,
            'implementation': 0,
            'testing': 0,
            'verification': 0,
            'total': 0
        }
        
        # Effort model (simplified)
        if change_type == 'add':
            effort['requirements'] = 4
            effort['design'] = 6
            effort['implementation'] = 8
            effort['testing'] = 2 * test_count
            effort['verification'] = 4
        elif change_type == 'modify':
            effort['requirements'] = 2
            effort['design'] = 4
            effort['implementation'] = 6
            effort['testing'] = 1.5 * test_count
            effort['verification'] = 3
        elif change_type == 'delete':
            effort['requirements'] = 1
            effort['design'] = 2
            effort['implementation'] = 3
            effort['testing'] = 1 * test_count
            effort['verification'] = 2
        
        effort['total'] = sum(effort.values())
        return effort
    
    def generate_report(self, result):
        """Generate impact analysis report."""
        report = f"""
CR Impact Analysis Report
========================
CR ID: {result['cr_id']}
Affected Artifact: {result['affected_artifact']}
Change Type: {result['change_type']}

Downstream Impact:
"""
        for item in result['downstream_impact']:
            report += f"  - {item['type']}: {item['id']}\n"
        
        report += f"\nRegression Tests ({len(result['regression_tests'])} tests):\n"
        for test in result['regression_tests']:
            report += f"  - {test['id']}: {test['name']}\n"
        
        report += f"\nEffort Estimate:\n"
        for phase, hours in result['effort_estimate'].items():
            report += f"  {phase}: {hours} hours\n"
        
        return report


def main():
    parser = argparse.ArgumentParser(description='Analyze CR impact')
    parser.add_argument('--cr-id', required=True, help='Change request ID')
    parser.add_argument('--affected-req', required=True, help='Affected requirement ID')
    parser.add_argument('--change-type', required=True, choices=['add', 'modify', 'delete'])
    parser.add_argument('--rtm-file', required=True, help='RTM file path')
    parser.add_argument('--output', help='Output file (default: stdout)')
    
    args = parser.parse_args()
    
    # Analyze impact
    analyzer = CRImpactAnalyzer(args.rtm_file)
    result = analyzer.analyze_impact(args.cr_id, args.affected_req, args.change_type)
    
    # Generate report
    report = analyzer.generate_report(result)
    
    # Output
    if args.output:
        with open(args.output, 'w') as f:
            f.write(report)
        print(f"Impact analysis report written to {args.output}")
    else:
        print(report)


if __name__ == '__main__':
    main()
```

### Script 2: Regression Test Selector

**File**: `tools/regression_test_selector.py`

```python
#!/usr/bin/env python3
"""
Regression Test Selector

Select regression tests based on SIL level and changed artifacts.

Usage:
    python3 tools/regression_test_selector.py \\
      --sil 2 \\
      --changed-artifacts REQ-PROJ-001,DES-PROJ-010 \\
      --rtm-file docs/traceability/requirements_traceability_matrix.md \\
      --output regression_tests.txt
"""

import argparse
import sys
from pathlib import Path

class RegressionTestSelector:
    def __init__(self, rtm_file, sil_level):
        self.rtm_file = Path(rtm_file)
        self.sil_level = sil_level
        self.rtm = self.load_rtm()
    
    def load_rtm(self):
        """Load RTM from file."""
        # Simplified: In production, parse structured RTM
        return {}
    
    def select_tests(self, changed_artifacts):
        """
        Select regression tests based on SIL level.
        
        Args:
            changed_artifacts: List of changed artifact IDs
            
        Returns:
            Set of test IDs to execute
        """
        if self.sil_level in [3, 4]:
            # SIL 3-4: ALWAYS full regression suite
            return self._get_all_tests()
        elif self.sil_level == 2:
            # SIL 2: Affected + related tests
            return self._select_affected_and_related(changed_artifacts)
        elif self.sil_level == 1:
            # SIL 1: Affected tests only
            return self._select_affected_only(changed_artifacts)
        else:
            # SIL 0: Optional (recommend affected tests)
            return self._select_affected_only(changed_artifacts)
    
    def _get_all_tests(self):
        """Get ALL tests from RTM (full regression)."""
        all_tests = set()
        # Iterate through RTM and collect all test IDs
        # (Implementation omitted for brevity)
        return all_tests
    
    def _select_affected_only(self, changed_artifacts):
        """Select only directly affected tests."""
        affected_tests = set()
        
        for artifact in changed_artifacts:
            # Trace from artifact to tests
            tests = self._trace_to_tests(artifact)
            affected_tests.update(tests)
        
        return affected_tests
    
    def _select_affected_and_related(self, changed_artifacts):
        """Select affected tests + related tests (1 hop)."""
        tests = set()
        
        # 1. Directly affected tests
        tests.update(self._select_affected_only(changed_artifacts))
        
        # 2. Related tests (1 hop)
        related_artifacts = set()
        for artifact in changed_artifacts:
            related = self._find_related_artifacts(artifact, hops=1)
            related_artifacts.update(related)
        
        for artifact in related_artifacts:
            related_tests = self._trace_to_tests(artifact)
            tests.update(related_tests)
        
        return tests
    
    def _trace_to_tests(self, artifact_id):
        """Trace from artifact to tests via RTM."""
        tests = set()
        # Walk RTM graph from artifact to tests
        # (Implementation omitted for brevity)
        return tests
    
    def _find_related_artifacts(self, artifact_id, hops):
        """Find related artifacts (same module, same feature)."""
        related = set()
        # Find artifacts related to artifact_id within 'hops' hops
        # (Implementation omitted for brevity)
        return related


def main():
    parser = argparse.ArgumentParser(description='Select regression tests')
    parser.add_argument('--sil', type=int, required=True, choices=[0,1,2,3,4])
    parser.add_argument('--changed-artifacts', required=True, 
                        help='Comma-separated list of changed artifact IDs')
    parser.add_argument('--rtm-file', required=True, help='RTM file path')
    parser.add_argument('--output', required=True, help='Output file (test list)')
    
    args = parser.parse_args()
    
    # Parse changed artifacts
    changed_artifacts = args.changed_artifacts.split(',')
    
    # Select tests
    selector = RegressionTestSelector(args.rtm_file, args.sil)
    tests = selector.select_tests(changed_artifacts)
    
    # Write test list
    with open(args.output, 'w') as f:
        for test_id in sorted(tests):
            f.write(f"{test_id}\n")
    
    print(f"Selected {len(tests)} regression tests (SIL {args.sil})")
    print(f"Test list written to {args.output}")


if __name__ == '__main__':
    main()
```

---

## Example Scenarios

### Scenario 1: Requirements Change from Validation Feedback (SIL 3)

**Context**:
- Project: Railway Door Control System (SIL 3)
- Phase: Validation (Phase 6)
- Issue: System testing reveals missing requirement for audible alert on timeout

**Step-by-Step Iteration**:

```bash
# ============================================
# STEP 1: VAL detects missing requirement
# ============================================
@val validate-system

# VAL output:
# ❌ System Test Failed: TEST-SYS-025
# Test: Door timeout behavior
# Expected: Audible alert on timeout
# Actual: No alert provided
# 
# ROOT CAUSE: Missing requirement for audible alert
# RECOMMENDATION: Add requirement to Software Requirements Specification

# ============================================
# STEP 2: VAL creates change request
# ============================================
# VAL creates CR-DOOR-0001
# Category: Requirements Change
# Trigger Phase: validation
# Target Phase: requirements
# Reason: System testing revealed missing requirement for audible alert

# ============================================
# STEP 3: Impact analysis
# ============================================
python3 tools/cr_impact_analyzer.py \
  --cr-id CR-DOOR-0001 \
  --affected-req NEW \
  --change-type add \
  --rtm-file docs/traceability/requirements_traceability_matrix.md

# Output:
# CR Impact Analysis Report
# ========================
# CR ID: CR-DOOR-0001
# Affected Artifact: NEW (REQ-DOOR-025 to be created)
# Change Type: add
#
# Downstream Impact:
#   - Requirements: 1 new requirement
#   - Design: 1 new design element (estimated)
#   - Code: ~50 LOC (estimated)
#   - Tests: 2 new tests (unit + integration)
#
# Regression Tests (SIL 3 = FULL SUITE): 25 tests
#
# Effort Estimate:
#   requirements: 4 hours
#   design: 6 hours
#   implementation: 8 hours
#   testing: 50 hours (full regression)
#   verification: 4 hours
#   total: 72 hours

# ============================================
# STEP 4: CCB review and approval
# ============================================
# CCB Meeting: 2026-03-11
# Members: PM, QUA, CM, SAF, VER
# 
# CCB Decision: APPROVED
# Safety Review: SAF approves (low safety impact, but required for compliance)
# 
# CR-DOOR-0001 status: APPROVED

# ============================================
# STEP 5: COD authorizes iteration
# ============================================
@cod start-iteration \
  --cr-id CR-DOOR-0001 \
  --trigger-phase validation \
  --target-phase requirements \
  --reason "Add missing requirement for audible alert"

# COD updates LIFECYCLE_STATE.md:
# iterations:
#   - iteration_id: ITER-001
#     cr_id: CR-DOOR-0001
#     start_date: "2026-03-11"
#     trigger_phase: validation
#     target_phase: requirements
#     iteration_scope: [requirements, design, implementation, integration, validation]
#     status: IN_PROGRESS

# ============================================
# STEP 6: REQ adds new requirement
# ============================================
@req add-requirement

# REQ creates REQ-DOOR-025:
# ID: REQ-DOOR-025
# Title: Audible Alert on Door Timeout
# Description: The door controller shall provide an audible alert 
#              when door closing exceeds timeout threshold (3 seconds).
# SIL: 3
# Rationale: User safety - alert passengers to door issue

# REQ updates Software Requirements Specification (SRS v1.1)

# REQ updates traceability:
workspace.py trace add-requirement \
  --req-id REQ-DOOR-025 \
  --description "Audible alert on timeout" \
  --sil 3 \
  --iteration ITER-001

workspace.py trace link \
  --from SYSTEM-REQ-010 \
  --to REQ-DOOR-025 \
  --type requirements

# ============================================
# STEP 7: DES designs implementation
# ============================================
@des design-requirement --req-id REQ-DOOR-025

# DES creates DES-DOOR-030:
# Design Element: Alert Controller
# Module: alert_controller.c
# Function: trigger_alert(alert_type_t type)
# Interface: Called by door_control.c when timeout detected

# DES updates Software Architecture Specification (SAS v1.1)

# DES updates traceability:
workspace.py trace link \
  --from REQ-DOOR-025 \
  --to DES-DOOR-030 \
  --type design

# ============================================
# STEP 8: IMP implements code
# ============================================
@imp implement-design --design-id DES-DOOR-030

# IMP creates alert_controller.c:
# - trigger_alert() function
# - alert_type_t enum (TIMEOUT_ALERT, ERROR_ALERT, etc.)
# - Hardware interface to buzzer

# IMP modifies door_control.c:
# - Line 150: Add timeout detection
# - Line 155: Call trigger_alert(TIMEOUT_ALERT) on timeout

# IMP creates unit tests:
# - TEST-DOOR-080: test_trigger_alert_timeout()
# - TEST-DOOR-081: test_trigger_alert_error()

# IMP updates traceability:
workspace.py trace link \
  --from DES-DOOR-030 \
  --to src/alert_controller.c:50 \
  --type implementation

workspace.py trace link \
  --from src/alert_controller.c:50 \
  --to TEST-DOOR-080 \
  --type unit_test

# ============================================
# STEP 9: TST executes unit tests
# ============================================
@tst run-unit-tests

# TST output:
# ✓ TEST-DOOR-080: test_trigger_alert_timeout() - PASS
# ✓ TEST-DOOR-081: test_trigger_alert_error() - PASS
#
# Unit test coverage: 100% (lines: 1250/1250, branches: 520/520)

# ============================================
# STEP 10: INT executes integration tests
# ============================================
@int run-integration-tests

# INT creates integration test:
# - TEST-INT-050: Door timeout with alert integration test

# INT output:
# ✓ TEST-INT-050: Door timeout with alert - PASS
#
# Integration test coverage: 100%

# ============================================
# STEP 11: Regression testing (SIL 3 = FULL)
# ============================================
python3 tools/regression_test_selector.py \
  --sil 3 \
  --changed-artifacts REQ-DOOR-025,DES-DOOR-030,src/alert_controller.c \
  --rtm-file docs/traceability/requirements_traceability_matrix.md \
  --output regression_tests.txt

# Output: 25 tests (ALL tests - full regression)

./scripts/run_regression_tests.sh regression_tests.txt

# Regression test results:
# Tests Executed: 25
# Tests Passed: 25
# Tests Failed: 0
# Pass Rate: 100%

# ============================================
# STEP 12: QUA reviews iteration artifacts
# ============================================
@qua review-iteration --iteration-id ITER-001

# QUA reviews:
# - SRS v1.1 (REQ-DOOR-025 added)
# - SAS v1.1 (DES-DOOR-030 added)
# - Code: alert_controller.c, door_control.c (MISRA C compliant)
# - Tests: TEST-DOOR-080, TEST-DOOR-081, TEST-INT-050 (all pass)
# - RTM updated (traceability complete)

# QUA result: APPROVED

# ============================================
# STEP 13: VER verifies iteration
# ============================================
@ver verify-iteration --iteration-id ITER-001

# VER checks:
# - Traceability: 100% complete
# - Coverage: 100% (statement, branch, condition)
# - MISRA C: 0 mandatory violations
# - Complexity: Max CCN = 8 (within limit of 10)
# - Static analysis: 0 critical issues

# VER result: APPROVED

# ============================================
# STEP 14: VAL re-validates system
# ============================================
@val validate-iteration --iteration-id ITER-001

# VAL re-executes system tests:
# ✓ TEST-SYS-025: Door timeout with audible alert - PASS (WAS FAIL)
# ✓ All other system tests: PASS

# VAL result: APPROVED (Iteration resolves original issue)

# ============================================
# STEP 15: COD completes iteration
# ============================================
@cod complete-iteration --iteration-id ITER-001

# COD checks:
# ✓ All iteration scope phases complete
# ✓ Traceability validated
# ✓ Regression tests passed (25/25)
# ✓ QUA approved
# ✓ VER approved
# ✓ VAL approved

# COD updates LIFECYCLE_STATE.md:
# iterations:
#   - iteration_id: ITER-001
#     cr_id: CR-DOOR-0001
#     start_date: "2026-03-11"
#     end_date: "2026-03-15"
#     status: COMPLETE
#     artifacts_updated: [REQ-DOOR-025, DES-DOOR-030, src/alert_controller.c, ...]
#     regression_tests_passed: 25
#     traceability_validated: true

# phases:
#   validation:
#     status: COMPLETE  (restored)
#     baseline: v1.1.0  (new baseline)

# COD output:
# ✓ Iteration ITER-001 COMPLETE
# ✓ Ready to proceed to Assessment phase (SIL 3)
```

---

### Scenario 2: Design Iteration from Implementation Feedback (SIL 2)

**Context**:
- Project: Railway Signal Controller (SIL 2)
- Phase: Implementation (Phase 4)
- Issue: Code reveals interface mismatch in design

**Step-by-Step Iteration**:

```bash
# ============================================
# STEP 1: IMP detects interface mismatch
# ============================================
@imp implement-design --design-id DES-SIGNAL-015

# IMP output:
# ❌ Implementation Error: Interface mismatch
# Design: DES-SIGNAL-015 specifies signal_state_t with 3 states
# Implementation: Hardware interface requires 5 states
# 
# ROOT CAUSE: Design specification incomplete
# RECOMMENDATION: Update design to include all hardware states

# ============================================
# STEP 2: IMP creates change request
# ============================================
# IMP creates CR-SIGNAL-0005
# Category: Design Change
# Trigger Phase: implementation
# Target Phase: design
# Reason: Interface mismatch - design incomplete

# ============================================
# STEP 3: Impact analysis (SIL 2)
# ============================================
python3 tools/cr_impact_analyzer.py \
  --cr-id CR-SIGNAL-0005 \
  --affected-req DES-SIGNAL-015 \
  --change-type modify \
  --rtm-file docs/traceability/requirements_traceability_matrix.md

# Output:
# Downstream Impact:
#   - Design: DES-SIGNAL-015 (modify)
#   - Code: src/signal_interface.c (modify)
# Regression Tests (SIL 2 = Affected + Related): 8 tests

# ============================================
# STEP 4: CCB approval (SIL 2)
# ============================================
# CCB: PM, QUA, CM
# Decision: APPROVED
# Safety Review: Not required (SIL 2 - recommended but not mandatory)

# ============================================
# STEP 5: COD authorizes iteration
# ============================================
@cod start-iteration \
  --cr-id CR-SIGNAL-0005 \
  --trigger-phase implementation \
  --target-phase design \
  --reason "Interface mismatch - design update required"

# Iteration scope: [design, implementation]

# ============================================
# STEP 6: DES updates design
# ============================================
@des update-design --design-id DES-SIGNAL-015

# DES modifies DES-SIGNAL-015:
# - signal_state_t enum: 3 states → 5 states
# - Update state machine diagram
# - Update interface specification

# DES updates Software Design Specification (SDS v1.2)

# ============================================
# STEP 7: IMP updates code
# ============================================
@imp implement-design --design-id DES-SIGNAL-015

# IMP modifies src/signal_interface.c:
# - Update signal_state_t enum (5 states)
# - Update state machine logic
# - Update unit tests

# ============================================
# STEP 8: Regression testing (SIL 2 = Affected + Related)
# ============================================
python3 tools/regression_test_selector.py \
  --sil 2 \
  --changed-artifacts DES-SIGNAL-015,src/signal_interface.c \
  --rtm-file docs/traceability/requirements_traceability_matrix.md \
  --output regression_tests.txt

# Output: 8 tests (affected + related, NOT full suite)

./scripts/run_regression_tests.sh regression_tests.txt

# Results: 8/8 PASS

# ============================================
# STEP 9: VER verifies, COD completes
# ============================================
@ver verify-iteration --iteration-id ITER-005
@cod complete-iteration --iteration-id ITER-005

# Iteration complete (duration: 2 days, effort: 20 hours)
```

---

## Summary

This workflow provides comprehensive guidance for **iteration and change management** throughout the EN 50128 lifecycle:

1. **Iteration Principles** - EN 50128 explicitly allows iterations (Section 5.3.2.2) with proper change control
2. **Feedback Loop Detection** - Algorithm to determine target phase and iteration scope based on issue type
3. **Change Request Process** - Formal CR workflow with CCB approval (SIL-dependent)
4. **Iteration Execution** - Step-by-step process to return to target phase, update artifacts, and restore quality
5. **Regression Testing** - SIL-dependent test selection (full regression for SIL 3-4, affected + related for SIL 2)
6. **Traceability Updates** - Maintain RTM bidirectional links throughout iteration (MANDATORY SIL 2+)
7. **LIFECYCLE_STATE.md** - Track all iterations for audit trail and lifecycle transparency
8. **Tool Integration** - Complete workspace.py trace/wf command examples for iteration management
9. **Automation Scripts** - CR impact analyzer and regression test selector for efficiency
10. **Example Scenarios** - Complete SIL 3 and SIL 2 iteration walkthroughs

**Key Takeaways**:

- **Iterations ARE allowed** in EN 50128 lifecycle (Section 5.3.2.2)
- **Change control IS required** for all iterations (formal CR process for SIL 2+)
- **Traceability MUST be maintained** through iterations (MANDATORY SIL 2+, gaps MUST be resolved)
- **Regression testing IS mandatory** (full suite for SIL 3-4, affected + related for SIL 2)
- **COD orchestrates** iterations and ensures completion criteria met before proceeding
- **LIFECYCLE_STATE.md records** all iterations for audit and transparency

This workflow enables COD to manage iterations effectively while maintaining EN 50128 compliance and safety integrity.
