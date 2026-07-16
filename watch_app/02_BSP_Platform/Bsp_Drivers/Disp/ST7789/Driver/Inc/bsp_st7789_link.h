#ifndef __ST7789_LINK
#define __ST7789_LINK

#include "main.h"
#include "stm32f411xe.h"

#include "bsp_st7789_driver.h"
#include "gpio_port.h"

#include "FreeRTOS.h"
#include "task.h"
#include "spi_port.h"
extern SPI_HandleTypeDef hspi2;
extern DMA_HandleTypeDef hdma_spi2_tx;

static inline uint8_t spi_transmit_data( uint8_t *pData, uint32_t dataLength)
{
	SENSOR_SPI2_HARDWARE_TRANSMIT(pData, dataLength, 0xFF);
	// HAL_SPI_Transmit(&hspi2, pData, dataLength, 0xFF);	
	return 0;
}

static inline uint8_t spi_transmit_data_dma( uint8_t *pData, \
											 uint32_t dataLength)
{
	SENSOR_SPI2_HARDWARE_TRANSMIT_DMA(pData,dataLength);
	//HAL_SPI_Transmit_DMA(&hspi2, pData, dataLength);
	while (hspi2.hdmatx->State != HAL_DMA_STATE_READY);
	
	return 0;
}

//    uint8_t (*pf_write_reset_pin)(uint8_t pinState);
//    uint8_t (*pf_write_cs_pin)(uint8_t pinState); 
//    uint8_t (*pf_write_dc_pin)(uint8_t pinState); 
static inline uint8_t gpio_write_reset_pin(uint8_t pinState)
{
	en_core_gpio_pin_state_t state = (pinState == 0) ? CORE_GPIO_PIN_RESET : CORE_GPIO_PIN_SET;
	core_gpio_write_pin(CORE_GPIO_LCD_RESET, state);
	return pinState;
}

static inline uint8_t gpio_write_cs_pin(uint8_t pinState)
{
	SENSOR_SPI2_HARDWARE_WRITE_CS(pinState);
	return pinState;
}

static inline uint8_t gpio_write_dc_pin(uint8_t pinState)
{
	en_core_gpio_pin_state_t state = (pinState == 0) ? CORE_GPIO_PIN_RESET : CORE_GPIO_PIN_SET;
	core_gpio_write_pin(CORE_GPIO_LCD_DC, state);
	return pinState;
}


/*****************************************************************************/






#endif /* __ST7789_LINK */
