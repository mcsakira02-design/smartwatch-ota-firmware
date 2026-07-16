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
 
#ifndef __I2C_PORT_H__  /* Avoid repeated inclusion */
#define __I2C_PORT_H__


//******************************** Includes *********************************//
#include "main.h"
#include "i2c.h"   // hardware i2c
#include "iic_hal.h" // software i2c
#include "os_freertos.h"
#include "osal_mutex.h"
//******************************** Includes *********************************//
//******************************** Typedefs *********************************//
typedef enum
{
    EN_HARDWARE_I2C = 0,
    EN_SOFTWARE_I2C
}en_i2c_state_t;

typedef enum
{
    CORE_I2C_OK = 0,
    CORE_I2C_ERROR
}en_core_i2c_status_t;

typedef enum
{
    CORE_I2C_BUS_1 = 0,
    CORE_I2C_BUS_2,
    CORE_I2C_BUS_MAX
}en_core_i2c_bus_t;


typedef struct
{
    en_i2c_state_t en_i2c_state;
    iic_bus_t st_iic_bus_inst;                          //软件i2c接口
    I2C_HandleTypeDef* st_I2C_HandleTypeDef;             //硬件i2c接口
    osal_mutex_handle_t st_osMutexId;                   //互斥锁接口
} st_i2c_port_t;

//******************************** Typedefs *********************************//

//******************************** Defines **********************************//
#define SENSOR_I2C_REGISTER_MUTEX(mutex)        \
        core_i2c_register_mutex(CORE_I2C_BUS_1,mutex)

#define SENSOR_I2C_HARDWARE_WRITE(dev_addr,data,size,timeout)        \
        core_i2c_write(CORE_I2C_BUS_1, dev_addr, data, size, timeout)

#define SENSOR_I2C_HARDWARE_READ(dev_addr,data,size,timeout)        \
        core_i2c_read(CORE_I2C_BUS_1, dev_addr, data, size, timeout)

#define SENSOR_I2C_HARDWARE_MEM_WRITE(dev_addr, mem_addr, em_size, data, size, timeout) \
        core_i2c_mem_write(CORE_I2C_BUS_1, dev_addr, mem_addr, em_size, data, size, timeout)

#define SENSOR_I2C_HARDWARE_MEM_READ(dev_addr, mem_addr, em_size, data, size, timeout) \
        core_i2c_mem_read(CORE_I2C_BUS_1,  dev_addr, mem_addr, em_size, data, size, timeout)

#define SENSOR_I2C_HARDWARE_MEM_READ_DMA(dev_addr, mem_addr, em_size, data, size, timeout) \
        core_i2c_mem_read_dma(CORE_I2C_BUS_1,  dev_addr, mem_addr, em_size, data, size)

#define SENSOR_I2C_SOFTWARE_START()  \
        core_i2c_soft_start(CORE_I2C_BUS_1)


#define SENSOR_I2C_SOFTWARE_STOP()  \
        core_i2c_soft_stop(CORE_I2C_BUS_1)


#define SENSOR_I2C_SOFTWARE_WAITACK()  \
        core_i2c_soft_wait_ack(CORE_I2C_BUS_1)

#define SENSOR_I2C_SOFTWARE_SENDACK()  \
        core_i2c_soft_send_ack(CORE_I2C_BUS_1)

#define SENSOR_I2C_SOFTWARE_SENDNOACK()  \
        core_i2c_soft_send_no_ack(CORE_I2C_BUS_1)

#define SENSOR_I2C_SOFTWARE_SENDBYTE(data)  \
        core_i2c_soft_send_byte(CORE_I2C_BUS_1,data)

#define SENSOR_I2C_SOFTWARE_RECEIVEBYTE(data)  \
        core_i2c_soft_receive_byte(CORE_I2C_BUS_1,data)

#define TOUCHPAD_I2C_HARDWARE_WRITE(dev_addr,data,size,timeout)        \
        core_i2c_write(CORE_I2C_BUS_2, dev_addr, data, size, timeout)

#define TOUCHPAD_I2C_HARDWARE_READ(dev_addr,data,size,timeout)        \
        core_i2c_read(CORE_I2C_BUS_2, dev_addr, data, size, timeout)

#define TOUCHPAD_I2C_HARDWARE_MEM_WRITE(dev_addr, mem_addr, em_size, data, size, timeout) \
        core_i2c_mem_write(CORE_I2C_BUS_2, dev_addr, mem_addr, em_size, data, size, timeout)

#define TOUCHPAD_I2C_HARDWARE_MEM_READ(dev_addr, mem_addr, em_size, data, size, timeout) \
        core_i2c_mem_read(CORE_I2C_BUS_2,  dev_addr, mem_addr, em_size, data, size, timeout)

#define TOUCHPAD_I2C_HARDWARE_MEM_READ_DMA(dev_addr, mem_addr, em_size, data, size) \
        core_i2c_mem_read_dma(CORE_I2C_BUS_2,  dev_addr, mem_addr, em_size, data, size)
//******************************** Defines **********************************//

//**************************** Interface Structs ****************************//

//**************************** Interface Structs ****************************//

//******************************** Classes **********************************//

//******************************** Classes **********************************//

//******************************** APIs *************************************//
void core_i2c_register_mutex(en_core_i2c_bus_t bus, osal_mutex_handle_t mutex);
//******************************** APIs *************************************//


#endif /* __BSP_TEMP_HUMI_XXX_HANDLER_H__ */



