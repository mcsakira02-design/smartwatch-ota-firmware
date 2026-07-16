/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file lvgl_sensor_interface.c
 * 
 * @par dependencies 
 * - lvgl_sensor_interface.h
 * 
 * @author ssj
 * 
 * @brief LVGL与传感器数据交互接口实现
 * 
 * Processing flow:
 * 
 * 实现LVGL与传感器模块的数据交互逻辑
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/

//******************************** Includes *********************************//
#include "lvgl_sensor_interface.h"
#include "Debug.h"
//******************************** Includes *********************************//

//******************************** Variable **********************************//
/* 数据有效性检查 */
static uint32_t last_data_timestamp = 0;
#define DATA_TIMEOUT_MS     30000   /* 30秒数据超时 */
//******************************** Variable **********************************//

//******************************** Function definitions ********************************//

/**
 * @brief LVGL界面切换到天气界面时调用
 */
void lvgl_weather_screen_enter(void)
{
    ui_state_t ui_event = UI_STATE_WEATHER;
    
#ifdef DEBUG_USER_SENSOR
    DEBUG_OUT("LVGL: Weather screen entered");
#endif
    
    /* 发送UI事件到传感器任务 */
    if(osal_queue_send(g_ui_event_queue, &ui_event, 100) != OSAL_SUCCESS)
    {
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("LVGL: Failed to send weather UI event");
#endif
    }
}

/**
 * @brief LVGL界面退出天气界面时调用
 */
void lvgl_weather_screen_exit(void)
{
    ui_state_t ui_event = UI_STATE_WATCHFACE;
    
#ifdef DEBUG_USER_SENSOR
    DEBUG_OUT("LVGL: Weather screen exited");
#endif
    
    /* 发送UI事件到传感器任务 */
    if(osal_queue_send(g_ui_event_queue, &ui_event, 100) != OSAL_SUCCESS)
    {
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("LVGL: Failed to send watchface UI event");
#endif
    }
}

/**
 * @brief LVGL界面切换到运动界面时调用
 */
void lvgl_sport_screen_enter(void)
{
    ui_state_t ui_event = UI_STATE_SPORT;
    
#ifdef DEBUG_USER_SENSOR
    DEBUG_OUT("LVGL: Sport screen entered");
#endif
    
    /* 发送UI事件到传感器任务 */
    if(osal_queue_send(g_ui_event_queue, &ui_event, 100) != OSAL_SUCCESS)
    {
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("LVGL: Failed to send sport UI event");
#endif
    }
}

/**
 * @brief LVGL界面退出运动界面时调用
 */
void lvgl_sport_screen_exit(void)
{
    ui_state_t ui_event = UI_STATE_WATCHFACE;
    
#ifdef DEBUG_USER_SENSOR
    DEBUG_OUT("LVGL: Sport screen exited");
#endif
    
    /* 发送UI事件到传感器任务 */
    if(osal_queue_send(g_ui_event_queue, &ui_event, 100) != OSAL_SUCCESS)
    {
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("LVGL: Failed to send watchface UI event");
#endif
    }
}

/**
 * @brief LVGL获取温度数据
 */
float lvgl_get_temperature(void)
{
    float temperature = 0.0f;
    
    /* 使用传感器模块提供的线程安全接口 */
    temperature = sensor_temp_read();
    
#ifdef DEBUG_USER_SENSOR
    DEBUG_OUT("LVGL: Get temperature = %.2f°C", temperature);
#endif
    
    return temperature;
}

/**
 * @brief LVGL获取湿度数据
 */
float lvgl_get_humidity(void)
{
    float humidity = 0.0f;
    
    /* 使用传感器模块提供的线程安全接口 */
    humidity = sensor_humidity_read();
    
#ifdef DEBUG_USER_SENSOR
    DEBUG_OUT("LVGL: Get humidity = %.2f%%", humidity);
#endif
    
    return humidity;
}

/**
 * @brief LVGL获取传感器数据包
 */
bool lvgl_get_sensor_data(lvgl_sensor_data_t *data)
{
    if(data == NULL)
    {
        return false;
    }
    
    /* 获取互斥锁保护 */
    if(osal_mutex_take(g_sensor_data_mutex, 100) == OSAL_SUCCESS)
    {
        data->temperature = g_system_status.temperature;
        data->humidity = g_system_status.humidity;
        data->timestamp = g_system_status.system_tick;
        data->data_valid = lvgl_is_sensor_data_valid();
        
        osal_mutex_give(g_sensor_data_mutex);
        
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("LVGL: Get sensor data - Temp: %.2f°C, Humi: %.2f%%, Valid: %d", 
                  data->temperature, data->humidity, data->data_valid);
#endif
        
        return true;
    }
    
    return false;
}

/**
 * @brief 检查传感器数据是否有效
 */
bool lvgl_is_sensor_data_valid(void)
{
    uint32_t current_time = osal_task_get_tick_count();
    uint32_t data_age;
    
    if(osal_mutex_take(g_sensor_data_mutex, 50) == OSAL_SUCCESS)
    {
        data_age = current_time - g_system_status.system_tick;
        osal_mutex_give(g_sensor_data_mutex);
        
        /* 检查数据是否在有效期内 */
        if(data_age < DATA_TIMEOUT_MS)
        {
            return true;
        }
    }
    
    return false;
}

/**
 * @brief 强制请求传感器数据更新
 */
bool lvgl_request_sensor_update(uint32_t sensor_mask)
{
    /* 这里可以实现强制更新逻辑 */
    /* 例如：发送特殊事件到传感器任务要求立即采样 */
    
#ifdef DEBUG_USER_SENSOR
    DEBUG_OUT("LVGL: Request sensor update, mask: 0x%X", sensor_mask);
#endif
    
    /* 简单实现：通过队列发送数据请求 */
    float dummy_data[2] = {0.0f, 0.0f};
    
    /* 这里可以扩展为发送特殊的请求消息 */
    /* 目前返回true表示请求已发送 */
    return true;
}

//******************************** Function definitions ********************************//