---
name: en50128-design
description: Software architecture and design patterns for EN 50128 compliant C programs with MISRA C and defensive programming
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  coding-standard: MISRA C:2012
---

# EN 50128 Design Skill

This skill provides the DES agent with authoritative reference data, generation
algorithms, technique tables, and defect remediation logic for software architecture
and design per EN 50128 §7.3 and §7.4.
**Load this skill before performing any DES activity.**

---

## 1. Authoritative Sources

| What you need | Where to find it |
|---------------|-----------------|
| Phase 3 activities, deliverable paths, completion criteria | `activities/phase-3-architecture-design.yaml` |
| Phase 4 activities, deliverable paths, completion criteria | `activities/phase-4-component-design.yaml` |
| Items 9–11, 15 ownership, doc IDs, template paths, SIL obligations | `activities/deliverables.yaml` |
| Annex C Table C.1 — full deliverable ownership catalogue | `DELIVERABLES.md` |
| Traceability rules T1–T15 (human-readable) | `TRACEABILITY.md` |
| Traceability obligations T1–T15 (machine-readable, agent consumption) | `activities/traceability.yaml` |
| Authority structure, two-track loop, CCB re-entry | `WORKFLOW.md` |
| Independence matrix (DES = No at all SIL levels) | `ORGANIZATION.md` |
| §7.3 SAS requirements, Table A.3 techniques | `std/EN50128-2011.md` |
| §7.4 design and implementation techniques, Table A.4 | `std/EN50128-2011.md` |
| SAS template (item 9) | `deliverables/architecture/Software-Architecture-Specification-template.md` |
| SDS template (item 10) | `deliverables/component-design/Software-Design-Specification-template.md` |
| SIS template (item 11) | `deliverables/architecture/Software-Interface-Specifications-template.md` |
| Component Design Spec template (item 15) | `deliverables/component-design/Software-Component-Design-Specification-template.md` |
| Defensive programming patterns, complexity guidelines, MISRA C design | `resources/` |
| SAF phase footprint, Hazard Log ownership | `tasks/SAFETY_ENGINEERING.md` |
| Canonical document paths at runtime | CM `query-location` |

---

## 2. DES Phase Footprint

DES is the primary agent for Phases 3 and 4.

| Annex C Item | Document | Owner | Phase |
|---|---|---|---|
| 9 | Software Architecture Specification (SAS) | **DES** | 3 |
| 10 | Software Design Specification (SDS) | **DES** | 3 |
| 11 | Software Interface Specifications (SIS) | **DES** | 3 |
| 12 | Software Integration Test Specification | INT | 3 |
| 13 | HW/SW Integration Test Specification | INT | 3 |
| 14 | Software Architecture and Design Verification Report | VER | 3 |
| 15 | Software Component Design Specification (SCDS) | **DES** | 4 |
| 16 | Software Component Test Specification | TST | 4 |
| 17 | Software Component Design Verification Report | VER | 4 |

- SAF co-authors safety architecture sections: FMEA/FTA on the SAS/SDS (HR at SIL 3–4 per Tables A.3/A.8).
- DES has NO authorship role in items 12, 13, 14, 16, or 17.
- DES independence: Not required at any SIL level (see `ORGANIZATION.md`).

---

## 3. create-sas Algorithm (item 9)

Follow these steps in order. Do not skip steps.

1. **Invoke CM `query-location`** via `task` tool with `--doc sas`. Record the canonical path.

2. **Read `.workspace`** to confirm active project name, SIL level, and base path.

3. **Verify Phase 3 prerequisites** (§7.3.2): locate the SRS (item 6), Hazard Log (SAF),
   SQAP (item 2), and SCMP (item 3). If any are missing, halt and report to PM.

4. **Load the SAS template** from `deliverables/architecture/Software-Architecture-Specification-template.md`.
   Fill the Document Control block (doc ID = `DOC-SAS-YYYY-001`, version = `0.1 DRAFT`).

5. **Fill the Approvals table** using project SIL level:
   - SIL 0–2: Author (DES), QUA, VER, PM
   - SIL 3–4: Author (DES), QUA, VER (independent), VAL (independent), PM
   Never add "Safety Manager", "QA Manager", or "Technical Reviewer".

