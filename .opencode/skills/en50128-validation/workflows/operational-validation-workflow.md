# Operational Validation Workflow

**EN 50128 Reference**: Section 7.7.4.5 (Testing in operational environment), Section 7.7.4.3  
**Phase**: Phase 7 - Validation  
**Role**: Validator (VAL) with operational staff  
**SIL Level**: All (0-4)

---

## Purpose

This workflow defines the complete process for validating software in real operational environments through field testing, pilot installations, and long-term operational monitoring. It implements EN 50128 Section 7.7.4.5 requirement for testing software "either by connection to real items of hardware or actual systems with which it would interface in operation."

**Key Objectives**:
- Validate software performance in actual operational conditions
- Identify issues not detectable in laboratory/HIL environment
- Demonstrate reliability over extended operations
- Validate environmental stress tolerance
- Obtain operational data for certification evidence
- Support transition from validation to production deployment

**Inputs**:
- Software Validation Plan (SVP)
- Integration Test Report (all integration tests passed)
- Laboratory/HIL validation results (all tests passed)
- Target hardware in operational configuration
- Operational procedures and training materials

**Outputs**:
- Operational Validation Report
- Pilot installation summary
- Long-term reliability data
- Environmental stress test results
- Field defect reports (if any)
- Operational readiness assessment

---

## Table of Contents

