# Interface Design Workflow

**Skill**: en50128-design  
**Document**: Software Interface Specifications (DOC-11)  
**EN 50128 Reference**: Section 7.3 (Software Architecture and Design)  
**Lifecycle Phase**: Phase 3 (Architecture & Design)  
**Primary Role**: Designer (DES)

---

## Purpose

This workflow guides the creation of **Software Interface Specifications**, which define all interfaces between:
- Software components (internal interfaces)
- Software and hardware (hardware interfaces)
- Software and external systems (external interfaces)
- Software and human operators (human-machine interfaces)

Interface specifications are **CRITICAL for EN 50128 compliance** because:
- **SIL 3-4**: Fully defined interfaces are HIGHLY RECOMMENDED (Table A.3, Technique 7)
- Poor interface design is a leading cause of integration defects
- Interfaces must be testable, traceable, and verifiable
- Hardware interfaces require defensive programming (error detection, validation)

---

## Inputs

### Required Inputs
1. **Software Architecture Specification (DOC-9)** - Architecture components and their relationships
2. **Software Requirements Specification (DOC-6)** - Interface requirements (INT-REQ-*)
3. **System Requirements Specification** - System-level interfaces
4. **Hardware Specifications** - Hardware interface details (I/O, memory maps, registers)

### Supporting Inputs
5. **Hazard Log** - Safety requirements for interfaces
6. **MISRA C Guidelines** - C interface design constraints
7. **Target Platform Specification** - Platform-specific interface details

---

## Outputs

### Primary Outputs
1. **Software Interface Specifications (DOC-11)** - Complete interface definitions
2. **Interface Traceability Matrix** - Requirements → Interfaces traceability
3. **Interface Test Specifications** - How interfaces will be tested

### Supporting Outputs
4. **Interface Design Review Report** - Peer review findings
5. **Interface Verification Report** - VER approval for SIL 3-4

---

## EN 50128 Techniques Applied

| Technique | SIL 0 | SIL 1-2 | SIL 3-4 | Reference | Application |
|-----------|-------|---------|---------|-----------|-------------|
| **Fully Defined Interface** | HR | HR | HR | D.38 | All interfaces formally specified |
| **Information Encapsulation** | R | HR | HR | D.33 | Hide internal details, expose only necessary |
| **Structured Methodology** | R | HR | **M** | D.52 | Systematic interface design process |
| **Defensive Programming** | - | HR | HR | D.14 | Validate all interface inputs |
| **Error Detection & Diagnosis** | - | R | HR | D.26 | Detect interface errors at runtime |

**Key for SIL 3-4**:
- **M** = Mandatory
- **HR** = Highly Recommended
- **R** = Recommended

---

## Workflow Overview

```
┌─────────────────────────────────────────────────────────────────┐
│ Phase 1: Interface Identification                               │
│ → Identify all interfaces from architecture                     │
│ → Classify interface types                                      │
│ → Extract interface requirements                                │
└─────────────────────────────────────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────────┐
│ Phase 2: Interface Design                                       │
│ → Define data structures (C structs, enums, typedefs)          │
│ → Define function prototypes                                    │
│ → Define communication protocols                                │
│ → Design error handling                                         │
└─────────────────────────────────────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────────┐
│ Phase 3: Interface Documentation                                │
│ → Create interface specifications                               │
│ → Document preconditions/postconditions                         │
│ → Define usage examples                                         │
│ → Specify error conditions                                      │
└─────────────────────────────────────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────────┐
│ Phase 4: Interface Validation                                   │
│ → Validate against requirements (traceability)                  │
│ → Check MISRA C compliance                                      │
│ → Validate defensive programming                                │
│ → Verify information encapsulation                              │
└─────────────────────────────────────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────────┐
│ Phase 5: Review & Approval                                      │
│ → Peer review (PEER)                                            │
│ → Quality assurance review (QUA)                                │
│ → Independent verification (VER, SIL 3-4)                       │
│ → Project manager approval (PM)                                 │
└─────────────────────────────────────────────────────────────────┘
                           ↓
┌─────────────────────────────────────────────────────────────────┐
│ Phase 6: Baseline                                               │
│ → Create configuration baseline                                 │
│ → Transition to implementation phase                            │
└─────────────────────────────────────────────────────────────────┘
```

---

## Phase 1: Interface Identification

### Step 1.1: Load Architecture

**Action**: Load Software Architecture Specification to identify components and their interactions.

```bash
# Assumed: Workspace already set up
# Read architecture document
cat docs/Software-Architecture-Specification.md
```

**Extract**:
- List of architecture components (e.g., ARCH-COMP-001, ARCH-COMP-002, ...)
- Component relationships (calls, data flow, control flow)
- External system connections
- Hardware connections

**Example**:
```
ARCH-COMP-001: Train Control Module
  → Calls: ARCH-COMP-002 (Speed Monitor)
  → Receives data from: Hardware (Speed Sensor, GPIO)
  → Sends commands to: Hardware (Emergency Brake Actuator)

ARCH-COMP-002: Speed Monitor
  → Called by: ARCH-COMP-001
  → Reads: Hardware (Speed Sensor via ADC)
```

---

### Step 1.2: Classify Interface Types

**EN 50128 Interface Classification**:

#### 1. **Internal Interfaces** (Software-to-Software within same system)
- **Function calls** between modules
- **Data structures** passed between modules
- **Shared memory** (if used - generally avoided in safety-critical)
- **Message passing** (queues, events)

**Example**:
```c
// Internal interface: Train Control → Speed Monitor
// Function: get_current_speed()
uint16_t get_current_speed(void);
```

#### 2. **Hardware Interfaces** (Software-to-Hardware)
- **Memory-mapped I/O** (GPIO, ADC, timers, etc.)
- **Interrupt handlers**
- **DMA transfers**
- **Hardware registers**

**Example**:
```c
// Hardware interface: Read speed sensor via ADC
#define ADC_SPEED_SENSOR_CHANNEL  (0x03)
#define ADC_DATA_REGISTER         ((volatile uint16_t*)0x40012000)

uint16_t read_speed_sensor_raw(void) {
    // Read ADC register (memory-mapped)
    return *ADC_DATA_REGISTER;
}
```

#### 3. **External Interfaces** (Software-to-External Systems)
- **Network protocols** (CAN, Ethernet, serial)
- **Inter-process communication** (IPC)
- **File system** (if used - rare in safety-critical)
- **Database** (if used - rare in safety-critical)

**Example**:
```c
// External interface: CAN bus communication
typedef struct {
    uint32_t id;          // CAN identifier
    uint8_t  data[8];     // CAN data (max 8 bytes)
    uint8_t  length;      // Data length
} can_message_t;

error_t can_send_message(const can_message_t* msg);
```

