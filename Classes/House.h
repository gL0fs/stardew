#ifndef __House_H__ 
#define __House_H__
#include "House.h"  
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support

class House : public BaseMapLayer 
{
public:
    static cocos2d::Scene* createScene(const std::string& spawnPointName);  // ������������
    static House* create(const std::string& spawnPointName);  // ���� House ʵ��
    bool init() override;  // ���� init ������ȷ���� virtual



private:

    bool initMap(const std::string& spawnPointName) override;  // ��ʼ����ͼ����
};

#endif

