/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file User_Task_Reso_Config.h
 * 
 * @par dependencies 
 * - User_Task_Reso_Config.h
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
#ifndef __USER_TASK_RESO_CONFIG_H__  //Avoid repeated including same files later
#define __USER_TASK_RESO_CONFIG_H__

//******************************** Includes *********************************//
#include "FreeRTOSConfig.h"
#include"osal.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//

#define USER_TASK_NUM          5
#define USER_QUEUE_NUM         3    // 队列资源数量
#define USER_MUTEX_NUM         4    // 互斥锁资源数量
#define USER_SEMA_NUM          2    // 信号量资源数量

//Task  Priority Classification
#define PRI_EMERGENCY     (configMAX_PRIORITIES-1)  // 紧急事件（最高）（保留2个优先级）
#define PRI_HARD_REALTIME (PRI_EMERGENCY-4)         // 硬件实时任务（传感器采样）（4个优先级跨度）
#define PRI_SOFT_REALTIME (PRI_HARD_REALTIME-5)     // 软件实时任务（协议解析）（5个优先级跨度）
#define PRI_NORMAL        (PRI_SOFT_REALTIME-7)     // 常规业务任务  
#define PRI_BACKGROUND    (1)                       // 后台任务（日志上传）

//******************************** Defines **********************************//
//******************************** Typedef **********************************//
// 任务配置结构体
typedef struct 
{
    const char *        task_name;
    osal_task_entry     func_pointer; 
    size_t              stack_size;
    osal_priority_t     priority; 
    osal_task_handle_t  task_handle;
    void *              argument;
}st_usertaskcfg_t;

// 队列配置结构体
typedef struct
{
    const char *        queue_name;     // 队列名称
    size_t              queue_depth;   // 队列深度
    size_t              data_size;     // 数据大小
    osal_queue_handle_t queue_handle;  // 队列句柄
}st_userqueuecfg_t;

// 互斥锁配置结构体
typedef struct
{
    const char *        mutex_name;     // 互斥锁名称
    osal_mutex_handle_t mutex_handle;   // 互斥锁句柄
}st_usermutexcfg_t;

// 信号量配置结构体
typedef struct
{
    const char *        sema_name;      // 信号量名称
    uint32_t            max_count;      // 最大计数值(计数信号量用)
    uint32_t            init_count;     // 初始计数值(计数信号量用)
    bool                is_binary;      // 是否为二进制信号量
    osal_sema_handle_t  sema_handle;    // 信号量句柄
}st_usersemacfg_t;

//******************************** Typedef **********************************//

//******************************** Declaring ********************************//
// 任务配置数组声明
extern st_usertaskcfg_t st_usertaskcfg[USER_TASK_NUM];

// 队列配置数组声明
extern st_userqueuecfg_t st_userqueuecfg[USER_QUEUE_NUM];

// 互斥锁配置数组声明
extern st_usermutexcfg_t st_usermutexcfg[USER_MUTEX_NUM];

// 信号量配置数组声明
extern st_usersemacfg_t st_usersemacfg[USER_SEMA_NUM];

// OS资源初始化函数声明
int32_t user_os_resources_init(void);
void user_os_resources_deinit(void);

//******************************** Declaring ********************************//

#endif /* __USER_TASK_RESO_CONFIG_H__ */
