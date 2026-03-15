---
name: en50128-documentation
description: EN 50128 compliant documentation templates for all mandatory deliverables including SRS, SAS, SDS, and test plans
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  document-types: SRS, SAS, SDS, SQAP, SCMP
---

## What I do

I provide templates and guidelines for all mandatory EN 50128 documentation per Section 5:
- Software Requirements Specification (SRS)
- Software Architecture Specification (SAS)
- Software Design Specification (SDS)
- Software Quality Assurance Plan (SQAP)
- Software Configuration Management Plan (SCMP)
- Test plans and reports
- Verification and validation documentation

## When to use me

Use this skill when:
- Creating any EN 50128 mandatory document
- Reviewing document completeness
- Ensuring document consistency
- Preparing deliverable packages
- Supporting certification activities

## EN 50128 Documentation Requirements

**All documentation requirements are based on:**
- **EN 50128:2011 Annex C** - Document requirements table
- **Table A.2** - Requirements specification techniques
- **Table A.3** - Architecture and design techniques
- **Table A.4** - Implementation techniques
- **Table A.5** - Verification and testing techniques
- **Table A.6** - Integration techniques
- **Table A.7** - Validation techniques
- **Table A.8** - Software analysis techniques
- **Table A.9** - Quality assurance techniques (3 MANDATORY for ALL SILs)
- **Table A.21** - Test coverage requirements

**Standard Reference:** `std/EN50128-2011.md` Annex C, all technique tables

## Mandatory Documentation by Phase

### Phase 1: Planning
- [ ] Software Quality Assurance Plan (SQAP)
- [ ] Software Configuration Management Plan (SCMP)
- [ ] Software Verification Plan (SVP)
- [ ] Software Validation Plan (SVaP)

### Phase 2: Requirements
- [ ] Software Requirements Specification (SRS)
- [ ] Requirements Traceability Matrix
- [ ] Requirements Verification Report

### Phase 3: Design
- [ ] Software Architecture Specification (SAS)
- [ ] Software Design Specification (SDS)
- [ ] Interface Specifications
- [ ] Design Verification Report

### Phase 4: Implementation
- [ ] Source Code
- [ ] Unit Test Specifications
- [ ] Unit Test Reports
- [ ] Code Review Records

### Phase 5: Testing
- [ ] Integration Test Specification
- [ ] Integration Test Report
- [ ] System Test Specification
- [ ] System Test Report
- [ ] Coverage Reports

### Phase 6: Validation
- [ ] Validation Test Specification
- [ ] Validation Test Report
- [ ] Software Assessment Report

## Document Templates

All EN 50128 document templates are available in the `templates/` directory. Each template includes:
- Standard document header (Document ID, Version, Date, Author, Reviewer, Approver, SIL Level, Status)
- Document Control table (version history)
- Approvals table (signature section with SIL-specific requirements)
- EN 50128-compliant structure and content guidance

### Available Templates

| Template File | Document Type | EN 50128 Reference | Lifecycle Phase |
|---------------|---------------|-------------------|-----------------|
| **`DOCUMENT-HEADER-TEMPLATE.md`** | General header structure (mandatory for ALL documents) | Annex C | All phases |
| **`Software-Quality-Assurance-Plan-template.md`** | Software Quality Assurance Plan | Section 6.5, Table A.9 | Phase 1 (Planning) |
| **`Software-Configuration-Management-Plan-template.md`** | Software Configuration Management Plan | Section 6.6, Table A.9 | Phase 1 (Planning) |
| **`Software-Verification-Plan-template.md`** | Software Verification Plan | Section 6.2, Table A.5 | Phase 1 (Planning) |
| **`Software-Validation-Plan-template.md`** | Software Validation Plan | Section 7.7, Table A.7 | Phase 1 (Planning) |

