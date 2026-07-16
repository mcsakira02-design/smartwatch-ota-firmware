/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file mpu6050.h
 * 
 * @par dependencies 
 * 
 * - stdint.h
 * - mpu6050.h
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of MPU6050 and corresponding options.
 * 
 * Processing flow:
 * 
 * call directly.
 * 
 * @version V1.1
 * 
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
//******************************** Includes *********************************//
#include "bsp_mpuxxx_driver.h"
#include "Debug.h"
//******************************** Defines **********************************//
#define IIC_MEMADD_SIZE_8BIT 0x00000001U
#define TIME_OUT_MS          1000
#define MPUXXX_NOT_INITED    0
#define MPUXXX_INITED        1

static uint8_t g_is_inited = MPUXXX_NOT_INITED;

static double accel_scale = 16384.0;
static double gyro_scale = 131.0;

//******************************** Macros ***********************************//
#define MPUXXX_WRITE_REG(p_mpu_driver, reg, p_data, len)\
                        p_mpu_driver->p_iic_driver_interface->pf_iic_mem_write(\
                        p_mpu_driver->p_iic_driver_interface->hi2c,\
                        (MPU_ADDR << 1) | 0,\
                        reg,\
                        IIC_MEMADD_SIZE_8BIT,\
                        p_data,\
                        len,\
                        TIME_OUT_MS)

#define MPUXXX_READ_REG(p_mpu_driver, reg, p_data, len)\
                        p_mpu_driver->p_iic_driver_interface->pf_iic_mem_read(\
                        p_mpu_driver->p_iic_driver_interface->hi2c,\
                        (MPU_ADDR << 1) | 1,\
                        reg,\
                        IIC_MEMADD_SIZE_8BIT,\
                        p_data, \
                        len, \
                        TIME_OUT_MS)

//******************************** Declaring ********************************//

//******************************** Functions ********************************//

