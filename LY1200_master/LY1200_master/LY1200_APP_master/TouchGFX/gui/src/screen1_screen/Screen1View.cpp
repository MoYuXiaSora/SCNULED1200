#include <gui/screen1_screen/Screen1View.hpp>
#include "math.h"
#include "control_box.h"
#include <string.h>
#define max(x,y) ( x>y?x:y )
#define min(x,y) ( x<y?x:y )

extern "C"
{	
	uint32_t CCTcheckFinalCal(uint8_t Levels[]){	
		return 0x00000|(Levels[4]<<16)|(Levels[3])<<12|(Levels[2]<<8)|(Levels[1]<<4)|(Levels[0]);
	}
	uint64_t CCTcalVarition (uint8_t GFXKeys, uint8_t Levels[]){ //按键对应的值
		switch ((GFXKeys&0xF0)>>4){
			case 0x00:
				return CCTcheckFinalCal(Levels);
			case 0x01://knob1左移
			  return 0x01;
			case 0x02://knob1右移
			  return 0x02;
			
			case 0x03://knob2左移
				return 0x03;			
			case 0x04://knob2右移
				return 0x04;
			
			case 0x07://key menu is pressed
			  memset(GFXLevels,0,sizeof(GFXLevels));//数组清为0				
				return 0x0000c;//go to menu c只是数值 eg c d e 返回的还是menu0x00000.
			
			case 0x08:
			  memset(GFXLevels,0,sizeof(GFXLevels));//数组清为0
				return 0x0000d;//cct界面
			
			case 0x09://key effect is pressed
			  memset(GFXLevels,0,sizeof(GFXLevels));//数组清为0				
				return 0x0000e;
			
		  case 0x0a://key back
			  memset(GFXLevels,0,sizeof(GFXLevels));//数组清为0				
				return 0x0000c;//go to menu 此c与0 区分开。
			default:
			return CCTcheckFinalCal(Levels) ;
		}
	}
}
Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
	Screen1ViewBase::setupScreen();
	Temperature_count=presenter->getCCTTemperature();//刷新新界面，用指针presenter 读取记录好的数值
	Light_count=presenter->getCCTLight();	

    //通配符显示
	Unicode::snprintfFloat(LightTextPgBuffer,LIGHTTEXTPG_SIZE, "%.1f", float(Light_count));
	Unicode::snprintf(TemperatureTextPgBuffer, TEMPERATURETEXTPG_SIZE, "%d", Temperature_count);
	 //进度器显示
	LightingProgress.setValue(Light_count*10);//进度器需要1000步。
	TemperatureProgress.setValue(Temperature_count);
}

void Screen1View::tearDownScreen()
{
	Screen1ViewBase::tearDownScreen();//离开此界面，用指针presenter 保存修改的数值
	
	presenter->saveCCTLight(Light_count);
	presenter->saveCCTTemperature(Temperature_count);
}

void Screen1View::handleKeyEvent(uint8_t key)
{
	ScreenMenuNumberGFX = CCTcalVarition(key,GFXLevels);	

     switch (ScreenMenuNumberGFX) 
   { 
		 case 0x01:
			 LightDown();
		 break;			 
		 case 0x02:
			 LightUp();
		 break;
		 
		 case 0x03:
			 TemperatureDown();
		 break;
		 case 0x04:
			 TemperatureUp();
		 break;
		 
		 case 0x0000c://key:menu，back
			 application().gotoScreenMenuScreenNoTransition();
		 break;
		case 0x0000d:
			 application().gotoScreen1ScreenNoTransition();// go to cct
	  break;		 
		 case 0x0000e://key：effect
			 application().gotoScreenEffectScreenNoTransition();
		 break;
						 
			default:
			break;
	 }
 }

