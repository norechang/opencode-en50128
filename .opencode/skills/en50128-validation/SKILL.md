---
name: en50128-validation
description: EN 50128 software validation and system testing for railway C applications
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  section: "7.7"
  sil_applicability: "0-4"
---

## What I do

I provide validation techniques, system testing approaches, and acceptance testing procedures required by EN 50128 Section 7.7:
- Overall software testing and validation
- Performance testing (mandatory SIL 3-4)
- Functional and black-box testing (mandatory SIL 3-4)
- System-level testing in target environment
- Operational scenario validation
- User acceptance testing

## When to use me

Use this skill when:
- Performing system-level validation
- Conducting acceptance testing
- Testing operational scenarios
- Validating performance requirements
- Preparing for software release
- Customer demonstration and acceptance

## Validation Techniques (EN 50128 Table A.7)

**EN 50128 Section 7.7, Table A.7** defines overall software testing techniques for validation:

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | **Performance Testing** | Table A.18 | - | HR | **M** |
| 2 | **Functional and Black-box Testing** | Table A.14 | HR | HR | **M** |
| 3 | Modelling | Table A.17 | - | R | R |

**Mandatory for SIL 3-4:**
- **Performance Testing (1)** - **MANDATORY**
- **Functional and Black-box Testing (2)** - **MANDATORY**

**Key Points:**
- One or more techniques SHALL be selected per SIL level
- Testing performed in target environment or high-fidelity simulation
- Independent validation MANDATORY for SIL 3-4

**Independence Requirements (SIL 3-4):**
- Validator **MUST** be independent from development team
- Validator **SHALL NOT report to Project Manager** (Section 5.1.2.10.f)
- Validator **gives agreement/disagreement for software release**

**Standard Reference:** `std/EN50128-2011.md` Section 7.7, Table A.7

## Validation Overview

**Purpose**: Demonstrate that software meets stakeholder needs and system requirements in operational environment

**Independent Validation**: MANDATORY for SIL 3-4 (Highly Recommended for SIL 2)
- Validator must be independent from development and verification teams
- Validation performed in target/representative environment
- Customer/end-user involvement required

**Key Difference from Verification**:
- **Verification**: "Are we building the product right?" (against specification)
- **Validation**: "Are we building the right product?" (against needs)

## Validation Planning

### Software Validation Plan (SVP) Template

```markdown
# Software Validation Plan

## 1. Introduction
### 1.1 Purpose
Validate [Software Component] for [Railway Application]

### 1.2 Scope
- Software Component: [Name and Version]
- SIL Level: [0-4]
- Target Platform: [Hardware/OS]
- Operational Environment: [Description]

### 1.3 References
- Software Requirements Specification (SRS)
- System Requirements Specification
- EN 50128:2011
- Project Quality Plan

## 2. Validation Approach
### 2.1 Validation Strategy
- System-level testing in target environment
- Operational scenario validation
- User acceptance testing
- Performance validation
- Safety validation

### 2.2 Independence
- Validation Team: [Names]
- Independence from Development: [Yes/No]
- Reporting Line: [Manager/Safety Manager]

## 3. Validation Environment
### 3.1 Target Platform
- Hardware: [CPU, Memory, I/O]
- Operating System: [Name, Version]
- Communication Interfaces: [CAN, Ethernet, Serial]

### 3.2 Test Environment
- Laboratory setup: [Description]
- Hardware-in-the-Loop (HIL): [Yes/No]
- Simulation environment: [Description]
- Real operational environment: [When applicable]

## 4. Validation Test Cases
### 4.1 Functional Validation
[List functional test scenarios]

### 4.2 Performance Validation
[List performance test scenarios]

### 4.3 Safety Validation
[List safety test scenarios]

### 4.4 Operational Scenarios
[List operational scenarios from stakeholders]

## 5. Acceptance Criteria
- All system-level tests pass
- Performance requirements met
- Safety requirements validated
- Customer acceptance obtained

## 6. Schedule
- Validation Start: [Date]
- Validation End: [Date]
- Acceptance Review: [Date]

## 7. Resources
- Validation Team: [Names and Roles]
- Test Equipment: [List]
- Budget: [If applicable]

## 8. Deliverables
- Validation Test Specification
- Validation Test Procedures
- Validation Test Results
- Validation Report
- Acceptance Certificate
```

## System Testing for Railway Software

### Test Environment Setup

