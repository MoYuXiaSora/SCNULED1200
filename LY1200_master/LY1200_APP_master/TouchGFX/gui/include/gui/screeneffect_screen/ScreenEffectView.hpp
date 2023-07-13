#ifndef SCREENEFFECTVIEW_HPP
#define SCREENEFFECTVIEW_HPP

#include <gui_generated/screeneffect_screen/ScreenEffectViewBase.hpp>
#include <gui/screeneffect_screen/ScreenEffectPresenter.hpp>
extern uint8_t MenuLevel ;//全局变量
extern uint8_t EffectType;//记录选中特效编号0-7.
class ScreenEffectView : public ScreenEffectViewBase
{
public:
    ScreenEffectView();
    virtual ~ScreenEffectView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
		virtual void handleKeyEvent(uint8_t key);//声明
		virtual void hideBox();
protected:
};

#endif // SCREENEFFECTVIEW_HPP
