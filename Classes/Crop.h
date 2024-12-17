#ifndef __CROP_H__  // 检查是否已经定义了 __CROP_H__
#define __CROP_H__  // 定义 __CROP_H__

#include "cocos2d.h"
#include "BaseMapLayer.h"

USING_NS_CC;

class Crop : public Node
{
public:
    enum class CropState
    {
        PLANTED,  // 作物已种植
        GROWING,  // 作物正在生长
        READY,    // 作物已成熟，可以收获
    };

    Crop(const std::string& name, const std::string& spriteFile)
        : _name(name), _spriteFile(spriteFile), _state(CropState::PLANTED), _growthTime(0)
    {
        _sprite = Sprite::create(spriteFile);
        if (_sprite)
        {
            this->addChild(_sprite);
        }
    }

    void update(float dt)
    {
        if (_state == CropState::GROWING)
        {
            _growthTime += dt;

            // 假设作物成长时间为10秒
            if (_growthTime >= 10)
            {
                _state = CropState::READY;
                CCLOG("%s has grown and is ready to harvest.", _name.c_str());
            }
        }
    }

    void harvest()
    {
        if (_state == CropState::READY)
        {
            CCLOG("%s has been harvested!", _name.c_str());
            _state = CropState::PLANTED;  // 重新开始种植过程
        }
    }

    void plant()
    {
        if (_state == CropState::PLANTED)
        {
            _state = CropState::GROWING;
            CCLOG("%s has been planted and is growing.", _name.c_str());
        }
    }

private:
    std::string _name;
    std::string _spriteFile;
    Sprite* _sprite;
    CropState _state;
    float _growthTime;  // 生长时间
}; 
#endif