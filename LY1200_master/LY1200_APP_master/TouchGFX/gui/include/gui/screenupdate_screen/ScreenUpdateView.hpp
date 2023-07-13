#ifndef SCREENUPDATEVIEW_HPP
#define SCREENUPDATEVIEW_HPP

#include <gui_generated/screenupdate_screen/ScreenUpdateViewBase.hpp>
#include <gui/screenupdate_screen/ScreenUpdatePresenter.hpp>
extern uint8_t MenuLevel;//此层=1 即第二层
class ScreenUpdateView : public ScreenUpdateViewBase
{
public:
    ScreenUpdateView();
    virtual ~ScreenUpdateView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
		virtual void handleKeyEvent(uint8_t);
protected:
};

#endif // SCREENUPDATEVIEW_HPP
