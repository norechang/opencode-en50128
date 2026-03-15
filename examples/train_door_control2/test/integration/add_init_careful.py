#!/usr/bin/env python3
import re

with open('software_integration_tests.c', 'r') as f:
    lines = f.readlines()

output_lines = []

for i, line in enumerate(lines):
    output_lines.append(line)
    
    # If this is door_fsm_init with &monitor, ensure safety_monitor_init was called
    if 'door_fsm_init(' in line and '&monitor' in line:
        # Search backwards for safety_monitor_init
        found_init = False
        for j in range(max(0, i-20), i):
            if 'safety_monitor_init(&monitor)' in lines[j]:
                found_init = True
                break
        
        if not found_init:
            # Add safety_monitor_init before this line
            indent = re.match(r'(\s*)', line).group(1)
            output_lines.insert(-1, f'{indent}safety_monitor_init(&monitor);\n')

with open('software_integration_tests.c', 'w') as f:
    f.writelines(output_lines)

print("Added safety_monitor_init calls")
