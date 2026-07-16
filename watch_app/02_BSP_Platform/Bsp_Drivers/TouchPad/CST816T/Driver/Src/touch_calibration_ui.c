//******************************** Includes *********************************//
#include "touch_calibration_ui.h"
#include "bsp_cst816t_calibration.h"
#include "lvgl.h"
#include "elog.h"

//******************************** Defines **********************************//
#define CALIBRATION_POINT_SIZE 20
#define CALIBRATION_CROSS_SIZE 10
#define CALIBRATION_TIMEOUT_MS 30000  // 30秒超时

//******************************** Types ************************************//
typedef enum {
    CALIBRATION_UI_STATE_INIT,
    CALIBRATION_UI_STATE_SHOW_POINT,
    CALIBRATION_UI_STATE_WAIT_TOUCH,
    CALIBRATION_UI_STATE_CALCULATING,
    CALIBRATION_UI_STATE_COMPLETE,
    CALIBRATION_UI_STATE_ERROR
} calibration_ui_state_t;

typedef struct {
    lv_obj_t *screen;
    lv_obj_t *label_title;
    lv_obj_t *label_instruction;
    lv_obj_t *point_cross;
    lv_obj_t *btn_skip;
    lv_obj_t *btn_restart;
    
    calibration_ui_state_t state;
    uint8_t current_point_index;
    uint32_t touch_start_time;
    bool touch_detected;
    
    touch_calibration_t *p_calibration;
    uint16_t standard_points[9][2];
} calibration_ui_t;

//******************************** Variables ********************************//
static calibration_ui_t g_calibration_ui = {0};

// 九点校准标准坐标 (3x3网格) - 已旋转180度适配屏幕显示
static const uint16_t default_calibration_points[9][2] = {
    {200, 280},    // 点0: 右下角 (原左上角旋转180度后)
    {120, 280},    // 点1: 下中 (原上中旋转180度后)
    {40, 280},     // 点2: 左下角 (原右上角旋转180度后)
    {200, 160},    // 点3: 右中 (原左中旋转180度后)     
    {120, 160},    // 点4: 中心点 (保持不变)
    {40, 160},     // 点5: 左中 (原右中旋转180度后)
    {200, 40},     // 点6: 右上角 (原左下角旋转180度后)
    {120, 40},     // 点7: 上中 (原下中旋转180度后)
    {40, 40}       // 点8: 左上角 (原右下角旋转180度后)
};

//******************************** Function Prototypes *********************//
static void calibration_ui_create_screen(void);
static void calibration_ui_show_point(uint8_t point_index);
static void calibration_ui_update_instruction(const char *text);
static void calibration_ui_handle_touch(lv_event_t *e);
static void calibration_ui_btn_skip_event(lv_event_t *e);
static void calibration_ui_btn_restart_event(lv_event_t *e);
static void calibration_ui_complete(void);
static void calibration_ui_error(const char *error_msg);
static void calibration_ui_timer_callback(lv_timer_t *timer);

//******************************** Functions ********************************//

/**
 * @brief 初始化触摸屏校准界面
 * @return 校准状态
 */
calibration_status_t touch_calibration_ui_init(void)
{
    // 获取校准实例
    g_calibration_ui.p_calibration = touch_calibration_get_instance();
    if (g_calibration_ui.p_calibration == NULL) {
        return CALIBRATION_ERROR_INVALID_POINT;
    }
    
    // 初始化校准模块
    calibration_status_t status = touch_calibration_init(g_calibration_ui.p_calibration);
    if (status != CALIBRATION_SUCCESS) {
        return status;
    }
    
    // 复制标准校准点并验证坐标
    log_d("Start initializing %d calibration points:", CALIBRATION_POINTS_NUM);
    for (int i = 0; i < CALIBRATION_POINTS_NUM; i++) {
        g_calibration_ui.standard_points[i][0] = default_calibration_points[i][0];
        g_calibration_ui.standard_points[i][1] = default_calibration_points[i][1];
        log_d("Calibration point %d: (%d, %d)", i + 1, 
              g_calibration_ui.standard_points[i][0], 
              g_calibration_ui.standard_points[i][1]);
        
        // 检查坐标是否在屏幕范围内
        if (g_calibration_ui.standard_points[i][0] >= SCREEN_WIDTH || 
            g_calibration_ui.standard_points[i][1] >= SCREEN_HEIGHT) {
            log_d("Warning: The coordinates of calibration point %d exceed the screen range", i + 1);
        }
    }
    log_d("The calibration points have been initialized. There are a total of %d points.", CALIBRATION_POINTS_NUM);
    
    // 重置校准参数
    touch_calibration_reset(g_calibration_ui.p_calibration);
    
    // 创建校准界面
    calibration_ui_create_screen();
    
    // 初始化状态
    g_calibration_ui.state = CALIBRATION_UI_STATE_INIT;
    g_calibration_ui.current_point_index = 0;
    g_calibration_ui.touch_detected = false;
    
    return CALIBRATION_SUCCESS;
}

