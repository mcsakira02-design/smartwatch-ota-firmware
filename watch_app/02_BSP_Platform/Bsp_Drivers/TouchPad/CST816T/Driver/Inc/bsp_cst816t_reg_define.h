/******************************************************************************
 * Copyright (C) 2025 EternalChip, Inc.(Gmbh) or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file bsp_cst816t_reg_define.h
 * 
 * @par dependencies 
 * 
 * @author 
 * 
 * @brief Provide the CST816T register definitions.
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
#ifndef __BSP_CST816T_REG_DEFINE_H
#define __BSP_CST816T_REG_DEFINE_H

#define GESTURE_ID          0x01    /* Current gesture ID                    */
#define FINGER_NUM          0x02    /* Number of fingers detected            */
#define X_POSH              0x03    /* X coordinate high byte                */
#define X_POSL              0x04    /* X coordinate low byte                 */
#define Y_POSH              0x05    /* Y coordinate high byte                */
#define Y_POSL              0x06    /* Y coordinate low byte                 */
#define CHIPID              0xA7    /* Chip ID                               */
#define PROJID              0xA8    /* Project ID                            */
#define FWVERSION           0xA9    /* Firmware versioN                      */
#define FACTORYID           0xAA    /* Factory ID                            */

#define BPCOH               0XB0    /* BPC offset high byte                  */
#define BPCOL               0XB1    /* BPC offset low byte                   */
#define BPC1H               0XB2    /* BPC1 high byte                        */
#define BPC1L               0XB3    /* BPC1 low byte                         */

#define SLEEPMODE           0XE5    /* Sleep mode control                    */
#define ERRRESETCTL         0XEA    /* Error reset control                   */
#define LONGPRESSTICK       0XEB    /* Long press stick                      */
#define MOTIONMASK          0XEC    /* Motion mask                           */
#define IRQPLUSEWIDTH       0XED    /* IRQ pulse width                       */
#define NORSCANPER          0XEE    /* Normal scan period                    */
#define MOTIONSLANGLE       0XEF    /* Motion slope angle                    */

#define LPSCANRAW1H         0XF0    /* Long press scan raw 1 high byte       */
#define LPSCANRAW1L         0XF1    /* Long press scan raw 1 low byte        */
#define LPSCANRAW2H         0XF2    /* Long press scan raw 2 high byte       */
#define LPSCANRAW2L         0XF3    /* Long press scan raw 2 low byte        */
#define LPAUTOWAKETIME      0XF4    /* Long press auto wake time             */
#define LPSCANTH            0XF5    /* Long press scan threshold             */
#define LPSCANWIN           0XF6    /* Long press scan window                */
#define LPSCANFREQ          0XF7    /* Long press scan frequency             */
#define LPSCANIDAC          0XF8    /* Long press scan IDAC                  */
#define AUTOSLEEPTIME       0XF9    /* Auto sleep time                       */
#define IRQCTL              0XFA    /* IRQ control                           */
#define AUTORESET           0XFB    /* Auto reset                            */
#define LONGPRESSTIME       0XFC    /* Long press time                       */
#define IOCTL               0XFD    /* IO control                            */
#define DISAUTOALEEP        0XFE    /* Disable auto sleep                    */

#endif /* __BSP_CST816T_REG_DEFINE_H */
