# EN 50128 V-Model Lifecycle Orchestration Workflow

**Skill**: `en50128-lifecycle-coordination`  
**Workflow**: V-Model Orchestration  
**Role**: Lifecycle Coordinator (COD)  
**EN 50128 Reference**: Section 5.3 (Software Lifecycle), Section 5.3.2 (Lifecycle Model)  
**Purpose**: Phase transitions, agent coordination, lifecycle state management

---

## Table of Contents

1. [V-Model Structure](#v-model-structure)
2. [Phase Initialization](#phase-initialization)
3. [Phase Execution](#phase-execution)
4. [Phase Transition](#phase-transition)
5. [Agent Coordination Patterns](#agent-coordination-patterns)
6. [LIFECYCLE_STATE.md Management](#lifecycle_statemd-management)
7. [Parallel Activities Coordination](#parallel-activities-coordination)
8. [Tool Integration](#tool-integration)
9. [Automation Scripts](#automation-scripts)
10. [Example Scenario](#example-scenario)

---

## V-Model Structure

### EN 50128 V-Model Overview

The EN 50128 V-Model is **MANDATORY** for SIL 2-4 projects (Section 5.3.2.1).

```
┌──────────────────────────────────────────────────────────────────┐
│ EN 50128 V-MODEL LIFECYCLE                                       │
├──────────────────────────────────────────────────────────────────┤
│                                                                  │
│ System Requirements ────────────────────────► System Validation │
│        │                                                ▲         │
│        │                                                │         │
│        ▼                                                │         │
│ Software Requirements ──────────────► Software Validation        │
│ (SRS - Section 7.2)                  (Section 7.7)      │        │
│        │                                                │         │
│        │                                                │         │
│        ▼                                                │         │
│ Software Architecture ──────────────► Integration Testing        │
│ (SAS - Section 7.3)                  (Section 7.6)      │        │
│        │                                                │         │
│        │                                                │         │
│        ▼                                                │         │
│ Software Design ────────────────────► Module Testing             │
│ (SDS - Section 7.3)                  (Section 7.4)      │        │
│        │                                                │         │
│        │                                                │         │
│        ▼                                                │         │
│ Implementation ─────────────────────► Unit Testing               │
│ (Code - Section 7.4)                 (Section 7.4)     │         │
│                                                                   │
│ ◄────── Verification (6.2) Throughout ─────────►                 │
│ ◄────── Quality Assurance (6.5) Throughout ────►                 │
│ ◄────── Configuration Management (6.6) Throughout ───►           │
│ ◄────── Safety Management Throughout ──────────►                 │
└───────────────────────────────────────────────────────────────────┘
```

### Phase Mapping

| Phase ID | Phase Name | EN 50128 Section | Primary Activities | Primary Agents |
|----------|-----------|------------------|-------------------|----------------|
| **0** | Initialization | 5.3 | COD setup, project creation | COD |
| **1** | Planning | 7.1 | SQAP, SCMP, SVP, SVaP | PM, QUA, CM, VER, VAL |
| **2** | Requirements | 7.2 | SRS, RTM, Hazard Log | REQ, SAF, TST |
| **3** | Design | 7.3 | SAS, SDS, Interfaces | DES, INT, SAF |
| **4** | Implementation | 7.4 | Source Code, Unit Tests | IMP, TST, VER, QUA |
| **5** | Integration | 7.6 | Integration Tests | INT, TST, VER, QUA |
| **6** | Validation | 7.7 | System Tests, Validation | VAL, TST, VER, QUA |
| **7** | Assessment | 6.4 | Assessment (SIL 3-4 only) | ASR (external) |
| **8** | Deployment | 7.8 | Release, Deployment, Maintenance | PM, CM, VER, VAL |

### Phase Dependencies

```
Phase 0 (Initialization)
  │
  ├─> Phase 1 (Planning) ────────────────────────────┐
  │     │                                             │
  │     └─> Phase 2 (Requirements) ──────────────────┤
  │           │                                       │
  │           └─> Phase 3 (Design) ──────────────────┤
  │                 │                                 │
  │                 └─> Phase 4 (Implementation) ────┤
  │                       │                           │
  │                       └─> Phase 5 (Integration) ─┤
  │                             │                     │
  │                             └─> Phase 6 (Validation)
  │                                   │
  │                                   ├─> Phase 7 (Assessment) [SIL 3-4]
  │                                   │     │
  │                                   │     └─> Phase 8 (Deployment)
  │                                   │
  │                                   └─> Phase 8 (Deployment) [SIL 0-2]
  │
  ├─ CM (Configuration Management) - ALL PHASES
  ├─ QUA (Quality Assurance) - ALL PHASES
  ├─ VER (Verification) - Phases 2-8
  └─ SAF (Safety) - Phases 2-6
```

**Critical**: Phases MUST execute in sequence (no skipping) for SIL 2-4. SIL 0-1 may use advisory mode.

---

## Phase Initialization

### Purpose

Initialize a new phase after successful gate check of previous phase.

### Phase Initialization Workflow

```
┌────────────────────────────────────────────────────┐
│ PHASE INITIALIZATION WORKFLOW                      │
├────────────────────────────────────────────────────┤
│ 1. Previous phase gate PASSED                      │
│ 2. COD updates LIFECYCLE_STATE.md                  │
│ 3. COD establishes baseline (if applicable)        │
│ 4. COD activates phase-specific agents             │
│ 5. COD creates phase deliverable tracking          │
│ 6. COD sets entry criteria verification             │
│ 7. COD notifies user of phase transition           │
│ 8. COD monitors phase activities                   │
└────────────────────────────────────────────────────┘
```

### Entry Criteria Verification

Before initializing phase, COD verifies:

1. **Previous phase complete**: Gate check PASSED
2. **Baseline established**: Previous phase artifacts baselined
3. **Artifacts available**: All input artifacts from previous phase accessible
4. **Team ready**: Required agents available for phase
5. **Tools ready**: Required tools available and qualified (if applicable)

### Phase Initialization Example

**Scenario**: Transition from Requirements (Phase 2) to Design (Phase 3) after successful gate check.

```bash
# User runs gate check
/cod gate-check requirements

# COD response:
# ✓ PASSED
# Baseline 1 established
# AUTHORIZED: Transition to Design phase
```

**COD Internal Actions** (automatic, not visible to user):

```python
# Pseudocode - COD internal phase initialization
def initialize_design_phase(project):
    # 1. Update LIFECYCLE_STATE.md
    lifecycle_state = load_lifecycle_state(project)
    lifecycle_state['current_phase'] = 'design'
    lifecycle_state['phase_started'] = datetime.now()
    lifecycle_state['phase_history'].append({
        'phase': 'design',
        'status': 'in_progress',
        'started': datetime.now(),
        'gate_passed': None
    })
    save_lifecycle_state(lifecycle_state)
    
    # 2. Verify baseline 1 established
    assert git_tag_exists('baseline-1'), "Baseline 1 not found"
    
    # 3. Create phase deliverable tracking
    deliverables = [
        'Software Architecture Specification (SAS)',
        'Software Design Specification (SDS)',
        'Software Interface Specifications',
        'Software Integration Test Specification',
        'Architecture and Design Verification Report',
        'Component Design Specification',
        'Component Test Specification'
    ]
    for deliverable in deliverables:
        add_deliverable_to_tracking(project, 'design', deliverable, status='pending')
    
    # 4. Activate phase-specific agents
    active_agents = ['DES', 'INT', 'SAF', 'VER', 'QUA', 'CM']
    lifecycle_state['active_agents'] = active_agents
    
    # 5. Set entry criteria
    entry_criteria = {
        'requirements_gate_passed': True,
        'srs_approved': True,
        'rtm_baselined': True,
        'baseline_1_established': True
    }
    lifecycle_state['current_phase_entry_criteria'] = entry_criteria
    
    # 6. Notify user
    print("""
    ═══════════════════════════════════════════════════════
    PHASE TRANSITION: Design (Phase 3)
    ═══════════════════════════════════════════════════════
    
    Current Phase: Architecture & Design
    Entry Criteria: ✓ All satisfied
    Active Agents: DES (Designer), INT (Integrator), SAF (Safety), VER (Verifier), QUA (Quality), CM (Config Mgmt)
    
    Deliverables:
      - Software Architecture Specification (SAS)
      - Software Design Specification (SDS)
      - Software Interface Specifications
      - Software Integration Test Specification
      - Architecture and Design Verification Report
      - Component Design Specification
      - Component Test Specification
    
    Next Steps:
      1. /des - Begin architecture and design
      2. /int - Create integration test specifications
      3. When complete: /cod gate-check design
    """)
    
    # 7. Begin monitoring phase activities
    start_phase_monitoring(project, 'design')
```

### Tool Integration

```bash
# Verify phase initialization
workspace.py wf status --phase design

# Check deliverables tracking
workspace.py wf list-deliverables --phase design

# Verify baseline established
git tag -l baseline-1

# Check LIFECYCLE_STATE.md
cat LIFECYCLE_STATE.md
```

---

## Phase Execution

### Purpose

Monitor and coordinate agent activities during phase execution.

### Phase Execution Workflow

```
┌────────────────────────────────────────────────────┐
│ PHASE EXECUTION WORKFLOW                           │
├────────────────────────────────────────────────────┤
│ 1. Primary agents invoked by user                  │
│ 2. COD monitors agent activities                   │
│ 3. COD tracks deliverable creation                 │
│ 4. COD verifies cross-cutting activities (CM, QUA) │
│ 5. COD detects lifecycle violations                │
│ 6. COD provides progress updates                   │
│ 7. COD signals when phase ready for gate check     │
└────────────────────────────────────────────────────┘
```

### Agent Activity Monitoring

COD tracks:

1. **Agent invocations**: Which agents invoked, when, by whom
2. **Deliverable creation**: Which deliverables created/updated
3. **Cross-cutting activities**: CM, QUA, VER, SAF activities throughout
4. **Progress estimation**: % complete based on deliverables
5. **Lifecycle violations**: Out-of-sequence activities, missing approvals

### Progress Tracking

COD estimates phase completion based on deliverables:

```python
def calculate_phase_progress(phase, deliverables):
    """Calculate phase completion percentage"""
    
    total_deliverables = len(deliverables)
    completed_deliverables = sum(1 for d in deliverables if d['status'] == 'complete')
    
    progress = (completed_deliverables / total_deliverables) * 100.0
    
    # Adjust for quality activities
    if phase in ['implementation', 'integration', 'validation']:
        # Require QUA review before 100% complete
        qua_review = any(d['name'] == 'QA Review Report' and d['status'] == 'complete' 
                         for d in deliverables)
        if not qua_review and progress >= 90:
            progress = 90  # Cap at 90% until QUA review
    
    return progress
```

### Lifecycle Violation Detection

COD enforces phase sequence (SIL-dependent):

**SIL 0-1 (Advisory Mode)**:
- Warn user of out-of-sequence activities
- Allow user to proceed with warning

**SIL 2 (Semi-Strict Mode)**:
- Block mandatory violations (e.g., implementation before design)
- Warn on highly recommended violations
- Require justification for overrides

**SIL 3-4 (Strict Mode)**:
- BLOCK all out-of-sequence activities
- No user override allowed
- Must complete phases in order

**Example Violation Detection**:

```python
def check_lifecycle_violation(current_phase, requested_agent, sil_level):
    """Check if agent invocation violates lifecycle"""
    
    # Define allowed agents per phase
    allowed_agents = {
        'planning': ['PM', 'QUA', 'CM', 'VER', 'VAL', 'SAF'],
        'requirements': ['REQ', 'SAF', 'TST', 'VER', 'QUA', 'CM'],
        'design': ['DES', 'INT', 'SAF', 'VER', 'QUA', 'CM'],
        'implementation': ['IMP', 'TST', 'VER', 'QUA', 'SAF', 'CM'],
        'integration': ['INT', 'TST', 'VER', 'QUA', 'CM'],
        'validation': ['VAL', 'TST', 'VER', 'QUA', 'CM'],
        'assessment': ['ASR', 'VER', 'CM'],
        'deployment': ['PM', 'CM', 'VER', 'VAL']
    }
    
    # Cross-cutting agents always allowed
    cross_cutting = ['CM', 'QUA', 'VER']
    if requested_agent in cross_cutting:
        return {'violation': False}
    
    # Check if agent allowed in current phase
    if requested_agent not in allowed_agents[current_phase]:
        # Determine enforcement level
        if sil_level <= 1:
            return {
                'violation': True,
                'severity': 'warning',
                'allow_override': True,
                'message': f"⚠ WARNING: {requested_agent} not typically used in {current_phase} phase"
            }
        elif sil_level == 2:
            return {
                'violation': True,
                'severity': 'error',
                'allow_override': True,
                'message': f"❌ ERROR: {requested_agent} not allowed in {current_phase} phase (justification required)"
            }
        else:  # SIL 3-4
            return {
                'violation': True,
                'severity': 'blocking',
                'allow_override': False,
                'message': f"🛑 BLOCKED: {requested_agent} not allowed in {current_phase} phase (SIL {sil_level} strict mode)"
            }
    
    return {'violation': False}
```

### Progress Updates

COD provides periodic progress updates:

```bash
# User checks status
/cod status

# COD response (example - Design phase in progress)
═══════════════════════════════════════════════════════
Lifecycle Status: train_door_control
═══════════════════════════════════════════════════════

Project Information:
  Name: Train Door Control System
  SIL Level: 3 (Strict gate enforcement)
  Lifecycle Model: V-Model
  Current Phase: Architecture & Design (In Progress)
  Phase Started: 2026-02-15
  Days in Phase: 2

Phase Progress:
  ✓ 1. Planning (Complete) - Gate passed: 2026-02-10
  ✓ 2. Requirements (Complete) - Gate passed: 2026-02-15
  ◆ 3. Architecture & Design (In Progress) - 70% complete
  ☐ 4. Implementation & Testing (Not Started)
  ☐ 5. Integration (Not Started)
  ☐ 6. Validation (Not Started)
  ☐ 7. Assessment (Not Started) - Required for SIL 3
  ☐ 8. Deployment (Not Started)

Current Phase: Architecture & Design
  Status: In Progress
  Completion: 70% (estimated)
  
  Deliverables:
    ✓ Software Architecture Specification (SAS) - Approved 2026-02-16
    ✓ Software Design Specification (SDS) - Approved 2026-02-17
    ⚠ Software Interface Specifications - In Progress
    ⚠ Software Integration Test Specification - Draft
    ✓ Component Design Specification - Approved 2026-02-17
    ✓ Component Test Specification - Approved 2026-02-17
    ☐ Architecture and Design Verification Report - Pending VER
    ☐ Software/Hardware Integration Test Specification - Not Started

  Agents Active:
    - DES (Designer) - last activity: 15 min ago
    - INT (Integrator) - last activity: 2 hours ago
    - VER (Verifier) - NEEDED (verification pending)

Next Steps:
  1. Complete Software Interface Specifications (DES)
  2. Finalize Integration Test Specification (INT)
  3. Perform design verification (VER)
  4. Generate Architecture and Design Verification Report (VER)
  5. When complete: /cod gate-check design
```

---

## Phase Transition

### Purpose

Authorize transition from one phase to the next after successful gate check.

### Phase Transition Workflow

```
┌────────────────────────────────────────────────────┐
│ PHASE TRANSITION WORKFLOW                          │
├────────────────────────────────────────────────────┤
│ 1. Gate check executed (/cod gate-check <phase>)   │
│ 2. COD verifies exit criteria                      │
│ 3. If PASSED:                                      │
│    a. Establish baseline (if applicable)           │
│    b. Update LIFECYCLE_STATE.md                    │
│    c. Close current phase                          │
│    d. Initialize next phase                        │
│    e. Notify user of transition                    │
│ 4. If BLOCKED:                                     │
│    a. Identify gaps                                │
│    b. Provide actionable guidance                  │
│    c. Block transition (SIL 3-4)                   │
│    d. Remain in current phase                      │
└────────────────────────────────────────────────────┘
```

### Exit Criteria Verification

COD verifies phase-specific exit criteria (see `phase-gate-management-workflow.md`).

### Baseline Establishment

After gate check PASSED, COD establishes baseline:

| Phase | Baseline | Git Tag | Contents |
|-------|----------|---------|----------|
| **Planning** | Baseline 0 | `baseline-0` | SQAP, SCMP, SVP, SVaP |
| **Requirements** | Baseline 1 | `baseline-1` | SRS, RTM, Hazard Log, Test Specs |
| **Design** | Baseline 2 | `baseline-2` | SAS, SDS, Interfaces, Integration Test Specs |
| **Implementation** | Baseline 3 | `baseline-3` | Source Code, Unit Tests |
| **Integration** | Baseline 4 | `baseline-4` | Integration Tests, Reports |
| **Validation** | Baseline 5 | `baseline-5` | Validation Report, System Tests |
| **Assessment** | Baseline 6 | `baseline-6` | Assessment Report |
| **Deployment** | Baseline 7 | `baseline-7` | Release Package |

**Baseline Establishment Script**:

```python
def establish_baseline(phase, baseline_number):
    """Establish baseline in Git"""
    
    baseline_tag = f'baseline-{baseline_number}'
    
    # 1. Ensure all changes committed
    subprocess.run(['git', 'add', '.'], check=True)
    subprocess.run(['git', 'commit', '-m', f'Baseline {baseline_number}: {phase.capitalize()} phase complete'], check=False)
    
    # 2. Create baseline tag
    subprocess.run(['git', 'tag', '-a', baseline_tag, '-m', f'EN 50128 Baseline {baseline_number}: {phase}'], check=True)
    
    # 3. Push tag to remote (optional)
    subprocess.run(['git', 'push', 'origin', baseline_tag], check=False)
    
    print(f"✓ Baseline {baseline_number} established: {baseline_tag}")
```

### Transition Authorization

**PASSED Gate**:

```
═══════════════════════════════════════════════════════
GATE RESULT: ✓ PASSED
═══════════════════════════════════════════════════════

Design phase complete. All SIL 3 criteria satisfied.

AUTHORIZED: Transition to Implementation & Testing phase

Baseline Established: Baseline 2 (git tag baseline-2)
Next Phase: Implementation & Testing (Phase 4)

Active Agents: IMP, TST, VER, QUA, SAF, CM
```

**BLOCKED Gate**:

```
═══════════════════════════════════════════════════════
GATE RESULT: ✗ BLOCKED
═══════════════════════════════════════════════════════

Design phase INCOMPLETE. SIL 3 requires all criteria satisfied.

DENIED: Transition to Implementation & Testing phase

Required Actions:
  1. Refactor process_command() to reduce complexity ≤ 10
  2. Refactor handle_emergency() to reduce complexity ≤ 10

Recommended approach:
  /des              # Refactor design
  /ver              # Verify refactored design
  /cod gate-check design

Current Phase: Architecture & Design (BLOCKED)
```

### Handoff Protocol

COD announces handoff from previous phase agents to next phase agents:

```
═══════════════════════════════════════════════════════
PHASE HANDOFF: Requirements → Design
═══════════════════════════════════════════════════════

Handoff from:
  - REQ (Requirements Engineer) - SRS complete, RTM baselined
  - SAF (Safety Engineer) - Hazard Log baselined
  - TST (Tester) - Overall Test Specification complete

Handoff to:
  - DES (Designer) - Begin architecture and design
  - INT (Integrator) - Begin integration test specifications

Cross-cutting agents continue:
  - VER (Verifier) - Verify design artifacts
  - QUA (Quality) - Review design quality
  - CM (Configuration Management) - Baseline design artifacts
  - SAF (Safety) - Review design for safety

Artifacts Available:
  - docs/SRS.md (Software Requirements Specification)
  - docs/RTM.md (Requirements Traceability Matrix)
  - docs/Hazard-Log.md (Hazard Log)
  - docs/test/Overall-Test-Spec.md (Overall Test Specification)

Next Steps:
  1. /des - Create Software Architecture Specification (SAS)
  2. /des - Create Software Design Specification (SDS)
  3. /int - Create Integration Test Specifications
  4. When complete: /cod gate-check design
```

---

## Agent Coordination Patterns

### Phase-to-Agent Mapping

COD maintains phase-to-agent mapping to coordinate activities:

| Phase | Primary Agents | Supporting Agents | Cross-Cutting Agents |
|-------|---------------|-------------------|----------------------|
| **0. Init** | COD | - | - |
| **1. Planning** | PM | QUA, CM, VER, VAL, SAF | CM, QUA |
| **2. Requirements** | REQ | SAF, TST | VER, VAL, QUA, CM |
| **3. Design** | DES | INT, SAF | VER, VAL, QUA, CM |
| **4. Implementation** | IMP | TST, SAF | VER, QUA, CM |
| **5. Integration** | INT | TST | VER, VAL, QUA, CM |
| **6. Validation** | VAL | TST | VER, QUA, CM |
| **7. Assessment** | ASR (external) | VER | CM |
| **8. Deployment** | PM | CM | VER, VAL, CM |

### Multi-Agent Coordination

**Pattern 1: Sequential Handoff**

Requirements phase → Design phase:

```
REQ completes SRS → COD gate check → PASS → DES begins design
```

**Pattern 2: Parallel Execution**

Design phase (multiple agents working simultaneously):

```
DES creates SAS, SDS
  ║
  ╠══► INT creates Integration Test Specs (parallel)
  ║
  ╠══► SAF reviews design for safety (parallel)
  ║
  ╚══► VER verifies design (after DES completes)
```

**Pattern 3: Cross-Cutting Coordination**

QUA reviews code during Implementation phase:

```
IMP implements module A → QUA reviews module A (parallel) → VER verifies module A
IMP implements module B → QUA reviews module B (parallel) → VER verifies module B
...
```

### Agent Synchronization

COD synchronizes agents at key points:

1. **Phase Start**: All primary agents notified
2. **Deliverable Submission**: VER/VAL agents notified for review
3. **Gate Check**: All agents must complete activities before gate
4. **Phase Transition**: New agents activated, old agents deactivated

---

## LIFECYCLE_STATE.md Management

### Purpose

`LIFECYCLE_STATE.md` is the **single source of truth** for project lifecycle status.

### LIFECYCLE_STATE.md Structure

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
- **Completion**: 70% (estimated)

## Phase History

| Phase | Status | Started | Completed | Gate Passed | Notes |
|-------|--------|---------|-----------|-------------|-------|
| 0. Initialization | Complete | 2026-02-10 | 2026-02-10 | N/A | COD initialized |
| 1. Planning | Complete | 2026-02-10 | 2026-02-10 | 2026-02-10 | All plans approved |
| 2. Requirements | Complete | 2026-02-10 | 2026-02-15 | 2026-02-15 | 42 requirements |
| 3. Design | In Progress | 2026-02-15 | - | - | 70% complete |
| 4. Implementation | Not Started | - | - | - | - |
| 5. Integration | Not Started | - | - | - | - |
| 6. Validation | Not Started | - | - | - | - |
| 7. Assessment | Not Started | - | - | - | Required for SIL 3 |
| 8. Deployment | Not Started | - | - | - | - |

## Deliverable Status

### Phase 3 (Design) - In Progress
- [x] Software Architecture Specification (SAS) - Approved 2026-02-16
- [x] Software Design Specification (SDS) - Approved 2026-02-17
- [ ] Software Interface Specifications - In Progress (70%)
- [ ] Software Integration Test Specification - Draft (50%)
- [x] Software Component Design Specification - Approved 2026-02-17
- [x] Software Component Test Specification - Approved 2026-02-17
- [ ] Architecture and Design Verification Report - Pending VER
- [ ] Software/Hardware Integration Test Specification - Not Started

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
- Software Req → Design: 70% (30/42 - in progress)
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

- DES (Designer) - Last activity: 15 min ago
- INT (Integrator) - Last activity: 2 hours ago
- VER (Verifier) - REQUIRED (design verification pending)

## Next Steps

1. Complete Software Interface Specifications (DES)
2. Finalize Integration Test Specification (INT)
3. Perform design verification (VER)
4. Generate Architecture and Design Verification Report (VER)
5. Run /cod gate-check design
```

### LIFECYCLE_STATE.md Update Triggers

COD updates `LIFECYCLE_STATE.md` on:

1. **Phase transition**: Update current phase, phase history
2. **Gate check**: Log gate result, criteria satisfied/violated
3. **Deliverable creation/update**: Update deliverable status
4. **Requirement change**: Log approval, update change log
5. **Agent activity**: Update active agents, last activity timestamp
6. **Iteration**: Log iteration, update change log
7. **Traceability update**: Update RTM status
8. **Metrics update**: Update code metrics, coverage, complexity

### LIFECYCLE_STATE.md Management Script

```python
#!/usr/bin/env python3
"""
LIFECYCLE_STATE.md management script
"""

import yaml
import datetime
from pathlib import Path

class LifecycleState:
    def __init__(self, project_root):
        self.project_root = Path(project_root)
        self.state_file = self.project_root / 'LIFECYCLE_STATE.md'
        self.state = self._load_state()
    
    def _load_state(self):
        """Load LIFECYCLE_STATE.md"""
        if not self.state_file.exists():
            return self._create_initial_state()
        # Parse markdown and extract state
        # (Implementation would parse markdown)
        return {}
    
    def _create_initial_state(self):
        """Create initial LIFECYCLE_STATE.md"""
        return {
            'project_name': '',
            'sil_level': 0,
            'lifecycle_model': 'V-Model',
            'cod_mode': 'Advisory',
            'created': datetime.datetime.now().isoformat(),
            'current_phase': 'planning',
            'phase_history': [],
            'deliverables': {},
            'traceability': {},
            'metrics': {}
        }
    
    def update_phase(self, new_phase):
        """Update current phase"""
        self.state['current_phase'] = new_phase
        self.state['phase_started'] = datetime.datetime.now().isoformat()
        self.state['phase_history'].append({
            'phase': new_phase,
            'status': 'in_progress',
            'started': datetime.datetime.now().isoformat()
        })
        self._save_state()
    
    def log_gate_check(self, phase, result, criteria):
        """Log gate check result"""
        if 'gate_history' not in self.state:
            self.state['gate_history'] = []
        
        self.state['gate_history'].append({
            'date': datetime.datetime.now().isoformat(),
            'phase': phase,
            'result': result,
            'criteria': criteria
        })
        
        # Update phase history
        for p in self.state['phase_history']:
            if p['phase'] == phase:
                if result == 'PASSED':
                    p['status'] = 'complete'
                    p['gate_passed'] = datetime.datetime.now().isoformat()
                else:
                    p['status'] = 'blocked'
                break
        
        self._save_state()
    
    def update_deliverable(self, phase, deliverable_name, status):
        """Update deliverable status"""
        if phase not in self.state['deliverables']:
            self.state['deliverables'][phase] = {}
        
        self.state['deliverables'][phase][deliverable_name] = {
            'status': status,
            'updated': datetime.datetime.now().isoformat()
        }
        self._save_state()
    
    def log_requirement_approval(self, activity, scope, files):
        """Log requirement approval"""
        if 'requirement_approvals' not in self.state:
            self.state['requirement_approvals'] = []
        
        self.state['requirement_approvals'].append({
            'date': datetime.datetime.now().isoformat(),
            'activity': activity,
            'scope': scope,
            'approved_by': 'User',
            'files_modified': files
        })
        self._save_state()
    
    def log_change(self, phase, change_type, description, impact, cr_number):
        """Log change in change log"""
        if 'change_log' not in self.state:
            self.state['change_log'] = []
        
        self.state['change_log'].append({
            'date': datetime.datetime.now().isoformat(),
            'phase': phase,
            'change_type': change_type,
            'description': description,
            'impact': impact,
            'cr_number': cr_number,
            'status': 'in_progress'
        })
        self._save_state()
    
    def _save_state(self):
        """Save LIFECYCLE_STATE.md"""
        # Convert state to markdown
        markdown = self._render_markdown()
        with open(self.state_file, 'w') as f:
            f.write(markdown)
    
    def _render_markdown(self):
        """Render state as markdown"""
        # Implementation would generate markdown from state
        return "# Project Lifecycle State\n\n..."
```

---

## Parallel Activities Coordination

### Purpose

Coordinate cross-cutting activities (CM, QUA, VER, SAF) that run throughout lifecycle.

### Cross-Cutting Agents

| Agent | Activities | Active Phases | Frequency |
|-------|-----------|---------------|-----------|
| **CM (Config Mgmt)** | Version control, change control, baselines | All phases (0-8) | Continuous |
| **QUA (Quality)** | Reviews, audits, quality gates | All phases (1-8) | Per deliverable |
| **VER (Verification)** | Document verification, static analysis | Phases 2-8 | Per deliverable |
| **SAF (Safety)** | Hazard analysis, safety reviews | Phases 2-6 | Periodic |

### Coordination Patterns

**Pattern 1: CM Continuous Activity**

```
Phase 1 (Planning)
  ├─ PM creates SQAP → CM commits to Git
  ├─ QUA creates SCMP → CM commits to Git
  └─ COD gate-check planning → CM establishes baseline-0

Phase 2 (Requirements)
  ├─ REQ creates SRS → CM commits to Git
  ├─ REQ updates RTM → CM commits to Git
  └─ COD gate-check requirements → CM establishes baseline-1

... (CM continues throughout all phases)
```

**Pattern 2: QUA Per-Deliverable Review**

```
Phase 4 (Implementation)
  ├─ IMP implements module A
  │   └─ QUA reviews module A (code review)
  ├─ IMP implements module B
  │   └─ QUA reviews module B (code review)
  └─ COD gate-check implementation
      └─ QUA verifies all code reviewed
```

**Pattern 3: VER Phase-End Verification**

```
Phase 3 (Design)
  ├─ DES creates SAS
  ├─ DES creates SDS
  ├─ INT creates Integration Test Specs
  └─ VER verifies design artifacts (before gate check)
      ├─ Verify SAS completeness
      ├─ Verify SDS completeness
      ├─ Verify traceability (RTM updated)
      └─ Generate Design Verification Report
```

**Pattern 4: SAF Periodic Safety Reviews**

```
Phase 2 (Requirements)
  └─ SAF performs hazard analysis, creates Hazard Log

Phase 3 (Design)
  └─ SAF reviews design for safety compliance

Phase 4 (Implementation)
  └─ SAF reviews safety-critical code

Phase 6 (Validation)
  └─ SAF validates safety requirements met
```

### Parallel Activity Scheduling

COD schedules cross-cutting activities:

```python
def schedule_cross_cutting_activities(phase, deliverables):
    """Schedule CM, QUA, VER, SAF activities"""
    
    activities = []
    
    # CM: Continuous version control
    activities.append({
        'agent': 'CM',
        'activity': 'Version control',
        'trigger': 'On every file change',
        'frequency': 'continuous'
    })
    
    # QUA: Per-deliverable review
    for deliverable in deliverables:
        activities.append({
            'agent': 'QUA',
            'activity': f'Review {deliverable}',
            'trigger': f'When {deliverable} submitted',
            'frequency': 'per-deliverable'
        })
    
    # VER: Phase-end verification
    activities.append({
        'agent': 'VER',
        'activity': f'Verify {phase} artifacts',
        'trigger': f'Before {phase} gate check',
        'frequency': 'phase-end'
    })
    
    # SAF: Periodic safety review (if phase 2-6)
    if phase in ['requirements', 'design', 'implementation', 'integration', 'validation']:
        activities.append({
            'agent': 'SAF',
            'activity': f'Safety review for {phase}',
            'trigger': f'{phase} midpoint and phase-end',
            'frequency': 'periodic'
        })
    
    return activities
```

---

## Tool Integration

### Workspace.py Workflow Management

COD integrates with `workspace.py wf` for workflow management:

```bash
# Check current phase status
workspace.py wf status

# Check specific phase status
workspace.py wf status --phase design

# List deliverables for phase
workspace.py wf list-deliverables --phase design

# Submit deliverable for review
workspace.py wf submit --deliverable "Software Architecture Specification" --phase design --file docs/design/SAS.md

# Approve deliverable (VER/VAL)
workspace.py wf approve --deliverable "Software Architecture Specification" --phase design --reviewer VER

# Generate phase report
workspace.py wf generate-report --phase design --output docs/reports/Design-Phase-Report.md

# Check baseline status
workspace.py wf baseline-status
```

### Workspace.py Traceability Management

COD integrates with `workspace.py trace` for traceability:

```bash
# Validate traceability for current phase
workspace.py trace validate

# Check traceability gaps
workspace.py trace check-gaps --phase design

# Generate traceability report
workspace.py trace report --output docs/traceability/RTM-Report.md

# Check forward traceability
workspace.py trace check-forward --from software_req --to design

# Check backward traceability
workspace.py trace check-backward --from design --to software_req
```

---

## Automation Scripts

### Phase Transition Checker

**Script**: `tools/phase_transition_checker.py` (~200 lines)

```python
#!/usr/bin/env python3
"""
Phase Transition Checker
Verifies phase ready for transition
"""

import sys
import json
from pathlib import Path

def check_phase_ready_for_transition(phase, sil_level, project_root):
    """Check if phase ready for gate check"""
    
    checks = []
    
    # 1. All deliverables complete
    deliverables = get_phase_deliverables(phase)
    deliverables_complete = check_deliverables_complete(phase, deliverables, project_root)
    checks.append({
        'name': 'Deliverables Complete',
        'passed': deliverables_complete['all_complete'],
        'details': deliverables_complete
    })
    
    # 2. Traceability updated
    traceability = check_traceability_updated(phase, project_root)
    checks.append({
        'name': 'Traceability Updated',
        'passed': traceability['updated'],
        'details': traceability
    })
    
    # 3. Quality activities complete
    quality = check_quality_activities(phase, sil_level, project_root)
    checks.append({
        'name': 'Quality Activities',
        'passed': quality['complete'],
        'details': quality
    })
    
    # 4. Verification complete (SIL 3-4)
    if sil_level >= 3:
        verification = check_verification_complete(phase, project_root)
        checks.append({
            'name': 'Verification (SIL 3-4)',
            'passed': verification['complete'],
            'details': verification
        })
    
    all_passed = all(c['passed'] for c in checks)
    
    return {
        'phase': phase,
        'sil_level': sil_level,
        'ready': all_passed,
        'checks': checks
    }

def get_phase_deliverables(phase):
    """Get required deliverables for phase"""
    
    deliverables = {
        'planning': ['SQAP', 'SCMP', 'SVP', 'SVaP', 'SQAP Verification Report'],
        'requirements': ['SRS', 'RTM', 'Overall Test Spec', 'Requirements Verification Report'],
        'design': ['SAS', 'SDS', 'Interfaces', 'Integration Test Spec', 'Design Verification Report'],
        'implementation': ['Source Code', 'Unit Tests', 'Code Verification Report', 'Component Test Report'],
        'integration': ['Integration Test Report', 'Integration Verification Report'],
        'validation': ['Validation Report', 'Overall Test Report'],
        'assessment': ['Assessment Report'],
        'deployment': ['Deployment Plan', 'Deployment Manual', 'Release Notes']
    }
    
    return deliverables.get(phase, [])

def check_deliverables_complete(phase, deliverables, project_root):
    """Check if all deliverables exist and approved"""
    
    # Placeholder: check if files exist
    complete_count = 0
    for deliverable in deliverables:
        # Check if deliverable exists in workspace.py wf
        # (Real implementation would call workspace.py)
        complete_count += 1
    
    return {
        'all_complete': complete_count == len(deliverables),
        'complete_count': complete_count,
        'total_count': len(deliverables)
    }

def check_traceability_updated(phase, project_root):
    """Check if RTM updated for phase"""
    
    # Placeholder: check RTM updated
    return {
        'updated': True,
        'coverage': 100.0
    }

def check_quality_activities(phase, sil_level, project_root):
    """Check quality activities complete"""
    
    # Placeholder: check QUA reviews complete
    return {
        'complete': True,
        'reviews': ['Code Review', 'Design Review']
    }

def check_verification_complete(phase, project_root):
    """Check verification complete (SIL 3-4)"""
    
    # Placeholder: check VER verification report exists
    return {
        'complete': True,
        'verification_report': f'docs/verification/{phase.capitalize()}-VER.md'
    }

def main():
    import argparse
    parser = argparse.ArgumentParser(description='Phase Transition Checker')
    parser.add_argument('phase', help='Phase to check')
    parser.add_argument('--sil', type=int, required=True, help='SIL level')
    parser.add_argument('--project-root', default='.', help='Project root')
    parser.add_argument('--json', action='store_true', help='JSON output')
    
    args = parser.parse_args()
    
    result = check_phase_ready_for_transition(args.phase, args.sil, args.project_root)
    
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        print(f"Phase Transition Check: {result['phase'].capitalize()}")
        print(f"Ready for Gate Check: {'✓ YES' if result['ready'] else '✗ NO'}")
        print("\nChecks:")
        for check in result['checks']:
            status = '✓' if check['passed'] else '✗'
            print(f"  {status} {check['name']}")
    
    sys.exit(0 if result['ready'] else 1)

if __name__ == '__main__':
    main()
```

### Agent Status Tracker

**Script**: `tools/agent_status_tracker.py` (~150 lines)

```python
#!/usr/bin/env python3
"""
Agent Status Tracker
Track agent activity and status
"""

import json
import datetime
from pathlib import Path

class AgentStatusTracker:
    def __init__(self, project_root):
        self.project_root = Path(project_root)
        self.status_file = self.project_root / '.agent_status.json'
        self.status = self._load_status()
    
    def _load_status(self):
        """Load agent status"""
        if self.status_file.exists():
            with open(self.status_file, 'r') as f:
                return json.load(f)
        return {'agents': {}}
    
    def log_agent_activity(self, agent, activity, details=None):
        """Log agent activity"""
        if agent not in self.status['agents']:
            self.status['agents'][agent] = {
                'activities': [],
                'last_activity': None
            }
        
        self.status['agents'][agent]['activities'].append({
            'timestamp': datetime.datetime.now().isoformat(),
            'activity': activity,
            'details': details
        })
        self.status['agents'][agent]['last_activity'] = datetime.datetime.now().isoformat()
        
        self._save_status()
    
    def get_active_agents(self, hours=24):
        """Get agents active in last N hours"""
        cutoff = datetime.datetime.now() - datetime.timedelta(hours=hours)
        
        active = []
        for agent, data in self.status['agents'].items():
            if data['last_activity']:
                last_activity = datetime.datetime.fromisoformat(data['last_activity'])
                if last_activity > cutoff:
                    active.append({
                        'agent': agent,
                        'last_activity': data['last_activity'],
                        'activities_count': len(data['activities'])
                    })
        
        return sorted(active, key=lambda x: x['last_activity'], reverse=True)
    
    def _save_status(self):
        """Save agent status"""
        with open(self.status_file, 'w') as f:
            json.dump(self.status, f, indent=2)

def main():
    import argparse
    parser = argparse.ArgumentParser(description='Agent Status Tracker')
    parser.add_argument('--log', help='Log agent activity: agent:activity')
    parser.add_argument('--list', action='store_true', help='List active agents')
    parser.add_argument('--project-root', default='.', help='Project root')
    
    args = parser.parse_args()
    
    tracker = AgentStatusTracker(args.project_root)
    
    if args.log:
        agent, activity = args.log.split(':', 1)
        tracker.log_agent_activity(agent, activity)
        print(f"✓ Logged activity for {agent}: {activity}")
    
    if args.list:
        active = tracker.get_active_agents(hours=24)
        print("Active Agents (last 24 hours):")
        for agent_data in active:
            print(f"  - {agent_data['agent']}: {agent_data['last_activity']} ({agent_data['activities_count']} activities)")
    
    return 0

if __name__ == '__main__':
    sys.exit(main())
```

---

## Example Scenario

### Complete SIL 3 Project Lifecycle

**Project**: Train Door Control System  
**SIL Level**: 3 (Strict Gatekeeper Mode)

#### Initialization

```bash
$ /cod plan --sil 3 --project train_door_control
```

**COD Output**:
```
✓ Lifecycle plan initialized for project: train_door_control
✓ SIL Level: 3 (Strict gate enforcement)
✓ Lifecycle Model: V-Model (Mandatory for SIL 3)
✓ Gate Enforcement: STRICT GATEKEEPER MODE

Created: LIFECYCLE_STATE.md

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
  1. Begin Phase 1 (Planning)
  2. When planning complete: /cod gate-check planning

Current Phase: Planning
```

#### Phase 1: Planning

```bash
# PM coordinates planning
$ /pm

# (PM creates SQAP, SCMP, SVP, SVaP with QUA, CM, VER, VAL)

# Gate check
$ /cod gate-check planning
```

**COD Output**:
```
═══════════════════════════════════════════════════════
PHASE GATE CHECK: Planning Complete
═══════════════════════════════════════════════════════

[✓] Planning Documents (5/5 complete)
[✓] Project Setup (4/4 complete)
[✓] Team Organization (4/4 satisfied)
[✓] Tool Qualification (SIL 3) (3/3 satisfied)
[✓] Independence Requirements (SIL 3) (3/3 satisfied)

═══════════════════════════════════════════════════════
GATE RESULT: ✓ PASSED
═══════════════════════════════════════════════════════

Baseline Established: Baseline 0 (git tag baseline-0)

═══════════════════════════════════════════════════════
PHASE TRANSITION: Requirements (Phase 2)
═══════════════════════════════════════════════════════

Active Agents: REQ, SAF, TST, VER, QUA, CM
```

#### Phase 2: Requirements

```bash
# User approval required
$ /req
```

**COD Output**:
```
🔐 APPROVAL REQUIRED: Requirements Activity

The Requirements Engineer (REQ) will establish software requirements.

Approve requirements activity? [Y/n]
```

**User**: `Y`

```bash
# REQ creates SRS, RTM
# SAF creates Hazard Log
# TST creates Overall Test Spec

# Check status
$ /cod status
```

**COD Output**:
```
Current Phase: Requirements (In Progress)
Completion: 80%

Deliverables:
  ✓ SRS - Complete
  ✓ RTM - Complete
  ✓ Hazard Log - Complete
  ⚠ Overall Test Spec - In Progress
  ☐ Requirements Verification Report - Pending VER
```

```bash
# Gate check
$ /cod gate-check requirements
```

**COD Output**:
```
═══════════════════════════════════════════════════════
GATE RESULT: ✓ PASSED
═══════════════════════════════════════════════════════

Baseline Established: Baseline 1 (git tag baseline-1)

═══════════════════════════════════════════════════════
PHASE HANDOFF: Requirements → Design
═══════════════════════════════════════════════════════

Handoff from:
  - REQ (Requirements Engineer) - SRS complete, RTM baselined
  - SAF (Safety Engineer) - Hazard Log baselined

Handoff to:
  - DES (Designer) - Begin architecture and design

Artifacts Available:
  - docs/SRS.md (42 requirements)
  - docs/RTM.md (100% traceable)
  - docs/Hazard-Log.md (5 hazards)
```

#### Phase 3-8: Continue Through Lifecycle

Similar pattern continues for all remaining phases (Design, Implementation, Integration, Validation, Assessment, Deployment).

---

## Summary

This workflow provides:

1. **Complete V-Model structure** - 8 phases with dependencies and parallel activities
2. **Phase initialization** - Entry criteria, baseline establishment, agent activation
3. **Phase execution** - Progress tracking, lifecycle violation detection, multi-agent coordination
4. **Phase transition** - Gate checks, baseline establishment, handoff protocols
5. **Agent coordination** - Phase-to-agent mapping, synchronization, parallel activity scheduling
6. **LIFECYCLE_STATE.md management** - Single source of truth for project status
7. **Parallel activities** - CM, QUA, VER, SAF coordination throughout lifecycle
8. **Tool integration** - workspace.py wf/trace for workflow and traceability management
9. **Automation scripts** - Phase transition checker, agent status tracker
10. **Complete example** - SIL 3 project lifecycle from initialization to deployment

**Key Principles**:
- **Strict phase sequence** (SIL 3-4: no skipping, no out-of-sequence)
- **Clear handoffs** between phases with artifact availability
- **Parallel activity coordination** for CM, QUA, VER, SAF
- **LIFECYCLE_STATE.md as single source of truth**
- **Automated tracking** with Python scripts and workspace.py integration

---

**Related Workflows**:
- `phase-gate-management-workflow.md` - Gate criteria and automation
- `traceability-rtm-workflow.md` - RTM management and gap detection
- `iteration-change-management-workflow.md` - Feedback loops and change control

**EN 50128 References**:
- Section 5.3: Software Lifecycle
- Section 5.3.2: Lifecycle Model (V-Model MANDATORY SIL 2-4)
- Section 5.3.2.1: V-Model structure
- Section 5.3.2.2: Lifecycle iterations
- Annex C Table C.1: Document Control Summary
