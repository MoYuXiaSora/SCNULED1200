#include <KeyController.hpp>
#include "control_box.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

extern osMessageQueueId_t boxInputQueueHandle;

using namespace touchgfx;
void  KeyController::init ()//初始化
{}
	
extern "C"
{
	extern struct BOX_INPUT box_Data_getQueue;
}

bool KeyController::sample(uint8_t & key)
{	
	  struct BOX_INPUT box_Data_getQueue;
	  struct BOX_INPUT box_Data_Local;	
	
		bool return_Flag;
		//获取消息
    if(osMessageQueueGet(boxInputQueueHandle, (void *)&box_Data_getQueue,NULL,portMAX_DELAY)==osOK){ 
			//获取消息成功
			//box_Data_direction=box_Data_getQueue;
			//对box_Data_...使用 赋值給 key
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
		key= '0' + box_Data_Local.key.value;			
		
    }
	return return_Flag;
}

//#include <KeyController.hpp>
//#include "key.h" 

//using namespace touchgfx;

//void  KeyController::init ()//初始化
//{}

//extern "C"
//{
// struct KEY_TYPE button_scanning();
//}


//	bool KeyController::sample(uint8_t & key) {
//		//采样 是否被按下
//	  struct KEY_TYPE key_driver;
//		key_driver = button_scanning ();
//		if(key_driver.key_state==KEY_STATE_SET ){
//			key=key_driver.key_value;
//			return true;
//	  }	
//		return false;
//	}

