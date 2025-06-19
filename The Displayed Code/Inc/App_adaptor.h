/**
 * @file    App_adaptor.h
 * @author  StitchLilo626 qgwei626@gmail.com
 * @date    2025-05-04
 * @version 1.0
 * @brief   ARINC 429 middle layer driver implementation file
 */

#ifndef ARINC_APP_H
#define ARINC_APP_H

#include "Arinc_config.h"

/**
 * @brief  Global channel control structure
 */
extern volatile ChannelStateUnion channel_state;

/* Application layer interface */
ARINC_Status arinc_init(const ARINC_Config* cfg);
ARINC_Status arinc_send(uint8_t channel, const uint32_t* data, uint16_t len);
ARINC_Status arinc_receive(uint8_t channel, uint32_t* buffer, uint16_t len);
ARINC_Status arinc_deinit(uint8_t channel);

/**
 * @brief  Set the value (0 or 1) of a specific channel using bitwise operation
 */
#define SET_CHANNEL(union_ptr, channel, val) \
    do { \
        if ((channel) < 16) { \
            if (val) { \
                (union_ptr)->value |= (1 << (channel)); \
            } else { \
                (union_ptr)->value &= ~(1 << (channel)); \
            } \
        } \
    } while (0)

/**
 * @brief  Check if a specific channel is enabled (bit is 1)
 */
#define CHANNEL_ENABLED(union_ptr, channel) \
    (((channel) < 16) ? (((union_ptr)->value & (1 << (channel))) != 0) : 0)



#endif
