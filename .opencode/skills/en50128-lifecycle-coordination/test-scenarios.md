# COD Test Scenarios

This document defines comprehensive test scenarios for the **Lifecycle Coordinator (COD)** agent to verify correct behavior across all SIL levels and lifecycle phases.

---

## Test Scenario Categories

1. **Initialization Tests** - COD project setup
2. **Phase Gate Tests** - Gate enforcement by SIL level
3. **User Approval Tests** - Requirements approval workflow
4. **Independence Tests** - Validator/Assessor independence verification
5. **Traceability Tests** - RTM completeness checks
6. **Status Monitoring Tests** - Lifecycle state tracking
7. **Change Management Tests** - Change request handling
8. **Error Handling Tests** - Invalid operations and edge cases

---

## 1. Initialization Tests

### Test 1.1: Successful COD Initialization (SIL 3)

**Objective**: Verify COD correctly initializes lifecycle tracking for a SIL 3 project.

**Preconditions**:
- Clean project directory: `examples/test_project_sil3/`
- No existing LIFECYCLE_STATE.md

**Test Steps**:
```bash
# 1. Navigate to project directory
cd examples/test_project_sil3/

# 2. Initialize COD
/cod plan --sil 3 --project test_project_sil3
```

**Expected Results**:
- ✅ LIFECYCLE_STATE.md created in `examples/test_project_sil3/`
- ✅ File contains:
  - Project name: test_project_sil3
  - SIL level: 3
  - Enforcement mode: Strict Gatekeeper
  - Current phase: Phase 0 (Initialization)
  - All 8 phase gates listed with status "PENDING"
  - Empty agent activity log
- ✅ COD responds: "Lifecycle tracking initialized for test_project_sil3 (SIL 3 - Strict Mode)"

**Pass Criteria**: LIFECYCLE_STATE.md created with correct structure and initial state.

---

### Test 1.2: COD Initialization with All SIL Levels

**Objective**: Verify COD correctly sets enforcement mode based on SIL level.

**Test Cases**:

| SIL | Project Name | Expected Mode | Expected Behavior |
|-----|--------------|---------------|-------------------|
| 0 | test_sil0 | Advisory | Warnings only, no blocking |
| 1 | test_sil1 | Advisory | Warnings only, no blocking |
| 2 | test_sil2 | Semi-strict | Requires justification for violations |
| 3 | test_sil3 | Strict Gatekeeper | BLOCKS transitions until criteria met |
| 4 | test_sil4 | Strict Gatekeeper | BLOCKS transitions until criteria met |

**Test Steps** (for each SIL):
```bash
cd examples/test_sil{0..4}/
/cod plan --sil {0..4} --project test_sil{0..4}
# Verify LIFECYCLE_STATE.md enforcement mode
```

**Pass Criteria**: Each project has correct enforcement mode in LIFECYCLE_STATE.md.

---

### Test 1.3: COD Re-initialization Protection

**Objective**: Verify COD prevents re-initialization of an existing project.

**Preconditions**:
- LIFECYCLE_STATE.md already exists in `examples/test_project_sil3/`

**Test Steps**:
```bash
cd examples/test_project_sil3/
/cod plan --sil 3 --project test_project_sil3
```

**Expected Results**:
- ❌ COD responds: "ERROR: LIFECYCLE_STATE.md already exists for test_project_sil3. Project already initialized."
- ❌ COD suggests: "Use `/cod status` to view current state or delete LIFECYCLE_STATE.md to re-initialize."
- ✅ Existing LIFECYCLE_STATE.md NOT modified

**Pass Criteria**: COD blocks re-initialization and preserves existing state.

---

## 2. Phase Gate Tests

### Test 2.1: Planning Gate - SIL 3 Strict Blocking

**Objective**: Verify COD blocks Requirements phase when planning gate criteria not met (SIL 3).

**Preconditions**:
- Project initialized: SIL 3, Phase 1 (Planning)
- Planning deliverables NOT complete

