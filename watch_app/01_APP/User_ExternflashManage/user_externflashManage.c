/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file User_Init.c
 * 
 * @par dependencies 
 * - User_Init.h
 * 
 * @author ssj
 * 
 * @brief For application layer task initialization
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
#include "user_externflashManage.h"
#include "osal.h"
#include "Debug.h"
#include "externflash_manage_port.h"

//TODO:os层没有解耦事件组，这里需要引用原库调用,后续需要重新解耦
#include "cmsis_os.h"
#include "event_groups.h"

//******************************** Includes *********************************//

//******************************** Variable **********************************//
extern EventGroupHandle_t userExtFlashEveGropHandle;
extern osal_sema_handle_t userExtFlashSemaHandle;
extern osal_mutex_handle_t extern_flash_mutex_handler;

extern_flash_handler_t extern_flash_handler;

static uint32_t s_u32_TargetAddress = 0;
static uint32_t s_u32_Size = 0;

uint8_t g_au8_lvgldata[LVGL_DATA_MAX_SIZE];
//******************************** Variable **********************************//

//******************************** Function definitions ********************************//
/**
 * @brief 获取LVGLUI数据任务
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * 
 * */
ext_flash_status_t Read_LvglData(uint32_t addr, uint32_t size)
{
	ext_flash_status_t ret = Ext_Flash_OK;
	uint32_t read_addr = addr + MEMORY_LVGL_START_ADDRESS;
	/*1.判断地址是否有效*/
	if((MEMORY_LVGL_START_ADDRESS > read_addr) || (MEMORY_LVGL_END_ADDRESS < read_addr))
	{
		ret = Ext_Flash_ERRORPARAMETER;
	}
	/*2.判断读取范围是否有效*/
	else if((read_addr + size) > MEMORY_LVGL_END_ADDRESS)
	{
		ret = Ext_Flash_ERRORNOMEMORY;
	}
	/*3.获取线程互斥锁，如果有其他任务正在存储数据,则返回*/
	else if(OSAL_ERROR == osal_mutex_take(extern_flash_mutex_handler,0))
	{
		ret = Ext_Flash_ERROR;
	}
	/*4.可以执行读取数据命令*/
	else
	{
		s_u32_TargetAddress = read_addr;
		s_u32_Size = size;
		/*5.触发任务采集，使能事件组*/
		xEventGroupSetBits(userExtFlashEveGropHandle, EVENT_LVGL); // 唤醒线程B
		/*6.非阻塞等待数据采集完成唤醒*/
		osal_sema_give(userExtFlashSemaHandle);					//先释放一次，然后获取两次，第二次获取等待数据采集的任务释放
		osal_sema_take(userExtFlashSemaHandle,OSAL_MAX_DELAY);	//先占据二值信号量
		osal_sema_take(userExtFlashSemaHandle,OSAL_MAX_DELAY);	//等待driver handler 释放二值信号量
		osal_mutex_give(extern_flash_mutex_handler);			//释放互斥锁
	}
	return ret;
}

/**
 * @brief 外部存储器管理任务
 * @param[in] :None
 * @param[Out] :None
 * @return None
 * 
 * */
void storage_manager_task(void *argument)
{
	EventBits_t uxBits;
    const EventBits_t uxBitsToWaitFor = EVENT_LVGL;//EVENT_OTA | EVENT_FLASHDB | EVENT_FATFS | EVENT_LVGL;

	for (;;)
	{
		//等待事件唤醒
		uxBits = xEventGroupWaitBits(
			userExtFlashEveGropHandle,        		// 事件组句柄
			uxBitsToWaitFor,    					// 要等待的事件位
			pdTRUE,             					// 退出时清除事件位
			pdTRUE,             					// 所有事件位都要设置
			portMAX_DELAY       					// 无限期等待
		);
		switch((uxBits & uxBitsToWaitFor))
		{
			case EVENT_OTA:
			//TODO :Add
			break;

			case EVENT_FLASHDB:
			//TODO :Add
			break;

			case EVENT_FATFS:
			//TODO :Add
			break;

			case EVENT_LVGL:
			externflash_read(s_u32_TargetAddress,s_u32_Size,g_au8_lvgldata);
			break;

			default:
				//Nothing todo
			break;
		}
	}
}
//******************************** Function definitions ********************************//
