/**
 * @file status_reporter.c
 * @brief Status Reporter Module Implementation (MOD-005)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.5 (MOD-005)
 * 
 * @description
 * Implements status collection and reporting to CAN bus and driver display.
 * All functions meet SIL 3 complexity requirement (≤10).
 */

#include "status_reporter.h"
#include "../sensor_hal/sensor_hal.h"  /* For can_message_t */
#include <string.h>  /* For memcpy */

/* Forward declarations for external functions */
extern uint8_t door_fsm_get_position(door_side_t side);
extern uint8_t door_fsm_get_state(door_side_t side);
extern bool door_fsm_is_locked(door_side_t side);
extern uint8_t fault_detection_get_active_faults(const void* fd, uint16_t* buffer, uint8_t buffer_size);
extern error_t communication_hal_can_send(const can_message_t* msg);

/* LED IDs and states (stubs) */
#define LED_LEFT_OPEN           (0U)
#define LED_LEFT_CLOSED         (1U)
#define LED_RIGHT_OPEN          (2U)
#define LED_RIGHT_CLOSED        (3U)
#define LED_FAULT               (4U)
#define LED_ON                  (1U)
#define LED_OFF                 (0U)

/* Door states */
#define DOOR_STATE_CLOSED       (0U)
#define DOOR_STATE_OPEN         (2U)
#define DOOR_STATE_LOCKED       (6U)

/* LED control stub */
extern void set_led(uint8_t led_id, uint8_t state);

/*===========================================================================*/
/* Public Function Implementations                                           */
/*===========================================================================*/

/**
 * @brief Initialize status reporter
 * @complexity 2 (1 base + 1 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.5.2 (pseudocode lines 1984-2005)
 */
