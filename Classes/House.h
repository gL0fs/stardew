#ifndef __House_H__ 
#define __House_H__
#include "House.h"  
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support

class House : public BaseMapLayer 
{
public:
    static cocos2d::Scene* createScene();  // ������������
    static House* create();  // ���� House ʵ��
    virtual bool init();  // ���� init ������ȷ���� virtual



private:

    bool initMap();  // ��ʼ����ͼ����

    void switchMap(const std::string& mapName,int path) override;  // ���� switchMap ����
};

#endif

