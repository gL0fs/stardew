#include "BaseMapLayer.h"
#include "BaseMapLayer.h"
USING_NS_CC;

BaseMapLayer::BaseMapLayer() : _map(nullptr), _playerInstance(nullptr) {
}

BaseMapLayer* BaseMapLayer::create(const std::string& tmxFile)
{
    BaseMapLayer* layer = new (std::nothrow) BaseMapLayer();
    if (layer && layer->initMap(tmxFile))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool BaseMapLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    CCLOG("BaseMapLayer::init() is called!");
    // ���ü��̼���
    initMouseEvent();
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(BaseMapLayer::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(BaseMapLayer::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // ���ö�ʱ�����������λ��
    this->scheduleUpdate();

    return true;
}


bool BaseMapLayer::initMap(const std::string& tmxFile)
{
    if (!init())
    {
        return false;
    }
    loadMap(tmxFile);

    return true;
}

void BaseMapLayer::loadMap(const std::string& tmxFile)
{
    _map = TMXTiledMap::create(tmxFile);
    Size mapSize = _map->getContentSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ����ͼ�Ŵ��ı�
    _map->setScale(1.0f);
    
    // �����ͼ����λ�ã�ȷ����ͼ������ʾ
    float scaledWidth = mapSize.width * _map->getScale();
    float scaledHeight = mapSize.height * _map->getScale();
    float x = origin.x + (visibleSize.width - scaledWidth) / 2;
    float y = origin.y + (visibleSize.height - scaledHeight) / 2;
    _map->setPosition(x, y);

    // ��ӵ�ͼ����
    this->addChild(_map, -1);

    // ��ʼ���ӽ�����Ϊ���λ��
    if (_playerInstance) {
        setViewPointCenter(_playerInstance->getPosition());
    }
}


void BaseMapLayer::initializePlayer() {

    // ��ȡ��ҵ���
    _playerInstance = Player::getInstance();
    // ��ʼ����Ҿ���
    if (!_playerInstance->initPlayer("Player.png")) {
        return;
    }

    // ��ȡ��Ƭ��ͼ����Ƭ�ߴ�
    auto tileSize = _map->getTileSize();

    // ��ȡ��Ҿ����ԭʼ�ߴ�
    auto playerContentSize = _playerInstance->getContentSize();

    // �������ű���
    // ��ҿ������Ϊ��ͼ���ӿ��
    float scaleWidth = tileSize.width / playerContentSize.width;
    // ��Ҹ߶�����Ϊ������ͼ���Ӹ߶�
    float scaleHeight = (2 * tileSize.height) / playerContentSize.height;

    // ������Ҿ�������ű���
    _playerInstance->setScale(scaleWidth, scaleHeight);

    // �������λ��
    setPlayerPosition("Objects", "SpawnPoint");

    // �����Ҿ��鵽��ͼ��
    this->addChild(_playerInstance);
}

void BaseMapLayer::setPlayerPosition(const std::string& objectGroupName, const std::string& spawnPointName) {
    if (!_map || !_playerInstance) return;

    // �ӵ�ͼ�������ȡ������
    auto objectGroup = _map->getObjectGroup(objectGroupName);
    if (!objectGroup) return;

    auto spawnPoint = objectGroup->getObject(spawnPointName);
    if (spawnPoint.empty()) return;

    // �������λ��
    float x = spawnPoint["x"].asFloat();
    float y = spawnPoint["y"].asFloat();

    _playerInstance->setPosition(cocos2d::Vec2(x, y));
    setViewPointCenter(_playerInstance->getPosition());
}

//bool BaseMapLayer::isCollisionAtNextPosition(const cocos2d::Vec2& nextPosition) {
//    // ��ȡ�ϰ����
//    auto obstacles = _map->getLayer("BackGround"); // �����ϰ������Ϊ"Obstacles"
//
//
//    if (!obstacles) {
//        // ���û���ϰ���㣬�򲻽�����ײ���
//        return false;
//    }
//
//    // ��ȡ��Ƭ��С�͵�ͼ��С
//    auto tileSize = this->_map->getTileSize();
//    auto mapSize = this->_map->getMapSize();
//
//    // ����һ��λ��ת��Ϊ��Ƭ����
//    int x = nextPosition.x / tileSize.width;
//    int y = (mapSize.height * tileSize.height - nextPosition.y) / tileSize.height;
//    auto tileCoord = cocos2d::Vec2(x, y);
//
//    // ��ȡ����Ƭ�����GID
//    int GID = obstacles->getTileGIDAt(tileCoord);
//
//    // ���GIDΪ0����ʾ��λ��û����Ƭ���������ϰ���
//    if (GID == 0) {
//        return false;
//    }
//
//    // ��ȡ��Ƭ������
//    cocos2d::Value properties = _map->getPropertiesForGID(GID);
//    if (properties.getType() == cocos2d::Value::Type::MAP) {
//        cocos2d::ValueMap propMap = properties.asValueMap();
//        // ����Ƿ���"collidable"���Բ���ֵΪtrue
//        bool collidable = propMap.find("collidable") != propMap.end() && propMap.at("collidable").asBool();
//        return collidable;
//    }
//
//    // Ĭ�ϲ�������ײ
//    return false;
//}
//

void BaseMapLayer::handlePlayerMovement(const cocos2d::Vec2& direction) {
    if (!_playerInstance) return;

    float moveSpeed = 5.0f;  // �ƶ��ٶ�
    cocos2d::Vec2 nextPosition = _playerInstance->getPosition() + direction * moveSpeed;

    // �����ײ��⣨�����Ҫ��
    // if (!isCollisionAtNextPosition(nextPosition)) {
    _playerInstance->setPosition(nextPosition);
    this->setViewPointCenter(nextPosition);
    // }
}

void BaseMapLayer::update(float delta) {
    // ��ӵ�����־
    CCLOG("Move Direction: x=%f, y=%f", _moveDirection.x, _moveDirection.y);

    if (_playerInstance && !_moveDirection.equals(Vec2::ZERO)) {
        handlePlayerMovement(_moveDirection);
    }
}
void BaseMapLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (!_playerInstance) return;
    CCLOG("Key Pressed: %d", static_cast<int>(keyCode));

    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_W:
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        _moveDirection.y = 1;  // �����ƶ�
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_S:
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        _moveDirection.y = -1;  // �����ƶ�
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _moveDirection.x = -1;  // �����ƶ�
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _moveDirection.x = 1;  // �����ƶ�
        break;
    }
    //��һ���ƶ�����
    _moveDirection.normalize();
}

void BaseMapLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (!_playerInstance) return;
    CCLOG("Key Pressed: %d", static_cast<int>(keyCode));

    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_W:
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        _moveDirection.y = 0;  // ֹͣ�����ƶ�
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_S:
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        _moveDirection.y = 0;  // ֹͣ�����ƶ�
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _moveDirection.x = 0;  // ֹͣ�����ƶ�
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _moveDirection.x = 0;  // ֹͣ�����ƶ�
        break;
    }
    //��һ���ƶ�����
    _moveDirection.normalize();
}
void BaseMapLayer::setViewPointCenter(Point position) {
    auto winSize = Director::getInstance()->getWinSize();
    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);

    x = MIN(x, (_map->getMapSize().width * this->_map->getTileSize().width) - winSize.height / 2);
    y = MIN(y, (_map->getMapSize().height * this->_map->getTileSize().width) - winSize.height / 2);
    auto actualPosition = Point(x, y);

    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
    auto viewPoint = centerOfView - actualPosition;
    this->setPosition(viewPoint);
}

void BaseMapLayer::initMouseEvent() {
    // ��������¼�������
    _mouseListener = cocos2d::EventListenerMouse::create();

    // ����������¼�
    _mouseListener->onMouseDown = [this](cocos2d::Event* event) {
        auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);

        // ��ȡ�����OpenGL����ϵ�е�λ��
        cocos2d::Vec2 mouseLocation = mouseEvent->getLocationInView();

        // ת��Ϊ��������
        cocos2d::Vec2 worldLocation = this->convertToNodeSpace(mouseLocation);

        // ����Ƿ��������
        if (canPlantTreeAtPosition(worldLocation)) {
            plantTree(worldLocation);
        }
        };

    // ����¼�������
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}
void BaseMapLayer::plantTree(cocos2d::Vec2 position) {
    // ������ľ����
    auto treeSprite = cocos2d::Sprite::create("tree1_spring.png");
    // ���ݵ�ͼ��Ƭ��С�������Ĵ�С
    auto tileSize = _map->getTileSize();
    float scaleX = tileSize.width / treeSprite->getContentSize().width;
    float scaleY = tileSize.height / treeSprite->getContentSize().height;
    treeSprite->setScale(scaleX, scaleY);
    // ������ľλ�ã���������Ƭ��
    treeSprite->setPosition(position);
    // ��ӵ���ͼ
    _map->addChild(treeSprite, 1);  // ȷ����������ϲ�
    // ���浽��ľvector
    _treesVector.pushBack(treeSprite);
    // �������������Ч
    // CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("plant.wav");
}
bool BaseMapLayer::canPlantTreeAtPosition(cocos2d::Vec2 position) {
    // ��ȡ��ͼ�����飬������ֲ����
    auto objectGroup = _map->getObjectGroup("PlantArea");
    if (!objectGroup) {
        CCLOG("No PlantArea object group found!");
        return false;
    }

    // ��λ��ת������ͼ�Ľڵ�����ϵ
    Vec2 mapPosition = _map->convertToNodeSpace(position);

    // ��������ֲ����
    for (auto& plantAreaValue : objectGroup->getObjects()) {
        auto plantArea = plantAreaValue.asValueMap();  // ȷ�� ValueMap ת��

        float x = plantArea["x"].asFloat();
        float y = plantArea["y"].asFloat();
        float width = plantArea["width"].asFloat();
        float height = plantArea["height"].asFloat();

        cocos2d::Rect plantRect(x, y, width, height);

        // ���λ���Ƿ��ڿ���ֲ������
        if (plantRect.containsPoint(mapPosition)) {
            // ����Ƿ��Ѿ�����
            for (auto tree : _treesVector) {
                if (tree && tree->getBoundingBox().intersectsRect(plantRect)) {
                    return false;  // �Ѿ�������
                }
            }
            return true;  // ������ֲ
        }
    }

    return false;  // ���ڿ���ֲ������
}



