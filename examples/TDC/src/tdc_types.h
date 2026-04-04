/**
 * @file    tdc_types.h
 * @brief   System-wide common types, constants, and error codes for TDC
 * @details Defines all shared types used by every component in the Train Door
 *          Control System. All types use fixed-width integers per MISRA C:2012.
 *
 * @project TDC (Train Door Control System)
 * @module  Common Types
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety
 * SIL Level: 3
 * Safety Requirements: REQ-SAFE-001 through REQ-SAFE-021 (shared types)
 *
 * @misra_compliance
 * MISRA C:2012 Compliance:
 * - All mandatory rules: Compliant
 * - Fixed-width types only (Rule 4.6, Directive 4.6)
 * - No variably-modified types
 * - Include guards present (Rule 21.1 pattern)
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4 (Software Design and Implementation)
 * - EN 50128:2011 Table A.4 (Implementation techniques)
 * - SCDS DOC-COMPDES-2026-001 §2.1
 */

/* MISRA C:2012 Rule 21.1: Include guard */
#ifndef TDC_TYPES_H
#define TDC_TYPES_H

/*============================================================================
 * INCLUDES
 *===========================================================================*/
#include <stdint.h>   /* Fixed-width integer types — MANDATORY SIL 2+ */
#include <stdbool.h>  /* bool type */
#include <stddef.h>   /* NULL, size_t */

/*============================================================================
 * SYSTEM CONSTANTS
 * Implements: REQ-SAFE-001, REQ-SAFE-003, REQ-INT-001
 * Design ref: SCDS DOC-COMPDES-2026-001 §2.1
 *===========================================================================*/

/** @brief Maximum number of doors in the system */
#define MAX_DOORS         (4U)

/** @brief Maximum number of DDU (Door Drive Unit) nodes */
#define MAX_DDU_NODES     (4U)

/** @brief Maximum number of event log entries */
#define MAX_LOG_ENTRIES   (1024U)

/** @brief Speed threshold for door interlock: 5.0 km/h expressed as × 10 */
#define SPEED_THRESHOLD   (50U)

/** @brief CAN communication timeout in milliseconds */
#define CAN_TIMEOUT_MS    (200U)

/** @brief SPI communication timeout in milliseconds */
#define SPI_TIMEOUT_MS    (5U)

/** @brief Watchdog refresh period in milliseconds */
#define WDG_REFRESH_MS    (40U)

/** @brief System cycle period in milliseconds */
#define CYCLE_MS          (20U)

/*============================================================================
 * ERROR CODES
 * Implements: REQ-SAFE-012, REQ-SAFE-013
 * Design ref: SCDS DOC-COMPDES-2026-001 §2.1
 *===========================================================================*/

/**
 * @brief System-wide error code enumeration.
 * @note  All callers MUST check every non-void function return value.
 */
typedef enum {
    SUCCESS             = 0,  /**< Operation completed successfully */
    ERR_NULL_PTR        = 1,  /**< NULL pointer argument detected */
    ERR_RANGE           = 2,  /**< Parameter out of valid range */
    ERR_TIMEOUT         = 3,  /**< Communication or operation timeout */
    ERR_CRC             = 4,  /**< CRC-16 validation failure */
    ERR_HW_FAULT        = 5,  /**< Hardware fault detected */
    ERR_INVALID_STATE   = 6,  /**< Invalid state transition requested */
    ERR_NOT_PERMITTED   = 7,  /**< Operation not permitted in current mode */
    ERR_SENSOR_DISAGREE = 8,  /**< 2oo2 sensor disagreement detected */
    ERR_COMM_TIMEOUT    = 9,  /**< Communication channel timeout */
    ERR_WATCHDOG        = 10  /**< Watchdog refresh failure */
} error_t;

/*============================================================================
 * DOOR STATE ENUMERATION
 * Implements: REQ-FUN-001 through REQ-FUN-015, REQ-SAFE-007
 * Design ref: SCDS DOC-COMPDES-2026-001 §2.1
 *===========================================================================*/

/**
 * @brief Externally visible door state.
 * @note  Reported to TCMS via CAN message 0x201.
 */
