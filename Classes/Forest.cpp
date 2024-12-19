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
Scene* Forest::createScene()
{
    auto scene = Scene::create();

    auto layer = Forest::create();

    if (layer != nullptr)
    {
        scene->addChild(layer);
    }
    return scene;
}
Forest* Forest::create()
{
    Forest* forest = new (std::nothrow) Forest();
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


    loadMap("Forest/Forest.tmx");//�����ͼ�� 
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
	if (toolbar->getParent() == nullptr)
        toolbarLayout->addChild(toolbar);
    CCLOG("add toolbar");
    return true;

}

void Forest::switchMap(const std::string& mapName)
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
            SceneManager::getInstance().goToScene(scene, "mine");
        }
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
			SceneManager::getInstance().goToScene(scene, "farm");
		}
	}
    else
    {
        CCLOG("Unknown map: %s", mapName.c_str());
    }
}

