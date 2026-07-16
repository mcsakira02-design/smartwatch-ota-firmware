/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file ec_bsp_em7028_driver.c
 * 
 * @par dependencies 
 * - ec_bsp_em7028_driver.h
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
 * 1.The em7028_inst function will instantiate the bsp_em7028_driver_t object and
 * with the needed funtion interface. 
 * 
 * 2.Then the users could all the IOs from instances of bsp_em7028_driver_t.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
//******************************** Includes *********************************//
#include "bsp_em7028_driver.h"
#include "bsp_em7028_reg.h"
#include "Debug.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//
#define EM7028_MEASURE_WAITING_TIME  80        // Measurement time [ms] 
#define EM7028_NOT_INITED             0        // Not init. flag 
#define EM7028_INITED                 1        // Not init. flag 

uint8_t  g_em7028_inited       = EM7028_NOT_INITED;       // Init. flag 
#define IS_EM7028INITED  (EM7028_INITED == g_em7028_inited) // if the device has been inited

//******************************** Defines **********************************//

//******************************** Variables ********************************//
// static int8_t  g_em7028_inited       = EM7028_NOT_INITED;       // Init. flag 
static uint8_t g_device_id           =                0;        // Device_id

//******************************** Variables ********************************//

//******************************** Functions ********************************//

/**
 * @brief Function for readonereg
 * 
 * Steps:
 *  1, XOR each byte of the input data with the CRC register.
 *  2, For each bit, check the most significant bit.
 *  3, Shift the CRC register left and, if the most significant bit is 1,
 *  XOR with the polynomial.
 * 
 * @param[in] p_data : Pointer to the input data.
 * @param[in] length : Length of the input data.
 * 
 * @return uint8_t : The calculated CRC-8 checksum.
 * 
 * */
uint8_t  em7028_readonereg(bsp_em7028_driver_t * const p_em7028_instance,
                            unsigned char regaddr)
{
	unsigned char dat;
    p_em7028_instance->p_iic_driver_instance->pf_iic_start(NULL);
    p_em7028_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, (EM7028_ADDR<<1));
    p_em7028_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL);
    p_em7028_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, regaddr);
    p_em7028_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL);

    p_em7028_instance->p_iic_driver_instance->pf_iic_start(NULL);
    p_em7028_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, (EM7028_ADDR<<1)+1);
    p_em7028_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL);
    p_em7028_instance->p_iic_driver_instance->pf_iic_receive_byte(NULL,&dat);
    p_em7028_instance->p_iic_driver_instance->pf_iic_send_no_ack(NULL);
    p_em7028_instance->p_iic_driver_instance->pf_iic_stop(NULL);
    return dat;
}

uint8_t  em7028_writeonereg(bsp_em7028_driver_t * const p_em7028_instance,
                        unsigned char RegAddr, unsigned char dat)
{
	p_em7028_instance->p_iic_driver_instance->pf_iic_start(NULL);
    p_em7028_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, (EM7028_ADDR<<1));
    if(p_em7028_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL))
    {
        p_em7028_instance->p_iic_driver_instance->pf_iic_stop(NULL);
        return 1;
    }
    p_em7028_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, RegAddr);
    if(p_em7028_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL))
    {
        p_em7028_instance->p_iic_driver_instance->pf_iic_stop(NULL);
        return 1;
    }
    p_em7028_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, dat);
    if(p_em7028_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL))
    {
        p_em7028_instance->p_iic_driver_instance->pf_iic_stop(NULL);
        return 1;
    }
    p_em7028_instance->p_iic_driver_instance->pf_iic_stop(NULL);
    return 0;
}

/**
 * @brief Function for reading em7028 ID.
 * 
 * Steps:
 *  1, Figure out which objects
 *  2, Internally call the related functions to read ID.
 * 
 * @param[in] p_em7028_instance : The pointer to object of bsp_em7028_driver_t.
 * 
 * @return  em7028_status_t.
 * 
 * */
static em7028_status_t em7028_read_id(bsp_em7028_driver_t * const p_em7028_instance,uint8_t *id)
{
    uint8_t data = 0;
    uint8_t i = 5;
    
#ifndef HARDWARE_IIC
    p_em7028_instance->p_iic_driver_instance->pf_critical_enter();
#endif /* End of HARDWARE_IIC */
    *id = em7028_readonereg(p_em7028_instance, ID_REG);
    while(*id != EM7028_ID && i)
    {
#ifdef OS_SUPPORTING
        p_em7028_instance->p_yield_instance->pf_rtos_yield(100);
        i--;
        *id = em7028_readonereg(p_em7028_instance, ID_REG);
    #ifdef DEBUG_HARTRATE_DRIVER
		DEBUG_OUT("EM7028 Try Read ID\r\n");
    #endif
#endif
    }
    if(i == 0)
    {
    #ifdef DEBUG_HARTRATE_DRIVER
		DEBUG_OUT("EM7028 Init Fail\r\n");
    #endif
        return EM7028_ERRORRESOURCE;
    }
#ifdef DEBUG_HARTRATE_DRIVER
	DEBUG_OUT("EM7028 Init SUCCESS\r\n");
#endif
    return EM7028_OK;
}

