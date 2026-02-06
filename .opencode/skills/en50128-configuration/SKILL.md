---
name: en50128-configuration
description: Software configuration management for EN 50128 railway software
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  phase: all-phases
---

## What I do

I provide configuration management strategies and best practices for railway software compliant with EN 50128 Section 6.6:
- Configuration identification and control
- Version control and baseline management
- Change request processing and tracking
- Configuration status accounting
- Configuration audits (Physical and Functional)
- Traceability management (mandatory SIL 3-4)
- Data recording and analysis (mandatory SIL 3-4)
- Build and release management
- Document control and archiving

## When to use me

Use this skill when:
- Developing Software Configuration Management Plan (SCMP)
- Setting up version control and CM infrastructure
- Identifying and tracking configuration items
- Processing change requests
- Managing software baselines and releases
- Performing configuration audits (PCA, FCA)
- Maintaining traceability matrices (SIL 3-4)
- Recording and analyzing CM metrics (SIL 3-4)
- Coordinating document control
- Preparing for release deployment

## Configuration Management Techniques (EN 50128 Table A.9)

**EN 50128 Section 6.5, Table A.9** defines quality assurance techniques including configuration management:

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 5 | Software Configuration Management | D.48 | **M** | **M** | **M** |
| 7 | Traceability | D.58 | R | HR | **M** |
| 8 | Data Recording and Analysis | D.12 | HR | HR | **M** |

**CRITICAL: Configuration Management is MANDATORY for ALL SIL levels (0, 1, 2, 3, 4)**

**Key Points:**
- **Software Configuration Management (SCM)** is **MANDATORY** for ALL SIL levels
- **Traceability** is **MANDATORY** for SIL 3-4, Highly Recommended for SIL 1-2
- **Data Recording and Analysis** is **MANDATORY** for SIL 3-4
- SCM includes: identification, control, status accounting, audits

**Standard Reference:** `std/EN50128-2011.md` Section 6.6, Table A.9, Reference D.48

## Configuration Management Components

### 1. Configuration Identification (D.48)

**Purpose:** Uniquely identify all configuration items

**Configuration Items (CIs) include:**
- Source code files (`.c`, `.h`)
- Build scripts (`Makefile`, `CMakeLists.txt`)
- Documentation (SRS, SAS, SDS, test plans)
- Test artifacts (test cases, test data, test results)
- Tools and compilers (with version numbers)
- Libraries and dependencies
- Configuration files

**Naming Convention Example:**
```
CI-<TYPE>-<YEAR>-<SEQ>
  
Examples:
CI-SRC-2026-001    (Source code module)
CI-DOC-2026-042    (Document)
CI-TEST-2026-123   (Test artifact)
CI-BUILD-2026-005  (Build configuration)
```

**Version Numbering Scheme:**
```
MAJOR.MINOR.PATCH

MAJOR: Incompatible changes, major functionality
MINOR: Backward-compatible new features
PATCH: Backward-compatible bug fixes

Examples:
1.0.0  (Initial release)
1.1.0  (New feature added)
1.1.1  (Bug fix)
2.0.0  (Breaking change)
```

### 2. Configuration Control (D.48)

**Purpose:** Control all changes to configuration items

**Change Control Process:**

```
┌─────────────────────┐
│  Change Request     │
│  Submitted (CR-XXX) │
└──────┬──────────────┘
       │
       ▼
┌─────────────────────┐
│  Impact Analysis    │
│  (Designer/Safety)  │
└──────┬──────────────┘
       │
       ▼
┌─────────────────────┐
│  Change Approval    │
│  (PM/Safety Mgr)    │
└──────┬──────────────┘
       │
       ▼
┌─────────────────────┐
│  Implementation     │
│  (Implementer)      │
└──────┬──────────────┘
       │
       ▼
┌─────────────────────┐
│  Reverification     │
│  (Verifier/Tester)  │
└──────┬──────────────┘
       │
       ▼
┌─────────────────────┐
│  Baseline Update    │
│  (Config Manager)   │
└─────────────────────┘
```

**Change Request Template:**
```
Change Request: CR-1234
Title: Fix boundary check in sensor_driver.c
Submitted By: Developer Name
Date: 2026-02-06
Priority: High
SIL Level: 3

Affected CIs:
- CI-SRC-2026-042 (sensor_driver.c v3.2.0)
- CI-TEST-2026-123 (unit_test_sensor.c v1.1.0)

Description:
Boundary check in function sensor_read() does not handle 
edge case when sensor value equals MAX_SENSOR_VALUE.

Impact Analysis:
Safety impact: Medium (could cause incorrect sensor reading)
Affected modules: sensor_driver, control_logic
Test impact: Add 3 new test cases
Documentation impact: Update SDS section 4.2

Reverification Required:
- Unit tests (TST)
- Static analysis (VER)
- Safety analysis update (SAF)

Approval: [PM Signature]
Implementation: [IMP Signature]
Verification: [VER Signature]
Closure Date: 2026-02-10
```

### 3. Configuration Status Accounting (D.48)

**Purpose:** Record and report status of all configuration items

