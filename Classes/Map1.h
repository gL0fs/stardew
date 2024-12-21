#ifndef __MAP1_H__
#define __MAP1_H__
#include "Farm.h" 
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support

class Map1 : public BaseMapLayer
{
public:
    static cocos2d::Scene* createScene();
    static Map1* create();
    virtual bool init();  // ���� init ������ȷ���� virtual
protected:
    Map1();
    virtual ~Map1();
private:
    Farm* _farm;
    bool Map1::initMap();
    cocos2d::Sprite* _player; // ��ɫ����
    cocos2d::Vec2 _velocity; // ��ɫ�ƶ��ٶ�
	void switchMap(const std::string& mapName,int path) override;
};
#endif