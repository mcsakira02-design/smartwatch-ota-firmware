/******************************************************************************
 *  
 * 
 * All Rights Reserved.
 * 
 * @file gpio_port.c
 * 
 * @par dependencies 
 * - gpio_port.h
 * - main.h
 * - gpio.h
 * 
 * @author ssj
 * 
 * @brief GPIO platform abstraction layer implementation
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
//******************************** Includes *********************************//
#include "gpio_port.h"
#include "main.h"
#include "gpio.h"
//******************************** Includes *********************************//

//******************************** Defines **********************************//

//******************************** Defines **********************************//

//******************************** Variables ********************************//
// GPIO引脚配置表
static const st_gpio_pin_config_t gpio_pin_configs[CORE_GPIO_PIN_MAX] = {
    // 显示相关GPIO
    [CORE_GPIO_LCD_RESET] = {
        .port = SPI_RESET_GPIO_Port,
        .pin = SPI_RESET_Pin,
        .default_state = CORE_GPIO_PIN_SET
    },
    [CORE_GPIO_LCD_DC] = {
        .port = LCD_DC_GPIO_Port,
        .pin = LCD_DC_Pin,
        .default_state = CORE_GPIO_PIN_RESET
    },
    [CORE_GPIO_LCD_CS] = {
        .port = LCD_CS_GPIO_Port,
        .pin = LCD_CS_Pin,
        .default_state = CORE_GPIO_PIN_RESET
    },
    
    // SPI相关GPIO
    [CORE_GPIO_SPI_RESET] = {
        .port = SPI_RESET_GPIO_Port,
        .pin = SPI_RESET_Pin,
        .default_state = CORE_GPIO_PIN_SET
    },
    [CORE_GPIO_SPI_CS] = {
        .port = SPI_CS_GPIO_Port,
        .pin = SPI_CS_Pin,
        .default_state = CORE_GPIO_PIN_RESET
    },
    
    // 触摸相关GPIO
    [CORE_GPIO_TP_RST] = {
        .port = TP_RST_GPIO_Port,
        .pin = TP_RST_Pin,
        .default_state = CORE_GPIO_PIN_SET
    },
    [CORE_GPIO_TP_INT] = {
        .port = TP_TINT_GPIO_Port,
        .pin = TP_TINT_Pin,
        .default_state = CORE_GPIO_PIN_SET
    },
    
    // 传感器相关GPIO
    [CORE_GPIO_SENSOR_SDA] = {
        .port = Sensor_SDA_GPIO_Port,
        .pin = Sensor_SDA_Pin,
        .default_state = CORE_GPIO_PIN_SET
    },
    [CORE_GPIO_SENSOR_SCL] = {
        .port = Sensor_SCL_GPIO_Port,
        .pin = Sensor_SCL_Pin,
        .default_state = CORE_GPIO_PIN_SET
    },
    
    // MPU6050中断引脚
    [CORE_GPIO_INT_FUNC] = {
        .port = Mpu6050_Int_GPIO_Port,
        .pin = Mpu6050_Int_Pin,
        .default_state = CORE_GPIO_PIN_RESET
    }
};
//******************************** Variables ********************************//

//******************************** Functions ********************************//
/**
 * @brief GPIO平台初始化
 * @param[in] None
 * @param[out] None
 * @return en_core_gpio_status_t 初始化状态
 */
en_core_gpio_status_t core_gpio_init(void)
{
    // 设置所有GPIO引脚为默认状态
    for(uint8_t i = 0; i < CORE_GPIO_PIN_MAX; i++)
    {
        if(gpio_pin_configs[i].port != NULL)
        {
            GPIO_PinState state = (gpio_pin_configs[i].default_state == CORE_GPIO_PIN_SET) ? 
                                  GPIO_PIN_SET : GPIO_PIN_RESET;
            HAL_GPIO_WritePin(gpio_pin_configs[i].port, gpio_pin_configs[i].pin, state);
        }
    }
    
    return CORE_GPIO_OK;
}

