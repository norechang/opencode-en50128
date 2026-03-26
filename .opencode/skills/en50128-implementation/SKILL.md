---
name: en50128-implementation
description: C programming patterns with MISRA C:2012 compliance for EN 50128 railway safety software
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  coding-standard: MISRA C:2012
---

# EN 50128 Implementation Skill

This skill provides the IMP agent with authoritative reference data, the source code
generation algorithm, MISRA C technique table, and defect remediation logic for software
implementation per EN 50128 §7.5 and Table A.4.
**Load this skill before performing any IMP activity.**

---

## 1. Authoritative Sources

| What you need | Where to find it |
|---------------|-----------------|
| Phase 5 activities, deliverable paths, completion criteria | `activities/phase-5-implementation-testing.yaml` |
| Item 18 ownership, doc ID, SIL obligations | `activities/deliverables.yaml` |
| Annex C Table C.1 — full deliverable ownership catalogue | `DELIVERABLES.md` |
| Traceability rules T1–T15 (human-readable) | `TRACEABILITY.md` |
| Traceability obligations T1–T15 (machine-readable, agent consumption) | `activities/traceability.yaml` |
| Authority structure, two-track loop, CCB re-entry | `WORKFLOW.md` |
| Independence matrix (IMP = No at all SIL levels) | `ORGANIZATION.md` |
| §7.5 implementation requirements, Table A.4 techniques | `std/EN50128-2011.md` |
| C header template (.h stub) | `deliverables/implementation/C-Header-Template.h` |
| C module template (.c stub) | `deliverables/implementation/C-Module-Template.c` |
| MISRA C:2012 patterns (all 178 rules + 16 directives) | `resources/misra-c-coding-patterns.md` |
| Unit testing patterns (Unity framework, mocking, coverage) | `resources/unit-testing-patterns.md` |
| Code review checklist (124 items, 11 categories) | `resources/code-review-checklist.md` |
| Common implementation pitfalls (40+ with fixes) | `resources/common-pitfalls.md` |
| Component Design Spec (IMP input, item 15) | CM `query-location --doc component-design-spec` |
| Canonical source code path at runtime | CM `query-location` |

---

## 2. IMP Phase Footprint

IMP is the primary agent for Phase 5 (source code only).

| Annex C Item | Document | Owner | Phase |
|---|---|---|---|
| 18 | Software Source Code and supporting documentation | **IMP** | 5 |
| 19 | Software Source Code Verification Report | VER | 5 |
| 20 | Software Component Test Report | TST | 5 |

- IMP independence: Not required at any SIL level (see `ORGANIZATION.md`).
- IMP MUST NOT test own code for SIL 3–4 (TST is independent tester).
- IMP MUST NOT contact QUA or VER directly — route all submissions through PM.

---

## 3. implement-modules Algorithm (item 18)

Follow these steps in order. Do not skip steps.

1. **Invoke CM `query-location`** via `task` tool with `--doc source-code`. Record the
   canonical `src/` path. Never write to a hard-coded path.

2. **Read `.workspace`** to confirm active project name, SIL level, and base path.

3. **Verify Phase 5 prerequisites**: locate the Software Component Design Specification
   (item 15). If missing, halt and report to PM.

4. **Load templates** `deliverables/implementation/C-Header-Template.h` and `deliverables/implementation/C-Module-Template.c`
   as stubs. For each component in the SCDS:
   - Create `<component>.h` — public interface only (types, function declarations).
   - Create `<component>.c` — implementation with file-header traceability block.

5. **File header traceability block** (mandatory SIL 3–4, HR SIL 2, R SIL 0–1):
   ```
   /* Module: <component name>
    * Implements: REQ-FUN-NNN [, REQ-SAFE-NNN, ...]
    * Design ref: SCDS §<section> (item 15)
    * SIL: <level>
    */
   ```

6. **Apply MISRA C:2012** (mandatory SIL 2+):
   - Fixed-width types only: `uint8_t`, `uint16_t`, `uint32_t`, `int8_t`, etc.
   - Static allocation only: no `malloc`, `calloc`, `realloc`, `free`.
   - No variable-length arrays.
   - No recursion (HR SIL 2+).
   - No function pointers (HR SIL 2+).
   - Validate all pointer parameters before first use.
   - Check all function return values — never discard.
   - Named constants for all numeric literals (`#define` or `enum`).

7. **Enforce complexity limits**: SIL 0–1: ≤20; SIL 2: ≤15; SIL 3–4: ≤10 cyclomatic
   complexity per function. Refactor functions that would exceed the limit.

