/*****************************************************************************
 * KEROS I2C Bus Driver
 *
 *
 * Copyright(C) CHIPSBRAIN GLOBAL CO., Ltd.
 * All rights reserved.
 *
 * File Name    : keros_i2c_interface.c
 * Author       : ARES HA
 *
 * Version      : V0.3
 * Date         : 2015.09.08
 * Description  : Keros I2C Bus Driver
 ****************************************************************************/
#define _SOURCE_I2CBUS_

/* USER INCLUDE BEGIN */

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "common.h"

/* USER INCLUDE END  */

#include "keros_lib.h"
#include "keros_i2c_interface.h"
//void  OSTimeDly (__IO INT16U ticks);

//static uint8_t  	cBusEnable;
//static uint16_t  	iStretchTime;


#define 	DLY_TIM_1	10//2
#define 	DLY_TIM_2	1

#define SDA_GPIO_Port	GPIOB
#define SCL_GPIO_Port 	GPIOB

#define SDA_Pin	GPIO_Pin_7
#define SCL_Pin	GPIO_Pin_6

/* USER CODE BEGIN  */
//  PORT Define
#define SDAHigh0  	{GPIO_SetBits(SDA_GPIO_Port, SDA_Pin);}
#define SDALow0   	{GPIO_ResetBits(SDA_GPIO_Port, SDA_Pin);}

#define SCLHigh0  	{GPIO_SetBits(SCL_GPIO_Port, SCL_Pin);}
#define SCLLow0   	{GPIO_ResetBits(SCL_GPIO_Port, SCL_Pin);}
#define SDAIn0(bMask)   {bMask = GPIO_ReadInputDataBit(SDA_GPIO_Port,SDA_Pin);}

//  SDA PORT Input/Output Define

void SCL0_PORT_OUTPUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/*Configure GPIO pin : I2C_SCL_Pin */
  	GPIO_InitStruct.GPIO_Pin = SCL_Pin;
  	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(SCL_GPIO_Port, &GPIO_InitStruct);
}

void SDA0_PORT_OUTPUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/*Configure GPIO pin : I2C_SDA_Pin */
  	GPIO_InitStruct.GPIO_Pin = SDA_Pin;
  	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(SDA_GPIO_Port, &GPIO_InitStruct);
}

void SDA0_PORT_INPUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

  	/*Configure GPIO pin : I2C_SDA_Pin */
  	GPIO_InitStruct.GPIO_Pin = SDA_Pin;
  	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(SDA_GPIO_Port, &GPIO_InitStruct);

}
/* USER CODE END  */


/******************************************************************************
 *
 * Function:
 *
 * Parameters:
 *
 *
 * Variables:        --
 *
 * Return Value:     --
 *
 * Description:      enables or disables the transmission for the selected channel
 *
 ******************************************************************************/
void  OSTimeDly (volatile uint16_t  ticks)
{
	while(ticks--);
}

void I2CSetInitial(void)
{
    /* Enable GPIOB clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
    /* Initialize SDA and SCL pins */
    SDA0_PORT_OUTPUT();
    SCL0_PORT_OUTPUT();
    
    /* Set initial state */
    I2CMasterStop();
}


/******************************************************************************
 *
 * Function:         I2CMasterStop
 *
 * Parameters:       bChannel
 *                            0 : I2C channel 0
 *                            1 : I2C channel 1
 *
 * Variables:        --
 *
 * Return Value:     --
 *
 * Description:      generates a stop condition on the selected channel
 *
 ******************************************************************************/

void I2CMasterStop(void)
{
	SDA0_PORT_OUTPUT();       	  /*  port direction P6.4 is an output */

	SCLLow0;
	SDALow0;
	OSTimeDly(DLY_TIM_1);
	SCLHigh0;
	OSTimeDly(DLY_TIM_1);
	SDAHigh0;
}

/******************************************************************************
 *
 * Function:         I2CMasterInit
 *
 * Parameters:       bChannel
 *                            0 : I2C channel 0
 *                            1 : I2C channel 1
 *
 * Variables:        --
 *
 * Return Value:     --
 *
 * Description:      initialises the I2C bus software interface for the selected
 *                   channel
 *
 ******************************************************************************/

void I2CMasterInit(void)
{
	uint8_t  cRc;

	SDAIn0(cRc);

	if(!cRc)
		I2CMasterStop();
}

/******************************************************************************
 *
 * Function:         I2CMasterStart
 *
 * Parameters:       bChannel
 *                            0 : I2C channel 0
 *                            1 : I2C channel 1
 *
 * Variables:        --
 *
 * Return Value:     --
 *
 * Description:      generates a start-condition on the selected channel
 *
 ******************************************************************************/

void I2CMasterStart(void)
{
	 SDA0_PORT_OUTPUT();          /*  port direction P3.1 is an output */

	SDAHigh0;
	SCLHigh0;
	OSTimeDly(DLY_TIM_1);
	SDALow0;
	OSTimeDly(DLY_TIM_1);
	SCLLow0;
}