#### 4. **Human-Machine Interfaces** (HMI)
- **Display outputs**
- **Operator inputs** (buttons, switches, touchscreen)
- **Alarms and warnings**

**Example**:
```c
// HMI interface: Display current speed on LCD
void display_speed(uint16_t speed_kmh);

// HMI interface: Read emergency stop button
bool is_emergency_stop_pressed(void);
```

---

### Step 1.3: Extract Interface Requirements

**Action**: From Software Requirements Specification, extract all interface requirements.

**Grep for interface requirements**:
```bash
# Search for interface requirements in SRS
grep -E "INT-REQ-[0-9]+" docs/Software-Requirements-Specification.md
```

**Example Interface Requirements**:
```
INT-REQ-001: The Train Control Module SHALL interface with the Speed Monitor to obtain current train speed.
INT-REQ-002: The Speed Monitor SHALL read speed sensor data via ADC Channel 3 at 100 Hz sampling rate.
INT-REQ-003: The Train Control Module SHALL send emergency brake command via GPIO pin PB5.
INT-REQ-004: All hardware interfaces SHALL validate input data before use (defensive programming).
INT-REQ-005: All function interfaces SHALL return error codes for failure conditions.
```

**Traceability**: Use **Traceability Manager** to create requirements → interfaces matrix.

```bash
# Create traceability matrix (assumed Traceability Manager available)
traceability.py create --from requirements --to interfaces --project TrainControl
```

---

### Step 1.4: Create Interface Inventory

**Action**: Document all identified interfaces in a structured list.

**Interface Inventory Table**:

| Interface ID | Name | Type | Source Component | Target Component | Requirements | Priority |
|--------------|------|------|------------------|------------------|--------------|----------|
| INT-001 | get_current_speed | Internal | Train Control | Speed Monitor | INT-REQ-001 | HIGH |
| INT-002 | read_speed_sensor_raw | Hardware | Speed Monitor | ADC Hardware | INT-REQ-002 | HIGH |
| INT-003 | set_emergency_brake | Hardware | Train Control | GPIO Hardware | INT-REQ-003 | CRITICAL |
| INT-004 | can_send_message | External | Train Control | CAN Bus | INT-REQ-006 | MEDIUM |
| INT-005 | display_speed | HMI | Train Control | LCD Display | INT-REQ-007 | LOW |

**Document in Interface Specifications**:
```markdown
## 3. Interface Inventory

### 3.1 Internal Interfaces (Software-to-Software)
- **INT-001**: `get_current_speed()` - Train Control → Speed Monitor
- **INT-006**: `calculate_brake_force()` - Train Control → Brake Controller

### 3.2 Hardware Interfaces (Software-to-Hardware)
- **INT-002**: Speed Sensor ADC Read (ADC Channel 3)
- **INT-003**: Emergency Brake GPIO (Pin PB5)

### 3.3 External Interfaces (Software-to-External System)
- **INT-004**: CAN Bus Communication (Train Network)

### 3.4 Human-Machine Interfaces (HMI)
- **INT-005**: LCD Speed Display
- **INT-008**: Emergency Stop Button Input
```

---

## Phase 2: Interface Design

### Step 2.1: Define Data Structures

**C Data Structures for Interfaces**: Use MISRA C compliant types.

#### 2.1.1: Internal Interface Data Structures

**Example**: Speed data structure passed between components.

```c
// File: interfaces/speed_interface.h

#ifndef SPEED_INTERFACE_H
#define SPEED_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>

// Speed data structure (internal interface)
typedef struct {
    uint16_t speed_kmh;        // Speed in km/h (0-400)
    uint16_t speed_raw;        // Raw ADC value (0-4095)
    bool     valid;            // Data validity flag
    uint32_t timestamp_ms;     // Timestamp in milliseconds
    uint8_t  sensor_status;    // Sensor health status (0=OK, >0=error)
} speed_data_t;

#endif // SPEED_INTERFACE_H
```

**MISRA C Compliance**:
- ✅ Fixed-width types (`uint16_t`, not `unsigned int`)
- ✅ Boolean type (`bool`, not `int`)
- ✅ Struct typedef with `_t` suffix
- ✅ Include guards

**Defensive Programming**:
- `valid` flag to indicate if data is trustworthy
- `sensor_status` for error detection
- `timestamp_ms` for detecting stale data

---

#### 2.1.2: Hardware Interface Data Structures

**Example**: GPIO interface for emergency brake.

```c
// File: interfaces/gpio_interface.h

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>

// GPIO pin definition (hardware interface)
typedef struct {
    volatile uint32_t* port;   // GPIO port base address
    uint8_t            pin;    // Pin number (0-15)
    bool               active_high; // true=active high, false=active low
} gpio_pin_t;

// GPIO state enumeration
typedef enum {
    GPIO_STATE_LOW  = 0,
    GPIO_STATE_HIGH = 1,
    GPIO_STATE_ERROR = 0xFF
} gpio_state_t;

#endif // GPIO_INTERFACE_H
```

**Hardware Abstraction**: Encapsulate hardware details in struct.

---

#### 2.1.3: External Interface Data Structures

**Example**: CAN bus message.

```c
// File: interfaces/can_interface.h

#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>

// CAN message structure (external interface)
typedef struct {
    uint32_t id;               // CAN identifier (11-bit or 29-bit)
    uint8_t  data[8];          // CAN data payload (max 8 bytes)
    uint8_t  length;           // Data length (0-8)
    bool     extended_id;      // true=29-bit ID, false=11-bit ID
    uint32_t timestamp_ms;     // Message timestamp
} can_message_t;

// CAN error codes
typedef enum {
    CAN_OK              = 0,
    CAN_ERR_TIMEOUT     = 1,
    CAN_ERR_BUS_OFF     = 2,
    CAN_ERR_INVALID_ID  = 3,
    CAN_ERR_BUFFER_FULL = 4
} can_error_t;

#endif // CAN_INTERFACE_H
```

**Error Handling**: Explicit error enumeration.

---

### Step 2.2: Define Function Prototypes

**Function Interface Design Principles** (EN 50128 + MISRA C):

1. **Return error codes** (not `void` for operations that can fail)
2. **Use `const` for input-only parameters**
3. **Use pointers for output parameters** (with NULL checks)
4. **Document preconditions and postconditions**
5. **Bounded execution time** (no recursion, no dynamic allocation)

---

#### 2.2.1: Internal Interface Functions

**Example**: Speed Monitor interface.

