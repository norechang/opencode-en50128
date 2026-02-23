#!/usr/bin/env python3
"""
EN 50128 Platform Help System

Provides comprehensive help information about all available commands and agents.

Usage:
    python3 enhelp.py              # List all commands
    python3 enhelp.py <command>    # Detailed help for specific command
"""

import sys
import os
import subprocess
from pathlib import Path
from io import StringIO

# Command registry with categories
COMMANDS = {
    "Lifecycle Management": {
        "cod": {
            "name": "/cod",
            "description": "Lifecycle Coordinator - Phase gates and V-Model compliance",
            "en50128_ref": "Section 5.3",
            "usage": "/cod [plan|gate-check|status|approve-requirement]",
            "file": ".opencode/commands/cod.md"
        },
        "workspace": {
            "name": "/workspace, /ws",
            "description": "Workspace management - Switch between projects",
            "en50128_ref": "Platform Extension",
            "usage": "/workspace [list|status|switch|create|archive]",
            "aliases": ["ws"],
            "file": ".opencode/commands/workspace.md"
        }
    },
    "Development Agents (EN 50128 Section 5.3)": {
        "req": {
            "name": "/req",
            "description": "Requirements Engineer - Software requirements specification",
            "en50128_ref": "Section 7.2, Table A.2",
            "usage": "/req",
            "file": ".opencode/commands/req.md"
        },
        "des": {
            "name": "/des",
            "description": "Designer - Software architecture and design",
            "en50128_ref": "Section 7.3, Table A.3",
            "usage": "/des",
            "file": ".opencode/commands/des.md"
        },
        "imp": {
            "name": "/imp",
            "description": "Implementer - C code implementation with MISRA C",
            "en50128_ref": "Section 7.4, Table A.4",
            "usage": "/imp",
            "file": ".opencode/commands/imp.md"
        },
        "tst": {
            "name": "/tst",
            "description": "Tester - Unit and integration testing with coverage",
            "en50128_ref": "Sections 7.4-7.5, Table A.5",
            "usage": "/tst",
            "file": ".opencode/commands/tst.md"
        },
        "int": {
            "name": "/int",
            "description": "Integrator - Component integration and interface testing",
            "en50128_ref": "Section 7.6, Table A.6",
            "usage": "/int",
            "file": ".opencode/commands/int.md"
        }
    },
    "Quality & Verification": {
        "ver": {
            "name": "/ver",
            "description": "Verifier - Static analysis and verification evidence",
            "en50128_ref": "Section 6.2, Table A.5",
            "usage": "/ver",
            "file": ".opencode/commands/ver.md"
        },
        "val": {
            "name": "/val",
            "description": "Validator - System testing and acceptance validation",
            "en50128_ref": "Section 7.7, Table A.7",
            "usage": "/val",
            "file": ".opencode/commands/val.md"
        },
        "qua": {
            "name": "/qua",
            "description": "Quality Assurance - Code reviews and audits",
            "en50128_ref": "Section 6.5, Table A.9",
            "usage": "/qua",
            "file": ".opencode/commands/qua.md"
        }
    },
    "Safety & Management": {
        "saf": {
            "name": "/saf",
            "description": "Safety Engineer - Hazard analysis, FMEA, and FTA",
            "en50128_ref": "Section 7.1, EN 50126",
            "usage": "/saf",
            "file": ".opencode/commands/saf.md"
        },
        "pm": {
            "name": "/pm",
            "description": "Project Manager - Project coordination and CCB leadership",
            "en50128_ref": "Section 5, Table B.9",
            "usage": "/pm",
            "file": ".opencode/commands/pm.md"
        },
        "cm": {
            "name": "/cm",
            "description": "Configuration Manager - Version control and baselines",
            "en50128_ref": "Section 6.6, Table A.9",
            "usage": "/cm",
            "file": ".opencode/commands/cm.md"
        }
    },
    "Utilities": {
        "enhelp": {
            "name": "/enhelp",
            "description": "Display EN 50128 help information",
            "en50128_ref": "N/A",
            "usage": "/enhelp [command]",
            "file": ".opencode/commands/enhelp.md"
        }
    }
}

# Category icons
CATEGORY_ICONS = {
    "Lifecycle Management": "📁",
    "Development Agents (EN 50128 Section 5.3)": "👨‍💻",
    "Quality & Verification": "✅",
    "Safety & Management": "🛡️",
    "Utilities": "📚"
}


def print_separator(char="=", length=80):
    """Print a separator line."""
    print(char * length)


