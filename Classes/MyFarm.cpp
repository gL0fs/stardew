#include "MyFarm.h"
#include "cocos2d.h"
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support

USING_NS_CC;

MyFarm::MyFarm()
{
    // 创建一个农场
    _farm = new Farm();
    this->addChild(_farm);  // 将农场加入到 MyFarm 层中
}

MyFarm::~MyFarm()
{
    // 清理农场资源
    delete _farm;
}

Scene* MyFarm::createScene()
{
    // 创建一个场景对象，不要自动释放
    auto scene = Scene::create();

    // 创建 MyFarm 实例，并设置为场景的子节点
    auto layer = MyFarm::create();

    // 如果 layer 创建成功，则添加到场景中
    if (layer != nullptr)
    {
        scene->addChild(layer);
    }

    // 返回场景对象
    return scene;
}

MyFarm* MyFarm::create()
{
    MyFarm* myFarm = new (std::nothrow) MyFarm();
    if (myFarm && myFarm->initMap())
    {
        myFarm->autorelease();
        return myFarm;
    }
    CC_SAFE_DELETE(myFarm);
    return nullptr;
}

bool MyFarm::init()
{
    // 首先，调用基类的 init 方法
    if (!BaseMapLayer::init()) {
        return false;
    }

    // 在这里可以添加 MyFarm 特定的初始化代码

    return true;
}

bool MyFarm::initMap()
{
    if (!init())
    {
        return false;
    }

    // 调用基类的方法来加载地图
    loadMap("Farm3.tmx"); // 假设你的地图文件名为 Farm3.tmx
    // 创建并添加时间UI
    auto visibleSize = Director::getInstance()->getVisibleSize();
    _timeUI = GameTimeUI::create();
    _timeUI->setPosition(Vec2(visibleSize.width - 120, visibleSize.height - 50));
    this->addChild(_timeUI, 10);  // 使用较高的Z序确保UI显示在最上层
    initializePlayer();

    return true;
}

void MyFarm::switchMap(const std::string& mapName,int path) {
    return;
}