**Test Steps**:
```bash
# 1. Initialize project
/cod plan --sil 3 --project test_gate_sil3

# 2. Attempt to invoke requirements WITHOUT completing planning
/req
```

**Expected Results**:
- ❌ COD intercepts `/req` invocation
- ❌ COD responds: "BLOCKED: Planning phase gate NOT passed. Requirements phase cannot begin."
- ❌ COD displays missing criteria:
  ```
  Planning Gate Checklist:
  ❌ SQAP not approved
  ❌ SCMP not approved
  ❌ SVP not approved
  ❌ SVaP not approved
  ```
- ❌ `/req` NOT executed
- ✅ COD suggests: "Complete planning deliverables and run `/cod gate-check planning` before proceeding."

**Pass Criteria**: COD blocks out-of-sequence activity for SIL 3.

---

### Test 2.2: Planning Gate - SIL 1 Advisory Only

**Objective**: Verify COD allows Requirements phase with warnings only (SIL 1).

**Preconditions**:
- Project initialized: SIL 1, Phase 1 (Planning)
- Planning deliverables NOT complete

**Test Steps**:
```bash
# 1. Initialize project
/cod plan --sil 1 --project test_gate_sil1

# 2. Attempt to invoke requirements WITHOUT completing planning
/req
```

**Expected Results**:
- ⚠️ COD intercepts `/req` invocation
- ⚠️ COD responds: "WARNING: Planning phase gate not passed. Proceeding with advisory mode (SIL 1)."
- ⚠️ COD displays missing criteria (same as SIL 3)
- ✅ `/req` IS executed (advisory mode allows override)
- ⚠️ COD logs warning in LIFECYCLE_STATE.md

**Pass Criteria**: COD allows activity with warnings for SIL 1.

---

### Test 2.3: Planning Gate - SIL 2 Justification Required

**Objective**: Verify COD requires justification for bypassing gate (SIL 2).

**Preconditions**:
- Project initialized: SIL 2, Phase 1 (Planning)
- Planning deliverables NOT complete

**Test Steps**:
```bash
# 1. Initialize project
/cod plan --sil 2 --project test_gate_sil2

# 2. Attempt to invoke requirements WITHOUT completing planning
/req
```

**Expected Results**:
- ⚠️ COD intercepts `/req` invocation
- ⚠️ COD responds: "SEMI-STRICT MODE: Planning phase gate not passed. Justification required to proceed."
- ⚠️ COD prompts: "Provide justification for bypassing gate (or 'cancel' to abort):"
- 🔄 User provides justification: "Early prototyping for feasibility study"
- ✅ COD logs justification in LIFECYCLE_STATE.md
- ✅ `/req` IS executed after justification provided

**Pass Criteria**: COD requires and logs justification for SIL 2.

---

### Test 2.4: Planning Gate - Successful Gate Check (SIL 3)

**Objective**: Verify COD correctly passes planning gate when all criteria met.

**Preconditions**:
- Project initialized: SIL 3, Phase 1 (Planning)
- All planning deliverables complete and approved

**Test Steps**:
```bash
# 1. Simulate planning completion
# (Create SQAP, SCMP, SVP, SVaP documents)

# 2. Update LIFECYCLE_STATE.md to mark deliverables complete

# 3. Request gate check
/cod gate-check planning
```

**Expected Results**:
- ✅ COD verifies all planning deliverables present
- ✅ COD verifies all documents approved
- ✅ COD updates LIFECYCLE_STATE.md:
  - Planning gate status: PASSED
  - Gate pass timestamp recorded
  - Current phase updated to: Phase 2 (Requirements)
- ✅ COD responds: "✅ Planning gate PASSED. Requirements phase authorized. Current phase: Requirements."

**Pass Criteria**: COD authorizes phase transition after gate criteria met.

---

### Test 2.5: Requirements Gate - User Approval Verification (SIL 3)

**Objective**: Verify COD checks user approval for requirement activities.

