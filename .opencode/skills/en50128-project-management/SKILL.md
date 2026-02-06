---
name: en50128-project-management
description: Project management and coordination for EN 50128 railway software development
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  phase: all-phases
  focus: coordination
---

## What I do

I provide project management guidance for EN 50128 railway software projects:
- Organizational structure and role assignment per SIL level
- Independence requirements enforcement (critical for SIL 3-4)
- Lifecycle planning and phase management
- Coordination across development, verification, and validation roles
- Stakeholder management (Validator, Assessor, Customer, Safety Authority)
- Resource planning and schedule management

## When to use me

Use this skill when:
- Setting up EN 50128 project organization
- Assigning personnel to roles
- Ensuring independence requirements are met
- Planning software development lifecycle
- Coordinating between roles (Designer, Implementer, Tester, etc.)
- Managing interface with Validator and Assessor
- Planning project phases and activities
- Resolving cross-role issues

## Critical Independence Requirements (EN 50128 Section 5.1.2)

### Validator Independence (MANDATORY SIL 3-4)

**EN 50128 Section 5.1.2.10.f:**
> "Validator shall not report to the Project Manager i.e. the Project Manager shall have no influence on the validator's decisions but the validator informs the Project Manager about his decisions."

**Key Points:**
- Validator is **organizationally independent** from Project Manager
- PM has **NO influence** on Validator decisions
- Validator **informs** PM (information flow only, not authority)
- Validator gives **agreement/disagreement for software release** (Section 5.1.2.8)

```
CORRECT (SIL 3-4):
    Safety Authority / Customer
              |
         ┌────┴────┐
         |         |
    Validator  Project Manager
         |         |
         |    ┌────┴─────────┐
         |    |              |
         |  Designer    Implementer
         |
    (Independent)

INCORRECT (SIL 3-4):
    Project Manager
         |
    ┌────┴─────┐
    |          |
  Validator  Designer
    
(Validator cannot report to PM!)
```

### Assessor Independence (MANDATORY ALL SILs)

**EN 50128 Section 5.1.2.4-7:**
- Assessor appointed by supplier, customer, or Safety Authority
- **Independent from supplier** (or at Safety Authority discretion)
- **Independent from project**
- **Organizationally independent** from all roles

### Verifier Independence (MANDATORY SIL 3-4)

**EN 50128 Section 5.1.2.10.i:**
> "A person who is Verifier shall neither be Requirements Manager, Designer, Implementer, Integrator, Tester nor Validator."

- Verifier **CAN report to PM OR Validator** (project decision)
- Verifier **CANNOT** be developer/tester of same component
- Independence from all development roles for same component

## Organizational Structures by SIL

### SIL 3-4 Organization (Strict Independence)

```
Safety Authority / Customer
         |
    ┌────┴─────┐
    |          |
Assessor   Organization
           (Independent)
           
Organization Structure:
├── Project Manager (PM)
│   ├── Requirements Manager
│   ├── Designer
│   ├── Implementer
│   ├── [Optionally: Integrator, Tester, Verifier]
│   └── Configuration Manager
│
└── Validator (INDEPENDENT - does NOT report to PM)
    ├── [Optionally: Integrator, Tester, Verifier]
    └── Validation Team
```

**Key Rules (Section 5.1.2.10):**

| Role Combination | Allowed? | Constraints |
|------------------|----------|-------------|
| Designer + Implementer (same component) | ✅ YES | Can be same person |
| Implementer + Tester (same component) | ❌ NO | Must be different |
| Designer + Verifier (same component) | ❌ NO | Must be different |
| Integrator + Tester | ✅ YES | Can be same person |
| PM + Designer | ✅ YES | If independence satisfied |
| PM + Validator | ❌ NO | Never allowed |
| Any role + Assessor | ❌ NO | Assessor always independent |

### SIL 0-2 Organization (Relaxed)

**EN 50128 Section 5.1.2.11-12:**
- PM, Requirements Manager, Designer, Implementer, Integrator, Tester, Verifier, and Validator **CAN all be the same person**
- **Assessor must still be independent**
- Document all role combinations
- Recommend some separation even for SIL 0-2

```
SIL 0-2 (Simplified):
    Project Manager
         |
    (May perform multiple roles)
         |
    ┌────┴─────┬─────────┬────────┐
    |          |         |        |
Designer  Implementer  Tester  Verifier
         |
    Validator (may be same person as PM)
    
Assessor (ALWAYS INDEPENDENT)
```

## Role Assignment Process

### Step 1: Determine SIL Level

