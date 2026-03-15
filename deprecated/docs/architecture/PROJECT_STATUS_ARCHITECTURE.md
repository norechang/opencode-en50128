# Project Status Maintenance Architecture

**Document ID**: DOC-ARCH-STATUS-2026-001  
**Version**: 1.0  
**Date**: 2026-02-24  
**Author**: COD (Lifecycle Coordinator)  
**Purpose**: Define single source of truth for example project status and synchronization methodology

---

## Problem Statement

### Current Issues (Identified 2026-02-24)

**Status information is scattered across multiple locations**:

1. **`.workspace` file** (platform root)
   - Contains: `active_workspace`, `sil`, `current_phase`, `completion`, `last_accessed`, `status`
   - Updated by: Workspace manager (`/ws` command)
   - Problem: Contains duplicate fields that also exist in `LIFECYCLE_STATE.md`

2. **`LIFECYCLE_STATE.md`** (example project root)
   - Contains: Project info, current phase, phase history, deliverables, metrics, traceability
   - Updated by: COD agent (`/cod` commands)
   - Problem: Very detailed (900+ lines), not synchronized with `.workspace`

3. **`README.md`** (example project root)
   - Contains: ❌ MISSING in train_door_control2
   - Expected: Project introduction, summary, current status, links to operational docs
   - Problem: No standard template, not synchronized with lifecycle state

### Synchronization Failures Observed

**Example from train_door_control2**:

| Source | Current Phase | Completion | Last Updated | Notes |
|--------|---------------|------------|--------------|-------|
| `.workspace` | Phase 6 - Integration | 0% | 2026-02-23 | Says "ready to begin" |
| `LIFECYCLE_STATE.md` | Integration (Phase 6) | 0% | 2026-02-23 | Detailed deliverables tracking |
| Phase History | Phase 5 complete | PARTIAL PASS | 2026-02-22 | MOD-001 only tested |
| Priority Tasks | Phase 5 work | - | - | 40 components untested |

**Issues**:
- `.workspace` says Phase 6 (Integration) is ready to begin
- `LIFECYCLE_STATE.md` says Phase 5 (Implementation) had PARTIAL PASS
- **Reality**: 40 components (MOD-002 to MOD-008) still need unit testing from Phase 5
- **Contradiction**: Phase 6 authorized but Phase 5 incomplete

---

## Architectural Principles

### Principle 1: Single Source of Truth (SSOT)

**Definition**: All project status SHALL derive from ONE authoritative source.

**Decision**: **`LIFECYCLE_STATE.md`** is the SSOT for project status.

**Rationale**:
1. Most detailed and comprehensive (deliverables, metrics, traceability)
2. Updated by COD agent (lifecycle authority)
3. Per-project isolation (one file per workspace)
4. Already contains all necessary information
5. Used by all agents for lifecycle decisions

### Principle 2: Derived Views

**Definition**: All other status displays SHALL be derived from SSOT.

**Implementation**:
- `.workspace` derives summary fields from `LIFECYCLE_STATE.md`
- `README.md` derives status section from `LIFECYCLE_STATE.md`
- Agent status displays derive from `LIFECYCLE_STATE.md`
- No independent status tracking outside SSOT

### Principle 3: Update Once, Reflect Everywhere

**Definition**: Status updates SHALL be made in SSOT only, then propagated.

**Workflow**:
```
COD updates LIFECYCLE_STATE.md (SSOT)
  ↓
Auto-sync to .workspace (summary)
  ↓
Auto-sync to README.md (user-facing)
  ↓
Agents read SSOT for decisions
```

### Principle 4: Workspace Awareness

**Definition**: All agents SHALL read active workspace from `.workspace` and operate on that workspace's SSOT.

**Implementation**:
- `.workspace` contains ONLY: `active_workspace` pointer + workspace metadata
- Agents always read `examples/<active_workspace>/LIFECYCLE_STATE.md` for status
- No status duplication in `.workspace`

---

## Proposed Architecture

### File Roles and Responsibilities

#### 1. `.workspace` (Platform Root)

**Role**: Workspace registry and active pointer

