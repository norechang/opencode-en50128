/**
 * @file fault_detection.h
 * @brief Fault Detection and Diagnosis Module (MOD-003)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.3 (MOD-003)
 * 
 * @description
 * Fault detection module: logs faults with timestamps and severity,
 * manages circular fault log, detects critical faults for safe state entry.
 * Maximum cyclomatic complexity: 7 (SIL 3 target: ≤10).
 * 
 * @memory_footprint
 * - fault_entry_t: 8 bytes each
 * - fault_detection_t: 259 bytes (32 × 8 + 3)
 * - Total: 259 bytes
 */

#ifndef FAULT_DETECTION_H
#define FAULT_DETECTION_H

#include "../common/types.h"
#include "../common/error_codes.h"

/*===========================================================================*/
/* Constants                                                                 */
/*===========================================================================*/

/** Fault log configuration */
#define FAULT_LOG_SIZE               (32U)       /**< 32 fault entries */
#define FAULT_AGE_TIMEOUT_MS         (10000U)    /**< 10 seconds timeout */

/*===========================================================================*/
/* Enumerations                                                              */
/*===========================================================================*/

/**
 * @brief Fault severity levels
 * @compliance MISRA C:2012 Rule 8.2 (complete type definitions)
 */
typedef enum {
    FAULT_SEVERITY_MINOR = 0U,       /**< Warning, system continues */
    FAULT_SEVERITY_MAJOR = 1U,       /**< Degraded mode */
    FAULT_SEVERITY_CRITICAL = 2U,    /**< Safe state entry required */
    FAULT_SEVERITY_MAX = 3U          /**< Sentinel value */
} fault_severity_t;

/**
 * @brief Fault code type
 * @compliance MISRA C:2012 (fixed-width integer)
 */
typedef uint16_t fault_code_t;

/*===========================================================================*/
/* Fault Code Definitions                                                    */
/*===========================================================================*/

/** No fault */
#define FAULT_NONE                       (0x0000U)

/** Sensor faults */
#define FAULT_POSITION_SENSOR_LEFT       (0x0001U)
#define FAULT_POSITION_SENSOR_RIGHT      (0x0002U)
#define FAULT_OBSTACLE_SENSOR_LEFT       (0x0003U)
#define FAULT_OBSTACLE_SENSOR_RIGHT      (0x0004U)
#define FAULT_SPEED_SENSOR_PRIMARY       (0x0005U)
#define FAULT_SPEED_SENSOR_SECONDARY     (0x0006U)
#define FAULT_SPEED_SENSOR_DISAGREE      (0x0007U)
#define FAULT_SPEED_SENSOR_BOTH          (0x0008U)  /**< CRITICAL */

/** Door operation faults */
#define FAULT_DOOR_OPEN_TIMEOUT          (0x0010U)
#define FAULT_DOOR_CLOSE_TIMEOUT         (0x0011U)
#define FAULT_DOOR_NOT_CLOSED_MOVING     (0x0012U)  /**< CRITICAL */

/** Obstacle detection */
#define FAULT_OBSTACLE_DETECTED          (0x0020U)

/** Communication faults */
#define FAULT_CAN_TIMEOUT                (0x0030U)

/** System faults */
#define FAULT_WATCHDOG_TIMEOUT           (0x0040U)  /**< CRITICAL */

/*===========================================================================*/
/* Data Structures                                                           */
/*===========================================================================*/

/**
 * @brief Fault log entry structure
 * @compliance MISRA C:2012 Rule 8.2 (complete type definitions)
 */
typedef struct {
    fault_code_t code;           /**< Fault code (2 bytes) */
    fault_severity_t severity;   /**< Fault severity (1 byte) */
    uint32_t timestamp;          /**< Timestamp in ms since boot (4 bytes) */
    bool active;                 /**< Active flag (1 byte) */
    /* Total: 8 bytes per entry */
} fault_entry_t;

/**
 * @brief Fault detection module state structure
 * @compliance Static allocation ONLY (259 bytes fixed size)
 */
typedef struct {
    fault_entry_t fault_log[FAULT_LOG_SIZE];  /**< Circular fault log (256 bytes) */
    uint8_t fault_log_head;                   /**< Next write index (1 byte) */
    uint8_t fault_log_count;                  /**< Active fault count (1 byte) */
    bool critical_fault_active;               /**< Critical fault flag (1 byte) */
    /* Total: 259 bytes */
} fault_detection_t;

/*===========================================================================*/
/* Public Function Prototypes                                                */
/*===========================================================================*/

/**
 * @brief Initialize fault detection module
 * @param[in,out] fd Pointer to fault detection structure
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 2 (1 base + 1 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.3.1
 */
error_t fault_detection_init(fault_detection_t* fd);

/**
 * @brief Update fault detection, age faults, clear expired faults
 * @param[in,out] fd Pointer to fault detection structure
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 6 (1 base + 5 IF/FOR)
 * @traceability DOC-COMPDES-2026-001 Section 3.3.2
 */
error_t fault_detection_update(fault_detection_t* fd);

/**
 * @brief Report a fault with timestamp and severity
 * @param[in,out] fd Pointer to fault detection structure
 * @param[in] code Fault code
 * @param[in] severity Fault severity level
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 7 (1 base + 6 IF/FOR)
 * @traceability DOC-COMPDES-2026-001 Section 3.3.3
 */
error_t fault_detection_report_fault(fault_detection_t* fd, fault_code_t code, fault_severity_t severity);

/**
 * @brief Check if any critical fault is active
 * @param[in] fd Pointer to fault detection structure
 * @return true if critical fault active, false otherwise (NULL-safe, fail-safe)
 * @complexity 2 (1 base + 1 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.3.4
 * @safety CRITICAL - Triggers safe state entry
 */
bool fault_detection_is_critical_fault_active(const fault_detection_t* fd);

/**
 * @brief Get all active fault codes (for status reporting)
 * @param[in] fd Pointer to fault detection structure
 * @param[out] buffer Buffer to store active fault codes
 * @param[in] buffer_size Size of buffer
 * @return Number of faults copied (0 if NULL or buffer full)
 * @complexity 5 (1 base + 4 IF/FOR)
 * @traceability DOC-COMPDES-2026-001 Section 3.3.5
 */
uint8_t fault_detection_get_active_faults(const fault_detection_t* fd, 
                                           fault_code_t* buffer, 
                                           uint8_t buffer_size);

/**
 * @brief Clear a fault (manual reset)
 * @param[in,out] fd Pointer to fault detection structure
 * @param[in] code Fault code to clear
 * @return ERROR_SUCCESS on success, ERROR_INVALID_PARAMETER if fault not found
 * @complexity 5 (1 base + 4 IF/FOR)
 * @traceability DOC-COMPDES-2026-001 Section 3.3.6
 */
error_t fault_detection_clear_fault(fault_detection_t* fd, fault_code_t code);

#endif /* FAULT_DETECTION_H */
