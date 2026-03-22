# EN 50128 Role-Based Agents

This document defines role-based agents for EN 50128 railway software development. Each agent corresponds to a specific role in the software development lifecycle and strictly follows EN 50128 behavioral constraints.

## Agent Invocation Syntax

User-facing agents are invoked using the `@agent` syntax in OpenCode:

```
@cod plan --sil 3 --project MyProject
@cod generate-system
@pm execute-phase 2
@cod gate-check phase-2
```

**Normal workflow**: You invoke only `@cod` and `@pm`. They orchestrate all other agents internally.  
**Internal agents** (REQ, DES, IMP, TST, VER, VAL, INT, SAF, QUA, CM, VMGR) are invoked by COD and PM — not directly by the user.

See `docs/USER-GUIDE.md` for complete usage instructions and the V-Model example.

**Related Documents**:
- **`docs/USER-GUIDE.md`** - Complete usage guide with agent commands and V-Model example (START HERE)
- **`LIFECYCLE.md`** - Complete EN 50128 V-Model software development lifecycle
- **`TOOLS.md`** - Comprehensive tool catalog with usage information for agents (CRITICAL); includes Agent Tool Usage Protocol
- **`WORKFLOW.md`** - **FUNDAMENTAL REFERENCE** — agent interaction and phase re-entry workflows; COD/PM/VMGR authority structure, per-phase execution loop, CCB change request re-entry flow
- **`.opencode/agents/`** - Agent definition files (one per role) — full role specs, techniques, Annex B narratives, and combination rules
- **`.opencode/skills/`** - Domain-specific skills loaded internally by agents
- **`std/EN50128-2011.md`** - Full EN 50128 standard (LLM-friendly Markdown)
- **`std/EN 50126-1-2017.md`** - RAMS standard Part 1
- **`std/EN 50126-2-2017.md`** - RAMS standard Part 2

---

## EN 50128 Technique/Measure Tables (Annex A)

The following tables define mandatory, highly recommended, and recommended techniques for each lifecycle phase. Agents SHALL reference these tables when performing their duties.

**Standard Location:** `std/EN50128-2011.md` (converted from PDF)

| Table | Section | Purpose | Key Agents |
|-------|---------|---------|------------|
| **Table A.2** | 7.2 | Software Requirements Specification techniques | REQ |
| **Table A.3** | 7.3 | Software Architecture techniques | DES |
| **Table A.4** | 7.4 | Software Design and Implementation techniques | DES, IMP |
| **Table A.5** | 6.2, 7.3 | Verification and Testing techniques | VER, TST |
| **Table A.6** | 7.6 | Integration techniques | INT |
| **Table A.7** | 7.7 | Overall Software Testing/Validation techniques | VAL |
| **Table A.8** | 6.3 | Software Analysis techniques | SAF |
| **Table A.9** | 6.5 | Software Quality Assurance techniques | QUA, CM |
| **Table A.13** | - | Dynamic Analysis and Testing | TST, VER |
| **Table A.19** | - | Static Analysis techniques | VER |
| **Table A.21** | - | Test Coverage for Code | TST |

**Key to Recommendations:**
- **M** = Mandatory - Must be used
- **HR** = Highly Recommended - Rationale required if not used
- **R** = Recommended - Should be considered
- **-** = No recommendation
- **NR** = Not Recommended - Rationale required if used

---

## EN 50128 Role Definitions (Section 5 and Annex B)

EN 50128:2011 defines the following organizational roles:

### Core Development Roles (Section 5.3)

| Role | EN 50128 Section | Description | Independence Required |
|------|------------------|-------------|----------------------|
| **Software Manager** | 5.3.1, Table B.1 | Overall software development responsibility | No |
| **Designer** | 5.3.2, Table B.2 | Software architecture and design | No |
| **Implementer** | 5.3.3, Table B.3 | Code implementation | No |
| **Tester** | 5.3.4, Table B.4 | Software testing | No |
| **Verifier** | 5.3.5, Table B.5 | Software verification | Yes (SIL 3-4) |
| **Integrator** | 5.3.6, Table B.6 | Software integration | No |
| **Validator** | 5.3.7, Table B.7 | Software validation | Yes (SIL 3-4) |
| **Assessor** | 5.3.8, Table B.8 | Independent safety assessment | Yes (SIL 3-4) |

### Management and Support Roles (Section 5, Annex B)