/**
 * @brief mpuxxx sleep
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_sleep(bsp_mpuxxx_driver_t *p_mpu_driver)
{
    return MPUxxx_OK;
}

/**
 * @brief mpuxxx wakeup
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_wakeup(bsp_mpuxxx_driver_t *p_mpu_driver)
{
    mpuxxx_status_t ret = MPUxxx_OK;
    uint8_t data = 0;
    data = SLEEP_BIT(0);
    
    ret = MPUXXX_WRITE_REG(p_mpu_driver, MPU_PWR_MGMT1_REG, &data, 1);
    if(ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_wakeup write MPU_PWR_MGMT1_REG error\r\n");
#endif
        return ret;
    }
    return ret;
}



/**
 * @brief set gyro fsr
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[in] fsr: gyro fsr
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_set_gyro_fsr(bsp_mpuxxx_driver_t *p_mpu_driver, uint8_t fsr)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    ret = MPUXXX_WRITE_REG(p_mpu_driver, MPU_GYRO_CFG_REG, &fsr, 1);
    if(ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_set_gyro_fsr write MPU_GYRO_CFG_REG error\r\n");
#endif
        return ret;
    }

    switch(fsr)
    {
        case 0x00: gyro_scale = 131.0; break;
        case 0x01: gyro_scale = 65.5; break;
        case 0x02: gyro_scale = 32.8; break;
        case 0x03: gyro_scale = 16.4; break;
        default:   gyro_scale = 131.0;
    }

    return ret;
}

/**
 * @brief set accel fsr
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[in] fsr: accel fsr
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_set_accel_fsr(bsp_mpuxxx_driver_t *p_mpu_driver, uint8_t fsr)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    ret = MPUXXX_WRITE_REG(p_mpu_driver, MPU_ACCEL_CFG_REG, &fsr, 1);
    if(ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_set_accel_fsr write MPU_ACCEL_CFG_REG error\r\n");
#endif
        return ret;
    }

    switch(fsr)
    {
        case 0x00: accel_scale = 16384.0; break;
        case 0x01: accel_scale = 8192.0; break;
        case 0x02: accel_scale = 4096.0; break;
        case 0x03: accel_scale = 2048.0; break;
        default:   accel_scale = 16384.0;
    }

    return ret;
}

/**
 * @brief set lpf
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[in] lpf: lpf
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_set_lpf(bsp_mpuxxx_driver_t *p_mpu_driver, uint8_t lpf)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    ret = MPUXXX_WRITE_REG(p_mpu_driver, MPU_CFG_REG, &lpf, 1);
    if(ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_set_lpf write MPU_CFG_REG error\r\n");
#endif
        return ret;
    }

    return ret;
}

/**
 * @brief set rate, Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[in] rate: rate
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_set_rate(bsp_mpuxxx_driver_t *p_mpu_driver, uint8_t rate)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    // Configure sample rate to 50Hz
    // Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
    // where Gyroscope Output Rate = 8kHz when the DLPF is disabled (DLPF_CFG = 0 or 7), and 1kHz when the DLPF is enabled

    ret = MPUXXX_WRITE_REG(p_mpu_driver, MPU_SAMPLE_RATE_REG, &rate, 1);
    if(ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_set_rate write MPU_SAMPLE_RATE_REG error\r\n");
#endif
        return ret;
    }

    return ret;
}

/**
 * @brief set interrupt enable
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[in] enable: enable
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_set_interrupt_enable(bsp_mpuxxx_driver_t *p_mpu_driver, uint8_t enable)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    ret = MPUXXX_WRITE_REG(p_mpu_driver, MPU_INT_EN_REG, &enable, 1);
    if(ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_set_interrupt_enable write MPU_INT_EN_REG error\r\n");
#endif
        return ret;
    }

    return ret;
}

/**
 * @brief set motion threshold
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[in] threshold: motion threshold
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_set_motion_threshold(bsp_mpuxxx_driver_t *p_mpu_driver, uint8_t threshold)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    ret = MPUXXX_WRITE_REG(p_mpu_driver, MPU_MOTION_DET_REG, &threshold, 1);
    if(ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_set_motion_threshold write MPU_MOTION_DET_REG error\r\n");
#endif
        return ret;
    }

    return ret;
}

/**
 * @brief set INT level
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[in] level: INT level
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_set_INT_level(bsp_mpuxxx_driver_t *p_mpu_driver, uint8_t level)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    ret = MPUXXX_WRITE_REG(p_mpu_driver, MPU_INTBP_CFG_REG, &level, 1);
    if(ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_set_INT_level write MPU_INTBP_CFG_REG error\r\n");
#endif
        return ret;
    }

    return ret;
}

/**
 * @brief set user ctrl
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[in] data: user ctrl data
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_set_user_ctrl(bsp_mpuxxx_driver_t *p_mpu_driver, uint8_t data)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    ret = MPUXXX_WRITE_REG(p_mpu_driver, MPU_USER_CTRL_REG, &data, 1);
    if(ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_set_user_ctrl write MPU_USER_CTRL_REG error\r\n");
#endif
        return ret;
    }

    return ret;
}

/**
 * @brief set pwr mgmt1 reg
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[in] data: pwr mgmt1 reg data
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_set_pwr_mgmt1_reg(bsp_mpuxxx_driver_t *p_mpu_driver, uint8_t data)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    ret = MPUXXX_WRITE_REG(p_mpu_driver, MPU_PWR_MGMT1_REG, &data, 1);
    if(ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_set_pwr_mgmt1_reg write MPU_PWR_MGMT1_REG error\r\n");
#endif
        return ret;
    }
    return ret;
}

/**
 * @brief set pwr mgmt2 reg
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[in] data: pwr mgmt2 reg data
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_set_pwr_mgmt2_reg(bsp_mpuxxx_driver_t *p_mpu_driver, uint8_t data)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    ret = MPUXXX_WRITE_REG(p_mpu_driver, MPU_PWR_MGMT2_REG, &data, 1);
    if(ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_set_pwr_mgmt2_reg write MPU_PWR_MGMT2_REG error\r\n");
#endif
        return ret;
    }
    return ret;
}

/**
 * @brief set fifo en reg
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[in] data: fifo en reg data
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_set_fifo_en_reg(bsp_mpuxxx_driver_t *p_mpu_driver, uint8_t data)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    ret = MPUXXX_WRITE_REG(p_mpu_driver, MPU_FIFO_EN_REG, &data, 1);
    if(ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_set_fifo_en_reg write MPU_FIFO_EN_REG error\r\n");
#endif
        return ret;
    }

    return ret;
}

/**
 * @brief get interrupt status reg
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[out] p_data: pointer to a uint8_t data
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_get_interrupt_status_reg(bsp_mpuxxx_driver_t *p_mpu_driver, uint8_t *p_data)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    ret = MPUXXX_READ_REG(p_mpu_driver, MPU_INT_STA_REG, p_data, 1);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_get_interrupt_status_reg read interrupt status reg error\r\n");
#endif
        return ret;
    }
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("get_interrupt_status_reg: %#x\r\n", *p_data);
#endif

    return ret;
}

/**
 * @brief get temperature
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[out] p_data: pointer to a mpu6050 data structure
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_get_temperature(bsp_mpuxxx_driver_t *p_mpu_driver, mpuxxx_data_t *p_data)
{
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("mpuxxx_get_temperature\r\n");
#endif
    mpuxxx_status_t ret = MPUxxx_OK;
    uint8_t data[2] = {0};
    int16_t temp = 0;

    ret = MPUXXX_READ_REG(p_mpu_driver, MPU_TEMP_OUTH_REG, data, 2);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_get_temperature read temperature error\r\n");
#endif
        return ret;
    }
    temp = (int16_t)(data[0] << 8 | data[1]);
    p_data->temperature = (float)(temp / 340.0 + 36.53);

    return ret;
}

/**
 * @brief get gyro
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[out] p_data: pointer to a mpu6050 data structure
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_get_gyro(bsp_mpuxxx_driver_t *p_mpu_driver, mpuxxx_data_t *p_data)
{
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("mpuxxx_get_gyro\r\n");
#endif
    mpuxxx_status_t ret = MPUxxx_OK;
	uint8_t data[6] = {0};
	
    ret = MPUXXX_READ_REG(p_mpu_driver, MPU_GYRO_XOUTH_REG, data, 6);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_get_gyro read gyro error\r\n");
#endif
        return ret;
    }
    p_data->gyro_x_raw = (int16_t)(data[0] << 8 | data[1]);
    p_data->gyro_y_raw = (int16_t)(data[2] << 8 | data[3]);
    p_data->gyro_z_raw = (int16_t)(data[4] << 8 | data[5]);

    p_data->gx = (double)(p_data->gyro_x_raw / gyro_scale);
    p_data->gy = (double)(p_data->gyro_y_raw / gyro_scale);
    p_data->gz = (double)(p_data->gyro_z_raw / gyro_scale);

    return ret;
}

/**
 * @brief get accel
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[out] p_data: pointer to a mpu6050 data structure
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_get_accel(bsp_mpuxxx_driver_t *p_mpu_driver, mpuxxx_data_t *p_data)
{
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("mpuxxx_get_accel\r\n");
#endif
    mpuxxx_status_t ret = MPUxxx_OK;
    uint8_t data[6] = {0};

    ret = MPUXXX_READ_REG(p_mpu_driver, MPU_ACCEL_XOUTH_REG, data, 6);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_get_accel read error\r\n");
#endif
        return ret;
    }
    p_data->accel_x_raw = (int16_t)(data[0] << 8 | data[1]);
    p_data->accel_y_raw = (int16_t)(data[2] << 8 | data[3]);
    p_data->accel_z_raw = (int16_t)(data[4] << 8 | data[5]);

    p_data->ax = (double)(p_data->accel_x_raw / accel_scale);
    p_data->ay = (double)(p_data->accel_y_raw / accel_scale);
    p_data->az = (double)(p_data->accel_z_raw / accel_scale);

    return ret;
}

/**
 * @brief get all data
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[out] p_data: pointer to a mpu6050 data structure
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_get_all_data(bsp_mpuxxx_driver_t *p_mpu_driver, mpuxxx_data_t *p_data)
{
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("mpuxxx_get_all_data\r\n");
#endif
    mpuxxx_status_t ret = MPUxxx_OK;
    uint8_t data[14] = {0};
    int16_t temp = 0;

    ret = MPUXXX_READ_REG(p_mpu_driver, MPU_ACCEL_XOUTH_REG, data, 14);
	if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_get_all_data read error\r\n");
#endif
        return ret;
    }
	
    p_data->accel_x_raw = (int16_t)(data[0] << 8 | data[1]);
    p_data->accel_y_raw = (int16_t)(data[2] << 8 | data[3]);
    p_data->accel_z_raw = (int16_t)(data[4] << 8 | data[5]);
    
    p_data->ax = (double)(p_data->accel_x_raw / accel_scale);
    p_data->ay = (double)(p_data->accel_y_raw / accel_scale);
    p_data->az = (double)(p_data->accel_z_raw / accel_scale);

	temp = (int16_t)(data[6] << 8 | data[7]);
    p_data->temperature = (float)(temp / 340.0 + 36.53);
									
    p_data->gyro_x_raw = (int16_t)(data[8] << 8 | data[9]);
    p_data->gyro_y_raw = (int16_t)(data[10] << 8 | data[11]);
    p_data->gyro_z_raw = (int16_t)(data[12] << 8 | data[13]);

    p_data->gx = (double)(p_data->gyro_x_raw / gyro_scale);
    p_data->gy = (double)(p_data->gyro_y_raw / gyro_scale);
    p_data->gz = (double)(p_data->gyro_z_raw / gyro_scale);
    
    return ret;
}

/**
 * @brief fifo init
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_fifo_init(bsp_mpuxxx_driver_t *p_mpu_driver)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    // reset fifo
    ret = mpuxxx_set_user_ctrl(p_mpu_driver, FIFO_RESET_BIT(1));
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_fifo_init reset fifo error\r\n");
#endif
        return ret;
    }

    // Wait for reset to complete
#ifdef OS_SUPPORTING
    p_mpu_driver->p_yield_interface->pf_rtos_yield(10);
#else
    p_mpu_driver->p_delay_interface->pf_delay_ms(10);
#endif

    // Configure FIFO enable register, note the configuration order
    ret = mpuxxx_set_fifo_en_reg(p_mpu_driver,
                                 ACCEL_FIFO_EN_BIT(1) |  // Enable accelerometer first
                                 XG_FIFO_EN_BIT(1)    |  // Then gyroscope
                                 YG_FIFO_EN_BIT(1)    |
                                 ZG_FIFO_EN_BIT(1));
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_fifo_init configure fifo enable register error\r\n");
#endif
        return ret;
    }

    // Enable FIFO last
    ret = mpuxxx_set_user_ctrl(p_mpu_driver, FIFO_EN_BIT(1));
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_fifo_init enable fifo error\r\n");
#endif
        return ret;
    }

    // Configure interrupt
    ret = mpuxxx_set_INT_level(p_mpu_driver, INT_RD_CLEAR_BIT(1) | INT_LEVEL_BIT(1));
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_fifo_init configure interrupt error\r\n");
#endif
        return ret;
    }

    // Enable FIFO overflow interrupt
    ret = mpuxxx_set_interrupt_enable(p_mpu_driver, FIFO_OVERFLOW_EN_BIT(1));
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_fifo_init enable fifo overflow interrupt error\r\n");
#endif
        return ret;
    }

    return ret;
}

/**
 * @brief read fifo when fifo overflow interrupt occur
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[out] p_data: pointer to a mpu6050 data structure array
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_read_fifo_isr_occur(bsp_mpuxxx_driver_t *p_mpu_driver, mpuxxx_data_t *p_data)
{

    mpuxxx_status_t ret = MPUxxx_OK;
#if 0  // can not be used, because the fifo data is not correct
    uint16_t fifo_count = 0;
    uint16_t fifo_packet_count = 0;
    uint8_t fifo_buffer[12] = {0};

    // Get FIFO count
    ret = MPUXXX_READ_REG(p_mpu_driver, MPU_FIFO_CNTH_REG, fifo_buffer, 2);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_read_fifo_isr_occur read FIFO count error\r\n");
#endif
        return ret;
    }

    fifo_count = (fifo_buffer[0] << 8) | fifo_buffer[1];
    
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("mpuxxx_read_fifo_isr_occur fifo_count: %u\r\n", fifo_count);
#endif
    
    // Read FIFO data in chunks of 12 bytes (6 bytes accel + 6 bytes gyro)
    if (fifo_count >= 12)
    {
        fifo_packet_count = fifo_count / 12;

        for (uint16_t i = 0; i < fifo_packet_count; i++)
        {
            ret = MPUXXX_READ_REG(p_mpu_driver, MPU_FIFO_RW_REG, fifo_buffer, 12);
            if (ret != MPUxxx_OK)
            {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
                DEBUG_OUT("mpuxxx_read_fifo read FIFO data error\r\n");
#endif
                return ret;
            }

            // Process accel data
            p_data[i].accel_x_raw = (int16_t)(fifo_buffer[0] << 8 | fifo_buffer[1]);
            p_data[i].accel_y_raw = (int16_t)(fifo_buffer[2] << 8 | fifo_buffer[3]);
            p_data[i].accel_z_raw = (int16_t)(fifo_buffer[4] << 8 | fifo_buffer[5]);

            // Process gyro data
            p_data[i].gyro_x_raw = (int16_t)(fifo_buffer[6]  << 8 | fifo_buffer[7]);
            p_data[i].gyro_y_raw = (int16_t)(fifo_buffer[8]  << 8 | fifo_buffer[9]);
            p_data[i].gyro_z_raw = (int16_t)(fifo_buffer[10] << 8 | fifo_buffer[11]);
            
            // Convert raw data to physical units
            p_data[i].ax = (double)(p_data[i].accel_x_raw / accel_scale);
            p_data[i].ay = (double)(p_data[i].accel_y_raw / accel_scale);
            p_data[i].az = (double)(p_data[i].accel_z_raw / accel_scale);
            
            p_data[i].gx = (double)(p_data[i].gyro_x_raw / gyro_scale);
            p_data[i].gy = (double)(p_data[i].gyro_y_raw / gyro_scale);
            p_data[i].gz = (double)(p_data[i].gyro_z_raw / gyro_scale);
			            
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
		DEBUG_OUT("fifo data:\r\n");
        DEBUG_OUT("ax: %lf, ay: %lf, az: %lf, gx: %lf, gy: %lf, gz: %lf\r\n",\
                  p_data[i].ax,
                  p_data[i].ay,
                  p_data[i].az,
                  p_data[i].gx,
                  p_data[i].gy,
                  p_data[i].gz );
#endif
        }
    }
#endif
    return ret;
}

/**
 * @brief read fifo by reading one packet
 *        only can be used when  ACCEL_FIFO_EN_BIT
                                 XG_FIFO_EN_BIT
                                 YG_FIFO_EN_BIT
                                 ZG_FIFO_EN_BIT    are sets
 * 
 * @param[in]  p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[out] p_data: pointer to a mpu6050 data structure
 * 
 * @data: 2024-12-11
 * 
 * @version: 1.0.0
 * 
 * @return mpuxxx_status_t
*/
#if 0
static mpuxxx_status_t mpuxxx_read_fifo_packet(bsp_mpuxxx_driver_t *p_mpu_driver, mpuxxx_data_t *p_data)
{
    mpuxxx_status_t ret = MPUxxx_OK;
    uint16_t fifo_count = 0;
    uint8_t fifo_buffer[12] = {0};

    // Get FIFO count
    ret = MPUXXX_READ_REG(p_mpu_driver, MPU_FIFO_CNTH_REG, fifo_buffer, 2);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_read_fifo read FIFO count error\r\n");
#endif
        return ret;
    }

    fifo_count = (fifo_buffer[0] << 8) | fifo_buffer[1];
    
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("mpuxxx_read_fifo fifo_count: %u\r\n", fifo_count);
#endif
    
    // Read FIFO data in chunks of 12 bytes (6 bytes accel + 6 bytes gyro)

    if (fifo_count >= 12)
    {
        ret = MPUXXX_READ_REG(p_mpu_driver, MPU_FIFO_RW_REG, fifo_buffer, 12);
        if (ret != MPUxxx_OK)
        {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
            DEBUG_OUT("mpuxxx_read_fifo read FIFO data error\r\n");
#endif
            return ret;
        }

        // Process accel data
        p_data->accel_x_raw = (int16_t)(fifo_buffer[0] << 8 | fifo_buffer[1]);
        p_data->accel_y_raw = (int16_t)(fifo_buffer[2] << 8 | fifo_buffer[3]);
        p_data->accel_z_raw = (int16_t)(fifo_buffer[4] << 8 | fifo_buffer[5]);

        // Process gyro data
        p_data->gyro_x_raw = (int16_t)(fifo_buffer[6]  << 8 | fifo_buffer[7]);
        p_data->gyro_y_raw = (int16_t)(fifo_buffer[8]  << 8 | fifo_buffer[9]);
        p_data->gyro_z_raw = (int16_t)(fifo_buffer[10] << 8 | fifo_buffer[11]);
        
        // Convert raw data to physical units
        p_data->ax = (double)(p_data->accel_x_raw / accel_scale);
        p_data->ay = (double)(p_data->accel_y_raw / accel_scale);
        p_data->az = (double)(p_data->accel_z_raw / accel_scale);
        
        p_data->gx = (double)(p_data->gyro_x_raw / gyro_scale);
        p_data->gy = (double)(p_data->gyro_y_raw / gyro_scale);
        p_data->gz = (double)(p_data->gyro_z_raw / gyro_scale);

#ifdef DEBUG_SENSOR_MPU6050_HANDLER
		DEBUG_OUT("fifo data:\r\n");
        DEBUG_OUT("ax: %lf, ay: %lf, az: %lf, gx: %lf, gy: %lf, gz: %lf\r\n",\
                  p_data->ax,
                  p_data->ay,
                  p_data->az,
                  p_data->gx,
                  p_data->gy,
                  p_data->gz );
#endif
    }
    
    return ret;
}
#endif 

