#pragma once
#ifndef __TOWN_H__
#define __TOWN_H__

#include "BaseMapLayer.h"

class Town : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene();
    static Town* create();
    virtual bool init() override;


protected:
    Town();
    virtual ~Town();

private:
    bool initMap();
};

#endif // __MAP1_H__