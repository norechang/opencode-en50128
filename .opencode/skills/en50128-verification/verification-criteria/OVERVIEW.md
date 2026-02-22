# VER Verification Criteria System

**Purpose**: Define automated verification checks for independent technical verification per EN 50128 Section 6.2

**Location**: `.opencode/skills/en50128-verification/verification-criteria/`

---

## Overview

The VER (Verifier) agent performs **independent technical verification** to ensure deliverables meet technical correctness, standards compliance, and engineering quality.

**VER Focus**: Technical correctness (NOT formatting/templates - QUA handles that)

**Distinction from QUA**:
| Aspect | QUA (Quality Assurance) | VER (Verifier) |
|--------|------------------------|----------------|
| **Focus** | Template compliance, formatting, basic quality | Technical correctness, standards, traceability |
| **Timing** | Early (before PM aggregates) | Late (after PM reports complete) |
| **Independence** | Internal quality function | Independent role (SIL 3-4) |
| **Scope** | Document structure, IDs, keywords | Content accuracy, engineering quality |
| **Authority** | Advisory (PM can override with justification) | Mandatory (PM cannot override for SIL 3-4) |

---

## Verification Criteria Files

### Per-Phase Verification Criteria

Each phase has a verification criteria YAML file defining checks for VER:

1. **`requirements-verification-criteria.yaml`** - Requirements phase (SRS, RTM, Hazard Log, Test Spec)
2. **`design-verification-criteria.yaml`** - Design phase (SAS, SDS, Interface Specs)
3. **`implementation-verification-criteria.yaml`** - Implementation phase (Source Code, Unit Tests)
4. **`integration-verification-criteria.yaml`** - Integration phase (Integration Tests)
5. **`validation-verification-criteria.yaml`** - Validation phase (System Tests, Validation Report)

---

## Verification Criteria Schema

```yaml
phase: "requirements"  # Phase name
sil_level: 3  # Target SIL level
verification_techniques:  # EN 50128 Table A.5 techniques applied
  - "Traceability (M)"
  - "Static Analysis (M)"
  - "Metrics (HR)"

deliverables:
  - name: "Software Requirements Specification (SRS)"
    file_pattern: "docs/SRS.md"
    owner: "REQ"
    
    verification_checks:
      - id: "VER-SRS-001"
        category: "requirements_quality"
        severity: "major"
        description: "All requirements unambiguous"
        criteria: "No undefined terms, no ambiguous language (shall vs should vs may)"
        verification_method: "Manual review + automated keyword check"
        pass_criteria: "All requirements use SHALL/SHOULD/MAY correctly per RFC 2119"
        reference: "EN 50128 Section 7.2.2.1"
        
      - id: "VER-SRS-002"
        category: "requirements_quality"
        severity: "major"
        description: "All requirements testable"
        criteria: "Each requirement has acceptance criteria or test case mapping"
        verification_method: "Check RTM for requirement-to-test mapping"
        pass_criteria: "100% requirements mapped to test cases in RTM"
        reference: "EN 50128 Section 7.2.2.3"
        
      - id: "VER-SRS-003"
        category: "sil_assignment"
        severity: "critical"
        description: "SIL levels assigned to all requirements"
        criteria: "Every requirement has SIL level (0-4) based on hazard analysis"
        verification_method: "Check each requirement for SIL field"
        pass_criteria: "100% requirements have SIL level assignment"
        reference: "EN 50128 Section 4.2-4.3, Section 7.2.4"
        
      - id: "VER-SRS-004"
        category: "c_constraints"
        severity: "major"
        description: "C language constraints considered"
        criteria: "Requirements specify fixed-width types, static allocation, bounded execution"
        verification_method: "Check for C-specific implementation constraints"
        pass_criteria: "Data types use stdint.h, memory allocation specified as static"
        reference: "MISRA C:2012 Directive 4.6"
        
      - id: "VER-SRS-005"
        category: "traceability"
        severity: "critical"
        description: "Traceability complete (System → Software requirements)"
        criteria: "All system requirements traced to software requirements in RTM"
        verification_method: "Check RTM for forward/backward traceability"
        pass_criteria: "100% forward trace, 100% backward trace, no orphans"
        reference: "EN 50128 Section 7.2.5, Table A.5 Technique 7 (M for SIL 3-4)"
```

