/******************************************************************************
 * Copyright (C) 2024 ssj
 * 
 * All Rights Reserved.
 * 
 * @file ec_bsp_flash_handler.h
 * 
 * @par dependencies 
 * - <Device-layer>.h
 * - stdio.h
 * - stdint.h
 * @author ssj
 * 
 * @brief Provide the APIs of Flash handler.
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

#ifndef __BSP_FLASH_HANDLER_H__
#define __BSP_FLASH_HANDLER_H__
/***********************************Include **********************************/
#include "bsp_w25q64_driver.h"
//#include <stdio.h>
#include <stdint.h>
/***********************************Include **********************************/

/*---------------------------------------------------------------------------*/

/***********************************Defines **********************************/

/*---Error callback code typedef ----*/
typedef enum
{
    FLASH_HANDLER_OK                    =                0,
    FLASH_HANDLER_ERROR,
    FLASH_HANDLER_ERROR_TIMEOUT,
    FLASH_HANDLER_ERROR_RESOURCE,
    FLASH_HANDLER_ERROR_PARAMETER,
    FLASH_HANDLER_ERROR_NOMEM,
    FLASH_HANDLER_ERROR_ISR,
    FLASH_HANDLER_ERROR_UNKNOWN,
    FLASH_HANDLER_ERROR_NOTINIT,
    FLASH_HANDLER_RESERVED              =       0x1FFFFFFF,
}flash_handler_status_t;

/*----Flash Handler Event code typedef----*/
typedef enum
{
    FLASH_HANDLER_EVENT_READ            =                0,
    FLASH_HANDLER_EVENT_WRITE,
    FLASH_HANDLER_EVENT_WRITE_NOERASE,
    FLASH_HANDLER_EVENT_ERASE_CHIP,
    FLASH_HANDLER_EVENT_ERASE_SECTOR,
    FLASH_HANDLER_EVENT_WAKEUP,
    FLASH_HANDLER_EVENT_SLEEP,
    FLASH_HANDLER_EVENT_TEST,
}flash_handler_event_type_t;

/*---Flash Handler Event Class defines----*/
/**
 * @note only Read or Write even need addr size & p_data
 *       other even can send NULL of them
 *       If Callback funcition is not needed, a NULL pointer can be passed in.  
 */
typedef struct
{
    uint32_t                       addr;    // Read or Write Addr
    uint32_t                       size;    // Read or Write Addr size
    uint8_t                     *p_data;    // Read or Write buffer pointer
    flash_handler_event_type_t     type;    //Event type
    void (*pf_callback)        (void *);    //Callback function
}flash_handler_event_t;

/*-----A test event----*/
static flash_handler_event_t flash_handler_test ={
    .addr =     NULL,
    .size =     NULL,
    .p_data =   NULL,
    .type    =   FLASH_HANDLER_EVENT_TEST,
    .pf_callback = NULL, 
};

/*----Not OS_SUPPORT need a metal FIFO queue*/
#ifndef     OS_SUPPORT
/*-------FIFO Len Define----------*/
#define     FLASH_METAL_QUEUE_MAX                    (10UL)
/*-------FIFO Struct Define---------*/
typedef struct 
{
    uint32_t                                         write;
    uint32_t                                          read;
    flash_handler_event_t     event[FLASH_METAL_QUEUE_MAX];
}flash_metal_queue_t;
#endif


/*---Flash Handler Interface needed ----- */

/*----------------------Form OS layer----------------------------*/
#ifdef OS_SUPPORT
typedef struct
{
    void                                            (*pf_os_delay)  (uint32_t);

    flash_handler_status_t    (*pf_os_queue_create) (uint32_t const item_num,\
                         uint32_t const item_size, void ** const queue_handle);

    flash_handler_status_t    (*pf_os_queue_send)   \
               (void * const queue_handle,void * const item, uint32_t timeout);

    flash_handler_status_t    (*pf_os_queue_receive)\
               (void * const queue_handle,void * const item, uint32_t timeout);
}flash_handler_os_interface_t;
#endif//OS_SUPPORT


/*---Input interface when instantiated---*/
typedef struct
{
    /*-Interface from Device layer-*/
    spi_w25q64_interface_t                      *p_spi_w25q64_instance;
    w25qxx_timebase_interface_t                          *p_timebase_instance;

#ifdef OS_SUPPORT
    flash_handler_os_interface_t                        *p_os_instance;
    w25qxx_os_delay_interface_t                          *p_os_delay_instance;
#else
    delay_interface_t                                *p_delay_instance;
#endif//OS_SUPPORT

}flash_handler_all_input_arg_t;


/*------Private data Class-----*/
typedef struct flash_handler_private_data flash_handler_private_data_t;


/*-------Handler Class Bsp Handler--------*/
typedef struct
{
    /*-interface passed to driver layer-*/
    w25qxx_timebase_interface_t                   *p_timebase_instance;
    spi_w25q64_interface_t               *p_spi_w25q64_instance;

#ifdef OS_SUPPORT
    /*-Interface from OS layer-*/
    flash_handler_os_interface_t                 *p_os_instance;
    w25qxx_os_delay_interface_t                   *p_os_delay_instance;
#else
    /*-Interface from Device layer-*/
    delay_interface_t                         *p_delay_instance;
#endif//OS_SUPPORT

    /*-Handler instance-*/
    bsp_w25q64_driver_t                      *p_w25q64_instance;

    /*-Handler of event queue-*/
    void                                  *p_event_queue_handle;

    /*-Private data-*/
    flash_handler_private_data_t                *p_private_data;

#ifdef FLASH_DEBUG
    debug_flash_handler_interface_t     *p_debug_flash_instance;
#endif//DEBUG

}bsp_flash_handler_t;
/***********************************Defines **********************************/

/*---------------------------------------------------------------------------*/

/***********************************Declaring ********************************/
/*---------------APIS-------------*/
/**
 * @brief Initialize the flash handler.
 *
 * @param p_flash_handler_instance Pointer to the flash handler instance.
 * @param p_input_arg Pointer to the input arguments for initialization.
 * @return flash_handler_status_t Status of the initialization.
 *            - FLASH_HANDLER_OK（0）: Initialization successful.
 *            - FLASH_HANDLER_ERROR: Initialization failed.
 */
flash_handler_status_t bsp_flash_handler_inst(
        bsp_flash_handler_t           *     const p_flash_handler_instance,
        flash_handler_all_input_arg_t *     const              p_input_arg
                                             );


/**
 * @brief A thread function that handles the flash events.
 * 
 * @note This function continuously checks for flash events 
 * in the event queue and processes them.
 */
void flash_handler_thread(void *argument);

/** 
 * @brief A function that put event input into the FIFO queue.
 * 
 * @param[in] event Pointer to the flash event to be added to the queue.
 */
flash_handler_status_t flash_handler_event_put(
                    const flash_handler_event_t  * const event
                                              );


void metal_event_handler(void);
                                                        
/***********************************Declaring ********************************/


#endif//__EC_BSP_FLASH_HANDLER_H__
