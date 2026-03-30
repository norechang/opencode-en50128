/**
 * @file test_mocks.h
 * @brief Centralized hardware driver stubs for unit testing
 * 
 * TRACEABILITY: DOC-COMPTEST-2026-001 v1.0
 * SIL Level: 3
 * 
 * This header provides declarations for hardware driver stubs (PWM, GPIO, ADC, CAN, UART, LED)
 * and system time functions needed for unit testing.
 * 
 * Signatures match the extern declarations in each source module exactly.
 */

#ifndef TEST_MOCKS_H
#define TEST_MOCKS_H

#include "../src/common/types.h"
#include "../src/common/error_codes.h"

/* =============================================================================
 * PWM Timer Driver Stubs
 * Signatures match: actuator_hal.c extern declarations
 * ============================================================================= */

/**
 * @brief Initialize PWM timer (stub)
 * @param[in] timer_id  Timer channel ID
 * @param[in] freq_hz   PWM frequency in Hz
 * @return mock_pwm_timer_init_result (default ERROR_SUCCESS)
 */
error_t pwm_timer_init(uint8_t timer_id, uint16_t freq_hz);

/**
 * @brief Set PWM duty cycle (stub)
 * @param[in] timer_id    Timer channel ID
 * @param[in] duty_cycle  Signed duty cycle (-100..+100)
 */
void pwm_set_duty_cycle(uint8_t timer_id, int8_t duty_cycle);

/* =============================================================================
 * GPIO Driver Stubs
 * Signatures match: actuator_hal.c and sensor_hal.c extern declarations
 * ============================================================================= */

/**
 * @brief Initialize GPIO pin as output (stub)
 * @param[in] pin Pin number
 */
void gpio_init_output(uint8_t pin);

/**
 * @brief Drive GPIO pin high (stub)
 * @param[in] pin Pin number
 */
void gpio_set_high(uint8_t pin);

/**
 * @brief Drive GPIO pin low (stub)
 * @param[in] pin Pin number
 */
void gpio_set_low(uint8_t pin);

/**
 * @brief Initialize GPIO pin as input with pull-up (stub)
 * @param[in] pin Pin number
 */
void gpio_init_input_pullup(uint8_t pin);

/**
 * @brief Read GPIO pin state (stub)
 * @param[in] pin Pin number
 * @return mock_gpio_read_value (default false)
 */
bool gpio_read(uint8_t pin);

/* =============================================================================
 * ADC Driver Stubs
 * Signatures match: sensor_hal.c extern declarations
 * ============================================================================= */

/**
 * @brief Initialize ADC (stub)
 * @param[in] resolution  ADC resolution code
 * @param[in] vref_mv     Reference voltage in mV
 * @return mock_adc_init_result (default ERROR_SUCCESS)
 */
error_t adc_init(uint8_t resolution, uint16_t vref_mv);

/**
 * @brief Read ADC channel (stub)
 * @param[in] channel ADC channel
 * @return mock_adc_read_value (default 0)
 */
uint16_t adc_read(uint8_t channel);

/* =============================================================================
 * CAN Bus Driver Stubs
 * Signatures match: communication_hal.c and sensor_hal.c extern declarations
 * ============================================================================= */

/**
 * @brief Initialize CAN controller (stub)
 * @param[in] baud_rate  CAN baud rate
 * @param[in] mode       Controller mode
 * @return mock_can_controller_init_result (default ERROR_SUCCESS)
 */
error_t can_controller_init(uint32_t baud_rate, uint8_t mode);

/**
 * @brief Configure CAN acceptance filter (stub)
 * @param[in] filter_mask  Acceptance mask
 * @return mock_can_filter_config_result (default ERROR_SUCCESS)
 */
error_t can_filter_config(uint32_t filter_mask);

/**
 * @brief Add a CAN ID to the acceptance filter (stub)
 * @param[in] can_id  CAN message ID to accept
 * @return mock_can_filter_add_result (default ERROR_SUCCESS)
 */
error_t can_filter_add(uint32_t can_id);

/**
 * @brief Transmit CAN message (stub)
 * @param[in] id      CAN message ID
 * @param[in] data    Pointer to data bytes
 * @param[in] length  Number of data bytes
 * @return mock_can_transmit_result (default ERROR_SUCCESS)
 */
error_t can_transmit(uint32_t id, const uint8_t* data, uint8_t length);

