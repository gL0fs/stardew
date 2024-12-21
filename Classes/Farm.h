#ifndef __farm_h__  // ����Ƿ��Ѿ������� __crop_h__
#define __farm_h__  // ���� __crop_h__
#include "crop.h"
#include "cocos2d.h"
#include "BaseMaplayer.h"

USING_NS_CC;

class Farm : public Node
{
public:
    Farm()
    {
        // ��ʼ��
        schedule([this](float dt) {
            this->update(dt);
            }, 1.0f, "update_key");
    }

    /*void plantCrop(const std::string& name, const std::string& spritefile, Vec2 position)
    {
        Crop* crop = new Crop(name, spritefile);
        crop->setPosition(position);
        this->addChild(crop);
        _crops.push_back(crop);
        crop->plant();  // ��ֲ����
    }*/

    void harvestCrop(int index)
    {
        if (index >= 0 && index < _crops.size())
        {
            _crops[index]->harvest();
        }
    }

    void update(float dt)
    {
        // ������������
        for (auto crop : _crops)
        {
            crop->update(dt);
        }
    }

private:
    std::vector<Crop*> _crops;  // �洢ũ������������
}; 
#endif