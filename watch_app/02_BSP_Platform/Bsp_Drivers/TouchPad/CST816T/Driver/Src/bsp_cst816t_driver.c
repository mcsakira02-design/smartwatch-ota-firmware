/******************************************************************************
 * Copyright (C) 2025 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file bsp_cst816t_driver.c
 * 
 * @par dependencies 
 * 
 * bsp_cst816t_driver.h
 * bsp_cst816t_reg_define.h
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
 *****************************************************************************/
//******************************** Includes *********************************//
#include "bsp_cst816t_driver.h"

//******************************** Defines **********************************//
#define CST816T_INITIALIZED   1
#define CST816T_UNINITIALIZED 0

#define IIC_MEMADD_SIZE_8BIT 0x00000001U
#define TIME_OUT_MS          1000

#define TOUCH_OFFSET_Y 15

#define CST816T_IIC_WRITE_REG(p_cst816t_instance, reg, p_data, len) \
                p_cst816t_instance->p_iic_driver_interface->pf_iic_mem_write( \
                p_cst816t_instance->p_iic_driver_interface->hi2c, \
                CST816T_IIC_ADDRESS << 1, \
                reg, \
                IIC_MEMADD_SIZE_8BIT, \
                p_data, \
                len, \
                TIME_OUT_MS)

#define CST816T_IIC_READ_REG(p_cst816t_instance, reg, p_data, len) \
                p_cst816t_instance->p_iic_driver_interface->pf_iic_mem_read( \
                p_cst816t_instance->p_iic_driver_interface->hi2c, \
                CST816T_IIC_ADDRESS << 1, \
                reg, \
                IIC_MEMADD_SIZE_8BIT, \
                p_data, \
                len, \
                TIME_OUT_MS)

//******************************** Variables ********************************//
static uint8_t g_cst816t_is_init = CST816T_UNINITIALIZED;

//******************************** Typedefs *********************************//


//******************************** Functions ********************************//
/**
 * @brief Get the gesture ID.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param mode: The gesture ID.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_get_gesture_id(
                struct bsp_cst816t_driver * const p_cst816t_instance,
                cst816_gesture_id_t *mode)
{
    uint8_t ret = 0;
    uint8_t data = 0x00;
    ret = CST816T_IIC_READ_REG(p_cst816t_instance, GESTURE_ID, &data, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_get_gesture_id: read GESTURE_ID failed!\r\n");
#endif /* DEBUG */
        return ret;
    }
    *mode = (cst816_gesture_id_t)data;
    return ret;
}

/**
 * @brief Get the touch screen coordinate.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param p_xy: The cst816_xy_t structure.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_get_xy_axis(
                struct bsp_cst816t_driver * const p_cst816t_instance, 
                cst816_xy_t *p_xy)
{
    uint8_t ret = 0;
    uint8_t data[4] = {0x00};

    ret = CST816T_IIC_READ_REG(p_cst816t_instance, X_POSH, data, 4);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_get_xy_axis: read X_POSH failed!\r\n");
#endif /* DEBUG */
        return ret;
    }
    // p_xy->x_pos = ((data[0] & 0x0f) << 8) | data[1];
    // p_xy->y_pos = ((data[2] & 0x0f) << 8) | data[3] + TOUCH_OFFSET_Y;

    // To align with ST7789's coordinate system, coordinate transformation is needed
    // Modify coordinate calculation method to achieve 180-degree rotation
    uint16_t raw_x = ((data[0] & 0x0f) << 8) | data[1];
    uint16_t raw_y = ((data[2] & 0x0f) << 8) | data[3];

    // Screen resolution is 240x320 
    p_xy->x_pos = 240 - raw_x;                    // Horizontal flip
    p_xy->y_pos = 320 - (raw_y + TOUCH_OFFSET_Y); // Vertical flip

#ifdef DEBUG
    DEBUG_OUT("bsp_cst816_get_xy_axis: x_pos = %d, y_pos = %d\r\n", p_xy->x_pos, p_xy->y_pos);
#endif /* DEBUG */
    return ret;
}

/**
 * @brief Get the chip ID.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param p_chipid: The chip ID.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_get_chipid(
                struct bsp_cst816t_driver * const p_cst816t_instance,
    uint8_t *p_chipid)
{
    uint8_t ret = 0;
    uint8_t data = 0x00;
    ret = CST816T_IIC_READ_REG(p_cst816t_instance, CHIPID, &data, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_get_chipid: read chip id failed!\r\n");
#endif /* DEBUG */
        return ret;
    }
    *p_chipid = data;
