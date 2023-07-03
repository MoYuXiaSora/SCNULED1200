#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
//extern uint8_t MenuLevel ;//全局变量
extern uint8_t CurveType;//调光类别标志位
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
	 float Light_count;
   float eLight_count;//由横坐标直接算出的亮度值（无理数）
   int Temperature_count ;
   float eTemperature_count;//由横坐标直接算出的色温值（无理数）

   float Light_xs;//s，利用(0-1)

   float Light_x;//exp
   float Light_xn;//归一化处理横坐标(0-ln101) Normalization

   float Light_xl;//log
   float Light_xln;//归一化处理横坐标(1-2的10次方)

   float Temperature_x;//exp
   float Temperature_xn;//归一化处理(ln2700-ln6500)

   float Temperature_xs;//s（0-1）

   float Temperature_xl; //log对数横坐标
   float Temperature_xln;//归一化处理横坐标(2的2.7-6.5次方)
   
};

#endif // SCREEN1VIEW_HPP
