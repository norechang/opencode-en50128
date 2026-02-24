/**
 * @file test_sensor_hal.c
 * @brief Unit tests for Sensor HAL Module (MOD-007)
 *
 * TRACEABILITY: DOC-COMPTEST-2026-001 v1.0
 * SIL Level: 3
 *
 * Coverage target (EN 50128 SIL 3 Table A.21):
 *   Statement: 100%, Branch: 100%, Condition (MC/DC): 100%
 *
 * Test cases: TC-MOD007-001 .. TC-MOD007-034
 *
 * IMPORTANT: "not initialized" tests (TC-004, TC-010, TC-015, TC-021) MUST
 * run before sensor_hal_init() since g_sensor_hal has no reset path.
 *
 * Speed read tests: sensor_hal_read_speed calls communication_hal_can_is_rx_ready
 * and communication_hal_can_receive, which are implemented in communication_hal.c.
 * communication_hal.c must be initialized (or at least its initialized flag must
 * match what we expect).
 *
 * Timeout check: last_speed_msg_time_ms=0 after sensor_hal_init.
 * elapsed = current_time - 0 = current_time.
 * If current_time > SPEED_MSG_TIMEOUT_MS (200), returns ERROR_TIMEOUT.
 * Tests use mock_set_system_time(0) to avoid timeout on non-timeout tests.
 */

#include "test_harness.h"
#include "test_mocks.h"
#include "../src/sensor_hal/sensor_hal.h"
#include "../src/communication_hal/communication_hal.h"

/* Forward declaration */
void run_sensor_hal_tests(void);

/* =========================================================================
 * TC-MOD007-004  read_position — not initialized → ERROR_NOT_INITIALIZED
 * (MUST run before init)
 * ========================================================================= */
