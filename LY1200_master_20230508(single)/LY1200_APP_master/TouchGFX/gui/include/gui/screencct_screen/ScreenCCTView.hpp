#ifndef SCREENCCTVIEW_HPP
#define SCREENCCTVIEW_HPP

#include <gui_generated/screencct_screen/ScreenCCTViewBase.hpp>
#include <gui/screencct_screen/ScreenCCTPresenter.hpp>

class ScreenCCTView : public ScreenCCTViewBase
{
public:
    ScreenCCTView();
    virtual ~ScreenCCTView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREENCCTVIEW_HPP
