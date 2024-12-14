#include "Map1.h"
#include "cocos2d.h"
#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support
#include "Tree.h"

Tree* Tree::create(TreeType type) {
    Tree* tree = new (std::nothrow) Tree();
    if (tree && tree->init(type)) {
        tree->autorelease();
        return tree;
    }
    CC_SAFE_DELETE(tree);
    return nullptr;
}

void plantTree(cocos2d::Vec2 position, cocos2d::TMXTiledMap* map, cocos2d::Vector<cocos2d::Sprite*>& treesVector) {
    // 创建树木精灵
    auto treeSprite = cocos2d::Sprite::create("tree1_spring.png");

    // 根据地图瓦片大小调整树的大小
    auto tileSize = map->getTileSize();
    float scaleX = tileSize.width / treeSprite->getContentSize().width;
    float scaleY = tileSize.height / treeSprite->getContentSize().height;
    treeSprite->setScale(scaleX, scaleY);

    // 设置树木位置（居中于瓦片）
    treeSprite->setPosition(position);

    // 添加到地图
    map->addChild(treeSprite, 1);  // 确保树在玩家上层

    // 保存到树木vector
    treesVector.pushBack(treeSprite);

    // 可以添加种树音效
    // CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("plant.wav");
}
bool Tree::init(TreeType type) {
    if (!Sprite::initWithFile(_stageSpriteFiles[0])) {
        return false;
    }

    _treeType = type;
    _currentStage = TreeStage::SEED;

    // 根据树木类型设置初始参数
    switch (type) {
    //case TreeType::APPLE:
    //    _fruits = { "apple" };
    //    break;
    //case TreeType::CHERRY:
    //    _fruits = { "cherry" };
    //    break;
    //case TreeType::ORANGE:
    //    _fruits = { "orange" };
    //    break;
    case TreeType::MAPLE:
        _fruits = { "maple_seed" };
        break;
    }

    return true;
}

void Tree::updateGrowth(float deltaTime) {
    _growthTime += deltaTime;

    // 根据生长时间推进阶段
    for (int i = 0; i < 4; ++i) {
        if (_growthTime >= _stageGrowthDuration[i] &&
            _currentStage == static_cast<TreeStage>(i)) {
            _currentStage = static_cast<TreeStage>(i + 1);
            updateTreeSprite();
        }
    }
}

void Tree::updateTreeSprite() {
    // 更新树木贴图到当前阶段
    this->setTexture(_stageSpriteFiles[static_cast<int>(_currentStage)]);

    // 可以根据阶段调整精灵大小
    float scale = 1.0f + (static_cast<int>(_currentStage) * 0.2f);
    this->setScale(scale);
}

std::vector<std::string> Tree::harvest() {
    if (_currentStage != TreeStage::HARVESTABLE) {
        return {}; // 不可收获
    }

    // 随机生成果实数量
    int fruitCount = cocos2d::RandomHelper::random_int(1, 5);
    std::vector<std::string> harvestedFruits;

    for (int i = 0; i < fruitCount; ++i) {
        harvestedFruits.push_back(_fruits[0]);
    }

    // 重置为成熟阶段，等待下一个收获周期
    _currentStage = TreeStage::MATURE;
    updateTreeSprite();

    return harvestedFruits;
}


