/**
 * @file    dsm.h
 * @brief   Door State Machine (DSM) public interface for TDC
 * @details Per-door FSM engine with 2oo2 sensor voting, operational mode
 *          management, emergency release, and cycle entry.
 *
 * @project TDC (Train Door Control System)
 * @module  DSM (Door State Machine) — COMP-004
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety
 * SIL Level: 3
 * Safety Requirements: REQ-SAFE-007/008/009/010/011/019/020, REQ-FUN-001–015
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §6
 */

#ifndef DSM_H
#define DSM_H

#include <stdint.h>
#include "tdc_types.h"

/**
 * @brief Initialise DSM module — all doors to FSM_IDLE with fail-safe defaults.
 * @return error_t SUCCESS
 * @note   UNIT-DSM-015; Complexity: 1
 */
error_t DSM_Init(void);

/**
 * @brief 20 ms cycle entry — read sensors and advance each door FSM.
 * @note   UNIT-DSM-016; Complexity: 2
 */
void DSM_RunCycle(void);

/**
 * @brief Update per-door FSM — dispatch to state-specific transition handlers.
 * @param[in] door_id           Door index (0–MAX_DOORS-1)
 * @param[in] cmd_open          1=open command active
 * @param[in] cmd_close         1=close command active
 * @param[in] pos_a_open        Sensor A open-position state
 * @param[in] pos_a_closed      Sensor A closed-position state
 * @param[in] pos_b_open        Sensor B open-position state
 * @param[in] pos_b_closed      Sensor B closed-position state
 * @param[in] lock_a            Lock sensor A state (1=locked)
 * @param[in] lock_b            Lock sensor B state (1=locked)
 * @param[in] obstacle          1=obstacle detected for this door
 * @param[in] speed_interlock   1=door open inhibited (speed too high)
 * @param[in] safe_state_active 1=system safe state active
 * @param[in] current_time_ms   Current system tick in milliseconds
 * @return error_t SUCCESS, ERR_RANGE
 * @note   UNIT-DSM-001; Complexity: 8
 */
error_t DSM_UpdateFSM(uint8_t door_id,
                      uint8_t cmd_open,
                      uint8_t cmd_close,
                      uint8_t pos_a_open,
                      uint8_t pos_a_closed,
                      uint8_t pos_b_open,
                      uint8_t pos_b_closed,
                      uint8_t lock_a,
                      uint8_t lock_b,
                      uint8_t obstacle,
                      uint8_t speed_interlock,
                      uint8_t safe_state_active,
                      uint32_t current_time_ms);

/**
 * @brief 2oo2 position sensor voter.
 * @param[in]  door_id        Door index (0–MAX_DOORS-1)
 * @param[in]  pos_a          Sensor A value (0 or 1)
 * @param[in]  pos_b          Sensor B value (0 or 1)
 * @param[out] voted_position Agreed position (0 if disagreement)
 * @param[out] disagree_out   1 if sensors disagree
 * @return error_t SUCCESS, ERR_NULL_PTR
 * @note   UNIT-DSM-012; Complexity: 3
 */
error_t DSM_VotePosition(uint8_t door_id,
                         uint8_t pos_a,
                         uint8_t pos_b,
                         uint8_t *voted_position,
                         uint8_t *disagree_out);

/**
 * @brief Transition operational mode with guard conditions.
 * @param[in] requested_mode New mode to transition to
 * @param[in] tcms_authorized 1 if TCMS has authorised the mode transition
 * @param[in] speed_zero      1 if current speed is zero
 * @return error_t SUCCESS, ERR_NOT_PERMITTED, ERR_INVALID_STATE
 * @note   UNIT-DSM-013; Complexity: 8
 */
error_t DSM_TransitionMode(op_mode_t requested_mode,
                           uint8_t tcms_authorized,
                           uint8_t speed_zero);

/**
 * @brief Handle emergency door release with 60 ms debounce.
 * @param[in] door_id        Door index (0–MAX_DOORS-1)
 * @param[in] current_time_ms Current system tick in milliseconds
 * @return error_t SUCCESS, ERR_RANGE
 * @note   UNIT-DSM-014; Complexity: 4
 */
error_t DSM_HandleEmergencyRelease(uint8_t door_id, uint32_t current_time_ms);

/**
 * @brief Process open command received from TCMS (CAN 0x101).
 * @param[in] door_mask Bitmask of doors to open (bit N = door N)
 * @return error_t SUCCESS
 */
error_t DSM_ProcessOpenCommand(uint8_t door_mask);

/**
 * @brief Process close command received from TCMS (CAN 0x102).
 * @param[in] door_mask Bitmask of doors to close (bit N = door N)
 * @return error_t SUCCESS
 */
error_t DSM_ProcessCloseCommand(uint8_t door_mask);

/**
 * @brief Get door state array (accessor for SKN, TCI).
 * @return const uint8_t* Pointer to door state array [MAX_DOORS]
 * @note   UNIT-DSM-017; Complexity: 1
 */
const uint8_t *DSM_GetDoorStates(void);

/**
 * @brief Get lock state array (accessor for SKN, TCI).
 * @return const uint8_t* Pointer to lock state array [MAX_DOORS]
 * @note   UNIT-DSM-018; Complexity: 1
 */
const uint8_t *DSM_GetLockStates(void);

/**
 * @brief Get closing-in-progress flags (accessor for OBD).
 * @return const uint8_t* Pointer to closing flags array [MAX_DOORS]
 */
const uint8_t *DSM_GetClosingFlags(void);

/**
 * @brief Get DSM fault status for FMG aggregation.
 * @return uint8_t 0 = no fault, non-zero = fault code
 */
uint8_t DSM_GetFault(void);

#endif /* DSM_H */

/*============================================================================
 * END OF FILE
 *===========================================================================*/
