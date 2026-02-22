# Workspace Awareness (Common Section for All Agents)

## Workspace Context

**CRITICAL**: Before executing any command, you MUST:

1. **Read the active workspace** from `.workspace` file at platform root
2. **Operate on the active workspace** for all file operations
3. **Display workspace context** in your responses

### Reading Active Workspace

**File Location**: `/home/norechang/work/EN50128/.workspace` (JSON format)

**Example Content**:
```json
{
  "active_workspace": "train_door_control2",
  "workspaces": {
    "train_door_control2": {
      "path": "examples/train_door_control2",
      "sil": 3,
      "current_phase": "Architecture & Design (Phase 3)",
      "completion": 30,
      "last_accessed": "2026-02-21T10:00:00",
      "status": "active"
    },
    "train_door_control": {
      "path": "examples/train_door_control",
      "sil": 3,
      "current_phase": "Phase 4 - Implementation & Testing",
      "completion": 85,
      "last_accessed": "2026-02-20T15:30:00",
      "status": "active"
    }
  }
}
```

### File Path Resolution

**IMPORTANT**: All paths are relative to the active workspace directory.

**Pattern**:
```
<WORKSPACE_ROOT> = examples/<active_workspace>/

LIFECYCLE_STATE.md     → <WORKSPACE_ROOT>/LIFECYCLE_STATE.md
docs/                  → <WORKSPACE_ROOT>/docs/
src/                   → <WORKSPACE_ROOT>/src/
test/                  → <WORKSPACE_ROOT>/test/
```

**Examples**:
- If active_workspace = `"train_door_control2"`:
  - Software Requirements Specification → `examples/train_door_control2/docs/Software-Requirements-Specification.md`
  - LIFECYCLE_STATE.md → `examples/train_door_control2/LIFECYCLE_STATE.md`
  - Source code → `examples/train_door_control2/src/`

- If active_workspace = `"train_door_control"`:
  - Software Requirements Specification → `examples/train_door_control/docs/Software-Requirements-Specification.md`
  - LIFECYCLE_STATE.md → `examples/train_door_control/LIFECYCLE_STATE.md`
  - Source code → `examples/train_door_control/src/`

### Displaying Workspace Context

**Always show workspace context at the start of your response**:

```
📁 Active Workspace: train_door_control2 (SIL 3)
   Path: examples/train_door_control2/
   Phase: Architecture & Design (Phase 3) | Completion: 30%
```

### Workspace Commands

If user wants to switch workspaces or view workspace information, delegate to workspace manager:

- `/workspace list` or `/ws list` - List all workspaces
- `/workspace status` or `/ws status` - Show current workspace details  
- `/workspace switch <project>` or `/ws switch <project>` - Switch to different workspace
- `/workspace create <name> --sil <level>` or `/ws create <name> --sil <level>` - Create new workspace

**Example Usage**:
```bash
# User wants to switch workspace
User: "Switch to train_door_control"
Agent: "I'll switch the workspace for you."
Agent: [Execute: python3 tools/workspace.py switch train_door_control]
Agent: "✅ Switched to train_door_control workspace (SIL 3, Phase 4)"
```

### Multi-Project Support

The platform supports multiple concurrent projects:
- Each project in `examples/` directory is an independent workspace
- Each workspace has its own LIFECYCLE_STATE.md tracking phase progress
- Workspace switching preserves context for each project
- You can resume work on any project by switching to its workspace

### Implementation Steps

**For every agent invocation**:

1. **Read `.workspace` file**:
   ```python
   import json
   
   with open('.workspace', 'r') as f:
       workspace_data = json.load(f)
   
   active_workspace = workspace_data['active_workspace']
   workspace_info = workspace_data['workspaces'][active_workspace]
   workspace_path = workspace_info['path']  # e.g., "examples/train_door_control2"
   ```

2. **Construct file paths**:
   ```python
   lifecycle_state = f"{workspace_path}/LIFECYCLE_STATE.md"
   docs_dir = f"{workspace_path}/docs/"
   srs_path = f"{workspace_path}/docs/Software-Requirements-Specification.md"
   ```

3. **Display workspace context**:
   ```
   📁 Active Workspace: {active_workspace} (SIL {workspace_info['sil']})
      Path: {workspace_path}/
      Phase: {workspace_info['current_phase']} | Completion: {workspace_info['completion']}%
   ```

4. **Operate on workspace files**:
   - Read/write documents in workspace path
   - Reference LIFECYCLE_STATE.md from workspace
   - Create artifacts in workspace directories

---

## Example Agent Workflow with Workspace Awareness

### Example 1: Requirements Engineer (/req)

```
User: "/req"

Agent Response:
---
📁 Active Workspace: train_door_control2 (SIL 3)
   Path: examples/train_door_control2/
   Phase: Requirements (Phase 2) | Completion: 50%

Requirements Engineer Agent (REQ) - EN 50128 Section 7.2

I'll help you work on software requirements for train_door_control2.

Reading workspace files:
- LIFECYCLE_STATE.md: examples/train_door_control2/LIFECYCLE_STATE.md
- Software Requirements Specification: examples/train_door_control2/docs/Software-Requirements-Specification.md
- Requirements Traceability Matrix: examples/train_door_control2/docs/Requirements-Traceability-Matrix.md

Current Status:
- 45 requirements defined (SWR-001 to SWR-045)
- Traceability: 38/45 requirements traced to system requirements (84%)
- 7 requirements need traceability links

What would you like to do?
1. Add new requirements
2. Update existing requirements
3. Complete traceability links
4. Review requirements for completeness
---
```

### Example 2: Designer (/des)

```
User: "/des"

Agent Response:
---
📁 Active Workspace: train_door_control (SIL 3)
   Path: examples/train_door_control/
   Phase: Architecture & Design (Phase 3) | Completion: 75%

Designer Agent (DES) - EN 50128 Section 7.3

I'll help you work on software architecture and design for train_door_control.

Reading workspace files:
- Software Architecture Specification: examples/train_door_control/docs/Software-Architecture-Specification.md
- Software Design Specification: examples/train_door_control/docs/Software-Design-Specification.md

Current Status:
- Architecture: 8 modules defined, 12 interfaces specified
- Design: 18 components designed (cyclomatic complexity: avg 6.2, max 9)
- Pending: Software Interface Specifications document

What would you like to do?
1. Complete Software Interface Specifications
2. Review architecture for modularity
3. Verify complexity constraints (SIL 3: max 10)
4. Perform design review
---
```

---

**This section should be included in every agent command file to ensure consistent workspace awareness across all agents.**
