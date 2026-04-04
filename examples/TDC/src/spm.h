/**
 * @file    spm.h
 * @brief   Speed Monitor (SPM) public interface for TDC
 * @details CAN speed reception, CRC-16 validation, sequence counter check,
 *          speed interlock evaluation, and cycle entry.
 *
 * @project TDC (Train Door Control System)
 * @module  SPM (Speed Monitor) — COMP-002
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety
 * SIL Level: 3
 * Safety Requirements: REQ-SAFE-001/002/003/016, REQ-PERF-002, SW-HAZ-001/007
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §4
 */

#ifndef SPM_H
#define SPM_H

#include <stdint.h>
#include "tdc_types.h"

/**
 * @brief Initialise the Speed Monitor module to fail-safe defaults.
 * @return error_t SUCCESS
 * @note   UNIT-SPM-003; Complexity: 1
 */
error_t SPM_Init(void);

/**
 * @brief 20 ms cycle entry — fetch latest CAN frame and evaluate interlock.
 * @note   UNIT-SPM-004; Complexity: 2
 */
void SPM_RunCycle(void);

/**
 * @brief Process a received CAN speed frame (validate CRC-16, seq counter, range).
 * @param[in] msg         Pointer to received TCMS speed message (must not be NULL)
 * @param[in] timestamp_ms Current system tick at time of reception
 * @return error_t SUCCESS, ERR_NULL_PTR, ERR_CRC, ERR_RANGE
 * @note   UNIT-SPM-001; Complexity: 6
 */
error_t SPM_ProcessSpeedFrame(const tcms_speed_msg_t *msg,
                              uint32_t timestamp_ms);

/**
 * @brief Evaluate speed interlock based on current speed and CAN data freshness.
 * @param[in]  current_time_ms Current system tick in milliseconds
 * @param[out] interlock_active_out 1 if interlock active (door open inhibited)
 * @return error_t SUCCESS, ERR_NULL_PTR
 * @note   UNIT-SPM-002; Complexity: 5
 */
error_t SPM_EvaluateInterlock(uint32_t current_time_ms,
                              uint8_t *interlock_active_out);

/**
 * @brief Get current speed value (accessor for SKN).
 * @return uint16_t Speed in km/h × 10 (0xFFFF if unknown)
 * @note   UNIT-SPM-005; Complexity: 1
 */
uint16_t SPM_GetSpeed(void);

/**
 * @brief Get SPM fault status for FMG aggregation.
 * @return uint8_t 0 = no fault, non-zero = fault code
 */
uint8_t SPM_GetFault();

#endif /* SPM_H */

/*============================================================================
 * END OF FILE
 *===========================================================================*/
