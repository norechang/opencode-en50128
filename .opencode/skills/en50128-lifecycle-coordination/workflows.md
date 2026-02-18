# EN 50128 Lifecycle Coordination Workflows

## Overview

This document provides practical workflow examples for using the Lifecycle Coordinator (COD) agent throughout the EN 50128 software development lifecycle.

---

## Workflow 1: Complete SIL 3 Project Lifecycle

### Scenario
New SIL 3 railway software project: Train Door Control System

### Workflow Steps

#### Step 1: Project Initialization

```bash
# Create project directory
cd examples
mkdir train_door_control
cd train_door_control

# Initialize COD for SIL 3 project
/cod plan --sil 3 --project train_door_control
```

**COD Response**:
```
✓ Lifecycle plan initialized for project: train_door_control
✓ SIL Level: 3 (Strict gate enforcement)
✓ Lifecycle Model: V-Model (Mandatory for SIL 3)
✓ Gate Enforcement: STRICT GATEKEEPER MODE

Created: examples/train_door_control/LIFECYCLE_STATE.md

Lifecycle Phases:
  1. [ ] Planning (Current Phase)
  2. [ ] Requirements
  3. [ ] Architecture & Design
  4. [ ] Implementation & Testing
  5. [ ] Integration
  6. [ ] Validation
  7. [ ] Assessment (Required for SIL 3)
  8. [ ] Deployment

Next Steps:
  1. Review lifecycle plan in LIFECYCLE_STATE.md
  2. Begin Phase 1 (Planning)
  3. When planning complete: /cod gate-check planning

Current Phase: Planning
```

---

#### Step 2: Phase 1 - Planning

```bash
# COD automatically monitors - Planning phase active

# PM coordinates planning activities
/pm    # Project planning

# PM works with agents to create planning documents
# Coordinate with QUA for SQAP
# Coordinate with CM for SCMP
# Coordinate with VER for SVP
# Coordinate with VAL for SVaP
```

**As planning documents are completed, PM reports to COD**:

```bash
# Report SQAP completion
/cod pm-update-deliverables --phase planning --deliverable SQAP --file docs/plans/SQAP.md --status complete

# Report SCMP completion
/cod pm-update-deliverables --phase planning --deliverable SCMP --file docs/plans/SCMP.md --status complete

# Report SVP completion
/cod pm-update-deliverables --phase planning --deliverable SVP --file docs/plans/SVP.md --status complete

# Report SVaP completion
/cod pm-update-deliverables --phase planning --deliverable SVaP --file docs/plans/SVaP.md --status complete
```

**COD tracks** these deliverables in LIFECYCLE_STATE.md and provides feedback on progress.

When all planning documents complete, PM reports planning phase completion:

```bash
/cod pm-report-planning-complete --project train_door_control
```

**COD Response** (if complete):
```
═══════════════════════════════════════════════════════
PM Planning Completion Report
═══════════════════════════════════════════════════════

Project: train_door_control (SIL 3, Strict Gatekeeper Mode)
Phase: Planning (Phase 1)
Reported by: PM (Project Manager)

Planning Phase Deliverables:
  ✓ SQAP (Software Quality Assurance Plan) - docs/plans/SQAP.md
  ✓ SCMP (Software Configuration Management Plan) - docs/plans/SCMP.md
  ✓ SVP (Software Verification Plan) - docs/plans/SVP.md
  ✓ SVaP (Software Validation Plan) - docs/plans/SVaP.md

═══════════════════════════════════════════════════════
Triggering Gate Check: Planning Phase
═══════════════════════════════════════════════════════

✓ Phase Gate Check: Planning Phase

[✓] Documents (5/5 complete)
  ✓ Software Quality Assurance Plan (approved)
  ✓ Software Configuration Management Plan (approved)
  ✓ Software Verification Plan (approved)
  ✓ Software Validation Plan (approved)
  ✓ SQAP Verification Report (approved)

[✓] Project Setup (4/4 complete)
  ✓ Version control initialized
  ✓ Baseline 0 established
  ✓ Build environment configured
  ✓ Tool qualification complete

[✓] Team Organization (4/4 satisfied)
  ✓ All roles assigned
  ✓ Independence requirements satisfied
  ✓ Reporting structure established
  ✓ Competency verified

═══════════════════════════════════════════════════════
GATE RESULT: ✓ PASSED
═══════════════════════════════════════════════════════

Planning phase complete. All SIL 3 criteria satisfied.

AUTHORIZED: Transition to Requirements phase

Current Phase: Requirements
```

