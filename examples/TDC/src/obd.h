/**
 * @file    obd.h
 * @brief   Obstacle Detector (OBD) public interface for TDC
 * @details ISR-based latch, polled dual-sensor (1oo2) detection, motor current
 *          monitoring, and cycle entry for obstacle detection and reversal.
 *
 * @project TDC (Train Door Control System)
 * @module  OBD (Obstacle Detector) — COMP-003
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety
 * SIL Level: 3
 * Safety Requirements: REQ-SAFE-004/005/006, REQ-PERF-003, SW-HAZ-002
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §5
 */

#ifndef OBD_H
#define OBD_H

#include <stdint.h>
#include "tdc_types.h"

/**
 * @brief Obstacle sensor interrupt service routine — minimal ISR, sets latch.
 * @param[in] door_id Door index (0–MAX_DOORS-1); silently ignored if out of range
 * @note   UNIT-OBD-001; Complexity: 2. Keep minimal per MISRA ISR guidance.
 */
void OBD_ObstacleISR(uint8_t door_id);

/**
 * @brief Initialise OBD module — clear all flags and state.
 * @return error_t SUCCESS
 * @note   UNIT-OBD-003; Complexity: 1
 */
error_t OBD_Init(void);

/**
 * @brief 20 ms cycle entry — poll sensors and update obstacle flags.
 * @note   UNIT-OBD-004; Complexity: 1
 */
void OBD_RunCycle(void);

/**
 * @brief Poll obstacle sensors and evaluate detection for all doors.
 * @details 1oo2 logic: ISR latch OR polled sensor A OR polled sensor B
 *          OR motor current > MAX_FORCE_ADC (when door closing) → obstacle.
 *          Fail-safe: sensor read error → assume obstacle present.
 * @param[in]  door_closing_flags Array of closing-in-progress flags [MAX_DOORS]
 * @param[out] obstacle_flags_out Output obstacle flags per door [MAX_DOORS]
 * @return error_t SUCCESS, ERR_NULL_PTR
 * @note   UNIT-OBD-002; Complexity: 10 (at SIL 3 limit)
 */
error_t OBD_PollSensorsAndEvaluate(const uint8_t door_closing_flags[MAX_DOORS],
                                   uint8_t obstacle_flags_out[MAX_DOORS]);

/**
 * @brief Get obstacle flags array (accessor for SKN and DSM).
 * @return const uint8_t* Pointer to internal obstacle flag array [MAX_DOORS]
 * @note   UNIT-OBD-005; Complexity: 1
 */
const uint8_t *OBD_GetObstacleFlags(void);

/**
 * @brief Get OBD fault status for FMG aggregation.
 * @return uint8_t 0 = no fault, non-zero = sensor read fault
 */
uint8_t OBD_GetFault(void);

#endif /* OBD_H */

/*============================================================================
 * END OF FILE
 *===========================================================================*/
