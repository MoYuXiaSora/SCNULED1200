/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screenmenu_screen/ScreenMenuViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include<images/SVGDatabase.hpp>

ScreenMenuViewBase::ScreenMenuViewBase()
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 480, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    box1.setPosition(0, 0, 480, 320);
    box1.setColor(touchgfx::Color::getColorFromRGB(41, 36, 36));
    add(box1);

    textArea1.setXY(208, 3);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_LNQG));
    add(textArea1);

    textArea2.setXY(47, 146);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_Q01U));
    add(textArea2);

    textArea2_1.setXY(213, 146);
    textArea2_1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2_1.setLinespacing(0);
    textArea2_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_7KP4));
    add(textArea2_1);

    textArea2_2.setXY(367, 146);
    textArea2_2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2_2.setLinespacing(0);
    textArea2_2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_O11H));
    add(textArea2_2);

    textArea2_3.setXY(39, 282);
    textArea2_3.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2_3.setLinespacing(0);
    textArea2_3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_WOHD));
    add(textArea2_3);

    textArea2_4.setXY(212, 282);
    textArea2_4.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2_4.setLinespacing(0);
    textArea2_4.setTypedText(touchgfx::TypedText(T___SINGLEUSE_MIH0));
    add(textArea2_4);

    textArea2_5.setXY(367, 282);
    textArea2_5.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2_5.setLinespacing(0);
    textArea2_5.setTypedText(touchgfx::TypedText(T___SINGLEUSE_CJDK));
    add(textArea2_5);

    svgbg_0.setSVG(SVG_BLACKB_ID);
    svgbg_0.setPosition(28, 40, 102, 101);
    svgbg_0.setScale(0.5f, 0.5f);
    svgbg_0.setImagePosition(0, 0);
    svgbg_0.setRotationCenter(0, 0);
    svgbg_0.setRotation(0);
    add(svgbg_0);

    svgbg_1.setSVG(SVG_BLACKB_ID);
    svgbg_1.setPosition(190, 40, 102, 101);
    svgbg_1.setScale(0.5f, 0.5f);
    svgbg_1.setImagePosition(0, 0);
    svgbg_1.setRotationCenter(0, 0);
    svgbg_1.setRotation(0);
    add(svgbg_1);

    svgbg_2.setSVG(SVG_BLACKB_ID);
    svgbg_2.setPosition(344, 40, 102, 101);
    svgbg_2.setScale(0.5f, 0.5f);
    svgbg_2.setImagePosition(0, 0);
    svgbg_2.setRotationCenter(0, 0);
    svgbg_2.setRotation(0);
    add(svgbg_2);

    svgbg_3.setSVG(SVG_BLACKB_ID);
    svgbg_3.setPosition(22, 178, 102, 101);
    svgbg_3.setScale(0.5f, 0.5f);
    svgbg_3.setImagePosition(0, 0);
    svgbg_3.setRotationCenter(0, 0);
    svgbg_3.setRotation(0);
    add(svgbg_3);

    svgbg_4.setSVG(SVG_BLACKB_ID);
    svgbg_4.setPosition(190, 178, 102, 101);
    svgbg_4.setScale(0.5f, 0.5f);
    svgbg_4.setImagePosition(0, 0);
    svgbg_4.setRotationCenter(0, 0);
    svgbg_4.setRotation(0);
    add(svgbg_4);

    svgbg_5.setSVG(SVG_BLACKB_ID);
    svgbg_5.setPosition(344, 178, 102, 101);
    svgbg_5.setScale(0.5f, 0.5f);
    svgbg_5.setImagePosition(0, 0);
    svgbg_5.setRotationCenter(0, 0);
    svgbg_5.setRotation(0);
    add(svgbg_5);

    box_0.setSVG(SVG_BLUEB_ID);
    box_0.setPosition(35, 49, 92, 92);
    box_0.setScale(0.5f, 0.5f);
    box_0.setImagePosition(0, 0);
    box_0.setRotationCenter(0, 0);
    box_0.setRotation(0);
    add(box_0);

    box_1.setSVG(SVG_BLUEB_ID);
    box_1.setPosition(205, 49, 92, 92);
    box_1.setScale(0.5f, 0.5f);
    box_1.setImagePosition(0, 0);
    box_1.setRotationCenter(0, 0);
    box_1.setRotation(0);
    add(box_1);

    box_2.setSVG(SVG_BLUEB_ID);
    box_2.setPosition(353, 49, 92, 92);
    box_2.setScale(0.5f, 0.5f);
    box_2.setImagePosition(0, 0);
    box_2.setRotationCenter(0, 0);
    box_2.setRotation(0);
    add(box_2);

    box_3.setSVG(SVG_BLUEB_ID);
    box_3.setPosition(35, 184, 92, 92);
    box_3.setScale(0.5f, 0.5f);
    box_3.setImagePosition(0, 0);
    box_3.setRotationCenter(0, 0);
    box_3.setRotation(0);
    add(box_3);

    box_4.setSVG(SVG_BLUEB_ID);
    box_4.setPosition(204, 184, 92, 92);
    box_4.setScale(0.5f, 0.5f);
    box_4.setImagePosition(0, 0);
    box_4.setRotationCenter(0, 0);
    box_4.setRotation(0);
    add(box_4);

    box_5.setSVG(SVG_BLUEB_ID);
    box_5.setPosition(353, 184, 92, 92);
    box_5.setScale(0.5f, 0.5f);
    box_5.setImagePosition(0, 0);
    box_5.setRotationCenter(0, 0);
    box_5.setRotation(0);
    add(box_5);

    svgImage_0.setSVG(SVG_SETTINGS_5_FILL_ID);
    svgImage_0.setPosition(50, 64, 59, 59);
    svgImage_0.setScale(0.5f, 0.5f);
    svgImage_0.setImagePosition(0, 0);
    svgImage_0.setRotationCenter(0, 0);
    svgImage_0.setRotation(0);
    add(svgImage_0);

    svgImage_1.setSVG(SVG_LINE_CHART_FILL_ID);
    svgImage_1.setPosition(216, 64, 62, 57);
    svgImage_1.setScale(0.52f, 0.5f);
    svgImage_1.setImagePosition(0, 0);
    svgImage_1.setRotationCenter(0, 0);
    svgImage_1.setRotation(0);
    add(svgImage_1);

    svgImage_2.setSVG(SVG_WINDY_FILL_ID);
    svgImage_2.setPosition(367, 67, 62, 57);
    svgImage_2.setScale(0.52f, 0.47f);
    svgImage_2.setImagePosition(0, 0);
    svgImage_2.setRotationCenter(0, 0);
    svgImage_2.setRotation(0);
    add(svgImage_2);

    svgImage_3.setSVG(SVG_SOUND_MODULE_FILL_ID);
    svgImage_3.setPosition(50, 200, 62, 57);
    svgImage_3.setScale(0.5f, 0.5f);
    svgImage_3.setImagePosition(0, 0);
    svgImage_3.setRotationCenter(0, 0);
    svgImage_3.setRotation(0);
    add(svgImage_3);

    svgImage_4.setSVG(SVG_TRANSLATE_ID);
    svgImage_4.setPosition(215, 208, 62, 57);
    svgImage_4.setScale(0.51f, 0.5f);
    svgImage_4.setImagePosition(0, 0);
    svgImage_4.setRotationCenter(0, 0);
    svgImage_4.setRotation(0);
    add(svgImage_4);

    svgImage_5.setSVG(SVG_EXCHANGE_FUNDS_FILL_ID);
    svgImage_5.setPosition(367, 200, 62, 57);
    svgImage_5.setScale(0.52f, 0.48f);
    svgImage_5.setImagePosition(0, 0);
    svgImage_5.setRotationCenter(0, 0);
    svgImage_5.setRotation(0);
    add(svgImage_5);
}

