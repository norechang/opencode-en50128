#!/usr/bin/env python3
import re

with open('software_integration_tests.c', 'r') as f:
    lines = f.readlines()

# Find all functions that use door_fsm_init
functions_needing_monitor = set()
current_function = None

for i, line in enumerate(lines):
    if re.match(r'^static bool (tc_int_\w+)\(void\)', line):
        current_function = re.match(r'^static bool (tc_int_\w+)\(void\)', line).group(1)
    if current_function and 'door_fsm_init(' in line and '&monitor' in line:
        functions_needing_monitor.add(current_function)

print(f"Functions needing monitor: {len(functions_needing_monitor)}")

# Now add monitor declarations
output_lines = []
current_function = None
monitor_added = False

for i, line in enumerate(lines):
    if re.match(r'^static bool (tc_int_\w+)\(void\)', line):
        current_function = re.match(r'^static bool (tc_int_\w+)\(void\)', line).group(1)
        monitor_added = False
    
    output_lines.append(line)
    
    # Check if we need to add monitor after fault_detection_t declaration
    if (current_function in functions_needing_monitor and 
        not monitor_added and 
        'fault_detection_t fault;' in line and
        'safety_monitor_t' not in line):
        # Check if next line already has monitor
        if i+1 < len(lines) and 'safety_monitor_t monitor' not in lines[i+1]:
            indent = re.match(r'(\s*)', line).group(1)
            output_lines.append(f'{indent}safety_monitor_t monitor;\n')
            monitor_added = True

with open('software_integration_tests.c', 'w') as f:
    f.writelines(output_lines)

print("Added monitor declarations to functions that need them")
