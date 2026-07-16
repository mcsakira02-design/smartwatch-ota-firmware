/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file User_Task_Reso_Config.c
 * 
 * @par dependencies
 * - User_Task_Reso_Config.c
 * 
 * @author ssj
 * 
 * @brief 表驱动的OS资源管理配置文件
 *        包含任务、队列、互斥锁、信号量等所有OS资源的统一配置管理
 * 
 * Processing flow:
 * 1. 在应用初始化时调用 user_os_resources_init() 创建所有OS资源
 * 2. 通过配置数组访问各种OS资源句柄
 * 3. 在系统退出时调用 user_os_resources_deinit() 释放资源
 * 
 * Usage Example:
 * // 初始化所有OS资源
 * if(user_os_resources_init() == 0) {
 *     // 使用队列发送数据
 *     uint32_t data = 0x1234;
 *     osal_queue_send(st_userqueuecfg[0].queue_handle, &data, 100);
 *     
 *     // 使用互斥锁保护资源
 *     osal_mutex_take(st_usermutexcfg[0].mutex_handle, OSAL_MAX_DELAY);
 *     // ... 访问共享资源 ...
 *     osal_mutex_give(st_usermutexcfg[0].mutex_handle);
 *     
 *     // 使用信号量同步
 *     osal_sema_take(st_usersemacfg[0].sema_handle, OSAL_MAX_DELAY);
 * }
 * 
 * @version V2.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
//******************************** Includes *********************************//
#include "user_task_reso_config.h"
#include "osal.h"
#include "bsp_temp_humi_xxx_handler.h"
#include "bsp_mpuxxx_handler.h"
#include "bsp_flash_handler.h"
//******************************** Includes *********************************//

//******************************** Variable **********************************//
osal_task_handle_t userSensorHandle;
osal_task_handle_t userStorgeHandle;
osal_task_handle_t LVGLTaskHandle;
extern temp_humi_handler_all_input_arg_t input_arg;
extern mpuxxx_handler_input_args_t mpu6050_input_args;
extern flash_handler_all_input_arg_t flash_handler_all_input_arg;

// 队列配置数组 - 用于线程间数据传输
st_userqueuecfg_t st_userqueuecfg[USER_QUEUE_NUM] = 
{
/*   队列名称           队列深度  数据大小        队列句柄  描述                    */
    {"SensorDataQueue",  10,      sizeof(uint32_t), NULL},//    "传感器数据队列"},
    {"StorageQueue",     5,       sizeof(uint32_t), NULL},//    "存储管理队列"},
    {"DisplayQueue",     8,       sizeof(uint32_t), NULL},//    "显示刷新队列"}
};

// 互斥锁配置数组 - 用于资源保护
st_usermutexcfg_t st_usermutexcfg[USER_MUTEX_NUM] = 
{
/*   互斥锁名称        互斥锁句柄        描述                    */
    {"FlashMutex",      NULL},//      "外部Flash访问保护"},
    {"SensorMutex",     NULL},//      "传感器数据访问保护"},
    {"DisplayMutex",    NULL},//      "显示资源访问保护"},
    {"I2CMutex",        NULL},//      "I2C总线访问保护"}
};

// 信号量配置数组 - 用于同步和计数
st_usersemacfg_t st_usersemacfg[USER_SEMA_NUM] = 
{
/*   信号量名称         最大计数  初始计数  是否二进制  信号量句柄  描述                    */
    {"DataReadySem",     1,       0,       true,      NULL},//      "数据就绪同步信号量"},
    {"StorageReadySem",  1,       1,       true,      NULL},//      "存储就绪同步信号量"}
};
//******************************** Variable **********************************//
//******************************** Function **********************************//
void temp_humi_handler_thread(void *argument);
void sensor_polling_task(void *argument);
void mpuxxx_handler_thread(void *argument);
void storage_manager_task(void *argument);
void flash_handler_thread(void *argument);
void display_refresh_task(void *argument);
//******************************** Function **********************************//
st_usertaskcfg_t st_usertaskcfg[USER_TASK_NUM] = 
{
/*    Name                  funct_ptr                       stack size   priority             		task_handle   argument*/
    {"SensorTask",          sensor_polling_task,            256,        PRI_SOFT_REALTIME,   		  NULL,         NULL},
    {"ExtFlashTask",        storage_manager_task,           256,        PRI_SOFT_REALTIME + 1,    NULL,         NULL},
    {"LVGLTask",            display_refresh_task,           256,       PRI_SOFT_REALTIME + 2,    NULL,         NULL},
    {"tempHandlerTask",     temp_humi_handler_thread,       1024,       PRI_HARD_REALTIME + 1,   	NULL,         &input_arg},
    // {"MpuHandlerTask",      mpuxxx_handler_thread,          1024,       PRI_HARD_REALTIME + 1,    NULL,         &mpu6050_input_args},
    {"ExtFlashDrv",         flash_handler_thread,           256,        PRI_HARD_REALTIME + 1,    NULL,         &flash_handler_all_input_arg}
};

