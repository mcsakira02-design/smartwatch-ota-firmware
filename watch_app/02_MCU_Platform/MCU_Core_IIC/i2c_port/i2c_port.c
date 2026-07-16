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
#include "i2c_port.h"
#include "i2c.h"   // hardware i2c
#include "iic_hal.h" // software i2c
#include "os_freertos.h"
#include "osal_mutex.h"
#include "cmsis_os2.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//

static st_i2c_port_t st_i2c_port[CORE_I2C_BUS_MAX] =
{
    [CORE_I2C_BUS_1] = {
        .en_i2c_state = EN_HARDWARE_I2C,
        .st_iic_bus_inst = {
            .IIC_SDA_PORT = Sensor_SDA_GPIO_Port,
            .IIC_SDA_PIN = Sensor_SDA_Pin,
            .IIC_SCL_PORT = Sensor_SCL_GPIO_Port,
            .IIC_SCL_PIN = Sensor_SCL_Pin
        },
        .st_I2C_HandleTypeDef = &hi2c1,
    },
    [CORE_I2C_BUS_2] ={
        .en_i2c_state = EN_HARDWARE_I2C,
        .st_I2C_HandleTypeDef = &hi2c3
    }
};
//******************************** Variables ********************************//

//******************************** Functions ********************************//
static void core_i2c_switch(en_core_i2c_bus_t bus, en_i2c_state_t state);


