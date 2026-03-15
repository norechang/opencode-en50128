# EN 50128 Deliverable-Centric Platform Design

## Document Information

| Property | Value |
|----------|-------|
| **Purpose** | Conceptual design for deliverable-centric EN 50128 platform |
| **Focus** | Mandatory deliverables with complete evidence per EN 50128 Annex C Table C.1 |
| **Approach** | Evidence-first, agent-orchestrated, SIL-aware automated generation |
| **Date** | 2026-03-09 |
| **Status** | Conceptual Design - Step 1 |

---

## Executive Summary

**Core Insight**: EN 50128 compliance is NOT about following processes - it's about **producing mandatory deliverables with complete evidence** that satisfy the standard's requirements.

**Platform Goal**: Automate the generation of all 46 EN 50128 mandatory deliverables (Table C.1) with complete traceability, evidence, and SIL-appropriate verification/validation, leveraging an agent-based system.

**Key Principle**: **"Deliverable-First, Evidence-Complete, Agent-Orchestrated"**

---

## 1. Conceptual Foundation

### 1.1 The Deliverable-Centric Paradigm Shift

**Traditional Approach (Process-Centric)**:
```
User Request → Agent Activities → Hopefully Correct Documents
```
**Problems**:
- Agents focus on "doing activities"
- Deliverables are byproducts
- Evidence collection is afterthought
- Compliance verification happens late
- Gaps discovered during assessment

**Deliverable-Centric Approach**:
```
User Request → Deliverable Requirements → Agent Evidence Generation → Complete Deliverable
```
**Benefits**:
- Every action generates evidence
- Deliverables are primary outputs
- Compliance built-in from start
- Real-time completeness tracking
- Automatic traceability

### 1.2 Core Concepts

#### A. Deliverable as First-Class Entity

Every EN 50128 deliverable is a **structured artifact** with:
1. **Template** - EN 50128-compliant structure (from Annex C)
2. **Content Requirements** - What must be documented (from standard sections)
3. **Evidence Requirements** - What must be proven (technique tables A.2-A.21)
4. **Verification Criteria** - How to check completeness and correctness
5. **Traceability Links** - Connections to other deliverables
6. **SIL-Dependent Rules** - What's mandatory/highly recommended/recommended

#### B. Evidence as Core Currency

Evidence types:
1. **Requirement Evidence**: Requirements → Traceability Matrix
2. **Design Evidence**: Architecture → Design Specs → Interface Specs
3. **Implementation Evidence**: Source Code → Static Analysis Reports → Complexity Metrics
4. **Test Evidence**: Test Plans → Test Cases → Test Results → Coverage Reports
5. **Verification Evidence**: Verification Reports → Tool Reports → Review Records
6. **Validation Evidence**: Validation Reports → Acceptance Records
7. **Configuration Evidence**: Baselines → Change Records → Audit Reports
8. **Quality Evidence**: Review Reports → QA Audits → Metrics

#### C. Agent as Evidence Generator

Each agent is responsible for:
1. **Generating** specific deliverables (as per Table C.1 "Written by" column)
2. **Collecting** evidence during work
3. **Populating** deliverable sections with evidence
4. **Ensuring** completeness per SIL level
5. **Submitting** to verification (VER checks) and validation (VAL checks)

---

## 2. EN 50128 Deliverable Mapping (Table C.1)

### 2.1 Complete Deliverable Catalog (46 Deliverables)

