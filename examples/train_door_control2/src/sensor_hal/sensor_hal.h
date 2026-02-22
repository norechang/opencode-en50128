/**
 * @file sensor_hal.h
 * @brief Hardware Abstraction Layer for Sensors (MOD-007)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.7 (MOD-007)
 * 
 * @description
 * Provides hardware abstraction for position sensors (ADC), obstacle sensors (GPIO),
 * speed sensors (CAN), and emergency handles (GPIO).
 * Maximum cyclomatic complexity: 7 (SIL 3 target: ≤10).
 * 
 * @memory_footprint
 * - sensor_hal_state_t: 24 bytes
 * - Total: 24 bytes
 */

#ifndef SENSOR_HAL_H
#define SENSOR_HAL_H

#include "../common/types.h"
#include "../common/error_codes.h"

/*===========================================================================*/
/* Constants                                                                 */
/*===========================================================================*/

/** ADC configuration */
#define ADC_MAX_VALUE            (4095U)     /**< 12-bit ADC maximum value */

/** Speed message timeout */
#define SPEED_MSG_TIMEOUT_MS     (200U)      /**< Speed CAN timeout (5 Hz expected) */

/** Position sensor plausibility check */
#define POSITION_MAX_DELTA       (819U)      /**< Max position change per sample (20%) */

/** Median filter configuration */
#define MEDIAN_FILTER_SIZE       (3U)        /**< 3-sample median filter */

/** CAN message IDs */
#define CAN_ID_SPEED_DATA        (0x100U)    /**< Speed data CAN message ID */

/*===========================================================================*/
/* Data Structures                                                           */
/*===========================================================================*/

/**
 * @brief Sensor HAL internal state structure
 * @compliance MISRA C:2012 Rule 8.2 (complete type definitions)
 */
typedef struct {
    uint16_t left_position_raw[3];      /**< Left door position history (3 samples) */
    uint16_t right_position_raw[3];     /**< Right door position history */
    uint8_t position_sample_index;      /**< Circular buffer index (0-2) */
    uint32_t last_speed_msg_time_ms;    /**< Timestamp of last speed CAN message */
    uint16_t last_primary_speed;        /**< Last primary speed (km/h * 10) */
    uint16_t last_secondary_speed;      /**< Last secondary speed */
    bool initialized;                   /**< Initialization flag */
} sensor_hal_state_t;

/**
 * @brief CAN message structure
 * @compliance MISRA C:2012 Rule 8.2 (complete type definitions)
 */
typedef struct {
    uint32_t id;        /**< CAN message ID (11-bit) */
    uint8_t dlc;        /**< Data Length Code (0-8) */
    uint8_t data[8];    /**< CAN data bytes */
} can_message_t;

/*===========================================================================*/
/* Public Function Prototypes                                                */
/*===========================================================================*/

/**
 * @brief Initialize sensor hardware (ADC, GPIO, CAN filters)
 * @return ERROR_SUCCESS on success, ERROR_HARDWARE_FAILURE on init failure
 * @complexity 4 (1 base + 2 IF + 1 FOR)
 * @traceability DOC-COMPDES-2026-001 Section 3.7.2
 */
error_t sensor_hal_init(void);

/**
 * @brief Read door position sensor with median filter and plausibility check
 * @param[in] side Door side (DOOR_SIDE_LEFT or DOOR_SIDE_RIGHT)
 * @param[out] position_raw Pointer to store filtered position (0-4095)
 * @return ERROR_SUCCESS on success
 *         ERROR_NOT_INITIALIZED if not initialized
 *         ERROR_NULL_POINTER if position_raw is NULL
 *         ERROR_INVALID_PARAMETER if invalid side
 * @complexity 7 (1 base + 6 IF/AND)
 * @traceability DOC-COMPDES-2026-001 Section 3.7.3
 * @safety Applies median filter and plausibility check to reject spikes
 */
error_t sensor_hal_read_position(door_side_t side, uint16_t* position_raw);

/**
 * @brief Read obstacle sensor (active low GPIO)
 * @param[in] side Door side (DOOR_SIDE_LEFT or DOOR_SIDE_RIGHT)
 * @param[out] obstacle_detected Pointer to store detection state (true = obstacle)
 * @return ERROR_SUCCESS on success
 *         ERROR_NOT_INITIALIZED if not initialized
 *         ERROR_NULL_POINTER if obstacle_detected is NULL
 *         ERROR_INVALID_PARAMETER if invalid side
 * @complexity 5 (1 base + 4 IF/AND)
 * @traceability DOC-COMPDES-2026-001 Section 3.7.4
 */
error_t sensor_hal_read_obstacle(door_side_t side, bool* obstacle_detected);

/**
 * @brief Read speed sensors from CAN messages (redundant sensors)
 * @param[out] primary_speed Pointer to store primary speed (km/h * 10)
 * @param[out] secondary_speed Pointer to store secondary speed
 * @return ERROR_SUCCESS on success
 *         ERROR_NOT_INITIALIZED if not initialized
 *         ERROR_NULL_POINTER if any pointer is NULL
 *         ERROR_TIMEOUT if no speed message received recently
 * @complexity 7 (1 base + 6 IF/OR/AND)
 * @traceability DOC-COMPDES-2026-001 Section 3.7.5
 * @safety Timeout check ensures stale data is not used
 */
error_t sensor_hal_read_speed(uint16_t* primary_speed, uint16_t* secondary_speed);

/**
 * @brief Read emergency release handle (active low GPIO)
 * @param[in] side Door side (DOOR_SIDE_LEFT or DOOR_SIDE_RIGHT)
 * @param[out] activated Pointer to store activation state (true = pulled)
 * @return ERROR_SUCCESS on success
 *         ERROR_NOT_INITIALIZED if not initialized
 *         ERROR_NULL_POINTER if activated is NULL
 *         ERROR_INVALID_PARAMETER if invalid side
 * @complexity 5 (1 base + 4 IF/AND)
 * @traceability DOC-COMPDES-2026-001 Section 3.7.6
 */
error_t sensor_hal_read_emergency_handle(door_side_t side, bool* activated);

/**
 * @brief Calculate median of 3 values (noise rejection filter)
 * @param[in] a First value
 * @param[in] b Second value
 * @param[in] c Third value
 * @return Median of three input values
 * @complexity 6 (1 base + 5 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.7.7
 * @note Helper function for position sensor filtering
 */
uint16_t median_of_3(uint16_t a, uint16_t b, uint16_t c);

#endif /* SENSOR_HAL_H */
