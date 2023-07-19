#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "system_data.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

extern char TouchGFX_Model_Choose;

Model::Model() : modelListener(0),CCT_Light_count(0.0),CCT_Temperature_count(2700)
,badBulb_Temperature(2700),explode_Temperature(2700),firework_Temperature(2700)
,flash_Temperature(2700),lighting_Frequency(2700),paparazzi_Temperature(2700)
,pulse_Temperature(2700),tv_Temperature(2700)//初始化
{
}
//周期性地从消息队列中获取数据，并更新其中某些参数，然后再将更新后的数据放回消息队列中
extern osMessageQueueId_t sysDataQueue_AppHandle;//消息队列

void Model::tick()//每一帧都会自动调用 保存状态数据
{ 
	struct SYS_DATA sys_Data_getQueue;//（void*)&指向需要放入消息队列的消息结构体
		//获取消息
	if(osMessageQueueGet(sysDataQueue_AppHandle, (void *)&sys_Data_getQueue,NULL,portMAX_DELAY)==osOK)
	{ //获取消息成功
		
		switch(TouchGFX_Model_Choose){
			case CCT:{
				sys_Data_getQueue.model_Parament = CCT;
				sys_Data_getQueue.cct_Parament.brightness = (getCCTLight()/100.0);
				sys_Data_getQueue.cct_Parament.color_Temperature = getCCTTemperature();
				sys_Data_getQueue.cct_Parament.cct_Update_Flag = FLAG_TRUE;
				sys_Data_getQueue.driver_Parament.drive_State_Update = driverUPDATE;//发送驱动板命令
			}break;
			case LIGHT_EFFECTS:{
				sys_Data_getQueue.model_Parament = LIGHT_EFFECTS;
				sys_Data_getQueue.LE_Parament.type = getLE_Type();
				sys_Data_getQueue.LE_Parament.brightness = getLE_Light();
				sys_Data_getQueue.LE_Parament.color_Temperature = getLE_Temperature();
				sys_Data_getQueue.LE_Parament.freq = getLE_Frequency();
				sys_Data_getQueue.LE_Parament.le_Update_Flag = FLAG_TRUE;
				sys_Data_getQueue.driver_Parament.drive_State_Update = driverUPDATE;//发送驱动板命令
			}break;
			default:{
				sys_Data_getQueue.model_Parament = MODEL_OFF;
				sys_Data_getQueue.cct_Parament.cct_Update_Flag = FLAG_FALSE;
				sys_Data_getQueue.LE_Parament.le_Update_Flag = FLAG_FALSE;
				sys_Data_getQueue.driver_Parament.drive_State_Update = driverSLEEP;//发送驱动板命令
			}
		}
	  
	}
	
	//放入消息 
	if(osMessageQueuePut(sysDataQueue_AppHandle, &sys_Data_getQueue,0,portMAX_DELAY)==osOK)
	{ //放入消息成功	
		
	}
	
}

