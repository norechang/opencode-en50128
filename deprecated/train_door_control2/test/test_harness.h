/**
 * @file test_harness.h
 * @brief Lightweight test harness for SIL 3 unit testing
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.5, Table A.21
 * 
 * @description
 * Simple unit test framework for embedded C testing. Provides assertions,
 * test execution, and pass/fail reporting suitable for SIL 3 requirements.
 * 
 * Alternative to Unity framework - self-contained and portable.
 */

#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

/*===========================================================================*/
/* Test Result Tracking                                                      */
/*===========================================================================*/

/** Global test failure counter */
extern int test_failures;

/** Global test pass counter */
extern int test_passes;

/** Current test name (for debugging) */
extern const char* current_test_name;

/*===========================================================================*/
/* Test Assertions                                                           */
/*===========================================================================*/

/**
 * @brief Assert condition is true
 * @param condition Boolean condition to test
 * @return true if pass, false if fail
 */
#define TEST_ASSERT(condition) \
    do { \
        if (!(condition)) { \
            printf("  FAIL: %s:%d - Assertion failed: %s\n", \
                   __FILE__, __LINE__, #condition); \
            test_failures++; \
            return false; \
        } \
    } while(0)

/**
 * @brief Assert two values are equal
 * @param expected Expected value
 * @param actual Actual value
 */
#define TEST_ASSERT_EQUAL(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            printf("  FAIL: %s:%d - Expected %d, got %d\n", \
                   __FILE__, __LINE__, (int)(expected), (int)(actual)); \
            test_failures++; \
            return false; \
        } \
    } while(0)

/**
 * @brief Assert two values are equal (unsigned)
 */
#define TEST_ASSERT_EQUAL_UINT(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            printf("  FAIL: %s:%d - Expected %u, got %u\n", \
                   __FILE__, __LINE__, (unsigned)(expected), (unsigned)(actual)); \
            test_failures++; \
            return false; \
        } \
    } while(0)

/**
 * @brief Assert two values are equal (pointers)
 */
#define TEST_ASSERT_EQUAL_PTR(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            printf("  FAIL: %s:%d - Expected ptr %p, got %p\n", \
                   __FILE__, __LINE__, (void*)(expected), (void*)(actual)); \
            test_failures++; \
            return false; \
        } \
    } while(0)

/**
 * @brief Assert pointer is NULL
 */
#define TEST_ASSERT_NULL(ptr) \
    TEST_ASSERT_EQUAL_PTR(NULL, ptr)

/**
 * @brief Assert pointer is NOT NULL
 */
#define TEST_ASSERT_NOT_NULL(ptr) \
    do { \
        if ((ptr) == NULL) { \
            printf("  FAIL: %s:%d - Expected non-NULL pointer\n", \
                   __FILE__, __LINE__); \
            test_failures++; \
            return false; \
        } \
    } while(0)

/**
 * @brief Assert boolean is true
 */
#define TEST_ASSERT_TRUE(condition) \
    TEST_ASSERT(condition)

/**
 * @brief Assert boolean is false
 */
#define TEST_ASSERT_FALSE(condition) \
    TEST_ASSERT(!(condition))

/**
 * @brief Assert two memory blocks are equal
 */
#define TEST_ASSERT_EQUAL_MEMORY(expected, actual, size) \
    do { \
        if (memcmp((expected), (actual), (size)) != 0) { \
            printf("  FAIL: %s:%d - Memory comparison failed\n", \
                   __FILE__, __LINE__); \
            test_failures++; \
            return false; \
        } \
    } while(0)

/*===========================================================================*/
/* Test Execution Functions                                                  */
/*===========================================================================*/

/**
 * @brief Run a single test case
 * @param name Test case name (for reporting)
 * @param test_func Test function pointer (returns true on pass)
 * @return true if test passed, false otherwise
 */
bool run_test(const char* name, bool (*test_func)(void));

/**
 * @brief Print test suite header
 * @param suite_name Name of test suite (module name)
 */
void test_suite_begin(const char* suite_name);

/**
 * @brief Print test suite footer with summary
 * @param suite_name Name of test suite
 * @param tests_in_suite Number of tests in this suite
 */
void test_suite_end(const char* suite_name, int tests_in_suite);

/**
 * @brief Reset test counters (call at start of test run)
 */
void test_reset_counters(void);

/**
 * @brief Print final test summary
 */
void test_print_summary(void);

#endif /* TEST_HARNESS_H */
