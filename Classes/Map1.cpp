#include "Map1.h"
#include "cocos2d.h"
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support



USING_NS_CC;
Map1::Map1()
{
    // ����һ��ũ��
    _farm = new Farm();
    this->addChild(_farm);  // ��ũ�����뵽 Map1 ����
}

Map1::~Map1()
{
    // ����ũ����Դ
    delete _farm;
}
Scene* Map1::createScene()
{
    // ����һ���������󣬲�Ҫ�Զ��ͷ�
    auto scene = Scene::create();

    // ���� Mine1 ʵ����������Ϊ�������ӽڵ�
    auto layer = Map1::create();

    // ��� layer �����ɹ�������ӵ�������
    if (layer != nullptr)
    {
        scene->addChild(layer);
    }

    // ���س�������
    return scene;
}
Map1* Map1::create()
{
    Map1* map1 = new (std::nothrow) Map1();
    if (map1 && map1->initMap())
    {
        map1->autorelease();
        return map1;
    }
    CC_SAFE_DELETE(map1);
    return nullptr;
}

bool Map1::init()
{
    // ���ȣ����û���� init ����
    if (!BaseMapLayer::init()) {
        return false;
    }


    // ���ö�ʱ�����£��Ա� update ����������
    this->scheduleUpdate();

    // ������������ Mine1 �ض��ĳ�ʼ������

    return true;
}
bool Map1::initMap()
{
    if (!init())
    {
        return false;
    }
    // ���û���ķ��������ص�ͼ
    loadMap("Farm3.tmx"); // ������ĵ�ͼ�ļ���Ϊ Mine1.tmx



    initializePlayer();

    // ����������κ��ض��ĵ�ͼ��ʼ������

    return true;
}

void Map1::switchMap(const std::string& mapName,int path) {
    return;
}