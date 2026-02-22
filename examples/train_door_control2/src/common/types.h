/**
 * @file types.h
 * @brief Common type definitions for train door control system
 * 
 * @project train_door_control2
 * @sil SIL 3
 * @standard EN 50128:2011 Section 7.4
 * @compliance MISRA C:2012
 * @traceability DOC-COMPDES-2026-001 v1.0 Section 3 (Common)
 * 
 * @description
 * Provides common fixed-width types, enumerations, and structures
 * used across all modules. All types use static allocation only.
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*===========================================================================*/
/* Door Side Enumeration                                                     */
/*===========================================================================*/

/**
 * @brief Door side identifier (left or right)
 * @compliance MISRA C:2012 Rule 8.2 (complete function types)
 */
typedef enum {
    DOOR_SIDE_LEFT = 0U,
    DOOR_SIDE_RIGHT = 1U,
    DOOR_SIDE_MAX = 2U
} door_side_t;

/*===========================================================================*/
/* System Time Functions                                                     */
/*===========================================================================*/

/**
 * @brief Get current system time in milliseconds
 * @return System time in milliseconds since boot
 * @note This is a platform-specific function (stub for now)
 */
uint32_t get_system_time_ms(void);

#endif /* TYPES_H */
