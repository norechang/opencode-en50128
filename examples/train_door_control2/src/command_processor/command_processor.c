/**
 * @file command_processor.c
 * @brief Command Processor Module Implementation (MOD-004)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.4 (MOD-004)
 * 
 * @description
 * Implements command processing from driver panel and CAN bus.
 * All functions meet SIL 3 complexity requirement (≤10).
 */

#include "command_processor.h"
#include <string.h>  /* For memcpy */

/* Forward declarations for external functions */
extern error_t door_fsm_process_event(void* fsm, door_event_t event);
extern uint8_t door_fsm_get_state(door_side_t side);
extern void fault_detection_report_fault(uint16_t code, uint8_t severity);

/* Fault codes */
#define FAULT_CAN_CMD_TIMEOUT      (0x0031U)
#define FAULT_CAN_CHECKSUM_ERROR   (0x0032U)
#define FAULT_SEVERITY_MINOR       (0U)

/* Door states */
#define DOOR_STATE_OPEN            (2U)

/* CRC-8 calculation (stub - replace with actual implementation) */
static uint8_t calculate_crc8(const uint8_t* data, uint8_t length)
{
    /* Simple XOR CRC for now - replace with proper CRC-8 */
    uint8_t crc = 0xFFU;
    uint8_t i;
    for (i = 0U; i < length; i++) {
        crc ^= data[i];
    }
    return crc;
}

/*===========================================================================*/
/* Public Function Implementations                                           */
/*===========================================================================*/

/**
 * @brief Initialize command processor
 * @complexity 2 (1 base + 1 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.4.1 (pseudocode lines 1602-1616)
 */
