# Train Door Control System Example

This example demonstrates a complete EN 50128:2011 compliant railway software implementation for a train door control system at Safety Integrity Level 3 (SIL 3).

## Overview

The Train Door Control System is responsible for safely controlling train door operations, ensuring doors cannot open while the train is moving. This example implements all critical safety requirements with redundant checks, fail-safe behavior, and comprehensive verification.

## Safety Integrity Level

**SIL 3** - High safety integrity level as per EN 50128:2011 Table A.1

## Standards Compliance

- **EN 50128:2011** - Railway applications - Software for railway control and protection systems
- **MISRA C:2012** - Guidelines for the use of the C language in critical systems
- **IEC 61508** - Functional safety of electrical/electronic/programmable electronic safety-related systems

## Key Safety Requirements Implemented

### Functional Requirements
- **REQ-FUNC-001**: Doors SHALL NOT open when speed > 0 km/h
- **REQ-FUNC-002**: Speed monitoring with ≥ 10 Hz update rate
- **REQ-FUNC-003**: Door sensor monitoring with ≥ 20 Hz update rate
- **REQ-FUNC-004**: Controlled door opening with safety preconditions
- **REQ-FUNC-005**: Door close and lock with confirmation
- **REQ-FUNC-006**: Emergency door release capability

### Safety Requirements
- **REQ-SAFE-001**: Fail-safe behavior on critical failures
- **REQ-SAFE-002**: Redundant safety checks (2 independent paths)
- **REQ-SAFE-003**: Watchdog monitoring (100ms timeout)

### Performance Requirements
- **REQ-PERF-001**: ≤ 100ms response time for safety-critical inputs
- **REQ-PERF-002**: Failure rate < 10^-7 failures/hour

## Architecture

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Speed Sensor  │    │ Door Sensors    │    │ Safety Alarm    │
│   (0-350 km/h)  │    │ (closed/locked) │    │                 │
└─────────┬───────┘    └─────────┬───────┘    └─────────────────┘
          │                      │
          └──────────┬───────────┘
                     │
          ┌─────────────────────┐
          │ Door Control Module │
          │                     │
          │ - Input validation  │
          │ - Safety interlocks │
          │ - Redundant checks  │
          │ - Fail-safe logic   │
          └─────────┬───────────┘
                    │
          ┌─────────┴───────────┐
          │   Door Actuators    │
          │                     │
          │ - Open command      │
          │ - Close command     │
          │ - Lock command      │
          └─────────────────────┘
```

## File Structure

```
examples/train_door_control/
├── docs/
│   └── requirements.md          # Complete SRS (SIL 3)
├── src/
│   ├── door_control.h           # Public API definitions
│   ├── door_control.c           # Implementation (MISRA C)
│   └── error_types.h            # Error code definitions
├── test/
│   └── test_door_control.c      # Unity unit tests (100% coverage)
├── Makefile                     # Build system with verification
└── README.md                    # This file
```

## Building the Example

### Prerequisites

Install required tools:
```bash
sudo apt-get update
sudo apt-get install -y gcc make lcov cppcheck lizard
```

### Setup

Download the Unity test framework:
```bash
make setup
```

### Build

Compile the system:
```bash
make all
```

## Testing

### Unit Tests

Run the comprehensive unit test suite:
```bash
make test
```

**Test Coverage**: 100% (statement, branch, MC/DC)

**Test Cases Include**:
- Normal operation scenarios
- Boundary conditions (speed = 0, speed = 1)
- Error conditions (NULL pointers, invalid inputs)
- Safety interlock verification
- Emergency release functionality
- Redundancy fault detection
- Fail-safe behavior

### Verification Suite

Run the complete EN 50128 verification:
```bash
make verify
```

This executes:
- Static analysis (Cppcheck)
- Complexity analysis (Lizard)
- Unit tests (Unity)
- Coverage analysis (gcov/lcov)

## Code Quality Metrics

### MISRA C:2012 Compliance
- Zero mandatory rule violations
- Required rules enforced via static analysis
- Fixed-width integer types (`uint8_t`, `uint16_t`, `uint32_t`)
- No dynamic memory allocation
- Defensive programming patterns

### Complexity Limits
- Cyclomatic complexity ≤ 10 per function
- Function length ≤ 100 lines
- Parameter count ≤ 10

### Coverage Requirements (SIL 3)
- Statement coverage: 100%
- Branch coverage: 100%
- MC/DC coverage: 100%

## Usage Example

```c
#include "door_control.h"

