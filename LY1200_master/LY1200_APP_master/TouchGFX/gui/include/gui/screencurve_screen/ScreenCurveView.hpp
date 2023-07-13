#ifndef SCREENCURVEVIEW_HPP
#define SCREENCURVEVIEW_HPP

#include <gui_generated/screencurve_screen/ScreenCurveViewBase.hpp>
#include <gui/screencurve_screen/ScreenCurvePresenter.hpp>
extern uint8_t MenuLevel ;//全局变量  此层为1
class ScreenCurveView : public ScreenCurveViewBase
{
public:
    ScreenCurveView();
    virtual ~ScreenCurveView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
		virtual void handleKeyEvent(uint8_t key);//声明
		virtual void hideBox();
protected:
};

#endif // SCREENCURVEVIEW_HPP
