#include <gui/screenlanguage_screen/ScreenLanguageView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include "math.h"
#include "control_box.h"
#define max(x,y) ( x>y?x:y )
#define min(x,y) ( x<y?x:y )
 //层级为第二层=1； 0，1，2，3，4 数组索引
extern "C"
{	
	uint32_t LancheckFinalCal(uint8_t Levels[]){	
			uint32_t sore = 0x00000|(Levels[4]<<16)|(Levels[3])<<12|(Levels[2]<<8)|(Levels[1]<<4)|(Levels[0]);
		return 0x00000|(Levels[4]<<16)|(Levels[3])<<12|(Levels[2]<<8)|(Levels[1]<<4)|(Levels[0]);
	}	
	uint64_t LancalVarition (uint8_t GFXKeys, uint8_t Levels[]){ //按键对应的值取高位进行case
		switch ((GFXKeys&0xF0)>>4){
			case 0x00:
				return LancheckFinalCal(Levels);
			case 0x01:
				Levels[MenuLevel] += (-1)*min((GFXKeys&0x0F),Levels[MenuLevel]);
				return LancheckFinalCal(Levels);//MenuLevel=1
			case 0x02:
				Levels[MenuLevel] += (GFXKeys&0x0F);
			  Levels[MenuLevel] = min(max(Levels[MenuLevel],1),2);//转的范围，应该写成循环？
				return LancheckFinalCal(Levels);
			
			case 0x06:
				Levels[MenuLevel+1] = 1;
			  MenuLevel+=1;//层级加1 为2
				return LancheckFinalCal(Levels);
			
			case 0x07:
				Levels[MenuLevel]=0x00;//将该层数组值置为0 该层00000.
			  MenuLevel=0;
				return 0x00004;//返回menu
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
			  return LancheckFinalCal(Levels);//0x00004//返回menu
			default:
				return LancheckFinalCal(Levels) ;
		}
	}
}
ScreenLanguageView::ScreenLanguageView()
{

}

void ScreenLanguageView::setupScreen()
{
    ScreenLanguageViewBase::setupScreen();
}

void ScreenLanguageView::tearDownScreen()
{
    ScreenLanguageViewBase::tearDownScreen();
}
void ScreenLanguageView::handleKeyEvent(uint8_t key)
{
	ScreenMenuNumberGFX = LancalVarition(key,GFXLevels);	

     switch (ScreenMenuNumberGFX)  //这里屏幕转换要添加方框清0
   {
    case 0x00014://BOX
			  box_0.setVisible(true);
        box_0.invalidate();
				box_1.setVisible(false);
        box_1.invalidate();		 
		break;
    case 0x00024:
			  //Hide box Show box
			  box_0.setVisible(false);
        box_0.invalidate();		
				box_1.setVisible(true);
        box_1.invalidate();
		break;
		
		//back 或者menu键
		case 0x00004://计算：使L(1)=0 层级menuLevel-1
		    application().gotoScreenMenuScreenNoTransition();
		break;
		
		
		//knob1 pressed 
		case 0x00114:	//按中第一个组件 Chinese
			 Texts::setLanguage(GB);
       invalidate();
		break;
		
		case 0x00124://按中第二个组件 English
        Texts::setLanguage(EN);
        invalidate();
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