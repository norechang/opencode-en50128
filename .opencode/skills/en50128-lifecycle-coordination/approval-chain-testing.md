# Approval Chain Testing Scenarios

This document provides test scenarios for the PM-VER-VAL-COD approval chain workflow for EN 50128 deliverables.

## Overview

The approval chain enforces independence requirements (EN 50128 Section 5.1.2) by restricting which roles can mark deliverables at each status level:

- **PM (Project Manager)**: Can mark deliverables as `draft` or `complete`
- **VER (Verifier)**: Can mark deliverables as `verified` or `rejected` (requires `complete` first)
- **VAL (Validator)**: Can mark deliverables as `validated` or `rejected` (requires `verified` first for SIL 3-4)
- **COD (Lifecycle Coordinator)**: Can mark deliverables as `approved` (requires `validated` for SIL 3-4)

---

## Test Scenario 1: Happy Path - SIL 3 Planning Phase Deliverable

**Context**: train_door_control2 project (SIL 3), Planning phase, SQAP deliverable

**Initial State**:
- SQAP created by PM
- Current status: `draft`
- File: `examples/train_door_control2/docs/plans/SQAP.md`

### Step 1: PM marks SQAP as complete

**Command**:
```bash
/cod pm-update-deliverables SQAP=complete
```

**Expected Behavior**:
- COD updates `LIFECYCLE_STATE.md`:
  - SQAP status: `draft` → `complete`
  - PM date: 2026-02-18
- COD adds entry to "Deliverable Approval Chain History" table:
  - `2026-02-18 | SQAP | Planning | draft | complete | PM | [username] | Ready for verification`
- COD output message:
  ```
  ✓ SQAP marked as 'complete' by PM
  
  Next step: Independent Verifier (VER) must verify this deliverable.
  Command: /cod ver-update-deliverables SQAP=verified
  ```

### Step 2: VER verifies SQAP

**Command**:
```bash
/cod ver-update-deliverables SQAP=verified
```

**Expected Behavior**:
- COD verifies prerequisite: SQAP status must be `complete` ✓
- COD updates `LIFECYCLE_STATE.md`:
  - SQAP status: `complete` → `verified`
  - VER date: 2026-02-19
- COD adds entry to approval chain history:
  - `2026-02-19 | SQAP | Planning | complete | verified | VER | [username] | Verification passed`
- COD output message:
  ```
  ✓ SQAP marked as 'verified' by VER
  
  Next step: Independent Validator (VAL) must validate this deliverable (SIL 3 requirement).
  Command: /cod val-update-deliverables SQAP=validated
  ```

### Step 3: VAL validates SQAP

**Command**:
```bash
/cod val-update-deliverables SQAP=validated
```

**Expected Behavior**:
- COD verifies prerequisite: SQAP status must be `verified` ✓ (SIL 3 requirement)
- COD updates `LIFECYCLE_STATE.md`:
  - SQAP status: `verified` → `validated`
  - VAL date: 2026-02-20
- COD adds entry to approval chain history:
  - `2026-02-20 | SQAP | Planning | verified | validated | VAL | [username] | Validation passed`
- COD output message:
  ```
  ✓ SQAP marked as 'validated' by VAL
  
  Deliverable ready for COD final approval.
  When all Planning phase deliverables are validated, PM can request gate check:
  Command: /cod pm-report-planning-complete
  ```

### Step 4: PM reports planning complete (triggers gate check)

**Command**:
```bash
/cod pm-report-planning-complete
```

**Expected Behavior**:
- COD automatically runs gate check for Planning phase
- COD verifies ALL Planning phase deliverables have complete approval chains:
  - SQAP: `validated` ✓
  - SCMP: `validated` ✓
  - SVP: `validated` ✓
  - SVaP: `validated` ✓
  - SQAP-Verification: `validated` ✓
- COD marks all deliverables as `approved` (COD final approval)
- COD updates `LIFECYCLE_STATE.md`:
  - All Planning deliverables: `validated` → `approved`
  - COD dates: 2026-02-20
  - Phase 1 status: `In Progress` → `Complete`
  - Phase 1 gate: `PASSED`
