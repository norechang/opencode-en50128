---
name: en50128-lifecycle-capabilities
description: Detailed algorithms and output formats for all COD lifecycle coordination capabilities (Initialize, Gate Check, Status, Re-enter, etc.)
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  role: lifecycle-coordinator
---

# COD Capability Details

**Load trigger**: Load this skill when executing any COD capability.
Always load `en50128-lifecycle-coordination` first.

---

## Capability 1: Initialize Lifecycle

**Trigger**: `@cod plan --sil <0–4> --project <name>`

**Algorithm**:
```
1. Read .workspace file; resolve active_workspace path
2. Validate parameters: SIL ∈ {0,1,2,3,4}; project name is a valid directory name
3. Determine gate enforcement mode:
     SIL 0–1 → Advisory
     SIL 2   → Semi-strict
     SIL 3–4 → Strict Gatekeeper
4. Create examples/<project_name>/LIFECYCLE_STATE.md
   (schema: en50128-lifecycle-coordination skill §LIFECYCLE_STATE.md Schema)
   - Set Phase 0 (Initialization) = complete
   - Set Phases 1–9 = not started
5. Create workspace directory structure:
     docs/  docs/plans/  docs/changes/  docs/project/  src/  tests/
6. Display workspace context (project, SIL, mode, path)
7. Display independence requirements for the declared SIL level
   (source: ORGANIZATION.md)
8. Recommend: @pm execute-phase 1
```

**Output**:
```
═══════════════════════════════════════════════════════
COD: Lifecycle Initialization Complete
═══════════════════════════════════════════════════════

Active Workspace: <project_name> (SIL <level>)
   Path: examples/<project_name>/
   COD Mode: <enforcement_mode>

✓ LIFECYCLE_STATE.md created
✓ Directory structure initialized
✓ Phase 0 (Initialization) marked COMPLETE

Independence Requirements (SIL <level>):
  [list applicable independence mandates from ORGANIZATION.md]

Next Steps:
  1. Assign roles with independence verification
  2. Run: @pm execute-phase 1
```

---

## Capability 2: Start Phase

**Trigger**: `@cod start-phase <phase-id>`

**Phase IDs**: `planning` | `requirements` | `architecture-design` | `component-design` |
`implementation-testing` | `integration` | `validation` | `assessment` | `deployment`

**Algorithm**:
```
1. Read .workspace and LIFECYCLE_STATE.md
2. Verify previous phase gate = PASSED (cannot skip phases)
3. Verify entry criteria satisfied (source: activities/phase-N-*.yaml §entry_criteria)
4. Update LIFECYCLE_STATE.md:
     current_phase = <phase-id>; status = in_progress; start_timestamp = now
5. Display phase name, required deliverables (→ DELIVERABLES.md for the phase),
   expected agents, entry criteria checklist
6. Coordinate with PM: notify to execute @pm execute-phase <phase-id>
```

---

## Capability 3: Gate Check

**Trigger**: `@cod gate-check <phase-id>`

**Algorithm**:
```
1. Read .workspace and LIFECYCLE_STATE.md
2. Run deterministic approval-chain tool (mandatory first step):
     python3 tools/workspace.py wf gate-check --phase <N> --sil <SIL>
   - Exit 1 at SIL 3–4 → BLOCK immediately; report violations to PM
   - Exit 1 at SIL 0–2 → record as warning; request justification
3. Load en50128-lifecycle-phase-checklists skill
4. Verify deliverables:
   - All required documents present (source: activities/phase-N-*.yaml §gate_check §criteria)
   - Document control fields populated (ID, version, approval signatures)
5. Verify quality criteria:
   - QUA template compliance recorded for every deliverable and every V&V report
   - Coverage metrics meet SIL threshold (source: activities/lifecycle.yaml §sil_requirements)
   - Cyclomatic complexity within limit (SIL 3–4 ≤ 10; SIL 2 ≤ 15; SIL 0–1 ≤ 20)
   - MISRA C compliance reported (SIL 2+ mandatory)
   - Static analysis results available (SIL 3–4 mandatory)
6. Verify traceability:
   - RTM completeness for the phase (rules T1–T15 in TRACEABILITY.md)
   - Forward and backward traces complete; no orphan items
7. Verify V&V:
   - VER report exists and approved (all SIL levels)
   - VMGR approval of VER report recorded (SIL 3–4)
   - VAL report exists and approved (SIL 3–4 all phases; SIL 0–2 Phases 5 and 7)
   - VMGR approval of VAL report recorded (SIL 3–4)
8. Apply SIL enforcement:
   - SIL 0–1: report failures as warnings; allow user override with acknowledgment
   - SIL 2:   report failures; require written justification to proceed
   - SIL 3–4: BLOCK transition on any failure; no override permitted
9. Update LIFECYCLE_STATE.md: gate check result (PASS/FAIL), timestamp, defect list if FAIL
10. If PASS: authorize next phase; if FAIL: list defects with owner, severity, action required
```

