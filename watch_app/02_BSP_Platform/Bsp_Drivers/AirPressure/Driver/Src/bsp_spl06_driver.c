/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file ec_bsp_spl06_driver.c
 * 
 * @par dependencies 
 * - ec_bsp_spl06_driver.h
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
 * 1.The spl06_inst function will instantiate the bsp_spl06_driver_t object and
 * with the needed funtion interface. 
 * 
 * 2.Then the users could all the IOs from instances of bsp_spl06_driver_t.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
//******************************** Includes *********************************//
#include "bsp_spl06_driver.h"
#include "bsp_spl06_reg.h"
#include "Debug.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//
#define SPL06_MEASURE_WAITING_TIME  80        // Measurement time [ms] 
#define SPL06_NOT_INITED             0        // Not init. flag 
#define SPL06_INITED                 1        // Not init. flag 

uint8_t  g_spl06_inited       = SPL06_NOT_INITED;       // Init. flag 
#define IS_SPL06INITED  (SPL06_INITED == g_spl06_inited) // if the device has been inited

//******************************** Defines **********************************//

//******************************** Variables ********************************//
// static int8_t  g_spl06_inited       = SPL06_NOT_INITED;       // Init. flag 
static uint8_t g_device_id           =                0;        // Device_id
static int16_t c0,c1,c01,c11,c20,c21,c30;
static int32_t c00,c10;
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
uint8_t  spl06_readonereg(bsp_spl06_driver_t * const p_spl06_instance,
                            unsigned char regaddr)
{
	unsigned char dat;
    p_spl06_instance->p_iic_driver_instance->pf_iic_start(NULL);
    p_spl06_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, (SPL_CHIP_ADDRESS<<1));
    p_spl06_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL);
    p_spl06_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, regaddr);
    p_spl06_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL);

    p_spl06_instance->p_iic_driver_instance->pf_iic_start(NULL);
    p_spl06_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, (SPL_CHIP_ADDRESS<<1)+1);
    p_spl06_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL);
    p_spl06_instance->p_iic_driver_instance->pf_iic_receive_byte(NULL,&dat);
    p_spl06_instance->p_iic_driver_instance->pf_iic_send_no_ack(NULL);
    p_spl06_instance->p_iic_driver_instance->pf_iic_stop(NULL);
    return dat;
}
/**
 * @brief Function for reading spl06 ID.
 * 
 * Steps:
 *  1, Figure out which objects
 *  2, Internally call the related functions to read ID.
 * 
 * @param[in] p_spl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
uint8_t  spl06_writeonereg(bsp_spl06_driver_t * const p_spl06_instance,
                        unsigned char RegAddr, unsigned char dat)
{
	p_spl06_instance->p_iic_driver_instance->pf_iic_start(NULL);
    p_spl06_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, (SPL_CHIP_ADDRESS<<1));
    if(p_spl06_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL))
    {
        p_spl06_instance->p_iic_driver_instance->pf_iic_stop(NULL);
        return 1;
    }
    p_spl06_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, RegAddr);
    if(p_spl06_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL))
    {
        p_spl06_instance->p_iic_driver_instance->pf_iic_stop(NULL);
        return 1;
    }
    p_spl06_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, dat);
    if(p_spl06_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL));
    {
        p_spl06_instance->p_iic_driver_instance->pf_iic_stop(NULL);
    }
    p_spl06_instance->p_iic_driver_instance->pf_iic_stop(NULL);
    return 0;
}

int32_t Get_Traw(bsp_spl06_driver_t * const p_spl06_instance)
{
	uint8_t buff[3];
	int32_t Traw;
	buff[0] = spl06_readonereg(p_spl06_instance,SPL_TMP_B0);
	buff[1] = spl06_readonereg(p_spl06_instance,SPL_TMP_B1);
	buff[2] = spl06_readonereg(p_spl06_instance,SPL_TMP_B2);
	Traw = buff[2];
	Traw = Traw << 8 | buff[1];
	Traw = Traw << 8 | buff[0];
	if(Traw & (1<<23))
	{Traw |= 0xFF000000;}//24 bit 2´s complement numbers
	return Traw;
}
/**
 * @brief Function for reading spl06 ID.
 * 
 * Steps:
 *  1, Figure out which objects
 *  2, Internally call the related functions to read ID.
 * 
 * @param[in] p_spl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
int32_t Get_Praw(bsp_spl06_driver_t * const p_spl06_instance)
{
	uint8_t buff[3];
	int32_t Praw;
	buff[0] = spl06_readonereg(p_spl06_instance,SPL_PRS_B0);
	buff[1] = spl06_readonereg(p_spl06_instance,SPL_PRS_B1);
	buff[2] = spl06_readonereg(p_spl06_instance,SPL_PRS_B2);
	Praw = buff[2];
	Praw = Praw << 8 | buff[1];
	Praw = Praw << 8 | buff[0];
	if(Praw & (1<<23))
	{Praw |= 0xFF000000;}//24 bit 2´s complement numbers
	return Praw;
}
/**
 * @brief Function for reading spl06 ID.
 * 
 * Steps:
 *  1, Figure out which objects
 *  2, Internally call the related functions to read ID.
 * 
 * @param[in] p_spl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
int16_t get_c0(bsp_spl06_driver_t * const p_spl06_instance)
{
	uint8_t buff[2];
	int16_t c0;
	buff[0] = spl06_readonereg(p_spl06_instance,COEF_C0);
	buff[1] = spl06_readonereg(p_spl06_instance,COEF_C0_C1);
	c0 = buff[0];
	c0 = (c0 << 4) | (buff[1] >> 4);
	if(c0 & (1<<11))
	{c0 |= 0xF000;}
	return c0;
}
/**
 * @brief Function for reading spl06 ID.
 * 
 * Steps:
 *  1, Figure out which objects
 *  2, Internally call the related functions to read ID.
 * 
 * @param[in] p_spl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
int16_t get_c1(bsp_spl06_driver_t * const p_spl06_instance)
{
	uint8_t buff[2];
	int16_t c1;
	buff[0] = spl06_readonereg(p_spl06_instance,COEF_C0_C1);
	buff[1] = spl06_readonereg(p_spl06_instance,COEF_C1);
	c1 = buff[0] & 0x0F;
	c1 = (c1 << 8) | buff[1] ;
	if(c1 & (1<<11))
	{c1 |= 0xF000;}
	return c1;
}

int32_t get_c00(bsp_spl06_driver_t * const p_spl06_instance)
{
	uint8_t buff[3];
	int32_t c00;
	buff[0] = spl06_readonereg(p_spl06_instance,COEF_C00_H);
	buff[1] = spl06_readonereg(p_spl06_instance,COEF_C00_L);
	buff[2] = spl06_readonereg(p_spl06_instance,COEF_C00_C10);
	c00 = buff[0];
	c00 = c00<<8 | buff[1];
	c00 = (c00<<4) | (buff[2]>>4);
	if(c00 & (1<<19))
	{c00 |= 0xFFF00000;}
	return c00;
}
/**
 * @brief Function for reading spl06 ID.
 * 
 * Steps:
 *  1, Figure out which objects
 *  2, Internally call the related functions to read ID.
 * 
 * @param[in] p_spl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
int32_t get_c10(bsp_spl06_driver_t * const p_spl06_instance)
{
	uint8_t buff[3];
	int32_t c10;
	buff[0] = spl06_readonereg(p_spl06_instance,COEF_C00_C10);
	buff[1] = spl06_readonereg(p_spl06_instance,COEF_C10_M);
	buff[2] = spl06_readonereg(p_spl06_instance,COEF_C10_L);
	c10 = buff[0] & 0x0F;
	c10 = c10<<8 | buff[1];
	c10 = c10<<8 | buff[2];
	if(c10 & (1<<19))
	{c10 |= 0xFFF00000;}
	return c10;
}

int16_t get_c01(bsp_spl06_driver_t * const p_spl06_instance)
{
	uint8_t buff[2];
	int32_t c01;
	buff[0] = spl06_readonereg(p_spl06_instance,COEF_C01_H);
	buff[1] = spl06_readonereg(p_spl06_instance,COEF_C01_L);
	c01 = buff[0];
	c01 = c01<<8 | buff[1];
	return c01;
}
/**
 * @brief Function for reading spl06 ID.
 * 
 * Steps:
 *  1, Figure out which objects
 *  2, Internally call the related functions to read ID.
 * 
 * @param[in] p_spl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
int16_t get_c11(bsp_spl06_driver_t * const p_spl06_instance)
{
	uint8_t buff[2];
	int32_t c11;
	buff[0] = spl06_readonereg(p_spl06_instance,COEF_C11_H);
	buff[1] = spl06_readonereg(p_spl06_instance,COEF_C11_L);
	c11 = buff[0];
	c11 = c11<<8 | buff[1];
	return c11;
}
/**
 * @brief Function for reading spl06 ID.
 * 
 * Steps:
 *  1, Figure out which objects
 *  2, Internally call the related functions to read ID.
 * 
 * @param[in] p_spl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
int16_t get_c20(bsp_spl06_driver_t * const p_spl06_instance)
{
	uint8_t buff[2];
	int32_t c20;
	buff[0] = spl06_readonereg(p_spl06_instance,COEF_C20_H);
	buff[1] = spl06_readonereg(p_spl06_instance,COEF_C20_L);
	c20 = buff[0];
	c20 = c20<<8 | buff[1];
	return c20;
}
/**
 * @brief Function for reading spl06 ID.
 * 
 * Steps:
 *  1, Figure out which objects
 *  2, Internally call the related functions to read ID.
 * 
 * @param[in] p_spl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
int16_t get_c21(bsp_spl06_driver_t * const p_spl06_instance)
{
	uint8_t buff[2];
	int32_t c21;
	buff[0] = spl06_readonereg(p_spl06_instance,COEF_C21_H);
	buff[1] = spl06_readonereg(p_spl06_instance,COEF_C21_L);
	c21 = buff[0];
	c21 = c21<<8 | buff[1];
	return c21;
}
/**
 * @brief Function for reading spl06 ID.
 * 
 * Steps:
 *  1, Figure out which objects
 *  2, Internally call the related functions to read ID.
 * 
 * @param[in] p_spl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
int16_t get_c30(bsp_spl06_driver_t * const p_spl06_instance)
{
	uint8_t buff[2];
	int32_t c30;
	buff[0] = spl06_readonereg(p_spl06_instance,COEF_C30_H);
	buff[1] = spl06_readonereg(p_spl06_instance,COEF_C30_L);
	c30 = buff[0];
	c30 = c30<<8 | buff[1];
	return c30;
}

/**
 * @brief Function for reading spl06 ID.
 * 
 * Steps:
 *  1, Figure out which objects
 *  2, Internally call the related functions to read ID.
 * 
 * @param[in] p_spl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
static spl06_status_t spl06_read_id(bsp_spl06_driver_t * const p_spl06_instance,uint8_t *id)
{
    uint8_t data = 0;
    uint8_t i = 5;
    
#ifndef HARDWARE_IIC
    p_spl06_instance->p_iic_driver_instance->pf_critical_enter();
#endif /* End of HARDWARE_IIC */
    *id = spl06_readonereg(p_spl06_instance, SPL_ID_REG);
    while(*id != SPL_CHIP_ID && i)
    {
#ifdef OS_SUPPORTING
        p_spl06_instance->p_yield_instance->pf_rtos_yield(100);
        i--;
        *id = spl06_readonereg(p_spl06_instance, SPL_ID_REG);
    #ifdef DEBUG_SENSOR_SPL06_DRIVER
		DEBUG_OUT("SPL06 Try Read ID\r\n");
    #endif
#endif
    }
    if(i == 0)
    {
    #ifdef DEBUG_SENSOR_SPL06_DRIVER
		DEBUG_OUT("SPL06 Init Fail\r\n");
    #endif
        return SPL06_ERRORRESOURCE;
    }