- COD adds entries to approval chain history for each deliverable
- COD adds entry to "Gate Check History" table:
  - `2026-02-20 | Planning | PASSED | 5 | 5 | All deliverables validated, approval chain complete`
- COD output message:
  ```
  ✓ GATE CHECK PASSED: Planning Phase
  
  All deliverables validated by independent VER and VAL.
  Baseline 0 established: Planning documents approved.
  
  Ready to proceed to Phase 2: Requirements
  Next steps:
  1. PM coordinates with REQ agent to establish SRS
  2. User approval REQUIRED for all requirement activities
  ```

---

## Test Scenario 2: Independence Violation - PM Attempts to Mark as Verified

**Context**: train_door_control2 project (SIL 3), SCMP deliverable at `complete` status

**Command**:
```bash
/cod pm-update-deliverables SCMP=verified
```

**Expected Behavior**:
- COD detects unauthorized status change
- COD rejects the request
- COD output message:
  ```
  ✗ ERROR: Independence violation
  
  PM cannot mark deliverable as 'verified'.
  
  Rationale: EN 50128 Section 5.1.2 requires independent verification for SIL 3-4 projects.
  The Verifier (VER) role must be independent from the Project Manager (PM).
  
  PM authority is limited to:
  - draft (initial creation)
  - complete (ready for verification)
  
  To verify SCMP, the independent Verifier must use:
  Command: /cod ver-update-deliverables SCMP=verified
  ```

---

## Test Scenario 3: Independence Violation - PM Attempts to Mark as Validated

**Context**: train_door_control2 project (SIL 3), SVP deliverable at `verified` status

**Command**:
```bash
/cod pm-update-deliverables SVP=validated
```

**Expected Behavior**:
- COD detects unauthorized status change
- COD rejects the request
- COD output message:
  ```
  ✗ ERROR: Independence violation
  
  PM cannot mark deliverable as 'validated'.
  
  Rationale: EN 50128 Section 5.1.2.10.f requires that the Validator (VAL) SHALL NOT report to the Project Manager (PM) for SIL 3-4 projects.
  
  PM authority is limited to:
  - draft (initial creation)
  - complete (ready for verification)
  
  To validate SVP, the independent Validator must use:
  Command: /cod val-update-deliverables SVP=validated
  ```

---

## Test Scenario 4: Prerequisite Violation - VER Attempts to Verify Draft

**Context**: train_door_control2 project (SIL 3), SVaP deliverable at `draft` status

**Command**:
```bash
/cod ver-update-deliverables SVaP=verified
```

**Expected Behavior**:
- COD detects prerequisite violation
- COD rejects the request
- COD output message:
  ```
  ✗ ERROR: Prerequisite not met
  
  Cannot verify SVaP: current status is 'draft'.
  
  Verification requires deliverable to be marked as 'complete' by PM first.
  
  Required workflow:
  1. PM marks as complete: /cod pm-update-deliverables SVaP=complete
  2. VER verifies: /cod ver-update-deliverables SVaP=verified
  
  Current status: draft
  Required status: complete
  ```

---

## Test Scenario 5: Prerequisite Violation - VAL Attempts to Validate Before Verification

**Context**: train_door_control2 project (SIL 3), SQAP deliverable at `complete` status (not yet verified)

**Command**:
```bash
/cod val-update-deliverables SQAP=validated
```

**Expected Behavior**:
- COD detects prerequisite violation
- COD rejects the request
- COD output message:
  ```
  ✗ ERROR: Prerequisite not met (SIL 3 requirement)
  
  Cannot validate SQAP: current status is 'complete'.
  
  For SIL 3-4 projects, validation requires deliverable to be 'verified' by independent VER first.
  
  Required workflow:
  1. PM marks as complete: /cod pm-update-deliverables SQAP=complete ✓ (done)
  2. VER verifies: /cod ver-update-deliverables SQAP=verified (required next)
  3. VAL validates: /cod val-update-deliverables SQAP=validated
  
  Current status: complete
  Required status: verified
  ```

