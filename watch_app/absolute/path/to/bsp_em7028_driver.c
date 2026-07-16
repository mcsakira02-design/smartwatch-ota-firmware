// 增加传感器模式配置
em7028_write_reg(EM7028_MODE_CONTROL, 0x02);  // 设置为心率监测模式
em7028_write_reg(EM7028_SAMPLE_RATE, 0x01);   // 设置采样率为100Hz

// 添加LED电流配置（根据硬件设计调整）
em7028_write_reg(EM7028_LED_CURRENT, 0x0F);  // 适当增大LED驱动电流