**Preconditions**:
- Project initialized: SIL 3, Phase 2 (Requirements)
- Planning gate PASSED
- User approval NOT obtained

**Test Steps**:
```bash
# 1. Request requirements gate check without user approval
/cod gate-check requirements
```

**Expected Results**:
- ❌ COD verifies requirements gate checklist
- ❌ COD detects missing user approval
- ❌ COD responds: "FAILED: User approval not obtained for requirement activities."
- ❌ Gate status remains: PENDING
- ❌ COD displays:
  ```
  Requirements Gate Checklist:
  ✅ SRS complete
  ✅ RTM complete
  ✅ Hazard analysis complete
  ❌ USER APPROVAL not obtained
  ```

**Pass Criteria**: COD enforces user approval requirement.

---

### Test 2.6: Implementation Gate - MISRA C Compliance Check (SIL 3)

**Objective**: Verify COD checks MISRA C compliance before passing implementation gate.

**Preconditions**:
- Project initialized: SIL 3, Phase 4 (Implementation)
- Design gate PASSED
- Code complete but MISRA C violations present

**Test Steps**:
```bash
# 1. Simulate implementation with MISRA C violations
# (Code has 5 mandatory violations)

# 2. Request gate check
/cod gate-check implementation
```

**Expected Results**:
- ❌ COD verifies MISRA C compliance report
- ❌ COD detects mandatory violations
- ❌ COD responds: "FAILED: MISRA C mandatory violations detected (5 violations). ZERO mandatory violations required for SIL 3."
- ❌ Gate status remains: PENDING
- ❌ COD displays violation summary

**Pass Criteria**: COD blocks gate passage with MISRA C violations.

---

### Test 2.7: Implementation Gate - Coverage Check (SIL 3)

**Objective**: Verify COD checks code coverage requirements for SIL 3.

**Preconditions**:
- Project initialized: SIL 3, Phase 4 (Implementation)
- MISRA C compliant
- Coverage: 98% statement, 95% branch, 90% condition

**Test Steps**:
```bash
# 1. Request gate check with incomplete coverage
/cod gate-check implementation
```

**Expected Results**:
- ❌ COD verifies coverage report
- ❌ COD detects insufficient coverage
- ❌ COD responds: "FAILED: Coverage requirements not met for SIL 3."
- ❌ COD displays:
  ```
  Coverage Requirements (SIL 3):
  ✅ Statement: 98% (target: 100%) - PASS
  ❌ Branch: 95% (target: 100%) - FAIL
  ❌ Condition: 90% (target: 100%) - FAIL
  ```

**Pass Criteria**: COD enforces 100% statement/branch/condition coverage for SIL 3.

---

### Test 2.8: Validation Gate - Independence Verification (SIL 3)

**Objective**: Verify COD checks validator independence before passing validation gate.

**Preconditions**:
- Project initialized: SIL 3, Phase 6 (Validation)
- Integration gate PASSED
- Validator reports to PM (VIOLATION)

**Test Steps**:
```bash
# 1. Request validation gate check
/cod gate-check validation
```

**Expected Results**:
- ❌ COD verifies validator independence
- ❌ COD detects independence violation
- ❌ COD responds: "CRITICAL FAILURE: Validator independence violation detected (SIL 3)."
- ❌ COD displays: "Validator MUST NOT report to Project Manager per EN 50128 Section 5.1.2.10.f"
- ❌ Gate status: FAILED (not just PENDING)
- 🚨 COD recommends: "Reassign validator to independent reporting structure before proceeding."

**Pass Criteria**: COD enforces validator independence for SIL 3.

---

### Test 2.9: Assessment Gate - Final Release Authorization (SIL 3)

**Objective**: Verify COD performs comprehensive checks before authorizing deployment.

**Preconditions**:
- Project initialized: SIL 3, Phase 8 (Assessment)
- All previous gates PASSED
- All deliverables complete

