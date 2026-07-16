/******************************************************************************
 * Copyright (C) 2025 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file bsp_cst816t_driver.h
 * 
 * @par dependencies 
 *
 * bsp_cst816t_reg_define.h
 * elog.h
 * stdint.h
 * main.h
 * 
 * @author 
 * 
 * @brief Provide the CST816T driver functions.
 * 
 * Processing flow:
 * 
 * call directly.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 * Return value description:
 * 0: Operation completed successfully
 * 1: Runtime error, no matching case
 * 2: Operation timeout failure
 * 3: Resource unavailable
 * 4: Parameter error
 * 5: Out of memory
 * 6: Not allowed to call in ISR context
 *
 *****************************************************************************/
#ifndef __BSP_CST816T_DRIVER_H
#define __BSP_CST816T_DRIVER_H

//******************************** Includes *********************************//
#include "bsp_cst816t_reg_define.h"
#include "elog.h"
#include <stdint.h>
#include "main.h"
//******************************** Defines **********************************//
#define OS_SUPPORTING              /* OS supporting                          */
#define CST816T_IIC_ADDRESS 0x15

//******************************** Declaring ********************************//
//******************************** Variables ********************************//
//******************************** Typedefs *********************************//
/* Form Core Layer :    TimeBase     */
typedef struct
{
    uint32_t (*pf_get_tick_count) (void);        /* Get tick count interface */
} cst816_timebase_interface_t;

/* From OS Layer :       OS_Delay    */
#ifdef OS_SUPPORTING
typedef struct
{
    void (*pf_rtos_yield) (const uint32_t);         /* OS No-Blocking delay  */
} cst816__yield_interface_t;
#endif /* OS_SUPPORTING */

/* From Core Layer :    GPIO Driver    */
typedef struct 
{
    uint8_t (*pf_write_reset_pin)(uint8_t state);
} gpio_opt_interface_t;

/* From Core Layer :    IIC Driver    */
typedef struct
{
    void *hi2c;             /* hi2c pointer to a I2C_HandleTypeDef structure */
    uint8_t (*pf_iic_init)      (void *);   /* IIC init    interface */
    uint8_t (*pf_iic_deinit)    (void *);   /* IIC deinit  interface */

    uint8_t (*pf_iic_mem_write)(void *hi2c,
                                uint16_t dst_address, 
                                uint16_t mem_addr, 
                                uint16_t mem_size, 
                                uint8_t *p_data, 
                                uint16_t size, 
                                uint32_t timeout);
    
    uint8_t (*pf_iic_mem_read) (void *hi2c, 
                                uint16_t dst_address, 
                                uint16_t mem_addr, 
                                uint16_t mem_size, 
                                uint8_t *p_data, 
                                uint16_t size, 
                                uint32_t timeout);
    // Use DMA to asynchronously read data from the I2C device's registers.
    uint8_t (*pf_iic_mem_read_dma)
                                (void *hi2c, 
                                uint16_t dst_address, 
                                uint16_t mem_addr, 
                                uint16_t mem_size, 
                                uint8_t *p_data, 
                                uint16_t size );
} cst816__iic_driver_interface_t;

/* Touch screen coordinate structure           */
typedef struct
{
	unsigned int x_pos;
	unsigned int y_pos;
} cst816_xy_t;

/* Gesture ID recognition options              */
typedef enum
{
	NOGESTURE   = 	0x00, // No gesture detected
    UPGLIDE     = 	0x01, // Up glide gesture
	DOWNGLIDE   = 	0x02, // Down glide gesture
	RIGHTGLIDE  = 	0x03, // Right glide gesture
	LEFTGLIDE   = 	0x04, // Left glide gesture
	CLICK       = 	0x05, // Single click gesture
	DOUBLECLICK =   0x0B, // Double click gesture
	LONGPRESS   = 	0x0C, // Long press gesture
} cst816_gesture_id_t;

/* Error reset control options   */
typedef enum
{
	ERR_RESET_DIG    = 0x00, // Large area reset function
	ERR_RESET_DOUBLE = 0x01, // Double click reset function
} cst816_err_reset_ctl_t;

/* Continuous motion configuration options     */
typedef enum
{
	MOTION_DISABLE   = 0x00, // Disable continuous motion detection
	EN_CON_LR        = 0x01, // Enable left-right continuous motion detection
	EN_CON_UD        = 0x02, // Enable up-down continuous motion detection
	EN_DCLICK        = 0x04, // Enable double click detection
	MOTION_ALLENABLE = 0x05, // Enable all motion detection
} cst816_motion_mask_t;

/* Interrupt low pulse emission mode options   */
typedef enum
{
    ONCE_WLP  = 0x00, // Only emit one low pulse signal for long press gesture
    EN_MOTION = 0x10, // Emit low pulse when gesture is detected
    EN_CHANGE = 0x20, // Emit low pulse when touch state changes
    EN_TOUCH  = 0x40, // Periodically emit low pulse when touch is detected
    EN_TEST   = 0x80, // Test mode, automatically emit periodic low pulses
} cst816_irq_ctl_t;

