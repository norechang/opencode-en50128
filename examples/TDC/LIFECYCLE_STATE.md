# Project Lifecycle State

## Project Information

| Property | Value |
|----------|-------|
| **Project Name** | TDC (Train Door Control) |
| **SIL Level** | SIL 3 |
| **COD Mode** | Strict Gatekeeper |
| **Standard** | EN 50128:2011 |
| **Language** | C (MISRA C:2012 mandatory) |
| **Created** | 2026-03-27 |
| **Last Updated** | 2026-03-27 |
| **Workspace Path** | `examples/TDC/` |

---

## Current Status

| Property | Value |
|----------|-------|
| **Current Phase** | Phase 0 — Initialization (Complete) |
| **Completion** | 5% |
| **Gate Mode** | Strict Gatekeeper (SIL 3 — no override permitted) |
| **Next Action** | Run `@pm execute-phase 1` to begin Planning phase |

---

## Phase History

| Phase | Status | Started | Completed | Gate Passed | Notes |
|-------|--------|---------|-----------|-------------|-------|
| Phase 0 — Initialization | ✅ Complete | 2026-03-27 | 2026-03-27 | N/A | Workspace initialized |
| Phase 1 — Planning | ⏳ Pending | — | — | — | Awaiting `@pm execute-phase 1` |
| Phase 2 — Requirements | ⏳ Pending | — | — | — | Awaiting Phase 1 gate |
| Phase 3 — Architecture & Design | ⏳ Pending | — | — | — | Awaiting Phase 2 gate |
| Phase 4 — Component Design | ⏳ Pending | — | — | — | Awaiting Phase 3 gate |
| Phase 5 — Implementation & Testing | ⏳ Pending | — | — | — | Awaiting Phase 4 gate |
| Phase 6 — Integration | ⏳ Pending | — | — | — | Awaiting Phase 5 gate |
| Phase 7 — Validation | ⏳ Pending | — | — | — | Awaiting Phase 6 gate |
| Phase 8 — Assessment | ⏳ Pending | — | — | — | SIL 3 — MANDATORY (§6.4.1.1) |
| Phase 9 — Deployment | ⏳ Pending | — | — | — | Awaiting Phase 8 gate |
| Phase 10 — Maintenance | ⏳ Pending | — | — | — | Ongoing after deployment |

---

## Deliverable Status

### Phase 0 — Initialization
| Deliverable | Status | Path |
|-------------|--------|------|
| LIFECYCLE_STATE.md | ✅ Created | `examples/TDC/LIFECYCLE_STATE.md` |
| System Requirements Specification | ✅ Generated | `examples/TDC/docs/system/System-Requirements-Specification.md` |
| System Architecture Description | ✅ Generated | `examples/TDC/docs/system/System-Architecture-Description.md` |
| System Safety Plan | ✅ Generated | `examples/TDC/docs/system/System-Safety-Plan.md` |
| System Safety Requirements Specification | ✅ Generated | `examples/TDC/docs/system/System-Safety-Requirements-Specification.md` |

### Phase 1 — Planning
| Deliverable | Status | Path |
|-------------|--------|------|
| Software Quality Assurance Plan (SQAP) | ✅ Generated | `examples/TDC/docs/phase-1-planning/Software-Quality-Assurance-Plan.md` |
| Software Configuration Management Plan (SCMP) | ✅ Generated | `examples/TDC/docs/phase-1-planning/Software-Configuration-Management-Plan.md` |
| Software Verification Plan (SVP) | ⏳ Pending | `examples/TDC/docs/Software-Verification-Plan.md` |
| Software Validation Plan (SVaP) | ⏳ Pending | `examples/TDC/docs/Software-Validation-Plan.md` |

