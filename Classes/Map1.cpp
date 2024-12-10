#include "Map1.h"

USING_NS_CC;

Map1::Map1()
{
}

Map1::~Map1()
{
    // 释放资源，如果需要的话
}
Scene* Map1::createScene()
{
    // 创建一个场景对象，不要自动释放
    auto scene = Scene::create();

    // 创建 Map1 实例，并设置为场景的子节点
    auto layer = Map1::create();

    // 如果 layer 创建成功，则添加到场景中
    if (layer != nullptr)
    {
        scene->addChild(layer);
    }

    // 返回场景对象
    return scene;
}
Map1* Map1::create()
{
    Map1* map1 = new (std::nothrow) Map1();
    if (map1 && map1->initMap())
    {
        map1->autorelease();
        return map1;
    }
    CC_SAFE_DELETE(map1);
    return nullptr;
}

bool Map1::init()
{
    // 首先，调用基类的 init 方法
    if (!BaseMapLayer::init())
    {
        return false;
    }

    // 设置定时器更新，以便 update 方法被调用
    this->scheduleUpdate();

    // 在这里可以添加 Map1 特定的初始化代码

    return true;
}
bool Map1::initMap()
{
    if (!init())
    {
        return false;
    }

    // 调用基类的方法来加载地图
    loadMap("mine1.tmx"); // 假设你的地图文件名为 map1.tmx

    // 设置玩家位置，假设对象组名为 "Objects"，生成点名为 "SpawnPoint"
    setPlayerPosition("Objects", "SpawnPoint");

    // 在这里添加任何特定的地图初始化代码

    return true;
}