**CI Status States:**
- **Draft** - Under development, not reviewed
- **Review** - Submitted for review
- **Approved** - Reviewed and approved, not released
- **Released** - Part of official baseline
- **Obsolete** - Superseded by newer version

**Status Tracking Example:**

| CI ID | Name | Version | Status | Last Modified | SIL | Owner |
|-------|------|---------|--------|---------------|-----|-------|
| CI-SRC-2026-042 | sensor_driver.c | 3.2.1 | Released | 2026-02-06 | 3 | Dev1 |
| CI-SRC-2026-043 | sensor_driver.h | 3.2.0 | Released | 2026-01-15 | 3 | Dev1 |
| CI-DOC-2026-001 | SRS | 2.0 | Released | 2025-12-01 | 3 | REQ |
| CI-TEST-2026-123 | unit_test_sensor.c | 1.1.1 | Review | 2026-02-06 | 3 | TST |

**Configuration Status Report (monthly):**
```
Configuration Status Report
Month: February 2026
Baseline: baseline_SIL3_v1.0.0

Summary:
- Total CIs: 247
- Released: 235 (95%)
- Under Review: 8 (3%)
- Draft: 4 (2%)

Change Requests:
- Submitted: 15
- Approved: 12
- Implemented: 10
- Closed: 9
- Average resolution time: 5.2 days

Baselines:
- Current: baseline_SIL3_v1.0.0 (released 2026-01-15)
- Next planned: baseline_SIL3_v1.1.0 (planned 2026-03-01)

Audit Status:
- Last PCA: 2026-01-20 (PASSED)
- Last FCA: 2026-01-20 (PASSED)
- Next audit: 2026-02-28
```

### 4. Configuration Audits (D.48)

**Physical Configuration Audit (PCA):**
- Verify source code matches documentation
- Verify all CIs present in baseline
- Verify version numbers correct
- Check file checksums/hashes
- Verify build reproducibility

**Functional Configuration Audit (FCA):**
- Verify software meets all requirements
- Verify test results match specifications
- Verify traceability complete (SIL 3-4)
- Verify all defects resolved
- Verify all documentation approved

**PCA Checklist:**
```
Physical Configuration Audit Checklist
Baseline: baseline_SIL3_v1.0.0
Date: 2026-02-20
Auditor: [Name]

[ ] All CIs listed in baseline manifest are present
[ ] All CI version numbers match manifest
[ ] All file checksums match recorded values
[ ] No unauthorized files in baseline
[ ] Build can be reproduced from baseline
[ ] All source files have correct headers with version info
[ ] All tools and compiler versions recorded
[ ] All dependencies identified and versioned
[ ] Baseline directory structure correct
[ ] Archive and retrieval procedures tested

Result: PASS / FAIL
Notes: [Any issues found]
Auditor Signature: ______________
Date: ______________
```

**FCA Checklist:**
```
Functional Configuration Audit Checklist
Baseline: baseline_SIL3_v1.0.0
Date: 2026-02-20
Auditor: [Name]

[ ] All requirements traced to design (100%)
[ ] All design elements traced to code (100%)
[ ] All code traced to tests (100%)
[ ] All tests passed (100%)
[ ] All mandatory coverage achieved (Statement, Branch, Condition)
[ ] All defects resolved or deferred with approval
[ ] All documents approved (SRS, SAS, SDS, test reports)
[ ] All safety requirements verified
[ ] All MISRA C violations resolved or justified
[ ] All static analysis issues resolved

Result: PASS / FAIL
Notes: [Any issues found]
Auditor Signature: ______________
Date: ______________
```

## C Language Configuration Management

### 1. Source File Version Headers

**MANDATORY:** Every C source file SHALL include version information

```c
/**
 * @file    sensor_driver.c
 * @brief   Railway sensor interface driver
 * @version 3.2.1
 * @date    2026-02-06
 * @author  Developer Name
 * 
 * @config  CI-SRC-2026-042
 * @sil     SIL-3
 * @status  Released
 * @baseline baseline_SIL3_v1.0.0
 * 
 * MISRA C:2012 Compliance:
 * - All mandatory rules: COMPLIANT
 * - Required rules: COMPLIANT (see MISRA_Compliance.txt)
 * - Advisory rules: 2 deviations (see Deviation_Log.txt)
 * 
 * Change History:
 * Version  Date        CR      Author  Description
 * -------  ----------  ------  ------  ---------------------------------
 * 3.2.1    2026-02-06  CR-1234 Dev1    Fix boundary check in sensor_read()
 * 3.2.0    2026-01-15  CR-1200 Dev2    Add diagnostic mode
 * 3.1.0    2025-12-01  CR-1150 Dev1    Initial SIL-3 release
 * 3.0.0    2025-11-01  CR-1100 Dev1    Baseline for certification
 */

#include "sensor_driver.h"

// MANDATORY: Runtime version information
const sw_version_t SW_VERSION = {
    .major = 3u,
    .minor = 2u,
    .patch = 1u,
    .config_id = "CI-SRC-2026-042",
    .build_date = __DATE__,
    .build_time = __TIME__,
    .sil_level = 3u
};

// Get version information (for diagnostics)
sw_version_t get_software_version(void)
{
    return SW_VERSION;
}
```

