# 智能手表软件设计需求文档

## 1. 文档概述

### 1.1 文档目的

本文档定义了智能手表项目中各驱动模块与LVGL GUI框架之间的数据交互逻辑、接口设计和通信机制，为系统架构设计和实现提供详细的技术规范。

### 1.2 适用范围

- 硬件平台：STM32F411基础的智能手表
- 操作系统：FreeRTOS
- GUI框架：LVGL

### 1.3 参考文档

- LVGL接口交互.txt
- STM32F411参考手册
- FreeRTOS开发指南

## 2. 系统架构设计

### 2.1 整体架构

```
┌─────────────────────────────────────────────────────────────┐
│                    LVGL GUI Layer                          │
├─────────────────────────────────────────────────────────────┤
│                 Data Exchange Layer                        │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐        │
│  │ Event Queue │  │ Data Buffer │  │ Sync Mutex  │        │
│  └─────────────┘  └─────────────┘  └─────────────┘        │
├─────────────────────────────────────────────────────────────┤
│                Application Layer                           │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐        │
│  │User_Display │  │User_Sensor  │  │User_Flash   │        │
│  └─────────────┘  └─────────────┘  └─────────────┘        │
├─────────────────────────────────────────────────────────────┤
│                   BSP Layer                               │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐        │
│  │   Display   │  │   Sensors   │  │   Storage   │        │
│  └─────────────┘  └─────────────┘  └─────────────┘        │
├─────────────────────────────────────────────────────────────┤
│                  Hardware Layer                           │
└─────────────────────────────────────────────────────────────┘
```

### 2.2 数据流向设计

#### 2.2.1 按需采样策略

- **温湿度传感器**：仅在相关界面激活时采样（0.1Hz）
- **心率传感器**：在健康监测界面激活时采样（1Hz）
- **运动传感器**：在运动界面或计步功能激活时采样（10Hz）
- **电池状态**：定期采样但低频率（0.1Hz）
- **触摸屏**：持续高频采样（100Hz）
- **显示刷新**：按需刷新（>100Hz）

#### 2.2.2 数据交互机制选择

**高频数据（>10Hz）**：

- 触摸数据：直接函数调用 + 中断驱动
- 显示刷新：DMA + 回调函数

**中频数据（1-10Hz）**：

- 运动数据：消息队列 + 事件驱动
- 心率数据：消息队列 + 定时采样

**低频数据（<1Hz）**：

- 温湿度：全局变量 + 事件通知
- 电池状态：全局变量 + 定时更新
- 配置数据：直接函数调用

## 3. 数据交互接口设计

### 3.1 数据结构定义

```c
/* 系统事件类型 */
typedef enum {
    SYS_EVENT_NONE = 0,
    SYS_EVENT_SENSOR_UPDATE,
    SYS_EVENT_BATTERY_UPDATE,
    SYS_EVENT_BT_STATUS_CHANGE,
    SYS_EVENT_UI_SWITCH,
    SYS_EVENT_POWER_MODE_CHANGE
} system_event_type_t;

/* 界面状态枚举 */
typedef enum {
    UI_STATE_WATCHFACE = 0,
    UI_STATE_HEALTH,
    UI_STATE_SPORT,
    UI_STATE_SETTINGS,
    UI_STATE_WEATHER,
    UI_STATE_SLEEP
} ui_state_t;

/* 传感器数据请求结构 */
typedef struct {
    uint32_t sensor_mask;     /* 请求的传感器位掩码 */
    uint32_t sample_rate;     /* 采样频率 */
    uint32_t duration;        /* 采样持续时间 */
} sensor_request_t;

/* 系统状态全局变量 */
typedef struct {
    ui_state_t current_ui_state;
    uint8_t battery_level;
    uint8_t bt_status;
    uint8_t power_mode;
    uint32_t system_tick;
} system_status_t;
```

### 3.2 消息队列设计

