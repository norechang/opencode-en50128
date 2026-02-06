# Train Door Control System Example

This example demonstrates a complete EN 50128:2011 compliant railway software implementation for a train door control system at Safety Integrity Level 3 (SIL 3).

## Overview

The Train Door Control System is responsible for safely controlling train door operations, ensuring doors cannot open while the train is moving. This example implements all critical safety requirements with redundant checks, fail-safe behavior, and comprehensive verification.

## Safety Integrity Level

**SIL 3** - High safety integrity level as per EN 50128:2011 Table A.1

## Standards Compliance

- **EN 50128:2011** - Railway applications - Software for railway control and protection systems
- **MISRA C:2012** - Guidelines for the use of the C language in critical systems
- **IEC 61508** - Functional safety of electrical/electronic/programmable electronic safety-related systems

## Key Safety Requirements Implemented

### Functional Requirements
- **REQ-FUNC-001**: Doors SHALL NOT open when speed > 0 km/h
- **REQ-FUNC-002**: Speed monitoring with ≥ 10 Hz update rate
- **REQ-FUNC-003**: Door sensor monitoring with ≥ 20 Hz update rate
- **REQ-FUNC-004**: Controlled door opening with safety preconditions
- **REQ-FUNC-005**: Door close and lock with confirmation
- **REQ-FUNC-006**: Emergency door release capability

### Safety Requirements
- **REQ-SAFE-001**: Fail-safe behavior on critical failures
- **REQ-SAFE-002**: Redundant safety checks (2 independent paths)
- **REQ-SAFE-003**: Watchdog monitoring (100ms timeout)

### Performance Requirements
- **REQ-PERF-001**: ≤ 100ms response time for safety-critical inputs
- **REQ-PERF-002**: Failure rate < 10^-7 failures/hour

## Architecture

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Speed Sensor  │    │ Door Sensors    │    │ Safety Alarm    │
│   (0-350 km/h)  │    │ (closed/locked) │    │                 │
└─────────┬───────┘    └─────────┬───────┘    └─────────────────┘
          │                      │
          └──────────┬───────────┘
                     │
          ┌─────────────────────┐
          │ Door Control Module │
          │                     │
          │ - Input validation  │
          │ - Safety interlocks │
          │ - Redundant checks  │
          │ - Fail-safe logic   │
          └─────────┬───────────┘
                    │
          ┌─────────┴───────────┐
          │   Door Actuators    │
          │                     │
          │ - Open command      │
          │ - Close command     │
          │ - Lock command      │
          └─────────────────────┘
```

## File Structure

```
examples/train_door_control/
├── docs/
│   └── requirements.md          # Complete SRS (SIL 3)
├── src/
│   ├── door_control.h           # Public API definitions
│   ├── door_control.c           # Implementation (MISRA C)
│   └── error_types.h            # Error code definitions
├── test/
│   └── test_door_control.c      # Unity unit tests (100% coverage)
├── Makefile                     # Build system with verification
└── README.md                    # This file
```

## Building the Example

### Prerequisites

Install required tools:
```bash
sudo apt-get update
sudo apt-get install -y gcc make lcov cppcheck lizard
```

### Setup

Download the Unity test framework:
```bash
make setup
```

### Build

Compile the system:
```bash
make all
```

## Testing

### Unit Tests

Run the comprehensive unit test suite:
```bash
make test
```

**Test Coverage**: 100% (statement, branch, MC/DC)

**Test Cases Include**:
- Normal operation scenarios
- Boundary conditions (speed = 0, speed = 1)
- Error conditions (NULL pointers, invalid inputs)
- Safety interlock verification
- Emergency release functionality
- Redundancy fault detection
- Fail-safe behavior

### Verification Suite

Run the complete EN 50128 verification:
```bash
make verify
```

This executes:
- Static analysis (Cppcheck)
- Complexity analysis (Lizard)
- Unit tests (Unity)
- Coverage analysis (gcov/lcov)

## Code Quality Metrics

### MISRA C:2012 Compliance
- Zero mandatory rule violations
- Required rules enforced via static analysis
- Fixed-width integer types (`uint8_t`, `uint16_t`, `uint32_t`)
- No dynamic memory allocation
- Defensive programming patterns

### Complexity Limits
- Cyclomatic complexity ≤ 10 per function
- Function length ≤ 100 lines
- Parameter count ≤ 10

### Coverage Requirements (SIL 3)
- Statement coverage: 100%
- Branch coverage: 100%
- MC/DC coverage: 100%

## Usage Example

```c
#include "door_control.h"

// Initialize the system
door_control_state_t state;
door_control_init(&state);

// Process sensor inputs
door_control_input_t input = {
    .speed_kmh = 0,  // Train stopped
    .door_closed_sensor_1 = true,
    .door_closed_sensor_2 = true,
    .door_locked_sensor_1 = true,
    .door_locked_sensor_2 = true
};

door_control_output_t output;
door_control_process(&input, &output, &state);

// Check outputs
if (output.door_lock_command) {
    // Activate door lock actuator
}
```

## Documentation

### Requirements Document
See `docs/requirements.md` for the complete Software Requirements Specification including:
- 18 detailed requirements
- SIL 3 classification
- Hazard analysis summary
- Traceability matrix
- Verification methods

### API Documentation
See `src/door_control.h` for complete API documentation including:
- Function specifications
- Parameter validation
- Error conditions
- Safety considerations

## Development Workflow

This example follows the EN 50128 development process:

1. **Requirements** (`/req`) - SRS development
2. **Design** (`/des`) - Architecture and interface design
3. **Implementation** (`/imp`) - MISRA C compliant coding
4. **Testing** (`/tst`) - Unit testing with 100% coverage
5. **Verification** (`/ver`) - Static analysis and verification
6. **Validation** (`/val`) - System validation
7. **Quality Assurance** (`/qua`) - Code reviews and audits

## Tool Integration

The build system integrates industry-standard tools:

- **GCC**: C compiler with MISRA-like warnings
- **Unity**: Unit testing framework
- **Cppcheck**: Static analysis for MISRA compliance
- **gcov/lcov**: Coverage analysis and reporting
- **Lizard**: Cyclomatic complexity measurement

## Learning Objectives

This example demonstrates:
- EN 50128:2011 compliance patterns
- SIL 3 safety-critical software development
- MISRA C:2012 coding standards
- Defensive programming techniques
- Redundant safety mechanisms
- Fail-safe system design
- Comprehensive verification strategies

## References

- EN 50128:2011 - Railway Software Standard
- MISRA C:2012 - C Coding Guidelines
- IEC 61508 - Functional Safety Standard
- Unity Test Framework - https://github.com/ThrowTheSwitch/Unity