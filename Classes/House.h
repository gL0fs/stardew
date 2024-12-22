#ifndef __House_H__ 
#define __House_H__
#include "House.h"  
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support

class House : public BaseMapLayer 
{
public:
    static cocos2d::Scene* createScene(const std::string& spawnPointName);  // 创建场景函数
    static House* create(const std::string& spawnPointName);  // 创建 House 实例
    bool init() override;  // 声明 init 函数，确保是 virtual



private:

    bool initMap(const std::string& spawnPointName) override;  // 初始化地图函数
};

#endif

