# Workspace Management Command

**Command**: `/workspace` or `/ws`  
**Purpose**: Manage EN 50128 project workspaces (switch between examples, resume progress)

---

## Description

The workspace management system allows you to:
- **Switch** between different example projects (e.g., train_door_control, train_door_control2)
- **Resume** progress on a specific project
- **List** all available projects with their status
- **Create** new project workspaces
- **Archive** completed projects

Each workspace maintains its own:
- Lifecycle state (current phase, completion percentage)
- Documentation (requirements, architecture, design, tests)
- Source code and build artifacts
- Configuration and planning documents

---

## Usage

### List all available workspaces
```bash
/workspace list
/ws list
```

**Output**:
- List of all projects in `examples/`
- Current phase for each project
- Completion percentage
- Last modified date
- Active workspace indicator (*)

**Implementation**:
1. Read `.workspace` to get `active_workspace` and workspace registry
2. For each workspace in registry:
   - Call `get_workspace_status(workspace_name)` to read from LIFECYCLE_STATE.md
   - Extract: project_name, sil, current_phase, completion, status
3. Display formatted list with active indicator (*)
4. Sort by last_accessed (most recent first)

### Switch to a different workspace
```bash
/workspace switch <project_name>
/ws switch train_door_control
```

**Actions**:
1. Validate target workspace exists in `.workspace` registry
2. Update `.workspace` file:
   - Set `active_workspace` to target project name
   - Update `last_accessed` timestamp for target workspace
3. Read target workspace LIFECYCLE_STATE.md using `get_workspace_status()`
4. Display workspace summary (SIL, current phase, completion, next steps)

**Implementation**:
- Read from SSOT (LIFECYCLE_STATE.md) after switch
- DO NOT cache status in `.workspace`
- Display derived status from LIFECYCLE_STATE.md

### Show current workspace status
```bash
/workspace status
/ws status
```

**Output**:
- Active project name
- Current lifecycle phase
- Phase completion percentage
- Recent activity
- Next recommended actions

**Implementation**:
1. Read `.workspace` to get `active_workspace`
2. Call `get_workspace_status(active_workspace)` to read from LIFECYCLE_STATE.md
3. Extract additional details:
   - Phase history (lines 120+)
   - Recent activity (lines 45+)
   - Next actions (lines 29+)
4. Display formatted status report

### Create a new workspace
```bash
/workspace create <project_name> --sil <0-4>
/ws create brake_controller --sil 4
```

**Actions**:
1. Create project directory structure
2. Initialize LIFECYCLE_STATE.md
3. Copy planning document templates
4. Run `/cod plan --sil <level> --project <name>`

### Resume a workspace (same as switch)
```bash
/workspace resume <project_name>
/ws resume train_door_control2
```

### Archive a completed workspace
```bash
/workspace archive <project_name>
/ws archive train_door_control
```

**Actions**:
1. Move project to `examples/archived/`
2. Create archive summary
3. Update workspace index

---

## Command Implementations

When the user invokes `/ws status`, `/ws list`, or `/ws switch`, you MUST:

### `/ws status` - Show Active Workspace Status

**Step-by-step execution**:

1. **Read active workspace pointer**:
   ```
   Read .workspace file
   Extract: active_workspace = <workspace_name>
   ```

2. **Read SSOT for active workspace**:
   ```
   Call get_workspace_status(active_workspace)
   Returns: {project_name, sil, current_phase, completion, status}
   ```

3. **Read additional details from LIFECYCLE_STATE.md**:
   ```
   Read examples/<active_workspace>/LIFECYCLE_STATE.md
   Extract recent activity (look for "Recent Activity" section around line 45)
   Extract next actions (look for "Next Actions" section around line 29)
   Extract phase history (look for "Phase History" section around line 120)
   ```

4. **Display formatted status**:
   ```
   📊 Active Workspace Status
   
   Project: <project_name>
   SIL Level: <sil>
   Current Phase: <current_phase>
   Completion: <completion>
   Status: <status>
   
   📋 Recent Activity:
   <list recent activity from LIFECYCLE_STATE.md>
   
   🎯 Next Actions:
   <list next actions from LIFECYCLE_STATE.md>
   
   Available commands:
   /cod status - Detailed lifecycle state
   /cod gate-check <phase> - Check phase gate
   /ws list - List all workspaces
   /ws switch <name> - Switch workspace
   ```