---

#### Step 3: Phase 2 - Requirements

```bash
# Invoke Requirements Engineer
/req
```

**COD INTERCEPTS** (User approval required):
```
🔐 APPROVAL REQUIRED: Requirements Activity

The Requirements Engineer (REQ) will establish software requirements.

This activity will:
- Elicit requirements from stakeholders and system specification
- Create Software Requirements Specification (SRS)
- Update Requirements Traceability Matrix (RTM)

Approve requirements activity? [Y/n/details]
```

User enters: `Y`

**COD**:
```
✓ Requirements activity APPROVED

Logged approval in: LIFECYCLE_STATE.md
Proceeding with Requirements Engineer (REQ)...
```

**REQ agent** proceeds to create:
- SRS (docs/SRS.md)
- RTM (docs/RTM.md)
- Hazard Log (docs/Hazard-Log.md)

Parallel activities:
```bash
/saf   # Safety Engineer - hazard analysis
/tst   # Tester - Overall test specification
```

When requirements complete:

```bash
/cod gate-check requirements
```

**COD verifies** all criteria, authorizes transition to Design phase.

---

#### Step 4: Phase 3 - Architecture & Design

```bash
/des   # Designer - create architecture and design
/int   # Integrator - integration test specs
```

**COD monitors**, no user approval needed (only for requirements)

When design complete:

```bash
/cod gate-check design
```

**COD checks**:
- Complexity ≤ 10
- No recursion
- Static allocation only
- Modular design
- All deliverables approved

If passed → authorize transition to Implementation

---

#### Step 5: Phase 4 - Implementation & Testing

```bash
/imp   # Implementer - write C code
/tst   # Tester - unit tests
/ver   # Verifier - static analysis
/qua   # Quality - code review
```

**COD monitors**:
- MISRA C compliance
- Coverage targets (100% statement, branch, condition for SIL 3)
- Static analysis clean

When implementation complete:

```bash
/cod gate-check implementation
```

**COD Response** (example - gap detected):
```
✗ Phase Gate Check: Implementation Phase

[✓] Code Quality (6/7 satisfied)
  ✓ MISRA C:2012 compliant
  ✓ Static allocation only
  ✓ No recursion
  ✓ Fixed-width types
  ✓ All pointers validated
  ✓ All return values checked
  ✗ Input validation missing in parse_command() [src/parser.c:42]

[✗] Unit Testing (2/3 satisfied)
  ✓ All unit tests written
  ✓ All unit tests passing
  ✗ Coverage insufficient:
    - Statement: 98% (target: 100% for SIL 3) ✓
    - Branch: 95% (target: 100% for SIL 3) ✗
    - Condition: 92% (target: 100% for SIL 3) ✗

═══════════════════════════════════════════════════════
GATE RESULT: ✗ BLOCKED
═══════════════════════════════════════════════════════

Required Actions:
  1. Add input validation to parse_command() [src/parser.c:42]
  2. Add tests to cover missing branches (5% gap)
  3. Add tests to cover missing conditions (8% gap)

Once complete, re-run: /cod gate-check implementation
```

User fixes issues, then:

```bash
/cod gate-check implementation
```

**COD**: ✓ PASSED → Authorize transition to Integration

---

#### Step 6-8: Integration, Validation, Assessment, Deployment

Similar pattern continues:

```bash
# Integration
/int
/cod gate-check integration

# Validation (independent validator for SIL 3)
/val
/cod gate-check validation

# Assessment (mandatory for SIL 3, independent assessor)
# (Assessor role not in current agent set - external)
/cod gate-check assessment

# Deployment
/pm
/cm
/cod gate-check deployment
```

---

## Workflow 2: Requirement Change During Implementation

### Scenario
During implementation (Phase 4), stakeholder requests new requirement

### Workflow Steps