| # | Phase | Deliverable | Written By | 1st Check | 2nd Check | Template Exists? |
|---|-------|-------------|------------|-----------|-----------|------------------|
| **Planning Phase** |
| 1 | Planning | Software Quality Assurance Plan (SQAP) | QUA | VER | VAL | ✅ |
| 2 | Planning | Software Quality Assurance Verification Report | VER | VER | VAL | ✅ |
| 3 | Planning | Software Configuration Management Plan (SCMP) | CM | VER | VAL | ✅ |
| 4 | Planning | Software Verification Plan (SVP) | VER | - | VAL | ✅ |
| 5 | Planning | Software Validation Plan (SVaP) | VAL | VER | - | ✅ |
| **Requirements Phase** |
| 6 | Requirements | Software Requirements Specification (SRS) | REQ | VER | VAL | ✅ |
| 7 | Requirements | Overall Software Test Specification | TST | VER | VAL | ✅ |
| 8 | Requirements | Software Requirements Verification Report | VER | - | VAL | ✅ |
| **Architecture & Design Phase** |
| 9 | Architecture | Software Architecture Specification (SAS) | DES | VER | VAL | ✅ |
| 10 | Architecture | Software Design Specification (SDS) | DES | VER | VAL | ✅ |
| 11 | Architecture | Software Interface Specifications | DES | VER | VAL | ✅ |
| 12 | Architecture | Software Integration Test Specification | INT | VER | VAL | ✅ |
| 13 | Architecture | SW/HW Integration Test Specification | INT | VER | VAL | ✅ |
| 14 | Architecture | Software Architecture and Design Verification Report | VER | - | VAL | ✅ |
| **Component Design Phase** |
| 15 | Component Design | Software Component Design Specification | DES | VER | VAL | ❌ Need |
| 16 | Component Design | Software Component Test Specification | TST | VER | VAL | ✅ |
| 17 | Component Design | Software Component Design Verification Report | VER | - | - | ❌ Need |
| **Implementation & Testing Phase** |
| 18 | Implementation | Software Source Code and Supporting Documentation | IMP | VER | VAL | ❌ (Code) |
| 19 | Implementation | Software Source Code Verification Report | VER | - | VAL | ✅ |
| 20 | Testing | Software Component Test Report | TST | VER | VAL | ✅ |
| **Integration Phase** |
| 21 | Integration | Software Integration Test Report | INT | VER | VAL | ✅ |
| 22 | Integration | SW/HW Integration Test Report | INT | VER | VAL | ✅ |
| 23 | Integration | Software Integration Verification Report | VER | - | - | ✅ |
| **Validation Phase** |
| 24 | Validation | Overall Software Test Report | TST | VER | VAL | ✅ |
| 25 | Validation | Software Validation Report | VAL | VER | - | ❌ Need |
| 26 | Validation | Tools Validation Report | TBD | VER | - | ❌ Need |
| **Application Data/Algorithms (if applicable)** |
| 28 | Application | Application Requirements Specification | REQ | VER | VAL | ❌ |
| 29 | Application | Application Preparation Plan | REQ/DES | VER | VAL | ❌ |
| 30 | Application | Application Test Specification | TST | VER | VAL | ❌ |
| 31 | Application | Application Architecture and Design | DES | VER | VAL | ❌ |
| 32 | Application | Application Preparation Verification Report | VER | - | - | ❌ |
| 33 | Application | Application Test Report | TST | VER | VAL | ❌ |
| 34 | Application | Source Code of Application Data/Algorithms | DES | VER | VAL | ❌ |
| 35 | Application | Application Data/Algorithms Verification Report | VER | - | VAL | ❌ |
| **Deployment Phase** |
| 36 | Deployment | Software Release and Deployment Plan | TBD | VER | VAL | ❌ Need |
| 37 | Deployment | Software Deployment Manual | TBD | VER | VAL | ❌ Need |
| 38 | Deployment | Release Notes | TBD | VER | VAL | ✅ |
| 39 | Deployment | Deployment Records | TBD | VER | VAL | ❌ Need |
| 40 | Deployment | Deployment Verification Report | VER | - | - | ❌ Need |
| **Maintenance Phase** |
| 41 | Maintenance | Software Maintenance Plan | TBD | VER | VAL | ❌ |
| 42 | Maintenance | Software Change Records | CM | VER | VAL | ✅ |
| 43 | Maintenance | Software Maintenance Records | TBD | VER | VAL | ❌ |
| 44 | Maintenance | Software Maintenance Verification Report | VER | VER | VAL | ❌ |
| **Assessment Phase** |
| 45 | Assessment | Software Assessment Plan | ASR | VER | - | ❌ |
| 46 | Assessment | Software Assessment Report | ASR | VER | - | ❌ |

**Template Status**:
- ✅ Exists: 22 templates
- ❌ Missing: 24 templates (need creation)

### 2.2 Deliverable Dependencies (Traceability Graph)

```
Phase 1: Planning
├─ SQAP (1) ──┬──► VER checks (2) ──► All subsequent QA activities
├─ SCMP (3) ──┼──► All configuration items
├─ SVP (4) ───┼──► All verification activities
└─ SVaP (5) ──┘──► All validation activities

Phase 2: Requirements
├─ SRS (6) ────┬──► SAS (9), SDS (10)  [Design derives from requirements]
│              ├──► All test specs (7, 12, 13, 16)  [Tests verify requirements]
│              └──► Traceability Matrix (embedded in SRS)
├─ Overall Test Spec (7) ──► Overall Test Report (24)
└─ Req Verification Report (8) ──► Gate Check

Phase 3: Architecture & Design
├─ SAS (9) ────┬──► SDS (10)  [Detailed design from architecture]
│              ├──► Interface Specs (11)
│              └──► Source Code (18)
├─ SDS (10) ───┼──► Component Design (15)
│              └──► Source Code (18)
├─ Interface Specs (11) ──► Integration Tests (12, 13)
├─ Integration Test Specs (12, 13) ──► Integration Test Reports (21, 22)
└─ Design Verification Report (14) ──► Gate Check

Phase 4: Component Design
├─ Component Design Spec (15) ──► Source Code (18)
├─ Component Test Spec (16) ──► Component Test Report (20)
└─ Component Design Verification Report (17) ──► Gate Check

Phase 5: Implementation & Testing
├─ Source Code (18) ──┬──► Static Analysis (in 19)
│                     ├──► Coverage Analysis (in 20)
│                     └──► Integration (21, 22)
├─ Source Code Verification Report (19) ──► Gate Check
└─ Component Test Report (20) ──► Gate Check

Phase 6: Integration
├─ SW Integration Test Report (21) ──┬──► Integration Verification (23)
├─ SW/HW Integration Test Report (22) ──┘
└─ Integration Verification Report (23) ──► Gate Check

Phase 7: Validation
├─ Overall Test Report (24) ──┬──► Validation Report (25)
├─ Tools Validation Report (26) ──┘
└─ Validation Report (25) ──► Gate Check

Phase 8: Assessment (SIL 3-4)
├─ Assessment Plan (45) ──► Assessment Activities
└─ Assessment Report (46) ──► Final Approval
```

