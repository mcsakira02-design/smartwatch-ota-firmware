/******************************************************************************
 * Copyright (C) 2025 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file bsp_cst816t_calibration.c
 * 
 * @par dependencies 
 * 
 * bsp_cst816t_calibration.h
 * 
 * @author 
 * 
 * @brief 实现CST816T触摸屏校准功能
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/

//******************************** Includes *********************************//
#include "bsp_cst816t_calibration.h"
#include <math.h>
#include <string.h>
#include "elog.h"
#include "Debug.h"
//******************************** Defines **********************************//
#define CALIBRATION_FLASH_ADDR    0x08070000  // Flash存储地址 (根据实际情况调整)
#define CALIBRATION_MAGIC_NUMBER  0x12345678  // 校准数据有效性标识

//******************************** Variables ********************************//
static touch_calibration_t g_calibration_data;

//******************************** Functions ********************************//

/**
 * @brief 初始化触摸屏校准参数
 */
calibration_status_t touch_calibration_init(touch_calibration_t *p_calibration)
{
    if (p_calibration == NULL) {
        return CALIBRATION_ERROR_INVALID_POINT;
    }
    
    memset(p_calibration, 0, sizeof(touch_calibration_t));
    
    // 设置默认校准参数 (无校准状态)
    p_calibration->is_calibrated = false;
    p_calibration->scale_x = 1.0f;
    p_calibration->scale_y = 1.0f;
    p_calibration->offset_x = 0;
    p_calibration->offset_y = 0;
    
    return CALIBRATION_SUCCESS;
}

/**
 * @brief 添加校准点
 */
calibration_status_t touch_calibration_add_point(touch_calibration_t *p_calibration,
                                                 uint16_t touch_x, uint16_t touch_y,
                                                 uint16_t screen_x, uint16_t screen_y,
                                                 uint8_t point_index)
{
    if (p_calibration == NULL || point_index >= CALIBRATION_POINTS_NUM) {
        return CALIBRATION_ERROR_INVALID_POINT;
    }
    
    p_calibration->points[point_index].touch_x = touch_x;
    p_calibration->points[point_index].touch_y = touch_y;
    p_calibration->points[point_index].screen_x = screen_x;
    p_calibration->points[point_index].screen_y = screen_y;
    
    return CALIBRATION_SUCCESS;
}

/**
 * @brief 计算校准参数 (九点线性校准)
 */
