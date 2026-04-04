# Examples Directory

This directory contains **actual EN 50128 project instances** developed using the EN 50128 platform.

## Purpose

Each subdirectory represents a complete, self-contained railway software project developed according to EN 50128:2011 standards. These are real development instances, not templates.

## Structure

```
examples/
├── README.md                          # This file
├── TDC/                               # Active SIL 3 Train Door Control project (Phase 6 complete; Phase 7 authorized)
│   ├── README.md                     # Project overview and status
│   ├── LIFECYCLE_STATE.md            # Lifecycle tracking
│   ├── Makefile                      # Build system
│   ├── src/                          # C source code (21 .c files, 9 .h files, 99 functions)
│   ├── tests/                        # 203 component tests + 50 integration tests
│   └── docs/                         # EN 50128 deliverables
│       ├── system/                   # System-level documents (EN 50126/50129)
│       ├── phase-1-planning/         # SQAP, SCMP, SVP, SVaP + reports
│       ├── phase-2-requirements/     # SRS, Overall Software Test Spec + reports
│       ├── phase-3-architecture-design/ # SAS, SDS, SIS, Integration Test Specs + reports
│       ├── phase-4-component-design/ # Component Design Spec, Component Test Spec + reports
│       ├── phase-5-implementation-testing/ # Source code verification + test reports
│       ├── phase-6-integration/      # SW + HW/SW Integration Test Reports + QEMU plan
│       ├── safety/                   # Hazard Log, FMEA, FTA
│       ├── traceability/             # Requirements Traceability Matrix
│       ├── change-control/           # CCRs (CCR-SVP-001)
│       └── non-conformance/          # NCRs (NCR-P5-001/002/003 — all closed)
│
└── [your-project-name]/               # Your EN 50128 project
    ├── src/                          # Your source code
    ├── test/                         # Your tests
    ├── docs/                         # Your documentation
    │   └── system/                   # System documents (mandatory per EN 50128 7.2.2)
    ├── LIFECYCLE_STATE.md            # Created by @cod plan
    └── ...
```

> **Archived projects**: `train_door_control2` and `test_eval_project` have been moved to
> `deprecated/` at the repository root. TDC is the active reference project.

## Creating a New Project

### Prerequisites: System-Level Documents (EN 50128 Section 7.2.2)

Before starting any EN 50128 project, you need **4 system-level input documents**:
1. System Requirements Specification
2. System Architecture Description
3. System Safety Plan
4. System Safety Requirements Specification

**Two Options**:

**Option A: Use Platform Templates** (Recommended):
```bash
# Generate automatically with COD after initialization
@cod generate-system

# Or manually copy from platform templates:
mkdir -p examples/my_project/docs/system
cp assets/sample_system/*.md examples/my_project/docs/system/
# Then customize for your system
```

**Option B: Study the TDC Reference**:
```bash
# See the 4 system documents produced for TDC
ls examples/TDC/docs/system/
# Review them to understand structure and expected content
```

### Option 1: Use OpenCode Agents (Recommended)

Start a new EN 50128 project using lifecycle coordinator and agents:

```bash
# 1. Initialize project with COD
@cod plan --sil 3 --project my_railway_project

# 2. Generate system-level input documents
@cod generate-system

# 3. Execute each phase via PM
@pm execute-phase 1    # Planning: SQAP, SCMP, SVP, SVaP
@cod gate-check phase-1

@pm execute-phase 2    # Requirements: SRS, Overall Software Test Spec
@cod gate-check phase-2

@pm execute-phase 3    # Architecture & Design: SAS, SDS, Interface Specs
@cod gate-check phase-3

@pm execute-phase 4    # Component Design
@cod gate-check phase-4

@pm execute-phase 5    # Implementation + Unit Testing
@cod gate-check phase-5

@pm execute-phase 6    # Integration
@cod gate-check phase-6

@pm execute-phase 7    # Overall Testing / Validation
@cod gate-check phase-7

# Phase 8: Assessment — facilitated by PM, conducted by independent assessor
@cod gate-check phase-8

@pm execute-phase 9    # Deployment
@cod gate-check phase-9
```