**Contents** (MINIMAL):
```json
{
  "active_workspace": "train_door_control2",
  "workspaces": {
    "train_door_control": {
      "path": "examples/train_door_control",
      "created": "2026-02-15T10:00:00Z",
      "last_accessed": "2026-02-21T15:22:49Z"
    },
    "train_door_control2": {
      "path": "examples/train_door_control2",
      "created": "2026-02-18T08:00:00Z",
      "last_accessed": "2026-02-24T00:00:00Z"
    }
  }
}
```

**REMOVED Fields** (now derived from SSOT):
- ❌ `sil` - Read from `LIFECYCLE_STATE.md` Project Information
- ❌ `current_phase` - Read from `LIFECYCLE_STATE.md` Current Status
- ❌ `completion` - Read from `LIFECYCLE_STATE.md` Current Status
- ❌ `status` - Read from `LIFECYCLE_STATE.md` Current Status
- ❌ `phase_5_status` - Read from `LIFECYCLE_STATE.md` Phase History
- ❌ `phase_5_gate_passed` - Read from `LIFECYCLE_STATE.md` Gate Check History
- ❌ `phase_6_priority_tasks` - Read from `LIFECYCLE_STATE.md` Next Steps

**Updated By**: Workspace manager (`/ws` commands) - ONLY for active pointer and timestamps

#### 2. `LIFECYCLE_STATE.md` (Project Root)

**Role**: Single Source of Truth for project status

**Sections** (COMPREHENSIVE):
1. **Project Information** - Name, SIL, lifecycle model, COD mode
2. **Current Status** - Current phase, completion, days in phase
3. **Phase History** - All phases with start/complete/gate dates
4. **Deliverable Status** - All deliverables by phase with approval chains
5. **Deliverable Approval Chain History** - Audit trail
6. **Requirement Approval History** - User approvals for requirement changes
7. **Change Log** - All changes with impact and CR numbers
8. **Gate Check History** - All gate checks with results
9. **Traceability Status** - Coverage across all traceability links
10. **Quality Metrics** - Requirements, design, code, test, defect metrics
11. **Agents Activity Log** - Agent invocations and artifacts modified
12. **Baselines** - Configuration baselines established
13. **Risks and Issues** - Active risks and issues tracking
14. **Next Steps** - Immediate actions and phase readiness

**Updated By**: COD agent ONLY (lifecycle authority)

**Read By**: All agents for lifecycle decisions

#### 3. `README.md` (Project Root)

**Role**: Human-readable project introduction and current status summary

**Template Structure**:
```markdown
# <Project Name>

**SIL Level**: <X> (from LIFECYCLE_STATE.md)  
**Current Phase**: <Phase Name> (from LIFECYCLE_STATE.md)  
**Completion**: <X>% (from LIFECYCLE_STATE.md)  
**Status**: <Active/Blocked/Complete> (from LIFECYCLE_STATE.md)

## Quick Start

[Links to build, test, run commands]

## Project Overview

[Business description, system context, safety requirements]

## Current Status

[AUTO-GENERATED from LIFECYCLE_STATE.md - see sync script]

**Phase Progress**:
- [x] Phase 1: Planning - Complete (2026-02-18)
- [x] Phase 2: Requirements - Complete (2026-02-19)
- [x] Phase 3: Architecture & Design - Complete (2026-02-21)
- [x] Phase 4: Component Design - Complete (2026-02-22)
- [ ] Phase 5: Implementation & Testing - IN PROGRESS (PARTIAL PASS)
- [ ] Phase 6: Integration - NOT STARTED

**Recent Activity**:
- 2026-02-22: Phase 4 gate check PASSED
- 2026-02-22: MOD-001 unit testing complete (100% coverage)
- 2026-02-22: Phase 5 gate check PARTIAL PASS (MOD-001 only)

**Next Steps**:
1. Complete unit testing MOD-002 to MOD-008 (40 components)
2. Measure MC/DC coverage (SIL 3 mandatory)
3. Run `/pm execute-phase component-implementation-testing` to complete Phase 5

## Documentation

- **Lifecycle State**: [LIFECYCLE_STATE.md](LIFECYCLE_STATE.md) - Detailed status
- **Requirements**: [docs/Software-Requirements-Specification.md](docs/Software-Requirements-Specification.md)
- **Architecture**: [docs/Software-Architecture-Specification.md](docs/Software-Architecture-Specification.md)
- **Design**: [docs/Software-Design-Specification.md](docs/Software-Design-Specification.md)

## Build and Test

[Build instructions]

## License and Safety

[Safety disclaimers, license info]
```

