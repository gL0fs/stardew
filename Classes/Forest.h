#pragma once
#ifndef __FOREST_H__
#define __FOREST_H__

#include "BaseMapLayer.h"
#include "Player.h"
#include "Mine.h"

#include "MainMenuScene.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"
#include "Test.h"

class Forest : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene(int path=0);
    static Forest* create(int path);
    virtual bool init() override;
    void switchMap(const std::string& mapName,int path) override;
    void Forest::initMouseEvent();
    cocos2d::Vec2 Forest::getTileCoordForPosition(cocos2d::Vec2 position);
    void Fishing(cocos2d::Vec2 position);
	void collect(cocos2d::Vec2 position);
	void cutTree(cocos2d::Vec2 position);
protected:
    Forest();
    virtual ~Forest();

private:
    bool initMap();
    cocos2d::EventListenerMouse* _mouseListener;

};

#endif // __FOREST_H__