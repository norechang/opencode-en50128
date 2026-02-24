/**
 * @file run_hal_tests.c
 * @brief Test runner for MOD-006, MOD-007, MOD-008 (HAL modules)
 *
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.5, Table A.21
 * @traceability DOC-COMPTEST-2026-001 v1.0
 *
 * @description
 * Separate binary for the three hardware abstraction layer modules:
 *   MOD-006 actuator_hal       — GPIO/PWM output abstraction
 *   MOD-007 sensor_hal         — position/speed/obstacle sensor abstraction
 *   MOD-008 communication_hal  — CAN/UART abstraction
 *
 * Hardware dependencies (GPIO, CAN, UART) are provided by test_mocks.c.
 * No stubs for inter-module functions are needed here.
 */

#include "test_harness.h"
#include <stdio.h>

extern void run_actuator_hal_tests(void);      /* MOD-006 */
extern void run_sensor_hal_tests(void);        /* MOD-007 */
extern void run_communication_hal_tests(void); /* MOD-008 */

int main(void)
{
    printf("\n");
    printf("================================================================================\n");
    printf(" MOD-006,007,008: HAL MODULES TEST EXECUTION (SIL 3)                          \n");
    printf("================================================================================\n");
    printf("Project: train_door_control2 | SIL: 3 | Spec: DOC-COMPTEST-2026-001 v1.0\n");
    printf("================================================================================\n\n");

    test_reset_counters();

    run_communication_hal_tests();  /* MOD-008 — MUST run first (not-initialized paths) */
    run_sensor_hal_tests();         /* MOD-007 — runs after comm_hal init'd */
    run_actuator_hal_tests();       /* MOD-006 */

    test_print_summary();

    return (test_failures == 0) ? 0 : 1;
}
