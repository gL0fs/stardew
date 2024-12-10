#pragma once
#ifndef __BASEMAPLAYER_H__
#define __BASEMAPLAYER_H__


#include "cocos2d.h" // ȷ��������Cocos2d-x����ͷ�ļ�

USING_NS_CC; // ʹ��Cocos2d-x�������ռ�
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h"
class BaseMapLayer : public cocos2d::Layer
{
public:
    static BaseMapLayer* create(const std::string& tmxFile);
    virtual bool init() override;
    Scene* BaseMapLayer::createScene();
    void loadMap(const std::string& tmxFile);
    void setPlayerPosition(const std::string& objectGroupName, const std::string& spawnPointName);
    //�����ƶ���غ���
    void StartMovement(EventKeyboard::KeyCode keyCode, Event* event);
    void StopMovement(EventKeyboard::KeyCode keyCode, Event* event);
    void BaseMapLayer::update(float dt);
   
protected:
    cocos2d::TMXTiledMap* _map;
    cocos2d::Sprite* _player;
    
    BaseMapLayer();
    bool initMap(const std::string& tmxFile);

    // ����״̬
    bool _isMovingUp;
    bool _isMovingDown;
    bool _isMovingLeft;
    bool _isMovingRight;
};

#endif // __BASEMAPLAYER_H__
