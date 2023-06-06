#ifndef SCREENCONTROLVIEW_HPP
#define SCREENCONTROLVIEW_HPP

#include <gui_generated/screencontrol_screen/ScreenControlViewBase.hpp>
#include <gui/screencontrol_screen/ScreenControlPresenter.hpp>
extern uint8_t MenuLevel ;//全局变量 此层=1
class ScreenControlView : public ScreenControlViewBase
{
public:
    ScreenControlView();
    virtual ~ScreenControlView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
			
		virtual void handleKeyEvent(uint8_t key);//声明
			//virtual void hideBox();//该界面仅两个组件 不用重复消除
protected:
};

#endif // SCREENCONTROLVIEW_HPP