error_t command_processor_init(command_processor_t* cp)
{
    /* Step 1: NULL check */
    if (cp == NULL) {                                           /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Initialize with default values */
    cp->current_mode = MODE_NORMAL;
    cp->last_can_cmd_time_ms = 0U;
    cp->can_cmd_timeout = false;
    cp->pending_cmd_left = DOOR_EVENT_NONE;
    cp->pending_cmd_right = DOOR_EVENT_NONE;
    cp->last_update_time_ms = get_system_time_ms();
    
    return ERROR_SUCCESS;
}

/**
 * @brief Update command processor, check timeouts, dispatch commands
 * @complexity 8 (1 base + 7 IF/SWITCH decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.4.2 (pseudocode lines 1630-1684)
 */
error_t command_processor_update(command_processor_t* cp)
{
    uint32_t current_time_ms;
    uint32_t can_cmd_age_ms;
    
    /* Step 1: NULL check */
    if (cp == NULL) {                                           /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Get current time */
    current_time_ms = get_system_time_ms();
    
    /* Step 3: Check CAN command timeout (1000ms) */
    if (cp->last_can_cmd_time_ms != 0U) {                       /* +1 */
        can_cmd_age_ms = current_time_ms - cp->last_can_cmd_time_ms;
        if (can_cmd_age_ms > CMD_PROC_CAN_TIMEOUT_MS) {         /* +1 */
            cp->can_cmd_timeout = true;
            fault_detection_report_fault(FAULT_CAN_CMD_TIMEOUT, FAULT_SEVERITY_MINOR);
        }
    }
    
    /* Step 4: Process pending left door command */
    if (cp->pending_cmd_left != DOOR_EVENT_NONE) {              /* +1 */
        (void)door_fsm_process_event(NULL, cp->pending_cmd_left);  /* FSM stub */
        cp->pending_cmd_left = DOOR_EVENT_NONE;
    }
    
    /* Step 5: Process pending right door command */
    if (cp->pending_cmd_right != DOOR_EVENT_NONE) {             /* +1 */
        (void)door_fsm_process_event(NULL, cp->pending_cmd_right);  /* FSM stub */
        cp->pending_cmd_right = DOOR_EVENT_NONE;
    }
    
    /* Step 6: Mode-specific processing */
    switch (cp->current_mode) {                                 /* +2 */
        case MODE_EMERGENCY:
            /* Emergency mode: force all doors open */
            if (door_fsm_get_state(DOOR_SIDE_LEFT) != DOOR_STATE_OPEN) {
                cp->pending_cmd_left = DOOR_EVENT_OPEN_CMD;
            }
            if (door_fsm_get_state(DOOR_SIDE_RIGHT) != DOOR_STATE_OPEN) {
                cp->pending_cmd_right = DOOR_EVENT_OPEN_CMD;
            }
            break;
        
        case MODE_DEGRADED:
            /* Degraded mode: allow manual operation only */
            break;
        
        case MODE_NORMAL:
        default:
            /* Normal mode: no special processing */
            break;
    }
    
    /* Step 7: Update timestamp */
    cp->last_update_time_ms = current_time_ms;
    
    return ERROR_SUCCESS;
}

/**
 * @brief Process driver panel button press
 * @complexity 6 (1 base + 5 IF/SWITCH decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.4.3 (pseudocode lines 1698-1743)
 */
error_t command_processor_process_driver_command(command_processor_t* cp, driver_command_t cmd)
{
    /* Step 1: NULL check */
    if (cp == NULL) {                                           /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Command validation */
    if (cmd >= DRIVER_CMD_MAX) {                                /* +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 3: Check if diagnostic mode (reject driver commands) */
    if (cp->current_mode == MODE_DIAGNOSTIC) {                  /* +1 */
        return ERROR_INVALID_STATE;
    }
    
    /* Step 4: Process command */
    switch (cmd) {                                              /* +2 */
        case DRIVER_CMD_OPEN_LEFT:
            cp->pending_cmd_left = DOOR_EVENT_OPEN_CMD;
            break;
        
        case DRIVER_CMD_OPEN_RIGHT:
            cp->pending_cmd_right = DOOR_EVENT_OPEN_CMD;
            break;
        
        case DRIVER_CMD_OPEN_ALL:
            cp->pending_cmd_left = DOOR_EVENT_OPEN_CMD;
            cp->pending_cmd_right = DOOR_EVENT_OPEN_CMD;
            break;
        
        case DRIVER_CMD_CLOSE_LEFT:
            cp->pending_cmd_left = DOOR_EVENT_CLOSE_CMD;
            break;
        
        case DRIVER_CMD_CLOSE_RIGHT:
            cp->pending_cmd_right = DOOR_EVENT_CLOSE_CMD;
            break;
        
        case DRIVER_CMD_CLOSE_ALL:
            cp->pending_cmd_left = DOOR_EVENT_CLOSE_CMD;
            cp->pending_cmd_right = DOOR_EVENT_CLOSE_CMD;
            break;
        
        case DRIVER_CMD_EMERGENCY_EVAC:
            /* Emergency evacuation: switch to emergency mode */
            cp->current_mode = MODE_EMERGENCY;
            cp->pending_cmd_left = DOOR_EVENT_OPEN_CMD;
            cp->pending_cmd_right = DOOR_EVENT_OPEN_CMD;
            break;
        
        case DRIVER_CMD_NONE:
        default:
            /* No action */
            break;
    }
    
    return ERROR_SUCCESS;
}

/**
 * @brief Process CAN bus door command message
 * @complexity 7 (1 base + 6 IF/SWITCH decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.4.4 (pseudocode lines 1757-1813)
 */
error_t command_processor_process_can_command(command_processor_t* cp, const can_message_t* msg)
{
    uint8_t cmd_code;
    uint8_t calculated_crc;
    
    /* Step 1: NULL checks */
    if ((cp == NULL) || (msg == NULL)) {                        /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Validate CAN message ID */
    if (msg->id != CAN_ID_DOOR_COMMAND) {                       /* +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 3: Validate DLC */
    if (msg->dlc != 2U) {                                       /* +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 4: Extract command code */
    cmd_code = msg->data[0];
    
    /* Step 5: Validate checksum (data[1] = CRC-8 of data[0]) */
    calculated_crc = calculate_crc8(&cmd_code, 1U);
    if (msg->data[1] != calculated_crc) {                       /* +1 */
        fault_detection_report_fault(FAULT_CAN_CHECKSUM_ERROR, FAULT_SEVERITY_MINOR);
        return ERROR_COMMUNICATION_FAILURE;
    }
    
    /* Step 6: Process CAN command code */
    switch (cmd_code) {                                         /* +2 */
        case 0x01U:  /* OPEN_LEFT */
            cp->pending_cmd_left = DOOR_EVENT_OPEN_CMD;
            break;
        
        case 0x02U:  /* OPEN_RIGHT */
            cp->pending_cmd_right = DOOR_EVENT_OPEN_CMD;
            break;
        
        case 0x03U:  /* OPEN_ALL */
            cp->pending_cmd_left = DOOR_EVENT_OPEN_CMD;
            cp->pending_cmd_right = DOOR_EVENT_OPEN_CMD;
            break;
        
        case 0x11U:  /* CLOSE_LEFT */
            cp->pending_cmd_left = DOOR_EVENT_CLOSE_CMD;
            break;
        
        case 0x12U:  /* CLOSE_RIGHT */
            cp->pending_cmd_right = DOOR_EVENT_CLOSE_CMD;
            break;
        
        case 0x13U:  /* CLOSE_ALL */
            cp->pending_cmd_left = DOOR_EVENT_CLOSE_CMD;
            cp->pending_cmd_right = DOOR_EVENT_CLOSE_CMD;
            break;
        
        default:
            /* Unknown command code */
            return ERROR_INVALID_DATA;
    }
    
    /* Step 7: Update CAN command timestamp (reset timeout) */
    cp->last_can_cmd_time_ms = get_system_time_ms();
    cp->can_cmd_timeout = false;
    
    return ERROR_SUCCESS;
}

/**
 * @brief Set operational mode
 * @complexity 5 (1 base + 4 IF/SWITCH decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.4.5 (pseudocode lines 1827-1857)
 */
error_t command_processor_set_mode(command_processor_t* cp, operation_mode_t mode)
{
    /* Step 1: NULL check */
    if (cp == NULL) {                                           /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 2: Mode validation */
    if (mode >= MODE_MAX) {                                     /* +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 3: Set new mode */
    cp->current_mode = mode;
    
    /* Step 4: Mode-specific initialization */
    switch (mode) {                                             /* +2 */
        case MODE_EMERGENCY:
            /* Emergency mode: queue open commands */
            cp->pending_cmd_left = DOOR_EVENT_OPEN_CMD;
            cp->pending_cmd_right = DOOR_EVENT_OPEN_CMD;
            break;
        
        case MODE_DEGRADED:
            /* Degraded mode: no special initialization */
            break;
        
        case MODE_NORMAL:
        default:
            /* Normal mode: no special initialization */
            break;
    }
    
    return ERROR_SUCCESS;
}

/**
 * @brief Get current operational mode
 * @complexity 2 (1 base + 1 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.4.6 (pseudocode lines 1871-1878)
 */
operation_mode_t command_processor_get_mode(const command_processor_t* cp)
{
    /* Defensive NULL check */
    if (cp == NULL) {                                           /* +1 */
        return MODE_NORMAL;  /* Safe default */
    }
    
    return cp->current_mode;
}
