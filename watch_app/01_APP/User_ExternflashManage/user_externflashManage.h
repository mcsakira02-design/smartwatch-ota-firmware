/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file User_Sensor.h
 * 
 * @par dependencies 
 * - User_Sensor.h
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
#ifndef __USER_EXTERNFLASHMANAGE_H__  //Avoid repeated including same files later
#define __USER_EXTERNFLASHMANAGE_H__

//******************************** Includes *********************************//
#include "osal.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//
/*定义事件位*/
#define EVENT_OTA       (1 << 0)
#define EVENT_FLASHDB   (1 << 1)
#define EVENT_FATFS     (1 << 2)
#define EVENT_LVGL      (1 << 3)

#define MEMORY_OTA_START_ADDRESS        (0x000000UL)
#define MEMORY_OTA_END_ADDRESS          (0x0FFFFFUL)
#define MEMORY_FLASHDB_START_ADDRESS    (0x100000UL)  
#define MEMORY_FLASHDB_END_ADDRESS      (0x1FFFFFUL)  
#define MEMORY_FATFS_START_ADDRESS      (0x200000UL) 
#define MEMORY_FATFS_END_ADDRESS        (0x2FFFFFUL) 
#define MEMORY_LVGL_START_ADDRESS       (0x300000UL) 
#define MEMORY_LVGL_END_ADDRESS         (0x5FFFFFUL) 

#define LVGL_DATA_MAX_SIZE              (1100)
//******************************** Defines **********************************//
//******************************** Typedefs **********************************//
typedef struct{

    uint32_t  target_address;         // 目标地址指针
    uint32_t  data_size;              // 需读取的字节数

}extern_flash_handler_t;

typedef enum
{
  Ext_Flash_OK                = 0,     /* Operation completed successfully.  */
  Ext_Flash_ERROR             = 1,     /* Run-time error without case matched*/
  Ext_Flash_ERRORTIMEOUT      = 2,     /* Operation failed with timeout      */
  Ext_Flash_ERRORRESOURCE     = 3,     /* Resource not available.            */
  Ext_Flash_ERRORPARAMETER    = 4,     /* Parameter error.                   */
  Ext_Flash_ERRORNOMEMORY     = 5,     /* Out of memory.                     */
  Ext_Flash_RESERVED  = 0x7FFFFFFF     /* Reserved  May check the caller     */
} ext_flash_status_t;

//******************************** Struct **********************************//
//******************************** Declaring ********************************//
ext_flash_status_t Read_LvglData(uint32_t addr, uint32_t size);
void storage_manager_task(void *argument);
//******************************** Declaring ********************************//

#endif /* __USER_EXTERNFLASHMANAGE_H__ */
