/**
 * @file integration_mocks.c
 * @brief Integration test mocks implementation
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.6
 * @test_phase Phase 6 Activity 0b (Integration Test Execution)
 * @traceability DOC-INTTEST-2026-001 v1.0
 */

#include "integration_mocks.h"
#include <stdio.h>
#include <string.h>

/*===========================================================================*/
/* Mock State Variables                                                      */
/*===========================================================================*/

/* PWM Outputs */
int8_t mock_left_door_pwm = 0;
int8_t mock_right_door_pwm = 0;

/* GPIO Outputs */
bool mock_left_door_locked = true;   /* Fail-safe: locked by default */
bool mock_right_door_locked = true;

/* ADC Inputs */
uint16_t mock_left_position_raw = 0;   /* 0 = fully closed */
uint16_t mock_right_position_raw = 0;

/* GPIO Inputs */
bool mock_left_obstacle_detected = false;
bool mock_right_obstacle_detected = false;
bool mock_left_emergency_active = false;
bool mock_right_emergency_active = false;

/* CAN Bus */
mock_can_message_t mock_can_rx_queue[MOCK_CAN_RX_QUEUE_SIZE];
uint8_t mock_can_rx_head = 0;
uint8_t mock_can_rx_tail = 0;
uint8_t mock_can_rx_count = 0;

mock_can_message_t mock_can_tx_queue[MOCK_CAN_TX_QUEUE_SIZE];
uint8_t mock_can_tx_head = 0;
uint8_t mock_can_tx_tail = 0;
uint8_t mock_can_tx_count = 0;

/* Speed Data */
uint16_t mock_primary_speed = 0;      /* 0 km/h (train stopped) */
uint16_t mock_secondary_speed = 0;
uint32_t mock_last_speed_update_ms = 0;

/* System Time */
uint32_t mock_system_time_ms = 0;

/* Error Injection */
error_t mock_pwm_init_error = ERROR_SUCCESS;
error_t mock_adc_init_error = ERROR_SUCCESS;
error_t mock_can_init_error = ERROR_SUCCESS;
error_t mock_can_transmit_error = ERROR_SUCCESS;
error_t mock_can_receive_error = ERROR_SUCCESS;

/* DEFECT-INT-009 & DEFECT-INT-016 FIX: Sensor-specific fault injection */
bool mock_sensor_fault_left_position = false;
bool mock_sensor_fault_right_position = false;
bool mock_sensor_fault_left_obstacle = false;
bool mock_sensor_fault_right_obstacle = false;

/*===========================================================================*/
/* Mock Control Functions                                                    */
/*===========================================================================*/

void mock_reset_all(void) {
    /* Reset PWM outputs */
    mock_left_door_pwm = 0;
    mock_right_door_pwm = 0;
    
    /* Reset GPIO outputs (fail-safe: locked) */
    mock_left_door_locked = true;
    mock_right_door_locked = true;
    
    /* Reset ADC inputs (doors closed) */
    mock_left_position_raw = 0;
    mock_right_position_raw = 0;
    
    /* Reset GPIO inputs (no obstacles, no emergency) */
    mock_left_obstacle_detected = false;
    mock_right_obstacle_detected = false;
    mock_left_emergency_active = false;
    mock_right_emergency_active = false;
    
    /* Reset CAN queues */
    memset(mock_can_rx_queue, 0, sizeof(mock_can_rx_queue));
    mock_can_rx_head = 0;
    mock_can_rx_tail = 0;
    mock_can_rx_count = 0;
    
    memset(mock_can_tx_queue, 0, sizeof(mock_can_tx_queue));
    mock_can_tx_head = 0;
    mock_can_tx_tail = 0;
    mock_can_tx_count = 0;
    
    /* Reset speed (train stopped) */
    mock_primary_speed = 0;
    mock_secondary_speed = 0;
    mock_last_speed_update_ms = 0;
    
    /* Reset system time */
    mock_system_time_ms = 0;
    
    /* Clear error injection */
    mock_pwm_init_error = ERROR_SUCCESS;
    mock_adc_init_error = ERROR_SUCCESS;
    mock_can_init_error = ERROR_SUCCESS;
    mock_can_transmit_error = ERROR_SUCCESS;
    mock_can_receive_error = ERROR_SUCCESS;
    
    /* DEFECT-INT-016 FIX: Clear sensor fault injection flags */
    mock_sensor_fault_left_position = false;
    mock_sensor_fault_right_position = false;
    mock_sensor_fault_left_obstacle = false;
    mock_sensor_fault_right_obstacle = false;
}

