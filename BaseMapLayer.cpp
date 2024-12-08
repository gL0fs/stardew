#include "BaseMapLayer.h"
#include "extensions/cocos-ext.h" // For keyboard support
USING_NS_CC;

BaseMapLayer::BaseMapLayer()
    : _map(nullptr), _player(nullptr)
{
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

bool BaseMapLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(BaseMapLayer::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(BaseMapLayer::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 设置定时器更新精灵位置
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

void BaseMapLayer::setPlayerPosition(const std::string& objectGroupName, const std::string& spawnPointName)
{
    TMXObjectGroup* objects = _map->getObjectGroup(objectGroupName);
    CCASSERT(objects, "ObjectGroup not found");
    auto spawnPoint = objects->getObject(spawnPointName);
    CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");

    int x = spawnPoint["x"].asInt();
    int y = spawnPoint["y"].asInt();
    auto tileSize = _map->getTileSize();

    _player = Sprite::create("player.png");
    _player->setScale(tileSize.width / _player->getContentSize().width,
        tileSize.height / _player->getContentSize().height);
    _player->setPosition(x, y);
    _map->addChild(_player, 10);
}
/*void BaseMapLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
            _isMovingUp = true;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            _isMovingDown = true;
            break;
        case EventKeyboard::KeyCode::KEY_A:
            _isMovingLeft = true;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            _isMovingRight = true;
            break;
    }
}

void BaseMapLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
            _isMovingUp = false;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            _isMovingDown = false;
            break;
        case EventKeyboard::KeyCode::KEY_A:
            _isMovingLeft = false;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            _isMovingRight = false;
            break;
    }
}

void BaseMapLayer::update(float delta)
{
    Vec2 playerPos = _player->getPosition();
    Vec2 velocity = Vec2::ZERO;

    if (_isMovingUp)    velocity.y += _playerSpeed;
    if (_isMovingDown)  velocity.y -= _playerSpeed;
    if (_isMovingLeft)  velocity.x -= _playerSpeed;
    if (_isMovingRight) velocity.x += _playerSpeed;

    playerPos += velocity * delta;
    _player->setPosition(playerPos);
}*/