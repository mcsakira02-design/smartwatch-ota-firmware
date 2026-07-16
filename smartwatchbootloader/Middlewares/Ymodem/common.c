/**
  ******************************************************************************
  * @file    common.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    10/15/2010
  * @brief   Common functions for Ymodem protocol
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "ymodem.h"
#include "stm32f4xx.h"
#include "USART.h"

/**
  * @brief  Convert string to integer
  * @param  inputstr: Input string to convert
  * @param  intnum: Converted integer value
  * @retval 1: Success, 0: Error
  */
uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum)
{
    uint32_t i = 0, res = 0;
    uint32_t val = 0;

    if (inputstr[0] == '0' && (inputstr[1] == 'x' || inputstr[1] == 'X'))
    {
        if (inputstr[2] == '\0')
        {
            return 0;
        }
        for (i = 2; i < 11; i++)
        {
            if (inputstr[i] == '\0')
            {
                *intnum = val;
                res = 1;
                break;
            }
            if (ISVALIDHEX(inputstr[i]))
            {
                val = (val << 4) + CONVERTHEX(inputstr[i]);
            }
            else
            {
                res = 0;
                break;
            }
        }

        if (i >= 11)
        {
            res = 0;
        }
    }
    else
    {
        for (i = 0; i < 11; i++)
        {
            if (inputstr[i] == '\0')
            {
                *intnum = val;
                res = 1;
                break;
            }
            else if ((inputstr[i] == 'k' || inputstr[i] == 'K') && (i > 0))
            {
                val = val << 10;
                *intnum = val;
                res = 1;
                break;
            }
            else if ((inputstr[i] == 'm' || inputstr[i] == 'M') && (i > 0))
            {
                val = val << 20;
                *intnum = val;
                res = 1;
                break;
            }
            else if (ISVALIDDEC(inputstr[i]))
            {
                val = val * 10 + CONVERTDEC(inputstr[i]);
            }
            else
            {
                res = 0;
                break;
            }
        }
        
        if (i >= 11)
        {
            res = 0;
        }
    }

    return res;
}

/**
  * @brief  Check if a key is pressed on serial port
  * @param  key: Pointer to store the received key
  * @retval 1: Key pressed, 0: No key pressed
  */
uint32_t SerialKeyPressed(uint8_t *key)
{
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
    {
        *key = (uint8_t)USART1->DR;
        //*key = (uint8_t)USART_ReceiveData(USART1);
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
  * @brief  Send a character via serial port
  * @param  c: Character to send
  * @retval None
  */
void SerialPutChar(uint8_t c)
{
    USART_SendChar(USART1, c);
}