#### Step 1: Change Request Initiated

User (or PM):
```bash
# Request requirement change
/req
```

**COD INTERCEPTS**:
```
🔐 APPROVAL REQUIRED: Requirements Activity

WARNING: Requirement change during Implementation phase.

Current Phase: Implementation & Testing (Phase 4)
Activity: Modify Software Requirements

Impact Analysis:
  - Requirements phase already complete (Phase 2)
  - Design based on current requirements (Phase 3)
  - Implementation in progress (Phase 4)
  
Potential Impact:
  - Design may need updates
  - Code may need modification
  - Tests may need updates
  - Traceability must be maintained
  - Regression testing required

This is an ITERATION - returning to earlier phase.

Change Control Board (CCB) approval recommended.

Approve requirement modification? [Y/n/details]
```

User enters: `details`

**COD**:
```
Detailed Scope:

Proposed Changes:
  - Add new requirement REQ-043: "Emergency stop button"
  - Modify existing requirement REQ-012: "Door close timing"

Files to be modified:
  - docs/SRS.md (add REQ-043, modify REQ-012)
  - docs/RTM.md (update traceability)

Impact Assessment:
  Phase 2 (Requirements): Update SRS, RTM
  Phase 3 (Design): Review design for REQ-043, modify timing for REQ-012
  Phase 4 (Implementation): Implement new code, modify existing code
  Phase 5 (Integration): Update integration tests
  Phase 6 (Validation): Update system tests

Affected Modules:
  - door_control.c (REQ-012)
  - emergency_stop.c (REQ-043 - NEW MODULE)
  - safety_monitor.c (REQ-043)

Regression Testing Required:
  - All unit tests for affected modules
  - All integration tests
  - All system tests for safety functions

Recommend:
  1. Create Change Request (CR-XXX)
  2. CCB approval
  3. Formal impact analysis
  4. Update all affected artifacts
  5. Full regression test suite

Approve requirement modification? [Y/n]
```

User enters: `Y`

**COD**:
```
✓ Requirements modification APPROVED

Logged in: LIFECYCLE_STATE.md
  - Activity: Modify
  - Scope: Add REQ-043, modify REQ-012
  - Approved: User
  - CR#: (pending CCB assignment)

ITERATION INITIATED:
  From: Phase 4 (Implementation)
  To: Phase 2 (Requirements) - temporary return
  
Proceeding with Requirements Engineer (REQ)...
```

---

#### Step 2: Requirement Update

**REQ agent** updates:
- SRS (add REQ-043, modify REQ-012)
- RTM (update traceability)

**COD logs** iteration in LIFECYCLE_STATE.md:
```markdown
## Change Log

| Date | Phase | Change Type | Description | Impact | CR# | Status |
|------|-------|-------------|-------------|--------|-----|--------|
| 2026-02-20 | Implementation | Requirement Change | Add REQ-043, modify REQ-012 | High | CR-005 | In Progress |
```

---

#### Step 3: Cascade Changes Through Lifecycle

```bash
# COD coordinates cascade

# Phase 3: Update design
/des   # Update design for new requirement

# Phase 4: Update implementation
/imp   # Implement changes

# Update tests
/tst   # Update unit tests, integration tests, system tests

# Verification
/ver   # Verify changes
/qua   # Review changes
```

**COD tracks** all affected artifacts, ensures traceability maintained.

---

#### Step 4: Regression Testing

```bash
# COD enforces regression testing before gate check

/tst   # Execute regression test suite
```

**COD verifies**:
- All affected unit tests re-executed
- All integration tests re-executed
- All system tests re-executed
- No regressions introduced

---

#### Step 5: Return to Implementation Gate

```bash
/cod gate-check implementation
```

**COD verifies**:
- New requirement (REQ-043) fully implemented and tested
- Modified requirement (REQ-012) updated and tested
- Traceability complete (RTM updated)
- Regression tests passed
- No new defects introduced

If passed → continue to Integration phase

---

## Workflow 3: Out-of-Sequence Activity (SIL 3 vs SIL 1)

### Scenario A: SIL 3 Project (Strict Mode)

Current phase: Requirements (Phase 2)

