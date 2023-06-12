#ifndef SCREENMENUVIEW_HPP
#define SCREENMENUVIEW_HPP

#include <gui_generated/screenmenu_screen/ScreenMenuViewBase.hpp>
#include <gui/screenmenu_screen/ScreenMenuPresenter.hpp>
extern uint8_t MenuLevel ;//全局变量
class ScreenMenuView : public ScreenMenuViewBase
{
public:
    ScreenMenuView();
    virtual ~ScreenMenuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
		virtual void handleKeyEvent(uint8_t key);//声明
		virtual void hideBox();
protected:
};

#endif // SCREENMENUVIEW_HPP
