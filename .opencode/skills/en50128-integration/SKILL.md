---
name: en50128-integration
description: Software integration strategies and testing for EN 50128 compliant C programs
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  phase: integration
---

## What I do

I provide integration strategies and best practices for railway software integration compliant with EN 50128 Section 7.6:
- Progressive integration approaches (bottom-up, top-down, sandwich)
- Interface testing for C modules
- Hardware/software integration patterns
- Integration test specification and execution
- Impact analysis for integration changes
- Integration verification and validation

## When to use me

Use this skill when:
- Integrating tested components into subsystems
- Performing software/hardware integration
- Testing interfaces between C modules
- Executing integration test specifications
- Analyzing impact of integration changes
- Preparing integration test reports
- Coordinating with hardware teams

## Integration Techniques (EN 50128 Table A.6)

**EN 50128 Section 7.6, Table A.6** defines integration techniques:

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | Functional and Black-box Testing | Table A.14 | HR | HR | HR |
| 2 | Performance Testing | Table A.18 | - | R | HR |

**Key Points:**
- Functional/Black-box Testing is **Highly Recommended** for ALL SIL levels
- Performance Testing is **Highly Recommended** for SIL 3-4
- One or more techniques SHALL be selected per SIL level

## Integration Strategies

### 1. Bottom-Up Integration

**Best for:** Testing low-level modules first, building confidence incrementally

```c
// Step 1: Integrate and test lowest-level modules
test_driver_module();
test_hardware_abstraction_layer();

// Step 2: Integrate next level (services using drivers)
test_sensor_service();  // Uses driver modules
test_actuator_service();

// Step 3: Integrate application level
test_control_logic();  // Uses services

// Step 4: Integrate top level
test_main_application();  // Uses all lower levels
```

**Advantages:**
- Test infrastructure (drivers, HAL) first
- Early detection of low-level issues
- No test stubs needed for lower levels

**Disadvantages:**
- Requires test drivers for high-level modules
- System-level testing delayed

### 2. Top-Down Integration

**Best for:** Testing critical control flow early

```c
// Step 1: Test top-level control with stubs
test_main_controller();  // Uses stubs for services

// Step 2: Replace stubs with real services
test_main_with_real_services();

// Step 3: Replace service stubs with real drivers
test_services_with_real_drivers();

// Step 4: Full system integration
test_complete_system();
```

**Advantages:**
- Test critical logic early
- Verify system architecture early
- Good for control-heavy systems

**Disadvantages:**
- Requires many stubs initially
- Stub complexity can be high

### 3. Sandwich Integration (Hybrid)

**Best for:** Large systems, parallel development teams

```c
// Simultaneously:
// Team A: Bottom-up from drivers
test_driver_layer();
test_service_layer();

// Team B: Top-down from control logic
test_control_layer();
test_application_layer();

// Final: Meet in the middle
test_complete_integration();
```

**Advantages:**
- Parallel testing
- Balances advantages of both approaches
- Good for complex systems

### 4. Progressive Integration (EN 50128 Recommended)

**EN 50128 Section 7.6.4.1:** "Integration shall progressively combine individual and previously tested components"

```c
// Increment 1: Core components
integrate_and_test(sensor_driver, sensor_service);

// Increment 2: Add next component
integrate_and_test(previous_integration, actuator_service);

// Increment 3: Add control logic
integrate_and_test(previous_integration, control_logic);

// Continue until complete
```

## C Module Interface Testing

### Interface Contract Verification

```c
// Example: Validate interface contracts during integration

// Interface definition (from header)
typedef enum {
    RESULT_SUCCESS = 0,
    RESULT_ERROR_NULL_PTR = 1,
    RESULT_ERROR_INVALID_PARAM = 2,
    RESULT_ERROR_TIMEOUT = 3
} result_t;

result_t sensor_read(const sensor_config_t* config, 
                     sensor_data_t* data,
                     uint32_t timeout_ms);

// Integration test: Verify ALL interface contracts
void test_sensor_read_interface(void) {
    sensor_config_t config = {/* valid config */};
    sensor_data_t data;
    result_t result;
    
    // Test 1: NULL pointer handling (contract requirement)
    result = sensor_read(NULL, &data, 100);
    TEST_ASSERT_EQUAL(RESULT_ERROR_NULL_PTR, result);
    
    result = sensor_read(&config, NULL, 100);
    TEST_ASSERT_EQUAL(RESULT_ERROR_NULL_PTR, result);
    
    // Test 2: Invalid parameters
    sensor_config_t invalid_config = {.sensor_id = 999};
    result = sensor_read(&invalid_config, &data, 100);
    TEST_ASSERT_EQUAL(RESULT_ERROR_INVALID_PARAM, result);
    
    // Test 3: Timeout behavior
    result = sensor_read(&config, &data, 0);  // Immediate timeout
    TEST_ASSERT_EQUAL(RESULT_ERROR_TIMEOUT, result);
    
    // Test 4: Valid operation
    result = sensor_read(&config, &data, 1000);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    TEST_ASSERT_TRUE(data.value >= MIN_SENSOR_VALUE);
    TEST_ASSERT_TRUE(data.value <= MAX_SENSOR_VALUE);
}
```