/**
 * @brief 写GPIO引脚状态
 * @param[in] pin GPIO引脚枚举
 * @param[in] state 引脚状态
 * @param[out] None
 * @return en_core_gpio_status_t 操作状态
 */
en_core_gpio_status_t core_gpio_write_pin(en_core_gpio_pin_t pin, en_core_gpio_pin_state_t state)
{
    if(pin >= CORE_GPIO_PIN_MAX)
    {
        return CORE_GPIO_ERROR;
    }
    
    if(gpio_pin_configs[pin].port == NULL)
    {
        return CORE_GPIO_ERROR;
    }
    
    GPIO_PinState hal_state = (state == CORE_GPIO_PIN_SET) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(gpio_pin_configs[pin].port, gpio_pin_configs[pin].pin, hal_state);
    
    return CORE_GPIO_OK;
}

/**
 * @brief 读GPIO引脚状态
 * @param[in] pin GPIO引脚枚举
 * @param[out] None
 * @return en_core_gpio_pin_state_t 引脚状态
 */
en_core_gpio_pin_state_t core_gpio_read_pin(en_core_gpio_pin_t pin)
{
    if(pin >= CORE_GPIO_PIN_MAX || gpio_pin_configs[pin].port == NULL)
    {
        return CORE_GPIO_PIN_RESET;
    }
    
    GPIO_PinState hal_state = HAL_GPIO_ReadPin(gpio_pin_configs[pin].port, gpio_pin_configs[pin].pin);
    
    return (hal_state == GPIO_PIN_SET) ? CORE_GPIO_PIN_SET : CORE_GPIO_PIN_RESET;
}

/**
 * @brief 翻转GPIO引脚状态
 * @param[in] pin GPIO引脚枚举
 * @param[out] None
 * @return en_core_gpio_status_t 操作状态
 */
en_core_gpio_status_t core_gpio_toggle_pin(en_core_gpio_pin_t pin)
{
    if(pin >= CORE_GPIO_PIN_MAX)
    {
        return CORE_GPIO_ERROR;
    }
    
    if(gpio_pin_configs[pin].port == NULL)
    {
        return CORE_GPIO_ERROR;
    }
    
    HAL_GPIO_TogglePin(gpio_pin_configs[pin].port, gpio_pin_configs[pin].pin);
    
    return CORE_GPIO_OK;
}

/**
 * @brief 直接写GPIO引脚状态（兼容HAL库接口）
 * @param[in] GPIOx GPIO端口
 * @param[in] GPIO_Pin GPIO引脚
 * @param[in] PinState 引脚状态
 * @param[out] None
 * @return en_core_gpio_status_t 操作状态
 */
en_core_gpio_status_t core_gpio_write_pin_direct(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    if(GPIOx == NULL)
    {
        return CORE_GPIO_ERROR;
    }
    
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
    
    return CORE_GPIO_OK;
}

/**
 * @brief 直接读GPIO引脚状态（兼容HAL库接口）
 * @param[in] GPIOx GPIO端口
 * @param[in] GPIO_Pin GPIO引脚
 * @param[out] None
 * @return GPIO_PinState 引脚状态
 */
GPIO_PinState core_gpio_read_pin_direct(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    if(GPIOx == NULL)
    {
        return GPIO_PIN_RESET;
    }
    
    return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

/**
 * @brief 直接翻转GPIO引脚状态（兼容HAL库接口）
 * @param[in] GPIOx GPIO端口
 * @param[in] GPIO_Pin GPIO引脚
 * @param[out] None
 * @return en_core_gpio_status_t 操作状态
 */
en_core_gpio_status_t core_gpio_toggle_pin_direct(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    if(GPIOx == NULL)
    {
        return CORE_GPIO_ERROR;
    }
    
    HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
    
    return CORE_GPIO_OK;
}

//******************************** Functions ********************************//



