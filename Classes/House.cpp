#include "House.h"  // ͷ�ļ�����Ϊ House.h
#include "cocos2d.h"
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support
USING_NS_CC;
Scene* House::createScene(const std::string& spawnPointName)  // �� MyFarm ��Ϊ House
{
    // ����һ���������󣬲�Ҫ�Զ��ͷ�
    auto scene = Scene::create();
    // ���� House ʵ����������Ϊ�������ӽڵ�
    auto layer = House::create(spawnPointName);
    // ��� layer �����ɹ�������ӵ�������
    if (layer != nullptr)
    {
        scene->addChild(layer);
        TimeManager* timeManager = TimeManager::getInstance();
        // ȷ��TimeManagerֻ����ʼ��һ��
        static bool timeManagerInitialized = false;
        if (!timeManagerInitialized) {
            timeManager->init();
            timeManagerInitialized = true;
        }

        // ȷ��TimeManagerֻ��һ�����ڵ�
        if (timeManager->getParent()) {
            timeManager->removeFromParent();
        }
        scene->addChild(timeManager);
        // �������ϵͳ
        WeatherSystem* weatherSystem = WeatherSystem::getInstance();
        // ȷ��TimeManagerֻ����ʼ��һ��
        static bool weatherSystemInitialized = false;
        if (!weatherSystemInitialized) {
            weatherSystem->init();
            weatherSystemInitialized = true;
        }
       
        // ȷ�� WeatherSystem ֻ��һ�����ڵ�
        if (weatherSystem->getParent()) {
            weatherSystem->removeFromParent();
        }
        scene->addChild(weatherSystem);
    }
    // ���س�������
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
    inventory = new Inventory(24);  // 24�񱳰�

    //// ��ʼ������ϵͳ
    //initializeAnimals();


    // ���ô�������
    setupTouchListener();

    // �����µ�һ�������
    setupNewDayListener();

    return true;
}

//void House::initializeAnimals() {
//    // ���һЩ��ʼ����
//    addAnimal("Golden Chiken", Vec2(300, 200));  // ���Ը�����Ҫ����λ��
//    addAnimal("Golden Chiken", Vec2(400, 200));
//    addAnimal("White Cow", Vec2(500, 200));
//}

void House::addAnimal(const std::string& type, const Vec2& position) {
    Animal animal;
    animal.type = type;
    animal.harvestedToday = false;
    animal.position = position;

    // ��������
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
    // ��ȡʱ�������
    auto timeManager = TimeManager::getInstance();

    // ��ʾ˯����ʾ
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto sleepLabel = Label::createWithTTF("˯����...", "Fonts/pixel_font.ttf", 40);
    sleepLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(sleepLabel, 100);

    // ��������
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
                // ����Ŀ�귶Χ�����ĵ�
                float centerX = (119.62 + 75.37 + 118.12 + 75.00) / 4;
                float centerY = (52.13 + 84.38 + 84.00 + 48.75) / 4;

                // ���������������
                _bedObject->x = centerX - (_bedObject->width / 2);
                _bedObject->y = centerY - (_bedObject->height / 2);

                auto debugDraw = DrawNode::create();
                debugDraw->setName("bedDebug");

                // ���ƴ��ķ�Χ����ɫ���Σ�
                Vec2 vertices[] = {
                    Vec2(_bedObject->x, _bedObject->y),
                    Vec2(_bedObject->x + _bedObject->width, _bedObject->y),
                    Vec2(_bedObject->x + _bedObject->width, _bedObject->y + _bedObject->height),
                    Vec2(_bedObject->x, _bedObject->y + _bedObject->height)
                };
               

                this->addChild(debugDraw, 100);  // ȷ�������ϲ�ɼ�

                CCLOG("Added debug rectangle for bed at: (%.2f, %.2f), size: %.2f x %.2f",
                    _bedObject->x, _bedObject->y, _bedObject->width, _bedObject->height);
                break;
            }
        }
    }

    return true;
}

bool House::onTouchBegan(Touch* touch, Event* event) {



    Vec2 touchLocation = touch->getLocation(); // ��ȡ��Ļ����λ��
    Vec2 locationInNode = this->convertToNodeSpace(touchLocation); // ת��Ϊ�ڵ�����ϵ

    // ��ת Y ��
    Size mapSize = _map->getMapSize();
    Size tileSize = _map->getTileSize();
    float mapHeight = mapSize.height * tileSize.height;
    locationInNode.y = mapHeight - locationInNode.y;


    // ��Ӵ�����Ŀ��ӻ�
    auto touchDebug = DrawNode::create();
    touchDebug->drawDot(locationInNode, 5, Color4F(0, 1, 0, 1));  // ��ɫ��
    this->addChild(touchDebug, 100);

    // 3���ɾ����������
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

    // ����һ������Ľ�������
    float extraSpace = 30.0f;
    Rect bedRect(
        _bedObject->x - extraSpace,
        _bedObject->y - extraSpace,
        _bedObject->width + (extraSpace * 2),
        _bedObject->height + (extraSpace * 2)
    );

    // ���µ��Ի���
    auto debugDraw = static_cast<DrawNode*>(this->getChildByName("bedDebug"));
    if (debugDraw) {
        debugDraw->clear();
        // ����ʵ�ʵĴ����򣨺�ɫ��
        Vec2 bedVertices[] = {
            Vec2(_bedObject->x, _bedObject->y),
            Vec2(_bedObject->x + _bedObject->width, _bedObject->y),
            Vec2(_bedObject->x + _bedObject->width, _bedObject->y + _bedObject->height),
            Vec2(_bedObject->x, _bedObject->y + _bedObject->height)
        };
        debugDraw->drawPolygon(bedVertices, 4, Color4F(1, 0, 0, 0.5), 1, Color4F(1, 1, 1, 1));

        // ���ƽ���������ɫ��
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
            // ��ȡ����İ�Χ��
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
            // ��Ӽ���������
            inventory->addItemToInventory("egg", 1);
            animal->harvestedToday = true;

            // ��������ջ񶯻�����Ч
            // ...
        }
        // �����������������������ջ��߼�
    }
}

void House::setupNewDayListener() {
    // �����µ�һ���¼�
    auto newDayListener = EventListenerCustom::create("new_day", CC_CALLBACK_1(House::onNewDay, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(newDayListener, this);
}

void House::onNewDay(EventCustom* event) {
    // �������ж�����ջ�״̬
    for (auto& animal : animals) {
        animal.harvestedToday = false;
    }
}