typedef enum {
    DOOR_STATE_UNKNOWN           = 0,  /**< State not yet determined */
    DOOR_STATE_FULLY_OPEN        = 1,  /**< Door fully open, sensor confirmed */
    DOOR_STATE_INTERMEDIATE      = 2,  /**< Door in transit (opening/closing) */
    DOOR_STATE_FULLY_CLOSED      = 3,  /**< Door fully closed, not yet locked */
    DOOR_STATE_CLOSED_AND_LOCKED = 4,  /**< Door fully closed and locked (2oo2) */
    DOOR_STATE_FAULT             = 5   /**< Door in fault state */
} door_state_t;

/*============================================================================
 * DOOR FSM STATE ENUMERATION
 * Implements: REQ-FUN-001–015, REQ-SAFE-007–011, SW-HAZ-003
 * Design ref: SCDS DOC-COMPDES-2026-001 §6.1
 *===========================================================================*/

/**
 * @brief Internal FSM state for each door.
 */
typedef enum {
    FSM_IDLE              = 0,  /**< Idle — awaiting open command */
    FSM_OPENING           = 1,  /**< Motor driving door open */
    FSM_FULLY_OPEN        = 2,  /**< Door at open position, motor stopped */
    FSM_CLOSING           = 3,  /**< Motor driving door closed */
    FSM_OBSTACLE_REVERSAL = 4,  /**< Obstacle detected — reversing to open */
    FSM_FULLY_CLOSED      = 5,  /**< Door at closed position, not yet locked */
    FSM_LOCKING           = 6,  /**< Lock solenoid energised — awaiting confirmation */
    FSM_CLOSED_AND_LOCKED = 7,  /**< Stable locked state */
    FSM_FAULT             = 8   /**< Fault — motor stopped, lock engaged */
} door_fsm_state_t;

/*============================================================================
 * FAULT SEVERITY ENUMERATION
 * Implements: REQ-SAFE-012, REQ-SAFE-013, REQ-SAFE-021
 * Design ref: SCDS DOC-COMPDES-2026-001 §7.1
 *===========================================================================*/

/**
 * @brief Fault severity levels.
 */
typedef enum {
    FAULT_NONE     = 0,  /**< No active fault */
    FAULT_LOW      = 1,  /**< Low-severity fault — log only */
    FAULT_MEDIUM   = 2,  /**< Medium-severity fault — report to TCMS */
    FAULT_HIGH     = 3,  /**< High-severity fault — disable affected door */
    FAULT_CRITICAL = 4   /**< Critical fault — safe state activation */
} fault_severity_t;

/*============================================================================
 * OPERATIONAL MODE ENUMERATION
 * Implements: REQ-FUN-016, REQ-FUN-017, REQ-SAFE-019, REQ-SAFE-020
 * Design ref: SCDS DOC-COMPDES-2026-001 §6.3
 *===========================================================================*/

/**
 * @brief System operational mode.
 */
typedef enum {
    MODE_NORMAL        = 0,  /**< Normal service operation */
    MODE_DIAGNOSTIC    = 1,  /**< Diagnostic mode (speed = 0 required) */
    MODE_MAINTENANCE   = 2,  /**< Maintenance mode (authorised personnel only) */
    MODE_DOOR_DISABLED = 3   /**< Door disabled mode */
} op_mode_t;

/*============================================================================
 * CROSS-CHANNEL SPI STATE STRUCTURE
 * Implements: REQ-SAFE-002, REQ-SAFE-008, SW-HAZ-001/003/011
 * Design ref: SCDS DOC-COMPDES-2026-001 §2.1, §3.1
 *===========================================================================*/

/**
 * @brief Cross-channel state exchanged via SPI between the two DCU channels.
 * @note  All safety-critical fields are covered by crc16 (CRC-16-CCITT 0x1021).
 *        The crc16 field itself is excluded from the CRC computation.
 */
typedef struct {
    uint16_t speed_kmh_x10;               /**< Current speed × 10 (km/h) */
    uint8_t  door_states[MAX_DOORS];      /**< Door state per door (door_state_t) */
    uint8_t  lock_states[MAX_DOORS];      /**< Lock sensor state per door (0/1) */
    uint8_t  obstacle_flags[MAX_DOORS];   /**< Obstacle detection flag per door */
    uint8_t  fault_flags;                 /**< Aggregated fault bitmask from FMG */
    uint8_t  safety_decisions;            /**< bit0=safe_state_active, bit1=departure_interlock_ok */
    uint16_t crc16;                       /**< CRC-16-CCITT over all preceding bytes */
} cross_channel_state_t;

