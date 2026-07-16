/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file airpressure_port.c
 * 
 * @par dependencies 
 * - airpressure_port.h
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
#include "airpressure_port.h"
#include "bsp_wrapper_airpressure.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//

//******************************** Variables ********************************//

//******************************** Functions ********************************//
void airpressure_init(void)
{
    drv_adapter_airpressure_init();
}
void airpressure_deinit(void)
{
    drv_adapter_airpressure_deinit();
}

void airpressure_read_id(uint8_t * const p_device_id)
{
    drv_adapter_airpressure_read_id(p_device_id);
}

void airpressure_spl_sleep(void)
{
    drv_adapter_airpressure_drv_spl_sleep();
}

void airpressure_spl_wakeup(void)
{
    drv_adapter_airpressure_drv_spl_wakeup();
}

void airpressure_altitude_calculate(float * const pf_altitude)
{
    drv_adapter_airpressure_drv_altitude_calculate(pf_altitude);
}

void airpressure_pressure_calculate(float * const pf_airpressure)
{
    drv_adapter_airpressure_drv_pressure_calculate(pf_airpressure);
}

void airpressure_temperature_calculate(float * const pf_temperature)
{
    drv_adapter_airpressure_drv_temperature_calculate(pf_temperature);
}
