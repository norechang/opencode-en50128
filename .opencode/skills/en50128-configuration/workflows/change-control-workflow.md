# Change Control Workflow for EN 50128 Configuration Management

**Document ID**: WF-CM-002  
**Version**: 1.0  
**Status**: Active  
**Skill**: en50128-configuration  
**Related Standard**: EN 50128:2011 Section 6.6.4

---

## Table of Contents

1. [Overview](#1-overview)
2. [EN 50128 Change Control Requirements](#2-en-50128-change-control-requirements)
3. [Change Request (CR) Process](#3-change-request-cr-process)
4. [Impact Analysis](#4-impact-analysis)
5. [Change Control Board (CCB)](#5-change-control-board-ccb)
6. [CR Implementation](#6-cr-implementation)
7. [Re-verification and Re-validation](#7-re-verification-and-re-validation)
8. [Baseline Update](#8-baseline-update)
9. [Tool Integration](#9-tool-integration)
10. [Automation Scripts](#10-automation-scripts)
11. [Example Scenarios](#11-example-scenarios)

---

## 1. Overview

### 1.1 Purpose

This workflow defines the formal **Change Request (CR)** process for EN 50128-compliant railway software development. Change control is **MANDATORY for ALL SIL levels** as part of Software Configuration Management (EN 50128 Table A.9 #5).

**Key Objectives**:
- Control all changes to configuration items (CIs)
- Assess impact before implementation
- Ensure traceability of all changes
- Maintain baseline integrity
- Enable audit trail for safety certification
- Coordinate re-verification and re-validation activities

### 1.2 Scope

**Applies to all changes**:
- Requirements modifications (SRS updates)
- Design changes (architecture, module design)
- Code modifications (bug fixes, features, refactoring)
- Documentation updates (plans, specifications, reports)
- Test artifacts (test code, test data, test plans)
- Tool configurations (build scripts, analysis tools)
- Baseline modifications (after gate approval)

**Out of Scope**:
- Informal work-in-progress (before baseline)
- Internal developer notes (not CIs)
- Build artifacts (generated outputs)

### 1.3 SIL-Specific Requirements

| Requirement | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 |
|-------------|-------|-------|-------|-------|-------|
| Formal CR process | **M** | **M** | **M** | **M** | **M** |
| Written impact analysis | R | HR | **M** | **M** | **M** |
| CCB approval before implementation | R | HR | **M** | **M** | **M** |
| Independent VER approval (CCB) | - | R | HR | **M** | **M** |
| VMGR approval for safety-critical | - | - | R | **M** | **M** |
| Traceability to all affected CIs | R | HR | **M** | **M** | **M** |
| Re-verification after change | R | HR | **M** | **M** | **M** |
| Re-validation after safety change | - | R | HR | **M** | **M** |
| Cumulative impact analysis | - | R | HR | **M** | **M** |
| Change metrics tracking | R | HR | **M** | **M** | **M** |

**Legend**: M = Mandatory, HR = Highly Recommended, R = Recommended, - = No recommendation

### 1.4 EN 50128 References

- **Section 6.6.4**: Modification and Change Control (detailed requirements)
- **Section 6.6.4.1**: Nine required aspects (a-i) for change control
- **Section 6.6.4.2**: Changes initiate return to appropriate lifecycle phase
- **Table A.9 #5**: Software Configuration Management (MANDATORY ALL SIL)
- **Table A.9 #7**: Traceability (MANDATORY SIL 3-4)
- **Table A.9 #8**: Data Recording and Analysis (MANDATORY SIL 3-4)

---

## 2. EN 50128 Change Control Requirements

### 2.1 Section 6.6.4.1: Nine Required Aspects

EN 50128 Section 6.6.4.1 mandates **nine specific aspects** for change control:

**a) Control of the modification process**
- Formal process for requesting, approving, implementing, and verifying changes
- Documented procedures (SCMP)
- CCB authority and responsibility

**b) Change request and impact analysis**
- Written change request with rationale
- Impact analysis: affected CIs, safety impact, cost/schedule impact
- Alternative solutions considered

**c) Approval of changes before implementation**
- CCB reviews and approves/rejects CR
- Independent VER/VAL approval for SIL 3-4
- Documentation of approval decision

**d) Check that the implementation and all consequential changes have been completed**
- Verification that all planned changes implemented
- No unintended side effects introduced
- Traceability updated (RTM, CI records)

**e) Re-verification and re-validation where appropriate**
- Re-run affected tests after change
- Full regression testing if safety-critical (SIL 3-4)
- Independent re-verification (SIL 3-4)

**f) Baseline update**
- Updated baseline after change closure
- New baseline tag (if gate-level change)
- Baseline documentation updated

**g) Archive of data and information**
- All CR records archived
- Impact analysis reports retained
- Verification evidence stored
- Audit trail maintained

**h) Configuration status accounting**
- Track CR status (submitted, approved, implemented, verified, closed)
- Report CR metrics (count, resolution time, categories)
- Cumulative impact tracking

**i) Cumulative effect of multiple changes**
- Assess combined impact of multiple CRs
- Identify emergent risks from change interactions
- Plan comprehensive re-verification if needed

### 2.2 Section 6.6.4.2: Return to Lifecycle Phase

**Critical requirement**: "All changes shall initiate a return to an appropriate phase of the lifecycle"

**Interpretation**:
- Requirements change → Return to Phase 2 (Requirements), proceed through design, implementation, testing
- Design change → Return to Phase 3 (Design), proceed through implementation, testing
- Implementation change (code) → Return to Phase 4 (Implementation), proceed through testing
- Test change → Return to Phase 5 (Testing)

**Integration with Lifecycle Coordination**:
- CM (Change Control) coordinates with COD (Lifecycle Coordinator) for phase re-entry
- COD tracks iteration status in LIFECYCLE_STATE.md
- See **Lifecycle-Coordination Workflow 4** (Iteration and Change Management) for detailed phase re-entry process

**Example**:
```
Change: Modify REQ-42 (timeout threshold from 100ms to 150ms)

Lifecycle Impact:
1. Return to Phase 2 (Requirements)
   - Update SRS with new threshold
   - Update RTM with new traceability
   - VER verifies requirements change
2. Proceed to Phase 3 (Design)
   - Review design (no change needed)
   - VER verifies design still valid
3. Proceed to Phase 4 (Implementation)
   - Update timeout.c with new constant
   - Update unit tests
   - Re-run unit tests (100% pass)
4. Proceed to Phase 5 (Integration)
   - Re-run integration tests (100% pass)
5. Proceed to Phase 6 (Validation)
   - Re-run affected system tests (100% pass)

Result: Change fully integrated through lifecycle
```

### 2.3 Traceability Requirements (EN 50128 Table A.9 #7)

**MANDATORY for SIL 3-4**, traceability for change control requires:
- Every CR linked to affected requirements
- Every changed CI linked to CR
- Bidirectional traceability: CR ↔ Requirements ↔ Code ↔ Tests
- Traceability matrix updated after each CR closure

**Implementation**:
- RTM (Requirements Traceability Matrix) updated with CR references
- Git commits include CR ID: `[CR-123]`
- `workspace.py trace validate-ci` checks traceability after CR

### 2.4 Data Recording and Analysis (EN 50128 Table A.9 #8)

**MANDATORY for SIL 3-4**, data recording for change control requires:
- CR submission date, approval date, implementation date, verification date, closure date
- CR category (defect, enhancement, safety, documentation)
- CR priority (critical, high, medium, low)
- CR status history (state transitions)
- CR resolution time (approval to closure)
- CR metrics: count, rate, distribution by category/priority

**Implementation**:
- CR database (YAML/JSON files tracked in Git)
- `workspace.py wf show-cr <id>` displays CR details
- Monthly CR reports generated from database

---

## 3. Change Request (CR) Process

### 3.1 CR Lifecycle States

**CR state machine**:

```
┌──────────────┐
│  SUBMITTED   │  CR created by requester
└──────┬───────┘
       │
       ▼
┌──────────────┐
│  IN_REVIEW   │  Impact analysis in progress
└──────┬───────┘
       │
       ▼
┌──────────────┐  CCB meeting
│ PENDING_CCB  │  Awaiting CCB decision
└──────┬───────┘
       │
       ├─────────────────────┐
       │                     │
       ▼                     ▼
┌──────────────┐      ┌──────────────┐
│   APPROVED   │      │   REJECTED   │  CR denied
└──────┬───────┘      └──────────────┘
       │
       ▼
┌──────────────┐
│IMPLEMENTATION│  Changes being made
└──────┬───────┘
       │
       ▼
┌──────────────┐
│VERIFICATION  │  Testing/verification
└──────┬───────┘
       │
       ├─────────────────────┐
       │                     │
       ▼                     ▼
┌──────────────┐      ┌──────────────┐
│   VERIFIED   │      │   FAILED     │  Verification failed
└──────┬───────┘      └──────┬───────┘
       │                     │
       │                     └───────────┐
       │                                 │
       ▼                                 ▼
┌──────────────┐                  ┌──────────────┐
│    CLOSED    │                  │  REWORK      │
└──────────────┘                  └──────────────┘
                                         │
                                         └─────────→ IMPLEMENTATION
```

**State Descriptions**:

| State | Description | Actions | Next States |
|-------|-------------|---------|-------------|
| SUBMITTED | CR created, awaiting triage | Assign to CM for impact analysis | IN_REVIEW |
| IN_REVIEW | Impact analysis in progress | CM performs impact analysis, prepares report | PENDING_CCB |
| PENDING_CCB | Awaiting CCB decision | CCB reviews CR and impact analysis | APPROVED, REJECTED |
| APPROVED | CCB approved, ready for implementation | Assign to implementer (REQ/DES/IMP) | IMPLEMENTATION |
| REJECTED | CCB rejected CR | Document rejection rationale, close CR | (none) |
| IMPLEMENTATION | Changes being implemented | Implementer modifies CIs, commits with CR reference | VERIFICATION |
| VERIFICATION | Changes being verified | VER performs re-verification, TST re-runs tests | VERIFIED, FAILED |
| VERIFIED | Verification passed | Prepare for baseline update | CLOSED |
| FAILED | Verification failed | Analyze failure, determine rework needed | REWORK |
| REWORK | Fixing verification failures | Implementer fixes issues | IMPLEMENTATION |
| CLOSED | CR fully implemented and verified | Archive CR records, update metrics | (none) |

### 3.2 CR Template

**CR records** stored in `changes/CR-<id>.yaml`:

```yaml
cr_id: CR-123
title: Fix null pointer dereference in timeout module
status: SUBMITTED
priority: HIGH
category: DEFECT
safety_related: true
sil_level: 3

requester:
  name: Jane Smith
  role: VER
  email: jane.smith@company.com
  date: 2024-03-10

description: |
  Null pointer dereference in timeout_check() when sensor_id >= MAX_SENSORS
  and timeout state not initialized. Causes crash in fault injection test.
  
  Observed Behavior:
  - Call timeout_check(5, 100) without prior timeout_init(5, ...)
  - Segmentation fault due to NULL pointer dereference
  
  Expected Behavior:
  - timeout_check() should return false for invalid sensor_id
  - No crash, defensive programming applied

affected_requirements:
  - REQ-42: Timeout detection
  - REQ-10: Defensive programming (all inputs validated)

affected_cis:
  - src/timeout.c
  - tests/unit_test_timeout.c

impact_analysis:
  performed_by: John Doe (CM)
  date: 2024-03-11
  affected_phases:
    - implementation
    - testing
  safety_impact: |
    CRITICAL: Null pointer dereference can cause system crash.
    Safety function (timeout monitoring) becomes unavailable.
    SIL 3 safety integrity violated.
  scope: |
    - Code change: Add bounds check in timeout_check() (1 line)
    - Test change: Add test case for invalid sensor_id (5 lines)
    - Regression testing: Re-run all timeout unit tests (15 tests)
    - Integration testing: Re-run timeout integration tests (3 tests)
  effort_estimate: 2 hours (implementation + testing)
  schedule_impact: None (can be completed within sprint)
  alternatives_considered: |
    1. Add assert() → Rejected (SIL 3 requires graceful handling)
    2. Add bounds check → SELECTED (defensive programming)

ccb_decision:
  meeting_date: 2024-03-12
  attendees:
    - John Doe (CM, Chair)
    - Alice Johnson (PM)
    - Bob Smith (VER)
    - Carol White (VMGR)
  decision: APPROVED
  rationale: |
    Critical safety defect, must be fixed immediately.
    Low implementation risk, clear solution.
    Approved for immediate implementation.
  conditions:
    - Must include test case for invalid sensor_id
    - Must re-run full timeout test suite
    - VMGR approval required after verification

implementation:
  assigned_to: John Doe (IMP)
  start_date: 2024-03-12
  commits:
    - a1b2c3d: "fix(timeout): Add bounds check for sensor_id [CR-123]"
    - b2c3d4e: "test(timeout): Add test for invalid sensor_id [CR-123]"
  end_date: 2024-03-12

verification:
  performed_by: Bob Smith (VER)
  date: 2024-03-13
  result: PASS
  evidence:
    - Unit tests: 16/16 PASS (added 1 new test)
    - Integration tests: 3/3 PASS
    - Coverage: 100% statement, branch, condition
    - Static analysis: 0 issues
  vmgr_approval: Carol White (VMGR)
  vmgr_approval_date: 2024-03-13

closure:
  closed_by: John Doe (CM)
  closed_date: 2024-03-13
  baseline_updated: baseline/gate4-implementation-v1.1
  lessons_learned: |
    Defensive programming gap identified in original implementation.
    Action: Add checklist item for bounds validation in code review.

metrics:
  time_to_approval: 2 days (submitted to approved)
  time_to_implementation: 0 days (approved to implemented)
  time_to_verification: 1 day (implemented to verified)
  time_to_closure: 3 days (submitted to closed)
```

### 3.3 CR Submission Process

**Who can submit CRs?**
- Any project team member
- Customer/stakeholder
- Assessor (ISA)
- Safety authority

**Submission steps**:

```bash
# Step 1: Create CR file
workspace.py wf create-cr --title "Fix null pointer in timeout module" \
  --category DEFECT \
  --priority HIGH \
  --description "Null pointer dereference in timeout_check()..." \
  --requester "Jane Smith (VER)" \
  --affected-req "REQ-42,REQ-10" \
  --affected-ci "src/timeout.c,tests/unit_test_timeout.c"

# Output:
# ✅ CR created: changes/CR-123.yaml
# ✅ CR-123 status: SUBMITTED
# ✅ Assigned to CM for impact analysis

# Step 2: Commit CR file
git add changes/CR-123.yaml
git commit -m "chore(cm): Submit CR-123 for null pointer fix

CR-123: Fix null pointer dereference in timeout module

Submitted by: Jane Smith (VER)
Category: DEFECT
Priority: HIGH
Safety related: Yes (SIL 3)

[CR-123] CR submission
" --signoff

git push origin develop

# Step 3: Notify CM (automated via CI webhook or manual)
# CM receives notification, begins impact analysis
```

### 3.4 CR Categories and Priorities

**CR Categories**:

| Category | Description | Examples |
|----------|-------------|----------|
| DEFECT | Bug fix, error correction | Null pointer, incorrect calculation, memory leak |
| ENHANCEMENT | New feature, improvement | New sensor support, performance optimization |
| SAFETY | Safety-related change | Safety requirement modification, hazard mitigation |
| DOCUMENTATION | Documentation only | SRS update, comment correction, user manual |
| REFACTORING | Code restructuring (no functional change) | Function splitting, variable renaming |
| TOOL | Tool or build configuration | Makefile update, static analyzer configuration |
| REQUIREMENTS | Requirements change | New requirement, requirement modification |

**CR Priorities**:

| Priority | Description | Response Time (SIL 3-4) | Examples |
|----------|-------------|------------------------|----------|
| CRITICAL | System unusable, safety violated | 24 hours | Crash, safety function failure, data corruption |
| HIGH | Major function impaired | 3 days | Incorrect output, performance degradation |
| MEDIUM | Minor function impaired | 1 week | UI issue, non-critical warning, minor inconsistency |
| LOW | Cosmetic, enhancement | 1 month | Typo, code cleanup, nice-to-have feature |

**SIL-Specific Escalation**:
- **SIL 3-4 + SAFETY category**: Automatic CRITICAL priority
- **SIL 3-4 + DEFECT + safety-related**: Automatic HIGH priority
- **SIL 0-2**: Standard prioritization

---

## 4. Impact Analysis

### 4.1 Impact Analysis Process

**CM performs impact analysis** after CR submission:

**Step 1: Understand the change**
- Read CR description carefully
- Clarify with requester if needed
- Identify root cause (for defects)

**Step 2: Identify affected CIs**
- Which source files affected?
- Which design documents affected?
- Which requirements affected?
- Which test artifacts affected?

**Step 3: Assess safety impact**
- Is this a safety-critical function?
- Can failure cause hazard?
- What is SIL level of affected function?
- Does change introduce new hazards?

**Step 4: Determine lifecycle phase impact**
- Which phases need re-execution?
- Requirements change → Phases 2-7
- Design change → Phases 3-7
- Code change → Phases 4-7

**Step 5: Estimate effort and schedule**
- Implementation effort (hours/days)
- Testing effort (test count, execution time)
- Verification effort (reviews, analysis)
- Schedule impact (can fit in sprint? need delay?)

**Step 6: Consider alternatives**
- What other solutions exist?
- Trade-offs (complexity, risk, effort)?
- Recommended solution?

**Step 7: Document findings**
- Write impact analysis report
- Update CR YAML with analysis results
- Prepare for CCB presentation

### 4.2 Impact Analysis Template

**Section 1: Affected Configuration Items**

```yaml
affected_cis:
  source_code:
    - path: src/timeout.c
      functions: [timeout_check]
      lines_changed: 1
      complexity_change: 0
    - path: src/timeout.h
      functions: []
      lines_changed: 0
      complexity_change: 0
  
  tests:
    - path: tests/unit_test_timeout.c
      tests_added: 1
      tests_modified: 0
      tests_deleted: 0
    - path: tests/integration_test_timeout.c
      tests_added: 0
      tests_modified: 0
      tests_deleted: 0
  
  documentation:
    - path: docs/design/SDS-v1.2.md
      section: "3.4 Timeout Module"
      change_description: "Add defensive programming note"
  
  requirements:
    - id: REQ-42
      change_type: NONE
      rationale: "Implementation fix, requirement unchanged"
    - id: REQ-10
      change_type: NONE
      rationale: "Defensive programming already required"
```

**Section 2: Safety Impact Analysis**

```yaml
safety_impact:
  safety_critical: true
  sil_level: 3
  hazard_analysis: |
    Original Issue:
    - Null pointer dereference can cause system crash
    - Timeout monitoring becomes unavailable
    - Loss of safety function (sensor monitoring)
    
    Hazard: H-05 "Loss of sensor timeout detection"
    - Consequence: Undetected sensor failure
    - Severity: MAJOR (potential train collision)
    - Probability: Before fix = PROBABLE, After fix = RARE
    
    Risk Reduction:
    - Fix eliminates null pointer dereference
    - Defensive programming applied (bounds check)
    - Risk reduced from INTOLERABLE to ACCEPTABLE
  
  fmea_impact:
    - fmea_id: FMEA-42-1
      failure_mode: "timeout_check() crash on invalid input"
      before_fix:
        detection: 5
        severity: 9
        rpn: 45
      after_fix:
        detection: 2
        severity: 9
        rpn: 18
  
  new_hazards: []
  mitigation_effectiveness: HIGH
```

**Section 3: Lifecycle Phase Impact**

```yaml
lifecycle_impact:
  phases_affected:
    - phase: 4-implementation
      activities:
        - Modify timeout.c (add bounds check)
        - Update unit tests (add test case)
      effort: 2 hours
      
    - phase: 5-integration
      activities:
        - Re-run timeout unit tests (16 tests)
        - Re-run timeout integration tests (3 tests)
      effort: 1 hour
      
    - phase: 6-validation
      activities:
        - Re-run affected system tests (scenario S-08)
      effort: 1 hour
  
  gate_impact: |
    No gate regression. Project currently at Gate 4 (Implementation).
    Change can be completed before Gate 5 (Integration).
  
  traceability_updates:
    - RTM: Add CR-123 reference to REQ-42, REQ-10
    - Git commits: Include [CR-123] in all commit messages
    - Hazard Log: Update H-05 mitigation status
```

**Section 4: Effort and Schedule Estimate**

```yaml
effort_estimate:
  implementation: 2 hours
  testing: 1 hour
  verification: 1 hour
  documentation: 0.5 hours
  total: 4.5 hours
  
schedule_impact:
  current_sprint: "Sprint 5 (2024-03-11 to 2024-03-25)"
  can_fit_in_sprint: true
  delay_required: false
  critical_path_affected: false
  
resource_requirements:
  implementer: 1 (IMP)
  tester: 1 (TST)
  verifier: 1 (VER, independent)
  reviewer: 1 (VMGR approval)
```

**Section 5: Alternatives Considered**

```yaml
alternatives:
  - alternative_id: ALT-1
    description: "Use assert() to catch invalid sensor_id"
    pros:
      - Simple, 1-line change
      - Catches error during development
    cons:
      - Not suitable for SIL 3 (abort on error, not graceful)
      - Assert may be disabled in production builds
    recommendation: REJECTED
  
  - alternative_id: ALT-2
    description: "Add bounds check, return false for invalid input"
    pros:
      - Defensive programming (SIL 3 requirement)
      - Graceful handling (no crash)
      - Simple, low risk
    cons:
      - None identified
    recommendation: SELECTED
  
  - alternative_id: ALT-3
    description: "Restructure timeout module to eliminate sensor_id parameter"
    pros:
      - Eliminates entire class of errors
    cons:
      - Major refactoring (high risk, high effort)
      - Breaks API (affects all callers)
      - Not justified for single defect
    recommendation: REJECTED
```

### 4.3 Cumulative Impact Analysis (SIL 3-4)

**EN 50128 Section 6.6.4.1(i)** requires assessment of **cumulative effects** of multiple changes.

**Process**:

1. **Identify related CRs** (same module, same requirement, same sprint)
2. **Assess combined impact** (total lines changed, total complexity increase)
3. **Check for emergent risks** (interactions between changes, unintended side effects)
4. **Determine comprehensive re-verification scope** (full regression test if cumulative impact high)

**Example cumulative analysis**:

```yaml
cumulative_impact:
  related_crs:
    - CR-120: Add multi-sensor support to timeout module
    - CR-121: Optimize timeout_check() performance
    - CR-123: Fix null pointer dereference (current)
  
  cumulative_changes:
    lines_added: 150
    lines_modified: 75
    lines_deleted: 20
    complexity_increase: +15 CCN total
    api_changes: 2 (timeout_init signature, timeout_check signature)
  
  emergent_risks:
    - risk_id: ER-1
      description: "Multiple changes to timeout_check() may introduce race condition"
      probability: LOW
      mitigation: "Add concurrency stress test"
    
    - risk_id: ER-2
      description: "API changes may break existing callers"
      probability: MEDIUM
      mitigation: "Full integration regression test required"
  
  comprehensive_verification:
    required: true
    scope: |
      - All timeout unit tests (16 tests)
      - All timeout integration tests (3 tests)
      - All system tests using timeout module (10 scenarios)
      - Concurrency stress test (new)
      - API compatibility check (all callers)
    effort: 8 hours (increased from 1 hour for single CR)
```

**Cumulative impact triggers** (SIL 3-4):
- ≥3 CRs to same module in same sprint → Cumulative analysis required
- Total lines changed ≥20% of module → Full regression test required
- Complexity increase ≥5 CCN → Complexity re-analysis required
- API changes → Integration regression test required

### 4.4 Impact Analysis Automation

**`tools/cr_impact_analyzer.py`** automates impact analysis:

```bash
# Analyze CR impact
python3 tools/cr_impact_analyzer.py --cr-id CR-123

# Output:
# Analyzing CR-123: Fix null pointer dereference in timeout module
# 
# Affected CIs:
# - src/timeout.c (1 function modified: timeout_check)
# - tests/unit_test_timeout.c (1 test added)
# 
# Safety Impact: CRITICAL (SIL 3 function)
# - Hazard H-05 affected
# - Risk reduced from RPN 45 to RPN 18
# 
# Lifecycle Impact:
# - Phase 4 (Implementation): 2 hours
# - Phase 5 (Integration): 1 hour
# - Phase 6 (Validation): 1 hour
# - Total effort: 4.5 hours
# 
# Cumulative Impact:
# - Related CRs: CR-120, CR-121 (same module, same sprint)
# - Total lines changed: 150 added, 75 modified, 20 deleted
# - Cumulative complexity: +15 CCN
# - Comprehensive verification REQUIRED
# 
# Recommendation: APPROVE
# - Low implementation risk
# - Clear solution (defensive programming)
# - Critical safety fix
# - Can complete within sprint

# Generate impact analysis report
python3 tools/cr_impact_analyzer.py --cr-id CR-123 --report impact-CR-123.md
```

---

## 5. Change Control Board (CCB)

### 5.1 CCB Composition

**CCB membership** (SIL 3-4):

| Role | Responsibility | Required? |
|------|---------------|-----------|
| Configuration Manager (CM) | Chair, facilitates meeting, records decisions | **MANDATORY** |
| Project Manager (PM) | Resource allocation, schedule impact | **MANDATORY** |
| Requirements Engineer (REQ) | Requirements impact assessment | As needed |
| Designer (DES) | Design impact assessment | As needed |
| Implementer (IMP) | Implementation feasibility | As needed |
| Verifier (VER) | Verification impact, independent view | **MANDATORY** (SIL 3-4) |
| Validator (VAL) | Validation impact (safety-critical changes) | As needed (SIL 3-4) |
| V&V Manager (VMGR) | Independent V&V authority, final approval | **MANDATORY** (SIL 3-4, safety-critical) |
| Safety Engineer (SAF) | Safety impact assessment | As needed (safety-related CRs) |
| Quality Assurance (QUA) | Process compliance | As needed |
| Customer Representative | Customer acceptance (if contractual) | As needed |

**SIL-Specific Requirements**:
- **SIL 0-2**: CM + PM minimum
- **SIL 3-4**: CM + PM + VER minimum, VMGR for safety-critical

### 5.2 CCB Meeting Process

**Frequency**:
- **Regular meetings**: Weekly (SIL 3-4), Bi-weekly (SIL 0-2)
- **Emergency meetings**: As needed for CRITICAL priority CRs

**Agenda**:

1. **Open** (5 min)
   - Roll call, quorum check
   - Review agenda
   - Approve previous meeting minutes

2. **Review pending CRs** (30-45 min)
   - For each CR in PENDING_CCB state:
     - CM presents CR and impact analysis
     - Discussion: feasibility, risks, alternatives
     - Safety impact review (SAF, if present)
     - VER/VAL opinion (for SIL 3-4)
     - Decision: APPROVE, REJECT, DEFER (need more info)

3. **Review in-progress CRs** (10 min)
   - Status update on IMPLEMENTATION, VERIFICATION state CRs
   - Identify blockers or delays

4. **Cumulative impact review** (10 min)
   - Review related CRs (same module, same sprint)
   - Assess cumulative impact
   - Adjust comprehensive verification scope if needed

5. **Metrics review** (5 min)
   - CR count by category, priority, status
   - Average resolution time
   - Trends (increasing defect rate?)

6. **Close** (5 min)
   - Action items
   - Next meeting date

**Total duration**: 60-75 minutes

### 5.3 CCB Decision Criteria

**Approval criteria**:
- ✅ Impact analysis complete and accurate
- ✅ Safety impact acceptable (or improved)
- ✅ Effort and schedule impact acceptable
- ✅ Resources available (people, time)
- ✅ Verification plan adequate
- ✅ Traceability plan defined
- ✅ Alternatives considered
- ✅ Independent VER concurs (SIL 3-4)
- ✅ VMGR concurs (SIL 3-4, safety-critical)

**Rejection criteria**:
- ❌ Insufficient impact analysis
- ❌ Unacceptable safety risk
- ❌ Insufficient resources
- ❌ Schedule conflict (critical path affected)
- ❌ Better alternative exists
- ❌ Not aligned with project goals
- ❌ VER/VMGR objects (SIL 3-4)

**Deferral criteria**:
- ⏸️ Need more information (impact unclear)
- ⏸️ Need expert consultation (SAF, customer)
- ⏸️ Need feasibility prototype
- ⏸️ Need detailed cost/schedule analysis

### 5.4 CCB Decision Recording

**CCB meeting minutes** template:

```markdown
# CCB Meeting Minutes

**Meeting ID**: CCB-2024-03-12  
**Date**: 2024-03-12 10:00-11:00  
**Location**: Conference Room A / Zoom  

## Attendees

- John Doe (CM, Chair) - Present
- Alice Johnson (PM) - Present
- Bob Smith (VER) - Present
- Carol White (VMGR) - Present
- Dave Brown (SAF) - Absent

## Agenda

1. Review CR-120, CR-121, CR-123
2. Cumulative impact review (timeout module)
3. Metrics review

## CR Review

### CR-120: Add multi-sensor support to timeout module

- **Status**: PENDING_CCB
- **Presenter**: John Doe (CM)
- **Impact**: 100 lines added, complexity +10 CCN, 5 days effort
- **Discussion**:
  - PM: Can fit in Sprint 5 if started immediately
  - VER: Requires comprehensive testing (20+ tests)
  - VMGR: Safety impact acceptable (improved functionality)
- **Decision**: APPROVED
- **Conditions**:
  - Must include ≥20 unit tests
  - Full integration regression test required
  - VMGR approval after verification
- **Votes**: 4 yes, 0 no, 0 abstain

### CR-121: Optimize timeout_check() performance

- **Status**: PENDING_CCB
- **Presenter**: John Doe (CM)
- **Impact**: 20 lines modified, complexity +2 CCN, 2 days effort
- **Discussion**:
  - PM: Performance improvement needed (100ms budget tight)
  - VER: Need performance benchmarks before/after
  - VMGR: Must not affect safety function correctness
- **Decision**: APPROVED
- **Conditions**:
  - Performance benchmark required (document improvement)
  - All existing tests must pass (no functional change)
  - Static analysis must remain clean
- **Votes**: 4 yes, 0 no, 0 abstain

### CR-123: Fix null pointer dereference in timeout module

- **Status**: PENDING_CCB
- **Presenter**: John Doe (CM)
- **Impact**: 1 line added, complexity +0 CCN, 4.5 hours effort
- **Discussion**:
  - VER: Critical defect, must fix immediately
  - VMGR: Agrees, safety violation
  - PM: Can complete today (CRITICAL priority)
- **Decision**: APPROVED
- **Conditions**:
  - Must include test case for invalid sensor_id
  - Full timeout test suite re-run required
  - VMGR approval after verification
- **Votes**: 4 yes, 0 no, 0 abstain

## Cumulative Impact Review

**Related CRs**: CR-120, CR-121, CR-123 (timeout module)

- **Cumulative changes**: 150 lines added, 75 modified, 20 deleted
- **Complexity increase**: +15 CCN (total module complexity now 35 CCN)
- **Emergent risks**: Potential race condition with multi-sensor + optimization
- **Mitigation**: Add concurrency stress test (new)
- **Comprehensive verification required**: Yes
  - All timeout unit tests (16 → 20 tests after CR-120)
  - All timeout integration tests (3 tests)
  - All system tests using timeout (10 scenarios)
  - New concurrency stress test

## Metrics Review

- **Total CRs**: 25 (10 open, 15 closed)
- **By category**: Defects 12, Enhancements 8, Safety 3, Documentation 2
- **By priority**: Critical 2, High 5, Medium 10, Low 8
- **Average resolution time**: 5 days (target: ≤7 days)
- **Trend**: Defect rate stable (3 per sprint, acceptable)

## Action Items

1. [John Doe] Update CR-120, CR-121, CR-123 status to APPROVED
2. [Alice Johnson] Assign CR-123 to implementer (CRITICAL, start immediately)
3. [Bob Smith] Prepare comprehensive verification plan for timeout module
4. [Carol White] Review cumulative impact analysis, approve comprehensive verification scope

## Next Meeting

**Date**: 2024-03-19 10:00-11:00  
**Agenda**: Review CR-124, CR-125, CR-126

---

**Minutes prepared by**: John Doe (CM)  
**Approved by**: Alice Johnson (PM), Carol White (VMGR)
```

---

## 6. CR Implementation

### 6.1 Implementation Process

**After CCB approval**, CR moves to IMPLEMENTATION state:

**Step 1: Assignment**
- CM assigns CR to appropriate implementer (REQ/DES/IMP)
- Implementer receives notification
- CR status updated: APPROVED → IMPLEMENTATION

**Step 2: Lifecycle Phase Re-entry**
- Implementer coordinates with COD (Lifecycle Coordinator)
- Determine which phase to re-enter (per EN 50128 Section 6.6.4.2)
- COD updates LIFECYCLE_STATE.md with iteration tracking
- See **Lifecycle-Coordination Workflow 4** for detailed iteration process

**Step 3: Implement Changes**
- Create feature/bugfix branch: `bugfix/CR-123-null-pointer-fix`
- Modify affected CIs (code, docs, tests)
- Follow coding standards (MISRA C for SIL 3-4)
- Maintain complexity limits (≤10 CCN for SIL 3-4)
- Apply defensive programming

**Step 4: Commit Changes**
- All commits include CR reference: `[CR-123]`
- Follow commit message conventions (see Version Control Workflow)
- Sign commits (GPG for SIL 3-4)

**Step 5: Update Traceability**
- Update RTM with CR references
- Link commits to requirements: `workspace.py trace link-commit <sha> REQ-42`
- Verify traceability: `workspace.py trace validate-ci`

**Step 6: Create Pull Request**
- Title: `[CR-123] Fix null pointer dereference in timeout module`
- Description: Link to CR, impact analysis, test results
- Assign reviewers (≥2 for SIL 3-4, at least 1 from VER)

**Step 7: Code Review**
- Address review comments
- Ensure MISRA C compliance
- Ensure complexity within limits
- Ensure defensive programming applied

**Step 8: Merge After Approval**
- CI passes (build, tests, coverage, static analysis)
- ≥2 reviews approved (SIL 3-4)
- Merge to develop (or main for hotfix)
- Delete feature branch

**Step 9: Update CR Status**
- CR status updated: IMPLEMENTATION → VERIFICATION
- Notify VER team

### 6.2 Implementation Example

**CR-123: Fix null pointer dereference**

```bash
# Step 1: Create bugfix branch
git checkout develop
git pull origin develop
git checkout -b bugfix/CR-123-null-pointer-fix

# Step 2: Implement fix
# Edit src/timeout.c: Add bounds check
cat > src/timeout.c << 'EOF'
#include "timeout.h"
#include <stddef.h>

#define MAX_SENSORS 4

typedef struct {
    uint32_t threshold_ms;
    uint32_t elapsed_ms;
    timeout_callback_t callback;
    bool active;
} timeout_state_t;

static timeout_state_t timeouts[MAX_SENSORS];

void timeout_init(uint8_t sensor_id, uint32_t threshold_ms, timeout_callback_t callback) {
    if (sensor_id >= MAX_SENSORS) return;  /* Bounds check */
    if (callback == NULL) return;          /* NULL check */
    
    timeouts[sensor_id].threshold_ms = threshold_ms;
    timeouts[sensor_id].elapsed_ms = 0;
    timeouts[sensor_id].callback = callback;
    timeouts[sensor_id].active = true;
}

bool timeout_check(uint8_t sensor_id, uint32_t elapsed_ms) {
    /* FIX: Add bounds check (was missing) */
    if (sensor_id >= MAX_SENSORS) return false;  /* NEW LINE */
    
    if (!timeouts[sensor_id].active) return false;
    
    timeouts[sensor_id].elapsed_ms += elapsed_ms;
    
    if (timeouts[sensor_id].elapsed_ms >= timeouts[sensor_id].threshold_ms) {
        timeouts[sensor_id].callback(sensor_id);
        return true;
    }
    
    return false;
}

void timeout_reset(uint8_t sensor_id) {
    if (sensor_id >= MAX_SENSORS) return;
    timeouts[sensor_id].elapsed_ms = 0;
}
EOF

git add src/timeout.c
git commit -m "fix(timeout): Add bounds check in timeout_check() [CR-123]

Fix null pointer dereference when sensor_id >= MAX_SENSORS.

Root Cause:
- timeout_check() did not validate sensor_id before array access
- Invalid sensor_id caused access to uninitialized memory
- Fault injection test revealed crash

Fix:
- Add bounds check: if (sensor_id >= MAX_SENSORS) return false
- Defensive programming applied (SIL 3 requirement REQ-10)

Safety Impact:
- Eliminates crash risk (system stability improved)
- Timeout monitoring remains available (safety function preserved)
- Hazard H-05 risk reduced from RPN 45 to RPN 18

Testing:
- Unit test added: test_timeout_invalid_sensor_id
- All timeout tests pass (16/16)
- Coverage: 100% statement, branch, condition

[CR-123] Null pointer fix
Refs: REQ-42, REQ-10
CCB approved: 2024-03-12
" --signoff

# Step 3: Add unit test
# Edit tests/unit_test_timeout.c: Add test case
git add tests/unit_test_timeout.c
git commit -m "test(timeout): Add test for invalid sensor_id [CR-123]

Add test case to verify timeout_check() handles invalid sensor_id
gracefully (no crash).

Test: test_timeout_invalid_sensor_id
- Call timeout_check() with sensor_id=100 (>= MAX_SENSORS=4)
- Expected: return false (no crash)
- Actual: return false (PASS)

Coverage impact:
- Branch coverage for bounds check: 100%
- Total coverage: 100% statement, branch, condition

[CR-123] Test for invalid sensor_id
Refs: REQ-42
" --signoff

# Step 4: Build and test locally
make clean all test
# Output: 16/16 tests PASS

# Step 5: Check coverage
make coverage
# Output: 100% statement, 100% branch, 100% condition

# Step 6: Static analysis
cppcheck --enable=all src/timeout.c
# Output: 0 issues

lizard src/timeout.c
# Output: timeout_check CCN=3 (≤10 OK)

# Step 7: Update traceability
workspace.py trace link-commit $(git rev-parse HEAD~1) CR-123
workspace.py trace link-commit $(git rev-parse HEAD) CR-123
workspace.py trace validate-ci

# Step 8: Push branch
git push -u origin bugfix/CR-123-null-pointer-fix

# Step 9: Create pull request (via GitHub UI)
# Title: [CR-123] Fix null pointer dereference in timeout module
# Description:
#   Fix critical null pointer dereference in timeout_check().
#   
#   CR-123: https://github.com/company/project/blob/develop/changes/CR-123.yaml
#   Impact Analysis: Critical safety defect, must fix immediately
#   CCB Decision: APPROVED (2024-03-12)
#   
#   Changes:
#   - Add bounds check in timeout_check() (1 line)
#   - Add unit test for invalid sensor_id (1 test)
#   
#   Testing:
#   - Unit tests: 16/16 PASS
#   - Coverage: 100% statement, branch, condition
#   - Static analysis: Clean
#   - Complexity: timeout_check CCN=3 (≤10 OK)
#   
#   Reviewers: @bob-ver (VER), @alice-pm (PM)
#   VMGR Approval Required: @carol-vmgr

# Step 10: Wait for review and CI
# CI pipeline runs:
# - Build: ✅ SUCCESS
# - Tests: ✅ 16/16 PASS
# - Coverage: ✅ 100%
# - Static analysis: ✅ 0 issues
# - Complexity: ✅ All ≤10 CCN
# - Traceability: ✅ PASS

# Reviewers approve:
# @bob-ver: "LGTM, bounds check correctly applied, test covers edge case"
# @alice-pm: "Approved, critical fix"

# Step 11: Merge pull request (via GitHub UI)
# Method: Merge commit (preserve history)

# Step 12: Update CR status
workspace.py wf update-cr CR-123 --status VERIFICATION --implementer "John Doe (IMP)" --commits "a1b2c3d,b2c3d4e"

# Step 13: Notify VER
# (Automated notification via CI webhook)

# Step 14: Sync local branch
git checkout develop
git pull origin develop
git branch -d bugfix/CR-123-null-pointer-fix
```

### 6.3 Implementation Constraints (SIL 3-4)

**MANDATORY constraints** for CR implementation at SIL 3-4:

| Constraint | Requirement |
|------------|-------------|
| **MISRA C compliance** | Zero mandatory violations |
| **Complexity** | All functions ≤10 CCN |
| **Defensive programming** | All inputs validated, all pointers checked |
| **Static allocation** | No malloc/calloc/realloc/free |
| **Test coverage** | 100% statement, branch, condition |
| **Static analysis** | Zero critical issues (Cppcheck, Clang, PC-lint) |
| **Code review** | ≥2 reviewers, at least 1 from VER |
| **Traceability** | All commits reference CR, RTM updated |
| **Signed commits** | GPG signature required |
| **Documentation** | Code comments, SDS updated (if design changed) |

---

## 7. Re-verification and Re-validation

### 7.1 Re-verification Process (VER)

**After implementation**, VER performs re-verification:

**Step 1: Verify Implementation Completeness**
- Check all planned changes implemented (per impact analysis)
- No unintended changes introduced
- All affected CIs updated (code, docs, tests)

**Step 2: Review Code**
- MISRA C compliance (zero mandatory violations)
- Complexity within limits (≤10 CCN for SIL 3-4)
- Defensive programming applied
- Code review checklist completed

**Step 3: Static Analysis**
- Run Cppcheck, Clang, PC-lint
- Zero critical issues required (SIL 3-4)
- All warnings justified (if any)

**Step 4: Test Execution**
- Run unit tests (100% pass required for SIL 3-4)
- Run integration tests (if affected)
- Run regression tests (if comprehensive verification)

**Step 5: Coverage Analysis**
- Measure coverage (gcov/lcov)
- 100% statement, branch, condition required (SIL 3-4)
- Identify any uncovered code (should be none)

**Step 6: Traceability Verification**
- Verify all commits reference CR
- Verify RTM updated with CR references
- Run `workspace.py trace validate-ci`

**Step 7: Document Verification Results**
- Create Verification Report (VR-CR-123.md)
- Include test results, coverage, static analysis, traceability
- Submit to VMGR for approval (SIL 3-4)

**Step 8: Decision**
- If PASS: Update CR status VERIFICATION → VERIFIED
- If FAIL: Update CR status VERIFICATION → FAILED, return to implementer

### 7.2 Re-validation Process (VAL/VMGR, SIL 3-4)

**For safety-critical changes**, VAL/VMGR performs re-validation:

**Step 1: Review Verification Results**
- VER verification report complete?
- All tests passed?
- Coverage adequate?
- Traceability verified?

**Step 2: System-Level Testing**
- Run affected system tests (operational scenarios)
- Verify safety function correctness on target hardware
- Perform fault injection tests (if applicable)

**Step 3: Safety Impact Verification**
- Verify hazard mitigation effective
- Verify FMEA/FTA updated (if applicable)
- Verify Hazard Log updated

**Step 4: Independent Review**
- VMGR performs independent review (not involved in implementation)
- Verify EN 50128 compliance
- Verify safety integrity maintained

**Step 5: Document Validation Results**
- Create Validation Report (VaR-CR-123.md)
- Include system test results, safety verification
- VMGR approval signature

**Step 6: Decision**
- If PASS: VMGR approves, CR can close
- If FAIL: VMGR rejects, return to implementer for rework

### 7.3 Comprehensive Verification (Cumulative Impact)

**When cumulative impact analysis** indicates comprehensive verification required:

**Scope**:
- All unit tests for affected modules (not just changed functions)
- All integration tests using affected modules
- All system tests related to affected functionality
- Additional stress/concurrency tests (if identified as emergent risk)

**Example** (Timeout module with CR-120, CR-121, CR-123):

```bash
# Step 1: Unit Tests
make test MODULE=timeout
# Expected: 20/20 tests PASS (increased from 16 after CR-120)

# Step 2: Integration Tests
make integration-test FILTER=timeout
# Expected: 3/3 tests PASS

# Step 3: System Tests
make system-test FILTER=sensor_monitoring
# Expected: 10/10 scenarios PASS

# Step 4: Concurrency Stress Test (new, identified in cumulative analysis)
make concurrency-test FILTER=timeout
# Expected: PASS (no race conditions detected)

# Step 5: API Compatibility Check
tools/check_api_compatibility.py --module timeout --baseline gate4-implementation
# Expected: All existing callers compatible with new API

# Step 6: Full Coverage Report
make coverage-full MODULE=timeout
# Expected: 100% statement, branch, condition (across all timeout tests)

# Step 7: Static Analysis (full module)
cppcheck --enable=all src/timeout.c src/timeout.h
clang-tidy src/timeout.c
# Expected: 0 critical issues

# Step 8: Complexity Re-analysis
lizard src/timeout.c
# Expected: All functions ≤10 CCN, total module complexity ≤50 CCN

# Step 9: Document Comprehensive Verification Results
cat > docs/verification/comprehensive-VR-timeout-sprint5.md << 'EOF'
# Comprehensive Verification Report: Timeout Module (Sprint 5)

**Related CRs**: CR-120, CR-121, CR-123

## Cumulative Changes
- Lines added: 150
- Lines modified: 75
- Lines deleted: 20
- Complexity increase: +15 CCN

## Test Results
- Unit tests: 20/20 PASS (100%)
- Integration tests: 3/3 PASS (100%)
- System tests: 10/10 PASS (100%)
- Concurrency stress test: PASS

## Coverage
- Statement: 100%
- Branch: 100%
- Condition: 100%

## Static Analysis
- Cppcheck: 0 issues
- Clang-tidy: 0 issues
- MISRA C: 0 mandatory violations

## Complexity
- timeout_init: CCN=3
- timeout_check: CCN=5
- timeout_reset: CCN=2
- Module total: CCN=35 (within limit)

## Traceability
- All commits reference CRs
- RTM updated with all CRs
- Traceability validation: PASS

## Conclusion
✅ Comprehensive verification PASSED
✅ All CRs (CR-120, CR-121, CR-123) verified
✅ No emergent risks detected
✅ Safe to close CRs and update baseline

**Verified by**: Bob Smith (VER)  
**Date**: 2024-03-13  
**VMGR Approval**: Carol White (VMGR)  
**Date**: 2024-03-13
EOF
```

---

## 8. Baseline Update

### 8.1 Baseline Update Process

**After CR closure**, baseline is updated:

**Step 1: Determine Baseline Impact**
- Minor change (bug fix, < 5% lines changed) → Patch baseline (e.g., v1.0.1)
- Major change (feature, ≥ 5% lines changed) → Minor baseline (e.g., v1.1.0)
- Breaking change (API change) → Major baseline (e.g., v2.0.0)

**Step 2: Create Baseline Tag**
```bash
# Patch baseline (bug fix)
git tag -a v1.0.1 -m "Baseline v1.0.1

Bug fixes:
- CR-123: Fix null pointer dereference in timeout module

Verification:
- All tests pass (100%)
- Coverage: 100%
- Static analysis clean

Approved by: VMGR
"

git push origin v1.0.1

# Or minor baseline (new feature)
git tag -a v1.1.0 -m "Baseline v1.1.0

New features:
- CR-120: Multi-sensor timeout support

Bug fixes:
- CR-123: Fix null pointer dereference

Verification:
- All tests pass (100%)
- Coverage: 100%
- Static analysis clean

Approved by: VMGR
"

git push origin v1.1.0
```

**Step 3: Update Baseline Documentation**
```bash
# Create baseline record
workspace.py wf create-baseline v1.0.1
# Output: ✅ Baseline v1.0.1 created and documented
```

**Step 4: Update CHANGELOG.md**
```markdown
## [1.0.1] - 2024-03-13

### Fixed
- CR-123: Fix null pointer dereference in timeout module
  - Add bounds check in timeout_check()
  - Add test case for invalid sensor_id
  - Safety impact: Eliminates crash risk (H-05 mitigation)

### Verification
- Unit tests: 16/16 PASS
- Integration tests: 3/3 PASS
- Coverage: 100% statement, branch, condition
- Static analysis: Clean (Cppcheck, Clang)

### Approved by
- Verifier: Bob Smith (VER)
- V&V Manager: Carol White (VMGR)
```

**Step 5: Archive CR Records**
```bash
# Move CR to archive
git add changes/CR-123.yaml
git commit -m "chore(cm): Close CR-123 and update baseline v1.0.1

CR-123 closed: Null pointer fix implemented, verified, and validated.

Baseline Impact:
- Patch release: v1.0.1
- Bug fix only (no API change)
- Backward compatible

[CR-123] CR closure
Baseline: v1.0.1
Approved-by: VMGR
"
```

### 8.2 Baseline Comparison

**Compare two baselines**:

```bash
# Compare baselines
workspace.py wf diff-baseline v1.0.0 v1.0.1

# Output:
# Differences between v1.0.0 and v1.0.1:
# 
# Change Requests:
# - CR-123: Fix null pointer dereference (CLOSED)
# 
# Code Changes:
# - src/timeout.c: +1 line (bounds check added)
# - tests/unit_test_timeout.c: +15 lines (1 test added)
# 
# Documentation Changes:
# - CHANGELOG.md: Updated with v1.0.1 release notes
# - docs/verification/VR-CR-123.md: Verification report added
# 
# Test Results:
# - Unit tests: 15 → 16 tests (+1)
# - Integration tests: 3 tests (unchanged)
# - System tests: 10 scenarios (unchanged)
# 
# Metrics:
# - Lines of code: 10,000 → 10,001 (+0.01%)
# - Complexity: 250 → 250 CCN (unchanged)
# - Coverage: 100% (unchanged)
# 
# Safety Impact:
# - Hazard H-05: Risk reduced from RPN 45 to RPN 18
# - No new hazards introduced
# 
# Verification:
# ✅ All tests passed
# ✅ Coverage maintained at 100%
# ✅ Static analysis clean
# ✅ VMGR approved
```

---

## 9. Tool Integration

### 9.1 Workspace CLI Integration

**`workspace.py wf` commands** for change control:

```bash
# CR Creation
workspace.py wf create-cr --title "Fix null pointer" --category DEFECT --priority HIGH --requester "Jane Smith (VER)"
# Output: ✅ CR-123 created: changes/CR-123.yaml

# CR Status Update
workspace.py wf update-cr CR-123 --status APPROVED
# Output: ✅ CR-123 status updated: SUBMITTED → APPROVED

# CR Details
workspace.py wf show-cr CR-123
# Output: (displays full CR YAML)

# CR List (by status)
workspace.py wf list-cr --status PENDING_CCB
# Output: CR-120, CR-121, CR-123

# CR List (by priority)
workspace.py wf list-cr --priority CRITICAL
# Output: CR-123

# CR Metrics
workspace.py wf cr-metrics
# Output:
# Total CRs: 25 (10 open, 15 closed)
# By category: Defect 12, Enhancement 8, Safety 3, Documentation 2
# By priority: Critical 2, High 5, Medium 10, Low 8
# Avg resolution time: 5 days

# CR Report
workspace.py wf cr-report --month 2024-03
# Output: Monthly CR report written to docs/cm/cr-report-2024-03.md
```

### 9.2 Git Integration

**Git commands** for change control:

```bash
# Find all commits for a CR
git log --all --grep="CR-123"

# Show CR impact (files changed)
git log --all --grep="CR-123" --stat

# Show CR commits with details
git log --all --grep="CR-123" --pretty=format:"%h - %s%n%b%n" --stat

# Count commits for a CR
git log --all --grep="CR-123" --oneline | wc -l

# Find all CRs affecting a file
git log --all --grep="CR-" -- src/timeout.c

# Generate CR closure report
git log --all --grep="CR-123" --pretty=format:"- %h: %s" > docs/cm/CR-123-commits.txt
```

### 9.3 Traceability Integration

**`workspace.py trace` commands** for CR traceability:

```bash
# Link CR to requirement
workspace.py trace link-cr CR-123 REQ-42
# Output: ✅ CR-123 linked to REQ-42

# Show all CRs for a requirement
workspace.py trace show-req REQ-42 --include-crs
# Output:
# REQ-42: System shall detect sensor timeout within 100ms
# Status: Implemented
# Change Requests:
# - CR-120: Add multi-sensor support (CLOSED)
# - CR-123: Fix null pointer dereference (CLOSED)

# Show all requirements for a CR
workspace.py trace show-cr CR-123
# Output:
# CR-123: Fix null pointer dereference
# Status: CLOSED
# Related requirements: REQ-42, REQ-10

# Validate CR traceability
workspace.py trace validate-ci --cr CR-123
# Output:
# ✅ CR-123 commits reference requirements
# ✅ CR-123 linked to requirements (REQ-42, REQ-10)
# ✅ RTM updated with CR-123
```

---

## 10. Automation Scripts

### 10.1 CR Impact Analyzer

**`tools/cr_impact_analyzer.py`** (200 lines):

```python
#!/usr/bin/env python3
"""
CR Impact Analyzer for EN 50128 Change Control.

Analyzes change request impact on configuration items, safety,
lifecycle phases, effort, and schedule.

Usage:
    python3 cr_impact_analyzer.py --cr-id CR-123
    python3 cr_impact_analyzer.py --cr-id CR-123 --report impact-CR-123.md
"""

import argparse
import yaml
import subprocess
import os
from typing import List, Dict, Set

class CRImpactAnalyzer:
    def __init__(self, cr_id: str):
        self.cr_id = cr_id
        self.cr_file = f"changes/{cr_id}.yaml"
        self.cr_data = None
        
    def load_cr(self):
        """Load CR from YAML file."""
        if not os.path.exists(self.cr_file):
            raise FileNotFoundError(f"CR file not found: {self.cr_file}")
        
        with open(self.cr_file, 'r') as f:
            self.cr_data = yaml.safe_load(f)
    
    def analyze_affected_cis(self) -> Dict:
        """Analyze affected configuration items."""
        affected_cis = self.cr_data.get('affected_cis', [])
        
        result = {
            'source_code': [],
            'tests': [],
            'documentation': [],
            'requirements': []
        }
        
        for ci in affected_cis:
            if ci.endswith('.c') or ci.endswith('.h'):
                # Analyze source code
                result['source_code'].append({
                    'path': ci,
                    'functions': self._extract_functions(ci),
                    'complexity': self._calculate_complexity(ci)
                })
            elif ci.startswith('tests/'):
                result['tests'].append(ci)
            elif ci.startswith('docs/'):
                result['documentation'].append(ci)
        
        return result
    
    def analyze_safety_impact(self) -> Dict:
        """Analyze safety impact."""
        safety_related = self.cr_data.get('safety_related', False)
        sil_level = self.cr_data.get('sil_level', 0)
        
        if not safety_related:
            return {'safety_critical': False}
        
        # Check if affected requirements are safety-critical
        affected_reqs = self.cr_data.get('affected_requirements', [])
        
        result = {
            'safety_critical': True,
            'sil_level': sil_level,
            'affected_requirements': affected_reqs,
            'hazards': self._find_related_hazards(affected_reqs)
        }
        
        return result
    
    def analyze_lifecycle_impact(self) -> Dict:
        """Determine which lifecycle phases affected."""
        category = self.cr_data.get('category', '')
        affected_cis = self.cr_data.get('affected_cis', [])
        
        phases_affected = set()
        
        # Determine phase based on affected CIs
        for ci in affected_cis:
            if 'requirements' in ci or ci.endswith('SRS'):
                phases_affected.add('2-requirements')
                phases_affected.add('3-design')
                phases_affected.add('4-implementation')
                phases_affected.add('5-integration')
                phases_affected.add('6-validation')
            elif 'design' in ci or ci.endswith('SAS') or ci.endswith('SDS'):
                phases_affected.add('3-design')
                phases_affected.add('4-implementation')
                phases_affected.add('5-integration')
                phases_affected.add('6-validation')
            elif ci.endswith('.c') or ci.endswith('.h'):
                phases_affected.add('4-implementation')
                phases_affected.add('5-integration')
                phases_affected.add('6-validation')
            elif ci.startswith('tests/'):
                phases_affected.add('5-integration')
                phases_affected.add('6-validation')
        
        return {
            'phases_affected': sorted(list(phases_affected)),
            'return_to_phase': min(phases_affected) if phases_affected else None
        }
    
    def estimate_effort(self) -> Dict:
        """Estimate implementation and verification effort."""
        category = self.cr_data.get('category', '')
        affected_cis = self.cr_data.get('affected_cis', [])
        
        # Simple heuristic: 1 hour per CI + 2 hours testing + 1 hour verification
        implementation = len(affected_cis) * 1.0
        testing = 2.0
        verification = 1.0
        documentation = 0.5
        
        total = implementation + testing + verification + documentation
        
        return {
            'implementation': implementation,
            'testing': testing,
            'verification': verification,
            'documentation': documentation,
            'total': total
        }
    
    def analyze_cumulative_impact(self) -> Dict:
        """Check for related CRs (cumulative impact)."""
        # Find CRs affecting same CIs
        affected_cis = set(self.cr_data.get('affected_cis', []))
        
        related_crs = []
        for cr_file in os.listdir('changes/'):
            if not cr_file.endswith('.yaml') or cr_file == os.path.basename(self.cr_file):
                continue
            
            with open(f'changes/{cr_file}', 'r') as f:
                other_cr = yaml.safe_load(f)
            
            other_cis = set(other_cr.get('affected_cis', []))
            
            if affected_cis & other_cis:  # Intersection
                related_crs.append({
                    'cr_id': other_cr.get('cr_id'),
                    'title': other_cr.get('title'),
                    'status': other_cr.get('status'),
                    'common_cis': list(affected_cis & other_cis)
                })
        
        comprehensive_verification_required = len(related_crs) >= 2
        
        return {
            'related_crs': related_crs,
            'comprehensive_verification_required': comprehensive_verification_required
        }
    
    def generate_report(self) -> str:
        """Generate impact analysis report."""
        affected_cis = self.analyze_affected_cis()
        safety_impact = self.analyze_safety_impact()
        lifecycle_impact = self.analyze_lifecycle_impact()
        effort = self.estimate_effort()
        cumulative = self.analyze_cumulative_impact()
        
        report = f"""# Impact Analysis Report: {self.cr_id}

**Title**: {self.cr_data.get('title')}  
**Category**: {self.cr_data.get('category')}  
**Priority**: {self.cr_data.get('priority')}  
**Requester**: {self.cr_data.get('requester', {}).get('name')}  

## Affected Configuration Items

### Source Code
{self._format_list(affected_cis['source_code'])}

### Tests
{self._format_list(affected_cis['tests'])}

### Documentation
{self._format_list(affected_cis['documentation'])}

## Safety Impact

**Safety Critical**: {safety_impact.get('safety_critical')}  
**SIL Level**: {safety_impact.get('sil_level')}  

## Lifecycle Impact

**Phases Affected**: {', '.join(lifecycle_impact['phases_affected'])}  
**Return to Phase**: {lifecycle_impact['return_to_phase']}  

## Effort Estimate

- Implementation: {effort['implementation']:.1f} hours
- Testing: {effort['testing']:.1f} hours
- Verification: {effort['verification']:.1f} hours
- Documentation: {effort['documentation']:.1f} hours
- **Total**: {effort['total']:.1f} hours

## Cumulative Impact

**Related CRs**: {len(cumulative['related_crs'])}  
**Comprehensive Verification Required**: {cumulative['comprehensive_verification_required']}  

{self._format_related_crs(cumulative['related_crs'])}

## Recommendation

{self._generate_recommendation(safety_impact, effort, cumulative)}

---
**Analyzed by**: Configuration Manager  
**Date**: {subprocess.check_output(['date', '+%Y-%m-%d']).decode().strip()}
"""
        return report
    
    def _extract_functions(self, file_path: str) -> List[str]:
        """Extract function names from C file."""
        # Simple grep for function definitions
        try:
            output = subprocess.check_output(
                f"grep -E '^[a-zA-Z_][a-zA-Z0-9_]*\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\\(' {file_path}",
                shell=True
            ).decode()
            functions = [line.split()[1].split('(')[0] for line in output.strip().split('\n')]
            return functions
        except:
            return []
    
    def _calculate_complexity(self, file_path: str) -> int:
        """Calculate cyclomatic complexity using lizard."""
        try:
            output = subprocess.check_output(f"lizard {file_path} -l c", shell=True).decode()
            # Parse lizard output for total complexity
            for line in output.split('\n'):
                if 'Total nloc' in line:
                    parts = line.split()
                    return int(parts[-1])
            return 0
        except:
            return 0
    
    def _find_related_hazards(self, requirements: List[str]) -> List[str]:
        """Find hazards related to requirements."""
        # Search Hazard Log for related hazards
        hazards = []
        try:
            with open('docs/safety/Hazard-Log-v1.0.md', 'r') as f:
                content = f.read()
                for req in requirements:
                    if req in content:
                        # Extract hazard IDs (simplified)
                        hazards.append(f"H-XX (related to {req})")
        except:
            pass
        return hazards
    
    def _format_list(self, items):
        if not items:
            return "- None"
        return '\n'.join([f"- {item}" for item in items])
    
    def _format_related_crs(self, related_crs):
        if not related_crs:
            return "No related CRs found."
        
        result = "Related CRs:\n"
        for cr in related_crs:
            result += f"- {cr['cr_id']}: {cr['title']} (Status: {cr['status']})\n"
            result += f"  Common CIs: {', '.join(cr['common_cis'])}\n"
        return result
    
    def _generate_recommendation(self, safety_impact, effort, cumulative):
        """Generate approval recommendation."""
        if safety_impact.get('safety_critical') and safety_impact.get('sil_level') >= 3:
            rec = "**RECOMMEND APPROVE** (Critical safety fix)\n"
            rec += "- Safety critical for SIL 3+\n"
            rec += "- Requires VMGR approval\n"
        elif effort['total'] > 40:
            rec = "**RECOMMEND DEFER** (High effort)\n"
            rec += "- Effort exceeds sprint capacity\n"
            rec += "- Consider breaking into smaller CRs\n"
        elif cumulative['comprehensive_verification_required']:
            rec = "**RECOMMEND APPROVE WITH CONDITIONS**\n"
            rec += "- Comprehensive verification required (related CRs)\n"
            rec += "- Full regression test needed\n"
        else:
            rec = "**RECOMMEND APPROVE**\n"
            rec += "- Low risk, clear solution\n"
        
        return rec


def main():
    parser = argparse.ArgumentParser(description='CR Impact Analyzer')
    parser.add_argument('--cr-id', required=True, help='Change Request ID (e.g., CR-123)')
    parser.add_argument('--report', help='Output report file (markdown)')
    
    args = parser.parse_args()
    
    analyzer = CRImpactAnalyzer(args.cr_id)
    analyzer.load_cr()
    
    report = analyzer.generate_report()
    
    if args.report:
        with open(args.report, 'w') as f:
            f.write(report)
        print(f"✅ Impact analysis report written to {args.report}")
    else:
        print(report)


if __name__ == '__main__':
    main()
```

### 10.2 CR Tracker Script

**`tools/cr_tracker.py`** (150 lines) - tracks CR status, generates metrics:

```python
#!/usr/bin/env python3
"""
CR Tracker for EN 50128 Change Control.

Tracks CR status, generates metrics and reports.

Usage:
    python3 cr_tracker.py --list --status PENDING_CCB
    python3 cr_tracker.py --metrics
    python3 cr_tracker.py --report --month 2024-03
"""

import argparse
import yaml
import os
from datetime import datetime
from collections import Counter
from typing import List, Dict

class CRTracker:
    def __init__(self):
        self.crs = []
        self.load_all_crs()
    
    def load_all_crs(self):
        """Load all CR files."""
        for cr_file in os.listdir('changes/'):
            if cr_file.endswith('.yaml'):
                with open(f'changes/{cr_file}', 'r') as f:
                    cr = yaml.safe_load(f)
                    self.crs.append(cr)
    
    def list_crs(self, status=None, priority=None, category=None):
        """List CRs filtered by status, priority, or category."""
        filtered = self.crs
        
        if status:
            filtered = [cr for cr in filtered if cr.get('status') == status]
        if priority:
            filtered = [cr for cr in filtered if cr.get('priority') == priority]
        if category:
            filtered = [cr for cr in filtered if cr.get('category') == category]
        
        print(f"CRs (Total: {len(filtered)}):")
        for cr in filtered:
            print(f"- {cr['cr_id']}: {cr['title']}")
            print(f"  Status: {cr['status']}, Priority: {cr['priority']}, Category: {cr['category']}")
    
    def generate_metrics(self):
        """Generate CR metrics."""
        total = len(self.crs)
        open_crs = [cr for cr in self.crs if cr['status'] not in ['CLOSED', 'REJECTED']]
        closed_crs = [cr for cr in self.crs if cr['status'] == 'CLOSED']
        
        categories = Counter([cr['category'] for cr in self.crs])
        priorities = Counter([cr['priority'] for cr in self.crs])
        statuses = Counter([cr['status'] for cr in self.crs])
        
        # Calculate average resolution time
        resolution_times = []
        for cr in closed_crs:
            if 'closure' in cr and 'closed_date' in cr['closure']:
                submit_date = datetime.fromisoformat(cr['requester']['date'])
                close_date = datetime.fromisoformat(cr['closure']['closed_date'])
                resolution_times.append((close_date - submit_date).days)
        
        avg_resolution = sum(resolution_times) / len(resolution_times) if resolution_times else 0
        
        print("CR Metrics:")
        print(f"- Total CRs: {total} ({len(open_crs)} open, {len(closed_crs)} closed)")
        print(f"- By category: {dict(categories)}")
        print(f"- By priority: {dict(priorities)}")
        print(f"- By status: {dict(statuses)}")
        print(f"- Average resolution time: {avg_resolution:.1f} days")
    
    def generate_report(self, month: str):
        """Generate monthly CR report."""
        # Filter CRs by submission month
        month_crs = [cr for cr in self.crs if cr['requester']['date'].startswith(month)]
        
        report = f"""# Change Request Report: {month}

## Summary

- Total CRs submitted: {len(month_crs)}
- Categories: {Counter([cr['category'] for cr in month_crs])}
- Priorities: {Counter([cr['priority'] for cr in month_crs])}

## CRs Submitted

"""
        for cr in month_crs:
            report += f"### {cr['cr_id']}: {cr['title']}\n\n"
            report += f"- **Category**: {cr['category']}\n"
            report += f"- **Priority**: {cr['priority']}\n"
            report += f"- **Status**: {cr['status']}\n"
            report += f"- **Requester**: {cr['requester']['name']}\n\n"
        
        report_file = f"docs/cm/cr-report-{month}.md"
        with open(report_file, 'w') as f:
            f.write(report)
        
        print(f"✅ CR report written to {report_file}")


def main():
    parser = argparse.ArgumentParser(description='CR Tracker')
    parser.add_argument('--list', action='store_true', help='List CRs')
    parser.add_argument('--status', help='Filter by status')
    parser.add_argument('--priority', help='Filter by priority')
    parser.add_argument('--category', help='Filter by category')
    parser.add_argument('--metrics', action='store_true', help='Generate CR metrics')
    parser.add_argument('--report', action='store_true', help='Generate CR report')
    parser.add_argument('--month', help='Report month (YYYY-MM)')
    
    args = parser.parse_args()
    
    tracker = CRTracker()
    
    if args.list:
        tracker.list_crs(status=args.status, priority=args.priority, category=args.category)
    elif args.metrics:
        tracker.generate_metrics()
    elif args.report:
        if not args.month:
            print("ERROR: --month required for --report")
            return 1
        tracker.generate_report(args.month)
    else:
        print("Use --list, --metrics, or --report")
        return 1
    
    return 0


if __name__ == '__main__':
    main()
```

---

## 11. Example Scenarios

### 11.1 Scenario 1: Critical Defect CR (SIL 3)

**Context**: Critical null pointer dereference discovered in timeout module during fault injection testing.

**Complete workflow** (CR-123):

```bash
# Day 1: CR Submission (by VER)
workspace.py wf create-cr --title "Fix null pointer in timeout module" \
  --category DEFECT --priority CRITICAL --safety-related true --sil-level 3 \
  --description "Null pointer dereference in timeout_check()..." \
  --requester "Jane Smith (VER)" \
  --affected-req "REQ-42,REQ-10" \
  --affected-ci "src/timeout.c,tests/unit_test_timeout.c"

# CR-123 created: changes/CR-123.yaml (status: SUBMITTED)

# Day 1: Impact Analysis (by CM)
python3 tools/cr_impact_analyzer.py --cr-id CR-123 --report docs/cm/impact-CR-123.md
# Output: Impact analysis complete
# - Safety critical: Yes (SIL 3)
# - Effort: 4.5 hours
# - Recommendation: APPROVE (critical safety fix)

# Update CR with impact analysis
workspace.py wf update-cr CR-123 --status IN_REVIEW --impact-analysis docs/cm/impact-CR-123.md

# Day 2: CCB Meeting
# CCB reviews CR-123
# Decision: APPROVED (unanimous, CRITICAL priority)
# Conditions: Test case required, VMGR approval after verification

workspace.py wf update-cr CR-123 --status APPROVED --ccb-decision "APPROVED (2024-03-12)"

# Day 2: Implementation (by IMP)
git checkout develop
git checkout -b bugfix/CR-123-null-pointer-fix

# [Implement fix as shown in Section 6.2]
# Commits: a1b2c3d (fix), b2c3d4e (test)

git push -u origin bugfix/CR-123-null-pointer-fix
# Create pull request (via GitHub UI)

workspace.py wf update-cr CR-123 --status IMPLEMENTATION

# Day 2: Code Review (by VER)
# Reviews approve: @bob-ver, @alice-pm
# CI passes: Build ✅, Tests ✅, Coverage ✅, Static Analysis ✅

# Merge to develop

workspace.py wf update-cr CR-123 --status VERIFICATION --commits "a1b2c3d,b2c3d4e"

# Day 3: Verification (by VER)
# Run comprehensive tests
make test coverage static-analysis

# Create Verification Report
cat > docs/verification/VR-CR-123.md << 'EOF'
# Verification Report: CR-123

**Verified by**: Bob Smith (VER)  
**Date**: 2024-03-13

## Test Results
- Unit tests: 16/16 PASS
- Integration tests: 3/3 PASS
- Coverage: 100% statement, branch, condition

## Static Analysis
- Cppcheck: 0 issues
- Clang: 0 issues

## Conclusion
✅ PASS
EOF

workspace.py wf update-cr CR-123 --status VERIFIED

# Day 3: Validation (by VMGR)
# VMGR reviews Verification Report
# Performs independent validation

cat > docs/validation/VaR-CR-123.md << 'EOF'
# Validation Report: CR-123

**Validated by**: Carol White (VMGR)  
**Date**: 2024-03-13

## System Testing
- Scenario S-08 (timeout monitoring): PASS

## Safety Impact Verification
- Hazard H-05 risk reduced: RPN 45 → 18

## Conclusion
✅ PASS  
✅ VMGR APPROVED
EOF

# Day 3: Closure (by CM)
workspace.py wf update-cr CR-123 --status CLOSED --vmgr-approval "Carol White (VMGR, 2024-03-13)"

# Create baseline
git tag -a v1.0.1 -m "Baseline v1.0.1: CR-123 fix"
git push origin v1.0.1

# Update CHANGELOG.md
# Archive CR

# CR-123 complete: 3 days (CRITICAL priority met <24hr approval, 3 days total)
```

---

## Summary

This **Change Control Workflow** provides comprehensive guidance for the formal Change Request (CR) process in EN 50128-compliant railway software development.

**Key Takeaways**:
1. **Change control is MANDATORY for ALL SIL levels** (EN 50128 Table A.9 #5)
2. **Nine required aspects** per EN 50128 Section 6.6.4.1 (a-i) must be addressed
3. **All changes initiate return to appropriate lifecycle phase** (Section 6.6.4.2)
4. **CCB approval required** before implementation (SIL 3-4 MANDATORY)
5. **Impact analysis** required (written, comprehensive for SIL 3-4)
6. **Re-verification and re-validation** after implementation (independent for SIL 3-4)
7. **Cumulative impact analysis** for multiple related CRs (SIL 3-4)
8. **Baseline update** after CR closure (semantic versioning)
9. **Complete traceability** (CR ↔ Requirements ↔ Code ↔ Tests)
10. **Data recording** for all CRs (metrics, status, resolution time)

**Related Workflows**:
- **WF-CM-001**: Version Control Workflow (commit conventions, Git integration)
- **WF-CM-003**: Baseline Management Workflow (baseline creation, PCA/FCA audits)
- **WF-CM-004**: Configuration Status Accounting (CI tracking, metrics)
- **Lifecycle-Coordination Workflow 4**: Iteration and Change Management (phase re-entry process)

**EN 50128 Compliance**:
- ✅ Section 6.6.4: Modification and Change Control
- ✅ Section 6.6.4.1: Nine required aspects (a-i)
- ✅ Section 6.6.4.2: Return to appropriate lifecycle phase
- ✅ Table A.9 #5: Software Configuration Management (MANDATORY ALL SIL)
- ✅ Table A.9 #7: Traceability (MANDATORY SIL 3-4)
- ✅ Table A.9 #8: Data Recording and Analysis (MANDATORY SIL 3-4)

---

**Document Control**

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2024-03-15 | Configuration Team | Initial version |

**Approvals**

| Role | Name | Signature | Date |
|------|------|-----------|------|
| Configuration Manager | | | |
| Quality Assurance | | | |
| VMGR (SIL 3-4) | | | |

---

*End of Change Control Workflow (WF-CM-002)*
