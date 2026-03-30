#!/usr/bin/env python3
import re

with open('software_integration_tests.c', 'r') as f:
    content = f.read()

# Pattern 1: door_fsm_init calls with 3 parameters (need to add 4th)
# Replace: door_fsm_init(&fsm, DOOR_SIDE_LEFT, &fault)
# With: door_fsm_init(&fsm, DOOR_SIDE_LEFT, &fault, &monitor)
# Similar for DOOR_SIDE_RIGHT, left_fsm, right_fsm

pattern1 = r'door_fsm_init\((&\w+), (DOOR_SIDE_\w+), (&\w+)\)'
replacement1 = r'door_fsm_init(\1, \2, \3, &monitor)'

content = re.sub(pattern1, replacement1, content)

with open('software_integration_tests.c', 'w') as f:
    f.write(content)

print("Updated all door_fsm_init calls")
