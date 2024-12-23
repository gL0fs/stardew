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
bool House::initMap(const std::string& spawnPointName) 
{
    if (!init())
    {
        return false;
    }
    // ���û���ķ��������ص�ͼ
    loadMap("house1.tmx");  // ����Ϊ house.tmx
    initializePlayer(spawnPointName);
    auto objectGroup = _map->getObjectGroup("Object");
    if (objectGroup) {
        auto bedObjects = objectGroup->getObjects();
        for (const auto& obj : bedObjects) {
            auto bedObj = obj.asValueMap();
            if (bedObj["name"].asString() == "Bed") {
                _bedObject = new BedObject();  // ʹ�� BedObject ����
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
    inventory = new Inventory(24);  // 24�񱳰�

    // ��ʼ������ϵͳ
    initializeAnimals();


    // ���ô�������
    setupTouchListener();

    // �����µ�һ�������
    setupNewDayListener();

    return true;
}

void House::initializeAnimals() {
    // ���һЩ��ʼ����
    addAnimal("Golden Chiken", Vec2(300, 200));  // ���Ը�����Ҫ����λ��
    addAnimal("Golden Chiken", Vec2(400, 200));
    addAnimal("White Cow", Vec2(500, 200));
}

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
bool House::checkBedInteraction(const Vec2& position) {
    if (!_bedObject) return false;

    Rect bedRect(_bedObject->x, _bedObject->y, _bedObject->width, _bedObject->height);
    return bedRect.containsPoint(position);
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

bool House::onTouchBegan(Touch* touch, Event* event) {
    Vec2 touchLocation = touch->getLocation();
    Vec2 locationInNode = this->convertToNodeSpace(touchLocation);

    // ����Ƿ����˴�
    if (checkBedInteraction(locationInNode)) {
        goToSleep();
        return true;
    }

    // ԭ�еĶ��ｻ���߼�
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