def print_all_commands():
    """Display list of all available commands grouped by category."""
    print_separator()
    print("EN 50128 Platform - Available Commands")
    print_separator()
    print()
    
    for category, commands in COMMANDS.items():
        icon = CATEGORY_ICONS.get(category, "")
        print(f"{icon} {category.upper()}")
        
        for cmd_key, cmd_info in commands.items():
            name = cmd_info["name"]
            desc = cmd_info["description"]
            print(f"  {name:20s}  {desc}")
        
        print()
    
    print_separator()
    print("Quick Start:")
    print("  1. List workspaces:        /workspace list")
    print("  2. Initialize lifecycle:   /cod plan --sil 3 --project <name>")
    print("  3. Start requirements:     /req")
    print()
    print("For detailed help on any command: /enhelp <command>")
    print("For platform documentation: See README.md and LIFECYCLE.md")
    print_separator()
    print()
    print("Navigation: Use ↑↓ arrows or PgUp/PgDn to scroll • Press 'q' to quit • Press 'h' for help")
    print()


def find_command(cmd_name):
    """Find command by name or alias."""
    # Remove leading slash if present
    cmd_name = cmd_name.lstrip('/')
    
    # Search in all categories
    for category, commands in COMMANDS.items():
        for cmd_key, cmd_info in commands.items():
            # Check main name
            if cmd_key == cmd_name:
                return cmd_key, cmd_info
            
            # Check aliases
            if "aliases" in cmd_info and cmd_name in cmd_info["aliases"]:
                return cmd_key, cmd_info
    
    return None, None


def get_command_examples(cmd_key):
    """Get usage examples for specific commands."""
    examples = {
        "cod": [
            "# Initialize SIL 3 project",
            "/cod plan --sil 3 --project train_door_control",
            "",
            "# Check if design phase is complete",
            "/cod gate-check design",
            "",
            "# View current status",
            "/cod status"
        ],
        "workspace": [
            "# List all workspaces",
            "/workspace list",
            "# or",
            "/ws list",
            "",
            "# Switch to different workspace",
            "/workspace switch train_door_control2",
            "",
            "# Check current workspace",
            "/ws status",
            "",
            "# Create new workspace",
            "/ws create brake_controller --sil 4"
        ],
        "req": [
            "# Start requirements engineering",
            "/req",
            "",
            "# COD will request approval for requirement activities",
            "# Define requirements, assign SIL levels, establish traceability"
        ],
        "des": [
            "# Start architecture and design",
            "/des",
            "",
            "# Create Software Architecture Specification (SAS)",
            "# Create Software Design Specification (SDS)",
            "# Ensure cyclomatic complexity ≤ 10 (SIL 3-4)"
        ],
        "imp": [
            "# Start implementation",
            "/imp",
            "",
            "# Implement C code with MISRA C:2012 compliance",
            "# Static allocation only (SIL 2+)",
            "# Defensive programming patterns"
        ],
        "tst": [
            "# Start testing",
            "/tst",
            "",
            "# Execute unit tests",
            "# Measure coverage (100% MC/DC for SIL 3-4)",
            "# Generate test reports"
        ],
        "int": [
            "# Start integration",
            "/int",
            "",
            "# Integrate components",
            "# Execute integration tests",
            "# Verify interfaces"
        ],
        "ver": [
            "# Start verification",
            "/ver",
            "",
            "# Run static analysis (PC-lint, Cppcheck)",
            "# Verify MISRA C compliance",
            "# Check coverage and complexity",
            "# Collect verification evidence"
        ],
        "val": [
            "# Start validation",
            "/val",
            "",
            "# Execute system tests on target",
            "# Validate operational scenarios",
            "# Conduct acceptance testing"
        ],
        "qua": [
            "# Start quality assurance",
            "/qua",
            "",
            "# Perform code review",
            "# Verify MISRA C compliance",
            "# Check complexity limits",
            "# Generate QA reports"
        ],
        "saf": [
            "# Start safety analysis",
            "/saf",
            "",
            "# Identify hazards",
            "# Perform FMEA analysis",
            "# Create FTA for critical hazards",
            "# Develop safety case"
        ],
        "pm": [
            "# Project management activities",
            "/pm",
            "",
            "# Coordinate project activities",
            "# Lead Change Control Board",
            "# Manage project risks",
            "# Report to COD for lifecycle decisions"
        ],
        "cm": [
            "# Configuration management",
            "/cm",
            "",
            "# Establish baselines",
            "# Process change requests",
            "# Maintain traceability",
            "# Conduct configuration audits"
        ],
        "enhelp": [
            "# Display all EN 50128 commands",
            "/enhelp",
            "",
            "# Get help for specific command",
            "/enhelp cod",
            "/enhelp workspace",
            "/enhelp req"
        ]
    }
    
    return examples.get(cmd_key, ["# No examples available"])