/**
 * @brief Function for reading em7028 Driver Layer Init.
 * 
 * @param[in] pem7028_instance : The pointer to object of bsp_em7028_driver_t.
 * 
 * @return  em7028_status_t.
 * 
 * */
static em7028_status_t em7028_init( bsp_em7028_driver_t * const p_em7028_instance)
{
    em7028_status_t ret = EM7028_OK;
#ifdef DEBUG_SENSOR_EM7028_DRIVER
    DEBUG_OUT("em7028_init start");
#endif
    
    if(NULL == p_em7028_instance->p_iic_driver_instance            ||
       NULL == p_em7028_instance->p_iic_driver_instance->pf_iic_init)
    {
#ifdef DEBUG_SENSOR_EM7028_DRIVER
        DEBUG_OUT("p_iic_driver_instance is NULL");
#endif
    }
    
    // Enter Critical Segmnet
#ifndef HARDWARE_IIC
    p_em7028_instance->p_iic_driver_instance->pf_critical_enter();
#endif /* End of HARDWARE_IIC */

    // Read the ID internally
    uint8_t id;
    ret = p_em7028_instance->pf_read_id(p_em7028_instance, &id);
    if ( EM7028_OK != ret )
    {
#ifdef DEBUG_SENSOR_EM7028_DRIVER
        // id read error
        DEBUG_OUT("em7028 id read error");
#endif
        return EM7028_ERRORRESOURCE;
    }

	em7028_writeonereg(p_em7028_instance, HRS_CFG,0x00);				
	//HRS1_EN, HRS2_dis
	//Heart Beat Measurement is enabled with LED1 turned on and only Red Light Sensor and IR sensor enabled. 
	//When LED1 turned on, the result stores to HRS_DATA0;
	em7028_writeonereg(p_em7028_instance, HRS2_DATA_OFFSET, 0x00);
	//0 offset
	em7028_writeonereg(p_em7028_instance, HRS2_GAIN_CTRL, 0x7f);		
	//HRS2 GAIN = 1
	em7028_writeonereg(p_em7028_instance, HRS1_CTRL, 0x47);
	//HRS1 GAIN =1, HRS1 RANGE =8, HRS1 FREQ = 2.62144MHz (1.5625ms), HRS1 RES = 16 bits, HRS1 mode
	em7028_writeonereg(p_em7028_instance, INT_CTRL, 0x00);
	//LED programmed current = 2.5mA

    //check if the device has been inited
    uint8_t data = 0;
    data = em7028_readonereg(p_em7028_instance, HRS_CFG);
    if(data != 0x00)
    {
#ifdef DEBUG_SENSOR_EM7028_DRIVER
        // Read the em7028 ID
        DEBUG_OUT("em7028's HRS_CFG = [0x%x] ", data);
#endif
        return EM7028_ERRORRESOURCE;
    }

    data = em7028_readonereg(p_em7028_instance, HRS1_CTRL);
    if(data!= 0x47)
    {
#ifdef DEBUG_SENSOR_EM7028_DRIVER
        // Read the em7028 ID
        DEBUG_OUT("em7028's HRS1_CTRL = [0x%x] ", data);
#endif
        return EM7028_ERRORRESOURCE;
    }
    // //Exit Critical Segmnet
#ifndef HARDWARE_IIC
    p_em7028_instance->p_iic_driver_instance->pf_critical_exit();
#endif /* End of HARDWARE_IIC */

    // Change the Flag of the internal flag
    g_em7028_inited = EM7028_INITED;
#ifdef DEBUG_SENSOR_EM7028_DRIVER
    // Read the em7028 ID
    DEBUG_OUT("em7028's ID = [0x%x] ", id);
#endif
    return EM7028_OK;
}

/**
 * @brief Function for reading em7028 Driver Layer Deinit.
 * 
 * @param[in] pem7028_instance : The pointer to object of bsp_em7028_driver_t.
 * 
 * @return  em7028_status_t.
 * 
 * */
uint8_t em7028_hrs_enable(bsp_em7028_driver_t * const p_em7028_instance)
{
	uint8_t i = 5;
    uint8_t id = 0;
    em7028_read_id(p_em7028_instance,&id);
	while(id != 0x36 && i)
	{
        p_em7028_instance->p_yield_instance->pf_rtos_yield(100);
		i--;
	}
	if(!i)
	{return 1;}
	em7028_writeonereg(p_em7028_instance,HRS_CFG,0x08);
	return 0;
}

