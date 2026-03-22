---
name: en50128-lifecycle-coordination
description: Project management and coordination for EN 50128 railway software development
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  role: lifecycle-coordinator
---

# EN 50128 Lifecycle Coordination Skill

## Skill Overview

**Purpose**: Lifecycle orchestration patterns for EN 50128 V-Model compliance

**Primary User**: Lifecycle Coordinator (COD) agent

**When to Use**:
- Phase planning and initialization
- Phase gate reviews
- Phase transitions
- Traceability management
- Document coordination
- Iteration handling

**Key Capabilities**:
1. V-Model phase management
2. SIL-dependent gate criteria
3. Deliverable tracking per Annex C
4. Traceability enforcement
5. Agent coordination across phases

---

## V-Model Phase Management

### V-Model Structure

The EN 50128 V-Model is highly recommended per §5.3, Figures 3–4; alternative lifecycle models are permissible per §5.3.2.14 with appropriate justification:

```
System Requirements ────────────────────► System Validation
       │                                        ▲
       │                                        │
       ▼                                        │
Software Requirements ──────────────► Software Validation
(SRS - Section 7.2)                    (Section 7.7)
       │                                        ▲
       │                                        │
       ▼                                        │
Software Architecture ──────────────► Integration Testing
(SAS - Section 7.3)                    (Section 7.6)
       │                                        ▲
       │                                        │
       ▼                                        │
Software Design ────────────────────► Module Testing
(SDS - Section 7.3)                    (Section 7.4)
       │                                        ▲
       │                                        │
       ▼                                        │
Implementation ─────────────────────► Unit Testing
(Code - Section 7.4)                   (Section 7.4)

◄───── Verification (6.2) Throughout ──────►
◄───── Quality Assurance (6.5) Throughout ──►
◄───── Configuration Management (6.6) Throughout ──►
◄───── Safety Management Throughout ───────►
```

### Phase Dependencies

| Phase | Depends On | Enables | Parallel Activities |
|-------|-----------|---------|---------------------|
| 0. Initialization | Project creation | Planning | - |
| 1. Planning | Initialization | Requirements | CM, QUA setup |
| 2. Requirements | Planning | Design | SAF (hazards), VER, QUA |
| 3. Design | Requirements | Component Design | VER, QUA, SAF (design review) |
| 4. Component Design | Design | Implementation | VER, QUA |
| 5. Implementation | Component Design | Integration | VER (static), QUA (code review), TST (unit) |
| 6. Integration | Implementation | Validation | VER, QUA, TST (integration) |
| 7. Validation | Integration | Assessment/Deployment | VER, QUA, TST (system) |
| 8. Assessment | Validation (SIL 1-4) | Deployment | ASR (independent) |
| 9. Deployment | Validation or Assessment | Maintenance | CM, VER |

### Parallel Activities (All Phases)

These activities run THROUGHOUT the lifecycle:

1. **Configuration Management (CM)** - Section 6.6
   - Version control
   - Change management
   - Baseline establishment
   - Traceability maintenance

2. **Quality Assurance (QUA)** - Section 6.5
   - Reviews
   - Audits
   - Quality gates
   - Metrics collection

3. **Verification (VER)** - Section 6.2
   - Document verification
   - Code verification
   - Test verification
   - Evidence collection

4. **Safety Management (SAF)** - Throughout
   - Hazard analysis
   - Safety requirements
   - Safety case development
   - Risk management

---

## Phase Gate Criteria

### Gate Structure

Each phase gate has:
1. **Entry Criteria** - Prerequisites to start phase
2. **Exit Criteria** - Requirements to complete phase
3. **Deliverables** - Required documents per Annex C
4. **Quality Criteria** - Metrics, coverage, compliance
5. **Traceability** - RTM completeness
6. **Verification** - Reviews, approvals

### SIL-Dependent Criteria

| Criterion Type | SIL 0-1 | SIL 2 | SIL 3-4 |
|----------------|---------|-------|---------|
| Documentation | Basic | Standard | Complete + Independent Review |
| Traceability | Recommended | Highly Recommended | **MANDATORY** |
| Coverage | Statement (HR) | Statement (HR), Branch (M) | Statement (M), Branch (M), Condition (M) |
| Static Analysis | Optional | Highly Recommended | **MANDATORY** |
| Verification | Internal | Internal | **Independent** |
| Validation | Internal | Internal | **Independent** |
| Assessment | Optional | Optional | **MANDATORY** |

