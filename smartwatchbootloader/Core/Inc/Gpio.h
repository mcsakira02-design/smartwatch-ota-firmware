/******************************************************************************
 * Copyright (C) 2024 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file Flash.c
 * 
 * @par dependencies 
 * - Flash.h
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
#ifndef __GPIO_H
#define __GPIO_H

#define LED_C13_PORT GPIOC
#define LED_C13_PIN  GPIO_Pin_13
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "main.h"
//#include "Systim.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define LED_OFF    GPIO_SetBits(LED_C13_PORT,LED_C13_PIN);
#define LED_ON     GPIO_ResetBits(LED_C13_PORT,LED_C13_PIN);
/* Exported functions ------------------------------------------------------- */

extern void Key_IO_Init(void);
extern uint8_t Key_Scan(void);
extern void Led_IO_Init(void);
extern void Breathing_light(void);
#endif /* __GPIO_H */
