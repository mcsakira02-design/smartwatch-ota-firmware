/******************************************************************************
 * Copyright (C) 2024 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file w25qxx_Handler.c
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
/* Includes ------------------------------------------------------------------*/
#include "w25qxx_Handler.h"
#include "w25qxx.h"
#include <stddef.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
st_W25Q_Handler as_w25q_handler[2];
W25Qx_Parameter s_w25qx_para;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* extern variables ---------------------------------------------------------*/

/**
 * @brief Set Block Parmeter
 * @param block_index: block index
 * @param app_size: app size
 * @return None
 */
void SetBlockParmeter(u8 block_index,uint32_t app_size)
{
    as_w25q_handler[block_index].write_index = app_size;
    as_w25q_handler[block_index].write_databuf_index = app_size % BLOCK_SIZE;
    as_w25q_handler[block_index].write_sector_index = app_size / BLOCK_SIZE;
}

/**
 * @brief Initialize W25Q64 flash handler
 * @param None
 * @return None
 */
void W25Q64_Init(void)
{
    W25Qx_Init();
    W25Qx_Get_Parameter(&s_w25qx_para);
    as_w25q_handler[0].read_index = 0U;
    as_w25q_handler[0].read_sector_index = 0U;
    as_w25q_handler[0].write_databuf_index = 0U;
    as_w25q_handler[0].write_index = 0U;
    as_w25q_handler[0].write_sector_index = 0U;
    as_w25q_handler[1].read_index = 0U;
    as_w25q_handler[1].read_sector_index = 0U;
    as_w25q_handler[1].write_databuf_index = 0U;
    as_w25q_handler[1].write_index = 0U;
    as_w25q_handler[1].write_sector_index = 0U;
}

/**
 * @brief Erase entire W25Q64 flash chip,禁止使用该函数，flash存在其他数据段
 * @param None
 * @return uint8_t 0: success, 1: failure
 */
uint8_t W25Q64_EraseChip(void)
{
    if (0U == W25Qx_Erase_Chip())
    {
        as_w25q_handler[0].read_index = 0U;
        as_w25q_handler[0].read_sector_index = 0U;
        as_w25q_handler[0].write_databuf_index = 0U;
        as_w25q_handler[0].write_index = 0U;
        as_w25q_handler[0].write_sector_index = 0U;
        as_w25q_handler[1].read_index = 0U;
        as_w25q_handler[1].read_sector_index = 0U;
        as_w25q_handler[1].write_databuf_index = 0U;
        as_w25q_handler[1].write_index = 0U;
        as_w25q_handler[1].write_sector_index = 0U;
        return 0U;
    }
    return 1U;
}

/**
 * @brief Write data to W25Q64 flash
 * @param data Pointer to data buffer
 * @param length Length of data to write
 * @return uint8_t 0: success, 1: failure
 */
uint8_t W25Q64_WriteData(uint8_t block_index, uint8_t *data, uint32_t length)
{
    uint32_t addr = 0U;
    uint16_t index = 0U;
    
    /* Parameter validation */
    if (data == NULL)
    {
        return 1U;
    }
    
    for (uint16_t i = 0U; i < length; i++)
    {
        /* 1. Cache data to write buffer */
        index = as_w25q_handler[block_index].write_databuf_index;
        as_w25q_handler[block_index].databuf[index] = data[i];
        as_w25q_handler[block_index].write_databuf_index++;
        
        /* 2. Check if buffer is full (4096 bytes) */
        if (as_w25q_handler[block_index].write_databuf_index == s_w25qx_para.SUBSECTOR_SIZE)
        {
            as_w25q_handler[block_index].write_databuf_index = 0U;
            
            /* Erase 1 sector */
            addr = s_w25qx_para.SUBSECTOR_SIZE * as_w25q_handler[block_index].write_sector_index;
            if(block_index == BLOCKB)
            {
                addr += EXTERN_FlashBstartAddr;
            }
            W25Qx_Erase_Block(addr);
            W25Qx_WriteEnable();
            
            /* Write entire sector (4096 bytes) */
            for (uint8_t j = 0U; j < 16U; j++)
            {
                /* Get current write address */
                addr = (s_w25qx_para.SUBSECTOR_SIZE * as_w25q_handler[block_index].write_sector_index) + 
                       (s_w25qx_para.PAGE_TOTAL_SIZE * j);
                if(block_index == BLOCKB)
                {
                    addr += EXTERN_FlashBstartAddr;
                }
                /* Execute write operation */
                index = s_w25qx_para.PAGE_TOTAL_SIZE * j;
                W25Qx_Write(&as_w25q_handler[block_index].databuf[index], addr, s_w25qx_para.PAGE_TOTAL_SIZE);
            }
            as_w25q_handler[block_index].write_sector_index++;
            
            /* Record total written data length */
            as_w25q_handler[block_index].write_index += s_w25qx_para.SUBSECTOR_SIZE;
        }
    }
    return 0U;
}