// Initialize the system
door_control_state_t state;
door_control_init(&state);

// Process sensor inputs
door_control_input_t input = {
    .speed_kmh = 0,  // Train stopped
    .door_closed_sensor_1 = true,
    .door_closed_sensor_2 = true,
    .door_locked_sensor_1 = true,
    .door_locked_sensor_2 = true
};

door_control_output_t output;
door_control_process(&input, &output, &state);

// Check outputs
if (output.door_lock_command) {
    // Activate door lock actuator
}
```

## Documentation

### Requirements Document
See `docs/requirements.md` for the complete Software Requirements Specification including:
- 18 detailed requirements
- SIL 3 classification
- Hazard analysis summary
- Traceability matrix
- Verification methods

### API Documentation
See `src/door_control.h` for complete API documentation including:
- Function specifications
- Parameter validation
- Error conditions
- Safety considerations

## Development Workflow

This example follows the EN 50128 development process:

1. **Requirements** (`/req`) - SRS development
2. **Design** (`/des`) - Architecture and interface design
3. **Implementation** (`/imp`) - MISRA C compliant coding
4. **Testing** (`/tst`) - Unit testing with 100% coverage
5. **Verification** (`/ver`) - Static analysis and verification
6. **Validation** (`/val`) - System validation
7. **Quality Assurance** (`/qua`) - Code reviews and audits

## Tool Integration

The build system integrates industry-standard tools:

- **GCC**: C compiler with MISRA-like warnings
- **Unity**: Unit testing framework
- **Cppcheck**: Static analysis for MISRA compliance
- **gcov/lcov**: Coverage analysis and reporting
- **Lizard**: Cyclomatic complexity measurement

## Learning Objectives

This example demonstrates:
- EN 50128:2011 compliance patterns
- SIL 3 safety-critical software development
- MISRA C:2012 coding standards
- Defensive programming techniques
- Redundant safety mechanisms
- Fail-safe system design
- Comprehensive verification strategies

---

## 🚀 Tutorial: Using the EN 50128 OpenCode Platform

This section provides **step-by-step instructions** for beginners to learn how to use the customized OpenCode platform for railway software development. Follow this tutorial to understand the complete EN 50128 V-Model lifecycle using specialized agents.

### Prerequisites

1. **Navigate to the platform root**:
   ```bash
   cd /home/norechang/work/EN50128
   ```

2. **Understand the platform structure**:
   - Platform root contains agents, skills, and standards
   - Projects are developed in `examples/` directory
   - This project is in `examples/train_door_control/`

### Tutorial Overview

We'll walk through the complete lifecycle using the 12 specialized EN 50128 agents:
- `/cod` - Lifecycle Coordinator (orchestrator)
- `/req` - Requirements Engineer
- `/des` - Designer
- `/imp` - Implementer
- `/tst` - Tester
- `/int` - Integrator
- `/ver` - Verifier
- `/val` - Validator
- `/saf` - Safety Engineer
- `/qua` - Quality Assurance
- `/pm` - Project Manager
- `/cm` - Configuration Manager

---

### Phase 0: Initialize Lifecycle Tracking (COD)

**Purpose**: Set up lifecycle orchestration with SIL-dependent phase gate enforcement.

```bash
# Initialize COD for this SIL 3 project
/cod plan --sil 3 --project train_door_control
```

**What happens**:
- COD creates `LIFECYCLE_STATE.md` in project root
- Initializes phase tracking (0 → Planning)
- Sets up SIL 3 strict gate enforcement mode
- Begins monitoring all agent activities

**Expected output**:
```
✅ Lifecycle initialized for project: train_door_control
   SIL Level: 3 (Strict gatekeeper mode)
   Current Phase: 0 - Initialization
   LIFECYCLE_STATE.md created
   
   Next step: /pm to begin project planning
