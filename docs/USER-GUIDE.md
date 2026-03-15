# EN 50128 Platform User Guide

**Version**: 2.0  
**Date**: 2026-03-15  
**Platform Status**: Production Ready (Phase 3 Complete)  
**Target Audience**: Railway software developers, project managers, safety engineers

---

## Table of Contents

1. [Overview](#overview)
2. [Getting Started](#getting-started)
3. [Platform Architecture](#platform-architecture)
4. [Development Workflow](#development-workflow)
5. [Skill-Based Development](#skill-based-development)
6. [Document-Centric Approach](#document-centric-approach)
7. [Tool Integration](#tool-integration)
8. [Complete Example: Developing a SIL 3 Component](#complete-example-developing-a-sil-3-component)
9. [Best Practices](#best-practices)
10. [Troubleshooting](#troubleshooting)
11. [References](#references)

---

## Overview

### What is the EN 50128 Platform?

The EN 50128 Platform is a **document-centric, skill-based development environment** for creating railway safety software compliant with EN 50128:2011 standard. It provides:

- ✅ **13 specialized skills** covering all EN 50128 lifecycle phases
- ✅ **50+ document templates** for all mandatory deliverables
- ✅ **40+ automation tools** for validation, testing, and verification
- ✅ **Complete V-Model lifecycle** with phase gate enforcement
- ✅ **SIL-aware workflows** (SIL 0-4 support)
- ✅ **MISRA C:2012 compliance** tooling
- ✅ **Traceability management** from requirements to validation
- ✅ **Zero placeholders** - all tools are production-ready

### Key Principles

1. **Document-Centric**: All work products are documents (markdown format)
2. **Skill-Based**: Load specialized skills using the `skill` tool
3. **SIL-Aware**: Workflows adapt to SIL level (0-4)
4. **Tool-Integrated**: Automated validation, testing, and verification
5. **Traceable**: End-to-end traceability from system requirements to validation

### Who Should Use This Platform?

- **Software Developers**: Implementing EN 50128 compliant C code
- **Requirements Engineers**: Creating Software Requirements Specifications
- **Designers**: Developing software architecture and design
- **Testers**: Creating and executing test plans
- **Verifiers**: Performing static analysis and verification
- **Safety Engineers**: Conducting FMEA, FTA, safety analysis
- **Quality Assurance**: Reviewing documents and code
- **Project Managers**: Coordinating lifecycle phases
- **Configuration Managers**: Managing versions and changes

---

## Getting Started

### Prerequisites

**System Requirements**:
- Linux (Ubuntu 20.04+ or Debian-based)
- Git 2.0+
- Python 3.8+
- GCC 11.0+ (for C compilation)
- 4GB RAM minimum, 8GB recommended

**Knowledge Requirements**:
- EN 50128:2011 standard (recommended reading: `std/EN50128-2011.md`)
- C programming language
- MISRA C:2012 (for SIL 2+)
- Git version control

### Installation

**1. Clone the Repository**
```bash
git clone <repository-url>
cd EN50128
```

**2. Install System Tools**
```bash
# Install all MANDATORY tools for SIL 3-4
./install_tools.sh

# Or check what's already installed
./install_tools.sh --check
```

**3. Install Python Tools**
```bash
# Setup virtual environment and install Python packages
./install_python.sh

# Activate the virtual environment
source venv/bin/activate
```

**4. Verify Tool Installation**
```bash
# Check all tools are installed and meet version requirements
source venv/bin/activate
tools/tool-validation/check-tool-versions.sh --sil 3 --verbose
```

Expected output: `[PASS] All tools OK`

**5. Validate Tool Configuration (SIL 2+)**
```bash
# Run automated T2 tool validation
tools/tool-validation/run-all-validations.sh
```

Expected output: `[PASS] All validations passed`

### Verification

Run a quick test to ensure everything works:

```bash
# 1. Check Git
git --version

# 2. Check Python tools
source venv/bin/activate
python3 tools/traceability_manager.py --help
python3 tools/workflow_manager.py --help

# 3. Check static analysis tools
cppcheck --version
clang --version
lizard --version

# 4. Check coverage tools
gcov --version
lcov --version
```

If all commands succeed, you're ready to start!

---

## Platform Architecture

### Directory Structure

```
EN50128/
├── .opencode/
│   └── skills/                   # 13 EN 50128 skills
│       ├── en50128-requirements/
│       ├── en50128-design/
│       ├── en50128-implementation/
│       ├── en50128-testing/
│       ├── en50128-verification/
│       ├── en50128-integration/
│       ├── en50128-validation/
│       ├── en50128-safety/
│       ├── en50128-quality/
│       ├── en50128-configuration/
│       ├── en50128-lifecycle-coordination/
│       ├── en50128-documentation/
│       └── en50128-project-management/
├── docs/                         # Documentation and guides
│   ├── LIFECYCLE.md             # Complete V-Model lifecycle
│   ├── USER-GUIDE.md            # This file
│   ├── phase3-plan.md           # Phase 3 implementation plan
│   └── reports/                 # Phase completion reports
├── std/                          # EN 50128 standard (LLM-friendly)
│   ├── EN50128-2011.md          # Main standard (7,256 lines)
│   ├── EN 50126-1-2017.md       # RAMS Part 1
│   └── EN 50126-2-2017.md       # RAMS Part 2
├── tools/                        # Automation tools
│   ├── traceability_manager.py  # Traceability management (1,539 lines)
│   ├── workflow_manager.py      # Document workflow (900+ lines)
│   ├── workspace.py             # Unified CLI (26K)
│   ├── scripts/                 # Validation scripts
│   │   ├── validate_srs_template.py
│   │   ├── validate_sas_sds_template.py
│   │   ├── validate_test_doc_template.py
│   │   ├── parse_coverage_report.py
│   │   └── generate_test_report.py
│   ├── tool-validation/         # Tool validation
│   │   ├── run-all-validations.sh
│   │   └── check-tool-versions.sh
│   └── mcdc/                    # MC/DC analysis
│       └── mcdc_analyzer.py
├── TOOLS.md                      # Tool catalog (904 lines)
├── AGENTS.md                     # Role definitions
├── LIFECYCLE.md                  # V-Model lifecycle guide
└── SUMMARY.md                    # Project status
```

### Key Files

| File | Purpose | Usage |
|------|---------|-------|
| **LIFECYCLE.md** | Complete V-Model lifecycle guide | START HERE for new projects |
| **TOOLS.md** | Tool catalog with T1/T2/T3 classification | Reference when selecting tools |
| **AGENTS.md** | EN 50128 role definitions | Understand who does what |
| **std/EN50128-2011.md** | Full EN 50128 standard | Reference for compliance |

---

## Development Workflow

### The EN 50128 V-Model

The platform follows the EN 50128 V-Model lifecycle with **8 phases**:

```
Phase 0: Initialization (Project setup)
    ↓
Phase 1: Planning (SQAP, SCMP, SVP, SVaP)
    ↓
Phase 2: Requirements (Software Requirements Specification)
    ↓
Phase 3: Architecture & Design (SAS, SDS)
    ↓
Phase 4: Implementation & Unit Testing (Source code, Unit tests)
    ↓
Phase 5: Integration (Integration tests)
    ↓
Phase 6: Validation (System tests, Validation Report)
    ↓
Phase 7: Assessment (Independent assessment - SIL 3-4 only)
    ↓
Phase 8: Deployment (Release package)
```

**Reference**: See `LIFECYCLE.md` for complete lifecycle guide (190 pages, 4,800 lines)

### Typical Development Flow

**For a New SIL 3 Component:**

1. **Load Requirements Skill** → Define requirements
2. **Load Safety Skill** → Identify hazards, perform FMEA
3. **Load Design Skill** → Create architecture and design
4. **Load Implementation Skill** → Write C code (MISRA C compliant)
5. **Load Testing Skill** → Create and execute unit tests
6. **Load Verification Skill** → Perform static analysis, verify coverage
7. **Load Integration Skill** → Integrate with other components
8. **Load Validation Skill** → Perform system validation
9. **Load Quality Skill** → Code reviews, quality gates
10. **Load Configuration Skill** → Version control, baselines

**At each step**, the platform provides:
- ✅ Document templates (pre-filled with EN 50128 structure)
- ✅ Workflows (step-by-step instructions)
- ✅ Automation tools (validation, testing, reporting)
- ✅ Traceability management (link requirements → tests)
- ✅ Quality checks (MISRA C, complexity, coverage)

---

## Skill-Based Development

### What are Skills?

Skills are **domain-specific knowledge packages** that provide:
- Comprehensive workflows (step-by-step procedures)
- Document templates (EN 50128 compliant)
- Tool integration (validation, testing, analysis)
- Code examples (C patterns, Python scripts)
- EN 50128 coverage (sections, tables, techniques)

### How to Load a Skill

**In OpenCode CLI**:
```
skill en50128-requirements
```

This loads the requirements skill with:
- 160 pages of requirements engineering workflows
- Requirements specification template
- Traceability management workflows
- SIL assignment procedures

### Available Skills (13 Total)

#### Core Development Skills (7)

1. **en50128-requirements** (160 pages, 7 files)
   - Requirements elicitation and analysis
   - Software Requirements Specification (SRS)
   - SIL level assignment
   - Requirements traceability
   - **When to use**: Phase 2 (Requirements)
   - **Tools**: validate_srs_template.py, traceability_manager.py

2. **en50128-design** (310 pages, 10 files)
   - Software architecture design
   - Software detailed design
   - MISRA C design patterns
   - Defensive programming
   - **When to use**: Phase 3 (Architecture & Design)
   - **Tools**: validate_sas_sds_template.py, Cppcheck, Clang

3. **en50128-implementation** (340 pages, 9 files)
   - C programming patterns
   - MISRA C:2012 compliance (178 rules documented)
   - Unit testing with Unity framework
   - Code review checklists (124 items)
   - **When to use**: Phase 4 (Implementation)
   - **Tools**: GCC, Cppcheck, gcov, Unity

4. **en50128-testing** (260 pages, 4 files)
   - Unit testing (component testing)
   - Integration testing
   - Coverage analysis (Table A.21)
   - Test report generation
   - **When to use**: Phases 4, 5, 6 (Testing)
   - **Tools**: Unity, gcov, lcov, generate_test_report.py

5. **en50128-verification** (400 pages, 11 files)
   - Static analysis
   - Complexity analysis
   - Verification reporting (11 report templates)
   - Evidence collection
   - **When to use**: Phases 4, 5, 6 (Verification)
   - **Tools**: Cppcheck, Clang, Lizard, run-all-validations.sh

6. **en50128-integration** (335 pages, 5 files)
   - Progressive integration strategies
   - Hardware/software integration
   - Integration testing
   - Interface testing
   - **When to use**: Phase 5 (Integration)
   - **Tools**: GCC, Valgrind, integration test frameworks

7. **en50128-validation** (335 pages, 4 files)
   - System validation
   - Acceptance testing
   - Operational validation
   - Customer sign-off
   - **When to use**: Phase 6 (Validation)
   - **Tools**: HIL, field test equipment, validation runners

#### Management Skills (4)

8. **en50128-quality** (248 pages, 5 files)
   - Software Quality Assurance Plan (SQAP)
   - Code reviews
   - Quality gates
   - Audits
   - **When to use**: Throughout all phases
   - **Tools**: All validation tools, review checklists

9. **en50128-safety** (350 pages, 5 files)
   - Hazard analysis
   - FMEA (Failure Mode and Effects Analysis)
   - FTA (Fault Tree Analysis)
   - Safety case development
   - **When to use**: Phases 2, 3, 6, 7 (Safety activities)
   - **Tools**: FMEA worksheet generator, FTA calculator

10. **en50128-configuration** (213 pages, 5 files)
    - Version control (Git)
    - Change control (CR process)
    - Baseline management
    - Configuration audits (PCA/FCA)
    - **When to use**: Throughout all phases
    - **Tools**: Git, workspace.py, baseline manager

11. **en50128-lifecycle-coordination** (300 pages, 5 files)
    - V-Model orchestration
    - Phase gate management
    - Traceability management (RTM)
    - Iteration workflows
    - **When to use**: Project coordination (all phases)
    - **Tools**: Gate checker, lifecycle state manager

#### Support Skills (2)

12. **en50128-documentation** (177 pages, 5 files)
    - Document workflows
    - Template automation
    - Document validation
    - Report generation
    - **When to use**: Throughout all phases
    - **Tools**: validate_srs_template.py, validate_sas_sds_template.py, validate_test_doc_template.py

13. **en50128-project-management** (exists, not fully tested)
    - Project coordination
    - Change Control Board (CCB)
    - Risk management
    - Stakeholder communication
    - **When to use**: Throughout project
    - **Tools**: workspace.py wf, project tracking

### Skill Selection by Phase

| Phase | Primary Skills | Support Skills |
|-------|---------------|----------------|
| **Phase 1: Planning** | lifecycle-coordination | quality, configuration, project-management |
| **Phase 2: Requirements** | requirements, safety | quality, configuration, documentation |
| **Phase 3: Design** | design, safety | verification, quality, configuration |
| **Phase 4: Implementation** | implementation, testing | verification, quality, configuration |
| **Phase 5: Integration** | integration, testing | verification, quality, configuration |
| **Phase 6: Validation** | validation | verification, quality, safety, configuration |
| **Phase 7: Assessment** | safety | verification, validation, quality |
| **Phase 8: Deployment** | project-management | configuration, quality |

---

## Document-Centric Approach

### Why Document-Centric?

EN 50128 is fundamentally a **document-driven standard**. All evidence of compliance is captured in documents. The platform makes document creation **easy, automated, and validated**.

### Document Templates

**All 13 skills provide document templates**. Examples:

1. **Software Requirements Specification (SRS)** - from `en50128-requirements`
2. **Software Architecture Specification (SAS)** - from `en50128-design`
3. **Software Design Specification (SDS)** - from `en50128-design`
4. **Component Test Specification** - from `en50128-testing`
5. **Verification Report** - from `en50128-verification`
6. **Validation Report** - from `en50128-validation`
7. **Hazard Log** - from `en50128-safety`
8. **FMEA Worksheet** - from `en50128-safety`
9. **Software Quality Assurance Plan (SQAP)** - from `en50128-quality`
10. **Software Configuration Management Plan (SCMP)** - from `en50128-configuration`

**Total**: 50+ document templates covering all EN 50128 Annex C requirements

### Document Workflow

**1. Create Document from Template**
```bash
# Load skill
skill en50128-requirements

# Copy template to your project
cp .opencode/skills/en50128-requirements/templates/Software-Requirements-Specification-template.md \
   my-project/docs/SRS-MyComponent.md
```

**2. Fill in Document**
- Edit the markdown file
- Follow the structure (already EN 50128 compliant)
- Add your specific requirements

**3. Validate Document**
```bash
# Validate SRS document
python3 tools/scripts/validate_srs_template.py \
    my-project/docs/SRS-MyComponent.md \
    --sil 3

# Output: PASS/FAIL with detailed findings
```

**4. Submit for Review**
```bash
# Submit document for workflow
python3 tools/workflow_manager.py submit \
    --document my-project/docs/SRS-MyComponent.md \
    --workflow-type requirements \
    --sil 3

# Document enters approval workflow
```

**5. Approve Document**
```bash
# Approve document (as each role)
python3 tools/workflow_manager.py approve \
    --document my-project/docs/SRS-MyComponent.md \
    --role DES \
    --decision APPROVE \
    --comment "Requirements clear and testable"

# Repeat for all required approvers (REQ, DES, TST, VER for SIL 3)
```

**6. Baseline Document**
```bash
# After all approvals, baseline the document
git add my-project/docs/SRS-MyComponent.md
git commit -m "Baseline SRS for MyComponent (Gate 2)"
git tag -a baseline-gate2 -m "Gate 2: Requirements Complete"
```

### Document Validation

**All documents are automatically validated** for:
- ✅ Document ID format (DOC-XXX-YYYY-NNN)
- ✅ Document Control table (version, date, author, etc.)
- ✅ Approvals table (SIL-specific approvers)
- ✅ Section completeness
- ✅ Content quality (requirements use SHALL/SHOULD/MAY, etc.)
- ✅ Traceability (MANDATORY SIL 3-4)

**Validation Tools**:
- `validate_srs_template.py` - Software Requirements Specification
- `validate_sas_sds_template.py` - Architecture/Design Specifications
- `validate_test_doc_template.py` - Test Specifications/Reports

---

## Tool Integration

### Tool Categories

**T1 Tools** (No qualification required):
- Text editors (vim, VS Code)
- Version control (Git)
- Python scripts (T1 classification)

**T2 Tools** (Validation required SIL 2+):
- Static analyzers (Cppcheck, Clang)
- Coverage tools (gcov, lcov)
- Complexity tools (Lizard)
- Build tools (GNU Make)

**T3 Tools** (Qualification required SIL 3-4):
- Compilers (GCC)
- Test frameworks (Unity)

### Tool Validation

**Check Tool Versions** (for your SIL level):
```bash
source venv/bin/activate
tools/tool-validation/check-tool-versions.sh --sil 3 --verbose
```

**Validate T2 Tools** (MANDATORY SIL 2+):
```bash
tools/tool-validation/run-all-validations.sh
```

This validates:
- GNU Make (build correctness)
- gcov (coverage accuracy)
- lcov (report generation)
- Cppcheck (static analysis)
- Clang (static analysis)
- Lizard (complexity calculation)

### Tool Usage Examples

**1. Static Analysis (MANDATORY SIL 3-4)**
```bash
# Cppcheck with MISRA addon
cppcheck --enable=all --addon=misra --xml --xml-version=2 \
    src/ 2> cppcheck_report.xml

# Clang static analyzer
scan-build -o analysis_results make

# Check complexity
lizard src/ --CCN 10
```

**2. Code Coverage (MANDATORY SIL 3-4)**
```bash
# Compile with coverage flags
gcc -fprofile-arcs -ftest-coverage -o my_test test.c module.c

# Run tests
./my_test

# Generate coverage report
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html

# Validate coverage against SIL requirements
python3 tools/scripts/parse_coverage_report.py \
    coverage.info --sil 3
```

**3. Test Report Generation**
```bash
# Run tests with JUnit XML output
./run_tests --output junit_results.xml

# Generate EN 50128 Component Test Report
python3 tools/scripts/generate_test_report.py \
    junit_results.xml \
    --output Component-Test-Report.md \
    --sil 3
```

### Traceability Management

**Initialize Traceability Matrix**:
```bash
python3 tools/traceability_manager.py create \
    --project my-project \
    --sil 3
```

**Add Requirements**:
```bash
python3 tools/traceability_manager.py add \
    --id SW-REQ-001 \
    --text "System shall monitor door speed" \
    --sil 3 \
    --parent SYS-REQ-001
```

**Link Design to Requirements**:
```bash
python3 tools/traceability_manager.py link \
    --from SW-REQ-001 \
    --to ARCH-001 \
    --type sw-to-arch
```

**Validate Traceability**:
```bash
python3 tools/traceability_manager.py validate --sil 3
# Expected: 100% coverage for SIL 3
```

**Generate Traceability Report**:
```bash
python3 tools/traceability_manager.py report \
    --format markdown \
    --output Traceability-Report.md
```

---

## Complete Example: Developing a SIL 3 Component

Let's develop a **Door Speed Monitor** component (SIL 3) from start to finish.

### Step 1: Load Requirements Skill

```
skill en50128-requirements
```

**Output**: Requirements skill loaded with 160 pages of workflows

### Step 2: Create Software Requirements Specification

**Copy template**:
```bash
mkdir -p my-project/docs
cp .opencode/skills/en50128-requirements/templates/Software-Requirements-Specification-template.md \
   my-project/docs/SRS-DoorSpeedMonitor.md
```

**Edit document**:
```markdown
# Software Requirements Specification

**Document ID**: DOC-REQ-SRS-001  
**Project**: Door Speed Monitor  
**SIL Level**: 3

## 3. Software Requirements

### 3.1 Functional Requirements

**SW-REQ-001**: The system **SHALL** monitor door closing speed continuously.
- **Rationale**: Safety-critical requirement to prevent door slamming
- **Priority**: HIGH
- **SIL**: 3
- **Traceability**: → SYS-REQ-001

**SW-REQ-002**: The system **SHALL** trigger an alarm if door speed exceeds 0.3 m/s.
- **Rationale**: EN 14752 door safety standard
- **Priority**: HIGH
- **SIL**: 3
- **Traceability**: → SYS-REQ-002

**SW-REQ-003**: The system **SHALL** update speed measurement every 50ms.
- **Rationale**: Response time requirement
- **Priority**: MEDIUM
- **SIL**: 3
- **Traceability**: → SYS-REQ-003
```

**Validate SRS**:
```bash
python3 tools/scripts/validate_srs_template.py \
    my-project/docs/SRS-DoorSpeedMonitor.md \
    --sil 3
```

**Expected output**: `PASS - 0 issues found`

### Step 3: Initialize Traceability

```bash
python3 tools/traceability_manager.py create \
    --project door-speed-monitor \
    --sil 3

python3 tools/traceability_manager.py add \
    --id SW-REQ-001 \
    --text "Monitor door closing speed continuously" \
    --sil 3 \
    --parent SYS-REQ-001

python3 tools/traceability_manager.py add \
    --id SW-REQ-002 \
    --text "Trigger alarm if speed exceeds 0.3 m/s" \
    --sil 3 \
    --parent SYS-REQ-002
```

### Step 4: Load Safety Skill and Perform FMEA

```
skill en50128-safety
```

**Create FMEA Worksheet**:
```bash
cp .opencode/skills/en50128-safety/templates/FMEA-Worksheet-template.md \
   my-project/docs/FMEA-DoorSpeedMonitor.md
```

**Fill in failure modes**:
```markdown
## Failure Mode Analysis

| ID | Component | Failure Mode | Effect | Severity | Occurrence | Detection | RPN | Mitigation |
|----|-----------|--------------|--------|----------|------------|-----------|-----|------------|
| FM-001 | Speed Sensor | No Output | Door speed unmonitored | 9 | 3 | 2 | 54 | Redundant sensor |
| FM-002 | Speed Calc | Incorrect Output | False alarm | 6 | 4 | 3 | 72 | Bounds checking |
| FM-003 | Alarm Logic | Delayed Output | Late alarm | 8 | 2 | 4 | 64 | Watchdog timer |
```

### Step 5: Load Design Skill

```
skill en50128-design
```

**Create Software Architecture Specification**:
```bash
cp .opencode/skills/en50128-design/templates/Software-Architecture-Specification-template.md \
   my-project/docs/SAS-DoorSpeedMonitor.md
```

**Define architecture**:
```markdown
## 5. Software Architecture

### 5.1 Module Structure

```
┌─────────────────────────────────────┐
│      DoorSpeedMonitor (Main)        │
└───────────┬─────────────────────────┘
            │
    ┌───────┴────────┬────────────┐
    │                │            │
┌───▼────┐    ┌──────▼─────┐  ┌─▼────────┐
│ Sensor │    │ SpeedCalc  │  │  Alarm   │
│ Input  │    │            │  │  Output  │
└────────┘    └────────────┘  └──────────┘
```

### 5.2 Module Interfaces

**Module**: SensorInput
- **Function**: `uint16_t ReadSensorPosition(void)`
- **Inputs**: None
- **Outputs**: Position in mm (0-1000)
- **Error Handling**: Returns 0xFFFF on sensor fault
```

**Validate SAS**:
```bash
python3 tools/scripts/validate_sas_sds_template.py \
    my-project/docs/SAS-DoorSpeedMonitor.md \
    --sil 3
```

### Step 6: Load Implementation Skill

```
skill en50128-implementation
```

**Implement in C** (following MISRA C:2012):
```c
/* door_speed_monitor.c */
#include <stdint.h>
#include <stdbool.h>
#include "door_speed_monitor.h"

/* MISRA C:2012 Rule 8.4: Static function */
static uint16_t previous_position = 0U;
static uint32_t previous_time_ms = 0U;

/* Calculate speed in mm/s */
static uint16_t CalculateSpeed(uint16_t current_pos, uint32_t current_time)
{
    uint16_t speed = 0U;
    
    /* Defensive programming: Validate inputs */
    if (current_time > previous_time_ms) {
        uint32_t delta_time = current_time - previous_time_ms;
        int32_t delta_pos = (int32_t)current_pos - (int32_t)previous_position;
        
        /* Defensive: Check for divide by zero */
        if (delta_time > 0U) {
            /* Speed = distance / time */
            speed = (uint16_t)((delta_pos * 1000) / delta_time);
        }
    }
    
    /* Update previous values */
    previous_position = current_pos;
    previous_time_ms = current_time;
    
    return speed;
}

/* Main monitoring function */
ErrorCode_t MonitorDoorSpeed(void)
{
    ErrorCode_t result = ERROR_NONE;
    uint16_t position;
    uint16_t speed;
    uint32_t current_time;
    
    /* Read sensor (SW-REQ-001) */
    position = ReadSensorPosition();
    
    /* Defensive: Validate sensor reading */
    if (position == SENSOR_FAULT) {
        result = ERROR_SENSOR_FAULT;
    } else {
        current_time = GetSystemTime();
        
        /* Calculate speed (SW-REQ-001) */
        speed = CalculateSpeed(position, current_time);
        
        /* Check alarm threshold (SW-REQ-002) */
        if (speed > SPEED_THRESHOLD_MM_S) {
            TriggerAlarm();
        }
    }
    
    return result;
}
```

**Validate MISRA C compliance**:
```bash
cppcheck --enable=all --addon=misra src/door_speed_monitor.c
```

**Check complexity** (MUST be ≤10 for SIL 3):
```bash
lizard src/door_speed_monitor.c --CCN 10
```

### Step 7: Load Testing Skill

```
skill en50128-testing
```

**Create unit tests** (Unity framework):
```c
/* test_door_speed_monitor.c */
#include "unity.h"
#include "door_speed_monitor.h"

void setUp(void) {
    /* Reset state before each test */
}

void tearDown(void) {
    /* Clean up after each test */
}

/* Test: Normal speed calculation (SW-REQ-001) */
void test_CalculateSpeed_NormalConditions(void)
{
    /* Arrange */
    MockSensorPosition(100);  /* 100mm */
    MockSystemTime(0);
    MonitorDoorSpeed();
    
    MockSensorPosition(400);  /* 400mm */
    MockSystemTime(50);       /* 50ms later */
    
    /* Act */
    ErrorCode_t result = MonitorDoorSpeed();
    
    /* Assert */
    TEST_ASSERT_EQUAL(ERROR_NONE, result);
    TEST_ASSERT_EQUAL(6000, GetLastSpeed());  /* 300mm / 50ms = 6000 mm/s */
}

/* Test: Alarm trigger at threshold (SW-REQ-002) */
void test_AlarmTrigger_ExceedsThreshold(void)
{
    /* Arrange */
    MockSensorPosition(0);
    MockSystemTime(0);
    MonitorDoorSpeed();
    
    MockSensorPosition(400);  /* 400mm in 50ms = 8000 mm/s = 8 m/s */
    MockSystemTime(50);
    
    /* Act */
    MonitorDoorSpeed();
    
    /* Assert */
    TEST_ASSERT_TRUE(IsAlarmTriggered());  /* Should trigger (8 m/s > 0.3 m/s) */
}

/* Test: Sensor fault handling */
void test_SensorFault_ReturnsError(void)
{
    /* Arrange */
    MockSensorPosition(SENSOR_FAULT);
    
    /* Act */
    ErrorCode_t result = MonitorDoorSpeed();
    
    /* Assert */
    TEST_ASSERT_EQUAL(ERROR_SENSOR_FAULT, result);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_CalculateSpeed_NormalConditions);
    RUN_TEST(test_AlarmTrigger_ExceedsThreshold);
    RUN_TEST(test_SensorFault_ReturnsError);
    return UNITY_END();
}
```

**Build and run tests with coverage**:
```bash
# Compile with coverage
gcc -fprofile-arcs -ftest-coverage \
    -I unity/src \
    -o test_runner \
    src/door_speed_monitor.c \
    test/test_door_speed_monitor.c \
    unity/src/unity.c

# Run tests
./test_runner

# Generate coverage report
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html

# Validate coverage (MUST be 100% for SIL 3)
python3 tools/scripts/parse_coverage_report.py coverage.info --sil 3
```

**Expected output**: `PASS - Statement: 100%, Branch: 100%`

**Generate test report**:
```bash
python3 tools/scripts/generate_test_report.py \
    test_results.xml \
    --output Component-Test-Report-DoorSpeedMonitor.md \
    --sil 3
```

### Step 8: Load Verification Skill

```
skill en50128-verification
```

**Run static analysis**:
```bash
# Cppcheck
cppcheck --enable=all --xml --xml-version=2 src/ 2> cppcheck_report.xml

# Clang analyzer
scan-build -o clang_results make

# Check complexity
lizard src/ --CCN 10
```

**Create Verification Report**:
```bash
cp .opencode/skills/en50128-verification/templates/Verification-Report-template.md \
   my-project/docs/Verification-Report-DoorSpeedMonitor.md
```

**Fill in verification results**:
```markdown
## 5. Verification Results

### 5.1 Static Analysis Results

| Tool | Version | Issues Found | Critical | Status |
|------|---------|--------------|----------|--------|
| Cppcheck | 2.13.0 | 0 | 0 | ✅ PASS |
| Clang | 18.1.3 | 0 | 0 | ✅ PASS |
| Lizard | 1.21.0 | 0 (CCN max: 5) | 0 | ✅ PASS |

### 5.2 Coverage Results

| Metric | Achieved | Required (SIL 3) | Status |
|--------|----------|------------------|--------|
| Statement Coverage | 100% | 100% | ✅ PASS |
| Branch Coverage | 100% | 100% | ✅ PASS |
| Condition Coverage | 100% | 100% | ✅ PASS |

### 5.3 MISRA C Compliance

| Category | Violations | Status |
|----------|------------|--------|
| Mandatory Rules | 0 | ✅ PASS |
| Required Rules | 2 (justified) | ✅ PASS |
| Advisory Rules | 5 | ⚠️ ACCEPTABLE |

**Overall Verification Result**: ✅ **PASS**
```

### Step 9: Update Traceability

**Link architecture to requirements**:
```bash
python3 tools/traceability_manager.py link \
    --from SW-REQ-001 \
    --to ARCH-DSM-001 \
    --type sw-to-arch

python3 tools/traceability_manager.py link \
    --from SW-REQ-002 \
    --to ARCH-DSM-002 \
    --type sw-to-arch
```

**Link tests to requirements**:
```bash
python3 tools/traceability_manager.py link \
    --from SW-REQ-001 \
    --to TEST-001 \
    --type sw-to-test

python3 tools/traceability_manager.py link \
    --from SW-REQ-002 \
    --to TEST-002 \
    --type sw-to-test
```

**Validate traceability** (100% required for SIL 3):
```bash
python3 tools/traceability_manager.py validate --sil 3
```

**Generate traceability report**:
```bash
python3 tools/traceability_manager.py report \
    --format markdown \
    --output Traceability-Matrix-DoorSpeedMonitor.md
```

### Step 10: Load Quality Skill and Perform Code Review

```
skill en50128-quality
```

**Perform code review** (using checklist from skill):
```bash
# Review checklist has 124 items
# - MISRA C compliance: ✅
# - Complexity ≤10: ✅
# - Defensive programming: ✅
# - Error handling: ✅
# - Traceability comments: ✅
```

**Create Code Review Report**:
```markdown
# Code Review Report

**Reviewer**: John Doe (QUA)  
**Date**: 2026-03-15  
**Component**: DoorSpeedMonitor

## Review Results

| Category | Items Checked | Issues Found | Status |
|----------|---------------|--------------|--------|
| MISRA C Compliance | 178 rules | 0 mandatory violations | ✅ PASS |
| Complexity | All functions | Max CCN: 5 (≤10 required) | ✅ PASS |
| Defensive Programming | All functions | All inputs validated | ✅ PASS |
| Error Handling | All functions | All errors handled | ✅ PASS |
| Traceability | All requirements | 100% coverage | ✅ PASS |

**Overall Result**: ✅ **APPROVED**
```

### Step 11: Baseline and Version Control

```bash
# Add all documents and code
git add my-project/

# Commit with traceability
git commit -m "Complete DoorSpeedMonitor component (SIL 3)

SW-REQ-001: Monitor door closing speed
SW-REQ-002: Trigger alarm at threshold

All verification complete:
- Static analysis: PASS
- Coverage: 100%
- Code review: PASS
- Traceability: 100%

Ready for integration."

# Tag baseline
git tag -a baseline-dsm-v1.0 -m "DoorSpeedMonitor v1.0 - Verified for SIL 3"
```

### Summary: What We Created

✅ **Documents** (7 total):
1. Software Requirements Specification (SRS)
2. FMEA Worksheet
3. Software Architecture Specification (SAS)
4. Component Test Specification
5. Component Test Report
6. Verification Report
7. Code Review Report

✅ **Code** (2 files):
1. `door_speed_monitor.c` (implementation)
2. `test_door_speed_monitor.c` (unit tests)

✅ **Evidence**:
- MISRA C compliance: 0 mandatory violations
- Complexity: CCN ≤ 5 (requirement: ≤10 for SIL 3)
- Coverage: 100% statement/branch/condition (requirement: 100% for SIL 3)
- Traceability: 100% (requirement: 100% for SIL 3)
- Static analysis: 0 issues
- Code review: APPROVED

✅ **Result**: **Component ready for integration** (SIL 3 compliant)

---

## Best Practices

### 1. Always Start with Requirements

❌ **DON'T**: Start coding without written requirements  
✅ **DO**: Load `en50128-requirements` skill first, create SRS

### 2. Maintain Traceability from Day 1

❌ **DON'T**: Add traceability at the end  
✅ **DO**: Initialize traceability matrix in Phase 2, update continuously

### 3. Use Skills Proactively

❌ **DON'T**: Try to remember EN 50128 rules  
✅ **DO**: Load the relevant skill and follow its workflows

### 4. Validate Early and Often

❌ **DON'T**: Wait until the end to validate documents  
✅ **DO**: Run validation tools after every document edit

### 5. Automate Where Possible

❌ **DON'T**: Manually check coverage, complexity, MISRA C  
✅ **DO**: Use automation tools (Cppcheck, Lizard, gcov)

### 6. Follow SIL-Specific Rules

❌ **DON'T**: Use same workflow for all SIL levels  
✅ **DO**: Check SIL-specific requirements (coverage, approvals, etc.)

### 7. Keep Documents in Sync with Code

❌ **DON'T**: Let documents become outdated  
✅ **DO**: Update documents when code changes, maintain traceability

### 8. Use Git Properly

❌ **DON'T**: Commit without clear messages or tags  
✅ **DO**: Use meaningful commit messages, tag baselines, reference CRs

### 9. Independent Verification/Validation (SIL 3-4)

❌ **DON'T**: Let developer verify their own code (SIL 3-4)  
✅ **DO**: Assign independent verifier (VER role) and validator (VAL role)

### 10. Document Everything

❌ **DON'T**: Rely on tribal knowledge  
✅ **DO**: Create documents for all decisions, analyses, reviews

---

## Troubleshooting

### Problem: Tool version check fails

**Symptom**: `check-tool-versions.sh` reports missing or old tools

**Solution**:
```bash
# Install missing tools
./install_tools.sh

# For Python tools
source venv/bin/activate
./install_python.sh

# Re-check
tools/tool-validation/check-tool-versions.sh --sil 3
```

### Problem: MISRA C violations

**Symptom**: Cppcheck reports MISRA C violations

**Solution**:
```bash
# 1. Run Cppcheck with detailed output
cppcheck --enable=all --addon=misra --verbose src/

# 2. Load implementation skill for guidance
skill en50128-implementation

# 3. Check MISRA C rules reference in skill
# File: .opencode/skills/en50128-implementation/resources/misra-c-2012-rules.md

# 4. Fix violations or justify deviations
# Document justified deviations in Software Design Specification
```

### Problem: Coverage < 100% (SIL 3-4)

**Symptom**: `parse_coverage_report.py` reports insufficient coverage

**Solution**:
```bash
# 1. Generate detailed coverage HTML
genhtml coverage.info --output-directory coverage_html

# 2. Open coverage_html/index.html in browser
# 3. Identify uncovered lines (shown in red)
# 4. Add tests for uncovered code paths
# 5. Re-run tests and verify 100% coverage
```

### Problem: Complexity > 10 (SIL 3-4)

**Symptom**: Lizard reports CCN > 10

**Solution**:
```bash
# 1. Identify complex functions
lizard src/ --CCN 10

# 2. Load design skill for refactoring guidance
skill en50128-design

# 3. Refactor complex functions:
#    - Extract sub-functions
#    - Simplify conditional logic
#    - Use lookup tables

# 4. Re-check complexity
lizard src/ --CCN 10
```

### Problem: Document validation fails

**Symptom**: `validate_srs_template.py` reports errors

**Solution**:
```bash
# 1. Run validator with verbose output
python3 tools/scripts/validate_srs_template.py my-doc.md --sil 3 --verbose

# 2. Read error messages carefully (they're specific)
# Example: "Missing Document Control table"

# 3. Load documentation skill for template reference
skill en50128-documentation

# 4. Fix issues based on error messages
# 5. Re-validate
```

### Problem: Traceability gaps

**Symptom**: `traceability_manager.py validate` reports < 100% coverage

**Solution**:
```bash
# 1. Generate gap report
python3 tools/traceability_manager.py report --format markdown

# 2. Identify gaps:
#    - Uncovered requirements (no design/test link)
#    - Orphan design elements (no requirement link)
#    - Untraced code (no design link)

# 3. Add missing links
python3 tools/traceability_manager.py link \
    --from SW-REQ-XXX \
    --to TEST-YYY \
    --type sw-to-test

# 4. Re-validate
python3 tools/traceability_manager.py validate --sil 3
```

### Getting Help

1. **Read the skill documentation**
   - Load the relevant skill and read SKILL.md
   - Check workflow files for step-by-step instructions

2. **Check TOOLS.md**
   - Tool catalog with usage examples
   - T1/T2/T3 classification
   - SIL-specific requirements

3. **Consult EN 50128 standard**
   - `std/EN50128-2011.md` (LLM-friendly version)
   - Search for specific section/table numbers

4. **Check LIFECYCLE.md**
   - Complete V-Model lifecycle guide
   - Phase-by-phase instructions

5. **Review example code**
   - All skills have complete C examples
   - Python automation scripts included

---

## References

### Platform Documentation

| Document | Description | Location |
|----------|-------------|----------|
| **LIFECYCLE.md** | Complete V-Model lifecycle (190 pages) | `docs/LIFECYCLE.md` |
| **TOOLS.md** | Tool catalog (904 lines) | `TOOLS.md` |
| **AGENTS.md** | Role definitions | `AGENTS.md` |
| **USER-GUIDE.md** | This document | `docs/USER-GUIDE.md` |

### Standards

| Standard | Description | Location |
|----------|-------------|----------|
| **EN 50128:2011** | Railway Software Standard | `std/EN50128-2011.md` (7,256 lines) |
| **EN 50126-1:2017** | RAMS Part 1 | `std/EN 50126-1-2017.md` |
| **EN 50126-2:2017** | RAMS Part 2 | `std/EN 50126-2-2017.md` |
| **MISRA C:2012** | C Coding Standard | Documented in `en50128-implementation` skill |

### Skills (13 Total)

| Skill | Pages | Location |
|-------|-------|----------|
| en50128-requirements | 160 | `.opencode/skills/en50128-requirements/` |
| en50128-design | 310 | `.opencode/skills/en50128-design/` |
| en50128-implementation | 340 | `.opencode/skills/en50128-implementation/` |
| en50128-testing | 260 | `.opencode/skills/en50128-testing/` |
| en50128-verification | 400 | `.opencode/skills/en50128-verification/` |
| en50128-integration | 335 | `.opencode/skills/en50128-integration/` |
| en50128-validation | 335 | `.opencode/skills/en50128-validation/` |
| en50128-safety | 350 | `.opencode/skills/en50128-safety/` |
| en50128-quality | 248 | `.opencode/skills/en50128-quality/` |
| en50128-configuration | 213 | `.opencode/skills/en50128-configuration/` |
| en50128-lifecycle-coordination | 300 | `.opencode/skills/en50128-lifecycle-coordination/` |
| en50128-documentation | 177 | `.opencode/skills/en50128-documentation/` |
| en50128-project-management | TBD | `.opencode/skills/en50128-project-management/` |

### Tools

| Tool | Purpose | Location |
|------|---------|----------|
| traceability_manager.py | Traceability management | `tools/traceability_manager.py` |
| workflow_manager.py | Document workflow | `tools/workflow_manager.py` |
| workspace.py | Unified CLI | `tools/workspace.py` |
| validate_srs_template.py | SRS validation | `tools/scripts/validate_srs_template.py` |
| validate_sas_sds_template.py | Architecture/Design validation | `tools/scripts/validate_sas_sds_template.py` |
| validate_test_doc_template.py | Test document validation | `tools/scripts/validate_test_doc_template.py` |
| generate_test_report.py | Test report generation | `tools/scripts/generate_test_report.py` |
| parse_coverage_report.py | Coverage analysis | `tools/scripts/parse_coverage_report.py` |
| check-tool-versions.sh | Tool version checking | `tools/tool-validation/check-tool-versions.sh` |
| run-all-validations.sh | T2 tool validation | `tools/tool-validation/run-all-validations.sh` |

---

## Quick Start Checklist

For a **new SIL 3 project**, follow this checklist:

- [ ] **Installation**
  - [ ] Clone repository
  - [ ] Run `./install_tools.sh`
  - [ ] Run `./install_python.sh`
  - [ ] Verify: `tools/tool-validation/check-tool-versions.sh --sil 3`

- [ ] **Phase 1: Planning**
  - [ ] Load `en50128-lifecycle-coordination` skill
  - [ ] Create project structure
  - [ ] Define SIL level (3)

- [ ] **Phase 2: Requirements**
  - [ ] Load `en50128-requirements` skill
  - [ ] Create SRS from template
  - [ ] Initialize traceability matrix
  - [ ] Validate SRS: `validate_srs_template.py`

- [ ] **Phase 2: Safety**
  - [ ] Load `en50128-safety` skill
  - [ ] Create Hazard Log
  - [ ] Perform FMEA
  - [ ] Perform FTA (if applicable)

- [ ] **Phase 3: Design**
  - [ ] Load `en50128-design` skill
  - [ ] Create SAS (architecture)
  - [ ] Create SDS (detailed design)
  - [ ] Validate: `validate_sas_sds_template.py`
  - [ ] Update traceability (requirements → architecture)

- [ ] **Phase 4: Implementation**
  - [ ] Load `en50128-implementation` skill
  - [ ] Write C code (MISRA C compliant)
  - [ ] Write unit tests (Unity framework)
  - [ ] Check MISRA C: `cppcheck --addon=misra`
  - [ ] Check complexity: `lizard --CCN 10`
  - [ ] Update traceability (design → code)

- [ ] **Phase 4: Testing**
  - [ ] Load `en50128-testing` skill
  - [ ] Run unit tests with coverage
  - [ ] Verify 100% coverage: `parse_coverage_report.py --sil 3`
  - [ ] Generate test report: `generate_test_report.py`
  - [ ] Update traceability (requirements → tests)

- [ ] **Phase 4: Verification**
  - [ ] Load `en50128-verification` skill
  - [ ] Run static analysis (Cppcheck, Clang)
  - [ ] Create Verification Report
  - [ ] Independent verification (SIL 3 required)

- [ ] **Phase 4: Quality**
  - [ ] Load `en50128-quality` skill
  - [ ] Perform code review (independent for SIL 3)
  - [ ] Create Code Review Report
  - [ ] Approve: All checks PASS

- [ ] **Traceability**
  - [ ] Validate 100% traceability: `traceability_manager.py validate --sil 3`
  - [ ] Generate traceability report

- [ ] **Baseline**
  - [ ] Commit all documents and code
  - [ ] Tag baseline: `git tag -a baseline-gate4`

- [ ] **Ready for Integration** ✅

---

**END OF USER GUIDE**

**Version**: 2.0  
**Last Updated**: 2026-03-15  
**Platform Status**: Production Ready  
**Questions?** Check LIFECYCLE.md, TOOLS.md, or load relevant skill

**Ready to start? Load your first skill:**
```
skill en50128-requirements
```
