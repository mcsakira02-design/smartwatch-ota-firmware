/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file drv_adapter_port_externflash.c
 * 
 * @par dependencies 
 * - drv_adapter_port_externflash.h
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
#include "bsp_wrapper_flash.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//
static externflash_drv_t      _externflash_drv_dev[2];
static uint32_t         _s_current_externflash_dev_idx = 0;
//******************************** Variables ********************************//

//******************************** Functions ********************************//
bool drv_adapter_externflash_reg(uint32_t index, externflash_drv_t * dev)
{
    if (index >= 2) {
        return false;
    }
    _externflash_drv_dev[index].idx = \
                                index;
    _externflash_drv_dev[index].dev_id = \
                                dev->dev_id;
    _externflash_drv_dev[index].user_data = \
                                dev->user_data;
    _externflash_drv_dev[index].externflash_drv_init = \
                                dev->externflash_drv_init;
    _externflash_drv_dev[index].externflash_drv_deinit = \
                                dev->externflash_drv_deinit;
    _externflash_drv_dev[index].externflash_drv_read = \
                                dev->externflash_drv_read;
    _externflash_drv_dev[index].externflash_drv_write = \
                                dev->externflash_drv_write;
    _externflash_drv_dev[index].externflash_drv_write_noerase = \
                                dev->externflash_drv_write_noerase;
    _externflash_drv_dev[index].externflash_drv_erasechip = \
                                dev->externflash_drv_erasechip;
    _externflash_drv_dev[index].externflash_drv_erasesector = \
                                dev->externflash_drv_erasesector;
    _externflash_drv_dev[index].externflash_drv_wakeup = \
                                dev->externflash_drv_wakeup;
    _externflash_drv_dev[index].externflash_drv_sleep = \
                                dev->externflash_drv_sleep;
    _externflash_drv_dev[index].externflash_drv_test = \
                                dev->externflash_drv_test;

    _s_current_externflash_dev_idx = index;

    return true;

}

void drv_adapter_externflash_init(void) {

    externflash_drv_t * dev = \
            &_externflash_drv_dev[_s_current_externflash_dev_idx];

    if(dev->externflash_drv_init) {
        dev->externflash_drv_init(dev);
    }

    return;
}

void drv_adapter_externflash_deinit(void) {
    externflash_drv_t * dev = \
            &_externflash_drv_dev[_s_current_externflash_dev_idx];

    if(dev->externflash_drv_deinit) {
        dev->externflash_drv_deinit(dev);
    }

    return;
}

void drv_adapter_externflash_read(uint32_t addr, \
                                  uint32_t size, \
                                  uint8_t *p_buf) 
{
    externflash_drv_t * dev = \
            &_externflash_drv_dev[_s_current_externflash_dev_idx];

    if(dev->externflash_drv_read) {
        dev->externflash_drv_read(dev,addr,size,p_buf);
    }

    return;
}

void drv_adapter_externflash_write(uint32_t addr, \
                                   uint32_t size, \
                                   uint8_t *p_buf) 
{
    externflash_drv_t * dev = \
            &_externflash_drv_dev[_s_current_externflash_dev_idx];

    if(dev->externflash_drv_write) {
        dev->externflash_drv_write(dev,addr,size,p_buf);
    }

    return;
}

void drv_adapter_externflash_write_noerase(void) 
{
    externflash_drv_t * dev = \
            &_externflash_drv_dev[_s_current_externflash_dev_idx];

    if(dev->externflash_drv_write_noerase) {
        dev->externflash_drv_write_noerase(dev);
    }

    return;
}

void drv_adapter_externflash_erasechip(void) {
    externflash_drv_t * dev = \
            &_externflash_drv_dev[_s_current_externflash_dev_idx];

    if(dev->externflash_drv_erasechip) {
        dev->externflash_drv_erasechip(dev);
    }

    return;
}

void drv_adapter_externflash_erasesector(void) {
    externflash_drv_t * dev = \
            &_externflash_drv_dev[_s_current_externflash_dev_idx];

    if(dev->externflash_drv_erasesector) {
        dev->externflash_drv_erasesector(dev);
    }

    return;
}
void drv_adapter_externflash_wakeup(void) {
    externflash_drv_t * dev = \
            &_externflash_drv_dev[_s_current_externflash_dev_idx];

    if(dev->externflash_drv_wakeup) {
        dev->externflash_drv_wakeup(dev);
    }

    return;
}
void drv_adapter_externflash_sleep(void) {
    externflash_drv_t * dev = \
            &_externflash_drv_dev[_s_current_externflash_dev_idx];

    if(dev->externflash_drv_sleep) {
        dev->externflash_drv_sleep(dev);
    }

    return;
}

void drv_adapter_externflash_test(void) {
    externflash_drv_t * dev = \
            &_externflash_drv_dev[_s_current_externflash_dev_idx];

    if(dev->externflash_drv_test) {
        dev->externflash_drv_test(dev);
    }
    return;
}
