#include "TouchGFX_User.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/*
 * 根据TouchGFX局部缓存要求需要自己完成以下三个函数
 * void TouchGFXGeneratedHAL::flushFrameBuffer(const touchgfx::Rect& rect);
 * int touchgfxDisplayDriverTransmitActive()；
 * extern "C" void touchgfxSignalVSync(void);
 */
 
/*
 * 
 */ 
uint8_t Transmiting = 0;
int touchgfxDisplayDriverTransmitActive()
{
	if(Transmiting == 0)
		return 0;
	else
		return 1;
}
 
/*
 * 
 */
void touchgfxDisplayDriverTransmitBlock(const uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	const uint8_t* a =pixels;
	  _st_lcd lcdinfo = {
      .pixels = a,
      .x = x,
      .y = y,
      .w = w,
      .h = h
		   };
	
		if(osMessageQueuePut(xQueueLCDHandle,&lcdinfo,NULL,16) == osOK)
		{
			//发送成功
			//startNewTransfer();
		}
		else
		{
			//发送失败
		}
	
}

/*
 * 
 */
void lcd_update(void)
{
	_st_lcd lcdinfo;
	
	BaseType_t xresult = osMessageQueueGet(xQueueLCDHandle,(void*)&lcdinfo,NULL,portMAX_DELAY);//osMessageGet(xQueueLCD,&lcdinfo,portMAX_DELAY);
	Transmiting = 1;
	if(xresult == osOK)
	{
		
		 //普通io
			uint16_t local_w,local_h=0;//记录touchgfx瞬时渲染一维数组指针位置
			uint16_t cout_w,cout_h=0;//局部渲染数组循环计数
			uint16_t color16=0;//8位转16位临时存储变量
			uint32_t i = 0;//8位转16位key值
			//LCD_Address_Set(lcdinfo.x,lcdinfo.y,lcdinfo.w,lcdinfo.h+lcdinfo.y);//1.每区域 设置光标矩形位置
			for(cout_h=0;cout_h<lcdinfo.h;cout_h++)
			{
				//LCD_Address_Set(lcdinfo.x,lcdinfo.y+local_h,lcdinfo.w,lcdinfo.y+local_h);//2.每行刷新 设置光标矩形位置 兼顾性能和撕裂
				//进行行刷新
				for(cout_w=0;cout_w<lcdinfo.w;cout_w++)
				{
					color16 = lcdinfo.pixels[i];
					color16 |= ((uint16_t)(lcdinfo.pixels[i+1]) << 8);
					LCD_Address_Set(lcdinfo.x+cout_w,lcdinfo.y+local_h,lcdinfo.x+cout_w,lcdinfo.y+local_h);//3.设置光标点位置 可完美解决画面撕裂问题 但会降低刷新速度
					LCD_IO_WriteData(color16);
					local_w++;
					i += 2;
				}
				local_h++;
			}
			local_w=local_h=0;
			
			
		//4.此函数输出模式为16bit行模式 不可直接带入lcdinfo.pixels 要先定位光标 同时直接输出会产生画面撕裂
		//LCD_IO_WriteMultipleData(lcdinfo.pixels, lcdinfo.w*lcdinfo.h);//此函数输出模式为16bit行模式 不可直接带入lcdinfo.pixels 要先定位光标 
		
		//5.DMA模式
		//LCD_Start_DMA_Transfer(lcdinfo.x,lcdinfo.y,lcdinfo.w,lcdinfo.h+lcdinfo.y,lcdinfo.pixels);

		Transmiting = 0;
	
    //DisplayDriver_TransferCompleteCallback();
	}
}

