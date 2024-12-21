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
Scene* Test::createScene(int path)
{
    auto scene = Scene::create();

    auto layer = Test::create(path);
    if (layer != nullptr)
    {
        scene->addChild(layer);
    }
    return scene;
}
Test* Test::create(int path)
{
    Test* test = new (std::nothrow) Test();
	test->_path = path;
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


    loadMap("Test/Test.tmx");//加入地图层 
    initializePlayer();//加入玩家层

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

void Test::switchMap(const std::string& mapName,int path)
{
    if (mapName == "mine")
    {
		if (SceneManager::getInstance().isMapInHistory("mine"))
		{
			SceneManager::getInstance().returnToPreviousScene();
			return;
        }
        else {
            auto scene = Mine::createScene();
            SceneManager::getInstance().goToScene(scene, "test");
        }
    }
    else if (mapName == "forest")
    {
        /*if (SceneManager::getInstance().isMapInHistory("forest"))
        {
            SceneManager::getInstance().returnToPreviousScene();
            return;
        }
        else {
        */
            auto scene = Forest::createScene(path);
            SceneManager::getInstance().goToScene(scene, "test");
        //}
    }
	else
	{
		CCLOG("Unknown map: %s", mapName.c_str());
	}
}



