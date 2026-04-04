/**
 * @file    crc_stub.c
 * @brief   CRC-16-CCITT implementation for test builds that use hal_stub.c
 *          instead of hal_services.c.
 *
 * @note    NOT safety software — test infrastructure only.
 *          Copies the production algorithm from hal_services.c so that
 *          SKN and other modules that call CRC16_CCITT_Compute can link
 *          when the real HAL is replaced by hal_stub.c.
 */

#include <stdint.h>
#include <stddef.h>
#include "hal.h"

/** @brief CRC-16-CCITT polynomial */
#define CRC16_POLY  (0x1021U)
/** @brief CRC-16-CCITT initial value */
#define CRC16_INIT  (0xFFFFU)

uint16_t CRC16_CCITT_Compute(const uint8_t *data, uint16_t length)
{
    uint16_t crc;
    uint16_t byte_idx;
    uint8_t  bit_idx;

    if ((NULL == data) || (0U == length))
    {
        crc = 0x0000U;
    }
    else
    {
        crc = CRC16_INIT;

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
