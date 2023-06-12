#include <KeyController.hpp>
#include "control_box.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "math.h"
#include <iostream>
#define max(x,y) ( x>y?x:y )
#define min(x,y) ( x<y?x:y )
using namespace std;
extern osMessageQueueId_t boxInputQueueHandle;


using namespace touchgfx;

//namespace touchgfx {//定义在命名空间
//	int component_Location=0;//组件位置i
//	int tier_Location=0;//层级位置j
////	int Knob_Pressed=0;//按下标志
//	int Screen_id=00000;//界面标识
//	
//}
uint32_t ScreenMenuNumberGFX = 0;
//uint8_t VariLocation  = 0 ;
void  KeyController::init ()//初始化
{}
	
extern "C"
{
	extern struct BOX_INPUT box_Data_getQueue;
	uint8_t CalVarition(BOX_INPUT *box_Data_gfx ,BOX_INPUT *box_Data_getQueue ,uint8_t CalVariationGFX){
		CalVariationGFX = 0;
		if (box_Data_gfx->knob1.knob_State ==1 && box_Data_gfx->knob1.mapping_Values!=0){ //判断按钮1是否被转 ，如果转了变化幅度不能是0
			if(box_Data_gfx->knob1.direction == 0 && box_Data_gfx->knob1.mapping_Values!=1 && box_Data_gfx->knob1.mapping_Values!=0){ //如果向左转了变化幅度不能是1
				CalVariationGFX|=(0x01<<4); //1按钮向左
				CalVariationGFX|=(15-(box_Data_gfx->knob1.mapping_Values));
			}else{
				CalVariationGFX|=(0x02<<4); //按钮向右
				CalVariationGFX|=min((box_Data_gfx->knob1.mapping_Values),15);
			}
			box_Data_getQueue->knob1.mapping_Values = 0;
			box_Data_getQueue->knob1.direction = 0;
			box_Data_getQueue->knob1.knob_State = 0;
			box_Data_getQueue->knob1.clear_Flag = 1; 
			return CalVariationGFX;
		}
		else if(box_Data_gfx->knob2.knob_State ==1&& box_Data_gfx->knob2.mapping_Values!=0){  //按钮2是否被转，相对位置不是0.
			if(box_Data_gfx->knob2.direction == 0){
				CalVariationGFX|=(0x03<<4);//2按钮向左
				CalVariationGFX|=(15-(box_Data_gfx->knob2.mapping_Values));
			}else{
				CalVariationGFX|=(0x04<<4);//按钮向右
				CalVariationGFX|=min((box_Data_gfx->knob2.mapping_Values),15);
			}
			box_Data_getQueue->knob2.mapping_Values =0;
			box_Data_getQueue->knob2.direction = 0;			
			box_Data_getQueue->knob2.knob_State =0;
			box_Data_getQueue->knob2.clear_Flag =1;
			return CalVariationGFX ;
		}
			else if(box_Data_gfx->key.state == 1){
				switch (box_Data_gfx->key.value){ //其他按键的值
					case KEY0_Pin_SET :
						CalVariationGFX|=(0x05<<4);//KNOB2按下
					  break;
					case KEY1_Pin_SET :
						CalVariationGFX|=(0x06<<4);//KNOB1按下
					  break;
					case KEY2_Pin_SET :
						CalVariationGFX|=(0x07<<4);//menu
					break;
					case KEY3_Pin_SET :
						CalVariationGFX|=(0x08<<4);//cct
					  break;
					case KEY6_Pin_SET :
						CalVariationGFX|=(0x09<<4);//effect
					  break;
					case KEY10_Pin_SET :
						CalVariationGFX|=(0x0a<<4);//back
					  break;
				}
				box_Data_getQueue->key.state = 0;//按键状态复位
				box_Data_getQueue->key.value = 0x0f;//置为不需要的0x0f 
			box_Data_getQueue->key.clear_Flag = 1;
				return CalVariationGFX ;
			}
			else return 0;
	}
}


bool KeyController::sample(uint8_t & key)
{	
	  struct BOX_INPUT box_Data_getQueue;
	  struct BOX_INPUT box_Data_Local;
    int CalVariation;	
	
		bool return_Flag;
		//获取消息
    if(osMessageQueueGet(boxInputQueueHandle, (void *)&box_Data_getQueue,NULL,portMAX_DELAY)==osOK){ 
			//获取消息成功
			//box_Data_direction=box_Data_getQueue;
			//对box_Data_...使用 赋值給 key
			  box_Data_Local=box_Data_getQueue;
   			key = CalVarition(&box_Data_Local, &box_Data_getQueue , CalVariation);
//			box_Data_getQueue.knob1.mapping_Values = 0;
//			box_Data_getQueue.knob1.direction = 0 ;
//			box_Data_getQueue.knob1.knob_State = 0;
//			box_Data_getQueue.knob1.clear_Flag = 1 ;
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
			//CalVariation = 0;
			//KNOB1
		 //if(CalVariation!=0){//variation右转正加，左转负减，不转为0			 
					//component_Location+=CalVariation; //box_Data_Local.knob1.variation;		
          //key= CalVariation;//设组件范围
		 //}		 
		  
       
				
			
//			else if(box_Data_Local.knob1.key_State==KNOB_STATE_SET){ //旋钮被按下
//				
//					tier_Location+=1;//界面层级加一
//				//	Knob_Pressed=1;//旋钮按下标志位
//					box_Data_Local.knob1.key_State=KNOB_STATE_RESET; //按下状态复位	
//    			component_Location=0;//层级改变之后，将组件的位置i清零  	
//			  	key=+10;	 
//				  }
//				// else{
//				//	Knob_Pressed=0;
//				// }
			
//        Screen_id= My_Place();//位置？？

			
				 
				 
		 //KEY236		
//		 if(box_Data_Local.key.value==KEY2_Pin_SET || box_Data_Local.key.value==KEY3_Pin_SET || box_Data_Local.key.value==KEY6_Pin_SET) {
//				Screen_id=00000; //将唯一标识符清零，然后用key=2(menu),key=3(cct),key=6(effect)	
//				key='0'+box_Data_Local.key.value;			
//			}

			
			
			
    }
	return return_Flag;
}


//int My_Place()	
//{	  
//		int tier; //指数运算的值
//	  tier=pow(10,(3-tier_Location));//3为最大层级-1（4-1）
//    Screen_id = Screen_id+key_State*10000+component_Location*tier;	
//	   
//	  
//	  return Screen_id;
//}
