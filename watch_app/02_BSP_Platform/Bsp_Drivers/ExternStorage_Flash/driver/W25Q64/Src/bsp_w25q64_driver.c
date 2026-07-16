/******************************************************************************
 * Copyright (C) 2024 ssj
 * 
 * All Rights Reserved.
 * 
 * @file ec_bsp_w25q64_driver.c
 * 
 * @par dependencies 
 * - ec_bsp_w25q64_reg.h
 * - ec_bsp_w25q64_driver.h
 * 
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

/*******************************Include **************************************/
#include "bsp_w25q64_driver.h"
#include "bsp_w25q64_reg.h"

#include "debug.h"
/*******************************Include **************************************/

//----------------------------------------------------------------------------

/*******************************Define ***************************************/
/*      -----w25q64 Config-----        */
#define     W25Q64_INITED                                      (1U)
#define     W25Q64_UNINITED                                    (0U)


/*      -----Define APIS------         */
#define     W25Q64_ISINITED     (W25Q64_INITED == \
                       (p_w25q64_instance -> p_private_data -> w25q64_inited))

/*******************************Define ***************************************/

//---------------------------------------------------------------------------

/*******************************Variables ***********************************/
typedef struct w25q64_private_data{
    uint8_t             w25q64_inited;
    uint16_t                w25qxx_id;
    w25q64_status_t    w25q64_isSleep;
}w25q64_private_data_t;
/*******************************Variables ***********************************/

//---------------------------------------------------------------------------
/**
 * @brief underlying code of reading w25q64 status.
 * 
 * @note static function only used by w25q64 driver.
 * @param p_w25q64_instance : which w25q64 instance.
 * 
 * @return uint8_t, 0 is ok, others is error.
 */
static uint8_t __read_status(\
                        bsp_w25q64_driver_t * const p_w25q64_instance
                            )
{
    uint8_t status =  0;
    /*----------------SPI Control Read w25q64 status REG------------------*/
#ifdef OS_SUPPORT /*if Define OS need to enter critical*/
    p_w25q64_instance -> p_spi_w25q64_instance ->     pf_critical_enter();
#endif
    p_w25q64_instance -> p_spi_w25q64_instance ->         pf_spi_cs_set();
    p_w25q64_instance -> p_spi_w25q64_instance -> \
                                   pf_spi_write_byte(W25Q64_CMD_READ_REG);

    status = \
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_spi_read_byte();

    p_w25q64_instance -> p_spi_w25q64_instance ->       pf_spi_cs_deset();
#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_critical_exit();
#endif

    /*-----check REG back value-----*/
    if (1 == (status & 0x01))
    {
        return 6;
    }
    else
    {
        return 0;
    }
}


/**
 * @brief underlying code of reading id of w25q64.
 * 
 * @note static function only used by w25q64 driver.
 * 
 * @param p_w25q64_instance : which w25q64 instance.
 * 
 * @return w25q64_status_t , 0 is ok, others is error.
 */
static w25q64_status_t __read_id(\
                            bsp_w25q64_driver_t * const p_w25q64_instance
                                )
{
    uint16_t id = 0;

    /*----------------SPI Control Read w25q64 ID--------------------------*/
#ifdef OS_SUPPORT   /*if OS_SUPPORT need critical enter and exit.*/
    p_w25q64_instance -> p_spi_w25q64_instance ->     pf_critical_enter();
#endif//OS_SUPPORT

    p_w25q64_instance -> p_spi_w25q64_instance ->         pf_spi_cs_set();
    p_w25q64_instance -> p_spi_w25q64_instance -> \
                                    pf_spi_write_byte(W25Q64_CMD_READ_ID);
    /*------Need to send 3 non-byte repalce void addr value---------*/
    p_w25q64_instance -> p_spi_w25q64_instance -> pf_spi_write_byte(0x00);
    p_w25q64_instance -> p_spi_w25q64_instance -> pf_spi_write_byte(0x00);
    p_w25q64_instance -> p_spi_w25q64_instance -> pf_spi_write_byte(0x00);
    /*------W25Q64 ID is 16bit So need read SPI twice--------*/
    id = \
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_spi_read_byte();

    id = id << 8;            //first read high 8bit so need shift left 8bit.

    id |= \
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_spi_read_byte();
    p_w25q64_instance -> p_spi_w25q64_instance ->       pf_spi_cs_deset();

#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_critical_exit();
#endif//OS_SUPPORT
    /*---------------------------------------------------------------------*/
#ifdef DEBUG_FLASH_W25Q64_DRIVER
    DEBUG_OUT("W25Q64 ID IS 0x%x",id);
#endif//DEBUG

    /*-----check ID value-----*/
    if ( 0xEF16 == id)
    {
        p_w25q64_instance -> p_private_data -> w25qxx_id = id;
        return W25Q64_OK;
    }
#ifdef DEBUG_FLASH_W25Q64_DRIVER
    DEBUG_OUT("Read W25Q64 ID failed");
#endif//DEBUG
    return W25Q64_ERROR_RESOURCE;
}

