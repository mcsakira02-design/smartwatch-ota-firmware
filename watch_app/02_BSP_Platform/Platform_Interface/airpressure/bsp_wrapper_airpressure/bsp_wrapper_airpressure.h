/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file bsp_wrapper_airpressure.h
 * 
 * @par dependencies 
 * - <Driver_Layer>.h
 * - stdbool.h
 * - stdint.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of airpressure handler 
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
 
#ifndef __BSP_WRAPPER_AIRPRESSURE_H__  /* Avoid repeated inclusion */
#define __BSP_WRAPPER_AIRPRESSURE_H__


//******************************** Includes *********************************//
#include "stdint.h"
#include "stdbool.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//


//******************************** Typedefs *********************************//
typedef struct _airpressure_drv_t {
    uint32_t    idx;
    uint32_t    dev_id;
    void        * user_data; 
    void        (*airpressure_drv_init)(struct _airpressure_drv_t *dev);
    void        (*airpressure_drv_deinit)(struct _airpressure_drv_t *dev);
    void        (*airpressure_drv_read_id)(struct _airpressure_drv_t *dev,
                                            uint8_t * const p_device_id);

    void        (*airpressure_drv_spl_sleep)(struct _airpressure_drv_t *dev);
    void        (*airpressure_drv_spl_wakeup)(struct _airpressure_drv_t *dev);
    void        (*airpressure_drv_altitude_calculate)(struct _airpressure_drv_t *dev,
                                                    float * const pf_altitudedata);
    void        (*airpressure_drv_pressure_calculate)(struct _airpressure_drv_t *dev,
                                                    float * const pf_altitudedata);
    void        (*airpressure_drv_temperature_calculate)(struct _airpressure_drv_t *dev,
                                                    float * const pf_altitudedata);
} airpressure_drv_t;

//******************************** Typedefs *********************************//


//**************************** Interface Structs ****************************//

//**************************** Interface Structs ****************************//


//******************************** Classes **********************************//

//******************************** Classes **********************************//


//******************************** APIs *************************************//
bool drv_adapter_airpressure_reg(uint32_t index, airpressure_drv_t * dev);

void drv_adapter_airpressure_init(void);

void drv_adapter_airpressure_deinit(void);

void drv_adapter_airpressure_read_id(uint8_t * const p_device_id);

void drv_adapter_airpressure_drv_spl_sleep(void);

void drv_adapter_airpressure_drv_spl_wakeup(void);

void drv_adapter_airpressure_drv_altitude_calculate(float * const pf_altitudedata);

void drv_adapter_airpressure_drv_pressure_calculate(float * const pf_pressuredata);

void drv_adapter_airpressure_drv_temperature_calculate(float * const pf_temperaturedata);

//******************************** APIs *************************************//
#endif /*  */
