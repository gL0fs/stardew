#include "Forest.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"
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


    loadMap("Forest/Forest.tmx");//�����ͼ�� 
    initializePlayer();//������Ҳ�

    auto toolbar = Toolbar::getInstance();//������ʵ��
    auto uiLayer = Layer::create();
    this->addChild(uiLayer);

    // ��UI�������toolbar
    int toolbarHeight = 16; // ���蹤�����ĸ߶���16����
    auto winSize = Director::getInstance()->getWinSize();
    auto toolbarLayout = ui::Layout::create();
    toolbarLayout->setSize(Size(winSize.width, toolbarHeight)); // ���ò��ִ�С
    toolbarLayout->setIgnoreAnchorPointForPosition(true);
    toolbarLayout->setPosition(Vec2(0, winSize.height / 2 - toolbarHeight / 2)); // ���ò���λ��Ϊ��Ļ��ֱ����
    uiLayer->addChild(toolbarLayout);

    // ����toolbar����ӵ�����

    // ����toolbar��λ��Ϊ���ֵ�����

    toolbar->setPosition(Vec2(toolbarLayout->getContentSize().width / 2, toolbarLayout->getContentSize().height / 2));
	if (toolbar->getParent() == nullptr)
        toolbarLayout->addChild(toolbar);
    CCLOG("add toolbar");

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
	else if (mapName == "farm")
	{
		if (SceneManager::getInstance().isMapInHistory("farm"))
		{
			SceneManager::getInstance().returnToPreviousScene();
			return;
		}
		else {
			auto scene = Map1::createScene();
			SceneManager::getInstance().goToScene(scene, "forest");
		}
	}
    else
    {
        CCLOG("Unknown map: %s", mapName.c_str());
    }
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
        static auto toolbarLayer = Toolbar::getInstance();
        int choice = toolbarLayer->getCurrentToolIndex();
        switch (choice) {
        case 1:
            Fishing(worldLocation);
            break;
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

void Forest::Fishing(cocos2d::Vec2 worldposition) {
    auto position = this->getTileCoordForPosition(worldposition);
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
		auto fish = Sprite::create("fishing.png");
        fish->setScale(10);

		fish->setPosition(worldposition);
        this->addChild(fish,1000);
		//�ȴ�һ��ʱ��������
		Sleep(2000);
		this->removeChild(fish,1000);
   
		
		srand(time(0));
		int random = rand() % 3 + 1;
		_playerInstance->addInventory("fish"+std::to_string(random), 1);
	}
}