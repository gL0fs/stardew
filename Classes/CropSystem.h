
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
    GrowthState _state = GrowthState::SEED;  // ��ʼ״̬������
    void updateSprite();  // �������ﾫ��ķ���
    int _daysWatered = 0;  // ��¼�ۼƽ�ˮ����
    bool _todayWatered = false;  // ��¼�����Ƿ�ˮ��
    float _plantedMinute = 0;  // ��¼��ֲʱ����Ϸ����
    int _plantedHour = 0;      // ��¼��ֲʱ����ϷСʱ
    int _plantedDay = 0;       // ��¼��ֲʱ����Ϸ����

    int _growthDays;
public:
    enum class CropType {
        CARROT,
        SMALL_TREE,
        RED_FLOWER,
        TREE_FLOWER
    };
   

    // ��������ķ���������λ�ú�����������Ϊ����
    static Crop* create(const cocos2d::Vec2& pos, CropType type);

    // ��ʼ������������λ�ú�����������Ϊ����
    bool Crop::init(const Vec2& pos, CropType type);
    // ���������ķ���
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


    // ��ȡ��ǰ���������״̬
    GrowthState getState() const { return _state; }

    // ��ȡ��ǰ���������
    CropType getType() const { return _cropType; }
    CropType _cropType;  // ��������
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
    // ����Ƿ������ĳ��λ����ֲ����
    bool canPlantAt(const cocos2d::Vec2& position) const;

   
private:
    std::vector<Crop*> _crops;  // �洢�������������
   
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
    // �����������״̬�ķ���
    void checkGrowth(float dt);

    // �����µ�һ�쿪ʼʱ���¼�
    void onNewDay(cocos2d::EventCustom* event);
    static CropSystem* _instance; // ����ʵ��
 /*   Crop::CropType _selectedCropType = Crop::CropType::CARROT;*/
};

#endif  // __CROP_SYSTEM_H__
