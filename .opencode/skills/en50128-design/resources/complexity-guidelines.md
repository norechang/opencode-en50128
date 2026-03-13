# Cyclomatic Complexity Guidelines for EN 50128 Railway Software

**Purpose**: Provide guidance on managing cyclomatic complexity in C code for railway safety-critical systems per EN 50128 requirements.

**EN 50128 Reference**: 
- Table A.4, Technique 8 "Analysable Programs" (MANDATORY for SIL 3-4)
- Table A.19 "Static Analysis" (MANDATORY for SIL 3-4)

**Applicability**: All SIL levels (limits vary by SIL)

**MISRA C:2012 Compliance**: All examples comply with MISRA C:2012 mandatory rules

---

## Table of Contents

1. [What is Cyclomatic Complexity?](#what-is-cyclomatic-complexity)
2. [EN 50128 Complexity Limits by SIL](#en-50128-complexity-limits-by-sil)
3. [How to Measure Complexity](#how-to-measure-complexity)
4. [How to Reduce Complexity](#how-to-reduce-complexity)
5. [Complexity Reduction Patterns](#complexity-reduction-patterns)
6. [Tools for Complexity Analysis](#tools-for-complexity-analysis)
7. [Examples: Complex vs. Simple Code](#examples-complex-vs-simple-code)
8. [Complexity Review Checklist](#complexity-review-checklist)

---

## What is Cyclomatic Complexity?

### Definition

**Cyclomatic Complexity** (also called **McCabe Complexity**) is a software metric that measures the number of linearly independent paths through a program's source code.

**Formula**:
```
Cyclomatic Complexity (CC) = Number of decision points + 1
```

**Decision Points** include:
- `if` statements
- `else if` branches
- `for` loops
- `while` loops
- `do-while` loops
- `switch` cases
- `&&` (logical AND) in conditions
- `||` (logical OR) in conditions
- `?:` (ternary operator)
- `goto` statements (discouraged in safety-critical code)

**Rationale**: Higher complexity = more paths = harder to test = more likely to contain bugs

---

### Simple Example

```c
// Example 1: Low complexity (CC = 1)
error_t SimpleFunction(uint32_t value) {
    return SUCCESS;  // No decision points
}
// Complexity = 0 decision points + 1 = 1

// Example 2: Low complexity (CC = 2)
error_t CheckValue(uint32_t value) {
    if (value > MAX_VALUE) {  // Decision point 1
        return ERROR_OUT_OF_RANGE;
    }
    return SUCCESS;
}
// Complexity = 1 decision point + 1 = 2

// Example 3: Medium complexity (CC = 4)
error_t ValidateInput(uint32_t value) {
    if (value == 0U) {           // Decision point 1
        return ERROR_ZERO_VALUE;
    }
    if (value > MAX_VALUE) {     // Decision point 2
        return ERROR_TOO_LARGE;
    }
    if (value < MIN_VALUE) {     // Decision point 3
        return ERROR_TOO_SMALL;
    }
    return SUCCESS;
}
// Complexity = 3 decision points + 1 = 4
```

---

### Complex Example (High Complexity)

```c
// Example 4: High complexity (CC = 15) - EXCEEDS SIL 3-4 LIMIT
error_t ProcessData(const data_t* data) {
    if (data == NULL) {                              // Decision 1
        return ERROR_NULL_POINTER;
    }
    
    if (data->type == TYPE_A) {                      // Decision 2
        if (data->value > 10) {                      // Decision 3
            if (data->value < 100) {                 // Decision 4
                if (data->flag1) {                   // Decision 5
                    // Process flag1
                } else if (data->flag2) {            // Decision 6
                    // Process flag2
                } else {                             
                    // Default
                }
            } else {                                 
                // Value >= 100
            }
        } else {                                     
            // Value <= 10
        }
    } else if (data->type == TYPE_B) {               // Decision 7
        if (data->value > 50) {                      // Decision 8
            if (data->enabled) {                     // Decision 9
                // Enabled path
            } else {                                 
                // Disabled path
            }
        } else {                                     
            // Value <= 50
        }
    } else if (data->type == TYPE_C) {               // Decision 10
        for (uint8_t i = 0U; i < data->count; i++) { // Decision 11 (loop)
            if (data->items[i] > 0) {                // Decision 12
                // Process item
            }
        }
    } else if (data->type == TYPE_D) {               // Decision 13
        // Process TYPE_D
    } else {                                         
        return ERROR_INVALID_TYPE;
    }
    
    return SUCCESS;
}
// Complexity = 14 decision points + 1 = 15
// EXCEEDS SIL 3-4 limit (10), exceeds SIL 2 limit (15)
```

---

## EN 50128 Complexity Limits by SIL

### Industry Standard Limits

| SIL Level | Maximum Cyclomatic Complexity | EN 50128 Justification |
|-----------|-------------------------------|------------------------|
| **SIL 0** | **≤ 20** | Recommended (no strict requirement) |
| **SIL 1** | **≤ 20** | Recommended (no strict requirement) |
| **SIL 2** | **≤ 15** | Highly Recommended (Table A.4: Analysable Programs) |
| **SIL 3** | **≤ 10** | **MANDATORY** (Table A.4: Analysable Programs, Table A.19: Static Analysis) |
| **SIL 4** | **≤ 10** | **MANDATORY** (Table A.4: Analysable Programs, Table A.19: Static Analysis) |

**Note**: EN 50128 does not specify exact numeric limits, but industry practice based on:
- IEC 61508 (functional safety standard)
- DO-178C (aviation software standard)
- ISO 26262 (automotive safety standard)
- Railway domain best practices

**Rationale for Limits**:
- **CC ≤ 10**: Function has few paths, easy to test, low bug probability
- **CC 11-15**: Function has moderate paths, testable with effort, moderate bug probability
- **CC 16-20**: Function has many paths, difficult to test, high bug probability
- **CC > 20**: Function is too complex, very difficult to test, very high bug probability

---

### Testing Implications

| Cyclomatic Complexity | Test Cases Required | Testing Difficulty |
|----------------------|---------------------|-------------------|
| 1-5 | 1-5 test cases | Easy (few paths) |
| 6-10 | 6-10 test cases | Moderate (manageable) |
| 11-15 | 11-15 test cases | Difficult (many paths) |
| 16-20 | 16-20 test cases | Very Difficult (complex logic) |
| > 20 | > 20 test cases | Extremely Difficult (unmaintainable) |

**100% Branch Coverage Requirement (SIL 3-4)**: Every decision point must be tested in both TRUE and FALSE branches. Higher complexity = more test cases needed.

**MC/DC Coverage Requirement (SIL 3-4)**: Modified Condition/Decision Coverage requires testing all combinations of conditions. Complexity grows exponentially with number of conditions.

---

## How to Measure Complexity

### Tool-Based Measurement

**Lizard** (Python tool for complexity analysis):
```bash
# Install lizard
pip install lizard

# Analyze single file
lizard src/module.c

# Analyze entire codebase
lizard src/

# Set complexity threshold (fail if exceeded)
lizard --CCN 10 src/

# Generate HTML report
lizard --html --output_file complexity_report.html src/
```

**Example Output**:
```
================================================
  NLOC    CCN   token  PARAM  length  location  
------------------------------------------------
      15      5     98      3      18  ProcessSensor@10-27@src/sensor.c
      42     12    256      4      45  ControlLoop@30-74@src/control.c
      28      8    178      2      31  ValidateInput@80-110@src/input.c
================================================
1 file analyzed.
==============================================================
NLOC    Avg.NLOC  AvgCCN  Avg.token  function_cnt    file
--------------------------------------------------------------
     85      28.3     8.3      177.3         3     src/control.c
==============================================================
```

**Interpretation**:
- **NLOC**: Non-Comment Lines of Code
- **CCN**: Cyclomatic Complexity Number
- **token**: Number of tokens (identifiers, operators, keywords)
- **PARAM**: Number of parameters
- **length**: Function length in lines

---

### Manual Calculation

**Step-by-Step Process**:

1. **Count Decision Points**:
   - Count `if` statements
   - Count `else if` branches
   - Count `for` loops
   - Count `while` loops
   - Count `do-while` loops
   - Count `switch` cases
   - Count `&&` and `||` in conditions (each counts as 1 decision)
   - Count `?:` ternary operators

2. **Add 1**:
   - Cyclomatic Complexity = Decision Points + 1

**Example Calculation**:
```c
error_t ValidateSpeed(uint16_t speed) {
    if (speed == 0U) {              // Decision 1
        return ERROR_ZERO_SPEED;
    }
    if (speed > MAX_SPEED) {        // Decision 2
        return ERROR_OVERSPEED;
    }
    if (speed < MIN_SPEED) {        // Decision 3
        return ERROR_UNDERSPEED;
    }
    return SUCCESS;
}

// Complexity = 3 decision points + 1 = 4 (OK for all SILs)
```

**Compound Conditions**:
```c
error_t ValidateRange(uint16_t value, bool enabled) {
    if ((value > MIN_VALUE) && (value < MAX_VALUE) && enabled) {
        // && counts as additional decision points
        // Decision 1: (value > MIN_VALUE)
        // Decision 2: && (value < MAX_VALUE)
        // Decision 3: && enabled
        return SUCCESS;
    }
    return ERROR_INVALID;
}

// Complexity = 3 decision points + 1 = 4 (OK for all SILs)
```

---

## How to Reduce Complexity

### Strategy 1: Extract Functions (Decomposition)

**Principle**: Break complex function into smaller, simpler functions

**Before** (CC = 15, exceeds SIL 3-4 limit):
```c
error_t ProcessData(const data_t* data) {
    if (data == NULL) return ERROR_NULL_POINTER;
    
    if (data->type == TYPE_A) {
        if (data->value > 10) {
            if (data->value < 100) {
                if (data->flag1) {
                    // Complex logic for flag1
                } else if (data->flag2) {
                    // Complex logic for flag2
                } else {
                    // Default logic
                }
            } else {
                // Value >= 100 logic
            }
        } else {
            // Value <= 10 logic
        }
    } else if (data->type == TYPE_B) {
        // More complex logic...
    } else if (data->type == TYPE_C) {
        // More complex logic...
    } else {
        return ERROR_INVALID_TYPE;
    }
    
    return SUCCESS;
}
```

**After** (CC = 5 for main function, CC ≤ 4 for helper functions):
```c
// Main function: dispatcher (CC = 5, OK for SIL 3-4)
error_t ProcessData(const data_t* data) {
    if (data == NULL) return ERROR_NULL_POINTER;
    
    switch (data->type) {
        case TYPE_A:
            return ProcessTypeA(data);  // Complexity moved to helper
        case TYPE_B:
            return ProcessTypeB(data);  // Complexity moved to helper
        case TYPE_C:
            return ProcessTypeC(data);  // Complexity moved to helper
        case TYPE_D:
            return ProcessTypeD(data);  // Complexity moved to helper
        default:
            return ERROR_INVALID_TYPE;
    }
}

// Helper function: TYPE_A processing (CC = 4, OK for SIL 3-4)
static error_t ProcessTypeA(const data_t* data) {
    if (data->value <= 10) {
        return ProcessLowValue(data);
    }
    if (data->value >= 100) {
        return ProcessHighValue(data);
    }
    // Medium value (10 < value < 100)
    return ProcessMediumValue(data);
}

// Helper function: medium value processing (CC = 3, OK for SIL 3-4)
static error_t ProcessMediumValue(const data_t* data) {
    if (data->flag1) {
        // Logic for flag1
        return SUCCESS;
    }
    if (data->flag2) {
        // Logic for flag2
        return SUCCESS;
    }
    // Default logic
    return SUCCESS;
}
```

**Benefits**:
- Main function complexity reduced from 15 to 5
- Each helper function has low complexity (≤ 4)
- Each function has single, clear purpose
- Easier to test (fewer paths per function)
- Easier to review and maintain

---

### Strategy 2: Use Guard Clauses (Early Returns)

**Principle**: Check error conditions first and return early

**Before** (CC = 5, deep nesting):
```c
error_t ProcessInput(const input_t* input, output_t* output) {
    if (input != NULL) {
        if (output != NULL) {
            if (input->value < MAX_VALUE) {
                if (input->value > MIN_VALUE) {
                    // Process valid input
                    output->result = input->value * 2U;
                    return SUCCESS;
                } else {
                    return ERROR_TOO_SMALL;
                }
            } else {
                return ERROR_TOO_LARGE;
            }
        } else {
            return ERROR_NULL_OUTPUT;
        }
    } else {
        return ERROR_NULL_INPUT;
    }
}
```

**After** (CC = 5, flat structure, more readable):
```c
error_t ProcessInput(const input_t* input, output_t* output) {
    // Guard clauses (early returns)
    if (input == NULL) return ERROR_NULL_INPUT;
    if (output == NULL) return ERROR_NULL_OUTPUT;
    if (input->value >= MAX_VALUE) return ERROR_TOO_LARGE;
    if (input->value <= MIN_VALUE) return ERROR_TOO_SMALL;
    
    // Process valid input (happy path at end)
    output->result = input->value * 2U;
    return SUCCESS;
}
```

**Benefits**:
- Same complexity (5), but more readable
- Reduced nesting depth (4 levels → 1 level)
- Happy path at end (not buried in nested if)
- Easier to add new validations

---

### Strategy 3: Simplify Conditional Logic

**Principle**: Replace complex conditionals with simpler equivalents

**Before** (CC = 4, complex condition):
```c
error_t CheckStatus(const device_t* device) {
    if ((device->status == STATUS_READY) &&
        (device->enabled) &&
        (device->error_count == 0U) &&
        (device->temperature < MAX_TEMP)) {
        return SUCCESS;
    }
    return ERROR_NOT_READY;
}
// Complexity = 4 (each && is a decision point)
```

**After** (CC = 2, helper function):
```c
static bool IsDeviceReady(const device_t* device) {
    // Helper function to encapsulate complex condition
    return (device->status == STATUS_READY) &&
           (device->enabled) &&
           (device->error_count == 0U) &&
           (device->temperature < MAX_TEMP);
}

error_t CheckStatus(const device_t* device) {
    if (IsDeviceReady(device)) {
        return SUCCESS;
    }
    return ERROR_NOT_READY;
}
// Complexity = 2 (single if statement)
// (Helper function has CC = 4, but that's OK if helper is simple)
```

**Benefits**:
- Main function complexity reduced
- Condition is reusable (can call IsDeviceReady elsewhere)
- Condition has meaningful name (self-documenting)

---

### Strategy 4: Replace Switch with Lookup Tables

**Principle**: For simple switch statements, use lookup tables

**Before** (CC = 8, large switch):
```c
uint8_t GetPriority(message_type_t type) {
    switch (type) {
        case MSG_EMERGENCY:   return 0U;
        case MSG_ALARM:       return 1U;
        case MSG_WARNING:     return 2U;
        case MSG_STATUS:      return 3U;
        case MSG_INFO:        return 4U;
        case MSG_DEBUG:       return 5U;
        default:              return 255U;  // Invalid
    }
}
// Complexity = 7 cases + 1 = 8 (OK for SIL 3-4, but can be improved)
```

**After** (CC = 2, lookup table):
```c
// Lookup table (constant data, no decisions)
static const uint8_t priority_table[NUM_MESSAGE_TYPES] = {
    [MSG_EMERGENCY] = 0U,
    [MSG_ALARM]     = 1U,
    [MSG_WARNING]   = 2U,
    [MSG_STATUS]    = 3U,
    [MSG_INFO]      = 4U,
    [MSG_DEBUG]     = 5U,
};

uint8_t GetPriority(message_type_t type) {
    // Range check (decision 1)
    if (type >= NUM_MESSAGE_TYPES) {
        return 255U;  // Invalid
    }
    // Lookup (no decision)
    return priority_table[type];
}
// Complexity = 1 decision + 1 = 2 (excellent for all SILs)
```

**Benefits**:
- Complexity reduced from 8 to 2
- No switch statement (faster, more maintainable)
- Easy to add new message types (just update table)
- Lookup table is constant data (can be in ROM/Flash)

**Caution**: Only use lookup tables for **simple mappings** (no complex logic per case). If each case has unique logic, use switch or extract functions.

---

### Strategy 5: Use Table-Driven Approach for State Machines

**Principle**: Implement state machines using state transition tables

**Before** (CC = 20, nested switch):
```c
error_t ProcessEvent(state_t current_state, event_t event, state_t* next_state) {
    switch (current_state) {
        case STATE_IDLE:
            switch (event) {
                case EVENT_START:    *next_state = STATE_RUNNING; return SUCCESS;
                case EVENT_SHUTDOWN: *next_state = STATE_OFF;     return SUCCESS;
                default:             return ERROR_INVALID_EVENT;
            }
        case STATE_RUNNING:
            switch (event) {
                case EVENT_STOP:     *next_state = STATE_IDLE;    return SUCCESS;
                case EVENT_ALARM:    *next_state = STATE_ALARM;   return SUCCESS;
                case EVENT_SHUTDOWN: *next_state = STATE_OFF;     return SUCCESS;
                default:             return ERROR_INVALID_EVENT;
            }
        case STATE_ALARM:
            switch (event) {
                case EVENT_RESET:    *next_state = STATE_IDLE;    return SUCCESS;
                case EVENT_SHUTDOWN: *next_state = STATE_OFF;     return SUCCESS;
                default:             return ERROR_INVALID_EVENT;
            }
        // ... more states
        default:
            return ERROR_INVALID_STATE;
    }
}
// Complexity = 20+ (nested switch, many branches)
```

**After** (CC = 4, table-driven):
```c
// State transition table (constant data)
typedef struct {
    state_t current_state;
    event_t event;
    state_t next_state;
} transition_t;

static const transition_t transition_table[] = {
    // From STATE_IDLE
    {STATE_IDLE,    EVENT_START,    STATE_RUNNING},
    {STATE_IDLE,    EVENT_SHUTDOWN, STATE_OFF},
    
    // From STATE_RUNNING
    {STATE_RUNNING, EVENT_STOP,     STATE_IDLE},
    {STATE_RUNNING, EVENT_ALARM,    STATE_ALARM},
    {STATE_RUNNING, EVENT_SHUTDOWN, STATE_OFF},
    
    // From STATE_ALARM
    {STATE_ALARM,   EVENT_RESET,    STATE_IDLE},
    {STATE_ALARM,   EVENT_SHUTDOWN, STATE_OFF},
    
    // ... more transitions
};

#define NUM_TRANSITIONS (sizeof(transition_table) / sizeof(transition_table[0]))

error_t ProcessEvent(state_t current_state, event_t event, state_t* next_state) {
    uint16_t i;
    
    // Lookup transition in table (decision 1: loop)
    for (i = 0U; i < NUM_TRANSITIONS; i++) {
        // Decision 2: match found?
        if ((transition_table[i].current_state == current_state) &&
            (transition_table[i].event == event)) {
            // Transition found
            *next_state = transition_table[i].next_state;
            return SUCCESS;
        }
    }
    
    // Transition not found (invalid event for current state)
    return ERROR_INVALID_EVENT;
}
// Complexity = 3 decisions + 1 = 4 (excellent for all SILs)
```

**Benefits**:
- Complexity reduced from 20+ to 4
- State transition table is **data** (easy to review, verify, validate)
- Easy to add new states or transitions (just update table)
- Table can be auto-generated from state machine model
- Table can be verified independently (static analysis)

---

## Complexity Reduction Patterns

### Pattern 1: Polymorphism via Function Pointers (Use Sparingly)

**Caution**: Function pointers are **NOT RECOMMENDED** for SIL 3-4 (MISRA C discourages, increases complexity).

Use only if:
- Complexity reduction is significant (CC > 20 → CC < 10)
- Safety analysis justifies the risk
- Extensive testing (including function pointer validation)

**Before** (CC = 12):
```c
error_t ProcessMessage(message_type_t type, const message_t* msg) {
    switch (type) {
        case TYPE_A: return ProcessTypeA(msg);
        case TYPE_B: return ProcessTypeB(msg);
        case TYPE_C: return ProcessTypeC(msg);
        case TYPE_D: return ProcessTypeD(msg);
        case TYPE_E: return ProcessTypeE(msg);
        case TYPE_F: return ProcessTypeF(msg);
        case TYPE_G: return ProcessTypeG(msg);
        case TYPE_H: return ProcessTypeH(msg);
        case TYPE_I: return ProcessTypeI(msg);
        case TYPE_J: return ProcessTypeJ(msg);
        default:     return ERROR_INVALID_TYPE;
    }
}
```

**After** (CC = 3, using function pointer table):
```c
// Function pointer type
typedef error_t (*message_handler_t)(const message_t* msg);

// Function pointer table (careful: safety risk if not validated)
static const message_handler_t handler_table[NUM_MESSAGE_TYPES] = {
    [TYPE_A] = ProcessTypeA,
    [TYPE_B] = ProcessTypeB,
    [TYPE_C] = ProcessTypeC,
    // ... more handlers
};

error_t ProcessMessage(message_type_t type, const message_t* msg) {
    message_handler_t handler;
    
    // Range check (decision 1)
    if (type >= NUM_MESSAGE_TYPES) {
        return ERROR_INVALID_TYPE;
    }
    
    // Get handler from table
    handler = handler_table[type];
    
    // Validate handler (decision 2 - defensive programming)
    if (handler == NULL) {
        return ERROR_INVALID_HANDLER;
    }
    
    // Call handler
    return handler(msg);
}
// Complexity = 2 decisions + 1 = 3 (excellent)
```

**Safety Considerations**:
- Validate function pointer is not NULL before calling (mandatory)
- Function pointer table must be const (in ROM/Flash, not modifiable)
- Extensive testing of all handlers
- Consider CRC protection for function pointer table (advanced)

---

### Pattern 2: Command Pattern (OOP-like in C)

**Before** (CC = 15, large switch):
```c
error_t ExecuteCommand(command_type_t cmd, const params_t* params) {
    switch (cmd) {
        case CMD_INIT:
            // Complex initialization logic
            break;
        case CMD_START:
            // Complex start logic
            break;
        case CMD_STOP:
            // Complex stop logic
            break;
        // ... 10 more commands
        default:
            return ERROR_INVALID_COMMAND;
    }
    return SUCCESS;
}
```

**After** (CC = 3, command objects):
```c
// Command structure
typedef struct {
    command_type_t type;
    error_t (*execute)(const params_t* params);
} command_t;

// Command implementations
static error_t ExecuteInit(const params_t* params) {
    // Initialization logic (separate function, manageable complexity)
    return SUCCESS;
}

static error_t ExecuteStart(const params_t* params) {
    // Start logic (separate function, manageable complexity)
    return SUCCESS;
}

// Command table
static const command_t command_table[NUM_COMMANDS] = {
    {CMD_INIT,  ExecuteInit},
    {CMD_START, ExecuteStart},
    {CMD_STOP,  ExecuteStop},
    // ... more commands
};

error_t ExecuteCommand(command_type_t cmd, const params_t* params) {
    uint16_t i;
    
    // Find command in table (decision 1: loop)
    for (i = 0U; i < NUM_COMMANDS; i++) {
        // Decision 2: match found?
        if (command_table[i].type == cmd) {
            // Validate handler (decision 3)
            if (command_table[i].execute == NULL) {
                return ERROR_INVALID_HANDLER;
            }
            // Execute command
            return command_table[i].execute(params);
        }
    }
    
    // Command not found
    return ERROR_INVALID_COMMAND;
}
// Complexity = 3 (manageable)
```

---

## Tools for Complexity Analysis

### Lizard (Recommended)

**Installation**:
```bash
pip install lizard
```

**Basic Usage**:
```bash
# Analyze single file
lizard src/module.c

# Analyze directory
lizard src/

# Set threshold (fail if CC > 10)
lizard --CCN 10 src/

# Generate HTML report
lizard --html --output_file complexity.html src/

# Analyze only functions with CC > 10
lizard --CCN 10 --warnings_only src/

# Output to CSV for processing
lizard --csv src/ > complexity.csv
```

**Integration with CI/CD**:
```bash
# In CI pipeline (fail build if complexity exceeds limit)
lizard --CCN 10 src/ || exit 1
```

---

### Cppcheck (Static Analysis + Complexity)

**Installation**:
```bash
sudo apt-get install cppcheck  # Linux
brew install cppcheck          # macOS
```

**Usage**:
```bash
# Basic analysis
cppcheck --enable=all src/

# Include complexity warnings
cppcheck --enable=all --max-complexity=10 src/

# Generate XML report
cppcheck --enable=all --xml --xml-version=2 src/ 2> cppcheck_report.xml
```

---

### Clang Static Analyzer

**Usage**:
```bash
# Analyze with complexity warnings
scan-build -enable-checker alpha.core.ComplexCondition make
```

---

## Examples: Complex vs. Simple Code

### Example 1: Input Validation

**Complex** (CC = 10, nested conditions):
```c
error_t ValidateInput(const input_t* input) {
    if (input != NULL) {
        if (input->type >= TYPE_MIN && input->type <= TYPE_MAX) {
            if (input->value >= 0) {
                if (input->value <= MAX_VALUE) {
                    if (input->enabled) {
                        if (input->priority >= 0 && input->priority <= 10) {
                            if (input->timestamp > 0) {
                                if (input->timestamp <= GetCurrentTime()) {
                                    return SUCCESS;
                                } else {
                                    return ERROR_FUTURE_TIMESTAMP;
                                }
                            } else {
                                return ERROR_INVALID_TIMESTAMP;
                            }
                        } else {
                            return ERROR_INVALID_PRIORITY;
                        }
                    } else {
                        return ERROR_DISABLED;
                    }
                } else {
                    return ERROR_VALUE_TOO_LARGE;
                }
            } else {
                return ERROR_VALUE_NEGATIVE;
            }
        } else {
            return ERROR_INVALID_TYPE;
        }
    } else {
        return ERROR_NULL_POINTER;
    }
}
// Complexity = 10 (at SIL 3-4 limit, deeply nested)
```

**Simple** (CC = 10, flat structure with guard clauses):
```c
error_t ValidateInput(const input_t* input) {
    // Guard clauses (early returns, no nesting)
    if (input == NULL) return ERROR_NULL_POINTER;
    if ((input->type < TYPE_MIN) || (input->type > TYPE_MAX)) return ERROR_INVALID_TYPE;
    if (input->value < 0) return ERROR_VALUE_NEGATIVE;
    if (input->value > MAX_VALUE) return ERROR_VALUE_TOO_LARGE;
    if (!input->enabled) return ERROR_DISABLED;
    if ((input->priority < 0) || (input->priority > 10)) return ERROR_INVALID_PRIORITY;
    if (input->timestamp == 0U) return ERROR_INVALID_TIMESTAMP;
    if (input->timestamp > GetCurrentTime()) return ERROR_FUTURE_TIMESTAMP;
    
    // All validations passed
    return SUCCESS;
}
// Complexity = 10 (same as before, but more readable, no deep nesting)
```

**Even Simpler** (CC = 2, extract helper functions):
```c
error_t ValidateInput(const input_t* input) {
    error_t err;
    
    // Validate structure
    err = ValidateInputStructure(input);
    if (err != SUCCESS) return err;
    
    // Validate values
    err = ValidateInputValues(input);
    if (err != SUCCESS) return err;
    
    return SUCCESS;
}
// Complexity = 2 (excellent for all SILs)

static error_t ValidateInputStructure(const input_t* input) {
    if (input == NULL) return ERROR_NULL_POINTER;
    if ((input->type < TYPE_MIN) || (input->type > TYPE_MAX)) return ERROR_INVALID_TYPE;
    if (!input->enabled) return ERROR_DISABLED;
    return SUCCESS;
}
// Complexity = 4 (OK for all SILs)

static error_t ValidateInputValues(const input_t* input) {
    if (input->value < 0) return ERROR_VALUE_NEGATIVE;
    if (input->value > MAX_VALUE) return ERROR_VALUE_TOO_LARGE;
    if ((input->priority < 0) || (input->priority > 10)) return ERROR_INVALID_PRIORITY;
    if (input->timestamp == 0U) return ERROR_INVALID_TIMESTAMP;
    if (input->timestamp > GetCurrentTime()) return ERROR_FUTURE_TIMESTAMP;
    return SUCCESS;
}
// Complexity = 6 (OK for all SILs)
```

---

### Example 2: State Machine

**Complex** (CC = 25, nested switch):
```c
error_t ProcessStateMachine(state_t state, event_t event) {
    switch (state) {
        case STATE_IDLE:
            switch (event) {
                case EVENT_START: /* ... */ break;
                case EVENT_STOP:  /* ... */ break;
                // ... 5 more events
            }
            break;
        case STATE_RUNNING:
            switch (event) {
                // ... 7 events
            }
            break;
        case STATE_ALARM:
            // ... more states
            break;
        // ... 5 more states
    }
    return SUCCESS;
}
// Complexity = 25+ (far exceeds all SIL limits)
```

**Simple** (CC = 4, table-driven):
```c
// Use state transition table (shown in Strategy 5 above)
// Complexity reduced to 4 (excellent for all SILs)
```

---

## Complexity Review Checklist

### During Design Phase

- [ ] **Estimate complexity** for each function (before implementation)
- [ ] **Target CC ≤ 10** for SIL 3-4 functions
- [ ] **Decompose complex algorithms** into smaller functions
- [ ] **Use tables** for simple mappings (switch statements, state machines)
- [ ] **Prefer simple control flow** (avoid deep nesting)

### During Implementation Phase

- [ ] **Measure complexity** with Lizard or Cppcheck
- [ ] **Refactor functions** that exceed SIL limits
- [ ] **Use guard clauses** to reduce nesting
- [ ] **Extract helper functions** to reduce complexity
- [ ] **Document complexity** in code comments

### During Review Phase

- [ ] **Verify complexity** is within SIL limits (≤10 for SIL 3-4, ≤15 for SIL 2, ≤20 for SIL 0-1)
- [ ] **Check tool reports** (Lizard, Cppcheck)
- [ ] **Justify exceptions** if complexity limit exceeded (must have rationale and mitigation)
- [ ] **Re-measure after changes** (complexity can increase during bug fixes)

---

## Summary

| SIL | Max CC | Strategy |
|-----|--------|----------|
| **0-1** | ≤ 20 | Keep functions simple, extract helpers when needed |
| **2** | ≤ 15 | Mandatory decomposition for complex functions |
| **3-4** | ≤ 10 | Aggressive decomposition, use tables, guard clauses |

**Key Principles**:
1. **Measure complexity early** (during design)
2. **Target low complexity** (CC ≤ 10 for SIL 3-4)
3. **Extract functions** when complexity exceeds limit
4. **Use guard clauses** to reduce nesting
5. **Use tables** for simple mappings
6. **Verify with tools** (Lizard, Cppcheck)

**Remember**: **Low complexity = easier testing = fewer bugs = higher safety**

---

## References

- **EN 50128:2011 Table A.4**: Software Design and Implementation Techniques, Technique 8 "Analysable Programs" (MANDATORY SIL 3-4)
- **EN 50128:2011 Table A.19**: Static Analysis (MANDATORY SIL 3-4)
- **McCabe, T. J. (1976)**: "A Complexity Measure" (original cyclomatic complexity paper)
- **IEC 61508**: Functional Safety standard (complexity guidelines)
- **MISRA C:2012**: Complexity recommendations
- **Lizard Tool**: https://github.com/terryyin/lizard

---

**END OF COMPLEXITY GUIDELINES**
