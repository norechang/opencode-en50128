/* =========================================================================
 * unity.h — Unity C Unit Test Framework v2.5.2 (minimal EN 50128 variant)
 * Copyright (c) 2007-14 Mike Karlesky, Mark VanderVoord, Greg Williams
 * SPDX-License-Identifier: MIT
 * =========================================================================*/
#ifndef UNITY_H
#define UNITY_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* -------------------------------------------------------------------------
 * Unity configuration
 * -------------------------------------------------------------------------*/
#define UNITY_COUNTER_TYPE   unsigned int
#define UNITY_LINE_TYPE      unsigned short
#define UNITY_FAIL_AND_BAIL  /* not set — continue all tests */

/* -------------------------------------------------------------------------
 * Internal types
 * -------------------------------------------------------------------------*/
typedef enum {
    UNITY_DISPLAY_STYLE_INT    = 0,
    UNITY_DISPLAY_STYLE_UINT   = 1,
    UNITY_DISPLAY_STYLE_HEX8   = 2,
    UNITY_DISPLAY_STYLE_HEX16  = 3,
    UNITY_DISPLAY_STYLE_HEX32  = 4
} UNITY_DISPLAY_STYLE_T;

struct UNITY_STORAGE_T {
    const char *TestFile;
    UNITY_LINE_TYPE CurrentTestLineNumber;
    UNITY_COUNTER_TYPE NumberOfTests;
    UNITY_COUNTER_TYPE TestFailures;
    UNITY_COUNTER_TYPE TestIgnores;
    unsigned char CurrentTestFailed;
    unsigned char CurrentTestIgnored;
};

extern struct UNITY_STORAGE_T Unity;

/* -------------------------------------------------------------------------
 * Public API macros
 * -------------------------------------------------------------------------*/
#define TEST_ASSERT(condition) \
    UnityAssertTrue((condition) ? 1 : 0, #condition, __LINE__)

#define TEST_ASSERT_TRUE(condition)   UnityAssertTrue((condition) ? 1 : 0, #condition, __LINE__)
#define TEST_ASSERT_FALSE(condition)  UnityAssertTrue((condition) ? 0 : 1, "!" #condition, __LINE__)
#define TEST_ASSERT_NULL(ptr)         UnityAssertTrue((ptr) == NULL ? 1 : 0, #ptr " is not NULL", __LINE__)
#define TEST_ASSERT_NOT_NULL(ptr)     UnityAssertTrue((ptr) != NULL ? 1 : 0, #ptr " is NULL", __LINE__)

#define TEST_ASSERT_EQUAL_INT(expected, actual) \
    UnityAssertEqualInt((int)(expected), (int)(actual), __LINE__)

#define TEST_ASSERT_EQUAL_UINT(expected, actual) \
    UnityAssertEqualUInt((unsigned)(expected), (unsigned)(actual), __LINE__)

#define TEST_ASSERT_EQUAL_UINT8(expected, actual) \
    UnityAssertEqualUInt((unsigned)(expected), (unsigned)(actual), __LINE__)

#define TEST_ASSERT_EQUAL_UINT16(expected, actual) \
    UnityAssertEqualUInt((unsigned)(expected), (unsigned)(actual), __LINE__)

#define TEST_ASSERT_EQUAL_UINT32(expected, actual) \
    UnityAssertEqualUInt((unsigned)(expected), (unsigned)(actual), __LINE__)

#define TEST_ASSERT_EQUAL_HEX16(expected, actual) \
    UnityAssertEqualHex16((uint16_t)(expected), (uint16_t)(actual), __LINE__)

#define TEST_ASSERT_EQUAL(expected, actual) \
    UnityAssertEqualInt((int)(expected), (int)(actual), __LINE__)

#define TEST_ASSERT_NOT_EQUAL(expected, actual) \
    UnityAssertTrue((int)(expected) != (int)(actual), \
        "Expected " #expected " != " #actual, __LINE__)
#define TEST_FAIL()               UnityFail("Test failed", __LINE__)
#define TEST_IGNORE()             UnityIgnore(__LINE__)
#define TEST_IGNORE_MESSAGE(msg)  UnityIgnore(__LINE__)

/* -------------------------------------------------------------------------
 * Test runner macros
 * -------------------------------------------------------------------------*/
#define UNITY_BEGIN()  UnityBegin(__FILE__)
#define UNITY_END()    UnityEnd()

#define RUN_TEST(func) do { \
    Unity.CurrentTestLineNumber = __LINE__; \
    UnityDefaultTestRun(func, #func, __LINE__); \
} while (0)

/* -------------------------------------------------------------------------
 * Function prototypes
 * -------------------------------------------------------------------------*/
void UnityBegin(const char *filename);
int  UnityEnd(void);
void UnityDefaultTestRun(void (*Func)(void), const char *FuncName, int FuncLineNum);
void UnityAssertTrue(int condition, const char *msg, unsigned short line);
void UnityAssertEqualInt(int expected, int actual, unsigned short line);
void UnityAssertEqualUInt(unsigned expected, unsigned actual, unsigned short line);
void UnityAssertEqualHex16(uint16_t expected, uint16_t actual, unsigned short line);
void UnityFail(const char *msg, unsigned short line);
void UnityIgnore(unsigned short line);

/* -------------------------------------------------------------------------
 * setUp / tearDown declarations (user provides per test file)
 * -------------------------------------------------------------------------*/
extern void setUp(void);
extern void tearDown(void);

#endif /* UNITY_H */
