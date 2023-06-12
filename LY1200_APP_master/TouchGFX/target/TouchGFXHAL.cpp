/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : TouchGFXHAL.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.21.1. This file is only
  * generated once! Delete this file from your project and re-generate code
  * using STM32CubeMX or change this file manually to update it.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#include <TouchGFXHAL.hpp>

/* USER CODE BEGIN TouchGFXHAL.cpp */

#include <KeyController.hpp> 
#include <KnobController.hpp> 
#include "W25Qx.h"

using namespace touchgfx;
static KeyController kc;//静�?�变�?
//static KnobController knc;

uint32_t text_i;
__IO uint16_t *ptr_get;
__IO uint16_t *ptr_last;
__IO uint32_t ptr_err;
#include <touchgfx/hal/OSWrappers.hpp>
extern "C"{
	void TouchGFXHAL_TE(void)
	{ 
			/* Unblock TouchGFX Engine Main Loop to render next frame */
			OSWrappers::signalVSync();  
	}
}

extern "C"{
	void TouchGFX_signalVSync_manual(void);
	void TouchGFX_signalVSync_manual(void)
	{ 
			/* Unblock TouchGFX Engine Main Loop to render next frame */
			//HAL::getInstance()->vSync();
			//OSWrappers::OSWrappers::giveFrameBufferSemaphoreFromISR();;
			OSWrappers::signalVSync();  
	}
}
extern "C"{
	void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//设置坐标函数
	void LCD_IO_WriteMultipleData_User(uint16_t* pData, uint32_t Size);
}
/* ******************************************************
 * Functions required by Partial Frame Buffer Strategy
 * ******************************************************
 *
 *  int touchgfxDisplayDriverTransmitActive() must return whether or not data is currently being transmitted, over e.g. SPI.
 *  void touchgfxDisplayDriverTransmitBlock(const uint8_t* pixels, uint16_t x, uint16_t y, uint16_t w, uint16_t h) will be called
 *  when the framework wants to send a block. The user must then transfer the data represented by the arguments.
 *
 *  A user must call touchgfx::startNewTransfer(); once touchgfxDisplayDriverTransmitBlock() has successfully sent a block.
 *  E.g. if using DMA to transfer the block, this could be called in the "Transfer Completed" interrupt handler.
 *
 */
#warning "A user must call touchgfx::startNewTransfer(); once touchgfxDisplayDriverTransmitBlock() has succesfully sent a block."
#warning "A user must implement C-methods touchgfxDisplayDriverTransmitActive() and touchgfxDisplayDriverTransmitBlock() used by the Partial Framebuffer Strategy."

void TouchGFXHAL::initialize()
{
    // Calling parent implementation of initialize().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.
    // Please note, HAL::initialize() must be called to initialize the framework.

    TouchGFXGeneratedHAL::initialize();
		
    Bitmap::removeCache();
    uint16_t* cacheStartAddr = (uint16_t*)0x6004B000;
    uint32_t cacheSize = 0xB5000; //741KB
    touchgfx::Bitmap::setCache(cacheStartAddr, cacheSize);
		touchgfx::Bitmap::cacheAll();
	
		kc.init ();//kc为Key Controller
	  setButtonController (&kc);
//	  knc.init ();
	  //setButtonController (&knc);
}

/**
 * Gets the frame buffer address used by the TFT controller.
 *
 * @return The address of the frame buffer currently being displayed on the TFT.
 */
uint16_t* TouchGFXHAL::getTFTFrameBuffer() const
{
    // Calling parent implementation of getTFTFrameBuffer().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    return TouchGFXGeneratedHAL::getTFTFrameBuffer();
}

/**
 * Sets the frame buffer address used by the TFT controller.
 *
 * @param [in] address New frame buffer address.
 */
void TouchGFXHAL::setTFTFrameBuffer(uint16_t* address)
{
    // Calling parent implementation of setTFTFrameBuffer(uint16_t* address).
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::setTFTFrameBuffer(address);
}

/**
 * This function is called whenever the framework has performed a partial draw.
 *
 * @param rect The area of the screen that has been drawn, expressed in absolute coordinates.
 *
 * @see flushFrameBuffer().
 */
