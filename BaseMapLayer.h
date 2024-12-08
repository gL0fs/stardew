#pragma once
#ifndef __BASEMAPLAYER_H__
#define __BASEMAPLAYER_H__

#include "cocos2d.h"

class BaseMapLayer : public cocos2d::Layer
{
public:
    static BaseMapLayer* create(const std::string& tmxFile);
    virtual bool init() override;

    void loadMap(const std::string& tmxFile);
    void setPlayerPosition(const std::string& objectGroupName, const std::string& spawnPointName);
    //virtual void update(float delta);
protected:
    cocos2d::TMXTiledMap* _map;
    cocos2d::Sprite* _player;

    BaseMapLayer();
   /* virtual ~BaseMapLayer();
    bool _isMovingUp;
    bool _isMovingDown;
    bool _isMovingLeft;
    bool _isMovingRight;
    float _playerSpeed;

    // ���������¼�����������
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
private:*/
    bool initMap(const std::string& tmxFile);
};

#endif // __BASEMAPLAYER_H__
/*
#ifndef BASEMAPLAYER_H
#define BASEMAPLAYER_H

#include "cocos2d.h"
#include "extensions/cocos-ext.h" // For keyboard support

USING_NS_CC;
USING_NS_CC_EXT;

class BaseMapLayer : public Layer
{
public:
    static BaseMapLayer* create(const std::string& tmxFile);

    virtual bool init();

    virtual bool initMap(const std::string& tmxFile);

    void setPlayerPosition(const std::string& objectGroupName, const std::string& spawnPointName);

    // ������������
    virtual void update(float delta); // ���º��������ھ����ƶ�

protected:
    TMXTiledMap* _map;
    Sprite* _player;

    // ������Ա����
    bool _isMovingUp;
    bool _isMovingDown;
    bool _isMovingLeft;
    bool _isMovingRight;
    float _playerSpeed;

    // ���������¼�����������
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    // ������Ա�����ͷ���...
};

#endif // BASEMAPLAYER_H*/