```c
// File: interfaces/speed_monitor_interface.h

#ifndef SPEED_MONITOR_INTERFACE_H
#define SPEED_MONITOR_INTERFACE_H

#include "speed_interface.h"
#include "error_codes.h"

/**
 * @brief Get current train speed
 * 
 * @param[out] speed  Pointer to speed data structure (output)
 * 
 * @return error_t
 *   - SUCCESS: Speed data retrieved successfully
 *   - ERR_NULL_POINTER: speed is NULL
 *   - ERR_SENSOR_FAULT: Speed sensor malfunction
 *   - ERR_STALE_DATA: Data older than 100ms (timeout)
 * 
 * @pre  Speed Monitor module initialized
 * @post speed->valid indicates if data is trustworthy
 * 
 * @note This function SHALL be called at least every 50ms
 * @note Execution time: <500 microseconds (worst case)
 */
error_t get_current_speed(speed_data_t* speed);

/**
 * @brief Initialize Speed Monitor module
 * 
 * @return error_t
 *   - SUCCESS: Initialization complete
 *   - ERR_ADC_INIT_FAILED: ADC hardware initialization failed
 * 
 * @pre  None
 * @post Speed Monitor ready for use
 * 
 * @note Must be called once at system startup before get_current_speed()
 */
error_t speed_monitor_init(void);

#endif // SPEED_MONITOR_INTERFACE_H
```

**Documentation Requirements** (EN 50128 SIL 3-4):
- ✅ `@brief` - Short description
- ✅ `@param` - All parameters documented (input/output direction)
- ✅ `@return` - All possible return values
- ✅ `@pre` - Preconditions (what must be true before call)
- ✅ `@post` - Postconditions (what will be true after call)
- ✅ `@note` - Additional constraints (timing, frequency, etc.)

---

#### 2.2.2: Hardware Interface Functions

**Example**: GPIO interface for emergency brake.

```c
// File: interfaces/gpio_interface.h (continued)

/**
 * @brief Set emergency brake GPIO pin
 * 
 * @param[in] state  Desired GPIO state (GPIO_STATE_LOW or GPIO_STATE_HIGH)
 * 
 * @return error_t
 *   - SUCCESS: GPIO set successfully
 *   - ERR_INVALID_PARAM: state is invalid
 *   - ERR_GPIO_FAULT: Hardware fault detected
 * 
 * @pre  GPIO module initialized
 * @post GPIO pin reflects requested state
 * 
 * @note Safety-critical: Failure triggers system shutdown
 * @note Execution time: <10 microseconds (worst case)
 */
error_t gpio_set_emergency_brake(gpio_state_t state);

/**
 * @brief Read emergency stop button GPIO pin (HMI interface)
 * 
 * @param[out] pressed  Pointer to boolean (true=pressed, false=not pressed)
 * 
 * @return error_t
 *   - SUCCESS: Button state read successfully
 *   - ERR_NULL_POINTER: pressed is NULL
 *   - ERR_GPIO_FAULT: Hardware fault detected
 * 
 * @pre  GPIO module initialized
 * @post *pressed contains button state
 * 
 * @note This function SHALL be called every 10ms (debouncing required externally)
 */
error_t gpio_read_emergency_stop_button(bool* pressed);
```

**Hardware Interface Defensive Programming**:
- Always check for hardware faults
- Return error codes (never assume hardware works)
- Document worst-case execution time (WCET)

---

#### 2.2.3: External Interface Functions

**Example**: CAN bus interface.

```c
// File: interfaces/can_interface.h (continued)

/**
 * @brief Send CAN message
 * 
 * @param[in] msg  Pointer to CAN message structure
 * 
 * @return can_error_t
 *   - CAN_OK: Message sent successfully
 *   - CAN_ERR_TIMEOUT: Timeout waiting for TX buffer
 *   - CAN_ERR_BUS_OFF: CAN bus off (too many errors)
 *   - CAN_ERR_INVALID_ID: Invalid CAN ID
 *   - CAN_ERR_BUFFER_FULL: Transmit buffer full
 * 
 * @pre  CAN module initialized
 * @pre  msg != NULL
 * @pre  msg->length <= 8
 * @post Message queued for transmission (not guaranteed delivered)
 * 
 * @note Non-blocking: Returns immediately if buffer full
 * @note Execution time: <1 millisecond (worst case)
 */
can_error_t can_send_message(const can_message_t* msg);

/**
 * @brief Receive CAN message (blocking with timeout)
 * 
 * @param[out] msg      Pointer to CAN message structure (output)
 * @param[in]  timeout  Timeout in milliseconds (0 = no wait)
 * 
 * @return can_error_t
 *   - CAN_OK: Message received
 *   - CAN_ERR_TIMEOUT: No message received within timeout
 *   - CAN_ERR_BUS_OFF: CAN bus off
 * 
 * @pre  CAN module initialized
 * @pre  msg != NULL
 * @post If CAN_OK, msg contains received message
 * 
 * @note Blocking: Waits up to timeout milliseconds
 * @note If timeout=0, returns immediately (non-blocking)
 */
can_error_t can_receive_message(can_message_t* msg, uint32_t timeout_ms);
```

**External Interface Considerations**:
- Network interfaces inherently unreliable (timeouts, errors)
- Always handle timeout/failure gracefully
- Non-blocking or bounded blocking time

---

### Step 2.3: Define Communication Protocols

For complex interfaces (especially external interfaces), define **communication protocols**.

**Example**: CAN bus protocol for speed broadcast.

```c
// File: interfaces/can_protocol.h

#ifndef CAN_PROTOCOL_H
#define CAN_PROTOCOL_H

#include "can_interface.h"

// CAN message IDs (defined in system specification)
#define CAN_ID_SPEED_BROADCAST      (0x100)
#define CAN_ID_BRAKE_COMMAND        (0x101)
#define CAN_ID_HEARTBEAT            (0x102)

// CAN message formats (byte layouts)

/**
 * Speed Broadcast Message (ID: 0x100)
 * Byte 0-1: Speed in km/h (uint16_t, big-endian)
 * Byte 2:   Sensor status (uint8_t)
 * Byte 3-6: Timestamp in ms (uint32_t, big-endian)
 * Byte 7:   Checksum (XOR of bytes 0-6)
 */
typedef struct {
    uint16_t speed_kmh;
    uint8_t  sensor_status;
    uint32_t timestamp_ms;
    uint8_t  checksum;
} can_speed_broadcast_t;

/**
 * @brief Pack speed broadcast message into CAN message
 */
error_t can_pack_speed_broadcast(can_message_t* msg, const can_speed_broadcast_t* data);

/**
 * @brief Unpack CAN message into speed broadcast structure
 */
error_t can_unpack_speed_broadcast(const can_message_t* msg, can_speed_broadcast_t* data);

#endif // CAN_PROTOCOL_H
```

**Protocol Design**:
- Define message IDs
- Define byte layouts (endianness, data types)
- Include checksums for error detection
- Provide pack/unpack functions

---

### Step 2.4: Design Error Handling

**Defensive Programming for Interfaces** (EN 50128 Table A.3, Technique 3):

#### 2.4.1: Input Validation