**Example Output**:
```
📊 Active Workspace Status

Project: Train Door Control System (v2)
SIL Level: 3
Current Phase: Component Implementation and Testing (Phase 5)
Completion: 25% (13 of 53 components tested)
Status: IN PROGRESS - Completing MOD-002 to MOD-008 unit testing (40 components remaining)

📋 Recent Activity:
- 2026-02-22: Phase 5 status corrected (was incorrectly showing Phase 6)
- 2026-02-22: MOD-001 unit testing complete (100% MC/DC coverage)
- 2026-02-21: Source code implementation complete (53 components)

🎯 Next Actions:
1. Complete unit testing for MOD-002 to MOD-008 (40 components)
2. Achieve 100% statement/branch/condition (MC/DC) coverage for all components
3. Run code review (QUA) after all unit tests complete
4. Submit to VER for verification

Available commands:
/cod status - Detailed lifecycle state
/imp - Continue implementation work
/tst - Execute unit tests
/qua - Run code review
```

---

### `/ws list` - List All Workspaces

**Step-by-step execution**:

1. **Read workspace registry**:
   ```
   Read .workspace file
   Extract: active_workspace, workspaces dict
   ```

2. **For each workspace in registry**:
   ```
   For each (name, metadata) in workspaces:
     Call get_workspace_status(name)
     Returns: {project_name, sil, current_phase, completion, status}
     Collect: (name, project_name, sil, current_phase, completion, last_accessed, is_active)
   ```

3. **Sort by last_accessed (most recent first)**

4. **Display formatted list**:
   ```
   📂 Available Workspaces
   
   <active indicator> <workspace_name> (<SIL level>)
     Phase: <current_phase>
     Completion: <completion>
     Last accessed: <last_accessed>
   
   Total: <count> workspaces
   
   Commands:
   /ws switch <name> - Switch to workspace
   /ws status - Show active workspace details
   /ws create <name> --sil <level> - Create new workspace
   ```

**Example Output**:
```
📂 Available Workspaces

* train_door_control2 (SIL 3) - ACTIVE
  Phase: Component Implementation and Testing (Phase 5)
  Completion: 25% (13 of 53 components tested)
  Last accessed: 2026-02-24 10:15:00

  train_door_control (SIL 3)
  Phase: Validation (Phase 7)
  Completion: 85%
  Last accessed: 2026-02-18 14:08:00

Total: 2 workspaces

Commands:
/ws switch <name> - Switch to workspace
/ws status - Show active workspace details
/ws create <name> --sil <level> - Create new workspace
```

---

### `/ws switch <workspace_name>` - Switch Active Workspace

**Step-by-step execution**:

1. **Validate target workspace exists**:
   ```
   Read .workspace file
   Check if <workspace_name> exists in workspaces dict
   If not found: Display error with available workspace list
   ```

2. **Update workspace registry**:
   ```
   Read .workspace file
   Set active_workspace = <workspace_name>
   Update workspaces[workspace_name].last_accessed = current timestamp (ISO 8601)
   Write .workspace file
   ```

3. **Read target workspace status from SSOT**:
   ```
   Call get_workspace_status(workspace_name)
   Returns: {project_name, sil, current_phase, completion, status}
   ```

4. **Read next actions from LIFECYCLE_STATE.md**:
   ```
   Read examples/<workspace_name>/LIFECYCLE_STATE.md
   Extract next actions (around line 29)
   ```

5. **Display switch confirmation and summary**:
   ```
   ✅ Workspace switched to: <workspace_name>
   
   Project: <project_name>
   SIL Level: <sil>
   Current Phase: <current_phase>
   Completion: <completion>
   Status: <status>
   
   🎯 Next Steps:
   <list next actions>
   
   Available commands:
   /cod status - Detailed lifecycle state
   /cod gate-check <phase> - Check phase gate
   <phase-specific commands based on current phase>
   ```

**Example Output**:
```
✅ Workspace switched to: train_door_control

Project: Train Door Control System
SIL Level: 3
Current Phase: Validation (Phase 7)
Completion: 85%
Status: IN PROGRESS - Completing validation testing

🎯 Next Steps:
1. Run validation tests (Overall Software Test)
2. Review validation results
3. Prepare for independent assessment

Available commands:
/cod status - Detailed lifecycle state
/val - Run validation activities
/cod gate-check validation - Check phase 7 gate
```

---

## SSOT Architecture: Status Queries

**Single Source of Truth**: `LIFECYCLE_STATE.md` (per-project)

### Status Query Pattern

When `/ws status` or `/ws list` is invoked:

1. Read `.workspace` to get active workspace and workspace list
2. For each workspace, read `examples/<workspace>/LIFECYCLE_STATE.md`
3. Extract status fields:
   - Project name (line 11: `| **Project Name** | <value> |`)
   - SIL level (line 12: `| **SIL Level** | <value> |`)
   - Current phase (line 24: `| **Current Phase** | <value> |`)
   - Completion (line 27: `| **Completion** | <value> |`)
   - Status (line 28: `| **Status** | <value> |`)
4. Display derived status (never cached)

### Function: `get_workspace_status(workspace_name)`

**Purpose**: Read workspace status from LIFECYCLE_STATE.md (SSOT)

**Algorithm**:
```
Input: workspace_name (string, e.g., "train_door_control2")
Output: dict with keys: project_name, sil, current_phase, completion, status

1. Construct path: lifecycle_path = "examples/{workspace_name}/LIFECYCLE_STATE.md"
2. Read LIFECYCLE_STATE.md content
3. Parse Project Information table (lines 8-16):
   - Extract "Project Name" from markdown table row
   - Extract "SIL Level" from markdown table row (convert to integer)
4. Parse Current Status table (lines 20-28):
   - Extract "Current Phase" from markdown table row
   - Extract "Completion" from markdown table row
   - Extract "Status" from markdown table row
5. Return status dictionary

Parsing pattern for markdown tables:
- Find line matching: | **<field_name>** | <value> |
- Extract <value> using regex: r'\| \*\*{field}\*\* \| (.*?) \|'
- Strip whitespace from extracted value
```

**Example Parsing**:
```markdown
# Input (LIFECYCLE_STATE.md lines 8-16):
| **Project Name** | Train Door Control System (v2) |
| **SIL Level** | 3 |

# Output:
{
  "project_name": "Train Door Control System (v2)",
  "sil": 3,
  "current_phase": "Component Implementation and Testing (Phase 5)",
  "completion": "25% (13 of 53 components tested)",
  "status": "IN PROGRESS - Completing MOD-002 to MOD-008 unit testing (40 components remaining)"
}
```

**Key Principle**: NEVER cache status fields in `.workspace`. Always read from SSOT on demand.

**Implementation Note**: When implementing this function, use the Read tool to read LIFECYCLE_STATE.md, then parse the markdown tables using regex or string matching to extract the required fields.

---

## Workspace State File

**Location**: `/home/norechang/work/EN50128/.workspace`

**Format** (JSON) - Simplified Schema (SSOT Architecture):
```json
{
  "active_workspace": "train_door_control2",
  "workspaces": {
    "train_door_control": {
      "path": "examples/train_door_control",
      "created": "2026-02-18T14:08:00Z",
      "last_accessed": "2026-02-18T14:08:00Z"
    },
    "train_door_control2": {
      "path": "examples/train_door_control2",
      "created": "2026-02-22T00:00:00Z",
      "last_accessed": "2026-02-21T14:38:00Z"
    }
  }
}
```

**IMPORTANT - SSOT Architecture**:
- `.workspace` contains ONLY workspace registry (path, timestamps)
- **NO status fields** (sil, current_phase, completion, status, etc.)
- All status information read from `LIFECYCLE_STATE.md` (Single Source of Truth)
- No caching, no duplication, no synchronization issues

---

## Workspace Directory Structure

Each workspace has standardized structure:

```
examples/<project_name>/
├── LIFECYCLE_STATE.md          # Phase tracking, deliverables status
├── README.md                    # Project overview
├── Makefile                     # Build system
├── docs/
│   ├── system/                  # System-level input documents
│   ├── plans/                   # SQAP, SCMP, SVP, SVaP
│   ├── Software-Requirements-Specification.md
│   ├── Software-Architecture-Specification.md
│   ├── Requirements-Traceability-Matrix.md
│   ├── Hazard-Log.md
│   ├── config/                  # Configuration items
│   ├── reports/                 # Verification reports
│   └── test/                    # Test specifications
├── src/                         # Source code
├── test/                        # Test code
├── build/                       # Build artifacts (not committed)
└── lib/                         # External libraries
```

---

## Workspace Switching Mechanism

### 1. Detect Current Workspace

Check `.workspace` file for `active_workspace` field.

If `.workspace` doesn't exist, create it by scanning `examples/` for directories containing `LIFECYCLE_STATE.md`.

**SSOT Pattern**: Read workspace pointer from `.workspace`, then read status from `LIFECYCLE_STATE.md`.

### 2. Save Current State

Before switching, ensure current workspace state is saved:
- LIFECYCLE_STATE.md is up to date
- All documents committed to git (optional, warn if uncommitted changes)
- Update `.workspace` with last_accessed timestamp

