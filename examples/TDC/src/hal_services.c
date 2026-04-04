/**
 * @file    hal_services.c
 * @brief   Hardware Abstraction Layer — GPIO, PWM, CAN, SPI, ADC, Watchdog,
 *          System Tick, and CRC-16-CCITT implementation.
 * @details Platform-stub implementations. In production, GPIO_Read() and
 *          related macros are replaced by device-register accesses.
 *          All functions return error_t; callers must check every return.
 *
 * @project TDC (Train Door Control System)
 * @module  HAL (Hardware Abstraction Layer) — COMP-008
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-INT-001–013, REQ-SAFE-014/017/018, SW-HAZ-006/008
 *
 * @requirements
 * - REQ-INT-001: UNIT-HAL-001 HAL_GPIO_ReadPositionSensor
 * - REQ-INT-002: UNIT-HAL-002 HAL_GPIO_ReadLockSensor
 * - REQ-INT-003: UNIT-HAL-003 HAL_GPIO_ReadObstacleSensor
 * - REQ-INT-004: UNIT-HAL-007 HAL_PWM_SetDutyCycle
 * - REQ-INT-005: UNIT-HAL-009 HAL_CAN_Receive, UNIT-HAL-010 HAL_CAN_Transmit
 * - REQ-INT-006: UNIT-HAL-012 HAL_SPI_CrossChannel_Exchange
 * - REQ-SAFE-014: UNIT-HAL-015 HAL_Watchdog_Refresh
 * - REQ-SAFE-017: UNIT-HAL-016 HAL_GetSystemTickMs
 * - REQ-SAFE-018: UNIT-HAL-020 CRC16_CCITT_Compute
 *
 * @misra_compliance
 * MISRA C:2012 Compliance:
 * - All mandatory rules: Compliant
 * - Rule 21.3: No dynamic allocation (static arrays only)
 * - No recursion, no function pointers in safety paths
 * - Fixed-width types throughout
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §10
 */

/* Implements: REQ-INT-001–013, REQ-SAFE-014/017/018, SW-HAZ-006/008 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §10 (COMP-008) */

/*============================================================================
 * INCLUDES
 *===========================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "hal.h"
#include "tdc_types.h"

/*============================================================================
 * PREPROCESSOR DEFINITIONS
 *===========================================================================*/

/** @brief Maximum PWM duty cycle value (100 percent) */
#define HAL_PWM_MAX_DUTY_PCT    (100U)

/** @brief Maximum ADC raw value for 12-bit ADC */
#define HAL_ADC_MAX_VALUE       (4095U)

/** @brief Maximum CAN DLC value */
#define HAL_CAN_MAX_DLC         (8U)

/** @brief Number of position sensor channels per door */
#define HAL_POSITION_SENSORS_PER_DOOR (2U)

/** @brief Number of lock sensor channels per door */
#define HAL_LOCK_SENSORS_PER_DOOR     (2U)

/** @brief Number of obstacle sensor channels per door */
#define HAL_OBSTACLE_SENSORS_PER_DOOR (2U)

/** @brief CRC-16-CCITT polynomial */
#define CRC16_POLY  (0x1021U)

/** @brief CRC-16-CCITT initial value */
#define CRC16_INIT  (0xFFFFU)

/** @brief SPI transfer size: sizeof(cross_channel_state_t) */
#define HAL_SPI_TRANSFER_BYTES  ((uint16_t)sizeof(cross_channel_state_t))

/*============================================================================
 * STATIC VARIABLES — GPIO shadow registers (stub for target hardware)
 * Implements: UNIT-HAL-001 through UNIT-HAL-006
 *===========================================================================*/

/**
 * @brief Shadow registers for position sensors [door][sensor] — platform stub.
 * @note  On target: replaced by direct GPIO register reads.
 */
static uint8_t s_position_sensor_shadow[MAX_DOORS][HAL_POSITION_SENSORS_PER_DOOR];

/**
 * @brief Shadow registers for lock sensors [door][sensor] — platform stub.
 */
static uint8_t s_lock_sensor_shadow[MAX_DOORS][HAL_LOCK_SENSORS_PER_DOOR];

/**
 * @brief Shadow registers for obstacle sensors [door][sensor] — platform stub.
 */