```c
/* 传感器数据消息队列 */
#define SENSOR_QUEUE_SIZE       10
#define SENSOR_MSG_SIZE         sizeof(st_sensor_data_t)

/* 系统事件消息队列 */
#define EVENT_QUEUE_SIZE        20
#define EVENT_MSG_SIZE          sizeof(system_event_type_t)

/* UI事件消息队列 */
#define UI_EVENT_QUEUE_SIZE     15
#define UI_EVENT_MSG_SIZE       sizeof(ui_state_t)
```

### 3.3 接口函数规范

#### 3.3.1 传感器接口

```c
/* 传感器管理接口 */
typedef struct {
    /* 传感器控制接口 */
    int32_t (*sensor_start)(uint32_t sensor_mask, uint32_t sample_rate);
    int32_t (*sensor_stop)(uint32_t sensor_mask);
    int32_t (*sensor_get_data)(uint32_t sensor_type, void* data, uint32_t timeout);
  
    /* 传感器状态查询 */
    bool (*sensor_is_active)(uint32_t sensor_type);
    uint32_t (*sensor_get_sample_rate)(uint32_t sensor_type);
} sensor_interface_t;

/* 具体传感器接口实现 */
float sensor_temp_read(void);                    /* 温度读取 */
float sensor_humidity_read(void);                /* 湿度读取 */
uint16_t sensor_heartrate_read(void);            /* 心率读取 */
uint32_t motion_get_steps(void);                 /* 步数获取 */
void motion_get_accel(float *x, float *y, float *z);  /* 加速度获取 */
void motion_get_gyro(float *x, float *y, float *z);   /* 角速度获取 */
```

#### 3.3.2 显示接口

```c
/* 显示管理接口 */
typedef struct {
    bool (*display_init)(uint16_t width, uint16_t height, uint8_t color_depth);
    void (*display_flush)(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const void* color_map);
    void (*display_set_backlight)(uint16_t brightness);
    bool (*display_is_busy)(void);
} display_interface_t;
```

#### 3.3.3 存储接口

```c
/* 存储管理接口 */
typedef struct {
    bool (*config_load)(void* config_struct, uint32_t size);
    bool (*config_save)(const void* config_struct, uint32_t size);
    bool (*flash_read)(uint32_t addr, void* data, uint32_t len);
    bool (*flash_write)(uint32_t addr, const void* data, uint32_t len);
    bool (*flash_erase)(uint32_t addr, uint32_t len);
} storage_interface_t;
```

## 4. 任务设计与调度

### 4.1 任务优先级分配

| 任务名称     | 优先级 | 栈大小 | 周期   | 功能描述          |
| ------------ | ------ | ------ | ------ | ----------------- |
| LVGL_Task    | 5      | 2048   | 5ms    | GUI刷新和事件处理 |
| Display_Task | 4      | 1024   | 按需   | 显示驱动管理      |
| Sensor_Task  | 3      | 1536   | 100ms  | 传感器数据采集    |
| Storage_Task | 2      | 1024   | 按需   | 存储管理          |
| System_Task  | 1      | 512    | 1000ms | 系统状态监控      |

### 4.2 任务间通信设计

```c
/* 全局队列句柄 */
extern osal_queue_handle_t g_sensor_data_queue;
extern osal_queue_handle_t g_system_event_queue;
extern osal_queue_handle_t g_ui_event_queue;

/* 全局互斥锁 */
extern osal_mutex_handle_t g_display_mutex;
extern osal_mutex_handle_t g_storage_mutex;
extern osal_mutex_handle_t g_sensor_mutex;

/* 全局事件组 */
extern osal_event_group_handle_t g_system_events;

/* 事件位定义 */
#define EVENT_SENSOR_READY      (1 << 0)
#define EVENT_DISPLAY_READY     (1 << 1)
#define EVENT_STORAGE_READY     (1 << 2)
#define EVENT_UI_SWITCH         (1 << 3)
#define EVENT_LOW_BATTERY       (1 << 4)
```

## 5. 具体模块交互逻辑

