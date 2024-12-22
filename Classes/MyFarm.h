#ifndef __MyFarm_H__
#define __MyFarm_H__
#include "Farm.h" 
#include "BaseMapLayer.h"
#include "GameTimeUI.h"
#include "extensions/cocos-ext.h" // For keyboard support

class MyFarm : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene();
    static MyFarm* create();
    virtual bool init();  // ���� init ������ȷ���� virtual
protected:
    MyFarm();
    virtual ~MyFarm();
    GameTimeUI* _timeUI;  // ���� GameTimeUI ָ��
private:
    Farm* _farm;
    bool MyFarm::initMap();
    //void MyFarm::update(float delta);
    //void MyFarm::checkPlayerCollision(const cocos2d::Vec2& nextPosition);

<<<<<<< HEAD
    void switchMap(const std::string& mapName,int path) override;
=======
    //void switchMap(const std::string& mapName) override;
>>>>>>> d841b37f330871413230ac34b19f244d8218b63f
};
#endif
