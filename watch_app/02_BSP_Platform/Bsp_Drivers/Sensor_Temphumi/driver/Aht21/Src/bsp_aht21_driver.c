/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file ec_bsp_aht21_driver.c
 * 
 * @par dependencies 
 * - ec_bsp_aht21_driver.h
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
 * 1.The aht21_inst function will instantiate the bsp_aht21_driver_t object and
 * with the needed funtion interface. 
 * 
 * 2.Then the users could all the IOs from instances of bsp_aht21_driver_t.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
//******************************** Includes *********************************//
#include "bsp_aht21_driver.h"
#include "bsp_aht21_reg.h"
#include "Debug.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//
#define AHT21_MEASURE_WAITING_TIME  80        // Measurement time [ms] 
#define AHT21_NOT_INITED             0        // Not init. flag 
#define AHT21_INITED                 1        // Not init. flag 
#define AHT21_ID                  0x18        // AHT21 ID

#define CRC8_POLYNOMIAL           0x31        // CRC-8 polynomial
#define CRC8_INITIAL              0xFF        // CRC-8 initial value


#define IS_INITED  (AHT21_INITED == g_inited) // if the device has been inited

//******************************** Defines **********************************//

//******************************** Variables ********************************//
static int8_t  g_inited       = AHT21_NOT_INITED;    // Init. flag 
static uint8_t g_device_id    =                0;    // Device_id

//******************************** Variables ********************************//

//******************************** Functions ********************************//

/**
 * @brief Function for calculating CRC-8 checksum.
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
static uint8_t CheckCrc8(const uint8_t *p_data, const uint8_t length)
{
    uint8_t crc = CRC8_INITIAL; // Initialize CRC register

    for (uint8_t i = 0; i < length; i++)
    {
        crc ^= p_data[i]; // XOR the current byte with the CRC

        // Process each bit of the current byte
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x80)
            {
                // If MSB is 1, shift and XOR with polynomial
                crc = (crc << 1) ^ CRC8_POLYNOMIAL; 
            }
            else
            {
                // Otherwise, just shift left
                crc <<= 1; 
            }
        }
    }

    return crc; // Return the final CRC value
}


/**
 * @brief Function for reading AHT21 ID.
 * 
 * Steps:
 *  1, Figure out which objects
 *  2, Internally call the related functions to read ID.
 * 
 * @param[in] p_aht21_instance : The pointer to object of bsp_aht21_driver_t.
 * 
 * @return  aht21_status_t.
 * 
 * */
static aht21_status_t __read_id(bsp_aht21_driver_t * const p_aht21_instance)
{

    uint8_t data = 0;
    
#ifndef HARDWARE_IIC
    p_aht21_instance->p_iic_driver_instance->pf_critical_enter();
#endif /* End of HARDWARE_IIC */
    
    // Send the IIC start Signal
    p_aht21_instance->p_iic_driver_instance->pf_iic_start(NULL);
    
    // Send command to read ID
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_byte(NULL,\
                                                AHT21_REG_READ_ADDR);
    
    // Wait the ACK of IIC slave device
    if ( AHT21_OK == \
        p_aht21_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL))
    {
        // Receive the data from slave device
        p_aht21_instance->p_iic_driver_instance->pf_iic_receive_byte(NULL,\
                                                                     &data);
    }
    
    // Send the stop signal
    p_aht21_instance->p_iic_driver_instance->pf_iic_stop(NULL);
    
#ifndef HARDWARE_IIC
    p_aht21_instance->p_iic_driver_instance->pf_critical_exit();
#endif /* End of HARDWARE_IIC */

    // Check the ID
    if ( AHT21_ID == (data & AHT21_ID) )
    {
        g_device_id = AHT21_ID;
        
        return AHT21_OK;
    }
    
    return AHT21_ERRORRESOURCE;
}

