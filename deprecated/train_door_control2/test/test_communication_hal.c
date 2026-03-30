/**
 * @file test_communication_hal.c
 * @brief Unit tests for Communication HAL Module (MOD-008)
 *
 * TRACEABILITY: DOC-COMPTEST-2026-001 v1.0
 * SIL Level: 3
 *
 * Coverage target (EN 50128 SIL 3 Table A.21):
 *   Statement: 100%, Branch: 100%, Condition (MC/DC): 100%
 *
 * Test cases: TC-MOD008-001 .. TC-MOD008-032
 *
 * ORDERING: This suite runs FIRST in the HAL runner (before sensor_hal and
 * actuator_hal) so that g_communication_hal is uninitialized at process start.
 * The "not initialized" tests (TC-MOD008-can_*_not_init, TC-MOD008-uart_*_not_init)
 * MUST run before the first communication_hal_init() call to cover lines 111,
 * 153, 211, 239 in communication_hal.c.
 */

#include "test_harness.h"
#include "test_mocks.h"
#include "../src/communication_hal/communication_hal.h"

/* Forward declaration */
void run_communication_hal_tests(void);

/* =========================================================================
 * TC-MOD008-can_send_not_init  can_send — not initialized → ERROR_NOT_INITIALIZED
 * MUST run before any call to communication_hal_init()
 * ========================================================================= */