**AUTO-GENERATED Section**: "Current Status" section is auto-generated from `LIFECYCLE_STATE.md`

**Updated By**:
- Manual: Project owner (overview, build instructions)
- Auto-sync: COD agent after lifecycle updates

---

## Synchronization Methodology

### Update Workflow

#### Primary Update Path (COD → SSOT)

```
1. User invokes COD command (e.g., /cod gate-check phase-x)
2. COD performs lifecycle operation
3. COD updates LIFECYCLE_STATE.md (SSOT)
   - Update Current Status section
   - Add entry to Phase History
   - Update Gate Check History
   - Update Metrics
   - Update Next Steps
4. COD triggers sync to derived views:
   a. Update .workspace with last_accessed timestamp
   b. Auto-generate README.md "Current Status" section
5. COD returns status to user
```

#### Workspace Switch Path (WS → SSOT Read)

```
1. User invokes /ws switch <project>
2. WS updates .workspace active_workspace pointer
3. WS reads target LIFECYCLE_STATE.md (SSOT)
4. WS displays summary derived from SSOT:
   - Current phase (from Current Status)
   - Completion (from Current Status)
   - Next steps (from Next Steps)
5. WS updates .workspace last_accessed timestamp
```

#### Agent Status Query Path (Agent → SSOT Read)

```
1. User invokes /cod status (or other agent status)
2. Agent reads .workspace to get active_workspace
3. Agent reads examples/<active_workspace>/LIFECYCLE_STATE.md
4. Agent extracts and displays relevant sections
5. Agent returns formatted status
```

### Synchronization Functions

#### Function 1: `sync_workspace_from_lifecycle_state()`

**Purpose**: Update `.workspace` derived fields from `LIFECYCLE_STATE.md`

**Called By**: COD agent after any SSOT update

**Implementation**:
```python
def sync_workspace_from_lifecycle_state(workspace_name):
    """
    Sync .workspace metadata from LIFECYCLE_STATE.md (SSOT).
    Only updates timestamps - all status derived on read.
    """
    # Read SSOT
    lifecycle_path = f"examples/{workspace_name}/LIFECYCLE_STATE.md"
    lifecycle_state = parse_lifecycle_state(lifecycle_path)
    
    # Update .workspace (ONLY timestamps)
    workspace_data = read_json(".workspace")
    workspace_data["workspaces"][workspace_name]["last_accessed"] = now()
    
    # DO NOT store sil, current_phase, completion, etc. in .workspace
    # These are DERIVED on read from LIFECYCLE_STATE.md
    
    write_json(".workspace", workspace_data)
```

#### Function 2: `generate_readme_status()`

**Purpose**: Auto-generate README.md "Current Status" section from `LIFECYCLE_STATE.md`

**Called By**: COD agent after phase transitions or gate checks

**Implementation**:
```python
def generate_readme_status(workspace_name):
    """
    Auto-generate README.md Current Status section from LIFECYCLE_STATE.md.
    """
    # Read SSOT
    lifecycle_path = f"examples/{workspace_name}/LIFECYCLE_STATE.md"
    lifecycle_state = parse_lifecycle_state(lifecycle_path)
    
    # Extract key fields
    current_phase = lifecycle_state["current_status"]["current_phase"]
    completion = lifecycle_state["current_status"]["completion"]
    phase_history = lifecycle_state["phase_history"]
    next_steps = lifecycle_state["next_steps"]
    
    # Generate markdown
    status_section = f"""## Current Status

**Phase Progress**:
{format_phase_history(phase_history)}

**Recent Activity**:
{format_recent_activity(lifecycle_state)}

**Next Steps**:
{format_next_steps(next_steps)}
"""
    
    # Update README.md (replace Current Status section only)
    readme_path = f"examples/{workspace_name}/README.md"
    update_readme_section(readme_path, "Current Status", status_section)
```

#### Function 3: `get_workspace_status()`

**Purpose**: Get current workspace status by reading SSOT

**Called By**: All agents, workspace manager

