#ifndef __KEYCONTROLLER_HPP__
#define __KEYCONTROLLER_HPP__

#include <platform/driver/Button/ButtonController.hpp> //需要继承基类（抽象类）

namespace touchgfx 
{
	class KeyController : public  ButtonController 
	{
		public:
		KeyController(){}
		virtual ~KeyController (){}
				
		virtual void init();
		virtual bool sample(uint8_t& key); 
	};
}

#endif