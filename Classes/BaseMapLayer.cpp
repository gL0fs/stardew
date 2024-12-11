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

    // ���ü��̼���
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
    float scaleX = visibleSize.width / mapSize.width;
    float scaleY = visibleSize.height / mapSize.height;
    float scale = MAX(scaleX, scaleY);
    _map->setScale(scale);
    _map->setPosition(origin.x + (visibleSize.width - mapSize.width * scale) / 2,
        origin.y + (visibleSize.height - mapSize.height * scale) / 2);
    this->addChild(_map, -1);
}


void BaseMapLayer::initializePlayer() {
    // ��ȡ��ҵ���
    _playerInstance = Player::getInstance();
	// ��ʼ����Ҿ���
	if (!_playerInstance->initPlayer("Player.png")) {
		return;
	}
	// �������λ��
    // ��ȡ��Ƭ��ͼ����Ƭ�ߴ�
    auto tileSize = _map->getTileSize();

    // ��ȡ��Ҿ����ԭʼ�ߴ�
    auto playerContentSize = _playerInstance->getContentSize();

    // �������ű���
    float scaleWidth = tileSize.width / playerContentSize.width;
    float scaleHeight = tileSize.height / playerContentSize.height;
    // ����ѡ����ݿ�Ȼ�߶����ţ��������߶����ǣ�ȡ��Сֵ��
    float scale = MIN(scaleWidth, scaleHeight);

    // ������Ҿ�������ű���
    _playerInstance->setScale(scale);
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
}

bool BaseMapLayer::isCollisionAtNextPosition(const cocos2d::Vec2& nextPosition) {
    // ��ȡ�ϰ����
    auto obstacles = _map->getLayer("BackGround"); // �����ϰ������Ϊ"Obstacles"
    if (!obstacles) {
        // ���û���ϰ���㣬�򲻽�����ײ���
        return false;
    }

    // ��ȡ��Ƭ��С�͵�ͼ��С
    auto tileSize = this->_map->getTileSize();
    auto mapSize = this->_map->getMapSize();

    // ����һ��λ��ת��Ϊ��Ƭ����
    int x = nextPosition.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - nextPosition.y) / tileSize.height;
    auto tileCoord = cocos2d::Vec2(x, y);

    // ��ȡ����Ƭ�����GID
    int GID = obstacles->getTileGIDAt(tileCoord);

    // ���GIDΪ0����ʾ��λ��û����Ƭ���������ϰ���
    if (GID == 0) {
        return false;
    }

    // ��ȡ��Ƭ������
    cocos2d::Value properties = _map->getPropertiesForGID(GID);
    if (properties.getType() == cocos2d::Value::Type::MAP) {
        cocos2d::ValueMap propMap = properties.asValueMap();
        // ����Ƿ���"collidable"���Բ���ֵΪtrue
        bool collidable = propMap.find("collidable") != propMap.end() && propMap.at("collidable").asBool();
        return collidable;
    }

    // Ĭ�ϲ�������ײ
    return false;
}

void BaseMapLayer::handlePlayerMovement(const cocos2d::Vec2& direction) {
    if (!_playerInstance) return;

    // ������һ��λ��
    cocos2d::Vec2 nextPosition = _playerInstance->getPosition() + direction;

    // ����Ƿ�����ײ
    if (!isCollisionAtNextPosition(nextPosition)) {
        _playerInstance->setPosition(nextPosition);
    }
}

void BaseMapLayer::update(float delta) {
    // ���������Ҳ����а��������£�ִ�г����ƶ�
    if (_playerInstance && !_moveDirection.equals(Vec2::ZERO)) {
        handlePlayerMovement(_moveDirection);  // �����ƶ�
    }
}


void BaseMapLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (!_playerInstance) return;

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