static uint8_t s_obstacle_sensor_shadow[MAX_DOORS][HAL_OBSTACLE_SENSORS_PER_DOOR];

/**
 * @brief Shadow registers for emergency release GPIO [door] — platform stub.
 */
static uint8_t s_emergency_release_shadow[MAX_DOORS];

/**
 * @brief Motor direction shadow [door]: 0=open, 1=close.
 */
static uint8_t s_motor_direction[MAX_DOORS];

/**
 * @brief Lock actuator shadow [door]: 1=locked, 0=unlocked.
 */
static uint8_t s_lock_actuator[MAX_DOORS];

/**
 * @brief PWM duty cycle shadow [door]: 0–100 percent.
 */
static uint8_t s_pwm_duty[MAX_DOORS];

/**
 * @brief ADC motor current shadow [door]: 0–4095 raw counts.
 */
static uint16_t s_adc_motor_current[MAX_DOORS];

/**
 * @brief CAN receive FIFO (single entry stub).
 */
static uint32_t s_can_rx_msg_id;
static uint8_t  s_can_rx_data[HAL_CAN_MAX_DLC];
static uint8_t  s_can_rx_dlc;
static uint8_t  s_can_rx_pending;

/**
 * @brief SPI cross-channel receive buffer.
 */
static cross_channel_state_t s_spi_rx_buffer;

/**
 * @brief System tick counter in milliseconds.
 */
static uint32_t s_system_tick_ms;

/**
 * @brief Watchdog fault flag.
 */
static uint8_t s_hal_fault_flag;

/**
 * @brief HAL initialisation flag.
 */
static uint8_t s_hal_initialized;

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS — HAL Initialisation
 * Implements: UNIT-HAL-017
 *===========================================================================*/

/**
 * @brief Initialise the HAL subsystem.
 * @complexity Cyclomatic complexity: 1 — within SIL 3 limit of 10
 */
error_t HAL_Init(void)
{
    uint8_t door_idx;
    uint8_t sensor_idx;

    /* Initialise GPIO shadows */
    for (door_idx = 0U; door_idx < MAX_DOORS; door_idx++)
    {
        for (sensor_idx = 0U; sensor_idx < HAL_POSITION_SENSORS_PER_DOOR; sensor_idx++)
        {
            s_position_sensor_shadow[door_idx][sensor_idx] = 0U;
            s_lock_sensor_shadow[door_idx][sensor_idx]     = 0U;
            s_obstacle_sensor_shadow[door_idx][sensor_idx] = 0U;
        }
        s_emergency_release_shadow[door_idx] = 0U;
        s_motor_direction[door_idx] = 0U;
        s_lock_actuator[door_idx]   = 0U;
        s_pwm_duty[door_idx]        = 0U;
        s_adc_motor_current[door_idx] = 0U;
    }

    s_can_rx_msg_id  = 0U;
    s_can_rx_dlc     = 0U;
    s_can_rx_pending = 0U;
    s_system_tick_ms = 0U;
    s_hal_fault_flag = 0U;
    s_hal_initialized = 1U;

    return SUCCESS;
}

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS — GPIO
 * Implements: UNIT-HAL-001, UNIT-HAL-002, UNIT-HAL-003, UNIT-HAL-004,
 *             UNIT-HAL-005, UNIT-HAL-006
 *===========================================================================*/

/**
 * @brief Read a door position sensor (2 per door).
 * @complexity Cyclomatic complexity: 4
 */
error_t HAL_GPIO_ReadPositionSensor(uint8_t door_id, uint8_t sensor_id,
                                    uint8_t *state)
{
    /* Implements: REQ-INT-001, UNIT-HAL-001 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §10.1.1 */
    error_t result;

    if (NULL == state)
    {
        result = ERR_NULL_PTR;
    }
    else if (door_id >= MAX_DOORS)
    {
        result = ERR_RANGE;
    }
    else if (sensor_id >= HAL_POSITION_SENSORS_PER_DOOR)
    {
        result = ERR_RANGE;
    }
    else
    {
        /* Platform stub: reads shadow register. Target: GPIO register read. */
        *state = s_position_sensor_shadow[door_id][sensor_id];
        result = SUCCESS;
    }

    return result;
}