```c
// Test harness for railway software validation
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

// Hardware abstraction for validation
typedef struct {
    uint16_t speed_input;
    uint16_t brake_pressure;
    bool door_sensor_front;
    bool door_sensor_rear;
    uint8_t track_circuit_status;
} validation_inputs_t;

typedef struct {
    uint16_t speed_command;
    uint16_t brake_command;
    bool door_lock_front;
    bool door_lock_rear;
    uint8_t alarm_status;
} validation_outputs_t;

// Validation test harness
typedef struct {
    validation_inputs_t inputs;
    validation_outputs_t outputs;
    validation_outputs_t expected;
    bool test_passed;
    char test_name[64];
} validation_test_t;

// Execute validation test
bool execute_validation_test(validation_test_t* test) {
    if (test == NULL) {
        return false;
    }
    
    // Apply inputs to system under test
    apply_inputs(&test->inputs);
    
    // Execute system cycle
    system_execute();
    
    // Read outputs
    read_outputs(&test->outputs);
    
    // Compare with expected
    test->test_passed = compare_outputs(&test->outputs, &test->expected);
    
    // Log results
    log_validation_result(test);
    
    return test->test_passed;
}

// Example: Door interlock validation test
validation_test_t door_interlock_test = {
    .test_name = "Door Interlock Safety - Speed > 0",
    .inputs = {
        .speed_input = 50,  // km/h
        .door_sensor_front = false,  // Door closed
        .door_sensor_rear = false,   // Door closed
    },
    .expected = {
        .door_lock_front = true,  // Must be locked
        .door_lock_rear = true,   // Must be locked
    }
};
```

### Operational Scenario Testing

#### Scenario 1: Normal Train Departure

```c
// Validation Test: Normal departure sequence
void validate_normal_departure(void) {
    printf("=== Validation: Normal Departure Sequence ===\n");
    
    // Initial state: Train at station, doors open
    set_train_state(STATE_AT_STATION);
    set_speed(0);
    set_doors(DOOR_OPEN);
    
    // Step 1: Close doors
    printf("Step 1: Operator closes doors...\n");
    command_close_doors();
    wait_for_condition(doors_are_closed, TIMEOUT_5_SEC);
    VALIDATE(get_door_status() == DOOR_CLOSED);
    VALIDATE(get_door_locks() == DOOR_LOCKED);
    
    // Step 2: Release brakes
    printf("Step 2: Release brakes...\n");
    command_release_brakes();
    wait_for_condition(brakes_are_released, TIMEOUT_2_SEC);
    VALIDATE(get_brake_status() == BRAKE_RELEASED);
    
    // Step 3: Apply traction
    printf("Step 3: Apply traction...\n");
    command_traction(TRACTION_25_PERCENT);
    wait_for_condition(train_is_moving, TIMEOUT_5_SEC);
    VALIDATE(get_speed() > 0);
    VALIDATE(get_door_locks() == DOOR_LOCKED);  // Safety check
    
    // Step 4: Accelerate to operational speed
    printf("Step 4: Accelerate to 80 km/h...\n");
    command_traction(TRACTION_50_PERCENT);
    wait_for_speed(80, TIMEOUT_30_SEC);
    VALIDATE(get_speed() >= 79 && get_speed() <= 81);
    
    printf("=== Normal Departure: PASS ===\n\n");
}
```

#### Scenario 2: Emergency Brake Application

```c
// Validation Test: Emergency brake during operation
void validate_emergency_braking(void) {
    printf("=== Validation: Emergency Braking ===\n");
    
    // Initial state: Train moving at 100 km/h
    set_train_state(STATE_OPERATIONAL);
    set_speed(100);
    set_doors(DOOR_CLOSED_LOCKED);
    
    uint32_t initial_time = get_time_ms();
    
    // Emergency event: Obstacle detected
    printf("Emergency: Obstacle detected!\n");
    trigger_emergency_brake();
    
    // Validate immediate response
    wait_ms(100);  // 100ms max response time for SIL 3-4
    VALIDATE(get_brake_status() == BRAKE_EMERGENCY);
    VALIDATE(get_traction_status() == TRACTION_OFF);
    
    // Monitor deceleration
    uint16_t prev_speed = get_speed();
    while (get_speed() > 0) {
        uint16_t current_speed = get_speed();
        
        // Validate continuous braking
        VALIDATE(current_speed <= prev_speed);
        
        // Validate deceleration rate
        uint32_t decel = calculate_deceleration(prev_speed, current_speed);
        VALIDATE(decel >= MIN_EMERGENCY_DECEL);
        VALIDATE(decel <= MAX_SAFE_DECEL);
        
        prev_speed = current_speed;
        wait_ms(100);
    }
    
    uint32_t stop_time = get_time_ms() - initial_time;
    uint32_t stop_distance = get_distance_traveled();
    
    printf("Stopped in %u ms, distance: %u m\n", stop_time, stop_distance);
    
    // Validate stopping distance
    VALIDATE(stop_distance <= calculate_max_stopping_distance(100));
    
    // Validate safety state
    VALIDATE(get_train_state() == STATE_SAFE);
    VALIDATE(get_door_locks() == DOOR_LOCKED);
    
    printf("=== Emergency Braking: PASS ===\n\n");
}
```

#### Scenario 3: Door Safety Interlock