---

## 3. Platform Architecture

### 3.1 System Components

```
┌─────────────────────────────────────────────────────────────────┐
│                    USER INTERFACE LAYER                          │
│  - CLI Commands: /cod deliverable-status, /cod generate-srs    │
│  - Progress Dashboard: Real-time deliverable completeness       │
│  - Evidence Browser: View collected evidence by deliverable     │
└─────────────────────────────────────────────────────────────────┘
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│              LIFECYCLE COORDINATOR (COD) - Orchestrator          │
│  - Deliverable State Management (LIFECYCLE_STATE.md extended)   │
│  - Phase Gate Enforcement (SIL-dependent)                       │
│  - Agent Task Assignment (deliverable-driven)                   │
│  - Evidence Completeness Verification                           │
│  - Traceability Graph Management                                │
└─────────────────────────────────────────────────────────────────┘
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│                   DELIVERABLE MANAGEMENT CORE                    │
│                                                                  │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │  Deliverable Repository (46 deliverables)                │  │
│  │  - Deliverable Definitions (JSON/YAML metadata)          │  │
│  │  - Template Library (Markdown templates)                 │  │
│  │  - Content Requirements (per section of EN 50128)        │  │
│  │  - Evidence Requirements (per technique tables)          │  │
│  │  - Verification Criteria (completeness checks)           │  │
│  └──────────────────────────────────────────────────────────┘  │
│                                                                  │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │  Deliverable State Tracker                               │  │
│  │  - Status: not_started / in_progress / draft /           │  │
│  │            verification / validation / approved          │  │
│  │  - Completeness: % of required content filled            │  │
│  │  - Evidence: % of required evidence collected            │  │
│  │  - Blockers: Missing dependencies, evidence gaps         │  │
│  └──────────────────────────────────────────────────────────┘  │
│                                                                  │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │  Evidence Repository                                      │  │
│  │  - Tool Reports (cppcheck, gcov, lcov, lizard, etc.)     │  │
│  │  - Analysis Results (static, dynamic, complexity)        │  │
│  │  - Test Results (unit, integration, system)              │  │
│  │  - Review Records (code reviews, design reviews)         │  │
│  │  - Traceability Data (req-to-test, req-to-code)          │  │
│  │  - Metrics (coverage %, complexity, MISRA violations)    │  │
│  └──────────────────────────────────────────────────────────┘  │
│                                                                  │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │  Traceability Engine                                      │  │
│  │  - Requirement Tracing (SRS → SAS → SDS → Code → Test)  │  │
│  │  - Automatic Link Detection (ID parsing, tagging)        │  │
│  │  - Gap Analysis (untested requirements, dead code)       │  │
│  │  - Coverage Matrix Generation                            │  │
│  └──────────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────────┘
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│                       AGENT EXECUTION LAYER                      │
│                                                                  │
│  Each agent receives DELIVERABLE-DRIVEN tasks:                  │
│                                                                  │
│  ┌─────────┐  ┌─────────┐  ┌─────────┐  ┌─────────┐           │
│  │   REQ   │  │   DES   │  │   IMP   │  │   TST   │  ...      │
│  │         │  │         │  │         │  │         │           │
│  │ Task:   │  │ Task:   │  │ Task:   │  │ Task:   │           │
│  │ Generate│  │ Generate│  │ Generate│  │ Generate│           │
│  │ SRS #6  │  │ SAS #9  │  │ Code #18│  │ Test #20│           │
│  │         │  │         │  │         │  │         │           │
│  │ Output: │  │ Output: │  │ Output: │  │ Output: │           │
│  │ - SRS   │  │ - SAS   │  │ - Code  │  │ - Report│           │
│  │ - Trace │  │ - Design│  │ - Static│  │ - Cov   │           │
│  │ - Evid  │  │ - Evid  │  │   Anal  │  │ - Evid  │           │
│  └─────────┘  └─────────┘  └─────────┘  └─────────┘           │
│                                                                  │
│  ┌─────────┐  ┌─────────┐  ┌─────────┐                         │
│  │   VER   │  │   VAL   │  │   QUA   │  ...                   │
│  │         │  │         │  │         │                         │
│  │ Task:   │  │ Task:   │  │ Task:   │                         │
│  │ Verify  │  │ Validate│  │ Review  │                         │
│  │ SRS #8  │  │ SRS #25 │  │ Code    │                         │
│  │         │  │         │  │         │                         │
│  │ Output: │  │ Output: │  │ Output: │                         │
│  │ - Report│  │ - Report│  │ - QA    │                         │
│  │ - Issues│  │ - Accept│  │   Report│                         │
│  │ - Evid  │  │ - Evid  │  │ - Evid  │                         │
│  └─────────┘  └─────────┘  └─────────┘                         │
└─────────────────────────────────────────────────────────────────┘
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│                    TOOL INTEGRATION LAYER                        │
│  - Static Analysis: cppcheck, clang, PC-lint, splint           │
│  - Complexity: lizard (cyclomatic complexity)                   │
│  - Coverage: gcov, lcov, bullseye                               │
│  - MC/DC: mcdc_analyzer.py                                      │
│  - Memory: valgrind, AddressSanitizer                           │
│  - Build: gcc, make                                             │
│  - Version Control: git                                         │
│  - Test Framework: Unity, CUnit                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 3.2 Deliverable Definition Schema

Each deliverable is defined with structured metadata:

```yaml
# Example: deliverables/SRS.yaml
deliverable_id: "DOC-006-SRS"
number: 6
name: "Software Requirements Specification"
abbreviation: "SRS"
phase: "requirements"
standard_section: "7.2"

