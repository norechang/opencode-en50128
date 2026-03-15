# FMEA (Failure Mode and Effects Analysis) Workflow

## Document Control

**Workflow**: FMEA (Failure Mode and Effects Analysis) for EN 50128 Railway Software  
**Skill**: en50128-safety  
**Version**: 2.0  
**Date**: 2026-03-14  
**Status**: Phase 2 Enhanced

## Table of Contents

1. [Purpose and Scope](#1-purpose-and-scope)
2. [EN 50128 and EN 50126 Applicability](#2-en-50128-and-en-50126-applicability)
3. [FMEA Process Overview](#3-fmea-process-overview)
4. [Software-Specific Failure Modes](#4-software-specific-failure-modes)
5. [Effects Analysis](#5-effects-analysis)
6. [Severity, Occurrence, Detection Ratings](#6-severity-occurrence-detection-ratings)
7. [RPN Calculation and Prioritization](#7-rpn-calculation-and-prioritization)
8. [Mitigation Strategies](#8-mitigation-strategies)
9. [FMEA Examples](#9-fmea-examples)
10. [FMEA to Hazard Log Integration](#10-fmea-to-hazard-log-integration)
11. [Tool Integration](#11-tool-integration)
12. [Example Scenario: Door Control FMEA](#12-example-scenario-door-control-fmea)

---

## 1. Purpose and Scope

### 1.1 FMEA Definition

**Failure Mode and Effects Analysis (FMEA)** is a systematic, bottom-up analysis technique used to:
- Identify potential failure modes of software components
- Analyze the effects of each failure mode on the system
- Assess the severity, occurrence probability, and detection capability
- Calculate Risk Priority Numbers (RPN) to prioritize mitigation efforts
- Define design improvements and preventive measures

### 1.2 FMEA Objectives in Railway Software

For EN 50128 compliant railway software:

1. **Early Failure Detection**: Identify potential software failures during design/implementation
2. **Risk Quantification**: Calculate RPN to prioritize safety-critical failures
3. **Design Improvement**: Drive defensive programming and fault tolerance features
4. **Hazard Log Integration**: Link FMEA failure modes to Hazard Log entries
5. **Traceability**: Trace failure modes → hazards → safety requirements → mitigations

### 1.3 Software FMEA vs Hardware FMEA

| Aspect | Hardware FMEA | Software FMEA |
|--------|---------------|---------------|
| **Failure Cause** | Physical degradation, wear-out | Logic errors, specification defects, timing issues |
| **Failure Rate** | Time-dependent (MTBF) | Time-independent (exists or not) |
| **Occurrence Rating** | Based on failure rate data | Based on complexity, testing coverage |
| **Detection** | Physical sensors, monitoring | Software assertions, diagnostics, runtime checks |
| **Mitigation** | Redundancy, maintenance | Defensive programming, formal verification, testing |

### 1.4 When to Perform FMEA

**Design Phase (Recommended)**:
- Software Architecture Specification complete
- Software Design Specification available
- Before implementation begins

**Post-Implementation (Highly Recommended)**:
- After code review
- Before integration testing
- After significant design changes

**Maintenance Phase**:
- After defect correction affecting safety-critical functions
- Before software upgrade releases

---

## 2. EN 50128 and EN 50126 Applicability

### 2.1 EN 50128 Requirements

**Table A.8: Software Analysis Techniques**

| Technique | SIL 0 | SIL 1 | SIL 2 | SIL 3 | SIL 4 | Reference |
|-----------|-------|-------|-------|-------|-------|-----------|
| Failure Mode and Effects Analysis (FMEA) | R | R | **HR** | **HR** | **HR** | D.25 |

**Legend**:
- **M** = Mandatory
- **HR** = Highly Recommended (rationale required if not used)
- **R** = Recommended
- **-** = No recommendation

**EN 50128 Section 6.3**: Software Analysis
- FMEA is part of Software Error Effect Analysis (SEEA)
- Analyzes potential software errors and their effects on system safety

### 2.2 EN 50126 Requirements

**EN 50126-1:2017 Section 6.3**: Risk Assessment
- FMEA is a recognized technique for hazard identification
- Supports quantitative risk analysis

**EN 50126-2:2017 Section 10**: Safety Integrity
- FMEA helps identify failures contributing to hazardous events
- Supports SIL allocation to software functions

### 2.3 IEC 60812:2018 Reference

**International Standard for FMEA**:
- Defines FMEA process, terminology, and worksheet format
- Provides guidance on severity, occurrence, detection scales
- Used as reference for railway software FMEA

### 2.4 SIL-Specific FMEA Requirements

| SIL Level | FMEA Requirement | Scope | Independent Review |
|-----------|------------------|-------|-------------------|
| **SIL 0** | Recommended | Critical functions | No |
| **SIL 1** | Recommended | Safety-related functions | No |
| **SIL 2** | **Highly Recommended** | All safety-related functions | Recommended |
| **SIL 3** | **Highly Recommended** | All software components | **Required** |
| **SIL 4** | **Highly Recommended** | All software components | **Required** |

**Note**: While not mandatory, FMEA is **highly recommended** for SIL 2+ and often required by railway operators for safety case acceptance.

---

## 3. FMEA Process Overview

### 3.1 FMEA Team Formation

**Team Composition** (cross-functional, 3-6 members):

1. **Safety Engineer (SAF)** - Team leader, FMEA facilitator
2. **Designer (DES)** - Software architecture and design knowledge
3. **Implementer (IMP)** - Code-level failure mode expertise
4. **Tester (TST)** - Detection method expertise
5. **Verifier (VER)** - Independent review (SIL 3-4)
6. **Domain Expert** - Railway operations knowledge

**Independence Requirements (SIL 3-4)**:
- Verifier SHALL NOT be Designer or Implementer
- FMEA review SHALL be independent from FMEA creation

### 3.2 FMEA Scope Definition

**Define Analysis Boundaries**:

1. **Component-Level FMEA**: Individual software modules (functions, classes)
2. **Function-Level FMEA**: Logical functions (speed monitoring, alarm processing)
3. **Interface-Level FMEA**: Communication interfaces (CAN bus, Ethernet, serial)

**Example Scope Statement**:
```
FMEA Scope: Speed Monitoring Module (speed_monitor.c)
- SIL Level: 3
- Functions Analyzed: get_speed(), validate_speed(), detect_overspeed()
- Interfaces: Wheel sensor input, CAN bus output, alarm interface
- Exclusions: Display functions (non-safety-related)
```

### 3.3 FMEA Worksheet Structure

**Standard FMEA Worksheet Columns**:

| Column | Description | Example |
|--------|-------------|---------|
| **Item** | Component/function being analyzed | `get_speed()` |
| **Function** | Intended function | Read wheel sensor, calculate speed |
| **Failure Mode** | How the item can fail | Returns incorrect speed value |
| **Local Effect** | Effect within the component | Speed calculation error |
| **System Effect** | Effect on the system | Incorrect speed displayed/processed |
| **End Effect** | Effect on safety | Train exceeds speed limit undetected |
| **Severity (S)** | Consequence severity (1-10) | 9 (Catastrophic) |
| **Cause** | Root cause of failure | Sensor noise not filtered |
| **Occurrence (O)** | Likelihood of occurrence (1-10) | 5 (Moderate) |
| **Detection Method** | How failure is detected | Range check in `validate_speed()` |
| **Detection (D)** | Detection difficulty (1-10) | 3 (High detection capability) |
| **RPN** | Risk Priority Number (S×O×D) | 135 |
| **Mitigation** | Proposed corrective action | Add median filter to sensor input |
| **Responsibility** | Who implements mitigation | IMP (Implementer) |
| **Status** | Open/Closed | Open |

### 3.4 FMEA Process Steps

```
┌────────────────────────────────────────────────────────────────┐
│ STEP 1: Define Scope and Boundaries                            │
│ - Select component/function for analysis                       │
│ - Define SIL level, interfaces, exclusions                     │
└────────────────────────────────────────────────────────────────┘
                            ↓
┌────────────────────────────────────────────────────────────────┐
│ STEP 2: Identify Failure Modes                                 │
│ - For each function, brainstorm potential failure modes        │
│ - Use software-specific failure mode checklist (Section 4)     │
└────────────────────────────────────────────────────────────────┘
                            ↓
┌────────────────────────────────────────────────────────────────┐
│ STEP 3: Analyze Effects                                        │
│ - Local effect (within component)                              │
│ - System effect (impact on other components)                   │
│ - End effect (impact on safety/operations)                     │
└────────────────────────────────────────────────────────────────┘
                            ↓
┌────────────────────────────────────────────────────────────────┐
│ STEP 4: Rate Severity (S)                                      │
│ - Use severity scale (1-10)                                    │
│ - Map to EN 50126-2 severity categories                        │
└────────────────────────────────────────────────────────────────┘
                            ↓
┌────────────────────────────────────────────────────────────────┐
│ STEP 5: Identify Causes and Rate Occurrence (O)                │
│ - Determine root causes (design, coding, requirements)         │
│ - Rate occurrence probability (1-10)                           │
└────────────────────────────────────────────────────────────────┘
                            ↓
┌────────────────────────────────────────────────────────────────┐
│ STEP 6: Identify Detection Methods and Rate Detection (D)      │
│ - Existing detection methods (assertions, checks, tests)       │
│ - Rate detection capability (1-10)                             │
└────────────────────────────────────────────────────────────────┘
                            ↓
┌────────────────────────────────────────────────────────────────┐
│ STEP 7: Calculate RPN                                          │
│ - RPN = Severity × Occurrence × Detection                      │
│ - Prioritize high RPN failure modes (RPN > 100)                │
└────────────────────────────────────────────────────────────────┘
                            ↓
┌────────────────────────────────────────────────────────────────┐
│ STEP 8: Define Mitigation Actions                              │
│ - Design changes, defensive programming, detection improvements│
│ - Assign responsibility and target date                        │
└────────────────────────────────────────────────────────────────┘
                            ↓
┌────────────────────────────────────────────────────────────────┐
│ STEP 9: Implement Mitigations and Recalculate RPN              │
│ - After mitigation, reassess S, O, D                           │
│ - Target RPN < 100 for safety-critical functions               │
└────────────────────────────────────────────────────────────────┘
                            ↓
┌────────────────────────────────────────────────────────────────┐
│ STEP 10: Document and Integrate with Hazard Log                │
│ - Create FMEA Report (DOC-SAF-FMEA-XXX)                        │
│ - Link failure modes to Hazard Log entries (traceability)      │
└────────────────────────────────────────────────────────────────┘
```

---

## 4. Software-Specific Failure Modes

### 4.1 Failure Mode Categories

**8 Primary Software Failure Mode Categories**:

1. **Incorrect Output** - Wrong value, wrong command
2. **No Output** - Missing command, timeout, null pointer
3. **Unexpected Output** - Spurious command, race condition
4. **Delayed Output** - Timing violation, performance degradation
5. **Data Corruption** - Memory error, communication error
6. **State Machine Errors** - Invalid state, illegal transition
7. **Resource Exhaustion** - Memory leak, CPU overload, buffer overflow
8. **Timing Errors** - Deadline missed, synchronization failure

### 4.2 Category 1: Incorrect Output

**Definition**: Function produces wrong value or executes wrong logic

**Examples**:
- Speed calculation returns incorrect value (e.g., 120 km/h instead of 80 km/h)
- Alarm priority assigned incorrectly (e.g., INFO instead of CRITICAL)
- Door control command reversed (OPEN instead of CLOSE)

**Typical Causes**:
- Arithmetic errors (integer overflow, rounding)
- Logic errors (wrong conditional, incorrect formula)
- Units mismatch (m/s vs km/h)
- Sensor calibration errors

**C Code Example**:
```c
/* FAILURE MODE: Incorrect speed calculation due to integer overflow */
uint16_t calculate_speed(uint32_t wheel_pulses, uint32_t time_ms) {
    // BUG: uint16_t result can overflow if wheel_pulses * 3600 > 65535
    uint16_t speed_kmh = (wheel_pulses * 3600) / time_ms;  // INCORRECT
    return speed_kmh;
}

/* MITIGATION: Use uint32_t for intermediate calculation */
uint16_t calculate_speed_safe(uint32_t wheel_pulses, uint32_t time_ms) {
    uint32_t speed_temp = (wheel_pulses * 3600UL) / time_ms;
    if (speed_temp > MAX_SPEED_KMH) {
        return MAX_SPEED_KMH;  // Saturate
    }
    return (uint16_t)speed_temp;
}
```

### 4.3 Category 2: No Output

**Definition**: Function fails to produce expected output

**Examples**:
- Function returns NULL pointer instead of valid data
- Communication timeout - no message sent
- Watchdog not fed - system reset
- Alarm not raised when condition met

**Typical Causes**:
- Null pointer dereference
- Communication failure
- Deadlock/livelock
- Infinite loop
- Exception/error not handled

**C Code Example**:
```c
/* FAILURE MODE: No alarm raised due to early return */
error_t raise_alarm(alarm_type_t type, uint8_t priority) {
    if (type >= NUM_ALARM_TYPES) {
        return ERROR_INVALID_TYPE;  // BUG: Early return, alarm not raised
    }
    
    // This code never executes if type is invalid
    alarm_queue_push(type, priority);
    notify_operator(type);
    return SUCCESS;
}

/* MITIGATION: Add assertion and log error before return */
error_t raise_alarm_safe(alarm_type_t type, uint8_t priority) {
    if (type >= NUM_ALARM_TYPES) {
        log_error("Invalid alarm type: %u", type);
        assert(false);  // Catch in testing
        return ERROR_INVALID_TYPE;
    }
    
    alarm_queue_push(type, priority);
    notify_operator(type);
    return SUCCESS;
}
```

### 4.4 Category 3: Unexpected Output

**Definition**: Function produces output when it should not

**Examples**:
- Spurious alarm raised (false positive)
- Door opens unexpectedly
- Emergency brake activates without cause
- Race condition causes duplicate command

**Typical Causes**:
- Race condition (concurrent access)
- Uninitialized variables
- Memory corruption (buffer overflow, dangling pointer)
- Interrupt timing issues

**C Code Example**:
```c
/* FAILURE MODE: Race condition causes spurious alarm */
static volatile bool alarm_pending = false;

void sensor_interrupt_handler(void) {
    if (sensor_value_exceeds_threshold()) {
        alarm_pending = true;  // BUG: Not atomic, can cause spurious alarm
    }
}

void main_loop(void) {
    if (alarm_pending) {
        raise_alarm(ALARM_OVERSPEED, PRIORITY_CRITICAL);
        alarm_pending = false;  // BUG: Race - interrupt may set after check
    }
}

/* MITIGATION: Use atomic operations and critical sections */
#include <stdatomic.h>
static atomic_bool alarm_pending = ATOMIC_VAR_INIT(false);

void sensor_interrupt_handler_safe(void) {
    if (sensor_value_exceeds_threshold()) {
        atomic_store(&alarm_pending, true);
    }
}

void main_loop_safe(void) {
    bool expected = true;
    if (atomic_compare_exchange_strong(&alarm_pending, &expected, false)) {
        raise_alarm(ALARM_OVERSPEED, PRIORITY_CRITICAL);
    }
}
```

### 4.5 Category 4: Delayed Output

**Definition**: Function produces correct output but too late

**Examples**:
- Brake command delayed, train overshoots station
- Alarm delayed, operator response too late
- Communication message delayed, missed deadline

**Typical Causes**:
- High CPU load (task overrun)
- Low task priority (preemption)
- Blocking I/O operations
- Inefficient algorithm (high complexity)

**C Code Example**:
```c
/* FAILURE MODE: Bubble sort causes timing violation */
void sort_alarms(alarm_t alarms[], uint16_t count) {
    // BUG: O(n^2) complexity - too slow for real-time processing
    for (uint16_t i = 0; i < count - 1; i++) {
        for (uint16_t j = 0; j < count - i - 1; j++) {
            if (alarms[j].priority < alarms[j+1].priority) {
                alarm_t temp = alarms[j];
                alarms[j] = alarms[j+1];
                alarms[j+1] = temp;
            }
        }
    }
}

/* MITIGATION: Use insertion sort (O(n) for nearly sorted) */
void sort_alarms_safe(alarm_t alarms[], uint16_t count) {
    for (uint16_t i = 1; i < count; i++) {
        alarm_t key = alarms[i];
        int16_t j = (int16_t)i - 1;
        while (j >= 0 && alarms[j].priority < key.priority) {
            alarms[j+1] = alarms[j];
            j--;
        }
        alarms[j+1] = key;
    }
}
```

### 4.6 Category 5: Data Corruption

**Definition**: Data becomes invalid or inconsistent

**Examples**:
- Speed value corrupted in memory
- Configuration data lost/corrupted
- CAN message checksum error
- Pointer corrupts unrelated data

**Typical Causes**:
- Buffer overflow
- Stack overflow
- Wild pointer (dangling, uninitialized)
- Bit errors (hardware, EMI)

**C Code Example**:
```c
/* FAILURE MODE: Buffer overflow corrupts adjacent data */
typedef struct {
    uint32_t speed_kmh;
    uint8_t alarm_buffer[16];  // BUG: Adjacent to speed
    bool emergency_brake_active;
} train_state_t;

void process_alarm_message(train_state_t* state, const char* msg) {
    // BUG: No bounds check - can overflow alarm_buffer
    strcpy((char*)state->alarm_buffer, msg);  // DANGEROUS
}

/* MITIGATION: Use safe string copy with bounds checking */
void process_alarm_message_safe(train_state_t* state, const char* msg) {
    size_t len = strlen(msg);
    if (len >= sizeof(state->alarm_buffer)) {
        len = sizeof(state->alarm_buffer) - 1;
        log_error("Alarm message truncated");
    }
    memcpy(state->alarm_buffer, msg, len);
    state->alarm_buffer[len] = '\0';
}
```

### 4.7 Category 6: State Machine Errors

**Definition**: State machine enters invalid state or illegal transition

**Examples**:
- Door state machine: LOCKED → OPENING (should require UNLOCKED)
- Train state: MOVING → STOPPED (should pass through BRAKING)
- Alarm state: CLEARED → CRITICAL (should be NEW → ACTIVE → CLEARED)

**Typical Causes**:
- Missing state validation
- Concurrent state changes (race condition)
- Exception in state transition handler
- Unexpected event received

**C Code Example**:
```c
/* FAILURE MODE: Invalid state transition */
typedef enum {
    DOOR_CLOSED,
    DOOR_LOCKED,
    DOOR_UNLOCKED,
    DOOR_OPENING,
    DOOR_OPEN
} door_state_t;

static door_state_t door_state = DOOR_CLOSED;

void unlock_door(void) {
    // BUG: No state validation - can unlock already open door
    door_state = DOOR_UNLOCKED;
    actuate_lock(false);
}

/* MITIGATION: Add state validation and logging */
error_t unlock_door_safe(void) {
    if (door_state != DOOR_CLOSED && door_state != DOOR_LOCKED) {
        log_error("Cannot unlock door in state %d", door_state);
        return ERROR_INVALID_STATE;
    }
    
    door_state = DOOR_UNLOCKED;
    actuate_lock(false);
    log_info("Door unlocked");
    return SUCCESS;
}
```

### 4.8 Category 7: Resource Exhaustion

**Definition**: System runs out of memory, CPU, or other resources

**Examples**:
- Memory leak - heap exhausted
- Stack overflow - recursive function
- Queue full - messages dropped
- CPU overload - tasks miss deadlines

**Typical Causes**:
- Memory allocation without deallocation
- Unbounded recursion
- Unbounded loops
- Resource leak (file handles, locks)

**C Code Example**:
```c
/* FAILURE MODE: Stack overflow due to recursion */
uint32_t calculate_factorial(uint32_t n) {
    if (n == 0) return 1;
    return n * calculate_factorial(n - 1);  // BUG: Unbounded recursion
}

/* MITIGATION: Use iterative implementation */
uint32_t calculate_factorial_safe(uint32_t n) {
    if (n > 12) {  // 13! overflows uint32_t
        return UINT32_MAX;
    }
    
    uint32_t result = 1;
    for (uint32_t i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
```

### 4.9 Category 8: Timing Errors

**Definition**: Timing constraint violated (deadline missed, synchronization failure)

**Examples**:
- Periodic task misses deadline
- Watchdog not fed in time
- Sensors not synchronized (time skew)
- Message arrives out of order

**Typical Causes**:
- Task overrun (execution time exceeds budget)
- Priority inversion
- Clock drift
- Interrupt latency

**C Code Example**:
```c
/* FAILURE MODE: Watchdog timeout due to blocking operation */
void watchdog_task(void) {
    while (1) {
        feed_watchdog();
        
        // BUG: Blocking I/O can delay watchdog feed
        read_configuration_from_flash();  // Takes 100ms
        
        delay_ms(50);  // Expected cycle time
    }
}

/* MITIGATION: Split into non-blocking operations */
void watchdog_task_safe(void) {
    static uint32_t cycle_count = 0;
    
    while (1) {
        feed_watchdog();  // Always feed first
        
        // Non-blocking config read every 10 cycles
        if (cycle_count % 10 == 0) {
            start_async_config_read();
        }
        
        cycle_count++;
        delay_ms(50);
    }
}
```

---

## 5. Effects Analysis

### 5.1 Three Levels of Effects

**Local Effect** → **System Effect** → **End Effect**

| Level | Description | Question | Example |
|-------|-------------|----------|---------|
| **Local** | Effect within the component | What happens inside this module? | Speed calculation returns 0 |
| **System** | Effect on other components | How does this affect the system? | Speed monitor raises false alarm |
| **End** | Effect on safety/operations | What is the impact on safety? | Train stopped unnecessarily |

### 5.2 Effect Analysis Template

```
Failure Mode: [Description]

LOCAL EFFECT:
- Immediate consequence within the component
- Internal state changes
- Data corruption within module

SYSTEM EFFECT:
- Impact on other software components
- Impact on hardware (actuators, sensors)
- Communication failures
- Performance degradation

END EFFECT (SAFETY):
- Potential harm to people (passengers, workers)
- Damage to equipment (train, infrastructure)
- Service disruption
- Environmental impact

END EFFECT (OPERATIONS):
- Availability reduction
- Maintainability issues
- Customer satisfaction impact
```

### 5.3 Example: Speed Monitor Failure Mode

**Failure Mode**: `calculate_speed()` returns speed value 50% higher than actual

**LOCAL EFFECT**:
- Speed calculation variable `speed_kmh` contains incorrect value (120 km/h instead of 80 km/h)
- Speed validation function receives incorrect input

**SYSTEM EFFECT**:
- Speed limit enforcement module receives incorrect speed
- Driver display shows incorrect speed (120 km/h)
- ATP (Automatic Train Protection) receives incorrect speed
- No overspeed alarm raised (actual speed 80 km/h, limit 100 km/h)

**END EFFECT (SAFETY)**:
- If actual speed exceeds limit, no alarm or braking occurs
- **CRITICAL HAZARD**: Train may exceed speed limit and derail on curves
- Potential casualties (passengers, crew)

**END EFFECT (OPERATIONS)**:
- Driver trusts incorrect speed indication
- Potential for manual braking errors
- Delayed schedule (if driver brakes conservatively)

### 5.4 Traceability: Effects to Hazards

Each FMEA End Effect SHOULD map to a Hazard Log entry:

```bash
# Create traceability link: FMEA failure mode → Hazard
workspace.py trace create \
    --from fmea \
    --to hazard \
    --source-id FMEA-SPD-001-FM01 \
    --target-id HAZ-SPD-001 \
    --rationale "Speed calculation error causes train overspeed hazard"
```

---

## 6. Severity, Occurrence, Detection Ratings

### 6.1 Severity Scale (1-10)

**Maps to EN 50126-2:2017 Severity Categories**

| Rating | Severity | Description | EN 50126-2 Category | Example |
|--------|----------|-------------|---------------------|---------|
| **10** | Catastrophic | Multiple fatalities | Catastrophic | Train derailment, collision |
| **9** | Catastrophic | Single fatality | Catastrophic | Passenger death |
| **8** | Critical | Severe injury | Critical | Serious injury requiring hospitalization |
| **7** | Critical | Moderate injury | Critical | Minor injury, medical attention |
| **6** | Major | Minor injury | Marginal | Bruises, no medical attention |
| **5** | Major | Service disruption > 2 hours | Marginal | Train delayed, passengers stranded |
| **4** | Moderate | Service disruption 30min - 2hr | Marginal | Train delayed, minor inconvenience |
| **3** | Minor | Service disruption < 30min | Negligible | Brief delay |
| **2** | Minor | No service impact, annoyance | Negligible | False alarm, display glitch |
| **1** | None | No effect | Negligible | No impact |

**SIL-Specific Severity Thresholds**:
- **SIL 4**: Focus on Severity 9-10 (Catastrophic)
- **SIL 3**: Focus on Severity 7-10 (Critical, Catastrophic)
- **SIL 2**: Focus on Severity 5-10 (Major, Critical, Catastrophic)
- **SIL 1**: Focus on Severity 3-10 (Minor+)

### 6.2 Occurrence Scale (1-10)

**Software Occurrence Based on Complexity and Testing**

| Rating | Occurrence | Probability | Description | Example Causes |
|--------|------------|-------------|-------------|----------------|
| **10** | Very High | > 1 in 2 | Almost certain to occur | Untested code, known defect |
| **9** | Very High | 1 in 3 | Very high probability | Complex logic, low test coverage |
| **8** | High | 1 in 8 | High probability | Moderate complexity, some testing |
| **7** | High | 1 in 20 | Moderate-high probability | Multiple input combinations |
| **6** | Moderate | 1 in 80 | Moderate probability | Average complexity, good testing |
| **5** | Moderate | 1 in 400 | Moderate-low probability | Defensive programming, unit tested |
| **4** | Low | 1 in 2,000 | Low probability | Well-tested, low complexity |
| **3** | Low | 1 in 15,000 | Low-moderate probability | Formal verification applied |
| **2** | Very Low | 1 in 150,000 | Very low probability | Proven design, extensive testing |
| **1** | Remote | < 1 in 1,500,000 | Nearly impossible | Certified library, formal proof |

**Factors Affecting Occurrence Rating**:
- **Complexity**: High cyclomatic complexity → Higher occurrence
- **Test Coverage**: Low coverage → Higher occurrence
- **Review**: No code review → Higher occurrence
- **Verification**: No static analysis → Higher occurrence
- **Experience**: Proven design patterns → Lower occurrence

### 6.3 Detection Scale (1-10)

**Detection Capability - Lower is Better**

| Rating | Detection | Capability | Description | Example Methods |
|--------|-----------|------------|-------------|-----------------|
| **10** | None | No detection | Failure undetectable | No checks, silent failure |
| **9** | Very Low | Very low chance | Detected only by end user | Customer complaint |
| **8** | Low | Low chance | Detected in field testing | System test finds issue |
| **7** | Low | Low-moderate chance | Detected in integration test | Integration test catches |
| **6** | Moderate | Moderate chance | Detected in unit test | Unit test coverage finds |
| **5** | Moderate | Moderate-high chance | Detected by code review | Code review finds issue |
| **4** | High | High chance | Detected by static analysis | Cppcheck, PC-lint finds |
| **3** | High | Very high chance | Detected by assertion | Runtime assertion fails |
| **2** | Very High | Almost certain | Detected by range check | Input validation catches |
| **1** | Certain | Compile-time | Prevented by design | Type system, compiler error |

**Detection Method Categories**:

1. **Compile-Time (D=1-2)**: Type checking, compiler warnings, lint
2. **Static Analysis (D=3-4)**: Cppcheck, PC-lint, Clang analyzer
3. **Code Review (D=4-5)**: Manual inspection by independent reviewer
4. **Unit Testing (D=5-6)**: Automated unit tests with assertions
5. **Integration Testing (D=6-7)**: Component integration tests
6. **System Testing (D=7-8)**: End-to-end system tests
7. **Field Testing (D=8-9)**: Operational scenario testing
8. **No Detection (D=10)**: Failure goes undetected until incident

### 6.4 Example Ratings

**Failure Mode**: Speed calculation returns incorrect value (50% high)

**Severity = 9** (Catastrophic - potential fatality)
- If actual speed exceeds limit, train may derail on curve
- Maps to EN 50126-2 Catastrophic

**Occurrence = 6** (Moderate - 1 in 80)
- Moderate complexity calculation (wheel pulses → km/h)
- Unit tested but edge cases may exist
- Integer overflow possible if not handled

**Detection = 3** (High - assertions catch)
- Runtime assertion checks speed range [0, MAX_SPEED]
- Comparison with previous speed (rate-of-change check)
- Very likely to be detected before end effect

**RPN = 9 × 6 × 3 = 162** (High priority for mitigation)

---

## 7. RPN Calculation and Prioritization

### 7.1 RPN Formula

**Risk Priority Number (RPN)**:
```
RPN = Severity (S) × Occurrence (O) × Detection (D)

Range: 1 to 1,000
```

### 7.2 RPN Interpretation

| RPN Range | Priority | Action Required | Timeline |
|-----------|----------|-----------------|----------|
| **800-1000** | **CRITICAL** | Immediate action, stop development | 1 week |
| **400-799** | **HIGH** | Urgent action required | 1 month |
| **200-399** | **MEDIUM** | Action required before release | 3 months |
| **100-199** | **LOW** | Action recommended | 6 months |
| **1-99** | **MINIMAL** | Monitor, no action required | N/A |

### 7.3 SIL-Specific RPN Thresholds

**Target RPN Thresholds by SIL**:

| SIL Level | Target RPN | Max Acceptable RPN | Rationale |
|-----------|------------|-------------------|-----------|
| **SIL 4** | < 50 | 100 | Highest safety integrity required |
| **SIL 3** | < 100 | 200 | High safety integrity required |
| **SIL 2** | < 150 | 300 | Moderate safety integrity required |
| **SIL 1** | < 200 | 400 | Basic safety integrity required |
| **SIL 0** | < 300 | 500 | Non-safety-related |

**Note**: These are **target** values. Any RPN > 200 should trigger mitigation planning regardless of SIL.

### 7.4 Prioritization Strategy

**Step 1: Rank by RPN**
```bash
# Generate RPN-sorted FMEA report
python3 tools/fmea/fmea_analyzer.py \
    --input docs/fmea/FMEA-SPD-001.csv \
    --sort-by rpn \
    --output docs/fmea/FMEA-SPD-001-prioritized.md
```

**Step 2: Consider Severity Override**
- Any failure mode with Severity ≥ 8 (Critical/Catastrophic) requires mitigation **regardless of RPN**
- Example: S=9, O=2, D=1 → RPN=18 (Low), but **still requires mitigation** due to S=9

**Step 3: Focus on High Occurrence + Low Detection**
- High O + High D = Hard to prevent, hard to detect → **Most dangerous**
- Example: S=7, O=8, D=8 → RPN=448 (High priority)

**Step 4: Quick Wins - Improve Detection**
- Easiest mitigation: Add detection mechanisms (assertions, checks, tests)
- Example: Add range check → D drops from 8 to 3 → RPN drops from 448 to 168

### 7.5 RPN Reduction Strategies

**Reduce Severity (S)**:
- **Difficult** - Requires design change, additional safety features
- Example: Add redundancy (dual sensors, voting)
- Example: Add fail-safe mechanism (default to safe state)

**Reduce Occurrence (O)**:
- **Moderate Difficulty** - Improve design, code quality, testing
- Example: Simplify logic (reduce complexity)
- Example: Apply defensive programming (input validation, error checking)
- Example: Increase test coverage (unit tests, integration tests)

**Reduce Detection (D)**:
- **Easiest** - Add detection mechanisms
- Example: Add assertions (`assert(speed < MAX_SPEED)`)
- Example: Add range checks (`if (speed > MAX_SPEED) return ERROR`)
- Example: Add static analysis rules (custom Cppcheck rule)
- Example: Add unit tests targeting this failure mode

### 7.6 Example RPN Calculation and Mitigation

**Before Mitigation**:
```
Failure Mode: Speed calculation integer overflow
S = 9 (Catastrophic - potential derailment)
O = 6 (Moderate - complex calculation, edge cases)
D = 7 (Low-moderate - only detected in integration test)
RPN = 9 × 6 × 7 = 378 (MEDIUM priority - action required)
```

**Mitigation Actions**:
1. **Reduce O**: Use `uint32_t` for intermediate calculation → O = 4
2. **Reduce D**: Add assertion `assert(speed < MAX_SPEED)` → D = 3

**After Mitigation**:
```
S = 9 (Unchanged - end effect still catastrophic if occurs)
O = 4 (Reduced - improved implementation reduces probability)
D = 3 (Reduced - assertion provides runtime detection)
RPN = 9 × 4 × 3 = 108 (LOW priority - acceptable for SIL 3)
```

**Result**: RPN reduced from 378 to 108 (71% reduction)

---

## 8. Mitigation Strategies

### 8.1 Mitigation Categories

**Three Primary Mitigation Approaches**:

1. **Design Changes** - Modify architecture to prevent failure
2. **Software Measures** - Defensive programming, error handling
3. **Detection Improvements** - Add checks, assertions, tests

### 8.2 Design Changes (Reduce Severity or Occurrence)

**Redundancy**:
```c
/* Dual sensor with voting - reduces severity */
typedef struct {
    uint16_t sensor1_speed;
    uint16_t sensor2_speed;
    bool sensor1_valid;
    bool sensor2_valid;
} speed_sensors_t;

uint16_t get_speed_redundant(speed_sensors_t* sensors) {
    if (!sensors->sensor1_valid && !sensors->sensor2_valid) {
        raise_alarm(ALARM_SENSOR_FAILURE, PRIORITY_CRITICAL);
        return 0;  // Safe state
    }
    
    if (!sensors->sensor1_valid) return sensors->sensor2_speed;
    if (!sensors->sensor2_valid) return sensors->sensor1_speed;
    
    // Both valid - average
    uint32_t avg = ((uint32_t)sensors->sensor1_speed + 
                    (uint32_t)sensors->sensor2_speed) / 2;
    
    // Check for disagreement
    uint16_t diff = (sensors->sensor1_speed > sensors->sensor2_speed) ?
                    (sensors->sensor1_speed - sensors->sensor2_speed) :
                    (sensors->sensor2_speed - sensors->sensor1_speed);
    
    if (diff > SENSOR_DISAGREEMENT_THRESHOLD) {
        raise_alarm(ALARM_SENSOR_DISAGREEMENT, PRIORITY_HIGH);
    }
    
    return (uint16_t)avg;
}
```

**Diversity**:
```c
/* Use different algorithms for cross-check */
uint16_t calculate_speed_method1(uint32_t pulses, uint32_t time_ms);
uint16_t calculate_speed_method2(uint32_t distance_mm, uint32_t time_ms);

uint16_t get_speed_diverse(uint32_t pulses, uint32_t time_ms, 
                           uint32_t distance_mm) {
    uint16_t speed1 = calculate_speed_method1(pulses, time_ms);
    uint16_t speed2 = calculate_speed_method2(distance_mm, time_ms);
    
    if (abs((int16_t)speed1 - (int16_t)speed2) > SPEED_DISAGREEMENT_KMH) {
        raise_alarm(ALARM_SPEED_CALCULATION_ERROR, PRIORITY_CRITICAL);
        return MIN(speed1, speed2);  // Conservative choice
    }
    
    return (speed1 + speed2) / 2;
}
```

**Fail-Safe Design**:
```c
/* Default to safe state on failure */
error_t set_door_state(door_state_t new_state) {
    if (new_state >= NUM_DOOR_STATES) {
        log_error("Invalid door state: %u", new_state);
        // FAIL-SAFE: Default to LOCKED
        door_state = DOOR_LOCKED;
        actuate_lock(true);
        return ERROR_INVALID_STATE;
    }
    
    // Validate state transition
    if (!is_valid_transition(door_state, new_state)) {
        log_error("Invalid transition: %u -> %u", door_state, new_state);
        // FAIL-SAFE: Do not change state
        return ERROR_INVALID_TRANSITION;
    }
    
    door_state = new_state;
    actuate_door(new_state);
    return SUCCESS;
}
```

### 8.3 Software Measures (Reduce Occurrence)

**Defensive Programming**:
```c
/* Input validation */
error_t process_speed_command(const speed_command_t* cmd) {
    // NULL pointer check
    if (cmd == NULL) {
        assert(false);  // Catch in testing
        return ERROR_NULL_POINTER;
    }
    
    // Range check
    if (cmd->target_speed > MAX_SPEED_KMH) {
        log_error("Speed command exceeds max: %u", cmd->target_speed);
        return ERROR_INVALID_SPEED;
    }
    
    // Type check
    if (cmd->command_type >= NUM_SPEED_COMMANDS) {
        log_error("Invalid command type: %u", cmd->command_type);
        return ERROR_INVALID_COMMAND;
    }
    
    // Process command
    return execute_speed_command(cmd);
}
```

**Error Handling**:
```c
/* Check all return values */
error_t send_brake_command(brake_level_t level) {
    error_t err;
    
    // Build command
    can_message_t msg;
    err = build_brake_message(&msg, level);
    if (err != SUCCESS) {
        log_error("Failed to build brake message: %d", err);
        raise_alarm(ALARM_BRAKE_SYSTEM_ERROR, PRIORITY_CRITICAL);
        return err;
    }
    
    // Send command
    err = can_send(&msg);
    if (err != SUCCESS) {
        log_error("Failed to send brake command: %d", err);
        raise_alarm(ALARM_COMMUNICATION_ERROR, PRIORITY_CRITICAL);
        return err;
    }
    
    // Verify acknowledgment
    can_message_t ack;
    err = can_receive(&ack, BRAKE_ACK_TIMEOUT_MS);
    if (err != SUCCESS) {
        log_error("Brake acknowledgment timeout");
        raise_alarm(ALARM_BRAKE_NO_ACK, PRIORITY_CRITICAL);
        return err;
    }
    
    return SUCCESS;
}
```

**Bounds Checking**:
```c
/* Safe array access */
error_t get_alarm_priority(alarm_type_t type, uint8_t* priority) {
    if (priority == NULL) return ERROR_NULL_POINTER;
    
    // Bounds check
    if (type >= NUM_ALARM_TYPES) {
        log_error("Invalid alarm type: %u", type);
        *priority = PRIORITY_UNKNOWN;
        return ERROR_INVALID_TYPE;
    }
    
    *priority = alarm_priority_table[type];
    return SUCCESS;
}
```

### 8.4 Detection Improvements (Reduce Detection Rating)

**Runtime Assertions**:
```c
/* Assert invariants */
#include <assert.h>

void update_speed(uint16_t new_speed) {
    assert(new_speed <= MAX_SPEED_KMH);  // Catch in testing/development
    
    // Additional runtime check for production
    if (new_speed > MAX_SPEED_KMH) {
        log_error("Speed exceeds maximum: %u", new_speed);
        new_speed = MAX_SPEED_KMH;
    }
    
    current_speed = new_speed;
}
```

**Range Checks**:
```c
/* Validate ranges at interfaces */
error_t set_target_speed(uint16_t speed_kmh) {
    if (speed_kmh > MAX_SPEED_KMH) {
        log_error("Target speed exceeds max: %u", speed_kmh);
        return ERROR_SPEED_TOO_HIGH;
    }
    
    if (speed_kmh < MIN_SPEED_KMH && speed_kmh != 0) {
        log_error("Target speed below min: %u", speed_kmh);
        return ERROR_SPEED_TOO_LOW;
    }
    
    target_speed = speed_kmh;
    return SUCCESS;
}
```

**Plausibility Checks**:
```c
/* Check rate of change */
error_t update_speed_with_plausibility(uint16_t new_speed) {
    // Check maximum acceleration (10 m/s^2 = 36 km/h/s)
    int32_t speed_diff = (int32_t)new_speed - (int32_t)previous_speed;
    uint32_t time_diff_ms = get_time_since_last_update();
    
    if (time_diff_ms > 0) {
        int32_t max_change = (MAX_ACCELERATION_KMH_PER_S * time_diff_ms) / 1000;
        
        if (abs(speed_diff) > max_change) {
            log_error("Implausible speed change: %d km/h in %u ms",
                      speed_diff, time_diff_ms);
            raise_alarm(ALARM_SPEED_SENSOR_ERROR, PRIORITY_HIGH);
            return ERROR_IMPLAUSIBLE_VALUE;
        }
    }
    
    previous_speed = current_speed;
    current_speed = new_speed;
    return SUCCESS;
}
```

**Unit Tests Targeting Failure Modes**:
```c
/* Test for integer overflow failure mode */
void test_speed_calculation_overflow(void) {
    // Test case: Large wheel pulse count that would overflow uint16_t
    uint32_t pulses = 50000;
    uint32_t time_ms = 1000;
    
    uint16_t speed = calculate_speed_safe(pulses, time_ms);
    
    // Should saturate at MAX_SPEED, not overflow
    TEST_ASSERT_EQUAL_UINT16(MAX_SPEED_KMH, speed);
}

/* Test for divide-by-zero failure mode */
void test_speed_calculation_zero_time(void) {
    uint32_t pulses = 100;
    uint32_t time_ms = 0;  // Edge case
    
    uint16_t speed = calculate_speed_safe(pulses, time_ms);
    
    // Should return error value, not crash
    TEST_ASSERT_EQUAL_UINT16(0, speed);
}
```

### 8.5 Mitigation Decision Matrix

| RPN | Severity | Recommended Mitigation Strategy |
|-----|----------|---------------------------------|
| **> 400** | Any | Immediate: Design change + software measures + detection |
| **200-400** | 8-10 | Urgent: Software measures + detection improvements |
| **200-400** | 1-7 | Software measures OR detection improvements |
| **100-200** | 8-10 | Software measures + detection improvements |
| **100-200** | 1-7 | Detection improvements |
| **< 100** | 8-10 | Detection improvements (monitoring) |
| **< 100** | 1-7 | No action required (acceptable risk) |

---

## 9. FMEA Examples

### 9.1 Example 1: Speed Monitoring Module

**Component**: `speed_monitor.c`  
**SIL Level**: 3  
**Functions Analyzed**: `get_speed()`, `validate_speed()`, `detect_overspeed()`

| Item | Function | Failure Mode | Local Effect | System Effect | End Effect | S | Cause | O | Detection | D | RPN | Mitigation | Status |
|------|----------|--------------|--------------|---------------|------------|---|-------|---|-----------|---|-----|------------|--------|
| SPD-001 | get_speed() | Returns incorrect speed (50% high) | Speed variable wrong | Wrong speed displayed, ATP receives wrong value | Train may exceed limit undetected | 9 | Integer overflow in calculation | 6 | Range check assertion | 3 | 162 | Use uint32_t for calc, saturate at max | Open |
| SPD-002 | get_speed() | Returns NULL pointer | Null dereference | System crash, watchdog reset | Train stops unexpectedly | 7 | Sensor disconnected, not detected | 5 | NULL check in caller | 4 | 140 | Add sensor health monitoring | Open |
| SPD-003 | get_speed() | Delayed return (> 100ms) | Timing violation | Stale speed value used | Brake decision based on old data | 6 | High CPU load, task preemption | 4 | Timing monitor | 5 | 120 | Increase task priority | Open |
| SPD-004 | validate_speed() | Fails to reject invalid speed | Invalid speed propagates | Wrong speed used in calculations | Safety decisions on bad data | 8 | Logic error in range check | 5 | Unit test finds issue | 5 | 200 | Add comprehensive unit tests | Open |
| SPD-005 | detect_overspeed() | False positive (alarm when no overspeed) | Spurious alarm raised | Unnecessary brake, service disruption | Train delays, customer dissatisfaction | 4 | Threshold too low, noise | 6 | System test detects | 6 | 144 | Add hysteresis to threshold | Open |
| SPD-006 | detect_overspeed() | False negative (no alarm when overspeed) | No alarm raised | Overspeed undetected | Train exceeds limit, potential derailment | 10 | Threshold too high | 3 | Integration test catches | 6 | 180 | Review threshold values, add margin | Open |

**Summary Statistics**:
- Total Failure Modes: 6
- Average RPN: 158
- High RPN (> 150): 5 (83%)
- Critical Severity (S ≥ 8): 3 (50%)

**Traceability Links**:
```bash
# Link failure modes to Hazard Log entries
workspace.py trace create --from fmea --to hazard \
    --source-id FMEA-SPD-001-FM01 --target-id HAZ-SPD-001 \
    --rationale "Speed calculation error causes overspeed hazard"

workspace.py trace create --from fmea --to hazard \
    --source-id FMEA-SPD-001-FM06 --target-id HAZ-SPD-001 \
    --rationale "False negative causes overspeed hazard"
```

### 9.2 Example 2: Alarm Processing Module

**Component**: `alarm_processor.c`  
**SIL Level**: 3  
**Functions Analyzed**: `raise_alarm()`, `clear_alarm()`, `get_alarm_priority()`

| Item | Function | Failure Mode | Local Effect | System Effect | End Effect | S | Cause | O | Detection | D | RPN | Mitigation | Status |
|------|----------|--------------|--------------|---------------|------------|---|-------|---|-----------|---|-----|------------|--------|
| ALM-001 | raise_alarm() | Alarm not raised (no output) | Alarm queue not updated | Operator not notified | Critical situation unnoticed | 9 | Early return on invalid type | 4 | Unit test catches | 5 | 180 | Add assertion, log error | Open |
| ALM-002 | raise_alarm() | Wrong priority assigned | Low priority for critical alarm | Alarm buried in queue | Operator delayed response | 8 | Priority lookup table error | 5 | Code review finds | 5 | 200 | Review priority table, add tests | Open |
| ALM-003 | raise_alarm() | Duplicate alarms | Queue overflow | Memory corruption | System crash | 7 | No duplicate check | 6 | Queue full error | 6 | 252 | Add duplicate detection logic | Open |
| ALM-004 | clear_alarm() | Alarm cleared prematurely | Active alarm removed | Condition still exists, no alarm | Operator unaware of issue | 8 | Logic error in clear condition | 5 | System test finds | 7 | 280 | Add condition re-check before clear | Open |
| ALM-005 | clear_alarm() | Wrong alarm cleared | Unrelated alarm removed | Active alarm still in queue | Operator confusion | 5 | Alarm ID mismatch | 4 | Integration test | 6 | 120 | Add ID validation | Open |
| ALM-006 | get_alarm_priority() | Returns wrong priority | Priority variable incorrect | Alarm sorted incorrectly | Low priority alarm shown first | 6 | Array index out of bounds | 5 | Bounds check catches | 3 | 90 | Add bounds check, assert | Open |

**Summary Statistics**:
- Total Failure Modes: 6
- Average RPN: 187
- High RPN (> 150): 4 (67%)
- Critical Severity (S ≥ 8): 4 (67%)

### 9.3 Example 3: Communication Interface

**Component**: `can_interface.c`  
**SIL Level**: 3  
**Functions Analyzed**: `can_send()`, `can_receive()`, `can_check_bus_health()`

| Item | Function | Failure Mode | Local Effect | System Effect | End Effect | S | Cause | O | Detection | D | RPN | Mitigation | Status |
|------|----------|--------------|--------------|---------------|------------|---|-------|---|-----------|---|-----|------------|--------|
| CAN-001 | can_send() | Message not sent (timeout) | Send buffer full | Critical command not delivered | Brake command missed, collision | 10 | Bus overload, hardware fault | 5 | Timeout detection | 4 | 200 | Add retry logic, bus monitoring | Open |
| CAN-002 | can_send() | Wrong message ID | Message routed incorrectly | Unintended recipient | Wrong component receives command | 8 | ID calculation error | 4 | Recipient checks ID | 5 | 160 | Add ID validation, unit tests | Open |
| CAN-003 | can_send() | Corrupted data | CRC mismatch | Message rejected by recipient | Command not executed | 7 | Memory corruption, EMI | 5 | CRC check detects | 3 | 105 | Add data integrity checks | Open |
| CAN-004 | can_receive() | Timeout (no message) | Receive buffer empty | Expected data not available | Stale data used in calculations | 6 | Sender failure, bus fault | 6 | Timeout error code | 4 | 144 | Add timeout handling, use last valid | Open |
| CAN-005 | can_receive() | Wrong message received | Unexpected message type | Message processed incorrectly | Invalid state transition | 8 | Message ID mismatch | 4 | Message type check | 4 | 128 | Add message type validation | Open |
| CAN-006 | can_check_bus_health() | False positive (bus OK when faulty) | Health flag incorrect | No error reported | Messages lost, undetected | 9 | Error counter threshold wrong | 5 | System test with fault injection | 6 | 270 | Review threshold, add redundant check | Open |

**Summary Statistics**:
- Total Failure Modes: 6
- Average RPN: 168
- High RPN (> 150): 4 (67%)
- Critical Severity (S ≥ 8): 4 (67%)

---

## 10. FMEA to Hazard Log Integration

### 10.1 Traceability Requirements

**EN 50128 Table A.3 (Architecture) and Table A.4 (Implementation)**:
- Traceability from FMEA failure modes to Hazard Log entries
- Traceability from mitigation actions to design requirements
- Traceability from failure modes to test cases

**Traceability Chain**:
```
FMEA Failure Mode → Hazard Log Entry → Safety Requirement → Design → Implementation → Test Case
```

### 10.2 FMEA to Hazard Mapping

**Rule**: Each FMEA end effect with Severity ≥ 7 (Critical/Catastrophic) SHALL be linked to a Hazard Log entry.

**Example Mapping**:

| FMEA Failure Mode | FMEA End Effect | Hazard ID | Hazard Description |
|-------------------|-----------------|-----------|-------------------|
| SPD-001: Speed calculation overflow | Train exceeds limit, derailment | HAZ-SPD-001 | Train overspeed on curve |
| SPD-006: Overspeed detection false negative | Train exceeds limit undetected | HAZ-SPD-001 | Train overspeed on curve |
| ALM-001: Critical alarm not raised | Operator unaware of danger | HAZ-OPR-003 | Operator unable to respond to emergency |
| CAN-001: Brake command not sent | Collision, casualties | HAZ-BRK-001 | Train fails to brake |

### 10.3 Creating Traceability Links

**Command Syntax**:
```bash
workspace.py trace create \
    --from fmea \
    --to hazard \
    --source-id <FMEA-ID-FMXX> \
    --target-id <HAZ-XXX-NNN> \
    --rationale "<Brief explanation of linkage>"
```

**Example Commands**:
```bash
# Speed calculation overflow → Overspeed hazard
workspace.py trace create \
    --from fmea \
    --to hazard \
    --source-id FMEA-SPD-001-FM01 \
    --target-id HAZ-SPD-001 \
    --rationale "Speed calculation overflow can cause train overspeed, leading to derailment on curves"

# Alarm not raised → Operator response hazard
workspace.py trace create \
    --from fmea \
    --to hazard \
    --source-id FMEA-ALM-001-FM01 \
    --target-id HAZ-OPR-003 \
    --rationale "Critical alarm not raised prevents operator from responding to emergency situation"

# Brake command not sent → Brake failure hazard
workspace.py trace create \
    --from fmea \
    --to hazard \
    --source-id FMEA-CAN-001-FM01 \
    --target-id HAZ-BRK-001 \
    --rationale "CAN timeout causes brake command not to be sent, train cannot stop"
```

### 10.4 Mitigation to Design Requirement Traceability

**Rule**: Each FMEA mitigation action SHALL be traced to a design requirement.

**Example**:
```bash
# Mitigation: Add sensor health monitoring
workspace.py trace create \
    --from fmea \
    --to requirements \
    --source-id FMEA-SPD-001-MIT01 \
    --target-id REQ-SAFE-042 \
    --rationale "FMEA mitigation SPD-002 requires sensor health monitoring per REQ-SAFE-042"

# Mitigation: Add duplicate alarm detection
workspace.py trace create \
    --from fmea \
    --to requirements \
    --source-id FMEA-ALM-003-MIT01 \
    --target-id REQ-SAFE-067 \
    --rationale "FMEA mitigation ALM-003 requires duplicate alarm detection per REQ-SAFE-067"
```

### 10.5 Validation of Traceability

**Verify Complete Traceability**:
```bash
# Validate all FMEA failure modes with S ≥ 7 are linked to hazards
workspace.py trace validate \
    --phase fmea \
    --sil 3 \
    --check-completeness

# Expected output:
# ✓ All critical FMEA failure modes (S ≥ 7) linked to Hazard Log
# ✓ All FMEA mitigations linked to design requirements
# ! Warning: FMEA-CAN-006-FM01 (S=9) has no hazard link
```

### 10.6 FMEA Report Integration in Hazard Log

**Update Hazard Log with FMEA Results**:

```markdown
### Hazard HAZ-SPD-001: Train Overspeed on Curve

**Severity**: Catastrophic  
**Likelihood**: Remote (with mitigations)  
**Risk**: MEDIUM (after mitigation)  
**SIL Allocation**: SIL 3

**Related FMEA Failure Modes**:
- FMEA-SPD-001-FM01: Speed calculation overflow (RPN=162)
- FMEA-SPD-001-FM06: Overspeed detection false negative (RPN=180)

**Mitigations Derived from FMEA**:
- REQ-SAFE-040: Speed calculation SHALL use uint32_t to prevent overflow
- REQ-SAFE-041: Speed value SHALL be saturated at MAX_SPEED_KMH
- REQ-SAFE-042: Overspeed detection threshold SHALL include 10% safety margin
```

---

## 11. Tool Integration

### 11.1 Python FMEA Worksheet Generator

**Script**: `tools/fmea/fmea_worksheet_generator.py`

```python
#!/usr/bin/env python3
"""
FMEA Worksheet Generator for EN 50128 Railway Software

Generates FMEA worksheet CSV from component specification.
Provides severity/occurrence/detection rating assistance.
Calculates RPN and prioritizes failure modes.
"""

import csv
import sys
from typing import List, Dict
from dataclasses import dataclass

@dataclass
class FailureMode:
    """FMEA Failure Mode"""
    item: str
    function: str
    failure_mode: str
    local_effect: str
    system_effect: str
    end_effect: str
    severity: int
    cause: str
    occurrence: int
    detection_method: str
    detection: int
    rpn: int
    mitigation: str
    responsibility: str
    status: str

class FMEAWorksheet:
    """FMEA Worksheet Manager"""
    
    def __init__(self, component: str, sil_level: int):
        self.component = component
        self.sil_level = sil_level
        self.failure_modes: List[FailureMode] = []
    
    def add_failure_mode(self, fm: FailureMode):
        """Add failure mode to worksheet"""
        fm.rpn = fm.severity * fm.occurrence * fm.detection
        self.failure_modes.append(fm)
    
    def sort_by_rpn(self):
        """Sort failure modes by RPN (descending)"""
        self.failure_modes.sort(key=lambda x: x.rpn, reverse=True)
    
    def filter_high_rpn(self, threshold: int = 100) -> List[FailureMode]:
        """Return failure modes with RPN > threshold"""
        return [fm for fm in self.failure_modes if fm.rpn > threshold]
    
    def export_csv(self, filename: str):
        """Export FMEA worksheet to CSV"""
        with open(filename, 'w', newline='') as csvfile:
            fieldnames = ['Item', 'Function', 'Failure Mode', 'Local Effect',
                         'System Effect', 'End Effect', 'Severity', 'Cause',
                         'Occurrence', 'Detection Method', 'Detection', 'RPN',
                         'Mitigation', 'Responsibility', 'Status']
            writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
            
            writer.writeheader()
            for fm in self.failure_modes:
                writer.writerow({
                    'Item': fm.item,
                    'Function': fm.function,
                    'Failure Mode': fm.failure_mode,
                    'Local Effect': fm.local_effect,
                    'System Effect': fm.system_effect,
                    'End Effect': fm.end_effect,
                    'Severity': fm.severity,
                    'Cause': fm.cause,
                    'Occurrence': fm.occurrence,
                    'Detection Method': fm.detection_method,
                    'Detection': fm.detection,
                    'RPN': fm.rpn,
                    'Mitigation': fm.mitigation,
                    'Responsibility': fm.responsibility,
                    'Status': fm.status
                })
        print(f"✓ FMEA worksheet exported to {filename}")
    
    def generate_report(self, filename: str):
        """Generate FMEA summary report (Markdown)"""
        with open(filename, 'w') as f:
            f.write(f"# FMEA Report: {self.component}\n\n")
            f.write(f"**SIL Level**: {self.sil_level}\n")
            f.write(f"**Date**: {datetime.now().strftime('%Y-%m-%d')}\n\n")
            
            f.write(f"## Summary Statistics\n\n")
            f.write(f"- Total Failure Modes: {len(self.failure_modes)}\n")
            f.write(f"- Average RPN: {sum(fm.rpn for fm in self.failure_modes) / len(self.failure_modes):.1f}\n")
            
            high_rpn = len([fm for fm in self.failure_modes if fm.rpn > 100])
            f.write(f"- High RPN (> 100): {high_rpn} ({high_rpn*100//len(self.failure_modes)}%)\n")
            
            critical = len([fm for fm in self.failure_modes if fm.severity >= 8])
            f.write(f"- Critical Severity (≥ 8): {critical} ({critical*100//len(self.failure_modes)}%)\n\n")
            
            f.write(f"## Prioritized Failure Modes\n\n")
            f.write("| Item | Failure Mode | S | O | D | RPN | Mitigation |\n")
            f.write("|------|--------------|---|---|---|-----|------------|\n")
            
            for fm in sorted(self.failure_modes, key=lambda x: x.rpn, reverse=True):
                f.write(f"| {fm.item} | {fm.failure_mode} | {fm.severity} | "
                       f"{fm.occurrence} | {fm.detection} | **{fm.rpn}** | "
                       f"{fm.mitigation} |\n")
        
        print(f"✓ FMEA report generated: {filename}")

def main():
    """Example usage"""
    if len(sys.argv) < 3:
        print("Usage: fmea_worksheet_generator.py <component> <sil_level>")
        sys.exit(1)
    
    component = sys.argv[1]
    sil_level = int(sys.argv[2])
    
    # Create FMEA worksheet
    fmea = FMEAWorksheet(component, sil_level)
    
    # Add failure modes (example for speed monitor)
    fmea.add_failure_mode(FailureMode(
        item="SPD-001",
        function="get_speed()",
        failure_mode="Returns incorrect speed (50% high)",
        local_effect="Speed variable wrong",
        system_effect="Wrong speed displayed, ATP receives wrong value",
        end_effect="Train may exceed limit undetected",
        severity=9,
        cause="Integer overflow in calculation",
        occurrence=6,
        detection_method="Range check assertion",
        detection=3,
        rpn=0,  # Will be calculated
        mitigation="Use uint32_t for calc, saturate at max",
        responsibility="IMP",
        status="Open"
    ))
    
    # Sort by RPN
    fmea.sort_by_rpn()
    
    # Export
    fmea.export_csv(f"FMEA-{component}.csv")
    fmea.generate_report(f"FMEA-{component}-report.md")

if __name__ == "__main__":
    from datetime import datetime
    main()
```

**Usage**:
```bash
# Generate FMEA worksheet for speed monitor (SIL 3)
python3 tools/fmea/fmea_worksheet_generator.py speed_monitor 3

# Output:
# ✓ FMEA worksheet exported to FMEA-speed_monitor.csv
# ✓ FMEA report generated: FMEA-speed_monitor-report.md
```

### 11.2 RPN Calculator and Prioritizer

**Script**: `tools/fmea/rpn_calculator.py`

```python
#!/usr/bin/env python3
"""
RPN Calculator for FMEA

Calculates RPN from severity, occurrence, detection ratings.
Identifies high-priority failure modes.
Suggests mitigation strategies based on S/O/D values.
"""

def calculate_rpn(severity: int, occurrence: int, detection: int) -> int:
    """Calculate RPN = S × O × D"""
    if not (1 <= severity <= 10 and 1 <= occurrence <= 10 and 1 <= detection <= 10):
        raise ValueError("S, O, D must be in range [1, 10]")
    return severity * occurrence * detection

def get_priority(rpn: int) -> str:
    """Get priority level from RPN"""
    if rpn >= 800:
        return "CRITICAL"
    elif rpn >= 400:
        return "HIGH"
    elif rpn >= 200:
        return "MEDIUM"
    elif rpn >= 100:
        return "LOW"
    else:
        return "MINIMAL"

def suggest_mitigation(severity: int, occurrence: int, detection: int) -> str:
    """Suggest mitigation strategy based on S/O/D"""
    if severity >= 8:
        if occurrence >= 6:
            return "URGENT: Reduce occurrence through design change + defensive programming"
        elif detection >= 6:
            return "URGENT: Improve detection (add assertions, checks, tests)"
        else:
            return "Monitor: Acceptable with current detection"
    elif occurrence >= 7 and detection >= 7:
        return "Improve detection: Add runtime checks, increase test coverage"
    elif occurrence >= 7:
        return "Reduce occurrence: Simplify design, increase code review"
    elif detection >= 7:
        return "Improve detection: Add assertions, static analysis rules"
    else:
        return "No immediate action required"

def main():
    """Interactive RPN calculator"""
    import sys
    
    if len(sys.argv) == 4:
        s = int(sys.argv[1])
        o = int(sys.argv[2])
        d = int(sys.argv[3])
    else:
        print("RPN Calculator for FMEA")
        print("=" * 40)
        s = int(input("Enter Severity (1-10): "))
        o = int(input("Enter Occurrence (1-10): "))
        d = int(input("Enter Detection (1-10): "))
    
    rpn = calculate_rpn(s, o, d)
    priority = get_priority(rpn)
    mitigation = suggest_mitigation(s, o, d)
    
    print(f"\n{'='*40}")
    print(f"RPN = {s} × {o} × {d} = {rpn}")
    print(f"Priority: {priority}")
    print(f"{'='*40}")
    print(f"Suggested Mitigation:")
    print(f"  {mitigation}")
    print(f"{'='*40}\n")

if __name__ == "__main__":
    main()
```

**Usage**:
```bash
# Calculate RPN interactively
python3 tools/fmea/rpn_calculator.py

# Or with command-line arguments
python3 tools/fmea/rpn_calculator.py 9 6 3
# Output:
# RPN = 9 × 6 × 3 = 162
# Priority: MEDIUM
# Suggested Mitigation: URGENT: Improve detection (add assertions, checks, tests)
```

### 11.3 Traceability Management with workspace.py

**Create FMEA → Hazard Traceability**:
```bash
# Batch create traceability links from FMEA CSV
python3 tools/fmea/create_fmea_traceability.py \
    --fmea-csv docs/fmea/FMEA-SPD-001.csv \
    --hazard-log docs/hazards/HAZARD_LOG.md \
    --output evidence/traceability/fmea-to-hazard.json

# Validate FMEA traceability completeness
workspace.py trace validate \
    --phase fmea \
    --sil 3 \
    --check-completeness \
    --output evidence/verification/fmea-traceability-report.md

# Generate FMEA traceability report
workspace.py trace report \
    --from fmea \
    --to validation \
    --format markdown \
    --output evidence/traceability/fmea-full-traceability.md
```

### 11.4 Workflow Management with workspace.py

**Submit FMEA Report for Review**:
```bash
# Submit FMEA report to QUA for review
workspace.py wf submit \
    --deliverable DOC-SAF-FMEA-001 \
    --phase safety-analysis \
    --author "Safety Engineer (SAF)" \
    --sil 3

# QUA reviews FMEA report
workspace.py wf review \
    --deliverable DOC-SAF-FMEA-001 \
    --reviewer QUA \
    --status approved \
    --comments "FMEA complete, all critical failure modes addressed"

# Check FMEA workflow status
workspace.py wf status --deliverable DOC-SAF-FMEA-001
```

**Example Output**:
```
FMEA Report Workflow Status
============================
Deliverable: DOC-SAF-FMEA-001
Phase: safety-analysis
Status: APPROVED
Author: Safety Engineer (SAF)
Reviewer: QUA
Review Date: 2026-03-14
Comments: FMEA complete, all critical failure modes addressed

Next Steps:
- Implement mitigations per FMEA recommendations
- Update design documents with mitigation requirements
- Create traceability links: FMEA → Requirements
```

---

## 12. Example Scenario: Door Control FMEA

### 12.1 Scenario Context

**Component**: Door Control System (`door_control.c`)  
**SIL Level**: 3  
**Safety Function**: Prevent door opening while train moving  
**Critical Requirement**: REQ-SAFE-DOOR-001: Doors SHALL remain locked when train speed > 5 km/h

### 12.2 Functions Analyzed

1. `get_door_state()` - Returns current door state (CLOSED, LOCKED, UNLOCKED, OPENING, OPEN)
2. `lock_door()` - Engages door lock mechanism
3. `unlock_door()` - Disengages door lock mechanism
4. `open_door()` - Opens door (if unlocked and speed = 0)
5. `close_door()` - Closes door
6. `check_door_interlock()` - Verifies door-speed interlock active

### 12.3 Complete FMEA Worksheet

| Item | Function | Failure Mode | Local Effect | System Effect | End Effect | S | Cause | O | Detection | D | RPN | Mitigation |
|------|----------|--------------|--------------|---------------|------------|---|-------|---|-----------|---|-----|------------|
| **DOOR-001** | check_door_interlock() | Returns FALSE when speed > 5 km/h | Interlock check passes | Door unlock allowed while moving | **Passenger falls out, fatality** | **10** | Logic error (wrong comparison) | 4 | Unit test catches | 5 | **200** | Add comprehensive unit tests, code review |
| **DOOR-002** | unlock_door() | Unlocks door without speed check | Door unlocked | Door can open while moving | **Passenger falls out, fatality** | **10** | Missing interlock check | 3 | Integration test catches | 6 | **180** | Add mandatory interlock check, assertion |
| **DOOR-003** | open_door() | Opens door despite lock engaged | Door opens with force | Lock mechanism damaged, door opens | **Door opens while moving, fatality** | **10** | State machine error | 3 | State validation catches | 5 | **150** | Add state validation, mechanical safety |
| **DOOR-004** | get_door_state() | Returns LOCKED when actually UNLOCKED | State variable wrong | System thinks door locked | Door opens unexpectedly | **9** | State corruption (memory) | 4 | Sensor cross-check | 4 | **144** | Add hardware sensor, cross-check |
| **DOOR-005** | lock_door() | Fails to engage lock | Lock not engaged | Door appears locked but isn't | Door opens while moving | **10** | Actuator failure | 5 | Lock sensor detects | 3 | **150** | Add lock sensor feedback verification |
| **DOOR-006** | open_door() | Spurious door opening | Door opens | Unexpected door open | Passenger surprise, minor injury | **6** | Race condition, interrupt | 5 | Operator observes | 8 | **240** | Add open command confirmation, atomic ops |
| **DOOR-007** | close_door() | Door fails to close | Door remains open | Train cannot depart | Service delay, no safety impact | **3** | Obstruction, actuator fault | 6 | Door sensor detects | 4 | **72** | Add retry logic, operator notification |
| **DOOR-008** | check_door_interlock() | Delayed execution (> 50ms) | Timing violation | Stale speed data used | Door unlocked with outdated speed info | **8** | Task overrun, low priority | 5 | Timing monitor | 5 | **200** | Increase task priority, reduce complexity |
| **DOOR-009** | unlock_door() | Data corruption (state variable) | Door state corrupted | Invalid state transition | System enters fail-safe (all doors locked) | **5** | Buffer overflow, wild pointer | 4 | Watchdog reset | 6 | **120** | Add bounds checking, stack canaries |
| **DOOR-010** | lock_door() | Lock command not sent (CAN timeout) | Command lost | Lock not engaged remotely | Door opens at remote station | **9** | CAN bus overload | 5 | Timeout detection | 4 | **180** | Add command acknowledgment, retry |

### 12.4 FMEA Summary

**Statistics**:
- Total Failure Modes: 10
- Average RPN: 164
- High RPN (> 150): 6 (60%)
- Critical Severity (S ≥ 8): 8 (80%)
- **Highest RPN**: DOOR-006 (Spurious door opening, RPN=240)

**Critical Findings**:
1. **Four failure modes with Severity = 10** (Catastrophic - potential fatality)
2. **Six failure modes with RPN > 150** (require urgent mitigation)
3. **Primary hazard**: Door opens while train moving (linked to HAZ-DOOR-001)

### 12.5 Mitigation Plan

**Immediate Actions (RPN > 200)**:

1. **DOOR-001 (RPN=200)**: Interlock logic error
   - **Mitigation**: Add comprehensive unit tests covering all speed/state combinations
   - **Verification**: Achieve 100% branch coverage for `check_door_interlock()`
   - **Timeline**: 1 week
   - **Responsibility**: IMP + TST

2. **DOOR-006 (RPN=240)**: Spurious door opening
   - **Mitigation**: Add two-button confirmation for door open command
   - **Mitigation**: Use atomic operations for door state changes
   - **Verification**: Race condition testing with fault injection
   - **Timeline**: 2 weeks
   - **Responsibility**: DES + IMP

3. **DOOR-008 (RPN=200)**: Timing violation
   - **Mitigation**: Increase task priority to highest (except watchdog)
   - **Mitigation**: Reduce function complexity (split into smaller functions)
   - **Verification**: Timing analysis confirms < 20ms worst-case
   - **Timeline**: 1 week
   - **Responsibility**: IMP + VER

**High Priority (RPN 150-199)**:

4. **DOOR-002, DOOR-003, DOOR-005, DOOR-010**: See detailed mitigation plan in FMEA report

### 12.6 Hazard Log Integration

**Link FMEA Failure Modes to Hazard**:

```bash
# Primary hazard: Door opens while train moving
workspace.py trace create --from fmea --to hazard \
    --source-id FMEA-DOOR-001 --target-id HAZ-DOOR-001 \
    --rationale "Interlock failure allows door unlock while moving"

workspace.py trace create --from fmea --to hazard \
    --source-id FMEA-DOOR-002 --target-id HAZ-DOOR-001 \
    --rationale "Missing speed check allows door unlock while moving"

workspace.py trace create --from fmea --to hazard \
    --source-id FMEA-DOOR-003 --target-id HAZ-DOOR-001 \
    --rationale "State machine error allows door open despite lock"

workspace.py trace create --from fmea --to hazard \
    --source-id FMEA-DOOR-005 --target-id HAZ-DOOR-001 \
    --rationale "Lock actuation failure leaves door unlocked"

# Validate traceability completeness
workspace.py trace validate --phase fmea --sil 3 --check-completeness
```

### 12.7 Updated Hazard Log Entry

```markdown
### Hazard HAZ-DOOR-001: Door Opens While Train Moving

**Severity**: Catastrophic (Potential fatality)  
**Initial Likelihood**: Occasional (10^-5 per hour)  
**Initial Risk**: HIGH  
**Target Likelihood**: Remote (10^-7 per hour)  
**Target Risk**: MEDIUM  
**SIL Allocation**: SIL 3

**Related FMEA Failure Modes**:
- FMEA-DOOR-001: Interlock logic error (RPN=200) ← **Requires urgent mitigation**
- FMEA-DOOR-002: Missing speed check (RPN=180) ← **Requires urgent mitigation**
- FMEA-DOOR-003: State machine error (RPN=150)
- FMEA-DOOR-005: Lock engagement failure (RPN=150)

**Mitigations**:
- REQ-SAFE-DOOR-001: Doors SHALL remain locked when speed > 5 km/h
- REQ-SAFE-DOOR-002: Door unlock SHALL verify interlock active (from FMEA-DOOR-002)
- REQ-SAFE-DOOR-003: Door open SHALL verify state is UNLOCKED (from FMEA-DOOR-003)
- REQ-SAFE-DOOR-004: Lock engagement SHALL be verified by sensor (from FMEA-DOOR-005)
- REQ-SAFE-DOOR-005: Door open command SHALL require two-button confirmation (from FMEA-DOOR-006)

**Verification**:
- Unit tests: 100% coverage of interlock logic
- Integration tests: Door-speed interlock testing with fault injection
- System tests: Operational scenarios with speed variations
```

### 12.8 Generate FMEA Report

```bash
# Create FMEA worksheet CSV
python3 tools/fmea/fmea_worksheet_generator.py door_control 3

# Generate prioritized report
python3 tools/fmea/rpn_calculator.py --analyze FMEA-door_control.csv

# Submit FMEA report for review
workspace.py wf submit \
    --deliverable DOC-SAF-FMEA-DOOR-001 \
    --phase safety-analysis \
    --author "SAF" \
    --sil 3

# Generate traceability report
workspace.py trace report \
    --from fmea \
    --to validation \
    --format markdown \
    --output evidence/traceability/fmea-door-control-trace.md
```

---

## Summary

This FMEA workflow provides:

1. **Systematic Failure Analysis**: 8 software-specific failure mode categories
2. **Quantitative Risk Assessment**: S/O/D ratings and RPN calculation
3. **Prioritization**: RPN-based prioritization with SIL-specific thresholds
4. **Mitigation Strategies**: Design changes, software measures, detection improvements
5. **Traceability**: FMEA → Hazard Log → Requirements integration
6. **Tool Support**: Python scripts for worksheet generation, RPN calculation, traceability
7. **EN 50128 Compliance**: Highly Recommended for SIL 2+, independent review for SIL 3-4

**Key Takeaways**:
- FMEA is bottom-up (component → system), complements top-down FTA
- RPN prioritizes mitigation efforts, but Severity ≥ 8 always requires action
- Easiest mitigation: Improve detection (add checks, assertions, tests)
- Complete traceability: FMEA → Hazard → Requirement → Test
- FMEA is iterative: Update after design changes, new defects, operational experience

**Next Workflow**: Fault Tree Analysis (FTA) - Top-down analysis of system-level hazards

---

**End of FMEA Workflow**