**Implementation**:
```python
def get_workspace_status(workspace_name):
    """
    Get workspace status from SSOT (LIFECYCLE_STATE.md).
    Returns derived view - does NOT cache in .workspace.
    """
    lifecycle_path = f"examples/{workspace_name}/LIFECYCLE_STATE.md"
    lifecycle_state = parse_lifecycle_state(lifecycle_path)
    
    return {
        "project_name": lifecycle_state["project_info"]["project_name"],
        "sil": lifecycle_state["project_info"]["sil_level"],
        "current_phase": lifecycle_state["current_status"]["current_phase"],
        "completion": lifecycle_state["current_status"]["completion"],
        "status": lifecycle_state["current_status"]["status"],
        "days_in_phase": lifecycle_state["current_status"]["days_in_phase"],
        "last_updated": lifecycle_state["project_info"]["last_updated"],
        # All fields DERIVED from SSOT, not stored separately
    }
```

### Consistency Guarantees

**GUARANTEE 1: No Stale Data**
- `.workspace` NEVER caches status fields (only active pointer + timestamps)
- All status queries read from SSOT (`LIFECYCLE_STATE.md`)
- No possibility of `.workspace` and `LIFECYCLE_STATE.md` being out of sync

**GUARANTEE 2: Single Update Point**
- ONLY COD agent updates `LIFECYCLE_STATE.md`
- All lifecycle operations flow through COD
- No agent can directly modify SSOT (enforced by architecture)

**GUARANTEE 3: Atomic Updates**
- COD updates SSOT atomically (single file write)
- Sync to derived views happens immediately after SSOT update
- User sees consistent view across all status displays

**GUARANTEE 4: Audit Trail**
- All SSOT updates logged in Change Log section
- All gate checks logged in Gate Check History
- All approvals logged in Approval Chain History
- Complete audit trail for EN 50128 compliance

---

## Implementation Plan

### Phase 1: Update `.workspace` Schema (HIGH PRIORITY)

**Action**: Remove redundant fields from `.workspace`

**Before**:
```json
{
  "active_workspace": "train_door_control2",
  "workspaces": {
    "train_door_control2": {
      "path": "examples/train_door_control2",
      "sil": 3,                              // ❌ REMOVE (read from SSOT)
      "current_phase": "Phase 6 - Integration", // ❌ REMOVE
      "completion": 0,                       // ❌ REMOVE
      "last_accessed": "2026-02-23T00:00:00.000000",
      "status": "active",                    // ❌ REMOVE
      "phase_5_status": "Complete (PARTIAL PASS - MOD-001 only)", // ❌ REMOVE
      "phase_5_gate_passed": "2026-02-22",   // ❌ REMOVE
      "phase_6_priority_tasks": [...]        // ❌ REMOVE
    }
  }
}
```

**After** (MINIMAL):
```json
{
  "active_workspace": "train_door_control2",
  "workspaces": {
    "train_door_control2": {
      "path": "examples/train_door_control2",
      "created": "2026-02-18T08:00:00Z",
      "last_accessed": "2026-02-24T00:00:00Z"
    }
  }
}
```

**Impact**: All status queries now read from SSOT, no stale data possible

### Phase 2: Create README.md Template

**Action**: Create standard README.md template for example projects

**Files**:
- `.opencode/templates/project-readme-template.md` - New template
- Includes auto-generated "Current Status" section marker

### Phase 3: Update Workspace Manager (`/ws` command)

**Action**: Modify workspace.md agent to read SSOT for status display

**Changes**:
1. `/ws status` - Read from `LIFECYCLE_STATE.md` instead of `.workspace`
2. `/ws list` - Read each workspace's `LIFECYCLE_STATE.md` for status
3. `/ws switch` - Display status derived from target SSOT

### Phase 4: Update COD Agent

**Action**: Add sync functions to COD lifecycle operations

**Changes**:
1. After `/cod gate-check` - Sync README.md status section
2. After phase transitions - Update README.md
3. After deliverable approvals - Sync if phase completion changed
4. Add `/cod sync-status` command for manual sync

### Phase 5: Update All Agents

**Action**: Ensure all agents read SSOT for status, not `.workspace`

**Agents to Update**:
- REQ, DES, IMP, TST, INT, VER, VAL, SAF, QUA, PM, CM, COD

