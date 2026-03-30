// Minimal test to debug TC-INT-2-001 failure
#include <stdio.h>
#include "../integration_mocks.h"
#include "../../../src/door_control/door_fsm.h"
#include "../../../src/actuator_hal/actuator_hal.h"
#include "../../../src/sensor_hal/sensor_hal.h"
#include "../../../src/safety_monitor/safety_monitor.h"
#include "../../../src/fault_detection/fault_detection.h"

int main() {
    mock_reset_all();
    actuator_hal_init();
    sensor_hal_init();
    
    door_fsm_t fsm;
    fault_detection_t fault;
    safety_monitor_t monitor;
    safety_monitor_init(&monitor);
    fault_detection_init(&fault);
    door_fsm_init(&fsm, DOOR_SIDE_LEFT, &fault, &monitor);
    
    printf("Initial state: fsm.current_state=%d, fsm.locked=%d\n", fsm.current_state, fsm.locked);
    
    mock_set_door_positions(0, 0);
    mock_set_train_speed(0);
    safety_monitor_update(&monitor);
    
    door_fsm_process_event(&fsm, DOOR_EVENT_OPEN_CMD);
    door_fsm_update(&fsm);
    
    printf("After OPEN command: state=%d, PWM=%d, locked=%d, position=%d%%\n", 
           door_fsm_get_state(&fsm), mock_left_door_pwm, fsm.locked, door_fsm_get_position(&fsm));
    
    for (int i = 0; i < 10; i++) {
        mock_advance_time(50);
        door_fsm_update(&fsm);
        if (i % 2 == 0) {
            printf("Cycle %3d: state=%d, PWM=%3d, position=%3d%%, ADC=%4d\n",
                   i, door_fsm_get_state(&fsm), mock_left_door_pwm, 
                   door_fsm_get_position(&fsm), mock_left_position_raw);
        }
        if (door_fsm_get_state(&fsm) == DOOR_STATE_OPEN) {
            printf("✓ Reached OPEN state at cycle %d\n", i);
            return 0;
        }
    }
    
    printf("✗ Did not reach OPEN after 10 cycles\n");
    printf("Final: state=%d, position=%d%%, ADC=%d\n", 
           door_fsm_get_state(&fsm), door_fsm_get_position(&fsm), mock_left_position_raw);
    
    return 1;
}
