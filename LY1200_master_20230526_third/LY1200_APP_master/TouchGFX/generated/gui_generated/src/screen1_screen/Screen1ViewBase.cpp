/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <images/BitmapDatabase.hpp>

Screen1ViewBase::Screen1ViewBase()
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 480, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    box1.setPosition(0, 0, 480, 320);
    box1.setColor(touchgfx::Color::getColorFromRGB(41, 36, 36));
    add(box1);

    textArea1.setXY(214, 13);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_VFHT));
    add(textArea1);

    textArea2.setXY(56, 43);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_80PN));
    add(textArea2);

    textArea3.setXY(309, 43);
    textArea3.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea3.setLinespacing(0);
    textArea3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_CP7Q));
    add(textArea3);

    LightingProgress.setXY(17, 96);
    LightingProgress.setProgressIndicatorPosition(0, 0, 190, 190);
    LightingProgress.setRange(0, 100, 100, 0);
    LightingProgress.setCenter(95, 95);
    LightingProgress.setRadius(85);
    LightingProgress.setLineWidth(20);
    LightingProgress.setStartEndAngle(0, 360);
    LightingProgress.setCapPrecision(180);
    LightingProgress.setBackground(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_CIRCLEPROGRESS_BACKGROUNDS_LARGE_ID));
    LightingProgressPainter.setColor(touchgfx::Color::getColorFromRGB(149, 225, 230));
    LightingProgress.setPainter(LightingProgressPainter);
    LightingProgress.setValue(15);
    add(LightingProgress);

    TemperatureProgress.setXY(267, 113);
    TemperatureProgress.setProgressIndicatorPosition(0, 0, 184, 94);
    TemperatureProgress.setRange(2700, 6500, 76, 0);
    TemperatureProgress.setCenter(91.8f, 92.8f);
    TemperatureProgress.setRadius(83);
    TemperatureProgress.setLineWidth(15.5f);
    TemperatureProgress.setStartEndAngle(-90, 90);
    TemperatureProgress.setCapPrecision(180);
    TemperatureProgress.setBackground(touchgfx::Bitmap(BITMAP_DARK_PROGRESSINDICATORS_BG_LARGE_CIRCLE_INDICATOR_BG_LINE_HALF_ID));
    TemperatureProgressPainter.setColor(touchgfx::Color::getColorFromRGB(219, 185, 31));
    TemperatureProgress.setPainter(TemperatureProgressPainter);
    TemperatureProgress.setValue(2700);
    add(TemperatureProgress);

    TemperatureTextPg.setXY(328, 184);
    TemperatureTextPg.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    TemperatureTextPg.setLinespacing(0);
    Unicode::snprintf(TemperatureTextPgBuffer, TEMPERATURETEXTPG_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_7APG).getText());
    TemperatureTextPg.setWildcard(TemperatureTextPgBuffer);
    TemperatureTextPg.resizeToCurrentText();
    TemperatureTextPg.setTypedText(touchgfx::TypedText(T___SINGLEUSE_QIPC));
    add(TemperatureTextPg);

    LightTextPg.setXY(69, 174);
    LightTextPg.setColor(touchgfx::Color::getColorFromRGB(255, 247, 247));
    LightTextPg.setLinespacing(10);
    Unicode::snprintf(LightTextPgBuffer, LIGHTTEXTPG_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_1NZU).getText());
    LightTextPg.setWildcard(LightTextPgBuffer);
    LightTextPg.resizeToCurrentText();
    LightTextPg.setTypedText(touchgfx::TypedText(T___SINGLEUSE_ZI7U));
    add(LightTextPg);
}

Screen1ViewBase::~Screen1ViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void Screen1ViewBase::setupScreen()
{

}

void Screen1ViewBase::handleKeyEvent(uint8_t key)
{
    if(3 == key)
    {
        //Interaction1
        //When hardware button 3 clicked change screen to ScreenMenu
        //Go to ScreenMenu with no screen transition
        application().gotoScreenMenuScreenNoTransition();
    
    }
}