#ifdef DEBUG
    DEBUG_OUT("bsp_cst816t_init: chipid = 0x%02X\r\n", data);
#endif /* DEBUG */
    return ret;
}

/**
 * @brief Get the touch screen finger number.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param p_finger_num: The touch screen finger number.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_get_finger_num(
                struct bsp_cst816t_driver * const p_cst816t_instance,
    uint8_t *p_finger_num)
{
    uint8_t ret = 0;
    uint8_t data = 0x00;
    ret = CST816T_IIC_READ_REG(p_cst816t_instance, FINGER_NUM, &data, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_get_finger_num: read FINGER_NUM failed!\r\n");
#endif /* DEBUG */
        return ret;
    }
    *p_finger_num = data;

#ifdef DEBUG
    DEBUG_OUT("bsp_cst816_get_finger_num: finger_num = %d\r\n", data);
#endif /* DEBUG */
    return ret;
}

/**
 * @brief Put the CST816T into sleep mode.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_sleep(
                struct bsp_cst816t_driver * const p_cst816t_instance)
{
    uint8_t ret = 0;
    uint8_t data = 0x03;
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, SLEEPMODE, &data, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_sleep: write SLEEPMODE failed!\r\n");
#endif /* DEBUG */
        return ret;
    }
    return ret;
}

/**
 * @brief Wake up the CST816T.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_wakeup(
                struct bsp_cst816t_driver * const p_cst816t_instance)
{
    return 0;
}

/**
 * @brief Set the error reset control.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param mode: The error reset control mode.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_err_reset_ctl(
                struct bsp_cst816t_driver * const p_cst816t_instance,
                cst816_err_reset_ctl_t mode)
{
    uint8_t ret = 0;
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, ERRRESETCTL, (uint8_t*)&mode, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_err_reset_ctl: write ERRRESETCTL failed!\r\n");
#endif /* DEBUG */
    }
    return ret;
}

/**
 * @brief Set the long press time threshold.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param threshold: The long press time threshold.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_long_press_th(
                struct bsp_cst816t_driver * const p_cst816t_instance,
                uint8_t threshold)
{
    uint8_t ret = 0;
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, LONGPRESSTICK, &threshold, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_long_press_th: write LONGPRESSTICK failed!\r\n");
#endif /* DEBUG */
    }
    return ret;
}

/**
 * @brief Set the motion mask.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param mode: The motion mask mode.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_motion_mask(
                struct bsp_cst816t_driver * const p_cst816t_instance, 
    cst816_motion_mask_t mode)
{
    uint8_t ret = 0;
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, MOTIONMASK, (uint8_t *)&mode, 1);
    if (0 != ret)
    {
#ifdef DEBUG
    DEBUG_OUT("bsp_cst816_set_motion_mask : set mode failed!\r\n");
#endif /* End of DEBUG */
    }
    return 0;
}

/**
 * @brief Set the IRQ pulse width.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param pulse_width: The IRQ pulse width.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_irq_pluse_width(
                struct bsp_cst816t_driver * const cst816t_instance,
    uint8_t pulse_width)
{
    uint8_t ret = 0;
    if (pulse_width > 200)
    {
        pulse_width = 200;
    }
    ret = CST816T_IIC_WRITE_REG(cst816t_instance, IRQPLUSEWIDTH, 
                                &pulse_width, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_irq_pluse_width: write IRQPLUSEWIDTH failed!\r\n");
#endif /* DEBUG */
        return ret;
    }
    return 0;
}

/**
 * @brief Set the normal scan period.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param scan_period: The normal scan period.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_nor_scan_per(
                struct bsp_cst816t_driver * const p_cst816t_instance,
    uint8_t scan_period)
{
    uint8_t ret = 0;
    if (scan_period > 30)
    {
        scan_period = 30;
    }
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, NORSCANPER, 
                                &scan_period, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_nor_scan_per: write NORSCANPER failed!\r\n");
#endif /* DEBUG */
        return ret;
    }
    HAL_Delay(5);  // 添加5ms延时
    return 0;
}

/**
 * @brief Set the motion slope angle.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param x_right_y_up_angle: The motion slope angle.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_motion_slope_angle(
                struct bsp_cst816t_driver * const p_cst816t_instance,
    uint8_t x_right_y_up_angle)
{
    uint8_t ret = 0;
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, MOTIONSLANGLE, 
                                &x_right_y_up_angle, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_motion_slope_angle: write MOTIONSLOPEANGLE failed!\r\n");
#endif /* DEBUG */
        return ret;
    }
    return 0;
}