**Two entry points only**: `@cod` (lifecycle authority) and `@pm` (phase execution).
All other agents are orchestrated internally.

### Option 2: Manual Setup

Create project structure manually:

```bash
cd examples
mkdir -p my_project/{src,test,docs,build}
cd my_project

# Create initial files
touch README.md
touch Makefile

# Initialize lifecycle
@cod plan --sil 3 --project my_project
```

## Available Examples

### TDC — Train Door Control (Active Reference Project)

**Path**: `examples/TDC/`

**Description**: SIL 3 train door control system. The primary active example demonstrating
the full EN 50128 platform workflow through Phases 0–2 with complete V&V approval chains.

**SIL Level**: 3

**Current Status**: Phase 6 (Integration) PASSED — Phase 7 (Validation) authorized

**Lifecycle Progress**:
- Phase 0 (Initialization): Complete — 4 system-level documents generated
- Phase 1 (Planning): PASSED — SQAP, SCMP, SVP, SVaP with QUA/VER/VAL/VMGR approval chain
- Phase 2 (Requirements): PASSED — SRS (53 requirements, 21 safety-critical), Overall SW Test Spec (133 test cases), full QUA→VER→VAL→VMGR→COD gate chain
- Phase 3 (Architecture & Design): PASSED — SAS, SDS, SIS; 8 components; FMEA/FTA; 2oo2 dual-channel design; 379 traceability links
- Phase 4 (Component Design): PASSED — Component Design Spec, Component Test Spec; 30 modules; zero defects
- Phase 5 (Implementation & Testing): PASSED (2nd attempt) — 21 source files, 99 functions; 203 test cases; 87.9% stmt / 83.9% branch coverage; MISRA C compliant; 3 NCRs raised and closed
- Phase 6 (Integration): PASSED — 50/50 integration tests PASS (28 SW + 22 HW/SW); 90.3% stmt / 98.3% branch; QEMU ARM emulator pre-validation environment integrated; 4 HIL-pending items tracked (VAL-C-001 MANDATORY for Phase 7 gate)
- Phase 7 (Validation): AUTHORIZED 2026-04-04 — not yet started

**Key Documents**:
- `docs/system/` — 4 system-level input documents (EN 50126/50129)
- `docs/phase-1-planning/` — SQAP, SCMP, SVP v1.1, SVaP + phase reports
- `docs/phase-2-requirements/` — SRS, OTSTSPEC + verification/validation reports
- `docs/phase-3-architecture-design/` — SAS, SDS, SIS, Integration Test Specs + verification reports
- `docs/phase-4-component-design/` — Component Design Spec, Component Test Spec + reports
- `docs/phase-5-implementation-testing/` — Source code, 203 test cases, coverage reports; NCR resolutions
- `docs/phase-6-integration/` — SW + HW/SW Integration Test Reports; QEMU Integration Plan + Tool Validation Report
- `docs/safety/` — Hazard-Log.md, FMEA-Report.md, FTA-Report.md
- `docs/traceability/` — Requirements Traceability Matrix (100% SRS→SAS→SDS→tests)
- `docs/change-control/` — CCR-SVP-001 (SVP correction, formally approved)
- `docs/non-conformance/` — NCR-P5-001/002/003 (all closed)

**What TDC demonstrates**:
- Complete `@cod plan` → `@cod generate-system` → `@pm execute-phase N` → `@cod gate-check phase-N` workflow through Phase 6
- Two-track gate model: QUA check → VER approval → VAL concurrence → VMGR final decision → COD gate pass
- NCR corrective action process (3 NCRs raised, root-caused, and closed with evidence)
- SVP formal change control (CCR-SVP-001: Table A.21 correction for SIL 3 coverage levels)
- QEMU ARM emulator integration for HIL pre-validation (T1/T2 tool qualification)
- Stub-based component testing with coverage gap justification (EN 50128 Table A.21 Req 2+4)
- Correct document naming convention (`phase-N-<name>/` directories)
- Full traceability: system requirements → software requirements → test cases (100%)
- Proper independence: VMGR approval independent from COD/PM

