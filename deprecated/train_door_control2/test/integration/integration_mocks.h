/**
 * @file integration_mocks.h
 * @brief Integration test mocks and simulation for hardware/external dependencies
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.6
 * @test_phase Phase 6 Activity 0b (Integration Test Execution)
 * @traceability DOC-INTTEST-2026-001 v1.0
 * 
 * @description
 * Provides mock implementations of hardware drivers and external dependencies
 * for integration testing on host PC (x86_64). All HAL functions are simulated.
 * 
 * @warning
 * These mocks are for SOFTWARE integration testing only (Phase 6).
 * Hardware/software integration testing (target hardware) is DEFERRED.
 */

#ifndef INTEGRATION_MOCKS_H
#define INTEGRATION_MOCKS_H

#include "../../src/common/types.h"
#include "../../src/common/error_codes.h"
#include "../../src/sensor_hal/sensor_hal.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*===========================================================================*/
/* Mock State Variables (Simulated Hardware State)                          */
/*===========================================================================*/

/* PWM Outputs (simulated motor control) */
extern int8_t mock_left_door_pwm;       /* -100 to +100 */
extern int8_t mock_right_door_pwm;      /* -100 to +100 */

/* GPIO Outputs (simulated lock control) */
extern bool mock_left_door_locked;      /* true = locked */
extern bool mock_right_door_locked;

/* ADC Inputs (simulated position sensors) */
extern uint16_t mock_left_position_raw;   /* 0-4095 (12-bit ADC) */
extern uint16_t mock_right_position_raw;

/* GPIO Inputs (simulated obstacle sensors) */
extern bool mock_left_obstacle_detected;  /* true = obstacle */
extern bool mock_right_obstacle_detected;

/* GPIO Inputs (simulated emergency handles) */
extern bool mock_left_emergency_active;   /* true = pulled */
extern bool mock_right_emergency_active;

/* CAN Bus Simulation */
typedef struct {
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8];
    uint32_t timestamp_ms;
    bool valid;
} mock_can_message_t;

#define MOCK_CAN_RX_QUEUE_SIZE 16
#define MOCK_CAN_TX_QUEUE_SIZE 16

extern mock_can_message_t mock_can_rx_queue[MOCK_CAN_RX_QUEUE_SIZE];
extern uint8_t mock_can_rx_head;
extern uint8_t mock_can_rx_tail;
extern uint8_t mock_can_rx_count;

extern mock_can_message_t mock_can_tx_queue[MOCK_CAN_TX_QUEUE_SIZE];
extern uint8_t mock_can_tx_head;
extern uint8_t mock_can_tx_tail;
extern uint8_t mock_can_tx_count;

/* Speed Data (from CAN or simulated) */
extern uint16_t mock_primary_speed;    /* km/h * 10 */
extern uint16_t mock_secondary_speed;  /* km/h * 10 */
extern uint32_t mock_last_speed_update_ms;

/* System Time Simulation */
extern uint32_t mock_system_time_ms;

/* Error Injection */
extern error_t mock_pwm_init_error;
extern error_t mock_adc_init_error;
extern error_t mock_can_init_error;
extern error_t mock_can_transmit_error;
extern error_t mock_can_receive_error;

/* DEFECT-INT-009 & DEFECT-INT-016 FIX: Sensor-specific fault injection */
extern bool mock_sensor_fault_left_position;   /**< Inject left position sensor fault */
extern bool mock_sensor_fault_right_position;  /**< Inject right position sensor fault */
extern bool mock_sensor_fault_left_obstacle;   /**< Inject left obstacle sensor fault */
extern bool mock_sensor_fault_right_obstacle;  /**< Inject right obstacle sensor fault */

/*===========================================================================*/
/* Mock Control Functions                                                    */
/*===========================================================================*/

/**
 * @brief Reset all mock state to safe defaults
 */
void mock_reset_all(void);

/**
 * @brief Advance simulated system time
 * @param[in] delta_ms Time increment in milliseconds
 */
void mock_advance_time(uint32_t delta_ms);

/**
 * @brief Inject CAN message into RX queue
 * @param[in] id CAN message ID
 * @param[in] data Data bytes (up to 8)
 * @param[in] dlc Data length code (0-8)
 * @return ERROR_SUCCESS on success, ERROR_BUFFER_FULL if queue full
 */