### 5.1 温湿度传感器交互逻辑

```c
/* UI切换到天气界面时的处理流程 */
void ui_weather_screen_enter(void) {
    /* 1. 发送传感器启动请求 */
    sensor_request_t req = {
        .sensor_mask = SENSOR_TEMP | SENSOR_HUMIDITY,
        .sample_rate = 100,  /* 0.1Hz = 100 * 10ms */
        .duration = 0        /* 持续采样直到界面退出 */
    };
  
    /* 2. 通过队列发送请求 */
    os_queue_send(g_sensor_request_queue, &req, 100);
  
    /* 3. 注册数据更新回调 */
    sensor_register_callback(SENSOR_TEMP, temp_data_callback);
    sensor_register_callback(SENSOR_HUMIDITY, humidity_data_callback);
}

/* 温度数据回调函数 */
void temp_data_callback(float temperature) {
    /* 更新全局变量 */
    g_system_status.temperature = temperature;
  
    /* 通知LVGL更新界面 */
    lv_event_send(weather_temp_label, LV_EVENT_REFRESH, NULL);
}

/* UI退出天气界面时的处理 */
void ui_weather_screen_exit(void) {
    /* 停止传感器采样 */
    sensor_request_t req = {
        .sensor_mask = SENSOR_TEMP | SENSOR_HUMIDITY,
        .sample_rate = 0,    /* 停止采样 */
        .duration = 0
    };
    os_queue_send(g_sensor_request_queue, &req, 100);
  
    /* 注销回调函数 */
    sensor_unregister_callback(SENSOR_TEMP);
    sensor_unregister_callback(SENSOR_HUMIDITY);
}
```

### 5.2 心率传感器交互逻辑

```c
/* 心率监测的状态机设计 */
typedef enum {
    HR_STATE_IDLE,
    HR_STATE_MEASURING,
    HR_STATE_STABLE,
    HR_STATE_ERROR
} heartrate_state_t;

/* 心率测量控制 */
void heartrate_measurement_start(void) {
    /* 1. 设置高频采样 */
    sensor_request_t req = {
        .sensor_mask = SENSOR_HEARTRATE,
        .sample_rate = 1000,  /* 1Hz */
        .duration = 30000     /* 30秒测量周期 */
    };
  
    /* 2. 启动测量任务 */
    os_queue_send(g_sensor_request_queue, &req, 100);
  
    /* 3. 设置状态 */
    g_heartrate_state = HR_STATE_MEASURING;
  
    /* 4. 启动超时定时器 */
    os_timer_start(g_heartrate_timeout_timer, 30000);
}

/* 心率数据处理 */
void heartrate_data_process(uint16_t raw_data) {
    static uint16_t hr_buffer[10];
    static uint8_t buffer_index = 0;
  
    /* 滑动平均滤波 */
    hr_buffer[buffer_index] = raw_data;
    buffer_index = (buffer_index + 1) % 10;
  
    /* 计算平均值 */
    uint32_t sum = 0;
    for(int i = 0; i < 10; i++) {
        sum += hr_buffer[i];
    }
    uint16_t avg_hr = sum / 10;
  
    /* 数据有效性检查 */
    if(avg_hr >= 40 && avg_hr <= 200) {
        g_system_status.heartrate = avg_hr;
        g_heartrate_state = HR_STATE_STABLE;
      
        /* 通知UI更新 */
        system_event_type_t event = SYS_EVENT_HEARTRATE_UPDATE;
        os_queue_send(g_system_event_queue, &event, 0);
    }
}
```

### 5.3 运动传感器交互逻辑

