/**
  ******************************************************************************
  * File Name          : TouchGFXGeneratedHAL.cpp
  ******************************************************************************
  * This file is generated by TouchGFX Generator 4.21.1. Please, do not edit!
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

#include <TouchGFXGeneratedHAL.hpp>
#include <touchgfx/hal/OSWrappers.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/hal/PaintImpl.hpp>
#include <touchgfx/hal/PaintRGB565Impl.hpp>

#include <touchgfx/widgets/canvas/CWRVectorRenderer.hpp>

namespace touchgfx
{
VectorRenderer* VectorRenderer::getInstance()
{
    static CWRVectorRendererRGB565 renderer;

    return &renderer;
}
} // namespace touchgfx

#include "stm32f4xx.h"

using namespace touchgfx;

void TouchGFXGeneratedHAL::initialize()
{
    HAL::initialize();
    registerEventListener(*(Application::getInstance()));
    setFrameBufferStartAddresses((void*)0x60000000, (void*)0, (void*)0);
}

void TouchGFXGeneratedHAL::configureInterrupts()
{
}

void TouchGFXGeneratedHAL::enableInterrupts()
{
}

void TouchGFXGeneratedHAL::disableInterrupts()
{
}

void TouchGFXGeneratedHAL::enableLCDControllerInterrupt()
{
}

bool TouchGFXGeneratedHAL::beginFrame()
{
    return HAL::beginFrame();
}

void TouchGFXGeneratedHAL::endFrame()
{
    HAL::endFrame();
}

uint16_t* TouchGFXGeneratedHAL::getTFTFrameBuffer() const
{
    //getTFTFrameBuffer() not used for selected Frame Buffer Strategy
    return 0;
}

void TouchGFXGeneratedHAL::setTFTFrameBuffer(uint16_t* adr)
{
    //setTFTFrameBuffer() not used for selected display interface
}

void TouchGFXGeneratedHAL::flushFrameBuffer(const touchgfx::Rect& rect)
{
    HAL::flushFrameBuffer(rect);
}

bool TouchGFXGeneratedHAL::blockCopy(void* RESTRICT dest, const void* RESTRICT src, uint32_t numBytes)
{
    return HAL::blockCopy(dest, src, numBytes);
}

/**
  * STM32 FMC Interface
  *  - Base Address           : 0x60000000
  *  - Bank Size              : 0x04000000
  *  - Bank ID                : 4
  *  - Bank Register Address  : 0x6C000000
  *  - Bank Memory Address    : 0x6C000080
  *  - Data Size              : 16 bits
  */
extern "C" {
    /**
     * @brief LCD constroller REG and RAM addresses
     */
#define FMC_BANK4_REG ((uint16_t *) 0x6C000000)
#define FMC_BANK4_MEM ((uint16_t *) 0x6C000080)

    /**
      * @brief  Writes register address.
      * @param  Reg: Register to be written
      */
    __STATIC_INLINE void FMC_BANK4_WriteReg(uint8_t Reg)
    {
        /* Write 16-bits Index, then write register */
        *FMC_BANK4_REG = Reg;
        __DSB();
    }

    /**
      * @brief  Writes register value.
      * @param  Data: Data to be written
      */
    __STATIC_INLINE void FMC_BANK4_WriteData(uint16_t Data)
    {
        /* Write 16-bits Reg */
        *FMC_BANK4_MEM = Data;
        __DSB();
    }

    /**
      * @brief  Reads register value.
      * @retval Read value
      */
    __STATIC_INLINE uint16_t FMC_BANK4_ReadData(void)
    {
        return *FMC_BANK4_MEM;
    }

    /********************************* LINK LCD ***********************************/
    /**
      * @brief  Initialize the LCD IO.
      * @param  None
      * @retval None
      */
    __weak void LCD_IO_Init(void)
    {
        // Already Done by MX_FMC_Init()
    }

    /**
      * @brief  Writes data on LCD data register.
      * @param  Data: Data to be written
      * @retval None
      */
    __weak void LCD_IO_WriteData(uint16_t RegValue)
    {
        /* Write 16-bits Reg */
        FMC_BANK4_WriteData(RegValue);
    }

    /**
      * @brief  Writes several data on LCD data register.
      * @param  Data: pointer on data to be written
      * @param  Size: data amount in 16bits short unit
      * @retval None
      */
    __weak void LCD_IO_WriteMultipleData(uint16_t* pData, uint32_t Size)
    {
        uint32_t  i;

        for (i = 0; i < Size; i++)
        {
            FMC_BANK4_WriteData(pData[i]);
        }
    }

    /**
      * @brief  Writes register on LCD register.
      * @param  Reg: Register to be written
      * @retval None
      */
    __weak void LCD_IO_WriteReg(uint8_t Reg)
    {
        /* Write 16-bits Index, then Write Reg */
        FMC_BANK4_WriteReg(Reg);
    }

    /**
      * @brief  Reads data from LCD data register.
      * @param  None
      * @retval Read data.
      */
    __weak uint16_t LCD_IO_ReadData(void)
    {
        return FMC_BANK4_ReadData();
    }

    /**
      * @brief  LCD delay
      * @param  Delay: Delay in ms
      * @retval None
      */
    __weak void LCD_IO_Delay(uint32_t Delay)
    {
        HAL_Delay(Delay);
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
