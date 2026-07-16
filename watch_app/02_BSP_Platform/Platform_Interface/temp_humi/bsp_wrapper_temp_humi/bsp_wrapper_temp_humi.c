/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file drv_adapter_port_temphumioment.c
 * 
 * @par dependencies 
 * - drv_adapter_port_temphumioment.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of AHT21 and corresponding opetions.
 * 
 * Processing flow:
 * 
 * 1.The aht21_inst function will instantiate the bsp_aht21_driver_t object and
 * with the needed funtion interface. 
 * 
 * 2.Then the users could all the IOs from instances of bsp_aht21_driver_t.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/

//******************************** Includes *********************************//
#include "bsp_wrapper_temp_humi.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//
static temphumi_drv_t       _temphumi_drv_dev[2];
static uint32_t             _s_current_temphumi_dev_idx = 0;
//******************************** Variables ********************************//

//******************************** Functions ********************************//
bool drv_adapter_temphumi_reg(uint32_t index, temphumi_drv_t * dev)
{
    if (index >= 2) {
        return false;
    }
    _temphumi_drv_dev[index].idx = \
                             index;
    _temphumi_drv_dev[index].dev_id = \
                             dev->dev_id;
    _temphumi_drv_dev[index].user_data = \
                             dev->user_data;
    _temphumi_drv_dev[index].temphumi_drv_init = \
                             dev->temphumi_drv_init;
    _temphumi_drv_dev[index].temphumi_drv_deinit = \
                             dev->temphumi_drv_deinit;
    _temphumi_drv_dev[index].temphumi_drv_read_temp = \
                             dev->temphumi_drv_read_temp;
    _temphumi_drv_dev[index].temphumi_drv_read_humi = \
                             dev->temphumi_drv_read_humi;
    _temphumi_drv_dev[index].temphumi_drv_read_temp_and_humi = \
                             dev->temphumi_drv_read_temp_and_humi;

    _s_current_temphumi_dev_idx = index;

    return true;
}

void drv_adapter_temphumi_init(void) {

    temphumi_drv_t * dev = &_temphumi_drv_dev[_s_current_temphumi_dev_idx];

    if(dev->temphumi_drv_init) {
        dev->temphumi_drv_init(dev);
    }

    return;
}

void drv_adapter_temphumi_deinit(void) {
    temphumi_drv_t * dev = &_temphumi_drv_dev[_s_current_temphumi_dev_idx];

    if(dev->temphumi_drv_deinit) {
        dev->temphumi_drv_deinit(dev);
    }

    return;
}

void drv_adapter_temphumi_read_temp(float *temp) {
    temphumi_drv_t * dev = &_temphumi_drv_dev[_s_current_temphumi_dev_idx];

    if(dev->temphumi_drv_read_temp) {
        dev->temphumi_drv_read_temp(dev,temp);
    }

    return;
}

void drv_adapter_temphumi_read_humi(float *humi) {
    temphumi_drv_t * dev = &_temphumi_drv_dev[_s_current_temphumi_dev_idx];

    if(dev->temphumi_drv_read_humi) {
        dev->temphumi_drv_read_humi(dev,humi);
    }

    return;
}

void drv_adapter_temphumi_read_temp_and_humi(float *temp,float *humi) {
    temphumi_drv_t * dev = &_temphumi_drv_dev[_s_current_temphumi_dev_idx];

    if(dev->temphumi_drv_read_temp_and_humi) {
        dev->temphumi_drv_read_temp_and_humi(dev,temp,humi);
    }

    return;
}
