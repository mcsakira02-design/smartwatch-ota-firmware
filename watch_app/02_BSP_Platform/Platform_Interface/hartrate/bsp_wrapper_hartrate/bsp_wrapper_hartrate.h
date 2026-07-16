/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file bsp_wrapper_hartrate.h
 * 
 * @par dependencies 
 * - <Driver_Layer>.h
 * - stdbool.h
 * - stdint.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of hartrate handler 
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
 
#ifndef __DRV_ADAPTER_hartrate_H__  /* Avoid repeated inclusion */
#define __DRV_ADAPTER_hartrate_H__


//******************************** Includes *********************************//
#include "stdint.h"
#include "stdbool.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//


//******************************** Typedefs *********************************//
typedef struct _hartrate_drv_t {
    uint32_t    idx;
    uint32_t    dev_id;
    void        * user_data; 
    void        (*hartrate_drv_init)(struct _hartrate_drv_t *dev);
    void        (*hartrate_drv_deinit)(struct _hartrate_drv_t *dev);
    void        (*hartrate_drv_read_id)(struct _hartrate_drv_t *dev,
                                    uint8_t * const p_device_id);
    void        (*hartrate_drv_read_hrs)(struct _hartrate_drv_t *dev,
                                        uint16_t * const p_heartrate);
    void        (*hartrate_drv_enable)(struct _hartrate_drv_t *dev);
    void        (*hartrate_drv_disable)(struct _hartrate_drv_t *dev);
} hartrate_drv_t;

//******************************** Typedefs *********************************//


//**************************** Interface Structs ****************************//

//**************************** Interface Structs ****************************//


//******************************** Classes **********************************//

//******************************** Classes **********************************//


//******************************** APIs *************************************//
bool drv_adapter_hartrate_reg(uint32_t index, hartrate_drv_t * dev);

void drv_adapter_hartrate_init(void);

void drv_adapter_hartrate_deinit(void);

void drv_adapter_hartrate_read_id(uint8_t * const p_device_id);

void drv_adapter_hartrate_drv_enable(void);

void drv_adapter_hartrate_drv_disable(void);

void drv_adapter_hartrate_drv_read_hrs(uint16_t * const p_heartrate);

//******************************** APIs *************************************//
#endif /*  */
