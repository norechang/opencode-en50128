# Integration Testing Workflow

**EN 50128 Reference**: Section 7.6 (Software Integration), Table A.6  
**Role**: Tester (TST) + Integrator (INT)  
**Phase**: Integration (Phase 5)  
**SIL Applicability**: All (0, 1, 2, 3, 4)

---

## Overview

This workflow defines the complete software integration testing process for EN 50128 railway applications. Integration testing verifies that software components work correctly together and that software integrates properly with hardware.

**Key Objectives**:
- Verify interface compatibility between components
- Validate component interaction and data flow
- Test integrated subsystems against architecture specifications
- Detect integration-specific defects (timing, synchronization, resource conflicts)
- Perform hardware/software integration testing

**EN 50128 Requirements**:
- **Integration Testing MANDATORY** for all SIL levels (Section 7.6)
- **Interface Testing HIGHLY RECOMMENDED** (Table A.6)
- **Performance Testing HIGHLY RECOMMENDED** SIL 3-4 (Table A.6)
- **Incremental integration** recommended (bottom-up, top-down, or sandwich)
- **Coverage requirements** apply to integrated code (Table A.21)

---

## EN 50128 Integration Techniques (Table A.6)

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | **Functional and Black-Box Testing** | Table A.14 | HR | HR | HR |
| 2 | **Performance Testing** | Table A.18 | - | R | HR |
| 3 | Interface Testing | D.34 | HR | HR | HR |
| 4 | Error Guessing | D.23 | R | R | R |
| 5 | Boundary Value Analysis | D.4 | HR | HR | HR |

**Key Points**:
- Functional testing HIGHLY RECOMMENDED for all SILs
- Performance testing HIGHLY RECOMMENDED for SIL 3-4
- Interface testing critical for multi-component systems

**Standard Reference**: `std/EN50128-2011.md` Section 7.6, Table A.6

---

## Integration Strategies

### Strategy 1: Bottom-Up Integration

**Approach**: Test low-level modules first, progressively integrating higher levels.

**Advantages**:
- No stubs required (only drivers)
- Early testing of critical low-level functions
- Hardware integration easier

**Example**:
```
Level 3: Application Layer [System Controller]
              |
Level 2: Service Layer [Brake Controller] [Speed Monitor]
              |                            |
Level 1: HAL Layer [GPIO Driver] [CAN Driver] [Timer Driver]
```

**Integration Order**:
1. Test Level 1 modules individually (unit testing complete)
2. Integrate Level 2 with Level 1, test interfaces
3. Integrate Level 3 with Level 2, test complete system

---

### Strategy 2: Top-Down Integration

**Approach**: Test high-level modules first, progressively integrating lower levels.

**Advantages**:
- Early testing of system-level functionality
- User-visible features tested early
- Design issues detected early

**Example**:
```
Phase 1: Test System Controller (with stubs for Brake Controller, Speed Monitor)
Phase 2: Replace Brake Controller stub, test integration
Phase 3: Replace Speed Monitor stub, test integration
Phase 4: Replace HAL stubs, test full system
```

---

### Strategy 3: Sandwich Integration (Recommended for SIL 3-4)

**Approach**: Combine bottom-up and top-down, meet in the middle.

**Advantages**:
- Parallel integration possible
- Critical interfaces tested early
- Balanced stub/driver requirements

**Example**:
```
Top-Down Stream:
  System Controller → Brake Controller

Bottom-Up Stream:
  GPIO Driver → Brake Controller

Meet at: Brake Controller integration
```

---

## Workflow Steps

### Step 1: Integration Test Planning

#### 1.1 Define Integration Scope

**Input Documents**:
- Software Architecture Specification (SAS) - `docs/SAS.md`
- Software Design Specification (SDS) - `docs/SDS.md`
- Component Test Reports - `docs/Component-Test-Report.md`

**Activities**:
```bash
# Review architecture to identify integration points
cat docs/SAS.md | grep -A10 "Module Interfaces"

# Review component test status
cat docs/Component-Test-Report.md | grep "Status:"

# Verify all components passed unit testing
workspace.py trace query --source unit-tests --direction forward

# Check for integration readiness
if [ "$(grep 'Status: PASS' docs/Component-Test-Report.md | wc -l)" -lt "$EXPECTED_MODULES" ]; then
    echo "ERROR: Not all components passed unit testing"
    exit 1
fi
```

