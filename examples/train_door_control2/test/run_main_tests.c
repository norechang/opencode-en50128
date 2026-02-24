/**
 * @file run_main_tests.c
 * @brief Main test runner for MOD-002 through MOD-008
 *
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.5, Table A.21
 * @traceability DOC-COMPTEST-2026-001 v1.0
 *
 * @description
 * Executes unit tests for 7 modules (MOD-002 .. MOD-008).
 * MOD-001 (door_fsm) is tested in a separate binary (test_fsm_runner)
 * because door_fsm.c uses simplified private extern declarations that are
 * signature-incompatible with the real module headers.
 *
 * SIL 3 Requirements:
 *   - Statement Coverage: 100% (MANDATORY)
 *   - Branch Coverage:    100% (MANDATORY)
 *   - Condition Coverage: 100% (MANDATORY)
 *   - Test Pass Rate:     100% (all tests must PASS)
 */

#include "test_harness.h"
#include <stdio.h>

/* External test suite runners */
extern void run_safety_monitor_tests(void);     /* MOD-002 */
extern void run_fault_detection_tests(void);    /* MOD-003 */
extern void run_command_processor_tests(void);  /* MOD-004 */
extern void run_status_reporter_tests(void);    /* MOD-005 */
extern void run_actuator_hal_tests(void);       /* MOD-006 */
extern void run_sensor_hal_tests(void);         /* MOD-007 */
extern void run_communication_hal_tests(void);  /* MOD-008 */

int main(void)
{
    printf("\n");
    printf("================================================================================\n");
    printf(" MOD-002..008: TRAIN DOOR CONTROL — COMPONENT UNIT TEST EXECUTION (SIL 3)      \n");
    printf("================================================================================\n");
    printf("Project: train_door_control2\n");
    printf("SIL Level: 3\n");
    printf("Test Specification: DOC-COMPTEST-2026-001 v1.0\n");
    printf("Test Report: DOC-COMPTESTRPT-2026-001 v1.0\n");
    printf("Date: 2026-02-24\n");
    printf("================================================================================\n\n");
    printf("EN 50128 SIL 3 Testing Requirements:\n");
    printf("  - Statement Coverage: 100%% (MANDATORY)\n");
    printf("  - Branch Coverage:    100%% (MANDATORY)\n");
    printf("  - Condition Coverage: 100%% (MANDATORY)\n");
    printf("  - Test Pass Rate:     100%% (all tests must PASS)\n\n");
    printf("================================================================================\n");

    test_reset_counters();

    run_safety_monitor_tests();        /* MOD-002 */
    run_fault_detection_tests();       /* MOD-003 */
    run_command_processor_tests();     /* MOD-004 */
    run_status_reporter_tests();       /* MOD-005 */
    run_actuator_hal_tests();          /* MOD-006 */
    run_sensor_hal_tests();            /* MOD-007 */
    run_communication_hal_tests();     /* MOD-008 */

    test_print_summary();

    return (test_failures == 0) ? 0 : 1;
}