/**
 * @brief 开始触摸屏校准
 */
void touch_calibration_ui_start(void)
{
    if (g_calibration_ui.screen == NULL) {
        return;
    }
    
    // 加载校准界面
    lv_scr_load(g_calibration_ui.screen);
    
    // 显示第一个校准点
    g_calibration_ui.state = CALIBRATION_UI_STATE_SHOW_POINT;
    g_calibration_ui.current_point_index = 0;
    calibration_ui_show_point(0);
    
    // 启动定时器检查超时
    lv_timer_t *timer = lv_timer_create(calibration_ui_timer_callback, 1000, NULL);
    lv_timer_set_repeat_count(timer, CALIBRATION_TIMEOUT_MS / 1000);
}

/**
 * @brief 创建校准界面
 */
static void calibration_ui_create_screen(void)
{
    // 创建屏幕
    g_calibration_ui.screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(g_calibration_ui.screen, lv_color_black(), 0);
    
    // 创建标题标签
    g_calibration_ui.label_title = lv_label_create(g_calibration_ui.screen);
    lv_label_set_text(g_calibration_ui.label_title, "Nine - point touch screen calibration");
    lv_obj_set_style_text_color(g_calibration_ui.label_title, lv_color_white(), 0);
    // lv_obj_set_style_text_font(g_calibration_ui.label_title, &lv_font_montserrat_16, 0);
    lv_obj_align(g_calibration_ui.label_title, LV_ALIGN_TOP_MID, 0, 20);
    
    // 创建指令标签
    g_calibration_ui.label_instruction = lv_label_create(g_calibration_ui.screen);
    lv_label_set_text(g_calibration_ui.label_instruction, "Please accurately touch the center point of the cross.\nNine - point calibration provides higher accuracy.");
    lv_obj_set_style_text_color(g_calibration_ui.label_instruction, lv_color_white(), 0);
    // lv_obj_set_style_text_font(g_calibration_ui.label_instruction, &lv_font_montserrat_12, 0);
    lv_obj_align(g_calibration_ui.label_instruction, LV_ALIGN_TOP_MID, 0, 50);
    lv_obj_set_style_text_align(g_calibration_ui.label_instruction, LV_TEXT_ALIGN_CENTER, 0);
    
    // 创建校准点十字
    g_calibration_ui.point_cross = lv_obj_create(g_calibration_ui.screen);
    lv_obj_set_size(g_calibration_ui.point_cross, CALIBRATION_POINT_SIZE, CALIBRATION_POINT_SIZE);
    lv_obj_set_style_bg_color(g_calibration_ui.point_cross, lv_color_white(), 0);
    lv_obj_set_style_border_width(g_calibration_ui.point_cross, 2, 0);
    lv_obj_set_style_border_color(g_calibration_ui.point_cross, lv_color_make(255, 0, 0), 0);
    lv_obj_set_style_radius(g_calibration_ui.point_cross, 0, 0);
    
    // 添加触摸事件
    lv_obj_add_event_cb(g_calibration_ui.screen, calibration_ui_handle_touch, LV_EVENT_PRESSED, NULL);
    
    // 创建跳过按钮（初始隐藏）
    g_calibration_ui.btn_skip = lv_btn_create(g_calibration_ui.screen);
    lv_obj_set_size(g_calibration_ui.btn_skip, 80, 30);
    lv_obj_align(g_calibration_ui.btn_skip, LV_ALIGN_BOTTOM_LEFT, 20, -20);
    lv_obj_t *label_skip = lv_label_create(g_calibration_ui.btn_skip);
    lv_label_set_text(label_skip, "jump");
    lv_obj_center(label_skip);
    lv_obj_add_event_cb(g_calibration_ui.btn_skip, calibration_ui_btn_skip_event, LV_EVENT_CLICKED, NULL);
    lv_obj_add_flag(g_calibration_ui.btn_skip, LV_OBJ_FLAG_HIDDEN);  // 初始隐藏
    
    // 创建重新开始按钮（初始隐藏）
    g_calibration_ui.btn_restart = lv_btn_create(g_calibration_ui.screen);
    lv_obj_set_size(g_calibration_ui.btn_restart, 80, 30);
    lv_obj_align(g_calibration_ui.btn_restart, LV_ALIGN_BOTTOM_RIGHT, -20, -20);
    lv_obj_t *label_restart = lv_label_create(g_calibration_ui.btn_restart);
    lv_label_set_text(label_restart, "start over");
    lv_obj_center(label_restart);
    lv_obj_add_event_cb(g_calibration_ui.btn_restart, calibration_ui_btn_restart_event, LV_EVENT_CLICKED, NULL);
    lv_obj_add_flag(g_calibration_ui.btn_restart, LV_OBJ_FLAG_HIDDEN);  // 初始隐藏
}

