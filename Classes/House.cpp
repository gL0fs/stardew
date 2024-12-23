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

bool House::onTouchBegan(Touch* touch, Event* event) {
    Vec2 touchLocation = touch->getLocation();

    // ���ұ������Ķ���
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