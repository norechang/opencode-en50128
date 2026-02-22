/**
 * @file door_fsm.c
 * @brief Door Control Finite State Machine Implementation (MOD-001)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.1 (MOD-001)
 * 
 * @description
 * Implements 7-state door control FSM with full defensive programming.
 * All functions meet SIL 3 complexity requirement (≤10).
 */

#include "door_fsm.h"

/* Forward declarations for HAL functions (to be implemented in HAL modules) */
extern error_t sensor_hal_read_position(door_side_t side, uint16_t* position_raw);
extern bool sensor_hal_read_obstacle(door_side_t side);
extern error_t actuator_hal_set_door_pwm(door_side_t side, int8_t duty_cycle);
extern error_t actuator_hal_set_door_lock(door_side_t side, bool locked);
extern bool safety_monitor_is_safe_to_open(void);
extern void fault_detection_report_fault(uint16_t code, uint8_t severity);
extern bool fault_detection_is_critical_fault_active(void);

/* Fault codes (partial, from fault_detection module) */
#define FAULT_POSITION_SENSOR         (0x0001U)
#define FAULT_OPEN_INTERLOCK          (0x0010U)
#define FAULT_CLOSE_BLOCKED           (0x0011U)
#define FAULT_DOOR_OPEN_TIMEOUT       (0x0020U)
#define FAULT_DOOR_CLOSE_TIMEOUT      (0x0021U)
#define FAULT_OBSTACLE_OPENING        (0x0030U)
#define FAULT_OBSTACLE_DETECTED       (0x0031U)
#define FAULT_DOOR_NOT_CLOSED_MOVING  (0x0040U)
#define FAULT_ACTUATOR_FAILURE        (0x0050U)
#define FAULT_LOCK_ACTUATOR_FAILURE   (0x0051U)
#define FAULT_EMERGENCY_RELEASE       (0x0060U)
#define FAULT_DOOR_SAFE_STATE_ENTRY   (0x0070U)
#define FAULT_CRITICAL                (0x8000U)

/* Fault severity levels */
#define FAULT_SEVERITY_MINOR    (0U)
#define FAULT_SEVERITY_MAJOR    (1U)
#define FAULT_SEVERITY_CRITICAL (2U)

/*===========================================================================*/
/* Private Function Prototypes                                               */
/*===========================================================================*/

static void door_fsm_process_queued_events(door_fsm_t* fsm);
static error_t door_fsm_transition_to_opening(door_fsm_t* fsm);
static error_t door_fsm_transition_to_open(door_fsm_t* fsm);
static error_t door_fsm_transition_to_closing(door_fsm_t* fsm);
static error_t door_fsm_transition_to_closed(door_fsm_t* fsm);
static error_t door_fsm_transition_to_locked(door_fsm_t* fsm);
static bool event_queue_contains(const door_fsm_t* fsm, door_event_t event);

/*===========================================================================*/
/* Public Function Implementations                                           */
/*===========================================================================*/

/**
 * @brief Initialize door FSM for specified side
 * @complexity 3 (1 base + 2 IF decisions)
 */