**See Also**:
- `TDC/LIFECYCLE_STATE.md` — Current lifecycle state and phase history

---

## Project Naming Conventions

When creating new projects in `examples/`, follow these naming conventions:

### Directory Names
- Use uppercase abbreviations for acronym-based projects: `TDC`, `ATP`, `ATC`
- Use lowercase with underscores for descriptive names: `signal_interlocking`, `braking_system`
- Be descriptive but concise

### Project Structure (Standard)
```
your_project/
├── README.md              # Project overview, SIL level, status
├── LIFECYCLE_STATE.md     # Created by @cod plan, tracks phase progress
├── Makefile               # Build system (added at Phase 5)
├── docs/                  # Documentation
│   ├── system/            # System-level documents (EN 50126/50129) ⚠️ REQUIRED
│   │   ├── System-Requirements-Specification.md
│   │   ├── System-Architecture-Description.md
│   │   ├── System-Safety-Plan.md
│   │   └── System-Safety-Requirements-Specification.md
│   ├── phase-1-planning/  # SQAP, SCMP, SVP, SVaP
│   │   └── reports/       # QUA, VER, VAL, VMGR phase reports
│   ├── phase-2-requirements/
│   │   └── reports/
│   ├── phase-3-design/
│   │   └── reports/
│   ├── phase-4-component-design/
│   │   └── reports/
│   ├── phase-5-implementation/
│   │   └── reports/
│   └── safety/
│       └── Hazard-Log.md
├── src/                   # C source code (added at Phase 5)
│   ├── *.c
│   ├── *.h
│   └── common/
├── test/                  # Unit tests (added at Phase 5)
│   ├── test_*.c
│   └── unity_config.h
├── build/                 # Build artifacts (gitignored)
└── lib/                   # External libraries (Unity, etc.)
```

**⚠️ CRITICAL**: The `docs/system/` directory with 4 system documents is **MANDATORY**
per EN 50128 Section 7.2.2. Use `@cod generate-system` or copy from `assets/sample_system/`.

---

## SIL Level Guidelines

| SIL | Risk Level | Example Projects | Key Techniques |
|-----|------------|------------------|----------------|
| **4** | Very High | Train control, ATP | Formal methods (HR), most stringent coverage |
| **3** | High | Door control, signaling | Structured methodology (M), independent V&V (M) |
| **2** | Medium | Passenger info with safety | MISRA C (M), branch coverage (M) |
| **1** | Low | Monitoring systems | Statement coverage (HR) |
| **0** | None | Administrative systems | Minimal requirements |

**Independence Requirements (Critical for SIL 3-4)**:
- Verifier MUST be independent of implementer
- Validator MUST be independent of designer/implementer
- Safety assessor MUST be independent of development team

---

## Development Workflow

For each project in `examples/`, follow the EN 50128 V-Model lifecycle:

```bash
# Initialize (Phase 0)
@cod plan --sil 3 --project your_project
@cod generate-system

# Planning (Phase 1)
@pm execute-phase 1
@cod gate-check phase-1

# Requirements (Phase 2)
@pm execute-phase 2
@cod gate-check phase-2

# Architecture & Design (Phase 3)
@pm execute-phase 3
@cod gate-check phase-3

# Component Design (Phase 4)
@pm execute-phase 4
@cod gate-check phase-4

# Implementation + Unit Testing (Phase 5)
@pm execute-phase 5
@cod gate-check phase-5

# Integration (Phase 6)
@pm execute-phase 6
@cod gate-check phase-6

# Validation (Phase 7)
@pm execute-phase 7
@cod gate-check phase-7

# Assessment (Phase 8 — independent assessor)
@cod gate-check phase-8

# Deployment (Phase 9)
@pm execute-phase 9
@cod gate-check phase-9
```

Check progress at any time:
```bash
@cod status   # Lifecycle state and phase progress
@pm status    # Project coordination status
```

---

## Quality Requirements

All projects in `examples/` MUST meet these quality standards:

