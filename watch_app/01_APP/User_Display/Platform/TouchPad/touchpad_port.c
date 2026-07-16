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
#include "touchpad_port.h"
#include "bsp_wrapper_touchpad.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//

void drv_adapter_touchpad_init(void);

void drv_adapter_touchpad_deinit(void);

uint8_t drv_adapter_touchpad_get_finger_num(uint8_t *p_finger_num);

uint8_t drv_adapter_touchpad_get_xy_axis(int16_t *p_x, int16_t *p_y);
//******************************** Variables ********************************//

//******************************** Functions ********************************//
void touchpad_bspinit(void)
{
    drv_adapter_touchpad_init();
}
void touchpad_deinit(void)
{
    drv_adapter_touchpad_deinit();
}

void touchpad_get_finger_num(uint8_t *p_finger_num)
{
    drv_adapter_touchpad_get_finger_num(p_finger_num);
}

void touchpad_get_xy_axis(int16_t *p_x, int16_t *p_y)
{
    drv_adapter_touchpad_get_xy_axis(p_x, p_y);
}