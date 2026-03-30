/**
 * @file test_safety_monitor.c
 * @brief Unit tests for Safety Monitor (MOD-002)
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.5, Table A.21
 * @traceability DOC-COMPTEST-2026-001 v1.0 Section 3.2
 * 
 * @description
 * Comprehensive unit tests for MOD-002 Safety Monitor.
 * Total test cases: 22
 * Coverage target: 100% statement, branch, condition (SIL 3)
 */

#include "test_harness.h"
#include "test_mocks.h"
#include "../src/safety_monitor/safety_monitor.h"

static int mod002_test_count = 0;

/* Mock HAL functions */
/* NOTE: get_system_time_ms() is now in test_mocks.c */
extern error_t sensor_hal_read_speed(uint16_t* primary, uint16_t* secondary);
static uint16_t mock_primary_speed = 0;
static uint16_t mock_secondary_speed = 0;
static error_t mock_speed_sensor_result = ERROR_SUCCESS;

error_t sensor_hal_read_speed(uint16_t* primary, uint16_t* secondary) {
    if (primary) *primary = mock_primary_speed;
    if (secondary) *secondary = mock_secondary_speed;
    return mock_speed_sensor_result;
}

void reset_safety_mocks(void) {
    reset_hardware_mocks();  /* Reset time from test_mocks.c */
    mock_primary_speed = 0;
    mock_secondary_speed = 0;
    mock_speed_sensor_result = ERROR_SUCCESS;
}

/* TC-MOD002-001: Initialization Success (Fail-Safe Defaults) */
bool test_safety_monitor_init_success(void) {
    safety_monitor_t monitor;
    error_t result = safety_monitor_init(&monitor);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_FALSE(monitor.is_safe_to_open);  /* Fail-safe: NOT safe initially */
    TEST_ASSERT_TRUE(monitor.should_lock);       /* Fail-safe: lock by default */
    return true;
}

