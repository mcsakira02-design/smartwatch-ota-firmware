/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file User_Init.c
 * 
 * @par dependencies 
 * - User_Init.h
 * 
 * @author ssj
 * 
 * @brief For application layer task initialization
 * 
 * Processing flow:
 * 
 * call directly.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
//******************************** Includes *********************************//
#include "user_isr_handlers.h"
#include "main.h"
#include "bsp_mpuxxx_driver.h"
#include "bsp_cst816t_driver.h"
#include "bsp_mpuxxx_handler.h"
#include "gpio_port.h"
//******************************** Includes *********************************//

//******************************** Variable **********************************//

//******************************** Variable **********************************//

//******************************** Function definitions ********************************//
void (*pf_pin_interrupt_callback)(void *, void *) = NULL;
void (*pf_dma_interrupt_callback)(void *, void *) = NULL;
void (*pf_int_interrupt_callback)(void *, void *) = NULL;

extern bsp_mpuxxx_handler_t handler_instance;
extern bsp_cst816t_driver_t cst816t_driver_instance;
// INT中断回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// INT test - 使用gpio_port接口	
	//core_gpio_write_pin(CORE_GPIO_INT_FUNC, CORE_GPIO_PIN_RESET);
	
	//log_i("HAL_GPIO_EXTI_Callback");
	
	mpuxxx_data_t mpu6050_data;

	if((GPIO_Pin == GPIO_PIN_5) && (NULL != pf_pin_interrupt_callback))
	{
		pf_pin_interrupt_callback(handler_instance.p_driver, \
								 (void *)&mpu6050_data);
		/*
		log_i("mpu6050 data: \r\n accel_x : %f, accel_y : %f, accel_z : %f \r\n gyro_x : %f, gyro_y : %f, gyro_z : %f \r\n temperature : %f \r\n ax : %f, ay : %f, az : %f\r\n gx : %f, gy : %f, gz : %f\r\n",
			  mpu6050_data.accel_x_raw,
			  mpu6050_data.accel_y_raw,
			  mpu6050_data.accel_z_raw,
			  mpu6050_data.gyro_x_raw,
			  mpu6050_data.gyro_y_raw,
			  mpu6050_data.gyro_z_raw,
			  mpu6050_data.temperature,
			  mpu6050_data.ax,
			  mpu6050_data.ay,
			  mpu6050_data.az,
			  mpu6050_data.gx,
			  mpu6050_data.gy,
			  mpu6050_data.gz);
		*/
	}
    if ((GPIO_Pin == GPIO_PIN_2) && (pf_int_interrupt_callback != NULL))
    {
        cst816_xy_t cst816_xy;
        pf_int_interrupt_callback(&cst816t_driver_instance, &cst816_xy);
    }
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c == &hi2c1)
	{
		pf_dma_interrupt_callback(handler_instance.p_driver, NULL);
	}  
}
//******************************** Function definitions ********************************//
