/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file ec_bsp_aht21_driver.h
 * 
 * @par dependencies 
 * - ec_bsp_aht21_reg.h
 * - stdio.h
 * - stdint.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of AHT21 and corresponding opetions.
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

#ifndef __BSP_AHT21_DRIVER_H__
#define __BSP_AHT21_DRIVER_H__

//******************************** Includes *********************************//

#include "bsp_aht21_reg.h"

// #include <stdio.h>
#include <stdint.h>

//******************************** Includes *********************************//

//******************************** Defines **********************************//
#define OS_SUPPORTING
//#define HARDWARE_IIC

/*  函数返回状态枚举                    */
typedef enum
{
  AHT21_OK                = 0,         /* Operation completed successfully.  */
  AHT21_ERROR             = 1,         /* Run-time error without case matched*/
  AHT21_ERRORTIMEOUT      = 2,         /* Operation failed with timeout      */
  AHT21_ERRORRESOURCE     = 3,         /* Resource not available.            */
  AHT21_ERRORPARAMETER    = 4,         /* Parameter error.                   */
  AHT21_ERRORNOMEMORY     = 5,         /* Out of memory.                     */
  AHT21_ERRORISR          = 6,         /* Not allowed in ISR context         */
  AHT21_RESERVED          = 0x7FFFFFFF /* Reserved                           */
} aht21_status_t;

//******************************** Defines **********************************//

//******************************** Declaring ********************************//

/* From Core Layer：  IIC Port        */
#ifndef HARDWARE_IIC     /* True : Software IIC */
typedef struct 
{
    aht21_status_t (*pf_iic_init)          (void*);  /*   IIC init    interf.*/
    aht21_status_t (*pf_iic_deinit)        (void*);  /*   IIC deinit  interf.*/
    aht21_status_t (*pf_iic_start)         (void*);  /*   IIC start   interf.*/
    aht21_status_t (*pf_iic_stop)          (void*);  /*   IIC stop    interf.*/
    aht21_status_t (*pf_iic_wait_ack)      (void*);  /*   IIC w-ack   interf.*/
    aht21_status_t (*pf_iic_send_ack)      (void*);  /*   IIC s-ack   interf.*/
    aht21_status_t (*pf_iic_send_no_ack)   (void*);  /*   IIC s-n-ack interf.*/
    aht21_status_t (*pf_iic_send_byte)     (void*,   /*   IIC s-byte  interf.*/
                                            const    uint8_t);
    aht21_status_t (*pf_iic_receive_byte)  (void*,   /*   IIC r-byte  interf.*/
                                            uint8_t * const );  
    aht21_status_t (*pf_critical_enter)     (void);  /* enter critical state.*/
    aht21_status_t (*pf_critical_exit )     (void);  /* exit  critical state.*/
} ahtxx_iic_driver_interface_t;
#endif /* End of HARDWARE_IIC */

#ifdef HARDWARE_IIC     /* True : Hardware IIC */
typedef struct
{
    aht21_status_t (*pfiic_init)           (void *); /*   IIC init    interf.*/
    aht21_status_t (*pfiic_deinit)         (void *); /*   IIC deinit  interf.*/
    aht21_status_t (*pfiic_send_ack)       (void *); /*   IIC s-ack   interf.*/
    aht21_status_t (*pfiic_send_no_ack)    (void *); /*   IIC s-n-ack interf.*/
    aht21_status_t (*pfiic_send_byte)(void *,        /*   IIC s-byte  interf.*/
                                           uint8_t);
    aht21_status_t (*pfiic_receive_byte)   (void *); /*   IIC r-byte  interf.*/
} ahtxx_iic_driver_interface_t;
#endif //End of HARDWARE_IIC

/* From Core Layer：  TimeBase        */
typedef struct
{
    uint32_t (*pf_get_tick_count)(void);            /*Get Tick number interf.*/
} ahtxx_timebase_interface_t;

/* From OS   Layer：  OS_Delay        */
#ifdef OS_SUPPORTING
typedef struct
{
    void (*pf_rtos_yield)(const uint32_t);          /*OS Not-Blocking Delay  */
}ahtxx_yield_interface_t;
#endif //End of OS_SUPPORTING

/* Aht21_hal_driver instance class    */
typedef struct
{
    ahtxx_iic_driver_interface_t *p_iic_driver_instance;
    ahtxx_timebase_interface_t     *p_timebase_instance;
    ahtxx_yield_interface_t           *p_yield_instance;

    aht21_status_t (*pf_inst)(
                                       void * const      paht21_instance,
                     ahtxx_iic_driver_interface_t * const piic_driver_instance,
                     ahtxx_timebase_interface_t   * const   ptimebase_instance,
                          ahtxx_yield_interface_t * const      pyield_instance);
         
    aht21_status_t (*pf_init)         (void * const);/*  AHT21 init function */
    aht21_status_t (*pf_deinit)       (void * const);/*AHT21 deinit function */
    aht21_status_t (*pf_read_id)      (void * const);/*AHT21 read_id function*/
    aht21_status_t (*pf_read_temp_humi)(void * const,/*Read Temp.Humi   func.*/
                                  float * const temp,
                                 float * const humi);
    aht21_status_t (*pf_read_humi)     (void * const,/*Read   Humi.  function*/
                                 float * const humi);
    aht21_status_t (*pf_sleep)        (void * const);/*AHT21  Sleep  function*/
    aht21_status_t (*pf_wakeup)       (void * const);/*AHT21 Wake-up function*/
} bsp_aht21_driver_t;

/* Aht21_hal_driver instance class Inst. Function        */
aht21_status_t aht21_inst(                                          
                        bsp_aht21_driver_t *          const paht21_instance,
                        ahtxx_iic_driver_interface_t * const piic_driver_instance,
#ifdef OS_SUPPORTING
                        ahtxx_yield_interface_t *           const pyield_instance,
#endif //End of OS_SUPPORTING
                        ahtxx_timebase_interface_t *     const ptimebase_instance); 
    

//******************************** Declaring ********************************//


#endif /* end of __EC_BSP_AHT21_DRIVER_H__ */ 
