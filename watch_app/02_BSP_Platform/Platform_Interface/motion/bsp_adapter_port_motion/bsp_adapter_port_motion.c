/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file bsp_adapter_port_motionoment.c
 * 
 * @par dependencies 
 * - bsp_adapter_port_motionoment.h
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
#include "mpu6050_integration.h"
#include "bsp_adapter_port_motion.h"
#include "bsp_wrapper_motion.h"
#include "bsp_mpuxxx_handler.h"


//******************************** Includes *********************************//
extern mpuxxx_handler_input_args_t mpu6050_input_args;
//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//
extern bsp_mpuxxx_handler_t handler_instance;
extern circular_buffer_t circular_buf;
//******************************** Variables ********************************//

//******************************** Functions ********************************//
/***********************************************************************************
 *                 Static Declarations For motiononment
 ***********************************************************************************/
static void motion_drv_init(motion_drv_t *dev);
static void motion_drv_deinit(motion_drv_t *dev);
static uint8_t motion_drv_getreqstate(motion_drv_t *dev);
static uint8_t * motion_drv_readdata(motion_drv_t *dev);
static void motion_drv_readdataend(motion_drv_t *dev);
/***********************************************************************************
 *                 Public Implements
 ***********************************************************************************/
void drv_adapter_motion_register(void)
{
    motion_drv_t _motion_drv = {
        .idx = 0,
        .dev_id = 0,
        .motion_drv_init = motion_drv_init,
        .motion_drv_deinit = motion_drv_deinit,
        .motion_drv_getreqstate = motion_drv_getreqstate,
        .motion_drv_readdata = motion_drv_readdata,
        .motion_drv_readdataend = motion_drv_readdataend,
    };

    drv_adapter_motion_reg(0, &_motion_drv);
}

/***********************************************************************************
 *                 Static Implements for Display
 ***********************************************************************************/
static void motion_drv_init(motion_drv_t *dev)
{
    //Handler线程已完成

}

static void motion_drv_deinit(motion_drv_t *dev)
{
    //销毁线程
}
static uint8_t motion_drv_getreqstate(motion_drv_t *dev)
{
	uint8_t data = 0;
    mpuxxx_status_t ret = MPUxxx_OK;
    //等待队列唤醒
    ret = handler_instance.p_input_args->p_os->os_queue_get\
                    ( handler_instance.p_unpack_queue_handle,
                                                &data,
                                                0xffffffff );
#ifdef DEBUG_SENSOR_ADAPTER_PORT_MOTION
	DEBUG_OUT("unpack_task: data = %d\n", data);
#endif
    return (uint8_t)ret;
}

static uint8_t * motion_drv_readdata(motion_drv_t *dev)
{
    uint8_t *addr = circular_buf.pfget_rbuffer_addr(&circular_buf);

    return addr;
}

static void motion_drv_readdataend(motion_drv_t *dev)
{
    circular_buf.pfdata_readed(&circular_buf);
}