```markdown
# SIL Determination Document

**Project:** Railway Signaling System - Track Circuit Monitor
**Hazard Analysis Reference:** HAZ-2026-001
**System Safety Requirements:** SRS-SYS-001

## SIL Assignment:
- **Software SIL Level:** SIL 3
- **Justification:** Controls safety-critical track circuit monitoring; 
  failure could lead to train collision (catastrophic)
- **RAMS Reference:** EN 50126:2017 risk analysis

## Independence Requirements (EN 50128 Section 5.1.2):
Based on SIL 3, the following independence requirements apply:
- Validator SHALL NOT report to Project Manager
- Verifier independent from Designer/Implementer of same component
- Integrator/Tester independent from Designer/Implementer of same component
- Assessor independent from all project roles
```

### Step 2: Define Organizational Structure

```markdown
# Organizational Structure - SIL 3 Project

## Reporting Structure:

### Executive Level:
- **Safety Authority:** Railway Safety Authority
- **Customer:** Railway Operator Co.

### Project Organization:

**Independent Assessor:**
- Name: [Assessor Name]
- Organization: Independent Safety Assessor Ltd.
- Reports to: Safety Authority
- **Independence:** Organizationally independent from supplier

**Validator (INDEPENDENT):**
- Name: [Validator Name]
- Reports to: Quality Director (NOT Project Manager)
- Team: 2 validation engineers
- **Independence:** Does NOT report to PM; informational relationship only

**Project Manager:**
- Name: [PM Name]
- Reports to: Engineering Director
- Responsibilities: Overall project coordination, schedule, resources

**Development Team (Reports to PM):**
- Requirements Manager: [Name]
- Designer: [Name] (different person from Implementer for critical modules)
- Implementer: [Name1], [Name2]
- Configuration Manager: [Name]

**Quality Team (May report to PM OR Validator):**
- Verifier: [Name] (independent from developers)
- Integrator: [Name] (may be same as Tester)
- Tester: [Name]

## Independence Verification:
- [ ] Validator does NOT report to PM ✓
- [ ] Assessor is organizationally independent ✓
- [ ] Verifier is not Designer/Implementer/Tester of same component ✓
- [ ] Integrator/Tester not Designer/Implementer of same component ✓
```

### Step 3: Document Role Assignments (EN 50128 Section 5.1.2.3)

**Requirement:** "Personnel assigned to roles shall be named and recorded"

```markdown
# Role Assignment Record

**Project:** Track Circuit Monitor Software
**SIL Level:** 3
**Date:** 2026-02-06
**Version:** 1.0

| Role | Person Name | Qualifications | Start Date | Also Performs |
|------|-------------|----------------|------------|---------------|
| Project Manager | John Smith | PMP, 10 yrs railway | 2026-01-01 | - |
| Requirements Mgr | Jane Doe | 5 yrs railway SW | 2026-01-15 | - |
| Designer | Bob Johnson | 8 yrs embedded SW | 2026-01-15 | (Designer only) |
| Implementer A | Alice Chen | 6 yrs C, MISRA C | 2026-02-01 | (Implementer only) |
| Implementer B | Mike Brown | 7 yrs C, MISRA C | 2026-02-01 | (Implementer only) |
| Integrator | Sarah Wilson | 5 yrs integration | 2026-03-01 | Tester |
| Tester | Sarah Wilson | 5 yrs testing | 2026-03-01 | Integrator |
| Verifier | David Lee | 10 yrs verification | 2026-01-15 | - |
| Config Manager | Emma Davis | 8 yrs CM | 2026-01-15 | - |
| **Validator** | **Tom Anderson** | **12 yrs validation** | **2026-01-15** | **INDEPENDENT** |
| **Assessor** | **Safety Assess Ltd** | **EN 50128 certified** | **2026-01-15** | **INDEPENDENT** |

## Independence Justification:
- Validator reports to Quality Director, NOT PM
- Assessor from independent company
- Verifier (David Lee) is not Designer/Implementer/Tester
- Integrator/Tester (Sarah Wilson) is not Designer/Implementer
- Bob Johnson (Designer) does not perform implementation for critical modules
```

## Lifecycle Planning (EN 50128 Section 5.3)

### Lifecycle Model Selection (Section 5.3.2.1)

**EN 50128:** "A lifecycle model shall be selected and detailed"

**Common Models for Railway Software:**

1. **V-Model** (Most Common for EN 50128)
   - Clear phase gates
   - Strong verification/validation
   - Good traceability
   - Recommended for SIL 2+

