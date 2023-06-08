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
#include <touchgfx/widgets/BoxWithBorder.hpp>
#include <touchgfx/widgets/Image.hpp>

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
    touchgfx::BoxWithBorder box_0;
    touchgfx::BoxWithBorder box_1;
    touchgfx::BoxWithBorder box_2;
    touchgfx::BoxWithBorder box_3;
    touchgfx::Image image_0;
    touchgfx::Image image_1;
    touchgfx::Image image_2;
    touchgfx::Image image_3;
    touchgfx::TextArea textArea2;
    touchgfx::TextArea textArea2_1;
    touchgfx::TextArea textArea2_2;
    touchgfx::TextArea textArea2_3;

private:

};

#endif // SCREENFANVIEWBASE_HPP