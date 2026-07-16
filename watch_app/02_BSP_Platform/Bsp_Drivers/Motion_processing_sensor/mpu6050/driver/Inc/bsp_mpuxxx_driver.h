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
 * 
 * @author ssj
 * 
 * @brief Provide the HAL APIs of MPU6050 and corresponding options.
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
#ifndef __BSP_MPUXXX_DRIVER_H__
#define __BSP_MPUXXX_DRIVER_H__
//******************************** Includes *********************************//
#include "bsp_mpu6050_reg.h"
#include "bsp_mpu6050_reg_bit.h"
#include "i2c.h"
#include "elog.h"

#include "circular_buffer.h"

#include <stdint.h>

//******************************** Defines **********************************//
#ifndef SYSTEM_ADAPTER_SUPPORTING  /* System adapter supporting              */
#define OS_SUPPORTING 1            /* OS supporting                          */
#endif /* SYSTEM_ADAPTER_SUPPORTING */


//******************************** Declaring ********************************//
extern circular_buffer_t circular_buf;

/*   Return values from functions    */
typedef enum
{ 
    MPUxxx_OK             = 0,          /*Operation completed successfully   */
    MPUxxx_ERROR          = 1,          /*Run-time error without case matched*/
    MPUxxx_ERRORTIMEOUT   = 2,          /*Operation failed with timeout      */
    MPUxxx_ERRORRESOURCE  = 3,          /*Resource not available             */
    MPUxxx_ERRORPARAMETER = 4,          /*Parameter error                    */
    MPUxxx_ERRORNOMEMORY  = 5,          /*Out of memory                      */
    MPUxxx_ERRORISR       = 6,          /*Not allowed in ISR context         */
    MPUxxx_RESERVED       = 0x7FFFFFFF, /*Reserved                           */
} mpuxxx_status_t;

/* From HAL Layer :       HAL_IIC    */
typedef struct
{  
    void *hi2c;             /* hi2c pointer to a I2C_HandleTypeDef structure */
    mpuxxx_status_t (*pf_iic_init)      (void *);   /* IIC init    interface */
    mpuxxx_status_t (*pf_iic_deinit)    (void *);   /* IIC deinit  interface */

    mpuxxx_status_t (*pf_iic_mem_write)(void *hi2c,
                                        uint16_t dst_address, 
                                        uint16_t mem_addr, 
                                        uint16_t mem_size, 
                                        uint8_t  *p_data, 
                                        uint16_t size, 
                                        uint32_t timeout);
    
    mpuxxx_status_t (*pf_iic_mem_read) (void *hi2c, 
                                        uint16_t dst_address, 
                                        uint16_t mem_addr, 
                                        uint16_t mem_size, 
                                        uint8_t  *p_data, 
                                        uint16_t size, 
                                        uint32_t timeout);
    // Use DMA to asynchronously read data from the I2C device's registers.                                    
    mpuxxx_status_t (*pf_iic_mem_read_dma) 
                                       (void *hi2c, 
                                        uint16_t dst_address, 
                                        uint16_t mem_addr, 
                                        uint16_t mem_size, 
                                        uint8_t  *p_data, 
                                        uint16_t size );
} mpuxxx_iic_driver_interface_t;

/* Interrupt of hardware             */
typedef struct
{
    mpuxxx_status_t (*pf_init)             (void);
    mpuxxx_status_t (*pf_deinit)           (void);
    mpuxxx_status_t (*pf_enable_interrupt) (void);
    mpuxxx_status_t (*pf_disable_interrupt)(void);
    mpuxxx_status_t (*pf_enable_clock)     (void);
    mpuxxx_status_t (*pf_disable_clock)    (void);
} hardware_interrupt_interface_t;

/* Form Core Layer :    TimeBase     */
typedef struct
{
    uint32_t (*pf_get_tick_count) (void);        /* Get tick count interface */
} mpuxxx_timebase_interface_t;

/* Store data from mpuxxx driver     */
typedef struct
{
    uint8_t *(*pf_buffer_init) (uint8_t size);
    uint8_t *(*pf_get_rbuffer_addr) (void);
    uint8_t *(*pf_get_wbuffer_addr) (void);
} buffer_interface_t;

typedef struct
{
    void (*pf_delay_init) (void);               /* Delay init interface    */
    void (*pf_delay_us) (const uint32_t);       /* Delay us interface      */
    void (*pf_delay_ms) (const uint32_t);       /* Delay ms interface      */
} mpuxxx_delay_interface_t;

/* From OS Layer :       OS_Delay    */
#ifdef OS_SUPPORTING
typedef struct
{
    void (*pf_rtos_yield) (const uint32_t);         /* OS No-Blocking delay  */
} mpuxxx_yield_interface_t;