**Header File Version:**
```c
/**
 * @file    sensor_driver.h
 * @brief   Railway sensor interface driver header
 * @version 3.2.0
 * @date    2026-01-15
 * @author  Developer Name
 * 
 * @config  CI-SRC-2026-043
 * @sil     SIL-3
 * @status  Released
 */

#ifndef SENSOR_DRIVER_H
#define SENSOR_DRIVER_H

#include <stdint.h>

// Version information structure
typedef struct {
    uint8_t major;
    uint8_t minor;
    uint8_t patch;
    const char* config_id;
    const char* build_date;
    const char* build_time;
    uint8_t sil_level;
} sw_version_t;

// Function prototypes
sw_version_t get_software_version(void);

#endif /* SENSOR_DRIVER_H */
```

### 2. Build Configuration Management

**Makefile with Version Control:**

```makefile
# Makefile for Sensor Driver Module
# Configuration ID: CI-BUILD-2026-001
# Version: 1.2.0
# Last Modified: 2026-02-06

# ============================================================================
# TOOL VERSIONS (MANDATORY: Record for traceability)
# ============================================================================
CC = gcc
CC_VERSION = 11.3.0
MISRA_CHECKER = pclp
MISRA_VERSION = 2.1.0
STATIC_ANALYZER = cppcheck
ANALYZER_VERSION = 2.9

# ============================================================================
# SOFTWARE VERSION
# ============================================================================
VERSION_MAJOR = 3
VERSION_MINOR = 2
VERSION_PATCH = 1
CONFIG_ID = CI-BUILD-2026-001
BUILD_DATE = $(shell date +%Y-%m-%d)

# ============================================================================
# COMPILER FLAGS (MANDATORY: Ensure reproducible builds)
# ============================================================================
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic
CFLAGS += -DVERSION_MAJOR=$(VERSION_MAJOR)
CFLAGS += -DVERSION_MINOR=$(VERSION_MINOR)
CFLAGS += -DVERSION_PATCH=$(VERSION_PATCH)
CFLAGS += -DCONFIG_ID=\"$(CONFIG_ID)\"
CFLAGS += -DBUILD_DATE=\"$(BUILD_DATE)\"

# SIL 3 specific flags (defensive programming)
CFLAGS += -O2 -fno-strict-aliasing
CFLAGS += -fstack-protector-strong
CFLAGS += -D_FORTIFY_SOURCE=2

# ============================================================================
# SOURCE FILES (Configuration Items)
# ============================================================================
SRCS = sensor_driver.c         # CI-SRC-2026-042 v3.2.1
HDRS = sensor_driver.h         # CI-SRC-2026-043 v3.2.0

OBJS = $(SRCS:.c=.o)

# ============================================================================
# BUILD TARGETS
# ============================================================================
all: sensor_driver.a

sensor_driver.o: sensor_driver.c $(HDRS)
	@echo "Building: $< ($(CONFIG_ID))"
	$(CC) $(CFLAGS) -c $< -o $@

sensor_driver.a: $(OBJS)
	ar rcs $@ $^
	@echo "Created: $@ (Version $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH))"

# ============================================================================
# STATIC ANALYSIS (MANDATORY SIL 3)
# ============================================================================
misra: $(SRCS)
	$(MISRA_CHECKER) $(SRCS) > misra_report.txt

static-analysis: $(SRCS)
	$(STATIC_ANALYZER) --enable=all $(SRCS) > static_analysis_report.txt

# ============================================================================
# CONFIGURATION MANAGEMENT
# ============================================================================
version-info:
	@echo "Configuration ID: $(CONFIG_ID)"
	@echo "Version: $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)"
	@echo "Build Date: $(BUILD_DATE)"
	@echo "Compiler: $(CC) $(CC_VERSION)"
	@echo "MISRA Checker: $(MISRA_CHECKER) $(MISRA_VERSION)"

clean:
	rm -f $(OBJS) sensor_driver.a

.PHONY: all misra static-analysis version-info clean
```

### 3. Baseline Management

**Baseline Directory Structure:**