```

**Check status anytime**:
```bash
/cod status
```

---

### Phase 1: Project Planning and Setup

#### Step 1.1: Project Management Setup (PM)

```bash
/pm
```

**Prompt the agent**: "Set up the train door control project. Create project organization chart, define roles, establish Change Control Board (CCB), and coordinate initial planning activities."

**What the agent does**:
- Establishes project organization
- Defines role assignments (Designer, Implementer, Tester, Verifier, Validator)
- Sets up Change Control Board (CCB) with PM as chair
- Creates project schedule and milestones
- Identifies stakeholders and communication plan

**Expected deliverables**:
- Project organization chart
- Role assignment matrix
- CCB charter
- Project schedule

#### Step 1.2: Configuration Management Setup (CM)

```bash
/cm
```

**Prompt**: "Establish Software Configuration Management Plan (SCMP) for train_door_control. Set up version control, define baselines, establish change control procedures."

**What the agent does**:
- Creates SCMP document
- Establishes Git branching strategy
- Defines configuration items (CIs)
- Sets up baseline procedures
- Establishes traceability matrix structure

**Expected deliverables**:
- `docs/SCMP.md` - Software Configuration Management Plan
- `.git/` - Version control initialized
- `docs/traceability_matrix.md` - RTM template

#### Step 1.3: Quality Assurance Planning (QUA)

```bash
/qua
```

**Prompt**: "Create Software Quality Assurance Plan (SQAP) for SIL 3 train door control system. Define quality metrics, review procedures, and compliance verification."

**What the agent does**:
- Creates SQAP document
- Defines quality metrics (complexity ≤10, coverage 100%)
- Establishes code review procedures
- Defines MISRA C compliance verification
- Sets up quality gates

**Expected deliverables**:
- `docs/SQAP.md` - Software Quality Assurance Plan
- Quality metrics dashboard template
- Code review checklist

#### Step 1.4: Verification and Validation Planning

**Verification Plan (VER agent)**:
```bash
/ver
```

**Prompt**: "Create Software Verification Plan (SVP) for SIL 3 system. Define static analysis, code reviews, complexity checks, coverage verification."

**Expected deliverables**:
- `docs/SVP.md` - Software Verification Plan
- Static analysis tool configuration
- Verification checklist

**Validation Plan (VAL agent)**:
```bash
/val
```

**Prompt**: "Create Software Validation Plan (SVaP) for SIL 3 train door control. Define system testing, acceptance criteria, operational scenarios."

**Expected deliverables**:
- `docs/SVaP.md` - Software Validation Plan
- System test specifications
- Acceptance test criteria

#### Step 1.5: Phase Gate Check - Planning Complete

```bash
/cod gate-check planning
```

**What COD verifies** (SIL 3 strict mode):
- [ ] SQAP approved ✓
- [ ] SCMP approved ✓
- [ ] SVP approved ✓
- [ ] SVaP approved ✓
- [ ] Project organization defined ✓
- [ ] Configuration management operational ✓

**Expected output**:
```
✅ Planning Phase Gate: PASSED
   All mandatory deliverables complete
   Baselines established
   
   Authorization: Transition to Phase 2 (Requirements)
   Next step: /req to begin requirements engineering
