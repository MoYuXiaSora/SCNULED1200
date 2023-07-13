/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */

#define USART3_NEW_FRAME 1
#define USART3_OLD_FRAME 0
	
struct UARTEx_FRAME
{
    /* data */
	volatile uint8_t new_Frame_Flag; //是否收到了新�?�? �?:USART3_NEW_FRAME �?:USART3_OLD_FRAME
	volatile uint8_t tx_Frame_Flag;	 //是否成功发�?�了新一�? 发�?�成功返回：HAL_OK   发�?�失败返回：HAL_BUSY / HAL_ERROR
	volatile uint16_t frame_Length;	 //新一帧数据长�?
	uint8_t *pData;	//缓冲区数组地�?指针
};

/* USER CODE END Private defines */

void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */

struct UARTEx_FRAME Transmit_To_ESP32C3(uint8_t *pData, uint16_t Size);
struct UARTEx_FRAME Receive_From_ESP32C3();
struct UARTEx_FRAME clear_UARTx_Frame();

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

