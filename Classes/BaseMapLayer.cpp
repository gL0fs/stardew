#include "BaseMapLayer.h"

USING_NS_CC;
#define COCOS2D_DEBUG 1
BaseMapLayer::BaseMapLayer() : _map(nullptr), _playerInstance(nullptr) {
}

BaseMapLayer* create(const std::string& tmxFile) {
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

    // ����ͼ�Ŵ��ı�
    _map->setScale(2.5f);
    _map->setAnchorPoint(Vec2(0, 0));
    // ֱ�ӽ���ͼ�����½Ƿ����ڲ�����½�
    _map->setPosition(0,0);

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

    //��û��ӵ�����£������Ҿ��鵽��ͼ��
	if (!_playerInstance->getParent())
        this->addChild(_playerInstance);
}

void BaseMapLayer::setPlayerPosition(const std::string& objectGroupName, const std::string& spawnPointName) {
    if (!_map || !_playerInstance) return;

    // �ӵ�ͼ�������ȡ������
    auto objectGroup = _map->getObjectGroup(objectGroupName);
    if (!objectGroup) return;

    auto spawnPoint = objectGroup->getObject(spawnPointName);
    if (spawnPoint.empty()) return;

    // ��ȡ��ͼ�ĳߴ�����ű���
    float mapScale = _map->getScale();
    cocos2d::Size mapSize = _map->getMapSize();
    cocos2d::Size tileSize = _map->getTileSize();

    // ���ݵ�ͼ���ű�������spawn point����
    float x = spawnPoint["x"].asFloat() * mapScale;
    // ת��y���꣺�����Ͻ�ԭ��ת��Ϊ���½�ԭ��
    float y = spawnPoint["y"].asFloat() * mapScale;
    CCLOG("MAPSIZE%f %f", mapSize.width, mapSize.height);
    CCLOG("SPAWN %f %f", spawnPoint["x"].asFloat(), spawnPoint["y"].asFloat());
    
    CCLOG("SPAWN %f %f", x, y);
    

    // �������λ��
    _playerInstance->setPosition(cocos2d::Vec2(x, y));
    setViewPointCenter(_playerInstance->getPosition());
   
}

bool BaseMapLayer::isCollisionAtNextPosition(const cocos2d::Vec2& nextPosition) {
    // ��ȡ�ϰ����
    auto obstacles = _map->getLayer("BackGround"); // �����ϰ������Ϊ"Obstacles"
    if (!obstacles) {
        // ���û���ϰ���㣬�򲻽�����ײ���
        return false;
    }

    // ��ȡ��Ƭ��С����ͼ��С�͵�ͼ���ű���
    auto tileSize = this->_map->getTileSize();
    auto mapSize = this->_map->getMapSize();
    auto mapScale = this->_map->getScale(); // ��ȡ��ͼ�����ű���
    
    // ����һ��λ��ת��Ϊ��Ƭ���꣬���ǵ�ͼ����
    int x = static_cast<int>(nextPosition.x / 17.83) ;
    int y = static_cast<int>(mapSize.height * 17.83 - nextPosition.y) / (17.83);
    auto tileCoord = cocos2d::Vec2(x, y);
    CCLOG("nextPosition:%f %f", nextPosition.x, nextPosition.y);
    //CCLOG("tileSize:%f %f", tileSize.width, tileSize.height);

    CCLOG("%d %d",x,y);
   
    // ��ȡ����Ƭ�����GID
    int GID = obstacles->getTileGIDAt(tileCoord);
    
    // ���GIDΪ0����ʾ��λ��û����Ƭ���������ϰ���
    if (GID == 0) {
        return false;
    }
    else
		return true;

    // ��ȡ��Ƭ������
    cocos2d::Value properties = _map->getPropertiesForGID(GID);
    if (properties.getType() == cocos2d::Value::Type::MAP) {
        cocos2d::ValueMap propMap = properties.asValueMap();
        // ����Ƿ���"collidable"���Բ���ֵΪtrue
        bool collidable = propMap.find("collidable") != propMap.end() && propMap.at("collidable").asBool();
        CCLOG("collision%d %d", x, y);
        return collidable;
    }
    
    // Ĭ�ϲ�������ײ
    return false;
}