/**
 * @brief Set the auto calibration period in low power mode.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param time: The auto calibration period.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_low_power_auto_wake_time(
                struct bsp_cst816t_driver * const p_cst816t_instance,
                uint8_t time)
{
    uint8_t ret = 0;
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, LPAUTOWAKETIME, &time, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_low_power_auto_wake_time: write LPAUTOWAKETIME failed!\r\n");
#endif /* DEBUG */
    }
    return ret;
}

/**
 * @brief Configure the low power scan wake-up threshold. 
 *        Lower value means higher sensitivity. Default value is 48.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param threshold: The long press scan threshold.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_lp_scan_th(
                struct bsp_cst816t_driver * const p_cst816t_instance,
    uint8_t threshold)
{
    uint8_t ret = 0;
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, LPSCANTH, 
                                &threshold, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_lp_scan_th: write LPSCANTH failed!\r\n");
#endif /* DEBUG */
        return ret;
    }
    return 0;
}

/**
 * @brief Set the low power scan range.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param window: The scan window (0-3).
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_lp_scan_win(
                struct bsp_cst816t_driver * const p_cst816t_instance,
                uint8_t window)
{
    uint8_t ret = 0;
    if (window > 3) {
        window = 3;
    }
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, LPSCANWIN, &window, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_lp_scan_win: write LPSCANWIN failed!\r\n");
#endif /* DEBUG */
    }
    return ret;
}

/**
 * @brief Set the long press scan frequency.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param frequency: The scan frequency (1-255).
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_lp_scan_freq(
                struct bsp_cst816t_driver * const p_cst816t_instance,
                uint8_t frequency)
{
    uint8_t ret = 0;
    if (frequency == 0) {
        frequency = 1;
    }
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, LPSCANFREQ, &frequency, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_lp_scan_freq: write LPSCANFREQ failed!\r\n");
#endif /* DEBUG */
    }
    return ret;
}

/**
 * @brief Set the low power scan current.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param idac: The scan current (1-255).
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_lp_scan_idac(
                struct bsp_cst816t_driver * const p_cst816t_instance,
                uint8_t idac)
{
    uint8_t ret = 0;
    if (idac == 0) {
        idac = 1;
    }
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, LPSCANIDAC, &idac, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_lp_scan_idac: write LPSCANIDAC failed!\r\n");
#endif /* DEBUG */
    }
    return ret;
}

/**
 * @brief Set the auto sleep time.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param time: The auto sleep time.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_auto_sleep_time(
                struct bsp_cst816t_driver * const p_cst816t_instance,
    uint8_t time)
{
    uint8_t ret = 0;
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, SLEEPMODE, &time, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_auto_sleep_time: write SLEEPMODE failed!\r\n");
#endif /* DEBUG */
        return ret;
    }
    return 0;
}

/**
 * @brief Set the interrupt control mode.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param mode: The interrupt control mode.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_irq_ctl(
                struct bsp_cst816t_driver * const p_cst816t_instance,
                cst816_irq_ctl_t mode)
{
    uint8_t ret = 0;
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, IRQCTL, (uint8_t*)&mode, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_irq_ctl: write IRQCTL failed!\r\n");
#endif /* DEBUG */
    }
    return ret;
}

/**
 * @brief Set the auto reset time.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param time: The auto reset time.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_auto_reset(
                struct bsp_cst816t_driver * const p_cst816t_instance,
                uint8_t time)
{
    uint8_t ret = 0;
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, AUTORESET, &time, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_auto_reset: write AUTORESET failed!\r\n");
#endif /* DEBUG */
    }
    return ret;
}

/**
 * @brief Set the long press time.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param time: The long press time.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_long_press_time(
                struct bsp_cst816t_driver * const p_cst816t_instance,
                uint8_t time)
{
    uint8_t ret = 0;
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, LONGPRESSTIME, &time, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_long_press_time: write LONGPRESSTIME failed!\r\n");
#endif /* DEBUG */
    }
    return ret;
}

/**
 * @brief Set the IO control mode.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param mode: The IO control mode.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_set_io_ctl(
                struct bsp_cst816t_driver * const p_cst816t_instance,
                uint8_t mode)
{
    uint8_t ret = 0;
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, IOCTL, &mode, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_set_io_ctl: write IOCTL failed!\r\n");
#endif /* DEBUG */
    }
    return ret;
}

