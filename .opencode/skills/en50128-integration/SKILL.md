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

## Comprehensive Workflows

This skill provides **4 comprehensive workflows** covering the complete integration lifecycle:

### 1. Component Integration Workflow (`workflows/component-integration-workflow.md`)

**EN 50128 Reference**: Section 7.6, Table A.6  
**Coverage**: Progressive integration strategies, interface verification, integration testing

**Key Topics**:
- Progressive integration (bottom-up, top-down, sandwich, big bang)
- Interface contract verification and validation
- Build system integration with Makefile automation
- Integration test execution with Python scripts
- Evidence collection and report generation
- Complete railway braking system example (1,400+ lines)
- Integration defect management and resolution

**Example Usage**:
```bash
# 1. Build integrated system
cd build
make integration

# 2. Run integration tests
cd ../tests/integration
./test_brake_speed_integration
./test_sensor_controller_integration

# 3. Generate integration coverage
make coverage
lcov --capture --directory . --output-file integration_coverage.info
genhtml integration_coverage.info --output-directory coverage_html

# 4. Validate integration test results
python3 ../../tools/integration_validator.py \
    --test-results test_results.json \
    --sil 3 \
    --output evidence/integration/validation_report.json

# 5. Update traceability
workspace.py trace create \
    --from tests \
    --to design \
    --source-id IT-BRAKE-001 \
    --target-id DES-MOD-010 \
    --rationale "Integration test validates brake-speed interface"

workspace.py trace validate --phase integration --sil 3
```

---

### 2. Hardware/Software Integration Workflow (`workflows/hw-sw-integration-workflow.md`)

**EN 50128 Reference**: Section 7.6.4.7-7.6.4.10 (HW/SW Integration Test Report)  
**Coverage**: HAL design, target testing, HIL testing, cross-compilation

**Key Topics**:
- Hardware Abstraction Layer (HAL) with 3 implementations (target, simulator, stub)
- Target hardware configuration and setup automation
- Hardware-in-the-Loop (HIL) testing with Python automation
- Cross-compilation verification (arm-none-eabi-gcc)
- Timing and performance validation on target hardware
- Safety mechanisms validation (watchdog timer, MPU)
- Memory layout verification on target
- Interrupt handling and real-time constraints

**Example Usage**:
```bash
# 1. Build for target hardware (ARM Cortex-M)
cd build
make TARGET=arm-cortex-m4 CONFIG=release

# 2. Flash to target hardware
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
    -c "program build/firmware.elf verify reset exit"

# 3. Run Hardware-in-the-Loop (HIL) tests
cd tests/hil
python3 hil_test_runner.py \
    --port /dev/ttyUSB0 \
    --baudrate 115200 \
    --test-suite brake_system_tests.json \
    --output results/hil_test_results.json

# 4. Validate timing constraints on target
arm-none-eabi-gdb build/firmware.elf \
    -ex "target remote localhost:3333" \
    -ex "monitor reset halt" \
    -ex "break main" \
    -ex "continue"

# Run timing analysis
python3 tools/timing_analyzer.py \
    --trace timing.log \
    --requirements requirements/timing_requirements.json \
    --output evidence/timing_validation.json

# 5. Verify safety mechanisms (watchdog, MPU)
python3 tests/hil/safety_mechanism_test.py \
    --port /dev/ttyUSB0 \
    --output evidence/safety_mechanisms.json
```

---

### 3. Interface Testing Workflow (`workflows/interface-testing-workflow.md`)

**EN 50128 Reference**: Table D.34 (Interface Testing - 5 levels)  
**Coverage**: Function interfaces, data structures, protocols, IPC, API compatibility

**Key Topics**:
- Function interface testing (parameters, return values, side effects)
- Data structure interface testing (layout, alignment, padding)
- Communication protocol testing (UART with framing, CRC validation)
- Inter-process communication testing (shared memory with semaphores)
- Interface contract validation (preconditions, postconditions, invariants)
- Boundary value testing for interfaces (EN 50128 D.34 Level 2-4)
- Interface mocking and stubbing techniques
- API compatibility testing across versions