/**
 * @brief init w25q64 driver.
 * 
 * @param p_w25q64_instance : which w25q64 instance.
 * 
 * @return w25q64_status_t, 0 is ok, others is error.
 */
static w25q64_status_t init(\
                    bsp_w25q64_driver_t * const p_w25q64_instance
                           )
{
    w25q64_status_t ret = W25Q64_ERROR_UNKNOWN;
    /*-------1. Check RTOS or metal system delay Port --------*/
#ifdef OS_SUPPORT
    if ( NULL == p_w25q64_instance -> p_os_delay_instance )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("OS Delay Port is NULL!\n");
#endif//DEBUG
        ret = W25Q64_ERROR_RESOURCE;
        return ret;
    }
#else
    if ( NULL == p_w25q64_instance -> p_delay_instance )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("Bare System Delay Port is NULL!");
#endif//DEBUG
        ret = W25Q64_ERROR_RESOURCE;
        return ret;
    }
#endif//OS_SUPPORT

    /*--------------2.check spi port-----------------*/
    if ( NULL == p_w25q64_instance -> p_spi_w25q64_instance   ||
         NULL == p_w25q64_instance -> p_spi_w25q64_instance -> \
                                                     pf_spi_init 
       )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("SPI Port is NULL!");
#endif
        ret = W25Q64_ERROR_RESOURCE;
        return ret;
    }
    /*--------------3.check private data-------------*/
    if ( NULL == p_w25q64_instance -> p_private_data)
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("private data is NULL!!");
#endif
        ret = W25Q64_ERROR_RESOURCE;
        return ret;
    }
    
    /*------------4.init w25q64 hardware layer-------------*/
#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->     pf_critical_enter();
#endif//OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->           pf_spi_init();
    p_w25q64_instance -> p_spi_w25q64_instance ->       pf_spi_cs_deset();

    /*-------------4.check w25q64 id -----------------------*/
    p_w25q64_instance -> pf_wakeup(p_w25q64_instance);
    ret = __read_id( p_w25q64_instance );
    if ( W25Q64_OK!= ret )
    {
        return ret;
    }
    p_w25q64_instance -> p_private_data -> w25q64_inited =  W25Q64_INITED;

#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_critical_exit();
#endif//OS_SUPPORT

    return ret;
}

/**
 * @brief deinit w25q64.
 * 
 * @param p_w25q64_instance : which w25q64 instance.
 * 
 * @return w25q64_status_t, 0 is ok, others is error.
 * 
 */
static w25q64_status_t deinit(\
                        bsp_w25q64_driver_t * const p_w25q64_instance
                             )
{
    /*---------1.check w25q64 is INITED------------*/
    if (! W25Q64_ISINITED )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 is not inited!");
#endif//DEBUG
        return W25Q64_ERROR_RESOURCE;
    }

    /*-----2.check w25q64 spi deinit port-------*/
    if (NULL == p_w25q64_instance -> p_spi_w25q64_instance -> pf_spi_deinit)
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 is not inited!");
#endif//DEBUG
        return W25Q64_ERROR_RESOURCE;
    }

    /*------------------3.Deinit w25q64 ---------------*/
#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->     pf_critical_enter();
#endif//OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->     pf_spi_deinit(NULL);

    /*------------------4.Reset W25Q64 INITED-----*/
    p_w25q64_instance -> p_private_data -> w25q64_inited =  W25Q64_INITED;

#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_critical_exit();
#endif//OS_SUPPORT

    return W25Q64_OK;
}

/**
 * @brief API of Sleeping w25q64
 * 
 * @param p_25q64_instance : which w25q64 instance
 * 
 * @return w25q64_status_t, 0 is ok, others is error.
 */
static w25q64_status_t sleep(
                        bsp_w25q64_driver_t * const p_w25q64_instance
                            )
{
    /*-----------1. Check w25q64 instance isSleep?---------*/
    if (W25Q64_SLEEP == \
        p_w25q64_instance -> p_private_data -> w25q64_isSleep
       )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 is already sleep");
#endif
        return W25Q64_ERROR_RESOURCE;
    }

    /*------------2. Check w25q64 is Busy ? ---------------*/
    uint8_t busy = __read_status(p_w25q64_instance);
    while (busy)
    {
#ifdef OS_SUPPORT
       p_w25q64_instance -> p_os_delay_instance ->     pf_os_delay_ms(50);
#else
       p_w25q64_instance -> p_delay_instance    ->        pf_delay_ms(50);
#endif//OS_SUPPORT
       busy = __read_status(p_w25q64_instance);
    }

    /*------------3. Control SPI hardware to send command----*/