/**
 * @brief Disable auto sleep function.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param disable: 0: Enable auto sleep, 1: Disable auto sleep.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816_disable_auto_sleep(
                struct bsp_cst816t_driver * const p_cst816t_instance,
                uint8_t disable)
{
    uint8_t ret = 0;
    ret = CST816T_IIC_WRITE_REG(p_cst816t_instance, DISAUTOALEEP, &disable, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816_disable_auto_sleep: write DISAUTOALEEP failed!\r\n");
#endif /* DEBUG */
    }
    return ret;
}

/**
 * @brief Deinitialize the CST816T driver instance.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816t_deinit(
    struct bsp_cst816t_driver * const p_cst816t_instance)
{
    uint8_t ret = 0;

    return ret;
}

/**
 * @brief The interrupt callback function.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param p_data: The cst816_xy_t structure.
 */
void cst816t_int_interrupt_callback(void *p_cst816t_instance, void *p_data)
{
    uint8_t ret = 0;
    uint8_t data[4] = {0x00};
    uint8_t touch_state = 0;

    if (NULL == p_cst816t_instance || NULL == p_data)
    {
#ifdef DEBUG
        DEBUG_OUT("cst816t_int_interrupt_callback: p_cst816t_instance is NULL!\r\n");
#endif /* DEBUG */
        return;
    }
    bsp_cst816t_driver_t *p_cst816t = (bsp_cst816t_driver_t *)p_cst816t_instance;
    cst816_xy_t *p_xy = (cst816_xy_t *)p_data;

    // Check touch state first
    ret = CST816T_IIC_READ_REG(p_cst816t, FINGER_NUM, &touch_state, 1);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("cst816t_int_interrupt_callback: read touch state failed!\r\n");
#endif /* DEBUG */
        return;
    }

    // If finger is lifted, return
    if (touch_state == 0)
    {
#ifdef DEBUG
        DEBUG_OUT("cst816t_int_interrupt_callback: finger lifted!\r\n");
#endif /* DEBUG */
        return;
    }

    // Read coordinates only if touch is detected
    ret = CST816T_IIC_READ_REG(p_cst816t, X_POSH, data, 4);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("cst816t_int_interrupt_callback: read X_POSH failed!\r\n");
#endif /* DEBUG */
        return;
    }
    // To align with ST7789's coordinate system, coordinate transformation is needed
    // Modify coordinate calculation method to achieve 180-degree rotation
    uint16_t raw_x = ((data[0] & 0x0f) << 8) | data[1];
    uint16_t raw_y = ((data[2] & 0x0f) << 8) | data[3];

    // Screen resolution is 240x320 
    p_xy->x_pos = 240 - raw_x;                    // Horizontal flip
    p_xy->y_pos = 320 - (raw_y + TOUCH_OFFSET_Y); // Vertical flip

#ifdef DEBUG
    DEBUG_OUT("cst816t_int_interrupt_callback: x_pos = %d, y_pos = %d\r\n", p_xy->x_pos, p_xy->y_pos);
#endif /* DEBUG */

    cst816_gesture_id_t gesture_id;
    ret = bsp_cst816_get_gesture_id(p_cst816t, &gesture_id);
#ifdef DEBUG
    DEBUG_OUT("cst816t_int_interrupt_callback: gesture_id = %d\r\n", gesture_id);
#endif /* DEBUG */
}

/**
 * @brief Initialize the CST816T driver instance.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * 
 * @return 0: Success, other: Error code.
 */
static uint8_t bsp_cst816t_init(bsp_cst816t_driver_t * const p_cst816t_instance)
{
    uint8_t ret = 0;
    uint8_t chipid = 0;

/* 1. Check if the CST816T driver has already been CST816T_INITIALIZED */
    if (CST816T_INITIALIZED == g_cst816t_is_init)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816t_init: CST816T driver has already CST816T_INITIALIZED!\r\n");
#endif /* DEBUG */
        return 1;
    }
#ifdef DEBUG
    DEBUG_OUT("bsp_cst816t_init: CST816T driver initialization start!\r\n");
#endif /* DEBUG */

/* 2. Get the chip ID */
    ret = bsp_cst816_get_chipid(p_cst816t_instance, &chipid);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816t_init: get chipid failed!\r\n");
#endif /* DEBUG */
        return ret;
    }

