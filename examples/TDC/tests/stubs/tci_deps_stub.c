/**
 * @file    tci_deps_stub.c
 * @brief   Stubs for DSM/FMG/SKN functions called by tci_init.c and tci_rx.c.
 *          tci_init.c calls: SKN_GetDepartureInterlock, DSM_GetDoorStates,
 *          DSM_GetLockStates, FMG_GetFaultState.
 *          tci_rx.c calls: DSM_ProcessOpenCommand, DSM_ProcessCloseCommand,
 *          FMG_ProcessEmergencyStop.
 *
 * @project TDC (Train Door Control System) — Unit Test Build Support
 * @note    NOT safety software.  Test infrastructure only.
 */

#include <stdint.h>
#include <stddef.h>
#include "tdc_types.h"
#include "dsm.h"
#include "fmg.h"
#include "skn.h"

/* -------------------------------------------------------------------------
 * Static stub state
 * ------------------------------------------------------------------------- */
static uint8_t s_door_states[MAX_DOORS]  = {0U, 0U, 0U, 0U};
static uint8_t s_lock_states[MAX_DOORS]  = {0U, 0U, 0U, 0U};
static uint8_t s_fault_state             = 0U;
static uint8_t s_departure_interlock     = 0U;

/* -------------------------------------------------------------------------
 * DSM stubs
 * ------------------------------------------------------------------------- */
const uint8_t *DSM_GetDoorStates(void)
{
    return s_door_states;
}

const uint8_t *DSM_GetLockStates(void)
{
    return s_lock_states;
}

error_t DSM_ProcessOpenCommand(uint8_t door_mask)
{
    (void)door_mask;
    return SUCCESS;
}

error_t DSM_ProcessCloseCommand(uint8_t door_mask)
{
    (void)door_mask;
    return SUCCESS;
}

/* -------------------------------------------------------------------------
 * FMG stubs
 * ------------------------------------------------------------------------- */
uint8_t FMG_GetFaultState(void)
{
    return s_fault_state;
}

error_t FMG_ProcessEmergencyStop(uint8_t stop_code)
{
    (void)stop_code;
    return SUCCESS;
}

/* -------------------------------------------------------------------------
 * SKN stubs
 * ------------------------------------------------------------------------- */
uint8_t SKN_GetDepartureInterlock(void)
{
    return s_departure_interlock;
}

/* -------------------------------------------------------------------------
 * Test-only setter helpers — allow test cases to inject stub return values.
 * NOT part of safety software.
 * ------------------------------------------------------------------------- */
void tci_stub_set_fault_state(uint8_t val)       { s_fault_state         = val; }
void tci_stub_set_departure_interlock(uint8_t v) { s_departure_interlock = v;   }