error_t mock_can_inject_message(uint32_t id, const uint8_t* data, uint8_t dlc);

/**
 * @brief Get last transmitted CAN message
 * @param[out] msg Pointer to store message
 * @return ERROR_SUCCESS on success, ERROR_NO_DATA if queue empty
 */
error_t mock_can_get_last_tx(mock_can_message_t* msg);

/**
 * @brief Set simulated door position (for both doors)
 * @param[in] left_pct Left door position (0-100%)
 * @param[in] right_pct Right door position (0-100%)
 */
void mock_set_door_positions(uint8_t left_pct, uint8_t right_pct);

/**
 * @brief Set simulated train speed
 * @param[in] speed_kmh Speed in km/h (will be converted to 0.1 km/h units)
 */
void mock_set_train_speed(uint16_t speed_kmh);

/**
 * @brief Set obstacle detection state
 * @param[in] side Door side
 * @param[in] detected true = obstacle detected
 */
void mock_set_obstacle(door_side_t side, bool detected);

/**
 * @brief Set emergency handle state
 * @param[in] side Door side
 * @param[in] activated true = handle pulled
 */
void mock_set_emergency_handle(door_side_t side, bool activated);

/**
 * @brief Simulate door position change based on PWM (for realistic testing)
 * @param[in] delta_ms Time elapsed since last update
 * 
 * @note Approximates door motion: 0-100% in ~5 seconds opening, ~7 seconds closing
 */
void mock_simulate_door_motion(uint32_t delta_ms);

/**
 * @brief Inject hardware error (for fault testing)
 * @param[in] error_type Error code to inject on next hardware call
 */
void mock_inject_error(error_t error_type);

/**
 * @brief Clear all injected errors
 */
void mock_clear_errors(void);

/**
 * @brief Inject sensor fault (DEFECT-INT-009 & DEFECT-INT-016 FIX)
 * @param[in] side Door side (DOOR_SIDE_LEFT or DOOR_SIDE_RIGHT)
 * @param[in] sensor_type 0=position, 1=obstacle
 * @param[in] fault_active true = inject fault, false = clear fault
 */
void mock_inject_sensor_fault(door_side_t side, uint8_t sensor_type, bool fault_active);

/*===========================================================================*/
/* Hardware Driver Stubs (implementations in integration_mocks.c)           */
/*===========================================================================*/

/* PWM Timer Driver */
error_t pwm_timer_init(uint8_t timer_id, uint16_t freq_hz);
void pwm_set_duty_cycle(uint8_t timer_id, int8_t duty_cycle);

/* GPIO Driver */
void gpio_init_output(uint8_t pin);
void gpio_set_high(uint8_t pin);
void gpio_set_low(uint8_t pin);
void gpio_init_input_pullup(uint8_t pin);
bool gpio_read(uint8_t pin);

/* ADC Driver */
error_t adc_init(uint8_t resolution, uint16_t vref_mv);
uint16_t adc_read(uint8_t channel);

/* CAN Controller Driver */
error_t can_controller_init(uint32_t baud_rate, uint8_t mode);
error_t can_filter_config(uint32_t filter_mask);
error_t can_filter_add(uint32_t can_id);
error_t can_transmit(uint32_t id, const uint8_t* data, uint8_t length);
error_t can_receive(uint32_t* id, uint8_t* data, uint8_t* length);
bool can_is_rx_ready(void);

/* LED Driver */
void led_init(uint8_t led_id);
void led_on(uint8_t led_id);
void led_off(uint8_t led_id);
void led_toggle(uint8_t led_id);
void set_led(uint8_t led_id, bool state);  /* Additional LED function */

/* UART Driver */
error_t uart_init(uint32_t baud_rate, uint8_t config);
void uart_send_byte(uint8_t byte);
void uart_send_string(const char* str);
error_t uart_transmit(const uint8_t* data, uint8_t length);
error_t uart_receive(uint8_t* data);
bool uart_is_rx_ready(void);

/* System Time */
uint32_t get_system_time_ms(void);

#endif /* INTEGRATION_MOCKS_H */
