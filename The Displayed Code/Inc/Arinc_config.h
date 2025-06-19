/**
 * @file    Arinc_config.h
 * @author  StitchLilo626 qgwei626@gmail.com
 * @date    2025-04-24
 * @version 1.0
 * @brief   ARINC 429 configuration header file
 */

#ifndef ARINC_CONFIG_H
#define ARINC_CONFIG_H

#include <stdio.h>
#include <stdbool.h>
#include "Arinc_type.h"

/**
 * @brief  Debug switch
 */
#define DEBUG 0 

#if DEBUG
    #define DEBUG_PRINTF(format, ...) printf("[DEBUG] " format, ##__VA_ARGS__)
#else
    #define DEBUG_PRINTF(format, ...) ((void)0) /**< No-operation when debug is off */
#endif

/**
 * @brief  Device and channel configuration
 */
#define MAX_DEVICES   4   /**< Number of devices, each supports 2 channels */
#define MAX_CHANNELS 16   /**< Total number of channels (0-15) */

/**
 * @brief  Hardware driver selection
 */
#define USE_DEI1016 1     /**< Enable DEI1016 driver */
#define USE_HI3593 0      /**< Enable HI3593 driver */
#define USE_HI8588 0      /**< Enable Hi8588/8585 driver */

/**
 * @brief  Ensure only one hardware driver is enabled
 */
#if (USE_DEI1016 + USE_HI3593 + USE_HI8588) > 1
    #error "Only one hardware driver can be enabled"
#endif

/**
 * @brief  Define hardware type based on enabled driver
 */
#if USE_DEI1016
    #define SELECTED_HW_TYPE ARINC_IF_DEI1016
#elif USE_HI3593
    #define SELECTED_HW_TYPE ARINC_IF_HI3593
#elif USE_HI8588
    #define SELECTED_HW_TYPE ARINC_IF_HI8588
#endif

/**
 * @brief  Device self-test configuration
 */
#define DEV0_SELF_TEST 0
#define DEV1_SELF_TEST 0
#define DEV2_SELF_TEST 0
#define DEV3_SELF_TEST 0

/**
 * @brief  Frame configuration
 */
#define FRAME_SIZE    7      /**< 1 header + 1 channel + 4 data + 1 CRC */
#define CMD_HEADER    0xAA
#define ARINC_HEADER  0x55
#define MAX_LABEL     10     /**< Maximum number of label checks */
#define MAX_QUEUE_LEN 128    /**< Queue depth */

/**
 * @brief  Bit operation masks
 */
#define BAUD_MASK    0xF0
#define PARITY_MASK  0x0F
#define SDN_MASK     0xF0
#define CH_EN_MASK   0x0F

#endif
