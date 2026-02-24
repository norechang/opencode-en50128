/**
 * @file test_fault_detection.c
 * @brief Unit tests for Fault Detection and Diagnosis Module (MOD-003)
 *
 * TRACEABILITY: DOC-COMPTEST-2026-001 v1.0
 * SIL Level: 3
 *
 * Coverage target (EN 50128 SIL 3 Table A.21):
 *   Statement: 100%, Branch: 100%, Condition (MC/DC): 100%
 *
 * Test cases: TC-MOD003-001 .. TC-MOD003-031
 */

#include "test_harness.h"
#include "test_mocks.h"
#include "../src/fault_detection/fault_detection.h"

/* Forward declaration */
void run_fault_detection_tests(void);

/* =========================================================================
 * Helper: initialised instance
 * ========================================================================= */
static fault_detection_t g_fd;

static void fd_setup(void)
{
    reset_hardware_mocks();
    (void)fault_detection_init(&g_fd);
}

/* =========================================================================
 * TC-MOD003-001  init — success
 * ========================================================================= */
static bool test_fault_detection_init_success(void)
{
    fault_detection_t fd;
    error_t result;

    result = fault_detection_init(&fd);

    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_FALSE(fd.critical_fault_active);
    TEST_ASSERT_EQUAL(0U, fd.fault_log_count);
    TEST_ASSERT_EQUAL(0U, fd.fault_log_head);
    return true;
}

/* =========================================================================
 * TC-MOD003-002  init — NULL → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_fault_detection_init_null(void)
{
    error_t result = fault_detection_init(NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD003-003  update — NULL → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_fault_detection_update_null(void)
{
    error_t result = fault_detection_update(NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD003-004  update — minor fault ages out after > 10 000 ms
 * ========================================================================= */
static bool test_fault_detection_update_fault_ages_out(void)
{
    error_t result;

    fd_setup();

    /* Report a minor fault at time 0 */
    mock_set_system_time(0U);
    result = fault_detection_report_fault(&g_fd, FAULT_CAN_TIMEOUT, FAULT_SEVERITY_MINOR);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(1U, g_fd.fault_log_count);

    /* Advance beyond the age-out window */
    mock_set_system_time(FAULT_AGE_TIMEOUT_MS + 1U);

    result = fault_detection_update(&g_fd);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(0U, g_fd.fault_log_count);
    return true;
}

/* =========================================================================
 * TC-MOD003-005  update — critical fault aged out → critical_fault_active=false
 * ========================================================================= */
static bool test_fault_detection_update_critical_cleared_by_aging(void)
{
    fd_setup();
    mock_set_system_time(0U);

    (void)fault_detection_report_fault(&g_fd, FAULT_WATCHDOG_TIMEOUT, FAULT_SEVERITY_CRITICAL);
    TEST_ASSERT_TRUE(g_fd.critical_fault_active);

    /* Advance beyond age-out */
    mock_set_system_time(FAULT_AGE_TIMEOUT_MS + 1U);
    (void)fault_detection_update(&g_fd);

    TEST_ASSERT_FALSE(g_fd.critical_fault_active);
    return true;
}

/* =========================================================================
 * TC-MOD003-006  report_fault — success, count becomes 1
 * ========================================================================= */
static bool test_fault_detection_report_fault_success(void)
{
    fd_setup();
    mock_set_system_time(100U);

    error_t result = fault_detection_report_fault(&g_fd, FAULT_CAN_TIMEOUT, FAULT_SEVERITY_MINOR);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(1U, g_fd.fault_log_count);
    TEST_ASSERT_EQUAL(FAULT_CAN_TIMEOUT, g_fd.fault_log[0].code);
    TEST_ASSERT_EQUAL(100U, g_fd.fault_log[0].timestamp);
    return true;
}