/**
 * @brief read fifo by reading one packet
 *        only can be used when  ACCEL_FIFO_EN_BIT
                                 XG_FIFO_EN_BIT
                                 YG_FIFO_EN_BIT
                                 ZG_FIFO_EN_BIT    are sets
 * 
 * @param[in]  p_mpu_driver: pointer to a mpu6050 driver structure
 * @param[out] p_data: pointer to a mpu6050 data structure
 * 
 * @data: 2024-12-18
 * 
 * @version: 1.1.0
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_read_fifo_packet(bsp_mpuxxx_driver_t *p_mpu_driver, mpuxxx_data_t *p_data)
{
    mpuxxx_status_t ret = MPUxxx_OK;
    uint16_t fifo_count = 0;
    uint16_t fifo_packet_count = 0;
    uint8_t fifo_buffer[12] = {0};

    // Get FIFO count
    ret = MPUXXX_READ_REG(p_mpu_driver, MPU_FIFO_CNTH_REG, fifo_buffer, 2);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_read_fifo read FIFO count error\r\n");
#endif
        return ret;
    }

    fifo_count = (fifo_buffer[0] << 8) | fifo_buffer[1];
    
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("mpuxxx_read_fifo fifo_count: %u\r\n", fifo_count);
#endif
    
    // Read FIFO data in chunks of 12 bytes (6 bytes accel + 6 bytes gyro)

    if (fifo_count >= 12)
    {
        fifo_packet_count = fifo_count / 12;

        for (uint16_t i = 0; i < fifo_packet_count; i++)
        {
            ret = MPUXXX_READ_REG(p_mpu_driver, MPU_FIFO_RW_REG, fifo_buffer, 12);
            if (ret != MPUxxx_OK)
            {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
                DEBUG_OUT("mpuxxx_read_fifo read FIFO data error\r\n");
#endif
                return ret;
            }

            // Process accel data
            p_data[i].accel_x_raw = (int16_t)(fifo_buffer[0] << 8 | fifo_buffer[1]);
            p_data[i].accel_y_raw = (int16_t)(fifo_buffer[2] << 8 | fifo_buffer[3]);
            p_data[i].accel_z_raw = (int16_t)(fifo_buffer[4] << 8 | fifo_buffer[5]);

            // Process gyro data
            p_data[i].gyro_x_raw = (int16_t)(fifo_buffer[6]  << 8 | fifo_buffer[7]);
            p_data[i].gyro_y_raw = (int16_t)(fifo_buffer[8]  << 8 | fifo_buffer[9]);
            p_data[i].gyro_z_raw = (int16_t)(fifo_buffer[10] << 8 | fifo_buffer[11]);
            
            // Convert raw data to physical units
            p_data[i].ax = (double)(p_data[i].accel_x_raw / accel_scale);
            p_data[i].ay = (double)(p_data[i].accel_y_raw / accel_scale);
            p_data[i].az = (double)(p_data[i].accel_z_raw / accel_scale);
            
            p_data[i].gx = (double)(p_data[i].gyro_x_raw / gyro_scale);
            p_data[i].gy = (double)(p_data[i].gyro_y_raw / gyro_scale);
            p_data[i].gz = (double)(p_data[i].gyro_z_raw / gyro_scale);

#ifdef DEBUG_SENSOR_MPU6050_HANDLER
            DEBUG_OUT("fifo data:\r\n");
            DEBUG_OUT("ax: %lf, ay: %lf, az: %lf, gx: %lf, gy: %lf, gz: %lf\r\n",\
                    p_data[i].ax,
                    p_data[i].ay,
                    p_data[i].az,
                    p_data[i].gx,
                    p_data[i].gy,
                    p_data[i].gz );
#endif
        }
    }
    
    return ret;
}

/**
 * @brief mpu6050 motion init
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_motion_init(bsp_mpuxxx_driver_t *p_mpu_driver)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    // motion detect threshold
    ret = mpuxxx_set_motion_threshold(p_mpu_driver, MOT_THR_BIT(0x10));
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_motion_init write (MPU_MOTION_DET_REG) motion detect reg error\r\n");
#endif
        return ret;
    }

    // motion detect interrupt active low
    ret = mpuxxx_set_INT_level(p_mpu_driver, ( INT_RD_CLEAR_BIT(1) | INT_LEVEL_BIT(1) ));
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_motion_init write (MPU_INTBP_CFG_REG) motion detect reg error\r\n");
#endif
        return ret;
    }

    // enable motion detect interrupt and enable data ready interrupt(0x41)
    //data = 0x41;

    // enable motion detect interrupt(0x40)
    ret = mpuxxx_set_interrupt_enable(p_mpu_driver, MOT_EN_BIT(1));
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_motion_init write (MPU_INTBP_CFG_REG) motion detect reg error\r\n");
#endif
        return ret;
    } 

    return ret;
}

/**
 * @brief mpuxxx init
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_init(bsp_mpuxxx_driver_t *p_mpu_driver)
{
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("mpuxxx_init start\r\n");
#endif
    mpuxxx_status_t ret = MPUxxx_OK;
    uint8_t id = 0;
    
#ifndef OS_SUPPORTING
    p_mpu_driver->p_delay_interface->pf_delay_init();
#endif

    // Initialize I2C
    p_mpu_driver->p_iic_driver_interface->pf_iic_init(NULL);

    // Reset MPU6050
    // Reset bit
    ret = mpuxxx_set_pwr_mgmt1_reg(p_mpu_driver, DEVICE_RESET_BIT(1)); 
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_init RESET error\r\n");
#endif
        return ret;
    }
                                 
#ifdef OS_SUPPORTING
    p_mpu_driver->p_yield_interface->pf_rtos_yield(100);
#else
    p_mpu_driver->p_delay_interface->pf_delay_ms(100);
#endif

    // Wake up MPU6050
    // Clear sleep bit
    ret = mpuxxx_wakeup(p_mpu_driver);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_init WAKE UP error\r\n");
#endif
        return ret;
    }

    // Configure Gyroscope for ±2000 dps (0x03 << 3)
    ret = mpuxxx_set_gyro_fsr(p_mpu_driver, FS_SEL_BIT(0X03));
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_init gyro config error\r\n");
#endif
        return ret;
    }

    // Configure Accelerometer for ±2g (0x00 << 3)
    ret = mpuxxx_set_accel_fsr(p_mpu_driver, AFS_SEL_BIT(0x00));
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_init accel config error\r\n");
#endif
        return ret;
    }

    // Configure sample rate to 50Hz
    // Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
    // where Gyroscope Output Rate = 8kHz when the DLPF is disabled (DLPF_CFG = 0 or 7), and 1kHz 
    // when the DLPF is enabled
    // 50Hz = 1000 / (1 + 19), so SMPLRT_DIV = 19
    // 0x04 : 200hz
    ret = mpuxxx_set_rate(p_mpu_driver, SMPLRT_DIV_BIT(0x19));
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_init sample rate config error\r\n");
#endif
        return ret;
    }

    // Configure DLPF, This value should be half of the sampling rate
    // when the sample rate is 50Hz, the DLPF should be 25Hz
    ret = mpuxxx_set_lpf(p_mpu_driver, DLPF_CFG_BIT(0x04));
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_init DLPF config error\r\n");
#endif
        return ret;
    }
	
#if 0
    // Disable all interrupts
    ret = mpuxxx_set_interrupt_enable(p_mpu_driver, COLOSE_ALL);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_init interrupt disable error\r\n");
#endif
        return ret;
    }
#endif
	
#if 1
	// open data ready interrupt
	ret = mpuxxx_set_interrupt_enable(p_mpu_driver, DATA_RDY_EN_BIT(1));
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_init interrupt disable error\r\n");
#endif
        return ret;
    }
#endif

    // Verify device ID
    ret = MPUXXX_READ_REG(p_mpu_driver, MPU_DEVICE_ID_REG, &id, 1);
    if (ret != MPUxxx_OK || id != MPU_ID)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_init device ID verification failed, ID: %#x\r\n", id);
#endif
        return MPUxxx_ERROR;
    }

#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("mpuxxx_init completed successfully, device ID: %#x\r\n", id);
#endif

    // Set clock source to PLL with X axis gyroscope reference
    ret = mpuxxx_set_pwr_mgmt1_reg(p_mpu_driver, CLKSEL_BIT(0x01) ); 
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_init CLKSEL error\r\n");
#endif
        return ret;
    }

    // Disable gyroscope standby
    ret = mpuxxx_set_pwr_mgmt2_reg(p_mpu_driver, 
                                                LP_WAKE_CTRL_BIT(0) | 
                                                STBY_XA_BIT(0)      | 
                                                STBY_YA_BIT(0)      | 
                                                STBY_ZA_BIT(0)      | 
                                                STBY_XG_BIT(0)      | 
                                                STBY_YG_BIT(0)      | 
                                                STBY_ZG_BIT(0) );
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("mpuxxx_init gyro standby error\r\n");
#endif
        return ret;
    }

    return MPUxxx_OK;
}

/**
 * @brief mpu6050 deinit
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t mpuxxx_deinit(bsp_mpuxxx_driver_t *p_mpu_driver)
{
    if (g_is_inited == MPUXXX_NOT_INITED)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("bsp_mpuxxx_driver_deinit not inited\r\n");
#endif
        return MPUxxx_ERROR;
    }

    g_is_inited = MPUXXX_NOT_INITED;

    return MPUxxx_OK;
}

/**
 * @brief mpuxxx INT interrupt callback
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * 
 * @return void
*/
void int_interrupt_callback(void *mpu_driver, void *mpu_data)
{
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("int_interrupt_callback start\r\n");
#endif
    mpuxxx_status_t ret = MPUxxx_OK;
    bsp_mpuxxx_driver_t *p_mpu_driver = NULL;
	
    if (NULL == mpu_driver)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("int_interrupt_callback parameter error\r\n");
#endif
    }

    p_mpu_driver = (bsp_mpuxxx_driver_t *)mpu_driver;

    // if not os supporting, get all data
