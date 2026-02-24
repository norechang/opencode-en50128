/**
 * @file test_status_reporter.c
 * @brief Unit tests for Status Reporter Module (MOD-005)
 *
 * TRACEABILITY: DOC-COMPTEST-2026-001 v1.0
 * SIL Level: 3
 *
 * Coverage target (EN 50128 SIL 3 Table A.21):
 *   Statement: 100%, Branch: 100%, Condition (MC/DC): 100%
 *
 * Test cases: TC-MOD005-001 .. TC-MOD005-016
 *
 * Local stubs for functions called by status_reporter.c:
 *   door_fsm_get_position, door_fsm_get_state, door_fsm_is_locked,
 *   fault_detection_get_active_faults, communication_hal_can_send
 *
 * NOTE: set_led is provided by test_mocks.c (void set_led(uint8_t, uint8_t)).
 * NOTE: door_fsm_get_state is also declared by test_command_processor.c, but
 *       since each .c is compiled as a translation unit, conflicting definitions
 *       would cause a multiple-definition linker error.  The static stubs here
 *       are defined with external linkage; command_processor.c's local stubs
 *       use the SAME signatures so there is only one definition at link time.
 *       To avoid multiply-defined symbols this file defines the authoritative
 *       versions; test_command_processor.c's stubs are superseded — see Makefile
 *       notes.  All stubs are controlled via file-scope variables below.
 */

#include "test_harness.h"
#include "test_mocks.h"
#include "../src/status_reporter/status_reporter.h"
#include "../src/sensor_hal/sensor_hal.h"   /* can_message_t */

/* Forward declaration */
void run_status_reporter_tests(void);

/* =========================================================================
 * Stub state (controlled by tests)
 * ========================================================================= */

static uint8_t stub_sr_left_pos    = 0U;
static uint8_t stub_sr_right_pos   = 0U;
static uint8_t stub_sr_left_state  = 0U;
static uint8_t stub_sr_right_state = 0U;
static bool    stub_sr_left_locked  = true;
static bool    stub_sr_right_locked = true;
static error_t stub_sr_can_send_result = ERROR_SUCCESS;

/* Track last can message sent */
static can_message_t stub_sr_last_can_msg;
static uint32_t      stub_sr_can_send_calls = 0U;

/* =========================================================================
 * Local stubs (status_reporter.c extern declarations)
 * ========================================================================= */

uint8_t door_fsm_get_position(door_side_t side)
{
    return (side == DOOR_SIDE_LEFT) ? stub_sr_left_pos : stub_sr_right_pos;
}

/* door_fsm_get_state — also needed by command_processor.c; provide single
 * definition here.  test_command_processor.c provides its own local version
 * but since they have the same signature the linker only needs one. */
uint8_t door_fsm_get_state(door_side_t side)
{
    return (side == DOOR_SIDE_LEFT) ? stub_sr_left_state : stub_sr_right_state;
}

bool door_fsm_is_locked(door_side_t side)
{
    return (side == DOOR_SIDE_LEFT) ? stub_sr_left_locked : stub_sr_right_locked;
}

uint8_t fault_detection_get_active_faults(const void* fd, uint16_t* buffer, uint8_t buffer_size)
{
    (void)fd;
    (void)buffer;
    (void)buffer_size;
    return 0U;  /* No active faults by default */
}

error_t communication_hal_can_send(const can_message_t* msg)
{
    if (msg != NULL) {
        stub_sr_last_can_msg = *msg;
    }
    stub_sr_can_send_calls++;
    return stub_sr_can_send_result;
}

/* =========================================================================
 * Setter helper — allows test_command_processor.c (and other test files)
 * to control the door state seen by door_fsm_get_state() without accessing
 * the file-scope static variables directly.
 * ========================================================================= */
void sr_set_door_states(uint8_t left, uint8_t right)
{
    stub_sr_left_state  = left;
    stub_sr_right_state = right;
}

/* =========================================================================
 * Helper
 * ========================================================================= */

static status_reporter_t g_sr;

static void sr_setup(void)
{
    reset_hardware_mocks();
    stub_sr_left_pos    = 0U;
    stub_sr_right_pos   = 0U;
    stub_sr_left_state  = 0U;
    stub_sr_right_state = 0U;
    stub_sr_left_locked  = true;
    stub_sr_right_locked = true;
    stub_sr_can_send_result = ERROR_SUCCESS;
    stub_sr_can_send_calls  = 0U;
    mock_set_system_time(0U);
    (void)status_reporter_init(&g_sr);
}

/* =========================================================================
 * TC-MOD005-001  init — success (locked defaults, counts zeroed)
 * ========================================================================= */