/* =========================================================================
 * TC-MOD003-007  report_fault — NULL → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_fault_detection_report_fault_null(void)
{
    error_t result = fault_detection_report_fault(NULL, FAULT_CAN_TIMEOUT, FAULT_SEVERITY_MINOR);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD003-008  report_fault — invalid severity (>= MAX) → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_fault_detection_report_fault_invalid_severity(void)
{
    fault_detection_t fd;
    error_t result;

    (void)fault_detection_init(&fd);
    result = fault_detection_report_fault(&fd, FAULT_CAN_TIMEOUT, FAULT_SEVERITY_MAX);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD003-009  report_fault — duplicate refreshes timestamp, count stays 1
 * ========================================================================= */
static bool test_fault_detection_report_fault_duplicate_refresh(void)
{
    fd_setup();

    mock_set_system_time(100U);
    (void)fault_detection_report_fault(&g_fd, FAULT_CAN_TIMEOUT, FAULT_SEVERITY_MINOR);
    TEST_ASSERT_EQUAL(1U, g_fd.fault_log_count);

    /* Report same fault again at later time */
    mock_set_system_time(500U);
    (void)fault_detection_report_fault(&g_fd, FAULT_CAN_TIMEOUT, FAULT_SEVERITY_MINOR);

    /* Count must remain 1, timestamp updated */
    TEST_ASSERT_EQUAL(1U, g_fd.fault_log_count);
    TEST_ASSERT_EQUAL(500U, g_fd.fault_log[0].timestamp);
    return true;
}

/* =========================================================================
 * TC-MOD003-010  report_fault — critical severity → critical_fault_active=true
 * ========================================================================= */
static bool test_fault_detection_report_fault_critical_sets_flag(void)
{
    fd_setup();
    TEST_ASSERT_FALSE(g_fd.critical_fault_active);

    (void)fault_detection_report_fault(&g_fd, FAULT_WATCHDOG_TIMEOUT, FAULT_SEVERITY_CRITICAL);

    TEST_ASSERT_TRUE(g_fd.critical_fault_active);
    return true;
}

/* =========================================================================
 * TC-MOD003-011  report_fault — log full (32 faults), count saturates at 32
 * ========================================================================= */
static bool test_fault_detection_report_fault_log_full(void)
{
    fault_detection_t fd;
    uint8_t i;

    (void)fault_detection_init(&fd);

    /* Fill the log with 32 unique fault codes */
    for (i = 0U; i < FAULT_LOG_SIZE; i++) {
        error_t err = fault_detection_report_fault(&fd, (fault_code_t)(0x0100U + i), FAULT_SEVERITY_MINOR);
        TEST_ASSERT_EQUAL(ERROR_SUCCESS, err);
    }
    TEST_ASSERT_EQUAL(FAULT_LOG_SIZE, fd.fault_log_count);

    /* One more — count must not exceed FAULT_LOG_SIZE */
    (void)fault_detection_report_fault(&fd, 0x0200U, FAULT_SEVERITY_MINOR);
    TEST_ASSERT_EQUAL(FAULT_LOG_SIZE, fd.fault_log_count);
    return true;
}

/* =========================================================================
 * TC-MOD003-012  is_critical_fault_active — false initially
 * ========================================================================= */
static bool test_fault_detection_is_critical_false_initially(void)
{
    fault_detection_t fd;
    (void)fault_detection_init(&fd);
    TEST_ASSERT_FALSE(fault_detection_is_critical_fault_active(&fd));
    return true;
}

/* =========================================================================
 * TC-MOD003-013  is_critical_fault_active — true after critical fault
 * ========================================================================= */
static bool test_fault_detection_is_critical_true_after_critical(void)
{
    fault_detection_t fd;
    (void)fault_detection_init(&fd);
    (void)fault_detection_report_fault(&fd, FAULT_WATCHDOG_TIMEOUT, FAULT_SEVERITY_CRITICAL);
    TEST_ASSERT_TRUE(fault_detection_is_critical_fault_active(&fd));
    return true;
}

