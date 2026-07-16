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
 
#ifndef __BSP_TEMP_HUMI_XXX_HANDLER_H__  /* Avoid repeated inclusion */
#define __BSP_TEMP_HUMI_XXX_HANDLER_H__


//******************************** Includes *********************************//

#include "bsp_aht21_driver.h"

#include <stdbool.h>
// #include <stdio.h>

//******************************** Includes *********************************//


//******************************** Defines **********************************//

#define AHT21_HANDLER_DEBUG                      /* Is in Debug mode         */

//******************************** Defines **********************************//


//******************************** Typedefs *********************************//

/*   Emulation of return case        */
typedef enum
{
  TEMP_HUMI_OK                = 0,     /* Operation completed successfully.  */
  TEMP_HUMI_ERROR             = 1,     /* Run-time error without case matched*/
  TEMP_HUMI_ERRORTIMEOUT      = 2,     /* Operation failed with timeout      */
  TEMP_HUMI_ERRORRESOURCE     = 3,     /* Resource not available.            */
  TEMP_HUMI_ERRORPARAMETER    = 4,     /* Parameter error.                   */
  TEMP_HUMI_ERRORNOMEMORY     = 5,     /* Out of memory.                     */
  TEMP_HUMI_ERRORISR          = 6,     /* Not allowed in ISR context         */
  TEMP_HUMI_RESERVED  = 0x7FFFFFFF     /* Reserved  May check the caller     */
} temp_humi_status_t;

typedef enum 
{
    TEMP_HUMI_EVENT_TEMP = 0,
    TEMP_HUMI_EVENT_HUMI,
    TEMP_HUMI_EVENT_BOTH
} temp_humi_xxx_event_data_type_t;

/*   Class of Event                  */
typedef struct
{
    float                   *temperature;        /* Temperature Reference    */
    float                      *humidity;        /* Humidity Reference       */
    uint32_t                    lifetime;        /* Lifetime of data         */
    uint32_t                   timestamp;        /* Timestamp of event       */
    temp_humi_xxx_event_data_type_t type;        /* The Data mode            */
    void (*pfcallback)(float *, float *);        /* The callback function    */
} temp_humi_xxx_event_t;

//******************************** Typedefs *********************************//


//**************************** Interface Structs ****************************//

/*   Interface from OS layer         */
typedef struct
{
    void   ( *os_delay_ms    )( uint32_t const ms);    /* Delay Interface    */
    temp_humi_status_t ( *os_queue_create)(            /* Queue_Create Inter.*/
                                uint32_t const item_num,  
                                uint32_t const item_size, 
                                void ** const queue_handle);
                                
    temp_humi_status_t ( *os_queue_put   )(            /* Queue_Send.  Inter.*/
                                void  * const queue_handle, 
                                void * const item, 
                                uint32_t timeout);
    temp_humi_status_t ( *os_queue_get   )( 
                                void *queue_handle,    /* Queue_Recv.  Inter.*/
                                void *msg, 
                                uint32_t timeout);
} temp_humi_handler_os_interface_t;

/*  Input Interface when instantiated */
typedef struct
{
    ahtxx_iic_driver_interface_t   *iic_driver_interface;   /* IIC Driver Instance */
    ahtxx_timebase_interface_t       *timebase_interface;   /* Timebase            */
    temp_humi_handler_os_interface_t *os_interface;   /* OS Interface        */
    ahtxx_yield_interface_t             *yield_interface;   /* CPU Yield Interface */
} temp_humi_handler_all_input_arg_t;

//**************************** Interface Structs ****************************//


//******************************** Classes **********************************//
typedef struct temp_humi_handler_private_data temp_humi_handler_private_data_t;

/*  Handler Class Bsp Handler        */
typedef struct bsp_temp_humi_xxx_handler
{
    /* Interface passed to driver layer */
    ahtxx_timebase_interface_t          *timebase_interface;
    ahtxx_iic_driver_interface_t      *iic_driver_interface;
    ahtxx_yield_interface_t                *yield_interface;
    
    /* Interface from OS layer          */
    temp_humi_handler_os_interface_t    *os_interface;

    /* Instance of driver instance      */
    bsp_aht21_driver_t               *paht21_instance;

    /* Handler of event queue           */
    void                          *event_queue_handle;
    
    /* Private data                     */
    temp_humi_handler_private_data_t  *p_private_data;

    /* Timestamp of last temperature reading */
    uint32_t                     last_temp_tick;

    /* Timestamp of last humidity reading */
    uint32_t                     last_humi_tick;
} bsp_temp_humi_xxx_handler_t;

//******************************** Classes **********************************//


//******************************** APIs *************************************//

/**
 * @brief A thread function that handles the temperature and humidity events.
 *
 * This function continuously checks for temperature and humidity updates and
 * sends them to the event queue. It also updates the last temperature and 
 * humidity.
 */
void temp_humi_handler_thread(void *argument);

/**
 * @brief Initializes the temperature and humidity handler instance.
 *
 * This function takes in a handler instance and input 
 * arguments to initialize the temperature and humidity handler. It sets up the
 * necessary interfaces, creates a queue for handling events, and initializes 
 * the last temperature and humidity timestamps.
 *
 * @param handler_instance A pointer to the temperature and 
 *                         humidity handler instance.
 * @param input_arg        A pointer to the input arguments containing 
 *                         the required interfaces.
 *
 * @return An 8-bit unsigned integer representing the 
 *         status of the initialization.
 *         - 0: Initialization successful.
 *         - Non-zero: Initialization failed.
 */
temp_humi_status_t bsp_temp_humi_xxx_handler_inst(
                        bsp_temp_humi_xxx_handler_t *handler_instance,
                        temp_humi_handler_all_input_arg_t *input_arg);


/**
 * @brief Reads the temperature and humidity from the AHT21 sensor.
 *
 * This function sends an event to the AHT21 to read the temperature and
 * humidity. When the temperature and humidity data is ready, the 
 * callback function or provided pointers for temp. & humi. will be updated.
 * 
 * @param[in] event A pointer to the event made by the caller
 *
 * @return An 8-bit signed integer representing the status of the event passed.
 *         - 0: Successfully queued in the bsp handler.
 *         - Non-zero: Failed to pass.
 */
temp_humi_status_t bsp_temp_humi_xxx_read(temp_humi_xxx_event_t *event);

//******************************** APIs *************************************//


#endif /* __BSP_TEMP_HUMI_XXX_HANDLER_H__ */