```
baseline_SIL3_v1.0.0/
├── configuration/
│   ├── baseline_manifest.txt           # List of all CIs with checksums
│   ├── traceability_matrix.csv         # Requirements to code traceability
│   ├── SCMP_v1.0.pdf                   # Software Configuration Management Plan
│   ├── tool_versions.txt               # All tool versions used
│   └── build_instructions.md           # How to reproduce build
│
├── source/
│   ├── sensor_driver.c                 # CI-SRC-2026-042 v3.2.1
│   ├── sensor_driver.h                 # CI-SRC-2026-043 v3.2.0
│   ├── control_logic.c                 # CI-SRC-2026-044 v2.1.0
│   ├── control_logic.h                 # CI-SRC-2026-045 v2.1.0
│   └── Makefile                        # CI-BUILD-2026-001 v1.2.0
│
├── documentation/
│   ├── SRS_v2.0.pdf                    # CI-DOC-2026-001 (Requirements)
│   ├── SAS_v2.0.pdf                    # CI-DOC-2026-002 (Architecture)
│   ├── SDS_v2.0.pdf                    # CI-DOC-2026-003 (Design)
│   ├── SVVP_v1.0.pdf                   # CI-DOC-2026-004 (Test Plan)
│   ├── MISRA_Compliance_v1.0.pdf       # CI-DOC-2026-010
│   └── Safety_Analysis_v1.0.pdf        # CI-DOC-2026-011
│
├── tests/
│   ├── unit_tests/
│   │   ├── test_sensor_driver.c        # CI-TEST-2026-123 v1.1.1
│   │   └── test_control_logic.c        # CI-TEST-2026-124 v1.0.0
│   ├── integration_tests/
│   │   └── test_integration.c          # CI-TEST-2026-201 v1.0.0
│   └── test_results/
│       ├── unit_test_report.txt        # CI-TEST-2026-301
│       ├── integration_test_report.txt # CI-TEST-2026-302
│       └── coverage_report.html        # CI-TEST-2026-303
│
├── tools/
│   ├── gcc-11.3.0/                     # Compiler (or reference)
│   ├── pclp-2.1.0/                     # MISRA checker (or reference)
│   └── tool_checksums.txt              # Verify tool integrity
│
└── build_artifacts/
    ├── sensor_driver.a                 # Built library
    ├── build_log.txt                   # Build output
    └── checksums.txt                   # Artifact checksums
```

**Baseline Manifest Example:**

```
Baseline Manifest: baseline_SIL3_v1.0.0
Created: 2026-02-06
Baseline Status: RELEASED
SIL Level: 3
Configuration Manager: [Name]
Approved By: [PM Name]

=============================================================================
SOURCE FILES
=============================================================================
CI-SRC-2026-042  sensor_driver.c      3.2.1  SHA256:a3f2b8c9...  Released
CI-SRC-2026-043  sensor_driver.h      3.2.0  SHA256:b4e7d1f0...  Released
CI-SRC-2026-044  control_logic.c      2.1.0  SHA256:c5a8e2f1...  Released
CI-SRC-2026-045  control_logic.h      2.1.0  SHA256:d6b9f3g2...  Released
CI-BUILD-2026-001 Makefile            1.2.0  SHA256:e7c0g4h3...  Released

=============================================================================
DOCUMENTATION
=============================================================================
CI-DOC-2026-001  SRS_v2.0.pdf         2.0    SHA256:f8d1h5i4...  Released
CI-DOC-2026-002  SAS_v2.0.pdf         2.0    SHA256:g9e2i6j5...  Released
CI-DOC-2026-003  SDS_v2.0.pdf         2.0    SHA256:h0f3j7k6...  Released
CI-DOC-2026-004  SVVP_v1.0.pdf        1.0    SHA256:i1g4k8l7...  Released

=============================================================================
TEST ARTIFACTS
=============================================================================
CI-TEST-2026-123 test_sensor_driver.c 1.1.1  SHA256:j2h5l9m8...  Released
CI-TEST-2026-301 unit_test_report.txt 1.0    SHA256:k3i6m0n9...  Released

=============================================================================
TOOLS (with versions recorded)
=============================================================================
gcc              11.3.0
pclp (MISRA)     2.1.0
cppcheck         2.9
Unity (test fw)  2.5.2
gcov/lcov        11.3.0

=============================================================================
TRACEABILITY STATUS (MANDATORY SIL 3-4)
=============================================================================
Requirements to Design:    100% traced (150/150)
Design to Code:            100% traced (245/245)
Code to Tests:             100% traced (245/245)
Bi-directional verified:   PASS

=============================================================================
VERIFICATION STATUS
=============================================================================
Unit Test Coverage:        100% (Statement, Branch, Condition)
Integration Test Coverage: 98% (Statement, Branch)
MISRA C Compliance:        PASS (0 violations, 2 justified deviations)
Static Analysis:           PASS (0 critical, 0 major issues)
Code Review:               PASS (all modules reviewed)

=============================================================================
AUDITS
=============================================================================
Physical Configuration Audit (PCA):   PASSED (2026-02-05)
Functional Configuration Audit (FCA): PASSED (2026-02-05)

=============================================================================
APPROVAL
=============================================================================
Configuration Manager:  [Signature] [Date]
Verifier:              [Signature] [Date]
Validator:             [Signature] [Date]
Project Manager:       [Signature] [Date]
Safety Manager:        [Signature] [Date]
```

## Traceability Management (MANDATORY SIL 3-4)

**EN 50128 Reference D.58:** Traceability is MANDATORY for SIL 3-4

**Traceability Matrix Format (CSV):**

```csv
Requirement ID,Requirement Text,Design ID,Design Element,Source File,Function/Variable,Test ID,Test Case
REQ-001,"Sensor shall read temperature range -40 to +85C",DES-005,Sensor Interface,sensor_driver.c,sensor_read_temp(),TEST-123,test_sensor_range_valid
REQ-001,"Sensor shall read temperature range -40 to +85C",DES-005,Sensor Interface,sensor_driver.c,sensor_read_temp(),TEST-124,test_sensor_range_min
REQ-001,"Sensor shall read temperature range -40 to +85C",DES-005,Sensor Interface,sensor_driver.c,sensor_read_temp(),TEST-125,test_sensor_range_max
REQ-002,"Sensor shall detect out-of-range values",DES-005,Sensor Interface,sensor_driver.c,sensor_validate(),TEST-126,test_sensor_out_of_range_low
REQ-002,"Sensor shall detect out-of-range values",DES-005,Sensor Interface,sensor_driver.c,sensor_validate(),TEST-127,test_sensor_out_of_range_high
REQ-003,"System shall enter safe state on sensor failure",DES-010,Safety Logic,control_logic.c,handle_sensor_failure(),TEST-201,test_safe_state_sensor_fail
```

