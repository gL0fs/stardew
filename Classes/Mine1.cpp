#include "Mine1.h"

USING_NS_CC;

Mine1::Mine1()
{
}

Mine1::~Mine1()
{
    // 释放资源，如果需要的话
}
Scene* Mine1::createScene()
{
    // 创建一个场景对象，不要自动释放
    auto scene = Scene::create();

    // 创建 Mine1 实例，并设置为场景的子节点
    auto layer = Mine1::create();

    // 如果 layer 创建成功，则添加到场景中
    if (layer != nullptr)
    {
        scene->addChild(layer);
    }

    // 返回场景对象
    return scene;
}
Mine1* Mine1::create()
{
    Mine1* map1 = new (std::nothrow) Mine1();
    if (map1 && map1->initMap())
    {
        map1->autorelease();
        return map1;
    }
    CC_SAFE_DELETE(map1);
    return nullptr;
}

bool Mine1::init()
{
    // 首先，调用基类的 init 方法
    if (!BaseMapLayer::init())
    {
        return false;
    }

    // 设置定时器更新，以便 update 方法被调用
    this->scheduleUpdate();

    // 在这里可以添加 Mine1 特定的初始化代码

    return true;
}
bool Mine1::initMap()
{
    if (!init())
    {
        return false;
    }

    // 调用基类的方法来加载地图
    loadMap("mine1.tmx"); // 假设你的地图文件名为 Mine1.tmx

    // 设置玩家位置，假设对象组名为 "Objects"，生成点名为 "SpawnPoint"
    setPlayerPosition("Objects", "SpawnPoint");

    // 在这里添加任何特定的地图初始化代码

    return true;
}