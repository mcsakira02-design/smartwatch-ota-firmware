/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file drv_adapter_port_externflashoment.c
 * 
 * @par dependencies 
 * - drv_adapter_port_externflashoment.h
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
#include "externflash_manage_port.h"
#include "bsp_adapter_port_flash.h"
#include "bsp_wrapper_flash.h"

//******************************** Includes *********************************//
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//

//******************************** Variables ********************************//

//******************************** Functions ********************************//

void externflash_init(void) {

    drv_adapter_externflash_init();
    return;
}

void externflash_deinit(void) {

    drv_adapter_externflash_deinit();

    return;
}

void externflash_read(uint32_t addr, uint32_t size, uint8_t *p_buf) {

    drv_adapter_externflash_read(addr, size, p_buf);

    return;
}

void externflash_write(uint32_t addr, uint32_t size, uint8_t *p_buf) {

    drv_adapter_externflash_write(addr, size, p_buf);

    return;
}

void externflash_write_noerase(void) {

    drv_adapter_externflash_write_noerase();

    return;
}

void externflash_erasechip(void) {

    drv_adapter_externflash_erasechip();

    return;
}

void externflash_erasesector(void) {

    drv_adapter_externflash_erasesector();

    return;
}

void externflash_wakeup(void) {

    drv_adapter_externflash_wakeup();

    return;
}

void externflash_Test(void) {

    drv_adapter_externflash_test();
    return;
}

void externflash_sleep(void) {

    drv_adapter_externflash_sleep();

    return;
}
