#ifndef __MyFarm_H__
#define __MyFarm_H__
#include "BaseMapLayer.h"
#include "GameTimeUI.h"
#include "CropSystem.h"  // �������ϵͳͷ�ļ�
#include "extensions/cocos-ext.h" // For keyboard support
#include "Toolbar.h"

class MyFarm : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene(const std::string& spawnPointName);
    static MyFarm* create(const std::string& spawnPointName);
    void onMouseDown1(cocos2d::EventMouse* event);
    void onKeyPressed1(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    bool init() override;  // ���� init ������ȷ���� virtual
protected:   
    CropSystem* _cropSystem;
    Toolbar* _toolbar;
    GameTimeUI* _timeUI;  // ���� GameTimeUI ָ��
private:
    
    bool MyFarm::initMap(const std::string& spawnPointName) override;
    cocos2d::EventListenerMouse* _mouseListener;
    void initCropSystem();    // �������ϵͳ��ʼ������


};
#endif
