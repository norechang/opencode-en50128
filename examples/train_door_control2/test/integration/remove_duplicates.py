#!/usr/bin/env python3
import re

with open('software_integration_tests.c', 'r') as f:
    lines = f.readlines()

output_lines = []
prev_line_was_monitor_decl = False

for i, line in enumerate(lines):
    # Check if this line is a monitor declaration
    is_monitor_decl = bool(re.match(r'\s*safety_monitor_t\s+monitor;\s*$', line))
    
    if is_monitor_decl and prev_line_was_monitor_decl:
        # Skip duplicate
        continue
    
    output_lines.append(line)
    prev_line_was_monitor_decl = is_monitor_decl

with open('software_integration_tests.c', 'w') as f:
    f.writelines(output_lines)

print("Removed consecutive duplicate monitor declarations")