#ifdef OS_SUPPORT   /*if def os need to enter critical*/
    p_w25q64_instance -> p_spi_w25q64_instance ->     pf_critical_enter();
#endif
    p_w25q64_instance -> p_spi_w25q64_instance ->         pf_spi_cs_set();
    p_w25q64_instance -> p_spi_w25q64_instance ->\
                                      pf_spi_write_byte(W25Q64_CMD_SLEEP);
    p_w25q64_instance -> p_spi_w25q64_instance ->       pf_spi_cs_deset();
    p_w25q64_instance -> p_private_data -> w25q64_isSleep =  W25Q64_SLEEP;
#ifdef OS_SUPPORT   
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_critical_exit();
#endif

#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 enter sleep status");
#endif
    return W25Q64_OK;
}

/**
 * @brief API of wakeup w25q64
 * 
 * @param p_25q64_instance : which w25q64 instance
 * 
 * @return w25q64_status_t, 0 is ok, others is error.
 */
static w25q64_status_t wakeup(
                    bsp_w25q64_driver_t * const p_w25q64_instance
                             )
{
    /*-------------1.Check W25Q64 is Sleep ?------*/
    if ( W25Q64_WAKEUP == \
         p_w25q64_instance -> p_private_data -> w25q64_isSleep
       )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 is already wakeup");
#endif
        return W25Q64_ERROR_RESOURCE;
    }

    /*------------2.Control SPI Hardware to send command -----*/
    uint8_t id = \
            ((p_w25q64_instance -> p_private_data -> w25qxx_id) & 0x00FF);
#ifdef OS_SUPPORT   /*if def os need to enter critical*/
    p_w25q64_instance -> p_spi_w25q64_instance ->     pf_critical_enter();
#endif
    p_w25q64_instance -> p_spi_w25q64_instance ->         pf_spi_cs_set();
    p_w25q64_instance -> p_spi_w25q64_instance ->\
                                     pf_spi_write_byte(W25Q64_CMD_WAKEUP);
    p_w25q64_instance -> p_spi_w25q64_instance -> pf_spi_write_byte(0x00);
    p_w25q64_instance -> p_spi_w25q64_instance -> pf_spi_write_byte(0x00);
    p_w25q64_instance -> p_spi_w25q64_instance -> pf_spi_write_byte(0x00);
    p_w25q64_instance -> p_spi_w25q64_instance ->   pf_spi_write_byte(id);
    p_w25q64_instance -> p_spi_w25q64_instance ->       pf_spi_cs_deset();
    p_w25q64_instance -> p_private_data -> w25q64_isSleep = W25Q64_WAKEUP;
#ifdef OS_SUPPORT   /*if def os need to enter critical*/
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_critical_exit();
#endif   

#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 enter wakeup status");
#endif

    return W25Q64_OK;
}

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
                              )
{
    if (! W25Q64_ISINITED )
    {
        return W25Q64_ERROR_RESOURCE;
    }
    *p_id = p_w25q64_instance -> p_private_data -> w25qxx_id;
    return W25Q64_OK;
}

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
                                   )
{
    if (! W25Q64_ISINITED )
    {
        return W25Q64_ERROR_RESOURCE;
    }
    return p_w25q64_instance -> p_private_data -> w25q64_isSleep;
}

/**
 * @brief API of Reading the data at the specified address of w25q64
 * 
 * @param  p_w25q64_instance : which w25q64 instance.
 * @param *p_data    : a pointer to store reading data of w25q64.
 * @param read_addr  : the address of w25q64 to read.
 * @param read_len   : the length of data to read.
 * 
 * @return w25q64_status_t, 0 is ok, others is error.
 */
static w25q64_status_t  read_data(
                    bsp_w25q64_driver_t      * const    p_w25q64_instance,
                    uint8_t                                       *p_data,
                    uint32_t                                    read_addr,
                    uint32_t                                     read_len
                                 )
{
    /*--------------1.Check Param is OK? ------------*/
    if ( NULL == p_data )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 Param is NULL!");
#endif//DEBUG
        return W25Q64_ERROR_PARAMETER;
    }
    /*-------1.1.Check p_data size-----------------*/
    //TBO
    
    /*---------------2.check w25q64 busy ------------*/
    uint8_t busy = __read_status(p_w25q64_instance);
    while (busy)
    {
#ifdef OS_SUPPORT
       p_w25q64_instance -> p_os_delay_instance ->     pf_os_delay_ms(50);
#else
       p_w25q64_instance -> p_delay_instance    ->        pf_delay_ms(50);
#endif//OS_SUPPORT
       busy = __read_status(p_w25q64_instance);
    }

    /*---------------3.check read_addr ------------------*/
    if ( read_addr + read_len > W25Q64_MAX_SIZE )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 read size out of MAXSIZE!!");
