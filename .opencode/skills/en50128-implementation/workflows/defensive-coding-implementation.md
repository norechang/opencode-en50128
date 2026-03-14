# Defensive Coding Implementation Workflow

**Skill**: en50128-implementation  
**Role**: Implementer (IMP)  
**Phase**: Implementation & Testing (Phase 4)  
**EN 50128 Reference**: Section 7.3 Table A.3 (Technique 2: Defensive Programming - HR for SIL 3-4)

---

## Purpose

This workflow guides the implementation of defensive programming patterns in C code for EN 50128 railway safety software. Defensive programming is **Highly Recommended** for SIL 3-4 per EN 50128 Table A.3 Technique 2.

**Key Objectives**:
- Detect and handle all possible error conditions
- Validate all inputs at module boundaries
- Protect against hardware faults and transient errors
- Implement fail-safe behavior
- Produce robust, fault-tolerant code

**Definition** (EN 50128 Annex D.14):
> "Defensive programming is a form of defensive design intended to ensure the continuing function of a piece of software in spite of unforeseeable usage of said software."

---

## Prerequisites

### Required Inputs
- [ ] Software Design Specification (DOC-10) with defensive programming requirements
- [ ] Hazard Log (safety-critical functions identified)
- [ ] Error handling strategy defined
- [ ] Fault detection requirements

### Required Knowledge
- EN 50128 Table A.3 defensive programming techniques
- MISRA C:2012 defensive programming rules
- Common C pitfalls and vulnerabilities
- Hardware fault modes (if applicable)

### Reference
See `../resources/defensive-programming-patterns.md` for 18 detailed patterns from design phase.

---

## Defensive Programming Principles

### 1. Assume Nothing
- **Never trust** inputs from external sources
- **Validate** all function parameters
- **Check** all return values
- **Verify** all assumptions with assertions

### 2. Explicit Error Handling
- **No silent failures** - always return error status
- **Propagate errors** up the call stack
- **Log all errors** for diagnostics
- **Enter safe state** on critical errors

### 3. Redundancy and Checking
- **Double-check critical values**
- **Use voting algorithms** for redundant sensors
- **Verify calculations** with inverse operations
- **Detect memory corruption** with checksums

### 4. Fail-Safe Design
- **Default to safe state** on error
- **Watchdog timers** for hang detection
- **Timeout mechanisms** for all operations
- **Graceful degradation** when possible

---

## Pattern 1: Input Validation

### 1.1 NULL Pointer Checks (Mandatory)

**Every function MUST check pointer parameters for NULL**:

```c
/**
 * @brief Process sensor data with full defensive checks
 * @param[in]  sensor_data Pointer to sensor data structure
 * @param[out] result      Pointer to result structure
 * @return SUCCESS or error code
 */
error_t process_sensor_data(const sensor_data_t* sensor_data, 
                            result_t* result)
{
    error_t status;
    
    /* DEFENSIVE: NULL pointer checks */
    if (sensor_data == NULL) {
        safety_log("process_sensor_data: NULL sensor_data");
        return ERROR_NULL_POINTER;
    }
    
    if (result == NULL) {
        safety_log("process_sensor_data: NULL result");
        return ERROR_NULL_POINTER;
    }
    
    /* DEFENSIVE: Validate sensor data structure integrity */
    if (sensor_data->magic != SENSOR_DATA_MAGIC) {
        safety_log("process_sensor_data: corrupted structure");
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Process validated inputs */
    status = perform_processing(sensor_data, result);
    
    return status;
}
```

**Why**: 
- Dereferencing NULL pointer causes undefined behavior (MISRA Rule 1.3)
- SIL 3-4 requires detection of all possible failures

### 1.2 Range Validation

```c
/**
 * @brief Set motor speed with range validation
 * @param[in] speed_rpm Requested speed in RPM
 * @return SUCCESS or error code
 */
error_t motor_set_speed(uint16_t speed_rpm)
{
    error_t status;
    
    /* DEFENSIVE: Range validation */
    if (speed_rpm > MOTOR_MAX_SPEED_RPM) {
        safety_log("motor_set_speed: speed exceeds maximum");
        return ERROR_OUT_OF_RANGE;
    }
    
    if (speed_rpm < MOTOR_MIN_SPEED_RPM) {
        safety_log("motor_set_speed: speed below minimum");
        return ERROR_OUT_OF_RANGE;
    }
    
    /* DEFENSIVE: Check motor is ready */
    if (motor_state != MOTOR_STATE_READY) {
        safety_log("motor_set_speed: motor not ready");
        return ERROR_INVALID_STATE;
    }
    
    /* Safe to set speed */
    status = hardware_set_motor_speed(speed_rpm);
    
    if (status != SUCCESS) {
        safety_log("motor_set_speed: hardware failure");
        /* Enter safe state */
        (void)motor_emergency_stop();
    }
    
    return status;
}
```