/**
 * @brief Finish writing remaining data in buffer to W25Q64 flash
 * @param None
 * @return uint8_t 0: success
 */
uint8_t W25Q64_WriteData_End(uint8_t block_index)   
{
    uint32_t addr = 0U;
    uint16_t index = 0U;
    uint8_t page_size = 0U;
    
    /* Check if there is remaining data in buffer */
    if (0U != as_w25q_handler[block_index].write_databuf_index)
    {
        /* Calculate number of pages to write */
        page_size = as_w25q_handler[block_index].write_databuf_index / s_w25qx_para.PAGE_TOTAL_SIZE;
        
        /* Erase sector first */
        addr = s_w25qx_para.SUBSECTOR_SIZE * as_w25q_handler[block_index].write_sector_index;
        if(block_index == BLOCKB)
        {
            addr += EXTERN_FlashBstartAddr;
        }
        W25Qx_Erase_Block(addr);
        W25Qx_WriteEnable();
        
        /* Write complete pages */
        for (uint8_t j = 0U; j < page_size; j++)
        {
            /* Get current write address */
            addr = (s_w25qx_para.SUBSECTOR_SIZE * as_w25q_handler[block_index].write_sector_index) + 
                   (s_w25qx_para.PAGE_TOTAL_SIZE * j);
            if(block_index == BLOCKB)
            {
                addr += EXTERN_FlashBstartAddr;
            }
            /* Execute write operation */
            index = s_w25qx_para.PAGE_TOTAL_SIZE * j;
            W25Qx_Write(&as_w25q_handler[block_index].databuf[index], addr, s_w25qx_para.PAGE_TOTAL_SIZE);
        }

        /* Write remaining data less than one page */
        if (0U != (as_w25q_handler[block_index].write_databuf_index % s_w25qx_para.PAGE_TOTAL_SIZE))
        {
            /* Get current write address */
            addr = (s_w25qx_para.SUBSECTOR_SIZE * as_w25q_handler[block_index].write_sector_index) + 
                   (s_w25qx_para.PAGE_TOTAL_SIZE * page_size);
            if(block_index == BLOCKB)
            {
                addr += EXTERN_FlashBstartAddr;
            }
            /* Execute write operation */
            index = s_w25qx_para.PAGE_TOTAL_SIZE * page_size;
            W25Qx_Write(&as_w25q_handler[block_index].databuf[index], addr, 
                        as_w25q_handler[block_index].write_databuf_index % s_w25qx_para.PAGE_TOTAL_SIZE);
        }
        as_w25q_handler[block_index].write_index += as_w25q_handler[block_index].write_databuf_index;   
    }
    return 0U;
}

/**
 * @brief Read data from W25Q64 flash
 * @param data Pointer to data buffer (requires 4096 bytes buffer)
 * @param length Pointer to length variable, returns actual read length
 * @return uint8_t 0: success, 1: no more data, 2: read error
 */
uint8_t W25Q64_ReadData(uint8_t block_index, uint8_t *data, uint16_t *length)
{
    uint32_t addr = 0U;
    
    /* Parameter validation */
    if ((data == NULL) || (length == NULL))
    {
        return 2U;
    }

    /* 1. Check if there is data to read */
    if (as_w25q_handler[block_index].write_index > as_w25q_handler[block_index].read_index)
    {
        /* Check if data crosses 4K boundary */
        if (as_w25q_handler[block_index].write_sector_index > as_w25q_handler[block_index].read_sector_index)
        {
            /* Data crosses 4K boundary - read full sector */
            *length = s_w25qx_para.SUBSECTOR_SIZE;
            addr = as_w25q_handler[block_index].read_sector_index * s_w25qx_para.SUBSECTOR_SIZE;
            if(block_index == BLOCKB)
            {
                addr += EXTERN_FlashBstartAddr;
            }
            if (0U != W25Qx_Read(data, addr, *length))
            {
                return 2U;
            }
            as_w25q_handler[block_index].read_sector_index++;
        }
        else
        {
            /* Data within 4K boundary */
            *length = as_w25q_handler[block_index].write_index - as_w25q_handler[block_index].read_index;
            addr = as_w25q_handler[block_index].read_sector_index * s_w25qx_para.SUBSECTOR_SIZE;
            if(block_index == BLOCKB)
            {
                addr += EXTERN_FlashBstartAddr;
            }
            if (0U != W25Qx_Read(data, addr, *length))
            {
                return 2U;
            }
        }
        as_w25q_handler[block_index].read_index += *length;
        return 0U;
    }
    else
    {
        return 1U;
    }
}
