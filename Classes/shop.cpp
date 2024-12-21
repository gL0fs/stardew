#include "Shop.h"
#include "Player.h"
Shop* Shop::_instance = nullptr; // ��ʼ������ʵ��

Shop* Shop::getInstance() {
    if (!_instance) {
        _instance = new (std::nothrow) Shop();
        if (_instance && _instance->init()) {
            // ��Ҫʹ�� autorelease()
        }
        else {
            CC_SAFE_DELETE(_instance);
            _instance = nullptr; // ȷ�� _instance ������Ϊ nullptr
        }
    }
    return _instance;
}

Shop::Shop() {
    // ˽�й��캯��
}

Shop::~Shop() {
    // ˽����������
}

bool Shop::init() {
    if (!Layer::init()) {
        return false;
    }

    // �����̵�� TMX ��ͼ
    _tileMap = TMXTiledMap::create("shop.tmx"); // �滻Ϊ����̵� TMX �ļ�
    CCLOG("SHOPINTIAL");
    if (!_tileMap) {
        CCLOG("Error: Failed to load shop TMX map!");
        return false;
    }
    _tileMap->setScale(5.0f);
    _tileMap->setAnchorPoint(Vec2(0.5, 0.5));
    _tileMap->setPosition(Director::getInstance()->getVisibleSize() / 2);
    
    this->addChild(_tileMap);

    // ��ȡ��Ʒ��
    _itemsLayer = _tileMap->getLayer("items"); // �滻Ϊ�����Ʒ������
    if (!_itemsLayer) {
        CCLOG("Error: 'items' layer not found in the TMX map!");
        return false;
    }

    // ��ʼ��ѡ�е���Ʒ����
    _selectedItemCoord = Vec2(SHOP_AREA_START_X, SHOP_AREA_START_Y);

    // ���������¼�
    auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = CC_CALLBACK_2(Shop::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    // ��ʾ��ҳ��еĽ�Ǯ
    displayPlayerMoney();
    return true;
}

void Shop::displayShop() {
    auto shop = Shop::getInstance();
    static int visible=1;
    if (!shop->getParent()) {
        Director::getInstance()->getRunningScene()->addChild(shop);
        CCLOG("�ɼ�");
    }
    else {
        visible = 1 - visible;
        shop->setVisible(visible);
        CCLOG("�л�");
    }
}

void Shop::highlightSelectedItem() {
    // ����������Ʒ������
    for (int y = SHOP_AREA_START_Y; y <= SHOP_AREA_END_Y; ++y) {
        for (int x = SHOP_AREA_START_X; x <= SHOP_AREA_END_X; ++x) {
            cocos2d::Sprite* tile = _itemsLayer->getTileAt(Vec2(x, y));
            if (tile) {
                tile->setScale(1.0f);
            }
        }
    }

    // �Ŵ�ѡ�е���Ʒ
    cocos2d::Sprite* selectedTile = _itemsLayer->getTileAt(_selectedItemCoord);
    if (selectedTile) {
        selectedTile->setScale(1.2f); // �Ŵ�ѡ�е���Ʒ
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
        case cocos2d::EventKeyboard::KeyCode::KEY_ENTER: // ���� Enter ��
            logSelectedItemCoord();
            break;
        default:
            return;
    }

    // ����������Ƿ����̵�������
    if (isWithinShopArea(newItemCoord)) {
        _selectedItemCoord = newItemCoord;
        highlightSelectedItem();
    }
}
void Shop::displayPlayerMoney() {
    // ��ȡ��ҵĽ�Ǯ����
    auto player = Player::getInstance();
    int playerMoney = player->getmoney(); // ���� player ��һ��ȫ�ֻ��Ա����

    // ����һ���ı���ǩ����ʾ��Ǯ
     _moneyLabel = Label::createWithTTF("Money: " + std::to_string(playerMoney), "fonts/arial.ttf", 24); // �滻����·��
    if (!_moneyLabel) {
        CCLOG("Error: Failed to create money label!");
        return;
    }

    // �����ı���ǩ��λ�ã��̵� TMX ��ͼ�����Ͻǣ�
    Vec2 mapTopLeft = Vec2(0, _tileMap->getContentSize().height);
    Vec2 worldTopLeft = _tileMap->convertToWorldSpace(mapTopLeft);
    _moneyLabel->setPosition(worldTopLeft + Vec2(10, -10)); // ��΢ƫ��һ�㣬�����ڵ���ͼ��Ե

    // ���ı���ǩ��ӵ��̵��
    this->addChild(_moneyLabel);
    CCLOG("Money label added at position: %f, %f", _moneyLabel->getPositionX(), _moneyLabel->getPositionY());
}
void Shop::updatePlayerMoneyDisplay(int newMoney) 
{
    // ����Ǯ��ǩ�Ƿ��Ѿ�����
    if (_moneyLabel) {
        // ���½�Ǯ��ǩ���ı�
        _moneyLabel->setString("Money: " + std::to_string(newMoney));
        CCLOG("Player money updated to: %d", newMoney);
    }
}
void Shop::logSelectedItemCoord() {
    
    // ��ӡ��ǰѡ�е���Ƭ����
    CCLOG("Selected item coordinate: (%d, %d)", (int)_selectedItemCoord.x, (int)_selectedItemCoord.y);
    auto player = Player::getInstance();
    if (_selectedItemCoord.x == 3)//�����ڵ�����
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
    if (_selectedItemCoord.x == 2)//�ڶ���
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
    // ���ø���� setVisible ����
    Layer::setVisible(visible);

    // ���ݿɼ��Զ�̬���û���ü����¼�������
    if (visible) {
        // ����̵�ɼ���������Ӽ����¼�������
        auto eventListener = EventListenerKeyboard::create();
        eventListener->onKeyPressed = CC_CALLBACK_2(Shop::onKeyPressed, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    }
    else {
        // ����̵겻�ɼ����Ƴ������¼�������
        _eventDispatcher->removeEventListenersForTarget(this, true);
    }
}