void BaseMapLayer::handlePlayerMovement(const cocos2d::Vec2& direction) {
    if (!_playerInstance) return;

    // ������һ��λ��
    CCLOG("PLAYER%f %f", _playerInstance->getPosition().x, _playerInstance->getPosition().y);
    cocos2d::Vec2 nextPosition = _playerInstance->getPosition() + direction;

    // ����Ƿ�����ײ
    if (!isCollisionAtNextPosition(nextPosition)) {
        _playerInstance->setPosition(nextPosition);
        this->setViewPointCenter(nextPosition);
    }
    checkChangeMap(nextPosition);
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
void BaseMapLayer::setViewPointCenter(Point position) {
    /*auto winSize = Director::getInstance()->getWinSize();
    int x=MAX(position.x,winSize.width/2);
    int y = MAX(position.y, winSize.height / 2);

    x = MIN(x, (_map->getMapSize().width * this->_map->getTileSize().width) - winSize.height / 2);
    y = MIN(y, (_map->getMapSize().height * this->_map->getTileSize().width) - winSize.height / 2);
    auto actualPosition = Point(x, y);

    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
    auto viewPoint = centerOfView - actualPosition;
    this->setPosition(viewPoint);*/
    auto winSize = Director::getInstance()->getWinSize();
    auto mapScale = _map->getScale(); // ��ȡ��ͼ�����ű���

    // �����ͼ�����سߴ�
    float mapPixelWidth = _map->getMapSize().width * _map->getTileSize().width * mapScale;
    float mapPixelHeight = _map->getMapSize().height * _map->getTileSize().height * mapScale;

    // ��������λ�ã�ȷ����ͼ���ᳬ����ͼ�߽�
    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);
    x = MIN(x, mapPixelWidth - winSize.width / 2);
    y = MIN(y, mapPixelHeight - winSize.height / 2);

    // ����ʵ��λ�ã���������
    auto actualPosition = Point(x, y);

    // ������ͼ�㣬��������
    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
    auto viewPoint = centerOfView - actualPosition ;
    this->setPosition(viewPoint);
}

void BaseMapLayer::checkChangeMap(const cocos2d::Vec2& nextPosition) {
    //�򿪶����
    auto objectGroup = _map->getObjectGroup("Objects");
    if (!objectGroup) {
        CCLOG("Object layer not found!");
        return;
    }
    CCLOG("open successful");

    // ��ȡ��Ƭ��С����ͼ��С�͵�ͼ���ű���
    auto tileSize = this->_map->getTileSize();
    auto mapSize = this->_map->getMapSize();
    auto mapScale = this->_map->getScale(); // ��ȡ��ͼ�����ű���

    // ����һ��λ��ת��Ϊ��Ƭ���꣬���ǵ�ͼ����
    int x = static_cast<int>(nextPosition.x / 17.83);
    int y = static_cast<int>(mapSize.height * 17.83 - nextPosition.y) / (17.83);
	CCLOG("%d x %d y", x, y);

	// ��ȡȫ�����������,�浽vector��
    int i = 1;
    while (true) {
        std::string objectName = std::to_string(i);
        auto object = objectGroup->getObject(objectName);
        if (object.empty()) {
			CCLOG("No more objects found!");
            break;
        }
        CCLOG("object %d", i);
        // ��ȡ��ͼ�ĳߴ�����ű���
        float mapScale = _map->getScale();
        cocos2d::Size mapSize = _map->getMapSize();
        cocos2d::Size tileSize = _map->getTileSize();

        // ���ݵ�ͼ���ű�������spawn point����
        float objectX = object["x"].asFloat() * mapScale;
        // ת��y���꣺�����Ͻ�ԭ��ת��Ϊ���½�ԭ��
        float objectY = object["y"].asFloat() * mapScale;
        int obx = static_cast<int>(objectX / 17.83);
        int oby = static_cast<int>(mapSize.height * 17.83 - objectY) / (17.83);

        CCLOG("%d obx %d oby", obx, oby);
        if (x == obx
            && y == oby ) {
            // ����������ײ
            CCLOG("Player collided with object!");
            // ����Ƿ���"MapName"����
            if (object.find("MapName") != object.end()) {
                // ��ȡĿ�ĵص�ͼ�ļ���
                std::string destination = object.at("MapName").asString();
                // ����Ŀ�ĵص�ͼ
				switchMap(destination);
                return;
            }
        }
        i++;
    }
}