**Integration Levels**:
1. **Component Integration**: Two or more software components
2. **Subsystem Integration**: Multiple components forming a subsystem
3. **System Integration**: All software subsystems
4. **HW/SW Integration**: Software with target hardware

---

#### 1.2 Identify Integration Test Cases

**Test Focus Areas**:

1. **Interface Testing** (HIGHLY RECOMMENDED all SILs)
   - Function call interfaces (parameters, return values)
   - Data structure passing (struct, arrays)
   - Global variable sharing
   - Inter-process communication (queues, semaphores)
   - Hardware interfaces (memory-mapped I/O, interrupts)

2. **Data Flow Testing**
   - Data passed correctly between components
   - Data transformation at boundaries
   - Data corruption detection

3. **Control Flow Testing**
   - Call sequences correct
   - State machine transitions
   - Event handling and propagation

4. **Resource Sharing Testing**
   - Concurrent access to shared resources
   - Mutex/semaphore correctness
   - Deadlock detection

5. **Timing and Performance** (HR SIL 3-4)
   - Response time requirements
   - Throughput requirements
   - Resource utilization (CPU, memory)

6. **Fault Propagation** (SIL 3-4)
   - Error detection across boundaries
   - Fault containment
   - Safe state transitions

**Test Case Identification**:
```bash
# Create integration test specification
cat > tests/specs/integration_test_spec.md << 'EOF'
# Integration Test Specification

## Integration: Brake Controller ↔ Speed Sensor

**Components**:
- `brake_controller.c` - Brake control logic
- `speed_sensor.c` - Speed measurement

**Interface**:
```c
// Speed sensor provides speed to brake controller
uint16_t speed_sensor_get_speed(void);
error_t brake_controller_set_target_speed(uint16_t speed);
```

**Test Cases**:
- **TC-INT-001**: Normal data flow (speed sensor → brake controller)
- **TC-INT-002**: Boundary - Maximum speed value
- **TC-INT-003**: Error - Speed sensor timeout
- **TC-INT-004**: Fault injection - Speed sensor stuck
- **TC-INT-005**: Performance - Response time < 10ms
EOF
```

---

#### 1.3 Set Up Integration Test Environment

**Test Environment Types**:

1. **Host-Based Integration** (early integration)
   - Tests run on development host
   - Mock hardware interfaces
   - Fast execution, easy debugging

2. **Target-Based Integration** (final integration)
   - Tests run on target hardware
   - Real hardware interfaces
   - Realistic timing and performance

**Directory Structure**:
```
tests/
├── integration/
│   ├── test_brake_speed_integration.c
│   ├── test_signal_processing_integration.c
│   ├── test_hw_sw_integration.c
│   └── Makefile
├── stubs/
│   ├── stub_can_driver.c
│   ├── stub_timer.c
│   └── stub_gpio.c
├── drivers/
│   ├── driver_application_layer.c
│   └── driver_system_controller.c
└── data/
    ├── integration_scenarios.json
    └── performance_profiles.csv
```

---

### Step 2: Build Integration Test Harness

#### 2.1 Create Test Stubs (Top-Down Integration)

**Stub Template**:
```c
// stub_speed_sensor.c
// Stub for speed sensor (top-down integration)

#include "speed_sensor.h"
#include <stdint.h>

// Stub state
static uint16_t stub_speed_value = 0U;
static bool stub_fault_active = false;

// Stub control functions (for testing)
void stub_speed_sensor_set_value(uint16_t speed) {
    stub_speed_value = speed;
}

void stub_speed_sensor_inject_fault(bool fault) {
    stub_fault_active = fault;
}

// Stubbed interface functions
uint16_t speed_sensor_get_speed(void) {
    if (stub_fault_active) {
        return 0xFFFFU;  // Invalid value
    }
    return stub_speed_value;
}

error_t speed_sensor_init(void) {
    stub_speed_value = 0U;
    stub_fault_active = false;
    return SUCCESS;
}
```

---

#### 2.2 Create Test Drivers (Bottom-Up Integration)

