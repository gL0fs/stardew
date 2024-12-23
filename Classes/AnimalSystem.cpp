// AnimalSystem.cpp
#include "AnimalSystem.h"
#include "Backpack.h"  // ��Ҫ��������ͷ�ļ�

USING_NS_CC;

Animal* Animal::create(const std::string& type, const Vec2& pos) {
    Animal* animal = new (std::nothrow) Animal();
    if (animal && animal->init(type, pos)) {
        animal->autorelease();
        return animal;
    }
    CC_SAFE_DELETE(animal);
    return nullptr;
}

bool Animal::init(const std::string& type, const Vec2& pos) {
    std::string spriteName = type + ".png";  // ������chicken.png��cow.png
    if (!Sprite::initWithFile(spriteName)) {
        return false;
    }

    _type = type;
    _collectedToday = false;
    _lastCollectDay = 0;
    _currentDay = 1;

    setPosition(pos);
    return true;
}

void Animal::collect() {
    _collectedToday = true;
    _lastCollectDay = _currentDay;
}

void Animal::onNewDay(int day) {
    _currentDay = day;
    _collectedToday = false;
}

// AnimalSystem implementation
AnimalSystem* AnimalSystem::create() {
    AnimalSystem* system = new (std::nothrow) AnimalSystem();
    if (system && system->init()) {
        system->autorelease();
        return system;
    }
    CC_SAFE_DELETE(system);
    return nullptr;
}

bool AnimalSystem::init() {
    if (!Node::init()) {
        return false;
    }

    // ע���µ�һ���¼�����
    auto listener = EventListenerCustom::create("new_day",
        CC_CALLBACK_1(AnimalSystem::onNewDay, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool AnimalSystem::addAnimal(const std::string& type, const Vec2& pos) {
    auto animal = Animal::create(type, pos);
    if (animal) {
        this->addChild(animal);
        _animals.push_back(animal);
        return true;
    }
    return false;
}

bool AnimalSystem::tryCollectProduct(const Vec2& touchPos) {
    for (auto animal : _animals) {
        if (animal->getBoundingBox().containsPoint(touchPos) && animal->canCollect()) {
            std::string animalType = animal->_type;
            std::string productType = _productTypes[animalType];

            // ��Ӳ�Ʒ������
            // ���豳����ȫ�ֿɷ��ʵģ���ͨ��ĳ�ַ�ʽ��ȡ
            // playerInventory.addItemToInventory(productType, 1);

            animal->collect();
            return true;
        }
    }
    return false;
}

void AnimalSystem::onNewDay(EventCustom* event) {
    int* currentDay = static_cast<int*>(event->getUserData());
    for (auto animal : _animals) {
        animal->onNewDay(*currentDay);
    }
}