# Modularity Guidelines for EN 50128 Railway Safety Software

**Purpose**: This document provides comprehensive guidance on modular design principles for EN 50128-compliant railway safety software written in C. It defines module design principles, sizing guidelines, interface patterns, coupling/cohesion metrics, and architecture patterns to achieve maintainable, testable, and safety-critical software systems.

**Scope**: Applies to Software Architecture Specification (DOC-9) and Software Design Specification (DOC-10) development.

**Audience**: Designers (DES), Implementers (IMP), Verifiers (VER), Quality Assurance (QUA)

**EN 50128 Reference**: Table A.3 Technique 19 "Modular Approach" - **MANDATORY SIL 2+**, Highly Recommended SIL 1

---

## Table of Contents

1. [Introduction to Modular Design](#1-introduction-to-modular-design)
2. [Module Design Principles](#2-module-design-principles)
3. [Module Size Guidelines](#3-module-size-guidelines)
4. [Interface Design for Modules](#4-interface-design-for-modules)
5. [Coupling Metrics and Management](#5-coupling-metrics-and-management)
6. [Cohesion Metrics and Management](#6-cohesion-metrics-and-management)
7. [Module Decomposition Strategies](#7-module-decomposition-strategies)
8. [Architecture Patterns](#8-architecture-patterns)
9. [Examples: Good vs. Bad Modularity](#9-examples-good-vs-bad-modularity)
10. [MISRA C Modularity Considerations](#10-misra-c-modularity-considerations)
11. [Module Review Checklist](#11-module-review-checklist)
12. [References](#12-references)

---

## 1. Introduction to Modular Design

### 1.1 What is Modularity?

**Modularity** is the decomposition of a software system into independent, interchangeable components (modules) with well-defined interfaces. Each module:
- Has a **single, clear responsibility** (Single Responsibility Principle)
- Encapsulates its **internal implementation details** (Information Hiding)
- Exposes a **minimal, stable public interface** (Interface Segregation)
- Has **minimal dependencies** on other modules (Low Coupling)
- Has **highly related internal elements** (High Cohesion)

### 1.2 Benefits of Modular Design

**For Railway Safety Software**:
- ✅ **Testability**: Modules can be tested in isolation (unit testing)
- ✅ **Verifiability**: Smaller, focused modules are easier to verify (static analysis, code review)
- ✅ **Maintainability**: Changes are localized to individual modules
- ✅ **Reusability**: Well-designed modules can be reused across projects
- ✅ **Scalability**: New functionality can be added without affecting existing modules
- ✅ **Safety**: Fault isolation - failures are contained within modules
- ✅ **Certification**: Modules can be certified individually (EN 50128 Section 7.6)

### 1.3 EN 50128 Requirements

**Table A.3 Technique 19: "Modular Approach"**

| SIL Level | Requirement | Rationale |
|-----------|-------------|-----------|
| **SIL 0** | Recommended (R) | Improves maintainability |
| **SIL 1** | Highly Recommended (HR) | Improves testability and verifiability |
| **SIL 2** | **MANDATORY (M)** | Required for systematic development |
| **SIL 3** | **MANDATORY (M)** | Required for safety-critical systems |
| **SIL 4** | **MANDATORY (M)** | Essential for highest safety integrity |

**EN 50128 Section 7.3.2.3**: "The Software Architecture Specification shall define the software components (modules) and their interfaces."

**EN 50128 Annex D.38**: "Modular Approach - The software is divided into discrete components (modules) such that a change to one component has minimal impact on other components. Each module should have a single, well-defined purpose."

### 1.4 When to Apply Modular Design

**Apply from the earliest design phases**:
- ✅ Software Architecture Specification (DOC-9) - Define high-level modules
- ✅ Software Design Specification (DOC-10) - Define detailed module interfaces
- ✅ Implementation - Implement modules as separate .c/.h file pairs
- ✅ Testing - Test modules independently (unit testing)
- ✅ Integration - Integrate modules progressively (EN 50128 Section 7.6)

---

## 2. Module Design Principles

### 2.1 Single Responsibility Principle (SRP)

**Definition**: Each module should have **one, and only one, reason to change**.

**Rationale**: A module with multiple responsibilities is harder to understand, test, and maintain. Changes to one responsibility may inadvertently affect other responsibilities.

**Example (BAD - Multiple Responsibilities)**:
```c
// sensor_manager.c - Violates SRP (3 responsibilities)
// 1. Sensor data acquisition
// 2. Data validation and processing
// 3. Logging and error reporting

void sensor_manager_process(void) {
    // Acquire sensor data (Responsibility 1)
    raw_data = adc_read(SENSOR_CHANNEL);
    
    // Validate and process (Responsibility 2)
    if (raw_data < MIN_VALUE || raw_data > MAX_VALUE) {
        // Log error (Responsibility 3)
        log_error("Sensor out of range");
        return ERROR;
    }
    
    processed_data = raw_data * SCALE_FACTOR;
    // More processing...
}
```

**Example (GOOD - Single Responsibility per Module)**:
```c
// sensor_acquisition.c - Responsibility: Raw sensor data acquisition
uint16_t sensor_read_raw(sensor_id_t sensor) {
    return adc_read(sensor_to_channel(sensor));
}

// sensor_validation.c - Responsibility: Data validation
error_t sensor_validate(sensor_id_t sensor, uint16_t raw_value, 
                        sensor_range_t* range) {
    if (raw_value < range->min || raw_value > range->max) {
        return ERROR_OUT_OF_RANGE;
    }
    return SUCCESS;
}

// sensor_processing.c - Responsibility: Data processing
int32_t sensor_process(uint16_t raw_value, sensor_calibration_t* cal) {
    return (int32_t)raw_value * cal->scale_factor + cal->offset;
}

// error_logger.c - Responsibility: Error logging
void log_sensor_error(sensor_id_t sensor, error_t error) {
    log_entry_t entry;
    entry.timestamp = get_timestamp();
    entry.source = LOG_SOURCE_SENSOR;
    entry.sensor_id = sensor;
    entry.error_code = error;
    log_write(&entry);
}
```

**Benefits**:
- Each module is easier to understand (focused purpose)
- Changes are localized (e.g., changing calibration logic doesn't affect logging)
- Each module can be tested independently
- Each module can be verified independently

### 2.2 High Cohesion

**Definition**: Elements (functions, data) within a module should be **closely related** and contribute to a single, well-defined purpose.

**Cohesion Hierarchy** (best to worst):
1. ✅ **Functional Cohesion**: All elements contribute to a single task (BEST)
2. ✅ **Sequential Cohesion**: Output of one element is input to next (GOOD)
3. ⚠️ **Communicational Cohesion**: Elements operate on same data (ACCEPTABLE)
4. ⚠️ **Procedural Cohesion**: Elements executed in sequence (WEAK)
5. ❌ **Temporal Cohesion**: Elements executed at same time (POOR)
6. ❌ **Logical Cohesion**: Elements grouped by type (POOR)
7. ❌ **Coincidental Cohesion**: No relationship (WORST)

**Example (POOR - Logical Cohesion)**:
```c
// utils.c - Logically cohesive (all "utility" functions)
// BUT elements are unrelated
void utils_init(void) {
    // Initialize random number generator
    srand(time(NULL));
    // Initialize CRC table
    crc_table_init();
    // Initialize string buffer
    string_buffer_clear();
}
```

**Example (GOOD - Functional Cohesion)**:
```c
// crc.c - Functionally cohesive (all contribute to CRC calculation)
static uint32_t crc_table[256];

void crc_table_init(void) {
    for (uint16_t i = 0; i < 256; i++) {
        crc_table[i] = crc_reflect(i, 8) << 24;
        for (uint8_t j = 0; j < 8; j++) {
            crc_table[i] = (crc_table[i] << 1) ^ 
                          ((crc_table[i] & (1 << 31)) ? POLYNOMIAL : 0);
        }
        crc_table[i] = crc_reflect(crc_table[i], 32);
    }
}

uint32_t crc_calculate(const uint8_t* data, size_t length) {
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; i++) {
        crc = (crc >> 8) ^ crc_table[(crc ^ data[i]) & 0xFF];
    }
    return crc ^ 0xFFFFFFFF;
}

bool crc_verify(const uint8_t* data, size_t length, uint32_t expected_crc) {
    return crc_calculate(data, length) == expected_crc;
}
```

**Target**: Aim for **Functional or Sequential Cohesion** in all modules.

### 2.3 Low Coupling

**Definition**: Modules should have **minimal dependencies** on other modules.

**Coupling Types** (loosest to tightest):
1. ✅ **No Coupling**: Modules are independent (BEST, but rare)
2. ✅ **Data Coupling**: Modules communicate via parameters (GOOD)
3. ⚠️ **Stamp Coupling**: Modules share composite data structures (ACCEPTABLE)
4. ⚠️ **Control Coupling**: One module controls behavior of another (WEAK)
5. ❌ **External Coupling**: Modules share external data (POOR)
6. ❌ **Common Coupling**: Modules share global data (POOR)
7. ❌ **Content Coupling**: One module modifies another's internals (WORST)

**Example (BAD - Common Coupling via Global Data)**:
```c
// global.c
uint16_t g_sensor_value;  // Global shared data
bool g_sensor_valid;

// sensor_reader.c
void sensor_read(void) {
    g_sensor_value = adc_read(SENSOR_CHANNEL);
    g_sensor_valid = (g_sensor_value < MAX_VALUE);
}

// control_logic.c
void control_update(void) {
    if (g_sensor_valid) {  // Direct access to global
        output = calculate_control(g_sensor_value);
    }
}
```

**Example (GOOD - Data Coupling via Parameters)**:
```c
// sensor_reader.c
error_t sensor_read(sensor_data_t* data) {
    if (data == NULL) return ERROR_NULL_POINTER;
    
    data->raw_value = adc_read(SENSOR_CHANNEL);
    data->valid = (data->raw_value < MAX_VALUE);
    data->timestamp = get_timestamp();
    
    return SUCCESS;
}

// control_logic.c
error_t control_update(const sensor_data_t* sensor, control_output_t* output) {
    if (sensor == NULL || output == NULL) return ERROR_NULL_POINTER;
    
    if (!sensor->valid) return ERROR_INVALID_SENSOR_DATA;
    
    output->value = calculate_control(sensor->raw_value);
    output->timestamp = get_timestamp();
    
    return SUCCESS;
}

// main.c
void control_loop(void) {
    sensor_data_t sensor_data;
    control_output_t control_output;
    
    if (sensor_read(&sensor_data) == SUCCESS) {
        if (control_update(&sensor_data, &control_output) == SUCCESS) {
            actuator_set(&control_output);
        }
    }
}
```

**Target**: Use **Data Coupling** or **Stamp Coupling** wherever possible. Avoid global data.

### 2.4 Information Hiding

**Definition**: Module **internals (implementation details) are hidden** from other modules. Only the public interface is visible.

**Rationale**: Changes to module internals do not affect other modules, as long as the interface remains stable.

**Example (BAD - Exposed Internals)**:
```c
// sensor.h - Exposes internal state
typedef struct {
    uint16_t raw_value;        // Internal state exposed
    uint16_t filtered_value;   // Internal state exposed
    uint16_t history[10];      // Internal buffer exposed
    uint8_t history_index;     // Internal index exposed
} sensor_state_t;

extern sensor_state_t g_sensor_state;  // Global state exposed

// Other modules can directly access and modify internals
void some_function(void) {
    g_sensor_state.raw_value = 0;  // Direct modification
}
```

**Example (GOOD - Information Hiding)**:
```c
// sensor.h - Public interface only
typedef struct sensor_t sensor_t;  // Opaque type (forward declaration)

error_t sensor_init(sensor_t* sensor);
error_t sensor_read(sensor_t* sensor, uint16_t* value);
error_t sensor_get_filtered(const sensor_t* sensor, uint16_t* filtered);

// sensor.c - Internal state hidden
struct sensor_t {
    uint16_t raw_value;        // Internal state (not in .h)
    uint16_t filtered_value;   // Internal state (not in .h)
    uint16_t history[10];      // Internal buffer (not in .h)
    uint8_t history_index;     // Internal index (not in .h)
};

static void sensor_update_filter(sensor_t* sensor);  // Internal function (static)

error_t sensor_read(sensor_t* sensor, uint16_t* value) {
    if (sensor == NULL || value == NULL) return ERROR_NULL_POINTER;
    
    sensor->raw_value = adc_read(SENSOR_CHANNEL);
    sensor_update_filter(sensor);  // Internal helper
    *value = sensor->raw_value;
    
    return SUCCESS;
}

static void sensor_update_filter(sensor_t* sensor) {
    // Internal implementation (not visible outside module)
    sensor->history[sensor->history_index] = sensor->raw_value;
    sensor->history_index = (sensor->history_index + 1) % 10;
    
    uint32_t sum = 0;
    for (uint8_t i = 0; i < 10; i++) {
        sum += sensor->history[i];
    }
    sensor->filtered_value = (uint16_t)(sum / 10);
}
```

**Benefits**:
- Implementation can be changed without affecting other modules
- Module internals cannot be accidentally corrupted by other modules
- Easier to verify module correctness (internal invariants maintained)

### 2.5 Interface Segregation

**Definition**: Modules should expose **minimal, focused interfaces**. Clients should not depend on interfaces they don't use.

**Example (BAD - Fat Interface)**:
```c
// sensor.h - Fat interface (many unrelated functions)
error_t sensor_init(sensor_t* sensor);
error_t sensor_read(sensor_t* sensor, uint16_t* value);
error_t sensor_calibrate(sensor_t* sensor, calibration_t* cal);
error_t sensor_self_test(sensor_t* sensor, test_result_t* result);
error_t sensor_get_statistics(sensor_t* sensor, statistics_t* stats);
error_t sensor_clear_statistics(sensor_t* sensor);
error_t sensor_log_enable(sensor_t* sensor, bool enable);
error_t sensor_log_get_entries(sensor_t* sensor, log_entry_t* entries, size_t* count);
error_t sensor_power_save(sensor_t* sensor, power_mode_t mode);
// ... 20 more functions
```

**Example (GOOD - Segregated Interfaces)**:
```c
// sensor_io.h - Core I/O interface (minimal)
error_t sensor_init(sensor_t* sensor);
error_t sensor_read(sensor_t* sensor, uint16_t* value);

// sensor_calibration.h - Calibration interface (separate)
error_t sensor_calibrate(sensor_t* sensor, const calibration_t* cal);
error_t sensor_verify_calibration(const sensor_t* sensor);

// sensor_diagnostics.h - Diagnostics interface (separate)
error_t sensor_self_test(sensor_t* sensor, test_result_t* result);
error_t sensor_get_statistics(const sensor_t* sensor, statistics_t* stats);

// sensor_logging.h - Logging interface (separate)
error_t sensor_log_enable(sensor_t* sensor, bool enable);
error_t sensor_log_get_entries(const sensor_t* sensor, log_entry_t* entries, size_t* count);

// sensor_power.h - Power management interface (separate)
error_t sensor_power_set_mode(sensor_t* sensor, power_mode_t mode);
```

**Benefits**:
- Clients depend only on interfaces they use
- Changes to one interface don't affect clients of other interfaces
- Easier to test (mock only required interfaces)
- Clearer dependencies

---

## 3. Module Size Guidelines

### 3.1 Lines of Code per Module

**Target Range**: 200-1000 LOC per module (.c file)

| Module Size | LOC Range | Assessment | Action |
|-------------|-----------|------------|--------|
| **Too Small** | < 100 | May indicate over-decomposition | Consider merging with related module |
| **Small** | 100-200 | Acceptable for simple modules | OK if functionally cohesive |
| **Ideal** | 200-500 | Sweet spot for most modules | Preferred size |
| **Acceptable** | 500-1000 | Larger modules (complex functionality) | Review for decomposition opportunities |
| **Large** | 1000-2000 | Approaching upper limit | Consider decomposing |
| **Too Large** | > 2000 | Difficult to understand and test | **MUST decompose** |

**Rationale**:
- **< 200 LOC**: May be over-decomposed (too many small files, navigation overhead)
- **200-500 LOC**: Easy to understand in single reading session
- **500-1000 LOC**: Acceptable if module has well-defined, complex purpose
- **> 1000 LOC**: Difficult to keep entire module in working memory

**SIL-Dependent Recommendations**:
- **SIL 0-1**: 200-1000 LOC acceptable
- **SIL 2**: 200-800 LOC recommended (easier verification)
- **SIL 3-4**: 200-500 LOC recommended (rigorous verification required)

### 3.2 Functions per Module

**Target Range**: 5-20 functions per module

| Function Count | Assessment | Action |
|----------------|------------|--------|
| **1-3 functions** | Very small module | Consider merging or verifying single responsibility |
| **5-10 functions** | Ideal for most modules | Preferred range |
| **10-20 functions** | Acceptable for complex modules | Review for decomposition |
| **> 20 functions** | Likely violates SRP | **Decompose into multiple modules** |

**Example**: A typical well-designed module might have:
- 1 initialization function
- 2-3 primary public API functions
- 2-4 secondary/utility public API functions
- 3-8 private static helper functions

### 3.3 File Organization

**One Module = One .c/.h File Pair**

```
module_name.h    -> Public interface (types, function declarations)
module_name.c    -> Implementation (private data, static functions, public functions)
```

**Example**:
```c
// speed_controller.h (Public interface)
#ifndef SPEED_CONTROLLER_H
#define SPEED_CONTROLLER_H

#include <stdint.h>
#include "error_codes.h"

typedef struct speed_controller_t speed_controller_t;

error_t speed_controller_init(speed_controller_t* ctrl);
error_t speed_controller_update(speed_controller_t* ctrl, uint16_t current_speed);
error_t speed_controller_set_target(speed_controller_t* ctrl, uint16_t target_speed);
error_t speed_controller_get_output(const speed_controller_t* ctrl, int16_t* output);

#endif /* SPEED_CONTROLLER_H */

// speed_controller.c (Implementation)
#include "speed_controller.h"
#include <stdlib.h>

#define MAX_ERROR 1000
#define KP 10
#define KI 5
#define KD 2

struct speed_controller_t {
    uint16_t target_speed;
    uint16_t current_speed;
    int32_t integral_error;
    int16_t previous_error;
    int16_t output;
};

static int16_t clamp(int32_t value, int16_t min, int16_t max);  // Private helper

error_t speed_controller_init(speed_controller_t* ctrl) {
    if (ctrl == NULL) return ERROR_NULL_POINTER;
    
    ctrl->target_speed = 0;
    ctrl->current_speed = 0;
    ctrl->integral_error = 0;
    ctrl->previous_error = 0;
    ctrl->output = 0;
    
    return SUCCESS;
}

static int16_t clamp(int32_t value, int16_t min, int16_t max) {
    if (value < (int32_t)min) return min;
    if (value > (int32_t)max) return max;
    return (int16_t)value;
}

// ... other functions
```

### 3.4 Complexity per Module

**Target**: Sum of cyclomatic complexities of all functions in module should be manageable.

**Rule of Thumb**: If module has 10 functions, and complexity limit is 10 per function (SIL 3-4), then total module complexity ≤ 100.

**Typical Distribution**:
- Simple modules: Total complexity 20-50
- Moderate modules: Total complexity 50-100
- Complex modules: Total complexity 100-200

**If total module complexity > 200**: Consider decomposing into multiple modules.

---

## 4. Interface Design for Modules

### 4.1 Public API Design Principles

**1. Minimal Interface**: Expose only necessary functions
```c
// BAD: Exposing internal helpers
error_t sensor_read_raw(sensor_t* s);
error_t sensor_apply_calibration(sensor_t* s);  // Internal step
error_t sensor_apply_filtering(sensor_t* s);    // Internal step
error_t sensor_validate_range(sensor_t* s);     // Internal step

// GOOD: Single public function (helpers are static)
error_t sensor_read(sensor_t* s, uint16_t* value);
```

**2. Stable Interface**: Changes to interface require updating all clients
```c
// Design interfaces to minimize future changes
// Use structs for configuration (can add fields without breaking API)
typedef struct {
    uint16_t sample_rate_hz;
    uint16_t filter_window;
    bool enable_logging;
    // Can add new fields here without breaking API
} sensor_config_t;

error_t sensor_configure(sensor_t* s, const sensor_config_t* config);
```

**3. Consistent Error Handling**: All functions return error_t
```c
error_t sensor_read(sensor_t* sensor, uint16_t* value);
error_t sensor_calibrate(sensor_t* sensor, const calibration_t* cal);
error_t sensor_self_test(sensor_t* sensor, test_result_t* result);
```

**4. Const Correctness**: Use const for read-only parameters
```c
error_t control_update(const sensor_data_t* input, control_output_t* output);
//                      ^^^^^                       (read-only)
```

**5. Opaque Types**: Hide internal structure
```c
// Public header (sensor.h)
typedef struct sensor_t sensor_t;  // Forward declaration only

// Implementation (sensor.c)
struct sensor_t {
    // Internal fields (not visible to clients)
};
```

### 4.2 Parameter Passing Guidelines

**For Structs**: Pass by pointer (not by value)
```c
// BAD: Pass by value (copies entire struct)
error_t process_data(sensor_data_t data);  // Inefficient

// GOOD: Pass by pointer
error_t process_data(const sensor_data_t* data);  // Efficient
```

**For Output Parameters**: Use pointers
```c
error_t sensor_read(sensor_t* sensor, uint16_t* value);
//                                    ^^^^^^^^^ output parameter
```

**For Arrays**: Pass pointer and length
```c
error_t filter_apply(const uint16_t* input, size_t input_len,
                     uint16_t* output, size_t output_len);
```

**Validate All Inputs**:
```c
error_t sensor_read(sensor_t* sensor, uint16_t* value) {
    if (sensor == NULL) return ERROR_NULL_POINTER;
    if (value == NULL) return ERROR_NULL_POINTER;
    
    // Function body
}
```

### 4.3 Encapsulation Patterns

**Pattern 1: Opaque Pointer**
```c
// Public header
typedef struct sensor_t sensor_t;

error_t sensor_create(sensor_t** sensor);  // Allocates sensor
error_t sensor_destroy(sensor_t* sensor);  // Deallocates sensor

// Implementation
struct sensor_t {
    // Hidden internals
};

error_t sensor_create(sensor_t** sensor) {
    if (sensor == NULL) return ERROR_NULL_POINTER;
    
    *sensor = malloc(sizeof(sensor_t));  // Note: Avoid malloc in SIL 2+
    if (*sensor == NULL) return ERROR_OUT_OF_MEMORY;
    
    return sensor_init(*sensor);
}
```

**Pattern 2: Client-Allocated (Preferred for SIL 2+)**
```c
// Public header
typedef struct sensor_t sensor_t;

size_t sensor_get_size(void);  // Returns sizeof(sensor_t)
error_t sensor_init(sensor_t* sensor);

// Client code (static allocation)
static uint8_t sensor_buffer[sensor_get_size()];
sensor_t* sensor = (sensor_t*)sensor_buffer;
sensor_init(sensor);
```

**Pattern 3: Compile-Time Opaque (Best for SIL 3-4)**
```c
// Public header
#define SENSOR_SIZE 64  // Fixed size (compile-time constant)

typedef struct {
    uint8_t opaque_data[SENSOR_SIZE];
} sensor_t;

error_t sensor_init(sensor_t* sensor);

// Implementation
typedef struct {
    uint16_t raw_value;
    uint16_t filtered_value;
    // ... internal fields (total ≤ 64 bytes)
} sensor_internal_t;

_Static_assert(sizeof(sensor_internal_t) <= SENSOR_SIZE, "Sensor size exceeded");

error_t sensor_init(sensor_t* sensor) {
    sensor_internal_t* internal = (sensor_internal_t*)sensor->opaque_data;
    // Initialize internal
}
```

---

## 5. Coupling Metrics and Management

### 5.1 Afferent Coupling (Ca)

**Definition**: Number of modules that **depend on** this module (incoming dependencies).

**Interpretation**:
- **High Ca**: Many modules depend on this module → Module is **stable** (used by many)
- **Low Ca**: Few modules depend on this module → Module is **unstable** (can be changed easily)

**Example**:
```
error_codes.h (Ca = 15) → Many modules use error codes → Highly stable
sensor_driver.c (Ca = 3) → Few modules use sensor driver → Less stable
```

**Measurement**:
```bash
# Count #include directives for this module
grep -r "include \"sensor_driver.h\"" src/ | wc -l
```

### 5.2 Efferent Coupling (Ce)

**Definition**: Number of modules that **this module depends on** (outgoing dependencies).

**Interpretation**:
- **High Ce**: This module depends on many others → Module is **unstable** (affected by many changes)
- **Low Ce**: This module has few dependencies → Module is **stable** (less affected by changes)

**Example**:
```
main.c (Ce = 10) → Depends on many modules → Unstable
crc.c (Ce = 1) → Depends only on stdint.h → Stable
```

**Measurement**:
```bash
# Count #include directives in this module
grep "^#include" src/sensor_driver.c | wc -l
```

### 5.3 Instability Metric (I)

**Definition**: I = Ce / (Ca + Ce)

**Range**: 0.0 (maximally stable) to 1.0 (maximally unstable)

**Interpretation**:
- **I = 0**: Module has no outgoing dependencies, but many incoming → Maximally stable
- **I = 1**: Module has no incoming dependencies, but many outgoing → Maximally unstable
- **I = 0.5**: Balanced coupling

**Guidelines**:
- **Foundational modules** (error_codes, types, CRC): Target I < 0.2 (stable)
- **Application modules** (main, control_logic): Target I > 0.5 (acceptable instability)
- **Avoid I > 0.8**: Highly unstable modules (too many dependencies, few dependents)

**Example Calculation**:
```
Module: speed_controller.c
Ca = 5 (5 modules include speed_controller.h)
Ce = 3 (speed_controller.c includes: stdint.h, error_codes.h, sensor_io.h)

I = Ce / (Ca + Ce) = 3 / (5 + 3) = 3 / 8 = 0.375

Interpretation: Moderately stable (good for control module)
```

### 5.4 Managing Coupling

**Strategy 1: Dependency Inversion**
```c
// BAD: High-level module depends on low-level module
// control_logic.c
#include "uart_driver.h"  // Direct dependency on low-level driver

void send_status(void) {
    uart_send_byte(STATUS_OK);  // Tight coupling
}

// GOOD: Both depend on abstraction
// communication_interface.h (abstraction)
typedef error_t (*send_byte_fn_t)(uint8_t byte);

typedef struct {
    send_byte_fn_t send_byte;
} comm_interface_t;

// control_logic.c
#include "communication_interface.h"  // Depends on abstraction

void send_status(const comm_interface_t* comm) {
    comm->send_byte(STATUS_OK);  // Loose coupling
}

// uart_driver.c (implements abstraction)
error_t uart_send_byte(uint8_t byte) { /* ... */ }

// main.c (wires up)
comm_interface_t comm = { .send_byte = uart_send_byte };
send_status(&comm);
```

**Strategy 2: Layered Architecture** (see Section 8.1)

**Strategy 3: Minimize Global Dependencies**
```c
// BAD: Global configuration affects all modules
extern config_t g_global_config;

// GOOD: Pass configuration explicitly
error_t module_init(module_t* module, const module_config_t* config);
```

---

## 6. Cohesion Metrics and Management

### 6.1 LCOM (Lack of Cohesion of Methods)

**Note**: LCOM is primarily an OOP metric, but the concept applies to C modules.

**Simplified LCOM for C Modules**:
- Count number of functions in module: N
- Count number of shared data elements (static variables): M
- For each function, count which data elements it accesses
- If functions share many data elements → High cohesion
- If functions share few data elements → Low cohesion

**Example (Low Cohesion)**:
```c
// utils.c - Functions share NO common data
static uint32_t crc_table[256];      // Used only by crc_calculate()
static char string_buffer[256];      // Used only by string_format()
static uint32_t random_seed;         // Used only by random_generate()

uint32_t crc_calculate(const uint8_t* data, size_t len) {
    // Uses crc_table only
}

void string_format(const char* fmt, ...) {
    // Uses string_buffer only
}

uint32_t random_generate(void) {
    // Uses random_seed only
}

// LCOM is HIGH (bad) - functions don't share data → Module lacks cohesion
```

**Example (High Cohesion)**:
```c
// pid_controller.c - Functions share common data
typedef struct {
    int16_t kp, ki, kd;           // Shared by all functions
    int32_t integral_error;       // Shared by all functions
    int16_t previous_error;       // Shared by all functions
} pid_state_t;

void pid_init(pid_state_t* state, int16_t kp, int16_t ki, int16_t kd) {
    state->kp = kp;
    state->ki = ki;
    state->kd = kd;
    state->integral_error = 0;
    state->previous_error = 0;
}

int16_t pid_update(pid_state_t* state, int16_t error) {
    state->integral_error += error;
    int16_t derivative = error - state->previous_error;
    state->previous_error = error;
    
    return state->kp * error + state->ki * state->integral_error + 
           state->kd * derivative;
}

void pid_reset(pid_state_t* state) {
    state->integral_error = 0;
    state->previous_error = 0;
}

// LCOM is LOW (good) - all functions share common data → High cohesion
```

### 6.2 Achieving High Cohesion

**Guideline 1: Single Responsibility**
- If functions don't share data, they likely belong in separate modules

**Guideline 2: Group Related Functions**
```c
// GOOD: All CRC functions together
// crc.c
static uint32_t crc_table[256];

void crc_table_init(void);
uint32_t crc_calculate(const uint8_t* data, size_t len);
bool crc_verify(const uint8_t* data, size_t len, uint32_t expected);
```

**Guideline 3: Decompose God Objects**
```c
// BAD: system_manager.c (does everything)
void system_init(void);
void sensor_read(void);
void control_update(void);
void actuator_set(void);
void log_write(void);

// GOOD: Decompose into cohesive modules
// system.c
void system_init(void);

// sensor.c
void sensor_read(void);

// controller.c
void control_update(void);

// actuator.c
void actuator_set(void);

// logger.c
void log_write(void);
```

---

## 7. Module Decomposition Strategies

### 7.1 Top-Down Decomposition

**Process**:
1. Start with high-level system functionality
2. Decompose into major subsystems
3. Decompose subsystems into modules
4. Decompose modules into functions

**Example**:
```
System: Train Speed Control
  ├─ Sensor Subsystem
  │    ├─ Speed Sensor Module
  │    ├─ Position Sensor Module
  │    └─ Brake Pressure Sensor Module
  ├─ Control Subsystem
  │    ├─ Speed Controller Module
  │    ├─ Brake Controller Module
  │    └─ Traction Controller Module
  └─ Actuator Subsystem
       ├─ Brake Actuator Module
       ├─ Traction Actuator Module
       └─ Display Actuator Module
```

**Benefits**:
- Clear system architecture from the start
- Easy to assign modules to teams
- Matches EN 50128 V-Model (system → software → components)

### 7.2 Bottom-Up Composition

**Process**:
1. Identify low-level primitives (ADC, GPIO, timers)
2. Build utility modules on top of primitives
3. Build application modules on top of utilities
4. Compose system from application modules

**Example**:
```
Layer 4 (Application): train_control.c
  ├─ Uses: speed_controller.c, brake_controller.c
  └─ Layer 3 (Control): speed_controller.c
       ├─ Uses: sensor.c, actuator.c
       └─ Layer 2 (Drivers): sensor.c
            ├─ Uses: adc.c, gpio.c
            └─ Layer 1 (HAL): adc.c, gpio.c
                 └─ Hardware
```

**Benefits**:
- Reusable low-level modules
- Easier to test (test primitives first, then build up)
- Natural for hardware-centric systems

### 7.3 Functional Decomposition

**Decompose by function**: Each module implements one function of the system.

**Example**:
```
System: Train Braking System
  ├─ brake_request.c       (Function: Detect brake request from driver)
  ├─ brake_control.c       (Function: Calculate required brake force)
  ├─ brake_actuator.c      (Function: Apply brake force)
  ├─ brake_monitor.c       (Function: Monitor brake effectiveness)
  └─ brake_diagnostics.c   (Function: Diagnose brake faults)
```

**Benefits**:
- Clear mapping from requirements to modules
- Easy to trace requirements to implementation
- Each module has single, clear purpose

### 7.4 Data-Driven Decomposition

**Decompose by data flow**: Each module processes one type of data.

**Example**:
```
Data Flow: Sensor → Filtering → Control → Actuation
  ├─ sensor_data.c         (Process: Acquire raw sensor data)
  ├─ filter_data.c         (Process: Filter and validate sensor data)
  ├─ control_data.c        (Process: Compute control outputs)
  └─ actuator_data.c       (Process: Send commands to actuators)
```

**Benefits**:
- Clear data flow through system
- Easy to add processing stages
- Natural for signal processing systems

---

## 8. Architecture Patterns

### 8.1 Layered Architecture

**Structure**: Modules organized in layers, with dependencies only flowing **downward**.

```
┌─────────────────────────────────────────┐
│  Application Layer                      │
│  (control_logic.c, train_manager.c)     │
└─────────────────┬───────────────────────┘
                  │ (uses)
┌─────────────────▼───────────────────────┐
│  Middleware Layer                       │
│  (sensor_manager.c, actuator_manager.c) │
└─────────────────┬───────────────────────┘
                  │ (uses)
┌─────────────────▼───────────────────────┐
│  Driver Layer                           │
│  (adc_driver.c, pwm_driver.c)           │
└─────────────────┬───────────────────────┘
                  │ (uses)
┌─────────────────▼───────────────────────┐
│  Hardware Abstraction Layer (HAL)       │
│  (hal_gpio.c, hal_timer.c)              │
└─────────────────────────────────────────┘
```

**Rules**:
- Layer N can only call Layer N-1 (downward dependencies)
- Layer N cannot call Layer N+1 (no upward dependencies)
- Layers are independent (can replace Layer N without affecting Layer N+2)

**Example**:
```c
// Layer 1: HAL
void hal_gpio_set(gpio_pin_t pin, bool value);

// Layer 2: Driver
void brake_actuator_set(uint8_t brake_force) {
    bool enable = (brake_force > 0);
    hal_gpio_set(BRAKE_PIN, enable);  // Calls Layer 1
}

// Layer 3: Middleware
void actuator_manager_update(actuator_cmd_t* cmd) {
    brake_actuator_set(cmd->brake_force);  // Calls Layer 2
}

// Layer 4: Application
void control_logic_update(void) {
    actuator_cmd_t cmd;
    cmd.brake_force = calculate_brake_force();
    actuator_manager_update(&cmd);  // Calls Layer 3
}
```

**Benefits**:
- Clear dependencies
- Easy to test (mock lower layers)
- Easy to port (replace HAL layer)

### 8.2 Modular Architecture (Peer-to-Peer)

**Structure**: Modules at same level communicate via well-defined interfaces.

```
┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│  Sensor     │────▶│  Control    │────▶│  Actuator   │
│  Module     │     │  Module     │     │  Module     │
└─────────────┘     └─────────────┘     └─────────────┘
      │                   │                    │
      └───────────────────┴────────────────────┘
                          │
                    ┌─────▼─────┐
                    │  Logger   │
                    │  Module   │
                    └───────────┘
```

**Example**:
```c
// Modules communicate via function calls
sensor_data_t sensor_data;
sensor_read(&sensor_data);

control_output_t control_output;
control_update(&sensor_data, &control_output);

actuator_set(&control_output);
```

**Benefits**:
- Flexible (modules can be combined in different ways)
- Reusable (modules are independent)
- Testable (each module can be tested in isolation)

### 8.3 Hierarchical Architecture (Parent-Child)

**Structure**: Parent modules manage child modules.

```
                    ┌─────────────┐
                    │   System    │
                    │   Manager   │
                    └──────┬──────┘
                           │
           ┌───────────────┼───────────────┐
           │               │               │
      ┌────▼────┐    ┌─────▼────┐    ┌────▼─────┐
      │ Sensor  │    │ Control  │    │ Actuator │
      │ Manager │    │ Manager  │    │ Manager  │
      └────┬────┘    └─────┬────┘    └────┬─────┘
           │               │               │
     ┌─────┴─────┐   ┌─────┴─────┐   ┌─────┴─────┐
     │ Speed     │   │ Brake     │   │ Brake     │
     │ Sensor    │   │ Control   │   │ Actuator  │
     └───────────┘   └───────────┘   └───────────┘
```

**Example**:
```c
// system_manager.c (parent)
void system_init(void) {
    sensor_manager_init();   // Initialize child
    control_manager_init();  // Initialize child
    actuator_manager_init(); // Initialize child
}

void system_update(void) {
    sensor_manager_update();   // Update child
    control_manager_update();  // Update child
    actuator_manager_update(); // Update child
}

// sensor_manager.c (child)
void sensor_manager_init(void) {
    speed_sensor_init();     // Initialize grandchild
    position_sensor_init();  // Initialize grandchild
}
```

**Benefits**:
- Clear ownership
- Easy to understand (tree structure)
- Matches organizational hierarchy

### 8.4 Pipe-and-Filter Architecture

**Structure**: Data flows through processing stages (filters).

```
Sensor → Filter 1 → Filter 2 → Control → Actuator
         (Validate) (Smooth)   (PID)
```

**Example**:
```c
// Each filter is a module
void raw_data_validate(const raw_data_t* input, validated_data_t* output);
void validated_data_smooth(const validated_data_t* input, smoothed_data_t* output);
void smoothed_data_control(const smoothed_data_t* input, control_cmd_t* output);

// Pipeline
raw_data_t raw;
sensor_read(&raw);

validated_data_t validated;
raw_data_validate(&raw, &validated);

smoothed_data_t smoothed;
validated_data_smooth(&validated, &smoothed);

control_cmd_t cmd;
smoothed_data_control(&smoothed, &cmd);

actuator_set(&cmd);
```

**Benefits**:
- Easy to add/remove processing stages
- Easy to test (each filter independently)
- Natural for signal processing

---

## 9. Examples: Good vs. Bad Modularity

### 9.1 Example 1: God Object (BAD)

**Problem**: One module does everything (violates SRP, low cohesion, high coupling).

```c
// system.c - GOD OBJECT (3000 LOC, 50 functions)
// Responsibilities:
// - Sensor reading (10 functions)
// - Data validation (8 functions)
// - Control logic (15 functions)
// - Actuator control (7 functions)
// - Logging (5 functions)
// - Diagnostics (5 functions)

static uint16_t g_speed_sensor_raw;
static uint16_t g_position_sensor_raw;
static uint16_t g_brake_pressure_raw;
static int16_t g_control_output;
static uint8_t g_brake_command;
// ... 50 more global variables

void system_init(void) {
    // 200 lines of initialization
}

void system_update(void) {
    // Read sensors
    g_speed_sensor_raw = adc_read(SPEED_SENSOR_CHANNEL);
    g_position_sensor_raw = adc_read(POSITION_SENSOR_CHANNEL);
    
    // Validate sensors
    if (g_speed_sensor_raw < MIN_SPEED || g_speed_sensor_raw > MAX_SPEED) {
        log_error("Speed sensor out of range");
        g_speed_sensor_raw = 0;
    }
    
    // Control logic
    int16_t error = TARGET_SPEED - g_speed_sensor_raw;
    g_control_output = PID_KP * error;  // Simplified PID
    
    // Actuator control
    if (g_control_output < 0) {
        g_brake_command = (uint8_t)(-g_control_output);
        pwm_set(BRAKE_PWM, g_brake_command);
    }
    
    // Logging
    log_write(LOG_SPEED, g_speed_sensor_raw);
    
    // ... 500 more lines
}

// ... 48 more functions
```

**Problems**:
- ❌ 3000 LOC in one file (too large)
- ❌ 50 functions (too many)
- ❌ Multiple responsibilities (sensor, control, actuator, logging)
- ❌ High coupling (everything depends on everything)
- ❌ Low cohesion (functions not related)
- ❌ Difficult to test (cannot test parts in isolation)
- ❌ Difficult to verify (too complex)
- ❌ Cannot reuse components

### 9.2 Example 1: Modular Design (GOOD)

**Solution**: Decompose into cohesive, loosely coupled modules.

```c
// sensor.c (200 LOC, 5 functions) - Responsibility: Sensor reading
error_t sensor_read(sensor_id_t id, uint16_t* value);
error_t sensor_validate(sensor_id_t id, uint16_t value, const sensor_range_t* range);

// control.c (300 LOC, 8 functions) - Responsibility: Control logic
error_t control_init(control_t* ctrl, const control_params_t* params);
error_t control_update(control_t* ctrl, int16_t error, int16_t* output);

// actuator.c (150 LOC, 4 functions) - Responsibility: Actuator control
error_t actuator_set_brake(uint8_t brake_force);
error_t actuator_set_traction(uint8_t traction_force);

// logger.c (200 LOC, 6 functions) - Responsibility: Logging
error_t log_write(log_source_t source, uint16_t value);

// main.c (100 LOC, 2 functions) - Responsibility: Orchestration
void control_loop(void) {
    uint16_t speed;
    sensor_read(SENSOR_SPEED, &speed);
    
    int16_t control_output;
    control_update(&controller, target_speed - speed, &control_output);
    
    if (control_output < 0) {
        actuator_set_brake((uint8_t)(-control_output));
    }
    
    log_write(LOG_SPEED, speed);
}
```

**Benefits**:
- ✅ 5 modules, each 100-300 LOC (manageable size)
- ✅ Each module has single responsibility
- ✅ Low coupling (modules communicate via function calls)
- ✅ High cohesion (related functions in same module)
- ✅ Easy to test (each module independently)
- ✅ Easy to verify (smaller, focused modules)
- ✅ Reusable (sensor module can be used in other projects)

### 9.3 Example 2: Tight Coupling (BAD)

**Problem**: Modules directly access each other's internals.

```c
// sensor.c
uint16_t g_sensor_value;  // Global, exposed to all modules

void sensor_read(void) {
    g_sensor_value = adc_read(SENSOR_CHANNEL);
}

// control.c
extern uint16_t g_sensor_value;  // Direct access to sensor's global

void control_update(void) {
    int16_t error = TARGET - g_sensor_value;  // Tight coupling
    // ...
}

// logger.c
extern uint16_t g_sensor_value;  // Direct access to sensor's global

void log_update(void) {
    log_write(g_sensor_value);  // Tight coupling
}
```

**Problems**:
- ❌ Global data exposed (no encapsulation)
- ❌ Tight coupling (control and logger depend on sensor internals)
- ❌ Difficult to test (cannot mock sensor)
- ❌ Changes to sensor affect control and logger

### 9.4 Example 2: Loose Coupling (GOOD)

**Solution**: Modules communicate via function calls (data coupling).

```c
// sensor.c
static uint16_t sensor_value;  // Private (static)

error_t sensor_read(uint16_t* value) {
    if (value == NULL) return ERROR_NULL_POINTER;
    
    sensor_value = adc_read(SENSOR_CHANNEL);
    *value = sensor_value;
    
    return SUCCESS;
}

// control.c
void control_update(uint16_t sensor_value) {
    int16_t error = TARGET - sensor_value;  // Loose coupling (parameter)
    // ...
}

// logger.c
void log_update(uint16_t sensor_value) {
    log_write(sensor_value);  // Loose coupling (parameter)
}

// main.c
void control_loop(void) {
    uint16_t sensor_value;
    sensor_read(&sensor_value);  // Get value via function call
    
    control_update(sensor_value);  // Pass via parameter
    log_update(sensor_value);      // Pass via parameter
}
```

**Benefits**:
- ✅ No global data (encapsulation)
- ✅ Loose coupling (via parameters)
- ✅ Easy to test (can pass mock values)
- ✅ Changes to sensor internals don't affect control/logger

---

## 10. MISRA C Modularity Considerations

### 10.1 File Organization (MISRA C Rule 8.8)

**Rule 8.8**: "An external object or function shall be declared once in one and only one file."

**Guideline**: One module = one .c/.h file pair.

```c
// sensor.h
extern uint16_t sensor_read(void);  // Declared in header

// sensor.c
#include "sensor.h"
uint16_t sensor_read(void) { /* ... */ }  // Defined in .c file

// control.c
#include "sensor.h"
void control_update(void) {
    uint16_t value = sensor_read();  // Uses declaration from header
}
```

### 10.2 Header Guards (MISRA C Directive 4.10)

**Directive 4.10**: "Precautions shall be taken to prevent the contents of a header file being included more than once."

```c
// sensor.h
#ifndef SENSOR_H
#define SENSOR_H

// Header contents

#endif /* SENSOR_H */
```

### 10.3 Static Functions (Information Hiding)

**MISRA C Rule 8.7**: "Functions and objects should not be defined with external linkage if they are referenced in only one translation unit."

**Guideline**: Module-internal functions should be declared `static`.

```c
// sensor.c
static void sensor_calibrate_internal(void);  // Internal helper (static)

uint16_t sensor_read(void) {  // Public API (external linkage)
    sensor_calibrate_internal();  // Call internal helper
    return adc_read(SENSOR_CHANNEL);
}

static void sensor_calibrate_internal(void) {
    // Implementation (not visible outside module)
}
```

### 10.4 Static Data (Encapsulation)

**Guideline**: Module-internal data should be declared `static` (file scope).

```c
// sensor.c
static uint16_t sensor_value;        // Internal state (static)
static sensor_state_t sensor_state;  // Internal state (static)

uint16_t sensor_read(void) {
    sensor_value = adc_read(SENSOR_CHANNEL);
    return sensor_value;
}
```

### 10.5 External Linkage (Minimal Public API)

**Guideline**: Only public API functions should have external linkage (declared in .h file).

```c
// sensor.h - Public API
extern error_t sensor_init(sensor_t* sensor);
extern error_t sensor_read(sensor_t* sensor, uint16_t* value);
// Only 2 public functions

// sensor.c - Implementation
static void sensor_apply_calibration(sensor_t* sensor);  // Internal (static)
static void sensor_apply_filter(sensor_t* sensor);       // Internal (static)
static bool sensor_validate_range(uint16_t value);       // Internal (static)

error_t sensor_init(sensor_t* sensor) { /* ... */ }      // Public
error_t sensor_read(sensor_t* sensor, uint16_t* value) { /* ... */ }  // Public
```

### 10.6 No Dynamic Memory Allocation (MISRA C Rule 21.3, SIL 2+)

**Rule 21.3**: "The memory allocation and deallocation functions of <stdlib.h> shall not be used."

**Guideline**: All module data should be statically allocated (SIL 2+).

```c
// BAD: Dynamic allocation (forbidden SIL 2+)
sensor_t* sensor_create(void) {
    sensor_t* sensor = malloc(sizeof(sensor_t));  // Forbidden
    return sensor;
}

// GOOD: Static allocation (SIL 2+)
#define MAX_SENSORS 10
static sensor_t sensors[MAX_SENSORS];  // Static array

error_t sensor_allocate(sensor_id_t id, sensor_t** sensor) {
    if (id >= MAX_SENSORS) return ERROR_INVALID_ID;
    *sensor = &sensors[id];
    return SUCCESS;
}
```

---

## 11. Module Review Checklist

### 11.1 Design Phase Checklist

**Module Identification**:
- [ ] Module has single, clear responsibility (SRP)
- [ ] Module name reflects its responsibility (e.g., `speed_controller`, `brake_actuator`)
- [ ] Module boundaries are well-defined
- [ ] Module does not duplicate functionality of existing modules

**Module Size**:
- [ ] Module size is 200-1000 LOC (target: 200-500 for SIL 3-4)
- [ ] Module has 5-20 functions
- [ ] Total module complexity is manageable (< 200 for SIL 3-4)

**Module Interface**:
- [ ] Module exposes minimal public API (5-10 public functions typical)
- [ ] All public functions are necessary (no "just in case" functions)
- [ ] Interface is stable (unlikely to change frequently)
- [ ] All public functions documented in header (.h file)

**Module Dependencies**:
- [ ] Module has low coupling (Ce < 5 for most modules)
- [ ] Module does not create circular dependencies
- [ ] Module dependencies follow layered architecture (if applicable)
- [ ] Module does not depend on implementation details of other modules

### 11.2 Implementation Phase Checklist

**File Organization**:
- [ ] One module = one .c/.h file pair
- [ ] Header file has include guards (MISRA C Directive 4.10)
- [ ] Header file contains only public interface (types, function declarations)
- [ ] Implementation file contains all internal details (static functions, static data)

**Information Hiding**:
- [ ] Internal functions are declared `static` (MISRA C Rule 8.7)
- [ ] Internal data is declared `static` (file scope)
- [ ] Module internals are not exposed in header file
- [ ] Opaque types used where appropriate

**Coupling**:
- [ ] Module uses data coupling or stamp coupling (not common/content coupling)
- [ ] Module does not access global data from other modules
- [ ] Module communicates via function calls (not shared globals)
- [ ] Instability metric I is appropriate (< 0.5 for stable modules)

**Cohesion**:
- [ ] All functions in module are related (contribute to single purpose)
- [ ] Module achieves functional or sequential cohesion
- [ ] No "utility" or "helper" modules with unrelated functions

**MISRA C Compliance**:
- [ ] External functions declared in header, defined in .c file (Rule 8.8)
- [ ] No dynamic memory allocation (Rule 21.3, SIL 2+)
- [ ] Fixed-width types used (`uint8_t`, not `unsigned char`)
- [ ] All inputs validated (defensive programming)

### 11.3 Verification Phase Checklist

**Static Analysis**:
- [ ] Module passes Cppcheck with no errors
- [ ] Module passes MISRA C checker with no mandatory violations (SIL 2+)
- [ ] Module complexity within limits (≤10 per function for SIL 3-4)
- [ ] No compiler warnings (gcc -Wall -Wextra -Werror)

**Code Review**:
- [ ] Module reviewed by peer (independent of author)
- [ ] Module reviewed by QA (MANDATORY all SILs)
- [ ] Module reviewed by VER (MANDATORY SIL 3-4)
- [ ] All review findings addressed

**Testing**:
- [ ] Module unit tests achieve required coverage (100% for SIL 3-4)
- [ ] Module can be tested in isolation (mocking dependencies)
- [ ] Module passes all unit tests
- [ ] Module integration tests pass

**Traceability**:
- [ ] Module traces to requirements (requirements_to_design matrix)
- [ ] Module functions trace to test cases (design_to_test matrix)
- [ ] Traceability verified via `traceability.py validate`

---

## 12. References

### 12.1 EN 50128 Standard References

- **Section 7.3**: Software Architecture and Design
- **Section 7.3.2.3**: "The Software Architecture Specification shall define the software components (modules) and their interfaces."
- **Table A.3 Technique 19**: "Modular Approach" (MANDATORY SIL 2+)
- **Annex D.38**: "Modular Approach" definition

### 12.2 MISRA C:2012 References

- **Directive 4.10**: Header file inclusion guards
- **Rule 8.7**: Static functions and objects
- **Rule 8.8**: External object/function declarations
- **Rule 21.3**: No dynamic memory allocation (SIL 2+)

### 12.3 Software Engineering References

- Martin, Robert C. "Clean Architecture: A Craftsman's Guide to Software Structure and Design" (2017)
  - Single Responsibility Principle
  - Dependency Inversion Principle
  - Component Cohesion and Coupling

- Stevens, W., Myers, G., Constantine, L. "Structured Design" (1974)
  - Coupling and Cohesion metrics (foundational paper)

- Martin, Robert C. "Agile Software Development: Principles, Patterns, and Practices" (2002)
  - SOLID principles applied to module design

- Parnas, D.L. "On the Criteria To Be Used in Decomposing Systems into Modules" (1972)
  - Information hiding (foundational paper)

### 12.4 Related Workflow Documents

- `.opencode/skills/en50128-design/workflows/architecture-design.md` - Architecture design process
- `.opencode/skills/en50128-design/workflows/software-design.md` - Detailed design process
- `.opencode/skills/en50128-design/workflows/design-review.md` - Design review process

### 12.5 Related Resource Documents

- `.opencode/skills/en50128-design/resources/defensive-programming-patterns.md` - Defensive programming
- `.opencode/skills/en50128-design/resources/complexity-guidelines.md` - Complexity management

### 12.6 Tool Documentation

- `docs/designs/TRACEABILITY-MANAGER-DESIGN.md` - Traceability validation tool
- `docs/designs/WORKFLOW-MANAGER-DESIGN.md` - Document workflow management tool

---

**Document Control**:
- **Version**: 1.0
- **Date**: 2026-03-13
- **Author**: EN50128 Design Skill Enhancement (Phase 2)
- **Status**: Draft
- **Review Status**: Pending QUA review

---

**END OF DOCUMENT**
