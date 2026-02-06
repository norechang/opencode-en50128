---
name: en50128-safety
description: Safety analysis techniques including FMEA and FTA for EN 50128 C programs with defensive programming patterns
license: Proprietary
compatibility: opencode
metadata:
  standard: EN 50128:2011
  domain: railway-software
  language: C
  safety-techniques: FMEA, FTA, Hazard Analysis
---

## What I do

I provide safety analysis techniques and patterns for EN 50128 Section 7.1 and EN 50126:
- Perform hazard identification and analysis
- Conduct FMEA for C code modules
- Execute Fault Tree Analysis (FTA)
- Determine and justify SIL levels
- Implement C-specific safety patterns (watchdog, redundancy, voting)
- Enforce defensive programming for safety
- Develop safety case documentation

## When to use me

Use this skill when:
- Performing hazard analysis
- Conducting FMEA on C modules
- Creating fault trees for hazardous conditions
- Determining SIL levels
- Implementing safety mechanisms in C
- Developing safety case
- Reviewing code for safety compliance

## Software Analysis Techniques (EN 50128 Table A.8)

**EN 50128 Section 6.3, Table A.8** defines software analysis techniques:

| # | TECHNIQUE/MEASURE | Ref | SIL 0 | SIL 1-2 | SIL 3-4 |
|---|-------------------|-----|-------|---------|---------|
| 1 | **Static Software Analysis** | D.13, D.37, Table A.19 | R | HR | HR |
| 2 | **Dynamic Software Analysis** | Table A.13, Table A.14 | - | R | HR |
| 3 | Cause Consequence Diagrams | D.6 | R | R | R |
| 4 | Event Tree Analysis | D.22 | - | R | R |
| 5 | **Software Error Effect Analysis** | D.25 | - | R | HR |

**Highly Recommended for SIL 3-4:**
- **Static Software Analysis (1)** - Highly Recommended
- **Dynamic Software Analysis (2)** - Highly Recommended
- **Software Error Effect Analysis (5)** - Highly Recommended

**Key Points:**
- One or more techniques SHALL be selected per SIL level
- Software Error Effect Analysis (SEEA) is Highly Recommended for SIL 3-4
- Static and Dynamic Analysis are Highly Recommended for SIL 3-4
- Techniques complement system-level safety analysis (FMEA, FTA, HAZOP)

**C Language Safety Analysis:**
- **Static analysis:** MISRA C compliance, control/data flow, complexity
- **Dynamic analysis:** Runtime behavior, memory usage, timing
- **SEEA:** Analyze failure modes of C code (NULL pointers, overflows, etc.)

**Standard Reference:** `std/EN50128-2011.md` Section 6.3, Table A.8

## SIL Determination

| SIL | Consequence | Tolerable Hazard Rate | C Code Implications |
|-----|-------------|----------------------|---------------------|
| 4 | Catastrophic | 10^-9 to 10^-8 /hr | No dynamic memory, 100% coverage, formal methods |
| 3 | Critical | 10^-8 to 10^-7 /hr | No dynamic memory (HR), 100% branch coverage |
| 2 | Marginal | 10^-7 to 10^-6 /hr | MISRA C mandatory, 100% branch coverage |
| 1 | Negligible | 10^-6 to 10^-5 /hr | Coding standards (HR) |
| 0 | Non-safety | No requirement | Standard practices |

## Safety Analysis Techniques by SIL (Table A.1)

| Technique | SIL 0-1 | SIL 2 | SIL 3-4 |
|-----------|---------|-------|---------|
| FMEA | R | HR | HR |
| FTA | R | HR | HR |
| HAZOP | R | HR | HR |
| Common Cause Failure | - | HR | **M** |

**M**=Mandatory, **HR**=Highly Recommended, **R**=Recommended

## Hazard Analysis Template

```markdown
## HAZ-[ID]: [Hazard Title]

**System**: [Affected system]
**Status**: [Open|Mitigated|Closed]

### Hazard Description
[Detailed description of hazardous condition]

### Consequences
- **Severity**: [Catastrophic|Critical|Marginal|Negligible]
- **Impact**: [Description]

### Causes
1. [Root cause 1]
2. [Root cause 2]

### Risk Assessment
- **Frequency**: [Frequent|Probable|Occasional|Remote|Improbable]
- **Risk Level**: [Unacceptable|Undesirable|Tolerable|Acceptable]
- **Assigned SIL**: [0|1|2|3|4]

### Safety Requirements
- REQ-SAFE-[ID]: [Mitigation requirement]

### Verification
- Test: TC-[ID]
- FMEA: [Reference]

### Residual Risk
[Remaining risk after mitigation]
```