#endif//DEBUG
        return W25Q64_ERROR_PARAMETER;
    }

    /*----------4. Control SPI hardware to read data-----------------*/
    /*if have OS need to enter critical to keep the data intact*/
#ifdef OS_SUPPORT 
    p_w25q64_instance -> p_spi_w25q64_instance ->     pf_critical_enter();
#endif//OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->         pf_spi_cs_set();
    p_w25q64_instance -> p_spi_w25q64_instance -> \
                                  pf_spi_write_byte(W25Q64_CMD_READ_DATA);
    p_w25q64_instance -> p_spi_w25q64_instance -> \
                                       pf_spi_write_byte((read_addr>>16));
    p_w25q64_instance -> p_spi_w25q64_instance -> \
                                        pf_spi_write_byte((read_addr>>8));
    p_w25q64_instance -> p_spi_w25q64_instance -> \
                                           pf_spi_write_byte((read_addr));
    while (read_len -- )
    {
        //Dangerous! must make sure the p_data will not be out of range!
        *p_data = p_w25q64_instance -> p_spi_w25q64_instance -> \
                                                       pf_spi_read_byte();
        p_data ++;
    }
    p_w25q64_instance -> p_spi_w25q64_instance ->       pf_spi_cs_deset();
#ifdef OS_SUPPORT 
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_critical_exit();
#endif//OS_SUPPORT
    return W25Q64_OK;
}

/**
 * @brief Internal function of Eraseing the sector at the specified address of w25q64 .
 * 
 * @param p_w25q64_instance : which w25q64 instance.
 * @param sector_addr        : the address of w25q64 to erase.
 * @note  1.Dangrous function.so only use in internal.
 *        2.Sector Addr must be 4KB aligned.  
 *        3.Addr only 24bit is used.
 * @return w25q64_status_t, 0 is ok, others is error.
 */
static w25q64_status_t __sector_erase(
                    bsp_w25q64_driver_t      * const    p_w25q64_instance,
                    uint32_t                                   sector_addr
                                   )
{
    uint8_t busy = 1;
    /*-----1.check sector is not 4KB aligned?? --------*/
    if ((sector_addr & (0x00000FFFU)) != 0)
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("sector addr is Wrong!!");
#endif//DEBUG
        return W25Q64_ERROR_PARAMETER;
    }

    /*------------------2.Erasing---------------------------*/
    /*--------2.1 check drive is busy frist-----------*/
    busy = __read_status(p_w25q64_instance);
    while (busy)
    {
#ifdef OS_SUPPORT
       p_w25q64_instance -> p_os_delay_instance ->     pf_os_delay_ms(50);
#else
       p_w25q64_instance -> p_delay_instance    ->        pf_delay_ms(50);
#endif//OS_SUPPORT
       busy = __read_status(p_w25q64_instance);
    }

    /*-----2.2 Control SPi hardware to make w25q64 write able------*/
    /*if have OS need to enter critical to keep the data intact*/
#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->     pf_critical_enter();
#endif//OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->         pf_spi_cs_set();
    p_w25q64_instance -> p_spi_w25q64_instance -> \
                                pf_spi_write_byte(W25Q64_CMD_WRITEON_REG);
    p_w25q64_instance -> p_spi_w25q64_instance ->       pf_spi_cs_deset();
#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_critical_exit();
#endif//OS_SUPPORT

    /*-----2.3 check drive busy again----------------*/
    busy = __read_status(p_w25q64_instance);
    while (busy)
    {
#ifdef OS_SUPPORT
       p_w25q64_instance -> p_os_delay_instance ->     pf_os_delay_ms(50);
#else
       p_w25q64_instance -> p_delay_instance    ->        pf_delay_ms(50);
#endif//OS_SUPPORT
       busy = __read_status(p_w25q64_instance);
    }

    /*-----2.4 Control SPI Hardware to send Erase Sector command-------*/
    /*if have OS need to enter critical to keep the data intact*/
#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->     pf_critical_enter();
#endif//OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->         pf_spi_cs_set();
    p_w25q64_instance -> p_spi_w25q64_instance -> \
                               pf_spi_write_byte(W25Q64_CMD_ERASE_SECTOR);
    p_w25q64_instance -> p_spi_w25q64_instance -> \
                   pf_spi_write_byte(((sector_addr & (0x00FF0000U))>>16));
    p_w25q64_instance -> p_spi_w25q64_instance -> \
                    pf_spi_write_byte(((sector_addr & (0x0000FF00U))>>8));
    p_w25q64_instance -> p_spi_w25q64_instance -> \
                       pf_spi_write_byte(((sector_addr & (0x000000FFU))));
    p_w25q64_instance -> p_spi_w25q64_instance ->       pf_spi_cs_deset();
