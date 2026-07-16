/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file ec_bsp_spl06_driver.h
 * 
 * @par dependencies 
 * - ec_bsp_spl06_reg.h
 * - stdio.h
 * - stdint.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of spl06 and corresponding opetions.
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

#ifndef __BSP_SPL06_DRIVER_H__
#define __BSP_SPL06_DRIVER_H__

//******************************** Includes *********************************//

#include "bsp_spl06_reg.h"
// #include <stdio.h>
#include <stdint.h>
#include "Debug.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//

/*  函数返回状态枚举                    */
typedef enum
{
  SPL06_OK                = 0,         /* Operation completed successfully.  */
  SPL06_ERROR             = 1,         /* Run-time error without case matched*/
  SPL06_ERRORTIMEOUT      = 2,         /* Operation failed with timeout      */
  SPL06_ERRORRESOURCE     = 3,         /* Resource not available.            */
  SPL06_ERRORPARAMETER    = 4,         /* Parameter error.                   */
  SPL06_ERRORNOMEMORY     = 5,         /* Out of memory.                     */
  SPL06_ERRORISR          = 6,         /* Not allowed in ISR context         */
  SPL06_RESERVED          = 0x7FFFFFFF /* Reserved                           */
} spl06_status_t;

//******************************** Defines **********************************//

//******************************** Declaring ********************************//
#ifndef HARDWARE_IIC     /* True : Hardware IIC */
typedef struct 
{
    spl06_status_t (*pf_iic_init)          (void*);  /*   IIC init    interf.*/
    spl06_status_t (*pf_iic_deinit)        (void*);  /*   IIC deinit  interf.*/
    spl06_status_t (*pf_iic_start)         (void*);  /*   IIC start   interf.*/
    spl06_status_t (*pf_iic_stop)          (void*);  /*   IIC stop    interf.*/
    spl06_status_t (*pf_iic_wait_ack)      (void*);  /*   IIC w-ack   interf.*/
    spl06_status_t (*pf_iic_send_ack)      (void*);  /*   IIC s-ack   interf.*/
    spl06_status_t (*pf_iic_send_no_ack)   (void*);  /*   IIC s-n-ack interf.*/
    spl06_status_t (*pf_iic_send_byte)     (void*,   /*   IIC s-byte  interf.*/
                                            const    uint8_t);
    spl06_status_t (*pf_iic_receive_byte)  (void*,   /*   IIC r-byte  interf.*/
                                            uint8_t * const );  
    spl06_status_t (*pf_critical_enter)     (void);  /* enter critical state.*/
    spl06_status_t (*pf_critical_exit )     (void);  /* exit  critical state.*/
} spl06_iic_driver_interface_t;
#endif /* End of HARDWARE_IIC */

#ifdef HARDWARE_IIC     /* True : Hardware IIC */
typedef struct
{
    spl06_status_t (*pfiic_init)           (void *); /*   IIC init    interf.*/
    spl06_status_t (*pfiic_deinit)         (void *); /*   IIC deinit  interf.*/
    spl06_status_t (*pfiic_send_ack)       (void *); /*   IIC s-ack   interf.*/
    spl06_status_t (*pfiic_send_no_ack)    (void *); /*   IIC s-n-ack interf.*/
    spl06_status_t (*pfiic_send_byte)(void *,        /*   IIC s-byte  interf.*/
                                           uint8_t);
    spl06_status_t (*pfiic_receive_byte)   (void *); /*   IIC r-byte  interf.*/
} spl06_iic_driver_interface_t;
#endif //End of HARDWARE_IIC

/* From OS   Layer：  OS_Delay        */
#ifdef OS_SUPPORTING
typedef struct
{
    void (*pf_rtos_yield)(const uint32_t);          /*OS Not-Blocking Delay  */
}spl06_yield_interface_t;
#endif //End of OS_SUPPORTING

/* spl06_hal_driver instance class    */
typedef struct
{   
    spl06_iic_driver_interface_t       *p_iic_driver_instance;
    spl06_yield_interface_t            *p_yield_instance;

    spl06_status_t (*pf_inst)(
                     void * const      pspl06_instance,
                     spl06_iic_driver_interface_t * const piic_driver_instance,
                     spl06_yield_interface_t * const      pyield_instance);
         
    spl06_status_t (*pf_init)                           (void * const);/*  spl06 init function */
    spl06_status_t (*pf_deinit)                         (void * const);/*spl06 deinit function */
    spl06_status_t (*pf_read_id)                        (void * const,
                                                         uint8_t * const u8_id);/*spl06 read_id function*/
    spl06_status_t (*pf_spl_sleep)                      (void * const);
    spl06_status_t (*pf_spl_wakeup)                     (void * const);
    spl06_status_t (*pf_altitude_calculate)             (void * const,
                                                        float * const pf_altitudedata);/**/
    spl06_status_t (*pf_pressure_calculate)             (void * const,
                                                        float * const pu16_pressuredata);/**/
    spl06_status_t (*pf_temperature_calculate)          (void * const,
                                                        float * const pu16_temperaturedata);/**/
} bsp_spl06_driver_t;

/* spl06_hal_driver instance class Inst. Function        */
spl06_status_t spl06_inst(                                          
                        bsp_spl06_driver_t *               const pspl06_instance,
                        spl06_iic_driver_interface_t *     const piic_driver_instance,
#ifdef OS_SUPPORTING
                        spl06_yield_interface_t *          const pyield_instance);
#endif //End of OS_SUPPORTING); 
    

//******************************** Declaring ********************************//
#endif /* end of __EC_BSP_SPL06_DRIVER_H__ */ 
