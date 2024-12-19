#pragma once
#ifndef __TEST_H__
#define __TEST_H__

#include "BaseMapLayer.h"
#include "Player.h"
#include "Mine.h"
#include "MainMenuScene.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"
#include "Forest.h"

class Test : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene(int path = 0);
    static Test* create(int path);
    virtual bool init() override;
    void switchMap(const std::string& mapName,int path) override;

protected:
    Test();
    virtual ~Test();

private:
    bool initMap();

};

#endif // __MAP1_H__