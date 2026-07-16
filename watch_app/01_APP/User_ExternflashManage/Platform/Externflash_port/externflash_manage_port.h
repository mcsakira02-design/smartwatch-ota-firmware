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
 
#ifndef __EXTERNFLASH_MANAGE_PORT_H__  /* Avoid repeated inclusion */
#define __EXTERNFLASH_MANAGE_PORT_H__


//******************************** Includes *********************************//
#include "stdint.h"
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
void externflash_init(void);

void externflash_deinit(void);

void externflash_read(uint32_t addr, uint32_t size, uint8_t *p_buf);

void externflash_write(uint32_t addr, uint32_t size, uint8_t *p_buf);

void externflash_write_noerase(void);
void externflash_erasesector(void);
void externflash_wakeup(void);
void externflash_write_sleep(void);
void externflash_write_Test(void);
void externflash_erasechip(void);
//******************************** APIs *************************************//


#endif /* __EC_BSP_TEMP_HUMI_XXX_HANDLER_H__ */