/**
 * @brief 显示校准点
 * @param point_index 校准点索引
 */
static void calibration_ui_show_point(uint8_t point_index)
{
    if (point_index >= CALIBRATION_POINTS_NUM) {
        log_d("The calibration point index is out of range: %d", point_index);
        return;
    }
    
    // 更新指令文本
    char instruction[64];
    snprintf(instruction, sizeof(instruction), "Please touch the %dth calibration point (%d/%d)", 
             point_index + 1, point_index + 1, CALIBRATION_POINTS_NUM);
    calibration_ui_update_instruction(instruction);
    
    log_d("Display calibration point %d: (%d, %d)", point_index + 1, 
          g_calibration_ui.standard_points[point_index][0],
          g_calibration_ui.standard_points[point_index][1]);
    
    // 移动校准点到指定位置
    uint16_t point_x = g_calibration_ui.standard_points[point_index][0];
    uint16_t point_y = g_calibration_ui.standard_points[point_index][1];
    lv_obj_set_pos(g_calibration_ui.point_cross, 
                   point_x - CALIBRATION_POINT_SIZE/2, 
                   point_y - CALIBRATION_POINT_SIZE/2);
    
    // 显示校准点
    lv_obj_clear_flag(g_calibration_ui.point_cross, LV_OBJ_FLAG_HIDDEN);
    
    // 更新状态
    g_calibration_ui.state = CALIBRATION_UI_STATE_WAIT_TOUCH;
    g_calibration_ui.touch_start_time = lv_tick_get();
    g_calibration_ui.touch_detected = false;
}

/**
 * @brief 更新指令文本
 * @param text 指令文本
 */
static void calibration_ui_update_instruction(const char *text)
{
    lv_label_set_text(g_calibration_ui.label_instruction, text);
}

/**
 * @brief 处理触摸事件
 * @param e 事件对象
 */
static void calibration_ui_handle_touch(lv_event_t *e)
{
    if (g_calibration_ui.state != CALIBRATION_UI_STATE_WAIT_TOUCH) {
        return;
    }
    
    // 获取触摸坐标
    lv_indev_t *indev = lv_indev_get_act();
    lv_point_t point;
    lv_indev_get_point(indev, &point);
    
    // 添加校准点
    uint16_t standard_x = g_calibration_ui.standard_points[g_calibration_ui.current_point_index][0];
    uint16_t standard_y = g_calibration_ui.standard_points[g_calibration_ui.current_point_index][1];
    calibration_status_t status = touch_calibration_add_point(
        g_calibration_ui.p_calibration,
        point.x, point.y,
        standard_x, standard_y,
        g_calibration_ui.current_point_index
    );
    
    if (status != CALIBRATION_SUCCESS) {
        log_d("Failed to add calibration points, status: %d", status);
        calibration_ui_error("Failed to add calibration points");
        return;
    }
    
    log_d("Calibration point %d added successfully: Touch coordinates (%d, %d) -> Standard coordinates (%d, %d)", 
          g_calibration_ui.current_point_index + 1, point.x, point.y, standard_x, standard_y);
    
    // 隐藏当前校准点
    lv_obj_add_flag(g_calibration_ui.point_cross, LV_OBJ_FLAG_HIDDEN);
    
    // 检查是否完成所有校准点
    g_calibration_ui.current_point_index++;
    log_d("Current calibration progress: %d/%d", g_calibration_ui.current_point_index, CALIBRATION_POINTS_NUM);
    
    if (g_calibration_ui.current_point_index >= CALIBRATION_POINTS_NUM) {
        // 开始计算校准参数
        g_calibration_ui.state = CALIBRATION_UI_STATE_CALCULATING;
        calibration_ui_update_instruction("Calculating the nine-point calibration parameters...");
        
        // 计算校准参数
        log_d("Start calculating the nine - point calibration parameters...");
        status = touch_calibration_calculate_linear(g_calibration_ui.p_calibration);
        if (status == CALIBRATION_SUCCESS) {
            log_d("The calculation of nine - point calibration parameters was successful");
            // 保存校准参数
            touch_calibration_save_to_flash(g_calibration_ui.p_calibration);
            log_d("The calibration parameters have been saved to Flash.");
            calibration_ui_complete();
        } else {
            log_d("The calculation of nine - point calibration parameters failed. Status: %d", status);
            calibration_ui_error("The calculation of nine - point calibration parameters failed");
        }
    } else {
        // 显示下一个校准点（延迟500ms）
        calibration_ui_show_point(g_calibration_ui.current_point_index);
    }
}