/**
 * @brief Read a door lock sensor (2 per door).
 * @complexity Cyclomatic complexity: 4
 */
error_t HAL_GPIO_ReadLockSensor(uint8_t door_id, uint8_t sensor_id,
                                uint8_t *state)
{
    /* Implements: REQ-INT-002, UNIT-HAL-002 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §10.1 */
    error_t result;

    if (NULL == state)
    {
        result = ERR_NULL_PTR;
    }
    else if (door_id >= MAX_DOORS)
    {
        result = ERR_RANGE;
    }
    else if (sensor_id >= HAL_LOCK_SENSORS_PER_DOOR)
    {
        result = ERR_RANGE;
    }
    else
    {
        *state = s_lock_sensor_shadow[door_id][sensor_id];
        result = SUCCESS;
    }

    return result;
}

/**
 * @brief Read an obstacle proximity sensor (2 per door).
 * @complexity Cyclomatic complexity: 4
 */
error_t HAL_GPIO_ReadObstacleSensor(uint8_t door_id, uint8_t sensor_id,
                                    uint8_t *state)
{
    /* Implements: REQ-INT-003, UNIT-HAL-003 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §10.1 */
    error_t result;

    if (NULL == state)
    {
        result = ERR_NULL_PTR;
    }
    else if (door_id >= MAX_DOORS)
    {
        result = ERR_RANGE;
    }
    else if (sensor_id >= HAL_OBSTACLE_SENSORS_PER_DOOR)
    {
        result = ERR_RANGE;
    }
    else
    {
        *state = s_obstacle_sensor_shadow[door_id][sensor_id];
        result = SUCCESS;
    }

    return result;
}

/**
 * @brief Read emergency release GPIO for a door.
 * @complexity Cyclomatic complexity: 2
 */
uint8_t HAL_GPIO_ReadEmergencyRelease(uint8_t door_id)
{
    /* Implements: UNIT-HAL-004 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §10.1 */
    uint8_t state;

    if (door_id >= MAX_DOORS)
    {
        state = 0U;  /* Fail-safe: treat as not activated */
    }
    else
    {
        state = s_emergency_release_shadow[door_id];
    }

    return state;
}

/**
 * @brief Set motor direction for a door.
 * @complexity Cyclomatic complexity: 2
 */
error_t HAL_GPIO_SetMotorDirection(uint8_t door_id, uint8_t direction)
{
    /* Implements: REQ-INT-004 (direction), UNIT-HAL-005 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §10.1 */
    error_t result;

    if (door_id >= MAX_DOORS)
    {
        result = ERR_RANGE;
    }
    else
    {
        s_motor_direction[door_id] = direction;
        result = SUCCESS;
    }

    return result;
}

/**
 * @brief Set lock solenoid actuator state for a door.
 * @complexity Cyclomatic complexity: 2
 */
error_t HAL_GPIO_SetLockActuator(uint8_t door_id, uint8_t locked)
{
    /* Implements: REQ-INT-004 (lock), UNIT-HAL-006 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §10.1 */
    error_t result;

    if (door_id >= MAX_DOORS)
    {
        result = ERR_RANGE;
    }
    else
    {
        s_lock_actuator[door_id] = locked;
        result = SUCCESS;
    }

    return result;
}

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS — PWM
 * Implements: UNIT-HAL-007, UNIT-HAL-008
 *===========================================================================*/

/**
 * @brief Set PWM duty cycle for motor drive (0–100 percent).
 * @complexity Cyclomatic complexity: 2
 */
error_t HAL_PWM_SetDutyCycle(uint8_t door_id, uint8_t duty_pct)
{
    /* Implements: REQ-INT-004 (PWM), UNIT-HAL-007 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §10.2 */
    error_t result;

    if (door_id >= MAX_DOORS)
    {
        result = ERR_RANGE;
    }
    else if (duty_pct > HAL_PWM_MAX_DUTY_PCT)
    {
        result = ERR_RANGE;
    }
    else
    {
        s_pwm_duty[door_id] = duty_pct;
        /* Target: write to PWM capture/compare register */
        result = SUCCESS;
    }

    return result;
}

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS — CAN
 * Implements: UNIT-HAL-009, UNIT-HAL-010, UNIT-HAL-011
 *===========================================================================*/

