#include "MyFarm.h"
#include "cocos2d.h"
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support

USING_NS_CC;

MyFarm::MyFarm()
{
    // ����һ��ũ��
    _farm = new Farm();
    this->addChild(_farm);  // ��ũ�����뵽 MyFarm ����
}

MyFarm::~MyFarm()
{
    // ����ũ����Դ
    delete _farm;
}

Scene* MyFarm::createScene()
{
    // ����һ���������󣬲�Ҫ�Զ��ͷ�
    auto scene = Scene::create();

    // ���� MyFarm ʵ����������Ϊ�������ӽڵ�
    auto layer = MyFarm::create();

    // ��� layer �����ɹ�������ӵ�������
    if (layer != nullptr)
    {
        scene->addChild(layer);
    }

    // ���س�������
    return scene;
}

MyFarm* MyFarm::create()
{
    MyFarm* myFarm = new (std::nothrow) MyFarm();
    if (myFarm && myFarm->initMap())
    {
        myFarm->autorelease();
        return myFarm;
    }
    CC_SAFE_DELETE(myFarm);
    return nullptr;
}

bool MyFarm::init()
{
    // ���ȣ����û���� init ����
    if (!BaseMapLayer::init()) {
        return false;
    }

    // ������������ MyFarm �ض��ĳ�ʼ������

    return true;
}

bool MyFarm::initMap()
{
    if (!init())
    {
        return false;
    }

    // ���û���ķ��������ص�ͼ
    loadMap("Farm3.tmx"); // ������ĵ�ͼ�ļ���Ϊ Farm3.tmx
    // ���������ʱ��UI
    auto visibleSize = Director::getInstance()->getVisibleSize();
    _timeUI = GameTimeUI::create();
    _timeUI->setPosition(Vec2(visibleSize.width - 120, visibleSize.height - 50));
    this->addChild(_timeUI, 10);  // ʹ�ýϸߵ�Z��ȷ��UI��ʾ�����ϲ�
    initializePlayer();

    return true;
}

void MyFarm::switchMap(const std::string& mapName,int path) {
    return;
}
