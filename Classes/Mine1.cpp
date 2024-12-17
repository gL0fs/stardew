#include "Mine1.h"

USING_NS_CC;

Mine1::Mine1()
{
}

Mine1::~Mine1()
{
    // �ͷ���Դ�������Ҫ�Ļ�
}
Scene* Mine1::createScene()
{
    // ����һ���������󣬲�Ҫ�Զ��ͷ�
    auto scene = Scene::create();

    // ���� Mine1 ʵ����������Ϊ�������ӽڵ�
    auto layer = Mine1::create();

    // ��� layer �����ɹ�������ӵ�������
    if (layer != nullptr)
    {
        scene->addChild(layer);
    }

    // ���س�������
    return scene;
}
Mine1* Mine1::create()
{
    Mine1* map1 = new (std::nothrow) Mine1();
    if (map1 && map1->initMap())
    {
        map1->autorelease();
        return map1;
    }
    CC_SAFE_DELETE(map1);
    return nullptr;
}

bool Mine1::init()
{
    // ���ȣ����û���� init ����
    if (!BaseMapLayer::init())
    {
        return false;
    }

    // ���ö�ʱ�����£��Ա� update ����������
    this->scheduleUpdate();

    // ������������ Mine1 �ض��ĳ�ʼ������

    return true;
}
bool Mine1::initMap()
{
    if (!init())
    {
        return false;
    }

    // ���û���ķ��������ص�ͼ
    loadMap("mine1.tmx"); // ������ĵ�ͼ�ļ���Ϊ Mine1.tmx

    // �������λ�ã������������Ϊ "Objects"�����ɵ���Ϊ "SpawnPoint"
	initializePlayer();

    // ����������κ��ض��ĵ�ͼ��ʼ������

    return true;
}

void Mine1::switchMap(const std::string& mapName)
{
	// ����������л���ͼ�Ĵ���
    return;
}