#!/usr/bin/env python3
import re

with open('software_integration_tests.c', 'r') as f:
    lines = f.readlines()

output_lines = []

for i, line in enumerate(lines):
    output_lines.append(line)
    
    # If this is door_fsm_init with &fault, ensure fault_detection_init was called
    if 'door_fsm_init(' in line and '&fault' in line:
        # Search backwards for fault_detection_init
        found_init = False
        for j in range(max(0, i-20), i):
            if 'fault_detection_init(&fault)' in lines[j]:
                found_init = True
                break
        
        if not found_init:
            # Add fault_detection_init before this line
            indent = re.match(r'(\s*)', line).group(1)
            output_lines.insert(-1, f'{indent}fault_detection_init(&fault);\n')

with open('software_integration_tests.c', 'w') as f:
    f.writelines(output_lines)

print("Added fault_detection_init calls")