### 1.3 Plausibility Checks

```c
/**
 * @brief Validate temperature sensor reading for plausibility
 * @param[in] temp_celsius Temperature reading in Celsius
 * @return true if plausible, false otherwise
 */
static bool is_temperature_plausible(int16_t temp_celsius)
{
    bool plausible = false;
    
    /* DEFENSIVE: Physical plausibility */
    if ((temp_celsius >= TEMP_PHYSICAL_MIN) && 
        (temp_celsius <= TEMP_PHYSICAL_MAX)) {
        
        /* DEFENSIVE: Rate of change check */
        static int16_t last_temp = TEMP_NOMINAL;
        int16_t delta = temp_celsius - last_temp;
        
        if ((delta >= -TEMP_MAX_DELTA) && (delta <= TEMP_MAX_DELTA)) {
            plausible = true;
            last_temp = temp_celsius;
        } else {
            safety_log("Temperature rate of change too high");
        }
    } else {
        safety_log("Temperature out of physical range");
    }
    
    return plausible;
}
```

**Plausibility Dimensions**:
- Physical limits (e.g., temperature -40°C to +85°C)
- Rate of change (delta from previous value)
- Correlation with other sensors
- Historical patterns

### 1.4 Array Bounds Checking

```c
/**
 * @brief Read element from circular buffer with bounds checking
 * @param[in]  buffer Pointer to circular buffer
 * @param[in]  index  Index to read [0..BUFFER_SIZE-1]
 * @param[out] value  Pointer to output value
 * @return SUCCESS or error code
 */
error_t buffer_read(const circular_buffer_t* buffer, 
                   uint16_t index, 
                   uint8_t* value)
{
    error_t status;
    
    /* DEFENSIVE: NULL checks */
    if ((buffer == NULL) || (value == NULL)) {
        return ERROR_NULL_POINTER;
    }
    
    /* DEFENSIVE: Bounds check */
    if (index >= BUFFER_SIZE) {
        safety_log("buffer_read: index out of bounds");
        return ERROR_OUT_OF_RANGE;
    }
    
    /* DEFENSIVE: Buffer consistency check */
    if (buffer->count > BUFFER_SIZE) {
        safety_log("buffer_read: buffer corrupted (count > size)");
        return ERROR_BUFFER_CORRUPTED;
    }
    
    /* Safe to access array */
    *value = buffer->data[index];
    status = SUCCESS;
    
    return status;
}
```

---

## Pattern 2: Return Value Checking

### 2.1 Always Check Return Values (MISRA Rule 17.7)

**FORBIDDEN: Ignoring return values**:
```c
/* MISRA Rule 17.7 violation */
calculate_speed(sensor_data);  /* Return value ignored */
set_brake_level(50U);          /* Error not detected */
```

**REQUIRED: Check all return values**:
```c
error_t status;

/* DEFENSIVE: Check return value */
status = calculate_speed(sensor_data, &speed);
if (status != SUCCESS) {
    safety_log("Speed calculation failed");
    return status;
}

/* DEFENSIVE: Check return value */
status = set_brake_level(50U);
if (status != SUCCESS) {
    safety_log("Brake setting failed");
    /* Enter safe state */
    (void)activate_emergency_brake();
    return status;
}
```

### 2.2 Error Propagation Pattern

```c
/**
 * @brief Multi-step process with error propagation
 */
error_t complex_operation(const input_t* input, output_t* output)
{
    error_t status;
    intermediate_t temp;
    
    /* DEFENSIVE: Check inputs */
    if ((input == NULL) || (output == NULL)) {
        return ERROR_NULL_POINTER;
    }
    
    /* Step 1: Validate input */
    status = validate_input(input);
    if (status != SUCCESS) {
        safety_log("Input validation failed");
        return status;  /* Propagate error */
    }
    
    /* Step 2: Perform calculation */
    status = calculate_intermediate(input, &temp);
    if (status != SUCCESS) {
        safety_log("Calculation failed");
        return status;  /* Propagate error */
    }
    
    /* Step 3: Generate output */
    status = generate_output(&temp, output);
    if (status != SUCCESS) {
        safety_log("Output generation failed");
        return status;  /* Propagate error */
    }
    
    return SUCCESS;
}
```

