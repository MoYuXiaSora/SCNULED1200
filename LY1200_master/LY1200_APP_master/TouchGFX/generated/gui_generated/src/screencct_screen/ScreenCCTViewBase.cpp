/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screencct_screen/ScreenCCTViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

ScreenCCTViewBase::ScreenCCTViewBase()
{
    __background.setPosition(0, 0, 480, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_R_ID));
    add(image1);
}

ScreenCCTViewBase::~ScreenCCTViewBase()
{

}

void ScreenCCTViewBase::setupScreen()
{

}