void TouchGFXHAL::flushFrameBuffer(const touchgfx::Rect& rect)
{
    // Calling parent implementation of flushFrameBuffer(const touchgfx::Rect& rect).
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.
    // Please note, HAL::flushFrameBuffer(const touchgfx::Rect& rect) must
    // be called to notify the touchgfx framework that flush has been performed.
    // To calculate he start adress of rect,
    // use advanceFrameBufferToRect(uint8_t* fbPtr, const touchgfx::Rect& rect)
    // defined in TouchGFXGeneratedHAL.cpp

	
	
			
//			uint16_t local_w,local_h=0;//记录touchgfx瞬时渲染�?维数组指针位�?
//			uint16_t cout_w,cout_h=0;//�?部渲染数组循环计�?
//			uint16_t color16=0;//8位转16位临时存储变�?
//			uint32_t i = 0;//8位转16位key�?
//			//LCD_Address_Set(lcdinfo.x,lcdinfo.y,lcdinfo.w,lcdinfo.h+lcdinfo.y);//1.每区�? 设置光标矩形位置
//			for(cout_h=0;cout_h<lcdinfo.h;cout_h++)
//			{
//				//LCD_Address_Set(lcdinfo.x,lcdinfo.y+local_h,lcdinfo.w,lcdinfo.y+local_h);//2.每行刷新 设置光标矩形位置 兼顾性能和撕�?
//				//进行行刷�?
//				for(cout_w=0;cout_w<lcdinfo.w;cout_w++)
//				{
//					color16 = lcdinfo.pixels[i];
//					color16 |= ((uint16_t)(lcdinfo.pixels[i+1]) << 8);
//					LCD_Address_Set(lcdinfo.x+cout_w,lcdinfo.y+local_h,lcdinfo.x+cout_w,lcdinfo.y+local_h);//3.设置光标点位�? 可完美解决画面撕裂问�? 但会降低刷新速度
//					LCD_IO_WriteData(color16);
//					local_w++;
//					i += 2;
//				}
//				local_h++;
//			}
//			local_w=local_h=0;
//			

	
	__IO uint16_t *ptr;
	uint32_t height;

	//LCD_Address_Set(0,0,319,479);
	//LCD_Address_Set(rect.x,rect.y,rect.x+rect.width-1,rect.y+rect.height-1);
	
	for(height = 0;height<rect.height; height++)
	{		
		ptr = getClientFrameBuffer() + rect.x + (height + rect.y) * HAL::DISPLAY_WIDTH;

		LCD_Address_Set(rect.x,height+rect.y,rect.x+rect.width-1,rect.y+height);
		//LCD_Address_Set(0,height,479,height);
//		
		LCD_IO_WriteMultipleData_User((uint16_t *)ptr, rect.width);
//		
//		text_i=height;
		
	}
	
  TouchGFXGeneratedHAL::flushFrameBuffer(rect);
}
void* dest_test; 
bool TouchGFXHAL::blockCopy(void* RESTRICT dest, const void* RESTRICT src, uint32_t numBytes)
{

	dest_test = dest;
	
	const uint32_t ExflashStart = 0x90000000;
	const uint32_t ExflashSize = 16*1024*1024;//外置FLASH 16MB 
	uint32_t dataffset = (uint32_t)src;
	if((dataffset >= ExflashStart)&&(dataffset < ExflashStart + ExflashSize))
	{
		dataffset = dataffset - ExflashStart;
		
		while(BSP_W25Qx_Read((uint8_t *)dest, dataffset, numBytes)!=W25Qx_OK)	
		{//传输错误

		}
		return true;		
	}
	else
		return HAL::blockCopy(dest, src, numBytes);
	//return TouchGFXGeneratedHAL::blockCopy(dest, src, numBytes);
}

/**
 * Configures the interrupts relevant for TouchGFX. This primarily entails setting
 * the interrupt priorities for the DMA and LCD interrupts.
 */
void TouchGFXHAL::configureInterrupts()
{
    // Calling parent implementation of configureInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::configureInterrupts();
}

/**
 * Used for enabling interrupts set in configureInterrupts()
 */
void TouchGFXHAL::enableInterrupts()
{
    // Calling parent implementation of enableInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::enableInterrupts();
}

/**
 * Used for disabling interrupts set in configureInterrupts()
 */
void TouchGFXHAL::disableInterrupts()
{
    // Calling parent implementation of disableInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::disableInterrupts();
}

/**
 * Configure the LCD controller to fire interrupts at VSYNC. Called automatically
 * once TouchGFX initialization has completed.
 */
void TouchGFXHAL::enableLCDControllerInterrupt()
{
    // Calling parent implementation of enableLCDControllerInterrupt().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::enableLCDControllerInterrupt();
}

bool TouchGFXHAL::beginFrame()
{
    return TouchGFXGeneratedHAL::beginFrame();
}

void TouchGFXHAL::endFrame()
{
    TouchGFXGeneratedHAL::endFrame();
}

/* USER CODE END TouchGFXHAL.cpp */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
