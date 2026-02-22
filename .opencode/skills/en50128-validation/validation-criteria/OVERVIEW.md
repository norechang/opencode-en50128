# VAL Validation Criteria System

**Purpose**: Define automated validation checks for independent validation per EN 50128 Section 7.7

**Location**: `.opencode/skills/en50128-validation/validation-criteria/`

---

## Overview

The VAL (Validator) agent performs **independent validation** to ensure the software product meets user needs and is fit for its intended operational purpose.

**VAL Focus**: User needs satisfaction, operational suitability, fitness for purpose

**Distinction from VER (Verifier)**:
| Aspect | VER (Verifier) | VAL (Validator) |
|--------|----------------|-----------------|
| **Question** | "Did we build the product right?" | "Did we build the right product?" |
| **Focus** | Technical correctness, standards compliance | User needs, operational suitability, fitness for purpose |
| **Methods** | Static analysis, code review, metrics | System testing, operational scenarios, acceptance testing |
| **Reference** | Requirements, design, standards | User needs, operational environment, acceptance criteria |
| **Independence** | Independent from PM, Developer (SIL 3-4) | Independent from PM, VER, Developer (SIL 3-4) |
| **Authority** | Technical approval (can reject code) | Operational approval (can reject deployment) |
| **EN 50128** | Section 6.2 (Verification) | Section 7.7 (Validation) |

**Distinction from QUA (Quality Assurance)**:
| Aspect | QUA | VAL |
|--------|-----|-----|
| **Focus** | Document quality, process compliance | Product suitability, user acceptance |
| **Timing** | Throughout (early gate checks) | Late (final acceptance) |
| **Scope** | Templates, formatting, internal quality | Operational fitness, user satisfaction |
| **Authority** | Advisory (process enforcement) | Mandatory approval for deployment (SIL 3-4) |

---

## Validation Criteria Files

### Per-Phase Validation Criteria

Each phase has a validation criteria YAML file defining checks for VAL:

1. **`requirements-validation-criteria.yaml`** - Requirements validation (user needs correctness)
2. **`design-validation-criteria.yaml`** - Design validation (architecture suitability)
3. **`implementation-validation-criteria.yaml`** - Implementation validation (code readiness)
4. **`integration-validation-criteria.yaml`** - Integration validation (subsystem integration)
5. **`validation-validation-criteria.yaml`** - Final validation (system acceptance)

---

## Validation Criteria Schema

```yaml
phase: "validation"  # Phase name
sil_level: 3  # Target SIL level
validation_techniques:  # EN 50128 Table A.7 techniques applied
  - "Performance Testing (M for SIL 3-4)"
  - "Functional and Black-box Testing (M for SIL 3-4)"
  - "Operational Scenario Testing"

deliverables:
  - name: "Software Validation Plan (SVaP)"
    file_pattern: "docs/SVaP.md"
    owner: "VAL"
    
    validation_checks:
      - id: "VAL-PLAN-001"
        category: "validation_planning"
        severity: "critical"
        description: "Validation scope covers all user needs"
        criteria: "All identified user needs have validation test cases"
        validation_method: "Map user needs to validation tests"
        pass_criteria: "100% user needs mapped to validation tests"
        reference: "EN 50128 Section 7.7.1"
        
      - id: "VAL-PLAN-002"
        category: "acceptance_criteria"
        severity: "critical"
        description: "Acceptance criteria clearly defined"
        criteria: "Measurable acceptance criteria for all critical functions"
        validation_method: "Review acceptance criteria for measurability"
        pass_criteria: "All acceptance criteria are objective and measurable"
        reference: "EN 50128 Section 7.7.2"
        
      - id: "VAL-PLAN-003"
        category: "operational_environment"
        severity: "major"
        description: "Target environment defined or simulated"
        criteria: "Validation in target operational environment or representative simulation"
        validation_method: "Check test environment specification"
        pass_criteria: "Target hardware OR justified simulation environment defined"
        reference: "EN 50128 Section 7.7.3"
```

**Check Categories**:
- `validation_planning` - Validation plan completeness
- `acceptance_criteria` - Acceptance criteria definition
- `operational_environment` - Test environment suitability
- `user_needs` - User needs satisfaction
- `operational_scenarios` - Operational scenario coverage
- `safety_validation` - Safety function validation
- `performance_validation` - Performance and timing validation
- `usability` - User interface and usability
- `deployment_readiness` - Readiness for operational deployment

**Severity Levels**:
- `critical` - Must be fixed (blocks validation approval)
- `major` - Should be fixed (VAL discretion to approve with customer agreement)
- `minor` - Recommended fix (advisory, customer decision)

---

## VAL Validation Workflow

