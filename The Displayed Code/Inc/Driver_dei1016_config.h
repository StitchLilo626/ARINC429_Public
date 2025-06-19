/**
 * @file    Driver_dei1016_config.h
 * @author  StitchLilo626 qgwei626@gmail.com
 * @date    2025-05-10
 * @version 1.0
 * @brief   DEI1016 driver configuration header file
 */

#ifndef __DEI1016_CONFIG_H_
#define __DEI1016_CONFIG_H_

#include "Arinc_config.h"

/** 
 * @brief Pin type enumeration for specific control pins 
 */
typedef enum {
    MR_PIN,     /* Master reset */
    LDCW_PIN,   /* Load control word */
    LD1_PIN,    /* Load Word1 */
    LD2_PIN,    /* Load Word2 */
    OE1_PIN,    /* Receiver 1 enable */
    OE2_PIN,    /* Receiver 2 enable */
    ENTXPIN,    /* Transmitter enable */
    SEL_PIN     /* Data word select */
} DEI_PinType;

#pragma pack(push, 1)
/**
 * @brief DEI1016 control register union
 */
typedef union {
    uint16_t value;
    struct {
        uint16_t D0      : 1;  /* Control register D0 (reserved) */
        uint16_t D1      : 1;  /* Control register D1 (reserved) */
        uint16_t D2      : 1;  /* Control register D2 (reserved) */
        uint16_t D3      : 1;  /* Control register D3 (reserved) */
        uint16_t PAREN   : 1;  /* D4 */
        uint16_t SLFTST  : 1;  /* D5 */
        uint16_t SDENB1  : 1;  /* D6 */
        uint16_t X1Y1    : 2;  /* D7 D8 */
        uint16_t SDENB2  : 1;  /* D9 */
        uint16_t X2Y2    : 2;  /* D10 D11 */
        uint16_t PARCK   : 1;  /* D12 */
        uint16_t TXSEL   : 1;  /* D13 */
        uint16_t RCVSEL  : 1;  /* D14 */
        uint16_t WLSEL   : 1;  /* D15 */
    } bits;
} DEI1016_ControlReg;
#pragma pack(pop)

/** ==== GPIO assignment rules ==== */
/** - Data port: Device0→GPIOB, Device1→GPIOC, Device2→GPIOD, Device3→GPIOE */

/* Device 0 (Channel 0-3) */
/* Data bus PB0-PB15 */
#define DEV0_DATA_PORT      GPIOB
/* Control pins */
#define DEV0_LD1_PORT       GPIOF
#define DEV0_LD2_PORT       GPIOF
#define DEV0_OE1_PORT       GPIOF
#define DEV0_OE2_PORT       GPIOF
#define DEV0_ENTX_PORT      GPIOF
#define DEV0_SEL_PORT       GPIOF
#define DEV0_MR_PORT        GPIOF
#define DEV0_LDCW_PORT      GPIOF
#define DEV0_DR1_PORT       GPIOF
#define DEV0_DR2_PORT       GPIOF

/* Device 1 (Channel 4-7) */
/* Data bus PC0-PC15 */
#define DEV1_DATA_PORT      GPIOC
/* Control pins */
#define DEV1_LD1_PORT       GPIOF
#define DEV1_LD2_PORT       GPIOF
#define DEV1_OE1_PORT       GPIOF
#define DEV1_OE2_PORT       GPIOF
#define DEV1_ENTX_PORT      GPIOF
#define DEV1_SEL_PORT       GPIOF
#define DEV1_MR_PORT        GPIOG
#define DEV1_LDCW_PORT      GPIOG
#define DEV1_DR1_PORT       GPIOG
#define DEV1_DR2_PORT       GPIOG

/* Device 2 (Channel 8-11) */
/* Data bus PD0-PD15 */
#define DEV2_DATA_PORT      GPIOD
/* Control pins */
#define DEV2_LD1_PORT       GPIOG
#define DEV2_LD2_PORT       GPIOG
#define DEV2_OE1_PORT       GPIOG
#define DEV2_OE2_PORT       GPIOG
#define DEV2_ENTX_PORT      GPIOG
#define DEV2_SEL_PORT       GPIOG
#define DEV2_MR_PORT        GPIOG
#define DEV2_LDCW_PORT      GPIOG
#define DEV2_DR1_PORT       GPIOG
#define DEV2_DR2_PORT       GPIOG

/* Device 3 (Channel 12-15) */
/* Data bus PE0-PE15 */
#define DEV3_DATA_PORT      GPIOE
/* Control pins */
#define DEV3_LD1_PORT       GPIOG
#define DEV3_LD2_PORT       GPIOG
#define DEV3_OE1_PORT       GPIOA
#define DEV3_OE2_PORT       GPIOA
#define DEV3_ENTX_PORT      GPIOA
#define DEV3_SEL_PORT       GPIOA
#define DEV3_MR_PORT        GPIOA
#define DEV3_LDCW_PORT      GPIOA
#define DEV3_DR1_PORT       GPIOA
#define DEV3_DR2_PORT       GPIOA

#endif /* __DEI1016_CONFIG_H_ */