/**
 * @brief Function for reading em7028 Driver Layer Deinit.
 * 
 * @param[in] pem7028_instance : The pointer to object of bsp_em7028_driver_t.
 * 
 * @return  em7028_status_t.
 * 
 * */
uint8_t em7028_hrs_disenable(bsp_em7028_driver_t * const p_em7028_instance)
{
	uint8_t i = 5;
    uint8_t id = 0;
    em7028_read_id(p_em7028_instance,&id);
	while(id != 0x36 && i)
	{
        p_em7028_instance->p_yield_instance->pf_rtos_yield(100);
		i--;
	}
	if(!i)
	{return 1;}
	em7028_writeonereg(p_em7028_instance,HRS_CFG,0x00);
	return 0;
}

/**
 * @brief Function for reading em7028 Driver Layer Deinit.
 * 
 * @param[in] pem7028_instance : The pointer to object of bsp_em7028_driver_t.
 * 
 * @return  em7028_status_t.
 * 
 * */
static em7028_status_t em7028_get_hrs1 \
            (bsp_em7028_driver_t * const p_em7028_instance,uint16_t * const u16_hartdata)
{
	*u16_hartdata = em7028_readonereg(p_em7028_instance,HRS1_DATA0_H);
	*u16_hartdata <<= 8;
	*u16_hartdata |= em7028_readonereg(p_em7028_instance,HRS1_DATA0_L);
	return 0;
}


/**
 * @brief Function for reading em7028 Driver Layer Deinit.
 * 
 * @param[in] pem7028_instance : The pointer to object of bsp_em7028_driver_t.
 * 
 * @return  em7028_status_t.
 * 
 * */
static em7028_status_t em7028_deinit(bsp_em7028_driver_t * const p_em7028_instance)
{
    g_em7028_inited = EM7028_NOT_INITED;
    return EM7028_OK;
}

/**
 * @brief Function for instantiate em7028 object.
 * 
 * @param[in] p_em7028_instance : The pointer to object of bsp_em7028_driver_t.
 * @param[in] p_iic_driver_instance : The pointer to reference of \
                                                      em7028_iic_driver_interface_t.
 * @param[in] p_timebase_instance : The pointer to reference of \
                                                        em7028_timebase_interface_t.
 * @param[in] p_yield_instance : The pointer to reference of \
                                                           em7028_yield_interface_t.
 * 
 * @return  em7028_status : [uint8_t] em7028 status .
 * 
 * */
em7028_status_t em7028_inst(
                        bsp_em7028_driver_t * const p_em7028_instance,
                        em7028_iic_driver_interface_t * const p_iic_driver_instance,
#ifdef OS_SUPPORTING
                        em7028_yield_interface_t * const p_yield_instance
#endif //End of OS_SUPPORTING
                        )
 {
    if( IS_EM7028INITED)
    {
        //Already initialized
        return EM7028_ERRORRESOURCE;
    }
#ifdef DEBUG_SENSOR_EM7028_DRIVER
    DEBUG_OUT("em7028_inst start");
#endif
    uint8_t ret = 0;
    if(NULL == p_em7028_instance || NULL == p_iic_driver_instance)
    {
        return 1;
    }

    p_em7028_instance->p_iic_driver_instance = p_iic_driver_instance;
    p_em7028_instance->p_yield_instance = p_yield_instance;

    p_em7028_instance->pf_init = (em7028_status_t (*)(void * const))\
                                                        em7028_init;
    p_em7028_instance->pf_deinit = (em7028_status_t (*)(void * const))\
                                                        em7028_deinit;
    p_em7028_instance->pf_read_id = (em7028_status_t (*)(void * const,uint8_t *id))\
                                                        em7028_read_id;
    p_em7028_instance->pf_hrs_enable = (em7028_status_t (*)(void * const))\
                                                        em7028_hrs_enable;
    p_em7028_instance->pf_hrs_disable = (em7028_status_t (*)(void * const))\
                                                        em7028_hrs_disenable;
    p_em7028_instance->pf_read_hrs = (em7028_status_t (*)(void * const,uint16_t * const u16_hartdata))\
                                                        em7028_get_hrs1;                                                    
    /* call the init function */
    ret = em7028_init(p_em7028_instance);
#ifdef DEBUG_SENSOR_EM7028_DRIVER
    DEBUG_OUT("em7028_init ret = %d", ret);
#endif
    if(ret)
    {
#ifdef DEBUG_SENSOR_EM7028_DRIVER
    DEBUG_OUT("em7028 init failed");
#endif
        return EM7028_ERRORRESOURCE;
    }
#ifdef DEBUG_SENSOR_EM7028_DRIVER
    DEBUG_OUT("em7028_inst end");
#endif
    return EM7028_OK;
 }   
 
 


 //******************************** Functions ********************************//
