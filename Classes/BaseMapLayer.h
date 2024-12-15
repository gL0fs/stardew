#pragma once
#ifndef __BASEMAPLAYER_H__
#define __BASEMAPLAYER_H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "Player.h"  // ���Playerͷ�ļ�����
#include <string>
#include "MainMenuScene.h"
#include "SceneManager.h"
using namespace cocos2d;

class BaseMapLayer : public cocos2d::Layer
{
public:
    BaseMapLayer();
    BaseMapLayer* create(const std::string& tmxFile);
    virtual bool init() override;
    bool initMap(const std::string& tmxFile);
    void loadMap(const std::string& tmxFile);
    void setPlayerPosition(const std::string& objectGroupName, const std::string& spawnPointName);

    // �޸���ײ�����ƶ���غ�����ʹ��Player����
    bool isCollisionAtNextPosition(const cocos2d::Vec2& nextPosition);
    void handlePlayerMovement(const cocos2d::Vec2& direction);  // ������ҵ��ƶ�
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);  // ��������
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);  // �����ɿ�
    
    void setViewPointCenter(Point position);//�ӽ�����player�ƶ����ƶ�
	void checkChangeMap(const cocos2d::Vec2& nextPosition);//����Ƿ���Ҫ�л���ͼ

    void update(float delta);  // ÿ֡����
	virtual void switchMap(const std::string& mapName)=0;//�л���ͼ
protected:
    cocos2d::TMXTiledMap* _map;
    // �Ƴ�_player����Ϊʹ��Player����
    Player* _playerInstance;  // ���Player����ָ��
    cocos2d::Vec2 _moveDirection;  // �ƶ�����

    // ��ӳ�ʼ����ҵķ���
    virtual void initializePlayer();
};
#endif