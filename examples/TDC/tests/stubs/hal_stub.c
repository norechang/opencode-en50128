/**
 * @file    hal_stub.c
 * @brief   HAL stub functions for unit tests that need to control HAL return
 *          values without real hardware.  Tests that need specific HAL
 *          behaviour can set the control variables declared below.
 *
 * @project TDC (Train Door Control System) — Unit Test Build Support
 * @note    NOT safety software.  Test infrastructure only.
 */

#include <stdint.h>
#include <stddef.h>
#include "hal.h"
#include "tdc_types.h"

/* -------------------------------------------------------------------------
 * Controllable return values for HAL stubs
 * Tests set these before calling the function under test.
 * ------------------------------------------------------------------------- */
error_t  hal_stub_can_receive_ret   = SUCCESS;
uint32_t hal_stub_can_receive_id    = 0x100U;
uint8_t  hal_stub_can_receive_data[8] = {0};
uint8_t  hal_stub_can_receive_dlc   = 5U;

error_t  hal_stub_can_transmit_ret  = SUCCESS;
error_t  hal_stub_spi_exchange_ret  = SUCCESS;
error_t  hal_stub_watchdog_ret      = SUCCESS;
uint32_t hal_stub_tick_ms           = 0U;
uint8_t  hal_stub_gpio_value        = 0U;   /* position/lock sensor value */
uint8_t  hal_stub_emerg_gpio        = 0U;   /* emergency release GPIO */
error_t  hal_stub_motor_start_ret   = SUCCESS;
error_t  hal_stub_motor_stop_ret    = SUCCESS;
error_t  hal_stub_lock_engage_ret   = SUCCESS;
error_t  hal_stub_lock_disengage_ret = SUCCESS;

/* Remote SPI state for SKN exchange tests */
#include "skn.h"
static cross_channel_state_t s_spi_remote;
void hal_stub_set_spi_remote(const cross_channel_state_t *r)
{
    if (r != NULL) { s_spi_remote = *r; }
}

/* -------------------------------------------------------------------------
 * HAL stub implementations
 * ------------------------------------------------------------------------- */

uint32_t HAL_GetSystemTickMs(void)
{
    return hal_stub_tick_ms;
}

error_t HAL_CAN_Receive(uint32_t *msg_id_out, uint8_t *data_out, uint8_t *dlc_out)
{
    uint8_t i;
    if ((msg_id_out == NULL) || (data_out == NULL) || (dlc_out == NULL))
    {
        return ERR_NULL_PTR;
    }
    if (hal_stub_can_receive_ret != SUCCESS)
    {
        return hal_stub_can_receive_ret;
    }
    *msg_id_out = hal_stub_can_receive_id;
    *dlc_out    = hal_stub_can_receive_dlc;
    for (i = 0U; i < 8U; i++)
    {
        data_out[i] = hal_stub_can_receive_data[i];
    }
    return SUCCESS;
}

error_t HAL_CAN_Transmit(uint32_t msg_id, const uint8_t *data, uint8_t dlc)
{
    (void)msg_id;
    (void)data;
    (void)dlc;
    return hal_stub_can_transmit_ret;
}

error_t HAL_SPI_CrossChannel_Exchange(const cross_channel_state_t *local,
                                       cross_channel_state_t       *remote_out)
{
    (void)local;
    if (remote_out != NULL)
    {
        *remote_out = s_spi_remote;
    }
    return hal_stub_spi_exchange_ret;
}

error_t HAL_Watchdog_Refresh(void)
{
    return hal_stub_watchdog_ret;
}

error_t HAL_GPIO_ReadPositionSensor(uint8_t door_id, uint8_t sensor_id,
                                     uint8_t *value_out)
{
    if (value_out == NULL)          { return ERR_NULL_PTR; }
    if (door_id >= MAX_DOORS)       { return ERR_RANGE; }
    if (sensor_id >= 2U)            { return ERR_RANGE; }
    *value_out = hal_stub_gpio_value;
    return SUCCESS;
}

error_t HAL_GPIO_ReadLockSensor(uint8_t door_id, uint8_t sensor_id,
                                 uint8_t *value_out)
{
    if (value_out == NULL)    { return ERR_NULL_PTR; }
    if (door_id >= MAX_DOORS) { return ERR_RANGE; }
    if (sensor_id >= 2U)      { return ERR_RANGE; }
    *value_out = hal_stub_gpio_value;
    return SUCCESS;
}

uint8_t HAL_GPIO_ReadEmergencyRelease(uint8_t door_id)
{
    (void)door_id;
    return hal_stub_emerg_gpio;
}

error_t HAL_MotorStart(uint8_t door_id, uint8_t direction)
{
    (void)door_id;
    (void)direction;
    return hal_stub_motor_start_ret;
}

error_t HAL_MotorStop(uint8_t door_id)
{
    (void)door_id;
    return hal_stub_motor_stop_ret;
}

error_t HAL_LockEngage(uint8_t door_id)
{
    (void)door_id;
    return hal_stub_lock_engage_ret;
}

error_t HAL_LockDisengage(uint8_t door_id)
{
    (void)door_id;
    return hal_stub_lock_disengage_ret;
}

error_t HAL_Init(void)
{
    return SUCCESS;
}

error_t HAL_GPIO_ReadObstacleSensor(uint8_t door_id, uint8_t sensor_id,
                                     uint8_t *value_out)
{
    if (value_out == NULL)    { return ERR_NULL_PTR; }
    if (door_id >= MAX_DOORS) { return ERR_RANGE; }
    if (sensor_id >= 2U)      { return ERR_RANGE; }
    *value_out = hal_stub_gpio_value;
    return SUCCESS;
}

error_t HAL_ADC_ReadMotorCurrent(uint8_t door_id, uint16_t *adc_value)
{
    if (adc_value == NULL)    { return ERR_NULL_PTR; }
    if (door_id >= MAX_DOORS) { return ERR_RANGE; }
    *adc_value = 0U;
    return SUCCESS;
}

error_t HAL_GPIO_SetMotorDirection(uint8_t door_id, uint8_t direction)
{
    (void)direction;
    if (door_id >= MAX_DOORS) { return ERR_RANGE; }
    return SUCCESS;
}

error_t HAL_GPIO_SetLockActuator(uint8_t door_id, uint8_t locked)
{
    (void)locked;
    if (door_id >= MAX_DOORS) { return ERR_RANGE; }
    return SUCCESS;
}

error_t HAL_PWM_SetDutyCycle(uint8_t door_id, uint8_t duty_pct)
{
    (void)duty_pct;
    if (door_id >= MAX_DOORS) { return ERR_RANGE; }
    return SUCCESS;
}

uint8_t HAL_GetFault(void)
{
    return 0U;
}