**Note**: Specification templates (SRS, SAS, SDS) have been moved to their domain-specific skill directories:
- **SRS** → `en50128-requirements/templates/Software-Requirements-Specification-template.md`
- **SAS** → `en50128-design/templates/Software-Architecture-Specification-template.md`
- **SDS** → `en50128-design/templates/Software-Design-Specification-template.md`

### Template Usage

1. **Always start with the general header template** (`DOCUMENT-HEADER-TEMPLATE.md`)
2. **Select the appropriate document-specific template** from the table above
3. **Follow the template structure exactly** - sections, tables, and required fields are all mandatory for EN 50128 compliance
4. **Fill in all fields** marked with `[placeholders]`
5. **Adjust SIL-specific sections** based on your target SIL level (0, 1, 2, 3, 4)
6. **Maintain traceability** - update Requirements Traceability Matrix (RTM) with every document change

### Template Compliance Verification

**Quality Assurance (QA)** and **Verification (VER)** roles SHALL verify template compliance during document reviews:

#### Template Compliance Checklist
- [ ] Standard header table present with all required fields (Document ID, Version, Date, Project, SIL Level, Author, Reviewer, Approver, Status)
- [ ] Document ID follows format: `DOC-<TYPE>-<YYYY>-<NNN>` (e.g., `DOC-SQAP-2026-001`)
- [ ] Version follows format: `MAJOR.MINOR` (0.1 for draft, 1.0 for first approved version)
- [ ] Document Control table present with version history
- [ ] Approvals table present with SIL-appropriate signature requirements
- [ ] All template sections present (no missing sections)
- [ ] Content follows template guidance (structure, format, required information)

**Non-compliance**: Documents that do not follow the template SHALL be marked as **Draft** status and returned to author for correction.

### SIL-Specific Template Requirements

| SIL Level | Approval Requirements | Additional Requirements |
|-----------|----------------------|-------------------------|
| **SIL 0-1** | Author + Reviewer + PM | Standard header, document control, approvals |
| **SIL 2** | Author + Reviewer + QA Manager + PM | Above + MISRA C compliance planning, static analysis planning |
| **SIL 3-4** | Author + Independent Reviewer + QA Manager + Safety Manager + PM + Customer (for SRS/SQAP) | Above + Independent verification/validation, traceability matrix (RTM) mandatory, enhanced safety analysis |

### Accessing Templates

**File Location**: `.opencode/skills/en50128-documentation/templates/`

**Reading Templates**:
```bash
# View general header template
cat .opencode/skills/en50128-documentation/templates/DOCUMENT-HEADER-TEMPLATE.md

# View SQAP template
cat .opencode/skills/en50128-documentation/templates/Software-Quality-Assurance-Plan-template.md

# List all templates
ls -l .opencode/skills/en50128-documentation/templates/
```

**For detailed template descriptions**, see: `templates/README.md`

## Document Review Checklist

### General Quality
- [ ] Follows standard template
- [ ] All sections complete
- [ ] Version control maintained
- [ ] Approvals present
- [ ] References correct
- [ ] Acronyms defined

### Technical Content
- [ ] Accurate and complete
- [ ] SIL level stated
- [ ] Requirements traceable
- [ ] Consistent with related docs
- [ ] EN 50128 compliance demonstrated

### Safety Critical (SIL 3-4)
- [ ] Independent review performed
- [ ] Safety analysis included
- [ ] Hazards addressed
- [ ] Verification evidence provided

## Comprehensive Workflows

This skill provides detailed, end-to-end workflows for creating EN 50128-compliant documentation. Each workflow covers the complete documentation lifecycle from creation through approval and baseline.

### Workflow 1: Software Requirements Specification (SRS) Documentation

**File**: `workflows/srs-documentation-workflow.md` (968 lines, ~39 pages)

**Purpose**: Complete end-to-end workflow for creating Software Requirements Specification documents per EN 50128 Section 7.2.