**Driver Template**:
```c
// driver_brake_controller.c
// Test driver for brake controller (bottom-up integration)

#include "brake_controller.h"
#include "unity.h"
#include <stdio.h>

// Driver function: Exercise brake controller with various inputs
void driver_test_brake_controller(void) {
    uint16_t test_speeds[] = {0, 50, 100, 150, 200, 250, 300};
    uint8_t brake_level;
    error_t result;
    
    printf("Driver: Testing brake controller with speed inputs...\n");
    
    for (size_t i = 0; i < sizeof(test_speeds) / sizeof(test_speeds[0]); i++) {
        result = brake_controller_apply(test_speeds[i], &brake_level);
        
        printf("Speed: %u km/h, Brake: %u%%, Result: %d\n",
               test_speeds[i], brake_level, result);
        
        TEST_ASSERT_EQUAL(SUCCESS, result);
        TEST_ASSERT_TRUE(brake_level <= 100U);
    }
}
```

---

#### 2.3 Integration Test Code

**Integration Test Example**:
```c
// test_brake_speed_integration.c
// Integration test: Brake Controller + Speed Sensor

#include "brake_controller.h"
#include "speed_sensor.h"
#include "unity.h"
#include <stdint.h>

// Setup and teardown
void setUp(void) {
    speed_sensor_init();
    brake_controller_init();
}

void tearDown(void) {
    brake_controller_shutdown();
}

// ========================================
// INTERFACE TESTS
// ========================================

// TC-INT-001: Normal data flow
// Requirement: REQ-INT-010
void test_brake_speed_normal_integration(void) {
    // Arrange: Set speed sensor value
    speed_sensor_set_value(100U);  // 100 km/h
    
    // Act: Brake controller reads speed and applies brake
    uint16_t speed = speed_sensor_get_speed();
    uint8_t brake_level;
    error_t result = brake_controller_apply(speed, &brake_level);
    
    // Assert: Brake applied correctly
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_TRUE(brake_level > 0U);
    TEST_ASSERT_EQUAL(speed, 100U);
}

// TC-INT-002: Boundary - Maximum speed
// Requirement: REQ-INT-010, REQ-IMPL-006
void test_brake_speed_maximum_integration(void) {
    // Arrange
    speed_sensor_set_value(MAX_SPEED);  // 300 km/h
    
    // Act
    uint16_t speed = speed_sensor_get_speed();
    uint8_t brake_level;
    error_t result = brake_controller_apply(speed, &brake_level);
    
    // Assert: Maximum brake applied
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(100U, brake_level);  // Full brake
}

// TC-INT-003: Error - Speed sensor timeout
// Requirement: REQ-SAFE-020
void test_brake_speed_timeout_integration(void) {
    // Arrange: Simulate sensor timeout
    speed_sensor_inject_fault(FAULT_TIMEOUT);
    
    // Act: Brake controller attempts to read speed
    uint16_t speed = speed_sensor_get_speed();
    error_t result = brake_controller_apply(speed, NULL);
    
    // Assert: Error detected, safe state entered
    TEST_ASSERT_EQUAL(ERROR_SENSOR_FAULT, result);
    TEST_ASSERT_TRUE(brake_controller_in_safe_state());
}

// ========================================
// DATA FLOW TESTS
// ========================================

// TC-INT-004: Data integrity across interface
// Requirement: REQ-INT-011
void test_data_integrity_across_interface(void) {
    // Test data integrity for various speed values
    uint16_t test_values[] = {0, 1, 50, 100, 150, 200, 250, 299, 300};
    
    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        speed_sensor_set_value(test_values[i]);
        uint16_t retrieved = speed_sensor_get_speed();
        
        // Assert: Data not corrupted across interface
        TEST_ASSERT_EQUAL(test_values[i], retrieved);
    }
}

// ========================================
// TIMING AND PERFORMANCE TESTS (HR SIL 3-4)
// ========================================

// TC-INT-005: Response time requirement
// Requirement: REQ-PERF-010
void test_brake_response_time(void) {
    // Arrange
    speed_sensor_set_value(200U);
    
    // Act: Measure response time
    uint32_t start_time = system_get_tick_us();  // Microseconds
    
    uint16_t speed = speed_sensor_get_speed();
    uint8_t brake_level;
    brake_controller_apply(speed, &brake_level);
    
    uint32_t end_time = system_get_tick_us();
    uint32_t elapsed = end_time - start_time;
    
    // Assert: Response time < 10ms (10,000 us)
    TEST_ASSERT_TRUE(elapsed < 10000U);
    printf("Response time: %u us\n", elapsed);
}

// TC-INT-006: Throughput test
// Requirement: REQ-PERF-011
void test_brake_speed_throughput(void) {
    // Test sustained operation: 1000 iterations
    uint32_t iterations = 1000U;
    uint32_t start_time = system_get_tick_ms();
    
    for (uint32_t i = 0; i < iterations; i++) {
        speed_sensor_set_value((uint16_t)(i % 300));
        uint16_t speed = speed_sensor_get_speed();
        uint8_t brake_level;
        brake_controller_apply(speed, &brake_level);
    }
    
    uint32_t end_time = system_get_tick_ms();
    uint32_t elapsed_ms = end_time - start_time;
    
    // Calculate throughput (operations per second)
    uint32_t throughput = (iterations * 1000U) / elapsed_ms;
    
    // Assert: Throughput > 100 ops/sec
    TEST_ASSERT_TRUE(throughput > 100U);
    printf("Throughput: %u ops/sec\n", throughput);
}

// ========================================
// FAULT PROPAGATION TESTS (SIL 3-4)
// ========================================

// TC-INT-007: Fault containment
// Requirement: REQ-SAFE-021
void test_fault_containment(void) {
    // Arrange: Inject fault in speed sensor
    speed_sensor_inject_fault(FAULT_STUCK);
    
    // Act: Brake controller detects fault
    uint16_t speed = speed_sensor_get_speed();
    uint8_t brake_level;
    error_t result = brake_controller_apply(speed, &brake_level);
    
    // Assert: Fault contained, safe state entered
    TEST_ASSERT_EQUAL(ERROR_SENSOR_FAULT, result);
    TEST_ASSERT_TRUE(brake_controller_in_safe_state());
    
    // Assert: Emergency brake applied
    TEST_ASSERT_EQUAL(100U, brake_controller_get_emergency_level());
    
    // Assert: Fault does NOT propagate to other modules
    TEST_ASSERT_FALSE(signal_processor_has_fault());  // Other module OK
}

// ========================================
// RESOURCE SHARING TESTS
// ========================================

// TC-INT-008: Concurrent access to shared resource
// Requirement: REQ-INT-012
void test_concurrent_access_shared_memory(void) {
    // Simulate concurrent access from two components
    // (In real system, use threads or interrupts)
    
    // Component 1: Write to shared memory
    shared_memory_write(SHARED_SPEED, 150U);
    
    // Component 2: Read from shared memory
    uint16_t value = shared_memory_read(SHARED_SPEED);
    
    // Assert: Data consistent
    TEST_ASSERT_EQUAL(150U, value);
    
    // Assert: No data corruption
    TEST_ASSERT_TRUE(shared_memory_crc_valid(SHARED_SPEED));
}

// ========================================
// TEST RUNNER
// ========================================

int main(void) {
    UNITY_BEGIN();
    
    // Interface tests
    RUN_TEST(test_brake_speed_normal_integration);
    RUN_TEST(test_brake_speed_maximum_integration);
    RUN_TEST(test_brake_speed_timeout_integration);
    
    // Data flow tests
    RUN_TEST(test_data_integrity_across_interface);
    
    // Performance tests (HR SIL 3-4)
    RUN_TEST(test_brake_response_time);
    RUN_TEST(test_brake_speed_throughput);
    
    // Fault propagation tests (SIL 3-4)
    RUN_TEST(test_fault_containment);
    
    // Resource sharing tests
    RUN_TEST(test_concurrent_access_shared_memory);
    
    return UNITY_END();
}
```

