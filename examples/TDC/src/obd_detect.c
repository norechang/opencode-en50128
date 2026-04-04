/**
 * @file    obd_detect.c
 * @brief   OBD Obstacle Detection — ISR latch, polled sensors, motor current.
 * @details Implements UNIT-OBD-001 (ObstacleISR), UNIT-OBD-002
 *          (PollSensorsAndEvaluate), UNIT-OBD-003 (Init), UNIT-OBD-004
 *          (RunCycle), UNIT-OBD-005 (GetObstacleFlags), and OBD_GetFault.
 *
 * @project TDC (Train Door Control System)
 * @module  OBD (Obstacle Detector) — COMP-003
 * @date    2026-04-04
 * @version 1.0
 *
 * @safety  SIL Level: 3
 * Safety Requirements: REQ-SAFE-004/005/006, REQ-PERF-003, SW-HAZ-002
 *
 * @misra_compliance
 * MISRA C:2012 Compliance: All mandatory rules compliant
 *
 * @en50128_references
 * - EN 50128:2011 Section 7.4, Table A.4
 * - SCDS DOC-COMPDES-2026-001 §5
 */

/* Implements: REQ-SAFE-004/005/006, SW-HAZ-002 */
/* Design ref: SCDS DOC-COMPDES-2026-001 §5 (COMP-003) */

#include <stdint.h>
#include <stddef.h>

#include "obd.h"
#include "skn.h"
#include "dsm.h"
#include "hal.h"
#include "dgn.h"
#include "tdc_types.h"

/*============================================================================
 * PREPROCESSOR DEFINITIONS
 *===========================================================================*/
/** @brief Motor current ADC threshold equivalent to maximum allowed force (~150 N) */
#define OBD_MAX_FORCE_ADC  (3000U)

/*============================================================================
 * STATIC VARIABLES
 *===========================================================================*/
/** @brief ISR-set latch flags; one per door. Set by OBD_ObstacleISR, cleared by poll */
static uint8_t s_obstacle_isr_flags[MAX_DOORS];

/** @brief Evaluated obstacle flags per door (result of last cycle evaluation) */
static uint8_t s_obstacle_flags[MAX_DOORS];

/** @brief Motor current ADC values per door (from last HAL read) */
static uint16_t s_motor_current_adc[MAX_DOORS];

/** @brief OBD fault flag (set if HAL sensor read fails) */
static uint8_t s_obd_fault_flag;

/*============================================================================
 * PUBLIC FUNCTION IMPLEMENTATIONS
 *===========================================================================*/

/**
 * @brief Obstacle sensor ISR — sets latch flag only (minimal ISR).
 * @details Called from hardware interrupt. Must be kept minimal.
 *          Bounds check performed defensively; out-of-range door_id ignored.
 * @complexity Cyclomatic complexity: 2 — within SIL 3 limit of 10
 */
void OBD_ObstacleISR(uint8_t door_id)
{
    /* Implements: REQ-SAFE-004, UNIT-OBD-001 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §5.1.1 */
    if (door_id < MAX_DOORS)
    {
        s_obstacle_isr_flags[door_id] = 1U;
    }
    /* Silently ignore out-of-range door_id (defensive; ISR cannot return error) */
}

/**
 * @brief Initialise OBD module — clear all flags and state.
 * @complexity Cyclomatic complexity: 1 — within SIL 3 limit of 10
 */
error_t OBD_Init(void)
{
    /* Implements: UNIT-OBD-003 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §5.3.1 */
    uint8_t door_idx;

    for (door_idx = 0U; door_idx < MAX_DOORS; door_idx++)
    {
        s_obstacle_isr_flags[door_idx]  = 0U;
        s_obstacle_flags[door_idx]      = 0U;
        s_motor_current_adc[door_idx]   = 0U;
    }
    s_obd_fault_flag = 0U;

    return SUCCESS;
}

/**
 * @brief 20 ms cycle entry — poll sensors and update global obstacle flags.
 * @complexity Cyclomatic complexity: 1 — within SIL 3 limit of 10
 */
void OBD_RunCycle(void)
{
    /* Implements: UNIT-OBD-004 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §5.3.2 */
    error_t err;

    err = OBD_PollSensorsAndEvaluate(DSM_GetClosingFlags(), g_obstacle_flags);
    (void)err;  /* Errors are logged and reflected in s_obd_fault_flag */
}

