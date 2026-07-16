#include "mpu6050_integration.h"
#include "bsp_mpuxxx_driver.h"
#include "bsp_mpuxxx_handler.h"
#include "circular_buffer.h"
#include "delay.h"

#include  "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "i2c.h"
#include "dma.h"

#include "i2c_port.h"
/*****************************************************************************/
// iic driver interface
mpuxxx_status_t iic_driver_init(void * iic_bus)
{
    // has already inited in main.c
    return MPUxxx_OK;
}
mpuxxx_status_t iic_driver_deinit(void *iic_bus)
{
    __HAL_RCC_I2C1_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);
    return MPUxxx_OK;
}
mpuxxx_status_t iic_mem_read(void *hi2c, 
                              uint16_t dst_address, 
                              uint16_t mem_addr, 
                              uint16_t mem_size, 
                              uint8_t  *p_data, 
                              uint16_t size, 
                              uint32_t timeout)
{
    HAL_StatusTypeDef ret = HAL_OK;
	//ret = HAL_I2C_Mem_Read(hi2c, dst_address, mem_addr, mem_size, p_data, size, timeout);
    //TODO:
    ret = SENSOR_I2C_HARDWARE_MEM_READ(dst_address, mem_addr, mem_size, p_data, size, timeout);
    if (ret != HAL_OK)
    {
        return MPUxxx_ERROR;
    }
    return MPUxxx_OK;
}
mpuxxx_status_t iic_mem_write(void *hi2c,
                               uint16_t dst_address, 
                               uint16_t mem_addr, 
                               uint16_t mem_size, 
                               uint8_t  *p_data, 
                               uint16_t size, 
                               uint32_t timeout)
{
    HAL_StatusTypeDef ret = HAL_OK;
	// ret = HAL_I2C_Mem_Write(hi2c, dst_address, mem_addr, mem_size, p_data, size, timeout);
    ret = SENSOR_I2C_HARDWARE_MEM_WRITE(dst_address, mem_addr, mem_size, p_data, size, timeout);
    if (ret != HAL_OK)
    {
        return MPUxxx_ERROR;
    }
    return MPUxxx_OK;
}
mpuxxx_status_t iic_mem_read_dma(void *hi2c, 
                                 uint16_t dst_address, 
                                 uint16_t mem_addr, 
                                 uint16_t mem_size, 
                                 uint8_t  *p_data, 
                                 uint16_t size )
{
    HAL_StatusTypeDef ret = HAL_OK;
    ret = HAL_I2C_Mem_Read_DMA(hi2c, dst_address, mem_addr, mem_size, p_data, size);
    if (ret != HAL_OK)
    {
        return MPUxxx_ERROR;
    }
    return MPUxxx_OK;
}