**Output (PASS)**:
```
═══════════════════════════════════════════════════════
COD: Phase <N> Gate Check — PASSED ✅
═══════════════════════════════════════════════════════

Active Workspace: <project_name> (SIL <level>)
   Phase: <name> | Completion: <N>%

Gate Criteria: <X>/<X> PASSED ✅

Deliverables: [per DELIVERABLES.md for this phase — all ✅]
Quality Criteria: [all ✅]
Traceability: [RTM completeness ✅]
Approval Chain (SIL <level>): [chain ✅]
Verification / Validation: [VER ✅ | VAL ✅ | VMGR ✅]
Independence: [all constraints ✅]

═══════════════════════════════════════════════════════
GATE STATUS: AUTHORIZED ✅
═══════════════════════════════════════════════════════

Phase <N+1> (<name>) AUTHORIZED to begin.
Recommended: @cod start-phase <next-phase-id>
```

**Output (FAIL — SIL 3–4)**:
```
═══════════════════════════════════════════════════════
COD: Phase <N> Gate Check — FAILED ❌
═══════════════════════════════════════════════════════

Active Workspace: <project_name> (SIL <level>) — Strict Gatekeeper

Gate Criteria: <X>/<Y> PASSED (<Z> FAILURES) ❌

Defects Found:

  DEFECT-<PHASE>-<NNN>: <description>
    Severity: Critical | Major | Minor
    Owner: <agent>
    Required Action: <action>
    Reference: EN 50128 §<clause>

═══════════════════════════════════════════════════════
GATE STATUS: BLOCKED ❌ (SIL <level> — No Override)
═══════════════════════════════════════════════════════

Phase <N+1> CANNOT begin until all defects resolved.
Recommended: PM coordinates defect resolution, then re-run gate check.
```

---

## Capability 4: Lifecycle Status Report

**Trigger**: `@cod status`

**Algorithm**:
```
1. Read .workspace and LIFECYCLE_STATE.md
2. Extract and format:
   - Project metadata (name, SIL, COD mode)
   - Current phase and status
   - Phase history table (all phases with status, dates, gate results)
   - Deliverable status for current phase
   - Traceability coverage percentages
   - Quality metrics summary (complexity, coverage, open defects)
   - Pending actions and next recommended command
3. Display formatted report
```

---

## Capability 5: Re-run Phase After Defect Resolution

**Trigger**: PM notifies COD that all defects from a failed gate check have been resolved.

**Algorithm**:
```
1. Read LIFECYCLE_STATE.md; confirm phase gate previously FAILED and defects marked resolved
2. Verify QUA has accepted all reworked deliverables
3. Re-coordinate V&V:
   - SIL 3–4: COD → VMGR → VER re-verify → QUA (VER report) → VMGR re-approve
               COD → VAL re-validate (via VMGR) → QUA (VAL report) → VMGR re-approve
   - SIL 0–2: COD → VER re-verify directly; VAL if applicable
4. Run gate-check (Capability 3) for the same phase
5. Update LIFECYCLE_STATE.md with new gate check result
```

**Output**: Same format as Capability 3 gate check (PASS or FAIL).

---

## Capability 6: Re-enter Phases After Approved Change

**Trigger**: PM notifies COD that a CCB-approved Change Request is ready for implementation.
**EN 50128 reference**: §5.5 (software modification), §5.3.2.13 (phase modification authority).

