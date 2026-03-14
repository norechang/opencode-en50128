# Traceability Management Workflow

**Purpose**: Establish, maintain, and verify traceability links throughout the software development lifecycle.

**EN 50128 Reference**: Section 7.2, Table A.9 (Traceability - MANDATORY SIL 3-4)

**Role**: Requirements Engineer (REQ), with coordination from Designer (DES), Tester (TST), Implementer (IMP)

**Prerequisites**:
- Software Requirements Specification (SRS) approved
- System Requirements Specification available
- Hazard Log available

---

## What is Traceability?

**Traceability** is the ability to trace relationships between:
- **Backward traceability**: Software requirements → Sources (system requirements, hazards, stakeholder needs)
- **Forward traceability**: Software requirements → Targets (design elements, test cases, code modules)

**EN 50128 Requirement**:
- **SIL 3-4**: Traceability is **MANDATORY** (Table A.9, Technique 7)
- **SIL 1-2**: Traceability is **Highly Recommended**
- **SIL 0**: Traceability is **Recommended**

---

## Traceability Types

### 1. Backward Traceability (Requirements → Sources)

**Purpose**: Ensure every software requirement has a justified source

**Traceability Links**:
```
System Requirements → Software Requirements
Hazards → Safety Requirements
Stakeholder Needs → Software Requirements
Standards/Regulations → Constraint Requirements
```

**Example**:
| Software Requirement | Source Type | Source ID | Source Description |
|----------------------|-------------|-----------|-------------------|
| REQ-FUNC-001 | System Req | SYS-CTRL-010 | Speed control system requirement |
| REQ-SAFE-010 | Hazard | HAZ-005 | Overspeed hazard mitigation |
| REQ-INTF-020 | Hardware Spec | HW-SENSOR-001 | Speed sensor interface specification |
| REQ-CONS-030 | Standard | EN 50128 7.4.4.3 | No dynamic memory allocation (SIL 2+) |

**Verification Criteria**:
- ✅ Every software requirement has at least one source
- ✅ Every system requirement is covered by at least one software requirement (100% for SIL 3-4)
- ✅ Every hazard is mitigated by at least one safety requirement
- ❌ No orphan requirements (requirements without sources)

### 2. Forward Traceability (Requirements → Targets)

**Purpose**: Ensure every requirement is implemented, tested, and verified

**Traceability Links**:
```
Software Requirements → Design Elements
Software Requirements → Code Modules
Software Requirements → Test Cases
Software Requirements → Verification Records
```

**Example**:
| Software Requirement | Design Element | Code Module | Test Cases | Verification |
|----------------------|----------------|-------------|------------|--------------|
| REQ-FUNC-001 | DESIGN-SENSOR-001 | sensor.c | TC-001, TC-002, TC-003 | VER-REQ-001 |
| REQ-SAFE-010 | DESIGN-SAFETY-010 | safety_monitor.c | TC-100, TC-101, TC-102 | VER-SAFE-010 |

**Verification Criteria**:
- ✅ Every software requirement is addressed by at least one design element
- ✅ Every software requirement is implemented in at least one code module
- ✅ Every software requirement is verified by at least one test case (100% for SIL 3-4)
- ✅ Every software requirement has a verification record
- ❌ No untested requirements
- ❌ No unimplemented requirements

### 3. Horizontal Traceability (Between Artifacts)

**Purpose**: Ensure consistency across lifecycle artifacts

**Traceability Links**:
```
Design Elements ↔ Code Modules
Test Cases ↔ Test Results
Code Modules ↔ Verification Records
```

---

## Workflow Steps

### Phase 1: Requirements Phase - Establish Backward Traceability

**Objective**: Link software requirements to sources

#### Step 1.1: Create System-to-Software Traceability Matrix
- [ ] List all system requirements (from System Requirements Specification)
- [ ] For each system requirement:
  - [ ] Identify derived software requirements
  - [ ] Record traceability link: SYS-XXX → REQ-YYY-ZZZ
  - [ ] Verify all system requirements covered (100% for SIL 3-4)

