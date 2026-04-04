/**
 * @file    skn_globals_stub.c
 * @brief   Defines the global safety state variables owned by skn_scheduler.c.
 *          For test binaries that do NOT compile skn_scheduler.c (to avoid
 *          pulling in all module headers), these definitions provide the
 *          required linker symbols.
 *
 * @project TDC (Train Door Control System) — Unit Test Build Support
 * @note    NOT safety software.  Test infrastructure only.
 */

#include <stdint.h>
#include "tdc_types.h"

/** @brief Global safe-state flag (owned by skn_scheduler.c in production) */
uint8_t g_safe_state_active      = 1U;  /* Default fail-safe ON */

/** @brief Global speed interlock flag */
uint8_t g_speed_interlock_active = 1U;  /* Default inhibit at startup */

/** @brief Global obstacle flags per door */
uint8_t g_obstacle_flags[MAX_DOORS] = {0U, 0U, 0U, 0U};
