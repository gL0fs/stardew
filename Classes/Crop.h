#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"
#include "TimeManager.h"

USING_NS_CC;

class Crop : public Node
{
public:
    enum class CropState
    {
        PLANTED,
        GROWING,
        READY,
    };

    static Crop* create(const std::string& name, const std::string& spriteFile, int daysToMature) {
        auto crop = new Crop(name, spriteFile, daysToMature);
        if (crop && crop->init()) {
            crop->autorelease();
            return crop;
        }
        CC_SAFE_DELETE(crop);
        return nullptr;
    }

    bool init() {
        if (!Node::init()) {
            return false;
        }

        _sprite = Sprite::create(_spriteFile);
        if (_sprite) {
            this->addChild(_sprite);
        }

        // 监听新的一天事件
        auto listener = EventListenerCustom::create("new_day", [this](EventCustom* event) {
            this->onNewDay();
            });
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        return true;
    }

    void onNewDay() {
        if (_state == CropState::GROWING) {
            _currentGrowthDay++;
            CCLOG("%s: Growth day %d of %d", _name.c_str(), _currentGrowthDay, _daysToMature);

            if (_currentGrowthDay >= _daysToMature) {
                _state = CropState::READY;
                CCLOG("%s has grown and is ready to harvest!", _name.c_str());
                // 这里可以更新作物的显示图片
            }
        }
    }

    void harvest() {
        if (_state == CropState::READY) {
            CCLOG("%s has been harvested!", _name.c_str());
            _state = CropState::PLANTED;
            _currentGrowthDay = 0;
            // 这里可以更新作物的显示图片为初始状态
        }
    }

    void plant() {
        if (_state == CropState::PLANTED) {
            _state = CropState::GROWING;
            _currentGrowthDay = 0;
            CCLOG("%s has been planted and is growing.", _name.c_str());
        }
    }

    CropState getState() const { return _state; }
    int getCurrentGrowthDay() const { return _currentGrowthDay; }
    int getDaysToMature() const { return _daysToMature; }

private:
    Crop(const std::string& name, const std::string& spriteFile, int daysToMature)
        : _name(name)
        , _spriteFile(spriteFile)
        , _daysToMature(daysToMature)
        , _currentGrowthDay(0)
        , _state(CropState::PLANTED)
    {}

    std::string _name;
    std::string _spriteFile;
    Sprite* _sprite;
    CropState _state;
    int _daysToMature;
    int _currentGrowthDay;
};

#endif