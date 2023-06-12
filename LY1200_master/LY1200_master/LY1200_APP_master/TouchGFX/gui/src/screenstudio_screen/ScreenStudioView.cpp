#include <gui/screenstudio_screen/ScreenStudioView.hpp>
#include "math.h"
#include "control_box.h"

 //层级为第二层=1； 0，1，2，3，4 数组索引
extern "C"
{	
	uint32_t StucheckFinalCal(uint8_t Levels[]){	
			uint32_t sore = 0x00000|(Levels[4]<<16)|(Levels[3])<<12|(Levels[2]<<8)|(Levels[1]<<4)|(Levels[0]);
		return 0x00000|(Levels[4]<<16)|(Levels[3])<<12|(Levels[2]<<8)|(Levels[1]<<4)|(Levels[0]);
	}	
	uint64_t StucalVarition (uint8_t GFXKeys, uint8_t Levels[]){ //按键对应的值取高位进行case
		switch ((GFXKeys&0xF0)>>4){
			case 0x00:
				return StucheckFinalCal(Levels);
			
//			case 0x06:
//				Levels[MenuLevel+1] = 1;
//			  MenuLevel+=1;//层级加1 为2
//				return StucheckFinalCal(Levels);
			case 0x07:
				Levels[MenuLevel]=0x00;//将该层数组值置为0 该层00000.
			  MenuLevel=0;				
				return 0x00003;//返回menu
			case 0x08:
				Levels[MenuLevel]=0x00;//将该层数组值置为0 
			  MenuLevel=0;
			  Levels[0]=0x00; 
				return 0x0000d;//直接去cct界面
      case 0x09:
				Levels[MenuLevel]=0x00;//将该层数组值置为0 该层00003.
			  MenuLevel=0;
			  Levels[0]=0x00; //该层00000
				return 0x0000e;//直接去effect界面	
     						
			case 0x0a:
				Levels[MenuLevel]=0;//MenuLevel=1 
			  MenuLevel-=1;		
			  return StucheckFinalCal(Levels);//0x00003//返回menu
			default:
				return StucheckFinalCal(Levels) ;
		}
	}
}

ScreenStudioView::ScreenStudioView()
{

}

void ScreenStudioView::setupScreen()
{
    ScreenStudioViewBase::setupScreen();
}

void ScreenStudioView::tearDownScreen()
{
    ScreenStudioViewBase::tearDownScreen();
}

void ScreenStudioView::handleKeyEvent(uint8_t key)
{
	  ScreenMenuNumberGFX=StucalVarition (key,GFXLevels);
	  switch (ScreenMenuNumberGFX)  //这里屏幕转换要添加方框清0
   { 
		case 0x00013:
		  box_0.setVisible(true);
			box_0.invalidate();
		break;
		//back 或者menu键
		case 0x00003://计算：使L(1)=0 层级menuLevel-1
		    application().gotoScreenMenuScreenNoTransition();
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