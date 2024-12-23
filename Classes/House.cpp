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
        TimeManager* timeManager = TimeManager::getInstance();
        // 确保TimeManager只被初始化一次
        static bool timeManagerInitialized = false;
        if (!timeManagerInitialized) {
            timeManager->init();
            timeManagerInitialized = true;
        }

        // 确保TimeManager只有一个父节点
        if (timeManager->getParent()) {
            timeManager->removeFromParent();
        }
        scene->addChild(timeManager);
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
    auto objectGroup = _map->getObjectGroup("Object");
    if (objectGroup) {
        auto bedObjects = objectGroup->getObjects();
        for (const auto& obj : bedObjects) {
            auto bedObj = obj.asValueMap();
            if (bedObj["name"].asString() == "Bed") {
                _bedObject = new BedObject();  // 使用 BedObject 类型
                _bedObject->x = bedObj["x"].asFloat();
                _bedObject->y = bedObj["y"].asFloat();
                _bedObject->width = bedObj["width"].asFloat();
                _bedObject->height = bedObj["height"].asFloat();
                break;
            }
        }
    }
    
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
bool House::checkBedInteraction(const Vec2& position) {
    if (!_bedObject) return false;

    Rect bedRect(_bedObject->x, _bedObject->y, _bedObject->width, _bedObject->height);
    return bedRect.containsPoint(position);
}

void House::goToSleep() {
    // 获取时间管理器
    auto timeManager = TimeManager::getInstance();

    // 显示睡觉提示
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto sleepLabel = Label::createWithTTF("睡觉中...", "Fonts/pixel_font.ttf", 40);
    sleepLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(sleepLabel, 100);

    // 淡出动画
    auto fadeOut = FadeOut::create(1.0f);
    auto fadeIn = FadeIn::create(1.0f);
    auto removeLabel = RemoveSelf::create();
    auto sleep = CallFunc::create([timeManager]() {
        timeManager->playerGoToBed();
        });

    sleepLabel->runAction(Sequence::create(
        fadeOut,
        sleep,
        fadeIn,
        DelayTime::create(1.0f),
        removeLabel,
        nullptr
    ));
}

bool House::onTouchBegan(Touch* touch, Event* event) {
    Vec2 touchLocation = touch->getLocation();
    Vec2 locationInNode = this->convertToNodeSpace(touchLocation);

    // 检查是否点击了床
    if (checkBedInteraction(locationInNode)) {
        goToSleep();
        return true;
    }

    // 原有的动物交互逻辑
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