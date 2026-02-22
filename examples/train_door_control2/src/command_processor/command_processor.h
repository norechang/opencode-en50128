/**
 * @file command_processor.h
 * @brief Command Processor Module (MOD-004)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.4 (MOD-004)
 * 
 * @description
 * Process door commands from driver panel and CAN bus.
 * Maximum cyclomatic complexity: 8 (SIL 3 target: ≤10).
 * 
 * @memory_footprint
 * - command_processor_t: 12 bytes
 * - Total: 12 bytes
 */

#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "../common/types.h"
#include "../common/error_codes.h"
#include "../sensor_hal/sensor_hal.h"  /* For can_message_t */

/*===========================================================================*/
/* Constants                                                                 */
/*===========================================================================*/

/** CAN command timeout (1 second) */
#define CMD_PROC_CAN_TIMEOUT_MS    (1000U)

/** CAN message ID for door commands */
#define CAN_ID_DOOR_COMMAND        (0x200U)

/*===========================================================================*/
/* Enumerations                                                              */
/*===========================================================================*/

/**
 * @brief Driver panel commands
 */
typedef enum {
    DRIVER_CMD_NONE = 0U,
    DRIVER_CMD_OPEN_LEFT = 1U,
    DRIVER_CMD_OPEN_RIGHT = 2U,
    DRIVER_CMD_OPEN_ALL = 3U,
    DRIVER_CMD_CLOSE_LEFT = 4U,
    DRIVER_CMD_CLOSE_RIGHT = 5U,
    DRIVER_CMD_CLOSE_ALL = 6U,
    DRIVER_CMD_EMERGENCY_EVAC = 7U,
    DRIVER_CMD_MAX = 8U
} driver_command_t;

/**
 * @brief Operational modes
 */
typedef enum {
    MODE_NORMAL = 0U,
    MODE_MANUAL = 1U,
    MODE_EMERGENCY = 2U,
    MODE_DIAGNOSTIC = 3U,
    MODE_DEGRADED = 4U,
    MODE_MAX = 5U
} operation_mode_t;

/**
 * @brief Door event type (from door_fsm.h)
 */
typedef uint8_t door_event_t;
#define DOOR_EVENT_NONE      (0U)
#define DOOR_EVENT_OPEN_CMD  (1U)
#define DOOR_EVENT_CLOSE_CMD (2U)

/*===========================================================================*/
/* Data Structures                                                           */
/*===========================================================================*/

/**
 * @brief Command processor state structure
 */
typedef struct {
    operation_mode_t current_mode;       /**< Current operational mode (1 byte) */
    uint32_t last_can_cmd_time_ms;       /**< Last CAN command timestamp (4 bytes) */
    bool can_cmd_timeout;                /**< CAN command timeout flag (1 byte) */
    door_event_t pending_cmd_left;       /**< Pending left door command (1 byte) */
    door_event_t pending_cmd_right;      /**< Pending right door command (1 byte) */
    uint32_t last_update_time_ms;        /**< Last update timestamp (4 bytes) */
    /* Total: 12 bytes */
} command_processor_t;

/*===========================================================================*/
/* Public Function Prototypes                                                */
/*===========================================================================*/

/**
 * @brief Initialize command processor
 * @param[in,out] cp Pointer to command processor structure
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 2 (1 base + 1 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.4.1
 */
error_t command_processor_init(command_processor_t* cp);

/**
 * @brief Update command processor, check timeouts, dispatch commands
 * @param[in,out] cp Pointer to command processor structure
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 8 (1 base + 7 IF/SWITCH)
 * @traceability DOC-COMPDES-2026-001 Section 3.4.2
 */
error_t command_processor_update(command_processor_t* cp);

/**
 * @brief Process driver panel button press
 * @param[in,out] cp Pointer to command processor structure
 * @param[in] cmd Driver command
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 6 (1 base + 5 IF/SWITCH)
 * @traceability DOC-COMPDES-2026-001 Section 3.4.3
 */
error_t command_processor_process_driver_command(command_processor_t* cp, driver_command_t cmd);

/**
 * @brief Process CAN bus door command message
 * @param[in,out] cp Pointer to command processor structure
 * @param[in] msg CAN message
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 7 (1 base + 6 IF/SWITCH)
 * @traceability DOC-COMPDES-2026-001 Section 3.4.4
 */
error_t command_processor_process_can_command(command_processor_t* cp, const can_message_t* msg);

/**
 * @brief Set operational mode
 * @param[in,out] cp Pointer to command processor structure
 * @param[in] mode Operational mode
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 5 (1 base + 4 IF/SWITCH)
 * @traceability DOC-COMPDES-2026-001 Section 3.4.5
 */
error_t command_processor_set_mode(command_processor_t* cp, operation_mode_t mode);

/**
 * @brief Get current operational mode
 * @param[in] cp Pointer to command processor structure
 * @return Current operational mode (MODE_NORMAL if NULL)
 * @complexity 2 (1 base + 1 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.4.6
 */
operation_mode_t command_processor_get_mode(const command_processor_t* cp);

#endif /* COMMAND_PROCESSOR_H */
