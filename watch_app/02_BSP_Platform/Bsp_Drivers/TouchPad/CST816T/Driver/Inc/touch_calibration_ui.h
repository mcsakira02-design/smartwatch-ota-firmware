#ifndef __TOUCH_CALIBRATION_UI_H__
#define __TOUCH_CALIBRATION_UI_H__

//******************************** Includes *********************************//
#include "bsp_cst816t_calibration.h"
#include "lvgl.h"

//******************************** Defines **********************************//

//******************************** Types ************************************//

//******************************** Function Prototypes *********************//

/**
 * @brief 初始化触摸屏校准界面
 * @return 校准状态
 * @retval CALIBRATION_SUCCESS 初始化成功
 * @retval CALIBRATION_ERROR_INVALID_PARAM 参数错误
 * @retval CALIBRATION_ERROR_NOT_INITIALIZED 模块未初始化
 */
calibration_status_t touch_calibration_ui_init(void);

/**
 * @brief 开始触摸屏校准
 * @note 此函数会加载校准界面并开始校准流程
 */
void touch_calibration_ui_start(void);

/**
 * @brief 清理校准界面资源
 * @note 在校准完成或取消后调用此函数释放资源
 */
void touch_calibration_ui_cleanup(void);

#endif /* __TOUCH_CALIBRATION_UI_H__ */