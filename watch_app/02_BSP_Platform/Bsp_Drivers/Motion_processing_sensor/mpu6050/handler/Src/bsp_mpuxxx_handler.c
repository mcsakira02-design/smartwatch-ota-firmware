/******************************************************************************
 * Copyright (C) 2025 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file bsp_mpuxxx_handler.c
 * 
 * @par dependencies 
 * 
 * - bsp_mpuxxx_handler.h
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
#include "bsp_mpuxxx_handler.h"
#include <stdint.h>

#include "Debug.h"

//******************************** Defines **********************************//
#define HANDLER_UNINITIALIZED 0
#define HANDLER_INITIALIZED   1

//******************************** Typedefs *********************************//

//******************************** Variables ********************************//
static uint8_t mpuxxx_handler_is_initialized = HANDLER_UNINITIALIZED;
bsp_mpuxxx_handler_t handler_instance = {0};

//******************************** Functions ********************************//
/* External variables */
extern void (*pf_pin_interrupt_callback)(void *, void *);
extern void (*pf_dma_interrupt_callback)(void *, void *);
/*
* @brief Register the callback function for mpuxxx INT interrupt
* @param callback: The callback function
*/
void register_callback(void (*callback)(void *, void *))
{
    pf_pin_interrupt_callback = callback;
}

/*
* @brief Register the callback function for DMA complete
* @param callback: The callback function
*/
void register_callback_dma(void (*callback)(void *, void *))
{
    pf_dma_interrupt_callback = callback;
}

/**
 * @brief Initialize the handler.
 * 
 * @param handler_instance: The handler to initialize.
 * 
 * @return: The status of the initialization.
 */
mpuxxx_status_t mpuxxx_handler_init(bsp_mpuxxx_handler_t *handler_instance)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    if (mpuxxx_handler_is_initialized == HANDLER_INITIALIZED)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_handler_init: handler already initialized\n");
#endif
        return MPUxxx_ERROR;
    }

    if (NULL == handler_instance->p_input_args->p_os->os_queue_create)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_handler_init: os queue create is NULL\n");
#endif
        return MPUxxx_ERROR;
    }

    // Create the mpuxxx queue
    ret = handler_instance->p_input_args->p_os->os_queue_create(
                                        handler_instance->queue_length,
                                        handler_instance->queue_item_size,
                                        &handler_instance->p_queue_handle);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_handler_init: queue create failed\n");
#endif
        return ret;
    }

    // Create the unpack queue
    ret = handler_instance->p_input_args->p_os->os_queue_create(
                                        handler_instance->queue_length,
                                        handler_instance->queue_item_size,
                                        &handler_instance->p_unpack_queue_handle);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_handler_init: unpack queue create failed\n");
#endif
        return ret;
    }

    if (NULL == handler_instance->p_driver)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_handler_init: driver is NULL\n");
#endif
        return MPUxxx_ERROR;
    }

    // Initialize the driver
    ret = bsp_mpuxxx_driver_inst(
                handler_instance->p_driver,
                handler_instance->p_input_args->p_iic_driver,
#ifdef OS_SUPPORTING
                handler_instance->p_input_args->p_yield,
                handler_instance->p_input_args->p_os,
#endif /* End of OS_SUPPORTING */
                handler_instance->p_input_args->p_delay,
                handler_instance->p_input_args->p_timebase,
                register_callback,
                register_callback_dma
#ifdef OS_SUPPORTING
                ,handler_instance->p_queue_handle
#endif /* End of OS_SUPPORTING */
                                                    );
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_handler_init: driver init failed\n");
#endif
        return ret;
    }

    return ret;
}

/**
 * @brief Initialize the handler.
 * 
 * @param handler_instance: The handler to initialize.
 * @param p_input_args: The input arguments.
 * 
 * @return: The status of the initialization.
 */
mpuxxx_status_t mpuxxx_handler_inst(
                        bsp_mpuxxx_handler_t *handler_instance, 
                        mpuxxx_handler_input_args_t *p_input_args )
{
    mpuxxx_status_t ret = MPUxxx_OK;
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("mpuxxx_handler_inst start\n");
#endif /* End of DEBUG */

/* Check the input arguments */
    if (NULL == handler_instance)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_handler_inst: handler is NULL\n");
#endif
        return MPUxxx_ERROR;
    }

    if (NULL == p_input_args)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_handler_inst: input args is NULL\n");
#endif
        return MPUxxx_ERROR;
    }

    if (NULL == p_input_args->p_iic_driver ||
        NULL == p_input_args->p_delay      ||
        NULL == p_input_args->p_os         ||
        NULL == p_input_args->p_timebase )
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_handler_inst: input args is invalid\n");
#endif
        return MPUxxx_ERROR;
    }
/* Save the input arguments */
    handler_instance->p_input_args = p_input_args;

/* Initialize the handler */
    ret = mpuxxx_handler_init(handler_instance);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_handler_inst: handler init failed\n");
#endif
        return ret;
    }

/* Set the handler initialized */
    mpuxxx_handler_is_initialized = HANDLER_INITIALIZED;

#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("mpuxxx_handler_inst end\n");
#endif /* End of DEBUG */
    return ret;
}

/**
 * @brief The thread function for mpuxxx handler
 * 
 * @param argument: The argument
 */
void mpuxxx_handler_thread(void *argument)
{
    mpuxxx_status_t ret = MPUxxx_OK;
	uint8_t data = 0;
	
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("mpuxxx_handler_thread start\n");
#endif

    if (NULL == argument)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_handler_thread: argument is NULL\n");
#endif
        return;
    }

    mpuxxx_handler_input_args_t *p_input_args =\
                                (mpuxxx_handler_input_args_t *)argument;

    buffer_init(&circular_buf, 10);
	// mpuxxx driver 
    bsp_mpuxxx_driver_t p_driver;
	// mpuxxx handler
    handler_instance.p_driver              = &p_driver;
    handler_instance.p_queue_handle        = NULL;
    handler_instance.p_unpack_queue_handle = NULL;
    handler_instance.queue_item_size       = 1;
    handler_instance.queue_length          = 20;

    ret = mpuxxx_handler_inst(&handler_instance, p_input_args);
	if (ret != MPUxxx_OK)
	{
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
		DEBUG_OUT("mpuxxx_handler_thread: mpuxxx_handler_inst failed\n");
#endif
		return;
	}
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
	DEBUG_OUT("=====mpuxxx_handler_inst success=====\n");
#endif

    for (;;)
    {
        // Get the data from the mpuxxx queue
        ret = handler_instance.p_input_args->p_os->os_queue_get(handler_instance.p_queue_handle,
                                                    &data,
                                                    0xffffffff);
        if (ret != MPUxxx_OK)
        {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
            DEBUG_OUT("mpuxxx_handler_thread: queue get failed\n");
#endif
        }

#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_handler_thread: data = %d\n", data);
#endif

        // Put the data into the unpack queue for unpacking
        ret = handler_instance.p_input_args->p_os->os_queue_put(handler_instance.p_unpack_queue_handle,
                                                    &data,
                                                    0);
        if (ret != MPUxxx_OK)
        {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
            DEBUG_OUT("mpuxxx_handler_thread: queue put failed\n");
#endif
        }

        vTaskDelay(2);
    }
}
