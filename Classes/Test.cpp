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
 
    loadMap("mine1.tmx"); 
	initializePlayer();

    return true;
}