**Example Usage**:
```bash
# 1. Build interface tests
cd tests/interface
make run

# 2. Execute function interface tests
./test_function_interfaces
./test_data_structure_interfaces

# 3. Execute protocol tests (UART example)
./test_uart_protocol
# Tests: Framing, CRC, error handling, timeout behavior

# 4. Execute IPC tests
./test_shared_memory_ipc
# Tests: Data integrity, race conditions, semaphore behavior

# 5. Generate interface test coverage
make coverage
gcov ../../src/interfaces/*.c

# 6. Validate interface contracts
python3 tools/contract_validator.py \
    --source src/interfaces \
    --tests tests/interface \
    --output evidence/interface/contract_validation.json

# 7. Update traceability
workspace.py trace create \
    --from tests \
    --to design \
    --source-id IT-IFACE-UART-001 \
    --target-id DES-IFACE-005 \
    --rationale "Interface test validates UART protocol specification"
```

---

### 4. Performance Testing Workflow (`workflows/performance-testing-workflow.md`)

**EN 50128 Reference**: Table A.6 (Performance Testing: HR SIL 3-4), Table A.18  
**Coverage**: Timing validation, resource usage, real-time compliance, profiling

**Key Topics**:
- Timing requirements validation (execution time, response time, jitter)
- Resource usage testing (CPU, memory, stack with watermarking)
- Real-time deadline compliance (zero deadline misses for SIL 3-4)
- Worst-Case Execution Time (WCET) analysis
- Throughput and latency testing (UART example)
- Performance profiling with gprof
- Performance regression testing framework (Python script)
- Performance baseline establishment and monitoring

**Example Usage**:
```bash
# 1. Build with profiling enabled
cd build
make PROFILE=1

# 2. Run performance tests
cd ../tests/performance
./test_timing_requirements
./test_resource_usage
./test_deadline_compliance

# 3. Collect performance data
gprof ../../build/firmware gmon.out > profile_analysis.txt

# 4. Analyze stack usage (watermarking technique)
python3 tools/stack_analyzer.py \
    --binary ../../build/firmware.elf \
    --map ../../build/firmware.map \
    --output evidence/performance/stack_usage.json

# 5. Validate timing requirements (SIL 3-4: zero deadline misses)
python3 tools/timing_validator.py \
    --sil 3 \
    --requirements requirements/timing_requirements.json \
    --results performance_results.json \
    --output evidence/performance/timing_validation.json

# 6. Performance regression testing
python3 tools/performance_regression.py \
    --baseline evidence/performance/baseline.json \
    --current performance_results.json \
    --threshold 5.0 \
    --output evidence/performance/regression_report.json

# 7. Generate performance report
python3 tools/performance_reporter.py \
    --results performance_results.json \
    --format markdown \
    --output evidence/performance/performance_test_report.md
```

---

## Integration Workflow Selection by SIL

| SIL Level | Required Workflows | Key Requirements |
|-----------|-------------------|------------------|
| **SIL 0-1** | Component Integration | Progressive integration (recommended), Functional testing (HR) |
| **SIL 2** | Component + Interface + Performance (R) | Progressive integration (HR), Interface testing (HR), Performance testing (R) |
| **SIL 3-4** | **ALL 4 workflows** | Progressive integration (**M**), Interface testing (HR), Performance testing (**HR**), HW/SW integration with HIL |

**SIL 3-4 Special Requirements**:
- Independent integration testing team
- 100% interface coverage
- Zero deadline misses for safety-critical tasks
- HIL testing on target hardware mandatory
- Performance baseline and regression monitoring
- Complete traceability from requirements through integration

---

## Tool Integration

### Integration Build Tools (Working Implementations)

**GNU Make** (Build automation):
```bash
# Build all components
make all

# Build integration tests
make integration

# Build with coverage
make coverage

# Build for target hardware
make TARGET=arm-cortex-m4
```

**Cross-Compilation** (ARM target):
```bash
# Compile for ARM Cortex-M4
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard \
    -O2 -g -Wall -Wextra \
    -Isrc/include -Isrc/hal \
    -c src/brake_controller.c -o build/brake_controller.o

# Link
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard \
    -T stm32f4_linker.ld \
    -Wl,-Map=build/firmware.map \
    build/*.o -o build/firmware.elf

# Generate binary
arm-none-eabi-objcopy -O binary build/firmware.elf build/firmware.bin
```

---

### Coverage Analysis Tools (Working Implementations)

