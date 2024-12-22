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

        // 初始化农田网格
        _gridSize = Size(10, 10); // 10x10的农田
        _tileSize = Size(32, 32); // 每个农田格子32x32像素

        // 创建农田背景（可选）
        createFarmBackground();

        return true;
    }

    void plantCrop(const std::string& name, const std::string& spriteFile, Vec2 position, int daysToMature)
    {
        // 转换鼠标/触摸位置到网格位置
        Vec2 gridPos = positionToGrid(position);

        // 检查该位置是否已有作物
        if (getCropAtGrid(gridPos)) {
            CCLOG("There's already a crop at this position!");
            return;
        }

        // 创建新作物
        auto crop = Crop::create(name, spriteFile, daysToMature);
        if (crop) {
            // 设置作物位置到网格中心
            Vec2 worldPos = gridToPosition(gridPos);
            crop->setPosition(worldPos);
            this->addChild(crop);
            _crops.pushBack(crop);

            // 记录作物在网格中的位置
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

            // 可选：收获后移除作物
            _crops.eraseObject(crop);
            _cropGrid.erase(std::make_pair(static_cast<int>(gridPos.x),
                static_cast<int>(gridPos.y)));
            crop->removeFromParent();
        }
    }

    // 获取指定网格位置的作物
    Crop* getCropAtGrid(const Vec2& gridPos) {
        auto it = _cropGrid.find(std::make_pair(static_cast<int>(gridPos.x),
            static_cast<int>(gridPos.y)));
        return it != _cropGrid.end() ? it->second : nullptr;
    }

    // 世界坐标转换为网格坐标
    Vec2 positionToGrid(const Vec2& position) {
        return Vec2(floor(position.x / _tileSize.width),
            floor(position.y / _tileSize.height));
    }

    // 网格坐标转换为世界坐标（网格中心点）
    Vec2 gridToPosition(const Vec2& gridPos) {
        return Vec2((gridPos.x + 0.5f) * _tileSize.width,
            (gridPos.y + 0.5f) * _tileSize.height);
    }

private:
    void createFarmBackground() {
        // 创建一个简单的网格背景
        auto draw = DrawNode::create();
        this->addChild(draw);

        // 绘制横向网格线
        for (int i = 0; i <= _gridSize.height; i++) {
            Vec2 start = Vec2(0, i * _tileSize.height);
            Vec2 end = Vec2(_gridSize.width * _tileSize.width, i * _tileSize.height);
            draw->drawLine(start, end, Color4F(0.5f, 0.5f, 0.5f, 0.3f));
        }

        // 绘制纵向网格线
        for (int i = 0; i <= _gridSize.width; i++) {
            Vec2 start = Vec2(i * _tileSize.width, 0);
            Vec2 end = Vec2(i * _tileSize.width, _gridSize.height * _tileSize.height);
            draw->drawLine(start, end, Color4F(0.5f, 0.5f, 0.5f, 0.3f));
        }
    }

    Vector<Crop*> _crops;  // 存储农场的所有作物
    std::map<std::pair<int, int>, Crop*> _cropGrid;  // 网格位置到作物的映射
    Size _gridSize;  // 农田大小（格子数）
    Size _tileSize;  // 每个格子的大小（像素）
};

#endif