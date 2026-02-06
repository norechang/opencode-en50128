# Configuration Directory

Configuration files and constants for EN 50128 railway software.

## Purpose

Centralized location for:
- System configuration
- Hardware configuration
- Safety parameters
- Platform-specific constants

## Configuration Requirements

All configuration must:
- Use `const` for compile-time constants
- Use fixed-width types
- Be validated at startup
- Be traceable to requirements
- Include range checks

## Example Configuration File

```c
// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

// Safety Parameters (SIL 3)
#define MAX_TRAIN_SPEED_KMH     300U
#define MAX_DOOR_OPEN_SPEED_KMH 0U
#define EMERGENCY_BRAKE_DECEL   2.5  // m/s²
#define WATCHDOG_TIMEOUT_MS     1000U

// Hardware Configuration
#define DOOR_SENSOR_COUNT       8U
#define SPEED_SENSOR_COUNT      4U
#define BRAKE_CHANNELS          2U

// Timing Configuration
#define SAFETY_TASK_PERIOD_MS   10U
#define CONTROL_TASK_PERIOD_MS  50U
#define COMM_TASK_PERIOD_MS     100U

// Memory Configuration
#define COMM_BUFFER_SIZE        256U
#define LOG_BUFFER_SIZE         1024U
#define MAX_EVENT_QUEUE         32U

// Error Thresholds
#define MAX_SENSOR_ERROR_COUNT  3U
#define MAX_COMM_TIMEOUT_COUNT  5U

// Safety Margins
#define SPEED_SENSOR_TOLERANCE  5U  // %
#define BRAKE_PRESSURE_MIN      50U // kPa

#endif // CONFIG_H
```

## Configuration Validation

Validate configuration at startup:

```c
error_t validate_configuration(void) {
    // Check ranges
    if (MAX_TRAIN_SPEED_KMH > 350U) {
        return ERROR_CONFIG_INVALID;
    }
    
    // Check consistency
    if (MAX_DOOR_OPEN_SPEED_KMH >= MAX_TRAIN_SPEED_KMH) {
        return ERROR_CONFIG_INVALID;
    }
    
    // Check resource limits
    if (COMM_BUFFER_SIZE < 128U) {
        return ERROR_CONFIG_INVALID;
    }
    
    return SUCCESS;
}
```

## Platform-Specific Configuration

For multi-platform support:

```c
// platform_config.h
#ifdef TARGET_PLATFORM_X86
    #define CPU_FREQUENCY_MHZ 2400U
    #define TIMER_RESOLUTION_US 1U
#elif defined(TARGET_PLATFORM_ARM)
    #define CPU_FREQUENCY_MHZ 168U
    #define TIMER_RESOLUTION_US 10U
#else
    #error "Platform not defined"
#endif
```

## Configuration Documentation

Each configuration must document:
- Purpose and rationale
- Valid range
- Safety justification
- Traceability to requirements

Example:
```c
/**
 * MAX_DOOR_OPEN_SPEED_KMH
 * 
 * Purpose: Maximum speed at which doors can be opened
 * Value: 0 km/h (doors only open when stopped)
 * Safety: Prevents doors opening while train is moving
 * Traceability: REQ-SAF-001, REQ-SAF-012
 * SIL: 3
 */
#define MAX_DOOR_OPEN_SPEED_KMH 0U
```

## References

- See `/des` agent for configuration design patterns
- Configuration must follow MISRA C:2012 rules
- Document rationale for all safety-critical parameters
