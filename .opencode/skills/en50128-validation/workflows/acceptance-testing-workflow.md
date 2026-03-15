# Acceptance Testing Workflow

**EN 50128 Reference**: Section 7.7.4.3, Section 5.1.2.8 (Validator approval)  
**Phase**: Phase 7 - Validation  
**Role**: Validator (VAL) with Customer participation  
**SIL Level**: All (0-4)

---

## Purpose

This workflow defines the complete process for customer acceptance testing, ensuring the software meets stakeholder expectations and operational needs. It implements EN 50128 Section 7.7.4.3 requirement for "tests which stress the system by complex scenarios reflecting the actual needs of the user."

**Key Objectives**:
- Demonstrate software meets stakeholder expectations
- Validate operational usability and effectiveness
- Obtain customer acceptance sign-off
- Verify software is ready for production deployment
- Document acceptance criteria and test results
- Support certification and regulatory approval

**Inputs**:
- Software Requirements Specification (SRS) - stakeholder requirements
- User requirements and operational procedures
- System Validation Report (preliminary)
- Integration Test Report
- Target hardware and operational environment

**Outputs**:
- User Acceptance Test (UAT) specification
- UAT execution results
- Customer acceptance certificate
- Acceptance test evidence (logs, videos, photos)
- Deficiency list (if any)

---

## Table of Contents

