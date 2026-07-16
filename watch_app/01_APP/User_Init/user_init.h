/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file Debug.h
 * 
 * @par dependencies 
 * - Debug.h
 * 
 * @author ssj
 * 
 * @brief Provide all the debugging tools in this project.
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
#ifndef __USER_INIT_H__  //Avoid repeated including same files later
#define __USER_INIT_H__

//******************************** Includes *********************************//
#include "osal.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Declaring ********************************//
void UserAppTask_Init(void);

/* 全局队列句柄声明 */
extern osal_queue_handle_t g_sensor_data_queue;
extern osal_queue_handle_t g_ui_event_queue;

/* 全局互斥锁声明 */
extern osal_mutex_handle_t g_sensor_data_mutex;

/* 系统状态全局变量声明 */
typedef enum {
    UI_STATE_WATCHFACE = 0,
    UI_STATE_HEALTH,
    UI_STATE_SPORT,
    UI_STATE_SETTINGS,
    UI_STATE_WEATHER,
    UI_STATE_SLEEP
} ui_state_t;

typedef struct {
    ui_state_t current_ui_state;
    float temperature;
    float humidity;
    uint8_t battery_level;
    uint32_t system_tick;
} system_status_t;

extern system_status_t g_system_status;
//******************************** Declaring ********************************//

#endif /* __EC_BSP_AHT21_DRIVER_H__ */
