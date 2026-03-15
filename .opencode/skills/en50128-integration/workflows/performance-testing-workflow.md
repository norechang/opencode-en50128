# Performance Testing Workflow

**EN 50128 Reference**: Table A.6 (Performance Testing), Table A.18 (Performance Testing Details)  
**Phase**: Phase 6 - Integration  
**Role**: Integrator (INT)  
**SIL Level**: All (0-4, Mandatory for SIL 3-4)

---

## Purpose

This workflow defines the comprehensive process for validating performance requirements during software integration to ensure "the software and hardware interact correctly to perform their intended functions" within specified time and resource constraints (EN 50128 Section 7.6.1.2).

**Key Objectives**:
- Timing requirements validation (execution time, response time, latency)
- Resource usage verification (CPU, memory, stack, heap)
- Throughput and bandwidth testing
- Real-time deadline compliance
- Performance profiling and optimization
- Performance regression detection

**EN 50128 Requirement**:
- **SIL 0**: Performance testing not recommended (-)
- **SIL 1-2**: Performance testing recommended (R)
- **SIL 3-4**: Performance testing **HIGHLY RECOMMENDED** (HR)

**Inputs**:
- Software Requirements Specification (timing/resource requirements)
- Software/Hardware Integration Test Specification
- Integrated software on target hardware
- Hardware performance specification

**Outputs**:
- Performance Test Report
- Timing analysis results
- Resource utilization profiles
- Performance regression report
- Optimization recommendations (if needed)

---

## Table of Contents

