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
 * All function signatures match the extern declarations in the source modules
 * exactly so that the entire test binary links with a single mock file.
 */

#include "test_mocks.h"
#include <string.h>  /* memcpy */

/* =============================================================================
 * Controllable mock return values (extern-visible, set by test files)
 * ============================================================================= */

error_t  mock_pwm_timer_init_result      = ERROR_SUCCESS;
error_t  mock_adc_init_result            = ERROR_SUCCESS;
error_t  mock_can_controller_init_result = ERROR_SUCCESS;
error_t  mock_can_filter_config_result   = ERROR_SUCCESS;
error_t  mock_can_filter_add_result      = ERROR_SUCCESS;
error_t  mock_uart_init_result           = ERROR_SUCCESS;
error_t  mock_can_transmit_result        = ERROR_SUCCESS;
error_t  mock_can_receive_result         = ERROR_SUCCESS;
error_t  mock_uart_receive_result        = ERROR_NO_DATA;
error_t  mock_uart_transmit_result       = ERROR_SUCCESS;

bool     mock_can_is_rx_ready_value      = false;
bool     mock_uart_is_rx_ready_value     = false;
bool     mock_gpio_read_value            = false;
bool     mock_pwm_timer_init_fail_on_second = false;
uint16_t mock_adc_read_value             = 0U;

uint32_t mock_can_receive_id             = 0U;
uint8_t  mock_can_receive_data[8]        = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};
uint8_t  mock_can_receive_dlc            = 0U;

/* =============================================================================
 * Hardware Driver Call Counters
 * ============================================================================= */

static uint32_t mock_pwm_init_calls  = 0U;
static uint32_t mock_gpio_init_calls = 0U;
static uint32_t mock_adc_init_calls  = 0U;
static uint32_t mock_can_init_calls  = 0U;
static uint32_t mock_uart_init_calls = 0U;
static uint32_t mock_led_set_calls   = 0U;

/* =============================================================================
 * System Time
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
 * PWM Timer Driver Stubs
 * Matches: extern error_t pwm_timer_init(uint8_t timer_id, uint16_t freq_hz);
 *          extern void    pwm_set_duty_cycle(uint8_t timer_id, int8_t duty_cycle);
 * ============================================================================= */

error_t pwm_timer_init(uint8_t timer_id, uint16_t freq_hz)
{
    (void)timer_id;
    (void)freq_hz;
    mock_pwm_init_calls++;
    if (mock_pwm_timer_init_fail_on_second && (mock_pwm_init_calls >= 2U)) {
        return mock_pwm_timer_init_result;
    }
    if (!mock_pwm_timer_init_fail_on_second) {
        return mock_pwm_timer_init_result;
    }
    return ERROR_SUCCESS;
}

void pwm_set_duty_cycle(uint8_t timer_id, int8_t duty_cycle)
{
    (void)timer_id;
    (void)duty_cycle;
}

/* =============================================================================
 * GPIO Driver Stubs
 * Matches: extern void gpio_init_output(uint8_t pin);
 *          extern void gpio_set_high(uint8_t pin);
 *          extern void gpio_set_low(uint8_t pin);
 *          extern void gpio_init_input_pullup(uint8_t pin);
 *          extern bool gpio_read(uint8_t pin);
 * ============================================================================= */

void gpio_init_output(uint8_t pin)
{
    (void)pin;
    mock_gpio_init_calls++;
}

void gpio_set_high(uint8_t pin)
{
    (void)pin;
}

void gpio_set_low(uint8_t pin)
{
    (void)pin;
}

void gpio_init_input_pullup(uint8_t pin)
{
    (void)pin;
    mock_gpio_init_calls++;
}

bool gpio_read(uint8_t pin)
{
    (void)pin;
    return mock_gpio_read_value;
}

/* =============================================================================
 * ADC Driver Stubs
 * Matches: extern error_t  adc_init(uint8_t resolution, uint16_t vref_mv);
 *          extern uint16_t adc_read(uint8_t channel);
 * ============================================================================= */

error_t adc_init(uint8_t resolution, uint16_t vref_mv)
{
    (void)resolution;
    (void)vref_mv;
    mock_adc_init_calls++;
    return mock_adc_init_result;
}

uint16_t adc_read(uint8_t channel)
{
    (void)channel;
    return mock_adc_read_value;
}

/* =============================================================================
 * CAN Bus Driver Stubs
 * Matches: extern error_t can_controller_init(uint32_t baud_rate, uint8_t mode);
 *          extern error_t can_filter_config(uint32_t filter_mask);
 *          extern error_t can_filter_add(uint32_t can_id);
 *          extern error_t can_transmit(uint32_t id, const uint8_t* data, uint8_t dlc);
 *          extern error_t can_receive(uint32_t* id, uint8_t* data, uint8_t* dlc);
 *          extern bool    can_is_rx_ready(void);
 * ============================================================================= */

