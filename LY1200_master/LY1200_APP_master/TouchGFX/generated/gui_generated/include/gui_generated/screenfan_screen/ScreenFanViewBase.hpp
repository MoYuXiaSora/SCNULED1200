/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREENFANVIEWBASE_HPP
#define SCREENFANVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screenfan_screen/ScreenFanPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/SVGImage.hpp>

class ScreenFanViewBase : public touchgfx::View<ScreenFanPresenter>
{
public:
    ScreenFanViewBase();
    virtual ~ScreenFanViewBase();
    virtual void setupScreen();

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
    touchgfx::TextArea textArea2_1;
    touchgfx::TextArea textArea2_2;
    touchgfx::TextArea textArea2_3;
    touchgfx::SVGImage svgbg_0;
    touchgfx::SVGImage svgbg_1;
    touchgfx::SVGImage svgbg_2;
    touchgfx::SVGImage svgbg_3;
    touchgfx::SVGImage box_0;
    touchgfx::SVGImage box_1;
    touchgfx::SVGImage box_2;
    touchgfx::SVGImage box_3;
    touchgfx::SVGImage svgimage;
    touchgfx::SVGImage svgimage_1;
    touchgfx::SVGImage svgimage_2;
    touchgfx::SVGImage svgimage_3;

private:

    /*
     * Canvas Buffer Size
     */
    static const uint32_t CANVAS_BUFFER_SIZE = 7200;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

};

#endif // SCREENFANVIEWBASE_HPP
