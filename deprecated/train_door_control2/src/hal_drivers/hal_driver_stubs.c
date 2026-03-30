/**
 * @file hal_driver_stubs.c
 * @brief Hardware driver stub implementations for compilation and testing
 * 
 * Module: Hardware Abstraction Layer (HAL) Driver Stubs
 * 
 * Purpose:
 * This file provides stub implementations for low-level hardware drivers.
 * These stubs simulate hardware behavior for testing purposes.
 * 
 * IMPORTANT: These stubs are NOT part of the safety-critical software.
 * They are test infrastructure only.
 * 
 * @version 1.0
 * @date 2026-02-22
 * 
 * @copyright Copyright (c) 2026
 * 
 * Safety Integrity Level: N/A (Test infrastructure only)
 */

#include "hal_driver_stubs.h"
#include <string.h>

/*============================================================================*/
/* Private Variables (Test State)                                            */
/*============================================================================*/

static uint8_t pwm_duty_cycles[4] = {0, 0, 0, 0};
static bool gpio_states[32] = {false};
static uint16_t adc_values[8] = {0, 0, 0, 0, 0, 0, 0, 0};

/* CAN message queue (simple ring buffer) */
#define CAN_QUEUE_SIZE 16
static struct {
    uint32_t id;
    uint8_t data[8];
    uint8_t length;
    bool valid;
} can_rx_queue[CAN_QUEUE_SIZE];
static uint8_t can_rx_head = 0;
static uint8_t can_rx_tail = 0;

/* UART buffers */
#define UART_RX_BUFFER_SIZE 256
static uint8_t uart_rx_buffer[UART_RX_BUFFER_SIZE];
static uint16_t uart_rx_count = 0;

/*============================================================================*/
/* PWM Driver Stubs                                                          */
/*============================================================================*/

bool pwm_init(void)
{
    /* Initialize PWM duty cycles to 0 */
    (void)memset(pwm_duty_cycles, 0, sizeof(pwm_duty_cycles));
    return true;
}

bool pwm_set_duty_cycle(uint8_t channel, uint8_t duty_cycle)
{
    if (channel >= 4U) {
        return false;
    }
    if (duty_cycle > 100U) {
        return false;
    }
    pwm_duty_cycles[channel] = duty_cycle;
    return true;
}

void pwm_stop(uint8_t channel)
{
    if (channel < 4U) {
        pwm_duty_cycles[channel] = 0;
    }
}

/*============================================================================*/
/* GPIO Driver Stubs                                                         */
/*============================================================================*/

bool gpio_init(void)
{
    /* Initialize GPIO states to false (low) */
    (void)memset(gpio_states, 0, sizeof(gpio_states));
    return true;
}

void gpio_write(uint8_t pin, bool state)
{
    if (pin < 32U) {
        gpio_states[pin] = state;
    }
}

bool gpio_read(uint8_t pin)
{
    if (pin < 32U) {
        return gpio_states[pin];
    }
    return false;
}

/*============================================================================*/
/* ADC Driver Stubs                                                          */
/*============================================================================*/

bool adc_init(void)
{
    /* Initialize ADC values to 0 */
    (void)memset(adc_values, 0, sizeof(adc_values));
    return true;
}

uint16_t adc_read(uint8_t channel)
{
    if (channel >= 8U) {
        return 0xFFFFU;
    }
    return adc_values[channel];
}

/*============================================================================*/
/* CAN Driver Stubs                                                          */
/*============================================================================*/

bool can_init(uint32_t baudrate)
{
    /* Validate baudrate */
    if ((baudrate != 125U) && (baudrate != 250U) && 
        (baudrate != 500U) && (baudrate != 1000U)) {
        return false;
    }
    
    /* Initialize CAN queue */
    (void)memset(can_rx_queue, 0, sizeof(can_rx_queue));
    can_rx_head = 0;
    can_rx_tail = 0;
    
    return true;
}