**Always validate interface inputs**:

```c
error_t get_current_speed(speed_data_t* speed) {
    // Input validation (defensive programming)
    if (speed == NULL) {
        return ERR_NULL_POINTER;
    }
    
    // Check module initialized
    if (!speed_monitor_initialized) {
        return ERR_NOT_INITIALIZED;
    }
    
    // Read speed from hardware
    uint16_t raw = read_speed_sensor_raw();
    
    // Validate raw data (range check)
    if (raw > ADC_MAX_VALUE) {
        speed->valid = false;
        return ERR_SENSOR_FAULT;
    }
    
    // Convert and populate structure
    speed->speed_raw = raw;
    speed->speed_kmh = (raw * SPEED_SCALE_FACTOR) / 1000;
    speed->valid = true;
    speed->timestamp_ms = get_system_time_ms();
    speed->sensor_status = 0; // OK
    
    return SUCCESS;
}
```

**Validation Checklist**:
- ✅ NULL pointer checks
- ✅ Range checks (bounds validation)
- ✅ State checks (module initialized?)
- ✅ Hardware fault detection

---

#### 2.4.2: Error Propagation

**Error codes SHALL be propagated, not ignored**:

```c
// CORRECT: Check return value and propagate error
error_t train_control_update(void) {
    speed_data_t speed;
    error_t err;
    
    // Call interface function
    err = get_current_speed(&speed);
    if (err != SUCCESS) {
        // Log error
        log_error("Failed to get speed: %d", err);
        // Propagate error
        return err;
    }
    
    // Use speed data only if valid
    if (!speed.valid) {
        log_warning("Speed data invalid");
        return ERR_INVALID_DATA;
    }
    
    // Check for stale data (older than 100ms)
    uint32_t now = get_system_time_ms();
    if ((now - speed.timestamp_ms) > 100) {
        log_warning("Speed data stale: age=%d ms", now - speed.timestamp_ms);
        return ERR_STALE_DATA;
    }
    
    // Speed data OK, proceed
    // ...
    return SUCCESS;
}
```

**Error Handling Best Practices**:
- ✅ Always check return values (MISRA C Rule 17.7)
- ✅ Log errors for diagnostics
- ✅ Propagate errors to caller
- ✅ Validate data freshness (timestamps)
- ✅ Check validity flags

---

#### 2.4.3: Error Detection & Diagnosis

**Hardware interfaces require error detection** (EN 50128 Table A.3, Technique 10):

```c
// Hardware interface with error detection
error_t read_speed_sensor_raw(uint16_t* raw) {
    if (raw == NULL) {
        return ERR_NULL_POINTER;
    }
    
    // Read ADC register
    volatile uint16_t* adc_data = ADC_DATA_REGISTER;
    uint16_t value = *adc_data;
    
    // Error detection: Check ADC status register
    volatile uint32_t* adc_status = ADC_STATUS_REGISTER;
    uint32_t status = *adc_status;
    
    if (status & ADC_STATUS_OVERRUN) {
        log_error("ADC overrun detected");
        return ERR_ADC_OVERRUN;
    }
    
    if (status & ADC_STATUS_TIMEOUT) {
        log_error("ADC timeout detected");
        return ERR_ADC_TIMEOUT;
    }
    
    // Plausibility check (speed sensor can't exceed physical limits)
    if (value > ADC_SPEED_SENSOR_MAX_VALID) {
        log_error("Speed sensor value implausible: %d", value);
        return ERR_SENSOR_FAULT;
    }
    
    *raw = value;
    return SUCCESS;
}
```

**Error Detection Techniques**:
- ✅ Check hardware status registers
- ✅ Plausibility checks (physical limits)
- ✅ Redundancy (if available - multiple sensors)
- ✅ Watchdog timers for interface timeouts

---

## Phase 3: Interface Documentation

### Step 3.1: Create Interface Specification Document

**Use Traceability Manager to generate interface inventory from architecture**:

```bash
# Extract interfaces from architecture components
traceability.py extract --document docs/Software-Architecture-Specification.md \
  --type architecture_to_interfaces
```

**Document Template** (follow EN 50128 structure):

```markdown
# Software Interface Specifications

**Document ID**: DOC-INT-SPEC-2026-001  
**Project**: Train Control System  
**SIL Level**: 3  
**Status**: Draft  
**Author**: Jane Doe (DES)  
**Date**: 2026-03-13

---

## 1. Introduction

### 1.1 Purpose
This document specifies all software interfaces for the Train Control System, including:
- Internal interfaces (software-to-software)
- Hardware interfaces (software-to-hardware)
- External interfaces (software-to-external systems)
- Human-machine interfaces (HMI)

### 1.2 Scope
Covers interfaces for:
- ARCH-COMP-001: Train Control Module
- ARCH-COMP-002: Speed Monitor
- ARCH-COMP-003: Brake Controller
- (etc.)

### 1.3 References
- Software Architecture Specification (DOC-SAS-2026-001)
- Software Requirements Specification (DOC-SRS-2026-001)
- MISRA C:2012 Guidelines
- Hardware Specification (provided by hardware team)

---

## 2. Interface Design Principles

### 2.1 General Principles
1. All interfaces SHALL use fixed-width types (uint8_t, uint16_t, etc.)
2. All functions that can fail SHALL return error codes
3. All pointer parameters SHALL be validated for NULL before use
4. All hardware interfaces SHALL detect and report errors
5. All external interfaces SHALL handle timeouts and failures gracefully

### 2.2 Defensive Programming (EN 50128 Table A.3, Technique 3)
- Input validation at all interface boundaries
- Range checks for all numeric inputs
- NULL pointer checks for all pointer parameters
- State validation (module initialized, hardware ready, etc.)

### 2.3 Information Encapsulation (EN 50128 Table A.3, Technique 9)
- Hide internal implementation details
- Expose only necessary interfaces
- Use opaque types where appropriate

---

## 3. Interface Inventory

### 3.1 Internal Interfaces (Software-to-Software)

| Interface ID | Name | Source | Target | Requirements | Priority |
|--------------|------|--------|--------|--------------|----------|
| INT-001 | get_current_speed | Train Control | Speed Monitor | INT-REQ-001 | HIGH |
| INT-006 | calculate_brake_force | Train Control | Brake Controller | INT-REQ-010 | CRITICAL |

### 3.2 Hardware Interfaces (Software-to-Hardware)

| Interface ID | Name | Hardware | Direction | Requirements | Priority |
|--------------|------|----------|-----------|--------------|----------|
| INT-002 | Speed Sensor ADC | ADC Ch3 | Input | INT-REQ-002 | HIGH |
| INT-003 | Emergency Brake GPIO | GPIO PB5 | Output | INT-REQ-003 | CRITICAL |

### 3.3 External Interfaces (Software-to-External System)

| Interface ID | Name | Protocol | Requirements | Priority |
|--------------|------|----------|--------------|----------|
| INT-004 | CAN Speed Broadcast | CAN 2.0B | INT-REQ-006 | MEDIUM |

### 3.4 Human-Machine Interfaces (HMI)

| Interface ID | Name | Device | Direction | Requirements | Priority |
|--------------|------|--------|-----------|--------------|----------|
| INT-005 | Speed Display | LCD | Output | INT-REQ-007 | LOW |
| INT-008 | Emergency Stop Button | GPIO | Input | INT-REQ-009 | CRITICAL |

---

## 4. Internal Interface Specifications

### 4.1 INT-001: get_current_speed

**Purpose**: Retrieve current train speed from Speed Monitor module.

**Function Prototype**:
```c
error_t get_current_speed(speed_data_t* speed);
```

**Parameters**:
- `speed` [out]: Pointer to speed data structure (must not be NULL)

**Return Values**:
- `SUCCESS`: Speed data retrieved successfully
- `ERR_NULL_POINTER`: speed is NULL
- `ERR_SENSOR_FAULT`: Speed sensor malfunction
- `ERR_STALE_DATA`: Data older than 100ms

**Preconditions**:
- Speed Monitor module initialized via `speed_monitor_init()`

**Postconditions**:
- `speed->valid` indicates data trustworthiness
- If `SUCCESS`, speed data is fresh (<100ms old)

**Usage Example**:
```c
speed_data_t speed;
error_t err = get_current_speed(&speed);

