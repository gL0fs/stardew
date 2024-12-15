

#pragma once
#ifndef __BASEMAPLAYER_H__
#define __BASEMAPLAYER_H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "Player.h"  // 添加Player头文件引用
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

    // 修改碰撞检测和移动相关函数以使用Player单例
    bool isCollisionAtNextPosition(const cocos2d::Vec2& nextPosition);
    void handlePlayerMovement(const cocos2d::Vec2& direction);  // 处理玩家的移动
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);  // 按键按下
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);  // 按键松开
    
    void setViewPointCenter(Point position);//视角随着player移动而移动
    

    void update(float delta);  // 每帧更新
    
    
     void initMouseEvent();

    bool canPlantTreeAtPosition(cocos2d::Vec2 position);
protected:
    cocos2d::TMXTiledMap* _map;
    // 移除_player，改为使用Player单例
    Player* _playerInstance;  // 添加Player单例指针
    cocos2d::Vec2 _moveDirection;  // 移动方向

    // 添加初始化玩家的方法
    virtual void initializePlayer();
private:
   cocos2d::Vector<cocos2d::Sprite*> _treesVector;

    
    std::string _treeSpriteFile = "tree.png";

    void plantTree(cocos2d::Vec2 position);

 
    cocos2d::EventListenerMouse* _mouseListener;
    
};
#endif

