#ifndef SCREENDMXVIEW_HPP
#define SCREENDMXVIEW_HPP

#include <gui_generated/screendmx_screen/ScreenDMXViewBase.hpp>
#include <gui/screendmx_screen/ScreenDMXPresenter.hpp>
extern uint8_t MenuLevel;//MenuLevel=2
class ScreenDMXView : public ScreenDMXViewBase
{
public:
    ScreenDMXView();
    virtual ~ScreenDMXView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
		virtual void handleKeyEvent(uint8_t);
protected:
};

#endif // SCREENDMXVIEW_HPP
