#include "system_data.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

static struct SYS_DATA sys_Parament={
    .cct_Parament={
        .brightness=0.9,         //CCT 亮度 浮点型  0.0%-100.0%
        .color_Temperature=4600, // CCT 色温 2700-6500K
        .curve=S_CURVE,          //四种类型 直线型 对数型 指数型 S型
        .cold_Percentage=0,      //冷色温输出结果 0.0%-100.0%
        .warm_Percentage=0       //暖色温输出结果 0.0%-100.0%
    },
    .driver_Parament={
        .drive_State_Update=driverUPDATE, //驱动板参数更新标识符
        .drive_Switch=driverON,           //驱动板开关机参数
        .drive_Status_Code=driverOK,      //电源驱动板状态码 0x77开机状态 0x88关机状态 0xXX异常状态
        .drive_Power_Ratio=0,             //驱动板功率负载率：0x00-0x64
        .drive_Temperature=25,            //驱动板温度：0x00-0xc8
        .LED_Temperature=25               //灯板温度：
    },
    .fan_Parament={
        .fan_Ratio=0x64     //风扇转速：0x00-0x64
    }
};

struct BOX_INPUT box_Parament={
		.key={
			.state=KEY_STATE_RESET,
			.value=NOKEY_VALUE,
			.clear_Flag = CLEAR_FLAG_OFF,
		},
		.knob1={
			.order_Number=FIRST,
			.direction=RIGHT,
			.variation=0,
			.mapping_Values=0,
			.key_State=KEY_STATE_RESET,
			.knob_State=KNOB_STATE_RESET,
			.clear_Flag=CLEAR_FLAG_OFF,
		},
		.knob2={
			.order_Number=SECOND,
			.direction=RIGHT,
			.variation=0,
			.mapping_Values=0,
			.key_State=KEY_STATE_RESET,
			.knob_State=KNOB_STATE_RESET,
			.clear_Flag=CLEAR_FLAG_OFF,
		},
};

extern osMessageQueueId_t sysDataQueue_AppHandle;
extern osMessageQueueId_t boxInputQueueHandle;

uint8_t system_Data_Init()
{
	osStatus_t stat_Local;
	stat_Local=osMessageQueuePut(sysDataQueue_AppHandle, &sys_Parament,0,portMAX_DELAY);
	if(stat_Local!=osOK)
	{
		return stat_Local;
	}
	
	stat_Local=osMessageQueuePut(boxInputQueueHandle, &box_Parament,0,portMAX_DELAY);
	if(stat_Local!=osOK)
	{
		return stat_Local;
	}
	
	return stat_Local;
}