/******************************************************************************
 * Copyright (C) 2024 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file Spi.h
 * 
 * @par dependencies 
 * - Spi.h
 * 
 * @author Jack | R&D Dept. | EternalChip 立芯嵌入式
 * 
 * @brief Functions related to reading and writing in the chip's flash area.
 * 
 * Processing flow:
 * 
 * call directly.
 * 
 * @version V1.0 2024-09-13
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H
#define __SPI_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define F_CS_Pin GPIO_Pin_3
#define F_CS_GPIO_Port GPIOB
/* Exported functions ------------------------------------------------------- */

void SPI1_Init(void);
u8 SPI1_WriteByte(u8 *WriteData, u16 dataSize, u32 timeout);
u8 SPI1_ReadByte(u8 *ReadData, u16 dataSize, u32 timeout);
#endif /* __FLASH_H */
