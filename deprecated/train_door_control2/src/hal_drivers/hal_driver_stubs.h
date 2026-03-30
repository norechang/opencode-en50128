/**
 * @file hal_driver_stubs.h
 * @brief Hardware driver stub declarations for compilation and testing
 * 
 * Module: Hardware Abstraction Layer (HAL) Driver Stubs
 * 
 * Purpose:
 * This file provides stub declarations for low-level hardware drivers.
 * These stubs allow the application to compile and link without actual
 * hardware dependencies. In production, these would be replaced with
 * real platform-specific driver implementations.
 * 
 * IMPORTANT: These stubs are NOT part of the safety-critical software.
 * They are test infrastructure only. The actual HAL interface in
 * actuator_hal.c, sensor_hal.c, and communication_hal.c IS safety-critical.
 * 
 * @version 1.0
 * @date 2026-02-22
 * 
 * @copyright Copyright (c) 2026
 * 
 * Safety Integrity Level: N/A (Test infrastructure only)
 */

#ifndef HAL_DRIVER_STUBS_H
#define HAL_DRIVER_STUBS_H

#include <stdint.h>
#include <stdbool.h>

/*============================================================================*/
/* PWM Driver Stubs (for motor control)                                      */
/*============================================================================*/

/**
 * @brief Initialize PWM hardware
 * @return true if successful, false otherwise
 */
bool pwm_init(void);

/**
 * @brief Set PWM duty cycle
 * @param channel PWM channel (0-3)
 * @param duty_cycle Duty cycle (0-100%)
 * @return true if successful, false otherwise
 */
bool pwm_set_duty_cycle(uint8_t channel, uint8_t duty_cycle);

/**
 * @brief Stop PWM output
 * @param channel PWM channel (0-3)
 */
void pwm_stop(uint8_t channel);

/*============================================================================*/
/* GPIO Driver Stubs (for digital I/O)                                       */
/*============================================================================*/

/**
 * @brief Initialize GPIO hardware
 * @return true if successful, false otherwise
 */
bool gpio_init(void);

/**
 * @brief Set GPIO pin state
 * @param pin GPIO pin number
 * @param state Pin state (true = high, false = low)
 */
void gpio_write(uint8_t pin, bool state);

/**
 * @brief Read GPIO pin state
 * @param pin GPIO pin number
 * @return Pin state (true = high, false = low)
 */
bool gpio_read(uint8_t pin);

/*============================================================================*/
/* ADC Driver Stubs (for analog sensor reading)                              */
/*============================================================================*/

/**
 * @brief Initialize ADC hardware
 * @return true if successful, false otherwise
 */
bool adc_init(void);

/**
 * @brief Read ADC value
 * @param channel ADC channel (0-7)
 * @return ADC value (0-4095 for 12-bit ADC, 0xFFFF on error)
 */
uint16_t adc_read(uint8_t channel);

/*============================================================================*/
/* CAN Driver Stubs (for CAN bus communication)                              */
/*============================================================================*/

/**
 * @brief Initialize CAN hardware
 * @param baudrate CAN baudrate in kbps (125, 250, 500, 1000)
 * @return true if successful, false otherwise
 */
bool can_init(uint32_t baudrate);

/**
 * @brief Send CAN message
 * @param id CAN message ID (11-bit standard)
 * @param data Pointer to data buffer
 * @param length Data length (0-8 bytes)
 * @return true if successful, false otherwise
 */
bool can_send(uint32_t id, const uint8_t *data, uint8_t length);

/**
 * @brief Receive CAN message (non-blocking)
 * @param id Pointer to store CAN message ID
 * @param data Pointer to data buffer (minimum 8 bytes)
 * @param length Pointer to store data length
 * @return true if message received, false if no message available
 */
bool can_receive(uint32_t *id, uint8_t *data, uint8_t *length);

/*============================================================================*/
/* UART Driver Stubs (for diagnostic console)                                */
/*============================================================================*/

/**
 * @brief Initialize UART hardware
 * @param baudrate UART baudrate (9600, 19200, 38400, 57600, 115200)
 * @return true if successful, false otherwise
 */
bool uart_init(uint32_t baudrate);

/**
 * @brief Send UART data
 * @param data Pointer to data buffer
 * @param length Data length
 * @return Number of bytes sent
 */
uint16_t uart_send(const uint8_t *data, uint16_t length);

/**
 * @brief Receive UART data (non-blocking)
 * @param data Pointer to data buffer
 * @param max_length Maximum data length
 * @return Number of bytes received
 */
uint16_t uart_receive(uint8_t *data, uint16_t max_length);

/*============================================================================*/
/* Test Helper Functions (for injecting test data)                           */
/*============================================================================*/

/**
 * @brief Set ADC value for testing
 * @param channel ADC channel (0-7)
 * @param value ADC value to set
 */
void test_adc_set_value(uint8_t channel, uint16_t value);

/**
 * @brief Set GPIO state for testing
 * @param pin GPIO pin number
 * @param state Pin state (true = high, false = low)
 */
void test_gpio_set_state(uint8_t pin, bool state);

/**
 * @brief Inject CAN message for testing
 * @param id CAN message ID
 * @param data Pointer to data buffer
 * @param length Data length (0-8 bytes)
 */
void test_can_inject_message(uint32_t id, const uint8_t *data, uint8_t length);

/**
 * @brief Inject UART data for testing
 * @param data Pointer to data buffer
 * @param length Data length
 */
void test_uart_inject_data(const uint8_t *data, uint16_t length);

#endif /* HAL_DRIVER_STUBS_H */
