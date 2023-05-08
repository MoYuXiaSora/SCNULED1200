#include <gui/screencurve_screen/ScreenCurveView.hpp>
#include "math.h"
#include "control_box.h"
#define max(x,y) ( x>y?x:y )
#define min(x,y) ( x<y?x:y )
 //层级为第二层 0，1，2，3，4 数组索引
extern "C"
{	
	uint32_t CurcheckFinalCal(uint8_t Levels[]){	
			uint32_t sore = 0x00000|(Levels[4]<<16)|(Levels[3])<<12|(Levels[2]<<8)|(Levels[1]<<4)|(Levels[0]);
		return 0x00000|(Levels[4]<<16)|(Levels[3])<<12|(Levels[2]<<8)|(Levels[1]<<4)|(Levels[0]);
	}
	uint64_t CurcalVarition (uint8_t GFXKeys, uint8_t Levels[]){ //按键对应的值取高位进行case
		switch ((GFXKeys&0xF0)>>4){
			case 0x00:
				return CurcheckFinalCal(Levels);
			case 0x01:
				Levels[MenuLevel] += (-1)*min((GFXKeys&0x0F),Levels[MenuLevel]);
				return CurcheckFinalCal(Levels);//MenuLevel=1
			case 0x02:
				Levels[MenuLevel] += (GFXKeys&0x0F);
			  Levels[MenuLevel] = min(max(Levels[MenuLevel],1),4);//转的范围，应该写成循环？
				return CurcheckFinalCal(Levels);
			
			case 0x06:
				Levels[MenuLevel+1] = 1;
			  MenuLevel+=1;//层级加1 为2
				return CurcheckFinalCal(Levels);
			case 0x07:
				Levels[MenuLevel]=0x00;//将该层数组值置为0 该层00000.
			  MenuLevel=0;				
				return 0x00001;//返回menu
			case 0x08:
				Levels[MenuLevel]=0x00;//将该层数组值置为0 该层00000.
			  MenuLevel=0;
			  Levels[0]=0x00; 
				return 0x0000d;//直接去cct界面
      case 0x09:
				Levels[MenuLevel]=0x00;//将该层数组值置为0 该层00000.
			  MenuLevel=0;
			  Levels[0]=0x00; 
				return 0x0000e;//直接去effect界面	
     						
			case 0x0a:
				Levels[MenuLevel]=0;//MenuLevel=1
			  MenuLevel-=1;		
			  return CurcheckFinalCal(Levels);//0x00001//返回menu
    	default:
				return CurcheckFinalCal(Levels) ;
		}
	}
}

ScreenCurveView::ScreenCurveView()
{

}

void ScreenCurveView::setupScreen()
{
    ScreenCurveViewBase::setupScreen();
}

void ScreenCurveView::tearDownScreen()
{
    ScreenCurveViewBase::tearDownScreen();
}
void ScreenCurveView::hideBox()
{
			  box_0.setVisible(false);
        box_0.invalidate();
				box_1.setVisible(false);
        box_1.invalidate();
		    box_2.setVisible(false);
        box_2.invalidate();
		    box_3.setVisible(false);
        box_3.invalidate();
}

void ScreenCurveView::handleKeyEvent(uint8_t key)
{
	ScreenMenuNumberGFX = CurcalVarition(key,GFXLevels);	

     switch (ScreenMenuNumberGFX)  //这里屏幕转换要添加方框清0
   {
    case 0x00011://BOX
		   	hideBox();
			  box_0.setVisible(true);
        box_0.invalidate();
		break;
    case 0x00021:
			  hideBox();
			  //Hide box Show box
				box_1.setVisible(true);
        box_1.invalidate();
		break;
    case 0x00031:
		      hideBox();
		      box_2.setVisible(true);
          box_2.invalidate();
		break;
    case 0x00041:
			    hideBox();
		      box_3.setVisible(true);
          box_3.invalidate();
		break;
		
		case 0x00001:
		     application().gotoScreenMenuScreenNoTransition();
		break;
		
		
		//knob1 pressed 
		case 0x00141:	//选中第四个组件
			    application().gotoScreen1ScreenNoTransition();
		break;
		
		//快捷键
		case 0x0000d:
			   application().gotoScreen1ScreenNoTransition();// go to cct
		break;
		case 0x0000e:
			   application().gotoScreenEffectScreenNoTransition();// go to effect
		break;
					
		
		default:
			break;
	}
}