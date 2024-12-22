#pragma once
#ifndef __FESTIVAL_H__
#define __FESTIVAL_H__

#include "BaseMapLayer.h"

class Festival : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene(const std::string& spawnPointName);
    static Festival* create(const std::string& spawnPointName);
    bool init() override;
    void initMouseEvent() override; // ȥ���� Festival::����Ϊ�������ඨ���ڲ�
    cocos2d::Vec2 getTileCoordForPosition(cocos2d::Vec2 position); // ͬ��
   
    bool initMap(const std::string& spawnPointName) override;
   
protected:
    Festival(); // ���캯��
    virtual ~Festival(); // ��������
    std::map<std::pair<int, int>, int> tileNaijiuMap; // �洢��ש������;öȵ�ӳ��
private:
    cocos2d::EventListenerMouse* _mouseListener;
    TMXTiledMap* festivalMap; // �� minemap ������Ϊ�����ʵ�����
   
};

#endif // __FESTIVAL_H__