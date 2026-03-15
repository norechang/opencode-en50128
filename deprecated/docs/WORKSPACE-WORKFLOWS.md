# Workspace Management Workflows and Best Practices

## Overview

This document provides practical workflows and best practices for managing multiple EN 50128 projects using the workspace management system.

---

## Table of Contents

1. [Basic Workspace Operations](#basic-workspace-operations)
2. [Multi-Project Development Workflows](#multi-project-development-workflows)
3. [Best Practices](#best-practices)
4. [Common Scenarios](#common-scenarios)
5. [Troubleshooting](#troubleshooting)

---

## Basic Workspace Operations

### Checking Current Workspace

**Always check which workspace is active before starting work:**

```bash
# Check active workspace status
/workspace status
# or
/ws status
```

**Output:**
```
================================================================================
Current Workspace Status
================================================================================

Project Name:     train_door_control2
SIL Level:        3
Current Phase:    Architecture & Design (Phase 3)
Completion:       30%
Status:           active
Path:             /home/norechang/work/EN50128/examples/train_door_control2

Recent Activity:
  - Software Architecture Specification: 75% complete

Next Steps:
  1. Complete Software Architecture Specification
  2. Complete Software Design Specification
  3. Run: /cod gate-check architecture-design
```

### Listing All Workspaces

```bash
# List all available workspaces
/workspace list
# or
/ws list
```

**Output:**
```
================================================================================
EN 50128 Project Workspaces
================================================================================

 * train_door_control2            SIL 3 | Architecture & Design (Phase 3) |  30% | active
   train_door_control             SIL 3 | Implementation & Testing (Phase 4) |  85% | active
   brake_controller               SIL 4 | Requirements (Phase 2) |  15% | active

Active workspace: train_door_control2

Commands:
  workspace.py switch <project_name>  - Switch to a different workspace
  workspace.py status                 - Show current workspace details
  workspace.py create <name> --sil <level> - Create new workspace
```

### Switching Workspaces

```bash
# Switch to a different project
/workspace switch <project_name>
# or
/ws switch <project_name>
```

**Example:**
```bash
$ /ws switch train_door_control

Switching workspace from 'train_door_control2' to 'train_door_control'...

Saved train_door_control2 state (Phase: Architecture & Design (Phase 3), 30%)
Loading train_door_control workspace...

✅ Workspace switched to: train_door_control

SIL Level:        3
Current Phase:    Implementation & Testing (Phase 4)
Completion:       85%

Next Steps:
  1. Complete unit testing
  2. Run integration tests
  3. Run: /cod gate-check implementation
```

### Creating New Workspaces

```bash
# Create a new workspace
/workspace create <project_name> --sil <level>
# or
/ws create <project_name> --sil <level>
```

**Example:**
```bash
$ /ws create brake_controller --sil 4

Creating new workspace: brake_controller (SIL 4)...

✅ Workspace created successfully!

Project Name:     brake_controller
SIL Level:        4
Path:             /home/norechang/work/EN50128/examples/brake_controller

Next Steps:
  1. Run: /cod plan --sil 4 --project brake_controller
  2. Begin requirements phase: /req
  3. Switch to this workspace: /ws switch brake_controller
```

---

## Multi-Project Development Workflows

### Workflow 1: Parallel Development on Multiple Projects

**Scenario**: You're working on two projects simultaneously - a train door control system (SIL 3) and a brake controller (SIL 4).

#### Morning: Work on Train Door Control (Design Phase)

```bash
# Start of day - check active workspace
$ /ws status
📁 Active Workspace: brake_controller (SIL 4)

# Switch to train door control
$ /ws switch train_door_control
✅ Workspace switched to: train_door_control (SIL 3)
   Phase: Architecture & Design (Phase 3) | 60%

# Work on design
$ /des
📁 Active Workspace: train_door_control (SIL 3)
   Path: examples/train_door_control/
   Phase: Architecture & Design (Phase 3) | Completion: 60%

Designer Agent (DES) - Working on Software Architecture Specification...
# ... complete design work ...

# Check phase status
$ /cod status
Phase 3 - Architecture & Design: 75% complete
```

#### Afternoon: Switch to Brake Controller (Requirements Phase)

```bash
# Switch workspaces
$ /ws switch brake_controller
✅ Workspace switched to: brake_controller (SIL 4)
   Phase: Requirements (Phase 2) | 40%

# Work on requirements
$ /req
📁 Active Workspace: brake_controller (SIL 4)
   Path: examples/brake_controller/
   Phase: Requirements (Phase 2) | Completion: 40%

Requirements Engineer (REQ) - Working on Software Requirements Specification...
# ... complete requirements work ...
```

#### End of Day: Context Preserved

```bash
# Both projects maintain independent state:
$ /ws list

 * brake_controller               SIL 4 | Requirements (Phase 2) |  55% | active
   train_door_control             SIL 3 | Architecture & Design (Phase 3) |  75% | active

# Next day, resume exactly where you left off
```

---

### Workflow 2: Maintenance on Production System While Developing New Feature

**Scenario**: Production system needs urgent bugfix while new feature is in development.

#### Urgent Bugfix Required

```bash
# Currently working on new feature development
$ /ws status
📁 Active Workspace: train_door_control_v2 (SIL 3)
   Phase: Implementation & Testing (Phase 4) | 45%

# Production issue reported - switch to production codebase
$ /ws switch train_door_control_prod
✅ Workspace switched to: train_door_control_prod (SIL 3)
   Phase: Deployment (Phase 8) | 100% (in maintenance)

# Analyze the issue
$ /saf
# Identify safety impact of bug...

# Implement fix
$ /imp
# Fix the defect in C code...

# Test the fix
$ /tst
# Run unit tests and regression tests...

# Verify fix
$ /ver
# Run static analysis, verify no regressions...

# Change management
$ /cm
# Create change request, update baseline...

# Return to feature development
$ /ws switch train_door_control_v2
✅ Workspace switched to: train_door_control_v2
   (Feature development continues at 45%)
```

---

### Workflow 3: Reference Implementation While Developing New Project

**Scenario**: Using completed project as reference for new project development.

```bash
# Working on new project
$ /ws status
📁 Active Workspace: passenger_info_system (SIL 2)
   Phase: Architecture & Design (Phase 3) | 20%

# Need to reference train door control architecture
$ /ws switch train_door_control
✅ Workspace switched to: train_door_control (SIL 3)
   Phase: Deployment (Phase 8) | 100%

# Read the architecture specification
# Read Software-Architecture-Specification.md
# Study modular design patterns...

# Copy architecture patterns (adapt to SIL 2 requirements)

# Switch back to continue work
$ /ws switch passenger_info_system
✅ Workspace switched to: passenger_info_system
   (Continue architecture design with learned patterns)

$ /des
# Apply learned patterns to new design...
```

---

## Best Practices

### 1. Always Check Active Workspace Before Starting Work

**WHY**: Prevents working on wrong project, ensures correct context.

```bash
# Good practice - check first
$ /ws status
📁 Active Workspace: train_door_control2 (SIL 3)

$ /des
# Work proceeds on correct project...
```

```bash
# Bad practice - assume workspace
$ /des
# Might be working on wrong project!
```

### 2. Use Short Alias `/ws` for Frequent Operations

**WHY**: Saves typing, improves workflow efficiency.

```bash
# Recommended for frequent use
/ws status
/ws list
/ws switch brake_controller

# Full command also available
/workspace status
/workspace list
/workspace switch brake_controller
```

### 3. Descriptive Project Names

**WHY**: Makes workspace switching easier, reduces confusion.

```bash
# Good: Descriptive, clear purpose
train_door_control
brake_controller_v2
passenger_info_system_upgrade

# Avoid: Vague, ambiguous
project1
test
temp_project
```

### 4. Create Separate Workspaces for Major Versions

**WHY**: Maintains production code while developing next version.

```bash
# Production version
train_door_control_v1_prod    # SIL 3, deployed, maintenance mode

# Development version
train_door_control_v2_dev     # SIL 3, Phase 4 - Implementation

# Feature branches (if needed)
train_door_control_v2_feature_emergency_release  # SIL 3, Phase 3 - Design
```

### 5. Regular Status Checks During Long Sessions

**WHY**: Confirms you're on correct workspace, tracks progress.

```bash
# Every 30-60 minutes during long development session
$ /ws status
📁 Active Workspace: train_door_control (SIL 3)
   Phase: Implementation & Testing (Phase 4) | 72%

# Confirm still working on intended project
```

### 6. Document Workspace Purpose in Project README

**WHY**: Helps team members understand project status and purpose.

**Example** (`examples/train_door_control/README.md`):
```markdown
# Train Door Control System (SIL 3)

**Workspace**: `train_door_control`
**Status**: Production (v1.0.0)
**Phase**: Deployment (Phase 8) - 100% complete
**Purpose**: Deployed production system for train door control

**Maintenance Mode**: Only critical bugfixes and safety updates
```

### 7. Archive Completed or Inactive Workspaces

**WHY**: Keeps workspace list manageable, focuses on active projects.

```bash
# Archive completed project
$ /ws archive train_door_control_old
✅ Workspace archived: train_door_control_old
   Files preserved in: examples/train_door_control_old/
   Workspace removed from active list
```

---

## Common Scenarios

### Scenario 1: "Which project am I working on?"

**Solution**:
```bash
$ /ws status
📁 Active Workspace: train_door_control2 (SIL 3)
   Path: examples/train_door_control2/
   Phase: Architecture & Design (Phase 3) | Completion: 30%
```

### Scenario 2: "I need to quickly switch between two projects"

**Solution**: Use short alias and tab completion
```bash
# Check list
$ /ws list

# Switch with short command
$ /ws switch train_door_control
$ /ws switch brake_controller
$ /ws switch train_door_control
```

### Scenario 3: "I forgot which phase each project is in"

**Solution**: Use list command
```bash
$ /ws list

 * train_door_control2            SIL 3 | Architecture & Design (Phase 3) |  30% | active
   train_door_control             SIL 3 | Implementation & Testing (Phase 4) |  85% | active
   brake_controller               SIL 4 | Requirements (Phase 2) |  15% | active
```

### Scenario 4: "I want to compare two projects side-by-side"

**Solution**: Switch between them and use file system tools
```bash
# Method 1: Switch and read
$ /ws switch project1
# Read Software-Architecture-Specification.md...

$ /ws switch project2
# Read Software-Architecture-Specification.md...

# Method 2: Use file system directly (both projects accessible)
$ diff examples/train_door_control/docs/Software-Architecture-Specification.md \
       examples/train_door_control2/docs/Software-Architecture-Specification.md
```

### Scenario 5: "I want to start a new project based on existing one"

**Solution**: Create new workspace, copy reference files
```bash
# Create new workspace
$ /ws create passenger_door_control --sil 3
✅ Workspace created: passenger_door_control

# Copy reference files from completed project
$ cp -r examples/train_door_control/docs/plans/ \
       examples/passenger_door_control/docs/plans/

# Switch to new workspace and adapt
$ /ws switch passenger_door_control
$ /cod plan --sil 3 --project passenger_door_control
$ /req  # Begin requirements (adapt from reference)
```

---

## Troubleshooting

### Problem: "Agent is working on wrong project"

**Cause**: Workspace not switched before invoking agent

**Solution**:
```bash
# Check active workspace
$ /ws status
📁 Active Workspace: wrong_project (SIL 3)

# Switch to correct workspace
$ /ws switch correct_project
✅ Workspace switched to: correct_project

# Now invoke agent (will work on correct project)
$ /des
📁 Active Workspace: correct_project (SIL 3)
   # Correct workspace context displayed
```

### Problem: "Cannot find LIFECYCLE_STATE.md"

**Cause**: Project not initialized with COD

**Solution**:
```bash
# Check if LIFECYCLE_STATE.md exists
$ ls examples/my_project/LIFECYCLE_STATE.md
ls: cannot access 'examples/my_project/LIFECYCLE_STATE.md': No such file or directory

# Initialize project with COD
$ /ws switch my_project
$ /cod plan --sil 3 --project my_project
✓ Lifecycle plan initialized
✓ Created: examples/my_project/LIFECYCLE_STATE.md
```

### Problem: "Workspace list is cluttered with old projects"

**Cause**: Too many archived or completed projects in examples/

**Solution**: Archive inactive projects
```bash
# Archive old projects
$ /ws archive old_project_1
$ /ws archive completed_project_2

# Or move manually
$ mv examples/old_project_archive ~/archive/en50128_projects/
```

### Problem: ".workspace file is corrupted"

**Cause**: Manual editing or filesystem error

**Solution**: Regenerate workspace state
```bash
# Backup corrupted file
$ cp .workspace .workspace.backup

# Regenerate by switching to valid project
$ /ws switch train_door_control
✅ Workspace file regenerated

# Check all projects detected
$ /ws list
```

### Problem: "Workspace shows wrong phase completion"

**Cause**: LIFECYCLE_STATE.md out of sync with actual work

**Solution**: Update lifecycle state with COD
```bash
$ /ws switch my_project
$ /cod status
# Review current phase status

# If incorrect, manually update LIFECYCLE_STATE.md
# Or use COD commands to update deliverable status
$ /cod pm-update-deliverables --phase requirements \
      --deliverable Software-Requirements-Specification \
      --file docs/Software-Requirements-Specification.md \
      --status complete
```

---

## Workspace State File Reference

The `.workspace` file (JSON) at platform root tracks all workspace metadata:

```json
{
  "active_workspace": "train_door_control2",
  "workspaces": {
    "train_door_control2": {
      "path": "examples/train_door_control2",
      "sil": 3,
      "current_phase": "Architecture & Design (Phase 3)",
      "completion": 30,
      "last_accessed": "2026-02-21T15:00:00",
      "status": "active"
    },
    "train_door_control": {
      "path": "examples/train_door_control",
      "sil": 3,
      "current_phase": "Implementation & Testing (Phase 4)",
      "completion": 85,
      "last_accessed": "2026-02-21T14:00:00",
      "status": "active"
    }
  }
}
```

**Fields**:
- `active_workspace`: Currently active project name
- `workspaces`: Dictionary of all discovered projects
  - `path`: Relative path from platform root
  - `sil`: Safety Integrity Level (0-4)
  - `current_phase`: Current lifecycle phase description
  - `completion`: Phase completion percentage (0-100)
  - `last_accessed`: ISO 8601 timestamp
  - `status`: Workspace status (active, archived, etc.)

---

## Advanced Tips

### Tip 1: Create Workspace Aliases in Shell

Add to your `.bashrc` or `.zshrc`:
```bash
alias ws='/workspace'
alias wss='/workspace status'
alias wsl='/workspace list'
alias wsw='/workspace switch'
```

Usage:
```bash
$ wss        # workspace status
$ wsl        # workspace list
$ wsw train_door_control  # workspace switch
```

### Tip 2: Use Git Branches with Workspaces

Each workspace can have its own Git branch:
```bash
$ /ws switch train_door_control_v2
$ cd examples/train_door_control_v2
$ git checkout -b feature/emergency-release

# Work on feature...

$ /ws switch train_door_control_prod
$ cd examples/train_door_control_prod
$ git checkout main  # Production branch
```

### Tip 3: Scripted Workspace Switching

Create shell function for context-aware switching:
```bash
# In .bashrc or .zshrc
switch_en50128_workspace() {
    /workspace switch "$1"
    cd "examples/$1"
    /cod status
}

alias wsc=switch_en50128_workspace
```

Usage:
```bash
$ wsc train_door_control
# Switches workspace, changes directory, shows COD status
```

---

## Summary

**Key Takeaways**:

1. **Always check active workspace** before starting work (`/ws status`)
2. **Use short alias** `/ws` for frequent operations
3. **Each workspace is independent** - phase progress, documentation, code
4. **Switching is instant** - context preserved for each project
5. **Agents automatically use active workspace** - no manual path configuration
6. **Best for parallel development** - multiple projects, feature branches, maintenance

**Most Common Commands**:
```bash
/ws status                      # What am I working on?
/ws list                        # Show all projects
/ws switch <project>            # Switch to different project
/ws create <name> --sil <level> # Create new project
```

**Workflow Pattern**:
```bash
1. /ws status                   # Check current workspace
2. /ws switch <target_project>  # Switch if needed
3. /<agent>                     # Work with agent (auto-uses active workspace)
4. /ws switch <next_project>    # Switch to next task
```

---

**For more information**:
- See `README.md` - Workspace Management section
- See `.opencode/commands/workspace.md` - Workspace command specification
- See `.opencode/commands/_workspace-awareness.md` - Agent implementation guide