/*============================================================================
 * TCMS SPEED CAN MESSAGE STRUCTURE
 * Implements: REQ-SAFE-001, REQ-SAFE-003, REQ-INT-007
 * Design ref: SCDS DOC-COMPDES-2026-001 §4.1
 *===========================================================================*/

/**
 * @brief CAN speed message received from TCMS on ID 0x100.
 */
typedef struct {
    uint16_t speed_kmh_x10;  /**< Speed × 10 (km/h), range 0–3000 */
    uint8_t  seq_counter;    /**< Rolling sequence counter (modulo 256) */
    uint16_t crc16;          /**< CRC-16-CCITT over speed and seq_counter */
} tcms_speed_msg_t;

/*============================================================================
 * EVENT LOG ENTRY STRUCTURE
 * Implements: REQ-FUN-018
 * Design ref: SCDS DOC-COMPDES-2026-001 §9
 *===========================================================================*/

/**
 * @brief Single event log entry (stored in circular buffer by DGN).
 */
typedef struct {
    uint32_t timestamp_ms;  /**< System tick at event time */
    uint8_t  source_comp;   /**< Source component ID (COMP_xxx constants) */
    uint8_t  event_code;    /**< Event code (EVT_xxx constants) */
    uint16_t data;          /**< Event-specific data payload */
    uint16_t crc16;         /**< CRC-16-CCITT over preceding 8 bytes */
} event_log_entry_t;

/*============================================================================
 * COMPONENT ID CONSTANTS (for DGN logging)
 *===========================================================================*/
#define COMP_SKN  (0x01U)  /**< Safety Kernel component ID */
#define COMP_SPM  (0x02U)  /**< Speed Monitor component ID */
#define COMP_OBD  (0x03U)  /**< Obstacle Detector component ID */
#define COMP_DSM  (0x04U)  /**< Door State Machine component ID */
#define COMP_FMG  (0x05U)  /**< Fault Manager component ID */
#define COMP_TCI  (0x06U)  /**< TCMS Interface component ID */
#define COMP_DGN  (0x07U)  /**< Diagnostics component ID */
#define COMP_HAL  (0x08U)  /**< Hardware Abstraction Layer component ID */

/*============================================================================
 * EVENT CODE CONSTANTS (for DGN logging)
 *===========================================================================*/
#define EVT_SPI_INFRA_TRANSIENT    (0x01U)  /**< SPI transient infrastructure fault */
#define EVT_SPI_INFRA_PERSISTENT   (0x02U)  /**< SPI persistent infrastructure fault */
#define EVT_SPI_CRC_FAIL           (0x03U)  /**< SPI CRC-16 failure */
#define EVT_CHANNEL_DISAGREE       (0x04U)  /**< Cross-channel safety data disagreement */
#define EVT_CAN_CRC_FAIL           (0x05U)  /**< CAN message CRC-16 failure */
#define EVT_CAN_SEQ_SKIP           (0x06U)  /**< CAN sequence counter discontinuity */
#define EVT_SPEED_RANGE_ERR        (0x07U)  /**< Speed value out of valid range */
#define EVT_SENSOR_DISAGREE        (0x08U)  /**< 2oo2 sensor disagreement */
#define EVT_FSM_FAULT              (0x09U)  /**< Door FSM entered FAULT state */
#define EVT_FAULT_ACTIVE           (0x0AU)  /**< Fault activated in FMG */
#define EVT_SELECTIVE_DISABLE      (0x0BU)  /**< Door selectively disabled */
#define EVT_SELECTIVE_DISABLE_UNAUTHORIZED (0x0CU) /**< Unauthorised disable attempt */
#define EVT_EMERGENCY_RELEASE      (0x0DU)  /**< Emergency door release activated */
#define EVT_SEQ_DISCONTINUITY      (0x0EU)  /**< CAN Rx sequence discontinuity */
#define EVT_LOG_INIT               (0x0FU)  /**< Diagnostic log initialised */

/*============================================================================
 * SAFETY GLOBALS MEMORY REGION CONSTANTS (for SKN memory integrity)
 * Implements: REQ-SAFE-009, SW-HAZ-008
 *===========================================================================*/

/** @brief Length of safety-critical global variable region for CRC snapshot */
#define SAFETY_GLOBALS_LEN  (64U)

/** @brief Stack canary value (fixed pattern for detection) */
#define CANARY_VALUE  (0xDEADBEEFUL)

#endif /* TDC_TYPES_H */

/*============================================================================
 * END OF FILE
 *===========================================================================*/
