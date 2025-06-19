/**
 * @file    Middle_adaptor.h
 * @author  StitchLilo626 qgwei626@gmail.com
 * @date    2025-05-08
 * @version 1.0
 * @brief   ARINC 429 middle layer adaptor interface header file
 */

#ifndef ARINC_ADAPTOR_H
#define ARINC_ADAPTOR_H
#include "Arinc_config.h"
#include "App_adaptor.h"
#include "Middle_normal.h"

/*Middle layer interface*/ 
ARINC_Status arinc_adaptor_init(const ARINC_Config* cfg);
ARINC_Status arinc_adaptor_send(uint8_t channel, const uint32_t* data, uint16_t len);
ARINC_Status arinc_adaptor_receive(uint8_t channel, uint32_t* buffer, uint16_t len);
ARINC_Status arinc_adaptor_deinit(uint8_t channel);

#endif /* ARINC_ADAPTOR_H_ */
