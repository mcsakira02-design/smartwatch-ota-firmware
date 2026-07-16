/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file drv_adapter_port_temphumioment.c
 * 
 * @par dependencies 
 * - i2c_port.h
 * - i2c.h
 * - iic_hal.h
 * - os_freertos
 * - osal_mutex
 * @author ssj
 * 
 * @brief Provide the HAL APIs of AHT21 and corresponding opetions.
 * 
 * Processing flow:
 * 
 * 2.Then the users could all the IOs from instances of bsp_aht21_driver_t.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
//******************************** Includes *********************************//
#include "adc_port.h"
#include "adc.h"
#include "os_freertos.h"
#include "osal_mutex.h"
#include "cmsis_os2.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//

static st_adc_port_t st_adc_port[CORE_ADC_BUS_MAX] =
{
    [CORE_ADC_BUS_1] = {
        .st_ADC_HandleTypeDef = &hadc1
    }
};
//******************************** Variables ********************************//

//******************************** Functions ********************************//
/**
 * @brief core_i2c_register_mutex
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
void core_adc_measure(en_core_adc_bus_t bus, uint32_t * p_adc_value)
{
    if (bus < CORE_ADC_BUS_MAX) 
    {
        HAL_ADC_Start(st_adc_port[bus].st_ADC_HandleTypeDef);
        
        if(HAL_ADC_PollForConversion(st_adc_port[bus].st_ADC_HandleTypeDef, 10) == HAL_OK)
        {
            *p_adc_value = HAL_ADC_GetValue(&hadc1);
        }
    }
}

