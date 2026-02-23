# EN 50128 Railway Software Development Platform

**AI-powered development platform for EN 50128:2011 compliant railway software**

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
/enhelp req        # Requirements Engineer
```

### 2. Create Your First Project

```bash
# Create and initialize a new SIL 3 project
mkdir -p examples/my_railway_project
cd examples/my_railway_project
/cod plan --sil 3 --project my_railway_project

# Start with requirements engineering
/req  # COD enforces user approval for requirements

# Follow the V-Model lifecycle
/des               # Architecture & Design
/cod gate-check design

/saf               # Safety Analysis (FMEA, FTA)
/imp               # Implementation (C + MISRA C:2012)
/tst               # Unit Testing with coverage
/ver               # Verification (static analysis)
/int               # Integration
/val               # Validation (system testing)
/cod gate-check validation

# Throughout: /cm (Configuration), /qua (Quality), /pm (Project Management)
```

### 3. Reference Implementation

See `examples/train_door_control2/` for a complete SIL 3 implementation (Phase 5 complete).

### 4. Multi-Project Workflow

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

Specialized AI agents accessible via slash commands:

| Command | Agent | Role |
|---------|-------|------|
| `/cod` | Lifecycle Coordinator | V-Model orchestration, phase gates, compliance enforcement |
| `/req` | Requirements Engineer | Requirements specification and traceability |
| `/des` | Designer | Software architecture and detailed design |
| `/imp` | Implementer | C code implementation with MISRA C compliance |
| `/tst` | Tester | Unit and integration testing with coverage |
| `/int` | Integrator | Component integration and interface testing |
| `/ver` | Verifier | Static analysis and verification evidence |
| `/val` | Validator | System testing and acceptance validation |
| `/saf` | Safety Engineer | Hazard analysis, FMEA, FTA, safety case |
| `/qua` | Quality Assurance | Code reviews, audits, quality gates |
| `/pm` | Project Manager | Project coordination, CCB leadership |
| `/cm` | Configuration Manager | Version control, baselines, change management |
| `/vmgr` | V&V Manager | Independent V&V authority (SIL 3-4) |
| `/workspace` (`/ws`) | Workspace Manager | Multi-project workspace management |
| `/enhelp` | Help System | Command documentation |

**Note**: COD enforces SIL-dependent phase gates: Advisory (SIL 0-1), Semi-strict (SIL 2), Strict (SIL 3-4).

See [AGENTS.md](AGENTS.md) for detailed documentation.

## Documentation

### Essential References

Platform documentation in root directory:

| Document | Description | Size |
|----------|-------------|------|
| **[TUTORIAL.md](TUTORIAL.md)** | Complete step-by-step tutorial for SIL 3 project | Comprehensive guide |
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
├── examples/                              # ⭐ YOUR PROJECTS GO HERE
│   ├── train_door_control2/              # Reference SIL 3 project (Phase 5)
│   │   ├── LIFECYCLE_STATE.md           # Phase tracking
│   │   ├── src/                         # C source (MISRA C)
│   │   ├── test/                        # Unity unit tests
│   │   ├── docs/                        # EN 50128 documents
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
- `examples/` = All railway software projects
- No `src/` in root = Projects go in `examples/`

See [docs/Project-Structure.md](docs/Project-Structure.md) for complete details.

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