**Check Categories**:
- `requirements_quality` - Requirement statement quality (unambiguous, testable)
- `sil_assignment` - SIL level assignments
- `c_constraints` - C language implementation constraints
- `traceability` - Requirements traceability
- `safety` - Safety requirements
- `standards_compliance` - EN 50128 technique application
- `design_quality` - Architecture/design quality (complexity, modularity)
- `code_quality` - Source code quality (MISRA C, static analysis)
- `test_coverage` - Test coverage requirements

**Severity Levels**:
- `critical` - Must be fixed (blocks verification)
- `major` - Should be fixed (VER discretion to pass with justification)
- `minor` - Recommended fix (advisory)

---

## VER Verification Workflow

```
1. COD invokes: /cod verify-phase requirements
2. COD loads: requirements-verification-criteria.yaml
3. For each deliverable (e.g., SRS):
   a. Load verification checks for deliverable
   b. Apply each check:
      - Read deliverable file
      - Apply verification method (manual review simulation, automated check)
      - Compare against pass criteria
      - Record: PASS or FAIL + defect description
   c. Aggregate results:
      - If all checks PASS: Mark deliverable as VERIFIED
      - If any CRITICAL/MAJOR fail: Mark deliverable as REJECTED + defect list
4. VER reports to COD:
   - Verified deliverables list
   - Rejected deliverables list with defects
5. COD proceeds:
   - If all verified: Invoke VAL
   - If any rejected: Return defects to PM
```

---

## Automated vs Manual Checks

**Automated Checks** (fast, deterministic):
- Keyword presence (SHALL/SHOULD/MAY)
- SIL level field presence
- Requirement ID format
- Traceability matrix completeness (count matches)
- C type usage (stdint.h types vs native types)

**Manual Review Simulation** (AI-assisted analysis):
- Requirement ambiguity detection (natural language analysis)
- Testability assessment (can this be verified?)
- Technical correctness (does this make engineering sense?)
- Safety adequacy (are safety concerns addressed?)
- Design quality (is complexity within limits?)

**VER Agent Approach**:
1. Run automated checks first (fast, objective)
2. For manual checks: Apply AI analysis with conservative threshold
3. If uncertain: Mark as DEFECT with recommendation (safe approach)
4. Generate comprehensive defect report with fix suggestions

---

## Example Verification Check Application

**Check**: VER-SRS-003 (SIL levels assigned)

**Deliverable**: docs/SRS.md

**Automated Verification**:
```python
# Pseudo-code for automated check
def verify_sil_assignments(srs_file):
    requirements = parse_requirements(srs_file)
    defects = []
    
    for req in requirements:
        if not req.has_field('SIL'):
            defects.append({
                'id': req.id,
                'severity': 'critical',
                'description': f'{req.id}: SIL level missing',
                'fix': 'Assign SIL level (0-4) per hazard analysis',
                'reference': 'EN 50128 Section 7.2.4'
            })
    
    return defects
```

**VER Result**:
- If no defects: ✓ VERIFIED
- If defects found: ✗ REJECTED + defect list

---

## Defect Report Format

When VER rejects a deliverable:

```yaml
deliverable: "Software Requirements Specification (SRS)"
file: "docs/SRS.md"
status: "rejected"
defects:
  - id: "VER-SRS-003-001"
    check: "VER-SRS-003"
    severity: "critical"
    requirement_id: "REQ-015"
    description: "SIL level missing"
    location: "docs/SRS.md:line 142"
    fix_suggestion: "Assign SIL level (0-4) based on hazard analysis. Reference Hazard-Log.md hazard mapping."
    reference: "EN 50128 Section 7.2.4"
    
  - id: "VER-SRS-004-001"
    check: "VER-SRS-004"
    severity: "major"
    requirement_id: "REQ-023"
    description: "C constraint violation: uses 'long' instead of fixed-width type"
    location: "docs/SRS.md:line 234"
    fix_suggestion: "Replace 'long' with 'int32_t' or 'int64_t' from <stdint.h>"
    reference: "MISRA C:2012 Directive 4.6"
```

