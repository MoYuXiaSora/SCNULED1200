#ifndef SCREENLANGUAGEVIEW_HPP
#define SCREENLANGUAGEVIEW_HPP

#include <gui_generated/screenlanguage_screen/ScreenLanguageViewBase.hpp>
#include <gui/screenlanguage_screen/ScreenLanguagePresenter.hpp>

extern uint8_t MenuLevel;
class ScreenLanguageView : public ScreenLanguageViewBase
{
public:
    ScreenLanguageView();
    virtual ~ScreenLanguageView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
		virtual void handleKeyEvent(uint8_t);
protected:
};

#endif // SCREENLANGUAGEVIEW_HPP
