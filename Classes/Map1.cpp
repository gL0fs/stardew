#include "Map1.h"

USING_NS_CC;

Map1::Map1()
{
}

Map1::~Map1()
{
    // �ͷ���Դ�������Ҫ�Ļ�
}
Scene* Map1::createScene()
{
    // ����һ���������󣬲�Ҫ�Զ��ͷ�
    auto scene = Scene::create();

    // ���� Map1 ʵ����������Ϊ�������ӽڵ�
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
    if (!BaseMapLayer::init())
    {
        return false;
    }

    // ���ö�ʱ�����£��Ա� update ����������
    this->scheduleUpdate();

    // ������������ Map1 �ض��ĳ�ʼ������

    return true;
}
bool Map1::initMap()
{
    if (!init())
    {
        return false;
    }

    // ���û���ķ��������ص�ͼ
    loadMap("mine1.tmx"); // ������ĵ�ͼ�ļ���Ϊ map1.tmx

    // �������λ�ã������������Ϊ "Objects"�����ɵ���Ϊ "SpawnPoint"
    setPlayerPosition("Objects", "SpawnPoint");

    // ����������κ��ض��ĵ�ͼ��ʼ������

    return true;
}