**EN 50128 Coverage**:
- Section 7.2: Software Requirements Specification (mandatory requirements)
- Table A.2: Requirements specification techniques (formal methods, modeling, structured methodology)
- Annex C Table C.1: SRS as mandatory deliverable for all SIL levels

**Key Content**:
1. **EN 50128 SRS Requirements** - Section 7.2 mandatory requirements, unambiguous requirement structure (SHALL/SHOULD/MAY keywords)
2. **SRS Document Structure** - Complete document template guidance (787-line template from requirements skill), standard header, document control, approvals
3. **Requirements Elicitation Techniques** - Stakeholder interviews, system analysis, hazard analysis (MANDATORY SIL 3-4), review of existing systems
4. **Requirements Categories** - Functional (REQ-FUNC-*), safety (REQ-SAFE-*), performance (REQ-PERF-*), interface (REQ-INT-*)
5. **SIL-Specific Content Requirements** - Approval workflows by SIL (SIL 0-1: PM approval, SIL 2: +Safety Manager, SIL 3-4: +Independent VER/VAL/Assessor)
6. **Requirements Traceability** - RTM management with `workspace.py trace link`, forward/backward traceability enforcement
7. **SRS Review and Approval Workflow** - 5-step workflow: QUA (template compliance) → VER (technical correctness) → SAF (safety completeness) → VAL (validation readiness) → PM (approval and baseline)
8. **Template Validation** - `validate_srs_template.py` (200 lines): Automated validation of document ID format, version control table, SIL-specific approvals, requirements format (SHALL/SHOULD/MAY keywords), traceability references
9. **Tool Integration** - `workspace.py wf` for document submission and approval tracking, `workspace.py trace` for requirements traceability management
10. **Automation Scripts** - `extract_requirements.py` (150 lines): Extract requirements from document and load into traceability database
11. **Complete Example Scenarios** - Scenario 1: SIL 3 SRS creation (143 requirements, 3-week timeline, end-to-end approval workflow), Scenario 2: SRS baseline update via change request (CCB process, impact analysis, re-approval)

**Workflow Features**:
- Step-by-step guidance for SRS creation from stakeholder needs to baselined document
- SIL-dependent approval workflows (SIL 0-1: 4 approvers, SIL 3-4: 7 approvers including independent roles)
- User approval REQUIRED for all requirement establishment/modification (COD coordination)
- Template validation before technical review (QUA 1-pass rule)
- Traceability automation with `workspace.py trace` commands
- Real-world example timelines and approval histories

**When to Use This Workflow**:
- Creating Software Requirements Specification (Phase 2: Requirements)
- Updating requirements during change control
- Establishing requirements traceability
- Preparing for requirements verification
- Supporting COD gate check for Phase 2 completion

---

### Workflow 2: Software Architecture/Design Specification (SAS/SDS) Documentation

**File**: `workflows/sas-sds-documentation-workflow.md` (1,015 lines, ~41 pages)

**Purpose**: Complete end-to-end workflow for creating Software Architecture Specification (SAS) and Software Design Specification (SDS) documents per EN 50128 Section 7.3.

**EN 50128 Coverage**:
- Section 7.3: Software Architecture and Design (mandatory requirements)
- Table A.3: Architecture and design techniques (modular approach MANDATORY SIL 2+, structured methodology MANDATORY SIL 3-4)
- Annex C Table C.1: SAS/SDS as mandatory deliverables for all SIL levels