### 2.3 Nested Function Calls

```c
/**
 * @brief Call chain with defensive error handling
 */
error_t high_level_operation(void)
{
    error_t status;
    
    /* DEFENSIVE: Explicit intermediate variable */
    status = level_2_operation();
    if (status != SUCCESS) {
        safety_log("level_2_operation failed with code %d", status);
        return status;
    }
    
    /* Continue only if previous succeeded */
    status = another_level_2_operation();
    if (status != SUCCESS) {
        safety_log("another_level_2_operation failed");
        return status;
    }
    
    return SUCCESS;
}
```

---

## Pattern 3: Safe Arithmetic Operations

### 3.1 Integer Overflow Detection

```c
/**
 * @brief Safe addition with overflow detection
 * @param[in]  a First operand
 * @param[in]  b Second operand
 * @param[out] result Pointer to result
 * @return SUCCESS or ERROR_OUT_OF_RANGE if overflow
 */
error_t safe_add_u32(uint32_t a, uint32_t b, uint32_t* result)
{
    error_t status;
    
    /* DEFENSIVE: NULL check */
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* DEFENSIVE: Overflow check before operation */
    if (a > (UINT32_MAX - b)) {
        safety_log("safe_add_u32: overflow detected");
        *result = UINT32_MAX;  /* Saturate to max */
        status = ERROR_OUT_OF_RANGE;
    } else {
        *result = a + b;
        status = SUCCESS;
    }
    
    return status;
}

/**
 * @brief Safe multiplication with overflow detection
 */
error_t safe_multiply_u32(uint32_t a, uint32_t b, uint32_t* result)
{
    error_t status;
    
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* DEFENSIVE: Check for overflow */
    if ((a != 0U) && (b > (UINT32_MAX / a))) {
        safety_log("safe_multiply_u32: overflow detected");
        *result = UINT32_MAX;
        status = ERROR_OUT_OF_RANGE;
    } else {
        *result = a * b;
        status = SUCCESS;
    }
    
    return status;
}
```

### 3.2 Division by Zero Protection

```c
/**
 * @brief Safe division with zero check
 */
error_t safe_divide_i32(int32_t numerator, 
                       int32_t denominator, 
                       int32_t* result)
{
    error_t status;
    
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* DEFENSIVE: Division by zero check */
    if (denominator == 0) {
        safety_log("safe_divide_i32: division by zero");
        *result = 0;
        status = ERROR_INVALID_PARAMETER;
    } 
    /* DEFENSIVE: Integer overflow check (INT_MIN / -1) */
    else if ((numerator == INT32_MIN) && (denominator == -1)) {
        safety_log("safe_divide_i32: division overflow");
        *result = INT32_MAX;
        status = ERROR_OUT_OF_RANGE;
    } 
    else {
        *result = numerator / denominator;
        status = SUCCESS;
    }
    
    return status;
}
```

### 3.3 Saturation Arithmetic

```c
/**
 * @brief Add with saturation (no overflow error)
 */
uint32_t saturating_add_u32(uint32_t a, uint32_t b)
{
    uint32_t result;
    
    /* DEFENSIVE: Saturate to maximum on overflow */
    if (a > (UINT32_MAX - b)) {
        result = UINT32_MAX;
        safety_log("saturating_add_u32: saturated to max");
    } else {
        result = a + b;
    }
    
    return result;
}
```

---

## Pattern 4: Hardware Fault Detection

### 4.1 Watchdog Timer Implementation

