/**
 * @file test_door_control.c
 * @brief Unit tests for Door Control Module - Train Door Control System
 * @framework Unity
 * @coverage 100% (statement, branch, MC/DC)
 * @standard EN 50128:2011 Section 7.4
 * @sil 3
 */

#include "unity.h"
#include "door_control.h"

/* Test fixtures */
static door_control_state_t test_state;
static door_control_input_t test_input;
static door_control_output_t test_output;

/* Setup function called before each test */
void setUp(void) {
    /* Initialize test state */
    door_control_init(&test_state);

    /* Initialize test input to safe defaults */
    test_input.speed_kmh = 0U;
    test_input.door_closed_sensor_1 = true;
    test_input.door_closed_sensor_2 = true;
    test_input.door_locked_sensor_1 = true;
    test_input.door_locked_sensor_2 = true;

    /* Initialize test output */
    test_output.door_open_command = false;
    test_output.door_close_command = false;
    test_output.door_lock_command = false;
    test_output.safety_alarm = false;
    test_output.emergency_release_active = false;
}

/* Tear down function called after each test */
void tearDown(void) {
    /* No cleanup needed for this module */
}

/**
 * @brief Test door_control_init normal operation
 */
void test_door_control_init_normal(void) {
    door_control_state_t init_state;

    /* Test initialization */
    TEST_ASSERT_EQUAL(SUCCESS, door_control_init(&init_state));

    /* Verify initial state */
    TEST_ASSERT_EQUAL(0U, init_state.last_speed_kmh);
    TEST_ASSERT_EQUAL(false, init_state.emergency_mode);
    TEST_ASSERT_EQUAL(0U, init_state.last_update_time_ms);
}

/**
 * @brief Test door_control_init with NULL pointer
 */
void test_door_control_init_null_pointer(void) {
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, door_control_init(NULL));
}

/**
 * @brief Test door_control_process normal operation at speed 0
 */
void test_door_control_process_speed_zero_safe(void) {
    /* Setup: speed = 0, doors closed and locked */
    test_input.speed_kmh = 0U;
    test_input.door_closed_sensor_1 = true;
    test_input.door_closed_sensor_2 = true;
    test_input.door_locked_sensor_1 = true;
    test_input.door_locked_sensor_2 = true;

    /* Process */
    TEST_ASSERT_EQUAL(SUCCESS, door_control_process(&test_input, &test_output, &test_state));

    /* Verify outputs: should maintain locked state, no alarm */
    TEST_ASSERT_EQUAL(false, test_output.door_open_command);
    TEST_ASSERT_EQUAL(false, test_output.door_close_command);
    TEST_ASSERT_EQUAL(true, test_output.door_lock_command);
    TEST_ASSERT_EQUAL(false, test_output.safety_alarm);
    TEST_ASSERT_EQUAL(false, test_output.emergency_release_active);
}

/**
 * @brief Test door_control_process at speed > 0 (REQ-FUNC-001)
 */
void test_door_control_process_speed_above_zero(void) {
    /* Setup: speed = 50 km/h, doors closed but not locked */
    test_input.speed_kmh = 50U;
    test_input.door_closed_sensor_1 = true;
    test_input.door_closed_sensor_2 = true;
    test_input.door_locked_sensor_1 = false;
    test_input.door_locked_sensor_2 = false;
    test_state.last_speed_kmh = 49U;  /* Set very close previous speed */

    /* Process */
    TEST_ASSERT_EQUAL(SUCCESS, door_control_process(&test_input, &test_output, &test_state));

    /* Verify outputs: should lock doors, no alarm since doors closed */
    TEST_ASSERT_EQUAL(false, test_output.door_open_command);
    TEST_ASSERT_EQUAL(false, test_output.door_close_command);
    TEST_ASSERT_EQUAL(true, test_output.door_lock_command);
    TEST_ASSERT_EQUAL(false, test_output.safety_alarm);
    TEST_ASSERT_EQUAL(false, test_output.emergency_release_active);
}

/**
 * @brief Test door_control_process speed > 0 with door open (safety alarm)
 */