#ifndef OS_SUPPORTING
	
    ret = mpuxxx_get_all_data(p_mpu_driver, (mpuxxx_data_t *)mpu_data);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("int_interrupt_callback mpuxxx_get_all_data error\r\n");
        DEBUG_OUT("ret = %d\r\n", ret);
#endif
    }

#else
    // 1. get buffer address
    uint8_t *wbuff = NULL;
	uint8_t data = 0;
    wbuff = circular_buf.pfget_wbuffer_addr(&circular_buf);
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("int_interrupt_callback wbuff = %p\r\n", wbuff);
#endif

    // 2. close interrupt of mpuxxx
    ret = mpuxxx_set_interrupt_enable(p_mpu_driver, COLOSE_ALL);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("int_interrupt_callback write interrupt enable reg error\r\n");
        DEBUG_OUT("ret = %d\r\n", ret);
#endif
    }
	
    //3. read the stauts of interrupt register
    ret = mpuxxx_get_interrupt_status_reg(p_mpu_driver, &data);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("int_interrupt_callback read inter reg data 11 error\r\n");
        DEBUG_OUT("ret = %d\r\n", ret);
#endif
    }

#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("int_interrupt_callback read inter reg data 11 = %#x", data);
#endif
    ret = mpuxxx_get_interrupt_status_reg(p_mpu_driver, &data);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("int_interrupt_callback read inter reg data 22 error\r\n");
        DEBUG_OUT("ret = %d\r\n", ret);
