#ifndef __TOUCHGFX_USER__H
#define __TOUCHGFX_USER__H

#include "TFT_LCD.h"

//#include "tim.h"
#include "cmsis_os.h"
#include "main.h"

extern osMessageQueueId_t xQueueLCDHandle;
//extern const osMessageQueueAttr_t xQueueLCD_attributes;
extern void DisplayDriver_TransferCompleteCallback(void);
int touchgfxDisplayDriverTransmitActive();
void touchgfxDisplayDriverTransmitBlock(const uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

typedef struct
{
  const uint8_t *pixels;
  uint16_t x;
  uint16_t y;
  uint16_t w;
  uint16_t h;
}_st_lcd;

//extern osThreadId_t Start_UpdateLcdTaskHandle;
//extern const osThreadAttr_t Start_UpdateLcdTask_attributes;

//void Start_UpdateLcdTask(void * argument);
#endif

