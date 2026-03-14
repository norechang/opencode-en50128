# Phase 1: Deliverable Metadata System - Detailed Design

## Document Information

| Property | Value |
|----------|-------|
| **Phase** | Phase 1 of 7 - Deliverable Metadata System |
| **Purpose** | Define structured metadata for all 46 EN 50128 mandatory deliverables |
| **Dependencies** | EN 50128:2011 Annex C Table C.1, Technique Tables A.2-A.21 |
| **Output** | 46 YAML deliverable definition files + schema + dependency graph |
| **Date** | 2026-03-09 |
| **Status** | Detailed Design |

---

## 1. Overview

### 1.1 Goals

1. **Structured Deliverable Definitions**: Create machine-readable specifications for all 46 deliverables
2. **Evidence Mapping**: Define what evidence is required per deliverable per SIL level
3. **Dependency Graph**: Explicit dependencies between deliverables (traceability forward/backward)
4. **Verification Criteria**: Automated completeness and correctness checks
5. **Agent Assignment**: Clear ownership (who writes, who checks)

### 1.2 Design Principles

- **Single Source of Truth**: One YAML file per deliverable, authoritative
- **SIL-Aware**: Evidence requirements scale with SIL level (0, 1, 2, 3, 4)
- **Tool-Friendly**: Machine-readable (YAML), parseable by Python/JavaScript
- **Human-Readable**: Developers can understand and modify definitions
- **Standard-Compliant**: Direct references to EN 50128 sections and tables

### 1.3 Directory Structure

```
/home/norechang/work/EN50128/
├── deliverables/                           # NEW - Deliverable metadata repository
│   ├── schema/
│   │   ├── deliverable-schema.yaml         # JSON Schema for deliverable definitions
│   │   ├── evidence-schema.yaml            # Schema for evidence requirements
│   │   └── README.md                       # Schema documentation
│   ├── planning/                           # Phase 1: Planning deliverables (5)
│   │   ├── DOC-001-SQAP.yaml
│   │   ├── DOC-002-SQAP-VER.yaml
│   │   ├── DOC-003-SCMP.yaml
│   │   ├── DOC-004-SVP.yaml
│   │   └── DOC-005-SVaP.yaml
│   ├── requirements/                       # Phase 2: Requirements (3)
│   │   ├── DOC-006-SRS.yaml
│   │   ├── DOC-007-OVERALL-TEST-SPEC.yaml
│   │   └── DOC-008-REQ-VER.yaml
│   ├── architecture/                       # Phase 3: Architecture & Design (6)
│   │   ├── DOC-009-SAS.yaml
│   │   ├── DOC-010-SDS.yaml
│   │   ├── DOC-011-INTERFACE-SPEC.yaml
│   │   ├── DOC-012-SW-INT-TEST-SPEC.yaml
│   │   ├── DOC-013-HW-SW-INT-TEST-SPEC.yaml
│   │   └── DOC-014-ARCH-DESIGN-VER.yaml
│   ├── component-design/                   # Phase 4: Component Design (3)
│   │   ├── DOC-015-COMPONENT-DESIGN.yaml
│   │   ├── DOC-016-COMPONENT-TEST-SPEC.yaml
│   │   └── DOC-017-COMPONENT-DESIGN-VER.yaml
│   ├── implementation/                     # Phase 5: Implementation & Testing (3)
│   │   ├── DOC-018-SOURCE-CODE.yaml
│   │   ├── DOC-019-SOURCE-CODE-VER.yaml
│   │   └── DOC-020-COMPONENT-TEST-REPORT.yaml
│   ├── integration/                        # Phase 6: Integration (3)
│   │   ├── DOC-021-SW-INT-TEST-REPORT.yaml
│   │   ├── DOC-022-HW-SW-INT-TEST-REPORT.yaml
│   │   └── DOC-023-INT-VER.yaml
│   ├── validation/                         # Phase 7: Validation (3)
│   │   ├── DOC-024-OVERALL-TEST-REPORT.yaml
│   │   ├── DOC-025-VALIDATION-REPORT.yaml
│   │   └── DOC-026-TOOLS-VALIDATION.yaml
│   ├── application/                        # Application data/algorithms (8)
│   │   ├── DOC-028-APP-REQ.yaml
│   │   ├── DOC-029-APP-PREP-PLAN.yaml
│   │   ├── DOC-030-APP-TEST-SPEC.yaml
│   │   ├── DOC-031-APP-ARCH-DESIGN.yaml
│   │   ├── DOC-032-APP-PREP-VER.yaml
│   │   ├── DOC-033-APP-TEST-REPORT.yaml
│   │   ├── DOC-034-APP-SOURCE-CODE.yaml
│   │   └── DOC-035-APP-DATA-VER.yaml
│   ├── deployment/                         # Phase 8: Deployment (5)
│   │   ├── DOC-036-RELEASE-DEPLOYMENT-PLAN.yaml
│   │   ├── DOC-037-DEPLOYMENT-MANUAL.yaml
│   │   ├── DOC-038-RELEASE-NOTES.yaml
│   │   ├── DOC-039-DEPLOYMENT-RECORDS.yaml
│   │   └── DOC-040-DEPLOYMENT-VER.yaml
│   ├── maintenance/                        # Maintenance (4)
│   │   ├── DOC-041-MAINTENANCE-PLAN.yaml
│   │   ├── DOC-042-CHANGE-RECORDS.yaml
│   │   ├── DOC-043-MAINTENANCE-RECORDS.yaml
│   │   └── DOC-044-MAINTENANCE-VER.yaml
│   ├── assessment/                         # Phase 9: Assessment (2)
│   │   ├── DOC-045-ASSESSMENT-PLAN.yaml
│   │   └── DOC-046-ASSESSMENT-REPORT.yaml
│   ├── dependency-graph.yaml               # Master dependency graph
│   ├── deliverable-catalog.yaml            # Master catalog (all 46)
│   └── README.md                           # Documentation
├── .opencode/skills/                       # Existing templates
│   ├── en50128-documentation/templates/    # Core documentation templates
│   ├── en50128-requirements/templates/     # Requirements templates
│   ├── en50128-design/templates/           # Design templates
│   ├── en50128-implementation/templates/   # Implementation templates
│   ├── en50128-testing/templates/          # Testing templates
│   ├── en50128-integration/templates/      # Integration templates
│   ├── en50128-validation/templates/       # Validation templates
│   ├── en50128-verification/templates/     # Verification templates (used across phases)
│   ├── en50128-safety/templates/           # Safety templates
│   ├── en50128-quality/templates/          # Quality templates
│   ├── en50128-configuration/templates/    # Configuration templates
│   └── en50128-project-management/templates/ # PM templates
└── tools/
    └── deliverables/                       # NEW - Deliverable management tools
        ├── validator.py                    # Validate deliverable YAML against schema
        ├── loader.py                       # Load and parse deliverable definitions
        ├── dependency_graph.py             # Generate and query dependency graph
        ├── evidence_checker.py             # Check evidence completeness
        └── README.md                       # Tool documentation
```

---

## 2. Deliverable Metadata Schema

### 2.1 Core Schema Definition

