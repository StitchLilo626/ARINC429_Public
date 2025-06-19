/**
 * @file    Driver_dei1016.c
 * @author  StitchLilo626 qgwei626@gmail.com
 * @date    2025-05-11
 * @version 1.0
 * @brief   DEI1016 driver implementation file
 */

#include "Inc/Driver_dei1016.h"

/**
 * @brief  Self-test configuration for each device
 */
uint16_t dei_self_test[MAX_DEVICES] = {DEV0_SELF_TEST, DEV1_SELF_TEST, DEV2_SELF_TEST, DEV3_SELF_TEST};

/**
 * @brief  Global device instance array
 */
DEI1016_Device dei_devices[MAX_DEVICES] = {
    {
        .data_port = DEV0_DATA_PORT,
        .ld1_port = DEV0_LD1_PORT, .ld1_pin = GPIO_PIN_0,
        .ld2_port = DEV0_LD2_PORT, .ld2_pin = GPIO_PIN_1,
        .oe1_port = DEV0_OE1_PORT, .oe1_pin = GPIO_PIN_2,
        .oe2_port = DEV0_OE2_PORT, .oe2_pin = GPIO_PIN_3,
        .entx_port = DEV0_ENTX_PORT, .entx_pin = GPIO_PIN_4,
        .sel_port = DEV0_SEL_PORT, .sel_pin = GPIO_PIN_5,
        .mr_port = DEV0_MR_PORT, .mr_pin = GPIO_PIN_6,
        .ldcw_port = DEV0_LDCW_PORT, .ldcw_pin = GPIO_PIN_7,
        .dr1_port = DEV0_DR1_PORT, .dr1_pin = GPIO_PIN_8,
        .dr2_port = DEV0_DR2_PORT, .dr2_pin = GPIO_PIN_9,
        .data_bus_direction = 1,
        .dma_active = false,
    #if USE_DEI1016
        .hdma = &hdma_memtomem_dma2_stream0,
    #endif
        .dr_pending = 0
    },
    {
        .data_port = DEV1_DATA_PORT,
        .ld1_port = DEV1_LD1_PORT, .ld1_pin = GPIO_PIN_10,
        .ld2_port = DEV1_LD2_PORT, .ld2_pin = GPIO_PIN_11,
        .oe1_port = DEV1_OE1_PORT, .oe1_pin = GPIO_PIN_12,
        .oe2_port = DEV1_OE2_PORT, .oe2_pin = GPIO_PIN_13,
        .entx_port = DEV1_ENTX_PORT, .entx_pin = GPIO_PIN_14,
        .sel_port = DEV1_SEL_PORT, .sel_pin = GPIO_PIN_15,
        .mr_port = DEV1_MR_PORT, .mr_pin = GPIO_PIN_0,
        .ldcw_port = DEV1_LDCW_PORT, .ldcw_pin = GPIO_PIN_1,
        .dr1_port = DEV1_DR1_PORT, .dr1_pin = GPIO_PIN_2,
        .dr2_port = DEV1_DR2_PORT, .dr2_pin = GPIO_PIN_3,
        .data_bus_direction = 1,
        .dma_active = false,
    #if USE_DEI1016
        .hdma = &hdma_memtomem_dma2_stream3,
    #endif
        .dr_pending = 0
    },
    {
        .data_port = DEV2_DATA_PORT,
        .ld1_port = DEV2_LD1_PORT, .ld1_pin = GPIO_PIN_4,
        .ld2_port = DEV2_LD2_PORT, .ld2_pin = GPIO_PIN_5,
        .oe1_port = DEV2_OE1_PORT, .oe1_pin = GPIO_PIN_6,
        .oe2_port = DEV2_OE2_PORT, .oe2_pin = GPIO_PIN_7,
        .entx_port = DEV2_ENTX_PORT, .entx_pin = GPIO_PIN_8,
        .sel_port = DEV2_SEL_PORT, .sel_pin = GPIO_PIN_9,
        .mr_port = DEV2_MR_PORT, .mr_pin = GPIO_PIN_10,
        .ldcw_port = DEV2_LDCW_PORT, .ldcw_pin = GPIO_PIN_11,
        .dr1_port = DEV2_DR1_PORT, .dr1_pin = GPIO_PIN_12,
        .dr2_port = DEV2_DR2_PORT, .dr2_pin = GPIO_PIN_13,
        .data_bus_direction = 1,
        .dma_active = false,
    #if USE_DEI1016
        .hdma = &hdma_memtomem_dma2_stream1,
    #endif
        .dr_pending = 0
    },
    {
        .data_port = DEV3_DATA_PORT,
        .ld1_port = DEV3_LD1_PORT, .ld1_pin = GPIO_PIN_14,
        .ld2_port = DEV3_LD2_PORT, .ld2_pin = GPIO_PIN_15,
        .oe1_port = DEV3_OE1_PORT, .oe1_pin = GPIO_PIN_4,
        .oe2_port = DEV3_OE2_PORT, .oe2_pin = GPIO_PIN_5,
        .entx_port = DEV3_ENTX_PORT, .entx_pin = GPIO_PIN_6,
        .sel_port = DEV3_SEL_PORT, .sel_pin = GPIO_PIN_7,
        .mr_port = DEV3_MR_PORT, .mr_pin = GPIO_PIN_8,
        .ldcw_port = DEV3_LDCW_PORT, .ldcw_pin = GPIO_PIN_13,
        .dr1_port = DEV3_DR1_PORT, .dr1_pin = GPIO_PIN_14,
        .dr2_port = DEV3_DR2_PORT, .dr2_pin = GPIO_PIN_15,
        .data_bus_direction = 1,
        .dma_active = false,
    #if USE_DEI1016
        .hdma = &hdma_memtomem_dma2_stream2,
    #endif
        .dr_pending = 0
    }
};

