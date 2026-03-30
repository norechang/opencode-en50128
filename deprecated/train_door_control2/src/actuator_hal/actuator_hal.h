/**
 * @file actuator_hal.h
 * @brief Hardware Abstraction Layer for Door Actuators (MOD-006)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.6 (MOD-006)
 * 
 * @description
 * Provides hardware abstraction for door motors (PWM) and lock solenoids (GPIO).
 * All functions use defensive programming with parameter validation and error checking.
 * Maximum cyclomatic complexity: 6 (SIL 3 target: ≤10).
 * 
 * @memory_footprint
 * - actuator_hal_state_t: 6 bytes
 * - Total: 6 bytes
 */

#ifndef ACTUATOR_HAL_H
#define ACTUATOR_HAL_H

#include "../common/types.h"
#include "../common/error_codes.h"

/*===========================================================================*/
/* Constants                                                                 */
/*===========================================================================*/

/** PWM duty cycle limits */
#define PWM_MIN_DUTY_CYCLE  (-100)    /**< Full reverse */
#define PWM_MAX_DUTY_CYCLE  (100)     /**< Full forward */
#define PWM_NEUTRAL         (0)       /**< Motor stopped */

/*===========================================================================*/
/* Data Structures                                                           */
/*===========================================================================*/

/**
 * @brief Actuator HAL internal state structure
 * @compliance MISRA C:2012 Rule 8.2 (complete type definitions)
 */
typedef struct {
    int8_t left_door_pwm;           /**< Left door PWM duty cycle (-100 to +100) */
    int8_t right_door_pwm;          /**< Right door PWM duty cycle */
    bool left_door_locked;          /**< Left door lock state (true = locked) */
    bool right_door_locked;         /**< Right door lock state */
    bool initialized;               /**< Initialization flag */
} actuator_hal_state_t;

/*===========================================================================*/
/* Public Function Prototypes                                                */
/*===========================================================================*/

/**
 * @brief Initialize actuator hardware (PWM timers, GPIO pins)
 * @return ERROR_SUCCESS on success, ERROR_HARDWARE_FAILURE on init failure
 * @complexity 3 (1 base + 2 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.6.2
 * @safety Sets all actuators to safe state (PWM=0, locks released)
 */
error_t actuator_hal_init(void);

/**
 * @brief Set door motor PWM duty cycle
 * @param[in] side Door side (DOOR_SIDE_LEFT or DOOR_SIDE_RIGHT)
 * @param[in] duty_cycle PWM duty cycle (-100 to +100, negative = reverse)
 * @return ERROR_SUCCESS on success
 *         ERROR_NOT_INITIALIZED if not initialized
 *         ERROR_OUT_OF_RANGE if duty_cycle out of range
 *         ERROR_INVALID_PARAMETER if invalid side
 * @complexity 6 (1 base + 5 IF/AND/OR)
 * @traceability DOC-COMPDES-2026-001 Section 3.6.3
 */
error_t actuator_hal_set_door_pwm(door_side_t side, int8_t duty_cycle);

/**
 * @brief Set door lock state
 * @param[in] side Door side (DOOR_SIDE_LEFT or DOOR_SIDE_RIGHT)
 * @param[in] locked Lock state (true = locked, false = unlocked)
 * @return ERROR_SUCCESS on success
 *         ERROR_NOT_INITIALIZED if not initialized
 *         ERROR_INVALID_PARAMETER if invalid side
 * @complexity 6 (1 base + 5 IF/AND)
 * @traceability DOC-COMPDES-2026-001 Section 3.6.4
 */
error_t actuator_hal_set_door_lock(door_side_t side, bool locked);

/**
 * @brief Emergency stop - immediately disable all actuators
 * @return ERROR_SUCCESS (always succeeds)
 * @complexity 1 (1 base, no branches - emergency function)
 * @traceability DOC-COMPDES-2026-001 Section 3.6.5
 * @safety Fail-safe function: stops all motors (PWM=0) and releases locks
 * @note No initialization check - must execute unconditionally in emergency
 */
error_t actuator_hal_emergency_stop(void);

#endif /* ACTUATOR_HAL_H */
