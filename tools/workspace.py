#!/usr/bin/env python3
"""
EN 50128 Workspace Manager

Manages multiple project workspaces for EN 50128 railway software development.
Allows switching between projects, resuming progress, and maintaining workspace state.

Usage:
    workspace.py list                           # List all workspaces
    workspace.py status                         # Show current workspace status
    workspace.py switch <project_name>          # Switch to different workspace
    workspace.py create <project_name> --sil <level>  # Create new workspace
    workspace.py archive <project_name>         # Archive completed workspace
"""

import json
import os
import sys
import subprocess
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Optional

# Platform root directory
PLATFORM_ROOT = Path("/home/norechang/work/EN50128")
EXAMPLES_DIR = PLATFORM_ROOT / "examples"
WORKSPACE_FILE = PLATFORM_ROOT / ".workspace"
ARCHIVED_DIR = EXAMPLES_DIR / "archived"


class WorkspaceManager:
    """Manages EN 50128 project workspaces."""

    def __init__(self):
        self.workspace_data = self._load_workspace_data()

    def _load_workspace_data(self) -> Dict:
        """Load workspace data from .workspace file, or create if not exists."""
        if WORKSPACE_FILE.exists():
            with open(WORKSPACE_FILE, 'r') as f:
                return json.load(f)
        else:
            # Create new workspace data by scanning examples/
            data = self._discover_workspaces()
            self._save_workspace_data(data)
            return data

    def _save_workspace_data(self, data: Dict):
        """Save workspace data to .workspace file."""
        with open(WORKSPACE_FILE, 'w') as f:
            json.dump(data, f, indent=2)

    def _discover_workspaces(self) -> Dict:
        """Discover workspaces by scanning examples/ directory."""
        workspaces = {}
        active_workspace = None

        if not EXAMPLES_DIR.exists():
            EXAMPLES_DIR.mkdir(parents=True)

        for project_dir in EXAMPLES_DIR.iterdir():
            if not project_dir.is_dir() or project_dir.name.startswith('.'):
                continue
            if project_dir.name == "archived":
                continue

            lifecycle_state = project_dir / "LIFECYCLE_STATE.md"
            if not lifecycle_state.exists():
                continue  # Not a valid workspace

            # Parse LIFECYCLE_STATE.md to extract info
            workspace_info = self._parse_lifecycle_state(lifecycle_state)
            if workspace_info:
                workspaces[project_dir.name] = {
                    "path": str(project_dir.relative_to(PLATFORM_ROOT)),
                    "sil": workspace_info.get("sil", 0),
                    "current_phase": workspace_info.get("current_phase", "Unknown"),
                    "completion": workspace_info.get("completion", 0),
                    "last_accessed": datetime.now().isoformat(),
                    "status": "active"
                }
                if active_workspace is None:
                    active_workspace = project_dir.name

        return {
            "active_workspace": active_workspace,
            "workspaces": workspaces
        }

    def _parse_lifecycle_state(self, filepath: Path) -> Optional[Dict]:
        """Parse LIFECYCLE_STATE.md to extract project info."""
        try:
            with open(filepath, 'r') as f:
                content = f.read()

            info = {}
            
            # Extract SIL level
            for line in content.split('\n'):
                if '| **SIL Level**' in line or '| **System SIL Level**' in line:
                    parts = line.split('|')
                    if len(parts) >= 3:
                        sil_str = parts[2].strip()
                        try:
                            info['sil'] = int(sil_str)
                        except ValueError:
                            info['sil'] = 3  # Default

                # Extract current phase
                if '| **Current Phase**' in line:
                    parts = line.split('|')
                    if len(parts) >= 3:
                        phase_str = parts[2].strip()
                        info['current_phase'] = phase_str

                # Extract completion
                if '| **Completion**' in line:
                    parts = line.split('|')
                    if len(parts) >= 3:
                        completion_str = parts[2].strip()
                        # Extract percentage
                        if '%' in completion_str:
                            try:
                                pct = int(completion_str.split('%')[0].strip().split()[-1])
                                info['completion'] = pct
                            except ValueError:
                                info['completion'] = 0

            return info if info else None

        except Exception as e:
            print(f"Warning: Could not parse {filepath}: {e}")
            return None

    def list_workspaces(self):
        """List all available workspaces."""
        workspaces = self.workspace_data.get('workspaces', {})
        active = self.workspace_data.get('active_workspace')

        if not workspaces:
            print("No workspaces found.")
            print(f"\nCreate a new workspace: workspace.py create <project_name> --sil <0-4>")
            return

        print("=" * 80)
        print("EN 50128 Project Workspaces")
        print("=" * 80)
        print()

        # Sort by last_accessed (most recent first)
        sorted_workspaces = sorted(
            workspaces.items(),
            key=lambda x: x[1].get('last_accessed', ''),
            reverse=True
        )

        for name, info in sorted_workspaces:
            is_active = (name == active)
            marker = " * " if is_active else "   "
            
            sil = info.get('sil', 'N/A')
            phase = info.get('current_phase', 'Unknown')
            completion = info.get('completion', 0)
            status = info.get('status', 'active')

            print(f"{marker}{name:<30} SIL {sil} | {phase:<30} | {completion:3}% | {status}")

        print()
        print(f"Active workspace: {active}")
        print()
        print("Commands:")
        print("  workspace.py switch <project_name>  - Switch to a different workspace")
        print("  workspace.py status                 - Show current workspace details")
        print("  workspace.py create <name> --sil <level> - Create new workspace")
        print()

    def show_status(self):
        """Show current workspace status."""
        active = self.workspace_data.get('active_workspace')
        workspaces = self.workspace_data.get('workspaces', {})

        if not active or active not in workspaces:
            print("Error: No active workspace.")
            print("Run: workspace.py list")
            return

        info = workspaces[active]
        project_path = PLATFORM_ROOT / info['path']
        lifecycle_state = project_path / "LIFECYCLE_STATE.md"

        print("=" * 80)
        print("Current Workspace Status")
        print("=" * 80)
        print()
        print(f"Project Name:     {active}")
        print(f"SIL Level:        {info.get('sil', 'N/A')}")
        print(f"Current Phase:    {info.get('current_phase', 'Unknown')}")
        print(f"Completion:       {info.get('completion', 0)}%")
        print(f"Status:           {info.get('status', 'active')}")
        print(f"Path:             {project_path}")
        print()

        # Read recent activity from LIFECYCLE_STATE.md
        if lifecycle_state.exists():
            print("Recent Activity:")
            self._show_recent_activity(lifecycle_state)
        
        print()
        print("Next Steps:")
        self._show_next_steps(info)
        print()

    def _show_recent_activity(self, lifecycle_state: Path):
        """Extract and show recent activity from LIFECYCLE_STATE.md."""
        try:
            with open(lifecycle_state, 'r') as f:
                content = f.read()
            
            # Look for Phase History section
            if "## Phase History" in content:
                lines = content.split("## Phase History")[1].split('\n')
                in_table = False
                row_count = 0
                for line in lines:
                    if '|' in line and '---' in line:
                        in_table = True
                        continue
                    if in_table and '|' in line:
                        if row_count < 3:  # Show last 3 phases
                            print(f"  {line.strip()}")
                            row_count += 1
                        if row_count >= 3:
                            break
        except Exception as e:
            print(f"  (Could not read activity: {e})")

    def _show_next_steps(self, info: Dict):
        """Show recommended next steps based on current phase."""
        phase = info.get('current_phase', '').lower()
        
        if 'planning' in phase or 'initialization' in phase:
            print("  1. Complete planning documents (SQAP, SCMP, SVP, SVaP)")
            print("  2. Run: /cod gate-check planning")
        elif 'requirements' in phase:
            print("  1. Complete Software Requirements Specification")
            print("  2. Update Requirements Traceability Matrix")
            print("  3. Run: /cod gate-check requirements")
        elif 'architecture' in phase or 'design' in phase:
            print("  1. Complete Software Architecture Specification")
            print("  2. Complete Software Design Specification")
            print("  3. Run: /cod gate-check architecture-design")
        elif 'implementation' in phase:
            print("  1. Implement source code")
            print("  2. Run unit tests")
            print("  3. Run: /cod gate-check implementation")
        elif 'integration' in phase:
            print("  1. Run integration tests")
            print("  2. Review integration test results")
            print("  3. Run: /cod gate-check integration")
        elif 'validation' in phase:
            print("  1. Run validation tests")
            print("  2. Prepare for independent assessment")
            print("  3. Run: /cod gate-check validation")
        else:
            print("  Run: /cod status (for detailed lifecycle state)")

    def switch_workspace(self, target_name: str):
        """Switch to a different workspace."""
        workspaces = self.workspace_data.get('workspaces', {})
        current_active = self.workspace_data.get('active_workspace')

        if target_name not in workspaces:
            print(f"Error: Workspace '{target_name}' not found.")
            print("\nAvailable workspaces:")
            for name in workspaces.keys():
                print(f"  - {name}")
            return False

        if target_name == current_active:
            print(f"Already in workspace: {target_name}")
            return True

        print(f"Switching workspace from '{current_active}' to '{target_name}'...")
        print()

        # Update last_accessed for current workspace
        if current_active and current_active in workspaces:
            workspaces[current_active]['last_accessed'] = datetime.now().isoformat()
            current_info = workspaces[current_active]
            print(f"Saved {current_active} state (Phase: {current_info.get('current_phase', 'Unknown')}, {current_info.get('completion', 0)}%)")

        # Set new active workspace
        self.workspace_data['active_workspace'] = target_name
        workspaces[target_name]['last_accessed'] = datetime.now().isoformat()
        self._save_workspace_data(self.workspace_data)

        print(f"Loading {target_name} workspace...")
        print()

        # Display new workspace summary
        target_info = workspaces[target_name]
        print("✅ Workspace switched to:", target_name)
        print()
        print(f"SIL Level:        {target_info.get('sil', 'N/A')}")
        print(f"Current Phase:    {target_info.get('current_phase', 'Unknown')}")
        print(f"Completion:       {target_info.get('completion', 0)}%")
        print()
        print("Next Steps:")
        self._show_next_steps(target_info)
        print()
        print("Available commands:")
        print("  /cod status           - View detailed lifecycle state")
        print("  workspace.py status   - Show workspace status")
        print()

        return True

    def create_workspace(self, project_name: str, sil: int):
        """Create a new workspace."""
        workspaces = self.workspace_data.get('workspaces', {})

        if project_name in workspaces:
            print(f"Error: Workspace '{project_name}' already exists.")
            return False

        if not (0 <= sil <= 4):
            print(f"Error: SIL level must be 0-4 (got {sil}).")
            return False

        project_path = EXAMPLES_DIR / project_name
        if project_path.exists():
            print(f"Error: Directory {project_path} already exists.")
            return False

        print(f"Creating new workspace: {project_name} (SIL {sil})...")

        # Create directory structure
        project_path.mkdir(parents=True)
        (project_path / "docs").mkdir()
        (project_path / "docs" / "system").mkdir()
        (project_path / "docs" / "plans").mkdir()
        (project_path / "docs" / "config").mkdir()
        (project_path / "docs" / "reports").mkdir()
        (project_path / "docs" / "test").mkdir()
        (project_path / "src").mkdir()
        (project_path / "test").mkdir()
        (project_path / "build").mkdir()

        print(f"  Created directory structure: {project_path}")

        # Create initial LIFECYCLE_STATE.md
        self._create_initial_lifecycle_state(project_path, project_name, sil)

        print(f"  Created LIFECYCLE_STATE.md")

        # Create README.md
        self._create_readme(project_path, project_name, sil)
        print(f"  Created README.md")

        # Add to workspace data
        workspaces[project_name] = {
            "path": str(project_path.relative_to(PLATFORM_ROOT)),
            "sil": sil,
            "current_phase": "Initialization (Phase 0)",
            "completion": 0,
            "last_accessed": datetime.now().isoformat(),
            "status": "active"
        }
        self.workspace_data['workspaces'] = workspaces
        self._save_workspace_data(self.workspace_data)

        print()
        print(f"✅ Workspace '{project_name}' created successfully!")
        print()
        print("Next steps:")
        print(f"  1. Switch to workspace: workspace.py switch {project_name}")
        print(f"  2. Initialize lifecycle: /cod plan --sil {sil} --project {project_name}")
        print()

        return True

    def _create_initial_lifecycle_state(self, project_path: Path, project_name: str, sil: int):
        """Create initial LIFECYCLE_STATE.md for new workspace."""
        content = f"""# Project Lifecycle State

**DO NOT edit this file manually - managed by Lifecycle Coordinator (COD)**

---

## Project Information

| Property | Value |
|----------|-------|
| **Project Name** | {project_name} |
| **SIL Level** | {sil} |
| **Lifecycle Model** | V-Model |
| **COD Mode** | {"Strict Gatekeeper" if sil >= 3 else "Semi-strict" if sil == 2 else "Advisory"} |
| **Created** | {datetime.now().strftime('%Y-%m-%d')} |
| **Last Updated** | {datetime.now().strftime('%Y-%m-%d %H:%M:%S')} UTC |

---

## Current Status

| Property | Value |
|----------|-------|
| **Current Phase** | Initialization (Phase 0) |
| **Phase Started** | {datetime.now().strftime('%Y-%m-%d')} |
| **Days in Phase** | 0 |
| **Completion** | 0% |
| **Status** | New Project - Ready for Planning |

---

## Phase History

| Phase | Status | Started | Completed | Gate Passed | Notes |
|-------|--------|---------|-----------|-------------|-------|
| 0. Initialization | In Progress | {datetime.now().strftime('%Y-%m-%d')} | - | - | Project created |

---

## Next Steps

1. Run `/cod plan --sil {sil} --project {project_name}` to initialize lifecycle
2. Create planning documents (SQAP, SCMP, SVP, SVaP)
3. Review EN 50128 requirements for SIL {sil}

---

**For detailed lifecycle documentation, see**: `../../LIFECYCLE.md`
"""
        with open(project_path / "LIFECYCLE_STATE.md", 'w') as f:
            f.write(content)

    def _create_readme(self, project_path: Path, project_name: str, sil: int):
        """Create README.md for new workspace."""
        content = f"""# {project_name}

**EN 50128 Railway Software Project**

---

## Project Information

- **Project Name**: {project_name}
- **SIL Level**: {sil}
- **Standard**: EN 50128:2011
- **Lifecycle Model**: V-Model
- **Created**: {datetime.now().strftime('%Y-%m-%d')}

---

## Project Status

**Current Phase**: Initialization  
**Completion**: 0%

See `LIFECYCLE_STATE.md` for detailed lifecycle state.

---

## Directory Structure

```
{project_name}/
├── LIFECYCLE_STATE.md          # Phase tracking (managed by COD)
├── README.md                    # This file
├── Makefile                     # Build system (TBD)
├── docs/
│   ├── system/                  # System-level input documents
│   ├── plans/                   # SQAP, SCMP, SVP, SVaP
│   ├── config/                  # Configuration items
│   ├── reports/                 # Verification reports
│   └── test/                    # Test specifications
├── src/                         # Source code
├── test/                        # Test code
└── build/                       # Build artifacts
```

---

## Getting Started

### 1. Initialize Lifecycle

```bash
/cod plan --sil {sil} --project {project_name}
```

### 2. Create Planning Documents

```bash
/pm create-plans
```

### 3. Define Requirements

```bash
/req
```

---

## EN 50128 Compliance

This project follows EN 50128:2011 SIL {sil} requirements.

**Key Requirements for SIL {sil}**:
{self._get_sil_requirements(sil)}

---

## References

- **Platform Documentation**: `../../LIFECYCLE.md`, `../../AGENTS.md`
- **EN 50128 Standard**: `../../std/EN50128-2011.md`
- **Phase Definitions**: `../../.opencode/skills/en50128-project-management/phase-definitions/`

---

**Last Updated**: {datetime.now().strftime('%Y-%m-%d')}
"""
        with open(project_path / "README.md", 'w') as f:
            f.write(content)

    def _get_sil_requirements(self, sil: int) -> str:
        """Get key requirements summary for SIL level."""
        if sil == 0:
            return """- No specific safety requirements
- Standard software development practices"""
        elif sil == 1:
            return """- Structured development process
- Basic testing and verification
- Code reviews recommended"""
        elif sil == 2:
            return """- MISRA C:2012 compliance mandatory
- 100% statement + branch coverage
- Static memory allocation only
- Code reviews mandatory"""
        elif sil == 3:
            return """- MISRA C:2012 compliance mandatory (zero mandatory violations)
- 100% statement, branch, and MC/DC coverage
- Static memory allocation only (no malloc/free)
- Cyclomatic complexity ≤ 10
- Independent verification required
- Code reviews mandatory"""
        elif sil == 4:
            return """- MISRA C:2012 compliance mandatory (zero violations)
- 100% statement, branch, and MC/DC coverage
- Formal methods highly recommended
- Static memory allocation only
- Cyclomatic complexity ≤ 10
- Independent verification and validation required
- Diverse programming recommended
- Code reviews mandatory"""
        else:
            return "- Unknown SIL level"

    def archive_workspace(self, project_name: str):
        """Archive a completed workspace."""
        workspaces = self.workspace_data.get('workspaces', {})
        active = self.workspace_data.get('active_workspace')

        if project_name not in workspaces:
            print(f"Error: Workspace '{project_name}' not found.")
            return False

        if project_name == active:
            print(f"Error: Cannot archive active workspace '{project_name}'.")
            print("Switch to another workspace first: workspace.py switch <other_project>")
            return False

        print(f"Archiving workspace: {project_name}...")

        # Create archived directory if not exists
        if not ARCHIVED_DIR.exists():
            ARCHIVED_DIR.mkdir()

        # Move project directory
        project_path = PLATFORM_ROOT / workspaces[project_name]['path']
        archive_path = ARCHIVED_DIR / project_name

        if archive_path.exists():
            print(f"Error: Archive destination {archive_path} already exists.")
            return False

        project_path.rename(archive_path)
        print(f"  Moved {project_path} -> {archive_path}")

        # Update workspace data
        workspaces[project_name]['status'] = 'archived'
        workspaces[project_name]['path'] = str(archive_path.relative_to(PLATFORM_ROOT))
        workspaces[project_name]['archived_date'] = datetime.now().isoformat()
        self._save_workspace_data(self.workspace_data)

        print()
        print(f"✅ Workspace '{project_name}' archived successfully!")
        print(f"Location: {archive_path}")
        print()

        return True