#endif
    }
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("int_interrupt_callback read inter reg data 22 = %#x", data);
#endif
    // get timestamp
    uint32_t timestamp_start = p_mpu_driver->p_timebase_interface->pf_get_tick_count();

#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("get timestamp start : %d\r\n", timestamp_start);
#endif
	// read data by dma
    ret = p_mpu_driver->p_iic_driver_interface->pf_iic_mem_read_dma(
                                    p_mpu_driver->p_iic_driver_interface->hi2c, 
                                    (MPU_ADDR << 1) | 1, 
                                    MPU_ACCEL_XOUTH_REG, 
                                    IIC_MEMADD_SIZE_8BIT, 
                                    wbuff, 
                                    circular_buf.size);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("int_interrupt_callback read accel data error\r\n");
        DEBUG_OUT("ret = %d\r\n", ret);
#endif
    }
#endif /* End of OS_SUPPORTING */

#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("int_interrupt_callback end\r\n");
#endif
}

/**
 * @brief mpu6050 dma interrupt callback
 * 
 * @param[in] p_mpu_driver: pointer to a mpu6050 driver structure
 * 
 * @return void
*/
void dma_interrupt_callback(void *mpu_driver, void *mpu_data)
{
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("dma_interrupt_callback start\r\n");
#endif
    mpuxxx_status_t ret = MPUxxx_OK;
	bsp_mpuxxx_driver_t *p_mpu_driver = NULL;

    if (NULL == mpu_driver)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("int_interrupt_callback parameter error\r\n");
#endif
    }

    p_mpu_driver = (bsp_mpuxxx_driver_t *)mpu_driver;

    uint32_t timestamp_end = p_mpu_driver->p_timebase_interface->pf_get_tick_count();
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("get timestamp end : %d\r\n", timestamp_end);
#endif

    // open data ready interrupt
    ret = mpuxxx_set_interrupt_enable(p_mpu_driver, DATA_RDY_EN_BIT(1) );
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("dma_interrupt_callback open interrupt error\r\n");
        DEBUG_OUT("ret = %d\r\n", ret);
