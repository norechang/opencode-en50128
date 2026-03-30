#!/usr/bin/env python3
import re

with open('software_integration_tests.c', 'r') as f:
    content = f.read()

# Split into functions
functions = re.split(r'(static bool tc_int_\w+\(void\) \{[^}]*\})', content, flags=re.DOTALL)

output = []
for part in functions:
    if 'static bool tc_int_' in part and '{' in part:
        # This is a function body
        # Check if it has door_fsm_init
        if 'door_fsm_init' not in part:
            # Remove safety_monitor_t monitor; if present
            part = re.sub(r'\s*safety_monitor_t monitor;\n', '', part)
        output.append(part)
    else:
        output.append(part)

with open('software_integration_tests.c', 'w') as f:
    f.write(''.join(output))

print("Removed unused monitor declarations")