**Test Steps**:
```bash
# 1. Request assessment gate check
/cod gate-check assessment
```

**Expected Results**:
- ✅ COD verifies ALL lifecycle phases complete
- ✅ COD verifies end-to-end traceability (RTM complete)
- ✅ COD verifies all deliverables present per SIL 3
- ✅ COD verifies assessor independence
- ✅ COD verifies approval certificate obtained
- ✅ COD updates LIFECYCLE_STATE.md:
  - Assessment gate status: PASSED
  - ALL 7 phase gates marked PASSED
  - Project status: READY FOR DEPLOYMENT
- ✅ COD responds: "✅ Assessment gate PASSED. Deployment authorized. Project complete."

**Pass Criteria**: COD authorizes deployment after all gates passed.

---

## 3. User Approval Tests

### Test 3.1: Requirements User Approval - First Invocation

**Objective**: Verify COD prompts for user approval when `/req` first invoked.

**Preconditions**:
- Project initialized: SIL 3, Phase 2 (Requirements)
- Planning gate PASSED
- No prior requirement activities

**Test Steps**:
```bash
# 1. Invoke requirements agent
/req
```

**Expected Results**:
- 🔄 COD intercepts `/req` invocation
- 🔄 COD prompts: "Requirement activity requires explicit user approval. Approve? [Y/N]"
- 🔄 User responds: Y
- ✅ COD logs approval in LIFECYCLE_STATE.md with timestamp
- ✅ COD allows `/req` to proceed
- ✅ COD responds: "User approval granted. Requirements activity authorized."

**Pass Criteria**: COD enforces user approval workflow.

---

### Test 3.2: Requirements User Approval - Denial

**Objective**: Verify COD blocks `/req` when user denies approval.

**Preconditions**: Same as Test 3.1

**Test Steps**:
```bash
# 1. Invoke requirements agent
/req

# 2. User denies approval
# Response: N
```

**Expected Results**:
- 🔄 COD intercepts `/req` invocation
- 🔄 COD prompts for approval
- 🔄 User responds: N
- ❌ COD responds: "User approval DENIED. Requirements activity blocked."
- ❌ `/req` NOT executed
- ❌ Denial logged in LIFECYCLE_STATE.md

**Pass Criteria**: COD blocks activity when approval denied.

---

### Test 3.3: Requirements Modification - Approval Required Again

**Objective**: Verify COD requires approval for requirement modifications after baseline.

**Preconditions**:
- Project initialized: SIL 3, Phase 4 (Implementation)
- Requirements baseline established
- User attempts to modify requirements

**Test Steps**:
```bash
# 1. Invoke requirements agent to modify baseline
/req
```

**Expected Results**:
- 🔄 COD intercepts `/req` invocation
- 🔄 COD detects: Requirements baseline exists (Phase > Requirements)
- 🔄 COD prompts: "Requirements baseline modification requires explicit approval. Approve? [Y/N]"
- 🔄 COD warns: "This will trigger change control and require traceability updates."
- 🔄 User responds: Y
- ✅ COD logs baseline modification approval
- ✅ COD allows `/req` to proceed
- ⚠️ COD flags: Change control required (CCB review)

**Pass Criteria**: COD enforces approval for baseline modifications.

---

## 4. Independence Tests

### Test 4.1: Validator Independence - Correct Setup (SIL 3)

**Objective**: Verify COD correctly validates independent validator setup.

**Preconditions**:
- Project initialized: SIL 3, Phase 6 (Validation)
- Validator assigned independently (does NOT report to PM)

**Test Steps**:
```bash
# 1. COD performs validation gate independence check
/cod gate-check validation
```

**Expected Results**:
- ✅ COD verifies validator role assignment
- ✅ COD verifies validator reporting structure
- ✅ COD confirms: Validator does NOT report to PM
- ✅ Independence check: PASSED
- ✅ COD logs: "Validator independence verified (SIL 3 compliant)"

**Pass Criteria**: COD correctly validates proper independence.

