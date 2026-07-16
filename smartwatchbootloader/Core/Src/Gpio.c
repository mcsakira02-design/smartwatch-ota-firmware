/******************************************************************************
 * Copyright (C) 2024 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file Gpio.c
 * 
 * @par dependencies 
 * - Gpio.h
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
/* Includes ------------------------------------------------------------------*/
#include "Gpio.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* extern variables ---------------------------------------------------------*/

void Key_IO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable the GPIOA peripheral */ 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t Key_Scan(void)
{
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_RESET)
    {
      Delay(50);
      if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_RESET)
      {
        return 1;
      }
    }
    return 0;
}

void Led_IO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable the GPIOC peripheral */ 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = LED_C13_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LED_C13_PORT, &GPIO_InitStructure);
}

void Breathing_light(void)
{
		/* C13 呼吸灯测试 */
		static uint8_t pwmset;
		static uint16_t time;
		static uint8_t timeflag;
		static uint8_t timecount;

		 /* 呼吸灯 */
		if(timeflag == 0)
		{
			time ++;
			if(time >= 1600) timeflag = 1;
		}
		else
		{
			time --;
			if(time == 0) timeflag = 0;
		}

		/* 占空比设置 */
		pwmset = time/80;

		/* 20ms 脉宽 */
		if(timecount > 20) timecount = 0;
		else timecount ++;

		if(timecount >= pwmset ) GPIO_SetBits(LED_C13_PORT,LED_C13_PIN);
		else GPIO_ResetBits(LED_C13_PORT,LED_C13_PIN);
		
		Delay(1);
}
