/**
 * @file door_control.h
 * @brief Door Control Module API - Train Door Control System
 * @standard EN 50128:2011 Section 7.4
 * @sil 3
 * @misra MISRA C:2012 compliant
 */

#ifndef DOOR_CONTROL_H
#define DOOR_CONTROL_H

#include <stdint.h>
#include <stdbool.h>
#include "error_types.h"

/**
 * @brief Maximum train speed in km/h
 */
#define MAX_TRAIN_SPEED_KMH  350U

/**
 * @brief Minimum speed threshold for door operations (must be 0)
 */
#define MIN_SAFE_SPEED_KMH   0U

/**
 * @brief Input data structure for door control processing
 *
 * Contains all sensor inputs required for door control decisions.
 * All inputs are validated before use.
 */
typedef struct {
    uint16_t speed_kmh;              /**< Current train speed (0-350 km/h) */
    bool door_closed_sensor_1;       /**< Door closed sensor 1 (true = closed) */
    bool door_closed_sensor_2;       /**< Door closed sensor 2 (true = closed) */
    bool door_locked_sensor_1;       /**< Door locked sensor 1 (true = locked) */
    bool door_locked_sensor_2;       /**< Door locked sensor 2 (true = locked) */
} door_control_input_t;

/**
 * @brief Output data structure for door control commands
 *
 * Contains all actuator commands and status indicators.
 */
typedef struct {
    bool door_open_command;          /**< Command to open door */
    bool door_close_command;         /**< Command to close door */
    bool door_lock_command;          /**< Command to lock door */
    bool safety_alarm;               /**< Safety alarm activation */
    bool emergency_release_active;   /**< Emergency release status */
} door_control_output_t;

/**
 * @brief Internal state structure for door control module
 *
 * Maintains state information between processing cycles.
 * Uses static allocation for SIL 3 compliance.
 */
typedef struct {
    uint16_t last_speed_kmh;         /**< Previous speed for rate checking */
    bool emergency_mode;             /**< Emergency release active flag */
    uint32_t last_update_time_ms;    /**< Timestamp of last processing */
} door_control_state_t;

/**
 * @brief Initialize the door control module
 *
 * Must be called once before any other door control functions.
 * Initializes state to safe defaults.
 *
 * @param[out] state Pointer to state structure (must not be NULL)
 * @return SUCCESS if initialization successful, error code otherwise
 * @pre state != NULL
 * @post State initialized to safe defaults
 */
error_t door_control_init(door_control_state_t* state);

/**
 * @brief Main door control processing function
 *
 * Processes sensor inputs and generates actuator commands.
 * Implements all safety interlocks and requirements.
 * Must be called periodically (recommended: every 50ms).
 *
 * @param[in]  input  Pointer to input structure (must not be NULL)
 * @param[out] output Pointer to output structure (must not be NULL)
 * @param[in,out] state Pointer to state structure (must not be NULL)
 * @return SUCCESS if processing successful, error code otherwise
 * @pre All pointers valid, input values in range
 * @post Output commands set according to safety requirements
 */
error_t door_control_process(const door_control_input_t* input,
                           door_control_output_t* output,
                           door_control_state_t* state);

/**
 * @brief Emergency door release function
 *
 * Activates emergency release mode, allowing door opening regardless
 * of speed. This overrides normal safety interlocks for emergency egress.
 * Logs the emergency activation.
 *
 * @param[out] output Pointer to output structure (must not be NULL)
 * @param[in,out] state Pointer to state structure (must not be NULL)
 * @return SUCCESS if emergency release activated, error code otherwise
 * @pre All pointers valid
 * @post Emergency mode activated, alarm triggered
 */
error_t door_control_emergency_release(door_control_output_t* output,
                                     door_control_state_t* state);

#endif /* DOOR_CONTROL_H */