/* 3. Configure basic touch parameters */
    // Set normal scan period to 10ms for better response
    ret = bsp_cst816_set_nor_scan_per(p_cst816t_instance, 10);
    if (0 != ret) 
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816t_init: set nor scan per failed!\r\n");
#endif /* DEBUG */
        return ret;
    }

    // Configure motion detection
    ret = bsp_cst816_set_motion_mask(p_cst816t_instance, 
                                    (cst816_motion_mask_t)(EN_CON_LR | EN_CON_UD | EN_DCLICK));
    if (0 != ret) 
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816t_init: set motion mask failed!\r\n");
#endif /* DEBUG */
        return ret;
    }

/* 4. Configure interrupt settings */
    // Set IRQ pulse width to 1ms
    ret = bsp_cst816_set_irq_pluse_width(p_cst816t_instance, 10);
    if (0 != ret) 
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816t_init: set irq pulse width failed!\r\n");
#endif /* DEBUG */
        return ret;
    }

    // Generate interrupt only when touch occurs and on motion
    ret = bsp_cst816_set_irq_ctl(p_cst816t_instance, (cst816_irq_ctl_t)(EN_TOUCH | EN_MOTION));
    if (0 != ret) 
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816t_init: set irq ctl failed!\r\n");
#endif /* DEBUG */
        return ret;
    }

/* 5. Configure power management */
    // Set auto sleep time to 2 seconds
    ret = bsp_cst816_set_auto_sleep_time(p_cst816t_instance, 2);
    if (0 != ret) 
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816t_init: set auto sleep time failed!\r\n");
#endif /* DEBUG */
        return ret;
    }

/* 6. Set long press time threshold */
    ret = bsp_cst816_set_long_press_th(p_cst816t_instance, 100); // 1s threshold
    if (0 != ret) 
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816t_init: set long press th failed!\r\n");
#endif /* DEBUG */
        return ret;
    }

/* 7. Final configurations */
    // Enable all necessary IO controls
    ret = bsp_cst816_set_io_ctl(p_cst816t_instance, 0x00); // Default IO control
    if (0 != ret) 
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816t_init: set io ctl failed!\r\n");
#endif /* DEBUG */
        return ret;
    }

#ifdef DEBUG
    DEBUG_OUT("bsp_cst816t_init: initialization completed successfully\r\n");
#endif /* DEBUG */

    return 0;
}

/**
 * @brief Initialize the CST816T driver instance.
 * 
 * @param p_cst816t_instance: The CST816T driver instance.
 * @param p_timebase_instance: The timebase driver instance.
 * @param p_yield_instance: The yield driver instance.
 * @param p_iic_driver_instance: The IIC driver instance.
 * @param p_gpio_opt_instance: The GPIO driver instance.
 * @param pp_int_callback: The interrupt callback function pointer.
 * 
 * @return 0: Success, other: Error code.
 */
uint8_t bsp_cst816t_inst(bsp_cst816t_driver_t   * const p_cst816t_instance,
                    cst816_timebase_interface_t   * const p_timebase_instance,
#ifdef OS_SUPPORTING
                    cst816__yield_interface_t      * const p_yield_instance,
#endif /* OS_SUPPORTING */
                    cst816__iic_driver_interface_t * const p_iic_driver_instance,
                    gpio_opt_interface_t   * const p_gpio_opt_instance,
                    void (**pp_int_callback)(void *, void *))
{
    uint8_t ret = 0;
#ifdef DEBUG
    DEBUG_OUT("bsp_cst816t_inst: instance initialization start!\r\n");
#endif /* DEBUG */

/* 1. Check if the parameters are valid */
    if (NULL == p_cst816t_instance  ||
        NULL == p_timebase_instance ||
        NULL == p_iic_driver_instance ||
        NULL == p_gpio_opt_instance )
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816t_inst: interface parameter error!\r\n");
#endif /* DEBUG */
        return 4;
    }

    if (NULL == p_timebase_instance->pf_get_tick_count     ||
        NULL == p_yield_instance->pf_rtos_yield            ||
        NULL == p_iic_driver_instance->hi2c                ||
        NULL == p_iic_driver_instance->pf_iic_deinit       ||
        NULL == p_iic_driver_instance->pf_iic_init         ||
        NULL == p_iic_driver_instance->pf_iic_mem_read     ||
        NULL == p_iic_driver_instance->pf_iic_mem_write    ||
        NULL == p_iic_driver_instance->pf_iic_mem_read_dma ||
        NULL == p_gpio_opt_instance->pf_write_reset_pin   )
        {
#ifdef DEBUG
            DEBUG_OUT("bsp_cst816t_inst: function pointer error!\r\n");
#endif /* DEBUG */
            return 3;
        }