/* =========================================================================
 * TC-MOD003-014  is_critical_fault_active — NULL → true (fail-safe)
 * ========================================================================= */
static bool test_fault_detection_is_critical_null_fail_safe(void)
{
    TEST_ASSERT_TRUE(fault_detection_is_critical_fault_active(NULL));
    return true;
}

/* =========================================================================
 * TC-MOD003-015  get_active_faults — success, returns 1 fault
 * ========================================================================= */
static bool test_fault_detection_get_active_faults_success(void)
{
    fault_detection_t fd;
    fault_code_t buf[4];
    uint8_t count;

    (void)fault_detection_init(&fd);
    (void)fault_detection_report_fault(&fd, FAULT_CAN_TIMEOUT, FAULT_SEVERITY_MINOR);

    count = fault_detection_get_active_faults(&fd, buf, 4U);

    TEST_ASSERT_EQUAL(1U, count);
    TEST_ASSERT_EQUAL(FAULT_CAN_TIMEOUT, buf[0]);
    return true;
}

/* =========================================================================
 * TC-MOD003-016  get_active_faults — NULL fd → returns 0
 * ========================================================================= */
static bool test_fault_detection_get_active_faults_null_fd(void)
{
    fault_code_t buf[4];
    uint8_t count = fault_detection_get_active_faults(NULL, buf, 4U);
    TEST_ASSERT_EQUAL(0U, count);
    return true;
}

/* =========================================================================
 * TC-MOD003-017  get_active_faults — NULL buffer → returns 0
 * ========================================================================= */
static bool test_fault_detection_get_active_faults_null_buffer(void)
{
    fault_detection_t fd;
    (void)fault_detection_init(&fd);
    uint8_t count = fault_detection_get_active_faults(&fd, NULL, 4U);
    TEST_ASSERT_EQUAL(0U, count);
    return true;
}

/* =========================================================================
 * TC-MOD003-018  get_active_faults — zero buffer_size → returns 0
 * ========================================================================= */
static bool test_fault_detection_get_active_faults_zero_size(void)
{
    fault_detection_t fd;
    fault_code_t buf[4];
    (void)fault_detection_init(&fd);
    (void)fault_detection_report_fault(&fd, FAULT_CAN_TIMEOUT, FAULT_SEVERITY_MINOR);

    uint8_t count = fault_detection_get_active_faults(&fd, buf, 0U);
    TEST_ASSERT_EQUAL(0U, count);
    return true;
}

/* =========================================================================
 * TC-MOD003-019  get_active_faults — buffer smaller than faults (copy only buffer_size)
 * ========================================================================= */
static bool test_fault_detection_get_active_faults_buffer_smaller(void)
{
    fault_detection_t fd;
    fault_code_t buf[2];
    uint8_t count;

    (void)fault_detection_init(&fd);
    (void)fault_detection_report_fault(&fd, 0x0001U, FAULT_SEVERITY_MINOR);
    (void)fault_detection_report_fault(&fd, 0x0002U, FAULT_SEVERITY_MINOR);
    (void)fault_detection_report_fault(&fd, 0x0003U, FAULT_SEVERITY_MINOR);

    count = fault_detection_get_active_faults(&fd, buf, 2U);
    TEST_ASSERT_EQUAL(2U, count);
    return true;
}

/* =========================================================================
 * TC-MOD003-020  clear_fault — success, count decrements
 * ========================================================================= */
static bool test_fault_detection_clear_fault_success(void)
{
    fault_detection_t fd;
    error_t result;

    (void)fault_detection_init(&fd);
    (void)fault_detection_report_fault(&fd, FAULT_CAN_TIMEOUT, FAULT_SEVERITY_MINOR);
    TEST_ASSERT_EQUAL(1U, fd.fault_log_count);

    result = fault_detection_clear_fault(&fd, FAULT_CAN_TIMEOUT);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(0U, fd.fault_log_count);
    return true;
}

/* =========================================================================
 * TC-MOD003-021  clear_fault — NULL → ERROR_NULL_POINTER
 * ========================================================================= */