bool can_send(uint32_t id, const uint8_t *data, uint8_t length)
{
    /* Validate parameters */
    if (data == NULL) {
        return false;
    }
    if (id > 0x7FFU) {  /* 11-bit standard CAN ID */
        return false;
    }
    if (length > 8U) {
        return false;
    }
    
    /* Stub: just return success (no actual transmission) */
    return true;
}

bool can_receive(uint32_t *id, uint8_t *data, uint8_t *length)
{
    /* Validate parameters */
    if ((id == NULL) || (data == NULL) || (length == NULL)) {
        return false;
    }
    
    /* Check if queue is empty */
    if (can_rx_head == can_rx_tail) {
        return false;
    }
    
    /* Retrieve message from queue */
    if (can_rx_queue[can_rx_tail].valid) {
        *id = can_rx_queue[can_rx_tail].id;
        *length = can_rx_queue[can_rx_tail].length;
        (void)memcpy(data, can_rx_queue[can_rx_tail].data, *length);
        
        /* Mark as consumed */
        can_rx_queue[can_rx_tail].valid = false;
        can_rx_tail = (can_rx_tail + 1U) % CAN_QUEUE_SIZE;
        
        return true;
    }
    
    return false;
}

/*============================================================================*/
/* UART Driver Stubs                                                         */
/*============================================================================*/

bool uart_init(uint32_t baudrate)
{
    /* Validate baudrate */
    if ((baudrate != 9600U) && (baudrate != 19200U) && 
        (baudrate != 38400U) && (baudrate != 57600U) && 
        (baudrate != 115200U)) {
        return false;
    }
    
    /* Initialize UART buffer */
    (void)memset(uart_rx_buffer, 0, sizeof(uart_rx_buffer));
    uart_rx_count = 0;
    
    return true;
}

uint16_t uart_send(const uint8_t *data, uint16_t length)
{
    /* Validate parameters */
    if (data == NULL) {
        return 0;
    }
    
    /* Stub: just return length (no actual transmission) */
    return length;
}

uint16_t uart_receive(uint8_t *data, uint16_t max_length)
{
    /* Validate parameters */
    if (data == NULL) {
        return 0;
    }
    
    /* Check if data available */
    if (uart_rx_count == 0U) {
        return 0;
    }
    
    /* Copy available data (up to max_length) */
    uint16_t to_copy = (uart_rx_count < max_length) ? uart_rx_count : max_length;
    (void)memcpy(data, uart_rx_buffer, to_copy);
    
    /* Update buffer */
    uart_rx_count -= to_copy;
    if (uart_rx_count > 0U) {
        (void)memmove(uart_rx_buffer, &uart_rx_buffer[to_copy], uart_rx_count);
    }
    
    return to_copy;
}

/*============================================================================*/
/* Test Helper Functions (for injecting test data)                           */
/*============================================================================*/

/* These functions are not declared in the header - they are for internal
   test harness use only */

void test_adc_set_value(uint8_t channel, uint16_t value)
{
    if (channel < 8U) {
        adc_values[channel] = value;
    }
}

void test_gpio_set_state(uint8_t pin, bool state)
{
    if (pin < 32U) {
        gpio_states[pin] = state;
    }
}

void test_can_inject_message(uint32_t id, const uint8_t *data, uint8_t length)
{
    if ((data != NULL) && (length <= 8U)) {
        uint8_t next_head = (can_rx_head + 1U) % CAN_QUEUE_SIZE;
        if (next_head != can_rx_tail) {  /* Queue not full */
            can_rx_queue[can_rx_head].id = id;
            can_rx_queue[can_rx_head].length = length;
            (void)memcpy(can_rx_queue[can_rx_head].data, data, length);
            can_rx_queue[can_rx_head].valid = true;
            can_rx_head = next_head;
        }
    }
}

void test_uart_inject_data(const uint8_t *data, uint16_t length)
{
    if ((data != NULL) && (length > 0U)) {
        uint16_t available = UART_RX_BUFFER_SIZE - uart_rx_count;
        uint16_t to_copy = (length < available) ? length : available;
        (void)memcpy(&uart_rx_buffer[uart_rx_count], data, to_copy);
        uart_rx_count += to_copy;
    }
}