1. [Acceptance Testing Overview](#acceptance-testing-overview)
2. [UAT Planning and Preparation](#uat-planning-and-preparation)
3. [UAT Test Case Development](#uat-test-case-development)
4. [Customer Involvement and Training](#customer-involvement-and-training)
5. [UAT Execution](#uat-execution)
6. [Acceptance Criteria Evaluation](#acceptance-criteria-evaluation)
7. [Customer Sign-Off Process](#customer-sign-off-process)
8. [Acceptance Evidence Collection](#acceptance-evidence-collection)
9. [Tool Integration](#tool-integration)
10. [SIL-Specific Requirements](#sil-specific-requirements)
11. [Example Acceptance Tests](#example-acceptance-tests)

---

## Acceptance Testing Overview

### Acceptance vs. Validation Testing

| Aspect | Validation Testing | Acceptance Testing |
|--------|-------------------|-------------------|
| **Purpose** | Technical correctness | User satisfaction |
| **Focus** | Requirements compliance | Operational effectiveness |
| **Performed By** | Independent Validator | Customer/End Users |
| **Criteria** | Technical specifications | Stakeholder expectations |
| **Environment** | Test lab, HIL | Operational environment |
| **Success Metric** | All tests pass | Customer approves |

**Relationship**: Acceptance testing is a **subset of validation** focused on customer approval.

---

### EN 50128 Requirements for Acceptance

**Section 7.7.4.3**: "The Validator shall specify and perform supplementary tests on his discretion or have them performed by the Tester. While the Overall Software Tests are mainly based on the structure of the Software Requirements Specification, the added value the Validator shall contribute, are tests which stress the system by complex scenarios reflecting the actual needs of the user."

**Section 5.1.2.8**: "The Validator shall give agreement/disagreement for the software release."

**Key Points**:
- Tests must reflect **actual user needs** (not just requirements)
- Complex operational scenarios required
- Customer/end-user participation essential
- Validator has final release approval authority

---

## UAT Planning and Preparation

### UAT Plan Template

```markdown
# User Acceptance Test Plan

## Document Control
- **Document ID**: DOC-VAL-UATP-001
- **Version**: 1.0
- **Date**: 2026-05-01
- **Author**: John Smith (Validator)
- **Project**: Railway Door Control System
- **SIL Level**: 3

## 1. Introduction

### 1.1 Purpose
Define user acceptance testing approach for Railway Door Control System to obtain customer approval for operational deployment.

### 1.2 Scope
- **Software**: Railway Door Control System v1.0.0
- **SIL Level**: 3
- **Acceptance Environment**: Railway depot test track + pilot installation
- **Customer**: Metro Rail Operations (David Lee, Operations Manager)
- **Duration**: 4 weeks (pilot operation)

### 1.3 Acceptance Objectives
- Demonstrate software meets operational needs
- Validate ease of use for train drivers
- Validate maintenance procedures
- Validate safety behavior in operational scenarios
- Obtain customer sign-off for deployment

## 2. Acceptance Criteria

### 2.1 Functional Acceptance
- [ ] All door operations work reliably
- [ ] Controls are intuitive for train drivers
- [ ] Response times meet operational expectations
- [ ] Diagnostics are clear and actionable
- [ ] Safety interlocks prevent unsafe operations

### 2.2 Operational Acceptance
- [ ] System operates reliably over 4-week pilot
- [ ] No unexpected behaviors observed
- [ ] Maintenance procedures are practical
- [ ] System integrates well with existing train systems
- [ ] Documentation is complete and understandable

### 2.3 Safety Acceptance
- [ ] All safety features work as expected
- [ ] Drivers feel confident in system safety
- [ ] Emergency procedures are effective
- [ ] No safety concerns raised by operators

### 2.4 Overall Acceptance
- [ ] Customer approves software for deployment
- [ ] Customer signs acceptance certificate

## 3. UAT Test Scenarios

### 3.1 Driver Interface Tests
- UAT-DRV-001: Door control during normal operation
- UAT-DRV-002: Door control in degraded mode
- UAT-DRV-003: Emergency door override
- UAT-DRV-004: Diagnostic information display
- UAT-DRV-005: Driver confidence in door status

### 3.2 Maintenance Interface Tests
- UAT-MAINT-001: Diagnostic mode access
- UAT-MAINT-002: Fault code interpretation
- UAT-MAINT-003: Door calibration procedure
- UAT-MAINT-004: System health monitoring

### 3.3 Operational Scenario Tests
- UAT-OP-001: Normal service day (full operations)
- UAT-OP-002: High passenger load scenario
- UAT-OP-003: Adverse weather operation
- UAT-OP-004: Extended operation (24 hours continuous)
- UAT-OP-005: Fault recovery procedures

### 3.4 Safety Scenario Tests
- UAT-SAFE-001: Door interlock effectiveness
- UAT-SAFE-002: Obstruction detection
- UAT-SAFE-003: Emergency brake coordination
- UAT-SAFE-004: Fail-safe behavior

## 4. Test Environment

### 4.1 Depot Test Track (Week 1-2)
- 500m test track
- Controlled environment
- Full instrumentation
- Daily testing sessions (4 hours/day)

### 4.2 Pilot Installation (Week 3-4)
- Train #4523 on Line 2
- Limited service (off-peak hours)
- Real operational conditions
- Customer supervision

### 4.3 Test Equipment
- Train #4523 (production vehicle)
- Data logger (CAN, diagnostics)
- Video recording equipment
- Observer checklists

## 5. Participants

| Role | Name | Organization | Responsibility |
|------|------|--------------|----------------|
| **Customer Representative** | David Lee | Metro Rail Operations | Overall acceptance decision |
| **Train Driver (Lead)** | Sarah Chen | Metro Rail Operations | Driver interface evaluation |
| **Train Driver** | Mike Johnson | Metro Rail Operations | Operational testing |
| **Maintenance Lead** | Tom Wilson | Metro Rail Maintenance | Maintenance procedures |
| **Safety Observer** | Emma Brown | Safety Department | Safety evaluation |
| **Validator** | John Smith | Independent | Test coordination, reporting |

### 5.1 Customer Training
- **Date**: 2026-04-25 (1 week before UAT)
- **Duration**: 1 day
- **Topics**: System operation, safety features, diagnostics, emergency procedures
- **Participants**: All customer participants

## 6. UAT Schedule

| Week | Activity | Location | Participants |
|------|----------|----------|--------------|
| **Week 1** | Driver interface tests | Depot test track | Drivers, Validator |
| **Week 2** | Maintenance & diagnostics | Depot test track | Maintenance, Validator |
| **Week 3** | Pilot installation (off-peak) | Line 2 | All participants |
| **Week 4** | Extended operation, final evaluation | Line 2 | All participants |
| **Week 5** | Acceptance review & sign-off | Office | Customer, Validator |

## 7. Success Criteria

### 7.1 Quantitative Criteria
- Zero critical defects during pilot
- Zero safety incidents during pilot
- ≤ 2 minor issues (documented, resolved)
- 100% driver confidence rating
- 95% operational availability during pilot

### 7.2 Qualitative Criteria
- Customer satisfaction with usability
- Positive driver feedback
- Maintenance procedures deemed practical
- Overall confidence in system readiness

## 8. Deficiency Management

### 8.1 Critical Deficiency
- **Action**: Abort UAT, fix defect, restart UAT
- **Authority**: Validator or Customer

### 8.2 Major Deficiency
- **Action**: Document, assess impact, determine if blocking
- **Authority**: Customer with Validator input

### 8.3 Minor Deficiency
- **Action**: Document, plan fix in future release
- **Authority**: Validator

## 9. Acceptance Decision

### 9.1 Acceptance Approval
- All acceptance criteria met
- Customer signs acceptance certificate
- Validator approves release (EN 50128 Section 5.1.2.8)

### 9.2 Conditional Acceptance
- Minor deficiencies documented
- Acceptance with restrictions (documented in Release Note)
- Customer and Validator approve with conditions

### 9.3 Acceptance Rejection
- Critical or multiple major deficiencies
- Customer or Validator rejects
- Re-UAT required after fixes

## 10. Deliverables

- [ ] UAT Test Specification (this plan + detailed test cases)
- [ ] UAT Execution Logs (daily logs, observations)
- [ ] Customer Feedback Forms (completed)
- [ ] UAT Test Report (summary of results)
- [ ] Acceptance Certificate (signed by customer)
- [ ] Deficiency List (if any)

## 11. Approvals

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Validator** | John Smith | ___________ | 2026-05-01 |
| **Customer Representative** | David Lee | ___________ | 2026-05-01 |
| **Safety Manager** | Alice Johnson | ___________ | 2026-05-01 |
```

---

### Traceability: UAT Plan to Stakeholder Requirements

```bash
# Link UAT Plan to stakeholder requirements in SRS
workspace.py trace create \
    --from validation \
    --to requirements \
    --source-id "DOC-VAL-UATP-001" \
    --target-id "DOC-REQ-SRS-001" \
    --rationale "UAT plan addresses all stakeholder requirements from Section 2.3" \
    --sil 3

# Validate stakeholder requirement coverage
workspace.py trace validate \
    --phase validation \
    --sil 3 \
    --coverage 100 \
    --filter "stakeholder" \
    --output evidence/traceability/uat_stakeholder_coverage.json
```

---

## UAT Test Case Development

### UAT Test Case Template

```markdown
# User Acceptance Test Case

## Test Information
- **Test ID**: UAT-DRV-001
- **Test Name**: Door Control During Normal Operation
- **Category**: Driver Interface
- **Stakeholder**: Train Driver
- **Requirement**: SRS-STAKE-010 (Driver shall control doors easily)
- **Priority**: HIGH
- **Duration**: 30 minutes

## Objective
Validate that train driver can control door operations during normal service using the driver interface, with intuitive controls and clear status feedback.

## Preconditions
- Train at depot test track
- System powered on and initialized
- Driver logged in and familiar with controls (post-training)
- All systems operational (no faults)

## Test Environment
- Location: Depot test track, Platform A
- Equipment: Train #4523, data logger, video recording
- Weather: Normal conditions
- Observers: Validator, Safety Observer

## Test Procedure (User Language - No Technical Jargon)

### Step 1: Initial Door Status Check
1. Look at door control panel
2. Verify all door status lights show green (doors closed)
3. Verify no warning lights or alarms

**Expected**: All indicators clear, no alarms

### Step 2: Open Doors (Arrival at Station)
1. Bring train to complete stop
2. Apply parking brake
3. Press "DOOR OPEN" button
4. Observe door status lights turn amber (opening)
5. Wait for doors to fully open
6. Observe door status lights turn green (fully open)

**Expected**:
- Doors begin opening within 1 second of button press
- Doors fully open within 4 seconds
- Door open indicators light up
- No alarms or warnings
- Passengers can board/exit safely

### Step 3: Close Doors (Departure Preparation)
1. Press "DOOR CLOSE" button
2. Observe door status lights turn amber (closing)
3. Wait for doors to fully close
4. Observe door status lights turn green (closed and locked)
5. Verify door lock indicators show locked

**Expected**:
- Doors begin closing within 1 second of button press
- Doors fully close within 5 seconds
- Door closed and locked indicators light up
- No alarms or warnings

### Step 4: Attempt to Open Doors While Moving (Safety Check)
1. Release parking brake
2. Accelerate to 20 km/h
3. **Attempt** to press "DOOR OPEN" button
4. Observe system response

**Expected**:
- Doors do NOT open
- Warning alarm sounds (door interlock)
- Visual warning on display
- Driver immediately understands doors cannot open while moving

### Step 5: Repeat Open/Close Cycle
1. Bring train to stop
2. Apply parking brake
3. Open doors
4. Close doors
5. Repeat 3 times

**Expected**:
- Consistent behavior on every cycle
- No degradation or unusual behavior
- Driver feels confident in control

## Acceptance Criteria
- [ ] All controls respond within 1 second
- [ ] Door status is always clear (lights, indicators)
- [ ] Safety interlock prevents opening while moving
- [ ] Driver finds controls intuitive (no confusion)
- [ ] Door operations are smooth and reliable
- [ ] Driver would feel confident using this system in service

## Driver Feedback Questions
1. Were the controls easy to understand? (Yes/No/Comments)
2. Was the door status always clear? (Yes/No/Comments)
3. Did you feel confident in the door control? (Yes/No/Comments)
4. Was the response time acceptable? (Yes/No/Comments)
5. Any suggestions for improvement? (Open comments)

## Results (Filled During Test)

### Execution Date: ___________
### Driver: ___________
### Observer: ___________

| Step | Pass/Fail | Notes |
|------|-----------|-------|
| 1. Initial status | ☐ Pass ☐ Fail | |
| 2. Open doors | ☐ Pass ☐ Fail | |
| 3. Close doors | ☐ Pass ☐ Fail | |
| 4. Safety interlock | ☐ Pass ☐ Fail | |
| 5. Repeat cycles | ☐ Pass ☐ Fail | |

### Overall Result: ☐ PASS ☐ FAIL

### Driver Feedback:
1. Controls intuitive: ☐ Yes ☐ No  
   Comments: ____________________

2. Status clear: ☐ Yes ☐ No  
   Comments: ____________________

3. Confidence: ☐ Yes ☐ No  
   Comments: ____________________

4. Response time: ☐ Yes ☐ No  
   Comments: ____________________

5. Suggestions: ____________________

### Observer Notes:
____________________

### Signatures:
- Driver: _________________ Date: _______
- Observer: _______________ Date: _______
- Validator: ______________ Date: _______
```

---

### C Code: UAT Test Harness for Data Logging

```c
// UAT test data logging system
// File: uat_logger.c

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "door_control_system.h"

// UAT event types
typedef enum {
    UAT_EVENT_TEST_START,
    UAT_EVENT_TEST_END,
    UAT_EVENT_BUTTON_PRESS,
    UAT_EVENT_DOOR_STATE_CHANGE,
    UAT_EVENT_ALARM,
    UAT_EVENT_SPEED_CHANGE,
    UAT_EVENT_OBSERVER_NOTE,
} uat_event_type_t;

// UAT log entry
typedef struct {
    uint32_t timestamp_ms;
    uat_event_type_t event_type;
    
    union {
        struct {
            char test_id[32];
            char driver_name[64];
        } test_start;
        
        struct {
            char test_id[32];
            bool passed;
        } test_end;
        
        struct {
            char button_name[32];
        } button_press;
        
        struct {
            uint8_t door_left_state;
            uint8_t door_right_state;
            bool door_left_locked;
            bool door_right_locked;
        } door_state;
        
        struct {
            uint8_t alarm_code;
            char alarm_description[128];
        } alarm;
        
        struct {
            uint16_t speed_kmh;
        } speed;
        
        struct {
            char note[256];
        } observer_note;
    } data;
} uat_log_entry_t;

// UAT logger context
typedef struct {
    FILE* log_file;
    FILE* csv_file;  // For easy analysis
    uint32_t entry_count;
    char current_test_id[32];
} uat_logger_t;

static uat_logger_t g_uat_logger = {0};

// Initialize UAT logger
result_t uat_logger_init(const char* log_dir) {
    char timestamp_str[32];
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    strftime(timestamp_str, sizeof(timestamp_str), "%Y%m%d_%H%M%S", tm_info);
    
    // Create log filenames
    char log_filename[256];
    char csv_filename[256];
    snprintf(log_filename, sizeof(log_filename), "%s/uat_log_%s.txt", 
             log_dir, timestamp_str);
    snprintf(csv_filename, sizeof(csv_filename), "%s/uat_log_%s.csv", 
             log_dir, timestamp_str);
    
    // Open log files
    g_uat_logger.log_file = fopen(log_filename, "w");
    g_uat_logger.csv_file = fopen(csv_filename, "w");
    
    if (g_uat_logger.log_file == NULL || g_uat_logger.csv_file == NULL) {
        printf("ERROR: Cannot create UAT log files\n");
        return RESULT_ERROR_FILE_IO;
    }
    
    // Write headers
    fprintf(g_uat_logger.log_file, "EN 50128 User Acceptance Test Log\n");
    fprintf(g_uat_logger.log_file, "Date: %s\n", get_date_string());
    fprintf(g_uat_logger.log_file, "Project: Railway Door Control System\n");
    fprintf(g_uat_logger.log_file, "SIL Level: 3\n\n");
    
    fprintf(g_uat_logger.csv_file, "Timestamp_ms,Event_Type,Test_ID,Details\n");
    
    g_uat_logger.entry_count = 0;
    g_uat_logger.current_test_id[0] = '\0';
    
    printf("UAT logger initialized: %s\n", log_filename);
    return RESULT_SUCCESS;
}

// Log test start
void uat_logger_test_start(const char* test_id, const char* driver_name) {
    uat_log_entry_t entry = {
        .timestamp_ms = get_time_ms(),
        .event_type = UAT_EVENT_TEST_START,
    };
    
    strncpy(entry.data.test_start.test_id, test_id, sizeof(entry.data.test_start.test_id) - 1);
    strncpy(entry.data.test_start.driver_name, driver_name, sizeof(entry.data.test_start.driver_name) - 1);
    
    strncpy(g_uat_logger.current_test_id, test_id, sizeof(g_uat_logger.current_test_id) - 1);
    
    // Write to log
    fprintf(g_uat_logger.log_file, "[%010u] TEST START: %s (Driver: %s)\n",
            entry.timestamp_ms, test_id, driver_name);
    
    fprintf(g_uat_logger.csv_file, "%u,TEST_START,%s,Driver: %s\n",
            entry.timestamp_ms, test_id, driver_name);
    
    fflush(g_uat_logger.log_file);
    fflush(g_uat_logger.csv_file);
    
    g_uat_logger.entry_count++;
}

// Log button press
void uat_logger_button_press(const char* button_name) {
    uint32_t timestamp = get_time_ms();
    
    fprintf(g_uat_logger.log_file, "[%010u] BUTTON PRESS: %s\n",
            timestamp, button_name);
    
    fprintf(g_uat_logger.csv_file, "%u,BUTTON_PRESS,%s,%s\n",
            timestamp, g_uat_logger.current_test_id, button_name);
    
    fflush(g_uat_logger.log_file);
    fflush(g_uat_logger.csv_file);
    
    g_uat_logger.entry_count++;
}

// Log door state change
void uat_logger_door_state_change(void) {
    uint32_t timestamp = get_time_ms();
    
    door_state_t left_state = get_door_state_left();
    door_state_t right_state = get_door_state_right();
    bool left_locked = get_door_lock_status_left();
    bool right_locked = get_door_lock_status_right();
    
    const char* left_str = door_state_to_string(left_state);
    const char* right_str = door_state_to_string(right_state);
    
    fprintf(g_uat_logger.log_file, "[%010u] DOOR STATE: Left=%s%s, Right=%s%s\n",
            timestamp, left_str, left_locked ? " (LOCKED)" : "",
            right_str, right_locked ? " (LOCKED)" : "");
    
    fprintf(g_uat_logger.csv_file, "%u,DOOR_STATE,%s,Left=%s%s;Right=%s%s\n",
            timestamp, g_uat_logger.current_test_id,
            left_str, left_locked ? "_LOCKED" : "",
            right_str, right_locked ? "_LOCKED" : "");
    
    fflush(g_uat_logger.log_file);
    fflush(g_uat_logger.csv_file);
    
    g_uat_logger.entry_count++;
}

// Log alarm
void uat_logger_alarm(uint8_t alarm_code, const char* description) {
    uint32_t timestamp = get_time_ms();
    
    fprintf(g_uat_logger.log_file, "[%010u] ALARM: 0x%02X - %s\n",
            timestamp, alarm_code, description);
    
    fprintf(g_uat_logger.csv_file, "%u,ALARM,%s,0x%02X: %s\n",
            timestamp, g_uat_logger.current_test_id, alarm_code, description);
    
    fflush(g_uat_logger.log_file);
    fflush(g_uat_logger.csv_file);
    
    g_uat_logger.entry_count++;
}

// Log speed change
void uat_logger_speed_change(uint16_t speed_kmh) {
    uint32_t timestamp = get_time_ms();
    
    fprintf(g_uat_logger.log_file, "[%010u] SPEED: %u km/h\n",
            timestamp, speed_kmh);
    
    fprintf(g_uat_logger.csv_file, "%u,SPEED,%s,%u km/h\n",
            timestamp, g_uat_logger.current_test_id, speed_kmh);
    
    fflush(g_uat_logger.log_file);
    fflush(g_uat_logger.csv_file);
    
    g_uat_logger.entry_count++;
}

// Log observer note
void uat_logger_observer_note(const char* note) {
    uint32_t timestamp = get_time_ms();
    
    fprintf(g_uat_logger.log_file, "[%010u] OBSERVER NOTE: %s\n",
            timestamp, note);
    
    fprintf(g_uat_logger.csv_file, "%u,OBSERVER_NOTE,%s,\"%s\"\n",
            timestamp, g_uat_logger.current_test_id, note);
    
    fflush(g_uat_logger.log_file);
    fflush(g_uat_logger.csv_file);
    
    g_uat_logger.entry_count++;
}

// Log test end
void uat_logger_test_end(const char* test_id, bool passed) {
    uint32_t timestamp = get_time_ms();
    
    fprintf(g_uat_logger.log_file, "[%010u] TEST END: %s - %s\n",
            timestamp, test_id, passed ? "PASS" : "FAIL");
    
    fprintf(g_uat_logger.csv_file, "%u,TEST_END,%s,%s\n",
            timestamp, test_id, passed ? "PASS" : "FAIL");
    
    fprintf(g_uat_logger.log_file, "\n");
    
    fflush(g_uat_logger.log_file);
    fflush(g_uat_logger.csv_file);
    
    g_uat_logger.entry_count++;
    g_uat_logger.current_test_id[0] = '\0';
}

// Finalize UAT logger
void uat_logger_finalize(void) {
    fprintf(g_uat_logger.log_file, "\n=== UAT Log Summary ===\n");
    fprintf(g_uat_logger.log_file, "Total log entries: %u\n", g_uat_logger.entry_count);
    
    if (g_uat_logger.log_file != NULL) {
        fclose(g_uat_logger.log_file);
    }
    if (g_uat_logger.csv_file != NULL) {
        fclose(g_uat_logger.csv_file);
    }
    
    printf("UAT log finalized (%u entries)\n", g_uat_logger.entry_count);
}

// Example: Instrumented UAT test execution
void execute_uat_drv_001(const char* driver_name) {
    printf("=== UAT-DRV-001: Door Control During Normal Operation ===\n");
    printf("Driver: %s\n", driver_name);
    printf("Observer: Follow test procedure and provide feedback\n\n");
    
    // Log test start
    uat_logger_test_start("UAT-DRV-001", driver_name);
    
    // Step 1: Initial status check
    printf("Step 1: Check initial door status\n");
    printf("  Observer: Verify all indicators are clear\n");
    uat_logger_observer_note("Step 1: Initial status check");
    uat_logger_door_state_change();
    wait_for_observer_confirmation();
    
    // Step 2: Open doors
    printf("\nStep 2: Open doors\n");
    printf("  Driver: Press DOOR OPEN button\n");
    wait_for_driver_action();
    
    uat_logger_button_press("DOOR_OPEN");
    system_command_door_open();
    
    // Monitor door opening
    uint32_t start_time = get_time_ms();
    while (!are_doors_fully_open() && (get_time_ms() - start_time) < 5000) {
        uat_logger_door_state_change();
        wait_ms(500);
    }
    
    uint32_t open_time = get_time_ms() - start_time;
    printf("  Doors opened in %u ms\n", open_time);
    uat_logger_observer_note_formatted("Doors opened in %u ms", open_time);
    
    wait_for_observer_confirmation();
    
    // Step 3: Close doors
    printf("\nStep 3: Close doors\n");
    printf("  Driver: Press DOOR CLOSE button\n");
    wait_for_driver_action();
    
    uat_logger_button_press("DOOR_CLOSE");
    system_command_door_close();
    
    // Monitor door closing
    start_time = get_time_ms();
    while (!are_doors_fully_closed() && (get_time_ms() - start_time) < 6000) {
        uat_logger_door_state_change();
        wait_ms(500);
    }
    
    uint32_t close_time = get_time_ms() - start_time;
    printf("  Doors closed in %u ms\n", close_time);
    uat_logger_observer_note_formatted("Doors closed in %u ms", close_time);
    
    wait_for_observer_confirmation();
    
    // Step 4: Safety interlock test
    printf("\nStep 4: Safety interlock test\n");
    printf("  Accelerate train to 20 km/h...\n");
    
    // Simulate acceleration (in real UAT, driver accelerates)
    for (uint16_t speed = 0; speed <= 20; speed += 5) {
        set_simulated_speed(speed);
        uat_logger_speed_change(speed);
        wait_ms(1000);
    }
    
    printf("  Driver: Attempt to press DOOR OPEN button (should be blocked)\n");
    wait_for_driver_action();
    
    uat_logger_button_press("DOOR_OPEN (attempt while moving)");
    result_t result = system_command_door_open();
    
    if (result == RESULT_ERROR_INTERLOCK) {
        printf("  ✓ Door interlock prevented opening (expected)\n");
        uat_logger_observer_note("Door interlock worked correctly - doors did not open");
        
        // Check alarm
        uint8_t alarm = system_get_alarm_status();
        if (alarm & ALARM_DOOR_INTERLOCK_VIOLATION) {
            printf("  ✓ Alarm raised (expected)\n");
            uat_logger_alarm(alarm, "Door interlock violation alarm");
        }
    } else {
        printf("  ✗ ERROR: Doors opened while moving!\n");
        uat_logger_observer_note("CRITICAL: Doors opened while moving!");
    }
    
    wait_for_observer_confirmation();
    
    // Step 5: Repeat cycles
    printf("\nStep 5: Repeat open/close cycles (3x)\n");
    
    // Stop train
    set_simulated_speed(0);
    uat_logger_speed_change(0);
    wait_ms(2000);
    
    for (int cycle = 1; cycle <= 3; cycle++) {
        printf("  Cycle %d...\n", cycle);
        uat_logger_observer_note_formatted("Cycle %d start", cycle);
        
        // Open
        system_command_door_open();
        uat_logger_button_press("DOOR_OPEN");
        wait_until_doors_open();
        uat_logger_door_state_change();
        
        wait_ms(2000);
        
        // Close
        system_command_door_close();
        uat_logger_button_press("DOOR_CLOSE");
        wait_until_doors_closed();
        uat_logger_door_state_change();
        
        wait_ms(1000);
    }
    
    printf("  Cycles complete\n");
    
    // Gather driver feedback
    printf("\n=== Driver Feedback ===\n");
    printf("1. Were the controls easy to understand? (Y/N): ");
    char response[128];
    get_user_input(response, sizeof(response));
    uat_logger_observer_note_formatted("Controls intuitive: %s", response);
    
    printf("2. Was the door status always clear? (Y/N): ");
    get_user_input(response, sizeof(response));
    uat_logger_observer_note_formatted("Status clear: %s", response);
    
    printf("3. Did you feel confident in the door control? (Y/N): ");
    get_user_input(response, sizeof(response));
    uat_logger_observer_note_formatted("Driver confidence: %s", response);
    
    printf("4. Was the response time acceptable? (Y/N): ");
    get_user_input(response, sizeof(response));
    uat_logger_observer_note_formatted("Response time acceptable: %s", response);
    
    printf("5. Any suggestions for improvement? ");
    get_user_input(response, sizeof(response));
    uat_logger_observer_note_formatted("Suggestions: %s", response);
    
    // Determine pass/fail
    printf("\nTest result (P for PASS, F for FAIL): ");
    get_user_input(response, sizeof(response));
    bool passed = (response[0] == 'P' || response[0] == 'p');
    
    // Log test end
    uat_logger_test_end("UAT-DRV-001", passed);
    
    printf("\n=== UAT-DRV-001 Complete: %s ===\n\n", passed ? "PASS" : "FAIL");
}
```

---

## Customer Involvement and Training

### Pre-UAT Customer Training

**Training Objectives**:
1. System operation overview
2. Safety features and interlocks
3. Normal operational procedures
4. Emergency procedures
5. Diagnostic interpretation
6. UAT testing procedures

**Training Duration**: 1 day (8 hours)

**Training Content**:

```markdown
# Customer Training Agenda

## Session 1: System Overview (9:00-10:30)
- Railway door control system architecture
- Hardware components and interfaces
- Software functionality overview
- Safety Integrity Level (SIL 3) explanation

## Session 2: Normal Operation (10:45-12:00)
- Driver interface walkthrough
- Door control procedures (open, close, lock)
- Status indicators and displays
- Normal operational scenarios

## Lunch Break (12:00-13:00)

## Session 3: Safety Features (13:00-14:30)
- Door interlock (speed-based)
- Obstruction detection and reversal
- Emergency procedures
- Fail-safe behavior
- Degraded mode operation

## Session 4: Diagnostics and Maintenance (14:45-16:00)
- Diagnostic mode access
- Fault code interpretation
- System health monitoring
- Maintenance procedures
- Troubleshooting guide

## Session 5: UAT Procedures (16:15-17:00)
- UAT test overview
- Test execution procedures
- Data logging and observations
- Feedback collection
- Acceptance criteria

## Practical Hands-On (if time permits)
- Driver simulator practice
- Diagnostic tool walkthrough
```

---

## UAT Execution

### Daily UAT Execution Template

```markdown
# UAT Daily Execution Log

**Date**: 2026-05-15  
**Location**: Depot Test Track, Platform A  
**Train**: #4523  
**Duration**: 4 hours (09:00-13:00)

## Participants
- Driver: Sarah Chen
- Observer: John Smith (Validator)
- Safety Observer: Emma Brown
- Data Logger: Automated (CAN logger)

## Tests Executed Today

| Test ID | Test Name | Start Time | Duration | Result | Notes |
|---------|-----------|------------|----------|--------|-------|
| UAT-DRV-001 | Door control - normal | 09:15 | 30 min | PASS | All criteria met |
| UAT-DRV-002 | Door control - degraded | 09:50 | 25 min | PASS | Handled correctly |
| UAT-DRV-003 | Emergency override | 10:20 | 20 min | PASS | Clear procedure |
| UAT-DRV-004 | Diagnostic display | 10:45 | 15 min | PASS | Easy to understand |

## Observations

### Positive Observations
- Driver found controls very intuitive
- Response times met expectations
- Door status indicators clear and unambiguous
- Safety interlock worked flawlessly
- No unexpected behaviors

### Issues Identified
- NONE

### Driver Feedback (Sarah Chen)
"The door control system is very straightforward. The indicators are clear, and I always know the status of the doors. The safety interlock gave me a clear alarm when I tried to open doors while moving - exactly what I would expect. I feel confident using this system."

**Driver Confidence Rating**: 10/10

### Observer Notes (John Smith)
"All tests executed successfully. Driver demonstrated good understanding of system operation. No hesitation or confusion observed. System behaved reliably throughout all tests."

## Action Items
- NONE

## Next Day Plan
- Continue with maintenance interface tests (UAT-MAINT series)
- Maintenance lead (Tom Wilson) will perform diagnostic tests

## Signatures
- Driver: _________________ Date: _______
- Validator: ______________ Date: _______
- Safety Observer: _________ Date: _______
```

---

## Acceptance Criteria Evaluation

### Acceptance Scorecard

```markdown
# UAT Acceptance Scorecard

**Project**: Railway Door Control System  
**Version**: 1.0.0  
**SIL Level**: 3  
**Evaluation Date**: 2026-06-05  
**Customer**: Metro Rail Operations

## Functional Acceptance

| Criterion | Weight | Score (1-5) | Weighted | Comments |
|-----------|--------|-------------|----------|----------|
| Door operations reliable | 20% | 5 | 1.00 | Perfect reliability over 4 weeks |
| Controls intuitive | 15% | 5 | 0.75 | All drivers found controls easy |
| Response times acceptable | 15% | 5 | 0.75 | Met expectations |
| Diagnostics clear | 10% | 5 | 0.50 | Easy fault identification |
| Safety interlocks effective | 20% | 5 | 1.00 | Worked flawlessly |
| Integration with train | 10% | 5 | 0.50 | Seamless integration |
| Documentation complete | 10% | 4 | 0.40 | Minor improvements suggested |

**Functional Acceptance Score**: 4.90 / 5.00 (98%) ✅ **PASS** (Threshold: 4.0)

## Operational Acceptance

| Criterion | Weight | Score (1-5) | Weighted | Comments |
|-----------|--------|-------------|----------|----------|
| Reliability over pilot | 25% | 5 | 1.25 | Zero unplanned downtime |
| No unexpected behaviors | 20% | 5 | 1.00 | Predictable operation |
| Maintenance practicality | 15% | 5 | 0.75 | Procedures straightforward |
| System integration | 20% | 5 | 1.00 | Works well with existing systems |
| Documentation quality | 10% | 4 | 0.40 | Good, minor improvements |
| Training effectiveness | 10% | 5 | 0.50 | Operators felt prepared |

**Operational Acceptance Score**: 4.90 / 5.00 (98%) ✅ **PASS** (Threshold: 4.0)

## Safety Acceptance

| Criterion | Weight | Score (1-5) | Weighted | Comments |
|-----------|--------|-------------|----------|----------|
| Safety features work | 35% | 5 | 1.75 | All safety tests passed |
| Driver confidence | 25% | 5 | 1.25 | 10/10 confidence rating |
| Emergency procedures | 20% | 5 | 1.00 | Clear and effective |
| No safety concerns | 20% | 5 | 1.00 | Zero safety incidents |

**Safety Acceptance Score**: 5.00 / 5.00 (100%) ✅ **PASS** (Threshold: 4.5 for SIL 3)

## Overall Acceptance

| Category | Score | Weight | Weighted | Status |
|----------|-------|--------|----------|--------|
| **Functional** | 4.90 | 35% | 1.72 | ✅ PASS |
| **Operational** | 4.90 | 35% | 1.72 | ✅ PASS |
| **Safety** | 5.00 | 30% | 1.50 | ✅ PASS |

**Overall Acceptance Score**: 4.94 / 5.00 (98.8%) ✅ **PASS**

**Acceptance Threshold (SIL 3)**: 4.5 / 5.00 (90%)

---

## Acceptance Decision

✅ **ACCEPTANCE APPROVED**

**Rationale**:
- All acceptance criteria exceeded thresholds
- Zero critical or major defects during pilot
- Zero safety incidents
- Excellent customer feedback (98% satisfaction)
- High driver confidence (10/10 average)
- Reliable operation over 4-week pilot

**Restrictions**: NONE

**Recommended for operational deployment**: YES

---

## Signatures

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Customer Representative** | David Lee | _____________ | 2026-06-05 |
| **Train Driver (Lead)** | Sarah Chen | _____________ | 2026-06-05 |
| **Maintenance Lead** | Tom Wilson | _____________ | 2026-06-05 |
| **Safety Observer** | Emma Brown | _____________ | 2026-06-05 |
| **Validator** | John Smith | _____________ | 2026-06-05 |
```

---

## Customer Sign-Off Process

### Acceptance Certificate Template

```markdown
# Software Acceptance Certificate

## Document Control
- **Document ID**: DOC-VAL-ACC-001
- **Version**: 1.0
- **Date**: 2026-06-08
- **Project**: Railway Door Control System
- **Software Version**: 1.0.0
- **SIL Level**: 3

---

## Customer Acceptance Statement

I, **David Lee**, Operations Manager for **Metro Rail Operations**, hereby certify that:

1. **User Acceptance Testing** has been completed for Railway Door Control System software Version 1.0.0 at SIL 3, in accordance with the User Acceptance Test Plan (DOC-VAL-UATP-001).

2. **All acceptance criteria** have been met, including functional, operational, and safety requirements.

3. **Pilot installation testing** was conducted on Train #4523 over a 4-week period (2026-05-08 to 2026-06-04), with the following results:
   - Zero critical defects
   - Zero safety incidents
   - 100% availability
   - Excellent driver feedback (average 10/10 confidence)
   - All operational scenarios validated successfully

4. The software **meets the operational needs** of Metro Rail Operations and is **fit for its intended application** in mainline passenger service.

5. I **approve this software for operational deployment** with **NO RESTRICTIONS**.

6. I acknowledge that:
   - System operates reliably within documented environmental limits
   - Training has been provided to all operational staff
   - Maintenance procedures are clear and practical
   - Safety features have been validated and are effective
   - Documentation is complete and understandable

---

## Acceptance Approval

**Customer Acceptance**: ✅ **APPROVED**

**Approval Date**: June 8, 2026

**Effective Date**: June 15, 2026 (deployment authorization)

---

## Customer Representative Signature

**Name**: David Lee  
**Title**: Operations Manager  
**Organization**: Metro Rail Operations

**Signature**: _________________________

**Date**: June 8, 2026

---

## Validator Confirmation

I, **John Smith**, Independent Validator, confirm that:

1. User Acceptance Testing was conducted in accordance with EN 50128:2011 Section 7.7.4.3 requirements.

2. Customer acceptance was obtained through rigorous testing with actual end users in operational environment.

3. All acceptance test results have been documented and archived.

4. Customer acceptance supports the **final validation approval** for software release (EN 50128 Section 5.1.2.8).

**Validator Signature**: _________________________

**Date**: June 8, 2026

---

## Witness (Safety Manager)

**Name**: Alice Johnson  
**Title**: Safety Manager

**Signature**: _________________________

**Date**: June 8, 2026

---

## Attachments

1. UAT Test Plan (DOC-VAL-UATP-001)
2. UAT Execution Logs (4 weeks)
3. UAT Test Report (DOC-VAL-UATR-001)
4. Acceptance Scorecard
5. Driver Feedback Forms (5 drivers)
6. Pilot Installation Summary Report

**Evidence Location**: `evidence/validation/acceptance/`
```

---

## Acceptance Evidence Collection

### Evidence Checklist

```markdown
# UAT Evidence Checklist

## Test Documentation
- [x] UAT Plan (DOC-VAL-UATP-001)
- [x] UAT Test Cases (15 test cases)
- [x] UAT Execution Logs (Daily logs, 4 weeks)
- [x] UAT Test Report (DOC-VAL-UATR-001)

## Test Results
- [x] Test result sheets (signed by driver, observer)
- [x] Pass/fail records for all tests
- [x] Deficiency reports (if any) - NONE
- [x] Re-test results (if applicable) - N/A

## Data Logs
- [x] CAN bus logs (4 weeks, 160 hours)
- [x] System diagnostic logs
- [x] Door operation logs (open/close cycles)
- [x] Alarm/event logs

## Driver Feedback
- [x] Driver feedback forms (5 drivers)
- [x] Driver confidence ratings (all 10/10)
- [x] Driver interview notes
- [x] Suggestions for improvement (minor UI suggestions)

## Photos and Videos
- [x] Photos of driver interface
- [x] Photos of door operations
- [x] Video of normal operation (5 min)
- [x] Video of safety interlock demonstration (2 min)
- [x] Video of emergency procedure (3 min)

## Pilot Installation Data
- [x] Pilot summary report (4 weeks)
- [x] Availability statistics (100%)
- [x] Incident reports (NONE)
- [x] Maintenance logs
- [x] Environmental conditions log (temperature, weather)

## Acceptance Documents
- [x] Acceptance Scorecard (4.94/5.00)
- [x] Acceptance Certificate (signed by customer)
- [x] Customer approval letter

## Traceability
- [x] UAT to stakeholder requirements traceability matrix
- [x] UAT coverage report (100% stakeholder requirements)

## Archive
- [x] All evidence archived to: `evidence/validation/acceptance/`
- [x] Evidence indexed and retrievable
- [x] Evidence backed up (offsite storage)
```

### Evidence Archive Structure

```
evidence/validation/acceptance/
├── uat_plan/
│   └── DOC-VAL-UATP-001_UAT_Plan_v1.0.md
├── uat_test_cases/
│   ├── UAT-DRV-001_Door_Control_Normal.md
│   ├── UAT-DRV-002_Door_Control_Degraded.md
│   ├── UAT-DRV-003_Emergency_Override.md
│   ├── UAT-DRV-004_Diagnostic_Display.md
│   └── ... (15 test cases total)
├── uat_execution_logs/
│   ├── week1/
│   │   ├── 2026-05-08_daily_log.md
│   │   ├── 2026-05-09_daily_log.md
│   │   └── ...
│   ├── week2/
│   ├── week3/
│   ├── week4/
│   └── uat_summary_log.md
├── uat_data_logs/
│   ├── can_logs/
│   │   ├── 2026-05-08_can.log
│   │   └── ... (28 files, one per day)
│   ├── system_logs/
│   │   ├── 2026-05-08_system.log
│   │   └── ...
│   └── uat_log_20260508_093000.csv (from uat_logger.c)
├── driver_feedback/
│   ├── sarah_chen_feedback.md
│   ├── mike_johnson_feedback.md
│   └── ... (5 drivers)
├── photos/
│   ├── driver_interface_01.jpg
│   ├── door_operation_01.jpg
│   └── ... (50 photos)
├── videos/
│   ├── normal_operation.mp4
│   ├── safety_interlock_demo.mp4
│   └── emergency_procedure.mp4
├── pilot_installation/
│   ├── pilot_summary_report.md
│   ├── availability_statistics.xlsx
│   ├── maintenance_logs.md
│   └── environmental_conditions.csv
├── acceptance/
│   ├── acceptance_scorecard.md
│   ├── DOC-VAL-ACC-001_Acceptance_Certificate_v1.0.md
│   └── customer_approval_letter.pdf
├── uat_report/
│   └── DOC-VAL-UATR-001_UAT_Report_v1.0.md
└── traceability/
    ├── uat_stakeholder_traceability.md
    └── uat_coverage_report.json
```

---

## Tool Integration

### Workflow Management: UAT Acceptance Certificate

```bash
# Submit UAT Acceptance Certificate to workflow system
workspace.py wf submit \
    --deliverable "DOC-VAL-ACC-001" \
    --phase validation \
    --author "John Smith (Validator)" \
    --description "Software Acceptance Certificate - Customer approval for deployment" \
    --files evidence/validation/acceptance/DOC-VAL-ACC-001_Acceptance_Certificate_v1.0.md

# Workflow: Customer signs → Validator confirms → Safety Manager witnesses → CM baselines

# Check acceptance workflow status
workspace.py wf status --deliverable "DOC-VAL-ACC-001"
```

---

### Traceability: UAT to Stakeholder Requirements

```bash
# Create traceability from UAT tests to stakeholder requirements
workspace.py trace create \
    --from validation \
    --to requirements \
    --source-id "UAT-DRV-001" \
    --target-id "SRS-STAKE-010" \
    --rationale "Validates stakeholder requirement for intuitive door control" \
    --sil 3

workspace.py trace create \
    --from validation \
    --to requirements \
    --source-id "UAT-SAFE-001" \
    --target-id "SRS-STAKE-015" \
    --rationale "Validates stakeholder requirement for door safety interlock" \
    --sil 3

# Generate stakeholder requirements coverage report
workspace.py trace report \
    --from validation \
    --to requirements \
    --filter "stakeholder" \
    --format markdown \
    --output evidence/traceability/uat_stakeholder_coverage.md \
    --include-stats

# Validate 100% stakeholder requirement coverage
workspace.py trace validate \
    --phase validation \
    --sil 3 \
    --coverage 100 \
    --filter "stakeholder" \
    --output evidence/traceability/uat_stakeholder_validation.json
```

**Expected Output** (uat_stakeholder_coverage.md):

```markdown
# UAT Stakeholder Requirements Coverage

| Stakeholder Requirement | Description | UAT Test(s) | Customer Feedback | Status |
|-------------------------|-------------|-------------|-------------------|--------|
| SRS-STAKE-010 | Intuitive door controls | UAT-DRV-001 | "Very easy to use" (10/10) | ✅ PASS |
| SRS-STAKE-015 | Effective safety interlock | UAT-SAFE-001 | "Exactly what I expected" | ✅ PASS |
| SRS-STAKE-020 | Clear diagnostics | UAT-MAINT-002 | "Easy to understand faults" | ✅ PASS |
| ... | ... | ... | ... | ... |

**Coverage**: 100% (15/15 stakeholder requirements)
```

---

## SIL-Specific Requirements

### SIL 0-1

**Acceptance Approach**:
- Customer testing: Recommended
- Formal UAT: Not required (informal acceptance acceptable)
- Customer sign-off: Recommended

**Minimum Requirements**:
- Demonstrate software to customer
- Obtain informal acceptance (email/letter)
- Document customer feedback

---

### SIL 2

**Acceptance Approach**:
- Customer testing: **Highly Recommended**
- Formal UAT: **Highly Recommended**
- Customer sign-off: Required
- Pilot installation: Recommended

**Minimum Requirements**:
- Formal UAT plan and test cases
- Customer participation in testing
- Documented customer feedback
- Acceptance certificate signed by customer

---

### SIL 3-4 (MANDATORY Requirements)

**Acceptance Approach**:
- Customer testing: **MANDATORY**
- Formal UAT: **MANDATORY**
- Customer sign-off: **MANDATORY**
- Pilot installation: **Highly Recommended** (operational environment testing)
- Independent validation: **MANDATORY**

**Minimum Requirements**:
- Comprehensive UAT plan approved by customer
- Detailed UAT test cases covering all stakeholder requirements
- Customer participation throughout UAT (drivers, operators, maintenance)
- Pilot installation in operational environment (minimum 2 weeks)
- 100% stakeholder requirements coverage
- Formal acceptance certificate signed by customer representative
- Validator confirmation of acceptance (EN 50128 Section 5.1.2.8)
- All acceptance evidence archived for certification

**Independence**:
- Validator coordinates UAT but does not influence customer decision
- Customer acceptance decision is independent
- Validator confirms process compliance (EN 50128 Section 7.7.4.3)

---

## Example Acceptance Tests

### Complete UAT Execution Script

```bash
# Run all UAT tests (automated logging, manual execution with customer)
# File: run_uat_suite.sh

#!/bin/bash

echo "=========================================="
echo "  EN 50128 User Acceptance Test Suite"
echo "  Railway Door Control System v1.0.0"
echo "  SIL Level: 3"
echo "=========================================="
echo ""

# Initialize UAT logger
mkdir -p evidence/validation/acceptance/uat_data_logs
export UAT_LOG_DIR="evidence/validation/acceptance/uat_data_logs"

# Driver interface tests (Week 1)
echo "=== Week 1: Driver Interface Tests ==="
./uat_tests/uat_drv_001_door_control_normal
./uat_tests/uat_drv_002_door_control_degraded
./uat_tests/uat_drv_003_emergency_override
./uat_tests/uat_drv_004_diagnostic_display
./uat_tests/uat_drv_005_driver_confidence

# Maintenance interface tests (Week 2)
echo "=== Week 2: Maintenance Interface Tests ==="
./uat_tests/uat_maint_001_diagnostic_mode
./uat_tests/uat_maint_002_fault_interpretation
./uat_tests/uat_maint_003_calibration
./uat_tests/uat_maint_004_health_monitoring

# Operational scenario tests (Week 3-4, pilot installation)
echo "=== Week 3-4: Pilot Installation Tests ==="
./uat_tests/uat_op_001_normal_service_day
./uat_tests/uat_op_002_high_load
./uat_tests/uat_op_003_adverse_weather
./uat_tests/uat_op_004_extended_operation
./uat_tests/uat_op_005_fault_recovery

# Safety scenario tests
echo "=== Safety Scenario Tests ==="
./uat_tests/uat_safe_001_interlock
./uat_tests/uat_safe_002_obstruction
./uat_tests/uat_safe_003_emergency_brake
./uat_tests/uat_safe_004_failsafe

echo ""
echo "=========================================="
echo "  UAT Suite Complete"
echo "  See: evidence/validation/acceptance/"
echo "=========================================="
```

---

## References

- **EN 50128:2011 Section 7.7.4.3**: Validator supplementary tests reflecting user needs
- **EN 50128:2011 Section 5.1.2.8**: Validator gives agreement/disagreement for software release
- **EN 50128:2011 Section 7.7.4.8**: Software Validation Report requirements
- **ISO/IEC 25010**: Software Quality Model (usability, operability)

---

## Summary

This **Acceptance Testing Workflow** provides:

1. ✅ Complete UAT planning (UAT plan template with customer involvement)
2. ✅ UAT test case development (user-language test procedures)
3. ✅ Customer training (pre-UAT preparation)
4. ✅ UAT execution (daily logs, driver feedback, pilot installation)
5. ✅ Acceptance criteria evaluation (scorecard, quantitative + qualitative)
6. ✅ Customer sign-off process (acceptance certificate template)
7. ✅ Acceptance evidence collection (photos, videos, logs, feedback)
8. ✅ Tool integration (workspace.py wf and trace)
9. ✅ SIL-specific requirements (0-4)
10. ✅ Complete C code examples (UAT logger, instrumented tests)
11. ✅ EN 50128 Section 7.7.4.3 compliance (complex user scenarios)

**Total**: ~1,100 lines, ~45 pages, comprehensive customer acceptance testing coverage.
