/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file Debug.h
 * 
 * @par dependencies 
 * - Debug.h
 * 
 * @author ssj
 * 
 * @brief Provide all the debugging tools in this project.
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
#ifndef __DEBUG_H__  //Avoid repeated including same files later
#define __DEBUG_H__

//******************************** Includes *********************************//
#include "elog.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//
#define DEBUG
#define OS_SUPPORTING


//所有trace输出均要经过当前模块控制输出
#ifdef DEBUG
/*trace输出Api*/
#define DEBUG_OUT(format, ...)      log_i(format, ##__VA_ARGS__)      //printf(...)

#define DEBUG_User_Init

#define DEBUG_SENSOR_AHT21_DRIVER         
#define DEBUG_SENSOR_AHT21_HANDLER        
#define DEBUG_SENSOR_ADAPTER_TEMPHUMI     
#define DEBUG_SENSOR_ADAPTER_PORT_TEMPHUMI
#define DEBUG_SENSOR_MPU6050_DRIVER             
#define DEBUG_SENSOR_MPU6050_HANDLER
#define DEBUG_SENSOR_ADAPTER_MOTION
#define DEBUG_SENSOR_ADAPTER_PORT_MOTION
#define DEBUG_USER_SENSOR

#define DEBUG_FLASH_W25Q64_DRIVER
#define DEBUG_FLASH_W25Q64_HANDLER
#define DEBUG_FLASH_ADAPTER
#define DEBUG_FLASH_ADAPTER_PORT
#define DEBUG_USER_FLASH

#define DEBUG_ST7789_DRIVER
#define DEBUG_ST7789_ADAPTER
#define DEBUG_ST7789_ADAPTER_PORT
#define DEBUG_LVGL
#define DEBUG_LCDCALIBRATE
#define DEBUG_CST816_DRIVER
#define DEBUG_CST816_ADAPTER
#define DEBUG_CST816_ADAPTER_PORT

#define DEBUG_SENSOR_EM7028_DRIVER

#define DEBUG_SENSOR_SPL06_DRIVER
#endif
//******************************** Defines **********************************//

//******************************** Declaring ********************************//
void Debug_Init(void);                                                       
//******************************** Declaring ********************************//

#endif /* __EC_BSP_AHT21_DRIVER_H__ */
