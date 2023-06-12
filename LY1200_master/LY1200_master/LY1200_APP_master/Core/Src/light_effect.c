#include "cmsis_os.h"
#include "light_effect.h"
#include "rng.h"

static uint8_t candle(struct LIGHTEFFECTS *candle_Parament);
static uint8_t breath(struct LIGHTEFFECTS *breath_Parament);
static uint8_t cloud(struct LIGHTEFFECTS *breath_Parament);

uint8_t lighteffects_Type_Choose(struct LIGHTEFFECTS *lighteffects_Parament_local)
{
	uint8_t return_flag;

	switch(lighteffects_Parament_local->type)
	{
		case CANDLE:/*蜡烛*/
		{
			return_flag = candle(lighteffects_Parament_local);
		}break;
		
		case FIRE:/*火焰*/
		{
			
		}break;
		
		case BREATH:/*呼吸*/
		{
			return_flag = breath(lighteffects_Parament_local);
		}break;		
		

		case CLOUND:/*云朵*/
		{
			return_flag = cloud(lighteffects_Parament_local);
		}break;	

		
		case PAPARAZZI:/*派对*/
		{
			
		}break;		
		

		case FAULT:/*故障*/
		{
			
		}break;		
		

		case TV:/*电视*/
		{
			
		}break;		
		
		case WELD:/*电焊*/
		{
			
		}break;	

		case EXPLODE:/*爆炸*/
		{
			
		}break;	

		case LIGHTNING:/*闪电*/
		{
			
		}break;	

		case STROBE:/*频闪*/
		{
			
		}break;		

		case FIREWORK:/*烟花*/
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

static uint8_t breath(struct LIGHTEFFECTS *breath_Parament)
{
	//定义 CARRY_OUT 阶段设置参数
	static float brightness_Set = 0;
	static int16_t color_Temperature_Set = 0;
	static uint8_t freq_Set = 0;

	if(breath_Parament->le_Update_Flag == FLAG_TRUE) breath_Parament->le_State = SETTING;	//有新的参数进来需要重新设置
	switch (breath_Parament->le_State)
	{
		case SETTING:
		{
			static uint8_t set_State = 0;
			switch (set_State)
			{
				case 0:
				{
					//参数赋值			
					brightness_Set = breath_Parament->brightness;
					color_Temperature_Set = breath_Parament->color_Temperature;
					if(breath_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = breath_Parament->freq;
					set_State=1;
				}break;

				case 1:
				{
					//参数赋值			
					brightness_Set = 0.006;//最小值不能设定为0
					color_Temperature_Set = breath_Parament->color_Temperature;
					if(breath_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = breath_Parament->freq;
					set_State=0;
				}break;
				default:
					return thisERROR;
					break;
			}

			//状态切换
			breath_Parament->le_State = CARRY_OUT;
		}break;
		
		case CARRY_OUT:
		{
			float brightness_Err = 0;//灯效亮度 0.0%-100.0%
			static float brightness_Out = 0;//灯效亮度 0.0%-100.0%
			#define LIGHT_P 0.01 	//每次变化步进比率
			
			int16_t color_Temperature_Err = 0;//灯效色温 2700-6500
			static int16_t color_Temperature_Out = 0;//灯效色温 2700-6500
			#define COLOR_TEMPERATURE_P 0.01 	//每次变化步进比率

			//计算本轮输出参数
			brightness_Err = brightness_Set - brightness_Out;	//计算亮度差值
			brightness_Out += LIGHT_P*brightness_Err;//累计亮度差值到输出
			color_Temperature_Out = color_Temperature_Set;
			//获得实际输出比例
			light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(breath_Parament->cold_Percentage), &(breath_Parament->warm_Percentage));
			//根据频率设置延迟
			osDelay(10/freq_Set); //最大周期长度为10*700ms
			if((fabsf(brightness_Err)<=0.001)&&(abs(color_Temperature_Err)<=50)) breath_Parament->le_State = SETTING;	//已经完成本轮变换，需要重新设置
		}break;

		default:
		{
			return thisERROR;
		}break;
	}	

	return thisOK;

}

static uint8_t cloud(struct LIGHTEFFECTS *cloud_Parament)
{
	//定义 CARRY_OUT 阶段设置参数
	static float brightness_Set = 0;
	static int16_t color_Temperature_Set = 0;
	static uint8_t freq_Set = 0;
	//保存 cloud 参数组
	float light_Para[2] = {0.3, 0.8};
	uint16_t color_Temperature_Para[2] = {6300, 3000};
	if(cloud_Parament->le_Update_Flag == FLAG_TRUE) cloud_Parament->le_State = SETTING;	//有新的参数进来需要重新设置
	switch (cloud_Parament->le_State)
	{
		case SETTING:
		{
			static uint8_t set_State = 0;
			switch (set_State)
			{
				case 0:
				{
					//参数赋值	低亮度高色温 模拟阴天		
					brightness_Set = cloud_Parament->brightness * light_Para[0];
					color_Temperature_Set = color_Temperature_Para[0];
					if(cloud_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = cloud_Parament->freq;
					set_State=1;
				}break;

				case 1:
				{
					//参数赋值 高亮度低色温 模拟晴天		
					brightness_Set = cloud_Parament->brightness * light_Para[1];//最小值不能设定为0
					color_Temperature_Set = color_Temperature_Para[1];
					if(cloud_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = cloud_Parament->freq;
					set_State=0;
				}break;
				default:
					return thisERROR;
					break;
			}

			//状态切换
			cloud_Parament->le_State = CARRY_OUT;
		}break;
		
		case CARRY_OUT:
		{
			float brightness_Err = 0;//灯效亮度 0.0%-100.0%
			static float brightness_Out = 0;//灯效亮度 0.0%-100.0%
			#define LIGHT_P 0.10 	//每次变化步进比率
			
			int16_t color_Temperature_Err = 0;//灯效色温 2700-6500
			static int16_t color_Temperature_Out = 0;//灯效色温 2700-6500
			#define COLOR_TEMPERATURE_P 0.10 	//每次变化步进比率

			//计算本轮输出参数
			brightness_Err = brightness_Set - brightness_Out;	//计算亮度差值
			brightness_Out += LIGHT_P*brightness_Err;//累计亮度差值到输出
			color_Temperature_Out = color_Temperature_Set;
			//获得实际输出比例
			light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(cloud_Parament->cold_Percentage), &(cloud_Parament->warm_Percentage));
			//打印输出冷暖比例 测试后删除
			//printf("%f, %f\n",cloud_Parament->cold_Percentage,cloud_Parament->warm_Percentage);
			//printf("1\n");
			//根据频率设置延迟
			osDelay(10/freq_Set); //最大周期长度为(2+1)*450ms
			if((fabsf(brightness_Err)<=0.001)&&(abs(color_Temperature_Err)<=50)) cloud_Parament->le_State = DELAY;	//已经完成本轮变换，需要重新设置
		}break;

		case DELAY:
		{
			osDelay(10*1000/freq_Set);//延迟最大10*1000ms
			cloud_Parament->le_State = SETTING;//切换状态机状态
		}break;
		default:
		{
			return thisERROR;
		}break;
	}	

	return thisOK;

}

/*
static uint8_t demo(struct LIGHTEFFECTS *demo_Parament)
{
	switch (breath_Parament->le_State)
	{
		case SETTING:
		{
			static float brightness_Set = 0;
			static uint16_t color_Temperature_Set = 0;
			static float brightness_para[1] = {0};
			static uint16_t color_Temperature_para[1] = {4600};

			static uint16_t setting_p = 0;
			brightness_Set = brightness_para[setting_p];
			color_Temperature_Set = color_Temperature_para[setting_p];
			setting_p++;
			breath_Parament->le_State = CARRY_OUT;


		}break;
		
		default:
		{
			float brightness_Err = 0;//灯效亮度 0.0%-100.0%
			static float brightness_Out = 0;//灯效亮度 0.0%-100.0%
			#define LIGHT_P 0.05 	//每次变化步进比率
			uint16_t color_Temperature_Err = 0;//灯效色温 2700-6500
			static uint16_t color_Temperature_Out = 0;//灯效色温 2700-6500
			#define COLOR_TEMPERATURE_P 0.05 	//每次变化步进比率

			//计算本轮输出参数
			brightness_Err = brightness_Set - brightness_Out;	//计算亮度差值
			brightness_Out += LIGHT_P*brightness_Err	//累计亮度差值到输出
			color_Temperature_Err = color_Temperature_Set - color_Temperature_Out;	//计算亮度差值
			color_Temperature_Out += COLOR_TEMPERATURE_P*color_Temperature_Err	//累计亮度差值到输出
			
			//获得实际输出比例
			light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(breath_Parament->cold_Percentage), &(breath_Parament->warm_Percentage));
			//根据频率设置延迟
			//osDelay(1);
			if(breath_Parament->le_Update_Flag == FLAG_TRUE) breath_Parament->le_State = SETTING;	//有新的参数进来需要重新设置
			if((brightness_Err<=0.04*brightness_Set)&&(color_Temperature_Err<=0.04*color_Temperature_Set)) breath_Parament->le_State = SETTING;	//已经完成本轮变换，需要重新设置
		}break;
	}	

	return thisOK;
}
*/
 