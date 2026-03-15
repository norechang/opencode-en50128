# Component Integration Workflow

**EN 50128 Reference**: Section 7.6.1, 7.6.4.1-7.6.4.6  
**Phase**: Phase 6 - Integration  
**Role**: Integrator (INT)  
**SIL Level**: All (0-4)

---

## Purpose

This workflow defines the complete process for progressively integrating tested C software components into subsystems and ultimately a complete software system. It implements EN 50128 Section 7.6.4.1 requirement for "progressively combining individual and previously tested components" with adequate interface validation.

**Key Objectives**:
- Progressive integration of independently tested components
- Interface contract verification at each integration step
- Integration defect detection and remediation
- Traceability from components through integration to system
- Evidence collection for verification (Section 7.6.4.11-7.6.4.13)

**Inputs**:
- Component Test Reports (from TST/IMP, Phase 5)
- Software Design Specification (from DES, Phase 3)
- Software Interface Specifications (from DES, Phase 3)
- Software Integration Test Specification (this phase)
- Verified components (C object files, libraries)

**Outputs**:
- Integrated software subsystems
- Software Integration Test Report (Section 7.6.4.3-7.6.4.6)
- Integration defect reports
- Updated traceability matrices
- Integration build artifacts (executables, libraries)

---

## Table of Contents