**gcov + lcov** (Integration coverage):
```bash
# Compile with coverage flags
gcc -fprofile-arcs -ftest-coverage -g -O0 \
    -o test_integration \
    src/module_a.c src/module_b.c tests/test_integration.c

# Run integration tests
./test_integration

# Generate coverage report
lcov --capture --directory . --output-file integration_coverage.info
lcov --remove integration_coverage.info '/usr/*' 'tests/*' \
    --output-file integration_coverage_filtered.info
genhtml integration_coverage_filtered.info \
    --output-directory coverage_html

# Combine with unit test coverage
lcov --add-tracefile ../unit/coverage.info \
     --add-tracefile integration_coverage_filtered.info \
     --output-file combined_coverage.info

# Validate coverage (SIL 3-4: 100% required)
python3 tools/check_coverage.py \
    --sil 3 \
    --coverage combined_coverage.json \
    --report evidence/coverage/integration_validation.json
```

---

### Hardware-in-the-Loop (HIL) Testing (Python Automation)

**HIL Test Automation** (Working):
```bash
# Install pyserial for UART communication
pip3 install pyserial

# Run HIL test suite
python3 tests/hil/hil_test_runner.py \
    --port /dev/ttyUSB0 \
    --baudrate 115200 \
    --test-suite tests/hil/brake_system_tests.json \
    --timeout 300 \
    --output results/hil_results.json

# Validate HIL test results
python3 tools/hil_validator.py \
    --results results/hil_results.json \
    --requirements requirements/hw_sw_requirements.json \
    --sil 3 \
    --output evidence/hil/validation_report.json
```

**HIL Test Script Example** (`tests/hil/hil_test_runner.py`):
```python
#!/usr/bin/env python3
"""Hardware-in-the-Loop (HIL) Test Runner"""

import serial
import json
import time

def run_hil_test(port, test_case):
    """Execute a single HIL test case"""
    with serial.Serial(port, 115200, timeout=5) as ser:
        # Send test command
        ser.write(test_case['command'].encode() + b'\n')
        
        # Wait for response
        response = ser.readline().decode().strip()
        
        # Validate response
        expected = test_case['expected_response']
        passed = (response == expected)
        
        return {
            'test_id': test_case['id'],
            'command': test_case['command'],
            'expected': expected,
            'actual': response,
            'result': 'PASS' if passed else 'FAIL',
            'timestamp': time.time()
        }

if __name__ == '__main__':
    # Load test suite
    with open('brake_system_tests.json') as f:
        test_suite = json.load(f)
    
    # Execute all tests
    results = []
    for test in test_suite['tests']:
        result = run_hil_test('/dev/ttyUSB0', test)
        results.append(result)
        print(f"{result['test_id']}: {result['result']}")
    
    # Save results
    with open('hil_results.json', 'w') as f:
        json.dump({'tests': results}, f, indent=2)
```

---

### Performance Analysis Tools (Working Implementations)

**gprof** (Profiling):
```bash
# Compile with profiling
gcc -pg -g -O2 -o firmware src/*.c

# Run program (generates gmon.out)
./firmware

# Generate profile report
gprof firmware gmon.out > profile.txt

# Analyze hotspots
grep "% time" profile.txt | head -20
```

**Valgrind** (Memory analysis on host):
```bash
# Check for memory leaks (host testing only)
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --log-file=valgrind.log \
         ./test_integration

# For SIL 2+: Zero leaks required
grep "definitely lost: 0 bytes" valgrind.log
```

**Stack Watermarking** (Target testing):
```c
// Initialize stack with pattern
void stack_watermark_init(void) {
    extern uint8_t _stack_start;
    extern uint8_t _stack_end;
    size_t stack_size = &_stack_end - &_stack_start;
    
    // Fill with 0xA5 pattern
    memset(&_stack_start, 0xA5, stack_size);
}

// Measure maximum stack usage
uint32_t stack_watermark_measure(void) {
    extern uint8_t _stack_start;
    extern uint8_t _stack_end;
    
    uint8_t* ptr = &_stack_start;
    while (*ptr == 0xA5 && ptr < &_stack_end) {
        ptr++;
    }
    
    return (uint32_t)(&_stack_end - ptr);
}
```

---

### Traceability Integration (Working Implementation)

