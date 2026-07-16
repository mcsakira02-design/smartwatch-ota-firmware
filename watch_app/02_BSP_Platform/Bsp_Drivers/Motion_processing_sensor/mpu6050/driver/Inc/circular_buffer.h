/******************************************************************************
 *  
 *
 * All Rights Reserved.
 *
 * @file circular_buffer.h
 *
 * @par dependencies
 *
 * - stdint.h
 *
 * @author ssj
 *
 * @brief Provide the circular buffer APIs.
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
#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__
//******************************** Includes *********************************//
#include <stdint.h>

typedef struct circular_buffer
{
    uint8_t *buffer; // 缓冲区
    uint8_t rflag;   // 读位置
    uint8_t wflag;   // 写位置
    uint8_t *(*pfget_wbuffer_addr)(struct circular_buffer *); // 获取写缓冲区地址
    uint8_t *(*pfget_rbuffer_addr)(struct circular_buffer *); // 获取读缓冲区地址
    void (*pfdata_writed)(struct circular_buffer *);          // 写数据
    void (*pfdata_readed)(struct circular_buffer *);          // 读数据
    uint8_t size;    // 缓冲区大小
} circular_buffer_t;

void buffer_init(circular_buffer_t *buffer, uint8_t size);

#endif /* __CIRCULAR_BUFFER_H__ */
