#ifndef __KEYCONTROLLER_HPP__
#define __KEYCONTROLLER_HPP__

#include <platform/driver/Button/ButtonController.hpp> //需要继承基类（抽象类）

namespace touchgfx 
{
//	extern int component_Location;//组件位置i
//	extern int tier_Location;//层级位置j
//	//extern int Knob_Pressed;//按下标志
//	extern int Screen_id;//界面标识
	
	class KeyController : public  ButtonController 
	{
		public:
			KeyController(){}
		virtual ~KeyController (){}
				
		virtual void init();
		virtual bool sample(uint8_t& key); 
	};
}
//int My_Place();//声明计算显示位置

#endif