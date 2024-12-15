#include "Test.h"

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
 
    loadMap("Forest/Forest.tmx"); 
	initializePlayer();

    return true;
}

void Test::switchMap(const std::string& mapName)
{
    if (mapName == "mine")
    {
        auto scene = Mine1::createScene();
        SceneManager::getInstance().goToScene(scene, "mine");

    }
	else
	{
		CCLOG("Unknown map: %s", mapName.c_str());
	}
}