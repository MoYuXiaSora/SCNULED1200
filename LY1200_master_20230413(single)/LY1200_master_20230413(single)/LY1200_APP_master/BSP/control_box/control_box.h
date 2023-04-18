#ifndef CONTROL_BOX_H_
#define CONTROL_BOX_H_

#include "stdio.h"
#include "stdint.h"

//该逻辑遵循CMSIS_RTOS2标识符逻辑
#define thisOK 0
#define thisERROR -1

enum KNOB_NUMBER {
    ZERO=0, //
    FIRST,  //
    SECOND,  //
};

enum KNOB_DIRECTION {
    LEFT=0, //
    RIGHT,  //
};

struct KNOB
{
    /* data */
	uint8_t order_Number; //旋钮的序号
	uint8_t direction;	//旋钮旋转的方向 0为向左 1为向右
	int16_t variation;	//旋钮变化的数值
	int16_t mapping_Values;//旋钮映射后的数值
  uint8_t key_State;  		//旋钮中键状态   0为悬空 1为按下
	uint8_t knob_State;  		//旋钮旋转状态   0为距离上次读取未被旋转 1为被选转
	//int16_t i;//测试使用
};


#define KEY_STATE_SET 1
#define KEY_STATE_RESET 0
#define KNOB_STATE_SET 1
#define KNOB_STATE_RESET 0

#define KEY0_Pin_SET 0
#define KEY1_Pin_SET 1
#define KEY2_Pin_SET 2
#define KEY3_Pin_SET 3
#define KEY6_Pin_SET 6
#define KEY10_Pin_SET 10
#define KEY_UP_Pin_SET 3
#define NOKEY_VALUE -1


struct KEY
{
    /* data */
  uint8_t state;  		//按键状态 0为无按键被按下 1为存在按键被按下
	int16_t value;	//不同按键按下对应的键值
};

uint8_t knob_Input(struct KNOB *knob_local,uint8_t mapping_Values_Local);


struct BOX_INPUT
{
	struct KNOB knob1;
	struct KNOB knob2;
	struct KEY key;
};

struct KEY button_scanning();

#endif  // CONTROL_BOX_H_