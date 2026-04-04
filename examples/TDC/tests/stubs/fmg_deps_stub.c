/**
 * @file    fmg_deps_stub.c
 * @brief   Stubs for component fault-accessor functions called by fmg_init.c
 *          (FMG_RunCycle aggregates faults from SPM, OBD, DSM, TCI, OBD).
 *          Also provides OBD_GetObstacleFlags stub used by skn_scheduler deps.
 *
 * @project TDC (Train Door Control System) — Unit Test Build Support
 * @note    NOT safety software.  Test infrastructure only.
 */

#include <stdint.h>
#include "tdc_types.h"

/* -------------------------------------------------------------------------
 * Test-only setter helpers — allow test cases to inject fault conditions.
 * NOT part of safety software.
 * ------------------------------------------------------------------------- */
static uint8_t s_spm_fault  = 0U;
static uint8_t s_obd_fault  = 0U;
static uint8_t s_dsm_fault  = 0U;
static uint8_t s_tci_fault  = 0U;

void fmg_stub_set_spm_fault(uint8_t v) { s_spm_fault = v; }
void fmg_stub_set_obd_fault(uint8_t v) { s_obd_fault = v; }
void fmg_stub_set_dsm_fault(uint8_t v) { s_dsm_fault = v; }
void fmg_stub_set_tci_fault(uint8_t v) { s_tci_fault = v; }
void fmg_stub_reset_all(void)
{
    s_spm_fault = 0U; s_obd_fault = 0U;
    s_dsm_fault = 0U; s_tci_fault = 0U;
}

/* -------------------------------------------------------------------------
 * SPM stub
 * ------------------------------------------------------------------------- */
uint8_t SPM_GetFault(void)
{
    return s_spm_fault;
}

/* -------------------------------------------------------------------------
 * OBD stubs
 * ------------------------------------------------------------------------- */
uint8_t OBD_GetFault(void)
{
    return s_obd_fault;
}

static uint8_t s_obstacle_flags[MAX_DOORS] = {0U, 0U, 0U, 0U};

const uint8_t *OBD_GetObstacleFlags(void)
{
    return s_obstacle_flags;
}

/* -------------------------------------------------------------------------
 * DSM stubs (for FMG build only — not compiled alongside real DSM)
 * ------------------------------------------------------------------------- */
uint8_t DSM_GetFault(void)
{
    return s_dsm_fault;
}

/* -------------------------------------------------------------------------
 * TCI stub
 * ------------------------------------------------------------------------- */
uint8_t TCI_GetFault(void)
{
    return s_tci_fault;
}
