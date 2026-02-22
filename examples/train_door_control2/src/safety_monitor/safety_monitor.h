/**
 * @file safety_monitor.h
 * @brief Safety Monitor Module (MOD-002)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.3, Table A.3
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.2 (MOD-002)
 * 
 * @description
 * Safety Monitor enforces speed-based door interlocks.
 * Monitors train speed, cross-checks redundant sensors,
 * enforces fail-safe logic for door operations.
 * Max complexity: 9 (within SIL 3 limit of 10).
 */

#ifndef SAFETY_MONITOR_H
#define SAFETY_MONITOR_H

#include "../common/types.h"
#include "../common/error_codes.h"

/*===========================================================================*/
/* Constants                                                                 */
/*===========================================================================*/

/** @brief Speed threshold for safe door opening (1.0 km/h, units: 0.1 km/h) */
#define SAFETY_SPEED_THRESHOLD_OPEN         (10U)

/** @brief Speed threshold for door locking (5.0 km/h, units: 0.1 km/h) */
#define SAFETY_SPEED_THRESHOLD_LOCK         (50U)

/** @brief Speed threshold for unlock (2.0 km/h, units: 0.1 km/h) */
#define SAFETY_SPEED_THRESHOLD_UNLOCK       (20U)

/** @brief Maximum sensor disagreement (10.0 km/h, units: 0.1 km/h) */
#define SAFETY_SPEED_DISAGREE_THRESHOLD     (100U)

/** @brief Maximum plausible speed (300.0 km/h, units: 0.1 km/h) */
#define SAFETY_SPEED_MAX_PLAUSIBLE          (3000U)

/** @brief Unlock hysteresis time (1 second) */
#define SAFETY_UNLOCK_HYSTERESIS_MS         (1000U)

/** @brief Sensor timeout (100ms max between updates) */
#define SAFETY_SENSOR_TIMEOUT_MS            (100U)

/*===========================================================================*/
/* Data Structures                                                           */
/*===========================================================================*/

/**
 * @brief Safety Monitor state structure
 * @compliance Static allocation ONLY (64 bytes fixed size)
 * @traceability DOC-COMPDES-2026-001 Section 3.2.8
 */
typedef struct {
    /* Speed sensor readings (raw values, units: 0.1 km/h) */
    uint16_t primary_speed;               /**< Primary speed sensor (2 bytes) */
    uint16_t secondary_speed;             /**< Secondary speed sensor (2 bytes) */
    uint16_t speed;                       /**< Validated speed (2 bytes) */
    
    /* Sensor health flags */
    bool primary_sensor_valid;            /**< Primary sensor healthy (1 byte) */
    bool secondary_sensor_valid;          /**< Secondary sensor healthy (1 byte) */
    
    /* Hysteresis timing for unlock condition */
    uint32_t unlock_condition_start_ms;   /**< Unlock timer start (4 bytes) */
    bool unlock_hysteresis_active;        /**< Unlock timer active (1 byte) */
    
    /* Computed safety interlocks */
    bool is_safe_to_open;                 /**< Safe to open doors (1 byte) */
    bool should_lock;                     /**< Should lock doors (1 byte) */
    bool should_unlock;                   /**< Should unlock doors (1 byte) */
    
    /* Timing */
    uint32_t last_update_time_ms;         /**< Last update time (4 bytes) */
    
    /* Total: 20 bytes used */
} safety_monitor_t;

/*===========================================================================*/
/* Public Function Prototypes                                                */
/*===========================================================================*/

/**
 * @brief Initialize safety monitor with fail-safe defaults
 * @param[in,out] monitor Pointer to safety monitor structure
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 2 (1 base + 1 IF)
 * @safety CRITICAL - Fail-safe initialization (doors locked until proven safe)
 */
error_t safety_monitor_init(safety_monitor_t* monitor);

/**
 * @brief Update safety monitor, validate speed sensors, compute interlocks
 * @param[in,out] monitor Pointer to safety monitor structure
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 9 (within SIL 3 limit of 10)
 * @safety CRITICAL - Enforces all speed-based door interlocks
 */
error_t safety_monitor_update(safety_monitor_t* monitor);

/**
 * @brief Check if safe to open doors (speed < 1 km/h)
 * @param[in] monitor Pointer to safety monitor structure
 * @return true if safe, false otherwise (NULL-safe, fail-safe)
 * @complexity 4
 * @safety CRITICAL - Prevents door opening when train moving
 */
bool safety_monitor_is_safe_to_open(const safety_monitor_t* monitor);

/**
 * @brief Check if doors should be locked (speed > 5 km/h)
 * @param[in] monitor Pointer to safety monitor structure
 * @return true if should lock, false otherwise (NULL-safe, fail-safe)
 * @complexity 3
 * @safety CRITICAL - Enforces door lock when train moving
 */
bool safety_monitor_should_lock(const safety_monitor_t* monitor);

/**
 * @brief Check if doors should be unlocked (speed < 2 km/h for ≥1s, hysteresis)
 * @param[in] monitor Pointer to safety monitor structure
 * @return true if should unlock, false otherwise (NULL-safe, fail-safe)
 * @complexity 4
 * @safety CRITICAL - Prevents premature unlock
 */
bool safety_monitor_should_unlock(const safety_monitor_t* monitor);

/**
 * @brief Get validated train speed (0.1 km/h resolution)
 * @param[in] monitor Pointer to safety monitor structure
 * @return Validated speed (NULL-safe, fail-safe returns 1000 = 100 km/h)
 * @complexity 2
 */
uint16_t safety_monitor_get_speed(const safety_monitor_t* monitor);

/**
 * @brief Get speed sensor health status (for diagnostics)
 * @param[in] monitor Pointer to safety monitor structure
 * @param[out] primary_valid Primary sensor health flag
 * @param[out] secondary_valid Secondary sensor health flag
 * @return ERROR_SUCCESS on success, error code otherwise
 * @complexity 2
 */
error_t safety_monitor_get_sensor_health(const safety_monitor_t* monitor, 
                                          bool* primary_valid, 
                                          bool* secondary_valid);

#endif /* SAFETY_MONITOR_H */