```

---

### Phase 2: Requirements Engineering

#### Step 2.1: Requirements Specification (REQ)

```bash
/req
```

**COD intercepts**: "⚠️ Requirement activity requires explicit USER APPROVAL. Approve? [Y/N]"

**Type**: `Y` (approve)

**Prompt the agent**: "Analyze the train door control system requirements. Extract functional, safety, and performance requirements from `docs/requirements.md`. Assign SIL levels, establish traceability to system requirements."

**What the agent does**:
- Reads existing `docs/requirements.md`
- Validates requirement quality (unambiguous, testable, traceable)
- Assigns SIL levels (most requirements SIL 3)
- Creates Requirements Traceability Matrix (RTM)
- Verifies SHALL/SHOULD/MAY keywords
- Checks C language constraints considered

**Expected deliverables**:
- `docs/requirements.md` - Software Requirements Specification (SRS) [ALREADY EXISTS]
- `docs/RTM.md` - Requirements Traceability Matrix
- Requirements review report

**Review the SRS**:
```bash
cat docs/requirements.md
```

You'll see 18 requirements:
- REQ-FUNC-001 to REQ-FUNC-006 (Functional)
- REQ-SAFE-001 to REQ-SAFE-003 (Safety)
- REQ-PERF-001 to REQ-PERF-002 (Performance)
- REQ-IF-001 to REQ-IF-007 (Interface)

#### Step 2.2: Safety Analysis (SAF)

```bash
/saf
```

**Prompt**: "Perform hazard analysis for train door control system. Identify hazards (doors opening while moving), perform FMEA, define safety requirements."

**What the agent does**:
- Identifies hazards (e.g., H-001: Doors open while train moving)
- Performs FMEA (Failure Mode and Effects Analysis)
- Analyzes failure modes (speed sensor failure, door sensor failure)
- Defines safety mechanisms (redundant sensors, fail-safe logic)
- Creates Hazard Log

**Expected deliverables**:
- `docs/hazard_log.md` - Hazard identification and analysis
- `docs/FMEA.md` - Failure Mode and Effects Analysis
- Safety requirements (REQ-SAFE-*)

#### Step 2.3: Configuration Management - Requirements Baseline (CM)

```bash
/cm
```

**Prompt**: "Establish requirements baseline for train_door_control. Freeze requirements, create baseline tag."

**What the agent does**:
- Creates Git tag `requirements-baseline-v1.0`
- Updates configuration status
- Records baseline in SCMP

```bash
# CM agent executes:
git tag -a requirements-baseline-v1.0 -m "Requirements baseline for train door control SIL 3"
```

#### Step 2.4: Phase Gate Check - Requirements Complete

```bash
/cod gate-check requirements
```

**What COD verifies** (SIL 3 strict mode):
- [ ] SRS complete, reviewed, and approved ✓
- [ ] All requirements unambiguous, testable, traceable ✓
- [ ] RTM complete (forward traceability) ✓
- [ ] SIL levels assigned to all requirements ✓
- [ ] Hazard Log established ✓
- [ ] Safety requirements identified ✓
- [ ] Requirements baseline established ✓
- [ ] USER APPROVAL obtained ✓

**Expected output**:
```
✅ Requirements Phase Gate: PASSED
   18 requirements specified (6 functional, 3 safety, 2 performance, 7 interface)
   RTM completeness: 100%
   Hazard analysis complete
   
   Authorization: Transition to Phase 3 (Design)
   Next step: /des to begin architecture and design