**Format**: CSV or Markdown table

**Example - system_to_software_requirements.csv**:
```csv
System_Requirement_ID,System_Requirement_Title,Software_Requirement_ID,Software_Requirement_Title,Coverage_Type
SYS-CTRL-001,Speed monitoring and control,REQ-FUNC-001,Read speed sensor value,Full
SYS-CTRL-001,Speed monitoring and control,REQ-FUNC-002,Validate speed sensor data,Full
SYS-CTRL-001,Speed monitoring and control,REQ-FUNC-003,Calculate control command,Full
SYS-CTRL-001,Speed monitoring and control,REQ-SAFE-010,Detect overspeed condition,Partial
SYS-SAFE-005,Emergency braking,REQ-SAFE-010,Detect overspeed condition,Partial
SYS-SAFE-005,Emergency braking,REQ-SAFE-011,Activate emergency brake,Full
```

**Coverage Types**:
- **Full**: Software requirement fully satisfies system requirement
- **Partial**: Software requirement partially satisfies system requirement (other SW requirements also needed)

**Tool**: `workspace.py trace validate --phase requirements --sil 3`

#### Step 1.2: Create Hazard-to-Safety-Requirements Traceability Matrix
- [ ] List all hazards (from Hazard Log)
- [ ] For each hazard:
  - [ ] Identify mitigating safety requirements
  - [ ] Record traceability link: HAZ-XXX → REQ-SAFE-YYY
  - [ ] Verify all hazards mitigated

**Example - hazard_to_safety_requirements.csv**:
```csv
Hazard_ID,Hazard_Description,Severity,SIL,Safety_Requirement_ID,Mitigation_Type
HAZ-005,Train overspeed,Catastrophic,4,REQ-SAFE-010,Detection
HAZ-005,Train overspeed,Catastrophic,4,REQ-SAFE-011,Mitigation
HAZ-005,Train overspeed,Catastrophic,4,REQ-SAFE-012,Recovery
HAZ-010,Sensor failure undetected,Critical,3,REQ-SAFE-020,Detection
HAZ-010,Sensor failure undetected,Critical,3,REQ-SAFE-021,Mitigation
```

**Mitigation Types**:
- **Prevention**: Prevents hazard from occurring
- **Detection**: Detects hazard occurrence
- **Mitigation**: Reduces hazard impact
- **Recovery**: Returns system to safe state

#### Step 1.3: Create Standards-to-Constraints Traceability Matrix
- [ ] List all applicable standards and regulations
- [ ] For each standard requirement:
  - [ ] Identify constraint requirements
  - [ ] Record traceability link: STANDARD-SECTION → REQ-CONS-YYY

**Example - standards_to_constraints.csv**:
```csv
Standard,Section,Standard_Requirement,Constraint_Requirement_ID,Constraint_Description
EN 50128,7.4.4.3,No dynamic memory allocation (SIL 2+),REQ-CONS-001,Static allocation only
EN 50128,7.4.4.24,No recursion (SIL 3-4),REQ-CONS-002,No recursive function calls
MISRA C,Rule 21.3,malloc/calloc/realloc/free shall not be used,REQ-CONS-001,Static allocation only
EN 50128,Table A.21,Branch coverage 100% (SIL 3-4),REQ-CONS-010,Achieve 100% branch coverage in testing
```

#### Step 1.4: Verify Backward Traceability Completeness
- [ ] Run traceability validation tool
- [ ] Check for orphan requirements (no source)
- [ ] Check for uncovered sources (system req without SW req)
- [ ] Fix gaps

**Command**: `workspace.py trace validate --phase requirements --sil 3`

**Expected Output**:
```
✅ Backward Traceability Check (SIL 3)
   - System Requirements Coverage: 45/45 (100%) ✅
   - Hazards Coverage: 12/12 (100%) ✅
   - Orphan Requirements: 0 ✅
   - Standards Coverage: 8/8 (100%) ✅
   
PASS: Backward traceability complete for SIL 3
```

