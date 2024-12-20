#pragma once
#ifndef __FESTIVAL_H__
#define __FESTIVAL_H__

#include "BaseMapLayer.h"

class Festival : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene();
    static Festival* create();
    virtual bool init() override;
    void initMouseEvent(); // 去掉了 Festival::，因为这是在类定义内部
    cocos2d::Vec2 getTileCoordForPosition(cocos2d::Vec2 position); // 同上
    void Festival::switchMap(const std::string& mapName, int path)override;
   
    bool initMap();
   
protected:
    Festival(); // 构造函数
    virtual ~Festival(); // 析构函数
    std::map<std::pair<int, int>, int> tileNaijiuMap; // 存储瓷砖坐标和耐久度的映射
private:
    cocos2d::EventListenerMouse* _mouseListener;
    TMXTiledMap* festivalMap; // 将 minemap 重命名为更合适的名称
   
};

#endif // __FESTIVAL_H__