# Who creates this deliverable
written_by: "REQ"
first_check: "VER"
second_check: "VAL"

# SIL-dependent requirements
sil_requirements:
  sil_0:
    mandatory: false
  sil_1:
    mandatory: true
    techniques: ["structured_methodology", "decision_tables"]
  sil_2:
    mandatory: true
    techniques: ["structured_methodology", "decision_tables", "modelling"]
  sil_3:
    mandatory: true
    techniques: ["formal_methods", "structured_methodology", "decision_tables", "modelling"]
  sil_4:
    mandatory: true
    techniques: ["formal_methods", "structured_methodology", "decision_tables", "modelling"]

# Template and structure
template_path: ".opencode/skills/en50128-documentation/templates/SRS-template.md"

# Required content sections
required_sections:
  - section_id: "1-introduction"
    title: "Introduction"
    mandatory: true
    content_requirements:
      - "Purpose of document"
      - "Scope of software"
      - "Definitions and abbreviations"
      - "References"
  - section_id: "2-functional-requirements"
    title: "Functional Requirements"
    mandatory: true
    content_requirements:
      - "Each requirement with unique ID (REQ-XXX-NNN)"
      - "Requirements use SHALL/SHOULD/MAY keywords"
      - "Each requirement is testable"
      - "SIL level assigned per requirement"
  - section_id: "3-performance-requirements"
    title: "Performance Requirements"
    mandatory: true
  - section_id: "4-interface-requirements"
    title: "Interface Requirements"
    mandatory: true
  - section_id: "5-safety-requirements"
    title: "Safety Requirements"
    mandatory: true
    sil_requirement: 1  # Mandatory SIL 1+
  - section_id: "6-traceability-matrix"
    title: "Traceability Matrix"
    mandatory: true
    sil_requirement: 3  # Mandatory SIL 3+
    evidence_requirements:
      - "System requirements to software requirements mapping"
      - "Software requirements to test cases mapping"

# Evidence required for this deliverable
evidence_requirements:
  - evidence_id: "req-traceability"
    description: "Traceability matrix from system requirements"
    mandatory_sil: 3
    source: "REQ agent traceability analysis"
    format: "CSV or table in SRS"
    
  - evidence_id: "req-review"
    description: "Requirements review records"
    mandatory_sil: 1
    source: "QUA agent review"
    format: "Review report"
    
  - evidence_id: "hazard-analysis"
    description: "Hazard analysis results"
    mandatory_sil: 2
    source: "SAF agent FMEA/FTA"
    format: "Hazard log entries"

# Verification criteria
verification_criteria:
  completeness:
    - "All required sections present"
    - "All requirements have unique IDs"
    - "All requirements have SIL assignments"
    - "Traceability matrix complete (SIL 3+)"
  correctness:
    - "Requirements use SHALL/SHOULD/MAY correctly"
    - "Each requirement is unambiguous"
    - "Each requirement is testable"
  consistency:
    - "No conflicting requirements"
    - "All referenced documents exist"

