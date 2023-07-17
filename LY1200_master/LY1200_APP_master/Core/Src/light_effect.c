#include "cmsis_os.h"
#include "light_effect.h"
#include "rng.h"

static uint8_t fire(struct LIGHTEFFECTS *fire_Parament);
static uint8_t breath(struct LIGHTEFFECTS *breath_Parament);
static uint8_t cloud(struct LIGHTEFFECTS *cloud_Parament);
static uint8_t paparazzi(struct LIGHTEFFECTS *paparazzi_Parament);
static uint8_t fault(struct LIGHTEFFECTS *fault_Parament);
static uint8_t tv(struct LIGHTEFFECTS *tv_Parament);
static uint8_t weld(struct LIGHTEFFECTS *weld_Parament);
static uint8_t explode(struct LIGHTEFFECTS *explode_Parament);
static uint8_t lightning(struct LIGHTEFFECTS *lightning_Parament);
static uint8_t strobe(struct LIGHTEFFECTS *strobe_Parament);
static uint8_t firework(struct LIGHTEFFECTS *firework_Parament);

static uint32_t LE_ii = 0; //测试使用 后续删除

uint8_t lighteffects_Type_Choose(struct LIGHTEFFECTS *lighteffects_Parament_local)
{
	uint8_t return_flag;

	switch(lighteffects_Parament_local->type)
	{
//		case CANDLE:/*蜡烛*/
//		{
//			return_flag = candle(lighteffects_Parament_local);
//		}break;
		
		case FIRE:/*火焰*/
		{
			return_flag = fire(lighteffects_Parament_local);
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
			return_flag = paparazzi(lighteffects_Parament_local);
		}break;		
		

		case FAULT:/*故障*/
		{
			return_flag = fault(lighteffects_Parament_local);
		}break;		
		

		case TV:/*电视*/
		{
			return_flag = tv(lighteffects_Parament_local);
		}break;		
		
		case WELD:/*电焊*/
		{
			return_flag = weld(lighteffects_Parament_local);
		}break;	

		case EXPLODE:/*爆炸*/
		{
			return_flag = explode(lighteffects_Parament_local);
		}break;	

		case LIGHTNING:/*闪电*/
		{
			return_flag = lightning(lighteffects_Parament_local);
		}break;	

		case STROBE:/*频闪*/
		{
			return_flag = strobe(lighteffects_Parament_local);
		}break;		

		case FIREWORK:/*烟花*/
		{
			return_flag = firework(lighteffects_Parament_local);
		}break;	

		default:
		{
			return 0;
		}
	}
	
	return return_flag;
}

