#ifndef __CROP_H__  // ����Ƿ��Ѿ������� __CROP_H__
#define __CROP_H__  // ���� __CROP_H__

#include "cocos2d.h"
#include "BaseMapLayer.h"

USING_NS_CC;

class Crop : public Node
{
public:
    enum class CropState
    {
        PLANTED,  // ��������ֲ
        GROWING,  // ������������
        READY,    // �����ѳ��죬�����ջ�
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

            // ��������ɳ�ʱ��Ϊ10��
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
            _state = CropState::PLANTED;  // ���¿�ʼ��ֲ����
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
    float _growthTime;  // ����ʱ��
}; 
#endif