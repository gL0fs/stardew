#include "Forest.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"
#include "MyFarm.h"
USING_NS_CC;

Forest::Forest()
{
}

Forest::~Forest()
{
}
Scene* Forest::createScene(int path)
{
    auto scene = Scene::create();
    
    auto layer = Forest::create(path);
	
    if (layer != nullptr)
    {
        scene->addChild(layer);
    }
    auto toolbarLayer = Toolbar::getInstance();
    toolbarLayer->setPositionOnLeft(); // 设置工具栏层位置

    if (toolbarLayer->getParent() == nullptr)
        scene->addChild(toolbarLayer, 1); // 将工具栏层添加到场景中
    else {
        toolbarLayer->getParent()->removeChild(toolbarLayer, false);
        scene->addChild(toolbarLayer);
    }

    CCLOG("add toolbar");
    return scene;
}
Forest* Forest::create(int path)
{
    Forest* forest = new (std::nothrow) Forest();
	forest->_path = path;
    if (forest && forest->initMap())
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

bool Forest::initMap()
{
    if (!init())
    {
        return false;
    }


    _map = TMXTiledMap::create("Forest/Forest.tmx");
    Size mapSize = _map->getContentSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 将地图放大四倍
    _map->setScale(2.5f);
    _map->setAnchorPoint(Vec2(0, 0));
    // 直接将地图的左下角放置在层的左下角
    _map->setPosition(0, 0);

    //修改可见度
	auto layer1 = _map->getLayer("fishing");
	auto layer2 = _map->getLayer("cutting");
    for (int x = 0; x < 60; ++x) {
        for (int y = 0; y < 45; ++y) {
            // 获取每个瓦片的位置
            Vec2 tilePos(x, y);

            // 获取瓦片对象
            Sprite* tileSprite1 = layer1->getTileAt(tilePos);
			Sprite* tileSprite2 = layer2->getTileAt(tilePos);

            if (tileSprite1) {
                // 设置瓦片透明度为 0（不可见）
                tileSprite1->setOpacity(0);
            }
            if (tileSprite2) {
                // 设置瓦片透明度为 0（不可见）
                tileSprite2->setOpacity(0);
            }
        }
    }

    // 添加地图到层
    this->addChild(_map, -1);

    initializePlayer();//加入玩家层

   

    // 创建toolbar并添加到布局

    // 设置toolbar的位置为布局的中心

   

	initMouseEvent();

    return true;

}

void Forest::switchMap(const std::string& mapName,int path)
{
    if (mapName == "test")
    {
        /*if (SceneManager::getInstance().isMapInHistory("test"))
        {
            SceneManager::getInstance().returnToPreviousScene();
            return;
        }
        else {
        */
            auto scene = Test::createScene(path);
            SceneManager::getInstance().goToScene(scene, "forest");
        //}
    }
	/*else if (mapName == "farm")
	{
		if (SceneManager::getInstance().isMapInHistory("farm"))
		{
			SceneManager::getInstance().returnToPreviousScene();
			return;
		}
		else {
			auto scene = MyFarm::createScene();
			SceneManager::getInstance().goToScene(scene, "forest");
		}
	}*/
    /*else if (mapName == "house")
    {
        if (SceneManager::getInstance().isMapInHistory("house"))
        {
            SceneManager::getInstance().returnToPreviousScene();
            return;
        }
        else {
            auto scene = House::createScene();
            SceneManager::getInstance().goToScene(scene, "forest");
        }
    }*/
    else
    {
        CCLOG("Unknown map: %s", mapName.c_str());
    }
}

void Forest::initMouseEvent() {
    // 移除现有的鼠标监听器
    if (_mouseListener) {
        _eventDispatcher->removeEventListener(_mouseListener);
        _mouseListener = nullptr;
        CCLOG("Existing mouse listener removed");
    }

    // 创建新的鼠标监听器
    _mouseListener = cocos2d::EventListenerMouse::create();
    CCLOG("New mouse listener created");
    // 设置鼠标按下事件的回调函数
    _mouseListener->onMouseDown = [this](cocos2d::Event* event) {
        auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
        cocos2d::Vec2 mouseLocation = mouseEvent->getLocationInView();
        cocos2d::Vec2 worldLocation = this->convertToNodeSpace(mouseLocation);

        CCLOG("Mouse down at location: (%f, %f)", mouseLocation.x, mouseLocation.y);
        CCLOG("World location: (%f, %f)", worldLocation.x, worldLocation.y);

        // 将鼠标位置转换为地图坐标
        cocos2d::Vec2 tileCoord = this->getTileCoordForPosition(worldLocation);

        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
            // 处理左键按下的逻辑
            CCLOG("左键按下");
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
			// 处理右键按下的逻辑
			CCLOG("右键按下");
			collect(tileCoord);
		}

        

    };

    // 注册新的鼠标监听器
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

	//如果离点击的钓鱼区域太远，不会钓到鱼
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
    

    // 获取钓鱼区的位置和大小
    float objectX = object["x"].asFloat() * mapScale;
    float objectY = object["y"].asFloat() * mapScale;
    float width = object["width"].asFloat() * mapScale;
    float height = object["height"].asFloat() * mapScale;
    int obx = static_cast<int>(objectX / 17.83);
    int oby = static_cast<int>(mapSize.height * 17.83 - objectY) / (17.83);
    int obwidth = static_cast<int>(width / 17.83);
    int obheight = static_cast<int>(height / 17.83) + 1;
    // 创建矩形
    CCLOG("obx %d oby %d", obx, oby);
    CCLOG("width %d height %d", obwidth, obheight);
    cocos2d::Rect fishRect(obx, oby- obheight, obwidth, obheight);
	if (fishRect.containsPoint(position)) {
		auto layer=_map->getLayer("fishing");
        Sprite* tileSprite = layer->getTileAt(position);
		// 钓鱼动画
        if (tileSprite) {
            tileSprite->setOpacity(255);  
        }
		//等待一段时间后钓到鱼
        this->scheduleOnce([=](float dt) {
            tileSprite->setOpacity(0);
            srand(time(0));
            int random = rand() % 3 + 1;
            _playerInstance->addInventory("fish" + std::to_string(random), 1);
            }, 2.0f, "delay_action_key");  // 延迟2秒后执行
	}
}

void Forest::deleteWholeObject(cocos2d::Vec2 position, TMXLayer* layer) {
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
    //如果离点击的采集物区域太远，不会收集
    if (abs(x - position.x) > 1 || abs(y - position.y) > 1) {
        return;
    }

	auto gid1 = _map->getLayer("collecting1")->getTileGIDAt(position);
	auto gid2 = _map->getLayer("collecting2")->getTileGIDAt(position);
	auto gid3 = _map->getLayer("collecting3")->getTileGIDAt(position);

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

    //如果离点击的树太远，不会砍
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
		count++;
		//显示砍树动画
        auto layer = _map->getLayer("cutting");
        Sprite* tileSprite = layer->getTileAt(position);
        // 砍树鱼动画
        if (tileSprite) {
            tileSprite->setOpacity(255);
        }
        this->scheduleOnce([=](float dt) {
            tileSprite->setOpacity(0);
            }, 0.3f, "delay_action_key");  // 延迟0.3秒后执行
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