#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
//extern uint8_t MenuLevel ;//全局变量
class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
		virtual void handleKeyEvent(uint8_t key);//声明
		virtual void LightDown();
		virtual void LightUp();//声明亮度大小升降的两个函数
		virtual void TemperatureUp();
		virtual void TemperatureDown();	
protected:
	 int Light_count;
   int Temperature_count;
};

#endif // SCREEN1VIEW_HPP
