/**
 * @file    fmg.h
 * @brief   Fault Manager (FMG) public interface for TDC
 * @details Fault aggregation, classification/escalation, selective door
 *          disablement, emergency stop processing, and cycle entry.
 *
 * @project TDC (Train Door Control System)
 * @module  FMG (Fault Manager) — COMP-005
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety
 * SIL Level: 3
 * Safety Requirements: REQ-SAFE-012/013/021, REQ-FUN-013/017/018, SW-HAZ-005/010
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §7
 */

#ifndef FMG_H
#define FMG_H

#include <stdint.h>
#include "tdc_types.h"

/**
 * @brief Initialise FMG module — clear all fault state.
 * @return error_t SUCCESS
 * @note   UNIT-FMG-004; Complexity: 1
 */
error_t FMG_Init(void);

/**
 * @brief 20 ms cycle entry — aggregate and classify faults.
 * @note   UNIT-FMG-005; Complexity: 1
 */
void FMG_RunCycle(void);

/**
 * @brief Aggregate fault flags from all components into a single bitmask.
 * @param[in]  spm_fault   SPM fault flag (0=OK, non-zero=fault)
 * @param[in]  obd_fault   OBD fault flag
 * @param[in]  dsm_fault   DSM fault flag
 * @param[in]  tci_fault   TCI fault flag
 * @param[in]  hal_fault   HAL fault flag
 * @param[out] fault_state_out Combined fault bitmask
 * @return error_t SUCCESS, ERR_NULL_PTR
 * @note   UNIT-FMG-001; Complexity: 2
 */
error_t FMG_AggregateFaults(uint8_t spm_fault,
                            uint8_t obd_fault,
                            uint8_t dsm_fault,
                            uint8_t tci_fault,
                            uint8_t hal_fault,
                            uint8_t *fault_state_out);

/**
 * @brief Classify fault bitmask and escalate to maximum severity.
 * @param[in]  fault_state    Aggregated fault bitmask
 * @param[out] max_severity_out Maximum severity of active faults
 * @return error_t SUCCESS, ERR_NULL_PTR
 * @note   UNIT-FMG-002; Complexity: 4
 */
error_t FMG_ClassifyAndEscalate(uint8_t fault_state,
                                fault_severity_t *max_severity_out);

/**
 * @brief Apply selective door disablement when authorised by TCMS.
 * @param[in] door_mask       Bitmask of doors to disable (bit N = door N)
 * @param[in] tcms_authorized 1 if TCMS has authorised the disablement
 * @return error_t SUCCESS, ERR_NOT_PERMITTED
 * @note   UNIT-FMG-003; Complexity: 2
 */
error_t FMG_HandleSelectiveDisablement(uint8_t door_mask,
                                       uint8_t tcms_authorized);

/**
 * @brief Process emergency stop command received from TCMS (CAN 0x104).
 * @param[in] stop_code Emergency stop command code
 * @return error_t SUCCESS
 */
error_t FMG_ProcessEmergencyStop(uint8_t stop_code);

/**
 * @brief Get current aggregated fault state (accessor for SKN, TCI).
 * @return uint8_t Aggregated fault bitmask (0 = no faults)
 * @note   UNIT-FMG-006; Complexity: 1
 */
uint8_t FMG_GetFaultState(void);

/**
 * @brief Get FMG fault status (for FMG self-reporting).
 * @return uint8_t 0 = no fault
 */
uint8_t FMG_GetFault(void);

#endif /* FMG_H */

/*============================================================================
 * END OF FILE
 *===========================================================================*/
