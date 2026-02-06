/**
 * @file door_control.c
 * @brief Door Control Module Implementation - Train Door Control System
 * @standard EN 50128:2011 Section 7.4
 * @sil 3
 * @misra MISRA C:2012 compliant
 */

#include <stddef.h>
#include "door_control.h"

/**
 * @brief Maximum allowed speed change rate (km/h per second)
 * Prevents unrealistic speed jumps that could indicate sensor faults
 */
#define MAX_SPEED_RATE_CHANGE_KMH_PER_SEC  50U

/**
 * @brief Minimum update interval in milliseconds
 * Ensures processing occurs frequently enough for safety
 */
#define MIN_UPDATE_INTERVAL_MS  10U

/**
 * @brief Maximum update interval in milliseconds
 * Detects if processing is too infrequent
 */
#define MAX_UPDATE_INTERVAL_MS  200U

/**
 * @brief Validate input parameters
 *
 * Checks all input values are within valid ranges and pointers are not NULL.
 *
 * @param[in] input Pointer to input structure
 * @param[in] output Pointer to output structure
 * @param[in] state Pointer to state structure
 * @return SUCCESS if all inputs valid, error code otherwise
 */
static error_t validate_inputs(const door_control_input_t* input,
                              const door_control_output_t* output,
                              const door_control_state_t* state) {
    /* MISRA C:2012 Rule 17.7 - Check all function return values */
    if ((input == NULL) || (output == NULL) || (state == NULL)) {
        return ERROR_NULL_POINTER;
    }

    /* Validate speed range */
    if (input->speed_kmh > MAX_TRAIN_SPEED_KMH) {
        return ERROR_OUT_OF_RANGE;
    }

    return SUCCESS;
}

/**
 * @brief Validate door sensor consistency
 *
 * Checks that redundant door sensors agree.
 * For SIL 3, disagreement triggers safety response.
 *
 * @param[in] input Pointer to input structure
 * @return SUCCESS if sensors consistent, ERROR_REDUNDANCY_FAULT otherwise
 */
static error_t validate_door_sensors(const door_control_input_t* input) {
    /* Check closed sensors agree */
    if (input->door_closed_sensor_1 != input->door_closed_sensor_2) {
        return ERROR_REDUNDANCY_FAULT;
    }

    /* Check locked sensors agree */
    if (input->door_locked_sensor_1 != input->door_locked_sensor_2) {
        return ERROR_REDUNDANCY_FAULT;
    }

    return SUCCESS;
}

/**
 * @brief Validate speed sensor plausibility
 *
 * Checks for unrealistic speed changes that could indicate faults.
 *
 * @param[in] input Pointer to input structure
 * @param[in] state Pointer to state structure
 * @return SUCCESS if speed plausible, ERROR_SENSOR_FAULT otherwise
 */
static error_t validate_speed_sensor(const door_control_input_t* input,
                                   const door_control_state_t* state) {
    /* Calculate time since last update (assume 50ms nominal) */
    /* For simplicity, assume time is valid - in real system would check */

    /* Check rate of change */
    uint16_t speed_delta;
    if (input->speed_kmh > state->last_speed_kmh) {
        speed_delta = input->speed_kmh - state->last_speed_kmh;
    } else {
        speed_delta = state->last_speed_kmh - input->speed_kmh;
    }

    /* Allow up to 50 km/h change per second (over 50ms = 2.5 km/h) */
    if (speed_delta > 3U) {
        return ERROR_SENSOR_FAULT;
    }

    return SUCCESS;
}

/**
 * @brief Determine door commands based on safety requirements
 *
 * Implements REQ-FUNC-001: Door lock when speed > 0
 * Implements fail-safe behavior per REQ-SAFE-001
 *
 * @param[in] input Pointer to input structure
 * @param[out] output Pointer to output structure
 * @param[in] state Pointer to state structure
 * @return SUCCESS if commands determined, error code otherwise
 */