1. [Integration Strategies](#integration-strategies)
2. [Progressive Integration Process](#progressive-integration-process)
3. [Interface Testing at Integration](#interface-testing-at-integration)
4. [Build System Integration](#build-system-integration)
5. [Integration Test Execution](#integration-test-execution)
6. [Defect Management and Re-integration](#defect-management-and-re-integration)
7. [Integration Evidence Collection](#integration-evidence-collection)
8. [Tool Integration](#tool-integration)
9. [SIL-Specific Requirements](#sil-specific-requirements)
10. [Example Integration Scenarios](#example-integration-scenarios)

---

## Integration Strategies

### Strategy Selection Criteria

**EN 50128 Section 7.6.4.1**: "The integration of software components shall be the process of progressively combining individual and previously tested components..."

Choose integration strategy based on:

| Criterion | Bottom-Up | Top-Down | Sandwich | Big Bang |
|-----------|-----------|----------|----------|----------|
| **Team Size** | Small (1-3) | Medium (3-5) | Large (5+) | Small (1-2) |
| **System Complexity** | Low-Medium | Medium-High | High | Low |
| **Critical Control Flow** | No | **Yes** | **Yes** | No |
| **Hardware Dependencies** | **Early** | Late | Parallel | Final |
| **SIL 3-4 Suitability** | ✅ **Yes** | ✅ **Yes** | ✅ **Yes** | ❌ **No** |
| **Parallel Development** | No | Partial | **Yes** | No |
| **Early Risk Detection** | Medium | **High** | **High** | **Low** |

**Recommendation by SIL**:
- **SIL 0-1**: Any strategy acceptable, Big Bang allowed for simple systems
- **SIL 2**: Progressive strategy (bottom-up, top-down, sandwich) - **Highly Recommended**
- **SIL 3-4**: Progressive strategy **MANDATORY** - Big Bang **NOT RECOMMENDED**

---

### 1. Bottom-Up Integration Strategy

**Best For**: Systems with critical low-level drivers, hardware abstraction layers, safety-critical infrastructure

**Principle**: Integrate lowest-level components first, building upward to application layer.

```
Level 4: Application         [ Main Application ]
                                     ↑
Level 3: Controllers         [ Control Logic ]
                                     ↑
Level 2: Services            [ Sensor Service ] [ Actuator Service ]
                                     ↑                    ↑
Level 1: Drivers/HAL        [ Sensor Driver ] [ Actuator Driver ]
                                     ↑                    ↑
Level 0: Hardware           [ Hardware Registers ]

Integration Order: Level 0 → Level 1 → Level 2 → Level 3 → Level 4
```

**C Example Structure**:

```c
// Level 1: Driver module (integrated first)
// File: sensor_driver.c

#include "sensor_driver.h"
#include "hardware_regs.h"  // Level 0 (hardware)

result_t sensor_driver_init(void) {
    // Direct hardware access
    HW_REG_SENSOR_CTRL = SENSOR_ENABLE;
    return RESULT_SUCCESS;
}

result_t sensor_driver_read(uint16_t* value) {
    if (value == NULL) {
        return RESULT_ERROR_NULL_PTR;
    }
    *value = HW_REG_SENSOR_DATA;
    return RESULT_SUCCESS;
}

// Level 2: Service module (integrated second)
// File: sensor_service.c

#include "sensor_service.h"
#include "sensor_driver.h"  // Depends on Level 1

typedef struct {
    uint16_t raw_value;
    uint16_t filtered_value;
    bool valid;
} sensor_data_t;

static sensor_data_t sensor_data;

result_t sensor_service_init(void) {
    result_t result = sensor_driver_init();  // Uses Level 1
    if (result != RESULT_SUCCESS) {
        return result;
    }
    sensor_data.valid = false;
    return RESULT_SUCCESS;
}

result_t sensor_service_update(void) {
    uint16_t raw;
    result_t result = sensor_driver_read(&raw);  // Uses Level 1
    if (result != RESULT_SUCCESS) {
        sensor_data.valid = false;
        return result;
    }
    
    // Service-level processing
    sensor_data.raw_value = raw;
    sensor_data.filtered_value = apply_filter(raw);
    sensor_data.valid = true;
    
    return RESULT_SUCCESS;
}

// Level 3: Controller module (integrated third)
// File: brake_controller.c

#include "brake_controller.h"
#include "sensor_service.h"  // Depends on Level 2

result_t brake_controller_compute(brake_command_t* command) {
    if (command == NULL) {
        return RESULT_ERROR_NULL_PTR;
    }
    
    // Use Level 2 service
    result_t result = sensor_service_update();
    if (result != RESULT_SUCCESS) {
        command->brake_level = MAX_BRAKE;  // Safe state
        return RESULT_ERROR_SENSOR_FAULT;
    }
    
    uint16_t speed = sensor_service_get_speed();
    command->brake_level = compute_brake_level(speed);
    
    return RESULT_SUCCESS;
}
```

**Integration Test Sequence (Bottom-Up)**:

```c
// Step 1: Test Level 1 (Driver) in isolation
// File: test_integration_step1_driver.c

void test_step1_driver_initialization(void) {
    result_t result = sensor_driver_init();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Verify hardware register state
    TEST_ASSERT_EQUAL(SENSOR_ENABLE, HW_REG_SENSOR_CTRL);
}

void test_step1_driver_read(void) {
    uint16_t value;
    result_t result = sensor_driver_read(&value);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    TEST_ASSERT_TRUE(value >= MIN_SENSOR_VALUE);
    TEST_ASSERT_TRUE(value <= MAX_SENSOR_VALUE);
}

// Step 2: Test Level 2 (Service) integrated with Level 1 (Driver)
// File: test_integration_step2_service.c

void test_step2_service_uses_driver(void) {
    // Initialize integrated system (Level 1 + Level 2)
    result_t result = sensor_service_init();  // Calls sensor_driver_init()
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Test service function using driver
    result = sensor_service_update();  // Calls sensor_driver_read()
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Verify data flow from driver to service
    uint16_t speed = sensor_service_get_speed();
    TEST_ASSERT_TRUE(speed >= 0);
    TEST_ASSERT_TRUE(speed <= MAX_SPEED);
}

void test_step2_service_handles_driver_error(void) {
    // Inject driver fault
    inject_fault("sensor_driver", FAULT_HARDWARE_ERROR);
    
    result_t result = sensor_service_update();
    TEST_ASSERT_EQUAL(RESULT_ERROR_HARDWARE, result);
    
    // Verify service handles error gracefully
    bool valid = sensor_service_is_valid();
    TEST_ASSERT_FALSE(valid);
}

// Step 3: Test Level 3 (Controller) integrated with Level 2 + Level 1
// File: test_integration_step3_controller.c

void test_step3_controller_uses_service(void) {
    // Initialize full integration stack
    sensor_service_init();  // Initializes Level 2 and Level 1
    
    brake_command_t command;
    result_t result = brake_controller_compute(&command);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Verify data flows through all levels:
    // Controller → Service → Driver → Hardware
    TEST_ASSERT_TRUE(command.brake_level >= 0);
    TEST_ASSERT_TRUE(command.brake_level <= MAX_BRAKE);
}

void test_step3_controller_handles_service_failure(void) {
    // Inject service failure (propagates from driver failure)
    inject_fault("sensor_driver", FAULT_DISCONNECTED);
    
    brake_command_t command;
    result_t result = brake_controller_compute(&command);
    
    // Verify controller enters safe state
    TEST_ASSERT_EQUAL(RESULT_ERROR_SENSOR_FAULT, result);
    TEST_ASSERT_EQUAL(MAX_BRAKE, command.brake_level);  // Safe state
}
```

**Advantages of Bottom-Up**:
- ✅ Low-level infrastructure (drivers, HAL) tested early
- ✅ No stubs required for lower levels
- ✅ Early hardware integration validation
- ✅ Suitable for hardware-dependent systems (railway signals, braking systems)

**Disadvantages of Bottom-Up**:
- ❌ Test drivers needed for upper levels (can be complex)
- ❌ System-level behavior validated late
- ❌ Control flow logic tested last

---

### 2. Top-Down Integration Strategy

**Best For**: Control-heavy systems, safety-critical decision logic, systems with complex state machines

**Principle**: Integrate top-level control logic first using stubs for lower-level components, progressively replacing stubs with real implementations.

```
Level 0: Application         [ Main Controller ] ← Integrated first
                                     ↓
Level 1: Services            [ Stub: Sensor ] [ Stub: Actuator ]
                                     ↓                    ↓
Level 2: Drivers             [ Stub ] [ Stub ]
                                     ↓        ↓
Level 3: Hardware            [ Not yet integrated ]

Integration Order: Level 0 → Level 1 (replace stubs) → Level 2 (replace stubs) → Level 3
```

**C Example with Stubs**:

```c
// Level 0: Top-level controller (integrated first)
// File: main_controller.c

#include "main_controller.h"
#include "sensor_service.h"    // Initially stubbed
#include "actuator_service.h"  // Initially stubbed

typedef enum {
    STATE_IDLE,
    STATE_MONITORING,
    STATE_BRAKING,
    STATE_EMERGENCY
} system_state_t;

static system_state_t current_state = STATE_IDLE;

result_t main_controller_init(void) {
    current_state = STATE_IDLE;
    
    // Initialize services (initially stubs)
    result_t result = sensor_service_init();
    if (result != RESULT_SUCCESS) {
        return result;
    }
    
    result = actuator_service_init();
    if (result != RESULT_SUCCESS) {
        return result;
    }
    
    current_state = STATE_MONITORING;
    return RESULT_SUCCESS;
}

result_t main_controller_cycle(void) {
    switch (current_state) {
        case STATE_MONITORING: {
            uint16_t speed = sensor_service_get_speed();  // Initially from stub
            
            if (speed > CRITICAL_SPEED) {
                current_state = STATE_BRAKING;
            } else if (speed == SENSOR_ERROR_VALUE) {
                current_state = STATE_EMERGENCY;
            }
            break;
        }
        
        case STATE_BRAKING: {
            result_t result = actuator_service_apply_brake(50);  // Initially to stub
            if (result != RESULT_SUCCESS) {
                current_state = STATE_EMERGENCY;
            }
            break;
        }
        
        case STATE_EMERGENCY: {
            actuator_service_apply_brake(100);  // Full brake (to stub initially)
            break;
        }
        
        default:
            break;
    }
    
    return RESULT_SUCCESS;
}

// ============================================================================
// INTEGRATION STEP 1: Use stubs for all lower levels
// File: sensor_service_stub.c

#include "sensor_service.h"

// Stub implementation for initial integration
static uint16_t stub_speed = 0;

result_t sensor_service_init(void) {
    // Stub: Just return success
    stub_speed = 50;  // Default test value
    return RESULT_SUCCESS;
}

uint16_t sensor_service_get_speed(void) {
    // Stub: Return predictable value for controller testing
    return stub_speed;
}

void sensor_service_stub_set_speed(uint16_t speed) {
    // Test helper for stub
    stub_speed = speed;
}

// ============================================================================
// INTEGRATION STEP 2: Replace sensor service stub with real implementation
// (Remove sensor_service_stub.c, link real sensor_service.c)

// File: sensor_service.c (REAL implementation)
#include "sensor_service.h"
#include "sensor_driver.h"  // Still stubbed at this step

static uint16_t current_speed = 0;

result_t sensor_service_init(void) {
    result_t result = sensor_driver_init();  // Call to driver (still stub)
    if (result != RESULT_SUCCESS) {
        return result;
    }
    current_speed = 0;
    return RESULT_SUCCESS;
}

uint16_t sensor_service_get_speed(void) {
    // Real implementation: read from driver (driver still stubbed)
    uint16_t raw_value;
    result_t result = sensor_driver_read(&raw_value);
    
    if (result == RESULT_SUCCESS) {
        current_speed = convert_raw_to_speed(raw_value);
    } else {
        current_speed = SENSOR_ERROR_VALUE;
    }
    
    return current_speed;
}

// ============================================================================
// INTEGRATION STEP 3: Replace driver stub with real implementation
// (Remove sensor_driver_stub.c, link real sensor_driver.c)

// File: sensor_driver.c (REAL implementation)
#include "sensor_driver.h"
#include "hardware_regs.h"  // Real hardware access

result_t sensor_driver_init(void) {
    // Real implementation: Initialize hardware
    HW_REG_SENSOR_CTRL = SENSOR_ENABLE;
    return RESULT_SUCCESS;
}

result_t sensor_driver_read(uint16_t* value) {
    if (value == NULL) {
        return RESULT_ERROR_NULL_PTR;
    }
    
    // Real implementation: Read hardware register
    *value = HW_REG_SENSOR_DATA;
    return RESULT_SUCCESS;
}
```

**Integration Test Sequence (Top-Down)**:

```c
// Step 1: Test controller with all stubs
// File: test_integration_step1_controller_with_stubs.c

void test_step1_controller_state_machine(void) {
    // All lower levels are stubs
    result_t result = main_controller_init();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Test: Normal monitoring state
    sensor_service_stub_set_speed(50);  // Stub control
    result = main_controller_cycle();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    TEST_ASSERT_EQUAL(STATE_MONITORING, main_controller_get_state());
    
    // Test: Transition to braking
    sensor_service_stub_set_speed(CRITICAL_SPEED + 10);  // Stub control
    result = main_controller_cycle();
    TEST_ASSERT_EQUAL(STATE_BRAKING, main_controller_get_state());
}

// Step 2: Test controller with real sensor service (driver still stub)
// File: test_integration_step2_controller_with_real_service.c

void test_step2_controller_with_real_sensor_service(void) {
    // Sensor service is REAL, driver is STUB
    result_t result = main_controller_init();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Configure driver stub to return specific value
    sensor_driver_stub_set_value(RAW_VALUE_100KMH);
    
    // Controller → Real Service → Stub Driver
    result = main_controller_cycle();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Verify service processes stubbed driver data
    uint16_t speed = sensor_service_get_speed();
    TEST_ASSERT_EQUAL(100, speed);  // Service converts raw to km/h
}

// Step 3: Test fully integrated system (all real implementations)
// File: test_integration_step3_full_system.c

void test_step3_full_integration(void) {
    // All components are REAL
    result_t result = main_controller_init();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Full integration: Controller → Service → Driver → Hardware
    result = main_controller_cycle();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Verify end-to-end behavior with real hardware
    // (May use hardware simulator or target hardware)
}
```

**Stub Design Guidelines (SIL 2+)**:

```c
// Good stub design: Simple, predictable, controllable

// File: sensor_driver_stub.h
#ifndef SENSOR_DRIVER_STUB_H
#define SENSOR_DRIVER_STUB_H

#include "sensor_driver.h"  // Same interface as real driver

// Stub control functions (for testing only)
void sensor_driver_stub_set_value(uint16_t value);
void sensor_driver_stub_set_error(result_t error);
void sensor_driver_stub_reset(void);

#endif

// File: sensor_driver_stub.c
#include "sensor_driver_stub.h"

static uint16_t stub_value = 0;
static result_t stub_error = RESULT_SUCCESS;

// Implements same interface as real driver
result_t sensor_driver_init(void) {
    stub_value = 0;
    stub_error = RESULT_SUCCESS;
    return RESULT_SUCCESS;
}

result_t sensor_driver_read(uint16_t* value) {
    if (value == NULL) {
        return RESULT_ERROR_NULL_PTR;  // Same validation as real driver
    }
    
    if (stub_error != RESULT_SUCCESS) {
        return stub_error;  // Simulate error
    }
    
    *value = stub_value;
    return RESULT_SUCCESS;
}

// Stub control functions
void sensor_driver_stub_set_value(uint16_t value) {
    stub_value = value;
}

void sensor_driver_stub_set_error(result_t error) {
    stub_error = error;
}

void sensor_driver_stub_reset(void) {
    stub_value = 0;
    stub_error = RESULT_SUCCESS;
}
```

**Advantages of Top-Down**:
- ✅ Critical control logic tested early
- ✅ System architecture validated early
- ✅ Early detection of design flaws in state machines
- ✅ Suitable for control-heavy systems (signaling interlocks, ATP systems)

**Disadvantages of Top-Down**:
- ❌ Complex stubs may be required
- ❌ Stub development effort can be significant
- ❌ Hardware integration delayed
- ❌ Stubs may mask interface issues

---

### 3. Sandwich Integration Strategy

**Best For**: Large railway systems, parallel development teams, complex SIL 3-4 projects

**Principle**: Simultaneously integrate bottom-up (from hardware) and top-down (from application), meeting in the middle at service layer.

```
Top Team (Top-Down):
    Application Layer → Controllers → [SERVICE LAYER] ← Meeting point
    
Bottom Team (Bottom-Up):
    Hardware → Drivers → HAL → [SERVICE LAYER] ← Meeting point
```

**Example: Railway Braking System**

```c
// ============================================================================
// TOP TEAM: Integrate top-down to service layer
// ============================================================================

// Application layer (Level 0)
// File: braking_application.c

#include "brake_controller.h"  // Level 1 (real)
#include "brake_service.h"     // Level 2 (interface to bottom team)

result_t braking_application_run(void) {
    brake_command_t command;
    
    // Compute brake command (Level 1 - real controller)
    result_t result = brake_controller_compute(&command);
    if (result != RESULT_SUCCESS) {
        return result;
    }
    
    // Send to service layer (Level 2 - interface point)
    result = brake_service_apply(command.brake_level);
    return result;
}

// Controller layer (Level 1)
// File: brake_controller.c

#include "brake_controller.h"
#include "sensor_service.h"  // Initially stubbed by top team

result_t brake_controller_compute(brake_command_t* command) {
    if (command == NULL) {
        return RESULT_ERROR_NULL_PTR;
    }
    
    // Get speed from service (stub or real depending on integration progress)
    uint16_t speed = sensor_service_get_speed();
    
    // Compute brake level (top team owns this logic)
    if (speed > 200) {
        command->brake_level = 100;  // Full brake
    } else if (speed > 100) {
        command->brake_level = 50;   // Moderate brake
    } else {
        command->brake_level = 0;    // No brake
    }
    
    return RESULT_SUCCESS;
}

// ============================================================================
// BOTTOM TEAM: Integrate bottom-up to service layer
// ============================================================================

// Service layer (Level 2 - interface between teams)
// File: brake_service.c

#include "brake_service.h"
#include "brake_driver.h"  // Level 3 (real, owned by bottom team)

result_t brake_service_init(void) {
    // Bottom team implements this using real driver
    return brake_driver_init();
}

result_t brake_service_apply(uint8_t brake_level) {
    // Bottom team implements this using real driver
    if (brake_level > 100) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    // Convert service-level command to driver-level command
    uint16_t pwm_duty = (brake_level * MAX_PWM_DUTY) / 100;
    
    return brake_driver_set_pwm(pwm_duty);
}

// Driver layer (Level 3)
// File: brake_driver.c

#include "brake_driver.h"
#include "hardware_regs.h"  // Real hardware

result_t brake_driver_init(void) {
    // Bottom team implements hardware initialization
    HW_REG_BRAKE_PWM_CTRL = PWM_ENABLE;
    HW_REG_BRAKE_PWM_FREQ = PWM_FREQ_1KHZ;
    return RESULT_SUCCESS;
}

result_t brake_driver_set_pwm(uint16_t duty_cycle) {
    if (duty_cycle > MAX_PWM_DUTY) {
        return RESULT_ERROR_INVALID_PARAM;
    }
    
    HW_REG_BRAKE_PWM_DUTY = duty_cycle;
    return RESULT_SUCCESS;
}
```

**Integration Test Sequence (Sandwich)**:

```c
// TOP TEAM: Test application + controller with service stub
// File: test_integration_top_team.c

void test_top_team_application_to_controller(void) {
    // Top team tests with stubbed service
    brake_service_stub_init();
    
    result_t result = braking_application_run();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Verify controller computed correct brake level
    uint8_t brake_level = brake_service_stub_get_last_command();
    TEST_ASSERT_TRUE(brake_level <= 100);
}

// BOTTOM TEAM: Test driver + service with application stub
// File: test_integration_bottom_team.c

void test_bottom_team_service_to_driver(void) {
    // Bottom team tests with stubbed application
    result_t result = brake_service_init();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Test service using real driver
    result = brake_service_apply(50);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Verify driver set correct PWM duty cycle
    uint16_t duty = HW_REG_BRAKE_PWM_DUTY;
    TEST_ASSERT_EQUAL((50 * MAX_PWM_DUTY) / 100, duty);
}

// INTEGRATION MEETING POINT: Full system test
// File: test_integration_full_sandwich.c

void test_full_sandwich_integration(void) {
    // Both teams integrated at service layer
    result_t result = braking_application_run();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Verify end-to-end: Application → Controller → Service → Driver → Hardware
    uint16_t pwm_duty = HW_REG_BRAKE_PWM_DUTY;
    TEST_ASSERT_TRUE(pwm_duty <= MAX_PWM_DUTY);
}
```

**Advantages of Sandwich**:
- ✅ Parallel development by multiple teams
- ✅ Early validation of both control logic AND hardware
- ✅ Clear interface contracts at service layer
- ✅ Reduced critical path (parallel work)
- ✅ Excellent for large SIL 3-4 projects

**Disadvantages of Sandwich**:
- ❌ Requires strong interface definition (service layer contract)
- ❌ Team coordination overhead
- ❌ Interface changes impact both teams

---

### 4. Big Bang Integration (NOT RECOMMENDED for SIL 2+)

**Description**: Integrate all components at once without progressive steps.

**C Example** (for reference only - avoid for SIL 2+):

```c
// All components integrated simultaneously
// File: test_integration_big_bang.c

void test_big_bang_full_system(void) {
    // Initialize ALL components at once
    sensor_driver_init();
    actuator_driver_init();
    sensor_service_init();
    actuator_service_init();
    brake_controller_init();
    main_application_init();
    
    // Test entire system
    result_t result = main_application_run();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // If this fails, very difficult to isolate root cause
}
```

**Why NOT RECOMMENDED for SIL 2+**:
- ❌ Poor defect localization (which component caused failure?)
- ❌ Violates EN 50128 Section 7.6.4.1 "progressively combining"
- ❌ High integration risk (everything fails if one component fails)
- ❌ Not auditable (no evidence of progressive validation)

**When Acceptable** (SIL 0-1 only):
- Very small systems (2-3 components)
- Prototype/proof-of-concept systems
- Non-safety-critical auxiliary functions

---

## Progressive Integration Process

### Integration Increment Planning

**EN 50128 Section 7.6.4.1**: "...progressively combining individual and previously tested components into a composite whole..."

**Integration Increment Template**:

```markdown
## Integration Increment: INC-[ID]

**Date**: [YYYY-MM-DD]
**Integrator**: [Name]
**SIL Level**: [0-4]

### Components to Integrate

| Component ID | Component Name | Version | Status |
|--------------|----------------|---------|--------|
| COMP-DRV-001 | sensor_driver.c | 1.2.0 | Unit Tested ✅ |
| COMP-SVC-002 | sensor_service.c | 1.1.0 | Unit Tested ✅ |

### Integration Order

1. Initialize sensor_driver
2. Initialize sensor_service (depends on sensor_driver)
3. Execute interface tests
4. Execute integration tests

### Interface Contracts to Verify

| Interface | Provider | Consumer | Contract Document |
|-----------|----------|----------|-------------------|
| sensor_driver_read() | sensor_driver | sensor_service | ICD-DRV-SVC-001 v1.0 |
| sensor_driver_init() | sensor_driver | sensor_service | ICD-DRV-SVC-001 v1.0 |

### Test Cases

| Test ID | Description | Expected Result |
|---------|-------------|-----------------|
| INT-001 | Service reads valid sensor data | PASS |
| INT-002 | Service handles driver error | PASS with error handling |
| INT-003 | Service detects NULL pointer | Return ERROR_NULL_PTR |

### Success Criteria

- All interface contracts verified ✅
- All integration test cases PASS ✅
- No memory leaks detected ✅
- Performance within limits ✅
- Traceability updated ✅

### Risks

| Risk | Mitigation |
|------|------------|
| Driver may return invalid data | Service validates data range |
| Driver initialization may fail | Service checks init result |

### Rollback Plan

If integration fails:
1. Revert to previous integrated baseline
2. Isolate failing component
3. Return component to implementer for fixes
4. Re-verify component unit tests
5. Re-attempt integration
```

---

### Step-by-Step Integration Example

**Scenario**: Integrate railway braking system components

**Components**:
- `brake_driver.c` (hardware control) - UNIT TESTED ✅
- `brake_service.c` (safety logic) - UNIT TESTED ✅
- `brake_controller.c` (application logic) - UNIT TESTED ✅

**Integration Sequence**:

```bash
# ============================================================================
# INCREMENT 1: Integrate brake_driver (baseline)
# ============================================================================

# Step 1.1: Verify component baseline
cd components/brake_driver
git checkout v1.2.0
make clean && make

# Step 1.2: Run unit tests (must PASS before integration)
make test
# Expected output:
# brake_driver unit tests: 15/15 PASS
# Coverage: Statement 100%, Branch 100%

# Step 1.3: Build integration test for driver alone
cd ../../integration/increment1
make integration_test_driver

# Step 1.4: Execute integration test
./integration_test_driver
# Expected: All driver interface tests PASS

# Step 1.5: Document increment 1 completion
workspace.py trace create \
    --from components \
    --to integration \
    --source-id COMP-DRV-001 \
    --target-id INC-001 \
    --rationale "Brake driver integrated as baseline for increment 1"

# ============================================================================
# INCREMENT 2: Integrate brake_service with brake_driver
# ============================================================================

# Step 2.1: Verify brake_service component
cd ../../components/brake_service
git checkout v1.1.0
make clean && make

# Step 2.2: Run unit tests
make test
# Expected: brake_service unit tests: 20/20 PASS

# Step 2.3: Build integration test (driver + service)
cd ../../integration/increment2
make integration_test_service

# Step 2.4: Execute integration test
./integration_test_service
# Expected: All service-driver interface tests PASS

# Step 2.5: Verify no memory leaks (SIL 2+)
valgrind --leak-check=full ./integration_test_service
# Expected: 0 bytes lost, 0 errors

# Step 2.6: Document increment 2 completion
workspace.py trace create \
    --from components \
    --to integration \
    --source-id COMP-SVC-002 \
    --target-id INC-002 \
    --rationale "Brake service integrated with driver"

# ============================================================================
# INCREMENT 3: Integrate brake_controller with service stack
# ============================================================================

# Step 3.1: Verify brake_controller component
cd ../../components/brake_controller
git checkout v1.0.0
make clean && make test
# Expected: brake_controller unit tests: 18/18 PASS

# Step 3.2: Build full integration (driver + service + controller)
cd ../../integration/increment3
make integration_test_full

# Step 3.3: Execute full integration test
./integration_test_full
# Expected: All integration tests PASS

# Step 3.4: Measure integration coverage (SIL 3-4)
make coverage
lcov --capture --directory . --output-file integration_coverage.info
genhtml integration_coverage.info --output-directory coverage_html

# Step 3.5: Validate coverage against SIL requirements
python3 ../../tools/check_coverage.py \
    --sil 3 \
    --coverage integration_coverage.json \
    --threshold statement:100,branch:100,condition:100

# Step 3.6: Document increment 3 completion
workspace.py trace create \
    --from components \
    --to integration \
    --source-id COMP-CTL-003 \
    --target-id INC-003 \
    --rationale "Brake controller integrated with full stack"

# ============================================================================
# INTEGRATION COMPLETE: Generate integration report
# ============================================================================

# Generate traceability report
workspace.py trace report \
    --from components \
    --to integration \
    --format markdown \
    --output evidence/integration/component_integration_trace.md

# Generate integration test summary
python3 tools/generate_integration_report.py \
    --test-results integration/increment*/test_results.xml \
    --coverage integration/increment3/integration_coverage.json \
    --output evidence/integration/Software_Integration_Test_Report.md
```

---

## Interface Testing at Integration

### Interface Contract Definition

**EN 50128 Principle**: "the components interfaces... may be adequately proven" (Section 7.6.4.1)

**C Interface Contract Example**:

```c
// File: sensor_driver.h (Interface Contract Document)

/**
 * @file sensor_driver.h
 * @brief Sensor Driver Interface Contract
 * @standard EN 50128 Section 7.6.4.1
 * @sil 3
 * @version 1.2.0
 * @date 2026-03-14
 * 
 * INTERFACE CONTRACT:
 * 
 * 1. Initialization Contract:
 *    - sensor_driver_init() MUST be called before any other function
 *    - sensor_driver_init() returns RESULT_SUCCESS on success
 *    - sensor_driver_init() returns RESULT_ERROR_HARDWARE if hardware fault
 *    - Multiple calls to sensor_driver_init() are safe (idempotent)
 * 
 * 2. Read Contract:
 *    - sensor_driver_read() requires valid non-NULL pointer
 *    - sensor_driver_read() returns RESULT_SUCCESS with valid data
 *    - sensor_driver_read() returns RESULT_ERROR_NULL_PTR if value == NULL
 *    - sensor_driver_read() returns RESULT_ERROR_NOT_READY if not initialized
 *    - sensor_driver_read() writes value in range [0, 1023]
 * 
 * 3. Error Handling Contract:
 *    - All functions return result_t error code
 *    - Functions NEVER modify output parameters on error
 *    - Functions validate all input parameters
 * 
 * 4. Thread Safety Contract:
 *    - Functions are NOT thread-safe (caller must synchronize)
 * 
 * 5. Memory Contract:
 *    - No dynamic memory allocation (SIL 3)
 *    - All state in static variables
 */

#ifndef SENSOR_DRIVER_H
#define SENSOR_DRIVER_H

#include "common_types.h"

/**
 * @brief Initialize sensor hardware
 * @return RESULT_SUCCESS on success
 * @return RESULT_ERROR_HARDWARE if hardware initialization fails
 * @pre None (can be called anytime)
 * @post Sensor hardware initialized and ready for reads
 * @contract Idempotent (safe to call multiple times)
 */
result_t sensor_driver_init(void);

/**
 * @brief Read current sensor value
 * @param[out] value Pointer to receive sensor reading [0, 1023]
 * @return RESULT_SUCCESS on success, value written to *value
 * @return RESULT_ERROR_NULL_PTR if value == NULL
 * @return RESULT_ERROR_NOT_READY if init not called
 * @pre sensor_driver_init() called successfully
 * @post On success: *value contains valid sensor reading
 * @post On error: *value unchanged
 * @contract NEVER writes to value on error
 */
result_t sensor_driver_read(uint16_t* value);

#endif  // SENSOR_DRIVER_H
```

**Integration Test for Interface Contract**:

```c
// File: test_integration_sensor_driver_contract.c

#include "sensor_driver.h"
#include "unity.h"

// ============================================================================
// CONTRACT TESTS: Initialization Contract
// ============================================================================

void test_contract_init_returns_success(void) {
    // Contract: sensor_driver_init() returns RESULT_SUCCESS on success
    result_t result = sensor_driver_init();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
}

void test_contract_init_idempotent(void) {
    // Contract: Multiple calls to init are safe (idempotent)
    result_t result1 = sensor_driver_init();
    result_t result2 = sensor_driver_init();
    result_t result3 = sensor_driver_init();
    
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result1);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result2);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result3);
}

// ============================================================================
// CONTRACT TESTS: Read Contract
// ============================================================================

void test_contract_read_requires_init(void) {
    // Contract: read() returns ERROR_NOT_READY if init not called
    
    // Reset driver state (simulate power-on)
    sensor_driver_reset_for_test();
    
    uint16_t value = 0xFFFF;  // Sentinel value
    result_t result = sensor_driver_read(&value);
    
    TEST_ASSERT_EQUAL(RESULT_ERROR_NOT_READY, result);
    TEST_ASSERT_EQUAL(0xFFFF, value);  // Unchanged on error
}

void test_contract_read_validates_null_pointer(void) {
    // Contract: read() returns ERROR_NULL_PTR if value == NULL
    sensor_driver_init();
    
    result_t result = sensor_driver_read(NULL);
    TEST_ASSERT_EQUAL(RESULT_ERROR_NULL_PTR, result);
}

void test_contract_read_returns_success_with_valid_data(void) {
    // Contract: read() returns SUCCESS and writes valid data
    sensor_driver_init();
    
    uint16_t value;
    result_t result = sensor_driver_read(&value);
    
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    TEST_ASSERT_TRUE(value >= 0);      // Contract: [0, 1023]
    TEST_ASSERT_TRUE(value <= 1023);   // Contract: [0, 1023]
}

void test_contract_read_does_not_modify_on_error(void) {
    // Contract: read() NEVER modifies output parameter on error
    sensor_driver_init();
    
    uint16_t value = 0xDEAD;  // Sentinel value
    result_t result = sensor_driver_read(NULL);  // Will fail
    
    // Verify sentinel unchanged (demonstrates contract violation if changed)
    TEST_ASSERT_EQUAL(0xDEAD, value);
}

// ============================================================================
// CONTRACT TESTS: Memory Contract
// ============================================================================

void test_contract_no_dynamic_allocation(void) {
    // Contract: No dynamic memory allocation (SIL 3)
    
    // Enable heap usage tracking
    enable_heap_tracker();
    
    sensor_driver_init();
    
    uint16_t value;
    for (int i = 0; i < 100; i++) {
        sensor_driver_read(&value);
    }
    
    // Verify zero heap allocations
    size_t heap_bytes = get_heap_usage();
    TEST_ASSERT_EQUAL(0, heap_bytes);  // Contract: no malloc/free
}

// ============================================================================
// CONTRACT TESTS: Thread Safety Contract
// ============================================================================

void test_contract_not_thread_safe_documented(void) {
    // Contract: Functions are NOT thread-safe
    // (This is a documentation test - verify contract clearly states this)
    
    // If multi-threaded access required, caller must use mutex
    // This test documents expected behavior, not a functional test
    
    TEST_PASS_MESSAGE("Contract states: NOT thread-safe, caller must synchronize");
}
```

---

### Data Flow Testing Across Interfaces

```c
// Test data integrity across component boundaries

void test_dataflow_sensor_to_controller(void) {
    // Initialize integration stack
    sensor_driver_init();
    sensor_service_init();
    brake_controller_init();
    
    // STEP 1: Inject known value at lowest level (driver)
    sensor_driver_test_set_value(512);  // Test helper
    
    // STEP 2: Read through service layer
    sensor_service_update();
    uint16_t service_speed = sensor_service_get_speed();
    
    // STEP 3: Compute through controller
    brake_command_t command;
    brake_controller_compute(&command);
    
    // VERIFY: Data flowed correctly through all layers
    // Driver: 512 (raw ADC value)
    // Service: 100 km/h (converted: 512 * 200 / 1023 ≈ 100)
    // Controller: 50% brake (for 100 km/h)
    
    TEST_ASSERT_EQUAL(100, service_speed);
    TEST_ASSERT_EQUAL(50, command.brake_level);
}

void test_dataflow_error_propagation(void) {
    // Test error propagates correctly up the stack
    
    sensor_driver_init();
    sensor_service_init();
    brake_controller_init();
    
    // STEP 1: Inject error at driver level
    sensor_driver_test_set_error(RESULT_ERROR_HARDWARE);
    
    // STEP 2: Service should detect error
    result_t service_result = sensor_service_update();
    TEST_ASSERT_EQUAL(RESULT_ERROR_HARDWARE, service_result);
    
    // STEP 3: Controller should handle service error
    brake_command_t command;
    result_t controller_result = brake_controller_compute(&command);
    TEST_ASSERT_EQUAL(RESULT_ERROR_SENSOR_FAULT, controller_result);
    
    // STEP 4: Verify safe state
    TEST_ASSERT_EQUAL(100, command.brake_level);  // Full brake on error
}
```

---

## Build System Integration

### Makefile for Progressive Integration

```makefile
# Makefile for progressive component integration (EN 50128 Section 7.6.4.1)
# SIL 3 Railway Braking System

# ===========================================================================
# Configuration
# ===========================================================================

PROJECT := railway_brake_system
SIL_LEVEL := 3

CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Werror -pedantic
CFLAGS += -O0 -g -fprofile-arcs -ftest-coverage  # Coverage for SIL 3
CFLAGS += -DSIL_LEVEL=$(SIL_LEVEL)

INCLUDE_DIRS := -Iinclude -Icomponents/common
LDFLAGS := -lgcov

# Component directories
COMP_DRIVER := components/brake_driver
COMP_SERVICE := components/brake_service
COMP_CONTROLLER := components/brake_controller

# Integration test directories
INT_INC1 := integration/increment1
INT_INC2 := integration/increment2
INT_INC3 := integration/increment3

# Unity test framework
UNITY_DIR := third_party/Unity
UNITY_SRC := $(UNITY_DIR)/src/unity.c

# ===========================================================================
# Integration Targets (Progressive Integration)
# ===========================================================================

.PHONY: all increment1 increment2 increment3 full_integration

all: full_integration

# ---------------------------------------------------------------------------
# INCREMENT 1: Integrate brake_driver (baseline)
# ---------------------------------------------------------------------------

increment1: $(INT_INC1)/integration_test_driver
	@echo "==================================================================="
	@echo "INCREMENT 1: Testing brake_driver (baseline)"
	@echo "==================================================================="
	$(INT_INC1)/integration_test_driver
	@echo "INCREMENT 1: PASS ✅"

$(INT_INC1)/integration_test_driver: $(COMP_DRIVER)/brake_driver.c \
                                      $(INT_INC1)/test_integration_driver.c \
                                      $(UNITY_SRC)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -I$(COMP_DRIVER) \
	    $(COMP_DRIVER)/brake_driver.c \
	    $(INT_INC1)/test_integration_driver.c \
	    $(UNITY_SRC) \
	    $(LDFLAGS) -o $@

# ---------------------------------------------------------------------------
# INCREMENT 2: Integrate brake_service with brake_driver
# ---------------------------------------------------------------------------

increment2: $(INT_INC2)/integration_test_service
	@echo "==================================================================="
	@echo "INCREMENT 2: Testing brake_service + brake_driver"
	@echo "==================================================================="
	$(INT_INC2)/integration_test_service
	@echo "INCREMENT 2: PASS ✅"

$(INT_INC2)/integration_test_service: $(COMP_DRIVER)/brake_driver.c \
                                       $(COMP_SERVICE)/brake_service.c \
                                       $(INT_INC2)/test_integration_service.c \
                                       $(UNITY_SRC)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) \
	    -I$(COMP_DRIVER) -I$(COMP_SERVICE) \
	    $(COMP_DRIVER)/brake_driver.c \
	    $(COMP_SERVICE)/brake_service.c \
	    $(INT_INC2)/test_integration_service.c \
	    $(UNITY_SRC) \
	    $(LDFLAGS) -o $@

# ---------------------------------------------------------------------------
# INCREMENT 3: Integrate brake_controller with full stack
# ---------------------------------------------------------------------------

increment3: $(INT_INC3)/integration_test_full
	@echo "==================================================================="
	@echo "INCREMENT 3: Testing full integration stack"
	@echo "==================================================================="
	$(INT_INC3)/integration_test_full
	@echo "INCREMENT 3: PASS ✅"

$(INT_INC3)/integration_test_full: $(COMP_DRIVER)/brake_driver.c \
                                    $(COMP_SERVICE)/brake_service.c \
                                    $(COMP_CONTROLLER)/brake_controller.c \
                                    $(INT_INC3)/test_integration_full.c \
                                    $(UNITY_SRC)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) \
	    -I$(COMP_DRIVER) -I$(COMP_SERVICE) -I$(COMP_CONTROLLER) \
	    $(COMP_DRIVER)/brake_driver.c \
	    $(COMP_SERVICE)/brake_service.c \
	    $(COMP_CONTROLLER)/brake_controller.c \
	    $(INT_INC3)/test_integration_full.c \
	    $(UNITY_SRC) \
	    $(LDFLAGS) -o $@

# ---------------------------------------------------------------------------
# FULL INTEGRATION: Run all increments in sequence
# ---------------------------------------------------------------------------

full_integration: increment1 increment2 increment3
	@echo "==================================================================="
	@echo "FULL INTEGRATION COMPLETE ✅"
	@echo "==================================================================="
	@$(MAKE) coverage_report

# ===========================================================================
# Coverage Analysis (MANDATORY SIL 3)
# ===========================================================================

.PHONY: coverage_report

coverage_report:
	@echo "Generating coverage report (SIL 3 requirement)..."
	lcov --capture --directory $(INT_INC3) --output-file integration_coverage.info
	lcov --remove integration_coverage.info '/usr/*' 'third_party/*' \
	    --output-file integration_coverage_filtered.info
	genhtml integration_coverage_filtered.info --output-directory coverage_html
	@echo "Coverage report: coverage_html/index.html"
	
	@echo "Validating coverage against SIL 3 requirements..."
	python3 tools/check_coverage.py \
	    --sil 3 \
	    --coverage integration_coverage.json \
	    --threshold statement:100,branch:100,condition:100

# ===========================================================================
# Memory Leak Detection (MANDATORY SIL 2+)
# ===========================================================================

.PHONY: memcheck

memcheck: $(INT_INC3)/integration_test_full
	@echo "Running Valgrind memory leak detection (SIL 2+ requirement)..."
	valgrind --leak-check=full --show-leak-kinds=all \
	    --track-origins=yes --verbose \
	    --log-file=valgrind_integration.log \
	    $(INT_INC3)/integration_test_full
	@echo "Valgrind report: valgrind_integration.log"
	@grep "ERROR SUMMARY: 0 errors" valgrind_integration.log || \
	    (echo "❌ Memory errors detected!" && exit 1)
	@grep "definitely lost: 0 bytes" valgrind_integration.log || \
	    (echo "❌ Memory leaks detected!" && exit 1)
	@echo "✅ No memory leaks detected"

# ===========================================================================
# Clean
# ===========================================================================

.PHONY: clean

clean:
	rm -f $(INT_INC1)/integration_test_driver
	rm -f $(INT_INC2)/integration_test_service
	rm -f $(INT_INC3)/integration_test_full
	rm -f *.gcda *.gcno *.gcov
	rm -f integration_coverage.info integration_coverage_filtered.info
	rm -rf coverage_html
	rm -f valgrind_integration.log
	@echo "Clean complete"
```

**Usage**:

```bash
# Run progressive integration (all increments)
make full_integration

# Run specific increment
make increment1
make increment2
make increment3

# Check memory leaks (SIL 2+)
make memcheck

# Generate coverage report (SIL 3-4)
make coverage_report

# Clean build artifacts
make clean
```

---

## Integration Test Execution

### Test Execution Script

```python
#!/usr/bin/env python3
"""
Integration Test Execution Script
EN 50128 Section 7.6.4.5 - Machine-readable test results
"""

import subprocess
import json
import sys
from datetime import datetime
from pathlib import Path

class IntegrationTestExecutor:
    def __init__(self, sil_level, test_spec_path):
        self.sil_level = sil_level
        self.test_spec = self.load_test_spec(test_spec_path)
        self.results = []
        
    def load_test_spec(self, path):
        """Load integration test specification (JSON format)"""
        with open(path, 'r') as f:
            return json.load(f)
    
    def execute_increment(self, increment_id):
        """Execute integration tests for one increment"""
        print(f"\\n{'='*70}")
        print(f"Executing Integration Increment: {increment_id}")
        print(f"{'='*70}\\n")
        
        increment = self.test_spec['increments'][increment_id]
        
        # Build integration test
        print(f"Building integration test...")
        build_cmd = increment['build_command']
        result = subprocess.run(build_cmd, shell=True, capture_output=True, text=True)
        
        if result.returncode != 0:
            print(f"❌ Build FAILED")
            print(result.stderr)
            return False
        
        print(f"✅ Build SUCCESS")
        
        # Execute integration test
        print(f"\\nExecuting integration test...")
        test_cmd = increment['test_executable']
        start_time = datetime.now()
        result = subprocess.run(test_cmd, shell=True, capture_output=True, text=True)
        end_time = datetime.now()
        execution_time = (end_time - start_time).total_seconds()
        
        # Parse test results (Unity framework output)
        passed, failed, total = self.parse_unity_output(result.stdout)
        
        increment_result = {
            'increment_id': increment_id,
            'timestamp': start_time.isoformat(),
            'execution_time_seconds': execution_time,
            'tests_total': total,
            'tests_passed': passed,
            'tests_failed': failed,
            'return_code': result.returncode,
            'stdout': result.stdout,
            'stderr': result.stderr,
            'status': 'PASS' if result.returncode == 0 else 'FAIL'
        }
        
        self.results.append(increment_result)
        
        if result.returncode == 0:
            print(f"✅ {passed}/{total} tests PASSED")
            return True
        else:
            print(f"❌ {failed}/{total} tests FAILED")
            print(result.stdout)
            return False
    
    def parse_unity_output(self, output):
        """Parse Unity test framework output"""
        # Unity output format: "X Tests Y Failures Z Ignored"
        lines = output.split('\\n')
        for line in lines:
            if 'Tests' in line and 'Failures' in line:
                parts = line.split()
                total = int(parts[0])
                failures = int(parts[2])
                passed = total - failures
                return passed, failures, total
        return 0, 0, 0
    
    def check_coverage(self, increment_id):
        """Check code coverage for SIL 3-4"""
        if self.sil_level < 3:
            print(f"\\nCoverage check not required for SIL {self.sil_level}")
            return True
        
        print(f"\\nChecking coverage (SIL {self.sil_level} requirement)...")
        
        # Generate coverage data
        subprocess.run(['lcov', '--capture', '--directory', '.', 
                       '--output-file', f'coverage_{increment_id}.info'],
                      capture_output=True)
        
        # Convert to JSON for validation
        subprocess.run(['gcovr', '--json', '--output', f'coverage_{increment_id}.json'],
                      capture_output=True)
        
        # Validate against SIL requirements
        cmd = [
            'python3', 'tools/check_coverage.py',
            '--sil', str(self.sil_level),
            '--coverage', f'coverage_{increment_id}.json',
            '--threshold', 'statement:100,branch:100,condition:100'
        ]
        
        result = subprocess.run(cmd, capture_output=True, text=True)
        
        if result.returncode == 0:
            print(f"✅ Coverage requirements MET")
            return True
        else:
            print(f"❌ Coverage requirements NOT MET")
            print(result.stdout)
            return False
    
    def check_memory_leaks(self, increment_id):
        """Check for memory leaks (SIL 2+)"""
        if self.sil_level < 2:
            print(f"\\nMemory leak check not required for SIL {self.sil_level}")
            return True
        
        print(f"\\nChecking memory leaks (SIL {self.sil_level} requirement)...")
        
        increment = self.test_spec['increments'][increment_id]
        test_exe = increment['test_executable']
        
        cmd = [
            'valgrind',
            '--leak-check=full',
            '--show-leak-kinds=all',
            '--error-exitcode=1',
            test_exe
        ]
        
        result = subprocess.run(cmd, capture_output=True, text=True)
        
        if result.returncode == 0:
            print(f"✅ No memory leaks detected")
            return True
        else:
            print(f"❌ Memory leaks detected")
            print(result.stderr)
            return False
    
    def generate_report(self, output_path):
        """Generate machine-readable integration test report (EN 50128 7.6.4.5b)"""
        report = {
            'project': 'Railway Braking System',
            'sil_level': self.sil_level,
            'test_specification': self.test_spec['metadata']['test_spec_id'],
            'test_specification_version': self.test_spec['metadata']['version'],
            'execution_timestamp': datetime.now().isoformat(),
            'integrator': self.test_spec['metadata']['integrator'],
            'increments': self.results,
            'summary': {
                'total_increments': len(self.results),
                'passed_increments': sum(1 for r in self.results if r['status'] == 'PASS'),
                'failed_increments': sum(1 for r in self.results if r['status'] == 'FAIL'),
                'total_tests': sum(r['tests_total'] for r in self.results),
                'passed_tests': sum(r['tests_passed'] for r in self.results),
                'failed_tests': sum(r['tests_failed'] for r in self.results)
            }
        }
        
        # Write JSON report (machine-readable per EN 50128 7.6.4.5b)
        with open(output_path, 'w') as f:
            json.dump(report, f, indent=2)
        
        print(f"\\n{'='*70}")
        print(f"Integration Test Report: {output_path}")
        print(f"{'='*70}")
        print(f"Total Increments: {report['summary']['total_increments']}")
        print(f"Passed: {report['summary']['passed_increments']}")
        print(f"Failed: {report['summary']['failed_increments']}")
        print(f"Total Tests: {report['summary']['total_tests']}")
        print(f"Passed Tests: {report['summary']['passed_tests']}")
        print(f"Failed Tests: {report['summary']['failed_tests']}")
        
        return report['summary']['failed_increments'] == 0

def main():
    if len(sys.argv) < 3:
        print("Usage: execute_integration_tests.py <SIL_LEVEL> <TEST_SPEC_JSON>")
        sys.exit(1)
    
    sil_level = int(sys.argv[1])
    test_spec_path = sys.argv[2]
    
    executor = IntegrationTestExecutor(sil_level, test_spec_path)
    
    all_passed = True
    
    # Execute all increments progressively
    for increment_id in executor.test_spec['increments'].keys():
        # Execute integration tests
        if not executor.execute_increment(increment_id):
            print(f"\\n❌ Increment {increment_id} FAILED - stopping integration")
            all_passed = False
            break
        
        # Check coverage (SIL 3-4)
        if not executor.check_coverage(increment_id):
            print(f"\\n❌ Coverage check FAILED for increment {increment_id}")
            all_passed = False
            break
        
        # Check memory leaks (SIL 2+)
        if not executor.check_memory_leaks(increment_id):
            print(f"\\n❌ Memory leak check FAILED for increment {increment_id}")
            all_passed = False
            break
    
    # Generate final report
    success = executor.generate_report('evidence/integration/integration_test_results.json')
    
    if success and all_passed:
        print(f"\\n✅ ALL INTEGRATION TESTS PASSED")
        sys.exit(0)
    else:
        print(f"\\n❌ INTEGRATION TESTS FAILED")
        sys.exit(1)

if __name__ == '__main__':
    main()
```

**Test Specification Example** (`integration_test_spec.json`):

```json
{
  "metadata": {
    "test_spec_id": "ITS-BRAKE-001",
    "version": "1.0.0",
    "date": "2026-03-14",
    "integrator": "Jane Smith",
    "sil_level": 3,
    "project": "Railway Braking System"
  },
  "increments": {
    "INC-001": {
      "description": "Integrate brake_driver (baseline)",
      "build_command": "make increment1",
      "test_executable": "./integration/increment1/integration_test_driver",
      "components": ["COMP-DRV-001"]
    },
    "INC-002": {
      "description": "Integrate brake_service with brake_driver",
      "build_command": "make increment2",
      "test_executable": "./integration/increment2/integration_test_service",
      "components": ["COMP-DRV-001", "COMP-SVC-002"]
    },
    "INC-003": {
      "description": "Integrate brake_controller with full stack",
      "build_command": "make increment3",
      "test_executable": "./integration/increment3/integration_test_full",
      "components": ["COMP-DRV-001", "COMP-SVC-002", "COMP-CTL-003"]
    }
  }
}
```

**Execution**:

```bash
# Run progressive integration tests
python3 tools/execute_integration_tests.py 3 integration_test_spec.json

# Output (example):
# ======================================================================
# Executing Integration Increment: INC-001
# ======================================================================
# 
# Building integration test...
# ✅ Build SUCCESS
# 
# Executing integration test...
# ✅ 12/12 tests PASSED
# 
# Checking coverage (SIL 3 requirement)...
# ✅ Coverage requirements MET
# 
# Checking memory leaks (SIL 3 requirement)...
# ✅ No memory leaks detected
# 
# ======================================================================
# Executing Integration Increment: INC-002
# ======================================================================
# ...
# 
# ======================================================================
# Integration Test Report: evidence/integration/integration_test_results.json
# ======================================================================
# Total Increments: 3
# Passed: 3
# Failed: 0
# Total Tests: 45
# Passed Tests: 45
# Failed Tests: 0
# 
# ✅ ALL INTEGRATION TESTS PASSED
```

---

## Defect Management and Re-integration

### Integration Defect Classification

**EN 50128 Section 7.6.4.5a**: "If there is a failure, the circumstances for the failure shall be recorded"

**Defect Categories**:

| Category | Description | Example | Impact | Re-integration Required |
|----------|-------------|---------|--------|-------------------------|
| **Interface Violation** | Component violates interface contract | NULL pointer not checked | HIGH | **Yes** - component unit tests inadequate |
| **Data Corruption** | Data corrupted across boundary | Wrong byte order | HIGH | **Yes** - interface design flaw |
| **Timing Issue** | Performance/timing violation | Timeout too short | MEDIUM | **Maybe** - configuration change |
| **Resource Leak** | Memory/resource leak detected | Missing free() | HIGH (SIL 2+) | **Yes** - component defect |
| **Configuration Error** | Wrong build settings | Wrong optimization level | LOW | **No** - rebuild only |
| **Test Defect** | Test case itself is wrong | Wrong expected value | LOW | **No** - fix test |

**Defect Report Template**:

```markdown
## Integration Defect Report: ID-[ID]

**Date**: [YYYY-MM-DD]  
**Severity**: [Critical|High|Medium|Low]  
**Category**: [Interface Violation|Data Corruption|Timing|Resource Leak|Config|Test]  
**SIL Level**: [0-4]

### Failure Circumstances (EN 50128 7.6.4.5a)

**Increment**: [INC-ID]  
**Test Case**: [TEST-ID]  
**Components Involved**: [List]

**Failure Description**:
[Describe what failed, when, under what conditions]

**Failure Output**:
```
[Test output showing failure]
```

**Root Cause Analysis**:
[What caused the failure - which component, which line of code]

### Impact Analysis (EN 50128 7.6.4.2)

**Impacted Components**: [List all affected components]  
**Impacted Tests**: [List tests that need re-execution]  
**Impacted Documentation**: [Interface specs, design docs]

### Remediation Plan

**Action Required**: [Fix component|Fix test|Rebuild|Reconfigure]  
**Assigned To**: [Developer name]  
**Target Date**: [YYYY-MM-DD]

**Fix Strategy**:
1. [Step 1]
2. [Step 2]
...

### Re-integration Plan

**Re-verification Required**:
- [ ] Component unit tests
- [ ] Interface contract tests
- [ ] Integration tests for this increment
- [ ] Regression tests for previous increments
- [ ] Coverage analysis
- [ ] Memory leak check

**Success Criteria**:
- All tests PASS
- No new defects introduced
- Coverage targets met (SIL 3-4)
- Traceability updated

**Approvals**:
- Integrator: [Name, Date]
- Verifier: [Name, Date] (SIL 3-4)
```

**Example Defect**:

```markdown
## Integration Defect Report: ID-2026-001

**Date**: 2026-03-14  
**Severity**: High  
**Category**: Interface Violation  
**SIL Level**: 3

### Failure Circumstances

**Increment**: INC-002  
**Test Case**: INT-SVC-004 (Service handles driver NULL response)  
**Components Involved**: brake_service.c, brake_driver.c

**Failure Description**:
During integration testing of brake_service with brake_driver, discovered that 
brake_service does NOT check for NULL pointer returned by brake_driver_get_status().
This violates defensive programming requirements (EN 50128 Table A.3 #14, HR for SIL 3).

**Failure Output**:
```
test_service_handles_driver_null_response: FAIL
  Expected: RESULT_ERROR_NULL_PTR
  Actual:   SEGMENTATION FAULT
  File: test_integration_service.c:145
```

**Root Cause Analysis**:
File: brake_service.c, line 78
```c
status_t* status = brake_driver_get_status();  // May return NULL
if (status->code == STATUS_OK) {  // ❌ CRASH if status == NULL
    ...
}
```

Missing NULL pointer check violates interface contract. Component unit tests
did not cover this case (test gap).

### Impact Analysis

**Impacted Components**: 
- brake_service.c (requires fix)
- test_brake_service.c (unit tests insufficient)

**Impacted Tests**: 
- INT-SVC-004 (currently failing)
- INT-SVC-005 to INT-SVC-010 (may also be affected)
- All tests in INC-003 (cannot proceed until fixed)

**Impacted Documentation**: 
- Software Design Specification (brake_service error handling)
- Interface Control Document ICD-DRV-SVC-001 (clarify NULL return)

### Remediation Plan

**Action Required**: Fix component (brake_service.c)  
**Assigned To**: John Doe (implementer)  
**Target Date**: 2026-03-15

**Fix Strategy**:
1. Add NULL pointer check in brake_service.c:78
2. Add unit test to verify NULL handling
3. Update interface documentation
4. Re-run component unit tests
5. Re-run integration increment INC-002

**Code Fix**:
```c
// File: brake_service.c, line 78 (FIXED)
status_t* status = brake_driver_get_status();
if (status == NULL) {  // ✅ Added NULL check
    return RESULT_ERROR_NULL_PTR;
}
if (status->code == STATUS_OK) {
    ...
}
```

### Re-integration Plan

**Re-verification Required**:
- [x] Component unit tests (brake_service) - PASS (15/15)
- [x] Interface contract tests - PASS (8/8)
- [x] Integration tests INC-002 - PASS (18/18)
- [x] Regression tests INC-001 - PASS (12/12)
- [x] Coverage analysis - PASS (100% statement, branch, condition)
- [x] Memory leak check - PASS (0 bytes leaked)

**Success Criteria**:
- [x] All tests PASS ✅
- [x] No new defects introduced ✅
- [x] Coverage targets met (SIL 3) ✅
- [x] Traceability updated ✅

**Approvals**:
- Integrator: Jane Smith, 2026-03-15
- Verifier: Alice Johnson, 2026-03-15
```

---

## Integration Evidence Collection

### Evidence Required (EN 50128 Section 7.6.4.5)

**Per EN 50128 Section 7.6.4.5**, Software Integration Test Report SHALL include:

1. **Test Results** (7.6.4.5a): Whether objectives met, pass/fail status, failure circumstances
2. **Test Cases** (7.6.4.5b): Machine-readable format preferred
3. **Repeatability** (7.6.4.5c): Automated execution
4. **Configuration** (7.6.4.5d): Identity and configuration of all integrated items

**Evidence Collection Script**:

```bash
#!/bin/bash
# collect_integration_evidence.sh
# Collects evidence for EN 50128 Section 7.6.4.5 compliance

set -e

PROJECT="Railway Braking System"
SIL_LEVEL=3
EVIDENCE_DIR="evidence/integration"
TIMESTAMP=$(date +%Y%m%d_%H%M%S)

echo "======================================================================="
echo "Collecting Integration Evidence (EN 50128 Section 7.6.4.5)"
echo "Project: $PROJECT"
echo "SIL Level: $SIL_LEVEL"
echo "======================================================================="

# Create evidence directory
mkdir -p $EVIDENCE_DIR

# ---------------------------------------------------------------------------
# 1. Test Results (7.6.4.5a) - Machine-readable format
# ---------------------------------------------------------------------------

echo "1. Collecting test results (machine-readable)..."

# Execute integration tests with JSON output
python3 tools/execute_integration_tests.py $SIL_LEVEL \
    integration_test_spec.json \
    > $EVIDENCE_DIR/integration_execution_log_$TIMESTAMP.txt

# Copy machine-readable results
cp evidence/integration/integration_test_results.json \
    $EVIDENCE_DIR/integration_test_results_$TIMESTAMP.json

echo "   ✅ Test results: $EVIDENCE_DIR/integration_test_results_$TIMESTAMP.json"

# ---------------------------------------------------------------------------
# 2. Test Cases (7.6.4.5b) - Preferably machine-readable
# ---------------------------------------------------------------------------

echo "2. Collecting test case specifications..."

# Export test cases from integration test specification
cp integration_test_spec.json \
    $EVIDENCE_DIR/integration_test_specification_$TIMESTAMP.json

# Generate test case traceability
workspace.py trace report \
    --from requirements \
    --to integration_tests \
    --format json \
    --output $EVIDENCE_DIR/test_case_traceability_$TIMESTAMP.json

echo "   ✅ Test cases: $EVIDENCE_DIR/integration_test_specification_$TIMESTAMP.json"
echo "   ✅ Traceability: $EVIDENCE_DIR/test_case_traceability_$TIMESTAMP.json"

# ---------------------------------------------------------------------------
# 3. Repeatability Evidence (7.6.4.5c) - Automated execution
# ---------------------------------------------------------------------------

echo "3. Demonstrating repeatability (automated execution)..."

# Run integration tests 3 times to demonstrate repeatability
for run in 1 2 3; do
    echo "   Run $run/3..."
    python3 tools/execute_integration_tests.py $SIL_LEVEL \
        integration_test_spec.json \
        > $EVIDENCE_DIR/repeatability_run${run}_$TIMESTAMP.txt
    
    # Verify same results
    diff $EVIDENCE_DIR/integration_test_results_$TIMESTAMP.json \
        evidence/integration/integration_test_results.json \
        && echo "   ✅ Run $run identical to baseline"
done

echo "   ✅ Repeatability: 3/3 runs produced identical results"

# ---------------------------------------------------------------------------
# 4. Configuration Documentation (7.6.4.5d) - Component versions
# ---------------------------------------------------------------------------

echo "4. Documenting component configuration..."

# Collect component versions
cat > $EVIDENCE_DIR/component_configuration_$TIMESTAMP.json <<EOF
{
  "project": "$PROJECT",
  "sil_level": $SIL_LEVEL,
  "integration_date": "$(date --iso-8601=seconds)",
  "integrator": "$(git config user.name) <$(git config user.email)>",
  "components": [
EOF

# List all integrated components with versions
for comp in components/*/; do
    comp_name=$(basename $comp)
    comp_version=$(git log -1 --format="%H" -- $comp)
    comp_date=$(git log -1 --format="%ai" -- $comp)
    
    cat >> $EVIDENCE_DIR/component_configuration_$TIMESTAMP.json <<EOF
    {
      "name": "$comp_name",
      "version": "$comp_version",
      "last_modified": "$comp_date",
      "path": "$comp"
    },
EOF
done

# Close JSON (remove trailing comma)
sed -i '$ s/,$//' $EVIDENCE_DIR/component_configuration_$TIMESTAMP.json

cat >> $EVIDENCE_DIR/component_configuration_$TIMESTAMP.json <<EOF
  ],
  "build_configuration": {
    "compiler": "$(gcc --version | head -1)",
    "compiler_flags": "$CFLAGS",
    "optimization_level": "O0",
    "coverage_enabled": true,
    "sil_level": $SIL_LEVEL
  }
}
EOF

echo "   ✅ Configuration: $EVIDENCE_DIR/component_configuration_$TIMESTAMP.json"

# ---------------------------------------------------------------------------
# 5. Coverage Evidence (MANDATORY SIL 3-4)
# ---------------------------------------------------------------------------

if [ $SIL_LEVEL -ge 3 ]; then
    echo "5. Collecting coverage evidence (SIL $SIL_LEVEL requirement)..."
    
    # Generate HTML coverage report
    lcov --capture --directory integration --output-file $EVIDENCE_DIR/integration_coverage.info
    genhtml $EVIDENCE_DIR/integration_coverage.info \
        --output-directory $EVIDENCE_DIR/coverage_html_$TIMESTAMP
    
    # Generate JSON coverage report
    gcovr --json --output $EVIDENCE_DIR/integration_coverage_$TIMESTAMP.json
    
    # Validate coverage
    python3 tools/check_coverage.py \
        --sil $SIL_LEVEL \
        --coverage $EVIDENCE_DIR/integration_coverage_$TIMESTAMP.json \
        --report $EVIDENCE_DIR/coverage_validation_$TIMESTAMP.json
    
    echo "   ✅ Coverage HTML: $EVIDENCE_DIR/coverage_html_$TIMESTAMP/index.html"
    echo "   ✅ Coverage JSON: $EVIDENCE_DIR/integration_coverage_$TIMESTAMP.json"
    echo "   ✅ Coverage validation: $EVIDENCE_DIR/coverage_validation_$TIMESTAMP.json"
fi

# ---------------------------------------------------------------------------
# 6. Memory Leak Evidence (MANDATORY SIL 2+)
# ---------------------------------------------------------------------------

if [ $SIL_LEVEL -ge 2 ]; then
    echo "6. Collecting memory leak evidence (SIL $SIL_LEVEL requirement)..."
    
    for increment in integration/increment*/integration_test_*; do
        increment_name=$(basename $increment)
        valgrind --leak-check=full --show-leak-kinds=all \
            --xml=yes --xml-file=$EVIDENCE_DIR/valgrind_${increment_name}_$TIMESTAMP.xml \
            $increment
    done
    
    echo "   ✅ Valgrind reports: $EVIDENCE_DIR/valgrind_*.xml"
fi

# ---------------------------------------------------------------------------
# 7. Traceability Evidence (MANDATORY SIL 3-4)
# ---------------------------------------------------------------------------

if [ $SIL_LEVEL -ge 3 ]; then
    echo "7. Collecting traceability evidence (SIL $SIL_LEVEL requirement)..."
    
    # Generate complete traceability chain
    workspace.py trace report \
        --from requirements \
        --to integration_tests \
        --format markdown \
        --output $EVIDENCE_DIR/requirements_to_integration_trace_$TIMESTAMP.md
    
    workspace.py trace report \
        --from components \
        --to integration_tests \
        --format markdown \
        --output $EVIDENCE_DIR/components_to_integration_trace_$TIMESTAMP.md
    
    # Validate traceability completeness
    workspace.py trace validate --phase integration --sil $SIL_LEVEL \
        > $EVIDENCE_DIR/traceability_validation_$TIMESTAMP.txt
    
    echo "   ✅ Traceability: requirements → integration"
    echo "   ✅ Traceability: components → integration"
    echo "   ✅ Traceability validation complete"
fi

# ---------------------------------------------------------------------------
# 8. Generate Integration Test Report (EN 50128 Section 7.6.4.3-7.6.4.6)
# ---------------------------------------------------------------------------

echo "8. Generating Software Integration Test Report..."

python3 tools/generate_integration_report.py \
    --test-results $EVIDENCE_DIR/integration_test_results_$TIMESTAMP.json \
    --test-spec $EVIDENCE_DIR/integration_test_specification_$TIMESTAMP.json \
    --coverage $EVIDENCE_DIR/integration_coverage_$TIMESTAMP.json \
    --configuration $EVIDENCE_DIR/component_configuration_$TIMESTAMP.json \
    --sil $SIL_LEVEL \
    --output $EVIDENCE_DIR/Software_Integration_Test_Report_$TIMESTAMP.md

echo "   ✅ Integration Test Report: $EVIDENCE_DIR/Software_Integration_Test_Report_$TIMESTAMP.md"

# ---------------------------------------------------------------------------
# Summary
# ---------------------------------------------------------------------------

echo ""
echo "======================================================================="
echo "Integration Evidence Collection COMPLETE"
echo "======================================================================="
echo "Evidence directory: $EVIDENCE_DIR"
echo ""
echo "Collected Evidence (EN 50128 Section 7.6.4.5):"
echo "  1. Test Results (7.6.4.5a): integration_test_results_$TIMESTAMP.json"
echo "  2. Test Cases (7.6.4.5b): integration_test_specification_$TIMESTAMP.json"
echo "  3. Repeatability (7.6.4.5c): repeatability_run{1,2,3}_$TIMESTAMP.txt"
echo "  4. Configuration (7.6.4.5d): component_configuration_$TIMESTAMP.json"
echo ""
if [ $SIL_LEVEL -ge 3 ]; then
    echo "Additional Evidence (SIL $SIL_LEVEL):"
    echo "  5. Coverage: integration_coverage_$TIMESTAMP.json"
    echo "  7. Traceability: *_trace_$TIMESTAMP.md"
fi
if [ $SIL_LEVEL -ge 2 ]; then
    echo "  6. Memory Leaks: valgrind_*.xml"
fi
echo ""
echo "Main Deliverable:"
echo "  Software Integration Test Report: Software_Integration_Test_Report_$TIMESTAMP.md"
echo ""
echo "✅ Ready for Verification (VER agent, EN 50128 Section 7.6.4.11-7.6.4.13)"
echo "======================================================================="
```

**Usage**:

```bash
# Collect all integration evidence
./tools/collect_integration_evidence.sh

# Output: evidence/integration/ directory with timestamped files
#   - integration_test_results_YYYYMMDD_HHMMSS.json
#   - component_configuration_YYYYMMDD_HHMMSS.json
#   - coverage_html_YYYYMMDD_HHMMSS/index.html
#   - Software_Integration_Test_Report_YYYYMMDD_HHMMSS.md
#   - (and more...)
```

---

## Tool Integration

### Working Tools for Integration

**Build and Test**:
- `gcc` - C compiler with coverage support (`-fprofile-arcs -ftest-coverage`)
- `make` - Build automation for progressive integration
- `Unity` - C test framework (third_party/Unity)

**Coverage Analysis** (SIL 3-4):
- `gcov` - Statement and branch coverage
- `lcov` - Coverage report generation (HTML)
- `gcovr` - Machine-readable coverage (JSON, XML)
- `tools/check_coverage.py` - SIL-specific coverage validation

**Memory Analysis** (SIL 2+):
- `valgrind` - Memory leak detection
- `--leak-check=full --show-leak-kinds=all`

**Traceability** (SIL 3-4):
- `workspace.py trace` - Traceability management
- `workspace.py trace create` - Link components to integration tests
- `workspace.py trace report` - Generate traceability reports
- `workspace.py trace validate` - Verify traceability completeness

**Integration Automation**:
- `tools/execute_integration_tests.py` - Automated test execution
- `tools/generate_integration_report.py` - Report generation
- `tools/collect_integration_evidence.sh` - Evidence collection

**Example Workflow**:

```bash
# 1. Progressive integration with automated testing
make full_integration

# 2. Collect evidence for EN 50128 compliance
./tools/collect_integration_evidence.sh

# 3. Validate traceability (SIL 3-4)
workspace.py trace validate --phase integration --sil 3

# 4. Generate final integration report
python3 tools/generate_integration_report.py \
    --test-results evidence/integration/integration_test_results.json \
    --coverage evidence/integration/integration_coverage.json \
    --sil 3 \
    --output evidence/integration/Software_Integration_Test_Report.md
```

---

## SIL-Specific Requirements

### SIL 0-1: Advisory Integration

**Requirements**:
- Progressive integration **recommended** (not mandatory)
- Interface testing **highly recommended**
- Documentation minimal

**Integration Approach**:
- Bottom-up or top-down acceptable
- Big Bang allowed for simple systems (<5 components)
- Manual testing acceptable

**Example**:
```bash
# SIL 0-1: Simplified integration
make all  # Build all components
make test # Run tests
# Done - no coverage/memory checks required
```

---

### SIL 2: Structured Integration

**Requirements (EN 50128)**:
- Progressive integration **highly recommended**
- Interface testing **highly recommended**
- Memory leak detection **highly recommended**
- Branch coverage **MANDATORY** (100%)

**Integration Approach**:
- Progressive strategy (bottom-up, top-down, sandwich)
- Automated testing **highly recommended**
- Valgrind memory checks
- 100% branch coverage

**Example**:
```bash
# SIL 2: Structured integration with memory checks
make full_integration
make memcheck  # Valgrind
make coverage  # Branch coverage 100%
```

---

### SIL 3-4: Rigorous Integration

**Requirements (EN 50128)**:
- Progressive integration **MANDATORY** (Section 7.6.4.1)
- Interface testing **MANDATORY**
- Independent verification **MANDATORY** (Section 7.6.4.11-7.6.4.13)
- Memory leak detection **MANDATORY**
- Statement, Branch, Condition coverage **MANDATORY** (100%)
- Traceability **MANDATORY** (Section 6.5.4.14-17)
- Machine-readable test results **MANDATORY** (Section 7.6.4.5b)
- Automated testing **highly recommended**

**Integration Approach**:
- Progressive strategy (bottom-up, top-down, sandwich) - Big Bang **NOT ALLOWED**
- Automated testing with CI/CD
- Complete coverage analysis (statement, branch, condition)
- Valgrind memory checks (0 leaks)
- Complete traceability (requirements → components → integration tests)
- Independent verifier reviews all evidence

**Example**:
```bash
# SIL 3-4: Rigorous integration with full evidence collection
make full_integration          # Progressive integration
make coverage_report           # 100% statement, branch, condition
make memcheck                  # 0 memory leaks
./tools/collect_integration_evidence.sh  # All evidence
workspace.py trace validate --phase integration --sil 3  # Traceability

# Submit to Verifier for review (EN 50128 Section 7.6.4.11-7.6.4.13)
```

---

## Example Integration Scenarios

### Example 1: Railway Braking System (SIL 3)

**System Overview**:
```
Application: Brake Application
    ↓
Controller: Brake Controller (safety logic)
    ↓
Service: Brake Service (abstraction layer)
    ↓
Driver: Brake Driver (hardware control)
    ↓
Hardware: Brake Actuator (PWM)
```

**Integration Strategy**: Bottom-Up

**Complete Integration Workflow**:

```bash
# ============================================================================
# PREPARATION: Verify all components unit tested
# ============================================================================

cd components/brake_driver
make test
# Output: 15/15 unit tests PASS, Coverage: 100% statement, 100% branch

cd ../brake_service
make test
# Output: 20/20 unit tests PASS, Coverage: 100% statement, 100% branch

cd ../brake_controller
make test
# Output: 18/18 unit tests PASS, Coverage: 100% statement, 100% branch

cd ../brake_application
make test
# Output: 12/12 unit tests PASS, Coverage: 100% statement, 100% branch

# ============================================================================
# INCREMENT 1: Integrate brake_driver (baseline)
# ============================================================================

cd ../../integration/increment1

# Create integration test
cat > test_integration_driver.c <<'EOF'
#include "brake_driver.h"
#include "unity.h"

void test_driver_init(void) {
    result_t result = brake_driver_init();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
}

void test_driver_set_pwm_valid(void) {
    brake_driver_init();
    result_t result = brake_driver_set_pwm(512);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    TEST_ASSERT_EQUAL(512, HW_REG_BRAKE_PWM_DUTY);
}

void test_driver_set_pwm_boundary(void) {
    brake_driver_init();
    
    // Boundary: 0
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, brake_driver_set_pwm(0));
    
    // Boundary: MAX
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, brake_driver_set_pwm(1023));
    
    // Boundary: MAX+1 (invalid)
    TEST_ASSERT_EQUAL(RESULT_ERROR_INVALID_PARAM, brake_driver_set_pwm(1024));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_driver_init);
    RUN_TEST(test_driver_set_pwm_valid);
    RUN_TEST(test_driver_set_pwm_boundary);
    return UNITY_END();
}
EOF

# Build and run
gcc -fprofile-arcs -ftest-coverage -g -O0 \
    -I../../components/brake_driver \
    -I../../third_party/Unity/src \
    ../../components/brake_driver/brake_driver.c \
    test_integration_driver.c \
    ../../third_party/Unity/src/unity.c \
    -o integration_test_driver

./integration_test_driver
# Output: 3 Tests 0 Failures 0 Ignored

# Document increment 1
workspace.py trace create \
    --from components \
    --to integration \
    --source-id COMP-DRV-001 \
    --target-id INC-001 \
    --rationale "Brake driver integrated as baseline"

# ============================================================================
# INCREMENT 2: Integrate brake_service with brake_driver
# ============================================================================

cd ../increment2

# Create integration test (service + driver)
cat > test_integration_service.c <<'EOF'
#include "brake_service.h"
#include "brake_driver.h"
#include "unity.h"

void test_service_init_calls_driver(void) {
    result_t result = brake_service_init();
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    // Verify driver initialized (check hardware register)
    TEST_ASSERT_EQUAL(PWM_ENABLE, HW_REG_BRAKE_PWM_CTRL);
}

void test_service_apply_uses_driver(void) {
    brake_service_init();
    
    // Apply 50% brake
    result_t result = brake_service_apply(50);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Verify driver received correct PWM duty cycle
    // 50% → (50 * 1023) / 100 = 511
    TEST_ASSERT_EQUAL(511, HW_REG_BRAKE_PWM_DUTY);
}

void test_service_handles_driver_error(void) {
    brake_service_init();
    
    // Inject driver fault
    brake_driver_test_set_error(RESULT_ERROR_HARDWARE);
    
    result_t result = brake_service_apply(50);
    TEST_ASSERT_EQUAL(RESULT_ERROR_HARDWARE, result);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_service_init_calls_driver);
    RUN_TEST(test_service_apply_uses_driver);
    RUN_TEST(test_service_handles_driver_error);
    return UNITY_END();
}
EOF

# Build and run
gcc -fprofile-arcs -ftest-coverage -g -O0 \
    -I../../components/brake_driver \
    -I../../components/brake_service \
    -I../../third_party/Unity/src \
    ../../components/brake_driver/brake_driver.c \
    ../../components/brake_service/brake_service.c \
    test_integration_service.c \
    ../../third_party/Unity/src/unity.c \
    -o integration_test_service

./integration_test_service
# Output: 3 Tests 0 Failures 0 Ignored

# Check memory leaks (SIL 3)
valgrind --leak-check=full --error-exitcode=1 ./integration_test_service
# Output: 0 bytes leaked, 0 errors

# Document increment 2
workspace.py trace create \
    --from components \
    --to integration \
    --source-id COMP-SVC-002 \
    --target-id INC-002 \
    --rationale "Brake service integrated with driver"

# ============================================================================
# INCREMENT 3: Integrate brake_controller with service stack
# ============================================================================

cd ../increment3

# Create integration test (controller + service + driver)
cat > test_integration_full.c <<'EOF'
#include "brake_controller.h"
#include "brake_service.h"
#include "brake_driver.h"
#include "unity.h"

void test_full_stack_integration(void) {
    // Initialize full stack
    brake_driver_init();
    brake_service_init();
    brake_controller_init();
    
    // Set speed = 150 km/h
    sensor_test_set_speed(150);
    
    // Compute brake command
    brake_command_t command;
    result_t result = brake_controller_compute(&command);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Apply brake through service
    result = brake_service_apply(command.brake_level);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Verify data flowed through all layers to hardware
    TEST_ASSERT_TRUE(HW_REG_BRAKE_PWM_DUTY > 0);
}

void test_full_stack_error_propagation(void) {
    brake_driver_init();
    brake_service_init();
    brake_controller_init();
    
    // Inject driver fault
    brake_driver_test_set_error(RESULT_ERROR_HARDWARE);
    
    // Controller should detect error and enter safe state
    brake_command_t command;
    result_t result = brake_controller_compute(&command);
    
    // Verify safe state (full brake)
    TEST_ASSERT_EQUAL(RESULT_ERROR_SENSOR_FAULT, result);
    TEST_ASSERT_EQUAL(100, command.brake_level);  // Full brake
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_full_stack_integration);
    RUN_TEST(test_full_stack_error_propagation);
    return UNITY_END();
}
EOF

# Build and run
gcc -fprofile-arcs -ftest-coverage -g -O0 \
    -I../../components/brake_driver \
    -I../../components/brake_service \
    -I../../components/brake_controller \
    -I../../third_party/Unity/src \
    ../../components/brake_driver/brake_driver.c \
    ../../components/brake_service/brake_service.c \
    ../../components/brake_controller/brake_controller.c \
    test_integration_full.c \
    ../../third_party/Unity/src/unity.c \
    -o integration_test_full

./integration_test_full
# Output: 2 Tests 0 Failures 0 Ignored

# Generate coverage report (SIL 3: 100% required)
lcov --capture --directory . --output-file integration_coverage.info
genhtml integration_coverage.info --output-directory coverage_html

# Validate coverage (SIL 3)
gcovr --json --output integration_coverage.json
python3 ../../tools/check_coverage.py \
    --sil 3 \
    --coverage integration_coverage.json \
    --threshold statement:100,branch:100,condition:100
# Output: Statement: 100.0% PASS, Branch: 100.0% PASS, Condition: 100.0% PASS

# Document increment 3
workspace.py trace create \
    --from components \
    --to integration \
    --source-id COMP-CTL-003 \
    --target-id INC-003 \
    --rationale "Brake controller integrated with full stack"

# ============================================================================
# EVIDENCE COLLECTION: Generate all evidence
# ============================================================================

cd ../..
./tools/collect_integration_evidence.sh

# Output:
# Evidence directory: evidence/integration/
#   - integration_test_results_20260314_143022.json
#   - component_configuration_20260314_143022.json
#   - coverage_html_20260314_143022/index.html
#   - Software_Integration_Test_Report_20260314_143022.md

# ============================================================================
# VERIFICATION: Submit to Verifier (VER agent)
# ============================================================================

# Verifier reviews evidence per EN 50128 Section 7.6.4.11-7.6.4.13
# VER creates Software Integration Verification Report

# ✅ Integration COMPLETE - Ready for next phase (Validation)
```

---

## Summary

This component integration workflow provides:

1. **EN 50128 Compliance**: Implements Section 7.6.4.1-7.6.4.6 requirements
2. **Progressive Integration**: Bottom-up, top-down, sandwich strategies
3. **Interface Testing**: Contract verification at all boundaries
4. **Automated Testing**: Python scripts, Makefiles, CI/CD support
5. **SIL-Specific Guidance**: Clear requirements for SIL 0-4
6. **Tool Integration**: gcov, lcov, valgrind, workspace.py
7. **Evidence Collection**: Complete evidence per EN 50128 Section 7.6.4.5
8. **Traceability**: Component → Integration test traceability (SIL 3-4)

**Next Steps**:
1. Review `workflows/hw-sw-integration-workflow.md` for hardware/software integration
2. Review `workflows/interface-testing-workflow.md` for interface testing techniques
3. Review `workflows/performance-testing-workflow.md` for timing/performance validation

**EN 50128 References**:
- Section 7.6.1: Integration Objectives
- Section 7.6.4.1: Progressive Integration Requirement
- Section 7.6.4.2: Impact Analysis for Modifications
- Section 7.6.4.3-7.6.4.6: Software Integration Test Report Requirements
- Section 7.6.4.11-7.6.4.13: Integration Verification Report
- Table A.6: Integration Techniques