/**
 * @brief  Encode ARINC 429 data word
 * @param  word1: First 16-bit word
 * @param  word2: Second 16-bit word
 * @retval Encoded 32-bit ARINC 429 data
 */
static uint32_t arinc429_encode(uint16_t word1, uint16_t word2) {
    uint32_t arinc = 0;
    for (int i = 0; i < 8; i++) {
        arinc |= ((word1 >> i) & 0x01) << (7 - i);
    }
    arinc |= ((word1 >> 11) & 0x1F) << 8;
    arinc |= (word2 & 0x7FFF) << 13;
    arinc |= ((word2 >> 15) & 0x01) << 28;
    arinc |= ((word1 >> 9) & 0x03) << 29;
    arinc |= ((word1 >> 8) & 0x01) << 31;
    return arinc;
}

/**
 * @brief  Decode ARINC 429 data word to Word1 and Word2
 * @param  arinc: Encoded 32-bit ARINC 429 data
 * @param  word1: Pointer to store first 16-bit word
 * @param  word2: Pointer to store second 16-bit word
 * @retval None
 */
static void arinc429_decode(uint32_t arinc, uint16_t *word1, uint16_t *word2) {
    *word1 = 0;
    *word2 = 0;
    for (int i = 0; i < 8; i++) {
        *word1 |= ((arinc >> (7 - i)) & 0x01) << i;
    }
    *word1 |= ((arinc >> 8) & 0x1F) << 11;
    *word1 |= ((arinc >> 31) & 0x01) << 8;
    *word1 |= ((arinc >> 29) & 0x03) << 9;
    *word2 |= ((arinc >> 13) & 0x7FFF);
    *word2 |= ((arinc >> 28) & 0x01) << 15;
}

/**
 * @brief  Clear EXTI interrupt pending flag
 * @param  GPIO_Pin: Pin to clear
 */
static void EXTI_ClearPendingBit(uint32_t GPIO_Pin) {
    EXTI->PR = GPIO_Pin;
}

