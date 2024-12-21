#include "House.h"  // 头文件更改为 House.h
#include "cocos2d.h"
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support

USING_NS_CC;

Scene* House::createScene()  // 将 MyFarm 改为 House
{
    // 创建一个场景对象，不要自动释放
    auto scene = Scene::create();

    // 创建 House 实例，并设置为场景的子节点
    auto layer = House::create();

    // 如果 layer 创建成功，则添加到场景中
    if (layer != nullptr)
    {
        scene->addChild(layer);
    }

    // 返回场景对象
    return scene;
}

House* House::create()  // 将 MyFarm 改为 House
{
    House* house = new (std::nothrow) House();
    if (house && house->initMap())
    {
        house->autorelease();
        return house;
    }
    CC_SAFE_DELETE(house);
    return nullptr;
}

bool House::init()  // 将 MyFarm 改为 House
{
    // 首先，调用基类的 init 方法
    if (!BaseMapLayer::init()) {
        return false;
    }

    // 在这里可以添加 House 特定的初始化代码

    return true;
}

bool House::initMap()  // 将 MyFarm 改为 House
{
    if (!init())
    {
        return false;
    }

    // 调用基类的方法来加载地图
    loadMap("house.tmx");  // 更改为 house.tmx

    initializePlayer();

    return true;
}

void House::switchMap(const std::string& mapName) {  // 将 MyFarm 改为 House
    return;
}
