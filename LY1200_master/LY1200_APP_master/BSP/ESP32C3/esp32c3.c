#include "esp32c3.h"
#include "usart.h"
#include "main.h"
#include "frame.h"



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
	memset(ESP32_DMA_Rx_Buffer,0,256);
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
//	printf("start to init esp32\r\n");
	BLE_SERVICE_STATUS = BLE_IDLE;
	esp32c3_SendCheck(BLEDEINIT,14,"OK");
	esp32c3_SendCheck(BLEINIT,14,"OK");
	esp32c3_SendCheck(BLESETNAME,23,"OK");
	esp32c3_SendCheck(BLEGETNAME,13,"OK");
	esp32c3_SendCheck(BLESETMODE,13,"OK");
	esp32c3_SendCheck(BLESYSMSG,13,"OK");
	esp32c3_SendCheck(BLEGATTSSRVCRE,19,"OK");
	esp32c3_SendCheck(BLEGATTSSRVSTART,21,"OK");
	esp32c3_SendCheck(BLEADVSTART,16,"OK");
	esp32c3_SendCheck(BLEADVDATA,52,"OK");
	BLE_SERVICE_STATUS = BLE_READY;
	return thisOK;
}


/**
* @brief  ESP32C3 处理蓝牙连接函数，此时蓝牙状态为等待连接状态 
  * @note   在mian.c中调用
  * @param  
  * @retval uint8_t thisOK / thisERROR
  * @example esp32c3_Init();
**/
uint8_t BlueToothMsgManage(uint8_t atstr[], uint8_t LenthOfAT)
{
//	printf("BlueToothMsgManage: \r\n");
//	printf("status+ %x \r\n", BLE_SERVICE_STATUS);
//	printf("framelenth + %x \r\n", LenthOfAT);
//	printf(atstr);
	  char *restr=strstr(atstr, "BLEDISCONN");
    if (strstr(atstr, "BLEDISCONN") != NULL) {
        BLE_SERVICE_STATUS = BLE_IDLE;
        esp32c3_SendCheck("+++",3 , "");
				esp32c3_SendCheck(BLEADVSTART,16,"OK");
				esp32c3_SendCheck(BLEADVDATA,46,"OK");
        BLE_SERVICE_STATUS = BLE_READY;
        return 0;
    } else if (strstr(atstr, "BLECFGMTU:") != NULL || strstr(atstr, "CONNPARAM") != NULL || strstr(atstr, "BLECONN") != NULL) {
        BLE_SERVICE_STATUS = BLE_CONNECTED;
        return 0;
    } else if (strstr(atstr, "WRITE") != NULL) {
        BLE_SERVICE_STATUS = BLE_IDLE;
        esp32c3_SendCheck(BLESPPCFG, 24,"OK");
        esp32c3_SendCheck(BLESPP,11, "OK");
        BLE_SERVICE_STATUS = BLE_SPP;
    } else {
        if (LenthOfAT <= 9) {
            esp32c3_Init();
        }
        return 0;
    }
}


/**
* @brief  ESP32C3 处理蓝牙连接函数，此时蓝牙状态为已连接但未开启透传状态 
  * @note   在mian.c中调用
  * @param  
  * @retval uint8_t thisOK / thisERROR
  * @example esp32c3_Init();
**/
uint8_t BlueToothSPPManage(uint8_t atstr[], uint8_t LenthOfAT)
{
//  printf("BlueToothSPPManage: \r\n");
//	printf("status+ %x \r\n", BLE_SERVICE_STATUS);
//	printf("framelenth + %x \r\n", LenthOfAT);
//	printf(atstr);
    if (strstr(atstr, "BLEDISCONN") != NULL) {
        BLE_SERVICE_STATUS = BLE_IDLE;
        esp32c3_SendCheck("+++",3 , "");
				soft_Delay(500);
				esp32c3_SendCheck(BLEADVSTART,16,"OK");
				esp32c3_SendCheck(BLEADVDATA,46,"OK");
        BLE_SERVICE_STATUS = BLE_READY;
    } else if (strstr(atstr, "WRITE") != NULL) {
        BLE_SERVICE_STATUS = BLE_IDLE;
        esp32c3_SendCheck(BLESPPCFG, 24,"OK");
        esp32c3_SendCheck(BLESPP,11, "OK");
        BLE_SERVICE_STATUS = BLE_SPP;
    }
    return 0;
}

