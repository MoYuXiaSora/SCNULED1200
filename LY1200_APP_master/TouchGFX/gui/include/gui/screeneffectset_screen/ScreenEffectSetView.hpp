#ifndef SCREENEFFECTSETVIEW_HPP
#define SCREENEFFECTSETVIEW_HPP

#include <gui_generated/screeneffectset_screen/ScreenEffectSetViewBase.hpp>
#include <gui/screeneffectset_screen/ScreenEffectSetPresenter.hpp>
extern uint8_t MenuLevel ;//全局变量 effectset层的层级=1
//extern uint8_t EffectType;//特效类别标志位 全局 不写多于
class ScreenEffectSetView : public ScreenEffectSetViewBase
{
public:
    ScreenEffectSetView();
    virtual ~ScreenEffectSetView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
		virtual void handleKeyEvent(uint8_t key);//声明
		virtual void LightDown();
		virtual void LightUp();//声明亮度大小升降的两个函数
		virtual void TemperatureUp();
		virtual void TemperatureDown();	
		virtual void FrequencyUp();
		virtual void FrequencyDown();
		virtual void GetEffectType(uint8_t ViewEffectType);//更新Get特效类型下的数值
		virtual void SaveEffectType(uint8_t ViewEffectType);//save
protected:
	 int Light_count;
   int Temperature_count;
   int Frequency_count;
};

#endif // SCREENEFFECTSETVIEW_HPP