/* CST816T driver structure */
typedef struct bsp_cst816t_driver
{
    cst816_timebase_interface_t   *p_timebase_interface;
#ifdef OS_SUPPORTING
    cst816__yield_interface_t      *p_yield_interface;
#endif /* OS_SUPPORTING */
    cst816__iic_driver_interface_t *p_iic_driver_interface;
    gpio_opt_interface_t   *p_gpio_opt_interface;

/********** CST816T initialization functions *************/
    uint8_t (*pf_cst816t_init)(
        struct bsp_cst816t_driver * const cst816t_instance);
    uint8_t (*pf_cst816t_deinit)(
        struct bsp_cst816t_driver * const cst816t_instance);

/********** CST816T touch screen operation functions *****/
    // Get the gesture ID
    uint8_t (*pf_cst816_get_gesture_id)(
        struct bsp_cst816t_driver * const cst816t_instance,
        cst816_gesture_id_t *mode);
    // Get the touch screen coordinate
    uint8_t (*pf_cst816_get_xy_axis)(
        struct bsp_cst816t_driver * const cst816t_instance, 
        cst816_xy_t *p_xy);
    // Get the touch screen chip ID
    uint8_t (*pf_cst816_get_chipid)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t *p_chipid);
    // Get the touch screen finger number
    uint8_t (*pf_cst816_get_finger_num)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t *p_finger_num);

/********** CST816T configuration functions **************/
    uint8_t (*pf_cst816_sleep)(
        struct bsp_cst816t_driver * const cst816t_instance);
    uint8_t (*pf_cst816_wakeup)(
        struct bsp_cst816t_driver * const cst816t_instance);
    // Set the error reset control
    uint8_t (*pf_cst816_set_err_reset_ctl)(
        struct bsp_cst816t_driver * const cst816t_instance,
        cst816_err_reset_ctl_t mode);
    // Set the long press time threshold
    uint8_t (*pf_cst816_set_long_press_th)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t threshold);
    // Set the different motion enable
    uint8_t (*pf_cst816_set_motion_mask)(
        struct bsp_cst816t_driver * const cst816t_instance, 
        cst816_motion_mask_t mode);
    // Set the interrupt pulse width
    uint8_t (*pf_cst816_set_irq_pluse_width)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t pulse_width);
    // Set the normal scan period
    uint8_t (*pf_cst816_set_nor_scan_per)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t scan_period);
    // Set the motion slope angle
    uint8_t (*pf_cst816_set_motion_slope_angle)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t x_right_y_up_angle);
    // Set the auto calibration period in low power mode
    uint8_t (*pf_set_low_power_auto_wake_time)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t time);
    // Set the low power scan threshold
    uint8_t (*pf_cst816_set_lp_scan_th)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t threshold);
    // Set the low power scan range, can select 0,1,2,3
    // 3 is the default range.
    uint8_t (*pf_cst816_set_lp_scan_win)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t window);
    // Set the long press scan frequency, can select 1 - 255
    // 7 is the default frequency.
    uint8_t (*pf_cst816_set_lp_scan_freq)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t frequency);
    // Set the low power scan current, can select 1 - 255
    uint8_t (*pf_cst816_set_lp_scan_idac)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t idac);
    // Set the auto sleep time
    uint8_t (*pf_cst816_set_auto_sleep_time)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t time);
    // Set the interrupt control
    uint8_t (*pf_cst816_set_irq_ctl)(
        struct bsp_cst816t_driver * const cst816t_instance,
        cst816_irq_ctl_t mode);
    // Set the auto reset time
    uint8_t (*pf_cst816_set_auto_reset)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t time);
    // Set the long press time for reset
    uint8_t (*pf_cst816_set_long_press_time)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t time);
    // Set the IO control mode
    uint8_t (*pf_cst816_set_io_ctl)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t mode);
    // Disable auto sleep function
    uint8_t (*pf_cst816_disable_auto_sleep)(
        struct bsp_cst816t_driver * const cst816t_instance,
        uint8_t disable);    
} bsp_cst816t_driver_t;

//******************************** Functions ********************************//
uint8_t bsp_cst816t_inst(bsp_cst816t_driver_t   * const p_cst816t_instance,
                cst816_timebase_interface_t   * const p_timebase_instance,
#ifdef OS_SUPPORTING
                cst816__yield_interface_t      * const p_yield_instance,
#endif /* OS_SUPPORTING */
                cst816__iic_driver_interface_t * const p_iic_driver_instance,
                gpio_opt_interface_t   * const p_gpio_opt_instance,
                void (**pp_int_callback)(void *, void *));

#endif /* __BSP_CST816T_DRIVER_H */