/* TC-MOD002-002: Initialization NULL Pointer */
bool test_safety_monitor_init_null(void) {
    error_t result = safety_monitor_init(NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* TC-MOD002-003: Update Both Sensors Valid (Agreement) */
bool test_safety_monitor_update_sensors_agree(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    mock_primary_speed = 50;   /* 5.0 km/h */
    mock_secondary_speed = 52; /* 5.2 km/h */
    error_t result = safety_monitor_update(&monitor);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_TRUE(monitor.primary_sensor_valid);
    TEST_ASSERT_TRUE(monitor.secondary_sensor_valid);
    /* Speed should be average: 51 */
    TEST_ASSERT_TRUE(monitor.speed >= 50 && monitor.speed <= 52);
    return true;
}

/* TC-MOD002-004: Update Sensor Disagreement (Fail-Safe: Use Higher Speed)
 * SAFETY_SPEED_DISAGREE_THRESHOLD = 100 (strictly >).
 * Use diff = 110 (>100) to trigger the disagree branch. */
bool test_safety_monitor_update_sensor_disagree(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    mock_primary_speed = 10;    /* 1.0 km/h */
    mock_secondary_speed = 120; /* 12.0 km/h — diff = 110 > threshold(100) */
    error_t result = safety_monitor_update(&monitor);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* Fail-safe: should use HIGHER speed (120) */
    TEST_ASSERT_EQUAL(120, monitor.speed);
    return true;
}

/* TC-MOD002-005: Update Primary Sensor Failed (Use Secondary) */
bool test_safety_monitor_update_primary_failed(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    mock_primary_speed = 9999; /* Invalid (too high) */
    mock_secondary_speed = 50;  /* Valid */
    error_t result = safety_monitor_update(&monitor);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_FALSE(monitor.primary_sensor_valid);
    TEST_ASSERT_TRUE(monitor.secondary_sensor_valid);
    TEST_ASSERT_EQUAL(50, monitor.speed);
    return true;
}

/* TC-MOD002-006: Update Both Sensors Failed (Fail-Safe: Assume High Speed) */
bool test_safety_monitor_update_both_sensors_failed(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    mock_primary_speed = 9999;   /* Invalid */
    mock_secondary_speed = 9999; /* Invalid */
    error_t result = safety_monitor_update(&monitor);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_FALSE(monitor.primary_sensor_valid);
    TEST_ASSERT_FALSE(monitor.secondary_sensor_valid);
    /* Fail-safe: assume high speed, lock doors */
    TEST_ASSERT_TRUE(monitor.should_lock);
    TEST_ASSERT_FALSE(monitor.is_safe_to_open);
    return true;
}

/* TC-MOD002-008: Update Is Safe to Open (Speed < 1 km/h) */
bool test_safety_monitor_update_safe_to_open(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    mock_primary_speed = 8; /* 0.8 km/h < 1.0 km/h */
    mock_secondary_speed = 9;
    error_t result = safety_monitor_update(&monitor);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_TRUE(monitor.is_safe_to_open);
    return true;
}

/* TC-MOD002-009: Update NULL Pointer */
bool test_safety_monitor_update_null(void) {
    error_t result = safety_monitor_update(NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* TC-MOD002-010: Is Safe to Open TRUE */
bool test_safety_monitor_is_safe_to_open_true(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    monitor.is_safe_to_open = true;
    monitor.primary_sensor_valid = true;
    monitor.secondary_sensor_valid = true;
    bool result = safety_monitor_is_safe_to_open(&monitor);
    TEST_ASSERT_TRUE(result);
    return true;
}

/* TC-MOD002-011: Is Safe to Open FALSE (Sensors Failed) */
bool test_safety_monitor_is_safe_to_open_sensors_failed(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    monitor.primary_sensor_valid = false;
    monitor.secondary_sensor_valid = false;
    bool result = safety_monitor_is_safe_to_open(&monitor);
    TEST_ASSERT_FALSE(result);  /* Fail-safe */
    return true;
}

/* TC-MOD002-012: Is Safe to Open NULL Pointer (Fail-Safe) */
bool test_safety_monitor_is_safe_to_open_null(void) {
    bool result = safety_monitor_is_safe_to_open(NULL);
    TEST_ASSERT_FALSE(result);  /* Fail-safe: NOT safe */
    return true;
}

/* TC-MOD002-013: Should Lock TRUE (Speed > 5 km/h) */
bool test_safety_monitor_should_lock_true(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    monitor.should_lock = true;
    monitor.primary_sensor_valid = true;
    bool result = safety_monitor_should_lock(&monitor);
    TEST_ASSERT_TRUE(result);
    return true;
}

/* TC-MOD002-014: Should Lock TRUE (Sensors Failed, Fail-Safe) */
bool test_safety_monitor_should_lock_sensors_failed(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    monitor.primary_sensor_valid = false;
    monitor.secondary_sensor_valid = false;
    bool result = safety_monitor_should_lock(&monitor);
    TEST_ASSERT_TRUE(result);  /* Fail-safe: lock by default */
    return true;
}

/* TC-MOD002-015: Should Lock NULL Pointer (Fail-Safe) */
bool test_safety_monitor_should_lock_null(void) {
    bool result = safety_monitor_should_lock(NULL);
    TEST_ASSERT_TRUE(result);  /* Fail-safe: lock by default */
    return true;
}

/* TC-MOD002-019: Get Speed Success */
bool test_safety_monitor_get_speed_success(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    monitor.speed = 500; /* 50.0 km/h */
    uint16_t speed = safety_monitor_get_speed(&monitor);
    TEST_ASSERT_EQUAL(500, speed);
    return true;
}

/* TC-MOD002-020: Get Speed NULL Pointer (Fail-Safe) */
bool test_safety_monitor_get_speed_null(void) {
    uint16_t speed = safety_monitor_get_speed(NULL);
    TEST_ASSERT_TRUE(speed >= 1000);  /* Fail-safe: assume high speed */
    return true;
}

/* TC-MOD002-007: Update Secondary Sensor Only (Primary Failed) */
bool test_safety_monitor_update_secondary_failed(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    mock_primary_speed = 9999;  /* Invalid - above SAFETY_SPEED_MAX_PLAUSIBLE (3000) */
    mock_secondary_speed = 75;  /* Valid */
    error_t result = safety_monitor_update(&monitor);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_FALSE(monitor.primary_sensor_valid);
    TEST_ASSERT_TRUE(monitor.secondary_sensor_valid);
    /* Fail-safe: only secondary valid, use secondary speed */
    TEST_ASSERT_EQUAL(75, monitor.speed);
    return true;
}

/* TC-MOD002-016: Should Unlock TRUE (speed < 2 km/h for >= 1s) */
bool test_safety_monitor_should_unlock_true(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    /* Set speed below SAFETY_SPEED_THRESHOLD_UNLOCK (20 = 2.0 km/h) */
    mock_primary_speed = 10;
    mock_secondary_speed = 10;
    /* First update - starts hysteresis timer at time=0 */
    safety_monitor_update(&monitor);
    TEST_ASSERT_FALSE(monitor.should_unlock);  /* Not yet: 0ms elapsed */
    /* Advance time >= SAFETY_UNLOCK_HYSTERESIS_MS (1000ms) */
    mock_advance_time(1100U);
    /* Second update - hysteresis already active, timer started at 0 */
    safety_monitor_update(&monitor);
    TEST_ASSERT_TRUE(monitor.should_unlock);
    return true;
}

/* TC-MOD002-017: Should Unlock FALSE (speed low but hysteresis not elapsed) */
bool test_safety_monitor_should_unlock_false_no_hysteresis(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    mock_primary_speed = 10;
    mock_secondary_speed = 10;
    /* Start hysteresis at time=0, only 500ms elapsed */
    safety_monitor_update(&monitor);  /* Starts timer at t=0 */
    mock_advance_time(500U);
    safety_monitor_update(&monitor);  /* 500ms < 1000ms */
    TEST_ASSERT_FALSE(monitor.should_unlock);
    return true;
}

/* TC-MOD002-018: Should Unlock NULL Pointer (Fail-Safe) */
bool test_safety_monitor_should_unlock_null(void) {
    bool result = safety_monitor_should_unlock(NULL);
    TEST_ASSERT_FALSE(result);  /* Fail-safe: keep locked */
    return true;
}

/* TC-MOD002-021: Get Sensor Health Success */
bool test_safety_monitor_get_sensor_health_success(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    mock_primary_speed = 50;
    mock_secondary_speed = 50;
    safety_monitor_update(&monitor);
    bool pv = false;
    bool sv = false;
    error_t result = safety_monitor_get_sensor_health(&monitor, &pv, &sv);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_TRUE(pv);
    TEST_ASSERT_TRUE(sv);
    return true;
}

/* TC-MOD002-022: Get Sensor Health NULL Pointer */
bool test_safety_monitor_get_sensor_health_null(void) {
    safety_monitor_t monitor;
    bool pv = false;
    bool sv = false;
    error_t result;
    result = safety_monitor_get_sensor_health(NULL, &pv, &sv);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    safety_monitor_init(&monitor);
    result = safety_monitor_get_sensor_health(&monitor, NULL, &sv);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    result = safety_monitor_get_sensor_health(&monitor, &pv, NULL);
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, result);
    return true;
}

/* TC-MOD002-023: Update Sensor Disagree — primary > secondary
 * Covers safety_monitor.c lines 113-114 (speed_diff = primary - secondary)
 * and line 122 (monitor->speed = primary_raw when primary > secondary). */
bool test_safety_monitor_update_disagree_primary_higher(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    mock_primary_speed = 120; /* diff = 110 > threshold(100), primary > secondary */
    mock_secondary_speed = 10;
    error_t result = safety_monitor_update(&monitor);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* Fail-safe: use HIGHER speed (primary=120) */
    TEST_ASSERT_EQUAL(120, monitor.speed);
    return true;
}

/* TC-MOD002-024: Update Only Primary Valid (secondary above MAX_PLAUSIBLE)
 * Covers safety_monitor.c lines 132-135:
 *   else if (primary_sensor_valid) { speed = primary_raw; report secondary fault; } */
bool test_safety_monitor_update_only_primary_valid(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    mock_primary_speed = 50;   /* Valid (< 3000) */
    mock_secondary_speed = 9999; /* Invalid (> SAFETY_SPEED_MAX_PLAUSIBLE = 3000) */
    error_t result = safety_monitor_update(&monitor);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    TEST_ASSERT_TRUE(monitor.primary_sensor_valid);
    TEST_ASSERT_FALSE(monitor.secondary_sensor_valid);
    TEST_ASSERT_EQUAL(50, monitor.speed);
    return true;
}

/* TC-MOD002-025: Is Safe to Open FALSE — valid sensors but speed too high
 * Covers safety_monitor.c line 203-204:
 *   else { return false; }  (is_safe_to_open == false with valid sensors) */
bool test_safety_monitor_is_safe_to_open_false_valid_sensors(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    monitor.is_safe_to_open = false;
    monitor.primary_sensor_valid = true;
    monitor.secondary_sensor_valid = false; /* one valid is enough */
    bool result = safety_monitor_is_safe_to_open(&monitor);
    TEST_ASSERT_FALSE(result);
    return true;
}

/* TC-MOD002-026: Should Unlock FALSE — both sensors failed (fail-safe)
 * Covers safety_monitor.c lines 243-245:
 *   if (both invalid) { return false; } */
bool test_safety_monitor_should_unlock_sensors_failed(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    monitor.primary_sensor_valid = false;
    monitor.secondary_sensor_valid = false;
    bool result = safety_monitor_should_unlock(&monitor);
    TEST_ASSERT_FALSE(result);  /* Fail-safe: keep locked */
    return true;
}

/* TC-MOD002-027: Should Unlock FALSE — hysteresis not active
 * Covers safety_monitor.c lines 249-251:
 *   if (!unlock_hysteresis_active) { return false; }
 * Use a freshly initialised monitor (hysteresis never started). */
bool test_safety_monitor_should_unlock_hysteresis_not_active(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    /* Sensors valid, but hysteresis never activated */
    monitor.primary_sensor_valid = true;
    monitor.secondary_sensor_valid = true;
    monitor.unlock_hysteresis_active = false;
    bool result = safety_monitor_should_unlock(&monitor);
    TEST_ASSERT_FALSE(result);
    return true;
}

/* TC-MOD002-028: Both sensors invalid via HAL error return (not plausibility)
 * Covers safety_monitor.c lines 104-108 compound &&:
 *   primary_sensor_valid = (err==ERROR_SUCCESS) && ...
 *   The err!=ERROR_SUCCESS branch (first operand false, &&-short-circuit).
 * When sensor_hal_read_speed returns ERROR_HARDWARE_FAILURE both valid-flags
 * become false via the error path, not via high ADC values. */
bool test_safety_monitor_both_invalid_via_error(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    mock_speed_sensor_result = ERROR_HARDWARE_FAILURE;
    error_t result = safety_monitor_update(&monitor);
    TEST_ASSERT_EQUAL(ERROR_SUCCESS, result);
    /* Both flags false because err != ERROR_SUCCESS */
    TEST_ASSERT_FALSE(monitor.primary_sensor_valid);
    TEST_ASSERT_FALSE(monitor.secondary_sensor_valid);
    /* Fail-safe: should lock, not safe to open */
    TEST_ASSERT_TRUE(monitor.should_lock);
    TEST_ASSERT_FALSE(monitor.is_safe_to_open);
    return true;
}

/* TC-MOD002-029: is_safe_to_open — primary valid, secondary invalid
 * Covers safety_monitor.c line 195 compound &&:
 *   (!primary_sensor_valid) && (!secondary_sensor_valid)
 *   When primary_sensor_valid=true the first operand is FALSE → && short-circuits
 *   to false, so the both-invalid branch is NOT taken. */
bool test_safety_monitor_is_safe_primary_valid_secondary_invalid(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    monitor.primary_sensor_valid = true;
    monitor.secondary_sensor_valid = false;
    monitor.is_safe_to_open = true;
    bool result = safety_monitor_is_safe_to_open(&monitor);
    /* Primary valid → not both-failed path → returns is_safe_to_open (true) */
    TEST_ASSERT_TRUE(result);
    return true;
}

/* TC-MOD002-030: should_lock — primary valid, secondary invalid
 * Covers safety_monitor.c line 221 compound &&:
 *   (!primary_sensor_valid) && (!secondary_sensor_valid)
 *   First operand false when primary_sensor_valid=true → short-circuit. */
bool test_safety_monitor_should_lock_primary_valid_secondary_invalid(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    monitor.primary_sensor_valid = true;
    monitor.secondary_sensor_valid = false;
    monitor.should_lock = false;   /* Explicitly not locked */
    bool result = safety_monitor_should_lock(&monitor);
    /* Primary valid → not both-failed path → returns should_lock (false) */
    TEST_ASSERT_FALSE(result);
    return true;
}

/* TC-MOD002-031: should_unlock — primary valid, secondary invalid
 * Covers safety_monitor.c line 243 compound &&:
 *   (!primary_sensor_valid) && (!secondary_sensor_valid)
 *   First operand false when primary_sensor_valid=true → short-circuit. */
bool test_safety_monitor_should_unlock_primary_valid_secondary_invalid(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    monitor.primary_sensor_valid = true;
    monitor.secondary_sensor_valid = false;
    monitor.unlock_hysteresis_active = false;
    bool result = safety_monitor_should_unlock(&monitor);
    /* Primary valid → not both-failed path → hysteresis not active → false */
    TEST_ASSERT_FALSE(result);
    return true;
}

/* TC-MOD002-033: is_safe_to_open — primary INVALID, secondary VALID
 * Covers safety_monitor.c line 195 branch 3:
 *   (!primary_sensor_valid) && (!secondary_sensor_valid)
 *   = true && false → whole condition FALSE (not both-invalid)
 * The "both sensors failed" path is NOT taken; falls through to return is_safe_to_open. */
bool test_safety_monitor_is_safe_primary_invalid_secondary_valid(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    monitor.primary_sensor_valid   = false;  /* primary invalid */
    monitor.secondary_sensor_valid = true;   /* secondary valid → condition false */
    monitor.is_safe_to_open = true;
    bool result = safety_monitor_is_safe_to_open(&monitor);
    /* Not both-invalid path → returns is_safe_to_open (true) */
    TEST_ASSERT_TRUE(result);
    return true;
}

/* TC-MOD002-034: should_lock — primary INVALID, secondary VALID
 * Covers safety_monitor.c line 221 branch 3:
 *   (!primary_sensor_valid) && (!secondary_sensor_valid)
 *   = true && false → whole condition FALSE */
bool test_safety_monitor_should_lock_primary_invalid_secondary_valid(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    monitor.primary_sensor_valid   = false;
    monitor.secondary_sensor_valid = true;
    monitor.should_lock = true;
    bool result = safety_monitor_should_lock(&monitor);
    /* Not both-invalid → returns should_lock (true) */
    TEST_ASSERT_TRUE(result);
    return true;
}

/* TC-MOD002-035: should_unlock — primary INVALID, secondary VALID
 * Covers safety_monitor.c line 243 branch 3:
 *   (!primary_sensor_valid) && (!secondary_sensor_valid)
 *   = true && false → whole condition FALSE */
bool test_safety_monitor_should_unlock_primary_invalid_secondary_valid(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    monitor.primary_sensor_valid   = false;
    monitor.secondary_sensor_valid = true;
    monitor.unlock_hysteresis_active = true;
    monitor.should_unlock = true;
    bool result = safety_monitor_should_unlock(&monitor);
    /* Not both-invalid, hysteresis active → returns should_unlock (true) */
    TEST_ASSERT_TRUE(result);
    return true;
}

/* TC-MOD002-032: should_unlock — hysteresis IS active (line 249 branch 1 false)
 * Covers safety_monitor.c line 249: if (!unlock_hysteresis_active)
 * When hysteresis IS active the condition is FALSE → falls through to line 255.
 * Also covers line 255: return monitor->should_unlock.
 *
 * Setup: run update() with low speed (10 < 20) at time=0 to start hysteresis,
 * advance 1100ms, run update() again to set should_unlock=true, then call
 * safety_monitor_should_unlock() which will reach line 255. */
bool test_safety_monitor_should_unlock_hysteresis_active(void) {
    safety_monitor_t monitor;
    reset_safety_mocks();
    safety_monitor_init(&monitor);
    mock_primary_speed = 10U;
    mock_secondary_speed = 10U;
    /* First update: starts hysteresis at t=0 */
    mock_set_system_time(0U);
    safety_monitor_update(&monitor);
    TEST_ASSERT_TRUE(monitor.unlock_hysteresis_active);
    TEST_ASSERT_FALSE(monitor.should_unlock);
    /* Advance > 1000ms; second update sets should_unlock=true */
    mock_advance_time(1100U);
    safety_monitor_update(&monitor);
    TEST_ASSERT_TRUE(monitor.should_unlock);
    /* Now call the accessor — hysteresis_active=true, should_unlock=true → line 255 */
    bool result = safety_monitor_should_unlock(&monitor);
    TEST_ASSERT_TRUE(result);
    return true;
}

/* Test Suite Runner */
void run_safety_monitor_tests(void) {
    test_suite_begin("MOD-002: Safety Monitor");
    
    run_test("TC-MOD002-001: init - success", test_safety_monitor_init_success); mod002_test_count++;
    run_test("TC-MOD002-002: init - NULL", test_safety_monitor_init_null); mod002_test_count++;
    run_test("TC-MOD002-003: update - sensors agree", test_safety_monitor_update_sensors_agree); mod002_test_count++;
    run_test("TC-MOD002-004: update - sensor disagree", test_safety_monitor_update_sensor_disagree); mod002_test_count++;
    run_test("TC-MOD002-005: update - primary failed", test_safety_monitor_update_primary_failed); mod002_test_count++;
    run_test("TC-MOD002-006: update - both sensors failed", test_safety_monitor_update_both_sensors_failed); mod002_test_count++;
    run_test("TC-MOD002-008: update - safe to open", test_safety_monitor_update_safe_to_open); mod002_test_count++;
    run_test("TC-MOD002-009: update - NULL", test_safety_monitor_update_null); mod002_test_count++;
    run_test("TC-MOD002-010: is_safe_to_open - true", test_safety_monitor_is_safe_to_open_true); mod002_test_count++;
    run_test("TC-MOD002-011: is_safe_to_open - sensors failed", test_safety_monitor_is_safe_to_open_sensors_failed); mod002_test_count++;
    run_test("TC-MOD002-012: is_safe_to_open - NULL", test_safety_monitor_is_safe_to_open_null); mod002_test_count++;
    run_test("TC-MOD002-013: should_lock - true", test_safety_monitor_should_lock_true); mod002_test_count++;
    run_test("TC-MOD002-014: should_lock - sensors failed", test_safety_monitor_should_lock_sensors_failed); mod002_test_count++;
    run_test("TC-MOD002-015: should_lock - NULL", test_safety_monitor_should_lock_null); mod002_test_count++;
    run_test("TC-MOD002-019: get_speed - success", test_safety_monitor_get_speed_success); mod002_test_count++;
    run_test("TC-MOD002-020: get_speed - NULL", test_safety_monitor_get_speed_null); mod002_test_count++;
    
    run_test("TC-MOD002-007: update - secondary only", test_safety_monitor_update_secondary_failed); mod002_test_count++;
    run_test("TC-MOD002-016: should_unlock - true", test_safety_monitor_should_unlock_true); mod002_test_count++;
    run_test("TC-MOD002-017: should_unlock - no hysteresis", test_safety_monitor_should_unlock_false_no_hysteresis); mod002_test_count++;
    run_test("TC-MOD002-018: should_unlock - NULL", test_safety_monitor_should_unlock_null); mod002_test_count++;
    run_test("TC-MOD002-021: get_sensor_health - success", test_safety_monitor_get_sensor_health_success); mod002_test_count++;
    run_test("TC-MOD002-022: get_sensor_health - NULL", test_safety_monitor_get_sensor_health_null); mod002_test_count++;
    run_test("TC-MOD002-023: update - disagree primary higher", test_safety_monitor_update_disagree_primary_higher); mod002_test_count++;
    run_test("TC-MOD002-024: update - only primary valid", test_safety_monitor_update_only_primary_valid); mod002_test_count++;
    run_test("TC-MOD002-025: is_safe_to_open - false valid sensors", test_safety_monitor_is_safe_to_open_false_valid_sensors); mod002_test_count++;
    run_test("TC-MOD002-026: should_unlock - sensors failed", test_safety_monitor_should_unlock_sensors_failed); mod002_test_count++;
    run_test("TC-MOD002-027: should_unlock - hysteresis not active", test_safety_monitor_should_unlock_hysteresis_not_active); mod002_test_count++;
    run_test("TC-MOD002-028: update - both invalid via HAL error", test_safety_monitor_both_invalid_via_error); mod002_test_count++;
    run_test("TC-MOD002-029: is_safe_to_open - primary valid secondary invalid", test_safety_monitor_is_safe_primary_valid_secondary_invalid); mod002_test_count++;
    run_test("TC-MOD002-030: should_lock - primary valid secondary invalid", test_safety_monitor_should_lock_primary_valid_secondary_invalid); mod002_test_count++;
    run_test("TC-MOD002-031: should_unlock - primary valid secondary invalid", test_safety_monitor_should_unlock_primary_valid_secondary_invalid); mod002_test_count++;
    run_test("TC-MOD002-032: should_unlock - hysteresis active reaches line 255", test_safety_monitor_should_unlock_hysteresis_active); mod002_test_count++;
    run_test("TC-MOD002-033: is_safe_to_open - primary invalid secondary valid", test_safety_monitor_is_safe_primary_invalid_secondary_valid); mod002_test_count++;
    run_test("TC-MOD002-034: should_lock - primary invalid secondary valid", test_safety_monitor_should_lock_primary_invalid_secondary_valid); mod002_test_count++;
    run_test("TC-MOD002-035: should_unlock - primary invalid secondary valid", test_safety_monitor_should_unlock_primary_invalid_secondary_valid); mod002_test_count++;

    test_suite_end("MOD-002: Safety Monitor", mod002_test_count);
}