---

### Phase 2: Design Phase - Establish Forward Traceability to Design

**Objective**: Link software requirements to design elements

#### Step 2.1: Create Requirements-to-Design Traceability Matrix
- [ ] Designer (DES) creates design elements (Software Architecture, Software Design)
- [ ] For each design element:
  - [ ] Identify implementing requirements
  - [ ] Record traceability link: REQ-XXX-YYY → DESIGN-ZZZ
- [ ] REQ engineer verifies all requirements addressed in design

**Example - requirements_to_design.csv**:
```csv
Requirement_ID,Requirement_Title,Design_Element_ID,Design_Element_Name,Design_Document
REQ-FUNC-001,Read speed sensor value,DESIGN-SENSOR-001,Speed Sensor Interface Module,SAS Section 4.2
REQ-FUNC-002,Validate speed sensor data,DESIGN-SENSOR-002,Sensor Validation Component,SDS Section 5.1
REQ-SAFE-010,Detect overspeed condition,DESIGN-SAFETY-001,Overspeed Detection Component,SDS Section 6.3
REQ-SAFE-011,Activate emergency brake,DESIGN-ACTUATOR-010,Emergency Brake Interface,SDS Section 7.2
```

**Verification**: All requirements have at least one design element

---

### Phase 3: Test Planning Phase - Establish Forward Traceability to Tests

**Objective**: Link software requirements to test cases

#### Step 3.1: Create Requirements-to-Test-Cases Traceability Matrix
- [ ] Tester (TST) creates test specifications
- [ ] For each requirement:
  - [ ] Identify test cases that verify the requirement
  - [ ] Record traceability link: REQ-XXX-YYY → TC-ZZZ
  - [ ] Ensure all requirements are testable
- [ ] REQ engineer verifies all requirements have test coverage (100% for SIL 3-4)

**Example - requirements_to_testcases.csv**:
```csv
Requirement_ID,Requirement_Title,SIL,Test_Case_ID,Test_Type,Test_Description
REQ-FUNC-001,Read speed sensor value,3,TC-FUNC-001-01,Unit Test,Test sensor read with valid data
REQ-FUNC-001,Read speed sensor value,3,TC-FUNC-001-02,Unit Test,Test sensor read with timeout
REQ-FUNC-001,Read speed sensor value,3,TC-FUNC-001-03,Integration Test,Test sensor read on target hardware
REQ-SAFE-010,Detect overspeed condition,4,TC-SAFE-010-01,Unit Test,Test overspeed detection at threshold
REQ-SAFE-010,Detect overspeed condition,4,TC-SAFE-010-02,Unit Test,Test overspeed detection above threshold
REQ-SAFE-010,Detect overspeed condition,4,TC-SAFE-010-03,Unit Test,Test detection latency < 100ms
REQ-SAFE-010,Detect overspeed condition,4,TC-SAFE-010-04,System Test,Test overspeed detection in operational scenario
```

**Test Types**:
- **Unit Test**: Component-level testing (Phase 5)
- **Integration Test**: Module integration testing (Phase 6)
- **System Test**: System-level validation testing (Phase 7)

**Verification**:
- ✅ All requirements have at least one test case (100% for SIL 3-4)
- ✅ All safety-critical requirements (SIL 3-4) have multiple test cases (boundary, nominal, fault injection)
- ❌ No untestable requirements

**Tool**: `workspace.py trace validate --phase tests --sil 3`

---

### Phase 4: Implementation Phase - Establish Forward Traceability to Code

**Objective**: Link software requirements to code modules

#### Step 4.1: Create Requirements-to-Code Traceability Matrix
- [ ] Implementer (IMP) creates source code
- [ ] For each code module/function:
  - [ ] Identify implemented requirements
  - [ ] Add traceability comment in code: `/* REQ-XXX-YYY */`
  - [ ] Record traceability link: REQ-XXX-YYY → module.c