---

### Test 4.2: Assessor Independence - Violation Detection (SIL 3)

**Objective**: Verify COD detects assessor independence violations.

**Preconditions**:
- Project initialized: SIL 3, Phase 8 (Assessment)
- Assessor assigned within project team (VIOLATION)

**Test Steps**:
```bash
# 1. Request assessment gate check
/cod gate-check assessment
```

**Expected Results**:
- ❌ COD verifies assessor independence
- ❌ COD detects: Assessor within project organization
- 🚨 COD responds: "CRITICAL FAILURE: Assessor independence violation (SIL 3)."
- ❌ COD displays: "Assessor MUST be completely independent per EN 50128 Section 5.3.8"
- ❌ Gate status: FAILED
- 🚨 COD blocks: Deployment authorization withheld

**Pass Criteria**: COD blocks deployment with assessor independence violation.

---

### Test 4.3: Verifier Independence - SIL 2 Warning

**Objective**: Verify COD warns about verifier independence for SIL 2.

**Preconditions**:
- Project initialized: SIL 2, Phase 4 (Implementation)
- Verifier is also implementer (same person)

**Test Steps**:
```bash
# 1. Request implementation gate check
/cod gate-check implementation
```

**Expected Results**:
- ⚠️ COD verifies verifier independence
- ⚠️ COD detects: Verifier = Implementer (same person)
- ⚠️ COD responds: "WARNING: Verifier independence highly recommended for SIL 2."
- ⚠️ COD prompts: "Provide justification for non-independent verifier:"
- 🔄 User provides justification
- ✅ COD logs justification
- ✅ Gate check proceeds (semi-strict mode for SIL 2)

**Pass Criteria**: COD warns but allows with justification for SIL 2.

---

## 5. Traceability Tests

### Test 5.1: Requirements Traceability - Gap Detection

**Objective**: Verify COD detects gaps in requirements traceability matrix.

**Preconditions**:
- Project initialized: SIL 3, Phase 2 (Requirements)
- SRS has 50 requirements
- RTM traces only 45 requirements

**Test Steps**:
```bash
# 1. Request requirements gate check
/cod gate-check requirements
```

**Expected Results**:
- ❌ COD analyzes RTM completeness
- ❌ COD detects: 5 requirements not traced
- ❌ COD responds: "FAILED: Requirements traceability incomplete."
- ❌ COD displays:
  ```
  Traceability Analysis:
  - Total requirements: 50
  - Traced requirements: 45
  - Missing traces: 5
  
  Untraced requirements:
  - REQ-FUNC-023
  - REQ-FUNC-034
  - REQ-SAFE-007
  - REQ-PERF-019
  - REQ-IF-012
  ```
- ❌ Gate status: PENDING

**Pass Criteria**: COD detects and reports traceability gaps.

---

### Test 5.2: Design Traceability - Bidirectional Check

**Objective**: Verify COD checks bidirectional traceability (requirements ↔ design).

**Preconditions**:
- Project initialized: SIL 3, Phase 3 (Design)
- Forward traceability complete (requirements → design)
- Backward traceability incomplete (design → requirements)

**Test Steps**:
```bash
# 1. Request design gate check
/cod gate-check design
```

**Expected Results**:
- ⚠️ COD verifies forward traceability: COMPLETE
- ❌ COD verifies backward traceability: INCOMPLETE
- ❌ COD responds: "FAILED: Bidirectional traceability not complete."
- ❌ COD displays:
  ```
  Traceability Analysis:
  ✅ Forward (REQ → DES): Complete
  ❌ Backward (DES → REQ): 3 design modules not traced
  
  Orphaned design modules:
  - DES-MOD-045
  - DES-MOD-067
  - DES-IF-023
  ```

**Pass Criteria**: COD enforces bidirectional traceability.

---

### Test 5.3: End-to-End Traceability - Assessment Check

**Objective**: Verify COD validates complete end-to-end traceability at assessment.

