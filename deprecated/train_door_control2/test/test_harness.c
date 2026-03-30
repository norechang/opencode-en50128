/**
 * @file test_harness.c
 * @brief Lightweight test harness implementation
 */

#include "test_harness.h"

/*===========================================================================*/
/* Global Variables                                                          */
/*===========================================================================*/

int test_failures = 0;
int test_passes = 0;
const char* current_test_name = NULL;

/*===========================================================================*/
/* Test Execution Functions                                                  */
/*===========================================================================*/

bool run_test(const char* name, bool (*test_func)(void)) {
    current_test_name = name;
    printf("  [TEST] %s ... ", name);
    fflush(stdout);
    
    bool result = test_func();
    
    if (result) {
        printf("PASS\n");
        test_passes++;
    } else {
        /* Failure details already printed by assertions */
    }
    
    return result;
}

void test_suite_begin(const char* suite_name) {
    printf("\n========================================\n");
    printf("Test Suite: %s\n", suite_name);
    printf("========================================\n");
}

void test_suite_end(const char* suite_name, int tests_in_suite) {
    printf("----------------------------------------\n");
    printf("Suite %s: %d tests completed\n", suite_name, tests_in_suite);
    printf("========================================\n\n");
}

void test_reset_counters(void) {
    test_failures = 0;
    test_passes = 0;
}

void test_print_summary(void) {
    int total = test_passes + test_failures;
    double pass_rate = (total > 0) ? (100.0 * test_passes / total) : 0.0;
    
    printf("\n");
    printf("================================================================================\n");
    printf("                          TEST EXECUTION SUMMARY                                \n");
    printf("================================================================================\n");
    printf("Total tests:    %d\n", total);
    printf("Passed:         %d\n", test_passes);
    printf("Failed:         %d\n", test_failures);
    printf("Pass rate:      %.1f%%\n", pass_rate);
    printf("================================================================================\n");
    
    if (test_failures == 0) {
        printf("STATUS: ALL TESTS PASSED ✓\n");
    } else {
        printf("STATUS: %d TESTS FAILED ✗\n", test_failures);
    }
    printf("================================================================================\n");
}