6. **Decompose the system** into high-level software components. For each component:
   - Name, responsibility, interfaces (in/out), data flows.
   - Apply Table A.3: Modular Approach (M SIL 2+), Structured Methodology (M SIL 3–4).

7. **Define safety architecture**: fault detection mechanisms, safe states, fail-safe
   behavior. Allocate safety requirements from the Hazard Log to components.

8. **Establish traceability** (Requirements → Architecture):
   - SIL 0–1: R — include if available.
   - SIL 2: HR — include; document reason if any omitted.
   - SIL 3–4: M — every component MUST trace to ≥1 SRS requirement or hazard.

9. **Document complexity limits** explicitly: SIL 0–1: ≤20; SIL 2: ≤15; SIL 3–4: ≤10
   cyclomatic complexity per function. Document no-dynamic-memory constraint (SIL 2+).

10. **Write the completed SAS** to the canonical path. Set version `0.1 DRAFT`.
    Return the path and component summary to PM.

---

## 4. create-sds-sis Algorithm (items 10 and 11)

Follow these steps in order. Prerequisite: SAS (item 9) must be baselined.

1. **Invoke CM `query-location`** for `--doc sds` and `--doc sis`. Record both paths.

2. **Load the SDS template** from `deliverables/component-design/Software-Design-Specification-template.md`
   and the SIS template from `deliverables/architecture/Software-Interface-Specifications-template.md`.
   Fill Document Control blocks and Approvals tables per the same SIL rules as Step 5 above.

3. **Decompose each SAS component** into modules. For each module specify:
   - Functional description, data structures (static allocation only, SIL 2+),
     algorithms (pseudocode or flowchart), pre/postconditions, error handling.
   - Enforce complexity: SIL 0–1 ≤20, SIL 2 ≤15, SIL 3–4 ≤10 cyclomatic complexity.

4. **Define all interfaces** in the SIS: internal (module-to-module), external
   (HW, external systems), HMI. For each interface: data types (fixed-width C types),
   value ranges, timing constraints, error/exception behavior.

5. **Establish traceability** (Architecture → Module, Interface):
   Every SDS module and SIS interface must trace back to a SAS component.

6. **Write SDS and SIS** to their canonical paths. Set version `0.1 DRAFT`.
   Return paths to PM.

---

## 5. create-component-design Algorithm (item 15)

Prerequisite: SDS (item 10) must be baselined.

1. **Invoke CM `query-location`** for `--doc component-design-spec`. Record the path.

2. **Load the Component Design Spec template** from
   `deliverables/component-design/Software-Component-Design-Specification-template.md`.
   Fill Document Control block and Approvals table per SIL rules.

3. **For each component** identified in the SDS, produce a component-level specification:
   - Function signatures, parameter types and valid ranges, return values, error codes.
   - State machine diagrams (where applicable), timing constraints, resource usage.
   - Pre/postconditions detailed enough for direct C implementation by IMP.

4. **Enforce SIL constraints** at component level:
   - Cyclomatic complexity must be achievable within SIL limits.
   - No dynamic memory allocation patterns.
   - No recursion (HR SIL 3–4).

5. **Establish traceability** (SDS Module → Component Design):
   Every component entry MUST trace to an SDS module (SIL 3–4: mandatory).

6. **Write SCDS** to the canonical path. Set version `0.1 DRAFT`. Return path to PM.

---

## 6. Table A.3 Techniques (§7.3)