---

## EN 50128 Compliance

**Table A.5 (Verification and Testing)** - Mandatory techniques for SIL 3-4:
- Technique 3: Static Analysis (**M**)
- Technique 7: Traceability (**M**)

**VER Verification Criteria** implements:
1. **Static Analysis** (Table A.19):
   - Control flow analysis (automated check for design/code)
   - Data flow analysis (automated check for design/code)
   - Code review (manual review simulation)
   - Complexity metrics (automated check)

2. **Traceability** (Technique 7):
   - Requirements traceability verification (RTM checks)
   - Forward/backward trace completeness
   - Orphan requirement/design/code detection

3. **Metrics** (Technique 5 - HR for SIL 3-4):
   - Cyclomatic complexity (≤10 for SIL 3-4)
   - Test coverage (100% branch/condition for SIL 3-4)
   - MISRA C compliance (zero mandatory violations for SIL 2+)

---

## Files in This Directory

- **`OVERVIEW.md`** (this file) - System overview
- **`requirements-verification-criteria.yaml`** - Requirements phase VER checks
- **`design-verification-criteria.yaml`** - Design phase VER checks
- **`implementation-verification-criteria.yaml`** - Implementation phase VER checks
- **`integration-verification-criteria.yaml`** - Integration phase VER checks
- **`validation-verification-criteria.yaml`** - Validation phase VER checks

---

## Usage by VER Agent

When VER agent is invoked by COD:

```bash
# COD orchestrates verification
/cod verify-phase requirements

# Internally, COD invokes VER:
# 1. Load .opencode/skills/en50128-verification/verification-criteria/requirements-verification-criteria.yaml
# 2. For each deliverable in criteria:
#    a. Apply verification checks
#    b. Generate defect report if failures
# 3. Return result to COD (verified or rejected)
```

VER agent workflow:
1. Load verification criteria for phase
2. For each deliverable:
   - Apply automated checks (keyword, format, traceability)
   - Apply manual review simulation (AI analysis)
   - Aggregate results
3. Mark deliverable as VERIFIED or REJECTED
4. Report to COD

---

## Verification Criteria Summary

| File | Phase | Checks | Deliverables | Status |
|------|-------|--------|--------------|--------|
| `requirements-verification-criteria.yaml` | Requirements | 16 | SRS, RTM, Hazard Log, Test Spec | ✅ Complete |
| `design-verification-criteria.yaml` | Architecture & Design | 20 | SAS, SDS, Interface Specs, RTM | ✅ Complete |
| `implementation-verification-criteria.yaml` | Implementation | 21 | Source Code, Unit Tests, MISRA Report, Static Analysis | ✅ Complete |
| `integration-verification-criteria.yaml` | Integration | 18 | Integration Tests, Interface Tests, Performance Tests | ✅ Complete |
| `validation-verification-criteria.yaml` | Validation | 20 | SVaP, Validation Tests, Acceptance Tests, Validation Report | ✅ Complete |

**Total**: 95 verification checks across 5 phases

---

## Next Steps

1. ✅ Create requirements-verification-criteria.yaml (COMPLETE - 16 checks)
2. ✅ Create design-verification-criteria.yaml (COMPLETE - 20 checks)
3. ✅ Create implementation-verification-criteria.yaml (COMPLETE - 21 checks)
4. ✅ Create integration-verification-criteria.yaml (COMPLETE - 18 checks)
5. ✅ Create validation-verification-criteria.yaml (COMPLETE - 20 checks)
6. ⏳ Create VAL validation criteria system (PENDING)
7. ⏳ Enhance VER agent with automated verification workflow (PENDING)
8. ⏳ Enhance VAL agent with automated validation workflow (PENDING)
9. ⏳ Test with train_door_control2 project (PENDING)