# Dependencies
depends_on:
  - deliverable_id: "DOC-001-SQAP"
    reason: "Quality standards defined"
  - deliverable_id: "DOC-003-SCMP"
    reason: "Document ID scheme defined"

# Feeds into (traceability forward)
feeds_into:
  - deliverable_id: "DOC-009-SAS"
    reason: "Architecture derives from requirements"
  - deliverable_id: "DOC-007-TEST-SPEC"
    reason: "Tests verify requirements"
  - deliverable_id: "DOC-008-REQ-VER"
    reason: "Requirements verification"

# Baseline information
baseline:
  create_baseline: true
  baseline_name: "SRS-Baseline"
  cm_control: "full"  # Full configuration control after approval
```

### 3.3 Enhanced LIFECYCLE_STATE.md Structure

Extend current `LIFECYCLE_STATE.md` with deliverable tracking:

```markdown
# Project Lifecycle State

## Project Information
[Existing content...]

## Deliverable Status Dashboard

### Phase 1: Planning (5 deliverables)
| # | Deliverable | Status | Completeness | Evidence | Blockers |
|---|-------------|--------|--------------|----------|----------|
| 1 | SQAP | approved | 100% | 100% | - |
| 2 | SQAP Verification | approved | 100% | 100% | - |
| 3 | SCMP | approved | 100% | 100% | - |
| 4 | SVP | approved | 100% | 100% | - |
| 5 | SVaP | approved | 100% | 100% | - |

**Phase Status**: ✅ COMPLETE - Gate approved 2026-03-01

### Phase 2: Requirements (3 deliverables)
| # | Deliverable | Status | Completeness | Evidence | Blockers |
|---|-------------|--------|--------------|----------|----------|
| 6 | SRS | draft | 85% | 60% | Missing traceability to SysReq-042, SysReq-051 |
| 7 | Overall Test Spec | in_progress | 40% | 20% | Waiting for SRS completion |
| 8 | Req Verification Report | not_started | 0% | 0% | Depends on SRS approval |

**Phase Status**: 🔄 IN PROGRESS - Estimated completion: 2026-03-15

### Phase 3: Architecture & Design (6 deliverables)
[Status: not_started - Blocked by Phase 2 gate]

... [Continue for all 46 deliverables]

## Evidence Repository Summary
- Total evidence artifacts: 127
- Static analysis reports: 12
- Test results: 45
- Coverage reports: 8
- Review records: 23
- Traceability matrices: 5
- Tool reports: 34

## Traceability Status
- Requirements traced: 156/180 (87%)
- Requirements tested: 134/156 (86%)
- Code coverage: 94.2%
- Untested requirements: REQ-042, REQ-051, ... (22 items)
- Dead code: 3 functions (module_x.c:234, module_y.c:567, ...)

## Current Blockers
1. **SRS Traceability Gap**: 24 system requirements not traced to software requirements
   - Owner: REQ agent
   - Due: 2026-03-12
2. **Missing FMEA**: Safety analysis incomplete for SIL 3 components
   - Owner: SAF agent
   - Due: 2026-03-14
```

---

## 4. Agent Behavior Redesign

### 4.1 Deliverable-Driven Agent Tasks

**OLD (Process-Centric)**:
```
User: "Write requirements for train door controller"
REQ Agent: 
  1. Loads requirements skill
  2. Analyzes user input
  3. Generates requirements document
  4. Hopes it follows template
  5. User must manually check completeness
```

**NEW (Deliverable-Centric)**:
```
User: "Generate SRS for train door controller"
COD: 
  1. Identifies deliverable: DOC-006-SRS
  2. Loads deliverable definition: SRS.yaml
  3. Checks prerequisites: SQAP (✅), SCMP (✅), System Requirements (✅)
  4. Assigns task to REQ agent with deliverable context
  
REQ Agent:
  1. Receives deliverable specification (SRS.yaml)
  2. Loads template from specification
  3. Identifies required evidence from specification
  4. Generates content section-by-section per specification
  5. Collects evidence:
     - Traceability matrix (system req → software req)
     - Safety requirements (from SAF agent / Hazard Log)
     - Review checklist
  6. Populates completeness metrics
  7. Submits to COD with evidence bundle
  
COD:
  1. Validates completeness (all required sections present)
  2. Validates evidence (traceability matrix complete per SIL)
  3. Updates LIFECYCLE_STATE.md (SRS: 100% complete, 100% evidence)
  4. Triggers VER agent for first check
  
VER Agent:
  1. Receives SRS + evidence bundle
  2. Runs verification criteria from SRS.yaml
  3. Generates Verification Report (DOC-008-REQ-VER)
  4. Submits to COD
  
