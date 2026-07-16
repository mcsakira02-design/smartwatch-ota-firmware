/******************************************************************************
 * Copyright (C) 2024 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file w25qxx_Handler.h
 * 
 * @par dependencies 
 * - w25qxx_Handler.h
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
#ifndef __W25Q_HANDLER_H
#define __W25Q_HANDLER_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
/**
 * @brief W25Q Handler structure
 * @note Minimum read/write unit Page = 256 bytes
 *       One sector = 16 Pages = 4096 bytes
 *       One block = 16 sectors = 64KB
 */
typedef struct 
{
    uint8_t  databuf[4096];           /* 4096 bytes data buffer for read/write */
    uint16_t write_databuf_index;     /* Write buffer index */
    uint32_t write_index;             /* Total write index */
    uint8_t  write_sector_index;      /* Write sector index (4096 bytes) */
    uint32_t read_index;              /* Total read index */
    uint8_t  read_sector_index;       /* Read sector index */
} st_W25Q_Handler;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define EXTERN_FlashAstartAddr 0x00000000
#define EXTERN_FlashBstartAddr 0x00080000
#define BLOCKA 0
#define BLOCKB 1
#define BLOCK_SIZE      4096    //此处为软件内部的扇区大小
/* Exported functions ------------------------------------------------------- */
void SetBlockParmeter(u8 block_index,uint32_t app_size);
void W25Q64_Init(void);
uint8_t W25Q64_EraseChip(void);
uint8_t W25Q64_WriteData(uint8_t block_index, uint8_t *data, uint32_t length);
uint8_t W25Q64_WriteData_End(uint8_t block_index);
uint8_t W25Q64_ReadData(uint8_t block_index, uint8_t *data, uint16_t *length);

#endif /* __W25Q_HANDLER_H */