mpuxxx_iic_driver_interface_t iic_driver_interface = {
    .hi2c                = &hi2c1,
    .pf_iic_init         = iic_driver_init,
    .pf_iic_deinit       = iic_driver_deinit,
    .pf_iic_mem_read     = iic_mem_read,
    .pf_iic_mem_write    = iic_mem_write,
    .pf_iic_mem_read_dma = iic_mem_read_dma,
};
/*****************************************************************************/
// timebase interface
mpuxxx_timebase_interface_t timebase_interface = {
    .pf_get_tick_count = HAL_GetTick,
};
/*****************************************************************************/
// buffer interface
//buffer_interface_t buffer_interface = {
//    // .pf_circular_buffer_init = circular_buffer_init,
//    // .pf_circular_buffer_deinit = circular_buffer_deinit,
//    // .pf_circular_buffer_put = circular_buffer_put,
//    // .pf_circular_buffer_get = circular_buffer_get,
//	
//};
/*****************************************************************************/
// yield interface
#ifdef OS_SUPPORTING
mpuxxx_yield_interface_t yield_interface = {
    .pf_rtos_yield = vTaskDelay,
};
#endif
/*****************************************************************************/
// delay interface
mpuxxx_delay_interface_t delay_interface = {
    .pf_delay_init = delay_init,
    .pf_delay_us = delay_us,
    .pf_delay_ms = delay_ms,
};
/*****************************************************************************/
// os interface
#ifdef OS_SUPPORTING
mpuxxx_status_t os_queue_create(uint32_t const queue_size, 
                                uint32_t const item_size, 
                                void **queue_handle)
{
	*queue_handle = xQueueCreate(queue_size, item_size);
	return MPUxxx_OK;
}
mpuxxx_status_t os_queue_delete(void * const queue_handle)
{
    vQueueDelete(queue_handle);
    return MPUxxx_OK;
}
mpuxxx_status_t os_queue_put(void * const queue_handle,
                            void * const item, 
                            uint32_t const timeout)
{
    xQueueSend(queue_handle, item, timeout);
    return MPUxxx_OK;	
}
mpuxxx_status_t os_queue_put_isr(void * const queue_handle,
                            void * const item, 
                            long * const HigherPriorityTaskWoken)
{
    xQueueSendFromISR(queue_handle, item, HigherPriorityTaskWoken);
    return MPUxxx_OK;
}
mpuxxx_status_t os_queue_get(void * const queue_handle,
                            void * const item, 
                            uint32_t const timeout)
{
    xQueueReceive(queue_handle, item, timeout);
    return MPUxxx_OK;
}
mpuxxx_status_t os_semaphore_create_mutex(void **mutex_handle)
{
    *mutex_handle = xSemaphoreCreateMutex();
    return MPUxxx_OK;
}
mpuxxx_status_t os_semaphore_delete_mutex(void * const mutex_handle)
{
    //vQueueDelete(mutex_handle);
    return MPUxxx_OK;
}
mpuxxx_status_t os_semaphore_lock_mutex(void * const mutex_handle)
{
    xSemaphoreTake(mutex_handle, portMAX_DELAY);
    return MPUxxx_OK;
}
mpuxxx_status_t os_semaphore_unlock_mutex(void * const mutex_handle)
{
    xSemaphoreGive(mutex_handle);
    return MPUxxx_OK;
}
mpuxxx_status_t os_semaphore_create_binary(void **binary_handle)
{
    *binary_handle = xSemaphoreCreateBinary();
    return MPUxxx_OK;
}
mpuxxx_status_t os_semaphore_delete_binary(void * const binary_handle)
{
    //vQueueDelete(binary_handle);
    return MPUxxx_OK;
}
mpuxxx_status_t os_semaphore_signal_binary(void * const binary_handle)
{
    xSemaphoreTake(binary_handle, portMAX_DELAY);
    return MPUxxx_OK;
}
mpuxxx_status_t os_semaphore_wait_binary(void * const binary_handle)
{
    xSemaphoreGive(binary_handle);
    return MPUxxx_OK;
}

mpuxxx_os_interface_t os_interface = {
    .os_queue_create = os_queue_create,
    .os_queue_delete = os_queue_delete,
    .os_queue_put    = os_queue_put,
	.os_queue_put_isr= os_queue_put_isr,
    .os_queue_get    = os_queue_get,

    .os_semaphore_create_mutex = os_semaphore_create_mutex,
    .os_semaphore_delete_mutex = os_semaphore_delete_mutex,
    .os_semaphore_lock_mutex   = os_semaphore_lock_mutex,
    .os_semaphore_unlock_mutex = os_semaphore_unlock_mutex,

    .os_semaphore_create_binary = os_semaphore_create_binary,
    .os_semaphore_delete_binary = os_semaphore_delete_binary,
    .os_semaphore_wait_binary   = os_semaphore_wait_binary,
    .os_semaphore_signal_binary = os_semaphore_signal_binary,
};
#endif

/*****************************************************************************/
// bsp mpu6050 driver instance
bsp_mpuxxx_driver_t bsp_mpu6050_driver = {
    .p_iic_driver_interface = &iic_driver_interface,
    .p_timebase_interface   = &timebase_interface,
    //.p_buffer_interface     = &buffer_interface,
#ifdef OS_SUPPORTING
    .p_yield_interface      = &yield_interface,
    .p_os_interface         = &os_interface,
#endif
};

/*****************************************************************************/
// bsp mpu6050 handler input args
mpuxxx_handler_input_args_t mpu6050_input_args = {
	.p_iic_driver = &iic_driver_interface,
    .p_delay      = &delay_interface,
    .p_os         = &os_interface,
    .p_timebase   = &timebase_interface,
	.p_yield      = &yield_interface,
};


