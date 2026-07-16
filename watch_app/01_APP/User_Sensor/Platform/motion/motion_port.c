/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file drv_adapter_port_temphumioment.c
 * 
 * @par dependencies 
 * - drv_adapter_port_temphumioment.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of AHT21 and corresponding opetions.
 * 
 * Processing flow:
 * 

 * 2.Then the users could all the IOs from instances of bsp_aht21_driver_t.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/

//******************************** Includes *********************************//
#include "motion_port.h"
#include "bsp_wrapper_motion.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//

//******************************** Variables ********************************//

//******************************** Functions ********************************//

void motion_init(void) {

    drv_adapter_motion_init();
    return;
}

void motion_deinit(void) {

    drv_adapter_motion_deinit();

    return;
}

uint8_t* motion_readdata(void) {

    return drv_adapter_motion_readdata();
}

uint8_t motion_getreqstate(void) {

    return drv_adapter_motion_getreqstate();
}

void motion_readdataend(void) {

    drv_adapter_motion_readdataend();
    return;
}
