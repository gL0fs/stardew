// AnimalSystem.h
#ifndef __ANIMAL_SYSTEM_H__
#define __ANIMAL_SYSTEM_H__

#include "cocos2d.h"
#include <map>
#include <string>

class Animal : public cocos2d::Sprite {
public:
    static Animal* create(const std::string& type, const cocos2d::Vec2& pos);
    bool init(const std::string& type, const cocos2d::Vec2& pos);

    bool canCollect() const { return !_collectedToday && _lastCollectDay != _currentDay; }
    void collect();
    void onNewDay(int day);
    std::string _type;
private:

    bool _collectedToday;
    int _lastCollectDay;
    int _currentDay;
};

class AnimalSystem : public cocos2d::Node {
public:
    static AnimalSystem* create();
    virtual bool init() override;

    bool addAnimal(const std::string& type, const cocos2d::Vec2& pos);
    bool tryCollectProduct(const cocos2d::Vec2& touchPos);
    void onNewDay(cocos2d::EventCustom* event);

private:
    std::vector<Animal*> _animals;
    std::map<std::string, std::string> _productTypes = {
        {"chicken", "egg"},
        {"cow", "milk"}
    };
};

#endif
