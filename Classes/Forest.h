#pragma once
#ifndef __FOREST_H__
#define __FOREST_H__

#include "BaseMapLayer.h"
#include "Player.h"
#include "Mine.h"
#include "Map1.h"
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
protected:
    Forest();
    virtual ~Forest();

private:
    bool initMap();

};

#endif // __FOREST_H__