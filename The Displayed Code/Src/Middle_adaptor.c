/**
 * @file    Middle_adaptor.c
 * @author  StitchLilo626 qgwei626@gmail.com
 * @date    2025-05-08
 * @version 1.0
 * @brief   ARINC 429 middle layer adaptor implementation file
 */

#include "Inc/Middle_adaptor.h"
#include <string.h>

/**
 * @brief  Initialize ARINC adaptor
 * @param  cfg Pointer to ARINC_Config structure
 * @retval ARINC_Status Initialization status code
 */
ARINC_Status arinc_adaptor_init(const ARINC_Config* cfg) {
    ARINC_InterfaceType hw_type = SELECTED_HW_TYPE;
    ARINC_Status ret = ARINC_ERR_DRIVER_NOT_READY;

    rt_mutex_take(&driver_ops_mutex, RT_WAITING_FOREVER);
    if (driver_ops[hw_type].init) {
        ret = driver_ops[hw_type].init(cfg);
    }
    rt_mutex_release(&driver_ops_mutex);

    return ret;
}

/**
 * @brief  Send ARINC 429 data
 * @param  channel Transmit channel number
 * @param  data Pointer to the data array to be sent (32-bit data)
 * @param  len Data length (in bytes)
 * @retval ARINC_Status Send status code
 */
ARINC_Status arinc_adaptor_send(uint8_t channel, const uint32_t* data, uint16_t len) {
    ARINC_InterfaceType hw_type = SELECTED_HW_TYPE;
    ARINC_Status ret = ARINC_ERR_DRIVER_NOT_READY;

    rt_mutex_take(&driver_ops_mutex, RT_WAITING_FOREVER);
    if (driver_ops[hw_type].send) {
        ret = driver_ops[hw_type].send(channel, data, len);
    }
    rt_mutex_release(&driver_ops_mutex);

    return ret;
}

/**
 * @brief  Receive ARINC 429 data
 * @param  channel Receive channel number
 * @param  buffer Pointer to the buffer to store received data (32-bit data)
 * @param  len Buffer length (in bytes)
 * @retval ARINC_Status Receive status code
 */
ARINC_Status arinc_adaptor_receive(uint8_t channel, uint32_t* buffer, uint16_t len) {
    ARINC_InterfaceType hw_type = SELECTED_HW_TYPE;
    ARINC_Status ret = ARINC_ERR_DRIVER_NOT_READY;

    rt_mutex_take(&driver_ops_mutex, RT_WAITING_FOREVER);
    if (driver_ops[hw_type].receive) {
        ret = driver_ops[hw_type].receive(channel, buffer, len);
    }
    rt_mutex_release(&driver_ops_mutex);

    return ret;
}

/**
 * @brief  Deinitialize ARINC adaptor
 * @param  channel Channel number
 * @retval ARINC_Status Deinitialization status code
 */
ARINC_Status arinc_adaptor_deinit(uint8_t channel) {
    ARINC_InterfaceType hw_type = SELECTED_HW_TYPE;
    ARINC_Status ret = ARINC_ERR_DRIVER_NOT_READY;

    rt_mutex_take(&driver_ops_mutex, RT_WAITING_FOREVER);
    if (driver_ops[hw_type].deinit) {
        ret = driver_ops[hw_type].deinit(channel);
    }
    rt_mutex_release(&driver_ops_mutex);

    return ret;
}

