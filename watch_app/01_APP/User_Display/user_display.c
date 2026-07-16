/******************************************************************************
 *  
 *
 * All Rights Reserved.
 *
 * @file User_Display.c
 *
 * @par dependencies
 * - User_Display.h
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
#include "User_Display.h"

#include "osal.h"
#include "stdio.h"

#include "lvgl.h"
#include "lvgl/examples/porting/lv_port_disp_template.h"
#include "lvgl/examples/porting/lv_port_indev_template.h"
#include "LVGL_ui/gui_guider.h"
#include "LVGL_ui/UI_Resource.h"
#include "User_ExternflashManage.h"
#include "elog.h"
// test
//#include "drv_adapter_display.h"
// 触摸屏校准相关
#include "bsp_cst816t_calibration.h"
#include "touch_calibration_ui.h"
#include "Debug.h"
// LVGL传感器接口
#include "lvgl_sensor_interface.h"
#include "user_init.h"
//******************************** Includes *********************************//

//******************************** Variable **********************************//
lv_ui guider_ui;
//extern  uint8_t lvgl_data[MAX_ARRAY_SIZE];
//extern uint8_t g_au8_lvgldata[LVGL_DATA_MAX_SIZE];

/* LVGL显示更新相关变量 */
static uint32_t display_update_counter = 0;
static uint32_t sensor_data_update_interval = 200; /* 1秒更新一次传感器显示 (5ms * 200) */
//******************************** Variable **********************************//

//******************************** Function definitions ********************************//
uint16_t cycle_cnt = 200;
extern void comprehensive_usage_example(void);
extern void user_Sensor_display(void);
/**
 * @brief 检查并执行触摸屏校准
 * @return true 校准完成或跳过，false 校准失败
 */
static bool check_and_calibrate_touchscreen(void)
{
    touch_calibration_t *p_calibration = touch_calibration_get_instance();
    
    // 初始化校准模块
    if (touch_calibration_init(p_calibration) != CALIBRATION_SUCCESS) {
#ifdef DEBUG_LCDCALIBRATE
        log_d("Touch calibration init failed\n");
#endif
        return false;
    }
    
    // 尝试从Flash加载校准参数
    calibration_status_t load_status = touch_calibration_load_from_flash(p_calibration);
    
    if (load_status == CALIBRATION_SUCCESS && p_calibration->is_calibrated) {
#ifdef DEBUG_LCDCALIBRATE
        log_d("Touch calibration loaded from flash\n");
#endif
        return true;  // 已有有效校准参数
    }
#ifdef DEBUG_LCDCALIBRATE
    log_d("No valid calibration found, starting calibration process\n");
#endif
    
    
    // 初始化校准UI
    if (touch_calibration_ui_init() != CALIBRATION_SUCCESS) {
#ifdef DEBUG_LCDCALIBRATE
    log_d("Touch calibration UI init failed\n");
#endif
        return false;
    }
    
    // 开始校准流程
    touch_calibration_ui_start();
    
    // 等待校准完成 (这里可以添加超时机制)
    osal_tick_type_t timeout_ticks = 60000;  // 60秒超时 (假设1ms一个tick)
    osal_tick_type_t start_tick = osal_task_get_tick_count();
    
    while (!p_calibration->is_calibrated) {
        lv_task_handler();
        osal_task_delay_ms(10);
        
        // 检查超时
        if ((osal_task_get_tick_count() - start_tick) > timeout_ticks) {
#ifdef DEBUG_LCDCALIBRATE
            log_d("Touch calibration timeout\n");
#endif
            touch_calibration_ui_cleanup();
            return false;
        }
    }
#ifdef DEBUG_LCDCALIBRATE
    log_d("Touch calibration completed successfully\n");
#endif
    
    
    // 保存校准参数到Flash
    if (touch_calibration_save_to_flash(p_calibration) != CALIBRATION_SUCCESS) {
#ifdef DEBUG_LCDCALIBRATE
    log_d("Failed to save calibration to flash\n");
#endif
        
    }
    
    // 清理校准UI资源
    touch_calibration_ui_cleanup();
    
    return true;
}

void display_refresh_task(void *argument)
{
    /*先读数据到原有数据中*/
    // lvgl init
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    
    // 在设置UI之前进行触摸屏校准
    if (!check_and_calibrate_touchscreen()) {
#ifdef DEBUG_LCDCALIBRATE
    log_d("Touch calibration failed, continuing with default settings\n");
#endif  
    }

    setup_ui(&guider_ui);

    for (;;)
    {
        lv_task_handler();
        user_Sensor_display();

        osal_task_delay_ms(5);
        // drv_adapter_display_SetBackLight(cycle_cnt);
    }
}

void user_Sensor_display(void)
{
    comprehensive_usage_example();
    /* 定期更新传感器数据显示 */
    display_update_counter++;
    if(display_update_counter >= sensor_data_update_interval)
    {
        display_update_counter = 0;
        
        /* 检查传感器数据是否有效并更新显示 */
        if(lvgl_is_sensor_data_valid())
        {
            lvgl_sensor_data_t sensor_data;
            if(lvgl_get_sensor_data(&sensor_data))
            {
#ifdef DEBUG_LVGL
                DEBUG_OUT("LVGL Display: Temp=%.1f°C, Humi=%.1f%%", 
                            sensor_data.temperature, sensor_data.humidity);
#endif
                /* 这里可以更新LVGL界面上的温湿度显示 */
                /* 例如：lv_label_set_text_fmt(temp_label, "%.1f°C", sensor_data.temperature); */
            }
        }
    }
}
//******************************** Function definitions ********************************//