void mock_advance_time(uint32_t delta_ms) {
    mock_system_time_ms += delta_ms;
    /* DEFECT-INT-005 FIX: Link door motion physics to ADC simulation */
    /* Simulate door motion based on PWM commands to update ADC readings */
    mock_simulate_door_motion(delta_ms);
}

error_t mock_can_inject_message(uint32_t id, const uint8_t* data, uint8_t dlc) {
    if (mock_can_rx_count >= MOCK_CAN_RX_QUEUE_SIZE) {
        return ERROR_BUFFER_FULL;
    }
    
    mock_can_rx_queue[mock_can_rx_head].id = id;
    mock_can_rx_queue[mock_can_rx_head].dlc = dlc;
    if (data != NULL && dlc > 0U) {
        memcpy(mock_can_rx_queue[mock_can_rx_head].data, data, dlc);
    }
    mock_can_rx_queue[mock_can_rx_head].timestamp_ms = mock_system_time_ms;
    mock_can_rx_queue[mock_can_rx_head].valid = true;
    
    mock_can_rx_head = (mock_can_rx_head + 1U) % MOCK_CAN_RX_QUEUE_SIZE;
    mock_can_rx_count++;
    
    return ERROR_SUCCESS;
}

error_t mock_can_get_last_tx(mock_can_message_t* msg) {
    if (msg == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (mock_can_tx_count == 0U) {
        return ERROR_NO_DATA;
    }
    
    /* DEFECT-INT-004 FIX: Get most recent transmitted message (head - 1, not tail - 1) */
    uint8_t last_idx = (mock_can_tx_head == 0U) ? 
                       (uint8_t)(MOCK_CAN_TX_QUEUE_SIZE - 1U) : 
                       (uint8_t)(mock_can_tx_head - 1U);
    
    memcpy(msg, &mock_can_tx_queue[last_idx], sizeof(mock_can_message_t));
    
    return ERROR_SUCCESS;
}

void mock_set_door_positions(uint8_t left_pct, uint8_t right_pct) {
    /* Convert percentage to 12-bit ADC value (0-4095) */
    mock_left_position_raw = (uint16_t)((left_pct * 4095U) / 100U);
    mock_right_position_raw = (uint16_t)((right_pct * 4095U) / 100U);
}

void mock_set_train_speed(uint16_t speed_kmh) {
    /* Convert km/h to 0.1 km/h units */
    mock_primary_speed = speed_kmh * 10U;
    mock_secondary_speed = speed_kmh * 10U;  /* Same for simulation */
    mock_last_speed_update_ms = mock_system_time_ms;
    
    /* DEFECT-INT-003 FIX: Ensure CAN TX queue processes speed messages correctly */
    /* Inject CAN speed message so sensor_hal_read_speed() can retrieve it */
    uint8_t speed_data[8];
    /* Bytes 0-1: Primary speed (big-endian) */
    speed_data[0] = (uint8_t)(mock_primary_speed >> 8);
    speed_data[1] = (uint8_t)(mock_primary_speed & 0xFFU);
    /* Bytes 2-3: Secondary speed (big-endian) */
    speed_data[2] = (uint8_t)(mock_secondary_speed >> 8);
    speed_data[3] = (uint8_t)(mock_secondary_speed & 0xFFU);
    /* Bytes 4-7: Reserved/unused */
    speed_data[4] = 0;
    speed_data[5] = 0;
    speed_data[6] = 0;
    speed_data[7] = 0;
    
    /* DEFECT-INT-004 & DEFECT-INT-011 FIX: Align mock CAN IDs with production */
    /* Inject into CAN RX queue with correct ID (CAN_ID_SPEED_DATA = 0x100) */
    (void)mock_can_inject_message(0x100U, speed_data, 8);
}

void mock_set_obstacle(door_side_t side, bool detected) {
    if (side == DOOR_SIDE_LEFT) {
        mock_left_obstacle_detected = detected;
    } else if (side == DOOR_SIDE_RIGHT) {
        mock_right_obstacle_detected = detected;
    }
}

void mock_set_emergency_handle(door_side_t side, bool activated) {
    if (side == DOOR_SIDE_LEFT) {
        mock_left_emergency_active = activated;
    } else if (side == DOOR_SIDE_RIGHT) {
        mock_right_emergency_active = activated;
    }
}

void mock_simulate_door_motion(uint32_t delta_ms) {
    /* DEFECT-INT-002 & DEFECT-INT-005 FIX: Update ADC to reflect motor position state */
    /* Simple linear motion model based on PWM */
    /* Opening: 0->100% in 5 seconds = 20%/second = 0.02%/ms */
    /* Closing: 100->0% in 7 seconds = 14.3%/second = 0.0143%/ms */
    
    /* Left door */
    if (mock_left_door_pwm > 0) {
        /* Opening - positive PWM increases position */
        int32_t delta_raw = (int32_t)(((int32_t)mock_left_door_pwm * (int32_t)delta_ms * 4095) / (100 * 5000));
        int32_t new_position = (int32_t)mock_left_position_raw + delta_raw;
        if (new_position > 4095) {
            mock_left_position_raw = 4095U;
        } else {
            mock_left_position_raw = (uint16_t)new_position;
        }
    } else if (mock_left_door_pwm < 0) {
        /* Closing - negative PWM decreases position */
        int32_t delta_raw = (int32_t)((-(int32_t)mock_left_door_pwm * (int32_t)delta_ms * 4095) / (100 * 7000));
        if ((uint16_t)delta_raw > mock_left_position_raw) {
            mock_left_position_raw = 0U;
        } else {
            mock_left_position_raw -= (uint16_t)delta_raw;
        }
    }
    /* else: PWM = 0, door stationary, position unchanged */
    
    /* Right door */
    if (mock_right_door_pwm > 0) {
        /* Opening - positive PWM increases position */
        int32_t delta_raw = (int32_t)(((int32_t)mock_right_door_pwm * (int32_t)delta_ms * 4095) / (100 * 5000));
        int32_t new_position = (int32_t)mock_right_position_raw + delta_raw;
        if (new_position > 4095) {
            mock_right_position_raw = 4095U;
        } else {
            mock_right_position_raw = (uint16_t)new_position;
        }
    } else if (mock_right_door_pwm < 0) {
        /* Closing - negative PWM decreases position */
        int32_t delta_raw = (int32_t)((-(int32_t)mock_right_door_pwm * (int32_t)delta_ms * 4095) / (100 * 7000));
        if ((uint16_t)delta_raw > mock_right_position_raw) {
            mock_right_position_raw = 0U;
        } else {
            mock_right_position_raw -= (uint16_t)delta_raw;
        }
    }
    /* else: PWM = 0, door stationary, position unchanged */
}

void mock_inject_error(error_t error_type) {
    /* For simplicity, inject error into all hardware functions */
    mock_pwm_init_error = error_type;
    mock_adc_init_error = error_type;
    mock_can_init_error = error_type;
    mock_can_transmit_error = error_type;
    mock_can_receive_error = error_type;
}

void mock_clear_errors(void) {
    mock_pwm_init_error = ERROR_SUCCESS;
    mock_adc_init_error = ERROR_SUCCESS;
    mock_can_init_error = ERROR_SUCCESS;
    mock_can_transmit_error = ERROR_SUCCESS;
    mock_can_receive_error = ERROR_SUCCESS;
    
    /* DEFECT-INT-016 FIX: Clear sensor fault flags */
    mock_sensor_fault_left_position = false;
    mock_sensor_fault_right_position = false;
    mock_sensor_fault_left_obstacle = false;
    mock_sensor_fault_right_obstacle = false;
}

/**
 * @brief Inject sensor fault (DEFECT-INT-009 & DEFECT-INT-016 FIX)
 * @param[in] side Door side
 * @param[in] sensor_type 0=position, 1=obstacle
 * @param[in] fault_active true = inject fault, false = clear fault
 */
void mock_inject_sensor_fault(door_side_t side, uint8_t sensor_type, bool fault_active) {
    if (sensor_type == 0U) {
        /* Position sensor fault */
        if (side == DOOR_SIDE_LEFT) {
            mock_sensor_fault_left_position = fault_active;
        } else if (side == DOOR_SIDE_RIGHT) {
            mock_sensor_fault_right_position = fault_active;
        }
    } else if (sensor_type == 1U) {
        /* Obstacle sensor fault */
        if (side == DOOR_SIDE_LEFT) {
            mock_sensor_fault_left_obstacle = fault_active;
        } else if (side == DOOR_SIDE_RIGHT) {
            mock_sensor_fault_right_obstacle = fault_active;
        }
    }
}

/*===========================================================================*/
/* Hardware Driver Stub Implementations                                      */
/*===========================================================================*/

/* PWM Timer Driver */
error_t pwm_timer_init(uint8_t timer_id, uint16_t freq_hz) {
    (void)timer_id;
    (void)freq_hz;
    return mock_pwm_init_error;
}

void pwm_set_duty_cycle(uint8_t timer_id, int8_t duty_cycle) {
    /* Timer 0 = left door, Timer 1 = right door */
    if (timer_id == 0U) {
        mock_left_door_pwm = duty_cycle;
    } else if (timer_id == 1U) {
        mock_right_door_pwm = duty_cycle;
    }
}

/* GPIO Driver */
void gpio_init_output(uint8_t pin) {
    (void)pin;
}

void gpio_set_high(uint8_t pin) {
    /* DEFECT-INT-001 FIX: Correct GPIO pin mapping to match production HAL */
    /* Pin 10 = left lock, Pin 11 = right lock (GPIO_LOCK_LEFT/RIGHT from actuator_hal.c) */
    if (pin == 10U) {
        mock_left_door_locked = true;
    } else if (pin == 11U) {
        mock_right_door_locked = true;
    }
}

void gpio_set_low(uint8_t pin) {
    /* DEFECT-INT-001 FIX: Correct GPIO pin mapping to match production HAL */
    /* Pin 10 = left lock, Pin 11 = right lock (GPIO_LOCK_LEFT/RIGHT from actuator_hal.c) */
    if (pin == 10U) {
        mock_left_door_locked = false;
    } else if (pin == 11U) {
        mock_right_door_locked = false;
    }
}

void gpio_init_input_pullup(uint8_t pin) {
    (void)pin;
}

bool gpio_read(uint8_t pin) {
    /* DEFECT-INT-001 FIX: Correct GPIO pin mapping to match production HAL */
    /* Pin 20 = left obstacle (active low), Pin 21 = right obstacle (GPIO_OBSTACLE_* from sensor_hal.c) */
    /* Pin 22 = left emergency, Pin 23 = right emergency (GPIO_EMERG_HANDLE_* from sensor_hal.c) */
    
    /* DEFECT-INT-009 FIX: Sensor fault injection for obstacle sensors */
    if (pin == 20U) {
        /* Left obstacle sensor - return error value if fault injected */
        if (mock_sensor_fault_left_obstacle) {
            return true;  /* Return non-detecting state (active low) to simulate fault */
        }
        return !mock_left_obstacle_detected;  /* Active low */
    } else if (pin == 21U) {
        /* Right obstacle sensor */
        if (mock_sensor_fault_right_obstacle) {
            return true;  /* Return non-detecting state to simulate fault */
        }
        return !mock_right_obstacle_detected;  /* Active low */
    } else if (pin == 22U) {
        return !mock_left_emergency_active;    /* Active low */
    } else if (pin == 23U) {
        return !mock_right_emergency_active;   /* Active low */
    }
    return false;
}

/* ADC Driver */
error_t adc_init(uint8_t resolution, uint16_t vref_mv) {
    (void)resolution;
    (void)vref_mv;
    return mock_adc_init_error;
}

uint16_t adc_read(uint8_t channel) {
    /* DEFECT-INT-001 FIX: ADC channel mapping to match production HAL */
    /* Channel 0 = left position, Channel 1 = right position (ADC_CHANNEL_* from sensor_hal.c) */
    
    /* DEFECT-INT-009 & DEFECT-INT-016 FIX: Sensor fault injection for position sensors */
    if (channel == 0U) {
        /* Left position sensor */
        if (mock_sensor_fault_left_position) {
            return 0xFFFFU;  /* Return invalid value to simulate sensor fault */
        }
        /* DEFECT-INT-002 FIX: ADC returns current position updated by motor commands */
        return mock_left_position_raw;
    } else if (channel == 1U) {
        /* Right position sensor */
        if (mock_sensor_fault_right_position) {
            return 0xFFFFU;  /* Return invalid value to simulate sensor fault */
        }
        /* DEFECT-INT-002 FIX: ADC returns current position updated by motor commands */
        return mock_right_position_raw;
    }
    return 0;
}

/* CAN Controller Driver */
error_t can_controller_init(uint32_t baud_rate, uint8_t mode) {
    (void)baud_rate;
    (void)mode;
    return mock_can_init_error;
}

error_t can_filter_config(uint32_t filter_mask) {
    (void)filter_mask;
    return ERROR_SUCCESS;
}

error_t can_filter_add(uint32_t can_id) {
    (void)can_id;
    return ERROR_SUCCESS;
}

error_t can_transmit(uint32_t id, const uint8_t* data, uint8_t length) {
    if (mock_can_transmit_error != ERROR_SUCCESS) {
        return mock_can_transmit_error;
    }
    
    if (mock_can_tx_count >= MOCK_CAN_TX_QUEUE_SIZE) {
        return ERROR_BUFFER_FULL;
    }
    
    /* Store in TX queue for verification */
    mock_can_tx_queue[mock_can_tx_head].id = id;
    mock_can_tx_queue[mock_can_tx_head].dlc = length;
    if (data != NULL && length > 0U) {
        memcpy(mock_can_tx_queue[mock_can_tx_head].data, data, length);
    }
    mock_can_tx_queue[mock_can_tx_head].timestamp_ms = mock_system_time_ms;
    mock_can_tx_queue[mock_can_tx_head].valid = true;
    
    mock_can_tx_head = (mock_can_tx_head + 1U) % MOCK_CAN_TX_QUEUE_SIZE;
    mock_can_tx_count++;
    
    return ERROR_SUCCESS;
}

error_t can_receive(uint32_t* id, uint8_t* data, uint8_t* length) {
    if (mock_can_receive_error != ERROR_SUCCESS) {
        return mock_can_receive_error;
    }
    
    if (id == NULL || data == NULL || length == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (mock_can_rx_count == 0U) {
        return ERROR_NO_DATA;
    }
    
    /* Retrieve from RX queue */
    *id = mock_can_rx_queue[mock_can_rx_tail].id;
    *length = mock_can_rx_queue[mock_can_rx_tail].dlc;
    memcpy(data, mock_can_rx_queue[mock_can_rx_tail].data, *length);
    
    mock_can_rx_tail = (mock_can_rx_tail + 1U) % MOCK_CAN_RX_QUEUE_SIZE;
    mock_can_rx_count--;
    
    return ERROR_SUCCESS;
}

bool can_is_rx_ready(void) {
    return (mock_can_rx_count > 0U);
}

/* UART Driver */
error_t uart_init(uint32_t baud_rate, uint8_t config) {
    (void)baud_rate;
    (void)config;
    return ERROR_SUCCESS;  /* Always succeed for integration testing */
}

void uart_send_byte(uint8_t byte) {
    /* For integration testing, just ignore UART output */
    (void)byte;
}

void uart_send_string(const char* str) {
    (void)str;
}

/* LED Driver */
void led_init(uint8_t led_id) {
    (void)led_id;
}

void led_on(uint8_t led_id) {
    (void)led_id;
}

void led_off(uint8_t led_id) {
    (void)led_id;
}

void led_toggle(uint8_t led_id) {
    (void)led_id;
}

/* System Time */
uint32_t get_system_time_ms(void) {
    return mock_system_time_ms;
}

/* Additional Hardware Driver Stubs (for status_reporter and communication_hal) */

/**
 * @brief set_led stub - LED control for status display
 */
void set_led(uint8_t led_id, bool state) {
    (void)led_id;
    (void)state;
    /* Mock implementation - no actual LED hardware */
}

/**
 * @brief uart_transmit stub - UART transmission
 */
error_t uart_transmit(const uint8_t* data, uint8_t length) {
    (void)data;
    (void)length;
    /* Mock implementation - no actual UART hardware */
    return ERROR_SUCCESS;
}

/**
 * @brief uart_receive stub - UART reception
 */
error_t uart_receive(uint8_t* data) {
    (void)data;
    /* Mock implementation - no actual UART hardware */
    return ERROR_NO_DATA;  /* No data available */
}

/**
 * @brief uart_is_rx_ready stub - Check if UART data available
 */
bool uart_is_rx_ready(void) {
    /* Mock implementation - no actual UART hardware */
    return false;  /* No data available */
}