**Traceability Verification:**

```c
// Example: Code with traceability tags
/**
 * @brief Read temperature from sensor
 * @trace REQ-001 Sensor shall read temperature range -40 to +85C
 * @trace DES-005 Sensor Interface Design
 * @return Temperature value in 0.1 degree Celsius
 */
int16_t sensor_read_temp(void)
{
    int16_t raw_value;
    int16_t temperature;
    
    // Read raw sensor value
    raw_value = read_sensor_register(TEMP_REGISTER);
    
    // Convert to temperature (0.1 degree resolution)
    temperature = (int16_t)((raw_value * 1250) / 1000);
    
    // Validate range: -40C to +85C (-400 to +850 in 0.1 degree units)
    // @trace REQ-001 Range validation
    if ((temperature < -400) || (temperature > 850)) {
        return SENSOR_ERROR_OUT_OF_RANGE;
    }
    
    return temperature;
}
```

## Data Recording and Analysis (MANDATORY SIL 3-4)

**EN 50128 Reference D.12:** Data Recording and Analysis is MANDATORY for SIL 3-4

**Metrics to Record:**

1. **Change Request Metrics:**
   - Number of CRs submitted per month
   - CR resolution time (average, min, max)
   - CR by type (enhancement, defect, documentation)
   - CR by priority (critical, high, medium, low)
   - CR by affected component

2. **Defect Metrics:**
   - Defects found by phase (requirements, design, implementation, testing)
   - Defects by severity
   - Defects by component
   - Defect resolution time

3. **Configuration Audit Metrics:**
   - Audit pass/fail rate
   - Issues found per audit
   - Issue resolution time

4. **Baseline Metrics:**
   - Number of baselines released
   - Time between baselines
   - Number of CIs per baseline
   - Baseline completeness

**Metrics Report Example:**

```
Configuration Management Metrics Report
Period: Q1 2026 (January - March)
Project: Railway Control System SIL-3
Configuration Manager: [Name]

=============================================================================
CHANGE REQUEST METRICS
=============================================================================
Total CRs Submitted:     47
  - Enhancements:        18 (38%)
  - Defects:             22 (47%)
  - Documentation:        7 (15%)

Total CRs Closed:        45 (96%)
Average Resolution Time: 6.3 days
  - Critical:            1.5 days (3 CRs)
  - High:                4.2 days (15 CRs)
  - Medium:              7.8 days (20 CRs)
  - Low:                 12.1 days (7 CRs)

Trend: Resolution time decreased by 15% compared to Q4 2025

=============================================================================
DEFECT METRICS
=============================================================================
Total Defects Found:     22
By Phase:
  - Requirements:         2 (9%)
  - Design:              3 (14%)
  - Implementation:      12 (55%)
  - Testing:             5 (23%)

By Severity:
  - Critical:            1 (5%)   - Resolved in 1 day
  - Major:               6 (27%)  - Resolved in 3.5 days avg
  - Minor:               15 (68%) - Resolved in 8.2 days avg

Trend: Defects found in implementation phase decreased by 20% (better code reviews)

=============================================================================
CONFIGURATION AUDIT METRICS
=============================================================================
Audits Conducted:        3 (monthly)
  - PCA Pass Rate:       100%
  - FCA Pass Rate:       100%

Average Issues per Audit: 2.3 (minor)
  - Missing documentation:   4 issues (all resolved)
  - Version mismatch:        2 issues (all resolved)
  - Traceability gaps:       1 issue (resolved)

Trend: Issues decreased by 40% compared to Q4 2025 (process improvement)

=============================================================================
BASELINE METRICS
=============================================================================
Baselines Released:      2
  - baseline_SIL3_v1.0.0 (2026-01-15)
  - baseline_SIL3_v1.1.0 (2026-03-01)

Average CIs per Baseline: 247
Baseline Completeness:    100% (all required CIs present)

=============================================================================
TRACEABILITY METRICS (SIL 3 MANDATORY)
=============================================================================
Requirements Traced:     100% (150/150)
Design Elements Traced:  100% (245/245)
Code Functions Traced:   100% (387/387)
Test Cases Traced:       100% (512/512)

Bi-directional Verification: PASS

=============================================================================
RECOMMENDATIONS
=============================================================================
1. Continue emphasis on code reviews (reduced implementation defects)
2. Increase frequency of PCA to bi-weekly for next baseline cycle
3. Automate traceability verification (reduce manual effort)
4. Document lessons learned from Q1 2026 for process improvement

Configuration Manager: [Signature]
Date: 2026-04-01
```

## Software Configuration Management Plan (SCMP)

**EN 50128 Annex C, Document #3:**
- **Written by:** Configuration Manager
- **First Check:** Verifier (VER)
- **Second Check:** Validator (VAL)
- **Status:** Highly Recommended for all SIL levels

