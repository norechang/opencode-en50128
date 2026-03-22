# Phase Definition YAML Schema

This document defines the schema for phase definition files used by PM agent orchestration.

## File Naming Convention

`phase-{number}-{name}.yaml`

Examples:
- `phase-2-requirements.yaml`
- `phase-3-architecture-design.yaml`
- `phase-4-implementation.yaml`

## Two-Track Execution Model

Phase execution is strictly divided into two independent tracks per WORKFLOW.md:

```
TRACK A — Development (PM-orchestrated)
  USER → PM → dev agents (REQ · DES · IMP · INT · TST · SAF · CM)
             → QUA template checks of dev deliverables
             → PM reports Track A complete to COD

TRACK B — Independent V&V (COD-orchestrated, begins after Track A)
  COD → VMGR → VER → QUA (VER report review) → VMGR
  COD → VAL  → QUA (VAL report review) → VMGR → COD gate-check
```

**Key constraint**: PM has NO authority over VER, VAL, or VMGR.  
VER and VAL MUST NOT appear in the `activities` list — they belong exclusively in the
`verification:` and `validation:` sections, which COD reads to orchestrate Track B.

The `activities:` list contains **only** Track A agents:
- Development agents: `req`, `saf`, `des`, `imp`, `int`, `tst`, `cm`
- QUA template reviews of **development deliverables** (not VER/VAL reports)

## YAML Schema

```yaml
phase:
  # Phase identification
  id: string                      # Unique phase ID (e.g., "requirements", "design")
  number: integer                 # Phase number (0-8)
  name: string                    # Human-readable name
  
  # TRACK A: Agent activities (PM-orchestrated development activities ONLY)
  # VER, VAL, and VMGR MUST NOT appear here — they are Track B (COD-orchestrated).
  # Track B is driven by the `verification:` and `validation:` sections below.
  activities:
    - agent: string               # Agent role — dev agents only: req, saf, tst, des, imp, int, cm, qua
                                  # qua is allowed ONLY for template reviews of dev deliverables
                                  # NEVER use: ver, val, vmgr (those are Track B)
      task_description: string    # What the agent should do
      owner: string               # Document owner agent (same as agent usually)
      deliverables:               # List of deliverables this activity produces
        - path: string            # Relative path to deliverable (from project root)
          doc_id: string          # Document ID (e.g., "DOC-SRS-2026-001")
          doc_type: string        # Document type (SRS, Hazard-Log, Test-Spec, etc.)
          qua_required: boolean   # QUA review required before PM accepts? (default: true)
      dependencies: []            # List of activity indices that must complete first (optional)
      parallel_group: integer     # Activities with same group number can run in parallel (optional)
  
  # Phase completion criteria (checked by COD during gate check)
  completion_criteria:
    all_deliverables_qua_accepted: boolean    # All deliverables passed QUA review?
    traceability_complete: boolean            # RTM complete and up-to-date?
    coverage_requirements:                    # Coverage thresholds
      requirements: integer                   # % requirements coverage
      code_statement: integer                 # % statement coverage (if applicable)
      code_branch: integer                    # % branch coverage (if applicable)
    custom_checks: []                         # List of custom checks (optional)
  
  # TRACK B: Verification requirements (COD-orchestrated — NOT part of activities list)
  # COD reads this section to orchestrate VER via VMGR after Track A completes.
  verification:
    required: boolean             # Independent verification required?
    verifier: string              # Verifier agent (always "ver")
    criteria: []                  # List of verification criteria VER must check
  
  # TRACK B: Validation requirements (COD-orchestrated — NOT part of activities list)
  # COD reads this section to orchestrate VAL via VMGR after VER completes.
  validation:
    required_sil: []              # List of SIL levels requiring validation (e.g., [3, 4])
    validator: string             # Validator agent (always "val")
    criteria: []                  # List of validation criteria VAL must satisfy
  
  # Gate check configuration
  gate_check:
    mandatory_sil: []             # SIL levels requiring mandatory gate check (default: all)
    blocking_sil: []              # SIL levels where gate check blocks transition (default: [3, 4])
```

## Example: Phase 2 (Requirements)

