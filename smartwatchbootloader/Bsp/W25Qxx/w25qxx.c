/**
 * @file w25qxx.c
 * @brief W25QXX external flash driver implementation
 * @author Jack | R&D Dept. | EternalChip
 * @version V1.0 2024-09-13
 */

#include "w25qxx.h"
#include <stddef.h>
#include <math.h>

/* External variables */
extern volatile uint32_t SysTickUptime;

/* Private macros */
#define DELAY_MS(ms) Delay(ms)
#define GET_TICK() SysTickUptime

/* Static variables */
static W25Qx_Parameter s_w25qx_para;

/* Private function prototypes */
static void W25Qx_Reset(void);
static uint8_t W25Qx_GetStatus(void);
/**
 * @brief Initialize the W25QXXXX interface
 * @retval uint8_t Status of initialization (W25Qx_OK or W25Qx_ERROR)
 */
uint8_t W25Qx_Init(void)
{
    uint8_t state;
    
    /* Reset W25Qxxx */
    W25Qx_Reset();
    
    /* Get W25QXX parameters */
    state = W25Qx_Get_Parameter(&s_w25qx_para);
    
    return state;
}

/**
 * @brief Reset the W25Qx device
 * @retval None
 */
static void W25Qx_Reset(void)
{
    uint8_t cmd[2] = {RESET_ENABLE_CMD, RESET_MEMORY_CMD};
    
    W25Qx_Enable();
    /* Send the reset command */
    (void)SPI1_WriteByte(cmd, 2U, W25QXXXX_TIMEOUT_VALUE);
    W25Qx_Disable();
}

/**
 * @brief Read current status of the W25QXXXX
 * @retval uint8_t W25QXXXX memory status (W25Qx_OK or W25Qx_BUSY)
 */
static uint8_t W25Qx_GetStatus(void)
{
    uint8_t cmd[] = {READ_STATUS_REG1_CMD};
    uint8_t status;
    
    W25Qx_Enable();
    
    /* Send the read status command */
    (void)SPI1_WriteByte(cmd, 1U, W25QXXXX_TIMEOUT_VALUE);
    /* Reception of the data */
    (void)SPI1_ReadByte(&status, 1U, W25QXXXX_TIMEOUT_VALUE);
    W25Qx_Disable();
    
    /* Check the value of the register */
    if ((status & W25QXXXX_FSR_BUSY) != 0U)
    {
        return W25Qx_BUSY;
    }
    else
    {
        return W25Qx_OK;
    }
}

/**
 * @brief Send a Write Enable command and wait for it to be effective
 * @retval uint8_t Status (W25Qx_OK or W25Qx_TIMEOUT)
 */
uint8_t W25Qx_WriteEnable(void)
{
    uint8_t cmd[] = {WRITE_ENABLE_CMD};
    uint32_t tickstart = GET_TICK();

    /* Select the FLASH: Chip Select low */
    W25Qx_Enable();
    /* Send the write enable command */
    (void)SPI1_WriteByte(cmd, 1U, W25QXXXX_TIMEOUT_VALUE);
    /* Deselect the FLASH: Chip Select high */
    W25Qx_Disable();
    
    /* Wait the end of Flash writing */
    while (W25Qx_GetStatus() == W25Qx_BUSY)
    {
        /* Check for the Timeout */
        if ((GET_TICK() - tickstart) > W25QXXXX_TIMEOUT_VALUE)
        {
            return W25Qx_TIMEOUT;
        }
        DELAY_MS(1U);
    }
    
    return W25Qx_OK;
}

/**
 * @brief Read Manufacture/Device ID
 * @param ID Pointer to store the device ID
 * @note Return value description:
 *       0xEF13: W25Q80
 *       0xEF14: W25Q16
 *       0xEF15: W25Q32
 *       0xEF16: W25Q64
 * @retval None
 */
void W25Qx_Read_ID(uint16_t *ID)
{
    uint8_t id_data[2];
    uint8_t cmd[4] = {READ_ID_CMD, 0x00U, 0x00U, 0x00U};
    
    if (ID == NULL)
    {
        return;
    }
    
    W25Qx_Enable();
    /* Send the read ID command */
    (void)SPI1_WriteByte(cmd, 4U, W25QXXXX_TIMEOUT_VALUE);
    /* Reception of the data */
    (void)SPI1_ReadByte(id_data, 2U, W25QXXXX_TIMEOUT_VALUE);
    
    *ID = ((uint16_t)id_data[0] << 8U) + (uint16_t)id_data[1];
    
    W25Qx_Disable();
}

