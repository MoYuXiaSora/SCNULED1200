#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}//初始化
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
		
		//虚函数通知数值改变 向ui发数据？？？（newzhi){} （连接接口）
protected:
    Model* model;//指针 
};

#endif // MODELLISTENER_HPP