#ifdef DEBUG_SENSOR_SPL06_DRIVER
	DEBUG_OUT("SPL06 Init SUCCESS\r\n");
#endif
    return SPL06_OK;
}

/**
 * @brief Function for reading spl06 Driver Layer Init.
 * 
 * @param[in] pspl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
static spl06_status_t spl06_init( bsp_spl06_driver_t * const p_spl06_instance)
{
    spl06_status_t ret = SPL06_OK;
#ifdef DEBUG_SENSOR_SPL06_DRIVER
    DEBUG_OUT("spl06_init start");
#endif
    
    if(NULL == p_spl06_instance->p_iic_driver_instance            ||
       NULL == p_spl06_instance->p_iic_driver_instance->pf_iic_init)
    {
#ifdef DEBUG_SENSOR_SPL06_DRIVER
        DEBUG_OUT("p_iic_driver_instance is NULL");
#endif
    }
    
    // Enter Critical Segmnet
#ifndef HARDWARE_IIC
    p_spl06_instance->p_iic_driver_instance->pf_critical_enter();
#endif /* End of HARDWARE_IIC */

    spl06_writeonereg(p_spl06_instance,SPL_PRS_CFG, 0x01);		// Pressure 2x oversampling

    spl06_writeonereg(p_spl06_instance,SPL_TMP_CFG, 0x80);		// External Temperature 1x oversampling

    spl06_writeonereg(p_spl06_instance,SPL_MEAS_CFG, 0x07);	// continuous pressure and temperature measurement

    spl06_writeonereg(p_spl06_instance,SPL_CFG_REG, 0x00);		//   

    c0 = get_c0(p_spl06_instance);
    c1 = get_c1(p_spl06_instance);
    c01 = get_c01(p_spl06_instance);
    c11 = get_c11(p_spl06_instance); 
    c20 = get_c20(p_spl06_instance);
    c21 = get_c21(p_spl06_instance);
    c30 = get_c30(p_spl06_instance);
    c00 = get_c00(p_spl06_instance);
    c10 = get_c10(p_spl06_instance);

    if(spl06_readonereg(p_spl06_instance,SPL_PRS_CFG)!=0x01 ||\
         spl06_readonereg(p_spl06_instance,SPL_CFG_REG)!=0x00)
    {
        return SPL06_ERROR;
    }//ERRO
    else 
    {
#ifdef DEBUG_SENSOR_SPL06_DRIVER
        // id read error
        DEBUG_OUT("spl06 init success");
#endif
    }//SUCCESS

    // Read the ID internally
    uint8_t id;
    ret = p_spl06_instance->pf_read_id(p_spl06_instance, &id);
    if ( SPL06_OK != ret )
    {
#ifdef DEBUG_SENSOR_SPL06_DRIVER
        // id read error
        DEBUG_OUT("spl06 id read error");
#endif
        return SPL06_ERRORRESOURCE;
    }
    //Exit Critical Segmnet