---

## Test Scenario 6: VER Rejects Deliverable

**Context**: train_door_control2 project (SIL 3), SCMP deliverable at `complete` status, VER finds issues

**Command**:
```bash
/cod ver-update-deliverables SCMP=rejected --reason "Section 3.2 missing baseline procedures, Section 4.1 has incomplete tool list"
```

**Expected Behavior**:
- COD updates `LIFECYCLE_STATE.md`:
  - SCMP status: `complete` → `rejected`
  - VER date: 2026-02-19 (rejection date)
- COD adds entry to approval chain history:
  - `2026-02-19 | SCMP | Planning | complete | rejected | VER | [username] | Section 3.2 missing baseline procedures, Section 4.1 has incomplete tool list`
- COD creates issue in "Risks and Issues" section:
  - Issue ID: ISS-001
  - Severity: High
  - Status: Open
  - Owner: PM
- COD output message:
  ```
  ✗ SCMP rejected by VER
  
  Reason: Section 3.2 missing baseline procedures, Section 4.1 has incomplete tool list
  
  Status: complete → rejected
  
  Next steps:
  1. PM coordinates with CM to address VER findings
  2. CM updates SCMP to resolve issues
  3. PM marks as complete again: /cod pm-update-deliverables SCMP=complete
  4. VER re-verifies: /cod ver-update-deliverables SCMP=verified
  
  Issue ISS-001 created and assigned to PM.
  ```

---

## Test Scenario 7: VAL Rejects Deliverable

**Context**: train_door_control2 project (SIL 3), SVP deliverable at `verified` status, VAL finds issues

**Command**:
```bash
/cod val-update-deliverables SVP=rejected --reason "Test coverage requirements unclear for SIL 3, static analysis tool qualification not addressed"
```

**Expected Behavior**:
- COD updates `LIFECYCLE_STATE.md`:
  - SVP status: `verified` → `rejected`
  - VAL date: 2026-02-20 (rejection date)
  - Note: VER verification date remains (shows it passed verification but failed validation)
- COD adds entry to approval chain history:
  - `2026-02-20 | SVP | Planning | verified | rejected | VAL | [username] | Test coverage requirements unclear for SIL 3, static analysis tool qualification not addressed`
- COD creates issue in "Risks and Issues" section:
  - Issue ID: ISS-002
  - Severity: High
  - Status: Open
  - Owner: PM (independent VAL reports issue, PM coordinates resolution)
- COD output message:
  ```
  ✗ SVP rejected by VAL
  
  Reason: Test coverage requirements unclear for SIL 3, static analysis tool qualification not addressed
  
  Status: verified → rejected
  
  Note: Deliverable passed VER verification but failed VAL validation.
  
  Next steps:
  1. PM coordinates with VER to address VAL findings
  2. VER updates SVP to resolve issues
  3. PM marks as complete: /cod pm-update-deliverables SVP=complete
  4. VER re-verifies: /cod ver-update-deliverables SVP=verified
  5. VAL re-validates: /cod val-update-deliverables SVP=validated
  
  Issue ISS-002 created and assigned to PM for coordination.
  ```

---

## Test Scenario 8: Gate Check Fails - Incomplete Approval Chains (SIL 3)

**Context**: train_door_control2 project (SIL 3), PM attempts gate check with incomplete approvals

**Current State**:
- SQAP: `validated` ✓
- SCMP: `complete` (missing VER verification) ✗
- SVP: `verified` (missing VAL validation) ✗
- SVaP: `draft` (missing PM complete) ✗
- SQAP-Verification: `not_started` ✗

**Command**:
```bash
/cod pm-report-planning-complete
```

