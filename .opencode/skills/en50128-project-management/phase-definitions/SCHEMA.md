# Phase Definition YAML Schema

This document defines the schema for phase definition files used by PM agent orchestration.

## File Naming Convention

`phase-{number}-{name}.yaml`

Examples:
- `phase-2-requirements.yaml`
- `phase-3-architecture-design.yaml`
- `phase-4-implementation.yaml`

## YAML Schema

```yaml
phase:
  # Phase identification
  id: string                      # Unique phase ID (e.g., "requirements", "design")
  number: integer                 # Phase number (0-8)
  name: string                    # Human-readable name
  
  # Agent activities (sequential execution)
  activities:
    - agent: string               # Agent role (req, saf, tst, des, imp, etc.)
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
  
  # Verification and validation requirements
  verification:
    required: boolean             # Independent verification required?
    verifier: string              # Verifier agent (usually "ver")
    criteria: []                  # List of verification criteria
  
  validation:
    required_sil: []              # List of SIL levels requiring validation (e.g., [3, 4])
    validator: string             # Validator agent (usually "val")
    criteria: []                  # List of validation criteria
  
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

## Verification and Validation Flow

After PM reports phase complete:
1. COD invokes VER agent (if `verification.required: true`)
2. COD invokes VAL agent (if SIL level in `validation.required_sil`)
3. COD performs gate check using `completion_criteria`
4. If VER/VAL FAIL: COD instructs PM to resolve defects and re-execute
5. If VER/VAL PASS: COD authorizes transition to next phase

## File Location

Phase definition files are stored in:
```
.opencode/skills/en50128-project-management/phase-definitions/
```

Phase definitions are loaded by PM agent when executing `/pm execute-phase <phase-id>`.
