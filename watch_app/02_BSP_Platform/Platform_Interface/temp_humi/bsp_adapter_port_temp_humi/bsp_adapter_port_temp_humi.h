/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file bsp_temp_humi_xxx_handler.h
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
 
#ifndef __BSP_ADAPTER_PORT_TEMPHUMI_H__  /* Avoid repeated inclusion */
#define __BSP_ADAPTER_PORT_TEMPHUMI_H__


//******************************** Includes *********************************//
#include "stdint.h"
#include "stdbool.h"
#include "bsp_wrapper_temp_humi.h"
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
void drv_adapter_temphumi_register(void);
//******************************** APIs *************************************//


#endif /* __BSP_TEMP_HUMI_XXX_HANDLER_H__ */