**Expected Behavior**:
- COD runs gate check for Planning phase
- COD detects incomplete approval chains (SIL 3 strict enforcement)
- COD BLOCKS transition to next phase
- COD output message:
  ```
  ✗ GATE CHECK BLOCKED: Planning Phase (SIL 3 strict mode)
  
  Incomplete approval chains detected. SIL 3 requires all deliverables to pass PM→VER→VAL→COD approval.
  
  Deliverable Status:
  ✓ SQAP: validated (ready for COD approval)
  ✗ SCMP: complete (missing VER verification)
  ✗ SVP: verified (missing VAL validation)
  ✗ SVaP: draft (missing PM complete)
  ✗ SQAP-Verification: not_started (missing document)
  
  Required Actions:
  
  1. SCMP:
     - VER must verify: /cod ver-update-deliverables SCMP=verified
     - Then VAL must validate: /cod val-update-deliverables SCMP=validated
  
  2. SVP:
     - VAL must validate: /cod val-update-deliverables SVP=validated
  
  3. SVaP:
     - PM must mark complete: /cod pm-update-deliverables SVaP=complete
     - Then VER must verify: /cod ver-update-deliverables SVaP=verified
     - Then VAL must validate: /cod val-update-deliverables SVaP=validated
  
  4. SQAP-Verification:
     - Document must be created
     - PM must mark complete: /cod pm-update-deliverables SQAP-Verification=complete
     - Then VER must verify: /cod ver-update-deliverables SQAP-Verification=verified
     - Then VAL must validate: /cod val-update-deliverables SQAP-Verification=validated
  
  Phase transition BLOCKED until all approval chains complete.
  Criteria met: 1 / 5
  
  EN 50128 Rationale: SIL 3 requires independent verification and validation (Section 5.1.2).
  ```

---

## Test Scenario 9: SIL 0-1 Project - Relaxed Approval Chain

**Context**: New project (SIL 1), Advisory mode, Planning phase

**Initial State**:
- SQAP: `complete` (PM marked)
- No VER or VAL approval yet

**Command**:
```bash
/cod gate-check planning
```

**Expected Behavior**:
- COD runs gate check for Planning phase
- COD checks SIL level: SIL 1 (Advisory mode)
- COD detects missing VER/VAL approvals
- COD issues WARNING but allows transition
- COD output message:
  ```
  ⚠ GATE CHECK PASSED WITH WARNINGS: Planning Phase (SIL 1 advisory mode)
  
  All mandatory deliverables present, but approval chains incomplete.
  
  Deliverable Status:
  ⚠ SQAP: complete (missing VER verification, missing VAL validation)
  ⚠ SCMP: complete (missing VER verification, missing VAL validation)
  ⚠ SVP: complete (missing VER verification, missing VAL validation)
  ⚠ SVaP: complete (missing VER verification, missing VAL validation)
  
  WARNINGS:
  - Independent verification (VER) highly recommended for SIL 1 (Table A.5)
  - Independent validation (VAL) recommended for SIL 1 (Table A.7)
  
  Recommendations:
  1. Consider adding VER verification: /cod ver-update-deliverables <deliverable>=verified
  2. Consider adding VAL validation: /cod val-update-deliverables <deliverable>=validated
  
  Phase transition ALLOWED (advisory mode).
  Criteria met: 4 / 4 (mandatory)
  Optional criteria: 0 / 8 (VER/VAL approvals)
  
  Proceed to Phase 2: Requirements? [yes/no]
  ```

---

## Test Scenario 10: Multiple Deliverables Update

**Context**: train_door_control2 project (SIL 3), PM completes multiple deliverables at once

**Command**:
```bash
/cod pm-update-deliverables SQAP=complete SCMP=complete SVP=complete SVaP=complete
```

**Expected Behavior**:
- COD updates all specified deliverables in `LIFECYCLE_STATE.md`
- COD adds entries to approval chain history for each deliverable
- COD output message:
  ```
  ✓ Deliverables updated by PM:
  
  - SQAP: draft → complete (2026-02-18)
  - SCMP: draft → complete (2026-02-18)
  - SVP: draft → complete (2026-02-18)
  - SVaP: draft → complete (2026-02-18)
  
  Next step: Independent Verifier (VER) must verify all deliverables.
  
  Commands:
  /cod ver-update-deliverables SQAP=verified SCMP=verified SVP=verified SVaP=verified
  
  Or verify individually as reviews complete.
  ```

