/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file bsp_adapter_port_touchpad.c
 * 
 * @par dependencies 
 * - bsp_adapter_port_touchpad.h
 * 
 * @author ssj
 * 
 * @brief 
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
//******************************** Includes *********************************//
#include "bsp_adapter_port_touchpad.h"
#include "bsp_wrapper_touchpad.h"
#include "osal.h"
#include "bsp_cst816t_driver.h"
#include "bsp_cst816t_link.h"
#include "bsp_cst816t_calibration.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//
//******************************** Defines **********************************//

//******************************** Variables ********************************//
bsp_cst816t_driver_t cst816t_driver_instance;

cst816_timebase_interface_t g_timebase_instance = {
    .pf_get_tick_count = osal_task_get_tick_count,
};

cst816__yield_interface_t g_yield_instance = {
    .pf_rtos_yield = osal_task_delay_ms,
};

cst816__iic_driver_interface_t g_iic_driver_instance = {
    .hi2c = &hi2c3,
    .pf_iic_init         = iic_driver_init,
    .pf_iic_deinit       = iic_driver_deinit,
    .pf_iic_mem_write    = iic_mem_write,
    .pf_iic_mem_read     = iic_mem_read,
    .pf_iic_mem_read_dma = iic_mem_read_dma,
};

gpio_opt_interface_t gpio_opt_instance = {
    .pf_write_reset_pin = gpio_opt_write_reset_pin,
};

//******************************** Variables ********************************//

//******************************** Functions ********************************//
/***********************************************************************************
 *                 Static Declarations For temphumionment
 ***********************************************************************************/
static void touchpad_drv_init(touchpad_drv_t *dev);
static void touchpad_drv_deinit(touchpad_drv_t *dev);
static uint8_t touchpad_drv_get_finger_num(touchpad_drv_t *dev,\
                                            uint8_t *p_finger_num);

static uint8_t touchpad_drv_get_xy_axis(touchpad_drv_t *dev,\
                                        int16_t *p_x, \
                                        int16_t *p_y);
/* External variables */
extern void (*pf_int_interrupt_callback)(void *, void *);

/*
* @brief Register the callback function for mpuxxx INT interrupt
* @param callback: The callback function
*/

/***********************************************************************************
 *                 Public Implements
 ***********************************************************************************/
void drv_adapter_touchpad_register(void)
{
    touchpad_drv_t _touchpad_drv = {
        .idx = 0,
        .dev_id = 0,
        .touchpad_drv_init = touchpad_drv_init,
        .touchpad_drv_deinit = touchpad_drv_deinit,
        .touchpad_drv_get_finger_num = touchpad_drv_get_finger_num,
        .touchpad_drv_get_xy_axis = touchpad_drv_get_xy_axis
    };

    drv_adapter_touchpad_reg(0, &_touchpad_drv);
}

/***********************************************************************************
 *                 Static Implements for touchpad
 ***********************************************************************************/
static void touchpad_drv_init(touchpad_drv_t *dev)
{
  bsp_cst816t_inst(&cst816t_driver_instance,
    &g_timebase_instance,
#ifdef OS_SUPPORTING
    &g_yield_instance,
#endif /* OS_SUPPORTING */
    &g_iic_driver_instance,
    &gpio_opt_instance,
    &pf_int_interrupt_callback);
}

static void touchpad_drv_deinit(touchpad_drv_t *dev)
{
  ;
}

static uint8_t touchpad_drv_get_finger_num(touchpad_drv_t *dev,\
                                            uint8_t *p_finger_num)
{
  uint8_t ret;
  ret = cst816t_driver_instance.pf_cst816_get_finger_num\
        (&cst816t_driver_instance, p_finger_num);
  return ret;
}

static uint8_t touchpad_drv_get_xy_axis(touchpad_drv_t *dev,\
                                        int16_t *p_x, \
                                        int16_t *p_y)
{
  cst816_xy_t get_point;
  uint8_t ret = cst816t_driver_instance.pf_cst816_get_xy_axis\
        (&cst816t_driver_instance,&get_point);
  
  // 应用触摸校准转换 (适配180度旋转)
  touch_calibration_t *p_calibration = touch_calibration_get_instance();
  if (p_calibration != NULL && p_calibration->is_calibrated) {
    uint16_t calibrated_x, calibrated_y;
    calibration_status_t status = touch_calibration_apply_matrix(p_calibration,
                                                                 get_point.x_pos, get_point.y_pos,
                                                                 &calibrated_x, &calibrated_y);
    if (status == CALIBRATION_SUCCESS) {
      (*p_x) = (int16_t)calibrated_x;
      (*p_y) = (int16_t)calibrated_y;
    } else {
      (*p_x) = get_point.x_pos;
      (*p_y) = get_point.y_pos;
    }
  } else {
    // 如果没有校准，直接返回原始坐标
    (*p_x) = get_point.x_pos;
    (*p_y) = get_point.y_pos;
  }
  
  return ret;
}

//******************************** Functions ********************************//
