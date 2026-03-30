/**
 * @file run_fault_tests.c
 * @brief Test runner for MOD-003 (fault_detection) — isolated binary
 *
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.5, Table A.21
 * @traceability DOC-COMPTEST-2026-001 v1.0
 *
 * @description
 * fault_detection.c uses the real 3-param fault_detection_report_fault
 * signature and has no conflicting extern dependencies.  This binary tests
 * fault_detection.c in isolation from other modules.
 */

#include "test_harness.h"
#include <stdio.h>

extern void run_fault_detection_tests(void);  /* MOD-003 */

int main(void)
{
    printf("\n");
    printf("================================================================================\n");
    printf(" MOD-003: FAULT DETECTION — COMPONENT UNIT TEST EXECUTION (SIL 3)              \n");
    printf("================================================================================\n");
    printf("Project: train_door_control2 | SIL: 3 | Spec: DOC-COMPTEST-2026-001 v1.0\n");
    printf("================================================================================\n\n");

    test_reset_counters();

    run_fault_detection_tests();  /* MOD-003 */

    test_print_summary();

    return (test_failures == 0) ? 0 : 1;
}