### 3. Load Target Workspace

- Read active workspace path from `.workspace`
- Read target `examples/<workspace>/LIFECYCLE_STATE.md` to extract status
- Display workspace summary (SIL, phase, completion from LIFECYCLE_STATE.md)
- Set `active_workspace` in `.workspace`
- Update `last_accessed` timestamp
- Recommend next actions based on current phase

**SSOT Pattern**: All status derived from LIFECYCLE_STATE.md on demand.

### 4. Context Restoration

When resuming a workspace, the agent should:
- Read LIFECYCLE_STATE.md to understand current phase
- Read Software Requirements Specification to understand project scope
- Read Hazard Log to understand safety context
- Display summary: "You are working on <project>, currently in <phase>, <completion>% complete. Next steps: <actions>"

---

## Integration with COD Agent

### Update COD to be Workspace-Aware

The Lifecycle Coordinator (COD) agent should:

1. **Always operate on active workspace**
   - Read `.workspace` to determine active project
   - Load `<active_workspace>/LIFECYCLE_STATE.md`

2. **Display workspace context**
   - When running `/cod status`, show active workspace name
   - Example: "Active Workspace: train_door_control2 (SIL 3)"

3. **Support workspace-specific commands**
   - `/cod plan` creates LIFECYCLE_STATE.md in active workspace
   - `/cod gate-check` checks phase gates for active workspace
   - `/cod status` shows status of active workspace

4. **Workspace isolation**
   - Each workspace has independent lifecycle state
   - Phase transitions only affect active workspace
   - No cross-contamination between projects

---

## Example Workflow

### Scenario: Switch from train_door_control2 to train_door_control

```bash
# Current workspace
/ws status
# Output: Active workspace: train_door_control2 (SIL 3)
#         Current phase: Architecture & Design (Phase 3)
#         Completion: 30%
#         Last activity: Created Software Architecture Specification

# List all workspaces
/ws list
# Output:
# Available workspaces:
#   * train_door_control2 (SIL 3) - Phase 3: Architecture & Design - 30% - Active
#     train_door_control  (SIL 3) - Phase 7: Validation - 85%

# Switch to train_door_control
/ws switch train_door_control
# Output:
# Switching workspace...
# Saved train_door_control2 state (Phase 3, 30%)
# Loading train_door_control workspace...
#
# ✅ Workspace switched to: train_door_control
#
# Project: Train Door Control System
# SIL Level: 3
# Current Phase: Phase 7 - Validation
# Completion: 85%
# Last Activity: Completed integration testing (2026-02-18)
#
# Next Steps:
# 1. Run validation tests (Overall Software Test)
# 2. Review validation results
# 3. Prepare for independent assessment
#
# Available commands:
#   /val - Run validation activities
#   /cod gate-check validation - Check phase 7 gate
#   /cod status - View detailed lifecycle state

# Check lifecycle state (now points to train_door_control)
/cod status
# Output shows train_door_control Phase 7 status

# Resume work on train_door_control2
/ws switch train_door_control2
# Output:
# Switching workspace...
# Saved train_door_control state (Phase 7, 85%)
# Loading train_door_control2 workspace...
#
# ✅ Workspace switched to: train_door_control2
#
# Project: Train Door Control System (v2)
# SIL Level: 3
# Current Phase: Phase 3 - Architecture & Design
# Completion: 30%
# Last Activity: Created Software Architecture Specification (2026-02-21)
#
# Next Steps:
# 1. Complete Software Design Specification
# 2. Create Software Interface Specifications
# 3. Run design reviews
#
# Available commands:
#   /des - Continue design work
#   /cod gate-check architecture-design - Check phase 3 gate
```

---

## Implementation Notes

### Workspace File Management

**Location**: `/home/norechang/work/EN50128/.workspace`

**Read on startup**: Check if `.workspace` exists
- If exists: Load active workspace
- If not exists: Create by scanning `examples/`, set first project as active

**Update on switch**: Write new active workspace

**Auto-save**: Update last_accessed timestamp on any activity

### Git Integration (Optional)

When switching workspaces, optionally check for uncommitted changes:

```bash
git status examples/<active_workspace>
```

If uncommitted changes exist, warn user:
```
⚠️  Warning: You have uncommitted changes in train_door_control2:
  - Modified: docs/Software-Architecture-Specification.md
  - Untracked: docs/new-document.md

Recommendation: Commit changes before switching workspaces.

Continue anyway? (y/n)
```