static bool test_fault_detection_clear_fault_null(void)
{
    error_t result = fault_detection_clear_fault(NULL, FAULT_CAN_TIMEOUT);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* =========================================================================
 * TC-MOD003-022  clear_fault — not found → ERROR_INVALID_PARAMETER
 * ========================================================================= */
static bool test_fault_detection_clear_fault_not_found(void)
{
    fault_detection_t fd;
    (void)fault_detection_init(&fd);

    error_t result = fault_detection_clear_fault(&fd, FAULT_CAN_TIMEOUT);
    TEST_ASSERT_EQUAL(ERROR_INVALID_PARAMETER, result);
    return true;
}

/* =========================================================================
 * TC-MOD003-023  clear_fault — last critical cleared → critical_fault_active=false
 * ========================================================================= */
static bool test_fault_detection_clear_fault_clears_critical(void)
{
    fault_detection_t fd;
    (void)fault_detection_init(&fd);
    (void)fault_detection_report_fault(&fd, FAULT_WATCHDOG_TIMEOUT, FAULT_SEVERITY_CRITICAL);
    TEST_ASSERT_TRUE(fd.critical_fault_active);

    error_t result = fault_detection_clear_fault(&fd, FAULT_WATCHDOG_TIMEOUT);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_FALSE(fd.critical_fault_active);
    return true;
}

/* =========================================================================
 * TC-MOD003-024  update — critical fault still active (within timeout window)
 *                Covers fault_detection.c lines 93-94:
 *                  else { if (severity == CRITICAL) critical_fault_found = true; }
 * ========================================================================= */
static bool test_fault_detection_update_critical_still_active(void)
{
    fd_setup();
    mock_set_system_time(0U);

    /* Report a CRITICAL fault at time 0 */
    (void)fault_detection_report_fault(&g_fd, FAULT_CAN_TIMEOUT, FAULT_SEVERITY_CRITICAL);
    TEST_ASSERT_TRUE(g_fd.critical_fault_active);

    /* Call update() well within the timeout window (100 ms < 10 000 ms) */
    mock_set_system_time(100U);
    error_t result = fault_detection_update(&g_fd);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);

    /* Fault is still active AND critical — flag must remain true */
    TEST_ASSERT_EQUAL(1U, g_fd.fault_log_count);
    TEST_ASSERT_TRUE(g_fd.critical_fault_active);
    return true;
}

/* =========================================================================
 * TC-MOD003-025  report_fault — duplicate fault upgraded from MINOR to CRITICAL
 *                Covers fault_detection.c line 133-134:
 *                  if (severity == FAULT_SEVERITY_CRITICAL) critical_fault_active = true;
 *                (inside the "duplicate found" path)
 * ========================================================================= */
static bool test_fault_detection_report_duplicate_upgraded_to_critical(void)
{
    fd_setup();
    mock_set_system_time(0U);

    /* First report: MINOR */
    (void)fault_detection_report_fault(&g_fd, FAULT_CAN_TIMEOUT, FAULT_SEVERITY_MINOR);
    TEST_ASSERT_FALSE(g_fd.critical_fault_active);
    TEST_ASSERT_EQUAL(1U, g_fd.fault_log_count);

    /* Second report: same code, now CRITICAL (duplicate upgrade path) */
    mock_set_system_time(200U);
    error_t result = fault_detection_report_fault(&g_fd, FAULT_CAN_TIMEOUT, FAULT_SEVERITY_CRITICAL);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);

    /* Count stays 1 (duplicate), but critical flag must now be set */
    TEST_ASSERT_EQUAL(1U, g_fd.fault_log_count);
    TEST_ASSERT_TRUE(g_fd.critical_fault_active);
    return true;
}

/* =========================================================================
 * TC-MOD003-026  clear_fault — clear one of two critical faults; remaining
 *                critical fault keeps critical_fault_active = true.
 *                Covers fault_detection.c lines 259-262:
 *                  re-scan loop finds remaining critical → critical_fault_found=true; break;
 * ========================================================================= */
