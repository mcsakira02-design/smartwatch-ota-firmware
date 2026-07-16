/******************************************************************************
 * Copyright (C) 2024 ssj
 * 
 * All Rights Reserved.
 * 
 * @file ec_bsp_w25q64_reg.h
 * 
 * 
 * @author ssj
 * 
 * @brief Provide the reg command of w25q64.
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
#ifndef __BSP_W25Q64_REG_H__
#define __BSP_W25Q64_REG_H__
/***********************************Defines **********************************/
/*---------------------W25Q64 REG COMMAND-----------------------*/
#define       W25Q64_CMD_READ_ID               (0x90U)
#define       W25Q64_CMD_READ_DATA             (0x03U)
#define       W25Q64_CMD_READ_REG              (0x05U)
#define       W25Q64_CMD_ERASE_SECTOR          (0x20U)
#define       W25Q64_CMD_CHIP_SECTOR           (0x07U)
#define       W25Q64_CMD_WRITEON_REG           (0x06U)
#define       W25Q64_CMD_WRITEOFF_REG          (0x04U)
#define       W25Q64_CMD_WRITE_DATA            (0x02U)
#define       W25Q64_CMD_SLEEP                 (0xB9U)
#define       W25Q64_CMD_WAKEUP                (0xABU)

/*--------------------W25Q64 PARAMETER Config-------------------*/
#define       W25Q64_SECTOR_SIZE               (4096U)
#define       W25Q64_PAGE_SIZE                  (256U)
#define       W25Q64_MAX_SIZE            (0x00800000U)
/***********************************Defines **********************************/

#endif
