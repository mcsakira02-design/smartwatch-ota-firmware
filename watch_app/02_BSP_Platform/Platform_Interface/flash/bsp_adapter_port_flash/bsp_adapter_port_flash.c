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
#include "main.h"
#include "osal.h"
#include "bsp_adapter_port_flash.h"
#include "bsp_wrapper_flash.h"
#include "bsp_flash_handler.h"
#include "Debug.h"
#include "spi.h"
#include "stdarg.h"
#include "spi_port.h"
#include "User_Task_Reso_Config.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//
//******************************** Defines **********************************//

//******************************** Variables ********************************//
osal_task_handle_t flash_handler_task;
//******************************** Variables ********************************//

//******************************** Functions ********************************//
/***********************************************************************************
 *                 Static Declarations For temphumionment
 ***********************************************************************************/
static void externflash_drv_init(externflash_drv_t *dev);
static void externflash_drv_deinit(externflash_drv_t *dev);
static void externflash_drv_read(externflash_drv_t *dev, uint32_t addr, uint32_t size, uint8_t *p_buf);
static void externflash_drv_write(externflash_drv_t *dev, uint32_t addr, uint32_t size, uint8_t *p_buf);
static void externflash_drv_write_noerase(externflash_drv_t *dev);
static void externflash_drv_erasechip(externflash_drv_t *dev);
static void externflash_drv_erasesector(externflash_drv_t *dev);
static void externflash_drv_wakeup(externflash_drv_t *dev);
static void externflash_drv_sleep(externflash_drv_t *dev);
static void externflash_drv_test(externflash_drv_t *dev);
/***********************************************************************************
 *                 Public Implements
 ***********************************************************************************/


void drv_adapter_externflash_register(void)
{
    externflash_drv_t _externflash_drv = {
        .idx = 0,
        .dev_id = 0,
        .externflash_drv_init = externflash_drv_init,
        .externflash_drv_deinit = externflash_drv_deinit,
        .externflash_drv_read = externflash_drv_read,
        .externflash_drv_write = externflash_drv_write,
        .externflash_drv_write_noerase = externflash_drv_write_noerase,
        .externflash_drv_erasechip = externflash_drv_erasechip,
        .externflash_drv_erasesector = externflash_drv_erasesector,
        .externflash_drv_wakeup = externflash_drv_wakeup,
        .externflash_drv_sleep = externflash_drv_sleep,
        .externflash_drv_test = externflash_drv_test
    };

    drv_adapter_externflash_reg(0, &_externflash_drv);
}

/***********************************************************************************
 *                 Static Implements for Display
 ***********************************************************************************/
uint8_t spi_cs_set(void)
{
  SENSOR_SPI1_HARDWARE_WRITE_CS(GPIO_PIN_RESET);
  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
  return 0;
}

uint8_t spi_cs_deset(void)
{
  SENSOR_SPI1_HARDWARE_WRITE_CS(GPIO_PIN_SET);
  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
  return 0;
}

uint8_t spi_write_byte(uint8_t data)
{
  uint8_t ret;
  ret = SENSOR_SPI1_HARDWARE_TRANSMIT((uint8_t *)&data, 1, HAL_MAX_DELAY);
  //ret = HAL_SPI_Transmit(&hspi1, (uint8_t *)&data, 1, HAL_MAX_DELAY);
  return ret;
}

uint8_t spi_read_byte(void)
{
  uint8_t data;
  SENSOR_SPI1_HARDWARE_RECEIVE((uint8_t *)&data, 1, HAL_MAX_DELAY);
  //HAL_SPI_Receive(&hspi1, (uint8_t *)&data, 1, HAL_MAX_DELAY);
  return data;
}
extern osal_sema_handle_t userExtFlashSemaHandle;
void read_finish_callback(void * p_buff)
{
  /*数据采集完成，释放信号量*/
  osal_sema_give(userExtFlashSemaHandle);
}

void write_finish_callback(void * p_buff)
{
  __NOP;
}

static void externflash_drv_init(externflash_drv_t *dev)
{



}

static void externflash_drv_deinit(externflash_drv_t *dev)
{
    //销毁线程
}


static void externflash_drv_read(externflash_drv_t *dev, \
                                uint32_t addr, \
                                uint32_t size, \
                                uint8_t *p_buf)
{
    flash_handler_event_t read_even ={
        .addr = addr,
        .size = size,
        .p_data = p_buf,
        .type = FLASH_HANDLER_EVENT_READ,
        .pf_callback = read_finish_callback,
    };
    flash_handler_event_put(&read_even);
}

static void externflash_drv_write(externflash_drv_t *dev, \
                                  uint32_t addr, \
                                  uint32_t size, \
                                  uint8_t *p_buf)
{
    flash_handler_event_t write_even ={
        .addr = addr,
        .size = size,
        .p_data = p_buf,
        .type = FLASH_HANDLER_EVENT_WRITE,
        .pf_callback = write_finish_callback,
    };
    flash_handler_event_put(&write_even);
}

static void externflash_drv_write_noerase(externflash_drv_t *dev)
{

}

static void externflash_drv_erasechip(externflash_drv_t *dev)
{

}

static void externflash_drv_erasesector(externflash_drv_t *dev)
{

}

static void externflash_drv_wakeup(externflash_drv_t *dev)
{

}

static void externflash_drv_sleep(externflash_drv_t *dev)
{

}

static void externflash_drv_test(externflash_drv_t *dev)
{

}

//外部接口实现挂载
static spi_w25q64_interface_t spi_w25q64_instance =
{
    .pf_spi_init = MX_SPI1_Init,
    .pf_spi_deinit = NULL,
    .pf_spi_cs_set = spi_cs_set,
    .pf_spi_cs_deset = spi_cs_deset,
    .pf_spi_write_byte = spi_write_byte,
    .pf_spi_read_byte = spi_read_byte,
    .pf_critical_enter = osal_enter_critical,
    .pf_critical_exit  = osal_exit_critical,
};

static w25qxx_timebase_interface_t timebase_instance =
{
    .pf_tick_count_get = HAL_GetTick,
};
static w25qxx_os_delay_interface_t os_delay_instance =
{
    .pf_os_delay_ms = osal_task_delay_ms,
};

static flash_handler_os_interface_t flash_handler_os_instance =
{
    .pf_os_delay         = osal_task_delay_ms,
    .pf_os_queue_create  = osal_queue_create,
    .pf_os_queue_receive = osal_queue_receive,
    .pf_os_queue_send    = osal_queue_send
};

flash_handler_all_input_arg_t flash_handler_all_input_arg =
{
    .p_spi_w25q64_instance  = &spi_w25q64_instance,
    .p_timebase_instance    = &timebase_instance,
    .p_os_instance          = &flash_handler_os_instance,
    .p_os_delay_instance    = &os_delay_instance,
};

//******************************** Functions ********************************//
