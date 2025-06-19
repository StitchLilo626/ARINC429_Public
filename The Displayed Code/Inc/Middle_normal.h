/**
 * @file    Middle_normal.h
 * @author  StitchLilo626 qgwei626@gmail.com
 * @date    2025-05-09
 * @version 1.0
 * @brief   ARINC 429 middle layer driver interface header file
 */

#ifndef ARINC_NORMAL_H
#define ARINC_NORMAL_H

#include "Arinc_config.h"

/** Hardware driver operation function pointer structure */
typedef struct {
    ARINC_Status (*init)(const ARINC_Config* config);
    ARINC_Status (*deinit)(uint8_t channel); 
    ARINC_Status (*send)(uint8_t channel, const uint32_t* data, uint16_t len);
    ARINC_Status (*receive)(uint8_t channel, uint32_t* buffer, uint16_t len);
} ARINC_DriverOps;

/** Hardware driver operation function pointer array */
extern ARINC_DriverOps driver_ops[ARINC_IF_TYPE_COUNT];

ARINC_Status arinc_adaptor_register_driver(ARINC_InterfaceType type, const ARINC_DriverOps* ops);
uint8_t calculateParity(uint32_t data, Parity parityType);
uint8_t channel_to_device_id(uint8_t channel);
uint8_t get_arinc_channel(uint8_t device_id, uint8_t receiver);

#endif /* ARINC_NORMAL_H */