```yaml
# deliverables/schema/deliverable-schema.yaml
# JSON Schema (expressed in YAML) for EN 50128 deliverable definitions

$schema: "http://json-schema.org/draft-07/schema#"
$id: "https://en50128.dev/schemas/deliverable-v1.yaml"
title: "EN 50128 Deliverable Definition Schema"
description: "Schema for defining EN 50128 mandatory deliverables per Annex C Table C.1"
version: "1.0.0"

type: object
required:
  - deliverable_id
  - number
  - name
  - phase
  - standard_section
  - written_by
  - template_path
  - sil_requirements

properties:
  # ===== Basic Identification =====
  deliverable_id:
    type: string
    pattern: "^DOC-\\d{3}-[A-Z0-9-]+$"
    description: "Unique deliverable ID (e.g., DOC-006-SRS)"
    examples:
      - "DOC-006-SRS"
      - "DOC-009-SAS"
      - "DOC-018-SOURCE-CODE"
  
  number:
    type: integer
    minimum: 1
    maximum: 50
    description: "Deliverable number from EN 50128 Annex C Table C.1"
    examples: [6, 9, 18]
  
  name:
    type: string
    minLength: 5
    maxLength: 200
    description: "Full deliverable name from EN 50128"
    examples:
      - "Software Requirements Specification"
      - "Software Architecture Specification"
      - "Software Source Code and Supporting Documentation"
  
  abbreviation:
    type: string
    maxLength: 20
    description: "Common abbreviation (e.g., SRS, SAS, SDS)"
    examples: ["SRS", "SAS", "SDS", "SQAP", "SCMP"]
  
  # ===== Lifecycle Context =====
  phase:
    type: string
    enum:
      - "planning"
      - "requirements"
      - "architecture"
      - "component-design"
      - "implementation"
      - "integration"
      - "validation"
      - "application"
      - "deployment"
      - "maintenance"
      - "assessment"
    description: "Lifecycle phase per EN 50128"
  
  standard_section:
    type: string
    pattern: "^\\d+(\\.\\d+)*$"
    description: "EN 50128:2011 section reference (e.g., 7.2, 7.3, 6.2)"
    examples: ["7.2", "7.3", "7.4", "6.2", "6.5"]
  
  # ===== Ownership (from Table C.1) =====
  written_by:
    type: string
    enum: ["REQ", "DES", "IMP", "TST", "INT", "VER", "VAL", "QUA", "CM", "SAF", "PM", "ASR", "TBD"]
    description: "Agent responsible for writing deliverable (per EN 50128 Table C.1)"
  
  first_check:
    type: string
    enum: ["VER", "VAL", "QUA", "NONE"]
    description: "First checker per EN 50128 Table C.1 (usually VER)"
  
  second_check:
    type: string
    enum: ["VER", "VAL", "QUA", "NONE"]
    description: "Second checker per EN 50128 Table C.1 (usually VAL)"
  
  # ===== Template and Structure =====
  template_path:
    type: string
    pattern: "^\\.\\.?\\/.*\\.md$"
    description: "Relative path to Markdown template file"
    examples:
      - ".opencode/skills/en50128-documentation/templates/SRS-template.md"
      - ".opencode/skills/en50128-design/templates/Software-Architecture-Specification-template.md"
  
  template_exists:
    type: boolean
    description: "Whether template file currently exists"
    default: false
  
  # ===== SIL Requirements =====
  sil_requirements:
    type: object
    required: ["sil_0", "sil_1", "sil_2", "sil_3", "sil_4"]
    description: "SIL-dependent requirements per deliverable"
    properties:
      sil_0:
        $ref: "#/definitions/sil_level_requirements"
      sil_1:
        $ref: "#/definitions/sil_level_requirements"
      sil_2:
        $ref: "#/definitions/sil_level_requirements"
      sil_3:
        $ref: "#/definitions/sil_level_requirements"
      sil_4:
        $ref: "#/definitions/sil_level_requirements"
  
  # ===== Required Content Sections =====
  required_sections:
    type: array
    description: "Sections that must be present in the deliverable"
    items:
      type: object
      required: ["section_id", "title", "mandatory"]
      properties:
        section_id:
          type: string
          pattern: "^[a-z0-9-]+$"
          description: "Unique section identifier"
          examples: ["1-introduction", "2-functional-requirements", "3-traceability"]
        
        title:
          type: string
          description: "Section title"
          examples: ["Introduction", "Functional Requirements", "Traceability Matrix"]
        
        mandatory:
          type: boolean
          description: "Whether section is mandatory for all SILs"
          default: true
        
        sil_requirement:
          type: integer
          minimum: 0
          maximum: 4
          description: "Minimum SIL level where this section is mandatory (if not all SILs)"
          examples: [0, 1, 2, 3, 4]
        
        content_requirements:
          type: array
          description: "What must be documented in this section"
          items:
            type: string
          examples:
            - "Each requirement with unique ID (REQ-XXX-NNN)"
            - "Requirements use SHALL/SHOULD/MAY keywords"
            - "Each requirement is testable"
        
        subsections:
          type: array
          description: "Nested subsections"
          items:
            $ref: "#/properties/required_sections/items"
  
  # ===== Evidence Requirements =====
  evidence_requirements:
    type: array
    description: "Evidence artifacts required for this deliverable"
    items:
      type: object
      required: ["evidence_id", "description", "mandatory_sil", "source"]
      properties:
        evidence_id:
          type: string
          pattern: "^[a-z0-9-]+$"
          description: "Unique evidence identifier"
          examples: ["req-traceability", "static-analysis", "test-coverage"]
        
        description:
          type: string
          description: "What evidence is required"
          examples:
            - "Traceability matrix from system requirements"
            - "Static analysis report (cppcheck, clang)"
            - "Unit test coverage report (gcov/lcov)"
        
        mandatory_sil:
          type: integer
          minimum: 0
          maximum: 4
          description: "Minimum SIL level where this evidence is mandatory"
          examples: [0, 1, 2, 3, 4]
        
        source:
          type: string
          description: "Where evidence comes from (agent, tool, manual)"
          examples:
            - "REQ agent traceability analysis"
            - "cppcheck static analysis"
            - "gcov coverage analysis"
            - "QUA agent code review"
        
        format:
          type: string
          description: "Expected evidence format"
          examples: ["CSV", "JSON", "XML", "Markdown", "PDF", "HTML"]
        
        storage_path:
          type: string
          description: "Relative path where evidence is stored"
          examples:
            - "evidence/traceability/req_trace.csv"
            - "evidence/static_analysis/cppcheck_report.xml"
            - "evidence/coverage/lcov_report.html"
        
        tool:
          type: string
          description: "Tool name if generated by tool"
          examples: ["cppcheck", "gcov", "lcov", "lizard", "valgrind"]
        
        verification_criteria:
          type: array
          description: "How to verify this evidence is complete/correct"
          items:
            type: string
          examples:
            - "All requirements have traceability links"
            - "No mandatory MISRA C violations"
            - "Statement coverage >= 100% (SIL 3+)"
  
  # ===== Verification Criteria =====
  verification_criteria:
    type: object
    description: "Criteria for deliverable completeness and correctness"
    properties:
      completeness:
        type: array
        description: "Checks for completeness"
        items:
          type: string
        examples:
          - "All required sections present"
          - "All requirements have unique IDs"
          - "Traceability matrix complete"
      
      correctness:
        type: array
        description: "Checks for correctness"
        items:
          type: string
        examples:
          - "Requirements use SHALL/SHOULD/MAY correctly"
          - "Each requirement is unambiguous"
          - "No conflicting requirements"
      
      consistency:
        type: array
        description: "Checks for internal and external consistency"
        items:
          type: string
        examples:
          - "All referenced documents exist"
          - "IDs are unique within document"
          - "Terminology consistent with SQAP"
  
  # ===== Dependencies =====
  depends_on:
    type: array
    description: "Deliverables that must exist before this one"
    items:
      type: object
      required: ["deliverable_id", "reason"]
      properties:
        deliverable_id:
          type: string
          pattern: "^DOC-\\d{3}-[A-Z0-9-]+$"
          description: "Deliverable ID this depends on"
        
        reason:
          type: string
          description: "Why this dependency exists"
          examples:
            - "Quality standards defined"
            - "Requirements must exist to design architecture"
            - "Code must exist before integration"
        
        dependency_type:
          type: string
          enum: ["blocking", "informational"]
          default: "blocking"
          description: "Whether dependency is blocking or just informational"
  
  feeds_into:
    type: array
    description: "Deliverables that depend on this one (forward traceability)"
    items:
      type: object
      required: ["deliverable_id", "reason"]
      properties:
        deliverable_id:
          type: string
          pattern: "^DOC-\\d{3}-[A-Z0-9-]+$"
        reason:
          type: string
  
  # ===== Configuration Management =====
  baseline:
    type: object
    description: "Configuration management requirements"
    properties:
      create_baseline:
        type: boolean
        description: "Whether to create CM baseline after approval"
        default: true
      
      baseline_name:
        type: string
        description: "Baseline name pattern"
        examples: ["SRS-Baseline", "SAS-v1.0", "Code-Release-1.0"]
      
      cm_control:
        type: string
        enum: ["none", "light", "full"]
        default: "full"
        description: "Level of configuration control after baseline"
  
  # ===== Metadata =====
  notes:
    type: string
    description: "Additional notes, caveats, or guidance"
  
  tags:
    type: array
    description: "Tags for categorization"
    items:
      type: string
    examples: ["verification-report", "test-deliverable", "sil-3-mandatory"]

# ===== Definitions (Reusable Schemas) =====
definitions:
  sil_level_requirements:
    type: object
    required: ["mandatory"]
    properties:
      mandatory:
        type: boolean
        description: "Whether deliverable is mandatory for this SIL level"
      
      techniques:
        type: array
        description: "EN 50128 techniques applicable (from Tables A.2-A.21)"
        items:
          type: object
          required: ["technique_name", "table_reference", "recommendation"]
          properties:
            technique_name:
              type: string
              description: "Technique name from EN 50128 Annex D"
              examples:
                - "Structured Methodology"
                - "Formal Methods"
                - "Static Analysis"
                - "Dynamic Analysis and Testing"
            
            table_reference:
              type: string
              pattern: "^A\\.\\d+$"
              description: "EN 50128 Annex A table reference"
              examples: ["A.2", "A.3", "A.5", "A.19", "A.21"]
            
            recommendation:
              type: string
              enum: ["M", "HR", "R", "-", "NR"]
              description: "Recommendation level: M=Mandatory, HR=Highly Recommended, R=Recommended, -=No recommendation, NR=Not Recommended"
            
            technique_id:
              type: string
              pattern: "^D\\.\\d+$"
              description: "EN 50128 Annex D section reference"
              examples: ["D.52", "D.28", "D.38"]
      
      additional_requirements:
        type: array
        description: "SIL-specific additional requirements"
        items:
          type: string
        examples:
          - "Independent verification required"
          - "100% requirement traceability mandatory"
          - "Formal proof required for safety-critical functions"
      
      evidence_thresholds:
        type: object
        description: "SIL-specific evidence thresholds"
        properties:
          test_coverage_statement:
            type: number
            minimum: 0
            maximum: 100
            description: "Minimum statement coverage %"
          
          test_coverage_branch:
            type: number
            minimum: 0
            maximum: 100
            description: "Minimum branch coverage %"
          
          test_coverage_condition:
            type: number
            minimum: 0
            maximum: 100
            description: "Minimum condition coverage %"
          
          test_coverage_mcdc:
            type: number
            minimum: 0
            maximum: 100
            description: "Minimum MC/DC coverage %"
          
          cyclomatic_complexity_max:
            type: integer
            minimum: 1
            maximum: 50
            description: "Maximum cyclomatic complexity per function"
          
          misra_mandatory_violations:
            type: integer
            minimum: 0
            description: "Maximum allowed MISRA C mandatory violations"
          
          misra_required_violations:
            type: integer
            minimum: 0
            description: "Maximum allowed MISRA C required violations"
```