COD:
  1. If VER approves → Triggers VAL agent for second check
  2. If VER rejects → Returns to REQ with issues list
  
VAL Agent:
  1. Receives SRS + evidence + VER report
  2. Runs validation checks
  3. Approves or rejects
  
COD:
  1. If VAL approves → Marks SRS as "approved", creates baseline
  2. Unblocks dependent deliverables (SAS, Test Specs)
  3. Updates phase gate status
```

### 4.2 Agent Interface Redesign

Every agent gets a new command structure:

```bash
# Deliverable-centric commands
/req generate-deliverable --id DOC-006-SRS --input "Train door controller requirements"
/des generate-deliverable --id DOC-009-SAS --based-on DOC-006-SRS
/imp generate-deliverable --id DOC-018-CODE --module door_controller --based-on DOC-010-SDS
/ver verify-deliverable --id DOC-006-SRS --generate-report DOC-008-REQ-VER
/val validate-deliverable --id DOC-006-SRS --generate-report DOC-025-VAL

# Evidence collection commands
/imp collect-evidence --code src/door_controller.c --static-analysis --complexity --misra
/tst collect-evidence --test-run unit_tests --coverage --output evidence/unit_test_results.json
/int collect-evidence --integration-test --performance --memory

# Traceability commands
/req trace-requirements --from system-requirements.md --to DOC-006-SRS
/tst trace-tests --from DOC-006-SRS --to test_suite/
/ver verify-traceability --deliverable DOC-006-SRS --coverage-target 100%

# COD orchestration commands
/cod deliverable-status [--deliverable-id DOC-006-SRS]
/cod gate-check --phase requirements
/cod generate-missing-evidence --phase requirements
/cod traceability-report --phase requirements
```

---

## 5. Evidence Collection Automation

### 5.1 Evidence Types and Sources

| Evidence Type | Generated By | Tool/Method | Output Format | Stored In |
|---------------|--------------|-------------|---------------|-----------|
| **Static Analysis** | VER | cppcheck, clang | XML, JSON | `evidence/static_analysis/` |
| **Complexity Metrics** | VER | lizard | JSON | `evidence/metrics/complexity.json` |
| **MISRA C Compliance** | VER | cppcheck, PC-lint | XML | `evidence/misra/misra_report.xml` |
| **Unit Test Results** | TST | Unity, CUnit | XML (JUnit) | `evidence/tests/unit/` |
| **Test Coverage** | TST | gcov, lcov | LCOV, HTML | `evidence/coverage/` |
| **MC/DC Coverage** | TST | mcdc_analyzer.py | JSON | `evidence/coverage/mcdc.json` |
| **Integration Test Results** | INT | Unity, custom | XML (JUnit) | `evidence/tests/integration/` |
| **Performance Metrics** | INT | custom profiling | JSON | `evidence/performance/` |
| **Memory Analysis** | INT | valgrind | XML | `evidence/memory/valgrind.xml` |
| **Code Review Records** | QUA | manual + checklist | Markdown | `evidence/reviews/` |
| **Design Review Records** | QUA | manual + checklist | Markdown | `evidence/reviews/` |
| **Traceability Matrix** | REQ | custom script | CSV, Markdown | `evidence/traceability/` |
| **Hazard Analysis** | SAF | FMEA, FTA | Markdown | `evidence/safety/` |
| **Configuration Audits** | CM | git, custom | Markdown | `evidence/configuration/` |
| **Change Records** | CM | git log, custom | JSON | `evidence/configuration/changes.json` |

### 5.2 Automatic Evidence Linking

**Problem**: Evidence scattered, manual collection tedious, easy to miss items

**Solution**: Automatic evidence linking during agent execution

```python
# Example: IMP agent generates code → automatically triggers evidence collection

class ImplementerAgent:
    def generate_code(self, deliverable_spec):
        # 1. Generate code based on design
        code_file = self.write_code_from_design(deliverable_spec)
        
        # 2. Automatic evidence collection (configured in deliverable spec)
        evidence_bundle = EvidenceCollector()
        
        # Static analysis (mandatory SIL 3+)
        if deliverable_spec.sil >= 3:
            evidence_bundle.add(
                self.run_static_analysis(code_file, tools=["cppcheck", "clang"])
            )
        
        # Complexity analysis (mandatory SIL 3+)
        if deliverable_spec.sil >= 3:
            evidence_bundle.add(
                self.run_complexity_analysis(code_file, threshold=10)
            )
        
        # MISRA C compliance (mandatory SIL 2+)
        if deliverable_spec.sil >= 2:
            evidence_bundle.add(
                self.run_misra_check(code_file)
            )
        
        # 3. Link evidence to deliverable
        deliverable_manager.link_evidence(
            deliverable_id="DOC-018-CODE",
            evidence_bundle=evidence_bundle
        )
        
        # 4. Update completeness metrics
        deliverable_manager.update_status(
            deliverable_id="DOC-018-CODE",
            status="draft",
            completeness=100,  # Code written
            evidence_completeness=self.calculate_evidence_completeness(
                evidence_bundle, deliverable_spec.evidence_requirements
            )
        )
        
        return code_file, evidence_bundle