```c
/**
 * @brief Watchdog refresh with fault detection
 */
error_t watchdog_refresh(void)
{
    static uint32_t last_refresh_time = 0U;
    uint32_t current_time;
    uint32_t delta;
    error_t status;
    
    current_time = system_get_time_ms();
    
    /* DEFENSIVE: Check for time wraparound */
    if (current_time >= last_refresh_time) {
        delta = current_time - last_refresh_time;
    } else {
        /* Wraparound occurred */
        delta = (UINT32_MAX - last_refresh_time) + current_time + 1U;
    }
    
    /* DEFENSIVE: Check refresh interval */
    if (delta < WATCHDOG_MIN_INTERVAL_MS) {
        safety_log("Watchdog refreshed too frequently");
        status = ERROR_TIMING;
    } else if (delta > WATCHDOG_MAX_INTERVAL_MS) {
        safety_log("Watchdog refresh interval too long");
        status = ERROR_TIMEOUT;
    } else {
        /* Safe to refresh */
        hardware_watchdog_refresh();
        last_refresh_time = current_time;
        status = SUCCESS;
    }
    
    return status;
}
```

### 4.2 Register Read-Back Verification

```c
/**
 * @brief Write to hardware register with read-back verification
 * @param[in] reg_addr Register address
 * @param[in] value Value to write
 * @return SUCCESS or error code
 */
error_t register_write_verified(volatile uint32_t* reg_addr, uint32_t value)
{
    error_t status;
    uint32_t readback;
    uint8_t retry_count;
    
    /* DEFENSIVE: NULL check */
    if (reg_addr == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* DEFENSIVE: Retry loop for transient errors */
    retry_count = 0U;
    status = ERROR_HARDWARE_FAULT;
    
    while ((retry_count < MAX_HARDWARE_RETRIES) && (status != SUCCESS)) {
        /* Write value */
        *reg_addr = value;
        
        /* DEFENSIVE: Read back and verify */
        readback = *reg_addr;
        
        if (readback == value) {
            status = SUCCESS;
        } else {
            safety_log("Register write verification failed (attempt %u)", 
                      retry_count + 1U);
            retry_count++;
            
            /* Small delay before retry */
            hardware_delay_us(RETRY_DELAY_US);
        }
    }
    
    if (status != SUCCESS) {
        safety_log("Register write failed after %u retries", MAX_HARDWARE_RETRIES);
    }
    
    return status;
}
```

### 4.3 Memory Corruption Detection

```c
/**
 * @brief Structure with integrity checking
 */
typedef struct {
    uint32_t magic_start;      /* Magic number at start */
    /* Data fields */
    uint16_t temperature;
    uint16_t pressure;
    uint8_t  status;
    /* Checksum at end */
    uint32_t checksum;
    uint32_t magic_end;        /* Magic number at end */
} sensor_data_t;

#define SENSOR_DATA_MAGIC_START  (0x12345678UL)
#define SENSOR_DATA_MAGIC_END    (0x87654321UL)

/**
 * @brief Calculate checksum for sensor data
 */
static uint32_t calculate_checksum(const sensor_data_t* data)
{
    uint32_t sum = 0U;
    
    sum += data->temperature;
    sum += data->pressure;
    sum += data->status;
    
    return sum;
}

/**
 * @brief Validate sensor data structure integrity
 */
error_t validate_sensor_data(const sensor_data_t* data)
{
    error_t status;
    uint32_t calculated_checksum;
    
    if (data == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* DEFENSIVE: Check magic numbers */
    if (data->magic_start != SENSOR_DATA_MAGIC_START) {
        safety_log("Sensor data: start magic corrupted");
        return ERROR_MEMORY_CORRUPTED;
    }
    
    if (data->magic_end != SENSOR_DATA_MAGIC_END) {
        safety_log("Sensor data: end magic corrupted");
        return ERROR_MEMORY_CORRUPTED;
    }
    
    /* DEFENSIVE: Verify checksum */
    calculated_checksum = calculate_checksum(data);
    if (calculated_checksum != data->checksum) {
        safety_log("Sensor data: checksum mismatch");
        return ERROR_MEMORY_CORRUPTED;
    }
    
    status = SUCCESS;
    return status;
}
```

---

## Pattern 5: Redundancy and Cross-Checking

### 5.1 Dual-Channel Redundancy