/**
 * @brief Function for reading AHT21 ID from outside calling.
 * 
 * @param[in] paht21_instance : The pointer to object of bsp_aht21_driver_t.
 * 
 * @return  ID of AHT21 : [uint8_t] ID of AHT21 Device.
 * 
 * */
static aht21_status_t aht21_read_id(\
                                   bsp_aht21_driver_t * const p_aht21_instance)
{
    if( !IS_INITED )
    {
        return AHT21_ERRORRESOURCE;
    }
#ifdef DEBUG_SENSOR_AHT21_DRIVER
    DEBUG_OUT("aht21_read_id");
#endif
    return g_device_id;
}

/**
 * @brief Function for reading AHT21 Driver Layer Init.
 * 
 * @param[in] paht21_instance : The pointer to object of bsp_aht21_driver_t.
 * 
 * @return  aht21_status_t.
 * 
 * */
static aht21_status_t aht21_init( bsp_aht21_driver_t * const p_aht21_instance)
{
    aht21_status_t ret = AHT21_OK;
#ifdef DEBUG_SENSOR_AHT21_DRIVER
    DEBUG_OUT("aht21_init start");
#endif
    p_aht21_instance->p_yield_instance->pf_rtos_yield(80);
    
    if(NULL == p_aht21_instance->p_iic_driver_instance            ||
       NULL == p_aht21_instance->p_iic_driver_instance->pf_iic_init)
    {
#ifdef DEBUG_SENSOR_AHT21_DRIVER
        DEBUG_OUT("p_iic_driver_instance is NULL");
#endif
    }
    
    // Enter Critical Segmnet
#ifndef HARDWARE_IIC
    p_aht21_instance->p_iic_driver_instance->pf_critical_enter();
#endif /* End of HARDWARE_IIC */

    // Init the IIC Interface
    p_aht21_instance->p_iic_driver_instance->pf_iic_init(NULL);
#ifdef DEBUG_SENSOR_AHT21_DRIVER
        DEBUG_OUT("aht21_init iic_driver_init---------");
#endif
    // Read the ID internally
    ret = __read_id(p_aht21_instance);
    if ( AHT21_OK != ret )
    {
        return AHT21_ERRORRESOURCE;
    }
    //Exit Critical Segmnet
#ifndef HARDWARE_IIC
    p_aht21_instance->p_iic_driver_instance->pf_critical_exit();
#endif /* End of HARDWARE_IIC */

    // Change the Flag of the internal flag
    g_inited = AHT21_INITED;
#ifdef DEBUG_SENSOR_AHT21_DRIVER
    // Read the AHT21 ID
    DEBUG_OUT("aht21's ID = [0x%x] ", aht21_read_id(p_aht21_instance));
#endif
    return AHT21_OK;
}

/**
 * @brief Function for reading AHT21 Driver Layer Deinit.
 * 
 * @param[in] paht21_instance : The pointer to object of bsp_aht21_driver_t.
 * 
 * @return  aht21_status_t.
 * 
 * */
static aht21_status_t aht21_deinit(bsp_aht21_driver_t * const p_aht21_instance)
{
    g_inited = AHT21_NOT_INITED;
    return AHT21_OK;
}

/**
 * @brief Function for reading AHT21 Status.
 * 
 * @param[in] paht21_instance : The pointer to object of bsp_aht21_driver_t.
 * 
 * @return  aht21_status : [uint8_t] aht21 status .
 * 
 * */
static uint8_t aht21_read_status(bsp_aht21_driver_t * const p_aht21_instance)
{
    if( !IS_INITED )
    {
        return AHT21_ERRORRESOURCE;
    }
    uint8_t rx_data = 0;
    
    // Enter Critical Segmnet
#ifndef HARDWARE_IIC
    p_aht21_instance->p_iic_driver_instance->pf_critical_enter();
#endif /* End of HARDWARE_IIC */
    
    // Send the IIC start Signal
    p_aht21_instance->p_iic_driver_instance->pf_iic_start(NULL);
    
    // Send the address of IIC slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, 
                                                          AHT21_REG_READ_ADDR);
    // Wait the ACK of IIC slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL);
    
    // Receive the data from slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_receive_byte(NULL,
                                                          &rx_data);
    
    // Send the non-ack signal from Master to Slave
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_no_ack(NULL);
    
    // Send the stop signal
    p_aht21_instance->p_iic_driver_instance->pf_iic_stop(NULL);
    
    //Exit Critical Segmnet