```c
/* 运动数据管理 */
typedef struct {
    uint32_t daily_steps;
    float total_distance;
    uint32_t calories_burned;
    bool is_walking;
    bool is_running;
} motion_data_t;

/* 运动检测算法 */
void motion_detection_algorithm(st_sensor_motion_data_t* motion_data) {
    static float accel_magnitude_prev = 0;
    static uint32_t step_count = 0;
    static uint32_t last_step_time = 0;
  
    /* 计算加速度幅值 */
    float accel_magnitude = sqrt(motion_data->ax * motion_data->ax + 
                                motion_data->ay * motion_data->ay + 
                                motion_data->az * motion_data->az);
  
    /* 步数检测算法 */
    if(accel_magnitude > 1.2 && accel_magnitude_prev < 1.2) {
        uint32_t current_time = os_task_get_tick_count();
        if(current_time - last_step_time > 300) {  /* 防抖动 */
            step_count++;
            last_step_time = current_time;
          
            /* 更新全局步数 */
            g_motion_data.daily_steps = step_count;
          
            /* 每10步通知一次UI */
            if(step_count % 10 == 0) {
                system_event_type_t event = SYS_EVENT_STEP_UPDATE;
                os_queue_send(g_system_event_queue, &event, 0);
            }
        }
    }
  
    accel_magnitude_prev = accel_magnitude;
}
```

### 5.4 显示系统交互逻辑

```c
/* 显示任务主循环 */
void display_refresh_task(void *argument) {
    lv_disp_drv_t disp_drv;
    lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf_1[240 * 10];
    static lv_color_t buf_2[240 * 10];
  
    /* 初始化LVGL显示驱动 */
    lv_disp_draw_buf_init(&draw_buf, buf_1, buf_2, 240 * 10);
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &draw_buf;
    disp_drv.flush_cb = display_flush_callback;
    disp_drv.hor_res = 240;
    disp_drv.ver_res = 280;
    lv_disp_drv_register(&disp_drv);
  
    while(1) {
        /* LVGL任务处理 */
        lv_task_handler();
      
        /* 检查系统事件 */
        system_event_type_t event;
        if(os_queue_receive(g_system_event_queue, &event, 5) == OS_SUCCESS) {
            handle_system_event(event);
        }
      
        /* 5ms周期 */
        os_task_delay_ms(5);
    }
}

/* 显示刷新回调 */
void display_flush_callback(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) {
    /* 获取显示互斥锁 */
    os_mutex_take(g_display_mutex, portMAX_DELAY);
  
    /* DMA传输显示数据 */
    display_dma_transfer(area->x1, area->y1, area->x2, area->y2, (uint16_t*)color_p);
  
    /* 释放互斥锁 */
    os_mutex_give(g_display_mutex);
  
    /* 通知LVGL传输完成 */
    lv_disp_flush_ready(disp_drv);
}
```

### 5.5 存储系统交互逻辑

```c
/* 配置数据管理 */
typedef struct {
    uint8_t brightness;
    uint8_t volume;
    uint32_t step_goal;
    char user_name[32];
    uint32_t crc32;
} user_config_t;

/* 配置加载 */
bool config_load_from_flash(user_config_t* config) {
    bool result = false;
  
    /* 获取存储互斥锁 */
    if(os_mutex_take(g_storage_mutex, 1000) == OS_SUCCESS) {
        /* 从Flash读取配置 */
        if(flash_read(CONFIG_FLASH_ADDR, config, sizeof(user_config_t))) {
            /* CRC校验 */
            uint32_t calc_crc = calculate_crc32((uint8_t*)config, sizeof(user_config_t) - 4);
            if(calc_crc == config->crc32) {
                result = true;
            }
        }
      
        /* 释放互斥锁 */
        os_mutex_give(g_storage_mutex);
    }
  
    return result;
}

/* 配置保存 */
bool config_save_to_flash(const user_config_t* config) {
    bool result = false;
    user_config_t temp_config = *config;
  
    /* 计算CRC */
    temp_config.crc32 = calculate_crc32((uint8_t*)&temp_config, sizeof(user_config_t) - 4);
  
    /* 获取存储互斥锁 */
    if(os_mutex_take(g_storage_mutex, 1000) == OS_SUCCESS) {
        /* 擦除扇区 */
        if(flash_erase(CONFIG_FLASH_ADDR, 4096)) {
            /* 写入配置 */
            result = flash_write(CONFIG_FLASH_ADDR, &temp_config, sizeof(user_config_t));
        }
      
        /* 释放互斥锁 */
        os_mutex_give(g_storage_mutex);
    }
  
    return result;
}
```

