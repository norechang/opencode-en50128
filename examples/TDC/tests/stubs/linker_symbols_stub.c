/**
 * @file    linker_symbols_stub.c
 * @brief   Stub definitions for linker-defined symbols used by SKN memory-
 *          integrity and stack-canary checks.  In production these symbols are
 *          provided by the linker script; here they are defined as normal C
 *          objects so that unit-test builds link without a special linker script.
 *
 * @project TDC (Train Door Control System) — Unit Test Build Support
 * @note    NOT safety software.  Test infrastructure only.
 */

#include <stdint.h>

/* ROM region stubs — skn_safe_state.c uses these for CRC check */
uint8_t  __rom_start__           = 0U;
uint8_t  __rom_end__             = 0U;
uint32_t __rom_expected_crc__    = 0U;

/* Stack sentinel stubs — skn_safe_state.c reads these for canary check */
uint32_t __stack_top_canary__    = 0xDEADBEEFU;
uint32_t __stack_bottom_canary__ = 0xDEADBEEFU;
