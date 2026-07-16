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
/* Includes ------------------------------------------------------------------*/
#include "Flash.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define FLASH_SECTOR_COUNT    (12U)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Flash sector size lookup table */
static const uint32_t s_flash_sector_size[FLASH_SECTOR_COUNT] = 
{
    FLASH_Sector_0,   /* Sector 0 */
    FLASH_Sector_1,   /* Sector 1 */
    FLASH_Sector_2,   /* Sector 2 */
    FLASH_Sector_3,   /* Sector 3 */
    FLASH_Sector_4,   /* Sector 4 */
    FLASH_Sector_5,   /* Sector 5 */
    FLASH_Sector_6,   /* Sector 6 */
    FLASH_Sector_7,   /* Sector 7 */
    FLASH_Sector_8,   /* Sector 8 */
    FLASH_Sector_9,   /* Sector 9 */
    FLASH_Sector_10,  /* Sector 10 */
    FLASH_Sector_11   /* Sector 11 */
};

/* Private function prototypes -----------------------------------------------*/
static uint16_t STMFLASH_GetFlashSector(uint32_t addr);

/* Private functions ---------------------------------------------------------*/
/* extern variables ---------------------------------------------------------*/

/**
 * @brief Erase flash area
 * @param addr Start address to erase
 * @param size Size of area to erase
 * @retval uint8_t 0: Success, 1: Fail
 */
uint8_t Flash_erase(uint32_t addr, uint32_t size)
{
    uint32_t flash_start_sector = 0U;
    uint32_t flash_end_sector = 0U;
    
    /* Parameter validation */
    if (size == 0U)
    {
        return 1U;
    }
    
    /* Get start and end sectors */
    flash_start_sector = STMFLASH_GetFlashSector(addr);
    flash_end_sector = STMFLASH_GetFlashSector(addr + size);

    /* Erase all sectors in the range */
    for (uint8_t i = 0U; i < FLASH_SECTOR_COUNT; i++)
    {
        if ((s_flash_sector_size[i] >= flash_start_sector) && 
            (s_flash_sector_size[i] <= flash_end_sector))
        {
            if (EreaseAppSector(s_flash_sector_size[i]) != FLASH_COMPLETE)
            {
                return 1U;
            }
        }
    }
    return 0U;
}

/**
 * @brief Get flash sector by address
 * @param addr Flash address
 * @return uint16_t Flash sector number
 */
static uint16_t STMFLASH_GetFlashSector(uint32_t addr)
{
    uint16_t sector = FLASH_Sector_11;
    
    if (addr < ADDR_FLASH_SECTOR_1)
    {
        sector = FLASH_Sector_0;
    }
    else if (addr < ADDR_FLASH_SECTOR_2)
    {
        sector = FLASH_Sector_1;
    }
    else if (addr < ADDR_FLASH_SECTOR_3)
    {
        sector = FLASH_Sector_2;
    }
    else if (addr < ADDR_FLASH_SECTOR_4)
    {
        sector = FLASH_Sector_3;
    }
    else if (addr < ADDR_FLASH_SECTOR_5)
    {
        sector = FLASH_Sector_4;
    }
    else if (addr < ADDR_FLASH_SECTOR_6)
    {
        sector = FLASH_Sector_5;
    }
    else if (addr < ADDR_FLASH_SECTOR_7)
    {
        sector = FLASH_Sector_6;
    }
    else if (addr < ADDR_FLASH_SECTOR_8)
    {
        sector = FLASH_Sector_7;
    }
    else if (addr < ADDR_FLASH_SECTOR_9)
    {
        sector = FLASH_Sector_8;
    }
    else if (addr < ADDR_FLASH_SECTOR_10)
    {
        sector = FLASH_Sector_9;
    }
    else if (addr < ADDR_FLASH_SECTOR_11)
    {
        sector = FLASH_Sector_10;
    }
    else
    {
        sector = FLASH_Sector_11;
    }
    
    return sector;
}

/**
 * @brief Unlock flash for write/erase operations
 * @param None
 * @return None
 */
void Flash_Unlock(void)
{
    FLASH_Unlock();
    while (FLASH_GetStatus() == FLASH_BUSY)
    {
        /* Wait for flash ready */
    }
}

/**
 * @brief Lock flash after write/erase operations
 * @param None
 * @return None
 */
void Flash_Lock(void)
{
    FLASH_Lock();
}

/**
 * @brief Erase application sector
 * @param FLASH_Sector Flash sector to erase
 * @return FLASH_Status Erase operation status
 * @note F4 operates by sector, app is planned to be in sector 6
 */
FLASH_Status EreaseAppSector(uint32_t FLASH_Sector)
{
    FLASH_Status flash_status;
    
    Flash_Unlock();
    flash_status = FLASH_EraseSector(FLASH_Sector, VoltageRange_3);
    Flash_Lock();
    
    return flash_status;
}

/**
 * @brief Write data to flash
 * @param address Flash address to write
 * @param data Data to write (32-bit word)
 * @return None
 */
void Flash_Write(uint32_t address, uint32_t data)
{
    FLASH_Status status;
    
    /* Unlock Flash */
    Flash_Unlock();
    
    /* Program one word (32 bits) */
    status = FLASH_ProgramWord(address, data);
    
    /* Check if programming was successful */
    if (status == FLASH_COMPLETE)
    {
        /* Data write successful */
        /* log_d("Flash_Write success"); */
    }
    else
    {
        /* Data write failed */
        /* Add error handling code here */
        /* log_e("Flash_Write fail"); */
    }
    
    /* Lock Flash */
    Flash_Lock();
}
