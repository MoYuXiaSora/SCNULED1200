/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "string.h"

#define USART3_DMA_RX_BUFFER_LENGTH 256 //由用户配置DMA缓存�? 可更�?
#define USART3_DMA_RX_IT_BUFFER_LENGTH 256 //由用户配置DMA_IT缓存�? 可更�?
__attribute__ ((section(".IRAM1"))) static volatile uint8_t USART3_DMA_Rx_Buffer[USART3_DMA_RX_BUFFER_LENGTH];
__attribute__ ((section(".IRAM1"))) static volatile uint8_t USART3_DMA_Rx_It_Buffer[USART3_DMA_RX_IT_BUFFER_LENGTH];

static struct UARTEx_FRAME UART3_Frame={
	.new_Frame_Flag=USART3_OLD_FRAME,
	.tx_Frame_Flag=HAL_OK,
	.frame_Length=0,
	.pData=USART3_DMA_Rx_Buffer
};

/* USER CODE END 0 */

UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart3_rx;

/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);//使能idle中断
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3,USART3_DMA_Rx_It_Buffer,sizeof(USART3_DMA_Rx_It_Buffer)/sizeof(USART3_DMA_Rx_It_Buffer[0]));
	__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);
	__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_DME);
  /* USER CODE END USART3_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART3 DMA Init */
    /* USART3_RX Init */
    hdma_usart3_rx.Instance = DMA1_Stream1;
    hdma_usart3_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart3_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart3_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart3_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart3_rx.Init.Mode = DMA_NORMAL;
    hdma_usart3_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart3_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart3_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart3_rx);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

    /* USART3 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart->Instance=USART3)
	{
		static uint16_t frame_Length_Last=0;
		
		UART3_Frame.new_Frame_Flag = USART3_NEW_FRAME;
		
		frame_Length_Last = UART3_Frame.frame_Length;
		
		UART3_Frame.frame_Length += USART3_DMA_RX_BUFFER_LENGTH - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);
		
		if((frame_Length_Last>(USART3_DMA_RX_BUFFER_LENGTH-1))||(UART3_Frame.frame_Length>USART3_DMA_RX_BUFFER_LENGTH))
		{
			frame_Length_Last=0;
		}
		
		memcpy(USART3_DMA_Rx_Buffer+frame_Length_Last,USART3_DMA_Rx_It_Buffer,UART3_Frame.frame_Length-frame_Length_Last);
		
		/* start the DMA again */
	  HAL_UARTEx_ReceiveToIdle_DMA(&huart3,USART3_DMA_Rx_It_Buffer,sizeof(USART3_DMA_Rx_It_Buffer)/sizeof(USART3_DMA_Rx_It_Buffer[0]));
		__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);
	  __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_DME);
	}
}


/**
  * @brief  使用 USART3 �? pData 中发�? Size 个字节大小的数据�? ESP32C3
  * @note  
  * @param  pData Pointer to data buffer (u8 or u16 data elements).
  * @param  Size  Amount of data elements (u8 or u16) to be received.
  * @retval struct UARTEx_FRAME 
  * @example if(HAL_OK==Transmit_To_ESP32C3(pData, sizeof(pData)));
**/
struct UARTEx_FRAME Transmit_To_ESP32C3(uint8_t *pData, uint16_t Size)
{
	/*
	* 发�?�成功返回：HAL_OK
	* 发�?�失败返回：HAL_BUSY / HAL_ERROR
	*/
	UART3_Frame.tx_Frame_Flag = HAL_UART_Transmit_IT(&huart3, pData, Size);
  return UART3_Frame;
}

/**
  * @brief  使用 USART3_DMA 接收�?帧数据到 ESP32C3
  * @note		static struct UARTEx_FRAME UART3_Frame={
							.new_Frame_Flag=USART3_OLD_FRAME, //是否收到了新�?�? �?:USART3_NEW_FRAME �?:USART3_OLD_FRAME
							.tx_Frame_Flag=HAL_OK,						//是否成功发�?�了新一�? 发�?�成功返回：HAL_OK   发�?�失败返回：HAL_BUSY / HAL_ERROR
							.frame_Length=0,									//新一帧数据长�?
							.pData=USART3_DMA_Rx_Buffer				//缓冲区数组地�?指针
						}; 
  * @param  
  * @retval struct UARTEx_FRAME 
  * @example if(HAL_OK==Transmit_To_ESP32C3(pData, sizeof(pData)));
**/
struct UARTEx_FRAME Receive_From_ESP32C3()
{
	return UART3_Frame;
}

/**
  * @brief  使用 USART3_DMA 接收�?帧数据到 ESP32C3
  * @note		static struct UARTEx_FRAME UART3_Frame={
							.new_Frame_Flag=USART3_OLD_FRAME, //是否收到了新�?�? �?:USART3_NEW_FRAME �?:USART3_OLD_FRAME
							.tx_Frame_Flag=HAL_OK,						//是否成功发�?�了新一�? 发�?�成功返回：HAL_OK   发�?�失败返回：HAL_BUSY / HAL_ERROR
							.frame_Length=0,									//新一帧数据长�?
							.pData=USART3_DMA_Rx_Buffer				//缓冲区数组地�?指针
						}; 
  * @param  
  * @retval struct UARTEx_FRAME 
  * @example if(HAL_OK==Transmit_To_ESP32C3(pData, sizeof(pData)));
**/
struct UARTEx_FRAME clear_UARTx_Frame()
{
	UART3_Frame.new_Frame_Flag=USART3_OLD_FRAME,  //是否收到了新�?�? �?:USART3_NEW_FRAME �?:USART3_OLD_FRAME
	UART3_Frame.tx_Frame_Flag=HAL_OK,					  	//是否成功发�?�了新一�? 发�?�成功返回：HAL_OK   发�?�失败返回：HAL_BUSY / HAL_ERROR
	UART3_Frame.frame_Length=0,									  //新一帧数据长�?
	UART3_Frame.pData=USART3_DMA_Rx_Buffer;		   	//缓冲区数组地�?指针
	
	return UART3_Frame;
}
/* USER CODE END 1 */
