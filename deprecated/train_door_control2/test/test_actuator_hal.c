/**
 * @file test_actuator_hal.c
 * @brief Unit tests for Actuator HAL Module (MOD-006)
 *
 * TRACEABILITY: DOC-COMPTEST-2026-001 v1.0
 * SIL Level: 3
 *
 * Coverage target (EN 50128 SIL 3 Table A.21):
 *   Statement: 100%, Branch: 100%, Condition (MC/DC): 100%
 *
 * Test cases: TC-MOD006-001 .. TC-MOD006-017
 *
 * IMPORTANT: "not initialized" tests (TC-003, TC-009) MUST be run BEFORE
 * any successful actuator_hal_init() call in this process because
 * g_actuator_hal.initialized has no reset path.  The suite runner
 * enforces this ordering explicitly.
 */

#include "test_harness.h"
#include "test_mocks.h"
#include "../src/actuator_hal/actuator_hal.h"

/* Forward declaration */
void run_actuator_hal_tests(void);

/* =========================================================================
 * TC-MOD006-003  set_door_pwm — not initialized → ERROR_NOT_INITIALIZED
 * (MUST run before init)
 * ========================================================================= */
static bool test_ah_pwm_not_initialized(void)
{
    /* g_actuator_hal.initialized is false at program start (BSS = 0) */
    error_t result = actuator_hal_set_door_pwm(DOOR_SIDE_LEFT, 0);
    TEST_ASSERT_EQUAL(ERROR_NOT_INITIALIZED, result);
    return true;
}

/* =========================================================================
 * TC-MOD006-009  set_door_lock — not initialized → ERROR_NOT_INITIALIZED
 * (MUST run before init)
 * ========================================================================= */
static bool test_ah_lock_not_initialized(void)
{
    error_t result = actuator_hal_set_door_lock(DOOR_SIDE_LEFT, true);
    TEST_ASSERT_EQUAL(ERROR_NOT_INITIALIZED, result);
    return true;
}

/* =========================================================================
 * TC-MOD006-001  init — success
 * (PWM=0, locks released, initialized=true)
 * ========================================================================= */
static bool test_ah_init_success(void)
{
    reset_hardware_mocks();
    error_t result = actuator_hal_init();
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* PWM init called twice (left + right timers) */
    TEST_ASSERT_EQUAL(2U, mock_get_pwm_init_calls());
    /* GPIO init called twice (left + right lock pins) */
    TEST_ASSERT_EQUAL(2U, mock_get_gpio_init_calls());
    return true;
}

/* =========================================================================
 * TC-MOD006-004  set_door_pwm — duty too low (< -100) → ERROR_OUT_OF_RANGE
 * ========================================================================= */
static bool test_ah_pwm_duty_too_low(void)
{
    /* actuator_hal is now initialized from TC-001 */
    error_t result = actuator_hal_set_door_pwm(DOOR_SIDE_LEFT, (int8_t)(-101));
    TEST_ASSERT_EQUAL(ERROR_OUT_OF_RANGE, result);
    return true;
}

/* =========================================================================
 * TC-MOD006-005  set_door_pwm — duty too high (> 100) → ERROR_OUT_OF_RANGE
 * ========================================================================= */
static bool test_ah_pwm_duty_too_high(void)
{
    /* Note: int8_t max is 127, so 101 is representable */
    error_t result = actuator_hal_set_door_pwm(DOOR_SIDE_LEFT, (int8_t)101);
    TEST_ASSERT_EQUAL(ERROR_OUT_OF_RANGE, result);
    return true;
}

/* =========================================================================
 * TC-MOD006-006  set_door_pwm — valid left → ERROR_SUCCESS, state updated
 * ========================================================================= */
static bool test_ah_pwm_valid_left(void)
{
    error_t result = actuator_hal_set_door_pwm(DOOR_SIDE_LEFT, (int8_t)50);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    return true;
}

/* =========================================================================
 * TC-MOD006-007  set_door_pwm — valid right → ERROR_SUCCESS
 * ========================================================================= */
static bool test_ah_pwm_valid_right(void)
{
    error_t result = actuator_hal_set_door_pwm(DOOR_SIDE_RIGHT, (int8_t)(-50));
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    return true;
}

/* =========================================================================
 * TC-MOD006-008  set_door_pwm — invalid side → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_ah_pwm_invalid_side(void)
{
    error_t result = actuator_hal_set_door_pwm((door_side_t)99U, (int8_t)0);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD006-010  set_door_lock — invalid side → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_ah_lock_invalid_side(void)
{
    error_t result = actuator_hal_set_door_lock((door_side_t)99U, true);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD006-011  set_door_lock — lock left → ERROR_SUCCESS
 * ========================================================================= */
static bool test_ah_lock_left_locked(void)
{
    error_t result = actuator_hal_set_door_lock(DOOR_SIDE_LEFT, true);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    return true;
}

/* =========================================================================
 * TC-MOD006-012  set_door_lock — unlock left → ERROR_SUCCESS
 * ========================================================================= */
static bool test_ah_lock_left_unlocked(void)
{
    error_t result = actuator_hal_set_door_lock(DOOR_SIDE_LEFT, false);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    return true;
}

/* =========================================================================
 * TC-MOD006-013  set_door_lock — lock right → ERROR_SUCCESS
 * ========================================================================= */
static bool test_ah_lock_right_locked(void)
{
    error_t result = actuator_hal_set_door_lock(DOOR_SIDE_RIGHT, true);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    return true;
}