static bool test_fault_detection_clear_fault_remaining_critical_stays(void)
{
    fault_detection_t fd;
    (void)fault_detection_init(&fd);

    /* Report two distinct CRITICAL faults */
    (void)fault_detection_report_fault(&fd, FAULT_CAN_TIMEOUT,       FAULT_SEVERITY_CRITICAL);
    (void)fault_detection_report_fault(&fd, FAULT_WATCHDOG_TIMEOUT,  FAULT_SEVERITY_CRITICAL);
    TEST_ASSERT_TRUE(fd.critical_fault_active);
    TEST_ASSERT_EQUAL(2U, fd.fault_log_count);

    /* Clear only the first one */
    error_t result = fault_detection_clear_fault(&fd, FAULT_CAN_TIMEOUT);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(1U, fd.fault_log_count);

    /* The second CRITICAL fault is still active — flag must remain true */
    TEST_ASSERT_TRUE(fd.critical_fault_active);
    return true;
}

/* =========================================================================
 * TC-MOD003-027  update — fault active within timeout, severity MINOR
 *                Covers fault_detection.c line 93 branch false:
 *                  if (fd->fault_log[i].severity == FAULT_SEVERITY_CRITICAL)
 *                  → NOT taken (MINOR fault stays active, critical_fault_active=false)
 * ========================================================================= */
static bool test_fault_detection_update_minor_still_active(void)
{
    fd_setup();
    mock_set_system_time(0U);

    /* Report a MINOR fault at time 0 */
    (void)fault_detection_report_fault(&g_fd, FAULT_CAN_TIMEOUT, FAULT_SEVERITY_MINOR);
    TEST_ASSERT_EQUAL(1U, g_fd.fault_log_count);

    /* Advance to 100ms — well within 10s timeout, fault stays active */
    mock_set_system_time(100U);

    error_t result = fault_detection_update(&g_fd);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);

    /* Fault must still be active, count unchanged, critical flag remains false */
    TEST_ASSERT_EQUAL(1U, g_fd.fault_log_count);
    TEST_ASSERT_FALSE(g_fd.critical_fault_active);
    return true;
}

/* =========================================================================
 * TC-MOD003-028  update — corrupted count (fault_log_count=0) with active entry
 *                Covers fault_detection.c line 88 branch false:
 *                  if (fd->fault_log_count > 0U) → NOT taken
 *                Fault ages out but count is already 0 — must not underflow.
 * ========================================================================= */
static bool test_fault_detection_update_corrupted_count_aging(void)
{
    fd_setup();
    mock_set_system_time(0U);

    /* Manually plant an active fault entry but corrupt the count to 0 */
    g_fd.fault_log[0].active    = true;
    g_fd.fault_log[0].code      = FAULT_CAN_TIMEOUT;
    g_fd.fault_log[0].severity  = FAULT_SEVERITY_MINOR;
    g_fd.fault_log[0].timestamp = 0U;
    g_fd.fault_log_count        = 0U;  /* Corrupted: count says 0 but entry is active */

    /* Advance past age-out threshold */
    mock_set_system_time(FAULT_AGE_TIMEOUT_MS + 1U);

    error_t result = fault_detection_update(&g_fd);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);

    /* Count must NOT underflow below 0; entry deactivated */
    TEST_ASSERT_FALSE(g_fd.fault_log[0].active);
    TEST_ASSERT_EQUAL(0U, g_fd.fault_log_count);
    return true;
}

/* =========================================================================
 * TC-MOD003-029  clear_fault — loop passes active entry with non-matching code
 *                Covers fault_detection.c line 240 branch 3 (active=true, code!=target):
 *                  if ((fd->fault_log[i].active == true) && (fd->fault_log[i].code == code))
 *                  → outer true but inner false (active entry, different code)
 * ========================================================================= */
