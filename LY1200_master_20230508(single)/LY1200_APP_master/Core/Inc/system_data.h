#ifndef SYSTEM_DATA_H_
#define SYSTEM_DATA_H_

#include "stdio.h"
#include "stdint.h"

#include "bsp.h"
#include "cct.h"
#include "light_effect.h"

//该逻辑遵循CMSIS_RTOS2标识符逻辑
#define thisOK 0
#define thisERROR -1

enum CONTROL
{
    BLE,              //蓝牙模式
	  DMX512,           //DMX512模式  
    BOX,              //控制盒模式  
    
};

enum MODEL
{
    CCT,              //CCT模式
	  LIGHT_EFFECTS,    //灯效模式   
    
};

struct SYS_DATA
{
    uint8_t control_Parament;//控制模式选择
    uint8_t model_Parament;//功能模式选择

    struct CCT cct_Parament;//CCT参数
    struct LIGHTEFFECTS LE_Parament;//特效参数

    struct DRIVER_DATA driver_Parament;//驱动板参数
    struct FAN fan_Parament;//风扇参数    
};

uint8_t system_Data_Init();

#endif  // SYSTEM_DATA_H_