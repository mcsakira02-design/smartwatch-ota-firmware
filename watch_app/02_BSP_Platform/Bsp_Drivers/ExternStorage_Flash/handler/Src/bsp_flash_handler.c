/******************************************************************************
 * Copyright (C) 2024 ssj
 * 
 * All Rights Reserved.
 * 
 * @file ec_bsp_flash_handler.c
 * 
 * @par dependencies 
 * - ec_bsp_flash_handler.h
 * - stdio.h
 * - stdint.h
 * 
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

/*******************************Include **************************************/
#include "bsp_flash_handler.h"
// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Debug.h"
//#pragma O0
/*******************************Include **************************************/

/*---------------------------------------------------------------------------*/

/*******************************Defines **************************************/
/*-----handler Macro Definition ------------*/
#define FLASH_HANDLER_NOT_INITIATED             (0U)
#define FLASH_HANDLER_INITIATED                 (1U)

#define MAX_DELAY_MS                   (0xffffffffUL)
#define WAITTOSLEEP                          (5000UL)

#define OS_QUEUE_CREATE                 \
                (p_instance->p_os_instance->pf_os_queue_create)
/*******************************Defines **************************************/

/*---------------------------------------------------------------------------*/

/*******************************Variables ************************************/
/*Flag to indicate if the handler has been initialized*/
/**
 * @note if you  have more flash and need more handler instance to control
 *       you need to change this to handler_instance private data
 */
static bsp_flash_handler_t *gp_flash_handler_instance =      NULL;

#ifndef OS_SUPPORT
static flash_metal_queue_t *gp_flash_metal_queue      =      NULL;
#endif//OS_SUPPORT


//private data structure to mange handler state
typedef struct flash_handler_private_data
{
    uint8_t           is_initated;
    uint32_t    last_handler_time;
}flash_handler_private_data_t;
/*******************************Variables ************************************/

/*---------------------------------------------------------------------------*/

/*******************************Function *************************************/
/**
 * @brief mount the handler instance globally for use in other functions
 * 
 * @param[in] instance Pointer to the handler instance to mount
 */
static void __mount_handler(bsp_flash_handler_t *p_instance)
{
    gp_flash_handler_instance = p_instance;
}

static flash_handler_status_t bsp_flash_handler_init(\
                                            bsp_flash_handler_t *p_instance
                                                    )
{
#ifdef DEBUG_FLASH_W25Q64_HANDLER
    DEBUG_OUT("handler init start.");
#endif

    int8_t ret = 0;
#ifdef OS_SUPPORT
    //Create event queue
    if ( NULL == OS_QUEUE_CREATE )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("queue create function is NULL!!.");
#endif
        return FLASH_HANDLER_ERROR_RESOURCE;
    }
    
    ret = OS_QUEUE_CREATE(10,sizeof(flash_handler_event_t),\
                                     &(p_instance -> p_event_queue_handle) 
                         );

#ifdef DEBUG_FLASH_W25Q64_HANDLER
    DEBUG_OUT("queue create ret = %d.",ret);
#endif
    if ( 0!= ret )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("queue create failed.");
#endif
        return FLASH_HANDLER_ERROR_RESOURCE;
    }
#else

    //Create A FIFO QUEUE FOR NOT OS
    gp_flash_metal_queue = (flash_metal_queue_t *)\
                                     malloc( sizeof(flash_metal_queue_t) );
    if ( NULL == gp_flash_metal_queue)
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("queue create failed.");
#endif
        return FLASH_HANDLER_ERROR_RESOURCE;
    }
    else
    {
        memset( gp_flash_metal_queue , 0 , sizeof(flash_metal_queue_t) );
        //reset FIFO queue
    }
#endif

    //construct W25QXX instance
    ret = w25q64_inst(p_instance -> p_w25q64_instance, \
                      p_instance -> p_spi_w25q64_instance,\
                      p_instance -> p_timebase_instance,
#ifdef OS_SUPPORT
                      p_instance -> p_os_delay_instance
#else
                      p_instance -> p_delay_instance
#endif//OS_SUPPORT
                     );