---

## 3. Example Deliverable Definitions

### 3.1 Example 1: Software Requirements Specification (SRS)

```yaml
# deliverables/requirements/DOC-006-SRS.yaml

# ===== Basic Identification =====
deliverable_id: "DOC-006-SRS"
number: 6
name: "Software Requirements Specification"
abbreviation: "SRS"

# ===== Lifecycle Context =====
phase: "requirements"
standard_section: "7.2"

# ===== Ownership =====
written_by: "REQ"
first_check: "VER"
second_check: "VAL"

# ===== Template =====
template_path: ".opencode/skills/en50128-documentation/templates/SRS-template.md"
template_exists: true

# ===== SIL Requirements =====
sil_requirements:
  sil_0:
    mandatory: false
    techniques: []
    additional_requirements: []
  
  sil_1:
    mandatory: true
    techniques:
      - technique_name: "Structured Methodology"
        table_reference: "A.2"
        technique_id: "D.52"
        recommendation: "R"
      - technique_name: "Decision Tables"
        table_reference: "A.2"
        technique_id: "D.13"
        recommendation: "R"
    additional_requirements:
      - "Requirements must be testable"
      - "Each requirement has unique ID"
  
  sil_2:
    mandatory: true
    techniques:
      - technique_name: "Structured Methodology"
        table_reference: "A.2"
        technique_id: "D.52"
        recommendation: "R"
      - technique_name: "Modelling"
        table_reference: "A.2"
        technique_id: "A.17"
        recommendation: "R"
      - technique_name: "Decision Tables"
        table_reference: "A.2"
        technique_id: "D.13"
        recommendation: "R"
    additional_requirements:
      - "Requirements must be testable"
      - "Each requirement has unique ID"
      - "Traceability to system requirements"
  
  sil_3:
    mandatory: true
    techniques:
      - technique_name: "Formal Methods"
        table_reference: "A.2"
        technique_id: "D.28"
        recommendation: "HR"
      - technique_name: "Structured Methodology"
        table_reference: "A.2"
        technique_id: "D.52"
        recommendation: "HR"
      - technique_name: "Modelling"
        table_reference: "A.2"
        technique_id: "A.17"
        recommendation: "HR"
      - technique_name: "Decision Tables"
        table_reference: "A.2"
        technique_id: "D.13"
        recommendation: "HR"
    additional_requirements:
      - "Requirements must be testable"
      - "Each requirement has unique ID"
      - "100% traceability to system requirements MANDATORY"
      - "100% traceability from requirements to tests MANDATORY"
    evidence_thresholds:
      test_coverage_statement: 100
      test_coverage_branch: 100
      test_coverage_condition: 100
  
  sil_4:
    mandatory: true
    techniques:
      - technique_name: "Formal Methods"
        table_reference: "A.2"
        technique_id: "D.28"
        recommendation: "HR"
      - technique_name: "Structured Methodology"
        table_reference: "A.2"
        technique_id: "D.52"
        recommendation: "HR"
      - technique_name: "Modelling"
        table_reference: "A.2"
        technique_id: "A.17"
        recommendation: "HR"
      - technique_name: "Decision Tables"
        table_reference: "A.2"
        technique_id: "D.13"
        recommendation: "HR"
    additional_requirements:
      - "Requirements must be testable"
      - "Each requirement has unique ID"
      - "100% traceability to system requirements MANDATORY"
      - "100% traceability from requirements to tests MANDATORY"
      - "Formal specification for safety-critical requirements"
    evidence_thresholds:
      test_coverage_statement: 100
      test_coverage_branch: 100
      test_coverage_condition: 100
      test_coverage_mcdc: 100

# ===== Required Content Sections =====
required_sections:
  - section_id: "document-control"
    title: "Document Control"
    mandatory: true
    content_requirements:
      - "Document ID in format DOC-XXX-YYYY-NNN"
      - "Document Control table (version, date, author, status)"
      - "Approvals table with signatures (author, VER, VAL)"
      - "Change history table"
  
  - section_id: "introduction"
    title: "1. Introduction"
    mandatory: true
    subsections:
      - section_id: "purpose"
        title: "1.1 Purpose"
        mandatory: true
        content_requirements:
          - "Purpose of this document"
          - "Intended audience"
      
      - section_id: "scope"
        title: "1.2 Scope"
        mandatory: true
        content_requirements:
          - "Scope of software system"
          - "What is in scope"
          - "What is out of scope"
      
      - section_id: "definitions"
        title: "1.3 Definitions and Abbreviations"
        mandatory: true
        content_requirements:
          - "Terms and definitions"
          - "Abbreviations"
      
      - section_id: "references"
        title: "1.4 References"
        mandatory: true
        content_requirements:
          - "EN 50128:2011"
          - "System requirements document"
          - "SQAP, SCMP references"
  
  - section_id: "functional-requirements"
    title: "2. Functional Requirements"
    mandatory: true
    content_requirements:
      - "Each requirement with unique ID (REQ-<MODULE>-<NNN>)"
      - "Requirements use SHALL (mandatory), SHOULD (recommended), MAY (optional)"
      - "Each requirement is testable and unambiguous"
      - "Each requirement has SIL level assigned"
      - "Rationale for each requirement"
  
  - section_id: "performance-requirements"
    title: "3. Performance Requirements"
    mandatory: true
    content_requirements:
      - "Timing requirements (response time, throughput)"
      - "Resource requirements (memory, CPU)"
      - "Capacity requirements"
  
  - section_id: "interface-requirements"
    title: "4. Interface Requirements"
    mandatory: true
    content_requirements:
      - "Hardware interfaces"
      - "Software interfaces"
      - "Communication interfaces"
      - "User interfaces"
  
  - section_id: "safety-requirements"
    title: "5. Safety Requirements"
    mandatory: true
    sil_requirement: 1
    content_requirements:
      - "Safety functions"
      - "Safety-critical requirements (derived from Hazard Log)"
      - "SIL assignments per requirement"
      - "Safety constraints"
  
  - section_id: "quality-requirements"
    title: "6. Quality Requirements"
    mandatory: true
    content_requirements:
      - "Reliability requirements"
      - "Maintainability requirements"
      - "Portability requirements"
  
  - section_id: "constraints"
    title: "7. Constraints"
    mandatory: true
    content_requirements:
      - "Design constraints"
      - "Implementation constraints (language, tools)"
      - "Regulatory constraints"
  
  - section_id: "traceability-matrix"
    title: "8. Traceability Matrix"
    mandatory: true
    sil_requirement: 3
    content_requirements:
      - "System requirements to software requirements mapping"
      - "Software requirements to test cases mapping (forward reference)"
      - "100% coverage of system requirements (SIL 3+)"

# ===== Evidence Requirements =====
evidence_requirements:
  - evidence_id: "system-req-traceability"
    description: "Traceability matrix from system requirements to software requirements"
    mandatory_sil: 3
    source: "REQ agent traceability analysis"
    format: "CSV"
    storage_path: "evidence/traceability/system_to_software_reqs.csv"
    verification_criteria:
      - "All system requirements have at least one software requirement link"
      - "All software requirements trace to at least one system requirement"
  
  - evidence_id: "req-test-traceability"
    description: "Traceability matrix from requirements to test cases"
    mandatory_sil: 3
    source: "REQ agent + TST agent traceability analysis"
    format: "CSV"
    storage_path: "evidence/traceability/req_to_test.csv"
    verification_criteria:
      - "All software requirements have at least one test case"
      - "All test cases trace to at least one requirement"
  
  - evidence_id: "req-review-record"
    description: "Requirements review record"
    mandatory_sil: 1
    source: "QUA agent requirements review"
    format: "Markdown"
    storage_path: "evidence/reviews/srs_review.md"
    verification_criteria:
      - "All requirements reviewed"
      - "Review checklist complete"
      - "All issues resolved or tracked"
  
  - evidence_id: "hazard-log-references"
    description: "References to Hazard Log entries for safety requirements"
    mandatory_sil: 2
    source: "SAF agent hazard analysis"
    format: "Embedded in SRS"
    verification_criteria:
      - "All safety requirements trace to hazards"
      - "All identified hazards have mitigating requirements"
  
  - evidence_id: "sil-assignment-justification"
    description: "Justification for SIL assignments per requirement"
    mandatory_sil: 2
    source: "REQ agent + SAF agent"
    format: "Embedded in SRS"
    verification_criteria:
      - "All requirements have SIL assignment"
      - "SIL assignments have rationale"

# ===== Verification Criteria =====
verification_criteria:
  completeness:
    - "All required sections present per schema"
    - "All requirements have unique IDs matching pattern REQ-<MODULE>-<NNN>"
    - "All requirements have SIL assignments (SIL 1+)"
    - "Traceability matrix complete (SIL 3+: 100% system req coverage)"
    - "All referenced documents exist (System Requirements, SQAP, SCMP)"
  
  correctness:
    - "Requirements use SHALL (mandatory), SHOULD (recommended), MAY (optional) correctly"
    - "Each requirement is unambiguous (single interpretation)"
    - "Each requirement is testable (can be verified by test)"
    - "Each requirement is atomic (one requirement per ID)"
    - "SIL assignments are justified"
  
  consistency:
    - "No conflicting requirements"
    - "Terminology consistent with SQAP glossary"
    - "All requirement IDs unique within document"
    - "All traceability links valid (referenced items exist)"

# ===== Dependencies =====
depends_on:
  - deliverable_id: "DOC-001-SQAP"
    reason: "Quality standards, document ID scheme, approval process defined"
    dependency_type: "blocking"
  
  - deliverable_id: "DOC-003-SCMP"
    reason: "Configuration management process, baseline procedure defined"
    dependency_type: "blocking"
  
  - deliverable_id: "EXTERNAL-SYSTEM-REQ"
    reason: "System requirements must exist for traceability"
    dependency_type: "blocking"

feeds_into:
  - deliverable_id: "DOC-007-OVERALL-TEST-SPEC"
    reason: "Test specification verifies requirements"
  
  - deliverable_id: "DOC-008-REQ-VER"
    reason: "Requirements verification report"
  
  - deliverable_id: "DOC-009-SAS"
    reason: "Software architecture derives from requirements"
  
  - deliverable_id: "DOC-010-SDS"
    reason: "Software design implements requirements"

# ===== Configuration Management =====
baseline:
  create_baseline: true
  baseline_name: "SRS-v{{version}}"
  cm_control: "full"

# ===== Metadata =====
notes: |
  SRS is the foundation document for the entire software lifecycle.
  All subsequent deliverables (design, code, tests) must trace back to SRS.
  
  For SIL 3-4 projects:
  - 100% traceability is MANDATORY (not just highly recommended)
  - Independent verification by VER agent required
  - Formal methods highly recommended for safety-critical requirements
  
  Requirements ID Format: REQ-<MODULE>-<NNN>
  Example: REQ-DOOR-001, REQ-BRAKE-042

tags:
  - "requirements"
  - "baseline-deliverable"
  - "sil-1-mandatory"
  - "traceability-source"
```

