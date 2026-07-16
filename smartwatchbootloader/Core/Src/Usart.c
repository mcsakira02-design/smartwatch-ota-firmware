/******************************************************************************
 * Copyright (C) 2024 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file USART.c
 * 
 * @par dependencies 
 * - USART.h
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
#include "USART.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* extern variables ---------------------------------------------------------*/

/**
  * @brief  RCC配置初始化 USART1 USART2
  * @param  Null
  * @retval None
  */
static void RCC_Configuration(void) {
    // 启用GPIOA时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    // 启用USART1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}
/**
  * @brief  串口GPIO配置初始化 USART1 USART2
  *         GPIO使用Pin_Speed_50MHz，Pull_Up_Pull_Down_None
  * @param  Null
  * @retval None
  */
static void GPIO_Configuration(void) 
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 配置PA9为USART1_TX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置PA10为USART1_RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 连接PA9和PA10到USART1的复用功能
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
}

/**
  * @brief  串口外设相关配置 USART1 USART2
  *         BaudRate = 115200, 8N1 模式
  * @param  Null
  * @retval None
  */
static void USART_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;

    // 配置USART1
    // USART_InitStructure.USART_BaudRate = 9600;
	  USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);

    // // 配置USART2
    // USART_InitStructure.USART_BaudRate = 115200;
    // USART_Init(USART2, &USART_InitStructure);
    // USART_Cmd(USART2, ENABLE);
}

/**
  * @brief  串口发送字节函数，使用USART2或USART1，使用阻塞方式
  * @param  USARTx USART2, USART1
  * @param  data 数据字节
  * @retval None
  */
void USART_SendChar(USART_TypeDef* USARTx, uint8_t data) {
    // 等待发送数据寄存器空
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    // 发送一个字节数据到USART
    USART_SendData(USARTx, data);
}
/**
  * @brief  串口接收字节函数，使用USART2或USART1，使用阻塞方式
  * @param  USARTx USART2, USART1
  * @retval 返回数据
  */
uint8_t USART_ReceiveChar(USART_TypeDef* USARTx) {
    // 等待接收数据寄存器满
    while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
    // 读取接收到的数据
    return USART_ReceiveData(USARTx);
}

void USART1_Init(void)
{
  RCC_Configuration();
	GPIO_Configuration();
	USART_Configuration();
}