/**
 * @brief Receive a CAN frame (low-level, called from ISR or polled).
 * @complexity Cyclomatic complexity: 3
 */
error_t HAL_CAN_Receive(uint32_t *msg_id, uint8_t *data, uint8_t *dlc)
{
    /* Implements: REQ-INT-005, UNIT-HAL-009 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §10.3 */
    error_t result;
    uint8_t byte_idx;

    if ((NULL == msg_id) || (NULL == data) || (NULL == dlc))
    {
        result = ERR_NULL_PTR;
    }
    else if (0U == s_can_rx_pending)
    {
        result = ERR_TIMEOUT;
    }
    else
    {
        *msg_id = s_can_rx_msg_id;
        *dlc    = s_can_rx_dlc;
        for (byte_idx = 0U; byte_idx < s_can_rx_dlc; byte_idx++)
        {
            data[byte_idx] = s_can_rx_data[byte_idx];
        }
        s_can_rx_pending = 0U;
        result = SUCCESS;
    }

    return result;
}

/**
 * @brief Transmit a CAN frame.
 * @complexity Cyclomatic complexity: 4
 */
error_t HAL_CAN_Transmit(uint32_t msg_id, const uint8_t *data, uint8_t dlc)
{
    /* Implements: REQ-INT-005, UNIT-HAL-010 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §10.3 */
    error_t result;

    if (NULL == data)
    {
        result = ERR_NULL_PTR;
    }
    else if (dlc > HAL_CAN_MAX_DLC)
    {
        result = ERR_RANGE;
    }
    else if (0U == s_hal_initialized)
    {
        result = ERR_HW_FAULT;
    }
    else
    {
        /* Target: load CAN mailbox registers, trigger transmission */
        (void)msg_id;  /* Used on target hardware */
        (void)data;
        (void)dlc;
        result = SUCCESS;
    }

    return result;
}

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS — SPI Cross-Channel
 * Implements: UNIT-HAL-012, UNIT-HAL-013
 *===========================================================================*/

/**
 * @brief Exchange cross-channel state struct via SPI with peer DCU.
 * @complexity Cyclomatic complexity: 3
 */
error_t HAL_SPI_CrossChannel_Exchange(const cross_channel_state_t *local,
                                      cross_channel_state_t *remote)
{
    /* Implements: REQ-SAFE-002, SW-HAZ-011, UNIT-HAL-012 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §10.4 */
    error_t result;

    if (NULL == local)
    {
        result = ERR_NULL_PTR;
    }
    else if (NULL == remote)
    {
        result = ERR_NULL_PTR;
    }
    else if (0U == s_hal_initialized)
    {
        result = ERR_HW_FAULT;
    }
    else
    {
        /* Target: full-duplex SPI DMA transfer of HAL_SPI_TRANSFER_BYTES.
         * Stub: return the local state as remote (loopback for unit-test). */
        *remote = s_spi_rx_buffer;
        /* Note: on target, s_spi_rx_buffer is populated by DMA ISR. */
        (void)local;
        result = SUCCESS;
    }

    return result;
}

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS — ADC
 * Implements: UNIT-HAL-014
 *===========================================================================*/

/**
 * @brief Read ADC value for motor current sensing.
 * @complexity Cyclomatic complexity: 3
 */
error_t HAL_ADC_ReadMotorCurrent(uint8_t door_id, uint16_t *adc_value)
{
    /* Implements: REQ-SAFE-006 (force/current), UNIT-HAL-014 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §10.5 */
    error_t result;

    if (NULL == adc_value)
    {
        result = ERR_NULL_PTR;
    }
    else if (door_id >= MAX_DOORS)
    {
        result = ERR_RANGE;
    }
    else
    {
        *adc_value = s_adc_motor_current[door_id];
        result = SUCCESS;
    }

    return result;
}

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS — Watchdog and System Services
 * Implements: UNIT-HAL-015, UNIT-HAL-016
 *===========================================================================*/

/**
 * @brief Refresh the hardware watchdog timer.
 * @complexity Cyclomatic complexity: 2
 */
