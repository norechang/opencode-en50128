#include <stdio.h>
#include <stdbool.h>
#include "integration_mocks.h"
#include "../../src/door_control/door_fsm.h"
#include "../../src/safety_monitor/safety_monitor.h"
#include "../../src/fault_detection/fault_detection.h"
#include "../../src/actuator_hal/actuator_hal.h"
#include "../../src/sensor_hal/sensor_hal.h"

#define TEST_ASSERT_EQUAL(expected, actual, msg) \
    if ((expected) != (actual)) { \
        printf("FAIL: %s (line %d): Expected %d, got %d\n", msg, __LINE__, (int)(expected), (int)(actual)); \
        return false; \
    }

#define TEST_ASSERT_TRUE(cond, msg) \
    if (!(cond)) { \
        printf("FAIL: %s (line %d)\n", msg, __LINE__); \
        return false; \
    }

#define TEST_ASSERT_FALSE(cond, msg) \
    if ((cond)) { \
        printf("FAIL: %s (line %d)\n", msg, __LINE__); \
        return false; \
    }

static bool tc_int_saf_001(void) {
    mock_reset_all();
    actuator_hal_init();
    sensor_hal_init();
    
    door_fsm_t fsm;
    fault_detection_t fault;
    safety_monitor_t monitor;
    safety_monitor_init(&monitor);
    door_fsm_init(&fsm, DOOR_SIDE_LEFT, &fault, &monitor);
    
    /* Door opens at 0 km/h */
    mock_set_train_speed(0);
    safety_monitor_update(&monitor);
    door_fsm_process_event(&fsm, DOOR_EVENT_OPEN_CMD);
    door_fsm_update(&fsm);
    TEST_ASSERT_EQUAL(DOOR_STATE_OPENING, door_fsm_get_state(&fsm), "Door should open at 0 km/h");
    
    /* Speed increases to 6 km/h during opening */
    mock_set_door_positions(50, 0);
    mock_set_train_speed(6);
    mock_advance_time(100);
    safety_monitor_update(&monitor);
    
    TEST_ASSERT_TRUE(safety_monitor_should_lock(&monitor), "Should lock at 6 km/h");
    TEST_ASSERT_FALSE(safety_monitor_is_safe_to_open(&monitor), "Should not be safe to open");
    
    return true;
}

int main(void) {
    printf("Running TC-INT-SAF-001 only...\n");
    bool result = tc_int_saf_001();
    if (result) {
        printf("PASS: TC-INT-SAF-001\n");
        return 0;
    } else {
        printf("FAIL: TC-INT-SAF-001\n");
        return 1;
    }
}
