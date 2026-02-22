/**
 * @file status_reporter.h
 * @brief Status Reporter Module (MOD-005)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.5 (MOD-005)
 * 
 * @description
 * Collect status from all modules and report to train control system (CAN)
 * and driver display at 20 Hz.
 * Maximum cyclomatic complexity: 6 (SIL 3 target: ≤10).
 * 
 * @memory_footprint
 * - status_reporter_t: 24 bytes
 * - can_msg_door_status_t: 8 bytes
 * - Total: 32 bytes
 */

#ifndef STATUS_REPORTER_H
#define STATUS_REPORTER_H

#include "../common/types.h"
#include "../common/error_codes.h"

/*===========================================================================*/
/* Constants                                                                 */
/*===========================================================================*/

/** Status report period (20 Hz = 50ms) */
#define STATUS_REPORT_PERIOD_MS    (50U)

/** CAN message ID for door status */
#define CAN_ID_DOOR_STATUS         (0x201U)

/*===========================================================================*/
/* Data Structures                                                           */
/*===========================================================================*/

/**
 * @brief CAN door status message structure (8 bytes)
 */
typedef struct {
    uint8_t door_left_position;      /**< Left door position (0-100%) */
    uint8_t door_right_position;     /**< Right door position (0-100%) */
    uint8_t door_left_state;         /**< Left door state (0=CLOSED, 1=OPEN, etc.) */
    uint8_t door_right_state;        /**< Right door state */
    uint8_t door_left_locked;        /**< Left door locked (0=unlocked, 1=locked) */
    uint8_t door_right_locked;       /**< Right door locked */
    uint8_t fault_code_high;         /**< Upper byte of active fault code */
    uint8_t fault_code_low;          /**< Lower byte of active fault code */
} can_msg_door_status_t;

/**
 * @brief Status reporter state structure (24 bytes)
 */
typedef struct {
    can_msg_door_status_t last_can_msg;  /**< Last CAN message (8 bytes) */
    uint32_t last_can_tx_time_ms;        /**< Last CAN TX timestamp (4 bytes) */
    uint32_t can_tx_count;               /**< CAN TX count (4 bytes) */
    uint8_t can_tx_error_count;          /**< CAN TX error count (1 byte) */
    uint32_t last_update_time_ms;        /**< Last update timestamp (4 bytes) */
    /* Total: 21 bytes (3 bytes padding for alignment) */
} status_reporter_t;

/*===========================================================================*/
/* Public Function Prototypes                                                */
/*===========================================================================*/

/**
 * @brief Initialize status reporter
 * @param[in,out] sr Pointer to status reporter structure
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 2 (1 base + 1 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.5.2
 */
error_t status_reporter_init(status_reporter_t* sr);

/**
 * @brief Update status reporter - collect and transmit status if period elapsed
 * @param[in,out] sr Pointer to status reporter structure
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 5 (1 base + 4 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.5.3
 */
error_t status_reporter_update(status_reporter_t* sr);

/**
 * @brief Collect status and send CAN message
 * @param[in,out] sr Pointer to status reporter structure
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 3 (1 base + 2 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.5.4
 */
error_t status_reporter_send_can_status(status_reporter_t* sr);

/**
 * @brief Update driver display LEDs based on door status
 * @param[in] sr Pointer to status reporter structure
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 6 (1 base + 5 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.5.5
 */
error_t status_reporter_update_display(const status_reporter_t* sr);

#endif /* STATUS_REPORTER_H */
