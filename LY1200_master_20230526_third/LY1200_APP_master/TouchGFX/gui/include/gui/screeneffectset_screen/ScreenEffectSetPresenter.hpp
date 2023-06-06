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
    //从视图访问模型中的数据，加载保存模型中的数据badBulbs
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
		
    //从视图访问模型中的数据，加载保存模型中的数据 firework
    void savePfireworkTemperature(int firework_Temperature)
		{
			model->saveMfireworkTemperature(firework_Temperature);
		}		
    void savePfireworkLight(int firework_Light)
		{
			model->saveMfireworkLight(firework_Light);
		}	
    void savePfireworkFrequency(int firework_Frequency)
		{
			model->saveMfireworkFrequency(firework_Frequency);
		}	
	
		
		int getPfireworkTemperature()
		{
		  return model->getMfireworkTemperature();
		}
		int getPfireworkLight()
		{
			return model->getMfireworkLight();
		}				
		int getPfireworkFrequency()
		{
		  return model->getMfireworkFrequency();
		}

    //从视图访问模型中的数据，加载保存模型中的数据 flash
    void savePflashTemperature(int flash_Temperature)
		{
			model->saveMflashTemperature(flash_Temperature);
		}		
    void savePflashLight(int flash_Light)
		{
			model->saveMflashLight(flash_Light);
		}	
    void savePflashFrequency(int flash_Frequency)
		{
			model->saveMflashFrequency(flash_Frequency);
		}	
	
		
		int getPflashTemperature()
		{
		  return model->getMflashTemperature();
		}
		int getPflashLight()
		{
			return model->getMflashLight();
		}				
		int getPflashFrequency()
		{
		  return model->getMflashFrequency();
		}
		
		
    //从视图访问模型中的数据，加载保存模型中的数据 lighting
    void savePlightingTemperature(int lighting_Temperature)
		{
			model->saveMlightingTemperature(lighting_Temperature);
		}		
    void savePlightingLight(int lighting_Light)
		{
			model->saveMlightingLight(lighting_Light);
		}	
    void savePlightingFrequency(int lighting_Frequency)
		{
			model->saveMlightingFrequency(lighting_Frequency);
		}	
	
		
		int getPlightingTemperature()
		{
		  return model->getMlightingTemperature();
		}
		int getPlightingLight()
		{
			return model->getMlightingLight();
		}				
		int getPlightingFrequency()
		{
		  return model->getMlightingFrequency();
		}	
		
    //从视图访问模型中的数据，加载保存模型中的数据 paparazzi
    void savePpaparazziTemperature(int paparazzi_Temperature)
		{
			model->saveMpaparazziTemperature(paparazzi_Temperature);
		}		
    void savePpaparazziLight(int paparazzi_Light)
		{
			model->saveMpaparazziLight(paparazzi_Light);
		}	
    void savePpaparazziFrequency(int paparazzi_Frequency)
		{
			model->saveMpaparazziFrequency(paparazzi_Frequency);
		}	
	
		
		int getPpaparazziTemperature()
		{
		  return model->getMpaparazziTemperature();
		}
		int getPpaparazziLight()
		{
			return model->getMpaparazziLight();
		}				
		int getPpaparazziFrequency()
		{
		  return model->getMpaparazziFrequency();
		}		
		
    //从视图访问模型中的数据，加载保存模型中的数据 pulse
    void savePpulseTemperature(int pulse_Temperature)
		{
			model->saveMpulseTemperature(pulse_Temperature);
		}		
    void savePpulseLight(int pulse_Light)
		{
			model->saveMpulseLight(pulse_Light);
		}	
    void savePpulseFrequency(int pulse_Frequency)
		{
			model->saveMpulseFrequency(pulse_Frequency);
		}	
	
		
		int getPpulseTemperature()
		{
		  return model->getMpulseTemperature();
		}
		int getPpulseLight()
		{
			return model->getMpulseLight();
		}				
		int getPpulseFrequency()
		{
		  return model->getMpulseFrequency();
		}		
		
    //从视图访问模型中的数据，加载保存模型中的数据 tv
    void savePtvTemperature(int tv_Temperature)
		{
			model->saveMtvTemperature(tv_Temperature);
		}		
    void savePtvLight(int tv_Light)
		{
			model->saveMtvLight(tv_Light);
		}	
    void savePtvFrequency(int tv_Frequency)
		{
			model->saveMtvFrequency(tv_Frequency);
		}	
	
		
		int getPtvTemperature()
		{
		  return model->getMtvTemperature();
		}
		int getPtvLight()
		{
			return model->getMtvLight();
		}				
		int getPtvFrequency()
		{
		  return model->getMtvFrequency();
		}		
		
		
    virtual ~ScreenEffectSetPresenter() {};

private:
    ScreenEffectSetPresenter();

    ScreenEffectSetView& view;
};

#endif // SCREENEFFECTSETPRESENTER_HPP
