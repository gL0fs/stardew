// Tree.h

#include "crop.h"
#include "cocos2d.h"
#include "BaseMaplayer.h"

USING_NS_CC;
class Tree : public cocos2d::Sprite {
public:
    enum class TreeStage {
        SEED,       // ���ӽ׶�

        MATURE,     // ����׶�
        HARVESTABLE // ���ջ�׶�
    };

    enum class TreeType {
       /* APPLE,
        CHERRY,
        ORANGE,*/
        MAPLE
    };

    // ������ľʵ���ľ�̬����
    static Tree* create(TreeType type);

    // ��ʼ����ľ
    virtual bool init(TreeType type);

    // ������ľ����״̬
    void updateGrowth(float deltaTime);

    // ��ȡ��ǰ��ľ�׶�
    TreeStage getCurrentStage() { return _currentStage; }

    // ��ȡ��ľ����
    TreeType getTreeType() { return _treeType; }

    // ����Ƿ�����ջ�
    bool isHarvestable() { return _currentStage == TreeStage::HARVESTABLE; }

    // �ջ�fruits
    std::vector<std::string> harvest();

private:
    TreeType _treeType;
    TreeStage _currentStage = TreeStage::SEED;

    // ������ز���
    float _growthTime = 0.0f;
    float _stageGrowthDuration[4] = { 60.0f, 120.0f, 180.0f, 240.0f }; // ÿ���׶ε�����ʱ�䣨�룩

    // ������ͼ
    std::string _stageSpriteFiles[5] = {
        "seed.gif",
        "mature_tree.gif"
        "harvestable_tree.gif"
    };

    // ��ʵ����
    std::vector<std::string> _fruits = {
       /* "apple", "cherry", "orange",*/"Maple" // ������ľ����
    };

    // ������ľ����
    void updateTreeSprite();
};