/**
 * @brief  High-speed GPIO write operation
 * @param  device_id: Device index
 * @param  pin_type: Pin type
 * @param  state: Pin state
 */
static void DEI_GPIO_WritePin(uint8_t device_id, DEI_PinType pin_type, GPIO_PinState state) {
    if (device_id >= MAX_DEVICES)
        return;
    DEI1016_Device *dev = &dei_devices[device_id];
    switch (pin_type) {
    case MR_PIN:
        state == GPIO_PIN_SET ? (dev->mr_port->BSRR = dev->mr_pin) : (dev->mr_port->BSRR = (uint32_t)dev->mr_pin << 16);
        break;
    case LDCW_PIN:
        state == GPIO_PIN_SET ? (dev->ldcw_port->BSRR = dev->ldcw_pin) : (dev->ldcw_port->BSRR = (uint32_t)dev->ldcw_pin << 16);
        break;
    case LD1_PIN:
        state == GPIO_PIN_SET ? (dev->ld1_port->BSRR = dev->ld1_pin) : (dev->ld1_port->BSRR = (uint32_t)dev->ld1_pin << 16);
        break;
    case LD2_PIN:
        state == GPIO_PIN_SET ? (dev->ld2_port->BSRR = dev->ld2_pin) : (dev->ld2_port->BSRR = (uint32_t)dev->ld2_pin << 16);
        break;
    case OE1_PIN:
        state == GPIO_PIN_SET ? (dev->oe1_port->BSRR = dev->oe1_pin) : (dev->oe1_port->BSRR = (uint32_t)dev->oe1_pin << 16);
        break;
    case OE2_PIN:
        state == GPIO_PIN_SET ? (dev->oe2_port->BSRR = dev->oe2_pin) : (dev->oe2_port->BSRR = (uint32_t)dev->oe2_pin << 16);
        break;
    case ENTXPIN:
        state == GPIO_PIN_SET ? (dev->entx_port->BSRR = dev->entx_pin) : (dev->entx_port->BSRR = (uint32_t)dev->entx_pin << 16);
        break;
    case SEL_PIN:
        state == GPIO_PIN_SET ? (dev->sel_port->BSRR = dev->sel_pin) : (dev->sel_port->BSRR = (uint32_t)dev->sel_pin << 16);
        break;
    default:
        break;
    }
}

/**
 * @brief  Set data bus direction (input or output)
 * @param  dev: Pointer to device structure
 * @param  is_output: 1 for output, 0 for input
 * @retval None
 */
static void set_data_bus_direction(DEI1016_Device *dev, uint8_t is_output) {
    if (is_output) {
        __disable_irq();
        if (!dev->dma_active) {
            dev->data_port->MODER = (dev->data_port->MODER & 0xFFFF0000) | 0x00005555;
        }
        __enable_irq();
    } else {
        __disable_irq();
        if (!dev->dma_active) {
            dev->data_port->MODER &= 0xFFFF0000;
        }
        __enable_irq();
    }
    if (!dev->dma_active) {
        dev->data_bus_direction = is_output;
    }
}

/**
 * @brief  Write to data bus
 * @param  dev: Pointer to device structure
 * @param  data: Data to write
 */
static void write_data_bus(DEI1016_Device *dev, uint16_t data) {
    __disable_irq();
    dev->data_port->ODR = data;
    __enable_irq();
}

/**
 * @brief  Read from data bus
 * @param  dev: Pointer to device structure
 * @retval Data read from bus
 */
static uint16_t read_data_bus(DEI1016_Device *dev) {
    __disable_irq();
    uint16_t data = (uint16_t)(dev->data_port->IDR & 0xFFFF);
    __enable_irq();
    return data;
}

/**
 * @brief  Initialize DEI1016 device
 * @param  config: Pointer to ARINC_Config structure
 * @retval ARINC_Status: Initialization status code
 */
