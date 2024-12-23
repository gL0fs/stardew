#include "House.h"  // 头文件更改为 House.h
#include "cocos2d.h"
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support
USING_NS_CC;
Scene* House::createScene(const std::string& spawnPointName)  // 将 MyFarm 改为 House
{
    // 创建一个场景对象，不要自动释放
    auto scene = Scene::create();
    // 创建 House 实例，并设置为场景的子节点
    auto layer = House::create(spawnPointName);
    // 如果 layer 创建成功，则添加到场景中
    if (layer != nullptr)
    {
        scene->addChild(layer);
    }
    // 返回场景对象
    return scene;
}
House* House::create(const std::string& spawnPointName)  
{
    House* house = new (std::nothrow) House();
    if (house && house->initMap(spawnPointName))
    {
        house->autorelease();
        return house;
    }
    CC_SAFE_DELETE(house);
    return nullptr;
}
bool House::initMap(const std::string& spawnPointName) 
{
    if (!init())
    {
        return false;
    }
    // 调用基类的方法来加载地图
    loadMap("house1.tmx");  // 更改为 house.tmx
    initializePlayer(spawnPointName);
    return true;
}


bool House::init() {
    if (!BaseMapLayer::init()) {
        return false;
    }
    inventory = new Inventory(24);  // 24格背包

    // 初始化动物系统
    initializeAnimals();

    // 设置触摸监听
    setupTouchListener();

    // 设置新的一天监听器
    setupNewDayListener();

    return true;
}

void House::initializeAnimals() {
    // 添加一些初始动物
    addAnimal("Golden Chiken", Vec2(300, 200));  // 可以根据需要调整位置
    addAnimal("Golden Chiken", Vec2(400, 200));
    addAnimal("White Cow", Vec2(500, 200));
}

void House::addAnimal(const std::string& type, const Vec2& position) {
    Animal animal;
    animal.type = type;
    animal.harvestedToday = false;
    animal.position = position;

    // 创建精灵
    animal.sprite = Sprite::create(type + ".png");
    if (animal.sprite) {
        animal.sprite->setPosition(position);
        this->addChild(animal.sprite);
    }

    animals.push_back(animal);
}

void House::setupTouchListener() {
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(House::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool House::onTouchBegan(Touch* touch, Event* event) {
    Vec2 touchLocation = touch->getLocation();

    // 查找被触摸的动物
    Animal* touchedAnimal = findTouchedAnimal(touchLocation);
    if (touchedAnimal) {
        harvestAnimal(touchedAnimal);
        return true;
    }

    return false;
}

Animal* House::findTouchedAnimal(const Vec2& touchPos) {
    for (auto& animal : animals) {
        if (animal.sprite) {
            // 获取精灵的包围盒
            Rect bounds = animal.sprite->getBoundingBox();
            if (bounds.containsPoint(touchPos)) {
                return &animal;
            }
        }
    }
    return nullptr;
}

void House::harvestAnimal(Animal* animal) {
    if (!animal->harvestedToday) {
        if (animal->type == "Golden Chiken") {
            // 添加鸡蛋到背包
            inventory->addItemToInventory("egg", 1);
            animal->harvestedToday = true;

            // 可以添加收获动画或音效
            // ...
        }
        // 可以在这里添加其他动物的收获逻辑
    }
}

void House::setupNewDayListener() {
    // 监听新的一天事件
    auto newDayListener = EventListenerCustom::create("new_day", CC_CALLBACK_1(House::onNewDay, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(newDayListener, this);
}

void House::onNewDay(EventCustom* event) {
    // 重置所有动物的收获状态
    for (auto& animal : animals) {
        animal.harvestedToday = false;
    }
}