if (err == SUCCESS && speed.valid) {
    printf("Speed: %d km/h\n", speed.speed_kmh);
} else {
    log_error("Failed to get speed: %d", err);
}
```

**Error Handling**:
- Caller MUST check return value (MISRA C Rule 17.7)
- Caller MUST check `speed.valid` before using data
- If error, caller should use safe default (e.g., assume stopped)

**Timing**:
- Worst-case execution time (WCET): 500 microseconds
- Recommended call frequency: 20 Hz (every 50ms)

**Traceability**:
- Satisfies: INT-REQ-001, SW-REQ-015
- Tests: TEST-INT-001

---

## 5. Hardware Interface Specifications

### 5.1 INT-002: Speed Sensor ADC

**Purpose**: Read raw speed sensor value from ADC hardware.

**Hardware Details**:
- ADC Channel: 3
- Resolution: 12-bit (0-4095)
- Reference Voltage: 3.3V
- Sampling Rate: 100 Hz
- Input Range: 0-3.3V (corresponds to 0-400 km/h)

**Function Prototype**:
```c
error_t read_speed_sensor_raw(uint16_t* raw);
```

**Parameters**:
- `raw` [out]: Pointer to receive raw ADC value (0-4095)

**Return Values**:
- `SUCCESS`: ADC value read successfully
- `ERR_NULL_POINTER`: raw is NULL
- `ERR_ADC_OVERRUN`: ADC data overrun (sampling too slow)
- `ERR_ADC_TIMEOUT`: ADC conversion timeout
- `ERR_SENSOR_FAULT`: Sensor value implausible

**Memory Map**:
```c
#define ADC_BASE_ADDRESS       (0x40012000)
#define ADC_DATA_REGISTER      ((volatile uint16_t*)(ADC_BASE_ADDRESS + 0x00))
#define ADC_STATUS_REGISTER    ((volatile uint32_t*)(ADC_BASE_ADDRESS + 0x04))
#define ADC_CONTROL_REGISTER   ((volatile uint32_t*)(ADC_BASE_ADDRESS + 0x08))