/**
 * @brief Get W25QX parameters
 * @param Para Pointer to W25Qx_Parameter structure
 * @retval uint8_t Status (W25Qx_OK or W25Qx_ERROR)
 */
uint8_t W25Qx_Get_Parameter(W25Qx_Parameter *Para)
{
    uint16_t id;
    uint32_t size;
    
    if (Para == NULL)
    {
        return W25Qx_ERROR;
    }
    
    Para->PAGE_TOTAL_SIZE = 256U;
    Para->SUBSECTOR_SIZE = 4096U;
    Para->SECTOR_SIZE = 0x10000U;
    
    W25Qx_Read_ID(&id);
    if ((id < W25Q80) || (id > W25Q128))
    {
        return W25Qx_ERROR;
    }
    
    //size = (uint32_t)powf(2.0f, (float)(id - 0xEF13U)) * 1024U * 1024U;
    // 原代码：powf(2.0f, (float)(id - 0xEF13U))
    // 可替换为：(1U << (id - 0xEF13U))
    size = (1U << (id - 0xEF13U)) * 1024U * 1024U;
    Para->FLASH_ID = id;
    Para->FLASH_TOTAL_SIZE = size;
    Para->SUBSECTOR_COUNT = Para->FLASH_TOTAL_SIZE / Para->SUBSECTOR_SIZE;
    Para->SECTOR_COUNT = Para->FLASH_TOTAL_SIZE / Para->SECTOR_SIZE;
    
    return W25Qx_OK;
}
/**
 * @brief Read an amount of data from the W25QXX memory
 * @param pData Pointer to data buffer to store read data
 * @param ReadAddr Read start address
 * @param Size Size of data to read
 * @retval uint8_t Memory status (W25Qx_OK or W25Qx_ERROR)
 */
uint8_t W25Qx_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size)
{
    uint8_t cmd[4];

    if ((pData == NULL) || (Size == 0U))
    {
        return W25Qx_ERROR;
    }

    /* Configure the command */
    cmd[0] = READ_CMD;
    cmd[1] = (uint8_t)(ReadAddr >> 16U);
    cmd[2] = (uint8_t)(ReadAddr >> 8U);
    cmd[3] = (uint8_t)(ReadAddr);
    
    W25Qx_Enable();
    /* Send the read command */
    (void)SPI1_WriteByte(cmd, 4U, W25QXXXX_TIMEOUT_VALUE);
    /* Reception of the data */
    if (SPI1_ReadByte(pData, Size, W25QXXXX_TIMEOUT_VALUE) != 1U)
    {
        W25Qx_Disable();
        return W25Qx_ERROR;
    }
    W25Qx_Disable();
    
    return W25Qx_OK;
}

/**
 * @brief Write an amount of data to the W25QXX memory
 * @param pData Pointer to data to be written
 * @param WriteAddr Write start address
 * @param Size Size of data to write
 * @retval uint8_t Memory status (W25Qx_OK, W25Qx_ERROR, or W25Qx_TIMEOUT)
 */
