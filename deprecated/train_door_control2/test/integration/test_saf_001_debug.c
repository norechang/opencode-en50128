#include <stdio.h>
#include <stdbool.h>
#include "integration_mocks.h"
#include "../../src/door_control/door_fsm.h"
#include "../../src/safety_monitor/safety_monitor.h"
#include "../../src/fault_detection/fault_detection.h"
#include "../../src/actuator_hal/actuator_hal.h"
#include "../../src/sensor_hal/sensor_hal.h"

int main(void) {
    printf("Running TC-INT-SAF-001 with debug...\n\n");
    
    mock_reset_all();
    actuator_hal_init();
    sensor_hal_init();
    
    door_fsm_t fsm;
    fault_detection_t fault;
    safety_monitor_t monitor;
    
    printf("Initializing safety monitor...\n");
    safety_monitor_init(&monitor);
    
    printf("Initializing door FSM...\n");
    door_fsm_init(&fsm, DOOR_SIDE_LEFT, &fault, &monitor);
    
    printf("\n=== Setting speed to 0 km/h ===\n");
    mock_set_train_speed(0);
    safety_monitor_update(&monitor);
    
    printf("Safety monitor speed: %u (0.1 km/h units)\n", safety_monitor_get_speed(&monitor));
    printf("Is safe to open: %d\n", safety_monitor_is_safe_to_open(&monitor));
    printf("Should lock: %d\n", safety_monitor_should_lock(&monitor));
    
    printf("\n=== Sending OPEN command ===\n");
    door_fsm_process_event(&fsm, DOOR_EVENT_OPEN_CMD);
    
    printf("\n=== Updating FSM ===\n");
    door_fsm_update(&fsm);
    
    printf("Door state: %d (0=CLOSED, 1=OPENING, 2=OPEN, 6=FAULT)\n", door_fsm_get_state(&fsm));
    
    if (door_fsm_get_state(&fsm) == DOOR_STATE_OPENING) {
        printf("\n✓ PASS: Door opened successfully at 0 km/h\n");
        return 0;
    } else {
        printf("\n✗ FAIL: Door did not open (state=%d)\n", door_fsm_get_state(&fsm));
        return 1;
    }
}