**SCMP Template (Required Sections):**

```
Software Configuration Management Plan (SCMP)

Project: [Railway Control System]
Version: 1.0
Date: 2026-01-01
Configuration Manager: [Name]
Approved By: [PM Name]

=============================================================================
1. INTRODUCTION
=============================================================================
1.1 Purpose
1.2 Scope
1.3 Applicable Standards (EN 50128:2011 Section 6.6)
1.4 Definitions and Abbreviations

=============================================================================
2. CONFIGURATION MANAGEMENT ORGANIZATION
=============================================================================
2.1 Roles and Responsibilities
    - Configuration Manager
    - Change Control Board (CCB)
    - Project Manager
    - Development Team
2.2 CM Tools and Environment
    - Version control: Git
    - CM database: [Tool name]
    - Build automation: Jenkins
    - Issue tracking: [Tool name]

=============================================================================
3. CONFIGURATION IDENTIFICATION
=============================================================================
3.1 Configuration Items (CIs)
    - Source code
    - Documentation
    - Test artifacts
    - Tools and compilers
    - Build scripts
3.2 Naming Conventions
    - CI-<TYPE>-<YEAR>-<SEQ>
3.3 Version Numbering Scheme
    - MAJOR.MINOR.PATCH
3.4 Baseline Identification
    - baseline_SIL<N>_vX.Y.Z
3.5 Document Control Procedures

=============================================================================
4. CONFIGURATION CONTROL
=============================================================================
4.1 Change Request Process
    - CR submission
    - CR evaluation and impact analysis
    - CR approval workflow (CCB)
    - CR implementation tracking
    - Reverification requirements
4.2 Change Control Board (CCB)
    - Membership: PM, Safety Mgr, CM, Tech Lead
    - Meeting frequency: Weekly
    - Approval authority by SIL level
4.3 Branch Management Strategy
    - main (production releases)
    - develop (integration)
    - feature branches
    - release branches
    - hotfix branches

=============================================================================
5. CONFIGURATION STATUS ACCOUNTING
=============================================================================
5.1 CI Status Tracking
    - Status states: Draft, Review, Approved, Released, Obsolete
5.2 Configuration Database
    - Tools: [Name]
    - Retention period: Life of project + 10 years
5.3 Status Reporting
    - Monthly configuration status reports
    - Quarterly metrics reports (MANDATORY SIL 3-4)
5.4 Change History Tracking
    - All changes recorded in CM database
    - Audit trail maintained

=============================================================================
6. CONFIGURATION AUDITS AND REVIEWS
=============================================================================
6.1 Physical Configuration Audit (PCA)
    - Frequency: Before each baseline release
    - Checklist: Appendix A
6.2 Functional Configuration Audit (FCA)
    - Frequency: Before each baseline release
    - Checklist: Appendix B
6.3 Periodic Reviews
    - CM process review: Quarterly
    - Tool audits: Annually
6.4 Audit Reporting
    - Audit reports to PM and Quality Manager

=============================================================================
7. INTERFACE CONTROL
=============================================================================
7.1 Interface Identification
    - Software interfaces
    - Hardware interfaces
    - External system interfaces
7.2 Interface Change Control
    - Interface change approval process
7.3 Third-Party Component Management
    - Vendor version control
    - License management

=============================================================================
8. BUILD AND RELEASE MANAGEMENT
=============================================================================
8.1 Build Procedures
    - Automated build process
    - Build verification tests
    - Reproducible builds
8.2 Release Criteria
    - All tests passed
    - All audits passed (PCA, FCA)
    - All documentation approved
    - Traceability verified (SIL 3-4)
8.3 Deployment Configuration
    - Target environment configuration
    - Installation procedures
8.4 Rollback Procedures
    - Emergency rollback to previous baseline

=============================================================================
9. TRACEABILITY (MANDATORY SIL 3-4)
=============================================================================
9.1 Traceability Requirements
    - Requirements to design
    - Design to code
    - Code to tests
    - Bi-directional traceability
9.2 Traceability Matrix Maintenance
    - Tool: Excel/CSV
    - Update frequency: Each CR closure
    - Verification: Before baseline release

=============================================================================
10. DATA RECORDING AND ANALYSIS (MANDATORY SIL 3-4)
=============================================================================
10.1 Metrics Collection
     - CR metrics
     - Defect metrics
     - Audit metrics
     - Baseline metrics
10.2 Analysis and Reporting
     - Monthly metrics reports
     - Quarterly trend analysis
     - Annual process improvement recommendations

=============================================================================
11. TRAINING
=============================================================================
11.1 CM Tool Training
11.2 Process Training
11.3 Role-Specific Training

=============================================================================
APPENDICES
=============================================================================
Appendix A: Physical Configuration Audit (PCA) Checklist
Appendix B: Functional Configuration Audit (FCA) Checklist
Appendix C: Change Request Template
Appendix D: Baseline Manifest Template
Appendix E: Configuration Status Report Template
```

## CM Workflow Example

**Complete Configuration Management Workflow:**

