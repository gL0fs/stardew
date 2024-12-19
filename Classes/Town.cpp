#include "Town.h"
USING_NS_CC;

Town::Town()
{
}

Town::~Town()
{
}
Scene* Town::createScene()
{
    auto scene = Scene::create();

    auto layer = Town::create();

    if (layer != nullptr)
    {
        scene->addChild(layer);
    }
    return scene;
}
Town* Town::create()
{
    Town* town = new (std::nothrow) Town();
    if (town && town->initMap())
    {
        town->autorelease();
        return town;
    }
    CC_SAFE_DELETE(town);
    return nullptr;
}

bool Town::init()
{
    if (!BaseMapLayer::init())
    {
        return false;
    }

    return true;
}

bool Town::initMap()
{
    if (!init())
    {
        return false;
    }

    loadMap("Town/town.tmx");
    initializePlayer();

    return true;
}