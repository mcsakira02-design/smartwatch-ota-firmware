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
 
#ifndef __BSP_WRAPPER_TEMP_HUMI_H__  /* Avoid repeated inclusion */
#define __BSP_WRAPPER_TEMP_HUMI_H__


//******************************** Includes *********************************//
#include "stdint.h"
#include "stdbool.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//


//******************************** Typedefs *********************************//
typedef struct _temphumi_drv_t {

    uint32_t idx;                                                                                /**< Record the instance index. */

    uint32_t dev_id;                                                                             /**< Record the device id. */

    void * user_data;                                                                            /**< Record the user data */

    void (* temphumi_drv_init)(struct _temphumi_drv_t * dev);                                           /**< function pointer to device init */

    void (* temphumi_drv_deinit)(struct _temphumi_drv_t * dev);                                         /**< function pointer to device deinit */

    void (* temphumi_drv_read_temp)(struct _temphumi_drv_t * dev, float *temp);                         /**< function pointer to read temp */

    void (* temphumi_drv_read_humi)(struct _temphumi_drv_t * dev, float *humi);                         /**< function pointer to read humi */

    void (* temphumi_drv_read_temp_and_humi)(struct _temphumi_drv_t * dev, float *temp, float *humi);   /**< function pointer to read temp and humi */
} temphumi_drv_t;

//******************************** Typedefs *********************************//


//**************************** Interface Structs ****************************//

//**************************** Interface Structs ****************************//


//******************************** Classes **********************************//

//******************************** Classes **********************************//


//******************************** APIs *************************************//
bool drv_adapter_temphumi_reg(uint32_t index, temphumi_drv_t * dev);

void drv_adapter_temphumi_init(void);

void drv_adapter_temphumi_deinit(void);

void drv_adapter_temphumi_read_temp(float *temp);

void drv_adapter_temphumi_read_humi(float *humi);

void drv_adapter_temphumi_read_temp_and_humi(float *temp,float *humi);
//******************************** APIs *************************************//


#endif /* __BSP_TEMP_HUMI_XXX_HANDLER_H__ */
