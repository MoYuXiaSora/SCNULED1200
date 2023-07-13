/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREENCURVEVIEWBASE_HPP
#define SCREENCURVEVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screencurve_screen/ScreenCurvePresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/BoxWithBorder.hpp>

class ScreenCurveViewBase : public touchgfx::View<ScreenCurvePresenter>
{
public:
    ScreenCurveViewBase();
    virtual ~ScreenCurveViewBase();
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
    touchgfx::BoxWithBorder box_0;
    touchgfx::BoxWithBorder box_1;
    touchgfx::BoxWithBorder box_2;
    touchgfx::BoxWithBorder box_3;
    touchgfx::TextArea textArea2;
    touchgfx::TextArea textArea2_2;
    touchgfx::TextArea textArea2_3;
    touchgfx::TextArea textArea2_1;
    touchgfx::Box box2_0;
    touchgfx::Box box2_1;
    touchgfx::Box box2_2;
    touchgfx::Box box2_3;

private:

};

#endif // SCREENCURVEVIEWBASE_HPP
