/**
 * @file    hal.h
 * @brief   Hardware Abstraction Layer public interface for TDC
 * @details Provides all hardware access functions: GPIO, PWM, CAN, SPI, ADC,
 *          watchdog, system tick, and CRC-16-CCITT computation.
 *
 * @project TDC (Train Door Control System)
 * @module  HAL (Hardware Abstraction Layer) — COMP-008
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety
 * SIL Level: 3
 * Safety Requirements: REQ-INT-001–013, REQ-SAFE-014/017/018, SW-HAZ-006/008
 *
 * @requirements
 * - REQ-INT-001: GPIO position sensor read
 * - REQ-INT-002: GPIO lock sensor read
 * - REQ-INT-003: GPIO obstacle sensor read
 * - REQ-INT-004: PWM motor control
 * - REQ-INT-005: CAN transmit/receive
 * - REQ-INT-006: SPI cross-channel exchange
 * - REQ-SAFE-014: Watchdog refresh within 40 ms
 * - REQ-SAFE-017: System tick monotonic counter
 * - REQ-SAFE-018: CRC-16-CCITT computation
 *
 * @misra_compliance
 * MISRA C:2012 Compliance:
 * - All mandatory rules: Compliant
 * - Fixed-width types only
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §10
 */

#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "tdc_types.h"

/*============================================================================
 * PUBLIC FUNCTION PROTOTYPES — GPIO
 * Implements: REQ-INT-001, REQ-INT-002, REQ-INT-003
 * Design ref: SCDS §10.1, UNIT-HAL-001 through UNIT-HAL-006
 *===========================================================================*/

/**
 * @brief Read a door position sensor (2 per door: sensor_id 0 or 1).
 * @param[in]  door_id   Door index (0–MAX_DOORS-1)
 * @param[in]  sensor_id Sensor index (0 or 1)
 * @param[out] state     Sensor state: 1=active, 0=inactive
 * @return error_t SUCCESS, ERR_NULL_PTR, ERR_RANGE
 */
error_t HAL_GPIO_ReadPositionSensor(uint8_t door_id, uint8_t sensor_id,
                                    uint8_t *state);

/**
 * @brief Read a door lock sensor (2 per door: sensor_id 0 or 1).
 * @param[in]  door_id   Door index (0–MAX_DOORS-1)
 * @param[in]  sensor_id Sensor index (0 or 1)
 * @param[out] state     Sensor state: 1=locked, 0=unlocked
 * @return error_t SUCCESS, ERR_NULL_PTR, ERR_RANGE
 */
error_t HAL_GPIO_ReadLockSensor(uint8_t door_id, uint8_t sensor_id,
                                uint8_t *state);

/**
 * @brief Read an obstacle proximity sensor (2 per door: sensor_id 0 or 1).
 * @param[in]  door_id   Door index (0–MAX_DOORS-1)
 * @param[in]  sensor_id Sensor index (0 or 1)
 * @param[out] state     Sensor state: 1=obstacle present, 0=clear
 * @return error_t SUCCESS, ERR_NULL_PTR, ERR_RANGE
 */
error_t HAL_GPIO_ReadObstacleSensor(uint8_t door_id, uint8_t sensor_id,
                                    uint8_t *state);

/**
 * @brief Read emergency release GPIO for a door.
 * @param[in] door_id Door index (0–MAX_DOORS-1)
 * @return 1 if emergency release is active, 0 otherwise (defensive: returns 0 on range error)
 */
uint8_t HAL_GPIO_ReadEmergencyRelease(uint8_t door_id);

/**
 * @brief Set motor direction for a door.
 * @param[in] door_id   Door index (0–MAX_DOORS-1)
 * @param[in] direction 0=open direction, 1=close direction
 * @return error_t SUCCESS, ERR_RANGE
 */
error_t HAL_GPIO_SetMotorDirection(uint8_t door_id, uint8_t direction);

/**
 * @brief Set lock solenoid actuator state for a door.
 * @param[in] door_id Door index (0–MAX_DOORS-1)
 * @param[in] locked  1=energise lock, 0=de-energise
 * @return error_t SUCCESS, ERR_RANGE
 */
error_t HAL_GPIO_SetLockActuator(uint8_t door_id, uint8_t locked);

/*============================================================================
 * PUBLIC FUNCTION PROTOTYPES — PWM
 * Implements: REQ-INT-004
 * Design ref: SCDS §10.2, UNIT-HAL-007 through UNIT-HAL-008
 *===========================================================================*/

/**
 * @brief Set PWM duty cycle for motor drive (0–100 percent).
 * @param[in] door_id    Door index (0–MAX_DOORS-1)
 * @param[in] duty_pct   Duty cycle 0–100 (0=off, 100=full)
 * @return error_t SUCCESS, ERR_RANGE
 */
error_t HAL_PWM_SetDutyCycle(uint8_t door_id, uint8_t duty_pct);

/*============================================================================
 * PUBLIC FUNCTION PROTOTYPES — CAN
 * Implements: REQ-INT-005, REQ-SAFE-003
 * Design ref: SCDS §10.3, UNIT-HAL-009 through UNIT-HAL-011
 *===========================================================================*/