2. **Iterative with V-Model per iteration**
   - Multiple V-model cycles
   - Each iteration adds functionality
   - Good for complex systems

3. **Incremental Development**
   - Core system first
   - Add features incrementally
   - Each increment follows V-model

**Document in Software Management Plan:**

```markdown
# Lifecycle Model - V-Model with Iterations

## Phase Structure:
1. Requirements Specification
2. Architecture & Design
3. Component Design
4. Implementation & Unit Testing
5. Integration & Integration Testing
6. System Testing / Validation
7. Deployment

## Iteration Strategy:
- **Iteration 1 (3 months):** Core track circuit monitoring
- **Iteration 2 (2 months):** Communication interface
- **Iteration 3 (2 months):** Diagnostic features

## Quality Assurance:
- QA activities run in parallel with all phases (Section 5.3.2.3)
- Independent verification at each phase gate
- Independent validation before release

## Phase Gate Criteria:
Each phase requires:
- All deliverables complete
- Verification report approved
- All defects resolved or deferred with rationale
- Traceability updated (MANDATORY SIL 3+)
```

### Activity Planning (Section 5.3.2.5)

**Requirement:** "All activities to be performed during a phase shall be defined and planned prior to commencement"

```markdown
# Phase Activities - Implementation Phase

## Pre-Phase Requirements:
- Software Design Specification (SDS) complete and verified
- MISRA C:2012 environment configured
- Unit test framework (Unity) set up
- Static analysis tools qualified (PC-lint Plus)

## Activities:

### Week 1-2: Module A (Track Circuit Interface)
- **Implementer:** Alice Chen
- **Activities:**
  1. Implement track_circuit_driver.c/h
  2. Write unit tests (test_track_circuit_driver.c)
  3. Self-review against MISRA C checklist
  4. Run static analysis (PC-lint)
  5. Execute unit tests (target 100% branch coverage)
- **Deliverables:** Source code, unit test report
- **Exit Criteria:** All tests pass, 100% branch coverage, MISRA C clean

### Week 3-4: Module B (Data Processing)
- **Implementer:** Mike Brown
- **Activities:**
  1. Implement data_processor.c/h
  2. Write unit tests
  3. MISRA C verification
  4. Static analysis
  5. Unit testing
- **Deliverables:** Source code, unit test report

### Week 5: Code Review (Quality Assurance)
- **Reviewer:** Verifier (David Lee)
- **Activities:**
  1. Review all source code
  2. Verify MISRA C compliance
  3. Verify defensive programming
  4. Verify complexity ≤ 10 (SIL 3)
  5. Verify traceability to design
- **Deliverables:** Code Review Report
- **Exit Criteria:** No critical defects, all HR recommendations addressed

### Week 6: Integration Preparation
- **Integrator:** Sarah Wilson
- **Activities:**
  1. Review integration test specification
  2. Set up integration test environment
  3. Prepare integration test harness
- **Deliverables:** Integration test environment ready

## Resources:
- 2 Implementers (full-time)
- 1 Verifier (50% allocation)
- PC-lint Plus licenses (2)
- Target hardware (2 units)

## Dependencies:
- Design Specification complete (predecessor)
- Test environment available (external)

## Risks:
- Hardware availability delay → Mitigation: Simulator available
- MISRA C compliance issues → Mitigation: Training completed, lint configured
```

## Coordination Activities

### Daily/Weekly Coordination

```markdown
# Weekly Project Coordination Meeting

**Attendees:** PM, Requirements Manager, Designer, Implementer leads, 
              Configuration Manager

**Agenda:**
1. Status review (each role)
2. Issues and blockers
3. Dependencies and handoffs
4. Risk review
5. Schedule status

**Information Sharing with Validator:**
- PM provides status update to Validator (information only)
- Validator provides feedback on validation planning
- **Note:** PM does NOT direct Validator activities

**Assessor Coordination:**
- Provide documentation as requested
- Schedule assessment reviews
- Address assessment findings
```

### Phase Gate Reviews

```markdown
# Phase Gate Review - Design Phase Complete

**Date:** 2026-03-15
**Phase:** Design → Implementation transition
**SIL:** 3

## Deliverables Review:
- [ ] Software Architecture Specification (SAS) - Complete
- [ ] Software Design Specification (SDS) - Complete  
- [ ] Interface Specifications - Complete
- [ ] Integration Test Specification - Complete
- [ ] Design Verification Report - Complete (Verifier approved)

## Quality Gate Criteria:
- [ ] All design documents reviewed and approved
- [ ] Traceability matrix updated (requirements → design) - MANDATORY SIL 3
- [ ] Architectural review passed
- [ ] Complexity analysis: All functions ≤ 10 cyclomatic complexity
- [ ] MISRA C design patterns verified
- [ ] No critical defects open

## Validator Input:
- Validator reviewed design documents
- Validator approves proceeding to implementation
- **Note:** Validator makes independent assessment

## Assessor Status:
- Design documents provided to Assessor
- Awaiting assessment report

## Decision: PROCEED to Implementation Phase
**Approved by:**
- Project Manager: [Signature]
- Validator: [Signature] (independent approval)
```

