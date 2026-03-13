# Defensive Programming Patterns for EN 50128 Railway Safety Software

**Purpose**: Provide C programming patterns for defensive programming in railway safety-critical systems per EN 50128 requirements.

**EN 50128 Reference**: 
- Table A.3, Technique 2 "Defensive Programming" (Highly Recommended for SIL 3-4)
- Annex D.14 "Defensive Programming"

**Applicability**: 
- **SIL 3-4**: Highly Recommended
- **SIL 1-2**: Recommended
- **SIL 0**: Optional

**MISRA C:2012 Compliance**: All patterns comply with MISRA C:2012 mandatory rules

---

## Table of Contents

1. [Introduction to Defensive Programming](#introduction-to-defensive-programming)
2. [Input Validation Patterns](#input-validation-patterns)
3. [Error Detection Patterns](#error-detection-patterns)
4. [Error Handling Patterns](#error-handling-patterns)
5. [Fail-Safe Patterns](#fail-safe-patterns)
6. [Data Integrity Patterns](#data-integrity-patterns)
7. [Control Flow Validation Patterns](#control-flow-validation-patterns)
8. [Resource Management Patterns](#resource-management-patterns)
9. [Assertion Patterns](#assertion-patterns)
10. [Complete Example: Safety-Critical Function](#complete-example-safety-critical-function)

---

## Introduction to Defensive Programming

### EN 50128 Definition (Annex D.14)

**Aim**: To produce programs which detect anomalous control flow, data flow or data values during their execution and react to these in a predetermined and acceptable manner.

**Description**: Defensive programming techniques systematically check for control or data anomalies throughout the program to decrease the likelihood of erroneous data processing.

**Two Categories**:
1. **Intrinsic Error-Safe Software**: Designed to accommodate its own design shortcomings (errors in design, coding, or requirements)
2. **Error-Tolerant Software**: Designed to expect failures in its environment or use outside nominal conditions

### Defensive Programming Principles

1. **Never Trust Inputs**: Validate all inputs from external sources (sensors, communication, user input)
2. **Check Preconditions**: Verify function preconditions before execution
3. **Check Postconditions**: Verify function postconditions after execution
4. **Detect Anomalies**: Detect unexpected control flow, data flow, or data values
5. **Fail-Safe**: React to anomalies in a predetermined, safe manner
6. **Redundancy**: Use redundancy to detect errors (cross-validation, voting)
7. **Simplicity**: Keep defensive checks simple and understandable

### When to Apply Defensive Programming

- **All safety-critical functions** (SIL 1+)
- **All public interfaces** (functions called from other modules)
- **All hardware interfaces** (memory-mapped I/O, sensors, actuators)
- **All external interfaces** (communication, file I/O)
- **All data processing** (calculations, conversions, filtering)

---

## Input Validation Patterns

### Pattern 1: NULL Pointer Check

**Purpose**: Prevent undefined behavior from NULL pointer dereference

**MISRA C Reference**: MISRA C:2012 Rule 1.3 (undefined behavior), Rule 17.7 (return value check)

**Pattern**:
```c
error_t ProcessData(const sensor_data_t* input, output_data_t* output) {
    // NULL pointer checks (defensive programming)
    if (input == NULL) {
        log_error("ProcessData: input is NULL");
        return ERROR_NULL_POINTER;
    }
    
    if (output == NULL) {
        log_error("ProcessData: output is NULL");
        return ERROR_NULL_POINTER;
    }
    
    // Proceed with processing (inputs validated)
    output->value = input->value * 2;
    return SUCCESS;
}
```

**Key Points**:
- Check **ALL** pointer parameters at function entry
- Return error immediately if NULL detected (fail-fast)
- Log error for diagnostics (if logging available)
- Use early return to reduce nesting

**When to Use**: 
- **MANDATORY** for all pointer parameters (SIL 2+)
- **MANDATORY** for safety-critical functions (all SILs)

---

### Pattern 2: Range Check (Numeric Parameters)

**Purpose**: Ensure numeric values are within valid range

**MISRA C Reference**: MISRA C:2012 Rule 14.3 (Boolean condition checks)

**Pattern**:
```c
error_t SetSpeed(uint16_t speed_kmh) {
    // Range check (defensive programming)
    if (speed_kmh > MAX_SPEED_KMH) {
        log_error("SetSpeed: speed exceeds maximum (%u > %u)", 
                  speed_kmh, MAX_SPEED_KMH);
        return ERROR_OUT_OF_RANGE;
    }
    
    // Proceed with valid speed
    current_speed = speed_kmh;
    return SUCCESS;
}
```

**Advanced Range Check** (both min and max):
```c
error_t SetTemperature(int16_t temperature_celsius) {
    // Range check with both limits
    if ((temperature_celsius < MIN_TEMPERATURE_C) || 
        (temperature_celsius > MAX_TEMPERATURE_C)) {
        log_error("SetTemperature: temperature out of range (%d not in [%d, %d])",
                  temperature_celsius, MIN_TEMPERATURE_C, MAX_TEMPERATURE_C);
        return ERROR_OUT_OF_RANGE;
    }
    
    // Proceed with valid temperature
    current_temperature = temperature_celsius;
    return SUCCESS;
}
```

**Key Points**:
- Define MIN and MAX constants for all ranges
- Check both minimum and maximum bounds (if applicable)
- Use meaningful error messages with actual values
- Reject invalid values immediately (fail-fast)

**When to Use**:
- **MANDATORY** for all numeric parameters with physical significance (speed, temperature, pressure, etc.)
- **MANDATORY** for safety-critical functions
- **RECOMMENDED** for all numeric parameters

---

### Pattern 3: Enum/State Check

**Purpose**: Ensure enum or state values are valid

**MISRA C Reference**: MISRA C:2012 Rule 16.4 (switch statement default), Rule 16.6 (switch with at least 2 cases)

**Pattern**:
```c
typedef enum {
    STATE_IDLE = 0,
    STATE_ACTIVE = 1,
    STATE_ERROR = 2,
    STATE_SHUTDOWN = 3
} system_state_t;

error_t ProcessState(system_state_t state) {
    // Enum validation (defensive programming)
    switch (state) {
        case STATE_IDLE:
            // Handle IDLE state
            break;
        case STATE_ACTIVE:
            // Handle ACTIVE state
            break;
        case STATE_ERROR:
            // Handle ERROR state
            break;
        case STATE_SHUTDOWN:
            // Handle SHUTDOWN state
            break;
        default:
            // Invalid state detected (defensive programming)
            log_error("ProcessState: invalid state %d", (int)state);
            return ERROR_INVALID_STATE;
    }
    
    return SUCCESS;
}
```

**Explicit Range Check** (alternative for enums):
```c
error_t SetSystemState(system_state_t new_state) {
    // Explicit enum range check
    if ((new_state < STATE_IDLE) || (new_state > STATE_SHUTDOWN)) {
        log_error("SetSystemState: invalid state %d", (int)new_state);
        return ERROR_INVALID_STATE;
    }
    
    // State transition validation
    if (!IsValidTransition(current_state, new_state)) {
        log_error("SetSystemState: invalid transition %d -> %d",
                  (int)current_state, (int)new_state);
        return ERROR_INVALID_TRANSITION;
    }
    
    // Proceed with valid state transition
    current_state = new_state;
    return SUCCESS;
}
```

**Key Points**:
- Always include `default` case in switch statements (MISRA C mandatory)
- Use explicit range checks for enum values received from external sources
- Validate state transitions (not just state values)
- Log invalid states for diagnostics

**When to Use**:
- **MANDATORY** for all enum parameters from external sources (communication, hardware, user input)
- **MANDATORY** for state machines in safety-critical functions

---

### Pattern 4: Array Bounds Check

**Purpose**: Prevent buffer overflows and underflows

**MISRA C Reference**: MISRA C:2012 Rule 18.1 (pointer arithmetic)

**Pattern**:
```c
#define BUFFER_SIZE 256U

static uint8_t buffer[BUFFER_SIZE];

error_t WriteBuffer(uint16_t index, uint8_t value) {
    // Array bounds check (defensive programming)
    if (index >= BUFFER_SIZE) {
        log_error("WriteBuffer: index out of bounds (%u >= %u)",
                  index, BUFFER_SIZE);
        return ERROR_INDEX_OUT_OF_BOUNDS;
    }
    
    // Proceed with write (index validated)
    buffer[index] = value;
    return SUCCESS;
}

error_t ReadBuffer(uint16_t index, uint8_t* value) {
    // NULL pointer check
    if (value == NULL) {
        log_error("ReadBuffer: value pointer is NULL");
        return ERROR_NULL_POINTER;
    }
    
    // Array bounds check
    if (index >= BUFFER_SIZE) {
        log_error("ReadBuffer: index out of bounds (%u >= %u)",
                  index, BUFFER_SIZE);
        return ERROR_INDEX_OUT_OF_BOUNDS;
    }
    
    // Proceed with read (index validated)
    *value = buffer[index];
    return SUCCESS;
}
```

**Key Points**:
- Use `>=` for bounds check (not `>`) since arrays are 0-indexed
- Use unsigned types for indices (prevents negative indices)
- Define buffer size as constant (use #define or const)
- Check bounds before accessing array

**When to Use**:
- **MANDATORY** for all array access with non-constant indices
- **MANDATORY** for safety-critical data structures

---

### Pattern 5: String Length Check

**Purpose**: Prevent buffer overflows in string operations

**MISRA C Reference**: MISRA C:2012 Rule 21.17 (string handling)

**Pattern**:
```c
#define MAX_NAME_LENGTH 32U

error_t SetName(const char* name, char* destination, size_t dest_size) {
    size_t name_len;
    
    // NULL pointer checks
    if (name == NULL) {
        log_error("SetName: name is NULL");
        return ERROR_NULL_POINTER;
    }
    if (destination == NULL) {
        log_error("SetName: destination is NULL");
        return ERROR_NULL_POINTER;
    }
    
    // String length check (defensive programming)
    name_len = strnlen(name, dest_size);  // Use strnlen, not strlen
    if (name_len >= dest_size) {
        log_error("SetName: name too long (%zu >= %zu)", name_len, dest_size);
        return ERROR_STRING_TOO_LONG;
    }
    
    // Safe string copy (with bounds check)
    (void)strncpy(destination, name, dest_size - 1U);
    destination[dest_size - 1U] = '\0';  // Ensure null termination
    
    return SUCCESS;
}
```

**Key Points**:
- Use `strnlen` instead of `strlen` (bounded length check)
- Use `strncpy` instead of `strcpy` (bounded copy)
- Always null-terminate destination string explicitly
- Check destination size is sufficient

**When to Use**:
- **MANDATORY** for all string operations (SIL 2+)
- **RECOMMENDED** to avoid string handling entirely in safety-critical code (use fixed-length byte arrays)

---

### Pattern 6: Plausibility Check

**Purpose**: Detect physically implausible values (sensor faults, corrupted data)

**EN 50128 Reference**: Annex D.14 (Defensive Programming - plausibility checks)

**Pattern**:
```c
#define MAX_PLAUSIBLE_SPEED_KMH 500U  // Train cannot exceed 500 km/h
#define MAX_PLAUSIBLE_ACCELERATION_MPS2 5U  // Train acceleration limited to 5 m/s^2

error_t ProcessSpeedSensor(const speed_sensor_t* sensor, uint16_t* speed_out) {
    uint16_t speed_kmh;
    uint16_t speed_change;
    
    // NULL pointer checks
    if (sensor == NULL) return ERROR_NULL_POINTER;
    if (speed_out == NULL) return ERROR_NULL_POINTER;
    
    speed_kmh = sensor->speed_kmh;
    
    // Plausibility check: absolute speed (defensive programming)
    if (speed_kmh > MAX_PLAUSIBLE_SPEED_KMH) {
        log_error("ProcessSpeedSensor: implausible speed %u km/h (max %u)",
                  speed_kmh, MAX_PLAUSIBLE_SPEED_KMH);
        return ERROR_IMPLAUSIBLE_DATA;
    }
    
    // Plausibility check: rate of change (defensive programming)
    if (speed_kmh > last_speed_kmh) {
        speed_change = speed_kmh - last_speed_kmh;
    } else {
        speed_change = last_speed_kmh - speed_kmh;
    }
    
    if (speed_change > MAX_PLAUSIBLE_ACCELERATION_MPS2) {
        log_error("ProcessSpeedSensor: implausible speed change %u km/h/cycle",
                  speed_change);
        return ERROR_IMPLAUSIBLE_DATA;
    }
    
    // Proceed with plausible speed
    *speed_out = speed_kmh;
    last_speed_kmh = speed_kmh;
    return SUCCESS;
}
```

**Key Points**:
- Define plausibility limits based on physical constraints
- Check absolute values (range check)
- Check rate of change (gradient check)
- Reject implausible data immediately (fail-safe)

**When to Use**:
- **MANDATORY** for all sensor inputs (SIL 1+)
- **MANDATORY** for all physical quantities with known limits
- **HIGHLY RECOMMENDED** for all data from external sources

---

## Error Detection Patterns

### Pattern 7: Hardware Fault Detection (Memory)

**Purpose**: Detect memory faults (bit flips, corruption)

**Pattern**:
```c
typedef struct {
    uint32_t data;
    uint32_t checksum;  // Simple checksum for fault detection
} protected_data_t;

// Calculate simple checksum (XOR-based)
static uint32_t CalculateChecksum(uint32_t data) {
    return ~data;  // Bitwise NOT as simple checksum
}

error_t WriteProtectedData(protected_data_t* pdata, uint32_t value) {
    // NULL pointer check
    if (pdata == NULL) return ERROR_NULL_POINTER;
    
    // Write data with checksum
    pdata->data = value;
    pdata->checksum = CalculateChecksum(value);
    
    return SUCCESS;
}

error_t ReadProtectedData(const protected_data_t* pdata, uint32_t* value) {
    uint32_t calculated_checksum;
    
    // NULL pointer checks
    if (pdata == NULL) return ERROR_NULL_POINTER;
    if (value == NULL) return ERROR_NULL_POINTER;
    
    // Verify checksum (fault detection)
    calculated_checksum = CalculateChecksum(pdata->data);
    if (calculated_checksum != pdata->checksum) {
        log_error("ReadProtectedData: checksum mismatch (expected 0x%08X, got 0x%08X)",
                  calculated_checksum, pdata->checksum);
        return ERROR_CHECKSUM_MISMATCH;
    }
    
    // Checksum valid, return data
    *value = pdata->data;
    return SUCCESS;
}
```

**Advanced: CRC-Based Protection**:
```c
#include <stdint.h>

typedef struct {
    uint32_t data;
    uint16_t crc16;  // CRC-16 for stronger protection
} crc_protected_data_t;

// CRC-16-CCITT calculation (polynomial 0x1021)
static uint16_t CalculateCRC16(uint32_t data) {
    uint16_t crc = 0xFFFFU;
    uint8_t* bytes = (uint8_t*)&data;
    uint8_t i, j;
    
    for (i = 0U; i < sizeof(uint32_t); i++) {
        crc ^= ((uint16_t)bytes[i] << 8);
        for (j = 0U; j < 8U; j++) {
            if ((crc & 0x8000U) != 0U) {
                crc = (crc << 1) ^ 0x1021U;
            } else {
                crc = crc << 1;
            }
        }
    }
    
    return crc;
}

error_t ReadCRCProtectedData(const crc_protected_data_t* pdata, uint32_t* value) {
    uint16_t calculated_crc;
    
    // NULL pointer checks
    if (pdata == NULL) return ERROR_NULL_POINTER;
    if (value == NULL) return ERROR_NULL_POINTER;
    
    // Verify CRC (fault detection)
    calculated_crc = CalculateCRC16(pdata->data);
    if (calculated_crc != pdata->crc16) {
        log_error("ReadCRCProtectedData: CRC mismatch");
        return ERROR_CRC_MISMATCH;
    }
    
    // CRC valid, return data
    *value = pdata->data;
    return SUCCESS;
}
```

**Key Points**:
- Use checksums or CRC to detect data corruption
- Simple checksum (XOR, NOT) for non-critical data
- CRC-16 or CRC-32 for safety-critical data
- Check data integrity before use

**When to Use**:
- **MANDATORY** for safety-critical data in RAM (SIL 3-4)
- **RECOMMENDED** for configuration data (SIL 2+)
- **RECOMMENDED** for data stored in EEPROM/Flash

---

### Pattern 8: Communication Fault Detection

**Purpose**: Detect communication errors (CRC, timeout, sequence errors)

**Pattern**:
```c
#define COMM_TIMEOUT_MS 1000U
#define MAX_SEQUENCE_GAP 5U

typedef struct {
    uint32_t timestamp_ms;
    uint16_t sequence_number;
    uint8_t data[64];
    uint16_t crc16;
} comm_message_t;

error_t ReceiveMessage(const comm_message_t* msg, uint8_t* data_out) {
    uint32_t current_time_ms;
    uint16_t calculated_crc;
    uint16_t sequence_gap;
    
    // NULL pointer checks
    if (msg == NULL) return ERROR_NULL_POINTER;
    if (data_out == NULL) return ERROR_NULL_POINTER;
    
    current_time_ms = GetCurrentTimeMs();
    
    // Timeout check (fault detection)
    if ((current_time_ms - msg->timestamp_ms) > COMM_TIMEOUT_MS) {
        log_error("ReceiveMessage: message timeout (age %u ms > %u ms)",
                  current_time_ms - msg->timestamp_ms, COMM_TIMEOUT_MS);
        return ERROR_TIMEOUT;
    }
    
    // Sequence number check (fault detection)
    if (msg->sequence_number > last_sequence_number) {
        sequence_gap = msg->sequence_number - last_sequence_number;
    } else {
        sequence_gap = last_sequence_number - msg->sequence_number;
    }
    
    if (sequence_gap > MAX_SEQUENCE_GAP) {
        log_error("ReceiveMessage: sequence gap detected (%u messages lost)",
                  sequence_gap);
        return ERROR_SEQUENCE_GAP;
    }
    
    // CRC check (fault detection)
    calculated_crc = CalculateCRC16Message(msg->data, sizeof(msg->data));
    if (calculated_crc != msg->crc16) {
        log_error("ReceiveMessage: CRC mismatch");
        return ERROR_CRC_MISMATCH;
    }
    
    // All checks passed, copy data
    (void)memcpy(data_out, msg->data, sizeof(msg->data));
    last_sequence_number = msg->sequence_number;
    
    return SUCCESS;
}
```

**Key Points**:
- Check message timestamp (detect stale data)
- Check sequence numbers (detect lost messages)
- Check CRC (detect corrupted data)
- Reject invalid messages immediately

**When to Use**:
- **MANDATORY** for all communication interfaces (CAN, UART, Ethernet, etc.) in safety-critical systems
- **MANDATORY** for SIL 2+ systems

---

### Pattern 9: Sensor Cross-Validation (Redundancy)

**Purpose**: Detect sensor faults using redundancy and voting

**Pattern**:
```c
#define NUM_SPEED_SENSORS 3U
#define MAX_SENSOR_DEVIATION_KMH 5U

error_t GetValidatedSpeed(const uint16_t sensor_speeds[NUM_SPEED_SENSORS],
                          uint16_t* validated_speed) {
    uint16_t sensor_a, sensor_b, sensor_c;
    uint16_t deviation_ab, deviation_ac, deviation_bc;
    uint16_t median_speed;
    
    // NULL pointer checks
    if (sensor_speeds == NULL) return ERROR_NULL_POINTER;
    if (validated_speed == NULL) return ERROR_NULL_POINTER;
    
    sensor_a = sensor_speeds[0];
    sensor_b = sensor_speeds[1];
    sensor_c = sensor_speeds[2];
    
    // Calculate deviations between sensors (cross-validation)
    deviation_ab = (sensor_a > sensor_b) ? (sensor_a - sensor_b) : (sensor_b - sensor_a);
    deviation_ac = (sensor_a > sensor_c) ? (sensor_a - sensor_c) : (sensor_c - sensor_a);
    deviation_bc = (sensor_b > sensor_c) ? (sensor_b - sensor_c) : (sensor_c - sensor_b);
    
    // Check if sensors agree within tolerance
    if ((deviation_ab > MAX_SENSOR_DEVIATION_KMH) ||
        (deviation_ac > MAX_SENSOR_DEVIATION_KMH) ||
        (deviation_bc > MAX_SENSOR_DEVIATION_KMH)) {
        log_error("GetValidatedSpeed: sensor disagreement (A=%u, B=%u, C=%u)",
                  sensor_a, sensor_b, sensor_c);
        return ERROR_SENSOR_DISAGREEMENT;
    }
    
    // Sensors agree, use median (voting)
    median_speed = MedianOfThree(sensor_a, sensor_b, sensor_c);
    *validated_speed = median_speed;
    
    return SUCCESS;
}

// Helper function: median of three values
static uint16_t MedianOfThree(uint16_t a, uint16_t b, uint16_t c) {
    uint16_t median;
    
    if (a > b) {
        if (b > c) {
            median = b;  // a > b > c
        } else if (a > c) {
            median = c;  // a > c > b
        } else {
            median = a;  // c > a > b
        }
    } else {
        if (a > c) {
            median = a;  // b > a > c
        } else if (b > c) {
            median = c;  // b > c > a
        } else {
            median = b;  // c > b > a
        }
    }
    
    return median;
}
```

**Key Points**:
- Use multiple sensors for critical measurements
- Cross-validate sensors (detect faulty sensor)
- Use voting (median, majority) to select valid value
- Define tolerance for sensor agreement

**When to Use**:
- **MANDATORY** for safety-critical sensors (speed, position, brake pressure) in SIL 3-4
- **HIGHLY RECOMMENDED** for SIL 2

---

## Error Handling Patterns

### Pattern 10: Error Return Codes

**Purpose**: Explicit error reporting using return codes

**MISRA C Reference**: MISRA C:2012 Rule 17.7 (return value must be used)

**Pattern**:
```c
// Error code definitions
typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER = 1,
    ERROR_OUT_OF_RANGE = 2,
    ERROR_INVALID_STATE = 3,
    ERROR_TIMEOUT = 4,
    ERROR_CRC_MISMATCH = 5,
    ERROR_IMPLAUSIBLE_DATA = 6,
    // ... more error codes
} error_t;

// Function with error return code
error_t PerformOperation(uint32_t input, uint32_t* output) {
    error_t err;
    
    // Input validation
    if (output == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (input > MAX_INPUT_VALUE) {
        return ERROR_OUT_OF_RANGE;
    }
    
    // Call sub-function and check return code (defensive programming)
    err = SubOperation(input);
    if (err != SUCCESS) {
        log_error("PerformOperation: SubOperation failed with error %d", (int)err);
        return err;  // Propagate error to caller
    }
    
    // Proceed with operation
    *output = input * 2U;
    return SUCCESS;
}

// Caller must check return code (MISRA C Rule 17.7)
void Caller(void) {
    uint32_t result;
    error_t err;
    
    err = PerformOperation(100U, &result);
    if (err != SUCCESS) {
        // Handle error
        log_error("Caller: PerformOperation failed with error %d", (int)err);
        EnterSafeState();  // Fail-safe action
        return;
    }
    
    // Use result (only if no error)
    UseResult(result);
}
```

**Key Points**:
- Use enum for error codes (type-safe, readable)
- Define `SUCCESS = 0` (allows `if (err != SUCCESS)` pattern)
- Always check return codes (MISRA C mandatory)
- Propagate errors to caller (or handle locally)
- Log errors for diagnostics

**When to Use**:
- **MANDATORY** for all functions that can fail (SIL 2+)
- **MANDATORY** for safety-critical functions (all SILs)

---

### Pattern 11: Error Logging

**Purpose**: Record errors for diagnostics and post-mortem analysis

**Pattern**:
```c
// Error logging levels
typedef enum {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO = 1,
    LOG_LEVEL_WARNING = 2,
    LOG_LEVEL_ERROR = 3,
    LOG_LEVEL_CRITICAL = 4
} log_level_t;

// Error log entry
typedef struct {
    uint32_t timestamp_ms;
    log_level_t level;
    error_t error_code;
    uint16_t line_number;
    const char* file_name;
    char message[64];
} log_entry_t;

// Error logging function
void LogError(log_level_t level, error_t error_code, 
              const char* file, uint16_t line, const char* message) {
    log_entry_t entry;
    
    // Populate log entry
    entry.timestamp_ms = GetCurrentTimeMs();
    entry.level = level;
    entry.error_code = error_code;
    entry.line_number = line;
    entry.file_name = file;
    (void)strncpy(entry.message, message, sizeof(entry.message) - 1U);
    entry.message[sizeof(entry.message) - 1U] = '\0';
    
    // Store log entry (circular buffer, EEPROM, etc.)
    StoreLogEntry(&entry);
    
    // Critical errors trigger immediate action
    if (level == LOG_LEVEL_CRITICAL) {
        EnterSafeState();
    }
}

// Macro for convenient error logging
#define LOG_ERROR(error_code, message) \
    LogError(LOG_LEVEL_ERROR, error_code, __FILE__, __LINE__, message)

#define LOG_CRITICAL(error_code, message) \
    LogError(LOG_LEVEL_CRITICAL, error_code, __FILE__, __LINE__, message)

// Usage example
error_t ProcessSensor(const sensor_data_t* sensor) {
    if (sensor == NULL) {
        LOG_ERROR(ERROR_NULL_POINTER, "ProcessSensor: sensor is NULL");
        return ERROR_NULL_POINTER;
    }
    
    if (sensor->value > MAX_PLAUSIBLE_VALUE) {
        LOG_CRITICAL(ERROR_IMPLAUSIBLE_DATA, "ProcessSensor: implausible sensor value");
        return ERROR_IMPLAUSIBLE_DATA;  // EnterSafeState() called by LOG_CRITICAL
    }
    
    return SUCCESS;
}
```

**Key Points**:
- Use log levels (DEBUG, INFO, WARNING, ERROR, CRITICAL)
- Record timestamp, error code, file, line number
- Store logs persistently (circular buffer, EEPROM)
- Critical errors trigger immediate safe state

**When to Use**:
- **MANDATORY** for all safety-critical systems (SIL 1+)
- **RECOMMENDED** for all embedded systems (diagnostics)

---

## Fail-Safe Patterns

### Pattern 12: Safe State Entry

**Purpose**: Transition to safe state on unrecoverable errors

**EN 50128 Reference**: Fail-safe behavior is required for safety-critical systems

**Pattern**:
```c
// Safe state definition
typedef enum {
    SAFE_STATE_BRAKES_APPLIED = 0,
    SAFE_STATE_POWER_OFF = 1,
    SAFE_STATE_ISOLATION = 2
} safe_state_t;

static bool safe_state_active = false;

// Enter safe state (fail-safe action)
void EnterSafeState(safe_state_t state) {
    // Idempotent: multiple calls to EnterSafeState are safe
    if (safe_state_active) {
        return;  // Already in safe state
    }
    
    // Log critical event
    LOG_CRITICAL(ERROR_SAFE_STATE_ENTRY, "Entering safe state");
    
    // Perform safe state actions
    switch (state) {
        case SAFE_STATE_BRAKES_APPLIED:
            // Apply emergency brakes
            SetBrakesState(BRAKES_EMERGENCY);
            // Cut power to motors
            SetMotorPower(POWER_OFF);
            break;
            
        case SAFE_STATE_POWER_OFF:
            // Cut all power
            SetSystemPower(POWER_OFF);
            break;
            
        case SAFE_STATE_ISOLATION:
            // Isolate faulty subsystem
            IsolateFaultySubsystem();
            break;
            
        default:
            // Unknown safe state (should never happen)
            SetBrakesState(BRAKES_EMERGENCY);
            SetMotorPower(POWER_OFF);
            break;
    }
    
    // Mark safe state active
    safe_state_active = true;
    
    // Remain in safe state until manual reset
    while (true) {
        // Watchdog refresh (prevent watchdog reset in safe state)
        RefreshWatchdog();
        
        // Wait for operator intervention
        // (In real system, wait for manual reset or safe recovery procedure)
    }
}

// Usage in safety-critical function
error_t SafeCriticalOperation(uint32_t input) {
    error_t err;
    
    // Perform operation with error checking
    err = PerformCriticalTask(input);
    if (err != SUCCESS) {
        // Unrecoverable error in safety-critical function
        LOG_CRITICAL(err, "SafeCriticalOperation: critical failure");
        EnterSafeState(SAFE_STATE_BRAKES_APPLIED);  // Does not return
    }
    
    return SUCCESS;
}
```

**Key Points**:
- Define safe states for system (brakes applied, power off, isolation)
- Safe state entry is **idempotent** (multiple calls safe)
- Log critical event before entering safe state
- Safe state is maintained until manual intervention
- Safe state actions are **irreversible** (cannot exit automatically)

**When to Use**:
- **MANDATORY** for all safety-critical systems (SIL 1+)
- **MANDATORY** on unrecoverable errors in safety-critical functions

---

### Pattern 13: Watchdog Timer

**Purpose**: Detect software hangs and reset system

**Pattern**:
```c
#define WATCHDOG_TIMEOUT_MS 100U

// Watchdog initialization
void InitWatchdog(void) {
    // Configure hardware watchdog timer
    WATCHDOG_CONTROL_REG = WATCHDOG_ENABLE | WATCHDOG_TIMEOUT_MS;
}

// Watchdog refresh (must be called periodically)
void RefreshWatchdog(void) {
    // Write magic value to watchdog register (hardware-specific)
    WATCHDOG_REFRESH_REG = WATCHDOG_MAGIC_VALUE;
}

// Main loop with watchdog refresh
void MainLoop(void) {
    while (true) {
        // Perform cyclic tasks
        ReadSensors();
        ProcessData();
        UpdateOutputs();
        
        // Refresh watchdog at end of cycle (defensive programming)
        RefreshWatchdog();
        
        // Wait for next cycle
        WaitForNextCycle();
    }
}

// Safety-critical function with bounded execution time
error_t TimeBoundedOperation(void) {
    uint32_t start_time_ms;
    uint32_t elapsed_time_ms;
    error_t err;
    
    start_time_ms = GetCurrentTimeMs();
    
    // Perform operation with timeout check
    err = PerformOperation();
    
    elapsed_time_ms = GetCurrentTimeMs() - start_time_ms;
    
    // Check execution time (defensive programming)
    if (elapsed_time_ms > MAX_EXECUTION_TIME_MS) {
        LOG_ERROR(ERROR_TIMEOUT, "TimeBoundedOperation: exceeded time limit");
        return ERROR_TIMEOUT;
    }
    
    return err;
}
```

**Key Points**:
- Hardware watchdog timer resets system if not refreshed
- Refresh watchdog at end of each cycle (proves software executing)
- Do NOT refresh watchdog in error handlers or safe state
- Watchdog timeout should be short (100-1000ms typical)
- Bounded execution time prevents watchdog timeout

**When to Use**:
- **MANDATORY** for all safety-critical systems (SIL 1+)
- **HIGHLY RECOMMENDED** for all embedded systems

---

## Data Integrity Patterns

### Pattern 14: Critical Data Protection

**Purpose**: Protect safety-critical data from corruption

**Pattern**:
```c
// Safety-critical data with redundancy and checksums
typedef struct {
    uint32_t speed_kmh;           // Primary speed value
    uint32_t speed_kmh_copy;      // Redundant copy
    uint32_t checksum;            // Checksum for integrity
} critical_speed_t;

// Write critical data (with redundancy and checksum)
void WriteCriticalSpeed(critical_speed_t* data, uint32_t speed_kmh) {
    uint32_t checksum;
    
    // Calculate checksum
    checksum = speed_kmh ^ CHECKSUM_SEED;
    
    // Write data with redundancy
    data->speed_kmh = speed_kmh;
    data->speed_kmh_copy = speed_kmh;
    data->checksum = checksum;
}

// Read critical data (with integrity checks)
error_t ReadCriticalSpeed(const critical_speed_t* data, uint32_t* speed_kmh) {
    uint32_t calculated_checksum;
    
    // NULL pointer checks
    if (data == NULL) return ERROR_NULL_POINTER;
    if (speed_kmh == NULL) return ERROR_NULL_POINTER;
    
    // Check redundancy (defensive programming)
    if (data->speed_kmh != data->speed_kmh_copy) {
        LOG_ERROR(ERROR_DATA_CORRUPTION, "ReadCriticalSpeed: redundancy check failed");
        return ERROR_DATA_CORRUPTION;
    }
    
    // Check checksum (defensive programming)
    calculated_checksum = data->speed_kmh ^ CHECKSUM_SEED;
    if (calculated_checksum != data->checksum) {
        LOG_ERROR(ERROR_CHECKSUM_MISMATCH, "ReadCriticalSpeed: checksum mismatch");
        return ERROR_CHECKSUM_MISMATCH;
    }
    
    // Data integrity verified
    *speed_kmh = data->speed_kmh;
    return SUCCESS;
}
```

**Key Points**:
- Use redundancy (duplicate data)
- Use checksums or CRC for integrity
- Verify integrity before using data
- Reject corrupted data immediately

**When to Use**:
- **MANDATORY** for all safety-critical data (SIL 3-4)
- **HIGHLY RECOMMENDED** for important data (SIL 2)

---

## Control Flow Validation Patterns

### Pattern 15: Assertion Checks (Invariants)

**Purpose**: Verify program invariants during execution

**EN 50128 Reference**: Annex D.24 "Failure Assertion Programming"

**MISRA C Reference**: MISRA C:2012 Directive 4.6 (use of assert.h discouraged in production)

**Pattern** (Custom Assert for Safety-Critical Code):
```c
// Custom assertion macro (do NOT use standard assert.h in safety code)
#define ASSERT(condition, error_code) \
    do { \
        if (!(condition)) { \
            LOG_CRITICAL(error_code, "Assertion failed: " #condition); \
            EnterSafeState(SAFE_STATE_BRAKES_APPLIED); \
        } \
    } while (0)

// Usage: Verify invariants in safety-critical code
error_t ProcessControlLoop(void) {
    uint32_t speed_kmh;
    error_t err;
    
    // Read speed
    err = ReadSpeed(&speed_kmh);
    if (err != SUCCESS) return err;
    
    // Assertion: speed must be within valid range (invariant)
    ASSERT((speed_kmh >= 0U) && (speed_kmh <= MAX_SPEED_KMH), 
           ERROR_INVARIANT_VIOLATION);
    
    // Assertion: system must be in valid state (invariant)
    ASSERT((system_state >= STATE_IDLE) && (system_state <= STATE_SHUTDOWN),
           ERROR_INVALID_STATE);
    
    // Perform control loop logic
    // ...
    
    return SUCCESS;
}
```

**Key Points**:
- Use assertions to verify invariants (conditions that must always be true)
- Do NOT use standard `assert.h` in safety-critical code (may be disabled in production)
- Use custom ASSERT macro that logs and enters safe state
- Assertions complement (not replace) error checking

**When to Use**:
- **RECOMMENDED** for safety-critical functions (SIL 2+)
- **RECOMMENDED** for verifying complex invariants

---

### Pattern 16: Sequence Checking

**Purpose**: Verify operations occur in correct order

**Pattern**:
```c
typedef enum {
    SEQ_STATE_INIT = 0,
    SEQ_STATE_CONFIGURED = 1,
    SEQ_STATE_RUNNING = 2,
    SEQ_STATE_STOPPED = 3
} sequence_state_t;

static sequence_state_t sequence_state = SEQ_STATE_INIT;

error_t Initialize(void) {
    // Sequence check: must be in INIT state
    if (sequence_state != SEQ_STATE_INIT) {
        LOG_ERROR(ERROR_INVALID_SEQUENCE, "Initialize: invalid sequence state");
        return ERROR_INVALID_SEQUENCE;
    }
    
    // Perform initialization
    // ...
    
    // Advance sequence state
    sequence_state = SEQ_STATE_CONFIGURED;
    return SUCCESS;
}

error_t Start(void) {
    // Sequence check: must be in CONFIGURED state
    if (sequence_state != SEQ_STATE_CONFIGURED) {
        LOG_ERROR(ERROR_INVALID_SEQUENCE, "Start: invalid sequence state");
        return ERROR_INVALID_SEQUENCE;
    }
    
    // Start operation
    // ...
    
    // Advance sequence state
    sequence_state = SEQ_STATE_RUNNING;
    return SUCCESS;
}

error_t Stop(void) {
    // Sequence check: must be in RUNNING state
    if (sequence_state != SEQ_STATE_RUNNING) {
        LOG_ERROR(ERROR_INVALID_SEQUENCE, "Stop: invalid sequence state");
        return ERROR_INVALID_SEQUENCE;
    }
    
    // Stop operation
    // ...
    
    // Advance sequence state
    sequence_state = SEQ_STATE_STOPPED;
    return SUCCESS;
}
```

**Key Points**:
- Track sequence state (initialization, configuration, running, stopped)
- Verify correct state before each operation
- Reject out-of-sequence operations
- Advance state only after successful operation

**When to Use**:
- **RECOMMENDED** for systems with initialization sequences
- **RECOMMENDED** for safety-critical state machines

---

## Resource Management Patterns

### Pattern 17: Static Memory Allocation

**Purpose**: Avoid dynamic memory allocation (required for SIL 2+)

**MISRA C Reference**: MISRA C:2012 Rule 21.3 (malloc/free shall not be used)

**Pattern**:
```c
// Static allocation: all memory allocated at compile-time
#define MAX_SENSORS 10U
#define MAX_MESSAGE_QUEUE_SIZE 32U

// Static array (no dynamic allocation)
static sensor_data_t sensor_array[MAX_SENSORS];

// Static message queue (no dynamic allocation)
static message_t message_queue[MAX_MESSAGE_QUEUE_SIZE];
static uint16_t queue_head = 0U;
static uint16_t queue_tail = 0U;
static uint16_t queue_count = 0U;

// Queue operations with bounds checking
error_t EnqueueMessage(const message_t* msg) {
    // NULL pointer check
    if (msg == NULL) return ERROR_NULL_POINTER;
    
    // Queue full check (defensive programming)
    if (queue_count >= MAX_MESSAGE_QUEUE_SIZE) {
        LOG_ERROR(ERROR_QUEUE_FULL, "EnqueueMessage: queue full");
        return ERROR_QUEUE_FULL;
    }
    
    // Add message to queue
    message_queue[queue_tail] = *msg;
    queue_tail = (queue_tail + 1U) % MAX_MESSAGE_QUEUE_SIZE;
    queue_count++;
    
    return SUCCESS;
}

error_t DequeueMessage(message_t* msg) {
    // NULL pointer check
    if (msg == NULL) return ERROR_NULL_POINTER;
    
    // Queue empty check (defensive programming)
    if (queue_count == 0U) {
        return ERROR_QUEUE_EMPTY;
    }
    
    // Remove message from queue
    *msg = message_queue[queue_head];
    queue_head = (queue_head + 1U) % MAX_MESSAGE_QUEUE_SIZE;
    queue_count--;
    
    return SUCCESS;
}
```

**Key Points**:
- Allocate all memory at compile-time (static arrays, static structs)
- Use fixed-size data structures (no dynamic resizing)
- Use circular buffers for queues
- Check bounds (queue full, queue empty)

**When to Use**:
- **MANDATORY** for SIL 2+ systems (no malloc/free allowed)
- **HIGHLY RECOMMENDED** for all embedded systems

---

## Complete Example: Safety-Critical Function

### Pattern 18: Comprehensive Defensive Programming

**Purpose**: Demonstrate all defensive programming patterns in a complete safety-critical function

```c
/**
 * @brief Safety-critical overspeed detection function
 * 
 * This function reads redundant speed sensors, validates the data,
 * and activates emergency brakes if overspeed is detected.
 * 
 * @param sensors Array of 3 redundant speed sensors (input)
 * @param brake_output Brake control output (output)
 * @return SUCCESS if operation completed successfully, error code otherwise
 * 
 * Safety Requirement: REQ-SAFE-001 "System SHALL detect overspeed within 100ms"
 * SIL: 4 (highest safety integrity level)
 */
error_t OverspeedDetection(const speed_sensor_t sensors[NUM_SPEED_SENSORS],
                           brake_control_t* brake_output) {
    uint16_t sensor_speeds[NUM_SPEED_SENSORS];
    uint16_t validated_speed;
    uint32_t current_time_ms;
    error_t err;
    uint8_t i;
    
    /* ========== INPUT VALIDATION (Defensive Programming) ========== */
    
    // NULL pointer checks (Pattern 1)
    if (sensors == NULL) {
        LOG_CRITICAL(ERROR_NULL_POINTER, "OverspeedDetection: sensors is NULL");
        EnterSafeState(SAFE_STATE_BRAKES_APPLIED);  // Does not return
    }
    
    if (brake_output == NULL) {
        LOG_CRITICAL(ERROR_NULL_POINTER, "OverspeedDetection: brake_output is NULL");
        EnterSafeState(SAFE_STATE_BRAKES_APPLIED);  // Does not return
    }
    
    // Sequence check (Pattern 16)
    if (system_state != STATE_RUNNING) {
        LOG_ERROR(ERROR_INVALID_STATE, "OverspeedDetection: system not running");
        return ERROR_INVALID_STATE;
    }
    
    /* ========== SENSOR DATA VALIDATION ========== */
    
    // Read and validate each sensor
    for (i = 0U; i < NUM_SPEED_SENSORS; i++) {
        // Plausibility check: absolute speed (Pattern 6)
        if (sensors[i].speed_kmh > MAX_PLAUSIBLE_SPEED_KMH) {
            LOG_ERROR(ERROR_IMPLAUSIBLE_DATA, 
                      "OverspeedDetection: sensor %u implausible (%u km/h)",
                      i, sensors[i].speed_kmh);
            // Continue with other sensors (fault tolerance)
            sensor_speeds[i] = 0U;  // Mark as invalid
        } else {
            sensor_speeds[i] = sensors[i].speed_kmh;
        }
        
        // Timestamp check: detect stale data (Pattern 8)
        current_time_ms = GetCurrentTimeMs();
        if ((current_time_ms - sensors[i].timestamp_ms) > SENSOR_TIMEOUT_MS) {
            LOG_ERROR(ERROR_TIMEOUT,
                      "OverspeedDetection: sensor %u timeout (age %u ms)",
                      i, current_time_ms - sensors[i].timestamp_ms);
            sensor_speeds[i] = 0U;  // Mark as invalid
        }
    }
    
    /* ========== SENSOR CROSS-VALIDATION (Pattern 9) ========== */
    
    err = GetValidatedSpeed(sensor_speeds, &validated_speed);
    if (err != SUCCESS) {
        // Sensor disagreement or all sensors invalid
        LOG_CRITICAL(err, "OverspeedDetection: sensor validation failed");
        
        // Fail-safe action: apply emergency brakes (Pattern 12)
        brake_output->emergency_brake = BRAKE_ACTIVE;
        brake_output->service_brake = BRAKE_ACTIVE;
        LOG_CRITICAL(ERROR_SENSOR_FAULT, "Emergency brakes activated (sensor fault)");
        
        return err;
    }
    
    /* ========== OVERSPEED DETECTION (Safety-Critical Logic) ========== */
    
    // Range check: ensure speed within valid range (Pattern 2)
    ASSERT((validated_speed >= 0U) && (validated_speed <= MAX_SPEED_KMH),
           ERROR_INVARIANT_VIOLATION);
    
    // Overspeed detection
    if (validated_speed > OVERSPEED_THRESHOLD_KMH) {
        // OVERSPEED DETECTED (safety hazard)
        LOG_CRITICAL(ERROR_OVERSPEED, 
                     "OVERSPEED DETECTED: %u km/h (threshold %u km/h)",
                     validated_speed, OVERSPEED_THRESHOLD_KMH);
        
        // Fail-safe action: apply emergency brakes (Pattern 12)
        brake_output->emergency_brake = BRAKE_ACTIVE;
        brake_output->service_brake = BRAKE_ACTIVE;
        
        // Increment overspeed counter (diagnostics)
        overspeed_event_count++;
        
        // Return success (emergency brakes applied as intended)
        return SUCCESS;
    }
    
    /* ========== NORMAL OPERATION ========== */
    
    // Speed within limits, release emergency brakes
    brake_output->emergency_brake = BRAKE_INACTIVE;
    
    // Service brakes controlled by operator (not this function)
    // (Do not modify service_brake in normal operation)
    
    // Postcondition assertion (Pattern 15)
    ASSERT((brake_output->emergency_brake == BRAKE_INACTIVE) ||
           (brake_output->emergency_brake == BRAKE_ACTIVE),
           ERROR_INVARIANT_VIOLATION);
    
    return SUCCESS;
}

/**
 * @brief Main control loop with defensive programming
 */
void MainControlLoop(void) {
    speed_sensor_t sensors[NUM_SPEED_SENSORS];
    brake_control_t brake_output;
    error_t err;
    uint32_t cycle_count = 0U;
    
    // Initialize system
    InitializeSystem();
    
    // Main loop
    while (true) {
        // Read sensors
        ReadSpeedSensors(sensors);
        
        // Overspeed detection (safety-critical function)
        err = OverspeedDetection(sensors, &brake_output);
        if (err != SUCCESS) {
            // Error logged by OverspeedDetection
            // Emergency brakes already applied if needed
            // Continue monitoring (do not stop control loop)
        }
        
        // Apply brake output
        SetBrakeControl(&brake_output);
        
        // Increment cycle counter
        cycle_count++;
        
        // Refresh watchdog (Pattern 13)
        RefreshWatchdog();
        
        // Wait for next cycle (50ms typical)
        WaitForNextCycle();
    }
}
```

**Defensive Programming Techniques Applied**:
1. ✅ NULL pointer checks (Pattern 1)
2. ✅ Range checks (Pattern 2)
3. ✅ Plausibility checks (Pattern 6)
4. ✅ Timeout checks (Pattern 8)
5. ✅ Sensor cross-validation (Pattern 9)
6. ✅ Error return codes (Pattern 10)
7. ✅ Error logging (Pattern 11)
8. ✅ Fail-safe behavior (Pattern 12)
9. ✅ Watchdog refresh (Pattern 13)
10. ✅ Assertion checks (Pattern 15)
11. ✅ Sequence checking (Pattern 16)

**EN 50128 Compliance**:
- ✅ Defensive Programming (Table A.3, Technique 2) - Highly Recommended SIL 3-4
- ✅ Fault Detection and Diagnosis (Table A.3, Technique 3) - Highly Recommended SIL 3-4
- ✅ Failure Assertion Programming (Annex D.24)

**MISRA C:2012 Compliance**:
- ✅ No undefined behavior (Rule 1.3)
- ✅ No dynamic memory allocation (Rule 21.3)
- ✅ Fixed-width types (uint16_t, uint32_t)
- ✅ Return values checked (Rule 17.7)

---

## Summary: Defensive Programming Checklist

### Input Validation
- [ ] Check all pointer parameters for NULL
- [ ] Check all numeric parameters for valid range
- [ ] Check all enum/state parameters for valid values
- [ ] Check all array indices for bounds
- [ ] Check all string lengths
- [ ] Check all physical values for plausibility

### Error Detection
- [ ] Checksum/CRC for critical data
- [ ] Timeout checks for communication
- [ ] Sequence number checks
- [ ] Sensor cross-validation (redundancy)
- [ ] Hardware fault detection (memory, communication, sensors)

### Error Handling
- [ ] Use error return codes for all fallible functions
- [ ] Check all return codes (MISRA C mandatory)
- [ ] Log all errors with context
- [ ] Propagate errors to caller or handle locally

### Fail-Safe Behavior
- [ ] Define safe states (brakes applied, power off, isolation)
- [ ] Enter safe state on unrecoverable errors
- [ ] Safe state is idempotent (multiple calls safe)
- [ ] Safe state maintained until manual intervention

### Data Integrity
- [ ] Redundancy for critical data (duplicate values)
- [ ] Checksums/CRC for data integrity
- [ ] Verify integrity before using data

### Control Flow Validation
- [ ] Assertions for invariants
- [ ] Sequence checks for operation order
- [ ] State machine validation

### Resource Management
- [ ] Static memory allocation only (SIL 2+)
- [ ] Bounded execution time (watchdog compatible)
- [ ] Queue/buffer overflow protection

---

## References

- **EN 50128:2011 Table A.3**: Software Architecture and Design Techniques, Technique 2 "Defensive Programming" (Highly Recommended SIL 3-4)
- **EN 50128:2011 Annex D.14**: Defensive Programming definition and techniques
- **EN 50128:2011 Annex D.24**: Failure Assertion Programming (preconditions and postconditions)
- **MISRA C:2012**: C Coding Standard for Safety-Critical Systems
  - Rule 1.3: No undefined behavior
  - Rule 17.7: Return value must be used
  - Rule 21.3: malloc/free shall not be used
- **IEC 61508**: Functional Safety standard (defensive programming techniques applicable across domains)

---

**END OF DEFENSIVE PROGRAMMING PATTERNS**