def main():
    """Main entry point."""
    manager = WorkspaceManager()

    if len(sys.argv) < 2:
        print("Usage: workspace.py <command> [options]")
        print()
        print("Commands:")
        print("  list                              - List all workspaces")
        print("  status                            - Show current workspace status")
        print("  switch <project_name>             - Switch to different workspace")
        print("  create <project_name> --sil <0-4> - Create new workspace")
        print("  archive <project_name>            - Archive completed workspace")
        print()
        print("Examples:")
        print("  workspace.py list")
        print("  workspace.py switch train_door_control")
        print("  workspace.py create brake_controller --sil 4")
        sys.exit(1)

    command = sys.argv[1]

    if command == "list":
        manager.list_workspaces()
    elif command == "status":
        manager.show_status()
    elif command == "switch" or command == "resume":
        if len(sys.argv) < 3:
            print("Error: Missing project name.")
            print("Usage: workspace.py switch <project_name>")
            sys.exit(1)
        project_name = sys.argv[2]
        manager.switch_workspace(project_name)
    elif command == "create":
        if len(sys.argv) < 5 or sys.argv[3] != "--sil":
            print("Error: Invalid arguments.")
            print("Usage: workspace.py create <project_name> --sil <0-4>")
            sys.exit(1)
        project_name = sys.argv[2]
        try:
            sil = int(sys.argv[4])
        except ValueError:
            print(f"Error: SIL level must be an integer (0-4).")
            sys.exit(1)
        manager.create_workspace(project_name, sil)
    elif command == "archive":
        if len(sys.argv) < 3:
            print("Error: Missing project name.")
            print("Usage: workspace.py archive <project_name>")
            sys.exit(1)
        project_name = sys.argv[2]
        manager.archive_workspace(project_name)
    else:
        print(f"Error: Unknown command '{command}'.")
        print("Run 'workspace.py' for usage.")
        sys.exit(1)


if __name__ == "__main__":
    main()