### 3.2 Example 2: Software Source Code Verification Report

```yaml
# deliverables/implementation/DOC-019-SOURCE-CODE-VER.yaml

# ===== Basic Identification =====
deliverable_id: "DOC-019-SOURCE-CODE-VER"
number: 19
name: "Software Source Code Verification Report"
abbreviation: "SOURCE-CODE-VER"

# ===== Lifecycle Context =====
phase: "implementation"
standard_section: "7.4"

# ===== Ownership =====
written_by: "VER"
first_check: "NONE"  # VER self-checks
second_check: "VAL"

# ===== Template =====
template_path: ".opencode/skills/en50128-implementation/templates/Software-Source-Code-Verification-Report-template.md"
template_exists: true

# ===== SIL Requirements =====
sil_requirements:
  sil_0:
    mandatory: false
  
  sil_1:
    mandatory: true
    techniques:
      - technique_name: "Static Analysis"
        table_reference: "A.19"
        technique_id: "D.47"
        recommendation: "R"
    evidence_thresholds:
      cyclomatic_complexity_max: 20
  
  sil_2:
    mandatory: true
    techniques:
      - technique_name: "Static Analysis"
        table_reference: "A.19"
        technique_id: "D.47"
        recommendation: "HR"
      - technique_name: "Metrics"
        table_reference: "A.5"
        technique_id: "D.37"
        recommendation: "R"
    additional_requirements:
      - "MISRA C:2012 compliance mandatory"
      - "Code review mandatory"
    evidence_thresholds:
      cyclomatic_complexity_max: 15
      misra_mandatory_violations: 0
      misra_required_violations: 10  # With justification
  
  sil_3:
    mandatory: true
    techniques:
      - technique_name: "Static Analysis"
        table_reference: "A.19"
        technique_id: "D.47"
        recommendation: "M"
      - technique_name: "Metrics"
        table_reference: "A.5"
        technique_id: "D.37"
        recommendation: "HR"
      - technique_name: "Software Error Effect Analysis"
        table_reference: "A.5"
        technique_id: "D.25"
        recommendation: "HR"
    additional_requirements:
      - "MISRA C:2012 compliance mandatory"
      - "Code review mandatory"
      - "Independent verification required"
      - "Multiple static analysis tools required"
    evidence_thresholds:
      cyclomatic_complexity_max: 10
      misra_mandatory_violations: 0
      misra_required_violations: 0  # Zero tolerance
  
  sil_4:
    mandatory: true
    techniques:
      - technique_name: "Static Analysis"
        table_reference: "A.19"
        technique_id: "D.47"
        recommendation: "M"
      - technique_name: "Formal Proof"
        table_reference: "A.5"
        technique_id: "D.29"
        recommendation: "HR"
      - technique_name: "Metrics"
        table_reference: "A.5"
        technique_id: "D.37"
        recommendation: "HR"
      - technique_name: "Software Error Effect Analysis"
        table_reference: "A.5"
        technique_id: "D.25"
        recommendation: "HR"
    additional_requirements:
      - "MISRA C:2012 compliance mandatory"
      - "Code review mandatory"
      - "Independent verification required"
      - "Multiple static analysis tools required"
      - "Formal proof for safety-critical functions"
    evidence_thresholds:
      cyclomatic_complexity_max: 10
      misra_mandatory_violations: 0
      misra_required_violations: 0

# ===== Required Content Sections =====
required_sections:
  - section_id: "document-control"
    title: "Document Control"
    mandatory: true
  
  - section_id: "introduction"
    title: "1. Introduction"
    mandatory: true
  
  - section_id: "verification-objectives"
    title: "2. Verification Objectives"
    mandatory: true
    content_requirements:
      - "Verification scope"
      - "Verification methods used"
      - "Reference to SVP (Software Verification Plan)"
  
  - section_id: "static-analysis-results"
    title: "3. Static Analysis Results"
    mandatory: true
    sil_requirement: 1
    content_requirements:
      - "Tools used (name, version, configuration)"
      - "Analysis scope (files analyzed)"
      - "Issues found (by severity: critical, warning, info)"
      - "Issue resolution status"
      - "Summary metrics"
  
  - section_id: "misra-compliance"
    title: "4. MISRA C Compliance"
    mandatory: true
    sil_requirement: 2
    content_requirements:
      - "MISRA C version (2012)"
      - "Deviations (if any, with justification)"
      - "Mandatory violations: 0 (SIL 2+)"
      - "Required violations: 0 (SIL 3+)"
      - "Advisory violations summary"
  
  - section_id: "complexity-metrics"
    title: "5. Complexity Metrics"
    mandatory: true
    sil_requirement: 2
    content_requirements:
      - "Cyclomatic complexity per function"
      - "Maximum complexity threshold enforced (10 SIL 3+, 15 SIL 2)"
      - "Functions exceeding threshold (FAIL if any for SIL 3+)"
  
  - section_id: "code-review-summary"
    title: "6. Code Review Summary"
    mandatory: true
    sil_requirement: 1
    content_requirements:
      - "Reference to QUA code review reports"
      - "Review coverage (% of code reviewed)"
      - "Issues found and resolution status"
  
  - section_id: "traceability-verification"
    title: "7. Traceability Verification"
    mandatory: true
    sil_requirement: 3
    content_requirements:
      - "Requirements to code traceability status"
      - "% of requirements with code implementation"
      - "Orphan code (code without requirements)"
  
  - section_id: "verification-conclusion"
    title: "8. Verification Conclusion"
    mandatory: true
    content_requirements:
      - "Overall verification result (PASS/FAIL)"
      - "Issues summary (critical, major, minor)"
      - "Gate approval recommendation"

# ===== Evidence Requirements =====
evidence_requirements:
  - evidence_id: "cppcheck-report"
    description: "Cppcheck static analysis report"
    mandatory_sil: 2
    source: "cppcheck"
    tool: "cppcheck"
    format: "XML"
    storage_path: "evidence/static_analysis/cppcheck_report.xml"
    verification_criteria:
      - "All files analyzed"
      - "No critical issues unresolved"
  
  - evidence_id: "clang-analyzer-report"
    description: "Clang Static Analyzer report"
    mandatory_sil: 3
    source: "clang"
    tool: "clang"
    format: "HTML"
    storage_path: "evidence/static_analysis/clang_report.html"
    verification_criteria:
      - "All files analyzed"
      - "No critical issues unresolved"
  
  - evidence_id: "misra-report"
    description: "MISRA C compliance report"
    mandatory_sil: 2
    source: "cppcheck --addon=misra"
    tool: "cppcheck"
    format: "XML"
    storage_path: "evidence/misra/misra_report.xml"
    verification_criteria:
      - "0 mandatory violations (SIL 2+)"
      - "0 required violations (SIL 3+)"
  
  - evidence_id: "complexity-report"
    description: "Cyclomatic complexity report"
    mandatory_sil: 2
    source: "lizard"
    tool: "lizard"
    format: "JSON"
    storage_path: "evidence/metrics/complexity.json"
    verification_criteria:
      - "All functions ≤ 10 complexity (SIL 3+)"
      - "All functions ≤ 15 complexity (SIL 2)"
  
  - evidence_id: "code-review-records"
    description: "QUA code review records"
    mandatory_sil: 1
    source: "QUA agent code review"
    format: "Markdown"
    storage_path: "evidence/reviews/code_review_*.md"
    verification_criteria:
      - "100% of code reviewed"
      - "All issues resolved or tracked"

# ===== Verification Criteria =====
verification_criteria:
  completeness:
    - "All required sections present"
    - "All evidence artifacts attached"
    - "Static analysis complete for all source files"
    - "MISRA C analysis complete (SIL 2+)"
    - "Complexity analysis complete (SIL 2+)"
  
  correctness:
    - "0 mandatory MISRA C violations (SIL 2+)"
    - "0 required MISRA C violations (SIL 3+)"
    - "All functions ≤ complexity threshold"
    - "All critical static analysis issues resolved"
  
  consistency:
    - "Tool versions documented"
    - "Analysis configurations documented"
    - "All referenced evidence files exist"

# ===== Dependencies =====
depends_on:
  - deliverable_id: "DOC-004-SVP"
    reason: "Verification plan defines verification methods"
    dependency_type: "blocking"
  
  - deliverable_id: "DOC-018-SOURCE-CODE"
    reason: "Source code must exist to verify"
    dependency_type: "blocking"
  
  - deliverable_id: "QUA-CODE-REVIEW"
    reason: "Code review must be complete"
    dependency_type: "blocking"

feeds_into:
  - deliverable_id: "DOC-023-INT-VER"
    reason: "Integration verification builds on code verification"
  
  - deliverable_id: "DOC-025-VALIDATION-REPORT"
    reason: "Validation references verification results"

# ===== Configuration Management =====
baseline:
  create_baseline: true
  baseline_name: "Source-Code-Verification-v{{version}}"
  cm_control: "full"

# ===== Metadata =====
notes: |
  This verification report is GATE-CRITICAL for SIL 2+ projects.
  
  SIL 3-4 BLOCKERS:
  - ANY mandatory MISRA C violation → FAIL
  - ANY required MISRA C violation → FAIL
  - ANY function > 10 cyclomatic complexity → FAIL
  - Critical static analysis issues unresolved → FAIL
  
  Tools required:
  - SIL 1-2: cppcheck OR clang (one tool minimum)
  - SIL 3-4: cppcheck AND clang (multiple tools MANDATORY)

tags:
  - "verification-report"
  - "gate-critical"
  - "sil-2-mandatory"
  - "static-analysis"
```