#ifndef HARDWARE_IIC
    p_spl06_instance->p_iic_driver_instance->pf_critical_exit();
#endif /* End of HARDWARE_IIC */

    // Change the Flag of the internal flag
    g_spl06_inited = SPL06_INITED;
#ifdef DEBUG_SENSOR_SPL06_DRIVER
    // Read the spl06 ID
    DEBUG_OUT("spl06's ID = [0x%x] ", id);
#endif
    return SPL06_OK;
}

/**
 * @brief Function for reading spl06 Driver Layer Deinit.
 * 
 * @param[in] pspl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
static spl06_status_t spl06_deinit(bsp_spl06_driver_t * const p_spl06_instance)
{
    g_spl06_inited = SPL06_NOT_INITED;
    return SPL06_OK;
}

/**
 * @brief Function for reading spl06 Driver Layer Deinit.
 * 
 * @param[in] pspl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
static spl06_status_t spl06_sleep(bsp_spl06_driver_t * const p_spl06_instance)
{
    // Enter Critical Segmnet
#ifndef HARDWARE_IIC
    p_spl06_instance->p_iic_driver_instance->pf_critical_enter();
#endif /* End of HARDWARE_IIC */

    // Send sleep Cmd
    spl06_writeonereg(p_spl06_instance, SPL_MEAS_CFG, 0x00);
    //Exit Critical Segmnet