> **Full per-phase checklists** (Phase 1–9) are in the `en50128-lifecycle-phase-checklists` skill.
> Load it before any gate-check or start-phase operation.

---

## Traceability Management

### Traceability Matrix (RTM) Structure

The Requirements Traceability Matrix SHALL maintain bidirectional traceability:

```
System Req → Software Req → Architecture → Design → Code → Unit Test → Integration Test → System Test → Validation Result
     ↑            ↑             ↑            ↑         ↑        ↑              ↑                ↑              ↑
     └────────────┴─────────────┴────────────┴─────────┴────────┴──────────────┴────────────────┴──────────────┘
                                    Bidirectional Traceability
```

### RTM Format Example

| System Req | Software Req | Design Module | Source File | Unit Test | Integration Test | System Test | Validation | Status |
|------------|--------------|---------------|-------------|-----------|------------------|-------------|------------|--------|
| SYS-001 | SWR-001, SWR-002 | door_control | door.c | test_door.c | int_test_01 | sys_test_05 | VAL-001 | ✓ |
| SYS-002 | SWR-003 | safety_monitor | safety.c | test_safety.c | int_test_02 | sys_test_06 | VAL-002 | ✓ |

### Traceability Verification (Per Phase)

**Phase 2 (Requirements)**:
- [ ] Forward: All system requirements → software requirements
- [ ] Backward: All software requirements → system requirements
- [ ] No orphan software requirements

**Phase 3 (Design)**:
- [ ] Forward: All software requirements → architecture components
- [ ] Forward: All architecture components → design modules
- [ ] Backward: All design modules → architecture → requirements
- [ ] No orphan design modules

**Phase 5 (Implementation)**:
- [ ] Forward: All design modules → source files
- [ ] Forward: All source files → unit tests
- [ ] Backward: All source files → design
- [ ] Backward: All unit tests → requirements
- [ ] No untested source files

**Phase 6 (Integration)**:
- [ ] Forward: All components → integration tests
- [ ] Backward: All integration tests → requirements
- [ ] Interface coverage complete

**Phase 7 (Validation)**:
- [ ] Forward: All requirements → system tests
- [ ] Backward: All system tests → requirements
- [ ] Forward: All system tests → validation results
- [ ] 100% requirements coverage
- [ ] All validation results PASS

### Traceability Gap Detection

COD SHALL detect and report:
1. **Orphan requirements**: Software requirements with no parent system requirement
2. **Uncovered requirements**: Requirements with no design/code/test
3. **Orphan code**: Source files not mapped to design
4. **Untested code**: Code not covered by unit/integration/system tests
5. **Unused tests**: Tests not mapped to requirements

---

## Document Coordination

### Annex C Document Control Summary

See [`DELIVERABLES.md`](../../../DELIVERABLES.md) for the complete Annex C Table C.1 document control summary (all phases, document names, author roles, and check columns).

### Document Approval Workflow

**Per-Phase Execution Loop (SIL 3-4)** — see WORKFLOW.md Diagram 1 for the authoritative flow:

```
PM: orchestrates dev agents → deliverable produced
  │
  ▼
QUA template check (1-pass rule)
  ├── FAIL ──► loops back to author (PM coordinates rework)
  └── PASS
        │
        ▼
      VER verification
        ├── REJECT ──► loops back to PM (rework required)
        └── APPROVE
              │
              ▼
            VER report → QUA template check (1-pass rule)
              ├── FAIL ──► loops back to VER (re-issue report)
              └── PASS
                    │
                    ▼
                  VMGR reviews VER report
                    ├── REJECT ──► loops to VER rework
                    └── APPROVE
                          │
                          ▼
                        COD invokes VAL (independent from VMGR and PM)
                          │
                          ▼
                        VAL Validation Report → QUA template check (1-pass rule)
                          ├── FAIL ──► loops back to VAL (re-issue report)
                          └── PASS
                                │
                                ▼
                              VMGR reviews VAL report
                                ├── REJECT ──► loops to VAL rework
                                └── APPROVE ── VMGR V&V Decision (cannot be overridden)
                                      │
                                      ▼
                                    COD gate-check:
                                      ✓ VER report VMGR-approved
                                      ✓ VAL report VMGR-approved
                                      ✓ All deliverables QUA-passed
                                      ✓ Traceability complete
                                      ✓ Zero critical defects
                                      → PASS: COD authorizes next phase
```