#ifdef DEBUG_FLASH_W25Q64_HANDLER
    DEBUG_OUT("w25q64 instance init ret = %d.",ret);
#endif
    if ( 0!= ret )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("w25q64 instance init failed.");
#endif
        return FLASH_HANDLER_ERROR_RESOURCE;
    }

#ifdef DEBUG_FLASH_W25Q64_HANDLER
    DEBUG_OUT("handler init done.");
#endif
    return FLASH_HANDLER_OK;
}

/**
 * @brief De-Initialize the flash handler.
 * 
 * @return flash_handler_status_t
 */

static flash_handler_status_t bsp_flash_handler_deinit(void)
{
    gp_flash_handler_instance -> p_private_data -> is_initated = \
                                               FLASH_HANDLER_NOT_INITIATED;
    return FLASH_HANDLER_OK;
}

/**
 * @brief Instantiate the flash handler.
 * 
 * @param[in] instance Pointer to the flash handler instance.
 * @param[in] input_arg Pointer to the input arguments for the handler.
 * 
 * @retval FLASH_HANDLER_OK if the handler is successfully instantiated.
 * @retval FLASH_HANDLER_ERROR_RESOURCE if the handler fails to instantiate.
 */
flash_handler_status_t bsp_flash_handler_inst(
                  bsp_flash_handler_t           * p_flash_handler_instance,
                  flash_handler_all_input_arg_t *                 input_arg
                                             )
{
    flash_handler_status_t ret = FLASH_HANDLER_ERROR_UNKNOWN;
#ifdef DEBUG_FLASH_W25Q64_HANDLER
    DEBUG_OUT("handler inst start.");
#endif

    /*-------1.Checkout the param -------*/
    if ( NULL == p_flash_handler_instance )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("flash handler instance is NULL!!.");
#endif
        return FLASH_HANDLER_ERROR_PARAMETER;
    }

    if ( NULL == input_arg )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("input arg is NULL!!.");
#endif
        return FLASH_HANDLER_ERROR_PARAMETER;
    }

    /*-------2.Checkout the input_arg is OK ???------*/
    if ( NULL == input_arg -> p_timebase_instance )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("timebase interface is NULL!!.");
#endif
        return FLASH_HANDLER_ERROR_PARAMETER;
    }

    if ( NULL == input_arg -> p_spi_w25q64_instance )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("spi w25q64 interface is NULL!!.");
#endif
        return FLASH_HANDLER_ERROR_PARAMETER;
    }

#ifdef OS_SUPPORT
    if ( NULL == input_arg -> p_os_instance ||
         NULL == input_arg -> p_os_delay_instance
       )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("os interface is NULL!!.");
#endif
    }
#else
    if ( NULL == input_arg -> p_delay_instance )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("delay is NULL!!.");
#endif//DEBUG        
    }
#endif//OS_SUPPORT

    /*------3.Malloc private data space---------*/
    flash_handler_private_data_t *p_private_data = NULL;
    p_private_data = (flash_handler_private_data_t *)\
                              malloc(sizeof(flash_handler_private_data_t));
    p_flash_handler_instance -> p_private_data =            p_private_data;
    /*------4.Mounting input interface to handler instance---*/
    p_flash_handler_instance -> p_spi_w25q64_instance = \
                                        input_arg -> p_spi_w25q64_instance;
    p_flash_handler_instance -> p_timebase_instance  = \
                                          input_arg -> p_timebase_instance;
#ifdef OS_SUPPORT
    p_flash_handler_instance -> p_os_instance       = \
                                                input_arg -> p_os_instance;
    p_flash_handler_instance -> p_os_delay_instance = \
                                           input_arg ->p_os_delay_instance;
#else
    p_flash_handler_instance -> p_delay_instance     = \
                                             input_arg -> p_delay_instance;
