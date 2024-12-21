#include "Mine.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#include <map>



void Mine::initializeNaijiuMap() {
    minemap = TMXTiledMap::create("mine1.tmx");
  
    cocos2d::TMXLayer* mineralsLayer = minemap->getLayer("mineral");
   
    cocos2d::Size mapSize = minemap->getMapSize();
    
    for (int x = 0; x < 40; ++x) {
        for (int y = 0; y < 30; ++y) {
            cocos2d::Vec2 tileCoord(x, y);
            int tileGID = mineralsLayer->getTileGIDAt(tileCoord);
            // ����Ĭ���;ö�Ϊ0���ʵ���ֵ
            int naijiu = 0;
            if (tileGID != 0) {
                cocos2d::Value properties = minemap->getPropertiesForGID(tileGID);
                if (!properties.isNull()) {
                    int isMine = properties.asValueMap().at("mine").asBool();
                    if (isMine == 1) {
                        naijiu = properties.asValueMap().at("naijiu").asInt();
                    }
                }
            }
            // ��ʹ��Ƭ�����ڣ�ҲΪ������Ĭ���;ö�
            tileNaijiuMap[std::make_pair(x, y)] = naijiu;
        }
    }
}
Mine::Mine()
{
}

Mine::~Mine()
{
}
Scene* Mine::createScene()
{
    auto scene = Scene::create();

    auto layer = Mine::create();

    if (layer != nullptr)
    {
        scene->addChild(layer);
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
Mine* Mine::create()
{
    Mine* mine = new (std::nothrow) Mine();
    if (mine && mine->initMap())
    {
        mine->autorelease();
        return mine;
    }
    CC_SAFE_DELETE(mine);
    return nullptr;
}

bool Mine::init()
{
    if (!BaseMapLayer::init())
    {
        return false;
    }
    
    return true;
}

bool Mine::initMap()
{
    if (!init())
    {
        return false;
    }
    // ���ص�ͼ
    minemap = TMXTiledMap::create("mine1.tmx");
   

    // ��ȡ����ͼ��
    mineralsLayer = minemap->getLayer("mineral");
 
    loadMap("mine1.tmx");//�����ͼ�� 
    initializePlayer();//������Ҳ�
    this->initMouseEvent();
    this->initializeNaijiuMap();
    
    return true;
}
void Mine::initMouseEvent() {
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

        // ��Ⲣ��������
        static auto toolbarLayer = Toolbar::getInstance();
        static auto player= Player::getInstance();
        auto zuobiao = player->getxy();
        int dx = std::abs(tileCoord.x - zuobiao.x);
        int dy = std::abs(tileCoord.y - zuobiao.y);
        CCLOG("DX DY TOOL  %d %d %d", dx, dy, toolbarLayer->getCurrentToolIndex());
        if (toolbarLayer->getCurrentToolIndex() == 3 && dx <= 1 && dy <= 1)
        {
            this->removeMineralAtTileCoord(tileCoord);
        }
        };

    // ע���µ���������
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}
cocos2d::Vec2 Mine::getTileCoordForPosition(cocos2d::Vec2 position) {
    
    int x = static_cast<int>(position.x / 17.83);
    int y = static_cast<int>(30 * 17.83 - position.y) / (17.83);
    CCLOG("DIANJI%d %d",x,y);
    
    return cocos2d::Vec2(x, y);
}

void Mine::removeMineralAtTileCoord(cocos2d::Vec2 tileCoord) {
    const auto _minemap = TMXTiledMap::create("mine1.tmx");
    const auto _mineralsLayer = _minemap->getLayer("mineral");
    static auto mineralsLayer = _map->getLayer("mineral");
    // ����ש�����Ƿ���Ч
    if (tileCoord.x >= 0 && tileCoord.x < 40 &&
        tileCoord.y >= 0 && tileCoord.y < 30) {
        // ��ȡ��ǰ��ש��GID
        CCLOG("1");
        int tileGID = _mineralsLayer->getTileGIDAt(tileCoord);
        CCLOG("2");
        // ����Ƿ��п���
        if (tileGID != 0) {
            CCLOG("exist");
            // ��ȡ��ש����
            if (!minemap) {
                CCLOG("minemap is NULL or invalid");
                return;
            }

            cocos2d::Value properties = _minemap->getPropertiesForGID(tileGID);

            CCLOG("getid");
            if (!properties.isNull()) {
                cocos2d::ValueMap propMap = properties.asValueMap();
                CCLOG("1");
                // ����������Ƿ���"mine"��ֵΪtrue
                bool isMine = propMap.at("mine").asBool();
                CCLOG("2");
                CCLOG("MINE%d", isMine ? 1 : 0); // ���1��0����ʾtrue��false
                if (isMine) {
                    CCLOG("mineexist");
                    auto it = tileNaijiuMap.find(std::make_pair(tileCoord.x, tileCoord.y));
                    if (it != tileNaijiuMap.end()) {
                        // �����;ö�
                        CCLOG("%d", it->second);
                        it->second -= 1;
                        // ����;ö��Ƿ�Ϊ0
                        if (it->second == 0) {
                            if (tileCoord.x < 0 || tileCoord.x >= 40 || tileCoord.y < 0 || tileCoord.y >= 30) {
                                CCLOG("tileCoord out of range: (%d, %d)", tileCoord.x, tileCoord.y);
                                return;
                            }
                            if (mineralsLayer == nullptr) {
                                CCLOG("mineralsLayer is NULL");
                                return;
                            }
                            // �Ƴ�����
                            CCLOG("REMOVE");
                            // ��ȡ"name"���ԣ���������һ������ֵ
                            int mineralNameInt = propMap.at("name").asInt();
                       
                            // ����ֱ��ʹ������ֵ����ʶ��Ʒ
                            _playerInstance->addInventory("kuang" + std::to_string(mineralNameInt), 1);
                            mineralsLayer->setTileGID(0, tileCoord);
                            CCLOG("Tile GID after removal: %d", mineralsLayer->getTileGIDAt(tileCoord));
                            Director::getInstance()->drawScene();

                            // ��ӳ�����Ƴ�
                            tileNaijiuMap.erase(it);
                        }
                    }
                }
            }
        }
    }
}

void Mine::switchMap(const std::string& mapName,int path) {
    return;
}