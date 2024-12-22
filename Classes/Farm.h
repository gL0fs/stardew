#ifndef __FARM_H__
#define __FARM_H__

#include "cocos2d.h"
#include "Crop.h"

USING_NS_CC;

class Farm : public Node
{
public:
    CREATE_FUNC(Farm);

    virtual bool init() override {
        if (!Node::init()) {
            return false;
        }

        // ��ʼ��ũ������
        _gridSize = Size(10, 10); // 10x10��ũ��
        _tileSize = Size(32, 32); // ÿ��ũ�����32x32����

        // ����ũ�ﱳ������ѡ��
        createFarmBackground();

        return true;
    }

    void plantCrop(const std::string& name, const std::string& spriteFile, Vec2 position, int daysToMature)
    {
        // ת�����/����λ�õ�����λ��
        Vec2 gridPos = positionToGrid(position);


        // ����λ���Ƿ���������
        if (getCropAtGrid(gridPos)) {
            CCLOG("There's already a crop at this position!");
            return;
        }

        // ����������
        auto crop = Crop::create(name, spriteFile, daysToMature);
        if (crop) {
            // ��������λ�õ���������
            Vec2 worldPos = gridToPosition(gridPos);
            crop->setPosition(worldPos);
            this->addChild(crop);
            _crops.pushBack(crop);

            // ��¼�����������е�λ��
            _cropGrid[std::make_pair(static_cast<int>(gridPos.x),
                static_cast<int>(gridPos.y))] = crop;

            crop->plant();
            CCLOG("Planted %s at grid position (%.0f, %.0f)",
                name.c_str(), gridPos.x, gridPos.y);
        }
    }

    void harvestCrop(Vec2 position)
    {
        Vec2 gridPos = positionToGrid(position);
        auto crop = getCropAtGrid(gridPos);

        if (crop && crop->getState() == Crop::CropState::READY) {
            crop->harvest();

            // ��ѡ���ջ���Ƴ�����
            _crops.eraseObject(crop);
            _cropGrid.erase(std::make_pair(static_cast<int>(gridPos.x),
                static_cast<int>(gridPos.y)));
            crop->removeFromParent();
        }
    }

    // ��ȡָ������λ�õ�����
    Crop* getCropAtGrid(const Vec2& gridPos) {
        auto it = _cropGrid.find(std::make_pair(static_cast<int>(gridPos.x),
            static_cast<int>(gridPos.y)));
        return it != _cropGrid.end() ? it->second : nullptr;
    }

    // ��������ת��Ϊ��������
    Vec2 positionToGrid(const Vec2& position) {
        return Vec2(floor(position.x / _tileSize.width),
            floor(position.y / _tileSize.height));
    }

    // ��������ת��Ϊ�������꣨�������ĵ㣩
    Vec2 gridToPosition(const Vec2& gridPos) {
        return Vec2((gridPos.x + 0.5f) * _tileSize.width,
            (gridPos.y + 0.5f) * _tileSize.height);
    }

private:
    void createFarmBackground() {
        // ����һ���򵥵����񱳾�
        auto draw = DrawNode::create();
        this->addChild(draw);

        // ���ƺ���������
        for (int i = 0; i <= _gridSize.height; i++) {
            Vec2 start = Vec2(0, i * _tileSize.height);
            Vec2 end = Vec2(_gridSize.width * _tileSize.width, i * _tileSize.height);
            draw->drawLine(start, end, Color4F(0.5f, 0.5f, 0.5f, 0.3f));
        }

        // ��������������
        for (int i = 0; i <= _gridSize.width; i++) {
            Vec2 start = Vec2(i * _tileSize.width, 0);
            Vec2 end = Vec2(i * _tileSize.width, _gridSize.height * _tileSize.height);
            draw->drawLine(start, end, Color4F(0.5f, 0.5f, 0.5f, 0.3f));
        }
    }

    Vector<Crop*> _crops;  // �洢ũ������������
    std::map<std::pair<int, int>, Crop*> _cropGrid;  // ����λ�õ������ӳ��
    Size _gridSize;  // ũ���С����������
    Size _tileSize;  // ÿ�����ӵĴ�С�����أ�
};

#endif