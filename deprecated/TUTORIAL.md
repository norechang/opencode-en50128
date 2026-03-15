# EN 50128 Platform Tutorial

**Complete Step-by-Step Guide to Railway Software Development**

---

## ⚠️ IMPORTANT: OpenCode TUI Required

**This tutorial MUST be followed within the OpenCode TUI (Terminal User Interface) environment.**

- **Install OpenCode**: Visit [https://opencode.ai](https://opencode.ai) for installation instructions
- **Why Required**: All commands (`/cod`, `/req`, `/des`, `/imp`, etc.) are OpenCode agents that only work in the TUI
- **Do NOT use**: Generic LLM interfaces - they cannot execute the specialized EN 50128 agents

**Setup**:
```bash
# 1. Install OpenCode (if not already installed)
# Visit https://opencode.ai/docs/installation

# 2. Clone this repository
git clone https://github.com/norechang/opencode-en50128.git
cd opencode-en50128

# 3. Launch OpenCode TUI
opencode

# 4. Verify platform is ready
/enhelp
```

---

## Tutorial Overview

This tutorial walks you through creating a complete EN 50128-compliant railway software project from scratch. We'll develop a **Train Door Control System** at SIL 3, following the complete V-Model lifecycle.

**Time Required**: 2-3 hours for complete walkthrough  
**Prerequisites**: Basic understanding of safety-critical software development  
**Example Reference**: `examples/train_door_control2/` - Completed implementation through Phase 5

---

## Development Modes

The platform supports two approaches to EN 50128 development:

### **Mode 1: PM Automation (Recommended)**

The **Project Manager (PM)** orchestrates the complete workflow, automatically coordinating agents in the correct sequence. This mode is **recommended for most users** as it simplifies the lifecycle and ensures proper agent coordination.

```bash
/pm execute-phase requirements    # PM → REQ, SAF, QUA, VER agents
/pm execute-phase design          # PM → DES, SAF, QUA, VER agents
# PM handles sequencing, quality gates, verification
```

**When to use**: Production projects, teams new to EN 50128, streamlined development

### **Mode 2: Manual Agent Invocation (Educational/Expert)**

Manually invoke each agent for **fine-grained control** and **learning purposes**. This mode demonstrates each agent's specific responsibilities and EN 50128 workflow details.

```bash
/req                        # Requirements Engineer
/saf                        # Safety Analysis
/qua review-requirements    # Quality Assurance
/ver verify-requirements    # Verification
/cod gate-check requirements
# User controls each step
```

**When to use**: Learning EN 50128 details, iterating on specific activities, expert customization

---

## Tutorial Approach

**This tutorial uses Manual Mode** to help you understand each agent's role and the EN 50128 lifecycle in detail. Once you're comfortable with the concepts:

1. **For learning**: Continue with Manual Mode (this tutorial)
2. **For production**: Switch to PM Automation Mode (see [PM Automation Guide](#pm-automation-guide))

---

## Table of Contents

1. [Development Modes](#development-modes)
2. [Tutorial Approach](#tutorial-approach)
3. [Introduction](#introduction)
4. [Phase 0: Project Initialization](#phase-0-project-initialization)
5. [Phase 1: Planning](#phase-1-planning)
6. [Phase 2: Requirements Specification](#phase-2-requirements-specification)
7. [Phase 3: Architecture & Design](#phase-3-architecture--design)
8. [Phase 4: Component Implementation & Testing](#phase-4-component-implementation--testing)
9. [Phase 5: Integration](#phase-5-integration)
10. [Phase 6: Validation](#phase-6-validation)
11. [Phase 7: Assessment (SIL 3-4)](#phase-7-assessment-sil-3-4)
12. [Phase 8: Deployment](#phase-8-deployment)
13. [PM Automation Guide](#pm-automation-guide) ⭐ **Streamlined Production Workflow**
14. [Advanced Topics](#advanced-topics)

---

## Introduction

### What You'll Build

A **Train Door Control System** (SIL 3) that:
- Controls door opening/closing based on train state
- Monitors door sensors (closed, locked, obstacle detection)
- Implements safety interlocks (no door opening while moving)
- Provides fault detection and safe state handling
- Meets EN 50128 requirements for SIL 3 software

### The EN 50128 V-Model

```
Phase 2: Requirements ──────────────┐
        ↓                           │ (Validation)
Phase 3: Architecture & Design      │
        ↓                           │
Phase 4: Implementation & Testing   │
        ↓                           │
Phase 5: Integration ───────────────┤
        ↓                           │
Phase 6: Validation ────────────────┘
        ↓
Phase 7: Assessment (SIL 3-4)
        ↓
Phase 8: Deployment
```

Each phase has:
- **Entry criteria** - What must be complete before starting
- **Activities** - What work is performed
- **Exit criteria** - What must be complete before proceeding
- **Deliverables** - Documents and artifacts produced

---

## Phase 0: Project Initialization

### Step 1: Create Project Directory

```bash
# Create project directory
mkdir train_door_control
cd train_door_control

# Initialize Git repository
git init
```

### Step 2: Initialize Lifecycle Tracking

Invoke the Lifecycle Coordinator to set up project tracking:

```bash
/cod plan --sil 3 --project "Train Door Control System"
```

**Expected Output**:
- Creates `LIFECYCLE_STATE.md` - Central project state tracking
- Initializes Phase 0 (Initialization)
- Sets SIL level to 3
- Creates workspace structure

**What COD Does**:
- Sets up phase tracking for all 9 phases (0-8)
- Defines entry/exit criteria for each phase
- Configures SIL 3 requirements (strict gate enforcement)
- Creates initial workspace configuration

### Step 3: Review Project State

```bash
/cod status
```

**Expected Output**:
```
Current Phase: Phase 0 (Initialization)
SIL Level: 3
Project: Train Door Control System
Status: In Progress

Next Phase: Phase 1 (Planning)
Entry Criteria: Phase 0 complete, project initialized
```

**Files Created**:
- `LIFECYCLE_STATE.md` - Project tracking (updated throughout lifecycle)
- `.workspace` - Workspace configuration (if using multi-workspace setup)

---

## Phase 1: Planning

### Overview

Create the four core planning documents required by EN 50128:
1. **SQAP** - Software Quality Assurance Plan
2. **SCMP** - Software Configuration Management Plan
3. **SVP** - Software Verification Plan
4. **SVaP** - Software Validation Plan

### Step 1: Create Software Quality Assurance Plan (SQAP)

```bash
/qua create-sqap --sil 3
```

**What QUA Agent Does**:
- Uses template from `skills/en50128-quality/templates/sqap-template.md`
- Configures for SIL 3 requirements
- Defines quality metrics (complexity ≤10, 100% coverage)
- Specifies mandatory code reviews
- Defines approval requirements

**Deliverable**: `docs/plans/DOC-SQAP-2026-001.md`

**Key Sections**:
- Quality objectives for SIL 3
- Code review process (mandatory, independent)
- MISRA C:2012 compliance (zero mandatory violations)
- Cyclomatic complexity limits (≤10)
- Coverage requirements (100% statement/branch/condition)

### Step 2: Create Software Configuration Management Plan (SCMP)

```bash
/cm create-scmp --sil 3
```

**What CM Agent Does**:
- Uses template from `skills/en50128-configuration/templates/scmp-template.md`
- Defines configuration items (all deliverables)
- Sets up version control strategy
- Defines baseline management
- Configures change control board (CCB)

**Deliverable**: `docs/plans/DOC-SCMP-2026-001.md`

**Key Sections**:
- Configuration identification scheme (DOC-XXX-YYYY-NNN)
- Version control (Git branching strategy)
- Baseline management (approved configurations)
- Change control process (CCB approval required for SIL 3)
- Traceability management (mandatory SIL 3)

### Step 3: Create Software Verification Plan (SVP)

```bash
/ver create-svp --sil 3
```

**What VER Agent Does**:
- Uses template from `skills/en50128-verification/templates/svp-template.md`
- Defines verification strategy for SIL 3
- Specifies static analysis tools (PC-lint, Cppcheck, Clang)
- Defines verification techniques per Table A.5
- Plans independence requirements

**Deliverable**: `docs/plans/DOC-SVP-2026-001.md`

**Key Sections**:
- Verification strategy (independent team for SIL 3)
- Static analysis (mandatory SIL 3)
- Coverage verification (100% statement/branch/condition)
- Traceability verification (mandatory SIL 3)
- Tool qualification (if using automated tools)

### Step 4: Create Software Validation Plan (SVaP)

```bash
/val create-svap --sil 3
```

**What VAL Agent Does**:
- Uses template from `skills/en50128-validation/templates/svap-template.md`
- Defines validation strategy for SIL 3
- Specifies system test approach
- Plans operational scenarios
- Defines acceptance criteria

**Deliverable**: `docs/plans/DOC-SVAP-2026-001.md`

**Key Sections**:
- Validation strategy (independent validation for SIL 3)
- System test approach (operational scenarios)
- Acceptance criteria (customer approval)
- Target environment testing (mandatory SIL 3)
- Performance testing (mandatory SIL 3)

### Step 5: Gate Check - Transition to Phase 2

```bash
/cod gate-check planning
```

**What COD Checks**:
- ✅ All four plans created (SQAP, SCMP, SVP, SVaP)
- ✅ Document templates compliant (QUA verification)
- ✅ SIL 3 requirements addressed
- ✅ Approval tables complete

**Expected Output**:
```
Phase 1 (Planning) Gate Check: PASS

Entry Criteria for Phase 2 (Requirements):
✅ SQAP approved
✅ SCMP approved
✅ SVP approved
✅ SVaP approved
✅ Configuration management active

Authorization: Proceed to Phase 2 (Requirements Specification)
```

**COD Updates**: `LIFECYCLE_STATE.md` transitions to Phase 2

---

## System-Level Documents (Prerequisite for Phase 2)

### Overview

**IMPORTANT**: Before you can begin Phase 2 (Software Requirements Specification), you need **four system-level input documents** per EN 50128 Section 7.2.2. These are produced by the **System Engineering phase** following EN 50126/50129 standards.

### Required System-Level Documents

1. **System Requirements Specification** - Overall system requirements (not just software)
2. **System Architecture Description** - Hardware/software partitioning, system boundaries
3. **System Safety Plan** - Safety management strategy, hazard analysis process, ISA plan
4. **System Safety Requirements Specification** - Hazards (FMEA/FTA), safety functions, SIL assignment

### Where to Find Templates

The platform provides **complete reference examples** in `assets/sample_system/`:

```bash
# View the templates
ls assets/sample_system/

# Read the comprehensive usage guide
cat assets/sample_system/README.md
```

**Available Templates** (569-1189 lines each):
- `System-Requirements-Specification-TEMPLATE.md` - 71 requirements example
- `System-Architecture-Description-TEMPLATE.md` - Dual-channel architecture example
- `System-Safety-Plan-TEMPLATE.md` - Complete safety management plan
- `System-Safety-Requirements-Specification-TEMPLATE.md` - 9 hazards, FMEA/FTA, 7 safety functions

### How to Use for Your Project

**Option 1: Study the Reference Example (Recommended for Learning)**

If you're following this tutorial to learn, you can study the reference implementation:

```bash
# View the completed system documents for Train Door Control
ls examples/train_door_control2/docs/system/
```

These are the **original, complete documents** (non-templated) that demonstrate proper EN 50126/50129 structure.

**Option 2: Create Your Own System Documents**

For a real project, you would:

1. **Copy templates to your project**:
   ```bash
   mkdir -p docs/system
   cp assets/sample_system/*.md docs/system/
   ```

2. **Customize metadata**: Replace `YYYY-MM-DD`, `[Name]`, `DOC-XXX-YYYY-NNN`

3. **Adapt content**: Replace Train Door Control specifics with YOUR system

4. **Ensure completeness**:
   - All hazards identified (FMEA/FTA performed)
   - Safety functions defined with SIL levels
   - System architecture documented
   - Safety management organization defined

See `assets/sample_system/README.md` for complete usage guide.

### For This Tutorial

**We'll assume system-level documents exist** and proceed directly to Phase 2 (Software Requirements). In the reference example (`examples/train_door_control2/`), these documents are already completed in `docs/system/`.

**Key Traceability**:
- System Requirements → Software Requirements (Phase 2)
- System Safety Requirements → Software Safety Requirements (Phase 2)
- System Architecture → Software Architecture (Phase 3)

---

## Phase 2: Requirements Specification

### Overview

Define **what the software** must do, derived from system-level requirements. Software requirements must be:
- **Unambiguous** - Single interpretation
- **Testable** - Can be verified
- **Traceable** - Forward to design, backward to system requirements
- **SIL-assigned** - Each requirement has SIL level

**Input Documents** (from System Engineering phase):
- System Requirements Specification
- System Safety Requirements Specification
- System Architecture Description

### Step 1: Create Software Requirements Specification (SRS)

**Important**: REQ agent requires **user approval** for requirement establishment (COD enforces this).

```bash
/req create-srs --system "Train Door Control" --sil 3
```

**What REQ Agent Does**:
- Uses template from `skills/en50128-requirements/templates/srs-template.md`
- Prompts user for requirements (cannot auto-generate - COD enforces approval)
- Assigns unique IDs (REQ-XXX format)
- Assigns SIL levels
- Creates traceability matrix

**User Interaction** (REQ will prompt):
```
Please provide software requirements for "Train Door Control System":

Enter requirements (one per line, or provide multi-line specification):
```

**Example Requirements** (you provide):
```
REQ-001: The system SHALL prevent door opening when train speed > 0 km/h [SIL 3]
REQ-002: The system SHALL detect door closed sensor within 100ms [SIL 3]
REQ-003: The system SHALL detect door locked sensor within 100ms [SIL 3]
REQ-004: The system SHALL detect obstacle sensor within 50ms [SIL 3]
REQ-005: The system SHALL command door to CLOSED state when obstacle detected [SIL 3]
REQ-006: The system SHALL provide fault indication when sensor fails [SIL 2]
REQ-007: The system SHALL enter safe state (doors closed) on critical failure [SIL 3]
REQ-008: The system SHALL support emergency door release [SIL 3]
```

**Deliverable**: `docs/requirements/DOC-SRS-2026-001.md`

**Key Sections**:
- Functional requirements (REQ-001 to REQ-NNN)
- Safety requirements (SIL 3 requirements marked)
- Performance requirements (timing constraints)
- Interface requirements (sensors, actuators, HMI)
- Traceability matrix (embedded in document)

### Step 2: Safety Analysis

Identify hazards and define safety requirements:

```bash
/saf analyze-hazards --system "Train Door Control"
```

**What SAF Agent Does**:
- Identifies hazards (e.g., "Door opens while train moving")
- Performs preliminary FMEA
- Defines safety requirements
- Updates Hazard Log
- Links hazards to requirements (traceability)

**Deliverable**: `docs/safety/DOC-HAZLOG-2026-001.md` (Hazard Log)

**Example Hazards**:
```
HAZ-001: Door opens while train speed > 0 km/h
  - Severity: Catastrophic
  - Mitigation: REQ-001 (speed interlock)
  
HAZ-002: Door fails to detect obstacle
  - Severity: Critical
  - Mitigation: REQ-004, REQ-005 (obstacle detection)
```

### Step 3: Quality Assurance - Requirements Review

```bash
/qua review-requirements
```

**What QUA Agent Checks**:
- ✅ Document template compliance (DOC-XXX-YYYY-NNN format)
- ✅ Document control table present
- ✅ Approvals table with SIL 3 roles (Designer, Implementer, Verifier, Validator)
- ✅ Requirements unambiguous (SHALL/SHOULD/MAY keywords)
- ✅ Requirements testable
- ✅ SIL levels assigned
- ✅ Traceability matrix present

**Deliverable**: `docs/quality/DOC-QA-REQ-2026-001.md` (QA Requirements Review Report)

### Step 4: Gate Check - Transition to Phase 3

```bash
/cod gate-check requirements
```

**What COD Checks** (SIL 3 - Strict Mode):
- ✅ SRS complete with all requirements
- ✅ Hazard Log created
- ✅ QUA review passed
- ✅ Traceability matrix complete
- ✅ User approval obtained for all requirements
- ✅ Baseline established (CM)

**Expected Output**:
```
Phase 2 (Requirements) Gate Check: PASS

Entry Criteria for Phase 3 (Architecture & Design):
✅ SRS approved (DOC-SRS-2026-001)
✅ Hazard Log created (DOC-HAZLOG-2026-001)
✅ QA review passed (DOC-QA-REQ-2026-001)
✅ Traceability complete
✅ Baseline REQ-001 established

Authorization: Proceed to Phase 3 (Architecture & Design)
```

**Files Created**:
- `docs/requirements/DOC-SRS-2026-001.md` (~50-100 lines depending on requirements)
- `docs/safety/DOC-HAZLOG-2026-001.md` (~30-50 lines)
- `docs/quality/DOC-QA-REQ-2026-001.md` (~20-30 lines)

---

## Phase 3: Architecture & Design

### Overview

Define **how** the system implements requirements. Design must satisfy:
- **Modular architecture** (mandatory SIL 2+)
- **Static memory allocation** (mandatory SIL 2+)
- **Cyclomatic complexity ≤10** (SIL 3)
- **Defensive programming** (highly recommended SIL 3)
- **MISRA C compliance** (mandatory SIL 2+)

### Step 1: Create Software Architecture Specification (SAS)

```bash
/des create-sas
```

**What DES Agent Does**:
- Uses template from `skills/en50128-design/templates/sas-template.md`
- Defines high-level architecture (modules, interfaces)
- Applies modular approach (mandatory SIL 2+)
- Designs for static allocation
- Creates architecture diagrams

**Deliverable**: `docs/design/DOC-SAS-2026-001.md`

**Example Architecture**:
```
Modules:
- door_control.c/h - Main door control logic
- sensor_monitor.c/h - Sensor reading and validation
- safety_interlock.c/h - Speed interlock and safety checks
- fault_manager.c/h - Fault detection and safe state handling
- door_interface.c/h - Hardware abstraction layer
```

**Key Design Decisions**:
- **No dynamic allocation** - All buffers statically allocated
- **Fixed-width types** - Use `uint8_t`, `uint16_t`, etc.
- **Bounded execution** - All functions have max execution time
- **Defensive programming** - All inputs validated, all returns checked

### Step 2: Create Software Design Specification (SDS)

```bash
/des create-sds
```

**What DES Agent Does**:
- Uses template from `skills/en50128-design/templates/sds-template.md`
- Defines detailed design for each module
- Specifies function signatures (C prototypes)
- Designs data structures (static only)
- Creates function-level flowcharts
- Ensures complexity limits (≤10 for SIL 3)

**Deliverable**: `docs/design/DOC-SDS-2026-001.md`

**Example Design** (door_control.c):
```c
/* Function: door_control_init
 * Complexity: 3
 * Traceability: REQ-001, REQ-007
 */
error_t door_control_init(void);

/* Function: door_control_process
 * Complexity: 8
 * Traceability: REQ-001, REQ-002, REQ-003, REQ-004, REQ-005
 */
error_t door_control_process(const sensor_data_t* sensors, door_command_t* cmd);

/* Data Structure: door_state_t
 * Static allocation: sizeof(door_state_t) = 64 bytes
 */
typedef struct {
    uint8_t state;              // Current door state
    uint8_t fault_status;       // Fault flags
    uint32_t fault_count;       // Fault counter
    bool emergency_release;     // Emergency release flag
} door_state_t;
```

### Step 3: Create Software Interface Specifications (SIS)

```bash
/des create-sis
```

**What DES Agent Does**:
- Defines all module interfaces
- Specifies sensor interfaces (ADC readings, GPIO)
- Specifies actuator interfaces (door motor control)
- Specifies inter-module interfaces
- Documents interface protocols

**Deliverable**: `docs/design/DOC-SIS-2026-001.md`

### Step 4: Safety Analysis - Design FMEA

```bash
/saf fmea --phase design
```

**What SAF Agent Does**:
- Performs FMEA on design
- Identifies single points of failure
- Analyzes common cause failures (SIL 3 mandatory)
- Proposes design mitigations
- Updates Hazard Log

**Deliverable**: `docs/safety/DOC-FMEA-DES-2026-001.md` (Design FMEA)

### Step 5: Quality Assurance - Design Review

```bash
/qua review-design
```

**What QUA Agent Checks**:
- ✅ Document templates compliant
- ✅ Modular architecture (mandatory SIL 2+)
- ✅ Static allocation (no malloc/free for SIL 2+)
- ✅ Complexity estimates ≤10 (SIL 3)
- ✅ Defensive programming patterns present
- ✅ Traceability to requirements complete

**Deliverable**: `docs/quality/DOC-QA-DES-2026-001.md` (QA Design Review Report)

### Step 6: Gate Check - Transition to Phase 4

```bash
/cod gate-check design
```

**What COD Checks** (SIL 3 - Strict Mode):
- ✅ SAS complete and approved
- ✅ SDS complete and approved
- ✅ SIS complete
- ✅ Design FMEA complete
- ✅ QUA review passed
- ✅ Traceability to requirements complete
- ✅ Baseline established (CM)

**Expected Output**:
```
Phase 3 (Architecture & Design) Gate Check: PASS

Entry Criteria for Phase 4 (Component Implementation & Testing):
✅ SAS approved (DOC-SAS-2026-001)
✅ SDS approved (DOC-SDS-2026-001)
✅ SIS approved (DOC-SIS-2026-001)
✅ Design FMEA complete (DOC-FMEA-DES-2026-001)
✅ QA review passed (DOC-QA-DES-2026-001)
✅ Baseline DES-001 established

Authorization: Proceed to Phase 4 (Component Implementation & Testing)
```

---

## Phase 4: Component Implementation & Testing

### Overview

Implement C code following MISRA C:2012 and perform unit testing. Requirements:
- **MISRA C:2012 compliance** (mandatory SIL 2+)
- **Static allocation only** (no malloc/calloc/realloc/free for SIL 2+)
- **Complexity ≤10** (SIL 3)
- **100% coverage** (statement/branch/condition for SIL 3)
- **Defensive programming** (all inputs validated, all returns checked)

### Step 1: Implement Module (Example: door_control.c)

```bash
/imp implement-module --name door_control --design docs/design/DOC-SDS-2026-001.md
```

**What IMP Agent Does**:
- Reads design specification
- Generates C source code (MISRA C compliant)
- Implements defensive programming patterns
- Ensures static allocation
- Creates corresponding header file
- Generates unit test skeleton

**Deliverable**: 
- `src/door_control.c` (~200-300 lines)
- `include/door_control.h` (~50-100 lines)
- `tests/test_door_control.c` (unit test skeleton)

**Example Implementation** (door_control.c excerpt):
```c
#include "door_control.h"
#include <stddef.h>

/* Static state - no dynamic allocation (SIL 2+ requirement) */
static door_state_t g_door_state;

/* Function: door_control_init
 * Complexity: 3
 * Traceability: REQ-007
 */
error_t door_control_init(void) {
    /* Defensive programming - validate state */
    (void)memset(&g_door_state, 0, sizeof(g_door_state));
    
    /* Initialize to safe state (doors closed) */
    g_door_state.state = DOOR_STATE_CLOSED;
    g_door_state.fault_status = 0U;
    g_door_state.fault_count = 0U;
    g_door_state.emergency_release = false;
    
    return ERROR_NONE;
}

/* Function: door_control_process
 * Complexity: 8
 * Traceability: REQ-001, REQ-002, REQ-003, REQ-004, REQ-005
 */
error_t door_control_process(const sensor_data_t* sensors, door_command_t* cmd) {
    error_t err = ERROR_NONE;
    
    /* Defensive programming - validate inputs (mandatory SIL 2+) */
    if ((sensors == NULL) || (cmd == NULL)) {
        return ERROR_NULL_POINTER;
    }
    
    /* REQ-001: Speed interlock - prevent door open if moving */
    if (sensors->speed_kmh > 0U) {
        if (g_door_state.state == DOOR_STATE_OPENING) {
            /* Safety violation - close door immediately */
            cmd->command = DOOR_CMD_CLOSE;
            err = ERROR_SAFETY_VIOLATION;
        }
    }
    
    /* REQ-004: Obstacle detection */
    if (sensors->obstacle_detected) {
        /* REQ-005: Close door when obstacle detected */
        cmd->command = DOOR_CMD_CLOSE;
        g_door_state.state = DOOR_STATE_CLOSING;
    }
    
    /* REQ-007: Safe state on critical failure */
    if (g_door_state.fault_status & FAULT_CRITICAL_MASK) {
        cmd->command = DOOR_CMD_CLOSE;
        g_door_state.state = DOOR_STATE_SAFE;
        err = ERROR_CRITICAL_FAULT;
    }
    
    return err;
}
```

### Step 2: Implement Unit Tests

```bash
/tst create-unit-tests --module door_control
```

**What TST Agent Does**:
- Uses Unity test framework
- Creates test cases for each function
- Tests normal operation
- Tests boundary conditions (mandatory SIL 3)
- Tests fault injection (highly recommended SIL 3)
- Targets 100% coverage (statement/branch/condition)

**Deliverable**: `tests/test_door_control.c` (~300-500 lines)

**Example Unit Test** (test_door_control.c excerpt):
```c
#include "unity.h"
#include "door_control.h"

void setUp(void) {
    /* Initialize before each test */
    door_control_init();
}

void tearDown(void) {
    /* Cleanup after each test */
}

/* Test REQ-001: Speed interlock */
void test_door_control_speed_interlock(void) {
    sensor_data_t sensors = {
        .speed_kmh = 50U,  /* Train moving */
        .door_closed = true,
        .door_locked = true,
        .obstacle_detected = false
    };
    door_command_t cmd;
    
    error_t err = door_control_process(&sensors, &cmd);
    
    /* Expect door command is CLOSE (not OPEN) */
    TEST_ASSERT_EQUAL(DOOR_CMD_CLOSE, cmd.command);
}

/* Test REQ-004, REQ-005: Obstacle detection */
void test_door_control_obstacle_detection(void) {
    sensor_data_t sensors = {
        .speed_kmh = 0U,
        .door_closed = false,
        .door_locked = false,
        .obstacle_detected = true  /* Obstacle present */
    };
    door_command_t cmd;
    
    error_t err = door_control_process(&sensors, &cmd);
    
    /* Expect door command is CLOSE */
    TEST_ASSERT_EQUAL(DOOR_CMD_CLOSE, cmd.command);
    TEST_ASSERT_EQUAL(ERROR_NONE, err);
}

/* Fault injection test (SIL 3) */
void test_door_control_null_pointer(void) {
    door_command_t cmd;
    
    /* Pass NULL pointer - test defensive programming */
    error_t err = door_control_process(NULL, &cmd);
    
    /* Expect error return */
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, err);
}
```

### Step 3: Run Unit Tests and Measure Coverage

```bash
/tst run-unit-tests --coverage
```

**What TST Agent Does**:
- Compiles tests with coverage instrumentation (gcov)
- Executes all unit tests
- Generates coverage report (lcov/gcovr)
- Verifies coverage meets SIL 3 requirements (100%)
- Generates test report

**Expected Output**:
```
Unit Test Results:
- Tests Run: 25
- Tests Passed: 25
- Tests Failed: 0

Coverage Results (gcov):
- Statement Coverage: 100.0% (250/250 lines)
- Branch Coverage: 100.0% (80/80 branches)
- Condition Coverage: 100.0% (40/40 conditions)

SIL 3 Requirements: MET
✅ Statement coverage ≥ 100% (MANDATORY SIL 3)
✅ Branch coverage ≥ 100% (MANDATORY SIL 3)
✅ Condition coverage ≥ 100% (MANDATORY SIL 3)
```

**Deliverable**: `docs/testing/DOC-UTEST-MOD-2026-001.md` (Unit Test Report for door_control)

### Step 4: Quality Assurance - Code Review

**MANDATORY for all SIL levels, BEFORE verification**

```bash
/qua review-code --module door_control
```

**What QUA Agent Checks**:
- ✅ MISRA C:2012 compliance (run PC-lint/Cppcheck)
  - **Zero mandatory violations** (SIL 2+)
  - Document deviations with rationale
- ✅ Cyclomatic complexity ≤10 (SIL 3)
- ✅ Static allocation only (no malloc/free)
- ✅ Defensive programming (all inputs validated, all returns checked)
- ✅ No recursion (highly recommended SIL 3)
- ✅ Traceability comments present (REQ-XXX references)

**Deliverable**: `docs/quality/DOC-QA-CODE-MOD-2026-001.md` (QA Code Review Report for door_control)

**Example QA Report**:
```
Module: door_control.c
Reviewer: QUA Agent
Date: 2026-02-23

MISRA C:2012 Compliance:
- Mandatory Rules: 0 violations ✅
- Required Rules: 2 violations (documented with rationale)
- Advisory Rules: 5 violations

Complexity Analysis:
- door_control_init: Complexity 3 ✅
- door_control_process: Complexity 8 ✅
- Maximum complexity: 8 (limit: 10 for SIL 3) ✅

Defensive Programming:
✅ All function inputs validated (NULL checks)
✅ All return values checked
✅ All error conditions handled

Static Allocation:
✅ No dynamic allocation (malloc/calloc/realloc/free)
✅ All buffers statically allocated

Conclusion: PASS - Code ready for verification
```

### Step 5: Verification - Static Analysis

```bash
/ver verify-module --module door_control
```

**What VER Agent Does**:
- Runs static analysis tools:
  - PC-lint Plus (MISRA C checker)
  - Cppcheck (general static analysis)
  - Clang Static Analyzer
- Runs complexity analysis (Lizard)
- Verifies QA review was performed (checks for QA report)
- Verifies coverage meets SIL 3 requirements
- Collects evidence for verification report

**Deliverable**: `docs/verification/DOC-VER-MOD-2026-001.md` (Verification Report for door_control)

### Step 6: Repeat for All Modules

Implement, test, review, and verify each module:
- sensor_monitor.c
- safety_interlock.c
- fault_manager.c
- door_interface.c

**Pro Tip**: Use `/imp implement-all` to batch process all modules from design.

### Step 7: Gate Check - Transition to Phase 5

```bash
/cod gate-check implementation
```

**What COD Checks** (SIL 3 - Strict Mode):
- ✅ All modules implemented (5 modules: door_control, sensor_monitor, safety_interlock, fault_manager, door_interface)
- ✅ All unit tests passed (100% pass rate)
- ✅ All coverage requirements met (100% statement/branch/condition for SIL 3)
- ✅ All QA reviews passed (mandatory - performed BEFORE verification)
- ✅ All verification reports complete (static analysis, complexity, coverage)
- ✅ Traceability complete (code to design to requirements)
- ✅ Baseline established (CM)

**Expected Output**:
```
Phase 4 (Component Implementation & Testing) Gate Check: PASS

Entry Criteria for Phase 5 (Integration):
✅ All modules implemented (5/5)
✅ Unit tests: 125 passed, 0 failed
✅ Coverage: 100% statement/branch/condition (SIL 3 requirement met)
✅ QA reviews: 5/5 passed
✅ Verification reports: 5/5 complete
✅ Baseline IMP-001 established

Authorization: Proceed to Phase 5 (Integration)
```

---

## Phase 5: Integration

### Overview

Integrate modules and perform integration testing. Requirements:
- **Progressive integration** (bottom-up, top-down, or sandwich)
- **Interface testing** (mandatory all SILs)
- **Performance testing** (highly recommended SIL 3)
- **Integration coverage** (target 100% for SIL 3)

### Step 1: Create Integration Plan

```bash
/int create-integration-plan
```

**What INT Agent Does**:
- Analyzes module dependencies
- Defines integration sequence (e.g., bottom-up)
- Identifies integration test scenarios
- Plans interface testing
- Plans performance testing

**Integration Sequence Example** (bottom-up):
```
Level 1: Hardware abstraction
  - door_interface.c (standalone)

Level 2: Monitoring and safety
  - sensor_monitor.c + door_interface.c
  - fault_manager.c + door_interface.c

Level 3: Safety interlock
  - safety_interlock.c + sensor_monitor.c + fault_manager.c

Level 4: Top-level control
  - door_control.c + all modules
```

**Deliverable**: `docs/integration/DOC-INTPLAN-2026-001.md`

### Step 2: Perform Integration (Level by Level)

```bash
/int integrate-level --level 1
```

**What INT Agent Does**:
- Integrates modules per plan
- Creates integration test cases
- Tests interfaces between modules
- Measures integration coverage
- Documents integration issues

**Example Integration Test** (Level 3):
```c
/* Integration Test: safety_interlock + sensor_monitor + fault_manager */
void test_integration_safety_chain(void) {
    /* Initialize all modules */
    sensor_monitor_init();
    fault_manager_init();
    safety_interlock_init();
    
    /* Simulate sensor input (speed > 0) */
    sensor_data_t sensors = {.speed_kmh = 50U};
    sensor_monitor_update(&sensors);
    
    /* Process safety interlock */
    interlock_status_t status;
    safety_interlock_check(&status);
    
    /* Verify door opening is blocked */
    TEST_ASSERT_EQUAL(INTERLOCK_BLOCKED, status.door_open_allowed);
}
```

### Step 3: Run Integration Tests

```bash
/int run-integration-tests --coverage
```

**Expected Output**:
```
Integration Test Results:
- Level 1: 10 tests, 10 passed
- Level 2: 20 tests, 20 passed
- Level 3: 15 tests, 15 passed
- Level 4: 25 tests, 25 passed

Integration Coverage:
- Interface Coverage: 100% (all interfaces tested)
- Integration Branch Coverage: 98.5%

SIL 3 Requirements: MET
✅ Interface testing complete (MANDATORY all SILs)
✅ Performance testing complete (MANDATORY SIL 3)
```

**Deliverable**: `docs/testing/DOC-INTTEST-2026-001.md` (Integration Test Report)

### Step 4: Performance Testing (SIL 3 Mandatory)

```bash
/int performance-test
```

**What INT Agent Tests**:
- Worst-case execution time (WCET)
- Memory usage (static allocation)
- Interrupt response time
- CPU utilization

**Example Performance Results**:
```
Performance Test Results:

Worst-Case Execution Time (WCET):
- door_control_process: 850 μs (requirement: < 1000 μs) ✅
- sensor_monitor_read: 120 μs (requirement: < 200 μs) ✅
- safety_interlock_check: 300 μs (requirement: < 500 μs) ✅

Memory Usage:
- Total RAM: 2.4 KB (static allocation only) ✅
- Stack depth: 512 bytes (max) ✅

Conclusion: All performance requirements met
```

**Deliverable**: `docs/testing/DOC-PERFTEST-2026-001.md` (Performance Test Report)

### Step 5: Quality Assurance - Integration Review

```bash
/qua review-integration
```

**What QUA Agent Checks**:
- ✅ Integration plan followed
- ✅ All integration tests passed
- ✅ Interface testing complete (mandatory)
- ✅ Performance testing complete (mandatory SIL 3)
- ✅ Integration coverage adequate
- ✅ Traceability maintained

**Deliverable**: `docs/quality/DOC-QA-INT-2026-001.md` (QA Integration Review Report)

### Step 6: Gate Check - Transition to Phase 6

```bash
/cod gate-check integration
```

**What COD Checks** (SIL 3 - Strict Mode):
- ✅ Integration plan complete
- ✅ All integration levels complete (4/4)
- ✅ All integration tests passed (70/70 tests)
- ✅ Interface testing complete (mandatory)
- ✅ Performance testing complete (mandatory SIL 3)
- ✅ QA review passed
- ✅ Baseline established (CM)

**Expected Output**:
```
Phase 5 (Integration) Gate Check: PASS

Entry Criteria for Phase 6 (Validation):
✅ Integration plan complete (DOC-INTPLAN-2026-001)
✅ Integration tests: 70 passed, 0 failed
✅ Interface testing complete (100% interfaces tested)
✅ Performance testing complete (all WCET requirements met)
✅ QA review passed (DOC-QA-INT-2026-001)
✅ Baseline INT-001 established

Authorization: Proceed to Phase 6 (Validation)
```

---

## Phase 6: Validation

### Overview

Validate that the **complete system** meets **user requirements** in the **target environment**. Independent validation mandatory for SIL 3.

### Step 1: Create Validation Test Specification

```bash
/val create-validation-tests
```

**What VAL Agent Does**:
- Creates system-level test scenarios
- Maps tests to requirements (traceability)
- Defines operational scenarios (realistic usage)
- Plans target environment testing (hardware-in-loop if available)
- Defines acceptance criteria

**Example Validation Tests**:
```
VTS-001: Normal Door Operation Sequence
  - Scenario: Train stopped, driver requests door open
  - Expected: Doors open, sensors confirm open state
  - Traceability: REQ-001, REQ-002, REQ-003

VTS-002: Speed Interlock Validation
  - Scenario: Train moving at 30 km/h, attempt door open
  - Expected: Door open request blocked, safety alarm raised
  - Traceability: REQ-001

VTS-003: Obstacle Detection Validation
  - Scenario: Door closing, obstacle detected mid-cycle
  - Expected: Door reverses to open, obstacle alarm raised
  - Traceability: REQ-004, REQ-005

VTS-004: Emergency Release Validation
  - Scenario: Emergency release activated during normal operation
  - Expected: Doors immediately release, emergency flag set
  - Traceability: REQ-008
```

**Deliverable**: `docs/validation/DOC-VTS-2026-001.md` (Validation Test Specification)

### Step 2: Execute Validation Tests

```bash
/val run-validation-tests
```

**What VAL Agent Does**:
- Executes validation tests on target (or simulator if target unavailable)
- Records test results (pass/fail/blocked)
- Captures evidence (logs, screenshots, videos)
- Identifies discrepancies

**Expected Output**:
```
Validation Test Execution Results:

VTS-001: Normal Door Operation Sequence - PASS
VTS-002: Speed Interlock Validation - PASS
VTS-003: Obstacle Detection Validation - PASS
VTS-004: Emergency Release Validation - PASS
... (20 more tests)

Summary:
- Total Tests: 25
- Passed: 25
- Failed: 0
- Blocked: 0

Requirements Coverage:
- Total Requirements: 8
- Requirements Validated: 8 (100%)
- Traceability Complete: YES ✅
```

**Deliverable**: 
- `docs/validation/DOC-VALTEST-2026-001.md` (Validation Test Report)
- `docs/validation/DOC-VALREP-2026-001.md` (Validation Report - summary)

### Step 3: Customer Acceptance

For SIL 3, **independent Validator** performs final review and obtains customer acceptance.

```bash
/val customer-acceptance
```

**What VAL Agent Does**:
- Prepares acceptance package (all deliverables)
- Presents validation results to customer
- Records customer feedback
- Obtains formal acceptance signature

**Deliverable**: `docs/validation/DOC-ACCEPTANCE-2026-001.md` (Customer Acceptance Record)

### Step 4: Quality Assurance - Validation Review

```bash
/qua review-validation
```

**What QUA Agent Checks**:
- ✅ Validation Test Specification template compliant
- ✅ All validation tests executed
- ✅ Requirements coverage 100%
- ✅ Traceability complete (tests to requirements)
- ✅ Customer acceptance obtained (SIL 3)

**Deliverable**: `docs/quality/DOC-QA-VAL-2026-001.md` (QA Validation Review Report)

### Step 5: Gate Check - Transition to Phase 7

```bash
/cod gate-check validation
```

**What COD Checks** (SIL 3 - Strict Mode):
- ✅ Validation Test Specification complete
- ✅ All validation tests passed (25/25)
- ✅ Requirements coverage 100% (8/8 requirements validated)
- ✅ Customer acceptance obtained
- ✅ QA review passed
- ✅ Validation report complete
- ✅ Baseline established (CM)

**Expected Output**:
```
Phase 6 (Validation) Gate Check: PASS

Entry Criteria for Phase 7 (Assessment):
✅ Validation tests: 25 passed, 0 failed
✅ Requirements validated: 8/8 (100%)
✅ Customer acceptance obtained (DOC-ACCEPTANCE-2026-001)
✅ QA review passed (DOC-QA-VAL-2026-001)
✅ Validation report complete (DOC-VALREP-2026-001)
✅ Baseline VAL-001 established

Authorization: Proceed to Phase 7 (Assessment) [SIL 3 - MANDATORY]
```

---

## Phase 7: Assessment (SIL 3-4)

### Overview

**Independent safety assessment** - MANDATORY for SIL 3-4. Assessor evaluates compliance with EN 50128 and approves for deployment.

### Step 1: Prepare Assessment Package

```bash
/pm prepare-assessment-package
```

**What PM Agent Does**:
- Collects all deliverables (28+ documents)
- Organizes by phase (Planning, Requirements, Design, Implementation, Integration, Validation)
- Prepares evidence package (test reports, QA reviews, verification reports)
- Creates assessment index

**Assessment Package Contents**:
```
Phase 1 - Planning:
- DOC-SQAP-2026-001.md (Software Quality Assurance Plan)
- DOC-SCMP-2026-001.md (Software Configuration Management Plan)
- DOC-SVP-2026-001.md (Software Verification Plan)
- DOC-SVAP-2026-001.md (Software Validation Plan)

Phase 2 - Requirements:
- DOC-SRS-2026-001.md (Software Requirements Specification)
- DOC-HAZLOG-2026-001.md (Hazard Log)

Phase 3 - Design:
- DOC-SAS-2026-001.md (Software Architecture Specification)
- DOC-SDS-2026-001.md (Software Design Specification)
- DOC-SIS-2026-001.md (Software Interface Specification)
- DOC-FMEA-DES-2026-001.md (Design FMEA)

Phase 4 - Implementation:
- Source code (5 modules)
- Unit test reports (5 reports)
- QA code reviews (5 reports)
- Verification reports (5 reports)

Phase 5 - Integration:
- DOC-INTPLAN-2026-001.md (Integration Plan)
- DOC-INTTEST-2026-001.md (Integration Test Report)
- DOC-PERFTEST-2026-001.md (Performance Test Report)

Phase 6 - Validation:
- DOC-VTS-2026-001.md (Validation Test Specification)
- DOC-VALTEST-2026-001.md (Validation Test Report)
- DOC-VALREP-2026-001.md (Validation Report)
- DOC-ACCEPTANCE-2026-001.md (Customer Acceptance Record)

Supporting Documents:
- Traceability matrices (forward and backward)
- QA review reports (all phases)
- Configuration management records (baselines, change requests)
```

### Step 2: Independent Assessment

**Note**: Assessment is performed by **independent Assessor** (not part of development team). For this tutorial, we simulate using `/pm` as assessment coordinator.

```bash
/pm request-assessment --assessor "Independent Safety Assessor"
```

**What Assessor Checks**:
1. **Process Compliance** - All EN 50128 lifecycle activities performed
2. **Technique Compliance** - Mandatory techniques applied (per Table A.x)
3. **Document Quality** - All deliverables complete and template-compliant
4. **Traceability** - Forward and backward traceability complete
5. **Quality Evidence** - QA reviews, verification reports, test coverage
6. **Independence** - Verification and validation performed by independent teams
7. **SIL 3 Requirements** - All SIL 3 specific requirements met

**Assessment Activities** (typically 2-4 weeks):
- Document review (all 28+ deliverables)
- Interviews with development team
- Code inspection (sample basis)
- Tool qualification review
- Configuration audit (PCA, FCA)
- Traceability verification

### Step 3: Assessment Report

Assessor creates **Assessment Report** documenting findings:

**Deliverable**: `docs/assessment/DOC-ASSESS-2026-001.md` (Assessment Report)

**Example Assessment Report**:
```
Assessment Report - Train Door Control System
Assessor: Independent Safety Assessor
Date: 2026-03-15
SIL Level: 3

1. Process Compliance: PASS
   ✅ All lifecycle phases complete (Phases 1-6)
   ✅ Phase gates enforced (COD strict mode)
   ✅ Configuration management active throughout

2. Technique Compliance: PASS
   ✅ Mandatory techniques applied (Table A.2, A.3, A.4, A.5, A.6, A.7)
   ✅ Structured methodology used (design, implementation)
   ✅ Modular approach (design, implementation)
   ✅ Static analysis performed (verification)
   ✅ Dynamic analysis and testing (unit, integration, validation)

3. Document Quality: PASS
   ✅ All 28 deliverables complete
   ✅ Document templates compliant
   ✅ QA reviews performed for all documents

4. Traceability: PASS
   ✅ Requirements to design: 100%
   ✅ Design to code: 100%
   ✅ Code to tests: 100%
   ✅ Tests to requirements: 100%

5. Quality Evidence: PASS
   ✅ MISRA C:2012 compliance: 0 mandatory violations
   ✅ Cyclomatic complexity: Max 8 (limit 10 for SIL 3)
   ✅ Coverage: 100% statement/branch/condition
   ✅ QA code reviews: 5/5 passed

6. Independence: PASS
   ✅ Verification performed by independent VER agent
   ✅ Validation performed by independent VAL agent
   ✅ Assessor independent from development

7. SIL 3 Requirements: PASS
   ✅ Static allocation only (no dynamic memory)
   ✅ Defensive programming (all inputs validated)
   ✅ Complexity limits met (≤10)
   ✅ Coverage requirements met (100%)
   ✅ Independent V&V performed

ASSESSMENT CONCLUSION: PASS
Recommendation: APPROVE for deployment

Assessor Signature: [Signature]
Date: 2026-03-15
```

### Step 4: Gate Check - Transition to Phase 8

```bash
/cod gate-check assessment
```

**What COD Checks** (SIL 3 - Strict Mode):
- ✅ Assessment complete (independent Assessor)
- ✅ Assessment report approved
- ✅ All findings resolved (if any)
- ✅ Assessor recommendation: APPROVE

**Expected Output**:
```
Phase 7 (Assessment) Gate Check: PASS

Entry Criteria for Phase 8 (Deployment):
✅ Assessment complete (DOC-ASSESS-2026-001)
✅ Assessment conclusion: PASS
✅ Assessor recommendation: APPROVE for deployment
✅ All findings resolved

Authorization: Proceed to Phase 8 (Deployment)
```

---

## Phase 8: Deployment

### Overview

Final phase - package software for deployment, create release documentation, and deploy to target environment.

### Step 1: Create Release Package

```bash
/pm create-release-package --version "1.0.0"
```

**What PM Agent Creates**:
- Binary image (compiled for target platform)
- Release notes
- Installation instructions
- Configuration files
- Deployment checklist

**Deliverable**: `release/train_door_control_v1.0.0/`

**Release Package Contents**:
```
release/train_door_control_v1.0.0/
├── bin/
│   └── door_control.elf         # Compiled binary
├── docs/
│   └── DOC-RELEASE-2026-001.md  # Release notes
├── config/
│   └── door_control_config.h    # Configuration file
└── install/
    └── INSTALL.md               # Installation instructions
```

### Step 2: Configuration Audit

Configuration Manager performs final audit:

```bash
/cm audit-configuration
```

**What CM Agent Checks**:
- ✅ All configuration items under version control
- ✅ All baselines established (8 baselines: REQ, DES, IMP, INT, VAL, etc.)
- ✅ All change requests closed
- ✅ Release tag created (v1.0.0)
- ✅ Traceability records complete

**Deliverable**: `docs/configuration/DOC-PCA-2026-001.md` (Physical Configuration Audit)

### Step 3: Deployment

Deploy to target environment (or customer delivery):

```bash
/pm deploy --target production --version "1.0.0"
```

**Deployment Activities**:
- Transfer binary to target hardware
- Configure system parameters
- Perform installation verification test (IVT)
- Obtain operational acceptance
- Archive all deliverables

**Deliverable**: `docs/deployment/DOC-DEPLOY-2026-001.md` (Deployment Record)

### Step 4: Project Closure

```bash
/cod close-project
```

**What COD Does**:
- Marks all phases complete
- Archives project state
- Generates final project report
- Updates LIFECYCLE_STATE.md

**Expected Output**:
```
Project: Train Door Control System
SIL Level: 3
Status: COMPLETE

Phase Summary:
✅ Phase 0: Initialization - COMPLETE
✅ Phase 1: Planning - COMPLETE
✅ Phase 2: Requirements - COMPLETE
✅ Phase 3: Architecture & Design - COMPLETE
✅ Phase 4: Component Implementation & Testing - COMPLETE
✅ Phase 5: Integration - COMPLETE
✅ Phase 6: Validation - COMPLETE
✅ Phase 7: Assessment - COMPLETE (PASS)
✅ Phase 8: Deployment - COMPLETE

Total Deliverables: 32 documents
Total Lines of Code: 2,500 (C source)
Total Test Cases: 150 (unit + integration + validation)
Final Coverage: 100% (statement/branch/condition)

PROJECT SUCCESSFULLY CLOSED
Date: 2026-03-20
```

### Congratulations!

You've completed a full EN 50128 SIL 3 software development lifecycle! 🎉

**What You've Accomplished**:
- ✅ Created 32 EN 50128-compliant deliverables
- ✅ Implemented 2,500+ lines of MISRA C:2012 compliant code
- ✅ Achieved 100% test coverage (unit + integration + validation)
- ✅ Passed independent assessment
- ✅ Deployed safety-critical railway software

---

## PM Automation Guide

**Streamlined Development with Project Manager Orchestration**

Now that you understand the EN 50128 lifecycle (from the manual mode walkthrough above), here's how to use **PM Automation Mode** for streamlined production development.

### Overview

Instead of invoking each agent manually, the **Project Manager (PM)** executes complete phases with automatic agent coordination:

```
/pm execute-phase <phase-name>
    ↓
PM orchestrates agents in correct sequence
    ↓
Automatic quality gates and verification
    ↓
COD gate check approval
```

### PM Automation Workflow

#### Phase 0: Project Initialization (Same as Manual Mode)

```bash
mkdir train_door_control_automated
cd train_door_control_automated

/cod plan --sil 3 --project "Train Door Control System"
```

#### Phase 1: Planning

```bash
/pm execute-phase planning
```

**What PM Does**:
1. `/qua create-sqap --sil 3` - Create Software Quality Assurance Plan
2. `/cm create-scmp --sil 3` - Create Software Configuration Management Plan
3. `/ver create-svp --sil 3` - Create Software Verification Plan
4. `/val create-svap --sil 3` - Create Software Validation Plan
5. `/qua review-plans` - QA review of all plans
6. `/cod gate-check planning` - Automatic gate check

**User Interaction**: PM may prompt for approvals (e.g., plan review)

**Result**: Phase 1 complete, all planning documents created

#### Phase 2: Requirements Specification

```bash
/pm execute-phase requirements
```

**What PM Does**:
1. `/req create-srs --sil 3` - REQ agent creates Software Requirements Specification
   - **User approval required** (COD enforces)
   - User provides requirements interactively
2. `/saf analyze-hazards` - SAF agent performs hazard analysis
3. `/saf fmea --phase requirements` - Preliminary FMEA
4. `/qua review-requirements` - QA template compliance check
5. `/ver verify-requirements` - VER agent verifies traceability
6. `/cm baseline create REQ-001` - CM creates baseline
7. `/cod gate-check requirements` - Automatic gate check

**User Interaction**: 
- Provide requirements when REQ prompts
- Approve hazard analysis results

**Result**: Phase 2 complete, SRS, Hazard Log, traceability established

#### Phase 3: Architecture & Design

```bash
/pm execute-phase design
```

**What PM Does**:
1. `/des create-sas` - Software Architecture Specification
2. `/des create-sds` - Software Design Specification  
3. `/des create-sis` - Software Interface Specifications
4. `/saf fmea --phase design` - Design FMEA
5. `/qua review-design` - QA design review (complexity, modularity, defensive programming)
6. `/ver verify-design` - VER agent verifies traceability and design compliance
7. `/cm baseline create DES-001` - CM creates design baseline
8. `/cod gate-check design` - Automatic gate check

**User Interaction**: Review and approve architecture decisions

**Result**: Phase 3 complete, SAS, SDS, SIS, Design FMEA

#### Phase 4: Component Implementation & Testing

```bash
/pm execute-phase implementation
```

**What PM Does** (for each module):
1. `/imp implement-module --name <module>` - IMP agent generates C code
2. `/tst create-unit-tests --module <module>` - TST agent creates unit tests
3. `/tst run-unit-tests --module <module> --coverage` - Execute tests with coverage
4. `/qua review-code --module <module>` - QA code review (MISRA C, complexity, defensive programming)
5. `/ver verify-module --module <module>` - VER agent runs static analysis
6. Repeat for all modules
7. `/cm baseline create IMP-001` - CM creates implementation baseline
8. `/cod gate-check implementation` - Automatic gate check

**User Interaction**: Review MISRA C deviations (if any)

**Result**: Phase 4 complete, all modules implemented with 100% test coverage

#### Phase 5: Integration

```bash
/pm execute-phase integration
```

**What PM Does**:
1. `/int create-integration-plan` - INT agent creates integration plan
2. `/int integrate-level --level 1` - Progressive integration (Level 1)
3. `/int integrate-level --level 2` - Progressive integration (Level 2)
4. `/int integrate-level --level 3` - Progressive integration (Level 3)
5. `/int integrate-level --level 4` - Progressive integration (Level 4)
6. `/int run-integration-tests --coverage` - Execute integration tests
7. `/int performance-test` - Performance testing (SIL 3 mandatory)
8. `/qua review-integration` - QA integration review
9. `/ver verify-integration` - VER agent verifies integration
10. `/cm baseline create INT-001` - CM creates integration baseline
11. `/cod gate-check integration` - Automatic gate check

**User Interaction**: Minimal (review integration test results)

**Result**: Phase 5 complete, all modules integrated with performance validated

#### Phase 6: Validation

```bash
/pm execute-phase validation
```

**What PM Does**:
1. `/val create-validation-tests` - VAL agent creates validation test specification
2. `/val run-validation-tests` - Execute validation tests on target
3. `/val customer-acceptance` - Obtain customer acceptance
4. `/qua review-validation` - QA validation review
5. `/ver verify-validation` - VER agent verifies validation completeness
6. `/cm baseline create VAL-001` - CM creates validation baseline
7. `/cod gate-check validation` - Automatic gate check

**User Interaction**: Customer interaction for acceptance

**Result**: Phase 6 complete, system validated, customer acceptance obtained

#### Phase 7: Assessment (SIL 3-4)

```bash
/pm execute-phase assessment
```

**What PM Does**:
1. `/pm prepare-assessment-package` - Collect all deliverables
2. `/pm request-assessment --assessor "Independent Safety Assessor"` - Coordinate assessment
3. Wait for independent assessor to complete assessment
4. `/pm review-assessment-findings` - Address any findings
5. `/cod gate-check assessment` - Automatic gate check (after assessor approval)

**User Interaction**: Coordinate with independent assessor, address findings

**Result**: Phase 7 complete, assessment passed, approval for deployment

#### Phase 8: Deployment

```bash
/pm execute-phase deployment
```

**What PM Does**:
1. `/pm create-release-package --version "1.0.0"` - Create release package
2. `/cm audit-configuration` - CM performs Physical Configuration Audit (PCA)
3. `/pm deploy --target production --version "1.0.0"` - Deploy to target
4. `/cod close-project` - Close project

**User Interaction**: Deployment verification

**Result**: Phase 8 complete, software deployed, project closed

---

### PM Automation Benefits

**Comparison: Manual Mode vs PM Automation Mode**

| Aspect | Manual Mode | PM Automation Mode |
|--------|-------------|-------------------|
| **Commands per phase** | 5-10+ individual commands | 1 command per phase |
| **Agent sequencing** | User manages | PM handles automatically |
| **Quality gates** | User invokes QUA manually | PM invokes automatically |
| **Verification** | User invokes VER manually | PM invokes automatically |
| **COD gate checks** | User invokes manually | PM invokes automatically |
| **Learning curve** | High (need to know EN 50128 details) | Low (PM guides workflow) |
| **Flexibility** | Maximum (fine-grained control) | Medium (phase-level control) |
| **Error prevention** | User must remember sequence | PM prevents out-of-sequence steps |
| **Best for** | Learning, expert customization | Production, streamlined development |

### When to Use Each Mode

**Use PM Automation Mode when:**
- ✅ You want streamlined development
- ✅ You're working on production projects
- ✅ Your team is new to EN 50128
- ✅ You want to reduce errors from missed steps
- ✅ You prefer single-command-per-phase workflow

**Use Manual Mode when:**
- ✅ You're learning EN 50128 lifecycle details
- ✅ You need to iterate on specific activities (e.g., just requirements)
- ✅ You're an expert and need fine-grained control
- ✅ You're debugging or customizing workflows
- ✅ You're following educational tutorials

### Switching Between Modes

You can **mix modes** in the same project:

```bash
# Use PM automation for most phases
/pm execute-phase requirements
/pm execute-phase design

# Switch to manual mode to iterate on implementation
/imp implement-module --name door_control
/tst run-unit-tests --module door_control
# Fix issues, re-run tests

# Back to PM automation for integration
/pm execute-phase integration
```

**COD tracks progress regardless of mode** - use `/cod status` to check phase completion.

---

## Advanced Topics

### Multi-Workspace Management

Work on multiple projects simultaneously using workspace switching:

```bash
# Create new workspace for second project
/cod plan --sil 2 --project "Signal Controller" --workspace signal_ctrl

# Switch between workspaces
/cod switch-workspace signal_ctrl
/cod switch-workspace train_door_control

# List all workspaces
/cod list-workspaces
```

**Workspace File** (`.workspace`):
```json
{
  "current": "train_door_control",
  "workspaces": {
    "train_door_control": {
      "project": "Train Door Control System",
      "sil": 3,
      "phase": 8,
      "status": "complete"
    },
    "signal_ctrl": {
      "project": "Signal Controller",
      "sil": 2,
      "phase": 2,
      "status": "in_progress"
    }
  }
}
```

### V&V Manager (VMGR) for SIL 3-4

For SIL 3-4 projects, use **VMGR** (V&V Manager) for independent verification and validation management:

```bash
# Initialize VMGR for SIL 3 project
/vmgr init --sil 3

# Review verification report
/vmgr review-verification --phase implementation

# Review validation report
/vmgr review-validation --phase validation

# Provide V&V approval to COD
/vmgr approve-gate --phase validation

# Check independence requirements
/vmgr independence-check
```

**VMGR Authority**:
- VMGR is **independent** from COD and PM
- VMGR manages VER team (VER reports to VMGR)
- VMGR performs VAL activities
- VMGR provides V&V approval/rejection to COD
- COD enforces gate based on VMGR decision (CANNOT override)

### Traceability Verification

Verify complete traceability at any time:

```bash
# Forward traceability (requirements → design → code → tests)
/ver trace-forward --from requirements

# Backward traceability (tests → code → design → requirements)
/ver trace-backward --from validation-tests

# Full traceability report
/ver traceability-report
```

**Example Traceability**:
```
REQ-001: Speed interlock
  → DES-MOD-001: door_control module
    → CODE: door_control.c:door_control_process (lines 45-60)
      → UTEST: test_door_control_speed_interlock
        → ITEST: test_integration_safety_chain
          → VTEST: VTS-002 (Speed Interlock Validation)
```

### Change Management

Handle requirement changes using Change Control Board (CCB):

```bash
# Create change request
/cm create-change-request --id CR-001 --description "Add door lock timeout"

# CCB review (PM leads CCB)
/pm ccb-review --cr CR-001

# Approve change (triggers impact analysis)
/cm approve-change --cr CR-001

# Implement change (follows full lifecycle for impacted phases)
/req update-requirement --id REQ-009 --description "Door lock timeout 5 seconds"
/des update-design --module door_control
/imp update-code --module door_control
/tst update-tests --module door_control

# Close change request
/cm close-change --cr CR-001
```

### Quality Metrics Dashboard

View project-wide quality metrics:

```bash
/qua metrics-dashboard
```

**Example Output**:
```
Quality Metrics - Train Door Control System

Code Quality:
- MISRA C Violations: 0 mandatory, 5 required, 12 advisory
- Cyclomatic Complexity: Max 8, Avg 4.2
- Lines of Code: 2,500

Test Coverage:
- Statement: 100% (2500/2500 lines)
- Branch: 100% (320/320 branches)
- Condition: 100% (160/160 conditions)

Verification:
- Static Analysis Findings: 0 critical, 3 minor
- Code Reviews: 5/5 passed

Validation:
- System Tests: 25/25 passed
- Customer Acceptance: Obtained

Overall Quality Grade: A+ (SIL 3 requirements met)
```

### CI/CD Integration

Integrate with CI/CD pipeline:

```bash
# Run automated verification (for CI/CD)
/ver ci-verify --module all

# Run automated tests (for CI/CD)
/tst ci-test --coverage --report junit.xml

# Generate quality gate report (for CI/CD)
/qua ci-quality-gate --fail-on-error
```

**Example CI/CD Workflow** (GitHub Actions):
```yaml
name: EN50128 Verification

on: [push, pull_request]

jobs:
  verify:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      
      - name: Run MISRA C Check
        run: /ver ci-verify --module all
      
      - name: Run Unit Tests
        run: /tst ci-test --coverage --report junit.xml
      
      - name: Quality Gate
        run: /qua ci-quality-gate --fail-on-error
      
      - name: Upload Coverage
        uses: codecov/codecov-action@v2
```

---

## Reference Example

For a complete working example, see:
- **`examples/train_door_control2/`** - Completed through Phase 5 (Integration)
  - 32 deliverables
  - 2,500+ lines of C code
  - 100% test coverage
  - Full traceability
  - MISRA C compliant

**Explore the example**:
```bash
cd examples/train_door_control2

# View project state
cat LIFECYCLE_STATE.md

# View requirements
cat docs/requirements/DOC-SRS-2026-001.md

# View source code
cat src/door_control/door_control.c

# View unit tests
cat tests/unit/door_control/test_door_control.c

# View gate check report (Phase 5)
cat docs/gate-checks/DOC-GATE-2026-005.md
```

---

## Next Steps

1. **Try the tutorial yourself** - Create your own SIL 3 project
2. **Explore the example** - Study `examples/train_door_control2/`
3. **Read the lifecycle guide** - See `LIFECYCLE.md` for phase details
4. **Review the agents** - See `AGENTS.md` for role definitions
5. **Join the community** - Contribute to the platform

**Questions?** See `docs/QUICKSTART.md` for help getting started.

**Need support?** Open an issue on GitHub.

---

**Platform Version**: 2.0  
**Last Updated**: 2026-02-23  
**License**: MIT
