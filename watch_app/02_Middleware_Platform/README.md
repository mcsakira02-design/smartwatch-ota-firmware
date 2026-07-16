# 中间件平台层 Middleware Platform

## 📌 模块定位
封装通用算法、中间件库（如Shell、协议栈、图形库等），提升平台可移植性和逻辑复用能力。

## 📁 典型模块
- LetterShell
- CircularBuffer
- AES Library
- Math Utility
- LVGL

## ✅ 命名规范
- 统一使用 `MW_Lib_模块名`、`MW_If_接口名`

## 🔄 依赖关系
- 依赖 OS 平台提供的任务/内存接口
- 可选依赖 BSP 或 MCU 能力

## 👥 责任人
- Middleware平台负责人：@XXX