```c
// Validation Test: Door cannot open while moving
void validate_door_interlock(void) {
    printf("=== Validation: Door Safety Interlock ===\n");
    
    // Initial state: Train moving at 50 km/h
    set_train_state(STATE_OPERATIONAL);
    set_speed(50);
    set_doors(DOOR_CLOSED_LOCKED);
    
    // Attempt to open door (should be prevented)
    printf("Attempting to open door at 50 km/h...\n");
    command_open_doors();
    wait_ms(1000);
    
    // Validate doors remain locked
    VALIDATE(get_door_status() == DOOR_CLOSED);
    VALIDATE(get_door_locks() == DOOR_LOCKED);
    VALIDATE(get_alarm_status() & ALARM_DOOR_INTERLOCK_VIOLATION);
    
    // Validate train response
    VALIDATE(get_brake_status() == BRAKE_APPLIED);  // Should apply brakes
    
    // Wait for train to stop
    wait_for_condition(train_is_stopped, TIMEOUT_30_SEC);
    VALIDATE(get_speed() == 0);
    
    // Now door can be opened
    printf("Train stopped, attempting to open door...\n");
    command_open_doors();
    wait_for_condition(doors_are_open, TIMEOUT_5_SEC);
    VALIDATE(get_door_status() == DOOR_OPEN);
    
    printf("=== Door Interlock: PASS ===\n\n");
}
```

### Performance Validation

```c
// Validate real-time performance requirements
typedef struct {
    const char* task_name;
    uint32_t max_execution_time_us;  // microseconds
    uint32_t max_jitter_us;
    uint32_t measurement_count;
} performance_requirement_t;

void validate_performance(void) {
    performance_requirement_t requirements[] = {
        {"Safety Monitor Task", 1000, 100, 1000},      // 1ms max, 100us jitter
        {"Speed Control Task", 5000, 500, 1000},       // 5ms max, 500us jitter
        {"Door Control Task", 10000, 1000, 1000},      // 10ms max, 1ms jitter
        {"Communication Task", 20000, 2000, 1000},     // 20ms max, 2ms jitter
    };
    
    for (size_t i = 0; i < sizeof(requirements)/sizeof(requirements[0]); i++) {
        printf("Validating: %s\n", requirements[i].task_name);
        
        uint32_t max_time = 0;
        uint32_t min_time = UINT32_MAX;
        uint32_t total_time = 0;
        
        for (uint32_t j = 0; j < requirements[i].measurement_count; j++) {
            uint32_t start = get_time_us();
            execute_task(i);
            uint32_t duration = get_time_us() - start;
            
            if (duration > max_time) max_time = duration;
            if (duration < min_time) min_time = duration;
            total_time += duration;
            
            // Validate max execution time
            if (duration > requirements[i].max_execution_time_us) {
                printf("FAIL: Execution time %u us exceeds limit %u us\n",
                       duration, requirements[i].max_execution_time_us);
                return;
            }
        }
        
        uint32_t avg_time = total_time / requirements[i].measurement_count;
        uint32_t jitter = max_time - min_time;
        
        printf("  Average: %u us\n", avg_time);
        printf("  Max: %u us (limit: %u us)\n", max_time, requirements[i].max_execution_time_us);
        printf("  Jitter: %u us (limit: %u us)\n", jitter, requirements[i].max_jitter_us);
        
        // Validate jitter
        if (jitter > requirements[i].max_jitter_us) {
            printf("FAIL: Jitter exceeds limit\n");
            return;
        }
        
        printf("  PASS\n\n");
    }
}
```

## Acceptance Testing

### User Acceptance Test (UAT) Template

```markdown
# User Acceptance Test

## Test Information
- Test ID: UAT-001
- Test Name: [Descriptive Name]
- Tester: [Customer/End User Name]
- Date: [Date]
- Software Version: [Version]

## Objective
[What operational capability is being validated]

## Preconditions
- System powered on
- All subsystems operational
- [Any specific setup required]

## Test Procedure
1. [Step 1 in user's language]
2. [Step 2 in user's language]
3. [Step 3 in user's language]
...

## Expected Results
[What the user should observe]

## Actual Results
[What was actually observed - filled by tester]

## Pass/Fail Criteria
- [ ] System behaves as expected
- [ ] User can operate system without assistance
- [ ] Performance meets operational needs
- [ ] No safety concerns observed

## Result
[ ] PASS  [ ] FAIL

## Comments
[User feedback and observations]

## Signatures
- Tester: _________________ Date: _______
- Validator: ______________ Date: _______
```

### Example UAT: Train Driver Interface

