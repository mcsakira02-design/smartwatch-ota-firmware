/******************************************************************************
 * Copyright (C) 2024 ssj
 * 
 * All Rights Reserved.
 * 
 * @file ec_bsp_w25q64_driver.h
 * 
 * @par dependencies 
 * - ec_bsp_w25q64_reg.h
 * - stdio.h
 * - stdint.h
 * @author ssj
 * 
 * @brief Provide the HAL APIs of w25q64 and corresponding opetions.
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
#ifndef __BSP_W25Q64_DRIVER_H__
#define __BSP_W25Q64_DRIVER_H__
/**********************************Include ***********************************/
#include "bsp_w25q64_reg.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*---System config header----*/
#include "flash_config.h"

/**********************************Include ***********************************/
/*---------------------------------------------------------------------------*/
/**********************************Defines ***********************************/
/*------Define W25Q64 Status return value------*/
typedef enum
{
    W25Q64_OK = 0,
    W25Q64_ERROR,
    W25Q64_ERROR_TIMEOUT,
    W25Q64_ERROR_RESOURCE,
    W25Q64_ERROR_PARAMETER,
    W25Q64_ERROR_NOMEM,
    W25Q64_BUSY,
    W25Q64_SLEEP,
    W25Q64_WAKEUP,
    W25Q64_ERROR_ISR,
    W25Q64_ERROR_UNKNOWN,
    W25Q64_RESERVED = 0x1FFFFFFF,
}w25q64_status_t;


/**********************************Defines ***********************************/

/*---------------------------------------------------------------------------*/

/**********************************Declaring *********************************/

/*-----------FROM Core Layer SPI PORT-------------*/
#ifndef USE_HARDWARE_SPI            //True -- use software spi.

typedef struct
{
    void        (*pf_spi_init)          (void *);   //spi init interf
    void        (*pf_spi_deinit)        (void *);   //spi deinit interf
    void        (*pf_spi_cs_set)        (void *);   //spi cs set interf
    void        (*pf_spi_cs_deset)      (void *);   //spi cs deset interf
    void        (*pf_spi_write_byte)    (void *);   //spi write byte interf
    void        (*pf_spi_read_byte)     (void *);   //spi read byte interf

    /*-OSSUPPORTING-*/
#ifdef OS_SUPPORT
    void        (*pf_critical_enter)    (void);   //critical enter interf
    void        (*pf_critical_exit)     (void);   //critical exit interf
#endif//OS_SUPPORT

}spi_w25q64_interface_t;

#else

typedef struct
{
    void        (*pf_spi_init)          (void);   //spi init interf
    void        (*pf_spi_deinit)        (void *);   //spi deinit interf
    uint8_t        (*pf_spi_cs_set)        (void);   //spi cs set interf
    uint8_t        (*pf_spi_cs_deset)      (void);   //spi cs deset interf
    uint8_t        (*pf_spi_write_byte)    (uint8_t);   //spi write byte interf
    uint8_t     (*pf_spi_read_byte)     (void);   //spi read byte interf

    /*-OSSUPPORTING-*/
#ifdef OS_SUPPORT
    void        (*pf_critical_enter)    (void);   //critical enter interf
    void        (*pf_critical_exit)     (void);   //critical exit interf
#endif//OS_SUPPORT
}spi_w25q64_interface_t;

#endif//USE_HARDWARE_SPI


/*--------From Core Layer TimeBase Port--------*/

typedef struct
{
    uint32_t   (*pf_tick_count_get)   (void);   //get tick count interf
}w25qxx_timebase_interface_t;


#ifndef OS_SUPPORT
typedef struct
{
    void        (*pf_delay_ms)         (const uint32_t);   //delay ms interf
}delay_interface_t;
#endif//OS_SUPPORT

/*---------From Core Layer OS Port-----------*/

#ifdef OS_SUPPORT
typedef struct
{
    void        (*pf_os_delay_ms)      (const uint32_t);   //delay ms interf
}w25qxx_os_delay_interface_t;
#endif//OS_SUPPORT
/*--------w25q64 driver instance private data class*/
/*------Private data Class-----*/
typedef struct w25q64_private_data                      w25q64_private_data_t;