**Link Integration Tests to Design**:
```bash
# Create traceability link (integration test → design module)
workspace.py trace create \
    --from tests \
    --to design \
    --source-id IT-BRAKE-SPEED-001 \
    --target-id DES-MOD-015 \
    --rationale "Integration test validates brake-speed sensor interface per SIS-IFACE-003"

# Create traceability link (integration test → interface spec)
workspace.py trace create \
    --from tests \
    --to specifications \
    --source-id IT-UART-PROTOCOL-001 \
    --target-id SIS-IFACE-010 \
    --rationale "Interface test validates UART protocol specification"

# Validate integration traceability completeness
workspace.py trace validate --phase integration --sil 3

# Generate traceability report (design → integration tests)
workspace.py trace report \
    --from design \
    --to tests \
    --format markdown \
    --output evidence/traceability/design_to_integration_tests.md

# Generate traceability matrix (requirements → design → integration tests)
workspace.py trace matrix \
    --phases requirements,design,integration \
    --format html \
    --output evidence/traceability/integration_matrix.html
```

---

## Integration Templates

The skill includes **5 comprehensive integration templates** (already present):

1. **Software Integration Test Specification** (`templates/Software-Integration-Test-Specification-template.md`)
   - Purpose: Define integration test cases for software components
   - Content: Test objectives, procedures, pass/fail criteria
   - Sections: Progressive integration strategy, interface tests, functional tests

2. **Software Integration Test Report** (`templates/Software-Integration-Test-Report-template.md`)
   - Purpose: Document software integration test results
   - Content: Test results, failures, configuration items, evidence
   - Approval: INT, TST, QA, Verifier (SIL 3-4)

3. **Hardware-Software Integration Test Specification** (`templates/Hardware-Software-Integration-Test-Specification-template.md`)
   - Purpose: Define HW/SW integration test cases
   - Content: Hardware setup, test procedures, timing requirements
   - Sections: Target hardware config, HIL tests, performance tests

4. **Hardware-Software Integration Test Report** (`templates/Hardware-Software-Integration-Test-Report-template.md`)
   - Purpose: Document HW/SW integration test results
   - Content: Target hardware results, HIL test results, timing validation
   - Approval: INT, TST, QA, Verifier (SIL 3-4)

5. **Software Integration Verification Report** (`templates/Software-Integration-Verification-Report-template.md`)
   - Purpose: Independent verification of integration activities
   - Content: Verification results, compliance checks, evidence
   - Approval: Verifier (independent for SIL 3-4)

---

## EN 50128 Table A.6 Implementation

### Integration Techniques (Table A.6)

| # | Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Workflow Coverage | Tool Support |
|---|-----------|-------|---------|---------|-------------------|--------------|
| 1 | **Functional and Black-box Testing** | HR | HR | HR | Component Integration, Interface Testing | Unity, gcov |
| 2 | **Performance Testing** | - | R | **HR** | Performance Testing | gprof, custom timing tools |

**Implementation Strategy**:
- **Functional Testing**: Covered in workflows 1, 3 (Component Integration, Interface Testing)
- **Performance Testing**: Covered in workflow 4 (Performance Testing)
- **Both techniques**: Demonstrated with complete code examples and tool automation

### EN 50128 Section 7.6 Requirements Coverage

| Section | Requirement | Workflow Coverage |
|---------|-------------|-------------------|
| 7.6.1 | Integration objectives | All workflows (introduction sections) |
| 7.6.4.1 | Progressive integration | Component Integration Workflow |
| 7.6.4.2 | Impact analysis for modifications | Component Integration Workflow (change management) |
| 7.6.4.3-7.6.4.6 | Software Integration Test Report | All workflows → Software Integration Test Report template |
| 7.6.4.7-7.6.4.10 | HW/SW Integration Test Report | HW/SW Integration Workflow → HW/SW Integration Test Report template |

---

## Standard References

- **EN 50128:2011 Section 7.6** (Integration) - `std/EN50128-2011.md` lines 3284-3404
- **EN 50128:2011 Table A.6** (Integration techniques) - `std/EN50128-TABLES-EXTRACTED.md`
- **EN 50128:2011 Table A.14** (Functional/Black-Box Testing) - `std/EN50128-2011.md`
- **EN 50128:2011 Table A.18** (Performance Testing) - `std/EN50128-2011.md`
- **EN 50128:2011 Table D.34** (Interface Testing - 5 levels) - `std/EN50128-2011.md`
- **EN 50128 Abbreviations** - `std/EN50128-ABBREVIATIONS.md`

---

## Related Skills

- `en50128-testing` - Component and unit testing
- `en50128-verification` - Verification techniques
- `en50128-implementation` - C implementation patterns
- `en50128-design` - Module design and interfaces
- `en50128-validation` - System validation and acceptance testing