```yaml
phase:
  id: "requirements"
  number: 2
  name: "Requirements Specification"
  
  activities:
    - agent: "req"
      task_description: "Create Software Requirements Specification (SRS) and Requirements Traceability Matrix (RTM)"
      owner: "req"
      deliverables:
        - path: "docs/SRS.md"
          doc_id: "DOC-SRS-2026-001"
          doc_type: "SRS"
          qua_required: true
        - path: "docs/RTM.md"
          doc_id: "DOC-RTM-2026-001"
          doc_type: "RTM"
          qua_required: true
      parallel_group: 1
    
    - agent: "saf"
      task_description: "Create Hazard Log with FMEA, FTA, and Common Cause Failure analysis"
      owner: "saf"
      deliverables:
        - path: "docs/Hazard-Log.md"
          doc_id: "DOC-HAZLOG-2026-001"
          doc_type: "Hazard-Log"
          qua_required: true
      parallel_group: 1
    
    - agent: "tst"
      task_description: "Create Overall Software Test Specification"
      owner: "tst"
      deliverables:
        - path: "docs/test/Overall-Test-Spec.md"
          doc_id: "DOC-TESTSPEC-2026-001"
          doc_type: "Test-Spec"
          qua_required: true
      dependencies: [0, 1]        # Depends on SRS and Hazard Log
  
  completion_criteria:
    all_deliverables_qua_accepted: true
    traceability_complete: true
    coverage_requirements:
      requirements: 100           # 100% system requirements traced to software requirements
  
  verification:
    required: true
    verifier: "ver"
    criteria:
      - "All requirements have unique IDs"
      - "All requirements have SIL levels"
      - "All requirements use SHALL/SHOULD/MAY keywords"
      - "RTM shows 100% traceability"
      - "All hazards have safety requirements"
  
  validation:
    required_sil: [3, 4]
    validator: "val"
    criteria:
      - "Requirements are testable"
      - "Requirements are unambiguous"
      - "Test specification covers all requirements"
  
  gate_check:
    mandatory_sil: [0, 1, 2, 3, 4]
    blocking_sil: [3, 4]
```

## Parallel Execution

Activities with the same `parallel_group` number can execute in parallel:

```yaml
activities:
  - agent: "req"
    parallel_group: 1    # Can run in parallel with SAF
  - agent: "saf"
    parallel_group: 1    # Can run in parallel with REQ
  - agent: "tst"
    parallel_group: 2    # Runs after group 1 completes
```

## Dependencies

Activities can specify dependencies by activity index (0-based):

```yaml
activities:
  - agent: "req"         # Index 0
  - agent: "saf"         # Index 1
  - agent: "tst"         # Index 2
    dependencies: [0, 1] # TST depends on REQ and SAF
```

## QUA Review Integration

When `qua_required: true`, the PM agent will:
1. Wait for owner agent to complete deliverable
2. Invoke QUA review for the deliverable
3. If QUA FAIL: Invoke owner agent to fix defects (max 3 iterations)
4. If QUA PASS: Mark deliverable as accepted
5. Once all activities complete and all deliverables QUA-accepted, report to COD

## Verification and Validation Flow (Two-Track Model)

Track A (PM-orchestrated) completes first, then Track B (COD-orchestrated) begins:

```
TRACK A:  PM → dev agents → QUA template checks → PM reports to COD
TRACK B:  COD → VMGR → VER → VMGR → COD → VAL → VMGR → COD gate-check
```

1. PM executes all `activities` (Track A dev agents + QUA template checks)
2. PM reports Track A complete to COD
3. COD hands off to VMGR, who manages VER (if `verification.required: true`)
4. QUA reviews VER report; VMGR approves
5. COD invokes VAL (if SIL level in `validation.required_sil`)
6. QUA reviews VAL report; VMGR approves
7. COD performs gate check using `completion_criteria`
8. If Track B FAIL: COD instructs PM to resolve defects (re-enters Track A)
9. If Track B PASS: COD authorizes transition to next phase

**PM has NO authority over VER, VAL, or VMGR** (WORKFLOW.md Key Independence Constraints).

## File Location

Phase definition files are stored in:
```
.opencode/skills/en50128-project-management/phase-definitions/
```

Phase definitions are loaded by PM agent when the user invokes `@pm execute-phase <phase-id>`.