```markdown
# UAT-005: Train Driver Interface - Normal Operation

## Objective
Validate that train driver can operate train controls during normal service

## Preconditions
- Train in depot, all systems operational
- Driver logged in
- Safety systems active

## Test Procedure
1. Inspect driver display - verify all indicators show green status
2. Close all doors using door close button
3. Verify door closed indicator lights up
4. Release parking brake using brake release lever
5. Advance throttle to 25% position
6. Observe train accelerates smoothly
7. Observe speed display shows increasing speed
8. At 40 km/h, return throttle to 0%
9. Apply service brake using brake lever
10. Verify train decelerates smoothly to stop
11. Apply parking brake

## Expected Results
- All controls respond within 1 second
- Display updates in real-time
- Acceleration/deceleration smooth and predictable
- No unexpected alarms or warnings
- Train stops within expected distance

## Acceptance Criteria
- [ ] Interface intuitive and easy to use
- [ ] Response times acceptable for operations
- [ ] Display clear and readable
- [ ] Controls ergonomic
- [ ] Overall operation meets driver expectations

## Result: [PASS/FAIL]

## Driver Comments:
[Space for driver feedback]
```

## Safety Validation

### Hazard-Based Validation

For each identified hazard, create validation test:

```c
// Example: Validate hazard mitigation for "Unintended Movement"
void validate_hazard_unintended_movement(void) {
    printf("=== Safety Validation: Unintended Movement Prevention ===\n");
    
    // Hazard: Train moves with parking brake applied
    set_train_state(STATE_AT_STATION);
    set_parking_brake(BRAKE_APPLIED);
    set_speed(0);
    
    // Attempt to apply traction
    printf("Attempting traction with parking brake...\n");
    command_traction(TRACTION_50_PERCENT);
    wait_ms(2000);
    
    // Validate train does not move
    VALIDATE(get_speed() == 0);
    VALIDATE(get_traction_status() == TRACTION_OFF);
    VALIDATE(get_alarm_status() & ALARM_BRAKE_INTERLOCK);
    
    // Hazard: Train moves with doors open
    printf("Releasing brake, attempting movement with doors open...\n");
    set_parking_brake(BRAKE_RELEASED);
    set_doors(DOOR_OPEN);
    command_traction(TRACTION_25_PERCENT);
    wait_ms(2000);
    
    // Validate train does not move
    VALIDATE(get_speed() == 0);
    VALIDATE(get_traction_status() == TRACTION_OFF);
    VALIDATE(get_alarm_status() & ALARM_DOOR_INTERLOCK);
    
    printf("=== Hazard Validation: PASS ===\n\n");
}
```

### Fault Injection Validation

```c
// Validate system response to faults
void validate_fault_response(void) {
    printf("=== Validation: Fault Injection Tests ===\n");
    
    // Fault 1: Speed sensor failure
    printf("Test 1: Speed sensor failure\n");
    inject_fault(FAULT_SPEED_SENSOR);
    wait_ms(500);
    VALIDATE(get_system_state() == STATE_DEGRADED);
    VALIDATE(get_alarm_status() & ALARM_SENSOR_FAULT);
    VALIDATE(get_speed_limit() == REDUCED_SPEED_LIMIT);
    clear_fault(FAULT_SPEED_SENSOR);
    
    // Fault 2: Communication timeout
    printf("Test 2: Communication timeout\n");
    inject_fault(FAULT_COMM_TIMEOUT);
    wait_ms(5000);  // Allow timeout to occur
    VALIDATE(get_system_state() == STATE_SAFE);
    VALIDATE(get_brake_status() == BRAKE_EMERGENCY);
    clear_fault(FAULT_COMM_TIMEOUT);
    
    // Fault 3: Memory corruption detection
    printf("Test 3: Memory corruption detection\n");
    inject_fault(FAULT_MEMORY_CORRUPTION);
    wait_ms(100);
    VALIDATE(get_system_state() == STATE_SAFE);
    VALIDATE(system_has_rebooted());
    
    printf("=== Fault Injection: PASS ===\n\n");
}
```

## Validation Report Template