**Algorithm**:
```
1. Read .workspace, LIFECYCLE_STATE.md, and approved CR from docs/changes/CR-<YYYY>-<NNN>.md
2. Determine affected phases from CR impact analysis:
   - Requirements change (SRS)         → Phase 2 onward
   - Design change (SAS/SDS)           → Phase 3 onward
   - Component design change           → Phase 4 onward
   - Code / unit test change           → Phase 5 onward
   - Integration change                → Phase 6 onward
   Record earliest affected phase and full set [phase_start … current_phase]
3. Mark all affected phases in LIFECYCLE_STATE.md:
     status = "re-entry-required"; reference = CR-<YYYY>-<NNN>
4. Instruct CM to create a baseline branch for CR implementation
   (per WORKFLOW.md Diagram 4)
5. For each affected phase in forward order from phase_start:
   a. COD → PM: "Re-execute phase <id> activities for CR <cr-id>"
   b. PM executes @pm execute-phase <id> (fixes + QUA-accepted deliverables)
   c. PM → COD: "Phase <id> activities re-complete"
   d. COD coordinates re-verification (Capability 5 re-verification step)
   e. COD runs gate-check for phase (Capability 3)
   f. PASS → mark phase re-entry complete in LIFECYCLE_STATE.md
      FAIL → apply SIL enforcement (block or warn); resolve then repeat
6. When all affected gates re-pass:
   - Update CR status in LIFECYCLE_STATE.md to "implemented-verified"
   - Instruct CM to create updated post-CR baseline
   - Resume normal lifecycle from current (highest) phase
```

**Output**:
```
═══════════════════════════════════════════════════════
COD: Re-entering Phases — CR-<YYYY>-<NNN>
═══════════════════════════════════════════════════════

Active Workspace: <project_name> (SIL <level>)
CR: <cr-id> — <description>
Earliest Affected Phase: Phase <N> (<name>)
Phases requiring re-entry: [Phase N, Phase N+1, …]

Re-entering Phase <N>:
  PM activities…     ✅ complete (QUA-accepted)
  VER re-verify…     ✅ PASSED
  Gate check…        ✅ PASSED

[repeat for each affected phase]

═══════════════════════════════════════════════════════
CR-<YYYY>-<NNN> RE-ENTRY COMPLETE ✅
═══════════════════════════════════════════════════════

CM: Updated baseline created (post-<cr-id>)
Next: Resume Phase <current_phase> or proceed to next phase gate.
```

---

## Capability 7: Notify User

**Trigger**: Critical lifecycle event (gate block, approval required, phase transition).

**Algorithm**:
```
1. Format message with: severity, workspace context, phase, timestamp
2. Display notification to user
3. Log notification in LIFECYCLE_STATE.md
4. State required action clearly
```

**Output**:
```
═══════════════════════════════════════════════════════
COD NOTIFICATION — <severity> (SIL <level> — <mode>)
═══════════════════════════════════════════════════════

Active Workspace: <project_name> | Phase: <name> | <timestamp>

MESSAGE: <event description>

Action Required: <what user must do>
```

---

## Capability 8: Finish Phase

**Trigger**: `@cod finish-phase` (after gate check PASS confirmed).

**Algorithm**:
```
1. Read LIFECYCLE_STATE.md; verify current phase gate = PASSED
2. Update LIFECYCLE_STATE.md:
   - Mark phase status = "complete"; record completion timestamp
   - Increment overall completion percentage (each of Phases 1–9 = ~11%)
3. Display phase completion summary (duration, deliverable count, gate result, VMGR approval if SIL 3–4)
4. Display next phase name and recommended command
```

---

## Capability 9: Generate System Documents

**Trigger**: `@cod generate-system [--system <N>]`

**Preconditions** (fail fast if not met):
```
1. .workspace exists with valid active_workspace
2. LIFECYCLE_STATE.md exists in workspace root
3. Phase 0 status = "complete" in LIFECYCLE_STATE.md
4. assets/sample_system/TYPICAL-SYSTEMS.md is readable
5. docs/system/ does NOT already contain generated docs (warn; require --overwrite to proceed)
6. EN 50126 standards available: std/EN 50126-1-2017.md and std/EN 50126-2-2017.md
```

