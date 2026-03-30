#!/usr/bin/env python3
import re

with open('software_integration_tests.c', 'r') as f:
    lines = f.readlines()

output_lines = []
i = 0
while i < len(lines):
    output_lines.append(lines[i])
    
    # If we find door_fsm_init call, check if safety_monitor_init was called before it
    if 'door_fsm_init(' in lines[i] and 'monitor' in lines[i]:
        # Search backwards for safety_monitor_init
        has_init = False
        for j in range(max(0, i-15), i):
            if 'safety_monitor_init' in lines[j]:
                has_init = True
                break
        
        if not has_init:
            # Add init before door_fsm_init
            indent = re.match(r'(\s*)', lines[i]).group(1)
            output_lines.insert(-1, f'{indent}safety_monitor_init(&monitor);\n')
    
    i += 1

with open('software_integration_tests.c', 'w') as f:
    f.writelines(output_lines)

print("Added missing safety_monitor_init calls")
