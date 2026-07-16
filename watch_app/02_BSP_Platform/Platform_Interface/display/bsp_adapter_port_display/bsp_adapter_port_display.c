/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file bsp_adapter_port_display.c
 * 
 * @par dependencies 
 * - bsp_adapter_port_display.h
 * 
 * @author ssj
 * 
 * @brief 
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
//******************************** Includes *********************************//
#include "bsp_adapter_port_display.h"
#include "bsp_wrapper_display.h"
#include "bsp_st7789_driver.h"
#include "bsp_st7789_link.h"
#include "st7789_reg_define.h"
#include "fonts.h"
#include "osal.h"
#include "tim.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//
//******************************** Defines **********************************//

//******************************** Variables ********************************//
bsp_st7789_driver_t st7789_driver_instance;
basic_oper_driver_interface_t st7789_oper_instance = {
  .pf_spi_transmit = spi_transmit_data,
  .pf_spi_transmit_dma = spi_transmit_data_dma,
  .pf_write_cs_pin = gpio_write_cs_pin,
  .pf_write_dc_pin = gpio_write_dc_pin,
  .pf_write_reset_pin = gpio_write_reset_pin
};

st7789_spi_driver_interface_t st7789_spi_instance;

st7789_timebase_interface_t st7789_time_instance = {
  .pf_delay_no_os = osal_task_delay_ms,
  .pf_get_tick_count = osal_task_get_tick_count
};

st7789_yield_interface_t st7789_yield = {
  .pf_rtos_yield = osal_task_delay_ms
};
//******************************** Variables ********************************//

//******************************** Functions ********************************//
/***********************************************************************************
 *                 Static Declarations For temphumionment
 ***********************************************************************************/
static void display_drv_init(display_drv_t *dev);
static void display_drv_deinit(display_drv_t *dev);
static void display_drv_draw_pixel(display_drv_t *dev,uint16_t x, \
            uint16_t y, uint16_t color);
static void display_drv_set_backlight(display_drv_t *dev,uint16_t \
            u16_resolution);
static void display_drv_draw_image(display_drv_t *dev, uint16_t x, \
            uint16_t y,uint16_t w, uint16_t h, const uint16_t *data);
/***********************************************************************************
 *                 Public Implements
 ***********************************************************************************/
void drv_adapter_display_register(void)
{
    display_drv_t _display_drv = {
        .idx = 0,
        .dev_id = 0,
        .display_drv_init = display_drv_init,
        .display_drv_deinit = display_drv_deinit,
        .display_drv_draw_pixel = display_drv_draw_pixel,
        .display_drv_set_backlight = display_drv_set_backlight,
        .display_drv_draw_image = display_drv_draw_image,
    };

    drv_adapter_display_reg(0, &_display_drv);
}

/***********************************************************************************
 *                 Static Implements for Display
 ***********************************************************************************/
static void display_drv_init(display_drv_t *dev)
{
  st7789_instance_driver_link(&st7789_driver_instance,
    &st7789_oper_instance,
    &st7789_spi_instance,
    &st7789_time_instance,
    &st7789_yield);
  st7789_driver_instance.pf_st7789_init(&st7789_driver_instance);
}

static void display_drv_deinit(display_drv_t *dev)
{
  ;
}


static void display_drv_draw_pixel(display_drv_t *dev,uint16_t x, \
            uint16_t y, uint16_t color)
{
  st7789_driver_instance.pf_draw_pixel(&st7789_driver_instance,x,y,color);
}

static void display_drv_set_backlight(display_drv_t *dev,\
                                      uint16_t u16_resolution)
{
  if(u16_resolution > 1000)
  {
    Set_PWM_DutyCycle(1000);
  }
  else
  {
    Set_PWM_DutyCycle(u16_resolution);
  }
}

static void display_drv_draw_image(display_drv_t *dev, \
                                   uint16_t x, \
                                   uint16_t y, \
                                   uint16_t w, \
                                   uint16_t h, \
                                   const uint16_t *data)
{
  st7789_driver_instance.pf_draw_image(&st7789_driver_instance,x,y,w,h,data);
}

//******************************** Functions ********************************//
