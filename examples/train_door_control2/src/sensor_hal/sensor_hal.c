/**
 * @file sensor_hal.c
 * @brief Hardware Abstraction Layer for Sensors Implementation (MOD-007)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4, Table A.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3.7 (MOD-007)
 * 
 * @description
 * Implements sensor reading with median filtering, plausibility checks, and timeout detection.
 * All functions meet SIL 3 complexity requirement (≤10).
 * 
 * @defensive_programming
 * - All public functions validate parameters
 * - Initialization state checked before operation
 * - Median filter rejects sensor spikes
 * - Timeout detection for CAN speed messages
 * - NULL pointer checks on all output parameters
 */

#include "sensor_hal.h"
#include <stdlib.h>  /* For abs() */

/*===========================================================================*/
/* Hardware Driver Stubs (to be replaced with actual driver in integration) */
/*===========================================================================*/

/* ADC Channel IDs */
#define ADC_CHANNEL_LEFT_POSITION   (0U)
#define ADC_CHANNEL_RIGHT_POSITION  (1U)

/* GPIO Pin IDs */
#define GPIO_OBSTACLE_LEFT          (20U)
#define GPIO_OBSTACLE_RIGHT         (21U)
#define GPIO_EMERG_HANDLE_LEFT      (22U)
#define GPIO_EMERG_HANDLE_RIGHT     (23U)

/* ADC Configuration */
#define ADC_12BIT                   (0U)
#define ADC_VREF_3V3                (3300U)

/* Hardware function stubs (platform-specific, to be linked) */
extern error_t adc_init(uint8_t resolution, uint16_t vref_mv);
extern uint16_t adc_read(uint8_t channel);
extern void gpio_init_input_pullup(uint8_t pin);
extern bool gpio_read(uint8_t pin);
extern error_t can_filter_add(uint32_t can_id);

/* Forward declaration for communication HAL functions */
extern bool communication_hal_can_is_rx_ready(void);
extern error_t communication_hal_can_receive(can_message_t* msg);

/*===========================================================================*/
/* Module State                                                              */
/*===========================================================================*/

/**
 * @brief Module state (static allocation)
 * @compliance EN 50128 SIL 3: Static memory allocation only
 */
static sensor_hal_state_t g_sensor_hal;

/*===========================================================================*/
/* Private Helper Functions                                                  */
/*===========================================================================*/

/**
 * @brief Calculate absolute difference between two unsigned values
 * @param[in] a First value
 * @param[in] b Second value
 * @return Absolute difference |a - b|
 * @note Helper to avoid signed/unsigned conversion issues
 */
static uint16_t absolute_difference(uint16_t a, uint16_t b)
{
    if (a > b) {
        return (a - b);
    } else {
        return (b - a);
    }
}

/*===========================================================================*/
/* Public Function Implementations                                           */
/*===========================================================================*/

/**
 * @brief Initialize sensor hardware (ADC, GPIO, CAN filters)
 * @complexity 4 (1 base + 2 IF + 1 FOR)
 * @traceability DOC-COMPDES-2026-001 Section 3.7.2 (pseudocode lines 2478-2511)
 */
error_t sensor_hal_init(void)
{
    error_t err;
    uint8_t i;
    
    /* Step 1: Initialize ADC for position sensors */
    err = adc_init(ADC_12BIT, ADC_VREF_3V3);
    if (err != ERROR_SUCCESS) {                                 /* +1 */
        return ERROR_HARDWARE_FAILURE;
    }
    
    /* Step 2: Initialize GPIO for obstacle sensors (active low) */
    gpio_init_input_pullup(GPIO_OBSTACLE_LEFT);
    gpio_init_input_pullup(GPIO_OBSTACLE_RIGHT);
    
    /* Step 3: Initialize GPIO for emergency handles (active low) */
    gpio_init_input_pullup(GPIO_EMERG_HANDLE_LEFT);
    gpio_init_input_pullup(GPIO_EMERG_HANDLE_RIGHT);
    
    /* Step 4: Initialize CAN filter for speed messages (ID 0x100) */
    err = can_filter_add(CAN_ID_SPEED_DATA);
    if (err != ERROR_SUCCESS) {                                 /* +1 */
        return ERROR_HARDWARE_FAILURE;
    }
    
    /* Step 5: Initialize internal state */
    for (i = 0U; i < 3U; i++) {                                 /* +1 */
        g_sensor_hal.left_position_raw[i] = 0U;
        g_sensor_hal.right_position_raw[i] = 0U;
    }
    g_sensor_hal.position_sample_index = 0U;
    g_sensor_hal.last_speed_msg_time_ms = 0U;
    g_sensor_hal.last_primary_speed = 0U;
    g_sensor_hal.last_secondary_speed = 0U;
    g_sensor_hal.initialized = true;
    
    return ERROR_SUCCESS;
}

