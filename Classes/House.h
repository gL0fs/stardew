#ifndef __House_H__ 
#define __House_H__
#include "House.h"  
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support

class House : public BaseMapLayer 
{
public:
    static cocos2d::Scene* createScene();  // 创建场景函数
    static House* create();  // 创建 House 实例
    virtual bool init();  // 声明 init 函数，确保是 virtual



private:

    bool initMap();  // 初始化地图函数

    void switchMap(const std::string& mapName) override;  // 重载 switchMap 函数
};

#endif