#endif//OS_SUPPORT
    
    /*-----4.Initialize the handler--------*/
    ret = bsp_flash_handler_init( p_flash_handler_instance );
    if ( FLASH_HANDLER_OK!= ret )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("handler init failed.");
#endif
        return FLASH_HANDLER_ERROR_RESOURCE;
    }

    p_flash_handler_instance -> p_private_data -> is_initated = \
                                                   FLASH_HANDLER_INITIATED;
#ifdef DEBUG_FLASH_W25Q64_HANDLER
    DEBUG_OUT("handler inst done.");
#endif
    return FLASH_HANDLER_OK;
}

/**
 * @brief flash event handler function.
 * 
 * @param[in] event Pointer to the flash event.
 * 
 */
flash_handler_status_t flash_event_handle(  
             const bsp_flash_handler_t    * const p_flash_handler_instance,
             const flash_handler_event_t  * const                   event
                                         )
{
    w25q64_status_t         ret         =                        W25Q64_OK;
    flash_handler_status_t  status      =      FLASH_HANDLER_ERROR_UNKNOWN;
    /*------1.Checkout the event------*/
    if ( NULL == event )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("event is NULL!!.");
#endif
        return FLASH_HANDLER_ERROR_PARAMETER;
    }

    /*------1.1.Checkout w25q64 state-------*/
    if ( (W25Q64_SLEEP == \
         read_w25qxx_isSleep(p_flash_handler_instance -> p_w25q64_instance))\
         && ( FLASH_HANDLER_EVENT_SLEEP != event -> type )
       )
    {
        p_flash_handler_instance -> p_w25q64_instance -> \
                  pf_wakeup(p_flash_handler_instance -> p_w25q64_instance);
    }
    
    /*------2.event state machine------*/
    switch ( event -> type )
    {
        case FLASH_HANDLER_EVENT_READ:
        {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
            DEBUG_OUT("read event.");
            DEBUG_OUT("p_data = %x.!addr = %x!size = %d",\
                                  event->p_data,event->addr,event->size);
#endif
            ret = p_flash_handler_instance -> p_w25q64_instance -> \
                    pf_read(p_flash_handler_instance -> p_w25q64_instance,
                                               event ->            p_data,
                                               event ->              addr,
                                               event ->              size
                            );

            break;
        }

        case FLASH_HANDLER_EVENT_WRITE:
        {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
            DEBUG_OUT("write event.");
            DEBUG_OUT("p_data = %x.!addr = %x!size = %d",\
                                    event->p_data,event->addr,event->size);
#endif
            ret = p_flash_handler_instance -> p_w25q64_instance -> \
              pf_write_erase(p_flash_handler_instance -> p_w25q64_instance,
                                                event ->            p_data,
                                                event ->              addr,
                                                event ->              size
                            );
            break;
        }
        case FLASH_HANDLER_EVENT_WRITE_NOERASE:
        {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
            DEBUG_OUT("write event.");
            DEBUG_OUT("p_data = %x.!addr = %x!size = %d",\
                                    event->p_data,event->addr,event->size);
#endif
            ret = p_flash_handler_instance -> p_w25q64_instance -> \
           pf_write_no_erase(p_flash_handler_instance -> p_w25q64_instance,
                                                event ->            p_data,
                                                event ->              addr,
                                                event ->              size
                            );
            break;
        }
        case FLASH_HANDLER_EVENT_ERASE_CHIP:
        {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
            DEBUG_OUT("chip erase event.");
#endif
            ret = p_flash_handler_instance -> p_w25q64_instance -> \
               pf_erase_chip(p_flash_handler_instance -> p_w25q64_instance);
            break;
        }

        case FLASH_HANDLER_EVENT_SLEEP:
        {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
            DEBUG_OUT("sleep event.");
#endif
            ret = p_flash_handler_instance -> p_w25q64_instance -> \
                    pf_sleep(p_flash_handler_instance -> p_w25q64_instance);
            break;
        }

        default:
        {
            break;
        }
    }

    if (ret == W25Q64_OK)
    {
        status = FLASH_HANDLER_OK;
    }
    else
    {
        status = FLASH_HANDLER_ERROR_RESOURCE;
    }

    if (FLASH_HANDLER_OK != status)
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("Event Handler fail,ret:%d",status); 
#endif
    }

    return status;
}
/** 
 * @brief A function that put event input into the FIFO queue.
 * 
 * @param[in] event Pointer to the flash event to be added to the queue.
 */