#endif
    }

#ifdef OS_SUPPORTING
    // change the buffer address
    circular_buf.pfdata_writed(&circular_buf);

    // notify the handler
    if (p_mpu_driver->queue_handle == NULL)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("queue_handle is NULL\r\n");
#endif
    }
    uint8_t tx_data = 1;
    ret = p_mpu_driver->p_os_interface->os_queue_put_isr(
                                    p_mpu_driver->queue_handle,
                                    &tx_data,
                                    NULL
                                    );
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("dma_interrupt_callback put queue error\r\n");
        DEBUG_OUT("ret = %d\r\n", ret);
#endif
    }
#endif

 #ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("dma_interrupt_callback end\r\n");
#endif     
}

/**
 * @brief mpu6050 driver init
 * 
 * @param[in] pmpu_driver: pointer to a mpu6050 driver structure
 * 
 * @return mpuxxx_status_t
*/
static mpuxxx_status_t bsp_mpuxxx_driver_init(bsp_mpuxxx_driver_t *pmpu_driver)
{
    mpuxxx_status_t ret = MPUxxx_OK;

    if (g_is_inited == MPUXXX_INITED)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("bsp_mpuxxx_driver_init already inited\r\n");
#endif
        return MPUxxx_ERROR;
    }

#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("bsp_mpuxxx_driver_init start\r\n");
#endif

    ret = mpuxxx_init(pmpu_driver);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("bsp_mpuxxx_driver_init mpuxxx_init error\r\n");
