/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file User_Sensor.h
 * 
 * @par dependencies 
 * - User_Sensor.h
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
#ifndef __USER_SENSOR_H__  //Avoid repeated including same files later
#define __USER_SENSOR_H__

//******************************** Includes *********************************//
#include "main.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//
typedef struct
{
    float temp;
    float humi;
}st_sensor_humitemp_data_t;

typedef struct
{
    /* Raw accelerometer data from sensor */
    int16_t accel_x_raw;
    int16_t accel_y_raw;
    int16_t accel_z_raw;

    /* Processed accelerometer data in g units */
    double ax;
    double ay;
    double az;

    /* Raw gyroscope data from sensor */
    int16_t gyro_x_raw;
    int16_t gyro_y_raw;
    int16_t gyro_z_raw;

    /* Processed gyroscope data in degrees/s */
    double gx;
    double gy;
    double gz;

    /* Temperature reading in degrees Celsius */
    float temperature;

    /* Kalman filter processed angles */
    double kalman_angle_x;
    double kalman_angle_y;
}st_sensor_motion_data_t;

typedef struct 
{
    st_sensor_motion_data_t st_sensor_motion_data;
    st_sensor_humitemp_data_t st_sensor_humitemp_data; 
}st_sensor_data_t;

/* 传感器请求结构 */
typedef struct {
    uint32_t sensor_mask;     /* 请求的传感器位掩码 */
    uint32_t sample_rate;     /* 采样频率(ms) */
    uint32_t duration;        /* 采样持续时间 */
} sensor_request_t;

/* 传感器类型定义 */
#define SENSOR_TEMP         (1 << 0)
#define SENSOR_HUMIDITY     (1 << 1)
#define SENSOR_MOTION       (1 << 2)
#define SENSOR_ALL          (SENSOR_TEMP | SENSOR_HUMIDITY | SENSOR_MOTION)

//******************************** Defines **********************************//

//******************************** Declaring ********************************//
void sensor_polling_task(void *argument);
float sensor_temp_read(void);
float sensor_humidity_read(void);
void sensor_start_sampling(uint32_t sensor_mask, uint32_t sample_rate);
void sensor_stop_sampling(uint32_t sensor_mask);
//******************************** Declaring ********************************//

#endif /* __USER_SENSOR_H__ */