#ifndef HARDWARE_IIC
    p_aht21_instance->p_iic_driver_instance->pf_critical_exit();
#endif /* End of HARDWARE_IIC */
#ifdef DEBUG_SENSOR_AHT21_DRIVER
    // Read the AHT21 ID
    DEBUG_OUT("rx_data=%#x", rx_data);
#endif
    return rx_data;
}

/**
 * @brief Function for reading AHT21 temprature and humidity
 * 
 * @param[in] p_aht21_instance : The pointer to object of bsp_aht21_driver_t.
 * @param[in] temp : [float *] The pointer to reference of temp variable.
 * @param[in] humi : [float *] pointer to reference of humi variable.
 * 
 * @return  aht21_status : [uint8_t] aht21 status .
 * 
 * */
static aht21_status_t aht21_read_temp_humi(\
                                bsp_aht21_driver_t * const p_aht21_instance,
                                float * const temp, 
                                float * const humi)
{
    if( !IS_INITED )
    {
        return AHT21_ERRORRESOURCE;
    }
    uint8_t        cnt = 5;
    uint8_t     byte_1th=0;
    uint8_t     byte_2th=0;
    uint8_t     byte_3th=0;
    uint8_t     byte_4th=0;
    uint8_t     byte_5th=0;
    uint8_t     byte_6th=0;
    uint32_t retu_data = 0;
    
    // Enter Critical Segmnet
#ifndef HARDWARE_IIC
    p_aht21_instance->p_iic_driver_instance->pf_critical_enter();
#endif /* End of HARDWARE_IIC */
    
    // Send the IIC start Signal
    p_aht21_instance->p_iic_driver_instance->pf_iic_start(NULL);
    
    // Send the address of IIC slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, 
                                                         AHT21_REG_WRITE_ADDR);
    // Wait the response of IIC slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL);
    
    // Send the command to ask aht21 prepare data
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, 
                                                        AHT21_REG_MEASURE_CMD);
    // Wait the ACK of IIC slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL);
    
    // Send the command to configure aht21 parameter[1]
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, 
                                                  AHT21_REG_MEASURE_CMD_ARGS1);
    // Wait the ACK of IIC slave device 
    p_aht21_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL);
    
    // Send the command to configure aht21 parameter[2]
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_byte(NULL, 
                                                  AHT21_REG_MEASURE_CMD_ARGS2);
    // Wait the ACK of IIC slave device 
    p_aht21_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL);
    
    // Send the stop signal
    p_aht21_instance->p_iic_driver_instance->pf_iic_stop(NULL);
    
    // Exit Critical Segmnet
#ifndef HARDWARE_IIC
    p_aht21_instance->p_iic_driver_instance->pf_critical_exit();
#endif /* End of HARDWARE_IIC */
    
    // Do the delay with AHT21_MEASURE_WAITING_TIME 
    int32_t start_time = \
                p_aht21_instance->p_timebase_instance->pf_get_tick_count();
    while(p_aht21_instance->p_timebase_instance->pf_get_tick_count() - 
                                       start_time < AHT21_MEASURE_WAITING_TIME)
    {   
#ifdef OS_SUPPORTING
        p_aht21_instance->p_yield_instance->pf_rtos_yield(\
                                                   AHT21_MEASURE_WAITING_TIME);
#endif //End of OS_SUPPORTING
    }
    
    // Do the delay with AHT21_MEASURE_WAITING_TIME 
    while((0x80 == (aht21_read_status(p_aht21_instance)&0x80) )  && cnt)
    {
        p_aht21_instance->p_yield_instance->pf_rtos_yield(5);
        cnt--;
        if ( 0 == cnt )
        {
            return AHT21_ERRORTIMEOUT;
        }
    };