```c
/**
 * @brief Read redundant sensors with cross-check
 */
error_t read_redundant_speed_sensors(uint16_t* speed)
{
    error_t status;
    uint16_t speed_a;
    uint16_t speed_b;
    uint16_t diff;
    
    if (speed == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* Read both sensors */
    status = sensor_a_read(&speed_a);
    if (status != SUCCESS) {
        safety_log("Sensor A read failed");
        return status;
    }
    
    status = sensor_b_read(&speed_b);
    if (status != SUCCESS) {
        safety_log("Sensor B read failed");
        return status;
    }
    
    /* DEFENSIVE: Cross-check redundant values */
    if (speed_a >= speed_b) {
        diff = speed_a - speed_b;
    } else {
        diff = speed_b - speed_a;
    }
    
    if (diff > SPEED_TOLERANCE_THRESHOLD) {
        safety_log("Speed sensors disagree: A=%u, B=%u", speed_a, speed_b);
        /* Enter safe state */
        (void)activate_emergency_brake();
        return ERROR_SENSOR_MISMATCH;
    }
    
    /* DEFENSIVE: Use average of both sensors */
    *speed = (speed_a + speed_b) / 2U;
    
    return SUCCESS;
}
```

### 5.2 Triple Modular Redundancy (TMR) with Voting

```c
/**
 * @brief Read three redundant sensors and vote
 */
error_t read_tmr_sensors(uint16_t* value)
{
    error_t status;
    uint16_t sensor_1;
    uint16_t sensor_2;
    uint16_t sensor_3;
    uint16_t diff_12;
    uint16_t diff_13;
    uint16_t diff_23;
    
    if (value == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* Read all three sensors */
    status = sensor_read(SENSOR_1, &sensor_1);
    if (status != SUCCESS) {
        safety_log("TMR: Sensor 1 failed");
        return status;
    }
    
    status = sensor_read(SENSOR_2, &sensor_2);
    if (status != SUCCESS) {
        safety_log("TMR: Sensor 2 failed");
        return status;
    }
    
    status = sensor_read(SENSOR_3, &sensor_3);
    if (status != SUCCESS) {
        safety_log("TMR: Sensor 3 failed");
        return status;
    }
    
    /* DEFENSIVE: Majority voting */
    diff_12 = (sensor_1 >= sensor_2) ? (sensor_1 - sensor_2) : (sensor_2 - sensor_1);
    diff_13 = (sensor_1 >= sensor_3) ? (sensor_1 - sensor_3) : (sensor_3 - sensor_1);
    diff_23 = (sensor_2 >= sensor_3) ? (sensor_2 - sensor_3) : (sensor_3 - sensor_2);
    
    /* If 1 and 2 agree */
    if (diff_12 <= TMR_TOLERANCE) {
        *value = (sensor_1 + sensor_2) / 2U;
        if (diff_13 > TMR_TOLERANCE) {
            safety_log("TMR: Sensor 3 disagreement");
        }
        status = SUCCESS;
    }
    /* If 1 and 3 agree */
    else if (diff_13 <= TMR_TOLERANCE) {
        *value = (sensor_1 + sensor_3) / 2U;
        safety_log("TMR: Sensor 2 disagreement");
        status = SUCCESS;
    }
    /* If 2 and 3 agree */
    else if (diff_23 <= TMR_TOLERANCE) {
        *value = (sensor_2 + sensor_3) / 2U;
        safety_log("TMR: Sensor 1 disagreement");
        status = SUCCESS;
    }
    /* No agreement */
    else {
        safety_log("TMR: All sensors disagree");
        status = ERROR_SENSOR_FAULT;
    }
    
    return status;
}
```

### 5.3 Inverse Calculation Verification

```c
/**
 * @brief Calculate with inverse verification
 */
error_t calculate_with_verification(uint32_t input, uint32_t* output)
{
    error_t status;
    uint32_t calculated;
    uint32_t verified;
    
    if (output == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* Forward calculation */
    calculated = complex_calculation(input);
    
    /* DEFENSIVE: Inverse calculation to verify */
    verified = inverse_calculation(calculated);
    
    /* Check if inverse matches original input */
    if (verified != input) {
        safety_log("Calculation verification failed");
        status = ERROR_CALCULATION;
    } else {
        *output = calculated;
        status = SUCCESS;
    }
    
    return status;
}
```

---

## Pattern 6: State Machine Defensive Implementation

### 6.1 Valid State Transition Checking