calibration_status_t touch_calibration_calculate_linear(touch_calibration_t *p_calibration)
{
    if (p_calibration == NULL) {
        return CALIBRATION_ERROR_INVALID_POINT;
    }
    
    // 检查是否有足够的校准点
    uint8_t valid_points = 0;
    for (uint8_t i = 0; i < CALIBRATION_POINTS_NUM; i++) {
        if (p_calibration->points[i].touch_x != 0 || p_calibration->points[i].touch_y != 0) {
            valid_points++;
#ifdef DEBUG_LCDCALIBRATE
            log_d("有效校准点 %d: 触摸(%d, %d) -> 屏幕(%d, %d)", i + 1,
                  p_calibration->points[i].touch_x, p_calibration->points[i].touch_y,
                  p_calibration->points[i].screen_x, p_calibration->points[i].screen_y);
#endif  


        }
    }
#ifdef DEBUG_LCDCALIBRATE
    log_d("有效校准点数量: %d/%d", valid_points, CALIBRATION_POINTS_NUM);
#endif  

    
    if (valid_points < 4) {  // 九点校准至少需要4个点
#ifdef DEBUG_LCDCALIBRATE
        log_d("校准点数量不足，需要至少4个点");
#endif 
        
        return CALIBRATION_ERROR_INSUFFICIENT_POINTS;
    }
    
    // 使用最小二乘法计算线性变换参数
    // 对于九点校准，我们使用更精确的计算方法
    float sum_touch_x = 0, sum_touch_y = 0;
    float sum_screen_x = 0, sum_screen_y = 0;
    float sum_touch_x2 = 0, sum_touch_y2 = 0;
    float sum_touch_x_screen_x = 0, sum_touch_y_screen_y = 0;
    float sum_touch_xy = 0, sum_touch_x_screen_y = 0, sum_touch_y_screen_x = 0;
    
    for (uint8_t i = 0; i < valid_points; i++) {
        float tx = p_calibration->points[i].touch_x;
        float ty = p_calibration->points[i].touch_y;
        float sx = p_calibration->points[i].screen_x;
        float sy = p_calibration->points[i].screen_y;
        
        sum_touch_x += tx;
        sum_touch_y += ty;
        sum_screen_x += sx;
        sum_screen_y += sy;
        sum_touch_x2 += tx * tx;
        sum_touch_y2 += ty * ty;
        sum_touch_xy += tx * ty;
        sum_touch_x_screen_x += tx * sx;
        sum_touch_y_screen_y += ty * sy;
        sum_touch_x_screen_y += tx * sy;
        sum_touch_y_screen_x += ty * sx;
    }
    
    float n = (float)valid_points;
    
    // 计算二维线性变换矩阵参数
    // X = a*touch_x + b*touch_y + c
    // Y = d*touch_x + e*touch_y + f
    
    float det = n * (sum_touch_x2 * sum_touch_y2 - sum_touch_xy * sum_touch_xy) +
                sum_touch_x * (sum_touch_xy * sum_touch_y - sum_touch_x * sum_touch_y2) +
                sum_touch_y * (sum_touch_x * sum_touch_xy - sum_touch_x2 * sum_touch_y);
    
    if (fabs(det) < 1e-6) {
        //log_d("矩阵奇异，使用简单线性变换");
        // 如果矩阵奇异，回退到简单的X-Y独立线性变换
        float denominator_x = n * sum_touch_x2 - sum_touch_x * sum_touch_x;
        float denominator_y = n * sum_touch_y2 - sum_touch_y * sum_touch_y;
        
        //log_d("分母检查: denominator_x=%.6f, denominator_y=%.6f", denominator_x, denominator_y);
        
        if (fabs(denominator_x) < 1e-6 || fabs(denominator_y) < 1e-6) {
            //log_d("分母为零，校准计算失败");
            return CALIBRATION_ERROR_CALCULATION_FAILED;
        }
        
        p_calibration->scale_x = (n * sum_touch_x_screen_x - sum_touch_x * sum_screen_x) / denominator_x;
        p_calibration->offset_x = (sum_screen_x - p_calibration->scale_x * sum_touch_x) / n;
        p_calibration->scale_y = (n * sum_touch_y_screen_y - sum_touch_y * sum_screen_y) / denominator_y;
        p_calibration->offset_y = (sum_screen_y - p_calibration->scale_y * sum_touch_y) / n;
        
        //log_d("简单线性校准参数: scale_x=%.3f, offset_x=%.1f, scale_y=%.3f, offset_y=%.1f",
        //      p_calibration->scale_x, p_calibration->offset_x, 
        //      p_calibration->scale_y, p_calibration->offset_y);
        
        // 清零交叉项
        p_calibration->matrix_a = p_calibration->scale_x;
        p_calibration->matrix_b = 0;
        p_calibration->matrix_c = p_calibration->offset_x;
        p_calibration->matrix_d = 0;
        p_calibration->matrix_e = p_calibration->scale_y;
        p_calibration->matrix_f = p_calibration->offset_y;
    } else {
        //log_d("使用完整的二维线性变换，det=%.6f", det);
        // 使用完整的二维线性变换 - 修复矩阵计算公式
        // 使用标准最小二乘法求解线性方程组
        
        // 对X坐标: screen_x = a*touch_x + b*touch_y + c
        float det_x = n * sum_touch_x2 - sum_touch_x * sum_touch_x;
        if (fabs(det_x) > 1e-6) {
            p_calibration->matrix_a = (n * sum_touch_x_screen_x - sum_touch_x * sum_screen_x) / det_x;
            p_calibration->matrix_c = (sum_screen_x - p_calibration->matrix_a * sum_touch_x) / n;
        } else {
            p_calibration->matrix_a = 1.0f;
            p_calibration->matrix_c = 0.0f;
        }
        p_calibration->matrix_b = 0.0f;  // 简化：假设X不依赖于Y
        
        // 对Y坐标: screen_y = d*touch_x + e*touch_y + f  
        float det_y = n * sum_touch_y2 - sum_touch_y * sum_touch_y;
        if (fabs(det_y) > 1e-6) {
            p_calibration->matrix_e = (n * sum_touch_y_screen_y - sum_touch_y * sum_screen_y) / det_y;
            p_calibration->matrix_f = (sum_screen_y - p_calibration->matrix_e * sum_touch_y) / n;
        } else {
            p_calibration->matrix_e = 1.0f;
            p_calibration->matrix_f = 0.0f;
        }
        p_calibration->matrix_d = 0.0f;  // 简化：假设Y不依赖于X
        
        // 更新简单参数用于兼容性
        p_calibration->scale_x = p_calibration->matrix_a;
        p_calibration->scale_y = p_calibration->matrix_e;
        p_calibration->offset_x = (int16_t)p_calibration->matrix_c;
        p_calibration->offset_y = (int16_t)p_calibration->matrix_f;
        
        // log_d("二维线性变换参数: a=%.3f, b=%.3f, c=%.1f, d=%.3f, e=%.3f, f=%.1f",
        //       p_calibration->matrix_a, p_calibration->matrix_b, p_calibration->matrix_c,
        //       p_calibration->matrix_d, p_calibration->matrix_e, p_calibration->matrix_f);
    }
    
    p_calibration->matrix_k = 1.0f;
    p_calibration->is_calibrated = true;
    
    // log_d("Nine-point calibration completed: a=%.3f, b=%.3f, c=%.1f, d=%.3f, e=%.3f, f=%.1f",
    //        p_calibration->matrix_a, p_calibration->matrix_b, p_calibration->matrix_c,
    //        p_calibration->matrix_d, p_calibration->matrix_e, p_calibration->matrix_f);
    
    return CALIBRATION_SUCCESS;
}