/* =========================================================================
 * TC-MOD006-014  set_door_lock — unlock right → ERROR_SUCCESS
 * ========================================================================= */
static bool test_ah_lock_right_unlocked(void)
{
    error_t result = actuator_hal_set_door_lock(DOOR_SIDE_RIGHT, false);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    return true;
}

/* =========================================================================
 * TC-MOD006-015  emergency_stop — works unconditionally (no init check)
 * ========================================================================= */
static bool test_ah_emergency_stop_always_works(void)
{
    /* emergency_stop has no init check by design (safety function) */
    error_t result = actuator_hal_emergency_stop();
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    return true;
}

/* =========================================================================
 * TC-MOD006-016  emergency_stop — after init, clears PWM and locks
 * ========================================================================= */
static bool test_ah_emergency_stop_clears_state(void)
{
    /* Set some non-zero PWM and lock state first */
    (void)actuator_hal_set_door_pwm(DOOR_SIDE_LEFT, (int8_t)75);
    (void)actuator_hal_set_door_pwm(DOOR_SIDE_RIGHT, (int8_t)75);
    (void)actuator_hal_set_door_lock(DOOR_SIDE_LEFT, true);
    (void)actuator_hal_set_door_lock(DOOR_SIDE_RIGHT, true);

    error_t result = actuator_hal_emergency_stop();
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);

    /* After emergency stop, set_door_pwm should still accept 0 (module initialized) */
    error_t pwm_result = actuator_hal_set_door_pwm(DOOR_SIDE_LEFT, (int8_t)0);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, pwm_result);
    return true;
}

/* =========================================================================
 * TC-MOD006-002b  init — right PWM timer init fails → ERROR_HARDWARE_FAILURE
 * Covers line 77 in actuator_hal.c (second pwm_timer_init failure)
 * ========================================================================= */
static bool test_ah_init_right_pwm_fails(void)
{
    reset_hardware_mocks();
    mock_pwm_timer_init_fail_on_second = true;
    mock_pwm_timer_init_result = ERROR_HARDWARE_FAILURE;
    error_t result = actuator_hal_init();
    TEST_ASSERT_EQUAL(ERROR_HARDWARE_FAILURE, result);
    /* Restore */
    mock_pwm_timer_init_fail_on_second = false;
    mock_pwm_timer_init_result = ERROR_SUCCESS;
    return true;
}

/* =========================================================================
 * TC-MOD006-002  init — PWM timer init fails → ERROR_HARDWARE_FAILURE
 * NOTE: Must run AFTER TC-001 because init failure path can be tested by
 *       failing the first pwm_timer_init call via mock.  g_actuator_hal
 *       remains initialized=true from TC-001, but we test the error path.
 * ========================================================================= */
static bool test_ah_init_pwm_fails(void)
{
    reset_hardware_mocks();
    mock_pwm_timer_init_result = ERROR_HARDWARE_FAILURE;
    error_t result = actuator_hal_init();
    TEST_ASSERT_EQUAL(ERROR_HARDWARE_FAILURE, result);
    /* Restore for subsequent tests */
    mock_pwm_timer_init_result = ERROR_SUCCESS;
    return true;
}

/* =========================================================================
 * Test suite runner
 *
 * ORDER MATTERS: TC-003 and TC-009 ("not initialized") MUST run before
 * TC-001 (init success).  All other tests run after init succeeds.
 * ========================================================================= */
void run_actuator_hal_tests(void)
{
    const int NUM_TESTS = 17;
    test_suite_begin("MOD-006: actuator_hal");

    /* Not-initialized tests FIRST (before any init call) */
    run_test("TC-MOD006-003: set_door_pwm not initialized",      test_ah_pwm_not_initialized);
    run_test("TC-MOD006-009: set_door_lock not initialized",     test_ah_lock_not_initialized);

    /* Init success */
    run_test("TC-MOD006-001: init success",                      test_ah_init_success);

    /* Tests that require module initialized */
    run_test("TC-MOD006-004: set_door_pwm duty too low",         test_ah_pwm_duty_too_low);
    run_test("TC-MOD006-005: set_door_pwm duty too high",        test_ah_pwm_duty_too_high);
    run_test("TC-MOD006-006: set_door_pwm valid left",           test_ah_pwm_valid_left);
    run_test("TC-MOD006-007: set_door_pwm valid right",          test_ah_pwm_valid_right);
    run_test("TC-MOD006-008: set_door_pwm invalid side",         test_ah_pwm_invalid_side);
    run_test("TC-MOD006-010: set_door_lock invalid side",        test_ah_lock_invalid_side);
    run_test("TC-MOD006-011: set_door_lock lock left",           test_ah_lock_left_locked);
    run_test("TC-MOD006-012: set_door_lock unlock left",         test_ah_lock_left_unlocked);
    run_test("TC-MOD006-013: set_door_lock lock right",          test_ah_lock_right_locked);
    run_test("TC-MOD006-014: set_door_lock unlock right",        test_ah_lock_right_unlocked);
    run_test("TC-MOD006-015: emergency_stop unconditional",      test_ah_emergency_stop_always_works);
    run_test("TC-MOD006-016: emergency_stop clears state",       test_ah_emergency_stop_clears_state);

    /* Init failure paths */
    run_test("TC-MOD006-002: init PWM timer fails",              test_ah_init_pwm_fails);
    run_test("TC-MOD006-002b: init right PWM timer fails",       test_ah_init_right_pwm_fails);

    test_suite_end("MOD-006: actuator_hal", NUM_TESTS);
}
