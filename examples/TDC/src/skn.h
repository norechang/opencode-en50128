/**
 * @file    skn.h
 * @brief   Safety Kernel (SKN) public interface for TDC
 * @details Cross-channel comparator, safe-state manager, scheduler entry point,
 *          memory integrity, stack canary, and initialisation.
 *
 * @project TDC (Train Door Control System)
 * @module  SKN (Safety Kernel) — COMP-001
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety
 * SIL Level: 3
 * Safety Requirements: REQ-SAFE-002/007/008/009/010/012/014/015/018
 *
 * @requirements
 * - REQ-SAFE-002: 2oo2 cross-channel comparison
 * - REQ-SAFE-008: Safe state activation on mismatch
 * - REQ-SAFE-009: Memory integrity CRC-16 check
 * - REQ-SAFE-015: Scheduler cycle discipline
 *
 * @misra_compliance
 * MISRA C:2012 Compliance:
 * - All mandatory rules: Compliant
 * - Fixed-width types only
 * - No dynamic allocation
 * - No recursion
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §3
 */

#ifndef SKN_H
#define SKN_H

#include <stdint.h>
#include <stdbool.h>
#include "tdc_types.h"

/*============================================================================
 * GLOBAL SAFETY STATE (writable ONLY by SKN — architecture rule SAS §5.2)
 *===========================================================================*/

/** @brief Global safe-state flag; 1=safe state active. Written only by SKN. */
extern uint8_t g_safe_state_active;

/** @brief Global speed interlock flag; 1=door open inhibited. Written by SPM. */
extern uint8_t g_speed_interlock_active;

/** @brief Global obstacle flags per door. Written by OBD. */
extern uint8_t g_obstacle_flags[MAX_DOORS];

/*============================================================================
 * PUBLIC FUNCTION PROTOTYPES
 * Design ref: SCDS DOC-COMPDES-2026-001 §3
 *===========================================================================*/

/**
 * @brief Initialise the Safety Kernel module.
 * @details Sets all safety flags to fail-safe defaults, computes ROM and RAM
 *          CRC-16 snapshots, places stack canary values.
 * @return error_t SUCCESS
 * @note   UNIT-SKN-009; Complexity: 1
 */
error_t SKN_Init(void);

/**
 * @brief Top-level 20 ms cycle dispatcher.
 * @details Orchestrates all components in deterministic order. This function
 *          is called by the RTOS tick ISR or bare-metal main loop.
 * @note   UNIT-SKN-008; Complexity: 3
 */
void SKN_RunCycle(void);

/**
 * @brief Build local safety state structure with CRC-16-CCITT.
 * @param[out] state           Pointer to cross_channel_state_t to populate
 * @param[in]  speed_kmh_x10  Current speed from SPM (0–3000 or 0xFFFF=unknown)
 * @param[in]  door_states    Array of door states [MAX_DOORS]
 * @param[in]  lock_states    Array of lock states [MAX_DOORS]
 * @param[in]  obstacle_flags Array of obstacle flags [MAX_DOORS]
 * @param[in]  fault_flags    Fault bitmask from FMG
 * @param[in]  safety_decisions Bitmask (bit0=safe_state_active, bit1=interlock_ok)
 * @return error_t SUCCESS, ERR_NULL_PTR
 * @note   UNIT-SKN-001; Complexity: 2
 */
error_t SKN_BuildLocalState(cross_channel_state_t *state,
                            uint16_t speed_kmh_x10,
                            const uint8_t door_states[MAX_DOORS],
                            const uint8_t lock_states[MAX_DOORS],
                            const uint8_t obstacle_flags[MAX_DOORS],
                            uint8_t fault_flags,
                            uint8_t safety_decisions);

/**
 * @brief Exchange cross-channel state via SPI and compare safety fields.
 * @details Implements OI-FMEA-001 SPI transient filter (3-consecutive-fault
 *          confirmation before asserting safe state for infrastructure faults).
 *          CRC-16 failure on safety payload → immediate safe state.
 *          Field disagreement → immediate safe state.
 * @param[in]  local               Pointer to local state (must not be NULL)
 * @param[out] safe_state_active_out Set to 1 on mismatch or persistent fault
 * @return error_t SUCCESS, ERR_NULL_PTR, ERR_CRC, ERR_COMM_TIMEOUT, ERR_SENSOR_DISAGREE
 * @note   UNIT-SKN-002; Complexity: 7
 */
error_t SKN_ExchangeAndCompare(const cross_channel_state_t *local,
                               uint8_t *safe_state_active_out);

/**
 * @brief Evaluate safe-state triggers (sticky flag).
 * @param[in]  channel_disagree    1 if cross-channel mismatch detected
 * @param[in]  fault_state         Fault bitmask from FMG
 * @param[in]  memory_crc_ok       1 if memory CRC OK
 * @param[in]  stack_canary_ok     1 if stack canary intact
 * @param[out] safe_state_active_out Updated safe state value
 * @return error_t SUCCESS, ERR_NULL_PTR
 * @note   UNIT-SKN-004; Complexity: 5
 */
error_t SKN_EvaluateSafeState(uint8_t channel_disagree,
                              uint8_t fault_state,
                              uint8_t memory_crc_ok,
                              uint8_t stack_canary_ok,
                              uint8_t *safe_state_active_out);

/**
 * @brief Evaluate departure interlock (all doors CLOSED_AND_LOCKED).
 * @param[in]  door_states      Array of door states [MAX_DOORS]
 * @param[in]  lock_states      Array of lock states [MAX_DOORS]
 * @param[in]  channel_disagree Cross-channel disagreement flag
 * @param[in]  safe_state_active Safe state flag
 * @param[out] interlock_ok_out 1 if all doors locked, 0 otherwise
 * @return error_t SUCCESS, ERR_NULL_PTR
 * @note   UNIT-SKN-005; Complexity: 7
 */
error_t SKN_EvaluateDepartureInterlock(const uint8_t door_states[MAX_DOORS],
                                       const uint8_t lock_states[MAX_DOORS],
                                       uint8_t channel_disagree,
                                       uint8_t safe_state_active,
                                       uint8_t *interlock_ok_out);

/**
 * @brief Check ROM and safety-critical RAM CRC-16 integrity.
 * @param[out] crc_ok_out 1 if both CRC checks pass, 0 otherwise
 * @return error_t SUCCESS, ERR_NULL_PTR, ERR_CRC
 * @note   UNIT-SKN-006; Complexity: 4
 */
error_t SKN_CheckMemoryIntegrity(uint8_t *crc_ok_out);

/**
 * @brief Check stack canary values at top and bottom of stack.
 * @param[out] canary_ok_out 1 if canary intact, 0 if corrupted
 * @return error_t SUCCESS, ERR_NULL_PTR, ERR_HW_FAULT
 * @note   UNIT-SKN-007; Complexity: 3
 */
error_t SKN_CheckStackCanary(uint8_t *canary_ok_out);

/**
 * @brief Get current departure interlock status (accessor for TCI).
 * @return uint8_t 1 if departure interlock OK (all doors locked), 0 otherwise
 */
uint8_t SKN_GetDepartureInterlock(void);

#endif /* SKN_H */

/*============================================================================
 * END OF FILE
 *===========================================================================*/
