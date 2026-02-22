# Owner Agent - Defect Resolution Workflow

This document defines the standard workflow for all owner agents (REQ, SAF, TST, DES, IMP) to handle QUA defect resolution.

---

## Overview

When an owner agent creates a deliverable (e.g., REQ creates SRS), the deliverable must pass through QUA review before PM accepts it. If QUA finds defects, the owner must fix them and resubmit (max 3 iterations).

**Approval Flow**: Owner → QUA → [Fix Loop] → PM

---

## Standard Commands for Owner Agents

Each owner agent (REQ, SAF, TST, DES, IMP) implements these commands:

### 1. `/[agent] submit-to-qua <doc-path> [--doc-type <type>]`

**Description**: Submit deliverable to QUA for quality review

**Parameters**:
- `<doc-path>`: Path to document (e.g., `docs/SRS.md`)
- `--doc-type <type>`: Optional document type (auto-detected if not provided)

**Workflow**:
```
1. Verify document exists and is complete
2. Invoke QUA: /qua review-document <doc-path> --owner [agent] --doc-type [type]
3. QUA returns: PASS/FAIL + defect list
4. If PASS:
   - Log: "✓ [Document] accepted by QUA"
   - Return: SUCCESS
5. If FAIL:
   - Log: "✗ [Document] rejected by QUA ([N] errors)"
   - Return: FAIL + defect list
```

**Example**:
```bash
# REQ submits SRS to QUA
/req submit-to-qua docs/SRS.md --doc-type SRS
```

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

Status: DEFECTS MUST BE FIXED
Next: Use /req fix-defects docs/SRS.md
```

---

### 2. `/[agent] fix-defects <doc-path> --defects <defect-list-json>`

**Description**: Automatically fix defects reported by QUA

**Parameters**:
- `<doc-path>`: Path to document
- `--defects <json>`: JSON array of defects (from QUA report)

**Workflow**:
```
1. Load document
2. For each defect in defect list:
   a. Parse defect (check_id, location, issue, fix_suggestion)
   b. Apply automated fix based on defect type:
      - Document ID format: Update to correct format
      - Missing field: Add field with appropriate value
      - Incorrect format: Correct format
      - Missing section: Add section
   c. Log fix applied
3. Save updated document
4. Return: SUCCESS
```

**Automated Fix Strategies by Defect Type**:

| Defect Type | Automated Fix Strategy |
|-------------|------------------------|
| **Document ID format** | Extract components, reformat to DOC-XXX-YYYY-NNN |
| **Missing SIL level** | Infer from context or default to project SIL |
| **Missing keywords** | Add appropriate keyword based on requirement type |
| **Missing verification method** | Default to "Test" for functional, "Review" for non-functional |
| **Missing section** | Add section with template structure |
| **Missing table** | Add table with required columns |
| **Incorrect format** | Reformat to match pattern |

**Example**:
```bash
/req fix-defects docs/SRS.md --defects '[
  {
    "check_id": "SRS-T001",
    "severity": "error",
    "location": "Document Control",
    "issue": "Document ID format incorrect",
    "fix": "Update to DOC-SRS-2026-001"
  }
]'
```

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
Next: Use /req submit-to-qua docs/SRS.md
```

---

### 3. `/[agent] submit-with-retry <doc-path> [--max-iterations 3]`

**Description**: Submit to QUA with automatic defect fixing and retry (used by PM orchestration)

**Parameters**:
- `<doc-path>`: Path to document
- `--max-iterations <N>`: Maximum retry attempts (default: 3)

**Workflow**:
```
iteration = 1
while iteration <= max_iterations:
  1. Submit to QUA: /[agent] submit-to-qua <doc-path>
  2. If QUA PASS:
     - Log: "✓ [Document] accepted by QUA after [N] iteration(s)"
     - Return: SUCCESS
  3. If QUA FAIL:
     - Log: "✗ Iteration [N]/[max]: QUA rejected with [M] errors"
     - If iteration < max_iterations:
       - Fix defects: /[agent] fix-defects <doc-path> --defects [defect_list]
       - Increment iteration
       - Continue loop
     - Else:
       - Log: "⚠ Failed after [max] iterations, escalating to user"
       - Return: ESCALATE + defect list
```

**Example**:
```bash
# PM invokes with automatic retry
/req submit-with-retry docs/SRS.md --max-iterations 3
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

## Integration with PM Orchestration

When PM executes `/pm execute-phase <phase-id>`:

```python
# Pseudocode
for activity in phase.activities:
  # 1. Invoke owner to create deliverable
  owner_agent = activity.agent
  deliverables = owner_agent.create_deliverables(activity)
  
  # 2. For each deliverable
  for deliverable in deliverables:
    if deliverable.qua_required:
      # 3. Submit with automatic retry
      result = owner_agent.submit_with_retry(
        doc_path=deliverable.path,
        max_iterations=3
      )
      
      # 4. Handle result
      if result.status == "SUCCESS":
        pm.mark_deliverable_accepted(deliverable)
        if verbosity >= "normal":
          print(f"✓ {deliverable.name} accepted by QUA after {result.iterations} iteration(s)")
      
      elif result.status == "ESCALATE":
        # User intervention required
        if verbosity >= "quiet":
          print(f"⚠ {deliverable.name} requires manual intervention")
          print(f"Remaining defects: {result.defects}")
        
        user_choice = prompt_user([
          "Fix manually and retry",
          "Skip this deliverable (phase incomplete)",
          "Abort phase execution"
        ])
        
        if user_choice == "fix_and_retry":
          # Wait for user to fix, then retry
          wait_for_user_fix()
          result = owner_agent.submit_with_retry(deliverable.path, max_iterations=1)
```

---

## Owner Agent Implementation Checklist

Each owner agent (REQ, SAF, TST, DES, IMP) must implement:

- [ ] `/[agent] submit-to-qua <doc-path>` - Submit to QUA
- [ ] `/[agent] fix-defects <doc-path> --defects <json>` - Auto-fix defects
- [ ] `/[agent] submit-with-retry <doc-path>` - Submit with retry loop
- [ ] Defect auto-fix logic for common defect types
- [ ] Escalation handling for complex defects

---

## Example: REQ Agent Workflow

```bash
# 1. REQ creates SRS (invoked by PM)
/req create-srs --project train_door_control2

# 2. PM invokes submit-with-retry (automatic)
/req submit-with-retry docs/SRS.md

# Internal workflow:
#   Iteration 1: Submit → QUA FAIL (2 errors) → Auto-fix → Resubmit
#   Iteration 2: Submit → QUA PASS
#   Result: SUCCESS after 2 iterations

# 3. PM marks SRS as QUA-accepted
# 4. PM continues with next activity (SAF creates Hazard Log)
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

- Owner agent commands: `.opencode/commands/req.md`, `saf.md`, `tst.md`, `des.md`, `imp.md`
- QUA checkers: `.opencode/skills/en50128-quality/review-criteria/*.yaml`
- Phase definitions: `.opencode/skills/en50128-project-management/phase-definitions/*.yaml`
