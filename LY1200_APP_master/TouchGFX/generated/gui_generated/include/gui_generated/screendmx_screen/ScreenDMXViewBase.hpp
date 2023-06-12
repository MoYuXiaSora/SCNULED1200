/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREENDMXVIEWBASE_HPP
#define SCREENDMXVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screendmx_screen/ScreenDMXPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/Image.hpp>

class ScreenDMXViewBase : public touchgfx::View<ScreenDMXPresenter>
{
public:
    ScreenDMXViewBase();
    virtual ~ScreenDMXViewBase();
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
    touchgfx::Image image1;
    touchgfx::Image image1_1;
    touchgfx::Box box_0;
    touchgfx::Box box_1;
    touchgfx::TextArea textArea2;
    touchgfx::TextArea textArea2_1;

private:

};

#endif // SCREENDMXVIEWBASE_HPP
