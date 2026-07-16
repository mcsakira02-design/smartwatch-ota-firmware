/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file hartrate_port.c
 * 
 * @par dependencies 
 * - hartrate_port.h
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
#include "hartrate_port.h"
#include "bsp_wrapper_hartrate.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//

//******************************** Variables ********************************//

//******************************** Functions ********************************//
void hartrate_init(void)
{
    drv_adapter_hartrate_init();
}
void hartrate_deinit(void)
{
    drv_adapter_hartrate_deinit();
}

void hartrate_read_id(uint8_t * const p_device_id)
{
    drv_adapter_hartrate_read_id(p_device_id);
}

void hartrate_drv_enable(void)
{
    drv_adapter_hartrate_drv_enable();
}

void hartrate_drv_disable(void)
{
    drv_adapter_hartrate_drv_disable();
}

void hartrate_drv_read_hrs(uint16_t * const p_heartrate)
{
    drv_adapter_hartrate_drv_read_hrs(p_heartrate);
}
