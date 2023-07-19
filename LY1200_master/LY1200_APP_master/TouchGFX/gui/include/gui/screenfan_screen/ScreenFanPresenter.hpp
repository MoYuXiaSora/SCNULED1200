#ifndef SCREENFANPRESENTER_HPP
#define SCREENFANPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenFanView;

class ScreenFanPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenFanPresenter(ScreenFanView& v);

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

		void saveFanType(int Type)
		{
			 model->saveFanType(Type);			
		}
		
		
		int getFanType()
		{
			return model->getFanType();
		}	

    virtual ~ScreenFanPresenter() {};

private:
    ScreenFanPresenter();

    ScreenFanView& view;
};

#endif // SCREENFANPRESENTER_HPP
