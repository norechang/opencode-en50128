# Components Directory

Reusable software components for EN 50128 railway systems.

## Purpose

This directory contains safety-critical C components that can be reused across multiple railway software projects.

## Component Requirements

Each component must:
- Be MISRA C:2012 compliant
- Have complete unit test coverage (100% for SIL 2+)
- Include comprehensive documentation
- Maintain traceability to requirements
- Follow defensive programming patterns

## Component Template

```c
// component_name.h
#ifndef COMPONENT_NAME_H
#define COMPONENT_NAME_H

#include <stdint.h>
#include "error_types.h"

// Public types
typedef struct component_state_t component_state_t;

// Public functions
error_t component_init(component_state_t* state);
error_t component_process(component_state_t* state, const input_t* input, output_t* output);
error_t component_shutdown(component_state_t* state);

#endif // COMPONENT_NAME_H
```

## Example Components

Future components may include:
- `door_control` - Train door safety control (SIL 3)
- `speed_monitor` - Speed monitoring and limiting (SIL 4)
- `brake_control` - Brake system control (SIL 3)
- `comm_protocol` - Safety communication protocol (SIL 2)
- `watchdog` - Safety watchdog implementation (SIL 3)

## Adding New Components

1. Design with `/des` agent
2. Implement with `/imp` agent  
3. Test with `/tst` agent
4. Verify with `/ver` agent
5. Review with `/qua` agent

See `docs/EN50128-Compliance-Guide.md` for complete workflow.
