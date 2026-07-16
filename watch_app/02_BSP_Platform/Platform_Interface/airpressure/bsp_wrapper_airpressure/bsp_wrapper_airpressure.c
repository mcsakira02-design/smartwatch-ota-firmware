/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file bsp_adapter_port_airpressure.c
 * 
 * @par dependencies 
 * - bsp_adapter_port_airpressure.h
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
#include "bsp_wrapper_airpressure.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//
static airpressure_drv_t       _airpressure_drv_dev[2];
static uint32_t             _s_current_airpressure_dev_idx = 0;
//******************************** Variables ********************************//

//******************************** Functions ********************************//
bool drv_adapter_airpressure_reg(uint32_t index, airpressure_drv_t *dev)
{
    if (index >= 2) {
        return false;
    }
    
    _airpressure_drv_dev[index].idx = index;
    _airpressure_drv_dev[index].dev_id = dev->dev_id;
    _airpressure_drv_dev[index].user_data = dev->user_data;
    _airpressure_drv_dev[index].airpressure_drv_init = dev->airpressure_drv_init;
    _airpressure_drv_dev[index].airpressure_drv_deinit = dev->airpressure_drv_deinit;
    _airpressure_drv_dev[index].airpressure_drv_read_id = dev->airpressure_drv_read_id;
    _airpressure_drv_dev[index].airpressure_drv_spl_sleep = dev->airpressure_drv_spl_sleep;
    _airpressure_drv_dev[index].airpressure_drv_spl_wakeup = dev->airpressure_drv_spl_wakeup;
    _airpressure_drv_dev[index].airpressure_drv_altitude_calculate = \
                                            dev->airpressure_drv_altitude_calculate;
    _airpressure_drv_dev[index].airpressure_drv_pressure_calculate = \
                                            dev->airpressure_drv_pressure_calculate;
    _airpressure_drv_dev[index].airpressure_drv_temperature_calculate = \
                                            dev->airpressure_drv_temperature_calculate;
    _s_current_airpressure_dev_idx = index;
    return true;
}

void drv_adapter_airpressure_init(void) 
{
    airpressure_drv_t * dev = \
            &_airpressure_drv_dev[_s_current_airpressure_dev_idx];
    if(dev->airpressure_drv_init) {
        dev->airpressure_drv_init(dev);
    }
    return;
}

void drv_adapter_airpressure_deinit(void) 
{
    airpressure_drv_t * dev = \
            &_airpressure_drv_dev[_s_current_airpressure_dev_idx];
    if(dev->airpressure_drv_deinit) {
        dev->airpressure_drv_deinit(dev);
    }
    return;
}

void drv_adapter_airpressure_read_id(uint8_t * const p_device_id) {
    airpressure_drv_t * dev = \
            &_airpressure_drv_dev[_s_current_airpressure_dev_idx];

    if(dev->airpressure_drv_read_id) {
        dev->airpressure_drv_read_id(dev,p_device_id);
    }
    return;
}

void drv_adapter_airpressure_drv_spl_sleep(void)
{
    airpressure_drv_t * dev = \
            &_airpressure_drv_dev[_s_current_airpressure_dev_idx];

    if(dev->airpressure_drv_spl_sleep) {
        dev->airpressure_drv_spl_sleep(dev);
    }
    return;
}

void drv_adapter_airpressure_drv_spl_wakeup(void)
{
    airpressure_drv_t * dev = \
            &_airpressure_drv_dev[_s_current_airpressure_dev_idx];
    if(dev->airpressure_drv_spl_wakeup) {
        dev->airpressure_drv_spl_wakeup(dev);
    }
    return;
}

void drv_adapter_airpressure_drv_altitude_calculate(float * const pf_altitudedata)
{
    airpressure_drv_t * dev = \
            &_airpressure_drv_dev[_s_current_airpressure_dev_idx];
    if(dev->airpressure_drv_altitude_calculate) {
        dev->airpressure_drv_altitude_calculate(dev,pf_altitudedata);
    }
    return;
}

void drv_adapter_airpressure_drv_pressure_calculate(float * const pf_pressuredata)
{
    airpressure_drv_t * dev = \
            &_airpressure_drv_dev[_s_current_airpressure_dev_idx]; 
    if(dev->airpressure_drv_pressure_calculate) {
        dev->airpressure_drv_pressure_calculate(dev,pf_pressuredata);
    }
    return;
}

void drv_adapter_airpressure_drv_temperature_calculate(float * const pf_temperaturedata)
{
    airpressure_drv_t * dev = \
            &_airpressure_drv_dev[_s_current_airpressure_dev_idx];
    if(dev->airpressure_drv_temperature_calculate) {
        dev->airpressure_drv_temperature_calculate(dev,pf_temperaturedata);
    }
    return;
}