static ARINC_Status Dei1016_init(const ARINC_Config *config) {
    if (config == NULL)
        return ARINC_ERR_PARAM_INVALID;
    if (config->channel >= MAX_CHANNELS)
        return ARINC_ERR_PARAM_INVALID;
    if (config->rate != BAUD_CONFIG_LOW && config->rate != BAUD_CONFIG_HIGH)
        return ARINC_ERR_PARAM_INVALID;
    if (!(config->parity == PARITY_NONE ||
          config->parity == PARITY_ODD ||
          config->parity == PARITY_EVEN)) {
        return ARINC_ERR_PARAM_INVALID;
    }

    uint8_t device_id = channel_to_device_id(config->channel);
    DEI1016_Device *dev = &dei_devices[device_id];
    DEI1016_ControlReg ctrl = {.value = 0};

    DEI_GPIO_WritePin(device_id, MR_PIN, GPIO_PIN_RESET);
    delay_us(5);
    DEI_GPIO_WritePin(device_id, MR_PIN, GPIO_PIN_SET);

    if ((config->channel & 1) == 0) {
        ctrl.bits.RCVSEL = (config->rate == BAUD_CONFIG_HIGH) ? 0 : 1;
        if ((config->channel & 3) == 0) {
            ctrl.bits.SDENB1 = (config->SDn != SD_CHECK_OFF) ? 1 : 0;
            if (config->SDn != SD_CHECK_OFF) {
                ctrl.bits.X1Y1 = config->SDn - 1;
            }
        } else {
            ctrl.bits.SDENB2 = (config->SDn != SD_CHECK_OFF) ? 1 : 0;
            if (config->SDn != SD_CHECK_OFF) {
                ctrl.bits.X2Y2 = config->SDn - 1;
            }
        }
    } else {
        ctrl.bits.PARCK = (config->parity == PARITY_EVEN) ? 1 : 0;
        ctrl.bits.PAREN = (config->parity != PARITY_NONE) ? 1 : 0;
        ctrl.bits.TXSEL = (config->rate == BAUD_CONFIG_HIGH) ? 0 : 1;
    }

    ctrl.bits.SLFTST = (dei_self_test[device_id] == 1) ? 0 : 1;
    ctrl.bits.WLSEL = 0;

    set_data_bus_direction(dev, 1);
    if (!dev->dma_active) {
        write_data_bus(dev, ctrl.value);
        DEI_GPIO_WritePin(device_id, dev->ldcw_pin, GPIO_PIN_RESET);
        delay_us(1);
        DEI_GPIO_WritePin(device_id, dev->ldcw_pin, GPIO_PIN_SET);
        set_data_bus_direction(dev, 0);
    } else {
        ArincCmd cmd = {0};
        cmd.config = *config;
        rt_mq_send(&init_mq, &cmd, sizeof(cmd));
    }
    return ARINC_OK;
}

/**
 * @brief  Deinitialize DEI1016 device
 * @param  channel: Channel number
 * @retval ARINC_Status: Deinitialization status code
 */
static ARINC_Status Dei1016_deinit(uint8_t channel) {
    if (channel >= MAX_CHANNELS)
        return ARINC_ERR_PARAM_INVALID;
    return ARINC_OK;
}

/**
 * @brief  Send ARINC 429 data
 * @param  channel: Transmit channel number
 * @param  data: Pointer to the data array to be sent (32-bit data)
 * @param  len: Data length (in bytes)
 * @retval ARINC_Status: Send status code
 */
