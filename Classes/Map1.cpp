#include "Map1.h"
#include "cocos2d.h"
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support



USING_NS_CC;
Map1::Map1()
{
    // 创建一个农场
    _farm = new Farm();
    this->addChild(_farm);  // 将农场加入到 Map1 层中
}

Map1::~Map1()
{
    // 清理农场资源
    delete _farm;
}
Scene* Map1::createScene()
{
    // 创建一个场景对象，不要自动释放
    auto scene = Scene::create();

    // 创建 Mine1 实例，并设置为场景的子节点
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
    if (!BaseMapLayer::init()) {
        return false;
    }


    // 设置定时器更新，以便 update 方法被调用
    this->scheduleUpdate();

    // 在这里可以添加 Mine1 特定的初始化代码

    return true;
}
bool Map1::initMap()
{
    if (!init())
    {
        return false;
    }
    // 调用基类的方法来加载地图
    loadMap("Farm3.tmx"); // 假设你的地图文件名为 Mine1.tmx



    initializePlayer();

    // 在这里添加任何特定的地图初始化代码

    return true;
}

void Map1::switchMap(const std::string& mapName,int path) {
    return;
}