- [ ] REQ engineer verifies all requirements implemented

**Example - requirements_to_code.csv**:
```csv
Requirement_ID,Requirement_Title,Code_Module,Function_Name,Line_Number
REQ-FUNC-001,Read speed sensor value,sensor.c,sensor_read(),45
REQ-FUNC-002,Validate speed sensor data,sensor.c,sensor_validate(),120
REQ-SAFE-010,Detect overspeed condition,safety_monitor.c,overspeed_detect(),200
REQ-SAFE-011,Activate emergency brake,actuator.c,emergency_brake_activate(),80
```

**Code Example with Traceability Comment**:
```c
/* sensor.c - Speed Sensor Interface Module */

/**
 * @brief Read speed sensor value via SPI interface
 * @req REQ-FUNC-001: Read speed sensor value
 * @return error_t: SUCCESS or error code
 */
error_t sensor_read(uint16_t* speed_value)
{
    /* REQ-FUNC-001: Read sensor via SPI at address 0x4000 */
    error_t err = spi_read(SENSOR_ADDRESS, speed_value);
    if (err != SUCCESS) {
        return ERROR_TIMEOUT;
    }
    
    return SUCCESS;
}
```

**Verification**: All requirements have at least one code implementation

**Tool**: `python tools/code-traceability-extractor.py --source src/ --output requirements_to_code.csv`

---

### Phase 5: Verification Phase - Establish Traceability to Verification Records

**Objective**: Link requirements to verification evidence

#### Step 5.1: Create Requirements-to-Verification Traceability Matrix
- [ ] Verifier (VER) performs verification activities
- [ ] For each requirement:
  - [ ] Record verification method used (Test, Analysis, Inspection, Demonstration)
  - [ ] Record verification result (PASS/FAIL)
  - [ ] Record verification evidence location
  - [ ] Link: REQ-XXX-YYY → VER-RECORD-ZZZ

**Example - requirements_to_verification.csv**:
```csv
Requirement_ID,Requirement_Title,SIL,Verification_Method,Verification_Result,Evidence_Document,Evidence_Location
REQ-FUNC-001,Read speed sensor value,3,Test,PASS,Unit Test Report,Section 4.1.1
REQ-FUNC-002,Validate speed sensor data,3,Test,PASS,Unit Test Report,Section 4.1.2
REQ-SAFE-010,Detect overspeed condition,4,Test,PASS,Safety Test Report,Section 6.3
REQ-SAFE-010,Detect overspeed condition,4,Analysis,PASS,Static Analysis Report,Section 3.2
REQ-CONS-001,Static allocation only,3,Inspection,PASS,Code Review Report,Section 5.1
```

**Verification Methods** (EN 50128 Table A.5):
- **Test**: Execute test cases, measure results
- **Analysis**: Static analysis, formal analysis, mathematical proof
- **Inspection**: Code review, document review, checklist review
- **Demonstration**: Show functionality in operational environment

**Verification Criteria**:
- ✅ All requirements have verification record
- ✅ All verification results are PASS (or issues tracked)
- ✅ All evidence documented and accessible

---

## Traceability Matrix Formats

### Format 1: CSV (Machine-Readable)

**Advantages**:
- Easy to parse programmatically
- Can be processed by scripts
- Easy to import/export from spreadsheets

**Example**: `system_to_software_requirements.csv`

### Format 2: Markdown Table (Human-Readable)

**Advantages**:
- Easy to read in documents
- Can be included in SRS, design documents
- Version controlled with Git

**Example**:
```markdown
## Traceability Matrix: System Requirements to Software Requirements

| System Req | System Requirement Title | Software Req | Software Requirement Title | Coverage |
|------------|--------------------------|--------------|----------------------------|----------|
| SYS-001 | Speed monitoring | REQ-FUNC-001 | Read speed sensor | Full |
| SYS-001 | Speed monitoring | REQ-FUNC-002 | Validate sensor data | Full |
| SYS-002 | Emergency braking | REQ-SAFE-011 | Activate emergency brake | Full |
```

