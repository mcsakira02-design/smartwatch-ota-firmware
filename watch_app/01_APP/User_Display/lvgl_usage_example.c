/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file lvgl_usage_example.c
 * 
 * @par dependencies 
 * - lvgl_sensor_interface.h
 * 
 * @author ssj
 * 
 * @brief LVGL传感器接口使用示例
 * 
 * Processing flow:
 * 
 * 演示如何在LVGL界面中使用传感器数据接口
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/

//******************************** Includes *********************************//
#include "lvgl_sensor_interface.h"
#include "Debug.h"
// #include "lvgl.h"  // 实际项目中需要包含LVGL头文件
//******************************** Includes *********************************//

//******************************** Variable **********************************//
/* 模拟LVGL标签对象 */
// lv_obj_t *temp_label = NULL;
// lv_obj_t *humi_label = NULL;

/* 数据更新标志 */
static bool need_update_display = false;
//******************************** Variable **********************************//

//******************************** Function definitions ********************************//

/**
 * @brief 模拟LVGL天气界面创建函数
 * @note 实际项目中这应该是LVGL的界面创建函数
 */
void weather_screen_create(void)
{
    /* 模拟创建温度和湿度显示标签 */
    // temp_label = lv_label_create(lv_scr_act());
    // humi_label = lv_label_create(lv_scr_act());
    
    /* 界面进入时启动传感器采样 */
    lvgl_weather_screen_enter();
    
#ifdef DEBUG_USER_SENSOR
    DEBUG_OUT("Weather screen created and sensor sampling started");
#endif
}

/**
 * @brief 模拟LVGL天气界面销毁函数
 */
void weather_screen_destroy(void)
{
    /* 界面退出时停止传感器采样 */
    lvgl_weather_screen_exit();
    
#ifdef DEBUG_USER_SENSOR
    DEBUG_OUT("Weather screen destroyed and sensor sampling stopped");
#endif
}

/**
 * @brief 模拟LVGL定时器回调函数 - 更新温湿度显示
 * @note 实际项目中这应该是LVGL的定时器回调
 */
void weather_display_update_timer_cb(void)
{
    lvgl_sensor_data_t sensor_data;
    char temp_str[32];
    char humi_str[32];
    
    /* 检查数据是否有效 */
    if(!lvgl_is_sensor_data_valid())
    {
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("Sensor data is not valid, skip update");
#endif
        return;
    }
    
    /* 获取传感器数据 */
    if(lvgl_get_sensor_data(&sensor_data))
    {
        /* 格式化显示字符串 */
        snprintf(temp_str, sizeof(temp_str), "温度: %.1f°C", sensor_data.temperature);
        snprintf(humi_str, sizeof(humi_str), "湿度: %.1f%%", sensor_data.humidity);
        
        /* 更新LVGL标签显示 */
        // lv_label_set_text(temp_label, temp_str);
        // lv_label_set_text(humi_label, humi_str);
        
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("Display updated: %s, %s", temp_str, humi_str);
#endif
    }
    else
    {
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("Failed to get sensor data");
#endif
    }
}

/**
 * @brief 模拟LVGL按钮事件回调 - 手动刷新数据
 */
void refresh_button_event_cb(void)
{
    /* 强制请求传感器数据更新 */
    if(lvgl_request_sensor_update(SENSOR_TEMP | SENSOR_HUMIDITY))
    {
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("Manual refresh requested");
#endif
        
        /* 延时后更新显示 */
        // lv_timer_create(weather_display_update_timer_cb, 1000, NULL);
    }
}

/**
 * @brief 模拟运动界面的传感器使用
 */
void sport_screen_sensor_usage(void)
{
    /* 进入运动界面 */
    lvgl_sport_screen_enter();
    
    /* 模拟运动数据显示更新 */
    // 这里可以添加运动传感器数据的获取和显示逻辑
    
#ifdef DEBUG_USER_SENSOR
    DEBUG_OUT("Sport screen sensor usage example");
#endif
    
    /* 退出运动界面 */
    lvgl_sport_screen_exit();
}

/**
 * @brief 简单的温度获取示例
 */
void simple_temperature_example(void)
{
    float temperature;
    
    /* 直接获取温度数据 */
    temperature = lvgl_get_temperature();
    
    /* 检查温度范围并显示警告 */
    if(temperature > 35.0f)
    {
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("High temperature warning: %.1f°C", temperature);
#endif
        /* 可以在这里显示高温警告 */
    }
    else if(temperature < 0.0f)
    {
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("Low temperature warning: %.1f°C", temperature);
#endif
        /* 可以在这里显示低温警告 */
    }
    else
    {
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("Normal temperature: %.1f°C", temperature);
#endif
    }
}

/**
 * @brief 综合使用示例
 */
void comprehensive_usage_example(void)
{
#ifdef DEBUG_USER_SENSOR
    DEBUG_OUT("=== LVGL Sensor Interface Usage Example ===");
#endif
    
    /* 1. 创建天气界面并启动传感器 */
    weather_screen_create();
    
    /* 2. 模拟等待数据采集 */
    // 这里应该是LVGL的事件循环
    
    /* 3. 更新显示 */
    weather_display_update_timer_cb();
    
    /* 4. 简单温度检查 */
    simple_temperature_example();
    
    /* 5. 运动界面使用示例 */
    sport_screen_sensor_usage();
    
    /* 6. 销毁界面并停止传感器 */
    weather_screen_destroy();
    
#ifdef DEBUG_USER_SENSOR
    DEBUG_OUT("=== Example completed ===");
#endif
}

//******************************** Function definitions ********************************//