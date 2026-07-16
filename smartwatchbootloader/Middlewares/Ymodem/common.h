/**
  ******************************************************************************
  * @file    common.h 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    10/15/2010
  * @brief   Common header file for Ymodem protocol
  ******************************************************************************
  */

#ifndef _COMMON_H_
#define _COMMON_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "ymodem.h"

/* Exported types ------------------------------------------------------------*/
typedef void (*pFunction)(void);

/* Exported constants --------------------------------------------------------*/
#define CMD_STRING_SIZE         128

#define PAGE_SIZE               0x800
#define FLASH_SIZE              0x100000
#define MAX_APP_SIZE            0x74000
/* Exported macro ------------------------------------------------------------*/
#define IS_AF(c)  ((c >= 'A') && (c <= 'F'))
#define IS_af(c)  ((c >= 'a') && (c <= 'f'))
#define IS_09(c)  ((c >= '0') && (c <= '9'))
#define ISVALIDHEX(c)  IS_AF(c) || IS_af(c) || IS_09(c)
#define ISVALIDDEC(c)  IS_09(c)
#define CONVERTDEC(c)  (c - '0')

#define CONVERTHEX_alpha(c)  (IS_AF(c) ? (c - 'A'+10) : (c - 'a'+10))
#define CONVERTHEX(c)   (IS_09(c) ? (c - '0') : CONVERTHEX_alpha(c))

/* Exported functions --------------------------------------------------------*/
uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum);
uint32_t SerialKeyPressed(uint8_t *key);
void SerialPutChar(uint8_t c);

#endif  /* _COMMON_H_ */
