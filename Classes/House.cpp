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
        // 添加天气系统
        WeatherSystem* weatherSystem = WeatherSystem::getInstance();
        // 确保TimeManager只被初始化一次
        static bool weatherSystemInitialized = false;
        if (!weatherSystemInitialized) {
            weatherSystem->init();
            weatherSystemInitialized = true;
        }
       
        // 确保 WeatherSystem 只有一个父节点
        if (weatherSystem->getParent()) {
            weatherSystem->removeFromParent();
        }
        scene->addChild(weatherSystem);
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
bool House::init() {
    if (!BaseMapLayer::init()) {
        return false;
    }
    inventory = new Inventory(24);  // 24格背包

    //// 初始化动物系统
    //initializeAnimals();


    // 设置触摸监听
    setupTouchListener();

    // 设置新的一天监听器
    setupNewDayListener();

    return true;
}

//void House::initializeAnimals() {
//    // 添加一些初始动物
//    addAnimal("Golden Chiken", Vec2(300, 200));  // 可以根据需要调整位置
//    addAnimal("Golden Chiken", Vec2(400, 200));
//    addAnimal("White Cow", Vec2(500, 200));
//}

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

bool House::initMap(const std::string& spawnPointName)
{
    if (!init()) {
        return false;
    }

    loadMap("house1.tmx");
    initializePlayer(spawnPointName);

    auto objectGroup = _map->getObjectGroup("Object");
    if (objectGroup) {
        auto bedObjects = objectGroup->getObjects();
        for (const auto& obj : bedObjects) {
            auto bedObj = obj.asValueMap();
            if (bedObj["name"].asString() == "Bed") {
                
                    _bedObject = new BedObject();
                // 计算目标范围的中心点
                float centerX = (119.62 + 75.37 + 118.12 + 75.00) / 4;
                float centerY = (52.13 + 84.38 + 84.00 + 48.75) / 4;

                // 调整床对象的坐标
                _bedObject->x = centerX - (_bedObject->width / 2);
                _bedObject->y = centerY - (_bedObject->height / 2);

                auto debugDraw = DrawNode::create();
                debugDraw->setName("bedDebug");

                // 绘制床的范围（红色矩形）
                Vec2 vertices[] = {
                    Vec2(_bedObject->x, _bedObject->y),
                    Vec2(_bedObject->x + _bedObject->width, _bedObject->y),
                    Vec2(_bedObject->x + _bedObject->width, _bedObject->y + _bedObject->height),
                    Vec2(_bedObject->x, _bedObject->y + _bedObject->height)
                };
               

                this->addChild(debugDraw, 100);  // 确保在最上层可见

                CCLOG("Added debug rectangle for bed at: (%.2f, %.2f), size: %.2f x %.2f",
                    _bedObject->x, _bedObject->y, _bedObject->width, _bedObject->height);
                break;
            }
        }
    }

    return true;
}

bool House::onTouchBegan(Touch* touch, Event* event) {



    Vec2 touchLocation = touch->getLocation(); // 获取屏幕触摸位置
    Vec2 locationInNode = this->convertToNodeSpace(touchLocation); // 转换为节点坐标系

    // 翻转 Y 轴
    Size mapSize = _map->getMapSize();
    Size tileSize = _map->getTileSize();
    float mapHeight = mapSize.height * tileSize.height;
    locationInNode.y = mapHeight - locationInNode.y;


    // 添加触摸点的可视化
    auto touchDebug = DrawNode::create();
    touchDebug->drawDot(locationInNode, 5, Color4F(0, 1, 0, 1));  // 绿色点
    this->addChild(touchDebug, 100);

    // 3秒后删除触摸点标记
    touchDebug->runAction(Sequence::create(
        DelayTime::create(3.0f),
        RemoveSelf::create(),
        nullptr
    ));

    CCLOG("Original touch location: (%.2f, %.2f)", touchLocation.x, touchLocation.y);
    CCLOG("Converted location: (%.2f, %.2f)", locationInNode.x, locationInNode.y);

    if (checkBedInteraction(locationInNode)) {
        CCLOG("Bed interaction detected!");
        goToSleep();
        return true;
    }

    return false;
}

bool House::checkBedInteraction(const Vec2& position) {
    if (!_bedObject) return false;

    // 创建一个更大的交互区域
    float extraSpace = 30.0f;
    Rect bedRect(
        _bedObject->x - extraSpace,
        _bedObject->y - extraSpace,
        _bedObject->width + (extraSpace * 2),
        _bedObject->height + (extraSpace * 2)
    );

    // 更新调试绘制
    auto debugDraw = static_cast<DrawNode*>(this->getChildByName("bedDebug"));
    if (debugDraw) {
        debugDraw->clear();
        // 绘制实际的床区域（红色）
        Vec2 bedVertices[] = {
            Vec2(_bedObject->x, _bedObject->y),
            Vec2(_bedObject->x + _bedObject->width, _bedObject->y),
            Vec2(_bedObject->x + _bedObject->width, _bedObject->y + _bedObject->height),
            Vec2(_bedObject->x, _bedObject->y + _bedObject->height)
        };
        debugDraw->drawPolygon(bedVertices, 4, Color4F(1, 0, 0, 0.5), 1, Color4F(1, 1, 1, 1));

        // 绘制交互区域（蓝色）
        Vec2 interactVertices[] = {
            Vec2(bedRect.origin.x, bedRect.origin.y),
            Vec2(bedRect.origin.x + bedRect.size.width, bedRect.origin.y),
            Vec2(bedRect.origin.x + bedRect.size.width, bedRect.origin.y + bedRect.size.height),
            Vec2(bedRect.origin.x, bedRect.origin.y + bedRect.size.height)
        };
        debugDraw->drawPolygon(interactVertices, 4, Color4F(0, 0, 1, 0.3), 1, Color4F(0, 0, 1, 1));
    }

    bool isInBed = bedRect.containsPoint(position);
    CCLOG("Touch position: (%.2f, %.2f)", position.x, position.y);
    CCLOG("Bed rect: (%.2f, %.2f, %.2f, %.2f)",
        bedRect.origin.x, bedRect.origin.y, bedRect.size.width, bedRect.size.height);
    CCLOG("Is in bed: %d", isInBed);

    return isInBed;
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