---

## 4. Evidence Schema

```yaml
# deliverables/schema/evidence-schema.yaml

$schema: "http://json-schema.org/draft-07/schema#"
$id: "https://en50128.dev/schemas/evidence-v1.yaml"
title: "EN 50128 Evidence Definition Schema"
description: "Schema for defining evidence requirements for EN 50128 deliverables"
version: "1.0.0"

type: object
required:
  - evidence_id
  - description
  - mandatory_sil
  - source

properties:
  evidence_id:
    type: string
    pattern: "^[a-z0-9-]+$"
    description: "Unique evidence identifier (lowercase, hyphen-separated)"
    examples:
      - "req-traceability"
      - "static-analysis-cppcheck"
      - "test-coverage-gcov"
      - "code-review-record"
  
  description:
    type: string
    minLength: 10
    maxLength: 500
    description: "Clear description of what evidence is required"
    examples:
      - "Traceability matrix from system requirements to software requirements"
      - "Cppcheck static analysis report showing zero critical issues"
      - "Unit test coverage report showing ≥100% statement coverage (SIL 3+)"
  
  mandatory_sil:
    type: integer
    minimum: 0
    maximum: 4
    description: "Minimum SIL level where this evidence is mandatory (0=all, 1=SIL1+, etc.)"
    examples: [0, 1, 2, 3, 4]
  
  source:
    type: string
    description: "Where evidence comes from (agent, tool, manual process)"
    examples:
      - "REQ agent traceability analysis"
      - "cppcheck static analysis tool"
      - "gcov coverage tool"
      - "QUA agent code review"
      - "Manual hazard analysis (SAF agent)"
  
  tool:
    type: string
    description: "Tool name if evidence is tool-generated"
    examples: ["cppcheck", "gcov", "lcov", "lizard", "valgrind", "clang"]
  
  tool_version:
    type: string
    description: "Minimum required tool version"
    examples: ["2.13.0", "11.0", "1.15"]
  
  format:
    type: string
    description: "Expected evidence format/file type"
    examples: ["CSV", "JSON", "XML", "Markdown", "PDF", "HTML", "LCOV"]
  
  storage_path:
    type: string
    pattern: "^evidence/.*"
    description: "Relative path where evidence should be stored (under evidence/ directory)"
    examples:
      - "evidence/traceability/req_trace.csv"
      - "evidence/static_analysis/cppcheck_report.xml"
      - "evidence/coverage/lcov_report.html"
      - "evidence/reviews/code_review_2026-03-09.md"
  
  verification_criteria:
    type: array
    description: "Criteria to verify this evidence is complete and correct"
    items:
      type: string
    examples:
      - "All requirements have traceability links"
      - "No mandatory MISRA C violations"
      - "Statement coverage >= 100% (SIL 3+)"
      - "All review checklist items addressed"
  
  generation_command:
    type: string
    description: "Command to generate this evidence (if automated)"
    examples:
      - "cppcheck --enable=all --xml --xml-version=2 src/ 2> evidence/static_analysis/cppcheck_report.xml"
      - "gcov src/*.c && lcov --capture --directory . --output-file evidence/coverage/coverage.info"
      - "lizard src/ -l c --json > evidence/metrics/complexity.json"
  
  automation_level:
    type: string
    enum: ["automatic", "semi-automatic", "manual"]
    description: "Level of automation for evidence generation"
    default: "automatic"
  
  collect_on_agent_action:
    type: string
    enum: ["code-write", "test-run", "review-complete", "design-complete", "manual"]
    description: "When should this evidence be automatically collected"
    examples: ["code-write", "test-run", "review-complete"]
  
  linked_deliverables:
    type: array
    description: "Deliverables that require this evidence"
    items:
      type: string
      pattern: "^DOC-\\d{3}-[A-Z0-9-]+$"
    examples: ["DOC-006-SRS", "DOC-019-SOURCE-CODE-VER"]
  
  notes:
    type: string
    description: "Additional notes or guidance for collecting this evidence"
```

---

## 5. Master Deliverable Catalog