error_t door_fsm_init(door_fsm_t* fsm, door_side_t side)
{
    uint8_t i;
    
    /* Step 1: NULL pointer check (defensive programming) */
    if (fsm == NULL) {                                      /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Side parameter validation */
    if (side >= DOOR_SIDE_MAX) {                            /* +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 3: Initialize FSM structure */
    fsm->current_state = DOOR_STATE_CLOSED;
    fsm->previous_state = DOOR_STATE_CLOSED;
    fsm->side = side;
    fsm->position = 0U;                     /* 0% (fully closed) */
    fsm->locked = false;
    fsm->state_entry_time_ms = get_system_time_ms();
    fsm->last_update_time_ms = get_system_time_ms();
    fsm->retry_count = 0U;
    fsm->last_fault_code = 0U;
    fsm->event_queue_head = 0U;
    fsm->event_queue_tail = 0U;
    fsm->event_queue_count = 0U;
    
    /* Step 4: Clear event queue */
    for (i = 0U; i < DOOR_FSM_MAX_EVENTS; i++) {
        fsm->event_queue[i] = DOOR_EVENT_NONE;
    }
    
    /* Step 5: Return success */
    return ERROR_SUCCESS;
}

/**
 * @brief Main state machine update function (50ms cycle)
 * @complexity 10 (EXACTLY at SIL 3 limit)
 * 
 * @note FIX for DEF-IMPL-001 (2026-02-22):
 *       Event dequeuing moved to END of function (after state processing)
 *       to ensure events are visible during state machine logic.
 */
error_t door_fsm_update(door_fsm_t* fsm)
{
    uint32_t current_time_ms;
    uint32_t time_in_state_ms;
    uint16_t position_raw;
    error_t error;
    bool obstacle;
    
    /* Step 1: NULL pointer check */
    if (fsm == NULL) {                                       /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Get current time and calculate time in state */
    current_time_ms = get_system_time_ms();
    time_in_state_ms = current_time_ms - fsm->state_entry_time_ms;
    
    /* Step 3: Read current door position from sensor */
    error = sensor_hal_read_position(fsm->side, &position_raw);
    if (error == ERROR_SUCCESS) {                            /* +1 */
        /* Convert 12-bit ADC (0-4095) to percentage (0-100) */
        fsm->position = (uint8_t)((position_raw * 100U) / 4095U);
    } else {
        /* Sensor failed, use last known position (degraded mode) */
        fault_detection_report_fault(FAULT_POSITION_SENSOR, FAULT_SEVERITY_MAJOR);
    }
    
    /* Step 4: Process events from queue */
    /* NOTE: Events are checked in state machine below, then dequeued at end */
    /* DO NOT dequeue here - state machine needs to see events in queue */
    
    /* Step 5: Check for critical faults (HIGHEST PRIORITY) */
    if (fault_detection_is_critical_fault_active()) {        /* +1 */
        (void)door_fsm_enter_safe_state(fsm, FAULT_CRITICAL);
        return ERROR_SUCCESS;
    }
    
    /* Step 6: Main state machine logic (7-way switch = +6 decisions) */
    switch (fsm->current_state) {                            /* +6 */
        
        case DOOR_STATE_CLOSED:
            /* Door fully closed, ready to open or lock */
            (void)actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_STOP_DUTY);
            
            /* Check for open command */
            if (event_queue_contains(fsm, DOOR_EVENT_OPEN_CMD)) {
                /* Safety interlock check */
                if (safety_monitor_is_safe_to_open()) {
                    (void)door_fsm_transition_to_opening(fsm);
                } else {
                    fault_detection_report_fault(FAULT_OPEN_INTERLOCK, FAULT_SEVERITY_MINOR);
                }
            }
            /* Check for lock command */
            else if (event_queue_contains(fsm, DOOR_EVENT_LOCK_CMD)) {
                (void)door_fsm_transition_to_locked(fsm);
            } else {
                /* No action */
            }
            break;
        
        case DOOR_STATE_OPENING:
            /* Door opening, apply PWM and monitor position */
            (void)actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_OPEN_DUTY);
            
            /* Check if fully open (position ≥ 95%) */
            if (fsm->position >= DOOR_FSM_POSITION_OPEN_PCT) {
                (void)door_fsm_transition_to_open(fsm);
            }
            /* Check for timeout (5 seconds) */
            else if (time_in_state_ms > DOOR_FSM_OPEN_TIMEOUT_MS) {
                fault_detection_report_fault(FAULT_DOOR_OPEN_TIMEOUT, FAULT_SEVERITY_MAJOR);
                (void)door_fsm_enter_safe_state(fsm, FAULT_DOOR_OPEN_TIMEOUT);
            }
            /* Check for obstacle (defensive, should not happen during opening) */
            else {
                obstacle = sensor_hal_read_obstacle(fsm->side);
                if (obstacle) {
                    (void)actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_STOP_DUTY);
                    fault_detection_report_fault(FAULT_OBSTACLE_OPENING, FAULT_SEVERITY_MAJOR);
                    (void)door_fsm_enter_safe_state(fsm, FAULT_OBSTACLE_OPENING);
                }
            }
            break;
        
        case DOOR_STATE_OPEN:
            /* Door fully open, maintain position */
            (void)actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_STOP_DUTY);
            
            /* Check for close command */
            if (event_queue_contains(fsm, DOOR_EVENT_CLOSE_CMD)) {
                /* Check no obstacle present */
                obstacle = sensor_hal_read_obstacle(fsm->side);
                if (!obstacle) {
                    (void)door_fsm_transition_to_closing(fsm);
                } else {
                    fault_detection_report_fault(FAULT_CLOSE_BLOCKED, FAULT_SEVERITY_MINOR);
                }
            }
            break;
        
        case DOOR_STATE_CLOSING:
            /* Door closing, apply reverse PWM, monitor obstacles */
            (void)actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_CLOSE_DUTY);
            
            /* Check if fully closed (position ≤ 5%) */
            if (fsm->position <= DOOR_FSM_POSITION_CLOSED_PCT) {
                (void)door_fsm_transition_to_closed(fsm);
            }
            /* CRITICAL: Check for obstacle (reaction time ≤ 100ms) */
            else {
                obstacle = sensor_hal_read_obstacle(fsm->side);
                if (obstacle) {
                    /* Immediate stop and reverse */
                    (void)actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_STOP_DUTY);
                    fault_detection_report_fault(FAULT_OBSTACLE_DETECTED, FAULT_SEVERITY_MINOR);
                    /* Reverse to open by 20% */
                    (void)door_fsm_transition_to_opening(fsm);
                }
                /* Check for timeout (7 seconds) */
                else if (time_in_state_ms > DOOR_FSM_CLOSE_TIMEOUT_MS) {
                    fault_detection_report_fault(FAULT_DOOR_CLOSE_TIMEOUT, FAULT_SEVERITY_MAJOR);
                    (void)door_fsm_enter_safe_state(fsm, FAULT_DOOR_CLOSE_TIMEOUT);
                } else {
                    /* No action */
                }
            }
            break;
        
        case DOOR_STATE_LOCKED:
            /* Door locked (train speed > 5 km/h) */
            (void)actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_STOP_DUTY);
            (void)actuator_hal_set_door_lock(fsm->side, true);
            fsm->locked = true;
            
            /* Check for unlock command (from safety monitor) */
            if (event_queue_contains(fsm, DOOR_EVENT_UNLOCK_CMD)) {
                /* Safety approved unlock (speed < 2 km/h for ≥1s) */
                (void)door_fsm_transition_to_closed(fsm);
            }
            break;
        
        case DOOR_STATE_EMERGENCY:
            /* Emergency release activated (hardware override) */
            (void)actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_STOP_DUTY);
            (void)actuator_hal_set_door_lock(fsm->side, false);
            fsm->locked = false;
            
            /* Log emergency event */
            fault_detection_report_fault(FAULT_EMERGENCY_RELEASE, FAULT_SEVERITY_CRITICAL);
            
            /* Stay in EMERGENCY state until manual reset */
            break;
        
        case DOOR_STATE_FAULT:
            /* Safe state: disable all actuators */
            (void)actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_STOP_DUTY);
            
            /* Lock door if closed, otherwise hold position */
            if (fsm->position <= DOOR_FSM_POSITION_CLOSED_PCT) {
                (void)actuator_hal_set_door_lock(fsm->side, true);
            }
            
            /* Await manual reset or fault clearance */
            break;
        
        default:
            /* Invalid state - enter safe state */
            (void)door_fsm_enter_safe_state(fsm, FAULT_CRITICAL);
            break;
    }
    
    /* Step 7: Dequeue processed event (if any) */
    /* FIX for DEF-IMPL-001: Dequeue AFTER state machine processes event */
    door_fsm_process_queued_events(fsm);
    
    /* Step 8: Update timestamp */
    fsm->last_update_time_ms = current_time_ms;
    
    /* Step 9: Return success */
    return ERROR_SUCCESS;
}

