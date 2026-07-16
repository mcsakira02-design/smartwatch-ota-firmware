/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file drv_adapter_touchpad.c
 * 
 * @par dependencies 
 * - bsp_wrapper_touchpad.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of Disp and corresponding opetions.
 * 
 * Processing flow:
 * 
 * 1.The Disp_inst function will instantiate Disp object and
 * with the needed funtion interface. 
 * 
 * 2.Then the users could all the IOs from instances of Disp.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/

//******************************** Includes *********************************//
#include "bsp_wrapper_touchpad.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//
static touchpad_drv_t      _touchpad_drv_dev[2];
static uint32_t         _s_current_touchpad_dev_idx = 0;
//******************************** Variables ********************************//

//******************************** Functions ********************************//
bool drv_adapter_touchpad_reg(uint32_t index, touchpad_drv_t * dev)
{
    if (index >= 2) {
        return false;
    }
    _touchpad_drv_dev[index].idx = \
                             index;
    _touchpad_drv_dev[index].dev_id = \
                             dev->dev_id;
    _touchpad_drv_dev[index].user_data = \
                             dev->user_data;
    _touchpad_drv_dev[index].touchpad_drv_init = \
                             dev->touchpad_drv_init;
    _touchpad_drv_dev[index].touchpad_drv_deinit = \
                             dev->touchpad_drv_deinit;
    _touchpad_drv_dev[index].touchpad_drv_get_finger_num = \
                             dev->touchpad_drv_get_finger_num;
    _touchpad_drv_dev[index].touchpad_drv_get_xy_axis = \
                             dev->touchpad_drv_get_xy_axis;

    _s_current_touchpad_dev_idx = index;

    return true;
}

void drv_adapter_touchpad_init(void) {

    touchpad_drv_t * dev = \
            &_touchpad_drv_dev[_s_current_touchpad_dev_idx];

    if(dev->touchpad_drv_init) {
        dev->touchpad_drv_init(dev);
    }

    return;
}

void drv_adapter_touchpad_deinit(void) {
    touchpad_drv_t * dev = \
            &_touchpad_drv_dev[_s_current_touchpad_dev_idx];

    if(dev->touchpad_drv_deinit) {
        dev->touchpad_drv_deinit(dev);
    }

    return;
}

uint8_t drv_adapter_touchpad_get_finger_num(uint8_t *p_finger_num) {
    touchpad_drv_t * dev = \
            &_touchpad_drv_dev[_s_current_touchpad_dev_idx];
    uint8_t ret = 0;
    
    if(dev->touchpad_drv_get_finger_num) {
        ret = dev->touchpad_drv_get_finger_num(dev,p_finger_num);
    }

    return ret;
}

uint8_t drv_adapter_touchpad_get_xy_axis(int16_t *p_x, int16_t *p_y) {
    touchpad_drv_t * dev = \
            &_touchpad_drv_dev[_s_current_touchpad_dev_idx];
    uint8_t ret = 0;
    if(dev->touchpad_drv_get_xy_axis) {
        ret = dev->touchpad_drv_get_xy_axis(dev,p_x, p_y);
    }

    return ret;
}