uint8_t W25Qx_Write(uint8_t* pData, uint32_t WriteAddr, uint32_t Size)
{
    uint8_t cmd[4];
    uint32_t end_addr, current_size, current_addr;
    uint32_t tickstart = GET_TICK();
    
    if ((pData == NULL) || (Size == 0U))
    {
        return W25Qx_ERROR;
    }
    
    /* Calculation of the size between the write address and the end of the page */
    current_addr = 0U;

    while (current_addr <= WriteAddr)
    {
        current_addr += W25QXXXX_PAGE_SIZE;
    }
    current_size = current_addr - WriteAddr;

    /* Check if the size of the data is less than the remaining place in the page */
    if (current_size > Size)
    {
        current_size = Size;
    }

    /* Initialize the address variables */
    current_addr = WriteAddr;
    end_addr = WriteAddr + Size;
    
    /* Perform the write page by page */
    do
    {
        /* Configure the command */
        cmd[0] = PAGE_PROG_CMD;
        cmd[1] = (uint8_t)(current_addr >> 16U);
        cmd[2] = (uint8_t)(current_addr >> 8U);
        cmd[3] = (uint8_t)(current_addr);

        /* Enable write operations */
        if (W25Qx_WriteEnable() != W25Qx_OK)
        {
            return W25Qx_ERROR;
        }
        
        W25Qx_Enable();
        /* Send the command */
        if (SPI1_WriteByte(cmd, 4U, W25QXXXX_TIMEOUT_VALUE) != 1U)
        {
            W25Qx_Disable();
            return W25Qx_ERROR;
        }
        
        /* Transmission of the data */
        if (SPI1_WriteByte(pData, current_size, W25QXXXX_TIMEOUT_VALUE) != 1U)
        {
            W25Qx_Disable();
            return W25Qx_ERROR;
        }
        W25Qx_Disable();
        
        /* Wait the end of Flash writing */
        while (W25Qx_GetStatus() == W25Qx_BUSY)
        {
            /* Check for the Timeout */
            if ((GET_TICK() - tickstart) > W25QXXXX_TIMEOUT_VALUE)
            {
                return W25Qx_TIMEOUT;
            }
        }
        
        /* Update the address and size variables for next page programming */
        current_addr += current_size;
        pData += current_size;
        current_size = ((current_addr + W25QXXXX_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : W25QXXXX_PAGE_SIZE;
    } while (current_addr < end_addr);

    return W25Qx_OK;
}

/**
 * @brief Erase the specified sector of the W25QXX memory
 * @param Address Sector address to erase
 * @retval uint8_t Memory status (W25Qx_OK or W25Qx_TIMEOUT)
 */
uint8_t W25Qx_Erase_Block(uint32_t Address)
{
    uint8_t cmd[4];
    uint32_t tickstart = GET_TICK();
    
    cmd[0] = SECTOR_ERASE_CMD;
    cmd[1] = (uint8_t)(Address >> 16U);
    cmd[2] = (uint8_t)(Address >> 8U);
    cmd[3] = (uint8_t)(Address);
    
    /* Enable write operations */
    if (W25Qx_WriteEnable() != W25Qx_OK)
    {
        return W25Qx_ERROR;
    }
    
    /* Select the FLASH: Chip Select low */
    W25Qx_Enable();
    /* Send the sector erase command */
    (void)SPI1_WriteByte(cmd, 4U, W25QXXXX_TIMEOUT_VALUE);
    /* Deselect the FLASH: Chip Select high */
    W25Qx_Disable();
    
    /* Wait the end of Flash erasing */
    while (W25Qx_GetStatus() == W25Qx_BUSY)
    {
        /* Check for the Timeout */
        if ((GET_TICK() - tickstart) > W25QXXXX_SECTOR_ERASE_MAX_TIME)
        {
            return W25Qx_TIMEOUT;
        }
    }
    
    return W25Qx_OK;
}

/**
 * @brief Erase the entire W25QXX memory (This function will take a very long time)
 * @retval uint8_t Memory status (W25Qx_OK or W25Qx_TIMEOUT)
 */
uint8_t W25Qx_Erase_Chip(void)
{
    uint8_t cmd[1];
    uint32_t tickstart = GET_TICK();
    
    cmd[0] = CHIP_ERASE_CMD;
    
    /* Enable write operations */
    if (W25Qx_WriteEnable() != W25Qx_OK)
    {
        return W25Qx_ERROR;
    }
    
    /* Select the FLASH: Chip Select low */
    W25Qx_Enable();
    /* Send the chip erase command */
    (void)SPI1_WriteByte(cmd, 1U, W25QXXXX_TIMEOUT_VALUE);
    /* Deselect the FLASH: Chip Select high */
    W25Qx_Disable();
    
    /* Wait the end of Flash erasing */
    while (W25Qx_GetStatus() == W25Qx_BUSY)
    {
        /* Check for the Timeout */
        if ((GET_TICK() - tickstart) > W25QXXXX_BULK_ERASE_MAX_TIME)
        {
            return W25Qx_TIMEOUT;
        }
    }
    
    return W25Qx_OK;
}


