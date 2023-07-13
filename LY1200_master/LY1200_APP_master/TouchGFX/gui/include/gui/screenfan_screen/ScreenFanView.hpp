#ifndef SCREENFANVIEW_HPP
#define SCREENFANVIEW_HPP

#include <gui_generated/screenfan_screen/ScreenFanViewBase.hpp>
#include <gui/screenfan_screen/ScreenFanPresenter.hpp>
extern uint8_t MenuLevel;// MenuLevel=1
class ScreenFanView : public ScreenFanViewBase
{
public:
    ScreenFanView();
    virtual ~ScreenFanView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
		virtual void handleKeyEvent(uint8_t);
		virtual void hideBox();
protected:
};

#endif // SCREENFANVIEW_HPP