static bool test_fault_detection_clear_fault_nonmatching_active_entry(void)
{
    fd_setup();

    /* Add two distinct MINOR faults */
    (void)fault_detection_report_fault(&g_fd, FAULT_CAN_TIMEOUT,      FAULT_SEVERITY_MINOR);
    (void)fault_detection_report_fault(&g_fd, FAULT_WATCHDOG_TIMEOUT, FAULT_SEVERITY_MINOR);
    TEST_ASSERT_EQUAL(2U, g_fd.fault_log_count);

    /* Clear the SECOND fault — loop will pass the first (active, non-matching) entry */
    error_t result = fault_detection_clear_fault(&g_fd, FAULT_WATCHDOG_TIMEOUT);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(1U, g_fd.fault_log_count);

    /* First fault still active */
    TEST_ASSERT_TRUE(g_fd.fault_log[0].active);
    TEST_ASSERT_EQUAL(FAULT_CAN_TIMEOUT, g_fd.fault_log[0].code);
    return true;
}

/* =========================================================================
 * TC-MOD003-030  clear_fault — corrupted count (fault_log_count=0) with active entry
 *                Covers fault_detection.c line 243 branch false:
 *                  if (fd->fault_log_count > 0U) → NOT taken
 *                Entry found and cleared but count is already 0 — must not underflow.
 * ========================================================================= */
static bool test_fault_detection_clear_fault_corrupted_count(void)
{
    fd_setup();

    /* Manually plant an active fault entry but corrupt the count to 0 */
    g_fd.fault_log[0].active    = true;
    g_fd.fault_log[0].code      = FAULT_CAN_TIMEOUT;
    g_fd.fault_log[0].severity  = FAULT_SEVERITY_MINOR;
    g_fd.fault_log[0].timestamp = 0U;
    g_fd.fault_log_count        = 0U;  /* Corrupted */

    error_t result = fault_detection_clear_fault(&g_fd, FAULT_CAN_TIMEOUT);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);

    /* Entry deactivated, count must NOT underflow */
    TEST_ASSERT_FALSE(g_fd.fault_log[0].active);
    TEST_ASSERT_EQUAL(0U, g_fd.fault_log_count);
    return true;
}

/* =========================================================================
 * TC-MOD003-031  clear_fault — clear CRITICAL, remaining MINOR stays active
 *                Covers fault_detection.c line 260 branch false (re-scan):
 *                  if ((fd->fault_log[i].active == true) &&
 *                      (fd->fault_log[i].severity == FAULT_SEVERITY_CRITICAL))
 *                  → active=true but severity!=CRITICAL (MINOR entry found, not critical)
 *                After clearing the CRITICAL fault, critical_fault_active must be false.
 * ========================================================================= */
static bool test_fault_detection_clear_critical_minor_remains(void)
{
    fd_setup();

    /* Add CRITICAL then MINOR */
    (void)fault_detection_report_fault(&g_fd, FAULT_WATCHDOG_TIMEOUT, FAULT_SEVERITY_CRITICAL);
    (void)fault_detection_report_fault(&g_fd, FAULT_CAN_TIMEOUT,      FAULT_SEVERITY_MINOR);
    TEST_ASSERT_TRUE(g_fd.critical_fault_active);
    TEST_ASSERT_EQUAL(2U, g_fd.fault_log_count);

    /* Clear the CRITICAL fault */
    error_t result = fault_detection_clear_fault(&g_fd, FAULT_WATCHDOG_TIMEOUT);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_EQUAL(1U, g_fd.fault_log_count);

    /* Re-scan finds MINOR only → critical_fault_active must now be false */
    TEST_ASSERT_FALSE(g_fd.critical_fault_active);

    /* MINOR entry still present */
    TEST_ASSERT_TRUE(g_fd.fault_log[1].active);
    TEST_ASSERT_EQUAL(FAULT_CAN_TIMEOUT, g_fd.fault_log[1].code);
    return true;
}

