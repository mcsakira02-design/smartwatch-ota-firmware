//******************************** Includes *********************************//
#include "bsp_cst816t_calibration.h"
#include "bsp_cst816t_driver.h"
#include <stdio.h>
#include "elog.h"
#include "Debug.h"
//******************************** Defines **********************************//
// 校准点数量
#define CALIBRATION_POINTS_COUNT 5

// 标准校准点坐标（屏幕坐标系）- 已旋转180度
static const uint16_t standard_points[CALIBRATION_POINTS_COUNT][2] = {
    {220, 300},    // 右下角 (原左上角旋转180度后)
    {20, 300},     // 左下角 (原右上角旋转180度后)
    {20, 20},      // 左上角 (原右下角旋转180度后)
    {220, 20},     // 右上角 (原左下角旋转180度后)
    {120, 160}     // 中心点 (保持不变)
};

//******************************** Functions ********************************//

/**
 * @brief 触摸屏校准示例函数
 * @note 这个函数展示了如何进行触摸屏校准的完整流程
 */
void touch_calibration_example(void)
{
#ifdef DEBUG_LCDCALIBRATE
    log_d("开始触摸屏校准...\n");
#endif 
    // 1. 获取校准实例
    touch_calibration_t *p_calibration = touch_calibration_get_instance();
    if (p_calibration == NULL) {
#ifdef DEBUG_LCDCALIBRATE
        log_d("获取校准实例失败！\n");
#endif 

        return;
    }
    
    // 2. 初始化校准模块
    calibration_status_t status = touch_calibration_init(p_calibration);
    if (status != CALIBRATION_SUCCESS) {
#ifdef DEBUG_LCDCALIBRATE
        log_d("校准模块初始化失败！\n");
#endif 

        return;
    }
    
    // 3. 重置校准参数
    touch_calibration_reset(p_calibration);
#ifdef DEBUG_LCDCALIBRATE
    log_d("请依次触摸屏幕上显示的校准点...\n");
#endif 

    
    // 4. 收集校准点数据
    for (int i = 0; i < CALIBRATION_POINTS_COUNT; i++) {
#ifdef DEBUG_LCDCALIBRATE
        log_d("请触摸第%d个校准点: (%d, %d)\n", 
               i + 1, standard_points[i][0], standard_points[i][1]);
#endif 

        
        // 等待用户触摸（这里需要实际的触摸检测逻辑）
        // 在实际应用中，这里应该显示校准点并等待用户触摸
        
        // 模拟获取触摸坐标（实际应用中应该从触摸屏驱动获取）
        uint16_t touch_x, touch_y;
        // touch_x = get_actual_touch_x(); // 实际触摸X坐标
        // touch_y = get_actual_touch_y(); // 实际触摸Y坐标
        
        // 这里使用模拟数据进行演示
        touch_x = standard_points[i][0] + (i * 2 - 4); // 模拟偏差
        touch_y = standard_points[i][1] + (i * 3 - 6); // 模拟偏差
        
        // 添加校准点
        status = touch_calibration_add_point(p_calibration,
                                              touch_x, touch_y,
                                              standard_points[i][0], standard_points[i][1],
                                              i);
        
        if (status != CALIBRATION_SUCCESS) {
#ifdef DEBUG_LCDCALIBRATE
            log_d("添加校准点%d失败！\n", i + 1);
#endif 

            return;
        }
#ifdef DEBUG_LCDCALIBRATE
        log_d("校准点%d添加成功: 标准坐标(%d, %d) -> 触摸坐标(%d, %d)\n",
               i + 1, standard_points[i][0], standard_points[i][1], touch_x, touch_y);
#endif 

    }
#ifdef DEBUG_LCDCALIBRATE
    log_d("计算校准参数...\n");
#endif 
    // 5. 计算校准参数

    status = touch_calibration_calculate_linear(p_calibration);
    if (status != CALIBRATION_SUCCESS) {
#ifdef DEBUG_LCDCALIBRATE
        log_d("计算线性校准参数失败！\n");
#endif 
        return;
    }
#ifdef DEBUG_LCDCALIBRATE
    log_d("线性校准参数计算成功！\n");
    log_d("X轴缩放: %.6f, Y轴缩放: %.6f\n", 
           p_calibration->scale_x, p_calibration->scale_y);
    log_d("X轴偏移: %d, Y轴偏移: %d\n", 
           p_calibration->offset_x, p_calibration->offset_y);
#endif 

    
    // 6. 保存校准参数到Flash（可选）
    status = touch_calibration_save_to_flash(p_calibration);
    if (status == CALIBRATION_SUCCESS) {
#ifdef DEBUG_LCDCALIBRATE
        log_d("校准参数已保存到Flash\n");
#endif 

    } else {
#ifdef DEBUG_LCDCALIBRATE
        log_d("保存校准参数到Flash失败\n");
#endif 
    }
#ifdef DEBUG_LCDCALIBRATE
    // 7. 测试校准效果
    log_d("\n测试校准效果...\n");
#endif 
    for (int i = 0; i < CALIBRATION_POINTS_COUNT; i++) {
        uint16_t test_touch_x = standard_points[i][0] + (i * 2 - 4); // 模拟触摸坐标
        uint16_t test_touch_y = standard_points[i][1] + (i * 3 - 6);
        uint16_t calibrated_x, calibrated_y;
        
        status = touch_calibration_apply_linear(p_calibration,
                                                 test_touch_x, test_touch_y,
                                                 &calibrated_x, &calibrated_y);
        
        if (status == CALIBRATION_SUCCESS) {
#ifdef DEBUG_LCDCALIBRATE
            log_d("测试点%d: 触摸坐标(%d, %d) -> 校准后坐标(%d, %d), 标准坐标(%d, %d)\n",
                   i + 1, test_touch_x, test_touch_y, calibrated_x, calibrated_y,
                   standard_points[i][0], standard_points[i][1]);
#endif 
        }
    }
#ifdef DEBUG_LCDCALIBRATE
    log_d("触摸屏校准完成！\n");
#endif 

}

