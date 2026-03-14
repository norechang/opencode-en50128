#!/usr/bin/env python3
import re

with open('software_integration_tests.c', 'r') as f:
    lines = f.readlines()

output_lines = []
i = 0
while i < len(lines):
    output_lines.append(lines[i])
    
    # If we find a fault_detection_t declaration, check if monitor is missing
    if re.match(r'\s*fault_detection_t\s+fault;', lines[i]):
        # Check next few lines for safety_monitor_t
        has_monitor = False
        for j in range(i+1, min(i+5, len(lines))):
            if 'safety_monitor_t' in lines[j]:
                has_monitor = True
                break
        
        if not has_monitor:
            # Add monitor declaration
            indent = re.match(r'(\s*)', lines[i]).group(1)
            output_lines.append(f'{indent}safety_monitor_t monitor;\n')
    
    i += 1

with open('software_integration_tests.c', 'w') as f:
    f.writelines(output_lines)

print("Added missing safety_monitor_t declarations")