```c
typedef enum {
    STATE_INIT,
    STATE_IDLE,
    STATE_ACTIVE,
    STATE_ERROR,
    STATE_SAFE
} system_state_t;

typedef struct {
    system_state_t current_state;
    system_state_t previous_state;
    uint32_t state_entry_time;
    uint32_t transition_count;
} state_machine_t;

/**
 * @brief Validate state transition
 */
static bool is_valid_transition(system_state_t from, system_state_t to)
{
    bool valid = false;
    
    /* DEFENSIVE: Explicit state transition table */
    switch (from) {
        case STATE_INIT:
            valid = (to == STATE_IDLE) || (to == STATE_ERROR);
            break;
            
        case STATE_IDLE:
            valid = (to == STATE_ACTIVE) || (to == STATE_ERROR) || (to == STATE_SAFE);
            break;
            
        case STATE_ACTIVE:
            valid = (to == STATE_IDLE) || (to == STATE_ERROR) || (to == STATE_SAFE);
            break;
            
        case STATE_ERROR:
            valid = (to == STATE_SAFE);
            break;
            
        case STATE_SAFE:
            /* Safe state is sticky - cannot exit */
            valid = (to == STATE_SAFE);
            break;
            
        default:
            valid = false;
            break;
    }
    
    return valid;
}

/**
 * @brief Transition state with validation
 */
error_t state_transition(state_machine_t* sm, system_state_t new_state)
{
    error_t status;
    
    if (sm == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* DEFENSIVE: Validate state value in range */
    if ((new_state < STATE_INIT) || (new_state > STATE_SAFE)) {
        safety_log("Invalid state value: %d", (int)new_state);
        return ERROR_INVALID_STATE;
    }
    
    /* DEFENSIVE: Validate transition is allowed */
    if (!is_valid_transition(sm->current_state, new_state)) {
        safety_log("Invalid transition: %d -> %d", sm->current_state, new_state);
        return ERROR_INVALID_TRANSITION;
    }
    
    /* DEFENSIVE: Detect excessive transitions (oscillation) */
    if (sm->transition_count > MAX_TRANSITIONS_PER_SECOND) {
        safety_log("Excessive state transitions detected");
        return ERROR_STATE_OSCILLATION;
    }
    
    /* Perform transition */
    sm->previous_state = sm->current_state;
    sm->current_state = new_state;
    sm->state_entry_time = system_get_time_ms();
    sm->transition_count++;
    
    status = SUCCESS;
    return status;
}
```

### 6.2 Timeout Detection in States

```c
/**
 * @brief Check for state timeout
 */
error_t check_state_timeout(const state_machine_t* sm)
{
    error_t status;
    uint32_t current_time;
    uint32_t elapsed_time;
    uint32_t max_time;
    
    if (sm == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    current_time = system_get_time_ms();
    elapsed_time = current_time - sm->state_entry_time;
    
    /* DEFENSIVE: Each state has a maximum allowed time */
    switch (sm->current_state) {
        case STATE_INIT:
            max_time = INIT_TIMEOUT_MS;
            break;
        case STATE_IDLE:
            max_time = IDLE_TIMEOUT_MS;
            break;
        case STATE_ACTIVE:
            max_time = ACTIVE_TIMEOUT_MS;
            break;
        case STATE_ERROR:
            max_time = ERROR_TIMEOUT_MS;
            break;
        case STATE_SAFE:
            max_time = UINT32_MAX;  /* No timeout in safe state */
            break;
        default:
            safety_log("Unknown state in timeout check");
            return ERROR_INVALID_STATE;
    }
    
    if (elapsed_time > max_time) {
        safety_log("State %d timeout after %u ms", sm->current_state, elapsed_time);
        status = ERROR_TIMEOUT;
    } else {
        status = SUCCESS;
    }
    
    return status;
}
```

---

## Pattern 7: Bounded Loops (No Infinite Loops)

### 7.1 Loop with Iteration Counter

```c
/**
 * @brief Process queue with bounded iterations
 */
error_t process_queue(queue_t* queue)
{
    error_t status;
    uint32_t iteration_count;
    queue_item_t item;
    
    if (queue == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    iteration_count = 0U;
    status = SUCCESS;
    
    /* DEFENSIVE: Bounded loop (not while(1)) */
    while ((iteration_count < MAX_QUEUE_PROCESS_ITERATIONS) && 
           (!queue_is_empty(queue))) {
        
        status = queue_dequeue(queue, &item);
        if (status != SUCCESS) {
            safety_log("Queue dequeue failed");
            break;
        }
        
        status = process_item(&item);
        if (status != SUCCESS) {
            safety_log("Item processing failed");
            break;
        }
        
        iteration_count++;
    }
    
    /* DEFENSIVE: Detect runaway loop */
    if (iteration_count >= MAX_QUEUE_PROCESS_ITERATIONS) {
        safety_log("Queue processing iteration limit reached");
        status = ERROR_TIMEOUT;
    }
    
    return status;
}
```

