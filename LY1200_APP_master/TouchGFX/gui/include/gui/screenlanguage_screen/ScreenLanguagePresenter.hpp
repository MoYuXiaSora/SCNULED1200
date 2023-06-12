#ifndef SCREENLANGUAGEPRESENTER_HPP
#define SCREENLANGUAGEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenLanguageView;

class ScreenLanguagePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenLanguagePresenter(ScreenLanguageView& v);

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

    virtual ~ScreenLanguagePresenter() {};

private:
    ScreenLanguagePresenter();

    ScreenLanguageView& view;
};

#endif // SCREENLANGUAGEPRESENTER_HPP