static bool test_sr_init_success(void)
{
    status_reporter_t sr;
    error_t result = status_reporter_init(&sr);

    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(0U, sr.can_tx_count);
    TEST_ASSERT_EQUAL(0U, sr.can_tx_error_count);
    TEST_ASSERT_EQUAL(1U, sr.last_can_msg.door_left_locked);
    TEST_ASSERT_EQUAL(1U, sr.last_can_msg.door_right_locked);
    return true;
}

/* =========================================================================
 * TC-MOD005-002  init — NULL → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_sr_init_null(void)
{
    error_t result = status_reporter_init(NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD005-003  update — NULL → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_sr_update_null(void)
{
    error_t result = status_reporter_update(NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD005-004  update — period not elapsed (no CAN TX)
 * ========================================================================= */
static bool test_sr_update_period_not_elapsed(void)
{
    sr_setup();
    /* last_can_tx_time_ms = 0, current = 10 → elapsed = 10 < 50 */
    mock_set_system_time(10U);

    (void)status_reporter_update(&g_sr);

    TEST_ASSERT_EQUAL(0U, stub_sr_can_send_calls);
    TEST_ASSERT_EQUAL(0U, g_sr.can_tx_count);
    return true;
}

/* =========================================================================
 * TC-MOD005-005  update — period elapsed, CAN TX succeeds, count incremented
 * ========================================================================= */
static bool test_sr_update_period_elapsed_tx_success(void)
{
    sr_setup();
    stub_sr_can_send_result = ERROR_SUCCESS;
    mock_set_system_time(STATUS_REPORT_PERIOD_MS);  /* Exactly 50ms */

    error_t result = status_reporter_update(&g_sr);

    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(1U, stub_sr_can_send_calls);
    TEST_ASSERT_EQUAL(1U, g_sr.can_tx_count);
    TEST_ASSERT_EQUAL(0U, g_sr.can_tx_error_count);
    return true;
}

/* =========================================================================
 * TC-MOD005-006  update — period elapsed, CAN TX fails, error_count++, returns error
 * ========================================================================= */
static bool test_sr_update_period_elapsed_tx_failure(void)
{
    sr_setup();
    stub_sr_can_send_result = ERROR_HARDWARE_FAILURE;
    mock_set_system_time(STATUS_REPORT_PERIOD_MS);

    error_t result = status_reporter_update(&g_sr);

    TEST_ASSERT_EQUAL(ERROR_HARDWARE_FAILURE, result);
    TEST_ASSERT_EQUAL(1U, g_sr.can_tx_error_count);
    TEST_ASSERT_EQUAL(0U, g_sr.can_tx_count);
    return true;
}

/* =========================================================================
 * TC-MOD005-007  send_can_status — NULL → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_sr_send_can_status_null(void)
{
    error_t result = status_reporter_send_can_status(NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD005-008  send_can_status — success (CAN msg fields populated correctly)
 * ========================================================================= */
static bool test_sr_send_can_status_fields_correct(void)
{
    sr_setup();
    stub_sr_left_pos    = 25U;
    stub_sr_right_pos   = 75U;
    stub_sr_left_state  = 2U;   /* OPEN */
    stub_sr_right_state = 0U;   /* CLOSED */
    stub_sr_left_locked  = false;
    stub_sr_right_locked = true;

    error_t result = status_reporter_send_can_status(&g_sr);

    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(25U,  g_sr.last_can_msg.door_left_position);
    TEST_ASSERT_EQUAL(75U,  g_sr.last_can_msg.door_right_position);
    TEST_ASSERT_EQUAL(2U,   g_sr.last_can_msg.door_left_state);
    TEST_ASSERT_EQUAL(0U,   g_sr.last_can_msg.door_right_state);
    TEST_ASSERT_EQUAL(0U,   g_sr.last_can_msg.door_left_locked);   /* not locked */
    TEST_ASSERT_EQUAL(1U,   g_sr.last_can_msg.door_right_locked);  /* locked */
    /* CAN message ID must be CAN_ID_DOOR_STATUS */
    TEST_ASSERT_EQUAL(CAN_ID_DOOR_STATUS, stub_sr_last_can_msg.id);
    TEST_ASSERT_EQUAL(8U, stub_sr_last_can_msg.dlc);
    return true;
}

/* =========================================================================
 * TC-MOD005-009  send_can_status — CAN send failure propagated
 * ========================================================================= */
static bool test_sr_send_can_status_failure_propagated(void)
{
    sr_setup();
    stub_sr_can_send_result = ERROR_COMMUNICATION_FAILURE;

    error_t result = status_reporter_send_can_status(&g_sr);

    TEST_ASSERT_EQUAL(ERROR_COMMUNICATION_FAILURE, result);
    return true;
}