8. **Apply defensive programming** (HR all SIL levels):
   - Validate all inputs at function entry (NULL, range, plausibility).
   - Validate all outputs before returning.
   - Use safe arithmetic helpers for add/multiply/divide where overflow is possible.
   - Return an error code from every non-void function.

9. **Run `lizard`** on the completed source tree to confirm complexity within limits.
   Fix any violations before reporting to PM.

10. **Return the list of created source files** and a traceability summary
    (files created, requirements covered, any gaps) to PM.

---

## 4. Table A.4 Techniques (§7.5)

| # | Technique/Measure | Ref | SIL 0 | SIL 1–2 | SIL 3–4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Formal Methods | D.28 | – | R | HR |
| 2 | Modelling | A.17 | R | HR | HR |
| 3 | Structured Methodology | D.52 | R | HR | HR |
| 4 | **Modular Approach** | D.38 | HR | **M** | **M** |
| 5 | Components | A.20 | HR | HR | HR |
| 6 | **Design and Coding Standards** | A.12 | HR | HR | **M** |
| 7 | Analysable Programs | D.2 | HR | HR | HR |
| 8 | Strongly Typed Programming Language | D.49 | R | HR | HR |
| 9 | Structured Programming | D.53 | R | HR | HR |
| 10 | Programming Language | A.15 | R | HR | HR |
| 11 | Language Subset | D.35 | – | – | HR |
| 12 | Object Oriented Programming | A.22 | R | R | R |
| 13 | Procedural Programming | D.60 | R | HR | HR |
| 14 | Metaprogramming | D.59 | R | R | R |

**Mandatory**: Entry 4 (Modular Approach) SIL 2+; Entry 6 (Design and Coding Standards) SIL 3–4.
MISRA C:2012 is the EN 50128 platform's coding standard for entry 6.

**Coverage (Table A.21)**: No percentage thresholds in EN 50128:2011.
Table A.21 Req.1 requires a quantified measure defined per project (in the SVP/SQAP).
Technique recommendations: SIL 1: Statement R, Branch HR; SIL 2: Statement HR, Branch HR;
SIL 3–4: Branch HR, Compound Condition HR.

---

## 5. Defect Remediation (fix-defects)

When PM routes QUA/VER findings to IMP, apply this table:

| Finding Code | Description | Action | Confidence |
|---|---|---|---|
| `M001` | Dynamic memory allocation (`malloc`/`free`) | Replace with static array + index counter | HIGH — auto-fix |
| `M002` | Variable-length array | Replace with fixed-size `#define` array | HIGH — auto-fix |
| `M003` | Non-fixed-width type (`int`, `long`, etc.) | Replace with `uint32_t` / `int32_t` etc. | HIGH — auto-fix |
| `M004` | Unchecked return value | Add `err = f(); if (err != SUCCESS) { ... }` | HIGH — auto-fix |
| `M005` | NULL pointer not validated | Add NULL guard at function entry | HIGH — auto-fix |
| `M006` | Magic number literal | Extract to named `#define` or `enum` | HIGH — auto-fix |
| `M007` | Recursion (SIL 2+) | Refactor to iterative equivalent | MEDIUM — flag for review |
| `C001` | Cyclomatic complexity > limit | Decompose function into sub-functions | MEDIUM — flag for review |
| `C002` | Traceability comment missing (SIL 3–4) | Escalate to PM — requires SCDS lookup | LOW — escalate |
| `C003` | Algorithmic correctness defect | Escalate to PM — requires DES review | LOW — escalate |

**Escalation rule**: LOW-confidence findings MUST be escalated to PM with a written
description of the gap. IMP MUST NOT invent traceability links or change algorithms
without DES approval.

---

## 6. Document Interactions

```
Component Design Spec (item 15, DES) + SRS (item 6, REQ)
  └─► IMP reads: SCDS (item 15), SRS requirement IDs
        │
        └─► IMP writes: Source Code (item 18)
              │
              ├─► TST reads: source code → executes Component Test Spec (item 16)
              │                               → writes Component Test Report (item 20) [TST owns]
              └─► VER reads: source code → writes Source Code VER Report (item 19) [VER owns]
```

**IMP provides to**: TST (source code for unit test execution), VER (source code
for static analysis and verification), INT (compiled modules for integration).

**IMP receives from**: DES (SCDS item 15), REQ (SRS requirement IDs for traceability),
PM (task assignment, defect routing).

**IMP does NOT contact**: QUA or VER directly. All submissions go through PM.
