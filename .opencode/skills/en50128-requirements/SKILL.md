---
name: en50128-requirements
description: Requirements engineering patterns and workflows for EN 50128 railway software compliance
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
---

# EN 50128 Requirements Skill

This skill provides the REQ agent with authoritative reference data, the SRS generation
algorithm, quality rules, traceability rules, and defect remediation logic.
**Load this skill before performing any REQ activity.**

---

## 1. Authoritative Sources

| What you need | Where to find it |
|---------------|-----------------|
| Phase 2 activities, deliverable paths, completion criteria | `activities/phase-2-requirements.yaml` |
| Item 6 doc ID, template path, SIL obligations, user_approval flag | `activities/deliverables.yaml` lines 164–205 |
| Annex C Table C.1 — full deliverable ownership catalogue | `DELIVERABLES.md` |
| Traceability rules T1–T15 | `TRACEABILITY.md` |
| Authority structure, two-track loop, rework path | `WORKFLOW.md` |
| Independence matrix (REQ = No at all SIL levels) | `ORGANIZATION.md` |
| §7.2 SRS requirements, Table A.2 techniques, §7.2.4.5 traceability | `std/EN50128-2011.md` |
| SRS template (primary artifact for item 6) | `templates/Software-Requirements-Specification-template.md` |
| SAF phase footprint, Hazard Log ownership | `tasks/SAFETY_ENGINEERING.md` |
| Canonical document paths at runtime | CM `query-location` |

---

## 2. REQ Phase Footprint

REQ is the primary agent for Phase 2 only.

| Annex C Item | Document | Owner | Phase |
|---|---|---|---|
| 6 | Software Requirements Specification (SRS) | **REQ** | 2 |
| 7 | Overall Software Test Specification | TST | 2 |
| 8 | Software Requirements Verification Report | VER | 2 |

- SAF co-authors the safety requirements section of item 6 (hazard identification, SIL assignment).
- REQ has NO authorship role in items 7 or 8.
- Item 6 carries `user_approval_required: true` — user/customer must approve before Track B (VER).
- REQ independence: Not required at any SIL level (see `ORGANIZATION.md`).

---

## 3. SRS Generation Algorithm (create-srs)

Follow these 15 steps in order. Do not skip steps.

1. **Invoke CM `query-location`** via `task` tool with `--doc srs`. Record the canonical path.
   Never proceed with a hard-coded path.

2. **Read `.workspace`** to confirm active project name, SIL level, and base path.

3. **Verify Phase 2 prerequisites** (§7.2.2): locate the four system documents:
   - System Requirements Specification
   - System Architecture Description
   - System Safety Plan
   - System Safety Requirements Specification
   If any are missing, halt and report to PM with the specific missing document(s).

4. **Load the SRS template** from `templates/Software-Requirements-Specification-template.md`.
   Fill the Document Control block (doc ID = `DOC-SRS-YYYY-001`, version = `0.1 DRAFT`).

5. **Fill the Approvals table** using project SIL level to determine required signatories:
   - SIL 0–2: Author (REQ) + QUA + VER
   - SIL 3–4: Author (REQ) + QUA + VER + VAL + PM
   Do not add "Safety Manager" or "QA Manager" — those are not EN 50128 roles.

6. **Extract functional requirements** from the System Requirements Specification.
   Assign IDs: `REQ-FUN-NNN` (3-digit zero-padded). Each requirement must include:
   description, rationale, acceptance criteria, verification method.

7. **Extract performance requirements**. Assign IDs: `REQ-PERF-NNN`.
   Include timing constraints, resource limits, WCET requirements where applicable.

8. **Extract interface requirements**. Assign IDs: `REQ-INT-NNN`.
   Specify hardware/software interfaces, protocols, data types (use fixed-width C types:
   `uint8_t`, `uint16_t`, `uint32_t`).

9. **Invoke SAF** via `task` tool: request hazard analysis output for Phase 2.
   Extract safety requirements from SAF's Hazard Log output. Assign IDs: `REQ-SAFE-NNN`.
   SAF is the hazard authority — do not independently classify or close hazards.

10. **Assign SIL levels** to each requirement. Base the assignment on hazard traceability
    (SAF-provided SIL classification). Document the rationale for each SIL assignment.

11. **Establish backward traceability** for each requirement:
    - SIL 0–1: Recommended (`R`) — include if available
    - SIL 2: Highly Recommended (`HR`) — include; document reason if omitted
    - SIL 3–4: Mandatory (`M`) — every requirement MUST have a system req or hazard parent
    Format: `Traceability: SYS-REQ-NNN [, HAZ-NNN]`

12. **Apply Table A.2 techniques** per SIL level (see Section 6 below). Document in the
    SRS which technique(s) were applied and where (section reference).

13. **Verify quality attributes** for every requirement using the 8-attribute checklist
    in Section 4 below. Fix any failing requirements before submission.

14. **Verify modal verb usage** per `resources/shall-should-may.md`:
    - `SHALL` = mandatory requirement
    - `SHOULD` = highly recommended
    - `MAY` = optional
    - Never use `WILL` as a requirement keyword.

15. **Write the completed SRS** to the canonical path from Step 1. Set version `0.1 DRAFT`.
    Return the path and a summary (requirement count by type, SIL distribution) to PM.

