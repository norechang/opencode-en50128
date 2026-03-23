---
name: en50128-lifecycle-examples
description: Complete lifecycle workflow examples for COD — SIL 3 full project, SIL 0-1 prototyping, SIL 2 iterative development
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  role: lifecycle-coordinator
---

# COD Lifecycle Workflow Examples

**Load trigger**: Load this skill when a user asks for a workflow example, or when COD needs
to illustrate the command sequence for a complete lifecycle or a specific SIL level.

---

## Example 1: Complete SIL 3 Project Workflow

```bash
# Phase 0: Initialization
@cod plan --sil 3 --project train_door_control
# Creates LIFECYCLE_STATE.md; sets Strict Gatekeeper mode

# Generate system-level documents (select from TYPICAL-SYSTEMS.md catalogue)
@cod generate-system
# Generates: System-Requirements-Specification.md, System-Architecture-Description.md,
#            System-Safety-Requirements-Specification.md, System-Safety-Plan.md
#            → docs/system/

# Phase 1: Planning
@pm execute-phase 1
# PM: SQAP, SCMP
# COD coordinates independently: VMGR → VER (SVP); VMGR (SVaP)  [independence requirement]
@cod gate-check planning

# Phase 2: Requirements  [USER APPROVAL required before REQ activities]
@pm execute-phase 2
# PM → REQ (SRS from system docs), SAF (hazard analysis), TST (Overall SW Test Spec)
# Track B: COD → VMGR → VER → QUA → VMGR → VAL → QUA → VMGR → COD
@cod gate-check requirements

# Phase 3: Architecture & Design
@pm execute-phase 3
# PM → DES (SAS, SDS, interface specs), SAF (FMEA/FTA update)
# Track B: full approval chain
@cod gate-check design

# Phase 4: Component Design
@pm execute-phase 4
# PM → DES (Component Design Specs, Component Test Specs)
# Track B: VER + VMGR approval
@cod gate-check component-design

# Phase 5: Implementation & Unit Testing
@pm execute-phase 5
# PM → IMP (C code, MISRA C:2012, complexity ≤10), TST (unit tests, 100% branch + condition)
# QUA code review (mandatory); VER static analysis; VMGR approval
@cod gate-check implementation-testing

# Phase 6: Integration
@pm execute-phase 6
# PM → INT (integration), TST (integration tests, performance)
# Track B: full approval chain
@cod gate-check integration

# Phase 7: Validation  [COD coordinates VAL directly — PM has no role]
@pm execute-phase 7
# COD → VAL (system testing, acceptance) → QUA → VMGR
# VMGR approval required; VMGR decision cannot be overridden
@cod gate-check validation

# Phase 8: Assessment (mandatory SIL 1–4, §6.4.1.1; SIL 0 exempt §6.4.1.2)
# External ISA/ASR reviews all lifecycle artifacts — no platform agent for this role
# COD monitors for ASR completion signal (manual entry in LIFECYCLE_STATE.md)
@cod gate-check assessment

# Phase 9: Deployment
@pm execute-phase 9
# PM → CM (final baseline, release package, deployment records)
@cod gate-check deployment

# Status at any time
@cod status
```

---

## Example 2: Quick Prototyping (SIL 0-1)

```bash
@cod plan --sil 0 --project prototype   # Optional for SIL 0-1 (Advisory mode)

@pm execute-phase 2   # Requirements (no mandatory user approval gate)
@pm execute-phase 3   # Basic design
@pm execute-phase 5   # Implement and test (statement + branch coverage HR)
@pm execute-phase 6   # Integration
@pm execute-phase 7   # Validation
@cod gate-check validation   # COD provides warnings; does not block transitions
```

---

## Example 3: Iterative Development (SIL 2)

```bash
@cod plan --sil 2 --project iterative_system
@cod generate-system

@pm execute-phase 1   # Planning: SQAP, SCMP, SVP, SVaP
@cod gate-check planning

# First iteration
@pm execute-phase 2   # Requirements (user approval required at SIL 2)
@cod gate-check requirements   # Semi-strict: justification required if incomplete

@pm execute-phase 3   # Architecture & Design
@cod gate-check design

@pm execute-phase 4   # Component Design
@cod gate-check component-design

@pm execute-phase 5   # Implement (MISRA C:2012); unit test (branch coverage M)
@cod gate-check implementation-testing

@pm execute-phase 6   # Integration
@cod gate-check integration

@pm execute-phase 7   # Validation
@cod gate-check validation

@pm execute-phase 9   # Deployment: baseline, release package
@cod gate-check deployment

@cod status   # Overall lifecycle progress and compliance summary
```