```

### 5.3 Evidence Completeness Calculation

```python
def calculate_evidence_completeness(collected_evidence, required_evidence, sil):
    """
    Calculate what % of required evidence has been collected.
    
    Args:
        collected_evidence: List of evidence artifacts collected
        required_evidence: List of evidence requirements from deliverable spec
        sil: SIL level (affects mandatory requirements)
    
    Returns:
        float: Percentage completeness (0-100)
    """
    required_items = [
        req for req in required_evidence
        if req.mandatory_sil <= sil  # Only count items mandatory for this SIL
    ]
    
    collected_ids = {e.evidence_id for e in collected_evidence}
    required_ids = {r.evidence_id for r in required_items}
    
    if not required_ids:
        return 100.0
    
    collected_count = len(collected_ids & required_ids)
    required_count = len(required_ids)
    
    return (collected_count / required_count) * 100.0
```

---

## 6. Traceability Automation

### 6.1 Automatic Traceability Link Detection

**Requirement ID Format**: `REQ-<MODULE>-<NUMBER>` (e.g., `REQ-DOOR-001`)
**Test Case ID Format**: `TC-<MODULE>-<NUMBER>` (e.g., `TC-DOOR-001`)
**Code Tag Format**: `@requirement REQ-DOOR-001` in comments

```c
/**
 * @brief Opens the train door
 * @requirement REQ-DOOR-001 System shall open door within 2 seconds
 * @requirement REQ-DOOR-005 System shall check door lock status before opening
 */
error_t door_open(door_t* door) {
    // Implementation
}
```

```c
// Test case
void test_door_open_timing(void) {
    /**
     * @testcase TC-DOOR-001
     * @verifies REQ-DOOR-001
     */
    // Test code
}
```

**Automatic Traceability Script**:
```python
# tools/traceability/auto_trace.py

def extract_requirement_links(source_dir, srs_file, test_dir):
    """
    Automatically extract traceability links from:
    - SRS (all requirements)
    - Source code (@requirement tags)
    - Test code (@verifies tags)
    
    Generate traceability matrix:
    - REQ → Design (SAS/SDS references)
    - REQ → Code (implementation references)
    - REQ → Test (test case coverage)
    """
    
    # Parse SRS for all requirements
    requirements = parse_requirements(srs_file)
    
    # Parse source code for @requirement tags
    code_links = scan_code_for_requirement_tags(source_dir)
    
    # Parse test code for @verifies tags
    test_links = scan_tests_for_verification_tags(test_dir)
    
    # Build traceability matrix
    matrix = TraceabilityMatrix()
    for req_id in requirements:
        matrix.add_requirement(req_id)
        matrix.link_code(req_id, code_links.get(req_id, []))
        matrix.link_tests(req_id, test_links.get(req_id, []))
    
    # Identify gaps
    untested_reqs = matrix.find_untested_requirements()
    uncovered_code = matrix.find_code_without_requirements()
    
    return matrix, untested_reqs, uncovered_code
```

### 6.2 Traceability Verification

```bash
# Automatic traceability verification
/ver verify-traceability --deliverable DOC-006-SRS

