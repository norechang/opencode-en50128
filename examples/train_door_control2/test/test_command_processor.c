/**
 * @file test_command_processor.c
 * @brief Unit tests for Command Processor Module (MOD-004)
 *
 * TRACEABILITY: DOC-COMPTEST-2026-001 v1.0
 * SIL Level: 3
 *
 * Coverage target (EN 50128 SIL 3 Table A.21):
 *   Statement: 100%, Branch: 100%, Condition (MC/DC): 100%
 *
 * Test cases: TC-MOD004-001 .. TC-MOD004-037
 *
 * Local stubs provided here to satisfy command_processor.c extern declarations
 * without pulling in the real door_fsm or fault_detection implementations.
 */

#include "test_harness.h"
#include "test_mocks.h"
#include "../src/command_processor/command_processor.h"

/* Forward declaration */
void run_command_processor_tests(void);

/* =========================================================================
 * Local stubs required by command_processor.c
 *   extern error_t door_fsm_process_event(void* fsm, door_event_t event);
 *   extern void    fault_detection_report_fault(uint16_t, uint8_t);
 *
 * NOTE: door_fsm_get_state is defined in test_status_reporter.c (single
 *       authoritative definition at link time). The stub state variables
 *       stub_sr_left_state/stub_sr_right_state in that file default to 0,
 *       which is sufficient for command_processor_update() EMERGENCY checks.
 * ========================================================================= */

error_t door_fsm_process_event(void* fsm, door_event_t event)
{
    (void)fsm;
    (void)event;
    return ERROR_SUCCESS;
}

void fault_detection_report_fault(uint16_t code, uint8_t severity)
{
    (void)code;
    (void)severity;
}

/* =========================================================================
 * CRC-8 helper (must match command_processor.c: XOR of 0xFF with each byte)
 * ========================================================================= */
static uint8_t compute_crc8(uint8_t byte)
{
    return (uint8_t)(0xFFU ^ byte);
}

/* =========================================================================
 * Helper
 * ========================================================================= */
static command_processor_t g_cp;

static void cp_setup(void)
{
    reset_hardware_mocks();
    mock_set_system_time(0U);
    (void)command_processor_init(&g_cp);
}

/* =========================================================================
 * TC-MOD004-001  init — success
 * ========================================================================= */
