// Minimal debug - just test FSM init
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// Check FSM locked state after init
typedef struct {
    uint8_t current_state;
    bool locked;
} door_fsm_test_t;

int main() {
    // Simulate FSM init setting locked = true
    door_fsm_test_t fsm;
    fsm.locked = true;  // After our INT-006 fix
    
    printf("FSM init: locked = %d\n", fsm.locked);
    
    // Simulate transition_to_opening check
    if (fsm.locked) {
        printf("FSM will call actuator_hal_set_door_lock(false)\n");
        fsm.locked = false;
    } else {
        printf("ERROR: FSM thinks door is already unlocked, won't disengage!\n");
    }
    
    printf("After transition: locked = %d\n", fsm.locked);
    
    return 0;
}
