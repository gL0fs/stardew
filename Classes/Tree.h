// Tree.h

#include "crop.h"
#include "cocos2d.h"
#include "BaseMaplayer.h"

USING_NS_CC;
class Tree : public cocos2d::Sprite {
public:
    enum class TreeStage {
        SEED,       // 种子阶段

        MATURE,     // 成熟阶段
        HARVESTABLE // 可收获阶段
    };

    enum class TreeType {
       /* APPLE,
        CHERRY,
        ORANGE,*/
        MAPLE
    };

    // 创建树木实例的静态方法
    static Tree* create(TreeType type);

    // 初始化树木
    virtual bool init(TreeType type);

    // 更新树木生长状态
    void updateGrowth(float deltaTime);

    // 获取当前树木阶段
    TreeStage getCurrentStage() { return _currentStage; }

    // 获取树木类型
    TreeType getTreeType() { return _treeType; }

    // 检查是否可以收获
    bool isHarvestable() { return _currentStage == TreeStage::HARVESTABLE; }

    // 收获fruits
    std::vector<std::string> harvest();

private:
    TreeType _treeType;
    TreeStage _currentStage = TreeStage::SEED;

    // 生长相关参数
    float _growthTime = 0.0f;
    float _stageGrowthDuration[4] = { 60.0f, 120.0f, 180.0f, 240.0f }; // 每个阶段的生长时间（秒）

    // 生长贴图
    std::string _stageSpriteFiles[5] = {
        "seed.gif",
        "mature_tree.gif"
        "harvestable_tree.gif"
    };

    // 果实类型
    std::vector<std::string> _fruits = {
       /* "apple", "cherry", "orange",*/"Maple" // 根据树木类型
    };

    // 更新树木精灵
    void updateTreeSprite();
};