static uint8_t fire(struct LIGHTEFFECTS *fire_Parament)
{
	/* _Parament->brightness 0.0%-100.0%
	*  _Parament->color_Temperature = 2700 -6500 
	*  _Parament->freq = 1 -10 'R'
	*/

	//定义 CARRY_OUT 阶段设置参数
	static float brightness_Set = 0;	//0%-100%
	static int16_t color_Temperature_Set = 0; //2700k-6500K
	static uint8_t freq_Set = 0;	//1 - 10 'R'

	float light_Para[2] = {1.0, 1.0};
	uint16_t color_Temperature_Para[2] = {2500, 3500};

	if(fire_Parament->le_Update_Flag == FLAG_TRUE) fire_Parament->le_State = SETTING;	//有新的参数进来需要重新设置
	switch (fire_Parament->le_State)
	{
		case SETTING:
		{
			static uint8_t set_State = 0;
			switch (set_State)
			{
				case 0:
				{
					//参数赋值			
					brightness_Set = fire_Parament->brightness * light_Para[0];
					color_Temperature_Set = color_Temperature_Para[0];
					if(fire_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = fire_Parament->freq;
					set_State=1;
				}break;

				case 1:
				{
					//参数赋值			
					brightness_Set = 0.006 * light_Para[1];//最小值不能设定为0
					color_Temperature_Set = color_Temperature_Para[1];
					if(fire_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = fire_Parament->freq;
					set_State=0;
				}break;
				default:
					return thisERROR;
					break;
			}

			//状态切换
			fire_Parament->le_State = CARRY_OUT;
		}break;
		
		case CARRY_OUT:
		{
			float brightness_Err = 0;//灯效亮度 0.0%-100.0%
			static float brightness_Out = 0;//灯效亮度 0.0%-100.0%
			#define LIGHT_P 0.05 	//每次变化步进比率
			
			float color_Temperature_Err = 0;//灯效色温 2700-6500
			static float color_Temperature_Out = 0;//灯效色温 2700-6500
			static int16_t color_Temperature_Out_int = 0;//灯效色温 2700-6500
			#define COLOR_TEMPERATURE_P 0.05 	//每次变化步进比率

			//计算本轮输出参数
			brightness_Err = brightness_Set - brightness_Out;	//计算亮度差值
			brightness_Out += LIGHT_P*brightness_Err;//累计亮度差值到输出

			color_Temperature_Err = color_Temperature_Set - color_Temperature_Out;
			color_Temperature_Out += COLOR_TEMPERATURE_P*color_Temperature_Err;
			color_Temperature_Out_int = (int16_t)color_Temperature_Out;
			//获得实际输出比例
			light_Effect_Analysis(&brightness_Out, &color_Temperature_Out_int, &(fire_Parament->cold_Percentage), &(fire_Parament->warm_Percentage));
			//根据频率设置延迟
			osDelay(30/freq_Set); //最大周期长度为(30+1)*136ms
			if((fabsf(brightness_Err)<=0.001)&&(fabsf(color_Temperature_Err)<=25)) fire_Parament->le_State = SETTING;	//已经完成本轮变换，需要重新设置
		}break;

		default:
		{
			return thisERROR;
		}break;
	}	

	return thisOK;	
}

static uint8_t breath(struct LIGHTEFFECTS *breath_Parament)
{
	/* _Parament->brightness 0.0%-100.0%
	*  _Parament->color_Temperature = 2700 -6500 
	*  _Parament->freq = 1 -10 'R'
	*/

	//定义 CARRY_OUT 阶段设置参数
	static float brightness_Set = 0;	//0%-100%
	static int16_t color_Temperature_Set = 0; //2700k-6500K
	static uint8_t freq_Set = 0;	//1 - 10 'R'

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
			#define LIGHT_P 0.05 	//每次变化步进比率
			
			int16_t color_Temperature_Err = 0;//灯效色温 2700-6500
			static int16_t color_Temperature_Out = 0;//灯效色温 2700-6500
			#define COLOR_TEMPERATURE_P 0.05 	//每次变化步进比率

			//计算本轮输出参数
			brightness_Err = brightness_Set - brightness_Out;	//计算亮度差值
			brightness_Out += LIGHT_P*brightness_Err;//累计亮度差值到输出
			color_Temperature_Out = color_Temperature_Set;
			//获得实际输出比例
			light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(breath_Parament->cold_Percentage), &(breath_Parament->warm_Percentage));
			//根据频率设置延迟
			osDelay(30/freq_Set); //最大周期长度为(30+1)*136ms
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
	/* _Parament->brightness 0.0%-100.0%
	*  //_Parament->color_Temperature = 2700 -6500 无此参数
	*  _Parament->freq = 1 -10 'R'
	*/

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
			#define LIGHT_P 0.05 	//每次变化步进比率
			
			int16_t color_Temperature_Err = 0;//灯效色温 2700-6500
			static int16_t color_Temperature_Out = 0;//灯效色温 2700-6500
			#define COLOR_TEMPERATURE_P 0.05 	//每次变化步进比率

			//计算本轮输出参数
			brightness_Err = brightness_Set - brightness_Out;	//计算亮度差值
			brightness_Out += LIGHT_P*brightness_Err;//累计亮度差值到输出
			color_Temperature_Out = color_Temperature_Set;
			//获得实际输出比例
			light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(cloud_Parament->cold_Percentage), &(cloud_Parament->warm_Percentage));
			//根据频率设置延迟
			osDelay(10/freq_Set); //最大周期长度为(10+1)*110ms
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

static uint8_t paparazzi(struct LIGHTEFFECTS *paparazzi_Parament)
{
    /* float _Parament->brightness 0.0%-100.0%
    *  //uint16_t _Parament->color_Temperature = 2700 -6500 
    *  uint8_t _Parament->freq = 1 -10 'R'
	*/

	//定义 CARRY_OUT 阶段设置参数
	static float brightness_Set = 0;
	static int16_t color_Temperature_Set = 0;
	static uint8_t freq_Set = 0;
	//保存 cloud 参数组
	#define PARA_LONG 10
	float light_Para[PARA_LONG] = {0.50, 0.525, 0.55, 0.575, 0.60, 0.625, 0.65, 0.675, 0.70, 0.725};
	uint16_t color_Temperature_Para[PARA_LONG] = {6250, 6000, 5750, 5500, 5250, 5000, 4750, 4500, 4250, 4000};
	if(paparazzi_Parament->le_Update_Flag == FLAG_TRUE) paparazzi_Parament->le_State = SETTING;	//有新的参数进来需要重新设置
	switch (paparazzi_Parament->le_State)
	{
		case SETTING:
		{
			static uint16_t set_State = 0;

			if(set_State>=PARA_LONG){set_State=0;}
			if(set_State<0){set_State=0;}

			brightness_Set = paparazzi_Parament->brightness * light_Para[set_State];
			color_Temperature_Set = color_Temperature_Para[set_State];
			if(paparazzi_Parament->freq == 'R') freq_Set = 1+random_number(10);
			else freq_Set = paparazzi_Parament->freq;

			set_State++;//参数切换
			if(set_State>=PARA_LONG){set_State=0;}
			if(set_State<0){set_State=0;}

			//状态切换
			paparazzi_Parament->le_State = CARRY_OUT;

		}break;
		
		case CARRY_OUT:
		{
			//float brightness_Err = 0;//灯效亮度 0.0%-100.0%
			static float brightness_Out = 0;//灯效亮度 0.0%-100.0%
			//#define LIGHT_P 0.05 	//每次变化步进比率
			
			//int16_t color_Temperature_Err = 0;//灯效色温 2700-6500
			static int16_t color_Temperature_Out = 0;//灯效色温 2700-6500
			//#define COLOR_TEMPERATURE_P 0.05 	//每次变化步进比率

			//计算本轮输出参数
			//brightness_Err = brightness_Set - brightness_Out;	//计算亮度差值
			//brightness_Out += LIGHT_P*brightness_Err;//累计亮度差值到输出
			brightness_Out = brightness_Set;
			color_Temperature_Out = color_Temperature_Set;
			//获得实际输出比例
			light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(paparazzi_Parament->cold_Percentage), &(paparazzi_Parament->warm_Percentage));
			//根据频率设置延迟
			//osDelay(10/freq_Set); //最大周期长度为(10+1)*110ms
			//if((fabsf(brightness_Err)<=0.001)&&(abs(color_Temperature_Err)<=50)) paparazzi_Parament->le_State = DELAY;	//已经完成本轮变换，需要重新设置
			paparazzi_Parament->le_State = DELAY;	//已经完成本轮变换，需要重新设置
		}break;

		case DELAY:
		{
			osDelay(3*1000/freq_Set);//延迟最大3*1000ms
			paparazzi_Parament->le_State = SETTING;//切换状态机状态
		}break;
		default:
		{
			return thisERROR;
		}break;
	}	

	return thisOK;	
}

