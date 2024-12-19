#include "Forest.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

Forest::Forest()
{
}

Forest::~Forest()
{
}
Scene* Forest::createScene(int path)
{
    auto scene = Scene::create();
    
    auto layer = Forest::create(path);
	
    if (layer != nullptr)
    {
        scene->addChild(layer);
    }
    return scene;
}
Forest* Forest::create(int path)
{
    Forest* forest = new (std::nothrow) Forest();
	forest->_path = path;
    if (forest && forest->initMap())
    {
        forest->autorelease();
        return forest;
    }
    CC_SAFE_DELETE(forest);
    return nullptr;
}

bool Forest::init()
{
    if (!BaseMapLayer::init())
    {
        return false;
    }

    return true;
}

bool Forest::initMap()
{
    if (!init())
    {
        return false;
    }


    loadMap("Forest/Forest.tmx");//加入地图层 
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

void Forest::switchMap(const std::string& mapName,int path)
{
    if (mapName == "test")
    {
        /*if (SceneManager::getInstance().isMapInHistory("test"))
        {
            SceneManager::getInstance().returnToPreviousScene();
            return;
        }
        else {
        */
            auto scene = Test::createScene(path);
            SceneManager::getInstance().goToScene(scene, "forest");
        //}
    }
	else if (mapName == "farm")
	{
		if (SceneManager::getInstance().isMapInHistory("farm"))
		{
			SceneManager::getInstance().returnToPreviousScene();
			return;
		}
		else {
			auto scene = Map1::createScene();
			SceneManager::getInstance().goToScene(scene, "forest");
		}
	}
    else
    {
        CCLOG("Unknown map: %s", mapName.c_str());
    }
}