static bool test_ch_can_send_not_initialized(void)
{
    /* g_communication_hal is uninitialized at process start */
    can_message_t msg;
    msg.id  = 0x100U;
    msg.dlc = 1U;
    msg.data[0] = 0x01U;
    error_t result = communication_hal_can_send(&msg);
    TEST_ASSERT_EQUAL(ERROR_NOT_INITIALIZED, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-can_receive_not_init  can_receive — not initialized → ERROR_NOT_INITIALIZED
 * MUST run before any call to communication_hal_init()
 * ========================================================================= */
static bool test_ch_can_receive_not_initialized(void)
{
    can_message_t msg;
    error_t result = communication_hal_can_receive(&msg);
    TEST_ASSERT_EQUAL(ERROR_NOT_INITIALIZED, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-uart_send_not_init  uart_send — not initialized → ERROR_NOT_INITIALIZED
 * MUST run before any call to communication_hal_init()
 * ========================================================================= */
static bool test_ch_uart_send_not_initialized(void)
{
    uint8_t data[4] = {0x01U, 0x02U, 0x03U, 0x04U};
    error_t result = communication_hal_uart_send(data, 4U);
    TEST_ASSERT_EQUAL(ERROR_NOT_INITIALIZED, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-uart_receive_not_init  uart_receive — not initialized → ERROR_NOT_INITIALIZED
 * MUST run before any call to communication_hal_init()
 * ========================================================================= */
static bool test_ch_uart_receive_not_initialized(void)
{
    uint8_t data[16];
    uint16_t length;
    error_t result = communication_hal_uart_receive(data, &length);
    TEST_ASSERT_EQUAL(ERROR_NOT_INITIALIZED, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-001  init — success
 * ========================================================================= */
static bool test_ch_init_success(void)
{
    reset_hardware_mocks();
    error_t result = communication_hal_init();
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(1U, mock_get_can_init_calls());
    TEST_ASSERT_EQUAL(1U, mock_get_uart_init_calls());
    return true;
}

/* =========================================================================
 * TC-MOD008-009  can_send — transmit succeeds, tx_count updated
 * ========================================================================= */
static bool test_ch_can_send_success(void)
{
    can_message_t msg;
    msg.id  = 0x201U;
    msg.dlc = 4U;
    msg.data[0] = 0x01U;
    msg.data[1] = 0x02U;
    msg.data[2] = 0x03U;
    msg.data[3] = 0x04U;

    mock_can_transmit_result = ERROR_SUCCESS;
    error_t result = communication_hal_can_send(&msg);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-010  can_send — transmit fails, tx_error_count updated
 * ========================================================================= */
static bool test_ch_can_send_transmit_fails(void)
{
    can_message_t msg;
    msg.id  = 0x100U;
    msg.dlc = 2U;
    msg.data[0] = 0xAAU;
    msg.data[1] = 0xBBU;

    mock_can_transmit_result = ERROR_COMMUNICATION_FAILURE;
    error_t result = communication_hal_can_send(&msg);
    TEST_ASSERT_EQUAL(ERROR_COMMUNICATION_FAILURE, result);
    /* Restore */
    mock_can_transmit_result = ERROR_SUCCESS;
    return true;
}

/* =========================================================================
 * TC-MOD008-006  can_send — NULL msg → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_ch_can_send_null_msg(void)
{
    error_t result = communication_hal_can_send(NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-007  can_send — ID > 0x7FF → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_ch_can_send_id_too_large(void)
{
    can_message_t msg;
    msg.id  = 0x800U;
    msg.dlc = 1U;
    msg.data[0] = 0x00U;

    error_t result = communication_hal_can_send(&msg);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-008  can_send — DLC > 8 → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_ch_can_send_dlc_too_large(void)
{
    can_message_t msg;
    msg.id  = 0x100U;
    msg.dlc = 9U;

    error_t result = communication_hal_can_send(&msg);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-012  can_receive — NULL msg → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_ch_can_receive_null_msg(void)
{
    error_t result = communication_hal_can_receive(NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-013  can_receive — no data (can_is_rx_ready=false) → ERROR_NO_DATA
 * ========================================================================= */
static bool test_ch_can_receive_no_data(void)
{
    can_message_t msg;
    mock_can_is_rx_ready_value = false;
    error_t result = communication_hal_can_receive(&msg);
    TEST_ASSERT_EQUAL(ERROR_NO_DATA, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-014  can_receive — success, rx_count updated
 * ========================================================================= */
static bool test_ch_can_receive_success(void)
{
    can_message_t msg;
    mock_can_is_rx_ready_value = true;
    mock_can_receive_id  = 0x100U;
    mock_can_receive_dlc = 4U;
    mock_can_receive_data[0] = 0x11U;
    mock_can_receive_data[1] = 0x22U;
    mock_can_receive_data[2] = 0x33U;
    mock_can_receive_data[3] = 0x44U;
    mock_can_receive_result = ERROR_SUCCESS;

    error_t result = communication_hal_can_receive(&msg);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(0x100U, msg.id);
    TEST_ASSERT_EQUAL(4U, msg.dlc);
    return true;
}

/* =========================================================================
 * TC-MOD008-015  can_receive — invalid ID (> 0x7FF) → ERROR_INVALID_DATA
 * ========================================================================= */
static bool test_ch_can_receive_invalid_id(void)
{
    can_message_t msg;
    mock_can_is_rx_ready_value = true;
    mock_can_receive_id  = 0x800U;  /* > 0x7FF */
    mock_can_receive_dlc = 2U;
    mock_can_receive_result = ERROR_SUCCESS;

    error_t result = communication_hal_can_receive(&msg);
    TEST_ASSERT_EQUAL(ERROR_INVALID_DATA, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-016  can_receive — invalid DLC (> 8) → ERROR_INVALID_DATA
 * ========================================================================= */
static bool test_ch_can_receive_invalid_dlc(void)
{
    can_message_t msg;
    mock_can_is_rx_ready_value = true;
    mock_can_receive_id  = 0x100U;
    mock_can_receive_dlc = 9U;  /* > 8 */
    mock_can_receive_result = ERROR_SUCCESS;

    error_t result = communication_hal_can_receive(&msg);
    TEST_ASSERT_EQUAL(ERROR_INVALID_DATA, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-017  can_is_rx_ready — returns false
 * ========================================================================= */
static bool test_ch_can_is_rx_ready_false(void)
{
    mock_can_is_rx_ready_value = false;
    bool result = communication_hal_can_is_rx_ready();
    TEST_ASSERT_FALSE(result);
    return true;
}

/* =========================================================================
 * TC-MOD008-018  can_is_rx_ready — returns true
 * ========================================================================= */
static bool test_ch_can_is_rx_ready_true(void)
{
    mock_can_is_rx_ready_value = true;
    bool result = communication_hal_can_is_rx_ready();
    TEST_ASSERT_TRUE(result);
    return true;
}

/* =========================================================================
 * TC-MOD008-020  uart_send — NULL data → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_ch_uart_send_null_data(void)
{
    error_t result = communication_hal_uart_send(NULL, 10U);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-021  uart_send — zero length → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_ch_uart_send_zero_length(void)
{
    uint8_t data[4] = {0x01U, 0x02U, 0x03U, 0x04U};
    error_t result = communication_hal_uart_send(data, 0U);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-022  uart_send — success
 * ========================================================================= */
static bool test_ch_uart_send_success(void)
{
    uint8_t data[4] = {0x41U, 0x42U, 0x43U, 0x44U};
    error_t result = communication_hal_uart_send(data, 4U);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-024  uart_receive — NULL data → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_ch_uart_receive_null_data(void)
{
    uint16_t length;
    error_t result = communication_hal_uart_receive(NULL, &length);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-025  uart_receive — NULL length → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_ch_uart_receive_null_length(void)
{
    uint8_t data[16];
    error_t result = communication_hal_uart_receive(data, NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-026  uart_receive — no data (uart_is_rx_ready=false) → ERROR_NO_DATA
 * ========================================================================= */
static bool test_ch_uart_receive_no_data(void)
{
    uint8_t data[16];
    uint16_t length;
    mock_uart_is_rx_ready_value = false;
    error_t result = communication_hal_uart_receive(data, &length);
    TEST_ASSERT_EQUAL(ERROR_NO_DATA, result);
    return true;
}

/* =========================================================================
 * TC-MOD008-027  uart_receive — rx_ready=true, uart_receive returns success
 * ========================================================================= */
static bool test_ch_uart_receive_success(void)
{
    uint8_t data[16];
    uint16_t length = 0U;
    mock_uart_is_rx_ready_value = true;
    mock_uart_receive_result = ERROR_SUCCESS;

    error_t result = communication_hal_uart_receive(data, &length);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);

    mock_uart_receive_result = ERROR_NO_DATA;  /* Restore default */
    return true;
}

/* =========================================================================
 * TC-MOD008-002  init — CAN controller init fails → ERROR_HARDWARE_FAILURE
 * ========================================================================= */
static bool test_ch_init_can_controller_fails(void)
{
    reset_hardware_mocks();
    mock_can_controller_init_result = ERROR_HARDWARE_FAILURE;
    error_t result = communication_hal_init();
    TEST_ASSERT_EQUAL(ERROR_HARDWARE_FAILURE, result);
    mock_can_controller_init_result = ERROR_SUCCESS;
    return true;
}

/* =========================================================================
 * TC-MOD008-003  init — CAN filter config fails → ERROR_HARDWARE_FAILURE
 * ========================================================================= */
static bool test_ch_init_can_filter_fails(void)
{
    reset_hardware_mocks();
    mock_can_filter_config_result = ERROR_HARDWARE_FAILURE;
    error_t result = communication_hal_init();
    TEST_ASSERT_EQUAL(ERROR_HARDWARE_FAILURE, result);
    mock_can_filter_config_result = ERROR_SUCCESS;
    return true;
}

/* =========================================================================
 * TC-MOD008-004  init — UART init fails → ERROR_HARDWARE_FAILURE
 * ========================================================================= */
static bool test_ch_init_uart_fails(void)
{
    reset_hardware_mocks();
    mock_uart_init_result = ERROR_HARDWARE_FAILURE;
    error_t result = communication_hal_init();
    TEST_ASSERT_EQUAL(ERROR_HARDWARE_FAILURE, result);
    mock_uart_init_result = ERROR_SUCCESS;
    return true;
}

/* =========================================================================
 * TC-MOD008-can_receive_driver_error  can_receive — driver fails → error propagated
 * ========================================================================= */
static bool test_ch_can_receive_driver_error(void)
{
    can_message_t msg;
    mock_can_is_rx_ready_value = true;
    mock_can_receive_result = ERROR_COMMUNICATION_FAILURE;

    error_t result = communication_hal_can_receive(&msg);
    TEST_ASSERT_EQUAL(ERROR_COMMUNICATION_FAILURE, result);

    mock_can_receive_result = ERROR_SUCCESS;  /* Restore */
    return true;
}

/* =========================================================================
 * TC-MOD008-uart_send_driver_error  uart_send — uart_transmit returns error
 * Covers line 222 (err != ERROR_SUCCESS branch in uart_send)
 * ========================================================================= */
static bool test_ch_uart_send_driver_error(void)
{
    uint8_t data[2] = {0xA1U, 0xB2U};
    mock_uart_transmit_result = ERROR_COMMUNICATION_FAILURE;
    error_t result = communication_hal_uart_send(data, 2U);
    TEST_ASSERT_EQUAL(ERROR_COMMUNICATION_FAILURE, result);
    mock_uart_transmit_result = ERROR_SUCCESS;  /* Restore */
    return true;
}

/* =========================================================================
 * TC-MOD008-uart_receive_driver_error  uart_receive — driver returns error
 * ========================================================================= */
static bool test_ch_uart_receive_driver_error(void)
{
    uint8_t data[16];
    uint16_t length;
    mock_uart_is_rx_ready_value = true;
    mock_uart_receive_result = ERROR_COMMUNICATION_FAILURE;

    error_t result = communication_hal_uart_receive(data, &length);
    TEST_ASSERT_EQUAL(ERROR_COMMUNICATION_FAILURE, result);

    mock_uart_receive_result = ERROR_NO_DATA;  /* Restore */
    return true;
}

/* =========================================================================
 * Test suite runner
 * ========================================================================= */
void run_communication_hal_tests(void)
{
    const int NUM_TESTS = 32;
    test_suite_begin("MOD-008: communication_hal");

    /* Not-initialized tests — MUST run before communication_hal_init() */
    run_test("TC-MOD008-can_send_not_init: not initialized",         test_ch_can_send_not_initialized);
    run_test("TC-MOD008-can_receive_not_init: not initialized",      test_ch_can_receive_not_initialized);
    run_test("TC-MOD008-uart_send_not_init: not initialized",        test_ch_uart_send_not_initialized);
    run_test("TC-MOD008-uart_receive_not_init: not initialized",     test_ch_uart_receive_not_initialized);

    /* Init success (establishes initialized state for subsequent tests) */
    run_test("TC-MOD008-001: init success",                         test_ch_init_success);

    /* CAN send tests */
    run_test("TC-MOD008-009: can_send success, tx_count++",         test_ch_can_send_success);
    run_test("TC-MOD008-010: can_send transmit fails",              test_ch_can_send_transmit_fails);
    run_test("TC-MOD008-006: can_send NULL msg",                    test_ch_can_send_null_msg);
    run_test("TC-MOD008-007: can_send ID > 0x7FF",                  test_ch_can_send_id_too_large);
    run_test("TC-MOD008-008: can_send DLC > 8",                     test_ch_can_send_dlc_too_large);

    /* CAN receive tests */
    run_test("TC-MOD008-012: can_receive NULL msg",                 test_ch_can_receive_null_msg);
    run_test("TC-MOD008-013: can_receive no data",                  test_ch_can_receive_no_data);
    run_test("TC-MOD008-014: can_receive success",                  test_ch_can_receive_success);
    run_test("TC-MOD008-015: can_receive invalid ID",               test_ch_can_receive_invalid_id);
    run_test("TC-MOD008-016: can_receive invalid DLC",              test_ch_can_receive_invalid_dlc);
    run_test("TC-MOD008-can_receive_driver_error: driver error",    test_ch_can_receive_driver_error);

    /* CAN RX ready tests */
    run_test("TC-MOD008-017: can_is_rx_ready false",                test_ch_can_is_rx_ready_false);
    run_test("TC-MOD008-018: can_is_rx_ready true",                 test_ch_can_is_rx_ready_true);

    /* UART send tests */
    run_test("TC-MOD008-020: uart_send NULL data",                  test_ch_uart_send_null_data);
    run_test("TC-MOD008-021: uart_send zero length",                test_ch_uart_send_zero_length);
    run_test("TC-MOD008-022: uart_send success",                    test_ch_uart_send_success);
    run_test("TC-MOD008-uart_send_driver_error: driver error",      test_ch_uart_send_driver_error);

    /* UART receive tests */
    run_test("TC-MOD008-024: uart_receive NULL data",               test_ch_uart_receive_null_data);
    run_test("TC-MOD008-025: uart_receive NULL length",             test_ch_uart_receive_null_length);
    run_test("TC-MOD008-026: uart_receive no data",                 test_ch_uart_receive_no_data);
    run_test("TC-MOD008-027: uart_receive success",                 test_ch_uart_receive_success);
    run_test("TC-MOD008-uart_receive_driver_error: driver error",   test_ch_uart_receive_driver_error);

    /* Init failure paths */
    run_test("TC-MOD008-002: init CAN controller fails",            test_ch_init_can_controller_fails);
    run_test("TC-MOD008-003: init CAN filter config fails",         test_ch_init_can_filter_fails);
    run_test("TC-MOD008-004: init UART fails",                      test_ch_init_uart_fails);

    /* Ensure re-init after failures restores state */
    run_test("TC-MOD008-001b: re-init after failures",              test_ch_init_success);

    test_suite_end("MOD-008: communication_hal", NUM_TESTS);
}
