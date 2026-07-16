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
 
#ifndef __AIRPRESSURE_PORT_H__  /* Avoid repeated inclusion */
#define __AIRPRESSURE_PORT_H__


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
void airpressure_init(void);

void airpressure_deinit(void);

void airpressure_read_id(uint8_t * const p_device_id);

void airpressure_spl_sleep(void);

void airpressure_spl_wakeup(void);

void airpressure_altitude_calculate(float * const pf_altitude);

void airpressure_pressure_calculate(float * const pf_airpressure);

void airpressure_temperature_calculate(float * const pf_temperature);

//******************************** APIs *************************************//


#endif /* __EC_BSP_TEMP_HUMI_XXX_HANDLER_H__ */