```markdown
# Software Validation Report

## 1. Executive Summary
- Project: [Name]
- Software Component: [Name and Version]
- SIL Level: [0-4]
- Validation Date: [Start] to [End]
- Validator: [Name] (Independent: Yes/No)
- Result: [PASS/FAIL]

## 2. Validation Environment
### 2.1 Target Platform
- Hardware: [Description]
- Operating System: [Name, Version]
- Configuration: [Details]

### 2.2 Test Setup
- Laboratory environment: [Description]
- HIL system: [If applicable]
- Test equipment: [List]

## 3. Validation Activities Summary
| Activity | Tests Planned | Tests Executed | Passed | Failed | Status |
|----------|--------------|----------------|--------|--------|--------|
| Functional Validation | 45 | 45 | 45 | 0 | PASS |
| Performance Validation | 12 | 12 | 12 | 0 | PASS |
| Safety Validation | 18 | 18 | 18 | 0 | PASS |
| Operational Scenarios | 8 | 8 | 8 | 0 | PASS |
| User Acceptance | 5 | 5 | 5 | 0 | PASS |
| **Total** | **88** | **88** | **88** | **0** | **PASS** |

## 4. Functional Validation Results
[Detailed results of functional tests]

## 5. Performance Validation Results
### 5.1 Timing Requirements
All real-time requirements met:
- Safety monitor: max 0.8ms (limit 1.0ms) ✓
- Speed control: max 4.2ms (limit 5.0ms) ✓
- Door control: max 8.5ms (limit 10.0ms) ✓

### 5.2 Resource Usage
- CPU usage: 45% average, 72% peak (limit 80%) ✓
- Memory usage: 1.2MB (limit 2.0MB) ✓
- Stack usage: 8KB max (limit 16KB) ✓

## 6. Safety Validation Results
All safety requirements validated:
- Door interlock: PASS
- Speed monitoring: PASS
- Emergency braking: PASS
- Fault detection: PASS
- Safe state transitions: PASS

## 7. Operational Scenarios
| Scenario | Description | Result | Notes |
|----------|-------------|--------|-------|
| SC-001 | Normal departure | PASS | Smooth operation |
| SC-002 | Emergency braking | PASS | Stop distance OK |
| SC-003 | Station stop | PASS | Precise positioning |
| SC-004 | Door operation | PASS | Reliable interlock |
| SC-005 | Fault recovery | PASS | Proper degradation |

## 8. User Acceptance Results
All acceptance tests passed with positive feedback:
- Train driver interface: Intuitive and responsive
- Maintenance interface: Clear diagnostics
- Overall usability: Meets operational needs

## 9. Issues and Observations
### 9.1 Issues Found
[None / List with resolution]

### 9.2 Observations
[Any notable observations or suggestions]

## 10. Traceability
- All system requirements validated: YES
- All hazards mitigated: YES
- All operational scenarios covered: YES

## 11. Conclusion
The software has been validated against all requirements and operational scenarios. All tests passed successfully. The software is ready for operational deployment at SIL [level].

## 12. Recommendations
- [ ] Approve for operational use
- [ ] Deploy to production
- [ ] Begin operational monitoring

## 13. Approvals
- Validator: _________________ Date: _______
- Project Manager: ___________ Date: _______
- Safety Manager: ____________ Date: _______
- Customer Representative: ___ Date: _______
```

## Validation Automation Scripts

### Python Script for Validation Test Execution

```python
#!/usr/bin/env python3
"""Execute validation test suite."""

import subprocess
import json
import sys
from datetime import datetime

class ValidationRunner:
    def __init__(self, config_file):
        with open(config_file) as f:
            self.config = json.load(f)
        self.results = []
    
    def run_test_suite(self):
        """Run all validation tests."""
        print(f"=== EN 50128 Validation Suite ===")
        print(f"Started: {datetime.now()}\n")
        
        for suite in self.config['test_suites']:
            print(f"Running {suite['name']}...")
            result = self.run_suite(suite)
            self.results.append(result)
        
        self.generate_report()
    
    def run_suite(self, suite):
        """Run a test suite."""
        result = subprocess.run(
            suite['command'],
            capture_output=True,
            text=True,
            shell=True
        )
        
        return {
            'name': suite['name'],
            'passed': (result.returncode == 0),
            'output': result.stdout,
            'errors': result.stderr
        }
    
    def generate_report(self):
        """Generate validation report."""
        total = len(self.results)
        passed = sum(1 for r in self.results if r['passed'])
        
        print(f"\n=== Validation Results ===")
        print(f"Total Suites: {total}")
        print(f"Passed: {passed}")
        print(f"Failed: {total - passed}")
        print(f"Success Rate: {100.0 * passed / total:.1f}%")
        
        # Save detailed report
        with open('validation_report.json', 'w') as f:
            json.dump(self.results, f, indent=2)
        
        return 0 if passed == total else 1

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: run_validation.py <config.json>")
        sys.exit(1)
    
    runner = ValidationRunner(sys.argv[1])
    sys.exit(runner.run_test_suite())
```

### Validation Configuration

```json
{
  "project": "Railway Door Control System",
  "sil_level": 3,
  "software_version": "1.0.0",
  "test_suites": [
    {
      "name": "Functional Validation",
      "command": "./tests/functional/run_all.sh"
    },
    {
      "name": "Performance Validation",
      "command": "./tests/performance/run_all.sh"
    },
    {
      "name": "Safety Validation",
      "command": "./tests/safety/run_all.sh"
    },
    {
      "name": "Operational Scenarios",
      "command": "./tests/scenarios/run_all.sh"
    }
  ]
}
```

---

## Comprehensive Workflows

This skill provides **3 comprehensive workflows** covering the complete validation lifecycle:

### 1. System Validation Workflow (`workflows/system-validation-workflow.md`)

**EN 50128 Reference**: Section 7.7 (Overall Software Testing / Final Validation), Table A.7  
**Coverage**: System-level testing, functional validation, performance validation, safety validation