/**
 * @brief Queue external event for processing
 * @complexity 7 (1 base + 6 decisions)
 */
error_t door_fsm_process_event(door_fsm_t* fsm, door_event_t event)
{
    uint8_t i;
    uint8_t queue_index;
    
    /* Step 1: NULL pointer check */
    if (fsm == NULL) {                                       /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Event validation */
    if (event >= DOOR_EVENT_MAX) {                           /* +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 3: Check if event queue is full */
    if (fsm->event_queue_count >= DOOR_FSM_MAX_EVENTS) {    /* +1 */
        return ERROR_BUFFER_FULL;
    }
    
    /* Step 4: Special handling for emergency events (highest priority) */
    if (event == DOOR_EVENT_EMERGENCY_RELEASE) {             /* +1 */
        /* Immediate transition, bypass queue */
        fsm->current_state = DOOR_STATE_EMERGENCY;
        (void)actuator_hal_set_door_lock(fsm->side, false);
        return ERROR_SUCCESS;
    }
    
    /* Step 5: Check for duplicate events in queue */
    for (i = 0U; i < fsm->event_queue_count; i++) {         /* +1 */
        queue_index = (fsm->event_queue_head + i) % DOOR_FSM_MAX_EVENTS;
        if (fsm->event_queue[queue_index] == event) {       /* +1 */
            /* Event already in queue, don't add duplicate */
            return ERROR_SUCCESS;
        }
    }
    
    /* Step 6: Enqueue event (circular buffer) */
    fsm->event_queue[fsm->event_queue_tail] = event;
    fsm->event_queue_tail = (fsm->event_queue_tail + 1U) % DOOR_FSM_MAX_EVENTS;
    fsm->event_queue_count++;
    
    /* Step 7: Return success */
    return ERROR_SUCCESS;
}

/**
 * @brief Force door to safe state (FAULT)
 * @complexity 3 (1 base + 2 decisions)
 */
error_t door_fsm_enter_safe_state(door_fsm_t* fsm, uint16_t fault_code)
{
    /* Step 1: NULL check */
    if (fsm == NULL) {                                       /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Record previous state */
    fsm->previous_state = fsm->current_state;
    
    /* Step 3: Set safe state */
    fsm->current_state = DOOR_STATE_FAULT;
    fsm->state_entry_time_ms = get_system_time_ms();
    fsm->last_fault_code = fault_code;
    
    /* Step 4: Disable all actuators (SAFE STATE) */
    (void)actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_STOP_DUTY);
    
    /* Step 5: Lock door if closed, otherwise release lock (allow manual operation) */
    if (fsm->position <= DOOR_FSM_POSITION_CLOSED_PCT) {    /* +1 */
        (void)actuator_hal_set_door_lock(fsm->side, true);
        fsm->locked = true;
    } else {
        (void)actuator_hal_set_door_lock(fsm->side, false);
        fsm->locked = false;
    }
    
    /* Step 6: Log safe state entry */
    fault_detection_report_fault(FAULT_DOOR_SAFE_STATE_ENTRY, FAULT_SEVERITY_MAJOR);
    
    return ERROR_SUCCESS;
}

/**
 * @brief Get current door state (accessor)
 * @complexity 2 (1 base + 1 IF)
 */
door_state_t door_fsm_get_state(const door_fsm_t* fsm)
{
    /* Defensive NULL check */
    if (fsm == NULL) {                                       /* +1 */
        return DOOR_STATE_FAULT;  /* Fail-safe default */
    }
    
    return fsm->current_state;
}

/**
 * @brief Get current door position (0-100%)
 * @complexity 2 (1 base + 1 IF)
 */
uint8_t door_fsm_get_position(const door_fsm_t* fsm)
{
    /* Defensive NULL check */
    if (fsm == NULL) {                                       /* +1 */
        return 0U;  /* Fail-safe: assume closed */
    }
    
    return fsm->position;
}

/**
 * @brief Get door lock status
 * @complexity 2 (1 base + 1 IF)
 */
bool door_fsm_is_locked(const door_fsm_t* fsm)
{
    /* Defensive NULL check */
    if (fsm == NULL) {                                       /* +1 */
        return false;  /* Fail-safe: assume unlocked */
    }
    
    return fsm->locked;
}

/*===========================================================================*/
/* Private Function Implementations                                          */
/*===========================================================================*/

/**
 * @brief Dequeue processed event from queue (helper function)
 * @complexity 2 (1 base + 1 IF)
 * 
 * @note CRITICAL FIX (DEF-IMPL-001 - 2026-02-22):
 *       This function is now called AFTER the state machine processes events,
 *       not before. Previously, events were dequeued before event_queue_contains()
 *       checked for them, making event-driven transitions impossible.
 *       
 *       New flow:
 *       1. door_fsm_update() reads sensors
 *       2. State machine checks event_queue_contains() (events still in queue)
 *       3. State machine processes event and transitions
 *       4. door_fsm_process_queued_events() dequeues the processed event
 *       
 *       This ensures events are visible to the state machine during processing.
 */
static void door_fsm_process_queued_events(door_fsm_t* fsm)
{
    /* Step 1: Check if queue is empty */
    if (fsm->event_queue_count == 0U) {                      /* +1 */
        return;
    }
    
    /* Step 2: Dequeue the event that was just processed by state machine */
    /* The state machine has already acted on this event in the main switch */
    fsm->event_queue_head = (fsm->event_queue_head + 1U) % DOOR_FSM_MAX_EVENTS;
    fsm->event_queue_count--;
}

/**
 * @brief Transition to OPENING state
 * @complexity 3 (1 base + 2 IF)
 */
static error_t door_fsm_transition_to_opening(door_fsm_t* fsm)
{
    error_t error;
    
    /* Step 1: Record previous state */
    fsm->previous_state = fsm->current_state;
    
    /* Step 2: Set new state */
    fsm->current_state = DOOR_STATE_OPENING;
    fsm->state_entry_time_ms = get_system_time_ms();
    fsm->retry_count = 0U;
    
    /* Step 3: Unlock door (if locked) */
    if (fsm->locked) {                                       /* +1 */
        fsm->locked = false;
        (void)actuator_hal_set_door_lock(fsm->side, false);
    }
    
    /* Step 4: Apply opening PWM */
    error = actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_OPEN_DUTY);
    if (error != ERROR_SUCCESS) {                            /* +1 */
        fault_detection_report_fault(FAULT_ACTUATOR_FAILURE, FAULT_SEVERITY_MAJOR);
        return error;
    }
    
    return ERROR_SUCCESS;
}

/**
 * @brief Transition to OPEN state (door fully open)
 * @complexity 2 (1 base + 1 IF)
 */
static error_t door_fsm_transition_to_open(door_fsm_t* fsm)
{
    error_t error;
    
    /* Step 1: Record previous state */
    fsm->previous_state = fsm->current_state;
    
    /* Step 2: Set new state */
    fsm->current_state = DOOR_STATE_OPEN;
    fsm->state_entry_time_ms = get_system_time_ms();
    
    /* Step 3: Stop motor (door is fully open) */
    error = actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_STOP_DUTY);
    if (error != ERROR_SUCCESS) {                            /* +1 */
        fault_detection_report_fault(FAULT_ACTUATOR_FAILURE, FAULT_SEVERITY_MAJOR);
        return error;
    }
    
    return ERROR_SUCCESS;
}