## Stakeholder Management

### Validator Relationship (Critical for SIL 3-4)

**DO:**
- ✅ Provide information when requested
- ✅ Inform Validator of project status
- ✅ Receive Validator feedback and decisions
- ✅ Support Validator activities (provide access, documentation)

**DON'T:**
- ❌ Direct Validator activities
- ❌ Influence Validator decisions
- ❌ Withhold information from Validator
- ❌ Pressure Validator for approvals

**Communication Protocol:**

```markdown
# PM - Validator Communication Protocol

## Regular Updates (Weekly):
**From PM to Validator:**
- Project status summary
- Phase completion status
- Issues that may affect validation
- Schedule updates

**From Validator to PM:**
- Validation planning status
- Test environment needs
- Documentation requests
- Validation findings (informational)

## Release Decision:
**Validator Authority (EN 50128 Section 5.1.2.8):**
- Validator gives agreement/disagreement for software release
- PM does NOT override Validator decision
- If Validator disagrees: address concerns, re-validate

## Escalation:
- If disagreement on release: Escalate to Safety Authority
- PM provides facts, Validator provides assessment
- Safety Authority makes final decision
```

### Assessor Relationship

```markdown
# Assessor Coordination

## Assessment Planning:
- Assessor defines assessment plan
- PM provides requested documentation
- PM coordinates access to personnel/facilities

## Assessment Execution:
- Assessor conducts independent assessment
- PM responds to findings
- PM tracks corrective actions

## Assessment Findings:
- Assessor reports findings to Safety Authority/Customer
- PM receives copy of assessment report
- PM develops corrective action plan
- PM implements corrections
- Assessor verifies corrections

## Documentation Requests:
Assessor may request:
- All phase deliverables (SRS, SAS, SDS, code, test reports)
- Verification reports
- Traceability matrices
- Process records (meeting minutes, reviews)
- Tool qualification records
```

## Project Planning Checklist

### Project Initiation:
- [ ] SIL level determined and documented
- [ ] Organizational structure defined (with independence)
- [ ] All roles assigned to named personnel (Section 5.1.2.3)
- [ ] Independence requirements verified
- [ ] Assessor appointed (Section 5.1.2.4)
- [ ] Validator independence established (Section 5.1.2.10.f for SIL 3-4)
- [ ] Lifecycle model selected and documented (Section 5.3.2.1)

### Planning Documents:
- [ ] Software Management Plan
- [ ] Software Quality Assurance Plan (SQAP)
- [ ] Software Configuration Management Plan (SCMP)
- [ ] Software Verification Plan (SVP)
- [ ] Software Validation Plan (SVaP)
- [ ] All plans reviewed and approved

### Phase Planning:
- [ ] All phase activities defined (Section 5.3.2.5)
- [ ] Resources allocated
- [ ] Schedule developed
- [ ] Dependencies identified
- [ ] Entry/exit criteria defined for each phase

### Ongoing:
- [ ] Regular coordination meetings
- [ ] Validator informed of project status
- [ ] Assessor provided requested documentation
- [ ] Traceability maintained (MANDATORY SIL 3-4)
- [ ] Configuration management active
- [ ] Issues tracked and resolved

## Standard References

- **EN 50128:2011 Section 5** (Management and Organisation) - `std/EN50128-2011.md` lines 1116-1370
- **EN 50128:2011 Section 5.1.2** (Independence Requirements) - `std/EN50128-2011.md` lines 1125-1248
- **EN 50128:2011 Section 5.3** (Lifecycle) - `std/EN50128-2011.md` lines 1304-1365
- **EN 50128:2011 Table B.9** (Project Manager Role) - `std/EN50128-2011.md` Annex B
- **EN 50128 Abbreviations** - `std/EN50128-ABBREVIATIONS.md`

## Related Skills

- `en50128-quality` - Quality assurance planning
- `en50128-configuration` - Configuration management
- `en50128-requirements` - Requirements management
- `en50128-documentation` - Document templates and standards