typedef struct
{
    mpuxxx_status_t (*os_queue_create)
                                    (uint32_t const item_num, 
                                    uint32_t const item_size, 
                                    void ** const queue_handle);
    mpuxxx_status_t (*os_queue_put)
                                    (void * const queue_handle,
                                    void * const item, 
                                    uint32_t const timeout);
	mpuxxx_status_t (*os_queue_put_isr)
									(void * const queue_handle,
									void * const item, 
									long * const HigherPriorityTaskWoken);
    mpuxxx_status_t (*os_queue_get)
                                    (void * const queue_handle,
                                    void * const item, 
                                    uint32_t const timeout);
    mpuxxx_status_t (*os_queue_delete)
                                    (void * const queue_handle);

    mpuxxx_status_t (*os_semaphore_create_mutex) (void **mutex_handle);
    mpuxxx_status_t (*os_semaphore_delete_mutex) (void * const mutex_handle);
    mpuxxx_status_t (*os_semaphore_lock_mutex)   (void * const mutex_handle);
    mpuxxx_status_t (*os_semaphore_unlock_mutex) (void * const mutex_handle);

    mpuxxx_status_t (*os_semaphore_create_binary) (void **binary_handle);
    mpuxxx_status_t (*os_semaphore_delete_binary) (void * const binary_handle);
    mpuxxx_status_t (*os_semaphore_wait_binary)   (void * const binary_handle);
    mpuxxx_status_t (*os_semaphore_signal_binary) (void * const binary_handle);
} mpuxxx_os_interface_t;
#endif /* End of OS_SUPPORTING       */

/* mpu6050 data form                 */
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
} mpuxxx_data_t;

/*     Driver structure              */
typedef struct bsp_mpuxxx_driver
{
    /* Core Layer */
    mpuxxx_iic_driver_interface_t           *p_iic_driver_interface;
    hardware_interrupt_interface_t          *p_interrupt_interface;
    mpuxxx_delay_interface_t                *p_delay_interface;
    mpuxxx_timebase_interface_t             *p_timebase_interface;

    /* OS Layer  */
#ifdef OS_SUPPORTING
    mpuxxx_yield_interface_t  *p_yield_interface;
    mpuxxx_os_interface_t     *p_os_interface;
    buffer_interface_t *p_buffer_interface;

    void *queue_handle;
    void *semaphore_mutex_handle;
    void *semaphore_binary_handle;

    void (*pf_dma_completed_callback)(void);
    void (*pf_int_interrupt_callback)(void);
#endif /* End of OS_SUPPORTING */

    /* Interface of mpuxxx driver    */
    mpuxxx_status_t (*pf_deinit)              (struct bsp_mpuxxx_driver *);
    mpuxxx_status_t (*pf_sleep)               (struct bsp_mpuxxx_driver *);
    mpuxxx_status_t (*pf_wakeup)              (struct bsp_mpuxxx_driver *);
    mpuxxx_status_t (*pf_set_gyro_fsr)        (struct bsp_mpuxxx_driver *, uint8_t);
    mpuxxx_status_t (*pf_set_accel_fsr)       (struct bsp_mpuxxx_driver *, uint8_t);
    mpuxxx_status_t (*pf_set_lpf)             (struct bsp_mpuxxx_driver *, uint8_t);
    mpuxxx_status_t (*pf_set_rate)            (struct bsp_mpuxxx_driver *, uint8_t);
    mpuxxx_status_t (*pf_set_interrupt_enable)(struct bsp_mpuxxx_driver *, uint8_t);
    mpuxxx_status_t (*pf_set_motion_threshold)(struct bsp_mpuxxx_driver *, uint8_t);
    mpuxxx_status_t (*pf_set_INT_level)       (struct bsp_mpuxxx_driver *, uint8_t);
    mpuxxx_status_t (*pf_set_user_ctrl)       (struct bsp_mpuxxx_driver *, uint8_t);
    mpuxxx_status_t (*pf_set_pwr_mgmt1_reg)   (struct bsp_mpuxxx_driver *, uint8_t);
    mpuxxx_status_t (*pf_set_pwr_mgmt2_reg)   (struct bsp_mpuxxx_driver *, uint8_t);
    mpuxxx_status_t (*pf_set_fifo_en_reg)     (struct bsp_mpuxxx_driver *, uint8_t);    
    mpuxxx_status_t (*pf_get_temperature)     (struct bsp_mpuxxx_driver *, mpuxxx_data_t *);
    mpuxxx_status_t (*pf_get_accel)           (struct bsp_mpuxxx_driver *, mpuxxx_data_t *);
    mpuxxx_status_t (*pf_get_gyro)            (struct bsp_mpuxxx_driver *, mpuxxx_data_t *);
    mpuxxx_status_t (*pf_get_all_data)        (struct bsp_mpuxxx_driver *, mpuxxx_data_t *);
    mpuxxx_status_t (*pf_get_interrupt_status_reg)(struct bsp_mpuxxx_driver *, uint8_t *);
    mpuxxx_status_t (*pf_read_fifo_packet)    (struct bsp_mpuxxx_driver *p_mpu_driver, 
                                                                           mpuxxx_data_t *p_data);
    mpuxxx_status_t (*pf_read_fifo_isr_occur) (struct bsp_mpuxxx_driver *p_mpu_driver, 
                                                                           mpuxxx_data_t *p_data);
} bsp_mpuxxx_driver_t;

//******************************** Functions ********************************//
/** 
 * @brief Initialize the MPU6050 driver instance with the provided interfaces 
 *        and callbacks
 * 
 * @param p_mpuxxx_driver Pointer to the MPU6050 driver structure to initialize
 * @param p_iic_driver_interface Pointer to the IIC driver interface implementation
 * @param p_yield_interface      Pointer to the yield interface (OS mode only)
 * @param p_os_interfece         Pointer to the OS interface (OS mode only) 
 * @param p_timebase_interface   Pointer to the timebase interface
 * @param callback_register      Function to register interrupt callback
 * @param callback_register_dma  Function to register DMA callback
 * @param queue_handle           Handle to queue for data transfer (OS mode only)
 * 
 * @return MPU6050_OK if successful, error code otherwise
 * 
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
                                                                            );

#endif /* End of __BSP_MPUXXX_DRIVER_H__ */