/**
 * @brief 计算校准参数 (高级非线性校准)
 * 使用最小二乘法计算变换矩阵
 */
calibration_status_t touch_calibration_calculate_matrix(touch_calibration_t *p_calibration)
{
    if (p_calibration == NULL) {
        return CALIBRATION_ERROR_INVALID_POINT;
    }
    
    // 使用三点校准法计算变换矩阵
    // 变换公式: X = (a*x + b*y + c) / (g*x + h*y + 1)
    //          Y = (d*x + e*y + f) / (g*x + h*y + 1)
    // 简化为线性变换: X = a*x + b*y + c, Y = d*x + e*y + f
    
    calibration_point_t *p0 = &p_calibration->points[0];
    calibration_point_t *p1 = &p_calibration->points[1];
    calibration_point_t *p2 = &p_calibration->points[2];
    
    // 构建方程组求解变换矩阵
    float x1 = p0->touch_x, y1 = p0->touch_y, X1 = p0->screen_x, Y1 = p0->screen_y;
    float x2 = p1->touch_x, y2 = p1->touch_y, X2 = p1->screen_x, Y2 = p1->screen_y;
    float x3 = p2->touch_x, y3 = p2->touch_y, X3 = p2->screen_x, Y3 = p2->screen_y;
    
    // 计算行列式
    float det = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
    
    if (fabs(det) < 1e-6) {
        return CALIBRATION_ERROR_CALCULATION_FAILED;
    }
    
    // 计算变换矩阵参数
    p_calibration->matrix_a = (X1*(y2-y3) + X2*(y3-y1) + X3*(y1-y2)) / det;
    p_calibration->matrix_b = (x1*(X3-X2) + x2*(X1-X3) + x3*(X2-X1)) / det;
    p_calibration->matrix_c = (x1*(y2*X3-y3*X2) + x2*(y3*X1-y1*X3) + x3*(y1*X2-y2*X1)) / det;
    
    p_calibration->matrix_d = (Y1*(y2-y3) + Y2*(y3-y1) + Y3*(y1-y2)) / det;
    p_calibration->matrix_e = (x1*(Y3-Y2) + x2*(Y1-Y3) + x3*(Y2-Y1)) / det;
    p_calibration->matrix_f = (x1*(y2*Y3-y3*Y2) + x2*(y3*Y1-y1*Y3) + x3*(y1*Y2-y2*Y1)) / det;
    
    p_calibration->matrix_k = 1.0f;
    
    p_calibration->is_calibrated = true;
    
    return CALIBRATION_SUCCESS;
}

