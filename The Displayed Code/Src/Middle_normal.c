/**
 * @file    Middle_normal.c
 * @author  StitchLilo626 qgwei626@gmail.com
 * @date    2025-05-09
 * @version 1.0
 * @brief   ARINC 429 middle layer driver implementation file
 */

#include "Inc/Middle_normal.h"
#include <string.h>

/**
 * @brief  Driver operation table (function pointers for each hardware type)
 */
ARINC_DriverOps driver_ops[ARINC_IF_TYPE_COUNT] = {0};

/**
 * @brief  Register a hardware driver to the driver operation table
 * @param  type Hardware interface type
 * @param  ops  Pointer to ARINC_DriverOps structure
 * @retval ARINC_Status Register status code
 */
ARINC_Status arinc_adaptor_register_driver(ARINC_InterfaceType type, const ARINC_DriverOps* ops) {
    if (type >= ARINC_IF_TYPE_COUNT || !ops || !ops->init ||
        !ops->send || !ops->receive || !ops->deinit) {
        return ARINC_ERR_PARAM_INVALID;
    }
    rt_mutex_take(&driver_ops_mutex, RT_WAITING_FOREVER);
    memcpy(&driver_ops[type], ops, sizeof(ARINC_DriverOps));
    rt_mutex_release(&driver_ops_mutex);

    return ARINC_OK;
}

/**
 * @brief  Calculate ARINC 429 data word parity
 * @param  data ARINC 429 data word (32 bits)
 * @param  parityType Parity type (PARITY_NONE, PARITY_ODD, PARITY_EVEN)
 * @retval Calculated parity bit
 */
uint8_t calculateParity(uint32_t data, Parity parityType) {
    uint8_t parity = 0;

    /* Count number of 1s */
    while (data) {
        parity ^= (data & 1);
        data >>= 1;
    }

    /* Adjust result based on parity type */
    switch (parityType) {
        case PARITY_NONE:
            return 0;
        case PARITY_ODD:
            return parity;
        case PARITY_EVEN:
            return !parity;
        default:
            return 0;
    }
}

/**
 * @brief  Calculate device ID from ARINC channel number
 * @param  channel ARINC channel number (0-15)
 * @retval Device ID (0-3), returns 0xFF if parameter is invalid
 */
uint8_t channel_to_device_id(uint8_t channel) {
    if (channel >= MAX_CHANNELS) {
        return 0xFF;
    }
    /* Each 4 channels correspond to one device (0~3→0, 4~7→1, 8~11→2, 12~15→3) */
    return channel / 4;
}

/**
 * @brief  Calculate ARINC channel number from device ID and receiver number
 * @param  device_id Device ID, range 0-3 (corresponds to 4 DEI1016 devices)
 * @param  receiver  Active receiver number, 0 or 1 (0=receiver1, 1=receiver2)
 * @retval Channel number (0-15), returns 0xFF if parameter is invalid
 */
uint8_t get_arinc_channel(uint8_t device_id, uint8_t receiver) {
    /* Parameter validity check */
    if (device_id >= MAX_DEVICES || receiver > 1) {
        return 0xFF;
    }
    /* Channel calculation rule:
     * device 0: receiver 0 → channel 0, receiver 1 → channel 2
     * device 1: receiver 0 → channel 4, receiver 1 → channel 6
     * device 2: receiver 0 → channel 8, receiver 1 → channel 10
     * device 3: receiver 0 → channel 12, receiver 1 → channel 14
     */
    return (device_id << 2) | (receiver << 1);
}
