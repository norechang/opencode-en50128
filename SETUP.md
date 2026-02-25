# EN 50128 Platform Setup Guide

**For users who just cloned this repository**

This guide walks you through the initial setup required to start developing EN 50128-compliant railway software.

---

## Prerequisites

Before starting, ensure you have:

- **Git** installed
- **Python 3.8+** installed
- **sudo/root access** (for system tool installation)
- **OpenCode TUI** installed ([https://opencode.ai](https://opencode.ai))

---

## Quick Setup (3 Steps)

### Step 1: Clone Repository

```bash
git clone https://github.com/norechang/opencode-en50128.git
cd opencode-en50128
```

### Step 2: Install System Tools

Install development and analysis tools required for EN 50128 compliance:

```bash
# Check what tools are available
./install_tools.sh --list

# Install all recommended tools (RECOMMENDED)
./install_tools.sh

# OR install only MANDATORY SIL 3 tools (minimal)
./install_tools.sh --minimal

# Verify installation
./install_tools.sh --check
```

**What gets installed**:
- **MANDATORY (SIL 3)**: gcc, gcov, lcov, cppcheck, clang, git
- **Highly Recommended**: valgrind
- **Optional**: doxygen, splint, ctags

**Note**: This requires `sudo` privileges to install system packages.

### Step 3: Install Python Tools

Install Python packages in a virtual environment:

```bash
# Create venv and install packages
./install_python.sh

# Verify installation
source venv/bin/activate
./install_python.sh --check
```

**What gets installed**:
- **Core**: pymupdf4llm, pycparser, tabulate
- **MANDATORY (SIL 3)**: lizard (cyclomatic complexity analyzer)
- **Code Quality**: autopep8, pylint, flake8, mypy
- **Testing**: pytest, pytest-cov, coverage
- **Documentation**: markdown, jinja2

---

## Verification

After installation, verify everything is working:

```bash
# Check system tools
./install_tools.sh --check

# Check Python tools (requires venv active)
source venv/bin/activate
./install_python.sh --check

# Test custom tools
python3 tools/enhelp.py
python3 tools/workspace.py list
```

**Expected Output**: All MANDATORY tools should show ✅ (green checkmarks).

---

## Detailed Setup

### System Tools Installation Options

#### Option 1: Full Installation (Recommended)

Installs all tools including optional ones:

```bash
./install_tools.sh
```

**Installs**:
- Build tools: gcc, make, cmake
- Coverage: gcov, lcov
- Static analysis: cppcheck, clang, splint
- Memory analysis: valgrind
- Documentation: doxygen, graphviz
- Version control: git
- Navigation: ctags

#### Option 2: Minimal Installation (MANDATORY Only)

Installs only tools required for SIL 3 compliance:

```bash
./install_tools.sh --minimal
```

**Installs**:
- gcc, gcov, lcov
- cppcheck, clang
- git

#### Option 3: Check Status Only

Check what's already installed without installing anything:

```bash
./install_tools.sh --check
```

---

### Python Tools Installation Options

#### Option 1: Fresh Installation

Creates new virtual environment and installs all packages:

```bash
./install_python.sh
```

#### Option 2: Upgrade Existing

Upgrades packages in existing virtual environment:

```bash
./install_python.sh --upgrade
```

#### Option 3: Check Status

Verify installation without making changes:

```bash
source venv/bin/activate
./install_python.sh --check
```

---

## Platform Structure

After setup, your directory structure should look like:

```
opencode-en50128/
├── venv/                      # Python virtual environment (created by install_python.sh)
├── tools/                     # Custom EN 50128 tools
│   ├── mcdc/                  # MC/DC analyzer
│   ├── pdf-conversion/        # Standards conversion
│   ├── static-analysis/       # MISRA C checker
│   ├── enhelp.py             # Command help system
│   └── workspace.py          # Workspace manager
├── examples/                  # Your railway software projects go here
│   └── train_door_control2/  # Reference implementation
├── .opencode/                 # OpenCode agent definitions
│   ├── commands/             # Agent command files
│   └── skills/               # Domain-specific skills
├── std/                       # EN 50128 standards (Markdown)
├── docs/                      # Platform documentation
├── TOOLS.md                   # Comprehensive tool catalog
├── AGENTS.md                  # Agent role definitions
├── LIFECYCLE.md               # V-Model lifecycle phases
├── README.md                  # Platform overview
├── requirements.txt           # Python package dependencies
├── install_python.sh          # Python setup script
└── install_tools.sh           # System tools installer
```

---

## Next Steps

After successful setup:

### 1. Launch OpenCode TUI

```bash
opencode
```

### 2. Get Help

```bash
# List all available commands
/enhelp

# Get help for specific command
/enhelp cod        # Lifecycle Coordinator
/enhelp workspace  # Workspace management
/enhelp pm         # Project Manager
```

### 3. Explore Reference Implementation

```bash
# Switch to reference project
/workspace switch train_door_control2

# Check project status
/cod status
```

### 4. Create Your Own Project

```bash
# Create new SIL 3 project
mkdir -p examples/my_railway_project
cd examples/my_railway_project
/cod plan --sil 3 --project my_railway_project

# Start development
/pm execute-phase planning
```

---

## Tool Catalog Reference

For detailed information about each tool:

- **Tool capabilities and usage**: See [`TOOLS.md`](TOOLS.md)
- **Agent tool usage protocols**: See [`AGENTS.md`](AGENTS.md#agent-tool-usage-protocol)
- **EN 50128 compliance requirements**: See [`LIFECYCLE.md`](LIFECYCLE.md)

---

## Troubleshooting

### Issue: Python version too old

```bash
python3 --version  # Should be 3.8 or higher
```

**Solution**: Install Python 3.8+ from your package manager or [python.org](https://www.python.org/downloads/)

### Issue: python3-venv not found

**Ubuntu/Debian**:
```bash
sudo apt-get install python3-venv
```

**Fedora/RHEL**:
```bash
sudo dnf install python3-venv
```

### Issue: Tool not found (e.g., clang)

```bash
./install_tools.sh --check  # Identify missing tools
./install_tools.sh          # Re-run installer
```

### Issue: Virtual environment activation fails

```bash
# Remove and recreate venv
rm -rf venv/
./install_python.sh
```

### Issue: Permission denied (install_tools.sh)

The scripts need to be executable:

```bash
chmod +x install_tools.sh install_python.sh
```

### Issue: Sudo password required

`install_tools.sh` requires root privileges to install system packages. This is normal and expected.

---

## Platform Updates

To update the platform and tools:

```bash
# Update platform code
git pull origin main

# Update system tools
./install_tools.sh

# Update Python packages
source venv/bin/activate
./install_python.sh --upgrade
```

---

## Minimal Setup for CI/CD

For automated builds in CI/CD pipelines:

```bash
# Non-interactive installation
export DEBIAN_FRONTEND=noninteractive

# Install minimal tools
./install_tools.sh --minimal

# Install Python tools
./install_python.sh

# Activate venv in CI
source venv/bin/activate
```

---

## Platform Architecture

This is a **development platform**, not a project template:

- **Platform**: Located in repository root (agents, skills, standards, tools)
- **Projects**: Located in `examples/` directory (your railway software)
- **Virtual Environment**: `venv/` (created by `install_python.sh`, gitignored)

Each project in `examples/` has:
- Independent lifecycle tracking (`LIFECYCLE_STATE.md`)
- Own Makefile and build configuration
- Own documentation (`docs/` subdirectory)
- Own source code (`src/` subdirectory)

---

## Support and Documentation

- **Tool Catalog**: [`TOOLS.md`](TOOLS.md) - Complete tool reference
- **Agent Roles**: [`AGENTS.md`](AGENTS.md) - EN 50128 agent definitions
- **Lifecycle Phases**: [`LIFECYCLE.md`](LIFECYCLE.md) - V-Model workflow
- **Tutorial**: [`TUTORIAL.md`](TUTORIAL.md) - Step-by-step guide
- **Standards**: `std/EN50128-2011.md` - Full EN 50128 standard

---

## EN 50128 Compliance Notes

### Tool Confidence Levels (TCL)

Per EN 50128 Section 6.7, tools are classified:

- **T1**: No qualification required (output verified) - lizard, valgrind, Python tools
- **T2**: Validation required - cppcheck, clang, gcov, lcov, git
- **T3**: Full qualification required - gcc (compiler)

### SIL 3 MANDATORY Tools

Per EN 50128 Tables A.19, A.21:

- **Static Analysis** (Table A.19): cppcheck, clang
- **Complexity** (Table A.19): lizard (CCN ≤ 10)
- **Coverage** (Table A.21): gcov, lcov (100% stmt/branch/MC/DC)
- **Version Control** (Table A.9): git (ALL SIL levels)

### Coverage Requirements

| SIL | Statement | Branch | MC/DC |
|-----|-----------|--------|-------|
| 0-1 | HR | HR | - |
| 2 | HR | **M** | - |
| 3-4 | **M** | **M** | **M** |

**M** = Mandatory, **HR** = Highly Recommended

---

## License

See [`LICENSE`](LICENSE) file.

---

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for development guidelines.

---

**Last Updated**: 2026-02-25

For questions or issues, please open a GitHub issue.