```

---

### Phase 3: Architecture and Design

#### Step 3.1: Software Design (DES)

```bash
/des
```

**Prompt**: "Design the train door control architecture. Create modular design with separation of concerns, define interfaces, ensure cyclomatic complexity ≤10, use static allocation only."

**What the agent does**:
- Creates Software Architecture Specification (SAS)
- Designs module structure:
  - `door_control.c` - Main control logic
  - `door_control.h` - Public API
  - `error_types.h` - Error definitions
- Defines interfaces (input/output structures)
- Applies defensive programming patterns
- Ensures static memory allocation (no malloc)
- Verifies complexity limits (≤10 for SIL 3)

**Expected deliverables**:
- `docs/SAS.md` - Software Architecture Specification
- `docs/SDS.md` - Software Design Specification
- `docs/ICD.md` - Interface Control Document
- Design traceability matrix (requirements → design)

**Review the design**:
```bash
cat src/door_control.h  # Public API
```

#### Step 3.2: Safety Analysis - FMEA/FTA (SAF)

```bash
/saf
```

**Prompt**: "Perform FMEA and FTA on the door control design. Analyze failure modes of speed monitoring, door sensor redundancy, and fail-safe mechanisms."

**What the agent does**:
- Performs design-level FMEA
- Constructs Fault Tree Analysis (FTA) for critical hazards
- Verifies redundant safety checks (2 sensors for speed, 2 for door)
- Validates fail-safe behavior on failures

**Expected deliverables**:
- `docs/FMEA_design.md` - Design-level FMEA
- `docs/FTA.md` - Fault Tree Analysis
- Safety mechanism verification report

#### Step 3.3: Design Review (QUA)

```bash
/qua
```

**Prompt**: "Perform design review for train door control. Check traceability to requirements, verify complexity limits, review safety mechanisms, check MISRA C design patterns."

**What the agent does**:
- Reviews SAS/SDS against requirements
- Checks design traceability (RTM completeness)
- Verifies complexity limits defined
- Reviews defensive programming patterns
- Checks static allocation strategy

**Expected deliverables**:
- `docs/design_review_report.md` - Design review findings

#### Step 3.4: Design Baseline (CM)

```bash
/cm
```

**Prompt**: "Establish design baseline."

```bash
# CM creates baseline
git tag -a design-baseline-v1.0 -m "Design baseline for train door control SIL 3"
```

#### Step 3.5: Phase Gate Check - Design Complete

```bash
/cod gate-check design
```

**What COD verifies**:
- [ ] SAS and SDS complete and approved ✓
- [ ] Design traceability matrix complete ✓
- [ ] Cyclomatic complexity limits defined (≤10) ✓
- [ ] Defensive programming patterns designed ✓
- [ ] Static memory allocation confirmed ✓
- [ ] Safety mechanisms designed ✓
- [ ] FMEA/FTA complete (SIL 3) ✓
- [ ] Design baseline established ✓

**Expected output**:
```
✅ Design Phase Gate: PASSED
   Modular architecture defined
   Complexity limits: ≤10 per function
   Static allocation verified
   
   Authorization: Transition to Phase 4 (Implementation)
   Next step: /imp to begin coding
```

---

### Phase 4: Implementation and Unit Testing

#### Step 4.1: Code Implementation (IMP)

```bash
/imp
```

**Prompt**: "Implement the train door control system in C following the design. Ensure MISRA C:2012 compliance, static allocation only, defensive programming, complexity ≤10, all pointers validated, all return values checked."

**What the agent does**:
- Implements `src/door_control.c` following SDS
- Uses fixed-width types (`uint8_t`, `uint16_t`, `uint32_t`)
- Validates all inputs (NULL pointer checks)
- Checks all return values
- Uses static allocation (no malloc/free)
- Limits function complexity to ≤10
- Adds defensive programming assertions

**Expected deliverables**:
- `src/door_control.c` - Implementation [ALREADY EXISTS]
- `src/door_control.h` - Public API [ALREADY EXISTS]
- `src/error_types.h` - Error codes [ALREADY EXISTS]

**Review the code**:
```bash
cat src/door_control.c
```

Key patterns to observe:
- NULL pointer validation: `if (input == NULL) return ERROR_NULL_POINTER;`
- Fixed-width types: `uint32_t speed_kmh;`
- Static allocation: No malloc/free anywhere
- Defensive checks: All sensor inputs validated

#### Step 4.2: Unit Test Development (TST)

```bash
/tst
```

**Prompt**: "Develop comprehensive unit tests for door_control module using Unity framework. Achieve 100% statement, branch, and condition coverage (SIL 3 requirement). Test normal operation, boundary conditions, error handling, safety interlocks."

**What the agent does**:
- Creates `test/test_door_control.c` [ALREADY EXISTS]
- Writes test cases for all functions
- Tests boundary values (speed=0, speed=1)
- Tests error conditions (NULL pointers)
- Tests safety interlocks (doors locked while moving)
- Verifies redundancy checks
- Tests fail-safe behavior

**Expected deliverables**:
- `test/test_door_control.c` - Unit tests

**Run the tests**:
```bash
make test
```

**Expected output**:
```
Running unit tests...
test/test_door_control.c:25:test_init_success:PASS
test/test_door_control.c:45:test_process_null_input:PASS
test/test_door_control.c:65:test_speed_zero_allows_door_open:PASS
...
-----------------------
18 Tests 0 Failures 0 Ignored
OK

