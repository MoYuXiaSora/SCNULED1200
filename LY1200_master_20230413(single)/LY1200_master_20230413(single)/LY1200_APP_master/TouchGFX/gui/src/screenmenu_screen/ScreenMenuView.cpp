#include <gui/screenmenu_screen/ScreenMenuView.hpp>
#include "math.h"
#include "control_box.h"
#define max(x,y) ( x>y?x:y )
#define min(x,y) ( x<y?x:y )
#define gotoCCT  0x0000d

uint8_t MenuLevel = 0; 
//先定义数组转int的函数 再加入数组
extern "C"
{	
	uint32_t checkFinalCal(uint8_t Levels[]){	
		return 0x00000|(Levels[4]<<16)|(Levels[3])<<12|(Levels[2]<<8)|(Levels[1]<<4)|(Levels[0]);
	}
	uint64_t calVarition (uint8_t GFXKeys, uint8_t Levels[]){ //按键对应的值
		switch ((GFXKeys&0xF0)>>4){
		  case 0x00://无触发动作 
			  return checkFinalCal(Levels);
		  case 0x01://KNOB1左转
				Levels[MenuLevel] += (-1)*min((GFXKeys&0x0F),Levels[MenuLevel]);
				return checkFinalCal(Levels);
			case 0x02:
				Levels[MenuLevel] += (GFXKeys&0x0F);//旋转的相对值 GFXKeys的低位。
			  Levels[MenuLevel] = min(max(Levels[MenuLevel],0),5);
				return checkFinalCal(Levels);
						
			case 0x06://KNOB1 is pressed
				Levels[MenuLevel+1] = 1; //数组 下一个为1
			  MenuLevel+=1;//层级加1
				return checkFinalCal(Levels);
			
			case 0x08://key cct is pressed 				
 			  Levels[MenuLevel]=0x00;//将该层数组值置为0 该层00000.
				return gotoCCT;//直接去cct界面
			case 0x09://key effect is pressed				
				Levels[MenuLevel]=0x00;//将该层数组值置为0 该层00000.
				return 0x0000e;//直接去effect界面
    	default:
			return checkFinalCal(Levels) ;
		}
	}
}

ScreenMenuView::ScreenMenuView()
{

}

void ScreenMenuView::setupScreen()
{
    ScreenMenuViewBase::setupScreen();
}

void ScreenMenuView::tearDownScreen()
{
    ScreenMenuViewBase::tearDownScreen();
}

void ScreenMenuView::hideBox()
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
}

void ScreenMenuView::handleKeyEvent(uint8_t key)
{
	ScreenMenuNumberGFX = calVarition(key,GFXLevels);	
//ScreenMenuNumberGFX = min(max(ScreenMenuNumberGFX,0),5); //这里要做进位处理的考虑
     switch (ScreenMenuNumberGFX)  //屏幕转换之前添加方框清0
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
		
		//knob1 pressed Levels[0+1]=1
		
		case 0x00010:
			   application().gotoScreenControlScreenNoTransition();
		break;
		case 0x00011:	//选中Curve
			    application().gotoScreenCurveScreenNoTransition();
		break;
		case 0x00012:
			   application().gotoScreenFanScreenNoTransition();
		break;
		case 0x00013:	//选中
			    application().gotoScreenStudioScreenNoTransition();
		break;
		case 0x00014:
			   application().gotoScreenLanguageScreenNoTransition();
		break;
		case 0x00015:	//选中
			    application().gotoScreenUpdateScreenNoTransition();
		break;		
		
		
		case gotoCCT:
			   application().gotoScreen1ScreenNoTransition();// go to cct
		break;
		case 0x0000e:
			   application().gotoScreenEffectScreenNoTransition();// go to effect
		break;
		
		default:
			break;
	}
}