/* =========================================================================
 * Test suite runner
 * ========================================================================= */
void run_fault_detection_tests(void)
{
    const int NUM_TESTS = 31;
    test_suite_begin("MOD-003: fault_detection");

    run_test("TC-MOD003-001: init success",                              test_fault_detection_init_success);
    run_test("TC-MOD003-002: init NULL",                                 test_fault_detection_init_null);
    run_test("TC-MOD003-003: update NULL",                               test_fault_detection_update_null);
    run_test("TC-MOD003-004: update fault ages out",                     test_fault_detection_update_fault_ages_out);
    run_test("TC-MOD003-005: update critical cleared by aging",          test_fault_detection_update_critical_cleared_by_aging);
    run_test("TC-MOD003-006: report_fault success",                      test_fault_detection_report_fault_success);
    run_test("TC-MOD003-007: report_fault NULL",                         test_fault_detection_report_fault_null);
    run_test("TC-MOD003-008: report_fault invalid severity",             test_fault_detection_report_fault_invalid_severity);
    run_test("TC-MOD003-009: report_fault duplicate refresh",            test_fault_detection_report_fault_duplicate_refresh);
    run_test("TC-MOD003-010: report_fault critical sets flag",           test_fault_detection_report_fault_critical_sets_flag);
    run_test("TC-MOD003-011: report_fault log full saturates",           test_fault_detection_report_fault_log_full);
    run_test("TC-MOD003-012: is_critical false initially",               test_fault_detection_is_critical_false_initially);
    run_test("TC-MOD003-013: is_critical true after critical fault",     test_fault_detection_is_critical_true_after_critical);
    run_test("TC-MOD003-014: is_critical NULL fail-safe true",           test_fault_detection_is_critical_null_fail_safe);
    run_test("TC-MOD003-015: get_active_faults success",                 test_fault_detection_get_active_faults_success);
    run_test("TC-MOD003-016: get_active_faults NULL fd",                 test_fault_detection_get_active_faults_null_fd);
    run_test("TC-MOD003-017: get_active_faults NULL buffer",             test_fault_detection_get_active_faults_null_buffer);
    run_test("TC-MOD003-018: get_active_faults zero size",               test_fault_detection_get_active_faults_zero_size);
    run_test("TC-MOD003-019: get_active_faults buffer smaller",          test_fault_detection_get_active_faults_buffer_smaller);
    run_test("TC-MOD003-020: clear_fault success",                       test_fault_detection_clear_fault_success);
    run_test("TC-MOD003-021: clear_fault NULL",                          test_fault_detection_clear_fault_null);
    run_test("TC-MOD003-022: clear_fault not found",                     test_fault_detection_clear_fault_not_found);
    run_test("TC-MOD003-023: clear_fault last critical clears flag",     test_fault_detection_clear_fault_clears_critical);
    run_test("TC-MOD003-024: update critical still active within window",test_fault_detection_update_critical_still_active);
    run_test("TC-MOD003-025: report_fault duplicate upgraded to critical",test_fault_detection_report_duplicate_upgraded_to_critical);
    run_test("TC-MOD003-026: clear_fault remaining critical stays active",test_fault_detection_clear_fault_remaining_critical_stays);
    run_test("TC-MOD003-027: update minor fault still active within window",test_fault_detection_update_minor_still_active);
    run_test("TC-MOD003-028: update corrupted count aging (no underflow)",  test_fault_detection_update_corrupted_count_aging);
    run_test("TC-MOD003-029: clear_fault non-matching active entry skipped",test_fault_detection_clear_fault_nonmatching_active_entry);
    run_test("TC-MOD003-030: clear_fault corrupted count (no underflow)",   test_fault_detection_clear_fault_corrupted_count);
    run_test("TC-MOD003-031: clear critical, minor remains, flag cleared",  test_fault_detection_clear_critical_minor_remains);

    test_suite_end("MOD-003: fault_detection", NUM_TESTS);
}
