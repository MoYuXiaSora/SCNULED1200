#include <gui/screenbluetooth_screen/ScreenBluetoothView.hpp>
#include "math.h"
#include "control_box.h"
#define max(x,y) ( x>y?x:y )
#define min(x,y) ( x<y?x:y )
 //层级为第3层=2； 0，1，2，3，4 数组索引
extern "C"
{	
	uint32_t BlucheckFinalCal(uint8_t Levels[]){	
		return 0x00000|(Levels[4]<<16)|(Levels[3])<<12|(Levels[2]<<8)|(Levels[1]<<4)|(Levels[0]);
	}	
	uint64_t BlucalVarition (uint8_t GFXKeys, uint8_t Levels[]){ //按键对应的值取高位进行case
		switch ((GFXKeys&0xF0)>>4){
			case 0x00:
				return BlucheckFinalCal(Levels);
			case 0x01:
				Levels[MenuLevel] += (-1)*min((GFXKeys&0x0F),Levels[MenuLevel]);
				return BlucheckFinalCal(Levels);//MenuLevel=2
			case 0x02:
				Levels[MenuLevel] += (GFXKeys&0x0F);
			  Levels[MenuLevel] = min(max(Levels[MenuLevel],1),2);//转的范围，应该写成循环？
				return BlucheckFinalCal(Levels);
			
			case 0x06:
				Levels[MenuLevel+1] = 1;
			  MenuLevel+=1;//层级加1 为3
				return BlucheckFinalCal(Levels);
			
			case 0x07:
				Levels[MenuLevel]=0x00;//将该层数组值置为0 该层00000.
			  Levels[1]=0;
			  MenuLevel=0;
				return 0x00000;//返回menu
			case 0x08:
				Levels[MenuLevel]=0x00;//将该层数组值置为0 该层00000.
			  Levels[1]=0;
			  MenuLevel=0;
			  Levels[0]=0x00; 
				return 0x0000d;//直接去cct界面
      case 0x09:
				Levels[MenuLevel]=0x00;//将该层数组值置为0 该层00000.
			  Levels[1]=0;
			  MenuLevel=0;
			  Levels[0]=0x00; 
				return 0x0000e;//直接去effect界面	
     						
			case 0x0a:
				Levels[MenuLevel]=0;//MenuLevel=2
			  MenuLevel-=1;		
			  return BlucheckFinalCal(Levels);//0x00010//返回control
			default:
				return BlucheckFinalCal(Levels) ;
		}
	}
}
ScreenBluetoothView::ScreenBluetoothView()
{

}

void ScreenBluetoothView::setupScreen()
{
    ScreenBluetoothViewBase::setupScreen();
}

void ScreenBluetoothView::tearDownScreen()
{
    ScreenBluetoothViewBase::tearDownScreen();
}
void ScreenBluetoothView::handleKeyEvent(uint8_t key)
{
	ScreenMenuNumberGFX = BlucalVarition(key,GFXLevels);	

     switch (ScreenMenuNumberGFX)  //这里屏幕转换要添加方框清0
   {
    case 0x00110://BOX
			  box_0.setVisible(true);
        box_0.invalidate();
				box_1.setVisible(false);
        box_1.invalidate();		 
		break;
    case 0x00210:
			  //Hide box Show box
			  box_0.setVisible(false);
        box_0.invalidate();		
				box_1.setVisible(true);
        box_1.invalidate();
		break;
		
		//back
		case 0x00010://计算：使 L(2)=0 层级menuLevel-1
		    application().gotoScreenControlScreenNoTransition();
		break;
		
		
		//knob1 pressed 
		case 0x01110:	//按中第一个组件 Bluetooth
//			    application().gotoScreenBluetoothScreenNoTransition();
		break;
		case 0x01210://按中第二个组件 DMX
//			    application().gotoScreenDMXScreenNoTransition();
		break;			
		
		//快捷键
		case 0x0000d:
			   application().gotoScreen1ScreenNoTransition();// go to cct
		break;
		case 0x0000e:
			   application().gotoScreenEffectScreenNoTransition();// go to effect
		break;
		//menu键
		case 0x00000://计算：使 L(2)=L(1)=0 层级menuLevel=0
		    application().gotoScreenMenuScreenNoTransition();
		break;
		
			
		default:
			break;
	}
}