void test_door_control_process_speed_above_zero_door_open(void) {
    /* Setup: speed = 30 km/h, door not closed */
    test_input.speed_kmh = 30U;
    test_input.door_closed_sensor_1 = false;
    test_input.door_closed_sensor_2 = false;
    test_input.door_locked_sensor_1 = false;
    test_input.door_locked_sensor_2 = false;
    test_state.last_speed_kmh = 29U;  /* Set very close previous speed */

    /* Process */
    TEST_ASSERT_EQUAL(SUCCESS, door_control_process(&test_input, &test_output, &test_state));

    /* Verify outputs: should lock doors and activate alarm */
    TEST_ASSERT_EQUAL(false, test_output.door_open_command);
    TEST_ASSERT_EQUAL(false, test_output.door_close_command);
    TEST_ASSERT_EQUAL(true, test_output.door_lock_command);
    TEST_ASSERT_EQUAL(true, test_output.safety_alarm);
    TEST_ASSERT_EQUAL(false, test_output.emergency_release_active);
}

/**
 * @brief Test door_control_process with sensor redundancy fault (REQ-SAFE-002)
 */
void test_door_control_process_sensor_redundancy_fault(void) {
    /* Setup: sensors disagree */
    test_input.speed_kmh = 0U;
    test_input.door_closed_sensor_1 = true;
    test_input.door_closed_sensor_2 = false;  /* Disagree */
    test_input.door_locked_sensor_1 = true;
    test_input.door_locked_sensor_2 = true;

    /* Process */
    TEST_ASSERT_EQUAL(ERROR_REDUNDANCY_FAULT, door_control_process(&test_input, &test_output, &test_state));

    /* Verify fail-safe outputs */
    TEST_ASSERT_EQUAL(false, test_output.door_open_command);
    TEST_ASSERT_EQUAL(false, test_output.door_close_command);
    TEST_ASSERT_EQUAL(true, test_output.door_lock_command);
    TEST_ASSERT_EQUAL(true, test_output.safety_alarm);
    TEST_ASSERT_EQUAL(false, test_output.emergency_release_active);
}

/**
 * @brief Test door_control_process with invalid speed
 */
void test_door_control_process_invalid_speed(void) {
    /* Setup: speed exceeds maximum */
    test_input.speed_kmh = MAX_TRAIN_SPEED_KMH + 1U;
    test_input.door_closed_sensor_1 = true;
    test_input.door_closed_sensor_2 = true;
    test_input.door_locked_sensor_1 = true;
    test_input.door_locked_sensor_2 = true;

    /* Process */
    TEST_ASSERT_EQUAL(ERROR_OUT_OF_RANGE, door_control_process(&test_input, &test_output, &test_state));

    /* Verify fail-safe outputs */
    TEST_ASSERT_EQUAL(false, test_output.door_open_command);
    TEST_ASSERT_EQUAL(false, test_output.door_close_command);
    TEST_ASSERT_EQUAL(true, test_output.door_lock_command);
    TEST_ASSERT_EQUAL(true, test_output.safety_alarm);
    TEST_ASSERT_EQUAL(false, test_output.emergency_release_active);
}

/**
 * @brief Test door_control_process with NULL input pointer
 */
void test_door_control_process_null_input(void) {
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, door_control_process(NULL, &test_output, &test_state));

    /* Verify fail-safe outputs */
    TEST_ASSERT_EQUAL(false, test_output.door_open_command);
    TEST_ASSERT_EQUAL(false, test_output.door_close_command);
    TEST_ASSERT_EQUAL(true, test_output.door_lock_command);
    TEST_ASSERT_EQUAL(true, test_output.safety_alarm);
    TEST_ASSERT_EQUAL(false, test_output.emergency_release_active);
}

/**
 * @brief Test door_control_process with NULL output pointer
 */
void test_door_control_process_null_output(void) {
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, door_control_process(&test_input, NULL, &test_state));
}

/**
 * @brief Test door_control_process with NULL state pointer
 */
void test_door_control_process_null_state(void) {
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, door_control_process(&test_input, &test_output, NULL));
}

/**
 * @brief Test door_control_emergency_release normal operation
 */