/* 2. Resource assignment */
    p_cst816t_instance->p_timebase_interface   = p_timebase_instance;
#ifdef OS_SUPPORTING
    p_cst816t_instance->p_yield_interface      = p_yield_instance;
#endif /* OS_SUPPORTING */
    p_cst816t_instance->p_iic_driver_interface = p_iic_driver_instance;

/* 3. Function pointer assignment */
    // Initialization functions
    p_cst816t_instance->pf_cst816t_init = bsp_cst816t_init;
    p_cst816t_instance->pf_cst816t_deinit = bsp_cst816t_deinit;

    // Touch screen operation functions
    p_cst816t_instance->pf_cst816_get_gesture_id = bsp_cst816_get_gesture_id;
    p_cst816t_instance->pf_cst816_get_xy_axis = bsp_cst816_get_xy_axis;
    p_cst816t_instance->pf_cst816_get_chipid = bsp_cst816_get_chipid;
    p_cst816t_instance->pf_cst816_get_finger_num = bsp_cst816_get_finger_num;

    // Configuration functions
    p_cst816t_instance->pf_cst816_sleep = bsp_cst816_sleep;
    p_cst816t_instance->pf_cst816_wakeup = bsp_cst816_wakeup;
    p_cst816t_instance->pf_cst816_set_err_reset_ctl = \
                                    bsp_cst816_set_err_reset_ctl;
    p_cst816t_instance->pf_cst816_set_long_press_th = \
                                    bsp_cst816_set_long_press_th;
    p_cst816t_instance->pf_cst816_set_motion_mask = \
                                    bsp_cst816_set_motion_mask;
    p_cst816t_instance->pf_cst816_set_irq_pluse_width = \
                                    bsp_cst816_set_irq_pluse_width;
    p_cst816t_instance->pf_cst816_set_nor_scan_per = \
                                    bsp_cst816_set_nor_scan_per;
    p_cst816t_instance->pf_cst816_set_motion_slope_angle = \
                                    bsp_cst816_set_motion_slope_angle;
    p_cst816t_instance->pf_set_low_power_auto_wake_time = \
                                    bsp_cst816_set_low_power_auto_wake_time;
    p_cst816t_instance->pf_cst816_set_lp_scan_th = \
                                    bsp_cst816_set_lp_scan_th;
    p_cst816t_instance->pf_cst816_set_lp_scan_win = \
                                    bsp_cst816_set_lp_scan_win;
    p_cst816t_instance->pf_cst816_set_lp_scan_freq = \
                                    bsp_cst816_set_lp_scan_freq;
    p_cst816t_instance->pf_cst816_set_lp_scan_idac = \
                                    bsp_cst816_set_lp_scan_idac;
    p_cst816t_instance->pf_cst816_set_auto_sleep_time = \
                                    bsp_cst816_set_auto_sleep_time;
    p_cst816t_instance->pf_cst816_set_irq_ctl = bsp_cst816_set_irq_ctl;
    p_cst816t_instance->pf_cst816_set_auto_reset = bsp_cst816_set_auto_reset;
    p_cst816t_instance->pf_cst816_set_long_press_time = \
                                    bsp_cst816_set_long_press_time;
    p_cst816t_instance->pf_cst816_set_io_ctl = bsp_cst816_set_io_ctl;
    p_cst816t_instance->pf_cst816_disable_auto_sleep = \
                                    bsp_cst816_disable_auto_sleep;

/* 4. Initialize the CST816T driver */
    ret = bsp_cst816t_init(p_cst816t_instance);
    if (0 != ret)
    {
#ifdef DEBUG
        DEBUG_OUT("bsp_cst816t_inst: CST816T driver init failed!\r\n");
#endif /* DEBUG */
        return ret;
    }

/* 5. Register the interrupt callback */
    if (pp_int_callback != NULL) {
        *pp_int_callback = cst816t_int_interrupt_callback;
    }

/* 6. Set the CST816T_INITIALIZED flag */
    g_cst816t_is_init = CST816T_INITIALIZED;

#ifdef DEBUG
    DEBUG_OUT("bsp_cst816t_inst: instance initialization completed!\r\n");
#endif /* DEBUG */
    return 0;
}