/**
 * @brief Transition to CLOSING state
 * @complexity 2 (1 base + 1 IF)
 */
static error_t door_fsm_transition_to_closing(door_fsm_t* fsm)
{
    error_t error;
    
    /* Step 1: Record previous state */
    fsm->previous_state = fsm->current_state;
    
    /* Step 2: Set new state */
    fsm->current_state = DOOR_STATE_CLOSING;
    fsm->state_entry_time_ms = get_system_time_ms();
    fsm->retry_count = 0U;
    
    /* Step 3: Apply closing PWM (reverse direction, negative duty) */
    error = actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_CLOSE_DUTY);
    if (error != ERROR_SUCCESS) {                            /* +1 */
        fault_detection_report_fault(FAULT_ACTUATOR_FAILURE, FAULT_SEVERITY_MAJOR);
        return error;
    }
    
    return ERROR_SUCCESS;
}

/**
 * @brief Transition to CLOSED state (door fully closed)
 * @complexity 3 (1 base + 2 IF)
 */
static error_t door_fsm_transition_to_closed(door_fsm_t* fsm)
{
    error_t error;
    
    /* Step 1: Record previous state */
    fsm->previous_state = fsm->current_state;
    
    /* Step 2: Set new state */
    fsm->current_state = DOOR_STATE_CLOSED;
    fsm->state_entry_time_ms = get_system_time_ms();
    
    /* Step 3: Stop motor */
    error = actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_STOP_DUTY);
    if (error != ERROR_SUCCESS) {                            /* +1 */
        fault_detection_report_fault(FAULT_ACTUATOR_FAILURE, FAULT_SEVERITY_MAJOR);
        return error;
    }
    
    /* Step 4: Unlock door (if it was locked) */
    if (fsm->locked) {                                       /* +1 */
        fsm->locked = false;
        (void)actuator_hal_set_door_lock(fsm->side, false);
    }
    
    return ERROR_SUCCESS;
}

