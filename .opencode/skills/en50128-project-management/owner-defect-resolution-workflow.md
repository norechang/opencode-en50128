# Owner Agent - Defect Resolution Workflow

This document defines the standard workflow for all owner agents (REQ, SAF, TST, DES, IMP) to handle QUA defect resolution.

---

## Overview

When an owner agent creates a deliverable (e.g., REQ creates SRS), the deliverable must pass through QUA review before PM accepts it. If QUA finds defects, the owner must fix them and resubmit (max 3 iterations).

**Approval Flow**: Owner → QUA → [Fix Loop] → PM

Owner agents are invoked by PM via the `task()` tool. QUA review is also invoked by PM (or by the owner agent itself) via `task()`. There are no slash commands — all inter-agent invocations use the `task()` tool.

---

## Workflow: Submit Deliverable to QUA

When PM invokes an owner agent to create a deliverable, the owner agent shall:

1. Create the deliverable (document or code artifact)
2. Invoke QUA via `task()` to review the deliverable:
   ```
   task({
     description: "Review <doc-name>",
     subagent_type: "qua",
     prompt: "Review <doc-path> for <doc-type> compliance. SIL: <N>. Return PASS or FAIL with defect list."
   })
   ```
3. Receive QUA result: PASS or FAIL + defect list
4. If PASS:
   - Log: "✓ [Document] accepted by QUA"
   - Return SUCCESS to PM (deliverable path + status)
5. If FAIL:
   - Log: "✗ [Document] rejected by QUA ([N] errors)"
   - Proceed to defect fix loop (see below)

**Output (PASS)**:
```
Submitting docs/SRS.md to QUA for review...
✓ SRS accepted by QUA (0 defects)
Status: READY FOR PM ACCEPTANCE
```

**Output (FAIL)**:
```
Submitting docs/SRS.md to QUA for review...
✗ SRS rejected by QUA (2 errors, 1 warning)

Defects found:
1. [ERROR] SRS-T001: Document ID format incorrect
   Location: Document Control table
   Fix: Update Document ID to "DOC-SRS-2026-001"

2. [ERROR] SRS-Q002: Requirement REQ-TDC-023 missing SIL level
   Location: Section 3.1
   Fix: Add SIL level (SIL 0-4)

3. [WARNING] SRS-Q005: Requirement REQ-TDC-045 exceeds 500 characters
   Location: Section 3.2
   Fix: Consider splitting into multiple requirements

Status: DEFECTS MUST BE FIXED — proceeding to auto-fix loop
```

---

## Workflow: Fix Defects

When QUA returns defects, the owner agent shall apply automated fixes directly to the deliverable:

1. Load the document
2. For each defect in the defect list:
   a. Parse the defect (check_id, location, issue, fix_suggestion)
   b. Apply automated fix based on defect type (see fix strategies below)
   c. Log fix applied
3. Save the updated document
4. Resubmit to QUA (repeat submit workflow above)

**Output**:
```
Fixing defects in docs/SRS.md...

Defect 1/2: SRS-T001 - Document ID format
  Location: Document Control table
  Action: Updated Document ID from "DOC-SRS-2026-1" to "DOC-SRS-2026-001"
  ✓ Fixed

Defect 2/2: SRS-Q002 - Missing SIL level
  Location: REQ-TDC-023
  Action: Added "SIL 3" (inherited from project SIL)
  ✓ Fixed

Summary: 2/2 defects fixed
Status: READY FOR RESUBMISSION
```

---

## Workflow: Submit with Retry Loop

The owner agent shall iterate up to `max_iterations` (default: 3) times:

```
iteration = 1
while iteration <= max_iterations:
  1. Invoke QUA via task() to review document
  2. If QUA PASS:
     - Log: "✓ [Document] accepted by QUA after [N] iteration(s)"
     - Return: SUCCESS to PM
  3. If QUA FAIL:
     - Log: "✗ Iteration [N]/[max]: QUA rejected with [M] errors"
     - If iteration < max_iterations:
       - Apply auto-fixes to document
       - Increment iteration
       - Continue loop
     - Else:
       - Log: "⚠ Failed after [max] iterations, escalating to user"
       - Return: ESCALATE + remaining defect list to PM
```