/**
 * @brief Read door position sensor with median filter and plausibility check
 * @complexity 7 (1 base + 6 IF/AND decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.7.3 (pseudocode lines 2530-2581)
 */
error_t sensor_hal_read_position(door_side_t side, uint16_t* position_raw)
{
    uint16_t adc_value;
    uint16_t* history;
    uint16_t last_value;
    uint16_t delta;
    uint8_t next_index;
    uint16_t filtered_value;
    
    /* Step 1: Defensive programming - Check initialization */
    if (g_sensor_hal.initialized == false) {                    /* +1 */
        return ERROR_NOT_INITIALIZED;
    }
    
    /* Step 2: Defensive programming - NULL check */
    if (position_raw == NULL) {                                 /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 3: Defensive programming - Validate side parameter */
    if ((side != DOOR_SIDE_LEFT) && (side != DOOR_SIDE_RIGHT)) { /* +1 +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 4: Read raw ADC value */
    if (side == DOOR_SIDE_LEFT) {                               /* +1 */
        adc_value = adc_read(ADC_CHANNEL_LEFT_POSITION);
    } else {
        adc_value = adc_read(ADC_CHANNEL_RIGHT_POSITION);
    }
    
    /* Step 5: Plausibility check - position cannot change > 20% in single sample */
    if (side == DOOR_SIDE_LEFT) {
        history = g_sensor_hal.left_position_raw;
    } else {
        history = g_sensor_hal.right_position_raw;
    }
    
    last_value = history[g_sensor_hal.position_sample_index];
    delta = absolute_difference(adc_value, last_value);
    if (delta > POSITION_MAX_DELTA) {                           /* +1 */
        /* Reject spike, use last valid value */
        adc_value = last_value;
    }
    
    /* Step 6: Store in circular buffer */
    next_index = (uint8_t)((g_sensor_hal.position_sample_index + 1U) % MEDIAN_FILTER_SIZE);
    history[next_index] = adc_value;
    g_sensor_hal.position_sample_index = next_index;
    
    /* Step 7: Apply 3-sample median filter */
    filtered_value = median_of_3(history[0], history[1], history[2]);
    
    /* Step 8: Return filtered value */
    *position_raw = filtered_value;
    
    return ERROR_SUCCESS;
}

/**
 * @brief Read obstacle sensor (active low GPIO)
 * @complexity 5 (1 base + 4 IF/AND decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.7.4 (pseudocode lines 2600-2628)
 */
error_t sensor_hal_read_obstacle(door_side_t side, bool* obstacle_detected)
{
    bool gpio_state;
    
    /* Step 1: Defensive programming - Check initialization */
    if (g_sensor_hal.initialized == false) {                    /* +1 */
        return ERROR_NOT_INITIALIZED;
    }
    
    /* Step 2: Defensive programming - NULL check */
    if (obstacle_detected == NULL) {                            /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 3: Defensive programming - Validate side parameter */
    if ((side != DOOR_SIDE_LEFT) && (side != DOOR_SIDE_RIGHT)) { /* +1 +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 4: Read GPIO (active low = obstacle detected) */
    if (side == DOOR_SIDE_LEFT) {
        gpio_state = gpio_read(GPIO_OBSTACLE_LEFT);
    } else {
        gpio_state = gpio_read(GPIO_OBSTACLE_RIGHT);
    }
    
    /* Step 5: Active low - LOW = obstacle present */
    *obstacle_detected = (gpio_state == false);
    
    return ERROR_SUCCESS;
}

/**
 * @brief Read speed sensors from CAN messages (redundant sensors)
 * @complexity 7 (1 base + 6 IF/OR/AND decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.7.5 (pseudocode lines 2647-2683)
 */
error_t sensor_hal_read_speed(uint16_t* primary_speed, uint16_t* secondary_speed)
{
    uint32_t current_time;
    uint32_t elapsed;
    can_message_t can_msg;
    error_t err;
    
    /* Step 1: Defensive programming - Check initialization */
    if (g_sensor_hal.initialized == false) {                    /* +1 */
        return ERROR_NOT_INITIALIZED;
    }
    
    /* Step 2: Defensive programming - NULL checks */
    if ((primary_speed == NULL) || (secondary_speed == NULL)) { /* +1 +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 3: Check if speed message received recently (timeout check) */
    current_time = get_system_time_ms();
    elapsed = current_time - g_sensor_hal.last_speed_msg_time_ms;
    if (elapsed > SPEED_MSG_TIMEOUT_MS) {                       /* +1 */
        /* Speed message timeout - return error */
        return ERROR_TIMEOUT;
    }
    
    /* Step 4: Check if new CAN message available */
    if (communication_hal_can_is_rx_ready() == true) {          /* +1 */
        err = communication_hal_can_receive(&can_msg);
        if ((err == ERROR_SUCCESS) &&                           /* +1 */
            (can_msg.id == CAN_ID_SPEED_DATA) &&
            (can_msg.dlc == 8U)) {
            /* Parse speed data (bytes 0-1: primary, bytes 2-3: secondary) */
            g_sensor_hal.last_primary_speed = 
                ((uint16_t)can_msg.data[0] << 8) | (uint16_t)can_msg.data[1];
            g_sensor_hal.last_secondary_speed = 
                ((uint16_t)can_msg.data[2] << 8) | (uint16_t)can_msg.data[3];
            g_sensor_hal.last_speed_msg_time_ms = current_time;
        }
    }
    
    /* Step 5: Return last valid speed values */
    *primary_speed = g_sensor_hal.last_primary_speed;
    *secondary_speed = g_sensor_hal.last_secondary_speed;
    
    return ERROR_SUCCESS;
}

/**
 * @brief Read emergency release handle (active low GPIO)
 * @complexity 5 (1 base + 4 IF/AND decision points)
 * @traceability DOC-COMPDES-2026-001 Section 3.7.6 (pseudocode lines 2702-2730)
 */
error_t sensor_hal_read_emergency_handle(door_side_t side, bool* activated)
{
    bool gpio_state;
    
    /* Step 1: Defensive programming - Check initialization */
    if (g_sensor_hal.initialized == false) {                    /* +1 */
        return ERROR_NOT_INITIALIZED;
    }
    
    /* Step 2: Defensive programming - NULL check */
    if (activated == NULL) {                                    /* +1 */
        return ERROR_NULL_POINTER;
    }
    
    /* Step 3: Defensive programming - Validate side parameter */
    if ((side != DOOR_SIDE_LEFT) && (side != DOOR_SIDE_RIGHT)) { /* +1 +1 */
        return ERROR_INVALID_PARAMETER;
    }
    
    /* Step 4: Read GPIO (active low = handle pulled) */
    if (side == DOOR_SIDE_LEFT) {
        gpio_state = gpio_read(GPIO_EMERG_HANDLE_LEFT);
    } else {
        gpio_state = gpio_read(GPIO_EMERG_HANDLE_RIGHT);
    }
    
    /* Step 5: Active low - LOW = handle activated */
    *activated = (gpio_state == false);
    
    return ERROR_SUCCESS;
}

/**
 * @brief Calculate median of 3 values (noise rejection filter)
 * @complexity 6 (1 base + 5 IF)
 * @traceability DOC-COMPDES-2026-001 Section 3.7.7 (pseudocode lines 2749-2768)
 */
uint16_t median_of_3(uint16_t a, uint16_t b, uint16_t c)
{
    /* Sort 3 values and return middle value */
    if (a > b) {                                                /* +1 */
        if (b > c) {                                            /* +1 */
            return b;                /* a > b > c */
        } else if (a > c) {                                     /* +1 */
            return c;                /* a > c > b */
        } else {
            return a;                /* c > a > b */
        }
    } else {
        if (a > c) {                                            /* +1 */
            return a;                /* b > a > c */
        } else if (b > c) {                                     /* +1 */
            return c;                /* b > c > a */
        } else {
            return b;                /* c > b > a */
        }
    }
}