def get_related_commands(cmd_key):
    """Get related commands for a given command."""
    relations = {
        "cod": ["workspace", "pm", "qua"],
        "workspace": ["cod"],
        "req": ["cod", "des", "saf"],
        "des": ["req", "imp", "int"],
        "imp": ["des", "tst", "qua"],
        "tst": ["imp", "int", "ver"],
        "int": ["tst", "des", "val"],
        "ver": ["tst", "qua", "val"],
        "val": ["int", "ver", "cod"],
        "qua": ["imp", "ver", "cod"],
        "saf": ["req", "des", "qua"],
        "pm": ["cod", "cm"],
        "cm": ["pm", "qua"],
        "enhelp": []
    }
    
    return relations.get(cmd_key, [])


def get_gate_enforcement_info(cmd_key):
    """Get SIL-dependent gate enforcement information."""
    if cmd_key == "cod":
        return [
            "GATE ENFORCEMENT (SIL-DEPENDENT):",
            "  SIL 0-1: Advisory mode - Warnings only, user can proceed",
            "  SIL 2:   Semi-strict mode - Justification required for violations",
            "  SIL 3-4: Strict mode - Phase transition BLOCKED until criteria met"
        ]
    return None


def print_command_detail(cmd_key, cmd_info):
    """Display detailed information about a specific command."""
    print_separator()
    print(f"Command: {cmd_info['name']}")
    print_separator()
    print()
    
    # Role and reference
    role_name = {
        "cod": "Lifecycle Coordinator (COD)",
        "workspace": "Workspace Manager",
        "req": "Requirements Engineer (REQ)",
        "des": "Designer (DES)",
        "imp": "Implementer (IMP)",
        "tst": "Tester (TST)",
        "int": "Integrator (INT)",
        "ver": "Verifier (VER)",
        "val": "Validator (VAL)",
        "qua": "Quality Assurance (QUA)",
        "saf": "Safety Engineer (SAF)",
        "pm": "Project Manager (PM)",
        "cm": "Configuration Manager (CM)",
        "enhelp": "EN 50128 Help System"
    }.get(cmd_key, cmd_key.upper())
    
    print(f"ROLE: {role_name}")
    print(f"EN 50128 REFERENCE: {cmd_info['en50128_ref']}")
    print()
    
    # Description
    print("DESCRIPTION:")
    desc_text = get_detailed_description(cmd_key)
    for line in desc_text:
        print(f"  {line}")
    print()
    
    # When to use
    print("WHEN TO USE:")
    when_text = get_when_to_use(cmd_key)
    for line in when_text:
        print(f"  {line}")
    print()
    
    # Usage
    print("USAGE:")
    print(f"  {cmd_info['usage']}")
    print()
    
    # Gate enforcement (for COD)
    gate_info = get_gate_enforcement_info(cmd_key)
    if gate_info:
        print()
        for line in gate_info:
            print(line)
        print()
    
    # Examples
    print("EXAMPLES:")
    examples = get_command_examples(cmd_key)
    for line in examples:
        print(f"  {line}")
    print()
    
    # Related commands
    related = get_related_commands(cmd_key)
    if related:
        print("RELATED COMMANDS:")
        for rel_cmd in related:
            rel_info = find_command(rel_cmd)[1]
            if rel_info:
                print(f"  {rel_info['name']:15s} - {rel_info['description']}")
        print()
    
    # Documentation
    print("DOCUMENTATION:")
    print(f"  - {cmd_info['file']} - Full command specification")
    if cmd_key in ["cod", "req", "des", "imp", "tst", "int", "ver", "val", "qua", "saf", "pm", "cm"]:
        print(f"  - AGENTS.md - Role definition and EN 50128 mapping")
    if cmd_key == "cod":
        print(f"  - LIFECYCLE.md - Complete V-Model lifecycle phases")
    if cmd_key == "workspace":
        print(f"  - README.md - Workspace management section")
    print()
    
    print_separator()
    print()
    print("Navigation: Use ↑↓ arrows or PgUp/PgDn to scroll • Press 'q' to quit • Press 'h' for help")
    print()