| Role | EN 50128 Reference | Description | Independence Required |
|------|-------------------|-------------|----------------------|
| **Lifecycle Coordinator (COD)** | Platform Extension (Section 5.3) | End-to-end lifecycle orchestration, phase gate enforcement | No |
| **V&V Manager (VMGR)** | Platform Extension (Section 5.1.2.10e) | Independent V&V authority, manages Verifier team, provides final V&V approval | Yes (SIL 3-4) |
| **Project Manager** | Section 5, Table B.9 | Overall project responsibility, coordinates across roles | No |
| **Configuration Manager** | Section 5, Table B.10 | Configuration and change management | No |

**Important Notes**:
- **Lifecycle Coordinator (COD)** is a platform extension role (not explicitly in EN 50128) that orchestrates the complete V-Model lifecycle
- **V&V Manager (VMGR)** is a platform extension role (based on EN 50128 Section 5.1.2.10e "Verifier can report to Validator") that provides independent V&V authority for SIL 3-4 projects
- **COD has overall lifecycle authority**; PM reports to COD for lifecycle decisions
- **VMGR is INDEPENDENT from COD and PM** (SIL 3-4); coordinates with COD but does not report to COD
- Independence is MANDATORY for Verifier, Validator, and Assessor roles at SIL 3-4
- One person MAY perform multiple roles IF independence requirements are met

---

## Development Language

- **Primary Language**: C (for safety-critical software)
- **Scripting Support**: Python (for build automation, testing harness, analysis tools — NOT part of safety software)
- **Standards**: MISRA C:2012 (mandatory for SIL 2+)

---

## Agent Roles (Index)

Full role specifications — including EN 50128 technique tables, Annex B narratives, and role combination rules — are in each agent's definition file under `.opencode/agents/`.

| # | Agent | Role | EN 50128 Section | Agent File |
|---|-------|------|------------------|------------|
| 1 | **REQ** | Requirements Engineer | Section 7.2, Table A.2 | `.opencode/agents/req.md` |
| 2 | **DES** | Designer | Section 7.3, Table A.3 | `.opencode/agents/des.md` |
| 3 | **IMP** | Implementer | Section 7.4, Table A.4 | `.opencode/agents/imp.md` |
| 4 | **TST** | Tester | Sections 7.4, 7.5, 7.7, Table A.5 | `.opencode/agents/tst.md` |
| 5 | **SAF** | Safety Engineer | Sections 7.1, 6.3, Table A.8 | `.opencode/agents/saf.md` |
| 6 | **VER** | Verifier | Section 6.2, Tables A.5, A.19 | `.opencode/agents/ver.md` |
| 7 | **VAL** | Validator | Section 7.7, Table A.7 | `.opencode/agents/val.md` |
| 8 | **QUA** | Quality Assurance | Section 6.5, Table A.9 | `.opencode/agents/qua.md` |
| 9 | **INT** | Integrator | Section 7.6, Table A.6 | `.opencode/agents/int.md` |
| 10 | **PM** | Project Manager | Section 5, Table B.9 | `.opencode/agents/pm.md` |
| 11 | **CM** | Configuration Manager | Section 6.6, Table A.9 | `.opencode/agents/cm.md` |
| 12 | **VMGR** | V&V Manager | Section 5.1.2.10e | `.opencode/agents/vmgr.md` |
| 13 | **COD** | Lifecycle Coordinator | Section 5.3, Annex C | `.opencode/agents/cod.md` |

---

## Agent Interaction and Workflow

### Typical Development Flow

> Full authority structure and per-phase gate loop: see **`WORKFLOW.md`**.