/**
 * @brief Receive a CAN frame (low-level, called from ISR).
 * @param[out] msg_id   CAN message identifier
 * @param[out] data     Data bytes (8 bytes max)
 * @param[out] dlc      Data Length Code (0–8)
 * @return error_t SUCCESS, ERR_NULL_PTR, ERR_TIMEOUT
 */
error_t HAL_CAN_Receive(uint32_t *msg_id, uint8_t *data, uint8_t *dlc);

/**
 * @brief Transmit a CAN frame.
 * @param[in] msg_id CAN message identifier
 * @param[in] data   Data bytes
 * @param[in] dlc    Data Length Code (0–8)
 * @return error_t SUCCESS, ERR_NULL_PTR, ERR_RANGE, ERR_TIMEOUT
 */
error_t HAL_CAN_Transmit(uint32_t msg_id, const uint8_t *data, uint8_t dlc);

/*============================================================================
 * PUBLIC FUNCTION PROTOTYPES — SPI Cross-Channel
 * Implements: REQ-SAFE-002, SW-HAZ-011
 * Design ref: SCDS §10.4, UNIT-HAL-012 through UNIT-HAL-013
 *===========================================================================*/

/**
 * @brief Exchange cross-channel state struct via SPI with peer DCU.
 * @param[in]  local   Pointer to local state to transmit (must not be NULL)
 * @param[out] remote  Pointer to buffer for received peer state (must not be NULL)
 * @return error_t SUCCESS, ERR_NULL_PTR, ERR_TIMEOUT, ERR_HW_FAULT
 */
error_t HAL_SPI_CrossChannel_Exchange(const cross_channel_state_t *local,
                                      cross_channel_state_t *remote);

/*============================================================================
 * PUBLIC FUNCTION PROTOTYPES — ADC
 * Implements: REQ-SAFE-006 (motor current for obstacle detection)
 * Design ref: SCDS §10.5, UNIT-HAL-014
 *===========================================================================*/

/**
 * @brief Read ADC value for motor current sensing.
 * @param[in]  door_id   Door index (0–MAX_DOORS-1)
 * @param[out] adc_value ADC raw value (0–4095 for 12-bit ADC)
 * @return error_t SUCCESS, ERR_NULL_PTR, ERR_RANGE, ERR_HW_FAULT
 */
error_t HAL_ADC_ReadMotorCurrent(uint8_t door_id, uint16_t *adc_value);

/*============================================================================
 * PUBLIC FUNCTION PROTOTYPES — Watchdog and System Services
 * Implements: REQ-SAFE-014, REQ-SAFE-017, REQ-SAFE-018
 * Design ref: SCDS §10.2, UNIT-HAL-015 through UNIT-HAL-020
 *===========================================================================*/

/**
 * @brief Refresh the hardware watchdog timer.
 *        Must be called within WDG_REFRESH_MS (40 ms) to prevent reset.
 * @return error_t SUCCESS, ERR_HW_FAULT
 */
error_t HAL_Watchdog_Refresh(void);

/**
 * @brief Get current system tick in milliseconds (monotonic).
 * @return uint32_t Current tick value (wraps at UINT32_MAX)
 */
uint32_t HAL_GetSystemTickMs(void);

/**
 * @brief Initialise the HAL subsystem.
 * @return error_t SUCCESS, ERR_HW_FAULT
 */
error_t HAL_Init(void);

/**
 * @brief Compute CRC-16-CCITT (polynomial 0x1021, init 0xFFFF, no final XOR).
 * @details Used by ALL components for data integrity checking (OI-FTA-003).
 * @param[in] data   Pointer to data buffer (must not be NULL)
 * @param[in] length Number of bytes to process (must be > 0)
 * @return uint16_t Computed CRC-16 value (0x0000 if data==NULL or length==0)
 * @note  Complexity: 4 — within SIL 3 limit of 10
 */
uint16_t CRC16_CCITT_Compute(const uint8_t *data, uint16_t length);

/*============================================================================
 * CONVENIENCE WRAPPERS — Motor and Lock control
 * Thin wrappers used by DSM to express intent clearly without repeating
 * multi-step GPIO+PWM sequences throughout the FSM.
 * Implements: REQ-INT-004, SCDS §10.2
 *===========================================================================*/

/**
 * @brief Start motor for a door in the specified direction.
 * @param[in] door_id   Door index (0–MAX_DOORS-1)
 * @param[in] direction 1=open, 0=close
 * @return error_t SUCCESS, ERR_RANGE, ERR_HW_FAULT
 */
error_t HAL_MotorStart(uint8_t door_id, uint8_t direction);

/**
 * @brief Stop motor for a door (duty cycle = 0).
 * @param[in] door_id Door index (0–MAX_DOORS-1)
 * @return error_t SUCCESS, ERR_RANGE
 */
error_t HAL_MotorStop(uint8_t door_id);

/**
 * @brief Engage (energise) the lock solenoid for a door.
 * @param[in] door_id Door index (0–MAX_DOORS-1)
 * @return error_t SUCCESS, ERR_RANGE
 */
error_t HAL_LockEngage(uint8_t door_id);

/**
 * @brief Disengage (de-energise) the lock solenoid for a door.
 * @param[in] door_id Door index (0–MAX_DOORS-1)
 * @return error_t SUCCESS, ERR_RANGE
 */
error_t HAL_LockDisengage(uint8_t door_id);

#endif /* HAL_H */

/*============================================================================
 * END OF FILE
 *===========================================================================*/