static uint8_t fault(struct LIGHTEFFECTS *fault_Parament)
{
    /* float _Parament->brightness 0.0%-100.0%
    *  uint16_t _Parament->color_Temperature = 2700 -6500 
    *  uint8_t _Parament->freq = 1 -10 'R'
	*/
	//定义 CARRY_OUT 阶段设置参数
	static float brightness_Set = 0;	//0%-100%
	static int16_t color_Temperature_Set = 0; //2700k-6500K
	static uint8_t freq_Set = 0;	//1 - 10 'R'

	if(fault_Parament->le_Update_Flag == FLAG_TRUE) fault_Parament->le_State = SETTING;	//有新的参数进来需要重新设置
	switch (fault_Parament->le_State)
	{
		case SETTING:
		{
			static uint8_t set_State = 0;
			switch (set_State)
			{
				case 0:
				{
					//参数赋值			
					brightness_Set = fault_Parament->brightness;
					color_Temperature_Set = fault_Parament->color_Temperature;
					if(fault_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = fault_Parament->freq;
					set_State=1;
				}break;

				case 1:
				{
					//参数赋值			
					brightness_Set = 0.01;//最小值不能设定为0
					color_Temperature_Set = fault_Parament->color_Temperature;
					if(fault_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = fault_Parament->freq;
					set_State=0;
				}break;
				default:
					return thisERROR;
					break;
			}

			//状态切换
			//fault_Parament->le_State = CARRY_OUT;
			if(random_number(2)==0)
			{
				fault_Parament->le_State = DELAY;
				if(set_State==0) set_State=1;
				if(set_State==1) set_State=0;
			}
			else
			{
				fault_Parament->le_State = CARRY_OUT;
			}
		}break;
		
		case CARRY_OUT:
		{
			float brightness_Err = 0;//灯效亮度 0.0%-100.0%
			static float brightness_Out = 0;//灯效亮度 0.0%-100.0%	
			int16_t color_Temperature_Err = 0;//灯效色温 2700-6500
			static int16_t color_Temperature_Out = 0;//灯效色温 2700-6500

			brightness_Out = brightness_Set; 
			color_Temperature_Out = color_Temperature_Set;
			//获得实际输出比例
			light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(fault_Parament->cold_Percentage), &(fault_Parament->warm_Percentage));
			//根据频率设置延迟
			osDelay(1000/freq_Set); //最大周期长度为(1000+1)*ms
			if((fabsf(brightness_Err)<=0.001)&&(abs(color_Temperature_Err)<=50)) fault_Parament->le_State = SETTING;	//已经完成本轮变换，需要重新设置
			
		}break;

		case DELAY:
		{
			osDelay(3000/freq_Set); //最大周期长度为(3000+1)*ms
			fault_Parament->le_State = SETTING;
		}break;

		default:
		{
			return thisERROR;
		}break;
	}	

	return thisOK;	
}

static uint8_t tv(struct LIGHTEFFECTS *tv_Parament)
{
    /* float _Parament->brightness 0.0%-100.0%
    *  //uint16_t _Parament->color_Temperature = 2700 -6500 
    *  uint8_t _Parament->freq = 1 -10 'R'
	*/

	//定义 CARRY_OUT 阶段设置参数
	static float brightness_Set = 0;
	static int16_t color_Temperature_Set = 0;
	static uint8_t freq_Set = 0;
	//保存 cloud 参数组
	float light_Para[4] = {0.525, 0.55, 0.575, 0.60};
	uint16_t color_Temperature_Para[4] = {6000, 5500, 5000, 4500};
	if(tv_Parament->le_Update_Flag == FLAG_TRUE) tv_Parament->le_State = SETTING;	//有新的参数进来需要重新设置
	switch (tv_Parament->le_State)
	{
		case SETTING:
		{
			static uint8_t set_State = 0;
			switch (set_State)
			{
				case 0:
				{
					//参数赋值	0		
					brightness_Set = tv_Parament->brightness * light_Para[0];
					color_Temperature_Set = color_Temperature_Para[0];
					if(tv_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = tv_Parament->freq;
					set_State=1;
				}break;

				case 1:
				{
					//参数赋值 1		
					brightness_Set = tv_Parament->brightness * light_Para[1];//最小值不能设定为0
					color_Temperature_Set = color_Temperature_Para[1];
					if(tv_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = tv_Parament->freq;
					set_State=2;
				}break;

				case 2:
				{
					//参数赋值 1		
					brightness_Set = tv_Parament->brightness * light_Para[2];//最小值不能设定为0
					color_Temperature_Set = color_Temperature_Para[2];
					if(tv_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = tv_Parament->freq;
					set_State=3;
				}break;

				case 3:
				{
					//参数赋值 1		
					brightness_Set = tv_Parament->brightness * light_Para[3];//最小值不能设定为0
					color_Temperature_Set = color_Temperature_Para[3];
					if(tv_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = tv_Parament->freq;
					set_State=0;
				}break;

				default:
					return thisERROR;
					break;
			}

			//状态切换
			tv_Parament->le_State = CARRY_OUT;
		}break;
		
		case CARRY_OUT:
		{
			//float brightness_Err = 0;//灯效亮度 0.0%-100.0%
			static float brightness_Out = 0;//灯效亮度 0.0%-100.0%
			//#define LIGHT_P 0.05 	//每次变化步进比率
			
			//int16_t color_Temperature_Err = 0;//灯效色温 2700-6500
			static int16_t color_Temperature_Out = 0;//灯效色温 2700-6500
			//#define COLOR_TEMPERATURE_P 0.05 	//每次变化步进比率

			//计算本轮输出参数
			//brightness_Err = brightness_Set - brightness_Out;	//计算亮度差值
			//brightness_Out += LIGHT_P*brightness_Err;//累计亮度差值到输出
			brightness_Out = brightness_Set;
			color_Temperature_Out = color_Temperature_Set;
			//获得实际输出比例
			light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(tv_Parament->cold_Percentage), &(tv_Parament->warm_Percentage));
			//根据频率设置延迟
			//osDelay(10/freq_Set); //最大周期长度为(10+1)*110ms
			//if((fabsf(brightness_Err)<=0.001)&&(abs(color_Temperature_Err)<=50)) tv_Parament->le_State = DELAY;	//已经完成本轮变换，需要重新设置
			tv_Parament->le_State = DELAY;	//已经完成本轮变换，需要重新设置
		}break;

		case DELAY:
		{
			osDelay(10*1000/freq_Set);//延迟最大10*1000ms
			tv_Parament->le_State = SETTING;//切换状态机状态
		}break;
		default:
		{
			return thisERROR;
		}break;
	}	

	return thisOK;

}

static uint8_t weld(struct LIGHTEFFECTS *weld_Parament)
{
    /* float _Parament->brightness 0.0%-100.0%
    *  uint16_t _Parament->color_Temperature = 2700 -6500 
    *  uint8_t _Parament->freq = 1 -10 'R'
	*/
	//定义 CARRY_OUT 阶段设置参数
	static float brightness_Set = 0;	//0%-100%
	static int16_t color_Temperature_Set = 4600; //2700k-6500K
	static uint8_t freq_Set = 5;	//1 - 10 'R'

	if(weld_Parament->le_Update_Flag == FLAG_TRUE) weld_Parament->le_State = SETTING;	//有新的参数进来需要重新设置
	switch (weld_Parament->le_State)
	{
		case SETTING:
		{
			static uint8_t set_State = 0;
			switch (set_State)
			{
				case 0:
				{
					//参数赋值			
					brightness_Set = weld_Parament->brightness;
					color_Temperature_Set = weld_Parament->color_Temperature;
					if(weld_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = weld_Parament->freq;
					set_State=1;
				}break;

				case 1:
				{
					//参数赋值			
					brightness_Set = weld_Parament->brightness * 0.5;//最小值不能设定为0
					if(brightness_Set<=0.005) brightness_Set = 0.005;
					color_Temperature_Set = weld_Parament->color_Temperature;
					if(weld_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = weld_Parament->freq;
					set_State=0;
				}break;
				default:
					return thisERROR;
					break;
			}
			//状态切换
			weld_Parament->le_State = CARRY_OUT;
			if(set_State==0)
			{
				if(random_number(2)==0)
				{
					weld_Parament->le_State = DELAY;
					set_State=0;
				}
			}
		}break;
		
		case CARRY_OUT:
		{
			float brightness_Err = 0;//灯效亮度 0.0%-100.0%
			static float brightness_Out = 0;//灯效亮度 0.0%-100.0%	
			int16_t color_Temperature_Err = 0;//灯效色温 2700-6500
			static int16_t color_Temperature_Out = 0;//灯效色温 2700-6500

			brightness_Out = brightness_Set; 
			color_Temperature_Out = color_Temperature_Set;
			//获得实际输出比例
			light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(weld_Parament->cold_Percentage), &(weld_Parament->warm_Percentage));
			//根据频率设置延迟
			osDelay(200/freq_Set); //最大周期长度为(200+1)*ms
			if((fabsf(brightness_Err)<=0.001)&&(abs(color_Temperature_Err)<=50)) weld_Parament->le_State = SETTING;	//已经完成本轮变换，需要重新设置
			
		}break;

		case DELAY:
		{
			//根据频率设置延迟
			osDelay(2000/freq_Set); //最大周期长度为(2000+1)*ms
			//状态切换
			weld_Parament->le_State = SETTING;		
				
		}break;

		default:
		{
			return thisERROR;
		}break;
	}	

	return thisOK;
}

static uint8_t explode(struct LIGHTEFFECTS *explode_Parament)
{
    /* float _Parament->brightness 0.0%-100.0%
    *  uint16_t _Parament->color_Temperature = 2700 -6500 
    *  uint8_t _Parament->freq = 1 -10 'R'
	*/
	//定义 CARRY_OUT 阶段设置参数
	static float brightness_Set = 0;	//0%-100%
	static int16_t color_Temperature_Set = 0; //2700k-6500K
	static uint8_t freq_Set = 0;	//1 - 10 'R'
	static uint8_t set_State = 0;
	
	if(explode_Parament->le_Update_Flag == FLAG_TRUE) explode_Parament->le_State = SETTING;	//有新的参数进来需要重新设置
	switch (explode_Parament->le_State)
	{
		case SETTING:
		{
			switch (set_State)
			{
				case 0:
				{
					//参数赋值			
					brightness_Set = explode_Parament->brightness;
					color_Temperature_Set = explode_Parament->color_Temperature;
					if(explode_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = explode_Parament->freq;
					set_State=1;
				}break;

				case 1:
				{
					//参数赋值			
					brightness_Set = 0.006;//最小值不能设定为0
					color_Temperature_Set = explode_Parament->color_Temperature;
					if(explode_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = explode_Parament->freq;
					set_State=0;
				}break;
				default:
					return thisERROR;
					break;
			}

			//状态切换
			explode_Parament->le_State = CARRY_OUT;
		}break;
		
		case CARRY_OUT:
		{
			float brightness_Err = 0;//灯效亮度 0.0%-100.0%
			static float brightness_Out = 0;//灯效亮度 0.0%-100.0%
			#define LIGHT_P 0.05 	//每次变化步进比率
			
			int16_t color_Temperature_Err = 0;//灯效色温 2700-6500
			static int16_t color_Temperature_Out = 0;//灯效色温 2700-6500
			#define COLOR_TEMPERATURE_P 0.05 	//每次变化步进比率
			
			if(set_State == 1)
			{
				brightness_Out = brightness_Set; 
				color_Temperature_Out = color_Temperature_Set;
				//获得实际输出比例
				light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(explode_Parament->cold_Percentage), &(explode_Parament->warm_Percentage));
				//根据频率设置延迟
				osDelay(1000/freq_Set); //最大周期长度为(30+1)*136ms
				if((fabsf(brightness_Err)<=0.001)&&(abs(color_Temperature_Err)<=50)) explode_Parament->le_State = SETTING;	//已经完成本轮变换，需要重新设置
			}
			else
			{
				//计算本轮输出参数
				brightness_Err = brightness_Set - brightness_Out;	//计算亮度差值
				brightness_Out += LIGHT_P*brightness_Err;//累计亮度差值到输出
				color_Temperature_Out = color_Temperature_Set;
				//获得实际输出比例
				light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(explode_Parament->cold_Percentage), &(explode_Parament->warm_Percentage));
				//根据频率设置延迟
				osDelay(50/freq_Set); //最大周期长度为(50+1)*136ms
				if((fabsf(brightness_Err)<=0.001)&&(abs(color_Temperature_Err)<=50)) explode_Parament->le_State = SETTING;	//已经完成本轮变换，需要重新设置
			}

		}break;

		default:
		{
			return thisERROR;
		}break;
	}	

	return thisOK;	
}

static uint8_t lightning(struct LIGHTEFFECTS *lightning_Parament)
{
    /* float _Parament->brightness 0.0%-100.0%
    *  uint16_t _Parament->color_Temperature = 2700 -6500 
    *  uint8_t _Parament->freq = 1 -10 'R'
	*/
	//定义 CARRY_OUT 阶段设置参数
	static float brightness_Set = 0;	//0%-100%
	static int16_t color_Temperature_Set = 4600; //2700k-6500K
	static uint8_t freq_Set = 5;	//1 - 10 'R'

	if(lightning_Parament->le_Update_Flag == FLAG_TRUE) lightning_Parament->le_State = SETTING;	//有新的参数进来需要重新设置
	switch (lightning_Parament->le_State)
	{
		case SETTING:
		{
			static uint8_t set_State = 0;
			switch (set_State)
			{
				case 0:
				{
					//参数赋值			
					brightness_Set = lightning_Parament->brightness;
					color_Temperature_Set = lightning_Parament->color_Temperature;
					if(lightning_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = lightning_Parament->freq;
					set_State=1;
				}break;

				case 1:
				{
					//参数赋值			
					brightness_Set = 0.01;//最小值不能设定为0
					color_Temperature_Set = lightning_Parament->color_Temperature;
					if(lightning_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = lightning_Parament->freq;
					set_State=0;
				}break;
				default:
					return thisERROR;
					break;
			}
			//状态切换
			lightning_Parament->le_State = CARRY_OUT;
			if(set_State==0)
			{
				if(random_number(2)==0)
				{
					lightning_Parament->le_State = DELAY;
					set_State=0;
				}
			}
		}break;
		
		case CARRY_OUT:
		{
			float brightness_Err = 0;//灯效亮度 0.0%-100.0%
			static float brightness_Out = 0;//灯效亮度 0.0%-100.0%	
			int16_t color_Temperature_Err = 0;//灯效色温 2700-6500
			static int16_t color_Temperature_Out = 0;//灯效色温 2700-6500

			brightness_Out = brightness_Set; 
			color_Temperature_Out = color_Temperature_Set;
			//获得实际输出比例
			light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(lightning_Parament->cold_Percentage), &(lightning_Parament->warm_Percentage));
			//根据频率设置延迟
			osDelay(200/freq_Set); //最大周期长度为(200+1)*ms
			if((fabsf(brightness_Err)<=0.001)&&(abs(color_Temperature_Err)<=50)) lightning_Parament->le_State = SETTING;	//已经完成本轮变换，需要重新设置
			
		}break;

		case DELAY:
		{
			//根据频率设置延迟
			osDelay(5000/freq_Set); //最大周期长度为(5000+1)*ms
			//状态切换
			lightning_Parament->le_State = SETTING;		
				
		}break;

		default:
		{
			return thisERROR;
		}break;
	}	

	return thisOK;
}

static uint8_t strobe(struct LIGHTEFFECTS *strobe_Parament)
{
    /* float _Parament->brightness 0.0%-100.0%
    *  uint16_t _Parament->color_Temperature = 2700 -6500 
    *  uint8_t _Parament->freq = 1 -10 'R'
	*/
	//定义 CARRY_OUT 阶段设置参数
	static float brightness_Set = 0;	//0%-100%
	static int16_t color_Temperature_Set = 0; //2700k-6500K
	static uint8_t freq_Set = 0;	//1 - 10 'R'

	if(strobe_Parament->le_Update_Flag == FLAG_TRUE) strobe_Parament->le_State = SETTING;	//有新的参数进来需要重新设置
	switch (strobe_Parament->le_State)
	{
		case SETTING:
		{
			static uint8_t set_State = 0;
			switch (set_State)
			{
				case 0:
				{
					//参数赋值			
					brightness_Set = strobe_Parament->brightness;
					color_Temperature_Set = strobe_Parament->color_Temperature;
					if(strobe_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = strobe_Parament->freq;
					set_State=1;
				}break;

				case 1:
				{
					//参数赋值			
					brightness_Set = 0.01;//最小值不能设定为0
					color_Temperature_Set = strobe_Parament->color_Temperature;
					if(strobe_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = strobe_Parament->freq;
					set_State=0;
				}break;
				default:
					return thisERROR;
					break;
			}

			//状态切换
			strobe_Parament->le_State = CARRY_OUT;
		}break;
		
		case CARRY_OUT:
		{
			float brightness_Err = 0;//灯效亮度 0.0%-100.0%
			static float brightness_Out = 0;//灯效亮度 0.0%-100.0%	
			int16_t color_Temperature_Err = 0;//灯效色温 2700-6500
			static int16_t color_Temperature_Out = 0;//灯效色温 2700-6500

			brightness_Out = brightness_Set; 
			color_Temperature_Out = color_Temperature_Set;
			//获得实际输出比例
			light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(strobe_Parament->cold_Percentage), &(strobe_Parament->warm_Percentage));
			//根据频率设置延迟
			osDelay(1000/freq_Set); //最大周期长度为(1000+1)*ms
			if((fabsf(brightness_Err)<=0.001)&&(abs(color_Temperature_Err)<=50)) strobe_Parament->le_State = SETTING;	//已经完成本轮变换，需要重新设置
			
		}break;

		default:
		{
			return thisERROR;
		}break;
	}	

	return thisOK;
}

static uint8_t firework(struct LIGHTEFFECTS *firework_Parament)
{
    /* float _Parament->brightness 0.0%-100.0%
    *  uint16_t _Parament->color_Temperature = 2700 -6500 
    *  uint8_t _Parament->freq = 1 -10 'R'
	*/
	//定义 CARRY_OUT 阶段设置参数
	static float brightness_Set = 0;	//0%-100%
	static int16_t color_Temperature_Set = 0; //2700k-6500K
	static uint8_t freq_Set = 0;	//1 - 10 'R'
	static uint8_t set_State = 0;
	
	if(firework_Parament->le_Update_Flag == FLAG_TRUE) firework_Parament->le_State = SETTING;	//有新的参数进来需要重新设置
	switch (firework_Parament->le_State)
	{
		case SETTING:
		{
			switch (set_State)
			{
				case 0:
				{
					//参数赋值			
					brightness_Set = firework_Parament->brightness;
					color_Temperature_Set = firework_Parament->color_Temperature;
					if(firework_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = firework_Parament->freq;
					set_State=1;
				}break;

				case 1:
				{
					//参数赋值			
					brightness_Set = 0.006;//最小值不能设定为0
					color_Temperature_Set = firework_Parament->color_Temperature;
					if(firework_Parament->freq == 'R') freq_Set = 1+random_number(10);
					else freq_Set = firework_Parament->freq;
					set_State=0;
				}break;
				default:
					return thisERROR;
					break;
			}

			//状态切换
			firework_Parament->le_State = CARRY_OUT;
		}break;
		
		case CARRY_OUT:
		{
			float brightness_Err = 0;//灯效亮度 0.0%-100.0%
			static float brightness_Out = 0;//灯效亮度 0.0%-100.0%
			#define LIGHT_P 0.05 	//每次变化步进比率
			
			int16_t color_Temperature_Err = 0;//灯效色温 2700-6500
			static int16_t color_Temperature_Out = 0;//灯效色温 2700-6500
			#define COLOR_TEMPERATURE_P 0.05 	//每次变化步进比率
			
			if(set_State == 1)
			{
				brightness_Out = brightness_Set; 
				color_Temperature_Out = color_Temperature_Set;
				//获得实际输出比例
				light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(firework_Parament->cold_Percentage), &(firework_Parament->warm_Percentage));
				//根据频率设置延迟
				osDelay(1000/freq_Set); //最大周期长度为(30+1)*136ms
				if((fabsf(brightness_Err)<=0.001)&&(abs(color_Temperature_Err)<=50)) firework_Parament->le_State = SETTING;	//已经完成本轮变换，需要重新设置
			}
			else
			{
				//计算本轮输出参数
				brightness_Err = brightness_Set - brightness_Out;	//计算亮度差值
				brightness_Out += LIGHT_P*brightness_Err;//累计亮度差值到输出
				color_Temperature_Out = color_Temperature_Set;
				//获得实际输出比例
				light_Effect_Analysis(&brightness_Out, &color_Temperature_Out, &(firework_Parament->cold_Percentage), &(firework_Parament->warm_Percentage));
				//根据频率设置延迟
				osDelay(30/freq_Set); //最大周期长度为(30+1)*136ms
				if((fabsf(brightness_Err)<=0.001)&&(abs(color_Temperature_Err)<=50)) firework_Parament->le_State = SETTING;	//已经完成本轮变换，需要重新设置
			}

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
 