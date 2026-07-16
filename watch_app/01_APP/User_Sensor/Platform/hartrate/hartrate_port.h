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
 
#ifndef __HART_RATE_PORT_H__  /* Avoid repeated inclusion */
#define __HART_RATE_PORT_H__


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
void hartrate_init(void);

void hartrate_deinit(void);

void hartrate_read_id(uint8_t * const p_device_id);

void hartrate_drv_enable(void);

void hartrate_drv_disable(void);

void hartrate_drv_read_hrs(uint16_t * const p_heartrate);
//******************************** APIs *************************************//


#endif /* __EC_BSP_TEMP_HUMI_XXX_HANDLER_H__ */