### Cross-Module Data Flow Testing

```c
// Test data flow across module boundaries

void test_sensor_to_controller_integration(void) {
    // Setup
    sensor_init();
    controller_init();
    
    // Test: Data flows from sensor through controller
    sensor_data_t sensor_data = {.value = 42};
    
    // Step 1: Sensor produces data
    result_t result = sensor_update(&sensor_data);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Step 2: Controller reads sensor data
    control_input_t input;
    result = controller_read_sensors(&input);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Step 3: Verify data integrity across boundary
    TEST_ASSERT_EQUAL(42, input.sensor_value);
    
    // Step 4: Controller processes data
    control_output_t output;
    result = controller_process(&input, &output);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Verify expected behavior
    TEST_ASSERT_TRUE(output.command_valid);
}
```

## Memory Layout Verification (SIL 2+)

```c
// Integration test: Verify memory layout

void test_memory_layout_integration(void) {
    // Verify no memory overlaps between modules
    
    extern uint8_t __module_a_start;
    extern uint8_t __module_a_end;
    extern uint8_t __module_b_start;
    extern uint8_t __module_b_end;
    
    // Check Module A memory
    size_t module_a_size = &__module_a_end - &__module_a_start;
    TEST_ASSERT_TRUE(module_a_size <= MODULE_A_MAX_SIZE);
    
    // Check Module B memory
    size_t module_b_size = &__module_b_end - &__module_b_start;
    TEST_ASSERT_TRUE(module_b_size <= MODULE_B_MAX_SIZE);
    
    // Check no overlap
    bool no_overlap = (&__module_a_end <= &__module_b_start) ||
                      (&__module_b_end <= &__module_a_start);
    TEST_ASSERT_TRUE(no_overlap);
    
    // Verify total memory within limits
    size_t total_memory = module_a_size + module_b_size;
    TEST_ASSERT_TRUE(total_memory <= TOTAL_MEMORY_LIMIT);
}
```

## Performance Testing (HR for SIL 3-4)

### Timing Constraints Verification

```c
// Performance test: Verify timing requirements during integration

void test_end_to_end_timing(void) {
    uint32_t start_time, end_time, execution_time;
    
    // Test: Sensor → Controller → Actuator timing
    start_time = get_timestamp_us();
    
    // Execute integrated function chain
    sensor_data_t data;
    sensor_read(&sensor_config, &data, 100);
    
    control_output_t output;
    controller_process(&data, &output);
    
    actuator_command(&actuator_config, &output);
    
    end_time = get_timestamp_us();
    execution_time = end_time - start_time;
    
    // Verify meets timing requirement
    TEST_ASSERT_TRUE(execution_time <= MAX_RESPONSE_TIME_US);
    
    // Log performance data (MANDATORY for SIL 3-4 per Table A.9)
    log_performance_metric("end_to_end_timing", execution_time);
}
```

### Resource Usage Testing

```c
// Performance test: Verify resource usage during integration

void test_integrated_resource_usage(void) {
    // Test stack usage
    uint32_t stack_usage = measure_stack_usage();
    TEST_ASSERT_TRUE(stack_usage <= MAX_STACK_SIZE);
    
    // Test CPU usage
    uint32_t cpu_percent = measure_cpu_usage();
    TEST_ASSERT_TRUE(cpu_percent <= MAX_CPU_USAGE_PERCENT);
    
    // Test memory usage (static allocation only for SIL 2+)
    uint32_t ram_usage = measure_ram_usage();
    TEST_ASSERT_TRUE(ram_usage <= MAX_RAM_SIZE);
    
    // Verify no dynamic allocation occurred (SIL 2+)
    uint32_t heap_usage = measure_heap_usage();
    TEST_ASSERT_EQUAL(0, heap_usage);  // Should be zero for SIL 2+
}
```

## Hardware/Software Integration

### Hardware Abstraction Layer Testing