**Algorithm**:
```
1. Read .workspace → active_workspace path
2. Read LIFECYCLE_STATE.md → project_name, sil_level, today's date
3. Check preconditions (error messages defined above)
4. Read EN 50126 standards for reference:
   - std/EN 50126-1-2017.md (RAMS Part 1: Generic RAMS Process)
   - std/EN 50126-2-2017.md (RAMS Part 2: Systems approach to safety)
5. Read assets/sample_system/TYPICAL-SYSTEMS.md → system list
6. If --system not provided: present numbered menu (name, SIL, domain, "Recommended For");
   ask user to select
7. Read selected system's catalogue entry:
   Overview, Hazard List (HAZ-xxx), Functional Requirements (SYS-FR-xxx),
   Safety Functions (SF-xxx), System Architecture, Communication Interfaces,
   Non-Functional Requirements, Design Constraints, Glossary
8. Read document templates from assets/sample_system/:
   - System-Requirements-Specification-TEMPLATE.md
   - System-Architecture-Description-TEMPLATE.md
   - System-Safety-Requirements-Specification-TEMPLATE.md
   - System-Safety-Plan-TEMPLATE.md
9. Create <workspace>/docs/system/
10. Generate four documents using templates (rules below) — content MUST be substantive, NOT generic placeholders
11. Register all four files in LIFECYCLE_STATE.md §System Documents
12. Display confirmation summary with file paths and content counts
```

**Document metadata substitution** (all four documents):
- Project name → `LIFECYCLE_STATE.md §project_name`
- SIL level → `LIFECYCLE_STATE.md §sil_level`
- System name → catalogue entry
- Date → today (YYYY-MM-DD)
- Doc IDs → DOC-SYS-{REQ|ARCH|SAF|PLAN}-YYYY-001
- Version → 1.0
- Approval fields → `[PENDING]`

**Standard References** (include in all documents where applicable):
- EN 50126-1:2017 - RAMS Part 1: Generic RAMS Process
- EN 50126-2:2017 - RAMS Part 2: Systems approach to safety
- EN 50128:2011 - Software for railway control and protection systems
- EN 50129:2018 - Safety related electronic systems for signalling

**Document 1 — System Requirements Specification**
- File: `docs/system/System-Requirements-Specification.md`
- Template: `assets/sample_system/System-Requirements-Specification-TEMPLATE.md` (MANDATORY USE)
- EN 50126 Reference: Part 1 Section 5 (System Definition and Application Conditions), Part 2 Section 5 (Hazard identification and risk analysis)
- Populate: §1 intro (name, SIL, standards including EN 50126-1 and EN 50126-2); §1.4 hazard summary (HAZ table);
  §2 functional requirements (SYS-FR-xxx — each with ID, description, rationale, SIL, verification method);
  §2 non-functional requirements; §3 requirements allocation to HW/SW/operational;
  §4 architecture overview; §5 V&V reference to SVP/SVaP;
  §6 traceability (SYS-FR-xxx → SW-REQ-xxx as [TBD], to be completed by @req);
  §8 glossary (all catalogue entries)

**Document 2 — System Architecture Description**
- File: `docs/system/System-Architecture-Description.md`
- Template: `assets/sample_system/System-Architecture-Description-TEMPLATE.md` (MANDATORY USE)
- EN 50126 Reference: Part 1 Section 6 (System Design and Implementation), Part 2 Section 6.4 (Architecture for safety)
- Populate: §2 architecture overview (system boundary, decomposition table);
  §3 hardware architecture (all HW components; ASCII block diagram);
  §4 software architecture (all SW components with purpose);
  §5 safety architecture (SF-xxx → component mapping, redundancy scheme per EN 50126-2);
  §6 communication architecture (full catalogue interface table);
  §8 HW/SW interface (signals, HAL structure);
  §10 ICDs (stub per external interface);
  §12 traceability (SYS-FR-xxx → architecture component);
  §13 references (applicable standards from catalogue including EN 50126-1, EN 50126-2)