```yaml
# deliverables/deliverable-catalog.yaml
# Master catalog of all 46 EN 50128 deliverables

version: "1.0.0"
standard: "EN 50128:2011"
reference: "Annex C Table C.1"
total_deliverables: 46

phases:
  - phase_id: "planning"
    phase_name: "Planning"
    deliverable_count: 5
    deliverables:
      - DOC-001-SQAP
      - DOC-002-SQAP-VER
      - DOC-003-SCMP
      - DOC-004-SVP
      - DOC-005-SVaP
  
  - phase_id: "requirements"
    phase_name: "Requirements"
    deliverable_count: 3
    deliverables:
      - DOC-006-SRS
      - DOC-007-OVERALL-TEST-SPEC
      - DOC-008-REQ-VER
  
  - phase_id: "architecture"
    phase_name: "Architecture & Design"
    deliverable_count: 6
    deliverables:
      - DOC-009-SAS
      - DOC-010-SDS
      - DOC-011-INTERFACE-SPEC
      - DOC-012-SW-INT-TEST-SPEC
      - DOC-013-HW-SW-INT-TEST-SPEC
      - DOC-014-ARCH-DESIGN-VER
  
  - phase_id: "component-design"
    phase_name: "Component Design"
    deliverable_count: 3
    deliverables:
      - DOC-015-COMPONENT-DESIGN
      - DOC-016-COMPONENT-TEST-SPEC
      - DOC-017-COMPONENT-DESIGN-VER
  
  - phase_id: "implementation"
    phase_name: "Implementation & Testing"
    deliverable_count: 3
    deliverables:
      - DOC-018-SOURCE-CODE
      - DOC-019-SOURCE-CODE-VER
      - DOC-020-COMPONENT-TEST-REPORT
  
  - phase_id: "integration"
    phase_name: "Integration"
    deliverable_count: 3
    deliverables:
      - DOC-021-SW-INT-TEST-REPORT
      - DOC-022-HW-SW-INT-TEST-REPORT
      - DOC-023-INT-VER
  
  - phase_id: "validation"
    phase_name: "Validation"
    deliverable_count: 3
    deliverables:
      - DOC-024-OVERALL-TEST-REPORT
      - DOC-025-VALIDATION-REPORT
      - DOC-026-TOOLS-VALIDATION
  
  - phase_id: "application"
    phase_name: "Application Data/Algorithms"
    deliverable_count: 8
    deliverables:
      - DOC-028-APP-REQ
      - DOC-029-APP-PREP-PLAN
      - DOC-030-APP-TEST-SPEC
      - DOC-031-APP-ARCH-DESIGN
      - DOC-032-APP-PREP-VER
      - DOC-033-APP-TEST-REPORT
      - DOC-034-APP-SOURCE-CODE
      - DOC-035-APP-DATA-VER
  
  - phase_id: "deployment"
    phase_name: "Deployment"
    deliverable_count: 5
    deliverables:
      - DOC-036-RELEASE-DEPLOYMENT-PLAN
      - DOC-037-DEPLOYMENT-MANUAL
      - DOC-038-RELEASE-NOTES
      - DOC-039-DEPLOYMENT-RECORDS
      - DOC-040-DEPLOYMENT-VER
  
  - phase_id: "maintenance"
    phase_name: "Maintenance"
    deliverable_count: 4
    deliverables:
      - DOC-041-MAINTENANCE-PLAN
      - DOC-042-CHANGE-RECORDS
      - DOC-043-MAINTENANCE-RECORDS
      - DOC-044-MAINTENANCE-VER
  
  - phase_id: "assessment"
    phase_name: "Assessment"
    deliverable_count: 2
    sil_requirement: 3  # Mandatory for SIL 3-4 only
    deliverables:
      - DOC-045-ASSESSMENT-PLAN
      - DOC-046-ASSESSMENT-REPORT

# Deliverable-to-File Mapping
deliverable_files:
  DOC-001-SQAP: "planning/DOC-001-SQAP.yaml"
  DOC-002-SQAP-VER: "planning/DOC-002-SQAP-VER.yaml"
  DOC-003-SCMP: "planning/DOC-003-SCMP.yaml"
  DOC-004-SVP: "planning/DOC-004-SVP.yaml"
  DOC-005-SVaP: "planning/DOC-005-SVaP.yaml"
  DOC-006-SRS: "requirements/DOC-006-SRS.yaml"
  DOC-007-OVERALL-TEST-SPEC: "requirements/DOC-007-OVERALL-TEST-SPEC.yaml"
  DOC-008-REQ-VER: "requirements/DOC-008-REQ-VER.yaml"
  DOC-009-SAS: "architecture/DOC-009-SAS.yaml"
  DOC-010-SDS: "architecture/DOC-010-SDS.yaml"
  DOC-011-INTERFACE-SPEC: "architecture/DOC-011-INTERFACE-SPEC.yaml"
  DOC-012-SW-INT-TEST-SPEC: "architecture/DOC-012-SW-INT-TEST-SPEC.yaml"
  DOC-013-HW-SW-INT-TEST-SPEC: "architecture/DOC-013-HW-SW-INT-TEST-SPEC.yaml"
  DOC-014-ARCH-DESIGN-VER: "architecture/DOC-014-ARCH-DESIGN-VER.yaml"
  DOC-015-COMPONENT-DESIGN: "component-design/DOC-015-COMPONENT-DESIGN.yaml"
  DOC-016-COMPONENT-TEST-SPEC: "component-design/DOC-016-COMPONENT-TEST-SPEC.yaml"
  DOC-017-COMPONENT-DESIGN-VER: "component-design/DOC-017-COMPONENT-DESIGN-VER.yaml"
  DOC-018-SOURCE-CODE: "implementation/DOC-018-SOURCE-CODE.yaml"
  DOC-019-SOURCE-CODE-VER: "implementation/DOC-019-SOURCE-CODE-VER.yaml"
  DOC-020-COMPONENT-TEST-REPORT: "implementation/DOC-020-COMPONENT-TEST-REPORT.yaml"
  DOC-021-SW-INT-TEST-REPORT: "integration/DOC-021-SW-INT-TEST-REPORT.yaml"
  DOC-022-HW-SW-INT-TEST-REPORT: "integration/DOC-022-HW-SW-INT-TEST-REPORT.yaml"
  DOC-023-INT-VER: "integration/DOC-023-INT-VER.yaml"
  DOC-024-OVERALL-TEST-REPORT: "validation/DOC-024-OVERALL-TEST-REPORT.yaml"
  DOC-025-VALIDATION-REPORT: "validation/DOC-025-VALIDATION-REPORT.yaml"
  DOC-026-TOOLS-VALIDATION: "validation/DOC-026-TOOLS-VALIDATION.yaml"
  DOC-028-APP-REQ: "application/DOC-028-APP-REQ.yaml"
  DOC-029-APP-PREP-PLAN: "application/DOC-029-APP-PREP-PLAN.yaml"
  DOC-030-APP-TEST-SPEC: "application/DOC-030-APP-TEST-SPEC.yaml"
  DOC-031-APP-ARCH-DESIGN: "application/DOC-031-APP-ARCH-DESIGN.yaml"
  DOC-032-APP-PREP-VER: "application/DOC-032-APP-PREP-VER.yaml"
  DOC-033-APP-TEST-REPORT: "application/DOC-033-APP-TEST-REPORT.yaml"
  DOC-034-APP-SOURCE-CODE: "application/DOC-034-APP-SOURCE-CODE.yaml"
  DOC-035-APP-DATA-VER: "application/DOC-035-APP-DATA-VER.yaml"
  DOC-036-RELEASE-DEPLOYMENT-PLAN: "deployment/DOC-036-RELEASE-DEPLOYMENT-PLAN.yaml"
  DOC-037-DEPLOYMENT-MANUAL: "deployment/DOC-037-DEPLOYMENT-MANUAL.yaml"
  DOC-038-RELEASE-NOTES: "deployment/DOC-038-RELEASE-NOTES.yaml"
  DOC-039-DEPLOYMENT-RECORDS: "deployment/DOC-039-DEPLOYMENT-RECORDS.yaml"
  DOC-040-DEPLOYMENT-VER: "deployment/DOC-040-DEPLOYMENT-VER.yaml"
  DOC-041-MAINTENANCE-PLAN: "maintenance/DOC-041-MAINTENANCE-PLAN.yaml"
  DOC-042-CHANGE-RECORDS: "maintenance/DOC-042-CHANGE-RECORDS.yaml"
  DOC-043-MAINTENANCE-RECORDS: "maintenance/DOC-043-MAINTENANCE-RECORDS.yaml"
  DOC-044-MAINTENANCE-VER: "maintenance/DOC-044-MAINTENANCE-VER.yaml"
  DOC-045-ASSESSMENT-PLAN: "assessment/DOC-045-ASSESSMENT-PLAN.yaml"
  DOC-046-ASSESSMENT-REPORT: "assessment/DOC-046-ASSESSMENT-REPORT.yaml"
```

---

## 6. Dependency Graph Structure

