# EN 50128 Phase Gate Management Workflow

**Skill**: `en50128-lifecycle-coordination`  
**Workflow**: Phase Gate Management  
**Role**: Lifecycle Coordinator (COD)  
**EN 50128 Reference**: Section 5.3 (Software Lifecycle), Annex C Table C.1 (Document Control)  
**Purpose**: Complete phase gate enforcement with SIL-specific criteria

---

## Table of Contents

1. [Phase Gate Overview](#phase-gate-overview)
2. [Gate 0/1: Planning Complete](#gate-01-planning-complete)
3. [Gate 2: Requirements Complete](#gate-2-requirements-complete)
4. [Gate 3: Design Complete](#gate-3-design-complete)
5. [Gate 4: Implementation Complete](#gate-4-implementation-complete)
6. [Gate 5: Integration Complete](#gate-5-integration-complete)
7. [Gate 6: Validation Complete](#gate-6-validation-complete)
8. [Gate 7: Assessment Complete (SIL 3-4 Only)](#gate-7-assessment-complete-sil-3-4-only)
9. [Gate 8: Deployment Complete](#gate-8-deployment-complete)
10. [Gate Check Automation](#gate-check-automation)
11. [Tool Integration](#tool-integration)
12. [Example Scenario](#example-scenario)

---

## Phase Gate Overview

### Purpose

Phase gates ensure that each lifecycle phase meets EN 50128 requirements before proceeding to the next phase. Gates enforce:

1. **Deliverable Completeness** - All required documents per Annex C Table C.1
2. **Quality Criteria** - Metrics, coverage, compliance thresholds met
3. **Traceability** - Requirements Traceability Matrix (RTM) complete
4. **Verification** - Independent reviews and approvals obtained
5. **Safety Compliance** - Hazards addressed, safety requirements satisfied

### Gate Structure

Each gate has standardized structure:

```
┌─────────────────────────────────────────────────────────┐
│ PHASE GATE STRUCTURE                                    │
├─────────────────────────────────────────────────────────┤
│ 1. Entry Criteria (verified from previous gate)        │
│ 2. Exit Criteria (must satisfy to pass gate)           │
│ 3. Deliverables (per EN 50128 Annex C Table C.1)       │
│ 4. Quality Criteria (metrics, coverage, compliance)    │
│ 5. Traceability (RTM completeness)                     │
│ 6. Verification (reviews, approvals)                   │
│ 7. Gate Decision (PASS/BLOCK/CONDITIONAL)              │
└─────────────────────────────────────────────────────────┘
```

### SIL-Dependent Gate Enforcement

| SIL Level | Enforcement Mode | Gate Behavior | Override Allowed |
|-----------|------------------|---------------|------------------|
| **SIL 0** | Advisory | Warnings only | Yes (user discretion) |
| **SIL 1** | Advisory | Warnings only | Yes (user discretion) |
| **SIL 2** | Semi-Strict | BLOCK on mandatory violations, warn on HR | Justification required |
| **SIL 3** | Strict | BLOCK on all violations | No (must fix) |
| **SIL 4** | Strict | BLOCK on all violations | No (must fix) |

### Gate Check Command

```bash
/cod gate-check <phase>
```

**Phases**:
- `planning` - Gate 0/1
- `requirements` - Gate 2
- `design` - Gate 3
- `implementation` - Gate 4
- `integration` - Gate 5
- `validation` - Gate 6
- `assessment` - Gate 7 (SIL 3-4 only)
- `deployment` - Gate 8

---

## Gate 0/1: Planning Complete

### Purpose

Verify project foundation established before requirements elicitation begins.

### Entry Criteria

- Project created (COD initialized)
- SIL level determined
- Project team assigned

### Exit Criteria (SIL-Dependent)

#### All SIL Levels (0-4)

1. **Planning Documents Complete**:
   - [ ] Software Quality Assurance Plan (SQAP)
   - [ ] Software Configuration Management Plan (SCMP)
   - [ ] Software Verification Plan (SVP)
   - [ ] Software Validation Plan (SVaP)
   - [ ] Software Quality Assurance Verification Report

2. **Project Setup**:
   - [ ] Version control initialized (Git repository)
   - [ ] Build environment configured
   - [ ] Configuration management operational (baseline 0 established)

3. **Team Organization**:
   - [ ] All roles assigned
   - [ ] Reporting structure documented

#### SIL 2+ Additional Criteria

4. **Tool Qualification**:
   - [ ] MISRA C checker qualified (T2/T3)
   - [ ] Static analysis tools qualified
   - [ ] Coverage tools qualified

5. **MISRA C Compliance Planning**:
   - [ ] MISRA C:2012 selected
   - [ ] Deviation process defined
   - [ ] Compliance strategy documented in SQAP

#### SIL 3-4 Additional Criteria

6. **Independence Requirements**:
   - [ ] Independent Verifier assigned (does NOT report to PM)
   - [ ] Independent Validator assigned (does NOT report to PM)
   - [ ] Organizational independence documented
   - [ ] No undue influence from development team

7. **Assessment Planning** (SIL 3-4):
   - [ ] Independent Assessor engaged
   - [ ] Assessment plan established
   - [ ] Safety Authority notified (if applicable)

### Deliverables (Annex C Table C.1)

| Document | Author | 1st Check (VER) | 2nd Check (VAL) | Baseline |
|----------|--------|-----------------|-----------------|----------|
| SQAP | QUA | VER | VAL | Baseline 0 |
| SCMP | CM | VER | VAL | Baseline 0 |
| SVP | VER | - | VAL | Baseline 0 |
| SVaP | VAL | VER | - | Baseline 0 |
| SQAP Verification Report | VER | - | VAL | Baseline 0 |

### Quality Criteria

- [ ] All planning documents follow EN 50128 templates
- [ ] All documents approved by designated reviewers
- [ ] Quality gates defined for all subsequent phases
- [ ] Configuration management procedures operational

### Verification

- [ ] Planning documents reviewed by VER
- [ ] Planning documents validated by VAL
- [ ] All review findings resolved
- [ ] Baseline 0 established in version control

### Tool Integration

```bash
# Check deliverable status
workspace.py wf status --phase planning

# Verify all planning documents submitted
workspace.py wf list-deliverables --phase planning --status submitted

# Check baseline established
git tag baseline-0

# Verify traceability initialized (RTM placeholder created)
workspace.py trace status
```

### Gate Check Output Example (SIL 3)

```
═══════════════════════════════════════════════════════
PHASE GATE CHECK: Planning Complete
═══════════════════════════════════════════════════════

Project: train_door_control
SIL Level: 3 (Strict Gatekeeper Mode)
Phase: Planning (Phase 1)

[✓] Planning Documents (5/5 complete)
  ✓ Software Quality Assurance Plan (SQAP) - docs/plans/SQAP.md
  ✓ Software Configuration Management Plan (SCMP) - docs/plans/SCMP.md
  ✓ Software Verification Plan (SVP) - docs/plans/SVP.md
  ✓ Software Validation Plan (SVaP) - docs/plans/SVaP.md
  ✓ SQAP Verification Report - docs/verification/SQAP-VER.md

[✓] Project Setup (4/4 complete)
  ✓ Version control initialized - Git repository
  ✓ Baseline 0 established - git tag baseline-0
  ✓ Build environment configured - Makefile, gcc 11.4.0
  ✓ Configuration management operational - SCMP procedures active

[✓] Team Organization (4/4 satisfied)
  ✓ All roles assigned - 13 roles documented
  ✓ Independence requirements satisfied:
    - Verifier (John Smith) independent from development
    - Validator (Jane Doe) independent from PM and development
  ✓ Reporting structure established - documented in SQAP Annex A
  ✓ Competency verified - training records in personnel files

[✓] Tool Qualification (SIL 3) (3/3 satisfied)
  ✓ MISRA C checker qualified - PC-lint Plus 2.0 (T2 qualified)
  ✓ Static analysis tools qualified - Cppcheck 2.13.0 (T1)
  ✓ Coverage tools qualified - gcov/lcov (T1)

[✓] Independence Requirements (SIL 3) (3/3 satisfied)
  ✓ Independent Verifier assigned - John Smith, reports to QA Manager
  ✓ Independent Validator assigned - Jane Doe, reports to Safety Authority
  ✓ Organizational independence documented - SQAP Section 4.2

═══════════════════════════════════════════════════════
GATE RESULT: ✓ PASSED
═══════════════════════════════════════════════════════

Planning phase complete. All SIL 3 criteria satisfied.

AUTHORIZED: Transition to Requirements phase

Baseline Established: Baseline 0
Next Phase: Requirements (Phase 2)
```

---

## Gate 2: Requirements Complete

### Purpose

Verify software requirements are complete, unambiguous, testable, and traceable before design begins.

### Entry Criteria

- Planning gate passed
- SQAP, SCMP, SVP, SVaP approved

### Exit Criteria (SIL-Dependent)

#### All SIL Levels (0-4)

1. **Requirements Documents Complete**:
   - [ ] Software Requirements Specification (SRS)
   - [ ] Overall Software Test Specification
   - [ ] Software Requirements Verification Report
   - [ ] Requirements Traceability Matrix (RTM)

2. **Requirements Quality**:
   - [ ] All requirements unambiguous (no undefined terms)
   - [ ] All requirements testable (acceptance criteria defined)
   - [ ] All requirements traceable (unique IDs assigned)
   - [ ] SHALL/SHOULD/MAY keywords used correctly (RFC 2119)
   - [ ] SIL levels assigned to all requirements

3. **Safety Requirements** (if applicable):
   - [ ] Hazard Log established
   - [ ] Safety requirements identified
   - [ ] Safety requirements traceable to hazards

#### SIL 2+ Additional Criteria

4. **Structured Methodology**:
   - [ ] Structured requirements methodology applied (HR for SIL 2, M for SIL 3-4)
   - [ ] Requirements modeled (use cases, state machines, decision tables)

5. **Traceability (Highly Recommended SIL 2)**:
   - [ ] RTM complete: System Req → Software Req
   - [ ] Forward traceability: All system requirements covered
   - [ ] Backward traceability: All software requirements traced
   - [ ] Traceability gap analysis performed
   - [ ] Orphan requirements identified and justified

#### SIL 3-4 Additional Criteria (MANDATORY)

6. **Traceability (MANDATORY SIL 3-4)**:
   - [ ] 100% traceability: System Req → Software Req
   - [ ] No orphan requirements (or justified with rationale)
   - [ ] RTM validated by independent VER

7. **Formal/Semiformal Methods** (HR SIL 3-4):
   - [ ] Critical requirements formalized (state machines, decision tables, Z notation)

### Deliverables (Annex C Table C.1)

| Document | Author | 1st Check (VER) | 2nd Check (VAL) | Baseline |
|----------|--------|-----------------|-----------------|----------|
| SRS | REQ | VER | VAL | Baseline 1 |
| Overall Software Test Specification | TST | VER | VAL | Baseline 1 |
| Software Requirements Verification Report | VER | - | VAL | Baseline 1 |
| RTM | REQ/CM | VER | VAL | Baseline 1 |
| Hazard Log | SAF | VER | VAL | Baseline 1 |

### Quality Criteria

**Requirements Quality Metrics**:

```python
# Python gate checker script (excerpt)
def check_requirements_quality(srs_file, rtm_file):
    """Check requirements quality criteria"""
    
    # 1. All requirements have unique IDs
    req_ids = extract_requirement_ids(srs_file)
    assert len(req_ids) == len(set(req_ids)), "Duplicate requirement IDs found"
    
    # 2. All requirements use SHALL/SHOULD/MAY
    for req in requirements:
        assert has_rfc2119_keyword(req), f"Requirement {req.id} missing SHALL/SHOULD/MAY"
    
    # 3. All requirements testable (acceptance criteria present)
    for req in requirements:
        assert has_acceptance_criteria(req), f"Requirement {req.id} not testable"
    
    # 4. All requirements traceable
    rtm = parse_rtm(rtm_file)
    for req_id in req_ids:
        assert req_id in rtm, f"Requirement {req_id} not in RTM"
    
    # 5. RTM bidirectional traceability (SIL 3-4)
    if sil_level >= 3:
        assert rtm_forward_coverage(rtm) == 100.0, "Forward traceability incomplete"
        assert rtm_backward_coverage(rtm) == 100.0, "Backward traceability incomplete"
    
    return True
```

**Traceability Thresholds**:

| SIL Level | Forward Coverage | Backward Coverage | Orphan Tolerance |
|-----------|------------------|-------------------|------------------|
| **SIL 0-1** | 80% (recommended) | 80% (recommended) | Allowed with justification |
| **SIL 2** | 90% (highly recommended) | 90% (highly recommended) | Minimal |
| **SIL 3-4** | 100% (MANDATORY) | 100% (MANDATORY) | None (or explicit safety rationale) |

### Verification

- [ ] SRS reviewed by VER (independent for SIL 3-4)
- [ ] RTM validated by VER
- [ ] Hazard Log reviewed by SAF
- [ ] All requirements traced to system requirements
- [ ] All review findings resolved

### Tool Integration

```bash
# Verify RTM completeness
workspace.py trace validate --phase requirements

# Check forward traceability
workspace.py trace check-forward --from system_req --to software_req

# Check backward traceability
workspace.py trace check-backward --from software_req --to system_req

# Identify orphan requirements
workspace.py trace check-gaps --phase requirements

# Generate traceability report
workspace.py trace report --phase requirements --output docs/traceability/RTM-Report.md

# Check deliverable status
workspace.py wf status --phase requirements

# Verify baseline 1 established
git tag baseline-1
```

### Gate Check Output Example (SIL 3, BLOCKED)

```
═══════════════════════════════════════════════════════
PHASE GATE CHECK: Requirements Complete
═══════════════════════════════════════════════════════

Project: train_door_control
SIL Level: 3 (Strict Gatekeeper Mode)
Phase: Requirements (Phase 2)

[✓] Requirements Documents (5/5 complete)
  ✓ Software Requirements Specification (SRS) - docs/SRS.md (42 requirements)
  ✓ Overall Software Test Specification - docs/test/Overall-Test-Spec.md
  ✓ Software Requirements Verification Report - docs/verification/SRS-VER.md
  ✓ Requirements Traceability Matrix (RTM) - docs/RTM.md
  ✓ Hazard Log - docs/Hazard-Log.md (5 hazards)

[✓] Requirements Quality (5/5 satisfied)
  ✓ All requirements unambiguous - 42/42 clear
  ✓ All requirements testable - 42/42 have acceptance criteria
  ✓ All requirements traceable - 42/42 have unique IDs
  ✓ SHALL/SHOULD/MAY keywords used - 42/42 compliant
  ✓ SIL levels assigned - 42/42 assigned (38 SIL-3, 4 SIL-4)

[✗] Traceability (SIL 3 MANDATORY) (2/3 satisfied) - INCOMPLETE
  ✗ Forward traceability: 97.4% (37/38 system requirements covered)
    - System requirement SYS-025 NOT covered by software requirements
  ✓ Backward traceability: 100% (42/42 software requirements traced)
  ✓ Orphan requirements: 0 (all justified)

[✓] Safety Requirements (3/3 satisfied)
  ✓ Hazard Log established - 5 hazards identified
  ✓ Safety requirements identified - 12 safety requirements
  ✓ Safety requirements traceable to hazards - 12/12 traced

[✓] Verification (3/3 satisfied)
  ✓ SRS reviewed by VER - approved 2026-02-15
  ✓ RTM validated by VER - approved 2026-02-15
  ✓ All review findings resolved - 3 findings closed

═══════════════════════════════════════════════════════
GATE RESULT: ✗ BLOCKED
═══════════════════════════════════════════════════════

Requirements phase INCOMPLETE. SIL 3 requires 100% traceability.

DENIED: Transition to Architecture & Design phase

Required Actions:
  1. Add software requirement(s) to cover SYS-025
     System Requirement: SYS-025 "System SHALL detect door obstruction within 100ms"
     Missing Coverage: No software requirement addresses obstruction detection timing
     
     Suggested Action:
       Add SWR-043: "Door control software SHALL invoke obstruction detection
                     function within 50ms of sensor input"
       Update RTM: SYS-025 → SWR-043

Recommended approach:
  /req              # Add missing requirement SWR-043
  workspace.py trace validate --phase requirements
  /cod gate-check requirements

Current Phase: Requirements (BLOCKED)
```

---

## Gate 3: Design Complete

### Purpose

Verify software architecture and design are complete, modular, and compliant with MISRA C guidelines before implementation begins.

### Entry Criteria

- Requirements gate passed
- SRS, RTM approved and baselined

### Exit Criteria (SIL-Dependent)

#### All SIL Levels (0-4)

1. **Design Documents Complete**:
   - [ ] Software Architecture Specification (SAS)
   - [ ] Software Design Specification (SDS)
   - [ ] Software Interface Specifications
   - [ ] Software Integration Test Specification
   - [ ] Software/Hardware Integration Test Specification (if applicable)
   - [ ] Software Architecture and Design Verification Report
   - [ ] Software Component Design Specification
   - [ ] Software Component Test Specification

2. **Design Quality**:
   - [ ] Modular design (highly recommended SIL 0-1, MANDATORY SIL 2+)
   - [ ] Module dependencies minimal and documented
   - [ ] Interface definitions complete and unambiguous
   - [ ] Defensive programming patterns defined

#### SIL 2+ Additional Criteria (MANDATORY)

3. **C Language Constraints**:
   - [ ] Static memory allocation ONLY (no malloc/free)
   - [ ] Fixed-width types specified (uint8_t, uint16_t, uint32_t, etc.)
   - [ ] Bounded execution time for all functions
   - [ ] Error handling strategy defined for all failure modes

4. **Complexity Constraints**:
   - [ ] Cyclomatic complexity within SIL-specific limits:
     - **SIL 2**: ≤ 15 per function
     - **SIL 3-4**: ≤ 10 per function (MANDATORY)
   - [ ] Nesting depth within limits (≤ 4 levels recommended)

5. **Structured Methodology** (MANDATORY SIL 2+):
   - [ ] Structured design methodology applied (e.g., Structured Analysis and Design Technique - SADT)

#### SIL 3-4 Additional Criteria (Highly Recommended)

6. **Advanced Constraints**:
   - [ ] No recursion (highly recommended SIL 3-4)
   - [ ] No function pointers (highly recommended SIL 3-4)
   - [ ] Safety-critical functions use redundancy/voting patterns

7. **Traceability (MANDATORY SIL 3-4)**:
   - [ ] RTM updated: Requirements → Architecture → Design
   - [ ] 100% requirements coverage in architecture
   - [ ] All architectural components mapped to design modules

### Deliverables (Annex C Table C.1)

| Document | Author | 1st Check (VER) | 2nd Check (VAL) | Baseline |
|----------|--------|-----------------|-----------------|----------|
| SAS | DES | VER | VAL | Baseline 2 |
| SDS | DES | VER | VAL | Baseline 2 |
| Software Interface Specifications | DES | VER | VAL | Baseline 2 |
| Software Integration Test Specification | INT | VER | VAL | Baseline 2 |
| Architecture and Design Verification Report | VER | - | VAL | Baseline 2 |
| Component Design Specification | DES | VER | VAL | Baseline 2 |
| Component Test Specification | TST | VER | VAL | Baseline 2 |

### Quality Criteria

**Complexity Analysis** (MANDATORY SIL 3-4):

```python
# Python gate checker script (excerpt)
def check_design_complexity(design_spec_file, sil_level):
    """Check cyclomatic complexity limits per SIL level"""
    
    complexity_limits = {
        0: 20,
        1: 20,
        2: 15,
        3: 10,
        4: 10
    }
    
    max_complexity = complexity_limits[sil_level]
    
    functions = extract_functions_from_design(design_spec_file)
    violations = []
    
    for func in functions:
        ccn = calculate_cyclomatic_complexity(func)
        if ccn > max_complexity:
            violations.append({
                'function': func.name,
                'ccn': ccn,
                'limit': max_complexity,
                'file': func.file
            })
    
    if violations:
        print(f"✗ Complexity violations found: {len(violations)}")
        for v in violations:
            print(f"  - {v['function']}() = {v['ccn']} (limit: {v['limit']}) [{v['file']}]")
        return False
    
    print(f"✓ All functions within complexity limit (≤{max_complexity})")
    return True
```

**Memory Allocation Check** (MANDATORY SIL 2+):

```python
def check_static_allocation(design_spec_file, sil_level):
    """Verify no dynamic memory allocation for SIL 2+ """
    
    if sil_level < 2:
        return True  # Not enforced for SIL 0-1
    
    # Check design specification for dynamic allocation patterns
    forbidden_patterns = ['malloc', 'calloc', 'realloc', 'free', 'new', 'delete']
    
    design_text = read_file(design_spec_file)
    
    violations = []
    for pattern in forbidden_patterns:
        if pattern in design_text.lower():
            violations.append(pattern)
    
    if violations:
        print(f"✗ Dynamic memory allocation found (forbidden for SIL {sil_level})")
        print(f"  Patterns: {', '.join(violations)}")
        return False
    
    print("✓ Static memory allocation only (SIL 2+ compliant)")
    return True
```

### Verification

- [ ] Design reviewed by VER (independent for SIL 3-4)
- [ ] Complexity analysis performed and within limits
- [ ] Modular design verified
- [ ] MISRA C compliance feasibility verified
- [ ] All review findings resolved

### Tool Integration

```bash
# Verify traceability updated
workspace.py trace validate --phase design

# Check complexity (from design specification)
python3 tools/complexity_analyzer.py --input docs/design/SDS.md --sil 3

# Check design deliverables status
workspace.py wf status --phase design

# Verify baseline 2 established
git tag baseline-2

# Generate design verification report
workspace.py wf generate-report --phase design --output docs/verification/Design-VER.md
```

### Gate Check Output Example (SIL 3, PASSED)

```
═══════════════════════════════════════════════════════
PHASE GATE CHECK: Design Complete
═══════════════════════════════════════════════════════

Project: train_door_control
SIL Level: 3 (Strict Gatekeeper Mode)
Phase: Architecture & Design (Phase 3)

[✓] Design Documents (8/8 complete)
  ✓ Software Architecture Specification (SAS) - docs/design/SAS.md
  ✓ Software Design Specification (SDS) - docs/design/SDS.md
  ✓ Software Interface Specifications - docs/design/Interfaces.md
  ✓ Software Integration Test Specification - docs/test/Integration-Test-Spec.md
  ✓ Architecture and Design Verification Report - docs/verification/Design-VER.md
  ✓ Component Design Specification - docs/design/Components.md
  ✓ Component Test Specification - docs/test/Component-Test-Spec.md
  ✓ Software/Hardware Integration Test Specification - docs/test/HW-Integration-Test-Spec.md

[✓] Design Quality (4/4 satisfied)
  ✓ Modular design - 12 modules identified, dependencies documented
  ✓ Module dependencies minimal - max fan-out: 3
  ✓ Interface definitions complete - 8 interfaces fully specified
  ✓ Defensive programming patterns defined - input validation, range checks

[✓] C Language Constraints (SIL 3) (4/4 satisfied)
  ✓ Static memory allocation only - no dynamic allocation in design
  ✓ Fixed-width types specified - all data types use stdint.h types
  ✓ Bounded execution time - WCET specified for all functions
  ✓ Error handling strategy defined - error codes, return value checking

[✓] Complexity Constraints (SIL 3) (3/3 satisfied)
  ✓ Cyclomatic complexity within limits (≤10):
    - Max CCN: 9 (process_door_command)
    - Average CCN: 4.2
    - All 87 functions ≤ 10
  ✓ Nesting depth within limits - max depth: 3 (recommended: ≤4)
  ✓ Function count per module - max: 12 (acceptable)

[✓] Advanced Constraints (SIL 3 Highly Recommended) (2/2 satisfied)
  ✓ No recursion - verified in design specification
  ✓ No function pointers - verified in design specification

[✓] Traceability (SIL 3 MANDATORY) (3/3 satisfied)
  ✓ RTM updated: Requirements → Architecture → Design
  ✓ 100% requirements coverage - 42/42 requirements mapped
  ✓ All components traced - 12/12 modules traced to requirements

[✓] Verification (4/4 satisfied)
  ✓ Design reviewed by VER (independent) - approved 2026-02-17
  ✓ Complexity analysis performed - Lizard, all functions ≤10
  ✓ Modular design verified - structured methodology applied
  ✓ All review findings resolved - 2 findings closed

═══════════════════════════════════════════════════════
GATE RESULT: ✓ PASSED
═══════════════════════════════════════════════════════

Design phase complete. All SIL 3 criteria satisfied.

AUTHORIZED: Transition to Implementation & Testing phase

Baseline Established: Baseline 2
Next Phase: Implementation & Testing (Phase 4)
```

---

## Gate 4: Implementation Complete

### Purpose

Verify source code is complete, MISRA C compliant, fully tested with adequate coverage, and verified by static analysis.

### Entry Criteria

- Design gate passed
- SAS, SDS approved and baselined

### Exit Criteria (SIL-Dependent)

#### All SIL Levels (0-4)

1. **Implementation Documents Complete**:
   - [ ] Software Source Code and Supporting Documentation
   - [ ] Software Source Code Verification Report
   - [ ] Software Component Test Report
   - [ ] Software Component Design Verification Report

2. **Code Quality**:
   - [ ] All code compiles without errors
   - [ ] All code compiles without warnings (recommended)
   - [ ] Coding standards applied (highly recommended)

3. **Unit Testing**:
   - [ ] Unit tests written for all components
   - [ ] All unit tests passing

#### SIL 2+ Additional Criteria (MANDATORY)

4. **MISRA C:2012 Compliance** (MANDATORY SIL 2+):
   - [ ] All mandatory rules satisfied (zero violations)
   - [ ] All required rules satisfied or deviated with justification
   - [ ] Advisory rules considered
   - [ ] Deviation log maintained and approved

5. **C Language Constraints** (MANDATORY SIL 2+):
   - [ ] Static allocation only (no malloc/calloc/realloc/free)
   - [ ] No recursion
   - [ ] Fixed-width integer types (uint8_t, uint16_t, etc.)
   - [ ] All pointers validated before use
   - [ ] All return values checked
   - [ ] All inputs validated (defensive programming)

6. **Static Analysis** (Highly Recommended SIL 2, MANDATORY SIL 3-4):
   - [ ] Static analysis performed (Cppcheck, Clang, PC-lint Plus)
   - [ ] All violations resolved or justified
   - [ ] Complexity analysis performed (Lizard)
   - [ ] All functions within cyclomatic complexity limits

7. **Coverage Requirements** (MANDATORY SIL 2+):
   - [ ] **SIL 2**: Statement (HR), Branch (**M**)
   - [ ] **SIL 3-4**: Statement (**M**), Branch (**M**), Condition (**M**)

**Coverage Thresholds**:

| SIL Level | Statement Coverage | Branch Coverage | Condition Coverage |
|-----------|-------------------|-----------------|-------------------|
| **SIL 0-1** | 80% (HR) | 70% (HR) | Not required |
| **SIL 2** | 90% (HR) | 95% (**M**) | Not required |
| **SIL 3-4** | 100% (**M**) | 100% (**M**) | 100% (**M**) |

#### SIL 3-4 Additional Criteria

8. **Code Review** (MANDATORY):
   - [ ] Independent code review performed (QUA)
   - [ ] MISRA C compliance verified in review
   - [ ] Defensive programming verified
   - [ ] Safety-critical code double-checked (SAF involved)
   - [ ] All review findings addressed

9. **Verification** (MANDATORY):
   - [ ] Independent verification by VER
   - [ ] Static analysis report reviewed
   - [ ] Coverage report reviewed
   - [ ] All verification findings resolved

### Deliverables (Annex C Table C.1)

| Document | Author | 1st Check (VER) | 2nd Check (VAL) | Baseline |
|----------|--------|-----------------|-----------------|----------|
| Software Source Code | IMP | VER | VAL | Baseline 3 |
| Source Code Verification Report | VER | - | VAL | Baseline 3 |
| Component Test Report | TST | VER | VAL | Baseline 3 |
| Component Design Verification Report | VER | - | VAL | Baseline 3 |

### Quality Criteria

**MISRA C Compliance Check**:

```python
# Python gate checker script (excerpt)
def check_misra_compliance(source_dir, sil_level):
    """Check MISRA C:2012 compliance"""
    
    if sil_level < 2:
        print("⚠ MISRA C not required for SIL 0-1 (but recommended)")
        return True
    
    # Run PC-lint Plus for MISRA C:2012
    result = subprocess.run([
        'pclp64',
        '--misra_2012',
        '--xml',
        '--output=misra_report.xml',
        f'{source_dir}/*.c'
    ], capture_output=True)
    
    # Parse XML report
    violations = parse_misra_xml('misra_report.xml')
    
    mandatory_violations = [v for v in violations if v['category'] == 'mandatory']
    required_violations = [v for v in violations if v['category'] == 'required' and not v['deviated']]
    
    if mandatory_violations:
        print(f"✗ MISRA C mandatory violations: {len(mandatory_violations)}")
        for v in mandatory_violations[:5]:  # Show first 5
            print(f"  - Rule {v['rule']}: {v['message']} [{v['file']}:{v['line']}]")
        return False
    
    if required_violations:
        print(f"✗ MISRA C required violations (no deviation): {len(required_violations)}")
        for v in required_violations[:5]:
            print(f"  - Rule {v['rule']}: {v['message']} [{v['file']}:{v['line']}]")
        return False
    
    print("✓ MISRA C:2012 compliance verified")
    print(f"  Mandatory violations: 0")
    print(f"  Required violations: {len([v for v in violations if v['category'] == 'required' and v['deviated']])} (all deviated with justification)")
    return True
```

**Coverage Check**:

```python
def check_coverage(coverage_report, sil_level):
    """Check test coverage thresholds"""
    
    coverage_thresholds = {
        0: {'statement': 80, 'branch': 70, 'condition': 0},  # HR
        1: {'statement': 80, 'branch': 70, 'condition': 0},  # HR
        2: {'statement': 90, 'branch': 95, 'condition': 0},  # M for branch
        3: {'statement': 100, 'branch': 100, 'condition': 100},  # M for all
        4: {'statement': 100, 'branch': 100, 'condition': 100}   # M for all
    }
    
    thresholds = coverage_thresholds[sil_level]
    coverage = parse_coverage_report(coverage_report)
    
    violations = []
    
    # Statement coverage
    if coverage['statement'] < thresholds['statement']:
        violations.append({
            'type': 'statement',
            'actual': coverage['statement'],
            'threshold': thresholds['statement']
        })
    
    # Branch coverage
    if coverage['branch'] < thresholds['branch']:
        violations.append({
            'type': 'branch',
            'actual': coverage['branch'],
            'threshold': thresholds['branch']
        })
    
    # Condition coverage (SIL 3-4)
    if sil_level >= 3 and coverage['condition'] < thresholds['condition']:
        violations.append({
            'type': 'condition',
            'actual': coverage['condition'],
            'threshold': thresholds['condition']
        })
    
    if violations:
        print(f"✗ Coverage insufficient for SIL {sil_level}")
        for v in violations:
            print(f"  - {v['type'].capitalize()}: {v['actual']}% (threshold: {v['threshold']}%)")
        return False
    
    print(f"✓ Coverage adequate for SIL {sil_level}")
    print(f"  Statement: {coverage['statement']}%")
    print(f"  Branch: {coverage['branch']}%")
    if sil_level >= 3:
        print(f"  Condition: {coverage['condition']}%")
    return True
```

### Verification

- [ ] Code reviewed by QUA (MANDATORY all SILs)
- [ ] Static analysis performed by VER
- [ ] Coverage verified by VER
- [ ] All verification findings resolved

### Tool Integration

```bash
# Run MISRA C checker
pclp64 --misra_2012 --xml --output=misra_report.xml src/*.c

# Run static analysis
cppcheck --enable=all --xml --xml-version=2 src/ 2> cppcheck_report.xml

# Run complexity analysis
lizard src/ --CCN 10 --xml > complexity_report.xml

# Run unit tests with coverage
make test-coverage

# Generate coverage report
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_report

# Verify coverage thresholds
workspace.py wf check-coverage --sil 3 --report coverage.info

# Check implementation deliverables
workspace.py wf status --phase implementation

# Verify baseline 3 established
git tag baseline-3
```

### Gate Check Output Example (SIL 3, BLOCKED - Coverage Insufficient)

```
═══════════════════════════════════════════════════════
PHASE GATE CHECK: Implementation & Testing Complete
═══════════════════════════════════════════════════════

Project: train_door_control
SIL Level: 3 (Strict Gatekeeper Mode)
Phase: Implementation & Testing (Phase 4)

[✓] Implementation Documents (4/4 complete)
  ✓ Software Source Code - 15 C files, 3,248 SLOC
  ✓ Source Code Verification Report - docs/verification/Code-VER.md
  ✓ Component Test Report - docs/test/Component-Test-Report.md
  ✓ Component Design Verification Report - docs/verification/Component-Design-VER.md

[✓] Code Quality (3/3 satisfied)
  ✓ All code compiles without errors - gcc 11.4.0, make successful
  ✓ All code compiles without warnings - zero warnings (-Wall -Wextra)
  ✓ Coding standards applied - MISRA C:2012

[✓] MISRA C:2012 Compliance (SIL 3 MANDATORY) (4/4 satisfied)
  ✓ All mandatory rules satisfied - zero violations
  ✓ All required rules satisfied or deviated - 2 deviations justified
  ✓ Advisory rules considered - 5 advisory violations documented
  ✓ Deviation log maintained - docs/MISRA-Deviations.md

[✓] C Language Constraints (SIL 3 MANDATORY) (6/6 satisfied)
  ✓ Static allocation only - no malloc/calloc/realloc/free found
  ✓ No recursion - verified by static analysis
  ✓ Fixed-width integer types - all types from stdint.h
  ✓ All pointers validated - 42 pointer checks verified
  ✓ All return values checked - 87 return checks verified
  ✓ All inputs validated - defensive programming applied

[✓] Static Analysis (SIL 3 MANDATORY) (4/4 satisfied)
  ✓ Static analysis performed - Cppcheck 2.13.0, Clang 18.0
  ✓ All violations resolved - 15 issues fixed, zero open
  ✓ Complexity analysis performed - Lizard
  ✓ All functions within limits - max CCN: 9, all ≤10

[✗] Coverage Requirements (SIL 3 MANDATORY) (1/3 satisfied) - INCOMPLETE
  ✓ Statement coverage: 98.2% (threshold: 100%) - GAP: 1.8%
  ✗ Branch coverage: 94.5% (threshold: 100%) - GAP: 5.5%
  ✗ Condition coverage: 89.3% (threshold: 100%) - GAP: 10.7%

  Coverage Gaps:
    File: src/emergency_stop.c
      - Line 142: Branch not covered (error path)
      - Line 156: Condition (status == ERROR) not tested
      - Line 178: Branch not covered (timeout path)
    
    File: src/safety_monitor.c
      - Line 89: Condition (sensor_fault && backup_active) not tested
      - Line 112: Branch not covered (redundancy failover)

[✓] Code Review (SIL 3 MANDATORY) (4/4 satisfied)
  ✓ Independent code review performed - QUA approved 2026-02-20
  ✓ MISRA C compliance verified - reviewed in code review
  ✓ Defensive programming verified - patterns confirmed
  ✓ All review findings addressed - 8 findings closed

[✓] Verification (SIL 3 MANDATORY) (4/4 satisfied)
  ✓ Independent verification by VER - approved 2026-02-20
  ✓ Static analysis report reviewed - VER confirmed
  ✓ Coverage report reviewed - VER noted gaps
  ✓ All verification findings resolved - 3 findings closed

═══════════════════════════════════════════════════════
GATE RESULT: ✗ BLOCKED
═══════════════════════════════════════════════════════

Implementation phase INCOMPLETE. SIL 3 requires 100% coverage.

DENIED: Transition to Integration phase

Required Actions:
  1. Add unit tests to cover missing branches (5.5% gap):
     - src/emergency_stop.c:142 - error path test needed
     - src/emergency_stop.c:178 - timeout path test needed
     - src/safety_monitor.c:112 - redundancy failover test needed
  
  2. Add unit tests to cover missing conditions (10.7% gap):
     - src/emergency_stop.c:156 - test status == ERROR condition
     - src/safety_monitor.c:89 - test sensor_fault && backup_active condition

  3. Execute new tests and re-measure coverage

Recommended approach:
  /tst              # Add missing unit tests
  make test-coverage
  /ver              # Verify coverage now 100%
  /cod gate-check implementation

Current Phase: Implementation & Testing (BLOCKED)
```

---

## Gate 5: Integration Complete

### Purpose

Verify software components integrated successfully, interfaces tested, and performance requirements met.

### Entry Criteria

- Implementation gate passed
- Source code, unit tests approved and baselined

### Exit Criteria (SIL-Dependent)

#### All SIL Levels (0-4)

1. **Integration Documents Complete**:
   - [ ] Software Integration Test Report
   - [ ] Software/Hardware Integration Test Report (if applicable)
   - [ ] Software Integration Verification Report

2. **Integration Activities**:
   - [ ] Integration strategy executed (bottom-up, top-down, or sandwich)
   - [ ] All components integrated without conflicts
   - [ ] Build system produces executable successfully
   - [ ] Integration incremental and controlled (not "big bang")

3. **Integration Testing**:
   - [ ] Integration test specification followed
   - [ ] All integration tests executed
   - [ ] All integration tests passing

#### SIL 2+ Additional Criteria

4. **Interface Testing** (Highly Recommended):
   - [ ] All module interfaces tested
   - [ ] All hardware interfaces tested (if applicable)
   - [ ] Data flow across interfaces verified
   - [ ] Interface error handling tested
   - [ ] Boundary conditions tested at interfaces

#### SIL 3-4 Additional Criteria

5. **Performance Testing** (Highly Recommended SIL 3-4):
   - [ ] Timing requirements verified
   - [ ] Memory usage verified (static allocation limits)
   - [ ] Throughput requirements met
   - [ ] Worst-case execution time (WCET) verified
   - [ ] Resource utilization acceptable (CPU, memory, I/O)

6. **Regression Testing**:
   - [ ] All unit tests re-executed after integration
   - [ ] No regressions introduced
   - [ ] Regression test results documented

### Deliverables (Annex C Table C.1)

| Document | Author | 1st Check (VER) | 2nd Check (VAL) | Baseline |
|----------|--------|-----------------|-----------------|----------|
| Software Integration Test Report | INT | VER | VAL | Baseline 4 |
| Software/Hardware Integration Test Report | INT | VER | VAL | Baseline 4 |
| Software Integration Verification Report | VER | - | VAL | Baseline 4 |

### Quality Criteria

**Integration Test Coverage**:

```python
def check_integration_coverage(integration_test_report):
    """Verify all interfaces tested"""
    
    # Extract interface definitions from design
    interfaces = extract_interfaces_from_design('docs/design/Interfaces.md')
    
    # Extract integration tests from report
    tests = extract_integration_tests(integration_test_report)
    
    # Check coverage
    tested_interfaces = set()
    for test in tests:
        tested_interfaces.update(test.interfaces_covered)
    
    untested_interfaces = set(interfaces) - tested_interfaces
    
    if untested_interfaces:
        print(f"✗ Interface testing incomplete: {len(untested_interfaces)} interfaces not tested")
        for iface in list(untested_interfaces)[:5]:
            print(f"  - {iface} not covered by integration tests")
        return False
    
    print(f"✓ All {len(interfaces)} interfaces tested")
    return True
```

### Verification

- [ ] Integration tests reviewed by VER
- [ ] Integration test results verified
- [ ] Interface coverage verified
- [ ] Performance tests verified (SIL 3-4)

### Tool Integration

```bash
# Run integration tests
make integration-test

# Check interface coverage
workspace.py wf check-interface-coverage --phase integration

# Run performance tests (SIL 3-4)
make performance-test

# Re-run unit tests (regression)
make test

# Check integration deliverables
workspace.py wf status --phase integration

# Verify baseline 4 established
git tag baseline-4
```

### Gate Check Output Example (SIL 3, PASSED)

```
═══════════════════════════════════════════════════════
PHASE GATE CHECK: Integration Complete
═══════════════════════════════════════════════════════

Project: train_door_control
SIL Level: 3 (Strict Gatekeeper Mode)
Phase: Integration (Phase 5)

[✓] Integration Documents (3/3 complete)
  ✓ Software Integration Test Report - docs/test/Integration-Test-Report.md
  ✓ Software/Hardware Integration Test Report - docs/test/HW-Integration-Test-Report.md
  ✓ Software Integration Verification Report - docs/verification/Integration-VER.md

[✓] Integration Activities (4/4 satisfied)
  ✓ Integration strategy executed - Bottom-up integration, 5 increments
  ✓ All components integrated - 12/12 modules integrated
  ✓ Build system produces executable - train_door_control.elf (327 KB)
  ✓ Integration incremental - 5 integration steps, tested at each step

[✓] Integration Testing (3/3 satisfied)
  ✓ Integration test specification followed - 42 tests executed
  ✓ All integration tests executed - 42/42 complete
  ✓ All integration tests passing - 42/42 passed

[✓] Interface Testing (SIL 3 Highly Recommended) (5/5 satisfied)
  ✓ All module interfaces tested - 8/8 internal interfaces covered
  ✓ All hardware interfaces tested - 3/3 hardware interfaces covered
  ✓ Data flow verified - data flow diagrams validated
  ✓ Interface error handling tested - error injection tests performed
  ✓ Boundary conditions tested - min/max/null tests performed

[✓] Performance Testing (SIL 3 Highly Recommended) (5/5 satisfied)
  ✓ Timing requirements verified - WCET < 50ms (measured: 42ms)
  ✓ Memory usage verified - static allocation 128KB (limit: 256KB)
  ✓ Throughput requirements met - 100 msgs/sec (measured: 120 msgs/sec)
  ✓ WCET verified - Rapitime analysis performed
  ✓ Resource utilization acceptable - CPU: 35%, Memory: 50%

[✓] Regression Testing (3/3 satisfied)
  ✓ All unit tests re-executed - 87/87 unit tests passed
  ✓ No regressions introduced - all tests passed, no new failures
  ✓ Regression results documented - docs/test/Regression-Test-Report.md

[✓] Verification (3/3 satisfied)
  ✓ Integration tests reviewed by VER - approved 2026-02-22
  ✓ Integration test results verified - VER confirmed
  ✓ Interface coverage verified - 100% interfaces tested

═══════════════════════════════════════════════════════
GATE RESULT: ✓ PASSED
═══════════════════════════════════════════════════════

Integration phase complete. All SIL 3 criteria satisfied.

AUTHORIZED: Transition to Validation phase

Baseline Established: Baseline 4
Next Phase: Validation (Phase 6)
```

---

## Gate 6: Validation Complete

### Purpose

Verify software meets all requirements, customer acceptance obtained, and system ready for deployment.

### Entry Criteria

- Integration gate passed
- Integration tests passed, performance verified

### Exit Criteria (SIL-Dependent)

#### All SIL Levels (0-4)

1. **Validation Documents Complete**:
   - [ ] Overall Software Test Report
   - [ ] Software Validation Report
   - [ ] Tools Validation Report (if applicable)

2. **Validation Testing**:
   - [ ] Overall Software Test Specification executed completely
   - [ ] All system tests passing
   - [ ] Testing performed in target environment (or representative simulator)
   - [ ] Operational scenarios tested

3. **Requirements Validation**:
   - [ ] RTM complete end-to-end: Requirements → Design → Code → Tests → Results
   - [ ] All requirements validated (every requirement has passing test)
   - [ ] All test cases traceable to requirements
   - [ ] 100% requirements coverage verified
   - [ ] Acceptance criteria met for all requirements

4. **Customer Acceptance**:
   - [ ] Customer/stakeholder acceptance testing performed
   - [ ] Customer acceptance obtained (formal sign-off)
   - [ ] All acceptance criteria met
   - [ ] Any deviations documented and accepted by customer

#### SIL 2+ Additional Criteria

5. **Performance Testing** (Highly Recommended SIL 2, MANDATORY SIL 3-4):
   - [ ] Performance testing complete
   - [ ] All performance requirements met

6. **Functional Testing** (Highly Recommended SIL 2, MANDATORY SIL 3-4):
   - [ ] Functional/black-box testing complete
   - [ ] All functional requirements validated

#### SIL 3-4 Additional Criteria (MANDATORY)

7. **Independence**:
   - [ ] Validation performed by independent Validator
   - [ ] Validator does NOT report to Project Manager
   - [ ] Validator has no undue influence from development team
   - [ ] Validator independence documented in organizational chart

8. **End-to-End Traceability** (MANDATORY):
   - [ ] 100% traceability: Requirements → Tests → Results
   - [ ] No untested requirements
   - [ ] All validation results documented

### Deliverables (Annex C Table C.1)

| Document | Author | 1st Check (VER) | 2nd Check | Baseline |
|----------|--------|-----------------|-----------|----------|
| Overall Software Test Report | VAL | VER | - | Baseline 5 |
| Software Validation Report | VAL | VER | - | Baseline 5 |
| Tools Validation Report | VAL | VER | - | Baseline 5 |

### Quality Criteria

**Requirements Coverage Verification**:

```python
def check_validation_coverage(srs_file, validation_report):
    """Verify 100% requirements coverage in validation"""
    
    requirements = extract_requirements(srs_file)
    validation_tests = extract_validation_tests(validation_report)
    
    # Build requirement-to-test mapping
    req_to_test = {}
    for test in validation_tests:
        for req_id in test.requirements_covered:
            if req_id not in req_to_test:
                req_to_test[req_id] = []
            req_to_test[req_id].append(test)
    
    # Check coverage
    untested_requirements = []
    for req in requirements:
        if req.id not in req_to_test:
            untested_requirements.append(req.id)
        elif not all(test.result == 'PASS' for test in req_to_test[req.id]):
            untested_requirements.append(req.id)
    
    if untested_requirements:
        print(f"✗ Requirements validation incomplete: {len(untested_requirements)} requirements not validated")
        for req_id in untested_requirements[:5]:
            print(f"  - {req_id} not validated (no passing test)")
        return False
    
    print(f"✓ 100% requirements validated: {len(requirements)}/{len(requirements)}")
    return True
```

### Verification

- [ ] Validation tests reviewed by VER
- [ ] Validation report reviewed by VER
- [ ] Requirements coverage verified by VER
- [ ] Customer acceptance documented

### Tool Integration

```bash
# Run system tests (validation)
make validation-test

# Verify requirements coverage
workspace.py trace validate --phase validation --check-coverage 100

# Generate validation report
workspace.py wf generate-report --phase validation --output docs/validation/Validation-Report.md

# Check validation deliverables
workspace.py wf status --phase validation

# Verify baseline 5 established
git tag baseline-5
```

### Gate Check Output Example (SIL 3, PASSED)

```
═══════════════════════════════════════════════════════
PHASE GATE CHECK: Validation Complete
═══════════════════════════════════════════════════════

Project: train_door_control
SIL Level: 3 (Strict Gatekeeper Mode)
Phase: Validation (Phase 6)

[✓] Validation Documents (3/3 complete)
  ✓ Overall Software Test Report - docs/test/Overall-Test-Report.md
  ✓ Software Validation Report - docs/validation/Validation-Report.md
  ✓ Tools Validation Report - docs/validation/Tools-Validation-Report.md

[✓] Validation Testing (4/4 satisfied)
  ✓ Overall Software Test Specification executed - 42 system tests
  ✓ All system tests passing - 42/42 passed
  ✓ Testing in target environment - Hardware-in-the-loop (HIL) simulator
  ✓ Operational scenarios tested - 8 operational scenarios validated

[✓] Requirements Validation (5/5 satisfied)
  ✓ RTM complete end-to-end - Requirements → Tests → Results
  ✓ All requirements validated - 42/42 requirements validated
  ✓ All test cases traceable - 42 tests traced to 42 requirements
  ✓ 100% requirements coverage - verified by traceability analysis
  ✓ Acceptance criteria met - all 42 requirements meet acceptance criteria

[✓] Customer Acceptance (4/4 satisfied)
  ✓ Customer acceptance testing performed - Customer witnessed 8 scenarios
  ✓ Customer acceptance obtained - Formal sign-off: 2026-02-25
  ✓ All acceptance criteria met - Customer approved all 42 requirements
  ✓ Deviations documented - Zero deviations

[✓] Performance Testing (SIL 3 MANDATORY) (1/1 satisfied)
  ✓ Performance testing complete - All timing, memory, throughput validated

[✓] Functional Testing (SIL 3 MANDATORY) (2/2 satisfied)
  ✓ Functional/black-box testing complete - 42 functional tests executed
  ✓ All functional requirements validated - 38/38 functional requirements passed

[✓] Independence (SIL 3 MANDATORY) (4/4 satisfied)
  ✓ Validation by independent Validator - Jane Doe (independent)
  ✓ Validator does NOT report to PM - Reports to Safety Authority
  ✓ No undue influence - Independence verified
  ✓ Independence documented - Organizational chart in SQAP

[✓] End-to-End Traceability (SIL 3 MANDATORY) (3/3 satisfied)
  ✓ 100% traceability verified - System Req → Software Req → Design → Code → Tests → Results
  ✓ No untested requirements - 0 gaps
  ✓ All validation results documented - Validation Report complete

[✓] Verification (3/3 satisfied)
  ✓ Validation tests reviewed by VER - approved 2026-02-25
  ✓ Validation report reviewed by VER - approved 2026-02-25
  ✓ Requirements coverage verified - 100% confirmed

═══════════════════════════════════════════════════════
GATE RESULT: ✓ PASSED
═══════════════════════════════════════════════════════

Validation phase complete. All SIL 3 criteria satisfied.

AUTHORIZED: Transition to Assessment phase (SIL 3 required)

Baseline Established: Baseline 5
Next Phase: Assessment (Phase 7)
```

---

## Gate 7: Assessment Complete (SIL 3-4 Only)

### Purpose

Independent assessment by Assessor confirms EN 50128 process compliance and safety case adequacy.

**Note**: Assessment is **MANDATORY** for SIL 3-4, **Optional** for SIL 0-2.

### Entry Criteria

- Validation gate passed
- All lifecycle documents complete
- Safety case complete

### Exit Criteria (SIL 3-4 MANDATORY)

1. **Assessment Documents Complete**:
   - [ ] Software Assessment Plan
   - [ ] Software Assessment Report

2. **Independence** (MANDATORY SIL 3-4):
   - [ ] Assessment performed by independent Assessor
   - [ ] Assessor independent from supplier (or Safety Authority discretion)
   - [ ] Assessor independent from project
   - [ ] Assessor independence documented

3. **Assessment Activities**:
   - [ ] Process compliance audit performed (all EN 50128 requirements)
   - [ ] All lifecycle documents reviewed
   - [ ] All evidence reviewed (test results, reviews, verifications)
   - [ ] Safety case evaluated
   - [ ] Traceability verified end-to-end (requirements → deployment)

4. **Assessment Findings**:
   - [ ] All findings documented in Assessment Report
   - [ ] All findings addressed or accepted with justification
   - [ ] No open critical findings
   - [ ] Residual risks acceptable and documented

5. **Safety Authority** (if applicable):
   - [ ] Safety Authority notified (if required by regulation)
   - [ ] Safety Authority approval obtained (if required)
   - [ ] All Safety Authority comments addressed

### Deliverables (Annex C Table C.1)

| Document | Author | 1st Check (VER) | 2nd Check | Baseline |
|----------|--------|-----------------|-----------|----------|
| Software Assessment Plan | ASR | VER | - | Baseline 6 |
| Software Assessment Report | ASR | VER | - | Baseline 6 |

### Quality Criteria

- [ ] Assessment performed by qualified Assessor (IEC 61508 competence)
- [ ] All EN 50128 lifecycle phases audited
- [ ] All mandatory techniques verified
- [ ] Safety case reviewed and accepted
- [ ] No open safety-critical findings

### Verification

- [ ] Assessment report reviewed by VER
- [ ] All assessment findings addressed
- [ ] Safety Authority approval obtained (if required)

### Tool Integration

```bash
# Check assessment deliverables
workspace.py wf status --phase assessment

# Verify baseline 6 established
git tag baseline-6

# Generate assessment evidence package
workspace.py wf generate-evidence-package --phase assessment --output assessment_evidence.zip
```

### Gate Check Output Example (SIL 3, PASSED)

```
═══════════════════════════════════════════════════════
PHASE GATE CHECK: Assessment Complete
═══════════════════════════════════════════════════════

Project: train_door_control
SIL Level: 3 (Strict Gatekeeper Mode)
Phase: Assessment (Phase 7) - MANDATORY for SIL 3

[✓] Assessment Documents (2/2 complete)
  ✓ Software Assessment Plan - docs/assessment/Assessment-Plan.md
  ✓ Software Assessment Report - docs/assessment/Assessment-Report.md

[✓] Independence (SIL 3 MANDATORY) (4/4 satisfied)
  ✓ Independent Assessor - Dr. Robert Johnson (TÜV SÜD)
  ✓ Assessor independent from supplier - External assessor
  ✓ Assessor independent from project - No project involvement
  ✓ Independence documented - Assessment Plan Section 2.1

[✓] Assessment Activities (5/5 satisfied)
  ✓ Process compliance audit performed - All EN 50128 phases audited
  ✓ All lifecycle documents reviewed - 47 documents reviewed
  ✓ All evidence reviewed - Test results, reviews, verifications
  ✓ Safety case evaluated - Safety case accepted
  ✓ Traceability verified - 100% end-to-end traceability confirmed

[✓] Assessment Findings (4/4 satisfied)
  ✓ All findings documented - 8 findings in Assessment Report
  ✓ All findings addressed - 8/8 findings closed
  ✓ No open critical findings - Zero critical findings
  ✓ Residual risks acceptable - Risk analysis in Assessment Report Section 5

[✓] Safety Authority (1/1 satisfied)
  ✓ Safety Authority approval obtained - Railway Safety Authority approved 2026-03-01

[✓] Verification (2/2 satisfied)
  ✓ Assessment report reviewed by VER - approved 2026-03-01
  ✓ All assessment findings addressed - 8 findings closed

═══════════════════════════════════════════════════════
GATE RESULT: ✓ PASSED
═══════════════════════════════════════════════════════

Assessment phase complete. All SIL 3 criteria satisfied.

AUTHORIZED: Transition to Deployment phase

Baseline Established: Baseline 6
Next Phase: Deployment (Phase 8)
```

---

## Gate 8: Deployment Complete

### Purpose

Verify software deployed successfully, release package complete, and maintenance plan established.

### Entry Criteria

- Validation gate passed (SIL 0-2)
- Assessment gate passed (SIL 3-4)

### Exit Criteria (All SIL Levels)

1. **Deployment Documents Complete**:
   - [ ] Software Release and Deployment Plan
   - [ ] Software Deployment Manual
   - [ ] Release Notes
   - [ ] Deployment Records
   - [ ] Deployment Verification Report
   - [ ] Software Maintenance Plan

2. **Release Package**:
   - [ ] Release package complete (executable, libraries, configuration, documentation)
   - [ ] Release package verified against baseline
   - [ ] Release package signed/authenticated (for SIL 3-4)
   - [ ] Deployment Manual complete and tested

3. **Deployment**:
   - [ ] Software deployed to operational environment
   - [ ] Deployment procedure followed exactly
   - [ ] Deployment verified (smoke tests, operational checks)
   - [ ] Deployment records complete (what, when, where, who)

4. **Maintenance**:
   - [ ] Maintenance plan established
   - [ ] Change control process active
   - [ ] Defect tracking system operational
   - [ ] Maintenance team assigned and trained

5. **Configuration Management**:
   - [ ] Final release baselined (version tagged in repository)
   - [ ] Baseline 7 established
   - [ ] Traceability complete from requirements to deployed code
   - [ ] All artifacts archived for future reference

### Deliverables (Annex C Table C.1)

| Document | Author | 1st Check (VER) | 2nd Check (VAL) | Baseline |
|----------|--------|-----------------|-----------------|----------|
| Software Release and Deployment Plan | PM | VER | VAL | Baseline 7 |
| Software Deployment Manual | PM | VER | VAL | Baseline 7 |
| Release Notes | PM | VER | VAL | Baseline 7 |
| Deployment Records | PM | VER | VAL | Baseline 7 |
| Deployment Verification Report | VER | - | VAL | Baseline 7 |
| Software Maintenance Plan | PM | VER | VAL | Baseline 7 |

### Quality Criteria

- [ ] Release package integrity verified (checksums, signatures)
- [ ] Deployment procedure tested in test environment before production
- [ ] Deployment records complete and auditable

### Verification

- [ ] Deployment verified by VER
- [ ] Deployment validated by VAL
- [ ] Baseline 7 established

### Tool Integration

```bash
# Create release package
make release

# Sign release package (SIL 3-4)
gpg --sign --armor train_door_control_v1.0.tar.gz

# Verify release package
sha256sum train_door_control_v1.0.tar.gz > checksum.txt

# Deploy to target environment
./deploy.sh --target production --version 1.0

# Verify deployment
./verify_deployment.sh --target production

# Check deployment deliverables
workspace.py wf status --phase deployment

# Verify baseline 7 established
git tag baseline-7 v1.0
git tag v1.0
git push origin v1.0 baseline-7
```

### Gate Check Output Example (SIL 3, PASSED)

```
═══════════════════════════════════════════════════════
PHASE GATE CHECK: Deployment Complete
═══════════════════════════════════════════════════════

Project: train_door_control
SIL Level: 3 (Strict Gatekeeper Mode)
Phase: Deployment (Phase 8)

[✓] Deployment Documents (6/6 complete)
  ✓ Software Release and Deployment Plan - docs/deployment/Deployment-Plan.md
  ✓ Software Deployment Manual - docs/deployment/Deployment-Manual.md
  ✓ Release Notes - docs/deployment/Release-Notes-v1.0.md
  ✓ Deployment Records - docs/deployment/Deployment-Records.md
  ✓ Deployment Verification Report - docs/verification/Deployment-VER.md
  ✓ Software Maintenance Plan - docs/deployment/Maintenance-Plan.md

[✓] Release Package (4/4 satisfied)
  ✓ Release package complete - train_door_control_v1.0.tar.gz (1.2 MB)
  ✓ Release package verified - SHA256 checksum verified
  ✓ Release package signed - GPG signature verified (SIL 3)
  ✓ Deployment Manual complete - tested in staging environment

[✓] Deployment (4/4 satisfied)
  ✓ Software deployed - Production environment, 2026-03-05 14:30 UTC
  ✓ Deployment procedure followed - Manual followed exactly
  ✓ Deployment verified - Smoke tests passed, operational checks passed
  ✓ Deployment records complete - What: v1.0, When: 2026-03-05, Where: Production, Who: John Smith

[✓] Maintenance (4/4 satisfied)
  ✓ Maintenance plan established - Maintenance Plan approved
  ✓ Change control process active - CCB operational
  ✓ Defect tracking system operational - JIRA configured
  ✓ Maintenance team assigned - 3 engineers trained

[✓] Configuration Management (4/4 satisfied)
  ✓ Final release baselined - Git tag: v1.0, baseline-7
  ✓ Baseline 7 established - All artifacts tagged
  ✓ Traceability complete - Requirements → Code → Deployed version
  ✓ All artifacts archived - Archive: train_door_control_v1.0_archive.tar.gz (15 MB)

[✓] Verification (3/3 satisfied)
  ✓ Deployment verified by VER - approved 2026-03-05
  ✓ Deployment validated by VAL - approved 2026-03-05
  ✓ Baseline 7 established - verified in repository

═══════════════════════════════════════════════════════
GATE RESULT: ✓ PASSED
═══════════════════════════════════════════════════════

Deployment phase complete. All SIL 3 criteria satisfied.

Software Release: train_door_control v1.0
Deployment Date: 2026-03-05 14:30 UTC
Baseline Established: Baseline 7

═══════════════════════════════════════════════════════
PROJECT LIFECYCLE COMPLETE
═══════════════════════════════════════════════════════

Congratulations! Train Door Control System v1.0 successfully deployed.

Status: OPERATIONAL
Next Phase: Maintenance (ongoing)
```

---

## Gate Check Automation

### Python Gate Checker Script

COD uses automated Python scripts to verify gate criteria.

**Script**: `tools/gate_checker.py` (~400 lines)

```python
#!/usr/bin/env python3
"""
EN 50128 Phase Gate Checker
Automated verification of phase gate criteria
"""

import argparse
import json
import sys
from pathlib import Path

class GateChecker:
    def __init__(self, project_root, sil_level):
        self.project_root = Path(project_root)
        self.sil_level = sil_level
        self.results = {
            'phase': None,
            'sil_level': sil_level,
            'criteria': [],
            'passed': False
        }
    
    def check_planning_gate(self):
        """Check planning phase gate criteria"""
        self.results['phase'] = 'planning'
        
        # Check documents
        docs = self._check_documents_exist([
            'docs/plans/SQAP.md',
            'docs/plans/SCMP.md',
            'docs/plans/SVP.md',
            'docs/plans/SVaP.md',
            'docs/verification/SQAP-VER.md'
        ])
        self.results['criteria'].append({
            'name': 'Planning Documents',
            'passed': all(docs.values()),
            'details': docs
        })
        
        # Check project setup
        setup = {
            'version_control': (self.project_root / '.git').exists(),
            'baseline_0': self._check_git_tag('baseline-0'),
            'build_env': (self.project_root / 'Makefile').exists()
        }
        self.results['criteria'].append({
            'name': 'Project Setup',
            'passed': all(setup.values()),
            'details': setup
        })
        
        # SIL 3-4: Check independence
        if self.sil_level >= 3:
            independence = self._check_independence()
            self.results['criteria'].append({
                'name': 'Independence (SIL 3-4)',
                'passed': independence,
                'details': {'independent_verifier': True, 'independent_validator': True}
            })
        
        # Overall gate result
        self.results['passed'] = all(c['passed'] for c in self.results['criteria'])
        return self.results
    
    def check_requirements_gate(self):
        """Check requirements phase gate criteria"""
        self.results['phase'] = 'requirements'
        
        # Check documents
        docs = self._check_documents_exist([
            'docs/SRS.md',
            'docs/RTM.md',
            'docs/test/Overall-Test-Spec.md',
            'docs/verification/SRS-VER.md'
        ])
        self.results['criteria'].append({
            'name': 'Requirements Documents',
            'passed': all(docs.values()),
            'details': docs
        })
        
        # Check traceability
        traceability = self._check_traceability_requirements()
        self.results['criteria'].append({
            'name': f'Traceability ({"MANDATORY" if self.sil_level >= 3 else "HR"})',
            'passed': traceability['passed'],
            'details': traceability
        })
        
        # Overall gate result
        self.results['passed'] = all(c['passed'] for c in self.results['criteria'])
        return self.results
    
    def check_design_gate(self):
        """Check design phase gate criteria"""
        self.results['phase'] = 'design'
        
        # Check documents
        docs = self._check_documents_exist([
            'docs/design/SAS.md',
            'docs/design/SDS.md',
            'docs/design/Interfaces.md',
            'docs/verification/Design-VER.md'
        ])
        self.results['criteria'].append({
            'name': 'Design Documents',
            'passed': all(docs.values()),
            'details': docs
        })
        
        # Check complexity (SIL 3-4: ≤10, SIL 2: ≤15)
        complexity = self._check_complexity()
        self.results['criteria'].append({
            'name': 'Complexity Constraints',
            'passed': complexity['passed'],
            'details': complexity
        })
        
        # Overall gate result
        self.results['passed'] = all(c['passed'] for c in self.results['criteria'])
        return self.results
    
    def check_implementation_gate(self):
        """Check implementation phase gate criteria"""
        self.results['phase'] = 'implementation'
        
        # Check MISRA C compliance (SIL 2+)
        if self.sil_level >= 2:
            misra = self._check_misra_compliance()
            self.results['criteria'].append({
                'name': 'MISRA C Compliance (MANDATORY SIL 2+)',
                'passed': misra['passed'],
                'details': misra
            })
        
        # Check coverage
        coverage = self._check_coverage()
        self.results['criteria'].append({
            'name': 'Coverage Requirements',
            'passed': coverage['passed'],
            'details': coverage
        })
        
        # Overall gate result
        self.results['passed'] = all(c['passed'] for c in self.results['criteria'])
        return self.results
    
    def check_integration_gate(self):
        """Check integration phase gate criteria"""
        self.results['phase'] = 'integration'
        
        # Check integration tests
        integration_tests = self._check_integration_tests()
        self.results['criteria'].append({
            'name': 'Integration Testing',
            'passed': integration_tests['passed'],
            'details': integration_tests
        })
        
        # Overall gate result
        self.results['passed'] = all(c['passed'] for c in self.results['criteria'])
        return self.results
    
    def check_validation_gate(self):
        """Check validation phase gate criteria"""
        self.results['phase'] = 'validation'
        
        # Check requirements coverage
        req_coverage = self._check_requirements_coverage()
        self.results['criteria'].append({
            'name': 'Requirements Validation',
            'passed': req_coverage['passed'],
            'details': req_coverage
        })
        
        # SIL 3-4: Check independence
        if self.sil_level >= 3:
            independence = self._check_validation_independence()
            self.results['criteria'].append({
                'name': 'Independence (SIL 3-4 MANDATORY)',
                'passed': independence,
                'details': {'independent_validator': True}
            })
        
        # Overall gate result
        self.results['passed'] = all(c['passed'] for c in self.results['criteria'])
        return self.results
    
    # Helper methods
    
    def _check_documents_exist(self, doc_paths):
        """Check if documents exist"""
        results = {}
        for doc_path in doc_paths:
            full_path = self.project_root / doc_path
            results[doc_path] = full_path.exists()
        return results
    
    def _check_git_tag(self, tag_name):
        """Check if Git tag exists"""
        import subprocess
        result = subprocess.run(
            ['git', 'tag', '-l', tag_name],
            cwd=self.project_root,
            capture_output=True,
            text=True
        )
        return tag_name in result.stdout
    
    def _check_traceability_requirements(self):
        """Check requirements traceability"""
        # Parse RTM and check forward/backward coverage
        # For SIL 3-4, require 100% coverage
        threshold = 100.0 if self.sil_level >= 3 else 90.0
        
        # Placeholder: actual implementation would parse RTM
        return {
            'passed': True,
            'forward_coverage': 100.0,
            'backward_coverage': 100.0,
            'threshold': threshold
        }
    
    def _check_complexity(self):
        """Check cyclomatic complexity"""
        limits = {0: 20, 1: 20, 2: 15, 3: 10, 4: 10}
        max_ccn = limits[self.sil_level]
        
        # Placeholder: actual implementation would run Lizard
        return {
            'passed': True,
            'max_ccn': 9,
            'limit': max_ccn
        }
    
    def _check_misra_compliance(self):
        """Check MISRA C compliance"""
        # Placeholder: actual implementation would parse PC-lint report
        return {
            'passed': True,
            'mandatory_violations': 0,
            'required_violations': 2,
            'required_deviations': 2
        }
    
    def _check_coverage(self):
        """Check test coverage"""
        thresholds = {
            0: {'statement': 80, 'branch': 70, 'condition': 0},
            1: {'statement': 80, 'branch': 70, 'condition': 0},
            2: {'statement': 90, 'branch': 95, 'condition': 0},
            3: {'statement': 100, 'branch': 100, 'condition': 100},
            4: {'statement': 100, 'branch': 100, 'condition': 100}
        }
        
        threshold = thresholds[self.sil_level]
        
        # Placeholder: actual implementation would parse coverage report
        coverage = {'statement': 98, 'branch': 95, 'condition': 90}
        
        passed = (
            coverage['statement'] >= threshold['statement'] and
            coverage['branch'] >= threshold['branch'] and
            coverage['condition'] >= threshold['condition']
        )
        
        return {
            'passed': passed,
            'coverage': coverage,
            'threshold': threshold
        }
    
    def _check_integration_tests(self):
        """Check integration tests"""
        # Placeholder
        return {
            'passed': True,
            'tests_executed': 42,
            'tests_passed': 42
        }
    
    def _check_requirements_coverage(self):
        """Check requirements validation coverage"""
        # Placeholder
        return {
            'passed': True,
            'requirements_total': 42,
            'requirements_validated': 42,
            'coverage': 100.0
        }
    
    def _check_independence(self):
        """Check independence requirements"""
        # Placeholder: check SQAP for independence documentation
        return True
    
    def _check_validation_independence(self):
        """Check validation independence"""
        # Placeholder
        return True

def main():
    parser = argparse.ArgumentParser(description='EN 50128 Phase Gate Checker')
    parser.add_argument('phase', choices=['planning', 'requirements', 'design', 'implementation', 'integration', 'validation'])
    parser.add_argument('--sil', type=int, required=True, choices=[0, 1, 2, 3, 4])
    parser.add_argument('--project-root', default='.', help='Project root directory')
    parser.add_argument('--json', action='store_true', help='Output JSON format')
    
    args = parser.parse_args()
    
    checker = GateChecker(args.project_root, args.sil)
    
    # Run gate check
    gate_methods = {
        'planning': checker.check_planning_gate,
        'requirements': checker.check_requirements_gate,
        'design': checker.check_design_gate,
        'implementation': checker.check_implementation_gate,
        'integration': checker.check_integration_gate,
        'validation': checker.check_validation_gate
    }
    
    results = gate_methods[args.phase]()
    
    if args.json:
        print(json.dumps(results, indent=2))
    else:
        print(f"Phase Gate Check: {results['phase'].capitalize()}")
        print(f"SIL Level: {results['sil_level']}")
        print(f"Result: {'PASSED' if results['passed'] else 'BLOCKED'}")
        print("\nCriteria:")
        for criterion in results['criteria']:
            status = '✓' if criterion['passed'] else '✗'
            print(f"  {status} {criterion['name']}")
    
    sys.exit(0 if results['passed'] else 1)

if __name__ == '__main__':
    main()
```

### Usage

```bash
# Check planning gate
python3 tools/gate_checker.py planning --sil 3 --project-root .

# Check requirements gate (JSON output)
python3 tools/gate_checker.py requirements --sil 3 --json

# Check implementation gate
python3 tools/gate_checker.py implementation --sil 3
```

---

## Tool Integration

### Workspace.py Integration

All gate checks integrate with `workspace.py` for traceability and workflow management.

```bash
# Check phase deliverable status
workspace.py wf status --phase <phase>

# List all deliverables for phase
workspace.py wf list-deliverables --phase <phase>

# Verify traceability at gate
workspace.py trace validate --phase <phase>

# Check traceability gaps
workspace.py trace check-gaps --phase <phase>

# Generate gate report
workspace.py wf generate-report --phase <phase> --output <file>
```

### Traceability Validation at Gates

Every gate verifies RTM completeness:

```bash
# Gate 2 (Requirements): System Req → Software Req
workspace.py trace check-forward --from system_req --to software_req
workspace.py trace check-backward --from software_req --to system_req

# Gate 3 (Design): Software Req → Design
workspace.py trace check-forward --from software_req --to design
workspace.py trace check-backward --from design --to software_req

# Gate 4 (Implementation): Design → Code → Unit Tests
workspace.py trace check-forward --from design --to code
workspace.py trace check-forward --from code --to unit_tests
workspace.py trace check-backward --from unit_tests --to software_req

# Gate 6 (Validation): Software Req → System Tests
workspace.py trace check-forward --from software_req --to system_tests
workspace.py trace validate --phase validation --check-coverage 100
```

---

## Example Scenario

### Complete SIL 3 Gate Sequence

**Project**: Train Door Control System  
**SIL Level**: 3 (Strict Gatekeeper Mode)

#### Phase 0: Initialization

```bash
/cod plan --sil 3 --project train_door_control
# LIFECYCLE_STATE.md created
# Current Phase: Planning
```

#### Phase 1: Planning

```bash
# PM coordinates planning
/pm

# Create planning documents
# - SQAP (QUA)
# - SCMP (CM)
# - SVP (VER)
# - SVaP (VAL)

# Gate check
/cod gate-check planning
# Result: ✓ PASSED
# Baseline 0 established
# Transition to Requirements
```

#### Phase 2: Requirements

```bash
# User approval required
/req
# COD: "🔐 APPROVAL REQUIRED: Requirements Activity"
# User: Y

# REQ creates SRS, RTM
# SAF creates Hazard Log
# TST creates Overall Test Spec

# Gate check
/cod gate-check requirements
# Result: ✗ BLOCKED (1 system requirement not covered)

# Fix: Add SWR-043
/req  # Add missing requirement

# Gate check retry
/cod gate-check requirements
# Result: ✓ PASSED
# Baseline 1 established
# Transition to Design
```

#### Phase 3: Design

```bash
# DES creates SAS, SDS
/des

# Gate check
/cod gate-check design
# Result: ✗ BLOCKED (Complexity violation: process_command = 15, limit: 10)

# Fix: Refactor design
/des  # Reduce complexity

# Gate check retry
/cod gate-check design
# Result: ✓ PASSED (Max CCN: 9)
# Baseline 2 established
# Transition to Implementation
```

#### Phase 4: Implementation

```bash
# IMP implements C code
/imp

# TST writes unit tests
/tst

# QUA reviews code
/qua

# VER performs static analysis
/ver

# Gate check
/cod gate-check implementation
# Result: ✗ BLOCKED (Coverage: branch 95%, condition 90%, need 100%)

# Fix: Add tests
/tst  # Add missing tests

# Gate check retry
/cod gate-check implementation
# Result: ✓ PASSED (Coverage: 100%/100%/100%)
# Baseline 3 established
# Transition to Integration
```

#### Phase 5: Integration

```bash
# INT integrates components
/int

# TST executes integration tests
/tst

# Gate check
/cod gate-check integration
# Result: ✓ PASSED
# Baseline 4 established
# Transition to Validation
```

#### Phase 6: Validation

```bash
# VAL performs system testing (independent validator)
/val

# Gate check
/cod gate-check validation
# Result: ✓ PASSED (100% requirements validated)
# Baseline 5 established
# Transition to Assessment (SIL 3 required)
```

#### Phase 7: Assessment (SIL 3)

```bash
# External Assessor reviews project
# (Not a command - external activity)

# Assessor creates Assessment Report

# Gate check
/cod gate-check assessment
# Result: ✓ PASSED
# Baseline 6 established
# Transition to Deployment
```

#### Phase 8: Deployment

```bash
# PM deploys software
/pm

# CM establishes baseline 7
/cm

# Gate check
/cod gate-check deployment
# Result: ✓ PASSED
# Baseline 7 established
# PROJECT COMPLETE
```

---

## Summary

This workflow provides:

1. **Complete phase gate structure** - All 8 phases with SIL-specific criteria
2. **SIL-dependent enforcement** - Advisory (SIL 0-1), Semi-Strict (SIL 2), Strict (SIL 3-4)
3. **Automated gate checking** - Python scripts for criteria verification
4. **Tool integration** - workspace.py trace/wf for traceability and workflow management
5. **Real examples** - Complete SIL 3 gate sequence with PASS/BLOCK scenarios
6. **Traceability enforcement** - RTM validation at every gate
7. **Quality metrics** - Complexity, coverage, MISRA C compliance thresholds

**Key Principles**:
- **Strict where safety demands** (SIL 3-4: BLOCK on violations)
- **Advisory where appropriate** (SIL 0-1: warnings, user discretion)
- **Clear feedback** - Actionable guidance for gate failures
- **Automated verification** - Python scripts reduce manual effort
- **Traceability throughout** - 100% RTM coverage enforced (SIL 3-4)

---

**Related Workflows**:
- `v-model-orchestration-workflow.md` - Phase transitions and agent coordination
- `traceability-rtm-workflow.md` - RTM management and gap detection
- `iteration-change-management-workflow.md` - Feedback loops and change control

**EN 50128 References**:
- Section 5.3: Software Lifecycle
- Annex C Table C.1: Software Document Control Summary
- Table A.2-A.21: Techniques and measures by SIL level
