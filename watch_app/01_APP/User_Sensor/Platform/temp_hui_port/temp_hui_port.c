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
 * 1.The aht21_inst function will instantiate the bsp_aht21_driver_t object and
 * with the needed funtion interface. 
 * 
 * 2.Then the users could all the IOs from instances of bsp_aht21_driver_t.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/

//******************************** Includes *********************************//
#include "temp_hui_port.h"
#include "bsp_wrapper_temp_humi.h"
//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//

//******************************** Variables ********************************//

//******************************** Functions ********************************//

void temphumi_init(void) {

    drv_adapter_temphumi_init();
    return;
}

void temphumi_deinit(void) {

    drv_adapter_temphumi_deinit();

    return;
}

void temphumi_read_temp(float *temp) {

    drv_adapter_temphumi_read_temp(temp);

    return;
}

void temphumi_read_humi(float *humi) {

    drv_adapter_temphumi_read_humi(humi);

    return;
}

void temphumi_read_temp_and_humi(float *temp,float *humi) {

    drv_adapter_temphumi_read_temp_and_humi(temp,humi);

    return;
}