**Preconditions**:
- Project initialized: SIL 3, Phase 8 (Assessment)
- All lifecycle phases complete

**Test Steps**:
```bash
# 1. Request assessment gate check
/cod gate-check assessment
```

**Expected Results**:
- ✅ COD verifies complete traceability chain:
  - Requirements → Design: Complete
  - Design → Code: Complete
  - Code → Unit Tests: Complete
  - Requirements → Integration Tests: Complete
  - Requirements → Validation Tests: Complete
- ✅ COD verifies bidirectional links present
- ✅ COD logs: "End-to-end traceability verified (100% coverage)"

**Pass Criteria**: COD validates complete traceability at final gate.

---

## 6. Status Monitoring Tests

### Test 6.1: Status Check - Early Phase

**Objective**: Verify `/cod status` displays accurate project state early in lifecycle.

**Preconditions**:
- Project initialized: SIL 3, Phase 2 (Requirements)
- Planning gate PASSED
- Requirements in progress

**Test Steps**:
```bash
# 1. Request status
/cod status
```

**Expected Results**:
- ✅ COD displays:
  ```
  PROJECT: test_project_sil3
  SIL LEVEL: 3 (Strict Gatekeeper Mode)
  CURRENT PHASE: Phase 2 - Requirements
  
  PHASE GATE STATUS:
  ✅ Planning Gate: PASSED (2026-02-18 10:45)
  🔄 Requirements Gate: IN PROGRESS
  ⏸️  Design Gate: PENDING
  ⏸️  Implementation Gate: PENDING
  ⏸️  Integration Gate: PENDING
  ⏸️  Validation Gate: PENDING
  ⏸️  Assessment Gate: PENDING
  
  DELIVERABLES STATUS:
  ✅ SQAP: Approved
  ✅ SCMP: Approved
  ✅ SVP: Approved
  ✅ SVaP: Approved
  🔄 SRS: In Progress (60% complete)
  ⏸️  RTM: Not Started
  ⏸️  Hazard Log: Not Started
  
  OVERALL PROGRESS: 15%
  ```

**Pass Criteria**: COD displays accurate current state.

---

### Test 6.2: Status Check - Mid-Lifecycle

**Objective**: Verify status display at implementation phase with mixed gate results.

**Preconditions**:
- Project initialized: SIL 3, Phase 4 (Implementation)
- Gates passed: Planning, Requirements, Design
- Implementation in progress

**Test Steps**:
```bash
/cod status
```

**Expected Results**:
- ✅ COD displays all passed gates with timestamps
- ✅ COD highlights current phase (Implementation)
- ✅ COD shows deliverable completion percentages
- ✅ COD displays recent agent activity
- ✅ Overall progress: ~50%

**Pass Criteria**: Status reflects mid-lifecycle accurately.

---

### Test 6.3: Status Check - Near Completion

**Objective**: Verify status display when all gates passed except assessment.

**Preconditions**:
- Project initialized: SIL 3, Phase 8 (Assessment)
- All gates PASSED except Assessment

**Test Steps**:
```bash
/cod status
```

**Expected Results**:
- ✅ COD displays 6 of 7 gates PASSED
- 🔄 Assessment gate: IN PROGRESS
- ✅ Overall progress: 95%
- ✅ COD displays: "Ready for final assessment"

**Pass Criteria**: Status shows near-completion accurately.

---

## 7. Change Management Tests

### Test 7.1: Change Request During Design Phase

**Objective**: Verify COD handles requirement change during design phase.

**Preconditions**:
- Project initialized: SIL 3, Phase 3 (Design)
- Requirements baseline established
- User requests requirement change

**Test Steps**:
```bash
# 1. User invokes requirements modification
/req

# 2. COD detects baseline modification
# 3. User approves change
# 4. User makes requirement modification
```

