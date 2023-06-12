#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "system_data.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

Model::Model() : modelListener(0),CCT_Light_count(15),CCT_Temperature_count(2700)
,CCT_Frequency_count(1),badBulb_Temperature(2700),explode_Temperature(2700)
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
		sys_Data_getQueue.cct_Parament.brightness = (getCCTLight()/100.0);
		sys_Data_getQueue.cct_Parament.color_Temperature = getCCTTemperature();
	}
	
	//放入消息 
	if(osMessageQueuePut(sysDataQueue_AppHandle, &sys_Data_getQueue,0,portMAX_DELAY)==osOK)
	{ //放入消息成功	
		//???外值赋值给CCT_L...
	}
	
}