/**
 * @brief Receive CAN message (stub)
 * @param[out] id      Pointer to store message ID
 * @param[out] data    Pointer to store data bytes
 * @param[out] length  Pointer to store DLC
 * @return mock_can_receive_result (default ERROR_SUCCESS when can_is_rx_ready)
 */
error_t can_receive(uint32_t* id, uint8_t* data, uint8_t* length);

/**
 * @brief Check CAN RX buffer status (stub)
 * @return mock_can_is_rx_ready_value (default false)
 */
bool can_is_rx_ready(void);

/* =============================================================================
 * UART Driver Stubs
 * Signatures match: communication_hal.c extern declarations
 * ============================================================================= */

/**
 * @brief Initialize UART (stub)
 * @param[in] baud_rate  UART baud rate
 * @param[in] config     UART configuration byte
 * @return mock_uart_init_result (default ERROR_SUCCESS)
 */
error_t uart_init(uint32_t baud_rate, uint8_t config);

/**
 * @brief Transmit UART data (stub)
 * @param[in] data    Pointer to data
 * @param[in] length  Data length
 * @return mock_uart_transmit_result (default ERROR_SUCCESS)
 */
error_t uart_transmit(const uint8_t* data, uint16_t length);

/**
 * @brief Receive UART data (stub)
 * @param[out] data    Pointer to store data
 * @param[out] length  Pointer to store length
 * @return ERROR_NO_DATA always (mock: no data available)
 */
error_t uart_receive(uint8_t* data, uint16_t* length);

/**
 * @brief Check UART RX buffer status (stub)
 * @return mock_uart_is_rx_ready_value (default false)
 */
bool uart_is_rx_ready(void);

/* =============================================================================
 * LED Driver Stubs
 * Signature matches: status_reporter.c extern declaration
 *   extern void set_led(uint8_t led_id, uint8_t state);
 * ============================================================================= */

/**
 * @brief Set LED state (stub)
 * @param[in] led_id  LED identifier
 * @param[in] state   LED state (non-zero = on, 0 = off)
 */
void set_led(uint8_t led_id, uint8_t state);

/* =============================================================================
 * System Time Functions
 * ============================================================================= */

/**
 * @brief Get system time in milliseconds
 * @return Current mock system time
 */
uint32_t get_system_time_ms(void);

/**
 * @brief Set mock system time
 * @param[in] time_ms Time in milliseconds
 */
void mock_set_system_time(uint32_t time_ms);

/**
 * @brief Advance mock system time
 * @param[in] delta_ms Time delta in milliseconds
 */
void mock_advance_time(uint32_t delta_ms);

/* =============================================================================
 * Controllable mock return values
 * Set these before calling the function under test to simulate failures.
 * ============================================================================= */

extern error_t mock_pwm_timer_init_result;
extern error_t mock_adc_init_result;
extern error_t mock_can_controller_init_result;
extern error_t mock_can_filter_config_result;
extern error_t mock_can_filter_add_result;
extern error_t mock_uart_init_result;
extern error_t mock_can_transmit_result;
extern error_t mock_can_receive_result;
extern error_t mock_uart_receive_result;
extern error_t mock_uart_transmit_result;

extern bool    mock_can_is_rx_ready_value;
extern bool    mock_uart_is_rx_ready_value;
extern bool    mock_gpio_read_value;
extern bool    mock_pwm_timer_init_fail_on_second;
extern uint16_t mock_adc_read_value;

/* CAN receive data populated when mock_can_receive_result == ERROR_SUCCESS */
extern uint32_t mock_can_receive_id;
extern uint8_t  mock_can_receive_data[8];
extern uint8_t  mock_can_receive_dlc;

/* =============================================================================
 * Hardware Driver Call Counter Accessors
 * ============================================================================= */

/** @brief Get number of pwm_timer_init() calls */
uint32_t mock_get_pwm_init_calls(void);

/** @brief Get number of gpio_init_*() calls */
uint32_t mock_get_gpio_init_calls(void);

/** @brief Get number of adc_init() calls */
uint32_t mock_get_adc_init_calls(void);

/** @brief Get number of can_controller_init() calls */
uint32_t mock_get_can_init_calls(void);

/** @brief Get number of uart_init() calls */
uint32_t mock_get_uart_init_calls(void);

/** @brief Get number of set_led() calls */
uint32_t mock_get_led_set_calls(void);

/**
 * @brief Reset all hardware mocks, call counters, and return values to defaults
 */
void reset_hardware_mocks(void);

#endif /* TEST_MOCKS_H */
