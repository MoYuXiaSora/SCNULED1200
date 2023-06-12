#ifndef __KNOBCONTROLLER_HPP__
#define __KNOBCONTROLLER_HPP__
 
#include <platform/driver/Button/ButtonController.hpp> 

namespace touchgfx 
{
	class KnobController : public  ButtonController 
	{
		public:
			
		KnobController(){}
		virtual ~KnobController (){}
				
		virtual void init();
		virtual bool sample(uint8_t& key); 
	};
}

#endif