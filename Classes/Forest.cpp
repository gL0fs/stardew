#include "Forest.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"
#include "MyFarm.h"
#include "AudioManager.h"
USING_NS_CC;

Forest::Forest()
{
}

Forest::~Forest()
{
}
Scene* Forest::createScene(const std::string& spawnPointName)
{
    auto scene = Scene::create();
    
    auto layer = Forest::create(spawnPointName);
	
    if (layer != nullptr)
    {
        scene->addChild(layer);
        TimeManager* timeManager = TimeManager::getInstance();
        // ȷ��TimeManagerֻ����ʼ��һ��
        static bool timeManagerInitialized = false;
        if (!timeManagerInitialized) {
            timeManager->init();
            timeManagerInitialized = true;
        }

        // ȷ��TimeManagerֻ��һ�����ڵ�
        if (timeManager->getParent()) {
            timeManager->removeFromParent();
        }
        scene->addChild(timeManager);
    }
    auto toolbarLayer = Toolbar::getInstance();
    toolbarLayer->setPositionOnLeft(); // ���ù�������λ��

    if (toolbarLayer->getParent() == nullptr)
        scene->addChild(toolbarLayer, 1); // ������������ӵ�������
    else {
        toolbarLayer->getParent()->removeChild(toolbarLayer, false);
        scene->addChild(toolbarLayer);
    }

    CCLOG("add toolbar");
    return scene;
}
Forest* Forest::create(const std::string& spawnPointName)
{
    Forest* forest = new (std::nothrow) Forest();
    if (forest && forest->initMap(spawnPointName))
    {
        forest->autorelease();
        return forest;
    }
    CC_SAFE_DELETE(forest);
    return nullptr;
}

bool Forest::init()
{
    if (!BaseMapLayer::init())
    {
        return false;
    }

    return true;
}

bool Forest::initMap(const std::string& spawnPointName)
{
    if (!init())
    {
        return false;
    }


    _map = cocos2d::TMXTiledMap::create("Forest/Forest.tmx");
    Size mapSize = _map->getContentSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ����ͼ�Ŵ��ı�
    _map->setScale(2.5f);
    _map->setAnchorPoint(Vec2(0, 0));
    // ֱ�ӽ���ͼ�����½Ƿ����ڲ�����½�
    _map->setPosition(0, 0);

    //�޸Ŀɼ���
	auto layer1 = _map->getLayer("fishing");
	auto layer2 = _map->getLayer("cutting");
    for (int x = 0; x < 60; ++x) {
        for (int y = 0; y < 45; ++y) {
            // ��ȡÿ����Ƭ��λ��
            Vec2 tilePos(x, y);

            // ��ȡ��Ƭ����
            Sprite* tileSprite1 = layer1->getTileAt(tilePos);
			Sprite* tileSprite2 = layer2->getTileAt(tilePos);

            if (tileSprite1) {
                // ������Ƭ͸����Ϊ 0�����ɼ���
                tileSprite1->setOpacity(0);
            }
            if (tileSprite2) {
                // ������Ƭ͸����Ϊ 0�����ɼ���
                tileSprite2->setOpacity(0);
            }
        }
    }

    // ��ӵ�ͼ����
    this->addChild(_map, -1);

    initializePlayer(spawnPointName);//������Ҳ�

   

    // ����toolbar����ӵ�����

    // ����toolbar��λ��Ϊ���ֵ�����

   

	initMouseEvent();

    return true;

}


void Forest::initMouseEvent() {
    // �Ƴ����е���������
    if (_mouseListener) {
        _eventDispatcher->removeEventListener(_mouseListener);
        _mouseListener = nullptr;
        CCLOG("Existing mouse listener removed");
    }

    // �����µ���������
    _mouseListener = cocos2d::EventListenerMouse::create();
    CCLOG("New mouse listener created");
    // ������갴���¼��Ļص�����
    _mouseListener->onMouseDown = [this](cocos2d::Event* event) {
        auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
        cocos2d::Vec2 mouseLocation = mouseEvent->getLocationInView();
        cocos2d::Vec2 worldLocation = this->convertToNodeSpace(mouseLocation);

        CCLOG("Mouse down at location: (%f, %f)", mouseLocation.x, mouseLocation.y);
        CCLOG("World location: (%f, %f)", worldLocation.x, worldLocation.y);

        // �����λ��ת��Ϊ��ͼ����
        cocos2d::Vec2 tileCoord = this->getTileCoordForPosition(worldLocation);

        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
            // ����������µ��߼�
            CCLOG("�������");
            static auto toolbarLayer = Toolbar::getInstance();
            int choice = toolbarLayer->getCurrentToolIndex();
            switch (choice) {
            case 1:
                Fishing(tileCoord);
                break;
            case 4:
				cutTree(tileCoord);
				break;
            }
		}
		else if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			// �����Ҽ����µ��߼�
			CCLOG("�Ҽ�����");
			collect(tileCoord);
		}

        

    };

    // ע���µ���������
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

cocos2d::Vec2 Forest::getTileCoordForPosition(cocos2d::Vec2 position) {
	
    int x = static_cast<int>(position.x / 17.83);
    int y = static_cast<int>(45 * 17.83 - position.y) / (17.83);
    CCLOG("DIANJI%d %d", x, y);

    return cocos2d::Vec2(x, y);
}