**Key Content**:
1. **EN 50128 Architecture and Design Requirements** - Section 7.3 mandatory requirements, SAS vs SDS separation (high-level vs detailed design)
2. **SAS Document Structure** - Complete document template guidance (731-line template from design skill), architecture overview, component decomposition, interface specifications
3. **SDS Document Structure** - Detailed module design, function specifications, state machines, data structures
4. **Architecture and Design Patterns** - Layered architecture (presentation/business logic/data), modular design (MANDATORY SIL 2+), state machine pattern, defensive programming patterns (NULL pointer checks, buffer overflow prevention)
5. **SIL-Specific Architecture Requirements** - Modular approach MANDATORY SIL 2+ (Table A.3), complexity ≤10 for SIL 3-4 (Table A.19), no dynamic memory allocation for SIL 2+ (Table A.4), no recursion for SIL 3-4 (HR)
6. **Design Traceability** - SRS → SAS → SDS → Code traceability, `workspace.py trace link` commands, orphan detection
7. **Architecture/Design Review Workflow** - 6-step workflow: QUA (template compliance) → VER (technical correctness) → SAF (safety patterns) → IMP (implementability) → PM (approval and baseline)
8. **Template Validation** - `validate_sas_sds_template.py` (200 lines): Automated validation of document structure, SIL-specific approvals, architecture diagrams presence, interface specifications, traceability to SRS
9. **Tool Integration** - `workspace.py wf` for document submission and approval tracking, `workspace.py trace` for design traceability management, design review checklist automation
10. **Complete Example Scenarios** - Scenario 1: SIL 3 SAS/SDS creation (87 architecture components, 134 design elements, 3-week timeline, end-to-end approval workflow)

**Workflow Features**:
- Step-by-step guidance for SAS/SDS creation from requirements to detailed design
- SIL-dependent architecture patterns (modular MANDATORY SIL 2+, layered HR all SILs)
- Design pattern templates (layered architecture, state machines, defensive programming with complete C code examples)
- Complexity enforcement (CCN ≤10 for SIL 3-4, automated checking with Lizard)
- Traceability automation with `workspace.py trace` commands
- Real-world example timelines and approval histories
- Memory allocation patterns (static only for SIL 2+, no malloc/free)

**When to Use This Workflow**:
- Creating Software Architecture Specification (Phase 3: Design)
- Creating Software Design Specification (Phase 3: Design)
- Establishing design traceability from requirements
- Preparing for design verification
- Supporting COD gate check for Phase 3 completion

---

### Workflow 3: Test and Verification Documentation

**File**: `workflows/test-verification-documentation-workflow.md` (2,413 lines, ~97 pages)

**Purpose**: Complete end-to-end workflow for creating test and verification documentation per EN 50128 Sections 6.1.4 (Testing), 6.2.4 (Verification), and Table A.21 (Test Coverage).

**EN 50128 Coverage**:
- Section 6.1.4.4: Test Specification requirements
- Section 6.1.4.5: Test Report requirements
- Section 6.2.4: Software Verification Plan and Reports
- Table A.21: Test coverage requirements by SIL level (Statement/Branch/Condition 100% for SIL 3-4)
- Table A.5: Verification and testing techniques (Dynamic Analysis MANDATORY SIL 3-4)

**Key Content**:
1. **EN 50128 Test Documentation Requirements** - Mandatory documents: Component Test Specification/Report, Integration Test Specification/Report, Overall Software Test Specification/Report
2. **Test Specification Structure** - Test objectives, test cases with inputs/expected outputs, coverage targets per Table A.21, test environment and tools, traceability to requirements
3. **Test Report Structure** - Test execution results (pass/fail for each test case), coverage achieved (statement/branch/condition %), defects found with severity, pass/fail assessment
4. **Verification Report Structure** - Verification activities (static analysis, code review, complexity, coverage, traceability), non-conformances found, verification evidence (reports, analysis results), approve/reject recommendation
5. **SIL-Specific Test Requirements** - Coverage by SIL: SIL 0-1 (Statement HR ~80%, Branch HR ~80%), SIL 2 (Branch MANDATORY 100%), SIL 3-4 (Statement/Branch/Condition MANDATORY 100%), Independent testing MANDATORY SIL 3-4
6. **Test Traceability** - Requirements-to-tests traceability matrix, `workspace.py trace link` commands, requirements coverage reports, test-to-results traceability
7. **Test Review and Approval Workflow** - Test Specification: QUA → VER → SAF → PM, Test Report: QUA → VER → VAL → PM, Verification Report: QUA → VAL → PM
8. **Template Validation** - `validate_test_doc_template.py` (200 lines): Automated validation of test specifications (test cases, coverage targets, traceability), test reports (results, coverage achieved, defects), verification reports (verification activities, evidence, non-conformances)
9. **Tool Integration** - `workspace.py wf` for document submission and approval tracking, `workspace.py trace` for test traceability management, coverage validation automation
10. **Automation Scripts** - `generate_test_report.py` (200 lines): Automatically generate Test Report from machine-readable test results (JUnit XML), `parse_coverage_report.py` (150 lines): Parse lcov coverage output and validate against SIL requirements
11. **Complete Example Scenarios** - Scenario 1: SIL 3 Component Testing end-to-end (150 test cases, 2 failures, coverage 99.2%, defect resolution, re-test, approval), Scenario 2: SIL 3 Verification Report creation (static analysis, MISRA C compliance, complexity analysis, coverage verification, traceability verification, approval)

