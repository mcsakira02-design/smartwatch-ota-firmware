/******************************************************************************
 * Copyright (C) 2024 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file Flash.h
 * 
 * @par dependencies 
 * - Flash.h
 * 
 * @author Jack | R&D Dept. | EternalChip
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
#ifndef __FLASH_H
#define __FLASH_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* FLASH sector start addresses */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000U)   /* Sector 0 start address, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000U)   /* Sector 1 start address, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000U)   /* Sector 2 start address, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000U)   /* Sector 3 start address, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000U)   /* Sector 4 start address, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000U)   /* Sector 5 start address, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000U)   /* Sector 6 start address, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000U)   /* Sector 7 start address, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000U)   /* Sector 8 start address, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000U)   /* Sector 9 start address, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000U)   /* Sector 10 start address, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000U)   /* Sector 11 start address, 128 Kbytes */

/* Exported functions ------------------------------------------------------- */
uint8_t Flash_erase(uint32_t addr, uint32_t size);
FLASH_Status EreaseAppSector(uint32_t FLASH_Sector);
void Flash_Unlock(void);
void Flash_Lock(void);
void Flash_Write(uint32_t address, uint32_t data);

#endif /* __FLASH_H */
