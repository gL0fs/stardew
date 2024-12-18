#pragma once
#ifndef __MINE_H__
#define __MINE_H__

#include "BaseMapLayer.h"

class Mine : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene();
    static Mine* create();
    virtual bool init() override;
    void Mine::initMouseEvent() override;
    cocos2d::Vec2 Mine::getTileCoordForPosition(cocos2d::Vec2 position);
    void Mine::removeMineralAtTileCoord(cocos2d::Vec2 tileCoord);
    void Mine::initializeNaijiuMap();
    bool initMap();
protected:
    Mine();
    virtual ~Mine();
    std::map<std::pair<int, int>, int> tileNaijiuMap; // �洢��ש������;öȵ�ӳ��
private:
    
    TMXTiledMap* minemap;
    TMXLayer* mineralsLayer;
};

#endif // __MINE_H__   