**Workflow Features**:
- Complete test documentation lifecycle from specification to report
- Coverage requirements by SIL (Table A.21) with automated validation
- Machine-readable test results (JUnit XML) with automated report generation
- Verification activities guidance (static analysis tools: Cppcheck/Clang, complexity: Lizard, coverage: gcov/lcov)
- SIL-dependent independence requirements (independent Tester/Verifier/Validator for SIL 3-4)
- Defect tracking and resolution workflow
- Traceability automation with `workspace.py trace` commands
- Real-world example timelines (2 weeks component testing, 1 week verification)

**When to Use This Workflow**:
- Creating Component Test Specification/Report (Phase 4: Component Testing)
- Creating Integration Test Specification/Report (Phase 5: Integration)
- Creating Overall Software Test Specification/Report (Phase 6: Validation)
- Creating Software Verification Report (Verification activities)
- Establishing test traceability from requirements
- Validating coverage against SIL requirements
- Supporting COD gate check for Phases 4, 5, 6 completion

---

## Tool Integration

This skill integrates with EN 50128 workspace tools to automate document workflows, traceability management, and template validation.

### Document Workflow Management (workspace.py wf)

The `workspace.py wf` tool automates document submission, approval tracking, and baseline management.

**Key Commands**:

#### Submit Document for Approval
```bash
workspace.py wf submit <document.md> \
  --doc-type <type> \
  --phase <phase> \
  --sil <sil-level> \
  --author "<Name (Role)>" \
  --description "<Brief description>"
```

**Example: Submit SRS for Approval (SIL 3)**
```bash
workspace.py wf submit docs/Software-Requirements-Specification.md \
  --doc-type srs \
  --phase requirements \
  --sil 3 \
  --author "Jane Doe (REQ)" \
  --description "Software requirements specification for train door control system"
```

**Output**:
```
Document submitted for approval: docs/Software-Requirements-Specification.md

Workflow ID: WF-SRS-001
Document Type: srs
Phase: requirements
SIL: 3
Status: Pending QUA Review

Approval Workflow (SIL 3):
  1. QUA (template compliance) - PENDING
  2. VER (technical review) - Not started
  3. SAF (safety review) - Not started
  4. VAL (validation readiness) - Not started
  5. PM (approval) - Not started

Next Step: QUA reviews document for template compliance
```

#### Record Approval
```bash
workspace.py wf approve <document.md> \
  --role <ROLE> \
  --approver "<Name (Role)>" \
  --comments "<Approval comments>"
```

**Example: QUA Approves SRS**
```bash
workspace.py wf approve docs/Software-Requirements-Specification.md \
  --role QUA \
  --approver "John Smith (QUA)" \
  --comments "Template compliance verified, all required sections present"
```

#### Check Approval Status
```bash
workspace.py wf status <document.md>
```