**Output (Success after 2 iterations)**:
```
=== Iteration 1/3 ===
Submitting docs/SRS.md to QUA...
✗ QUA rejected (2 errors)
Fixing defects automatically...
  ✓ Fixed 2/2 defects

=== Iteration 2/3 ===
Submitting docs/SRS.md to QUA...
✓ QUA accepted

Summary: SRS accepted by QUA after 2 iterations
Status: READY FOR PM ACCEPTANCE
```

**Output (Escalation after 3 iterations)**:
```
=== Iteration 1/3 ===
Submitting docs/SRS.md to QUA...
✗ QUA rejected (3 errors)
Fixing defects automatically...
  ✓ Fixed 2/3 defects
  ✗ Could not auto-fix 1 defect (requires manual intervention)

=== Iteration 2/3 ===
Submitting docs/SRS.md to QUA...
✗ QUA rejected (1 error)
Fixing defects automatically...
  ✗ Could not auto-fix 1 defect (complex issue)

=== Iteration 3/3 ===
Submitting docs/SRS.md to QUA...
✗ QUA rejected (1 error)

⚠ ESCALATION REQUIRED
Failed to pass QUA review after 3 iterations.

Remaining defect:
1. [ERROR] SRS-C002: Traceability section incomplete
   Location: Section 7
   Issue: RTM reference missing
   Manual fix required: Add reference to RTM document

Status: REQUIRES USER INTERVENTION
Action: Please fix defect manually and retry
```

---

## Defect Auto-Fix Logic

### High-Confidence Fixes (Always Automated)

1. **Document ID format** (SRS-T001, HAZ-T001, TST-T001)
   ```
   From: "DOC-SRS-2026-1"
   To:   "DOC-SRS-2026-001"
   Logic: Pad number to 3 digits, ensure format DOC-XXX-YYYY-NNN
   ```

2. **Missing Document Control table** (SRS-T002, HAZ-T002, TST-T002)
   ```
   Action: Insert standard Document Control table template
   ```

3. **Missing Approvals table** (SRS-T003, HAZ-T003, TST-T003)
   ```
   Action: Insert standard Approvals table with SIL-appropriate roles
   ```

4. **Item ID format** (SRS-Q001, HAZ-Q001, TST-Q001)
   ```
   From: "REQ-TDC-1"
   To:   "REQ-TDC-001"
   Logic: Pad number to 3 digits
   ```

5. **Missing SIL level** (SRS-Q002)
   ```
   Action: Add project SIL level to requirement
   Logic: If project is SIL 3, add "SIL 3"
   ```

6. **Missing keywords** (SRS-Q003)
   ```
   Action: Add appropriate keyword based on context
   Logic: Mandatory requirements → SHALL, recommendations → SHOULD
   ```

### Medium-Confidence Fixes (Automated with Caution Flag)

1. **Missing verification method** (SRS-Q004)
   ```
   Action: Add default verification method
   Logic: Functional requirements → "Test", non-functional → "Review"
   Flag: ⚠ Auto-assigned, please review
   ```

2. **Missing section** (SRS-T004, HAZ-T004, TST-T004)
   ```
   Action: Add section with template structure
   Flag: ⚠ Section added with placeholder content
   ```

### Low-Confidence Fixes (Escalate to User)

1. **Content issues** (SRS-C002, HAZ-C006, TST-C002)
   ```
   Examples:
   - Traceability incomplete
   - Coverage < 100%
   - Complex logical errors
   Action: ESCALATE (cannot auto-fix)
   ```

2. **Requirement text issues** (SRS-Q005)
   ```
   Example: Requirement too long (> 500 chars)
   Action: WARNING only (user decides whether to split)
   ```

---

## Integration with PM Phase Execution