Statement coverage: 100.0%
Branch coverage: 100.0%
Condition coverage: 100.0%
```

#### Step 4.3: Static Analysis and Verification (VER)

```bash
/ver
```

**Prompt**: "Run static analysis on train door control code. Check MISRA C:2012 compliance using Cppcheck, measure cyclomatic complexity using Lizard, verify coverage meets SIL 3 requirements (100%)."

**What the agent does**:
- Runs Cppcheck for MISRA C compliance
- Runs Lizard for complexity analysis
- Verifies coverage reports
- Checks for MISRA mandatory violations (must be zero)

**Run verification**:
```bash
make verify
```

**Expected output**:
```
========================================
Static Analysis (Cppcheck)
========================================
Checking src/door_control.c...
✅ 0 errors found
✅ MISRA C: 0 mandatory violations

========================================
Complexity Analysis (Lizard)
========================================
door_control_init: Complexity 2 ✅
door_control_process: Complexity 8 ✅
check_speed_interlock: Complexity 4 ✅
...
✅ All functions within limit (≤10)

========================================
Coverage Analysis
========================================
Statement: 100.0% ✅
Branch: 100.0% ✅
Condition: 100.0% ✅
MC/DC: 100.0% ✅
```

#### Step 4.4: Code Review (QUA)

```bash
/qua
```

**Prompt**: "Perform code review for train_door_control. Check MISRA C compliance, verify defensive programming, check complexity, review test coverage, verify traceability code→design."

**What the agent does**:
- Reviews code against MISRA C:2012
- Checks defensive programming patterns
- Verifies all pointers validated
- Verifies all returns checked
- Reviews test coverage
- Checks code→design traceability

**Expected deliverables**:
- `docs/code_review_report.md` - Code review findings

#### Step 4.5: Implementation Baseline (CM)

```bash
/cm
```

**Prompt**: "Establish implementation baseline."

```bash
git tag -a implementation-baseline-v1.0 -m "Implementation baseline - code and tests complete"
```

#### Step 4.6: Phase Gate Check - Implementation Complete

```bash
/cod gate-check implementation
```

**What COD verifies**:
- [ ] All source code complete and reviewed ✓
- [ ] MISRA C:2012 compliance verified (zero mandatory violations) ✓
- [ ] Unit tests written for all modules ✓
- [ ] All unit tests pass (100% pass rate) ✓
- [ ] Coverage: 100% statement, 100% branch, 100% condition (SIL 3) ✓
- [ ] Static analysis clean ✓
- [ ] Cyclomatic complexity ≤10 ✓
- [ ] Implementation baseline established ✓

**Expected output**:
```
✅ Implementation Phase Gate: PASSED
   MISRA C: 0 mandatory violations
   Coverage: 100% statement/branch/condition
   Complexity: All functions ≤10
   Unit tests: 18/18 passed
   
   Authorization: Transition to Phase 5 (Integration)
   Next step: /int for integration testing