**Example Output**:
```
Document: docs/Software-Requirements-Specification.md
Workflow ID: WF-SRS-001
Status: Approved

Approval History:
  1. QUA - John Smith - Approved - 2026-03-10 14:30
  2. VER - Alice Johnson (Independent) - Approved - 2026-03-11 10:15
  3. SAF - Bob Wilson - Approved - 2026-03-12 09:00
  4. VAL - David Lee (Independent) - Approved - 2026-03-13 11:30
  5. PM - Charlie Brown - Approved - 2026-03-13 15:45

Document Status: BASELINE (v1.0)
Next Phase: Architecture and Design
```

### Traceability Management (workspace.py trace)

The `workspace.py trace` tool automates traceability link creation, validation, and reporting.

**Key Commands**:

#### Link Requirements to Design
```bash
workspace.py trace link \
  --from "<source-id>" \
  --to "<target-id>" \
  --type "<link-type>" \
  --rationale "<Justification>"
```

**Example: Link SRS Requirement to SAS Component**
```bash
workspace.py trace link \
  --from "REQ-FUNC-001" \
  --to "COMP-MOD-001" \
  --type "derived-to" \
  --rationale "Module MOD-001 implements system initialization requirement REQ-FUNC-001"
```

**Link Types**:
- `derived-to` - Requirement → Design (SRS → SAS/SDS)
- `implements` - Design → Code (SAS/SDS → functions)
- `verified-by` - Requirement → Test (SRS → test cases)
- `found-defect` - Test → Defect (test case → defect ID)

#### Validate Traceability Completeness
```bash
workspace.py trace validate
```

**Example Output**:
```
================================================================================
Traceability Validation Report
================================================================================
SIL: 3 (Traceability MANDATORY)

Forward Traceability:
  SRS → SAS: 143/143 (100%) ✓
  SRS → SDS: 143/143 (100%) ✓
  SRS → Code: 143/143 (100%) ✓
  SRS → Tests: 143/143 (100%) ✓

Backward Traceability:
  SAS → SRS: 87/87 design elements traced (100%) ✓
  SDS → SRS: 134/134 design elements traced (100%) ✓
  Code → SRS: 156/156 functions traced (100%) ✓
  Tests → SRS: 247/247 test cases traced (100%) ✓

Orphan Detection:
  Orphan design elements (SAS/SDS not traced to SRS): 0 ✓
  Orphan code (functions not traced to design): 0 ✓
  Orphan tests (tests not traced to requirements): 0 ✓

✅ PASS: Traceability complete (SIL 3 requirement met)
================================================================================
```

#### Generate Requirements Coverage Report
```bash
workspace.py trace report --type requirements-coverage
```

**Example Output**:
```
================================================================================
Requirements Coverage Report
================================================================================
Generated: 2026-03-15 10:30:00
SIL: 3 (100% coverage MANDATORY)

Total Requirements: 143
Requirements with Tests: 143 (100%)
Requirements without Tests: 0

Coverage by Category:
  Functional Requirements (REQ-FUNC-*): 87/87 (100%)
  Safety Requirements (REQ-SAFE-*): 34/34 (100%)
  Performance Requirements (REQ-PERF-*): 12/12 (100%)
  Interface Requirements (REQ-INT-*): 10/10 (100%)

✅ PASS: All requirements have test coverage (SIL 3 requirement met)
================================================================================
```

### Template Validation Scripts

The documentation skill provides Python scripts for automated template validation.

#### validate_srs_template.py
Validates Software Requirements Specification documents for EN 50128 compliance.

**Usage**:
```bash
python3 validate_srs_template.py <srs-document.md> <sil-level>
```

**Example**:
```bash
python3 validate_srs_template.py docs/Software-Requirements-Specification.md 3
```

**Checks**:
- Document ID format (`DOC-SRS-YYYY-NNN`)
- Version control table presence and format
- SIL-specific approvals table (7 approvers for SIL 3-4)
- Requirements format (SHALL/SHOULD/MAY keywords)
- Requirements traceability references
- All mandatory sections present (Introduction, Requirements by Category, Traceability Matrix, etc.)

