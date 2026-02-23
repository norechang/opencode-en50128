# EN 50128 Railway Software Development Platform

**AI-powered development platform for EN 50128:2011 compliant railway software**

---

## ⚠️ IMPORTANT: OpenCode TUI Required

**This platform MUST be used within the OpenCode TUI (Terminal User Interface) environment.**

- **Install OpenCode**: Visit [https://opencode.ai](https://opencode.ai) for installation instructions
- **Why Required**: This platform uses OpenCode's agent system, specialized skills, and command routing
- **Do NOT use**: Generic LLM interfaces (ChatGPT, Claude web interface, etc.) - they cannot invoke the specialized agents or access EN 50128 skills

**Quick Start**:
```bash
# Install OpenCode (if not already installed)
# Visit https://opencode.ai/docs/installation

# Clone this repository
git clone https://github.com/norechang/opencode-en50128.git
cd opencode-en50128

# Launch OpenCode TUI
opencode

# Start using EN 50128 agents
/enhelp
```

---

## Overview

This platform provides a complete EN 50128-compliant development environment using OpenCode:

- **13 specialized AI agents** for lifecycle management and compliance (Lifecycle Coordinator, Requirements, Design, Implementation, Testing, Verification, Validation, Safety, Quality, Integration, Project Management, Configuration Management, V&V Manager)
- **12 domain-specific skills** with patterns, templates, and best practices
- **Complete EN 50128 standards** in LLM-friendly Markdown format (2.7 MB)
- **V-Model lifecycle** implementation with SIL-dependent phase gate enforcement
- **Multi-workspace support** for concurrent project development
- **Production-ready workflows** for safety-critical railway software (SIL 0-4)

**Platform Architecture**: This is a development platform, not a project template. All actual railway software projects are developed in the `examples/` directory, each with independent lifecycle tracking.

## Quick Start

### 1. Getting Help

```bash
# List all available commands
/enhelp

# Get detailed help for specific commands
/enhelp cod        # Lifecycle Coordinator
/enhelp workspace  # Workspace management
/enhelp pm         # Project Manager (automation mode)
/enhelp req        # Requirements Engineer (manual mode)
```

### 2. Development Modes

The platform supports two approaches to EN 50128 development:

#### **Mode 1: PM Automation (Recommended for Most Users)**

Project Manager orchestrates the workflow, automatically coordinating agents:

```bash
# Create and initialize a new SIL 3 project
mkdir -p examples/my_railway_project
cd examples/my_railway_project
/cod plan --sil 3 --project my_railway_project

# PM executes complete phases with agent orchestration
/pm execute-phase planning        # PM → QUA, CM, VER, VAL agents
/pm execute-phase requirements    # PM → REQ, SAF, QUA, VER agents
/pm execute-phase design          # PM → DES, SAF, QUA, VER agents
/pm execute-phase implementation  # PM → IMP, TST, QUA, VER agents
/pm execute-phase integration     # PM → INT, QUA, VER agents
/pm execute-phase validation      # PM → VAL, QUA, VER agents
/pm execute-phase assessment      # PM coordinates independent assessment
/pm execute-phase deployment      # PM → Release packaging

# PM handles: agent sequencing, QA gates, verification coordination, COD gate checks
```

**Benefits**:
- ✅ Simplified workflow - single command per phase
- ✅ Automatic agent coordination and sequencing
- ✅ Built-in quality gates and verification checkpoints
- ✅ Ideal for users less familiar with EN 50128 details

#### **Mode 2: Manual Agent Invocation (Expert/Advanced Users)**

Directly invoke individual agents for fine-grained control:

```bash
# Create and initialize a new SIL 3 project
mkdir -p examples/my_railway_project
cd examples/my_railway_project
/cod plan --sil 3 --project my_railway_project

# Manually invoke each agent in sequence
/req                   # Requirements Engineer
/saf                   # Safety Analysis
/qua review-requirements
/ver verify-requirements
/cod gate-check requirements

/des                   # Designer
/saf fmea --phase design
/qua review-design
/ver verify-design
/cod gate-check design

/imp                   # Implementer
/tst                   # Tester
/qua review-code
/ver verify-module
/cod gate-check implementation

# Continue for integration, validation, etc.
```

**Benefits**:
- ✅ Maximum control over each step
- ✅ Flexibility to customize workflow
- ✅ Ideal for experts who understand EN 50128 lifecycle details
- ✅ Useful for iterating on specific activities

**Which Mode Should You Use?**
- **New to EN 50128?** → Use **PM Automation Mode**
- **Experienced with EN 50128?** → Either mode works; PM automation is faster
- **Need fine-grained control?** → Use **Manual Mode**
- **Following the tutorial?** → Tutorial demonstrates **Manual Mode** for educational purposes

### 3. EN 50128 Organizational Roles

The platform implements 13 specialized agents representing EN 50128-defined roles:

#### Core Development Roles (EN 50128 Section 5.3)

| Agent | Command | EN 50128 Role | Responsibilities | Independence (SIL 3-4) |
|-------|---------|---------------|------------------|----------------------|
| **Requirements Engineer** | `/req` | Requirements Manager (5.3.1) | Requirements specification, SIL assignment, traceability | No |
| **Designer** | `/des` | Designer (5.3.2) | Architecture & design, MISRA C patterns, complexity control | No |
| **Implementer** | `/imp` | Implementer (5.3.3) | C code implementation, unit tests, MISRA C compliance | No |
| **Tester** | `/tst` | Tester (5.3.4) | Unit/integration testing, coverage analysis (100% SIL 3-4) | No |
| **Integrator** | `/int` | Integrator (5.3.6) | Component integration, interface testing, performance testing | No |
| **Verifier** | `/ver` | Verifier (5.3.5) | Static analysis, verification evidence, compliance checking | **Yes** |
| **Validator** | `/val` | Validator (5.3.7) | System testing, acceptance validation, customer approval | **Yes** |
| **Safety Engineer** | `/saf` | (Implicit) | FMEA, FTA, hazard analysis, safety case development | No |

#### Management & Support Roles (EN 50128 Section 5, Annex B)

| Agent | Command | EN 50128 Role | Responsibilities | Independence (SIL 3-4) |
|-------|---------|---------------|------------------|----------------------|
| **Lifecycle Coordinator** | `/cod` | Platform Extension* | V-Model orchestration, phase gate enforcement, lifecycle compliance | No |
| **Project Manager** | `/pm` | Project Manager (Table B.9) | Team coordination, CCB leadership, resource management, risk management | No |
| **Configuration Manager** | `/cm` | Configuration Manager (Table B.10) | Version control, baselines, change control, traceability (mandatory all SILs) | No |
| **Quality Assurance** | `/qua` | (Implicit in 6.5) | Code reviews, audits, MISRA C checks, quality gates, template compliance | No |
| **V&V Manager** | `/vmgr` | Platform Extension** | Independent V&V authority, manages Verifier team, final V&V approval | **Yes** |

**Notes**:
- **Platform Extension\***: COD is not explicitly defined in EN 50128 but implements Section 5.3 lifecycle orchestration requirements
- **Platform Extension\*\***: VMGR formalizes EN 50128 Section 5.1.2.10e organizational structure ("Verifier can report to Validator")
- **Independence Requirements (SIL 3-4)**: VER, VAL, and VMGR MUST be independent from development team (REQ, DES, IMP, TST, INT)
- **Assessor Role**: Not implemented as agent (requires external independent safety assessor per EN 50128 5.3.8)

#### Organizational Authority Structure (SIL 3-4)

```
        Safety Authority / Customer
                |
        ┌───────┴───────────┐
        |                   |
    COD (Lifecycle)     VMGR (Independent V&V)
        |                   |
        |               ┌───┴───┐
        |           VER (Team) VAL
        |
    PM (Project Coordination)
        |
    ┌───┴────────────────────────┐
    |                            |
REQ, DES, IMP, TST, INT      QUA, CM, SAF
(Development Team)        (Support Functions)
```

**Key Authority Relationships**:
- **COD** has overall lifecycle authority, enforces phase gates
- **VMGR** is independent, provides V&V approval/rejection (cannot be overridden by COD or PM)
- **PM** coordinates development team, reports to COD for lifecycle decisions
- **VER/VAL** report to VMGR (SIL 3-4), ensuring independence from PM
- **QUA/CM/SAF** support both development and V&V activities

See [AGENTS.md](AGENTS.md) for complete role definitions and EN 50128 technique tables.

### 4. Reference Implementation

See `examples/train_door_control2/` for a complete SIL 3 implementation (Phase 5 complete).

**Note**: The reference implementation uses **Manual Mode** to demonstrate each agent's responsibilities. For production use, consider **PM Automation Mode** for streamlined workflow.

### 5. Multi-Project Workflow

The platform supports concurrent development on multiple projects:

```bash
/workspace status              # Check active project
/workspace list                # List all projects
/workspace switch project_name # Switch between projects
/workspace create new_project --sil 4  # Create new project
```

**Shortcuts**: Use `/ws` instead of `/workspace` for brevity.

Each workspace maintains independent:
- Phase progress and completion status
- Documentation in `docs/` directory
- Source code in `src/` directory
- Test code in `test/` directory

See [TUTORIAL.md](TUTORIAL.md) for detailed step-by-step walkthrough.

## Core Concepts

### SIL Levels

Safety Integrity Levels determine requirements stringency:

| SIL | Risk Level | Examples | Key Requirements |
|-----|------------|----------|------------------|
| 4 | Very High | Train control, ATP | 100% coverage, formal methods, independent V&V |
| 3 | High | Signaling, interlocking | 100% coverage, static analysis, independent V&V |
| 2 | Medium | Passenger info (safety impact) | Branch coverage, MISRA C |
| 1 | Low | Non-critical monitoring | Statement coverage |
| 0 | None | Administrative systems | Basic testing |

### Available Agents

Specialized AI agents accessible via slash commands (see [EN 50128 Organizational Roles](#3-en-50128-organizational-roles) for complete details):

| Command | Agent | Role |
|---------|-------|------|
| `/cod` | Lifecycle Coordinator | V-Model orchestration, phase gates, compliance enforcement |
| `/req` | Requirements Engineer | Requirements specification and traceability |
| `/des` | Designer | Software architecture and detailed design |
| `/imp` | Implementer | C code implementation with MISRA C compliance |
| `/tst` | Tester | Unit and integration testing with coverage |
| `/int` | Integrator | Component integration and interface testing |
| `/ver` | Verifier | Static analysis and verification evidence (independent SIL 3-4) |
| `/val` | Validator | System testing and acceptance validation (independent SIL 3-4) |
| `/saf` | Safety Engineer | Hazard analysis, FMEA, FTA, safety case |
| `/qua` | Quality Assurance | Code reviews, audits, quality gates |
| `/pm` | Project Manager | Project coordination, CCB leadership, reports to COD |
| `/cm` | Configuration Manager | Version control, baselines, change management (mandatory all SILs) |
| `/vmgr` | V&V Manager | Independent V&V authority, manages VER team (SIL 3-4) |
| `/workspace` (`/ws`) | Workspace Manager | Multi-project workspace management |
| `/enhelp` | Help System | Command documentation |

**Key Notes**:
- **Independence (SIL 3-4)**: VER, VAL, VMGR must be independent from development team
- **Phase Gates**: COD enforces SIL-dependent gates: Advisory (SIL 0-1), Semi-strict (SIL 2), Strict (SIL 3-4)
- **Configuration Management**: CM is mandatory for ALL SIL levels (0-4)

See [AGENTS.md](AGENTS.md) for detailed documentation and EN 50128 technique tables.

## Documentation

### Essential References

Platform documentation in root directory:

| Document | Description | Size |
|----------|-------------|------|
| **[TUTORIAL.md](TUTORIAL.md)** | Complete step-by-step tutorial for SIL 3 project (Manual Mode for learning, PM Automation Guide for production) | Comprehensive guide |
| **[LIFECYCLE.md](LIFECYCLE.md)** | EN 50128 V-Model lifecycle (10 phases) | 1637 lines |
| **[AGENTS.md](AGENTS.md)** | All 13 agent definitions and workflows | 837 lines |
| **[PHASES-VS-DOCUMENTS.md](PHASES-VS-DOCUMENTS.md)** | Phase-to-document mapping (30+ documents) | 580 lines |
| **[EN50128-DELIVERABLES-MAPPING.md](EN50128-DELIVERABLES-MAPPING.md)** | Document naming guide | 264 lines |
| **[CONTRIBUTING.md](CONTRIBUTING.md)** | Contribution guidelines | - |
| **[CHANGELOG.md](CHANGELOG.md)** | Version history | - |

### Supporting Documentation

Additional guides in `docs/` directory:

- **[QUICKSTART.md](docs/QUICKSTART.md)** - Getting started guide
- **[SETUP.md](docs/SETUP.md)** - Setup instructions  
- **[EN50128-Compliance-Guide.md](docs/EN50128-Compliance-Guide.md)** - Compliance overview
- **[Project-Structure.md](docs/Project-Structure.md)** - Detailed structure
- **[WORKSPACE-WORKFLOWS.md](docs/WORKSPACE-WORKFLOWS.md)** - Multi-project workflows

### EN 50128 Standards

LLM-friendly Markdown standards in `std/` directory:

- **EN50128-2011.md** - Railway software standard (2.2 MB)
- **EN 50126-1-2017.md** - RAMS Part 1 (293 KB)
- **EN 50126-2-2017.md** - RAMS Part 2 (210 KB)
- **EN50128-ABBREVIATIONS.md** - Official abbreviations
- **EN50128-TABLES-EXTRACTED.md** - All technique tables (A.2-A.23)

## Platform Architecture

This is an **EN 50128 development platform** - actual railway software projects reside in `examples/`.

```
EN50128/                                   # Platform Root
│
├── TUTORIAL.md                            # Step-by-step tutorial (NEW!)
├── LIFECYCLE.md                           # V-Model lifecycle (1637 lines)
├── AGENTS.md                              # 13 agent definitions
├── README.md                              # This file
│
├── .opencode/                             # OpenCode customization
│   ├── commands/                          # 13 agent commands
│   │   ├── cod.md                        # Lifecycle Coordinator
│   │   ├── req.md, des.md, imp.md       # Requirements, Design, Implementation
│   │   ├── tst.md, int.md               # Testing, Integration
│   │   ├── ver.md, val.md               # Verification, Validation
│   │   ├── saf.md, qua.md               # Safety, Quality
│   │   ├── pm.md, cm.md, vmgr.md        # PM, Config, V&V Manager
│   │   └── workspace.md, enhelp.md      # Workspace, Help
│   └── skills/                            # 12 domain-specific skills
│       ├── en50128-requirements/         # Requirements engineering
│       ├── en50128-design/               # Architecture & design
│       ├── en50128-implementation/       # C + MISRA C
│       ├── en50128-testing/              # Testing methodologies
│       ├── en50128-integration/          # Integration techniques
│       ├── en50128-verification/         # Verification & static analysis
│       ├── en50128-validation/           # Validation & system testing
│       ├── en50128-safety/               # Safety analysis (FMEA, FTA)
│       ├── en50128-quality/              # Quality assurance
│       ├── en50128-documentation/        # Documentation templates
│       ├── en50128-project-management/   # Project management
│       └── en50128-configuration/        # Configuration management
│
├── std/                                   # EN 50128 Standards (LLM-friendly)
│   ├── EN50128-2011.md                   # Main standard (2.2 MB)
│   ├── EN 50126-1-2017.md                # RAMS Part 1
│   ├── EN 50126-2-2017.md                # RAMS Part 2
│   └── ...
│
├── docs/                                  # Platform documentation
│   ├── QUICKSTART.md, SETUP.md
│   ├── EN50128-Compliance-Guide.md
│   ├── Project-Structure.md
│   └── WORKSPACE-WORKFLOWS.md
│
├── assets/                                # Platform assets
│   └── sample_system/                    # ⭐ System-level document templates
│       ├── README.md                     # Usage guide
│       ├── System-Requirements-Specification-TEMPLATE.md
│       ├── System-Architecture-Description-TEMPLATE.md
│       ├── System-Safety-Plan-TEMPLATE.md
│       └── System-Safety-Requirements-Specification-TEMPLATE.md
│
├── examples/                              # ⭐ YOUR PROJECTS GO HERE
│   ├── train_door_control2/              # Reference SIL 3 project (Phase 5)
│   │   ├── LIFECYCLE_STATE.md           # Phase tracking
│   │   ├── src/                         # C source (MISRA C)
│   │   ├── test/                        # Unity unit tests
│   │   ├── docs/                        # EN 50128 documents
│   │   │   └── system/                  # System-level documents (EN 50126/50129)
│   │   ├── Makefile
│   │   └── README.md
│   └── [your_project]/                   # Create new projects here
│
└── tools/                                 # Platform tools
    ├── pdf-conversion/                    # PDF to Markdown
    └── static-analysis/                   # MISRA C checking
```

**Key Points**:
- Platform root = EN 50128 agents, skills, standards
- `assets/sample_system/` = System-level document templates (EN 50126/50129 inputs)
- `examples/` = All railway software projects
- No `src/` in root = Projects go in `examples/`

See [docs/Project-Structure.md](docs/Project-Structure.md) for complete details.

## System-Level Documents (EN 50126/50129 Inputs)

### Overview

Per EN 50128 Section 7.2.2, **four system-level documents are MANDATORY inputs** before software requirements specification can begin:

1. **System Requirements Specification** - Overall system functional and non-functional requirements
2. **System Architecture Description** - Hardware/software partitioning, system structure
3. **System Safety Plan** - Safety management strategy, lifecycle activities, V&V plan
4. **System Safety Requirements Specification** - Hazards (FMEA/FTA), safety functions, safety requirements

These documents are produced by the **System Engineering phase** (EN 50126/50129) and consumed by the **Software Engineering phase** (EN 50128).

### Sample Templates Available

The platform provides **complete reference examples** in `assets/sample_system/`:

| Template | Lines | Content |
|----------|-------|---------|
| **System-Requirements-Specification-TEMPLATE.md** | 569 | 71 requirements for Train Door Control System |
| **System-Architecture-Description-TEMPLATE.md** | 769 | Dual-channel architecture, hardware/software partitioning |
| **System-Safety-Plan-TEMPLATE.md** | 1189 | Complete safety management plan, ISA strategy, lifecycle |
| **System-Safety-Requirements-Specification-TEMPLATE.md** | 508 | 9 hazards, FMEA/FTA, 7 safety functions at SIL 2-3 |

**These are NOT generic templates** - they contain complete Train Door Control System content as learning examples. Only metadata is templated (Document IDs, dates, names).

### How to Use

1. **Study the examples**: Read `assets/sample_system/README.md` and the template files
2. **Copy for your project**: Copy relevant templates to `your_project/docs/system/`
3. **Customize metadata**: Replace `YYYY-MM-DD`, `[Name]`, `DOC-XXX-YYYY-NNN` with your project info
4. **Adapt content**: Replace Train Door Control specifics with YOUR system (keep structure and rigor)
5. **Use as EN 50128 inputs**: Reference these in Phase 2 (Requirements) when using `/req` agent

See `assets/sample_system/README.md` for complete usage guide and example workflows.

### Reference Implementation

`examples/train_door_control2/docs/system/` contains the original (non-templated) system documents for the reference implementation.

### When to Create

**Before Phase 2 (Requirements Specification)**:

```
System Engineering (EN 50126/50129)
    ↓
Create 4 system-level documents ← Use assets/sample_system/ as reference
    ↓
Phase 2: Software Requirements (EN 50128) ← Begins here
    ↓
Use /req, /des, /imp, etc.
```

## EN 50128 Compliance Requirements

### Code Coverage by SIL (Table A.21)

| Coverage Type | SIL 0-1 | SIL 2 | SIL 3-4 |
|---------------|---------|-------|---------|
| Statement Coverage | HR | HR | **M** |
| Branch Coverage | HR | **M** | **M** |
| Condition Coverage | R | HR | **M** |
| MC/DC Coverage | - | R | HR |

**M** = Mandatory, **HR** = Highly Recommended, **R** = Recommended

### Testing Techniques (Table A.5)

| Technique | SIL 0-1 | SIL 2 | SIL 3-4 |
|-----------|---------|-------|---------|
| Boundary Value Analysis | HR | HR | **M** |
| Equivalence Partitioning | HR | HR | HR |
| Fault Injection | R | HR | HR |

### Independence Requirements (SIL 3-4)

**Mandatory for SIL 3-4:**
- Independent verification team (separate from development)
- Independent validation team
- Independent safety assessor
- Tool qualification for development tools

### Recommended Tools by SIL

**All SILs**: Git, Make/CMake, Markdown

**SIL 2+**: Coverity/PC-lint/Cppcheck (static analysis), gcov/lcov (coverage), DOORS/Jama (requirements)

**SIL 3-4**: SCADE/B-Method (formal methods), SPIN/NuSMV (model checking), tool qualification per EN 50128 Annex C

## Best Practices

### 1. Traceability
Establish bidirectional traceability from day one: Requirements ↔ Design ↔ Code ↔ Tests

### 2. Defensive Programming (SIL 2+)
- Validate all inputs
- Check all return values  
- Handle all error conditions
- Use assertions liberally

### 3. Configuration Management
- Version control everything
- Establish baselines early
- Implement change control (CCB for SIL 3-4)
- Maintain audit trail

### 4. Independent Review (SIL 3-4)
- Separate development and V&V teams
- Independent safety assessment
- Peer review all code and documents

### 5. Comprehensive Testing
- Achieve required coverage targets (100% for SIL 3-4)
- Test boundary conditions (mandatory SIL 3-4)
- Perform fault injection (highly recommended SIL 3-4)
- Execute regression tests

## Common Pitfalls

1. **Late traceability** - Establish from the beginning, not retroactively
2. **Insufficient independence** - Separate teams required for SIL 3-4
3. **Poor documentation** - Keep docs updated throughout lifecycle
4. **Tool over-reliance** - Qualify tools per EN 50128 Annex C
5. **Inadequate testing** - Meet mandatory coverage requirements
6. **Weak change control** - Implement rigorous CM process early

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines on:
- Adding new agent commands
- Creating skills and templates
- Improving documentation
- Reporting issues

## Version History

See [CHANGELOG.md](CHANGELOG.md) for detailed version history.

**Current Version**: 2.0.0 (2026-02-23)
- Complete EN 50128 V-Model implementation (10 phases)
- 13 operational agents with SIL-dependent behaviors
- Comprehensive tutorial (TUTORIAL.md)
- Multi-workspace support
- Streamlined documentation

## License

MIT License - See LICENSE file for details.

## Support

- **Tutorial**: [TUTORIAL.md](TUTORIAL.md) - Complete step-by-step guide
- **Quick Start**: [docs/QUICKSTART.md](docs/QUICKSTART.md)
- **Agent Reference**: [AGENTS.md](AGENTS.md)
- **Lifecycle Guide**: [LIFECYCLE.md](LIFECYCLE.md)
- **Issues**: Report bugs and feature requests on GitHub

---

**Disclaimer**: This platform provides guidance and tools for EN 50128 compliance. Actual certification requires independent safety assessment by qualified assessors and approval by relevant railway authorities.
