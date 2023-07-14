#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

		//通过模型保存和检索 最新的数据，将受保护的值(温度亮度频率）添加到模型，添加公共函数访问此值
    //CCT界面参数
		void saveCCTTemperature(int saveTemperature)
		{
			CCT_Temperature_count = saveTemperature;
		}
		void saveCCTLight(float saveLight)
		{
			CCT_Light_count=saveLight;
		}	
		void saveLightxn(float saveLightxn)
		{
			Light_xn=saveLightxn;
		}	
		int getCCTTemperature()
		{
			return CCT_Temperature_count;
		}
		float  getCCTLight()
		{
			return CCT_Light_count;
		}
		float  getLightxn()
		{
			return Light_xn;
		}
		//以上代码：数值得以保存于模型中，可检索数据，访问数值。
		
		//Fan类型保存
		void saveFanType( int saveFanType)
		{
			FanType = saveFanType;
		}
		int getFanType()
		{
			return FanType ;
		}
		
		//effect界面参数 badBulbs
		void saveMbadBulbsTemperature(int saveTemperature)
		{
			badBulb_Temperature = saveTemperature;
		}
		void saveMbadBulbsLight(int saveLight)
		{
			badBulb_Light=saveLight;
		}			
		void saveMbadBulbsFrequency(int saveFrequency)
		{
			badBulb_Frequency=saveFrequency;
		}					
		int getMbadBulbsTemperature()
		{
			return badBulb_Temperature;
		}
		int  getMbadBulbsLight()
		{
			return badBulb_Light;
		}			
		int getMbadBulbsFrequency()
		{
			return badBulb_Frequency;
		}
		
				//effect界面参数 explode
		void saveMexplodeTemperature(int saveTemperature)
		{
			explode_Temperature = saveTemperature;
		}
		void saveMexplodeLight(int saveLight)
		{
			explode_Light=saveLight;
		}			
		void saveMexplodeFrequency(int saveFrequency)
		{
			explode_Frequency=saveFrequency;
		}					
		int getMexplodeTemperature()
		{
			return explode_Temperature;
		}
		int  getMexplodeLight()
		{
			return explode_Light;
		}			
		int getMexplodeFrequency()
		{
			return explode_Frequency;
		}
		
				//effect界面参数 firework
		void saveMfireworkTemperature(int saveTemperature)
		{
			firework_Temperature = saveTemperature;
		}
		void saveMfireworkLight(int saveLight)
		{
			firework_Light=saveLight;
		}			
		void saveMfireworkFrequency(int saveFrequency)
		{
			firework_Frequency=saveFrequency;
		}					
		int getMfireworkTemperature()
		{
			return firework_Temperature;
		}
		int  getMfireworkLight()
		{
			return firework_Light;
		}			
		int getMfireworkFrequency()
		{
			return firework_Frequency;
		}		

				//effect界面参数 flash
		void saveMflashTemperature(int saveTemperature)
		{
			flash_Temperature = saveTemperature;
		}
		void saveMflashLight(int saveLight)
		{
			flash_Light=saveLight;
		}			
		void saveMflashFrequency(int saveFrequency)
		{
			flash_Frequency=saveFrequency;
		}					
		int getMflashTemperature()
		{
			return flash_Temperature;
		}
		int  getMflashLight()
		{
			return flash_Light;
		}			
		int getMflashFrequency()
		{
			return flash_Frequency;
		}		

				//effect界面参数 lighting
		void saveMlightingTemperature(int saveTemperature)
		{
			lighting_Temperature = saveTemperature;
		}
		void saveMlightingLight(int saveLight)
		{
			lighting_Light=saveLight;
		}			
		void saveMlightingFrequency(int saveFrequency)
		{
			lighting_Frequency=saveFrequency;
		}					
		int getMlightingTemperature()
		{
			return lighting_Temperature;
		}
		int  getMlightingLight()
		{
			return lighting_Light;
		}			
		int getMlightingFrequency()
		{
			return lighting_Frequency;
		}		

				//effect界面参数 paparazzi
		void saveMpaparazziTemperature(int saveTemperature)
		{
			paparazzi_Temperature = saveTemperature;
		}
		void saveMpaparazziLight(int saveLight)
		{
			paparazzi_Light=saveLight;
		}			
		void saveMpaparazziFrequency(int saveFrequency)
		{
			paparazzi_Frequency=saveFrequency;
		}					
		int getMpaparazziTemperature()
		{
			return paparazzi_Temperature;
		}
		int  getMpaparazziLight()
		{
			return paparazzi_Light;
		}			
		int getMpaparazziFrequency()
		{
			return paparazzi_Frequency;
		}		

				//effect界面参数 pulse
		void saveMpulseTemperature(int saveTemperature)
		{
			pulse_Temperature = saveTemperature;
		}
		void saveMpulseLight(int saveLight)
		{
			pulse_Light=saveLight;
		}			
		void saveMpulseFrequency(int saveFrequency)
		{
			pulse_Frequency=saveFrequency;
		}					
		int getMpulseTemperature()
		{
			return pulse_Temperature;
		}
		int  getMpulseLight()
		{
			return pulse_Light;
		}			
		int getMpulseFrequency()
		{
			return pulse_Frequency;
		}		
		

				//effect界面参数 tv
		void saveMtvTemperature(int saveTemperature)
		{
			tv_Temperature = saveTemperature;
		}
		void saveMtvLight(int saveLight)
		{
			tv_Light=saveLight;
		}			
		void saveMtvFrequency(int saveFrequency)
		{
			tv_Frequency=saveFrequency;
		}					
		int getMtvTemperature()
		{
			return tv_Temperature;
		}
		int  getMtvLight()
		{
			return tv_Light;
		}			
		int getMtvFrequency()
		{
			return tv_Frequency;
		}		
		
		    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }
    void tick();
		
protected:
	ModelListener* modelListener; //model有指向当前活动Presenter的指针 其类型是接口ModelListener
	float CCT_Light_count;//cct界面
	int CCT_Temperature_count;
  float Light_xn;

  int FanType;//Fan类型

	int badBulb_Light;//特效界面
	int badBulb_Temperature;
	int badBulb_Frequency;
	int explode_Light;//特效界面
	int explode_Temperature;
	int explode_Frequency;
	int firework_Light;//特效界面firework
	int firework_Temperature;
	int firework_Frequency;
	int flash_Light;//特效界面flash
	int flash_Temperature;
	int flash_Frequency;
	int lighting_Light;//特效界面lighting
	int lighting_Temperature;
	int lighting_Frequency;
	int paparazzi_Light;//特效界面paparazzi
	int paparazzi_Temperature;
	int paparazzi_Frequency;
	int pulse_Light;//特效界面pulse
	int pulse_Temperature;
	int pulse_Frequency;
	int tv_Light;//特效界面tv
	int tv_Temperature;
	int tv_Frequency;

};

#endif // MODEL_HPP