**Changes**:
- Read `.workspace` for active_workspace pointer ONLY
- Read `LIFECYCLE_STATE.md` for all status queries
- Display workspace context derived from SSOT

### Phase 6: Create train_door_control2 README.md

**Action**: Generate initial README.md for train_door_control2

**Status**: ❌ MISSING (priority task)

---

## Validation and Testing

### Test Case 1: Phase Transition Sync

**Scenario**: User completes Phase 5, transitions to Phase 6

**Steps**:
1. `/cod gate-check component-implementation-testing`
2. Gate passes
3. COD updates `LIFECYCLE_STATE.md` (Phase 5 complete, Phase 6 current)
4. COD syncs README.md "Current Status" section
5. `/ws status` shows Phase 6 as current
6. `/cod status` shows Phase 6 as current
7. README.md shows Phase 6 as current
8. `.workspace` shows last_accessed updated (no status fields)

**Expected**: All views show Phase 6 consistently

### Test Case 2: Workspace Switch

**Scenario**: User switches from project A to project B

**Steps**:
1. Current workspace: train_door_control2 (Phase 5)
2. `/ws switch train_door_control`
3. Workspace manager reads train_door_control SSOT
4. Displays status from train_door_control SSOT
5. `/cod status` shows train_door_control status
6. `/ws switch train_door_control2`
7. Displays train_door_control2 status from SSOT

**Expected**: Each switch shows correct workspace status, no cross-contamination

### Test Case 3: Multi-Agent Status Query

**Scenario**: Multiple agents query status for same workspace

**Steps**:
1. `/cod status` - Reads SSOT, shows Phase 5
2. `/pm status` - Reads SSOT, shows Phase 5
3. `/ws status` - Reads SSOT, shows Phase 5
4. User opens README.md - Shows Phase 5

**Expected**: All status displays consistent (all read from SSOT)

### Test Case 4: README.md Auto-Generation

**Scenario**: COD completes gate check, auto-updates README.md

**Steps**:
1. Initial README.md shows Phase 4 complete
2. `/cod gate-check component-design`
3. Gate passes (Phase 4 → Phase 5 transition)
4. COD updates LIFECYCLE_STATE.md
5. COD auto-generates README.md "Current Status" section
6. User opens README.md
7. README.md shows Phase 5 as current

**Expected**: README.md automatically updated with new status

---

## Migration Plan (train_door_control2)

### Current State Analysis

**Problem**: train_door_control2 has inconsistent status:
- `.workspace` says Phase 6 (Integration), 0% complete
- `LIFECYCLE_STATE.md` says Phase 5 PARTIAL PASS (MOD-001 only)
- 40 components (MOD-002 to MOD-008) still need unit testing

**Root Cause**: Phase 5 gate was passed with condition (PARTIAL PASS), but:
1. Gate authorization allowed Phase 6 entry (incorrect for SIL 3 strict mode)
2. `.workspace` was updated to Phase 6 independently
3. Reality: Phase 5 still has substantial work (40 components untested)

### Recommended Fix

**Option 1: Revert to Phase 5 (RECOMMENDED)**

**Action**: Reset current phase to Phase 5, complete remaining work

**Steps**:
1. Update `LIFECYCLE_STATE.md`:
   - Set `current_phase` = "Component Implementation and Testing (Phase 5)"
   - Set `status` = "IN PROGRESS - Completing MOD-002 to MOD-008"
   - Set `completion` = 25% (13/53 components tested)
2. Update `.workspace`:
   - Remove all status fields (keep only path + timestamps)
3. Create `README.md`:
   - Auto-generate from LIFECYCLE_STATE.md
   - Show Phase 5 as current with pending tasks
4. User runs: `/pm execute-phase component-implementation-testing --resume`
5. Complete unit testing for MOD-002 to MOD-008
6. Measure MC/DC coverage (SIL 3 mandatory)
7. Run: `/cod gate-check component-implementation-testing` (full pass this time)
8. If full pass: Transition to Phase 6

**Rationale**: SIL 3 strict mode should NOT allow Phase 6 entry with incomplete Phase 5

**Option 2: Accept Partial and Document (NOT RECOMMENDED)**

**Action**: Accept Phase 5 PARTIAL PASS as sufficient, proceed with Phase 6

