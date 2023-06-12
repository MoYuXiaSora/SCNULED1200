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
		void saveCCTLight(int saveLight)
		{
			CCT_Light_count=saveLight;
		}		
		int getCCTTemperature()
		{
			return CCT_Temperature_count;
		}
		int  getCCTLight()
		{
			return CCT_Light_count;
		}

		//以上代码：数值得以保存于模型中，可检索数据，访问数值。
		
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
		
		
				
		    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }
    void tick();
		
protected:
	ModelListener* modelListener; //model有指向当前活动Presenter的指针 其类型是接口ModelListener
	int CCT_Light_count;//cct界面
	int CCT_Temperature_count;
	int CCT_Frequency_count;

	int badBulb_Light;//特效界面
	int badBulb_Temperature;
	int badBulb_Frequency;
	int explode_Light;//特效界面
	int explode_Temperature;
	int explode_Frequency;


};

#endif // MODEL_HPP
