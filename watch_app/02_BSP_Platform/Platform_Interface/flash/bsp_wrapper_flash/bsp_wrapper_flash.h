/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file bsp_wrapper_flash.h
 * 
 * @par dependencies 
 * - <Driver_Layer>.h
 * - stdbool.h
 * - stdint.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of flash handler 
 * and corresponding operations.
 * 
 * Processing flow:
 * 
 * Call directly.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
 
#ifndef __DRV_ADAPTER_FLASH_H__  /* Avoid repeated inclusion */
#define __DRV_ADAPTER_FLASH_H__


//******************************** Includes *********************************//
#include "stdint.h"
#include "stdbool.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//


//******************************** Typedefs *********************************//
typedef struct _externflash_drv_t {

    uint32_t idx;                                                                                /**< Record the instance index. */

    uint32_t dev_id;                                                                             /**< Record the device id. */

    void * user_data;                                                                            /**< Record the user data */

    void (* externflash_drv_init)(struct _externflash_drv_t * dev);                                           /**< function pointer to device init */

    void (* externflash_drv_deinit)(struct _externflash_drv_t * dev);                            /**< function pointer to device deinit */

    void (* externflash_drv_read)(struct _externflash_drv_t * dev, \
                                  uint32_t addr, \
                                  uint32_t size, \
                                  uint8_t *p_buf);

    void (* externflash_drv_write)(struct _externflash_drv_t * dev, \
                                  uint32_t addr, \
                                  uint32_t size, \
                                  uint8_t *p_buf);

    void (* externflash_drv_write_noerase)(struct _externflash_drv_t * dev);

    void (* externflash_drv_erasechip)(struct _externflash_drv_t * dev);

    void (* externflash_drv_erasesector)(struct _externflash_drv_t * dev);

    void (* externflash_drv_wakeup)(struct _externflash_drv_t * dev);

    void (* externflash_drv_sleep)(struct _externflash_drv_t * dev);

    void (* externflash_drv_test)(struct _externflash_drv_t * dev);

} externflash_drv_t;

//******************************** Typedefs *********************************//


//**************************** Interface Structs ****************************//

//**************************** Interface Structs ****************************//


//******************************** Classes **********************************//

//******************************** Classes **********************************//


//******************************** APIs *************************************//
bool drv_adapter_externflash_reg(uint32_t index, externflash_drv_t * dev);

void drv_adapter_externflash_init(void);

void drv_adapter_externflash_deinit(void);

void drv_adapter_externflash_read(uint32_t addr, uint32_t size, uint8_t *p_buf);

void drv_adapter_externflash_write(uint32_t addr, uint32_t size, uint8_t *p_buf);

void drv_adapter_externflash_write_noerase(void);

void drv_adapter_externflash_erasechip(void);

void drv_adapter_externflash_erasesector(void);

void drv_adapter_externflash_wakeup(void);

void drv_adapter_externflash_sleep(void);

void drv_adapter_externflash_test(void);
//******************************** APIs *************************************//


#endif /* __BSP_TEMP_HUMI_XXX_HANDLER_H__ */
