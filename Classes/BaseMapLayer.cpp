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

    // 设置键盘监听
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(BaseMapLayer::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(BaseMapLayer::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 设置定时器，更新玩家位置
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
    // 获取玩家单例
    _playerInstance = Player::getInstance();
	// 初始化玩家精灵
	if (!_playerInstance->initPlayer("Player.png")) {
		return;
	}
	// 设置玩家位置
	setPlayerPosition("Objects", "SpawnPoint");
	// 添加玩家精灵到地图层
	this->addChild(_playerInstance);
}

void BaseMapLayer::setPlayerPosition(const std::string& objectGroupName, const std::string& spawnPointName) {
    if (!_map || !_playerInstance) return;

    // 从地图对象组获取出生点
    auto objectGroup = _map->getObjectGroup(objectGroupName);
    if (!objectGroup) return;

    auto spawnPoint = objectGroup->getObject(spawnPointName);
    if (spawnPoint.empty()) return;

    // 设置玩家位置
    float x = spawnPoint["x"].asFloat();
    float y = spawnPoint["y"].asFloat();
    _playerInstance->setPosition(cocos2d::Vec2(x, y));
}

bool BaseMapLayer::isCollisionAtNextPosition(const cocos2d::Vec2& nextPosition) {
    // 使用Player单例的位置进行碰撞检测
    // 实现碰撞逻辑，返回是否发生碰撞
    return false;  // 需要根据具体地图和碰撞规则实现
}

void BaseMapLayer::handlePlayerMovement(const cocos2d::Vec2& direction) {
    if (!_playerInstance) return;

    // 计算下一个位置
    cocos2d::Vec2 nextPosition = _playerInstance->getPosition() + direction;

    // 检查是否发生碰撞
    if (!isCollisionAtNextPosition(nextPosition)) {
        _playerInstance->setPosition(nextPosition);
    }
}

void BaseMapLayer::update(float delta) {
    // 如果存在玩家并且有按键被按下，执行持续移动
    if (_playerInstance && !_moveDirection.equals(Vec2::ZERO)) {
        handlePlayerMovement(_moveDirection);  // 持续移动
    }
}


void BaseMapLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (!_playerInstance) return;

    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_W:
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        _moveDirection.y = 1;  // 向上移动
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_S:
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        _moveDirection.y = -1;  // 向下移动
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _moveDirection.x = -1;  // 向左移动
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _moveDirection.x = 1;  // 向右移动
        break;
    }
	//归一化移动方向
	_moveDirection.normalize();
}

void BaseMapLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (!_playerInstance) return;

    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_W:
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        _moveDirection.y = 0;  // 停止向上移动
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_S:
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        _moveDirection.y = 0;  // 停止向下移动
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _moveDirection.x = 0;  // 停止向左移动
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _moveDirection.x = 0;  // 停止向右移动
        break;
    }
	//归一化移动方向
	_moveDirection.normalize();
}