## FMEA for C Code

### C-Specific Failure Modes

| Failure Mode | Effect | Severity | C Mitigation |
|--------------|--------|----------|--------------|
| NULL pointer dereference | System crash | 9 | Validate all pointers |
| Buffer overflow | Memory corruption | 10 | Bounds checking |
| Integer overflow | Wrong calculation | 8 | Safe arithmetic |
| Divide by zero | Exception/crash | 9 | Zero check |
| Uninitialized variable | Undefined behavior | 8 | Initialize all variables |

### FMEA Template for C Module

```markdown
## FMEA: [Module Name]

**Module**: [C file]
**SIL**: [Level]

| Failure Mode | Effect | Severity | Cause | Mitigation | Code Location |
|--------------|--------|----------|-------|------------|---------------|
| NULL pointer | Crash | 9 | No validation | Add NULL check | brake.c:125 |
| Buffer overflow | Corruption | 10 | No bounds check | Add size check | brake.c:145 |
```

## C Safety Patterns

### NULL Pointer Check Pattern

```c
error_t safe_function(const data_t* ptr) {
    if (ptr == NULL) {
        log_safety_violation("NULL pointer");
        return ERROR_NULL_POINTER;
    }
    // Use pointer safely
    return SUCCESS;
}
```

### Buffer Overflow Prevention

```c
error_t safe_copy(char* dest, const char* src, size_t dest_size) {
    if ((dest == NULL) || (src == NULL)) {
        return ERROR_NULL_POINTER;
    }
    
    size_t len = strlen(src);
    if (len >= dest_size) {
        return ERROR_BUFFER_TOO_SMALL;
    }
    
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
    
    return SUCCESS;
}
```

### Integer Overflow Detection

```c
error_t safe_multiply(uint32_t a, uint32_t b, uint32_t* result) {
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if ((a != 0U) && (b > (UINT32_MAX / a))) {
        log_safety_violation("Integer overflow");
        return ERROR_OVERFLOW;
    }
    
    *result = a * b;
    return SUCCESS;
}
```

### Divide by Zero Protection

```c
error_t safe_divide(int32_t num, int32_t den, int32_t* result) {
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (den == 0) {
        log_safety_violation("Divide by zero");
        return ERROR_DIVIDE_BY_ZERO;
    }
    
    *result = num / den;
    return SUCCESS;
}
```

## Watchdog Pattern

```c
#define WATCHDOG_TIMEOUT_MS  1000U

typedef struct {
    uint32_t last_feed_time;
    bool enabled;
} watchdog_t;

error_t watchdog_init(watchdog_t* wd) {
    if (wd == NULL) {
        return ERROR_NULL_POINTER;
    }
    wd->last_feed_time = get_system_time_ms();
    wd->enabled = true;
    return SUCCESS;
}

error_t watchdog_feed(watchdog_t* wd) {
    if (wd == NULL) {
        return ERROR_NULL_POINTER;
    }
    wd->last_feed_time = get_system_time_ms();
    hardware_watchdog_reset();
    return SUCCESS;
}

void main_safety_task(void) {
    watchdog_t wd;
    watchdog_init(&wd);
    
    while (1) {
        error_t status = perform_safety_function();
        if (status != SUCCESS) {
            enter_safe_state();
            break;
        }
        watchdog_feed(&wd);
        delay_ms(100);
    }
}
```

## Redundancy and Voting Pattern

```c
typedef struct {
    sensor_value_t channel_a;
    sensor_value_t channel_b;
    uint32_t disagreement_count;
} redundant_sensor_t;

error_t read_redundant_sensor(redundant_sensor_t* sensor, sensor_value_t* output) {
    if ((sensor == NULL) || (output == NULL)) {
        return ERROR_NULL_POINTER;
    }
    
    // Read both channels
    sensor->channel_a = read_sensor_channel_a();
    sensor->channel_b = read_sensor_channel_b();
    
    // Cross-check
    int32_t diff = abs(sensor->channel_a - sensor->channel_b);
    
    if (diff < AGREEMENT_TOLERANCE) {
        // Channels agree - use average
        *output = (sensor->channel_a + sensor->channel_b) / 2U;
        sensor->disagreement_count = 0U;
        return SUCCESS;
    }
    
    // Channels disagree
    sensor->disagreement_count++;
    
    if (sensor->disagreement_count > MAX_DISAGREEMENTS) {
        log_safety_violation("Persistent sensor disagreement");
        enter_safe_state();
        return ERROR_SENSOR_DISAGREEMENT;
    }
    
    return ERROR_SENSOR_TEMPORARY_FAULT;
}
```

