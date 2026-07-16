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
#include "user_init.h"
#include "osal.h"
#include "temp_hui_port.h"
#include "motion_port.h"
#include "externflash_manage_port.h"
#include "user_sensor.h"
#include "user_externflashmanage.h"
#include "hartrate_port.h"
#include "User_Display.h"
#include "cmsis_os.h"
#include "event_groups.h"

#include "debug.h"
#include "i2c_port.h"
#include "adc_port.h"
#include "bsp_temp_humi_xxx_handler.h"
#include "user_task_reso_config.h"
#include "gpio_port.h"

#include "airpressure_port.h"


//******************************** Includes *********************************//

//******************************** Variable **********************************//
/*线程定义*/
osal_task_handle_t userTaskInitHandle;
/*事件组*/
EventGroupHandle_t userExtFlashEveGropHandle;
/*信号量*/
osal_sema_handle_t userExtFlashSemaHandle;
/*i2c互斥锁*/
osal_mutex_handle_t sensor_i2c_mutex_handler;
/*事件组句柄*/
EventGroupHandle_t xtemphumi_event_flags_handle;

osal_mutex_handle_t extern_flash_mutex_handler;

/* 新增的全局资源 */
osal_queue_handle_t g_sensor_data_queue;
osal_queue_handle_t g_ui_event_queue;
osal_mutex_handle_t g_sensor_data_mutex;
system_status_t g_system_status = {
    .current_ui_state = UI_STATE_WATCHFACE,
    .temperature = 0.0f,
    .humidity = 0.0f,
    .battery_level = 100,
    .system_tick = 0
};

extern st_usertaskcfg_t st_usertaskcfg[USER_TASK_NUM];
extern st_userqueuecfg_t st_userqueuecfg[USER_QUEUE_NUM];
extern st_usermutexcfg_t st_usermutexcfg[USER_MUTEX_NUM];
extern st_usersemacfg_t st_usersemacfg[USER_SEMA_NUM];
//******************************** Variable **********************************//

//******************************** Function definitions ********************************//
/**
 * @brief User initialization task thread
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * 
 * */
