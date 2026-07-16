/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file drv_adapter_port_temphumioment.c
 * 
 * @par dependencies 
 * - drv_adapter_port_temphumioment.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of AIRPRESSURE and corresponding opetions.
 * 
 * Processing flow:
 * 
 * 2.Then the users could all the IOs from instances of bsp_AIRPRESSURE_driver_t.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
//******************************** Includes *********************************//
#include "main.h"
#include "bsp_adapter_port_airpressure.h"
#include "bsp_wrapper_airpressure.h"
#include "bsp_spl06_driver.h"
#include "Debug.h"
#include "stdarg.h"
#include "i2c_port.h"
#include "osal.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//
//******************************** Defines **********************************//

//******************************** Variables ********************************//

//******************************** Variables ********************************//

//******************************** Functions ********************************//
/***********************************************************************************
 *                 Static Declarations For temphumionment
 ***********************************************************************************/
static void airpressure_drv_init(airpressure_drv_t *dev);
static void airpressure_drv_deinit(airpressure_drv_t *dev);
static void airpressure_drv_read_id(airpressure_drv_t *dev, uint8_t *p_id);
static void airpressure_drv_altitude_calculate(airpressure_drv_t *dev, float * const pf_altitudedata);
static void airpressure_drv_pressure_calculate(airpressure_drv_t *dev, float * const pf_pressuredata);
static void airpressure_drv_temperature_calculate(airpressure_drv_t *dev, float * const pf_temperaturedata);
/***********************************************************************************
 *                 Public Implements
 ***********************************************************************************/
void drv_adapter_airpressure_register(void)
{
    airpressure_drv_t _airpressure_drv = {
        .idx = 0,
        .dev_id = 0,
        .airpressure_drv_init = airpressure_drv_init,
        .airpressure_drv_deinit = airpressure_drv_deinit,
        .airpressure_drv_read_id = airpressure_drv_read_id,
        .airpressure_drv_altitude_calculate = airpressure_drv_altitude_calculate,
        .airpressure_drv_pressure_calculate = airpressure_drv_pressure_calculate,
        .airpressure_drv_temperature_calculate = airpressure_drv_temperature_calculate,
    };

    drv_adapter_airpressure_reg(0, &_airpressure_drv);
}

/***********************************************************************************
 *                 Static Implements for Display
 ***********************************************************************************/
/* USER CODE BEGIN FunctionPrototypes */
static spl06_status_t iic_init_myown(void * bus)
{
    //上电默认硬件I2C
  //AHT_CLK_ENABLE;
  //IICInit(&iic_bus_instance);
  //Could check the register of IIC if required
  return SPL06_OK;
}

static spl06_status_t iic_start_myown(void * bus)
{
    //IICStart(&iic_bus_instance);
    SENSOR_I2C_SOFTWARE_START();
    return SPL06_OK;
}

static spl06_status_t iic_stop_myown(void * bus)
{
    //IICStop(&iic_bus_instance);
    SENSOR_I2C_SOFTWARE_STOP();
    return SPL06_OK;
}

static spl06_status_t pfiic_wait_ack_myown(void * bus)
{
    unsigned char ret = SUCCESS; // should be ErrorStatus but IICWaitAck(X)
    ret = SENSOR_I2C_SOFTWARE_WAITACK();
    if(SUCCESS == ret)
    {
        return SPL06_OK;
    } else {
        return SPL06_ERRORTIMEOUT;
    }
}

static spl06_status_t iic_send_ack_myown(void * bus)
{
    //IICSendAck(&iic_bus_instance);
    SENSOR_I2C_SOFTWARE_SENDACK();
    return SPL06_OK;
}

static spl06_status_t iic_send_no_ack_myown(void * bus)
{
    // IICSendNotAck(&iic_bus_instance);
    SENSOR_I2C_SOFTWARE_SENDNOACK();
    return SPL06_OK;
}

static spl06_status_t iic_send_byte_myown(void * bus, uint8_t data)
{
    //IICSendByte(&iic_bus_instance, data);
    SENSOR_I2C_SOFTWARE_SENDBYTE(data);
    return SPL06_OK;
}

static spl06_status_t iic_receive_byte_myown(void * bus, uint8_t * const data)
{
    // *data = IICReceiveByte(&iic_bus_instance);
    SENSOR_I2C_SOFTWARE_RECEIVEBYTE(data);
    return SPL06_OK;
}

// 构造iic总线实例
static spl06_iic_driver_interface_t iic_driver_interface = {
  .pf_iic_init         = iic_init_myown,
  .pf_iic_start        = iic_start_myown,
  .pf_iic_stop         = iic_stop_myown,
  .pf_iic_wait_ack     = pfiic_wait_ack_myown,
  .pf_iic_send_no_ack  = iic_send_no_ack_myown,
  .pf_iic_send_byte    = iic_send_byte_myown,
  .pf_iic_receive_byte = iic_receive_byte_myown,
  .pf_iic_send_ack     = iic_send_ack_myown,
  .pf_critical_enter   = osal_enter_critical,
  .pf_critical_exit    = osal_exit_critical
};

static spl06_yield_interface_t yield_interface =
{
  .pf_rtos_yield       = osal_task_delay_ms
};
      
bsp_spl06_driver_t airpressure_input_arg = 
{
  .p_iic_driver_instance = &iic_driver_interface,
  .p_yield_instance      = &yield_interface
};

static void airpressure_drv_init(airpressure_drv_t *dev)
{
    spl06_inst(&airpressure_input_arg,
              airpressure_input_arg.p_iic_driver_instance,
#ifdef OS_SUPPORTING
              airpressure_input_arg.p_yield_instance
#endif
            );
}

static void airpressure_drv_deinit(airpressure_drv_t *dev)
{

}
static void airpressure_drv_read_id
            (airpressure_drv_t *dev, uint8_t *p_id)
{
    airpressure_input_arg.pf_read_id(&airpressure_input_arg, p_id);
}

static void airpressure_drv_altitude_calculate\
        (airpressure_drv_t *dev, float * const pf_altitudedata)
{
    airpressure_input_arg.pf_altitude_calculate(&airpressure_input_arg, pf_altitudedata);
}

static void airpressure_drv_pressure_calculate\
        (airpressure_drv_t *dev, float * const pf_pressuredata)
{
    airpressure_input_arg.pf_pressure_calculate(&airpressure_input_arg, pf_pressuredata);
}

static void airpressure_drv_temperature_calculate\
        (airpressure_drv_t *dev, float * const pf_temperaturedata)
{
    airpressure_input_arg.pf_temperature_calculate(&airpressure_input_arg, pf_temperaturedata);
}
//******************************** Functions ********************************//