__WEAK void display_refresh_task(void *argument)
{

}

  __WEAK void flash_handler_thread(void *argument)
{

}

__WEAK void temp_humi_handler_thread(void *argument)
{

}

__WEAK void sensor_polling_task(void *argument)
{

}

__WEAK void mpuxxx_handler_thread(void *argument)
{

}

__WEAK void storage_manager_task(void *argument)
{

}

/**
 * @brief OS资源初始化函数
 * @note 按照配置数组创建所有OS资源
 * @return int32_t 初始化结果
 */
int32_t user_os_resources_init(void)
{
    int32_t ret = 0;
    uint32_t i;
    
    // 初始化队列资源
    for(i = 0; i < USER_QUEUE_NUM; i++)
    {
        ret = osal_queue_create(st_userqueuecfg[i].queue_depth, 
                               st_userqueuecfg[i].data_size,
                               &st_userqueuecfg[i].queue_handle);
        if(ret != 0)
        {
            // 队列创建失败，记录错误并返回
            return ret;
        }
    }
    
    // 初始化互斥锁资源
    for(i = 0; i < USER_MUTEX_NUM; i++)
    {
        ret = osal_mutex_create(&st_usermutexcfg[i].mutex_handle);
        if(ret != 0)
        {
            // 互斥锁创建失败，记录错误并返回
            return ret;
        }
    }
    
    // 初始化信号量资源
    for(i = 0; i < USER_SEMA_NUM; i++)
    {
        if(st_usersemacfg[i].is_binary)
        {
            // 创建二进制信号量
            ret = osal_sema_binary_create(&st_usersemacfg[i].sema_handle);
        }
        else
        {
            // 创建计数信号量
            ret = osal_sema_countings_create(&st_usersemacfg[i].sema_handle,
                                            st_usersemacfg[i].max_count,
                                            st_usersemacfg[i].init_count);
        }
        
        if(ret != 0)
        {
            // 信号量创建失败，记录错误并返回
            return ret;
        }
    }
    
    return 0; // 所有资源初始化成功
}

/**
 * @brief OS资源反初始化函数
 * @note 释放所有已创建的OS资源
 */
void user_os_resources_deinit(void)
{
    uint32_t i;
    
    // 删除队列资源
    for(i = 0; i < USER_QUEUE_NUM; i++)
    {
        if(st_userqueuecfg[i].queue_handle != NULL)
        {
            osal_queue_delete(st_userqueuecfg[i].queue_handle);
            st_userqueuecfg[i].queue_handle = NULL;
        }
    }
    
    // 删除互斥锁资源
    for(i = 0; i < USER_MUTEX_NUM; i++)
    {
        if(st_usermutexcfg[i].mutex_handle != NULL)
        {
            osal_mutex_delete(st_usermutexcfg[i].mutex_handle);
            st_usermutexcfg[i].mutex_handle = NULL;
        }
    }
    
    // 删除信号量资源
    for(i = 0; i < USER_SEMA_NUM; i++)
    {
        if(st_usersemacfg[i].sema_handle != NULL)
        {
            osal_sema_delete(st_usersemacfg[i].sema_handle);
            st_usersemacfg[i].sema_handle = NULL;
        }
    }
}