**Expected Results**:
- 🔄 COD detects: Change to baselined requirements
- 🔄 COD prompts for user approval
- ✅ User approval obtained
- ⚠️ COD responds: "Change control required. Change request will be created."
- ⚠️ COD logs change in LIFECYCLE_STATE.md
- ⚠️ COD flags: Design traceability update required
- ⚠️ COD warns: Regression testing required

**Pass Criteria**: COD manages baseline change with proper workflow.

---

### Test 7.2: Traceability Update After Change

**Objective**: Verify COD tracks traceability updates after requirement change.

**Preconditions**:
- Requirement change made (from Test 7.1)
- Design phase active

**Test Steps**:
```bash
# 1. Attempt design gate check without updating traceability
/cod gate-check design
```

**Expected Results**:
- ❌ COD detects: Recent requirement change (REQ-FUNC-025 modified)
- ❌ COD verifies: Traceability not updated for changed requirement
- ❌ COD responds: "FAILED: Traceability not updated after requirement change."
- ❌ COD displays:
  ```
  Changed requirements without traceability update:
  - REQ-FUNC-025 (changed: 2026-02-18 14:30)
  ```
- ❌ COD suggests: "Update design to reflect changed requirement and update RTM."

**Pass Criteria**: COD enforces traceability updates after changes.

---

## 8. Error Handling Tests

### Test 8.1: Invalid SIL Level

**Objective**: Verify COD rejects invalid SIL values.

**Test Steps**:
```bash
/cod plan --sil 5 --project test_invalid
```

**Expected Results**:
- ❌ COD responds: "ERROR: Invalid SIL level '5'. Valid values: 0, 1, 2, 3, 4"
- ❌ Project NOT initialized

**Pass Criteria**: COD validates SIL input.

---

### Test 8.2: Invalid Phase for Gate Check

**Objective**: Verify COD rejects invalid phase names.

**Test Steps**:
```bash
/cod gate-check coding
```

**Expected Results**:
- ❌ COD responds: "ERROR: Invalid phase 'coding'. Valid phases: planning, requirements, design, implementation, integration, validation, assessment"

**Pass Criteria**: COD validates phase names.

---

### Test 8.3: Gate Check Without Initialization

**Objective**: Verify COD prevents gate check before project initialization.

**Preconditions**:
- No LIFECYCLE_STATE.md exists

**Test Steps**:
```bash
/cod gate-check planning
```

**Expected Results**:
- ❌ COD responds: "ERROR: No lifecycle state found. Initialize project first with `/cod plan --sil [0-4] --project [name]`"

**Pass Criteria**: COD requires initialization before operations.

---

### Test 8.4: Out-of-Order Gate Check

**Objective**: Verify COD prevents skipping phases (e.g., checking design gate before requirements).

**Preconditions**:
- Project initialized: SIL 3, Phase 1 (Planning)
- Planning gate NOT passed

**Test Steps**:
```bash
/cod gate-check design
```

**Expected Results**:
- ❌ COD responds: "ERROR: Cannot check Design gate. Previous gate (Requirements) not passed."
- ❌ COD displays gate sequence and current position
- ❌ COD suggests: "Complete Planning and Requirements phases first."

**Pass Criteria**: COD enforces phase sequence.

---

## 9. Integration Tests (Full Lifecycle)

### Test 9.1: Complete SIL 3 Lifecycle - Happy Path

**Objective**: Verify COD successfully manages a complete SIL 3 project lifecycle.