```c
// Test hardware interface integration

void test_hardware_abstraction_layer(void) {
    // Initialize hardware (may be simulated in test environment)
    hal_init();
    
    // Test: Read from hardware register
    uint32_t register_value;
    result_t result = hal_read_register(GPIO_BASE, GPIO_INPUT_REG, 
                                        &register_value);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Test: Write to hardware register
    result = hal_write_register(GPIO_BASE, GPIO_OUTPUT_REG, 0x12345678);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    
    // Test: Verify write was successful
    result = hal_read_register(GPIO_BASE, GPIO_OUTPUT_REG, &register_value);
    TEST_ASSERT_EQUAL(RESULT_SUCCESS, result);
    TEST_ASSERT_EQUAL(0x12345678, register_value);
    
    // Test: Interrupt handling
    hal_enable_interrupt(TIMER_IRQ);
    // Trigger interrupt (simulation or real hardware)
    TEST_ASSERT_TRUE(interrupt_occurred);
}
```

## Impact Analysis (EN 50128 Section 7.6.4.2)

**Requirement:** "Any modification during integration requires impact study"

### Impact Analysis Process

```c
// Example: Document impact of integration change

/**
 * Integration Change Request: ICR-2026-001
 * 
 * Change: Update sensor_read() interface to add timestamp parameter
 * 
 * Impact Analysis:
 * 
 * 1. Affected Components:
 *    - sensor_driver.c (DIRECT)
 *    - sensor_driver.h (DIRECT)
 *    - sensor_service.c (DIRECT - calls sensor_read)
 *    - controller.c (INDIRECT - uses sensor_service)
 *    - data_logger.c (DIRECT - calls sensor_read)
 * 
 * 2. Integration Tests Affected:
 *    - test_sensor_integration.c
 *    - test_sensor_service_integration.c
 *    - test_data_logger_integration.c
 * 
 * 3. Reverification Required:
 *    - Unit tests for sensor_driver.c
 *    - Integration tests for all affected components
 *    - Interface contract verification tests
 *    - Regression testing for controller
 * 
 * 4. Documentation Updates:
 *    - Software Interface Specification
 *    - Integration Test Specification
 *    - Traceability Matrix (MANDATORY SIL 3-4)
 * 
 * 5. Estimated Effort: 8 hours
 */

// Old interface
// result_t sensor_read(const sensor_config_t* config, sensor_data_t* data);

// New interface
result_t sensor_read(const sensor_config_t* config, 
                     sensor_data_t* data,
                     uint32_t* timestamp_ms);
```

## Integration Test Report Requirements

**Per EN 50128 Section 7.6.4.3-7.6.4.6, Integration Test Report SHALL include:**

1. **Test Results Summary**
   - Whether objectives and criteria met
   - Pass/fail status for each test case

2. **Test Cases and Results**
   - Preferably machine-readable format
   - All test cases documented

3. **Failure Documentation**
   - Circumstances of any failures
   - Root cause analysis

4. **Configuration Documentation**
   - Identity and configuration of all integrated items
   - Version numbers
   - Build configuration

5. **Technique Usage**
   - Demonstrate correct use of Table A.6 techniques
   - Functional/Black-box testing (HR for all SILs)
   - Performance testing (HR for SIL 3-4)

6. **Repeatability**
   - Tests are repeatable
   - Preferably automated

## Integration Checklist

Before completing integration phase:

- [ ] Progressive integration approach followed
- [ ] All interfaces tested at each integration step
- [ ] Functional/Black-box testing performed (HR for all SILs)
- [ ] Performance testing performed (HR for SIL 3-4, R for SIL 1-2)
- [ ] Test results recorded (machine-readable preferred)
- [ ] All failures documented with circumstances
- [ ] Impact analysis performed for all modifications
- [ ] Component identities and configurations documented
- [ ] Tests are repeatable (automated if possible)
- [ ] Table A.6 technique usage demonstrated
- [ ] Integration test reports complete
- [ ] Memory layout verified (SIL 2+)
- [ ] Timing constraints verified
- [ ] Hardware/software interfaces tested
- [ ] Traceability updated (MANDATORY SIL 3-4)
- [ ] Ready for handoff to Verifier

## Standard References

- **EN 50128:2011 Section 7.6** (Integration) - `std/EN50128-2011.md` lines 3284-3404
- **EN 50128:2011 Table A.6** (Integration techniques) - `std/EN50128-TABLES-EXTRACTED.md`
- **EN 50128:2011 Table A.14** (Functional/Black-Box Testing) - `std/EN50128-2011.md`
- **EN 50128:2011 Table A.18** (Performance Testing) - `std/EN50128-2011.md`
- **EN 50128 Abbreviations** - `std/EN50128-ABBREVIATIONS.md`

## Related Skills

- `en50128-testing` - Component and unit testing
- `en50128-verification` - Verification techniques
- `en50128-implementation` - C implementation patterns
- `en50128-design` - Module design and interfaces
