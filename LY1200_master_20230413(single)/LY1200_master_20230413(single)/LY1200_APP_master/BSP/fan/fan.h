#ifndef FAN_H_
#define FAN_H_

#include "stdio.h"
#include "stdint.h"

//该逻辑遵循CMSIS_RTOS2标识符逻辑
#define thisOK 0
#define thisERROR -1

struct FAN
{
    /* data */
    uint8_t fan_Ratio;//风扇转速：0x00-0x64
};


#endif  // FAN_H_