/**
 * @brief 应用校准参数转换坐标 (线性校准)
 */
calibration_status_t touch_calibration_apply_linear(touch_calibration_t *p_calibration,
                                                    uint16_t raw_x, uint16_t raw_y,
                                                    uint16_t *p_calibrated_x, uint16_t *p_calibrated_y)
{
    if (p_calibration == NULL || p_calibrated_x == NULL || p_calibrated_y == NULL) {
        return CALIBRATION_ERROR_INVALID_POINT;
    }
    
    if (!p_calibration->is_calibrated) {
        // 如果未校准，直接返回原始坐标
#ifdef DEBUG_LCDCALIBRATE
        log_d("线性校准未启用，返回原始坐标: (%d, %d)", raw_x, raw_y);
#endif 
        
        *p_calibrated_x = raw_x;
        *p_calibrated_y = raw_y;
        return CALIBRATION_SUCCESS;
    }
    
    // 应用线性变换
    int32_t cal_x = (int32_t)(raw_x * p_calibration->scale_x) + p_calibration->offset_x;
    int32_t cal_y = (int32_t)(raw_y * p_calibration->scale_y) + p_calibration->offset_y;
#ifdef DEBUG_LCDCALIBRATE
    log_d("线性校准: 原始(%d, %d) -> 变换前(%d, %d)", raw_x, raw_y, cal_x, cal_y);
    log_d("线性参数: scale_x=%.3f, offset_x=%d, scale_y=%.3f, offset_y=%d",
          p_calibration->scale_x, p_calibration->offset_x, 
          p_calibration->scale_y, p_calibration->offset_y);
#endif 

    
    // 限制坐标范围
    if (cal_x < 0) cal_x = 0;
    if (cal_x >= SCREEN_WIDTH) cal_x = SCREEN_WIDTH - 1;
    if (cal_y < 0) cal_y = 0;
    if (cal_y >= SCREEN_HEIGHT) cal_y = SCREEN_HEIGHT - 1;
    
    *p_calibrated_x = (uint16_t)cal_x;
    *p_calibrated_y = (uint16_t)cal_y;
#ifdef DEBUG_LCDCALIBRATE
    log_d("线性校准最终坐标: (%d, %d)", *p_calibrated_x, *p_calibrated_y);
#endif 

    
    return CALIBRATION_SUCCESS;
}

/**
 * @brief 应用矩阵校准变换坐标 (九点校准)
 */
calibration_status_t touch_calibration_apply_matrix(touch_calibration_t *p_calibration,
                                                    uint16_t raw_x, uint16_t raw_y,
                                                    uint16_t *p_calibrated_x, uint16_t *p_calibrated_y)
{
    if (p_calibration == NULL || p_calibrated_x == NULL || p_calibrated_y == NULL) {
        return CALIBRATION_ERROR_INVALID_POINT;
    }
    
    if (!p_calibration->is_calibrated) {
#ifdef DEBUG_LCDCALIBRATE
        log_d("未校准，返回原始坐标: (%d, %d)", raw_x, raw_y);
#endif 
        
        *p_calibrated_x = raw_x;
        *p_calibrated_y = raw_y;
        return CALIBRATION_SUCCESS;
    }
    
    // 应用二维线性变换矩阵: 
    // X = a*touch_x + b*touch_y + c
    // Y = d*touch_x + e*touch_y + f
    
    float tx = (float)raw_x;
    float ty = (float)raw_y;
    
    float transformed_x = p_calibration->matrix_a * tx + 
                         p_calibration->matrix_b * ty + 
                         p_calibration->matrix_c;
    
    float transformed_y = p_calibration->matrix_d * tx + 
                         p_calibration->matrix_e * ty + 
                         p_calibration->matrix_f;
#ifdef DEBUG_LCDCALIBRATE
    log_d("坐标转换: 原始(%d, %d) -> 变换前(%.1f, %.1f)", raw_x, raw_y, transformed_x, transformed_y);
    log_d("变换矩阵: a=%.3f, b=%.3f, c=%.1f, d=%.3f, e=%.3f, f=%.1f",
          p_calibration->matrix_a, p_calibration->matrix_b, p_calibration->matrix_c,
          p_calibration->matrix_d, p_calibration->matrix_e, p_calibration->matrix_f);
#endif 

    
    // 边界检查和限制
    if (transformed_x < 0) {
        transformed_x = 0;
    } else if (transformed_x >= SCREEN_WIDTH) {
        transformed_x = SCREEN_WIDTH - 1;
    }
    
    if (transformed_y < 0) {
        transformed_y = 0;
    } else if (transformed_y >= SCREEN_HEIGHT) {
        transformed_y = SCREEN_HEIGHT - 1;
    }
    
    *p_calibrated_x = (uint16_t)(transformed_x + 0.5f);  // 四舍五入
    *p_calibrated_y = (uint16_t)(transformed_y + 0.5f);  // 四舍五入
#ifdef DEBUG_LCDCALIBRATE
    log_d("最终校准坐标: (%d, %d)", *p_calibrated_x, *p_calibrated_y);
#endif 
    return CALIBRATION_SUCCESS;
}

