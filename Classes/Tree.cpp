
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
    // ������ľ����
    auto treeSprite = cocos2d::Sprite::create("tree1_spring.png");

    // ���ݵ�ͼ��Ƭ��С�������Ĵ�С
    auto tileSize = map->getTileSize();
    float scaleX = tileSize.width / treeSprite->getContentSize().width;
    float scaleY = tileSize.height / treeSprite->getContentSize().height;
    treeSprite->setScale(scaleX, scaleY);

    // ������ľλ�ã���������Ƭ��
    treeSprite->setPosition(position);

    // ��ӵ���ͼ
    map->addChild(treeSprite, 1);  // ȷ����������ϲ�

    // ���浽��ľvector
    treesVector.pushBack(treeSprite);

    // �������������Ч
    // CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("plant.wav");
}
bool Tree::init(TreeType type) {
    if (!Sprite::initWithFile(_stageSpriteFiles[0])) {
        return false;
    }

    _treeType = type;
    _currentStage = TreeStage::SEED;

    // ������ľ�������ó�ʼ����
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

    // ��������ʱ���ƽ��׶�
    for (int i = 0; i < 4; ++i) {
        if (_growthTime >= _stageGrowthDuration[i] &&
            _currentStage == static_cast<TreeStage>(i)) {
            _currentStage = static_cast<TreeStage>(i + 1);
            updateTreeSprite();
        }
    }
}

void Tree::updateTreeSprite() {
    // ������ľ��ͼ����ǰ�׶�
    this->setTexture(_stageSpriteFiles[static_cast<int>(_currentStage)]);

    // ���Ը��ݽ׶ε��������С
    float scale = 1.0f + (static_cast<int>(_currentStage) * 0.2f);
    this->setScale(scale);
}

std::vector<std::string> Tree::harvest() {
    if (_currentStage != TreeStage::HARVESTABLE) {
        return {}; // �����ջ�
    }

    // ������ɹ�ʵ����
    int fruitCount = cocos2d::RandomHelper::random_int(1, 5);
    std::vector<std::string> harvestedFruits;

    for (int i = 0; i < fruitCount; ++i) {
        harvestedFruits.push_back(_fruits[0]);
    }

    // ����Ϊ����׶Σ��ȴ���һ���ջ�����
    _currentStage = TreeStage::MATURE;
    updateTreeSprite();

    return harvestedFruits;
}