### Format 3: JSON (Structured Data)

**Advantages**:
- Structured, hierarchical data
- Easy to parse programmatically
- Supports complex relationships

**Example**: `traceability.json`
```json
{
  "traceability": [
    {
      "requirement_id": "REQ-FUNC-001",
      "requirement_title": "Read speed sensor value",
      "sil": 3,
      "backward_links": [
        {"type": "system_requirement", "id": "SYS-CTRL-001", "coverage": "full"}
      ],
      "forward_links": [
        {"type": "design", "id": "DESIGN-SENSOR-001", "document": "SAS Section 4.2"},
        {"type": "code", "id": "sensor.c", "function": "sensor_read()", "line": 45},
        {"type": "test", "id": "TC-FUNC-001-01", "result": "PASS"},
        {"type": "test", "id": "TC-FUNC-001-02", "result": "PASS"},
        {"type": "verification", "id": "VER-REQ-001", "result": "PASS"}
      ]
    }
  ]
}
```

---

## Traceability Maintenance

### When to Update Traceability

**Requirements Change**:
- [ ] Update backward traceability (new source or modified source)
- [ ] Update forward traceability (affected design, tests, code)
- [ ] Use change control process (CM agent)

**Design Change**:
- [ ] Update requirements-to-design traceability
- [ ] Verify no new requirements introduced (scope creep)

**Code Change**:
- [ ] Update requirements-to-code traceability
- [ ] Verify all requirements still implemented

**Test Change**:
- [ ] Update requirements-to-test traceability
- [ ] Verify all requirements still tested (100% for SIL 3-4)

**Version Control**:
- [ ] All traceability matrices under version control (Git)
- [ ] Traceability matrices updated with each baseline
- [ ] Traceability included in configuration audits

---

## Traceability Verification Checklist

### Backward Traceability
- [ ] All software requirements have at least one source
- [ ] All system requirements covered by at least one software requirement
- [ ] All hazards mitigated by at least one safety requirement
- [ ] All standard requirements addressed by constraint requirements
- [ ] No orphan requirements
- [ ] 100% coverage for SIL 3-4 (MANDATORY)

### Forward Traceability
- [ ] All requirements addressed by at least one design element
- [ ] All requirements implemented in at least one code module
- [ ] All requirements verified by at least one test case
- [ ] All requirements have verification record (PASS)
- [ ] No untested requirements
- [ ] No unimplemented requirements
- [ ] 100% test coverage for SIL 3-4 (MANDATORY)

### Traceability Quality
- [ ] All traceability links are valid (referenced items exist)
- [ ] No broken links
- [ ] Traceability matrices are up-to-date
- [ ] Traceability matrices under configuration control

---

## Tools

**Traceability Manager** (`workspace.py trace`):
- `workspace.py trace validate` - Validate traceability completeness and correctness
- `workspace.py trace extract` - Extract traceability links from documents and source code
- `workspace.py trace create` - Create traceability matrices
- `workspace.py trace check-gaps` - Find missing traceability links
- `workspace.py trace report` - Generate traceability reports for reviews
- `workspace.py trace query` - Query specific traceability relationships

**Documentation**: See `tools/README_TRACEABILITY.md` for complete command reference

---

## Standard References

- **EN 50128:2011 Section 7.2** - Software Requirements (traceability required)
- **EN 50128:2011 Table A.9** - Software Quality Assurance Techniques
  - Technique 7: Traceability (MANDATORY SIL 3-4, HR SIL 1-2, R SIL 0)
- **EN 50128:2011 Annex D.58** - Traceability Definition

---

## Next Steps

1. Establish backward traceability during requirements phase
2. Maintain forward traceability throughout design, implementation, and test phases
3. Verify traceability completeness before each phase gate
4. Include traceability matrices in Software Requirements Specification (Section 8)
5. Use traceability for impact analysis during change management