error_t can_controller_init(uint32_t baud_rate, uint8_t mode)
{
    (void)baud_rate;
    (void)mode;
    mock_can_init_calls++;
    return mock_can_controller_init_result;
}

error_t can_filter_config(uint32_t filter_mask)
{
    (void)filter_mask;
    return mock_can_filter_config_result;
}

error_t can_filter_add(uint32_t can_id)
{
    (void)can_id;
    return mock_can_filter_add_result;
}

error_t can_transmit(uint32_t id, const uint8_t* data, uint8_t length)
{
    (void)id;
    (void)data;
    (void)length;
    return mock_can_transmit_result;
}

error_t can_receive(uint32_t* id, uint8_t* data, uint8_t* length)
{
    if (id != NULL) {
        *id = mock_can_receive_id;
    }
    if (data != NULL) {
        (void)memcpy(data, mock_can_receive_data, 8U);
    }
    if (length != NULL) {
        *length = mock_can_receive_dlc;
    }
    return mock_can_receive_result;
}

bool can_is_rx_ready(void)
{
    return mock_can_is_rx_ready_value;
}

/* =============================================================================
 * UART Driver Stubs
 * Matches: extern error_t uart_init(uint32_t baud_rate, uint8_t config);
 *          extern error_t uart_transmit(const uint8_t* data, uint16_t length);
 *          extern error_t uart_receive(uint8_t* data, uint16_t* length);
 *          extern bool    uart_is_rx_ready(void);
 * ============================================================================= */

error_t uart_init(uint32_t baud_rate, uint8_t config)
{
    (void)baud_rate;
    (void)config;
    mock_uart_init_calls++;
    return mock_uart_init_result;
}

error_t uart_transmit(const uint8_t* data, uint16_t length)
{
    (void)data;
    (void)length;
    return mock_uart_transmit_result;
}

error_t uart_receive(uint8_t* data, uint16_t* length)
{
    (void)data;
    (void)length;
    return mock_uart_receive_result;
}

bool uart_is_rx_ready(void)
{
    return mock_uart_is_rx_ready_value;
}

/* =============================================================================
 * LED Driver Stub
 * Matches: extern void set_led(uint8_t led_id, uint8_t state);  (status_reporter.c)
 * ============================================================================= */

void set_led(uint8_t led_id, uint8_t state)
{
    (void)led_id;
    (void)state;
    mock_led_set_calls++;
}

/* =============================================================================
 * Hardware Driver Call Counter Accessors
 * ============================================================================= */

uint32_t mock_get_pwm_init_calls(void)  { return mock_pwm_init_calls;  }
uint32_t mock_get_gpio_init_calls(void) { return mock_gpio_init_calls; }
uint32_t mock_get_adc_init_calls(void)  { return mock_adc_init_calls;  }
uint32_t mock_get_can_init_calls(void)  { return mock_can_init_calls;  }
uint32_t mock_get_uart_init_calls(void) { return mock_uart_init_calls; }
uint32_t mock_get_led_set_calls(void)   { return mock_led_set_calls;   }

/* =============================================================================
 * Mock Reset Function
 * ============================================================================= */

void reset_hardware_mocks(void)
{
    uint8_t i;

    mock_system_time_ms = 0U;

    /* Reset call counters */
    mock_pwm_init_calls  = 0U;
    mock_gpio_init_calls = 0U;
    mock_adc_init_calls  = 0U;
    mock_can_init_calls  = 0U;
    mock_uart_init_calls = 0U;
    mock_led_set_calls   = 0U;

    /* Reset return-value controls */
    mock_pwm_timer_init_result      = ERROR_SUCCESS;
    mock_adc_init_result            = ERROR_SUCCESS;
    mock_can_controller_init_result = ERROR_SUCCESS;
    mock_can_filter_config_result   = ERROR_SUCCESS;
    mock_can_filter_add_result      = ERROR_SUCCESS;
    mock_uart_init_result           = ERROR_SUCCESS;
    mock_can_transmit_result        = ERROR_SUCCESS;
    mock_can_receive_result         = ERROR_SUCCESS;
    mock_uart_receive_result        = ERROR_NO_DATA;
    mock_uart_transmit_result       = ERROR_SUCCESS;

    /* Reset state variables */
    mock_can_is_rx_ready_value      = false;
    mock_uart_is_rx_ready_value     = false;
    mock_gpio_read_value            = false;
    mock_pwm_timer_init_fail_on_second = false;
    mock_adc_read_value             = 0U;

    mock_can_receive_id  = 0U;
    mock_can_receive_dlc = 0U;
    for (i = 0U; i < 8U; i++) {
        mock_can_receive_data[i] = 0U;
    }
}
