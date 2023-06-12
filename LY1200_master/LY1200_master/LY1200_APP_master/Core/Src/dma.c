/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dma.c
  * @brief   This file provides code for the configuration
  *          of all the requested memory to memory DMA transfers.
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
#include "dma.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure DMA                                                              */
/*----------------------------------------------------------------------------*/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * Enable DMA controller clock
  */
void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);

}

/* USER CODE BEGIN 2 */
//矩形缓冲区传�??

void LCD_Start_DMA_Transfer(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint8_t *color)
{
  LCD_Address_Set(x1,y1,x2,y2);
  
  //HAL_DMA_Abort(&hdma_memtomem_dma2_stream0);             //关闭DMA传输 
  //while (HAL_DMA_GetState(DMA2_Stream0) != DISABLE){}     //等待DMA可配�?? 
  //DMA2_Stream0->NDTR = (uint16_t)((x2-x1+1)*(y2-y1+1)*2); //数据传输�??  
  //DMA2_Stream0->PAR  = (uint16_t)color;                   //传输数组 
	//while (HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0,HAL_DMA_FULL_TRANSFER,100) != HAL_OK){}     //等待DMA
	//uint8_t status;
	//status = HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0,HAL_DMA_FULL_TRANSFER,100);
	//HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0,HAL_DMA_FULL_TRANSFER,100);
  //HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint16_t *)color, (uint32_t)(0x6C000000 | 0x0000007E), (x2-x1+1)*(y2-y1+1)*2);	                          //�??启DMA传输  
	//HAL_DMA_Abort(&hdma_memtomem_dma2_stream0);
	//HAL_DMA_Start(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)		
}

/* USER CODE END 2 */