---

## Expected COD Implementation Behavior

### State Management

1. **Read LIFECYCLE_STATE.md** at start of every COD command
2. **Parse deliverable status** from LIFECYCLE_STATE.md (source of truth)
3. **Validate role authority** before any status change
4. **Validate prerequisites** (status flow: draft → complete → verified → validated → approved)
5. **Update LIFECYCLE_STATE.md** atomically (all changes at once)
6. **Append to approval chain history** (never delete history entries)

### Authority Validation

```
PM can mark:    draft, complete
VER can mark:   verified, rejected (requires complete first)
VAL can mark:   validated, rejected (requires verified first for SIL 3-4)
COD can mark:   approved (requires validated for SIL 3-4)
```

### Prerequisite Validation

```
draft → complete:   No prerequisite (PM can do anytime)
complete → verified: Requires status=complete (VER)
verified → validated: Requires status=verified (VAL, SIL 3-4)
complete → validated: Requires status=complete (VAL, SIL 0-2, if VER not used)
validated → approved: Requires status=validated (COD, during gate check)
```

### Gate Check Logic (SIL 3-4)

For each deliverable in current phase:
1. Check status is `validated` (PM→VER→VAL chain complete)
2. If any deliverable NOT validated: BLOCK gate check, list required actions
3. If all deliverables validated: PASS gate check, mark all as `approved`, transition phase

### Gate Check Logic (SIL 0-1)

For each deliverable in current phase:
1. Check status is at least `complete` (PM marked)
2. If any deliverable NOT complete: FAIL gate check
3. If all deliverables complete but NOT validated: PASS with WARNINGS
4. If all deliverables validated: PASS gate check

---

## Success Criteria

### For PM Commands
- ✓ PM can mark deliverables as `draft` or `complete`
- ✗ PM CANNOT mark deliverables as `verified`, `validated`, or `approved`
- ✓ Clear error messages explain independence violations
- ✓ Multiple deliverables can be updated in one command

### For VER Commands
- ✓ VER can mark deliverables as `verified` or `rejected`
- ✗ VER CANNOT verify deliverables that are not `complete`
- ✓ Clear error messages explain prerequisite violations
- ✓ Rejection reasons are recorded in approval chain history

### For VAL Commands
- ✓ VAL can mark deliverables as `validated` or `rejected`
- ✗ VAL CANNOT validate deliverables that are not `verified` (SIL 3-4)
- ✓ VAL CAN validate deliverables that are `complete` (SIL 0-2, if VER not used)
- ✓ Clear error messages explain prerequisite violations
- ✓ Rejection reasons are recorded in approval chain history

### For Gate Checks
- ✓ SIL 3-4: BLOCKS transition if approval chains incomplete
- ✓ SIL 0-2: WARNS but ALLOWS transition if VER/VAL missing
- ✓ Clear output shows which deliverables need action
- ✓ Clear output shows required commands to complete approval chains
- ✓ All deliverables marked `approved` when gate passes
- ✓ Gate check history recorded with pass/fail result

### For Independence
- ✓ VER must be independent from PM, Designer, Implementer (enforced by role restrictions)
- ✓ VAL must NOT report to PM (enforced by role restrictions, emphasized in documentation)
- ✓ PM CANNOT override VER or VAL decisions (no authority to mark verified/validated)
- ✓ COD enforces approval chain sequence (prevents skipping steps)

---

## Related Files

- `.opencode/commands/cod.md` - COD command definitions
- `.opencode/commands/pm.md` - PM command definitions and authority restrictions
- `.opencode/commands/ver.md` - VER command definitions and independence requirements
- `.opencode/commands/val.md` - VAL command definitions and independence requirements
- `.opencode/skills/en50128-lifecycle-coordination/project-state-template.md` - LIFECYCLE_STATE.md template
- `examples/train_door_control2/LIFECYCLE_STATE.md` - Live project state (test target)

---

**Document Version**: 1.0  
**Last Updated**: 2026-02-18  
**Author**: EN 50128 Lifecycle Coordination Team
