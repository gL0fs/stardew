#ifndef __HOUSE_H__
#define __HOUSE_H__

#include "cocos2d.h"
#include "BaseMapLayer.h"
#include "Backpack.h"
#include "TimeManager.h"

USING_NS_CC;

struct Animal {
    Sprite* sprite;
    std::string type;
    bool harvestedToday;
    Vec2 position;
};

class House : public BaseMapLayer {
public:
    static Scene* createScene(const std::string& spawnPointName);
    static House* create(const std::string& spawnPointName);

    virtual bool init() override;
    virtual bool initMap(const std::string& spawnPointName);

    // �������ϵͳ
    void addAnimal(const std::string& type, const Vec2& position);
    void initializeAnimals();
    bool onTouchBegan(Touch* touch, Event* event);
    void harvestAnimal(Animal* animal);

    // �µ�һ������
    void onNewDay(EventCustom* event);

private:
    std::vector<Animal> animals;
    Inventory* inventory;

    void setupTouchListener();
    Animal* findTouchedAnimal(const Vec2& touchPos);
    void setupNewDayListener();
};

#endif // __HOUSE_H__