```
Safety Authority / Customer
├── COD (Lifecycle Coordinator) ◄──coordinate──► VMGR (Independent V&V Authority)
│     • Phase gates                (no report)    • Manages VER team
│     • Lifecycle state                           • Reviews VER reports
│     • Compliance                                • Reviews VAL reports
│     • Cannot override VMGR                      • Final V&V decision
│                                                   (cannot be overridden)
│ authorizes phases                              manages
▼                                                   ▼
PM (Project Manager)                           VER (Verifier)
│  • Team coordination                         • Verification reports
│  • Resource mgmt                             • Static analysis
│  • Stakeholder comms                         • Coverage checks
│  • CCB leadership                            • Reports to VMGR
│  • Reports to COD for lifecycle
└──► orchestrates: REQ · DES · IMP · INT · TST · QUA · CM · SAF

     ┌─────────┐
     │ PHASE 1 │ Planning
     │  PM+QUA │ - SQAP, SCMP, SVP, SVaP
     │  +CM+SAF│
     └────┬────┘
          │ deliverable → QUA check → VER → VMGR → VAL → VMGR
          │ COD Gate Check: @cod gate-check planning
          ▼
     ┌─────────┐
     │ PHASE 2 │ Requirements Specification
     │   REQ   │ - SRS (USER APPROVAL REQUIRED)
     │  +SAF   │ - Assign SIL levels, traceability
     └────┬────┘
          │ deliverable → QUA check → VER → VMGR → VAL → VMGR
          │ COD Gate Check: @cod gate-check requirements
          ▼
     ┌─────────┐
     │ PHASE 3 │ Architecture & Design
     │   DES   │ - SAS, SDS, Software Interface Specifications
     │  +SAF   │ - Integration test specifications, FMEA/FTA
     └────┬────┘
          │ deliverable → QUA check → VER → VMGR → VAL → VMGR
          │ COD Gate Check: @cod gate-check design
          ▼
     ┌─────────┐
     │ PHASE 4 │ Component Design
     │   DES   │ - Software Component Design Specification
     │  +TST   │ - Software Component Test Specification
     └────┬────┘
          │ deliverable → QUA check → VER → VMGR → VAL → VMGR
          │ COD Gate Check: @cod gate-check component-design
          ▼
     ┌─────────┐
     │ PHASE 5 │ Implementation & Testing
     │   IMP   │ - Code modules (MISRA C)
     │  +TST   │ - Unit tests + coverage
     └────┬────┘
          │ deliverable → QUA check → VER → VMGR → VAL → VMGR
          │ COD Gate Check: @cod gate-check implementation-testing
          ▼
     ┌─────────┐
     │ PHASE 6 │ Integration
     │   INT   │ - Integrate components
     │  +TST   │ - Integration testing
     └────┬────┘
          │ deliverable → QUA check → VER → VMGR → VAL → VMGR
          │ COD Gate Check: @cod gate-check integration
          ▼
     ┌─────────┐
     │ PHASE 7 │ Validation — COD invokes VAL independently
     │   VAL   │ - System testing, acceptance testing
     │  +TST   │ - Overall Software Test Report, Release Note
     └────┬────┘
          │ VAL report → QUA check → VMGR approval
          │ COD Gate Check: @cod gate-check validation
          ▼
     ┌─────────┐
     │ PHASE 8 │ Assessment — mandatory SIL 1-4 (§6.4.1.1)
     │  ASR    │ - Software Assessment Plan & Report
     │ (indep.)│ - Independent assessor reviews all artifacts
     └────┬────┘
          │ COD Gate Check: @cod gate-check assessment
          ▼
     ┌─────────┐
     │ PHASE 9 │ Deployment
     │  PM+CM  │ - Release and Deployment Plan
     │  +VER   │ - Deployment Records + Verification Report
     └────┬────┘
          │ COD Gate Check: @cod gate-check deployment
          ▼
     ┌──────────┐
     │ PHASE 10 │ Maintenance (ongoing)
     │  PM+CM   │ - Change Records, Maintenance Records
     │  +VER    │ - Maintenance Verification Report
     └──────────┘

     ── Active throughout all phases ──────────────────────────

     ┌─────────┐   ┌─────────┐   ┌─────────┐   ┌─────────┐
     │   SAF   │   │   QUA   │   │   CM    │   │   PM    │
     │ Hazard  │   │Template │   │Version  │   │Coord-   │
     │ analysis│   │checks / │   │control /│   │ination /│
     │ Safety  │   │ audits  │   │baselines│   │   CCB   │
     │ case    │   │         │   │         │   │         │
     └─────────┘   └─────────┘   └─────────┘   └─────────┘
```

### Example Workflow

```bash
# ── USER INVOKES ONLY TWO COMMANDS ────────────────────────────────────────────

# Initialize lifecycle (COD creates LIFECYCLE_STATE.md)
@cod plan --sil 3 --project MyProject

# Generate system-level documents from typical systems catalogue
@cod generate-system

# Execute each phase (PM orchestrates all agents internally)
@pm execute-phase 1    # Planning: SQAP, SCMP, SVP, SVaP
@cod gate-check planning

@pm execute-phase 2    # Requirements: SRS, Overall SW Test Spec
@cod gate-check requirements

@pm execute-phase 3    # Architecture & Design: SAS, SDS, SIS, Integration Test Specs
@cod gate-check design

@pm execute-phase 4    # Component Design: Component Design Spec, Component Test Spec
@cod gate-check component-design

@pm execute-phase 5    # Implementation & Testing: source code, unit tests, coverage
@cod gate-check implementation-testing

@pm execute-phase 6    # Integration: integration testing, SW/HW integration
@cod gate-check integration

# Phase 7: Validation — COD coordinates VAL directly (independence requirement)
@pm execute-phase 7
@cod gate-check validation

# Phase 8: Assessment — mandatory SIL 1-4 (independent assessor)
@cod gate-check assessment

@pm execute-phase 9    # Deployment: release package, final baseline
@cod gate-check deployment

# Phase 10: Maintenance (ongoing — triggered by change requests via CCB)
```