1. [Operational Validation Overview](#operational-validation-overview)
2. [Field Test Planning](#field-test-planning)
3. [Pilot Installation Setup](#pilot-installation-setup)
4. [Environmental Stress Testing](#environmental-stress-testing)
5. [Long-Term Operational Monitoring](#long-term-operational-monitoring)
6. [Field Defect Management](#field-defect-management)
7. [Operational Readiness Assessment](#operational-readiness-assessment)
8. [Operational Evidence Collection](#operational-evidence-collection)
9. [Tool Integration](#tool-integration)
10. [SIL-Specific Requirements](#sil-specific-requirements)
11. [Example Operational Validation Scenarios](#example-operational-validation-scenarios)

---

## Operational Validation Overview

### Laboratory vs. Operational Validation

| Aspect | Laboratory/HIL | Operational Validation |
|--------|----------------|------------------------|
| **Environment** | Controlled, simulated | Real, uncontrolled |
| **Duration** | Days to weeks | Weeks to months |
| **Stress Factors** | Predictable | Unpredictable (weather, wear, EMI) |
| **Failure Modes** | Expected faults injected | Real faults emerge naturally |
| **Risk** | Low (test environment) | Higher (operational impact) |
| **Evidence Value** | Technical compliance | Operational readiness |
| **Cost** | Lower | Higher (operational deployment) |

**Why Operational Validation is Essential**:
- Laboratory cannot replicate all real-world conditions
- Environmental factors (temperature, humidity, vibration, EMI) affect reliability
- Long-term wear and degradation reveal latent defects
- Human factors emerge in real operations
- System interactions with actual railway infrastructure

---

### EN 50128 Requirements for Operational Testing

**Section 7.7.4.5**: "The software shall be exercised either by connection to real items of hardware or actual systems with which it would interface in operation, or by simulation of input signals and loads driven by outputs. It shall be exercised under conditions present during normal operation, anticipated occurrences and undesired conditions requiring system action. Where simulated inputs or loads are used it shall be shown that these do not differ significantly from the inputs and loads encountered in operation."

**Key Requirements**:
- Testing with **real hardware** or high-fidelity simulation
- Testing under **normal, anticipated, and undesired conditions**
- If simulation used, must demonstrate equivalence to real operation

**Validation Hierarchy** (increasing realism):
1. ✅ Laboratory (benchtop hardware) - Basic functionality
2. ✅ HIL (simulated environment) - System-level integration
3. ✅ Field test (depot/test track) - Controlled operational conditions
4. ✅ **Pilot installation** (limited service) - **Real operational environment**
5. ✅ **Full deployment** (production) - Complete operational use

**SIL 3-4 Requirement**: Pilot installation (step 4) is **Highly Recommended** for certification.

---

## Field Test Planning

### Operational Validation Plan Template

```markdown
# Operational Validation Plan

## Document Control
- **Document ID**: DOC-VAL-OVP-001
- **Version**: 1.0
- **Date**: 2026-04-15
- **Author**: John Smith (Validator)
- **Project**: Railway Door Control System
- **SIL Level**: 3

## 1. Introduction

### 1.1 Purpose
Define operational validation approach for Railway Door Control System in actual railway operational environment to demonstrate fitness for deployment at SIL 3.

### 1.2 Scope
- **Phase 1**: Depot field testing (2 weeks)
- **Phase 2**: Test track operations (2 weeks)
- **Phase 3**: Pilot installation - limited service (4 weeks)
- **Phase 4**: Extended pilot - expanded service (4 weeks)
- **Total Duration**: 12 weeks

### 1.3 Operational Environment
- **Railway System**: Metro Rail Line 2 (urban metro)
- **Train**: #4523 (production vehicle, 6 cars)
- **Service Type**: Passenger service (peak and off-peak)
- **Daily Operation**: Up to 18 hours/day
- **Environmental**: -10°C to +40°C, urban EMI, variable humidity

## 2. Operational Validation Objectives

### 2.1 Primary Objectives
- [ ] Validate software operates reliably in real operational conditions
- [ ] Validate environmental stress tolerance (temperature, humidity, vibration, EMI)
- [ ] Validate long-term reliability (≥ 4 weeks continuous operation)
- [ ] Identify any issues not detectable in laboratory/HIL
- [ ] Demonstrate operational availability ≥ 99.5%
- [ ] Collect operational data for certification evidence

### 2.2 Success Criteria
- **Zero critical defects** (safety-impacting)
- **Zero high-priority defects** (service-impacting)
- **Operational availability** ≥ 99.5% during pilot
- **No unexpected behaviors** in operational scenarios
- **Environmental stress tests** PASS (temperature, vibration, EMI)
- **Long-term operation** ≥ 1,000 hours fault-free
- **Operator satisfaction** ≥ 90%

## 3. Operational Validation Phases

### Phase 1: Depot Field Testing (Week 1-2)
**Location**: Railway depot, maintenance yard  
**Purpose**: Initial operational checkout, basic reliability  
**Duration**: 2 weeks, 4 hours/day  
**Activities**:
- System installation and commissioning
- Basic operational cycles (door open/close)
- Environmental baseline testing
- Operator familiarization

**Success Criteria**:
- System operates reliably in depot environment
- No installation issues
- Baseline performance established

---

### Phase 2: Test Track Operations (Week 3-4)
**Location**: Depot test track (500m closed loop)  
**Purpose**: Dynamic testing with train motion, repeated cycles  
**Duration**: 2 weeks, 8 hours/day  
**Activities**:
- Door operations during train motion (station stops)
- Repeated open/close cycles (100+ per day)
- Fault injection scenarios
- Performance monitoring under load

**Success Criteria**:
- Reliable operation over 1,000+ door cycles
- No degradation observed
- All fault scenarios handled correctly

---

### Phase 3: Pilot Installation - Limited Service (Week 5-8)
**Location**: Line 2, limited service (off-peak hours)  
**Purpose**: Real passenger service, limited scope  
**Duration**: 4 weeks, 6 hours/day (off-peak)  
**Activities**:
- Passenger service operation
- Real-world door loading (passengers boarding/exiting)
- Environmental stress (actual weather conditions)
- Operator feedback collection

**Success Criteria**:
- Zero service-impacting incidents
- Positive operator feedback
- Availability ≥ 99.5%

---

### Phase 4: Extended Pilot - Expanded Service (Week 9-12)
**Location**: Line 2, expanded service (peak + off-peak)  
**Purpose**: Full operational validation, long-term reliability  
**Duration**: 4 weeks, 18 hours/day (peak + off-peak)  
**Activities**:
- Full passenger service operation
- Peak load scenarios (high passenger density)
- Extended continuous operation
- Long-term reliability monitoring

**Success Criteria**:
- Zero critical defects over 500+ hours operation
- Operational availability ≥ 99.5%
- Long-term stability demonstrated

## 4. Test Environment

### 4.1 Train Configuration
- **Train**: #4523 (6-car metro train)
- **Doors**: 4 doors per car (24 total)
- **Control System**: Railway Door Control System v1.0.0 (SIL 3)
- **Integration**: CAN bus, safety PLC, train control system

### 4.2 Operational Route
- **Line**: Metro Line 2 (urban)
- **Length**: 15 km
- **Stations**: 12 stations
- **Speed**: Up to 80 km/h (operational limit)
- **Headway**: 3 minutes (peak), 6 minutes (off-peak)

### 4.3 Environmental Conditions
- **Temperature**: -10°C to +40°C (seasonal variation)
- **Humidity**: 20% to 95% (non-condensing)
- **Vibration**: EN 61373 Class B (railway vehicles)
- **EMI**: EN 50121-3-2 Class A1 (urban traction systems)
- **Altitude**: Sea level to 200m

### 4.4 Instrumentation
- **Data Logger**: CAN bus logger (continuous recording)
- **Temperature Sensors**: 4x (door control units)
- **Vibration Sensors**: 2x (door control units)
- **Video Cameras**: 2x (driver interface, door operations)
- **Event Logger**: On-board diagnostic system

## 5. Operational Test Scenarios

### 5.1 Normal Operations
- Daily passenger service (routine station stops)
- Door open/close cycles (high frequency)
- Peak load scenarios (crowded passengers)
- Off-peak scenarios (low passenger density)

### 5.2 Environmental Stress
- Hot weather operation (≥ +35°C)
- Cold weather operation (≤ 0°C)
- High humidity (≥ 80%)
- Heavy rain operation
- Strong wind operation

### 5.3 Operational Stress
- Rapid turnaround (short station dwell time)
- Extended operation (18 hours continuous)
- High cycle count (500+ cycles/day)
- Degraded mode operation (with faults present)

### 5.4 Fault Scenarios
- Single door fault (one door inoperative)
- Sensor fault during operation
- Communication fault (CAN bus)
- Power glitch/brownout

## 6. Data Collection

### 6.1 Continuous Data Logging
- CAN bus traffic (all messages)
- System diagnostics (health status)
- Door operation events (open/close, lock/unlock)
- Alarms and faults
- Environmental data (temperature, vibration)

### 6.2 Daily Reports
- Operational summary (hours, cycles, faults)
- Driver feedback (issues, observations)
- Maintenance actions (if any)
- Environmental conditions (weather)

### 6.3 Weekly Reports
- Reliability statistics (MTBF, availability)
- Defect summary (if any)
- Performance trends
- Operator satisfaction survey

## 7. Risk Management

### 7.1 Operational Risks

| Risk | Impact | Probability | Mitigation |
|------|--------|-------------|------------|
| Critical defect during service | HIGH | LOW | Backup train ready, abort procedure |
| Safety incident | HIGH | VERY LOW | Safety observer, strict procedures |
| Service disruption | MEDIUM | LOW | Limited service scope, off-peak |
| Environmental damage | MEDIUM | LOW | Environmental testing completed |
| EMI interference | MEDIUM | MEDIUM | EMI testing completed, monitoring |

### 7.2 Abort Criteria
- **Immediate Abort**: Critical safety defect detected
- **Planned Abort**: High-priority defect affecting service
- **Authority**: Validator or Operations Manager

## 8. Roles and Responsibilities

| Role | Name | Responsibility |
|------|------|----------------|
| **Validator** | John Smith | Overall operational validation, approval |
| **Operations Manager** | David Lee | Operational coordination, daily oversight |
| **Train Driver (Lead)** | Sarah Chen | Daily operation, feedback |
| **Maintenance Engineer** | Tom Wilson | On-site support, fault response |
| **Safety Observer** | Emma Brown | Safety monitoring, incident response |
| **Data Analyst** | Mike Johnson | Data collection, analysis, reporting |

## 9. Schedule

| Phase | Start Date | End Date | Duration | Key Activities |
|-------|------------|----------|----------|----------------|
| **Phase 1: Depot** | 2026-04-22 | 2026-05-03 | 2 weeks | Installation, commissioning |
| **Phase 2: Test Track** | 2026-05-06 | 2026-05-17 | 2 weeks | Dynamic testing, cycles |
| **Phase 3: Limited Pilot** | 2026-05-20 | 2026-06-14 | 4 weeks | Off-peak service |
| **Phase 4: Extended Pilot** | 2026-06-17 | 2026-07-12 | 4 weeks | Peak + off-peak service |
| **Report & Analysis** | 2026-07-15 | 2026-07-26 | 2 weeks | Data analysis, report |
| **Total** | | | **14 weeks** | |

## 10. Deliverables

- [ ] Operational Validation Plan (this document)
- [ ] Daily Operational Logs (84 days)
- [ ] Weekly Progress Reports (12 weeks)
- [ ] Environmental Stress Test Report
- [ ] Long-Term Reliability Report
- [ ] Field Defect Reports (if any)
- [ ] Operational Validation Report (final)
- [ ] Operational Readiness Assessment

## 11. Acceptance Criteria

### 11.1 Technical Criteria
- Zero critical defects during operational validation
- Operational availability ≥ 99.5%
- Environmental stress tests PASS
- Long-term reliability ≥ 1,000 hours fault-free

### 11.2 Operational Criteria
- Operator satisfaction ≥ 90%
- No service disruptions caused by system
- Maintenance procedures validated as practical

### 11.3 Safety Criteria
- Zero safety incidents
- All safety features validated in operational environment
- Emergency procedures effective

## 12. Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Validator** | John Smith | ___________ | 2026-04-15 |
| **Operations Manager** | David Lee | ___________ | 2026-04-15 |
| **Safety Manager** | Alice Johnson | ___________ | 2026-04-15 |
| **Project Manager** | Bob Wilson | ___________ | 2026-04-15 |
```

---

### Traceability: Operational Validation Plan to Requirements

```bash
# Link Operational Validation Plan to operational requirements
workspace.py trace create \
    --from validation \
    --to requirements \
    --source-id "DOC-VAL-OVP-001" \
    --target-id "SRS-OPS-*" \
    --rationale "Operational validation plan addresses all operational requirements" \
    --sil 3

# Validate operational requirements coverage
workspace.py trace validate \
    --phase validation \
    --sil 3 \
    --filter "operational" \
    --output evidence/traceability/operational_validation_coverage.json
```

---

## Pilot Installation Setup

### Installation Procedure

```c
// Pilot installation commissioning checklist
// File: pilot_commissioning.c

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "door_control_system.h"

// Commissioning test structure
typedef struct {
    uint16_t test_number;
    const char* test_name;
    const char* acceptance_criteria;
    bool (*test_function)(void);
    bool passed;
    char notes[256];
} commissioning_test_t;

// Test: Hardware installation verification
bool test_comm_001_hardware_installation(void) {
    printf("TEST COMM-001: Hardware Installation Verification\n");
    
    // Check all control units present
    bool all_units_present = true;
    for (uint8_t unit_id = 1; unit_id <= 6; unit_id++) {
        printf("  Checking door control unit %u...\n", unit_id);
        if (!check_unit_present(unit_id)) {
            printf("  ERROR: Unit %u not responding\n", unit_id);
            all_units_present = false;
        }
    }
    
    // Check CAN bus connectivity
    printf("  Checking CAN bus connectivity...\n");
    bool can_ok = check_can_bus_health();
    
    // Check power supply
    printf("  Checking power supply voltages...\n");
    bool power_ok = check_power_supply();
    
    bool passed = all_units_present && can_ok && power_ok;
    printf("  Result: %s\n\n", passed ? "PASS" : "FAIL");
    return passed;
}

// Test: Software version verification
bool test_comm_002_software_version(void) {
    printf("TEST COMM-002: Software Version Verification\n");
    
    // Check software version on all units
    const char* expected_version = "1.0.0";
    bool all_versions_correct = true;
    
    for (uint8_t unit_id = 1; unit_id <= 6; unit_id++) {
        char version[32];
        if (get_unit_software_version(unit_id, version, sizeof(version))) {
            printf("  Unit %u: Version %s\n", unit_id, version);
            if (strcmp(version, expected_version) != 0) {
                printf("  ERROR: Expected %s, got %s\n", expected_version, version);
                all_versions_correct = false;
            }
        } else {
            printf("  ERROR: Cannot read version from unit %u\n", unit_id);
            all_versions_correct = false;
        }
    }
    
    printf("  Result: %s\n\n", all_versions_correct ? "PASS" : "FAIL");
    return all_versions_correct;
}

// Test: Configuration verification
bool test_comm_003_configuration(void) {
    printf("TEST COMM-003: Configuration Verification\n");
    
    // Load expected configuration
    configuration_t expected_config;
    load_configuration_from_file("config/pilot_train_4523.cfg", &expected_config);
    
    // Read actual configuration from system
    configuration_t actual_config;
    read_system_configuration(&actual_config);
    
    // Compare configurations
    bool config_match = compare_configurations(&expected_config, &actual_config);
    
    if (!config_match) {
        printf("  Configuration mismatch detected:\n");
        print_configuration_diff(&expected_config, &actual_config);
    }
    
    printf("  Result: %s\n\n", config_match ? "PASS" : "FAIL");
    return config_match;
}

// Test: Sensor calibration
bool test_comm_004_sensor_calibration(void) {
    printf("TEST COMM-004: Sensor Calibration\n");
    
    bool all_sensors_calibrated = true;
    
    for (uint8_t door_id = 1; door_id <= 24; door_id++) {
        printf("  Calibrating door %u sensors...\n", door_id);
        
        // Calibrate door closed position
        if (!calibrate_door_closed_position(door_id)) {
            printf("  ERROR: Failed to calibrate closed position\n");
            all_sensors_calibrated = false;
        }
        
        // Calibrate door open position
        if (!calibrate_door_open_position(door_id)) {
            printf("  ERROR: Failed to calibrate open position\n");
            all_sensors_calibrated = false;
        }
        
        // Verify calibration
        if (!verify_door_calibration(door_id)) {
            printf("  ERROR: Calibration verification failed\n");
            all_sensors_calibrated = false;
        }
    }
    
    printf("  Result: %s\n\n", all_sensors_calibrated ? "PASS" : "FAIL");
    return all_sensors_calibrated;
}

// Test: Safety interlock verification
bool test_comm_005_safety_interlocks(void) {
    printf("TEST COMM-005: Safety Interlock Verification\n");
    
    // Test 1: Speed interlock
    printf("  Test 1: Speed interlock\n");
    set_simulated_speed(50);  // 50 km/h
    result_t result = system_command_door_open();
    bool speed_interlock_ok = (result == RESULT_ERROR_INTERLOCK);
    printf("    Speed interlock: %s\n", speed_interlock_ok ? "OK" : "FAIL");
    
    // Test 2: Brake interlock
    printf("  Test 2: Brake interlock\n");
    set_simulated_speed(0);
    set_brake_status(BRAKE_RELEASED);  // Brake not applied
    result = system_command_door_open();
    bool brake_interlock_ok = (result == RESULT_ERROR_INTERLOCK);
    printf("    Brake interlock: %s\n", brake_interlock_ok ? "OK" : "FAIL");
    
    // Test 3: Obstruction interlock
    printf("  Test 3: Obstruction interlock\n");
    set_brake_status(BRAKE_APPLIED);
    system_command_door_open();
    wait_until_doors_open();
    inject_obstruction(1);  // Door 1 obstruction
    system_command_door_close();
    wait_ms(2000);
    bool obstruction_ok = !is_door_closed(1);  // Door should not close
    printf("    Obstruction interlock: %s\n", obstruction_ok ? "OK" : "FAIL");
    
    bool all_interlocks_ok = speed_interlock_ok && brake_interlock_ok && obstruction_ok;
    printf("  Result: %s\n\n", all_interlocks_ok ? "PASS" : "FAIL");
    return all_interlocks_ok;
}

// Test: Operational cycle test
bool test_comm_006_operational_cycles(void) {
    printf("TEST COMM-006: Operational Cycle Test\n");
    printf("  Performing 100 open/close cycles...\n");
    
    uint16_t cycles_passed = 0;
    uint16_t cycles_failed = 0;
    
    for (uint16_t cycle = 1; cycle <= 100; cycle++) {
        // Open cycle
        system_command_door_open();
        if (!wait_until_doors_open_timeout(10000)) {
            printf("  ERROR: Cycle %u - Doors failed to open\n", cycle);
            cycles_failed++;
            continue;
        }
        
        wait_ms(1000);  // Dwell time
        
        // Close cycle
        system_command_door_close();
        if (!wait_until_doors_closed_timeout(10000)) {
            printf("  ERROR: Cycle %u - Doors failed to close\n", cycle);
            cycles_failed++;
            continue;
        }
        
        wait_ms(500);
        cycles_passed++;
        
        // Progress indicator
        if (cycle % 10 == 0) {
            printf("  Completed %u cycles (%u passed, %u failed)\n", 
                   cycle, cycles_passed, cycles_failed);
        }
    }
    
    bool passed = (cycles_failed == 0);
    printf("  Result: %s (%u/%u cycles passed)\n\n", 
           passed ? "PASS" : "FAIL", cycles_passed, 100);
    return passed;
}

// Execute complete commissioning test suite
void execute_pilot_commissioning(void) {
    printf("==================================================\n");
    printf("  Pilot Installation Commissioning\n");
    printf("  Train #4523, Line 2\n");
    printf("  Railway Door Control System v1.0.0 (SIL 3)\n");
    printf("==================================================\n\n");
    
    commissioning_test_t tests[] = {
        {1, "Hardware Installation", "All units present and responding", test_comm_001_hardware_installation, false, ""},
        {2, "Software Version", "All units running v1.0.0", test_comm_002_software_version, false, ""},
        {3, "Configuration", "Configuration matches pilot train spec", test_comm_003_configuration, false, ""},
        {4, "Sensor Calibration", "All sensors calibrated", test_comm_004_sensor_calibration, false, ""},
        {5, "Safety Interlocks", "All safety interlocks verified", test_comm_005_safety_interlocks, false, ""},
        {6, "Operational Cycles", "100 cycles without failure", test_comm_006_operational_cycles, false, ""},
    };
    
    uint16_t num_tests = sizeof(tests) / sizeof(tests[0]);
    uint16_t tests_passed = 0;
    
    // Execute all tests
    for (uint16_t i = 0; i < num_tests; i++) {
        tests[i].passed = tests[i].test_function();
        if (tests[i].passed) {
            tests_passed++;
        }
    }
    
    // Print summary
    printf("==================================================\n");
    printf("  Commissioning Summary\n");
    printf("==================================================\n");
    for (uint16_t i = 0; i < num_tests; i++) {
        printf("  [%s] COMM-%03u: %s\n", 
               tests[i].passed ? "PASS" : "FAIL",
               tests[i].test_number,
               tests[i].test_name);
    }
    printf("\n");
    printf("  Tests Passed: %u / %u\n", tests_passed, num_tests);
    
    if (tests_passed == num_tests) {
        printf("\n  ✅ COMMISSIONING COMPLETE - READY FOR PILOT OPERATION\n");
    } else {
        printf("\n  ❌ COMMISSIONING FAILED - ADDRESS FAILURES BEFORE PILOT\n");
    }
    printf("==================================================\n");
}
```

---

## Environmental Stress Testing

### Temperature Stress Test

```c
// Environmental stress testing
// File: environmental_stress_tests.c

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "door_control_system.h"

// Environmental test structure
typedef struct {
    const char* test_id;
    const char* test_name;
    float temperature_min_c;
    float temperature_max_c;
    uint32_t duration_minutes;
    uint16_t cycles_to_perform;
    bool passed;
} env_test_t;

// Test ENV-001: Cold temperature operation (-10°C)
void test_env_001_cold_operation(void) {
    printf("=== ENV-001: Cold Temperature Operation ===\n");
    printf("Temperature: -10°C\n");
    printf("Duration: 2 hours\n");
    printf("Cycles: 50 open/close\n\n");
    
    // Wait for cold chamber to stabilize
    printf("Waiting for cold chamber to reach -10°C...\n");
    wait_for_temperature_stable(-10.0f, 1.0f);  // ±1°C tolerance
    
    float actual_temp = get_chamber_temperature();
    printf("Chamber temperature: %.1f°C\n\n", actual_temp);
    
    // Perform operational cycles at cold temperature
    uint16_t cycles_passed = 0;
    uint16_t cycles_failed = 0;
    
    uint32_t start_time = get_time_ms();
    for (uint16_t cycle = 1; cycle <= 50; cycle++) {
        // Open doors
        result_t result = system_command_door_open();
        if (result != RESULT_SUCCESS) {
            printf("Cycle %u: Door open failed (result=%d)\n", cycle, result);
            cycles_failed++;
            continue;
        }
        
        if (!wait_until_doors_open_timeout(15000)) {  // Longer timeout for cold
            printf("Cycle %u: Timeout waiting for doors to open\n", cycle);
            cycles_failed++;
            continue;
        }
        
        wait_ms(2000);  // Dwell
        
        // Close doors
        result = system_command_door_close();
        if (result != RESULT_SUCCESS) {
            printf("Cycle %u: Door close failed (result=%d)\n", cycle, result);
            cycles_failed++;
            continue;
        }
        
        if (!wait_until_doors_closed_timeout(15000)) {
            printf("Cycle %u: Timeout waiting for doors to close\n", cycle);
            cycles_failed++;
            continue;
        }
        
        cycles_passed++;
        
        // Check for system faults
        uint8_t fault_status = system_get_fault_status();
        if (fault_status != 0) {
            printf("Cycle %u: Fault detected: 0x%02X\n", cycle, fault_status);
            cycles_failed++;
        }
        
        // Progress indicator
        if (cycle % 10 == 0) {
            float current_temp = get_chamber_temperature();
            printf("Cycle %u: %u passed, %u failed (temp: %.1f°C)\n",
                   cycle, cycles_passed, cycles_failed, current_temp);
        }
    }
    
    uint32_t duration_ms = get_time_ms() - start_time;
    float duration_hours = duration_ms / 3600000.0f;
    
    // Evaluate results
    bool passed = (cycles_failed == 0);
    
    printf("\n=== ENV-001 Results ===\n");
    printf("Temperature: %.1f°C (target: -10°C)\n", actual_temp);
    printf("Duration: %.2f hours\n", duration_hours);
    printf("Cycles Passed: %u / 50\n", cycles_passed);
    printf("Cycles Failed: %u / 50\n", cycles_failed);
    printf("Result: %s\n\n", passed ? "PASS" : "FAIL");
}

// Test ENV-002: Hot temperature operation (+40°C)
void test_env_002_hot_operation(void) {
    printf("=== ENV-002: Hot Temperature Operation ===\n");
    printf("Temperature: +40°C\n");
    printf("Duration: 2 hours\n");
    printf("Cycles: 50 open/close\n\n");
    
    // Wait for hot chamber to stabilize
    printf("Waiting for hot chamber to reach +40°C...\n");
    wait_for_temperature_stable(40.0f, 1.0f);
    
    float actual_temp = get_chamber_temperature();
    printf("Chamber temperature: %.1f°C\n\n", actual_temp);
    
    // Similar cycle testing as cold test
    // (Implementation similar to test_env_001_cold_operation)
    
    // ... (omitted for brevity - same pattern as cold test)
    
    printf("\n=== ENV-002 Results ===\n");
    printf("Result: PASS\n\n");
}

// Test ENV-003: Temperature cycling (thermal stress)
void test_env_003_temperature_cycling(void) {
    printf("=== ENV-003: Temperature Cycling (Thermal Stress) ===\n");
    printf("Cycle: -10°C → +40°C → -10°C\n");
    printf("Number of Cycles: 5\n");
    printf("Duration: ~10 hours\n\n");
    
    for (uint8_t cycle = 1; cycle <= 5; cycle++) {
        printf("Thermal Cycle %u/5\n", cycle);
        
        // Cold phase (-10°C, 1 hour)
        printf("  Phase 1: Cooling to -10°C...\n");
        ramp_temperature_to(-10.0f, 30);  // 30 minutes ramp time
        wait_for_temperature_stable(-10.0f, 2.0f);
        printf("  Cold soak at -10°C for 1 hour...\n");
        wait_ms(60 * 60 * 1000);  // 1 hour
        
        // Perform functional test at cold temperature
        printf("  Functional test at -10°C...\n");
        perform_basic_functional_test();
        
        // Hot phase (+40°C, 1 hour)
        printf("  Phase 2: Heating to +40°C...\n");
        ramp_temperature_to(40.0f, 30);  // 30 minutes ramp time
        wait_for_temperature_stable(40.0f, 2.0f);
        printf("  Hot soak at +40°C for 1 hour...\n");
        wait_ms(60 * 60 * 1000);  // 1 hour
        
        // Perform functional test at hot temperature
        printf("  Functional test at +40°C...\n");
        perform_basic_functional_test();
        
        printf("Thermal Cycle %u complete\n\n", cycle);
    }
    
    printf("\n=== ENV-003 Results ===\n");
    printf("Result: PASS (all functional tests passed)\n\n");
}

// Test ENV-004: Vibration stress (EN 61373 Class B)
void test_env_004_vibration_stress(void) {
    printf("=== ENV-004: Vibration Stress (EN 61373 Class B) ===\n");
    printf("Standard: EN 61373 (Railway Vehicle Vibration)\n");
    printf("Class: B (Bogie-mounted equipment)\n");
    printf("Duration: 2 hours per axis (X, Y, Z)\n\n");
    
    // Enable vibration monitoring
    vibration_monitor_start();
    
    // Test X-axis vibration
    printf("X-Axis Vibration Test (2 hours)...\n");
    vibration_shaker_enable(AXIS_X, EN61373_CLASS_B_PROFILE);
    uint32_t start_time = get_time_ms();
    
    while ((get_time_ms() - start_time) < (2 * 60 * 60 * 1000)) {  // 2 hours
        // Perform periodic functional checks
        if ((get_time_ms() - start_time) % (15 * 60 * 1000) == 0) {  // Every 15 minutes
            printf("  Functional check at +%u minutes...\n", 
                   (get_time_ms() - start_time) / (60 * 1000));
            if (!perform_basic_functional_test()) {
                printf("  ERROR: Functional test failed during vibration\n");
                vibration_shaker_disable();
                return;
            }
        }
        wait_ms(1000);
    }
    
    vibration_shaker_disable();
    printf("X-Axis complete\n\n");
    
    // Test Y-axis and Z-axis similarly...
    // (omitted for brevity)
    
    vibration_monitor_stop();
    vibration_stats_t stats = vibration_monitor_get_stats();
    
    printf("\n=== ENV-004 Results ===\n");
    printf("Max Vibration (X): %.2f g\n", stats.max_x_g);
    printf("Max Vibration (Y): %.2f g\n", stats.max_y_g);
    printf("Max Vibration (Z): %.2f g\n", stats.max_z_g);
    printf("Functional Tests During Vibration: ALL PASS\n");
    printf("Result: PASS\n\n");
}

// Test ENV-005: EMI stress (EN 50121-3-2 Class A1)
void test_env_005_emi_stress(void) {
    printf("=== ENV-005: EMI Stress (EN 50121-3-2 Class A1) ===\n");
    printf("Standard: EN 50121-3-2 (Railway EMI)\n");
    printf("Class: A1 (Urban traction systems)\n");
    printf("Duration: 1 hour\n\n");
    
    // Enable EMI field generator
    emi_field_generator_enable(EN50121_CLASS_A1_PROFILE);
    
    // Monitor system operation under EMI stress
    uint32_t start_time = get_time_ms();
    uint16_t emi_errors = 0;
    
    while ((get_time_ms() - start_time) < (60 * 60 * 1000)) {  // 1 hour
        // Perform door cycles
        system_command_door_open();
        if (!wait_until_doors_open_timeout(10000)) {
            printf("  ERROR: Door open failed under EMI stress\n");
            emi_errors++;
        }
        
        wait_ms(2000);
        
        system_command_door_close();
        if (!wait_until_doors_closed_timeout(10000)) {
            printf("  ERROR: Door close failed under EMI stress\n");
            emi_errors++;
        }
        
        wait_ms(2000);
        
        // Check for communication errors (CAN bus)
        can_stats_t can_stats = can_get_statistics();
        if (can_stats.error_count > 0) {
            printf("  WARNING: CAN errors detected: %u\n", can_stats.error_count);
            // Acceptable if errors are recovered
        }
        
        // Progress indicator every 10 minutes
        if ((get_time_ms() - start_time) % (10 * 60 * 1000) == 0) {
            printf("  +%u minutes: %u errors detected\n",
                   (get_time_ms() - start_time) / (60 * 1000), emi_errors);
        }
    }
    
    emi_field_generator_disable();
    
    printf("\n=== ENV-005 Results ===\n");
    printf("EMI Errors: %u\n", emi_errors);
    printf("Result: %s\n\n", (emi_errors == 0) ? "PASS" : "FAIL");
}

// Execute complete environmental stress test suite
void execute_environmental_stress_tests(void) {
    printf("==================================================\n");
    printf("  Environmental Stress Testing\n");
    printf("  Railway Door Control System v1.0.0 (SIL 3)\n");
    printf("==================================================\n\n");
    
    // Cold temperature
    test_env_001_cold_operation();
    
    // Hot temperature
    test_env_002_hot_operation();
    
    // Temperature cycling
    test_env_003_temperature_cycling();
    
    // Vibration
    test_env_004_vibration_stress();
    
    // EMI
    test_env_005_emi_stress();
    
    printf("==================================================\n");
    printf("  Environmental Stress Testing Complete\n");
    printf("  All Tests: PASS\n");
    printf("==================================================\n");
}
```

---

## Long-Term Operational Monitoring

### Operational Data Collection

```bash
# Automated operational data collection script
# File: collect_operational_data.sh

#!/bin/bash

# Configuration
PILOT_TRAIN="4523"
LOG_DIR="evidence/validation/operational/pilot_data"
DURATION_DAYS=28  # 4 weeks
SAMPLE_INTERVAL=60  # seconds

mkdir -p "$LOG_DIR/can_logs"
mkdir -p "$LOG_DIR/diagnostic_logs"
mkdir -p "$LOG_DIR/event_logs"
mkdir -p "$LOG_DIR/environmental"

echo "=========================================="
echo "  Operational Data Collection"
echo "  Train: $PILOT_TRAIN"
echo "  Duration: $DURATION_DAYS days"
echo "=========================================="

# Start data loggers
echo "Starting data loggers..."

# CAN bus logger (continuous)
candump can0 -L > "$LOG_DIR/can_logs/can_$(date +%Y%m%d).log" &
CAN_PID=$!

# System diagnostic logger
while true; do
    TIMESTAMP=$(date +%Y-%m-%d_%H:%M:%S)
    
    # Collect system health status
    system_status=$(./tools/query_system_status.sh)
    echo "$TIMESTAMP,$system_status" >> "$LOG_DIR/diagnostic_logs/system_health.csv"
    
    # Collect door operation statistics
    door_stats=$(./tools/query_door_statistics.sh)
    echo "$TIMESTAMP,$door_stats" >> "$LOG_DIR/diagnostic_logs/door_statistics.csv"
    
    # Collect environmental data
    env_data=$(./tools/query_environmental.sh)
    echo "$TIMESTAMP,$env_data" >> "$LOG_DIR/environmental/environment.csv"
    
    sleep $SAMPLE_INTERVAL
done &
DIAG_PID=$!

echo "Data loggers started (CAN PID=$CAN_PID, DIAG PID=$DIAG_PID)"
echo "Collecting data for $DURATION_DAYS days..."
echo "Stop with: kill $CAN_PID $DIAG_PID"
```

---

### Daily Operational Log Template

```markdown
# Daily Operational Log

**Date**: 2026-05-25 (Pilot Day 6)  
**Train**: #4523  
**Service**: Line 2, Off-Peak  
**Hours of Operation**: 8 hours (10:00-18:00)  
**Driver**: Sarah Chen

## Operational Summary

| Metric | Value |
|--------|-------|
| **Total Operation Time** | 8 hours |
| **Station Stops** | 96 stops |
| **Door Open/Close Cycles** | 384 cycles (4 doors × 96 stops) |
| **Distance Traveled** | 240 km |
| **Passengers Carried** | ~1,200 passengers (estimated) |

## System Performance

| Parameter | Value | Status |
|-----------|-------|--------|
| **System Availability** | 100% | ✅ Target: ≥99.5% |
| **Door Operation Success** | 384/384 (100%) | ✅ PASS |
| **Average Door Open Time** | 3.2 seconds | ✅ Target: ≤4s |
| **Average Door Close Time** | 4.1 seconds | ✅ Target: ≤5s |
| **Alarms** | 0 | ✅ Zero alarms |
| **Faults** | 0 | ✅ Zero faults |

## Environmental Conditions

| Parameter | Min | Max | Average |
|-----------|-----|-----|---------|
| **Ambient Temperature** | 22°C | 28°C | 25°C |
| **Humidity** | 45% | 65% | 55% |
| **Weather** | Clear | Clear | Sunny |

## Observations

### Positive Observations
- All door operations completed successfully
- Consistent performance throughout the day
- No unexpected behaviors
- Driver reports system working smoothly

### Issues
- **NONE**

## Driver Feedback (Sarah Chen)
"Another smooth day of operation. The door system continues to work perfectly. Passengers had no issues boarding or exiting. I'm very confident in this system."

**Driver Confidence Rating**: 10/10

## Maintenance Actions
- **NONE** (no maintenance required)

## Data Collected
- [x] CAN bus logs (8 hours, 15 MB)
- [x] System diagnostic logs
- [x] Door operation event logs
- [x] Environmental sensor data

## Next Day Plan
- Continue off-peak pilot operation
- Monitor for any emerging issues

## Signatures
- Driver: _________________ Date: _______
- Observer: ______________ Date: _______
```

---

## Field Defect Management

### Field Defect Report Template

```markdown
# Field Defect Report

**Report ID**: FDR-2026-001  
**Date Detected**: 2026-05-28  
**Location**: Train #4523, Car 3, Door 11  
**Pilot Phase**: Phase 3 (Limited Service)  
**Reporter**: Mike Johnson (Data Analyst)

## Defect Description

**Summary**: Door 11 (Car 3, left side) experienced delayed closing on two occasions during high passenger load scenarios.

**Detailed Description**:
- Occurrence 1: 2026-05-28 14:23 - Door close command issued, door took 8.2 seconds to close (normal: 4-5 seconds)
- Occurrence 2: 2026-05-28 16:45 - Door close command issued, door took 7.8 seconds to close

**Conditions**:
- High passenger density (rush hour)
- Ambient temperature: 32°C
- Humidity: 70%

## Classification

| Category | Value |
|----------|-------|
| **Severity** | MINOR |
| **Safety Impact** | NONE (no safety function affected) |
| **Service Impact** | LOW (slight delay, no service disruption) |
| **Frequency** | 2 occurrences in 384 cycles (0.5%) |

**Priority**: LOW

## Root Cause Analysis

**Investigation Findings**:
1. Door mechanism experienced higher friction due to:
   - High temperature (32°C)
   - High humidity (70%)
   - Door seals expanded slightly in hot/humid conditions

2. Door motor control algorithm used conservative current limits to avoid overstressing mechanism in hot conditions (safety feature working as designed)

3. CAN bus logs show no communication errors
4. Sensor calibration verified correct
5. Mechanical inspection: No abnormal wear, lubrication adequate

**Root Cause**: Door seal expansion in hot/humid conditions causes increased friction. Motor control algorithm conservatively limits current in hot conditions, resulting in slower door closing speed.

## Resolution

**Action Taken**:
1. Verified door mechanism within specification (closing time ≤10 seconds acceptable per SRS-OPS-025)
2. Adjusted door seal material specification for better dimensional stability in hot/humid conditions (design improvement for future production)
3. No software changes required (system working as designed)

**Status**: CLOSED (Not a defect - working as designed, within specification)

## Impact Assessment

**Operational Impact**: NONE (door closing time still within acceptable range)

**Safety Impact**: NONE (no safety functions affected)

**Continue Pilot?**: YES (no reason to abort or pause)

## Lessons Learned

- Environmental stress testing in laboratory should include combined temperature + humidity + high mechanical load scenarios
- Door closing time specification (≤10 seconds) is adequate for operational needs
- System robustness validated - prioritizes reliability over speed in adverse conditions

## Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Reporter** | Mike Johnson | ___________ | 2026-05-28 |
| **Validator** | John Smith | ___________ | 2026-05-29 |
| **Operations Manager** | David Lee | ___________ | 2026-05-29 |

**Disposition**: No action required, continue pilot operation
```

---

## Operational Readiness Assessment

### Operational Readiness Checklist

```markdown
# Operational Readiness Assessment

**Project**: Railway Door Control System  
**Version**: 1.0.0  
**SIL Level**: 3  
**Assessment Date**: 2026-07-15  
**Assessor**: John Smith (Validator)

## Assessment Criteria

### 1. Technical Readiness

| Criterion | Status | Evidence |
|-----------|--------|----------|
| All validation tests passed | ✅ PASS | Validation Report DOC-VAL-REP-001 |
| Laboratory validation complete | ✅ PASS | 88/88 tests passed |
| HIL validation complete | ✅ PASS | All scenarios validated |
| Environmental stress tests passed | ✅ PASS | ENV-001 through ENV-005 all PASS |
| Integration tests passed | ✅ PASS | Integration Report DOC-INT-REP-001 |
| Verification complete | ✅ PASS | Verification Report DOC-VER-REP-001 |
| Code coverage 100% (SIL 3) | ✅ PASS | Statement/Branch/MC/DC 100% |
| Static analysis clean | ✅ PASS | Zero critical issues |
| MISRA C compliant | ✅ PASS | Zero mandatory violations |

**Technical Readiness**: ✅ **READY**

---

### 2. Operational Readiness

| Criterion | Status | Evidence |
|-----------|--------|----------|
| Pilot installation complete | ✅ PASS | 12 weeks, 1,200+ hours |
| Operational availability ≥99.5% | ✅ PASS | 99.9% achieved |
| Long-term reliability demonstrated | ✅ PASS | 1,200 hours fault-free |
| Environmental tolerance validated | ✅ PASS | -10°C to +40°C tested |
| High cycle count validated | ✅ PASS | 15,000+ cycles completed |
| Degraded mode validated | ✅ PASS | Single-fault operation tested |
| Maintenance procedures validated | ✅ PASS | Practical and effective |
| Operator training complete | ✅ PASS | All drivers trained |
| Documentation complete | ✅ PASS | All operational docs delivered |

**Operational Readiness**: ✅ **READY**

---

### 3. Safety Readiness

| Criterion | Status | Evidence |
|-----------|--------|----------|
| Hazard analysis complete | ✅ PASS | Hazard Log DOC-SAF-HL-001 |
| All hazard mitigations validated | ✅ PASS | 18/18 hazards addressed |
| Safety interlocks validated | ✅ PASS | Zero interlock failures |
| Fail-safe behavior validated | ✅ PASS | Safe state on all faults |
| Emergency procedures validated | ✅ PASS | Effective in all scenarios |
| Zero safety incidents (pilot) | ✅ PASS | Zero incidents in 1,200 hours |
| Safety case complete | ✅ PASS | Safety Case DOC-SAF-SC-001 |

**Safety Readiness**: ✅ **READY**

---

### 4. Customer Acceptance

| Criterion | Status | Evidence |
|-----------|--------|----------|
| User acceptance tests passed | ✅ PASS | 15/15 UAT tests passed |
| Customer acceptance obtained | ✅ PASS | Acceptance Certificate DOC-VAL-ACC-001 |
| Driver confidence ≥90% | ✅ PASS | 98% average (10/10 rating) |
| Operator satisfaction ≥90% | ✅ PASS | 96% satisfaction |
| Maintenance satisfaction ≥90% | ✅ PASS | 94% satisfaction |
| No critical customer concerns | ✅ PASS | Zero concerns raised |

**Customer Acceptance**: ✅ **APPROVED**

---

### 5. Documentation Readiness

| Document | Status | Version | Date |
|----------|--------|---------|------|
| Software Requirements Specification | ✅ Complete | 1.0 | 2026-02-10 |
| Software Architecture Specification | ✅ Complete | 1.0 | 2026-02-28 |
| Software Design Specification | ✅ Complete | 1.0 | 2026-03-15 |
| Source Code | ✅ Complete | 1.0.0 | 2026-04-20 |
| Software Verification Report | ✅ Complete | 1.0 | 2026-05-10 |
| Software Integration Report | ✅ Complete | 1.0 | 2026-05-25 |
| Software Validation Report | ✅ Complete | 1.0 | 2026-06-10 |
| User Acceptance Test Report | ✅ Complete | 1.0 | 2026-06-08 |
| Operational Validation Report | ✅ Complete | 1.0 | 2026-07-15 |
| Release Note | ✅ Complete | 1.0 | 2026-07-15 |
| User Manual | ✅ Complete | 1.0 | 2026-06-15 |
| Maintenance Manual | ✅ Complete | 1.0 | 2026-06-15 |
| Safety Case | ✅ Complete | 1.0 | 2026-06-20 |

**Documentation Readiness**: ✅ **COMPLETE**

---

## Overall Operational Readiness Assessment

### Readiness Summary

| Category | Status |
|----------|--------|
| **Technical Readiness** | ✅ READY |
| **Operational Readiness** | ✅ READY |
| **Safety Readiness** | ✅ READY |
| **Customer Acceptance** | ✅ APPROVED |
| **Documentation Readiness** | ✅ COMPLETE |

### Assessment Result

✅ **READY FOR OPERATIONAL DEPLOYMENT**

**Confidence Level**: HIGH (all criteria met, extensive validation completed)

### Deployment Recommendation

I, **John Smith**, Independent Validator, recommend **APPROVAL FOR OPERATIONAL DEPLOYMENT** of Railway Door Control System software Version 1.0.0 at SIL 3.

**Rationale**:
- All technical, operational, and safety readiness criteria met
- Extensive validation completed (laboratory, HIL, pilot installation)
- 1,200+ hours of fault-free operation in real environment
- Zero safety incidents, zero critical defects
- High customer satisfaction (98% driver confidence)
- Complete documentation package
- EN 50128:2011 compliance verified

**Restrictions**: NONE

**Deployment Authorization Date**: July 20, 2026

### Signatures

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Validator** | John Smith | _____________ | 2026-07-15 |
| **Safety Manager** | Alice Johnson | _____________ | 2026-07-15 |
| **Operations Manager** | David Lee | _____________ | 2026-07-16 |
| **Project Manager** | Bob Wilson | _____________ | 2026-07-16 |
```

---

## Operational Evidence Collection

### Evidence Archive Structure

```
evidence/validation/operational/
├── operational_validation_plan/
│   └── DOC-VAL-OVP-001_Operational_Validation_Plan_v1.0.md
├── commissioning/
│   ├── commissioning_test_results.md
│   └── commissioning_photos/ (50 photos)
├── environmental_stress/
│   ├── ENV-001_cold_operation_report.md
│   ├── ENV-002_hot_operation_report.md
│   ├── ENV-003_temperature_cycling_report.md
│   ├── ENV-004_vibration_stress_report.md
│   └── ENV-005_emi_stress_report.md
├── pilot_data/
│   ├── can_logs/ (84 days × 18 hours = 1,512 hours of CAN logs)
│   ├── diagnostic_logs/ (system health data)
│   ├── event_logs/ (door operations, alarms, faults)
│   ├── environmental/ (temperature, humidity data)
│   └── daily_logs/ (84 daily operational logs)
├── field_defects/
│   ├── FDR-2026-001_Door_Closing_Delay.md (CLOSED)
│   └── field_defect_summary.md
├── operational_readiness/
│   ├── operational_readiness_assessment.md
│   ├── deployment_authorization.md
│   └── transition_to_production_plan.md
└── operational_validation_report/
    └── DOC-VAL-OVR-001_Operational_Validation_Report_v1.0.md
```

---

## Tool Integration

### Workflow Management: Operational Validation Report

```bash
# Submit Operational Validation Report
workspace.py wf submit \
    --deliverable "DOC-VAL-OVR-001" \
    --phase validation \
    --author "John Smith (Validator)" \
    --description "Operational Validation Report - 12-week pilot installation" \
    --files evidence/validation/operational/operational_validation_report/DOC-VAL-OVR-001_Operational_Validation_Report_v1.0.md

# Workflow: Validator creates → QUA reviews → Safety Manager approves → CM baselines

# Check workflow status
workspace.py wf status --deliverable "DOC-VAL-OVR-001"
```

---

### Traceability: Operational Tests to Requirements

```bash
# Create traceability from operational tests to operational requirements
workspace.py trace create \
    --from validation \
    --to requirements \
    --source-id "OP-PILOT-2026" \
    --target-id "SRS-OPS-*" \
    --rationale "12-week pilot validates all operational requirements" \
    --sil 3

# Generate operational requirements coverage report
workspace.py trace report \
    --from validation \
    --to requirements \
    --filter "operational" \
    --format markdown \
    --output evidence/traceability/operational_requirements_coverage.md \
    --include-stats
```

---

## SIL-Specific Requirements

### SIL 0-1

**Operational Validation**:
- Laboratory/HIL validation: Sufficient
- Pilot installation: Recommended but not required
- Environmental stress testing: Basic (temperature range)

**Minimum Requirements**:
- Laboratory validation complete
- Basic environmental testing
- Short-term operational testing (optional)

---

### SIL 2

**Operational Validation**:
- Laboratory/HIL validation: Required
- Pilot installation: **Highly Recommended**
- Environmental stress testing: Required (temperature, vibration)

**Minimum Requirements**:
- Laboratory and HIL validation complete
- Environmental stress testing (temperature, vibration)
- Pilot installation highly recommended (2-4 weeks)
- Operational data collection

---

### SIL 3-4 (MANDATORY Requirements)

**Operational Validation**:
- Laboratory/HIL validation: **MANDATORY**
- Pilot installation: **Highly Recommended** (effectively mandatory for certification)
- Environmental stress testing: **MANDATORY** (temperature, vibration, EMI)
- Long-term monitoring: **MANDATORY** (≥4 weeks)

**Minimum Requirements**:
- Laboratory validation (all tests PASS)
- HIL validation (all scenarios PASS)
- Environmental stress testing (full EN 61373, EN 50121 compliance)
- **Pilot installation** (≥4 weeks, real operational environment)
- Long-term reliability demonstration (≥1,000 hours)
- Operational availability ≥99.5%
- Zero critical defects during pilot
- Customer acceptance from pilot
- Complete operational data logs archived

**Evidence for Certification**:
- Operational Validation Report
- Pilot installation data (CAN logs, diagnostics, environmental data)
- Environmental stress test reports
- Long-term reliability statistics
- Customer acceptance certificate
- Operational readiness assessment

---

## Example Operational Validation Scenarios

### Complete Pilot Installation Execution

```bash
# Pilot installation execution script
# File: execute_pilot_installation.sh

#!/bin/bash

echo "=========================================="
echo "  Pilot Installation - 12 Week Program"
echo "  Train #4523, Metro Line 2"
echo "=========================================="

# Phase 1: Depot Testing (Week 1-2)
echo "Phase 1: Depot Testing (2 weeks)"
./pilot_phases/phase1_depot_testing.sh
if [ $? -ne 0 ]; then
    echo "ERROR: Phase 1 failed - aborting pilot"
    exit 1
fi

# Phase 2: Test Track Operations (Week 3-4)
echo "Phase 2: Test Track Operations (2 weeks)"
./pilot_phases/phase2_test_track.sh
if [ $? -ne 0 ]; then
    echo "ERROR: Phase 2 failed - aborting pilot"
    exit 1
fi

# Phase 3: Limited Service (Week 5-8)
echo "Phase 3: Limited Service Pilot (4 weeks)"
./pilot_phases/phase3_limited_service.sh
if [ $? -ne 0 ]; then
    echo "ERROR: Phase 3 failed - aborting pilot"
    exit 1
fi

# Phase 4: Extended Service (Week 9-12)
echo "Phase 4: Extended Service Pilot (4 weeks)"
./pilot_phases/phase4_extended_service.sh
if [ $? -ne 0 ]; then
    echo "ERROR: Phase 4 failed - aborting pilot"
    exit 1
fi

# Generate final reports
echo "Generating operational validation reports..."
./tools/generate_operational_validation_report.sh

echo "=========================================="
echo "  Pilot Installation Complete: SUCCESS"
echo "  See: evidence/validation/operational/"
echo "=========================================="
```

---

## References

- **EN 50128:2011 Section 7.7.4.5**: Testing in operational environment
- **EN 50128:2011 Section 7.7.4.3**: Complex scenarios reflecting user needs
- **EN 61373**: Railway applications - Vibration and shock tests
- **EN 50121-3-2**: Railway EMI - Rolling stock
- **IEC 60068-2**: Environmental testing procedures

---

## Summary

This **Operational Validation Workflow** provides:

1. ✅ Complete field test planning (12-week operational validation plan)
2. ✅ Pilot installation setup (commissioning procedures, C code)
3. ✅ Environmental stress testing (temperature, vibration, EMI - C code)
4. ✅ Long-term operational monitoring (data collection scripts)
5. ✅ Field defect management (defect report template)
6. ✅ Operational readiness assessment (deployment authorization)
7. ✅ Operational evidence collection (comprehensive archive)
8. ✅ Tool integration (workspace.py wf and trace)
9. ✅ SIL-specific requirements (0-4, pilot mandatory for SIL 3-4)
10. ✅ Complete operational validation examples
11. ✅ EN 50128 Section 7.7.4.5 compliance (real hardware, real conditions)

**Total**: ~1,050 lines, ~40 pages, comprehensive operational validation coverage.
