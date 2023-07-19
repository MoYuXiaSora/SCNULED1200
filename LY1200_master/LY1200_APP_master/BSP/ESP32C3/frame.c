#include "main.h"
#include "string.h"
#include "math.h"
#include "frame.h"
#include "esp32c3.h"
#include "usart.h"

 
uint8_t CorrectFrame[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // 正确帧回复
uint8_t OtaAddressFrame[5] = { 0x00, 0x00, 0x00, 0x00, 0x00 }; //OTA地址帧回复
uint8_t WrongFrame[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }; // 错误帧回复
uint8_t FinalWrongFrame[1] = {0x01};
static uint8_t ESP32_ReturnFrame[50];
static uint32_t CRC32_table[256] = { 0 };

typedef struct OtaFile {
		uint32_t FileCRC32; //文件CRC32
	  uint32_t lenth;  //文件总长度    
		uint32_t ExpectedLenth;  //期待收到的包起始地址        
    uint32_t PacketOffSet; //当前已经收到的地址
		uint32_t CRC32_Caled; //计算过后的CRC32
		uint8_t title[10]; 
		uint8_t data[20000];
} ;

volatile static struct OtaFile OtaFile1 ={
	.lenth = 0x00000000,
	.ExpectedLenth = 0x00000000,
	.CRC32_Caled = 0xffffffff,
	.FileCRC32 = 0xffffffff,
	.PacketOffSet = 0x00000000,
};

uint8_t BlueFrameManage(uint8_t FrameData[], uint8_t FrameLen ,struct SYS_DATA *sys_Data_getQueue){
	
    uint16_t FrameHead = ((0x0000 | (FrameData[0] << 8)) | FrameData[1]); 
    uint8_t FrameCmd = FrameData[2];
    if (FrameLen <= 3) {
        return 0;
    }
    if (FrameHead != 0x55aa) {
        BlueToothCmdManage(FrameData,FrameLen);
        return 0;
    }
		
    switch (FrameCmd) {
        case 0x01:
            if (CheckSum(FrameData, FrameLen) != FrameData[FrameLen - 1]) {
                ReturnFrame(0xff, 0x01, WrongFrame,20); // send error msg
                break;
            }
            ReturnFrame(0x01, 0x08, "00010101",20);
            break;
        case 0x02:
            if (CheckSum(FrameData, FrameLen) != FrameData[FrameLen - 1]) {
                ReturnFrame(0xff, 0x01, WrongFrame,20);
                break;
            }
            Datacmd(FrameData);
            break;
        case 0x05:
            if (CheckSum(FrameData, FrameLen) != FrameData[FrameLen - 1]) {
                ReturnFrame(0x05, 0x01, WrongFrame,11);
                // send error msg
                break;
            }
            GetReadyToOTA(FrameData);
            break;
        case 0x06:
            if (CheckSum(FrameData, FrameLen) != FrameData[FrameLen - 1]) {
                ReturnFrame(0x06, 0x01, WrongFrame,11);
                break;
            }
            LoadOTAData(FrameData);
            break;
				case 0x07:
					  if (CheckSum(FrameData, FrameLen) != FrameData[FrameLen - 1]) {
                break;
            }
						LoadFeatureData(FrameData,FrameLen,sys_Data_getQueue);
				case 0x08:
					  if (CheckSum(FrameData, FrameLen) != FrameData[FrameLen - 1]) {
                break;
            }
						LoadFanData(FrameData,sys_Data_getQueue);

        case 0xee:
            if (CheckSum(FrameData, FrameLen) != FrameData[FrameLen - 1]) {
                ReturnFrame(0xff, 0x01, WrongFrame,15);
                // send error msg
                break;
            }
            break;
    }
}

uint8_t Datacmd(uint8_t FrameCmd[])
{
    uint8_t SleepCmd = FrameCmd[5];
    uint16_t HIS_HUE = (0x0000 | (FrameCmd[6] << 8 | FrameCmd[7]));
    uint8_t HIS_S = FrameCmd[8];
    uint8_t HIS_I = FrameCmd[9];
    uint16_t CCT_CT = (0x0000 | (FrameCmd[10] << 8 | FrameCmd[11]));
    uint8_t CCT_I = FrameCmd[12];
    uint8_t FX_MODE = FrameCmd[13];
    uint8_t FX_TYPE = FrameCmd[14];
    uint8_t FX_I = FrameCmd[15];
    uint8_t FX_FREQ = FrameCmd[16];
    //
    return 0;
}

//查表法生成CRC32函数
void init_CRC32_table(uint32_t CRC32_table[])
{
    uint32_t i;
    uint32_t j;
    uint32_t crcTablevalue;
		memset(CRC32_table,0,256);
    for (i = 0; i != 256; i++) {
        crcTablevalue = i;
        for (j = 0; j != 8; j++) {
            if (crcTablevalue & 1) {
                crcTablevalue = (crcTablevalue >> 1) ^ 0xEDB88320;
            } else {
                crcTablevalue >>= 1;
            }
        }
        CRC32_table[i] = crcTablevalue;
    }
}

//分段式生成CRC32函数
uint32_t GetEspCRC32(uint32_t OTAcrc, uint8_t *Crcdata, uint32_t Crcsize)
{
    uint32_t i;
    for (i = 0; i < Crcsize; i++) {
        OTAcrc = ((OTAcrc >> 8) & 0xFFFFFF) ^ CRC32_table[(OTAcrc ^ Crcdata[i]) & 0xFF];
    }
    return OTAcrc;
}

uint8_t GetReadyToOTA(uint8_t FrameData[])
{
    char FileTitle[10] = { "XJBGJ" };
    init_CRC32_table(CRC32_table);
    //memcpy(Otafile1.title, FileTitle, sizeof(FileTitle));
    OtaFile1.lenth = (0x00000000 | (FrameData[5] << 24) | (FrameData[6] << 16) | (FrameData[7] << 8) | (FrameData[8]));
    OtaFile1.FileCRC32 =
        (0x00000000 | (FrameData[9] << 24) | (FrameData[10] << 16) | (FrameData[11] << 8) | (FrameData[12]));
		OtaAddressFrame[4] = (uint8_t)OtaFile1.ExpectedLenth;
		OtaAddressFrame[3] = (uint8_t)(OtaFile1.ExpectedLenth>>8);
		OtaAddressFrame[2] = (uint8_t)(OtaFile1.ExpectedLenth>>16);
		OtaAddressFrame[1] = (uint8_t)(OtaFile1.ExpectedLenth>>24);    
    // memcpy (Otafile1.data,FileData,Otafile1.lenth);
    ReturnFrame(0x05, 0x05, OtaAddressFrame ,11);
		//printf("0x05");
    return 0;
}

uint8_t LoadOTAData(uint8_t FrameData[])
{
		//获取当前偏移
    uint32_t DevicePacketOffset =
        (0x00000000 | (FrameData[5] << 24) | (FrameData[6] << 16) | (FrameData[7] << 8) | (FrameData[8]));
		////获取数据部分长度
    uint8_t DataLen = FrameData[4] - 4;
		if(DevicePacketOffset<OtaFile1.ExpectedLenth){ //说明是小程序重传帧
			  ReturnFrame(0x06, 0x00, CorrectFrame,6);
        return 0;
		}
		else if(DevicePacketOffset==OtaFile1.ExpectedLenth){			
			// //这里替换成拷贝内存						
			OtaFile1.CRC32_Caled = GetEspCRC32(OtaFile1.CRC32_Caled, FrameData + 9, DataLen);
			OtaFile1.PacketOffSet = DevicePacketOffset;
			OtaFile1.ExpectedLenth = DevicePacketOffset + DataLen;
			memcpy(OtaFile1.data + DevicePacketOffset, FrameData + 9, DataLen);
			if (OtaFile1.PacketOffSet == OtaFile1.lenth) { //最后一帧了
				if (~OtaFile1.CRC32_Caled == OtaFile1.FileCRC32) { // 取非计算CRC32
					ReturnFrame(0x06, 0x01, CorrectFrame,7);
					OtaFile1.PacketOffSet = 0x00000000;
          OtaFile1.CRC32_Caled = 0xffffffff;
					OtaFile1.lenth = 0x00000000;
					OtaFile1.ExpectedLenth = 0x00000000;
					//printf("0x06 right");
					soft_Delay(500); //等待DMA发送完毕，测试代码可删除
					memset(OtaFile1.data, 0, 500); //
          
					} else {
						OtaFile1.PacketOffSet = 0x00000000;
            OtaFile1.CRC32_Caled = 0xffffffff;
						OtaFile1.lenth = 0x00000000;
						OtaFile1.ExpectedLenth = 0x00000000;
            memset(OtaFile1.data, 0, 500); //
						ReturnFrame(0x06, 0x01, FinalWrongFrame,7);
					}
					return 0;
			}
			ReturnFrame(0x06, 0x00, CorrectFrame,6);
			return 0 ;
		}
		return 0;
	}
//	  else if (DevicePacketOffset > Otafile1.PacketOffSet) {
//			  Otafile1.PacketOffSet = DevicePacketOffset;
//        memcpy(Otafile1.data + DevicePacketOffset, FrameData + 9, DataLen);
//        Otafile1.CRC32_Caled = GetCRC32(Otafile1.CRC32_Caled, FrameData + 9, DataLen);
//			  Otafile1.OtaAddress = DevicePacketOffset + DataLen;
//        if (Otafile1.PacketOffSet == Otafile1.lenth) { //最后一帧了
//            if (~Otafile1.CRC32_Caled == Otafile1.FileCRC32) { // 取非计算CRC32
//                ReturnFrame(0x06, 0x01, CorrectFrame,7);
//							  Otafile1.PacketOffSet = 0x00000000;
//                Otafile1.CRC32_Caled = 0xffffffff;
//							  Otafile1.OtaAddress = 0x00000000;
//                //u1_printf("0x06");
//            } else {
//							Otafile1.PacketOffSet = 0x00000000;
//              Otafile1.CRC32_Caled = 0xffffffff;
//							Otafile1.OtaAddress = 0x00000000;
//            	memset(Otafile1.data, 0, 60000); //
//							ReturnFrame(0x06, 0x01, FinalWrongFrame,7);
//            }
//            return 0;
//        }
//        ReturnFrame(0x06, 0x00, CorrectFrame,6);
//        return 0;
//    }
//	  if (DevicePacketOffset==0 && DevicePacketOffset == Otafile1.PacketOffSet  ) { // 
//			  Otafile1.PacketOffSet = DevicePacketOffset;
//			  memcpy(Otafile1.data + DevicePacketOffset, FrameData + 9, DataLen);
//			  //Otafile1.CRC32_Caled = GetCRC32(Otafile1.CRC32_Caled, FrameData + 9, DataLen);
//			  Otafile1.OtaAddress += 0x40;
//        ReturnFrame(0x06, 0x00, CorrectFrame,6);
//        return 0;
//    }
//    if (DevicePacketOffset <= Otafile1.PacketOffSet) { // 
//        ReturnFrame(0x06, 0x00, CorrectFrame,6);
//        return 0;
//    }
//    return 0;

uint8_t LoadFanData(uint8_t FrameData[] ,struct SYS_DATA *sys_Data_getQueue)
{
	sys_Data_getQueue->control_Parament = BLE;
	  sys_Data_getQueue->fan_Parament.fan_Ratio = FrameData[6];
    return 0;
}

uint8_t LoadCCTData(uint8_t FrameData[] ,struct SYS_DATA *sys_Data_getQueue)
{
	sys_Data_getQueue->control_Parament = BLE;
	sys_Data_getQueue->model_Parament = CCT ;
  sys_Data_getQueue->cct_Parament.brightness = ((float)FrameData[10] / 10) + FrameData[9];
	sys_Data_getQueue->cct_Parament.color_Temperature = (0x0000|(FrameData[7]<<8)|((FrameData[8])));
	sys_Data_getQueue->cct_Parament.curve = FrameData[11]; //这里需要修改
	sys_Data_getQueue->cct_Parament.cct_Update_Flag = FLAG_TRUE;
	return 0 ;
}

uint8_t LoadLightEffectData(uint8_t FrameData[] ,struct SYS_DATA *sys_Data_getQueue)
{
	uint8_t BLEFXType = FrameData[7];
	double_t BLEFX_brightness = ((float)FrameData[9] / 10) + FrameData[8];
	uint16_t BLEFXColorTemperature = (0x0000|(FrameData[10]<<8)|((FrameData[11])));
	uint8_t BLEFXFREQ = FrameData[12];
	sys_Data_getQueue->control_Parament = BLE;
	sys_Data_getQueue->model_Parament = LIGHT_EFFECTS;
	sys_Data_getQueue->LE_Parament.type = BLEFXType;
	sys_Data_getQueue->LE_Parament.le_State = SETTING;
	sys_Data_getQueue->LE_Parament.le_Update_Flag = FLAG_TRUE;
	sys_Data_getQueue->LE_Parament.brightness = BLEFX_brightness;
	sys_Data_getQueue->LE_Parament.color_Temperature = BLEFXColorTemperature;
	sys_Data_getQueue->LE_Parament.freq = BLEFXFREQ;
	return 0 ;
}
uint8_t LoadFeatureData(uint8_t FrameData[] , int FrameLen ,struct SYS_DATA *sys_Data_getQueue)
{
	if(FrameLen>=15){ //测试是否粘包
		return 0 ;
	}
	if(FrameData[5]==0x01){
		//开启睡眠
		return 0;
	}
	else {
		switch (FrameData[6]) {
			case 0x00 :
				LoadCCTData(FrameData,sys_Data_getQueue);
			break;
			case 0x01 :
				LoadLightEffectData(FrameData ,sys_Data_getQueue);
			break;
		}
	}
	return 0 ;
}
//计算每一帧的校验和
uint8_t CheckSum(uint8_t FrameData[], uint8_t Framelen)
{
    uint16_t FrameSum = 0x0000;
    int res;
    for (res = 0; res <= Framelen - 2; res++) {
        FrameSum += FrameData[res];
    }
    return FrameSum % 256;
}

//向ESP32返回对应的帧
uint8_t ReturnFrame(uint8_t FrameCmd, uint8_t DataLenth, uint8_t *ResData , int FrameLenth )
{
    int res;
    uint16_t FrameSum = 0x0000;
    memset(ESP32_ReturnFrame, 0, 50);
    ESP32_ReturnFrame[0] = 0x55;
    ESP32_ReturnFrame[1] = 0xaa;
    ESP32_ReturnFrame[2] = FrameCmd;
    ESP32_ReturnFrame[3] = 0x00;
    ESP32_ReturnFrame[4] = DataLenth;
    memcpy(ESP32_ReturnFrame + 5, ResData, DataLenth);
    for (res = 0; res < FrameLenth - 1; res++) {
        FrameSum += ESP32_ReturnFrame[res];
    }
    ESP32_ReturnFrame[FrameLenth-1] = (FrameSum) % 256;
    //esp32c3_SendCheck(BLEDEINIT,14,"OK");
		//Transmit_To_ESP32C3(BLEDEINIT,14);
		Transmit_To_ESP32C3((uint8_t*)ESP32_ReturnFrame, (uint16_t)FrameLenth);
    return 0;
}

