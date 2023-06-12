#ifndef SCREENSTUDIOVIEW_HPP
#define SCREENSTUDIOVIEW_HPP

#include <gui_generated/screenstudio_screen/ScreenStudioViewBase.hpp>
#include <gui/screenstudio_screen/ScreenStudioPresenter.hpp>
extern uint8_t MenuLevel;//此层=1 即第二层
class ScreenStudioView : public ScreenStudioViewBase
{
public:
    ScreenStudioView();
    virtual ~ScreenStudioView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
		virtual void handleKeyEvent(uint8_t);//
protected:
};

#endif // SCREENSTUDIOVIEW_HPP
