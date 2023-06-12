/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
#include "can.h"

/* USER CODE BEGIN 0 */

const int16_t CANTXDATALONG = 8;  //CAN发�?�数组长�??
const int16_t CANRXDATALONG = 8;  //CAN接受数组长度
volatile uint8_t CanTxData[CANTXDATALONG]={0};  //CAN发�?�数�??
volatile uint8_t CanRxData[CANRXDATALONG]={0};  //CAN接受数组

static void MX_CAN1_Filter_Init();
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 3;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_9TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_4TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  MX_CAN1_Filter_Init();
	
	if(HAL_CAN_Start(&hcan1)!=HAL_OK) Error_Handler();
	
	if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING)!=HAL_OK) Error_Handler();
	
  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

static uint8_t MX_CAN1_Tx(char *buf, int length)
{
	CAN_TxHeaderTypeDef TxHeader;
	uint32_t mailBoxId = 0;
	HAL_StatusTypeDef statetypedef = 0;
	
	TxHeader.StdId = 0x001;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.DLC = 8;
	TxHeader.TransmitGlobalTime = DISABLE;
	
	uint8_t can_Tx_Buffer[8]={0};
	
  if (length > CANTXDATALONG)
  {
    /* code */
    
		
		uint8_t tx_Count_Sum=ceil(length/(CANTXDATALONG*1.0));
		
    uint8_t tx_Count=0;
    while (tx_Count_Sum>0)
    {
			memcpy(can_Tx_Buffer,(buf+tx_Count),CANTXDATALONG);
      statetypedef = HAL_CAN_AddTxMessage(&hcan1,&TxHeader,can_Tx_Buffer,&mailBoxId);
	    if(statetypedef!=HAL_OK) return thisERROR;
      tx_Count += CANTXDATALONG;
      tx_Count_Sum--;
    }
  }
  else
  {
    statetypedef = HAL_CAN_AddTxMessage(&hcan1,&TxHeader,buf,&mailBoxId);

	  if(statetypedef!=HAL_OK) return thisERROR;
  }
  
	while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1)==0);
	
	return thisOK;
	
}

static void MX_CAN1_Filter_Init()
{
	CAN_FilterTypeDef sFilterCfg;
	sFilterCfg.FilterActivation = CAN_FILTER_ENABLE;
	sFilterCfg.FilterBank = 0;
	sFilterCfg.FilterMode = CAN_FILTERMODE_IDMASK; 
	sFilterCfg.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterCfg.FilterFIFOAssignment = CAN_FilterFIFO0;
	
	
	sFilterCfg.FilterMaskIdHigh = 0x0000;
	sFilterCfg.FilterMaskIdLow = 0x0000;
	sFilterCfg.FilterIdHigh = 0x0000;
	sFilterCfg.FilterIdLow =0x0000;
	HAL_CAN_ConfigFilter(&hcan1,&sFilterCfg);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef RxHeader;
		
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, CanRxData) != HAL_OK)
	{
		Error_Handler();
	}	

  if (CanRxData[6]==even_parity(CanRxData, 0, 5))//校验成功读取数据
  {
/*     drive_State=CanRxData[1];       //驱动板状态码
    drive_Temperature=CanRxData[2]; //驱动板温�??
    drive_Power=CanRxData[3];       //驱动板功率负�?? */
  }
  
}

uint8_t can_Tx_User(char *tx_Buf, int length)
{
  return MX_CAN1_Tx(tx_Buf, length);

}

uint8_t driver_Data_Format(uint8_t drive_Switch_Local,float cold_Out,float warm_Out,uint8_t fan_Ratio_Local,uint8_t *driver_TxData_Local)
{
    //float cold_Out=0;                   //定义冷色温输出�??0.0-100%
    //float warm_Out=0;                   //定义暖色温输出�??0.0-100%

    uint8_t even_parity_flag = 0;       //偶校验标志位
    uint16_t first_electric_current=0;  //第一路电流�??0000-1000（等效为0.0%-100.0%�??
    uint16_t second_electric_current=0; //第二路电流�??0000-1000（等效为0.0%-100.0%�??
    uint16_t third_electric_current=0;  //第三路电流�??0000-1000（等效为0.0%-100.0%�??
    uint16_t fourth_electric_current=0; //第四路电流�??0000-1000（等效为0.0%-100.0%�??

    uint16_t sum_electric_current=0;    //总的电流�??0000-4000
    uint16_t set_LED_power=0;           //设定的LED功率�??

    //将冷暖输出进行格式转化并赋四路电流数值（这里假设第一路是冷色温）
    first_electric_current=(cold_Out*1000)+0.5;//+0.5实现float类型转换为uint16_t时四舍五�??
    second_electric_current=(cold_Out*1000)+0.5;
    third_electric_current=(warm_Out*1000)+0.5;
    fourth_electric_current=(warm_Out*1000)+0.5;

    //安全�??�??
    //对四路电流输出�?�进行限�??
    if(first_electric_current>1000)    {first_electric_current=1000;}
    else if(first_electric_current<0)  {first_electric_current=0;}
    if(second_electric_current>1000)   {second_electric_current=1000;}
    else if(second_electric_current<0) {second_electric_current=0;}
    if(third_electric_current>1000)    {third_electric_current=1000;}
    else if(third_electric_current<0)  {third_electric_current=0;}
    if(fourth_electric_current>1000)   {fourth_electric_current=1000;}
    else if(fourth_electric_current<0) {fourth_electric_current=0;}

    //计算主控板设定的输出功率
    sum_electric_current=first_electric_current+second_electric_current+third_electric_current+fourth_electric_current;
    //判断LED功率是否超出1200W，超出则不输�??
    if(sum_electric_current>2000){first_electric_current=second_electric_current=third_electric_current=fourth_electric_current=0;}
    set_LED_power= sum_electric_current *2400/(1000*4);

    driver_TxData_Local[0] =0xaa; //第一帧帧�??0xaa
    driver_TxData_Local[1] =(first_electric_current / 256);//第一路恒流输出高八位0x00-0x0a
    driver_TxData_Local[2] =(first_electric_current % 256);//第一路恒流输出低八位0x00-0x63
    driver_TxData_Local[3] =(second_electric_current / 256);//第二路恒流输出高八位0x00-0x0a
    driver_TxData_Local[4] =(second_electric_current % 256);//第二路恒流输出低八位0x00-0x63
    driver_TxData_Local[5] =drive_Switch_Local;//�??0x77�??0x88�??
    even_parity_flag=even_parity(driver_TxData_Local, 0, 5);
    driver_TxData_Local[6] =even_parity_flag;//第一帧前6位偶校验
    driver_TxData_Local[7] =0xfe;//第一帧帧�??

    driver_TxData_Local[8] =0xbb;//第二帧帧�??0xbb
    driver_TxData_Local[9] =(third_electric_current / 256);//第三路恒流输出高八位0x00-0x0a
    driver_TxData_Local[10]=(third_electric_current % 256);//第三路恒流输出低八位0x00-0x63
    driver_TxData_Local[11]=(fourth_electric_current / 256);//第四路恒流输出高八位0x00-0x0a
    driver_TxData_Local[12]=(fourth_electric_current % 256);//第四路恒流输出低八位0x00-0x63
    driver_TxData_Local[13]=fan_Ratio_Local;                //第五路DC0-12V输出0x00-0x64
    even_parity_flag=even_parity(driver_TxData_Local, 8, 13);
    driver_TxData_Local[14]=even_parity_flag;//第二帧前6位偶校验
    driver_TxData_Local[15]=0xff;//第二路帧�??0xff
}

/* USER CODE END 1 */
