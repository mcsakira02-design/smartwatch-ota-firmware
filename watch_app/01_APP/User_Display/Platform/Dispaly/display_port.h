/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file drv_adapter_temphumioment.h
 * 
 * @par dependencies 
 * - <Driver_Layer>.h
 * - stdbool.h
 * - stdint.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of temperature and humidity sensor handler 
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
 
#ifndef __DISPLAY_PORT_H__  /* Avoid repeated inclusion */
#define __DISPLAY_PORT_H__


//******************************** Includes *********************************//
#include "stdint.h"
#include "stdbool.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//


//******************************** Typedefs *********************************//


//******************************** Typedefs *********************************//


//**************************** Interface Structs ****************************//

//**************************** Interface Structs ****************************//


//******************************** Classes **********************************//

//******************************** Classes **********************************//


//******************************** APIs *************************************//
void display_init(void);

void display_deinit(void);

void display_draw_image(uint16_t x, \
                                        uint16_t y, \
                                        uint16_t w, \
                                        uint16_t h, \
                                        const uint16_t *data);

void display_draw_pixel(uint16_t x, uint16_t y, uint16_t color);

void display_set_backlight(uint16_t u16_resolution);

//******************************** APIs *************************************//


#endif /* __EC_BSP_TEMP_HUMI_XXX_HANDLER_H__ */
