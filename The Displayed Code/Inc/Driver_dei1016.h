/**
 * @file    Driver_dei1016.h
 * @author  StitchLilo626 qgwei626@gmail.com
 * @date    2025-05-11
 * @version 1.0
 * @brief   DEI1016 device structure definition header file
 */

#ifndef __DEI1016_H_
#define __DEI1016_H_

#include "Driver_dei1016_config.h"
#include "Middle_normal.h"

/**
 * @brief  DEI1016 device structure
 */
typedef struct {
    GPIO_TypeDef* data_port;           /** Data bus port (D0-D15) */
    /* Control pins */
    GPIO_TypeDef* ld1_port;  uint16_t ld1_pin;
    GPIO_TypeDef* ld2_port;  uint16_t ld2_pin;
    GPIO_TypeDef* oe1_port;  uint16_t oe1_pin;
    GPIO_TypeDef* oe2_port;  uint16_t oe2_pin;
    GPIO_TypeDef* entx_port; uint16_t entx_pin;
    GPIO_TypeDef* sel_port;  uint16_t sel_pin;
    GPIO_TypeDef* mr_port;   uint16_t mr_pin;
    GPIO_TypeDef* ldcw_port; uint16_t ldcw_pin;
    /* Interrupt pins */
    GPIO_TypeDef* dr1_port;  uint16_t dr1_pin;
    GPIO_TypeDef* dr2_port;  uint16_t dr2_pin;
    /* DMA configuration */
    DMA_HandleTypeDef* hdma;         /** Device-specific DMA handle */
    volatile bool dma_active;        /** DMA active flag */
    /* Data bus direction status */
    uint8_t data_bus_direction;      /** Current direction (0=input, 1=output) */
    uint8_t data_bus_direction_orig; /** Original direction (for restore) */
    /* Data storage (2D array: [receiver][word1/word2]) */
    uint16_t rx_buffer[2][2];        /** rx_buffer[0][0]=RX1 word1, rx_buffer[0][1]=RX1 word2
                                          rx_buffer[1][0]=RX2 word1, rx_buffer[1][1]=RX2 word2 */
    uint8_t dr_pending;              /** Bit0: DR1 pending, Bit1: DR2 pending */
    uint8_t active_receiver;         /** Current active receiver (0=RX1, 1=RX2) */
    uint8_t word_stage;              /** Receive stage: 0=word1, 1=word2 */
} DEI1016_Device;

extern DEI1016_Device dei_devices[MAX_DEVICES];

#endif /* __DEI1016_H_ */