/**
* @brief  ESP32C3 处理蓝牙连接函数，此时蓝牙状态为已连接但未开启透传状态 
  * @note   在mian.c中调用
  * @param  
  * @retval uint8_t thisOK / thisERROR
  * @example esp32c3_Init();
**/
uint8_t BlueToothCmdManage(uint8_t FrameData[], uint8_t FrameLen)
{
	//printf("BlueToothCMDManage: \r\n");
	//printf("status+ %x \r\n", BLE_SERVICE_STATUS);
	//printf("framelenth + %x \r\n", FrameLen);
	//printf(FrameData);
    if (strstr(FrameData, "BLEDISCONN") != NULL) {
        BLE_SERVICE_STATUS = BLE_IDLE;
        esp32c3_SendCheck("+++",3 , "");
			  soft_Delay(500);
				esp32c3_SendCheck(BLEADVSTART,16,"OK");
				esp32c3_SendCheck(BLEADVDATA,46,"OK");
        BLE_SERVICE_STATUS = BLE_READY;
        return 0;
    } else if ((strstr(FrameData, "WRITE") != NULL)) {
        BLE_SERVICE_STATUS = BLE_IDLE;
        esp32c3_SendCheck(BLESPPCFG, 24,"OK");
        esp32c3_SendCheck(BLESPP,11, "OK");
        BLE_SERVICE_STATUS = BLE_SPP;
    } else
		return 0;
}


/**
* @brief  ESP32C3 服务接收函数 
  * @note   在mian.c中调用
  * @param  
  * @retval uint8_t thisOK / thisERROR
  * @example esp32c3_Init();
**/
uint8_t BleService(uint8_t *pData,uint8_t FrameLength,struct SYS_DATA *sys_Data_getQueue){
		struct UARTEx_FRAME ESP32_Frame_Local={
		.new_Frame_Flag=USART3_OLD_FRAME,
		.tx_Frame_Flag=HAL_OK,
		.frame_Length=0,
		.pData=0
	};	
//	printf("status+ %x \r\n", BLE_SERVICE_STATUS);
//	printf("framelenth + %x \r\n", FrameLength);
	if(FrameLength<=1){return 0;}
	while (*pData == 0x00 && FrameLength > 0) {
    pData++;
    FrameLength--;
}
	memcpy(ESP32_DMA_Rx_Buffer,pData,FrameLength);
	switch (BLE_SERVICE_STATUS) {
		case BLE_IDLE:
			if (FrameLength<=1) {
			}
			break;
		case BLE_READY:
			BlueToothMsgManage(ESP32_DMA_Rx_Buffer, FrameLength);
			memset(ESP32_DMA_Rx_Buffer,0,256);
		  ESP32_Frame_Local=clear_UARTx_Frame();
			break;
		case BLE_CONNECTED:
			BlueToothSPPManage(ESP32_DMA_Rx_Buffer, FrameLength);
			memset(ESP32_DMA_Rx_Buffer,0,256);
			ESP32_Frame_Local=clear_UARTx_Frame();
			break;
		case BLE_SPP:			
			BlueFrameManage(ESP32_DMA_Rx_Buffer, FrameLength ,sys_Data_getQueue);
			memset(ESP32_DMA_Rx_Buffer,0,256);
			ESP32_Frame_Local=clear_UARTx_Frame();
			break;			
            }
	return 0;
}


uint8_t BleClearSysData(struct SYS_DATA *sys_Data_getQueue){
	sys_Data_getQueue->cct_Parament.cct_Update_Flag = 0;
	sys_Data_getQueue->LE_Parament.le_Update_Flag = 0;
	return 0 ;
}