static bool test_cp_init_success(void)
{
    command_processor_t cp;
    mock_set_system_time(0U);
    error_t result = command_processor_init(&cp);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(MODE_NORMAL, cp.current_mode);
    TEST_ASSERT_FALSE(cp.can_cmd_timeout);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-002  init — NULL → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_cp_init_null(void)
{
    error_t result = command_processor_init(NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD004-003  update — NULL → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_cp_update_null(void)
{
    error_t result = command_processor_update(NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD004-004  update — no pending command (nothing dispatched)
 * ========================================================================= */
static bool test_cp_update_no_pending(void)
{
    cp_setup();
    error_t result = command_processor_update(&g_cp);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-005  update — pending left dispatched and cleared to NONE
 * ========================================================================= */
static bool test_cp_update_pending_left_dispatched(void)
{
    cp_setup();
    g_cp.pending_cmd_left = DOOR_EVENT_OPEN_CMD;

    (void)command_processor_update(&g_cp);

    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_left);
    return true;
}

/* =========================================================================
 * TC-MOD004-006  update — pending right dispatched and cleared to NONE
 * ========================================================================= */
static bool test_cp_update_pending_right_dispatched(void)
{
    cp_setup();
    g_cp.pending_cmd_right = DOOR_EVENT_CLOSE_CMD;

    (void)command_processor_update(&g_cp);

    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-007  update — CAN timeout triggers fault after > 1000 ms
 * ========================================================================= */
static bool test_cp_update_can_timeout_triggers_fault(void)
{
    cp_setup();
    /* Record a CAN command at time 0 */
    g_cp.last_can_cmd_time_ms = 1U;  /* Non-zero so timeout check runs */

    mock_set_system_time(CMD_PROC_CAN_TIMEOUT_MS + 2U);
    (void)command_processor_update(&g_cp);

    TEST_ASSERT_TRUE(g_cp.can_cmd_timeout);
    return true;
}

/* =========================================================================
 * TC-MOD004-008  update — MODE_EMERGENCY queues open commands for closed doors
 * ========================================================================= */
static bool test_cp_update_emergency_queues_open(void)
{
    cp_setup();
    g_cp.current_mode = MODE_EMERGENCY;
    /* stub_sr_left_state / stub_sr_right_state default to 0 (from test_status_reporter.c),
     * so door state != DOOR_STATE_OPEN (2). Emergency handler will queue open commands. */

    (void)command_processor_update(&g_cp);

    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-009  process_driver_command — NULL → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_cp_driver_cmd_null(void)
{
    error_t result = command_processor_process_driver_command(NULL, DRIVER_CMD_OPEN_LEFT);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD004-010  process_driver_command — invalid cmd (>= MAX) → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_cp_driver_cmd_invalid(void)
{
    cp_setup();
    error_t result = command_processor_process_driver_command(&g_cp, DRIVER_CMD_MAX);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD004-011  process_driver_command — diagnostic mode rejects → ERROR_INVALID_STATE
 * ========================================================================= */
static bool test_cp_driver_cmd_diagnostic_mode_rejects(void)
{
    cp_setup();
    g_cp.current_mode = MODE_DIAGNOSTIC;
    error_t result = command_processor_process_driver_command(&g_cp, DRIVER_CMD_OPEN_LEFT);
    TEST_ASSERT_EQUAL(ERROR_INVALID_STATE, result);
    return true;
}

/* =========================================================================
 * TC-MOD004-012  process_driver_command — OPEN_LEFT sets pending_cmd_left=OPEN
 * ========================================================================= */
static bool test_cp_driver_cmd_open_left(void)
{
    cp_setup();
    (void)command_processor_process_driver_command(&g_cp, DRIVER_CMD_OPEN_LEFT);
    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-013  process_driver_command — OPEN_RIGHT sets pending_cmd_right=OPEN
 * ========================================================================= */
static bool test_cp_driver_cmd_open_right(void)
{
    cp_setup();
    (void)command_processor_process_driver_command(&g_cp, DRIVER_CMD_OPEN_RIGHT);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-014  process_driver_command — OPEN_ALL sets both pending OPEN
 * ========================================================================= */
static bool test_cp_driver_cmd_open_all(void)
{
    cp_setup();
    (void)command_processor_process_driver_command(&g_cp, DRIVER_CMD_OPEN_ALL);
    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-015  process_driver_command — CLOSE_ALL sets both pending CLOSE
 * ========================================================================= */
static bool test_cp_driver_cmd_close_all(void)
{
    cp_setup();
    (void)command_processor_process_driver_command(&g_cp, DRIVER_CMD_CLOSE_ALL);
    TEST_ASSERT_EQUAL(DOOR_EVENT_CLOSE_CMD, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_CLOSE_CMD, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-016  process_driver_command — EMERGENCY_EVAC switches mode + queues open
 * ========================================================================= */
static bool test_cp_driver_cmd_emergency_evac(void)
{
    cp_setup();
    (void)command_processor_process_driver_command(&g_cp, DRIVER_CMD_EMERGENCY_EVAC);
    TEST_ASSERT_EQUAL(MODE_EMERGENCY, g_cp.current_mode);
    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-017  process_driver_command — NONE is no-op → ERROR_SUCCESS
 * ========================================================================= */
static bool test_cp_driver_cmd_none(void)
{
    cp_setup();
    error_t result = command_processor_process_driver_command(&g_cp, DRIVER_CMD_NONE);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-018  process_can_command — NULL cp → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_cp_can_cmd_null_cp(void)
{
    can_message_t msg = {CAN_ID_DOOR_COMMAND, 2U, {0x01U, 0x00U}};
    error_t result = command_processor_process_can_command(NULL, &msg);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD004-019  process_can_command — NULL msg → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_cp_can_cmd_null_msg(void)
{
    cp_setup();
    error_t result = command_processor_process_can_command(&g_cp, NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD004-020  process_can_command — wrong ID → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_cp_can_cmd_wrong_id(void)
{
    cp_setup();
    can_message_t msg;
    msg.id  = 0x100U;
    msg.dlc = 2U;
    msg.data[0] = 0x01U;
    msg.data[1] = compute_crc8(0x01U);

    error_t result = command_processor_process_can_command(&g_cp, &msg);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD004-021  process_can_command — wrong DLC → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_cp_can_cmd_wrong_dlc(void)
{
    cp_setup();
    can_message_t msg;
    msg.id  = CAN_ID_DOOR_COMMAND;
    msg.dlc = 1U;
    msg.data[0] = 0x01U;

    error_t result = command_processor_process_can_command(&g_cp, &msg);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD004-022  process_can_command — bad checksum → ERROR_COMMUNICATION_FAILURE
 * ========================================================================= */
static bool test_cp_can_cmd_bad_checksum(void)
{
    cp_setup();
    can_message_t msg;
    msg.id  = CAN_ID_DOOR_COMMAND;
    msg.dlc = 2U;
    msg.data[0] = 0x01U;
    msg.data[1] = 0x00U;  /* Wrong CRC */

    error_t result = command_processor_process_can_command(&g_cp, &msg);
    TEST_ASSERT_EQUAL(ERROR_COMMUNICATION_FAILURE, result);
    return true;
}

/* =========================================================================
 * TC-MOD004-023  process_can_command — valid OPEN_LEFT (0x01) → sets left pending
 * ========================================================================= */
static bool test_cp_can_cmd_valid_open_left(void)
{
    cp_setup();
    can_message_t msg;
    msg.id  = CAN_ID_DOOR_COMMAND;
    msg.dlc = 2U;
    msg.data[0] = 0x01U;
    msg.data[1] = compute_crc8(0x01U);

    error_t result = command_processor_process_can_command(&g_cp, &msg);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_left);
    return true;
}

/* =========================================================================
 * TC-MOD004-024  process_can_command — unknown cmd code → ERROR_INVALID_DATA
 * ========================================================================= */
static bool test_cp_can_cmd_unknown_code(void)
{
    cp_setup();
    can_message_t msg;
    msg.id  = CAN_ID_DOOR_COMMAND;
    msg.dlc = 2U;
    msg.data[0] = 0xFFU;  /* Unknown code */
    msg.data[1] = compute_crc8(0xFFU);

    error_t result = command_processor_process_can_command(&g_cp, &msg);
    TEST_ASSERT_EQUAL(ERROR_INVALID_DATA, result);
    return true;
}

/* =========================================================================
 * TC-MOD004-025  set_mode — success normal
 * ========================================================================= */
static bool test_cp_set_mode_normal(void)
{
    cp_setup();
    g_cp.current_mode = MODE_MANUAL;
    error_t result = command_processor_set_mode(&g_cp, MODE_NORMAL);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(MODE_NORMAL, g_cp.current_mode);
    return true;
}

/* =========================================================================
 * TC-MOD004-026  set_mode — EMERGENCY queues open commands
 * ========================================================================= */
static bool test_cp_set_mode_emergency_queues_open(void)
{
    cp_setup();
    error_t result = command_processor_set_mode(&g_cp, MODE_EMERGENCY);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(MODE_EMERGENCY, g_cp.current_mode);
    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-027  set_mode — invalid (>= MODE_MAX) → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_cp_set_mode_invalid(void)
{
    cp_setup();
    error_t result = command_processor_set_mode(&g_cp, MODE_MAX);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD004-028  set_mode — NULL → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_cp_set_mode_null(void)
{
    error_t result = command_processor_set_mode(NULL, MODE_NORMAL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD004-029  get_mode — success, returns current mode
 * ========================================================================= */
static bool test_cp_get_mode_success(void)
{
    cp_setup();
    g_cp.current_mode = MODE_MANUAL;
    operation_mode_t mode = command_processor_get_mode(&g_cp);
    TEST_ASSERT_EQUAL(MODE_MANUAL, mode);
    return true;
}

/* =========================================================================
 * TC-MOD004-030  get_mode — NULL → MODE_NORMAL (safe default)
 * ========================================================================= */
static bool test_cp_get_mode_null(void)
{
    operation_mode_t mode = command_processor_get_mode(NULL);
    TEST_ASSERT_EQUAL(MODE_NORMAL, mode);
    return true;
}

/* =========================================================================
 * TC-MOD004-031  process_driver_command — CLOSE_LEFT sets pending_cmd_left=CLOSE
 * Covers line 175-177 in command_processor.c
 * ========================================================================= */
static bool test_cp_driver_cmd_close_left(void)
{
    cp_setup();
    (void)command_processor_process_driver_command(&g_cp, DRIVER_CMD_CLOSE_LEFT);
    TEST_ASSERT_EQUAL(DOOR_EVENT_CLOSE_CMD, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-032  process_driver_command — CLOSE_RIGHT sets pending_cmd_right=CLOSE
 * Covers line 179-181 in command_processor.c
 * ========================================================================= */
static bool test_cp_driver_cmd_close_right(void)
{
    cp_setup();
    (void)command_processor_process_driver_command(&g_cp, DRIVER_CMD_CLOSE_RIGHT);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_CLOSE_CMD, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-033  update — MODE_DEGRADED: allow manual operation only (no-op)
 * Covers lines 122-124 in command_processor.c (MODE_DEGRADED case in update)
 * ========================================================================= */
static bool test_cp_update_mode_degraded(void)
{
    cp_setup();
    g_cp.current_mode = MODE_DEGRADED;
    error_t result = command_processor_update(&g_cp);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* Degraded mode has no special command queuing */
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-034  process_can_command — OPEN_RIGHT (0x02) → sets right pending
 * Covers line 245-247 in command_processor.c
 * ========================================================================= */
static bool test_cp_can_cmd_open_right(void)
{
    cp_setup();
    can_message_t msg;
    msg.id  = CAN_ID_DOOR_COMMAND;
    msg.dlc = 2U;
    msg.data[0] = 0x02U;
    msg.data[1] = compute_crc8(0x02U);
    error_t result = command_processor_process_can_command(&g_cp, &msg);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-035  process_can_command — OPEN_ALL (0x03) → sets both pending OPEN
 * Covers lines 249-252 in command_processor.c
 * ========================================================================= */
static bool test_cp_can_cmd_open_all(void)
{
    cp_setup();
    can_message_t msg;
    msg.id  = CAN_ID_DOOR_COMMAND;
    msg.dlc = 2U;
    msg.data[0] = 0x03U;
    msg.data[1] = compute_crc8(0x03U);
    error_t result = command_processor_process_can_command(&g_cp, &msg);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_OPEN_CMD, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-036  process_can_command — CLOSE_LEFT (0x11) → sets left pending CLOSE
 * Covers line 254-256 in command_processor.c
 * ========================================================================= */
static bool test_cp_can_cmd_close_left(void)
{
    cp_setup();
    can_message_t msg;
    msg.id  = CAN_ID_DOOR_COMMAND;
    msg.dlc = 2U;
    msg.data[0] = 0x11U;
    msg.data[1] = compute_crc8(0x11U);
    error_t result = command_processor_process_can_command(&g_cp, &msg);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(DOOR_EVENT_CLOSE_CMD, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-037  process_can_command — CLOSE_RIGHT (0x12) → sets right pending CLOSE
 * Covers line 258-260 in command_processor.c
 * ========================================================================= */
static bool test_cp_can_cmd_close_right(void)
{
    cp_setup();
    can_message_t msg;
    msg.id  = CAN_ID_DOOR_COMMAND;
    msg.dlc = 2U;
    msg.data[0] = 0x12U;
    msg.data[1] = compute_crc8(0x12U);
    error_t result = command_processor_process_can_command(&g_cp, &msg);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_CLOSE_CMD, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-038  process_can_command — CLOSE_ALL (0x13) → sets both pending CLOSE
 * Covers lines 262-265 in command_processor.c
 * ========================================================================= */
static bool test_cp_can_cmd_close_all_can(void)
{
    cp_setup();
    can_message_t msg;
    msg.id  = CAN_ID_DOOR_COMMAND;
    msg.dlc = 2U;
    msg.data[0] = 0x13U;
    msg.data[1] = compute_crc8(0x13U);
    error_t result = command_processor_process_can_command(&g_cp, &msg);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(DOOR_EVENT_CLOSE_CMD, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_CLOSE_CMD, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-039  set_mode — DEGRADED: mode set, no special init
 * Covers lines 307-309 in command_processor.c (MODE_DEGRADED case in set_mode)
 * ========================================================================= */
static bool test_cp_set_mode_degraded(void)
{
    cp_setup();
    error_t result = command_processor_set_mode(&g_cp, MODE_DEGRADED);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(MODE_DEGRADED, g_cp.current_mode);
    /* No commands queued in degraded mode */
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_right);
    return true;
}

/* =========================================================================
 * TC-MOD004-040  update — CAN timeout check: last_can_cmd_time_ms != 0 but
 *                age <= CMD_PROC_CAN_TIMEOUT_MS (branch false on line 92)
 *                Covers command_processor.c line 92 branch 1 (false):
 *                  if (can_cmd_age_ms > CMD_PROC_CAN_TIMEOUT_MS)  → NOT taken
 * ========================================================================= */
static bool test_cp_update_can_timeout_not_expired(void)
{
    cp_setup();
    /* Set a non-zero last CAN time so the outer if on line 90 is entered */
    g_cp.last_can_cmd_time_ms = 1U;
    /* Advance time to 500ms: age = 500 - 1 = 499 < 1000ms timeout */
    mock_set_system_time(500U);

    (void)command_processor_update(&g_cp);

    /* Timeout flag must NOT have been set */
    TEST_ASSERT_FALSE(g_cp.can_cmd_timeout);
    return true;
}

/* =========================================================================
 * TC-MOD004-041  update — MODE_EMERGENCY, both doors already OPEN
 *                Covers command_processor.c lines 114/117 branch 2 (false):
 *                  if (door_fsm_get_state(LEFT) != DOOR_STATE_OPEN) → NOT taken
 *                  if (door_fsm_get_state(RIGHT) != DOOR_STATE_OPEN) → NOT taken
 *
 * Uses sr_set_door_states() from test_status_reporter.c to make
 * door_fsm_get_state() return DOOR_STATE_OPEN (2) for both sides.
 * ========================================================================= */
extern void sr_set_door_states(uint8_t left, uint8_t right);

static bool test_cp_update_emergency_doors_already_open(void)
{
    cp_setup();
    g_cp.current_mode = MODE_EMERGENCY;
    /* Make both doors appear OPEN (state = 2 = DOOR_STATE_OPEN) */
    sr_set_door_states(2U, 2U);

    (void)command_processor_update(&g_cp);

    /* Neither pending_cmd should be set because doors are already OPEN */
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_left);
    TEST_ASSERT_EQUAL(DOOR_EVENT_NONE, g_cp.pending_cmd_right);

    /* Restore door states to CLOSED for other tests */
    sr_set_door_states(0U, 0U);
    return true;
}

/* =========================================================================
 * Test suite runner
 * ========================================================================= */
void run_command_processor_tests(void)
{
    const int NUM_TESTS = 41;
    test_suite_begin("MOD-004: command_processor");

    run_test("TC-MOD004-001: init success",                          test_cp_init_success);
    run_test("TC-MOD004-002: init NULL",                             test_cp_init_null);
    run_test("TC-MOD004-003: update NULL",                           test_cp_update_null);
    run_test("TC-MOD004-004: update no pending",                     test_cp_update_no_pending);
    run_test("TC-MOD004-005: update pending left dispatched",        test_cp_update_pending_left_dispatched);
    run_test("TC-MOD004-006: update pending right dispatched",       test_cp_update_pending_right_dispatched);
    run_test("TC-MOD004-007: update CAN timeout triggers fault",     test_cp_update_can_timeout_triggers_fault);
    run_test("TC-MOD004-008: update EMERGENCY queues open",          test_cp_update_emergency_queues_open);
    run_test("TC-MOD004-009: driver_cmd NULL cp",                    test_cp_driver_cmd_null);
    run_test("TC-MOD004-010: driver_cmd invalid",                    test_cp_driver_cmd_invalid);
    run_test("TC-MOD004-011: driver_cmd diagnostic rejects",         test_cp_driver_cmd_diagnostic_mode_rejects);
    run_test("TC-MOD004-012: driver_cmd OPEN_LEFT",                  test_cp_driver_cmd_open_left);
    run_test("TC-MOD004-013: driver_cmd OPEN_RIGHT",                 test_cp_driver_cmd_open_right);
    run_test("TC-MOD004-014: driver_cmd OPEN_ALL",                   test_cp_driver_cmd_open_all);
    run_test("TC-MOD004-015: driver_cmd CLOSE_ALL",                  test_cp_driver_cmd_close_all);
    run_test("TC-MOD004-016: driver_cmd EMERGENCY_EVAC",             test_cp_driver_cmd_emergency_evac);
    run_test("TC-MOD004-017: driver_cmd NONE no-op",                 test_cp_driver_cmd_none);
    run_test("TC-MOD004-018: can_cmd NULL cp",                       test_cp_can_cmd_null_cp);
    run_test("TC-MOD004-019: can_cmd NULL msg",                      test_cp_can_cmd_null_msg);
    run_test("TC-MOD004-020: can_cmd wrong ID",                      test_cp_can_cmd_wrong_id);
    run_test("TC-MOD004-021: can_cmd wrong DLC",                     test_cp_can_cmd_wrong_dlc);
    run_test("TC-MOD004-022: can_cmd bad checksum",                  test_cp_can_cmd_bad_checksum);
    run_test("TC-MOD004-023: can_cmd valid OPEN_LEFT",               test_cp_can_cmd_valid_open_left);
    run_test("TC-MOD004-024: can_cmd unknown code",                  test_cp_can_cmd_unknown_code);
    run_test("TC-MOD004-025: set_mode normal success",               test_cp_set_mode_normal);
    run_test("TC-MOD004-026: set_mode EMERGENCY queues open",        test_cp_set_mode_emergency_queues_open);
    run_test("TC-MOD004-027: set_mode invalid",                      test_cp_set_mode_invalid);
    run_test("TC-MOD004-028: set_mode NULL",                         test_cp_set_mode_null);
    run_test("TC-MOD004-029: get_mode success",                      test_cp_get_mode_success);
    run_test("TC-MOD004-030: get_mode NULL safe default",            test_cp_get_mode_null);
    run_test("TC-MOD004-031: driver_cmd CLOSE_LEFT",                 test_cp_driver_cmd_close_left);
    run_test("TC-MOD004-032: driver_cmd CLOSE_RIGHT",                test_cp_driver_cmd_close_right);
    run_test("TC-MOD004-033: update MODE_DEGRADED no-op",            test_cp_update_mode_degraded);
    run_test("TC-MOD004-034: can_cmd OPEN_RIGHT (0x02)",             test_cp_can_cmd_open_right);
    run_test("TC-MOD004-035: can_cmd OPEN_ALL (0x03)",               test_cp_can_cmd_open_all);
    run_test("TC-MOD004-036: can_cmd CLOSE_LEFT (0x11)",             test_cp_can_cmd_close_left);
    run_test("TC-MOD004-037: can_cmd CLOSE_RIGHT (0x12)",            test_cp_can_cmd_close_right);
    run_test("TC-MOD004-038: can_cmd CLOSE_ALL (0x13)",              test_cp_can_cmd_close_all_can);
    run_test("TC-MOD004-039: set_mode DEGRADED",                     test_cp_set_mode_degraded);
    run_test("TC-MOD004-040: update CAN timeout not expired",        test_cp_update_can_timeout_not_expired);
    run_test("TC-MOD004-041: update EMERGENCY doors already open",   test_cp_update_emergency_doors_already_open);

    test_suite_end("MOD-004: command_processor", NUM_TESTS);
}