## 6. 电源管理与性能优化

### 6.1 电源模式管理

```c
/* 电源模式定义 */
typedef enum {
    POWER_MODE_NORMAL,      /* 正常模式 */
    POWER_MODE_LOW_POWER,   /* 低功耗模式 */
    POWER_MODE_SLEEP,       /* 睡眠模式 */
    POWER_MODE_DEEP_SLEEP   /* 深度睡眠模式 */
} power_mode_t;

/* 电源模式切换策略 */
void power_mode_manager(void) {
    static uint32_t last_activity_time = 0;
    uint32_t current_time = os_task_get_tick_count();
    uint32_t idle_time = current_time - last_activity_time;
  
    /* 根据空闲时间切换电源模式 */
    if(idle_time > 60000) {  /* 1分钟无操作 */
        power_set_mode(POWER_MODE_SLEEP);
        /* 停止非必要传感器 */
        sensor_stop(SENSOR_TEMP | SENSOR_HUMIDITY);
        /* 降低显示刷新率 */
        display_set_refresh_rate(1);
    } else if(idle_time > 30000) {  /* 30秒无操作 */
        power_set_mode(POWER_MODE_LOW_POWER);
        /* 降低传感器采样率 */
        sensor_set_sample_rate(SENSOR_ALL, 50);
    }
}
```

### 6.2 内存管理优化

```c
/* 内存池管理 */
#define SENSOR_DATA_POOL_SIZE   10
#define UI_EVENT_POOL_SIZE      20

static st_sensor_data_t sensor_data_pool[SENSOR_DATA_POOL_SIZE];
static uint8_t sensor_pool_bitmap = 0;

/* 内存池分配 */
st_sensor_data_t* sensor_data_alloc(void) {
    os_enter_critical();
  
    for(int i = 0; i < SENSOR_DATA_POOL_SIZE; i++) {
        if(!(sensor_pool_bitmap & (1 << i))) {
            sensor_pool_bitmap |= (1 << i);
            os_exit_critical();
            return &sensor_data_pool[i];
        }
    }
  
    os_exit_critical();
    return NULL;  /* 内存池已满 */
}

/* 内存池释放 */
void sensor_data_free(st_sensor_data_t* ptr) {
    if(ptr >= sensor_data_pool && ptr < sensor_data_pool + SENSOR_DATA_POOL_SIZE) {
        int index = ptr - sensor_data_pool;
        os_enter_critical();
        sensor_pool_bitmap &= ~(1 << index);
        os_exit_critical();
    }
}
```

## 7. 错误处理与容错机制

### 7.1 传感器错误处理

```c
/* 传感器错误类型 */
typedef enum {
    SENSOR_ERROR_NONE = 0,
    SENSOR_ERROR_TIMEOUT,
    SENSOR_ERROR_I2C_FAIL,
    SENSOR_ERROR_DATA_INVALID,
    SENSOR_ERROR_CALIBRATION_FAIL
} sensor_error_t;

/* 传感器错误处理 */
void sensor_error_handler(uint32_t sensor_type, sensor_error_t error) {
    switch(error) {
        case SENSOR_ERROR_TIMEOUT:
            /* 重新初始化传感器 */
            sensor_reinit(sensor_type);
            break;
          
        case SENSOR_ERROR_I2C_FAIL:
            /* 重置I2C总线 */
            i2c_bus_reset();
            sensor_reinit(sensor_type);
            break;
          
        case SENSOR_ERROR_DATA_INVALID:
            /* 使用上次有效数据 */
            sensor_use_last_valid_data(sensor_type);
            break;
          
        default:
            /* 记录错误日志 */
            log_error("Sensor error: type=%d, error=%d", sensor_type, error);
            break;
    }
}
```

