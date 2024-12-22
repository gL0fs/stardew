// CropSystem.h
//#ifndef __CROP_SYSTEM_H__
//#define __CROP_SYSTEM_H__
//
//#include "cocos2d.h"
//#include "TimeManager.h"

//class Crop : public cocos2d::Sprite {
//public:
//
//
//    enum class CropType {
//        CARROT,
//        SMALL_TREE,
//        RED_FLOWER,
//        TREE_FLOWER
//    };
//    static Crop* create(const cocos2d::Vec2& pos, CropType type);
//    virtual bool init(const Vec2& pos,CropType type);
//
//
//    // 生长状态
//    enum class GrowthState {
//        SEED,    // carrot1
//        GROWING, // carrot2
//        MATURE   // carrot3
//    };
//
//    void grow();
//    bool isMature() const { return _state == GrowthState::MATURE; }
//    GrowthState getState() const { return _state; }
//    CropType getType() const { return _cropType; }
//private:
//    GrowthState _state = GrowthState::SEED;
//    void updateSprite();
//    CropType _cropType;
//    float _plantedMinute = 0;  // 记录种植时的游戏分钟
//    int _plantedHour = 0;      // 记录种植时的游戏小时
//    int _plantedDay = 0;       // 记录种植时的游戏天数
//};
//
//class CropSystem : public cocos2d::Node {
//public:
//    static CropSystem* create();
//    virtual bool init() override;
//    std::string selectCropType(CropType type);
//
//    // 移除作物
//    bool removeCrop(const cocos2d::Vec2& position);
//    // 种植作物
//    bool plantCrop(const cocos2d::Vec2& position);
//
//    // 检查位置是否可以种植
//    bool canPlantAt(const cocos2d::Vec2& position) const;
//
//    // 获取网格位置
//    cocos2d::Vec2 getGridPosition(const cocos2d::Vec2& position) const;
//
//private:
//    std::vector<Crop*> _crops;
//    const float TILE_SIZE = 32.0f;
//
//    void checkGrowth(float dt);  // 检查作物生长
//    void onNewDay(cocos2d::EventCustom* event);  // 处理新的一天
//
//    Crop::CropType _selectedCropType = Crop::CropType::CARROT;
//
//
//};
//
//#endif


#ifndef __CROP_SYSTEM_H__
#define __CROP_SYSTEM_H__

#include "cocos2d.h"
#include "TimeManager.h"

class Crop : public cocos2d::Sprite {
public:
    // 作物类型枚举
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

    // 生长状态枚举
    enum class GrowthState {
        SEED,    // carrot1
        GROWING, // carrot2
        MATURE   // carrot3
    };

    // 作物生长的方法
    void grow();

    // 判断作物是否成熟
    bool isMature() const { return _state == GrowthState::MATURE; }

    // 获取当前作物的生长状态
    GrowthState getState() const { return _state; }

    // 获取当前作物的类型
    CropType getType() const { return _cropType; }

private:
    GrowthState _state = GrowthState::SEED;  // 初始状态是种子
    void updateSprite();  // 更新作物精灵的方法
    CropType _cropType;  // 作物类型
    float _plantedMinute = 0;  // 记录种植时的游戏分钟
    int _plantedHour = 0;      // 记录种植时的游戏小时
    int _plantedDay = 0;       // 记录种植时的游戏天数

    int _growthDays;
};

class CropSystem : public cocos2d::Node {
public:
    static CropSystem* create();
    virtual bool init() override;

    bool plantCrop(const cocos2d::Vec2& position);
    bool removeCrop(const cocos2d::Vec2& position);
    void selectCropType(Crop::CropType type) { _selectedCropType = type; }
    
  
    // 检查是否可以在某个位置种植作物
    bool canPlantAt(const cocos2d::Vec2& position) const;

   
private:
    std::vector<Crop*> _crops;  // 存储所有作物的容器
   
    static const int TILE_SIZE = 32;

    Crop::CropType _selectedCropType;

    cocos2d::Vec2 getGridPosition(const cocos2d::Vec2& position) const;
    // 检查作物生长状态的方法
    void checkGrowth(float dt);

    // 处理新的一天开始时的事件
    void onNewDay(cocos2d::EventCustom* event);
    static CropSystem* _instance; // 单例实例
 /*   Crop::CropType _selectedCropType = Crop::CropType::CARROT;*/
};

#endif  // __CROP_SYSTEM_H__
