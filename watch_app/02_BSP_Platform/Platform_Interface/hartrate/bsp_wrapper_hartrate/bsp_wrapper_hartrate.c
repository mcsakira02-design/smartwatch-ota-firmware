/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file bsp_adapter_port_hartrate.c
 * 
 * @par dependencies 
 * - bsp_adapter_port_hartrate.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of AHT21 and corresponding opetions.
 * 
 * Processing flow:
 * 
 * 
 * 2.Then the users could all the IOs from instances of bsp_aht21_driver_t.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/

//******************************** Includes *********************************//
#include "bsp_wrapper_hartrate.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//
static hartrate_drv_t       _hartrate_drv_dev[2];
static uint32_t             _s_current_hartrate_dev_idx = 0;
//******************************** Variables ********************************//

//******************************** Functions ********************************//
bool drv_adapter_hartrate_reg(uint32_t index, hartrate_drv_t *dev)
{
    if (index >= 2) {
        return false;
    }
    
    _hartrate_drv_dev[index].idx = index;
    _hartrate_drv_dev[index].dev_id = dev->dev_id;
    _hartrate_drv_dev[index].user_data = dev->user_data;
    _hartrate_drv_dev[index].hartrate_drv_init = dev->hartrate_drv_init;
    _hartrate_drv_dev[index].hartrate_drv_deinit = dev->hartrate_drv_deinit;
    _hartrate_drv_dev[index].hartrate_drv_read_id = dev->hartrate_drv_read_id;
    _hartrate_drv_dev[index].hartrate_drv_read_hrs = dev->hartrate_drv_read_hrs;
    _hartrate_drv_dev[index].hartrate_drv_enable = dev->hartrate_drv_enable;
    _hartrate_drv_dev[index].hartrate_drv_disable = dev->hartrate_drv_disable;
    _s_current_hartrate_dev_idx = index;
    return true;
}

void drv_adapter_hartrate_init(void) 
{
    hartrate_drv_t * dev = \
            &_hartrate_drv_dev[_s_current_hartrate_dev_idx];
    if(dev->hartrate_drv_init) {
        dev->hartrate_drv_init(dev);
    }
    return;
}

void drv_adapter_hartrate_deinit(void) 
{
    hartrate_drv_t * dev = \
            &_hartrate_drv_dev[_s_current_hartrate_dev_idx];
    if(dev->hartrate_drv_deinit) {
        dev->hartrate_drv_deinit(dev);
    }
    return;
}

void drv_adapter_hartrate_read_id(uint8_t * const p_device_id) {
    hartrate_drv_t * dev = \
            &_hartrate_drv_dev[_s_current_hartrate_dev_idx];

    if(dev->hartrate_drv_read_id) {
        dev->hartrate_drv_read_id(dev,p_device_id);
    }
    return;
}

void drv_adapter_hartrate_drv_read_hrs(uint16_t * const p_heartrate) 
{
    hartrate_drv_t * dev = \
            &_hartrate_drv_dev[_s_current_hartrate_dev_idx];

    if(dev->hartrate_drv_read_hrs) {
        dev->hartrate_drv_read_hrs(dev,p_heartrate);
    }
    return;
}

void drv_adapter_hartrate_drv_enable(void) 
{
    hartrate_drv_t * dev = \
            &_hartrate_drv_dev[_s_current_hartrate_dev_idx];

    if(dev->hartrate_drv_enable) {
        dev->hartrate_drv_enable(dev);
    }

    return;
}

void drv_adapter_hartrate_drv_disable(void) 
{
    hartrate_drv_t * dev = \
            &_hartrate_drv_dev[_s_current_hartrate_dev_idx];

    if(dev->hartrate_drv_disable) {
        dev->hartrate_drv_disable(dev);
    }

    return;
}
