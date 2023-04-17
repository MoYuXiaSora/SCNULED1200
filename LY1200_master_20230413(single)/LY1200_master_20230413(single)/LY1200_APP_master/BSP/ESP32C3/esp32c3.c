#include "esp32c3.h"
#include "usart.h"
#include "main.h"

typedef enum {
    BLE_IDLE = 0,
    BLE_READY,
    BLE_CONNECTED,
    BLE_SPP
} Ble_Service_Status;
static uint8_t ESP32_DMA_Rx_Buffer[256];
Ble_Service_Status BLE_SERVICE_STATUS = BLE_IDLE;

/**
  * @brief  ESP32C3 发送检测函数 
  * @note   在mian.c中调用
  * @param  
  * @retval uint8_t thisOK / thisERROR
  * @example esp32c3_Init();
**/
uint8_t esp32c3_SendCheck(uint8_t *pData, int Size,uint8_t *pCheck)
{
	char *loc;
	uint8_t retry = 5;    //重传次数
	struct UARTEx_FRAME ESP32_Frame_Local={
		.new_Frame_Flag=USART3_OLD_FRAME,
		.tx_Frame_Flag=HAL_OK,
		.frame_Length=0,
		.pData=0
	};	
	while (retry--) {	
	Transmit_To_ESP32C3(pData, Size);		
	soft_Delay(20);
	ESP32_Frame_Local=Receive_From_ESP32C3();
	memcpy(ESP32_DMA_Rx_Buffer,ESP32_Frame_Local.pData,ESP32_Frame_Local.frame_Length);
	if (strstr(ESP32_DMA_Rx_Buffer, pCheck) != 0) {
		memset(ESP32_DMA_Rx_Buffer,0,256);
		ESP32_Frame_Local=clear_UARTx_Frame();
		return thisOK;
	}else{
	ESP32_Frame_Local=clear_UARTx_Frame();
	memset(ESP32_DMA_Rx_Buffer,0,256);	
  continue;}
	ESP32_Frame_Local=clear_UARTx_Frame();
	return thisERROR;
}
}


/**
  * @brief  ESP32C3 初始化函数 
  * @note   在mian.c中调用
  * @param  
  * @retval uint8_t thisOK / thisERROR
  * @example esp32c3_Init();
**/
uint8_t esp32c3_Init()
{
	esp32c3_SendCheck(BLEDEINIT,14,"OK");
	esp32c3_SendCheck(BLEINIT,14,"OK");
	esp32c3_SendCheck(BLESETNAME,20,"OK");
	esp32c3_SendCheck(BLESETMODE,13,"OK");
	esp32c3_SendCheck(BLESYSMSG,13,"OK");
	esp32c3_SendCheck(BLEGATTSSRVCRE,19,"OK");
	esp32c3_SendCheck(BLEGATTSSRVSTART,21,"OK");
	esp32c3_SendCheck(BLEADVSTART,16,"OK");
	esp32c3_SendCheck(BLEADVDATA,46,"OK");
	return thisOK;
}


uint8_t BleService(uint8_t *pData,uint8_t FrameLength){
	if(FrameLength<=1){return 0;}
	memcpy(ESP32_DMA_Rx_Buffer,pData,FrameLength);
	switch (BLE_SERVICE_STATUS) {
		case 0:
			if (FrameLength<=1) {
			}
			break;
		case 1:
			//BlueToothMsgManage(ESP32_DMA_Rx_Buffer, FrameLength);
			break;
		case 2:
			//BlueToothSPPManage(ESP32_DMA_Rx_Buffer, FrameLength);
			break;
		case 3:
			//BlueToothSPPManage(ESP32_DMA_Rx_Buffer, FrameLength);
			break;			
            }
}