/******************************************************************************
 *
 * Function:         I2CMasterWrite
 *
 * Parameters:       bChannel
 *                            0 : I2C channel 0
 *                            1 : I2C channel 1
 *                   bDataByte  : byte to write
 *
 * Variables:        --
 *
 * Return-value:     1 : if no acknowledge from I2C Bus slave receiver
 *                   0 : if acknowledge from I2C Bus slave receiver
 *
 * Description:      transmits one byte on the selected channel
 *
 ******************************************************************************/

uint8_t I2CMasterWrite(uint8_t bDataByte)
{
	uint8_t bMask;
	int i;

   	bMask = 0x80;
   	//if(bChannel == BUS0)
   	{
		for(i = 0; i < 8; i++)
      	{
			if( (bMask & bDataByte))
				SDAHigh0
			else
				SDALow0

			bMask = bMask >> 1;

			SCLHigh0;
			OSTimeDly(DLY_TIM_1);
         	SCLLow0;
			OSTimeDly(DLY_TIM_1); //pdz 2019 0510
      	}

      	SDAHigh0;
      	SDA0_PORT_INPUT();        	  /*  port direction P6.4 is an input */
      	//OSTimeDly(DLY_TIM_1);
		SCLHigh0;
		OSTimeDly(DLY_TIM_1);
		SDAIn0(bMask);
		SCLLow0;

		SDA0_PORT_OUTPUT();
   	}

   	/* return acknowledge */
   	return bMask;
}

/******************************************************************************
 *
 * Function:         I2CMasterRead
 *
 * Parameters:       bChannel
 *                              0 : I2C channel 0
 *                              1 : I2C channel 1
 *                   bAck
 *                              1 : send acknowledge after byte transmission
 *                              0 : no acknowledge after transmission(=>last byte send)
 *
 * Variables:        --
 *
 * Return Value:     received byte
 *
 * Description:      reads one byte on the selected channel
 *
 ******************************************************************************/

uint8_t I2CMasterRead( uint8_t bAck)
{
   	uint8_t bMask, cReceiveByte, i ;
		uint8_t  cRc;

		cReceiveByte= 0;
    bMask = 0x80;
   	//if(bChannel == BUS0)
   	{
      		//SDAHigh0;
      		SDA0_PORT_INPUT();        	   /*  port direction P6.4 is an input */

					for(i = 0; i < 8; i++)
      		{

         		SCLHigh0;

						SDAIn0(cRc);
         		if(cRc)
            			cReceiveByte |= bMask;
         		else
            			cReceiveByte |= 0x00; /*  only to get symetric bus */

						//OSTimeDly(DLY_TIM_1);
         		SCLLow0;
        	 	bMask = bMask >> 1;
						OSTimeDly(DLY_TIM_1);
       		}

      		SDA0_PORT_OUTPUT();    	     /*  port direction P6.4 is an output */

      		SDAHigh0;
					//OSTimeDly(DLY_TIM_1);
      		if(bAck)
         		SDALow0;

					//OSTimeDly(DLY_TIM_1);
       		SCLHigh0;
					OSTimeDly(DLY_TIM_1);
      		SCLLow0;


  	}

   	/* return received databyte */
   return cReceiveByte;

}


/******************************************************************************
 *
 * Function:         I2CSendDeviceAddress
 *
 * Parameters:       bChannel
 *                              0 : I2C channel 0
 *                              1 : I2C channel 1
 *                   bDevAddr : IC slave address
 *                   wSubAddr : subaddress of I2C bus slave IC,
 *                              start address (first byte) of data block,
 *                              if '-1': no subaddress to be send
 *
 * Variables:        --
 *
 * Return-value:               0 : operation successful
 *        ERR_I2C_NO_ADDRESS_ACK : no ack for IC-address
 *     ERR_I2C_NO_SUBADDRESS_ACK : no ack for subaddress/first byte
 *
 * Description:      generates start condition, device address and subaddress on
 *                   selected channel
 *
 ******************************************************************************/

uint8_t I2CSendDeviceAddress( uint8_t bDevAddr)
{
   	uint8_t i;

   	I2CMasterInit();
   	for(i = 0; i < MAXATTEMPTS; i++)
   	{
      		I2CMasterStart();
      		if(I2CMasterWrite( bDevAddr) == 0)
      		{
         			return 0;
      		}
   	}
   	return ERR_I2C_NO_ADDRESS_ACK;
}

/******************************************************************************
 *
 * Function:         I2CMasterReceiver
 *
 * Parameters:       bChannel
 *                              0 : I2C channel 0
 *                              1 : I2C channel 1
 *                   bDevAddr : IC slave address
 *
 * Variables:        --
 *
 * Return Value:     0 : operation successful(acknowledge by I2C Bus slave receiver)
 *                   1 : no acknowledge by I2C Bus slave receiver
 *
 * Description:      generates a repeated start condition, followed by a device read
 *                   address
 *
 ******************************************************************************/

