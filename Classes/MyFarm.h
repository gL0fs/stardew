#ifndef __MyFarm_H__
#define __MyFarm_H__
#include "Farm.h" 
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support

class MyFarm : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene();
    static MyFarm* create();
    virtual bool init();  // ���� init ������ȷ���� virtual
//protected:
//    MyFarm();
//    virtual ~MyFarm();
private:
    Farm* _farm;
    bool MyFarm::initMap();
    //void MyFarm::update(float delta);
    //void MyFarm::checkPlayerCollision(const cocos2d::Vec2& nextPosition);

    void switchMap(const std::string& mapName) override;
};
#endif