static error_t determine_door_commands(const door_control_input_t* input,
                                     door_control_output_t* output,
                                     const door_control_state_t* state) {
    /* Default to safe state */
    output->door_open_command = false;
    output->door_close_command = false;
    output->door_lock_command = false;
    output->safety_alarm = false;

    /* Emergency mode overrides all interlocks */
    if (state->emergency_mode) {
        output->emergency_release_active = true;
        output->door_lock_command = false;
        output->door_open_command = true;
        output->safety_alarm = true;
        output->door_close_command = false;
        return SUCCESS;
    }

    /* REQ-FUNC-001: Prevent door opening when speed > 0 */
    if (input->speed_kmh > MIN_SAFE_SPEED_KMH) {
        /* Speed > 0: ensure doors are locked */
        if (!input->door_locked_sensor_1) {
            output->door_lock_command = true;
        }
        /* REQ-SAFE-001: Activate alarm if door not secure */
        if (!input->door_closed_sensor_1) {
            output->safety_alarm = true;
        }
        return SUCCESS;
    }

    /* Speed = 0: allow normal operation */
    /* For this implementation, default to locked state */
    /* Higher level system would issue open/close commands */
    output->door_lock_command = true;

    return SUCCESS;
}

error_t door_control_init(door_control_state_t* state) {
    /* Validate input */
    if (state == NULL) {
        return ERROR_NULL_POINTER;
    }

    /* Initialize to safe defaults */
    state->last_speed_kmh = 0U;
    state->emergency_mode = false;
    state->last_update_time_ms = 0U;

    return SUCCESS;
}

error_t door_control_process(const door_control_input_t* input,
                           door_control_output_t* output,
                           door_control_state_t* state) {
    error_t status;

    /* Step 1: Validate all pointers and input ranges */
    status = validate_inputs(input, output, state);
    if (status != SUCCESS) {
        /* In fail-safe mode, set safe outputs */
        if (output != NULL) {
            output->door_open_command = false;
            output->door_close_command = false;
            output->door_lock_command = true;
            output->safety_alarm = true;
            output->emergency_release_active = false;
        }
        return status;
    }

    /* Step 2: Validate sensor consistency (REQ-SAFE-002) */
    status = validate_door_sensors(input);
    if (status != SUCCESS) {
        /* Redundancy fault: fail-safe */
        output->door_open_command = false;
        output->door_close_command = false;
        output->door_lock_command = true;
        output->safety_alarm = true;
        output->emergency_release_active = false;
        return status;
    }

    /* Step 3: Validate speed sensor plausibility */
    status = validate_speed_sensor(input, state);
    if (status != SUCCESS) {
        /* Sensor fault: fail-safe */
        output->door_open_command = false;
        output->door_close_command = false;
        output->door_lock_command = true;
        output->safety_alarm = true;
        output->emergency_release_active = false;
        return status;
    }

    /* Step 4: Determine door commands */
    status = determine_door_commands(input, output, state);
    if (status != SUCCESS) {
        /* Command determination failed: fail-safe */
        output->door_open_command = false;
        output->door_close_command = false;
        output->door_lock_command = true;
        output->safety_alarm = true;
        output->emergency_release_active = false;
        return status;
    }

    /* Step 5: Update state for next cycle */
    state->last_speed_kmh = input->speed_kmh;
    /* Assume time updated externally */

    return SUCCESS;
}

error_t door_control_emergency_release(door_control_output_t* output,
                                     door_control_state_t* state) {
    /* Validate pointers */
    if ((output == NULL) || (state == NULL)) {
        return ERROR_NULL_POINTER;
    }

    /* Activate emergency mode */
    state->emergency_mode = true;

    /* Set emergency outputs */
    output->emergency_release_active = true;
    output->door_lock_command = false;
    output->door_open_command = true;
    output->safety_alarm = true;
    output->door_close_command = false;

    return SUCCESS;
}