static ARINC_Status Dei1016_send(uint8_t channel, const uint32_t *data, uint16_t len) {
    if (channel >= MAX_CHANNELS || !data || len == 0) {
        return ARINC_ERR_PARAM_INVALID;
        DEBUG_PRINTF("ARINC_ERR\n");
    }

    uint8_t device_id = channel_to_device_id(channel);
    DEI1016_Device *dev = &dei_devices[device_id];

    set_data_bus_direction(dev, 1);
    uint16_t word1 = 0;
    uint16_t word2 = 0;

    for (uint16_t i = 0; i < len; i++) {
        ArincMsg tx_msg;
        tx_msg.channel = channel;
        tx_msg.data = data[i];
        if (!dev->dma_active) {
            DEI_GPIO_WritePin(device_id, ENTXPIN, GPIO_PIN_RESET);

            arinc429_decode(data[i], &word1, &word2);

            write_data_bus(dev, word1);
            DEBUG_PRINTF("dev:%d,data:%04x\n", device_id, word1);
            DEI_GPIO_WritePin(device_id, dev->ld1_pin, GPIO_PIN_RESET);
            delay_us(1);
            DEI_GPIO_WritePin(device_id, dev->ld1_pin, GPIO_PIN_SET);

            write_data_bus(dev, word2);
            DEBUG_PRINTF("dev:%d,data:%04x\n", device_id, word2);
            DEI_GPIO_WritePin(device_id, dev->ld2_pin, GPIO_PIN_RESET);
            delay_us(1);
            DEI_GPIO_WritePin(device_id, dev->ld2_pin, GPIO_PIN_SET);

            DEI_GPIO_WritePin(device_id, ENTXPIN, GPIO_PIN_SET);
        } else {
            rt_mq_send(&tx_mq, &tx_msg, sizeof(tx_msg));
            DEBUG_PRINTF("dev:%d,tx_mq", device_id);
        }
    }
    DEBUG_PRINTF("send\n");
    return ARINC_OK;
}

/**
 * @brief  Receive ARINC 429 data
 * @param  channel: Receive channel number
 * @param  buffer: Pointer to the buffer to store received data
 * @param  len: Data length (in bytes)
 * @retval ARINC_Status: Receive status code
 */
static ARINC_Status Dei1016_receive(uint8_t channel, uint32_t *buffer, uint16_t len) {
    if (channel >= MAX_CHANNELS || !buffer || len == 0)
        return ARINC_ERR_PARAM_INVALID;

    uint8_t device_id = channel_to_device_id(channel);
    DEI1016_Device *dev = &dei_devices[device_id];

    set_data_bus_direction(dev, 0);

    for (uint16_t i = 0; i < len; i++) {
        DEI_GPIO_WritePin(device_id, dev->sel_pin, GPIO_PIN_RESET);
        DEI_GPIO_WritePin(device_id, dev->oe1_pin, GPIO_PIN_RESET);
        delay_us(1);
        buffer[i] = (uint32_t)read_data_bus(dev) << 16;
        DEI_GPIO_WritePin(device_id, dev->oe1_pin, GPIO_PIN_SET);

        DEI_GPIO_WritePin(device_id, dev->sel_pin, GPIO_PIN_SET);
        DEI_GPIO_WritePin(device_id, dev->oe1_pin, GPIO_PIN_RESET);
        delay_us(1);
        buffer[i] |= read_data_bus(dev);
        DEI_GPIO_WritePin(device_id, dev->oe1_pin, GPIO_PIN_SET);
    }

    return ARINC_OK;
}

/**
 * @brief  Driver operation structure for DEI1016
 */
static ARINC_DriverOps dei1016_driver_ops = {
    .init = Dei1016_init,
    .deinit = Dei1016_deinit,
    .send = Dei1016_send,
    .receive = Dei1016_receive
};

/**
 * @brief  Register DEI1016 driver to Middle layer
 * @retval ARINC_Status: Register status code
 */
ARINC_Status Dei1016_register(void) {
    arinc_adaptor_register_driver(ARINC_IF_DEI1016, &dei1016_driver_ops);
    return ARINC_OK;
}

#if USE_DEI1016
/**
 * @brief  Auto register DEI1016 driver at startup
 */
INIT_COMPONENT_EXPORT(Dei1016_register);
#endif

