#include "House.h"  // ͷ�ļ�����Ϊ House.h
#include "cocos2d.h"
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support

USING_NS_CC;

Scene* House::createScene()  // �� MyFarm ��Ϊ House
{
    // ����һ���������󣬲�Ҫ�Զ��ͷ�
    auto scene = Scene::create();

    // ���� House ʵ����������Ϊ�������ӽڵ�
    auto layer = House::create();

    // ��� layer �����ɹ�������ӵ�������
    if (layer != nullptr)
    {
        scene->addChild(layer);
    }

    // ���س�������
    return scene;
}

House* House::create()  // �� MyFarm ��Ϊ House
{
    House* house = new (std::nothrow) House();
    if (house && house->initMap())
    {
        house->autorelease();
        return house;
    }
    CC_SAFE_DELETE(house);
    return nullptr;
}

bool House::init()  // �� MyFarm ��Ϊ House
{
    // ���ȣ����û���� init ����
    if (!BaseMapLayer::init()) {
        return false;
    }

    // ������������ House �ض��ĳ�ʼ������

    return true;
}

bool House::initMap()  // �� MyFarm ��Ϊ House
{
    if (!init())
    {
        return false;
    }

    // ���û���ķ��������ص�ͼ
    loadMap("house1.tmx");  // ����Ϊ house.tmx

    initializePlayer();

    return true;
}

void House::switchMap(const std::string& mapName,int path) {  // �� MyFarm ��Ϊ House
    return;
}