void Screen1View::LightDown()
{   
	switch(CurveType)
	{
	 case 0:
		 Light_count -= 0.1;
		 Light_count=max(Light_count,0.0);
	 break;

	 case 1://s
		Light_xs -=0.001;
	 	Light_xs = min(max(Light_xs,0),1);
	  if(Light_xs <= 0.5)
		{
			eLight_count = 100*(0.5 - 0.5*pow((1-2*Light_xs),2.2));
		}
		else 
		{
			eLight_count = 100*(0.5 + 0.5*pow((2*(Light_xs-0.5)),2.2));			
		}
	  Light_count = std::round(eLight_count*10)/10;//round是四舍五入，最后结果剩小数点后一位
	  Light_count = max(Light_count,0.0);				
	 break;
		
	 case 2://exp
		Light_xn -= 0.001;//一共1000步
		Light_xn = min(max(Light_xn,0.0),1.0);
		Light_x = Light_xn*log(101);
		eLight_count =  exp(Light_x)-1;
		Light_count = std::round(eLight_count*10)/10;//round是四舍五入，最后结果剩小数点后一位	 
		Light_count = max(Light_count,0.0);	
	 break;
		
		default:
		break;	
	}	
		
	 presenter->saveCCTLight(Light_count);//通过presenter保存到mode 函数中直接进行采样
	 LightingProgress.setValue(Light_count*10);//给进度条设置亮度的值 
	 LightingProgress.invalidate(); //更新显示进度条的值
	 //通配符显示
	 
	 Unicode::snprintfFloat(LightTextPgBuffer,LIGHTTEXTPG_SIZE, "%.1f", float(Light_count));
	 LightTextPg.invalidate();//更新显示		
	
//     LightingTextPg.updateValue(Light_count, 1000);
//     LightingTextPg.invalidate(); //文本进度条
	
}
void Screen1View::LightUp()
{
	switch(CurveType)
	{
	 case 0:
		Light_count+= 0.1; //0线型曲线 
		Light_count=min(Light_count,100.0);
	 break;

	 case 1://s
		Light_xs +=0.001;
	 	Light_xs = min(max(Light_xs,0),1);
	  if(Light_xs <= 0.5)
		{
			eLight_count = 100*(0.5 - 0.5*pow((1-2*Light_xs),2.2));
		}
		else 
		{
			eLight_count = 100*(0.5 + 0.5*pow((2*(Light_xs-0.5)),2.2));			
		}
	  Light_count = std::round(eLight_count*10)/10;//round是四舍五入，最后结果剩小数点后一位
	  Light_count = min(Light_count,100.0);				
	 break;
		
	 case 2://exp
		Light_xn += 0.001;//一共1000步
		Light_xn = min(max(Light_xn,0.0),1.0);
		Light_x = Light_xn*log(101);
		eLight_count =  exp(Light_x)-1;
		Light_count = std::round(eLight_count*10)/10;//round是四舍五入，最后结果剩小数点后一位	 
	  Light_count = min(Light_count,100.0);
	 break;
	 
	 default:
	 break;	 
	}
	
	 presenter->saveCCTLight(Light_count);
	 LightingProgress.setValue(Light_count*10);//给进度条设置亮度的值0-1000步。
	 LightingProgress.invalidate(); //更新显示进度条的值
	 //通配符显示
	 Unicode::snprintfFloat(LightTextPgBuffer,LIGHTTEXTPG_SIZE, "%.1f", float(Light_count));
	 LightTextPg.invalidate();//更新显示		
}

void Screen1View::TemperatureDown()
{
	 Temperature_count-= 50;
	 Temperature_count=max(Temperature_count,2700);
	 presenter->saveCCTTemperature(Temperature_count);
//	 touchgfx_printf("Temperature_count %ld \r\n", Temperature_count);//打印数据
	 TemperatureProgress.setValue(Temperature_count);//给进度条设置色温的值
	 TemperatureProgress.invalidate(); //更新显示半环进度条的值	
    //通配符显示
    Unicode::snprintf(TemperatureTextPgBuffer, TEMPERATURETEXTPG_SIZE, "%d", Temperature_count);
	  TemperatureTextPg.invalidate();//更新显示			
}
void Screen1View::TemperatureUp()
{
	 Temperature_count+= 50;
	 Temperature_count=min(Temperature_count,6500);
	 presenter->saveCCTTemperature(Temperature_count);
//	touchgfx_printf("Temperature_count %ld \r\n", Temperature_count);//打印数据
	TemperatureProgress.setValue(Temperature_count);//给进度条设置色温的值
	TemperatureProgress.invalidate(); //更新显示半环进度条的值

	//通配符显示
	Unicode::snprintf(TemperatureTextPgBuffer, TEMPERATURETEXTPG_SIZE, "%d", Temperature_count);
	TemperatureTextPg.invalidate();//更新显示
}