---

## 4. Requirements Quality Rules

Every requirement MUST satisfy all 8 attributes:

| Attribute | Criterion |
|-----------|-----------|
| **Unambiguous** | Single interpretation only; no vague terms ("reasonable", "adequate") |
| **Testable** | Can be verified with an objective, repeatable pass/fail criterion |
| **Clear** | Understood by a qualified engineer on first reading |
| **Correct** | Accurately reflects the stated stakeholder or system need |
| **Feasible** | Technically achievable within project constraints |
| **Atomic** | States one and only one thing; cannot be split into smaller requirements |
| **Necessary** | Would be missed if omitted; no gold-plating |
| **Implementation-free** | Does not prescribe a solution; specifies WHAT not HOW |

**Requirement ID format**: `REQ-[TYPE]-[NNN]`
Types: `FUN` (functional), `PERF` (performance), `INT` (interface), `SAFE` (safety)

---

## 5. Traceability Rules

Source of truth: `TRACEABILITY.md` (rules T1–T15). Summary for REQ:

| SIL | Obligation | What to trace |
|-----|-----------|---------------|
| 0–1 | R | SW req → system req (include if available) |
| 2 | HR | SW req → system req; document reason if any omitted |
| 3–4 | **M** | SW req → system req AND/OR hazard; 100% coverage required |

**Backward traceability** (REQ owns): every software requirement traces to a system
requirement or hazard. Embed in each requirement block: `Traceability: SYS-REQ-NNN`.

**Forward traceability** (DES/TST own): requirements → design elements → test cases.
REQ does not produce forward traceability links; those are produced by DES and TST.

**RTM format**: Embedded traceability fields in the SRS are sufficient for SIL 0–3.
For SIL 3–4 projects, PM may request a standalone Requirements Traceability Matrix
(`docs/requirements/Requirements-Traceability-Matrix.md`). If requested, REQ generates
it as a Markdown table: `REQ-ID | Description | SYS-REQ | HAZ | Design | Tests | Code`.

---

## 6. Table A.2 Techniques

EN 50128:2011 Table A.2 — requirements specification techniques:

| # | Technique | Ref | SIL 0 | SIL 1–2 | SIL 3–4 |
|---|-----------|-----|-------|---------|---------|
| 1 | Formal Methods | D.28 | – | R | HR |
| 2 | Modelling | Table A.17 | R | R | HR |
| 3 | Structured Methodology | D.52 | R | R | HR |
| 4 | Decision Tables | D.13 | R | R | HR |

At least one technique SHALL be selected and applied. For SIL 3–4, document which
technique(s) were used and in which SRS section(s) they appear. See `std/EN50128-2011.md`
§7.2 and Annex D for authoritative technique descriptions.

---

## 7. Defect Remediation (fix-defects)

When PM routes QUA findings to REQ, apply this table:

| Finding Code | Description | Action | Confidence |
|---|---|---|---|
| `T001` | Document ID format incorrect | Reformat to `DOC-SRS-YYYY-001` | HIGH — auto-fix |
| `T002` | Document Control block missing/incomplete | Insert standard block from template | HIGH — auto-fix |
| `T003` | Approvals table missing or wrong roles | Replace with SIL-correct approvals (see Step 5) | HIGH — auto-fix |
| `T004` | Required section absent | Add section heading + TBD marker | HIGH — auto-fix |
| `Q001` | Requirement ID missing or malformed | Assign next available ID in sequence | HIGH — auto-fix |
| `Q002` | SIL level not assigned | Add project SIL level with rationale | HIGH — auto-fix |
| `Q003` | Modal verb missing (no SHALL/SHOULD/MAY) | Rewrite requirement with correct keyword | MEDIUM — flag for review |
| `Q004` | Verification method absent | Add `Test`, `Review`, or `Inspection` | MEDIUM — flag for review |
| `C001` | Traceability field missing (SIL 3–4) | Escalate to PM — requires SAF input | LOW — escalate |
| `C002` | Acceptance criteria not testable | Escalate to PM — requires stakeholder input | LOW — escalate |

**Escalation rule**: LOW-confidence findings MUST be escalated to PM with a written
description of the gap. REQ MUST NOT invent traceability links or acceptance criteria.

---

## 8. Document Interactions

```
Phase 0 system docs (S1–S4)
  └─► REQ reads: System Requirements Spec, System Safety Requirements Spec
        │
        ├─► SAF: hazard analysis → REQ-SAFE-xxx safety requirements
        │
        └─► REQ writes: SRS (item 6)
                │
                ├─► DES reads: SRS → Software Architecture Specification
                ├─► TST reads: SRS → Overall SW Test Specification (item 7) [TST owns]
                └─► VER reads: SRS → Software Requirements Verification Report (item 8) [VER owns]
```

**REQ provides to**: DES (forward traceability base), TST (testability requirements),
VER (item 6 for verification), VAL (2nd-check on item 6).

**REQ receives from**: System documents (Phase 0), SAF (Hazard Log, SIL assignments),
PM (task assignment, defect routing, user approval confirmation).

**REQ does NOT contact**: QUA or VER directly. All submissions go through PM.