void Forest::Fishing(cocos2d::Vec2 position) {
    cocos2d::Size mapSize = _map->getMapSize();
    cocos2d::Size tileSize = _map->getTileSize();
    int x = static_cast<int>(_playerInstance->getPosition().x / 17.83);
    int y = static_cast<int>(mapSize.height * 17.83 - _playerInstance->getPosition().y) / (17.83);

	//��������ĵ�������̫Զ�����������
    if (abs(x - position.x) > 5 || abs(y - position.y) > 5) {
        return;
    }


    auto objectGroup = _map->getObjectGroup("Objects");
	if (!objectGroup) {
		CCLOG("No FishArea object group found!");
		return;
	}
    auto object=objectGroup->getObject("Water");
    float mapScale = _map->getScale();
    

    // ��ȡ��������λ�úʹ�С
    float objectX = object["x"].asFloat() * mapScale;
    float objectY = object["y"].asFloat() * mapScale;
    float width = object["width"].asFloat() * mapScale;
    float height = object["height"].asFloat() * mapScale;
    int obx = static_cast<int>(objectX / 17.83);
    int oby = static_cast<int>(mapSize.height * 17.83 - objectY) / (17.83);
    int obwidth = static_cast<int>(width / 17.83);
    int obheight = static_cast<int>(height / 17.83) + 1;
    // ��������
    CCLOG("obx %d oby %d", obx, oby);
    CCLOG("width %d height %d", obwidth, obheight);
    cocos2d::Rect fishRect(obx, oby- obheight, obwidth, obheight);
	if (fishRect.containsPoint(position)) {
		auto layer=_map->getLayer("fishing");
        Sprite* tileSprite = layer->getTileAt(position);
		// ���㶯��
        if (tileSprite) {
            tileSprite->setOpacity(255);  
        }
        AudioManager::getInstance()->playEffect("fish.mp3", 1.0f);
		//�ȴ�һ��ʱ��������
        this->scheduleOnce([=](float dt) {
            tileSprite->setOpacity(0);
            srand(time(0));
            int random = rand() % 3 + 1;
            _playerInstance->addInventory("fish" + std::to_string(random), 1);
            }, 2.0f, "delay_action_key");  // �ӳ�2���ִ��
	}
}

void Forest::deleteWholeObject(cocos2d::Vec2 position, cocos2d::TMXLayer* layer) {
	auto gid = layer->getTileGIDAt(position);
	if (gid != 0) {
		layer->removeTileAt(position);
		deleteWholeObject(Vec2(position.x+1,position.y), layer);
		deleteWholeObject(Vec2(position.x - 1, position.y), layer);
		deleteWholeObject(Vec2(position.x, position.y + 1), layer);
		deleteWholeObject(Vec2(position.x, position.y - 1), layer);
	}
    else {
        return;
    }
}

void Forest::collect(cocos2d::Vec2 position) {
    int x = static_cast<int>(_playerInstance->getPosition().x / 17.83);
    int y = static_cast<int>(45 * 17.83 - _playerInstance->getPosition().y) / (17.83);
    //��������Ĳɼ�������̫Զ�������ռ�
    if (abs(x - position.x) > 1 || abs(y - position.y) > 1) {
        return;
    }

	auto gid1 = _map->getLayer("collecting1")->getTileGIDAt(position);
	auto gid2 = _map->getLayer("collecting2")->getTileGIDAt(position);
	auto gid3 = _map->getLayer("collecting3")->getTileGIDAt(position);
    AudioManager::getInstance()->playEffect("shouji.mp3", 1.0f);
    CCLOG("SHOUJI");
	if (gid1 != 0) {
		deleteWholeObject(position, _map->getLayer("collecting1"));
		_playerInstance->addInventory("berry", 1);
	}
	else if (gid2 != 0) {
		deleteWholeObject(position, _map->getLayer("collecting2"));
		_playerInstance->addInventory("plant", 1);
	}
	else if (gid3 != 0) {
		deleteWholeObject(position, _map->getLayer("collecting3"));
		_playerInstance->addInventory("flower", 1);
	}
	
}

void Forest::cutTree(cocos2d::Vec2 position) {
    int x = static_cast<int>(_playerInstance->getPosition().x / 17.83);
    int y = static_cast<int>(45 * 17.83 - _playerInstance->getPosition().y) / (17.83);

    //�����������̫Զ�����ῳ
    if (abs(x - position.x) > 1 || abs(y - position.y) > 1) {
        return;
    }


	static auto _position = position;
    static int count = 1;
	if (_position != position) {
		_position = position;
		count = 1;
    }
    else {
        AudioManager::getInstance()->playEffect("wood.mp3", 1.0f);
		count++;
		//��ʾ��������
        auto layer = _map->getLayer("cutting");
        Sprite* tileSprite = layer->getTileAt(position);
        // �����㶯��
        if (tileSprite) {
            tileSprite->setOpacity(255);
        }
        this->scheduleOnce([=](float dt) {
            tileSprite->setOpacity(0);
            }, 0.3f, "delay_action_key");  // �ӳ�0.3���ִ��
    }
	CCLOG("count%d", count);
	if (count > 5) {
        auto gid1 = _map->getLayer("tree1")->getTileGIDAt(position);
        auto gid2 = _map->getLayer("tree2")->getTileGIDAt(position);

        if (gid1 != 0) {
            deleteWholeObject(position, _map->getLayer("tree1"));
            _playerInstance->addInventory("wood", 5);
        }
        else if (gid2 != 0) {
            deleteWholeObject(position, _map->getLayer("tree2"));
            _playerInstance->addInventory("wood", 10);
        }
	}
    
}