#ifndef HARDWARE_IIC
    p_spl06_instance->p_iic_driver_instance->pf_critical_exit();
#endif /* End of HARDWARE_IIC */
    return SPL06_OK;
}

/**
 * @brief Function for reading spl06 Driver Layer Deinit.
 * 
 * @param[in] pspl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
static spl06_status_t spl06_wakeup(bsp_spl06_driver_t * const p_spl06_instance)
{
    // Enter Critical Segmnet
#ifndef HARDWARE_IIC
    p_spl06_instance->p_iic_driver_instance->pf_critical_enter();
#endif /* End of HARDWARE_IIC */

    // Send sleep Cmd
    spl06_writeonereg(p_spl06_instance, SPL_MEAS_CFG, 0x07);
    //Exit Critical Segmnet
#ifndef HARDWARE_IIC
    p_spl06_instance->p_iic_driver_instance->pf_critical_exit();
#endif /* End of HARDWARE_IIC */
    return SPL06_OK;
}

/**
 * @brief Function for reading spl06 Driver Layer Deinit.
 * 
 * @param[in] pspl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
static spl06_status_t spl06_pressure_calculate(bsp_spl06_driver_t * const p_spl06_instance,\
                                                float * const pu16_pressuredata)
{
	float Traw_sc, Praw_sc, Pcomp;
	Traw_sc = Get_Traw(p_spl06_instance);
	Traw_sc /= KT;
	Praw_sc = Get_Praw(p_spl06_instance);
	Praw_sc /= KP;
	Pcomp = (c00) + Praw_sc * ((c10) + Praw_sc * ((c20) + Praw_sc * (c30))) + Traw_sc * (c01) + Traw_sc * Praw_sc * ((c11) + Praw_sc * (c21));
	*pu16_pressuredata = Pcomp;
    return SPL06_OK;
}
/**
 * @brief Function for reading spl06 Driver Layer Deinit.
 * 
 * @param[in] pspl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
static spl06_status_t spl06_temperature_calculate(bsp_spl06_driver_t * const p_spl06_instance,\
                                                    float * const pu16_temperaturedata)
{
	float Traw_sc, Tcomp;
	Traw_sc = Get_Traw(p_spl06_instance);
	Traw_sc /= KT;
	Tcomp = c0 * 0.5 + c1 * Traw_sc;
    *pu16_temperaturedata = Tcomp;
    return SPL06_OK;
}
/**
 * @brief Function for reading spl06 Driver Layer Deinit.
 * 
 * @param[in] pspl06_instance : The pointer to object of bsp_spl06_driver_t.
 * 
 * @return  spl06_status_t.
 * 
 * */