---

### Step 3: Execute Integration Tests

#### 3.1 Build Integration Test Executable

```bash
# Build integration tests
cd tests/integration

# Makefile for integration tests
cat > Makefile << 'EOF'
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic \
         -fprofile-arcs -ftest-coverage \
         -g -O0 -DINTEGRATION_TEST

INCLUDES = -I../../src -I../../include -I../stubs -I../drivers -I../unity/src

SRC_FILES = ../../src/brake_controller.c ../../src/speed_sensor.c
TEST_FILES = test_brake_speed_integration.c
UNITY = ../unity/src/unity.c

all: test_brake_speed_integration

test_brake_speed_integration: $(TEST_FILES) $(SRC_FILES) $(UNITY)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

run: all
	./test_brake_speed_integration

coverage: run
	gcov $(SRC_FILES)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory ../coverage_integration

clean:
	rm -f test_* *.gcda *.gcno *.gcov coverage.info
	rm -rf ../coverage_integration

.PHONY: all run coverage clean
EOF

# Build and run
make run

# Output:
# test_brake_speed_integration.c:25:test_brake_speed_normal_integration:PASS
# test_brake_speed_integration.c:40:test_brake_speed_maximum_integration:PASS
# test_brake_speed_integration.c:55:test_brake_speed_timeout_integration:PASS
# test_brake_speed_integration.c:70:test_data_integrity_across_interface:PASS
# test_brake_speed_integration.c:85:test_brake_response_time:PASS
# Response time: 2450 us
# test_brake_speed_integration.c:105:test_brake_speed_throughput:PASS
# Throughput: 1250 ops/sec
# test_brake_speed_integration.c:125:test_fault_containment:PASS
# test_brake_speed_integration.c:145:test_concurrent_access_shared_memory:PASS
#
# -----------------------
# 8 Tests 0 Failures 0 Ignored 
# OK
```