#endif
        return ret;
    }

#if 0
    ret = mpuxxx_motion_init(pmpu_driver);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("bsp_mpuxxx_driver_init mpuxxx_init error\r\n");
#endif
        return ret;
    }
#endif

   ret = mpuxxx_fifo_init(pmpu_driver);
   if (ret != MPUxxx_OK)
   {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
       DEBUG_OUT("bsp_mpuxxx_driver_init mpuxxx_fifo_init error\r\n");
#endif
       return ret;
   }

#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("bsp_mpuxxx_driver_init end\r\n");
#endif
    return MPUxxx_OK;
}

/**
 * @brief mpu6050 driver instance
 * 
 * @param[in] p_mpuxxx_driver: pointer to a mpu6050 driver structure
 * @param[in] p_iic_driver_interface: pointer to a iic driver interface
 * @param[in] p_yield_interface: pointer to a yield interface
 * @param[in] p_os_interfece: pointer to a os interface
 * @param[in] p_timebase_interface: pointer to a timebase interface
 * @param[in] callback_register: pointer to a callback function
 * @param[in] callback_register_dma: pointer to a callback function
 * 
 * @return mpuxxx_status_t
*/
mpuxxx_status_t bsp_mpuxxx_driver_inst(
                bsp_mpuxxx_driver_t    *p_mpuxxx_driver,
                mpuxxx_iic_driver_interface_t *p_iic_driver_interface,
#ifdef OS_SUPPORTING
                mpuxxx_yield_interface_t      *p_yield_interface,
                mpuxxx_os_interface_t         *p_os_interfece,
#endif /* End of OS_SUPPORTING */
                mpuxxx_delay_interface_t      *p_delay_interface,
                mpuxxx_timebase_interface_t   *p_timebase_interface,
                void (*callback_register)    (void (*callback)(void *, void *)),
                void (*callback_register_dma)(void (*callback)(void *, void *))
#ifdef OS_SUPPORTING
                ,void *queue_handle
#endif /* End of OS_SUPPORTING */
                                                                            )
{
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("bsp_mpuxxx_driver_inst start\r\n");
#endif

    mpuxxx_status_t ret = MPUxxx_OK;

    if (NULL == p_mpuxxx_driver        || 
        NULL == p_iic_driver_interface || 
        NULL == p_timebase_interface   ||
        NULL == p_delay_interface
#ifdef OS_SUPPORTING
        || NULL == p_yield_interface 
        || NULL == p_os_interfece 
#endif /* End of OS_SUPPORTING */
        || NULL == callback_register 
        || NULL == callback_register_dma)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("bsp_mpuxxx_driver_inst parameter error\r\n");
#endif
        ret = MPUxxx_ERRORPARAMETER;
    }

    p_mpuxxx_driver->p_iic_driver_interface = p_iic_driver_interface;

    if (NULL == p_iic_driver_interface->pf_iic_init      || 
        NULL == p_iic_driver_interface->pf_iic_deinit    ||
        NULL == p_iic_driver_interface->pf_iic_mem_write ||
        NULL == p_iic_driver_interface->pf_iic_mem_read  ||
        NULL == p_iic_driver_interface->pf_iic_mem_read_dma)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("bsp_mpuxxx_driver_inst iic driver interface error\r\n");