### 7.2 Timeout-Based Loop

```c
/**
 * @brief Wait for condition with timeout
 */
error_t wait_for_ready(uint32_t timeout_ms)
{
    error_t status;
    uint32_t start_time;
    uint32_t elapsed_time;
    bool ready;
    
    start_time = system_get_time_ms();
    ready = false;
    status = ERROR_TIMEOUT;
    
    /* DEFENSIVE: Loop with time limit */
    do {
        ready = hardware_is_ready();
        
        if (ready) {
            status = SUCCESS;
            break;
        }
        
        elapsed_time = system_get_time_ms() - start_time;
        
        /* DEFENSIVE: Check timeout */
        if (elapsed_time >= timeout_ms) {
            safety_log("wait_for_ready: timeout after %u ms", elapsed_time);
            status = ERROR_TIMEOUT;
            break;
        }
        
        /* Small delay to avoid busy-wait */
        hardware_delay_us(POLL_DELAY_US);
        
    } while (true);  /* Exit via break only */
    
    return status;
}
```

---

## Pattern 8: Fail-Safe Entry

### 8.1 Safe State Entry Function

```c
/**
 * @brief Enter safe state on critical error
 */
void enter_safe_state(safe_state_reason_t reason)
{
    /* DEFENSIVE: This function MUST succeed */
    
    /* 1. Stop all actuators immediately */
    (void)actuator_emergency_stop_all();
    
    /* 2. Apply emergency brake */
    (void)brake_apply_emergency();
    
    /* 3. Cut power to non-critical systems */
    (void)power_disable_non_critical();
    
    /* 4. Activate visual/audible alarms */
    (void)alarm_activate(ALARM_SAFE_STATE);
    
    /* 5. Log reason for safe state entry */
    safety_log("SAFE STATE ENTERED: reason = %d", reason);
    
    /* 6. Update system state */
    system_state = SYSTEM_STATE_SAFE;
    
    /* 7. Infinite loop (safe state is sticky) */
    while (true) {
        /* Refresh watchdog to prove we're alive */
        (void)watchdog_refresh();
        
        /* Flash LED to indicate safe state */
        (void)led_toggle(LED_SAFE_STATE);
        
        /* Wait for manual intervention */
        hardware_delay_ms(500U);
    }
}
```

### 8.2 Graceful Degradation

```c
/**
 * @brief Handle sensor failure with degradation
 */
error_t read_primary_sensor_with_fallback(uint16_t* value)
{
    error_t status;
    static uint8_t primary_fail_count = 0U;
    
    if (value == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    /* Try primary sensor */
    status = sensor_primary_read(value);
    
    if (status == SUCCESS) {
        /* Primary sensor working */
        primary_fail_count = 0U;
    } else {
        /* DEFENSIVE: Track failures */
        primary_fail_count++;
        safety_log("Primary sensor failure #%u", primary_fail_count);
        
        /* DEFENSIVE: Switch to backup sensor */
        if (primary_fail_count < MAX_PRIMARY_FAILURES) {
            safety_log("Attempting backup sensor");
            status = sensor_backup_read(value);
            
            if (status == SUCCESS) {
                safety_log("Backup sensor operational (degraded mode)");
            } else {
                safety_log("Backup sensor also failed");
                /* Both sensors failed - enter safe state */
                enter_safe_state(SAFE_STATE_SENSOR_FAILURE);
            }
        } else {
            safety_log("Primary sensor exceeded failure threshold");
            /* Permanent switch to backup */
            status = sensor_backup_read(value);
        }
    }
    
    return status;
}
```

---

## SIL-Dependent Requirements

### SIL 0-1: Recommended
- Basic input validation (NULL checks, range checks)
- Return value checking encouraged
- Defensive logging optional

### SIL 2: Highly Recommended
- Input validation mandatory
- Return value checking mandatory
- Plausibility checks for critical inputs
- Hardware read-back verification recommended