# Output:
# Traceability Verification Report
# ==================================
# Requirements: 180
# Requirements with design links: 180 (100%)
# Requirements with code links: 176 (98%)
# Requirements with test links: 156 (87%)
# 
# GAPS FOUND:
# - Untested requirements: REQ-DOOR-042, REQ-DOOR-051, ... (24 items)
# - Code without requirements: door_helper.c:line 234 (orphan function)
# 
# BLOCKERS:
# - SIL 3 project requires 100% requirement test coverage
# - Current: 87% (FAIL - blocks gate)
```

---

## 7. Next Steps: Detailed Design Phases

### Phase 1: Deliverable Metadata System (CURRENT - Step 2)
**Goal**: Create structured definitions for all 46 deliverables

**Tasks**:
1. Design deliverable metadata schema (YAML format)
2. Create deliverable definition files for all 46 deliverables
3. Map evidence requirements per deliverable per SIL
4. Define verification criteria per deliverable
5. Build dependency graph (which deliverables depend on which)

**Output**:
- `deliverables/` directory with 46 YAML files
- Deliverable schema documentation
- Dependency graph visualization

### Phase 2: Evidence Repository System
**Goal**: Automated evidence collection and storage

**Tasks**:
1. Design evidence storage structure
2. Implement evidence collector framework
3. Integrate tool outputs (cppcheck, gcov, lizard, etc.)
4. Build evidence linking mechanism
5. Create evidence completeness calculator

### Phase 3: Traceability Engine
**Goal**: Automatic traceability link detection and verification

**Tasks**:
1. Define traceability ID formats and tagging conventions
2. Implement traceability parser (scan SRS, code, tests)
3. Build traceability matrix generator
4. Create gap analysis tools
5. Implement traceability verification

### Phase 4: Deliverable State Management
**Goal**: Real-time tracking of deliverable status

**Tasks**:
1. Extend LIFECYCLE_STATE.md with deliverable tracking
2. Implement deliverable state machine (states, transitions)
3. Build completeness calculation engine
4. Create blocker detection and reporting
5. Implement phase gate criteria checking

### Phase 5: Agent Integration
**Goal**: Retrofit agents with deliverable-centric behavior

**Tasks**:
1. Add deliverable context to agent invocations
2. Implement evidence collection in agent workflows
3. Add automatic evidence linking after agent actions
4. Update agent outputs to reference deliverable specs
5. Test end-to-end workflows per deliverable

### Phase 6: User Interface
**Goal**: User-friendly deliverable management

**Tasks**:
1. CLI commands for deliverable status, generation, evidence
2. Progress dashboard (text-based or web)
3. Evidence browser
4. Traceability viewer
5. Gap analysis reports

### Phase 7: Validation & Testing
**Goal**: Ensure platform generates compliant deliverables

**Tasks**:
1. Create test project (e.g., simple SIL 3 component)
2. Generate all 46 deliverables end-to-end
3. Verify completeness and correctness
4. Conduct mock assessment (simulate assessor review)
5. Refine based on findings

---

## 8. Success Criteria

The platform is successful when:

1. **Completeness**: All 46 EN 50128 mandatory deliverables can be generated automatically
2. **Evidence**: Every deliverable includes 100% of required evidence per SIL level
3. **Traceability**: Complete requirement-to-test traceability with automatic gap detection
4. **Compliance**: All deliverables pass verification and validation checks
5. **Automation**: Minimal manual effort - agent orchestration handles evidence collection
6. **Transparency**: Real-time visibility into deliverable status, evidence completeness, blockers
7. **SIL-Aware**: Correctly enforces SIL-dependent mandatory/highly recommended/recommended techniques
8. **Assessor-Ready**: Generated deliverables are assessment-ready (pass mock assessor review)

---

## Appendix A: Key Differences from Current Implementation

| Aspect | Current (Process-Centric) | Proposed (Deliverable-Centric) |
|--------|---------------------------|--------------------------------|
| **Primary Focus** | Agent activities, lifecycle phases | Deliverables with evidence |
| **Agent Tasks** | "Do requirements analysis" | "Generate DOC-006-SRS with evidence" |
| **Output** | Hopefully correct documents | Verified, evidence-complete deliverables |
| **Traceability** | Manual, error-prone | Automatic, with gap detection |
| **Evidence** | Collected after-the-fact | Collected during generation |
| **Completeness** | User manually checks | Automatic calculation, blocking gates |
| **Status Tracking** | Phase-level (rough) | Deliverable-level (precise) |
| **Quality Gates** | Phase completion | Evidence completeness + verification |
| **User Experience** | "Hope it's compliant" | "Real-time compliance visibility" |

---

## Appendix B: Template Gaps to Fill

**Missing Templates (24)**:
1. Software Component Design Specification (15)
2. Software Component Design Verification Report (17)
3. Software Validation Report (25) - CRITICAL
4. Tools Validation Report (26) - CRITICAL
5. Application Requirements Specification (28)
6. Application Preparation Plan (29)
7. Application Test Specification (30)
8. Application Architecture and Design (31)
9. Application Preparation Verification Report (32)
10. Application Test Report (33)
11. Source Code of Application Data/Algorithms (34)
12. Application Data/Algorithms Verification Report (35)
13. Software Release and Deployment Plan (36) - CRITICAL
14. Software Deployment Manual (37) - CRITICAL
15. Deployment Records (39) - CRITICAL
16. Deployment Verification Report (40) - CRITICAL
17. Software Maintenance Plan (41)
18. Software Maintenance Records (43)
19. Software Maintenance Verification Report (44)
20. Software Assessment Plan (45) - CRITICAL for SIL 3-4
21. Software Assessment Report (46) - CRITICAL for SIL 3-4
22-24. Application data/algorithms deliverables (if applicable)

**Priority**: Create templates marked CRITICAL first (validation, assessment, deployment)

---

**END OF CONCEPTUAL DESIGN - STEP 1**

**Next Document**: Detailed Design for Phase 1 - Deliverable Metadata System