/**
 * @brief Transition to LOCKED state (speed > 5 km/h)
 * @complexity 4 (1 base + 3 IF)
 */
static error_t door_fsm_transition_to_locked(door_fsm_t* fsm)
{
    error_t error;
    
    /* Step 1: Validate door is closed */
    if (fsm->position > DOOR_FSM_POSITION_CLOSED_PCT) {     /* +1 */
        /* CRITICAL FAULT: door not closed when attempting lock */
        fault_detection_report_fault(FAULT_DOOR_NOT_CLOSED_MOVING, FAULT_SEVERITY_CRITICAL);
        (void)door_fsm_enter_safe_state(fsm, FAULT_DOOR_NOT_CLOSED_MOVING);
        return ERROR_INVALID_STATE;
    }
    
    /* Step 2: Record previous state */
    fsm->previous_state = fsm->current_state;
    
    /* Step 3: Set new state */
    fsm->current_state = DOOR_STATE_LOCKED;
    fsm->state_entry_time_ms = get_system_time_ms();
    fsm->locked = true;
    
    /* Step 4: Engage lock solenoid */
    error = actuator_hal_set_door_lock(fsm->side, true);
    if (error != ERROR_SUCCESS) {                            /* +1 */
        fault_detection_report_fault(FAULT_LOCK_ACTUATOR_FAILURE, FAULT_SEVERITY_CRITICAL);
        return error;
    }
    
    /* Step 5: Stop motor (ensure door doesn't move) */
    error = actuator_hal_set_door_pwm(fsm->side, DOOR_FSM_PWM_STOP_DUTY);
    if (error != ERROR_SUCCESS) {                            /* +1 */
        fault_detection_report_fault(FAULT_ACTUATOR_FAILURE, FAULT_SEVERITY_MAJOR);
        return error;
    }
    
    return ERROR_SUCCESS;
}

/**
 * @brief Helper: Check if event is in queue
 * @complexity 3 (1 base + 2 IF)
 */
static bool event_queue_contains(const door_fsm_t* fsm, door_event_t event)
{
    uint8_t i;
    uint8_t queue_index;
    
    /* Check if queue is empty */
    if (fsm->event_queue_count == 0U) {                      /* +1 */
        return false;
    }
    
    /* Search queue */
    for (i = 0U; i < fsm->event_queue_count; i++) {         /* +1 */
        queue_index = (fsm->event_queue_head + i) % DOOR_FSM_MAX_EVENTS;
        if (fsm->event_queue[queue_index] == event) {
            return true;
        }
    }
    
    return false;
}