#define ADC_STATUS_OVERRUN     (0x00000001)
#define ADC_STATUS_TIMEOUT     (0x00000002)
```

**Calibration**:
- Raw value 0 = 0 km/h
- Raw value 4095 = 400 km/h
- Scale factor: (400 * 1000) / 4095 = 97.7 (use integer math)

**Error Detection**:
- Check ADC_STATUS_REGISTER for overrun/timeout
- Plausibility check: raw value must be ≤ 4095
- Rate-of-change check: speed can't change >50 km/h per 100ms

**Defensive Programming**:
```c
error_t read_speed_sensor_raw(uint16_t* raw) {
    if (raw == NULL) {
        return ERR_NULL_POINTER;
    }
    
    volatile uint16_t* adc_data = ADC_DATA_REGISTER;
    volatile uint32_t* adc_status = ADC_STATUS_REGISTER;
    
    // Check for hardware errors
    uint32_t status = *adc_status;
    if (status & ADC_STATUS_OVERRUN) {
        return ERR_ADC_OVERRUN;
    }
    if (status & ADC_STATUS_TIMEOUT) {
        return ERR_ADC_TIMEOUT;
    }
    
    // Read ADC value
    uint16_t value = *adc_data;
    
    // Plausibility check
    if (value > 4095) {
        return ERR_SENSOR_FAULT;
    }
    
    // Rate-of-change check (against previous value)
    static uint16_t previous_value = 0;
    int32_t delta = (int32_t)value - (int32_t)previous_value;
    if (abs(delta) > 500) { // Max change per 10ms
        log_warning("Sudden speed change: delta=%d", delta);
        // Don't fail, but log warning
    }
    previous_value = value;
    
    *raw = value;
    return SUCCESS;
}
```

**Traceability**:
- Satisfies: INT-REQ-002, SW-REQ-016, SAF-REQ-005
- Tests: TEST-INT-002, TEST-HW-ADC-001

---

## 6. External Interface Specifications

### 6.1 INT-004: CAN Speed Broadcast

**Purpose**: Broadcast train speed to other systems via CAN bus.

**Protocol Details**:
- CAN Standard: CAN 2.0B (29-bit extended ID)
- CAN ID: 0x100
- Baud Rate: 500 kbps
- Broadcast Rate: 10 Hz (every 100ms)
- Priority: Medium

**Message Format**:

| Byte | Field | Type | Description | Range |
|------|-------|------|-------------|-------|
| 0-1  | Speed | uint16_t | Speed in km/h (big-endian) | 0-400 |
| 2    | Status | uint8_t | Sensor status (0=OK) | 0-255 |
| 3-6  | Timestamp | uint32_t | Time in ms (big-endian) | 0-2^32 |
| 7    | Checksum | uint8_t | XOR of bytes 0-6 | 0-255 |

**Function Prototype**:
```c
error_t can_broadcast_speed(const speed_data_t* speed);
```

**Implementation**:
```c
error_t can_broadcast_speed(const speed_data_t* speed) {
    if (speed == NULL) {
        return ERR_NULL_POINTER;
    }
    
    // Validate speed data
    if (!speed->valid) {
        return ERR_INVALID_DATA;
    }
    
    // Pack CAN message
    can_message_t msg;
    msg.id = CAN_ID_SPEED_BROADCAST;
    msg.extended_id = false;
    msg.length = 8;
    
    // Byte 0-1: Speed (big-endian)
    msg.data[0] = (uint8_t)(speed->speed_kmh >> 8);
    msg.data[1] = (uint8_t)(speed->speed_kmh & 0xFF);
    
    // Byte 2: Status
    msg.data[2] = speed->sensor_status;
    
    // Byte 3-6: Timestamp (big-endian)
    msg.data[3] = (uint8_t)(speed->timestamp_ms >> 24);
    msg.data[4] = (uint8_t)(speed->timestamp_ms >> 16);
    msg.data[5] = (uint8_t)(speed->timestamp_ms >> 8);
    msg.data[6] = (uint8_t)(speed->timestamp_ms & 0xFF);
    
    // Byte 7: Checksum (XOR of bytes 0-6)
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < 7; i++) {
        checksum ^= msg.data[i];
    }
    msg.data[7] = checksum;
    
    // Send message
    can_error_t err = can_send_message(&msg);
    if (err != CAN_OK) {
        log_error("CAN send failed: %d", err);
        return ERR_CAN_SEND_FAILED;
    }
    
    return SUCCESS;
}
```

**Error Handling**:
- If CAN send fails, log error but continue (non-critical)
- Retry not implemented (broadcast nature - next message in 100ms)
- CAN bus errors handled by lower-level driver

**Traceability**:
- Satisfies: INT-REQ-006, SW-REQ-020
- Tests: TEST-INT-004, TEST-CAN-001

---

## 7. Interface Traceability Matrix

**Use Traceability Manager to validate interface coverage**:

```bash
# Validate that all interface requirements have interface specifications
traceability.py validate --matrix requirements_to_interfaces --sil 3
```

### 7.1 Requirements → Interfaces

| Requirement ID | Requirement Description | Interface ID | Interface Name | Status |
|----------------|------------------------|--------------|----------------|--------|
| INT-REQ-001 | Train Control → Speed Monitor interface | INT-001 | get_current_speed | ✅ |
| INT-REQ-002 | Speed sensor ADC interface | INT-002 | read_speed_sensor_raw | ✅ |
| INT-REQ-003 | Emergency brake GPIO interface | INT-003 | gpio_set_emergency_brake | ✅ |
| INT-REQ-004 | Input validation (defensive) | ALL | (Applied to all interfaces) | ✅ |
| INT-REQ-005 | Error code returns | ALL | (Applied to all interfaces) | ✅ |
| INT-REQ-006 | CAN speed broadcast | INT-004 | can_broadcast_speed | ✅ |

**Coverage**: 100% (6/6 interface requirements satisfied)

---

## 8. Interface Validation

### 8.1 MISRA C Compliance

All interfaces SHALL comply with MISRA C:2012:
- ✅ Fixed-width types (Rule 4.6)
- ✅ Return values checked (Rule 17.7)
- ✅ Pointer parameters validated for NULL (Rule 1.3, Directive 4.1)
- ✅ No recursion (Rule 17.2)
- ✅ No dynamic allocation (Rule 21.3)

**Validation**: Run MISRA C checker on interface header files.

```bash
# Check MISRA C compliance (assumed tool available)
cppcheck --addon=misra interfaces/*.h
```

---

### 8.2 Defensive Programming Validation

All interfaces SHALL implement defensive programming:
- ✅ Input validation (NULL checks, range checks)
- ✅ State validation (module initialized?)
- ✅ Error detection (hardware faults, plausibility checks)
- ✅ Error propagation (return error codes, log errors)

**Validation Checklist**:

| Interface | NULL Check | Range Check | State Check | Error Detect | Error Return |
|-----------|------------|-------------|-------------|--------------|--------------|
| INT-001 | ✅ | ✅ | ✅ | ✅ | ✅ |
| INT-002 | ✅ | ✅ | ✅ | ✅ | ✅ |
| INT-003 | ✅ | ✅ | ✅ | ✅ | ✅ |
| INT-004 | ✅ | ✅ | ✅ | ✅ | ✅ |

---

### 8.3 Information Encapsulation Validation

All interfaces SHALL hide implementation details:
- ✅ Internal data structures not exposed (use opaque types if needed)
- ✅ Hardware details abstracted (register addresses in .c file, not .h)
- ✅ Only necessary functions exposed (helper functions static)

**Example**: Hardware register addresses defined in .c file only:

```c
// speed_monitor.c (implementation file - NOT exposed in header)
#define ADC_BASE_ADDRESS       (0x40012000)
#define ADC_DATA_REGISTER      ((volatile uint16_t*)(ADC_BASE_ADDRESS + 0x00))
```

---

## 9. Interface Testing

### 9.1 Interface Test Strategy

Each interface SHALL have dedicated tests:

1. **Unit Tests**: Test interface functions in isolation
   - Mock hardware (for hardware interfaces)
   - Test all error paths
   - Test boundary conditions

2. **Integration Tests**: Test interfaces between real components
   - Component A → Component B integration
   - Hardware integration (on target platform)
   - External system integration (CAN bus, etc.)

3. **Fault Injection**: Test error handling
   - Inject hardware faults (ADC errors, timeouts)
   - Inject invalid inputs (NULL pointers, out-of-range values)
   - Verify defensive programming works

---

### 9.2 Interface Test Specifications

**Create test specifications for each interface**:

```markdown
### TEST-INT-001: get_current_speed Interface Test

**Objective**: Verify get_current_speed interface works correctly.

**Test Cases**:

1. **TC-INT-001-01**: Normal operation
   - Pre: Speed Monitor initialized, sensor working
   - Action: Call get_current_speed(&speed)
   - Expected: Returns SUCCESS, speed.valid=true, speed.speed_kmh valid

2. **TC-INT-001-02**: NULL pointer
   - Pre: Speed Monitor initialized
   - Action: Call get_current_speed(NULL)
   - Expected: Returns ERR_NULL_POINTER

3. **TC-INT-001-03**: Not initialized
   - Pre: Speed Monitor NOT initialized
   - Action: Call get_current_speed(&speed)
   - Expected: Returns ERR_NOT_INITIALIZED

4. **TC-INT-001-04**: Sensor fault
   - Pre: Speed Monitor initialized, sensor fault injected
   - Action: Call get_current_speed(&speed)
   - Expected: Returns ERR_SENSOR_FAULT, speed.valid=false

5. **TC-INT-001-05**: Stale data
   - Pre: Speed Monitor initialized, no sensor updates for >100ms
   - Action: Call get_current_speed(&speed)
   - Expected: Returns ERR_STALE_DATA
```

**Test Coverage Requirements** (EN 50128 SIL 3):
- ✅ Statement coverage: 100%
- ✅ Branch coverage: 100%
- ✅ Condition coverage: 100%
- ✅ All error paths tested

---

## 10. Interface Review Checklist

Before finalizing interface specifications, verify:

### 10.1 Completeness
- [ ] All architecture components have defined interfaces
- [ ] All interface requirements traced to interface specifications
- [ ] All interface functions documented (parameters, returns, pre/post)
- [ ] All error conditions defined
- [ ] All hardware interfaces have memory maps

### 10.2 Correctness
- [ ] Interface functions have correct signatures
- [ ] Error codes cover all failure modes
- [ ] Data structures correctly sized
- [ ] Hardware addresses match hardware specification
- [ ] Communication protocols match external system specs

### 10.3 EN 50128 Compliance
- [ ] Defensive programming applied (Table A.3, Technique 3)
- [ ] Information encapsulation applied (Table A.3, Technique 9)
- [ ] Fully defined interfaces (Table A.3, Technique 7)
- [ ] Error detection for hardware (Table A.3, Technique 10)
- [ ] MISRA C compliance (Table A.12)

### 10.4 Testability
- [ ] All interfaces testable (can be called from test harness)
- [ ] Error injection possible (for fault testing)
- [ ] Hardware interfaces mockable (for unit testing)
- [ ] Test specifications created

---

## Phase 4: Interface Validation

### Step 4.1: Traceability Validation

**Use Traceability Manager to validate interface coverage**:

```bash
# Validate requirements → interfaces traceability
traceability.py validate --matrix requirements_to_interfaces --sil 3

# Expected output:
# ✅ Coverage: 100% (6/6 interface requirements traced)
# ✅ No orphan requirements
# ✅ No untested interfaces
```

**Generate traceability report**:

```bash
# Generate report for embedding in document
traceability.py report --from requirements --to interfaces --format markdown \
  > /tmp/interface_traceability.md

# Copy report into Section 7 of Interface Specifications
```

---

### Step 4.2: MISRA C Compliance Check

**Run static analysis on interface headers**:

```bash
# MISRA C compliance check (assumed tool available)
cppcheck --enable=all --addon=misra interfaces/*.h 2>&1 | tee misra_report.txt

# Check for violations
if grep -q "MISRA" misra_report.txt; then
    echo "❌ MISRA C violations found - must fix before approval"
else
    echo "✅ MISRA C compliant"
fi
```

**Common MISRA C Issues in Interfaces**:
- Rule 4.6: Use fixed-width types (uint8_t, not unsigned char)
- Rule 8.2: Function prototypes must include parameter names
- Rule 8.3: Function definitions must match prototypes
- Rule 17.7: Return values must be checked (enforced by documentation)

---

### Step 4.3: Defensive Programming Validation

**Manual review checklist** (automated tools can't fully validate):

```markdown
### Defensive Programming Review

For each interface function, verify:

1. **Input Validation**
   - [ ] All pointer parameters checked for NULL
   - [ ] All numeric parameters range-checked
   - [ ] All array/buffer parameters have length validation

2. **State Validation**
   - [ ] Module initialization checked before use
   - [ ] Hardware readiness checked (for hardware interfaces)

3. **Error Detection**
   - [ ] Hardware status registers checked (for hardware interfaces)
   - [ ] Plausibility checks for sensor data
   - [ ] Timeout detection for external interfaces

4. **Error Propagation**
   - [ ] All error conditions return error codes (not void)
   - [ ] Errors logged for diagnostics
   - [ ] Error codes documented

5. **Resource Safety**
   - [ ] No memory leaks (static allocation only)
   - [ ] No buffer overflows (bounds checking)
   - [ ] No race conditions (if multi-threaded - rare in safety-critical)
```

---

### Step 4.4: Information Encapsulation Validation

**Check that internal details are hidden**:

```bash
# Check that hardware register addresses are NOT in header files
if grep -r "0x[0-9A-Fa-f]*000" interfaces/*.h; then
    echo "⚠️ WARNING: Hardware addresses found in header files"
    echo "Move to .c implementation files for encapsulation"
fi

# Check that internal helper functions are static (not in headers)
if grep -E "static.*\(" interfaces/*.h; then
    echo "⚠️ WARNING: Static functions should not be in headers"
fi
```

---

## Phase 5: Review & Approval

### Step 5.1: Submit for Review

**Use Workflow Manager to submit Interface Specifications for review**:

```bash
# Submit document for review workflow (assumed Workflow Manager available)
workspace.py workflow submit Software-Interface-Specifications --for-review \
  --message "Interface specifications complete, ready for peer review"
```

**Workflow Manager routes to reviewers** based on SIL level:
- **SIL 3**: PEER → QUA → SAFETY_MGR → VER → VAL → PM (6 approvals)

---

### Step 5.2: Peer Review (PEER)

**Peer reviewer checklist**:

1. **Completeness**
   - [ ] All interfaces from architecture specification included
   - [ ] All interface requirements traced
   - [ ] All functions documented

2. **Correctness**
   - [ ] Function signatures correct
   - [ ] Data structures sized appropriately
   - [ ] Error handling complete

3. **Design Quality**
   - [ ] Interfaces follow design principles
   - [ ] Defensive programming applied
   - [ ] Information encapsulation maintained

4. **Testability**
   - [ ] Interfaces testable
   - [ ] Test specifications adequate

**Peer review command**:

```bash
# Peer reviewer approves
workspace.py workflow review Software-Interface-Specifications --role PEER \
  --approve --comment "Interfaces well-defined, defensive programming applied, traceability complete"
```

---

### Step 5.3: Quality Assurance Review (QUA)

**QUA reviewer checklist** (template compliance + quality):

1. **Document Template Compliance**
   - [ ] Document ID format correct (DOC-INT-SPEC-YYYY-NNN)
   - [ ] All mandatory sections present
   - [ ] Document Control table complete

2. **EN 50128 Compliance**
   - [ ] Table A.3 techniques applied (Defensive Programming, Information Encapsulation, etc.)
   - [ ] SIL-appropriate rigor
   - [ ] Traceability complete

3. **MISRA C Compliance**
   - [ ] Fixed-width types used
   - [ ] No prohibited constructs

4. **Quality Attributes**
   - [ ] Interfaces complete, correct, consistent
   - [ ] Defensive programming thorough
   - [ ] Error handling robust

**QUA review command**:

```bash
# QUA approves after checking template compliance and quality
workspace.py workflow review Software-Interface-Specifications --role QUA \
  --approve --comment "Template compliant, EN 50128 techniques applied, quality criteria met"
```

---

### Step 5.4: Independent Verification (VER, SIL 3-4)

**VER reviewer checklist** (independent technical review):

1. **Requirements Traceability**
   - [ ] All interface requirements traced to interfaces (100%)
   - [ ] Traceability matrix validated (use Traceability Manager)

2. **Technical Correctness**
   - [ ] Interface specifications technically sound
   - [ ] Hardware interfaces match hardware specification
   - [ ] External interfaces match external system specifications

3. **Safety Requirements**
   - [ ] Safety-critical interfaces identified
   - [ ] Defensive programming adequate for safety
   - [ ] Error detection for safety-critical interfaces

4. **Static Analysis**
   - [ ] MISRA C compliance verified
   - [ ] No static analysis warnings

**VER review command**:

```bash
# VER performs independent verification
workspace.py workflow review Software-Interface-Specifications --role VER \
  --approve --comment "Verification complete: traceability 100%, MISRA C compliant, safety requirements met"
```

**Note**: VER must be **independent** (EN 50128 Section 5.1.2.10) - not the same person as DES, IMP, or TST.

---

### Step 5.5: All Approvals Obtained

**Workflow Manager tracks approvals**:

```bash
# Check approval status
workspace.py workflow status Software-Interface-Specifications --approvals

# Output:
# ✅ PEER: Approved by Alice (2026-03-13)
# ✅ QUA: Approved by Bob (2026-03-14)
# ✅ SAFETY_MGR: Approved by Carol (2026-03-14)
# ✅ VER: Approved by David (2026-03-15)
# ⏳ VAL: Pending
# ⏳ PM: Pending
```

**After all approvals**:

```bash
# Mark as approved
workspace.py workflow approve Software-Interface-Specifications

# Output: Software-Interface-Specifications marked as APPROVED
```

---

## Phase 6: Baseline

### Step 6.1: Create Configuration Baseline

**After all Phase 3 (Architecture & Design) deliverables approved**, create baseline:

```bash
# Create baseline for Architecture & Design phase (includes Interface Specifications)
workspace.py workflow baseline --phase architecture --tag ARCH-BASELINE-v1.0.0 \
  --message "Architecture & Design phase complete, all deliverables approved"
```

**Baseline includes**:
- Software Architecture Specification (DOC-9)
- Software Design Specification (DOC-10)
- **Software Interface Specifications (DOC-11)** ← This document
- Architecture Verification Report (DOC-14)

**Workflow Manager**:
- ✅ Creates Git tag: `ARCH-BASELINE-v1.0.0`
- ✅ Generates baseline manifest with checksums
- ✅ Transitions all deliverables to **Baseline** status
- ✅ Updates LIFECYCLE_STATE.md

---

### Step 6.2: Phase Gate Check

**Before advancing to Phase 4 (Implementation)**, Lifecycle Coordinator runs gate check:

```bash
# Validate all prerequisites for Phase 4 (Implementation)
workspace.py workflow gate-check architecture --sil 3

# Checks:
# ✅ All architecture deliverables approved
# ✅ Baseline created
# ✅ Traceability complete (requirements → architecture → design → interfaces)
# ✅ QUA reviews passed
# ✅ Independent VER approval obtained
# Result: GATE CHECK PASSED ✅
```

**If gate check passes**, advance to Phase 4:

```bash
workspace.py workflow advance-phase --to implementation
```

---

## Integration with Other Workflows

### Integration with Architecture Design Workflow

**Interface design follows architecture design**:
1. Architecture defines components and relationships
2. Interface design defines how components communicate
3. Architecture workflow creates high-level interfaces
4. This workflow creates detailed interface specifications

**Workflow sequence**:
```
workflows/architecture-design.md (Phase 1-6)
    → Creates: Software Architecture Specification
    → Identifies: High-level component interfaces

workflows/interface-design.md (Phase 1-6)  ← YOU ARE HERE
    → Creates: Software Interface Specifications
    → Details: Function prototypes, data structures, protocols
```

---

### Integration with Software Design Workflow

**Interface specifications used by software design**:
1. Software design workflow uses interfaces to design component internals
2. Software design must conform to interface contracts
3. Software design cannot change interfaces without approval

**Workflow sequence**:
```
workflows/interface-design.md (Phase 1-6)
    → Creates: Software Interface Specifications
    → Defines: Function prototypes, data structures

workflows/software-design.md (Phase 1-6)
    → Uses: Interface Specifications
    → Designs: Internal implementation details
    → Creates: Software Design Specification
```

---

### Integration with Implementation Workflow

**Interface specifications used during implementation**:
1. Implementation must follow interface specifications exactly
2. Interface headers (.h files) created from specifications
3. Any deviations require Change Request (CR)

**Workflow sequence**:
```
workflows/interface-design.md (Phase 1-6)
    → Creates: Software Interface Specifications

(Implementation workflow - future skill: en50128-implementation)
    → Uses: Interface Specifications
    → Creates: Interface header files (.h)
    → Implements: Interface functions (.c)
```

---

## Tool Integration Summary

This workflow integrates with:

### Traceability Manager
```bash
# Create traceability matrices
traceability.py create --from requirements --to interfaces

# Validate traceability
traceability.py validate --matrix requirements_to_interfaces --sil 3

# Generate traceability report
traceability.py report --from requirements --to interfaces --format markdown
```

### Workflow Manager
```bash
# Submit for review
workspace.py workflow submit Software-Interface-Specifications --for-review

# Review and approve
workspace.py workflow review Software-Interface-Specifications --role VER --approve

# Create baseline
workspace.py workflow baseline --phase architecture --tag ARCH-BASELINE-v1.0.0

# Phase gate check
workspace.py workflow gate-check architecture --sil 3
```

---

## References

### EN 50128 Standard
- **Section 7.3**: Software Architecture and Design
- **Table A.3**: Software Architecture techniques
  - Technique 3: Defensive Programming (HR for SIL 3-4)
  - Technique 7: Fully Defined Interface (HR for SIL 3-4)
  - Technique 9: Information Encapsulation (HR for SIL 3-4)
  - Technique 10: Error Detection and Diagnosis (HR for SIL 3-4)
- **Table A.12**: Design and Coding Standards (M for SIL 3-4)
- **Annex C, Table C.1**: Document DOC-11 (Software Interface Specifications)

### MISRA C Guidelines
- **MISRA C:2012** - C coding standard for safety-critical systems
- **Rule 4.6**: Use fixed-width types
- **Rule 8.2**: Function prototypes shall include parameter names
- **Rule 17.7**: Return values shall be used

### Related Workflows
- `workflows/architecture-design.md` - Software Architecture Specification
- `workflows/software-design.md` - Software Design Specification
- `workflows/design-review.md` - Design review process

### Related Resources
- `resources/defensive-programming-patterns.md` - Defensive programming patterns
- `resources/misra-c-design-guidelines.md` - MISRA C design guidelines

### Related Templates
- `templates/Software-Interface-Specifications-template.md` - Interface Specifications template

---

**END OF WORKFLOW**
