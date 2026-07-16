/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file gpio_port.h
 * 
 * @par dependencies 
 * - main.h
 * - gpio.h
 * 
 * @author ssj
 * 
 * @brief GPIO platform abstraction layer interface
 * 
 * Processing flow:
 * 
 * Call directly.
 * 
 * @version V1.0
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
 
#ifndef __GPIO_PORT_H__  /* Avoid repeated inclusion */
#define __GPIO_PORT_H__

//******************************** Includes *********************************//
#include "main.h"
#include "gpio.h"
//******************************** Includes *********************************//

//******************************** Typedefs *********************************//
typedef enum
{
    CORE_GPIO_OK = 0,
    CORE_GPIO_ERROR
}en_core_gpio_status_t;

typedef enum
{
    CORE_GPIO_PIN_RESET = 0,
    CORE_GPIO_PIN_SET
}en_core_gpio_pin_state_t;

// GPIO引脚定义枚举
typedef enum
{
    // 显示相关GPIO
    CORE_GPIO_LCD_RESET = 0,    // LCD复位引脚
    CORE_GPIO_LCD_DC,           // LCD数据/命令选择引脚
    CORE_GPIO_LCD_CS,           // LCD片选引脚
    
    // SPI相关GPIO
    CORE_GPIO_SPI_RESET,        // SPI复位引脚
    CORE_GPIO_SPI_CS,           // SPI片选引脚
    
    // 触摸相关GPIO
    CORE_GPIO_TP_RST,           // 触摸屏复位引脚
    CORE_GPIO_TP_INT,           // 触摸屏中断引脚
    
    // 传感器相关GPIO
    CORE_GPIO_SENSOR_SDA,       // 传感器I2C数据线
    CORE_GPIO_SENSOR_SCL,       // 传感器I2C时钟线
    
    // 功能引脚
    CORE_GPIO_INT_FUNC,         // 功能中断引脚
    
    CORE_GPIO_PIN_MAX
}en_core_gpio_pin_t;

typedef struct
{
    GPIO_TypeDef* port;         // GPIO端口
    uint16_t pin;               // GPIO引脚
    en_core_gpio_pin_state_t default_state; // 默认状态
} st_gpio_pin_config_t;

//******************************** Typedefs *********************************//

//******************************** Defines **********************************//
// LCD相关GPIO操作宏
#define LCD_RESET_SET()         core_gpio_write_pin(CORE_GPIO_LCD_RESET, CORE_GPIO_PIN_SET)
#define LCD_RESET_CLR()         core_gpio_write_pin(CORE_GPIO_LCD_RESET, CORE_GPIO_PIN_RESET)
#define LCD_DC_SET()            core_gpio_write_pin(CORE_GPIO_LCD_DC, CORE_GPIO_PIN_SET)
#define LCD_DC_CLR()            core_gpio_write_pin(CORE_GPIO_LCD_DC, CORE_GPIO_PIN_RESET)
#define LCD_CS_SET()            core_gpio_write_pin(CORE_GPIO_LCD_CS, CORE_GPIO_PIN_SET)
#define LCD_CS_CLR()            core_gpio_write_pin(CORE_GPIO_LCD_CS, CORE_GPIO_PIN_RESET)

// SPI相关GPIO操作宏
#define SPI_RESET_SET()         core_gpio_write_pin(CORE_GPIO_SPI_RESET, CORE_GPIO_PIN_SET)
#define SPI_RESET_CLR()         core_gpio_write_pin(CORE_GPIO_SPI_RESET, CORE_GPIO_PIN_RESET)
#define SPI_CS_SET()            core_gpio_write_pin(CORE_GPIO_SPI_CS, CORE_GPIO_PIN_SET)
#define SPI_CS_CLR()            core_gpio_write_pin(CORE_GPIO_SPI_CS, CORE_GPIO_PIN_RESET)

// 触摸相关GPIO操作宏
#define TP_RST_SET()            core_gpio_write_pin(CORE_GPIO_TP_RST, CORE_GPIO_PIN_SET)
#define TP_RST_CLR()            core_gpio_write_pin(CORE_GPIO_TP_RST, CORE_GPIO_PIN_RESET)
#define TP_INT_READ()           core_gpio_read_pin(CORE_GPIO_TP_INT)

// 功能引脚操作宏
#define INT_FUNC_SET()          core_gpio_write_pin(CORE_GPIO_INT_FUNC, CORE_GPIO_PIN_SET)
#define INT_FUNC_CLR()          core_gpio_write_pin(CORE_GPIO_INT_FUNC, CORE_GPIO_PIN_RESET)

//******************************** Defines **********************************//

//******************************** Function Declarations *******************//
/**
 * @brief GPIO平台初始化
 * @param[in] None
 * @param[out] None
 * @return en_core_gpio_status_t 初始化状态
 */
en_core_gpio_status_t core_gpio_init(void);

/**
 * @brief 写GPIO引脚状态
 * @param[in] pin GPIO引脚枚举
 * @param[in] state 引脚状态
 * @param[out] None
 * @return en_core_gpio_status_t 操作状态
 */
en_core_gpio_status_t core_gpio_write_pin(en_core_gpio_pin_t pin, en_core_gpio_pin_state_t state);

/**
 * @brief 读GPIO引脚状态
 * @param[in] pin GPIO引脚枚举
 * @param[out] None
 * @return en_core_gpio_pin_state_t 引脚状态
 */
en_core_gpio_pin_state_t core_gpio_read_pin(en_core_gpio_pin_t pin);

/**
 * @brief 翻转GPIO引脚状态
 * @param[in] pin GPIO引脚枚举
 * @param[out] None
 * @return en_core_gpio_status_t 操作状态
 */
en_core_gpio_status_t core_gpio_toggle_pin(en_core_gpio_pin_t pin);

/**
 * @brief 直接写GPIO引脚状态（兼容HAL库接口）
 * @param[in] GPIOx GPIO端口
 * @param[in] GPIO_Pin GPIO引脚
 * @param[in] PinState 引脚状态
 * @param[out] None
 * @return en_core_gpio_status_t 操作状态
 */
en_core_gpio_status_t core_gpio_write_pin_direct(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

/**
 * @brief 直接读GPIO引脚状态（兼容HAL库接口）
 * @param[in] GPIOx GPIO端口
 * @param[in] GPIO_Pin GPIO引脚
 * @param[out] None
 * @return GPIO_PinState 引脚状态
 */
GPIO_PinState core_gpio_read_pin_direct(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/**
 * @brief 直接翻转GPIO引脚状态（兼容HAL库接口）
 * @param[in] GPIOx GPIO端口
 * @param[in] GPIO_Pin GPIO引脚
 * @param[out] None
 * @return en_core_gpio_status_t 操作状态
 */
en_core_gpio_status_t core_gpio_toggle_pin_direct(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

//******************************** Function Declarations *******************//

#endif /* __GPIO_PORT_H__ */



