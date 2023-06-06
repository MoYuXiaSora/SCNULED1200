/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "system_data.h"
#include "algorithm_library.h"
#include "bsp.h"

#include "usart.h"

#include "cct.h"
#include "light_effect.h"

#include "app_touchgfx.h"
#include "TouchGFX_User.h"

#include "test_array.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
UBaseType_t test_info[10];
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for cctTask */
osThreadId_t cctTaskHandle;
const osThreadAttr_t cctTask_attributes = {
  .name = "cctTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for canTask */
osThreadId_t canTaskHandle;
const osThreadAttr_t canTask_attributes = {
  .name = "canTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for lightEffectTask */
osThreadId_t lightEffectTaskHandle;
const osThreadAttr_t lightEffectTask_attributes = {
  .name = "lightEffectTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for menuTask */
osThreadId_t menuTaskHandle;
const osThreadAttr_t menuTask_attributes = {
  .name = "menuTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for GUI_Task */
osThreadId_t GUI_TaskHandle;
const osThreadAttr_t GUI_Task_attributes = {
  .name = "GUI_Task",
  .stack_size = 4096 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for lcdTransferTask */
osThreadId_t lcdTransferTaskHandle;
const osThreadAttr_t lcdTransferTask_attributes = {
  .name = "lcdTransferTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for inputTask */
osThreadId_t inputTaskHandle;
const osThreadAttr_t inputTask_attributes = {
  .name = "inputTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for testTask */
osThreadId_t testTaskHandle;
const osThreadAttr_t testTask_attributes = {
  .name = "testTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for wirelessTask */
osThreadId_t wirelessTaskHandle;
const osThreadAttr_t wirelessTask_attributes = {
  .name = "wirelessTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for sysDataQueue_App */
osMessageQueueId_t sysDataQueue_AppHandle;
const osMessageQueueAttr_t sysDataQueue_App_attributes = {
  .name = "sysDataQueue_App"
};
/* Definitions for xQueueLCD */
osMessageQueueId_t xQueueLCDHandle;
const osMessageQueueAttr_t xQueueLCD_attributes = {
  .name = "xQueueLCD"
};
/* Definitions for boxInputQueue */
osMessageQueueId_t boxInputQueueHandle;
const osMessageQueueAttr_t boxInputQueue_attributes = {
  .name = "boxInputQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void cctTask_Entry_App(void *argument);
void canTask_Entry(void *argument);
void lightEffectTask_Entry(void *argument);
void menuTask_Entry(void *argument);
extern void TouchGFX_Task(void *argument);
void lcdTransferTask_Entry(void *argument);
void inputTask_Entry(void *argument);
void testTask_Entry(void *argument);
void wirelessTask_Entry(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of sysDataQueue_App */
  sysDataQueue_AppHandle = osMessageQueueNew (1, sizeof(struct SYS_DATA), &sysDataQueue_App_attributes);

  /* creation of xQueueLCD */
  xQueueLCDHandle = osMessageQueueNew (16, sizeof(_st_lcd), &xQueueLCD_attributes);

  /* creation of boxInputQueue */
  boxInputQueueHandle = osMessageQueueNew (2, sizeof(struct BOX_INPUT), &boxInputQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of cctTask */
  cctTaskHandle = osThreadNew(cctTask_Entry_App, NULL, &cctTask_attributes);

  /* creation of canTask */
  canTaskHandle = osThreadNew(canTask_Entry, NULL, &canTask_attributes);

  /* creation of lightEffectTask */
  lightEffectTaskHandle = osThreadNew(lightEffectTask_Entry, NULL, &lightEffectTask_attributes);

  /* creation of menuTask */
  menuTaskHandle = osThreadNew(menuTask_Entry, NULL, &menuTask_attributes);

  /* creation of GUI_Task */
  GUI_TaskHandle = osThreadNew(TouchGFX_Task, NULL, &GUI_Task_attributes);

  /* creation of lcdTransferTask */
  lcdTransferTaskHandle = osThreadNew(lcdTransferTask_Entry, NULL, &lcdTransferTask_attributes);

  /* creation of inputTask */
  inputTaskHandle = osThreadNew(inputTask_Entry, NULL, &inputTask_attributes);

  /* creation of testTask */
  testTaskHandle = osThreadNew(testTask_Entry, NULL, &testTask_attributes);

  /* creation of wirelessTask */
  wirelessTaskHandle = osThreadNew(wirelessTask_Entry, NULL, &wirelessTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */

  /* Input Data : sys_Data_getQueue.cct_Parament
   * Onput Data : 
                   */

  struct SYS_DATA sys_Data_getQueue={
    
  };
	struct BOX_INPUT box_Data_getQueue={
		
	};

  //初始化系统参�??
  if(system_Data_Init()==osOK)
  {
    //系统参数初始化成�??

  }
  else
  {
    //系统参数初始化失�??

  }

  for(;;)
  {
    //获取消息
    if(osMessageQueueGet(sysDataQueue_AppHandle, (void *)&sys_Data_getQueue,NULL,portMAX_DELAY)==osOK)
    { //获取消息成功
      
    }
    else
    { //获取消息失败
      
    }

    //放入消息 
    if(osMessageQueuePut(sysDataQueue_AppHandle, &sys_Data_getQueue,0,portMAX_DELAY)==osOK)
    { //放入消息成功
      
    }
    else
    { //放入消息失败
      
    }
    
				//获取消息
    if(osMessageQueueGet(boxInputQueueHandle, (void *)&box_Data_getQueue,NULL,portMAX_DELAY)==osOK)
    { //获取消息成功

    }
    else
    { //获取消息失败
      
    }

    //放入消息 
    if(osMessageQueuePut(boxInputQueueHandle, &box_Data_getQueue,0,portMAX_DELAY)==osOK)
    { //放入消息成功
      
    }
    else
    { //放入消息失败
      
    }
		
		
		
    
    HAL_Delay(100);//硬延时等�??100ms 系统初始�??
    
    //while(osThreadTerminate(defaultTaskHandle)!=osOK);//终止StartDefaultTask线程
		
		test_info[0] = uxTaskGetStackHighWaterMark(NULL);
		
		osThreadExit();
		
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_cctTask_Entry_App */
/**
* @brief Function implementing the cctTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_cctTask_Entry_App */
void cctTask_Entry_App(void *argument)
{
  /* USER CODE BEGIN cctTask_Entry_App */
  /* Infinite loop */

  /* Input Data : sys_Data_getQueue.cct_Parament
   * Onput Data : sys_Data_getQueue.cct_Parament.cold_Percentage
                  sys_Data_getQueue.cct_Parament.cold_Percentage */

   struct SYS_DATA sys_Data_getQueue={
    .cct_Parament={ 0, 4600, S_CURVE, 0, 0}
  };

  for(;;)
  {
    //获取消息
    if(osMessageQueueGet(sysDataQueue_AppHandle, (void *)&sys_Data_getQueue,NULL,portMAX_DELAY)==osOK)
    { //获取消息成功
      //运行 cct_User 将输入的亮度和色温计算为应输出的冷�?�暖两�?�道比例
      cct_User(&(sys_Data_getQueue.cct_Parament),&(sys_Data_getQueue.cct_Parament.cold_Percentage), &(sys_Data_getQueue.cct_Parament.warm_Percentage));
    }

    //放入消息 
    if(osMessageQueuePut(sysDataQueue_AppHandle, &sys_Data_getQueue,0,portMAX_DELAY)==osOK)
    { //放入消息成功
      
    }
		
		test_info[1] = uxTaskGetStackHighWaterMark(NULL);
		
    osDelay(1);
  }
  /* USER CODE END cctTask_Entry_App */
}

/* USER CODE BEGIN Header_canTask_Entry */
/**
* @brief Function implementing the canTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_canTask_Entry */
void canTask_Entry(void *argument)
{
  /* USER CODE BEGIN canTask_Entry */
  /* Infinite loop */
  struct SYS_DATA sys_Data_getQueue={
    .cct_Parament={ 0, 4600, S_CURVE, 0, 0},
    .driver_Parament={ driverTRUE, 0x88},
    .fan_Parament=0,
  };

  #define DRIVER_TXDATA_LENGTH 16//驱动板发送数据长�??
  uint8_t driver_TxData[DRIVER_TXDATA_LENGTH]={0};//驱动板发送数据缓�??

  for(;;)
  {
    //获取消息
    if (osMessageQueueGet(sysDataQueue_AppHandle, (void *)&sys_Data_getQueue,NULL,portMAX_DELAY)==osOK)
    { //获取消息成功
      //按照与驱动板协议，将驱动�??�??数据进行CAN格式化编�??
      switch (sys_Data_getQueue.model_Parament)
      {
        case CCT:{
          /* code */
          driver_Data_Format(sys_Data_getQueue.driver_Parament.drive_Switch,sys_Data_getQueue.cct_Parament.cold_Percentage,sys_Data_getQueue.cct_Parament.warm_Percentage,sys_Data_getQueue.fan_Parament.fan_Ratio,driver_TxData);
        }break;
        
       case LIGHT_EFFECTS:{
          /* code */
          driver_Data_Format(sys_Data_getQueue.driver_Parament.drive_Switch,sys_Data_getQueue.LE_Parament.cold_Percentage,sys_Data_getQueue.LE_Parament.warm_Percentage,sys_Data_getQueue.fan_Parament.fan_Ratio,driver_TxData);
        }break;

        default:
          break;
      }
      //将CAN发�?�数组中的数据进行发�??
      can_Tx_User(driver_TxData, DRIVER_TXDATA_LENGTH);
    }
    //放入消息
    if(osMessageQueuePut(sysDataQueue_AppHandle, &sys_Data_getQueue,0,portMAX_DELAY)==osOK)
    { //放入消息成功

    }

		test_info[2] = uxTaskGetStackHighWaterMark(NULL);
		
    osDelay(1);
  }
  /* USER CODE END canTask_Entry */
}

/* USER CODE BEGIN Header_lightEffectTask_Entry */
/**
* @brief Function implementing the lightEffectTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_lightEffectTask_Entry */
void lightEffectTask_Entry(void *argument)
{
  /* USER CODE BEGIN lightEffectTask_Entry */
  /* Infinite loop */

  /* Input Data : sys_Data_getQueue.LE_Parament
   * Onput Data : sys_Data_getQueue.LE_Parament.cold_Percentage
                  sys_Data_getQueue.LE_Parament.warm_Percentage */

   struct SYS_DATA sys_Data_getQueue={
    .LE_Parament={ CANDLE, SETTING, 0, 4600, 5, 0, 0}//{类型，状态，亮度，色温，频率，冷通道结果，暖通道结果};
  };

  for(;;)
  {
    //获取消息
    if(osMessageQueueGet(sysDataQueue_AppHandle, (void *)&sys_Data_getQueue,NULL,portMAX_DELAY)==osOK)
    { //获取消息成功
      //运行 lighteffects_Type_Choose 将输入的特效参数计算为应输出的冷、暖两�?�道比例

      lighteffects_Type_Choose(&sys_Data_getQueue.LE_Parament);

    }

    //放入消息 
    if(osMessageQueuePut(sysDataQueue_AppHandle, &sys_Data_getQueue,0,portMAX_DELAY)==osOK)
    { //放入消息成功
      
    }
		
		test_info[3] = uxTaskGetStackHighWaterMark(NULL);
		
    osDelay(1);
		
		
  }


  /* USER CODE END lightEffectTask_Entry */
}

/* USER CODE BEGIN Header_menuTask_Entry */
/**
* @brief Function implementing the menuTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_menuTask_Entry */
void menuTask_Entry(void *argument)
{
  /* USER CODE BEGIN menuTask_Entry */
	
	struct SYS_DATA sys_Data_getQueue={
    
  };
	
  /* Infinite loop */
  for(;;)
  {
		//获取消息
    if(osMessageQueueGet(sysDataQueue_AppHandle, (void *)&sys_Data_getQueue,NULL,portMAX_DELAY)==osOK)
    { //获取消息成功
			
//			//对数值进行处�??
//			sys_Data_getQueue.cct_Parament.brightness+=(knob_Data1.variation)/1000.0;
//			sys_Data_getQueue.cct_Parament.color_Temperature+=(knob_Data2.variation)/1000.0;
    }
		
    //放入消息 
    if(osMessageQueuePut(sysDataQueue_AppHandle, &sys_Data_getQueue,0,portMAX_DELAY)==osOK)
    { //放入消息成功
      
    }
		test_info[4] = uxTaskGetStackHighWaterMark(NULL);
    osDelay(1);
  }
  /* USER CODE END menuTask_Entry */
}

/* USER CODE BEGIN Header_lcdTransferTask_Entry */
/**
* @brief Function implementing the lcdTransferTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_lcdTransferTask_Entry */
void lcdTransferTask_Entry(void *argument)
{
  /* USER CODE BEGIN lcdTransferTask_Entry */
  /* Infinite loop */
  for(;;)
  {
		//lcd_update();//将渲染的图像刷新到LCD屏幕�??
		
		test_info[5] = uxTaskGetStackHighWaterMark(NULL);
		
    osDelay(1);
  }
  /* USER CODE END lcdTransferTask_Entry */
}

/* USER CODE BEGIN Header_inputTask_Entry */
/**
* @brief Function implementing the inputTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_inputTask_Entry */
void inputTask_Entry(void *argument)
{
  /* USER CODE BEGIN inputTask_Entry */
	
struct BOX_INPUT box_Data_getQueue={
			.key={
				.state=KEY_STATE_RESET,
				.value=NOKEY_VALUE,
				.clear_Flag = CLEAR_FLAG_OFF,
			},
			.knob1={
				.order_Number=FIRST,
				.direction=RIGHT,
				.variation=0,
				.mapping_Values=0,
				.key_State=KEY_STATE_RESET,
				.knob_State=KNOB_STATE_RESET,
				.clear_Flag=CLEAR_FLAG_OFF,
			},
			.knob2={
				.order_Number=SECOND,
				.direction=RIGHT,
				.variation=0,
				.mapping_Values=0,
				.key_State=KEY_STATE_RESET,
				.knob_State=KNOB_STATE_RESET,
				.clear_Flag=CLEAR_FLAG_OFF,
			},
	};

  /* Infinite loop */
  for(;;)
  {
		//获取消息
    if(osMessageQueueGet(boxInputQueueHandle, (void *)&box_Data_getQueue,NULL,portMAX_DELAY)==osOK)
    { //获取消息成功
      if(knob_Input(&(box_Data_getQueue.knob1), 15)==thisOK)
			{

			}
			if(knob_Input(&(box_Data_getQueue.knob2), 15)==thisOK)
			{

			}
			box_Data_getQueue.key = button_scanning(box_Data_getQueue.key.clear_Flag);
    }
    else
    { //获取消息失败
      
    }

    //放入消息 
    if(osMessageQueuePut(boxInputQueueHandle, &box_Data_getQueue,0,portMAX_DELAY)==osOK)
    { //放入消息成功
      
    }
    else
    { //放入消息失败
      
    }
		test_info[6] = uxTaskGetStackHighWaterMark(NULL);
    osDelay(1);
  }
  /* USER CODE END inputTask_Entry */
}

/* USER CODE BEGIN Header_testTask_Entry */
/**
* @brief Function implementing the testTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_testTask_Entry */
void testTask_Entry(void *argument)
{
  /* USER CODE BEGIN testTask_Entry */
  /* Infinite loop */
  for(;;)
  {
		uint8_t i=0;
		uint8_t j=1;
		//printf("Event Recorder Test! \n");
//		EventStartG(0);
		EventStartA(0);
		//EventRecordItem
		//uint8_t i = USART3_DMA_Rx_Buffer[0];
		//测试spi flash
		//uint8_t ID_test[2]={0x01,0x02};
		//Receive_From_ESP32C3(ID_test, 2);
//		extern uint8_t rx_array[8];
//		Receive_From_ESP32C3(rx_array, sizeof(rx_array));
//		extern uint8_t rx_array[8];
//		extern UART_HandleTypeDef huart3;
//		extern DMA_HandleTypeDef hdma_usart3_rx;
//		extern DMA_HandleTypeDef hdma_usart3_tx;
//		HAL_UARTEx_ReceiveToIdle_DMA(&huart3,rx_array,sizeof(rx_array));
//		extern volatile uint8_t new_Frame_Flag;
//		if(new_Frame_Flag==1)
//		{
//			Transmit_To_ESP32C3(ID_test, sizeof(ID_test));
//			
//			new_Frame_Flag=0;
//		}

//		if(Receive_From_ESP32C3(rx_array, sizeof(rx_array))==HAL_OK)
//		{
//			Transmit_To_ESP32C3(ID_test, sizeof(ID_test));
//		}
		
//		uint8_t rx[10];
		//BSP_W25Qx_Read_ID(ID_test);//读取ID
	
//		uint8_t aa = 0;
//		uint8_t iii=1;
//		if(iii<0) aa=test_array[1];
		
		//初始化写入数�?
//		for(uint16_t i=0;i<SECTOR_SIZE;i++)
//		{
//			tx[i]=i;
//		}
		
		
		//操作扇区
//		uint32_t j=0x00;
//		do
//		{
//			//擦除扇区
//			//BSP_W25Qx_Erase_Block(j);
//			//写扇�?
//			//BSP_W25Qx_Write(tx, j,sizeof(tx)/sizeof(tx[0]));
//			//读取扇区
//			BSP_W25Qx_Read(rx, j, sizeof(rx)/sizeof(rx[0]));
//			
////			for(uint16_t k=0;k<SECTOR_SIZE;k++)
////			{
//////				if(rx[k]==(k%256))
//////				{
//////					//rx[k]=0;
//////				}
//////				else { flag=0xFF; break;}
////			}
//			
//			j=j+SECTOR_SIZE;
//		}while(j<FLASH_SIZE);
//	   
//		volatile uint8_t testi;
//		testi=test_array[0];
		

//		BSP_W25Qx_Erase_Block(0x00);
//		
//		BSP_W25Qx_Read(rx, 0x00, sizeof(rx)/sizeof(rx[0]));
//		
//		for(uint16_t i=0;i<4*1024;i++)
//		{
//				tx[i]=i;
//			
//		}
//		
//		BSP_W25Qx_Write(tx, 0x00,sizeof(tx)/sizeof(tx[0]));
//		
//		BSP_W25Qx_Read(rx, 0x00, sizeof(rx)/sizeof(rx[0]));
		

 
// //测试外置sram
//		uint8_t *externalRAM = 0x60000000;
//		const uint32_t size = 1*1024*1024;
//		
//		uint8_t *bit_RAM = 0x6004B008;
//		uint8_t *frame_RAM = 0x60000000;
//		
//		uint8_t test_ii;
//		
//		//1.读取FLASH
//		BSP_W25Qx_Read((uint8_t *)0x6004B008, 0x00000000, 0x0003FC00);
//		//比对位图缓冲区与FLASH内容是否�?�?
//		for(uint32_t numBytes_i = 0;numBytes_i<0x0003FC00;numBytes_i++)
//		{
//			BSP_W25Qx_Read(&test_ii, numBytes_i, 1);
//			if(test_ii !=bit_RAM[numBytes_i]) 
//			{
//				break;
//			}
//		}
//		
//		//2.将位图缓冲区数据写入至渲染区
//		for(uint32_t numBytes_i = 0;numBytes_i<0x0003FC00;numBytes_i++)
//		{
//			frame_RAM[numBytes_i]=bit_RAM[numBytes_i];
//		}
//		//3.比对位图缓冲区与FLASH内容是否�?�?
//		for(uint32_t numBytes_i = 0;numBytes_i<0x0003FC00;numBytes_i++)
//		{
//			BSP_W25Qx_Read(&test_ii, numBytes_i, 1);
//			if(test_ii !=bit_RAM[numBytes_i]) 
//			{
//				break;
//			}
//		}

		
		/*
		//外置sram存储全局变量 写入spiflash 测试 两个数组放全�?变量�?
//		__attribute__((section(".RAM3"))) uint8_t rx[4*1024]={1,1,1,1,1,1,1,1,1,1};
//		__attribute__((section(".RAM3"))) uint8_t tx[4*1024];
		uint8_t ID_test[2]={0};
//		uint8_t rx[10]={1,1,1,1,1,1,1,1,1,1};
		BSP_W25Qx_Read_ID(ID_test);//读取ID
		
		uint8_t aa = test_array[1];
		//读取扇区
	  BSP_W25Qx_Read(rx, 0x00, sizeof(rx)/sizeof(rx[0]));
		
		BSP_W25Qx_Erase_Block(0x00);
		
		BSP_W25Qx_Read(rx, 0x00, sizeof(rx)/sizeof(rx[0]));
		
		for(uint16_t i=0;i<4*1024;i++)
		{
				tx[i]=i;
			
		}
		
		BSP_W25Qx_Write(tx, 0x00,sizeof(tx)/sizeof(tx[0]));
		
		BSP_W25Qx_Read(rx, 0x00, sizeof(rx)/sizeof(rx[0]));
		*/
		
//		for (i = 1; i < 4096+1; i++)
//    {
//        g_test_buffer[i-1] = (i);         /* 预存测试数据 */
//    }

		test_info[7] = uxTaskGetStackHighWaterMark(NULL);
    osDelay(100);
		EventStopA(0);
  }
  /* USER CODE END testTask_Entry */
}

/* USER CODE BEGIN Header_wirelessTask_Entry */
/**
* @brief Function implementing the wirelessTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_wirelessTask_Entry */
void wirelessTask_Entry(void *argument)
{
  /* USER CODE BEGIN wirelessTask_Entry */
	
	struct SYS_DATA sys_Data_getQueue={
    
  };
	
  /* Infinite loop */
  for(;;)
  {
		//获取消息
    if(osMessageQueueGet(sysDataQueue_AppHandle, (void *)&sys_Data_getQueue,NULL,portMAX_DELAY)==osOK)
    {//获取消息成功
			
			uint8_t test_array[1]={0x00};//测试数组用完即删�?
			struct UARTEx_FRAME UART3_Frame_Local={
				.new_Frame_Flag=USART3_OLD_FRAME,
				.tx_Frame_Flag=HAL_OK,
				.frame_Length=0,
				.pData=0
			};
			UART3_Frame_Local=Receive_From_ESP32C3();
			if(USART3_NEW_FRAME==UART3_Frame_Local.new_Frame_Flag)
			{//新一帧接收成�?
				//发�?�接收到的数�?
				Transmit_To_ESP32C3(UART3_Frame_Local.pData, UART3_Frame_Local.frame_Length);
				//清除接收标志
				UART3_Frame_Local=clear_UARTx_Frame();
				if(USART3_OLD_FRAME==UART3_Frame_Local.new_Frame_Flag)
				{//清除接收标志成功
					
				}
				else
				{//清除接收标志失败
					
				}
			}
			else
			{//新一帧接收失�? �? 无新数据
				 Transmit_To_ESP32C3(test_array, sizeof(test_array)/sizeof(test_array[0]));
			}

    }
		else
		{//获取消息失败
			
		}
		
    //放入消息 
    if(osMessageQueuePut(sysDataQueue_AppHandle, &sys_Data_getQueue,0,portMAX_DELAY)==osOK)
    {//放入消息成功
      
    }
		else
		{//放入消息失败
			
		}			
		
    osDelay(100);
  }
  /* USER CODE END wirelessTask_Entry */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