User attempts:
```bash
/imp   # Try to implement code before design
```

**COD BLOCKS**:
```
❌ LIFECYCLE VIOLATION: Out-of-Sequence Activity

You attempted to invoke Implementation (IMP) agent.

Current Phase: Requirements (Phase 2)
IMP Agent Allowed In: Implementation & Testing (Phase 4)

Implementation cannot begin until:
  1. Requirements phase complete
  2. Requirements gate passed (/cod gate-check requirements)
  3. Architecture & Design phase complete
  4. Design gate passed (/cod gate-check design)

SIL 3 project: Strict enforcement mode
Lifecycle violations are BLOCKED.

Activity DENIED.
```

User must complete Requirements and Design before Implementation.

---

### Scenario B: SIL 1 Project (Advisory Mode)

Current phase: Requirements (Phase 2)

User attempts:
```bash
/imp   # Try to implement code before design
```

**COD WARNS**:
```
⚠ WARNING: Out-of-Sequence Activity

You attempted to invoke Implementation (IMP) agent.

Current Phase: Requirements (Phase 2)
IMP Agent Allowed In: Implementation & Testing (Phase 4)

Recommendation: Complete Requirements → Design phases first.

SIL 1 project: Advisory mode
You may proceed if you have a specific reason (e.g., prototyping, proof-of-concept).

Note: Proceeding without design may require rework later.

Proceed with Implementation anyway? [y/N]
```

User enters: `y`

**COD**:
```
⚠ Out-of-sequence activity ALLOWED (SIL 1 advisory mode)

Logged exception in: LIFECYCLE_STATE.md
Rationale: User override in advisory mode

Proceeding with Implementer (IMP)...

Note: Remember to complete Requirements and Design phases for final system.
```

---

## Workflow 4: Phase Gate Failure and Recovery

### Scenario
Design phase gate check fails due to high complexity

```bash
/cod gate-check design
```

**COD Response**:
```
✗ Phase Gate Check: Design Phase

[✗] Design Quality (2/3 satisfied) - INCOMPLETE
  ✗ Cyclomatic complexity EXCEEDS limit:
    - process_command() = 15 (limit: 10 for SIL 3)
    - handle_emergency() = 12 (limit: 10 for SIL 3)
  ✓ Fixed-width types specified
  ✓ Bounded execution time verified

[✓] Architecture Quality (6/6 satisfied)
  ✓ Modular design verified
  ✓ Static memory allocation only
  ✓ No dynamic allocation
  ✓ No recursion
  ✓ Interfaces fully defined
  ✓ Module dependencies documented

═══════════════════════════════════════════════════════
GATE RESULT: ✗ BLOCKED
═══════════════════════════════════════════════════════

Design phase INCOMPLETE. SIL 3 requires all criteria satisfied.

DENIED: Transition to Implementation & Testing phase

Required Actions:
  1. Refactor process_command() to reduce complexity ≤ 10
     Suggestions:
     - Extract sub-functions for command parsing
     - Simplify conditional logic
     - Use lookup tables instead of switch statements
  
  2. Refactor handle_emergency() to reduce complexity ≤ 10
     Suggestions:
     - Extract emergency type handling to separate functions
     - Simplify error handling paths

Recommended approach:
  /des   # Refactor design to reduce complexity
  /ver   # Verify refactored design
  /qua   # Review refactored design

Once refactored, re-run: /cod gate-check design

Current Phase: Architecture & Design (BLOCKED)
```

---

### Recovery Steps

```bash
# Step 1: Refactor design
/des
# Designer refactors functions, reduces complexity

# Step 2: Verify refactored design
/ver
# Verifier checks complexity metrics

# Step 3: Review
/qua
# QA reviews changes

# Step 4: Re-check gate
/cod gate-check design
```

**COD Response** (if fixed):
```
✓ Phase Gate Check: Design Phase

[✓] Design Quality (3/3 satisfied)
  ✓ Cyclomatic complexity within limits:
    - process_command() = 8 (limit: 10) ✓
    - handle_emergency() = 9 (limit: 10) ✓
    - All other functions ≤ 10 ✓
  ✓ Fixed-width types specified
  ✓ Bounded execution time verified

[✓] Architecture Quality (6/6 satisfied)
  ... (all satisfied)

═══════════════════════════════════════════════════════
GATE RESULT: ✓ PASSED
═══════════════════════════════════════════════════════

Design phase complete. All SIL 3 criteria satisfied.

AUTHORIZED: Transition to Implementation & Testing phase

Current Phase: Implementation & Testing
```