def get_detailed_description(cmd_key):
    """Get detailed description for a command."""
    descriptions = {
        "cod": [
            "The Lifecycle Coordinator orchestrates the complete EN 50128 V-Model lifecycle,",
            "enforces phase gates, and coordinates all development activities. COD has",
            "overall lifecycle authority and manages phase transitions based on SIL level."
        ],
        "workspace": [
            "The workspace manager allows you to work on multiple EN 50128 projects",
            "concurrently. Each workspace has independent lifecycle state, documentation,",
            "and source code. Switch between workspaces to pause/resume different projects."
        ],
        "req": [
            "The Requirements Engineer develops Software Requirements Specification (SRS)",
            "according to EN 50128 Section 7.2. Creates unambiguous, testable requirements",
            "with full traceability to system requirements and SIL level assignment."
        ],
        "des": [
            "The Designer creates Software Architecture and Design Specifications per",
            "EN 50128 Section 7.3. Ensures modular design, complexity limits, defensive",
            "programming, and MISRA C compliance (SIL 2+)."
        ],
        "imp": [
            "The Implementer writes C code according to EN 50128 Section 7.4 with",
            "MISRA C:2012 compliance. Uses static allocation only (SIL 2+), defensive",
            "programming, and maintains cyclomatic complexity within limits."
        ],
        "tst": [
            "The Tester develops and executes unit and integration tests per EN 50128",
            "Sections 7.4-7.5. Measures coverage (statement, branch, MC/DC) and ensures",
            "100% coverage for SIL 3-4 projects."
        ],
        "int": [
            "The Integrator performs component integration per EN 50128 Section 7.6.",
            "Conducts integration testing, interface testing, and verifies component",
            "interactions according to Software Architecture Specification."
        ],
        "ver": [
            "The Verifier conducts independent verification per EN 50128 Section 6.2.",
            "Performs static analysis, MISRA C checking, coverage verification, and",
            "collects verification evidence for all lifecycle phases."
        ],
        "val": [
            "The Validator performs independent validation per EN 50128 Section 7.7.",
            "Conducts system testing on target hardware, validates operational scenarios,",
            "and obtains customer acceptance (independence mandatory for SIL 3-4)."
        ],
        "qua": [
            "Quality Assurance performs code reviews, audits, and quality checks per",
            "EN 50128 Section 6.5. Verifies MISRA C compliance, complexity limits,",
            "and document template compliance throughout the lifecycle."
        ],
        "saf": [
            "The Safety Engineer performs hazard analysis per EN 50128 Section 7.1 and",
            "EN 50126. Conducts FMEA, FTA, determines SIL levels, and develops safety",
            "case with safety requirements and integrity measures."
        ],
        "pm": [
            "The Project Manager coordinates project activities per EN 50128 Section 5",
            "and Table B.9. Manages resources, schedules, risks, and leads Change Control",
            "Board. Reports to COD for lifecycle decisions."
        ],
        "cm": [
            "The Configuration Manager maintains configuration control per EN 50128",
            "Section 6.6. Manages baselines, change requests, traceability, and conducts",
            "configuration audits (mandatory for ALL SIL levels)."
        ],
        "enhelp": [
            "The EN 50128 help system provides information about all available EN 50128",
            "commands and agents. Use without arguments for command list, or specify",
            "a command name for detailed help with EN 50128 standard references."
        ]
    }
    
    return descriptions.get(cmd_key, ["No detailed description available"])


def get_when_to_use(cmd_key):
    """Get 'when to use' guidance for a command."""
    when_to_use = {
        "cod": [
            "- Initialize a new project lifecycle",
            "- Check phase gate readiness",
            "- View current lifecycle status",
            "- Approve requirement activities",
            "- Authorize phase transitions"
        ],
        "workspace": [
            "- Switch between multiple projects",
            "- View all available workspaces",
            "- Create a new project workspace",
            "- Check current workspace status",
            "- Archive completed projects"
        ],
        "req": [
            "- Define software requirements from system requirements",
            "- Establish requirements traceability",
            "- Assign SIL levels to requirements",
            "- Update or modify requirements (with COD approval)"
        ],
        "des": [
            "- Create software architecture",
            "- Design module interfaces",
            "- Define component structure",
            "- Ensure design meets complexity and safety constraints"
        ],
        "imp": [
            "- Implement C code from design",
            "- Write unit tests",
            "- Ensure MISRA C compliance",
            "- Apply defensive programming patterns"
        ],
        "tst": [
            "- Execute unit tests",
            "- Execute integration tests",
            "- Measure test coverage",
            "- Perform fault injection testing (SIL 3-4)"
        ],
        "int": [
            "- Integrate software components",
            "- Test component interfaces",
            "- Verify component interactions",
            "- Conduct performance testing"
        ],
        "ver": [
            "- Perform static analysis",
            "- Verify MISRA C compliance",
            "- Check coverage and complexity metrics",
            "- Collect verification evidence for gate checks"
        ],
        "val": [
            "- Conduct system-level testing",
            "- Validate against user requirements",
            "- Test on target hardware",
            "- Obtain customer acceptance"
        ],
        "qua": [
            "- Perform code reviews",
            "- Conduct quality audits",
            "- Verify document template compliance",
            "- Check process compliance"
        ],
        "saf": [
            "- Identify system hazards",
            "- Perform FMEA analysis",
            "- Create fault tree analysis (FTA)",
            "- Develop safety case",
            "- Define safety requirements"
        ],
        "pm": [
            "- Coordinate project activities",
            "- Manage project schedule and resources",
            "- Lead Change Control Board meetings",
            "- Manage project risks and issues"
        ],
        "cm": [
            "- Establish configuration baselines",
            "- Process change requests",
            "- Maintain traceability matrices",
            "- Conduct configuration audits (PCA, FCA)"
        ],
        "enhelp": [
            "- Learn about available EN 50128 commands",
            "- Get detailed command information with EN 50128 references",
            "- Find related commands",
            "- Understand command usage and examples"
        ]
    }
    
    return when_to_use.get(cmd_key, ["- See command documentation for usage information"])


