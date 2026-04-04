/**
 * @file    obd_dsm_stub.c
 * @brief   DSM stub for OBD unit tests.
 *          obd_detect.c calls DSM_GetClosingFlags() to determine which
 *          doors are closing.  This stub returns a controllable array.
 *
 * @project TDC (Train Door Control System) — Unit Test Build Support
 * @note    NOT safety software.  Test infrastructure only.
 */

#include <stdint.h>
#include <stddef.h>
#include "dsm.h"
#include "tdc_types.h"

static uint8_t s_closing_flags[MAX_DOORS] = {0U, 0U, 0U, 0U};

void obd_stub_set_closing_flags(const uint8_t flags[MAX_DOORS])
{
    uint8_t i;
    for (i = 0U; i < MAX_DOORS; i++)
    {
        s_closing_flags[i] = flags[i];
    }
}

const uint8_t *DSM_GetClosingFlags(void)
{
    return s_closing_flags;
}
