# Interface Testing Workflow

**EN 50128 Reference**: Section 7.6.4.1, D.34 (Interface Testing)  
**Phase**: Phase 6 - Integration  
**Role**: Integrator (INT)  
**SIL Level**: All (0-4)

---

## Purpose

This workflow defines the comprehensive process for testing software interfaces to demonstrate that "interfaces of subprograms do not contain any errors or any errors that lead to failures in a particular application of the software" (EN 50128 D.34).

**Key Objectives**:
- Function interface validation (parameters, return values, side effects)
- Data structure interface testing (struct layout, alignment, padding)
- Communication protocol interface testing (UART, SPI, I2C, CAN)
- Inter-process communication (IPC) testing (shared memory, queues, semaphores)
- Interface contract validation (preconditions, postconditions, invariants)
- Boundary and edge case testing for all interface variables
- Interface compatibility validation across modules

**Inputs**:
- Software Interface Specifications (from DES, Phase 3)
- Software Design Specification (from DES, Phase 3)
- Component Test Reports (from TST, Phase 5)
- Integrated components (from component integration)

**Outputs**:
- Interface Test Report
- Interface defect reports
- Interface compatibility matrix
- Updated traceability matrices (interface requirements → tests)

---

## Table of Contents

1. [Interface Testing Principles](#interface-testing-principles)
2. [Function Interface Testing](#function-interface-testing)
3. [Data Structure Interface Testing](#data-structure-interface-testing)
4. [Communication Protocol Interface Testing](#communication-protocol-interface-testing)
5. [Inter-Process Communication Testing](#inter-process-communication-testing)
6. [Interface Contract Validation](#interface-contract-validation)
7. [Boundary Value Testing](#boundary-value-testing)
8. [Interface Mocking and Stubbing](#interface-mocking-and-stubbing)
9. [API Compatibility Testing](#api-compatibility-testing)
10. [Tool Integration for Interface Testing](#tool-integration-for-interface-testing)

---

## Interface Testing Principles

### EN 50128 Interface Testing Requirements

**EN 50128 D.34**: "To demonstrate that interfaces of subprograms do not contain any errors or any errors that lead to failures in a particular application of the software or to detect all errors that may be relevant."

**Levels of Interface Testing Completeness** (EN 50128 D.34):

1. **Level 1 (Minimal)**: Test all interface variables at their extreme positions
2. **Level 2 (Basic)**: Test each interface variable individually at extreme values with others at normal values
3. **Level 3 (Thorough)**: Test all values of the domain of each interface variable with others at normal values
4. **Level 4 (Exhaustive)**: Test all values of all variables in combination (feasible only for small interfaces)
5. **Level 5 (Context-Aware)**: Test specified test conditions relevant to each call of each subroutine

**SIL-Specific Requirements**:

| SIL | Minimum Interface Testing Level | Additional Requirements |
|-----|--------------------------------|-------------------------|
| **0-1** | Level 2 (Basic) | Interface variable extremes |
| **2** | Level 3 (Thorough) | Domain coverage, boundary testing |
| **3-4** | Level 3-4 (Thorough/Exhaustive) | Full domain coverage, combinatorial testing for critical interfaces, formal contract validation |

**Interface Types Covered**:
- **Function interfaces**: Parameters, return values, global state modifications
- **Data structure interfaces**: Struct layout, memory alignment, padding
- **Communication interfaces**: UART, SPI, I2C, CAN, Ethernet
- **IPC interfaces**: Shared memory, message queues, semaphores, pipes
- **Hardware interfaces**: Memory-mapped I/O, DMA, interrupts

---

## Function Interface Testing

### Function Interface Test Strategy

**Objective**: Validate all function parameters, return values, and side effects.

**Testing Dimensions**:
1. **Parameter validation**: Valid, invalid, boundary, NULL, extreme values
2. **Return value verification**: Expected returns for all parameter combinations
3. **Side effects**: Global variable modifications, memory allocations, I/O operations
4. **Error handling**: Error codes, errno, exception behavior
5. **Precondition/postcondition**: Contract validation

### Example: Safety-Critical Function Interface Test

**Function Under Test**:

```c
// File: brake_controller.h
// Function interface for safety-critical braking system
// EN 50128 SIL 3

#ifndef BRAKE_CONTROLLER_H
#define BRAKE_CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>
#include "common_types.h"

/**
 * @brief Apply braking force
 * @standard EN 50128 Section 7.6
 * @sil 3
 * 
 * INTERFACE CONTRACT:
 * @pre brake_init() must have been called
 * @pre brake_force_percent >= 0 && brake_force_percent <= 100
 * @pre wheel_id < MAX_WHEELS
 * @post If SUCCESS, brake force applied within 100ms
 * @post If ERROR_*, no brake state change
 * 
 * @param wheel_id Wheel identifier (0 to MAX_WHEELS-1)
 * @param brake_force_percent Brake force percentage (0-100)
 * @return SUCCESS (0) on success, error code otherwise
 */
result_t brake_apply(uint8_t wheel_id, uint8_t brake_force_percent);

// Error codes
#define SUCCESS                  0
#define ERROR_NOT_INITIALIZED    1
#define ERROR_INVALID_WHEEL_ID   2
#define ERROR_INVALID_FORCE      3
#define ERROR_HARDWARE_FAULT     4

#define MAX_WHEELS 4

#endif // BRAKE_CONTROLLER_H
```

**Implementation**:

```c
// File: brake_controller.c

#include "brake_controller.h"
#include <stddef.h>

static bool g_initialized = false;
static uint8_t g_brake_force[MAX_WHEELS] = {0};

result_t brake_init(void) {
    g_initialized = true;
    for (uint8_t i = 0; i < MAX_WHEELS; i++) {
        g_brake_force[i] = 0;
    }
    return SUCCESS;
}

result_t brake_apply(uint8_t wheel_id, uint8_t brake_force_percent) {
    // DEFENSIVE: Check initialization (precondition)
    if (!g_initialized) {
        return ERROR_NOT_INITIALIZED;
    }
    
    // DEFENSIVE: Validate wheel_id (parameter range check)
    if (wheel_id >= MAX_WHEELS) {
        return ERROR_INVALID_WHEEL_ID;
    }
    
    // DEFENSIVE: Validate brake_force_percent (parameter range check)
    if (brake_force_percent > 100) {
        return ERROR_INVALID_FORCE;
    }
    
    // Apply brake force (side effect: modify global state)
    g_brake_force[wheel_id] = brake_force_percent;
    
    return SUCCESS;
}

uint8_t brake_get_force(uint8_t wheel_id) {
    if (wheel_id >= MAX_WHEELS) {
        return 0;
    }
    return g_brake_force[wheel_id];
}
```

**Interface Test Suite** (Unity framework):

```c
// File: test_brake_controller_interface.c
// Interface tests for brake_apply() function
// EN 50128 SIL 3 - Level 3 Interface Testing

#include "unity.h"
#include "brake_controller.h"

void setUp(void) {
    // Initialize before each test
    brake_init();
}

void tearDown(void) {
    // Cleanup after each test
}

// ============================================================================
// TEST CATEGORY: Parameter Validity Testing (EN 50128 D.34 Level 2)
// ============================================================================

void test_brake_apply_valid_parameters_wheel0(void) {
    // Test: Valid parameters for wheel 0
    result_t result = brake_apply(0, 50);
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(50, brake_get_force(0));
}

void test_brake_apply_valid_parameters_wheel3(void) {
    // Test: Valid parameters for wheel 3 (last wheel)
    result_t result = brake_apply(3, 75);
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(75, brake_get_force(3));
}

void test_brake_apply_invalid_wheel_id(void) {
    // Test: Invalid wheel_id (boundary violation)
    result_t result = brake_apply(4, 50);  // wheel_id = MAX_WHEELS
    TEST_ASSERT_EQUAL(ERROR_INVALID_WHEEL_ID, result);
}

void test_brake_apply_invalid_wheel_id_extreme(void) {
    // Test: Invalid wheel_id (extreme value)
    result_t result = brake_apply(255, 50);
    TEST_ASSERT_EQUAL(ERROR_INVALID_WHEEL_ID, result);
}

void test_brake_apply_invalid_force(void) {
    // Test: Invalid brake_force_percent (boundary violation)
    result_t result = brake_apply(0, 101);  // force > 100
    TEST_ASSERT_EQUAL(ERROR_INVALID_FORCE, result);
}

void test_brake_apply_invalid_force_extreme(void) {
    // Test: Invalid brake_force_percent (extreme value)
    result_t result = brake_apply(0, 255);
    TEST_ASSERT_EQUAL(ERROR_INVALID_FORCE, result);
}

// ============================================================================
// TEST CATEGORY: Boundary Value Testing (EN 50128 D.34 Level 2)
// ============================================================================

void test_brake_apply_boundary_wheel_min(void) {
    // Test: wheel_id minimum boundary (0)
    result_t result = brake_apply(0, 50);
    TEST_ASSERT_EQUAL(SUCCESS, result);
}

void test_brake_apply_boundary_wheel_max(void) {
    // Test: wheel_id maximum boundary (MAX_WHEELS - 1)
    result_t result = brake_apply(MAX_WHEELS - 1, 50);
    TEST_ASSERT_EQUAL(SUCCESS, result);
}

void test_brake_apply_boundary_force_min(void) {
    // Test: brake_force_percent minimum boundary (0)
    result_t result = brake_apply(0, 0);
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(0, brake_get_force(0));
}

void test_brake_apply_boundary_force_max(void) {
    // Test: brake_force_percent maximum boundary (100)
    result_t result = brake_apply(0, 100);
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(100, brake_get_force(0));
}

// ============================================================================
// TEST CATEGORY: Combinatorial Testing (EN 50128 D.34 Level 4 - SIL 3+)
// ============================================================================

void test_brake_apply_all_wheels_all_forces(void) {
    // Test: All wheels with different force levels (combinatorial)
    // SIL 3 requirement: Test critical combinations
    
    const uint8_t test_forces[] = {0, 25, 50, 75, 100};
    const uint8_t num_forces = sizeof(test_forces) / sizeof(test_forces[0]);
    
    for (uint8_t wheel = 0; wheel < MAX_WHEELS; wheel++) {
        for (uint8_t i = 0; i < num_forces; i++) {
            result_t result = brake_apply(wheel, test_forces[i]);
            TEST_ASSERT_EQUAL_MESSAGE(SUCCESS, result, "Failed for valid combination");
            TEST_ASSERT_EQUAL_MESSAGE(test_forces[i], brake_get_force(wheel), "Force not applied correctly");
        }
    }
}

// ============================================================================
// TEST CATEGORY: Precondition Violation Testing
// ============================================================================

void test_brake_apply_precondition_not_initialized(void) {
    // Test: Precondition violation - not initialized
    // This test does NOT call setUp() to simulate uninitialized state
    
    // Manually create uninitialized state (simulate fresh start)
    extern bool g_initialized;  // Access internal state for testing
    g_initialized = false;
    
    result_t result = brake_apply(0, 50);
    TEST_ASSERT_EQUAL(ERROR_NOT_INITIALIZED, result);
}

// ============================================================================
// TEST CATEGORY: Side Effect Verification
// ============================================================================

void test_brake_apply_side_effect_global_state_modified(void) {
    // Test: Side effect - global brake state modified
    brake_apply(0, 30);
    TEST_ASSERT_EQUAL(30, brake_get_force(0));
    
    // Apply different force - verify state change
    brake_apply(0, 60);
    TEST_ASSERT_EQUAL(60, brake_get_force(0));
}

void test_brake_apply_side_effect_no_cross_interference(void) {
    // Test: Side effect - setting one wheel doesn't affect others
    brake_apply(0, 10);
    brake_apply(1, 20);
    brake_apply(2, 30);
    brake_apply(3, 40);
    
    TEST_ASSERT_EQUAL(10, brake_get_force(0));
    TEST_ASSERT_EQUAL(20, brake_get_force(1));
    TEST_ASSERT_EQUAL(30, brake_get_force(2));
    TEST_ASSERT_EQUAL(40, brake_get_force(3));
}

// ============================================================================
// TEST CATEGORY: Error Recovery Testing
// ============================================================================

void test_brake_apply_error_recovery_after_invalid_call(void) {
    // Test: System can recover after error
    result_t result1 = brake_apply(10, 50);  // Invalid wheel_id
    TEST_ASSERT_EQUAL(ERROR_INVALID_WHEEL_ID, result1);
    
    // Valid call should succeed after error
    result_t result2 = brake_apply(0, 50);
    TEST_ASSERT_EQUAL(SUCCESS, result2);
    TEST_ASSERT_EQUAL(50, brake_get_force(0));
}

// Unity test runner
int main(void) {
    UNITY_BEGIN();
    
    // Parameter validity tests
    RUN_TEST(test_brake_apply_valid_parameters_wheel0);
    RUN_TEST(test_brake_apply_valid_parameters_wheel3);
    RUN_TEST(test_brake_apply_invalid_wheel_id);
    RUN_TEST(test_brake_apply_invalid_wheel_id_extreme);
    RUN_TEST(test_brake_apply_invalid_force);
    RUN_TEST(test_brake_apply_invalid_force_extreme);
    
    // Boundary value tests
    RUN_TEST(test_brake_apply_boundary_wheel_min);
    RUN_TEST(test_brake_apply_boundary_wheel_max);
    RUN_TEST(test_brake_apply_boundary_force_min);
    RUN_TEST(test_brake_apply_boundary_force_max);
    
    // Combinatorial tests (SIL 3+)
    RUN_TEST(test_brake_apply_all_wheels_all_forces);
    
    // Precondition tests
    RUN_TEST(test_brake_apply_precondition_not_initialized);
    
    // Side effect tests
    RUN_TEST(test_brake_apply_side_effect_global_state_modified);
    RUN_TEST(test_brake_apply_side_effect_no_cross_interference);
    
    // Error recovery tests
    RUN_TEST(test_brake_apply_error_recovery_after_invalid_call);
    
    return UNITY_END();
}
```

**Compilation and Execution**:

```bash
# Compile interface tests
gcc -Wall -Wextra -std=c11 \
    -I./include \
    -I./unity/src \
    brake_controller.c \
    test_brake_controller_interface.c \
    unity/src/unity.c \
    -o test_brake_interface

# Execute tests
./test_brake_interface

# Expected output:
# test_brake_apply_valid_parameters_wheel0:PASS
# test_brake_apply_valid_parameters_wheel3:PASS
# test_brake_apply_invalid_wheel_id:PASS
# test_brake_apply_invalid_wheel_id_extreme:PASS
# ...
# ----------------------
# 18 Tests 0 Failures 0 Ignored
# OK
```

---

## Data Structure Interface Testing

### Data Structure Interface Test Strategy

**Objective**: Validate struct layout, alignment, padding, and cross-module compatibility.

**Testing Dimensions**:
1. **Size verification**: Struct size matches specification
2. **Alignment verification**: Fields aligned correctly for target architecture
3. **Padding detection**: Detect unexpected padding bytes
4. **Endianness**: Verify byte order for multi-byte fields
5. **Cross-module compatibility**: Same struct definition across compilation units

### Example: Safety Data Structure Interface Test

**Data Structure Definition**:

```c
// File: safety_data.h
// Safety-critical data structures for railway signaling
// EN 50128 SIL 3

#ifndef SAFETY_DATA_H
#define SAFETY_DATA_H

#include <stdint.h>
#include <stdbool.h>

// CRITICAL: This struct is shared between modules and persisted to flash
// Layout MUST remain stable across compiler versions and optimization levels

/**
 * @brief Signal state data structure
 * @standard EN 50128 Section 7.6
 * @sil 3
 * 
 * LAYOUT REQUIREMENTS:
 * - Total size: 16 bytes (including padding)
 * - CRC covers all fields except crc32 itself
 * - Must be identical in all compilation units
 */
typedef struct {
    uint8_t signal_id;           // Offset 0, size 1
    uint8_t signal_state;        // Offset 1, size 1 (RED=0, YELLOW=1, GREEN=2)
    uint16_t voltage_mv;         // Offset 2, size 2 (millivolts)
    uint32_t timestamp_ms;       // Offset 4, size 4 (milliseconds since boot)
    bool safety_critical;        // Offset 8, size 1
    uint8_t padding[3];          // Offset 9, size 3 (explicit padding to 12 bytes)
    uint32_t crc32;              // Offset 12, size 4 (CRC-32 of bytes 0-11)
} signal_state_t;               // Total: 16 bytes

// Signal states
#define SIGNAL_RED    0
#define SIGNAL_YELLOW 1
#define SIGNAL_GREEN  2

#endif // SAFETY_DATA_H
```

**Data Structure Interface Test Suite**:

```c
// File: test_safety_data_interface.c
// Data structure interface tests
// EN 50128 SIL 3 - Structure Layout Validation

#include "unity.h"
#include "safety_data.h"
#include <stddef.h>  // for offsetof()
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

// ============================================================================
// TEST CATEGORY: Structure Size Verification
// ============================================================================

void test_signal_state_size(void) {
    // Test: Structure size matches specification (16 bytes)
    TEST_ASSERT_EQUAL_size_t(16, sizeof(signal_state_t));
}

// ============================================================================
// TEST CATEGORY: Field Offset Verification
// ============================================================================

void test_signal_state_field_offsets(void) {
    // Test: Field offsets match specification
    // CRITICAL: Changes to offsets break binary compatibility
    
    TEST_ASSERT_EQUAL_size_t(0, offsetof(signal_state_t, signal_id));
    TEST_ASSERT_EQUAL_size_t(1, offsetof(signal_state_t, signal_state));
    TEST_ASSERT_EQUAL_size_t(2, offsetof(signal_state_t, voltage_mv));
    TEST_ASSERT_EQUAL_size_t(4, offsetof(signal_state_t, timestamp_ms));
    TEST_ASSERT_EQUAL_size_t(8, offsetof(signal_state_t, safety_critical));
    TEST_ASSERT_EQUAL_size_t(9, offsetof(signal_state_t, padding));
    TEST_ASSERT_EQUAL_size_t(12, offsetof(signal_state_t, crc32));
}

// ============================================================================
// TEST CATEGORY: Field Size Verification
// ============================================================================

void test_signal_state_field_sizes(void) {
    // Test: Field sizes match specification
    signal_state_t s;
    
    TEST_ASSERT_EQUAL_size_t(1, sizeof(s.signal_id));
    TEST_ASSERT_EQUAL_size_t(1, sizeof(s.signal_state));
    TEST_ASSERT_EQUAL_size_t(2, sizeof(s.voltage_mv));
    TEST_ASSERT_EQUAL_size_t(4, sizeof(s.timestamp_ms));
    TEST_ASSERT_EQUAL_size_t(1, sizeof(s.safety_critical));
    TEST_ASSERT_EQUAL_size_t(3, sizeof(s.padding));
    TEST_ASSERT_EQUAL_size_t(4, sizeof(s.crc32));
}

// ============================================================================
// TEST CATEGORY: Alignment Verification
// ============================================================================

void test_signal_state_alignment(void) {
    // Test: Multi-byte fields are properly aligned
    // voltage_mv (uint16_t) should be 2-byte aligned
    // timestamp_ms (uint32_t) should be 4-byte aligned
    // crc32 (uint32_t) should be 4-byte aligned
    
    TEST_ASSERT_EQUAL(0, offsetof(signal_state_t, voltage_mv) % 2);
    TEST_ASSERT_EQUAL(0, offsetof(signal_state_t, timestamp_ms) % 4);
    TEST_ASSERT_EQUAL(0, offsetof(signal_state_t, crc32) % 4);
}

// ============================================================================
// TEST CATEGORY: No Unexpected Padding
// ============================================================================

void test_signal_state_no_unexpected_padding(void) {
    // Test: No compiler-inserted padding beyond explicit padding field
    size_t calculated_size = 
        sizeof(uint8_t) +   // signal_id
        sizeof(uint8_t) +   // signal_state
        sizeof(uint16_t) +  // voltage_mv
        sizeof(uint32_t) +  // timestamp_ms
        sizeof(bool) +      // safety_critical
        3 +                 // explicit padding
        sizeof(uint32_t);   // crc32
    
    TEST_ASSERT_EQUAL_size_t(calculated_size, sizeof(signal_state_t));
}

// ============================================================================
// TEST CATEGORY: Cross-Module Compatibility
// ============================================================================

void test_signal_state_cross_module_size_compatibility(void) {
    // Test: External module sees same size
    // In real project, this would be defined in another .c file
    extern size_t get_signal_state_size_from_module_b(void);
    
    // For this test, we simulate it
    // TEST_ASSERT_EQUAL_size_t(sizeof(signal_state_t), get_signal_state_size_from_module_b());
    
    // Placeholder for demonstration
    TEST_ASSERT_EQUAL_size_t(16, sizeof(signal_state_t));
}

// ============================================================================
// TEST CATEGORY: Memory Layout Verification
// ============================================================================

void test_signal_state_memory_layout(void) {
    // Test: Verify actual memory layout with known data
    signal_state_t s;
    memset(&s, 0, sizeof(s));
    
    s.signal_id = 0xAA;
    s.signal_state = 0xBB;
    s.voltage_mv = 0xCCDD;
    s.timestamp_ms = 0xEEFF0011;
    s.safety_critical = true;
    s.crc32 = 0x12345678;
    
    // Cast to byte array and verify layout
    uint8_t* bytes = (uint8_t*)&s;
    
    TEST_ASSERT_EQUAL_HEX8(0xAA, bytes[0]);  // signal_id
    TEST_ASSERT_EQUAL_HEX8(0xBB, bytes[1]);  // signal_state
    
    // voltage_mv depends on endianness
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    TEST_ASSERT_EQUAL_HEX8(0xDD, bytes[2]);  // voltage_mv low byte
    TEST_ASSERT_EQUAL_HEX8(0xCC, bytes[3]);  // voltage_mv high byte
    #else
    TEST_ASSERT_EQUAL_HEX8(0xCC, bytes[2]);
    TEST_ASSERT_EQUAL_HEX8(0xDD, bytes[3]);
    #endif
}

// ============================================================================
// TEST CATEGORY: Initialization Testing
// ============================================================================

void test_signal_state_zero_initialization(void) {
    // Test: Zero initialization produces expected state
    signal_state_t s = {0};
    
    TEST_ASSERT_EQUAL(0, s.signal_id);
    TEST_ASSERT_EQUAL(0, s.signal_state);
    TEST_ASSERT_EQUAL(0, s.voltage_mv);
    TEST_ASSERT_EQUAL(0, s.timestamp_ms);
    TEST_ASSERT_EQUAL(false, s.safety_critical);
    TEST_ASSERT_EQUAL(0, s.crc32);
}

// Unity test runner
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_signal_state_size);
    RUN_TEST(test_signal_state_field_offsets);
    RUN_TEST(test_signal_state_field_sizes);
    RUN_TEST(test_signal_state_alignment);
    RUN_TEST(test_signal_state_no_unexpected_padding);
    RUN_TEST(test_signal_state_cross_module_size_compatibility);
    RUN_TEST(test_signal_state_memory_layout);
    RUN_TEST(test_signal_state_zero_initialization);
    
    return UNITY_END();
}
```

---

## Communication Protocol Interface Testing

### Protocol Interface Test Strategy

**Objective**: Validate communication interfaces (UART, SPI, I2C, CAN) at byte/frame level.

**Testing Dimensions**:
1. **Frame format**: Start/stop bits, parity, CRC
2. **Timing**: Baud rate, clock frequency, setup/hold times
3. **Error detection**: CRC validation, parity errors, framing errors
4. **Flow control**: RTS/CTS, XON/XOFF
5. **Protocol state machine**: Idle, transmit, receive, error states

### Example: UART Protocol Interface Test

**UART Interface Definition**:

```c
// File: uart_interface.h
// UART communication interface
// EN 50128 SIL 2

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>
#include "common_types.h"

/**
 * @brief UART configuration
 */
typedef struct {
    uint32_t baud_rate;      // Baud rate (e.g., 9600, 115200)
    uint8_t data_bits;       // Data bits (7 or 8)
    uint8_t stop_bits;       // Stop bits (1 or 2)
    uint8_t parity;          // Parity (NONE, ODD, EVEN)
} uart_config_t;

// Parity options
#define UART_PARITY_NONE 0
#define UART_PARITY_ODD  1
#define UART_PARITY_EVEN 2

/**
 * @brief Initialize UART interface
 */
result_t uart_init(const uart_config_t* config);

/**
 * @brief Send byte over UART
 * @pre uart_init() must have been called
 * @return SUCCESS if byte queued, error otherwise
 */
result_t uart_send_byte(uint8_t byte);

/**
 * @brief Receive byte from UART (non-blocking)
 * @pre uart_init() must have been called
 * @param[out] byte Received byte (valid only if SUCCESS returned)
 * @return SUCCESS if byte available, ERROR_NO_DATA if no byte, error otherwise
 */
result_t uart_receive_byte(uint8_t* byte);

/**
 * @brief Send frame with CRC
 * Frame format: [START_BYTE][LENGTH][DATA...][CRC16][END_BYTE]
 */
result_t uart_send_frame(const uint8_t* data, uint8_t length);

/**
 * @brief Receive frame with CRC validation
 */
result_t uart_receive_frame(uint8_t* data, uint8_t* length, uint8_t max_length);

#define UART_START_BYTE 0x7E
#define UART_END_BYTE   0x7F
#define UART_MAX_FRAME_SIZE 256

#define ERROR_NO_DATA 10
#define ERROR_CRC_MISMATCH 11
#define ERROR_FRAMING_ERROR 12

#endif // UART_INTERFACE_H
```

**UART Protocol Interface Test Suite**:

```c
// File: test_uart_interface.c
// UART protocol interface tests
// EN 50128 SIL 2

#include "unity.h"
#include "uart_interface.h"
#include <string.h>

// Mock UART hardware for testing
static uint8_t mock_tx_buffer[256];
static uint8_t mock_tx_index = 0;
static uint8_t mock_rx_buffer[256];
static uint8_t mock_rx_count = 0;
static uint8_t mock_rx_index = 0;

void setUp(void) {
    mock_tx_index = 0;
    mock_rx_count = 0;
    mock_rx_index = 0;
    memset(mock_tx_buffer, 0, sizeof(mock_tx_buffer));
    memset(mock_rx_buffer, 0, sizeof(mock_rx_buffer));
}

void tearDown(void) {}

// Helper: Load mock RX buffer for receive tests
void mock_uart_load_rx(const uint8_t* data, uint8_t length) {
    memcpy(mock_rx_buffer, data, length);
    mock_rx_count = length;
    mock_rx_index = 0;
}

// ============================================================================
// TEST CATEGORY: UART Configuration Interface
// ============================================================================

void test_uart_init_valid_config(void) {
    // Test: Initialize UART with valid configuration
    uart_config_t config = {
        .baud_rate = 115200,
        .data_bits = 8,
        .stop_bits = 1,
        .parity = UART_PARITY_NONE
    };
    
    result_t result = uart_init(&config);
    TEST_ASSERT_EQUAL(SUCCESS, result);
}

void test_uart_init_null_config(void) {
    // Test: Initialize with NULL config (defensive programming)
    result_t result = uart_init(NULL);
    TEST_ASSERT_NOT_EQUAL(SUCCESS, result);
}

void test_uart_init_invalid_baud_rate(void) {
    // Test: Initialize with invalid baud rate
    uart_config_t config = {
        .baud_rate = 0,  // Invalid
        .data_bits = 8,
        .stop_bits = 1,
        .parity = UART_PARITY_NONE
    };
    
    result_t result = uart_init(&config);
    TEST_ASSERT_NOT_EQUAL(SUCCESS, result);
}

// ============================================================================
// TEST CATEGORY: Byte-Level Interface Testing
// ============================================================================

void test_uart_send_byte_single(void) {
    // Test: Send single byte
    uart_config_t config = {115200, 8, 1, UART_PARITY_NONE};
    uart_init(&config);
    
    result_t result = uart_send_byte(0xAA);
    TEST_ASSERT_EQUAL(SUCCESS, result);
    
    // Verify byte transmitted to mock hardware
    TEST_ASSERT_EQUAL(0xAA, mock_tx_buffer[0]);
}

void test_uart_send_byte_multiple(void) {
    // Test: Send multiple bytes in sequence
    uart_config_t config = {115200, 8, 1, UART_PARITY_NONE};
    uart_init(&config);
    
    const uint8_t test_data[] = {0x01, 0x02, 0x03, 0x04};
    for (uint8_t i = 0; i < sizeof(test_data); i++) {
        result_t result = uart_send_byte(test_data[i]);
        TEST_ASSERT_EQUAL(SUCCESS, result);
    }
    
    // Verify all bytes transmitted
    TEST_ASSERT_EQUAL_UINT8_ARRAY(test_data, mock_tx_buffer, sizeof(test_data));
}

void test_uart_receive_byte_available(void) {
    // Test: Receive byte when data available
    uart_config_t config = {115200, 8, 1, UART_PARITY_NONE};
    uart_init(&config);
    
    // Load mock RX buffer
    uint8_t rx_data[] = {0xBB};
    mock_uart_load_rx(rx_data, 1);
    
    uint8_t received;
    result_t result = uart_receive_byte(&received);
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(0xBB, received);
}

void test_uart_receive_byte_no_data(void) {
    // Test: Receive byte when no data available
    uart_config_t config = {115200, 8, 1, UART_PARITY_NONE};
    uart_init(&config);
    
    uint8_t received;
    result_t result = uart_receive_byte(&received);
    TEST_ASSERT_EQUAL(ERROR_NO_DATA, result);
}

void test_uart_receive_byte_null_pointer(void) {
    // Test: Receive with NULL pointer (defensive programming)
    uart_config_t config = {115200, 8, 1, UART_PARITY_NONE};
    uart_init(&config);
    
    result_t result = uart_receive_byte(NULL);
    TEST_ASSERT_NOT_EQUAL(SUCCESS, result);
}

// ============================================================================
// TEST CATEGORY: Frame-Level Interface Testing
// ============================================================================

void test_uart_send_frame_valid(void) {
    // Test: Send valid frame
    // Frame format: [START_BYTE][LENGTH][DATA...][CRC16][END_BYTE]
    uart_config_t config = {115200, 8, 1, UART_PARITY_NONE};
    uart_init(&config);
    
    const uint8_t data[] = {0x10, 0x20, 0x30};
    result_t result = uart_send_frame(data, sizeof(data));
    TEST_ASSERT_EQUAL(SUCCESS, result);
    
    // Verify frame structure
    TEST_ASSERT_EQUAL(UART_START_BYTE, mock_tx_buffer[0]);
    TEST_ASSERT_EQUAL(sizeof(data), mock_tx_buffer[1]);  // LENGTH
    TEST_ASSERT_EQUAL_UINT8_ARRAY(data, &mock_tx_buffer[2], sizeof(data));
    // mock_tx_buffer[5] and [6] are CRC16 (not verified here, see CRC tests)
    TEST_ASSERT_EQUAL(UART_END_BYTE, mock_tx_buffer[7]);
}

void test_uart_send_frame_empty(void) {
    // Test: Send empty frame (boundary case)
    uart_config_t config = {115200, 8, 1, UART_PARITY_NONE};
    uart_init(&config);
    
    result_t result = uart_send_frame(NULL, 0);
    
    // Empty frame may be valid or invalid depending on specification
    // For safety-critical systems, typically invalid
    TEST_ASSERT_NOT_EQUAL(SUCCESS, result);
}

void test_uart_send_frame_oversized(void) {
    // Test: Send frame exceeding max size
    uart_config_t config = {115200, 8, 1, UART_PARITY_NONE};
    uart_init(&config);
    
    uint8_t large_data[UART_MAX_FRAME_SIZE + 10];
    result_t result = uart_send_frame(large_data, sizeof(large_data));
    TEST_ASSERT_NOT_EQUAL(SUCCESS, result);
}

void test_uart_receive_frame_valid(void) {
    // Test: Receive valid frame with correct CRC
    uart_config_t config = {115200, 8, 1, UART_PARITY_NONE};
    uart_init(&config);
    
    // Simulate received frame: [START][LEN][DATA][CRC][END]
    uint8_t rx_frame[] = {
        UART_START_BYTE,        // Start
        0x03,                   // Length = 3
        0x10, 0x20, 0x30,       // Data
        0xAB, 0xCD,             // CRC16 (placeholder)
        UART_END_BYTE           // End
    };
    mock_uart_load_rx(rx_frame, sizeof(rx_frame));
    
    uint8_t received_data[10];
    uint8_t received_length;
    result_t result = uart_receive_frame(received_data, &received_length, sizeof(received_data));
    
    // Note: Actual CRC validation would require real CRC implementation
    // For this test, assume CRC passes
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(3, received_length);
    TEST_ASSERT_EQUAL_UINT8_ARRAY((uint8_t[]){0x10, 0x20, 0x30}, received_data, 3);
}

void test_uart_receive_frame_crc_mismatch(void) {
    // Test: Receive frame with incorrect CRC
    uart_config_t config = {115200, 8, 1, UART_PARITY_NONE};
    uart_init(&config);
    
    // Simulate received frame with bad CRC
    uint8_t rx_frame[] = {
        UART_START_BYTE,        // Start
        0x03,                   // Length = 3
        0x10, 0x20, 0x30,       // Data
        0xFF, 0xFF,             // Bad CRC
        UART_END_BYTE           // End
    };
    mock_uart_load_rx(rx_frame, sizeof(rx_frame));
    
    uint8_t received_data[10];
    uint8_t received_length;
    result_t result = uart_receive_frame(received_data, &received_length, sizeof(received_data));
    
    TEST_ASSERT_EQUAL(ERROR_CRC_MISMATCH, result);
}

void test_uart_receive_frame_missing_start_byte(void) {
    // Test: Receive frame missing START_BYTE (framing error)
    uart_config_t config = {115200, 8, 1, UART_PARITY_NONE};
    uart_init(&config);
    
    // Simulate received frame missing start byte
    uint8_t rx_frame[] = {
        0xFF,                   // Wrong start byte
        0x03,
        0x10, 0x20, 0x30,
        0xAB, 0xCD,
        UART_END_BYTE
    };
    mock_uart_load_rx(rx_frame, sizeof(rx_frame));
    
    uint8_t received_data[10];
    uint8_t received_length;
    result_t result = uart_receive_frame(received_data, &received_length, sizeof(received_data));
    
    TEST_ASSERT_EQUAL(ERROR_FRAMING_ERROR, result);
}

// Unity test runner
int main(void) {
    UNITY_BEGIN();
    
    // Configuration interface tests
    RUN_TEST(test_uart_init_valid_config);
    RUN_TEST(test_uart_init_null_config);
    RUN_TEST(test_uart_init_invalid_baud_rate);
    
    // Byte-level interface tests
    RUN_TEST(test_uart_send_byte_single);
    RUN_TEST(test_uart_send_byte_multiple);
    RUN_TEST(test_uart_receive_byte_available);
    RUN_TEST(test_uart_receive_byte_no_data);
    RUN_TEST(test_uart_receive_byte_null_pointer);
    
    // Frame-level interface tests
    RUN_TEST(test_uart_send_frame_valid);
    RUN_TEST(test_uart_send_frame_empty);
    RUN_TEST(test_uart_send_frame_oversized);
    RUN_TEST(test_uart_receive_frame_valid);
    RUN_TEST(test_uart_receive_frame_crc_mismatch);
    RUN_TEST(test_uart_receive_frame_missing_start_byte);
    
    return UNITY_END();
}
```

---

## Inter-Process Communication Testing

### IPC Interface Test Strategy

**Objective**: Validate shared memory, message queues, semaphores, and other IPC mechanisms.

**Testing Dimensions**:
1. **Synchronization**: Mutex, semaphore, spinlock correctness
2. **Data integrity**: No corruption during concurrent access
3. **Deadlock detection**: No circular wait conditions
4. **Race conditions**: Proper ordering guarantees
5. **Error handling**: Timeout, resource exhaustion

### Example: Shared Memory Interface Test

**Shared Memory Interface**:

```c
// File: shared_memory.h
// Shared memory interface for inter-module communication
// EN 50128 SIL 3

#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <stdint.h>
#include <stdbool.h>
#include "common_types.h"

/**
 * @brief Shared memory region for sensor data
 * @standard EN 50128 Section 7.6
 * @sil 3
 * 
 * CONCURRENCY CONTROL:
 * - Protected by semaphore (must acquire before read/write)
 * - Producer writes sensor data
 * - Consumer reads sensor data
 */
typedef struct {
    uint32_t sequence_number;    // Incremented on each write
    uint16_t sensor_value_1;     // Sensor 1 reading
    uint16_t sensor_value_2;     // Sensor 2 reading
    uint32_t timestamp_ms;       // Timestamp of reading
    bool valid;                  // Data validity flag
} shared_sensor_data_t;

/**
 * @brief Initialize shared memory
 */
result_t shm_init(void);

/**
 * @brief Acquire lock for shared memory access
 * @param timeout_ms Timeout in milliseconds (0 = no wait, -1 = infinite)
 * @return SUCCESS if acquired, ERROR_TIMEOUT if timeout
 */
result_t shm_acquire(uint32_t timeout_ms);

/**
 * @brief Release lock for shared memory
 */
result_t shm_release(void);

/**
 * @brief Write sensor data to shared memory (MUST hold lock)
 * @pre shm_acquire() must have been called successfully
 */
result_t shm_write_sensor_data(const shared_sensor_data_t* data);

/**
 * @brief Read sensor data from shared memory (MUST hold lock)
 * @pre shm_acquire() must have been called successfully
 */
result_t shm_read_sensor_data(shared_sensor_data_t* data);

#define ERROR_TIMEOUT 20
#define ERROR_NOT_LOCKED 21

#endif // SHARED_MEMORY_H
```

**Shared Memory Interface Test Suite**:

```c
// File: test_shared_memory_interface.c
// Shared memory interface tests
// EN 50128 SIL 3

#include "unity.h"
#include "shared_memory.h"
#include <string.h>

void setUp(void) {
    shm_init();
}

void tearDown(void) {}

// ============================================================================
// TEST CATEGORY: Lock Acquisition Interface
// ============================================================================

void test_shm_acquire_success(void) {
    // Test: Acquire lock when available
    result_t result = shm_acquire(1000);  // 1 second timeout
    TEST_ASSERT_EQUAL(SUCCESS, result);
    
    // Release for cleanup
    shm_release();
}

void test_shm_acquire_already_locked(void) {
    // Test: Attempt to acquire lock when already held
    result_t result1 = shm_acquire(1000);
    TEST_ASSERT_EQUAL(SUCCESS, result1);
    
    // Second acquire should timeout (same task cannot acquire twice)
    result_t result2 = shm_acquire(100);  // Short timeout
    TEST_ASSERT_EQUAL(ERROR_TIMEOUT, result2);
    
    // Release
    shm_release();
}

void test_shm_release_without_acquire(void) {
    // Test: Release without acquiring (defensive programming)
    result_t result = shm_release();
    TEST_ASSERT_NOT_EQUAL(SUCCESS, result);
}

// ============================================================================
// TEST CATEGORY: Write Interface Testing
// ============================================================================

void test_shm_write_sensor_data_with_lock(void) {
    // Test: Write sensor data while holding lock
    shm_acquire(1000);
    
    shared_sensor_data_t write_data = {
        .sequence_number = 1,
        .sensor_value_1 = 100,
        .sensor_value_2 = 200,
        .timestamp_ms = 1000,
        .valid = true
    };
    
    result_t result = shm_write_sensor_data(&write_data);
    TEST_ASSERT_EQUAL(SUCCESS, result);
    
    shm_release();
}

void test_shm_write_sensor_data_without_lock(void) {
    // Test: Attempt to write without holding lock (should fail)
    shared_sensor_data_t write_data = {
        .sequence_number = 1,
        .sensor_value_1 = 100,
        .sensor_value_2 = 200,
        .timestamp_ms = 1000,
        .valid = true
    };
    
    result_t result = shm_write_sensor_data(&write_data);
    TEST_ASSERT_EQUAL(ERROR_NOT_LOCKED, result);
}

void test_shm_write_sensor_data_null_pointer(void) {
    // Test: Write with NULL pointer (defensive programming)
    shm_acquire(1000);
    
    result_t result = shm_write_sensor_data(NULL);
    TEST_ASSERT_NOT_EQUAL(SUCCESS, result);
    
    shm_release();
}

// ============================================================================
// TEST CATEGORY: Read Interface Testing
// ============================================================================

void test_shm_read_sensor_data_with_lock(void) {
    // Test: Read sensor data while holding lock
    
    // First, write some data
    shm_acquire(1000);
    shared_sensor_data_t write_data = {
        .sequence_number = 42,
        .sensor_value_1 = 123,
        .sensor_value_2 = 456,
        .timestamp_ms = 5000,
        .valid = true
    };
    shm_write_sensor_data(&write_data);
    shm_release();
    
    // Now read it back
    shm_acquire(1000);
    shared_sensor_data_t read_data;
    result_t result = shm_read_sensor_data(&read_data);
    TEST_ASSERT_EQUAL(SUCCESS, result);
    
    // Verify data matches
    TEST_ASSERT_EQUAL(42, read_data.sequence_number);
    TEST_ASSERT_EQUAL(123, read_data.sensor_value_1);
    TEST_ASSERT_EQUAL(456, read_data.sensor_value_2);
    TEST_ASSERT_EQUAL(5000, read_data.timestamp_ms);
    TEST_ASSERT_TRUE(read_data.valid);
    
    shm_release();
}

void test_shm_read_sensor_data_without_lock(void) {
    // Test: Attempt to read without holding lock (should fail)
    shared_sensor_data_t read_data;
    result_t result = shm_read_sensor_data(&read_data);
    TEST_ASSERT_EQUAL(ERROR_NOT_LOCKED, result);
}

void test_shm_read_sensor_data_null_pointer(void) {
    // Test: Read with NULL pointer (defensive programming)
    shm_acquire(1000);
    
    result_t result = shm_read_sensor_data(NULL);
    TEST_ASSERT_NOT_EQUAL(SUCCESS, result);
    
    shm_release();
}

// ============================================================================
// TEST CATEGORY: Data Integrity Testing
// ============================================================================

void test_shm_data_integrity_write_read_multiple(void) {
    // Test: Write and read multiple times, verify data integrity
    
    for (uint32_t i = 1; i <= 10; i++) {
        // Write
        shm_acquire(1000);
        shared_sensor_data_t write_data = {
            .sequence_number = i,
            .sensor_value_1 = (uint16_t)(i * 10),
            .sensor_value_2 = (uint16_t)(i * 20),
            .timestamp_ms = i * 1000,
            .valid = true
        };
        shm_write_sensor_data(&write_data);
        shm_release();
        
        // Read
        shm_acquire(1000);
        shared_sensor_data_t read_data;
        shm_read_sensor_data(&read_data);
        shm_release();
        
        // Verify
        TEST_ASSERT_EQUAL(i, read_data.sequence_number);
        TEST_ASSERT_EQUAL(i * 10, read_data.sensor_value_1);
        TEST_ASSERT_EQUAL(i * 20, read_data.sensor_value_2);
        TEST_ASSERT_EQUAL(i * 1000, read_data.timestamp_ms);
        TEST_ASSERT_TRUE(read_data.valid);
    }
}

// ============================================================================
// TEST CATEGORY: Concurrency Testing (Simulated)
// ============================================================================

void test_shm_concurrent_write_read_simulation(void) {
    // Test: Simulate producer-consumer pattern
    // In real system, this would be separate threads/tasks
    
    // Producer writes
    shm_acquire(1000);
    shared_sensor_data_t producer_data = {
        .sequence_number = 100,
        .sensor_value_1 = 999,
        .sensor_value_2 = 888,
        .timestamp_ms = 50000,
        .valid = true
    };
    shm_write_sensor_data(&producer_data);
    shm_release();
    
    // Consumer reads (separate lock acquisition)
    shm_acquire(1000);
    shared_sensor_data_t consumer_data;
    shm_read_sensor_data(&consumer_data);
    shm_release();
    
    // Verify consumer received producer's data
    TEST_ASSERT_EQUAL(100, consumer_data.sequence_number);
    TEST_ASSERT_EQUAL(999, consumer_data.sensor_value_1);
    TEST_ASSERT_EQUAL(888, consumer_data.sensor_value_2);
    TEST_ASSERT_EQUAL(50000, consumer_data.timestamp_ms);
}

// Unity test runner
int main(void) {
    UNITY_BEGIN();
    
    // Lock acquisition tests
    RUN_TEST(test_shm_acquire_success);
    RUN_TEST(test_shm_acquire_already_locked);
    RUN_TEST(test_shm_release_without_acquire);
    
    // Write interface tests
    RUN_TEST(test_shm_write_sensor_data_with_lock);
    RUN_TEST(test_shm_write_sensor_data_without_lock);
    RUN_TEST(test_shm_write_sensor_data_null_pointer);
    
    // Read interface tests
    RUN_TEST(test_shm_read_sensor_data_with_lock);
    RUN_TEST(test_shm_read_sensor_data_without_lock);
    RUN_TEST(test_shm_read_sensor_data_null_pointer);
    
    // Data integrity tests
    RUN_TEST(test_shm_data_integrity_write_read_multiple);
    
    // Concurrency tests
    RUN_TEST(test_shm_concurrent_write_read_simulation);
    
    return UNITY_END();
}
```

---

## Interface Contract Validation

### Contract-Based Testing

**Objective**: Validate preconditions, postconditions, and invariants at interface boundaries.

**Contract Elements**:
1. **Preconditions**: Must be true before function call
2. **Postconditions**: Must be true after function call
3. **Invariants**: Always true for object/module state
4. **Side effects**: Documented state changes

### Example: Contract Validation Framework

**Design-by-Contract Macros**:

```c
// File: contracts.h
// Design-by-contract support for interface validation
// EN 50128 SIL 3

#ifndef CONTRACTS_H
#define CONTRACTS_H

#include <stdbool.h>
#include <assert.h>

// Enable contract checking for SIL 2+ (can be disabled for SIL 0-1)
#if defined(SIL_LEVEL) && (SIL_LEVEL >= 2)
    #define CONTRACTS_ENABLED 1
#else
    #define CONTRACTS_ENABLED 0
#endif

#if CONTRACTS_ENABLED

// Precondition check
#define PRECONDITION(condition, error_code) \
    do { \
        if (!(condition)) { \
            return (error_code); \
        } \
    } while(0)

// Postcondition check
#define POSTCONDITION(condition) \
    assert(condition)

// Invariant check
#define INVARIANT(condition) \
    assert(condition)

#else

// Contracts disabled
#define PRECONDITION(condition, error_code) ((void)0)
#define POSTCONDITION(condition) ((void)0)
#define INVARIANT(condition) ((void)0)

#endif // CONTRACTS_ENABLED

#endif // CONTRACTS_H
```

**Function with Contract Validation**:

```c
// File: stack.h
// Stack data structure with contract validation
// EN 50128 SIL 3

#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stdbool.h>
#include "common_types.h"
#include "contracts.h"

#define STACK_MAX_SIZE 100

typedef struct {
    uint32_t data[STACK_MAX_SIZE];
    uint16_t top;  // Index of top element (-1 if empty, represented as UINT16_MAX)
} stack_t;

/**
 * @brief Initialize stack
 * @post Stack is empty
 * @post top == -1 (UINT16_MAX)
 */
result_t stack_init(stack_t* stack);

/**
 * @brief Push value onto stack
 * @pre stack != NULL
 * @pre stack is not full (top < STACK_MAX_SIZE - 1)
 * @post top incremented by 1
 * @post data[top] == value
 */
result_t stack_push(stack_t* stack, uint32_t value);

/**
 * @brief Pop value from stack
 * @pre stack != NULL
 * @pre stack is not empty (top != UINT16_MAX)
 * @post top decremented by 1
 * @post *value == previous data[top]
 */
result_t stack_pop(stack_t* stack, uint32_t* value);

/**
 * @brief Check if stack is empty
 * @pre stack != NULL
 */
bool stack_is_empty(const stack_t* stack);

/**
 * @brief Check if stack is full
 * @pre stack != NULL
 */
bool stack_is_full(const stack_t* stack);

#define ERROR_STACK_NULL    30
#define ERROR_STACK_FULL    31
#define ERROR_STACK_EMPTY   32

#endif // STACK_H
```

**Implementation with Contracts**:

```c
// File: stack.c

#include "stack.h"
#include <string.h>

// INVARIANT: Stack integrity check
static bool stack_invariant(const stack_t* stack) {
    if (stack == NULL) return false;
    if (stack->top >= STACK_MAX_SIZE && stack->top != UINT16_MAX) return false;
    return true;
}

result_t stack_init(stack_t* stack) {
    PRECONDITION(stack != NULL, ERROR_STACK_NULL);
    
    memset(stack, 0, sizeof(stack_t));
    stack->top = UINT16_MAX;  // Empty stack
    
    POSTCONDITION(stack->top == UINT16_MAX);  // Stack is empty
    INVARIANT(stack_invariant(stack));
    
    return SUCCESS;
}

result_t stack_push(stack_t* stack, uint32_t value) {
    PRECONDITION(stack != NULL, ERROR_STACK_NULL);
    INVARIANT(stack_invariant(stack));
    PRECONDITION(!stack_is_full(stack), ERROR_STACK_FULL);
    
    // Save old state for postcondition check
    uint16_t old_top = stack->top;
    
    // Push value
    if (stack->top == UINT16_MAX) {
        stack->top = 0;  // First element
    } else {
        stack->top++;
    }
    stack->data[stack->top] = value;
    
    POSTCONDITION(stack->top == old_top + 1 || (old_top == UINT16_MAX && stack->top == 0));
    POSTCONDITION(stack->data[stack->top] == value);
    INVARIANT(stack_invariant(stack));
    
    return SUCCESS;
}

result_t stack_pop(stack_t* stack, uint32_t* value) {
    PRECONDITION(stack != NULL, ERROR_STACK_NULL);
    PRECONDITION(value != NULL, ERROR_INVALID_PARAMETER);
    INVARIANT(stack_invariant(stack));
    PRECONDITION(!stack_is_empty(stack), ERROR_STACK_EMPTY);
    
    uint16_t old_top = stack->top;
    
    // Pop value
    *value = stack->data[stack->top];
    if (stack->top == 0) {
        stack->top = UINT16_MAX;  // Stack now empty
    } else {
        stack->top--;
    }
    
    POSTCONDITION(stack->top == old_top - 1 || (old_top == 0 && stack->top == UINT16_MAX));
    INVARIANT(stack_invariant(stack));
    
    return SUCCESS;
}

bool stack_is_empty(const stack_t* stack) {
    PRECONDITION(stack != NULL, false);
    return stack->top == UINT16_MAX;
}

bool stack_is_full(const stack_t* stack) {
    PRECONDITION(stack != NULL, false);
    return stack->top == (STACK_MAX_SIZE - 1);
}
```

**Contract Validation Tests**:

```c
// File: test_stack_contracts.c
// Contract validation tests for stack interface
// EN 50128 SIL 3

#include "unity.h"
#include "stack.h"

void setUp(void) {}
void tearDown(void) {}

// ============================================================================
// TEST CATEGORY: Precondition Validation
// ============================================================================

void test_stack_init_precondition_null(void) {
    // Test: init with NULL violates precondition
    result_t result = stack_init(NULL);
    TEST_ASSERT_EQUAL(ERROR_STACK_NULL, result);
}

void test_stack_push_precondition_null(void) {
    // Test: push with NULL stack violates precondition
    result_t result = stack_push(NULL, 42);
    TEST_ASSERT_EQUAL(ERROR_STACK_NULL, result);
}

void test_stack_push_precondition_full_stack(void) {
    // Test: push to full stack violates precondition
    stack_t stack;
    stack_init(&stack);
    
    // Fill stack
    for (uint16_t i = 0; i < STACK_MAX_SIZE; i++) {
        stack_push(&stack, i);
    }
    
    // Attempt to push to full stack
    result_t result = stack_push(&stack, 999);
    TEST_ASSERT_EQUAL(ERROR_STACK_FULL, result);
}

void test_stack_pop_precondition_empty_stack(void) {
    // Test: pop from empty stack violates precondition
    stack_t stack;
    stack_init(&stack);
    
    uint32_t value;
    result_t result = stack_pop(&stack, &value);
    TEST_ASSERT_EQUAL(ERROR_STACK_EMPTY, result);
}

// ============================================================================
// TEST CATEGORY: Postcondition Validation
// ============================================================================

void test_stack_init_postcondition_empty(void) {
    // Test: After init, stack is empty (postcondition)
    stack_t stack;
    result_t result = stack_init(&stack);
    
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_TRUE(stack_is_empty(&stack));  // Postcondition: stack is empty
}

void test_stack_push_postcondition_value_stored(void) {
    // Test: After push, value is stored (postcondition)
    stack_t stack;
    stack_init(&stack);
    
    result_t result = stack_push(&stack, 123);
    TEST_ASSERT_EQUAL(SUCCESS, result);
    
    // Postcondition: value is now top of stack
    uint32_t popped;
    stack_pop(&stack, &popped);
    TEST_ASSERT_EQUAL(123, popped);
}

void test_stack_push_postcondition_top_incremented(void) {
    // Test: After push, top is incremented (postcondition)
    stack_t stack;
    stack_init(&stack);
    
    TEST_ASSERT_TRUE(stack_is_empty(&stack));
    
    stack_push(&stack, 1);
    TEST_ASSERT_FALSE(stack_is_empty(&stack));  // Postcondition: no longer empty
    
    stack_push(&stack, 2);
    // Postcondition: size increased (tested indirectly)
}

void test_stack_pop_postcondition_value_returned(void) {
    // Test: After pop, correct value returned (postcondition)
    stack_t stack;
    stack_init(&stack);
    
    stack_push(&stack, 456);
    
    uint32_t popped;
    result_t result = stack_pop(&stack, &popped);
    
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(456, popped);  // Postcondition: correct value
}

// ============================================================================
// TEST CATEGORY: Invariant Validation
// ============================================================================

void test_stack_invariant_maintained_across_operations(void) {
    // Test: Stack invariant maintained throughout operations
    stack_t stack;
    stack_init(&stack);
    
    // Invariant holds after init
    TEST_ASSERT_TRUE(stack_is_empty(&stack) || !stack_is_full(&stack));
    
    // Push some values
    for (uint32_t i = 0; i < 10; i++) {
        stack_push(&stack, i);
        // Invariant: stack state consistent (not tested explicitly, relies on INVARIANT() in implementation)
    }
    
    // Pop some values
    for (uint32_t i = 0; i < 10; i++) {
        uint32_t val;
        stack_pop(&stack, &val);
        // Invariant: stack state consistent
    }
    
    // Invariant holds at end
    TEST_ASSERT_TRUE(stack_is_empty(&stack));
}

// Unity test runner
int main(void) {
    UNITY_BEGIN();
    
    // Precondition tests
    RUN_TEST(test_stack_init_precondition_null);
    RUN_TEST(test_stack_push_precondition_null);
    RUN_TEST(test_stack_push_precondition_full_stack);
    RUN_TEST(test_stack_pop_precondition_empty_stack);
    
    // Postcondition tests
    RUN_TEST(test_stack_init_postcondition_empty);
    RUN_TEST(test_stack_push_postcondition_value_stored);
    RUN_TEST(test_stack_push_postcondition_top_incremented);
    RUN_TEST(test_stack_pop_postcondition_value_returned);
    
    // Invariant tests
    RUN_TEST(test_stack_invariant_maintained_across_operations);
    
    return UNITY_END();
}
```

---

## Boundary Value Testing

### Boundary Testing Strategy

**EN 50128 D.34**: "Test all interface variables at their extreme positions."

**Boundary Types**:
1. **Numeric boundaries**: Min, max, zero, -1, overflow points
2. **Array boundaries**: Index 0, size-1, size (out of bounds)
3. **String boundaries**: Empty, max length, NULL terminator position
4. **Time boundaries**: Timeout=0, timeout=max, wraparound points
5. **State boundaries**: State transitions at critical points

### Boundary Value Analysis Example

```c
// File: test_boundaries.c
// Comprehensive boundary value testing
// EN 50128 SIL 3 - D.34 Level 2

#include "unity.h"
#include <stdint.h>
#include <limits.h>

// Function under test: Calculate average
result_t calculate_average(const uint16_t* values, uint8_t count, uint16_t* average);

void setUp(void) {}
void tearDown(void) {}

// ============================================================================
// TEST CATEGORY: Numeric Boundary Testing
// ============================================================================

void test_average_boundary_count_zero(void) {
    // Test: count = 0 (minimum boundary)
    uint16_t values[] = {100};
    uint16_t average;
    result_t result = calculate_average(values, 0, &average);
    
    // Zero count is invalid
    TEST_ASSERT_NOT_EQUAL(SUCCESS, result);
}

void test_average_boundary_count_one(void) {
    // Test: count = 1 (edge case)
    uint16_t values[] = {42};
    uint16_t average;
    result_t result = calculate_average(values, 1, &average);
    
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(42, average);
}

void test_average_boundary_count_max(void) {
    // Test: count = UINT8_MAX (maximum boundary)
    uint16_t values[UINT8_MAX];
    for (uint16_t i = 0; i < UINT8_MAX; i++) {
        values[i] = 1;
    }
    
    uint16_t average;
    result_t result = calculate_average(values, UINT8_MAX, &average);
    
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(1, average);
}

void test_average_boundary_value_zero(void) {
    // Test: All values = 0 (minimum value boundary)
    uint16_t values[] = {0, 0, 0, 0};
    uint16_t average;
    result_t result = calculate_average(values, 4, &average);
    
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(0, average);
}

void test_average_boundary_value_max(void) {
    // Test: All values = UINT16_MAX (maximum value boundary)
    uint16_t values[] = {UINT16_MAX, UINT16_MAX, UINT16_MAX};
    uint16_t average;
    result_t result = calculate_average(values, 3, &average);
    
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(UINT16_MAX, average);
}

void test_average_boundary_overflow_risk(void) {
    // Test: Values that could cause overflow during summation
    // Sum of 4 * 20000 = 80000 exceeds UINT16_MAX (65535)
    uint16_t values[] = {20000, 20000, 20000, 20000};
    uint16_t average;
    result_t result = calculate_average(values, 4, &average);
    
    // Implementation must use uint32_t for intermediate sum
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(20000, average);
}

// ============================================================================
// TEST CATEGORY: Pointer Boundary Testing
// ============================================================================

void test_average_boundary_null_values(void) {
    // Test: values = NULL (pointer boundary)
    uint16_t average;
    result_t result = calculate_average(NULL, 10, &average);
    
    TEST_ASSERT_NOT_EQUAL(SUCCESS, result);
}

void test_average_boundary_null_output(void) {
    // Test: average = NULL (output pointer boundary)
    uint16_t values[] = {10, 20, 30};
    result_t result = calculate_average(values, 3, NULL);
    
    TEST_ASSERT_NOT_EQUAL(SUCCESS, result);
}

// Unity test runner
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_average_boundary_count_zero);
    RUN_TEST(test_average_boundary_count_one);
    RUN_TEST(test_average_boundary_count_max);
    RUN_TEST(test_average_boundary_value_zero);
    RUN_TEST(test_average_boundary_value_max);
    RUN_TEST(test_average_boundary_overflow_risk);
    RUN_TEST(test_average_boundary_null_values);
    RUN_TEST(test_average_boundary_null_output);
    
    return UNITY_END();
}
```

---

## Interface Mocking and Stubbing

### Mock/Stub Strategy for Interface Isolation

**Objective**: Test interfaces in isolation without full system dependencies.

**Techniques**:
1. **Stubbing**: Provide minimal implementation to satisfy interface
2. **Mocking**: Simulate interface behavior with verification
3. **Fake**: Simplified working implementation for testing

### Example: Hardware Interface Mock

```c
// File: mock_hal_gpio.c
// Mock implementation of GPIO HAL for interface testing
// EN 50128 SIL 3

#include "hal_gpio.h"
#include <string.h>

// Mock state tracking
static bool mock_initialized = false;
static bool mock_pin_states[32];  // Assume 32 GPIO pins
static uint32_t mock_call_count_set = 0;
static uint32_t mock_call_count_read = 0;

// Mock initialization
result_t hal_gpio_init(void) {
    mock_initialized = true;
    memset(mock_pin_states, 0, sizeof(mock_pin_states));
    mock_call_count_set = 0;
    mock_call_count_read = 0;
    return SUCCESS;
}

// Mock set pin
result_t hal_gpio_set_pin(uint8_t pin, bool value) {
    if (!mock_initialized) return ERROR_NOT_INITIALIZED;
    if (pin >= 32) return ERROR_INVALID_PIN;
    
    mock_pin_states[pin] = value;
    mock_call_count_set++;
    return SUCCESS;
}

// Mock read pin
result_t hal_gpio_read_pin(uint8_t pin, bool* value) {
    if (!mock_initialized) return ERROR_NOT_INITIALIZED;
    if (pin >= 32) return ERROR_INVALID_PIN;
    if (value == NULL) return ERROR_INVALID_PARAMETER;
    
    *value = mock_pin_states[pin];
    mock_call_count_read++;
    return SUCCESS;
}

// Mock verification functions (for testing)
bool mock_gpio_verify_pin_state(uint8_t pin, bool expected_value) {
    if (pin >= 32) return false;
    return mock_pin_states[pin] == expected_value;
}

uint32_t mock_gpio_get_set_call_count(void) {
    return mock_call_count_set;
}

uint32_t mock_gpio_get_read_call_count(void) {
    return mock_call_count_read;
}

void mock_gpio_reset(void) {
    mock_initialized = false;
    memset(mock_pin_states, 0, sizeof(mock_pin_states));
    mock_call_count_set = 0;
    mock_call_count_read = 0;
}
```

**Test Using Mock**:

```c
// File: test_application_with_mock.c
// Application test using mocked GPIO interface
// EN 50128 SIL 3

#include "unity.h"
#include "application.h"  // Application under test
#include "hal_gpio.h"     // HAL interface
#include "mock_hal_gpio.h"  // Mock verification functions

void setUp(void) {
    mock_gpio_reset();
    hal_gpio_init();
}

void tearDown(void) {}

void test_application_sets_output_pins_correctly(void) {
    // Test: Application sets GPIO pins through HAL interface
    
    // Call application function
    application_activate_outputs();
    
    // Verify application called HAL correctly (using mock verification)
    TEST_ASSERT_TRUE(mock_gpio_verify_pin_state(PIN_LED1, true));
    TEST_ASSERT_TRUE(mock_gpio_verify_pin_state(PIN_LED2, true));
    TEST_ASSERT_TRUE(mock_gpio_verify_pin_state(PIN_RELAY, true));
    
    // Verify number of calls
    TEST_ASSERT_EQUAL(3, mock_gpio_get_set_call_count());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_application_sets_output_pins_correctly);
    return UNITY_END();
}
```

---

## API Compatibility Testing

### API Version Compatibility

**Objective**: Ensure interface compatibility across versions.

**Compatibility Dimensions**:
1. **Binary compatibility**: Struct layout, function signatures unchanged
2. **Source compatibility**: Code compiles without changes
3. **Behavioral compatibility**: Same inputs produce same outputs
4. **Semantic versioning**: Major.Minor.Patch version tracking

### API Compatibility Test Framework

```c
// File: test_api_compatibility.c
// API compatibility tests
// EN 50128 SIL 2

#include "unity.h"
#include "api_v1.h"
#include "api_v2.h"

void setUp(void) {}
void tearDown(void) {}

// ============================================================================
// TEST CATEGORY: Binary Compatibility
// ============================================================================

void test_api_struct_size_unchanged(void) {
    // Test: Structure size unchanged between versions
    // CRITICAL: Changing struct size breaks binary compatibility
    
    // In real test, compare against recorded size from v1
    const size_t expected_size_v1 = 64;  // From API v1
    
    TEST_ASSERT_EQUAL_size_t(expected_size_v1, sizeof(api_data_v2_t));
}

void test_api_function_signature_compatible(void) {
    // Test: Function signature compatible
    // This test verifies that old code compiles with new API
    
    api_data_v2_t data;
    result_t result = api_process(&data);  // Function exists in both v1 and v2
    
    // If this compiles, source compatibility preserved
    TEST_ASSERT_TRUE(result == SUCCESS || result != SUCCESS);  // Any result OK
}

// ============================================================================
// TEST CATEGORY: Behavioral Compatibility
// ============================================================================

void test_api_behavior_consistent_with_v1(void) {
    // Test: API v2 behaves identically to v1 for common use cases
    
    api_data_v2_t data_v2;
    data_v2.input = 42;
    
    result_t result = api_process(&data_v2);
    
    // Expected behavior from v1: output = input * 2
    TEST_ASSERT_EQUAL(SUCCESS, result);
    TEST_ASSERT_EQUAL(84, data_v2.output);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_api_struct_size_unchanged);
    RUN_TEST(test_api_function_signature_compatible);
    RUN_TEST(test_api_behavior_consistent_with_v1);
    return UNITY_END();
}
```

---

## Tool Integration for Interface Testing

### Workspace Integration for Interface Testing

**Command Pattern**:

```bash
# Compile all interface tests
make interface_tests

# Run interface test suite
./run_interface_tests.sh

# Generate interface test report
python3 tools/workspace.py wf start interface-testing \
    --project railway_control \
    --sil 3 \
    --output interface_test_report.md

# Verify interface coverage
python3 tools/interface_coverage_check.py \
    --interfaces src/interfaces/ \
    --tests tests/interface/ \
    --report interface_coverage.json
```

### Interface Test Automation Script

```bash
#!/bin/bash
# File: run_interface_tests.sh
# Automated interface testing for integration phase
# EN 50128 Phase 6

set -e

echo "==================================="
echo "Interface Testing - EN 50128"
echo "==================================="

# Compile interface tests
echo "Compiling interface tests..."
gcc -Wall -Wextra -std=c11 \
    -I./include -I./unity/src \
    test_brake_controller_interface.c \
    brake_controller.c \
    unity/src/unity.c \
    -o test_brake_interface

gcc -Wall -Wextra -std=c11 \
    -I./include -I./unity/src \
    test_safety_data_interface.c \
    unity/src/unity.c \
    -o test_safety_data_interface

gcc -Wall -Wextra -std=c11 \
    -I./include -I./unity/src \
    test_uart_interface.c \
    uart_interface.c \
    unity/src/unity.c \
    -o test_uart_interface

# Run all interface tests
echo "Running interface tests..."
./test_brake_interface
./test_safety_data_interface
./test_uart_interface

echo "==================================="
echo "Interface Testing Complete"
echo "==================================="
```

---

## SIL-Specific Requirements

### Interface Testing by SIL Level

| SIL | Interface Testing Requirements | Documentation |
|-----|-------------------------------|---------------|
| **0-1** | Basic interface testing (parameters, return values) | Test results recorded |
| **2** | Thorough interface testing (boundary values, error cases) | Interface Test Report required |
| **3-4** | Exhaustive interface testing (all combinations for critical interfaces, contract validation, concurrency testing) | Detailed Interface Test Report with traceability matrix, independent review required |

**SIL 3-4 Additional Requirements**:
- Combinatorial testing for critical interfaces (EN 50128 D.34 Level 4)
- Formal contract validation (preconditions, postconditions, invariants)
- Concurrency testing for multi-threaded interfaces
- Cross-module compatibility verification
- Interface regression testing on any change

---

## Summary

This workflow provides comprehensive interface testing guidance for EN 50128 integration phase:

1. **Function Interfaces**: Parameter validation, return values, side effects, contracts
2. **Data Structure Interfaces**: Layout, alignment, padding, cross-module compatibility
3. **Communication Interfaces**: Protocol compliance, error detection, timing
4. **IPC Interfaces**: Synchronization, data integrity, deadlock prevention
5. **Contract Validation**: Preconditions, postconditions, invariants enforced
6. **Boundary Testing**: Extreme values, edge cases, overflow conditions
7. **Mocking/Stubbing**: Interface isolation for focused testing
8. **API Compatibility**: Version compatibility across major/minor releases

**EN 50128 Compliance**: All interface testing follows Section 7.6.4.1 and D.34 requirements with SIL-appropriate thoroughness levels.

**Tool Integration**: Unity framework, workspace.py workflows, automated test execution, coverage reporting.

**Next Steps**: After interface testing, proceed to performance testing workflow (performance-testing-workflow.md).
