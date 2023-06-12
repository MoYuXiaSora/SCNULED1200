/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
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
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "algorithm_library.h"

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan1;

/* USER CODE BEGIN Private defines */

//该�?�辑遵循CMSIS_RTOS2标识符�?�辑
#define thisOK 0
#define thisERROR -1
//驱动板状态标识符
#define driverON 0x77
#define driverOFF 0x88
#define driverERROR -1
#define driverOK 0
#define driverTRUE 1
//驱动板参数更新标识符
#define driverSLEEP 0
#define driverUPDATE 1

extern const int16_t CANTXDATALONG;
extern const int16_t CANRXDATALONG;
extern volatile uint8_t CanTxData[];
extern volatile uint8_t CanRxData[];


struct CAN_DATA
{
  /* data */
//  volatile uint8_t CanTxData[];
//  volatile uint8_t CanRxData[];
};

struct DRIVER_DATA
{
  /* data */
  uint8_t drive_State_Update; //驱动更新状�??
  uint8_t drive_Switch;       //驱动板开关机：开0x77，关0x88
  uint8_t drive_Temperature;  //驱动板温度：0x00-0xc8
  uint8_t drive_Power_Ratio;  //驱动板功率负载率�??0x00-0x64
  uint8_t drive_Status_Code;  //电源驱动板状态码 0x77�??机状�?? 0x88关机状�?? 0xXX异常状�??
  uint8_t LED_Temperature;    //灯板温度�??

  //uint8_t drive_TxData[16];   //发�?�给驱动板的数组
  //uint8_t drive_RxData[16];   //从驱动板接受的数�??
};


/* USER CODE END Private defines */

void MX_CAN1_Init(void);

/* USER CODE BEGIN Prototypes */

uint8_t can_Tx_User(char *tx_Buf, int length);
uint8_t driver_Data_Format(uint8_t drive_Switch_Local,float cold_Out,float warm_Out,uint8_t fan_Ratio_Local,uint8_t *driver_TxData_Local);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

