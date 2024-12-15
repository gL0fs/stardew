#include "Test.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

Test::Test()
{
}

Test::~Test()
{
}
Scene* Test::createScene()
{
    auto scene = Scene::create();

    auto layer = Test::create();

    if (layer != nullptr)
    {
        scene->addChild(layer);
    }
    return scene;
}
Test* Test::create()
{
    Test* test = new (std::nothrow) Test();
    if (test && test->initMap())
    {
        test->autorelease();
        return test;
    }
    CC_SAFE_DELETE(test);
    return nullptr;
}

bool Test::init()
{
    if (!BaseMapLayer::init())
    {
        return false;
    }

    return true;
}

bool Test::initMap()
{
    if (!init())
    {
        return false;
    }
 
    loadMap("mine1.tmx");//�����ͼ�� 
	initializePlayer();//������Ҳ�

    auto toolbar = Toolbar::getInstance();//������ʵ��
    auto uiLayer = Layer::create();
    this->addChild(uiLayer);

    // ��UI�������toolbar
    int toolbarHeight = 16; // ���蹤�����ĸ߶���16����
    auto winSize = Director::getInstance()->getWinSize();
    auto toolbarLayout = ui::Layout::create();
    toolbarLayout->setSize(Size(winSize.width, toolbarHeight)); // ���ò��ִ�С
    toolbarLayout->setIgnoreAnchorPointForPosition(true);
    toolbarLayout->setPosition(Vec2(0, winSize.height / 2 - toolbarHeight / 2)); // ���ò���λ��Ϊ��Ļ��ֱ����
    uiLayer->addChild(toolbarLayout);

    // ����toolbar����ӵ�����
   
    // ����toolbar��λ��Ϊ���ֵ�����
    toolbar->setPosition(Vec2(toolbarLayout->getContentSize().width / 2, toolbarLayout->getContentSize().height / 2));
    toolbarLayout->addChild(toolbar);
    CCLOG("add toolbar");
    return true;
}