### Phase 2 — Requirements
| Deliverable | Status | Path |
|-------------|--------|------|
| Software Requirements Specification (SRS) | ⏳ Pending | `examples/TDC/docs/Software-Requirements-Specification.md` |
| Hazard Log | ⏳ Pending | `examples/TDC/docs/Hazard-Log.md` |
| Requirements Traceability Matrix (RTM) | ⏳ Pending | `examples/TDC/docs/Requirements-Traceability-Matrix.md` |

### Phase 3 — Architecture & Design
| Deliverable | Status | Path |
|-------------|--------|------|
| Software Architecture Specification (SAS) | ⏳ Pending | `examples/TDC/docs/Software-Architecture-Specification.md` |
| Software Design Specification (SDS) | ⏳ Pending | `examples/TDC/docs/Software-Design-Specification.md` |
| Software Interface Specifications (SIS) | ⏳ Pending | `examples/TDC/docs/Software-Interface-Specifications.md` |
| FMEA Worksheet | ⏳ Pending | `examples/TDC/docs/FMEA-Worksheet.md` |

### Phase 4 — Component Design
| Deliverable | Status | Path |
|-------------|--------|------|
| Software Component Design Specification | ⏳ Pending | `examples/TDC/docs/Software-Component-Design-Specification.md` |
| Software Component Test Specification | ⏳ Pending | `examples/TDC/docs/Software-Component-Test-Specification.md` |

### Phase 5 — Implementation & Testing
| Deliverable | Status | Path |
|-------------|--------|------|
| Source Code (C, MISRA C:2012) | ⏳ Pending | `examples/TDC/src/` |
| Unit Tests (Unity framework) | ⏳ Pending | `examples/TDC/tests/unit/` |
| Unit Test Results (100% coverage) | ⏳ Pending | `examples/TDC/test-results/unit/` |
| Code Review Report | ⏳ Pending | `examples/TDC/docs/Code-Review-Report.md` |
| Verification Report — Phase 5 | ⏳ Pending | `examples/TDC/docs/Verification-Report-Phase5.md` |

### Phase 6 — Integration
| Deliverable | Status | Path |
|-------------|--------|------|
| Integration Plan | ⏳ Pending | `examples/TDC/docs/Integration-Plan.md` |
| Integration Tests | ⏳ Pending | `examples/TDC/tests/integration/` |
| Integration Test Report | ⏳ Pending | `examples/TDC/docs/Integration-Test-Report.md` |
| Verification Report — Phase 6 | ⏳ Pending | `examples/TDC/docs/Verification-Report-Phase6.md` |

### Phase 7 — Validation
| Deliverable | Status | Path |
|-------------|--------|------|
| Validation Report | ⏳ Pending | `examples/TDC/docs/Validation-Report.md` |

### Phase 8 — Assessment (SIL 3 — MANDATORY)
| Deliverable | Status | Path |
|-------------|--------|------|
| Software Assessment Plan | ⏳ Pending | `examples/TDC/docs/Software-Assessment-Plan.md` |
| Software Assessment Report | ⏳ Pending | `examples/TDC/docs/Software-Assessment-Report.md` |

### Phase 9 — Deployment
| Deliverable | Status | Path |
|-------------|--------|------|
| Release and Deployment Plan | ⏳ Pending | `examples/TDC/docs/Release-Deployment-Plan.md` |
| Release Package | ⏳ Pending | `examples/TDC/release/` |
| Deployment Verification Report | ⏳ Pending | `examples/TDC/docs/Deployment-Verification-Report.md` |

---

## Gate Check History

| Date | Phase | Result | Criteria Failed | Notes |
|------|-------|--------|-----------------|-------|
| 2026-03-27 | Phase 0 | ✅ PASS | None | Initialization complete |

---

## Agents Active

