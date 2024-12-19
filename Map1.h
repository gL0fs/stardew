#ifndef __MAP1_H__
#define __MAP1_H__
#include "Farm.h" 
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support

class Map1 : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene();
    static Map1* create();
    virtual bool init();  // 声明 init 函数，确保是 virtual
protected:
    Map1();
    virtual ~Map1();
private:
    Farm* _farm;
    bool Map1::initMap();
    cocos2d::Sprite* _player; // 角色精灵
    cocos2d::Vec2 _velocity; // 角色移动速度
	void switchMap(const std::string& mapName) override;
};
#endif