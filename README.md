# EN 50128 Railway Software Development Platform

**AI-powered development platform for EN 50128:2011 compliant railway software**

**Status**: Active Development — agent and skill rewrite in progress (see [Agent Rewrite Status](#agent-rewrite-status))
**Version**: 3.1.0

---

## Overview

This platform provides a complete EN 50128-compliant software development environment using OpenCode. It implements the full V-Model lifecycle with SIL-dependent phase gate enforcement, 14 specialized AI agents, and 18 domain-specific skill libraries.

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

@pm execute-phase 2    # Requirements: SRS
@cod gate-check phase-2

@pm execute-phase 3    # Architecture & Design: SAS, SDS, Interface Specs, Integration Test Specs
@cod gate-check phase-3

@pm execute-phase 4    # Component Design: Component Design Spec, Component Test Spec
@cod gate-check phase-4

@pm execute-phase 5    # Implementation + Unit Testing: Source Code, Component Test Report
@cod gate-check phase-5

@pm execute-phase 6    # Integration: SW + HW/SW Integration Test Reports
@cod gate-check phase-6

@pm execute-phase 7    # Overall Testing / Validation: Overall Software Test Report
@cod gate-check phase-7

# Phase 8: Assessment — facilitated by PM, conducted by independent ASR
@cod gate-check phase-8

@pm execute-phase 9    # Deployment: Release and Deployment Plan, Deployment Records
@cod gate-check phase-9
```

**Two entry points only**: `@cod` (lifecycle authority) and `@pm` (phase execution). All other agents are orchestrated internally.

### 3. Check Status

```bash
@cod status            # Lifecycle state, phase progress, deliverables
@pm status             # Project coordination status
```

---

## Platform Architecture

### Information Architecture

The platform is structured in three tiers:

```
┌──────────────────────────────────────────────────────────────┐
│  TIER 1 — Fundamental Documents (authoritative, ISA-reviewed) │
│  AGENTS.md · LIFECYCLE.md · WORKFLOW.md · ORGANIZATION.md    │
│  DELIVERABLES.md · TRACEABILITY.md · TOOLS.md                │
├──────────────────────────────────────────────────────────────┤
│  TIER 2 — Machine-Readable YAML (activities/)                 │
│  phase-N-*.yaml · workflow.yaml · deliverables.yaml          │
│  roles.yaml · organization.yaml · lifecycle.yaml             │
│  traceability.yaml                                           │
├──────────────────────────────────────────────────────────────┤
│  TIER 3 — Agent & Skill Shells (.opencode/)                   │
│  Thin behavioral files that reference Tiers 1 & 2.           │
│  No duplication of standard content.                         │
└──────────────────────────────────────────────────────────────┘
```

Agents and skills are **thin shells** — they describe *how to act*, not *what the rules are*. All rules live in the fundamental documents and YAML files.

### Fundamental Documents

These files are the single source of truth for all platform rules. They are ISA-reviewed and must not be modified without formal change control.

| Document | Purpose |
|----------|---------|
| [`AGENTS.md`](AGENTS.md) | Role definitions, independence matrix, agent-to-skill mapping |
| [`LIFECYCLE.md`](LIFECYCLE.md) | V-Model phases (0–10), entry/exit criteria, deliverable mapping |
| [`WORKFLOW.md`](WORKFLOW.md) | Authority structure (Diagrams 1–4), two-track model, CCB re-entry flow |
| [`ORGANIZATION.md`](ORGANIZATION.md) | SIL-tiered org charts, role combination rules |
| [`DELIVERABLES.md`](DELIVERABLES.md) | Complete Annex C Table C.1 deliverable catalogue |
| [`TRACEABILITY.md`](TRACEABILITY.md) | Traceability rules T1–T15, gate enforcement |
| [`TOOLS.md`](TOOLS.md) | Tool catalogue, SIL requirements, T1/T2/T3 confidence levels |

### Machine-Readable YAML (`activities/`)

The `activities/` directory provides machine-readable representations of the lifecycle. These are the **primary data source** for agents — agents read these files directly rather than relying on prose descriptions.

| File | Content |
|------|---------|
| `phase-0-initialization.yaml` | Lifecycle initialization activities |
| `phase-1-planning.yaml` through `phase-10-maintenance.yaml` | Per-phase Track A activities, deliverables, Track B criteria, gate check criteria |
| `workflow.yaml` | CCB re-entry flow, change classification rules |
| `deliverables.yaml` | Complete deliverable catalogue (mirrors DELIVERABLES.md) |
| `lifecycle.yaml` | Phase FSM, transitions, SIL-dependent enforcement rules |
| `roles.yaml` | Role definitions with independence requirements by SIL |
| `organization.yaml` | Role combination rules, org structure |
| `traceability.yaml` | Traceability rules T1–T15 in structured form |

### OpenCode Tabs

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
| `@req` | Requirements Engineer (§7.2, Table B.2) | No |
| `@des` | Designer (§7.3, Table B.2) | No |
| `@imp` | Implementer (§7.4, Table B.3) | No |
| `@tst` | Tester (§7.5, Table B.4) | No |
| `@int` | Integrator (§7.6, Table B.6) | No |
| `@ver` | Verifier (§6.2, Table B.5) | **MANDATORY** |
| `@val` | Validator (§7.7, Table B.7) | **MANDATORY** |
| `@saf` | Safety Engineer (§7.1, §6.3) | No |

#### Management and Support Agents

| Agent | EN 50128 Role | Independence (SIL 3-4) |
|-------|---------------|------------------------|
| `@cod` | Lifecycle Coordinator (§5.3, platform extension) | No |
| `@pm` | Project Manager (§5, Table B.9) | No |
| `@cm` | Configuration Manager (§6.6, Table B.10) | No |
| `@qua` | Quality Assurance (§6.5) | No |
| `@vmgr` | V&V Manager (§5.1.2.10e, platform extension) | **MANDATORY** |

**User entry points**: `@cod` and `@pm` only. All other agents are orchestrated internally by COD and PM.

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
- **PM** coordinates Track A (development) only; reports to COD for lifecycle decisions
- **VER/VAL** operate on Track B; PM never directs them

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

## Agent Rewrite Status

The COD and PM agents have been rewritten following a **thin shell** philosophy: agent and skill files reference authoritative sources (fundamental documents + `activities/` YAMLs) rather than duplicating them. This eliminates content drift and reduces context load.

### Completed

| Agent | Before | After | Reduction |
|-------|--------|-------|-----------|
| **COD** (`cod.md` + 5 skill files) | ~13,600 lines | ~1,100 lines | 92% |
| **PM** (`pm.md` + skill + phase YAMLs) | ~5,100 lines | ~670 lines | 87% |

**COD** skill files rewritten: `en50128-lifecycle-coordination`, `en50128-lifecycle-capabilities`, `en50128-lifecycle-phase-checklists`, `en50128-lifecycle-examples`. Ten obsolete COD workflow/template files deleted.

**PM** skill files rewritten: `en50128-project-management/SKILL.md` and all phase coordination data consolidated into a single `phase-coordination.yaml`. Five obsolete PM files deleted (SCHEMA.md, defect workflow, 3 templates). PM-local phase YAMLs now contain only PM-specific coordination notes (special cases, agent sequencing, escalation triggers) — all base phase data is read from `activities/phase-N-*.yaml`.

### In Progress

The remaining 12 agent files (REQ, DES, IMP, TST, INT, VER, VAL, SAF, QUA, CM, VMGR, and supporting raildev/doc-reviewer agents) are being rewritten using the same thin-shell approach. Until rewritten, they remain functional but may carry more prose than necessary.

**Rewrite principles applied to each agent:**
1. Agent file (`*.md`) is a boot script only (~70–90 lines): identity, skill load instruction, capabilities list, hard rules, reference table
2. Primary skill (`SKILL.md`) is an authoritative-sources table + unique behavioral patterns only (~120–150 lines)
3. All rules and data live in fundamental documents or `activities/` YAMLs — never duplicated in agent/skill files
4. Phase-specific coordination notes live in a single `phase-coordination.yaml` per skill, keyed by phase number

---

## Directory Structure

```
EN50128/
├── README.md                          # This file
├── AGENTS.md                          # Role definitions, independence matrix  ← fundamental doc
├── LIFECYCLE.md                       # EN 50128 V-Model (10 phases)           ← fundamental doc
├── WORKFLOW.md                        # Authority structure, two-track model    ← fundamental doc
├── ORGANIZATION.md                    # SIL-tiered org charts, role rules       ← fundamental doc
├── DELIVERABLES.md                    # Annex C Table C.1 deliverables          ← fundamental doc
├── TRACEABILITY.md                    # Traceability rules T1–T15               ← fundamental doc
├── TOOLS.md                           # Tool catalog (T1/T2/T3 confidence)      ← fundamental doc
├── SETUP.md                           # Installation guide
├── CONTRIBUTING.md                    # Contribution guidelines
├── CHANGELOG.md                       # Version history
│
├── activities/                        # Machine-readable lifecycle data (primary agent data source)
│   ├── phase-0-initialization.yaml   # Lifecycle initialization
│   ├── phase-1-planning.yaml         # Phase 1: Track A activities, deliverables, gate criteria
│   ├── phase-2-requirements.yaml     # Phase 2: Requirements
│   ├── phase-3-architecture-design.yaml
│   ├── phase-4-component-design.yaml
│   ├── phase-5-implementation-testing.yaml
│   ├── phase-6-integration.yaml
│   ├── phase-7-validation.yaml
│   ├── phase-8-assessment.yaml
│   ├── phase-9-deployment.yaml
│   ├── phase-10-maintenance.yaml
│   ├── workflow.yaml                  # CCB re-entry flow, change classification
│   ├── deliverables.yaml             # Complete deliverable catalogue
│   ├── lifecycle.yaml                # Phase FSM, SIL enforcement rules
│   ├── roles.yaml                    # Role definitions and independence rules
│   ├── organization.yaml             # Role combination rules
│   └── traceability.yaml             # Traceability rules T1–T15
│
├── .opencode/
│   ├── agents/                        # 14 agent definition files (thin boot scripts)
│   │   ├── raildev.md                # Primary RailDev mode
│   │   ├── cod.md                    # Lifecycle Coordinator  ✓ rewritten
│   │   ├── pm.md                     # Project Manager        ✓ rewritten
│   │   ├── req.md, des.md, imp.md   # Requirements, Design, Implementation
│   │   ├── tst.md, int.md           # Testing, Integration
│   │   ├── ver.md, val.md           # Verification, Validation
│   │   ├── saf.md, qua.md           # Safety, Quality
│   │   ├── cm.md, vmgr.md           # Config, V&V Manager
│   │   └── doc-reviewer.md           # ISA / doc review
│   └── skills/                        # 18 domain-specific skills
│       ├── en50128-lifecycle-coordination/   ✓ rewritten
│       ├── en50128-lifecycle-capabilities/   ✓ rewritten
│       ├── en50128-lifecycle-phase-checklists/ ✓ rewritten
│       ├── en50128-lifecycle-examples/       ✓ rewritten
│       ├── en50128-lifecycle-tool-integration/
│       ├── en50128-project-management/       ✓ rewritten
│       │   ├── SKILL.md
│       │   └── phase-coordination.yaml       # PM coordination notes for all 10 phases
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
│       ├── en50128-configuration/
│       └── en50128-tools/
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
| [`WORKFLOW.md`](WORKFLOW.md) | Authority structure, two-track model, CCB re-entry flow |
| [`ORGANIZATION.md`](ORGANIZATION.md) | SIL-tiered org charts, role combination rules |
| [`DELIVERABLES.md`](DELIVERABLES.md) | Annex C Table C.1 complete deliverable matrix |
| [`TRACEABILITY.md`](TRACEABILITY.md) | Traceability rules T1–T15 |
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
