#pragma once
#ifndef __MAP1_H__
#define __MAP1_H__

#include "BaseMapLayer.h"

class Map1 : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene();
    static Map1* create();
    virtual bool init() override;

protected:
    Map1();
    virtual ~Map1();

private:
    bool initMap();
};

#endif // __MAP1_H__