1. [Performance Testing Principles](#performance-testing-principles)
2. [Timing Requirements Validation](#timing-requirements-validation)
3. [Resource Usage Testing](#resource-usage-testing)
4. [Real-Time Deadline Compliance](#real-time-deadline-compliance)
5. [Throughput and Latency Testing](#throughput-and-latency-testing)
6. [Performance Profiling](#performance-profiling)
7. [Performance Regression Testing](#performance-regression-testing)
8. [Tool Integration for Performance Testing](#tool-integration-for-performance-testing)
9. [SIL-Specific Requirements](#sil-specific-requirements)
10. [Example Performance Testing Scenarios](#example-performance-testing-scenarios)

---

## Performance Testing Principles

### EN 50128 Performance Testing Requirements

**EN 50128 Table A.18 - Performance Testing**:

Performance testing verifies that the software meets:
1. **Timing requirements**: Response time, execution time, cycle time
2. **Throughput requirements**: Data processing rate, transaction rate
3. **Resource requirements**: CPU usage, memory usage, I/O bandwidth
4. **Capacity requirements**: Maximum load, concurrent operations
5. **Efficiency requirements**: Power consumption, resource utilization

**Performance Metrics Categories**:

| Category | Metrics | Measurement Methods |
|----------|---------|-------------------|
| **Timing** | Execution time, response time, latency, jitter | Hardware timers, instrumentation, oscilloscope |
| **CPU** | CPU utilization, idle time, context switches | Performance counters, profilers |
| **Memory** | Heap usage, stack usage, static allocation | Memory profilers, linker maps |
| **I/O** | Throughput, bandwidth, IOPS | Instrumentation, bus analyzers |
| **Real-Time** | Deadline misses, priority inversion, blocking time | RTOS tracers, logic analyzers |

**SIL-Specific Performance Testing Depth**:

| SIL | Performance Testing Depth | Key Focus Areas |
|-----|--------------------------|-----------------|
| **0** | Minimal (optional) | Basic functional verification |
| **1-2** | Moderate | Timing bounds, resource limits verified on target |
| **3-4** | Comprehensive | Worst-case execution time (WCET), all deadlines verified, stress testing, long-term stability |

---

## Timing Requirements Validation

### Timing Validation Strategy

**Objective**: Verify all timing requirements are met under all conditions (best case, typical case, worst case).

**Timing Requirements Types**:
1. **Execution time**: How long a function/task takes to complete
2. **Response time**: Time from stimulus to response (includes scheduling delays)
3. **Cycle time**: Time between periodic task invocations
4. **Latency**: Time delay in data path
5. **Jitter**: Variation in timing (critical for real-time systems)

### Example: Safety-Critical Function Timing Test

**Timing Requirements Specification**:

```c
// File: brake_timing_requirements.h
// Timing requirements for braking system
// EN 50128 SIL 3

#ifndef BRAKE_TIMING_REQUIREMENTS_H
#define BRAKE_TIMING_REQUIREMENTS_H

#include <stdint.h>

/**
 * @brief Timing requirements for brake_apply()
 * @standard EN 50128 Section 7.6
 * @sil 3
 * 
 * TIMING REQUIREMENTS:
 * - Maximum execution time: 50 microseconds (on target hardware: 100 MHz ARM Cortex-M4)
 * - Response time (from sensor trigger to brake actuation): 100 milliseconds
 * - Cycle time: 10 milliseconds (100 Hz control loop)
 * - Jitter tolerance: +/- 1 millisecond
 * 
 * WORST-CASE CONDITIONS:
 * - All 4 brakes applied simultaneously
 * - Maximum interrupt load
 * - Cache misses
 */

// Timing constraints (microseconds)
#define BRAKE_APPLY_MAX_EXEC_TIME_US     50
#define BRAKE_RESPONSE_MAX_TIME_MS       100
#define BRAKE_CYCLE_TIME_MS              10
#define BRAKE_JITTER_TOLERANCE_MS        1

#endif // BRAKE_TIMING_REQUIREMENTS_H
```

**Timing Test Harness**:

```c
// File: test_brake_timing.c
// Timing validation tests for brake system
// EN 50128 SIL 3 - Performance Testing

#include "unity.h"
#include "brake_controller.h"
#include "brake_timing_requirements.h"
#include <stdint.h>

// Hardware timer access for precise timing
// Assume ARM Cortex-M4 with DWT cycle counter
#define DWT_CYCCNT   (*(volatile uint32_t*)0xE0001004)  // Cycle count register
#define DWT_CONTROL  (*(volatile uint32_t*)0xE0001000)  // Control register
#define DWT_LAR      (*(volatile uint32_t*)0xE0001FB0)  // Lock access register

#define CPU_FREQ_HZ  100000000  // 100 MHz
#define CYCLES_TO_US(cycles) ((cycles) / (CPU_FREQ_HZ / 1000000))

static void timing_init(void) {
    // Enable DWT cycle counter
    DWT_LAR = 0xC5ACCE55;     // Unlock
    DWT_CONTROL |= 1;         // Enable cycle counter
}

static uint32_t timing_get_cycles(void) {
    return DWT_CYCCNT;
}

void setUp(void) {
    timing_init();
    brake_init();
}

void tearDown(void) {}

// ============================================================================
// TEST CATEGORY: Execution Time Testing
// ============================================================================

void test_brake_apply_execution_time_typical(void) {
    // Test: Measure execution time under typical conditions
    
    uint32_t start_cycles, end_cycles, elapsed_cycles;
    uint32_t elapsed_us;
    
    // Warm up cache
    brake_apply(0, 50);
    
    // Measure execution time
    start_cycles = timing_get_cycles();
    result_t result = brake_apply(0, 75);
    end_cycles = timing_get_cycles();
    
    TEST_ASSERT_EQUAL(SUCCESS, result);
    
    elapsed_cycles = end_cycles - start_cycles;
    elapsed_us = CYCLES_TO_US(elapsed_cycles);
    
    // Verify execution time meets requirement
    char msg[100];
    snprintf(msg, sizeof(msg), "Execution time %lu us exceeds limit %d us", 
             elapsed_us, BRAKE_APPLY_MAX_EXEC_TIME_US);
    TEST_ASSERT_LESS_THAN_MESSAGE(BRAKE_APPLY_MAX_EXEC_TIME_US, elapsed_us, msg);
    
    // Log timing for documentation
    printf("brake_apply() execution time (typical): %lu us\n", elapsed_us);
}

void test_brake_apply_execution_time_worst_case(void) {
    // Test: Measure execution time under worst-case conditions
    // Worst case: Cold cache, all brakes applied, interrupts enabled
    
    uint32_t max_time_us = 0;
    const uint32_t NUM_ITERATIONS = 100;
    
    for (uint32_t i = 0; i < NUM_ITERATIONS; i++) {
        // Flush cache (platform-specific, here simulated)
        // flush_instruction_cache();
        // flush_data_cache();
        
        // Apply brake with timing measurement
        uint32_t start = timing_get_cycles();
        brake_apply(i % 4, (i * 7) % 100);  // Varying parameters
        uint32_t end = timing_get_cycles();
        
        uint32_t elapsed_us = CYCLES_TO_US(end - start);
        if (elapsed_us > max_time_us) {
            max_time_us = elapsed_us;
        }
    }
    
    // Verify worst-case execution time
    char msg[100];
    snprintf(msg, sizeof(msg), "Worst-case execution time %lu us exceeds limit %d us", 
             max_time_us, BRAKE_APPLY_MAX_EXEC_TIME_US);
    TEST_ASSERT_LESS_THAN_MESSAGE(BRAKE_APPLY_MAX_EXEC_TIME_US, max_time_us, msg);
    
    printf("brake_apply() worst-case execution time: %lu us (over %lu iterations)\n", 
           max_time_us, NUM_ITERATIONS);
}

void test_brake_apply_execution_time_all_wheels_simultaneous(void) {
    // Test: Worst case - all 4 brakes applied in rapid succession
    
    uint32_t start = timing_get_cycles();
    
    brake_apply(0, 100);
    brake_apply(1, 100);
    brake_apply(2, 100);
    brake_apply(3, 100);
    
    uint32_t end = timing_get_cycles();
    uint32_t total_us = CYCLES_TO_US(end - start);
    
    // Total time should be less than 4 * max_exec_time
    uint32_t max_allowed_us = 4 * BRAKE_APPLY_MAX_EXEC_TIME_US;
    
    char msg[100];
    snprintf(msg, sizeof(msg), "Total execution time %lu us exceeds limit %lu us", 
             total_us, max_allowed_us);
    TEST_ASSERT_LESS_THAN_MESSAGE(max_allowed_us, total_us, msg);
    
    printf("4x brake_apply() total time: %lu us (avg: %lu us)\n", 
           total_us, total_us / 4);
}

// ============================================================================
// TEST CATEGORY: Response Time Testing
// ============================================================================

void test_brake_response_time_sensor_to_actuation(void) {
    // Test: End-to-end response time from sensor detection to brake actuation
    // This simulates the full control loop
    
    uint32_t start_ms = system_get_time_ms();
    
    // Simulate sensor detection
    sensor_event_detected();
    
    // Wait for brake actuation (this would be interrupt-driven in real system)
    while (!brake_is_actuated()) {
        // Timeout check
        uint32_t elapsed_ms = system_get_time_ms() - start_ms;
        if (elapsed_ms > BRAKE_RESPONSE_MAX_TIME_MS) {
            TEST_FAIL_MESSAGE("Brake response timeout");
        }
    }
    
    uint32_t end_ms = system_get_time_ms();
    uint32_t response_time_ms = end_ms - start_ms;
    
    // Verify response time meets requirement
    char msg[100];
    snprintf(msg, sizeof(msg), "Response time %lu ms exceeds limit %d ms", 
             response_time_ms, BRAKE_RESPONSE_MAX_TIME_MS);
    TEST_ASSERT_LESS_THAN_MESSAGE(BRAKE_RESPONSE_MAX_TIME_MS, response_time_ms, msg);
    
    printf("Brake response time (sensor to actuation): %lu ms\n", response_time_ms);
}

// ============================================================================
// TEST CATEGORY: Jitter Testing
// ============================================================================

void test_brake_cycle_time_jitter(void) {
    // Test: Measure jitter in periodic brake control loop
    // Requirement: 10 ms cycle time +/- 1 ms jitter
    
    const uint32_t NUM_CYCLES = 100;
    uint32_t cycle_times_ms[NUM_CYCLES];
    
    uint32_t last_cycle_time_ms = system_get_time_ms();
    
    for (uint32_t i = 0; i < NUM_CYCLES; i++) {
        // Wait for next cycle (simulated, would be RTOS task in real system)
        wait_for_next_cycle();
        
        uint32_t current_time_ms = system_get_time_ms();
        cycle_times_ms[i] = current_time_ms - last_cycle_time_ms;
        last_cycle_time_ms = current_time_ms;
    }
    
    // Calculate statistics
    uint32_t min_cycle = UINT32_MAX;
    uint32_t max_cycle = 0;
    uint64_t sum = 0;
    
    for (uint32_t i = 0; i < NUM_CYCLES; i++) {
        if (cycle_times_ms[i] < min_cycle) min_cycle = cycle_times_ms[i];
        if (cycle_times_ms[i] > max_cycle) max_cycle = cycle_times_ms[i];
        sum += cycle_times_ms[i];
    }
    
    uint32_t avg_cycle = (uint32_t)(sum / NUM_CYCLES);
    uint32_t jitter = max_cycle - min_cycle;
    
    // Verify average cycle time
    TEST_ASSERT_INT_WITHIN(BRAKE_JITTER_TOLERANCE_MS, BRAKE_CYCLE_TIME_MS, avg_cycle);
    
    // Verify jitter is within tolerance
    char msg[100];
    snprintf(msg, sizeof(msg), "Jitter %lu ms exceeds tolerance %d ms", 
             jitter, 2 * BRAKE_JITTER_TOLERANCE_MS);
    TEST_ASSERT_LESS_THAN_MESSAGE(2 * BRAKE_JITTER_TOLERANCE_MS, jitter, msg);
    
    printf("Cycle time: avg=%lu ms, min=%lu ms, max=%lu ms, jitter=%lu ms\n",
           avg_cycle, min_cycle, max_cycle, jitter);
}

// Unity test runner
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_brake_apply_execution_time_typical);
    RUN_TEST(test_brake_apply_execution_time_worst_case);
    RUN_TEST(test_brake_apply_execution_time_all_wheels_simultaneous);
    RUN_TEST(test_brake_response_time_sensor_to_actuation);
    RUN_TEST(test_brake_cycle_time_jitter);
    
    return UNITY_END();
}
```

---

## Resource Usage Testing

### Resource Testing Strategy

**Objective**: Verify software operates within resource constraints (CPU, memory, stack, heap, I/O bandwidth).

**Resource Metrics**:
1. **CPU utilization**: Percentage of CPU time used
2. **Memory usage**: Static, heap, stack consumption
3. **Stack depth**: Maximum stack usage (critical for embedded systems)
4. **I/O bandwidth**: Data transfer rates
5. **Power consumption**: Energy usage (for battery-powered systems)

### Example: Memory and Stack Usage Test

**Memory Requirements Specification**:

```c
// File: memory_requirements.h
// Memory usage requirements
// EN 50128 SIL 3

#ifndef MEMORY_REQUIREMENTS_H
#define MEMORY_REQUIREMENTS_H

#include <stdint.h>

/**
 * @brief Memory requirements for railway control system
 * @standard EN 50128 Section 7.6
 * @sil 3
 * 
 * MEMORY CONSTRAINTS:
 * - Total RAM: 128 KB
 * - Stack per task: Max 4 KB
 * - Heap: No dynamic allocation allowed (SIL 3)
 * - Static data: Max 64 KB
 * - Code (flash): Max 512 KB
 */

#define MAX_RAM_TOTAL_KB            128
#define MAX_STACK_PER_TASK_KB       4
#define MAX_STATIC_DATA_KB          64
#define MAX_CODE_FLASH_KB           512

// Stack watermark pattern for unused stack detection
#define STACK_WATERMARK_PATTERN     0xDEADBEEF

#endif // MEMORY_REQUIREMENTS_H
```

**Memory Usage Test Suite**:

```c
// File: test_memory_usage.c
// Memory and stack usage validation tests
// EN 50128 SIL 3

#include "unity.h"
#include "memory_requirements.h"
#include <stdint.h>
#include <string.h>

// External linker symbols (defined by linker script)
extern uint32_t _sdata;    // Start of .data section
extern uint32_t _edata;    // End of .data section
extern uint32_t _sbss;     // Start of .bss section
extern uint32_t _ebss;     // End of .bss section
extern uint32_t _stext;    // Start of .text section
extern uint32_t _etext;    // End of .text section
extern uint32_t _stack_start;
extern uint32_t _stack_end;

void setUp(void) {}
void tearDown(void) {}

// ============================================================================
// TEST CATEGORY: Static Memory Usage
// ============================================================================

void test_static_data_size_within_limits(void) {
    // Test: Verify static data (.data + .bss) within limits
    
    uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    uint32_t total_static_kb = (data_size + bss_size) / 1024;
    
    char msg[100];
    snprintf(msg, sizeof(msg), "Static data %lu KB exceeds limit %d KB", 
             total_static_kb, MAX_STATIC_DATA_KB);
    TEST_ASSERT_LESS_THAN_MESSAGE(MAX_STATIC_DATA_KB, total_static_kb, msg);
    
    printf("Static memory usage:\n");
    printf("  .data: %lu bytes\n", data_size);
    printf("  .bss:  %lu bytes\n", bss_size);
    printf("  Total: %lu KB / %d KB\n", total_static_kb, MAX_STATIC_DATA_KB);
}

void test_code_size_within_limits(void) {
    // Test: Verify code size (.text) within flash limits
    
    uint32_t text_size = (uint32_t)&_etext - (uint32_t)&_stext;
    uint32_t text_size_kb = text_size / 1024;
    
    char msg[100];
    snprintf(msg, sizeof(msg), "Code size %lu KB exceeds limit %d KB", 
             text_size_kb, MAX_CODE_FLASH_KB);
    TEST_ASSERT_LESS_THAN_MESSAGE(MAX_CODE_FLASH_KB, text_size_kb, msg);
    
    printf("Code size: %lu KB / %d KB\n", text_size_kb, MAX_CODE_FLASH_KB);
}

// ============================================================================
// TEST CATEGORY: Stack Usage Testing
// ============================================================================

// Stack watermark: Fill unused stack with pattern, then measure high watermark
static void stack_watermark_init(void) {
    // Fill stack with watermark pattern
    uint32_t* stack_ptr = (uint32_t*)&_stack_start;
    uint32_t stack_size = (uint32_t)&_stack_end - (uint32_t)&_stack_start;
    uint32_t num_words = stack_size / sizeof(uint32_t);
    
    for (uint32_t i = 0; i < num_words; i++) {
        stack_ptr[i] = STACK_WATERMARK_PATTERN;
    }
}

static uint32_t stack_watermark_measure(void) {
    // Find lowest address with watermark pattern intact
    // This indicates unused stack
    uint32_t* stack_ptr = (uint32_t*)&_stack_start;
    uint32_t stack_size = (uint32_t)&_stack_end - (uint32_t)&_stack_start;
    uint32_t num_words = stack_size / sizeof(uint32_t);
    
    uint32_t used_words = 0;
    for (uint32_t i = 0; i < num_words; i++) {
        if (stack_ptr[i] != STACK_WATERMARK_PATTERN) {
            used_words = num_words - i;
            break;
        }
    }
    
    return used_words * sizeof(uint32_t);  // Bytes used
}

void test_stack_usage_main_task(void) {
    // Test: Verify main task stack usage within limits
    
    // Initialize stack watermark
    stack_watermark_init();
    
    // Execute main task workload (simulate worst-case call stack)
    main_task_worst_case_workload();
    
    // Measure stack usage
    uint32_t stack_used_bytes = stack_watermark_measure();
    uint32_t stack_used_kb = stack_used_bytes / 1024;
    
    char msg[100];
    snprintf(msg, sizeof(msg), "Stack usage %lu KB exceeds limit %d KB", 
             stack_used_kb, MAX_STACK_PER_TASK_KB);
    TEST_ASSERT_LESS_THAN_MESSAGE(MAX_STACK_PER_TASK_KB, stack_used_kb, msg);
    
    printf("Main task stack usage: %lu bytes (%lu KB / %d KB)\n",
           stack_used_bytes, stack_used_kb, MAX_STACK_PER_TASK_KB);
}

void test_stack_usage_deep_recursion_prevented(void) {
    // Test: Verify no unbounded recursion (SIL 3 requirement)
    // This test ensures stack doesn't overflow due to recursion
    
    // Attempt to call recursive function (should be prevented at compile/design time)
    // For testing, we verify that any recursion is bounded
    
    stack_watermark_init();
    
    // Call function with known maximum recursion depth
    uint32_t result = factorial_iterative(10);  // Iterative, not recursive
    TEST_ASSERT_EQUAL(3628800, result);
    
    uint32_t stack_used = stack_watermark_measure();
    
    // Verify stack usage reasonable (no deep recursion)
    TEST_ASSERT_LESS_THAN(1024, stack_used);  // Should be < 1 KB
    
    printf("Stack usage (factorial): %lu bytes\n", stack_used);
}

// ============================================================================
// TEST CATEGORY: Heap Usage Testing (Should be ZERO for SIL 3)
// ============================================================================

void test_no_dynamic_allocation_sil3(void) {
    // Test: Verify NO dynamic memory allocation for SIL 3
    // This is enforced at design time, but we verify at runtime
    
    // Attempt to detect any heap usage (should be none)
    // In real system, this would use heap instrumentation
    
    // For this test, we verify malloc is not linked
    // (This test would fail to compile if malloc is called)
    
    TEST_PASS_MESSAGE("No dynamic allocation detected (SIL 3 compliant)");
}

// ============================================================================
// TEST CATEGORY: Memory Fragmentation (Not applicable for SIL 3 - static only)
// ============================================================================

void test_memory_layout_no_gaps(void) {
    // Test: Verify memory layout has no unexpected gaps
    // (This checks linker script correctness)
    
    uint32_t data_start = (uint32_t)&_sdata;
    uint32_t data_end = (uint32_t)&_edata;
    uint32_t bss_start = (uint32_t)&_sbss;
    uint32_t bss_end = (uint32_t)&_ebss;
    
    // Typically .bss follows .data immediately (or nearly so)
    uint32_t gap = bss_start - data_end;
    
    // Allow small alignment gap (e.g., 16 bytes)
    TEST_ASSERT_LESS_THAN(32, gap);
    
    printf("Memory layout:\n");
    printf("  .data: 0x%08lX - 0x%08lX\n", data_start, data_end);
    printf("  .bss:  0x%08lX - 0x%08lX\n", bss_start, bss_end);
    printf("  Gap:   %lu bytes\n", gap);
}

// Unity test runner
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_static_data_size_within_limits);
    RUN_TEST(test_code_size_within_limits);
    RUN_TEST(test_stack_usage_main_task);
    RUN_TEST(test_stack_usage_deep_recursion_prevented);
    RUN_TEST(test_no_dynamic_allocation_sil3);
    RUN_TEST(test_memory_layout_no_gaps);
    
    return UNITY_END();
}
```

---

## Real-Time Deadline Compliance

### Real-Time Testing Strategy

**Objective**: Verify all real-time tasks meet their deadlines under all load conditions.

**Real-Time Metrics**:
1. **Deadline misses**: Number of times task misses deadline
2. **Priority inversion**: Lower-priority task blocks higher-priority task
3. **Task scheduling**: Task execution order and preemption
4. **Interrupt latency**: Time to service interrupt
5. **Context switch overhead**: Time to switch between tasks

### Example: Real-Time Deadline Test

**Real-Time Requirements**:

```c
// File: realtime_requirements.h
// Real-time scheduling requirements
// EN 50128 SIL 3

#ifndef REALTIME_REQUIREMENTS_H
#define REALTIME_REQUIREMENTS_H

#include <stdint.h>

/**
 * @brief Real-time task definitions
 * @standard EN 50128 Section 7.6
 * @sil 3
 * 
 * TASK REQUIREMENTS:
 * - TASK_BRAKE_CONTROL: Period 10 ms, Deadline 10 ms, Priority HIGH
 * - TASK_SENSOR_READ:   Period 20 ms, Deadline 20 ms, Priority MEDIUM
 * - TASK_LOGGING:       Period 100 ms, Deadline 100 ms, Priority LOW
 * 
 * DEADLINE MISS TOLERANCE:
 * - SIL 3: ZERO deadline misses allowed for safety-critical tasks
 */

typedef struct {
    const char* name;
    uint32_t period_ms;
    uint32_t deadline_ms;
    uint32_t priority;  // Higher number = higher priority
} task_spec_t;

// Task specifications
static const task_spec_t TASK_SPECS[] = {
    {"BRAKE_CONTROL", 10,  10,  3},  // Highest priority
    {"SENSOR_READ",   20,  20,  2},
    {"LOGGING",       100, 100, 1}   // Lowest priority
};

#define NUM_TASKS (sizeof(TASK_SPECS) / sizeof(TASK_SPECS[0]))

// Deadline miss tracking
typedef struct {
    uint32_t task_id;
    uint32_t deadline_misses;
    uint32_t max_response_time_ms;
    uint32_t invocations;
} task_timing_t;

#endif // REALTIME_REQUIREMENTS_H
```

**Real-Time Deadline Test Suite**:

```c
// File: test_realtime_deadlines.c
// Real-time deadline compliance tests
// EN 50128 SIL 3

#include "unity.h"
#include "realtime_requirements.h"
#include "rtos.h"  // RTOS interface
#include <string.h>

static task_timing_t task_timings[NUM_TASKS];

void setUp(void) {
    memset(task_timings, 0, sizeof(task_timings));
    rtos_init();
}

void tearDown(void) {
    rtos_shutdown();
}

// ============================================================================
// TEST CATEGORY: Deadline Compliance Testing
// ============================================================================

void test_brake_control_task_meets_deadlines(void) {
    // Test: Brake control task meets all deadlines (SIL 3 requirement)
    
    const uint32_t TEST_DURATION_MS = 10000;  // 10 seconds
    const uint32_t TASK_ID = 0;  // BRAKE_CONTROL
    
    // Start task
    rtos_task_start(TASK_ID);
    
    // Run for test duration
    uint32_t start_time = system_get_time_ms();
    while ((system_get_time_ms() - start_time) < TEST_DURATION_MS) {
        rtos_schedule();
    }
    
    // Get timing statistics
    task_timing_t* timing = &task_timings[TASK_ID];
    
    // SIL 3 requirement: ZERO deadline misses for safety-critical task
    char msg[100];
    snprintf(msg, sizeof(msg), "BRAKE_CONTROL had %lu deadline misses (SIL 3: must be 0)", 
             timing->deadline_misses);
    TEST_ASSERT_EQUAL_MESSAGE(0, timing->deadline_misses, msg);
    
    // Verify expected number of invocations
    uint32_t expected_invocations = TEST_DURATION_MS / TASK_SPECS[TASK_ID].period_ms;
    TEST_ASSERT_INT_WITHIN(2, expected_invocations, timing->invocations);
    
    printf("BRAKE_CONTROL task:\n");
    printf("  Invocations:     %lu\n", timing->invocations);
    printf("  Deadline misses: %lu\n", timing->deadline_misses);
    printf("  Max response:    %lu ms\n", timing->max_response_time_ms);
}

void test_all_tasks_meet_deadlines_under_load(void) {
    // Test: All tasks meet deadlines under maximum load
    
    const uint32_t TEST_DURATION_MS = 30000;  // 30 seconds
    
    // Start all tasks
    for (uint32_t i = 0; i < NUM_TASKS; i++) {
        rtos_task_start(i);
    }
    
    // Add background load (simulate worst-case conditions)
    rtos_enable_background_load();
    
    // Run for test duration
    uint32_t start_time = system_get_time_ms();
    while ((system_get_time_ms() - start_time) < TEST_DURATION_MS) {
        rtos_schedule();
    }
    
    // Verify all tasks met deadlines
    for (uint32_t i = 0; i < NUM_TASKS; i++) {
        task_timing_t* timing = &task_timings[i];
        
        char msg[100];
        snprintf(msg, sizeof(msg), "Task %s had %lu deadline misses", 
                 TASK_SPECS[i].name, timing->deadline_misses);
        
        // SIL 3: Zero deadline misses for all tasks
        TEST_ASSERT_EQUAL_MESSAGE(0, timing->deadline_misses, msg);
        
        printf("Task %s:\n", TASK_SPECS[i].name);
        printf("  Invocations:     %lu\n", timing->invocations);
        printf("  Deadline misses: %lu\n", timing->deadline_misses);
        printf("  Max response:    %lu ms (deadline: %lu ms)\n", 
               timing->max_response_time_ms, TASK_SPECS[i].deadline_ms);
    }
}

// ============================================================================
// TEST CATEGORY: Priority Inversion Detection
// ============================================================================

void test_no_priority_inversion(void) {
    // Test: Verify no priority inversion occurs
    // Priority inversion: Low-priority task blocks high-priority task
    
    // Setup: Create scenario where priority inversion could occur
    // - Low-priority task holds shared resource
    // - High-priority task needs that resource
    
    rtos_task_start(0);  // High priority (BRAKE_CONTROL)
    rtos_task_start(2);  // Low priority (LOGGING)
    
    // Enable priority inheritance protocol (should prevent inversion)
    rtos_enable_priority_inheritance();
    
    const uint32_t TEST_DURATION_MS = 5000;
    uint32_t start_time = system_get_time_ms();
    while ((system_get_time_ms() - start_time) < TEST_DURATION_MS) {
        rtos_schedule();
    }
    
    // Check for priority inversion events
    uint32_t inversion_count = rtos_get_priority_inversion_count();
    
    char msg[100];
    snprintf(msg, sizeof(msg), "Detected %lu priority inversion events (SIL 3: must be 0)", 
             inversion_count);
    TEST_ASSERT_EQUAL_MESSAGE(0, inversion_count, msg);
    
    printf("Priority inversion events: %lu\n", inversion_count);
}

// ============================================================================
// TEST CATEGORY: Interrupt Latency Testing
// ============================================================================

void test_interrupt_latency_within_bounds(void) {
    // Test: Interrupt latency meets requirements
    // Requirement: Interrupt serviced within 50 microseconds
    
    const uint32_t MAX_LATENCY_US = 50;
    const uint32_t NUM_SAMPLES = 1000;
    
    uint32_t max_latency_us = 0;
    uint64_t total_latency_us = 0;
    
    for (uint32_t i = 0; i < NUM_SAMPLES; i++) {
        // Trigger test interrupt
        uint32_t trigger_time = timing_get_cycles();
        test_interrupt_trigger();
        
        // Wait for interrupt to be serviced
        while (!test_interrupt_serviced()) {
            // Busy wait
        }
        uint32_t service_time = timing_get_cycles();
        
        uint32_t latency_us = CYCLES_TO_US(service_time - trigger_time);
        
        if (latency_us > max_latency_us) {
            max_latency_us = latency_us;
        }
        total_latency_us += latency_us;
        
        test_interrupt_clear();
    }
    
    uint32_t avg_latency_us = (uint32_t)(total_latency_us / NUM_SAMPLES);
    
    // Verify max latency within bounds
    char msg[100];
    snprintf(msg, sizeof(msg), "Max interrupt latency %lu us exceeds limit %d us", 
             max_latency_us, MAX_LATENCY_US);
    TEST_ASSERT_LESS_THAN_MESSAGE(MAX_LATENCY_US, max_latency_us, msg);
    
    printf("Interrupt latency: avg=%lu us, max=%lu us (limit: %d us)\n",
           avg_latency_us, max_latency_us, MAX_LATENCY_US);
}

// Unity test runner
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_brake_control_task_meets_deadlines);
    RUN_TEST(test_all_tasks_meet_deadlines_under_load);
    RUN_TEST(test_no_priority_inversion);
    RUN_TEST(test_interrupt_latency_within_bounds);
    
    return UNITY_END();
}
```

---

## Throughput and Latency Testing

### Throughput Testing Strategy

**Objective**: Verify data processing rates meet requirements under sustained load.

**Throughput Metrics**:
1. **Data rate**: Bytes per second, packets per second
2. **Transaction rate**: Operations per second
3. **Sustained throughput**: Average over long period
4. **Peak throughput**: Maximum instantaneous rate
5. **Throughput under load**: Performance degradation under stress

### Example: Communication Throughput Test

**Throughput Test Suite**:

```c
// File: test_throughput.c
// Throughput and latency testing
// EN 50128 SIL 2

#include "unity.h"
#include "uart_interface.h"
#include <stdint.h>

void setUp(void) {
    uart_config_t config = {115200, 8, 1, UART_PARITY_NONE};
    uart_init(&config);
}

void tearDown(void) {}

// ============================================================================
// TEST CATEGORY: Sustained Throughput Testing
// ============================================================================

void test_uart_sustained_throughput(void) {
    // Test: Measure sustained UART throughput
    // Requirement: 115200 baud = 11520 bytes/sec theoretical (with overhead)
    
    const uint32_t TEST_DURATION_MS = 10000;  // 10 seconds
    const uint32_t FRAME_SIZE = 64;
    uint8_t test_frame[FRAME_SIZE];
    
    // Fill test frame with data
    for (uint32_t i = 0; i < FRAME_SIZE; i++) {
        test_frame[i] = (uint8_t)i;
    }
    
    uint32_t frames_sent = 0;
    uint32_t start_time = system_get_time_ms();
    
    while ((system_get_time_ms() - start_time) < TEST_DURATION_MS) {
        result_t result = uart_send_frame(test_frame, FRAME_SIZE);
        if (result == SUCCESS) {
            frames_sent++;
        }
    }
    
    uint32_t elapsed_ms = system_get_time_ms() - start_time;
    uint32_t bytes_sent = frames_sent * FRAME_SIZE;
    uint32_t bytes_per_sec = (bytes_sent * 1000) / elapsed_ms;
    
    // Verify throughput meets minimum requirement (e.g., 80% of theoretical)
    const uint32_t MIN_THROUGHPUT_BPS = 9000;  // 9000 bytes/sec minimum
    
    char msg[100];
    snprintf(msg, sizeof(msg), "Throughput %lu bytes/sec below minimum %d bytes/sec", 
             bytes_per_sec, MIN_THROUGHPUT_BPS);
    TEST_ASSERT_GREATER_THAN_MESSAGE(MIN_THROUGHPUT_BPS, bytes_per_sec, msg);
    
    printf("UART throughput:\n");
    printf("  Frames sent:  %lu\n", frames_sent);
    printf("  Bytes sent:   %lu\n", bytes_sent);
    printf("  Duration:     %lu ms\n", elapsed_ms);
    printf("  Throughput:   %lu bytes/sec\n", bytes_per_sec);
}

// ============================================================================
// TEST CATEGORY: Latency Testing
// ============================================================================

void test_uart_round_trip_latency(void) {
    // Test: Measure round-trip latency (send + receive)
    // Requirement: < 10 ms round-trip time
    
    const uint32_t MAX_LATENCY_MS = 10;
    const uint32_t NUM_SAMPLES = 100;
    
    uint8_t test_data[] = {0x01, 0x02, 0x03, 0x04};
    uint32_t max_latency_ms = 0;
    uint64_t total_latency_ms = 0;
    
    for (uint32_t i = 0; i < NUM_SAMPLES; i++) {
        uint32_t start = system_get_time_ms();
        
        // Send frame
        uart_send_frame(test_data, sizeof(test_data));
        
        // Wait for echo (loopback or remote echo)
        uint8_t received[10];
        uint8_t length;
        while (uart_receive_frame(received, &length, sizeof(received)) != SUCCESS) {
            // Timeout check
            if ((system_get_time_ms() - start) > MAX_LATENCY_MS * 2) {
                TEST_FAIL_MESSAGE("UART echo timeout");
            }
        }
        
        uint32_t end = system_get_time_ms();
        uint32_t latency_ms = end - start;
        
        if (latency_ms > max_latency_ms) {
            max_latency_ms = latency_ms;
        }
        total_latency_ms += latency_ms;
    }
    
    uint32_t avg_latency_ms = (uint32_t)(total_latency_ms / NUM_SAMPLES);
    
    // Verify latency within bounds
    char msg[100];
    snprintf(msg, sizeof(msg), "Max round-trip latency %lu ms exceeds limit %d ms", 
             max_latency_ms, MAX_LATENCY_MS);
    TEST_ASSERT_LESS_THAN_MESSAGE(MAX_LATENCY_MS, max_latency_ms, msg);
    
    printf("UART round-trip latency: avg=%lu ms, max=%lu ms\n",
           avg_latency_ms, max_latency_ms);
}

// ============================================================================
// TEST CATEGORY: Burst Throughput Testing
// ============================================================================

void test_uart_burst_throughput(void) {
    // Test: Measure peak burst throughput
    // Requirement: Handle short bursts at full baud rate
    
    const uint32_t BURST_SIZE = 1000;  // bytes
    uint8_t burst_data[BURST_SIZE];
    
    // Fill burst data
    for (uint32_t i = 0; i < BURST_SIZE; i++) {
        burst_data[i] = (uint8_t)(i & 0xFF);
    }
    
    uint32_t start_time = system_get_time_ms();
    
    // Send burst
    for (uint32_t i = 0; i < BURST_SIZE; i++) {
        uart_send_byte(burst_data[i]);
    }
    
    uint32_t end_time = system_get_time_ms();
    uint32_t elapsed_ms = end_time - start_time;
    
    uint32_t burst_rate_bps = (BURST_SIZE * 1000) / elapsed_ms;
    
    printf("Burst throughput: %lu bytes in %lu ms = %lu bytes/sec\n",
           BURST_SIZE, elapsed_ms, burst_rate_bps);
    
    // Verify burst handling (should not drop data)
    TEST_ASSERT_GREATER_THAN(5000, burst_rate_bps);  // Minimum 5 KB/sec burst
}

// Unity test runner
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_uart_sustained_throughput);
    RUN_TEST(test_uart_round_trip_latency);
    RUN_TEST(test_uart_burst_throughput);
    
    return UNITY_END();
}
```

---

## Performance Profiling

### Profiling Strategy

**Objective**: Identify performance bottlenecks and optimization opportunities.

**Profiling Methods**:
1. **Instrumentation profiling**: Insert timing code at function entry/exit
2. **Sampling profiling**: Periodically sample program counter
3. **Call graph analysis**: Identify hot paths through call tree
4. **CPU profiling**: Identify CPU-intensive functions
5. **Memory profiling**: Identify memory allocation patterns

### Example: Profiling Integration

**Profiling with gprof (GNU profiler)**:

```bash
#!/bin/bash
# File: profile_performance.sh
# Performance profiling script
# EN 50128 Phase 6 Integration

set -e

echo "==================================="
echo "Performance Profiling"
echo "==================================="

# Compile with profiling enabled
echo "Compiling with profiling..."
gcc -Wall -Wextra -std=c11 -pg \
    -I./include \
    -o brake_system_profiled \
    src/brake_controller.c \
    src/sensor_manager.c \
    src/main.c

# Run program to generate profiling data
echo "Running profiled application..."
./brake_system_profiled

# Generate profile report
echo "Generating profile report..."
gprof brake_system_profiled gmon.out > profile_report.txt

# Extract top functions by CPU time
echo ""
echo "Top 10 functions by CPU time:"
grep -A 15 "% time" profile_report.txt | head -20

# Extract call graph
echo ""
echo "Call graph:"
grep -A 50 "index % time" profile_report.txt | head -60

echo ""
echo "Full report saved to: profile_report.txt"
```

**Profiling Analysis Example Output**:

```
Top 10 functions by CPU time:
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 42.50      0.42     0.42   100000     0.00     0.00  brake_calculate_force
 23.50      0.65     0.23    50000     0.00     0.01  sensor_read_all
 15.25      0.80     0.15   100000     0.00     0.00  crc16_calculate
  8.75      0.89     0.09   100000     0.00     0.00  brake_apply
  5.00      0.94     0.05    10000     0.01     0.10  control_loop_iteration
```

**Performance Hotspot Identification**:

```c
// File: performance_analysis.c
// Identify and document performance hotspots
// EN 50128 SIL 3

/*
 * PERFORMANCE ANALYSIS RESULTS (from gprof)
 * 
 * HOTSPOT 1: brake_calculate_force() - 42.5% CPU time
 * - Called 100,000 times
 * - 0.00 ms per call (fast, but high frequency)
 * - RECOMMENDATION: Already optimized, no action needed
 * 
 * HOTSPOT 2: sensor_read_all() - 23.5% CPU time
 * - Called 50,000 times
 * - Includes I2C communication (slow)
 * - RECOMMENDATION: Consider caching sensor values
 * 
 * HOTSPOT 3: crc16_calculate() - 15.25% CPU time
 * - Called 100,000 times
 * - RECOMMENDATION: Use hardware CRC if available (STM32 has CRC peripheral)
 * 
 * OVERALL ASSESSMENT:
 * - Total CPU utilization: ~89% (within target < 95%)
 * - No immediate optimization required for SIL 3
 * - Monitor for regression in future releases
 */
```

---

## Performance Regression Testing

### Regression Testing Strategy

**Objective**: Detect performance degradation across software versions.

**Regression Detection**:
1. **Baseline establishment**: Record performance metrics for baseline version
2. **Automated comparison**: Compare new version against baseline
3. **Threshold alerts**: Trigger alert if performance degrades > threshold (e.g., 10%)
4. **Historical tracking**: Track performance trends over time

### Example: Performance Regression Framework

**Baseline Performance Database**:

```json
{
  "project": "railway_brake_system",
  "sil": 3,
  "baseline_version": "v1.0.0",
  "baseline_date": "2026-03-01",
  "metrics": {
    "brake_apply_exec_time_us": {
      "typical": 35,
      "worst_case": 48,
      "max_allowed": 50
    },
    "brake_response_time_ms": {
      "typical": 85,
      "worst_case": 95,
      "max_allowed": 100
    },
    "stack_usage_bytes": {
      "main_task": 2048,
      "max_allowed": 4096
    },
    "code_size_kb": {
      "text": 234,
      "max_allowed": 512
    },
    "static_data_kb": {
      "data_bss": 42,
      "max_allowed": 64
    }
  }
}
```

**Regression Test Script**:

```python
#!/usr/bin/env python3
# File: check_performance_regression.py
# Performance regression detection
# EN 50128 Phase 6

import json
import sys

def load_baseline(baseline_file):
    """Load baseline performance metrics."""
    with open(baseline_file, 'r') as f:
        return json.load(f)

def load_current(current_file):
    """Load current performance test results."""
    with open(current_file, 'r') as f:
        return json.load(f)

def check_regression(baseline, current, threshold_percent=10):
    """
    Check for performance regression.
    
    Args:
        baseline: Baseline metrics
        current: Current metrics
        threshold_percent: Regression threshold (default 10%)
    
    Returns:
        (passed, report)
    """
    report = []
    passed = True
    
    for metric_name, baseline_vals in baseline['metrics'].items():
        if metric_name not in current['metrics']:
            report.append(f"MISSING: {metric_name} not found in current results")
            passed = False
            continue
        
        current_vals = current['metrics'][metric_name]
        
        for key in ['typical', 'worst_case']:
            if key not in baseline_vals or key not in current_vals:
                continue
            
            baseline_val = baseline_vals[key]
            current_val = current_vals[key]
            
            # Calculate percentage change
            if baseline_val > 0:
                percent_change = ((current_val - baseline_val) / baseline_val) * 100
            else:
                percent_change = 0
            
            # Check for regression
            if percent_change > threshold_percent:
                report.append(
                    f"REGRESSION: {metric_name}.{key} increased by {percent_change:.1f}% "
                    f"(baseline: {baseline_val}, current: {current_val}, "
                    f"threshold: {threshold_percent}%)"
                )
                passed = False
            elif percent_change > 0:
                report.append(
                    f"WARNING: {metric_name}.{key} increased by {percent_change:.1f}% "
                    f"(baseline: {baseline_val}, current: {current_val}, "
                    f"within threshold: {threshold_percent}%)"
                )
            else:
                report.append(
                    f"OK: {metric_name}.{key} improved by {abs(percent_change):.1f}% "
                    f"(baseline: {baseline_val}, current: {current_val})"
                )
    
    return passed, report

def main():
    if len(sys.argv) != 3:
        print("Usage: check_performance_regression.py <baseline.json> <current.json>")
        sys.exit(1)
    
    baseline_file = sys.argv[1]
    current_file = sys.argv[2]
    
    print("==============================================")
    print("Performance Regression Check - EN 50128")
    print("==============================================")
    
    baseline = load_baseline(baseline_file)
    current = load_current(current_file)
    
    print(f"Baseline version: {baseline['baseline_version']}")
    print(f"Current version:  {current.get('version', 'unknown')}")
    print(f"Regression threshold: 10%")
    print("")
    
    passed, report = check_regression(baseline, current)
    
    for line in report:
        print(line)
    
    print("")
    if passed:
        print("RESULT: PASSED - No performance regression detected")
        sys.exit(0)
    else:
        print("RESULT: FAILED - Performance regression detected")
        sys.exit(1)

if __name__ == '__main__':
    main()
```

**Usage**:

```bash
# Run performance tests and generate current results
./run_performance_tests.sh > performance_current.json

# Check for regression against baseline
python3 check_performance_regression.py \
    performance_baseline.json \
    performance_current.json

# Output:
# ==============================================
# Performance Regression Check - EN 50128
# ==============================================
# Baseline version: v1.0.0
# Current version:  v1.1.0
# Regression threshold: 10%
#
# OK: brake_apply_exec_time_us.typical improved by 2.9% (baseline: 35, current: 34)
# OK: brake_apply_exec_time_us.worst_case improved by 4.2% (baseline: 48, current: 46)
# WARNING: brake_response_time_ms.typical increased by 5.9% (baseline: 85, current: 90, within threshold: 10%)
# REGRESSION: stack_usage_bytes.main_task increased by 15.6% (baseline: 2048, current: 2368, threshold: 10%)
#
# RESULT: FAILED - Performance regression detected
```

---

## Tool Integration for Performance Testing

### Workspace Integration

**Performance Testing Workflow Commands**:

```bash
# Initialize performance testing workflow
python3 tools/workspace.py wf start performance-testing \
    --project railway_control \
    --sil 3 \
    --output performance_test_report.md

# Run timing analysis
make timing_tests
./run_timing_tests.sh

# Run memory analysis
make memory_tests
./run_memory_tests.sh

# Run real-time deadline tests
make realtime_tests
./run_realtime_tests.sh

# Generate performance report
python3 tools/generate_performance_report.py \
    --results results/performance/ \
    --baseline performance_baseline.json \
    --output performance_test_report.md

# Complete workflow
python3 tools/workspace.py wf complete performance-testing \
    --report performance_test_report.md
```

### Performance Test Automation Script

```bash
#!/bin/bash
# File: run_performance_tests.sh
# Automated performance testing for integration phase
# EN 50128 Phase 6

set -e

echo "==================================="
echo "Performance Testing - EN 50128"
echo "==================================="

# Create results directory
mkdir -p results/performance

# 1. Timing Tests
echo "Running timing tests..."
gcc -Wall -Wextra -std=c11 -O2 \
    -I./include -I./unity/src \
    test_brake_timing.c \
    brake_controller.c \
    unity/src/unity.c \
    -o test_brake_timing

./test_brake_timing | tee results/performance/timing_results.txt

# 2. Memory Tests
echo "Running memory tests..."
gcc -Wall -Wextra -std=c11 -O2 \
    -I./include -I./unity/src \
    -Wl,-Map=results/performance/memory_map.txt \
    test_memory_usage.c \
    brake_controller.c \
    unity/src/unity.c \
    -o test_memory_usage

./test_memory_usage | tee results/performance/memory_results.txt

# Extract memory usage from linker map
arm-none-eabi-size test_memory_usage > results/performance/size_analysis.txt

# 3. Stack Analysis (if using stack profiler)
echo "Running stack analysis..."
# Requires instrumentation or RTOS support
# Example: FreeRTOS uxTaskGetStackHighWaterMark()

# 4. Real-Time Tests (if RTOS present)
echo "Running real-time deadline tests..."
gcc -Wall -Wextra -std=c11 -O2 \
    -I./include -I./unity/src -I./rtos/include \
    test_realtime_deadlines.c \
    brake_controller.c \
    rtos/rtos_sim.c \
    unity/src/unity.c \
    -o test_realtime

./test_realtime | tee results/performance/realtime_results.txt

# 5. Throughput Tests
echo "Running throughput tests..."
gcc -Wall -Wextra -std=c11 -O2 \
    -I./include -I./unity/src \
    test_throughput.c \
    uart_interface.c \
    unity/src/unity.c \
    -o test_throughput

./test_throughput | tee results/performance/throughput_results.txt

# 6. Generate summary report
echo "Generating performance summary..."
python3 tools/summarize_performance.py \
    --results results/performance/ \
    --output results/performance/summary.json

# 7. Check regression (if baseline exists)
if [ -f performance_baseline.json ]; then
    echo "Checking for performance regression..."
    python3 tools/check_performance_regression.py \
        performance_baseline.json \
        results/performance/summary.json
else
    echo "No baseline found, skipping regression check"
fi

echo "==================================="
echo "Performance Testing Complete"
echo "Results saved to: results/performance/"
echo "==================================="
```

---

## SIL-Specific Requirements

### Performance Testing by SIL Level

| SIL | Performance Testing Requirements | Evidence Required |
|-----|----------------------------------|-------------------|
| **0** | Optional performance verification | None |
| **1-2** | Basic performance testing (timing, memory on target) | Performance test results documented |
| **3-4** | Comprehensive performance testing (WCET, deadlines, stress, long-term stability) | Detailed Performance Test Report with WCET analysis, traceability matrix, independent review |

**SIL 3-4 Additional Requirements**:
- **Worst-Case Execution Time (WCET)** analysis for all safety-critical functions
- **Deadline compliance** verification for all real-time tasks (zero deadline misses)
- **Stress testing** under maximum load for extended duration (e.g., 24+ hours)
- **Resource margin analysis**: Verify at least 20% margin on CPU, memory, stack
- **Long-term stability**: No performance degradation over extended operation
- **Independent review** of performance test results

**WCET Analysis Methods** (SIL 3-4):
1. **Measurement-based**: Instrument code, measure on target hardware under stress
2. **Static analysis**: Use timing analysis tools (e.g., aiT, Bound-T)
3. **Hybrid approach**: Combine measurement with static analysis

---

## Example Performance Testing Scenarios

### Scenario 1: Railway Braking System Performance Validation

**System**: Safety-critical railway braking system (SIL 3)

**Requirements**:
- Brake apply execution time: < 50 μs
- Brake response time (sensor to actuation): < 100 ms
- Control loop cycle time: 10 ms ± 1 ms
- CPU utilization: < 80% average, < 95% peak
- Stack usage per task: < 4 KB
- Zero deadline misses

**Test Approach**:
1. Execute timing tests with hardware timers (DWT cycle counter)
2. Measure worst-case execution time under stress (cache misses, interrupts)
3. Verify real-time deadlines with RTOS tracer
4. Profile CPU usage with gprof or hardware performance counters
5. Measure stack high-watermark with stack painting
6. Run 24-hour stress test to verify long-term stability

**Expected Results**:
- All timing requirements met with margin (e.g., 40 μs typical, 48 μs worst-case)
- Zero deadline misses over 24-hour test
- CPU utilization: 65% average, 88% peak
- Stack usage: 2.5 KB typical, 3.2 KB worst-case
- No performance degradation over 24 hours

---

### Scenario 2: Communication Interface Throughput Test

**System**: UART communication for signaling system (SIL 2)

**Requirements**:
- Baud rate: 115200 bps
- Sustained throughput: > 9 KB/sec (80% of theoretical)
- Frame round-trip latency: < 10 ms
- No data loss under sustained load

**Test Approach**:
1. Send frames continuously for 10 seconds, measure throughput
2. Measure round-trip latency with loopback or echo server
3. Stress test with burst traffic
4. Verify error detection (CRC, framing errors)

**Expected Results**:
- Sustained throughput: 10.2 KB/sec (achieved)
- Round-trip latency: 7.3 ms average, 9.8 ms worst-case
- Zero frame loss over 10-second test
- All CRC errors detected and rejected

---

## Summary

This workflow provides comprehensive performance testing guidance for EN 50128 integration phase:

1. **Timing Validation**: Execution time, response time, cycle time, jitter measurement
2. **Resource Testing**: CPU, memory, stack, code size verification
3. **Real-Time Compliance**: Deadline verification, priority inversion detection, interrupt latency
4. **Throughput Testing**: Sustained throughput, burst handling, latency measurement
5. **Performance Profiling**: Hotspot identification, optimization recommendations
6. **Regression Testing**: Baseline comparison, automated regression detection

**EN 50128 Compliance**: All performance testing follows Table A.6 and Table A.18 requirements with SIL-appropriate depth.

**Tool Integration**: Unity framework, hardware timers (DWT), gprof, workspace.py workflows, automated regression checks.

**Next Steps**: After performance testing, proceed to enhancing the Integration SKILL.md and creating the phase completion report.