### Workspace Discovery

Scan `examples/` directory for subdirectories containing `LIFECYCLE_STATE.md`. These are valid workspaces.

For each workspace:
1. Add workspace entry to `.workspace` index with path and timestamps
2. **DO NOT extract or cache status** (sil, phase, completion) in `.workspace`
3. Status will be read from LIFECYCLE_STATE.md on demand when displaying

**SSOT Enforcement**: `.workspace` is registry only, not a cache.

### Error Handling

- **Workspace not found**: "Error: Workspace 'xyz' not found. Available workspaces: [list]"
- **Invalid LIFECYCLE_STATE.md**: "Error: Workspace 'xyz' has invalid or missing LIFECYCLE_STATE.md. Run /cod plan to initialize."
- **Permission errors**: "Error: Cannot access workspace 'xyz'. Check permissions."

---

## Agent Behavior with Workspaces

### All Agents Use Active Workspace

Every agent (REQ, DES, IMP, TST, VER, VAL, INT, SAF, QUA, PM, CM, COD) should:

1. **Read active workspace** from `.workspace` on startup
2. **Operate on active workspace files**:
   - Read/write documents in `examples/<active_workspace>/docs/`
   - Read/write code in `examples/<active_workspace>/src/`
   - Update `examples/<active_workspace>/LIFECYCLE_STATE.md`
3. **Display workspace context** in responses:
   - "Working on: train_door_control2 (SIL 3, Phase 3)"

### Example: REQ Agent with Workspaces

```bash
/req
# Agent behavior:
# 1. Read .workspace to get active workspace = "train_door_control2"
# 2. Read examples/train_door_control2/docs/system/System-Requirements-Specification.md
# 3. Work on examples/train_door_control2/docs/Software-Requirements-Specification.md
# 4. Update examples/train_door_control2/LIFECYCLE_STATE.md
# 5. Display: "Requirements engineering for: train_door_control2 (SIL 3)"
```

---

## Skill Updates Required

### Update `en50128-project-management` Skill

**File**: `.opencode/skills/en50128-project-management/SKILL.md`

Add workspace awareness:

```markdown
## Workspace Management

The COD agent manages multiple project workspaces.

**Active Workspace**: Read from `.workspace` file
**Workspace Path**: `examples/<active_workspace>/`
**State File**: `examples/<active_workspace>/LIFECYCLE_STATE.md`

All COD operations (plan, gate-check, status) SHALL operate on the active workspace.
```

### Update All Agent Skills

Each agent skill should include:

```markdown
## Workspace Context

This agent operates on the **active workspace** defined in `.workspace`.

**Document Paths**: All document references are relative to `examples/<active_workspace>/docs/`
**Source Code**: All code references are relative to `examples/<active_workspace>/src/`
```

---

## Benefits

### 1. Multiple Projects
- Work on multiple railway projects simultaneously
- Each project has independent lifecycle state
- No confusion between projects

### 2. Resume Progress
- Switch between projects without losing context
- Lifecycle state persisted in LIFECYCLE_STATE.md
- Agent knows exactly where you left off

### 3. Clean Separation
- Each project has own directory structure
- No cross-contamination of documents or code
- Easy to archive completed projects

### 4. Scalability
- Platform supports unlimited number of projects
- Easy to create new projects with `/ws create`
- Standardized structure across all projects

---

## Future Enhancements

### 1. Workspace Templates
```bash
/ws create brake_controller --template door_control --sil 4
```
Copy structure and initial documents from existing project.

### 2. Workspace Comparison
```bash
/ws compare train_door_control train_door_control2
```
Show differences in requirements, architecture, progress.

### 3. Workspace Merge
```bash
/ws merge train_door_control train_door_control2 --output train_door_control_v3
```
Merge two projects (useful for incorporating lessons learned).

### 4. Workspace Snapshots
```bash
/ws snapshot train_door_control2 --tag "Phase2-Complete"
```
Create snapshot for rollback or comparison.

### 5. Cloud Sync
```bash
/ws sync train_door_control2 --remote https://git.example.com/projects/
```
Sync workspace to remote repository.

---

## References

- **LIFECYCLE.md**: Platform V-Model lifecycle documentation
- **AGENTS.md**: Agent roles and responsibilities
- **COD Agent**: `.opencode/commands/cod.md`

---

**Implementation Priority**: High  
**Required for**: Multi-project support, context switching  
**Dependencies**: COD agent, all agent skills  

---

**Note**: This command should be implemented as a platform feature accessible to all users working with multiple EN 50128 projects.
