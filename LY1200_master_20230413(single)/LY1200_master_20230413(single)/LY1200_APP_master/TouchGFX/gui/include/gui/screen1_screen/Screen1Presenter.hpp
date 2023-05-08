#ifndef SCREEN1PRESENTER_HPP
#define SCREEN1PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen1View;

class Screen1Presenter : public touchgfx::Presenter, public ModelListener//继承了ModelListener类
{
public:
	 Screen1Presenter(Screen1View& v);//构造函数以view指针为入参

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

//可以重写虚函数？？？ 通知view应更新显示的数值CCT_L...外部向UI传值

    //从视图访问模型中的数据，加载保存模型中的数据
    void saveCCTTemperature(int CCT_Temperature_count)
		{
			model->saveCCTTemperature(CCT_Temperature_count);
		}
		
		void saveCCTLight(int CCT_Light_count)
		{
			 model->saveCCTLight(CCT_Light_count);
		}
		
		int getCCTTemperature()
		{
		  return model->getCCTTemperature();
		}
		int getCCTLight()
		{
			return model->getCCTLight();
		}
		
		
		

    virtual ~Screen1Presenter() {};

private:
    Screen1Presenter();

    Screen1View& view;
};

#endif // SCREEN1PRESENTER_HPP
