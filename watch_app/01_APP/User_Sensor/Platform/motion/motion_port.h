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
 
#ifndef __MOTION_PORT_H__  /* Avoid repeated inclusion */
#define __MOTION_PORT_H__

//******************************** Includes *********************************//
#include "main.h"
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
void motion_init(void);

void motion_deinit(void);

uint8_t* motion_readdata(void);

uint8_t motion_getreqstate(void);

void motion_readdataend(void);
//******************************** APIs *************************************//


#endif /* __EC_BSP_TEMP_HUMI_XXX_HANDLER_H__ */