**Key Topics**:
- Software Validation Plan (SVP) development with complete template
- Validation environment setup (laboratory, HIL, pilot installation)
- Functional validation (MANDATORY SIL 3-4, Table A.14)
- Performance validation (MANDATORY SIL 3-4, Table A.18)
- Safety validation (hazard-based testing, fault injection)
- Operational scenario validation (customer-defined scenarios)
- Requirements coverage validation (100% traceability verification)
- Validation report generation (EN 50128 Section 7.7.4.6-7.7.4.11)
- Complete C code examples (2,482 lines, ~100 pages)
- Python test automation scripts

**Example Usage**:
```bash
# 1. Create Software Validation Plan (SVP)
mkdir -p plans
cat > plans/DOC-VAL-SVP-001.md <<'EOF'
# Software Validation Plan
## Document Control
- Document ID: DOC-VAL-SVP-001
- SIL Level: 3
...
EOF

# 2. Setup validation environment
cd tests/validation
python3 setup_validation_env.py \
    --target arm-cortex-m4 \
    --hil-config hil_brake_system.json \
    --output evidence/validation/environment_setup.json

# 3. Execute functional validation tests
./test_functional_validation
./test_brake_interlock_validation
./test_door_safety_validation

# 4. Execute performance validation (SIL 3-4 MANDATORY)
python3 performance_validation.py \
    --requirements requirements/performance_requirements.json \
    --sil 3 \
    --output evidence/validation/performance_validation.json

# 5. Execute safety validation
./test_safety_validation
python3 fault_injection.py \
    --fault-list hazard_log.json \
    --output evidence/validation/safety_validation.json

# 6. Validate requirements coverage
workspace.py trace validate --phase validation --sil 3
workspace.py trace report \
    --from requirements \
    --to tests \
    --format markdown \
    --output evidence/validation/requirements_coverage.md

# 7. Generate validation report
python3 tools/validation_reporter.py \
    --svp plans/DOC-VAL-SVP-001.md \
    --results evidence/validation/*.json \
    --format markdown \
    --output evidence/validation/DOC-VAL-REP-001.md

# 8. Submit for review
workspace.py wf submit \
    --deliverable DOC-VAL-REP-001 \
    --phase validation
```

---

### 2. Acceptance Testing Workflow (`workflows/acceptance-testing-workflow.md`)

**EN 50128 Reference**: Section 7.7.4.3, Section 5.1.2.8 (Validator approval)  
**Coverage**: User acceptance testing, customer sign-off, operational readiness

**Key Topics**:
- User Acceptance Test (UAT) planning and preparation
- UAT test case development (user-language procedures, no technical jargon)
- Customer involvement and training for UAT execution
- UAT execution with daily logs and driver feedback
- Acceptance criteria evaluation (quantitative scorecard + qualitative feedback)
- Customer sign-off process (acceptance certificate template)
- Acceptance evidence collection (comprehensive archive: logs, videos, photos)
- Pilot installation procedures and commissioning
- Complete C code examples (1,549 lines, ~62 pages)
- UAT automation with Python logging

**Example Usage**:
```bash
# 1. Create UAT Plan
mkdir -p plans
cat > plans/DOC-VAL-UATP-001.md <<'EOF'
# User Acceptance Test Plan
## Document Control
- Document ID: DOC-VAL-UATP-001
- Customer: Railway Operator XYZ
...
EOF

# 2. Develop UAT test cases (user language)
python3 tools/uat_generator.py \
    --requirements requirements/user_requirements.json \
    --template templates/uat_test_case.md \
    --output tests/uat/test_cases/

# 3. Train customer on UAT procedures
# Provide: UAT Plan, Test Procedures, Instrumented Software

# 4. Execute UAT with customer
cd tests/uat
# Customer executes tests, system logs to uat_results.json
python3 uat_logger.py \
    --port /dev/ttyUSB0 \
    --output evidence/uat/uat_execution_log.json

# 5. Collect customer feedback
python3 uat_feedback_collector.py \
    --results evidence/uat/uat_execution_log.json \
    --output evidence/uat/customer_feedback.json

# 6. Evaluate acceptance criteria
python3 tools/acceptance_evaluator.py \
    --results evidence/uat/uat_execution_log.json \
    --criteria plans/acceptance_criteria.json \
    --sil 3 \
    --output evidence/uat/acceptance_evaluation.json

# 7. Generate acceptance certificate (if all criteria met)
python3 tools/acceptance_certificate_generator.py \
    --evaluation evidence/uat/acceptance_evaluation.json \
    --customer "Railway Operator XYZ" \
    --output evidence/uat/DOC-VAL-ACC-001.pdf

# 8. Submit for final approval
workspace.py wf submit \
    --deliverable DOC-VAL-ACC-001 \
    --phase validation
```

---

### 3. Operational Validation Workflow (`workflows/operational-validation-workflow.md`)

**EN 50128 Reference**: Section 7.7.4.5 (Testing in operational environment), Section 7.7.4.3  
**Coverage**: Field testing, pilot installations, long-term operational monitoring