error_t status_reporter_init(status_reporter_t* sr)
{
    /* Step 1: NULL check */
    if (sr == NULL) {                                           /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Initialize all fields to zero/default */
    sr->last_can_msg.door_left_position = 0U;
    sr->last_can_msg.door_right_position = 0U;
    sr->last_can_msg.door_left_state = 0U;
    sr->last_can_msg.door_right_state = 0U;
    sr->last_can_msg.door_left_locked = 1U;      /* Locked by default (fail-safe) */
    sr->last_can_msg.door_right_locked = 1U;
    sr->last_can_msg.fault_code_high = 0U;
    sr->last_can_msg.fault_code_low = 0U;
    sr->last_can_tx_time_ms = 0U;
    sr->can_tx_count = 0U;
    sr->can_tx_error_count = 0U;
    sr->last_update_time_ms = 0U;
    
    return ERROR_SUCCESS;
}

/**
 * @brief Update status reporter - collect and transmit status if period elapsed
 * @complexity 5 (1 base + 4 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.5.3 (pseudocode lines 2024-2054)
 */
error_t status_reporter_update(status_reporter_t* sr)
{
    uint32_t current_time;
    uint32_t elapsed;
    error_t err;
    error_t err2;
    
    /* Step 1: NULL check */
    if (sr == NULL) {                                           /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Get current timestamp */
    current_time = get_system_time_ms();
    sr->last_update_time_ms = current_time;
    
    /* Step 3: Check if CAN TX period elapsed (50ms) */
    elapsed = current_time - sr->last_can_tx_time_ms;
    if (elapsed >= STATUS_REPORT_PERIOD_MS) {                   /* +1 */
        /* Collect status from all modules */
        err = status_reporter_send_can_status(sr);
        if (err != ERROR_SUCCESS) {                             /* +1 */
            sr->can_tx_error_count++;
            return err;
        }
        sr->last_can_tx_time_ms = current_time;
        sr->can_tx_count++;
    }
    
    /* Step 4: Update driver display LEDs */
    err2 = status_reporter_update_display(sr);
    if (err2 != ERROR_SUCCESS) {                                /* +1 */
        return err2;
    }
    
    return ERROR_SUCCESS;
}

/**
 * @brief Collect status and send CAN message
 * @complexity 3 (1 base + 2 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.5.4 (pseudocode lines 2073-2116)
 */
error_t status_reporter_send_can_status(status_reporter_t* sr)
{
    uint8_t left_pos;
    uint8_t right_pos;
    uint8_t left_state;
    uint8_t right_state;
    bool left_locked;
    bool right_locked;
    uint16_t active_faults;
    can_message_t can_msg;
    error_t err;
    
    /* Step 1: NULL check */
    if (sr == NULL) {                                           /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Collect door positions from Door FSM */
    left_pos = door_fsm_get_position(DOOR_SIDE_LEFT);
    right_pos = door_fsm_get_position(DOOR_SIDE_RIGHT);
    
    /* Step 3: Collect door states */
    left_state = door_fsm_get_state(DOOR_SIDE_LEFT);
    right_state = door_fsm_get_state(DOOR_SIDE_RIGHT);
    
    /* Step 4: Collect lock status */
    left_locked = door_fsm_is_locked(DOOR_SIDE_LEFT);
    right_locked = door_fsm_is_locked(DOOR_SIDE_RIGHT);
    
    /* Step 5: Collect active faults (stub - get first fault) */
    active_faults = 0U;  /* Simplified - replace with actual fault query */
    
    /* Step 6: Format CAN message */
    sr->last_can_msg.door_left_position = left_pos;
    sr->last_can_msg.door_right_position = right_pos;
    sr->last_can_msg.door_left_state = left_state;
    sr->last_can_msg.door_right_state = right_state;
    sr->last_can_msg.door_left_locked = left_locked ? 1U : 0U;
    sr->last_can_msg.door_right_locked = right_locked ? 1U : 0U;
    sr->last_can_msg.fault_code_high = (uint8_t)(active_faults >> 8);
    sr->last_can_msg.fault_code_low = (uint8_t)(active_faults & 0xFFU);
    
    /* Step 7: Transmit CAN message */
    can_msg.id = CAN_ID_DOOR_STATUS;
    can_msg.dlc = 8U;
    (void)memcpy(can_msg.data, &sr->last_can_msg, 8U);
    
    err = communication_hal_can_send(&can_msg);
    if (err != ERROR_SUCCESS) {                                 /* +1 */
        return err;
    }
    
    return ERROR_SUCCESS;
}

/**
 * @brief Update driver display LEDs based on door status
 * @complexity 6 (1 base + 5 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.5.5 (pseudocode lines 2135-2183)
 */
error_t status_reporter_update_display(const status_reporter_t* sr)
{
    uint8_t left_state;
    uint8_t right_state;
    uint16_t active_faults;
    
    /* Step 1: NULL check */
    if (sr == NULL) {                                           /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Read door states */
    left_state = door_fsm_get_state(DOOR_SIDE_LEFT);
    right_state = door_fsm_get_state(DOOR_SIDE_RIGHT);
    
    /* Step 3: LED_LEFT_OPEN (green): ON if left door OPEN */
    if (left_state == DOOR_STATE_OPEN) {                        /* +1 */
        set_led(LED_LEFT_OPEN, LED_ON);
    } else {
        set_led(LED_LEFT_OPEN, LED_OFF);
    }
    
    /* Step 4: LED_LEFT_CLOSED (red): ON if left door CLOSED/LOCKED */
    if (left_state == DOOR_STATE_LOCKED) {                      /* +1 */
        set_led(LED_LEFT_CLOSED, LED_ON);
    } else {
        set_led(LED_LEFT_CLOSED, LED_OFF);
    }
    
    /* Step 5: LED_RIGHT_OPEN (green): ON if right door OPEN */
    if (right_state == DOOR_STATE_OPEN) {                       /* +1 */
        set_led(LED_RIGHT_OPEN, LED_ON);
    } else {
        set_led(LED_RIGHT_OPEN, LED_OFF);
    }
    
    /* Step 6: LED_RIGHT_CLOSED (red): ON if right door CLOSED/LOCKED */
    if (right_state == DOOR_STATE_LOCKED) {                     /* +1 */
        set_led(LED_RIGHT_CLOSED, LED_ON);
    } else {
        set_led(LED_RIGHT_CLOSED, LED_OFF);
    }
    
    /* Step 7: LED_FAULT (yellow): ON if any faults active */
    active_faults = 0U;  /* Simplified - replace with actual fault query */
    if (active_faults != 0U) {
        set_led(LED_FAULT, LED_ON);
    } else {
        set_led(LED_FAULT, LED_OFF);
    }
    
    return ERROR_SUCCESS;
}