```
1. COD invokes: /cod verify-phase validation
   (After VER has verified technical correctness)
   
2. COD instructs VAL: "Validate requirements phase deliverables"

3. VAL loads: requirements-validation-criteria.yaml

4. For each deliverable (e.g., SRS):
   a. Load validation checks for deliverable
   b. Apply each check:
      - Read deliverable file
      - Check user needs satisfaction
      - Check operational suitability
      - Compare against pass criteria
      - Record: PASS or FAIL + issue description
   c. Aggregate results:
      - If all checks PASS: Mark deliverable as VALIDATED
      - If any CRITICAL/MAJOR fail: Mark deliverable as REJECTED + issue list

5. VAL reports to COD:
   - Validated deliverables list
   - Rejected deliverables list with issues
   - Validation conclusion (approved/rejected for operational use)

6. COD proceeds:
   - If validated: Gate check PASS, authorize phase transition
   - If rejected: Return issues to PM for resolution
```

---

## Validation Focus by Phase

### Requirements Phase Validation
**Question**: "Do the requirements capture the right user needs?"
- User needs completeness (all user needs addressed)
- Operational scenario coverage (realistic scenarios defined)
- Safety requirements adequacy (hazards mitigated)
- Usability requirements (user interface specified)

### Design Phase Validation
**Question**: "Will this design meet operational needs?"
- Architecture suitability for operational environment
- Performance feasibility (can meet timing requirements)
- Safety architecture adequacy (fault tolerance, redundancy)
- Maintainability and extensibility

### Implementation Phase Validation
**Question**: "Is the code ready for integration and testing?"
- Code completeness (all design elements implemented)
- Unit test quality (tests represent real usage)
- Error handling readiness (operational error scenarios)

### Integration Phase Validation
**Question**: "Does the integrated system work as intended?"
- Interface correctness in operational context
- End-to-end scenario testing
- Performance under realistic load
- Fault injection and recovery

### Validation Phase (Final)
**Question**: "Is the software fit for deployment?"
- System-level operational testing
- Acceptance criteria met
- Customer approval obtained
- Deployment readiness confirmed

---

## Automated vs Manual Validation Checks

**Automated Checks** (objective, measurable):
- Test coverage of user needs (mapping check)
- Acceptance criteria presence (document structure)
- Test pass rate (100% pass required)
- Performance measurements vs requirements (timing, throughput)
- Traceability completeness (user needs → requirements → tests)

**Manual Review Simulation** (AI-assisted, subjective):
- User needs completeness (are all user needs captured?)
- Operational suitability (will this work in real environment?)
- Usability assessment (is the interface intuitive?)
- Safety adequacy (are hazards properly mitigated?)
- Deployment readiness (is documentation sufficient for operators?)

**VAL Agent Approach**:
1. Run automated checks first (objective, fast)
2. For manual checks: Apply AI analysis with operational perspective
3. Simulate user/operator perspective (not developer perspective)
4. If uncertain: Mark as ISSUE with recommendation
5. Generate validation report with deployment recommendations

---

## Example Validation Check Application

**Check**: VAL-PLAN-001 (User needs coverage)

**Deliverable**: docs/SRS.md, docs/SVaP.md

**Automated Validation**:
```python
# Pseudo-code for automated check
def validate_user_needs_coverage(user_needs_doc, srs_doc, svap_doc):
    user_needs = parse_user_needs(user_needs_doc)
    requirements = parse_requirements(srs_doc)
    validation_tests = parse_validation_tests(svap_doc)
    
    issues = []
    
    for need in user_needs:
        # Check requirement coverage
        reqs = find_requirements_for_need(need, requirements)
        if not reqs:
            issues.append({
                'id': need.id,
                'severity': 'critical',
                'description': f'{need.id}: No requirements address this user need',
                'fix': 'Add requirements to address user need',
                'reference': 'EN 50128 Section 7.7.1'
            })
        
        # Check validation test coverage
        tests = find_tests_for_need(need, validation_tests)
        if not tests:
            issues.append({
                'id': need.id,
                'severity': 'critical',
                'description': f'{need.id}: No validation tests for this user need',
                'fix': 'Add validation test cases for user need',
                'reference': 'EN 50128 Section 7.7.2'
            })
    
    return issues
```

**VAL Result**:
- If no issues: ✓ VALIDATED
- If issues found: ✗ REJECTED + issue list

---

## Issue Report Format

When VAL rejects a deliverable:

```yaml
deliverable: "Software Requirements Specification (SRS)"
file: "docs/SRS.md"
status: "rejected"
validation_issues:
  - id: "VAL-PLAN-001-001"
    check: "VAL-PLAN-001"
    severity: "critical"
    user_need_id: "UN-005"
    description: "User need 'Emergency stop button' not addressed in requirements"
    location: "User needs: docs/UserNeeds.md:line 42"
    fix_suggestion: "Add safety requirement for emergency stop button with response time <100ms"
    customer_impact: "Critical safety function missing - cannot deploy without this"
    reference: "EN 50128 Section 7.7.1"
    
  - id: "VAL-PLAN-002-001"
    check: "VAL-PLAN-002"
    severity: "major"
    requirement_id: "REQ-042"
    description: "Acceptance criteria too vague: 'system shall be fast'"
    location: "docs/SRS.md:line 312"
    fix_suggestion: "Replace with measurable criteria: 'Door response time ≤500ms from button press'"
    customer_impact: "Cannot objectively determine if requirement is met"
    reference: "EN 50128 Section 7.7.2"
```

---

## EN 50128 Compliance

**Table A.7 (Overall Software Testing/Validation)** - Mandatory techniques for SIL 3-4:
- Technique 1: Performance Testing (**M** for SIL 3-4)
- Technique 2: Functional and Black-box Testing (**M** for SIL 3-4)

**VAL Validation Criteria** implements:
1. **Performance Testing** (Table A.18):
   - Timing validation (response times, WCET)
   - Throughput validation (data rates, transaction rates)
   - Resource validation (CPU, memory, I/O utilization)
   - Real-time constraint validation

2. **Functional and Black-box Testing** (Table A.14):
   - Requirements-based testing (black-box approach)
   - Operational scenario testing
   - Boundary value analysis
   - Equivalence partitioning

3. **Operational and Usage Procedures Testing**:
   - User operational scenarios
   - Normal operation validation
   - Degraded mode operation
   - Emergency procedures

---

## Validation Criteria Summary

| File | Phase | Checks | Deliverables | Status |
|------|-------|--------|--------------|--------|
| `requirements-validation-criteria.yaml` | Requirements | TBD | SRS, User Needs, SVaP | ⏳ Pending |
| `design-validation-criteria.yaml` | Architecture & Design | TBD | SAS, SDS, SVaP | ⏳ Pending |
| `implementation-validation-criteria.yaml` | Implementation | TBD | Source Code, Unit Tests | ⏳ Pending |
| `integration-validation-criteria.yaml` | Integration | TBD | Integration Tests, SVaP | ⏳ Pending |
| `validation-validation-criteria.yaml` | Validation (Final) | TBD | Validation Tests, Validation Report | ⏳ Pending |

---

## Files in This Directory

- **`OVERVIEW.md`** (this file) - System overview
- **`requirements-validation-criteria.yaml`** - Requirements validation checks (PENDING)
- **`design-validation-criteria.yaml`** - Design validation checks (PENDING)
- **`implementation-validation-criteria.yaml`** - Implementation validation checks (PENDING)
- **`integration-validation-criteria.yaml`** - Integration validation checks (PENDING)
- **`validation-validation-criteria.yaml`** - Final validation checks (PENDING)

---

## Usage by VAL Agent

When VAL agent is invoked by COD:

```bash
# COD orchestrates validation
/cod verify-phase requirements

# After VER completes verification, COD invokes VAL:
# 1. Load .opencode/skills/en50128-validation/validation-criteria/requirements-validation-criteria.yaml
# 2. For each deliverable in criteria:
#    a. Apply validation checks
#    b. Generate issue report if failures
# 3. Return result to COD (validated or rejected)
```

VAL agent workflow:
1. Load validation criteria for phase
2. For each deliverable:
   - Apply automated checks (coverage, traceability, metrics)
   - Apply manual review simulation (user needs, operational suitability)
   - Assess from user/operator perspective (NOT developer perspective)
   - Aggregate results
3. Mark deliverable as VALIDATED or REJECTED
4. Report to COD with deployment recommendation

---

## Independence Requirements (SIL 3-4)

**EN 50128 Section 5.3.7 - Validator Role**:
- Validator SHALL be independent from Project Manager
- Validator SHALL be independent from Developer, Designer, Implementer
- Validator SHALL be independent from Verifier
- Validator SHALL NOT report to Project Manager (reports to COD or Safety Authority)

**Organizational Independence**:
```
Safety Authority / Customer
        |
        ├─── Validator (VAL) - Independent, reports to Safety Authority
        |
        └─── Lifecycle Coordinator (COD)
                 |
                 ├─── Verifier (VER) - Independent from PM, reports to COD
                 |
                 └─── Project Manager (PM)
                          |
                          └─── Development Team (REQ, DES, IMP, TST, INT)
```

---

## Next Steps

1. ⏳ Create requirements-validation-criteria.yaml
2. ⏳ Create design-validation-criteria.yaml
3. ⏳ Create implementation-validation-criteria.yaml
4. ⏳ Create integration-validation-criteria.yaml
5. ⏳ Create validation-validation-criteria.yaml
6. ⏳ Enhance VAL agent with automated validation workflow
7. ⏳ Test with train_door_control2 project