ScreenMenuViewBase::~ScreenMenuViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void ScreenMenuViewBase::setupScreen()
{

}

void ScreenMenuViewBase::handleKeyEvent(uint8_t key)
{
    if(10 == key)
    {
        //Interaction1
        //When hardware button 10 clicked change screen to Screen1
        //Go to Screen1 with no screen transition
        application().gotoScreen1ScreenNoTransition();
    
    }

    if(11 == key)
    {
        //Interaction2
        //When hardware button 11 clicked change screen to ScreenCurve
        //Go to ScreenCurve with no screen transition
        application().gotoScreenCurveScreenNoTransition();
    
    }

    if(12 == key)
    {
        //Interaction3
        //When hardware button 12 clicked change screen to ScreenEffect
        //Go to ScreenEffect with no screen transition
        application().gotoScreenEffectScreenNoTransition();
    
    }

    if(13 == key)
    {
        //Interaction4
        //When hardware button 13 clicked change screen to ScreenControl
        //Go to ScreenControl with no screen transition
        application().gotoScreenControlScreenNoTransition();
    
    }

    if(14 == key)
    {
        //Interaction5
        //When hardware button 14 clicked change screen to ScreenFan
        //Go to ScreenFan with no screen transition
        application().gotoScreenFanScreenNoTransition();
    
    }

    if(15 == key)
    {
        //Interaction6
        //When hardware button 15 clicked change screen to ScreenStudio
        //Go to ScreenStudio with no screen transition
        application().gotoScreenStudioScreenNoTransition();
    
    }

    if(17 == key)
    {
        //Interaction7
        //When hardware button 17 clicked change screen to ScreenLanguage
        //Go to ScreenLanguage with no screen transition
        application().gotoScreenLanguageScreenNoTransition();
    
    }

    if(18 == key)
    {
        //Interaction8
        //When hardware button 18 clicked change screen to ScreenUpdate
        //Go to ScreenUpdate with no screen transition
        application().gotoScreenUpdateScreenNoTransition();
    
    }

    if(19 == key)
    {
        //Interaction9
        //When hardware button 19 clicked show box_0
        //Show box_0
        box_0.setVisible(true);
        box_0.invalidate();
    
    }
}
