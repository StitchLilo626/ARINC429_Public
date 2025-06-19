/**
 * @file    App_adaptor.c
 * @author  StitchLilo626 qgwei626@gmail.com
 * @date    2025-05-04
 * @version 1.0
 * @brief   ARINC 429 application adaptor implementation file
 */

#include "Inc/App_adaptor.h"

/** 
  * @brief  Global channel control structure initialization 
  */
volatile ChannelStateUnion channel_state = {.value = 0};

/**
  * @brief  Initialize the ARINC adapter
  * @param  cfg: Pointer to the ARINC configuration structure
  * @retval ARINC_Status: Initialization status code
  */
ARINC_Status arinc_init(const ARINC_Config* cfg) {
    /** Parameter validation */
    if (!cfg || cfg->channel >= MAX_CHANNELS || 
        (cfg->rate != BAUD_CONFIG_LOW && cfg->rate != BAUD_CONFIG_HIGH)) {
        return ARINC_ERR_PARAM_INVALID;
    }
    
    /** Directly call the middle layer initialization */
    return arinc_adaptor_init(cfg);
}

/**
  * @brief  Send ARINC 429 data
  * @param  channel: Transmit channel number
  * @param  data: Pointer to the data array to be sent (32-bit data)
  * @param  len: Data length (in bytes)
  * @retval ARINC_Status: Send status code
  */
ARINC_Status arinc_send(uint8_t channel, const uint32_t *data, uint16_t len) {
    /** Channel number validation */
    if (channel >= MAX_CHANNELS) {
        return ARINC_ERR_CHANNEL_INVALID;
    }

    /** Data pointer and length validation */
    if (data == NULL || len == 0) {
        return ARINC_ERR_PARAM_INVALID;
    }
    if(CHANNEL_ENABLED(&channel_state, channel)){
        /** Call the middle layer send interface */
        return arinc_adaptor_send(channel, data, len);
    }else{
        DEBUG_PRINTF("[WARN] ch%u status0x%02X,failed\n",
                     channel,CHANNEL_ENABLED(&channel_state, channel)); 
        return ARINC_ERR_DRIVER_NOT_READY;
    }
}

/**
  * @brief  Receive ARINC 429 data
  * @param  channel: Receive channel number
  * @param  buffer: Pointer to the receive buffer (32-bit data)
  * @param  len: Buffer length (in bytes)
  * @retval ARINC_Status: Receive status code
  */
ARINC_Status arinc_receive(uint8_t channel, uint32_t* buffer, uint16_t len) {
    /** Channel validation */
    if (channel >= MAX_CHANNELS || !buffer || len == 0) {
        return ARINC_ERR_PARAM_INVALID;
    }

    return arinc_adaptor_receive(channel, buffer, len);
}

/**
  * @brief  Deinitialize the ARINC adapter
  * @param  channel: Channel number
  * @retval ARINC_Status: Deinitialization status code
  */
ARINC_Status arinc_deinit(uint8_t channel){

    if (channel >= MAX_CHANNELS) {
        return ARINC_ERR_PARAM_INVALID;
    }

    return arinc_adaptor_deinit(channel);
}