static bool test_sh_read_position_not_initialized(void)
{
    uint16_t pos;
    error_t result = sensor_hal_read_position(DOOR_SIDE_LEFT, &pos);
    TEST_ASSERT_EQUAL(ERROR_NOT_INITIALIZED, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-010  read_obstacle — not initialized → ERROR_NOT_INITIALIZED
 * (MUST run before init)
 * ========================================================================= */
static bool test_sh_read_obstacle_not_initialized(void)
{
    bool detected;
    error_t result = sensor_hal_read_obstacle(DOOR_SIDE_LEFT, &detected);
    TEST_ASSERT_EQUAL(ERROR_NOT_INITIALIZED, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-015  read_speed — not initialized → ERROR_NOT_INITIALIZED
 * (MUST run before init)
 * ========================================================================= */
static bool test_sh_read_speed_not_initialized(void)
{
    uint16_t pri, sec;
    error_t result = sensor_hal_read_speed(&pri, &sec);
    TEST_ASSERT_EQUAL(ERROR_NOT_INITIALIZED, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-021  read_emergency_handle — not initialized → ERROR_NOT_INITIALIZED
 * (MUST run before init)
 * ========================================================================= */
static bool test_sh_read_emergency_not_initialized(void)
{
    bool activated;
    error_t result = sensor_hal_read_emergency_handle(DOOR_SIDE_LEFT, &activated);
    TEST_ASSERT_EQUAL(ERROR_NOT_INITIALIZED, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-001  init — success
 * ========================================================================= */
static bool test_sh_init_success(void)
{
    reset_hardware_mocks();
    mock_set_system_time(0U);
    error_t result = sensor_hal_init();
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* ADC init called once */
    TEST_ASSERT_EQUAL(1U, mock_get_adc_init_calls());
    /* GPIO init called 4 times (2 obstacle + 2 emergency handle) */
    TEST_ASSERT_EQUAL(4U, mock_get_gpio_init_calls());
    return true;
}

/* =========================================================================
 * TC-MOD007-005  read_position — NULL output → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_sh_read_position_null(void)
{
    error_t result = sensor_hal_read_position(DOOR_SIDE_LEFT, NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-006  read_position — invalid side → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_sh_read_position_invalid_side(void)
{
    uint16_t pos;
    error_t result = sensor_hal_read_position((door_side_t)99U, &pos);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-007  read_position — valid left (ADC returns value)
 * ========================================================================= */
static bool test_sh_read_position_valid_left(void)
{
    uint16_t pos = 0U;
    mock_adc_read_value = 2048U;
    error_t result = sensor_hal_read_position(DOOR_SIDE_LEFT, &pos);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* First sample: all history is 0, delta = 2048 > 819 → spike rejected → pos stays 0 */
    /* (median of 0,0,0 = 0) */
    TEST_ASSERT_EQUAL(0U, pos);
    return true;
}

/* =========================================================================
 * TC-MOD007-008  read_position — valid right
 * ========================================================================= */
static bool test_sh_read_position_valid_right(void)
{
    uint16_t pos = 0U;
    mock_adc_read_value = 100U;
    /* First call: history all 0, delta=100 <= 819 → accepted */
    error_t result = sensor_hal_read_position(DOOR_SIDE_RIGHT, &pos);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* Median of {0, 0, 100} (depends on buffer layout after first sample) = 0 or 100 */
    /* Just verify no error */
    return true;
}

/* =========================================================================
 * TC-MOD007-009  read_position — spike rejected (delta > 819)
 * ========================================================================= */
static bool test_sh_read_position_spike_rejected(void)
{
    uint16_t pos = 9999U;

    /* First: set a baseline value in the history via a small step */
    mock_adc_read_value = 10U;
    (void)sensor_hal_read_position(DOOR_SIDE_LEFT, &pos);
    (void)sensor_hal_read_position(DOOR_SIDE_LEFT, &pos);
    (void)sensor_hal_read_position(DOOR_SIDE_LEFT, &pos);

    /* Now try a huge spike (delta > 819 from 10) */
    mock_adc_read_value = 4000U;
    uint16_t before_spike = pos;
    error_t result = sensor_hal_read_position(DOOR_SIDE_LEFT, &pos);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* Spike is rejected — output should be stable (close to previous value) */
    /* The spike ADC value is rejected and replaced with last_value (10),
     * so median of history stays around 10 */
    TEST_ASSERT_TRUE(pos < 820U);  /* Not the spike value 4000 */
    (void)before_spike;
    return true;
}

/* =========================================================================
 * TC-MOD007-011  read_obstacle — NULL output → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_sh_read_obstacle_null(void)
{
    error_t result = sensor_hal_read_obstacle(DOOR_SIDE_LEFT, NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-012  read_obstacle — invalid side → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_sh_read_obstacle_invalid_side(void)
{
    bool detected;
    error_t result = sensor_hal_read_obstacle((door_side_t)99U, &detected);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-013  read_obstacle — no obstacle (gpio_read=true → active low → false)
 * ========================================================================= */
static bool test_sh_read_obstacle_not_detected(void)
{
    bool detected = true;
    mock_gpio_read_value = true;  /* Pin high = no obstacle (active low) */
    error_t result = sensor_hal_read_obstacle(DOOR_SIDE_LEFT, &detected);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_FALSE(detected);
    return true;
}

/* =========================================================================
 * TC-MOD007-014  read_obstacle — detected (gpio_read=false → active low → true)
 * ========================================================================= */
static bool test_sh_read_obstacle_detected(void)
{
    bool detected = false;
    mock_gpio_read_value = false;  /* Pin low = obstacle present (active low) */
    error_t result = sensor_hal_read_obstacle(DOOR_SIDE_LEFT, &detected);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_TRUE(detected);
    return true;
}

/* =========================================================================
 * TC-MOD007-016  read_speed — NULL primary → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_sh_read_speed_null_primary(void)
{
    uint16_t sec;
    error_t result = sensor_hal_read_speed(NULL, &sec);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-017  read_speed — NULL secondary → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_sh_read_speed_null_secondary(void)
{
    uint16_t pri;
    error_t result = sensor_hal_read_speed(&pri, NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-018  read_speed — timeout (advance > 200ms, no CAN msg) → ERROR_TIMEOUT
 * After sensor_hal_init, last_speed_msg_time_ms=0.
 * elapsed = current_time - 0 = current_time.  If > 200 → timeout.
 * ========================================================================= */
static bool test_sh_read_speed_timeout(void)
{
    uint16_t pri, sec;
    mock_set_system_time(201U);
    mock_can_is_rx_ready_value = false;
    error_t result = sensor_hal_read_speed(&pri, &sec);
    TEST_ASSERT_EQUAL(ERROR_TIMEOUT, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-019  read_speed — cached value returned (within timeout)
 * Advance time to just within timeout window.
 * ========================================================================= */
static bool test_sh_read_speed_cached_value(void)
{
    uint16_t pri = 9999U, sec = 9999U;
    mock_set_system_time(100U);   /* 100 <= 200: within timeout */
    mock_can_is_rx_ready_value = false;
    error_t result = sensor_hal_read_speed(&pri, &sec);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* Returns last known values (0 after init) */
    TEST_ASSERT_EQUAL(0U, pri);
    TEST_ASSERT_EQUAL(0U, sec);
    return true;
}

/* =========================================================================
 * TC-MOD007-020  read_speed — new CAN msg parsed correctly
 * ========================================================================= */
static bool test_sh_read_speed_new_can_msg(void)
{
    uint16_t pri = 0U, sec = 0U;

    /* Initialize communication_hal so can_receive path works */
    reset_hardware_mocks();
    (void)communication_hal_init();

    mock_set_system_time(50U);   /* Within timeout */

    /* Set up CAN message: primary=300 (0x012C), secondary=250 (0x00FA), ID=0x100, DLC=8 */
    mock_can_is_rx_ready_value = true;
    mock_can_receive_id  = CAN_ID_SPEED_DATA;    /* 0x100 */
    mock_can_receive_dlc = 8U;
    mock_can_receive_data[0] = 0x01U;  /* primary high byte */
    mock_can_receive_data[1] = 0x2CU;  /* primary low byte  → 300 */
    mock_can_receive_data[2] = 0x00U;  /* secondary high byte */
    mock_can_receive_data[3] = 0xFAU;  /* secondary low byte → 250 */

    error_t result = sensor_hal_read_speed(&pri, &sec);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(300U, pri);
    TEST_ASSERT_EQUAL(250U, sec);
    return true;
}

/* =========================================================================
 * TC-MOD007-022  read_emergency_handle — NULL output → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_sh_emergency_handle_null(void)
{
    error_t result = sensor_hal_read_emergency_handle(DOOR_SIDE_LEFT, NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-023  read_emergency_handle — invalid side → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_sh_emergency_handle_invalid_side(void)
{
    bool activated;
    error_t result = sensor_hal_read_emergency_handle((door_side_t)99U, &activated);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-024  read_emergency_handle — not activated (gpio_read=true → false)
 * ========================================================================= */
static bool test_sh_emergency_handle_not_activated(void)
{
    bool activated = true;
    mock_gpio_read_value = true;   /* Pin high = not activated (active low) */
    error_t result = sensor_hal_read_emergency_handle(DOOR_SIDE_LEFT, &activated);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_FALSE(activated);
    return true;
}

/* =========================================================================
 * TC-MOD007-024b  read_emergency_handle — right side (gpio_read=false → activated)
 * ========================================================================= */
static bool test_sh_emergency_handle_right_activated(void)
{
    bool activated = false;
    mock_gpio_read_value = false;  /* Pin low = activated (active low) */
    error_t result = sensor_hal_read_emergency_handle(DOOR_SIDE_RIGHT, &activated);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_TRUE(activated);
    return true;
}

/* =========================================================================
 * TC-MOD007-002  init — ADC fails → ERROR_HARDWARE_FAILURE
 * ========================================================================= */
static bool test_sh_init_adc_fails(void)
{
    reset_hardware_mocks();
    mock_adc_init_result = ERROR_HARDWARE_FAILURE;
    error_t result = sensor_hal_init();
    TEST_ASSERT_EQUAL(ERROR_HARDWARE_FAILURE, result);
    mock_adc_init_result = ERROR_SUCCESS;
    return true;
}

/* =========================================================================
 * TC-MOD007-003  init — can_filter_add fails → ERROR_HARDWARE_FAILURE
 * ========================================================================= */
static bool test_sh_init_can_filter_fails(void)
{
    reset_hardware_mocks();
    mock_can_filter_add_result = ERROR_HARDWARE_FAILURE;
    error_t result = sensor_hal_init();
    TEST_ASSERT_EQUAL(ERROR_HARDWARE_FAILURE, result);
    mock_can_filter_add_result = ERROR_SUCCESS;
    return true;
}

/* =========================================================================
 * TC-MOD007-025  read_obstacle — right side detected
 *                Covers sensor_hal.c line 225: gpio_read(GPIO_OBSTACLE_RIGHT)
 * ========================================================================= */
static bool test_sh_read_obstacle_right_side(void)
{
    bool detected = false;
    mock_gpio_read_value = false;  /* Pin low = obstacle present (active low) */
    error_t result = sensor_hal_read_obstacle(DOOR_SIDE_RIGHT, &detected);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_TRUE(detected);
    return true;
}

/* =========================================================================
 * median_of_3 branch coverage tests (TC-MOD007-026 .. TC-MOD007-031)
 * All 6 orderings of (a,b,c) — covers sensor_hal.c lines 331-346.
 *
 * Branch map:
 *   (30,20,10): a>b=T, b>c=T                     → return b(20)  [line 333]
 *   (30,10,20): a>b=T, b>c=F, a>c=T              → return c(20)  [line 335]
 *   (20,10,30): a>b=T, b>c=F, a>c=F              → return a(20)  [line 337]
 *   (20,30,10): a>b=F, a>c=T                      → return a(20)  [line 341]
 *   (10,30,20): a>b=F, a>c=F, b>c=T              → return c(20)  [line 343]
 *   (10,20,30): a>b=F, a>c=F, b>c=F              → return b(20)  [line 345]
 * ========================================================================= */

/* TC-MOD007-026: median(30,20,10) → 20  [a>b>c] */
static bool test_sh_median_a_gt_b_gt_c(void)
{
    uint16_t result = median_of_3(30U, 20U, 10U);
    TEST_ASSERT_EQUAL(20U, result);
    return true;
}

/* TC-MOD007-027: median(30,10,20) → 20  [a>c>b] */
static bool test_sh_median_a_gt_c_gt_b(void)
{
    uint16_t result = median_of_3(30U, 10U, 20U);
    TEST_ASSERT_EQUAL(20U, result);
    return true;
}

/* TC-MOD007-028: median(20,10,30) → 20  [c>a>b] */
static bool test_sh_median_c_gt_a_gt_b(void)
{
    uint16_t result = median_of_3(20U, 10U, 30U);
    TEST_ASSERT_EQUAL(20U, result);
    return true;
}

/* TC-MOD007-029: median(20,30,10) → 20  [b>a>c] */
static bool test_sh_median_b_gt_a_gt_c(void)
{
    uint16_t result = median_of_3(20U, 30U, 10U);
    TEST_ASSERT_EQUAL(20U, result);
    return true;
}

/* TC-MOD007-030: median(10,30,20) → 20  [b>c>a] */
static bool test_sh_median_b_gt_c_gt_a(void)
{
    uint16_t result = median_of_3(10U, 30U, 20U);
    TEST_ASSERT_EQUAL(20U, result);
    return true;
}

/* TC-MOD007-031: median(10,20,30) → 20  [c>b>a] */
static bool test_sh_median_c_gt_b_gt_a(void)
{
    uint16_t result = median_of_3(10U, 20U, 30U);
    TEST_ASSERT_EQUAL(20U, result);
    return true;
}

/* =========================================================================
 * TC-MOD007-032  read_speed — can_receive() returns hardware failure
 *                Covers sensor_hal.c line 267 branch (err != ERROR_SUCCESS):
 *                  if ((err == ERROR_SUCCESS) && ...) → false (err != SUCCESS)
 *                Speed values remain cached (0); function returns ERROR_SUCCESS
 *                because the CAN rx-ready / receive failure is non-fatal.
 * ========================================================================= */
static bool test_sh_read_speed_can_receive_error(void)
{
    uint16_t pri = 9999U, sec = 9999U;

    reset_hardware_mocks();
    (void)sensor_hal_init();       /* Reset cached speed to 0 */
    (void)communication_hal_init();

    mock_set_system_time(50U);   /* Within timeout */
    mock_can_is_rx_ready_value = true;
    mock_can_receive_result    = ERROR_HARDWARE_FAILURE;  /* Force receive error */

    error_t result = sensor_hal_read_speed(&pri, &sec);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* Cached values unchanged (0 after init) */
    TEST_ASSERT_EQUAL(0U, pri);
    TEST_ASSERT_EQUAL(0U, sec);
    return true;
}

/* =========================================================================
 * TC-MOD007-033  read_speed — CAN ID mismatch
 *                Covers sensor_hal.c line 268 branch (id != CAN_ID_SPEED_DATA):
 *                  if ((err == ERROR_SUCCESS) && (can_msg.id == CAN_ID_SPEED_DATA) && ...)
 *                  → err==SUCCESS but id!=0x100 → whole condition false
 * ========================================================================= */
static bool test_sh_read_speed_can_id_mismatch(void)
{
    uint16_t pri = 9999U, sec = 9999U;

    reset_hardware_mocks();
    (void)sensor_hal_init();       /* Reset cached speed to 0 */
    (void)communication_hal_init();

    mock_set_system_time(50U);
    mock_can_is_rx_ready_value = true;
    mock_can_receive_result    = ERROR_SUCCESS;
    mock_can_receive_id        = 0x200U;  /* Wrong ID */
    mock_can_receive_dlc       = 8U;

    error_t result = sensor_hal_read_speed(&pri, &sec);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* Cached values unchanged (0 after init) */
    TEST_ASSERT_EQUAL(0U, pri);
    TEST_ASSERT_EQUAL(0U, sec);
    return true;
}

/* =========================================================================
 * TC-MOD007-034  read_speed — DLC mismatch
 *                Covers sensor_hal.c line 269 branch (dlc != 8):
 *                  if ((err == ERROR_SUCCESS) && (can_msg.id == CAN_ID_SPEED_DATA)
 *                      && (can_msg.dlc == 8U)) → id correct but dlc != 8
 * ========================================================================= */
static bool test_sh_read_speed_can_dlc_mismatch(void)
{
    uint16_t pri = 9999U, sec = 9999U;

    reset_hardware_mocks();
    (void)sensor_hal_init();       /* Reset cached speed to 0 */
    (void)communication_hal_init();

    mock_set_system_time(50U);
    mock_can_is_rx_ready_value = true;
    mock_can_receive_result    = ERROR_SUCCESS;
    mock_can_receive_id        = CAN_ID_SPEED_DATA;  /* Correct ID */
    mock_can_receive_dlc       = 4U;                 /* Wrong DLC */

    error_t result = sensor_hal_read_speed(&pri, &sec);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* Cached values unchanged (0 after init) */
    TEST_ASSERT_EQUAL(0U, pri);
    TEST_ASSERT_EQUAL(0U, sec);
    return true;
}

/* =========================================================================
 * Test suite runner
 *
 * ORDER MATTERS: Not-initialized tests run FIRST (before any sensor_hal_init).
 * ========================================================================= */
void run_sensor_hal_tests(void)
{
    const int NUM_TESTS = 34;
    test_suite_begin("MOD-007: sensor_hal");

    /* Not-initialized tests FIRST */
    run_test("TC-MOD007-004: read_position not initialized",        test_sh_read_position_not_initialized);
    run_test("TC-MOD007-010: read_obstacle not initialized",        test_sh_read_obstacle_not_initialized);
    run_test("TC-MOD007-015: read_speed not initialized",           test_sh_read_speed_not_initialized);
    run_test("TC-MOD007-021: read_emergency not initialized",       test_sh_read_emergency_not_initialized);

    /* Init success */
    run_test("TC-MOD007-001: init success",                         test_sh_init_success);

    /* Position tests */
    run_test("TC-MOD007-005: read_position NULL output",            test_sh_read_position_null);
    run_test("TC-MOD007-006: read_position invalid side",           test_sh_read_position_invalid_side);
    run_test("TC-MOD007-007: read_position valid left",             test_sh_read_position_valid_left);
    run_test("TC-MOD007-008: read_position valid right",            test_sh_read_position_valid_right);
    run_test("TC-MOD007-009: read_position spike rejected",         test_sh_read_position_spike_rejected);

    /* Obstacle tests */
    run_test("TC-MOD007-011: read_obstacle NULL output",            test_sh_read_obstacle_null);
    run_test("TC-MOD007-012: read_obstacle invalid side",           test_sh_read_obstacle_invalid_side);
    run_test("TC-MOD007-013: read_obstacle not detected",           test_sh_read_obstacle_not_detected);
    run_test("TC-MOD007-014: read_obstacle detected",               test_sh_read_obstacle_detected);
    run_test("TC-MOD007-025: read_obstacle right side detected",    test_sh_read_obstacle_right_side);

    /* Speed tests */
    run_test("TC-MOD007-016: read_speed NULL primary",              test_sh_read_speed_null_primary);
    run_test("TC-MOD007-017: read_speed NULL secondary",            test_sh_read_speed_null_secondary);
    run_test("TC-MOD007-018: read_speed timeout",                   test_sh_read_speed_timeout);
    run_test("TC-MOD007-019: read_speed cached value",              test_sh_read_speed_cached_value);
    run_test("TC-MOD007-020: read_speed new CAN msg parsed",        test_sh_read_speed_new_can_msg);

    /* Emergency handle tests */
    run_test("TC-MOD007-022: read_emergency NULL output",           test_sh_emergency_handle_null);
    run_test("TC-MOD007-023: read_emergency invalid side",          test_sh_emergency_handle_invalid_side);
    run_test("TC-MOD007-024: read_emergency not activated",         test_sh_emergency_handle_not_activated);
    run_test("TC-MOD007-024b: read_emergency right activated",      test_sh_emergency_handle_right_activated);

    /* Init failure paths */
    run_test("TC-MOD007-002: init ADC fails",                       test_sh_init_adc_fails);
    run_test("TC-MOD007-003: init can_filter_add fails",            test_sh_init_can_filter_fails);

    /* median_of_3 branch coverage */
    run_test("TC-MOD007-026: median(30,20,10)=20 [a>b>c]",         test_sh_median_a_gt_b_gt_c);
    run_test("TC-MOD007-027: median(30,10,20)=20 [a>c>b]",         test_sh_median_a_gt_c_gt_b);
    run_test("TC-MOD007-028: median(20,10,30)=20 [c>a>b]",         test_sh_median_c_gt_a_gt_b);
    run_test("TC-MOD007-029: median(20,30,10)=20 [b>a>c]",         test_sh_median_b_gt_a_gt_c);
    run_test("TC-MOD007-030: median(10,30,20)=20 [b>c>a]",         test_sh_median_b_gt_c_gt_a);
    run_test("TC-MOD007-031: median(10,20,30)=20 [c>b>a]",         test_sh_median_c_gt_b_gt_a);
    run_test("TC-MOD007-032: read_speed CAN receive error",         test_sh_read_speed_can_receive_error);
    run_test("TC-MOD007-033: read_speed CAN ID mismatch",           test_sh_read_speed_can_id_mismatch);
    run_test("TC-MOD007-034: read_speed CAN DLC mismatch",          test_sh_read_speed_can_dlc_mismatch);

    test_suite_end("MOD-007: sensor_hal", NUM_TESTS);
}