**Rationale**: NOT RECOMMENDED because:
- Violates SIL 3 strict gatekeeper principles
- 40 untested components = HIGH RISK
- MC/DC coverage not measured (SIL 3 MANDATORY per Table A.21)
- Creates precedent for incomplete phases

### COD Gate Check Policy Clarification

**ISSUE**: COD allowed PARTIAL PASS for SIL 3 project

**EN 50128 Requirement**: SIL 3 requires 100% statement, branch, AND condition (MC/DC) coverage (Table A.21)

**COD Behavior Should Be**:

**SIL 3-4 Strict Gatekeeper Mode**:
- ✅ FULL PASS: All criteria 100% satisfied → Authorize transition
- ❌ PARTIAL PASS: Rejected, same as FAIL → Block transition, require completion
- ❌ FAIL: Block transition, require rework

**Rationale**: SIL 3-4 safety integrity cannot compromise on mandatory requirements

**Action**: Update COD gate check logic to reject PARTIAL PASS for SIL 3-4

---

## Documentation Updates Required

### 1. Update COD Agent Command Definition

**File**: `.opencode/commands/cod.md`

**Changes**:
- Add "Workspace Awareness" section with SSOT architecture
- Update `/cod gate-check` to specify PARTIAL PASS handling by SIL
- Add `/cod sync-status` command for manual README.md sync
- Update all command examples to show SSOT-first approach

### 2. Update Workspace Manager Command

**File**: `.opencode/commands/workspace.md`

**Changes**:
- Update `.workspace` schema (remove status fields)
- Update all commands to read SSOT instead of `.workspace` cache
- Add "SSOT Architecture" section referencing this document

### 3. Update Project Management Skill

**File**: `.opencode/skills/en50128-project-management/SKILL.md`

**Changes**:
- Add SSOT architecture principles
- Update PM workflow to coordinate with COD (SSOT authority)
- Clarify that PM reports status via COD, does not maintain separate status

### 4. Update All Agent Skills

**Files**: `.opencode/skills/en50128-*/SKILL.md`

**Changes**:
- Add "Workspace Context" section
- Specify: Read `.workspace` for active pointer, read `LIFECYCLE_STATE.md` for status
- Remove any instructions to update `.workspace` with status fields

### 5. Create README.md Template

**File**: `.opencode/templates/project-readme-template.md`

**New file**: Standard template for example project README.md

### 6. Update Examples README

**File**: `examples/README.md`

**Changes**:
- Add section on README.md structure and auto-sync
- Add section on SSOT architecture
- Update workflow to mention README.md creation

---

## Summary

### Key Decisions

1. **SSOT**: `LIFECYCLE_STATE.md` is the single source of truth for all project status
2. **Derived Views**: `.workspace` and `README.md` are derived views, never independently updated
3. **Workspace File**: Contains ONLY active pointer + timestamps, no status duplication
4. **Auto-Sync**: COD automatically updates README.md after lifecycle operations
5. **No Cache**: All status queries read from SSOT, no caching in `.workspace`

### Benefits

1. **Consistency**: Impossible to have conflicting status across files
2. **Simplicity**: Only one file to update (COD is authority)
3. **Audit Trail**: Complete history in LIFECYCLE_STATE.md
4. **Maintainability**: Single update point, no sync bugs
5. **EN 50128 Compliance**: Lifecycle authority (COD) maintains official state

### Implementation Priority

**IMMEDIATE** (Phase 1-2):
1. Update `.workspace` schema (remove status fields)
2. Create README.md template
3. Generate train_door_control2 README.md

**HIGH** (Phase 3-5):
4. Update workspace manager to read SSOT
5. Update COD agent with sync functions
6. Update all agent skills

**MEDIUM** (Phase 6):
7. Validation and testing
8. Migration of train_door_control2 status

---

**Approved By**: COD (Lifecycle Coordinator)  
**Effective Date**: 2026-02-24  
**Review Date**: After implementation complete

---

## References

- **LIFECYCLE.md**: V-Model lifecycle phases and deliverables
- **AGENTS.md**: Agent roles and COD authority
- **workspace.md**: Workspace management command definition
- **EN 50128:2011**: Section 5.3 (Lifecycle issues and documentation)
