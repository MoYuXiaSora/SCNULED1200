#ifndef SCREENCONTROLPRESENTER_HPP
#define SCREENCONTROLPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenControlView;

class ScreenControlPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenControlPresenter(ScreenControlView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~ScreenControlPresenter() {};

private:
    ScreenControlPresenter();

    ScreenControlView& view;
};

#endif // SCREENCONTROLPRESENTER_HPP
