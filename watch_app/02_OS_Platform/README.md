# 操作系统封装层 OS Platform

## 📌 模块定位
封装 RTOS 内核能力，对外统一提供任务、队列、信号量、内存管理等接口，便于替换操作系统。

## 📁 模块结构
- OSAL_Task
- OSAL_Sema
- OSAL_Queue
- OSAL_Heap

## ✅ 命名规范
- 模块前缀建议使用 `Dbg_` 或 `Test_`
- 函数命名建议使用 `MCU_设备_操作`，如 `MCU_UART_Send()`
- 结构体命名建议使用 `MCU_设备_Config_t`，如 `MCU_UART_Config_t`
- 宏定义建议使用 `MCU_设备_XXX`，如 `MCU_UART_TX_PIN`

## 🔄 依赖关系
- 向下依赖具体 RTOS（如 FreeRTOS）
- 向上供 APP 和 Middleware 调用

## 👥 责任人
- OS平台负责人：@Jack,Simon
