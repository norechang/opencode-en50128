/**
 * @file test_mocks.c
 * @brief Centralized hardware driver stubs for unit testing
 * 
 * TRACEABILITY: DOC-COMPTEST-2026-001 v1.0
 * SIL Level: 3
 * 
 * This file provides hardware driver stubs (PWM, GPIO, ADC, CAN, UART, LED)
 * that are NOT part of the safety software but are needed to link tests.
 * 
 * Module-specific mocks (sensor_hal, actuator_hal, etc.) are defined
 * in individual test files to match their specific extern declarations.
 */

#include "test_mocks.h"

/* =============================================================================
 * Hardware Driver Call Counters (for test verification)
 * ============================================================================= */

static uint32_t mock_pwm_init_calls = 0U;
static uint32_t mock_gpio_init_calls = 0U;
static uint32_t mock_adc_init_calls = 0U;
static uint32_t mock_can_init_calls = 0U;
static uint32_t mock_uart_init_calls = 0U;
static uint32_t mock_led_set_calls = 0U;

/* =============================================================================
 * PWM Timer Driver Stubs
 * ============================================================================= */

error_t pwm_timer_init(void)
{
    mock_pwm_init_calls++;
    return ERROR_SUCCESS;
}

error_t pwm_set_duty_cycle(uint8_t channel, uint16_t duty_cycle)
{
    (void)channel;
    (void)duty_cycle;
    return ERROR_SUCCESS;
}

error_t pwm_stop(uint8_t channel)
{
    (void)channel;
    return ERROR_SUCCESS;
}

/* =============================================================================
 * GPIO Driver Stubs
 * ============================================================================= */

error_t gpio_init_output(uint8_t pin)
{
    (void)pin;
    mock_gpio_init_calls++;
    return ERROR_SUCCESS;
}

error_t gpio_init_input(uint8_t pin)
{
    (void)pin;
    mock_gpio_init_calls++;
    return ERROR_SUCCESS;
}

error_t gpio_set_pin(uint8_t pin, bool state)
{
    (void)pin;
    (void)state;
    return ERROR_SUCCESS;
}

bool gpio_read_pin(uint8_t pin)
{
    (void)pin;
    return false;
}

/* =============================================================================
 * ADC Driver Stubs
 * ============================================================================= */

error_t adc_init(void)
{
    mock_adc_init_calls++;
    return ERROR_SUCCESS;
}

uint16_t adc_read(uint8_t channel)
{
    (void)channel;
    return 0U;
}

/* =============================================================================
 * CAN Bus Driver Stubs
 * ============================================================================= */

error_t can_init(uint32_t baudrate)
{
    (void)baudrate;
    mock_can_init_calls++;
    return ERROR_SUCCESS;
}

error_t can_transmit(uint32_t id, const uint8_t* data, uint8_t length)
{
    (void)id;
    (void)data;
    (void)length;
    return ERROR_SUCCESS;
}

error_t can_receive(uint32_t* id, uint8_t* data, uint8_t* length)
{
    (void)id;
    (void)data;
    (void)length;
    return ERROR_TIMEOUT;  /* No data available */
}

/* =============================================================================
 * UART Driver Stubs
 * ============================================================================= */

error_t uart_init(uint32_t baudrate)
{
    (void)baudrate;
    mock_uart_init_calls++;
    return ERROR_SUCCESS;
}

error_t uart_transmit(const uint8_t* data, uint16_t length)
{
    (void)data;
    (void)length;
    return ERROR_SUCCESS;
}

error_t uart_receive(uint8_t* data, uint16_t* length)
{
    (void)data;
    (void)length;
    return ERROR_TIMEOUT;  /* No data available */
}

/* =============================================================================
 * LED Driver Stubs
 * ============================================================================= */

error_t set_led(uint8_t led_id, bool state)
{
    (void)led_id;
    (void)state;
    mock_led_set_calls++;
    return ERROR_SUCCESS;
}

/* =============================================================================
 * System Time Function (used by multiple modules)
 * ============================================================================= */

static uint32_t mock_system_time_ms = 0U;

uint32_t get_system_time_ms(void)
{
    return mock_system_time_ms;
}

void mock_set_system_time(uint32_t time_ms)
{
    mock_system_time_ms = time_ms;
}

void mock_advance_time(uint32_t delta_ms)
{
    mock_system_time_ms += delta_ms;
}

/* =============================================================================
 * Hardware Driver Call Counter Accessors
 * ============================================================================= */

uint32_t mock_get_pwm_init_calls(void)
{
    return mock_pwm_init_calls;
}

uint32_t mock_get_gpio_init_calls(void)
{
    return mock_gpio_init_calls;
}

uint32_t mock_get_adc_init_calls(void)
{
    return mock_adc_init_calls;
}

uint32_t mock_get_can_init_calls(void)
{
    return mock_can_init_calls;
}

uint32_t mock_get_uart_init_calls(void)
{
    return mock_uart_init_calls;
}

uint32_t mock_get_led_set_calls(void)
{
    return mock_led_set_calls;
}

/* =============================================================================
 * Mock Reset Function
 * ============================================================================= */

void reset_hardware_mocks(void)
{
    mock_system_time_ms = 0U;
    mock_pwm_init_calls = 0U;
    mock_gpio_init_calls = 0U;
    mock_adc_init_calls = 0U;
    mock_can_init_calls = 0U;
    mock_uart_init_calls = 0U;
    mock_led_set_calls = 0U;
}
