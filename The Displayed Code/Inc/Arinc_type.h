/**
 * @file    Arinc_type.h
 * @author  StitchLilo626 qgwei626@gmail.com
 * @date    2025-05-05
 * @version 1.0
 * @brief   ARINC 429 type definitions header file
 */

#ifndef ARINC_TYPE_H
#define ARINC_TYPE_H

#include <stdint.h>

/** ARINC communication status codes */
typedef enum
{
    ARINC_OK = 0,
    ARINC_ERR_CHANNEL_INVALID,
    ARINC_ERR_DRIVER_NOT_READY,
    ARINC_ERR_PARAM_INVALID
} ARINC_Status;

/** Channel state enumeration */
typedef enum
{
    CHANNEL_STATE_DISABLED = 0x00,  /* Channel disabled */
    CHANNEL_STATE_ENABLED  = 0x01   /* Channel enabled */
} ChannelState;

/** Baud rate configuration enumeration */
typedef enum
{
    BAUD_CONFIG_LOW  = 0x00,  /* Low baud rate */
    BAUD_CONFIG_HIGH = 0x01   /* High baud rate */
} BaudRate;

/** Parity mode enumeration */
typedef enum
{
    PARITY_NONE = 0x00,  /* No parity */
    PARITY_ODD  = 0x01,  /* Odd parity */
    PARITY_EVEN = 0x02   /* Even parity */
} Parity;

/** Source/Destination code check mode enumeration (XY bit combination) */
typedef enum
{
    SD_CHECK_OFF = 0,  /* Check disabled */
    XY_00        = 1,  /* X=0, Y=0 */
    XY_01        = 2,  /* X=0, Y=1 */
    XY_10        = 3,  /* X=1, Y=0 */
    XY_11        = 4   /* X=1, Y=1 */
} SDCheckMode;

/**
 * @brief UART message structure
 * @note  payload[0]: upper 4 bits - baud, lower 4 bits - parity
 *        payload[1]: upper 4 bits - SDn, lower 4 bits - channel enable
 *        payload[2]: label check
 *        payload[3]: reserved
 */
typedef struct
{
    uint8_t channel;
    uint8_t payload[4];
} UartMsg;

/**
 * @brief ARINC configuration structure
 */
typedef struct
{
    uint8_t channel;
    BaudRate rate;
    SDCheckMode SDn;
    Parity parity;
    uint8_t label;  /* Label check byte */
} ARINC_Config;

/**
 * @brief ARINC message structure
 */
typedef struct
{
    uint8_t channel;  /* Channel number */
    uint32_t data;    /* Data content */
} ArincMsg;

/**
 * @brief ARINC command structure
 */
typedef struct
{
    ARINC_Config config;  /* Configuration parameters */
} ArincCmd;

/** Hardware interface type enumeration */
typedef enum
{
    ARINC_IF_DEI1016 = 0,
    ARINC_IF_HI3593  = 1,
    ARINC_IF_HI8588  = 2,  /* Add new hardware here */
    ARINC_IF_TYPE_COUNT
} ARINC_InterfaceType;

/**
 * @brief Channel enable state management structure
 */
#pragma pack(push, 1)
typedef union {
    uint16_t value;  /* 16-bit integer for direct access */
    struct {
        uint16_t receiver0     : 1;  /* Receiver channel 0 */
        uint16_t transmitter0  : 1;  /* Transmitter channel 0 */
        uint16_t receiver1     : 1;  /* Receiver channel 1 */
        uint16_t transmitter1  : 1;  /* Transmitter channel 1 */
        uint16_t receiver2     : 1;  /* Receiver channel 2 */
        uint16_t transmitter2  : 1;  /* Transmitter channel 2 */
        uint16_t receiver3     : 1;  /* Receiver channel 3 */
        uint16_t transmitter3  : 1;  /* Transmitter channel 3 */
        uint16_t receiver4     : 1;  /* Receiver channel 4 */
        uint16_t transmitter4  : 1;  /* Transmitter channel 4 */
        uint16_t receiver5     : 1;  /* Receiver channel 5 */
        uint16_t transmitter5  : 1;  /* Transmitter channel 5 */
        uint16_t receiver6     : 1;  /* Receiver channel 6 */
        uint16_t transmitter6  : 1;  /* Transmitter channel 6 */
        uint16_t receiver7     : 1;  /* Receiver channel 7 */
        uint16_t transmitter7  : 1;  /* Transmitter channel 7 */
    } bits;  /* Bit field structure */
} ChannelStateUnion;
#pragma pack(pop)

#endif