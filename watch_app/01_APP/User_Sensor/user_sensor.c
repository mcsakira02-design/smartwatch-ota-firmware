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
#include "user_sensor.h"
#include "user_init.h"
#include "osal.h"
#include "Debug.h"
#include "temp_hui_port.h"
#include "motion_port.h"
#include "i2c.h"
//TODO:后续接口修改
#include "bsp_mpuxxx_driver.h"

//******************************** Includes *********************************//

//******************************** Variable **********************************//
/* 传感器状态管理 */
static struct {
    uint32_t active_sensors;        /* 当前激活的传感器 */
    uint32_t temp_sample_rate;      /* 温度采样率(ms) */
    uint32_t motion_sample_rate;    /* 运动传感器采样率(ms) */
    uint32_t last_temp_sample;      /* 上次温度采样时间 */
    uint32_t last_motion_sample;    /* 上次运动采样时间 */
    bool temp_sampling_enabled;     /* 温度采样使能 */
    bool motion_sampling_enabled;   /* 运动采样使能 */
} sensor_state = {
    .active_sensors = 0,
    .temp_sample_rate = 10000,      /* 默认10秒采样一次 */
    .motion_sample_rate = 100,      /* 默认100ms采样一次 */
    .last_temp_sample = 0,
    .last_motion_sample = 0,
    .temp_sampling_enabled = false,
    .motion_sampling_enabled = false
};

//******************************** Variable **********************************//
void sensor_motion(void);
void sensor_temp_humi(void);
//******************************** Function definitions ********************************//


/**
 * @brief 传感器轮询任务 - 实现按需采样策略
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * 
 * */
void sensor_polling_task(void *argument)
{
  /* USER CODE BEGIN userTaskFunction */
  ui_state_t ui_event;
  uint32_t current_time;
  
#ifdef DEBUG_USER_SENSOR
  DEBUG_OUT("sensor polling task start");
#endif
  
  //等待驱动初始化完成
  osal_task_delay_ms(200);
  
  for(;;)
  {
    /* 检查UI事件队列，响应界面切换 */
    if(osal_queue_receive(g_ui_event_queue, &ui_event, 0) == OSAL_SUCCESS)
    {
      /* 根据UI状态调整传感器采样策略 */
      switch(ui_event)
      {
        case UI_STATE_WEATHER:
          /* 切换到天气界面，启动温湿度采样 */
          sensor_start_sampling(SENSOR_TEMP | SENSOR_HUMIDITY, 10000); /* 10秒采样一次 */
#ifdef DEBUG_USER_SENSOR
          DEBUG_OUT("Weather UI activated, start temp/humidity sampling");
#endif
          break;
          
        case UI_STATE_SPORT:
          /* 切换到运动界面，启动运动传感器采样 */
          sensor_start_sampling(SENSOR_MOTION, 100); /* 100ms采样一次 */
#ifdef DEBUG_USER_SENSOR
          DEBUG_OUT("Sport UI activated, start motion sampling");
#endif
          break;
          
        case UI_STATE_WATCHFACE:
        case UI_STATE_SETTINGS:
          /* 切换到表盘或设置界面，停止非必要传感器采样 */
          sensor_stop_sampling(SENSOR_TEMP | SENSOR_HUMIDITY);
#ifdef DEBUG_USER_SENSOR
          DEBUG_OUT("UI switched, stop unnecessary sampling");
#endif
          break;
          
        default:
          break;
      }
      
      /* 更新全局UI状态 */
      if(osal_mutex_take(g_sensor_data_mutex, 100) == OSAL_SUCCESS)
      {
        g_system_status.current_ui_state = ui_event;
        osal_mutex_give(g_sensor_data_mutex);
      }
    }
    
    /* 获取当前时间 */
    current_time = osal_task_get_tick_count();
    
    /* 按需执行传感器采样 */
    if(sensor_state.temp_sampling_enabled)
    {
      if((current_time - sensor_state.last_temp_sample) >= sensor_state.temp_sample_rate)
      {
        sensor_temp_humi();
        sensor_state.last_temp_sample = current_time;
      }
    }
    
    if(sensor_state.motion_sampling_enabled)
    {
      if((current_time - sensor_state.last_motion_sample) >= sensor_state.motion_sample_rate)
      {
        sensor_motion();
        sensor_state.last_motion_sample = current_time;
      }
    }
    
    /* 任务延时 */
    osal_task_delay_ms(10);
  }
  /* USER CODE END userTaskFunction */
}

/**
 * @brief 温湿度传感器读取 - 更新全局状态
 * @param[in] :None
 * @param[Out] :None
 * @return :None
 * */
void sensor_temp_humi(void)
{
	float temp, humi;
	float sensor_data[2];
	
#ifdef DEBUG_USER_SENSOR
	DEBUG_OUT("Reading temp/humidity sensor");
#endif
	
	/* 读取温湿度数据 */
	temphumi_read_temp_and_humi(&temp, &humi);
	
	/* 更新全局状态变量 */
	if(osal_mutex_take(g_sensor_data_mutex, 100) == OSAL_SUCCESS)
	{
		g_system_status.temperature = temp;
		g_system_status.humidity = humi;
		g_system_status.system_tick = osal_task_get_tick_count();
		osal_mutex_give(g_sensor_data_mutex);
		
#ifdef DEBUG_USER_SENSOR
		DEBUG_OUT("Temp: %.2f°C, Humidity: %.2f%%", temp, humi);
#endif
	}
	
	/* 可选：通过队列发送数据给其他任务 */
	sensor_data[0] = temp;
	sensor_data[1] = humi;
	osal_queue_send(g_sensor_data_queue, sensor_data, 0);
}