uint8_t I2CMasterReceiver( uint8_t bDevAddr)
{
   	bDevAddr |= 0x01;
   	I2CMasterStart();
   	return I2CMasterWrite(bDevAddr);
}

/****************************************************************************
 *
 * Function:      I2cWrite
 *
 * Parameters:    bChannel       ;[in]  I2C channel [0, 1]
 *                bDevAddr       ;[in]  IC device address
 *                pbAddr         ;[in]  Pointer to start of buffer of subaddresses
 *                wAddrLen       ;[in]  Length (number of bytes) of subaddress buffer
 *                pbData         ;[in]  Pointer to start of received data buffer
 *                wDataLen       ;[in]  Length (number of bytes) of data buffer
 *
 * Return Value:  uint8_t  = 0                         : operation successful
 *                      = ERR_I2C_BUS_DISABLE       : bus disabled by user
 *                      = ERR_I2C_NO_ADDRESS_ACK    : no ack for IC-address
 *                      = ERR_I2C_NO_SUBADDRESS_ACK : no ack for subaddress
 *
 * Description:   General I2c bus routine to write number of bytes of subaddresses
 *                and write number of bytes of data to the I2C Bus on the
 *                selected channel.
 *
 ****************************************************************************/

uint8_t I2CWrite (uint8_t bDevAddr, uint8_t *pbAddr, uint8_t wAddrLen, uint8_t *pbData, uint8_t wDataLen)
{
   	uint8_t bErr;


      	/*  Write Device Address */
      	bErr = I2CSendDeviceAddress (bDevAddr);

      	if (bErr)
         	{  I2CMasterStop (); return bErr;  }

      	/*  Write Subaddresses */
      	while (wAddrLen > 0)
      	{
         	if (I2CMasterWrite (*pbAddr) > 0)
            		{  I2CMasterStop();  return ERR_I2C_NO_DATA_ACK;  }

         	pbAddr ++;
         	wAddrLen --;
      	}

      	/*  Write Databytes */
      	while (wDataLen > 0)
      	{
         	if (I2CMasterWrite (*pbData) > 0)
            		{  I2CMasterStop();  return ERR_I2C_NO_DATA_ACK;  }

         	pbData ++;
         	wDataLen --;
      	}

      	I2CMasterStop ();

   	return 0;

} /*  I2CWrite */

/****************************************************************************
 *
 * Function:      I2cRead
 *
 * Parameters:    bChannel       ;[in]  I2C channel [0, 1]
 *                bDevAddr       ;[in]  IC device address
 *                pbAddr         ;[in]  Pointer to start of buffer of subaddresses
 *                wAddrLen       ;[in]  Length (number of bytes) of subaddress buffer
 *                pbData         ;[out] Pointer to start of received data buffer
 *                wDataLen       ;[in]  Length (number of bytes) of data buffer
 *
 * Return Value:  uint8_t  = 0                         : operation successful
 *                      = ERR_I2C_BUS_DISABLE       : bus disabled by user
 *                      = ERR_I2C_NO_ADDRESS_ACK    : no ack for IC-address
 *                      = ERR_I2C_NO_SUBADDRESS_ACK : no ack for subaddress
 *
 * Description:   General I2c bus routine to write number of bytes of subaddresses
 *                and read number of bytes of data from the I2C Bus on the
 *                selected channel.
 *
 ****************************************************************************/

uint8_t I2CRead (uint8_t bDevAddr, uint8_t *pbAddr, uint8_t wAddrLen, uint8_t *pbData, uint8_t wDataLen)
{
   	uint8_t bErr;

   	/*  Write Device Address */
      	bErr = I2CSendDeviceAddress ( bDevAddr);

      	if (bErr)
      	{
         	I2CMasterStop ();
         	return bErr;
      	}

      	/*  Write Subaddresses */
      	while (wAddrLen > 0)
      	{
         	if (I2CMasterWrite ( *pbAddr) > 0)
            		{  I2CMasterStop();  return ERR_I2C_NO_DATA_ACK;  }

         	pbAddr ++;
         	wAddrLen --;
      	}

      	/*  Send repeated startcondition and IC read-address */
      	SDAHigh0;
      	bErr = I2CMasterReceiver ( bDevAddr);

      	if (bErr)
         	{  I2CMasterStop (); return bErr;  }

      	if (wDataLen == 0)
         	return 0;

      	/*  Read Databytes with acknowledge from master */
      	wDataLen --;

      	while (wDataLen > 0)
      	{
         	*pbData = I2CMasterRead (1);
         	pbData ++;
         	wDataLen --;
      	}

      	/*  Read last Databyte with no acknowledge from master */
      	*pbData = I2CMasterRead (0);
      	I2CMasterStop();

   	return 0;
} /*  I2CRead */