def suggest_similar_commands(cmd_name):
    """Suggest similar commands if exact match not found."""
    suggestions = []
    
    for category, commands in COMMANDS.items():
        for cmd_key, cmd_info in commands.items():
            # Check if cmd_name is substring of cmd_key or vice versa
            if cmd_name.lower() in cmd_key.lower() or cmd_key.lower() in cmd_name.lower():
                suggestions.append((cmd_key, cmd_info))
            # Check description for matches
            elif cmd_name.lower() in cmd_info["description"].lower():
                suggestions.append((cmd_key, cmd_info))
    
    return suggestions[:5]  # Return top 5 suggestions


def display_with_pager(content):
    """
    Display content using a pager (less) for scrollable output.
    User can press 'q' to quit, similar to OpenCode's /help dialog.
    
    Falls back to direct print if:
    - Not in interactive terminal
    - Pager not available
    - Content is very short
    """
    # Check if we're in an interactive terminal
    if not sys.stdout.isatty():
        print(content)
        return
    
    # For short content (< 40 lines), just print directly
    line_count = content.count('\n')
    if line_count < 40:
        print(content)
        return
    
    # Try to use less as pager (most Unix-like systems)
    pager_commands = [
        ['less', '-R', '-X', '-F'],  # -R: raw colors, -X: no clear screen, -F: quit if one screen
        ['more'],  # Fallback to more
    ]
    
    for pager_cmd in pager_commands:
        try:
            # Check if pager exists
            if subprocess.run(['which', pager_cmd[0]], 
                            stdout=subprocess.DEVNULL, 
                            stderr=subprocess.DEVNULL).returncode != 0:
                continue
            
            # Open pager process
            pager = subprocess.Popen(
                pager_cmd,
                stdin=subprocess.PIPE,
                stdout=sys.stdout,
                stderr=sys.stderr
            )
            
            # Send content to pager
            try:
                pager.stdin.write(content.encode('utf-8'))
                pager.stdin.close()
                pager.wait()
                return
            except (BrokenPipeError, IOError):
                # User quit pager early
                return
                
        except (FileNotFoundError, PermissionError):
            continue
    
    # Fallback: just print if no pager available
    print(content)
    print("\n(Tip: Install 'less' for better scrolling experience - press 'q' to quit)")


def main():
    """Main entry point."""
    # Capture output in a string buffer
    output = StringIO()
    original_stdout = sys.stdout
    sys.stdout = output
    
    try:
        if len(sys.argv) == 1:
            # No arguments - show all commands
            print_all_commands()
        else:
            # Show detailed help for specific command
            cmd_name = sys.argv[1]
            cmd_key, cmd_info = find_command(cmd_name)
            
            if cmd_info:
                print_command_detail(cmd_key, cmd_info)
            else:
                # Command not found
                print(f"❌ Unknown command: /{cmd_name}")
                print()
                
                # Suggest similar commands
                suggestions = suggest_similar_commands(cmd_name)
                if suggestions:
                    print("Did you mean one of these?")
                    for cmd_key, cmd_info in suggestions:
                        print(f"  {cmd_info['name']:15s} - {cmd_info['description']}")
                    print()
                
                print("Use /enhelp to see all available commands.")
    finally:
        # Restore stdout
        sys.stdout = original_stdout
    
    # Display captured output through pager
    content = output.getvalue()
    display_with_pager(content)


if __name__ == "__main__":
    main()
