# Source Code Directory

This directory contains the source code for EN 50128 compliant railway software components.

## Directory Structure

```
src/
├── components/     # Reusable software components
├── config/         # Configuration files and constants
├── interfaces/     # Hardware and software interfaces
└── tests/          # Test code and test harness
```

## Guidelines

### C Language Requirements

All source code must follow:
- **MISRA C:2012** (mandatory for SIL 2+)
- **Fixed-width types**: Use `uint8_t`, `uint16_t`, not `int`, `long`
- **Static allocation only**: No `malloc/free` for SIL 2+
- **Defensive programming**: Validate all inputs, check all outputs
- **Cyclomatic complexity**: ≤ 10 (SIL 3-4), ≤ 15 (SIL 2), ≤ 20 (SIL 0-1)

### Module Structure

Each C module should consist of:
- Header file (`.h`) with public interface
- Implementation file (`.c`) with private implementation
- Unit test file (`test_*.c`)

Example:
```
components/
├── door_control.h
├── door_control.c
└── test_door_control.c
```

### Error Handling

All functions must return error status:

```c
typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER,
    ERROR_INVALID_PARAMETER,
    ERROR_OUT_OF_RANGE,
    // ...
} error_t;

error_t function_name(const input_t* input, output_t* output);
```

### Documentation

Each function must have:
```c
/**
 * Brief description of function
 * 
 * @param[in]  input   Description
 * @param[out] output  Description
 * @return Error code (SUCCESS or error)
 * 
 * Traceability: REQ-xxx, DES-yyy
 */
```

## Getting Started

Use the `/imp` agent to generate MISRA C compliant code:

```bash
/imp
Create a door control module with safety interlocks
```

## Verification

Before committing code:

```bash
# Static analysis
cppcheck --addon=misra src/

# Complexity check
lizard --CCN 10 src/

# Unit tests
make test
```

## References

- Use `/imp` agent for implementation guidance
- See `docs/EN50128-Compliance-Guide.md` for coding standards
- MISRA C:2012 rules in `.opencode/skills/en50128-implementation/`
