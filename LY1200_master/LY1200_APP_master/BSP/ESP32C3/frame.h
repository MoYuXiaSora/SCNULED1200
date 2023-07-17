#ifndef __FRAME_H
#define __FRAME_H	 
#include "esp32c3.h"  


#define  FrameHead1 0x55
#define  FrameHead2 0xaa

uint32_t GetEspCRC32(uint32_t crc, uint8_t* data, uint32_t size);
uint8_t FrameCheckAndDataSet(uint8_t FrameData[],uint8_t Framelen);
uint8_t CheckSum(uint8_t FrameData[],uint8_t Framelen);
uint8_t Datacmd(uint8_t FrameCmd[]);
uint8_t GetReadyToOTA();  
uint8_t LoadOTAData(uint8_t FrameData[]);
uint8_t LoadFanData(uint8_t FrameData[]);
uint8_t LoadFeatureData(uint8_t FrameData[],int Framelenth);
uint8_t ReturnFrame(uint8_t FrameCmd ,uint8_t DataLenth,uint8_t ResData[],int Framelenth);
uint8_t CheckFinalRes(void);
uint8_t BlueFrameManage(uint8_t FrameData[], uint8_t FrameLen);
void init_CRC32_table(uint32_t CRC32_table[]);

///uint8_t CorrectFrame[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // 
///uint8_t OtaAddressFrame[5] = { 0x00, 0x00, 0x00, 0x00, 0x00 };
///uint8_t WrongFrame[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }; // 
///uint8_t FinalWrongFrame[1] = {0x01};

#endif  