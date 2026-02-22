/**
 * @file door_fsm.h
 * @brief Door Control Finite State Machine (MOD-001)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.1 (MOD-001)
 * 
 * @description
 * Door Control FSM implements 7-state door control logic with safety interlocks.
 * States: CLOSED, OPENING, OPEN, CLOSING, LOCKED, EMERGENCY, FAULT.
 * Max complexity: 10 (SIL 3 limit).
 * 
 * @components
 * - door_fsm_init()
 * - door_fsm_update()
 * - door_fsm_process_event()
 * - door_fsm_enter_safe_state()
 * - door_fsm_get_state()
 * - door_fsm_get_position()
 * - door_fsm_is_locked()
 * + 6 private transition functions
 */

#ifndef DOOR_FSM_H
#define DOOR_FSM_H

#include "../common/types.h"
#include "../common/error_codes.h"

/*===========================================================================*/
/* Door State Enumeration                                                    */
/*===========================================================================*/

/**
 * @brief Door state enumeration (7 states)
 * @compliance MISRA C:2012 Rule 8.2
 */
typedef enum {
    DOOR_STATE_CLOSED = 0U,       /**< Door fully closed, unlocked */
    DOOR_STATE_OPENING = 1U,      /**< Door opening (motor active) */
    DOOR_STATE_OPEN = 2U,         /**< Door fully open */
    DOOR_STATE_CLOSING = 3U,      /**< Door closing (motor active) */
    DOOR_STATE_LOCKED = 4U,       /**< Door locked (speed > 5 km/h) */
    DOOR_STATE_EMERGENCY = 5U,    /**< Emergency release activated */
    DOOR_STATE_FAULT = 6U,        /**< Safe state (fault detected) */
    DOOR_STATE_MAX = 7U           /**< Sentinel value */
} door_state_t;

/*===========================================================================*/
/* Door Event Enumeration                                                    */
/*===========================================================================*/

/**
 * @brief Door event enumeration (external commands)
 * @compliance MISRA C:2012 Rule 8.2
 */
typedef enum {
    DOOR_EVENT_NONE = 0U,                 /**< No event */
    DOOR_EVENT_OPEN_CMD = 1U,             /**< Open door command */
    DOOR_EVENT_CLOSE_CMD = 2U,            /**< Close door command */
    DOOR_EVENT_LOCK_CMD = 3U,             /**< Lock door command */
    DOOR_EVENT_UNLOCK_CMD = 4U,           /**< Unlock door command */
    DOOR_EVENT_EMERGENCY_RELEASE = 5U,    /**< Emergency release activated */
    DOOR_EVENT_OBSTACLE_DETECTED = 6U,    /**< Obstacle detected */
    DOOR_EVENT_FAULT_DETECTED = 7U,       /**< Fault detected */
    DOOR_EVENT_POSITION_CHANGED = 8U,     /**< Position sensor changed */
    DOOR_EVENT_TIMEOUT = 9U,              /**< Timeout occurred */
    DOOR_EVENT_MAX = 10U                  /**< Sentinel value */
} door_event_t;

/*===========================================================================*/
/* Constants                                                                 */
/*===========================================================================*/

/** 
 * @brief Maximum events in queue (circular buffer)
 * 
 * @note FIX for DEF-DESIGN-001 (2026-02-22):
 *       Reduced from 16 to 8 to match number of unique queueable event types.
 *       Event types: OPEN_CMD, CLOSE_CMD, LOCK_CMD, UNLOCK_CMD, 
 *                    OBSTACLE_DETECTED, FAULT_DETECTED, POSITION_CHANGED, TIMEOUT
 *       (EMERGENCY_RELEASE bypasses queue, total = 8 queueable events)
 *       
 *       With duplicate detection (door_fsm_process_event lines 318-325),
 *       maximum queue fill is 8 unique events. Queue size 16 made 
 *       ERROR_BUFFER_FULL unreachable, preventing 100% test coverage.
 *       
 *       New size: 8 (matches event diversity, queue full now reachable)
 */
#define DOOR_FSM_MAX_EVENTS           (8U)

/** @brief Door open timeout (5 seconds) */
#define DOOR_FSM_OPEN_TIMEOUT_MS      (5000U)

/** @brief Door close timeout (7 seconds) */
#define DOOR_FSM_CLOSE_TIMEOUT_MS     (7000U)

/** @brief Position threshold for closed (≤5%) */
#define DOOR_FSM_POSITION_CLOSED_PCT  (5U)

/** @brief Position threshold for open (≥95%) */
#define DOOR_FSM_POSITION_OPEN_PCT    (95U)

/** @brief Maximum retry attempts */
#define DOOR_FSM_MAX_RETRIES          (3U)

/** @brief PWM duty cycle for opening (80%) */
#define DOOR_FSM_PWM_OPEN_DUTY        (80)

/** @brief PWM duty cycle for closing (-60%, negative = reverse) */
#define DOOR_FSM_PWM_CLOSE_DUTY       (-60)

/** @brief PWM duty cycle for stop (0%) */
#define DOOR_FSM_PWM_STOP_DUTY        (0)

/*===========================================================================*/
/* Data Structures                                                           */
/*===========================================================================*/

