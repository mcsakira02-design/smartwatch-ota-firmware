/******************************************************************************
 * Copyright (C) 2025 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file bsp_mpuxxx_handler.h
 * 
 * @par dependencies 
 * 
 * - bsp_mpuxxx_driver.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of MPU6050 and corresponding options.
 * 
 * Processing flow:
 * 
 * call directly.
 * 
 * @version V1.0
 * 
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
//******************************** Includes *********************************//
#include "bsp_mpuxxx_driver.h"

#include "FreeRTOS.h"
#include "task.h"
//******************************** Defines **********************************//

//******************************** Typedefs *********************************//
/*  Input arguments for the handler  */
typedef struct
{
	mpuxxx_iic_driver_interface_t *p_iic_driver;
    mpuxxx_timebase_interface_t   *p_timebase;
    mpuxxx_delay_interface_t      *p_delay;
    mpuxxx_os_interface_t         *p_os;
	mpuxxx_yield_interface_t      *p_yield;
} mpuxxx_handler_input_args_t;

/*  Handler structure                */
typedef struct
{
	mpuxxx_handler_input_args_t *p_input_args;
    bsp_mpuxxx_driver_t         *p_driver;
    void                        *p_queue_handle;
    void                        *p_unpack_queue_handle;
    uint32_t                    queue_item_size;
    uint32_t                    queue_length;
}bsp_mpuxxx_handler_t;

//******************************** Functions ********************************//
mpuxxx_status_t mpuxxx_handler_inst(
                        bsp_mpuxxx_handler_t *p_handler, 
                        mpuxxx_handler_input_args_t *p_input_args );

/**
 * @brief The thread function for mpuxxx handler
 * 
 * @param argument: The argument
 */
void mpuxxx_handler_thread(void *argument);

