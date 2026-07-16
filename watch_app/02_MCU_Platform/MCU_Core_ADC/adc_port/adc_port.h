/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file ec_bsp_externflash_i_xxx_handler.h
 * 
 * @par dependencies 
 * 
 * 
 * @author ssj
 * 
 * @brief 
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
 
#ifndef __ADC_PORT_H__  /* Avoid repeated inclusion */
#define __ADC_PORT_H__


//******************************** Includes *********************************//
#include "main.h"
#include "adc.h"   // hardware i2c
//******************************** Includes *********************************//
//******************************** Typedefs *********************************//
typedef enum
{
    CORE_ADC_OK = 0,
    CORE_ADC_ERROR
}en_core_adc_status_t;

typedef enum
{
    CORE_ADC_BUS_1 = 0,//Light Adc
    CORE_ADC_BUS_MAX
}en_core_adc_bus_t;

typedef struct
{                  
    ADC_HandleTypeDef* st_ADC_HandleTypeDef;            
} st_adc_port_t;

//******************************** Typedefs *********************************//

//******************************** Defines **********************************//
#define LIGHT_ADC_MEASURE(p_adc_value)        \
        core_adc_measure(CORE_I2C_BUS_1,p_adc_value)
//******************************** Defines **********************************//

//**************************** Interface Structs ****************************//

//**************************** Interface Structs ****************************//

//******************************** Classes **********************************//

//******************************** Classes **********************************//

//******************************** APIs *************************************//
//******************************** APIs *************************************//


#endif /* __BSP_TEMP_HUMI_XXX_HANDLER_H__ */



