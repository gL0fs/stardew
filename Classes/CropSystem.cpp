#include "CropSystem.h"

USING_NS_CC;

CropSystem* CropSystem::_instance = nullptr;
// Crop ʵ��
Crop* Crop::create(const Vec2& pos, CropType type) {
    Crop* crop = new (std::nothrow) Crop();
    if (crop && crop->init(pos, type)) {
        crop->autorelease();
        return crop;
    }
    CC_SAFE_DELETE(crop);
    return nullptr;
}
bool Crop::init(const Vec2& pos, CropType type) {
    _cropType = type;
    _daysWatered = 0;
    _todayWatered = false;
    _isWatered = false;
    _state = GrowthState::SEED;

 // ������������������������
    switch (type) {
    case CropType::CARROT:
        _growthDays = 3;
        break;
    case CropType::SMALL_TREE:
    case CropType::RED_FLOWER:
        _growthDays = 4;
        break;
    }

    std::string spriteName;
    switch (type) {
    case CropType::CARROT:
        spriteName = "carrot1.png";
        break;
    case CropType::SMALL_TREE:
        spriteName = "smalltree1.png";
        break;
    case CropType::RED_FLOWER:
        spriteName = "redflower1.png";
        break;
  
    }

    if (!Sprite::initWithFile(spriteName)) {
        return false;
    }

    setPosition(pos);
    return true;
}
void Crop::grow() {
    if (!_isWatered) return;  // �������û��ˮ��������

    switch (_state) {
    case GrowthState::SEED:
        if (_daysWatered >= 1) {
            _state = GrowthState::GROWING;
            updateSprite();
        }
        break;
    case GrowthState::GROWING:
        if (_daysWatered >= _growthDays - 1) {
            _state = GrowthState::MATURE;
            updateSprite();
        }
        break;
    case GrowthState::MATURE:
        // ���ֳ���״ֱ̬���ջ�
        break;
    }
}

bool CropSystem::waterCrop(const Vec2& position) {
    auto crop = findCropAt(position);
    if (crop && !crop->isWatered()) {
        crop->water();
        crop->grow();  // ��������Ƿ��������
        return true;
    }
    return false;
}
std::string CropSystem::harvestCrop(const Vec2& position) {
    auto crop = findCropAt(position);
    if (crop && crop->isMature() && crop->getDaysWatered() >= crop->getGrowthDays()) {
        std::string harvestItem = _harvestItems[crop->_cropType];
        removeCrop(position);
        //����
        return harvestItem;
    }
    return "";
}

Crop* CropSystem::findCropAt(const Vec2& position) {
    Vec2 gridPos = getGridPosition(position);
    for (auto crop : _crops) {
        if (crop->getPosition() == gridPos) {
            return crop;
        }
    }
    return nullptr;
} 
void Crop::updateSprite() {
    std::string filename;
    std::string number;

    switch (_state) {
    case GrowthState::SEED: number = "1"; break;
    case GrowthState::GROWING: number = "2"; break;
    case GrowthState::MATURE: number = "3"; break;
    }

    switch (_cropType) {
    case CropType::CARROT:
        filename = "carrot" + number + ".png";
        break;
    case CropType::SMALL_TREE:
        filename = "smalltree" + number + ".png";
        break;
    case CropType::RED_FLOWER:
        filename = "redflower" + number + ".png";
        break;
  
    }

    setTexture(filename);
}
// CropSystem ʵ��
CropSystem* CropSystem::create() {
    CropSystem* system = new (std::nothrow) CropSystem();
    if (system && system->init()) {
        system->autorelease();
        return system;
    }
    CC_SAFE_DELETE(system);
    return nullptr;
}

bool CropSystem::init() {
    if (!Node::init()) {
        return false;
    }
    _selectedCropType = Crop::CropType::CARROT;  // Ĭ��ѡ����ܲ�
    // ע��ÿ���Ӹ���
    this->schedule(CC_SCHEDULE_SELECTOR(CropSystem::checkGrowth), 1.0f);

    // ע���µ�һ���¼�����
    auto listener = EventListenerCustom::create("new_day",
        CC_CALLBACK_1(CropSystem::onNewDay, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool CropSystem::plantCrop(const Vec2& position) {
    Vec2 gridPos = getGridPosition(position);

    if (!canPlantAt(gridPos)) {
        return false;
    }

    auto crop = Crop::create(gridPos, _selectedCropType);
    if (crop) {
        this->addChild(crop);
        _crops.push_back(crop);
        return true;
    }
    return false;
}
bool CropSystem::removeCrop(const Vec2& position) {
    Vec2 gridPos = getGridPosition(position);

    for (auto it = _crops.begin(); it != _crops.end(); ++it) {
        if ((*it)->getPosition() == gridPos) {
            (*it)->removeFromParent();
            _crops.erase(it);
            return true;
        }
    }
    return false;
}

Vec2 CropSystem::getGridPosition(const Vec2& position) const {
    int gridX = static_cast<int>(position.x / TILE_SIZE);
    int gridY = static_cast<int>(position.y / TILE_SIZE);
    return Vec2(gridX * TILE_SIZE + TILE_SIZE / 2, gridY * TILE_SIZE + TILE_SIZE / 2);
}

bool CropSystem::canPlantAt(const Vec2& position) const {
    Vec2 gridPos = getGridPosition(position);

    // ����Ƿ��������������λ��
    for (const auto& crop : _crops) {
        if (crop->getPosition() == gridPos) {
            return false;
        }
    }

    return true;
}

void CropSystem::checkGrowth(float dt) {
    auto timeManager = TimeManager::getInstance();

    for (auto crop : _crops) {
        // ��������Ը���ʱ����������������
        // ÿ���Ӽ��һ��
        if (!crop->isMature()) {
            crop->grow();
        }
    }
}

void CropSystem::onNewDay(EventCustom* event) {
    CCLOG("�µ�һ�쿪ʼ�ˣ������������״̬");
   
        auto weatherSystem = WeatherSystem::getInstance();
        bool isRaining = weatherSystem->getCurrentWeather() == WeatherSystem::Weather::RAINY;

        for (auto crop : _crops) {
            crop->resetDailyWater();  // ����ÿ�ս�ˮ״̬
            if (isRaining) {
                crop->water();  // ������꣬�Զ���ˮ
            }
            crop->grow();  // ����Ƿ��������
        }
}