/**
 * @brief core_i2c_register_mutex
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
void core_i2c_register_mutex(en_core_i2c_bus_t bus, osal_mutex_handle_t mutex)
{
    if (bus < CORE_I2C_BUS_MAX) {
        st_i2c_port[bus].st_osMutexId = mutex;
    }
}

/**
 * @brief core_i2c_lock
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
static inline void core_i2c_lock(en_core_i2c_bus_t bus)
{
    if (st_i2c_port[bus].st_osMutexId) {
        osal_mutex_take(st_i2c_port[bus].st_osMutexId, osWaitForever);
    }
}

/**
 * @brief core_i2c_unlock
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
static inline void core_i2c_unlock(en_core_i2c_bus_t bus)
{
    if (st_i2c_port[bus].st_osMutexId) {
        osal_mutex_give(st_i2c_port[bus].st_osMutexId);
    }
}

/**
 * @brief core_i2c_write
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
en_core_i2c_status_t core_i2c_write(en_core_i2c_bus_t bus, uint16_t dev_addr, uint8_t *data, uint16_t size, uint32_t timeout)
{
    if (bus >= CORE_I2C_BUS_MAX || ((I2C_HandleTypeDef *)&st_i2c_port[bus].st_I2C_HandleTypeDef == NULL)) return CORE_I2C_ERROR;
    core_i2c_lock(bus);
    core_i2c_switch(bus,EN_HARDWARE_I2C);
    HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(st_i2c_port[bus].st_I2C_HandleTypeDef, dev_addr, data, size, timeout);
    core_i2c_unlock(bus);
    return (ret == HAL_OK) ? CORE_I2C_OK : CORE_I2C_ERROR;
}

/**
 * @brief core_i2c_read
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
en_core_i2c_status_t core_i2c_read(en_core_i2c_bus_t bus, uint16_t dev_addr, uint8_t *data, uint16_t size, uint32_t timeout)
{
    if (bus >= CORE_I2C_BUS_MAX || ((I2C_HandleTypeDef *)&st_i2c_port[bus].st_I2C_HandleTypeDef == NULL)) return CORE_I2C_ERROR;
    core_i2c_lock(bus);
    core_i2c_switch(bus,EN_HARDWARE_I2C);
    HAL_StatusTypeDef ret = HAL_I2C_Master_Receive(st_i2c_port[bus].st_I2C_HandleTypeDef, dev_addr, data, size, timeout);
    core_i2c_unlock(bus);
    return (ret == HAL_OK) ? CORE_I2C_OK : CORE_I2C_ERROR;
}

/**
 * @brief core_i2c_mem_write
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
en_core_i2c_status_t core_i2c_mem_write(en_core_i2c_bus_t bus, uint16_t dev_addr, uint16_t mem_addr, uint16_t mem_size,
                                     uint8_t *data, uint16_t size, uint32_t timeout)
{
    if (bus >= CORE_I2C_BUS_MAX || ((I2C_HandleTypeDef *)&st_i2c_port[bus].st_I2C_HandleTypeDef == NULL)) return CORE_I2C_ERROR;
    core_i2c_lock(bus);
    core_i2c_switch(bus,EN_HARDWARE_I2C);
    HAL_StatusTypeDef ret = HAL_I2C_Mem_Write(st_i2c_port[bus].st_I2C_HandleTypeDef, dev_addr, mem_addr, mem_size, data, size, timeout);
    core_i2c_unlock(bus);
    return (ret == HAL_OK) ? CORE_I2C_OK : CORE_I2C_ERROR;
}
/**
 * @brief core_i2c_mem_read
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
en_core_i2c_status_t core_i2c_mem_read(en_core_i2c_bus_t bus, uint16_t dev_addr, uint16_t mem_addr, uint16_t mem_size,
                                    uint8_t *data, uint16_t size, uint32_t timeout)
{
    if (bus >= CORE_I2C_BUS_MAX || ((I2C_HandleTypeDef *)&st_i2c_port[bus].st_I2C_HandleTypeDef == NULL)) return CORE_I2C_ERROR;
    core_i2c_lock(bus);
    core_i2c_switch(bus,EN_HARDWARE_I2C);
    HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(st_i2c_port[bus].st_I2C_HandleTypeDef, dev_addr, mem_addr, mem_size, data, size, timeout);
    core_i2c_unlock(bus);
    return (ret == HAL_OK) ? CORE_I2C_OK : CORE_I2C_ERROR;
}

/**
 * @brief core_i2c_mem_read_dma
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
en_core_i2c_status_t core_i2c_mem_read_dma(en_core_i2c_bus_t bus, uint16_t dev_addr, uint16_t mem_addr, uint16_t mem_size,
                                            uint8_t *data, uint16_t size)
{
    if (bus >= CORE_I2C_BUS_MAX || ((I2C_HandleTypeDef *)&st_i2c_port[bus].st_I2C_HandleTypeDef == NULL)) return CORE_I2C_ERROR;
    //core_i2c_lock(bus);
    core_i2c_switch(bus,EN_HARDWARE_I2C);
    HAL_StatusTypeDef ret = \
    HAL_I2C_Mem_Read_DMA(st_i2c_port[bus].st_I2C_HandleTypeDef, \
                        dev_addr, mem_addr, mem_size, data, size);
    //core_i2c_unlock(bus);
    return (ret == HAL_OK) ? CORE_I2C_OK : CORE_I2C_ERROR;
}
/**
 * @brief core_i2c_soft_start
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
en_core_i2c_status_t core_i2c_soft_start(en_core_i2c_bus_t bus)
{
    if (bus >= CORE_I2C_BUS_MAX || st_i2c_port[bus].st_iic_bus_inst.IIC_SDA_PORT == NULL) return CORE_I2C_ERROR;
    core_i2c_lock(bus);
    core_i2c_switch(bus,EN_SOFTWARE_I2C);
    IICStart(&st_i2c_port[bus].st_iic_bus_inst);
    //core_i2c_unlock(bus);
    return CORE_I2C_OK;
}

/**
 * @brief core_i2c_soft_stop
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
en_core_i2c_status_t core_i2c_soft_stop(en_core_i2c_bus_t bus)
{
    if (bus >= CORE_I2C_BUS_MAX || st_i2c_port[bus].st_iic_bus_inst.IIC_SDA_PORT == NULL) return CORE_I2C_ERROR;
    IICStop(&st_i2c_port[bus].st_iic_bus_inst);
    core_i2c_unlock(bus);
    return CORE_I2C_OK;
}

/**
 * @brief core_i2c_soft_wait_ack
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
en_core_i2c_status_t core_i2c_soft_wait_ack(en_core_i2c_bus_t bus)
{
    if (bus >= CORE_I2C_BUS_MAX || st_i2c_port[bus].st_iic_bus_inst.IIC_SDA_PORT == NULL) return CORE_I2C_ERROR;
    unsigned char ret = SUCCESS; // should be ErrorStatus but IICWaitAck(X)
    ret = IICWaitAck(&st_i2c_port[bus].st_iic_bus_inst);
    if(SUCCESS == ret)
    {
        return CORE_I2C_OK;
    } else {
        return CORE_I2C_ERROR;
    }
}

/**
 * @brief core_i2c_soft_send_ack
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
en_core_i2c_status_t core_i2c_soft_send_ack(en_core_i2c_bus_t bus)
{
    if (bus >= CORE_I2C_BUS_MAX || st_i2c_port[bus].st_iic_bus_inst.IIC_SDA_PORT == NULL) return CORE_I2C_ERROR;
    IICSendAck(&st_i2c_port[bus].st_iic_bus_inst);
    return CORE_I2C_OK;
}

/**
 * @brief core_i2c_soft_send_no_ack
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
en_core_i2c_status_t core_i2c_soft_send_no_ack(en_core_i2c_bus_t bus)
{
    if (bus >= CORE_I2C_BUS_MAX || st_i2c_port[bus].st_iic_bus_inst.IIC_SDA_PORT == NULL) return CORE_I2C_ERROR;
    IICSendNotAck(&st_i2c_port[bus].st_iic_bus_inst);
    return CORE_I2C_OK;
}

/**
 * @brief core_i2c_soft_send_byte
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
en_core_i2c_status_t core_i2c_soft_send_byte(en_core_i2c_bus_t bus,uint8_t data)
{
    if (bus >= CORE_I2C_BUS_MAX || st_i2c_port[bus].st_iic_bus_inst.IIC_SDA_PORT == NULL) return CORE_I2C_ERROR;
    IICSendByte(&st_i2c_port[bus].st_iic_bus_inst, data);
    return CORE_I2C_OK;
}

/**
 * @brief core_i2c_soft_receive_byte
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
en_core_i2c_status_t core_i2c_soft_receive_byte(en_core_i2c_bus_t bus,uint8_t * const data)
{
    if (bus >= CORE_I2C_BUS_MAX || st_i2c_port[bus].st_iic_bus_inst.IIC_SDA_PORT == NULL) return CORE_I2C_ERROR;
    *data = IICReceiveByte(&st_i2c_port[bus].st_iic_bus_inst);
    return CORE_I2C_OK;
}
/**
 * @brief I2C_software_Init
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
static en_core_i2c_status_t core_i2c_software_init(en_core_i2c_bus_t bus)
{
    if (bus >= CORE_I2C_BUS_MAX || st_i2c_port[bus].st_iic_bus_inst.IIC_SDA_PORT == NULL) return CORE_I2C_ERROR;
    GPIO_InitTypeDef GPIO_InitStructure = {0};

	__HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStructure.Pin = st_i2c_port[bus].st_iic_bus_inst.IIC_SDA_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(st_i2c_port[bus].st_iic_bus_inst.IIC_SDA_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = st_i2c_port[bus].st_iic_bus_inst.IIC_SCL_PIN ;
    HAL_GPIO_Init(st_i2c_port[bus].st_iic_bus_inst.IIC_SCL_PORT, &GPIO_InitStructure);
}

/**
 * @brief user_com_switch
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * */
static void core_i2c_switch(en_core_i2c_bus_t bus, en_i2c_state_t state)
{
	if (bus >= CORE_I2C_BUS_MAX || st_i2c_port[bus].st_iic_bus_inst.IIC_SDA_PORT == NULL) return;
	if(st_i2c_port[bus].en_i2c_state == state)
  {
    //相等，不切换
  }
  else
  {
    if(EN_HARDWARE_I2C == state)
    {
        __HAL_RCC_I2C1_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);
        //切换硬件I2C
        MX_I2C1_Init();
		st_i2c_port[bus].en_i2c_state = EN_HARDWARE_I2C;
    }
    else
    {
      /*切换软件I2C
      需要先把硬件I2C停掉
      停用I2C外设*/
      HAL_I2C_DeInit(st_i2c_port[bus].st_I2C_HandleTypeDef);
      // 禁用I2C时钟
      __HAL_RCC_I2C1_CLK_DISABLE();

      core_i2c_software_init(bus);
		
	  st_i2c_port[bus].en_i2c_state = EN_SOFTWARE_I2C;
    }
  }
}


