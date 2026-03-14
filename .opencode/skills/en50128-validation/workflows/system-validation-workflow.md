# System Validation Workflow

**EN 50128 Reference**: Section 7.7 (Overall Software Testing / Final Validation), Table A.7  
**Phase**: Phase 7 - Validation  
**Role**: Validator (VAL)  
**SIL Level**: All (0-4)

---

## Purpose

This workflow defines the complete process for validating integrated software against stakeholder requirements and operational needs in the target environment. It implements EN 50128 Section 7.7.4.1 requirement for demonstrating that software is "fit for its intended application" through system-level testing and validation.

**Key Objectives**:
- Validate software meets stakeholder needs (not just requirements)
- System-level testing in target or representative environment
- Independent validation (MANDATORY SIL 3-4)
- Operational scenario validation
- Performance validation (MANDATORY SIL 3-4)
- Evidence collection for certification and release

**Inputs**:
- Software Requirements Specification (SRS) from REQ, Phase 2
- System Requirements Specification
- Overall Software Test Specification
- Software Validation Plan (SVP)
- Integration Test Report from INT, Phase 6
- All verification evidence from VER
- Hazard Log from SAF

**Outputs**:
- Software Validation Report (Section 7.7.4.6-7.7.4.11)
- Overall Software Test Report (Section 7.7.4.1-7.7.4.4)
- Release Note (Section 7.7.4.12)
- Validation test results (pass/fail evidence)
- Acceptance certificate (customer sign-off)

---

## Table of Contents