#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_critical_exit();
#endif//OS_SUPPORT
    return W25Q64_OK;
}

/**
 * @brief Internal function of Eraseing w25q64 .
 * 
 * @param p_w25q64_instance : which w25q64 instance.
 * @note  1.Dangrous function.
 * 
 * @return w25q64_status_t, 0 is ok, others is error.
 */
static w25q64_status_t chip_erase(
                    bsp_w25q64_driver_t      * const    p_w25q64_instance
                                 )
{
    uint8_t busy = 1;
    /*------------------1.Erasing---------------------------*/
    /*--------1.1 check drive is busy frist-----------*/
    busy = __read_status(p_w25q64_instance);
    while (busy)
    {
#ifdef OS_SUPPORT
       p_w25q64_instance -> p_os_delay_instance ->     pf_os_delay_ms(50);
#else
       p_w25q64_instance -> p_delay_instance    ->        pf_delay_ms(50);
#endif//OS_SUPPORT
       busy = __read_status(p_w25q64_instance);
    }

    /*-----2.2 Control SPi hardware to make w25q64 write able------*/
    /*if have OS need to enter critical to keep the data intact*/
#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->     pf_critical_enter();
#endif//OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->         pf_spi_cs_set();
    p_w25q64_instance -> p_spi_w25q64_instance -> \
                                pf_spi_write_byte(W25Q64_CMD_WRITEON_REG);
    p_w25q64_instance -> p_spi_w25q64_instance ->       pf_spi_cs_deset();
#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_critical_exit();
#endif//OS_SUPPORT

    /*-----2.3 check drive busy again----------------*/
    busy = __read_status(p_w25q64_instance);
    while (busy)
    {
#ifdef OS_SUPPORT
       p_w25q64_instance -> p_os_delay_instance ->     pf_os_delay_ms(50);
#else
       p_w25q64_instance -> p_delay_instance    ->        pf_delay_ms(50);
#endif//OS_SUPPORT
       busy = __read_status(p_w25q64_instance);
    }

    /*-----2.4 Control SPI Hardware to send Erase Sector command-------*/
    /*if have OS need to enter critical to keep the data intact*/
#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->     pf_critical_enter();
#endif//OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->         pf_spi_cs_set();
    p_w25q64_instance -> p_spi_w25q64_instance -> \
                               pf_spi_write_byte(W25Q64_CMD_ERASE_SECTOR);
    p_w25q64_instance -> p_spi_w25q64_instance ->       pf_spi_cs_deset();
#ifdef OS_SUPPORT
    p_w25q64_instance -> p_spi_w25q64_instance ->      pf_critical_exit();
#endif//OS_SUPPORT
    return W25Q64_OK;
}

/**
 * @brief Internal function of writing the data at the specified address of w25q64 .
 * 
 * @param p_w25q64_instance ：which w25q64 instance.
 * @param *p_data            ：a pointer to store writing data of w25q64.
 * @param write_addr         ：the address of w25q64 to write.
 * @param write_len          ：the length of data to write.
 * 
 * @note  1.Dangrous function.so only use in internal.
 *        2.Addr only 24bit is used.
 * 
 * @retval w25q64_status_t, 0 is ok, others is error.
 */
static w25q64_status_t __write(
                    bsp_w25q64_driver_t      * const    p_w25q64_instance,
                    const  uint8_t                                *p_data,
                    uint32_t                                   write_addr,
                    uint32_t                                         size
                              )
{
    /*-----1.check param is ok? ----*/
    if ( NULL == p_data )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 Param is NULL!");
#endif//DEBUG
        return W25Q64_ERROR_PARAMETER;
    }
    /*-------1.1.Check p_data size-----------------*/
    //TBO

    /*-----2.check write_addr ----*/
    if ( write_addr + size > W25Q64_MAX_SIZE )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 write Param is Wrong!!");
