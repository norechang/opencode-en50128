/**
 * @file    spm_tci_stub.c
 * @brief   TCI stub for SPM unit tests.
 *          spm_can.c calls TCI_GetSpeedFramePtr() to get the latest speed
 *          frame.  This stub lets tests inject a controlled frame pointer.
 *
 * @project TDC (Train Door Control System) — Unit Test Build Support
 * @note    NOT safety software.  Test infrastructure only.
 */

#include <stdint.h>
#include <stddef.h>
#include "tci.h"
#include "tdc_types.h"

static const tcms_speed_msg_t *s_frame_ptr = NULL;

void spm_stub_set_speed_frame(const tcms_speed_msg_t *f, uint8_t valid)
{
    (void)valid;
    s_frame_ptr = f;
}

const tcms_speed_msg_t *TCI_GetSpeedFramePtr(void)
{
    return s_frame_ptr;
}