flash_handler_status_t flash_handler_event_put(
                    const flash_handler_event_t  * const event
                                              )
{
    /*------0.Checkout gp_flash_handler_instance is mount---*/
    if ( NULL == gp_flash_handler_instance)
    {
        return FLASH_HANDLER_ERROR_NOTINIT;
    }
    if (FLASH_HANDLER_EVENT_TEST == event -> type)
    {
        return FLASH_HANDLER_OK;
    }
    
    /*------1.Checkout the handler is initialized------*/
    if ( FLASH_HANDLER_NOT_INITIATED == \
        gp_flash_handler_instance -> p_private_data -> is_initated )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("handler is not initialized.");
#endif
        return FLASH_HANDLER_ERROR_RESOURCE;
    }

    /*-------2.Queue the event for processing ----------*/
#ifdef OS_SUPPORT
#ifdef DEBUG_FLASH_W25Q64_HANDLER
    DEBUG_OUT("queue_handle : [%x],event_addr:[%x]",\
        gp_flash_handler_instance -> p_event_queue_handle,event);
#endif//DEBUG

    flash_handler_status_t status = FLASH_HANDLER_ERROR_UNKNOWN;
    status = gp_flash_handler_instance -> p_os_instance -> \
        pf_os_queue_send(
            gp_flash_handler_instance -> p_event_queue_handle,
                                               (void * )event,
                                                 MAX_DELAY_MS
                        );
    if (status)
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("event put failed.");
#endif//DEBUG
        return FLASH_HANDLER_ERROR_RESOURCE;
    }
#else
    gp_flash_metal_queue -> event[ gp_flash_metal_queue -> write ] = *event;
    if ( (gp_flash_metal_queue -> write) >= (FLASH_METAL_QUEUE_MAX - 1) )
    {
        gp_flash_metal_queue -> write = 0;
    }
    else
    {
        gp_flash_metal_queue -> write++;
    }
    return FLASH_HANDLER_OK;
#endif
    return status;
}

/**
 * @brief A thread function that handles the flash events.
 * 
 * @note This function continuously checks for flash events 
 * in the event queue and processes them.
 */
void flash_handler_thread(void *argument)
{
    flash_handler_all_input_arg_t *input_arg  =                        NULL;
    flash_handler_status_t          status    = FLASH_HANDLER_ERROR_UNKNOWN;


#ifdef OS_SUPPORT
    //W25Q64 driver instance.
    bsp_w25q64_driver_t                                   bsp_w25q64_driver;
    //flash handler instance.
    bsp_flash_handler_t                              flash_handler_instance;
#else
    //W25Q64 driver instance.
    static bsp_w25q64_driver_t                            bsp_w25q64_driver;
    //flash handler instance.
    static bsp_flash_handler_t                       flash_handler_instance;
#endif
    if ( NULL == argument )
    {
        return;
    }
    input_arg =                   (flash_handler_all_input_arg_t *)argument;

#ifdef DEBUG_FLASH_W25Q64_HANDLER
//    flash_handler_instance.p_debug_flash_instance = \
//                                        input_arg -> p_debug_flash_instance;
    DEBUG_OUT("Debug port is mounted.");
#endif//DEBUG

#ifdef OS_SUPPORT
    /*if def OS need to enter critical to ensure inst complete*/
    /*--check os interface---*/
    if ( NULL == input_arg -> p_spi_w25q64_instance -> pf_critical_enter ||
         NULL == input_arg -> p_spi_w25q64_instance -> pf_critical_exit 
       )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("critical control port is NULL!!");
#endif
        return;
    }
    input_arg -> p_spi_w25q64_instance -> pf_critical_enter();
