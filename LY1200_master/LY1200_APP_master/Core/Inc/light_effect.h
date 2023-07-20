#ifndef LIGHTEFFECTS_H_
#define LIGHTEFFECTS_H_

#include "stdio.h"
#include "stdint.h"

//该逻辑遵循CMSIS_RTOS2标识符逻辑
#define thisOK 0
#define thisERROR -1

#define FLAG_TRUE 1
#define FLAG_FALSE 0

enum LIGHTEFFECTS_TYPE
{
    FAULT,               //故障
    EXPLODE,             //爆炸
	  FIREWORK,            //烟花
	  STROBE,              //闪光灯
    LIGHTNING,           //闪电
    PAPARAZZI,           //派对
		WELD,                //电焊
		TV,                  //电视
	  FIRE,                //火焰  
    BREATH,              //呼吸  
    CLOUND,              //云朵	
    LT_MAX,
};


struct LIGHTEFFECTS
{   
		/* input data */
    uint8_t type;//灯效类型
    uint8_t le_State; //特效状态
    uint8_t le_Update_Flag; //是否有新参数更新
    float brightness;//灯效亮度 0.0%-100.0%
    uint16_t color_Temperature;//灯效色温 2700-6500
    uint8_t freq;//灯效频率 1 - 10 R（自动）
	
		/* output data */
    float cold_Percentage;  //冷色温输出结果 0.0%-100.0%
    float warm_Percentage;  //暖色温输出结果 0.0%-100.0%

};

enum STATUE
{
    SETTING,              //设置参数模式
    CARRY_OUT,            //执行输出模式
    DELAY                 //输出等待模式
    
};

uint8_t lighteffects_Type_Choose(struct LIGHTEFFECTS *lighteffects_Parament_local);

#endif  // LIGHTEFFECTS_H_
