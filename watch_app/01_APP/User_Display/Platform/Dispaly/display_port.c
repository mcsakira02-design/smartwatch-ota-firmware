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
#include "display_port.h"
#include "bsp_wrapper_display.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//

//******************************** Variables ********************************//

//******************************** Functions ********************************//
void display_init(void)
{
    drv_wrapper_display_init();
}
void display_deinit(void)
{
    drv_wrappter_display_deinit();
}

void display_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    drv_wrapper_display_draw_pixel(x, y, color);
}

void display_set_backlight(uint16_t u16_resolution)
{
    drv_wrapper_display_set_backlight(u16_resolution);
}

void display_draw_image(uint16_t x, \
                                        uint16_t y, \
                                        uint16_t w, \
                                        uint16_t h, \
                                        const uint16_t *data)
{
    drv_wrapper_display_drv_draw_image(x, y, w, h, data);
}