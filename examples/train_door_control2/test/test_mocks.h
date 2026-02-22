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
 * Module-specific mocks (sensor_hal, actuator_hal, safety_monitor, fault_detection)
 * are defined in individual test files to match their specific extern declarations.
 */

#ifndef TEST_MOCKS_H
#define TEST_MOCKS_H

#include "../src/common/types.h"
#include "../src/common/error_codes.h"

/* =============================================================================
 * PWM Timer Driver Stubs
 * ============================================================================= */

/**
 * @brief Initialize PWM timer (stub)
 * @return ERROR_SUCCESS always
 */
error_t pwm_timer_init(void);

/**
 * @brief Set PWM duty cycle (stub)
 * @param[in] channel PWM channel
 * @param[in] duty_cycle Duty cycle (0-1000)
 * @return ERROR_SUCCESS always
 */
error_t pwm_set_duty_cycle(uint8_t channel, uint16_t duty_cycle);

/**
 * @brief Stop PWM output (stub)
 * @param[in] channel PWM channel
 * @return ERROR_SUCCESS always
 */
error_t pwm_stop(uint8_t channel);

/* =============================================================================
 * GPIO Driver Stubs
 * ============================================================================= */

/**
 * @brief Initialize GPIO pin as output (stub)
 * @param[in] pin Pin number
 * @return ERROR_SUCCESS always
 */
error_t gpio_init_output(uint8_t pin);

/**
 * @brief Initialize GPIO pin as input (stub)
 * @param[in] pin Pin number
 * @return ERROR_SUCCESS always
 */
error_t gpio_init_input(uint8_t pin);

/**
 * @brief Set GPIO pin state (stub)
 * @param[in] pin Pin number
 * @param[in] state Pin state (true = high, false = low)
 * @return ERROR_SUCCESS always
 */
error_t gpio_set_pin(uint8_t pin, bool state);

/**
 * @brief Read GPIO pin state (stub)
 * @param[in] pin Pin number
 * @return false always
 */
bool gpio_read_pin(uint8_t pin);

/* =============================================================================
 * ADC Driver Stubs
 * ============================================================================= */

/**
 * @brief Initialize ADC (stub)
 * @return ERROR_SUCCESS always
 */
error_t adc_init(void);

/**
 * @brief Read ADC channel (stub)
 * @param[in] channel ADC channel
 * @return 0 always
 */
uint16_t adc_read(uint8_t channel);

/* =============================================================================
 * CAN Bus Driver Stubs
 * ============================================================================= */

/**
 * @brief Initialize CAN bus (stub)
 * @param[in] baudrate CAN baudrate
 * @return ERROR_SUCCESS always
 */
error_t can_init(uint32_t baudrate);

/**
 * @brief Transmit CAN message (stub)
 * @param[in] id CAN message ID
 * @param[in] data Pointer to data
 * @param[in] length Data length
 * @return ERROR_SUCCESS always
 */
error_t can_transmit(uint32_t id, const uint8_t* data, uint8_t length);

/**
 * @brief Receive CAN message (stub)
 * @param[out] id Pointer to store message ID
 * @param[out] data Pointer to store data
 * @param[out] length Pointer to store length
 * @return ERROR_TIMEOUT always (no data available)
 */
error_t can_receive(uint32_t* id, uint8_t* data, uint8_t* length);

/* =============================================================================
 * UART Driver Stubs
 * ============================================================================= */

/**
 * @brief Initialize UART (stub)
 * @param[in] baudrate UART baudrate
 * @return ERROR_SUCCESS always
 */
error_t uart_init(uint32_t baudrate);

/**
 * @brief Transmit UART data (stub)
 * @param[in] data Pointer to data
 * @param[in] length Data length
 * @return ERROR_SUCCESS always
 */
error_t uart_transmit(const uint8_t* data, uint16_t length);

/**
 * @brief Receive UART data (stub)
 * @param[out] data Pointer to store data
 * @param[out] length Pointer to store length
 * @return ERROR_TIMEOUT always (no data available)
 */
error_t uart_receive(uint8_t* data, uint16_t* length);

/* =============================================================================
 * LED Driver Stubs
 * ============================================================================= */

/**
 * @brief Set LED state (stub)
 * @param[in] led_id LED identifier
 * @param[in] state LED state (true = on, false = off)
 * @return ERROR_SUCCESS always
 */
error_t set_led(uint8_t led_id, bool state);

/* =============================================================================
 * System Time Functions
 * ============================================================================= */

/**
 * @brief Get system time in milliseconds
 * @return Current mock system time
 * @note This function is used by multiple modules
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
 * Hardware Driver Call Counter Accessors
 * ============================================================================= */

/**
 * @brief Get number of pwm_timer_init() calls
 * @return Call count
 */
uint32_t mock_get_pwm_init_calls(void);

/**
 * @brief Get number of gpio_init_*() calls
 * @return Call count
 */
uint32_t mock_get_gpio_init_calls(void);

/**
 * @brief Get number of adc_init() calls
 * @return Call count
 */
uint32_t mock_get_adc_init_calls(void);

/**
 * @brief Get number of can_init() calls
 * @return Call count
 */
uint32_t mock_get_can_init_calls(void);

/**
 * @brief Get number of uart_init() calls
 * @return Call count
 */
uint32_t mock_get_uart_init_calls(void);

/**
 * @brief Get number of set_led() calls
 * @return Call count
 */
uint32_t mock_get_led_set_calls(void);

/**
 * @brief Reset all hardware mocks and call counters
 */
void reset_hardware_mocks(void);

#endif /* TEST_MOCKS_H */