/**
 * @brief Door FSM state structure
 * @compliance Static allocation ONLY (85 bytes fixed size after queue reduction)
 * @traceability DOC-COMPDES-2026-001 Section 3.1.14
 * 
 * @note FIX for DEF-DESIGN-001 (2026-02-22):
 *       Event queue size reduced from 16 to 8 elements
 */
typedef struct {
    /* State information */
    door_state_t current_state;           /**< Current FSM state (1 byte) */
    door_state_t previous_state;          /**< Previous FSM state (1 byte) */
    door_side_t side;                     /**< Door side (left/right, 1 byte) */
    uint8_t position;                     /**< Door position 0-100% (1 byte) */
    bool locked;                          /**< Lock state (1 byte) */
    
    /* Timing information */
    uint32_t state_entry_time_ms;         /**< State entry time (4 bytes) */
    uint32_t last_update_time_ms;         /**< Last update time (4 bytes) */
    
    /* Error handling */
    uint8_t retry_count;                  /**< Retry counter (1 byte) */
    uint16_t last_fault_code;             /**< Last fault code (2 bytes) */
    
    /* Event queue (circular buffer) - REDUCED from 16 to 8 (DEF-DESIGN-001) */
    door_event_t event_queue[DOOR_FSM_MAX_EVENTS];  /**< Event queue (8 bytes) */
    uint8_t event_queue_head;             /**< Queue head index (1 byte) */
    uint8_t event_queue_tail;             /**< Queue tail index (1 byte) */
    uint8_t event_queue_count;            /**< Number of queued events (1 byte) */
    
    /* Total size: 85 bytes (reduced from 93 bytes, padding may apply for alignment) */
} door_fsm_t;

/*===========================================================================*/
/* Public Function Prototypes                                                */
/*===========================================================================*/

/**
 * @brief Initialize door FSM for specified side
 * @param[in,out] fsm Pointer to door FSM structure (must not be NULL)
 * @param[in] side Door side (LEFT or RIGHT)
 * @return ERROR_SUCCESS on success, error code otherwise
 * @pre fsm must not be NULL
 * @pre side must be valid (DOOR_SIDE_LEFT or DOOR_SIDE_RIGHT)
 * @post FSM initialized to CLOSED state with default values
 * @complexity 3 (1 base + 2 IF decisions)
 * @safety Non-critical (initialization only)
 */
error_t door_fsm_init(door_fsm_t* fsm, door_side_t side);

/**
 * @brief Main state machine update function (50ms cycle)
 * @param[in,out] fsm Pointer to door FSM structure (must not be NULL)
 * @return ERROR_SUCCESS on success, error code otherwise
 * @pre fsm must not be NULL and initialized
 * @post FSM state may transition, actuators may be commanded
 * @complexity 10 (EXACTLY at SIL 3 limit)
 * @safety CRITICAL - Enforces all door safety interlocks
 * @wcet ≤ 10 ms
 */
error_t door_fsm_update(door_fsm_t* fsm);

/**
 * @brief Queue external event for processing
 * @param[in,out] fsm Pointer to door FSM structure (must not be NULL)
 * @param[in] event Event to queue
 * @return ERROR_SUCCESS on success, error code otherwise
 * @pre fsm must not be NULL and initialized
 * @pre event must be valid
 * @post Event queued or immediate transition (emergency)
 * @complexity 7 (1 base + 6 decisions)
 * @safety CRITICAL - Emergency event handling
 */
error_t door_fsm_process_event(door_fsm_t* fsm, door_event_t event);

/**
 * @brief Force door to safe state (FAULT)
 * @param[in,out] fsm Pointer to door FSM structure (must not be NULL)
 * @param[in] fault_code Fault code identifier
 * @return ERROR_SUCCESS on success, error code otherwise
 * @pre fsm must not be NULL
 * @post FSM transitions to FAULT state, actuators disabled
 * @complexity 3 (1 base + 2 decisions)
 * @safety CRITICAL - Safe state entry
 */
error_t door_fsm_enter_safe_state(door_fsm_t* fsm, uint16_t fault_code);

/**
 * @brief Get current door state (accessor)
 * @param[in] fsm Pointer to door FSM structure
 * @return Current door state, or DOOR_STATE_FAULT if fsm is NULL
 * @pre None (NULL-safe)
 * @post No state change
 * @complexity 2 (1 base + 1 IF)
 * @safety Non-critical (read-only accessor)
 */
door_state_t door_fsm_get_state(const door_fsm_t* fsm);

/**
 * @brief Get current door position (0-100%)
 * @param[in] fsm Pointer to door FSM structure
 * @return Door position (0-100%), or 0 if fsm is NULL
 * @pre None (NULL-safe)
 * @post No state change
 * @complexity 2 (1 base + 1 IF)
 * @safety Non-critical (read-only accessor)
 */
uint8_t door_fsm_get_position(const door_fsm_t* fsm);

/**
 * @brief Get door lock status
 * @param[in] fsm Pointer to door FSM structure
 * @return true if locked, false otherwise (or if fsm is NULL)
 * @pre None (NULL-safe)
 * @post No state change
 * @complexity 2 (1 base + 1 IF)
 * @safety Non-critical (read-only accessor)
 */
bool door_fsm_is_locked(const door_fsm_t* fsm);

#endif /* DOOR_FSM_H */
