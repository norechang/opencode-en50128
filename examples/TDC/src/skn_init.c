/**
 * @file    skn_init.c
 * @brief   SKN Initialisation — UNIT-SKN-009 SKN_Init.
 * @details Initialises all SKN sub-modules, takes CRC snapshots, and
 *          places stack canary values. Called once at system startup
 *          before the scheduler starts.
 *
 * @project TDC (Train Door Control System)
 * @module  SKN (Safety Kernel) — MOD-SKN-004
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-009/015, SW-HAZ-008
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §3.4
 */

/* Implements: REQ-SAFE-009/015, UNIT-SKN-009 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §3.4 (MOD-SKN-004) */

#include <stdint.h>

#include "skn.h"
#include "hal.h"
#include "tdc_types.h"

/*============================================================================
 * EXTERNAL LINKER SYMBOLS — defined/resolved by skn_safe_state.c
 * Declared extern here to permit initialisation from this TU.
 *===========================================================================*/
extern void SKN_SafeState_Init(void);

/* Linker-provided symbols for ROM region */
extern uint8_t  __rom_start__;
extern uint8_t  __rom_end__;
extern uint16_t __rom_expected_crc__;

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS
 *===========================================================================*/

/**
 * @brief Initialise the Safety Kernel module.
 * @complexity Cyclomatic complexity: 1 — within SIL 3 limit of 10
 */
error_t SKN_Init(void)
{
    /* Implements: REQ-SAFE-009/015, UNIT-SKN-009 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §3.4.1 */
    uint16_t rom_len;

    /* Initialise safe-state sub-module (clears flags, takes RAM CRC snapshot,
     * places stack canary values) */
    SKN_SafeState_Init();

    /* Compute ROM CRC-16 snapshot for integrity checking.
     * Use uintptr_t arithmetic (not pointer subtraction) to avoid MISRA
     * Rule 18.2 / cppcheck comparePointers on extern linker symbols. */
    rom_len = (uint16_t)((uintptr_t)&__rom_end__ - (uintptr_t)&__rom_start__);
    __rom_expected_crc__ = CRC16_CCITT_Compute(&__rom_start__, rom_len);

    return SUCCESS;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
