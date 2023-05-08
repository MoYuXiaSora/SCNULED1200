/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN1VIEWBASE_HPP
#define SCREEN1VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/containers/progress_indicators/CircleProgress.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class Screen1ViewBase : public touchgfx::View<Screen1Presenter>
{
public:
    Screen1ViewBase();
    virtual ~Screen1ViewBase();
    virtual void setupScreen();
    virtual void handleKeyEvent(uint8_t key);

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box box1;
    touchgfx::TextArea textArea1;
    touchgfx::TextArea textArea2;
    touchgfx::TextArea textArea3;
    touchgfx::CircleProgress LightingProgress;
    touchgfx::PainterRGB565 LightingProgressPainter;
    touchgfx::CircleProgress TemperatureProgress;
    touchgfx::PainterRGB565 TemperatureProgressPainter;
    touchgfx::TextAreaWithOneWildcard TemperatureTextPg;
    touchgfx::TextAreaWithOneWildcard LightTextPg;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEMPERATURETEXTPG_SIZE = 5;
    touchgfx::Unicode::UnicodeChar TemperatureTextPgBuffer[TEMPERATURETEXTPG_SIZE];
    static const uint16_t LIGHTTEXTPG_SIZE = 8;
    touchgfx::Unicode::UnicodeChar LightTextPgBuffer[LIGHTTEXTPG_SIZE];

private:

    /*
     * Canvas Buffer Size
     */
    static const uint32_t CANVAS_BUFFER_SIZE = 7200;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

};

#endif // SCREEN1VIEWBASE_HPP
