/* =========================================================================
 * unity.c — Unity C Unit Test Framework v2.5.2 (minimal EN 50128 variant)
 * Copyright (c) 2007-14 Mike Karlesky, Mark VanderVoord, Greg Williams
 * SPDX-License-Identifier: MIT
 * =========================================================================*/

#include "unity.h"
#include <stdio.h>
#include <string.h>

/* Global Unity state */
struct UNITY_STORAGE_T Unity;

void UnityBegin(const char *filename)
{
    Unity.TestFile           = filename;
    Unity.NumberOfTests      = 0;
    Unity.TestFailures       = 0;
    Unity.TestIgnores        = 0;
    Unity.CurrentTestFailed  = 0;
    Unity.CurrentTestIgnored = 0;
    printf("\n-----------------------\n");
    printf("Running: %s\n\n", filename);
}

int UnityEnd(void)
{
    unsigned int pass = Unity.NumberOfTests - Unity.TestFailures - Unity.TestIgnores;
    printf("\n-----------------------\n");
    printf("%u Tests %u Failures %u Ignored\n",
           Unity.NumberOfTests, Unity.TestFailures, Unity.TestIgnores);
    if (Unity.TestFailures == 0U) {
        printf("OK\n");
    } else {
        printf("FAIL\n");
    }
    printf("-----------------------\n\n");
    return (int)Unity.TestFailures;
}

void UnityDefaultTestRun(void (*Func)(void), const char *FuncName, int FuncLineNum)
{
    (void)FuncLineNum;
    Unity.NumberOfTests++;
    Unity.CurrentTestFailed  = 0;
    Unity.CurrentTestIgnored = 0;
    setUp();
    Func();
    tearDown();
    if (Unity.CurrentTestIgnored != 0) {
        Unity.TestIgnores++;
        printf("%s:%u:IGNORE\n", Unity.TestFile, (unsigned)Unity.CurrentTestLineNumber);
    } else if (Unity.CurrentTestFailed != 0) {
        Unity.TestFailures++;
        /* failure message already printed */
    } else {
        printf("%s:%s:PASS\n", Unity.TestFile, FuncName);
    }
}

void UnityAssertTrue(int condition, const char *msg, unsigned short line)
{
    if (!condition) {
        Unity.CurrentTestFailed = 1;
        printf("%s:%u:FAIL: Expected TRUE Was FALSE: %s\n",
               Unity.TestFile, (unsigned)line, msg);
    }
}

void UnityAssertEqualInt(int expected, int actual, unsigned short line)
{
    if (expected != actual) {
        Unity.CurrentTestFailed = 1;
        printf("%s:%u:FAIL: Expected %d Was %d\n",
               Unity.TestFile, (unsigned)line, expected, actual);
    }
}

void UnityAssertEqualUInt(unsigned expected, unsigned actual, unsigned short line)
{
    if (expected != actual) {
        Unity.CurrentTestFailed = 1;
        printf("%s:%u:FAIL: Expected %u Was %u\n",
               Unity.TestFile, (unsigned)line, expected, actual);
    }
}

void UnityAssertEqualHex16(uint16_t expected, uint16_t actual, unsigned short line)
{
    if (expected != actual) {
        Unity.CurrentTestFailed = 1;
        printf("%s:%u:FAIL: Expected 0x%04X Was 0x%04X\n",
               Unity.TestFile, (unsigned)line, (unsigned)expected, (unsigned)actual);
    }
}

void UnityFail(const char *msg, unsigned short line)
{
    Unity.CurrentTestFailed = 1;
    printf("%s:%u:FAIL: %s\n", Unity.TestFile, (unsigned)line, msg);
}

void UnityIgnore(unsigned short line)
{
    Unity.CurrentTestIgnored = 1;
    Unity.CurrentTestLineNumber = line;
}