When PM executes a phase (invoked by user as `@pm execute-phase <phase-id>`), PM orchestrates owner agents via the `task()` tool using the following pattern:

```python
# Pseudocode for PM phase execution inner loop
for activity in phase.activities:
  # 1. Invoke owner to create deliverable
  owner_result = task({
    subagent_type: activity.agent,
    prompt: f"Create {activity.deliverable_name} for {phase_id}. ..."
  })
  
  # owner_result includes deliverable path + QUA submit-with-retry outcome
  
  # 2. Handle result
  if owner_result.qua_status == "SUCCESS":
    pm.mark_deliverable_accepted(owner_result.deliverable)
    print(f"✓ {owner_result.deliverable.name} accepted by QUA after {owner_result.iterations} iteration(s)")
  
  elif owner_result.qua_status == "ESCALATE":
    # User intervention required
    print(f"⚠ {owner_result.deliverable.name} requires manual intervention")
    print(f"Remaining defects: {owner_result.defects}")
    
    # PM suspends phase execution and asks user how to proceed:
    # - Fix manually and PM retries (invokes same owner agent again via task())
    # - Skip this deliverable (phase incomplete — PM reports to COD)
    # - Abort phase execution
```

Owner agents receiving PM's `task()` invocation SHALL:
1. Create the deliverable
2. Run the submit-with-retry loop internally (invoking QUA via `task()`)
3. Return a structured result to PM containing:
   - `deliverable_path`: canonical path returned by CM
   - `qua_status`: "SUCCESS" | "ESCALATE"
   - `iterations`: number of QUA review cycles
   - `defects`: remaining defects if ESCALATE

---

## Owner Agent Behavior Checklist

Each owner agent (REQ, SAF, TST, DES, IMP) must implement:

- [ ] On PM invocation via `task()`: create deliverable, then run QUA submit-with-retry loop
- [ ] Invoke QUA via `task({subagent_type: "qua", ...})` — not via any slash command
- [ ] Apply defect auto-fix logic for common defect types
- [ ] Escalate to PM (via return value) when auto-fix is exhausted after 3 iterations
- [ ] Return structured result (deliverable path, QUA status, iteration count, remaining defects)

---

## Example: REQ Agent Workflow

```
1. PM invokes REQ via task():
   task({
     description: "Create Software Requirements Specification",
     subagent_type: "req",
     prompt: "Create the SRS for project train_door_control2 at SIL 3.
              Query CM for canonical path first.
              After creating, run QUA submit-with-retry loop (max 3 iterations).
              Return: {deliverable_path, qua_status, iterations, defects}."
   })

2. REQ internally:
   a. task({subagent_type: "cm", prompt: "query-location --doc srs"})
      → returns: phase-2-requirements/Software-Requirements-Specification.md
   b. Creates Software-Requirements-Specification.md
   c. Iteration 1: task({subagent_type: "qua", prompt: "Review phase-2-requirements/Software-Requirements-Specification.md ..."})
      → QUA FAIL (2 errors)
   d. Auto-fixes 2/2 defects
   e. Iteration 2: task({subagent_type: "qua", prompt: "Review ..."})
      → QUA PASS
   f. Returns to PM: {deliverable_path: "phase-2-requirements/Software-Requirements-Specification.md", qua_status: "SUCCESS", iterations: 2}

3. PM marks SRS as QUA-accepted
4. PM continues with next activity (SAF creates Hazard Log)
```

---

## Benefits

1. **Fast feedback loops**: Defects caught and fixed immediately
2. **Minimal user intervention**: 90%+ of defects auto-fixed
3. **Consistent quality**: All deliverables pass QUA before PM accepts
4. **Clear escalation**: User only involved when necessary
5. **Audit trail**: All QUA reviews and fixes logged

---

## Files

- QUA checkers: `.opencode/skills/en50128-quality/review-criteria/*.yaml`
- Phase definitions: `.opencode/skills/en50128-project-management/phase-definitions/*.yaml`
