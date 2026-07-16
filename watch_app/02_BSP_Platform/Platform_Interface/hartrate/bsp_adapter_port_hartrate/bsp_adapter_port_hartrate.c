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
 * @brief Provide the HAL APIs of EM7028 and corresponding opetions.
 * 
 * Processing flow:
 * 
 * 2.Then the users could all the IOs from instances of bsp_EM7028_driver_t.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
//******************************** Includes *********************************//
#include "main.h"
#include "bsp_adapter_port_hartrate.h"
#include "bsp_wrapper_hartrate.h"
#include "bsp_em7028_driver.h"
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
static void hartrate_drv_init(hartrate_drv_t *dev);
static void hartrate_drv_deinit(hartrate_drv_t *dev);
static void hartrate_drv_read_id(hartrate_drv_t *dev, uint8_t *p_id);
static void hartrate_drv_read_hrs(hartrate_drv_t *dev, uint16_t *p_heartrate);
static void hartrate_drv_enable(hartrate_drv_t *dev);
static void hartrate_drv_disable(hartrate_drv_t *dev);
/***********************************************************************************
 *                 Public Implements
 ***********************************************************************************/


void drv_adapter_hartrate_register(void)
{
    hartrate_drv_t _hartrate_drv = {
        .idx = 0,
        .dev_id = 0,
        .hartrate_drv_init = hartrate_drv_init,
        .hartrate_drv_deinit = hartrate_drv_deinit,
        .hartrate_drv_read_id = hartrate_drv_read_id,
        .hartrate_drv_read_hrs = hartrate_drv_read_hrs,
        .hartrate_drv_enable = hartrate_drv_enable,
        .hartrate_drv_disable = hartrate_drv_disable,
    };

    drv_adapter_hartrate_reg(0, &_hartrate_drv);
}

/***********************************************************************************
 *                 Static Implements for Display
 ***********************************************************************************/
/* USER CODE BEGIN FunctionPrototypes */
static em7028_status_t iic_init_myown(void * bus)
{
    //上电默认硬件I2C
  //AHT_CLK_ENABLE;
  //IICInit(&iic_bus_instance);
  //Could check the register of IIC if required
  return EM7028_OK;
}

static em7028_status_t iic_start_myown(void * bus)
{
    //IICStart(&iic_bus_instance);
    SENSOR_I2C_SOFTWARE_START();
    return EM7028_OK;
}

static em7028_status_t iic_stop_myown(void * bus)
{
    //IICStop(&iic_bus_instance);
    SENSOR_I2C_SOFTWARE_STOP();
    return EM7028_OK;
}

static em7028_status_t pfiic_wait_ack_myown(void * bus)
{
    unsigned char ret = SUCCESS; // should be ErrorStatus but IICWaitAck(X)
    ret = SENSOR_I2C_SOFTWARE_WAITACK();
    if(SUCCESS == ret)
    {
        return EM7028_OK;
    } else {
        return EM7028_ERRORTIMEOUT;
    }
}

static em7028_status_t iic_send_ack_myown(void * bus)
{
    //IICSendAck(&iic_bus_instance);
    SENSOR_I2C_SOFTWARE_SENDACK();
    return EM7028_OK;
}

static em7028_status_t iic_send_no_ack_myown(void * bus)
{
    // IICSendNotAck(&iic_bus_instance);
    SENSOR_I2C_SOFTWARE_SENDNOACK();
    return EM7028_OK;
}

static em7028_status_t iic_send_byte_myown(void * bus, uint8_t data)
{
    //IICSendByte(&iic_bus_instance, data);
    SENSOR_I2C_SOFTWARE_SENDBYTE(data);
    return EM7028_OK;
}

static em7028_status_t iic_receive_byte_myown(void * bus, uint8_t * const data)
{
    // *data = IICReceiveByte(&iic_bus_instance);
    SENSOR_I2C_SOFTWARE_RECEIVEBYTE(data);
    return EM7028_OK;
}

// 构造iic总线实例
static em7028_iic_driver_interface_t iic_driver_interface = {
  .pf_iic_init         = iic_init_myown,
  .pf_iic_start        = iic_start_myown,
  .pf_iic_stop         = iic_stop_myown,
  .pf_iic_wait_ack     = pfiic_wait_ack_myown,
  .pf_iic_send_no_ack  = iic_send_no_ack_myown,
  .pf_iic_send_byte    = iic_send_byte_myown,
  .pf_iic_receive_byte = iic_receive_byte_myown,
  .pf_iic_send_ack     = iic_send_ack_myown,
  .pf_critical_enter   = (em7028_status_t (*)(void))vPortEnterCritical,
  .pf_critical_exit    = (em7028_status_t (*)(void))vPortExitCritical
};

static em7028_yield_interface_t yield_interface =
{
  .pf_rtos_yield       = osal_task_delay_ms
};
      
bsp_em7028_driver_t em7028_input_arg = 
{
  .p_iic_driver_instance = &iic_driver_interface,
  .p_yield_instance      = &yield_interface
};

static void hartrate_drv_init(hartrate_drv_t *dev)
{
  em7028_inst(&em7028_input_arg,
              em7028_input_arg.p_iic_driver_instance,
#ifdef OS_SUPPORTING
              em7028_input_arg.p_yield_instance
#endif
            );
}

static void hartrate_drv_deinit(hartrate_drv_t *dev)
{
    ;
}
static void hartrate_drv_read_id
            (hartrate_drv_t *dev, uint8_t *p_id)
{
    em7028_input_arg.pf_read_id(&em7028_input_arg,p_id);
}
static void hartrate_drv_read_hrs
            (hartrate_drv_t *dev, uint16_t *p_heartrate)
{
    em7028_input_arg.pf_read_hrs(&em7028_input_arg,p_heartrate);
}
static void hartrate_drv_enable(hartrate_drv_t *dev)
{
    em7028_input_arg.pf_hrs_enable(&em7028_input_arg);
}
static void hartrate_drv_disable(hartrate_drv_t *dev)
{
    em7028_input_arg.pf_hrs_disable(&em7028_input_arg);
}

//******************************** Functions ********************************//
