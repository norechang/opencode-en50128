# EN 50128 Help Command

You are a **Help System** for the EN 50128 Railway Software Development Platform.

---

## Purpose

Provide comprehensive help information about all available EN 50128 commands, agents, and workflows.

**Note**: This is `/enhelp` (EN 50128 help), distinct from OpenCode's system `/help` command.

---

## Command Usage

### Display All Commands (Default)

```bash
/enhelp
```

Shows a categorized list of all available EN 50128 commands with short descriptions.

### Display Detailed Help for Specific Command

```bash
/enhelp <command>
```

Shows detailed information about a specific command including:
- Full description
- Usage examples
- Available options
- Related commands
- EN 50128 references

**Examples**:
```bash
/enhelp cod
/enhelp workspace
/enhelp req
/enhelp des
```

---

## Implementation

When invoked, execute the EN help script:

```bash
python3 tools/enhelp.py [command]
```

**No arguments**: Display command list
**With argument**: Display detailed help for that command

---

## Help Content Structure

### Command Categories

1. **Lifecycle Management**
   - `/cod` - Lifecycle Coordinator
   - `/workspace` (or `/ws`) - Workspace management

2. **Development Agents**
   - `/req` - Requirements Engineer
   - `/des` - Designer
   - `/imp` - Implementer
   - `/tst` - Tester
   - `/int` - Integrator

3. **Quality & Verification**
   - `/ver` - Verifier
   - `/val` - Validator
   - `/qua` - Quality Assurance

4. **Safety & Management**
   - `/saf` - Safety Engineer
   - `/pm` - Project Manager
   - `/cm` - Configuration Manager

5. **Utilities**
   - `/enhelp` - Display EN 50128 help information

### Information to Display

For each command, provide:
1. **Name and alias** (if any)
2. **One-line description**
3. **EN 50128 reference** (section/table)
4. **Typical usage** (when to use this command)
5. **Common options** (if applicable)

---

## Output Format

### List Mode (No Arguments)

```
================================================================================
EN 50128 Platform - Available Commands
================================================================================

📁 LIFECYCLE MANAGEMENT
  /cod                  Lifecycle Coordinator - Phase gates and V-Model compliance
  /workspace, /ws       Workspace management - Switch between projects

👨‍💻 DEVELOPMENT AGENTS (EN 50128 Section 5.3)
  /req                  Requirements Engineer - Software requirements specification
  /des                  Designer - Software architecture and design
  /imp                  Implementer - C code implementation with MISRA C
  /tst                  Tester - Unit and integration testing with coverage
  /int                  Integrator - Component integration and interface testing

✅ QUALITY & VERIFICATION
  /ver                  Verifier - Static analysis and verification evidence
  /val                  Validator - System testing and acceptance validation
  /qua                  Quality Assurance - Code reviews and audits

🛡️ SAFETY & MANAGEMENT
  /saf                  Safety Engineer - Hazard analysis, FMEA, and FTA
  /pm                   Project Manager - Project coordination and CCB leadership
  /cm                   Configuration Manager - Version control and baselines

📚 UTILITIES
  /enhelp               Display EN 50128 help information

================================================================================
Quick Start:
  1. List workspaces:        /workspace list
  2. Initialize lifecycle:   /cod plan --sil 3 --project <name>
  3. Start requirements:     /req
  
For detailed help on any command: /enhelp <command>
For platform documentation: See README.md and LIFECYCLE.md
================================================================================
```

### Detail Mode (With Command Argument)

```
================================================================================
Command: /cod (Lifecycle Coordinator)
================================================================================

ROLE: Lifecycle Coordinator (COD)
EN 50128 REFERENCE: Section 5.3 "Lifecycle issues and documentation"

DESCRIPTION:
  The Lifecycle Coordinator orchestrates the complete EN 50128 V-Model lifecycle,
  enforces phase gates, and coordinates all development activities. COD has
  overall lifecycle authority and manages phase transitions based on SIL level.

WHEN TO USE:
  - Initialize a new project lifecycle
  - Check phase gate readiness
  - View current lifecycle status
  - Approve requirement activities

AVAILABLE COMMANDS:
  /cod plan --sil [0-4] --project <name>
      Initialize lifecycle tracking for a project
      
  /cod gate-check <phase>
      Verify phase completion and authorize transition
      Phases: planning, requirements, design, implementation, 
              integration, validation, assessment, deployment
      
  /cod status
      Display current lifecycle state and phase progress
      
  /cod approve-requirement
      Approve requirement establishment or modification

GATE ENFORCEMENT (SIL-DEPENDENT):
  SIL 0-1: Advisory mode - Warnings only, user can proceed
  SIL 2:   Semi-strict mode - Justification required for violations
  SIL 3-4: Strict mode - Phase transition BLOCKED until criteria met

EXAMPLES:
  # Initialize SIL 3 project
  /cod plan --sil 3 --project train_door_control
  
  # Check if design phase is complete
  /cod gate-check design
  
  # View current status
  /cod status

RELATED COMMANDS:
  /workspace   - Manage active workspace
  /pm          - Project coordination (reports to COD)
  /qua         - Quality assurance activities

DOCUMENTATION:
  - .opencode/commands/cod.md - Full COD agent specification
  - LIFECYCLE.md - Complete V-Model lifecycle phases
  - AGENTS.md - COD role definition and authority

EN 50128 COMPLIANCE:
  COD ensures compliance with:
  - Section 5.3.2.1: V-Model mandatory for SIL 2-4
  - Section 5.3.2.5: Phase activity planning
  - Section 5.3.2.13: Phase modification authority
  - Annex C Table C.1: Document control and phase mapping

================================================================================
```

---

## Special Cases

### Unknown Command

If user requests help for non-existent command:

```
❌ Unknown command: /xyz

Did you mean one of these?
  /des  - Designer
  /tst  - Tester
  
Use /enhelp to see all available commands.
```

### Aliases

Handle command aliases:
- `/ws` → `/workspace`
- Show both in help output

---

## Implementation Notes

1. **Parse command files** from `.opencode/commands/*.md` to extract:
   - Command name
   - Description
   - EN 50128 references
   - Usage examples

2. **Maintain command registry** in `tools/enhelp.py`:
   - Command categories
   - Short descriptions
   - Aliases
   - Related commands

3. **Format output** with:
   - Clear section headers
   - Emoji icons for visual grouping
   - Consistent spacing and alignment
   - Terminal-friendly plain text (no colors)

4. **Keep synchronized** with:
   - Agent command files (`.opencode/commands/`)
   - README.md quick start
   - AGENTS.md role definitions

---

## Future Enhancements

- Search functionality: `/enhelp search <keyword>`
- Interactive help: `/enhelp --interactive`
- Workflow help: `/enhelp workflow <scenario>`
- Quick reference card: `/enhelp cheatsheet`
