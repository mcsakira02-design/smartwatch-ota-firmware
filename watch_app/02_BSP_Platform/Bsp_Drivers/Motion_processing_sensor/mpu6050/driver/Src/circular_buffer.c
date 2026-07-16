/******************************************************************************
 *  
 *
 * All Rights Reserved.
 *
 * @file circular_buffer.c
 *
 * @par dependencies
 *
 * - circular_buffer.h
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
#include "circular_buffer.h"
#include <string.h>
#include <stdlib.h>
#include "Debug.h"
circular_buffer_t circular_buf;

uint8_t *get_wbuffer_addr(circular_buffer_t *buffer)
{
    return buffer->buffer + buffer->wflag * 14;
}

uint8_t *get_rbuffer_addr(circular_buffer_t *buffer)
{
    return buffer->buffer + buffer->rflag * 14;
}

void data_writed(circular_buffer_t *buffer)
{
    // DMA写数据结束
    // todo:buffer已满
    buffer->wflag = (buffer->wflag + 1) % buffer->size;
}

void data_readed(circular_buffer_t *buffer)
{
    // 读取数据结束
    // todo: 没有可读数据
    buffer->rflag = (buffer->rflag + 1) % buffer->size;
}

void buffer_init(circular_buffer_t *buffer, uint8_t size)
{
    if (NULL == buffer)
    {
#ifdef DEBUG_SENSOR_MPU6050_DRIVER
        DEBUG_OUT("buffer is NULL");
#endif
    }

    buffer->size = size;
    buffer->rflag = 0;
    buffer->wflag = 0;

    /*buffer 分配空间*/
    buffer->buffer = (uint8_t *)malloc(size * 14);

    buffer->pfget_rbuffer_addr = get_rbuffer_addr;
    buffer->pfget_wbuffer_addr = get_wbuffer_addr;
    buffer->pfdata_readed      = data_readed;
    buffer->pfdata_writed      = data_writed;
}
