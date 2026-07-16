/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file lvgl_sensor_interface.h
 * 
 * @par dependencies 
 * - user_sensor.h
 * - user_init.h
 * 
 * @author ssj
 * 
 * @brief LVGL与传感器数据交互接口
 * 
 * Processing flow:
 * 
 * LVGL界面切换时调用相应接口启动/停止传感器采样
 * LVGL需要数据时调用读取接口获取最新数据
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
#ifndef __LVGL_SENSOR_INTERFACE_H__
#define __LVGL_SENSOR_INTERFACE_H__

//******************************** Includes *********************************//
#include "user_sensor.h"
#include "user_init.h"
#include "osal.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//
/* LVGL事件类型定义 */
typedef enum {
    LVGL_EVENT_UI_ENTER_WEATHER = 0,    /* 进入天气界面 */
    LVGL_EVENT_UI_EXIT_WEATHER,         /* 退出天气界面 */
    LVGL_EVENT_UI_ENTER_SPORT,          /* 进入运动界面 */
    LVGL_EVENT_UI_EXIT_SPORT,           /* 退出运动界面 */
    LVGL_EVENT_DATA_REQUEST             /* 数据请求 */
} lvgl_sensor_event_t;

/* 传感器数据结构 */
typedef struct {
    float temperature;      /* 温度 */
    float humidity;         /* 湿度 */
    uint32_t timestamp;     /* 时间戳 */
    bool data_valid;        /* 数据有效性 */
} lvgl_sensor_data_t;

//******************************** Defines **********************************//

//******************************** Declaring ********************************//

/**
 * @brief LVGL界面切换到天气界面时调用
 * @param[in] None
 * @param[out] None
 * @return None
 * @note 启动温湿度传感器采样
 */
void lvgl_weather_screen_enter(void);

/**
 * @brief LVGL界面退出天气界面时调用
 * @param[in] None
 * @param[out] None
 * @return None
 * @note 停止温湿度传感器采样
 */
void lvgl_weather_screen_exit(void);

/**
 * @brief LVGL界面切换到运动界面时调用
 * @param[in] None
 * @param[out] None
 * @return None
 * @note 启动运动传感器采样
 */
void lvgl_sport_screen_enter(void);

/**
 * @brief LVGL界面退出运动界面时调用
 * @param[in] None
 * @param[out] None
 * @return None
 * @note 停止运动传感器采样
 */
void lvgl_sport_screen_exit(void);

/**
 * @brief LVGL获取温度数据
 * @param[in] None
 * @param[out] None
 * @return float 温度值(°C)
 * @note 线程安全的温度数据获取
 */
float lvgl_get_temperature(void);

/**
 * @brief LVGL获取湿度数据
 * @param[in] None
 * @param[out] None
 * @return float 湿度值(%)
 * @note 线程安全的湿度数据获取
 */
float lvgl_get_humidity(void);

/**
 * @brief LVGL获取传感器数据包
 * @param[in] None
 * @param[out] data 传感器数据结构指针
 * @return bool true-成功, false-失败
 * @note 一次性获取所有传感器数据
 */
bool lvgl_get_sensor_data(lvgl_sensor_data_t *data);

/**
 * @brief 检查传感器数据是否有效
 * @param[in] None
 * @param[out] None
 * @return bool true-有效, false-无效
 * @note 用于LVGL判断是否需要更新显示
 */
bool lvgl_is_sensor_data_valid(void);

/**
 * @brief 强制请求传感器数据更新
 * @param[in] sensor_mask 传感器掩码
 * @param[out] None
 * @return bool true-成功, false-失败
 * @note 用于LVGL主动请求数据更新
 */
bool lvgl_request_sensor_update(uint32_t sensor_mask);

//******************************** Declaring ********************************//

#endif /* __LVGL_SENSOR_INTERFACE_H__ */