#endif//DEBUG
        return W25Q64_ERROR_PARAMETER;
    }
    /*-----3. calculate the page offset------*/
    uint32_t page_offset    = \
                     W25Q64_PAGE_SIZE - ( write_addr % W25Q64_PAGE_SIZE );
    uint32_t page_write_len = page_offset;
    while (1)
    {
        if (size <= page_offset)
        {
            page_offset =        size;
        }
        page_write_len  = page_offset;
        uint8_t busy = __read_status(p_w25q64_instance);
        while (busy)
        {
#ifdef OS_SUPPORT
           p_w25q64_instance -> p_os_delay_instance -> pf_os_delay_ms(50);
#else
           p_w25q64_instance -> p_delay_instance ->       pf_delay_ms(50);
#endif//OS_SUPPORT
           busy = __read_status(p_w25q64_instance);
        }
        /*---------3.2 Control SPI Hardware to send write able command----------*/
        /*if have OS need to enter critical to keep the data intact*/

#ifdef OS_SUPPORT
        p_w25q64_instance -> p_spi_w25q64_instance -> pf_critical_enter();
#endif//OS_SUPPORT

        p_w25q64_instance -> p_spi_w25q64_instance ->     pf_spi_cs_set();
        p_w25q64_instance -> p_spi_w25q64_instance -> \
                                pf_spi_write_byte(W25Q64_CMD_WRITEON_REG);
        p_w25q64_instance -> p_spi_w25q64_instance ->   pf_spi_cs_deset();

#ifdef OS_SUPPORT
        p_w25q64_instance -> p_spi_w25q64_instance ->  pf_critical_exit();
#endif //OS_SUPPORT

        /*------waiting driver callback----------------------------------------*/
        busy = __read_status(p_w25q64_instance);
        while (busy)
        {
#ifdef OS_SUPPORT
           p_w25q64_instance -> p_os_delay_instance -> pf_os_delay_ms(50);
#else
           p_w25q64_instance -> p_delay_instance ->       pf_delay_ms(50);
#endif//OS_SUPPORT
           busy = __read_status(p_w25q64_instance);
        }
        /*------------3.3 Control SPI Hardware to send data-----------*/
        /*if have OS need to enter critical to keep the data intact*/
#ifdef OS_SUPPORT
        p_w25q64_instance -> p_spi_w25q64_instance -> pf_critical_enter();
#endif//OS_SUPPORT
        p_w25q64_instance -> p_spi_w25q64_instance ->     pf_spi_cs_set();
        p_w25q64_instance -> p_spi_w25q64_instance -> \
                                 pf_spi_write_byte(W25Q64_CMD_WRITE_DATA);
        p_w25q64_instance -> p_spi_w25q64_instance -> \
             pf_spi_write_byte( ( ( write_addr & (0x00FF0000U) ) >>16 ) );
        p_w25q64_instance -> p_spi_w25q64_instance -> \
              pf_spi_write_byte( ( ( write_addr & (0x0000FF00U) ) >>8 ) );
        p_w25q64_instance -> p_spi_w25q64_instance -> \
                  pf_spi_write_byte( ( ( write_addr & (0x000000FFU) ) ) );
        while (page_write_len--)
        {
            p_w25q64_instance->p_spi_w25q64_instance->\
                                               pf_spi_write_byte(*p_data);
            p_data ++;
        }
        p_w25q64_instance -> p_spi_w25q64_instance ->   pf_spi_cs_deset();

#ifdef OS_SUPPORT
        p_w25q64_instance -> p_spi_w25q64_instance ->  pf_critical_exit();
#endif//OS_SUPPORT
        /*------3.Check whether all the data has been written completely.--------*/
        if ( page_offset == size ) break;
        write_addr +=      page_offset;
        size       -=      page_offset;
        page_offset = W25Q64_PAGE_SIZE;
    }
    return W25Q64_OK;
}
/**
 * @brief API of writing the data at the specified address of w25q64 .
 * 
 * @param p_w25q64_instance : which w25q64 instance.
 * @param *p_data            : a pointer to store writing data of w25q64.
 * @param write_addr         : the address of w25q64 to write.
 * @param write_len          : the length of data to write.
 * 
 * @retval
 */
static w25q64_status_t  write_data_erase (
                    bsp_w25q64_driver_t      * const   p_w25q64_instance,
                    const uint8_t                                 *p_data,
                    uint32_t                                   write_addr,
                    uint32_t                                         size
                                   )
{
    /*-----1.check param is ok? ----*/
    if ( NULL == p_data )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 Param is NULL!");
#endif//DEBUG
        return W25Q64_ERROR_PARAMETER;
    }
    /*-------1.1.Check p_data size-----------------*/
    //TBO

    /*-----2.check write_addr ----*/
    if ( write_addr + size > W25Q64_MAX_SIZE )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 write Param is Wrong!!");
#endif//DEBUG
        return W25Q64_ERROR_PARAMETER;
    }

    /*-----3. calculate the sector offset ------*/
    uint32_t sector_offset = write_addr               %  W25Q64_SECTOR_SIZE;
    uint32_t sector_remain = W25Q64_SECTOR_SIZE       -       sector_offset;
    uint32_t sector_addr   = write_addr               -       sector_offset;

    
    /*------3.1 Loop write data until all finished ----------------------*/
    while (1)
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 Sector addr = %x!", sector_addr);
#endif//DEBUG
        /*3.2 Check if the remaining sector size is sufficient for writing*/
        if (size <= sector_remain)
        {
            sector_remain = size;
        }
        __sector_erase(p_w25q64_instance, sector_addr);
        //wait complete