---

#### 3.2 Hardware/Software Integration Testing

**Target Hardware Test Setup**:
```bash
# Flash software to target hardware
make TARGET=arm-none-eabi
arm-none-eabi-objcopy -O ihex build/integration_test.elf build/integration_test.hex
st-flash write build/integration_test.hex 0x08000000

# Monitor test execution via UART
minicom -D /dev/ttyUSB0 -b 115200

# Capture test results
minicom --capturefile=test_results.log -D /dev/ttyUSB0 -b 115200 &
# Run tests on target
# (Tests execute automatically on boot)
```

**Hardware-in-the-Loop (HIL) Testing**:
```python
#!/usr/bin/env python3
# hil_test_runner.py - Hardware-in-the-loop integration testing

import serial
import time
import json

class HILTestRunner:
    def __init__(self, port='/dev/ttyUSB0', baudrate=115200):
        self.serial = serial.Serial(port, baudrate, timeout=1)
        self.results = []
    
    def run_test(self, test_name, test_func):
        """Execute single HW test"""
        print(f"Running {test_name}...")
        
        # Send command to target
        self.serial.write(f"RUN {test_name}\n".encode())
        
        # Wait for result
        start_time = time.time()
        result_line = self.serial.readline().decode().strip()
        elapsed = time.time() - start_time
        
        # Parse result
        if "PASS" in result_line:
            self.results.append({
                'test': test_name,
                'status': 'PASS',
                'time': elapsed
            })
            print(f"  {test_name}: PASS ({elapsed:.3f}s)")
        else:
            self.results.append({
                'test': test_name,
                'status': 'FAIL',
                'time': elapsed
            })
            print(f"  {test_name}: FAIL")
    
    def run_all_tests(self):
        """Execute all HW integration tests"""
        test_list = [
            'test_brake_speed_integration',
            'test_can_communication',
            'test_interrupt_timing',
            'test_dma_transfer'
        ]
        
        for test in test_list:
            self.run_test(test, None)
        
        # Generate report
        self.generate_report()
    
    def generate_report(self):
        """Generate HW test report"""
        with open('hw_integration_report.json', 'w') as f:
            json.dump({
                'tests': self.results,
                'summary': {
                    'total': len(self.results),
                    'passed': sum(1 for r in self.results if r['status'] == 'PASS'),
                    'failed': sum(1 for r in self.results if r['status'] == 'FAIL')
                }
            }, f, indent=2)

if __name__ == "__main__":
    runner = HILTestRunner()
    runner.run_all_tests()
```

---

### Step 4: Analyze Integration Test Results

#### 4.1 Coverage Analysis (Integration Level)