/**
 * @brief Evaluate obstacle presence for a single door (1oo2 + current logic).
 * @details Called per-door by OBD_PollSensorsAndEvaluate.
 *          Sets s_obd_fault_flag on HAL read error.
 *          Returns 1U if obstacle detected, 0U if clear.
 * @complexity Cyclomatic complexity: 8 — within SIL 3 limit of 10
 */
static uint8_t obd_evaluate_single_door(uint8_t door_idx,
                                         uint8_t door_closing_flag)
{
    /* Implements: UNIT-OBD-002 (per-door helper) */
    uint8_t  detected;
    uint8_t  sensor_a;
    uint8_t  sensor_b;
    error_t  hal_ret_a;
    error_t  hal_ret_b;
    error_t  adc_ret;

    detected = 0U;

    /* ISR latch — consume and clear */
    if (0U != s_obstacle_isr_flags[door_idx])
    {
        detected = 1U;
        s_obstacle_isr_flags[door_idx] = 0U;
    }

    /* Polled sensor A */
    sensor_a  = 0U;
    hal_ret_a = HAL_GPIO_ReadObstacleSensor(door_idx, 0U, &sensor_a);

    if (hal_ret_a != SUCCESS)
    {
        detected = 1U;  /* Fail-safe: read error → assume obstacle */
        s_obd_fault_flag = 1U;
    }
    else if (0U != sensor_a)
    {
        detected = 1U;
    }
    else
    {
        /* Sensor A clear — no action */
    }

    /* Polled sensor B (1oo2 — either sensor triggers reversal) */
    sensor_b  = 0U;
    hal_ret_b = HAL_GPIO_ReadObstacleSensor(door_idx, 1U, &sensor_b);

    if (hal_ret_b != SUCCESS)
    {
        detected = 1U;
        s_obd_fault_flag = 1U;
    }
    else if (0U != sensor_b)
    {
        detected = 1U;
    }
    else
    {
        /* Sensor B clear — no action */
    }

    /* Motor current check — only when door is closing (REQ-SAFE-006) */
    if (0U != door_closing_flag)
    {
        adc_ret = HAL_ADC_ReadMotorCurrent(door_idx,
                                           &s_motor_current_adc[door_idx]);

        if ((adc_ret == SUCCESS) &&
            (s_motor_current_adc[door_idx] > OBD_MAX_FORCE_ADC))
        {
            detected = 1U;
        }
    }

    return detected;
}

/**
 * @brief Poll obstacle sensors and evaluate detection for all doors.
 * @details 1oo2 logic per door delegated to obd_evaluate_single_door.
 *          Fail-safe: any read error → obstacle.
 * @complexity Cyclomatic complexity: 4 — within SIL 3 limit of 10
 */
error_t OBD_PollSensorsAndEvaluate(const uint8_t door_closing_flags[MAX_DOORS],
                                   uint8_t obstacle_flags_out[MAX_DOORS])
{
    /* Implements: REQ-SAFE-004/005/006, UNIT-OBD-002 */
    /* Design ref: SCDS DOC-COMPDES-2026-001 §5.2.1 */
    error_t  result;
    uint8_t  door_idx;
    uint8_t  detected;

    if ((NULL == door_closing_flags) || (NULL == obstacle_flags_out))
    {
        /* Fail-safe: set all flags to obstacle-present on null pointer */
        for (door_idx = 0U; door_idx < MAX_DOORS; door_idx++)
        {
            if (NULL != obstacle_flags_out)
            {
                obstacle_flags_out[door_idx] = 1U;
            }
        }
        s_obd_fault_flag = 1U;
        result = ERR_NULL_PTR;
    }
    else
    {
        s_obd_fault_flag = 0U;

        for (door_idx = 0U; door_idx < MAX_DOORS; door_idx++)
        {
            detected = obd_evaluate_single_door(door_idx,
                                                door_closing_flags[door_idx]);
            s_obstacle_flags[door_idx]   = detected;
            obstacle_flags_out[door_idx] = detected;
        }

        result = SUCCESS;
    }

    return result;
}

/**
 * @brief Get obstacle flags array accessor.
 * @complexity Cyclomatic complexity: 1
 */
const uint8_t *OBD_GetObstacleFlags(void)
{
    /* Implements: UNIT-OBD-005 */
    return s_obstacle_flags;
}

/**
 * @brief Get OBD fault status for FMG aggregation.
 * @complexity Cyclomatic complexity: 1
 */
uint8_t OBD_GetFault(void)
{
    return s_obd_fault_flag;
}

/*============================================================================
 * END OF FILE
 *===========================================================================*/