**SIL 0-2 simplified loop** (VER-only phases): deliverable → QUA → VER → PASS → COD gate-check (VAL required only for Phase 5/7)

### Document Baseline Strategy

| Baseline | Phase | Contents | When Established |
|----------|-------|----------|------------------|
| **Baseline 0** | Planning | SQAP, SCMP, SVP, SVaP | Planning gate passed |
| **Baseline 1** | Requirements | SRS, RTM, Test Specs | Requirements gate passed |
| **Baseline 2** | Design | SAS, SDS, Interfaces | Design gate passed |
| **Baseline 3** | Component Design | Component Design Specs, Component Test Specs | Component Design gate passed |
| **Baseline 4** | Implementation | Source Code, Unit Tests | Implementation gate passed |
| **Baseline 5** | Integration | Integration Tests, Reports | Integration gate passed |
| **Baseline 6** | Validation | Validation Report | Validation gate passed |
| **Baseline 7** | Assessment | Assessment Report | Assessment gate passed (SIL 1-4) |
| **Baseline 8** | Deployment | Release Package | Deployment complete |

---

## Iteration Handling

> For the full CCB/CR process, regression test selection, and iteration execution workflow,
> load the `en50128-lifecycle-tool-integration` skill or read
> `workflows/iteration-change-management-workflow.md` directly.

### Feedback Loops in V-Model

EN 50128 Section 5.3.2.2: "The lifecycle model shall take into account the possibility of iterations in and between phases."

**Common Iteration Patterns**:

1. **Requirements Feedback** (from Design):
   - Design reveals ambiguous/infeasible requirements → return to Requirements phase

2. **Design Feedback** (from Implementation):
   - Implementation reveals design issues → return to Design phase

3. **Validation Feedback** (from Validation):
   - System testing reveals requirement not met → trace back to root cause and fix

### Iteration Control

When iteration detected:

1. **COD detects iteration request** (from agent or user)
2. **Assess impact**: Which phase to return to? What artifacts affected?
3. **User approval required** (for requirements changes)
4. **Change control activated**: CR created, CCB approval (SIL-dependent)
5. **Execute iteration**: Return to phase, update artifacts, maintain traceability
6. **Update lifecycle state**: Log iteration in `LIFECYCLE_STATE.md`

### Regression Testing Requirements

After iteration:
- [ ] All affected unit tests re-executed
- [ ] All affected integration tests re-executed
- [ ] All affected system tests re-executed
- [ ] Regression test results documented
- [ ] Traceability updated

---

## Agent Coordination Patterns

### Phase-to-Agent Mapping

| Phase | Primary Agents | Supporting Agents | Cross-Cutting |
|-------|---------------|-------------------|---------------|
| **0. Init** | COD | - | - |
| **1. Planning** | PM | QUA, CM, VER, VAL, SAF | CM, QUA |
| **2. Requirements** | REQ | SAF, TST | VER, VAL, QUA, CM |
| **3. Design** | DES | INT, SAF | VER, VAL, QUA, CM |
| **4. Component Design** | DES | TST | VER, QUA, CM |
| **5. Implementation** | IMP | TST, SAF | VER, QUA, CM |
| **6. Integration** | INT | TST | VER, VAL, QUA, CM |
| **7. Validation** | VAL | TST | VER, QUA, CM |
| **8. Assessment** | ASR (external) | VER | CM |
| **9. Deployment** | PM | CM | VER, VAL, CM |

### Agent Handoff Protocol

When phase transition authorized:

