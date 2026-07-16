#ifndef __ST7789_DRIVER
#define __ST7789_DRIVER

#include <stdint.h>
#include "fonts.h"

typedef struct spi_gpio_driver_interface_obj
{
    /*-----need to be realized by user based on the hardware platform-----*/
    uint8_t (*pf_spi_transmit)(const uint8_t *pData, uint32_t dataLength);
    uint8_t (*pf_spi_transmit_dma)(const uint8_t *pData, uint32_t dataLength);
    uint8_t (*pf_write_reset_pin)(uint8_t pinState);
    uint8_t (*pf_write_cs_pin)(uint8_t pinState); 
    uint8_t (*pf_write_dc_pin)(uint8_t pinState);  
    /*-----need to be realized by user based on the hardware platform-----*/
}basic_oper_driver_interface_t;

typedef struct st7789_driver_interface_obj
{
    uint8_t (*pf_st7789_write_data) (void * const driver_instance, \
                                     uint8_t *pData, \
                                     uint32_t dataLength);
    uint8_t (*pf_st7789_write_simple_data) (void * const driver_instance,\
                                            const uint8_t dataSend);
    uint8_t (*pf_st7789_write_command) (void * const driver_instance, \
                                        const uint8_t cmd, \
                                        uint8_t dataLength); 
}st7789_spi_driver_interface_t;

typedef struct st7789_timebase_interface_obj
{
    uint32_t    (*pf_get_tick_count)       (void);
    void    (*pf_delay_no_os) (uint32_t delay);
    
}st7789_timebase_interface_t;

typedef struct st7789_yield_interface_obj
{
    void (*pf_rtos_yield) (const uint32_t yield_cnt);    
}st7789_yield_interface_t;



typedef struct bsp_st7789_driver_obj
{
    basic_oper_driver_interface_t * p_st7789_basic_operation;
    st7789_spi_driver_interface_t * p_st7789_spi_instance;
    st7789_timebase_interface_t * p_timebase_instance;
    st7789_yield_interface_t * p_yield_instance;

    /* Basic functions. */
    uint8_t (*pf_st7789_init) (void * const st7789_instance);
    uint8_t (*pf_set_direction) (void * const st7789_instance, \
                                 uint8_t direction);
    uint8_t (*pf_fill_color) (void * const st7789_instance, \
                              uint16_t color);
    uint8_t (*pf_draw_pixel) (void * const st7789_instance, \
                              uint16_t x, uint16_t y, uint16_t color);
    uint8_t (*pf_fill) (void * const st7789_instance, \
                        uint16_t xSta, \
                        uint16_t ySta, \
                        uint16_t xEnd, \
                        uint16_t yEnd, \
                        uint16_t color);
    uint8_t (*pf_draw_pixel_4px) (void * const st7789_instance,\
                                 uint16_t x, \
                                 uint16_t y, \
                                 uint16_t color);

    uint8_t (*pf_set_addr_window) (void * const st7789_instance, \
                                   uint16_t x0, \
                                   uint16_t y0, \
                                   uint16_t x1, \
                                   uint16_t y1);

    /* Graphical functions. */
    uint8_t (*pf_draw_line) (void * const st7789_instance, \
                             uint16_t x1, \
                             uint16_t y1, \
                             uint16_t x2, \
                             uint16_t y2, \
                             uint16_t color);
    uint8_t (*pf_draw_rectangle) (void * const st7789_instance, \
                                  uint16_t x1, \
                                  uint16_t y1, \
                                  uint16_t x2, \
                                  uint16_t y2, \
                                  uint16_t color);
    uint8_t (*pf_draw_circle) (void * const st7789_instance, \
                               uint16_t x0, \
                               uint16_t y0, \
                               uint8_t r, \
                               uint16_t color);
    uint8_t (*pf_draw_image) (void * const st7789_instance, \
                              uint16_t x, \
                              uint16_t y, \
                              uint16_t w, \
                              uint16_t h, \
                              const uint16_t *data);
    uint8_t (*pf_invert_colors) (void * const st7789_instance, \
                                 uint16_t invert);

    /* Text functions. */
    uint8_t (*pf_write_char) (void * const st7789_instance, \
                              uint16_t x, \
                              uint16_t y, \
                              uint16_t ch, 
                              font_def_t font, \
                              uint16_t color, \
                              uint16_t bgcolor);
    uint8_t (*pf_write_string) (void * const st7789_instance, \
                                uint16_t x, \
                                uint16_t y, \
                                const char *str, \
                                font_def_t font, \
                                uint16_t color, \
                                uint16_t bgcolor);
    /* Extented Graphical functions. */
    uint8_t (*pf_draw_filled_rectangle) (void * const st7789_instance, \
                                        uint16_t x, \
                                        uint16_t y, \
                                        uint16_t w, \
                                        uint16_t h, \
                                        uint16_t color);
    uint8_t (*pf_draw_triangle) (void * const st7789_instance, \
                                 uint16_t x1, \
                                 uint16_t y1, \
                                 uint16_t x2, \
                                 uint16_t y2, \
                                 uint16_t x3, \
                                 uint16_t y3, \
                                 uint16_t color);
    uint8_t (*pf_draw_filled_triangle) (void * const st7789_instance, \
                                        uint16_t x1, \
                                        uint16_t y1, \
                                        uint16_t x2, \
                                        uint16_t y2, \
                                        uint16_t x3, \
                                        uint16_t y3, \
                                        uint16_t color);
    uint8_t (*pf_draw_filled_circle) (void * const st7789_instance, \
                                      int16_t x0, \
                                      int16_t y0, \
                                      int16_t r, \
                                      uint16_t color);                                                                 

    /* Command functions */
    uint8_t (*pf_tear_effect) (void * const st7789_instance, uint8_t tear);

    /*test function*/
    uint8_t (*pf_test_your_device) (void * const st7789_instance);
}bsp_st7789_driver_t;



uint8_t st7789_instance_driver_link  (bsp_st7789_driver_t * const st7789_driver_instance,
                                       basic_oper_driver_interface_t * const st7789_basic_operation_instance,
                                       st7789_spi_driver_interface_t * const st7789_spi_gpio_instance,
                                       st7789_timebase_interface_t   * const timebase_instance,
                                       st7789_yield_interface_t      * const yield_instance);

#endif /* __ST7789_DRIVER */