---

## Workflow 5: COD Status Monitoring

### Check Current Status

```bash
/cod status
```

**COD Response**:
```
═══════════════════════════════════════════════════════
Lifecycle Status: train_door_control
═══════════════════════════════════════════════════════

Project Information:
  Name: Train Door Control System
  SIL Level: 3 (Strict gate enforcement)
  Lifecycle Model: V-Model
  Current Phase: Implementation & Testing (In Progress)
  Phase Started: 2026-02-18
  Days in Phase: 2

Phase Progress:
  ✓ 1. Planning (Complete) - Gate passed: 2026-02-10
  ✓ 2. Requirements (Complete) - Gate passed: 2026-02-15
  ✓ 3. Architecture & Design (Complete) - Gate passed: 2026-02-17
  ◆ 4. Implementation & Testing (In Progress) - Started: 2026-02-18
  ☐ 5. Integration (Not Started)
  ☐ 6. Validation (Not Started)
  ☐ 7. Assessment (Not Started) - Required for SIL 3
  ☐ 8. Deployment (Not Started)

Current Phase: Implementation & Testing
  Status: In Progress
  Completion: 60% (estimated)
  
  Deliverables:
    ✓ Software Source Code - 15 files (in progress)
    ⚠ Source Code Verification Report - pending VER
    ⚠ Component Test Report - 80% tests passing
    ⚠ Component Design Verification Report - pending

  Coverage:
    Statement: 92% (target: 100%)
    Branch: 88% (target: 100%)
    Condition: 85% (target: 100%)

  Agents Active:
    - IMP (Implementer) - last activity: 15 min ago
    - TST (Tester) - last activity: 30 min ago
    - VER (Verifier) - NEEDED (verification pending)

Next Steps:
  1. Complete remaining unit tests (TST)
  2. Achieve 100% coverage (TST)
  3. Perform static analysis (VER)
  4. Code review (QUA)
  5. When complete: /cod gate-check implementation
```

---

## Workflow 6: Multi-Agent Coordination

### Scenario
Design phase with multiple agents working in parallel

```bash
# Primary agent
/des   # Designer creates architecture and design

# COD monitors, allows parallel agents
```

User invokes supporting agents in parallel:

```bash
/int   # Integrator creates integration test specs (allowed)
/saf   # Safety Engineer reviews design for safety (allowed)
```

**COD coordinates**:
- Tracks deliverables from each agent
- Ensures no conflicts (e.g., INT waits for DES to define interfaces)
- Updates LIFECYCLE_STATE.md with agent activity
- Notifies when all deliverables ready for gate check

When all agents complete:

```bash
/cod gate-check design
```

**COD verifies** deliverables from ALL agents (DES, INT, SAF, VER, QUA).

---

## Summary

These workflows demonstrate:

1. **Complete lifecycle** - SIL 3 project from initialization to deployment
2. **Requirement changes** - Iteration handling with impact analysis
3. **SIL-dependent enforcement** - Strict (SIL 3) vs Advisory (SIL 1)
4. **Gate failure recovery** - Identifying issues, fixing, re-checking
5. **Status monitoring** - Tracking progress throughout lifecycle
6. **Multi-agent coordination** - Parallel activities, deliverable tracking

**Key Principles**:
- **COD orchestrates** - not obstructs
- **User approval** for requirements (high impact)
- **SIL-dependent strictness** - safety where needed, flexibility where appropriate
- **Clear feedback** - actionable guidance for gate failures
- **Traceability enforced** - end-to-end coverage verification
- **Iteration supported** - feedback loops managed with change control

---

**Related Documents**:
- `.opencode/commands/cod.md` - COD agent definition
- `.opencode/skills/en50128-lifecycle-coordination/SKILL.md` - Phase management patterns
- `LIFECYCLE.md` - Complete lifecycle reference