**Test Steps**:
```bash
# Phase 0: Initialization
/cod plan --sil 3 --project complete_test

# Phase 1: Planning
/pm   # Project setup
/cm   # Config management
/qua  # Quality assurance
/cod gate-check planning
# Expected: ✅ PASSED

# Phase 2: Requirements
/req  # User approval: Y
# Complete SRS, RTM, Hazard Log
/cod gate-check requirements
# Expected: ✅ PASSED

# Phase 3: Design
/des
# Complete SAS, SDS, ICD
/cod gate-check design
# Expected: ✅ PASSED

# Phase 4: Implementation
/imp
# Complete code, unit tests (100% coverage)
/cod gate-check implementation
# Expected: ✅ PASSED

# Phase 5: Integration
/int
# Complete integration tests
/cod gate-check integration
# Expected: ✅ PASSED

# Phase 6: Validation
/val  # Independent validator
# Complete validation tests, UAT
/cod gate-check validation
# Expected: ✅ PASSED (with independence check)

# Phase 7: Assessment
/qua  # Assessment
# Independent assessor review
/cod gate-check assessment
# Expected: ✅ PASSED (deployment authorized)

# Status Check
/cod status
# Expected: All gates PASSED, 100% complete
```

**Expected Final State**:
- All 7 phase gates: PASSED
- Project status: READY FOR DEPLOYMENT
- Deployment authorized: YES
- Overall progress: 100%

**Pass Criteria**: Complete lifecycle managed successfully with all gates passed.

---

### Test 9.2: Complete SIL 1 Lifecycle - Advisory Mode

**Objective**: Verify COD advisory mode for SIL 1 allows flexibility.

**Test Steps**: Similar to 9.1 but with incomplete deliverables

**Expected Results**:
- ⚠️ COD provides warnings throughout
- ✅ All agent invocations allowed (no blocking)
- ⚠️ Warnings logged in LIFECYCLE_STATE.md
- ✅ Project completes with warnings

**Pass Criteria**: Advisory mode works without blocking.

---

## 10. Regression Tests

### Test 10.1: Multiple Projects Simultaneously

**Objective**: Verify COD correctly manages multiple projects independently.

**Test Steps**:
```bash
# Project 1: SIL 3
cd examples/project1_sil3/
/cod plan --sil 3 --project project1_sil3
/cod status
# Expected: project1_sil3 state

# Project 2: SIL 2
cd examples/project2_sil2/
/cod plan --sil 2 --project project2_sil2
/cod status
# Expected: project2_sil2 state (different from project1)

# Return to Project 1
cd examples/project1_sil3/
/cod status
# Expected: project1_sil3 state (unchanged)
```

**Pass Criteria**: Each project maintains independent state.

---

## Test Summary

| Category | Total Tests | Critical Tests |
|----------|-------------|----------------|
| Initialization | 3 | 1 |
| Phase Gates | 9 | 5 |
| User Approval | 3 | 2 |
| Independence | 3 | 3 |
| Traceability | 3 | 2 |
| Status Monitoring | 3 | 0 |
| Change Management | 2 | 1 |
| Error Handling | 4 | 1 |
| Integration | 2 | 2 |
| Regression | 1 | 0 |
| **TOTAL** | **33** | **17** |

---

## Test Execution Guidelines

### Manual Testing
1. Create test project directories in `examples/`
2. Execute test steps sequentially
3. Verify expected results match actual behavior
4. Document any deviations

### Automated Testing (Future)
- Test framework: Python pytest
- Mock LIFECYCLE_STATE.md file operations
- Simulate agent invocations
- Verify COD responses and state updates

### Critical Path Tests (Must Pass)
Focus on critical tests (17 total) for release validation:
- Test 1.1: COD initialization
- Test 2.1: SIL 3 strict blocking
- Test 2.4: Successful gate check
- Test 2.5: User approval verification
- Test 2.6: MISRA C compliance
- Test 2.7: Coverage requirements
- Test 2.8: Independence verification
- Test 2.9: Final release authorization
- Test 3.1: User approval workflow
- Test 3.3: Baseline modification approval
- Test 4.1: Validator independence correct
- Test 4.2: Assessor independence violation
- Test 5.1: Traceability gap detection
- Test 7.1: Change request handling
- Test 8.3: Uninitialized project protection
- Test 9.1: Complete SIL 3 lifecycle
- Test 9.2: Complete SIL 1 lifecycle

---

**Document Version**: 1.0  
**Last Updated**: 2026-02-18  
**Status**: Ready for Execution