#ifdef OS_SUPPORT
        p_w25q64_instance -> p_os_delay_instance ->   pf_os_delay_ms(150);
#else
        p_w25q64_instance -> p_delay_instance    ->      pf_delay_ms(150);
#endif//OS_SUPPORT
        uint8_t status = __read_status(p_w25q64_instance);
        while (status)
        {
#ifdef OS_SUPPORT
            p_w25q64_instance -> p_os_delay_instance -> pf_os_delay_ms(150);
#else
            p_w25q64_instance -> p_delay_instance    ->    pf_delay_ms(150);
#endif//OS_SUPPORT
            status = __read_status(p_w25q64_instance);
        }
        /*-----3.3 use internal function write data------*/
        __write(p_w25q64_instance, p_data, write_addr, sector_remain);
        /*-----3.4Check whether all the data has been written completely.----*/
        if (sector_remain == size) break;
        p_data       +=      sector_remain;
        size         -=      sector_remain;
        write_addr   +=      sector_remain;
        sector_addr   =         write_addr;
        sector_remain = W25Q64_SECTOR_SIZE;
    }
    return W25Q64_OK;
}


/**
 * @brief API of writing the data at the specified address of w25q64 .
 * 
 * @param p_w25q64_instance : which w25q64 instance.
 * @param *p_data            : a pointer to store writing data of w25q64.
 * @param write_addr         : the address of w25q64 to write.
 * @param write_len          : the length of data to write.
 * 
 * @retval
 */
static w25q64_status_t  write_data_noErase (
                    bsp_w25q64_driver_t      * const   p_w25q64_instance,
                    const uint8_t                                 *p_data,
                    uint32_t                                   write_addr,
                    uint32_t                                         size
                                   )
{
    /*-----1.check param is ok? ----*/
    if ( NULL == p_data )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 Param is NULL!");
#endif//DEBUG
        return W25Q64_ERROR_PARAMETER;
    }
    /*-------1.1.Check p_data size-----------------*/
    //TBO

    /*-----2.check write_addr ----*/
    if ( write_addr + size > W25Q64_MAX_SIZE )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 write Param is Wrong!!");
#endif//DEBUG
        return W25Q64_ERROR_PARAMETER;
    }

    /*-----3. calculate the sector offset ------*/
    uint32_t sector_offset = write_addr               %  W25Q64_SECTOR_SIZE;
    uint32_t sector_remain = W25Q64_SECTOR_SIZE       -       sector_offset;
    uint32_t sector_addr   = write_addr               -       sector_offset;

#ifdef DEBUG_FLASH_W25Q64_DRIVER
    DEBUG_OUT("W25Q64 Sector addr = %x!", sector_addr);
#endif//DEBUG
    /*3.1 Check if the remaining sector size is sufficient for writing*/
    if (size > sector_remain)
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 write addr out of a sector");
#endif//DEBUG
        return W25Q64_ERROR_PARAMETER;
    }
    sector_remain = size;
    uint8_t status = __read_status(p_w25q64_instance);
    while (status)
    {
#ifdef OS_SUPPORT
        p_w25q64_instance -> p_os_delay_instance -> pf_os_delay_ms(150);
#else
        p_w25q64_instance -> p_delay_instance    ->    pf_delay_ms(150);
#endif//OS_SUPPORT
        status = __read_status(p_w25q64_instance);
    }
    /*-----3.2 use internal function write data------*/
    __write(p_w25q64_instance, p_data, write_addr, sector_remain);

    return W25Q64_OK;
}


/**
 * @brief instanct w25q64 driver.
 * 
 * @param p_w25q64_instance     : which w25q54 drive instance
 * @param p_spi_w25q64_instance : w25q64 hardware SPI instance 
 * @param p_timebase_instance   : hardware timebase instance
 * @param p_os_delay_instance or p_delay_instance
 * @param p_debug_port_instance (if need)
 * 
 * @note  before instanct must make sure
 *        1. spi instance from MCU Core has been instance.
 *        2. timebase instance from MCU Core has been instance
 *        3. delay instance(OS or metal) has been instance
 *        4. debug_port has been instance if DEBUG is enabled
 * @return w25q64_status_t, 0 is ok, others is error.
 */