**Document 3 — System Safety Requirements Specification**
- File: `docs/system/System-Safety-Requirements-Specification.md`
- Template: `assets/sample_system/System-Safety-Requirements-Specification-TEMPLATE.md` (MANDATORY USE)
- EN 50126 Reference: Part 2 Section 5 (Hazard identification, risk assessment, SIL allocation), Section 6 (Safety requirements), Section 7 (FMEA/FTA analysis)
- Populate: §2.1 hazard identification (full HAZ table with severity/frequency/SIL per EN 50126-2 risk matrix);
  §2.2 SIL determination rationale (per EN 50126-2 Table 3);
  §2.3 FMEA (one row per HW component — failure mode/effect derived from hazards; mitigation = SF reference);
  §2.4 FTA stub (top event = most catastrophic hazard; gates from contributing hazards);
  §3 safety functions (full SF table — ID, description, SIL, derived from HAZ references);
  §3.3 CCF analysis (common cause failure notes from redundancy architecture);
  §4 safety function allocation (SF-xxx → HW/SW/combined per EN 50126-2);
  §5.2 SW integrity requirements (SIL-specific, referencing EN 50128 and EN 50126-2 Section 6.5);
  §7 hazard log (all HAZ entries, status = OPEN);
  §8 traceability (HAZ → SF → SYS-FR cross-reference matrix)

**Document 4 — System Safety Plan**
- File: `docs/system/System-Safety-Plan.md`
- Template: `assets/sample_system/System-Safety-Plan-TEMPLATE.md` (MANDATORY USE)
- EN 50126 Reference: Part 1 Section 4 (RAMS lifecycle and management), Part 2 Section 4 (Safety management), Section 8 (Safety management plan requirements)
- Populate: §1 intro (name, SIL, scope referencing EN 50126-1 lifecycle);
  §2 safety management organization (Safety Manager, ISA, PM with [NAME TBD] per EN 50126-2 Section 4.2);
  §3 safety lifecycle (phases → EN 50126-1 V-Model; reference LIFECYCLE_STATE.md);
  §4 hazard management (process referencing SSRS Hazard Log; FMEA/FTA schedule per EN 50126-2);
  §5 safety requirements management (traceability chain: hazards → SF → SW req per EN 50126-2 Section 6);
  §6 safety V&V (activities table per lifecycle phase; reference SVP/SVaP and EN 50126-1 Section 7);
  §7 ISA plan (scope = SIL level and all SF-xxx; independence requirements per EN 50126-2 Section 4.4);
  §8 safety case (outline per EN 50129 Annex B);
  §12 change management (safety-relevant change control; reference @cm and CCB process per EN 50126-1 Section 9);
  §13 safety metrics (PFH target, coverage target, defect density target based on SIL per EN 50126-2 Annex B)

**LIFECYCLE_STATE.md update** — add after generation:
```markdown
## System Documents

Generated by: @cod generate-system
System: <system_name>
Date: <YYYY-MM-DD>

| Document | File | Status |
|----------|------|--------|
| System Requirements Specification | docs/system/System-Requirements-Specification.md | GENERATED |
| System Architecture Description | docs/system/System-Architecture-Description.md | GENERATED |
| System Safety Requirements Specification | docs/system/System-Safety-Requirements-Specification.md | GENERATED |
| System Safety Plan | docs/system/System-Safety-Plan.md | GENERATED |

Note: Review and approve with system engineering team before Phase 2.
```

**EN 50128 references**: §7.2.2, §7.2.2(a), §7.2.2(b), §7.2.2(c)
**EN 50126 references**: Part 1 Sections 4–7; Part 2 Sections 4–8 (RAMS lifecycle, safety management, hazard analysis, safety requirements)

---

## Capability 10: Sync README

**Trigger**: `@cod sync-readme`

**Algorithm**:
```
1. Read LIFECYCLE_STATE.md: current phase, completion %, last gate check result
2. Read README.md
3. Update README.md "Current Status" section:
   - Current phase name and number
   - Completion percentage
   - Last gate check result and date
   - Next recommended action
4. Update phase progress checklist (✅ complete / ⏳ in progress / — not started per phase)
5. Write README.md
6. Report: fields updated, file written
```
