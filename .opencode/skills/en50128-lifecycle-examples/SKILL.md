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
# Phase 0: Initialization (COD)
@cod plan --sil 3 --project train_door_control
# Initialize lifecycle tracking, create LIFECYCLE_STATE.md
# COD monitors all subsequent activities

# Generate system-level documents
@cod generate-system
# Prompts for selection from 5 typical railway systems (TYPICAL-SYSTEMS.md)
# Generates: System-Requirements-Specification.md, System-Architecture.md,
#            Hazard-Log.md, RAMS-Requirements.md in docs/system/

# Phase 1: Planning
@pm execute-phase 1
# PM coordinates: project planning, CCB setup, SQAP, SCMP, SVP, SVaP
# Internally: QUA establishes quality processes, CM establishes version control

# COD Phase Gate Check
@cod gate-check planning
# COD verifies all planning documents approved before allowing requirements phase

# Phase 2: Requirements
@pm execute-phase 2
# PM coordinates: REQ creates SRS from system-level inputs
# Internally: SAF performs hazard analysis, QUA checks template compliance,
#             VER verifies requirements, CM baselines requirements
# USER APPROVAL required before REQ activities proceed

# COD Phase Gate Check
@cod gate-check requirements
# COD verifies SRS complete, traceability complete, hazard analysis done, user approval obtained
# COD verifies QA template compliance check performed (MANDATORY SIL 3-4)

# Phase 3: Architecture & Design
@pm execute-phase 3
# PM coordinates: DES creates SAS, SDS, interface specs
# Internally: SAF performs FMEA/FTA, QUA checks template compliance,
#             VER verifies design, CM baselines design

# COD Phase Gate Check
@cod gate-check design
# COD verifies design complete, traceability to requirements, complexity limits defined
# COD verifies QA template compliance check performed (MANDATORY SIL 3-4)

# Phase 4: Component Design
@pm execute-phase 4
# PM coordinates: DES produces Software Component Design Specifications, Test Specifications
# Internally: QUA checks template compliance, VER verifies component designs, CM baselines

# COD Phase Gate Check
@cod gate-check component-design
# COD verifies component designs complete, test specifications ready

# Phase 5: Implementation & Unit Testing
@pm execute-phase 5
# PM coordinates: IMP implements C code (MISRA C:2012), TST writes and executes unit tests
# Internally: QUA performs code review (MISRA C compliance, complexity ≤10),
#             VER runs static analysis, CM baselines code
# COD independently coordinates: VMGR reviews and approves verification (SIL 3-4)

# COD Phase Gate Check
@cod gate-check implementation-testing
# COD verifies MISRA C compliance, coverage met (100% for SIL 3), complexity ≤10
# COD verifies QA code review performed (MANDATORY all SILs)

# Phase 6: Integration
@pm execute-phase 6
# PM coordinates: INT integrates components, TST executes integration tests
# Internally: QUA reviews integration test report, VER verifies integration,
#             CM establishes integration baseline

# COD Phase Gate Check
@cod gate-check integration
# COD verifies all integration tests pass, interfaces tested, baseline established
# COD verifies QA integration test review performed (MANDATORY SIL 3-4)

# Phase 7: Validation
# COD coordinates VAL directly (independence requirement — VAL does not report to PM)
@cod gate-check validation
# COD verifies all tests pass, customer acceptance, validator independence
# COD verifies QA validation review performed (MANDATORY SIL 3-4)

# Phase 8: Assessment (mandatory SIL 1-4 per §6.4.1.1; SIL 0 exempt per §6.4.1.2)
# Independent assessor reviews all lifecycle artifacts and issues approval certificate
@cod gate-check assessment
# COD verifies assessment complete, assessor independence, deployment authorization

# Phase 9: Deployment
@pm execute-phase 9
# PM coordinates: CM establishes final baseline, deployment package prepared

# COD Status Check (anytime)
@cod status
# View current phase, progress, deliverable status, gate compliance
```

---

## Example 2: Quick Prototyping (SIL 0-1)

```bash
# Simplified workflow for lower SIL levels
@cod plan --sil 0 --project prototype  # Optional for SIL 0-1 (advisory mode)
@pm execute-phase 2  # Requirements (no user approval gate for SIL 0-1)
@pm execute-phase 3  # Basic design
@pm execute-phase 5  # Implement and test (80% coverage)
@pm execute-phase 6  # Integration
@cod gate-check validation  # COD provides warnings only, does not block transitions
```

---

## Example 3: Iterative Development (SIL 2)

```bash
# Initial project setup
@cod plan --sil 2 --project iterative_system
@cod generate-system

# Iteration planning
@pm execute-phase 1  # Plan iteration, coordinate team, establish baselines

# Development cycle
@pm execute-phase 2  # Refine requirements for iteration (user approval required)
@cod gate-check requirements  # Semi-strict: requires justification if incomplete
@pm execute-phase 3  # Design iteration features
@cod gate-check design  # Semi-strict mode
@pm execute-phase 5  # Implement with MISRA C:2012, unit test (100% branch - mandatory SIL 2)
@pm execute-phase 6  # Integration testing
@cod gate-check implementation-testing  # Semi-strict: checks MISRA C, coverage

# Iteration completion
@cod gate-check integration
@pm execute-phase 9  # Merge to main, tag baseline
@cod status  # Check overall progress and compliance
```
