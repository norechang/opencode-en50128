#!/usr/bin/env python3
import re

with open('software_integration_tests.c', 'r') as f:
    lines = f.readlines()

output_lines = []
in_function = False
monitor_declared_in_function = False
function_start_line = 0

for i, line in enumerate(lines):
    # Track function boundaries
    if re.match(r'^static bool tc_int_', line):
        in_function = True
        monitor_declared_in_function = False
        function_start_line = i
        output_lines.append(line)
        continue
    
    # Track function end
    if in_function and line.strip() == '}' and i > function_start_line + 5:
        in_function = False
        monitor_declared_in_function = False
        output_lines.append(line)
        continue
    
    # Check for duplicate safety_monitor_t monitor
    if 'safety_monitor_t monitor;' in line:
        if monitor_declared_in_function:
            # Skip duplicate
            continue
        else:
            monitor_declared_in_function = True
            output_lines.append(line)
            continue
    
    output_lines.append(line)

with open('software_integration_tests.c', 'w') as f:
    f.writelines(output_lines)

print("Cleaned up duplicate monitor declarations")
