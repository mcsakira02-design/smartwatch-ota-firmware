/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file drv_adapter_temphumioment.h
 * 
 * @par dependencies 
 * - <Driver_Layer>.h
 * - stdbool.h
 * - stdint.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of temperature and humidity sensor handler 
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
 
#ifndef __DRV_ADAPTER_MOTION_H__  /* Avoid repeated inclusion */
#define __DRV_ADAPTER_MOTION_H__


//******************************** Includes *********************************//
#include "stdint.h"
#include "stdbool.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//


//******************************** Typedefs *********************************//
typedef struct _motion_drv_t {

    uint32_t idx;                                                                                /**< Record the instance index. */

    uint32_t dev_id;                                                                             /**< Record the device id. */

    void * user_data;                                                                            /**< Record the user data */

    void (* motion_drv_init)(struct _motion_drv_t * dev);                                           /**< function pointer to device init */

    void (* motion_drv_deinit)(struct _motion_drv_t * dev);                                         /**< function pointer to device deinit */

    uint8_t (* motion_drv_getreqstate)(struct _motion_drv_t * dev);                                         /**< function pointer to device deinit */

    uint8_t * (* motion_drv_readdata)(struct _motion_drv_t * dev);                                         /**< function pointer to device deinit */

    void (* motion_drv_readdataend)(struct _motion_drv_t * dev);                                         /**< function pointer to device deinit */
} motion_drv_t;

//******************************** Typedefs *********************************//


//**************************** Interface Structs ****************************//

//**************************** Interface Structs ****************************//


//******************************** Classes **********************************//

//******************************** Classes **********************************//


//******************************** APIs *************************************//
bool drv_adapter_motion_reg(uint32_t index, motion_drv_t * dev);

void drv_adapter_motion_init(void);

void drv_adapter_motion_deinit(void);

uint8_t drv_adapter_motion_getreqstate(void);

uint8_t* drv_adapter_motion_readdata(void);

void drv_adapter_motion_readdataend(void);
//******************************** APIs *************************************//


#endif /* __BSP_TEMP_HUMI_XXX_HANDLER_H__ */
