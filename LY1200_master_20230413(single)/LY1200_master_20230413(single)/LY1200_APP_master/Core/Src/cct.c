#include "cct.h"

const float cct_Cold_Surface[77]={ //77组冷色温表从2700k-6500k 每50k步进
    0.01754, 
    0.04000, 
    0.06349, 
    0.08475, 
    0.10638, 
    0.12727, 
    0.14754, 
    0.16667, 
    0.18644, 
    0.20548, 
    0.22388, 
    0.24194, 
    0.25926, 
    0.27660, 
    0.29333, 
    0.30986, 
    0.32609, 
    0.34177, 
    0.35714, 
    0.37255, 
    0.38739, 
    0.40206, 
    0.41667, 
    0.43056, 
    0.44444, 
    0.45794, 
    0.47143, 
    0.48454, 
    0.50000, 
    0.51042, 
    0.52308, 
    0.53548, 
    0.54795, 
    0.56000, 
    0.57229, 
    0.58385, 
    0.59551, 
    0.60684, 
    0.61842, 
    0.62963, 
    0.64063, 
    0.65169, 
    0.66250, 
    0.67327, 
    0.68376, 
    0.69444, 
    0.70476, 
    0.71545, 
    0.72527, 
    0.73529, 
    0.74528, 
    0.75510, 
    0.76531, 
    0.77465, 
    0.78409, 
    0.79365, 
    0.80303, 
    0.81250, 
    0.82178, 
    0.83077, 
    0.84000, 
    0.84906, 
    0.85714, 
    0.86667, 
    0.87500, 
    0.88421, 
    0.89286, 
    0.90141, 
    0.91000, 
    0.91837, 
    0.92683, 
    0.93506, 
    0.94340, 
    0.95146, 
    0.95960, 
    0.96739, 
    0.97561,
};

const float cct_Warm_Surface[77]={ //77组暖色温表从2700k-6500k 每50k步进
    0.98246, 
    0.96000, 
    0.93651, 
    0.91525, 
    0.89362, 
    0.87273, 
    0.85246, 
    0.83333, 
    0.81356, 
    0.79452, 
    0.77612, 
    0.75806, 
    0.74074, 
    0.72340, 
    0.70667, 
    0.69014, 
    0.67391, 
    0.65823, 
    0.64286, 
    0.62745, 
    0.61261, 
    0.59794, 
    0.58333, 
    0.56944, 
    0.55556, 
    0.54206, 
    0.52857, 
    0.51546, 
    0.50000, 
    0.48958, 
    0.47692, 
    0.46452, 
    0.45205, 
    0.44000, 
    0.42771, 
    0.41615, 
    0.40449, 
    0.39316, 
    0.38158, 
    0.37037, 
    0.35938, 
    0.34831, 
    0.33750, 
    0.32673, 
    0.31624, 
    0.30556, 
    0.29524, 
    0.28455, 
    0.27473, 
    0.26471, 
    0.25472, 
    0.24490, 
    0.23469, 
    0.22535, 
    0.21591, 
    0.20635, 
    0.19697, 
    0.18750, 
    0.17822, 
    0.16923, 
    0.16000, 
    0.15094, 
    0.14286, 
    0.13333, 
    0.12500, 
    0.11579, 
    0.10714, 
    0.09859, 
    0.09000, 
    0.08163, 
    0.07317, 
    0.06494, 
    0.05660, 
    0.04854, 
    0.04040, 
    0.03261, 
    0.02439, 
};

static uint8_t cct_analysis(struct CCT *cct_local,float *cct_Cold_Out, float *cct_Warm_Out)
{
    float cct_Cold_Ratio=0;
    float cct_Warm_Ratio=0;

    //输入参数检查
    if((cct_local->brightness<0) || (cct_local->brightness>1)) return thisERROR;
    if((cct_local->color_Temperature<2700) || (cct_local->color_Temperature>6500)) return thisERROR;

    //对输入色温值查表得到冷暖比例
    cct_Cold_Ratio = cct_Cold_Surface[(cct_local->color_Temperature-2700)/50];
    cct_Warm_Ratio = cct_Warm_Surface[(cct_local->color_Temperature-2700)/50];

    //计算冷暖两路输出
    *cct_Cold_Out = (cct_Cold_Ratio*cct_local->brightness);
    *cct_Warm_Out = (cct_Warm_Ratio*cct_local->brightness);

    return thisOK;
}

uint8_t cct_User(struct CCT *cct_Local_app,float *cct_Cold_Out_App, float *cct_Warm_Out_App)
{
    return cct_analysis(cct_Local_app, cct_Cold_Out_App, cct_Warm_Out_App);
}


uint8_t light_Effect_Analysis(float *brightness_Local, uint16_t *color_Temperature_Local, float *cold_Out_App, float *warm_Out_App)
{
//    struct CCT *cct_Local_app={
//        .brightness = *brightness_Local,
//        .color_Temperature = *color_Temperature_Local,
//        .cold_Percentage=0,
//        .warm_Percentage=0,
//    };
	
	  struct CCT *cct_Local_app;
		cct_Local_app->brightness = *brightness_Local;
	  cct_Local_app->color_Temperature = *color_Temperature_Local;
	  cct_Local_app->cold_Percentage=0;
		cct_Local_app->warm_Percentage=0;

    return cct_analysis(cct_Local_app, cold_Out_App, warm_Out_App);
}
