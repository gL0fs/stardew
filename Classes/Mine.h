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
    void Mine::initMouseEvent() ;
    cocos2d::Vec2 Mine::getTileCoordForPosition(cocos2d::Vec2 position);
    void Mine::removeMineralAtTileCoord(cocos2d::Vec2 tileCoord);
    void Mine::initializeNaijiuMap();
    bool initMap();
    void switchMap(const std::string& mapName,int path) override;
protected:
    Mine();
    virtual ~Mine();
    std::map<std::pair<int, int>, int> tileNaijiuMap; // �洢��ש������;öȵ�ӳ��
private:
    cocos2d::EventListenerMouse* _mouseListener;
    TMXTiledMap* minemap;
    TMXLayer* mineralsLayer;
};

#endif // __MINE_H__   