### SIL 3-4: Highly Recommended (EN 50128 Table A.3)
- **Comprehensive input validation** (all patterns)
- **All return values checked** (no exceptions)
- **Plausibility and cross-checks** mandatory
- **Hardware fault detection** (watchdog, read-back, memory checks)
- **Redundancy and voting** for critical sensors
- **Bounded loops** (no infinite loops without timeout)
- **Fail-safe entry** on all critical errors
- **Extensive logging** for diagnostics

---

## Checklist

### Input Validation
- [ ] All pointer parameters checked for NULL
- [ ] All numeric inputs range-validated
- [ ] Plausibility checks for sensor data
- [ ] Array bounds checked before access
- [ ] String lengths validated
- [ ] Structure integrity checked (magic numbers, checksums)

### Error Handling
- [ ] All function return values checked
- [ ] Errors propagated up call stack
- [ ] Critical errors logged
- [ ] Safe state entry on critical failures
- [ ] Error codes defined comprehensively

### Arithmetic Safety
- [ ] Integer overflow detection
- [ ] Division by zero protection
- [ ] Saturation or error on overflow
- [ ] Explicit casts with range checks

### Hardware Fault Protection
- [ ] Watchdog timer implemented and refreshed
- [ ] Register write read-back verification
- [ ] Memory corruption detection (checksums, magic numbers)
- [ ] Retry logic for transient faults

### Redundancy
- [ ] Redundant sensor cross-checking
- [ ] Voting algorithms (dual/triple)
- [ ] Inverse calculation verification
- [ ] Multiple independent calculations

### State Management
- [ ] State transitions validated
- [ ] State timeouts checked
- [ ] Invalid states detected
- [ ] State oscillation prevention

### Loops and Timeouts
- [ ] All loops bounded (iteration or time)
- [ ] No infinite loops (except safe state)
- [ ] Timeout mechanisms implemented
- [ ] Watchdog refresh in long loops

### Fail-Safe
- [ ] Safe state entry function defined
- [ ] Safe state is sticky (cannot exit)
- [ ] Graceful degradation implemented
- [ ] Alarm/logging on safe state entry

---

## Tools and Verification

### Static Analysis
```bash
# Cppcheck: Detect defensive programming violations
cppcheck --enable=all \
         --addon=cert \
         --addon=threadsafety \
         src/module.c
```

### Code Review Focus
- Review all error paths
- Verify NULL checks present
- Confirm return values checked
- Validate loop bounds
- Check fail-safe logic

### Runtime Monitoring
```bash
# Valgrind: Detect NULL dereferences at runtime
valgrind --leak-check=full \
         --track-origins=yes \
         ./application
```

---

## Common Pitfalls

### Pitfall 1: Ignoring Return Values
```c
/* BAD */
function_that_can_fail();

/* GOOD */
error_t status = function_that_can_fail();
if (status != SUCCESS) {
    handle_error(status);
}
```

### Pitfall 2: Unchecked NULL Pointers
```c
/* BAD */
void function(data_t* ptr)
{
    ptr->field = 10;  /* Crash if ptr == NULL */
}

/* GOOD */
error_t function(data_t* ptr)
{
    if (ptr == NULL) {
        return ERROR_NULL_POINTER;
    }
    ptr->field = 10;
    return SUCCESS;
}
```

### Pitfall 3: Unbounded Loops
```c
/* BAD */
while (!condition) {
    /* Could run forever */
}

/* GOOD */
uint32_t timeout = 1000U;
while ((!condition) && (timeout > 0U)) {
    timeout--;
}
if (timeout == 0U) {
    return ERROR_TIMEOUT;
}
```

---

## Related Resources

- **[Defensive Programming Patterns](../resources/defensive-programming-patterns.md)** - 18 comprehensive patterns from design phase
- **[MISRA C Coding Patterns](../resources/misra-c-coding-patterns.md)** - MISRA C compliant defensive code
- **[Code Review Checklist](../resources/code-review-checklist.md)** - Review defensive programming compliance
- **[Common Pitfalls](../resources/common-pitfalls.md)** - Common defensive programming mistakes

---

## References

1. **EN 50128:2011** Section 7.3 Table A.3 (Technique 2: Defensive Programming - HR for SIL 3-4)
2. **EN 50128:2011** Annex D.14 (Defensive Programming)
3. **MISRA C:2012** Guidelines (defensive programming rules)
4. **IEC 61508** Functional Safety Standard
5. **`std/EN50128-2011.md`** - Full EN 50128 standard (project repository)
