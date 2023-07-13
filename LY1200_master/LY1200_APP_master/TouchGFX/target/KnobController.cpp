#include <KnobController.hpp>
#include "control_box.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

extern osMessageQueueId_t boxInputQueueHandle;

using namespace touchgfx;

void  KnobController::init ()//初始化
{}

extern "C"
{
	struct BOX_INPUT box_Data_getQueue;
}

bool KnobController::sample(uint8_t & key)
{	
	  struct BOX_INPUT box_Data_getQueue;
	  struct BOX_INPUT box_Data_Local;	
		bool return_Flag;
	
		//获取消息
    if(osMessageQueueGet(boxInputQueueHandle, (void *)&box_Data_getQueue,NULL,portMAX_DELAY)==osOK){ 
			//获取消息成功
			box_Data_Local=box_Data_getQueue;
			
			return_Flag = true;
		}
    else
    { //获取消息失败
				return_Flag = false;
    }

    //放入消息 
    if(osMessageQueuePut(boxInputQueueHandle, &box_Data_getQueue,0,portMAX_DELAY)==osOK)
    { //放入消息成功
      
    }
    else
    { //放入消息失败
      
    }	
		
		if(return_Flag==true)
		{
			key = box_Data_Local.knob1.direction;
			
			if(box_Data_Local.knob2.order_Number==SECOND)
			{
				if((box_Data_Local.knob2.direction==1)&&(box_Data_Local.knob2.variation!=0)){
			 key = box_Data_Local.knob2.direction + 2 ;}
			}
		}
				
		return return_Flag;
}