```

---

### Phase 5: Integration Testing

#### Step 5.1: Integration Testing (INT)

```bash
/int
```

**Prompt**: "Perform integration testing for train door control. Test interfaces between door_control module and external systems (speed sensors, door sensors, actuators). Verify data flow, error handling at boundaries."

**What the agent does**:
- Creates integration test plan
- Tests module interfaces
- Verifies data flow between components
- Tests error handling at boundaries
- Performs performance testing (response time ≤100ms)

**Expected deliverables**:
- `docs/integration_test_plan.md`
- `docs/integration_test_results.md`
- Performance test results

**Run integration tests**:
```bash
make integration-test  # If integration tests exist
```

#### Step 5.2: Integration Baseline (CM)

```bash
/cm
```

**Prompt**: "Establish integration baseline."

```bash
git tag -a integration-baseline-v1.0 -m "Integration baseline - all tests passed"
```

#### Step 5.3: Phase Gate Check - Integration Complete

```bash
/cod gate-check integration
```

**What COD verifies**:
- [ ] Integration tests executed and passed ✓
- [ ] All interfaces tested ✓
- [ ] Performance requirements met ✓
- [ ] Integration baseline established ✓

**Expected output**:
```
✅ Integration Phase Gate: PASSED
   All integration tests passed
   Performance: Response time <100ms
   
   Authorization: Transition to Phase 6 (Validation)
   Next step: /val for system validation
```

---

### Phase 6: System Validation

#### Step 6.1: Validation Testing (VAL)

**IMPORTANT**: For SIL 3, validator MUST be independent from development team.

```bash
/val
```

**Prompt**: "Perform system validation for train door control SIL 3. Execute validation test suite, perform operational scenario testing, validate all 18 requirements, obtain acceptance."

**What the agent does**:
- Executes validation test suite
- Tests operational scenarios (train stopped → doors open → train moves → doors lock)
- Validates all requirements (REQ-FUNC-*, REQ-SAFE-*, REQ-PERF-*)
- Performs safety validation
- Generates validation report

**Expected deliverables**:
- `docs/validation_test_report.md`
- `docs/validation_summary.md`
- Acceptance certificate

#### Step 6.2: Independent Verification Evidence (VER)

```bash
/ver
```

**Prompt**: "Collect all verification evidence for train door control SIL 3. Generate verification report with static analysis results, coverage reports, complexity analysis, traceability verification."

**What the agent does**:
- Collects all static analysis reports
- Verifies complete traceability (requirements→design→code→tests)
- Generates verification evidence package
- Creates verification report

**Expected deliverables**:
- `docs/verification_report.md`
- `docs/verification_evidence_package.zip`

#### Step 6.3: Phase Gate Check - Validation Complete

```bash
/cod gate-check validation
```

**What COD verifies**:
- [ ] All validation tests passed ✓
- [ ] All requirements validated ✓
- [ ] Customer acceptance obtained ✓
- [ ] Safety requirements validated ✓
- [ ] Independent validator verified (SIL 3) ✓
- [ ] Validation baseline established ✓

**Expected output**:
```
✅ Validation Phase Gate: PASSED
   All 18 requirements validated
   Independent validation team confirmed
   Customer acceptance obtained
   
   Authorization: Transition to Phase 7 (Assessment)
   Next step: Quality assessment and final approval
```

---

### Phase 7: Assessment and Release

#### Step 7.1: Quality Assessment (QUA)

```bash
/qua
```

**Prompt**: "Perform final quality assessment for train door control SIL 3. Verify all deliverables complete, all quality metrics met, EN 50128 compliance demonstrated."

**What the agent does**:
- Reviews all lifecycle artifacts
- Verifies EN 50128 compliance (all techniques applied)
- Checks quality metrics met
- Generates compliance matrix
- Prepares assessment report

**Expected deliverables**:
- `docs/assessment_report.md`
- `docs/compliance_matrix.md`
- `docs/safety_case.md`

#### Step 7.2: Release Baseline (CM)

```bash
/cm
```

**Prompt**: "Establish release baseline v1.0 for train door control."

```bash
git tag -a v1.0.0-SIL3 -m "Release v1.0.0 - Train Door Control SIL 3"
```

#### Step 7.3: Final Project Coordination (PM)

```bash
/pm
```

**Prompt**: "Coordinate final release approval for train door control v1.0. Obtain deployment authorization, prepare release package."

**What the agent does**:
- Coordinates with all stakeholders
- Obtains final approvals
- Prepares release package
- Archives all evidence

**Expected deliverables**:
- Deployment authorization
- Release notes
- Release package

#### Step 7.4: Phase Gate Check - Assessment Complete

```bash
/cod gate-check assessment
```

**What COD verifies**:
- [ ] Assessment report complete ✓
- [ ] Safety case approved ✓
- [ ] All lifecycle phases complete ✓
- [ ] EN 50128 compliance demonstrated ✓
- [ ] Release baseline established ✓
- [ ] Deployment authorization obtained ✓

**Expected output**:
```
✅ Assessment Phase Gate: PASSED
   All lifecycle phases complete
   EN 50128 compliance verified
   Safety case approved
   
   ✅ PROJECT READY FOR DEPLOYMENT
