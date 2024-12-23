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
Scene* Test::createScene(const std::string& spawnPointName)
{
    auto scene = Scene::create();

    auto layer = Test::create(spawnPointName);
    if (layer != nullptr)
    {
        scene->addChild(layer);
    }
    return scene;
}
Test* Test::create(const std::string& spawnPointName)
{
    Test* test = new (std::nothrow) Test();
    if (test && test->initMap(spawnPointName))
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

bool Test::initMap(const std::string& spawnPointName)
{
    if (!init())
    {
        return false;
    }


    loadMap("Test/Test.tmx");//加入地图层 
    initializePlayer(spawnPointName);//加入玩家层

    auto toolbar = Toolbar::getInstance();//工具栏实例
    auto uiLayer = Layer::create();
    this->addChild(uiLayer);

    // 在UI层中添加toolbar
    int toolbarHeight = 16; // 假设工具栏的高度是16像素
    auto winSize = Director::getInstance()->getWinSize();
    auto toolbarLayout = ui::Layout::create();
    toolbarLayout->setSize(Size(winSize.width, toolbarHeight)); // 设置布局大小
    toolbarLayout->setIgnoreAnchorPointForPosition(true);
    toolbarLayout->setPosition(Vec2(0, winSize.height / 2 - toolbarHeight / 2)); // 设置布局位置为屏幕垂直中心
    uiLayer->addChild(toolbarLayout);

    // 创建toolbar并添加到布局

    // 设置toolbar的位置为布局的中心

    toolbar->setPosition(Vec2(toolbarLayout->getContentSize().width / 2, toolbarLayout->getContentSize().height / 2));
    if (toolbar->getParent() == nullptr)
        toolbarLayout->addChild(toolbar);
    CCLOG("add toolbar");
    return true;

}
