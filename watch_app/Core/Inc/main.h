/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TP_TINT_Pin GPIO_PIN_2
#define TP_TINT_GPIO_Port GPIOB
#define TP_TINT_EXTI_IRQn EXTI2_IRQn
#define SPI_RESET_Pin GPIO_PIN_10
#define SPI_RESET_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_12
#define LCD_CS_GPIO_Port GPIOB
#define LCD_SCK_Pin GPIO_PIN_13
#define LCD_SCK_GPIO_Port GPIOB
#define LCD_DC_Pin GPIO_PIN_14
#define LCD_DC_GPIO_Port GPIOB
#define LCD_MOSI_Pin GPIO_PIN_15
#define LCD_MOSI_GPIO_Port GPIOB
#define TP_SCL_Pin GPIO_PIN_8
#define TP_SCL_GPIO_Port GPIOA
#define TP_RST_Pin GPIO_PIN_15
#define TP_RST_GPIO_Port GPIOA
#define SPI_CS_Pin GPIO_PIN_3
#define SPI_CS_GPIO_Port GPIOB
#define TP_SDA_Pin GPIO_PIN_4
#define TP_SDA_GPIO_Port GPIOB
#define Mpu6050_Int_Pin GPIO_PIN_5
#define Mpu6050_Int_GPIO_Port GPIOB
#define Mpu6050_Int_EXTI_IRQn EXTI9_5_IRQn
#define Sensor_SCL_Pin GPIO_PIN_6
#define Sensor_SCL_GPIO_Port GPIOB
#define Sensor_SDA_Pin GPIO_PIN_7                                           
#define Sensor_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