```bash
# Generate integration coverage report
cd tests/integration
make coverage

# Check integrated coverage
lcov --add-tracefile ../unit/coverage.info \
     --add-tracefile ./coverage.info \
     --output-file ../combined_coverage.info

genhtml ../combined_coverage.info --output-directory ../coverage_combined

# Validate coverage targets
python3 ../../tools/check_coverage.py \
    --sil 3 \
    --coverage ../combined_coverage.info \
    --level integration

# Output:
# Integration Coverage Analysis
# =============================
# SIL Level: 3
# 
# Statement Coverage: 100.0% [PASS]
# Branch Coverage:    100.0% [PASS]
# Condition Coverage: 100.0% [PASS]
# 
# Integration-Specific Coverage:
# - Interface calls: 100% (all interfaces tested)
# - Error paths: 100% (all error conditions tested)
# - Fault scenarios: 95% (19/20 faults injected)
# 
# Result: PASS
```

---

#### 4.2 Performance Analysis

```bash
# Analyze performance test results
cat tests/integration/test_results.log | grep "Response time"
# Output:
# Response time: 2450 us (Target: < 10000 us) [PASS]

cat tests/integration/test_results.log | grep "Throughput"
# Output:
# Throughput: 1250 ops/sec (Target: > 100 ops/sec) [PASS]

# Generate performance report
python3 tools/analyze_performance.py \
    --results tests/integration/test_results.log \
    --requirements docs/SRS.md \
    --output tests/reports/performance_analysis.md
```

---

#### 4.3 Update Traceability

```bash
# Link integration tests to requirements
workspace.py trace create \
    --from tests \
    --to requirements \
    --source-id TC-INT-001 \
    --target-id REQ-INT-010 \
    --rationale "Integration test verifies brake-speed interface"

# Link integration tests to design
workspace.py trace create \
    --from tests \
    --to design \
    --source-id TC-INT-001 \
    --target-id DES-IF-005 \
    --rationale "Integration test verifies interface design"

# Generate integration traceability report
workspace.py trace report \
    --from requirements \
    --to tests \
    --format markdown \
    --output evidence/traceability/integration_traceability.md

# Validate traceability
workspace.py trace validate --phase integration --sil 3
```

---

## Deliverables

### Required Outputs

1. **Integration Test Specification**
   - Location: `docs/Integration-Test-Specification.md`
   - Content: Integration test cases, interfaces, procedures

2. **Integration Test Report**
   - Location: `docs/Integration-Test-Report.md`
   - Template: `templates/Integration-Test-Report-template.md`
   - Content: Test results, coverage, performance, defects

3. **Integration Test Code**
   - Location: `tests/integration/test_*.c`
   - Framework: Unity
   - Coverage: Interface, data flow, performance

4. **Coverage Reports** (Integration Level)
   - Location: `tests/coverage_integration/`
   - Combined with unit test coverage

5. **Performance Test Results**
   - Location: `tests/reports/performance_analysis.md`
   - Content: Response times, throughput, resource utilization

6. **Traceability Evidence**
   - Location: `evidence/traceability/integration_traceability.csv`
   - Tool: `workspace.py trace report`

---

## Quality Gates

### Integration Testing Exit Criteria

**All SIL Levels**:
- [ ] All integration test cases executed
- [ ] All interfaces tested (100%)
- [ ] Critical integration defects resolved
- [ ] Integration test report generated

**SIL 2**:
- [ ] 100% branch coverage (integrated code)
- [ ] Interface testing complete
- [ ] Performance requirements verified

**SIL 3-4**:
- [ ] **100% statement, branch, condition coverage** (integrated code)
- [ ] **Interface testing complete (MANDATORY)**
- [ ] **Performance testing complete (HR)**
- [ ] **Fault propagation tested**
- [ ] Hardware/software integration tested (if applicable)
- [ ] Independent verification performed
- [ ] Traceability validated

---

## References

- **EN 50128:2011**
  - Section 7.6 - Software Integration
  - Table A.6 - Integration Techniques
  - Table A.21 - Coverage Requirements
- **Standard Location**: `std/EN50128-2011.md`
- **Skill Resources**: 
  - `resources/integration-testing-patterns.md`
  - `resources/performance-testing-guide.md`