#### validate_sas_sds_template.py
Validates Software Architecture and Design Specification documents for EN 50128 compliance.

**Usage**:
```bash
python3 validate_sas_sds_template.py <sas-sds-document.md> <doc-type> <sil-level>
```

**Example**:
```bash
python3 validate_sas_sds_template.py docs/Software-Architecture-Specification.md sas 3
```

**Checks**:
- Document ID format
- Version control and approvals
- Architecture diagrams presence (for SAS)
- Interface specifications
- Traceability to SRS
- SIL-specific content (modular approach documented for SIL 2+, complexity limits stated for SIL 3-4)

#### validate_test_doc_template.py
Validates test and verification documents for EN 50128 compliance.

**Usage**:
```bash
python3 validate_test_doc_template.py <document.md> <doc-type> <sil-level>
```

**Example**:
```bash
python3 validate_test_doc_template.py docs/Component-Test-Specification.md test-specification 3
```

**Document Types**: `test-specification`, `test-report`, `verification-report`

**Checks**:
- Test Specification: Test cases format, coverage targets match SIL requirements (100% for SIL 3-4), traceability to requirements
- Test Report: Test results documented (pass/fail), coverage achieved, defects documented, pass/fail recommendation
- Verification Report: Verification activities documented, non-conformances documented, evidence references, approve/reject recommendation

### Automation Script Integration

#### generate_test_report.py
Automatically generates Test Report from machine-readable test results (JUnit XML format).

**Usage**:
```bash
python3 generate_test_report.py <test-results.xml> <template.md> <output-report.md>
```

**Example**:
```bash
python3 generate_test_report.py \
  build/test-results.xml \
  templates/Component-Test-Report-template.md \
  docs/Component-Test-Report.md
```

**Features**:
- Parses JUnit XML test results
- Generates Executive Summary (pass/fail, coverage, defects)
- Generates Test Execution Summary table (by module)
- Generates Coverage Analysis section
- Populates template with actual test results

#### parse_coverage_report.py
Parses lcov coverage output and validates against SIL requirements.

**Usage**:
```bash
python3 parse_coverage_report.py <coverage.info> <sil-level>
```

**Example**:
```bash
python3 parse_coverage_report.py build/coverage.info 3
```

**Features**:
- Parses lcov coverage.info file
- Validates coverage against Table A.21 requirements
- Identifies uncovered code (files, lines)
- Reports coverage by file
- Exit code 0 (PASS) or 1 (FAIL) for CI/CD integration

#### extract_requirements.py
Extracts requirements from SRS document and loads into traceability database.

**Usage**:
```bash
python3 extract_requirements.py <srs-document.md>
```

**Example**:
```bash
python3 extract_requirements.py docs/Software-Requirements-Specification.md
```

**Features**:
- Extracts requirements with IDs (REQ-FUNC-001, REQ-SAFE-002, etc.)
- Parses requirement attributes (category, priority, SIL level)
- Loads into traceability database for `workspace.py trace` commands
- Validates requirement format (SHALL/SHOULD/MAY keywords)

---

## EN 50128 Coverage Summary

This skill provides complete coverage of EN 50128 documentation requirements across all lifecycle phases.

### Standards Coverage

| EN 50128 Section/Table | Coverage | Workflow Reference |
|------------------------|----------|-------------------|
| **Section 5** | General documentation requirements | All workflows |
| **Section 6.1.4.4** | Test Specification requirements | Workflow 3 (Test/Verification) |
| **Section 6.1.4.5** | Test Report requirements | Workflow 3 (Test/Verification) |
| **Section 6.2.4** | Verification Report requirements | Workflow 3 (Test/Verification) |
| **Section 7.2** | Software Requirements Specification | Workflow 1 (SRS) |
| **Section 7.3** | Software Architecture and Design | Workflow 2 (SAS/SDS) |
| **Table A.2** | Requirements specification techniques | Workflow 1 (SRS) |
| **Table A.3** | Architecture and design techniques | Workflow 2 (SAS/SDS) |
| **Table A.5** | Verification and testing techniques | Workflow 3 (Test/Verification) |
| **Table A.21** | Test coverage requirements | Workflow 3 (Test/Verification) |
| **Annex C Table C.1** | Mandatory documents by phase | All workflows |