**Key Topics**:
- Operational Validation Plan template (12-week field test plan)
- Pilot installation setup and commissioning procedures
- Environmental stress testing (temperature, vibration, humidity, EMI)
- Long-term operational monitoring (1,000+ hours continuous operation)
- Field defect management and emergency response procedures
- Operational readiness assessment and deployment authorization
- Operational evidence collection (comprehensive field data)
- Laboratory vs operational validation comparison
- Complete C code examples (1,560 lines, ~62 pages)
- Python field test automation

**Example Usage**:
```bash
# 1. Create Operational Validation Plan
mkdir -p plans
cat > plans/DOC-VAL-OVP-001.md <<'EOF'
# Operational Validation Plan
## Document Control
- Document ID: DOC-VAL-OVP-001
- Field Test Site: Test Track A, Pilot Line B
- Duration: 12 weeks
...
EOF

# 2. Commission pilot installation
cd tests/operational
python3 commissioning.py \
    --site "Test Track A" \
    --hardware-id "HW-PILOT-001" \
    --output evidence/operational/commissioning_report.json

# 3. Execute environmental stress tests
./test_environmental_stress
python3 environmental_test_runner.py \
    --test-suite environmental_stress_tests.json \
    --output evidence/operational/environmental_results.json

# 4. Start long-term monitoring (1,000+ hours)
python3 field_monitor.py \
    --site "Test Track A" \
    --duration 1000 \
    --log-interval 60 \
    --output evidence/operational/field_monitoring_log.json &

# 5. Collect operational data
python3 operational_data_collector.py \
    --monitoring-log evidence/operational/field_monitoring_log.json \
    --interval daily \
    --output evidence/operational/daily_reports/

# 6. Analyze field reliability
python3 tools/reliability_analyzer.py \
    --field-data evidence/operational/field_monitoring_log.json \
    --requirements requirements/reliability_requirements.json \
    --sil 3 \
    --output evidence/operational/reliability_analysis.json

# 7. Assess operational readiness
python3 tools/operational_readiness_assessor.py \
    --validation-results evidence/validation/ \
    --uat-results evidence/uat/ \
    --field-results evidence/operational/ \
    --sil 3 \
    --output evidence/operational/readiness_assessment.json

# 8. Generate operational validation report
python3 tools/operational_validator.py \
    --plan plans/DOC-VAL-OVP-001.md \
    --results evidence/operational/*.json \
    --format markdown \
    --output evidence/operational/DOC-VAL-OP-001.md
```

---

## Validation Workflow Selection by SIL

| SIL Level | Required Workflows | Key Requirements |
|-----------|-------------------|------------------|
| **SIL 0-1** | System Validation | Functional testing (HR), Independent validation (R) |
| **SIL 2** | System + Acceptance | Functional testing (HR), Performance testing (HR), Independent validation (HR) |
| **SIL 3-4** | **ALL 3 workflows** | Functional testing (**M**), Performance testing (**M**), Independent validation (**M**), Pilot installation (HR) |

**SIL 3-4 Special Requirements**:
- Independent Validator (MANDATORY, must not report to Project Manager)
- 100% functional coverage validation (all requirements traced and validated)
- Performance validation MANDATORY (Table A.18)
- Pilot installation Highly Recommended (operational validation)
- Customer acceptance certificate required
- Complete traceability from requirements through validation tests
- Validator has final release approval authority

---

## Tool Integration

### Validation Test Execution (Working Implementations)

**Python Validation Runner**:
```bash
# Execute complete validation suite
python3 tools/validation_runner.py \
    --config validation_config.json \
    --sil 3 \
    --output evidence/validation/validation_results.json

# Validation config includes:
# - Functional test suites
# - Performance test suites
# - Safety test suites
# - Operational scenarios
```

**Validation Configuration Example** (`validation_config.json`):
```json
{
  "project": "Railway Door Control System",
  "sil_level": 3,
  "software_version": "1.0.0",
  "test_suites": [
    {
      "name": "Functional Validation",
      "command": "./tests/functional/run_all.sh",
      "mandatory": true
    },
    {
      "name": "Performance Validation",
      "command": "./tests/performance/run_all.sh",
      "mandatory": true
    },
    {
      "name": "Safety Validation",
      "command": "./tests/safety/run_all.sh",
      "mandatory": true
    }
  ]
}
```

---

### Performance Validation Tools (Working Implementations)

**Performance Testing** (MANDATORY SIL 3-4):
```bash
# Execute timing validation
./tests/performance/test_timing_requirements

# Measure execution time, jitter, deadline compliance
python3 tools/performance_validator.py \
    --sil 3 \
    --requirements requirements/timing_requirements.json \
    --results performance_results.json \
    --output evidence/validation/performance_validation.json

# For SIL 3-4: Zero deadline misses required
```

