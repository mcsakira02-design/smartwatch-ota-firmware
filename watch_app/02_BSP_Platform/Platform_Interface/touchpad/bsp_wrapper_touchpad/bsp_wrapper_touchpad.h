/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file bsp_wrapper_touchpad.h
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
 
#ifndef __DRV_ADAPTER_TOUCHPAD_H__  /* Avoid repeated inclusion */
#define __DRV_ADAPTER_TOUCHPAD_H__


//******************************** Includes *********************************//
#include "stdint.h"
#include "stdbool.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//


//******************************** Typedefs *********************************//
typedef struct _touchpad_drv_t {

    uint32_t idx;                                                                                           /**< Record the instance index. */
    uint32_t dev_id;                                                                                        /**< Record the device id. */
    void * user_data;                                                                                       /**< Record the user data */
    void (* touchpad_drv_init)(struct _touchpad_drv_t * dev);                                                 /**< function pointer to device init */
    void (* touchpad_drv_deinit)(struct _touchpad_drv_t * dev);                                                 /**< function pointer to device init */
    uint8_t (* touchpad_drv_get_finger_num)(struct _touchpad_drv_t * dev,uint8_t *p_finger_num);                   /**< function pointer to device init */
    uint8_t (* touchpad_drv_get_xy_axis)(struct _touchpad_drv_t * dev,int16_t *p_x, int16_t *p_y);                   /**< function pointer to device init */
}touchpad_drv_t;

//******************************** Typedefs *********************************//


//**************************** Interface Structs ****************************//

//**************************** Interface Structs ****************************//


//******************************** Classes **********************************//

//******************************** Classes **********************************//


//******************************** APIs *************************************//
bool drv_adapter_touchpad_reg(uint32_t index, touchpad_drv_t * dev);

void drv_adapter_touchpad_init(void);

void drv_adapter_touchpad_deinit(void);

uint8_t drv_adapter_touchpad_get_finger_num(uint8_t *p_finger_num);

uint8_t drv_adapter_touchpad_get_xy_axis(int16_t *p_x, int16_t *p_y);


//******************************** APIs *************************************//


#endif /* drv_adapter_touchpad */