| Agent | Role | Independence | Status |
|-------|------|-------------|--------|
| COD | Lifecycle Coordinator | N/A | ✅ Active |
| PM | Project Manager | Not required | ⏳ Awaiting Phase 1 |
| REQ | Requirements Engineer | Not required | ⏳ Awaiting Phase 2 |
| DES | Designer | Not required | ⏳ Awaiting Phase 3 |
| IMP | Implementer | Not required | ⏳ Awaiting Phase 5 |
| TST | Tester | Highly Recommended (SIL 3) | ⏳ Awaiting Phase 5 |
| VER | Verifier | **MANDATORY INDEPENDENT** (SIL 3) | ⏳ Awaiting Phase 1 |
| VAL | Validator | **MANDATORY INDEPENDENT** (SIL 3) | ⏳ Awaiting Phase 7 |
| INT | Integrator | Not required | ⏳ Awaiting Phase 6 |
| SAF | Safety Engineer | Not required | ⏳ Awaiting Phase 2 |
| QUA | Quality Assurance | Not required | ⏳ Awaiting Phase 1 |
| CM | Configuration Manager | Not required | ⏳ Awaiting Phase 1 |
| VMGR | V&V Manager | **MANDATORY INDEPENDENT** (SIL 3) | ⏳ Awaiting Phase 1 |

---

## SIL 3 Mandatory Constraints

The following constraints are MANDATORY for this SIL 3 project and will be enforced at every gate:

| Constraint | Requirement | Enforcement |
|------------|------------|-------------|
| MISRA C:2012 | Zero mandatory violations | VER — hard gate block |
| Cyclomatic Complexity | CCN ≤ 10 per function | VER (Lizard) — hard gate block |
| Statement Coverage | 100% | TST (gcov/lcov) — hard gate block |
| Branch Coverage | 100% | TST (gcov/lcov) — hard gate block |
| Condition Coverage (MC/DC) | 100% | TST (mcdc_analyzer.py) — hard gate block |
| No dynamic memory allocation | `malloc`/`free` forbidden | VER — hard gate block |
| No recursion | Forbidden | VER — hard gate block |
| Independent VER | Mandatory (COD invokes, not PM) | COD enforced |
| Independent VAL | Mandatory (reports to VMGR, not PM) | COD enforced |
| VMGR approval | Required for every VER/VAL report | VMGR — cannot be overridden |
| ISA Assessment | Mandatory Phase 8 (§6.4.1.1) | COD gate block |
| Traceability (RTM) | 100% SYS-REQ → SW-REQ → Code → Test | VER + COD gate |

---

## Traceability Status

| Direction | Coverage | Status |
|-----------|----------|--------|
| SYS-REQ → SW-REQ | 0% | ⏳ Initialized in Phase 2 |
| SW-REQ → Architecture | 0% | ⏳ Initialized in Phase 3 |
| Architecture → Code | 0% | ⏳ Initialized in Phase 5 |
| Code → Unit Tests | 0% | ⏳ Initialized in Phase 5 |
| SW-REQ → Validation | 0% | ⏳ Initialized in Phase 7 |

---

## Metrics

| Metric | Target | Current |
|--------|--------|---------|
| Total SW Requirements | TBD | — |
| Requirements with SIL allocation | 100% | — |
| Orphaned requirements | 0 | — |
| MISRA violations | 0 mandatory | — |
| Max CCN | ≤ 10 | — |
| Statement coverage | 100% | — |
| Branch coverage | 100% | — |
| Condition (MC/DC) coverage | 100% | — |
| Open defects | 0 at release | — |

---

## Change Log

| Date | Phase | CR# | Description | Impact |
|------|-------|-----|-------------|--------|
| 2026-03-27 | Phase 0 | — | Project initialized by COD | N/A |

---

## Next Steps

1. **Run `@cod generate-system`** — Select from typical railway systems catalogue and generate 4 system-level documents in `examples/TDC/docs/system/`
2. **Run `@pm execute-phase 1`** — Begin Planning phase (SQAP, SCMP, SVP, SVaP)
3. **Run `@cod gate-check phase-1`** — Verify Phase 1 completion before proceeding