## Safe State Transition

```c
typedef enum {
    STATE_NORMAL,
    STATE_DEGRADED,
    STATE_SAFE,
    STATE_EMERGENCY
} safety_state_t;

void enter_safe_state(safety_event_t event) {
    // Log event
    log_safety_event(event);
    
    // Disable outputs
    disable_all_actuators();
    
    // Apply physical safety
    engage_emergency_brake();
    
    // Set safe state
    current_state = STATE_SAFE;
    
    // Notify system
    notify_safety_state_change(STATE_SAFE);
    
    // Require manual reset
    require_manual_reset();
}
```

## Input Validation Safety Pattern

```c
error_t safety_input_validation(const input_t* input) {
    // NULL check
    if (input == NULL) {
        log_safety_violation("NULL input");
        return ERROR_NULL_POINTER;
    }
    
    // Range check
    if ((input->value < SAFE_MIN) || (input->value > SAFE_MAX)) {
        log_safety_violation("Input out of safe range");
        return ERROR_OUT_OF_SAFE_RANGE;
    }
    
    // Rate of change check
    static uint32_t last_value = 0U;
    uint32_t delta = abs((int32_t)input->value - (int32_t)last_value);
    
    if (delta > MAX_RATE_OF_CHANGE) {
        log_safety_violation("Unsafe rate of change");
        return ERROR_UNSAFE_RATE;
    }
    
    last_value = input->value;
    return SUCCESS;
}
```

## Python Safety Analysis Tool

```python
#!/usr/bin/env python3
"""
Safety analysis for C code
Detects common safety issues
"""

import re
import sys
from pathlib import Path

def analyze_safety_issues(c_file, sil_level):
    """Scan C code for safety concerns"""
    
    issues = []
    forbidden_funcs = ['malloc', 'calloc', 'realloc', 'free']
    
    with open(c_file, 'r') as f:
        for line_num, line in enumerate(f, 1):
            # Check for dynamic memory (forbidden SIL 2+)
            if sil_level >= 2:
                for func in forbidden_funcs:
                    if f'\\b{func}\\b' in line:
                        issues.append({
                            'line': line_num,
                            'severity': 'CRITICAL',
                            'message': f'{func}() forbidden for SIL {sil_level}',
                            'code': line.strip()
                        })
    
    return issues

if __name__ == "__main__":
    issues = analyze_safety_issues(sys.argv[1], int(sys.argv[2]))
    
    print(f"Safety Analysis: {len(issues)} issues")
    for issue in issues:
        print(f"[{issue['severity']}] Line {issue['line']}: {issue['message']}")
    
    sys.exit(1 if issues else 0)
```

## Safety Requirements Pattern

```markdown
### REQ-SAFE-[ID]: [Safety Function]

**Type**: Safety Requirement
**SIL**: [3-4]
**Hazard**: HAZ-[ID]

**Description**:
The system SHALL [action] when [condition] to prevent [hazard]
with a failure rate not exceeding [X] per hour.

**Safe State**:
Upon detection of [failure], the system SHALL transition to [safe state].

**Fault Detection**:
The system SHALL detect [fault] within [time] using [mechanism].

**C Implementation Constraints**:
- No dynamic allocation
- No recursion
- Bounded execution time
- Defensive programming mandatory
```

## Safety Review Checklist

- [ ] All hazards identified
- [ ] SIL levels justified
- [ ] Safety requirements complete
- [ ] FMEA performed on C modules
- [ ] FTA performed for critical hazards
- [ ] C code follows safety patterns
- [ ] No dynamic memory (SIL 2+)
- [ ] Defensive programming applied
- [ ] Fault detection implemented
- [ ] Safe states defined and reachable

## References
- EN 50128:2011 Section 7.1 (Safety Requirements)
- EN 50128:2011 Table A.1 (Safety Analysis Techniques)
- EN 50126:2017 (RAMS)
- IEC 61508 (Functional Safety)