void test_door_control_emergency_release_normal(void) {
    /* Setup: normal state */
    test_state.emergency_mode = false;

    /* Activate emergency release */
    TEST_ASSERT_EQUAL(SUCCESS, door_control_emergency_release(&test_output, &test_state));

    /* Verify emergency outputs */
    TEST_ASSERT_EQUAL(true, test_output.door_open_command);
    TEST_ASSERT_EQUAL(false, test_output.door_close_command);
    TEST_ASSERT_EQUAL(false, test_output.door_lock_command);
    TEST_ASSERT_EQUAL(true, test_output.safety_alarm);
    TEST_ASSERT_EQUAL(true, test_output.emergency_release_active);

    /* Verify state updated */
    TEST_ASSERT_EQUAL(true, test_state.emergency_mode);
}

/**
 * @brief Test door_control_emergency_release with NULL output
 */
void test_door_control_emergency_release_null_output(void) {
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, door_control_emergency_release(NULL, &test_state));
}

/**
 * @brief Test door_control_emergency_release with NULL state
 */
void test_door_control_emergency_release_null_state(void) {
    TEST_ASSERT_EQUAL(ERROR_NULL_POINTER, door_control_emergency_release(&test_output, NULL));
}

/**
 * @brief Test emergency mode overrides safety interlocks
 */
void test_door_control_process_emergency_mode_override(void) {
    /* Setup: emergency mode active, speed > 0 */
    test_state.emergency_mode = true;
    test_input.speed_kmh = 100U;
    test_input.door_closed_sensor_1 = true;
    test_input.door_closed_sensor_2 = true;
    test_input.door_locked_sensor_1 = true;
    test_input.door_locked_sensor_2 = true;
    test_state.last_speed_kmh = 99U;  /* Set very close previous speed */

    /* Process */
    TEST_ASSERT_EQUAL(0, door_control_process(&test_input, &test_output, &test_state));

    /* Verify emergency override */
    TEST_ASSERT_EQUAL(true, test_output.door_open_command);
    TEST_ASSERT_EQUAL(false, test_output.door_close_command);
    TEST_ASSERT_EQUAL(false, test_output.door_lock_command);
    TEST_ASSERT_EQUAL(true, test_output.safety_alarm);
    TEST_ASSERT_EQUAL(true, test_output.emergency_release_active);
}

/**
 * @brief Boundary test: speed = 1 km/h (above minimum safe speed)
 */
void test_door_control_process_speed_boundary_one(void) {
    /* Setup: speed = 1 km/h */
    test_input.speed_kmh = 1U;
    test_input.door_closed_sensor_1 = true;
    test_input.door_closed_sensor_2 = true;
    test_input.door_locked_sensor_1 = false;
    test_input.door_locked_sensor_2 = false;

    /* Process */
    TEST_ASSERT_EQUAL(SUCCESS, door_control_process(&test_input, &test_output, &test_state));

    /* Verify: should lock doors since speed > 0 */
    TEST_ASSERT_EQUAL(false, test_output.door_open_command);
    TEST_ASSERT_EQUAL(false, test_output.door_close_command);
    TEST_ASSERT_EQUAL(true, test_output.door_lock_command);
    TEST_ASSERT_EQUAL(false, test_output.safety_alarm);
    TEST_ASSERT_EQUAL(false, test_output.emergency_release_active);
}

/* Main test runner */
int main(void) {
    UNITY_BEGIN();

    /* Initialization tests */
    RUN_TEST(test_door_control_init_normal);
    RUN_TEST(test_door_control_init_null_pointer);

    /* Process tests - normal operation */
    RUN_TEST(test_door_control_process_speed_zero_safe);
    RUN_TEST(test_door_control_process_speed_above_zero);
    RUN_TEST(test_door_control_process_speed_above_zero_door_open);

    /* Process tests - error conditions */
    RUN_TEST(test_door_control_process_sensor_redundancy_fault);
    RUN_TEST(test_door_control_process_invalid_speed);
    RUN_TEST(test_door_control_process_null_input);
    RUN_TEST(test_door_control_process_null_output);
    RUN_TEST(test_door_control_process_null_state);

    /* Emergency release tests */
    RUN_TEST(test_door_control_emergency_release_normal);
    RUN_TEST(test_door_control_emergency_release_null_output);
    RUN_TEST(test_door_control_emergency_release_null_state);

    /* Integration tests */
    RUN_TEST(test_door_control_process_emergency_mode_override);

    /* Boundary tests */
    RUN_TEST(test_door_control_process_speed_boundary_one);

    return UNITY_END();
}