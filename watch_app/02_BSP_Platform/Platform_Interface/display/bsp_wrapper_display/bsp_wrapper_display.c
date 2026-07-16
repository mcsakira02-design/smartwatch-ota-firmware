/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file drv_adapter_display.c
 * 
 * @par dependencies 
 * - bsp_wrapper_display.h
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
#include "bsp_wrapper_display.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//
static display_drv_t      _display_drv_dev[2];
static uint32_t         _s_current_display_dev_idx = 0;
//******************************** Variables ********************************//

//******************************** Functions ********************************//
bool drv_adapter_display_reg(uint32_t index, display_drv_t * dev)
{
    if (index >= 2) {
        return false;
    }
    _display_drv_dev[index].idx = \
                            index;
    _display_drv_dev[index].dev_id = \
                            dev->dev_id;
    _display_drv_dev[index].user_data = \
                            dev->user_data;
    _display_drv_dev[index].display_drv_init = \
                            dev->display_drv_init;
    _display_drv_dev[index].display_drv_deinit = \
                            dev->display_drv_deinit;
    _display_drv_dev[index].display_drv_draw_pixel = \
                            dev->display_drv_draw_pixel;
	_display_drv_dev[index].display_drv_set_backlight = \
                            dev->display_drv_set_backlight;
	_display_drv_dev[index].display_drv_draw_image = \
                            dev->display_drv_draw_image;
    _s_current_display_dev_idx = index;

    return true;
}

void drv_wrapper_display_init(void) {

    display_drv_t * dev = &_display_drv_dev[_s_current_display_dev_idx];

    if(dev->display_drv_init) {
        dev->display_drv_init(dev);
    }

    return;
}

void drv_wrappter_display_deinit(void) {
    display_drv_t * dev = &_display_drv_dev[_s_current_display_dev_idx];

    if(dev->display_drv_deinit) {
        dev->display_drv_deinit(dev);
    }

    return;
}

void drv_wrapper_display_draw_pixel(uint16_t x, uint16_t y, uint16_t color) {
    display_drv_t * dev = &_display_drv_dev[_s_current_display_dev_idx];

    if(dev->display_drv_draw_pixel) {
        dev->display_drv_draw_pixel(dev,x,y,color);
    }
    return;
}

void drv_wrapper_display_set_backlight(uint16_t u16_resolution)
{
	display_drv_t * dev = &_display_drv_dev[_s_current_display_dev_idx];
    if(dev->display_drv_set_backlight) {
        dev->display_drv_set_backlight(dev,u16_resolution);
    }
}

void drv_wrapper_display_drv_draw_image(uint16_t x, \
                                        uint16_t y, \
                                        uint16_t w, \
                                        uint16_t h, \
                                        const uint16_t *data)
{
	display_drv_t * dev = &_display_drv_dev[_s_current_display_dev_idx];
    if(dev->display_drv_draw_image) {
        dev->display_drv_draw_image(dev,x,y,w,h,data);
    }
}