```bash
# ============================================================================
# PHASE 1: SETUP (Project Start)
# ============================================================================

# 1.1 Develop SCMP
# - Write Software Configuration Management Plan
# - Define CM organization (roles, CCB)
# - Define CI identification scheme (CI-<TYPE>-<YEAR>-<SEQ>)
# - Define version numbering (MAJOR.MINOR.PATCH)
# - Plan configuration audits
# - Get SCMP approved by VER and VAL

# 1.2 Setup CM Infrastructure
# - Configure Git repository (main, develop, feature branches)
# - Setup CM database for tracking CIs
# - Configure build automation (Jenkins/CI-CD)
# - Establish naming conventions
# - Setup issue tracking system

# 1.3 Training
# - Train team on CM procedures
# - Train team on tools (Git, CM database)
# - Train team on change request process

# ============================================================================
# PHASE 2: CONFIGURATION IDENTIFICATION
# ============================================================================

# 2.1 Identify Configuration Items
# Source code: sensor_driver.c → CI-SRC-2026-042
# Documents: SRS → CI-DOC-2026-001
# Tests: test_sensor_driver.c → CI-TEST-2026-123
# Build: Makefile → CI-BUILD-2026-001
# Tools: gcc 11.3.0, pclp 2.1.0 (record versions)

# 2.2 Record CIs in CM Database
# Add all CIs with metadata:
#   - CI ID
#   - Name
#   - Version
#   - Status (Draft/Review/Approved/Released)
#   - Owner
#   - SIL level
#   - Last modified date

# 2.3 Establish Traceability (MANDATORY SIL 3-4)
# Create traceability matrix:
#   REQ-001 → DES-005 → sensor_driver.c:sensor_read_temp() → TEST-123

# ============================================================================
# PHASE 3: CONFIGURATION CONTROL (Ongoing)
# ============================================================================

# 3.1 Receive Change Request
# CR-1234: "Fix boundary check in sensor_driver.c"
# Record in CM database

# 3.2 Impact Analysis
# Coordinate with Designer and Safety Engineer
# Affected CIs: CI-SRC-2026-042, CI-TEST-2026-123
# Safety impact: Medium
# Test impact: Add 3 new test cases

# 3.3 Change Control Board (CCB) Approval
# Present CR-1234 to CCB
# CCB evaluates safety impact, schedule impact, cost
# CCB approves or rejects CR

# 3.4 Implementation
# Implementer implements change
# Version: sensor_driver.c v3.2.0 → v3.2.1

# 3.5 Reverification
# Tester executes tests (unit, integration)
# Verifier runs static analysis
# Safety Engineer reviews safety impact

# 3.6 Update Baseline
# Update affected CIs in baseline
# Update traceability matrix
# Update version numbers
# Close CR-1234

# ============================================================================
# PHASE 4: CONFIGURATION STATUS ACCOUNTING (Ongoing)
# ============================================================================

# 4.1 Track CI Status
# Update CM database with CI status changes
# sensor_driver.c: Released v3.2.1

# 4.2 Generate Status Reports
# Monthly: Configuration Status Report
#   - Total CIs: 247
#   - Released: 235
#   - Under Review: 8
#   - Draft: 4
#   - CRs submitted: 15
#   - CRs closed: 9

# 4.3 Record Metrics (MANDATORY SIL 3-4)
# CR metrics: Count, resolution time, type
# Defect metrics: By phase, by severity
# Audit metrics: Pass rate, issues found
# Baseline metrics: Number released, completeness

# 4.4 Analyze Trends
# Quarterly trend analysis
# Identify process improvements
# Report to management

# ============================================================================
# PHASE 5: BASELINE RELEASE
# ============================================================================

# 5.1 Prepare Baseline
# Create baseline directory: baseline_SIL3_v1.0.0/
# Collect all CIs (source, docs, tests, tools)
# Generate baseline manifest with checksums
# Verify traceability 100% complete (SIL 3-4)

# 5.2 Physical Configuration Audit (PCA)
# Verify all CIs present
# Verify version numbers correct
# Verify checksums match
# Verify build reproducibility
# Result: PASS

# 5.3 Functional Configuration Audit (FCA)
# Verify all requirements met
# Verify all tests passed
# Verify 100% coverage achieved
# Verify all documents approved
# Result: PASS

# 5.4 Baseline Approval
# Configuration Manager approves
# Verifier approves
# Validator approves
# Project Manager approves
# Safety Manager approves

# 5.5 Release Baseline
# Package baseline for deployment
# Generate release notes
# Archive baseline (retain life of project + 10 years)
# Notify stakeholders

# ============================================================================
# PHASE 6: MAINTENANCE (Post-Release)
# ============================================================================

# 6.1 Field Change Requests
# Receive CR from field (defect report)
# Process through CCB
# Implement, reverify, update baseline
# Release maintenance update (hotfix)

# 6.2 Periodic Audits
# Monthly PCA/FCA for ongoing development
# Quarterly CM process review
# Annual tool audits

# 6.3 Continuous Improvement
# Review metrics quarterly
# Identify process improvements
# Update SCMP as needed (with approval)
```

## CM Checklist

**Configuration Management Quality Checklist:**

Before approving any baseline release, verify:

### Planning and Setup
- [ ] SCMP developed and approved (by VER and VAL)
- [ ] CM infrastructure established (version control, CM database, build automation)
- [ ] CM tools selected and configured
- [ ] Team trained on CM procedures and tools

### Configuration Identification
- [ ] All CIs identified with unique IDs (CI-<TYPE>-<YEAR>-<SEQ>)
- [ ] Version numbering scheme applied consistently (MAJOR.MINOR.PATCH)
- [ ] All source files have version headers
- [ ] All documents version-controlled
- [ ] All tools and compilers versions recorded

### Traceability (MANDATORY SIL 3-4)
- [ ] Traceability matrix complete (requirements to design to code to tests)
- [ ] Bi-directional traceability verified
- [ ] 100% traceability coverage achieved
- [ ] Traceability verified by independent Verifier

### Configuration Control
- [ ] Change control process documented
- [ ] Change Control Board (CCB) established
- [ ] All change requests processed through CCB
- [ ] Impact analysis performed for all changes
- [ ] Reverification performed after all changes
- [ ] Change history recorded for all CIs

### Configuration Status Accounting
- [ ] CM database populated with all CIs
- [ ] CI status tracked (Draft, Review, Approved, Released)
- [ ] Configuration status reports generated (monthly)
- [ ] Change request metrics recorded (SIL 3-4 MANDATORY)
- [ ] Audit trail maintained for all changes

### Data Recording and Analysis (MANDATORY SIL 3-4)
- [ ] CM metrics recorded (CR, defect, audit, baseline)
- [ ] Metrics analyzed for trends
- [ ] Quarterly metrics reports generated
- [ ] Process improvements identified and documented

### Configuration Audits
- [ ] Physical Configuration Audit (PCA) performed and PASSED
- [ ] Functional Configuration Audit (FCA) performed and PASSED
- [ ] All audit issues resolved
- [ ] Audit reports documented and archived

### Baseline Management
- [ ] Baseline directory structure established
- [ ] Baseline manifest generated with checksums
- [ ] All CIs present in baseline
- [ ] Build reproducibility verified
- [ ] Baseline approved by all required roles (CM, VER, VAL, PM, Safety Mgr)

### Build and Release
- [ ] Build procedures documented
- [ ] Build automation configured
- [ ] Release criteria met (tests passed, audits passed, docs approved)
- [ ] Deployment configuration documented
- [ ] Rollback procedures documented and tested

### Documentation
- [ ] SCMP current and approved
- [ ] Baseline manifest complete
- [ ] Traceability matrix complete (SIL 3-4)
- [ ] Configuration status reports up to date
- [ ] Audit reports archived
- [ ] Change records complete

### Archive and Retention
- [ ] Baseline archived in controlled storage
- [ ] Archive retention period: Life of project + 10 years (minimum)
- [ ] Retrieval procedures tested
- [ ] Archive integrity verified (checksums)

## Standard References

- **EN 50128:2011 Section 6.6** - Modification and Change Control - `std/EN50128-2011.md`
- **EN 50128:2011 Section 5.3.2.7** - Document Traceability - `std/EN50128-2011.md` line 1332
- **EN 50128:2011 Table A.9** - Software Quality Assurance (CM techniques) - `std/EN50128-TABLES-EXTRACTED.md` lines 64-88
- **EN 50128:2011 Table B.10** - Configuration Manager Role - `std/EN50128-2011.md` Annex B
- **EN 50128:2011 Reference D.48** - Software Configuration Management techniques - `std/EN50128-2011.md`
- **EN 50128:2011 Reference D.58** - Traceability (MANDATORY SIL 3-4) - `std/EN50128-2011.md`
- **EN 50128:2011 Reference D.12** - Data Recording and Analysis (MANDATORY SIL 3-4) - `std/EN50128-2011.md`
- **EN 50128:2011 Annex C** - SCMP Document Requirements - `std/EN50128-2011.md`

## Interaction with Other Agents

**Receives input from:**
- **All agents** - Change requests, document updates
- `/req` - Requirements changes, requirements traceability
- `/des` - Design changes, architecture updates
- `/imp` - Code changes, defect fixes
- `/tst` - Test defect reports, test artifact updates
- `/int` - Integration issues, interface changes

**Provides services to:**
- **All agents** - Version control, document control, change tracking
- `/ver` - Traceability verification, audit support, baseline verification
- `/val` - Baseline approval support, release documentation
- `/qua` - CM metrics, audit results, process compliance data
- `/pm` - Status reports, change metrics, baseline status

**Coordinates with:**
- `/pm` - Change Control Board (CCB), baseline approvals, resource allocation
- `/qua` - CM audits, process compliance, quality metrics
- `/saf` - Safety-critical change evaluation, safety impact analysis

## Abbreviations

- **CM** = Configuration Manager
- **CI** = Configuration Item
- **SCMP** = Software Configuration Management Plan
- **CCB** = Change Control Board
- **PCA** = Physical Configuration Audit
- **FCA** = Functional Configuration Audit
- **CR** = Change Request
- **SIL** = Safety Integrity Level
- **M** = Mandatory
- **HR** = Highly Recommended
- **R** = Recommended

**Reference:** `std/EN50128-ABBREVIATIONS.md`
