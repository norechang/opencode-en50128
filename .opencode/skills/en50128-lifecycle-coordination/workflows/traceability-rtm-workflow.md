# EN 50128 Traceability and RTM Management Workflow

**Skill**: `en50128-lifecycle-coordination`  
**Workflow**: Traceability and Requirements Traceability Matrix (RTM) Management  
**Role**: Lifecycle Coordinator (COD)  
**EN 50128 Reference**: Section 7.2.4.19 (Traceability), Table A.5 #7 (Traceability MANDATORY SIL 3-4)  
**Purpose**: RTM creation, maintenance, gap detection, bidirectional verification

---

## Table of Contents

1. [RTM Structure](#rtm-structure)
2. [RTM Creation and Initialization](#rtm-creation-and-initialization)
3. [RTM Updates Per Phase](#rtm-updates-per-phase)
4. [Bidirectional Traceability Verification](#bidirectional-traceability-verification)
5. [Gap Detection and Reporting](#gap-detection-and-reporting)
6. [SIL-Specific Traceability Requirements](#sil-specific-traceability-requirements)
7. [Tool Integration](#tool-integration)
8. [RTM Audit](#rtm-audit)
9. [Automation Scripts](#automation-scripts)
10. [Example Scenario](#example-scenario)

---

## RTM Structure

### EN 50128 Traceability Requirements

**EN 50128 Section 7.2.4.19**: "The software requirements shall be traceable throughout the software lifecycle."

**EN 50128 Table A.5 #7**: Traceability is **MANDATORY** for SIL 3-4, **Highly Recommended** for SIL 2, **Recommended** for SIL 0-1.

### Complete Traceability Chain

```
System Requirements (External)
    │
    ↓ (Forward Traceability)
Software Requirements (SRS)
    │
    ↓
Software Architecture (SAS)
    │
    ↓
Software Design (SDS)
    │
    ↓
Source Code (Implementation)
    │
    ↓
Unit Tests
    │
    ↓
Integration Tests
    │
    ↓
System Tests (Validation)
    │
    ↓
Validation Results
    │
    ↑ (Backward Traceability)
    │
Back to System Requirements
```

### RTM Table Structure

**Complete RTM Example**:

| System Req | Software Req | Architecture | Design Module | Source File | Unit Test | Integration Test | System Test | Validation Result | Status |
|------------|--------------|--------------|---------------|-------------|-----------|------------------|-------------|-------------------|--------|
| SYS-001 | SWR-001, SWR-002 | DoorControlModule | door_control | door.c | test_door.c | INT-001 | SYS-001 | VAL-001 (PASS) | ✓ Complete |
| SYS-002 | SWR-003 | SafetyMonitor | safety_monitor | safety.c | test_safety.c | INT-002 | SYS-002 | VAL-002 (PASS) | ✓ Complete |
| SYS-003 | SWR-004, SWR-005 | EmergencyStop | emergency_stop | emergency.c | test_emergency.c | INT-003 | SYS-003 | VAL-003 (PASS) | ✓ Complete |

### RTM Fields

| Field | Description | Phase Created | Mandatory |
|-------|-------------|---------------|-----------|
| **System Req** | System requirement ID | Requirements | Yes |
| **Software Req** | Software requirement ID(s) | Requirements | Yes |
| **Architecture** | Architectural component | Design | Yes (SIL 2+) |
| **Design Module** | Design module name | Design | Yes (SIL 2+) |
| **Source File** | Source code file(s) | Implementation | Yes (SIL 2+) |
| **Unit Test** | Unit test file(s) | Implementation | Yes (SIL 2+) |
| **Integration Test** | Integration test ID(s) | Integration | Yes (SIL 2+) |
| **System Test** | System test ID(s) | Validation | Yes |
| **Validation Result** | Validation result ID | Validation | Yes |
| **Status** | Traceability status | All phases | Yes |

---

## RTM Creation and Initialization

### Purpose

Create initial RTM during Requirements phase (Phase 2).

### RTM Initialization Workflow

```
┌────────────────────────────────────────────────────┐
│ RTM INITIALIZATION WORKFLOW (Phase 2)              │
├────────────────────────────────────────────────────┤
│ 1. Requirements Engineer (REQ) creates SRS         │
│ 2. REQ extracts system requirements                │
│ 3. REQ creates software requirements               │
│ 4. REQ creates RTM with System Req → Software Req  │
│ 5. REQ verifies forward traceability               │
│ 6. REQ verifies backward traceability              │
│ 7. workspace.py trace create (initialization)      │
│ 8. COD validates RTM at gate check                 │
└────────────────────────────────────────────────────┘
```

### Initial RTM Creation

**Phase 2 (Requirements)**: Create RTM with System Req → Software Req mapping.

**Example**: Train Door Control System

**System Requirements** (from System Specification):
- SYS-001: System shall open door on button press within 2 seconds
- SYS-002: System shall close door automatically after 10 seconds
- SYS-003: System shall detect obstructions during closing
- SYS-004: System shall stop closing if obstruction detected
- SYS-005: System shall provide emergency stop function

**Software Requirements** (in SRS):
- SWR-001: Software shall monitor door open button state every 100ms
- SWR-002: Software shall command door motor to open position within 1.8 seconds
- SWR-003: Software shall start close timer after door fully open
- SWR-004: Software shall command door motor to close position after 10-second timer expires
- SWR-005: Software shall monitor obstruction sensor every 50ms
- SWR-006: Software shall halt door motor immediately if obstruction detected
- SWR-007: Software shall activate emergency stop on emergency button press

**Initial RTM** (Phase 2):

| System Req | Software Req | Status |
|------------|--------------|--------|
| SYS-001 | SWR-001, SWR-002 | ✓ Traced |
| SYS-002 | SWR-003, SWR-004 | ✓ Traced |
| SYS-003 | SWR-005 | ✓ Traced |
| SYS-004 | SWR-006 | ✓ Traced |
| SYS-005 | SWR-007 | ✓ Traced |

### Tool Integration: RTM Creation

```bash
# Initialize RTM
workspace.py trace create --phase requirements

# Add system requirement
workspace.py trace add --type system_req --id SYS-001 --description "System shall open door on button press within 2 seconds"

# Add software requirement with traceability
workspace.py trace add --type software_req --id SWR-001 --description "Software shall monitor door open button state every 100ms" --parent SYS-001

workspace.py trace add --type software_req --id SWR-002 --description "Software shall command door motor to open position within 1.8 seconds" --parent SYS-001

# Validate initial RTM
workspace.py trace validate --phase requirements

# Generate RTM report
workspace.py trace report --phase requirements --output docs/RTM.md
```

---

## RTM Updates Per Phase

### Purpose

Update RTM as lifecycle progresses through phases.

### Phase-by-Phase RTM Updates

#### Phase 3 (Design): Add Architecture and Design Links

**Workflow**:
1. Designer (DES) creates Software Architecture Specification (SAS)
2. Designer creates Software Design Specification (SDS)
3. Designer updates RTM with Architecture and Design modules
4. COD validates RTM at design gate

**Tool Integration**:

```bash
# Add architecture component
workspace.py trace add --type architecture --id DoorControlModule --description "Door control architectural component" --parent SWR-001,SWR-002

# Add design module
workspace.py trace add --type design --id door_control --description "Door control design module" --parent DoorControlModule

# Validate design traceability
workspace.py trace validate --phase design

# Check forward traceability: Software Req → Design
workspace.py trace check-forward --from software_req --to design
```

**Updated RTM** (Phase 3):

| System Req | Software Req | Architecture | Design Module | Status |
|------------|--------------|--------------|---------------|--------|
| SYS-001 | SWR-001, SWR-002 | DoorControlModule | door_control | ✓ Traced |
| SYS-002 | SWR-003, SWR-004 | DoorControlModule | door_control | ✓ Traced |
| SYS-003 | SWR-005 | ObstructionDetector | obstruction | ✓ Traced |
| SYS-004 | SWR-006 | SafetyMonitor | safety_monitor | ✓ Traced |
| SYS-005 | SWR-007 | EmergencyStop | emergency_stop | ✓ Traced |

#### Phase 4 (Implementation): Add Source Code and Unit Tests

**Workflow**:
1. Implementer (IMP) creates source code
2. Tester (TST) creates unit tests
3. IMP/TST update RTM with source files and unit tests
4. COD validates RTM at implementation gate

**Tool Integration**:

```bash
# Add source file
workspace.py trace add --type code --id door.c --description "Door control implementation" --parent door_control

# Add unit test
workspace.py trace add --type unit_test --id test_door.c --description "Door control unit tests" --parent door.c

# Validate implementation traceability
workspace.py trace validate --phase implementation

# Check backward traceability: Code → Software Req
workspace.py trace check-backward --from code --to software_req
```

**Updated RTM** (Phase 4):

| System Req | Software Req | Design Module | Source File | Unit Test | Status |
|------------|--------------|---------------|-------------|-----------|--------|
| SYS-001 | SWR-001, SWR-002 | door_control | door.c | test_door.c | ✓ Traced |
| SYS-002 | SWR-003, SWR-004 | door_control | door.c | test_door.c | ✓ Traced |
| SYS-003 | SWR-005 | obstruction | obstruction.c | test_obstruction.c | ✓ Traced |
| SYS-004 | SWR-006 | safety_monitor | safety.c | test_safety.c | ✓ Traced |
| SYS-005 | SWR-007 | emergency_stop | emergency.c | test_emergency.c | ✓ Traced |

#### Phase 5 (Integration): Add Integration Tests

**Workflow**:
1. Integrator (INT) creates integration tests
2. INT updates RTM with integration test IDs
3. COD validates RTM at integration gate

**Tool Integration**:

```bash
# Add integration test
workspace.py trace add --type integration_test --id INT-001 --description "Door open/close integration test" --parent door.c,obstruction.c

# Validate integration traceability
workspace.py trace validate --phase integration
```

#### Phase 6 (Validation): Add System Tests and Results

**Workflow**:
1. Validator (VAL) executes system tests
2. VAL records validation results
3. VAL updates RTM with system tests and results
4. COD validates 100% requirements coverage (MANDATORY SIL 3-4)

**Tool Integration**:

```bash
# Add system test
workspace.py trace add --type system_test --id SYS-TEST-001 --description "System test for door opening" --parent SWR-001,SWR-002

# Add validation result
workspace.py trace add --type validation_result --id VAL-001 --description "Validation result: PASS" --parent SYS-TEST-001

# Validate end-to-end traceability
workspace.py trace validate --phase validation --check-coverage 100

# Generate final RTM
workspace.py trace report --output docs/RTM-Final.md
```

**Final RTM** (Phase 6):

| System Req | Software Req | Design | Source | Unit Test | Integration Test | System Test | Validation Result | Status |
|------------|--------------|--------|--------|-----------|------------------|-------------|-------------------|--------|
| SYS-001 | SWR-001, SWR-002 | door_control | door.c | test_door.c | INT-001 | SYS-TEST-001 | VAL-001 (PASS) | ✓ Complete |

---

## Bidirectional Traceability Verification

### Purpose

Verify forward and backward traceability at each phase gate.

### Forward Traceability

**Definition**: Every artifact at level N traces to at least one artifact at level N+1.

**Examples**:
- Every system requirement traces to at least one software requirement
- Every software requirement traces to at least one design module
- Every design module traces to at least one source file
- Every source file traces to at least one unit test
- Every requirement traces to at least one system test

### Backward Traceability

**Definition**: Every artifact at level N+1 traces back to at least one artifact at level N.

**Examples**:
- Every software requirement traces back to at least one system requirement
- Every design module traces back to at least one software requirement
- Every source file traces back to at least one design module
- Every unit test traces back to at least one requirement
- Every system test traces back to at least one requirement

### Bidirectional Verification Algorithm

```python
def verify_bidirectional_traceability(rtm, from_type, to_type):
    """
    Verify bidirectional traceability between two artifact types
    
    Args:
        rtm: Requirements Traceability Matrix
        from_type: Source artifact type (e.g., 'software_req')
        to_type: Target artifact type (e.g., 'design')
    
    Returns:
        dict with forward_coverage, backward_coverage, orphan_from, orphan_to
    """
    
    # Extract artifacts
    from_artifacts = rtm.get_artifacts(from_type)
    to_artifacts = rtm.get_artifacts(to_type)
    
    # Forward traceability: from → to
    from_with_links = set()
    for from_id in from_artifacts:
        links = rtm.get_links(from_id, to_type)
        if links:
            from_with_links.add(from_id)
    
    forward_coverage = len(from_with_links) / len(from_artifacts) * 100.0 if from_artifacts else 0.0
    orphan_from = set(from_artifacts) - from_with_links
    
    # Backward traceability: to → from
    to_with_links = set()
    for to_id in to_artifacts:
        links = rtm.get_reverse_links(to_id, from_type)
        if links:
            to_with_links.add(to_id)
    
    backward_coverage = len(to_with_links) / len(to_artifacts) * 100.0 if to_artifacts else 0.0
    orphan_to = set(to_artifacts) - to_with_links
    
    return {
        'forward_coverage': forward_coverage,
        'backward_coverage': backward_coverage,
        'orphan_from': list(orphan_from),
        'orphan_to': list(orphan_to),
        'bidirectional': forward_coverage == 100.0 and backward_coverage == 100.0
    }
```

### Tool Integration: Bidirectional Verification

```bash
# Verify forward traceability: System Req → Software Req
workspace.py trace check-forward --from system_req --to software_req

# Output:
# Forward Traceability: System Req → Software Req
# Coverage: 100.0% (5/5 system requirements traced)
# Orphan system requirements: None

# Verify backward traceability: Software Req → System Req
workspace.py trace check-backward --from software_req --to system_req

# Output:
# Backward Traceability: Software Req → System Req
# Coverage: 100.0% (7/7 software requirements traced back)
# Orphan software requirements: None

# Verify bidirectional: Software Req ↔ Design
workspace.py trace check-bidirectional --from software_req --to design

# Output:
# Bidirectional Traceability: Software Req ↔ Design
# Forward Coverage: 100.0% (7/7 software requirements traced to design)
# Backward Coverage: 100.0% (5/5 design modules traced to requirements)
# Bidirectional: ✓ Complete
```

---

## Gap Detection and Reporting

### Purpose

Identify and report traceability gaps.

### Gap Types

1. **Uncovered Requirements**: Requirements with no design/code/test
2. **Orphan Artifacts**: Design/code/tests not traced to requirements
3. **Missing Tests**: Requirements with no system tests
4. **Untested Code**: Source files with no unit tests
5. **Incomplete Validation**: System tests with no validation results

### Gap Detection Algorithm

```python
def detect_traceability_gaps(rtm):
    """Detect all traceability gaps"""
    
    gaps = {
        'uncovered_requirements': [],
        'orphan_design': [],
        'orphan_code': [],
        'untested_requirements': [],
        'untested_code': [],
        'unvalidated_tests': []
    }
    
    # 1. Uncovered requirements (no design/code)
    for req in rtm.get_artifacts('software_req'):
        design_links = rtm.get_links(req, 'design')
        if not design_links:
            gaps['uncovered_requirements'].append({
                'id': req,
                'type': 'no_design',
                'description': rtm.get_description(req)
            })
        else:
            # Has design, check for code
            code_links = []
            for design_id in design_links:
                code_links.extend(rtm.get_links(design_id, 'code'))
            if not code_links:
                gaps['uncovered_requirements'].append({
                    'id': req,
                    'type': 'no_code',
                    'description': rtm.get_description(req)
                })
    
    # 2. Orphan design (not traced to requirements)
    for design_id in rtm.get_artifacts('design'):
        req_links = rtm.get_reverse_links(design_id, 'software_req')
        if not req_links:
            gaps['orphan_design'].append({
                'id': design_id,
                'description': rtm.get_description(design_id)
            })
    
    # 3. Orphan code (not traced to design)
    for code_id in rtm.get_artifacts('code'):
        design_links = rtm.get_reverse_links(code_id, 'design')
        if not design_links:
            gaps['orphan_code'].append({
                'id': code_id,
                'file': code_id
            })
    
    # 4. Untested requirements (no system tests)
    for req in rtm.get_artifacts('software_req'):
        test_links = rtm.get_links(req, 'system_test')
        if not test_links:
            gaps['untested_requirements'].append({
                'id': req,
                'description': rtm.get_description(req)
            })
    
    # 5. Untested code (no unit tests)
    for code_id in rtm.get_artifacts('code'):
        test_links = rtm.get_links(code_id, 'unit_test')
        if not test_links:
            gaps['untested_code'].append({
                'id': code_id,
                'file': code_id
            })
    
    # 6. Unvalidated tests (no validation results)
    for test_id in rtm.get_artifacts('system_test'):
        validation_links = rtm.get_links(test_id, 'validation_result')
        if not validation_links:
            gaps['unvalidated_tests'].append({
                'id': test_id,
                'description': rtm.get_description(test_id)
            })
    
    return gaps
```

### Gap Report Format

```
═══════════════════════════════════════════════════════
TRACEABILITY GAP REPORT
═══════════════════════════════════════════════════════

Project: Train Door Control System
SIL Level: 3 (100% traceability MANDATORY)
Report Date: 2026-02-20

[✗] Uncovered Requirements (1 gap)
  ✗ SWR-008: Software shall log door events
    - Type: No design
    - Impact: High
    - Action: Create design module for event logging

[✓] Orphan Design (0 gaps)
  ✓ All design modules traced to requirements

[✗] Orphan Code (2 gaps)
  ✗ src/util/logger.c
    - Not traced to design module
    - Action: Add logger design module or remove file
  ✗ src/util/debug.c
    - Not traced to design module
    - Action: Justification required (debug utility)

[✗] Untested Requirements (1 gap)
  ✗ SWR-006: Software shall halt door motor if obstruction detected
    - No system test
    - Action: Create SYS-TEST-006

[✓] Untested Code (0 gaps)
  ✓ All source files have unit tests

[✗] Unvalidated Tests (3 gaps)
  ✗ SYS-TEST-005: Emergency stop test
    - No validation result
    - Action: Execute test, record result
  ... (2 more)

═══════════════════════════════════════════════════════
SUMMARY
═══════════════════════════════════════════════════════

Total Gaps: 7
  - Critical: 2 (Uncovered requirements, Untested requirements)
  - High: 2 (Orphan code)
  - Medium: 3 (Unvalidated tests)

Traceability Status: ✗ INCOMPLETE (93.2% complete, target: 100% for SIL 3)

Required Actions:
  1. Add design module for SWR-008 (event logging)
  2. Create system test SYS-TEST-006 (obstruction halt)
  3. Justify or remove orphan code files
  4. Execute and record validation results for 3 system tests
```

### Tool Integration: Gap Detection

```bash
# Detect all gaps
workspace.py trace check-gaps

# Detect specific gap type
workspace.py trace check-gaps --type uncovered_requirements
workspace.py trace check-gaps --type orphan_code
workspace.py trace check-gaps --type untested_requirements

# Generate gap report
workspace.py trace check-gaps --report docs/traceability/Gap-Report.md

# Calculate traceability coverage
workspace.py trace coverage
# Output:
# Traceability Coverage:
#   System Req → Software Req: 100.0%
#   Software Req → Design: 98.5% (1 gap)
#   Design → Code: 100.0%
#   Code → Unit Tests: 100.0%
#   Requirements → System Tests: 98.0% (1 gap)
#   Overall: 93.2%
```

---

## SIL-Specific Traceability Requirements

### Traceability Requirements by SIL

| SIL Level | Traceability | Coverage Threshold | Justification for Gaps |
|-----------|--------------|-------------------|------------------------|
| **SIL 0** | Recommended | 80% (recommended) | Optional |
| **SIL 1** | Recommended | 80% (recommended) | Optional |
| **SIL 2** | Highly Recommended | 95% (highly recommended) | Recommended |
| **SIL 3** | **MANDATORY** | **100%** | **Required for all gaps** |
| **SIL 4** | **MANDATORY** | **100%** | **Required for all gaps** |

### SIL 3-4 Traceability Enforcement

**COD enforces**:

1. **100% forward traceability**: Every requirement must trace forward to tests
2. **100% backward traceability**: Every artifact must trace back to requirements
3. **No orphan artifacts**: All design/code/tests must be traceable
4. **Gap justification**: Any gaps require safety justification
5. **Independent verification**: RTM verified by independent VER

**Gate Check Enforcement**:

```python
def check_traceability_gate_sil3(rtm):
    """Check traceability for SIL 3-4 gate"""
    
    # Calculate coverage
    coverage = rtm.calculate_coverage()
    
    # SIL 3-4: Require 100% coverage
    if coverage['overall'] < 100.0:
        return {
            'passed': False,
            'reason': f"Traceability coverage {coverage['overall']}% < 100% (SIL 3 MANDATORY)",
            'gaps': rtm.detect_gaps()
        }
    
    # Check for orphan artifacts
    orphans = rtm.find_orphans()
    if orphans['total'] > 0:
        # Check if all orphans justified
        unjustified = [o for o in orphans['list'] if not o['justified']]
        if unjustified:
            return {
                'passed': False,
                'reason': f"{len(unjustified)} orphan artifacts without justification",
                'orphans': unjustified
            }
    
    return {
        'passed': True,
        'coverage': coverage,
        'orphans_justified': orphans['total']
    }
```

---

## Tool Integration

### workspace.py trace Commands

Complete command reference for traceability management:

```bash
# 1. Initialize RTM
workspace.py trace create --phase requirements

# 2. Add artifacts with traceability links
workspace.py trace add --type software_req --id SWR-001 --description "..." --parent SYS-001
workspace.py trace add --type design --id door_control --description "..." --parent SWR-001,SWR-002
workspace.py trace add --type code --id door.c --description "..." --parent door_control
workspace.py trace add --type unit_test --id test_door.c --description "..." --parent door.c
workspace.py trace add --type system_test --id SYS-TEST-001 --description "..." --parent SWR-001
workspace.py trace add --type validation_result --id VAL-001 --description "PASS" --parent SYS-TEST-001

# 3. Validate traceability
workspace.py trace validate                      # Validate all
workspace.py trace validate --phase design       # Validate specific phase

# 4. Check forward/backward traceability
workspace.py trace check-forward --from software_req --to design
workspace.py trace check-backward --from design --to software_req
workspace.py trace check-bidirectional --from software_req --to design

# 5. Detect gaps
workspace.py trace check-gaps                    # All gaps
workspace.py trace check-gaps --type uncovered_requirements
workspace.py trace check-gaps --report docs/traceability/Gap-Report.md

# 6. Calculate coverage
workspace.py trace coverage
workspace.py trace coverage --from software_req --to design

# 7. Generate reports
workspace.py trace report --output docs/RTM.md
workspace.py trace report --phase validation --output docs/RTM-Final.md

# 8. Query traceability
workspace.py trace query --id SWR-001           # Find all links for SWR-001
workspace.py trace query --id SWR-001 --direction forward
workspace.py trace query --id door.c --direction backward

# 9. Export RTM
workspace.py trace export --format csv --output RTM.csv
workspace.py trace export --format json --output RTM.json
workspace.py trace export --format html --output RTM.html
```

---

## RTM Audit

### Purpose

Independent verification of RTM completeness and accuracy (MANDATORY SIL 3-4).

### RTM Audit Checklist

**Audited by**: Verifier (VER) - independent for SIL 3-4

**Audit Criteria**:

1. **RTM Completeness**:
   - [ ] All system requirements in RTM
   - [ ] All software requirements in RTM
   - [ ] All design modules in RTM
   - [ ] All source files in RTM
   - [ ] All tests in RTM
   - [ ] All validation results in RTM

2. **Forward Traceability**:
   - [ ] 100% system requirements → software requirements (SIL 3-4)
   - [ ] 100% software requirements → design (SIL 3-4)
   - [ ] 100% design → code (SIL 3-4)
   - [ ] 100% code → unit tests (SIL 3-4)
   - [ ] 100% requirements → system tests (SIL 3-4)

3. **Backward Traceability**:
   - [ ] 100% software requirements → system requirements (SIL 3-4)
   - [ ] 100% design → software requirements (SIL 3-4)
   - [ ] 100% code → design (SIL 3-4)
   - [ ] 100% tests → requirements (SIL 3-4)

4. **Accuracy**:
   - [ ] All traceability links accurate (no incorrect links)
   - [ ] All artifact IDs valid (no broken links)
   - [ ] All descriptions accurate

5. **Gap Justification**:
   - [ ] All orphan artifacts justified
   - [ ] All uncovered requirements justified (or none for SIL 3-4)

### RTM Audit Report

```markdown
# Requirements Traceability Matrix Audit Report

**Project**: Train Door Control System  
**SIL Level**: 3  
**Audit Date**: 2026-02-25  
**Auditor**: John Smith (Verifier, Independent)

## Audit Summary

- **RTM Completeness**: ✓ Complete
- **Forward Traceability**: ✓ 100%
- **Backward Traceability**: ✓ 100%
- **Accuracy**: ✓ Verified
- **Gap Justification**: ✓ All gaps justified (2 orphan artifacts)

## Audit Findings

### 1. RTM Completeness

✓ All 5 system requirements present in RTM
✓ All 7 software requirements present in RTM
✓ All 5 design modules present in RTM
✓ All 8 source files present in RTM
✓ All 8 unit tests present in RTM
✓ All 5 integration tests present in RTM
✓ All 7 system tests present in RTM
✓ All 7 validation results present in RTM

### 2. Forward Traceability

✓ System Req → Software Req: 100% (5/5)
✓ Software Req → Design: 100% (7/7)
✓ Design → Code: 100% (5/5)
✓ Code → Unit Tests: 100% (8/8)
✓ Requirements → System Tests: 100% (7/7)

### 3. Backward Traceability

✓ Software Req → System Req: 100% (7/7)
✓ Design → Software Req: 100% (5/5)
✓ Code → Design: 100% (8/8)
✓ Unit Tests → Code: 100% (8/8)
✓ System Tests → Requirements: 100% (7/7)

### 4. Accuracy

Sampled 20 traceability links (random selection):
- ✓ All 20 links verified as accurate
- ✓ All artifact IDs valid
- ✓ All descriptions match artifacts

### 5. Gap Justification

Identified gaps:
- 2 orphan artifacts (debug.c, logger.c)

Justifications reviewed:
- ✓ debug.c: Justified as debug utility (not part of safety software)
- ✓ logger.c: Justified as diagnostic utility (not safety-critical)

## Conclusion

The Requirements Traceability Matrix is **COMPLETE** and **ACCURATE** for SIL 3.

- 100% forward traceability verified
- 100% backward traceability verified
- All orphan artifacts justified
- No uncovered requirements
- RTM ready for deployment

**Verification Status**: ✓ APPROVED

**Signed**: John Smith, Verifier (Independent)  
**Date**: 2026-02-25
```

---

## Automation Scripts

### RTM Gap Detector Script

**Script**: `tools/rtm_gap_detector.py` (~250 lines)

```python
#!/usr/bin/env python3
"""
RTM Gap Detector
Detect traceability gaps in Requirements Traceability Matrix
"""

import json
import sys
from pathlib import Path

class RTMGapDetector:
    def __init__(self, rtm_file):
        self.rtm_file = Path(rtm_file)
        self.rtm = self._load_rtm()
        self.gaps = {
            'uncovered_requirements': [],
            'orphan_design': [],
            'orphan_code': [],
            'untested_requirements': [],
            'untested_code': [],
            'unvalidated_tests': []
        }
    
    def _load_rtm(self):
        """Load RTM from JSON file"""
        with open(self.rtm_file, 'r') as f:
            return json.load(f)
    
    def detect_all_gaps(self):
        """Detect all traceability gaps"""
        self.detect_uncovered_requirements()
        self.detect_orphan_design()
        self.detect_orphan_code()
        self.detect_untested_requirements()
        self.detect_untested_code()
        self.detect_unvalidated_tests()
        return self.gaps
    
    def detect_uncovered_requirements(self):
        """Detect requirements with no design/code"""
        for req in self.rtm.get('software_requirements', []):
            req_id = req['id']
            # Check if requirement has design link
            has_design = any(
                req_id in d.get('parent_requirements', [])
                for d in self.rtm.get('design', [])
            )
            if not has_design:
                self.gaps['uncovered_requirements'].append({
                    'id': req_id,
                    'type': 'no_design',
                    'description': req.get('description', '')
                })
        
        return self.gaps['uncovered_requirements']
    
    def detect_orphan_design(self):
        """Detect design modules not traced to requirements"""
        for design in self.rtm.get('design', []):
            parent_reqs = design.get('parent_requirements', [])
            if not parent_reqs:
                self.gaps['orphan_design'].append({
                    'id': design['id'],
                    'description': design.get('description', '')
                })
        
        return self.gaps['orphan_design']
    
    def detect_orphan_code(self):
        """Detect source files not traced to design"""
        for code in self.rtm.get('code', []):
            parent_design = code.get('parent_design', [])
            if not parent_design:
                self.gaps['orphan_code'].append({
                    'id': code['id'],
                    'file': code.get('file', '')
                })
        
        return self.gaps['orphan_code']
    
    def detect_untested_requirements(self):
        """Detect requirements with no system tests"""
        for req in self.rtm.get('software_requirements', []):
            req_id = req['id']
            # Check if requirement has system test link
            has_test = any(
                req_id in t.get('parent_requirements', [])
                for t in self.rtm.get('system_tests', [])
            )
            if not has_test:
                self.gaps['untested_requirements'].append({
                    'id': req_id,
                    'description': req.get('description', '')
                })
        
        return self.gaps['untested_requirements']
    
    def detect_untested_code(self):
        """Detect source files with no unit tests"""
        for code in self.rtm.get('code', []):
            code_id = code['id']
            # Check if code has unit test link
            has_test = any(
                code_id in t.get('parent_code', [])
                for t in self.rtm.get('unit_tests', [])
            )
            if not has_test:
                self.gaps['untested_code'].append({
                    'id': code_id,
                    'file': code.get('file', '')
                })
        
        return self.gaps['untested_code']
    
    def detect_unvalidated_tests(self):
        """Detect system tests with no validation results"""
        for test in self.rtm.get('system_tests', []):
            test_id = test['id']
            # Check if test has validation result
            has_result = any(
                test_id in r.get('parent_test', [])
                for r in self.rtm.get('validation_results', [])
            )
            if not has_result:
                self.gaps['unvalidated_tests'].append({
                    'id': test_id,
                    'description': test.get('description', '')
                })
        
        return self.gaps['unvalidated_tests']
    
    def generate_gap_report(self):
        """Generate human-readable gap report"""
        report = []
        report.append("═" * 60)
        report.append("TRACEABILITY GAP REPORT")
        report.append("═" * 60)
        report.append("")
        
        total_gaps = sum(len(gaps) for gaps in self.gaps.values())
        
        # Uncovered requirements
        if self.gaps['uncovered_requirements']:
            report.append(f"[✗] Uncovered Requirements ({len(self.gaps['uncovered_requirements'])} gaps)")
            for gap in self.gaps['uncovered_requirements'][:5]:
                report.append(f"  ✗ {gap['id']}: {gap['description'][:50]}...")
                report.append(f"    - Type: {gap['type']}")
        else:
            report.append("[✓] Uncovered Requirements (0 gaps)")
        report.append("")
        
        # Orphan design
        if self.gaps['orphan_design']:
            report.append(f"[✗] Orphan Design ({len(self.gaps['orphan_design'])} gaps)")
            for gap in self.gaps['orphan_design'][:5]:
                report.append(f"  ✗ {gap['id']}: {gap['description'][:50]}...")
        else:
            report.append("[✓] Orphan Design (0 gaps)")
        report.append("")
        
        # Orphan code
        if self.gaps['orphan_code']:
            report.append(f"[✗] Orphan Code ({len(self.gaps['orphan_code'])} gaps)")
            for gap in self.gaps['orphan_code'][:5]:
                report.append(f"  ✗ {gap['file']}")
        else:
            report.append("[✓] Orphan Code (0 gaps)")
        report.append("")
        
        # Untested requirements
        if self.gaps['untested_requirements']:
            report.append(f"[✗] Untested Requirements ({len(self.gaps['untested_requirements'])} gaps)")
            for gap in self.gaps['untested_requirements'][:5]:
                report.append(f"  ✗ {gap['id']}: {gap['description'][:50]}...")
        else:
            report.append("[✓] Untested Requirements (0 gaps)")
        report.append("")
        
        # Untested code
        if self.gaps['untested_code']:
            report.append(f"[✗] Untested Code ({len(self.gaps['untested_code'])} gaps)")
            for gap in self.gaps['untested_code'][:5]:
                report.append(f"  ✗ {gap['file']}")
        else:
            report.append("[✓] Untested Code (0 gaps)")
        report.append("")
        
        # Unvalidated tests
        if self.gaps['unvalidated_tests']:
            report.append(f"[✗] Unvalidated Tests ({len(self.gaps['unvalidated_tests'])} gaps)")
            for gap in self.gaps['unvalidated_tests'][:5]:
                report.append(f"  ✗ {gap['id']}: {gap['description'][:50]}...")
        else:
            report.append("[✓] Unvalidated Tests (0 gaps)")
        report.append("")
        
        # Summary
        report.append("═" * 60)
        report.append("SUMMARY")
        report.append("═" * 60)
        report.append(f"Total Gaps: {total_gaps}")
        report.append("")
        
        return "\n".join(report)

def main():
    import argparse
    parser = argparse.ArgumentParser(description='RTM Gap Detector')
    parser.add_argument('rtm_file', help='RTM JSON file')
    parser.add_argument('--json', action='store_true', help='JSON output')
    parser.add_argument('--report', help='Generate gap report file')
    
    args = parser.parse_args()
    
    detector = RTMGapDetector(args.rtm_file)
    gaps = detector.detect_all_gaps()
    
    if args.json:
        print(json.dumps(gaps, indent=2))
    else:
        report = detector.generate_gap_report()
        print(report)
        
        if args.report:
            with open(args.report, 'w') as f:
                f.write(report)
            print(f"\n✓ Gap report written to {args.report}")
    
    total_gaps = sum(len(g) for g in gaps.values())
    sys.exit(0 if total_gaps == 0 else 1)

if __name__ == '__main__':
    main()
```

---

## Example Scenario

### Complete RTM for SIL 3 Door Control System

**Phase 2 (Requirements)**: Initialize RTM

```bash
workspace.py trace create --phase requirements

# Add system requirements
workspace.py trace add --type system_req --id SYS-001 --description "System shall open door on button press within 2 seconds"
workspace.py trace add --type system_req --id SYS-002 --description "System shall close door automatically after 10 seconds"

# Add software requirements with traceability
workspace.py trace add --type software_req --id SWR-001 --description "Software shall monitor door open button state every 100ms" --parent SYS-001
workspace.py trace add --type software_req --id SWR-002 --description "Software shall command door motor to open position within 1.8 seconds" --parent SYS-001

# Validate
workspace.py trace validate --phase requirements
# Output: ✓ Forward traceability: 100% (2/2 system requirements)
```

**Phase 3 (Design)**: Add design traceability

```bash
workspace.py trace add --type architecture --id DoorControlModule --description "Door control architectural component" --parent SWR-001,SWR-002
workspace.py trace add --type design --id door_control --description "Door control design module" --parent DoorControlModule

workspace.py trace validate --phase design
# Output: ✓ Software Req → Design: 100% (2/2 requirements)
```

**Phase 4 (Implementation)**: Add code traceability

```bash
workspace.py trace add --type code --id door.c --description "Door control implementation" --parent door_control
workspace.py trace add --type unit_test --id test_door.c --description "Door control unit tests" --parent door.c

workspace.py trace validate --phase implementation
# Output: ✓ Design → Code: 100%, Code → Unit Tests: 100%
```

**Phase 6 (Validation)**: Complete end-to-end traceability

```bash
workspace.py trace add --type system_test --id SYS-TEST-001 --description "System test for door opening" --parent SWR-001,SWR-002
workspace.py trace add --type validation_result --id VAL-001 --description "Validation result: PASS" --parent SYS-TEST-001

workspace.py trace validate --phase validation --check-coverage 100
# Output: ✓ End-to-end traceability: 100% (SIL 3 compliant)

workspace.py trace report --output docs/RTM-Final.md
```

---

## Summary

This workflow provides:

1. **Complete RTM structure** - System Req → Software Req → Design → Code → Tests → Validation
2. **RTM creation and initialization** - Phase 2 (Requirements)
3. **RTM updates per phase** - Design, Implementation, Integration, Validation
4. **Bidirectional traceability verification** - Forward and backward coverage
5. **Gap detection and reporting** - 6 gap types, automated detection
6. **SIL-specific requirements** - 100% coverage mandatory SIL 3-4
7. **Tool integration** - Complete workspace.py trace command reference
8. **RTM audit** - Independent verification (MANDATORY SIL 3-4)
9. **Automation scripts** - RTM gap detector, coverage calculator
10. **Complete example** - SIL 3 door control system RTM

**Key Principles**:
- **100% traceability for SIL 3-4** (MANDATORY per EN 50128 Table A.5)
- **Bidirectional verification** at every phase gate
- **Automated gap detection** to identify issues early
- **Independent RTM audit** for SIL 3-4
- **workspace.py integration** for all traceability operations

---

**Related Workflows**:
- `phase-gate-management-workflow.md` - Gate criteria include traceability verification
- `v-model-orchestration-workflow.md` - Phase transitions update RTM
- `iteration-change-management-workflow.md` - Iterations maintain traceability

**EN 50128 References**:
- Section 7.2.4.19: Traceability requirements
- Table A.5 #7: Traceability (MANDATORY SIL 3-4, HR SIL 2, R SIL 0-1)
- Section 5.3.2.13: Traceability throughout lifecycle
