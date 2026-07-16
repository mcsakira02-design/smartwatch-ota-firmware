/*
 * @Author: xmprocat
 * @Date: 2025-03-20 20:26:22
 * @LastEditors: xmprocat
 * @LastEditTime: 2025-03-20 20:26:42
 * @Description: 
 */
#ifndef _LOG_H_
#define _LOH_H_
#include "SEGGER_RTT.h"

#define LOG_DEBUG 1

#if LOG_DEBUG


#define LOG_PROTO(type,color,format,...)            \
        SEGGER_RTT_printf(0,"  %s%s"format"\r\n%s", \
                          color,                    \
                          type,                     \
                          ##__VA_ARGS__,            \
                          RTT_CTRL_RESET)

/* ����*/
#define LOG_CLEAR() SEGGER_RTT_WriteString(0, "  "RTT_CTRL_CLEAR)

/* ����ɫ��־��� */
#define LOG(format,...) LOG_PROTO("","",format,##__VA_ARGS__)

/* ����ɫ��ʽ��־��� */
#define LOGD(format,...) LOG_PROTO("[DEBUG]: ", RTT_CTRL_TEXT_BRIGHT_BLUE , format, ##__VA_ARGS__)
#define LOGI(format,...) LOG_PROTO("[INFO]: ", RTT_CTRL_TEXT_BRIGHT_GREEN , format, ##__VA_ARGS__)
#define LOGW(format,...) LOG_PROTO("[WARN]: ", RTT_CTRL_TEXT_BRIGHT_YELLOW, format, ##__VA_ARGS__)
#define LOGE(format,...) LOG_PROTO("[ERROR]: ", RTT_CTRL_TEXT_BRIGHT_RED   , format, ##__VA_ARGS__)

#else
#define LOG_CLEAR()
#define LOG
#define LOGI
#define LOGW
#define LOGE

#endif

#endif // !_LOG_H_

