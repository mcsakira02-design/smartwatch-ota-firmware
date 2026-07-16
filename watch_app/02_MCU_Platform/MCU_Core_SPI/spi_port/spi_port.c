/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file drv_adapter_port_temphumioment.c
 * 
 * @par dependencies 
 * - i2c_port.h
 * - i2c.h
 * - iic_hal.h
 * - os_freertos
 * - osal_mutex
 * @author ssj
 * 
 * @brief Provide the HAL APIs of AHT21 and corresponding opetions.
 * 
 * Processing flow:
 * 
 * 2.Then the users could all the IOs from instances of bsp_aht21_driver_t.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
//******************************** Includes *********************************//
#include "spi_port.h"
#include "main.h"
#include "spi.h"   // hardware i2c
#include "os_freertos.h"
#include "osal_mutex.h"
#include "cmsis_os2.h"
#include "gpio_port.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//
// 结构体重定义
static st_spi_port_t st_spi_port[CORE_SPI_BUS_MAX] = {
    [CORE_SPI_BUS_1] = {
        .st_SPI_HandleTypeDef = &hspi1,
        .cs_port = SPI_CS_GPIO_Port,
        .cs_pin = SPI_CS_Pin
    },
    [CORE_SPI_BUS_2] = {
        .st_SPI_HandleTypeDef = &hspi2,
        .cs_port = LCD_CS_GPIO_Port,
        .cs_pin = LCD_CS_Pin
    }
};

// SPI基础传输函数
en_core_spi_status_t core_spi_transmit(en_core_spi_bus_t bus, uint8_t *data, uint16_t size, uint32_t timeout) {
    HAL_StatusTypeDef ret = HAL_SPI_Transmit(st_spi_port[bus].st_SPI_HandleTypeDef, data, size, timeout);
    return (ret == HAL_OK) ? CORE_SPI_OK : CORE_SPI_ERROR;
}

// SPI基础传输函数
en_core_spi_status_t core_spi_receive(en_core_spi_bus_t bus, uint8_t *data, uint16_t size, uint32_t timeout) {
    HAL_StatusTypeDef ret = HAL_SPI_Receive(st_spi_port[bus].st_SPI_HandleTypeDef, data, size, timeout);
    return (ret == HAL_OK) ? CORE_SPI_OK : CORE_SPI_ERROR;
}
// SPI基础传输函数
en_core_spi_status_t core_spi_transmit_dma(en_core_spi_bus_t bus, uint8_t *data, uint16_t size) {
    HAL_StatusTypeDef ret = HAL_SPI_Transmit_DMA(st_spi_port[bus].st_SPI_HandleTypeDef, data, size);
    return (ret == HAL_OK) ? CORE_SPI_OK : CORE_SPI_ERROR;
}

// SPI基础传输函数
en_core_spi_status_t core_spi_write_cs(en_core_spi_bus_t bus, uint8_t pinState) {
	en_core_spi_status_t ret = CORE_SPI_OK;
	en_core_gpio_pin_t cs_pin = (bus == CORE_SPI_BUS_1) ? CORE_GPIO_SPI_CS : CORE_GPIO_LCD_CS;
	en_core_gpio_pin_state_t state = (pinState == 0) ? CORE_GPIO_PIN_RESET : CORE_GPIO_PIN_SET;
	core_gpio_write_pin(cs_pin, state);
    return (ret == HAL_OK) ? CORE_SPI_OK : CORE_SPI_ERROR;
}

// SPI片选控制的传输
en_core_spi_status_t core_spi_write_with_cs(en_core_spi_bus_t bus, uint8_t *data, uint16_t size) {
    en_core_gpio_pin_t cs_pin = (bus == CORE_SPI_BUS_1) ? CORE_GPIO_SPI_CS : CORE_GPIO_LCD_CS;
    core_gpio_write_pin(cs_pin, CORE_GPIO_PIN_RESET);
    HAL_StatusTypeDef ret = HAL_SPI_Transmit(st_spi_port[bus].st_SPI_HandleTypeDef, data, size, 100);
    core_gpio_write_pin(cs_pin, CORE_GPIO_PIN_SET);
    return (ret == HAL_OK) ? CORE_SPI_OK : CORE_SPI_ERROR;
}



