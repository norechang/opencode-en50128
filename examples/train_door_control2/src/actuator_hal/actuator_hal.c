/**
 * @file actuator_hal.c
 * @brief Hardware Abstraction Layer for Door Actuators Implementation (MOD-006)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.6 (MOD-006)
 * 
 * @description
 * Implements PWM motor control and GPIO lock control with full defensive programming.
 * All functions meet SIL 3 complexity requirement (≤10).
 * 
 * @defensive_programming
 * - All public functions validate parameters
 * - Initialization state checked before operation
 * - Return values from hardware functions checked
 * - Fail-safe defaults applied
 */

#include "actuator_hal.h"

/*===========================================================================*/
/* Hardware Driver Stubs (to be replaced with actual driver in integration) */
/*===========================================================================*/

/* PWM Timer IDs */
#define PWM_TIMER_LEFT   (0U)
#define PWM_TIMER_RIGHT  (1U)

/* GPIO Pin IDs */
#define GPIO_LOCK_LEFT   (10U)
#define GPIO_LOCK_RIGHT  (11U)

/* PWM Frequency */
#define PWM_FREQ_1KHZ    (1000U)

/* Hardware function stubs (platform-specific, to be linked) */
extern error_t pwm_timer_init(uint8_t timer_id, uint16_t freq_hz);
extern void pwm_set_duty_cycle(uint8_t timer_id, int8_t duty_cycle);
extern void gpio_init_output(uint8_t pin);
extern void gpio_set_high(uint8_t pin);
extern void gpio_set_low(uint8_t pin);

/*===========================================================================*/
/* Module State                                                              */
/*===========================================================================*/

/**
 * @brief Module state (static allocation)
 * @compliance EN 50128 SIL 3: Static memory allocation only
 */
static actuator_hal_state_t g_actuator_hal;

/*===========================================================================*/
/* Public Function Implementations                                           */
/*===========================================================================*/

/**
 * @brief Initialize actuator hardware (PWM timers, GPIO pins)
 * @complexity 3 (1 base + 2 IF decisions)
 * @traceability DOC-COMPDES-2026-001 Section 3.6.2 (pseudocode lines 2249-2281)
 */
error_t actuator_hal_init(void)
{
    error_t err;
    
    /* Step 1: Initialize PWM timers for door motors */
    err = pwm_timer_init(PWM_TIMER_LEFT, PWM_FREQ_1KHZ);
    if (err != ERROR_SUCCESS) {                                 /* +1 */
        return ERROR_HARDWARE_FAILURE;
    }
    
    err = pwm_timer_init(PWM_TIMER_RIGHT, PWM_FREQ_1KHZ);
    if (err != ERROR_SUCCESS) {                                 /* +1 */
        return ERROR_HARDWARE_FAILURE;
    }
    
    /* Step 2: Set initial PWM duty cycle to 0 (motors stopped) */
    pwm_set_duty_cycle(PWM_TIMER_LEFT, 0);
    pwm_set_duty_cycle(PWM_TIMER_RIGHT, 0);
    
    /* Step 3: Initialize lock GPIO pins (active high = locked) */
    gpio_init_output(GPIO_LOCK_LEFT);
    gpio_init_output(GPIO_LOCK_RIGHT);
    
    /* Step 4: Release locks initially (fail-safe: unlocked on init) */
    gpio_set_low(GPIO_LOCK_LEFT);
    gpio_set_low(GPIO_LOCK_RIGHT);
    
    /* Step 5: Update internal state */
    g_actuator_hal.left_door_pwm = 0;
    g_actuator_hal.right_door_pwm = 0;
    g_actuator_hal.left_door_locked = false;
    g_actuator_hal.right_door_locked = false;
    g_actuator_hal.initialized = true;
    
    return ERROR_SUCCESS;
}

/**
 * @brief Set door motor PWM duty cycle
 * @complexity 6 (1 base + 5 IF/AND/OR decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.6.3 (pseudocode lines 2300-2326)
 */
error_t actuator_hal_set_door_pwm(door_side_t side, int8_t duty_cycle)
{
    /* Step 1: Defensive programming - Check initialization */
    if (g_actuator_hal.initialized == false) {                  /* +1 */
        return ERROR_NOT_INITIALIZED;
    }
    
    /* Step 2: Defensive programming - Range check duty cycle */
    if ((duty_cycle < PWM_MIN_DUTY_CYCLE) ||                    /* +1 */
        (duty_cycle > PWM_MAX_DUTY_CYCLE)) {                    /* +1 */
        return ERROR_OUT_OF_RANGE;
    }
    
    /* Step 3: Defensive programming - Validate side parameter */
    if ((side != DOOR_SIDE_LEFT) && (side != DOOR_SIDE_RIGHT)) { /* +1 +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 4: Set PWM based on side */
    if (side == DOOR_SIDE_LEFT) {
        pwm_set_duty_cycle(PWM_TIMER_LEFT, duty_cycle);
        g_actuator_hal.left_door_pwm = duty_cycle;
    } else {
        pwm_set_duty_cycle(PWM_TIMER_RIGHT, duty_cycle);
        g_actuator_hal.right_door_pwm = duty_cycle;
    }
    
    return ERROR_SUCCESS;
}

/**
 * @brief Set door lock state
 * @complexity 6 (1 base + 5 IF/AND decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.6.4 (pseudocode lines 2345-2374)
 */
error_t actuator_hal_set_door_lock(door_side_t side, bool locked)
{
    /* Step 1: Defensive programming - Check initialization */
    if (g_actuator_hal.initialized == false) {                  /* +1 */
        return ERROR_NOT_INITIALIZED;
    }
    
    /* Step 2: Defensive programming - Validate side parameter */
    if ((side != DOOR_SIDE_LEFT) && (side != DOOR_SIDE_RIGHT)) { /* +1 +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 3: Set lock GPIO based on side */
    if (side == DOOR_SIDE_LEFT) {                               /* +1 */
        if (locked == true) {                                   /* +1 */
            gpio_set_high(GPIO_LOCK_LEFT);      /* Energize lock solenoid */
        } else {
            gpio_set_low(GPIO_LOCK_LEFT);       /* De-energize lock */
        }
        g_actuator_hal.left_door_locked = locked;
    } else {
        if (locked == true) {
            gpio_set_high(GPIO_LOCK_RIGHT);
        } else {
            gpio_set_low(GPIO_LOCK_RIGHT);
        }
        g_actuator_hal.right_door_locked = locked;
    }
    
    return ERROR_SUCCESS;
}

/**
 * @brief Emergency stop - immediately disable all actuators
 * @complexity 1 (1 base, no branches - emergency function)
 * @traceability DOC-COMPDES-2026-001 Section 3.6.5 (pseudocode lines 2393-2409)
 * 
 * @safety Emergency function - no initialization check required
 *         Must execute unconditionally to ensure safety
 */
error_t actuator_hal_emergency_stop(void)
{
    /* Step 1: Stop all motors immediately (no initialization check - emergency) */
    pwm_set_duty_cycle(PWM_TIMER_LEFT, 0);
    pwm_set_duty_cycle(PWM_TIMER_RIGHT, 0);
    
    /* Step 2: Release all locks (fail-safe: unlock in emergency) */
    gpio_set_low(GPIO_LOCK_LEFT);
    gpio_set_low(GPIO_LOCK_RIGHT);
    
    /* Step 3: Update internal state */
    g_actuator_hal.left_door_pwm = 0;
    g_actuator_hal.right_door_pwm = 0;
    g_actuator_hal.left_door_locked = false;
    g_actuator_hal.right_door_locked = false;
    
    return ERROR_SUCCESS;
}
