/******************************************************************************
 * Copyright (C) 2025 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file bsp_cst816t_calibration.h
 * 
 * @par dependencies 
 * 
 * @author 
 * 
 * @brief 提供CST816T触摸屏校准功能，解决非线性畸变和安装偏移问题
 * 
 * Processing flow:
 * 
 * 1. 定义校准参数结构
 * 2. 提供校准算法接口
 * 3. 支持多点校准和线性插值
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
#ifndef __BSP_CST816T_CALIBRATION_H
#define __BSP_CST816T_CALIBRATION_H

#include "stdint.h"
#include "stdbool.h"
#include "bsp_cst816t_driver.h"

//******************************** Defines **********************************//
#define CALIBRATION_POINTS_NUM    9    // 校准点数量：九点校准（3x3网格）
#define SCREEN_WIDTH             240   // 屏幕宽度
#define SCREEN_HEIGHT            320   // 屏幕高度

//******************************** Typedefs *********************************//

/* 校准点结构 */
typedef struct {
    uint16_t touch_x;    // 触摸原始坐标X
    uint16_t touch_y;    // 触摸原始坐标Y
    uint16_t screen_x;   // 屏幕目标坐标X
    uint16_t screen_y;   // 屏幕目标坐标Y
} calibration_point_t;

/* 校准参数结构 */
typedef struct {
    bool is_calibrated;                                    // 是否已校准
    calibration_point_t points[CALIBRATION_POINTS_NUM];   // 校准点数组
    
    // 线性变换矩阵参数 (用于简单线性校准)
    float scale_x;       // X轴缩放系数
    float scale_y;       // Y轴缩放系数
    int16_t offset_x;    // X轴偏移量
    int16_t offset_y;    // Y轴偏移量
    
    // 高级校准参数 (用于非线性校准)
    float matrix_a;      // 变换矩阵参数A
    float matrix_b;      // 变换矩阵参数B
    float matrix_c;      // 变换矩阵参数C
    float matrix_d;      // 变换矩阵参数D
    float matrix_e;      // 变换矩阵参数E
    float matrix_f;      // 变换矩阵参数F
    float matrix_k;      // 变换矩阵参数K
} touch_calibration_t;

/* 校准状态枚举 */
typedef enum {
    CALIBRATION_SUCCESS = 0,
    CALIBRATION_ERROR_INVALID_POINT,
    CALIBRATION_ERROR_INSUFFICIENT_POINTS,
    CALIBRATION_ERROR_CALCULATION_FAILED
} calibration_status_t;

//******************************** Functions ********************************//

/**
 * @brief 初始化触摸屏校准参数
 * 
 * @param p_calibration 校准参数结构指针
 * @return calibration_status_t 校准状态
 */
calibration_status_t touch_calibration_init(touch_calibration_t *p_calibration);

/**
 * @brief 添加校准点
 * 
 * @param p_calibration 校准参数结构指针
 * @param touch_x 触摸原始坐标X
 * @param touch_y 触摸原始坐标Y
 * @param screen_x 屏幕目标坐标X
 * @param screen_y 屏幕目标坐标Y
 * @param point_index 校准点索引 (0-8)
 * @return calibration_status_t 校准状态
 */
calibration_status_t touch_calibration_add_point(touch_calibration_t *p_calibration,
                                                 uint16_t touch_x, uint16_t touch_y,
                                                 uint16_t screen_x, uint16_t screen_y,
                                                 uint8_t point_index);

/**
 * @brief 计算校准参数 (简单线性校准)
 * 
 * @param p_calibration 校准参数结构指针
 * @return calibration_status_t 校准状态
 */
calibration_status_t touch_calibration_calculate_linear(touch_calibration_t *p_calibration);

/**
 * @brief 计算校准参数 (高级非线性校准)
 * 
 * @param p_calibration 校准参数结构指针
 * @return calibration_status_t 校准状态
 */
calibration_status_t touch_calibration_calculate_matrix(touch_calibration_t *p_calibration);

/**
 * @brief 应用校准参数转换坐标 (线性校准)
 * 
 * @param p_calibration 校准参数结构指针
 * @param raw_x 原始触摸坐标X
 * @param raw_y 原始触摸坐标Y
 * @param p_calibrated_x 校准后坐标X指针
 * @param p_calibrated_y 校准后坐标Y指针
 * @return calibration_status_t 校准状态
 */
calibration_status_t touch_calibration_apply_linear(touch_calibration_t *p_calibration,
                                                    uint16_t raw_x, uint16_t raw_y,
                                                    uint16_t *p_calibrated_x, uint16_t *p_calibrated_y);

/**
 * @brief 应用校准参数转换坐标 (矩阵校准)
 * 
 * @param p_calibration 校准参数结构指针
 * @param raw_x 原始触摸坐标X
 * @param raw_y 原始触摸坐标Y
 * @param p_calibrated_x 校准后坐标X指针
 * @param p_calibrated_y 校准后坐标Y指针
 * @return calibration_status_t 校准状态
 */
calibration_status_t touch_calibration_apply_matrix(touch_calibration_t *p_calibration,
                                                    uint16_t raw_x, uint16_t raw_y,
                                                    uint16_t *p_calibrated_x, uint16_t *p_calibrated_y);

/**
 * @brief 保存校准参数到Flash
 * 
 * @param p_calibration 校准参数结构指针
 * @return calibration_status_t 校准状态
 */
calibration_status_t touch_calibration_save_to_flash(touch_calibration_t *p_calibration);

/**
 * @brief 从Flash加载校准参数
 * 
 * @param p_calibration 校准参数结构指针
 * @return calibration_status_t 校准状态
 */
calibration_status_t touch_calibration_load_from_flash(touch_calibration_t *p_calibration);

/**
 * @brief 重置校准参数
 * 
 * @param p_calibration 校准参数结构指针
 * @return calibration_status_t 校准状态
 */
calibration_status_t touch_calibration_reset(touch_calibration_t *p_calibration);

/**
 * @brief 获取标准校准点坐标 (用于校准界面显示)
 * 
 * @param point_index 校准点索引 (0-8)
 * @param p_screen_x 屏幕坐标X指针
 * @param p_screen_y 屏幕坐标Y指针
 * @return calibration_status_t 校准状态
 */
calibration_status_t touch_calibration_get_standard_point(uint8_t point_index,
                                                          uint16_t *p_screen_x, uint16_t *p_screen_y);

/**
 * @brief 获取全局校准数据实例
 * 
 * @return touch_calibration_t* 校准数据指针
 */
touch_calibration_t* touch_calibration_get_instance(void);

#endif /* __BSP_CST816T_CALIBRATION_H */