**Resource Usage Validation**:
```bash
# Measure CPU, memory, stack usage on target
python3 tools/resource_validator.py \
    --binary build/firmware.elf \
    --map build/firmware.map \
    --sil 3 \
    --output evidence/validation/resource_validation.json
```

---

### Hardware-in-the-Loop (HIL) Validation

**HIL Test Execution**:
```bash
# Install pyserial for UART communication
pip3 install pyserial

# Run HIL validation suite
python3 tests/hil/hil_validation_runner.py \
    --port /dev/ttyUSB0 \
    --baudrate 115200 \
    --test-suite tests/hil/validation_tests.json \
    --timeout 600 \
    --output evidence/validation/hil_results.json

# Validate HIL test results
python3 tools/hil_validator.py \
    --results evidence/validation/hil_results.json \
    --requirements requirements/system_requirements.json \
    --sil 3 \
    --output evidence/validation/hil_validation.json
```

---

### Traceability Integration (Working Implementation)

**Link Validation Tests to Requirements**:
```bash
# Create traceability link (validation test → requirement)
workspace.py trace create \
    --from tests \
    --to requirements \
    --source-id VT-BRAKE-001 \
    --target-id REQ-SAF-015 \
    --rationale "Validation test validates emergency brake requirement"

# Create traceability link (validation test → hazard)
workspace.py trace create \
    --from tests \
    --to hazards \
    --source-id VT-DOOR-INTERLOCK-001 \
    --target-id HAZ-004 \
    --rationale "Validation test validates door interlock mitigates unintended movement hazard"

# Validate validation traceability completeness (100% required SIL 3-4)
workspace.py trace validate --phase validation --sil 3

# Generate traceability report (requirements → validation tests)
workspace.py trace report \
    --from requirements \
    --to tests \
    --format markdown \
    --output evidence/validation/requirements_coverage.md

# Verify 100% coverage (SIL 3-4)
python3 tools/coverage_checker.py \
    --traceability evidence/validation/requirements_coverage.md \
    --sil 3 \
    --output evidence/validation/coverage_validation.json
```

---

### Workflow Management (Working Implementation)

**Submit Validation Report for Review**:
```bash
# Submit validation report to QA
workspace.py wf submit \
    --deliverable DOC-VAL-REP-001 \
    --phase validation

# QA reviews (document template compliance)
workspace.py wf review \
    --deliverable DOC-VAL-REP-001 \
    --reviewer QUA \
    --status approved \
    --comments "Template compliance verified. All sections complete."

# VMGR reviews (technical validation)
workspace.py wf review \
    --deliverable DOC-VAL-REP-001 \
    --reviewer VMGR \
    --status approved \
    --comments "All validation tests passed. 100% requirements coverage. Approve for release."

# Check workflow status
workspace.py wf status --deliverable DOC-VAL-REP-001
```

---

## EN 50128 Section 7.7 Coverage

This skill provides **complete coverage** of EN 50128 Section 7.7 (Overall Software Testing / Final Validation):

| Section | Topic | Coverage in Workflows |
|---------|-------|----------------------|
| **7.7.4.1** | Overall Software Test Specification | System Validation Workflow |
| **7.7.4.2** | Overall Software Testing | System Validation Workflow |
| **7.7.4.3** | Supplementary validation tests | Acceptance Testing, Operational Validation |
| **7.7.4.4** | Overall Software Test Report | System Validation Workflow (report generation) |
| **7.7.4.5** | Testing in operational environment | Operational Validation Workflow |
| **7.7.4.6-7.7.4.11** | Software Validation Report | System Validation Workflow (SVR template) |
| **7.7.4.12** | Release Note | System Validation Workflow (release note template) |

---

## Table A.7 Validation Techniques Coverage

| # | Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Workflow Coverage |
|---|-----------|-------|---------|---------|-------------------|
| **1** | **Performance Testing** | - | HR | **M** | System Validation (Section 4), Operational Validation (environmental stress) |
| **2** | **Functional and Black-box Testing** | HR | HR | **M** | System Validation (Section 3), Acceptance Testing (UAT) |
| **3** | Modelling | - | R | R | System Validation (operational scenarios) |

**SIL 3-4 Mandatory Techniques**:
- ✅ **Performance Testing (1)** - Covered in System Validation Workflow (timing, resource usage, real-time compliance)
- ✅ **Functional and Black-box Testing (2)** - Covered in System Validation (functional tests), Acceptance Testing (UAT)

---

## References

- EN 50128:2011 Section 7.7 (Overall Software Testing / Final Validation)
- EN 50128:2011 Table A.7 (Validation Techniques)
- EN 50128:2011 Table A.14 (Functional and Black-box Testing)
- EN 50128:2011 Table A.18 (Performance Testing)
- EN 50126 Part 1 (RAMS Process)
- ISO/IEC 25010 (Software Quality)
- IEC 61508 Part 3 (Software Validation)
