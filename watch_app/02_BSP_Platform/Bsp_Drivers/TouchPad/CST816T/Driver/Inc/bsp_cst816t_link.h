/******************************************************************************
 * Copyright (C) 2025 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file bsp_cst816t_link.h
 * 
 * @par dependencies 
 * 
 * bsp_cst816t_driver.h
 * 
 * @author 
 * 
 * @brief Provide the CST816T driver interface.
 * 
 * Processing flow:
 * 
 * call directly.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
#ifndef __BSP_CST816T_LINK_H
#define __BSP_CST816T_LINK_H

#include "main.h"
#include "bsp_cst816t_driver.h"

#include "FreeRTOS.h"
#include "task.h"
#include "i2c_port.h"
#include "gpio_port.h"

extern I2C_HandleTypeDef hi2c3;

// iic driver interface
static inline uint8_t iic_driver_init(void * iic_bus)
{
    // has already inited in main.c
    return 0;
}
static inline uint8_t iic_driver_deinit(void *iic_bus)
{
    __HAL_RCC_I2C2_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10);
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3);
    return 0;
}
static inline uint8_t iic_mem_read(void *hi2c, 
                              uint16_t dst_address, 
                              uint16_t mem_addr, 
                              uint16_t mem_size, 
                              uint8_t  *p_data, 
                              uint16_t size, 
                              uint32_t timeout)
{
    HAL_StatusTypeDef ret = HAL_OK;
	// ret = HAL_I2C_Mem_Read(hi2c, dst_address, mem_addr, mem_size, p_data, size, timeout);
    ret = TOUCHPAD_I2C_HARDWARE_MEM_READ(dst_address, mem_addr, mem_size, p_data, size, timeout);
    if (ret != HAL_OK)
    {
        return 1;
    }
    return 0;
}
static inline uint8_t iic_mem_write(void *hi2c,
                               uint16_t dst_address, 
                               uint16_t mem_addr, 
                               uint16_t mem_size, 
                               uint8_t  *p_data, 
                               uint16_t size, 
                               uint32_t timeout)
{
    HAL_StatusTypeDef ret = HAL_OK;
	// ret = HAL_I2C_Mem_Write(hi2c, dst_address, mem_addr, mem_size, p_data, size, timeout);
    ret = TOUCHPAD_I2C_HARDWARE_MEM_WRITE(dst_address, mem_addr, mem_size, p_data, size, timeout);
    if (ret != HAL_OK)
    {
        return 1;
    }
    return 0;
}
static inline uint8_t iic_mem_read_dma(void *hi2c, 
                                 uint16_t dst_address, 
                                 uint16_t mem_addr, 
                                 uint16_t mem_size, 
                                 uint8_t  *p_data, 
                                 uint16_t size )
{
    HAL_StatusTypeDef ret = HAL_OK;
    //ret = HAL_I2C_Mem_Read_DMA(hi2c, dst_address, mem_addr, mem_size, p_data, size);
    ret = TOUCHPAD_I2C_HARDWARE_MEM_READ_DMA(dst_address, mem_addr, mem_size, p_data, size);
    if (ret != HAL_OK)
    {
        return 1;
    }
    return 0;
}

static inline uint8_t gpio_opt_write_reset_pin(uint8_t state)
{
    en_core_gpio_pin_state_t gpio_state = (state == 0) ? CORE_GPIO_PIN_RESET : CORE_GPIO_PIN_SET;
    core_gpio_write_pin(CORE_GPIO_TP_RST, gpio_state);
    return 0;
}

#endif /* __BSP_CST816T_LINK_H */
