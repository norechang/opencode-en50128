/**
 * @file run_modules_tests.c
 * @brief Test runner for MOD-002, MOD-004, MOD-005 (modules with simplified externs)
 *
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.5, Table A.21
 * @traceability DOC-COMPTEST-2026-001 v1.0
 *
 * @description
 * Separate binary for modules that use simplified private extern declarations:
 *   MOD-002 safety_monitor    — uses sensor_hal_read_speed + fault_detection_report_fault (2-param)
 *   MOD-004 command_processor — uses door_fsm_process_event (void*) + fault_detection_report_fault (2-param)
 *   MOD-005 status_reporter   — uses door_fsm_get_state/position/locked (side-based) + fault_detection_get_active_faults (void*)
 *
 * These simplified interfaces are incompatible with the real module header
 * signatures, so this binary does NOT link the real fault_detection.c,
 * sensor_hal.c, communication_hal.c, or door_fsm.c.  Stubs with the
 * matching simplified signatures are provided by the test files themselves.
 */

#include "test_harness.h"
#include <stdio.h>

extern void run_safety_monitor_tests(void);     /* MOD-002 */
extern void run_command_processor_tests(void);  /* MOD-004 */
extern void run_status_reporter_tests(void);    /* MOD-005 */

int main(void)
{
    printf("\n");
    printf("================================================================================\n");
    printf(" MOD-002,004,005: MODULES TEST EXECUTION (SIL 3)                               \n");
    printf("================================================================================\n");
    printf("Project: train_door_control2 | SIL: 3 | Spec: DOC-COMPTEST-2026-001 v1.0\n");
    printf("================================================================================\n\n");

    test_reset_counters();

    run_safety_monitor_tests();        /* MOD-002 */
    run_command_processor_tests();     /* MOD-004 */
    run_status_reporter_tests();       /* MOD-005 */

    test_print_summary();

    return (test_failures == 0) ? 0 : 1;
}
