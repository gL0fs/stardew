#include "Shop.h"
#include "Player.h"
Shop* Shop::_instance = nullptr; // 初始化单例实例

Shop* Shop::getInstance() {
    if (!_instance) {
        _instance = new (std::nothrow) Shop();
        if (_instance && _instance->init()) {
            // 不要使用 autorelease()
        }
        else {
            CC_SAFE_DELETE(_instance);
            _instance = nullptr; // 确保 _instance 被设置为 nullptr
        }
    }
    return _instance;
}

Shop::Shop() {
    // 私有构造函数
}

Shop::~Shop() {
    // 私有析构函数
}

bool Shop::init() {
    if (!Layer::init()) {
        return false;
    }

    // 加载商店的 TMX 地图
    _tileMap = TMXTiledMap::create("shop.tmx"); // 替换为你的商店 TMX 文件
    CCLOG("SHOPINTIAL");
    if (!_tileMap) {
        CCLOG("Error: Failed to load shop TMX map!");
        return false;
    }
    _tileMap->setScale(5.0f);
    _tileMap->setAnchorPoint(Vec2(0.5, 0.5));
    _tileMap->setPosition(Director::getInstance()->getVisibleSize() / 2);
    
    this->addChild(_tileMap);

    // 获取物品层
    _itemsLayer = _tileMap->getLayer("items"); // 替换为你的物品层名称
    if (!_itemsLayer) {
        CCLOG("Error: 'items' layer not found in the TMX map!");
        return false;
    }

    // 初始化选中的物品坐标
    _selectedItemCoord = Vec2(SHOP_AREA_START_X, SHOP_AREA_START_Y);

    // 监听键盘事件
    auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = CC_CALLBACK_2(Shop::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    // 显示玩家持有的金钱
    displayPlayerMoney();
    return true;
}

void Shop::displayShop() {
    auto shop = Shop::getInstance();
    static int visible=1;
    if (!shop->getParent()) {
        Director::getInstance()->getRunningScene()->addChild(shop);
        
    }
    else {
        visible = 1 - visible;
        shop->setVisible(visible);
    }
}

void Shop::highlightSelectedItem() {
    // 重置所有物品的缩放
    for (int y = SHOP_AREA_START_Y; y <= SHOP_AREA_END_Y; ++y) {
        for (int x = SHOP_AREA_START_X; x <= SHOP_AREA_END_X; ++x) {
            cocos2d::Sprite* tile = _itemsLayer->getTileAt(Vec2(x, y));
            if (tile) {
                tile->setScale(1.0f);
            }
        }
    }

    // 放大选中的物品
    cocos2d::Sprite* selectedTile = _itemsLayer->getTileAt(_selectedItemCoord);
    if (selectedTile) {
        selectedTile->setScale(1.2f); // 放大选中的物品
    }
}

bool Shop::isWithinShopArea(cocos2d::Vec2 itemCoord) {
    return (itemCoord.x >= SHOP_AREA_START_X && itemCoord.x <= SHOP_AREA_END_X &&
        itemCoord.y >= SHOP_AREA_START_Y && itemCoord.y <= SHOP_AREA_END_Y);
}

void Shop::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    cocos2d::Vec2 newItemCoord = _selectedItemCoord;

    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            newItemCoord.y -= 1;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            newItemCoord.y += 1;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            newItemCoord.x -= 1;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            newItemCoord.x += 1;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_ENTER: // 处理 Enter 键
            logSelectedItemCoord();
            break;
        default:
            return;
    }

    // 检查新坐标是否在商店区域内
    if (isWithinShopArea(newItemCoord)) {
        _selectedItemCoord = newItemCoord;
        highlightSelectedItem();
    }
}
void Shop::displayPlayerMoney() {
    // 获取玩家的金钱数额
    auto player = Player::getInstance();
    int playerMoney = player->getmoney(); // 假设 player 是一个全局或成员变量

    // 创建一个文本标签来显示金钱
     _moneyLabel = Label::createWithTTF("Money: " + std::to_string(playerMoney), "fonts/arial.ttf", 24); // 替换字体路径
    if (!_moneyLabel) {
        CCLOG("Error: Failed to create money label!");
        return;
    }

    // 设置文本标签的位置（商店 TMX 地图的左上角）
    Vec2 mapTopLeft = Vec2(0, _tileMap->getContentSize().height);
    Vec2 worldTopLeft = _tileMap->convertToWorldSpace(mapTopLeft);
    _moneyLabel->setPosition(worldTopLeft + Vec2(10, -10)); // 稍微偏移一点，避免遮挡地图边缘

    // 将文本标签添加到商店层
    this->addChild(_moneyLabel);
    CCLOG("Money label added at position: %f, %f", _moneyLabel->getPositionX(), _moneyLabel->getPositionY());
}
void Shop::updatePlayerMoneyDisplay(int newMoney) 
{
    // 检查金钱标签是否已经创建
    if (_moneyLabel) {
        // 更新金钱标签的文本
        _moneyLabel->setString("Money: " + std::to_string(newMoney));
        CCLOG("Player money updated to: %d", newMoney);
    }
}
void Shop::logSelectedItemCoord() {
    
    // 打印当前选中的瓦片坐标
    CCLOG("Selected item coordinate: (%d, %d)", (int)_selectedItemCoord.x, (int)_selectedItemCoord.y);
    auto player = Player::getInstance();
    if (_selectedItemCoord.x == 3)//鱼类在第三列
    {
        if (_selectedItemCoord.y == 1)
        {
            if (player->getInventory()->removeItem("fish1", 1))
                player->setMoney(player->getmoney() + 10);
        }
        else if (_selectedItemCoord.y == 2)
        {
            if (player->getInventory()->removeItem("fish2", 1))
                player->setMoney(player->getmoney() + 30);
        }
        else if (player->getInventory()->removeItem("fish3", 1))
        {
            player->setMoney(player->getmoney() + 50);
        }

    }
    if (_selectedItemCoord.x == 1)
    {
        if (_selectedItemCoord.y == 1)
        {
            if (player->getInventory()->removeItem("kuang1", 1))
                player->setMoney(player->getmoney() + 50);
        }
        else if (_selectedItemCoord.y == 2)
        {
            if (player->getInventory()->removeItem("kuang2", 1))
                player->setMoney(player->getmoney() + 10);
        }
    }
    if (_selectedItemCoord.x == 2)//第二列
    {
        if (_selectedItemCoord.y == 1)
        {
            if (player->getInventory()->addItemToInventory("seed",1));
                player->setMoney(player->getmoney() + 50);
        }
        else if (_selectedItemCoord.y == 2)
        {
            if (player->getInventory()->removeItem("kuang2", 1))
                player->setMoney(player->getmoney() + 10);
        }
    }

}
void Shop::setVisible(bool visible) {
    // 调用父类的 setVisible 方法
    Layer::setVisible(visible);

    // 根据可见性动态启用或禁用键盘事件监听器
    if (visible) {
        // 如果商店可见，重新添加键盘事件监听器
        auto eventListener = EventListenerKeyboard::create();
        eventListener->onKeyPressed = CC_CALLBACK_2(Shop::onKeyPressed, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    }
    else {
        // 如果商店不可见，移除键盘事件监听器
        _eventDispatcher->removeEventListenersForTarget(this, true);
    }
}