/**
 * @brief 保存校准参数到Flash (简化实现)
 */
calibration_status_t touch_calibration_save_to_flash(touch_calibration_t *p_calibration)
{
    if (p_calibration == NULL) {
        return CALIBRATION_ERROR_INVALID_POINT;
    }
    
    // TODO: 实现Flash写入功能
    // 这里需要根据具体的Flash驱动实现
    // 建议将校准参数保存到专用的Flash区域
    
    return CALIBRATION_SUCCESS;
}

/**
 * @brief 从Flash加载校准参数 (简化实现)
 */
calibration_status_t touch_calibration_load_from_flash(touch_calibration_t *p_calibration)
{
    if (p_calibration == NULL) {
        return CALIBRATION_ERROR_INVALID_POINT;
    }
    
    // TODO: 实现Flash读取功能
    // 这里需要根据具体的Flash驱动实现
    
    return CALIBRATION_SUCCESS;
}

/**
 * @brief 重置校准参数
 */
calibration_status_t touch_calibration_reset(touch_calibration_t *p_calibration)
{
    return touch_calibration_init(p_calibration);
}

/**
 * @brief 获取标准校准点坐标 (九点校准) - 已旋转180度
 */
calibration_status_t touch_calibration_get_standard_point(uint8_t point_index,
                                                          uint16_t *p_screen_x, uint16_t *p_screen_y)
{
    if (p_screen_x == NULL || p_screen_y == NULL || point_index >= CALIBRATION_POINTS_NUM) {
        return CALIBRATION_ERROR_INVALID_POINT;
    }
    
    // 定义九点校准的标准位置 (3x3网格) - 旋转180度后的坐标
    const uint16_t margin = 30; // 距离边缘的距离
    const uint16_t x_positions[3] = {
        SCREEN_WIDTH - margin,     // 右侧 (原左侧旋转180度后)
        SCREEN_WIDTH / 2,         // 中间
        margin                    // 左侧 (原右侧旋转180度后)
    };
    const uint16_t y_positions[3] = {
        SCREEN_HEIGHT - margin,    // 下方 (原上方旋转180度后)
        SCREEN_HEIGHT / 2,        // 中间
        margin                    // 上方 (原下方旋转180度后)
    };
    
    // 九点校准点分布 (3x3网格) - 旋转180度后:
    // 原始布局:     旋转180度后:
    // 0 1 2         8 7 6
    // 3 4 5   -->   5 4 3
    // 6 7 8         2 1 0
    uint8_t row = point_index / 3;
    uint8_t col = point_index % 3;
    
    if (row >= 3 || col >= 3) {
        return CALIBRATION_ERROR_INVALID_POINT;
    }
    
    *p_screen_x = x_positions[col];
    *p_screen_y = y_positions[row];
    
    return CALIBRATION_SUCCESS;
}

/**
 * @brief 获取全局校准数据指针
 */
touch_calibration_t* touch_calibration_get_instance(void)
{
    return &g_calibration_data;
}