1. **COD announces phase transition**:
   ```
   Phase transition authorized: Design → Implementation

   Handoff from:
     - DES (Designer) - design artifacts complete
     - INT (Integrator) - integration test specs ready

   Handoff to:
     - IMP (Implementer) - begin C code implementation
     - TST (Tester) - begin unit test development

   Cross-cutting agents continue:
     - VER (Verifier) - verify source code
     - QUA (Quality) - conduct code reviews
     - CM (Config Mgmt) - baseline code
   ```

2. **Receiving agents acknowledge**
3. **COD monitors progress** in new phase
4. **COD verifies previous phase artifacts available**

---

## COD State Management

### LIFECYCLE_STATE.md Structure

Each project SHALL have `LIFECYCLE_STATE.md` in project root:

```markdown
# Project Lifecycle State

## Project Information
- **Project Name**: Train Door Control System
- **SIL Level**: 3
- **Lifecycle Model**: V-Model
- **COD Mode**: Strict Gatekeeper
- **Created**: 2026-02-10
- **Last Updated**: 2026-02-18

## Current Status
- **Current Phase**: Design (Phase 3)
- **Phase Started**: 2026-02-15
- **Days in Phase**: 3
- **Completion**: 75% (estimated)

## Phase History

| Phase | Status | Started | Completed | Gate Passed | Notes |
|-------|--------|---------|-----------|-------------|-------|
| 0. Initialization | Complete | 2026-02-10 | 2026-02-10 | N/A | COD initialized |
| 1. Planning | Complete | 2026-02-10 | 2026-02-10 | 2026-02-10 | All plans approved |
| 2. Requirements | Complete | 2026-02-10 | 2026-02-15 | 2026-02-15 | 42 requirements |
| 3. Design | In Progress | 2026-02-15 | - | - | 8/8 deliverables |
| 4. Component Design | Not Started | - | - | - | - |
| 5. Implementation | Not Started | - | - | - | - |
| 6. Integration | Not Started | - | - | - | - |
| 7. Validation | Not Started | - | - | - | - |
| 8. Assessment | Not Started | - | - | - | Required for SIL 3 |
| 9. Deployment | Not Started | - | - | - | - |

## Deliverable Status

### Phase 3 (Design) - In Progress
- [x] Software Architecture Specification (SAS) - Approved 2026-02-16
- [x] Software Design Specification (SDS) - Approved 2026-02-17
- [ ] Software Interface Specifications - In Progress
- [ ] Software Integration Test Specification - Draft
- [x] Software Component Design Specification - Approved 2026-02-17
- [x] Software Component Test Specification - Approved 2026-02-18
- [ ] Architecture and Design Verification Report - Pending
- [x] Component Design Verification Report - Approved 2026-02-18

## Requirement Approval History

| Date | Activity | Scope | Approved By | Files Modified |
|------|----------|-------|-------------|----------------|
| 2026-02-11 | Establish | Initial SRS (42 requirements) | User | docs/SRS.md, docs/RTM.md |

## Change Log

| Date | Phase | Change Type | Description | Impact | CR# |
|------|-------|-------------|-------------|--------|-----|
| 2026-02-16 | Design | Clarification | Updated interface timing specs | Low | CR-001 |

## Gate Check History

| Date | Phase | Result | Criteria | Notes |
|------|-------|--------|----------|-------|
| 2026-02-10 | Planning | PASSED | 5/5 | All planning docs approved |
| 2026-02-15 | Requirements | PASSED | 6/6 | 42 requirements, 100% traceable |

## Traceability Status

- System Req → Software Req: 100% (38/38)
- Software Req → Design: 100% (42/42)
- Design → Code: 0% (not started)
- Code → Unit Tests: 0% (not started)
- Requirements → System Tests: 100% (42/42 specified)

## Metrics

- Requirements: 42 total (38 functional, 4 safety)
- Design Modules: 12
- Cyclomatic Complexity: Max 8 (target ≤10 for SIL 3)
- Lines of Code: 0 (not started)
- Test Coverage: 0% (not started)

## Agents Active

- DES (Designer) - Last activity: 2 hours ago
- INT (Integrator) - Last activity: 4 hours ago
- VER (Verifier) - REQUIRED (design verification pending)

## Next Steps

1. Complete Software Interface Specifications (DES)
2. Finalize Integration Test Specification (INT)
3. Perform design verification (VER)
4. Generate Architecture and Design Verification Report (VER)
5. Run @cod gate-check design
```