1. [Validation Planning](#validation-planning)
2. [Validation Environment Setup](#validation-environment-setup)
3. [System-Level Test Execution](#system-level-test-execution)
4. [Performance Validation](#performance-validation)
5. [Safety Validation](#safety-validation)
6. [Operational Scenario Validation](#operational-scenario-validation)
7. [Requirements Coverage Validation](#requirements-coverage-validation)
8. [Validation Report Generation](#validation-report-generation)
9. [Tool Integration](#tool-integration)
10. [SIL-Specific Requirements](#sil-specific-requirements)
11. [Example Validation Scenarios](#example-validation-scenarios)

---

## Validation Planning

### Software Validation Plan (SVP) Development

**EN 50128 Section 7.7.4.6**: "A Software Validation Report shall be written, under the responsibility of the Validator, on the basis of the Software Validation Plan."

**SVP Required Elements**:

```markdown
# Software Validation Plan (SVP)

## Document Control
- **Document ID**: DOC-VAL-SVP-001
- **Version**: 1.0
- **Date**: 2026-03-14
- **Author**: [Validator Name]
- **SIL Level**: [0-4]
- **Project**: [Railway Safety System Name]

## 1. Introduction

### 1.1 Purpose
This Software Validation Plan defines the approach, resources, and schedule for validating [Software Component] for [Railway Application] at SIL [level].

**Validation Objective**: Demonstrate that the software meets stakeholder needs and is fit for its intended application in the operational railway environment.

### 1.2 Scope
- **Software Component**: [Name and Version]
- **SIL Level**: [0-4]
- **Target Platform**: [Hardware/OS/Processor]
- **Operational Environment**: [Railway installation, depot, mainline]
- **Validation Approach**: [Independent validation, target environment testing]

### 1.3 References
- Software Requirements Specification (SRS) - DOC-REQ-SRS-001
- System Requirements Specification - SYS-REQ-001
- EN 50128:2011 Section 7.7
- Software Verification Plan (SVP) - DOC-VER-SVP-001
- Hazard Log - DOC-SAF-HL-001
- Software Integration Report - DOC-INT-REP-001

## 2. Validation Strategy

### 2.1 Validation Approach (EN 50128 Table A.7)

**Selected Techniques by SIL**:

| SIL 0-1 | SIL 2 | SIL 3-4 |
|---------|-------|---------|
| Functional Testing (HR) | Functional Testing (HR) | **Functional Testing (M)** |
| - | Performance Testing (HR) | **Performance Testing (M)** |
| - | Modelling (R) | Modelling (R) |

**Rationale**:
- **Functional Testing**: MANDATORY for SIL 3-4, covers all system requirements
- **Performance Testing**: MANDATORY for SIL 3-4, validates real-time constraints
- **Modelling**: Used for complex state behavior analysis (optional for all SILs)

### 2.2 Independence Requirements

**SIL 3-4 (EN 50128 Section 5.1.2.10.f)**:
- ✅ Validator **MUST** be independent from development team
- ✅ Validator **SHALL NOT** report to Project Manager
- ✅ Validator reports to Safety Manager or Customer
- ✅ Validator has authority to approve/reject software release

**SIL 2**:
- Independent validation **Highly Recommended**
- Same person may perform verification and validation with justification

**SIL 0-1**:
- Independent validation recommended but not required

### 2.3 Validation Team

| Role | Name | Independence | Responsibility |
|------|------|--------------|----------------|
| **Validator** (Lead) | [Name] | ✅ Independent (SIL 3-4) | Overall validation, report approval |
| **Tester** | [Name] | Reports to Validator | Test execution, results recording |
| **Domain Expert** | [Name] | Customer/Operator | Operational scenario validation |
| **Safety Engineer** | [Name] | Independent | Safety validation review |

**Independence Verification**:
- Validator: No involvement in REQ, DES, IMP, INT, VER roles
- Organizational separation: Different reporting line from development
- Financial independence: No project schedule/cost pressure

## 3. Validation Environment

### 3.1 Target Platform Configuration

**Hardware**:
- Processor: [ARM Cortex-M4 / x86 / PowerPC]
- Memory: [RAM size, ROM size]
- I/O Interfaces: [CAN, Ethernet, Serial, GPIO]
- Safety Features: [Watchdog, ECC memory, redundant processors]

**Software**:
- Operating System: [Bare-metal / FreeRTOS / Linux]
- Compiler: [gcc version, optimization level]
- Libraries: [Standard library, safety library versions]

**Configuration**:
- Deployment configuration (same as operational)
- Safety parameters enabled
- Diagnostic monitoring active
- Logging and tracing configured

### 3.2 Test Environment Types

**1. Laboratory Environment** (Initial validation):
- Benchtop hardware target
- Simulated sensors/actuators
- Controlled test conditions
- Full diagnostic access

**2. Hardware-in-the-Loop (HIL)** (System integration):
- Real hardware interfaces
- Simulated railway environment
- Fault injection capability
- Real-time operation

**3. Pilot Installation** (Final validation):
- Actual railway installation
- Real operational conditions
- Limited geographic scope
- Customer supervision

### 3.3 Test Equipment and Tools

| Equipment | Purpose | Calibration Date | Notes |
|-----------|---------|------------------|-------|
| Target hardware | Execution platform | N/A | Production-equivalent |
| HIL simulator | Environment simulation | 2026-01-15 | Certified tool |
| CAN analyzer | Interface monitoring | 2026-02-10 | Calibrated |
| Oscilloscope | Timing analysis | 2026-01-20 | Calibrated |
| Power supply | Voltage variation testing | 2026-02-01 | Calibrated |

## 4. Validation Test Scope

### 4.1 Functional Validation (MANDATORY SIL 3-4)

**Test Coverage**:
- All system requirements from SRS (100% traceability)
- All operational modes (normal, degraded, safe, maintenance)
- All user interfaces (HMI, operator controls)
- All communication interfaces (CAN, Ethernet, serial)
- All fault detection and handling mechanisms

**Test Approach**: Black-box functional testing (EN 50128 Table A.14)

### 4.2 Performance Validation (MANDATORY SIL 3-4)

**Real-Time Requirements**:
- Task execution times (worst-case execution time - WCET)
- Task jitter and deadline adherence
- Interrupt response times
- Communication latency (CAN, Ethernet)
- Memory usage (RAM, stack, heap)
- CPU utilization

**Test Approach**: Performance testing (EN 50128 Table A.18)

### 4.3 Safety Validation

**Hazard Mitigation Validation**:
- Validate all hazard mitigations from Hazard Log
- Fault injection testing (hardware faults, software faults)
- Safe state transitions (emergency brake, fail-safe outputs)
- Redundancy and voting mechanisms
- Watchdog and self-test functions

**Test Approach**: Fault injection, boundary testing, stress testing

### 4.4 Operational Scenarios

**Stakeholder-Defined Scenarios**:
- Normal train operation (departure, running, arrival)
- Emergency scenarios (obstacle detection, emergency brake)
- Degraded operation (sensor failure, partial system failure)
- Maintenance and diagnostic scenarios
- Environmental stress scenarios (temperature, vibration, EMI)

**Test Approach**: Scenario-based testing with customer involvement

### 4.5 Regression Validation

**Changes Since Last Validation**:
- All modified requirements
- All modified design elements
- All modified source code
- All defect fixes

**Test Approach**: Re-execute affected tests, full regression suite

## 5. Acceptance Criteria

### 5.1 Test Pass Criteria

**Functional Tests**:
- 100% of system requirements validated successfully
- Zero critical defects (safety-impacting)
- Zero high-priority defects blocking deployment
- All medium/low defects documented in Release Note

**Performance Tests** (SIL 3-4):
- All timing requirements met with margin (≥10% margin)
- CPU utilization ≤80% under peak load
- Memory utilization ≤75% of available
- No deadline misses or watchdog timeouts

**Safety Tests**:
- All hazard mitigations validated successfully
- Safe state reached within required time for all faults
- No undetected failures in safety-critical functions

### 5.2 Validation Approval Criteria

- [ ] All validation tests executed successfully
- [ ] Requirements traceability 100% complete
- [ ] All verification evidence reviewed and accepted
- [ ] Independent validation performed (SIL 3-4)
- [ ] Safety validation report approved by Safety Manager
- [ ] Customer acceptance obtained (user acceptance tests)
- [ ] Release Note approved with documented restrictions

## 6. Validation Schedule

| Activity | Start Date | End Date | Duration | Responsible |
|----------|-----------|----------|----------|-------------|
| SVP Development | 2026-03-01 | 2026-03-10 | 10 days | Validator |
| Test Environment Setup | 2026-03-11 | 2026-03-20 | 10 days | Tester |
| Laboratory Validation | 2026-03-21 | 2026-04-10 | 21 days | Validator |
| HIL Validation | 2026-04-11 | 2026-04-30 | 20 days | Validator |
| Pilot Installation | 2026-05-01 | 2026-05-31 | 31 days | Validator |
| Validation Report | 2026-06-01 | 2026-06-10 | 10 days | Validator |
| **Total Duration** | | | **102 days** | |

**Milestones**:
- M1: SVP Approved - 2026-03-10
- M2: Laboratory Validation Complete - 2026-04-10
- M3: HIL Validation Complete - 2026-04-30
- M4: Pilot Installation Complete - 2026-05-31
- M5: Validation Report Approved - 2026-06-10

## 7. Resources

### 7.1 Personnel
- Validator (Lead): 1.0 FTE, 102 days
- Tester: 1.0 FTE, 82 days
- Domain Expert: 0.5 FTE, 31 days (pilot phase)
- Safety Engineer: 0.25 FTE, 10 days (review)

### 7.2 Equipment
- Target hardware: 2 units (1 primary, 1 spare)
- HIL simulator: 1 system
- Test equipment: CAN analyzer, oscilloscope, power supply
- Pilot installation site: Access to railway depot

### 7.3 Budget
- Personnel: [Budget allocation]
- Equipment: [Budget allocation]
- Travel (pilot site): [Budget allocation]

## 8. Validation Deliverables

| Deliverable | Description | Due Date | Approver |
|-------------|-------------|----------|----------|
| **Software Validation Plan (SVP)** | This document | 2026-03-10 | Safety Manager |
| **Overall Software Test Report** | Test execution results | 2026-06-05 | Validator |
| **Software Validation Report** | Validation assessment | 2026-06-10 | Validator |
| **Release Note** | Restrictions and limitations | 2026-06-10 | Validator |
| **Acceptance Certificate** | Customer approval | 2026-06-15 | Customer |

## 9. Risks and Mitigation

| Risk | Impact | Probability | Mitigation |
|------|--------|-------------|------------|
| Pilot site unavailable | High | Low | Backup site identified |
| Test equipment failure | Medium | Medium | Spare equipment available |
| Critical defect found late | High | Low | Early HIL testing, thorough verification |
| Customer availability | Medium | Medium | Schedule confirmed in advance |

## 10. Change Control

All changes to this SVP shall be managed through the project Change Control Board (CCB). Changes affecting validation scope, schedule, or criteria require Safety Manager approval.

## 11. Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Validator** (Author) | [Name] | ___________ | _____ |
| **Safety Manager** | [Name] | ___________ | _____ |
| **Quality Manager** | [Name] | ___________ | _____ |
| **Project Manager** | [Name] | ___________ | _____ |

**Note**: Validator approval authority is independent of Project Manager (SIL 3-4).
```

---

### Traceability: Link SVP to SRS

```bash
# Create traceability from Validation Plan to Requirements
workspace.py trace create \
    --from validation \
    --to requirements \
    --source-id "DOC-VAL-SVP-001" \
    --target-id "DOC-REQ-SRS-001" \
    --rationale "Validation plan covers all system requirements from SRS" \
    --sil 3

# Validate traceability completeness
workspace.py trace validate \
    --phase validation \
    --sil 3 \
    --output evidence/traceability/validation_to_requirements.json
```

---

## Validation Environment Setup

### Target Hardware Configuration

**EN 50128 Section 7.7.4.5**: "The software shall be exercised either by connection to real items of hardware or actual systems with which it would interface in operation, or by simulation of input signals and loads driven by outputs."

#### Laboratory Setup (Phase 1)

```c
// Validation test harness for railway door control system
// File: validation_harness.c

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "door_control_system.h"  // System under validation

// Hardware abstraction for validation testing
typedef struct {
    // Inputs (sensors)
    uint16_t speed_sensor_kmh;
    bool door_closed_sensor_left;
    bool door_closed_sensor_right;
    bool operator_door_open_button;
    bool operator_door_close_button;
    uint8_t door_obstruction_sensor;  // 0 = clear, 1 = obstruction
    
    // System state
    uint32_t timestamp_ms;
} validation_inputs_t;

typedef struct {
    // Outputs (actuators)
    bool door_motor_left_open;
    bool door_motor_left_close;
    bool door_motor_right_open;
    bool door_motor_right_close;
    bool door_lock_left;
    bool door_lock_right;
    
    // Status indicators
    uint8_t alarm_status;
    bool safety_brake_active;
} validation_outputs_t;

// Validation test case structure
typedef struct {
    const char* test_id;
    const char* test_name;
    const char* requirement_id;  // Traceability to SRS
    
    validation_inputs_t inputs;
    validation_outputs_t expected_outputs;
    validation_outputs_t actual_outputs;
    
    uint32_t max_response_time_ms;  // Real-time requirement
    uint32_t actual_response_time_ms;
    
    bool passed;
    char notes[256];
} validation_test_case_t;

// Global validation context
typedef struct {
    uint32_t tests_executed;
    uint32_t tests_passed;
    uint32_t tests_failed;
    
    FILE* log_file;
    bool abort_on_failure;  // For critical tests
} validation_context_t;

static validation_context_t g_val_ctx = {0};

// Initialize validation environment
result_t validation_init(const char* log_filename) {
    printf("=== EN 50128 System Validation ===\n");
    printf("Initializing validation environment...\n");
    
    // Open log file
    g_val_ctx.log_file = fopen(log_filename, "w");
    if (g_val_ctx.log_file == NULL) {
        printf("ERROR: Cannot open log file %s\n", log_filename);
        return RESULT_ERROR_FILE_IO;
    }
    
    fprintf(g_val_ctx.log_file, "EN 50128 System Validation Log\n");
    fprintf(g_val_ctx.log_file, "Date: %s\n", get_timestamp_string());
    fprintf(g_val_ctx.log_file, "SIL Level: 3\n");
    fprintf(g_val_ctx.log_file, "System: Railway Door Control\n");
    fprintf(g_val_ctx.log_file, "Version: 1.0.0\n\n");
    
    // Initialize system under test
    result_t result = door_control_system_init();
    if (result != RESULT_SUCCESS) {
        printf("ERROR: System initialization failed\n");
        return result;
    }
    
    g_val_ctx.tests_executed = 0;
    g_val_ctx.tests_passed = 0;
    g_val_ctx.tests_failed = 0;
    g_val_ctx.abort_on_failure = false;
    
    printf("Validation environment initialized successfully\n\n");
    return RESULT_SUCCESS;
}

// Execute single validation test case
bool validation_execute_test(validation_test_case_t* test) {
    if (test == NULL) {
        return false;
    }
    
    printf("Executing: %s [%s]\n", test->test_id, test->test_name);
    printf("  Requirement: %s\n", test->requirement_id);
    
    fprintf(g_val_ctx.log_file, "TEST: %s - %s\n", test->test_id, test->test_name);
    fprintf(g_val_ctx.log_file, "  Requirement: %s\n", test->requirement_id);
    
    // Apply inputs to system
    apply_validation_inputs(&test->inputs);
    
    // Execute system cycle and measure response time
    uint32_t start_time = get_time_ms();
    door_control_system_execute();
    uint32_t end_time = get_time_ms();
    
    test->actual_response_time_ms = end_time - start_time;
    
    // Read actual outputs
    read_validation_outputs(&test->actual_outputs);
    
    // Compare expected vs actual
    bool outputs_match = compare_outputs(&test->expected_outputs, &test->actual_outputs);
    bool timing_met = (test->actual_response_time_ms <= test->max_response_time_ms);
    
    test->passed = outputs_match && timing_met;
    
    // Log results
    if (test->passed) {
        printf("  RESULT: PASS\n");
        printf("  Response Time: %u ms (limit: %u ms)\n", 
               test->actual_response_time_ms, test->max_response_time_ms);
        fprintf(g_val_ctx.log_file, "  RESULT: PASS\n");
        g_val_ctx.tests_passed++;
    } else {
        printf("  RESULT: FAIL\n");
        if (!outputs_match) {
            printf("  ERROR: Output mismatch\n");
            fprintf(g_val_ctx.log_file, "  RESULT: FAIL (Output mismatch)\n");
            log_output_differences(&test->expected_outputs, &test->actual_outputs, 
                                    g_val_ctx.log_file);
        }
        if (!timing_met) {
            printf("  ERROR: Timing violation (%u ms > %u ms)\n",
                   test->actual_response_time_ms, test->max_response_time_ms);
            fprintf(g_val_ctx.log_file, "  RESULT: FAIL (Timing violation)\n");
        }
        g_val_ctx.tests_failed++;
    }
    
    fprintf(g_val_ctx.log_file, "  Notes: %s\n\n", test->notes);
    printf("\n");
    
    g_val_ctx.tests_executed++;
    
    // Abort if critical test failed
    if (!test->passed && g_val_ctx.abort_on_failure) {
        printf("CRITICAL TEST FAILED - Aborting validation\n");
        return false;
    }
    
    return test->passed;
}

// Finalize validation and generate summary
void validation_finalize(void) {
    printf("=== Validation Summary ===\n");
    printf("Tests Executed: %u\n", g_val_ctx.tests_executed);
    printf("Tests Passed:   %u\n", g_val_ctx.tests_passed);
    printf("Tests Failed:   %u\n", g_val_ctx.tests_failed);
    
    if (g_val_ctx.tests_executed > 0) {
        float pass_rate = 100.0f * g_val_ctx.tests_passed / g_val_ctx.tests_executed;
        printf("Pass Rate:      %.1f%%\n", pass_rate);
    }
    
    fprintf(g_val_ctx.log_file, "\n=== Validation Summary ===\n");
    fprintf(g_val_ctx.log_file, "Tests Executed: %u\n", g_val_ctx.tests_executed);
    fprintf(g_val_ctx.log_file, "Tests Passed:   %u\n", g_val_ctx.tests_passed);
    fprintf(g_val_ctx.log_file, "Tests Failed:   %u\n", g_val_ctx.tests_failed);
    
    if (g_val_ctx.log_file != NULL) {
        fclose(g_val_ctx.log_file);
    }
    
    printf("\nValidation log saved\n");
}
```

---

#### HIL (Hardware-in-the-Loop) Setup

```c
// HIL simulation interface for realistic environment testing
// File: hil_interface.c

#include "hil_interface.h"
#include <stdint.h>
#include <stdbool.h>

// HIL simulator provides realistic railway environment
typedef struct {
    // Train dynamics
    float train_speed_kmh;
    float train_acceleration_m_s2;
    float train_position_m;
    
    // Door mechanics (simulated by HIL)
    float door_position_left_mm;   // 0 = closed, 800 = fully open
    float door_position_right_mm;
    float door_opening_velocity_mm_s;
    
    // Environmental conditions
    float ambient_temperature_c;
    float door_load_kg;  // Passenger pressure on door
    bool obstruction_present;
    
    // Fault injection (HIL capability)
    bool inject_sensor_fault;
    bool inject_actuator_fault;
    bool inject_power_glitch;
} hil_simulator_state_t;

static hil_simulator_state_t g_hil_state;

// Initialize HIL simulator
result_t hil_init(const char* config_file) {
    printf("Initializing HIL simulator...\n");
    
    // Load HIL configuration
    if (!load_hil_config(config_file)) {
        return RESULT_ERROR_CONFIG;
    }
    
    // Connect to HIL hardware
    if (!hil_connect()) {
        return RESULT_ERROR_CONNECTION;
    }
    
    // Initialize train state
    g_hil_state.train_speed_kmh = 0.0f;
    g_hil_state.train_acceleration_m_s2 = 0.0f;
    g_hil_state.door_position_left_mm = 0.0f;  // Closed
    g_hil_state.door_position_right_mm = 0.0f;
    g_hil_state.ambient_temperature_c = 20.0f;
    g_hil_state.inject_sensor_fault = false;
    
    printf("HIL simulator initialized\n");
    return RESULT_SUCCESS;
}

// Update HIL simulation (called every cycle)
void hil_update(uint32_t delta_time_ms) {
    float delta_time_s = delta_time_ms / 1000.0f;
    
    // Update train dynamics
    g_hil_state.train_speed_kmh += g_hil_state.train_acceleration_m_s2 * delta_time_s * 3.6f;
    if (g_hil_state.train_speed_kmh < 0.0f) {
        g_hil_state.train_speed_kmh = 0.0f;
    }
    
    g_hil_state.train_position_m += (g_hil_state.train_speed_kmh / 3.6f) * delta_time_s;
    
    // Update door mechanics (realistic door motion simulation)
    if (g_hil_state.door_opening_velocity_mm_s > 0.0f) {
        // Door opening
        g_hil_state.door_position_left_mm += g_hil_state.door_opening_velocity_mm_s * delta_time_s;
        g_hil_state.door_position_right_mm += g_hil_state.door_opening_velocity_mm_s * delta_time_s;
        
        // Limit to fully open position
        if (g_hil_state.door_position_left_mm > 800.0f) {
            g_hil_state.door_position_left_mm = 800.0f;
        }
        if (g_hil_state.door_position_right_mm > 800.0f) {
            g_hil_state.door_position_right_mm = 800.0f;
        }
    } else if (g_hil_state.door_opening_velocity_mm_s < 0.0f) {
        // Door closing
        g_hil_state.door_position_left_mm += g_hil_state.door_opening_velocity_mm_s * delta_time_s;
        g_hil_state.door_position_right_mm += g_hil_state.door_opening_velocity_mm_s * delta_time_s;
        
        // Limit to closed position
        if (g_hil_state.door_position_left_mm < 0.0f) {
            g_hil_state.door_position_left_mm = 0.0f;
        }
        if (g_hil_state.door_position_right_mm < 0.0f) {
            g_hil_state.door_position_right_mm = 0.0f;
        }
        
        // Detect obstruction during closing
        if (g_hil_state.obstruction_present && 
            g_hil_state.door_position_left_mm < 100.0f) {
            // Obstruction detected - stop door motion
            g_hil_state.door_opening_velocity_mm_s = 0.0f;
        }
    }
    
    // Send updated state to HIL hardware
    hil_write_simulator_state(&g_hil_state);
}

// Apply door motor commands from system under test
void hil_apply_door_commands(bool motor_left_open, bool motor_left_close,
                               bool motor_right_open, bool motor_right_close) {
    // Simulate door motor velocity based on commands
    if (motor_left_open && !motor_left_close) {
        g_hil_state.door_opening_velocity_mm_s = 200.0f;  // 200 mm/s opening
    } else if (motor_left_close && !motor_left_open) {
        g_hil_state.door_opening_velocity_mm_s = -150.0f;  // 150 mm/s closing
    } else {
        g_hil_state.door_opening_velocity_mm_s = 0.0f;  // Stopped
    }
}

// Read simulated sensor values
uint16_t hil_get_speed_sensor(void) {
    if (g_hil_state.inject_sensor_fault) {
        return 0xFFFF;  // Invalid sensor reading
    }
    return (uint16_t)g_hil_state.train_speed_kmh;
}

bool hil_get_door_closed_sensor_left(void) {
    return (g_hil_state.door_position_left_mm < 5.0f);  // Closed threshold
}

bool hil_get_obstruction_sensor(void) {
    return g_hil_state.obstruction_present;
}

// Fault injection for validation testing
void hil_inject_fault(hil_fault_type_t fault_type) {
    switch (fault_type) {
        case HIL_FAULT_SPEED_SENSOR:
            g_hil_state.inject_sensor_fault = true;
            printf("HIL: Injected speed sensor fault\n");
            break;
        
        case HIL_FAULT_DOOR_OBSTRUCTION:
            g_hil_state.obstruction_present = true;
            printf("HIL: Injected door obstruction\n");
            break;
        
        case HIL_FAULT_POWER_GLITCH:
            g_hil_state.inject_power_glitch = true;
            printf("HIL: Injected power glitch\n");
            break;
        
        default:
            break;
    }
}

void hil_clear_fault(hil_fault_type_t fault_type) {
    switch (fault_type) {
        case HIL_FAULT_SPEED_SENSOR:
            g_hil_state.inject_sensor_fault = false;
            break;
        
        case HIL_FAULT_DOOR_OBSTRUCTION:
            g_hil_state.obstruction_present = false;
            break;
        
        case HIL_FAULT_POWER_GLITCH:
            g_hil_state.inject_power_glitch = false;
            break;
        
        default:
            break;
    }
}
```

---

## System-Level Test Execution

### Functional Validation Test Suite

**EN 50128 Table A.7**: Functional and Black-box Testing (MANDATORY SIL 3-4)

```c
// Functional validation test suite
// File: functional_validation_tests.c

#include "validation_harness.h"
#include <stdio.h>

// Test VAL-FUNC-001: Door remains locked while train is moving
void test_val_func_001_door_lock_while_moving(void) {
    validation_test_case_t test = {
        .test_id = "VAL-FUNC-001",
        .test_name = "Door Lock While Moving",
        .requirement_id = "SRS-SAFE-010",  // Traceability to safety requirement
        .inputs = {
            .speed_sensor_kmh = 50,  // Train moving at 50 km/h
            .door_closed_sensor_left = true,
            .door_closed_sensor_right = true,
            .operator_door_open_button = true,  // Operator attempts to open
        },
        .expected_outputs = {
            .door_motor_left_open = false,  // Door must NOT open
            .door_motor_right_open = false,
            .door_lock_left = true,   // Locks must remain engaged
            .door_lock_right = true,
            .alarm_status = ALARM_DOOR_INTERLOCK_VIOLATION,
        },
        .max_response_time_ms = 100,  // Must respond within 100ms (SIL 3)
        .abort_on_failure = true,  // CRITICAL SAFETY TEST
    };
    
    strcpy(test.notes, "Safety-critical: Prevents passenger ejection");
    validation_execute_test(&test);
}

// Test VAL-FUNC-002: Door opens when train is stopped
void test_val_func_002_door_open_when_stopped(void) {
    validation_test_case_t test = {
        .test_id = "VAL-FUNC-002",
        .test_name = "Door Open When Stopped",
        .requirement_id = "SRS-FUNC-020",
        .inputs = {
            .speed_sensor_kmh = 0,  // Train stopped
            .door_closed_sensor_left = true,
            .door_closed_sensor_right = true,
            .operator_door_open_button = true,
        },
        .expected_outputs = {
            .door_motor_left_open = true,  // Door should open
            .door_motor_right_open = true,
            .door_lock_left = false,  // Locks released
            .door_lock_right = false,
            .alarm_status = 0,  // No alarms
        },
        .max_response_time_ms = 500,  // Comfort response time
        .abort_on_failure = false,
    };
    
    strcpy(test.notes, "Normal operation: Allow passenger egress");
    validation_execute_test(&test);
}

// Test VAL-FUNC-003: Door closes automatically after timeout
void test_val_func_003_door_auto_close(void) {
    validation_test_case_t test = {
        .test_id = "VAL-FUNC-003",
        .test_name = "Door Auto-Close Timeout",
        .requirement_id = "SRS-FUNC-025",
        .inputs = {
            .speed_sensor_kmh = 0,
            .door_closed_sensor_left = false,  // Door open
            .door_closed_sensor_right = false,
            .operator_door_open_button = false,
            .operator_door_close_button = false,
            .timestamp_ms = 30000,  // 30 seconds elapsed
        },
        .expected_outputs = {
            .door_motor_left_close = true,  // Auto-close triggered
            .door_motor_right_close = true,
            .alarm_status = ALARM_AUTO_CLOSE_INITIATED,
        },
        .max_response_time_ms = 100,
        .abort_on_failure = false,
    };
    
    strcpy(test.notes, "Operational requirement: Prevent departure delays");
    validation_execute_test(&test);
}

// Test VAL-FUNC-004: Door obstruction detection
void test_val_func_004_obstruction_detection(void) {
    validation_test_case_t test = {
        .test_id = "VAL-FUNC-004",
        .test_name = "Door Obstruction Detection",
        .requirement_id = "SRS-SAFE-015",
        .inputs = {
            .speed_sensor_kmh = 0,
            .door_closed_sensor_left = false,  // Door partially open
            .door_obstruction_sensor = 1,  // Obstruction present
            .operator_door_close_button = true,
        },
        .expected_outputs = {
            .door_motor_left_close = false,  // Stop closing
            .door_motor_left_open = true,    // Reverse to open
            .alarm_status = ALARM_DOOR_OBSTRUCTION,
        },
        .max_response_time_ms = 200,  // Must respond quickly (safety)
        .abort_on_failure = true,  // CRITICAL SAFETY TEST
    };
    
    strcpy(test.notes, "Safety-critical: Prevent passenger injury");
    validation_execute_test(&test);
}

// Test VAL-FUNC-005: Emergency brake triggers door lock
void test_val_func_005_emergency_brake_locks_doors(void) {
    validation_test_case_t test = {
        .test_id = "VAL-FUNC-005",
        .test_name = "Emergency Brake Locks Doors",
        .requirement_id = "SRS-SAFE-020",
        .inputs = {
            .speed_sensor_kmh = 80,  // High speed
            .door_closed_sensor_left = true,
            .door_closed_sensor_right = true,
            // Emergency brake signal from train system (injected via HIL)
        },
        .expected_outputs = {
            .door_lock_left = true,   // Locks engaged
            .door_lock_right = true,
            .safety_brake_active = true,
            .alarm_status = ALARM_EMERGENCY_BRAKE,
        },
        .max_response_time_ms = 50,  // Very fast response required
        .abort_on_failure = true,  // CRITICAL SAFETY TEST
    };
    
    strcpy(test.notes, "Safety-critical: Maintain door integrity during emergency braking");
    validation_execute_test(&test);
}

// Execute full functional validation suite
void run_functional_validation_suite(void) {
    printf("=== Functional Validation Test Suite ===\n");
    printf("EN 50128 Table A.7: Functional and Black-box Testing (MANDATORY SIL 3-4)\n\n");
    
    // Initialize validation environment
    validation_init("validation_functional.log");
    
    // Execute all functional tests
    test_val_func_001_door_lock_while_moving();
    test_val_func_002_door_open_when_stopped();
    test_val_func_003_door_auto_close();
    test_val_func_004_obstruction_detection();
    test_val_func_005_emergency_brake_locks_doors();
    
    // Add more functional tests...
    // (Total: 45 functional tests covering all SRS requirements)
    
    // Finalize and generate summary
    validation_finalize();
}
```

---

### Traceability: Validation Tests to Requirements

```bash
# Create traceability from validation tests to SRS requirements
workspace.py trace create \
    --from validation \
    --to requirements \
    --source-id "VAL-FUNC-001" \
    --target-id "SRS-SAFE-010" \
    --rationale "Validates door interlock safety requirement" \
    --sil 3

workspace.py trace create \
    --from validation \
    --to requirements \
    --source-id "VAL-FUNC-004" \
    --target-id "SRS-SAFE-015" \
    --rationale "Validates obstruction detection requirement" \
    --sil 3

# Generate requirements coverage report
workspace.py trace report \
    --from validation \
    --to requirements \
    --format markdown \
    --output evidence/traceability/validation_requirements_coverage.md

# Validate 100% requirements coverage
workspace.py trace validate \
    --phase validation \
    --sil 3 \
    --coverage 100 \
    --output evidence/traceability/validation_coverage_report.json
```

---

## Performance Validation

### Real-Time Performance Testing (MANDATORY SIL 3-4)

**EN 50128 Table A.7**: Performance Testing (MANDATORY SIL 3-4)  
**EN 50128 Table A.18**: Performance Testing Techniques

```c
// Performance validation test suite
// File: performance_validation_tests.c

#include "validation_harness.h"
#include <stdio.h>
#include <time.h>

// Performance measurement structure
typedef struct {
    const char* task_name;
    const char* requirement_id;
    
    uint32_t max_execution_time_us;  // WCET requirement
    uint32_t max_jitter_us;          // Jitter requirement
    uint32_t measurement_count;
    
    // Measurements
    uint32_t execution_times_us[1000];
    uint32_t min_time_us;
    uint32_t max_time_us;
    uint32_t avg_time_us;
    uint32_t jitter_us;
    
    bool passed;
} performance_test_t;

// High-resolution timer functions (platform-specific)
static inline uint32_t get_time_us(void) {
    // ARM Cortex-M: Use DWT cycle counter
    uint32_t cycles = DWT->CYCCNT;
    return cycles / (SystemCoreClock / 1000000);
}

// Test PERF-001: Safety monitor task timing
void test_perf_001_safety_monitor_timing(void) {
    performance_test_t test = {
        .task_name = "Safety Monitor Task",
        .requirement_id = "SRS-PERF-010",
        .max_execution_time_us = 1000,  // 1 ms WCET
        .max_jitter_us = 100,            // 100 us max jitter
        .measurement_count = 1000,
    };
    
    printf("Executing: PERF-001 - %s\n", test.task_name);
    printf("  Requirement: %s\n", test.requirement_id);
    printf("  WCET Limit: %u us\n", test.max_execution_time_us);
    printf("  Jitter Limit: %u us\n\n", test.max_jitter_us);
    
    // Measure execution time over many iterations
    for (uint32_t i = 0; i < test.measurement_count; i++) {
        uint32_t start = get_time_us();
        
        // Execute safety monitor task
        safety_monitor_task_execute();
        
        uint32_t end = get_time_us();
        test.execution_times_us[i] = end - start;
        
        // Delay to simulate periodic execution (10 ms period)
        delay_us(10000 - (end - start));
    }
    
    // Analyze measurements
    test.min_time_us = UINT32_MAX;
    test.max_time_us = 0;
    uint64_t total_time_us = 0;
    
    for (uint32_t i = 0; i < test.measurement_count; i++) {
        uint32_t time = test.execution_times_us[i];
        if (time < test.min_time_us) test.min_time_us = time;
        if (time > test.max_time_us) test.max_time_us = time;
        total_time_us += time;
    }
    
    test.avg_time_us = (uint32_t)(total_time_us / test.measurement_count);
    test.jitter_us = test.max_time_us - test.min_time_us;
    
    // Evaluate pass/fail
    bool wcet_met = (test.max_time_us <= test.max_execution_time_us);
    bool jitter_met = (test.jitter_us <= test.max_jitter_us);
    test.passed = wcet_met && jitter_met;
    
    // Print results
    printf("  Results:\n");
    printf("    Min:    %u us\n", test.min_time_us);
    printf("    Avg:    %u us\n", test.avg_time_us);
    printf("    Max:    %u us (limit: %u us) %s\n", 
           test.max_time_us, test.max_execution_time_us,
           wcet_met ? "[PASS]" : "[FAIL]");
    printf("    Jitter: %u us (limit: %u us) %s\n",
           test.jitter_us, test.max_jitter_us,
           jitter_met ? "[PASS]" : "[FAIL]");
    printf("  Overall: %s\n\n", test.passed ? "PASS" : "FAIL");
}

// Test PERF-002: Door control task timing
void test_perf_002_door_control_timing(void) {
    performance_test_t test = {
        .task_name = "Door Control Task",
        .requirement_id = "SRS-PERF-020",
        .max_execution_time_us = 10000,  // 10 ms WCET
        .max_jitter_us = 1000,           // 1 ms max jitter
        .measurement_count = 1000,
    };
    
    // Similar implementation to test_perf_001...
    // (Omitted for brevity)
}

// Test PERF-003: CPU utilization under peak load
void test_perf_003_cpu_utilization(void) {
    printf("Executing: PERF-003 - CPU Utilization Under Peak Load\n");
    printf("  Requirement: SRS-PERF-030\n");
    printf("  CPU Limit: 80%% (SIL 3 requirement)\n\n");
    
    // Enable CPU utilization measurement
    cpu_utilization_monitor_start();
    
    // Run system under peak load for 60 seconds
    printf("  Running peak load scenario (60 seconds)...\n");
    uint32_t start_time = get_time_ms();
    while ((get_time_ms() - start_time) < 60000) {
        // Execute all periodic tasks
        safety_monitor_task_execute();
        door_control_task_execute();
        communication_task_execute();
        diagnostic_task_execute();
        
        // Simulate peak load: all doors operating, high communication rate
        simulate_peak_load();
    }
    
    // Get CPU utilization statistics
    cpu_utilization_stats_t stats = cpu_utilization_monitor_get_stats();
    
    printf("  Results:\n");
    printf("    Average CPU: %.1f%%\n", stats.average_utilization_percent);
    printf("    Peak CPU:    %.1f%% (limit: 80.0%%) %s\n",
           stats.peak_utilization_percent,
           (stats.peak_utilization_percent <= 80.0f) ? "[PASS]" : "[FAIL]");
    printf("    Idle Time:   %.1f%%\n", 100.0f - stats.average_utilization_percent);
    printf("  Overall: %s\n\n",
           (stats.peak_utilization_percent <= 80.0f) ? "PASS" : "FAIL");
}

// Test PERF-004: Memory utilization
void test_perf_004_memory_utilization(void) {
    printf("Executing: PERF-004 - Memory Utilization\n");
    printf("  Requirement: SRS-PERF-040\n\n");
    
    // Get memory statistics
    memory_stats_t mem_stats = get_memory_stats();
    
    // Calculate utilization percentages
    float ram_utilization = 100.0f * mem_stats.ram_used_bytes / mem_stats.ram_total_bytes;
    float stack_utilization = 100.0f * mem_stats.stack_used_bytes / mem_stats.stack_total_bytes;
    
    printf("  RAM Usage:\n");
    printf("    Used:  %u bytes\n", mem_stats.ram_used_bytes);
    printf("    Total: %u bytes\n", mem_stats.ram_total_bytes);
    printf("    Utilization: %.1f%% (limit: 75.0%%) %s\n",
           ram_utilization,
           (ram_utilization <= 75.0f) ? "[PASS]" : "[FAIL]");
    
    printf("  Stack Usage:\n");
    printf("    Used:  %u bytes\n", mem_stats.stack_used_bytes);
    printf("    Total: %u bytes\n", mem_stats.stack_total_bytes);
    printf("    Utilization: %.1f%% (limit: 75.0%%) %s\n",
           stack_utilization,
           (stack_utilization <= 75.0f) ? "[PASS]" : "[FAIL]");
    
    bool passed = (ram_utilization <= 75.0f) && (stack_utilization <= 75.0f);
    printf("  Overall: %s\n\n", passed ? "PASS" : "FAIL");
}

// Test PERF-005: Interrupt response time
void test_perf_005_interrupt_response_time(void) {
    printf("Executing: PERF-005 - Interrupt Response Time\n");
    printf("  Requirement: SRS-PERF-050\n");
    printf("  Response Time Limit: 50 us (SIL 3)\n\n");
    
    // Measure interrupt latency (time from interrupt signal to ISR execution)
    uint32_t measurements[100];
    uint32_t max_latency_us = 0;
    
    for (uint32_t i = 0; i < 100; i++) {
        // Trigger test interrupt and measure latency
        uint32_t latency_us = measure_interrupt_latency(TEST_INTERRUPT_ID);
        measurements[i] = latency_us;
        
        if (latency_us > max_latency_us) {
            max_latency_us = latency_us;
        }
    }
    
    printf("  Results:\n");
    printf("    Max Latency: %u us (limit: 50 us) %s\n",
           max_latency_us,
           (max_latency_us <= 50) ? "[PASS]" : "[FAIL]");
    printf("  Overall: %s\n\n",
           (max_latency_us <= 50) ? "PASS" : "FAIL");
}

// Execute full performance validation suite
void run_performance_validation_suite(void) {
    printf("=== Performance Validation Test Suite ===\n");
    printf("EN 50128 Table A.7: Performance Testing (MANDATORY SIL 3-4)\n");
    printf("EN 50128 Table A.18: Performance Testing Techniques\n\n");
    
    test_perf_001_safety_monitor_timing();
    test_perf_002_door_control_timing();
    test_perf_003_cpu_utilization();
    test_perf_004_memory_utilization();
    test_perf_005_interrupt_response_time();
    
    // Additional performance tests...
    // (Total: 12 performance tests)
}
```

---

## Safety Validation

### Hazard-Based Validation (SIL 3-4)

**Approach**: For each identified hazard in Hazard Log, validate mitigation effectiveness

```c
// Safety validation test suite
// File: safety_validation_tests.c

#include "validation_harness.h"
#include "hil_interface.h"
#include <stdio.h>

// Safety test structure
typedef struct {
    const char* test_id;
    const char* test_name;
    const char* hazard_id;  // Traceability to Hazard Log
    const char* requirement_id;  // Safety requirement
    
    bool passed;
    char failure_description[256];
} safety_test_t;

// Test SAFE-001: Validate mitigation for "Unintended Door Opening"
void test_safe_001_unintended_door_opening(void) {
    safety_test_t test = {
        .test_id = "SAFE-001",
        .test_name = "Unintended Door Opening Prevention",
        .hazard_id = "HAZ-001",
        .requirement_id = "SRS-SAFE-010",
    };
    
    printf("Executing: %s - %s\n", test.test_id, test.test_name);
    printf("  Hazard: %s\n", test.hazard_id);
    printf("  Requirement: %s\n\n", test.requirement_id);
    
    // Scenario: Train moving at 100 km/h
    // Inject fault: Spurious door open command
    
    hil_set_train_speed(100.0f);  // High speed
    wait_ms(1000);  // Allow system to stabilize
    
    // Inject fault: Hardware fault causes door open signal
    printf("  Injecting fault: Spurious door open command...\n");
    hil_inject_fault(HIL_FAULT_SPURIOUS_DOOR_OPEN);
    wait_ms(2000);  // Allow system to react
    
    // Verify doors remain closed and locked
    bool door_left_closed = hil_get_door_closed_sensor_left();
    bool door_right_closed = hil_get_door_closed_sensor_right();
    bool door_left_locked = system_get_door_lock_status_left();
    bool door_right_locked = system_get_door_lock_status_right();
    uint8_t alarm = system_get_alarm_status();
    
    test.passed = door_left_closed && door_right_closed &&
                   door_left_locked && door_right_locked &&
                   (alarm & ALARM_DOOR_INTERLOCK_VIOLATION);
    
    if (test.passed) {
        printf("  Result: PASS\n");
        printf("    - Doors remained closed: YES\n");
        printf("    - Doors remained locked: YES\n");
        printf("    - Alarm raised: YES\n");
    } else {
        printf("  Result: FAIL\n");
        snprintf(test.failure_description, sizeof(test.failure_description),
                 "Door opened while moving (left=%d, right=%d)",
                 !door_left_closed, !door_right_closed);
        printf("    %s\n", test.failure_description);
    }
    
    // Clear fault
    hil_clear_fault(HIL_FAULT_SPURIOUS_DOOR_OPEN);
    printf("\n");
}

// Test SAFE-002: Validate mitigation for "Door Closes on Passenger"
void test_safe_002_door_obstruction_response(void) {
    safety_test_t test = {
        .test_id = "SAFE-002",
        .test_name = "Door Obstruction Response",
        .hazard_id = "HAZ-002",
        .requirement_id = "SRS-SAFE-015",
    };
    
    printf("Executing: %s - %s\n", test.test_id, test.test_name);
    printf("  Hazard: %s\n", test.hazard_id);
    printf("  Requirement: %s\n\n", test.requirement_id);
    
    // Scenario: Door closing, passenger caught in door
    hil_set_train_speed(0.0f);  // Train stopped
    wait_ms(500);
    
    // Start door closing
    printf("  Starting door close sequence...\n");
    system_command_door_close();
    wait_ms(1000);  // Door partially closed
    
    // Inject obstruction (passenger in doorway)
    printf("  Injecting obstruction (passenger in doorway)...\n");
    hil_inject_fault(HIL_FAULT_DOOR_OBSTRUCTION);
    
    // Measure response time
    uint32_t start_time = get_time_ms();
    uint32_t response_time_ms = 0;
    bool door_reversed = false;
    
    // Wait for system response (max 500 ms)
    while ((get_time_ms() - start_time) < 500) {
        // Check if door motor reversed to open
        if (system_get_door_motor_command_left() == DOOR_MOTOR_OPEN) {
            response_time_ms = get_time_ms() - start_time;
            door_reversed = true;
            break;
        }
        wait_ms(10);
    }
    
    // Verify door reversed to open
    uint8_t alarm = system_get_alarm_status();
    
    test.passed = door_reversed && 
                   (response_time_ms <= 200) &&  // Fast response required
                   (alarm & ALARM_DOOR_OBSTRUCTION);
    
    if (test.passed) {
        printf("  Result: PASS\n");
        printf("    - Door reversed to open: YES\n");
        printf("    - Response time: %u ms (limit: 200 ms)\n", response_time_ms);
        printf("    - Alarm raised: YES\n");
    } else {
        printf("  Result: FAIL\n");
        if (!door_reversed) {
            strcpy(test.failure_description, "Door did not reverse on obstruction");
        } else if (response_time_ms > 200) {
            snprintf(test.failure_description, sizeof(test.failure_description),
                     "Response time too slow: %u ms", response_time_ms);
        }
        printf("    %s\n", test.failure_description);
    }
    
    // Clear fault
    hil_clear_fault(HIL_FAULT_DOOR_OBSTRUCTION);
    printf("\n");
}

// Test SAFE-003: Validate mitigation for "Loss of Speed Sensor"
void test_safe_003_speed_sensor_failure(void) {
    safety_test_t test = {
        .test_id = "SAFE-003",
        .test_name = "Speed Sensor Failure Handling",
        .hazard_id = "HAZ-003",
        .requirement_id = "SRS-SAFE-030",
    };
    
    printf("Executing: %s - %s\n", test.test_id, test.test_name);
    printf("  Hazard: %s\n", test.hazard_id);
    printf("  Requirement: %s\n\n", test.requirement_id);
    
    // Scenario: Train potentially moving, speed sensor fails
    hil_set_train_speed(30.0f);  // Moderate speed
    wait_ms(1000);
    
    // Inject speed sensor fault
    printf("  Injecting fault: Speed sensor failure...\n");
    hil_inject_fault(HIL_FAULT_SPEED_SENSOR);
    
    // Wait for fault detection (must be detected within 500 ms)
    uint32_t start_time = get_time_ms();
    uint32_t detection_time_ms = 0;
    bool fault_detected = false;
    
    while ((get_time_ms() - start_time) < 500) {
        if (system_get_alarm_status() & ALARM_SENSOR_FAULT) {
            detection_time_ms = get_time_ms() - start_time;
            fault_detected = true;
            break;
        }
        wait_ms(10);
    }
    
    // Verify safe state reached
    bool doors_locked = system_get_door_lock_status_left() && 
                         system_get_door_lock_status_right();
    bool safe_state = (system_get_state() == STATE_SAFE);
    
    test.passed = fault_detected && 
                   doors_locked && 
                   safe_state &&
                   (detection_time_ms <= 500);
    
    if (test.passed) {
        printf("  Result: PASS\n");
        printf("    - Fault detected: YES (time: %u ms)\n", detection_time_ms);
        printf("    - Doors locked: YES\n");
        printf("    - Safe state reached: YES\n");
    } else {
        printf("  Result: FAIL\n");
        printf("    - Fault detected: %s\n", fault_detected ? "YES" : "NO");
        printf("    - Doors locked: %s\n", doors_locked ? "YES" : "NO");
        printf("    - Safe state: %s\n", safe_state ? "YES" : "NO");
    }
    
    // Clear fault
    hil_clear_fault(HIL_FAULT_SPEED_SENSOR);
    printf("\n");
}

// Execute full safety validation suite
void run_safety_validation_suite(void) {
    printf("=== Safety Validation Test Suite ===\n");
    printf("Validates hazard mitigations from Hazard Log\n");
    printf("SIL 3 Requirements\n\n");
    
    // Initialize HIL for fault injection
    hil_init("hil_config.json");
    
    test_safe_001_unintended_door_opening();
    test_safe_002_door_obstruction_response();
    test_safe_003_speed_sensor_failure();
    
    // Additional safety tests for all hazards...
    // (Total: 18 safety tests covering all hazards)
    
    hil_shutdown();
}
```

### Traceability: Safety Tests to Hazard Log

```bash
# Create traceability from safety validation tests to Hazard Log
workspace.py trace create \
    --from validation \
    --to safety \
    --source-id "SAFE-001" \
    --target-id "HAZ-001" \
    --rationale "Validates mitigation for unintended door opening hazard" \
    --sil 3

workspace.py trace create \
    --from validation \
    --to safety \
    --source-id "SAFE-002" \
    --target-id "HAZ-002" \
    --rationale "Validates mitigation for door obstruction hazard" \
    --sil 3

# Generate hazard coverage report
workspace.py trace report \
    --from validation \
    --to safety \
    --format markdown \
    --output evidence/traceability/validation_hazard_coverage.md
```

---

## Operational Scenario Validation

### Customer-Defined Operational Scenarios

**EN 50128 Section 7.7.4.3**: "The Validator shall specify and perform supplementary tests... tests which stress the system by complex scenarios reflecting the actual needs of the user."

```c
// Operational scenario validation tests
// File: operational_scenario_validation.c

#include "validation_harness.h"
#include "hil_interface.h"
#include <stdio.h>

// Operational scenario structure
typedef struct {
    const char* scenario_id;
    const char* scenario_name;
    const char* description;
    const char* stakeholder;  // Who defined this scenario
    
    bool passed;
    uint32_t duration_ms;
    char notes[512];
} operational_scenario_t;

// Scenario OP-001: Normal Train Departure Sequence
void scenario_op_001_normal_departure(void) {
    operational_scenario_t scenario = {
        .scenario_id = "OP-001",
        .scenario_name = "Normal Train Departure",
        .description = "Complete sequence from station stop to mainline operation",
        .stakeholder = "Train Operator",
    };
    
    printf("=== Operational Scenario: %s ===\n", scenario.scenario_name);
    printf("ID: %s\n", scenario.scenario_id);
    printf("Stakeholder: %s\n", scenario.stakeholder);
    printf("Description: %s\n\n", scenario.description);
    
    uint32_t start_time = get_time_ms();
    bool success = true;
    
    // Step 1: Train at station, doors open, passengers boarding
    printf("Step 1: Train at station, doors open\n");
    hil_set_train_speed(0.0f);
    system_command_door_open();
    wait_ms(2000);
    
    if (!verify_doors_open()) {
        printf("  ERROR: Doors failed to open\n");
        success = false;
        goto scenario_end;
    }
    printf("  Doors open - passengers boarding\n");
    
    // Step 2: Operator closes doors for departure
    printf("\nStep 2: Operator initiates door close\n");
    wait_ms(15000);  // 15 seconds for boarding
    system_command_door_close();
    wait_ms(3000);   // Door close time
    
    if (!verify_doors_closed_and_locked()) {
        printf("  ERROR: Doors not properly closed and locked\n");
        success = false;
        goto scenario_end;
    }
    printf("  Doors closed and locked\n");
    
    // Step 3: Release brakes
    printf("\nStep 3: Release brakes\n");
    system_command_release_brakes();
    wait_ms(1000);
    
    if (!verify_brakes_released()) {
        printf("  ERROR: Brakes not released\n");
        success = false;
        goto scenario_end;
    }
    printf("  Brakes released\n");
    
    // Step 4: Apply traction, accelerate to 40 km/h
    printf("\nStep 4: Apply traction, accelerate to 40 km/h\n");
    hil_set_train_acceleration(1.0f);  // 1 m/s² acceleration
    wait_ms(11000);  // ~11 seconds to reach 40 km/h
    
    float speed = hil_get_train_speed();
    if (speed < 38.0f || speed > 42.0f) {
        printf("  ERROR: Speed out of range: %.1f km/h\n", speed);
        success = false;
        goto scenario_end;
    }
    printf("  Speed reached: %.1f km/h\n", speed);
    
    // Verify doors still locked while moving
    if (!verify_doors_closed_and_locked()) {
        printf("  ERROR: Doors unlocked while moving!\n");
        success = false;
        goto scenario_end;
    }
    printf("  Doors remain locked (safety verified)\n");
    
    // Step 5: Cruise at 80 km/h (mainline operation)
    printf("\nStep 5: Accelerate to mainline speed (80 km/h)\n");
    hil_set_train_acceleration(0.8f);
    wait_ms(15000);  // Accelerate to 80 km/h
    
    speed = hil_get_train_speed();
    if (speed < 78.0f || speed > 82.0f) {
        printf("  ERROR: Speed out of range: %.1f km/h\n", speed);
        success = false;
        goto scenario_end;
    }
    printf("  Mainline speed reached: %.1f km/h\n", speed);
    printf("  Doors remain locked (safety verified)\n");
    
scenario_end:
    scenario.duration_ms = get_time_ms() - start_time;
    scenario.passed = success;
    
    if (scenario.passed) {
        printf("\n=== Scenario Result: PASS ===\n");
        printf("Duration: %.1f seconds\n", scenario.duration_ms / 1000.0f);
        strcpy(scenario.notes, "Normal departure sequence completed successfully");
    } else {
        printf("\n=== Scenario Result: FAIL ===\n");
        strcpy(scenario.notes, "Scenario failed - see error messages above");
    }
    printf("\n");
}

// Scenario OP-002: Emergency Stop from High Speed
void scenario_op_002_emergency_stop(void) {
    operational_scenario_t scenario = {
        .scenario_id = "OP-002",
        .scenario_name = "Emergency Stop from High Speed",
        .description = "Train traveling at 120 km/h, emergency brake applied",
        .stakeholder = "Safety Engineer",
    };
    
    printf("=== Operational Scenario: %s ===\n", scenario.scenario_name);
    printf("ID: %s\n", scenario.scenario_id);
    printf("Stakeholder: %s\n", scenario.stakeholder);
    printf("Description: %s\n\n", scenario.description);
    
    uint32_t start_time = get_time_ms();
    bool success = true;
    
    // Step 1: Train traveling at 120 km/h
    printf("Step 1: Train at high speed (120 km/h)\n");
    hil_set_train_speed(120.0f);
    wait_ms(2000);
    printf("  Speed: %.1f km/h\n", hil_get_train_speed());
    
    // Step 2: Emergency event detected (obstacle on track)
    printf("\nStep 2: Emergency! Obstacle detected on track\n");
    printf("  Triggering emergency brake...\n");
    
    uint32_t brake_start_time = get_time_ms();
    system_trigger_emergency_brake();
    
    // Step 3: Verify immediate brake response
    wait_ms(100);  // Max 100 ms response time for SIL 3
    uint32_t brake_response_time = get_time_ms() - brake_start_time;
    
    if (!verify_emergency_brake_active()) {
        printf("  ERROR: Emergency brake not activated\n");
        success = false;
        goto emergency_end;
    }
    printf("  Emergency brake activated (response: %u ms)\n", brake_response_time);
    
    if (brake_response_time > 100) {
        printf("  WARNING: Response time exceeds 100 ms limit\n");
        success = false;
    }
    
    // Step 4: Monitor deceleration until stop
    printf("\nStep 3: Monitoring deceleration...\n");
    float prev_speed = hil_get_train_speed();
    uint32_t position_at_brake = hil_get_train_position();
    
    while (hil_get_train_speed() > 1.0f) {
        float current_speed = hil_get_train_speed();
        
        // Verify continuous deceleration
        if (current_speed > prev_speed + 1.0f) {  // Allow 1 km/h tolerance
            printf("  ERROR: Speed increased during braking!\n");
            success = false;
            break;
        }
        
        prev_speed = current_speed;
        wait_ms(100);
    }
    
    uint32_t stop_time = get_time_ms() - brake_start_time;
    uint32_t stop_distance = hil_get_train_position() - position_at_brake;
    
    printf("  Train stopped\n");
    printf("  Stop time: %.1f seconds\n", stop_time / 1000.0f);
    printf("  Stop distance: %u meters\n", stop_distance);
    
    // Step 5: Verify safety state
    printf("\nStep 4: Verifying safety state...\n");
    
    // Doors must remain locked
    if (!verify_doors_closed_and_locked()) {
        printf("  ERROR: Doors not locked in safe state\n");
        success = false;
    } else {
        printf("  Doors locked: YES\n");
    }
    
    // System in safe state
    if (system_get_state() != STATE_SAFE) {
        printf("  ERROR: System not in safe state\n");
        success = false;
    } else {
        printf("  System in safe state: YES\n");
    }
    
emergency_end:
    scenario.duration_ms = get_time_ms() - start_time;
    scenario.passed = success;
    
    if (scenario.passed) {
        printf("\n=== Scenario Result: PASS ===\n");
        snprintf(scenario.notes, sizeof(scenario.notes),
                 "Emergency stop completed: %.1fs, %um distance",
                 stop_time / 1000.0f, stop_distance);
    } else {
        printf("\n=== Scenario Result: FAIL ===\n");
        strcpy(scenario.notes, "Emergency stop failed - see error messages");
    }
    printf("\n");
}

// Scenario OP-003: Degraded Operation (Single Door Fault)
void scenario_op_003_degraded_operation(void) {
    operational_scenario_t scenario = {
        .scenario_id = "OP-003",
        .scenario_name = "Degraded Operation - Single Door Fault",
        .description = "One door fails, train continues operation with reduced capacity",
        .stakeholder = "Operations Manager",
    };
    
    printf("=== Operational Scenario: %s ===\n", scenario.scenario_name);
    printf("ID: %s\n", scenario.scenario_id);
    printf("Stakeholder: %s\n", scenario.stakeholder);
    printf("Description: %s\n\n", scenario.description);
    
    uint32_t start_time = get_time_ms();
    bool success = true;
    
    // Step 1: Normal operation, train at station
    printf("Step 1: Train at station, normal operation\n");
    hil_set_train_speed(0.0f);
    wait_ms(1000);
    
    // Step 2: Left door fails to open
    printf("\nStep 2: Attempting to open doors...\n");
    system_command_door_open();
    wait_ms(3000);
    
    // Inject left door fault
    hil_inject_fault(HIL_FAULT_DOOR_LEFT_MOTOR);
    printf("  FAULT: Left door motor failure\n");
    
    // Step 3: Verify degraded mode entered
    printf("\nStep 3: Verifying degraded mode...\n");
    
    // Right door should still work
    bool right_door_open = hil_get_door_open_sensor_right();
    bool left_door_failed = !hil_get_door_open_sensor_left();
    bool degraded_alarm = (system_get_alarm_status() & ALARM_DEGRADED_MODE);
    
    if (!right_door_open || !left_door_failed || !degraded_alarm) {
        printf("  ERROR: System did not enter degraded mode correctly\n");
        success = false;
        goto degraded_end;
    }
    
    printf("  Right door operational: YES\n");
    printf("  Left door failed: YES\n");
    printf("  Degraded mode alarm: YES\n");
    printf("  System allows continued operation with reduced capacity\n");
    
    // Step 4: Close doors and depart
    printf("\nStep 4: Close doors and depart (degraded mode)\n");
    system_command_door_close();
    wait_ms(3000);
    
    // Verify right door closed, left door fault handled
    bool right_door_closed = hil_get_door_closed_sensor_right();
    if (!right_door_closed) {
        printf("  ERROR: Right door failed to close\n");
        success = false;
        goto degraded_end;
    }
    printf("  Right door closed: YES\n");
    printf("  Left door: FAULT (locked in last known position)\n");
    
    // Step 5: Accelerate with speed limit in degraded mode
    printf("\nStep 5: Accelerate (degraded mode speed limit: 60 km/h)\n");
    hil_set_train_acceleration(0.8f);
    wait_ms(10000);
    
    float speed = hil_get_train_speed();
    if (speed > 62.0f) {  // Should not exceed degraded limit + margin
        printf("  ERROR: Speed exceeds degraded mode limit: %.1f km/h\n", speed);
        success = false;
    } else {
        printf("  Speed: %.1f km/h (within degraded limit)\n", speed);
    }
    
degraded_end:
    scenario.duration_ms = get_time_ms() - start_time;
    scenario.passed = success;
    
    hil_clear_fault(HIL_FAULT_DOOR_LEFT_MOTOR);
    
    if (scenario.passed) {
        printf("\n=== Scenario Result: PASS ===\n");
        strcpy(scenario.notes, "Degraded operation handled correctly, service maintained");
    } else {
        printf("\n=== Scenario Result: FAIL ===\n");
        strcpy(scenario.notes, "Degraded mode handling failed");
    }
    printf("\n");
}

// Execute all operational scenarios
void run_operational_scenario_validation(void) {
    printf("==================================================\n");
    printf("  EN 50128 Operational Scenario Validation\n");
    printf("  Section 7.7.4.3: Complex scenarios reflecting user needs\n");
    printf("==================================================\n\n");
    
    hil_init("hil_config.json");
    
    scenario_op_001_normal_departure();
    scenario_op_002_emergency_stop();
    scenario_op_003_degraded_operation();
    
    // Additional operational scenarios...
    // Total: 8 operational scenarios covering all modes and fault conditions
    
    hil_shutdown();
}
```

---

## Requirements Coverage Validation

### Traceability Matrix Verification

**EN 50128 Section 7.7.4.8.c**: "An evaluation of the test coverage on the requirements of the Software Requirements Specification shall be provided."

```bash
# Generate complete requirements coverage report
workspace.py trace report \
    --from validation \
    --to requirements \
    --format markdown \
    --output evidence/traceability/validation_requirements_coverage_full.md \
    --include-stats

# Validate 100% requirements coverage
workspace.py trace validate \
    --phase validation \
    --sil 3 \
    --coverage 100 \
    --report-uncovered \
    --output evidence/traceability/validation_coverage_check.json
```

**Expected Output** (validation_requirements_coverage_full.md):

```markdown
# Validation Requirements Coverage Report

**Project**: Railway Door Control System  
**SIL Level**: 3  
**Date**: 2026-03-14  
**Validator**: John Smith (Independent)

## Coverage Statistics

| Metric | Count | Percentage |
|--------|-------|------------|
| **Total SRS Requirements** | 87 | 100% |
| **Requirements Covered by Validation Tests** | 87 | 100% ✅ |
| **Requirements NOT Covered** | 0 | 0% |
| **Functional Requirements Covered** | 45 / 45 | 100% ✅ |
| **Performance Requirements Covered** | 12 / 12 | 100% ✅ |
| **Safety Requirements Covered** | 18 / 18 | 100% ✅ |
| **Interface Requirements Covered** | 12 / 12 | 100% ✅ |

## Traceability Matrix

| SRS Requirement | Description | Validation Test(s) | Status |
|-----------------|-------------|-------------------|--------|
| SRS-SAFE-010 | Door interlock while moving | VAL-FUNC-001, SAFE-001 | ✅ PASS |
| SRS-SAFE-015 | Obstruction detection | VAL-FUNC-004, SAFE-002 | ✅ PASS |
| SRS-FUNC-020 | Door open when stopped | VAL-FUNC-002 | ✅ PASS |
| SRS-FUNC-025 | Auto-close timeout | VAL-FUNC-003 | ✅ PASS |
| SRS-PERF-010 | Safety monitor timing | PERF-001 | ✅ PASS |
| ... | ... | ... | ... |

## Validation Conclusion

✅ **All SRS requirements validated successfully (100% coverage)**
✅ **All validation tests PASSED**
✅ **Software is fit for its intended application**
```

---

## Validation Report Generation

### Software Validation Report Template (EN 50128 Section 7.7.4.6-7.7.4.11)

```markdown
# Software Validation Report

**Document Control**
- **Document ID**: DOC-VAL-REP-001
- **Version**: 1.0
- **Date**: 2026-06-10
- **Author**: John Smith (Validator, Independent)
- **SIL Level**: 3
- **Project**: Railway Door Control System
- **Software Version**: 1.0.0

## Document Control Table

| Version | Date | Author | Changes | Approver |
|---------|------|--------|---------|----------|
| 0.1 | 2026-06-01 | J. Smith | Initial draft | - |
| 1.0 | 2026-06-10 | J. Smith | Final release | Safety Manager |

## Approvals (EN 50128 Section 5.1.2.10.f - Validator Independence)

| Role | Name | Signature | Date | Independence |
|------|------|-----------|------|--------------|
| **Validator** (Lead) | John Smith | _________ | 2026-06-10 | ✅ Independent |
| **Safety Manager** | Alice Johnson | _________ | 2026-06-10 | ✅ Independent |
| **Quality Manager** | Bob Wilson | _________ | 2026-06-10 | N/A |
| **Customer Representative** | David Lee | _________ | 2026-06-15 | ✅ Independent |

**Note**: Validator does NOT report to Project Manager (EN 50128 SIL 3-4 requirement).

---

## 1. Executive Summary (EN 50128 Section 7.7.4.8)

### 1.1 Validation Objective
Validate that the Railway Door Control System software (Version 1.0.0, SIL 3) meets stakeholder needs and is fit for its intended application in mainline railway operations.

### 1.2 Validation Result

**✅ VALIDATION PASSED**

The Railway Door Control System software has been validated against all system requirements and operational scenarios. All validation tests passed successfully. The software is **fit for its intended application** and ready for operational deployment at SIL 3.

### 1.3 Summary Statistics

| Activity | Tests Planned | Tests Executed | Passed | Failed | Status |
|----------|--------------|----------------|--------|--------|--------|
| Functional Validation | 45 | 45 | 45 | 0 | ✅ PASS |
| Performance Validation | 12 | 12 | 12 | 0 | ✅ PASS |
| Safety Validation | 18 | 18 | 18 | 0 | ✅ PASS |
| Operational Scenarios | 8 | 8 | 8 | 0 | ✅ PASS |
| User Acceptance Tests | 5 | 5 | 5 | 0 | ✅ PASS |
| **TOTAL** | **88** | **88** | **88** | **0** | **✅ PASS** |

**Pass Rate**: 100%  
**Critical Defects**: 0  
**High-Priority Defects**: 0

### 1.4 Independence Confirmation (SIL 3)

✅ Validator (John Smith) is independent from development team  
✅ Validator does NOT report to Project Manager  
✅ Validator reports to Safety Manager  
✅ No organizational, financial, or schedule pressure on validation decisions

---

## 2. Validation Environment (EN 50128 Section 7.7.4.5, 7.7.4.10.b)

### 2.1 Target Platform Configuration

**Hardware**:
- Processor: ARM Cortex-M4 STM32F407, 168 MHz
- Memory: 192 KB RAM, 1 MB Flash
- I/O: 4x CAN, 2x UART, 16x GPIO, 4x ADC
- Safety Features: Dual watchdog, ECC memory, CRC unit

**Software**:
- Operating System: FreeRTOS v10.4.6
- Compiler: arm-none-eabi-gcc v11.2.1 (-O2 -g)
- Safety Library: libsafety v2.1.0 (qualified tool T2)

**Configuration**:
- SIL 3 safety parameters enabled
- Watchdog timeout: 100 ms
- Diagnostic monitoring: Active
- Logging: Enabled for validation

### 2.2 Test Environment

**Laboratory Environment**:
- 2x STM32F407 Discovery boards (production-equivalent)
- Benchtop power supply (calibrated 2026-02-01)
- CAN analyzer (calibrated 2026-02-10)
- Oscilloscope (calibrated 2026-01-20)

**Hardware-in-the-Loop (HIL)**:
- dSPACE HIL Simulator (qualified tool T3)
- Realistic railway environment simulation
- Fault injection capability
- Certified 2025-12-15

**Pilot Installation**:
- Railway depot test track, 500m
- Real train hardware interfaces
- Customer supervision (David Lee, Operations Manager)

### 2.3 Test Equipment Identification (EN 50128 Section 7.7.4.10.b)

| Equipment | Model | Serial Number | Calibration Date | Cert. Number |
|-----------|-------|---------------|------------------|--------------|
| CAN Analyzer | Vector CANalyzer | VN1234 | 2026-02-10 | CAL-2026-045 |
| Oscilloscope | Tektronix MSO4104 | TEK5678 | 2026-01-20 | CAL-2026-012 |
| Power Supply | Keysight E3631A | KS9012 | 2026-02-01 | CAL-2026-029 |
| HIL Simulator | dSPACE SCALEXIO | DS4321 | N/A (digital) | CERT-T3-2025 |

---

## 3. Validation Activities Summary

### 3.1 Functional Validation (EN 50128 Table A.7, MANDATORY SIL 3)

**Approach**: Functional and Black-box Testing (EN 50128 Table A.14)

**Test Coverage**:
- All 87 system requirements from SRS validated
- All operational modes tested (normal, degraded, safe, maintenance)
- All user interfaces tested (operator controls, HMI)
- All communication interfaces tested (CAN, UART)

**Results**:
- 45 functional tests executed
- 45 tests PASSED
- 0 tests FAILED
- 100% functional requirements coverage

**Key Tests**:
- VAL-FUNC-001: Door interlock while moving (PASS - 82ms response)
- VAL-FUNC-004: Obstruction detection (PASS - 178ms response)
- VAL-FUNC-005: Emergency brake locks doors (PASS - 45ms response)

### 3.2 Performance Validation (EN 50128 Table A.7, MANDATORY SIL 3)

**Approach**: Performance Testing (EN 50128 Table A.18)

**Real-Time Requirements Validated**:
- Task execution times (WCET)
- Task jitter and deadline adherence
- Interrupt response times
- CPU utilization under peak load
- Memory utilization (RAM, stack)

**Results**:
- 12 performance tests executed
- 12 tests PASSED
- 0 tests FAILED

**Key Results**:

| Requirement | Limit | Measured | Margin | Status |
|-------------|-------|----------|--------|--------|
| Safety Monitor WCET | 1000 us | 815 us | 18.5% | ✅ PASS |
| Door Control WCET | 10000 us | 8234 us | 17.7% | ✅ PASS |
| CPU Utilization (peak) | 80% | 68.2% | 14.8% | ✅ PASS |
| RAM Utilization | 75% | 62.1% | 17.2% | ✅ PASS |
| Interrupt Response | 50 us | 38 us | 24.0% | ✅ PASS |

**All performance requirements met with adequate margin (≥10%).**

### 3.3 Safety Validation

**Approach**: Hazard-based validation with fault injection

**Hazard Coverage**:
- All 18 hazards from Hazard Log validated
- Fault injection testing performed (HIL)
- Safe state transitions verified
- Redundancy and voting mechanisms tested

**Results**:
- 18 safety tests executed
- 18 tests PASSED
- 0 tests FAILED
- 100% hazard mitigation coverage

**Key Safety Tests**:

| Test ID | Hazard | Mitigation Validated | Result |
|---------|--------|----------------------|--------|
| SAFE-001 | Unintended door opening | Door interlock enforced | ✅ PASS |
| SAFE-002 | Door closes on passenger | Obstruction reversal (178ms) | ✅ PASS |
| SAFE-003 | Loss of speed sensor | Fault detected (342ms), safe state | ✅ PASS |

**All hazard mitigations validated successfully.**

### 3.4 Operational Scenarios (EN 50128 Section 7.7.4.3)

**Approach**: Complex scenarios reflecting actual user needs

**Scenarios Validated**:
1. OP-001: Normal departure sequence (PASS - 43.2s)
2. OP-002: Emergency stop from 120 km/h (PASS - 18.4s, 427m)
3. OP-003: Degraded operation (single door fault) (PASS)
4. OP-004: Station stop precision (PASS - ±15cm accuracy)
5. OP-005: Fault recovery and reset (PASS)
6. OP-006: Cold start initialization (PASS - 2.1s)
7. OP-007: Environmental stress (temperature, vibration) (PASS)
8. OP-008: Extended operation (24 hours) (PASS)

**Results**:
- 8 operational scenarios executed
- 8 scenarios PASSED
- 0 scenarios FAILED

**Stakeholder Feedback**:
- Train Operator: "Intuitive controls, smooth operation"
- Maintenance Engineer: "Clear diagnostics, easy troubleshooting"
- Safety Engineer: "Robust fault handling, predictable safe states"

### 3.5 User Acceptance Testing

**Approach**: Customer-supervised operational testing at pilot site

**Acceptance Tests**:
1. UAT-001: Driver interface usability (PASS - "Intuitive")
2. UAT-002: Operational performance (PASS - "Meets expectations")
3. UAT-003: Maintenance interface (PASS - "Clear diagnostics")
4. UAT-004: Safety behavior (PASS - "Confident in safety")
5. UAT-005: Overall system satisfaction (PASS - "Ready for deployment")

**Customer Acceptance**:
✅ Customer Representative (David Lee) approved software for operational use

---

## 4. Requirements Coverage (EN 50128 Section 7.7.4.8.c)

**Requirements Traceability**: 100% complete

| Category | Total | Covered | Coverage |
|----------|-------|---------|----------|
| Functional Requirements | 45 | 45 | 100% ✅ |
| Performance Requirements | 12 | 12 | 100% ✅ |
| Safety Requirements | 18 | 18 | 100% ✅ |
| Interface Requirements | 12 | 12 | 100% ✅ |
| **TOTAL** | **87** | **87** | **100% ✅** |

**Traceability Evidence**: `evidence/traceability/validation_requirements_coverage_full.md`

---

## 5. Verification Activities Evaluation (EN 50128 Section 7.7.4.8.d)

**Verification Evidence Reviewed**:
- ✅ Verification Report (DOC-VER-REP-001) - Approved
- ✅ Integration Report (DOC-INT-REP-001) - Approved
- ✅ Unit Test Reports (Phase 5) - All tests passed
- ✅ Static Analysis Reports (Cppcheck, Clang) - Zero critical issues
- ✅ Code Coverage Reports - 100% statement, branch, MC/DC (SIL 3)
- ✅ Code Review Reports - All code reviewed, approved
- ✅ MISRA C Compliance Report - Zero mandatory violations

**Traceability Verification**:
✅ Requirements → Design → Code → Tests: COMPLETE
✅ All traceability matrices reviewed and validated

**Verification Conclusion**: All verification activities completed successfully per Software Verification Plan.

---

## 6. EN 50128 Technique Compliance (EN 50128 Section 7.7.4.9)

**Table A.7 Compliance** (Overall Software Testing, SIL 3-4):

| # | Technique | SIL 3-4 | Applied | Evidence |
|---|-----------|---------|---------|----------|
| 1 | Performance Testing | **M** | ✅ YES | Section 3.2, 12 tests |
| 2 | Functional and Black-box Testing | **M** | ✅ YES | Section 3.1, 45 tests |
| 3 | Modelling | R | NO | Not required (SIL 3) |

**Combination Effectiveness**: The combination of MANDATORY techniques (Performance Testing + Functional Testing) is appropriate for SIL 3. Comprehensive coverage of all requirements, operational scenarios, and safety hazards demonstrates effective validation.

---

## 7. Software Configuration (EN 50128 Section 7.7.4.10.a)

**Software Identity**:
- Software Component: Railway Door Control System
- Version: 1.0.0
- Git Commit: `a1b2c3d4e5f6g7h8i9j0`
- Build Date: 2026-05-20 14:35:22 UTC
- Compiler: arm-none-eabi-gcc 11.2.1 (-O2 -g -std=c11)
- Configuration Baseline: BASELINE-6.0

**Configuration Items**:
- Source code: 87 files, 15,234 SLOC
- Headers: 45 files
- Libraries: libsafety v2.1.0, FreeRTOS v10.4.6
- Test code: 122 files, 8,923 SLOC

**Configuration Status**: BASELINED (BASELINE-6.0, approved by CM)

---

## 8. Deviations and Non-Conformances (EN 50128 Section 7.7.4.10.e-h, 7.7.4.11)

### 8.1 Deviations Found During Validation

**ZERO deviations found during validation testing.**

All tests passed on first execution. No defects detected. No corrective actions required.

### 8.2 Known Limitations (Release Note Items)

**Operational Limitations**:
1. **Speed Sensor Redundancy**: Single speed sensor configuration. Degraded mode entered if sensor fails. (LOW risk, documented in operator manual)
2. **Maximum Train Speed**: Validated up to 120 km/h. Higher speeds require additional validation. (Documented in SRS)

**Environmental Limitations**:
- Operating temperature: -40°C to +70°C (validated)
- Humidity: 0-95% non-condensing (validated)
- EMI: EN 50121-3-2 Class A1 (validated)

### 8.3 Risk Evaluation (EN 50128 Section 7.7.4.10.f)

All known limitations evaluated for risk impact:
- ✅ Speed sensor limitation: LOW risk (safe state on failure)
- ✅ Speed range limitation: NO risk (documented, enforced)

**No safety-impacting limitations identified.**

---

## 9. Conclusion (EN 50128 Section 7.7.4.8, 7.7.4.10.i)

### 9.1 Software Validation Plan Objectives (EN 50128 Section 7.7.4.8.a)

✅ **All objectives and criteria of the Software Validation Plan (DOC-VAL-SVP-001) have been met.**

No deviations from the plan. All planned validation activities completed successfully.

### 9.2 Software Requirements Specification Fulfillment (EN 50128 Section 7.7.4.8.b)

✅ **The software on its target machine fulfills ALL requirements set out in the Software Requirements Specification (DOC-REQ-SRS-001).**

100% requirements coverage validated. All functional, performance, safety, and interface requirements met.

### 9.3 Fitness for Intended Application (EN 50128 Section 7.7.4.10.i)

✅ **The Railway Door Control System software (Version 1.0.0, SIL 3) is FIT FOR ITS INTENDED APPLICATION in mainline railway operations, taking into account the application conditions and constraints documented in the Release Note.**

### 9.4 Validator Recommendation

**I, John Smith, Independent Validator, recommend approval for operational deployment.**

---

## 10. Release Approval (EN 50128 Section 5.1.2.8)

**Validator Agreement for Software Release** (EN 50128 Section 5.1.2.8):

✅ **APPROVAL GRANTED** for operational deployment

**Restrictions and Constraints**: See Release Note (DOC-VAL-RN-001)

---

## 11. Approvals

| Role | Name | Signature | Date | Independence |
|------|------|-----------|------|--------------|
| **Validator** (Lead) | John Smith | _________________ | 2026-06-10 | ✅ Independent |
| **Safety Manager** | Alice Johnson | _________________ | 2026-06-10 | ✅ Independent |
| **Quality Manager** | Bob Wilson | _________________ | 2026-06-10 | N/A |
| **Customer Representative** | David Lee | _________________ | 2026-06-15 | ✅ Independent |

---

## 12. Appendices

**Appendix A**: Detailed Test Results  
**Appendix B**: Traceability Matrices  
**Appendix C**: HIL Test Logs  
**Appendix D**: Performance Measurement Data  
**Appendix E**: Customer Acceptance Certificates

**Evidence Location**: `evidence/validation/`
```

---

## Tool Integration

### Workflow Management: Submit Validation Report for Review

```bash
# Submit Software Validation Report to workflow system
workspace.py wf submit \
    --deliverable "DOC-VAL-REP-001" \
    --phase validation \
    --author "John Smith (Validator)" \
    --description "Software Validation Report - Railway Door Control System v1.0.0, SIL 3" \
    --files evidence/validation/DOC-VAL-REP-001_Software_Validation_Report.md

# Validation report must be reviewed by QUA first (template compliance)
# Then reviewed by Safety Manager (technical approval)
# Then reviewed by Customer (acceptance)

# Check workflow status
workspace.py wf status --deliverable "DOC-VAL-REP-001"
```

**Expected Workflow**:
1. **Validator** (VAL) creates Validation Report
2. **Quality Assurance** (QUA) reviews template compliance (1 pass)
3. **Safety Manager** reviews technical content and approves
4. **Customer** reviews and provides acceptance sign-off
5. **Configuration Manager** (CM) baselines deliverable

---

### Traceability: Validation Complete

```bash
# Finalize all validation traceability
workspace.py trace validate --phase validation --sil 3 --final

# Generate comprehensive traceability report for certification
workspace.py trace report \
    --from validation \
    --to requirements,design,implementation,integration,verification \
    --format markdown \
    --output evidence/traceability/END_TO_END_TRACEABILITY.md \
    --include-all

# Archive validation evidence
tar -czf validation_evidence_v1.0.0.tar.gz evidence/validation/
```

---

## SIL-Specific Requirements

### SIL 0-1

**Validation Approach**:
- Functional testing (HR)
- Independent validation: Recommended but not required
- Performance testing: Not required
- Operational scenarios: Recommended

**Minimum Requirements**:
- Test all functional requirements
- Document test results
- Customer acceptance

---

### SIL 2

**Validation Approach**:
- Functional testing (HR) ← Use functional testing
- Performance testing (HR) ← Use performance testing
- Independent validation: **Highly Recommended**
- Operational scenarios: Required

**Minimum Requirements**:
- Test all functional and performance requirements
- Independent validation highly recommended (separate from development)
- Customer acceptance
- Validation report with traceability

---

### SIL 3-4 (MANDATORY Requirements)

**Validation Approach**:
- **Functional testing (M)** ← **MANDATORY**
- **Performance testing (M)** ← **MANDATORY**
- **Independent validation (M)** ← **MANDATORY**
- Operational scenarios: **MANDATORY**
- Safety validation: **MANDATORY**

**Independence Requirements** (EN 50128 Section 5.1.2.10.f):
✅ Validator MUST be independent from development team  
✅ Validator SHALL NOT report to Project Manager  
✅ Validator reports to Safety Manager or Customer  
✅ Validator gives final approval/disapproval for software release

**Minimum Requirements**:
- Test ALL requirements (100% coverage)
- Performance requirements met with margin (≥10%)
- All hazards validated with fault injection
- Operational scenarios validated in target/HIL environment
- Pilot installation testing (highly recommended)
- Customer acceptance required
- Independent Validation Report required

---

## Example Validation Scenarios

### Complete Validation Test Suite Execution

```bash
# Main validation program
# File: main_validation.c

int main(void) {
    printf("==================================================\n");
    printf("  EN 50128 System Validation - SIL 3\n");
    printf("  Railway Door Control System v1.0.0\n");
    printf("  Validator: John Smith (Independent)\n");
    printf("==================================================\n\n");
    
    // 1. Functional Validation (MANDATORY SIL 3)
    run_functional_validation_suite();
    
    // 2. Performance Validation (MANDATORY SIL 3)
    run_performance_validation_suite();
    
    // 3. Safety Validation
    run_safety_validation_suite();
    
    // 4. Operational Scenarios
    run_operational_scenario_validation();
    
    // 5. Generate validation report
    generate_validation_report();
    
    printf("==================================================\n");
    printf("  Validation Complete\n");
    printf("  See: validation_report.md\n");
    printf("==================================================\n");
    
    return 0;
}
```

**Compilation and Execution**:

```bash
# Cross-compile for ARM Cortex-M4 target
arm-none-eabi-gcc -O2 -g -mcpu=cortex-m4 -mthumb \
    -o validation_tests.elf \
    main_validation.c \
    functional_validation_tests.c \
    performance_validation_tests.c \
    safety_validation_tests.c \
    operational_scenario_validation.c \
    validation_harness.c \
    hil_interface.c \
    -lsafety -lfreertos

# Flash to target hardware
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
    -c "program validation_tests.elf verify reset exit"

# Execute on target (via UART console)
minicom -D /dev/ttyUSB0 -b 115200

# Collect results
# Results logged to: evidence/validation/validation_*.log
```

---

## References

- **EN 50128:2011 Section 7.7**: Overall Software Testing / Final Validation
- **EN 50128:2011 Table A.7**: Overall Software Testing Techniques
- **EN 50128:2011 Table A.14**: Functional and Black-box Testing
- **EN 50128:2011 Table A.18**: Performance Testing
- **EN 50128:2011 Section 5.1.2.10.f**: Validator Independence
- **EN 50128:2011 Section 6.3.4.7-6.3.4.11**: Validation Report Requirements

---

## Summary

This **System Validation Workflow** provides:

1. ✅ Complete validation planning (SVP template)
2. ✅ Validation environment setup (laboratory, HIL, pilot)
3. ✅ Functional validation (MANDATORY SIL 3-4)
4. ✅ Performance validation (MANDATORY SIL 3-4)
5. ✅ Safety validation (hazard-based with fault injection)
6. ✅ Operational scenarios (customer-defined)
7. ✅ Requirements coverage (100% traceability)
8. ✅ Validation report generation (EN 50128 compliant)
9. ✅ Tool integration (workspace.py trace and wf)
10. ✅ SIL-specific requirements (0-4)
11. ✅ Complete C code examples (validation harness, HIL, tests)
12. ✅ Independence requirements (SIL 3-4)

**Total**: ~1,200 lines, ~50 pages, comprehensive EN 50128 Section 7.7 coverage.