#ifdef DEBUG_SENSOR_AHT21_DRIVER
    // Read the AHT21 ID
    DEBUG_OUT("read temp");
#endif
    // Enter Critical Segmnet
#ifndef HARDWARE_IIC
    p_aht21_instance->p_iic_driver_instance->pf_critical_enter();
#endif /* End of HARDWARE_IIC */
    
    // Send the IIC start Signal
    p_aht21_instance->p_iic_driver_instance->pf_iic_start(NULL);
    
    // Send the address of IIC slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_byte(NULL,\
                                                          AHT21_REG_READ_ADDR);
    // Wait the response of IIC slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_wait_ack(NULL);
    
    // Receive the data from slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_receive_byte(NULL,\
                                                                    &byte_1th);
    // Send the ack signal from Master to Slave
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_ack(NULL);

    // Receive the data from slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_receive_byte(NULL,\
                                                                    &byte_2th);
    // Send the ack signal from Master to Slave
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_ack(NULL);

    // Receive the data from slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_receive_byte(NULL,\
                                                                    &byte_3th);
    // Send the ack signal from Master to Slave
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_ack(NULL);
    
    // Receive the data from slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_receive_byte(NULL,\
                                                                    &byte_4th);
    // Send the ack signal from Master to Slave
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_ack(NULL);
    
    // Receive the data from slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_receive_byte(NULL,\
                                                                    &byte_5th);
    // Send the ack signal from Master to Slave
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_ack(NULL);
    
    // Receive the data from slave device
    p_aht21_instance->p_iic_driver_instance->pf_iic_receive_byte(NULL,\
                                                                    &byte_6th);
    // Send the non-ack signal from Master to Slave
    p_aht21_instance->p_iic_driver_instance->pf_iic_send_no_ack(NULL);
    
    // Send the stop signal
    p_aht21_instance->p_iic_driver_instance->pf_iic_stop(NULL);
    
#ifndef HARDWARE_IIC
    p_aht21_instance->p_iic_driver_instance->pf_critical_exit();
#endif /* End of HARDWARE_IIC */

    retu_data = (retu_data|byte_2th)<<8;
    retu_data = (retu_data|byte_3th)<<8;
    retu_data = (retu_data|byte_4th);
    retu_data =retu_data >>4;
    *humi = (retu_data * 1000 >> 20);
    *humi /= 10;
    
    retu_data = 0;
    retu_data = (retu_data|(byte_4th&0x0f))<<8;
    retu_data = (retu_data|byte_5th)<<8;
    retu_data = (retu_data|byte_6th);
    retu_data = retu_data&0xfffff;
    *temp = ((retu_data * 2000 >> 20)- 500);
    *temp /= 10;
    return AHT21_OK;
}

/**
 * @brief Function for reading AHT21 humidity.
 * 
 * @param[in] p_aht21_instance : The pointer to object of bsp_aht21_driver_t.
 * @param[out] humi : [float *] The pointer to reference of huminity variable.
 * 
 * @return  aht21_status : [uint8_t] aht21 status .
 * 
 * */
static aht21_status_t aht21_read_humidity(\
                                bsp_aht21_driver_t * const p_aht21_instance, 
                                                          float * const humi)
{
    if( !IS_INITED )
    {
        return AHT21_ERRORRESOURCE;
    }
    return AHT21_OK;
}

/**
 * @brief Function for make AHT21 sleep.
 * 
 * @param[in] p_aht21_instance : The pointer to object of bsp_aht21_driver_t.
 * @param[out] humi : [float *] The pointer to reference of huminity variable.
 * 
 * @return  aht21_status : [uint8_t] aht21 status .
 * 
 * */
