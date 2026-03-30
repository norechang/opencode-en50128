/**
 * @file run_fsm_tests.c
 * @brief Test runner for Door Control FSM (MOD-001) — separate binary
 *
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.5, Table A.21
 * @traceability DOC-COMPTEST-2026-001 v1.0
 *
 * @description
 * Separate test binary for MOD-001 (door_fsm.c).  door_fsm.c uses private
 * extern declarations with simplified signatures that are incompatible with
 * the real module headers.  Isolating it in its own binary avoids linker
 * multiple-definition errors while still generating gcov coverage data.
 */

#include "test_harness.h"
#include <stdio.h>

/* MOD-001 test suite */
extern void run_door_fsm_tests(void);  /* 32 tests — defined in test_door_fsm.c */

int main(void)
{
    printf("\n");
    printf("================================================================================\n");
    printf(" MOD-001: DOOR CONTROL FSM — COMPONENT UNIT TEST EXECUTION (SIL 3)             \n");
    printf("================================================================================\n");
    printf("Project: train_door_control2\n");
    printf("SIL Level: 3\n");
    printf("Test Specification: DOC-COMPTEST-2026-001 v1.0 Section 3.1\n");
    printf("================================================================================\n\n");

    test_reset_counters();

    run_door_fsm_tests();  /* MOD-001 */

    test_print_summary();

    return (test_failures == 0) ? 0 : 1;
}