### 7.2 看门狗机制

```c
/* 任务看门狗 */
#define WATCHDOG_TIMEOUT_MS     5000

typedef struct {
    const char* task_name;
    uint32_t last_feed_time;
    uint32_t timeout_ms;
    bool is_enabled;
} task_watchdog_t;

static task_watchdog_t task_watchdogs[] = {
    {"LVGL_Task", 0, 1000, true},
    {"Sensor_Task", 0, 2000, true},
    {"Display_Task", 0, 1000, true}
};

/* 看门狗喂狗 */
void watchdog_feed(const char* task_name) {
    for(int i = 0; i < sizeof(task_watchdogs)/sizeof(task_watchdog_t); i++) {
        if(strcmp(task_watchdogs[i].task_name, task_name) == 0) {
            task_watchdogs[i].last_feed_time = os_task_get_tick_count();
            break;
        }
    }
}

/* 看门狗检查任务 */
void watchdog_check_task(void *argument) {
    while(1) {
        uint32_t current_time = os_task_get_tick_count();
      
        for(int i = 0; i < sizeof(task_watchdogs)/sizeof(task_watchdog_t); i++) {
            if(task_watchdogs[i].is_enabled) {
                uint32_t elapsed = current_time - task_watchdogs[i].last_feed_time;
                if(elapsed > task_watchdogs[i].timeout_ms) {
                    /* 任务超时，记录错误并重启系统 */
                    log_error("Task %s timeout, system reset", task_watchdogs[i].task_name);
                    NVIC_SystemReset();
                }
            }
        }
      
        os_task_delay_ms(1000);
    }
}
```

## 8. 性能指标与测试要求

### 8.1 性能指标

| 指标项         | 目标值  | 测试方法             |
| -------------- | ------- | -------------------- |
| UI响应时间     | <100ms  | 触摸到界面更新的延迟 |
| 传感器数据延迟 | <50ms   | 数据采集到显示的延迟 |
| 内存使用率     | <80%    | 运行时内存监控       |
| CPU使用率      | <70%    | 任务调度统计         |
| 电池续航       | >24小时 | 实际使用测试         |
| 启动时间       | <3秒    | 上电到界面显示       |

### 8.2 测试用例

#### 8.2.1 功能测试

- 各传感器数据采集准确性测试
- UI界面切换流畅性测试
- 数据存储完整性测试
- 电源管理功能测试

#### 8.2.2 性能测试

- 长时间运行稳定性测试
- 内存泄漏检测
- 任务调度效率测试
- 中断响应时间测试

#### 8.2.3 压力测试

- 高频数据采集压力测试
- 多任务并发执行测试
- 存储读写压力测试
- 低电量运行测试

## 9. 开发规范与约定

### 9.1 编码规范

- 遵循MISRA C 2012标准
- 函数命名采用模块前缀+功能描述
- 全局变量使用g_前缀
- 静态变量使用s_前缀
- 常量使用全大写+下划线

### 9.2 注释规范

- 所有公共接口必须有详细的Doxygen注释
- 复杂算法必须有实现原理说明
- 关键数据结构必须有字段说明

### 9.3 版本管理

- 使用语义化版本号（主版本.次版本.修订版本）
- 每个版本必须有对应的变更日志
- 关键功能变更必须有向后兼容性说明

## 10. 总结

本软件设计需求文档详细定义了智能手表项目的软件架构、数据交互机制、接口设计和实现规范。通过采用分层架构、按需采样、多种通信机制相结合的设计方案，能够有效平衡系统性能、功耗和用户体验。

关键设计要点：

1. **按需采样策略**：根据UI状态动态控制传感器采样，优化功耗
2. **多层次通信机制**：高频数据直接调用，中频数据队列传输，低频数据全局变量
3. **模块化设计**：清晰的接口定义和职责分离
4. **容错机制**：完善的错误处理和看门狗保护
5. **性能优化**：内存池管理和电源模式切换