### Lifecycle Phase Coverage

| Phase | Documents Covered | Workflow Reference |
|-------|-------------------|-------------------|
| **Phase 1: Planning** | SQAP, SCMP, SVP, SVaP (templates provided) | Templates directory |
| **Phase 2: Requirements** | SRS, RTM (complete workflow) | Workflow 1 (SRS) |
| **Phase 3: Design** | SAS, SDS (complete workflow) | Workflow 2 (SAS/SDS) |
| **Phase 4: Implementation** | Component Test Specification/Report (complete workflow) | Workflow 3 (Test/Verification) |
| **Phase 5: Integration** | Integration Test Specification/Report (complete workflow) | Workflow 3 (Test/Verification) |
| **Phase 6: Validation** | Overall Software Test Specification/Report (complete workflow) | Workflow 3 (Test/Verification) |
| **All Phases** | Verification Reports (complete workflow) | Workflow 3 (Test/Verification) |

### Tool Coverage

| Tool/Capability | Purpose | Workflow Integration |
|-----------------|---------|----------------------|
| **workspace.py wf** | Document submission, approval tracking, baseline management | All workflows (SRS, SAS/SDS, Test/Verification) |
| **workspace.py trace** | Traceability link creation, validation, reporting | All workflows (requirements → design → code → tests) |
| **validate_srs_template.py** | Automated SRS template validation | Workflow 1 (SRS) |
| **validate_sas_sds_template.py** | Automated SAS/SDS template validation | Workflow 2 (SAS/SDS) |
| **validate_test_doc_template.py** | Automated test/verification document validation | Workflow 3 (Test/Verification) |
| **generate_test_report.py** | Automated test report generation from JUnit XML | Workflow 3 (Test/Verification) |
| **parse_coverage_report.py** | Coverage parsing and SIL validation | Workflow 3 (Test/Verification) |
| **extract_requirements.py** | Requirement extraction and traceability loading | Workflow 1 (SRS) |

### SIL-Specific Coverage

All workflows provide SIL-specific guidance (SIL 0, 1, 2, 3, 4):

- **SIL 0-1**: Standard approval workflows (4 approvers), template compliance, basic traceability
- **SIL 2**: Enhanced approval workflows (5 approvers including Safety Manager), MISRA C planning, static analysis planning, traceability recommended
- **SIL 3-4**: Independent approval workflows (7+ approvers including Independent VER/VAL/Assessor), traceability MANDATORY (100%), coverage MANDATORY (Statement/Branch/Condition 100%), independent testing/verification/validation

---

## References
- EN 50128:2011 Section 5 (Documentation)
- EN 50128:2011 Section 6.1.4 (Testing Documentation)
- EN 50128:2011 Section 6.2.4 (Verification Documentation)
- EN 50128:2011 Section 7.2 (Software Requirements Specification)
- EN 50128:2011 Section 7.3 (Software Architecture and Design)
- EN 50128:2011 Table A.2 (Requirements Specification Techniques)
- EN 50128:2011 Table A.3 (Architecture and Design Techniques)
- EN 50128:2011 Table A.5 (Verification and Testing Techniques)
- EN 50128:2011 Table A.21 (Test Coverage for Code)
- EN 50128:2011 Annex B (Document Guidelines)
- EN 50128:2011 Annex C Table C.1 (Document Control Summary)
- ISO/IEC 15289 (Documentation Management)
