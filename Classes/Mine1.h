#pragma once

#ifndef __MINE1_H__
#define __MINE1_H__

#include "BaseMapLayer.h"

class Mine1 : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene();
    static Mine1* create();
    bool Mine1::init();


protected:
    Mine1();
    virtual ~Mine1();

private:
    bool Mine1::initMap();
};

#endif // __Mine1_H__