#endif    
    //instance w25q64 driver.
    flash_handler_instance.p_w25q64_instance =           &bsp_w25q64_driver;
    status    =    bsp_flash_handler_inst(
                                                    &flash_handler_instance,
                                                                  input_arg
                                         );

    if ( FLASH_HANDLER_OK ==  status )
    {
        __mount_handler( &flash_handler_instance );
    }
#ifdef OS_SUPPORT
    input_arg -> p_spi_w25q64_instance -> pf_critical_exit();
    flash_handler_event_t                                             event;
    for (;;)
    {
        status = flash_handler_instance.p_os_instance -> \
            pf_os_queue_receive(
                flash_handler_instance.p_event_queue_handle,
                &event,
                MAX_DELAY_MS
                               );
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("get handler = [%x].",flash_handler_instance.p_event_queue_handle);
#endif
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("get ret = %d.",status);
#endif
        // if ( 0 != status )
        // {
        //     if (W25Q64_WAKEUP == read_w25qxx_isSleep (&bsp_w25q64_driver) )
        //     {
        //         bsp_w25q64_driver.pf_sleep(&bsp_w25q64_driver);
        //     }
        //     continue;
        // }
        
        if (FLASH_HANDLER_OK == \
            flash_event_handle(&flash_handler_instance ,&event)
           )
        {
            if (NULL == event.pf_callback)
            {
                continue;
            }
            event.pf_callback(event.p_data);
        }
        else
        {
            //TBO....
        }
    }
#else
   //metal_system can start timeer to let handler Start at regular intervals
    
#endif//OS_SUPPORT
}

#ifndef OS_SUPPORT
void metal_event_handler(void)
{
    if ( gp_flash_metal_queue == NULL )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("Not metal queue");
#endif
        return;
    }
    if ( gp_flash_handler_instance == NULL )
    {
#ifdef DEBUG_FLASH_W25Q64_HANDLER
        DEBUG_OUT("Not handler instance queue");
#endif
        return;
    }
    
    while ( (gp_flash_metal_queue -> read) != \
            (gp_flash_metal_queue -> write)
          )
    {
        flash_handler_status_t ret = FLASH_HANDLER_OK;
        ret = flash_event_handle( gp_flash_handler_instance,\
        &(gp_flash_metal_queue -> event[ gp_flash_metal_queue -> read ]));
        if ( (NULL != \
             (gp_flash_metal_queue -> \
                event[gp_flash_metal_queue -> read].pf_callback)
             ) &&
            (FLASH_HANDLER_OK == ret)
           )
        {                
            gp_flash_metal_queue -> \
                event[gp_flash_metal_queue -> read].\
                    pf_callback(gp_flash_metal_queue -> \
                        event[gp_flash_metal_queue -> read].p_data
                               );
        }
        if (gp_flash_metal_queue -> read >= FLASH_METAL_QUEUE_MAX - 1)
        {
            gp_flash_metal_queue -> read = 0;
        }
        else
        {
            gp_flash_metal_queue -> read ++;
        }
        gp_flash_handler_instance -> p_private_data -> last_handler_time = \
        gp_flash_handler_instance -> p_timebase_instance -> pf_tick_count_get();
    }
    uint32_t time_sub = (gp_flash_handler_instance -> p_timebase_instance -> \
                            pf_tick_count_get()
                        )   
                        -
                        (gp_flash_handler_instance -> p_private_data -> \
                            last_handler_time
                        );
    if ( 
         (time_sub >= WAITTOSLEEP) &&
         (W25Q64_WAKEUP == \
            read_w25qxx_isSleep(gp_flash_handler_instance -> p_w25q64_instance)
         )
       )
    {
        gp_flash_handler_instance -> p_w25q64_instance -> \
                    pf_sleep(gp_flash_handler_instance -> p_w25q64_instance);
    }
    

    return;
}

#endif//OS_SUPPORT
