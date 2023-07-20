#ifndef ESP32C3_H_
#define ESP32C3_H_

#include "stdio.h"
#include "stdint.h"
#include "math.h"
#include "frame.h"
#include "system_data.h"

//该逻辑遵循CMSIS_RTOS2标识符逻辑
#define thisOK 0
#define thisERROR -1

#define BLEDEINIT "AT+BLEINIT=0\r\n"
#define BLEINIT "AT+BLEINIT=2\r\n"
#define BLESETNAME "AT+BLENAME=\"LY_1200X\"\r\n"
#define BLEGETNAME "AT+BLENAME?\r\n"
#define BLESETMODE "AT+CWMODE=0\r\n"
#define BLESYSMSG "AT+SYSMSG=7\r\n"
#define BLEGATTSSRVCRE 	"AT+BLEGATTSSRVCRE\r\n"
#define BLEGATTSSRVSTART "AT+BLEGATTSSRVSTART\r\n"
#define BLEADVSTART "AT+BLEADVSTART\r\n"
#define BLEADVDATA "AT+BLEADVDATA=\"02010609094c595f3132303058030302A0\"\r\n"
#define BLESPPCFG "AT+BLESPPCFG=1,1,6,1,5\r\n"
#define BLESPP "AT+BLESPP\r\n"
struct ESP32C3
{
    /* data */

	
};

uint8_t BleService(uint8_t *pData,uint8_t FrameLength,struct SYS_DATA *sys_Data_getQueue);
uint8_t esp32c3_Init();
uint8_t esp32c3_SendCheck(uint8_t *pData, int Size,uint8_t *pCheck);
uint8_t BlueToothMsgManage(uint8_t *atstr, uint8_t LenthOfAT);
uint8_t BlueToothSPPManage(uint8_t atstr[], uint8_t LenthOfAT);
uint8_t BleClearSysData(struct SYS_DATA *sys_Data_getQueue);


#endif  // ESP32C3_H_