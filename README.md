# EN 50128 Railway Software Development Platform

**AI-powered development platform for EN 50128:2011 compliant railway software**

**Status**: Production Ready  
**Version**: 3.0.0

---

## Overview

This platform provides a complete EN 50128-compliant software development environment using OpenCode. It implements the full V-Model lifecycle with SIL-dependent phase gate enforcement, 14 specialized AI agents, and 13 domain-specific skill libraries.

**Primary use**: Develop safety-critical railway software in C (SIL 0-4) with full EN 50128:2011 compliance — from planning through deployment.

**This is a development platform, not a project template.** All railway software projects are developed in the `examples/` directory, each with independent lifecycle tracking.

---

## IMPORTANT: OpenCode Required

This platform must be used within the OpenCode TUI environment.

- **Install OpenCode**: See [https://opencode.ai](https://opencode.ai)
- **Why required**: The platform uses OpenCode's agent system, specialized skills, and `@agent` routing
- **Do NOT use**: Generic LLM interfaces — they cannot invoke agents or access EN 50128 skills

---

## Quick Start

### 1. Install Tools

```bash
# System tools (requires sudo)
./install_tools.sh

# Python tools (creates venv/)
./install_python.sh

# Verify
./install_tools.sh --check
```

See [`SETUP.md`](SETUP.md) for complete setup instructions.

### 2. Start a Project

```bash
# In OpenCode — initialize lifecycle
@cod plan --sil 3 --project my_railway_component

# Generate system-level input documents (choose from 5 typical railway systems)
@cod generate-system

# Execute phases via Project Manager
@pm execute-phase 1    # Planning: SQAP, SCMP, SVP, SVaP
@cod gate-check phase-1

@pm execute-phase 2    # Requirements: SRS, Overall Test Spec
@cod gate-check phase-2

@pm execute-phase 3    # Design: SAS, SDS, Interface Specs
@cod gate-check phase-3

@pm execute-phase 4    # Implementation + Unit Testing
@cod gate-check phase-4

@pm execute-phase 5    # Integration
@cod gate-check phase-5

# Phase 6 validation — COD invokes VAL directly (independence)
@cod gate-check phase-6

@pm execute-phase 8    # Deployment
```

**Two entry points only**: `@cod` (lifecycle authority) and `@pm` (phase execution). All other agents are orchestrated internally.

### 3. Check Status

```bash
@cod status            # Lifecycle state, phase progress, deliverables
@pm status             # Project coordination status
```

---

## Platform Architecture

### OpenCode Tabs

The platform provides three OpenCode tabs:

| Tab | Mode | Purpose |
|-----|------|---------|
| **RailDev** | Primary | Default mode — railway software development with full EN 50128 context |
| **Build** | Primary | Compilation and testing focused |
| **Plan** | Primary | Planning and architecture focused |

Use the **RailDev** tab for all EN 50128 development work.

### Agent System

14 specialized AI agents implement EN 50128-defined roles:

#### Core Development Agents

| Agent | EN 50128 Role | Independence (SIL 3-4) |
|-------|---------------|------------------------|
| `@req` | Requirements Manager (5.3.1) | No |
| `@des` | Designer (5.3.2) | No |
| `@imp` | Implementer (5.3.3) | No |
| `@tst` | Tester (5.3.4) | No |
| `@int` | Integrator (5.3.6) | No |
| `@ver` | Verifier (5.3.5) | **MANDATORY** |
| `@val` | Validator (5.3.7) | **MANDATORY** |
| `@saf` | Safety Engineer (7.1) | No |

#### Management and Support Agents

| Agent | EN 50128 Role | Independence (SIL 3-4) |
|-------|---------------|------------------------|
| `@cod` | Lifecycle Coordinator (5.3) | No |
| `@pm` | Project Manager (Table B.9) | No |
| `@cm` | Configuration Manager (Table B.10) | No |
| `@qua` | Quality Assurance (6.5) | No |
| `@vmgr` | V&V Manager (5.1.2.10e) | **MANDATORY** |

**User entry points**: `@cod` and `@pm` only. All other agents are orchestrated internally by COD and PM.

See [`AGENTS.md`](AGENTS.md) for complete role definitions and EN 50128 technique tables.

### Authority Structure (SIL 3-4)

```
        Safety Authority / Customer
                |
        ┌───────┴───────────┐
        |                   |
    COD (Lifecycle)     VMGR (Independent V&V)
        |                   |
    PM (Team)           VER (Verification)
        |
    REQ, DES, IMP, INT, TST, QUA, CM, SAF
```

- **COD** has overall lifecycle authority; enforces phase gates
- **VMGR** is independent; V&V approval cannot be overridden by COD or PM
- **PM** coordinates development team; reports to COD for lifecycle decisions

---

## SIL Levels

| SIL | Risk Level | Hazard Impact | Key Requirements |
|-----|------------|---------------|-----------------|
| 4 | Very High | Catastrophic - multiple fatalities | Formal methods, independent V&V, 100% coverage |
| 3 | High | Critical - single fatality | Static analysis (M), independent V&V, 100% coverage |
| 2 | Medium | Marginal - serious injuries | Branch coverage (M), MISRA C, static analysis (HR) |
| 1 | Low | Negligible - minor injuries | Statement coverage (HR) |
| 0 | None | Non-safety related | Basic testing |

---

## Directory Structure

```
EN50128/
├── README.md                          # This file
├── AGENTS.md                          # All 14 agent definitions
├── LIFECYCLE.md                       # EN 50128 V-Model (10 phases)
├── TOOLS.md                           # Tool catalog for agents
├── SETUP.md                           # Installation guide
├── CONTRIBUTING.md                    # Contribution guidelines
├── CHANGELOG.md                       # Version history
│
├── .opencode/
│   ├── agents/                        # 14 agent definition files
│   │   ├── raildev.md                # Primary RailDev mode
│   │   ├── cod.md, pm.md            # Lifecycle + Project Management
│   │   ├── req.md, des.md, imp.md   # Requirements, Design, Implementation
│   │   ├── tst.md, int.md           # Testing, Integration
│   │   ├── ver.md, val.md           # Verification, Validation
│   │   ├── saf.md, qua.md           # Safety, Quality
│   │   ├── cm.md, vmgr.md           # Config, V&V Manager
│   │   └── [build.md, plan.md]       # Build + Plan mode agents
│   └── skills/                        # 13 domain-specific skills
│       ├── en50128-requirements/
│       ├── en50128-design/
│       ├── en50128-implementation/
│       ├── en50128-testing/
│       ├── en50128-integration/
│       ├── en50128-verification/
│       ├── en50128-validation/
│       ├── en50128-safety/
│       ├── en50128-quality/
│       ├── en50128-documentation/
│       ├── en50128-project-management/
│       ├── en50128-configuration/
│       └── en50128-lifecycle-coordination/
│
├── std/                               # EN 50128 Standards (LLM-friendly Markdown)
│   ├── EN50128-2011.md               # Main standard (2.2 MB)
│   ├── EN 50126-1-2017.md            # RAMS Part 1
│   ├── EN 50126-2-2017.md            # RAMS Part 2
│   └── EN50128-TABLES-EXTRACTED.md   # Technique tables A.2-A.23
│
├── docs/
│   ├── USER-GUIDE.md                 # Complete platform user guide (START HERE)
│   └── plans/                        # Phase 1 plan templates
│
├── assets/
│   └── sample_system/                # System-level document templates + catalogue
│       ├── README.md                 # Usage guide
│       ├── TYPICAL-SYSTEMS.md        # Catalogue of 5 typical railway systems
│       ├── System-Requirements-Specification-TEMPLATE.md
│       ├── System-Architecture-Description-TEMPLATE.md
│       ├── System-Safety-Plan-TEMPLATE.md
│       └── System-Safety-Requirements-Specification-TEMPLATE.md
│
├── tools/                             # Python + shell analysis tools
│   ├── mcdc/mcdc_analyzer.py         # MC/DC analysis
│   ├── workspace.py                  # Workspace management
│   ├── workflow_manager.py           # Phase gate enforcement
│   ├── enhelp.py                     # Platform help
│   └── scripts/                      # Validation scripts
│
├── deliverables/                      # YAML deliverable definitions
├── evidence/                          # Traceability evidence
│
└── examples/                          # YOUR PROJECTS GO HERE
    └── train_door_control2/           # Reference SIL 3 project
        ├── LIFECYCLE_STATE.md
        ├── src/                       # C source (MISRA C)
        ├── tests/                     # Unity unit tests
        └── docs/                      # EN 50128 deliverables
```

---

## System-Level Documents (EN 50126/50129 Inputs)

Per EN 50128 Section 7.2.2, **four system-level documents are MANDATORY inputs** before software requirements specification can begin:

1. **System Requirements Specification** — Overall system functional and non-functional requirements
2. **System Architecture Description** — Hardware/software partitioning, system structure
3. **System Safety Plan** — Safety management strategy, lifecycle activities, V&V plan
4. **System Safety Requirements Specification** — Hazards (FMEA/FTA), safety functions, safety requirements

These are produced by System Engineering (EN 50126/50129) and consumed by Software Engineering (EN 50128).

**Automated generation**: After `@cod plan`, run `@cod generate-system` to automatically generate all four documents by selecting from the **5 typical railway systems** in `assets/sample_system/TYPICAL-SYSTEMS.md`. Generated documents are placed in `docs/system/`.

**Manual path**: Templates are in `assets/sample_system/`. Copy, adapt, and place them in `docs/system/` before running `@pm execute-phase 2`.

---

## Key Documentation

| Document | Purpose |
|----------|---------|
| [`docs/USER-GUIDE.md`](docs/USER-GUIDE.md) | Complete user guide with worked examples — **start here** |
| [`AGENTS.md`](AGENTS.md) | All 14 agent definitions, commands, and EN 50128 technique tables |
| [`LIFECYCLE.md`](LIFECYCLE.md) | Full V-Model lifecycle, phase gate criteria, deliverable mapping |
| [`TOOLS.md`](TOOLS.md) | Tool catalog with SIL requirements, confidence levels (T1/T2/T3) |
| [`SETUP.md`](SETUP.md) | Installation and environment setup |
| [`CONTRIBUTING.md`](CONTRIBUTING.md) | Contribution guidelines |
| [`CHANGELOG.md`](CHANGELOG.md) | Version history |

---

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for guidelines on adding agents, creating skills, improving documentation, and reporting issues.

---

## License

MIT License — see LICENSE file for details.

---

**Disclaimer**: This platform provides guidance and tooling for EN 50128 compliance. Actual certification requires independent safety assessment by qualified assessors and approval by relevant railway authorities.