```yaml
# deliverables/dependency-graph.yaml
# Master dependency graph showing deliverable relationships

version: "1.0.0"
description: "EN 50128 deliverable dependency graph - shows which deliverables depend on which"

# Graph structure: adjacency list format
# Each entry: source deliverable → list of deliverables it depends on

dependencies:
  # Phase 1: Planning - No dependencies (foundation)
  DOC-001-SQAP: []
  DOC-002-SQAP-VER:
    - DOC-001-SQAP
  DOC-003-SCMP: []
  DOC-004-SVP: []
  DOC-005-SVaP: []
  
  # Phase 2: Requirements
  DOC-006-SRS:
    - DOC-001-SQAP  # Quality standards defined
    - DOC-003-SCMP  # Document ID scheme defined
    - EXTERNAL-SYSTEM-REQ  # System requirements exist
  
  DOC-007-OVERALL-TEST-SPEC:
    - DOC-006-SRS  # Test spec verifies requirements
    - DOC-001-SQAP
  
  DOC-008-REQ-VER:
    - DOC-006-SRS  # Verify requirements
    - DOC-004-SVP  # Verification plan defines method
  
  # Phase 3: Architecture & Design
  DOC-009-SAS:
    - DOC-006-SRS  # Architecture derives from requirements
    - DOC-001-SQAP
  
  DOC-010-SDS:
    - DOC-009-SAS  # Design from architecture
    - DOC-006-SRS
  
  DOC-011-INTERFACE-SPEC:
    - DOC-009-SAS  # Interfaces from architecture
    - DOC-010-SDS
  
  DOC-012-SW-INT-TEST-SPEC:
    - DOC-009-SAS  # Integration tests from architecture
    - DOC-010-SDS
  
  DOC-013-HW-SW-INT-TEST-SPEC:
    - DOC-011-INTERFACE-SPEC  # HW/SW integration tests
  
  DOC-014-ARCH-DESIGN-VER:
    - DOC-009-SAS
    - DOC-010-SDS
    - DOC-011-INTERFACE-SPEC
    - DOC-004-SVP
  
  # Phase 4: Component Design
  DOC-015-COMPONENT-DESIGN:
    - DOC-010-SDS  # Component design from design
  
  DOC-016-COMPONENT-TEST-SPEC:
    - DOC-015-COMPONENT-DESIGN
  
  DOC-017-COMPONENT-DESIGN-VER:
    - DOC-015-COMPONENT-DESIGN
    - DOC-004-SVP
  
  # Phase 5: Implementation & Testing
  DOC-018-SOURCE-CODE:
    - DOC-010-SDS  # Code implements design
    - DOC-015-COMPONENT-DESIGN
  
  DOC-019-SOURCE-CODE-VER:
    - DOC-018-SOURCE-CODE
    - DOC-004-SVP
    - QUA-CODE-REVIEW  # Code review complete
  
  DOC-020-COMPONENT-TEST-REPORT:
    - DOC-016-COMPONENT-TEST-SPEC
    - DOC-018-SOURCE-CODE
  
  # Phase 6: Integration
  DOC-021-SW-INT-TEST-REPORT:
    - DOC-012-SW-INT-TEST-SPEC
    - DOC-018-SOURCE-CODE
  
  DOC-022-HW-SW-INT-TEST-REPORT:
    - DOC-013-HW-SW-INT-TEST-SPEC
    - DOC-018-SOURCE-CODE
  
  DOC-023-INT-VER:
    - DOC-021-SW-INT-TEST-REPORT
    - DOC-022-HW-SW-INT-TEST-REPORT
    - DOC-004-SVP
  
  # Phase 7: Validation
  DOC-024-OVERALL-TEST-REPORT:
    - DOC-007-OVERALL-TEST-SPEC
    - DOC-018-SOURCE-CODE
  
  DOC-025-VALIDATION-REPORT:
    - DOC-024-OVERALL-TEST-REPORT
    - DOC-005-SVaP
  
  DOC-026-TOOLS-VALIDATION:
    - DOC-001-SQAP  # Tool validation per SQAP
  
  # Phase 8: Application (if applicable)
  DOC-028-APP-REQ:
    - DOC-006-SRS
  
  DOC-029-APP-PREP-PLAN:
    - DOC-028-APP-REQ
  
  DOC-030-APP-TEST-SPEC:
    - DOC-028-APP-REQ
  
  DOC-031-APP-ARCH-DESIGN:
    - DOC-028-APP-REQ
  
  DOC-032-APP-PREP-VER:
    - DOC-031-APP-ARCH-DESIGN
    - DOC-034-APP-SOURCE-CODE
  
  DOC-033-APP-TEST-REPORT:
    - DOC-030-APP-TEST-SPEC
    - DOC-034-APP-SOURCE-CODE
  
  DOC-034-APP-SOURCE-CODE:
    - DOC-031-APP-ARCH-DESIGN
  
  DOC-035-APP-DATA-VER:
    - DOC-034-APP-SOURCE-CODE
  
  # Phase 9: Deployment
  DOC-036-RELEASE-DEPLOYMENT-PLAN:
    - DOC-025-VALIDATION-REPORT  # Must be validated before deployment
  
  DOC-037-DEPLOYMENT-MANUAL:
    - DOC-036-RELEASE-DEPLOYMENT-PLAN
  
  DOC-038-RELEASE-NOTES:
    - DOC-025-VALIDATION-REPORT
  
  DOC-039-DEPLOYMENT-RECORDS:
    - DOC-036-RELEASE-DEPLOYMENT-PLAN
    - DOC-037-DEPLOYMENT-MANUAL
  
  DOC-040-DEPLOYMENT-VER:
    - DOC-039-DEPLOYMENT-RECORDS
  
  # Phase 10: Maintenance
  DOC-041-MAINTENANCE-PLAN:
    - DOC-040-DEPLOYMENT-VER  # After deployment
  
  DOC-042-CHANGE-RECORDS:
    - DOC-003-SCMP
  
  DOC-043-MAINTENANCE-RECORDS:
    - DOC-041-MAINTENANCE-PLAN
  
  DOC-044-MAINTENANCE-VER:
    - DOC-043-MAINTENANCE-RECORDS
  
  # Phase 11: Assessment (SIL 3-4)
  DOC-045-ASSESSMENT-PLAN:
    - DOC-001-SQAP
  
  DOC-046-ASSESSMENT-REPORT:
    - DOC-045-ASSESSMENT-PLAN
    - DOC-025-VALIDATION-REPORT  # All validation complete

# Reverse dependencies (feeds_into)
# Automatically generated from dependencies above
reverse_dependencies:
  DOC-001-SQAP:
    - DOC-002-SQAP-VER
    - DOC-006-SRS
    - DOC-007-OVERALL-TEST-SPEC
    - DOC-009-SAS
    - DOC-026-TOOLS-VALIDATION
    - DOC-045-ASSESSMENT-PLAN
  
  DOC-003-SCMP:
    - DOC-006-SRS
    - DOC-042-CHANGE-RECORDS
  
  DOC-004-SVP:
    - DOC-008-REQ-VER
    - DOC-014-ARCH-DESIGN-VER
    - DOC-017-COMPONENT-DESIGN-VER
    - DOC-019-SOURCE-CODE-VER
    - DOC-023-INT-VER
  
  DOC-005-SVaP:
    - DOC-025-VALIDATION-REPORT
  
  DOC-006-SRS:
    - DOC-007-OVERALL-TEST-SPEC
    - DOC-008-REQ-VER
    - DOC-009-SAS
    - DOC-010-SDS
    - DOC-028-APP-REQ
  
  # ... (continue for all deliverables)
```

---

## 7. Implementation: Python Tools

### 7.1 Deliverable Loader