/*--------w25q64 driver instance class------*/
typedef struct
{
    //--drclaring instance class---
    spi_w25q64_interface_t                            *p_spi_w25q64_instance;
    w25qxx_timebase_interface_t                                *p_timebase_instance;
#ifdef OS_SUPPORT
    w25qxx_os_delay_interface_t                                *p_os_delay_instance;
#else
    delay_interface_t                                      *p_delay_instance;
#endif//OS_SUPPORT
    w25q64_private_data_t                                     *p_private_data;
    
    //---declaring instance function----
    w25q64_status_t (*pf_inst)(
                                    void    *   const       p_w25q64_instance,
                  spi_w25q64_interface_t    *   const   p_spi_w25q64_instance,
                  w25qxx_timebase_interface_t      *   const     p_timebase_instance,

#ifdef OS_SUPPORT
                  w25qxx_os_delay_interface_t      *   const     p_os_delay_instance
#else
                  delay_interface_t         *   const        p_delay_instance
#endif//OS_SUPPORT
                              );

    w25q64_status_t (*pf_init)                              (void * const);
    w25q64_status_t (*pf_deinit)                            (void * const);
    w25q64_status_t (*pf_read_id)          (void * const,uint16_t * const);
    w25q64_status_t (*pf_read)                   (void * const,uint8_t * ,\
                                                      uint32_t ,uint32_t );
    w25q64_status_t (*pf_write_erase)      (void * const,const uint8_t * ,\
                                                      uint32_t ,uint32_t );
    w25q64_status_t (*pf_write_no_erase)   (void * const,const uint8_t * ,\
                                                      uint32_t ,uint32_t );
    w25q64_status_t (*pf_erase_chip)                        (void * const);
    w25q64_status_t (*pf_sleep)                             (void * const);
    w25q64_status_t (*pf_wakeup)                            (void * const);
}bsp_w25q64_driver_t;


/*----------w25q64 instance class funtion declaring port-----------------*/
/**
 * @brief instanct w25q64 driver.
 * 
 * @param p_w25q64_interface     : which w25q54 drive
 * @param p_spi_w25q64_interface : w25q64 hardware SPI interface 
 * @param p_timebase_interface   : hardware timebase interface
 * @param p_os_delay_interface or p_delay_interface
 * @param p_debug_port_interface (if need)
 * 
 * @note  before instanct must make sure
 *        1. spi interface from MCU Core has been loaded.
 *        2. timebase interface from MCU Core has been loaded
 *        3. delay interface(OS or metal) has been loaded
 *        4. debug_port has been loaded if DEBUG is enabled
 * @return w25q64_status_t, 0 is ok, others is error.
 */
w25q64_status_t w25q64_inst(
                bsp_w25q64_driver_t      * const           p_w25q64_instance,
                spi_w25q64_interface_t   * const       p_spi_w25q64_instance,
                w25qxx_timebase_interface_t     * const         p_timebase_instance,
#ifdef OS_SUPPORT
                w25qxx_os_delay_interface_t     * const         p_os_delay_instance
#else
                delay_interface_t        * const            p_delay_instance
#endif//OS_SUPPORT
                           );//instance w25q64 driver

/**
 * @brief API of reading w25q64 id 
 * 
 * @param p_w25q64_instance : which w25q64 instance.
 * @param *p_id:a pointer to store data about id of w25q64
 * 
 * @return w25q64_status_t, 0 is ok, others is error.
 */
w25q64_status_t read_w25qxx_id(
                    bsp_w25q64_driver_t      * const    p_w25q64_instance,
                    uint16_t                 * const                 p_id
                              );

/**
 * @brief API of checking w25q64 sleep status 
 * 
 * @param p_w25q64_instance : which w25q64 instance.
 * @param *p_id:a pointer to store data about sleep status of w25q64
 * 
 * @return w25q64_status_t, 0 is ok, others is error.
 */
w25q64_status_t read_w25qxx_isSleep(
                    bsp_w25q64_driver_t      * const     p_w25q64_instance
                                   );

/**********************************Declaring *********************************/




#endif//__EC_BSP_W25Q64_DRIVER_H__