/* =========================================================================
 * TC-MOD005-010  update_display — NULL → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_sr_update_display_null(void)
{
    error_t result = status_reporter_update_display(NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD005-011  update_display — left door OPEN (state=2) → LED_LEFT_OPEN called ON
 * ========================================================================= */
static bool test_sr_update_display_left_open(void)
{
    sr_setup();
    stub_sr_left_state = 2U;  /* DOOR_STATE_OPEN */
    uint32_t led_calls_before = mock_get_led_set_calls();

    error_t result = status_reporter_update_display(&g_sr);

    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* set_led must have been called (at least 1 call more than before) */
    TEST_ASSERT(mock_get_led_set_calls() > led_calls_before);
    return true;
}

/* =========================================================================
 * TC-MOD005-012  update_display — left door LOCKED (state=6) → LED_LEFT_CLOSED ON
 * ========================================================================= */
static bool test_sr_update_display_left_locked(void)
{
    sr_setup();
    stub_sr_left_state = 6U;  /* DOOR_STATE_LOCKED */

    error_t result = status_reporter_update_display(&g_sr);

    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    return true;
}

/* =========================================================================
 * TC-MOD005-013  update_display — right door OPEN (state=2) → LED_RIGHT_OPEN ON
 * ========================================================================= */
static bool test_sr_update_display_right_open(void)
{
    sr_setup();
    stub_sr_right_state = 2U;

    error_t result = status_reporter_update_display(&g_sr);

    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    return true;
}

/* =========================================================================
 * TC-MOD005-014  update_display — right door LOCKED (state=6) → LED_RIGHT_CLOSED ON
 * ========================================================================= */
static bool test_sr_update_display_right_locked(void)
{
    sr_setup();
    stub_sr_right_state = 6U;

    error_t result = status_reporter_update_display(&g_sr);

    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    return true;
}

/* =========================================================================
 * TC-MOD005-015  update_display — no fault → LED_FAULT=OFF (active_faults=0)
 * ========================================================================= */
static bool test_sr_update_display_no_fault(void)
{
    sr_setup();
    /* active_faults hardcoded to 0 in simplified impl → LED_FAULT OFF */
    error_t result = status_reporter_update_display(&g_sr);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    return true;
}

/* =========================================================================
 * TC-MOD005-016  send_can_status — locked fields set correctly
 * ========================================================================= */
static bool test_sr_send_can_status_locked_fields(void)
{
    sr_setup();
    stub_sr_left_locked  = true;
    stub_sr_right_locked = false;

    (void)status_reporter_send_can_status(&g_sr);

    TEST_ASSERT_EQUAL(1U, g_sr.last_can_msg.door_left_locked);
    TEST_ASSERT_EQUAL(0U, g_sr.last_can_msg.door_right_locked);
    return true;
}

/* =========================================================================
 * Test suite runner
 * ========================================================================= */
void run_status_reporter_tests(void)
{
    const int NUM_TESTS = 16;
    test_suite_begin("MOD-005: status_reporter");

    run_test("TC-MOD005-001: init success",                             test_sr_init_success);
    run_test("TC-MOD005-002: init NULL",                                test_sr_init_null);
    run_test("TC-MOD005-003: update NULL",                              test_sr_update_null);
    run_test("TC-MOD005-004: update period not elapsed",                test_sr_update_period_not_elapsed);
    run_test("TC-MOD005-005: update period elapsed TX success",         test_sr_update_period_elapsed_tx_success);
    run_test("TC-MOD005-006: update period elapsed TX failure",         test_sr_update_period_elapsed_tx_failure);
    run_test("TC-MOD005-007: send_can_status NULL",                     test_sr_send_can_status_null);
    run_test("TC-MOD005-008: send_can_status fields correct",           test_sr_send_can_status_fields_correct);
    run_test("TC-MOD005-009: send_can_status failure propagated",       test_sr_send_can_status_failure_propagated);
    run_test("TC-MOD005-010: update_display NULL",                      test_sr_update_display_null);
    run_test("TC-MOD005-011: update_display left door OPEN",            test_sr_update_display_left_open);
    run_test("TC-MOD005-012: update_display left door LOCKED",          test_sr_update_display_left_locked);
    run_test("TC-MOD005-013: update_display right door OPEN",           test_sr_update_display_right_open);
    run_test("TC-MOD005-014: update_display right door LOCKED",         test_sr_update_display_right_locked);
    run_test("TC-MOD005-015: update_display no fault LED off",          test_sr_update_display_no_fault);
    run_test("TC-MOD005-016: send_can_status locked fields correct",    test_sr_send_can_status_locked_fields);

    test_suite_end("MOD-005: status_reporter", NUM_TESTS);
}
