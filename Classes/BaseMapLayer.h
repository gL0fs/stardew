#pragma once
#ifndef __BASEMAPLAYER_H__
#define __BASEMAPLAYER_H__


#include "cocos2d.h" // 确保包含了Cocos2d-x的主头文件

USING_NS_CC; // 使用Cocos2d-x的命名空间
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
    //键盘移动相关函数
    void StartMovement(EventKeyboard::KeyCode keyCode, Event* event);
    void StopMovement(EventKeyboard::KeyCode keyCode, Event* event);
    void BaseMapLayer::update(float dt);
   
protected:
    cocos2d::TMXTiledMap* _map;
    cocos2d::Sprite* _player;
    
    BaseMapLayer();
    bool initMap(const std::string& tmxFile);

    // 按键状态
    bool _isMovingUp;
    bool _isMovingDown;
    bool _isMovingLeft;
    bool _isMovingRight;
};

#endif // __BASEMAPLAYER_H__
