#ifndef CCT_H_
#define CCT_H_

#include "stdio.h"
#include "stdint.h"

//该逻辑遵循CMSIS_RTOS2标识符逻辑
#define thisOK 0
#define thisERROR -1

enum CURVE {
    LINE=0, //直线型
    LOGARITHM,  //对数型
    INDEX,  //指数型
    S_CURVE, //S型
};

struct CCT
{
    /* data */
    float brightness; //CCT 亮度 浮点型  0.0%-100.0%
    uint16_t color_Temperature; // CCT 色温 2700-6500K
    enum CURVE curve;  //四种类型 直线型 对数型 指数型 S型
    float cold_Percentage;  //冷色温输出结果 0.0%-100.0%
    float warm_Percentage;  //暖色温输出结果 0.0%-100.0%
    
};

uint8_t cct_User(struct CCT *cct_Local_app,float *cct_Cold_Out_App, float *cct_Warm_Out_App);
uint8_t light_Effect_Analysis(float *brightness_Local, uint16_t *color_Temperature_Local, float *cold_Out_App, float *warm_Out_App);

#endif  // CCT_H_