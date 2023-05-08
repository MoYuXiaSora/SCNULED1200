#include "control_box.h"
#include "tim.h"

static struct KEY key_Parament;
static uint8_t EC11_1_knob_State;
static uint8_t EC11_2_knob_State;

uint8_t knob_Input(struct KNOB *knob_local,uint8_t mapping_Values_Local)
{
	//判断是需要哪个旋钮的数据
	if(knob_local->order_Number==FIRST)
	{//第一个
		encoder_EOF(&htim3,&(knob_local->direction), &(knob_local->variation));
		
		knob_local->key_State = !HAL_GPIO_ReadPin(GPIOC, EC11_1_KEY1_Pin);
		knob_local->knob_State = EC11_1_knob_State;
		
		if((knob_local->mapping_Values)>=0&&(knob_local->mapping_Values)<mapping_Values_Local)
		{
			knob_local->mapping_Values += (knob_local->variation)%mapping_Values_Local;
		}
		
		if((knob_local->mapping_Values)<0)
		{
			knob_local->mapping_Values = mapping_Values_Local-1;
		}
		else if((knob_local->mapping_Values)>=mapping_Values_Local)
		{
			knob_local->mapping_Values = 0;
		}
		
		return thisOK;
	}
	else if(knob_local->order_Number==SECOND)
	{//第二个
		encoder_EOF(&htim4,&(knob_local->direction), &(knob_local->variation));
		
		knob_local->key_State = !HAL_GPIO_ReadPin(GPIOC, EC11_2_KEY0_Pin);
		knob_local->knob_State = EC11_2_knob_State;
		
		if((knob_local->mapping_Values)>=0&&(knob_local->mapping_Values)<mapping_Values_Local)
		{
			knob_local->mapping_Values += (knob_local->variation)%mapping_Values_Local;
		}
		
		if((knob_local->mapping_Values)<0)
		{
			knob_local->mapping_Values = mapping_Values_Local-1;
		}
		else if((knob_local->mapping_Values)>=mapping_Values_Local)
		{
			knob_local->mapping_Values = 0;
		}
		
		return thisOK;
	}
	else return thisERROR;//参数错误

}

//按键外部中断回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
	switch(GPIO_Pin)
	{
		case EC11_1_KEY1_Pin:
		{
			key_Parament.state=KEY_STATE_SET;
			key_Parament.value=KEY1_Pin_SET;
		}break;
		
		case EC11_2_KEY0_Pin:
		{
			key_Parament.state=KEY_STATE_SET;
			key_Parament.value=KEY0_Pin_SET;
		}break;
		
		case MENU_KEY2_Pin:
		{
			key_Parament.state=KEY_STATE_SET;
			key_Parament.value=KEY2_Pin_SET;
		}break;
		
		case CCT_KEY3_Pin:
		{
			key_Parament.state=KEY_STATE_SET;
			key_Parament.value=KEY3_Pin_SET;
		}break;
		
		case EFFECT_KEY6_Pin:
		{
			key_Parament.state=KEY_STATE_SET;
			key_Parament.value=KEY6_Pin_SET;
		}break;
		
		case BACK_KEY10_Pin:
		{
			key_Parament.state=KEY_STATE_SET;
			key_Parament.value=KEY10_Pin_SET;
		}break;
		
//		case :
//		{
//			
//		}break;
//		

		default: break;
	}
}

struct KEY button_scanning()
{
	return key_Parament;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)
	{//第一个
		EC11_1_knob_State=KNOB_STATE_SET;
	}
	
	if(htim->Instance == TIM4)
	{//第二个
		EC11_2_knob_State=KNOB_STATE_SET;
	}
}