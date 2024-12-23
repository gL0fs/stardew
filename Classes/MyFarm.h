#ifndef __MyFarm_H__
#define __MyFarm_H__
#include "BaseMapLayer.h"
#include "CropSystem.h"  // �������ϵͳͷ�ļ�
#include "extensions/cocos-ext.h" // For keyboard support
//#include"AnimalSystem.h"
#include "Toolbar.h"

class MyFarm : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene(const std::string& spawnPointName);
    static MyFarm* create(const std::string& spawnPointName);
    void onMouseDown1(cocos2d::EventMouse* event);
    void onKeyPressed1(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    //void initAnimalSystem() {
    //    _animalSystem = AnimalSystem::create();
    //    if (_animalSystem) {
    //        this->addChild(_animalSystem, 1);
    //        // ���һЩ��ʼ����
    //        _animalSystem->addAnimal("chicken", Vec2(100, 100));
    //        _animalSystem->addAnimal("cow", Vec2(200, 100));
    //    }
    //}

    virtual bool init() override;
 
protected:   
    CropSystem* _cropSystem;
 /*   AnimalSystem* _animalSystem;*/
private:  
    bool MyFarm::initMap(const std::string& spawnPointName) override;

    cocos2d::EventListenerMouse* _mouseListener;
    void initCropSystem();    // �������ϵͳ��ʼ������
   
    float _timeOfDay;  // ��ǰʱ�䣨0-1��Χ��ʾһ���е�ĳ��ʱ�̣�
    LayerColor* _nightLayer;

    // ˽�г�Ա����
    void updateDayNightCycle();
};
#endif
