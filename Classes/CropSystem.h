
#ifndef __CROP_SYSTEM_H__
#define __CROP_SYSTEM_H__

#include "cocos2d.h"
#include "TimeManager.h"

class Crop : public cocos2d::Sprite {
private:
    enum class GrowthState {
        SEED,    // carrot1
        GROWING, // carrot2
        MATURE   // carrot3
    };
    GrowthState _state = GrowthState::SEED;  // 初始状态是种子
    void updateSprite();  // 更新作物精灵的方法
    int _daysWatered = 0;  // 记录累计浇水天数
    bool _todayWatered = false;  // 记录今天是否浇水过
    float _plantedMinute = 0;  // 记录种植时的游戏分钟
    int _plantedHour = 0;      // 记录种植时的游戏小时
    int _plantedDay = 0;       // 记录种植时的游戏天数

    int _growthDays;
public:
    enum class CropType {
        CARROT,
        SMALL_TREE,
        RED_FLOWER,
        TREE_FLOWER
    };
   

    // 创建作物的方法，接受位置和作物类型作为参数
    static Crop* create(const cocos2d::Vec2& pos, CropType type);

    // 初始化方法，接受位置和作物类型作为参数
    bool Crop::init(const Vec2& pos, CropType type);
    // 作物生长的方法
    void grow();
    bool _isWatered;
    void resetDailyWater() { _todayWatered = false; _isWatered = false; }
    int getDaysWatered() const { return _daysWatered; }
    void water() {
        if (!_todayWatered) {
            _todayWatered = true;
            _isWatered = true;
            _daysWatered++;
        }
    }
    bool isWatered() const { return _isWatered; }
    bool isMature() const { return _state == GrowthState::MATURE; }


    // 获取当前作物的生长状态
    GrowthState getState() const { return _state; }

    // 获取当前作物的类型
    CropType getType() const { return _cropType; }
    CropType _cropType;  // 作物类型
};

class CropSystem : public cocos2d::Node {
public:
    static CropSystem* create();
    virtual bool init() override;

    bool plantCrop(const cocos2d::Vec2& position);
    bool removeCrop(const cocos2d::Vec2& position);
    void selectCropType(Crop::CropType type) { _selectedCropType = type; }
    
    bool waterCrop(const cocos2d::Vec2& position);
    std::string harvestCrop(const cocos2d::Vec2& position);
    // 检查是否可以在某个位置种植作物
    bool canPlantAt(const cocos2d::Vec2& position) const;

   
private:
    std::vector<Crop*> _crops;  // 存储所有作物的容器
   
    static const int TILE_SIZE = 32;

    Crop::CropType _selectedCropType;
    Crop* findCropAt(const cocos2d::Vec2& position);
    std::map<Crop::CropType, std::string> _harvestItems = {
        {Crop::CropType::CARROT, "carrot"},
        {Crop::CropType::SMALL_TREE, "wood"},
        {Crop::CropType::RED_FLOWER, "redflower"},
        {Crop::CropType::TREE_FLOWER, "treeflower"}
    };
    cocos2d::Vec2 getGridPosition(const cocos2d::Vec2& position) const;
    // 检查作物生长状态的方法
    void checkGrowth(float dt);

    // 处理新的一天开始时的事件
    void onNewDay(cocos2d::EventCustom* event);
    static CropSystem* _instance; // 单例实例
 /*   Crop::CropType _selectedCropType = Crop::CropType::CARROT;*/
};

#endif  // __CROP_SYSTEM_H__
