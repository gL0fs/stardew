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
//    // ����״̬
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
//    float _plantedMinute = 0;  // ��¼��ֲʱ����Ϸ����
//    int _plantedHour = 0;      // ��¼��ֲʱ����ϷСʱ
//    int _plantedDay = 0;       // ��¼��ֲʱ����Ϸ����
//};
//
//class CropSystem : public cocos2d::Node {
//public:
//    static CropSystem* create();
//    virtual bool init() override;
//    std::string selectCropType(CropType type);
//
//    // �Ƴ�����
//    bool removeCrop(const cocos2d::Vec2& position);
//    // ��ֲ����
//    bool plantCrop(const cocos2d::Vec2& position);
//
//    // ���λ���Ƿ������ֲ
//    bool canPlantAt(const cocos2d::Vec2& position) const;
//
//    // ��ȡ����λ��
//    cocos2d::Vec2 getGridPosition(const cocos2d::Vec2& position) const;
//
//private:
//    std::vector<Crop*> _crops;
//    const float TILE_SIZE = 32.0f;
//
//    void checkGrowth(float dt);  // �����������
//    void onNewDay(cocos2d::EventCustom* event);  // �����µ�һ��
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
    // ��������ö��
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

    // ����״̬ö��
    enum class GrowthState {
        SEED,    // carrot1
        GROWING, // carrot2
        MATURE   // carrot3
    };

    // ���������ķ���
    void grow();

    // �ж������Ƿ����
    bool isMature() const { return _state == GrowthState::MATURE; }

    // ��ȡ��ǰ���������״̬
    GrowthState getState() const { return _state; }

    // ��ȡ��ǰ���������
    CropType getType() const { return _cropType; }

private:
    GrowthState _state = GrowthState::SEED;  // ��ʼ״̬������
    void updateSprite();  // �������ﾫ��ķ���
    CropType _cropType;  // ��������
    float _plantedMinute = 0;  // ��¼��ֲʱ����Ϸ����
    int _plantedHour = 0;      // ��¼��ֲʱ����ϷСʱ
    int _plantedDay = 0;       // ��¼��ֲʱ����Ϸ����

    int _growthDays;
};

class CropSystem : public cocos2d::Node {
public:
    static CropSystem* create();
    virtual bool init() override;

    bool plantCrop(const cocos2d::Vec2& position);
    bool removeCrop(const cocos2d::Vec2& position);
    void selectCropType(Crop::CropType type) { _selectedCropType = type; }
    
  
    // ����Ƿ������ĳ��λ����ֲ����
    bool canPlantAt(const cocos2d::Vec2& position) const;

   
private:
    std::vector<Crop*> _crops;  // �洢�������������
   
    static const int TILE_SIZE = 32;

    Crop::CropType _selectedCropType;

    cocos2d::Vec2 getGridPosition(const cocos2d::Vec2& position) const;
    // �����������״̬�ķ���
    void checkGrowth(float dt);

    // �����µ�һ�쿪ʼʱ���¼�
    void onNewDay(cocos2d::EventCustom* event);
    static CropSystem* _instance; // ����ʵ��
 /*   Crop::CropType _selectedCropType = Crop::CropType::CARROT;*/
};

#endif  // __CROP_SYSTEM_H__
