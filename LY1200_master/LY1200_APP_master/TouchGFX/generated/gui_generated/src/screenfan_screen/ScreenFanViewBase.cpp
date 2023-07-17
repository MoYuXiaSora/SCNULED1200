/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screenfan_screen/ScreenFanViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include<images/SVGDatabase.hpp>

ScreenFanViewBase::ScreenFanViewBase()
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 480, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    box1.setPosition(0, 0, 480, 320);
    box1.setColor(touchgfx::Color::getColorFromRGB(41, 36, 36));
    add(box1);

    textArea1.setXY(190, 14);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_9FOF));
    add(textArea1);

    textArea2.setXY(114, 147);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_J7D7));
    add(textArea2);

    textArea2_1.setXY(303, 146);
    textArea2_1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2_1.setLinespacing(0);
    textArea2_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_E64Y));
    add(textArea2_1);

    textArea2_2.setXY(114, 287);
    textArea2_2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2_2.setLinespacing(0);
    textArea2_2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_CZ82));
    add(textArea2_2);

    textArea2_3.setXY(303, 287);
    textArea2_3.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2_3.setLinespacing(0);
    textArea2_3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_ZZ1H));
    add(textArea2_3);

    svgbg_0.setSVG(SVG_BLACKB_ID);
    svgbg_0.setPosition(90, 41, 101, 101);
    svgbg_0.setScale(0.5f, 0.5f);
    svgbg_0.setImagePosition(0, 0);
    svgbg_0.setRotationCenter(0, 0);
    svgbg_0.setRotation(0);
    add(svgbg_0);

    svgbg_1.setSVG(SVG_BLACKB_ID);
    svgbg_1.setPosition(278, 41, 101, 101);
    svgbg_1.setScale(0.5f, 0.5f);
    svgbg_1.setImagePosition(0, 0);
    svgbg_1.setRotationCenter(0, 0);
    svgbg_1.setRotation(0);
    add(svgbg_1);

    svgbg_2.setSVG(SVG_BLACKB_ID);
    svgbg_2.setPosition(90, 176, 101, 101);
    svgbg_2.setScale(0.5f, 0.5f);
    svgbg_2.setImagePosition(0, 0);
    svgbg_2.setRotationCenter(0, 0);
    svgbg_2.setRotation(0);
    add(svgbg_2);

    svgbg_3.setSVG(SVG_BLACKB_ID);
    svgbg_3.setPosition(278, 176, 101, 101);
    svgbg_3.setScale(0.5f, 0.5f);
    svgbg_3.setImagePosition(0, 0);
    svgbg_3.setRotationCenter(0, 0);
    svgbg_3.setRotation(0);
    add(svgbg_3);

    box_0.setSVG(SVG_BLUEB_ID);
    box_0.setPosition(100, 50, 92, 92);
    box_0.setScale(0.5f, 0.5f);
    box_0.setImagePosition(0, 0);
    box_0.setRotationCenter(0, 0);
    box_0.setRotation(0);
    add(box_0);

    box_1.setSVG(SVG_BLUEB_ID);
    box_1.setPosition(287, 50, 92, 92);
    box_1.setScale(0.5f, 0.5f);
    box_1.setImagePosition(0, 0);
    box_1.setRotationCenter(0, 0);
    box_1.setRotation(0);
    add(box_1);

    box_2.setSVG(SVG_BLUEB_ID);
    box_2.setPosition(100, 183, 92, 92);
    box_2.setScale(0.5f, 0.5f);
    box_2.setImagePosition(0, 0);
    box_2.setRotationCenter(0, 0);
    box_2.setRotation(0);
    add(box_2);

    box_3.setSVG(SVG_BLUEB_ID);
    box_3.setPosition(287, 183, 92, 92);
    box_3.setScale(0.5f, 0.5f);
    box_3.setImagePosition(0, 0);
    box_3.setRotationCenter(0, 0);
    box_3.setRotation(0);
    add(box_3);

    svgimage.setSVG(SVG_WINDY_FILL_ID);
    svgimage.setPosition(110, 61, 60, 60);
    svgimage.setScale(0.5f, 0.5f);
    svgimage.setImagePosition(0, 0);
    svgimage.setRotationCenter(0, 0);
    svgimage.setRotation(0);
    add(svgimage);

    svgimage_1.setSVG(SVG_WINDY_FILL_ID);
    svgimage_1.setPosition(303, 61, 60, 60);
    svgimage_1.setScale(0.5f, 0.5f);
    svgimage_1.setImagePosition(0, 0);
    svgimage_1.setRotationCenter(0, 0);
    svgimage_1.setRotation(0);
    add(svgimage_1);

    svgimage_2.setSVG(SVG_WINDY_FILL_ID);
    svgimage_2.setPosition(110, 196, 60, 60);
    svgimage_2.setScale(0.5f, 0.5f);
    svgimage_2.setImagePosition(0, 0);
    svgimage_2.setRotationCenter(0, 0);
    svgimage_2.setRotation(0);
    add(svgimage_2);

    svgimage_3.setSVG(SVG_WINDY_FILL_ID);
    svgimage_3.setPosition(303, 196, 60, 60);
    svgimage_3.setScale(0.5f, 0.5f);
    svgimage_3.setImagePosition(0, 0);
    svgimage_3.setRotationCenter(0, 0);
    svgimage_3.setRotation(0);
    add(svgimage_3);
}

ScreenFanViewBase::~ScreenFanViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void ScreenFanViewBase::setupScreen()
{

}