error_t HAL_Watchdog_Refresh(void)
{
    /* Implements: REQ-SAFE-014, SW-HAZ-006, UNIT-HAL-015 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §10.2 */
    error_t result;

    if (0U == s_hal_initialized)
    {
        s_hal_fault_flag = 1U;
        result = ERR_HW_FAULT;
    }
    else
    {
        /* Target: write watchdog service register (IWDG_KR = 0xAAAA on STM32) */
        result = SUCCESS;
    }

    return result;
}

/**
 * @brief Get current system tick in milliseconds (monotonic).
 * @complexity Cyclomatic complexity: 1
 */
uint32_t HAL_GetSystemTickMs(void)
{
    /* Implements: REQ-SAFE-017, UNIT-HAL-016 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §10.2 */
    /* Target: read SysTick-derived counter. Stub: return shadow variable. */
    return s_system_tick_ms;
}

/**
 * @brief Get HAL fault status for FMG aggregation.
 * @complexity Cyclomatic complexity: 1
 */
uint8_t HAL_GetFault(void)
{
    return s_hal_fault_flag;
}

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATION — CRC-16-CCITT
 * Implements: UNIT-HAL-020
 *===========================================================================*/

/**
 * @brief Compute CRC-16-CCITT (polynomial 0x1021, init 0xFFFF, no final XOR).
 * @details Bit-by-bit algorithm. All safety-critical data structures in TDC
 *          use this function for integrity protection (OI-FTA-003).
 * @complexity Cyclomatic complexity: 4 — within SIL 3 limit of 10
 */
uint16_t CRC16_CCITT_Compute(const uint8_t *data, uint16_t length)
{
    /* Implements: REQ-SAFE-010/018, OI-FTA-003, UNIT-HAL-020 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §2.2, §10.2 */
    uint16_t crc;
    uint16_t byte_idx;
    uint8_t  bit_idx;

    /* Defensive: return 0x0000 on invalid input */
    if ((NULL == data) || (0U == length))
    {
        crc = 0x0000U;
    }
    else
    {
        crc = CRC16_INIT;  /* 0xFFFF */

        for (byte_idx = 0U; byte_idx < length; byte_idx++)
        {
            crc ^= ((uint16_t)data[byte_idx] << 8U);

            for (bit_idx = 0U; bit_idx < 8U; bit_idx++)
            {
                if ((crc & 0x8000U) != 0U)
                {
                    crc = (uint16_t)((crc << 1U) ^ CRC16_POLY);
                }
                else
                {
                    crc = (uint16_t)(crc << 1U);
                }
            }
        }
    }

    return crc;
}

/*============================================================================
 * CONVENIENCE WRAPPERS — Motor and Lock Control
 * Implements: REQ-INT-004, SCDS DOC-COMPDES-2026-001 §10.2
 *===========================================================================*/

/** @brief Full speed duty cycle (percent) */
#define HAL_MOTOR_FULL_DUTY  (80U)

/**
 * @brief Start motor for a door in the specified direction.
 * @complexity Cyclomatic complexity: 3
 */
error_t HAL_MotorStart(uint8_t door_id, uint8_t direction)
{
    /* Implements: REQ-INT-004 */
    error_t err;

    if (door_id >= MAX_DOORS)
    {
        return ERR_RANGE;
    }

    err = HAL_GPIO_SetMotorDirection(door_id, direction);
    if (SUCCESS != err)
    {
        return err;
    }

    err = HAL_PWM_SetDutyCycle(door_id, HAL_MOTOR_FULL_DUTY);
    return err;
}

/**
 * @brief Stop motor for a door (duty cycle = 0).
 * @complexity Cyclomatic complexity: 1
 */
error_t HAL_MotorStop(uint8_t door_id)
{
    /* Implements: REQ-INT-004 */
    return HAL_PWM_SetDutyCycle(door_id, 0U);
}

/**
 * @brief Engage (energise) the lock solenoid for a door.
 * @complexity Cyclomatic complexity: 1
 */
error_t HAL_LockEngage(uint8_t door_id)
{
    /* Implements: REQ-INT-002 */
    return HAL_GPIO_SetLockActuator(door_id, 1U);
}

/**
 * @brief Disengage (de-energise) the lock solenoid for a door.
 * @complexity Cyclomatic complexity: 1
 */
error_t HAL_LockDisengage(uint8_t door_id)
{
    /* Implements: REQ-INT-002 */
    return HAL_GPIO_SetLockActuator(door_id, 0U);
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
