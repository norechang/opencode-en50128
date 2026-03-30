#!/usr/bin/env python3
import re

with open('software_integration_tests.c', 'r') as f:
    lines = f.readlines()

output_lines = []
in_function = False
monitor_seen_in_function = False

for i, line in enumerate(lines):
    # Detect function start
    if re.match(r'^static bool tc_int_', line):
        in_function = True
        monitor_seen_in_function = False
        output_lines.append(line)
        continue
    
    # Detect function end
    if in_function and line.strip() == '}' and i > 10:
        # Check if this is likely the function end (not just an if block)
        # by checking if we're at the right indentation level
        if not line.startswith('    '):
            in_function = False
            monitor_seen_in_function = False
    
    # Check for monitor declaration within function
    if in_function and re.match(r'\s*safety_monitor_t\s+monitor;\s*$', line):
        if monitor_seen_in_function:
            # Skip duplicate
            continue
        monitor_seen_in_function = True
    
    output_lines.append(line)

with open('software_integration_tests.c', 'w') as f:
    f.writelines(output_lines)

print("Removed duplicate monitor declarations within functions")
