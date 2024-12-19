#pragma once
#ifndef __TEST_H__
#define __TEST_H__

#include "BaseMapLayer.h"
#include "Player.h"
#include "Mine.h"
#include "MainMenuScene.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"

class Test : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene();
    static Test* create();
    virtual bool init() override;
    void switchMap(const std::string& mapName) override;
protected:
    Test();
    virtual ~Test();

private:
    bool initMap();
	
};

#endif // __MAP1_H__