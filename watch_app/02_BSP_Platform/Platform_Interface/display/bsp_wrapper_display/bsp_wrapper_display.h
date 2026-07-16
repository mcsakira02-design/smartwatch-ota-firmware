/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file bsp_wrapper_display.h
 * 
 * @par dependencies 
 * - <Driver_Layer>.h
 * - stdbool.h
 * - stdint.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of flash handler 
 * and corresponding operations.
 * 
 * Processing flow:
 * 
 * Call directly.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
 
#ifndef __DRV_ADAPTER_DISPLAY_H__  /* Avoid repeated inclusion */
#define __DRV_ADAPTER_DISPLAY_H__


//******************************** Includes *********************************//
#include "stdint.h"
#include "stdbool.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//


//******************************** Typedefs *********************************//
typedef struct _display_drv_t {

    uint32_t idx;                                                                                           /**< Record the instance index. */
    uint32_t dev_id;                                                                                        /**< Record the device id. */
    void * user_data;                                                                                       /**< Record the user data */
    void (* display_drv_init)(struct _display_drv_t * dev);                                                 /**< function pointer to device init */
    void (* display_drv_deinit)(struct _display_drv_t * dev);                                                 /**< function pointer to device init */
    void (* display_drv_draw_pixel)(struct _display_drv_t * dev,\
                                    uint16_t x, \
                                    uint16_t y, \
                                    uint16_t color);    /**< function pointer to device init */
    void (* display_drv_set_backlight)(struct _display_drv_t * dev,\
                                       uint16_t u16_resolution);
    void ( *display_drv_draw_image)(struct _display_drv_t * dev, \
                                    uint16_t x, \
                                    uint16_t y, \
                                    uint16_t w, \
                                    uint16_t h, \
                                    const uint16_t *data);
}display_drv_t;

//******************************** Typedefs *********************************//


//**************************** Interface Structs ****************************//

//**************************** Interface Structs ****************************//


//******************************** Classes **********************************//

//******************************** Classes **********************************//


//******************************** APIs *************************************//
bool drv_adapter_display_reg(uint32_t index, display_drv_t * dev);

void drv_wrapper_display_init(void);

void drv_wrappter_display_deinit(void);

void drv_wrapper_display_draw_pixel(uint16_t x, uint16_t y, uint16_t color);

void drv_wrapper_display_set_backlight(uint16_t u16_resolution);

void drv_wrapper_display_drv_draw_image(uint16_t x, \
                                        uint16_t y, \
                                        uint16_t w, \
                                        uint16_t h, \
                                        const uint16_t *data);
//******************************** APIs *************************************//


#endif /* drv_adapter_display */