#endif
        ret = MPUxxx_ERRORRESOURCE;
    }

#ifdef OS_SUPPORTING
    p_mpuxxx_driver->p_yield_interface = p_yield_interface;

    if (NULL == p_mpuxxx_driver->p_yield_interface->pf_rtos_yield)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("bsp_mpuxxx_driver_inst yield interface or os interface error\r\n");
#endif
        ret = MPUxxx_ERRORRESOURCE;
    }

	p_mpuxxx_driver->p_os_interface = p_os_interfece;

    if (NULL == p_mpuxxx_driver->p_os_interface->os_queue_create            ||
        NULL == p_mpuxxx_driver->p_os_interface->os_queue_delete            || 
        NULL == p_mpuxxx_driver->p_os_interface->os_queue_put               ||
		NULL == p_mpuxxx_driver->p_os_interface->os_queue_put_isr           ||
        NULL == p_mpuxxx_driver->p_os_interface->os_queue_get               ||
        NULL == p_mpuxxx_driver->p_os_interface->os_semaphore_create_mutex  ||
        NULL == p_mpuxxx_driver->p_os_interface->os_semaphore_delete_mutex  ||
        NULL == p_mpuxxx_driver->p_os_interface->os_semaphore_lock_mutex    ||
        NULL == p_mpuxxx_driver->p_os_interface->os_semaphore_unlock_mutex  ||
        NULL == p_mpuxxx_driver->p_os_interface->os_semaphore_create_binary ||
        NULL == p_mpuxxx_driver->p_os_interface->os_semaphore_delete_binary ||
        NULL == p_mpuxxx_driver->p_os_interface->os_semaphore_wait_binary   ||
        NULL == p_mpuxxx_driver->p_os_interface->os_semaphore_signal_binary)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("bsp_mpuxxx_driver_inst os interface error\r\n");
#endif
        ret = MPUxxx_ERRORRESOURCE;
    }
#endif /* End of OS_SUPPORTING */

    p_mpuxxx_driver->p_delay_interface = p_delay_interface;

    if (NULL == p_mpuxxx_driver->p_delay_interface->pf_delay_init ||
        NULL == p_mpuxxx_driver->p_delay_interface->pf_delay_us   ||
        NULL == p_mpuxxx_driver->p_delay_interface->pf_delay_ms)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("bsp_mpuxxx_driver_inst delay interface error\r\n");
#endif
        ret = MPUxxx_ERRORRESOURCE;
    }

    p_mpuxxx_driver->p_timebase_interface = p_timebase_interface;

    if (NULL == p_mpuxxx_driver->p_timebase_interface->pf_get_tick_count)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("bsp_mpuxxx_driver_inst timebase interface error\r\n");
#endif
        ret = MPUxxx_ERRORRESOURCE;
    }

    p_mpuxxx_driver->pf_sleep                    = mpuxxx_sleep;
    p_mpuxxx_driver->pf_wakeup                   = mpuxxx_wakeup;
    p_mpuxxx_driver->pf_deinit                   = mpuxxx_deinit;
    p_mpuxxx_driver->pf_set_gyro_fsr             = mpuxxx_set_gyro_fsr;
    p_mpuxxx_driver->pf_set_accel_fsr            = mpuxxx_set_accel_fsr;
    p_mpuxxx_driver->pf_set_lpf                  = mpuxxx_set_lpf;
    p_mpuxxx_driver->pf_set_rate                 = mpuxxx_set_rate;
    p_mpuxxx_driver->pf_set_interrupt_enable     = mpuxxx_set_interrupt_enable;
    p_mpuxxx_driver->pf_set_motion_threshold     = mpuxxx_set_motion_threshold;
    p_mpuxxx_driver->pf_set_INT_level            = mpuxxx_set_INT_level;
    p_mpuxxx_driver->pf_set_user_ctrl            = mpuxxx_set_user_ctrl;
    p_mpuxxx_driver->pf_set_pwr_mgmt1_reg        = mpuxxx_set_pwr_mgmt1_reg;
    p_mpuxxx_driver->pf_set_pwr_mgmt2_reg        = mpuxxx_set_pwr_mgmt2_reg;
    p_mpuxxx_driver->pf_set_fifo_en_reg          = mpuxxx_set_fifo_en_reg;
    p_mpuxxx_driver->pf_get_temperature          = mpuxxx_get_temperature;
    p_mpuxxx_driver->pf_get_accel                = mpuxxx_get_accel;
    p_mpuxxx_driver->pf_get_gyro                 = mpuxxx_get_gyro;
    p_mpuxxx_driver->pf_get_all_data             = mpuxxx_get_all_data;
    p_mpuxxx_driver->pf_get_interrupt_status_reg = mpuxxx_get_interrupt_status_reg;
    p_mpuxxx_driver->pf_read_fifo_packet         = mpuxxx_read_fifo_packet;
    p_mpuxxx_driver->pf_read_fifo_isr_occur      = mpuxxx_read_fifo_isr_occur;
    
    p_mpuxxx_driver->queue_handle = queue_handle;

    ret = bsp_mpuxxx_driver_init(p_mpuxxx_driver);
    if (ret != MPUxxx_OK)
    {
#ifdef DEBUG_SENSOR_MPU6050_HANDLER
        DEBUG_OUT("bsp_mpuxxx_driver_inst bsp_mpuxxx_driver_init error\r\n");
#endif
        return ret;
    }
    
    callback_register    (int_interrupt_callback);
    callback_register_dma(dma_interrupt_callback);
        
    g_is_inited = MPUXXX_INITED;

#ifdef DEBUG_SENSOR_MPU6050_HANDLER
    DEBUG_OUT("bsp_mpuxxx_driver_inst end\r\n");
#endif

    return ret;
}


