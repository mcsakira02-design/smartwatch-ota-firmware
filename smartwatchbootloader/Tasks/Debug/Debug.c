#include "Debug.h"
#include "elog.h"
#include "stdio.h"
/**
 * @brief 初始化简化版elog日志系统
 * @note 优化内存占用，只保留基本的日志输出功能
 */
void app_elog_init(void)
{
    elog_init(); 
    
    /* 优化：关闭颜色支持以节省内存 */
    //elog_set_text_color_enabled(false);

    /* 优化：简化格式设置，只保留级别和标签 */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_LVL | ELOG_FMT_TAG);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG);
    
    /* 优化：由于配置中已限制日志级别为INFO，DEBUG和VERBOSE不会被编译 */
    
    elog_start();
}
