#ifndef SCREENEFFECTSETPRESENTER_HPP
#define SCREENEFFECTSETPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>


using namespace touchgfx;
//extern uint8_t EffectType=0;//特效类别标志位
class ScreenEffectSetView;

class ScreenEffectSetPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenEffectSetPresenter(ScreenEffectSetView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();//初始化逻辑

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();//离开时，拆解


//m要通过p与v联系
    //从视图访问模型中的数据，加载保存模型中的数据
    void savePbadBulbsTemperature(int badBulbs_Temperature)
		{
			model->saveMbadBulbsTemperature(badBulbs_Temperature);
		}		
		void savePbadBulbsLight(int badBulb_Light)
		{
			 model->saveMbadBulbsLight(badBulb_Light);
		}
		void savePbadBulbsFrequency(int badBulb_Frequency)
		{
			 model->saveMbadBulbsFrequency(badBulb_Frequency);
		}		
		
		int getPbadBulbsTemperature()
		{
		  return model->getMbadBulbsTemperature();
		}
		int getPbadBulbsLight()
		{
			return model->getMbadBulbsLight();
		}				
		int getPbadBulbsFrequency()
		{
		  return model->getMbadBulbsFrequency();
		}

		
    //从视图访问模型中的数据，加载保存模型中的数据 explode
    void savePexplodeTemperature(int explode_Temperature)
		{
			model->saveMexplodeTemperature(explode_Temperature);
		}		
    void savePexplodeLight(int explode_Light)
		{
			model->saveMexplodeLight(explode_Light);
		}	
    void savePexplodeFrequency(int explode_Frequency)
		{
			model->saveMexplodeFrequency(explode_Frequency);
		}	
	
		
		int getPexplodeTemperature()
		{
		  return model->getMexplodeTemperature();
		}
		int getPexplodeLight()
		{
			return model->getMexplodeLight();
		}				
		int getPexplodeFrequency()
		{
		  return model->getMexplodeFrequency();
		}
		
    virtual ~ScreenEffectSetPresenter() {};

private:
    ScreenEffectSetPresenter();

    ScreenEffectSetView& view;
};

#endif // SCREENEFFECTSETPRESENTER_HPP
