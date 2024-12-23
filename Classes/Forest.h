#pragma once
#ifndef __FOREST_H__
#define __FOREST_H__

#include "BaseMapLayer.h"
#include "Player.h"
#include "Mine.h"

#include "MyFarm.h"

#include "MainMenuScene.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"
#include "Test.h"
#include"House.h"
USING_NS_CC;
class Forest : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene(const std::string& spawnPointName);
    static Forest* create(const std::string& spawnPointName);
    bool init() override;
    void Forest::initMouseEvent();
    cocos2d::Vec2 Forest::getTileCoordForPosition(cocos2d::Vec2 position);
    void Fishing(cocos2d::Vec2 position);
	void collect(cocos2d::Vec2 position);
	void cutTree(cocos2d::Vec2 position);
protected:
    Forest();
    virtual ~Forest();

private:
    bool initMap(const std::string& spawnPointName)override;
    cocos2d::EventListenerMouse* _mouseListener;
	void deleteWholeObject(cocos2d::Vec2 position, cocos2d::TMXLayer* layer);
};

#endif // __FOREST_H__