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
    static cocos2d::Scene* createScene(const std::string& spawnPointName);
    static Test* create(const std::string& spawnPointName);
    bool init() override;

protected:
    Test();
    virtual ~Test();

private:
    bool initMap(const std::string& spawnPointName)override;

};

#endif // __MAP1_H__