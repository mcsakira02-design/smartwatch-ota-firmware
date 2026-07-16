/**
 * @file w25qxx.h
 * @brief W25QXX external flash driver header file
 * @author Jack | R&D Dept. | EternalChip
 * @version V1.0 2024-09-13
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W25QXX_H
#define __W25QXX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
	 
/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup W25QXXXX
  * @{
  */

/** @defgroup W25QXXXX_Exported_Types
  * @{
  */
   
/**
  * @}
  */ 

/** @defgroup W25QXXXX_Exported_Constants
  * @{
  */
   
/**
 * @brief W25QXX Configuration
 */

/* W25Q32 default configuration */
#define W25QXXXX_FLASH_SIZE                  0x0400000U /* 32 MBits => 4MBytes */
#define W25QXXXX_SECTOR_COUNT                0x40U      /* 64 sectors of 64KBytes */
#define W25QXXXX_SECTOR_SIZE                 0x10000U   /* 64 sectors of 64KBytes */
#define W25QXXXX_SUBSECTOR_COUNT             0x0400U    /* 1024 subsectors of 4kBytes */
#define W25QXXXX_SUBSECTOR_SIZE              0x1000U    /* 1024 subsectors of 4kBytes */
#define W25QXXXX_PAGE_SIZE                   0x100U     /* 16384 pages of 256 bytes */

/* W25QXX device IDs */
#define W25Q80                               0xEF13U
#define W25Q16                               0xEF14U
#define W25Q32                               0xEF15U
#define W25Q64                               0xEF16U
#define W25Q128                              0xEF17U

/* Timing parameters */
#define W25QXXXX_DUMMY_CYCLES_READ           4U
#define W25QXXXX_DUMMY_CYCLES_READ_QUAD      10U

#define W25QXXXX_BULK_ERASE_MAX_TIME         250000U
#define W25QXXXX_SECTOR_ERASE_MAX_TIME       3000U
#define W25QXXXX_SUBSECTOR_ERASE_MAX_TIME    800U
#define W25QXXXX_TIMEOUT_VALUE               1000U

/**
 * @brief W25QXX Commands
 */
/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66U
#define RESET_MEMORY_CMD                     0x99U

#define ENTER_QPI_MODE_CMD                   0x38U
#define EXIT_QPI_MODE_CMD                    0xFFU

/* Identification Operations */
#define READ_ID_CMD                          0x90U
#define DUAL_READ_ID_CMD                     0x92U
#define QUAD_READ_ID_CMD                     0x94U
#define READ_JEDEC_ID_CMD                    0x9FU

/* Read Operations */
#define READ_CMD                             0x03U
#define FAST_READ_CMD                        0x0BU
#define DUAL_OUT_FAST_READ_CMD               0x3BU
#define DUAL_INOUT_FAST_READ_CMD             0xBBU
#define QUAD_OUT_FAST_READ_CMD               0x6BU
#define QUAD_INOUT_FAST_READ_CMD             0xEBU

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06U
#define WRITE_DISABLE_CMD                    0x04U

/* Register Operations */
#define READ_STATUS_REG1_CMD                 0x05U
#define READ_STATUS_REG2_CMD                 0x35U
#define READ_STATUS_REG3_CMD                 0x15U

#define WRITE_STATUS_REG1_CMD                0x01U
#define WRITE_STATUS_REG2_CMD                0x31U
#define WRITE_STATUS_REG3_CMD                0x11U


/* Program Operations */
#define PAGE_PROG_CMD                        0x02U
#define QUAD_INPUT_PAGE_PROG_CMD             0x32U

/* Erase Operations */
#define SECTOR_ERASE_CMD                     0x20U
#define CHIP_ERASE_CMD                       0xC7U

#define PROG_ERASE_RESUME_CMD                0x7AU
#define PROG_ERASE_SUSPEND_CMD               0x75U

/* Flag Status Register */
#define W25QXXXX_FSR_BUSY                    0x01U    /*!< busy */
#define W25QXXXX_FSR_WREN                    0x02U    /*!< write enable */
#define W25QXXXX_FSR_QE                      0x02U    /*!< quad enable */

/* GPIO control macros */
#define W25Qx_Enable()                       GPIO_ResetBits(F_CS_GPIO_Port, F_CS_Pin)
#define W25Qx_Disable()                      GPIO_SetBits(F_CS_GPIO_Port, F_CS_Pin)

/* Status definitions */
#define W25Qx_OK                             0x00U
#define W25Qx_ERROR                          0x01U
#define W25Qx_BUSY                           0x02U
#define W25Qx_TIMEOUT                        0x03U

/* Type definitions */
typedef struct
{
    uint32_t FLASH_ID;
    uint32_t FLASH_TOTAL_SIZE;
    uint32_t SECTOR_COUNT;
    uint32_t SECTOR_SIZE;
    uint32_t SUBSECTOR_COUNT;
    uint32_t SUBSECTOR_SIZE;
    uint32_t PAGE_TOTAL_SIZE;
} W25Qx_Parameter;

/* Function declarations */
uint8_t W25Qx_Init(void);
uint8_t W25Qx_WriteEnable(void);
void W25Qx_Read_ID(uint16_t *ID);
uint8_t W25Qx_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size);
uint8_t W25Qx_Write(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
uint8_t W25Qx_Erase_Block(uint32_t Address);
uint8_t W25Qx_Erase_Chip(void);
uint8_t W25Qx_Get_Parameter(W25Qx_Parameter *Para);
/**
  * @}
  */
  
/** @defgroup W25QXXXX_Exported_Functions
  * @{
  */ 
/**
  * @}
  */ 
      
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __W25Qx_H */

