# EN 50128 Platform User Guide

**Version**: 3.0  
**Date**: 2026-03-15  
**Platform Status**: Production Ready  
**Target Audience**: Railway software developers, project managers, safety engineers

---

## Table of Contents

1. [Overview](#overview)
2. [Getting Started](#getting-started)
3. [Platform Architecture](#platform-architecture)
4. [Agent-Orchestrated Workflow](#agent-orchestrated-workflow)
5. [Agent Reference](#agent-reference)
6. [Tool Integration](#tool-integration)
7. [Complete Example: SIL 3 Door Speed Monitor](#complete-example-sil-3-door-speed-monitor)
8. [Best Practices](#best-practices)
9. [Troubleshooting](#troubleshooting)
10. [References](#references)

---

## Overview

### What is the EN 50128 Platform?

The EN 50128 Platform is a **document-centric, agent-orchestrated development environment** for creating railway safety software compliant with EN 50128:2011. It provides:

- **13 specialized agents** covering all EN 50128 roles and lifecycle phases
- **50+ document templates** for all mandatory deliverables (Annex C)
- **40+ automation tools** for validation, testing, and verification
- **Complete V-Model lifecycle** with SIL-dependent phase gate enforcement
- **SIL-aware workflows** (SIL 0-4 support)
- **MISRA C:2012 compliance** tooling (SIL 2+)
- **End-to-end traceability** from system requirements to validation

### Key Principles

1. **Agent-Orchestrated**: COD orchestrates the lifecycle; PM coordinates agents within phases
2. **Document-Centric**: All work products are markdown documents; evidence lives in documents
3. **SIL-Aware**: Agent behaviors, gate enforcement, and coverage requirements adapt to SIL level
4. **Tool-Integrated**: Automated validation, testing, static analysis, and traceability management
5. **Standard-Compliant**: Every action references EN 50128 sections, tables, and techniques

### How It Works

**You provide system-level inputs. Agents produce all deliverables.**

```
You provide:
  assets/sample_system/System-Requirements-Specification.md
  assets/sample_system/System-Hazard-Log.md

You invoke:
  @cod plan --sil 3 --project TrainDoorControl

COD orchestrates → PM coordinates → Agents create all deliverables:
  ✅ Phase 1: SQAP, SCMP, SVP, SVaP
  ✅ Phase 2: SRS, Hazard Log, Traceability Matrix
  ✅ Phase 3: SAS, SDS, Interface Specifications
  ✅ Phase 4: C source code, unit tests, Verification Report
  ✅ Phase 5: Integration plan, integration tests, Integration Report
  ✅ Phase 6: System tests, Validation Report
  ✅ Phase 7: Assessment Report (SIL 3-4)
  ✅ Phase 8: Release package
```

---

## Getting Started

### Prerequisites

**System Requirements**:
- Linux (Ubuntu 20.04+ or Debian-based)
- Git 2.0+
- Python 3.8+
- GCC 11.0+ (for C compilation)
- 4GB RAM minimum, 8GB recommended

**Knowledge Requirements**:
- EN 50128:2011 standard (recommended reading: `std/EN50128-2011.md`)
- C programming language
- MISRA C:2012 (for SIL 2+)
- Git version control

### Installation

**1. Clone the Repository**
```bash
git clone <repository-url>
cd EN50128
```

**2. Install System Tools**
```bash
# Install all MANDATORY tools for SIL 3-4
./install_tools.sh

# Or check what's already installed
./install_tools.sh --check
```

**3. Install Python Tools**
```bash
# Setup virtual environment and install Python packages
./install_python.sh

# Activate the virtual environment
source venv/bin/activate
```

**4. Verify Tool Installation**
```bash
# Check all tools are installed and meet version requirements
source venv/bin/activate
tools/tool-validation/check-tool-versions.sh --sil 3 --verbose
```

Expected output: `[PASS] All tools OK`

**5. Validate Tool Configuration (SIL 2+)**
```bash
# Run automated T2 tool validation
tools/tool-validation/run-all-validations.sh
```

Expected output: `[PASS] All validations passed`

### Your First Project

**1. Prepare system-level inputs:**
```bash
mkdir -p assets/sample_system
# Create System-Requirements-Specification.md
# Create System-Hazard-Log.md (optional but recommended for SIL 2+)
```

**2. Start the lifecycle:**
```
@cod plan --sil 3 --project MyRailwayComponent
```

COD will initialize the workspace, create `LIFECYCLE_STATE.md`, and display the V-Model plan.

**3. Execute phases via PM:**
```
@pm execute-phase 1
```

PM will coordinate all agents for Phase 1 (Planning), produce SQAP, SCMP, SVP, SVaP, and report completion to COD.

**4. Advance to the next phase after COD gate check:**
```
@cod gate-check phase-1
@pm execute-phase 2
```

Repeat until `@pm execute-phase 8`.

---

## Platform Architecture

### Directory Structure

```
EN50128/
├── .opencode/
│   ├── agents/                   # 13 EN 50128 role agents
│   │   ├── cod.md               # Lifecycle Coordinator
│   │   ├── pm.md                # Project Manager
│   │   ├── req.md               # Requirements Engineer
│   │   ├── des.md               # Designer
│   │   ├── imp.md               # Implementer
│   │   ├── tst.md               # Tester
│   │   ├── ver.md               # Verifier (independent)
│   │   ├── val.md               # Validator (independent)
│   │   ├── int.md               # Integrator
│   │   ├── saf.md               # Safety Engineer
│   │   ├── qua.md               # Quality Assurance
│   │   ├── cm.md                # Configuration Manager
│   │   └── vmgr.md              # V&V Manager (SIL 3-4)
│   └── skills/                   # Internal skills loaded by agents
│       ├── en50128-requirements/
│       ├── en50128-design/
│       ├── en50128-implementation/
│       ├── en50128-testing/
│       ├── en50128-verification/
│       ├── en50128-integration/
│       ├── en50128-validation/
│       ├── en50128-safety/
│       ├── en50128-quality/
│       ├── en50128-configuration/
│       ├── en50128-lifecycle-coordination/
│       ├── en50128-documentation/
│       └── en50128-project-management/
├── assets/
│   └── sample_system/            # User-provided system-level inputs
├── examples/                     # Complete example projects (agent-produced)
├── docs/                         # Platform documentation
│   ├── LIFECYCLE.md             # Complete V-Model lifecycle guide
│   └── USER-GUIDE.md            # This file
├── std/                          # EN 50128 standard (LLM-friendly)
│   ├── EN50128-2011.md
│   ├── EN 50126-1-2017.md
│   └── EN 50126-2-2017.md
├── tools/                        # Automation tools
│   ├── traceability_manager.py
│   ├── workflow_manager.py
│   ├── workspace.py
│   ├── scripts/
│   │   ├── validate_srs_template.py
│   │   ├── validate_sas_sds_template.py
│   │   ├── validate_test_doc_template.py
│   │   ├── parse_coverage_report.py
│   │   └── generate_test_report.py
│   ├── tool-validation/
│   │   ├── run-all-validations.sh
│   │   └── check-tool-versions.sh
│   └── mcdc/
│       └── mcdc_analyzer.py
├── AGENTS.md                     # Role definitions and @agent syntax reference
├── LIFECYCLE.md                  # V-Model lifecycle guide
└── TOOLS.md                      # Tool catalog with T1/T2/T3 classification
```

### Authority Structure

```
        Safety Authority / Customer
                    |
        ┌───────────┴──────────────┐
        |                          |
    COD (Lifecycle Authority)   VMGR (Independent V&V — SIL 3-4)
        |                          |
    PM (Team Coordination)      VER (reports to VMGR)
        |
    REQ, DES, IMP, TST, INT, SAF, QUA, CM
```

**Key rules:**
- **COD** has overall lifecycle authority; PM reports to COD for lifecycle decisions
- **VMGR** is independent of COD and PM (SIL 3-4 mandatory)
- **VER** is invoked by COD (not PM) to preserve independence
- **VAL** SHALL NOT report to PM (EN 50128 Section 5.1.2.10.f)

---

## Agent-Orchestrated Workflow

### The V-Model Lifecycle

The platform follows the EN 50128 V-Model with **9 phases** (Phases 0–8):

```
Phase 0: Initialization
    @cod plan --sil <level> --project <name>
    ↓
Phase 1: Planning
    @pm execute-phase 1
    → @qua create-sqap, @cm create-scmp, @ver create-svp, @val create-svap
    ↓ @cod gate-check phase-1
Phase 2: Requirements
    @pm execute-phase 2
    → @req create-srs, @saf create-hazard-log, @cm create-baseline phase-2
    ↓ @cod gate-check phase-2
Phase 3: Architecture & Design
    @pm execute-phase 3
    → @des create-sas, @des create-sds, @des create-sis, @saf perform-fmea
    ↓ @cod gate-check phase-3
Phase 4: Implementation & Unit Testing
    @pm execute-phase 4
    → @imp implement-all, @tst create-unit-tests, @tst run-unit-tests
    → @qua review-code (invoked by PM), @ver verify-phase 4 (invoked by COD)
    ↓ @cod gate-check phase-4
Phase 5: Integration
    @pm execute-phase 5
    → @int plan-integration, @tst create-integration-tests, @tst run-integration-tests
    → @int create-integration-report, @ver verify-phase 5 (invoked by COD)
    ↓ @cod gate-check phase-5
Phase 6: Validation
    @cod invoke-val validate-phase 6
    → @val validate-phase 6
    ↓ @cod gate-check phase-6
Phase 7: Assessment (SIL 3-4 only)
    @cod invoke-assessor
    ↓ @cod gate-check phase-7
Phase 8: Deployment
    @pm execute-phase 8
    → @cm create-baseline phase-8, @cm create-release-package
    ↓ @cod finish
```

### SIL-Dependent Gate Enforcement

| SIL Level | Gate Enforcement | Override Allowed? |
|-----------|-----------------|-------------------|
| SIL 0-1 | Advisory (warnings) | Yes, with user override |
| SIL 2 | Semi-strict (justification required) | Yes, with documented justification |
| SIL 3-4 | Strict (hard block) | No — gate MUST pass before proceeding |

### How PM Coordinates Agents

When you run `@pm execute-phase <N>`, PM:

1. Reads the phase definition from `.opencode/skills/en50128-project-management/phase-definitions/`
2. Invokes each agent in dependency order using `@agent <command>` syntax
3. Runs the QUA approval loop: agent creates document → `@qua review-document` → fix if rejected → resubmit once
4. Reports phase completion to COD
5. COD performs gate check before PM proceeds to next phase

**Example — Phase 4 execution (simplified):**
```
@pm execute-phase 4

PM → @imp implement-all --sil 3
IMP → produces src/, writes C code (MISRA C compliant)

PM → @tst create-unit-tests --source src/ --sil 3
TST → produces tests/unit/

PM → @tst run-unit-tests --sil 3
TST → runs tests, reports coverage (MUST be 100% for SIL 3)

PM → @qua review-code --path src/ --sil 3
QUA → produces Code-Review-Report.md

COD → @ver verify-phase 4 --sil 3   (COD invokes, NOT PM)
VER → runs static analysis, produces Verification-Report-Phase4.md

COD → VMGR reviews Verification Report (SIL 3-4)
VMGR → approves or rejects

COD performs gate check → PASS → PM may proceed to Phase 5
```

### User Interaction Points

Users interact with **two agents** for most operations:

| Command | Who Invokes | What Happens |
|---------|-------------|--------------|
| `@cod plan --sil 3 --project X` | You | COD initializes workspace, creates LIFECYCLE_STATE.md |
| `@cod status` | You | COD reports current phase, completion %, deliverable status |
| `@cod gate-check phase-N` | You | COD verifies phase criteria and authorizes transition |
| `@pm execute-phase N` | You | PM coordinates all agents for phase N, produces all deliverables |
| `@pm status` | You | PM reports team status, active tasks, issues |
| `@pm resolve-defects phase-N` | You | PM coordinates defect resolution after VER/VAL rejection |
| `@cod finish` | You | COD performs final compliance check and marks project complete |

For specialized work, you may also invoke agents directly:

| Command | Agent | Use Case |
|---------|-------|----------|
| `@req create-srs` | REQ | Create SRS standalone (outside PM orchestration) |
| `@ver verify-phase 4` | VER | Re-verify after defect fixes |
| `@qua review-document path/to/doc.md` | QUA | Review a specific document |
| `@cm create-baseline phase-2` | CM | Baseline a specific phase |
| `@saf perform-fmea --component X` | SAF | Safety analysis for specific component |

---

## Agent Reference

### COD — Lifecycle Coordinator

**EN 50128 Basis**: Section 5.3 (Lifecycle issues and documentation)

**Commands**:

```
@cod plan --sil <0-4> --project <name>
    Initialize workspace, create LIFECYCLE_STATE.md, display V-Model plan

@cod status
    Report current phase, completion percentage, deliverable status, issues

@cod gate-check <phase-id>
    Verify phase completion criteria:
    - All deliverables present and validated
    - Approvals obtained per SIL level
    - Traceability complete (mandatory SIL 3-4)
    - VER/VAL/VMGR approvals (SIL 3-4)
    Returns: PASS (proceed) or BLOCK (criteria list)

@cod approve-requirement
    Authorize a requirement establishment or modification activity

@cod re-run <phase-id>
    Re-execute a phase after defect resolution

@cod finish
    Final compliance check, archive project, close LIFECYCLE_STATE.md
```

**Gate check criteria (SIL 3):**
- All deliverables for the phase exist in `examples/<project>/docs/`
- Document IDs follow format `DOC-XXX-YYYY-NNN`
- QUA review reports present and APPROVED
- VER verification report APPROVED by VMGR
- Traceability matrix shows 100% coverage
- Git baseline tag created for the phase

---

### PM — Project Manager

**EN 50128 Basis**: Section 5, Table B.9

**Commands**:

```
@pm execute-phase <phase-id>
    Coordinate all agents for the specified phase.
    Produces all deliverables, runs QUA approval loop, reports to COD.
    Phase IDs: 1 (Planning), 2 (Requirements), 3 (Design),
               4 (Implementation), 5 (Integration), 8 (Deployment)

@pm resolve-defects <phase-id>
    Coordinate defect resolution after VER or VAL rejection.
    Re-invokes relevant agents to fix issues, then re-submits to VER/VAL.

@pm status
    Report team status, active tasks, pending approvals, open issues.

@pm ccb-meeting --cr <change-request-id>
    Chair Change Control Board meeting for a change request.
    Produces CCB Decision Record.

@pm assign-roles --sil <0-4>
    Verify role assignments meet SIL independence requirements.
```

---

### REQ — Requirements Engineer

**EN 50128 Basis**: Section 7.2, Table A.2

**PM Orchestration Commands**:

```
@req create-srs [--based-on <system-req-path>]
    Create Software Requirements Specification from template.
    Validates with validate_srs_template.py.
    Output: docs/Software-Requirements-Specification.md

@req fix-defects --document <path> --defects <defect-list>
    Fix defects found during VER or QUA review.

@req update-traceability
    Update traceability matrix after requirements changes.
```

---

### DES — Designer

**EN 50128 Basis**: Section 7.3, Table A.3

**PM Orchestration Commands**:

```
@des create-sas
    Create Software Architecture Specification.
    Output: docs/Software-Architecture-Specification.md

@des create-sds
    Create Software Design Specification (detailed design).
    Output: docs/Software-Design-Specification.md

@des create-sis
    Create Software Interface Specifications.
    Output: docs/Software-Interface-Specifications.md

@des fix-defects --document <path> --defects <defect-list>
    Fix design defects after VER/QUA review.
```

---

### IMP — Implementer

**EN 50128 Basis**: Section 7.4, Table A.4

**PM Orchestration Commands**:

```
@imp implement-all [--sil <0-4>]
    Implement all modules from SDS in MISRA C compliant C code.
    Static allocation only (SIL 2+). No recursion (SIL 3-4).
    Output: src/<module>.c, include/<module>.h

@imp fix-defects --component <name> --defects <defect-list>
    Fix implementation defects.

@imp run-build
    Compile all source files, report errors.
    Output: build/
```

---

### TST — Tester

**EN 50128 Basis**: Sections 7.4, 7.5, 7.7, Table A.5, Table A.21

**Coverage requirements by SIL** (Table A.21):

| SIL | Statement | Branch | Condition (MC/DC) |
|-----|-----------|--------|-------------------|
| 0-1 | HR | HR | — |
| 2 | HR | M | — |
| 3-4 | M | M | M |

**PM Orchestration Commands**:

```
@tst create-unit-tests [--source <path>] [--sil <0-4>]
    Create Unity unit tests for all modules.
    Output: tests/unit/test_<module>.c

@tst run-unit-tests [--sil <0-4>]
    Execute unit tests with coverage measurement.
    Validates coverage against SIL requirements.
    Output: test-results/unit/, coverage/

@tst create-integration-tests
    Create integration test specifications and test code.
    Output: tests/integration/

@tst run-integration-tests
    Execute integration tests, record results.
    Output: test-results/integration/

@tst run-system-tests
    Execute system-level validation tests.
    Output: test-results/system/
```

---

### VER — Verifier

**EN 50128 Basis**: Section 6.2, Table A.5, Table A.19  
**Independence**: MANDATORY for SIL 3-4 — invoked by COD, NOT PM

**COD Invocation Commands**:

```
@ver verify-phase <phase-id> [--sil <0-4>]
    Perform full verification for a lifecycle phase:
    - Static analysis (Cppcheck, Clang — MANDATORY SIL 3-4)
    - Complexity analysis (Lizard — CCN ≤ 10 for SIL 3-4)
    - MISRA C compliance check
    - Coverage verification
    - Traceability verification
    Output: docs/Verification-Report-Phase<N>.md

@ver re-verify-phase <phase-id> [--sil <0-4>]
    Re-verify after defect resolution.
```

---

### VAL — Validator

**EN 50128 Basis**: Section 7.7, Table A.7  
**Independence**: MANDATORY for SIL 3-4 — SHALL NOT report to PM

**COD Invocation Commands**:

```
@val create-validation-plan
    Create Software Validation Plan (SVaP).
    Output: docs/Software-Validation-Plan.md

@val validate-phase <phase-id> [--sil <0-4>]
    Execute validation for the phase:
    - Operational scenario testing
    - System-level acceptance tests
    - Performance testing (MANDATORY SIL 3-4)
    Output: docs/Validation-Report.md

@val approve-release
    Provide formal release approval per EN 50128 Section 5.1.2.8.
```

---

### INT — Integrator

**EN 50128 Basis**: Section 7.6, Table A.6

**PM Orchestration Commands**:

```
@int plan-integration
    Create integration plan (progressive: bottom-up or top-down).
    Output: docs/Integration-Plan.md

@int create-integration-report
    Document integration test results (actual results from TST).
    Output: docs/Integration-Test-Report.md

@int fix-defects --defects <defect-list>
    Coordinate defect resolution for integration issues.
```

---

### SAF — Safety Engineer

**EN 50128 Basis**: Section 7.1, Section 6.3, Table A.8

**PM Orchestration Commands**:

```
@saf create-hazard-log [--based-on <system-hazard-log>]
    Create software-level Hazard Log.
    Output: docs/Hazard-Log.md

@saf perform-fmea [--component <name>]
    Perform Failure Mode and Effects Analysis.
    Output: docs/FMEA-Worksheet.md

@saf update-safety-requirements
    Update software safety requirements based on FMEA/FTA findings.
```

---

### QUA — Quality Assurance

**EN 50128 Basis**: Section 6.5, Table A.9

**PM Orchestration Commands**:

```
@qua review-document <path> --type <doc-type> --sil <0-4>
    Template compliance review for a document.
    Checks: Document ID, Document Control table, Approvals table,
            section completeness, content quality.
    Output: docs/QA-Review-<document-name>.md
    Returns: APPROVED or REJECTED (with finding list)

@qua review-code --path <src-path> --sil <0-4>
    Code review against EN 50128 and MISRA C checklist (124 items).
    Output: docs/Code-Review-Report.md
    Returns: APPROVED or REJECTED

@qua generate-sqap
    Create Software Quality Assurance Plan.
    Output: docs/Software-Quality-Assurance-Plan.md
```

---

### CM — Configuration Manager

**EN 50128 Basis**: Section 6.6, Table A.9  
**Note**: Configuration Management is MANDATORY for ALL SIL levels (0, 1, 2, 3, 4)

**PM Orchestration Commands**:

```
@cm create-scmp
    Create Software Configuration Management Plan.
    Output: docs/Software-Configuration-Management-Plan.md

@cm create-baseline <phase-id>
    Create a Git baseline for the specified phase.
    Tags repository: baseline-phase-<N>-<date>

@cm process-change-request --cr <cr-id>
    Process a change request through CCB workflow.
```

---

### VMGR — V&V Manager

**EN 50128 Basis**: Section 5.1.2.10e (Verifier can report to Validator)  
**Independence**: MANDATORY for SIL 3-4 — does NOT report to COD or PM

**Commands**:

```
@vmgr review-verification <phase-id>
    Technical review of Verification Report.
    Returns: APPROVED or REJECTED (with findings)

@vmgr approve-gate <phase-id>
    Provide formal V&V approval/rejection to COD for gate check.
    VMGR decisions CANNOT be overridden by COD or PM.

@vmgr status
    Report V&V status for all phases.

@vmgr independence-check
    Verify independence requirements are met for all V&V roles.
```

---

## Tool Integration

### Tool Classification

**T1 Tools** (No qualification required):
- Text editors, Git, Python scripts

**T2 Tools** (Validation required SIL 2+):
- Static analyzers (Cppcheck, Clang)
- Coverage tools (gcov, lcov)
- Complexity tools (Lizard)
- Build tools (GNU Make)

**T3 Tools** (Qualification required SIL 3-4):
- Compilers (GCC)
- Test frameworks (Unity)

### Verifying Tool Installation

```bash
source venv/bin/activate
tools/tool-validation/check-tool-versions.sh --sil 3 --verbose
```

### Key Tools Used by Agents

| Tool | Agent | Purpose | SIL Requirement |
|------|-------|---------|-----------------|
| `cppcheck --addon=misra` | VER | MISRA C static analysis | MANDATORY SIL 3-4 |
| `scan-build` (Clang) | VER | Static analysis | MANDATORY SIL 3-4 |
| `lizard --CCN 10` | VER | Complexity analysis (CCN ≤ 10) | MANDATORY SIL 3-4 |
| `gcov` / `lcov` | TST | Code coverage measurement | MANDATORY SIL 3-4 |
| `mcdc_analyzer.py` | TST | MC/DC analysis | MANDATORY SIL 3-4 |
| `validate_srs_template.py` | REQ, QUA | SRS document validation | All SILs |
| `validate_sas_sds_template.py` | DES, QUA | Architecture/design validation | All SILs |
| `validate_test_doc_template.py` | TST, QUA | Test document validation | All SILs |
| `generate_test_report.py` | TST | EN 50128 test report generation | All SILs |
| `parse_coverage_report.py` | TST, VER | Coverage validation vs. SIL | All SILs |
| `traceability_manager.py` | REQ, VER | Traceability matrix management | MANDATORY SIL 3-4 |
| `workspace.py` | COD, CM | Workspace and baseline management | All SILs |

### Running Tools Directly

Agents invoke tools automatically. If you need to run them manually:

```bash
# Static analysis
cppcheck --enable=all --addon=misra --xml --xml-version=2 src/ 2> cppcheck_report.xml
scan-build -o clang_results make

# Complexity
lizard src/ --CCN 10

# Coverage
gcc -fprofile-arcs -ftest-coverage -o test_runner src/module.c tests/unit/test_module.c
./test_runner
lcov --capture --directory . --output-file coverage.info
python3 tools/scripts/parse_coverage_report.py coverage.info --sil 3

# Document validation
python3 tools/scripts/validate_srs_template.py docs/SRS.md --sil 3
python3 tools/scripts/validate_sas_sds_template.py docs/SAS.md --sil 3

# Traceability
python3 tools/traceability_manager.py validate --sil 3
python3 tools/traceability_manager.py report --format markdown --output RTM.md
```

---

## Complete Example: SIL 3 Door Speed Monitor

This example shows the complete lifecycle for a SIL 3 component using agent orchestration.

### Inputs

Create the system-level inputs in `assets/sample_system/`:

**System-Requirements-Specification.md** (excerpt):
```markdown
# System Requirements Specification

**SYS-REQ-001**: The system SHALL monitor door closing speed continuously.
**SYS-REQ-002**: The system SHALL trigger an alarm if door speed exceeds 0.3 m/s.
**SYS-REQ-003**: The system SHALL update speed measurement every 50ms.
```

### Phase 0: Initialize

```
@cod plan --sil 3 --project DoorSpeedMonitor
```

COD creates `examples/DoorSpeedMonitor/LIFECYCLE_STATE.md` and displays the V-Model plan:
```
📁 Active Workspace: DoorSpeedMonitor (SIL 3)
   Phase: 0 (Initialization) | Completion: 0%
   Path: examples/DoorSpeedMonitor/

V-Model Plan:
  ✅ Phase 0: Initialized
  ⏳ Phase 1: Planning
  ⏳ Phase 2: Requirements
  ⏳ Phase 3: Architecture & Design
  ⏳ Phase 4: Implementation & Unit Testing
  ⏳ Phase 5: Integration
  ⏳ Phase 6: Validation
  ⏳ Phase 7: Assessment (SIL 3 — REQUIRED)
  ⏳ Phase 8: Deployment
```

### Phase 1: Planning

```
@pm execute-phase 1
```

PM coordinates:
1. `@qua generate-sqap` → `docs/Software-Quality-Assurance-Plan.md`
2. `@cm create-scmp` → `docs/Software-Configuration-Management-Plan.md`
3. `@ver create-svp` → `docs/Software-Verification-Plan.md`
4. `@val create-validation-plan` → `docs/Software-Validation-Plan.md`
5. QUA review loop: `@qua review-document` for each document
6. `@cm create-baseline phase-1`
7. PM reports to COD: Phase 1 complete

```
@cod gate-check phase-1
```

COD verifies all 4 planning documents present, validated, and reviewed. Returns PASS.

### Phase 2: Requirements

```
@pm execute-phase 2
```

PM coordinates:
1. `@req create-srs --based-on assets/sample_system/System-Requirements-Specification.md`
   - REQ produces `docs/Software-Requirements-Specification.md`
   - Runs `validate_srs_template.py` internally
2. `@saf create-hazard-log --based-on assets/sample_system/System-Hazard-Log.md`
   - SAF produces `docs/Hazard-Log.md`
3. QUA review loop for both documents
4. `@cm create-baseline phase-2`

SRS contains (generated by REQ):
```markdown
## 3. Software Requirements

**SW-REQ-001**: The system **SHALL** monitor door closing speed continuously.
- SIL: 3 | Priority: HIGH | Traceability: → SYS-REQ-001

**SW-REQ-002**: The system **SHALL** trigger an alarm if door speed exceeds 0.3 m/s.
- SIL: 3 | Priority: HIGH | Traceability: → SYS-REQ-002

**SW-REQ-003**: The system **SHALL** update speed measurement every 50ms.
- SIL: 3 | Priority: MEDIUM | Traceability: → SYS-REQ-003
```

```
@cod gate-check phase-2
```

COD verifies SRS validated, QUA approved, traceability initialized. Returns PASS.

### Phase 3: Architecture & Design

```
@pm execute-phase 3
```

PM coordinates:
1. `@des create-sas` → `docs/Software-Architecture-Specification.md`
2. `@des create-sds` → `docs/Software-Design-Specification.md`
3. `@des create-sis` → `docs/Software-Interface-Specifications.md`
4. `@saf perform-fmea --component DoorSpeedMonitor` → `docs/FMEA-Worksheet.md`
5. QUA review loop for all documents
6. `@cm create-baseline phase-3`

DES produces architecture (excerpt from SAS):
```
┌─────────────────────────────────────┐
│      DoorSpeedMonitor (Main)        │
└───────────┬─────────────────────────┘
            │
    ┌───────┴────────┬────────────┐
    │                │            │
┌───▼────┐    ┌──────▼─────┐  ┌─▼────────┐
│ Sensor │    │ SpeedCalc  │  │  Alarm   │
│ Input  │    │            │  │  Output  │
└────────┘    └────────────┘  └──────────┘
```

Complexity target: CCN ≤ 10 for all modules (SIL 3).

```
@cod gate-check phase-3
```

COD verifies SAS/SDS validated, FMEA complete, QUA approved, traceability updated. Returns PASS.

### Phase 4: Implementation & Unit Testing

```
@pm execute-phase 4
```

PM coordinates:

**IMP produces** `src/door_speed_monitor.c` (MISRA C:2012 compliant):
```c
#include <stdint.h>
#include <stdbool.h>
#include "door_speed_monitor.h"

/* MISRA C:2012 Rule 8.4: Static linkage */
static uint16_t previous_position = 0U;
static uint32_t previous_time_ms = 0U;

static uint16_t CalculateSpeed(uint16_t current_pos, uint32_t current_time)
{
    uint16_t speed = 0U;

    if (current_time > previous_time_ms) {
        uint32_t delta_time = current_time - previous_time_ms;
        int32_t delta_pos = (int32_t)current_pos - (int32_t)previous_position;

        /* Defensive: divide-by-zero protection */
        if (delta_time > 0U) {
            speed = (uint16_t)((delta_pos * 1000) / (int32_t)delta_time);
        }
    }

    previous_position = current_pos;
    previous_time_ms = current_time;

    return speed;
}

ErrorCode_t MonitorDoorSpeed(void)
{
    ErrorCode_t result = ERROR_NONE;
    uint16_t position;
    uint16_t speed;
    uint32_t current_time;

    /* Read sensor — SW-REQ-001 */
    position = ReadSensorPosition();

    /* Defensive: validate sensor reading */
    if (position == SENSOR_FAULT) {
        result = ERROR_SENSOR_FAULT;
    } else {
        current_time = GetSystemTime();
        speed = CalculateSpeed(position, current_time);

        /* Check alarm threshold — SW-REQ-002 */
        if (speed > SPEED_THRESHOLD_MM_S) {
            TriggerAlarm();
        }
    }

    return result;
}
```

**TST produces and executes** unit tests (Unity framework):
```c
void test_CalculateSpeed_NormalConditions(void)
{
    MockSensorPosition(100); MockSystemTime(0); MonitorDoorSpeed();
    MockSensorPosition(400); MockSystemTime(50);

    ErrorCode_t result = MonitorDoorSpeed();

    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    TEST_ASSERT_EQUAL(6000, GetLastSpeed());  /* 300mm / 50ms */
}

void test_AlarmTrigger_ExceedsThreshold(void)
{
    MockSensorPosition(0); MockSystemTime(0); MonitorDoorSpeed();
    MockSensorPosition(400); MockSystemTime(50);
    MonitorDoorSpeed();
    TEST_ASSERT_TRUE(IsAlarmTriggered());
}

void test_SensorFault_ReturnsError(void)
{
    MockSensorPosition(SENSOR_FAULT);
    ErrorCode_t result = MonitorDoorSpeed();
    TEST_ASSERT_EQUAL(ERROR_SENSOR_FAULT, result);
}
```

Coverage result (MUST be 100% for SIL 3):
```
Statement Coverage: 100%  ✅
Branch Coverage:    100%  ✅
Condition Coverage: 100%  ✅
```

**QUA reviews** `src/` — Code Review Report produced and APPROVED.

**COD invokes VER** (independent — not PM):
```
@ver verify-phase 4 --sil 3
```

VER produces `docs/Verification-Report-Phase4.md`:
```
Static Analysis:
  Cppcheck 2.13.0:   0 issues  ✅
  Clang 18.x:        0 issues  ✅

Complexity:
  Lizard:    max CCN = 5 (≤10 required)  ✅

MISRA C:
  Mandatory violations: 0  ✅
  Required violations:  0  ✅

Coverage:
  Statement: 100%  ✅  Branch: 100%  ✅  Condition: 100%  ✅

Overall: PASS
```

**VMGR reviews and approves** Verification Report (SIL 3 required).

`@cm create-baseline phase-4`

```
@cod gate-check phase-4
```

COD verifies all deliverables, VMGR approval received. Returns PASS.

### Phase 5: Integration

```
@pm execute-phase 5
```

PM coordinates:
1. `@int plan-integration` → `docs/Integration-Plan.md`
2. `@tst create-integration-tests` → `tests/integration/`
3. `@tst run-integration-tests` → `test-results/integration/`
4. `@int create-integration-report` → `docs/Integration-Test-Report.md`
5. QUA review loop
6. COD invokes `@ver verify-phase 5`
7. VMGR approves
8. `@cm create-baseline phase-5`

```
@cod gate-check phase-5
```

### Phase 6: Validation

COD invokes VAL (independent):
```
@val validate-phase 6 --sil 3
```

VAL produces `docs/Validation-Report.md`:
- Operational scenario tests: PASS
- Performance tests (MANDATORY SIL 3): PASS
- Functional/black-box tests: PASS
- Overall: **APPROVED FOR RELEASE**

VMGR provides final V&V approval to COD.

```
@cod gate-check phase-6
```

### Phase 7: Assessment (SIL 3 — Required)

Independent assessor reviews all evidence. COD coordinates.

```
@cod gate-check phase-7
```

### Phase 8: Deployment

```
@pm execute-phase 8
```

PM coordinates:
1. `@cm create-baseline phase-8`
2. `@cm create-release-package`
3. PM produces final release package

```
@cod finish
```

COD performs final compliance check and archives project.

### What Was Produced

All deliverables in `examples/DoorSpeedMonitor/`:

**Planning (Phase 1)**:
- `docs/Software-Quality-Assurance-Plan.md`
- `docs/Software-Configuration-Management-Plan.md`
- `docs/Software-Verification-Plan.md`
- `docs/Software-Validation-Plan.md`

**Requirements & Safety (Phase 2)**:
- `docs/Software-Requirements-Specification.md`
- `docs/Hazard-Log.md`

**Design (Phase 3)**:
- `docs/Software-Architecture-Specification.md`
- `docs/Software-Design-Specification.md`
- `docs/Software-Interface-Specifications.md`
- `docs/FMEA-Worksheet.md`

**Implementation (Phase 4)**:
- `src/door_speed_monitor.c` — MISRA C compliant
- `include/door_speed_monitor.h`
- `tests/unit/test_door_speed_monitor.c`
- `test-results/unit/` — 100% coverage
- `docs/Code-Review-Report.md`
- `docs/Verification-Report-Phase4.md`

**Integration (Phase 5)**:
- `docs/Integration-Plan.md`
- `tests/integration/`
- `docs/Integration-Test-Report.md`
- `docs/Verification-Report-Phase5.md`

**Validation (Phase 6)**:
- `docs/Validation-Report.md`

**Deployment (Phase 8)**:
- Release package with all evidence
- Git baseline tags for all phases

**Traceability**: SYS-REQ → SW-REQ → Architecture → Code → Tests (100% coverage)

---

## Best Practices

### 1. Let COD and PM Drive the Lifecycle

**Do not** manually create documents or invoke individual agents out of sequence.  
**Do** use `@pm execute-phase N` to let PM coordinate agents in the correct order.

### 2. Maintain Traceability from Day 1

REQ initializes the traceability matrix in Phase 2. VER validates it in each subsequent phase. Do not skip this — it is MANDATORY for SIL 3-4.

### 3. Respect the QUA Approval Loop

QUA reviews every document before it is submitted to VER. The loop is:
1. Agent creates document
2. `@qua review-document` — if REJECTED, agent fixes and resubmits once
3. If rejected again → PM escalates to COD

### 4. Preserve VER and VAL Independence (SIL 3-4)

- **VER** is always invoked by **COD**, not PM
- **VAL** SHALL NOT report to PM (EN 50128 5.1.2.10.f)
- **VMGR** is independent of both COD and PM
- Do not try to route VER/VAL activities through PM for SIL 3-4

### 5. Follow SIL-Specific Constraints

| Constraint | SIL 2 | SIL 3-4 |
|------------|-------|---------|
| Dynamic memory (`malloc`) | Forbidden | Forbidden |
| Recursion | Forbidden | Forbidden |
| Complexity (CCN) | ≤ 15 | ≤ 10 |
| Statement coverage | HR | MANDATORY (100%) |
| Branch coverage | MANDATORY | MANDATORY (100%) |
| Condition coverage | — | MANDATORY (100%) |
| Independent VER/VAL | Recommended | MANDATORY |
| Static analysis | Highly Recommended | MANDATORY |
| MISRA C | MANDATORY | MANDATORY |

### 6. Validate Documents Early

Agents run `validate_srs_template.py`, `validate_sas_sds_template.py`, and `validate_test_doc_template.py` automatically. If you edit documents manually, re-run validation before submitting for QUA review.

### 7. Never Fabricate Test Results

INT must document **actual** test results from TST. INT does not create test code or run tests. TST executes tests and provides results to INT. Fabricating results violates EN 50128 and is a blocking gate failure.

### 8. Use Meaningful Git Commits and Baselines

CM creates baseline tags at each phase gate. Use descriptive commit messages referencing requirement IDs (e.g., `SW-REQ-001`). This is part of the configuration management evidence.

---

## Troubleshooting

### Problem: COD gate-check fails — deliverable missing

**Symptom**: `@cod gate-check phase-N` reports a missing document

**Solution**:
```
@pm execute-phase N    (re-run the phase — PM will identify what is missing)
```
Or invoke the specific agent to produce the missing document:
```
@req create-srs        (if SRS is missing)
@qua review-document docs/SRS.md --type srs --sil 3
```

---

### Problem: VER verification rejected

**Symptom**: `@ver verify-phase N` returns REJECTED with findings

**Solution**:
```
@pm resolve-defects <phase-id>
```
PM coordinates the relevant agents (IMP for code issues, DES for design issues, REQ for requirements gaps) to fix defects, then re-submits to VER.

---

### Problem: MISRA C violations

**Symptom**: Cppcheck reports MISRA C violations in VER report

**Solution**: IMP fixes violations. Reference:
```bash
cppcheck --enable=all --addon=misra --verbose src/
# Check: .opencode/skills/en50128-implementation/resources/misra-c-2012-rules.md
```
Zero mandatory violations are required for SIL 2+. Required violations must be justified and documented in SDS.

---

### Problem: Coverage < 100% (SIL 3-4)

**Symptom**: `parse_coverage_report.py` reports insufficient coverage

**Solution**:
```bash
genhtml coverage.info --output-directory coverage_html
# Open coverage_html/index.html — uncovered lines shown in red
# Add tests for uncovered paths
```
Then: `@tst run-unit-tests --sil 3` to re-measure.

---

### Problem: Complexity > 10 (SIL 3-4)

**Symptom**: Lizard reports CCN > 10 in VER report

**Solution**: `@imp fix-defects` with refactoring guidance from `@des`. Options:
- Extract sub-functions
- Simplify conditional logic
- Use lookup tables

Then: `@ver re-verify-phase N`

---

### Problem: QUA review rejected

**Symptom**: `@qua review-document` returns REJECTED

**Solution**: Read the finding list from the QA Review Report. Common issues:
- Missing Document ID (`DOC-XXX-YYYY-NNN` format required)
- Missing Document Control table
- Missing Approvals table with SIL-required roles
- Section incomplete or using informal language (SHALL/SHOULD/MAY required for requirements)

The originating agent (REQ, DES, etc.) fixes findings and resubmits to QUA once.

---

### Problem: VMGR rejects verification report (SIL 3-4)

**Symptom**: `@vmgr review-verification` returns REJECTED

**Solution**: VMGR decisions cannot be overridden by COD or PM. Read the VMGR rejection findings carefully.
```
@pm resolve-defects <phase-id>    (PM coordinates targeted fixes)
@ver re-verify-phase <phase-id>   (COD invokes VER after fixes)
@vmgr review-verification <phase-id>   (VMGR re-reviews)
```

---

### Getting Help

1. **`@cod status`** — check current lifecycle state and what is blocking
2. **`LIFECYCLE.md`** — complete V-Model lifecycle guide with phase definitions
3. **`TOOLS.md`** — tool catalog with T1/T2/T3 classification and usage
4. **`std/EN50128-2011.md`** — EN 50128 standard (LLM-friendly, 7,256 lines)
5. **`AGENTS.md`** — full agent role definitions with EN 50128 references

---

## References

### Platform Documentation

| Document | Description | Location |
|----------|-------------|----------|
| **LIFECYCLE.md** | Complete V-Model lifecycle | `docs/LIFECYCLE.md` |
| **TOOLS.md** | Tool catalog (T1/T2/T3) | `TOOLS.md` |
| **AGENTS.md** | Role definitions | `AGENTS.md` |
| **USER-GUIDE.md** | This document | `docs/USER-GUIDE.md` |

### Standards

| Standard | Description | Location |
|----------|-------------|----------|
| **EN 50128:2011** | Railway Software Standard | `std/EN50128-2011.md` (7,256 lines) |
| **EN 50126-1:2017** | RAMS Part 1 | `std/EN 50126-1-2017.md` |
| **EN 50126-2:2017** | RAMS Part 2 | `std/EN 50126-2-2017.md` |
| **MISRA C:2012** | C Coding Standard | `.opencode/skills/en50128-implementation/` |

### Agents (13 Total)

| Agent | Role | EN 50128 Basis | Independence |
|-------|------|----------------|--------------|
| `@cod` | Lifecycle Coordinator | Section 5.3 | — |
| `@pm` | Project Manager | Section 5, Table B.9 | — |
| `@req` | Requirements Engineer | Section 7.2 | — |
| `@des` | Designer | Section 7.3 | — |
| `@imp` | Implementer | Section 7.4 | — |
| `@tst` | Tester | Sections 7.4, 7.5 | — |
| `@ver` | Verifier | Section 6.2 | MANDATORY SIL 3-4 |
| `@val` | Validator | Section 7.7 | MANDATORY SIL 3-4 |
| `@int` | Integrator | Section 7.6 | — |
| `@saf` | Safety Engineer | Sections 7.1, 6.3 | — |
| `@qua` | Quality Assurance | Section 6.5 | — |
| `@cm` | Configuration Manager | Section 6.6 | — |
| `@vmgr` | V&V Manager | Section 5.1.2.10e | MANDATORY SIL 3-4 |

### Tools

| Tool | Agent | Location |
|------|-------|----------|
| `traceability_manager.py` | REQ, VER | `tools/traceability_manager.py` |
| `workflow_manager.py` | QUA, CM | `tools/workflow_manager.py` |
| `workspace.py` | COD, CM | `tools/workspace.py` |
| `validate_srs_template.py` | REQ, QUA | `tools/scripts/` |
| `validate_sas_sds_template.py` | DES, QUA | `tools/scripts/` |
| `validate_test_doc_template.py` | TST, QUA | `tools/scripts/` |
| `generate_test_report.py` | TST | `tools/scripts/` |
| `parse_coverage_report.py` | TST, VER | `tools/scripts/` |
| `mcdc_analyzer.py` | TST | `tools/mcdc/` |
| `check-tool-versions.sh` | All | `tools/tool-validation/` |
| `run-all-validations.sh` | VER | `tools/tool-validation/` |

---

**END OF USER GUIDE**

**Version**: 3.0  
**Last Updated**: 2026-03-15  
**Platform Status**: Production Ready  
**Questions?** Run `@cod status` or check `LIFECYCLE.md`, `TOOLS.md`, `AGENTS.md`

**Ready to start?**
```
@cod plan --sil 3 --project MyRailwayComponent
```

---

## EN 50128 Compliance Reference

### Safety Integrity Levels (SIL)

EN 50128 defines five SIL levels based on risk:

| SIL | Risk Level | Hazard Impact | Tolerable Hazard Rate |
|-----|------------|---------------|----------------------|
| 4 | Very High | Catastrophic - Multiple fatalities | 10^-9 to 10^-8 /hour |
| 3 | High | Critical - Single fatality | 10^-8 to 10^-7 /hour |
| 2 | Medium | Marginal - Serious injuries | 10^-7 to 10^-6 /hour |
| 1 | Low | Negligible - Minor injuries | 10^-6 to 10^-5 /hour |
| 0 | None | Non-safety related | No requirement |

### Development Techniques by SIL (Tables A.3, A.4)

#### Requirements Engineering

- Structured methods: HR (all SILs)
- Semi-formal methods: HR (SIL 3-4)
- Formal methods: R (SIL 3-4)

#### Design

- Modular design: M (SIL 2-4), HR (SIL 0-1)
- Structured design: M (SIL 2-4), HR (SIL 0-1)
- Defensive programming: M (SIL 3-4), HR (SIL 0-2)

#### Coding Standards

- Coding standards: M (all SILs)
- Structured programming: M (SIL 2-4), HR (SIL 0-1)
- No dynamic objects: HR (SIL 3-4)
- No dynamic variables: R (SIL 3-4)

### Verification and Coverage Requirements (Table A.5, Table A.21)

#### Code Coverage by SIL

| Coverage Type | SIL 0-1 | SIL 2 | SIL 3-4 |
|---------------|---------|-------|---------|
| Statement | HR | HR | M |
| Branch | HR | M | M |
| Condition | R | HR | M |
| MC/DC | - | R | HR |

#### Testing Techniques

- Boundary value analysis: M (SIL 3-4), HR (SIL 0-2)
- Equivalence partitioning: HR (all SILs)
- Error guessing: R (all SILs)
- Fault injection: HR (SIL 2-4)

### Independence Requirements

#### SIL 3-4 Requirements

- Independent verification team (Verifier MANDATORY)
- Independent validation team (Validator MANDATORY, cannot report to PM)
- Independent safety assessor (Assessor MANDATORY, often external)
- Separation of design and test responsibilities

### Common Compliance Challenges

1. **Traceability** — Use the built-in traceability system in SRS; RTM is implicit per EN 50128
2. **Independence** — Ensure `@ver` and `@val` agents operate independently from `@imp`/`@des`
3. **Code Coverage** — Use `gcov`/`lcov` with `@tst`; aim for 100% statement/branch/condition (SIL 3-4)
4. **Documentation** — Use `@qua review-document` to check compliance before each phase gate
5. **Tool Qualification** — See `TOOLS.md` for T1/T2/T3 tool confidence levels

### Best Practices

1. **Start with Planning** — Run `@cod plan` first; define SIL levels before writing any requirements
2. **Apply Defensive Programming** — Validate all inputs, check all outputs, handle all errors; use assertions
3. **Implement Strong Configuration Management** — `@cm create-baseline` at each phase gate
4. **Perform Regular Reviews** — `@qua review-document` after every major deliverable
5. **Maintain Evidence** — Keep all verification records; `@ver` evidence is mandatory for SIL 3-4

### Assessment and Certification

**Independent Safety Assessment (ISA)** — Required for SIL 1-4:
- Review of development process
- Review of technical documentation
- Review of verification evidence
- Assessment report with approval/conditions

**Certification Bodies**: National railway authorities, Notified bodies (e.g., TÜV, Lloyd's Register), Independent safety assessors

### Change Management

**Change Process**:
1. Change request submitted
2. Impact analysis performed (safety impact assessed)
3. Change approved by CCB (via `@pm` / Change Control Board)
4. Implementation with verification (`@imp`, `@ver`)
5. Regression testing (`@tst`)
6. Documentation updated
7. Change deployed

**Version Management**:
- Major version: Significant changes requiring re-certification
- Minor version: Bug fixes and minor enhancements
- Patch version: Critical safety patches

### Abbreviations

| Abbreviation | Meaning |
|---|---|
| CCB | Change Control Board |
| CM | Configuration Management |
| FCA | Functional Configuration Audit |
| FMEA | Failure Mode and Effects Analysis |
| FTA | Fault Tree Analysis |
| ISA | Independent Safety Assessor |
| MC/DC | Modified Condition/Decision Coverage |
| PCA | Physical Configuration Audit |
| QA | Quality Assurance |
| RAMS | Reliability, Availability, Maintainability, Safety |
| SCMP | Software Configuration Management Plan |
| SIL | Safety Integrity Level |
| SQAP | Software Quality Assurance Plan |
| SRS | Software Requirements Specification |
| V&V | Verification and Validation |

### Standards References

- EN 50128:2011 - Railway applications - Software for railway control and protection systems
- EN 50126-1:2017 - Railway applications - RAMS (Part 1)
- EN 50126-2:2017 - Railway applications - RAMS (Part 2)
- EN 50129:2018 - Safety related electronic systems for signalling
- IEC 61508 - Functional safety of E/E/PE safety-related systems
- MISRA C:2012 - Guidelines for the use of the C language in critical systems