### Code Quality (SIL 2+)
- MISRA C:2012 compliant
- Static memory allocation only (no malloc/free)
- Cyclomatic complexity ≤ 10 (SIL 3-4) or ≤ 15 (SIL 2)
- Defensive programming (validate inputs, check returns)
- No recursion (highly recommended SIL 3-4)

### Test Coverage (by SIL)
- **SIL 0-1**: Statement (HR), Branch (HR)
- **SIL 2**: Statement (HR), Branch (M)
- **SIL 3-4**: Statement (M), Branch (M), Condition/MC/DC (HR — Table A.21)

### Documentation
- README.md with project overview and SIL level
- Requirements specification (SRS)
- Architecture specification (SAS)
- Design specification (SDS)
- Test specifications and reports
- Safety analysis (Hazard Log, FMEA/FTA for SIL 2+)

---

## Building and Testing

### Standard Makefile Targets

All projects should support these targets:

```bash
make              # Build source code
make test         # Build and run unit tests
make coverage     # Generate coverage report
make clean        # Remove build artifacts
make static       # Run static analysis (cppcheck)
make complexity   # Check cyclomatic complexity (lizard)
```

### Unity Test Framework

Projects use Unity for unit testing:

- **Include**: `lib/Unity/` (vendored)
- **Test files**: `test/test_*.c`
- **Configuration**: `test/unity_config.h`
- **Assertions**: `TEST_ASSERT_EQUAL()`, `TEST_ASSERT_TRUE()`, etc.

---

## Best Practices

### 1. Keep Projects Self-Contained
Each project should be independently buildable:
```bash
cd examples/your_project
make test  # Should work without additional setup
```

### 2. Document Traceability
Maintain traceability in code comments:
```c
/**
 * @brief Opens the train doors safely
 * @traceto REQ-FUNC-004, DES-MOD-002
 */
error_t door_open(door_t* door);
```

### 3. Use Consistent Error Handling
```c
typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER,
    ERROR_INVALID_PARAMETER,
    ERROR_OUT_OF_RANGE,
    ERROR_HARDWARE_FAULT
} error_t;

error_t result = subsystem_function();
if (result != SUCCESS) {
    return result;
}
```

### 4. Safety-Critical Patterns
- **Input validation**: Check all pointers, ranges, states
- **Fail-safe defaults**: Default to safe state on error
- **Redundancy**: Duplicate critical checks
- **Watchdogs**: Implement timeout monitoring
- **Self-tests**: Periodic health checks

---

## Support and Resources

### EN 50128 Platform Resources
- **Main README**: `../../README.md` — Platform overview
- **User Guide**: `../../docs/USER-GUIDE.md` — Complete user guide (start here)
- **Lifecycle Guide**: `../../LIFECYCLE.md` — V-Model phases (0–10)
- **Agent Reference**: `../../AGENTS.md` — 14 agent roles
- **Workflow**: `../../WORKFLOW.md` — Authority structure, two-track model
- **System Templates**: `../../assets/sample_system/` — System document templates
- **Standards**: `../../std/EN50128-2011.md` — Full EN 50128 standard

### External Resources
- Unity Test Framework: https://github.com/ThrowTheSwitch/Unity
- MISRA C:2012 Guidelines: https://www.misra.org.uk
- EN 50128:2011 Standard: Official standard document
- EN 50126:2017 RAMS: System-level safety management

### Getting Help
- Review the active example: `TDC/`
- Use OpenCode agents: `@cod`, `@pm` (entry points)
- Check system document templates: `assets/sample_system/README.md`
- Follow the user guide: `docs/USER-GUIDE.md`
- Review lifecycle phases: `LIFECYCLE.md`

---

## Summary

- **`examples/`** = Real EN 50128 project instances
- **`TDC/`** = Active reference project (SIL 3, Phases 1–6 complete; Phase 7 authorized)
- **Each project** = Self-contained, fully documented, compliant
- **Use agents** = `@cod` and `@pm` (entry points); all others orchestrated internally
- **Follow standards** = MISRA C, EN 50128 technique tables
- **Maintain quality** = High coverage, low complexity, defensive programming

**Start your EN 50128 project here.**