static spl06_status_t spl06_altitude_calculate(bsp_spl06_driver_t * const p_spl06_instance,\
                                                float * const pf_altitudedata)
{
	float Altitude;
	Altitude = 44330 * (1 - powf(Pressure_Calculate()/101325, 0.1903));
    *pf_altitudedata = Altitude;
    return SPL06_OK;
}

/**
 * @brief Function for instantiate spl06 object.
 * 
 * @param[in] p_spl06_instance : The pointer to object of bsp_spl06_driver_t.
 * @param[in] p_iic_driver_instance : The pointer to reference of \
                                                      spl06_iic_driver_interface_t.
 * @param[in] p_timebase_instance : The pointer to reference of \
                                                        spl06_timebase_interface_t.
 * @param[in] p_yield_instance : The pointer to reference of \
                                                           spl06_yield_interface_t.
 * 
 * @return  spl06_status : [uint8_t] spl06 status .
 * 
 * */
spl06_status_t spl06_inst(
                        bsp_spl06_driver_t * const p_spl06_instance,
                        spl06_iic_driver_interface_t * const p_iic_driver_instance,
#ifdef OS_SUPPORTING
                        spl06_yield_interface_t * const p_yield_instance
#endif //End of OS_SUPPORTING
                        )
 {
    if( IS_SPL06INITED)
    {
        //Already initialized
        return SPL06_ERRORRESOURCE;
    }
#ifdef DEBUG_SENSOR_SPL06_DRIVER
    DEBUG_OUT("spl06_inst start");
#endif
    uint8_t ret = 0;
    if(NULL == p_spl06_instance || NULL == p_iic_driver_instance)
    {
        return 1;
    }

    p_spl06_instance->p_iic_driver_instance = p_iic_driver_instance;
    p_spl06_instance->p_yield_instance = p_yield_instance;

    p_spl06_instance->pf_init = (spl06_status_t (*)(void * const))\
                                                        spl06_init;
    p_spl06_instance->pf_deinit = (spl06_status_t (*)(void * const))\
                                                        spl06_deinit;
    p_spl06_instance->pf_read_id = (spl06_status_t (*)(void * const))\
                                                        spl06_read_id;
    /* call the init function */
    ret = spl06_init(p_spl06_instance);
#ifdef DEBUG_SENSOR_SPL06_DRIVER
    DEBUG_OUT("spl06_init ret = %d", ret);
#endif
    if(ret)
    {
#ifdef DEBUG_SENSOR_SPL06_DRIVER
    DEBUG_OUT("spl06 init failed");
#endif
        return SPL06_ERRORRESOURCE;
    }
#ifdef DEBUG_SENSOR_SPL06_DRIVER
    DEBUG_OUT("spl06_inst end");
#endif
    return SPL06_OK;
 }   
 

 
 //******************************** Functions ********************************//