static void userTaskInitFunction(void *argument)
{
  /* USER CODE BEGIN userTaskFunction */
  int32_t ret;
  osal_task_delay_ms(200);

  /* ========== 表驱动OS资源统一初始化 ========== */
  ret = user_os_resources_init();
  if(ret != OSAL_SUCCESS)
  {
#ifdef DEBUG_User_Init
    DEBUG_OUT("OS resources init failed, error code: %d", ret);
#endif
    // OS资源初始化失败，系统无法正常运行
    while(1); // 停止系统运行
  }
#ifdef DEBUG_User_Init
  DEBUG_OUT("All OS resources initialized successfully");
#endif
  
  /* ========== GPIO平台初始化 ========== */
  ret = core_gpio_init();
  if(ret != CORE_GPIO_OK)
  {
#ifdef DEBUG_User_Init
    DEBUG_OUT("GPIO platform init failed, error code: %d", ret);
#endif
  }
  else
  {
#ifdef DEBUG_User_Init
    DEBUG_OUT("GPIO platform initialized successfully");
#endif
  }
  
  /* ========== 表驱动任务创建 ========== */
  for(uint8_t i = 0; i < USER_TASK_NUM; i++)
  {
    ret = osal_task_create \
        (st_usertaskcfg[i].task_name, \
         st_usertaskcfg[i].func_pointer, \
         st_usertaskcfg[i].stack_size, \
         st_usertaskcfg[i].priority, \
         st_usertaskcfg[i].task_handle,\
         st_usertaskcfg[i].argument);
    if(OSAL_ERROR == ret)
    {
#ifdef DEBUG_User_Init
      DEBUG_OUT("%s task init failed ",st_usertaskcfg[i].task_name);
#endif
      //TODO:线程创建失败需要关闭对应的相关功能
    }
    else
    {
#ifdef DEBUG_User_Init
      DEBUG_OUT("%s task created successfully", st_usertaskcfg[i].task_name);
#endif
    }
  }

  {
    /* ========== 以下资源创建已迁移到表驱动配置中 ========== */
    /* 原有资源创建代码已注释，现在通过 user_task_reso_config.c 中的配置数组统一管理 */
    
    //创建事件唤醒 - 【注意】此事件组暂未迁移到表驱动，需要单独处理
    xtemphumi_event_flags_handle = xEventGroupCreate();
    if (xtemphumi_event_flags_handle == NULL) 
    {
        // 事件组创建失败
        while(1);
    }

    /*创建互斥锁保护I2C执行 - 已迁移到表驱动配置: st_usermutexcfg[3] (I2CMutex)*/
    // ret = osal_mutex_create(&sensor_i2c_mutex_handler);
    // 现在使用表驱动配置中的 I2CMutex
    sensor_i2c_mutex_handler = st_usermutexcfg[3].mutex_handle; // I2CMutex
    if(sensor_i2c_mutex_handler != NULL)
    {
      core_i2c_register_mutex(0, sensor_i2c_mutex_handler);
#ifdef DEBUG_User_Init
      DEBUG_OUT("i2c mutex from table config success");
#endif
    }
    else
    {
#ifdef DEBUG_User_Init
      DEBUG_OUT("i2c mutex from table config failed");
#endif
    }
    
    /* 创建传感器数据队列 - 已迁移到表驱动配置: st_userqueuecfg[0] (SensorDataQueue) */
    // ret = osal_queue_create(10, sizeof(float) * 2, &g_sensor_data_queue);
    g_sensor_data_queue = st_userqueuecfg[0].queue_handle; // SensorDataQueue
    if(g_sensor_data_queue == NULL)
    {
#ifdef DEBUG_User_Init
      DEBUG_OUT("sensor data queue from table config failed");
#endif
    }
    else
    {
#ifdef DEBUG_User_Init
      DEBUG_OUT("sensor data queue from table config success");
#endif
    }
    
    /* 创建UI事件队列 - 已迁移到表驱动配置: st_userqueuecfg[2] (DisplayQueue) */
    // ret = osal_queue_create(15, sizeof(ui_state_t), &g_ui_event_queue);
    g_ui_event_queue = st_userqueuecfg[2].queue_handle; // DisplayQueue
    if(g_ui_event_queue == NULL)
    {
#ifdef DEBUG_User_Init
      DEBUG_OUT("ui event queue from table config failed");
#endif
    }
    else
    {
#ifdef DEBUG_User_Init
      DEBUG_OUT("ui event queue from table config success");
#endif
    }
    
    /* 创建传感器数据互斥锁 - 已迁移到表驱动配置: st_usermutexcfg[1] (SensorMutex) */
    // ret = osal_mutex_create(&g_sensor_data_mutex);
    g_sensor_data_mutex = st_usermutexcfg[1].mutex_handle; // SensorMutex
    if(g_sensor_data_mutex == NULL)
    {
#ifdef DEBUG_User_Init
      DEBUG_OUT("sensor data mutex from table config failed");
#endif
    }
    else
    {
#ifdef DEBUG_User_Init
      DEBUG_OUT("sensor data mutex from table config success");
#endif
    }
  }
  //外部flash初始化
  {
    /* ========== 外部Flash资源创建已迁移到表驱动配置中 ========== */
    
    /*创建外部flash事件组 - 【注意】此事件组暂未迁移到表驱动，需要单独处理*/
    userExtFlashEveGropHandle = xEventGroupCreate();
    
    /* 创建外部flash信号量 - 已迁移到表驱动配置: st_usersemacfg[1] (StorageReadySem) */
    // ret = osal_sema_binary_create(&userExtFlashSemaHandle);
    userExtFlashSemaHandle = st_usersemacfg[1].sema_handle; // StorageReadySem
    if(userExtFlashSemaHandle == NULL)
    {
#ifdef DEBUG_User_Init
      DEBUG_OUT("Flash sema from table config error");
#endif
    }
    else
    {
#ifdef DEBUG_User_Init
      DEBUG_OUT("Flash sema from table config success");
#endif
    }
  }

	/* 创建线程互斥锁 - 已迁移到表驱动配置: st_usermutexcfg[0] (FlashMutex) */
	// ret = osal_mutex_create(&extern_flash_mutex_handler);
	extern_flash_mutex_handler = st_usermutexcfg[0].mutex_handle; // FlashMutex
	if(extern_flash_mutex_handler == NULL)
	{
		//从表驱动配置获取失败
#ifdef DEBUG_User_Init
      DEBUG_OUT("Flash mutex from table config error");
#endif
	}
	else
	{
#ifdef DEBUG_User_Init
      DEBUG_OUT("Flash mutex from table config success");
#endif
	}
  osal_task_delete(NULL);
  /* USER CODE END userTaskFunction */
}

/**
 * @brief OS creation initialization thread task
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * 
 * */
void UserAppTask_Init(void)
{
  osal_task_create("userTask", userTaskInitFunction, 128 * 4,
    PRI_EMERGENCY, userTaskInitHandle,NULL);
}

//******************************** Function definitions ********************************//
