#include "Festival.h"
#include "Toolbar.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#include <map>
#include "BaseMapLayer.h"
#include "MarketPriceSystem.h"
Festival::Festival()
{
}

Festival::~Festival()
{
}
Scene* Festival::createScene(const std::string& spawnPointName)
{
    auto scene = Scene::create();

    auto layer = Festival::create(spawnPointName);

    if (layer != nullptr)
    {
        scene->addChild(layer);
        TimeManager* timeManager = TimeManager::getInstance();
        // 确保TimeManager只被初始化一次
        static bool timeManagerInitialized = false;
        if (!timeManagerInitialized) {
            timeManager->init();
            timeManagerInitialized = true;
        }

        // 确保TimeManager只有一个父节点
        if (timeManager->getParent()) {
            timeManager->removeFromParent();
        }
        scene->addChild(timeManager);
    }
    
    return scene;
}
Festival* Festival::create(const std::string& spawnPointName)
{
    Festival* festival = new (std::nothrow) Festival();
    if (festival && festival->initMap(spawnPointName))
    {
        festival->autorelease();
        return festival;
    }
    CC_SAFE_DELETE(festival);
    return nullptr;
}

bool Festival::init()
{
    if (!BaseMapLayer::init())
    {
        return false;
    }

    return true;
}

bool Festival::initMap(const std::string& spawnPointName)
{
    if (!init())
    {
        return false;
    }
    // 加载地图
    festivalMap = TMXTiledMap::create("mine1.tmx");

    //this->addChild(minemap); // 将地图添加到当前层

    // 获取矿物图层
    //mineralsLayer = minemap->getLayer("mineral");

    loadMap("Festival.tmx");//加入地图层 
    initializePlayer(spawnPointName);//加入玩家层
    this->initMouseEvent();
   

    return true;
}
void Festival::initMouseEvent() {
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
        TMXLayer* backgroundLayer = _map->getLayer("BackGround");
        static auto map = _map;
        if (backgroundLayer) {
            // 获取当前格子的瓦片GID
            int tileGID = backgroundLayer->getTileGIDAt(tileCoord);
            if (tileGID) {
                // 获取瓦片属性
                ValueMap properties = map->getPropertiesForGID(tileGID).asValueMap();
                if (properties.empty()) {
                    CCLOG("No properties found for this tile.");
                }
                else {
                    // 检查food属性
                    if (properties.find("food") != properties.end() && properties.at("food").asBool()) {
                        auto player = Player::getInstance();
                        player->setHealth(100);
                    }
                    // 检查shop属性
                    if (properties.find("shop") != properties.end() && properties.at("shop").asBool()) {
                        static int i = 0;
                        if (i == 0)
                        {
                            i++;
                            MarketPriceSystem::getInstance().applyPromotion();
                        }
                        
                    }
                }
            }
        }
    };

    // 注册新的鼠标监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}
cocos2d::Vec2 Festival::getTileCoordForPosition(cocos2d::Vec2 position) {

    int x = static_cast<int>(position.x / 17.83);
    int y = static_cast<int>(30 * 17.83 - position.y) / (17.83);
    CCLOG("DIANJI%d %d", x, y);

    return cocos2d::Vec2(x, y);
}