/**
 * @brief 从Flash加载校准参数的示例
 */
void touch_calibration_load_example(void)
{
#ifdef DEBUG_LCDCALIBRATE
    log_d("从Flash加载校准参数...\n");
#endif 
    // 获取校准实例
    touch_calibration_t *p_calibration = touch_calibration_get_instance();
    if (p_calibration == NULL) {
#ifdef DEBUG_LCDCALIBRATE
        log_d("获取校准实例失败！\n");
#endif
        return;
    }
    
    // 初始化校准模块
    calibration_status_t status = touch_calibration_init(p_calibration);
    if (status != CALIBRATION_SUCCESS) {
#ifdef DEBUG_LCDCALIBRATE
        log_d("校准模块初始化失败！\n");
#endif
        return;
    }
    
    // 从Flash加载校准参数
    status = touch_calibration_load_from_flash(p_calibration);
    if (status == CALIBRATION_SUCCESS) {
#ifdef DEBUG_LCDCALIBRATE
        log_d("校准参数加载成功！\n");
        log_d("X轴缩放: %.6f, Y轴缩放: %.6f\n", 
               p_calibration->scale_x, p_calibration->scale_y);
        log_d("X轴偏移: %d, Y轴偏移: %d\n", 
               p_calibration->offset_x, p_calibration->offset_y);
#endif

    } else {
#ifdef DEBUG_LCDCALIBRATE
        log_d("从Flash加载校准参数失败，使用默认参数\n");
#endif
    }
}

/**
 * @brief 获取标准校准点坐标
 * @param index 校准点索引 (0-4)
 * @param p_x 输出X坐标
 * @param p_y 输出Y坐标
 * @return 校准状态
 */
calibration_status_t get_standard_calibration_point(uint8_t index, uint16_t *p_x, uint16_t *p_y)
{
    if (index >= CALIBRATION_POINTS_COUNT || p_x == NULL || p_y == NULL) {
        return CALIBRATION_ERROR_INVALID_POINT;
    }
    
    *p_x = standard_points[index][0];
    *p_y = standard_points[index][1];
    
    return CALIBRATION_SUCCESS;
}

/**
 * @brief 获取校准点总数
 * @return 校准点数量
 */
uint8_t get_calibration_points_count(void)
{
    return CALIBRATION_POINTS_COUNT;
}