---

## C Language Compliance Summary

| Requirement | SIL 0-1 | SIL 2 | SIL 3-4 |
|-------------|---------|-------|---------|
| Structured programming | R | HR | **M** |
| MISRA C:2012 | R | **M** | **M** |
| No dynamic memory allocation | R | **M** | **M** |
| Static analysis | R | HR | **M** |
| Cyclomatic complexity ≤ limit | 20 | 15 | 10 |
| 100% statement/branch/MC/DC coverage | - | branch **M** | all **M** |
| No recursion | R | HR | HR |
| No function pointers | R | HR | HR |

**Python MUST NOT** be used for any safety-critical functions or code subject to SIL requirements.

---

## Agent-to-Skill Mapping

Each agent **internally loads its skill** when invoked. Users do not load skills directly.

| Agent | Role | Skill Loaded Internally | EN 50128 Section |
|-------|------|------------------------|------------------|
| REQ | Requirements Engineer | `en50128-requirements` | Section 7.2 |
| DES | Designer | `en50128-design` | Section 7.3 |
| IMP | Implementer | `en50128-implementation` | Section 7.4 |
| TST | Tester | `en50128-testing` | Sections 7.4, 7.5, 7.7 |
| VER | Verifier | `en50128-verification` | Section 6.2 |
| VAL | Validator | `en50128-validation` | Section 7.7 |
| INT | Integrator | `en50128-integration` | Section 7.6 |
| SAF | Safety Engineer | `en50128-safety` | Sections 7.1, 6.3 |
| QUA | Quality Assurance | `en50128-quality` | Section 6.5 |
| CM | Configuration Manager | `en50128-configuration` | Section 6.6 |
| COD | Lifecycle Coordinator | `en50128-lifecycle-coordination` | Section 5.3 |
| PM | Project Manager | `en50128-project-management` | Section 5, Table B.9 |
| VMGR | V&V Manager | `en50128-lifecycle-coordination` (base) | Section 5.1.2.10e |

---

## Standard References

- EN 50128:2011 - Railway Software Standard
- EN 50126:2017 - RAMS
- MISRA C:2012 - C Coding Standard
- IEC 61508 - Functional Safety

---

## EN 50128 Role Independence Reference

### Role Independence Matrix

| Role | SIL 0-1 | SIL 2 | SIL 3-4 |
|------|---------|-------|---------|
| Project Manager | No | No | No |
| Software Manager | No | No | No |
| Configuration Manager | No | No | No |
| Designer | No | No | No |
| Implementer | No | No | No |
| Tester | No | HR | HR |
| Verifier | No | HR | **M** |
| Integrator | No | No | No |
| Validator | No | HR | **M** |
| Assessor | N/A | N/A | **M** |

**Legend**: **M** = Mandatory, **HR** = Highly Recommended, **No** = Not required

### Role Combination Rules

**Allowed Combinations** (when independence is not required):

- Software Manager + Designer
- Designer + Implementer
- Implementer + Tester (SIL 0-2 only)
- Integrator + Tester

**Prohibited Combinations** (for SIL 3-4):

- Designer/Implementer + Verifier
- Any development role + Validator
- Any role + Assessor
- Implementer + Tester (own code)

**Best Practice for SIL 3-4 Projects**:
- Separate teams for Development and Verification/Validation
- Independent Assessor (often external to the organization)
- Clear organizational separation with independent reporting lines

> **Full Annex B role narratives** and per-role combination rules are in each agent's definition file (`.opencode/agents/<role>.md`).

### Agent Mapping to EN 50128 Roles

| EN 50128 Role | Agent | Independence Notes |
|---------------|-------|--------------------|
| Project Manager | PM | Not required |
| Software Manager | PM | Not required (combined with PM in this platform) |
| Configuration Manager | CM | Not required |
| Designer | DES | Not required |
| Implementer | IMP | Not required |
| Tester | TST | Highly recommended for SIL 3-4 |
| Verifier | VER | **Mandatory for SIL 3-4** |
| Integrator | INT | Not required |
| Validator | VAL | **Mandatory for SIL 3-4** |
| Assessor | (external) | **Mandatory for SIL 3-4** |

**Additional Agents** (platform extensions):
- Safety Engineer (SAF) — Supports safety analysis per Section 7.1
- Requirements Engineer (REQ) — Supports requirements phase per Section 7.2
- Quality Assurance (QUA) — Supports QA per Section 6.5
- V&V Manager (VMGR) — Independent V&V authority for SIL 3-4 (Section 5.1.2.10e)
- Lifecycle Coordinator (COD) — End-to-end lifecycle orchestration (Section 5.3)
