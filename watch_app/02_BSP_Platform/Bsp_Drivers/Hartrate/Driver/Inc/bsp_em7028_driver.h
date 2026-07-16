/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file ec_bsp_em7028_driver.h
 * 
 * @par dependencies 
 * - ec_bsp_em7028_reg.h
 * - stdio.h
 * - stdint.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of em7028 and corresponding opetions.
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

#ifndef __BSP_EM7028_DRIVER_H__
#define __BSP_EM7028_DRIVER_H__

//******************************** Includes *********************************//

#include "bsp_em7028_reg.h"
// #include <stdio.h>
#include <stdint.h>
#include "Debug.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//

/*  函数返回状态枚举                    */
typedef enum
{
  EM7028_OK                = 0,         /* Operation completed successfully.  */
  EM7028_ERROR             = 1,         /* Run-time error without case matched*/
  EM7028_ERRORTIMEOUT      = 2,         /* Operation failed with timeout      */
  EM7028_ERRORRESOURCE     = 3,         /* Resource not available.            */
  EM7028_ERRORPARAMETER    = 4,         /* Parameter error.                   */
  EM7028_ERRORNOMEMORY     = 5,         /* Out of memory.                     */
  EM7028_ERRORISR          = 6,         /* Not allowed in ISR context         */
  EM7028_RESERVED          = 0x7FFFFFFF /* Reserved                           */
} em7028_status_t;

//******************************** Defines **********************************//

//******************************** Declaring ********************************//
#ifndef HARDWARE_IIC     /* True : Hardware IIC */
typedef struct 
{
    em7028_status_t (*pf_iic_init)          (void*);  /*   IIC init    interf.*/
    em7028_status_t (*pf_iic_deinit)        (void*);  /*   IIC deinit  interf.*/
    em7028_status_t (*pf_iic_start)         (void*);  /*   IIC start   interf.*/
    em7028_status_t (*pf_iic_stop)          (void*);  /*   IIC stop    interf.*/
    em7028_status_t (*pf_iic_wait_ack)      (void*);  /*   IIC w-ack   interf.*/
    em7028_status_t (*pf_iic_send_ack)      (void*);  /*   IIC s-ack   interf.*/
    em7028_status_t (*pf_iic_send_no_ack)   (void*);  /*   IIC s-n-ack interf.*/
    em7028_status_t (*pf_iic_send_byte)     (void*,   /*   IIC s-byte  interf.*/
                                            const    uint8_t);
    em7028_status_t (*pf_iic_receive_byte)  (void*,   /*   IIC r-byte  interf.*/
                                            uint8_t * const );  
    em7028_status_t (*pf_critical_enter)     (void);  /* enter critical state.*/
    em7028_status_t (*pf_critical_exit )     (void);  /* exit  critical state.*/
} em7028_iic_driver_interface_t;
#endif /* End of HARDWARE_IIC */

#ifdef HARDWARE_IIC     /* True : Hardware IIC */
typedef struct
{
    em7028_status_t (*pfiic_init)           (void *); /*   IIC init    interf.*/
    em7028_status_t (*pfiic_deinit)         (void *); /*   IIC deinit  interf.*/
    em7028_status_t (*pfiic_send_ack)       (void *); /*   IIC s-ack   interf.*/
    em7028_status_t (*pfiic_send_no_ack)    (void *); /*   IIC s-n-ack interf.*/
    em7028_status_t (*pfiic_send_byte)(void *,        /*   IIC s-byte  interf.*/
                                           uint8_t);
    em7028_status_t (*pfiic_receive_byte)   (void *); /*   IIC r-byte  interf.*/
} em7028_iic_driver_interface_t;
#endif //End of HARDWARE_IIC

/* From OS   Layer：  OS_Delay        */
#ifdef OS_SUPPORTING
typedef struct
{
    void (*pf_rtos_yield)(const uint32_t);          /*OS Not-Blocking Delay  */
}em7028_yield_interface_t;
#endif //End of OS_SUPPORTING

/* em7028_hal_driver instance class    */
typedef struct
{   
    em7028_iic_driver_interface_t       *p_iic_driver_instance;
    em7028_yield_interface_t            *p_yield_instance;

    em7028_status_t (*pf_inst)(
                     void * const      pem7028_instance,
                     em7028_iic_driver_interface_t * const piic_driver_instance,
                     em7028_yield_interface_t * const      pyield_instance);
         
    em7028_status_t (*pf_init)              (void * const);/*  em7028 init function */
    em7028_status_t (*pf_deinit)            (void * const);/*em7028 deinit function */
    em7028_status_t (*pf_read_id)           (void * const,
                                            uint8_t * const u8_id);/*em7028 read_id function*/
    em7028_status_t (*pf_hrs_enable)        (void * const);
    em7028_status_t (*pf_hrs_disable)       (void * const);
    em7028_status_t (*pf_read_hrs)          (void * const,
                                            uint16_t * const u16_hartdata);/**/
} bsp_em7028_driver_t;

/* em7028_hal_driver instance class Inst. Function        */
em7028_status_t em7028_inst(                                          
                        bsp_em7028_driver_t *               const pem7028_instance,
                        em7028_iic_driver_interface_t *     const piic_driver_instance,
#ifdef OS_SUPPORTING
                        em7028_yield_interface_t *          const pyield_instance);
#endif //End of OS_SUPPORTING); 
    

//******************************** Declaring ********************************//
#endif /* end of __EC_BSP_EM7028_DRIVER_H__ */ 
