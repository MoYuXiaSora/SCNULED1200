#include "light_effect.h"
#include "rng.h"

static uint8_t candle(struct LIGHTEFFECTS *candle_Parament);

uint8_t lighteffects_Type_Choose(struct LIGHTEFFECTS *lighteffects_Parament_local)
{
	uint8_t return_flag;

	switch(lighteffects_Parament_local->type)
	{
		case CANDLE:/**/
		{
			return_flag = candle(lighteffects_Parament_local);
		}break;
		
		case FIRE:/**/
		{
			
		}break;
		
		case BREATH:
		{
			
		}break;		
		

		case CLOUND:
		{
			
		}break;	

		
		case PAPARAZZI:
		{
			
		}break;		
		

		case FAULT:
		{
			
		}break;		
		

		case TV:
		{
			
		}break;		
		

		default:
		{
			return 0;
		}
	}
	
	return return_flag;
}

static uint8_t candle(struct LIGHTEFFECTS *candle_Parament)
{
	float brightness_Local = candle_Parament->brightness;
	uint16_t color_Temperature_Local = candle_Parament->color_Temperature;
	uint16_t freq_Local = candle_Parament->freq;
	
	float brightness_Set;
	float brightness_Dvalue;
	uint16_t color_Temperature_Set;
	uint16_t color_Temperature_Dvalue;
	float brightness_Out;
	uint16_t color_Temperature_Out;
	

	float brightness_Amplitude= 0.5*brightness_Local;//亮度变化幅值
	uint16_t color_Temperature_Amplitude=1000;//色温变化幅值
	uint16_t random_Scope = 3;//随机数范围 

	switch (candle_Parament->le_State)
	{
		case SETTING:
			/* code */
			{
				//1.设定特效变化范围
				uint8_t rng = random_number(random_Scope); //数值范围0 - 2 
				brightness_Set = brightness_Local - brightness_Amplitude*(rng/(random_Scope-1));
				color_Temperature_Set = color_Temperature_Local - color_Temperature_Amplitude*(rng/(random_Scope-1));

				brightness_Dvalue = (brightness_Set-brightness_Out);
				color_Temperature_Dvalue=(color_Temperature_Set-color_Temperature_Out);
				candle_Parament->le_State = CARRY_OUT;
			}break;

		case CARRY_OUT:
		/* code */
		{
			//2.计算输出数值
			if((abs(brightness_Dvalue)<=0.001)&&(abs(color_Temperature_Dvalue)<=1))
			{
				brightness_Out = brightness_Dvalue*0.01+brightness_Out;
				color_Temperature_Out = color_Temperature_Dvalue*0.01+color_Temperature_Out;
				//输入参数检查
				if(brightness_Out<0) brightness_Out=0;
				else if(brightness_Out>1) brightness_Out=1;
				if(color_Temperature_Out<2700) brightness_Out=2700;
				else if(color_Temperature_Out>6500) brightness_Out=6500;
				light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(candle_Parament->cold_Percentage), &(candle_Parament->warm_Percentage));
			}
			else candle_Parament->le_State = SETTING;	
		}break;

		default:
			break;
	}
	return thisOK;
}