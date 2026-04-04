/**
 * @file    hal_test_vars.c
 * @brief   Provides the hal_stub_* control variables for test_hal.c.
 *          test_hal.c tests the real hal_services.c, so it cannot compile
 *          hal_stub.c (which would cause duplicate function symbols).
 *          This TU provides only the variable definitions that test_hal.c
 *          references in its setUp().
 *
 * @project TDC (Train Door Control System) — Unit Test Build Support
 * @note    NOT safety software.  Test infrastructure only.
 */

#include <stdint.h>
#include "tdc_types.h"

/* Control variables accessed by test_hal.c setUp() */
error_t  hal_stub_can_transmit_ret  = SUCCESS;
error_t  hal_stub_spi_exchange_ret  = SUCCESS;
error_t  hal_stub_watchdog_ret      = SUCCESS;
uint8_t  hal_stub_gpio_value        = 0U;
uint32_t hal_stub_tick_ms           = 0U;
