#include <gui/screeneffect_screen/ScreenEffectView.hpp>
#include "math.h"
#include "control_box.h"
#define max(x,y) ( x>y?x:y )
#define min(x,y) ( x<y?x:y )

extern "C"
{	
	uint32_t EffcheckFinalCal(uint8_t Levels[]){	
			uint32_t sore = 0x00000|(Levels[4]<<16)|(Levels[3])<<12|(Levels[2]<<8)|(Levels[1]<<4)|(Levels[0]);
		return 0x00000|(Levels[4]<<16)|(Levels[3])<<12|(Levels[2]<<8)|(Levels[1]<<4)|(Levels[0]);
	}
	uint64_t EffcalVarition (uint8_t GFXKeys, uint8_t Levels[]){ //键对应的值
		switch ((GFXKeys&0xF0)>>4){
			case 0x00:
				return EffcheckFinalCal(Levels);
			case 0x01://KNOB1 MenuLevel=0
				Levels[MenuLevel] += (-1)*min((GFXKeys&0x0F),Levels[MenuLevel]);
				return EffcheckFinalCal(Levels);
			case 0x02:
				Levels[MenuLevel] += (GFXKeys&0x0F);
			  Levels[MenuLevel] = min(max(Levels[MenuLevel],0),7);//转的范围8个组件，应该写成循环？
				return EffcheckFinalCal(Levels);
			
			case 0x06:								
				Levels[MenuLevel+1] = 1;
			  MenuLevel+=1;//层级加1 则为2
			  EffectType=Levels[0];//记录选中特效编号0-7.
				return EffcheckFinalCal(Levels);
			
			case 0x07://key menu
				Levels[MenuLevel]=0;
			  return 0x0000c;		
			case 0x08://key cct
				Levels[MenuLevel]=0;
			  return 0x0000d;			
			
			case 0x0a://key back
				Levels[MenuLevel]=0;	
			  return 0x0000c;
			default:
				return EffcheckFinalCal(Levels) ;
		}
	}
}

ScreenEffectView::ScreenEffectView()
{

}

void ScreenEffectView::setupScreen()
{
    ScreenEffectViewBase::setupScreen();
}

void ScreenEffectView::tearDownScreen()
{
    ScreenEffectViewBase::tearDownScreen();
}
void ScreenEffectView::hideBox()
{
			  box_0.setVisible(false);
        box_0.invalidate();
				box_1.setVisible(false);
        box_1.invalidate();
		    box_2.setVisible(false);
        box_2.invalidate();
		    box_3.setVisible(false);
        box_3.invalidate();
		    box_4.setVisible(false);
        box_4.invalidate();
		    box_5.setVisible(false);
        box_5.invalidate();
		    box_6.setVisible(false);
        box_6.invalidate();
		    box_7.setVisible(false);
        box_7.invalidate();	     	
}

void ScreenEffectView::handleKeyEvent(uint8_t key)
{
	ScreenMenuNumberGFX = EffcalVarition(key,GFXLevels);	

     switch (ScreenMenuNumberGFX)  //这里屏幕转换要添加方框清0
   {
    case 0x00000://BOX
		   	hideBox();
			  box_0.setVisible(true);
        box_0.invalidate();
		break;
    case 0x00001:
			  hideBox();
			  //Hide box Show box
				box_1.setVisible(true);
        box_1.invalidate();
		break;
    case 0x00002:
		      hideBox();
		      box_2.setVisible(true);
          box_2.invalidate();
		break;
    case 0x00003:
			    hideBox();
		      box_3.setVisible(true);
          box_3.invalidate();
		break;
    case 0x00004:
			    hideBox();
		      box_4.setVisible(true);
          box_4.invalidate();
		break;
    case 0x00005:	
			    hideBox();
		      box_5.setVisible(true);
          box_5.invalidate();
		break;
		case 0x00006:
			    hideBox();
		      box_6.setVisible(true);
          box_6.invalidate();
		break;
		case 0x00007:
			    hideBox();
		      box_7.setVisible(true);
          box_7.invalidate();
		break;		
		
		//knob1 pressed Levels[0+1]=1
		case 0x00010:
		case 0x00011:
		case 0x00012:
		case 0x00013:
		case 0x00014:
		case 0x00015:
		case 0x00016:
		case 0x00017:		
			   application().gotoScreenEffectSetScreenNoTransition();
		break;
		

		
		case 0x0000d:
			   application().gotoScreen1ScreenNoTransition();// go to cct
		break;		
		case 0x0000c://key menu key back
			   application().gotoScreenMenuScreenNoTransition();// go to menu
		break;
		
		default:
			break;
	}
}