| # | Technique/Measure | Ref | SIL 0 | SIL 1–2 | SIL 3–4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Structured Methodology | D.52 | R | HR | **M** |
| 2 | Defensive Programming | D.14 | – | HR | HR |
| 3 | Fault Detection and Diagnosis | D.26 | – | R | HR |
| 4 | Information Encapsulation | D.33 | R | HR | HR |
| 5 | Modelling | A.17 | R | R | HR |
| 6 | Formal Methods | D.28 | – | R | HR |
| 7 | Fully Defined Interface | D.38 | HR | HR | HR |
| 8 | Structured Design | D.51 | R | HR | HR |
| 9 | Functional Cohesion | D.55 | R | R | HR |
| 10 | Coupling and Cohesion | D.55 | R | R | HR |
| 11 | Software Modules with Low Coupling | D.55 | R | HR | HR |
| 12 | Event-driven Programming | D.21 | – | – | R |
| 13 | Concurrency | D.11 | – | R | R |
| 14 | Interrupt | D.35 | – | – | R |
| 15 | Object-oriented Programming | D.39 | – | R | R |
| 16 | Design and Coding Standards | A.12 | HR | HR | HR |
| 17 | Software Design Notations | D.46 | R | R | HR |
| 18 | Data Flow Diagrams | D.10 | R | R | R |
| 19 | **Modular Approach** | D.38 | HR | **M** | **M** |
| 20 | Schedulability Analysis | D.40 | – | R | HR |
| 21 | Time-triggered Architecture | D.56 | – | R | HR |
| 22 | Memorisation of Data/Program Flow | D.36 | R | HR | HR |
| 23 | Failure Assertion Programming | D.24 | – | R | HR |

**Mandatory**: Entry 19 (Modular Approach) SIL 2+; Entry 1 (Structured Methodology) SIL 3–4.

---

## 7. Defect Remediation (fix-defects)

When PM routes QUA/VER findings to DES, apply this table:

| Finding Code | Description | Action | Confidence |
|---|---|---|---|
| `T001` | Document ID format incorrect | Reformat to `DOC-SAS/SDS/SIS/COMPDESIGN-YYYY-001` | HIGH — auto-fix |
| `T002` | Document Control block missing/incomplete | Insert standard block from template | HIGH — auto-fix |
| `T003` | Approvals table missing or wrong roles | Replace with SIL-correct approvals (Section 3, Step 5) | HIGH — auto-fix |
| `T004` | Required section absent | Add section heading + TBD marker | HIGH — auto-fix |
| `A001` | Component missing from SAS | Add component with description and interfaces | MEDIUM — flag for review |
| `A002` | Complexity limit not documented | Add constraint statement in SAS/SDS | HIGH — auto-fix |
| `A003` | Dynamic memory allocation referenced (SIL 2+) | Remove and replace with static allocation pattern | HIGH — auto-fix |
| `A004` | Modular Approach not applied/documented (SIL 2+) | Add methodology documentation in SAS | MEDIUM — flag for review |
| `A005` | Structured Methodology not documented (SIL 3–4) | Add methodology name and section reference | MEDIUM — flag for review |
| `C001` | Traceability missing (SIL 3–4) | Escalate to PM — requires REQ/SAF input | LOW — escalate |
| `C002` | Safety architecture gap | Escalate to PM — requires SAF review | LOW — escalate |

**Escalation rule**: LOW-confidence findings MUST be escalated to PM with a written
description of the gap. DES MUST NOT invent traceability links or safety mitigations.

---

## 8. Document Interactions

```
SRS (item 6, REQ) + Hazard Log (SAF)
  └─► DES reads: SRS, Hazard Log
        │
        ├─► DES writes: SAS (item 9)
        │     └─► DES writes: SDS (item 10)
        │           └─► DES writes: SIS (item 11)
        │                 ├─► INT writes: SW Integration Test Spec (item 12)
        │                 └─► INT writes: HW/SW Integration Test Spec (item 13)
        │
        ├─► VER writes: Design Verification Report (item 14) [VER owns]
        │
        └─► DES writes: Component Design Spec (item 15) ← from SDS
              └─► TST writes: Component Test Spec (item 16) [TST owns]
                    └─► VER writes: Component Design VER Report (item 17) [VER owns]
```

**DES provides to**: IMP (items 10, 15 drive C implementation), TST (design for
testability review), INT (item 11 SIS drives integration test specs).

**DES receives from**: REQ (SRS item 6), SAF (Hazard Log, SIL assignments, FMEA/FTA),
PM (task assignment, defect routing).

**DES does NOT contact**: QUA or VER directly. All submissions go through PM.