```

---

### Final: Check Complete Lifecycle Status

```bash
/cod status
```

**Expected output**:
```
========================================
LIFECYCLE STATUS: train_door_control
========================================
Project: train_door_control
SIL Level: 3 (Strict gatekeeper mode)
Current Phase: 8 - Assessment Complete

Phase Status:
  ✅ Phase 1: Planning - PASSED
  ✅ Phase 2: Requirements - PASSED
  ✅ Phase 3: Design - PASSED
  ✅ Phase 4: Implementation - PASSED
  ✅ Phase 5: Integration - PASSED
  ✅ Phase 6: Validation - PASSED
  ✅ Phase 7: Assessment - PASSED

Deliverables: 24/24 complete (100%)
Traceability: 100% forward, 100% backward
Quality Metrics: All met
Coverage: 100% (statement/branch/condition)

✅ PROJECT STATUS: READY FOR DEPLOYMENT
```

---

## 📝 Tutorial Summary

You've now completed the full EN 50128 V-Model lifecycle using the customized OpenCode platform!

### What You Learned:

1. **Lifecycle Orchestration**: Used `/cod` to manage phase gates and ensure EN 50128 compliance
2. **Requirements Engineering**: Used `/req` to specify and manage requirements with user approval
3. **Safety Analysis**: Used `/saf` to perform hazard analysis, FMEA, and FTA
4. **Design**: Used `/des` to create modular, safety-critical architecture
5. **Implementation**: Used `/imp` to code in MISRA C:2012 compliant C
6. **Testing**: Used `/tst` to achieve 100% coverage (SIL 3 requirement)
7. **Verification**: Used `/ver` to perform static analysis and collect evidence
8. **Validation**: Used `/val` to validate system requirements
9. **Quality Assurance**: Used `/qua` for reviews and assessments
10. **Configuration Management**: Used `/cm` for baselines and change control
11. **Project Management**: Used `/pm` for coordination and approvals

### Key Takeaways:

- **COD is the orchestrator**: Always use `/cod gate-check <phase>` before moving to next phase (SIL 3)
- **User approval for requirements**: COD enforces explicit approval for `/req` activities
- **SIL-dependent gates**: SIL 3 uses strict blocking gates; SIL 0-1 uses advisory warnings
- **Independence matters**: Validator and Verifier must be independent for SIL 3-4
- **Traceability is mandatory**: RTM must be complete at all phases
- **Coverage is mandatory**: 100% statement/branch/condition for SIL 3-4

### Next Steps:

1. **Create your own project**: `mkdir examples/my_project && cd examples/my_project`
2. **Initialize COD**: `/cod plan --sil 2 --project my_project`
3. **Follow the lifecycle**: Start with `/pm` for planning
4. **Reference this example**: Use train_door_control as a template

---

## References

- EN 50128:2011 - Railway Software Standard
- MISRA C:2012 - C Coding Guidelines
- IEC 61508 - Functional Safety Standard
- Unity Test Framework - https://github.com/ThrowTheSwitch/Unity