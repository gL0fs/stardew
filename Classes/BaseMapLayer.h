#pragma once
#ifndef __BASEMAPLAYER_H__
#define __BASEMAPLAYER_H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "Player.h"  // ���Playerͷ�ļ�����
using namespace cocos2d;

class BaseMapLayer : public cocos2d::Layer
{
public:
    BaseMapLayer();
    static BaseMapLayer* create(const std::string& tmxFile);
    virtual bool init() override;
    bool initMap(const std::string& tmxFile);
    void loadMap(const std::string& tmxFile);
    void setPlayerPosition(const std::string& objectGroupName, const std::string& spawnPointName);

    // �޸���ײ�����ƶ���غ�����ʹ��Player����
    //bool isCollisionAtNextPosition(const cocos2d::Vec2& nextPosition);
    void handlePlayerMovement(const cocos2d::Vec2& direction);  // ������ҵ��ƶ�
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);  // ��������
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);  // �����ɿ�

    void setViewPointCenter(Point position);//�ӽ�����player�ƶ����ƶ�
    // ��ʼ������¼�
    void initMouseEvent();

    // ����Ƿ���������ķ���
    bool canPlantTreeAtPosition(cocos2d::Vec2 position);
    void update(float delta);  // ÿ֡����
protected:
    cocos2d::TMXTiledMap* _map;
    // �Ƴ�_player����Ϊʹ��Player����
    Player* _playerInstance;  // ���Player����ָ��
    cocos2d::Vec2 _moveDirection;  // �ƶ�����

    // ��ӳ�ʼ����ҵķ���
    virtual void initializePlayer();
private:
    // �����ľ���黺��
    cocos2d::Vector<cocos2d::Sprite*> _treesVector;

    // ��ľ����
    std::string _treeSpriteFile = "tree.png";

    // ��������
    void plantTree(cocos2d::Vec2 position);

    // ����¼�������
    cocos2d::EventListenerMouse* _mouseListener;
};
#endif