```python
# tools/deliverables/loader.py
"""
Deliverable definition loader and parser.
Loads YAML deliverable definitions and provides query interface.
"""

import yaml
from pathlib import Path
from typing import Dict, List, Optional, Any
from dataclasses import dataclass, field

@dataclass
class EvidenceRequirement:
    """Evidence requirement definition."""
    evidence_id: str
    description: str
    mandatory_sil: int
    source: str
    format: str
    storage_path: str
    tool: Optional[str] = None
    verification_criteria: List[str] = field(default_factory=list)

@dataclass
class DeliverableDefinition:
    """Complete deliverable definition."""
    deliverable_id: str
    number: int
    name: str
    abbreviation: str
    phase: str
    standard_section: str
    written_by: str
    first_check: str
    second_check: str
    template_path: str
    template_exists: bool
    sil_requirements: Dict[str, Any]
    required_sections: List[Dict[str, Any]]
    evidence_requirements: List[EvidenceRequirement]
    verification_criteria: Dict[str, List[str]]
    depends_on: List[Dict[str, str]]
    feeds_into: List[Dict[str, str]]
    baseline: Dict[str, Any]
    notes: Optional[str] = None
    tags: List[str] = field(default_factory=list)

class DeliverableLoader:
    """Load and manage deliverable definitions."""
    
    def __init__(self, deliverables_dir: Path):
        """
        Initialize loader.
        
        Args:
            deliverables_dir: Path to deliverables/ directory
        """
        self.deliverables_dir = Path(deliverables_dir)
        self._cache: Dict[str, DeliverableDefinition] = {}
    
    def load_deliverable(self, deliverable_id: str) -> DeliverableDefinition:
        """
        Load a deliverable definition by ID.
        
        Args:
            deliverable_id: Deliverable ID (e.g., "DOC-006-SRS")
        
        Returns:
            DeliverableDefinition object
        
        Raises:
            FileNotFoundError: If deliverable definition not found
            ValueError: If YAML is invalid
        """
        if deliverable_id in self._cache:
            return self._cache[deliverable_id]
        
        # Find deliverable file (search all phase directories)
        deliverable_file = self._find_deliverable_file(deliverable_id)
        if not deliverable_file:
            raise FileNotFoundError(f"Deliverable {deliverable_id} not found")
        
        # Load YAML
        with open(deliverable_file, 'r') as f:
            data = yaml.safe_load(f)
        
        # Parse evidence requirements
        evidence_reqs = []
        for ev_data in data.get('evidence_requirements', []):
            evidence_reqs.append(EvidenceRequirement(
                evidence_id=ev_data['evidence_id'],
                description=ev_data['description'],
                mandatory_sil=ev_data['mandatory_sil'],
                source=ev_data['source'],
                format=ev_data['format'],
                storage_path=ev_data['storage_path'],
                tool=ev_data.get('tool'),
                verification_criteria=ev_data.get('verification_criteria', [])
            ))
        
        # Create deliverable object
        deliverable = DeliverableDefinition(
            deliverable_id=data['deliverable_id'],
            number=data['number'],
            name=data['name'],
            abbreviation=data['abbreviation'],
            phase=data['phase'],
            standard_section=data['standard_section'],
            written_by=data['written_by'],
            first_check=data['first_check'],
            second_check=data['second_check'],
            template_path=data['template_path'],
            template_exists=data.get('template_exists', False),
            sil_requirements=data['sil_requirements'],
            required_sections=data.get('required_sections', []),
            evidence_requirements=evidence_reqs,
            verification_criteria=data.get('verification_criteria', {}),
            depends_on=data.get('depends_on', []),
            feeds_into=data.get('feeds_into', []),
            baseline=data.get('baseline', {}),
            notes=data.get('notes'),
            tags=data.get('tags', [])
        )
        
        self._cache[deliverable_id] = deliverable
        return deliverable
    
    def _find_deliverable_file(self, deliverable_id: str) -> Optional[Path]:
        """Find deliverable YAML file by ID."""
        # Search all phase directories
        for phase_dir in self.deliverables_dir.iterdir():
            if phase_dir.is_dir() and phase_dir.name != 'schema':
                deliverable_file = phase_dir / f"{deliverable_id}.yaml"
                if deliverable_file.exists():
                    return deliverable_file
        return None
    
    def get_required_evidence(self, deliverable_id: str, sil: int) -> List[EvidenceRequirement]:
        """
        Get evidence requirements for a deliverable at given SIL level.
        
        Args:
            deliverable_id: Deliverable ID
            sil: SIL level (0-4)
        
        Returns:
            List of evidence requirements mandatory for this SIL
        """
        deliverable = self.load_deliverable(deliverable_id)
        return [
            ev for ev in deliverable.evidence_requirements
            if ev.mandatory_sil <= sil
        ]
    
    def get_dependencies(self, deliverable_id: str) -> List[str]:
        """Get list of deliverable IDs this deliverable depends on."""
        deliverable = self.load_deliverable(deliverable_id)
        return [dep['deliverable_id'] for dep in deliverable.depends_on]
    
    def get_dependents(self, deliverable_id: str) -> List[str]:
        """Get list of deliverable IDs that depend on this one."""
        deliverable = self.load_deliverable(deliverable_id)
        return [dep['deliverable_id'] for dep in deliverable.feeds_into]
```

### 7.2 Schema Validator

```python
# tools/deliverables/validator.py
"""
Validate deliverable YAML files against schema.
"""

import yaml
import jsonschema
from pathlib import Path
from typing import List, Tuple, Optional

class DeliverableValidator:
    """Validate deliverable definitions against schema."""
    
    def __init__(self, schema_path: Path):
        """
        Initialize validator.
        
        Args:
            schema_path: Path to deliverable-schema.yaml
        """
        with open(schema_path, 'r') as f:
            self.schema = yaml.safe_load(f)
    
    def validate_file(self, deliverable_file: Path) -> Tuple[bool, List[str]]:
        """
        Validate a deliverable YAML file.
        
        Args:
            deliverable_file: Path to deliverable YAML file
        
        Returns:
            (is_valid, error_messages)
        """
        try:
            with open(deliverable_file, 'r') as f:
                data = yaml.safe_load(f)
        except Exception as e:
            return False, [f"YAML parse error: {e}"]
        
        errors = []
        try:
            jsonschema.validate(instance=data, schema=self.schema)
            return True, []
        except jsonschema.ValidationError as e:
            errors.append(f"Validation error: {e.message}")
            return False, errors
        except jsonschema.SchemaError as e:
            errors.append(f"Schema error: {e.message}")
            return False, errors
    
    def validate_all(self, deliverables_dir: Path) -> Dict[str, Tuple[bool, List[str]]]:
        """
        Validate all deliverable YAML files.
        
        Args:
            deliverables_dir: Path to deliverables/ directory
        
        Returns:
            Dictionary mapping file path to (is_valid, errors)
        """
        results = {}
        for yaml_file in deliverables_dir.rglob("*.yaml"):
            if yaml_file.parent.name != 'schema':  # Skip schema files
                is_valid, errors = self.validate_file(yaml_file)
                results[str(yaml_file)] = (is_valid, errors)
        return results
```

---

## 8. Implementation Plan

### Task Breakdown

| Task # | Task | Effort | Priority | Dependencies |
|--------|------|--------|----------|--------------|
| 1.1 | Create directory structure | 1 hour | HIGH | None |
| 1.2 | Write deliverable schema YAML | 2 hours | HIGH | 1.1 |
| 1.3 | Write evidence schema YAML | 1 hour | HIGH | 1.1 |
| 1.4 | Write Python loader (loader.py) | 3 hours | HIGH | 1.2, 1.3 |
| 1.5 | Write Python validator (validator.py) | 2 hours | MEDIUM | 1.2 |
| 1.6 | Define all 46 deliverables (YAML) | 16 hours | HIGH | 1.2 |
| 1.7 | Create master catalog | 1 hour | MEDIUM | 1.6 |
| 1.8 | Create dependency graph | 3 hours | HIGH | 1.6 |
| 1.9 | Write unit tests for tools | 4 hours | MEDIUM | 1.4, 1.5 |
| 1.10 | Documentation (README files) | 2 hours | LOW | All |

**Total Estimated Effort**: 35 hours (~5 working days)

### Prioritized Deliverables to Define First

**Tier 1 (Critical Path)**: 8 deliverables
1. DOC-001-SQAP (foundation)
2. DOC-003-SCMP (foundation)
3. DOC-006-SRS (requirements baseline)
4. DOC-009-SAS (architecture)
5. DOC-010-SDS (design)
6. DOC-018-SOURCE-CODE (implementation)
7. DOC-019-SOURCE-CODE-VER (gate-critical)
8. DOC-025-VALIDATION-REPORT (validation)

**Tier 2 (High Value)**: 10 deliverables
- All verification reports (DOC-008, DOC-014, DOC-017, DOC-023, DOC-040, DOC-044)
- Test specifications and reports (DOC-007, DOC-020, DOC-024)
- Assessment (DOC-045, DOC-046)

**Tier 3 (Complete Set)**: Remaining 28 deliverables

---

## 9. Success Criteria

Phase 1 is complete when:

1. ✅ All 46 deliverable definitions created and validated against schema
2. ✅ Python tools (loader, validator) implemented and tested
3. ✅ Master catalog and dependency graph complete
4. ✅ Evidence requirements mapped per SIL per deliverable
5. ✅ Documentation complete (README files, examples)
6. ✅ At least 2 complete deliverable examples (SRS, SOURCE-CODE-VER) fully defined

**Validation Test**:
```python
# Load SRS deliverable
loader = DeliverableLoader(Path("deliverables"))
srs = loader.load_deliverable("DOC-006-SRS")

# Get SIL 3 evidence requirements
evidence = loader.get_required_evidence("DOC-006-SRS", sil=3)
assert len(evidence) >= 3  # At minimum: traceability, review, hazard references

# Check dependencies
deps = loader.get_dependencies("DOC-006-SRS")
assert "DOC-001-SQAP" in deps
assert "DOC-003-SCMP" in deps
```

---

## 10. Next Steps After Phase 1

Once Phase 1 is complete:
1. **Phase 2: Evidence Repository System** - Automatic evidence collection and storage
2. **Phase 3: Traceability Engine** - Automatic traceability link detection and verification
3. **Phase 4: Deliverable State Management** - Real-time tracking of deliverable status (DEFERRED per user request)

---

**END OF PHASE 1 DETAILED DESIGN**

Ready to begin implementation!