mpuxxx_data_t mpu6050_data;
void sensor_motion(void)
{
#ifdef DEBUG_USER_SENSOR
	DEBUG_OUT("unpack_task start\n");
#endif  
  uint8_t ret = 0;
  uint8_t data = 0;
  int16_t temp = 0;
  

  ret = motion_getreqstate();
  if (0 == ret)
  {
#ifdef DEBUG_USER_SENSOR
	  DEBUG_OUT("unpack_task: data = %d\n", data);
#endif
  }
  uint8_t *addr = motion_readdata();
#ifdef DEBUG_USER_SENSOR
	DEBUG_OUT("unpack_task: addr = %p\n", addr);
#endif
  temp = (int16_t)(*(addr + 6) << 8 | *(addr + 7));
  mpu6050_data.temperature = 36.53 + temp/340.0;

  mpu6050_data.accel_x_raw = (int16_t)(*(addr + 0) << 8 | *(addr + 1));
  mpu6050_data.accel_y_raw = (int16_t)(*(addr + 2) << 8 | *(addr + 3));
  mpu6050_data.accel_z_raw = (int16_t)(*(addr + 4) << 8 | *(addr + 5));

  mpu6050_data.ax = mpu6050_data.accel_x_raw / 16384.0;
  mpu6050_data.ay = mpu6050_data.accel_y_raw / 16384.0;
  mpu6050_data.az = mpu6050_data.accel_z_raw / 14418.0;

  mpu6050_data.gyro_x_raw = (int16_t)(*(addr + 8) << 8 | *(addr + 9));
  mpu6050_data.gyro_y_raw = (int16_t)(*(addr + 10) << 8 | *(addr + 11));
  mpu6050_data.gyro_z_raw = (int16_t)(*(addr + 12) << 8 | *(addr + 13));

  mpu6050_data.gx = mpu6050_data.gyro_x_raw / 131.0;
  mpu6050_data.gy = mpu6050_data.gyro_y_raw / 131.0;
  mpu6050_data.gz = mpu6050_data.gyro_z_raw / 131.0;
  
#ifdef DEBUG_USER_SENSOR
  DEBUG_OUT("UnpackThread temp=%f", mpu6050_data.temperature);
  DEBUG_OUT("UnpackThread ax=%f", mpu6050_data.ax);
  DEBUG_OUT("UnpackThread ay=%f", mpu6050_data.ay);
  DEBUG_OUT("UnpackThread az=%f", mpu6050_data.az);
  DEBUG_OUT("UnpackThread gx=%f", mpu6050_data.gx);
  DEBUG_OUT("UnpackThread gy=%f", mpu6050_data.gy);
  DEBUG_OUT("UnpackThread gz=%f", mpu6050_data.gz);
#endif


  motion_readdataend();
}

/**
 * @brief 启动传感器采样
 * @param[in] sensor_mask: 传感器掩码
 * @param[in] sample_rate: 采样频率(ms)
 * @return None
 */
void sensor_start_sampling(uint32_t sensor_mask, uint32_t sample_rate)
{
    if(sensor_mask & SENSOR_TEMP)
    {
        sensor_state.temp_sampling_enabled = true;
        sensor_state.temp_sample_rate = sample_rate;
        sensor_state.active_sensors |= SENSOR_TEMP;
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("Temperature sampling started, rate: %dms", sample_rate);
#endif
    }
    
    if(sensor_mask & SENSOR_HUMIDITY)
    {
        sensor_state.temp_sampling_enabled = true;  /* 温湿度一起采样 */
        sensor_state.active_sensors |= SENSOR_HUMIDITY;
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("Humidity sampling started");
#endif
    }
    
    if(sensor_mask & SENSOR_MOTION)
    {
        sensor_state.motion_sampling_enabled = true;
        sensor_state.motion_sample_rate = sample_rate;
        sensor_state.active_sensors |= SENSOR_MOTION;
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("Motion sampling started, rate: %dms", sample_rate);
#endif
    }
}

/**
 * @brief 停止传感器采样
 * @param[in] sensor_mask: 传感器掩码
 * @return None
 */
void sensor_stop_sampling(uint32_t sensor_mask)
{
    if(sensor_mask & (SENSOR_TEMP | SENSOR_HUMIDITY))
    {
        sensor_state.temp_sampling_enabled = false;
        sensor_state.active_sensors &= ~(SENSOR_TEMP | SENSOR_HUMIDITY);
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("Temperature/Humidity sampling stopped");
#endif
    }
    
    if(sensor_mask & SENSOR_MOTION)
    {
        sensor_state.motion_sampling_enabled = false;
        sensor_state.active_sensors &= ~SENSOR_MOTION;
#ifdef DEBUG_USER_SENSOR
        DEBUG_OUT("Motion sampling stopped");
#endif
    }
}

/**
 * @brief 读取温度数据
 * @return 温度值
 */
float sensor_temp_read(void)
{
    float temp = 0.0f;
    
    if(osal_mutex_take(g_sensor_data_mutex, 100) == OSAL_SUCCESS)
    {
        temp = g_system_status.temperature;
        osal_mutex_give(g_sensor_data_mutex);
    }
    
    return temp;
}

/**
 * @brief 读取湿度数据
 * @return 湿度值
 */
float sensor_humidity_read(void)
{
    float humidity = 0.0f;
    
    if(osal_mutex_take(g_sensor_data_mutex, 100) == OSAL_SUCCESS)
    {
        humidity = g_system_status.humidity;
        osal_mutex_give(g_sensor_data_mutex);
    }
    
    return humidity;
}

//******************************** Function definitions ********************************//