static aht21_status_t aht21_sleep(bsp_aht21_driver_t * const p_aht21_instance)
{
    if( !IS_INITED )
    {
        return AHT21_ERRORRESOURCE;
    }
    return AHT21_OK;
}

/**
 * @brief Function for make AHT21 wake-up.
 * 
 * @param[in] p_aht21_instance : The pointer to object of bsp_aht21_driver_t.
 * @param[out] humi : [float *] The pointer to reference of huminity variable.
 * 
 * @return  aht21_status : [uint8_t] aht21 status .
 * 
 * */
static aht21_status_t aht21_wakeup(bsp_aht21_driver_t * const p_aht21_instance)
{
    if( !IS_INITED )
    {
        return AHT21_ERRORRESOURCE;
    }
    return AHT21_OK;
}

/**
 * @brief Function for instantiate AHT21 object.
 * 
 * @param[in] p_aht21_instance : The pointer to object of bsp_aht21_driver_t.
 * @param[in] p_iic_driver_instance : The pointer to reference of \
                                                      ahtxx_iic_driver_interface_t.
 * @param[in] p_timebase_instance : The pointer to reference of \
                                                        ahtxx_timebase_interface_t.
 * @param[in] p_yield_instance : The pointer to reference of \
                                                           ahtxx_yield_interface_t.
 * 
 * @return  aht21_status : [uint8_t] aht21 status .
 * 
 * */
aht21_status_t aht21_inst(
                        bsp_aht21_driver_t * const p_aht21_instance,
                        ahtxx_iic_driver_interface_t * const p_iic_driver_instance,
#ifdef OS_SUPPORTING
                        ahtxx_yield_interface_t * const p_yield_instance,
#endif //End of OS_SUPPORTING
                        ahtxx_timebase_interface_t * const p_timebase_instance
                        )
 {
    if( IS_INITED)
    {
        //Already initialized
        return AHT21_ERRORRESOURCE;
    }
#ifdef DEBUG_SENSOR_AHT21_DRIVER
    DEBUG_OUT("aht21_inst start");
#endif
    uint8_t ret = 0;
    if(NULL == p_aht21_instance || NULL == p_iic_driver_instance)
    {
        return 1;
    }


    p_aht21_instance->p_iic_driver_instance = p_iic_driver_instance;
    p_aht21_instance->p_timebase_instance = p_timebase_instance;
    p_aht21_instance->p_yield_instance = p_yield_instance;

    p_aht21_instance->pf_init = (aht21_status_t (*)(void * const))\
                                                        aht21_init;
    p_aht21_instance->pf_deinit = (aht21_status_t (*)(void * const))\
                                                        aht21_deinit;
    p_aht21_instance->pf_read_id = (aht21_status_t (*)(void * const))\
                                                        aht21_read_id;
    p_aht21_instance->pf_read_temp_humi = \
              (aht21_status_t (*)(void * const,float * const temp,
                                                float * const humi))\
                                                    aht21_read_temp_humi;
    p_aht21_instance->pf_read_humi = \
              (aht21_status_t (*) (void * const,float * const humi))\
                                                aht21_read_humidity;
    p_aht21_instance->pf_sleep = (aht21_status_t (*)(void * const))\
                                                        aht21_sleep;
    p_aht21_instance->pf_wakeup = (aht21_status_t (*)(void * const))\
                                                       aht21_wakeup;

    /* call the init function */
    ret = aht21_init(p_aht21_instance);
#ifdef DEBUG_SENSOR_AHT21_DRIVER
    DEBUG_OUT("aht21_init ret = %d", ret);
#endif
    if(ret)
    {
#ifdef DEBUG_SENSOR_AHT21_DRIVER
    DEBUG_OUT("aht21 init failed");
#endif
        return AHT21_ERRORRESOURCE;
    }
#ifdef DEBUG_SENSOR_AHT21_DRIVER
    DEBUG_OUT("aht21_inst end");
#endif
    return AHT21_OK;
 }   
 
 
 //******************************** Functions ********************************//