w25q64_status_t w25q64_inst(
                bsp_w25q64_driver_t      * const           p_w25q64_instance,
                spi_w25q64_interface_t   * const       p_spi_w25q64_instance,
                w25qxx_timebase_interface_t     * const         p_timebase_instance,
// #ifdef DEBUG_FLASH_W25Q64_DRIVER
//                 debug_w25q64_interface_t * const     p_debug_w25q64_instance,
// #endif

#ifdef OS_SUPPORT
                w25qxx_os_delay_interface_t     * const          p_os_delay_instance
#else 
                delay_interface_t        * const             p_delay_instance
#endif//OS_SUPPORT
                            )
{
    w25q64_status_t ret = W25Q64_ERROR_UNKNOWN;
#ifdef DEBUG_FLASH_W25Q64_DRIVER
    /*-----0.if def DEBUG need mount fisrt------*/
    // if ( NULL == p_debug_w25q64_instance)
    // {
    //     ret = W25Q64_ERROR_PARAMETER;
    //     return ret;
    // }
    
    // p_w25q64_instance -> p_debug_w25q64_instance = p_debug_w25q64_instance;

    DEBUG_OUT("W25Q64 Debug port mount success!");
#endif//DEBUG
    /*-----1. Mount private data of w25q64--------*/
    w25q64_private_data_t *p_private_data      =                      NULL;
    p_private_data = \
            (w25q64_private_data_t *)malloc(sizeof(w25q64_private_data_t));
    if (NULL == p_private_data)
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("private data space malloc error");
#endif//DEBUG
        ret = W25Q64_ERROR_NOMEM;
        return ret;
    }
    memset(p_private_data,0,sizeof(w25q64_private_data_t));

    p_w25q64_instance -> p_private_data =                   p_private_data;


    /*----2.Check W25Q64 is init ?? ---------*/
    if ( W25Q64_ISINITED )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 is already inited!");
#endif//DEBUG
        ret = W25Q64_ERROR_RESOURCE;
        return ret;
    }
    /*-----2.Check Param is OK ?? ------*/
    if ( NULL == p_w25q64_instance         ||
         NULL == p_spi_w25q64_instance     ||
         NULL == p_timebase_instance       
       )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 Param is NULL!"); 
#endif//DEBUG
        ret = W25Q64_ERROR_PARAMETER;
        return ret;
    }
    /*----3.Check RTOS or bare - system delay Port*/
#ifdef OS_SUPPORT
    if ( NULL == p_os_delay_instance )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("OS Delay Port is NULL!");
#endif//DEBUG
        ret = W25Q64_ERROR_PARAMETER;
        return ret;
    }
#else
    if ( NULL == p_delay_instance )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("Bare System Delay Port is NULL!");
#endif//DEBUG
        ret = W25Q64_ERROR_PARAMETER;
        return ret;
    }
#endif//OS_SUPPORT

    /*----3. Mount external port ----*/
    p_w25q64_instance -> p_spi_w25q64_instance =     p_spi_w25q64_instance;
    p_w25q64_instance -> p_timebase_instance   =       p_timebase_instance;

#ifdef OS_SUPPORT
    p_w25q64_instance -> p_os_delay_instance   =       p_os_delay_instance;
#else
    p_w25q64_instance -> p_delay_instance      =          p_delay_instance;
#endif//OS_SUPPORT
    
    /*-----4. Mount internal function port ------*/
    p_w25q64_instance -> pf_init        = (w25q64_status_t(*)(void * const))\
                                                                        init;
    p_w25q64_instance -> pf_deinit      = (w25q64_status_t(*)(void * const))\
                                                                      deinit;
    p_w25q64_instance -> pf_read        = (w25q64_status_t(*)\
                    (void * const ,uint8_t * ,uint32_t ,uint32_t ))read_data;
    p_w25q64_instance -> pf_write_erase = (w25q64_status_t(*)\
       (void * const ,const uint8_t * ,uint32_t ,uint32_t ))write_data_erase;
    p_w25q64_instance -> pf_write_no_erase = (w25q64_status_t(*)\
     (void * const ,const uint8_t * ,uint32_t ,uint32_t ))write_data_noErase;
    p_w25q64_instance -> pf_sleep       = (w25q64_status_t(*)\
                                                        (void * const))sleep;
    p_w25q64_instance -> pf_wakeup      = (w25q64_status_t(*)\
                                                       (void * const))wakeup;
    p_w25q64_instance -> pf_erase_chip  = (w25q64_status_t(*)\
                                                   (void * const))chip_erase;
    //TBO

    /*-----5. Init W25Q64 --------*/
    ret = p_w25q64_instance -> pf_init(p_w25q64_instance);
    if ( W25Q64_OK == ret )
    {
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 init Success!");
#endif//DEBUG
    }
    else
    {
        free(p_private_data);
#ifdef DEBUG_FLASH_W25Q64_DRIVER
        DEBUG_OUT("W25Q64 init Fail!");
#endif//DEBUG
    }
    return ret;
}

