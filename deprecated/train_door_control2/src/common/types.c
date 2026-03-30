/**
 * @file types.c
 * @brief Common type implementations
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3 (Common)
 */

#include "types.h"

/*===========================================================================*/
/* Static Variables                                                          */
/*===========================================================================*/

/** @brief System time counter (milliseconds) - stub implementation */
static volatile uint32_t g_system_time_ms = 0U;

/*===========================================================================*/
/* Function Implementations                                                  */
/*===========================================================================*/

/**
 * @brief Get current system time in milliseconds
 * @return System time in milliseconds since boot
 * @note Stub implementation - platform-specific timer required
 * @complexity 1 (no branches)
 */
uint32_t get_system_time_ms(void)
{
    /* In real implementation, read hardware timer */
    /* For now, return static counter */
    return g_system_time_ms;
}