---

## Comprehensive Workflows

This skill includes **4 comprehensive workflows** (~300 pages, ~12,000 lines) in the `workflows/` directory.
Load these only when deep procedural detail is needed for a specific workflow type.

### 1. Phase Gate Management Workflow

**File**: `workflows/phase-gate-management-workflow.md` (2,319 lines)

**Load when**: Deep gate validation logic, Python gate checker script, or complete SIL-annotated gate sequences are needed.

**Content**: 8 complete phase gates (Planning through Deployment); SIL-dependent enforcement (Advisory/Semi-strict/Strict); Python gate checker (~400 lines); mandatory deliverables per Annex C; quality thresholds; approval workflows.

### 2. V-Model Orchestration Workflow

**File**: `workflows/v-model-orchestration-workflow.md` (1,507 lines)

**Load when**: Phase initialization/transition procedures, agent orchestration patterns, LIFECYCLE_STATE.md Python management scripts, or complete SIL 3 lifecycle example are needed.

**Content**: 9 phase definitions; agent orchestration for 12 agents; parallel activities; state management; baseline management; Python automation scripts (~500 lines).

### 3. Traceability and RTM Management Workflow

**File**: `workflows/traceability-rtm-workflow.md` (1,481 lines)

**Load when**: Full RTM creation/update procedures, 60+ `workspace.py trace` command examples, Python RTM gap detector script, or RTM audit procedures are needed.

**Content**: Bidirectional traceability; gap detection (6 types); SIL-specific coverage requirements; complete workspace.py commands; Python RTM gap detector (~250 lines); RTM audit checklist.

### 4. Iteration and Change Management Workflow

**File**: `workflows/iteration-change-management-workflow.md` (1,543 lines)

**Load when**: Full CR process, CCB composition rules, regression test selection, or complete iteration execution procedures are needed.

**Content**: 5 iteration types; CR document template; CCB composition (SIL-dependent); regression test selection (SIL 3-4: full suite); Python CR impact analyzer (~250 lines) and regression test selector (~200 lines).

---

## Workflow Selection by SIL

| Task | Workflow | SIL 0-1 | SIL 2 | SIL 3-4 | Key Features |
|------|----------|---------|-------|---------|--------------|
| **Phase Gate Check** | Phase Gate Management | Advisory | Semi-strict | Strict | BLOCK on violations (SIL 3-4) |
| **Phase Transition** | V-Model Orchestration | Informal | Structured | Formal | Baseline control (SIL 2+) |
| **Traceability** | RTM Management | Optional | HR | **MANDATORY** | 100% coverage required (SIL 3-4) |
| **Iteration** | Change Management | Informal | CR required | Formal CR + CCB | Full regression (SIL 3-4) |

---

## Tool Integration

> Full `workspace.py trace` and `workspace.py wf` command reference, Python automation scripts,
> EN 50128 coverage table, and statistics are in the `en50128-lifecycle-tool-integration` skill.
> Load it when running any workspace.py command or reviewing coverage statistics.

---

## Summary

This skill provides COD with:

1. **V-Model phase management** — Structure, dependencies, parallel activities
2. **Phase gate criteria** — SIL-dependent criteria summary; full checklists in `en50128-lifecycle-phase-checklists`
3. **Traceability management** — RTM structure, verification, gap detection
4. **Document coordination** — Annex C mapping, approval workflows, baselines
5. **Iteration handling** — Feedback loops, change control overview
6. **Agent coordination** — Phase-to-agent mapping, handoff protocols
7. **State management** — LIFECYCLE_STATE.md structure and content
8. **Comprehensive workflows** — 4 workflows (~300 pages) available on demand
9. **Tool integration** — Full command reference in `en50128-lifecycle-tool-integration`

**Key Principle**: COD orchestrates the lifecycle to ensure EN 50128 V-Model compliance while enabling efficient development. Be strict where safety demands (SIL 3-4), but be helpful and guiding at all times.
