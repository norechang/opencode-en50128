# Interfaces Directory

Hardware and software interfaces for EN 50128 railway systems.

## Purpose

Defines interfaces between:
- Hardware and software (HAL - Hardware Abstraction Layer)
- Software components
- External systems
- Communication protocols

## Interface Types

### 1. Hardware Abstraction Layer (HAL)

Abstract hardware-specific code:

```c
// hal_gpio.h - GPIO interface
#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>
#include "error_types.h"

typedef enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALTERNATE
} gpio_mode_t;

error_t hal_gpio_init(uint8_t pin, gpio_mode_t mode);
error_t hal_gpio_read(uint8_t pin, bool* state);
error_t hal_gpio_write(uint8_t pin, bool state);

#endif // HAL_GPIO_H
```

### 2. Component Interfaces

Define clear interfaces between components:

```c
// interface_door_control.h
#ifndef INTERFACE_DOOR_CONTROL_H
#define INTERFACE_DOOR_CONTROL_H

#include <stdint.h>
#include <stdbool.h>
#include "error_types.h"

typedef struct {
    bool door_closed_sensor;
    bool door_locked_sensor;
    uint16_t train_speed_kmh;
} door_control_input_t;

typedef struct {
    bool door_lock_command;
    bool door_open_command;
    bool door_close_command;
    bool safety_alarm;
} door_control_output_t;

// Interface functions
error_t door_control_process(
    const door_control_input_t* input,
    door_control_output_t* output
);

#endif // INTERFACE_DOOR_CONTROL_H
```

### 3. Communication Interfaces

For inter-system communication:

```c
// interface_comm.h
#ifndef INTERFACE_COMM_H
#define INTERFACE_COMM_H

#include <stdint.h>
#include "error_types.h"

#define COMM_MAX_PAYLOAD_SIZE 256U

typedef struct {
    uint8_t message_id;
    uint8_t sequence_number;
    uint16_t payload_length;
    uint8_t payload[COMM_MAX_PAYLOAD_SIZE];
    uint16_t checksum;
} comm_message_t;

error_t comm_send(const comm_message_t* message);
error_t comm_receive(comm_message_t* message, uint32_t timeout_ms);
error_t comm_validate_checksum(const comm_message_t* message);

#endif // INTERFACE_COMM_H
```

## Interface Design Principles

1. **Clear Ownership**: Each interface has one owner
2. **Minimal Coupling**: Minimize dependencies
3. **Defensive Design**: Validate all inputs
4. **Error Handling**: Always return error status
5. **Documentation**: Document assumptions and constraints

## Interface Documentation Template

```c
/**
 * Interface: [Name]
 * 
 * Purpose: [What this interface does]
 * 
 * Owner: [Component that implements this]
 * 
 * Clients: [Components that use this]
 * 
 * Thread Safety: [Thread-safe / Not thread-safe / Reentrant]
 * 
 * Constraints:
 * - [List any constraints]
 * - [Memory requirements]
 * - [Timing requirements]
 * 
 * Traceability: [REQ-xxx, DES-yyy]
 * 
 * SIL: [0-4]
 */
```

## Hardware Abstraction Guidelines

### Platform Independence

```c
// Bad: Platform-specific code in component
void control_door(void) {
    *((volatile uint32_t*)0x40020000) = 0x01;  // Direct register access
}

// Good: Use HAL
void control_door(void) {
    hal_gpio_write(DOOR_LOCK_PIN, true);
}
```

### Hardware Configuration

Keep hardware specifics in HAL:

```c
// hal_config.h
#define DOOR_SENSOR_PIN     GPIO_PIN_0
#define DOOR_LOCK_PIN       GPIO_PIN_1
#define SPEED_SENSOR_PIN    GPIO_PIN_2
```

## Safety-Critical Interfaces (SIL 3-4)

For safety-critical interfaces:

1. **Add redundancy**: Multiple channels
2. **Add validation**: Cross-check data
3. **Add timeout**: Detect communication failures
4. **Add diagnostics**: Monitor interface health

```c
typedef struct {
    sensor_value_t channel_a;
    sensor_value_t channel_b;
    bool valid;
    uint32_t timestamp;
} redundant_sensor_interface_t;

error_t read_redundant_sensor(redundant_sensor_interface_t* data);
```

## Interface Testing

All interfaces must have:
- Unit tests for each function
- Integration tests for interface interactions
- Boundary condition tests
- Error injection tests

## Creating Interfaces

Use `/des` agent to design interfaces:

```bash
/des
Design a hardware abstraction layer for door sensors
```

## References

- See `.opencode/skills/en50128-design/` for interface patterns
- Follow MISRA C:2012 interface guidelines
- Document all interfaces in Software Design Specification (SDS)