/**
 * @brief 跳过按钮事件处理
 * @param e 事件对象
 */
static void calibration_ui_btn_skip_event(lv_event_t *e)
{
    log_d("The user chooses to skip calibration.");
    // 加载默认校准参数或跳过校准
    touch_calibration_load_from_flash(g_calibration_ui.p_calibration);
    calibration_ui_complete();
}

/**
 * @brief 重新开始按钮事件处理
 * @param e 事件对象
 */
static void calibration_ui_btn_restart_event(lv_event_t *e)
{
    log_d("The user chooses to restart the calibration");
    // 重置校准参数
    touch_calibration_reset(g_calibration_ui.p_calibration);
    
    // 隐藏按钮
    lv_obj_add_flag(g_calibration_ui.btn_skip, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(g_calibration_ui.btn_restart, LV_OBJ_FLAG_HIDDEN);
    
    // 重新开始校准
    g_calibration_ui.current_point_index = 0;
    calibration_ui_show_point(0);
}

/**
 * @brief 校准完成
 */
static void calibration_ui_complete(void)
{
    g_calibration_ui.state = CALIBRATION_UI_STATE_COMPLETE;
    
    // 隐藏校准点和按钮
    lv_obj_add_flag(g_calibration_ui.point_cross, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(g_calibration_ui.btn_skip, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(g_calibration_ui.btn_restart, LV_OBJ_FLAG_HIDDEN);
    
    // 显示完成信息
    calibration_ui_update_instruction("Nine-point calibration completed!\nTouch accuracy has been optimized.\nAutomatically return in 3 seconds.");
    
    // TODO: 3秒后返回主界面
    // 这里可以添加返回主界面的逻辑
}

/**
 * @brief 校准错误处理
 * @param error_msg 错误信息
 */
static void calibration_ui_error(const char *error_msg)
{
    g_calibration_ui.state = CALIBRATION_UI_STATE_ERROR;
    
    log_d("Calibration error: %s", error_msg);
    
    // 显示错误信息
    char error_text[128];
    snprintf(error_text, sizeof(error_text), "error: %s\n Please click to restart", error_msg);
    calibration_ui_update_instruction(error_text);
    
    // 隐藏校准点
    lv_obj_add_flag(g_calibration_ui.point_cross, LV_OBJ_FLAG_HIDDEN);
    
    // 显示重新开始按钮
    lv_obj_clear_flag(g_calibration_ui.btn_restart, LV_OBJ_FLAG_HIDDEN);
}

/**
 * @brief 定时器回调函数（检查超时）
 * @param timer 定时器对象
 */
static void calibration_ui_timer_callback(lv_timer_t *timer)
{
    if (g_calibration_ui.state == CALIBRATION_UI_STATE_WAIT_TOUCH) {
        uint32_t elapsed = lv_tick_get() - g_calibration_ui.touch_start_time;
        if (elapsed > CALIBRATION_TIMEOUT_MS) {
            log_d("Calibration point %d touch timeout", g_calibration_ui.current_point_index + 1);
            calibration_ui_error("touch timeout");
        }
    }
}

/**
 * @brief 清理校准界面资源
 */
void touch_calibration_ui_cleanup(void)
{
    if (g_calibration_ui.screen != NULL) {
        lv_obj_del(g_calibration_ui.screen);
        g_calibration_ui.screen = NULL;
    }
}